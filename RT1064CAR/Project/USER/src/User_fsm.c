#include "User_fsm.h"
#if AntiWay ==0
#define OutGarageAngle 90
#else
#define OutGarageAngle -90
#endif
volatile float LPWM, RPWM, PIDValue, tt, LRAFlag, RRAFlag, OutRAroll, PassAR = 0, CntAR = 0, CarFlag = 0, ARFuseNum, CloseSingal = 0;
float LastLaserDistant;
uint8 OneIN = 0;
float LeftDeadZone = 15.5;//22.5  速度可提高aaaaaaaaaaaaaaaaaaaaa
float RightDeadZone = 15.5;//22.5
uint8 TenSingal, CarSingal, StartSingal, RoundaboutSingal;

extern uint32_t TwoCarCount;

FSM_t Car_Fsm;
FsmTable_t Car_Table[] =
{
    //{到来的事件，当前的状态，将要要执行的函数，下一个状态}
    { RUNSTART,  Stop,    RunStart,  GoLine },
    { RUNSTOP,  GoLine,    RunStop,  Stop },
    { NOTHING,  Stop,      RunStop,  Stop},
    { NOTHING,  GoLine,    FindLine,  GoLine},
    { TENCROSS, GoLine, PassCross, GoLine},
    { FINDCAR,  GoLine, CleanDistant, SendBall},
    {	NOTHING, SendBall, StopToSendBall, SendBall},
    { FLASEFINDCAR, SendBall, BackLine, GoLine},
    { NOTHING, OutGarage, GoOutGarage, OutGarage},
    { GOOUT,   OutGarage, FindLine,   GoLine},
    {GOBRIDGE, GoLine, CleanDistant, FindBridge},
    {NOTHING, FindBridge, FindLine, FindBridge},
    {CROSSBRIDGE, FindBridge, PassBridge, GoLine},
    {FindRoundabout, GoLine, InRoundaboutProcess, InRoundabout},
    {NOTHING, InRoundabout, InRoundaboutProcess, InRoundabout},
    {ENDINROUNDABOUT, InRoundabout, CleanDistant, PassRoundabout},
    {NOTHING, PassRoundabout, FindLine, PassRoundabout},
    {OutRoundabout, PassRoundabout, CleanDistant, OutingRoundabout},
    {NOTHING, OutingRoundabout, OutRoundaboutProcess, OutingRoundabout},
    {ENDOUTROUNDABOUT, OutingRoundabout, FindLine, GoLine},
	
//	{ NOTHING, OutGarage, GoOutGarage, OutGarage},
//	{ GOOUT,   OutGarage, FindLine,   GoLine},
//	{ NOTHING,  GoLine,    FindLine,  GoLine},
//	{ GOBRIDGE, GoLine,CleanDistant , FindBridge},
//	{ NOTHING, FindBridge, FindLine, FindBridge},
//	{ CROSSBRIDGE, FindBridge, PassBridge, GoLine},
//	{ NOTHING,  GoLine,    FindLine,  GoLine},
//	{ FINDCAR,  GoLine, CleanDistant, SendBall},
//	{ NOTHING, SendBall, StopToSendBall, SendBall},
	
//    { FLASEFINDCAR, SendBall, BackLine, GoLine},
//	{ RUNSTOP,  GoLine,    RunStop,  Stop },
//    { NOTHING,  Stop,      RunStop,  Stop},

    //如果出现新的代码加入在此
};
//*****************//
//
//函数作用：状态机注册
//
//****************//
void FSM_Regist(FSM_t* Pfsm, FsmTable_t* Ptable)
{
    Pfsm->PfsmTable = Ptable;
}
//*****************//
//
//函数作用：状态机状态迁移
//
//****************//
void FSM_StateTransfer(FSM_t* Pfsm, int State)
{
    Pfsm->CurState = State;
}

