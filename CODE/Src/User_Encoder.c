/*
 * User_Encoder.c
 *
 *  Created on: 2020年7月3日
 *      Author: Quantum815
 */

#include "..\CODE\Inc\User_Encoder.h"

double Distance;

void EncoderInit(void)
{
	gpt12_init(GPT12_T2, GPT12_T2INB_P33_7, GPT12_T2EUDB_P33_6);
	//gpt12_init(GPT12_T3, GPT12_T3INA_P02_6, GPT12_T3EUDA_P02_7);
}

void CurDistance(void)  //有阻塞
{
	int16 encoder0, encoder1;
	static double Ldistance, Rdistance;

	encoder0 = gpt12_get(GPT12_T2);
	encoder1 = gpt12_get(GPT12_T3);

	Ldistance += ((double)encoder0/1024)*((WHEEL_DIAMETER*3.1415)/1000);
	Rdistance += ((double)encoder1/1024)*((WHEEL_DIAMETER*3.1415)/1000);
	Distance = (Ldistance + Rdistance) / 2;
	gpt12_clear(GPT12_T2);
	//printf("%d\r\n",encoder0);  //测试
	gpt12_clear(GPT12_T3);
}

double GetDistance(void)
{
	return Distance;
}

double GetSpeed(void)  //主进程20ms   似乎存在问题
{
	return (Distance/0.02);
}
