
#ifndef MOTORS_H_
#define MOTORS_H_

/*! @brief FTM PWM operation modes */
typedef enum
{
    MOTOR_eMoveForward = 1U, /*!< move forward */
	MOTOR_eBreakForward,     /*!< break forward */
	MOTOR_eMoveBack,         /*!< move back */
	MOTOR_eBreakBack,        /*!< break back */
	MOTOR_eStop              /*!< stop */
} MOTOR_eMotorsOrders;

/** init FTM component to control two DC motors on BL bridge */
void MOTORS_Initialization(void);

/** drive FTM to control two DC motors */
void MOTORS_UpdateCommand(MOTOR_eMotorsOrders eMotorCommand, uint8_t u8PWMLevelLeft, uint8_t u8PWMLevelRight);

#endif /* MOTORS_H_ */
