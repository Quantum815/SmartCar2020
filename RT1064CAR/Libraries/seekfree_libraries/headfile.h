/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2019,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ��һȺ��179029047(����)  ��Ⱥ��244861897
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ����������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file       		headfile
 * @company	   		�ɶ���ɿƼ����޹�˾
 * @author     		��ɿƼ�(QQ3184284598)
 * @version    		�鿴doc��version�ļ� �汾˵��
 * @Software 		IAR 8.3 or MDK 5.28
 * @Target core		NXP RT1064DVL6A
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2019-04-30
 ********************************************************************************************************************/
 
#ifndef _headfile_h
#define _headfile_h


#include <stdint.h>
#include "fsl_common.h"

#include "fsl_debug_console.h"
#include "fsl_iomuxc.h"
#include "fsl_pit.h"

#include "board.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "fsl_cache.h"
#include "common.h"
#include "zf_vector.h"

//------�ļ�ϵͳ���ͷ�ļ�
#include "ff.h"
#include "diskio.h"
#include "fsl_sd_disk.h"

#include "SEEKFREE_PRINTF.h"


//------��ɿƼ���Ƭ����������ͷ�ļ�
#include "zf_gpio.h"
#include "zf_iomuxc.h"
#include "zf_pit.h"
#include "zf_pwm.h"
#include "zf_uart.h"
#include "zf_spi.h"
#include "zf_systick.h"
#include "zf_qtimer.h"
#include "zf_adc.h"
#include "zf_iic.h"
#include "zf_flash.h"
#include "zf_camera.h"
#include "zf_csi.h"
#include "zf_rom_api.h"
#include "zf_usb_cdc.h"
#include "zf_sdcard.h"

//------��ɿƼ���Ʒ����ͷ�ļ�
#include "SEEKFREE_FONT.h"
#include "SEEKFREE_18TFT.h"
#include "SEEKFREE_IPS114_SPI.h"
#include "SEEKFREE_IPS200_PARALLEL8.h"
#include "SEEKFREE_IIC.h"
#include "SEEKFREE_VIRSCO.h"
#include "SEEKFREE_FUN.h"
#include "SEEKFREE_MPU6050.h"
#include "SEEKFREE_OLED.h"
#include "SEEKFREE_NRF24L01.h"
#include "SEEKFREE_MMA8451.h"
#include "SEEKFREE_L3G4200D.h"
#include "SEEKFREE_ICM20602.h"
#include "SEEKFREE_MT9V03X.h"
#include "SEEKFREE_WIRELESS.h"
#include "SEEKFREE_MT9V03X_CSI.h"
#include "SEEKFREE_W25QXXJV.h"
#include "SEEKFREE_SCC8660_CSI.h"
#include "SEEKFREE_SCC8660.h"
//******************own file**********************//
//#define USECARMER
#define HARDSPI
extern int RTIME;
#include "arm_math.h"
#include "User_Decode.h"
#include "User_init.h"
#include "User_fsm.h"
#include "User_ImageProcess.h"
#include "User_Uart.h"
#include "DebugCode.h"
#include "User_Motor.h"
#include "User_Gyro_IIC.h"
#include "User_Gyro_UART.h"
#include "isr.h"
#include "User_PID.h"
#include "User_OSTU.h"
#include "User_ADC.h"
#include "User_SuperSonic.h"
#include "User_TFmini.h"
#include "User_VL53L1.h"
//******************需要调整的参数**********************//

//FindLine函数的pid参数
#define FidLP 25
#define FidLI 0.2
#define FidLD 4000
#define FuseMidLine -0.002763617550954
//出库相关参数
#define AntiWay 0 //出库方向 0左 1右
#define StraightLineOutGarage 0.12 //出库前直行距离
//出库直行陀螺仪pid
#define OutGarageGyroKpStraightLineKP 25
#define OutGarageGyroKpStraightLineKI 0.1
#define OutGarageGyroKpStraightLineKD 98
//出库转弯陀螺仪pid
#define OutGarageGyroKpCStraightLineKP 50
#define OutGarageGyroKpCStraightLineKI 0.1
#define OutGarageGyroKpCStraightLineKD 95
//环岛判别条件
#define ADCvalueC 2500 //入圆时中心电感值
#define ADCvalueCL 2500 //入圆时左斜电感值
#define ADCvalueCR 2500//入圆时右斜电感值
#define ADCvalueLL 2400//入圆时最左侧电感值
#define ADCvalueRR 2400// 入圆时最右侧电感值
//入圆相关参数
#define InRAngle 10 //入左圆角度
#define SpeedDownInAngle -13 //入圆减速pwm
#define StraightLineInRA 0.2 //入圆时直行距离 这个值必须大于0.2且小于GYROLineInRA
#define SpeedStraightInRA 8.5 //入圆时直行时的基础速度
#define CSpeedStraightInRA 1.5 //入左圆时差速
#define GYROLineInRA 0.4 //入圆时陀螺仪走的距离 这个值必须小于0.8
/*入圆时转向PID参数*/
#define InRAGyroKp 105
#define InRAGyroKi 0
#define InRAGyroKd 200
//出圆相关参数
#define OutRALeftAngle 30 //出左圆时的偏角度
#define SpeedDownOutAngle -13 //出圆减速pwm
#define GYROLineOutRA 0.6 //出圆陀螺仪走的距离
//出圆陀螺仪PID
#define OutRAGyroKp 105
#define OutRAGyroKi 0
#define OutRAGyroKd 200
#endif

