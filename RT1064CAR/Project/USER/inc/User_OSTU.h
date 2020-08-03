#ifndef _USER_OSTU
#define _USER_OSTU
#include "headfile.h"

#define IMAGEH  MT9V03X_CSI_H //行 HEIGHT 
#define IMAGEW  MT9V03X_CSI_W  //列 WIDTH 

uint8_t GetOSTU(uint8_t tmImage[IMAGEH][IMAGEW]);
void BinaryImage(uint8_t tmImage[IMAGEH][IMAGEW],uint8_t ThresholdV);
void GyroReadByte(void);
#endif