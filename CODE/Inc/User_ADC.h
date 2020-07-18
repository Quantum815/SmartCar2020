/*
 * User_ADC.h
 *
 *  Created on: 2020Äê7ÔÂ14ÈÕ
 *      Author: Quantum815
 */

#ifndef CODE_INC_USER_ADC_H_
#define CODE_INC_USER_ADC_H_

#include "headfile.h"

void ADCInit(void);
void UpdateADCValue(void);
int16 ADCValueHandle(uint8 num);

#endif /* CODE_INC_USER_ADC_H_ */
