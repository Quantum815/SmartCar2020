/*
 * User_FSM.c
 *
 *  Created on: 2020年7月2日
 *      Author: Quantum815
 */

#include "..\CODE\Inc\User_fsm.h"

FSMTable_t CarTable[] =
{
    //{到来的事件，当前的状态，将要要执行的函数，下一个状态}
    { RUNSTART, Stop,   RunStart, GoLine },
    { RUNSTOP,  GoLine, RunStop,  Stop   },
	{ NOEVENT, Stop,   RunStop,  Stop   },
	{ NOEVENT, GoLine, FindLine, GoLine }
    //如果出现新的代码加入在此
};

FSM_t CarFSM;

//事件反应函数
void RunStart(void)
{

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

}

//************************************************
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
    int flag = 0;
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
        printf("there is no match!\n");
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
    FSMEventHandle(&CarFSM, NOEVENT);
}

