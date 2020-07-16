/*
 * User_Motor.c
 *
 *  Created on: 2020年7月4日
 *      Author: Quantum815
 */

#include "..\CODE\Inc\User_Motor.h"

void ServoMotorInit(void)
{
	gtm_pwm_init(ATOM0_CH0_P21_2, 50, 5000);
	gtm_pwm_init(ATOM0_CH1_P21_3, 50, 5000);
}

void SetServoPWM(uint8 ServoNum, uint8 PWMDuty)  //PWMDuty为百分比
{
	uint32 PWMCount = 0;
	PWMCount = GTM_ATOM0_PWM_DUTY_MAX * (PWMDuty/100);
	switch(ServoNum)
	{
		case 1: pwm_duty(ATOM0_CH0_P21_2, PWMCount); break;
		case 2: pwm_duty(ATOM0_CH1_P21_3, PWMCount); break;
	}
}

void MotorInit(void)
{
	gtm_pwm_init(ATOM1_CH5_P02_5 , 8000, 25000);
	gtm_pwm_init(ATOM1_CH6_P02_6 , 8000, 25000);
	gtm_pwm_init(ATOM1_CH4_P02_4 , 8000, 25000);
	gtm_pwm_init(ATOM1_CH7_P02_7 , 8000, 25000);
}

void SetMotorPWM(Motor_State_t MotorState, uint8 PWMDuty)  //已经过驱动板测试，暂时不用更改
{
	uint32 PWMCount = 0;
	PWMCount = GTM_ATOM1_PWM_DUTY_MAX * (PWMDuty / 100);
	switch(MotorState)
	{
		case LMotor_F: pwm_duty(ATOM1_CH5_P02_5, PWMCount); break;
		case LMotor_B: pwm_duty(ATOM1_CH6_P02_6, PWMCount); break;
		case RMotor_F: pwm_duty(ATOM1_CH4_P02_4, PWMCount); break;
		case RMotor_B: pwm_duty(ATOM1_CH7_P02_7, PWMCount); break;
	}
}

void MotorUserHandle(Motor_State_t Motor, uint8 PWMDuty)
{
    if(Motor == LMotor_F)
    {
		SetMotorPWM(LMotor_B, 0);
		SetMotorPWM(LMotor_F, PWMDuty);
    }
    else if(Motor == LMotor_B)
    {
		SetMotorPWM(LMotor_F, 0);
		SetMotorPWM(LMotor_B, PWMDuty);
    }
    else if(Motor == RMotor_F)
    {
		SetMotorPWM(RMotor_B, 0);
		SetMotorPWM(RMotor_F, PWMDuty);

    }
    else if(Motor == RMotor_B)
    {
		SetMotorPWM(RMotor_F, 0);
		SetMotorPWM(RMotor_B, PWMDuty);
    }
}

