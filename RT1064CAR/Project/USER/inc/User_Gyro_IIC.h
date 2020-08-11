#ifndef _USER_GYRO
#define _USER_GYRO
#include "headfile.h"

void GyroInit(void);
void GyroReadByte(void);
AT_ITCM_SECTION_INIT(void DealRoll(void));
AT_ITCM_SECTION_INIT(double GetGYROError());
AT_ITCM_SECTION_INIT(double GetGYROCulError());
AT_ITCM_SECTION_INIT(void InitGYRORollAngle(float Angle));
AT_ITCM_SECTION_INIT(void GYROPID(float Kp,float Ki,float Kd));
AT_ITCM_SECTION_INIT(void UpdateCulAngle(void));
AT_ITCM_SECTION_INIT(double CulAngle(void));
AT_ITCM_SECTION_INIT(void InitCulAngle(void));
AT_ITCM_SECTION_INIT(void GyroErrorCheck(void));
extern double Pitch_value,yaw_value,roll_value,a_1,a_2,a_3,_NowGyroYawAngle;
extern float GYROerror;
#endif