/*
 * User_Encoder.c
 *
 *  Created on: 2020ƒÍ7‘¬3»’
 *      Author: Quantum815
 */

#include "..\CODE\Inc\User_Encoder.h"

#pragma section all "cpu0_dsram"

static double CurDistance, TotalDistance;

#pragma section all restore

void EncoderInit(void)
{
	gpt12_init(GPT12_T2, GPT12_T2INB_P33_7, GPT12_T2EUDB_P33_6);
	gpt12_init(GPT12_T6, GPT12_T6INA_P20_3, GPT12_T6EUDA_P20_0);
}

void CountDistance(void)
{
	int16 encoder0, encoder1;
	double CurLdistance, CurRdistance;

	encoder0 = gpt12_get(GPT12_T2);
	encoder1 = gpt12_get(GPT12_T6);

	CurLdistance = ((double)encoder0/1024)*((WHEEL_DIAMETER*3.1415)/1000)*(30/68.0);
	CurRdistance = -((double)encoder1/1024)*((WHEEL_DIAMETER*3.1415)/1000)*(30/68.0);
	CurDistance = (CurLdistance + CurRdistance) / 2;
	TotalDistance += CurDistance;

	//printf("L  %lf	",CurLdistance);  //≤‚ ‘
	//printf("R  %lf	",CurRdistance);  //≤‚ ‘
	//printf("%lf\r\n",TotalDistance);  //≤‚ ‘

	gpt12_clear(GPT12_T2);
	gpt12_clear(GPT12_T6);
}

double GetDistance(void)
{
	return TotalDistance;
}

double GetSpeed(void)  //5ms÷–∂œæ‡¿Îº∆À„
{
	return (CurDistance/0.005);
}

void CleanDistance(void)
{
	TotalDistance = 0;
}
