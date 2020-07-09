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

void SetServoPWM(uint8 ServoNum, float PWMDuty)  //PWMDuty为百分比
{
	double PWMCount = 0;
	PWMCount = GTM_ATOM0_PWM_DUTY_MAX * (PWMDuty/100);
	switch(ServoNum)
	{
		case 1: pwm_duty(ATOM0_CH0_P21_2,(uint32)PWMCount); break;
		case 2: pwm_duty(ATOM0_CH1_P21_3,(uint32)PWMCount); break;
	}
}

void MotorInit(void)
{
	gtm_pwm_init(ATOM1_CH4_P02_4 , 2000, 45000);
	gtm_pwm_init(ATOM1_CH5_P02_5 , 2000, 5000);
	gtm_pwm_init(ATOM1_CH6_P02_6 , 2000, 45000);
	gtm_pwm_init(ATOM1_CH7_P02_7 , 2000, 5000);
}

void SetMotorPWM(Motor_State_t MotorState, float PWMDuty)  //已经过驱动板测试，暂时不用更改
{
	double PWMCount = 0;
	PWMCount = GTM_ATOM1_PWM_DUTY_MAX * (PWMDuty / 100);
	switch(MotorState)
	{
		case LMotor_F: pwm_duty(ATOM1_CH5_P02_5, (uint32)PWMCount); break;
		case LMotor_B: pwm_duty(ATOM1_CH6_P02_6, (uint32)PWMCount); break;
		case RMotor_F: pwm_duty(ATOM1_CH4_P02_4, (uint32)PWMCount); break;
		case RMotor_B: pwm_duty(ATOM1_CH7_P02_7, (uint32)PWMCount); break;
	}
}

