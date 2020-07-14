/*
 * User_ADC.c
 *
 *  Created on: 2020Äê7ÔÂ14ÈÕ
 *      Author: Quantum815
 */

#include "..\CODE\Inc\User_ADC.h"

static uint16 ADCvalueNum[5];

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
uint16 ADCValue(uint8 num)
{
	if(num > 4)
		return -1;
	return ADCvalueNum[num];
}
