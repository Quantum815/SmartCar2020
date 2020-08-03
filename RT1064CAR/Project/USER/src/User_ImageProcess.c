#include "User_ImageProcess.h"
int x1, x2, x3, x4;
double MidLineFuseNum;
int CloseThresholds;
int FarThresholds;
uint8 ProcessImageFlag = 0;
uint8 DisplayIMAG[MT9V03X_CSI_H][MT9V03X_CSI_W], OSTUIMAG[15][MT9V03X_CSI_W];
uint8 LeftLine[MT9V03X_CSI_H], RightLine[MT9V03X_CSI_H], MidLine[MT9V03X_CSI_H];
uint8 RValue,GValue,BValue;
int RedNum,GreenNum,BlueNum;
//void ImagePretreatment(void)
//{
//    for (int i = 0; i <= MT9V03X_CSI_H - 1; i++)
//    {
//        for(int j = 0; j <= MT9V03X_CSI_W - 1; j++)
//        {

//            if((i <= 50 && (j <= 50 || j >= 138)) || (i >= 70 && (j <= 50 || j >= 138)))
//            {
//                DisplayIMAG[i][j] = mt9v03x_csi_image[i][j] + 0;
//            }

//        }
//    }
//    for(int i = 15; i <= (MT9V03X_CSI_H - 1) - 15; i++)
//    {
//        for(int j = 0; j <= (MT9V03X_CSI_W - 1); j++)
//        {
//            if(i >= 50)
//            {
//                if(mt9v03x_csi_image[i][j] <= CloseThresholds)
//                {
//                    DisplayIMAG[i][j] = 0;
//                }
//                else
//                {
//                    DisplayIMAG[i][j] = 255;
//                }
//            }
//            else
//            {
//                if(mt9v03x_csi_image[i][j] <= FarThresholds)
//                {
//                    DisplayIMAG[i][j] = 0;
//                }
//                else
//                {
//                    DisplayIMAG[i][j] = 255;
//                }
//            }
//        }
//    }

//}
//void FindMedLine(void)
//{
//    for (int i = (MT9V03X_CSI_H - 1) - 15; i >= 15; i--)
//    {
//        if(i >= (MT9V03X_CSI_H - 1) - 20)
//        {
//            for (int j = 0; j <= MT9V03X_CSI_W - 1; j++)
//            {
//                if (DisplayIMAG[i][j] == 255)
//                {
//                    x1 = j;
//                    LeftLine[i] = j;
//                    break;
//                }
//                else if(j == 187)
//                {
//                    LeftLine[i] = 187;
//                }
//            }
//            for(int k = MT9V03X_CSI_W; k >= 0; k--)
//            {
//                if(DisplayIMAG[i][k] == 255)
//                {
//                    x2 = k;
//                    RightLine[i] = k;
//                    break;
//                }
//                else if(k == 0)
//                {
//                    RightLine[i] = 0;
//                }
//            }
//            //DisplayIMAG[i][(int)((x1 + x2) / 2)] = 0;
//            MidLine[i] = (int)((x1 + x2) / 2);
//        }
//        else
//        {
//            for (int f = ((int)((x1 + x2) / 2)); f >= 0; f--)
//            {
//                if (DisplayIMAG[i][f] == 0)
//                {
//                    LeftLine[i] = f;
//                    x3 = f;
//                    break;
//                }
//                else if(f == 0)
//                {
//                    LeftLine[i] = 0;
//                }
//            }
//            for (int g = (int)((x1 + x2) / 2); g <= MT9V03X_CSI_W - 1; g++)
//            {
//                if (DisplayIMAG[i][g] == 0)
//                {
//                    x4 = g;
//                    RightLine[i] = g;
//                    break;
//                }
//                else if(g == 187)
//                {
//                    RightLine[i] = 187;
//                }
//            }
//            //DisplayIMAG[i][(int)((x3 + x4) / 2)] = 0;

