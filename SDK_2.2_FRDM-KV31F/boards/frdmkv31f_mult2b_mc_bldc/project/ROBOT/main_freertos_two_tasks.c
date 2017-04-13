/*
* Copyright (c) 2015 - 2016, Freescale Semiconductor, Inc.
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without modification,
* are permitted provided that the following conditions are met:
*
* o Redistributions of source code must retain the above copyright notice, this list
*   of conditions and the following disclaimer.
*
* o Redistributions in binary form must reproduce the above copyright notice, this
*   list of conditions and the following disclaimer in the documentation and/or
*   other materials provided with the distribution.
*
* o Neither the name of Freescale Semiconductor, Inc. nor the names of its
*   contributors may be used to endorse or promote products derived from this
*   software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
* ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
* ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/*! \file main_freertos_two_tasks.c
    \brief FreeRTOS (two task) implementation of sensor fusion on FRDM-K64F.

    This file shows one recommended way to incorporate sensor fusion capabilities
    into a FreeRTOS project.
*/

/* FreeRTOS kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "event_groups.h"

// KSDK and ISSDK Headers
#include "fsl_debug_console.h"  // KSDK header file for the debug interface
#include "board.h"              // KSDK header file to define board configuration
#include "pin_mux.h"            // KSDK header file for pin mux initialization functions
#include "clock_config.h"       // KSDK header file for clock configuration
#include "fsl_port.h"           // KSDK header file for Port I/O control
#include "fsl_i2c.h"            // KSDK header file for I2C interfaces
#include "fxas21002.h"          // register address and bit field definitions
#include "mpl3115.h"            // register address and bit field definitions
#include "fxos8700.h"           // register address and bit field definitions
#include "fsl_i2c_cmsis.h"
#include "register_io_i2c.h"
#include "fsl_smc.h"

// Sensor Fusion Headers
#include "sensor_fusion.h"      // top level magCal and sensor fusion interfaces
#include "control.h"  	        // Command/Streaming interface - application specific
#include "status.h"   	        // Sta:tus indicator interface - application specific
#include "drivers.h"  	        // NXP sensor drivers OR customer-supplied drivers

#include "driver_pit.h"        // PIT is used to call cyclically sensor fusion task
#ifdef COM_TG
#include "com.h" // com headers
#endif
#include "motors.h"

// Global data structures
SensorFusionGlobals sfg;                ///< This is the primary sensor fusion data structure
ControlSubsystem controlSubsystem;      ///< used for serial communications
StatusSubsystem statusSubsystem;        ///< provides visual (usually LED) status indicator
struct PhysicalSensor sensors[3];              ///< This implementation uses three physical sensors
EventGroupHandle_t event_group = NULL;
EventGroupHandle_t event_PIT = NULL; ///<used to call cyclically the read_task

registerDeviceInfo_t i2cBusInfo_frdm_fxs_mul2b_shield = {
    .deviceInstance     = I2C_S_DEVICE_INDEX,
    .functionParam      = SMC,
    .idleFunction       = (registeridlefunction_t) SMC_SetPowerModeWait
};

registerDeviceInfo_t i2cBusInfo_frdm_kv31f = {
    .deviceInstance     = I2C_B_DEVICE_INDEX,
    .functionParam      = SMC,
    .idleFunction       = (registeridlefunction_t) SMC_SetPowerModeWait
};

static void read_task(void *pvParameters);              // FreeRTOS Task definition
static void fusion_task(void *pvParameters);            // FreeRTOS Task definition
static void WakeUp(void);                               // function used to wake up read task

/// This is a FreeRTOS (dual task) implementation of the NXP sensor fusion demo build.
int main(void)
{
    BOARD_InitPins();                   // defined in pin_mux.c, initializes pkg pins
    BOARD_BootClockRUN();               // defined in clock_config.c, initializes clocks
    BOARD_InitDebugConsole();           // defined in board.c, initializes the OpenSDA port

    ARM_DRIVER_I2C* I2Cdrv1 = &I2C_S_DRIVER;           // defined in the <shield>.h file
    ARM_DRIVER_I2C* I2Cdrv0 = &I2C_BB_DRIVER;          // defined in the frdm_kv31f.h file

    I2Cdrv1->Initialize(I2C_S_SIGNAL_EVENT);           // Initialize the KSDK driver for the I2C port
    I2Cdrv1->PowerControl(ARM_POWER_FULL);             // Set the I2C Power mode.
    I2Cdrv1->Control(ARM_I2C_BUS_SPEED, ARM_I2C_BUS_SPEED_FAST);      // Configure the I2C bus speed

    I2Cdrv0->Initialize(I2C_BB_SIGNAL_EVENT);           // Initialize the KSDK driver for the I2C port
    I2Cdrv0->PowerControl(ARM_POWER_FULL);              // Set the I2C Power mode.
    I2Cdrv0->Control(ARM_I2C_BUS_SPEED, ARM_I2C_BUS_SPEED_FAST);// Configure the I2C bus speed

#ifndef COM_TG
    initializeControlPort(&controlSubsystem);                           // configure pins and ports for the control sub-system
#endif

    MOTORS_Initialization();

    initializeStatusSubsystem(&statusSubsystem);                        // configure pins and ports for the status sub-system
    initSensorFusionGlobals(&sfg, &statusSubsystem, &controlSubsystem); // Initialize sensor fusion structures
    // "install" the sensors we will be using
    sfg.installSensor(&sfg, &sensors[0], FXOS8700_I2C_ADDR,              1, (void*) I2Cdrv1, &i2cBusInfo_frdm_fxs_mul2b_shield, FXOS8700_Init,  FXOS8700_Read);
    //sfg.installSensor(&sfg, &sensors[0], MOTHER_BOARD_FXOS8700_I2C_ADDR, 1, (void*) I2Cdrv0, &i2cBusInfo_frdm_kv31f,            FXOS8700_Init,  FXOS8700_Read);
    sfg.installSensor(&sfg, &sensors[1], FXAS21002_I2C_ADDR,             1, (void*) I2Cdrv1, &i2cBusInfo_frdm_fxs_mul2b_shield, FXAS21002_Init, FXAS21002_Read);
    sfg.installSensor(&sfg, &sensors[2], MPL3115_I2C_ADDR,               2, (void*) I2Cdrv1, &i2cBusInfo_frdm_fxs_mul2b_shield, MPL3115_Init,   MPL3115_Read);
    sfg.initializeFusionEngine(&sfg);	        // This will initialize sensors and magnetic calibration

    event_group = xEventGroupCreate();
    event_PIT   = xEventGroupCreate();

    xTaskCreate(read_task, "READ", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 2, NULL);
    xTaskCreate(fusion_task, "FUSION", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);

#ifdef COM_TG
    COM_InitializeTask();
#endif

    NVIC_SetPriority(PIT0_IRQn, 5);             //fix the priority of PIT0
    pit_init(12500, WakeUp);                    //Start PIT timer used to call cyclically the sensor fusion tasks every 12.5 ms

    sfg.setStatus(&sfg, NORMAL);                // If we got this far, let's set status state to NORMAL
    vTaskStartScheduler();                      // Start the RTOS scheduler
    sfg.setStatus(&sfg, HARD_FAULT);            // If we got this far, FreeRTOS does not have enough memory allocated
    for (;;) ;
}

static void read_task(void *pvParameters)
{
    static uint16_t i=0;              // general counter variable
    while (1)
    {
        // wait periodic PIT event
        xEventGroupWaitBits(event_PIT,      /* The event PIT handle. */
                            B0,             /* The bit pattern the event group is waiting for. */
                            pdTRUE,         /* BIT_0 and BIT_4 will be cleared automatically. */
                            pdFALSE,        /* Don't wait for both bits, either bit unblock task. */
                            portMAX_DELAY); /* Block indefinitely to wait for the condition to be met. */
        i++;
        sfg.readSensors(&sfg, i);           // Reads sensors, applies HAL and does averaging (if applicable)
        if(i==OVERSAMPLE_RATE)
        {
            xEventGroupSetBits(event_group, B0);
            i=0;
        }
    }
}

