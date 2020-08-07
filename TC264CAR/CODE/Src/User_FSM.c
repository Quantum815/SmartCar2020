/*
 * User_FSM.c
 *
 *  Created on: 2020年7月2日
 *      Author: Quantum815
 */

#include "..\CODE\Inc\User_fsm.h"

#pragma section all "cpu0_dsram"

FSMTable_t CarTable[] =
{
//    到来的事件                   当前的状态                  将要要执行的函数                    下一个状态
//	    正常执行状态表
	{ NOEVENT,          WaitBall,         WaitRunStop,           WaitBall         },
	{ GETBALL,          WaitBall,         FindLine,              GoLine           },
	{ NOEVENT,          GoLine,           FindLine,              GoLine           },
	{ FINDROUNDABOUT,   GoLine,           InRoundaboutProcess,   InRoundabout     },
	{ NOEVENT,          InRoundabout,     InRoundaboutProcess,   InRoundabout     },
	{ ENDINROUNDABOUT,  InRoundabout,     FindLine,              PassRoundabout   },
	{ NOEVENT,          PassRoundabout,   FindLine,              PassRoundabout   },
	{ OUTROUNDABOUT,    PassRoundabout,   OutRoundaboutProcess,  OutingRoundabout },
	{ NOEVENT,          OutingRoundabout, OutRoundaboutProcess,  OutingRoundabout },
	{ ENDOUTROUNDABOUT, OutingRoundabout, FindLine,              GoLine           },
	{ LEFTFINDZEBRA,    GoLine,           TurnLeftGoGarage,      LeftInGarage     },
	{ RIGHTFINDZEBRA,   GoLine,           TurnRightGoGarage,     RightInGarage    },
	{ NOEVENT,          LeftInGarage,     TurnLeftGoGarage,      LeftInGarage     },
	{ NOEVENT,          RightInGarage,    TurnRightGoGarage,     RightInGarage    },
    { RUNSTOP,          LeftInGarage,     RunStop,               Stop             },
    { RUNSTOP,          RightInGarage,    RunStop,               Stop             },
	{ NOEVENT,          Stop,             RunStop,               Stop             },
//	  debug强制停止状态表
	{ RUNSTOP,          GoLine,           RunStop,               Stop             },
	{ RUNSTOP,          InRoundabout,     RunStop,               Stop             },
	{ RUNSTOP,          PassRoundabout,   RunStop,               Stop             },
	{ RUNSTOP,          OutingRoundabout, RunStop,               Stop             },
	{ RUNSTOP,          LeftInGarage,     RunStop,               Stop             },
	{ RUNSTOP,          RightInGarage,    RunStop,               Stop             }
};
FSM_t CarFSM;
double MidLineFuseNum;
volatile float LPWM, RPWM;
float PIDValue;

//状态机各种标志位和计数位
uint8 StartFlag;
volatile uint8 IntoRoundaboutCount;  //环岛消抖
volatile uint8 RoundaboutCount;//进圆计数
volatile uint8 LRoundaboutFlag;  //判断为左环
volatile uint8 RRoundaboutFlag;  //判断为右环
volatile uint8 PassingRoundaboutFlag; //判断是否在走圆
volatile uint8 GoGarageFinishFlag;
volatile uint8 KickFlag;

#pragma section all restore


//*********************************************************
//					事件反应函数
void WaitRunStop(void)
{
	if(GetDistance(0) > 0.02 && !TwoCarRxFlag)
	{
		KickFlag = 1;
		MotorUserHandle(LMotor_B, LeftWheelBrakeZone+9);
		MotorUserHandle(RMotor_B, RightWheelBrakeZone+9);
	}
	else
	{
		MotorUserHandle(LMotor_B, LeftWheelBrakeZone);
		MotorUserHandle(RMotor_B, RightWheelBrakeZone);
	}
}
void RunStop(void)
{
	MotorUserHandle(LMotor_B, LeftWheelBrakeZone);
	MotorUserHandle(RMotor_B, RightWheelBrakeZone);
}

