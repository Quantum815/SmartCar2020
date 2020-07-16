/*
 * User_Uart.h
 *
 *  Created on: 2020Äê7ÔÂ2ÈÕ
 *      Author: Quantum815
 */

#ifndef CODE_INC_USER_UART_H_
#define CODE_INC_USER_UART_H_

#include "headfile.h"

extern uint8 DebugUartRxBuff;

void DebugUARTInit(void);
void DebugSend(void);

void GyroUARTInit(void);
void GyroUARTReadByte(void);
void GyroCalculate(void);
#endif /* CODE_INC_USER_UART_H_ */
