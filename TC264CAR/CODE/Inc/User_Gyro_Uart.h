/*
 * User_Gyro_Uart.h
 *
 *  Created on: 2020年7月18日
 *      Author: Quantum815
 */

#ifndef CODE_INC_USER_GYRO_UART_H_
#define CODE_INC_USER_GYRO_UART_H_

#include "headfile.h"

extern double PitchAngle, RollAngle, YawAngle, TargetGyroYawAngle;

void GyroUARTInit(void);
void GyroUARTReadByte(void);
void GyroCalculate(void);
void ManageYawAngle(void);
void GyroYawAngleInit(double RotationAngle);
double GetGyroError(void);  //获取比例误差
void GyroPID(double Kp, double Ki, double Kd);
double CulAngle(void);
void InitCulAngle(void);
void UpdateCulAngle(void);
double GetGYROCulError(void);
#endif /* CODE_INC_USER_GYRO_UART_H_ */
