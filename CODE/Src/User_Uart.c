/*
 * User_Uart.c
 *
 *  Created on: 2020年7月2日
 *      Author: Quantum815
 */

#include "..\CODE\Inc\User_Uart.h"

#pragma section all "cpu0_dsram"

uint8 DebugUartRxBuff;
uint8 GyroUnlockInstruction[5] = {0xff, 0xaa, 0x69, 0x88, 0xb5};  //解锁指令
uint8 GyroAutoCalibration[5] = {0xff, 0xaa, 0x63, 0x00, 0x00};  //陀螺仪自动校准
uint8 GyroKeepConfiguration[5] = {0xff, 0xaa, 0x00, 0x00, 0x00};  //保持配置
uint8 GYRORxBuff[11];
uint8 ReceiveNum=0,gyro_rx_flag=0;
float PitchAngle,RollAngle,YawAngle;
#pragma section all restore

void DebugUARTInit()
{
	uart_init(UART_3, 115200, UART3_TX_P15_6, UART3_RX_P15_7);
}

/*void ADCReadData(void)
{
    uint16 ADCValue, NumLenth = 0, temp;
    uint8 ADCStr[1000];
    ADCValue = adc_convert(ADC_1, ADC1_CH0_A16, ADC_12BIT);
    temp = ADCValue;
    while(temp != 0)
    {
        temp = temp / 10;
        NumLenth++;
    }
    ADCStr[0] = ADCValue + '0';
    uart_putbuff(UART_3, ADCStr, NumLenth);
    uart_putstr(UART_3, "\r\n");
    systick_delay_ms(STM1, 100);
}*/

//debug命令
//0x01 停车  0x02启动   0x03通过串口发送数据回上位机
//0x04 返回当前状态回上位机
void UserDebug(void)
{
	if(DebugUartRxBuff == 0x00)
	{
		FSMEventHandle(&CarFSM, NOEVENT);
	}
    if(DebugUartRxBuff == 0x01)
    {
        FSMEventHandle(&CarFSM, RUNSTOP);
        DebugUartRxBuff = 0x00;
    }
    else if(DebugUartRxBuff == 0x02)
    {
        FSMEventHandle(&CarFSM, RUNSTART);
        DebugUartRxBuff = 0x00;
    }
    else if(DebugUartRxBuff == 0x03)
    {
        if(mt9v03x_finish_flag)
        {
            mt9v03x_finish_flag = 0;
            seekfree_sendimg_03x(UART_0, mt9v03x_image[0], MT9V03X_W, MT9V03X_H);
        }
    }
	else if(DebugUartRxBuff == 0x04)
	{
		if(ReturnFSMState(&CarFSM) == GoLine)
		{
			uart_putstr(UART_0, "GoLine\r\n");
			my_delay(3000000);
		}
		else if(ReturnFSMState(&CarFSM) == Stop)
		{
			uart_putstr(UART_0, "Stop\r\n");
			my_delay(3000000);
		}
		else if(ReturnFSMState(&CarFSM) == SendBall)
		{
			uart_putstr(UART_0, "SendBall\r\n");
			my_delay(3000000);
		}
	}
}

void GyroUARTInit()
{
	uart_init(UART_0, 115200, UART0_TX_P14_0, UART0_RX_P14_1);
	uart_putbuff(UART_0, GyroUnlockInstruction, 5);
	systick_delay_ms(STM1, 100);
	uart_putbuff(UART_0, GyroAutoCalibration, 5);
	systick_delay_ms(STM1, 100);
	uart_putbuff(UART_0, GyroKeepConfiguration, 5);
	systick_delay_ms(STM1, 100);
}

void GyroReadByte()
{
	while(uart_query(UART_0,&GYRORxBuff[ReceiveNum]))
	{

		if(ReceiveNum==0 && GYRORxBuff[0]!=0x55)
			ReceiveNum=0;
		if(ReceiveNum==1 && GYRORxBuff[1]!=0x53)
			ReceiveNum=0;

        if(10 == ReceiveNum)
        {
        	ReceiveNum = 0;
            gyro_rx_flag = 1;
        }
        ReceiveNum++;
	}
/*	switch(GyroRxBuffer[1])
	{
		case 0x50: stcTime.ucYear 		= ucRxBuffer[2];
					stcTime.ucMonth 	= ucRxBuffer[3];
					stcTime.ucDay 		= ucRxBuffer[4];
					stcTime.ucHour 		= ucRxBuffer[5];
					stcTime.ucMinute 	= ucRxBuffer[6];
					stcTime.ucSecond 	= ucRxBuffer[7];
					stcTime.usMiliSecond=((unsigned short)ucRxBuffer[9]<<8)|ucRxBuffer[8];
					break;
		case 0x51:	stcAcc.a[0] = ((unsigned short)ucRxBuffer[3]<<8)|ucRxBuffer[2];
					stcAcc.a[1] = ((unsigned short)ucRxBuffer[5]<<8)|ucRxBuffer[4];
					stcAcc.a[2] = ((unsigned short)ucRxBuffer[7]<<8)|ucRxBuffer[6];
					break;
		case 0x53:	stcAngle.Angle[0] = ((unsigned short)ucRxBuffer[3]<<8)|ucRxBuffer[2];
					stcAngle.Angle[1] = ((unsigned short)ucRxBuffer[5]<<8)|ucRxBuffer[4];
					stcAngle.Angle[2] = ((unsigned short)ucRxBuffer[7]<<8)|ucRxBuffer[6];
					stcAngle.T = ((unsigned short)ucRxBuffer[9]<<8)|ucRxBuffer[8];
					break;
	}*/
}
void GyroCul(void)
{
	uint8_t sum = 0;
    uint32_t temp = 0;
    if(gyro_rx_flag==1)
    {
    sum += GYRORxBuff[0];
    sum += GYRORxBuff[1];
    sum += GYRORxBuff[2];
    sum += GYRORxBuff[3];
    sum += GYRORxBuff[4];
    sum += GYRORxBuff[5];
    sum += GYRORxBuff[6];
    sum += GYRORxBuff[7];
    sum += GYRORxBuff[8];
    sum += GYRORxBuff[9];
    if(sum != GYRORxBuff[10])
    {
        printf("f**k ");
        gyro_rx_flag=0;
        ReceiveNum=0;
    }
    temp = GYRORxBuff[3];
    temp <<= 8;
    temp |= GYRORxBuff[2];

    PitchAngle= (float)temp / (float)32768 * (float)180;

    temp = GYRORxBuff[5];
    temp <<= 8;
    temp |= GYRORxBuff[4];
    RollAngle = (float)temp / (float)32768 * (float)180;

    temp = GYRORxBuff[7];
    temp <<= 8;
    temp |= GYRORxBuff[6];
    YawAngle = (float)temp / (float)32768 * (float)180;
    gyro_rx_flag=0;
    }
}
