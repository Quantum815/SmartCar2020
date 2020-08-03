#ifndef _USER_ADC
#define _USER_ADC
#include "headfile.h"
void ADCinit(void);
void UpdateADCvalue(void);
float_t ADCvalue(uint8 num);
#endif