#ifndef _IMAGEPROCESS_H
#define _IMAGEPROCESS_H
#include "headfile.h"
#include "User_fsm.h"
enum ColorT
{
	MRED,
	MGREEN,
	MBLUE,
};
//AT_ITCM_SECTION_INIT(void ImagePretreatment(void));
//AT_ITCM_SECTION_INIT(void FindMedLine(void));
//AT_ITCM_SECTION_INIT(void FindMedLine_ADD(void));
AT_ITCM_SECTION_INIT(void CameraProcess(void));
AT_ITCM_SECTION_INIT(void UpDateRedNnm(void));
AT_ITCM_SECTION_INIT(void TakePointColor(uint16 *dat, uint16 x, uint16 y, uint16 z, uint8 *r, uint8 *g, uint8 *b));
int ReturnColorNum(int Color);
//AT_ITCM_SECTION_INIT(void EdgePointFind(void));
//AT_ITCM_SECTION_INIT(double GetMidLineNum(void));
//AT_ITCM_SECTION_INIT(void ShowMidLine(void));
//AT_ITCM_SECTION_INIT(void GetOSTUIMAG(void));

extern uint8 ProcessImageFlag;
extern double MidLineFuseNum;
//extern uint8 DisplayIMAG[MT9V03X_CSI_H][MT9V03X_CSI_W];
#endif