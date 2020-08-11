#include "User_TFmini.h"
int LaserDistant;
float GetLaserDistant(void)
{
//	if(LaserDistant==0)
//		LaserDistant=99999;
	return LaserDistant/100.0;
}
void UpDateLaserDistant(void)
{
	uint8_t sum = 0;
	if(LaserRecFlag==1)
	{
		for(int i = 0;i < 8; i++)
		{
			sum += TFminiRx_Data[i];
		}
		//sum+=0x59;
		if(sum == TFminiRx_Data[8])
		{
			LaserDistant = TFminiRx_Data[3];
			LaserDistant <<= 8;
			LaserDistant += TFminiRx_Data[2];
		}
		else
		{
			LaserDistant=-1;
			//gpio_toggle(B9);
			//systick_delay_ms(500);
			//PRINTF("fuck you son of bitch\r\n");
			//NVIC_SystemReset();	
		}
		LaserRecFlag=0;
	}
}
float LaserDistantPID(float KP,float KI,float KD,float Distant)
{
	float32_t PidValue;
	float32_t OldValue ;
	float32_t ErrorValue;
	float32_t IntegralerrValue=0;
	float32_t Errored;
	float32_t DIS=GetLaserDistant();
	if(DIS>=900)
	{
		return 0;
	}
	else
	{
	ErrorValue = GetLaserDistant()-Distant;
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
	if(DIS<=0.8 && DIS >=0.4)
	{
			if(PidValue>800)
		PidValue=800;
			else if (PidValue<-800)
		PidValue=-800;
	}
	else if(DIS<0.4)
	{
					if(PidValue>500)
		PidValue=500;
			else if (PidValue<-500)
		PidValue=-500;
	}
	return PidValue=PidValue/100;
}
	//return PidValue/100;
	
}