void LogicThing(void)
{
    static uint8 LenthSingal;
    FSM_Regist(&Car_Fsm, Car_Table);
    if(StartSingal == 0)
    {
        Car_Fsm.CurState = OutGarage;
        StartSingal = 1;
    }
    Car_Fsm.Size = sizeof(Car_Table) / sizeof(FsmTable_t);
    //&& (ADCvalue(1) >= 500 || ADCvalue(3) >= 500)
    if((ADCvalue(2) >= ADCvalueC && (ADCvalue(1) >= ADCvalueCL || ADCvalue(3) >= ADCvalueCR)   && (ADCvalue(0) > ADCvalueLL || ADCvalue(4) > ADCvalueRR)) && ReturnFSMState(&Car_Fsm) == GoLine)
        //	if(ADCvalue(2)>=3000)
    {

        RoundaboutSingal++;
        if(RoundaboutSingal >= 3)
        {
            ips114_showfloat(100, 4, 233, 4, 4);
            //StopRunAndProgram();
            //PRINTF("%d\r\n",CntAR);
            //PRINTF("FIND AR\r\n");
            if(ADCvalue(1) > ADCvalue(3))
            {
                LRAFlag = 1;
                RRAFlag = 0;
            }
            else
            {
                LRAFlag = 0;
                RRAFlag = 1;
            }
            //ips114_showstr(0,20,"cri");
            InitGYRORollAngle(InRAngle);   //70
            //_NowGyroYawAngle=-0;
            CleanDistant();
            InitCulAngle();
            OutRAroll = roll_value;
            FSM_EventHandle(&Car_Fsm, FindRoundabout);
            CntAR++;
            OneIN = 0;
        }
    }
    else if(GetDistant(0) > 0.8 && ReturnFSMState(&Car_Fsm) == InRoundabout)
    {
        //StopRunAndProgram();
        //PRINTF("END IN AR\r\n");
        ClearValue();
        FSM_EventHandle(&Car_Fsm, ENDINROUNDABOUT);

    }
    //else if(CulAngle() >= 420 && ReturnFSMState(&Car_Fsm) == PassRoundabout)
    else if(CulAngle() >= 360 && ReturnFSMState(&Car_Fsm) == PassRoundabout)
    {
        StopRunAndProgram();
        //StopRunAndProgram();
        //PRINTF("Begin Out\r\n");
//				if(PassAR==1)
        //_NowGyroYawAngle = OutRAroll + 20 ;
        InitGYRORollAngle(OutRAroll - OutRALeftAngle);
        ClearValue();
        FSM_EventHandle(&Car_Fsm, OutRoundabout);
        PassAR = 1;
        //CleanDistant();

    }
    else if(GetDistant(0) > 1 && ReturnFSMState(&Car_Fsm) == OutingRoundabout && PassAR == 1)
    {
        ClearValue();
        //PRINTF("End Out\r\n");
        FSM_EventHandle(&Car_Fsm, ENDOUTROUNDABOUT);
    }
    else
        //else if(ReturnFSMState(&Car_Fsm) == OutingRoundabout || ReturnFSMState(&Car_Fsm) == PassRoundabout || ReturnFSMState(&Car_Fsm) == InRoundabout)
    {

        //PRINTF("NOTHING\r\n");
        //ips114_clear(WHITE);
        RoundaboutSingal = 0;
        FSM_EventHandle(&Car_Fsm, NOTHING);
        //CleanDistant();
    }
//////		else if(GetDistant()>0.6 && ReturnFSMState(&Car_Fsm) == OutGarage)
    if(ReturnFSMState(&Car_Fsm) == OutGarage)
    {
        if(GetDistant(0) > 0.5 )
        {
            CleanDistant();
            FSM_EventHandle(&Car_Fsm, GOOUT);

        }
        else
        {
            FSM_EventHandle(&Car_Fsm, NOTHING);
            //CleanDistant();
        }
    }
    if(GetLaserDistant() <= 1.6 && ReturnFSMState(&Car_Fsm) == GoLine &&	GetDistant(1)>8 )  //出发开始的屏蔽距离
    {
        if(CarFlag < 3)
        {
            if(LastLaserDistant <= GetLaserDistant())
            {
                LenthSingal++;
                if(LenthSingal >= 2)
                {
                    LenthSingal = 0;
                    CarFlag++;
                }
            }
            else
            {
                LenthSingal = 0;
            }
        }
        else if(CarFlag >= 3)
        {
            if(CloseSingal == 0)
            {

//                StopRunAndProgram();
                FSM_EventHandle(&Car_Fsm, GOBRIDGE);
                CloseSingal++;
                CarFlag = 0;
            }
            else
            {
//                StopRunAndProgram();
                FSM_EventHandle(&Car_Fsm, FINDCAR);
            }

        }
        else
        {   //CarFlag=0;
            //FSM_EventHandle(&Car_Fsm, NOTHING);
        }
        LastLaserDistant = GetLaserDistant();
    }
    else
    {
        CarFlag = 0;
    }


    if(ReturnFSMState(&Car_Fsm) == FindBridge && GetDistant(0) <= 2.4)  //识别到桥到过桥的屏蔽距离
    {
        //FSM_EventHandle(&Car_Fsm, NOTHING);
    }
    else if(ReturnFSMState(&Car_Fsm) == FindBridge && GetDistant(0) > 2.4)
    {
        //StopRunAndProgram();
        FSM_EventHandle(&Car_Fsm, CROSSBRIDGE);

    }
    if(ReturnFSMState(&Car_Fsm) == SendBall)
    {
        //FSM_EventHandle(&Car_Fsm, NOTHING);
    }

    //FSM_EventHandle(&Car_Fsm, NOTHING);
}

