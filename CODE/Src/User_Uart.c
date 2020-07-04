/*
 * User_Uart.c
 *
 *  Created on: 2020Äê7ÔÂ2ÈÕ
 *      Author: Quantum815
 */

#include "..\CODE\Inc\User_Uart.h"

void DebugUARTInit()
{
	uart_init(UART_3, 921600, UART3_TX_P15_6, UART3_RX_P15_7);
}