static void fusion_task(void *pvParameters)
{
    uint16_t i=0;  // general counter variable
    while (1)
    {
        xEventGroupWaitBits(event_group,    /* The event group handle. */
                            B0,             /* The bit pattern the event group is waiting for. */
                            pdTRUE,         /* BIT_0 and BIT_4 will be cleared automatically. */
                            pdFALSE,        /* Don't wait for both bits, either bit unblock task. */
                            portMAX_DELAY); /* Block indefinitely to wait for the condition to be met. */

        sfg.conditionSensorReadings(&sfg);  // magCal is run as part of this
        sfg.runFusion(&sfg);                // Run the actual fusion algorithms
        sfg.applyPerturbation(&sfg);        // apply debug perturbation (testing only)

        sfg.loopcounter++;                  // The loop counter is used to "serialize" mag cal operations
        i=i+1;
        if (i>=4)
        {                                   // Some status codes include a "blink" feature.  This loop
            i=0;                            // should cycle at least four times for that to operate correctly.
            sfg.updateStatus(&sfg);         // This is where pending status updates are made visible

#ifdef COM_TG
        COM_WakeUp();                       // wake-up task COM
#endif
        }
        sfg.queueStatus(&sfg, NORMAL);      // assume NORMAL status for next pass through the loop


#ifndef COM_TG
        sfg.pControlSubsystem->stream(&sfg, sUARTOutputBuffer);      // Send stream data to the Sensor Fusion Toolbox
#endif
    }
}

static void WakeUp(void)
{
    BaseType_t xHigherPriorityTaskWoken, xResult;

    xHigherPriorityTaskWoken = pdFALSE;
    xResult = pdFAIL;

    xResult = xEventGroupSetBitsFromISR(event_PIT, B0, &xHigherPriorityTaskWoken );

    if (xResult != pdFAIL)
    {
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    }

}
/// \endcode




