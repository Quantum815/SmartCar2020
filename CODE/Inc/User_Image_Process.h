/*
 * User_Image_Process.h
 *
 *  Created on: 2020Äê7ÔÂ4ÈÕ
 *      Author: Quantum815
 */

#ifndef CODE_INC_USER_IMAGE_PROCESS_H_
#define CODE_INC_USER_IMAGE_PROCESS_H_

#include "headfile.h"

#define CloseThresholds 112
#define FarThresholds 112

double GetMidLineNum(void);
extern uint8 ProcessImageFlag;
extern double MidLineFuseNum;

void ImagePretreatment(void);
void FindMedLine(void);
void CameraProcess(void);
void EdgePointFind(void);
//extern uint8 DisplayIMAG[MT9V03X_H][MT9V03X_W];

#endif /* CODE_INC_USER_IMAGE_PROCESS_H_ */
