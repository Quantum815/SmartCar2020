#include "User_Uart.h"
uint8 Uart_Send,LaserRecFlag;
uint8 DebugUart_Data,TFminiRx_Data[9],VL53L1RX_Data[7];
uint8 DebugRx_Buffer,TFminiRx_Buffer[9],VL53L1RX_Buffer[7];
lpuart_transfer_t   DebugReceivexfer,GyroReceivexfer,TFminiReceivexfer,VL53L1Receivexfer;
lpuart_handle_t     DebugLpuartHandle,GyroLpuartHandle,TFminiLpuartHandle,VL53L1LpuartHandle;
uint8 AutoCalibration[5] = {0xff,0xaa,0x63,0x00,0x00};
uint8 SaveConfig[5] = {0xff,0xaa,0x00,0x00,0x00};
void DebugUART_CallBack(LPUART_Type *base, lpuart_handle_t *handle, status_t status, void *userData)
{
	  if(kStatus_LPUART_RxIdle == status)
    {
        DebugUart_Data = DebugRx_Buffer;
    }
    
    handle->rxDataSize = DebugReceivexfer.dataSize;
    handle->rxData = DebugReceivexfer.data;
}
//void GyroUART_CallBack(LPUART_Type *base, lpuart_handle_t *handle, status_t status, void *userData)
//{
//	static int temp=0;
//		 if(kStatus_LPUART_RxIdle == status)
//    {

//for(temp = 0;temp<=11;temp++)
//			{
//				GyroUart_Data[temp]=GyroRx_Buffer[temp];
//			}


//    }
//    
//    handle->rxDataSize = GyroReceivexfer.dataSize;
//    handle->rxData = GyroReceivexfer.data;
//}
void DebugUARTInit()
{
	//uint32_t uartClkSrcFreq = BOARD_DebugConsoleSrcFreq();
	//uart_init (USART_1, 115200,UART1_TX_B12,UART1_RX_B13);
	uart_init (USART_3, 115200,UART3_TX_C8,UART3_RX_C9);		
	NVIC_SetPriority(LPUART3_IRQn,1);
	uart_rx_irq(USART_3,1);
	DebugReceivexfer.dataSize =1;
	DebugReceivexfer.data =&DebugRx_Buffer;
	uart_set_handle(USART_3, &DebugLpuartHandle, DebugUART_CallBack, NULL, 0, DebugReceivexfer.data, 1);
	//DbgConsole_Init(USART_1, 115200, BOARD_DEBUG_UART_TYPE, uartClkSrcFreq);
}
//void GyroUartInit(void)
//{
//	uart_init (USART_4, 115200,UART4_TX_C16,UART4_RX_C17);	
//	NVIC_SetPriority(LPUART1_IRQn,3);
//	uart_rx_irq(USART_4,1);
//	GyroReceivexfer.dataSize =11;
//	GyroReceivexfer.data = GyroRx_Buffer;
//	uart_set_handle(USART_4, &GyroLpuartHandle, GyroUART_CallBack, NULL, 0, GyroReceivexfer.data, 11 );
//  uart_putbuff(USART_4,AutoCalibration,5);
//	systick_delay(100);
//	uart_putbuff(USART_4,SaveConfig,5);
//}
void TFminiUartInit(void)
{
		uart_init (USART_3, 115200,UART3_TX_C8,UART3_RX_C9);	
  	NVIC_SetPriority(LPUART3_IRQn,1);
  	uart_rx_irq(USART_3,1);
  	TFminiReceivexfer.dataSize =9;
		TFminiReceivexfer.data = TFminiRx_Buffer;
  	uart_set_handle(USART_3, &TFminiLpuartHandle, TFminiUART_CallBack, NULL, 0, TFminiReceivexfer.data, 9 );
}
void TFminiUART_CallBack(LPUART_Type *base, lpuart_handle_t *handle, status_t status, void *userData)
{
		if(kStatus_LPUART_RxIdle == status)
    {
			for(int i=0;i<9;i++)
        TFminiRx_Data[i] = TFminiRx_Buffer[i];
				LaserRecFlag=1;
    }
    
    handle->rxDataSize = VL53L1Receivexfer.dataSize;
    handle->rxData = VL53L1Receivexfer.data;
}
void VL53L1UartInit(void)
{
		uart_init (USART_1, 115200,UART1_TX_B12,UART1_RX_B13);
  	NVIC_SetPriority(LPUART3_IRQn,0);
  	uart_rx_irq(USART_1,1);
  	VL53L1Receivexfer.dataSize =7;
		VL53L1Receivexfer.data = VL53L1RX_Buffer;
  	uart_set_handle(USART_1, &VL53L1LpuartHandle, VL53L1UART_CallBack, NULL, 0, VL53L1Receivexfer.data, 7 );
}
void VL53L1UART_CallBack(LPUART_Type *base, lpuart_handle_t *handle, status_t status, void *userData)
{
		if(kStatus_LPUART_RxIdle == status)
    {
			for(int i=0;i<7;i++)
			{
        VL53L1RX_Data[i] = VL53L1RX_Buffer[i];
			}
				LaserRecFlag=1;
    }
    
    handle->rxDataSize = VL53L1Receivexfer.dataSize;
    handle->rxData = VL53L1Receivexfer.data;
}
void TwoCarUart(void)
{
	uart_init (USART_8, 115200,UART8_TX_D16,UART8_RX_D17);
}