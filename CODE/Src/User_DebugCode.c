/*
 * User_DebugCode.c
 *
 *  Created on: 2020年7月3日
 *      Author: Quantum815
 */

#include "..\CODE\Inc\User_DebugCode.h"

uint8 DebugUartRxBuff;

//debug命令
//0x01 停车  0x02启动   0x03通过串口发送数据回上位机
//0x04 返回当前状态回上位机
void UserDebug(void)
{
    if(DebugUartRxBuff == 0x01)
    {
        FSMEventHandle(&CarFSM, RUNSTOP);
    }
    else if(DebugUartRxBuff == 0x02)
    {
        FSMEventHandle(&CarFSM, RUNSTART);
    }
    else if(DebugUartRxBuff == 0x03)
    {
        if(mt9v03x_finish_flag)
        {
            mt9v03x_finish_flag = 0;
            seekfree_sendimg_03x(UART_0, mt9v03x_image[0], MT9V03X_W, MT9V03X_H);
        }
    }
	else if(DebugUartRxBuff == 0x04)
	{
		if(ReturnFSMState(&CarFSM) == GoLine)
		{
			uart_putstr(UART_0, "Goline\r\n");
			my_delay(20000000);
		}
		else if(ReturnFSMState(&CarFSM) == Stop)
		{
			uart_putstr(UART_0, "Stop\r\n");
			my_delay(20000000);
		}
		else if(ReturnFSMState(&CarFSM) == SendBall)
		{
			uart_putstr(UART_0, "SendBall\r\n");
			my_delay(20000000);
		}
	}
}