void FSM_EventHandle(FSM_t* Pfsm, int Event)
{
    FsmTable_t* pActTable = Pfsm->PfsmTable;
    void (*eventActFun)() = NULL;  //函数指针初始化为空
    int NextState;
    int CurState = Pfsm->CurState;
    int g_max_num = Pfsm->Size;
    int flag = 0; //标识是否满足条件
    int i;

    /*获取当前动作函数*/
    for (i = 0; i < g_max_num; i++)
    {
        //当且仅当当前状态下来个指定的事件，我才执行它
        if (Event == pActTable[i].event && CurState == pActTable[i].CurState)
        {
            flag = 1;
            eventActFun = pActTable[i].eventActFun;
            NextState = pActTable[i].NextState;
            break;
        }
    }


    if (flag) //如果满足条件了
    {
        /*动作执行*/
        if (eventActFun)
        {
            eventActFun();
        }

        //跳转到下一个状态
        FSM_StateTransfer(Pfsm, NextState);
    }
    else
    {
        //printf("there is no match\n");
    }
}


void RunStart(void)
{
    MotorUserHandle(LMotor_F, 30);
    MotorUserHandle(RMotor_F, 30);
}
void RunStop(void)
{
    SetMotorPWM(RMotor_B, 0);
    SetMotorPWM(LMotor_F, 0);
    SetMotorPWM(LMotor_B, 0);
    SetMotorPWM(RMotor_F, 0);
    PRINTF("STOP");

}

int ReturnFSMState(FSM_t* Pfsm)
{
    return Pfsm->CurState;
}
void FindLine(void)
{
    static float LLPWM, LRPWM;
    float test;
    PIDValue =  GetPid(FuseMidLine, 1000 * MidLineFuseNum, FidLP, FidLI, FidLD); //54 0 35000  56.8 0 10500
//    if(TenSingal>=5)   (GetSpeed()/1.3)*
//		PIDValue = 0-PIDValue;
//		if((GetDistant(2)>7.5 &&GetDistant(2)<8.5)||(GetDistant(2)>9.5 &&GetDistant(2)<10.5))
//		{
//			LPWM = 10.5 - PIDValue;
//		    RPWM = 10.5 + PIDValue;
//		}
//		else
//		{
    LPWM = LeftDeadZone - PIDValue;
    RPWM = RightDeadZone + PIDValue;
//		}

    if(LPWM >= 40)
        LPWM = 40;
    else if(LPWM <= -40)
        LPWM = -40;
    if(RPWM >= 40)
        RPWM = 40;
    else if(RPWM <= -40)
        RPWM = -40;
    MotorUserHandle(LMotor_F, LPWM);
    MotorUserHandle(RMotor_F, RPWM);

}
void ADCulMidLine(void)
{
    float_t Lsqrt, Rsqrt, t1, t2;
    arm_sqrt_f32(ADCvalue(0), &Lsqrt);
    arm_sqrt_f32(ADCvalue(4), &Rsqrt);
    if(ADCvalue(0) + ADCvalue(4) == 0)
    {
        MidLineFuseNum = 0;
    }
    else
        MidLineFuseNum = (Lsqrt - Rsqrt) / (ADCvalue(0) + ADCvalue(4));
}
void PassCross(void)
{

}
void StopToSendBall(void)
{
	static uint8_t xxx=0;
//	static uint32 temp = 0;
	FindLineAdjPWM(0.01, 0, 0);
	if(!xxx)
	{
		TwoCarCount = 0;
		xxx = 1;
	}
//		systick_start();
//	temp += systick_getval_ms();
	if(/*GetDistant(0) >= 0.8 ||*/ TwoCarCount == 250 /*//延迟时间可减小，目前为2500ms aaaaaaaaaaaaa|| (GetSpeed() <= 0.3 && GetSpeed() >= -0.3 && temp >= 3000)*/)
	{
		GiveBall();
		StopRunAndProgram();
	}
}
	