//            if(x4 == 188 && x3 == 0)
//            {
//                x2 = x4;
//                x1 = x3;
//            }
//            if(((x3 + x4) / 2) - ((x1 + x2) / 2) < 5 || ((x3 + x4) / 2) - ((x1 + x2) / 2) > -5)
//            {
//                x2 = x4;
//                x1 = x3;
//            }
//            MidLine[i] = (int)((x1 + x2) / 2);
//        }
//    }
//}
void TakePointColor(uint16 *dat, uint16 x, uint16 y, uint16 z, uint8 *r, uint8 *g, uint8 *b)
{
	  uint16 pixel;
    
    //获取指定坐标的像素数据
    pixel = dat[x+y*z];
    
    //因为R5G3是存储在低八位 G3B5是存储在高八位
    //因为我们先将位置进行交换，便于获取每个分量的数据
    pixel = ((pixel&0xff)<<8) |(pixel>>8);
    
    *r = pixel>>11;
    *g = (pixel>>5)&0x3f;
    *b = pixel&0x1f;
}
void UpDateRedNnm(void)
{
	RedNum=0;GreenNum=0;BlueNum=0;
	for(int i=0;i<SCC8660_CSI_PIC_H;i++)
	{
		for(int j=0;j<SCC8660_CSI_PIC_W;j++)
		{
			TakePointColor(scc8660_csi_image[0],i, j, SCC8660_CSI_PIC_W, &RValue,&GValue,&BValue);
			if(RValue>= 29&& GValue<= 45 && BValue<26)
			{
				RedNum++;
			}
			else if(RValue<=5 && GValue>=50 && BValue<=5)
			{
				GreenNum++;
			}
			else if(RValue<=5 && GValue<=10 && BValue>=25)
			{
				BlueNum++;
			}
		}
	}
}
int ReturnColorNum(int Color)
{
	if(Color == MRED)
	{
		return RedNum;
	}
	else if(Color == MGREEN)
	{
		return GreenNum;
	}
	else if(Color == MBLUE)
	{
		return BlueNum;
	}
	else
	{
		return -1;
	}
}
void CameraProcess(void)
{
	int NUMRED;
	UpDateRedNnm();
//	if(mt9v03x_csi_finish_flag)
//	{
//		mt9v03x_csi_finish_flag=0;
//    ips114_displayimage032_zoom(mt9v03x_csi_image[0], MT9V03X_CSI_W, MT9V03X_CSI_H, 240, 135);
//		//seekfree_sendimg_03x_usb_cdc(mt9v03x_csi_image[0], MT9V03X_CSI_W, MT9V03X_CSI_H);
//	}
//    CloseThresholds = GetOSTU(mt9v03x_csi_image)+15;
//    FarThresholds = GetOSTU(mt9v03x_csi_image)+15;
//    ImagePretreatment();
//    FindMedLine_ADD();
//    //EdgePointFind();
//    MidLineFuseNum = GetMidLineNum();
//    ProcessImageFlag = 1;

//    for(int i = 85; i < 105; i++)
//    {
//        DisplayIMAG[i][MidLine[i]] = 0;
//    }
//      //ShowMidLine();
//NUMRED=ReturnColorNum(MRED);
//	if(NUMRED>=300)
//	{
//		StopRunAndProgram();
//	}
    //ips114_displayimage032_zoom(DisplayIMAG[0], MT9V03X_CSI_W, MT9V03X_CSI_H, 240, 135);
}
//void EdgePointFind(void)
//{
//    uint8 Rbp = 0, Lbp = 0;
//    for(int i = 105; i >= 15; i--)
//    {
//        if(RightLine[i] - RightLine[i - 1] >= 3 || RightLine[i] - RightLine[i - 1] <= -3)
//            Rbp = Rbp + 1;
//        if(LeftLine[i] - LeftLine[i - 1] >= 3 || LeftLine[i] - LeftLine[i - 1] <= -3)
//            Lbp = Rbp + 1;
//    }
//    if(Rbp + Lbp >= 4 || Rbp >= 2 || Lbp >= 2)
//    {
//        Rbp = 0;
//        Lbp = 0;
//        for(int i = 105; i >= 15; i--)
//        {
//            if(RightLine[i] - RightLine[i - 1] >= 5 || RightLine[i] - RightLine[i - 1] <= -5)
//            {
//                RightLine[i] = RightLine[i - 1] - 1;
//            }
//            if(LeftLine[i] - LeftLine[i - 1] >= 5 || LeftLine[i] - LeftLine[i - 1] <= -5)
//            {
//                LeftLine[i] = LeftLine[i - 1] + 1;
//            }
//        }
//        for(int i = 187; i >= 0; i--)
//        {
//            MidLine[i] = (int)((LeftLine[i] + RightLine[i]) / 2);
//        }
//    }
//}

//double GetMidLineNum(void)
//{
//    double ClearLineSum = 0, MidLineSum = 0, LongLineSum = 0;
//    double AllLineSum = 0;
//    for(int i = 15; i <= 105; i++)
//    {
//        if(i >= 15 && i <= 45)
//            LongLineSum += MidLine[i];
//        else if(i > 55 && i < 65)
//            MidLineSum += MidLine[i];
//        else if(i >= 85 && i <= 105)
//            ClearLineSum += MidLine[i];
//    }
//    AllLineSum = LongLineSum * 0  + MidLineSum * 0  + ClearLineSum ;
//    return AllLineSum / 20;

//}
//void ShowMidLine(void)
//{
//    uint8 ShowMidLineIMG[MT9V03X_CSI_H][MT9V03X_CSI_W] = {255};
//    for(int i = 0; i <= MT9V03X_CSI_H - 1; i++)
//    {
//        for(int j = 0; j <= MT9V03X_CSI_W - 1; j++)
//            ShowMidLineIMG[i][j] = 255;
//    }
//    for(int i = 90; i <= 105; i++)
//    {

//        ShowMidLineIMG[i][MidLine[i]] = 0;
//    }
//    ips114_displayimage032_zoom(ShowMidLineIMG[0], MT9V03X_CSI_W, MT9V03X_CSI_H, 240, 135);

//}
//void FindMedLine_ADD(void)
//{
//    //DisplayIMAG
//    float CountWhitePixels = 0, FirstWhitePixels, BlackFlag = 0;
//    int AllAddsum;
//    for(int i = 0; i <= MT9V03X_CSI_W - 1; i++)
//    {
//        for(int j = 0; j <= MT9V03X_CSI_W - 1; j++)
//        {
//            if(DisplayIMAG[i][j] == 255)
//            {
////				FirstWhitePixels=j;
//                CountWhitePixels++;
////				if(CountWhitePixels>=20)
////				{
////
////				}
//                AllAddsum += j;
//                BlackFlag = 0;

//            }
//            else
//            {
//                BlackFlag++;
//                if(BlackFlag == 5)
//                {
//                    if(CountWhitePixels <= 40)
//                    {
//                        AllAddsum = 0;
//                        CountWhitePixels = 0;
//                    }
//                }
//            }

//        }
//        MidLine[i] = (uint8)(AllAddsum / CountWhitePixels * 1.0);
//    }
//}
//void GetOSTUIMAG(void)
//{
//    for(int i = 0; i < 15; i++)
//    {
//        for(int j = 0; j < MT9V03X_CSI_W; j++)
//            OSTUIMAG[i][j] = mt9v03x_csi_image[i + 15][j];
//    }
//}