void FindLine(void)
{
	if(!PassingRoundaboutFlag){
		LRoundaboutFlag = 0;
		RRoundaboutFlag = 0;
		PassingRoundaboutFlag = 0;
	}
	PIDValue = GetPIDValue(PIDMidLineFuseNum, MidLineFuseNum*1000, FINDLINE_P, FINDLINE_I, FINDLINE_D);
	//printf("%f\r\n",PIDValue);
	LPWM = LeftWheelDeadZone + LeftNormalSpeed - PIDValue;
	RPWM = RightWheelDeadZone + RightNormalSpeed + PIDValue;

    if(LPWM >= 50)
        LPWM = 50;
    else if(LPWM <= -50)
        LPWM = -50;
    if(RPWM >= 50)
        RPWM = 50;
    else if(RPWM <= -50)
        RPWM = -50;
    MotorUserHandle(LMotor_F, LPWM);
    MotorUserHandle(RMotor_F, RPWM);
}

void InRoundaboutProcess(void)
{
	static uint8 InCleanDistanceFlag = 0;

	if(!InCleanDistanceFlag)
	{
		CleanDistance();
		InCleanDistanceFlag = 1;
	}

	if(LRoundaboutFlag)
	{
//		if(GetDistance(0) < 0.1)
//		{
//			FindLine();
//		}
//		else
		if(GetDistance(0) < 0.4)//0.35 //0.4
		{
	    	uart_putchar(UART_3,0X02);//状态检测2
			FindLineAdjPWM(6, -8, 12);//6 -4 6 //6 -8 12
		}
		else
		{
	    	uart_putchar(UART_3,0X03);//状态检测3
			FindLine();
			PassingRoundaboutFlag = 1;
		}
	}
	else if(RRoundaboutFlag)
	{
		if(GetDistance(0) < 0.3)
		{
			FindLineAdjPWM(6, 0, 6);
		}
		else
		{
			FindLine();
			PassingRoundaboutFlag = 1;
		}
	}
}

void OutRoundaboutProcess(void)
{
	static uint8 OutCleanDistanceFlag = 0;

	if(!OutCleanDistanceFlag)
	{
		CleanDistance();
		OutCleanDistanceFlag = 1;
	}

	if(LRoundaboutFlag)
	{
//		if(GetDistance(0) < 0.3)
//		{
//			FindLineAdjPWM(6, 6, 0);
//		}
//		else
//		{
//			PassingRoundaboutFlag = 0;
//			FindLine();
//		}
		FindLine();
	}
	else if(RRoundaboutFlag)
	{
//		if(GetDistance(0) < 0.3)
//		{
//			FindLineAdjPWM(6, 6, 0);
//		}
//		else
//		{
//			PassingRoundaboutFlag = 0;
//			FindLine();
//		}
		FindLine();
	}
}

void TurnLeftGoGarage(void)
{
	static uint8 CleanDistanceFlag = 0;

	if(!CleanDistanceFlag)
	{
		CleanDistance();
		CleanDistanceFlag = 1;
	}
	GyroYawAngleInit(SetLeftRotationAngle);//+左转；-右转
	GyroPID(GYRO_P, GYRO_I, GYRO_D);
	if(TotalDistance[0] >= 0.05)//0.05;0.01;原始0.25
	{
	    MotorUserHandle(LMotor_F, LeftWheelDeadZone);
	    MotorUserHandle(RMotor_F, RightWheelDeadZone+10);//10;10;原始0
	}
	if(TotalDistance[0] >= 0.3)//0.5;原始0.7
	{
		RunStop();
		GoGarageFinishFlag = 1;
	}
}

