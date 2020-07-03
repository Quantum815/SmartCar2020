/*
 * User_FSM.h
 *
 *  Created on: 2020年7月2日
 *      Author: Quantum815
 */

#ifndef CODE_INC_USER_FSM_H_
#define CODE_INC_USER_FSM_H_

#include "headfile.h"

enum CarState
{
    Stop,
    GoLine,
    SendBall
    //如果出现新的代码加入在此
};

enum CarEvent
{
    RUNSTART,
    RUNSTOP
    //如果出现新的代码加入在此
};

typedef struct {
    int Event;   //事件
    int CurState;  //当前状态
    void (*EventAction)();  //函数指针
    int NextState;  //下一个状态
}FSMTable;

extern FSMTable CarTable[];

typedef struct {
    int CurState;  //当前状态
    FSMTable *FsmTable;  //状态表
    int Size;  //表的项数
}FSM;

extern FSM CarFSM;

void RunStart(void);
void RunStop(void);

void FSMRegist(FSM* fsm, FSMTable *fsmtable);
void FSMStateTransfer(FSM *fsm, int state);
void FSMEventAction(FSM *fsm, int event);
void LogicThing(void);
int ReturnFSMState(FSM *fsm);

#endif /* CODE_INC_USER_FSM_H_ */
