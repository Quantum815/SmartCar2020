/*
 * User_Init.c
 *
 *  Created on: 2020年7月2日
 *      Author: Quantum815
 */

#include "..\CODE\Inc\User_Init.h"

void UserInit(void)
{
	pit_interrupt_ms(CCU6_0, PIT_CH0, 20);//主进程20ms
	//adc_init(ADC_1,ADC1_CH3_B14,ADC_8BIT);
	//DebugUARTInit();
	gpio_init(P20_9, GPO, 0, PUSHPULL);//LED初始化CPU0
	pit_interrupt_ms(CCU6_1, PIT_CH0, 500);//LED判断CPU0是否卡死500ms
}


