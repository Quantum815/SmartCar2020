/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：三群：824575535
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		main
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		查看doc内version文件 版本说明
 * @Software 		tasking v6.3r1
 * @Target core		TC264D
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-3-23
 ********************************************************************************************************************/


#include "headfile.h"
#pragma section all "cpu0_dsram"
//将本语句与#pragma section all restore语句之间的全局变量都放在CPU0的RAM中
uint8 x;
#pragma section all restore

//工程导入到软件之后，应该选中工程然后点击refresh刷新一下之后再编译
//工程默认设置为关闭优化，可以自己右击工程选择properties->C/C++ Build->Setting
//然后在右侧的窗口中找到C/C++ Compiler->Optimization->Optimization level处设置优化等级
//一般默认新建立的工程都会默认开2级优化，因此大家也可以设置为2级优化

//对于TC系列默认是不支持中断嵌套的，希望支持中断嵌套需要在中断内使用enableInterrupts();来开启中断嵌套
//简单点说实际上进入中断后TC系列的硬件自动调用了disableInterrupts();来拒绝响应任何的中断，因为需要我们自己手动调用enableInterrupts();来开启中断的响应。

#pragma section all "cpu0_psram"

void core0_main(void)
{
	get_clk();//获取时钟频率  务必保留

	//用户在此处调用各种初始化函数等
    //UserInit();
	TwoCarUARTInit();
    gpio_init(P21_4, GPO, 1, PUSHPULL);
    gpio_init(P21_5, GPO, 1, PUSHPULL);
	enableInterrupts();

	while (TRUE)
	{
		if(TwoCarRxFlag == 1)
			gpio_set(P21_4, 0);
		else
			gpio_set(P21_5, 0);
    	//seekfree_sendimg_03x(UART_3, *mt9v03x_image[MT9V03X_H], MT9V03X_W, MT9V03X_H);
		//ips114_showfloat(0,0,2.222,4,4);
		//FindLine();
		//GyroI2CReadByte();
		//for(int i =0;i<=10;i++)
		//printf("%d   ",GYRORxBuff[i]);
		//printf("\r\n");
		//systick_delay_ms(STM0, 100);
		//UpdateADCValue();
		//DebugReadADCData();
		//GyroUARTReadByte();
		//CountDistance();
		//GyroCalculate();
    	//ADCcalculateMidLine();
    	//systick_delay_ms(STM0, 20);
    	//CountDistance();


		//ips114_showchar(50,50,'t');
		//MotorUserHandle(RMotor_B, 00);
		//MotorUserHandle(LMotor_F, 20);
		///systick_delay_ms(STM0, 2000);
		//MotorUserHandle(LMotor_F, 10);
		//MotorUserHandle(LMotor_B, 20);
		//systick_delay_ms(STM0, 2000);
		//MotorUserHandle(LMotor_B, 0);
		//MotorUserHandle(RMotor_F, 7.2);
		///systick_delay_ms(STM0, 2000);
		//MotorUserHandle(RMotor_F, 0);
		//MotorUserHandle(RMotor_B, 20);
		//systick_delay_ms(STM0, 2000);
		//uart_putstr(UART_0, "xxxxx");
	}
}

#pragma section all restore


