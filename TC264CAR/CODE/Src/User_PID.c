/*
 * User_PID.c
 *
 *  Created on: 2020年7月8日
 *      Author: Quantum815
 */

#include "..\CODE\Inc\User_PID.h"

#pragma section all "cpu0_dsram"

double PidValue;
double PreviousErrorValue;
double NowErrorValue;
double IntegralErrorValue;
double DifferentialErrorValue;
double OldValue;

#pragma section all restore


#pragma section all "cpu0_psram"

double GetPIDValue(double middle, double value, double kP, double kI, double kD)
{

	NowErrorValue = value - middle;
	//IntegralErrorValue += NowErrorValue;
	DifferentialErrorValue = NowErrorValue - PreviousErrorValue;
	OldValue = PidValue;

	PidValue = kP * NowErrorValue + kI * IntegralErrorValue + kD * DifferentialErrorValue;

	PreviousErrorValue = NowErrorValue;

	PidValue = 0.1 * OldValue + 0.9 * PidValue;	                       //低通滤波

	if(PidValue > 2800)
		PidValue = 2800;
	else if(PidValue < -2800)
		PidValue = -2800;

	return (PidValue/100);
}

void CleanPIDValue(void)
{
	PidValue = 0;
	PreviousErrorValue = 0;
	NowErrorValue = 0;
	IntegralErrorValue = 0;
	OldValue = 0;
}

#pragma section all restore
