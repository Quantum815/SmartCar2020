#include "User_TFmini.h"
int LaserDistant;
float GetLaserDistant(void)
{
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
		if(sum == TFminiRx_Data[8])
		{
			LaserDistant = TFminiRx_Data[3];
			LaserDistant <<= 8;
			LaserDistant += TFminiRx_Data[2];
		}
		else
		{
			//gpio_toggle(B9);
			//systick_delay_ms(500);
			//PRINTF("fuck you son of bitch\r\n");
			//NVIC_SystemReset();	
		}
		LaserRecFlag=0;
	}
}