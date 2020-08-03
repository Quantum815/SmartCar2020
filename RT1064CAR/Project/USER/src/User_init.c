#include "User_init.h"
void UserInit(void)
{
	usb_cdc_init();	
	#ifdef USECARMER
	//mt9v03x_csi_init();   //初始化摄像头
	scc8660_csi_init();
	#endif
	gpio_init(B9,GPO,1,GPIO_PIN_CONFIG);// rgb启动
	gpio_init(D13,GPO,0,GPIO_PIN_CONFIG);	
	gpio_init(D14,GPO,0,GPIO_PIN_CONFIG);
	gpio_init(D15,GPO,0,GPIO_PIN_CONFIG);	
	//超声波测距外部中断初始化 超声波使用D15 以及PIT CH3
	//gpio_interrupt_init(D15,BOTH,GPIO_INT_CONFIG);
	
	ADCinit();
	pit_init();
	pit_interrupt_ms(PIT_CH1,10); //用led显示系统板存活
	pit_interrupt_ms(PIT_CH0,10);  //主进程
	pit_interrupt_ms(PIT_CH2,5);  //计算距离
	
	//PIT CH3 已经被超声波测距使用
	//pit_interrupt_us(PIT_CH3,60000);
	
	BOARD_InitDebugConsole();
	//DebugUARTInit();
	TwoCarUart();
	//TFminiUartInit();
	VL53L1UartInit();
	EnCodeInit();
	MotorInit();
	GyroInit();
	ips114_init();

	SetMotorPWM(LMotor_F, 1);
	SetMotorPWM(LMotor_B, 1);
	SetMotorPWM(RMotor_F, 1);
	SetMotorPWM(RMotor_B, 1);
	CleanDistant();
	InitGYRORollAngle(0);
	NVIC_SetPriority(PIT_IRQn,1);
}