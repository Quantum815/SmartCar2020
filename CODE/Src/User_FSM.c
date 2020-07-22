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
	{ NOEVENT,  Stop,     RunStop,   Stop    },
    { RUNSTART, Stop,     RunStart,  GoLine  },
	{ NOEVENT,  GoLine,   FindLine,  GoLine  },
	{ GOCROSS,  GoLine,   PassCross, GoLine  },
	{ INGARAGE, GoLine,   GoGarage,  InGarage},
	{ NOEVENT,  InGarage, GoGarage,  InGarage},
    { RUNSTOP,  InGarage, RunStop,   Stop    }
};
FSM_t CarFSM;
double MidLineFuseNum;
float LPWM, RPWM, PIDValue, tt;
uint8 StartSingal;

#pragma section all restore

//事件反应函数
void RunStart(void)
{
	MotorUserHandle(LMotor_F,20);
	MotorUserHandle(RMotor_F,20);
}

void RunStop(void)
{
	SetMotorPWM(LMotor_F, 0);
	SetMotorPWM(LMotor_B, 0);
	SetMotorPWM(RMotor_F, 0);
	SetMotorPWM(RMotor_B, 0);
}

void FindLine(void)
{
    //static float LastLPWM, LastRPWM;
	//float test;
	PIDValue = (GetSpeed()) * GetPIDValue(0.001560, MidLineFuseNum*1000, FINDLINE_P, FINDLINE_I, FINDLINE_D);
	printf("%f\r\n",PIDValue);
//    if(TenSingal>=5)
//		PIDValue = 0-PIDValue;
	LPWM = LeftWheelDeadZone + PIDValue;
    RPWM = RightWheelDeadZone + PIDValue;

    if(LPWM >= 50)
        LPWM = 50;
    else if(LPWM <= -50)
        LPWM = -50;
    if(RPWM >= 50)
        RPWM = 50;
    else if(RPWM <= -50)
        RPWM = -50;
		//test=GetSpeed();
		//PRINTF("%f\r\n",test);
		//test=GetPid(0, 1000*MidLineFuseNum, 50, 0, 3900);
	//printf("LPWM=%f     RPWM=%f\r\n",LPWM,RPWM);
		//PRINTF("%f\r\n",test);
		//ips114_showfloat(100,0,MidLineFuseNum,4,4);
//    if(LLPWM - LPWM >= 5 || LLPWM - LPWM <= -5)
//    {
//        LPWM = LLPWM + (LLPWM - LPWM);
//    }
//    else if(LRPWM - RPWM >= 5 || LRPWM - RPWM <= -5)
//    {
//        RPWM = LRPWM + (LRPWM - RPWM);
//    }
//    LLPWM = LPWM;
//    LRPWM = RPWM;
    MotorUserHandle(LMotor_F, LPWM);
    MotorUserHandle(RMotor_F, RPWM);
}

void PassCross(void)
{
//	float test1,test2,cut;
//			cut=GYROPID(0.35,0,2);
//			test1=LeftWheelDeadZone+cut;
//			test2=RightWheelDeadZone-cut;
//			if(test1>=40)
//				test1=40;
//			else if(test1<=-40)
//			test1=-40;
//			if(test2>=40)
//				test2=40;
//			else if(test2<=-40)
//				test2=-40;
//    MotorUserHandle(LMotor_F, test1);
//    MotorUserHandle(RMotor_F, test2);
//	  MotorUserHandle(LMotor_F, LeftWheelDeadZone);
//    MotorUserHandle(RMotor_F, RightWheelDeadZone);
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
    int flag = 0;  //标识条件是否满足
    int i;

    //获取当前动作函数
    for (i=0; i<size; i++)
    {
        //当且仅当当前状态下来个指定的事件，我才执行它
        if (event == fsmTable[i].Event && curState == fsmTable[i].CurState)
        {
        	flag = 1;
            eventAction = fsmTable[i].EventAction;
            nextState = fsmTable[i].NextState;
        	if(eventAction)
        		eventAction();
        	FSMStateTransfer(fsm, nextState);
            break;
        }
    }
    if(!flag)
    {
        //printf("there is no match!\n");
    }
}

int ReturnFSMState(FSM_t *fsm)
{
	return fsm->CurState;
}

void FSMRun(void)
{
    FSMRegist(&CarFSM, CarTable);
    CarFSM.CurState = Stop;
    CarFSM.Size = sizeof(CarTable) / sizeof(FSMTable_t);
    if(StartSingal == 0)
    {
        CarFSM.CurState = GoLine;
    	StartSingal = 1;
    }
    FSMEventHandle(&CarFSM, NOEVENT);
}

