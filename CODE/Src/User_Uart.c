/*
 * User_Uart.c
 *
 *  Created on: 2020年7月2日
 *      Author: Quantum815
 */

#include "..\CODE\Inc\User_Uart.h"

#pragma section all "cpu0_dsram"

uint8 DebugRxBuff;

uint8 GyroUnlockInstruction[5] = {0xff, 0xaa, 0x69, 0x88, 0xb5};  //解锁指令
uint8 GyroAutoCalibration[5] = {0xff, 0xaa, 0x63, 0x00, 0x00};  //陀螺仪自动校准
uint8 GyroKeepConfiguration[5] = {0xff, 0xaa, 0x00, 0x00, 0x00};  //保持配置
uint8 GyroRxBuff[11];
int8 GyroReceiveNum, GyroRxFlag;
float PitchAngle, RollAngle, YawAngle;

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
			FSMEventHandle(&CarFSM, RUNSTART);
			DebugRxBuff = 0x00;
		}
		else if(DebugRxBuff == 0x03)
		{
			if(mt9v03x_finish_flag)
			{
				seekfree_sendimg_03x(UART_3, mt9v03x_image[0], MT9V03X_W, MT9V03X_H);
				mt9v03x_finish_flag = 0;
			}
		}
		else if(DebugRxBuff == 0x04)
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
		}
	}
}

void GyroUARTInit(void)
{
	uart_init(UART_0, 115200, UART0_TX_P14_0, UART0_RX_P14_1);
	uart_putbuff(UART_0, &GyroUnlockInstruction[0], 5);
	systick_delay_ms(STM1, 100);
	uart_putbuff(UART_0, &GyroAutoCalibration[0], 5);
	systick_delay_ms(STM1, 100);
	uart_putbuff(UART_0, &GyroKeepConfiguration[0], 5);
	systick_delay_ms(STM1, 100);
}

void GyroUARTReadByte(void)
{
	if(uart_query(UART_0, &GyroRxBuff[GyroReceiveNum]))
	{
		if(GyroReceiveNum==0 && GyroRxBuff[0]!=0x55)
			GyroReceiveNum = -1;
		if(GyroReceiveNum==1 && GyroRxBuff[1]!=0x53)
			GyroReceiveNum = -1;

        if(10 == GyroReceiveNum)
        {
        	GyroReceiveNum = -1;
            GyroRxFlag = 1;
        }
        GyroReceiveNum++;
	}
}
void GyroCalculate(void)
{
	uint8 sum = 0;
    uint32 temp = 0;

    if(GyroRxFlag == 1)
    {
		sum += GyroRxBuff[0];
		sum += GyroRxBuff[1];
		sum += GyroRxBuff[2];
		sum += GyroRxBuff[3];
		sum += GyroRxBuff[4];
		sum += GyroRxBuff[5];
		sum += GyroRxBuff[6];
		sum += GyroRxBuff[7];
		sum += GyroRxBuff[8];
		sum += GyroRxBuff[9];
		if(sum != GyroRxBuff[10])
		{
			printf("RECEIVE ERROR!\r\n");
			GyroRxFlag = 0;
			GyroReceiveNum = 0;
			return;
		}
		temp = GyroRxBuff[3];
		temp <<= 8;
		temp |= GyroRxBuff[2];
		PitchAngle= (float)temp / (float)32768 * (float)180;

		temp = GyroRxBuff[5];
		temp <<= 8;
		temp |= GyroRxBuff[4];
		RollAngle = (float)temp / (float)32768 * (float)180;

		temp = GyroRxBuff[7];
		temp <<= 8;
		temp |= GyroRxBuff[6];
		YawAngle = (float)temp / (float)32768 * (float)180;
		GyroRxFlag = 0;
		printf("p=%f,r=%f,y=%f\r\n",PitchAngle,RollAngle,YawAngle);
    }

}
