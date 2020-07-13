/*
 * User_OSTU.h
 *
 *  Created on: 2020Äê7ÔÂ6ÈÕ
 *      Author: Quantum815
 */

#ifndef CODE_INC_USER_OSTU_H_
#define CODE_INC_USER_OSTU_H_

#include "headfile.h"

uint16_t GetOSTU(uint8_t tmImage[MT9V03X_H][MT9V03X_W]);
void BinaryImage(uint8_t tmImage[MT9V03X_H][MT9V03X_W],uint8_t ThresholdV);
//void GyroReadByte(void);

#endif /* CODE_INC_USER_OSTU_H_ */
