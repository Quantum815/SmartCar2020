#include "User_Decode.h"
double Distant[10],NowDistant;
#define wheel 62
void EnCodeInit(void)
{
	  qtimer_quad_init(QTIMER_3,QTIMER3_TIMER2_B18,QTIMER3_TIMER3_B19);
    qtimer_quad_init(QTIMER_1,QTIMER1_TIMER0_C0,QTIMER1_TIMER1_C1);
}
void CulDistant(void)
{
	int16 EnCoder1,EnCoder2;
	double LDistant,RDistant;
	EnCoder1=qtimer_quad_get(QTIMER_3,QTIMER3_TIMER2_B18);
	EnCoder2=qtimer_quad_get(QTIMER_1,QTIMER1_TIMER0_C0);
	LDistant=((double)EnCoder1/1024)*((wheel*3.1415)/1000)*(30/68.0);
	RDistant=((double)EnCoder2/1024)*((wheel*3.1415)/1000)*(30/68.0);
	NowDistant=(-LDistant+RDistant)/2;
	for(int i=0;i<10;i++)
	Distant[i]+=(-LDistant+RDistant)/2;
	qtimer_quad_clear(QTIMER_3,QTIMER3_TIMER2_B18);
  qtimer_quad_clear(QTIMER_1,QTIMER1_TIMER0_C0);
}
double GetDistant(int i)
{
	return Distant[i];
}
double GetSpeed(void)
{
	return (NowDistant/0.005);
}
void CleanDistant(void)
{
	Distant[0]=0;
}
float SpeedPID(float KP,float KI,float KD,float Speed)
{
	
	float32_t PidValue;
	float32_t OldValue ;
	float32_t ErrorValue;
	float32_t IntegralerrValue=0;
	float32_t Errored;
	float32_t DIS=GetSpeed();
	if(DIS>=900)
	{
		return 0;
	}
	else
	{
	ErrorValue = Speed-DIS;
	PidValue = 		   KP * ErrorValue +
									 KI * IntegralerrValue +
									 KD *(ErrorValue - Errored);
	Errored = ErrorValue;
	//ips114_showfloat(20,20,cutdif,3,5);
	PidValue = 0.1*OldValue + 0.9*PidValue;	                       //????
	if(PidValue>1500)
		PidValue=1500;
	else if (PidValue<-1500)
		PidValue=-1500;

	return PidValue=PidValue/100;
}
	}