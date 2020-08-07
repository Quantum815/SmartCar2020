/*
 * User_Encoder.h
 *
 *  Created on: 2020Äê7ÔÂ3ÈÕ
 *      Author: Quantum815
 */

#ifndef CODE_INC_USER_ENCODER_H_
#define CODE_INC_USER_ENCODER_H_

#include "headfile.h"

extern double CurDistance, TotalDistance[10];

void EncoderInit(void);
void CountDistance(void);
double GetDistance(int i);
double GetSpeed(void);
void CleanDistance(void);

#endif /* CODE_INC_USER_ENCODER_H_ */
