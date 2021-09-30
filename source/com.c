#include "assert.h"

/* FreeRTOS kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "event_groups.h"

/* Freescale includes. */
#include "stdtype.h"

#ifdef COM_REAL_TIME_ROBOT
#ifdef COM_BLUETOOTH
#include "uart.h"
#else
#include "lpuart.h"
#endif
#endif

#ifdef UART_TIME_LOG
#include "driver_pit.h"    //used to timestamp uart caracter
#endif

#include "hdlc.h"

/* sensor fusion */
#include "sensor_fusion.h"

/* filter*/
#include "filter.h"
#include "motors.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* Task priorities. */
#define uart_task_PRIORITY (tskIDLE_PRIORITY)
#define COM_FLAG1 (TickType_t)1

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
EventGroupHandle_t event_COM = NULL; ///<used to call cyclically the COM task
UI08 COM_gu8TxLifeByteFrame = 0;
UI08 COM_gu8RxLifeByteFrame = 0;


float af32ListOfAcc[256][3];
uint32_t u32Index=0;
float af32AverageAcc[3];
float af32SumAcc[3];
uint32_t u32InitIsdone = 0;

/* command received from the master:
 * - 't' connect TX and RX lpuart to test hard in loop mode
 * - 's' send Gx, Gy, Gz, roll, pitch , eCompass periodically
 **/
UI08 gu8CmdReceived = 0;

UI32 gu32CmdPattern = 0; /*used to test com when Rx is connected to Tx */


float gfAccGlOutput[3];
float gfVelGl[3];
float gfPosition[3];
extern SensorFusionGlobals sfg;


static float f32Cap = 0;
static float f32CapError;

static MOTOR_eMotorsOrders eMotorCommand = MOTOR_eStop;
static uint16_t u16PWMLevel = 0;

static UI32 gu32PIT1TxValue = 0;
static UI32 gu32PIT1RxValue = 0;
static UI32 gu32LatencyInus = 0;

/*cap control command */
static void CalculateNewMotorCommand(MOTOR_eMotorsOrders eMotorCommand,
		                             uint16_t  u16PWMLevelCmd,
					  				 float f32CapCmd,
									 float f32eCompass,
									 uint16_t* u16NewPWMLevelLeft, uint16_t* u16NewPWMLevelRight)
{
	int16_t s16PWMLeft =0;
	int16_t s16PWMRight=0;
	uint16_t u16PWMMax = MOTORS_u16GetMaxPWMLevel();

	/* calculate the error between the cap command and the eCompass */
    f32CapError = f32CapCmd - f32eCompass;

    /* calculate the minus cap error */
    if(f32CapError >   180.0) f32CapError = -(360.0-f32CapError);
    if(f32CapError <= -180.0) f32CapError =  (360.0+f32CapError);

    /* calculate the new motor command */
    s16PWMLeft  = ((int16_t)u16PWMLevelCmd)  + (int16_t)(((float)u16PWMLevelCmd) * f32CapError/10.0);
	s16PWMRight = ((int16_t)u16PWMLevelCmd)  - (int16_t)(((float)u16PWMLevelCmd) * f32CapError/10.0);

    /* check the range of PWM Right */
	if(s16PWMLeft <= 0)
		*u16NewPWMLevelLeft = 0U;
	else if(s16PWMLeft >= u16PWMMax)
		*u16NewPWMLevelLeft = u16PWMMax;
	else
		*u16NewPWMLevelLeft = s16PWMLeft;

	/* check the range of PWM Right */
	if(s16PWMRight <= 0)
		*u16NewPWMLevelRight = 0U;
	else if(s16PWMRight >= u16PWMMax)
		*u16NewPWMLevelRight = u16PWMMax;
	else
		*u16NewPWMLevelRight = s16PWMRight;

    /**/
}

/*!
 * @brief Task responsible for controlling com with PC/master board with bluetooth.
 */
