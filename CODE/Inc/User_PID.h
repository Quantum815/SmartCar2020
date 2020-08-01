/*
 * User_PID.h
 *
 *  Created on: 2020Äê7ÔÂ8ÈÕ
 *      Author: Quantum815
 */

#ifndef CODE_INC_USER_PID_H_
#define CODE_INC_USER_PID_H_

#include "headfile.h"

double GetPIDValue(double middle, double value, double kP, double kI, double kD);
void CleanPIDValue(void);

#endif /* CODE_INC_USER_PID_H_ */
