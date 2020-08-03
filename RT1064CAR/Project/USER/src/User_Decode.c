#include "User_Decode.h"
static double Distant,NowDistant;
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
	Distant+=(-LDistant+RDistant)/2;
	qtimer_quad_clear(QTIMER_3,QTIMER3_TIMER2_B18);
  qtimer_quad_clear(QTIMER_1,QTIMER1_TIMER0_C0);
}
double GetDistant(void)
{
	return Distant;
}
double GetSpeed(void)
{
	return (NowDistant/0.005);
}
void CleanDistant(void)
{
	Distant=0;
}
