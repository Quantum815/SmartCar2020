/*
 * User_Camera_Init.c
 *
 *  Created on: 2020年7月2日
 *      Author: Quantum815
 */

#include "..\CODE\Inc\User_Camera_Init.h"

void UserCameraInit(void)
{
	#ifdef USECARMERA
	mt9v03x_init();   //初始化摄像头
	#endif

	//LED判断CPU1是否卡死
	gpio_init(P21_4, GPO, 1, PUSHPULL);

	//摄像头进程
	pit_interrupt_ms(CCU6_0, PIT_CH1, CameraProcessTime);
}

