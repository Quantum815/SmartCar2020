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
extern uint8 wireless_rx_buffer[2];

void TwoCarUARTInit(void);
uint8 TwoCarState(void);

#endif /* CODE_INC_USER_TWO_CAR_H_ */
