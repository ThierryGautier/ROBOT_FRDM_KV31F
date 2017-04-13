#include "fsl_ftm.h"
#include "clock_config.h"
#include "motors.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* The Flextimer base address/channel pair used for board */
#define BOARD_FTM_BASEADDR FTM0

/* FTM channel 0 works with FTM channels 0 */
#define BOARD_FTM_CHANNEL0 kFTM_Chnl_0

/* FTM channel 1 works with FTM channels 1 */
#define BOARD_FTM_CHANNEL1 kFTM_Chnl_1

/* FTM channel 2 works with FTM channels 2 */
#define BOARD_FTM_CHANNEL2 kFTM_Chnl_2

/* FTM channel 3 works with FTM channels 3 */
#define BOARD_FTM_CHANNEL3 kFTM_Chnl_3

/* FTM channel 4 works with FTM channels 4 */
#define BOARD_FTM_CHANNEL4 kFTM_Chnl_4

/* FTM channel 5 works with FTM channels 5 */
#define BOARD_FTM_CHANNEL5 kFTM_Chnl_5

/* Get source clock for FTM driver */
#define FTM_SOURCE_CLOCK CLOCK_GetFreq(kCLOCK_BusClk)

/*******************************************************************************
 * Prototypes
 ******************************************************************************/


/*******************************************************************************
 * Variables
 ******************************************************************************/


/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * @brief MOTORS_Initialization function
 */
void MOTORS_Initialization(void)
{
    ftm_config_t ftmInfo;

    ftm_chnl_pwm_signal_param_t ftmParam[6];

    /* Configure ftm params with frequency 24kHZ */
    ftmParam[0].chnlNumber = BOARD_FTM_CHANNEL0;
    ftmParam[0].level = kFTM_HighTrue;
    ftmParam[0].dutyCyclePercent = 0;
    ftmParam[0].firstEdgeDelayPercent = 0U;

    ftmParam[1].chnlNumber = BOARD_FTM_CHANNEL1;
    ftmParam[1].level = kFTM_HighTrue;
    ftmParam[1].dutyCyclePercent = 0;
    ftmParam[1].firstEdgeDelayPercent = 0U;

    ftmParam[2].chnlNumber = BOARD_FTM_CHANNEL2;
    ftmParam[2].level = kFTM_HighTrue;
    ftmParam[2].dutyCyclePercent = 0;
    ftmParam[2].firstEdgeDelayPercent = 0U;

    ftmParam[3].chnlNumber = BOARD_FTM_CHANNEL3;
    ftmParam[3].level = kFTM_HighTrue;
    ftmParam[3].dutyCyclePercent = 0;
    ftmParam[3].firstEdgeDelayPercent = 0U;

    ftmParam[4].chnlNumber = BOARD_FTM_CHANNEL4;
    ftmParam[4].level = kFTM_HighTrue;
    ftmParam[4].dutyCyclePercent = 0;
    ftmParam[4].firstEdgeDelayPercent = 0U;

    ftmParam[5].chnlNumber = BOARD_FTM_CHANNEL5;
    ftmParam[5].level = kFTM_HighTrue;
    ftmParam[5].dutyCyclePercent = 0;
    ftmParam[5].firstEdgeDelayPercent = 0U;

    FTM_GetDefaultConfig(&ftmInfo);

    /* Initialize FTM module */
    FTM_Init(BOARD_FTM_BASEADDR, &ftmInfo);

    /* Setup output of a PWM signal */
    FTM_SetupPwm(BOARD_FTM_BASEADDR,
    		     &ftmParam[0],
				 sizeof(ftmParam)/sizeof(ftmParam[0]),
				 kFTM_EdgeAlignedPwm,
				 24000U,
				 FTM_SOURCE_CLOCK);
    FTM_StartTimer(BOARD_FTM_BASEADDR, kFTM_SystemClock);
}

