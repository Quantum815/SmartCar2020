/*
 * User_Gyro_I2C.h
 *
 *  Created on: 2020年7月4日
 *      Author: Quantum815
 */

//目前无法运行
#ifndef CODE_INC_USER_GYRO_I2C_H_
#define CODE_INC_USER_GYRO_I2C_H_

#include "headfile.h"

#ifdef USEGYROI2C

#define I2C_ADDR 0x56
#define AX_PTR 0x34

short CharToShort(unsigned char cData[]);
void GyroInit(void);
void GyroI2CReadByte(void);

#endif /* CODE_INC_USER_GYRO_I2C_H_ */

#endif