static void com_TxTask(void *pvParameters)
{
    union
	{
    	float    f32Value;
    	uint32_t u32Value;
    	uint8_t  au8Data[4];
	}Convert32Bits;

	uint8_t au8TxFrame[HDLC_U8_MAX_NB_BYTE_IN_FRAME];
    uint8_t u8TxFrameSize;

    uint16_t u16PWMLevelLeft;
    uint16_t u16PWMLevelRight;

    while(1)
    {
        xEventGroupWaitBits(event_COM,      /* The event group handle. */
        		            COM_FLAG1,      /* The bit pattern the event group is waiting for. */
                            pdTRUE,         /* BIT_0 and BIT_4 will be cleared automatically. */
                            pdFALSE,        /* Don't wait for both bits, either bit unblock task. */
                            portMAX_DELAY); /* Block indefinitely to wait for the condition to be met. */

        /* test loopback TX et RX */
        if(gu8CmdReceived == 't')
        {
            /* Send frame data */
        	au8TxFrame[0] = 'C';
        	au8TxFrame[1] = 'A';
        	au8TxFrame[2] = 'F';
        	au8TxFrame[3] = 'E';
    	    u8TxFrameSize = 4;
    	    HDLC_bPutFrame(&au8TxFrame[0],&u8TxFrameSize);
        }
        else if(gu8CmdReceived == 's')
        {
        	//calculate new PWM left and right
			CalculateNewMotorCommand(eMotorCommand,
									 u16PWMLevel,
									 f32Cap,
									 sfg.SV_9DOF_GBY_KALMAN.fRhoPl,
									 &u16PWMLevelLeft,&u16PWMLevelRight);

			// update new motor command
			MOTORS_UpdateCommand(eMotorCommand,u16PWMLevelLeft,u16PWMLevelRight);

			//periodical communication with the slave device
			/*update life byte*/
			au8TxFrame[ 0] = COM_gu8TxLifeByteFrame;
			au8TxFrame[ 1] = COM_gu8RxLifeByteFrame;
			COM_gu8TxLifeByteFrame++;

			/* update pit channel 1 */
			gu32PIT1TxValue = pit_GetChannel1();
			Convert32Bits.f32Value = gu32LatencyInus;
			au8TxFrame[ 2] = Convert32Bits.au8Data[0];
			au8TxFrame[ 3] = Convert32Bits.au8Data[1];
			au8TxFrame[ 4] = Convert32Bits.au8Data[2];
			au8TxFrame[ 5] = Convert32Bits.au8Data[3];

			/* update linear acceleration (g) X */
			Convert32Bits.f32Value = sfg.SV_9DOF_GBY_KALMAN.fAccGl[CHX];
			au8TxFrame[ 6] = Convert32Bits.au8Data[0];
			au8TxFrame[ 7] = Convert32Bits.au8Data[1];
			au8TxFrame[ 8] = Convert32Bits.au8Data[2];
			au8TxFrame[ 9] = Convert32Bits.au8Data[3];

			/* update linear acceleration (g) Y */
			Convert32Bits.f32Value = sfg.SV_9DOF_GBY_KALMAN.fAccGl[CHY];
			au8TxFrame[10] = Convert32Bits.au8Data[0];
			au8TxFrame[11] = Convert32Bits.au8Data[1];
			au8TxFrame[12] = Convert32Bits.au8Data[2];
			au8TxFrame[13] = Convert32Bits.au8Data[3];

			/* update linear acceleration (g) Z */
			Convert32Bits.f32Value = sfg.SV_9DOF_GBY_KALMAN.fAccGl[CHZ];
			au8TxFrame[14] = Convert32Bits.au8Data[0];
			au8TxFrame[15] = Convert32Bits.au8Data[1];
			au8TxFrame[16] = Convert32Bits.au8Data[2];
			au8TxFrame[17] = Convert32Bits.au8Data[3];

			/* update roll (deg) */
			Convert32Bits.f32Value = sfg.SV_9DOF_GBY_KALMAN.fPhiPl;
			au8TxFrame[18] = Convert32Bits.au8Data[0];
			au8TxFrame[19] = Convert32Bits.au8Data[1];
			au8TxFrame[20] = Convert32Bits.au8Data[2];
			au8TxFrame[21] = Convert32Bits.au8Data[3];

			/* update pitch (deg) */
			Convert32Bits.f32Value = sfg.SV_9DOF_GBY_KALMAN.fThePl;
			au8TxFrame[22] = Convert32Bits.au8Data[0];
			au8TxFrame[23] = Convert32Bits.au8Data[1];
			au8TxFrame[24] = Convert32Bits.au8Data[2];
			au8TxFrame[25] = Convert32Bits.au8Data[3];

			/* update compass (deg) */
			Convert32Bits.f32Value = sfg.SV_9DOF_GBY_KALMAN.fRhoPl;
			au8TxFrame[26] = Convert32Bits.au8Data[0];
			au8TxFrame[27] = Convert32Bits.au8Data[1];
			au8TxFrame[28] = Convert32Bits.au8Data[2];
			au8TxFrame[29] = Convert32Bits.au8Data[3];

            /* Send frame data */
    	    u8TxFrameSize = 30;
    	    HDLC_bPutFrame(&au8TxFrame[0],&u8TxFrameSize);
         }
    }
}

