/*
 * User_ImageProcess.c
 *
 *  Created on: 2020Äê7ÔÂ4ÈÕ
 *      Author: Quantum815
 */

#include <..\CODE\Inc\User_Image_Process.h>

int x1, x2, x3, x4;
double MidLineFuseNum;
uint8 Rbp = 0, Lbp = 0;
uint8 ProcessImageFlag = 0;
uint8 DisplayIMAG[MT9V03X_H][MT9V03X_W];
uint8 LeftLine[MT9V03X_H], RightLine[MT9V03X_H], MidLine[MT9V03X_H];

void ImagePretreatment(void)
{
    for (int i = 0; i <= MT9V03X_H - 1; i++)
    {
        for(int j = 0; j <= MT9V03X_W - 1; j++)
        {

            if((i <= 50 && (j <= 50 || j >= 138)) || (i >= 70 && (j <= 50 || j >= 138)))
            {
                DisplayIMAG[i][j] = mt9v03x_image[i][j] + 0;
            }

        }
    }
    for(int i = 0; i <= MT9V03X_H - 1; i++)
    {
        for(int j = 0; j <= MT9V03X_W - 1; j++)
        {
            if(i >= 50)
            {
                if(mt9v03x_image[i][j] <= CloseThresholds)
                {
                    DisplayIMAG[i][j] = 0;
                }
                else
                {
                    DisplayIMAG[i][j] = 255;
                }
            }
            else
            {
                if(mt9v03x_image[i][j] <= FarThresholds)
                {
                    DisplayIMAG[i][j] = 0;
                }
                else
                {
                    DisplayIMAG[i][j] = 255;
                }
            }
        }
    }

}
void FindMedLine(void)
{
    for (int i = 0; i <= MT9V03X_H - 1; i++)
    {
        if(i <= 10)
        {
            for (int j = 0; j <= MT9V03X_W - 1; j++)
            {
                if (DisplayIMAG[i][j] == 0)
                {
                    x1 = j;
                    LeftLine[i] = (uint8)j;
                    break;
                }
                else if(j == 187)
                {
                    LeftLine[i] = 187;
                }
            }
            for(int k = MT9V03X_W; k >= 0; k--)
            {
                if(DisplayIMAG[i][k] == 0)
                {
                    x2 = k;
                    RightLine[i] = (uint8)k;
                    break;
                }
                else if(k == 0)
                {
                    RightLine[i] = 0;
                }
            }
            //DisplayIMAG[i][(int)((x1 + x2) / 2)] = 0;
            MidLine[i] = (int)((x1 + x2) / 2);
        }
        else
        {
            for (int f = ((int)((x1 + x2) / 2)); f >= 0; f--)
            {
                if (DisplayIMAG[i][f] == 0)
                {
                    LeftLine[i] = (uint8)f;
                    x3 = f;
                    break;
                }
                else if(f == 0)
                {
                    LeftLine[i] = 0;
                }
            }
            for (int g = (int)((x1 + x2) / 2); g <= MT9V03X_W - 1; g++)
            {
                if (DisplayIMAG[i][g] == 0)
                {
                    x4 = g;
                    RightLine[i] = (uint8)g;
                    break;
                }
                else if(g == 187)
                {
                    RightLine[i] = 187;
                }
            }
            //DisplayIMAG[i][(int)((x3 + x4) / 2)] = 0;

            if(x4 == 188 && x3 == 0)
            {
                x2 = x4;
                x1 = x3;
            }
            if(((x3 + x4) / 2) - ((x1 + x2) / 2) < 5 || ((x3 + x4) / 2) - ((x1 + x2) / 2) > -5)
            {
                x2 = x4;
                x1 = x3;
            }
            MidLine[i] = (int)((x1 + x2) / 2);
        }
    }
}

void CameraProcess(void)
{
	if(mt9v03x_finish_flag)
	{
		mt9v03x_finish_flag=0;
		ips114_displayimage032_zoom(mt9v03x_image[0], MT9V03X_W, MT9V03X_H, 240, 135);
		//seekfree_sendimg_03x_usb_cdc(mt9v03x_csi_image[0], MT9V03X_CSI_W, MT9V03X_CSI_H);
	}
//    ImagePretreatment();
//    FindMedLine();
//    EdgePointFind();
//	  MidLineFuseNum=GetMidLineNum();
//    ProcessImageFlag = 1;
//			for(int i=0;i<MT9V03X_H;i++)
//		{
//			DisplayIMAG[i][(int)(LeftLine[i]+RightLine[i])/2]=0;
//		}
//    ips114_displayimage032_zoom(DisplayIMAG[0], MT9V03X_W, MT9V03X_H, 240, 135);
}
void EdgePointFind(void)
{

    for(int i = 105; i >= 20; i--)
    {
        if(RightLine[i] - RightLine[i - 1] >= 3 || RightLine[i] - RightLine[i - 1] <= -3)
            Rbp = Rbp + 1;
        if(LeftLine[i] - LeftLine[i - 1] >= 3 || LeftLine[i] - LeftLine[i - 1] <= -3)
            Lbp = Rbp + 1;
    }
    if(Rbp + Lbp >= 4 || Rbp >= 2 || Lbp >= 2)
    {
        Rbp = 0;
        Lbp = 0;
        for(int i = 105; i >= 20; i--)
        {
            if(RightLine[i] - RightLine[i - 1] >= 5 || RightLine[i] - RightLine[i - 1] <= -5)
            {
                RightLine[i] = RightLine[i - 1] - 1;
            }
            if(LeftLine[i] - LeftLine[i - 1] >= 5 || LeftLine[i] - LeftLine[i - 1] <= -5)
            {
                LeftLine[i] = LeftLine[i - 1] + 1;
            }
        }
        for(int i = 187; i >= 0; i--)
        {
            MidLine[i] = (int)((LeftLine[i] + RightLine[i]) / 2);
        }
    }
}

double GetMidLineNum(void)
{
	long MidLineSum=0;
    double MidLineFuse;
    for(int i = 13; i <= 105; i++)
    {
				MidLineSum+= MidLine[i];
    }
		return MidLineFuse/93;

}


