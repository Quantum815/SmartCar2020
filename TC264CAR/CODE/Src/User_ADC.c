/*
 * User_ADC.c
 *
 *  Created on: 2020Äê7ÔÂ14ÈÕ
 *      Author: Quantum815
 */

#include "..\CODE\Inc\User_ADC.h"

#pragma section all "cpu0_dsram"

static uint16 ADCValue[5];

#pragma section all restore


#pragma section all "cpu0_psram"

void ADCInit(void)
{
	adc_init(ADC_0,ADC0_CH0_A0);
	adc_init(ADC_0,ADC0_CH1_A1);
	adc_init(ADC_0,ADC0_CH2_A2);
	adc_init(ADC_0,ADC0_CH3_A3);
	adc_init(ADC_0,ADC0_CH4_A4);
}
void UpdateADCValue(void)
{
	ADCValue[0] = adc_convert(ADC_0, ADC0_CH0_A0, ADC_12BIT);
	ADCValue[1] = adc_convert(ADC_0, ADC0_CH1_A1, ADC_12BIT);
	ADCValue[2] = adc_convert(ADC_0, ADC0_CH2_A2, ADC_12BIT);
	ADCValue[3] = adc_convert(ADC_0, ADC0_CH3_A3, ADC_12BIT);
	ADCValue[4] = adc_convert(ADC_0, ADC0_CH4_A4, ADC_12BIT);
}

int16 ADCValueHandle(uint8 num)
{
	if(num > 4)
		return -1;
	return ADCValue[num];
}

void ADCcalculateMidLine(void)
{
	float Lsqrt, Rsqrt;
	Lsqrt = sqrt(ADCValueHandle(0));
	Rsqrt = sqrt(ADCValueHandle(4));
	if(Lsqrt + Rsqrt == 0)
		MidLineFuseNum = 0;
	else
		MidLineFuseNum = (Lsqrt-Rsqrt)/(ADCValueHandle(0)+ADCValueHandle(4));
	//printf("%lf\r\n", MidLineFuseNum);
}

#pragma section all restore
