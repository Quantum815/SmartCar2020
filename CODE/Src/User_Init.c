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

	//主进程和CPU0的LED
	pit_interrupt_ms(CCU6_0, PIT_CH0, MainProcessTime);
	//距离计算
	pit_interrupt_ms(CCU6_1, PIT_CH0, CountDistanceTime);

	//各类资源与外设
	//ADCInit();
	//DebugUARTInit();
	//EncoderInit();
	//MotorInit();
	GyroUARTInit();
	//ServoMotorInit();
}


