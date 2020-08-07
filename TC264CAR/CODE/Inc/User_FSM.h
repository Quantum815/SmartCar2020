/*
 * User_FSM.h
 *
 *  Created on: 2020年7月2日
 *      Author: Quantum815
 */

#ifndef CODE_INC_USER_FSM_H_
#define CODE_INC_USER_FSM_H_

#include "headfile.h"

extern double MidLineFuseNum;
extern double MidLineFuseRatioNum;

enum CarState  //状态
{
	WaitBall,
    GoLine,
	InRoundabout,
	PassRoundabout,
	OutingRoundabout,
	LeftInGarage,
	RightInGarage,
    Stop
};

enum CarEvent  //事件
{
	NOEVENT,
	GETBALL,
	FINDROUNDABOUT,
	ENDINROUNDABOUT,
	OUTROUNDABOUT,
	ENDOUTROUNDABOUT,
	LEFTFINDZEBRA,
	RIGHTFINDZEBRA,
    RUNSTOP
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

void WaitRunStop(void);
void RunStop(void);
void FindLine(void);
void InRoundaboutProcess(void);
void OutRoundaboutProcess(void);
void TurnLeftGoGarage(void);
void TurnRightGoGarage(void);

void FSMRegist(FSM_t *fsm, FSMTable_t *fsmtable);
void FSMStateTransfer(FSM_t *fsm, int state);
void FSMEventHandle(FSM_t *fsm, int event);
int ReturnFSMState(FSM_t *fsm);
void FSMRun(void);
void FindLineAdjPWM(double PWM, double LCut, double RCut);
void FindLineRatioAdjPWM(double PWM, double LCut, double RCut);

#endif /* CODE_INC_USER_FSM_H_ */
