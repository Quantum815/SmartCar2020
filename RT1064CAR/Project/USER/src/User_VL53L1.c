#include "User_VL53L1.h"
uint8 GetDistantMM[8] = {0x50, 0x03, 0x00, 0x34, 0x00, 0x01, 0xc8, 0x45};
float distant;
float GetDistantFRVL(void)
{
		unsigned short tmp=0x0000;
    uart_putbuff(USART_1, GetDistantMM, 8);
    while(LaserRecFlag!=1)
    {}
			if(CheckCRC())
			{
				tmp=((VL53L1RX_Data[3]|tmp)<<8)|VL53L1RX_Data[4];
				distant=(int)tmp;
				return distant/10.0;
			}
			else
			return -1;

}
int CheckCRC(void)
{
    unsigned short tmp = 0xffff;
		unsigned short RecCRC=0x0000;
		RecCRC=((VL53L1RX_Data[6]|RecCRC)<<8)|VL53L1RX_Data[5];
    for(int n = 0; n < 5; n++) {
        tmp = VL53L1RX_Data[n] ^ tmp;
        for(int i = 0; i < 8; i++) {
            if(tmp & 0x01) {
                tmp = tmp >> 1;
                tmp = tmp ^ 0xa001;
            }
            else {
                tmp = tmp >> 1;
            }
        }
    }
		if(tmp==RecCRC)
		{
			return 1;
		}
		else
		{
			return 0;
		}
		
}