//	FindLineAdjPWM(0.15, 0, 0);
//	if(GetLaserDistant() == 0.3)
//	{
//		GiveBall();
//		StopRunAndProgram();
//	}
//	StopRunAndProgram();
//	if(GetLaserDistant() <= 0.1)
//		FindLineAdjPWM(-0.8, 0, 0);
//	else if(GetLaserDistant() <= 0.8)
//		FindLineAdjPWM(-0.5, 0, 0);
//	else if(GetLaserDistant() <= 1.5)
//		FindLineAdjPWM(0.5, 0, 0);
//	else if(GetLaserDistant() == 0.3)
//	{
//		GiveBall();
//		StopRunAndProgram();
//	}
//	int i = 0;
//	i++;
//	if(fabs(GetSpeed()-1) >= 0.1)
//	{
//		FindLineAdjBasePWM(SpeedPID(3500,500,500,0.8));
//	}
//	if(GetSpeed() >= 0.35)
//		FindLineAdjPWM(-1.2, 0, 0);
//	else if( GetLaserDistant() > 0.3)
//	{
//		FindLineAdjPWM(0.2, 0, 0);
//		if(i >= 300000000)
//		{
//			GiveBall();
//			StopRunAndProgram();
//		}
//	}
//	{
		//FindLineAdjPWM(0.2, 0, 0);
//		if(GetSpeed() <= 0.02 && GetSpeed() >= -0.02)
//		{
//			GiveBall();
//			StopRunAndProgram();
//		}
//	}
//目前	
//	if(GetSpeed() >= 0.3)
//	{
//		if(GetLaserDistant() < 0.6 && GetLaserDistant() >= 0.4)
//			FindLineAdjPWM(-0.1, 0, 0);
//		else if(GetLaserDistant() < 1 && GetLaserDistant() >= 0.6)
//			FindLineAdjPWM(-0.3, 0, 0);
//		else
//			FindLineAdjPWM(-0.5, 0, 0);
//	}
//	else
//		FindLineAdjPWM(0.5, 0, 0);
//	if(GetSpeed() <= 0.005 && GetSpeed() >= -0.005)
//	{
//		GiveBall();
//		StopRunAndProgram();
//	}
	
	
//    if(GetLaserDistant() < 1.6 && GetLaserDistant() >= 1.5)   //寻找距离
//    {
//        if(GetSpeed() >= 0.8)
//        {
//            FindLineAdjPWM(-5, 0, 0);
//            FindLineAdjPWM(-5, 0, 0);
//        }
//    }
//    else if(GetLaserDistant() < 1.5 && GetLaserDistant() > 0.5)
//    {
////        if(Pitch_value < 40/*-160*/)
////        {
//            if((fabs(GetLaserDistant() - 0.4)) > 0.1)
//            {
//                FindLineAdjBasePWM(LaserDistantPID(6000, 1, 100000, 0.4));
//                CleanDistant();
//            }
//            else
//            {
//                if(GetLaserDistant() <= 0.4)
//                {
//                    FindLineAdjBasePWM(5);
//					if(GetSpeed() < 0.1 && GetSpeed() > -0.1)
//					{
//						GiveBall();
//						StopRunAndProgram();
//					}
//                }
//                else
//                {
//                    FindLineAdjBasePWM(5);
//                }
//            }
//        }
//        else
//        {
//            FindLineAdjBasePWM(5);
//        }
//}	
	
