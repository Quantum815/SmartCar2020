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

	//主进程
	pit_interrupt_ms(CCU6_0, PIT_CH0, MainProcessTime);
	//计算
	pit_interrupt_ms(CCU6_1, PIT_CH0, CalculationTime);

	//各类资源与外设
	TwoCarUARTInit();
	ADCInit();
	GyroUARTInit();
	EncoderInit();
	MotorInit();
	RunStop();
	CleanDistance();
	CleanPIDValue();

	//测试
	gpio_init(P21_5, GPO, 1, PUSHPULL);
	DebugUARTInit();
	ips114_init();
}


