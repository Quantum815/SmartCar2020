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
	pit_interrupt_ms(CCU6_1, PIT_CH0, CPU0TestTime);

	//主进程
	pit_interrupt_ms(CCU6_0, PIT_CH0, MainProcessTime);

	//各类资源与外设
	//adc_init(ADC_1,ADC1_CH3_B14,ADC_8BIT);  //需要修改

	//DebugUARTInit();
	//EncoderInit();
	//ServoMotorInit();
	//MotorInit();
	//GyroInit();
	//ips114_init();
}