void MOTORS_UpdateCommand(MOTOR_eMotorsOrders eMotorCommand, uint8_t u8PWMLevelLeft, uint8_t u8PWMLevelRight)
{   /** Trx:transistor of the bridges            **/
	/** Mx:Motor                                 **/
	/**     -= + batt                            **/
	/**     |--------|--------|                  **/
	/**    Tr0      Tr2     Tr4                  **/
	/**     |---M1---|---M2---|                  **/
	/**    Tr1      Tr3     TR5                  **/
	/**     |--------|--------|                  **/
	/**     -= - batt                            **/
	switch(eMotorCommand)
	{
	    case MOTOR_eMoveForward:
	    	/* drive Tr0/4 u8PWMLevel%; Tr1/2/5 disable 0%; Tr3 enable 100% */
	    	/**     |--------|--------|                  **/
	    	/**    Tr0(PWM) Tr2(OFF) Tr4(PWM)            **/
	    	/**     |---M1---|---M2---|                  **/
	    	/**    Tr1(OFF) Tr3(ON)  Tr5(OFF)            **/
	    	/**     |--------|--------|                  **/
	        FTM_UpdatePwmDutycycle(BOARD_FTM_BASEADDR,BOARD_FTM_CHANNEL0,kFTM_EdgeAlignedPwm,u8PWMLevelLeft);
	        FTM_UpdatePwmDutycycle(BOARD_FTM_BASEADDR,BOARD_FTM_CHANNEL1,kFTM_EdgeAlignedPwm,0);
	        FTM_UpdatePwmDutycycle(BOARD_FTM_BASEADDR,BOARD_FTM_CHANNEL2,kFTM_EdgeAlignedPwm,0);
	        FTM_UpdatePwmDutycycle(BOARD_FTM_BASEADDR,BOARD_FTM_CHANNEL3,kFTM_EdgeAlignedPwm,100);
	        FTM_UpdatePwmDutycycle(BOARD_FTM_BASEADDR,BOARD_FTM_CHANNEL4,kFTM_EdgeAlignedPwm,u8PWMLevelRight);
	        FTM_UpdatePwmDutycycle(BOARD_FTM_BASEADDR,BOARD_FTM_CHANNEL5,kFTM_EdgeAlignedPwm,0);
	        break;

	    case MOTOR_eBreakForward:
	    	/* drive Tr1/5 u8PWMLevel%; Tr0/2/4 disable 0%; Tr3 enable 100% */
	    	/**     |--------|--------|                  **/
	    	/**    Tr0(OFF) Tr2(OFF) Tr4(OFF)            **/
	    	/**     |---M1---|---M2---|                  **/
	    	/**    Tr1(PWM) Tr3(ON)  Tr5(PWM)            **/
	    	/**     |--------|--------|                  **/
	        FTM_UpdatePwmDutycycle(BOARD_FTM_BASEADDR,BOARD_FTM_CHANNEL0,kFTM_EdgeAlignedPwm,0);
	        FTM_UpdatePwmDutycycle(BOARD_FTM_BASEADDR,BOARD_FTM_CHANNEL1,kFTM_EdgeAlignedPwm,u8PWMLevelLeft);
	        FTM_UpdatePwmDutycycle(BOARD_FTM_BASEADDR,BOARD_FTM_CHANNEL2,kFTM_EdgeAlignedPwm,0);
	        FTM_UpdatePwmDutycycle(BOARD_FTM_BASEADDR,BOARD_FTM_CHANNEL3,kFTM_EdgeAlignedPwm,99);
	        FTM_UpdatePwmDutycycle(BOARD_FTM_BASEADDR,BOARD_FTM_CHANNEL4,kFTM_EdgeAlignedPwm,0);
	        FTM_UpdatePwmDutycycle(BOARD_FTM_BASEADDR,BOARD_FTM_CHANNEL5,kFTM_EdgeAlignedPwm,u8PWMLevelRight);
	    	break;

	    case MOTOR_eMoveBack:
	    	/* drive Tr1/5 u8PWMLevel%; Tr0/3/4 disable 0%; Tr2 enable 99% */
	    	/**     |--------|--------|                  **/
	    	/**    Tr0(OFF) Tr2(ON)  Tr4(OFF)            **/
	    	/**     |---M1---|---M2---|                  **/
	    	/**    Tr1(PWM) Tr3(OFF) Tr5(PWM)            **/
	    	/**     |--------|--------|                  **/
	        FTM_UpdatePwmDutycycle(BOARD_FTM_BASEADDR,BOARD_FTM_CHANNEL0,kFTM_EdgeAlignedPwm,0);
	        FTM_UpdatePwmDutycycle(BOARD_FTM_BASEADDR,BOARD_FTM_CHANNEL1,kFTM_EdgeAlignedPwm,u8PWMLevelLeft);
	        FTM_UpdatePwmDutycycle(BOARD_FTM_BASEADDR,BOARD_FTM_CHANNEL2,kFTM_EdgeAlignedPwm,99);
	        FTM_UpdatePwmDutycycle(BOARD_FTM_BASEADDR,BOARD_FTM_CHANNEL3,kFTM_EdgeAlignedPwm,0);
	        FTM_UpdatePwmDutycycle(BOARD_FTM_BASEADDR,BOARD_FTM_CHANNEL4,kFTM_EdgeAlignedPwm,0);
	        FTM_UpdatePwmDutycycle(BOARD_FTM_BASEADDR,BOARD_FTM_CHANNEL5,kFTM_EdgeAlignedPwm,u8PWMLevelRight);
	    	break;

	    case MOTOR_eBreakBack:
	    	/* drive Tr0/4 u8PWMLevel%; Tr1/3/5 disable 0%; Tr2 enable 99% */
	    	/**     |--------|--------|                  **/
	    	/**    Tr0(PWM) Tr2(ON)  Tr4(PWM)            **/
	    	/**     |---M1---|---M2---|                  **/
	    	/**    Tr1(OFF) Tr3(OFF) Tr5(OFF)            **/
	    	/**     |--------|--------|                  **/
	        FTM_UpdatePwmDutycycle(BOARD_FTM_BASEADDR,BOARD_FTM_CHANNEL0,kFTM_EdgeAlignedPwm,u8PWMLevelLeft);
	        FTM_UpdatePwmDutycycle(BOARD_FTM_BASEADDR,BOARD_FTM_CHANNEL1,kFTM_EdgeAlignedPwm,0);
	        FTM_UpdatePwmDutycycle(BOARD_FTM_BASEADDR,BOARD_FTM_CHANNEL2,kFTM_EdgeAlignedPwm,99);
	        FTM_UpdatePwmDutycycle(BOARD_FTM_BASEADDR,BOARD_FTM_CHANNEL3,kFTM_EdgeAlignedPwm,0);
	        FTM_UpdatePwmDutycycle(BOARD_FTM_BASEADDR,BOARD_FTM_CHANNEL4,kFTM_EdgeAlignedPwm,u8PWMLevelRight);
	        FTM_UpdatePwmDutycycle(BOARD_FTM_BASEADDR,BOARD_FTM_CHANNEL5,kFTM_EdgeAlignedPwm,0);
	    	break;

	    case MOTOR_eStop:
	    default:
	        FTM_UpdatePwmDutycycle(BOARD_FTM_BASEADDR,BOARD_FTM_CHANNEL0,kFTM_EdgeAlignedPwm,0);
	        FTM_UpdatePwmDutycycle(BOARD_FTM_BASEADDR,BOARD_FTM_CHANNEL1,kFTM_EdgeAlignedPwm,0);
	        FTM_UpdatePwmDutycycle(BOARD_FTM_BASEADDR,BOARD_FTM_CHANNEL2,kFTM_EdgeAlignedPwm,0);
	        FTM_UpdatePwmDutycycle(BOARD_FTM_BASEADDR,BOARD_FTM_CHANNEL3,kFTM_EdgeAlignedPwm,0);
	        FTM_UpdatePwmDutycycle(BOARD_FTM_BASEADDR,BOARD_FTM_CHANNEL4,kFTM_EdgeAlignedPwm,0);
	        FTM_UpdatePwmDutycycle(BOARD_FTM_BASEADDR,BOARD_FTM_CHANNEL5,kFTM_EdgeAlignedPwm,0);
	    	break;
	}
    /* Software trigger to update registers. */
    FTM_SetSoftwareTrigger(BOARD_FTM_BASEADDR, true);
}

