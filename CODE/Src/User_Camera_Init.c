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

	//pit_interrupt_ms(CCU6_0, PIT_CH1, 20);//摄像头进程20ms，注释
	gpio_init(P21_4, GPO, 1, PUSHPULL);//LED初始化CPU1
	pit_interrupt_ms(CCU6_1, PIT_CH1, 500);//LED判断CPU1是否卡死500ms

	//scc8660_csi_init(); //自动曝光on TC264不支持
}

