/*
 * User_Motor.h
 *
 *  Created on: 2020Äê7ÔÂ4ÈÕ
 *      Author: Quantum815
 */

#ifndef CODE_INC_USER_MOTOR_H_
#define CODE_INC_USER_MOTOR_H_

#include "headfile.h"

typedef enum Motor_State
{
    LMotor_F,
    LMotor_B,
    RMotor_F,
	RMotor_B
}Motor_State_t;

void ServoMotorInit(void);
void SetServoPWM(uint8 ServoNum, uint8 PWMDuty);
void MotorInit(void);
void SetMotorPWM(Motor_State_t MotorState, uint8 PWMDuty);
void MotorUserHandle(Motor_State_t Motor, uint8 PWMDuty);

#endif /* CODE_INC_USER_MOTOR_H_ */
