/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
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
 * o Neither the name of the copyright holder nor the names of its
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

/** 
 * @file  mma865x_freefall.c
 *  @brief The mma865x_freefall.c file implements the ISSDK MMA865x sensor driver
 *        example demonstration for Freefall Detection.
 */

//-----------------------------------------------------------------------
// SDK Includes
//-----------------------------------------------------------------------
#include "board.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "fsl_debug_console.h"

//-----------------------------------------------------------------------
// CMSIS Includes
//-----------------------------------------------------------------------
#include "Driver_I2C.h"
#include "fsl_i2c_cmsis.h"

/* ISSDK Includes */
#include "issdk_hal.h"
#include "mma865x_drv.h"
#include "systick_utils.h"

//-----------------------------------------------------------------------
// Macros
//-----------------------------------------------------------------------
/* FF_MT freefall counter register values for High resolution Mode and ODR = 100Hz.
 * These values have been derived based on the MMA865x DataSheet and Application Note AN4070 for MMA8451 (the same is
 * applicable to MMA865x too).
 * http://cache.freescale.com/files/sensors/doc/app_note/AN4070.pdf */
#define FF_MT_WT_DBCNT 0x28  /* Debounce count value. */
#define FF_MT_THS_VALUE 0x03 /* Threshold Value. */
//-----------------------------------------------------------------------
// Constants
//-----------------------------------------------------------------------
/*! @brief Register settings for freefall detection. */
const registerwritelist_t cMma865xConfigFreeFall[] =
    {/*! Configure the MMA865x to set FS Range as 2g. */
     {MMA865x_XYZ_DATA_CFG, MMA865x_XYZ_DATA_CFG_FS_2G, MMA865x_XYZ_DATA_CFG_FS_MASK},
     /*! Configure the MMA865x to set ODR to 100Hz. */
     {MMA865x_CTRL_REG1, MMA865x_CTRL_REG1_DR_100HZ, MMA865x_CTRL_REG1_DR_MASK},
     /*! Configure the MMA865x to set High Resolution mode. */
     {MMA865x_CTRL_REG2, MMA865x_CTRL_REG2_MODS_HR, MMA865x_CTRL_REG2_MODS_MASK},
     /*! Configure the MMA865x to set freefall Mode and enable all XYZ axis events and event latching. */
     {MMA865x_FF_MT_CFG, MMA865x_FF_MT_CFG_ELE_EN | MMA865x_FF_MT_CFG_OAE_FREEFALL | MMA865x_FF_MT_CFG_XEFE_EN |
                             MMA865x_FF_MT_CFG_YEFE_EN | MMA865x_FF_MT_CFG_ZEFE_EN,
      MMA865x_FF_MT_CFG_ELE_MASK | MMA865x_FF_MT_CFG_OAE_MASK | MMA865x_FF_MT_CFG_XEFE_MASK |
          MMA865x_FF_MT_CFG_YEFE_MASK | MMA865x_FF_MT_CFG_ZEFE_MASK},
     /*! Configure the MMA865x to set Debounce counter to be cleared on favourable events and the thresholds . */
     {MMA865x_FF_MT_THS, MMA865x_FF_MT_THS_DBCNTM_INC_CLR | FF_MT_THS_VALUE,
      MMA865x_FF_MT_THS_DBCNTM_MASK | MMA865x_FF_MT_THS_THS_MASK},
     /*! Configure the MMA865x to set Debounce counter value. */
     {MMA865x_FF_MT_COUNT, FF_MT_WT_DBCNT, 0},
     __END_WRITE_DATA__};

/*! @brief Address of Freefall Status Register. */
const registerreadlist_t cMma865xFreeFallEvent[] = {{.readFrom = MMA865x_FF_MT_SRC, .numBytes = 1}, __END_READ_DATA__};

//-----------------------------------------------------------------------
// Functions
//-----------------------------------------------------------------------
/*!
 * @brief Main function
 */
int main(void)
{
    int32_t status;
    uint8_t dataReady;
    ARM_DRIVER_I2C *I2Cdrv = &I2C_S_DRIVER; // Now using the shield.h value!!!
    mma865x_i2c_sensorhandle_t mma865xDriver;

    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_SystickEnable();
    BOARD_InitDebugConsole();

    PRINTF("\r\n ISSDK MMA865x sensor driver example for Freefall Detection. \r\n");

    /*! Initialize the I2C driver. */
    status = I2Cdrv->Initialize(I2C_S_SIGNAL_EVENT);
    if (ARM_DRIVER_OK != status)
    {
        PRINTF("\r\n I2C Initialization Failed\r\n");
        return -1;
    }

    /*! Set the I2C Power mode. */
    status = I2Cdrv->PowerControl(ARM_POWER_FULL);
    if (ARM_DRIVER_OK != status)
    {
        PRINTF("\r\n I2C Power Mode setting Failed\r\n");
        return -1;
    }

    /*! Set the I2C bus speed. */
    status = I2Cdrv->Control(ARM_I2C_BUS_SPEED, ARM_I2C_BUS_SPEED_FAST);
    if (ARM_DRIVER_OK != status)
    {
        PRINTF("\r\n I2C Control Mode setting Failed\r\n");
        return -1;
    }

    /*! Initialize the MMA865x sensor driver. */
    status = MMA865x_I2C_Initialize(&mma865xDriver, &I2C_S_DRIVER, I2C_S_DEVICE_INDEX, MMA8652_I2C_ADDR,
                                    MMA8652_WHOAMI_VALUE);
    if (SENSOR_ERROR_NONE != status)
    {
        PRINTF("\r\n Sensor Initialization Failed\r\n");
        return -1;
    }
    PRINTF("\r\n Successfully Initiliazed Sensor\r\n");

    /*!  Set the task to be executed while waiting for I2C transactions to complete. */
    MMA865x_I2C_SetIdleTask(&mma865xDriver, (registeridlefunction_t)SMC_SetPowerModeWait, SMC);

    /* Set data not ready, event data will be available after sensor is configured and free fall detected. */
    dataReady = 0;

    /*! Configure the MMA865x sensor for Freefall detection Mode. */
    status = MMA865x_I2C_Configure(&mma865xDriver, cMma865xConfigFreeFall);
    if (SENSOR_ERROR_NONE != status)
    {
        PRINTF("\r\n MMA865x Sensor Configuration Failed, Err = %d \r\n", status);
        return -1;
    }
    PRINTF("\r\n MMA865x now active and detecting freefall... \r\n");

    for (;;) /* Forever loop */
    {
        /*! Read the Freefall event FLAGs from MMA865x. */
        status = MMA865x_I2C_ReadData(&mma865xDriver, cMma865xFreeFallEvent, &dataReady);
        if (SENSOR_ERROR_NONE != status)
        {
            PRINTF("\r\n Read Failed\r\n");
            return -1;
        }
        if (0 == (dataReady & MMA865x_FF_MT_SRC_EA_MASK))
        { /* Loop, if new event is not detected. */
            continue;
        }

        /*! Display that a freefall event has been detected. */
        PRINTF("\r\n Freefall detected !!!\r\n");
    }
}
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////