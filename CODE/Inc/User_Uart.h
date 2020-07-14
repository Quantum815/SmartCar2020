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

void DebugUARTInit();
//void ADCReadData(void);
void UserDebug(void);

void GyroUARTInit();
void GyroReadByte();

#endif /* CODE_INC_USER_UART_H_ */
