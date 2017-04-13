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

float gfAccGlOutput[3];
float gfVelGl[3];
float gfPosition[3];

extern SensorFusionGlobals sfg;

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
	}ConvertBytes;

	uint8_t i;

	uint8_t au8TxFrame[HDLC_U8_MAX_NB_BYTE_IN_FRAME] = {0x00,0xAD,0xAA,0x55,00};
    uint8_t u8TxFrameSize;

    //periodical communication with the other device Bluetooth
    while(1)
    {
        xEventGroupWaitBits(event_COM,      /* The event group handle. */
        		            COM_FLAG1,      /* The bit pattern the event group is waiting for. */
                            pdTRUE,         /* BIT_0 and BIT_4 will be cleared automatically. */
                            pdFALSE,        /* Don't wait for both bits, either bit unblock task. */
                            portMAX_DELAY); /* Block indefinitely to wait for the condition to be met. */

        /*update life byte*/
        au8TxFrame[ 0] = COM_gu8TxLifeByteFrame;
        au8TxFrame[ 1] = COM_gu8RxLifeByteFrame;
        COM_gu8TxLifeByteFrame++;
#if 0
        /* */
        if(u32InitIsdone <= 255)
        {
			//filter_filterBlock(&sfg);
			af32ListOfAcc[u32Index][CHX] = sfg.SV_9DOF_GBY_KALMAN.fAccGl[CHX];
			af32ListOfAcc[u32Index][CHY] = sfg.SV_9DOF_GBY_KALMAN.fAccGl[CHY];
			af32ListOfAcc[u32Index][CHZ] = sfg.SV_9DOF_GBY_KALMAN.fAccGl[CHZ];

			af32SumAcc[CHX] += af32ListOfAcc[u32Index][CHX];
			af32SumAcc[CHY] += af32ListOfAcc[u32Index][CHY];
			af32SumAcc[CHZ] += af32ListOfAcc[u32Index][CHZ];

			u32Index = (u32Index+1)%256;
			u32InitIsdone++;
        }
        else
        {

        	af32SumAcc[CHX] -= af32ListOfAcc[u32Index][CHX];
			af32SumAcc[CHY] -= af32ListOfAcc[u32Index][CHY];
			af32SumAcc[CHZ] -= af32ListOfAcc[u32Index][CHZ];

        	af32SumAcc[CHX] += sfg.SV_9DOF_GBY_KALMAN.fAccGl[CHX];
			af32SumAcc[CHY] += sfg.SV_9DOF_GBY_KALMAN.fAccGl[CHY];
			af32SumAcc[CHZ] += sfg.SV_9DOF_GBY_KALMAN.fAccGl[CHZ];

        	af32ListOfAcc[u32Index][CHX] = sfg.SV_9DOF_GBY_KALMAN.fAccGl[CHX];
			af32ListOfAcc[u32Index][CHY] = sfg.SV_9DOF_GBY_KALMAN.fAccGl[CHY];
			af32ListOfAcc[u32Index][CHZ] = sfg.SV_9DOF_GBY_KALMAN.fAccGl[CHZ];


	        af32AverageAcc[CHX] = af32SumAcc[CHX]/256;
	        af32AverageAcc[CHY] = af32SumAcc[CHY]/256;
	        af32AverageAcc[CHZ] = af32SumAcc[CHZ]/256;

	        u32Index  = (u32Index+1)%256;
			gfAccGlOutput[CHX] = sfg.SV_9DOF_GBY_KALMAN.fAccGl[CHX] - af32AverageAcc[CHX];
			gfAccGlOutput[CHY] = sfg.SV_9DOF_GBY_KALMAN.fAccGl[CHY] - af32AverageAcc[CHY];
			gfAccGlOutput[CHZ] = sfg.SV_9DOF_GBY_KALMAN.fAccGl[CHZ] - af32AverageAcc[CHZ];
			for (i = CHX; i <= CHZ; i++) {
				// integrate acceleration (in g) to velocity in m/s
				gfVelGl[i] += gfAccGlOutput[i] * sfg.SV_9DOF_GBY_KALMAN.fgdeltat;
				// integrate velocity (in m/s) to displacement (m)
				gfPosition[i] += gfVelGl[i] * sfg.SV_9DOF_GBY_KALMAN.fdeltat;
			}
        }
#endif
        af32AverageAcc[CHX] = (sfg.SV_9DOF_GBY_KALMAN.fAccGl[CHX] + af32AverageAcc[CHX])/2;
        af32AverageAcc[CHY] = (sfg.SV_9DOF_GBY_KALMAN.fAccGl[CHY] + af32AverageAcc[CHY])/2;
        af32AverageAcc[CHZ] = (sfg.SV_9DOF_GBY_KALMAN.fAccGl[CHZ] + af32AverageAcc[CHZ])/2;

		gfAccGlOutput[CHX] = sfg.SV_9DOF_GBY_KALMAN.fAccGl[CHX] - af32AverageAcc[CHX];
		gfAccGlOutput[CHY] = sfg.SV_9DOF_GBY_KALMAN.fAccGl[CHY] - af32AverageAcc[CHY];
		gfAccGlOutput[CHZ] = sfg.SV_9DOF_GBY_KALMAN.fAccGl[CHZ] - af32AverageAcc[CHZ];
		for (i = CHX; i <= CHZ; i++) {
			// integrate acceleration (in g) to velocity in m/s
			gfVelGl[i] += gfAccGlOutput[i] * sfg.SV_9DOF_GBY_KALMAN.fgdeltat;
			// integrate velocity (in m/s) to displacement (m)
			gfPosition[i] += gfVelGl[i] * sfg.SV_9DOF_GBY_KALMAN.fdeltat;
		}


        /* update systick */
        ConvertBytes.u32Value = sfg.SV_9DOF_GBY_KALMAN.systick;
        au8TxFrame[ 2] = ConvertBytes.au8Data[0];
        au8TxFrame[ 3] = ConvertBytes.au8Data[1];
        au8TxFrame[ 4] = ConvertBytes.au8Data[2];
        au8TxFrame[ 5] = ConvertBytes.au8Data[3];

        /* update linear acceleration (g) X */
        ConvertBytes.f32Value = gfAccGlOutput[CHX];
        au8TxFrame[ 6] = ConvertBytes.au8Data[0];
        au8TxFrame[ 7] = ConvertBytes.au8Data[1];
        au8TxFrame[ 8] = ConvertBytes.au8Data[2];
        au8TxFrame[ 9] = ConvertBytes.au8Data[3];

        /* update linear acceleration (g) Y */
        ConvertBytes.f32Value = gfAccGlOutput[CHY];
        au8TxFrame[10] = ConvertBytes.au8Data[0];
        au8TxFrame[11] = ConvertBytes.au8Data[1];
        au8TxFrame[12] = ConvertBytes.au8Data[2];
        au8TxFrame[13] = ConvertBytes.au8Data[3];

        /* update linear acceleration (g) Z */
        ConvertBytes.f32Value = gfAccGlOutput[CHZ];
        au8TxFrame[14] = ConvertBytes.au8Data[0];
        au8TxFrame[15] = ConvertBytes.au8Data[1];
        au8TxFrame[16] = ConvertBytes.au8Data[2];
        au8TxFrame[17] = ConvertBytes.au8Data[3];

        /* update displacement (m) X */
        ConvertBytes.f32Value = gfAccGlOutput[CHX];
        au8TxFrame[18] = ConvertBytes.au8Data[0];
        au8TxFrame[19] = ConvertBytes.au8Data[1];
        au8TxFrame[20] = ConvertBytes.au8Data[2];
        au8TxFrame[21] = ConvertBytes.au8Data[3];

        /* update displacement (m) Y */
        ConvertBytes.f32Value = gfVelGl[CHX]; //af32AverageAcc[CHY];
        au8TxFrame[22] = ConvertBytes.au8Data[0];
        au8TxFrame[23] = ConvertBytes.au8Data[1];
        au8TxFrame[24] = ConvertBytes.au8Data[2];
        au8TxFrame[25] = ConvertBytes.au8Data[3];

        /* update displacement (m) Z */
        ConvertBytes.f32Value = gfPosition[CHX]; //af32AverageAcc[CHZ];
        au8TxFrame[26] = ConvertBytes.au8Data[0];
        au8TxFrame[27] = ConvertBytes.au8Data[1];
        au8TxFrame[28] = ConvertBytes.au8Data[2];
        au8TxFrame[29] = ConvertBytes.au8Data[3];

        /* Send frame data */
    	u8TxFrameSize = 30;
    	HDLC_bPutFrame(&au8TxFrame[0],&u8TxFrameSize);
    }
}

/*!
 * @brief Task responsible for controlling com with PC/master board with bluetooth.
 */
static void com_RxTask(void *pvParameters)
{
    BOOL bFrameReceived= FALSE;
    uint8_t au8RxFrame[HDLC_U8_MAX_NB_BYTE_IN_FRAME];
    uint8_t u8RxFrameSize;
    while(1)
    {
    	bFrameReceived = HDLC_bGetFrame(&au8RxFrame[0],&u8RxFrameSize);
        if((bFrameReceived == TRUE) &&
           (u8RxFrameSize!=0))
        {
        	COM_gu8RxLifeByteFrame++;
         	MOTORS_UpdateCommand(au8RxFrame[0],au8RxFrame[1],au8RxFrame[2]); // update motor control
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
