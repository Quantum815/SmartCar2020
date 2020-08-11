#ifndef _USER_DEFINE
#define _USER_DEFINE
#include "headfile.h"

extern double Distant[10],NowDistant;

void EnCodeInit(void);
AT_ITCM_SECTION_INIT(void CulDistant(void));
AT_ITCM_SECTION_INIT(double GetDistant(int i));
AT_ITCM_SECTION_INIT(double GetSpeed(void));
AT_ITCM_SECTION_INIT(void CleanDistant(void));
AT_ITCM_SECTION_INIT(float SpeedPID(float KP,float KI,float KD,float Speed));
#endif