/*
 * User_Encoder.c
 *
 *  Created on: 2020年7月3日
 *      Author: Quantum815
 */

#include "..\CODE\Inc\User_Encoder.h"

double CurDistance;
double TotalDistance;

void EncoderInit(void)
{
	gpt12_init(GPT12_T2, GPT12_T2INB_P33_7, GPT12_T2EUDB_P33_6);
	gpt12_init(GPT12_T6, GPT12_T6INA_P20_3, GPT12_T6EUDA_P20_0);
}

void CountDistance(void)
{
	int16 encoder0, encoder1;
	double CurLdistance, CurRdistance;
	static double TotalLdistance, TotalRdistance;

	encoder0 = gpt12_get(GPT12_T2);
	encoder1 = gpt12_get(GPT12_T6);

	CurLdistance = ((double)encoder0/1024)*((WHEEL_DIAMETER*3.1415)/1000);
	CurRdistance = ((double)encoder1/1024)*((WHEEL_DIAMETER*3.1415)/1000);
	CurDistance = (CurLdistance + CurRdistance) / 2;

	TotalLdistance += CurLdistance;
	TotalRdistance += CurLdistance;
	TotalDistance = (TotalLdistance + TotalRdistance) / 2;

	gpt12_clear(GPT12_T2);
	//printf("%lf\r\n",Ldistance);  //测试
	gpt12_clear(GPT12_T6);
}

double GetDistance(void)
{
	return TotalDistance;
}

double GetSpeed(void)  //主进程20ms   似乎存在问题
{
	return (CurDistance/0.02);
}
