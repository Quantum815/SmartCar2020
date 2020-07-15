/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：三群：824575535
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		headfile
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		查看doc内version文件 版本说明
 * @Software 		tasking v6.3r1
 * @Target core		TC264D
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-3-23
 ********************************************************************************************************************/
 
#ifndef _headfile_h
#define _headfile_h




#include "SEEKFREE_PRINTF.h"

#include "zf_assert.h"
#include "stdio.h"
#include "math.h"
//官方头文件
#include "ifxAsclin_reg.h"
#include "SysSe/Bsp/Bsp.h"
#include "IfxCcu6_Timer.h"
#include "IfxScuEru.h"

//------逐飞科技单片机外设驱动头文件
#include "zf_gpio.h"
#include "zf_gtm_pwm.h"
#include "zf_uart.h"
#include "zf_ccu6_pit.h"
#include "zf_stm_systick.h"
#include "zf_spi.h"
#include "zf_eru.h"
#include "zf_eru_dma.h"
#include "zf_vadc.h"
#include "zf_gpt12.h"
#include "zf_eeprom.h"

//------逐飞科技产品驱动头文件
#include "SEEKFREE_18TFT.h"
#include "SEEKFREE_FONT.h"
#include "SEEKFREE_FUN.h"
#include "SEEKFREE_IIC.h"
#include "SEEKFREE_IPS114_SPI.h"
#include "SEEKFREE_OLED.h"
#include "SEEKFREE_VIRSCO.h"
#include "SEEKFREE_MT9V03X.h"
#include "SEEKFREE_ICM20602.h"
#include "SEEKFREE_MPU6050.h"
#include "SEEKFREE_MMA8451.h"
#include "SEEKFREE_L3G4200D.h"
#include "SEEKFREE_WIRELESS.h"
#include "SEEKFREE_IPS200_PARALLEL8.h"
#include "SEEKFREE_7725.h"
#include "SEEKFREE_RDA5807.h"

//------自定义头文件
#include <stdint.h>
#include "..\CODE\Inc\User_Init.h"
#include "..\CODE\Inc\User_Camera_Init.h"
#include "..\CODE\Inc\User_Uart.h"
#include "..\CODE\Inc\User_FSM.h"
#include "..\CODE\Inc\User_Encoder.h"
#include "..\CODE\Inc\User_Motor.h"
#include "..\CODE\Inc\User_Gyro_I2C.h"
#include "..\CODE\Inc\User_Image_Process.h"
#include "..\CODE\Inc\User_OSTU.h"
#include "..\CODE\Inc\User_PID.h"
#include "..\CODE\Inc\User_ADC.h"

//------预处理内容
//是否使用摄像头
//#define USECARMERA

//是否使用陀螺仪I2C
//#define USEGYROI2C

//进程中断时间
#define MainProcessTime 10
#define CountDistanceTime 5
#define CameraProcessTime 20

//双核防卡死测试LED中断时间
#define CPU0TIMES (500/MainProcessTime)
#define CPU1TIMES (500/CameraProcessTime)

//车轮直径
#define WHEEL_DIAMETER 62

//车轮启动死区PWM占空比
#define LeftWheelDeadZone 10
#define RightWheelDeadZone 10

//图像处理阈值
#define CloseThresholds 130
#define FarThresholds 130

#endif