void TurnRightGoGarage(void)
{
	static uint8 CleanDistanceFlag = 0;

	if(!CleanDistanceFlag)
	{
		CleanDistance();
		CleanDistanceFlag = 1;
	}
	GyroYawAngleInit(-SetRightRotationAngle);
	GyroPID(GYRO_P, GYRO_I, GYRO_D);
	if(TotalDistance[0] >= 0.05)//0.05;原始0.25
	{
//    	uart_putchar(UART_3,0X06);//状态检测6
	    MotorUserHandle(LMotor_F, LeftWheelDeadZone+15);//10;原始0
	    MotorUserHandle(RMotor_F, RightWheelDeadZone);
	}
	else if(TotalDistance[0] >= 0.2 )//0.5;原始0.7
	{
//    	uart_putchar(UART_3,0X07);//状态检测7
		RunStop();
		GoGarageFinishFlag = 1;
	}
	if(GetDistance(1)>=15.5)
	{
		RunStop();
		GoGarageFinishFlag = 1;
	}
}
//*********************************************************


//*********************************************************
//					状态机功能函数

//函数作用：状态机注册
void FSMRegist(FSM_t *fsm, FSMTable_t *fsmtable)
{
    fsm->FsmTable = fsmtable;
}

//状态机状态迁移
void FSMStateTransfer(FSM_t* fsm, int state)
{
    fsm->CurState = state;
}

//状态机状态执行函数
void FSMEventHandle(FSM_t *fsm, int event)
{
	FSMTable_t *fsmTable = fsm->FsmTable;
    int curState = fsm->CurState;
    void (*eventAction)() = NULL;  //函数指针初始化为空
    int nextState = -1;
    int size = fsm->Size;
    //int flag = 0;  //标识条件是否满足
    int i;

    //获取当前动作函数
    for (i=0; i<size; i++)
    {
        //当且仅当当前状态下来个指定的事件，我才执行它
        if (event == fsmTable[i].Event && curState == fsmTable[i].CurState)
        {
        	//flag = 1;
            eventAction = fsmTable[i].EventAction;
            nextState = fsmTable[i].NextState;
        	if(eventAction)
        		eventAction();
        	FSMStateTransfer(fsm, nextState);
            break;
        }
    }
    //if(!flag)
    //{
        //printf("No match!\n");
    //}
}

int ReturnFSMState(FSM_t *fsm)
{
	return fsm->CurState;
}
//********************************************************


