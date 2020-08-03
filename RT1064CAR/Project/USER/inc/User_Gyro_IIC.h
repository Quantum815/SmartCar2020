#ifndef _USER_GYRO
#define _USER_GYRO
#include "headfile.h"

void GyroInit(void);
void GyroReadByte(void);
void DealRoll(void);
double GetGYROError();
double GetGYROCulError();
void InitGYRORollAngle(float Angle);
void GYROPID(float Kp,float Ki,float Kd);
void UpdateCulAngle(void);
double CulAngle(void);
void InitCulAngle(void);
void GyroErrorCheck(void);
extern double Pitch_value,yaw_value,roll_value,a_1,a_2,a_3,_NowGyroYawAngle;
extern float GYROerror;
#endif