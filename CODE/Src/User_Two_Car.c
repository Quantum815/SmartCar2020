/*
 * User_Two_Car.c
 *
 *  Created on: 2020Äê7ÔÂ24ÈÕ
 *      Author: Quantum815
 */

#include "..\CODE\Inc\User_Two_Car.h"

#pragma section all "cpu0_dsram"

uint8 TwoCarReceiveNum;
uint8 TwoCarRxFlag;
uint8 TwoCarRxBuff[2];

#pragma section all restore


void TwoCarUARTInit(void)
{
	seekfree_wireless_init();
}

void TwoCarReadData(void)
{
	static uint8 count = 0;
	while(uart_query(WIRELESS_UART, &TwoCarRxBuff[TwoCarReceiveNum]))
	{
		//uart_putstr(WIRELESS_UART, "test");
		TwoCarReceiveNum++;
		if(TwoCarReceiveNum == 1 && TwoCarRxBuff[0] != 0x01)
			TwoCarReceiveNum = 0;
		if(TwoCarReceiveNum == 2)
		{
			if(TwoCarRxBuff[1] != 0xff)
				TwoCarReceiveNum = 0;
			else
			{
				//uart_putstr(WIRELESS_UART, "success");
				count++;
				TwoCarReceiveNum = 0;
				if(count == 5)
					TwoCarRxFlag = 1;
				break;
			}
		}
	}
}

void TwoCarSendData(uint8 *buff, uint32 len)
{
    if(!gpio_get(RTS_PIN))
    	uart_putbuff(WIRELESS_UART, buff, len);
}

uint8 TwoCarStateJudge(void)
{
	static uint8 count;
	if(TwoCarRxFlag)
	{
		count++;
		TwoCarRxFlag = 0;
		if(count == 5)
		{
			count = 0;
			return 1;
		}
	}
	else
	{
		count--;
		if(count <= 0)
			count = 0;
	}
	return 0;
}
