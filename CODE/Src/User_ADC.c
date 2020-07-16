/*
 * User_ADC.c
 *
 *  Created on: 2020Äê7ÔÂ14ÈÕ
 *      Author: Quantum815
 */

#include "..\CODE\Inc\User_ADC.h"

#pragma section all "cpu0_dsram"

static uint16 ADCvalueNum[5];

#pragma section all restore

void ADCInit(void)
{
	adc_init(ADC_0,ADC0_CH0_A0);
	adc_init(ADC_0,ADC0_CH1_A1);
	adc_init(ADC_0,ADC0_CH2_A2);
	adc_init(ADC_0,ADC0_CH3_A3);
	adc_init(ADC_0,ADC0_CH4_A4);
}
void UpdateADCvalue(void)
{
	ADCvalueNum[0]=adc_convert(ADC_0, ADC0_CH0_A0, ADC_12BIT);
	ADCvalueNum[1]=adc_convert(ADC_0, ADC0_CH1_A1, ADC_12BIT);
	ADCvalueNum[2]=adc_convert(ADC_0, ADC0_CH2_A2, ADC_12BIT);
	ADCvalueNum[3]=adc_convert(ADC_0, ADC0_CH3_A3, ADC_12BIT);
	ADCvalueNum[4]=adc_convert(ADC_0, ADC0_CH4_A4, ADC_12BIT);
}

/*void ADCReadData(void)
{
    uint16 ADCValue;
    ADCValue = adc_convert(ADC_1, ADC1_CH0_A16, ADC_12BIT);
    temp = ADCValue;
    while(temp != 0)
    {
        temp = temp / 10;
        NumLenth++;
    }
    ADCStr[0] = ADCValue + '0';
    uart_putbuff(UART_3, ADCStr, NumLenth);
    uart_putstr(UART_3, "\r\n");
    systick_delay_ms(STM1, 100);
}*/

int16 ADCValue(uint8 num)
{
	if(num > 4)
		return -1;
	return ADCvalueNum[num];
}