void FSMRun(void)
{
    FSMRegist(&CarFSM, CarTable);
	if(!StartFlag)
	{
		CarFSM.CurState = WaitBall;
		StartFlag = 1;
	}
    CarFSM.Size = sizeof(CarTable) / sizeof(FSMTable_t);

    if(ReturnFSMState(&CarFSM) == WaitBall)
    {
//    	if(TwoCarStateJudge())  //测试时注释
		FSMEventHandle(&CarFSM, GETBALL);
    }
//    else if(ADCValueHandle(2) >= ADCvalueC && (ADCValueHandle(1) >= ADCvalueCL || ADCValueHandle(3) >= ADCvalueCR)\
//    && (ADCValueHandle(0) > ADCvalueLL || ADCValueHandle(4) > ADCvalueRR) && ReturnFSMState(&CarFSM) == GoLine && RoundaboutCount==0)//检测进圆
//    {
//    	IntoRoundaboutCount++;
//    	if(IntoRoundaboutCount >= 3)//连续检测三次
//    	{
//    		RoundaboutCount=1;
//    		if(ADCValueHandle(1) > ADCValueHandle(3))//判断左圆或右圆
//			{
//    	    	uart_putchar(UART_3,0X01);//状态检测1
//				LRoundaboutFlag = 1;//左圆
//				RRoundaboutFlag = 0;
//			}
//			else
//			{
//				LRoundaboutFlag = 0;
//				RRoundaboutFlag = 1;//右圆
//			}
////    		RoundaboutCount = 0;
//            FSMEventHandle(&CarFSM, FINDROUNDABOUT);
////            FSMEventHandle(&CarFSM, RUNSTOP);
//    	}
//    }
//    else if(PassingRoundaboutFlag && ReturnFSMState(&CarFSM) == InRoundabout)//圆内过程
//    {
//    	uart_putchar(UART_3,0X04);//状态检测4
//    	FSMEventHandle(&CarFSM, ENDINROUNDABOUT);
//    }
//    else if(ADCValueHandle(2) >= ADCvalueC && (ADCValueHandle(1) >= ADCvalueCL || ADCValueHandle(3) >= ADCvalueCR)\
//    && (ADCValueHandle(0) > ADCvalueLL || ADCValueHandle(4) > ADCvalueRR) && ReturnFSMState(&CarFSM) == PassRoundabout && PassingRoundaboutFlag && GetDistance(1)>=10.5)//检测出圆
//    {
////    	PassingRoundaboutFlag=0;
//    	uart_putchar(UART_3,0X05);//状态检测5
//    	FSMEventHandle(&CarFSM, OUTROUNDABOUT);
////    	FSMEventHandle(&CarFSM, RUNSTOP);
//    }
//    else if(PassingRoundaboutFlag && ReturnFSMState(&CarFSM) == OutingRoundabout)
//    {
//		PassingRoundaboutFlag = 0;
//    	FSMEventHandle(&CarFSM, ENDOUTROUNDABOUT);
////		FSMEventHandle(&CarFSM, RUNSTOP);
//    }
    else if(!InGarageDirection && EnterGarageFlag && ReturnFSMState(&CarFSM) == GoLine && GetDistance(1)>=9)
    {
        MotorUserHandle(LMotor_F, LeftWheelDeadZone+LeftInGarageSpeed);
        MotorUserHandle(RMotor_F, RightWheelDeadZone+RightInGarageSpeed);
    	FSMEventHandle(&CarFSM, LEFTFINDZEBRA);
    }
    else if(InGarageDirection && EnterGarageFlag && ReturnFSMState(&CarFSM) == GoLine && GetDistance(1)>=9)
    {
        MotorUserHandle(LMotor_F, LeftWheelDeadZone+LeftInGarageSpeed);
        MotorUserHandle(RMotor_F, RightWheelDeadZone+RightInGarageSpeed);
    	FSMEventHandle(&CarFSM, RIGHTFINDZEBRA);
    }
    else if(GoGarageFinishFlag && ReturnFSMState(&CarFSM) == LeftInGarage)
    {
    	FSMEventHandle(&CarFSM, RUNSTOP);
    }
    else if(GoGarageFinishFlag && ReturnFSMState(&CarFSM) == RightInGarage)
    {
    	FSMEventHandle(&CarFSM, RUNSTOP);
    }
    else
    	FSMEventHandle(&CarFSM, NOEVENT);
}

//其他函数
void FindLineAdjPWM(double PWM, double LCut, double RCut)
{
    PIDValue =  GetPIDValue(PIDMidLineFuseNum, 1000 * MidLineFuseNum, 15, 0.1, 2000);
    //PIDValue =  GetPIDValue(-0.002763617550954, 1000 * MidLineFuseNum, 41, 0, 3300); //54 0 35000  56.8 0 10500
    if(PWM >= 0)
    {
        LPWM = PWM + LeftWheelDeadZone - PIDValue + LCut;
        RPWM = PWM + RightWheelDeadZone +PIDValue + RCut;
    }
    else if(PWM < 0)
    {
        LPWM = PWM + PIDValue;
        RPWM = PWM - PIDValue;
    }
    if(LPWM >= 50)
        LPWM = 50;
    else if(LPWM <= -50)
        LPWM = -50;
    if(RPWM >= 50)
        RPWM = 50;
    else if(RPWM <= -50)
        RPWM = -50;
    MotorUserHandle(LMotor_F, LPWM);
    MotorUserHandle(RMotor_F, RPWM);
}

