/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2019,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：一群：179029047(已满)  二群：244861897
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		main
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		查看doc内version文件 版本说明
 * @Software 		IAR 8.3 or MDK 5.28
 * @Target core		NXP RT1064DVL6A
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2019-04-30
 ********************************************************************************************************************/

#include "headfile.h"       //没插摄像头需要define为0 不然程序会卡住define SHOWNUM
int RTIME=0;
float DIS;
uint8 cnt;
//#define SHOWNUM


int main(void)
{
	float_t Lsqrt, Rsqrt, t1, t2,MidLineFuseNum1,PIDValue1,OneIN=0;
	
    
    DisableGlobalIRQ();
    board_init();
    UserInit();
    EnableGlobalIRQ(0);
    //InitGYRORollAngle();
	//_NowGyroYawAngle=-20;
	InitCulAngle();
		CleanDistant();
	//_NowGyroYawAngle = 90;
    //gpio_init(B9,GPO,0,GPIO_PIN_CONFIG);
//			int i = 0;
    while (1)

    {
						//测试
//通讯测试
//		uart_putchar(USART_8,0x01);
//		uart_putchar(USART_8,0xff);
//		systick_delay_ms(1000);
//		    uint8 chr[2] = {0x01, 0xff};
//			if(i == 0)
//		for(i=0; i<20; i++)
//		{
//			uart_putbuff(USART_8, chr, 2);
//		}
		
//屏蔽距离测试
//		if(GetDistant(1) < 8)
//			FindLine();
//		else
//			StopRunAndProgram();
		
//		MotorUserHandle(RMotor_B, 0);
//	MotorUserHandle(LMotor_F, 20);
//		systick_delay_ms(2000);
//	MotorUserHandle(LMotor_B, 20);
//		systick_delay_ms(2000);
//		MotorUserHandle(LMotor_B, 0);
//	MotorUserHandle(RMotor_F, 20);
//		systick_delay_ms(2000);
//	MotorUserHandle(RMotor_B, 20);
//		systick_delay_ms(2000);
		
			//uart_putbuff(USART_1, chr, 2);
			//ADCreadData();
//			PRINTF("%f,%f",GYROerror,roll_value);
			//ADCreadData();
//			PRINTF("GYROerror=%f,roll_value=%f,LaserDistant=%f,SPEED=%f\r\n",GYROerror,roll_value,GetLaserDistant(),GetSpeed());
			ips114_showfloat(110,0,GYROerror,4,6);
			ips114_showfloat(110,1,Pitch_value,4,6);
			ips114_showfloat(110,2,yaw_value,4,6);
			ips114_showfloat(110,3,roll_value,4,6);
			ips114_showfloat(110,4,Distant[0],4,6);
			ips114_showfloat(110,5,Distant[1],4,6);
			ips114_showfloat(110,6,GetLaserDistant(),4,6);
		ShowNUMinDisplay();
//			DIS=GetDistant();
//			//FindLineAR();
//        if(DIS < 0)
//        {
//					//FindLineAR(15.5,0,0);
//					//FindLineAdjPWM(10);
            ///MotorUserHandle(LMotor_B, 20);
//            //MotorUserHandle(RMotor_F, -20);
//            //GYROPID(35, 0.1, 98);
//            //PRINTF("1");
//            //GYROPID(1, 0.1, 98);

//        }
//        else if(DIS >= 0 && DIS <= 0.5)
//        {
//					//FindLineAR(15.5,0,3.27);
//            //StopRunAndProgram();
////            MotorUserHandle(LMotor_F, 10);
////            MotorUserHandle(RMotor_F, 0);
//            //PRINTF("2");
//            if(OneIN == 0)
//            {
//                _NowGyroYawAngle = 90;
//                OneIN++;
//            }

//            GYROPID(35,0 , 95);
//        }
////        else if(GetDistant() > 0.4 && GetDistant() <= 0.5)
////        {
////            MotorUserHandle(LMotor_F, 14);
////            MotorUserHandle(RMotor_F, 17);
////            PRINTF("3");
////        }
////        else if(GetDistant() > 0.5 && GetDistant() <= 0.6)
////        {
////            MotorUserHandle(LMotor_F, 13);
////            MotorUserHandle(RMotor_F, 19);
////            PRINTF("4");
////        }
//        else if(DIS > 0.5 && DIS<0.8)
//        {
//            StopRunAndProgram();
//            FindLineAR(15.5,0,0.26);
//        }
			//PRINTF("%f\r\n",CulAngle());
//			    static uint8 abc = 0;
//			//FindLineAR();
//        if(GetDistant() <= 0.05)
//        {
////            MotorUserHandle(LMotor_F, 14);
////            MotorUserHandle(RMotor_F, 14);
//            GYROPID(35, 0.1, 98);
//            PRINTF("1");
//            //GYROPID(1, 0.1, 98);

//        }
//        else if(GetDistant() > 0.05 && GetDistant() <= 0.8)
//        {
//            StopRunAndProgram();
////            MotorUserHandle(LMotor_F, 15);
////            MotorUserHandle(RMotor_F, 17);
//            PRINTF("2");
//            if(cnt == 0)
//            {
//                _NowGyroYawAngle = -120;
//                cnt++;
//            }

//            GYROPID(45, 0.1, 95);
//        }
//        else if(GetDistant() > 0.4 && GetDistant() <= 0.5)
//        {
//            MotorUserHandle(LMotor_F, 14);
//            MotorUserHandle(RMotor_F, 17);
//            PRINTF("3");
//        }
//        else if(GetDistant() > 0.5 && GetDistant() <= 0.6)
//        {
//            MotorUserHandle(LMotor_F, 13);
//            MotorUserHandle(RMotor_F, 19);
//            PRINTF("4");
//        }
//        else if(GetDistant() > 0.8)
//        {
//            //StopRunAndProgram();
//            FindLine();
//        }
			    //uart_putbuff(USART_8,chr,2);
//    arm_sqrt_f32(ADCvalue(1), &Lsqrt);
//    arm_sqrt_f32(ADCvalue(3), &Rsqrt);
//		if(ADCvalue(1) + ADCvalue(3)==0)
//		{
//			MidLineFuseNum1=0;
//		}
//		else
//    MidLineFuseNum1 = (Lsqrt - Rsqrt) / (ADCvalue(1) + ADCvalue(3));
//		    PIDValue1 =  GetPid(-0.002763617550954, 1000 * MidLineFuseNum1, 56, 0, 9000); //54 0 35000
////    if(TenSingal>=5)   (GetSpeed()/1.3)*
////		PIDValue = 0-PIDValue;
//    LPWM = 10 + PIDValue1;
//    RPWM = 10 - PIDValue1;


//    if(LPWM >= 50)
//        LPWM = 50;
//    else if(LPWM <= -50)
//        LPWM = -50;
//    if(RPWM >= 50)
//        RPWM = 50;
//    else if(RPWM <= -50)
//        RPWM = -50;
//    //test=GetSpeed();
//    //PRINTF("%f\r\n",test);
//    //test=GetPid(0, 1000*MidLineFuseNum, 50, 0, 3900);
//    //PRINTF("L=%f     R=%f     \r\n",LPWM,RPWM);
//    //PRINTF("%f\r\n",test);
	//ips114_showfloat(100,0,DIS,4,4);
////    if(LLPWM - LPWM >= 5 || LLPWM - LPWM <= -5)
////    {
////        LPWM = LLPWM + (LLPWM - LPWM);
////    }
////    else if(LRPWM - RPWM >= 5 || LRPWM - RPWM <= -5)
////    {
////        RPWM = LRPWM + (LRPWM - RPWM);
////    }
////    LLPWM = LPWM;
////    LRPWM = RPWM;
//    MotorUserHandle(LMotor_F, LPWM);
//    MotorUserHandle(RMotor_F, RPWM);
		
//			        if(GetDistant() <= 1)
//        {
//            MotorUserHandle(LMotor_F, 16.5);
//            MotorUserHandle(RMotor_F, 16.5);

						
//            GYROPID(35, 0.1, 98);
//            //GYROPID(1, 0.1, 98);

//        }
//        else if(GetDistant() > 1 && GetDistant() <= 2)
//        {
//					//StopRunAndProgram();
//					MotorUserHandle(RMotor_F, 30);
//					MotorUserHandle(LMotor_F, 30);
//					systick_delay_ms(1000);
//								MotorUserHandle(RMotor_F, -30);
//					MotorUserHandle(LMotor_F, -30);
//		systick_delay_ms(2000);
//            if(cnt == 0)
//            {
//                _NowGyroYawAngle = -90;
//                cnt++;
//            }

//            GYROPID(35, 0.1, 95);
//        }
//        else if(GetDistant() > 0.8)
//        {
//					StopRunAndProgram();
//            FindLine();
//        }
//			if(scc8660_csi_finish_flag)
//			{
//				scc8660_csi_finish_flag=0;
//				//seekfree_sendimg_scc8660_usb_cdc((uint8 *)scc8660_csi_image[0],SCC8660_CSI_PIC_W,SCC8660_CSI_PIC_H);
//				ips114_displayimage8660_zoom(scc8660_csi_image[0], SCC8660_CSI_PIC_W, SCC8660_CSI_PIC_H, 160, 120);
//			}
			//cut=ReturnColorNum(MRED);
			//ips114_showint16(160,1,RTIME);
			//GyroErrorCheck();
//        #ifdef SHOWNUM
//        #endif
			//FindLine();
			//cut=CulAngle();
//      cnt = GetDistant();
//        if(cut <= 0.3)
//        {
//            GYROPID(25, 0.1, 98);
//        }
//        else if(cut > 0.3 && cut <= 1.2)
//        {
//            if(cnt == 0)
//            {
//                _NowGyroYawAngle = 90;
//                cnt++;
//            }
//            GYROPID(35, 0.1,95);
//        }
//        else if(cut > 1.2)
//        {
//            MotorUserHandle(LMotor_F, 50);
//            MotorUserHandle(RMotor_F, 50);
//						systick_delay_ms(2000);
//            MotorUserHandle(LMotor_F, -50);
//            MotorUserHandle(RMotor_F, -50);
//						systick_delay_ms(1000);
//            //CleanDistant();
//        }
				
//            MotorUserHandle(LMotor_F, 50);
//            MotorUserHandle(RMotor_F, 50);
//            MotorUserHandle(LMotor_B, 50);
//            MotorUserHandle(RMotor_B, 50);
        //GYROPID(0,0,0);
        //UpDateLaserDistant();
//		cut=GYROPID(0.35,0,2);
//			test1=LeftDeadZone+cut;
//			test2=RightDeadZone-cut;
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
//						MotorUserHandle(LMotor_F,20);
//			MotorUserHandle(RMotor_F,20);
        //MotorUserHandle(LMotor_F,LeftDeadZone);
        //MotorUserHandle(RMotor_F,RightDeadZone);
        //PRINTF("%f\r\n",cut);
        //test1=GYROPID(0,0,0,0);

//			test1=GetDistant();
//			test2=GetSpeed();
        //ips114_showuint8(140,20,DebugRx_Buffer);
        //PRINTF("%lf\r\n",GetSpeed());
        //systick_delay_ms(50);
//			ips114_showstr(20,0,"distant:");
//			ips114_showstr(20,20,"speed:");
				//while(1);
        //ips114_showfloat(70,20,RPWM,4,4);
        //pwm_init(PWM2_MODULE3_CHA_D2, 2000,25000);
        //UserDebug();
//			SetMotorPWM(LMotor_B,30);
//			SetMotorPWM(RMotor_B,50);
//			SetMotorPWM(LMotor_F,50);
//			SetMotorPWM(RMotor_F,30);

    }
}


