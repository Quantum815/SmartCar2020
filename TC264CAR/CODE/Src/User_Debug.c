/*
 * User_Debug.c
 *
 *  Created on: 2020年7月2日
 *      Author: Quantum815
 */

#include "..\CODE\Inc\User_Debug.h"

#pragma section all "cpu0_dsram"

uint8 DebugRxBuff;
uint16 DebugADCValue[5];

#pragma section all restore

void DebugUARTInit(void)
{
	uart_init(UART_3, 115200, UART3_TX_P15_6, UART3_RX_P15_7);
}

//debug命令
//0x01 停车  0x02启动   0x03通过串口发送数据回上位机
//0x04 返回当前状态回上位机
void DebugSend(void)
{
	if(uart_query(UART_3, &DebugRxBuff))
	{
		if(DebugRxBuff == 0x00)
		{
			FSMEventHandle(&CarFSM, NOEVENT);
		}
		if(DebugRxBuff == 0x01)
		{
			FSMEventHandle(&CarFSM, RUNSTOP);
			DebugRxBuff = 0x00;
		}
		else if(DebugRxBuff == 0x02)
		{
			if(mt9v03x_finish_flag)
			{
				seekfree_sendimg_03x(UART_3, mt9v03x_image[0], MT9V03X_W, MT9V03X_H);
				mt9v03x_finish_flag = 0;
			}
			DebugRxBuff = 0x00;
		}
		else if(DebugRxBuff == 0x03)
		{
			if(ReturnFSMState(&CarFSM) == GoLine)
			{
				uart_putstr(UART_3, "GoLine\r\n");
				my_delay(7000000);
			}
			else if(ReturnFSMState(&CarFSM) == Stop)
			{
				uart_putstr(UART_3, "Stop\r\n");
				my_delay(7000000);
			}
			DebugRxBuff = 0x00;
		}
	}
}

void DebugReadParameter(void)
{
	ips114_showfloat(0,0,ADCValueHandle(0),4,6);
	ips114_showfloat(0,1,ADCValueHandle(1),4,6);
	ips114_showfloat(0,2,ADCValueHandle(2),4,6);
	ips114_showfloat(0,3,ADCValueHandle(3),4,6);
	ips114_showfloat(0,4,ADCValueHandle(4),4,6);
	ips114_showfloat(0,5,MidLineFuseNum,4,6);
	ips114_showfloat(120,0,PitchAngle,4,6);
	ips114_showfloat(120,1,RollAngle,4,6);
	ips114_showfloat(120,2,YawAngle,4,6);
	ips114_showfloat(120,4,TotalDistance,4,6);
	ips114_showfloat(120,5,Threshold,4,6);
}
