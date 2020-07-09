/*
 * User_PID.c
 *
 *  Created on: 2020年7月8日
 *      Author: Quantum815
 */

#include "..\CODE\Inc\User_PID.h"

uint8_t GetPIDValue(uint8_t middle,uint8_t value,uint8_t kP,uint8_t kI,uint8_t kD)
{
	uint8_t PidValue;
	uint8_t OldValue = 0;
	static double NowErrorValue;
	static double IntegralErrorValue;
	static double PreviousErrorValue;

	NowErrorValue = value - middle;
	IntegralErrorValue += NowErrorValue;

	OldValue = PidValue;  //问题亟需解决

	PidValue = kP * NowErrorValue + kI * IntegralErrorValue + kD * (NowErrorValue - PreviousErrorValue);
	PreviousErrorValue = NowErrorValue;

	PidValue = 0.1 * OldValue + 0.9 * PidValue;	                       //低通滤波

	return PidValue;
}
