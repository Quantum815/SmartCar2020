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
	
	if(time==0)
	{
	ADCvalue[0]=adc_convert(ADC_1, ADC1_CH3_B14);
	ADCvalue[1]=adc_convert(ADC_1, ADC1_CH4_B15);
	ADCvalue[2]=adc_convert(ADC_1, ADC1_CH5_B16);
	ADCvalue[3]=adc_convert(ADC_1, ADC1_CH6_B17);
	ADCvalue[4]=adc_convert(ADC_1, ADC1_CH10_B21);
	time++;	
	}
	else if(time==1)
	{
	ADCvalue[5]=adc_convert(ADC_1, ADC1_CH3_B14);
	ADCvalue[6]=adc_convert(ADC_1, ADC1_CH4_B15);
	ADCvalue[7]=adc_convert(ADC_1, ADC1_CH5_B16);
	ADCvalue[8]=adc_convert(ADC_1, ADC1_CH6_B17);
	ADCvalue[9]=adc_convert(ADC_1, ADC1_CH10_B21);
	ADCvalueNum[0]=(ADCvalue[0]+ADCvalue[5])/2;
	ADCvalueNum[1]=(ADCvalue[1]+ADCvalue[6])/2;
	ADCvalueNum[2]=(ADCvalue[2]+ADCvalue[7])/2;
	ADCvalueNum[3]=(ADCvalue[3]+ADCvalue[8])/2;
	ADCvalueNum[4]=(ADCvalue[4]+ADCvalue[9])/2;
		
	time=0;	
	}
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