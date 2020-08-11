#include "User_PID.h"
	float32_t PidValue;
	float32_t OldValue ;
	float32_t ErrorValue;
	float32_t IntegralerrValue=0;
	float32_t Errored;
float GetPid(float middle,float value,float kP,float kI,float kD)
{

//	float32_t KPV,KDV,TEMP;
//	
//	ErrorValue = value - middle;

//	
//	OldValue = PidValue;
//	TEMP=(ErrorValue - Errored);
//	arm_mult_f32(&kP,&ErrorValue,&KPV,1);
//	arm_mult_f32(&kD,&TEMP,&KDV,1);
//	PidValue = 		   KPV +
//									 //kI * IntegralerrValue +
//									 KDV;
//	Errored = ErrorValue;
////	if(IntegralerrValue>=100)
////		IntegralerrValue=0;
//	//ips114_showfloat(20,20,cutdif,3,5);
//	PidValue = 0.1*OldValue + 0.9*PidValue;	                       //低通滤波
//	if(PidValue>2500)
//		PidValue=2500;
//	else if (PidValue<-2500)
//		PidValue=-2500;
//	return PidValue/100;
	
	
	
//	
	ErrorValue = value - middle;
	IntegralerrValue += ErrorValue;
//	IntegralerrValue += ErrorValue;
//	if(ErrorValue>=4.5)
//	{
//		LeftDeadZone=10.8;
//    RightDeadZone=10.5;
//		//kP=kP*0.95;
//		kD=kD*0.3;
//	}
//	else
//	{
//		LeftDeadZone=15.8;
//    RightDeadZone=15.5;
//	}
	OldValue = PidValue;
	
	PidValue = 		   kP * ErrorValue +
									 kI * IntegralerrValue +
									 kD *(ErrorValue - Errored);
	Errored = ErrorValue;
	//ips114_showfloat(20,20,cutdif,3,5);
	PidValue = 0.1*OldValue + 0.9*PidValue;	                       //低通滤波
	if(PidValue>3000)
		PidValue=3000;
	else if (PidValue<-3000)
		PidValue=-3000;
	return PidValue/100;
}
void ClearValue(void)
{
PidValue=0;
OldValue =0;
ErrorValue=0;
IntegralerrValue=0;
 Errored=0;
}