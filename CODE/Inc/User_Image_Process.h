/*
 * User_Image_Process.h
 *
 *  Created on: 2020Äê7ÔÂ4ÈÕ
 *      Author: Quantum815
 */

#ifndef CODE_INC_USER_IMAGE_PROCESS_H_
#define CODE_INC_USER_IMAGE_PROCESS_H_

#include "headfile.h"

extern uint8 ProcessImageFlag;
extern uint8 EnterGarageFlag;
extern double MidLineFuseNum;

void ImagePretreatment(void);
void FindMidLine(void);
void CameraProcess(void);
void EdgePointFind(void);
double GetMidLineNum(void);
void ShowMidLine(void);
void FindMidLine_ADD(void);
void GetOSTUIMAG(void);
void FindZebra(void);


#endif /* CODE_INC_USER_IMAGE_PROCESS_H_ */