//    static int time;
//    float DIS;
//    //PRINTF("Send Ball");
//    DIS = GetDistant(0);
//    if(time == 0)
//    {
//        if(fabs(GetSpeed()-1.5) >= 0.1)
//        {
//					FindLineAdjBasePWM(SpeedPID(3500,500,500,0.8));
//        }
//        else
//        {
//            //StopRunAndProgram();
//            time++;
//        }
//    }
//		else if(time ==1)
//		{
//			   if(fabs(GetSpeed()-0.8) >= 0.1)
//        {
//FindLineAdjBasePWM(SpeedPID(3500,500,500,0.8));
//        }
//        else
//        {
//            //StopRunAndProgram();
//            time++;
//        }
//		}
//    else if(time == 2)
//    {
//        if(Pitch_value < -172)
//        {
//            if((fabs(GetLaserDistant() - 0.1)) > 0.05)
//            {
//                FindLineAdjBasePWM(LaserDistantPID(7000, 1, 100000, 0.1));
//                CleanDistant();
//            }
//            else
//            {
//                if(GetDistant(0) <= 0.05)
//                {
//                    FindLineAdjBasePWM(5);
//                }
//                else if(GetDistant(0) > 0.05)
//                {
//                    GiveBall();
//                    StopRunAndProgram();
//                }
//                else
//                {
//									CleanDistant();
//                    FindLineAdjBasePWM(5);
//                }
//            }
//        }
//        else
//        {
//            FindLineAdjBasePWM(0);
//        }
//    }


