#include "User_Gyro_IIC.h"
//#include "arm_math.h"
#define I2C_ARR 0x50
#define AX 0x34
uint8 GyroAngle[24];
int check=0;

double Pitch_value,yaw_value,roll_value,a_1,a_2,a_3,_NowGyroYawAngle,AngleAdd,LastAngle;
float GYROerror = 0;


short CharToShort(unsigned char cData[])
{
	return ((short)cData[1]<<8)|cData[0];
}
void GyroInit(void)
{
iic_init(IIC_2, IIC2_SDA_C5, IIC2_SCL_C4,400*1000);//硬件IIC初始化    波特率为400khz 
}
void GyroReadByte(void)
{
	//aaa=iic_write_reg(IIC_2,0x50,0x34,0x01);
	check=iic_read_reg_bytes(IIC_2,I2C_ARR,AX,&GyroAngle[0],24);
	Pitch_value =  (float)CharToShort(&GyroAngle[18])/32768.0*180;         
	yaw_value =((float)CharToShort(&GyroAngle[20])/32768.0*180); 
	roll_value =((float)CharToShort(&GyroAngle[22])/32768.0*180); 
	//roll_value =((float)CharToShort(&GyroAngle[22])/32768.0*180);
	a_1  =  (float)CharToShort(&GyroAngle[0])/32768.0*16;         
	a_2  =  ((float)CharToShort(&GyroAngle[2])/32768.0*16); 
	a_3  =  ((float)CharToShort(&GyroAngle[4])/32768.0*16); 
	DealRoll();
}


void DealRoll(void)
{
	//roll_value= -roll_value;
    if(roll_value < 0)
    {
        roll_value = roll_value + 360;
    }
}
double GetGYROError(void)
{
    if (_NowGyroYawAngle < 180)
    {
        if (roll_value > 180)
        {
            if (fabs(roll_value - _NowGyroYawAngle) <= 180)
            {
                return (roll_value - _NowGyroYawAngle);
            }
            else

                return (-(_NowGyroYawAngle + 360 - roll_value));
        }
        else
            return (roll_value - _NowGyroYawAngle);
    }
    else
    {
        if (roll_value < 180)
        {
            if (fabs(roll_value - _NowGyroYawAngle) <= 180)
            {
                return (roll_value - _NowGyroYawAngle);
            }
            else

                return ((roll_value + 360) - _NowGyroYawAngle);
        }
        else if (fabs(roll_value - _NowGyroYawAngle) <= 180)
        {
            return (roll_value - _NowGyroYawAngle);
        }
        else
            return ((roll_value + 360) - _NowGyroYawAngle);
    }
}
void InitGYRORollAngle(float Angle)
{
	_NowGyroYawAngle=roll_value+Angle;
	if(_NowGyroYawAngle>=360)
		_NowGyroYawAngle-=360;
	if(_NowGyroYawAngle<0)
_NowGyroYawAngle+=360;
}
void GYROPID(float KP,float KI,float KD)
{
		
    //float Kp = 35, Ki = 0.01, Kd = 95;
    float  P = 0, I = 0, D = 0, PID_value = 0,LO,RO;
		static double previous_error = 0;
    GYROerror = (float)GetGYROError();
    //PRINTF("%f\n", GYROerror);
    P = GYROerror;
    I = I + GYROerror;
    D = GYROerror - previous_error;
    PID_value = (KP * P) + (KI * I) + (KD * D);
    previous_error = GYROerror;
    PID_value = PID_value/1000;
		LO=8.5+PID_value;
		RO=8.5-PID_value;
		if(LO>=40)
			LO=40;
		else if(LO<=-40)
			LO=-40;
		if(RO>=40)
			RO=40;
		else if(RO<=-40)
			RO=-40;
		MotorUserHandle(LMotor_F,LO);
		MotorUserHandle(RMotor_F,RO);
		
	//return PID_value;
}
void GyroErrorCheck(void)
{
	if(check==1)
	{
		ips114_showstr(100,3,"GyroError");
		GyroInit();
	}
	else if(check==0)
	{
		ips114_clear(WHITE);
		check=2;
	}
}
double CulAngle(void)
{
	return AngleAdd;
}
void InitCulAngle(void)
{
	AngleAdd=0;
	LastAngle=roll_value;
}
void UpdateCulAngle(void)
{
	//float temp;
	AngleAdd+=fabs(GetGYROCulError());
	LastAngle=roll_value;
}
double GetGYROCulError()
{
	    if (LastAngle < 180)
    {
        if (roll_value > 180)
        {
            if (fabs(roll_value - LastAngle) <= 180)
            {
                return (roll_value - LastAngle);
            }
            else

                return (-(LastAngle + 360 - roll_value));
        }
        else
            return (roll_value - LastAngle);
    }
    else
    {
        if (roll_value < 180)
        {
            if (fabs(roll_value - LastAngle) <= 180)
            {
                return (roll_value - LastAngle);
            }
            else

                return ((roll_value + 360) - LastAngle);
        }
        else if (fabs(roll_value - LastAngle) <= 180)
        {
            return (roll_value - LastAngle);
        }
        else
            return ((roll_value + 360) - LastAngle);
    }
}