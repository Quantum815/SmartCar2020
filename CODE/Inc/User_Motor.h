/*
 * User_Motor.h
 *
 *  Created on: 2020Äê7ÔÂ4ÈÕ
 *      Author: Quantum815
 */

#ifndef CODE_INC_USER_MOTOR_H_
#define CODE_INC_USER_MOTOR_H_

#include "headfile.h"

enum Motor_State
{
    LMotor_F,
    LMotor_B,
    RMotor_F,
	RMotor_B,
};

void ServoMotorInit(void);
void MotorInit(void);
void SetServoPWM(uint8 ServoNum, float PWMDuty);
void SetMotorPWM(uint8 MotorState, float PWMDuty);

#endif /* CODE_INC_USER_MOTOR_H_ */
