/*
 * User_Gyro_I2C.h
 *
 *  Created on: 2020Äê7ÔÂ4ÈÕ
 *      Author: Quantum815
 */

#ifndef CODE_INC_USER_GYRO_I2C_H_
#define CODE_INC_USER_GYRO_I2C_H_

#include "headfile.h"

#define I2C_ADDR 0x56
#define AX_PTR 0x34

short CharToShort(unsigned char cData[]);
void GyroInit(void);
void GyroReadByte(void);

#endif /* CODE_INC_USER_GYRO_I2C_H_ */
