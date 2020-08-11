#ifndef _USER_TF
#define _USER_TF
#include "headfile.h"
AT_ITCM_SECTION_INIT(float GetLaserDistant(void));
void UpDateLaserDistant(void);
AT_ITCM_SECTION_INIT(float LaserDistantPID(float KP,float KI,float KD,float Distant));
#endif