/*!
 * @brief Task responsible for controlling com with PC/master board with bluetooth.
 */
static void com_RxTask(void *pvParameters)
{
	union
	{
    	    int16_t  s16Value;
    	    uint16_t u16Value;
	    	uint8_t  au8Data[2];
	}Convert16Bits;

	union
	{
	   	float    f32Value;
	   	uint32_t u32Value;
	   	uint8_t  au8Data[4];
	}Convert32Bits;

	BOOL bFrameReceived= FALSE;
    uint8_t au8RxFrame[HDLC_U8_MAX_NB_BYTE_IN_FRAME];
    uint8_t u8RxFrameSize;

    while(1)
    {
    	bFrameReceived = HDLC_bGetFrame(&au8RxFrame[0],&u8RxFrameSize);
        /* received a test command */
        if(bFrameReceived == TRUE)
        {
			/* received a command ('s':start, 'e':stop...) */
			if(u8RxFrameSize==1)
			{
				gu8CmdReceived = au8RxFrame[0];
				COM_gu8RxLifeByteFrame++;
			}
        	/* frame test loopback mode (RX connected to TX)*/
			else if(u8RxFrameSize==4)
			{
				/* read the PWM level */
				Convert32Bits.au8Data[0] = au8RxFrame[0];
				Convert32Bits.au8Data[1] = au8RxFrame[1];
				Convert32Bits.au8Data[2] = au8RxFrame[2];
				Convert32Bits.au8Data[3] = au8RxFrame[3];
				gu32CmdPattern = Convert32Bits.u32Value;
				COM_gu8RxLifeByteFrame++;
			}
			/* received cyclic motor command , response of request */
			else if(u8RxFrameSize==7)
			{
				COM_gu8RxLifeByteFrame++;

				/* get PIT1 value and measure latency */
				gu32PIT1RxValue = pit_GetChannel1();
				if(gu32PIT1RxValue > gu32PIT1TxValue)
				{
					gu32LatencyInus = gu32PIT1RxValue-gu32PIT1TxValue;
				}
				else
				{
					gu32LatencyInus = 0xFFFFFFFF-gu32PIT1TxValue+gu32PIT1RxValue;
				}

				/* read motor order */
				eMotorCommand           = (MOTOR_eMotorsOrders)au8RxFrame[0];

				/* read the PWM level */
				Convert16Bits.au8Data[0] = au8RxFrame[1];
				Convert16Bits.au8Data[1] = au8RxFrame[2];
				u16PWMLevel = Convert16Bits.u16Value;

				/* read cap command  in degree */
				Convert32Bits.au8Data[0] = au8RxFrame[3];
				Convert32Bits.au8Data[1] = au8RxFrame[4];
				Convert32Bits.au8Data[2] = au8RxFrame[5];
				Convert32Bits.au8Data[3] = au8RxFrame[6];
				f32Cap = Convert32Bits.f32Value;

			}
			else
			{
				/* do nothing */
			}
        }
    }
}


/*******************************************************************************
 * Code
 ******************************************************************************/

void COM_InitializeTask(void)
{
	BOOL bIsInitialized;

#ifdef COM_REAL_TIME_ROBOT
#ifdef COM_BLUETOOTH
	/* init device UART connected to bluetooth device communicate with the robot though bluetooth communication */
	bIsInitialized = HDLC_bInitialize(0,
    						    	  UART_bOpenDevice,
									  UART_bGetRxChar,
									  UART_bPutTxBuffer,
									  UART_bCloseDevice);
#else
	/* init device LPUART connected to the robot */
	bIsInitialized = HDLC_bInitialize(0,
    						    	  LPUART_bOpenDevice,
									  LPUART_bGetRxChar,
									  LPUART_bPutTxBuffer,
									  LPUART_bCloseDevice);
#endif
#endif
	if (bIsInitialized == TRUE )
    {
        /* create the Tx/Rx Task */
        xTaskCreate(com_TxTask, "ComTxtask", configMINIMAL_STACK_SIZE, NULL, uart_task_PRIORITY+1, NULL);
        xTaskCreate(com_RxTask, "ComRxtask", configMINIMAL_STACK_SIZE, NULL, uart_task_PRIORITY, NULL);

        event_COM   = xEventGroupCreate();

    }
    else
    {
    	assert(0);
    }
}

void COM_WakeUp(void)
{
	xEventGroupSetBits(event_COM, COM_FLAG1);
}

