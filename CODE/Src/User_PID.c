/*
 * User_PID.c
 *
 *  Created on: 2020年7月8日
 *      Author: Quantum815
 */

#include "..\CODE\Inc\User_PID.h"

#pragma section all "cpu0_dsram"
uint8_t PidValue;
#pragma section all restore

uint8_t GetPIDValue(uint8_t middle,uint8_t value,uint8_t kP,uint8_t kI,uint8_t kD)
{
	static double PreviousErrorValue = 0;
	static double NowErrorValue = 0;
	static double IntegralErrorValue = 0;
	static double DifferentialErrorValue = 0;
	static uint8_t OldValue = 0;

	NowErrorValue = value - middle;
	IntegralErrorValue += NowErrorValue;
	DifferentialErrorValue = NowErrorValue - PreviousErrorValue;

	OldValue = PidValue;
	PidValue = kP * NowErrorValue + kI * IntegralErrorValue + kD * DifferentialErrorValue;
	PreviousErrorValue = NowErrorValue;
	PidValue = 0.1 * OldValue + 0.9 * PidValue;	                       //低通滤波

	return PidValue;
}
