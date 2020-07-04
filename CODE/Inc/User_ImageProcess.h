/*
 * User_ImageProcess.h
 *
 *  Created on: 2020Äê7ÔÂ4ÈÕ
 *      Author: Quantum815
 */

#ifndef CODE_INC_USER_IMAGEPROCESS_H_
#define CODE_INC_USER_IMAGEPROCESS_H_

#include "headfile.h"
#include "User_fsm.h"

#define CloseThresholds 112
#define FarThresholds 112

void ImagePretreatment(void);
void FindMidLine(void);
void CameraProcess(void);
extern uint8 ProcessImageFlag;
//extern uint8 DisplayImage[MT9V03X_CSI_H][MT9V03X_CSI_W];

#endif /* CODE_INC_USER_IMAGEPROCESS_H_ */
