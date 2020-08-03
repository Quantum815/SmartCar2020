#ifndef _USER_PID
#define _USER_PID
#include "headfile.h"

AT_ITCM_SECTION_INIT(float GetPid(float middle,float value,float kP,float kI,float kD));
AT_ITCM_SECTION_INIT(void ClearValue(void));
#endif