//}
void GiveBall(void)
{
	static int i = 0;
	static int flag = 0;
    uint8 chr[2] = {0x01, 0xff};
    gpio_set(D13, 1);
    gpio_set(D14, 1);
    gpio_set(D15, 1);
    while(1)
    {
		if(i == 0)
		{
			for(i=0; i<11; i++)
			{
				uart_putbuff(USART_8, chr, 2);
			}
		}		
        MotorUserHandle(LMotor_F, 0);
        MotorUserHandle(RMotor_F, 0);
    }
}
void BackLine(void)
{
    CarFlag = 0;
}
void GoOutGarage(void)
{
    static float cut, cnt = 0;
    cut = GetDistant(0);
    if(cut <= StraightLineOutGarage)
    {
        GYROPID(OutGarageGyroKpStraightLineKP, OutGarageGyroKpStraightLineKI, OutGarageGyroKpStraightLineKD);
    }
    else if(cut > StraightLineOutGarage && cut <= 0.5)
    {
        if(cnt == 0)
        {
            InitGYRORollAngle(OutGarageAngle);
            cnt++;
        }
        GYROPID(OutGarageGyroKpCStraightLineKP, OutGarageGyroKpCStraightLineKI, OutGarageGyroKpCStraightLineKD);
    }
}
void InRoundaboutProcess(void)
{
    static uint8 abc = 0, temp1 = 0;
    float DIS ;
    DIS = fabs(GetDistant(0));
    //FindLineAR();
    if(GetSpeed() >= 0.5 && temp1 == 0) //0.2
    {
        FindLineAdjPWM(SpeedDownInAngle, 0, 0);
        temp1 = 1;
        //FindLineAdjPWM(8.5,0, 0);
        //FindLineAR(15.5,0,0);
        //FindLineAdjPWM(10);
        //MotorUserHandle(LMotor_F, -20);
        //MotorUserHandle(RMotor_F, -20);
        //GYROPID(35, 0.1, 98);
        //PRINTF("1");
        //GYROPID(1, 0.1, 98);

    }
//				else if(DIS > 0 && DIS <= 0.1)
//				{
//					FindLineAdjPWM(15.5,0,1.8);
//				}
    if(temp1 == 1)
    {
        if(DIS > 0 && DIS <= StraightLineInRA)   //0.2 0.4
        {
            FindLineAdjPWM(SpeedStraightInRA, LSpeedStraightInRA, RSpeedStraightInRA);
            //FindLineAdjPWM(15.5, 0, 3.5);
            //StopRunAndProgram();
//            MotorUserHandle(LMotor_F, 10);
//            MotorUserHandle(RMotor_F, 0);
            //PRINTF("2");

            //GYROPID(195, 0, 800);  //150  800
        }//45 0.1 95

        else if(DIS > StraightLineInRA && DIS <= GYROLineInRA)
        {
            GYROPID(InRAGyroKp, InRAGyroKi, InRAGyroKd); //150  800
        }
        else if(DIS > GYROLineInRA && DIS < 0.8)
        {
            FindLine();
        }
    }
//    }
}
void OutRoundaboutProcess(void)
{
    float DIS ;
    DIS = fabs(GetDistant(0));
    if(DIS <= 0.1)
    {
        FindLineAdjPWM(SpeedDownOutAngle, 0, 0);
    }
    else if(DIS < 0.1 && DIS <= GYROLineOutRA)
        GYROPID(OutRAGyroKp, OutRAGyroKi, OutRAGyroKd);
    //FindLineAdjPWM(15.5, 0.5, 0);
    //FindLine();
    else if(DIS > GYROLineOutRA && DIS <= 0.6)
    {
        //StopRunAndProgram();
        FindLine();
        //GYROPID(55, 0.1, 95);
        //StopRunAndProgram();
        //FindLineAdjPWM(15.5, 0, 0);

    }
    else
    {
        FindLine();
        //FindLineAdjPWM(15.5, 0, 0.3);
    }
//        if(GetDistant() <= 0.2)
//        {
//					MotorUserHandle(LMotor_F, 5);
//					MotorUserHandle(RMotor_F, 25);
//            //GYROPID(55, 0.1, 98);

//
//        }
//				else if(GetDistant() > 0.2)
//				{
//					MotorUserHandle(LMotor_F, 15);
//					MotorUserHandle(RMotor_F, 15);

}
void ADCulARLine(void)
{
    float_t Lsqrt, Rsqrt, t1, t2;
    arm_sqrt_f32(ADCvalue(1), &Lsqrt);
    arm_sqrt_f32(ADCvalue(3), &Rsqrt);
    if(ADCvalue(1) + ADCvalue(3) == 0)
    {
        ARFuseNum = 0;
    }
    else
        ARFuseNum = (Lsqrt - Rsqrt) / (ADCvalue(1) + ADCvalue(3));
}
void FindLineAR(float PWM, float Lcut, float Rcut)
{
    static float LLPWM, LRPWM;
    float test;
    PIDValue =  GetPid(-0.002763617550954, 1000 * ARFuseNum, 40, 0, 4000); //54 0 35000  56.8 0 10500
    LPWM = PWM + PIDValue + Lcut;
    RPWM = PWM - PIDValue + Rcut;
    if(LPWM >= 40)
        LPWM = 40;
    else if(LPWM <= -40)
        LPWM = -40;
    if(RPWM >= 40)
        RPWM = 40;
    else if(RPWM <= -40)
        RPWM = -40;
    MotorUserHandle(LMotor_F, LPWM);
    MotorUserHandle(RMotor_F, RPWM);
}
void FindLineAdjPWM(float PWM, float Lcut, float Rcut)
{
    static float LLPWM, LRPWM;
    float test;
    PIDValue =  GetPid(FuseMidLine, 1000 * MidLineFuseNum, 6, 0.1, 2000);
    //PIDValue =  GetPid(-0.002763617550954, 1000 * MidLineFuseNum, 41, 0, 3300); //54 0 35000  56.8 0 10500
    if(PWM >= 0)
    {
        LPWM = PWM - PIDValue + Lcut;
        RPWM = PWM + PIDValue + Rcut;
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
void PassBridge(void)
{
    FindLine();
    //StopRunAndProgram();
}
void FindLineAdjBasePWM(float PWM)
{
    static float LLPWM, LRPWM;
    float test;
    PIDValue =  GetPid(FuseMidLine, 1000 * MidLineFuseNum, 12, 0, 2100);

    //PIDValue =  GetPid(-0.002763617550954, 1000 * MidLineFuseNum, 41, 0, 3300); //54 0 35000  56.8 0 10500
    if(PWM >= 0)
    {
        LPWM = PWM - PIDValue ;
        RPWM = PWM + PIDValue ;
    }
    else if(PWM < 0)
    {
        LPWM = PWM + PIDValue;
        RPWM = PWM - PIDValue;
    }
    if(LPWM >= 20)
        LPWM = 20;
    else if(LPWM <= -20)
        LPWM = -20;
    if(RPWM >= 20)
        RPWM = 20;
    else if(RPWM <= -20)
        RPWM = -20;
    MotorUserHandle(LMotor_F, LPWM);
    MotorUserHandle(RMotor_F, RPWM);
}