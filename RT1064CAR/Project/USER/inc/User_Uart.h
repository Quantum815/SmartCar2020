#ifndef UART_H
#define UART_H
#include "headfile.h"
void GyroUART_CallBack(LPUART_Type *base, lpuart_handle_t *handle, status_t status, void *userData);
void DebugUART_CallBack(LPUART_Type *base, lpuart_handle_t *handle, status_t status, void *userData);
void TFminiUART_CallBack(LPUART_Type *base, lpuart_handle_t *handle, status_t status, void *userData);
void VL53L1UART_CallBack(LPUART_Type *base, lpuart_handle_t *handle, status_t status, void *userData);
void DebugUARTInit(void);
void GyroUartInit(void);
void TFminiUartInit(void);
void TwoCarUart(void);
void VL53L1UartInit(void);
extern uint8 DebugRx_Buffer,TFminiRx_Data[9],LaserRecFlag,VL53L1RX_Data[7];

#endif