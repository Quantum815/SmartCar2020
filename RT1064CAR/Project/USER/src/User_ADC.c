#include "User_ADC.h"
float_t ADCvalueNum[5];
void ADCinit(void)
{
	adc_init(ADC_1,ADC1_CH3_B14,ADC_12BIT);
	adc_init(ADC_1,ADC1_CH4_B15,ADC_12BIT);
	adc_init(ADC_1,ADC1_CH5_B16,ADC_12BIT);
	adc_init(ADC_1,ADC1_CH6_B17,ADC_12BIT);
	adc_init(ADC_1,ADC1_CH10_B21,ADC_12BIT);
}
void UpdateADCvalue(void)
{
	static uint8 time,ADCvalue[10];
	
	ADCvalueNum[0]=adc_convert(ADC_1, ADC1_CH3_B14);
	ADCvalueNum[1]=adc_convert(ADC_1, ADC1_CH4_B15);
	ADCvalueNum[2]=adc_convert(ADC_1, ADC1_CH5_B16);
	ADCvalueNum[3]=adc_convert(ADC_1, ADC1_CH6_B17);
	ADCvalueNum[4]=adc_convert(ADC_1, ADC1_CH10_B21);

	for(int i=0;i<5;i++)
	{
		if(ADCvalueNum[i]<=20)
		{
			ADCvalueNum[i]=0;
		}
	}
}
float_t ADCvalue(uint8 num)
{
	if(num>4)
		return -1;
	return ADCvalueNum[num];
}