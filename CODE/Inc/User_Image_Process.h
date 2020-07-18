/*
 * User_Image_Process.h
 *
 *  Created on: 2020Äê7ÔÂ4ÈÕ
 *      Author: Quantum815
 */

#ifndef CODE_INC_USER_IMAGE_PROCESS_H_
#define CODE_INC_USER_IMAGE_PROCESS_H_

#include "headfile.h"

#ifdef IMAGEPROCESS

extern uint8 ProcessImageFlag;
extern double MidLineFuseNum;

void ImagePretreatment(void);
void FindMidLine(void);
void CameraProcess(void);
void EdgePointFind(void);
double GetMidLineNum(void);
void ShowMidLine(void);
void FindMidLine_ADD(void);
void GetOSTUIMAG(void);
extern uint8 ProcessImageFlag;
extern double MidLineFuseNum;
//extern uint8 DisplayIMAG[MT9V03X_H][MT9V03X_W];

#endif /* CODE_INC_USER_IMAGE_PROCESS_H_ */

#endif
