/*
 * User_Gyro_Uart.c
 *
 *  Created on: 2020年7月18日
 *      Author: Quantum815
 */

#include "..\CODE\Inc\User_Gyro_Uart.h"

#pragma section all "cpu0_dsram"

uint8 GyroUnlockInstruction[5] = {0xff, 0xaa, 0x69, 0x88, 0xb5};  //解锁指令
uint8 GyroAutoCalibration[5] = {0xff, 0xaa, 0x63, 0x00, 0x00};  //陀螺仪自动校准
uint8 GyroKeepConfiguration[5] = {0xff, 0xaa, 0x00, 0x00, 0x00};  //保持配置
uint8 GyroRxBuff[11];
uint8 GyroReceiveNum, GyroRxFlag;
double PitchAngle, RollAngle, YawAngle, TargetGyroYawAngle;

#pragma section all restore


#pragma section all "cpu0_psram"

void GyroUARTInit(void)
{
	uart_init(UART_0, 115200, UART0_TX_P14_0, UART0_RX_P14_1);
	uart_putbuff(UART_0, &GyroUnlockInstruction[0], 5);
	systick_delay_ms(STM1, 100);
	uart_putbuff(UART_0, &GyroAutoCalibration[0], 5);
	systick_delay_ms(STM1, 100);
	uart_putbuff(UART_0, &GyroKeepConfiguration[0], 5);
	systick_delay_ms(STM1, 100);
}

void GyroUARTReadByte(void)
{
	while(uart_query(UART_0, &GyroRxBuff[GyroReceiveNum]))
	{
        GyroReceiveNum++;
		if(GyroReceiveNum==1 && GyroRxBuff[0]!=0x55)
			GyroReceiveNum = 0;
		if(GyroReceiveNum==2 && GyroRxBuff[1]!=0x53)
			GyroReceiveNum = 0;
        if(11 == GyroReceiveNum)
        {
        	GyroReceiveNum = 0;
            GyroRxFlag = 1;
            break;
        }
	}
}
void GyroCalculate(void)
{
	uint8 sum = 0;
    short temp = 0;

    if(GyroRxFlag == 1)
    {
		sum += GyroRxBuff[0];
		sum += GyroRxBuff[1];
		sum += GyroRxBuff[2];
		sum += GyroRxBuff[3];
		sum += GyroRxBuff[4];
		sum += GyroRxBuff[5];
		sum += GyroRxBuff[6];
		sum += GyroRxBuff[7];
		sum += GyroRxBuff[8];
		sum += GyroRxBuff[9];
		if(sum != GyroRxBuff[10])
		{
			//printf("RECEIVE ERROR!\n");
			GyroRxFlag = 0;
			GyroReceiveNum = 0;
			return;
		}
		temp = (GyroRxBuff[3] << 8) | GyroRxBuff[2];
		PitchAngle = (double)temp / (double)32768 * (double)180;  //y轴俯仰角

		temp = (GyroRxBuff[5] << 8) | GyroRxBuff[4];
		RollAngle = (double)temp / (double)32768 * (double)180;  //x轴滚动角

		temp = (GyroRxBuff[7] << 8) | GyroRxBuff[6];
		YawAngle = (double)temp / (double)32768 * (double)180;//z轴旋转角
		ManageYawAngle();
		GyroRxFlag = 0;
    }
}
void ManageYawAngle(void)
{
    if(YawAngle < 0)
    	YawAngle = YawAngle + 360;
}

void GyroYawAngleInit(double RotationAngle)
{
	TargetGyroYawAngle = YawAngle + RotationAngle;  //左转正右转负
	if(TargetGyroYawAngle > 360)
		TargetGyroYawAngle -= 360;
	else if(TargetGyroYawAngle < 0)
		TargetGyroYawAngle += 360;
}

double GetGyroError(void)
{
    if (TargetGyroYawAngle < 180)
    {
        if (YawAngle > 180)
        {
            if (fabs(YawAngle - TargetGyroYawAngle) <= 180)
            {
                return (YawAngle - TargetGyroYawAngle);
            }
            else

                return (-(TargetGyroYawAngle + 360 - YawAngle));
        }
        else
            return (YawAngle - TargetGyroYawAngle);
    }
    else
    {
        if (YawAngle < 180)
        {
            if (fabs(YawAngle - TargetGyroYawAngle) <= 180)
            {
                return (YawAngle - TargetGyroYawAngle);
            }
            else

                return ((YawAngle + 360) - TargetGyroYawAngle);
        }
        else if (fabs(YawAngle - TargetGyroYawAngle) <= 180)
        {
            return (YawAngle - TargetGyroYawAngle);
        }
        else
            return ((YawAngle + 360) - TargetGyroYawAngle);
    }
}

void GyroPID(double Kp, double Ki, double Kd)
{

    double error = 0, P = 0, I = 0, D = 0, PIDValue = 0;
    double LPWMDutyOut, RPWMDutyOut;
	static double previousError = 0;

    error = GetGyroError();
    //printf("%f\n", error);
    P = error;
    I += error;
    D = error - previousError;

    PIDValue = (Kp * P) + (Ki * I) + (Kd * D);
    previousError = error;
    PIDValue /= 1000;

    LPWMDutyOut = LeftWheelDeadZone + LeftInGarageSpeed - PIDValue;
    RPWMDutyOut = RightWheelDeadZone + RightInGarageSpeed + PIDValue;
	if(LPWMDutyOut >= 40)
		LPWMDutyOut = 40;
	else if(LPWMDutyOut <= -40)
		LPWMDutyOut = -40;
	if(RPWMDutyOut >= 40)
		RPWMDutyOut = 40;
	else if(RPWMDutyOut <= -40)
		RPWMDutyOut = -40;
	MotorUserHandle(LMotor_F, LPWMDutyOut);
	MotorUserHandle(RMotor_F, RPWMDutyOut);
}

#pragma section all restore