//SetMotorPWM(LMotor_B,0);
//SetMotorPWM(RMotor_F,50);//向板子，左，向板子转
//SetMotorPWM(LMotor_B,50);//向板子，左，反向板子转
//SetMotorPWM(RMotor_B,50);//向板子，右，反向板子转
//SetMotorPWM(LMotor_F,50);//向板子，右，向板子转
//systick_delay_ms(1000);
//SetMotorPWM(RMotor_F,0);
//SetMotorPWM(RMotor_F,50);//向板子，左，向板子转
//SetMotorPWM(LMotor_B,50);//向板子，左，反向板子转
//SetMotorPWM(RMotor_B,50);//向板子，右，反向板子转
//SetMotorPWM(LMotor_F,50);//向板子，右，向板子转
//左右已经修正
//			test1=IsrCount;
//			CameraProcess();
//			test2=IsrCount;
//			cut=test2-test1;
//		if(mt9v03x_csi_finish_flag)
//	{
//		mt9v03x_csi_finish_flag=0;
//    //ips114_displayimage032_zoom(mt9v03x_csi_image[0], MT9V03X_CSI_W, MT9V03X_CSI_H, 240, 135);
//		seekfree_sendimg_03x_usb_cdc(mt9v03x_csi_image[0], MT9V03X_CSI_W, MT9V03X_CSI_H);
//	}
//			//gpio_toggle(D15);
//			//systick_delay_ms(1000);
//			//SetMotorPWM(LMotor_F,0);
//			//SetMotorPWM(RMotor_B,0);
//			SetMotorPWM(RMotor_F,50);//向板子，左，向板子转
//			SetMotorPWM(LMotor_B,50);//向板子，左，反向板子转
////			//SetMotorPWM(RMotor_B,50);//向板子，右，反向板子转
////			//SetMotorPWM(LMotor_F,50);//向板子，右，向板子转
//			//systick_delay_ms(1000);
//			//SetMotorPWM(LMotor_B,0);
//			//SetMotorPWM(RMotor_F,0);
//			SetMotorPWM(RMotor_B,50);//向板子，左，向板子转
//////
//			SetMotorPWM(LMotor_F,50);//向板子，左，反向板子转
//////SetMotorPWM(RMotor_B,50);//向板子，右，反向板子转
//////SetMotorPWM(LMotor_F,50);//向板子，右，向板子转
//////左右已经修正
////        //UserDebug();
////			SetServoPWM(1,50);
////			SetServoPWM(2,50);
////			SetServoPWM(3,50);
