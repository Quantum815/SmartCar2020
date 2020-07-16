/*
 * User_PID.c
 *
 *  Created on: 2020年7月8日
 *      Author: Quantum815
 */

#include "..\CODE\Inc\User_PID.h"

#pragma section all "cpu0_dsram"

double PidValue;

#pragma section all restore

#pragma section all "cpu0_psram"

double GetPIDValue(double middle, double value, double kP, double kI, double kD)
{
	static double PreviousErrorValue = 0;
	static double NowErrorValue = 0;
	static double IntegralErrorValue = 0;
	static double DifferentialErrorValue = 0;
	static double OldValue = 0;

	NowErrorValue = value - middle;
	IntegralErrorValue += NowErrorValue;
	DifferentialErrorValue = NowErrorValue - PreviousErrorValue;
	OldValue = PidValue;

	PidValue = kP * NowErrorValue + kI * IntegralErrorValue + kD * DifferentialErrorValue;

	PreviousErrorValue = NowErrorValue;
	PidValue = 0.1 * OldValue + 0.9 * PidValue;	                       //低通滤波
	if(PidValue > 1200)
		PidValue = 1200;
	else if(PidValue < -1200)
		PidValue = -1200;

	return (PidValue/100);
}

#pragma section all restore
