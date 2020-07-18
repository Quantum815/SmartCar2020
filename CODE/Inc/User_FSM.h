/*
 * User_FSM.h
 *
 *  Created on: 2020年7月2日
 *      Author: Quantum815
 */

#ifndef CODE_INC_USER_FSM_H_
#define CODE_INC_USER_FSM_H_

#include "headfile.h"

enum CarState  //状态
{
    Stop,
    GoLine
    //如果出现新的代码加入在此
};

enum CarEvent  //事件
{
	NOEVENT,
    RUNSTART,
    RUNSTOP,
	GOROUND
    //如果出现新的代码加入在此
};

typedef struct FSMTable{
    int Event;   //事件
    int CurState;  //当前状态
    void (*EventAction)();  //函数指针
    int NextState;  //下一个状态
}FSMTable_t;

extern FSMTable_t CarTable[];

typedef struct FSM{
    int CurState;  //当前状态
    FSMTable_t *FsmTable;  //状态表
    int Size;  //表的项数
}FSM_t;

extern FSM_t CarFSM;

void RunStart(void);
void RunStop(void);
//void FindLine(void);
void PassCross(void);

void FSMRegist(FSM_t *fsm, FSMTable_t *fsmtable);
void FSMStateTransfer(FSM_t *fsm, int state);
void FSMEventHandle(FSM_t *fsm, int event);
int ReturnFSMState(FSM_t *fsm);
void FSMRun(void);

#endif /* CODE_INC_USER_FSM_H_ */
