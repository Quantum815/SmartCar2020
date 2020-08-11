#ifndef _USER_FSM
#define _USER_FSM
#include "headfile.h"
#include "stdio.h"
//#include "arm_math.h"
extern float LeftDeadZone;
extern float RightDeadZone;
AT_ITCM_SECTION_INIT(void LogicThing(void));
AT_ITCM_SECTION_INIT(void RunStart(void));
AT_ITCM_SECTION_INIT(void RunStop(void));
AT_ITCM_SECTION_INIT(void FindLine(void));
AT_ITCM_SECTION_INIT(void PassCross(void));
AT_ITCM_SECTION_INIT(void StopToSendBall(void));
AT_ITCM_SECTION_INIT(void GoOutGarage(void));
AT_ITCM_SECTION_INIT(void InRoundaboutProcess(void));
AT_ITCM_SECTION_INIT(void OutRoundaboutProcess(void));
AT_ITCM_SECTION_INIT(void BackLine(void));
AT_ITCM_SECTION_INIT(void PassBridge(void));
enum NXP_State
{
    Stop,
    GoLine,
    SendBall,
		OutGarage,
		FindBridge,
		InRoundabout,
		PassRoundabout,
		OutingRoundabout,
};

enum Car_Event
{
    RUNSTART = 1,
    RUNSTOP,
		NOTHING,
		TENCROSS,
		FINDCAR,
	  GOOUT,
		FindRoundabout,
		OutRoundabout,
		ENDINROUNDABOUT,
		ENDOUTROUNDABOUT,
		FLASEFINDCAR,
		GOBRIDGE,
		CROSSBRIDGE,
};

typedef struct FsmTable_s {
    int event;   //事件
    int CurState;  //当前状态
    void (*eventActFun)();  //函数指针
    int NextState;  //下一个状态
} FsmTable_t;
extern FsmTable_t Car_Table[] ;

typedef struct FSM_s {
    int CurState;//当前状态
    FsmTable_t * PfsmTable;//状态表
    int Size;//表的项数
} FSM_t;
extern FSM_t Car_Fsm;
extern volatile float LPWM,RPWM,ARFuseNum;
AT_ITCM_SECTION_INIT(void FSM_Regist(FSM_t* Pfsm, FsmTable_t* Ptable));
AT_ITCM_SECTION_INIT(void FSM_StateTransfer(FSM_t* Pfsm, int State));
AT_ITCM_SECTION_INIT(void FSM_EventHandle(FSM_t* Pfsm, int Event));
AT_ITCM_SECTION_INIT(int ReturnFSMState(FSM_t* Pfsm));
AT_ITCM_SECTION_INIT(void ADCulMidLine(void));
AT_ITCM_SECTION_INIT(void ADCulARLine(void));
AT_ITCM_SECTION_INIT(void FindLineAR(float PWM,float Lcut,float Rcut));
AT_ITCM_SECTION_INIT(void FindLineAdjPWM(float PWM,float Lcut,float Rcut));
AT_ITCM_SECTION_INIT(void GiveBall(void));
AT_ITCM_SECTION_INIT(void FindLineAdjBasePWM(float PWM));
#endif