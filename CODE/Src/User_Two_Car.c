/*
 * User_Two_Car.c
 *
 *  Created on: 2020Äê7ÔÂ24ÈÕ
 *      Author: Quantum815
 */

#include "..\CODE\Inc\User_Two_Car.h"

void TwoCarUARTInit(void)
{
	seekfree_wireless_init();
}

uint8 TwoCarState(void)
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
