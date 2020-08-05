/*
 * User_Two_Car.c
 *
 *  Created on: 2020ƒÍ7‘¬24»’
 *      Author: Quantum815
 */

#include "..\CODE\Inc\User_Two_Car.h"

#pragma section all "cpu0_dsram"

uint8 TwoCarReceiveNum;
uint8 TwoCarRxFlag;
uint8 TwoCarRxBuff[2];

#pragma section all restore


#pragma section all "cpu0_psram"

void TwoCarUARTInit(void)
{
	seekfree_wireless_init();
}

void TwoCarReadData(void)
{
	static uint8 count = 0;
	while(uart_query(WIRELESS_UART, &TwoCarRxBuff[TwoCarReceiveNum]))
	{
		uart_putchar(WIRELESS_UART, 0x00);  //≤‚ ‘
		TwoCarReceiveNum++;
		if(TwoCarReceiveNum == 1 && TwoCarRxBuff[0] != 0x01)
			TwoCarReceiveNum = 0;
		if(TwoCarReceiveNum == 2)
		{
			if(TwoCarRxBuff[1] != 0xff)
				TwoCarReceiveNum = 0;
			else
			{
				uart_putchar(WIRELESS_UART, 0xff);  //≤‚ ‘
				count++;
				TwoCarReceiveNum = 0;
				if(count == 3)
				{
					TwoCarRxFlag = 1;
					gpio_set(P21_5, 0);  //≤‚ ‘
				}
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

#pragma section all restore
