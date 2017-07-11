#include "assert.h"

/* FreeRTOS kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "event_groups.h"

/* Freescale includes. */
#include "stdtype.h"
#include "uart.h"
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

/* command reveived from the master:
 * - 's' send Gx, Gy, Gz, roll, pitch , eCompass */
UI08 u8CmdReceived = 0;

float gfAccGlOutput[3];
float gfVelGl[3];
float gfPosition[3];
extern SensorFusionGlobals sfg;


static float f32Cap = 0;
static float f32CapError;

static MOTOR_eMotorsOrders eMotorCommand = MOTOR_eStop;
static uint16_t u16PWMLevel = 0;


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

        if(u8CmdReceived == 's')
        {
			//calculate PWM left and right
			CalculateNewMotorCommand(eMotorCommand,
									 u16PWMLevel,
									 f32Cap,
									 sfg.SV_9DOF_GBY_KALMAN.fRhoPl,
									 &u16PWMLevelLeft,&u16PWMLevelRight);

			// update motor control
			MOTORS_UpdateCommand(eMotorCommand,u16PWMLevelLeft,u16PWMLevelRight);

			//periodical communication with the slave device Bluetooth on /dev/rfcommxx
			/*update life byte*/
			au8TxFrame[ 0] = COM_gu8TxLifeByteFrame;
			au8TxFrame[ 1] = COM_gu8RxLifeByteFrame;
			COM_gu8TxLifeByteFrame++;

			/* update linear acceleration (g) X */
			Convert32Bits.f32Value = sfg.SV_9DOF_GBY_KALMAN.fAccGl[CHX];
			au8TxFrame[ 2] = Convert32Bits.au8Data[0];
			au8TxFrame[ 3] = Convert32Bits.au8Data[1];
			au8TxFrame[ 4] = Convert32Bits.au8Data[2];
			au8TxFrame[ 5] = Convert32Bits.au8Data[3];

			/* update linear acceleration (g) Y */
			Convert32Bits.f32Value = sfg.SV_9DOF_GBY_KALMAN.fAccGl[CHY];
			au8TxFrame[ 6] = Convert32Bits.au8Data[0];
			au8TxFrame[ 7] = Convert32Bits.au8Data[1];
			au8TxFrame[ 8] = Convert32Bits.au8Data[2];
			au8TxFrame[ 9] = Convert32Bits.au8Data[3];

			/* update linear acceleration (g) Z */
			Convert32Bits.f32Value = sfg.SV_9DOF_GBY_KALMAN.fAccGl[CHZ];
			au8TxFrame[10] = Convert32Bits.au8Data[0];
			au8TxFrame[11] = Convert32Bits.au8Data[1];
			au8TxFrame[12] = Convert32Bits.au8Data[2];
			au8TxFrame[13] = Convert32Bits.au8Data[3];

			/* update roll (deg) */
			Convert32Bits.f32Value = sfg.SV_9DOF_GBY_KALMAN.fPhiPl;
			au8TxFrame[14] = Convert32Bits.au8Data[0];
			au8TxFrame[15] = Convert32Bits.au8Data[1];
			au8TxFrame[16] = Convert32Bits.au8Data[2];
			au8TxFrame[17] = Convert32Bits.au8Data[3];

			/* update pitch (deg) */
			Convert32Bits.f32Value = sfg.SV_9DOF_GBY_KALMAN.fThePl;
			au8TxFrame[18] = Convert32Bits.au8Data[0];
			au8TxFrame[19] = Convert32Bits.au8Data[1];
			au8TxFrame[20] = Convert32Bits.au8Data[2];
			au8TxFrame[21] = Convert32Bits.au8Data[3];

			/* update compass (deg) */
			Convert32Bits.f32Value = sfg.SV_9DOF_GBY_KALMAN.fRhoPl;
			au8TxFrame[22] = Convert32Bits.au8Data[0];
			au8TxFrame[23] = Convert32Bits.au8Data[1];
			au8TxFrame[24] = Convert32Bits.au8Data[2];
			au8TxFrame[25] = Convert32Bits.au8Data[3];

            /* Send frame data */
    	    u8TxFrameSize = 26;
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
        /* received a start command */
        if((bFrameReceived == TRUE) &&
           (u8RxFrameSize==1))
        {
        	u8CmdReceived = au8RxFrame[0];
        }
        /* received a motor command */
        else if((bFrameReceived == TRUE) &&
                (u8RxFrameSize==7))
        {
        	COM_gu8RxLifeByteFrame++;
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

    }
}

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief Application entry point.
 */
void COM_InitializeTask(void)
{
	BOOL bIsInitialized;
     /* init device */
	bIsInitialized = HDLC_bInitialize(0,
    						    	 UART_bOpenDevice,
									 UART_bGetRxChar,
									 UART_bPutTxChar,
									 UART_bCloseDevice);
    if (bIsInitialized == TRUE )
    {
        /* create the Tx/Rx Task */
        xTaskCreate(com_TxTask, "ComTxtask", configMINIMAL_STACK_SIZE, NULL, uart_task_PRIORITY, NULL);
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


#if 0 // code to check validity of eCompass

static int8_t s8CapIsInitialized = false;

if((sCompass = sfg.SV_9DOF_GBY_KALMAN.iFirstAccelMagLock == true) &&
   (s8CapIsInitialized == false))
{
    /* init first value of the s16Cap = eCompass at the startup of the system */
	s16Cap = sfg.SV_9DOF_GBY_KALMAN.fRhoPl;
	s16CapError = 0;
	s8CapIsInitialized = true;
}
else if((sCompass = sfg.SV_9DOF_GBY_KALMAN.iFirstAccelMagLock == true) &&
        (s8CapIsInitialized == true))
{

#endif
