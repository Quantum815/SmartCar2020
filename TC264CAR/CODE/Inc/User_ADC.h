/*
 * User_ADC.h
 *
 *  Created on: 2020Äê7ÔÂ14ÈÕ
 *      Author: Quantum815
 */

#ifndef CODE_INC_USER_ADC_H_
#define CODE_INC_USER_ADC_H_

#include "headfile.h"

extern uint16 ADCValue[5];
extern double MidLineFuseNum;

void ADCInit(void);
void UpdateADCValue(void);
int16 ADCValueHandle(uint8 num);
void ADCcalculateMidLine(void);
void ADCcalculateRatioMidLine(void);

#endif /* CODE_INC_USER_ADC_H_ */
