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
    //{到来的事件，当前的状态，将要要执行的函数，下一个状态}
	{ NOEVENT,          WaitBall,         RunStop,               WaitBall         },
	{ GETBALL,          WaitBall,         FindLine,              GoLine           },
	{ NOEVENT,          GoLine,           FindLine,              GoLine           },
	{ FINDROUNDABOUT,   GoLine,           InRoundaboutProcess,   InRoundabout     },
	{ NOEVENT,          InRoundabout,     InRoundaboutProcess,   InRoundabout     },
	{ ENDINROUNDABOUT,  InRoundabout,     CleanDistance,         PassRoundabout   },
	{ NOEVENT,          PassRoundabout,   FindLine,              PassRoundabout   },
	{ OUTROUNDABOUT,    PassRoundabout,   CleanDistance,         OutingRoundabout },
	{ NOEVENT,          OutingRoundabout, OutRoundaboutProcess,  OutingRoundabout },
	{ ENDOUTROUNDABOUT, OutingRoundabout, FindLine,              GoLine           },
	{ FINDZEBRA,        GoLine,           GoGarage,              InGarage         },
	{ NOEVENT,          InGarage,         GoGarage,              InGarage         },
    { RUNSTOP,          InGarage,         RunStop,               Stop             }
};
FSM_t CarFSM;
double MidLineFuseNum;
volatile float LPWM, RPWM;
float PIDValue;
uint8 StartFlag;

#pragma section all restore

#pragma section all "cpu0_psram"

//事件反应函数
void RunStop(void)
{
	MotorUserHandle(LMotor_F, 0);
	MotorUserHandle(RMotor_F, 0);
	//MotorUserHandle(LMotor_B, 80);
	//MotorUserHandle(RMotor_B, 80);
	MotorUserHandle(LMotor_B, 0);
	MotorUserHandle(RMotor_B, 0);
}

void FindLine(void)
{
	//static uint8 uphillCount = 0, downhillCount = 0;

	PIDValue = GetPIDValue(-0.000133, MidLineFuseNum*1000, FINDLINE_P, FINDLINE_I, FINDLINE_D);
	//printf("%f\r\n",PIDValue);
	//if(PitchAngle - FirstPitchAngle <= -3)
	//{
		//uphillCount++;
		//if(uphillCount == 10)
		//{
			//LPWM = LeftWheelDeadZone + LeftUphillSpeed + PIDValue;
		   //RPWM = RightWheelDeadZone + RightUphillSpeed - PIDValue;
		    //uphillCount = 0;
		//}

	//}
	//else if(PitchAngle - FirstPitchAngle >= 3)
	//{
		//downhillCount++;
		//if(downhillCount == 10)
		//{
			//LPWM = LeftWheelDeadZone + LeftDownhillSpeed + PIDValue;
			//RPWM = RightWheelDeadZone + RightDownhillSpeed - PIDValue;
			//downhillCount = 0;
		//}
	//}
	//else
	//{
		LPWM = LeftWheelDeadZone + LeftNormalSpeed + PIDValue;
	    RPWM = RightWheelDeadZone + RightNormalSpeed - PIDValue;
	//}

    if(LPWM >= 30)
        LPWM = 30;
    else if(LPWM <= -30)
        LPWM = -30;
    if(RPWM >= 30)
        RPWM = 30;
    else if(RPWM <= -30)
        RPWM = -30;
    MotorUserHandle(LMotor_F, LPWM);
    MotorUserHandle(RMotor_F, RPWM);
}

void InRoundaboutProcess(void)
{

}

void OutRoundaboutProcess(void)
{

}

void GoGarage(void)
{

}


//*********************************************************
//状态机功能函数
//
//函数作用：状态机注册
//
//****************
void FSMRegist(FSM_t *fsm, FSMTable_t *fsmtable)
{
    fsm->FsmTable = fsmtable;
}

//*****************
//
//函数作用：状态机状态迁移
//
//****************
void FSMStateTransfer(FSM_t* fsm, int state)
{
    fsm->CurState = state;
}

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
        //printf("there is no match!\n");
    //}
}

int ReturnFSMState(FSM_t *fsm)
{
	return fsm->CurState;
}

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
    	//if(TwoCarState())  //测试时注释
    		FSMEventHandle(&CarFSM, GETBALL);
    }
    //else if(ReturnFSMState(&CarFSM) == GoLine)
    //{
    	//FSMEventHandle(&CarFSM, FINDROUNDABOUT);
    //}
    else if(ReturnFSMState(&CarFSM) == InRoundabout)
    {
    	//FSMEventHandle(&CarFSM, ENDINROUNDABOUT);
    }
    else if(ReturnFSMState(&CarFSM) == PassRoundabout)
    {
    	//FSMEventHandle(&CarFSM, OUTROUNDABOUT);
    }
    else if(ReturnFSMState(&CarFSM) == OutingRoundabout)
    {
    	//FSMEventHandle(&CarFSM, ENDOUTROUNDABOUT);
    }
    //else if(ReturnFSMState(&CarFSM) == GoLine)
    //{
    	//FSMEventHandle(&CarFSM, FINDZEBRA);
    //}
    else if(ReturnFSMState(&CarFSM) == InGarage)
    {
    	//FSMEventHandle(&CarFSM, RUNSTOP);
    }
    else
    	FSMEventHandle(&CarFSM, NOEVENT);
}

#pragma section all restore

