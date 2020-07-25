/*
 * User_Init.c
 *
 *  Created on: 2020年7月2日
 *      Author: Quantum815
 */

#include "..\CODE\Inc\User_Init.h"

void UserInit(void)
{
	//LED判断CPU0是否卡死
	gpio_init(P20_9, GPO, 0, PUSHPULL);
	pit_interrupt_ms(CCU6_1, PIT_CH1, LED0Time);

	//主进程和CPU0
	pit_interrupt_ms(CCU6_0, PIT_CH0, MainProcessTime);
	//距离计算
	pit_interrupt_ms(CCU6_1, PIT_CH0, CountDistanceTime);

	//各类资源与外设
	ADCInit();
	EncoderInit();
	MotorInit();
	//TwoCarUARTInit();
	GyroUARTInit();
	//MotorUserHandle(LMotor_F, 30);
	//MotorUserHandle(LMotor_B, 30);
	//MotorUserHandle(RMotor_F, 30);
	//MotorUserHandle(RMotor_B, 30);
	CleanDistance();
	GyroYawAngleInit();

	//测试
	//DebugUARTInit();
	ips114_init();
}


