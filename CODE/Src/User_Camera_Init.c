/*
 * User_Camera_Init.c
 *
 *  Created on: 2020年7月2日
 *      Author: Quantum815
 */

#include "..\CODE\Inc\User_Camera_Init.h"

void UserCameraInit(void)
{
	//LED判断CPU1是否卡死
	gpio_init(P21_4, GPO, 1, PUSHPULL);

	//摄像头进程
	pit_interrupt_ms(CCU6_0, PIT_CH1, CameraProcessTime);

	//各类资源与外设
	mt9v03x_init();

	//测试
	//gpio_init(P20_8, GPO, 1, PUSHPULL);
	DebugUARTInit();  //单核有便可，双核也行
	//ips114_init();  //双核都得有
}

