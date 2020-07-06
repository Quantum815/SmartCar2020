/*
 * User_OSTU.h
 *
 *  Created on: 2020年7月6日
 *      Author: Quantum815
 */

#ifndef CODE_INC_USER_OSTU_H_
#define CODE_INC_USER_OSTU_H_

#include "headfile.h"

#define IMAGEH  MT9V03X_H //行 HEIGHT
#define IMAGEW  MT9V03X_W  //列 WIDTH

uint8_t GetOSTU(uint8_t tmImage[IMAGEH][IMAGEW]);
void BinaryImage(uint8_t tmImage[IMAGEH][IMAGEW],uint8_t ThresholdV);
void GyroReadByte(void);

#endif /* CODE_INC_USER_OSTU_H_ */
