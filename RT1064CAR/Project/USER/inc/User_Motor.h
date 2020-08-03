#ifndef _SENDBALL_H
#define _SENDBALL_H
#include "headfile.h"
typedef enum 
{
    LMotor_F,
    LMotor_B,
    RMotor_F,
		RMotor_B,
} Motor_State;
void ServoMotorInit(void);
void MotorInit(void);
void SetServoPWM(uint8 ServoNum,float PWNDuty);
void SetMotorPWM(Motor_State Motor,float PWNDuty);
void MotorUserHandle(Motor_State Motor,float PWNDuty);
#endif