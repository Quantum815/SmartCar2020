/*
 * User_Two_Car.h
 *
 *  Created on: 2020Äê7ÔÂ24ÈÕ
 *      Author: Quantum815
 */

#ifndef CODE_INC_USER_TWO_CAR_H_
#define CODE_INC_USER_TWO_CAR_H_

#include "headfile.h"

extern uint8 TwoCarRxFlag;

void TwoCarUARTInit(void);
void TwoCarReadData(void);
void TwoCarSendData(uint8 *buff, uint32 len);
uint8 TwoCarStateJudge(void);

#endif /* CODE_INC_USER_TWO_CAR_H_ */
