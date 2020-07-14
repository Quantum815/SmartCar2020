/*
 * User_Gyro_I2C.c
 *
 *  Created on: 2020年7月4日
 *      Author: Quantum815
 */

//目前无法运行
/*#include "..\CODE\Inc\User_Gyro_I2C.h"

#pragma section all "cpu0_dsram"
uint8 GyroPtr[24];
float AX, AY, AZ, Roll_value, Pitch_value, Yaw_value;
#pragma section all restore

short CharToShort(unsigned char cData[])
{
	return ((short)cData[1]<<8)|cData[0];
}

void GyroInit(void)
{
	simiic_init();
}

void GyroReadByte(void)
{
	simiic_read_regs(I2C_ADDR, AX_PTR, GyroPtr, 24, SIMIIC);

	AX = (float)CharToShort(&GyroPtr[0])/32768.0*16;  //x轴角速度
	AY = (float)CharToShort(&GyroPtr[2])/32768.0*16;  //y轴角速度
	AZ = (float)CharToShort(&GyroPtr[4])/32768.0*16;  //z轴角速度

	Roll_value = (float)CharToShort(&GyroPtr[18])/32768.0*180;  //x轴滚动角
	Pitch_value = (float)CharToShort(&GyroPtr[20])/32768.0*180;  //y轴俯仰角
	Yaw_value = (float)CharToShort(&GyroPtr[22])/32768.0*180;  //z轴旋转角
	printf("AX:%f AY:%f AZ:%f \r\nRoll_value:%f Pitch_value:%f Yaw_value:%f\r\n\r\n", AX, AY, AZ, Roll_value, Pitch_value, Yaw_value);
	//uart_putstr(UART_3, "test");
	//uart_putchar(UART_3, Roll_value);
}*/
