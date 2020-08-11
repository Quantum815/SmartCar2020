#include "DebugCode.h"
void ADCreadData(void)
{
    uint16 adc_value[5], NumLenth = 0, temp[5];
    //uint8 adc_str[1000];
    adc_value[0] = adc_convert(ADC_1, ADC1_CH3_B14);
		adc_value[1] = adc_convert(ADC_1, ADC1_CH4_B15);
		adc_value[2] = adc_convert(ADC_1, ADC1_CH5_B16);
		adc_value[3] = adc_convert(ADC_1, ADC1_CH6_B17);
		adc_value[4] = adc_convert(ADC_1, ADC1_CH10_B21);
//		for(int i=0;i<=4;i++)
//	{
//		PRINTF("%d     ",adc_value[i]);
//		//ips114_showfloat(100,0,adc_value[i],4,4);
//    
//	}
//	PRINTF("\r\n");
	//systick_delay_ms(10);
}
////////在这里定义相关的debug命令////////////
//
//0x01 停车 0x02启动  0x03通过串口发送数据回电脑 0x04通过usb-cdc发送数据回电脑
//0x05 返回当前状态回上位机
//
/////////////////////////////////////////////
void UserDebug(void)
{
    if(DebugRx_Buffer == 0x01)
    {
			StopRunAndProgram();
        //FSM_EventHandle(&Car_Fsm, RUNSTOP);
				DebugRx_Buffer = 0x00;
    }
    else if(DebugRx_Buffer == 0x02)
    {
        FSM_EventHandle(&Car_Fsm, RUNSTART);
				DebugRx_Buffer = 0x00;
    }
		 else if(DebugRx_Buffer == 0x00)
    {
        FSM_EventHandle(&Car_Fsm, NOTHING);
				//DebugRx_Buffer = 0x00;
    }
    else if(DebugRx_Buffer == 0x03)
    {
        if(mt9v03x_csi_finish_flag)
        {
            mt9v03x_csi_finish_flag = 0;
						//csi_seekfree_sendimg_03x_m(USART_1);
            csi_seekfree_sendimg_03x(USART_1, mt9v03x_csi_image[0], MT9V03X_CSI_W, MT9V03X_CSI_H);
        }
    }
    else if(DebugRx_Buffer == 0x04)
    {
        if(mt9v03x_csi_finish_flag)
        {
            mt9v03x_csi_finish_flag = 0;
            seekfree_sendimg_03x_usb_cdc(mt9v03x_csi_image[0], MT9V03X_CSI_W, MT9V03X_CSI_H);

        }
    }
		else if(DebugRx_Buffer == 0x05)
		{
			if(ReturnFSMState(&Car_Fsm) == GoLine)
			{
				uart_putstr(USART_1,"Goline\r\n");
				my_delay(20000000);
			}
			else if(ReturnFSMState(&Car_Fsm) == Stop)
			{
				uart_putstr(USART_1,"Stop\r\n");
				my_delay(20000000);
			}
			else if(ReturnFSMState(&Car_Fsm) == SendBall)
			{
				uart_putstr(USART_1,"SendBall\r\n");
				my_delay(20000000);
			}
		}
}
void StopRunAndProgram(void)
{
	MotorUserHandle(LMotor_F,0);
	MotorUserHandle(RMotor_F,0);
while(1);
}
void ShowNUMinDisplay(void)
{
			ips114_showfloat(0,0,ADCvalue(0),4,6);
			ips114_showfloat(0,1,ADCvalue(1),4,6);
			ips114_showfloat(0,2,ADCvalue(2),4,6);
			ips114_showfloat(0,3,ADCvalue(3),4,6);
			ips114_showfloat(0,4,ADCvalue(4),4,6);
			ips114_showfloat(0,5,MidLineFuseNum,4,6);
			//systick_delay_ms(100);
}