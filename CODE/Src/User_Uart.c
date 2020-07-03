/*
 * User_Uart.c
 *
 *  Created on: 2020Äê7ÔÂ2ÈÕ
 *      Author: Quantum815
 */

#include "..\CODE\Inc\User_Uart.h"

uint8 uartBuff;

void DebugUARTInit()
{
	uart_init(UART_3, 921600, UART3_TX_P15_6, UART3_RX_P15_7);
}

void DebugUARTCallBack(LPUART_Type *base, lpuart_handle_t *handle, status_t status, void *userData)
{
	  if(kStatus_LPUART_RxIdle == status)
    {
        Uart_Data = Rx_Buffer;
    }

    handle->rxDataSize = Receivexfer.dataSize;
    handle->rxData = Receivexfer.data;
}
