/*
 * User_Gyro_Uart.h
 *
 *  Created on: 2020年7月18日
 *      Author: Quantum815
 */

#ifndef CODE_INC_USER_GYRO_UART_H_
#define CODE_INC_USER_GYRO_UART_H_

#include "headfile.h"

void GyroUARTInit(void);
void GyroUARTReadByte(void);
void GyroCalculate(void);
void ManageYawAngle(void);
void GyroYawAngleInit(void);
double GetGyroError(void);  //获取比例误差
double GyroPID(double Kp, double Ki, double Kd);

#endif /* CODE_INC_USER_GYRO_UART_H_ */
