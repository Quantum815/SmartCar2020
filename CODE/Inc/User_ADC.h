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
void UpdateADCvalue(void);
//void ADCReadData(void);
int16 ADCValue(uint8 num);

#endif /* CODE_INC_USER_ADC_H_ */
