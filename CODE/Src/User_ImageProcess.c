/*
 * User_ImageProcess.c
 *
 *  Created on: 2020年7月4日
 *      Author: Quantum815
 */

#include <..\CODE\Inc\User_Image_Process.h>

#ifdef IMAGEPROCESS

#pragma section all "cpu0_dsram"

uint8 EnterGarageFlag;

#pragma section all restore

#pragma section all "cpu1_dsram"

/*int x1, x2, x3, x4;
int CloseThresholds;
int FarThresholds;
uint8 ProcessImageFlag = 0;
uint8 DisplayIMAGE[MT9V03X_H][MT9V03X_W], OSTUIMAGE[15][MT9V03X_W];
uint8 LeftLine[MT9V03X_H], RightLine[MT9V03X_H], MidLine[MT9V03X_H];*/

#pragma section all restore


#pragma section all "cpu1_psram"

//图像图处理
/*void ImagePretreatment(void)
{
    for (uint8 i = 0; i <= MT9V03X_H - 1; i++)
    {
        for(uint8 j = 0; j <= MT9V03X_W-1; j++)
        {

            if((i<=50 && (j<=50 || j>=138)) || (i>=70 && (j<=50 || j>=138)))
            {
                DisplayIMAGE[i][j] = mt9v03x_image[i][j] + 0;
            }

        }
    }
    for(int i = 15; i <= (MT9V03X_H-1)-15; i++)
    {
        for(int j = 0; j <= MT9V03X_W-1; j++)
        {
            if(i >= 50)
            {
                if(mt9v03x_image[i][j] <= CloseThresholds)
                {
                    DisplayIMAGE[i][j] = 0;  //白
                }
                else
                {
                    DisplayIMAGE[i][j] = 255;  //黑
                }
            }
            else
            {
                if(mt9v03x_image[i][j] <= FarThresholds)
                {
                    DisplayIMAGE[i][j] = 0;
                }
                else
                {
                    DisplayIMAGE[i][j] = 255;
                }
            }
        }
    }

}
void FindMidLine(void)
{

    for (uint8 i = (MT9V03X_H - 1) - 15; i >= 15; i--)
    {
        if(i >= (MT9V03X_H - 1) - 20)
        {
            for (uint8 j = 0; j <= MT9V03X_W - 1; j++)
            {
                if (DisplayIMAGE[i][j] == 255)
                {
                    x1 = j;
                    LeftLine[i] = j;
                    break;
                }
                else if(j == 187)
                {
                    LeftLine[i] = 187;
                }
            }
            for(uint8 k = MT9V03X_W; k >= 0; k--)
            {
                if(DisplayIMAGE[i][k] == 255)
                {
                    x2 = k;
                    RightLine[i] = k;
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
            for (uint8 f = ((int)((x1 + x2) / 2)); f >= 0; f--)
            {
                if (DisplayIMAGE[i][f] == 0)
                {
                    LeftLine[i] = f;
                    x3 = f;
                    break;
                }
                else if(f == 0)
                {
                    LeftLine[i] = 0;
                }
            }
            for (uint8 g = (int)((x1 + x2) / 2); g <= MT9V03X_W - 1; g++)
            {
                if (DisplayIMAGE[i][g] == 0)
                {
                    x4 = g;
                    RightLine[i] = g;
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
//	if(mt9v03x_finish_flag)
//	{
//		mt9v03x_finish_flag=0;
//		ips114_displayimage032_zoom(mt9v03x_image[0], MT9V03X_W, MT9V03X_H, 240, 135);
//	}
    CloseThresholds = GetOSTU(mt9v03x_image) + 15;
    FarThresholds = GetOSTU(mt9v03x_image) + 15;
	ImagePretreatment();
    FindMidLine_ADD();
	//EdgePointFind();
	 MidLineFuseNum = GetMidLineNum();
	ProcessImageFlag = 1;
//			for(int i=0;i<MT9V03X_H;i++)
//		{
//			DisplayIMAGE[i][(int)(LeftLine[i]+RightLine[i])/2]=0;
//		}
//    ips114_displayimage032_zoom(DisplayIMAGE[0], MT9V03X_W, MT9V03X_H, 240, 135);
}
void EdgePointFind(void)
{
    uint8 Rbp = 0, Lbp = 0;

    for(int i = 105; i >= 15; i--)
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
        for(int i = 105; i >= 15; i--)
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
    double ClearLineSum = 0, MidLineSum = 0, LongLineSum = 0;
    double AllLineSum = 0;
    for(int i = 15; i <= 105; i++)
    {
        if(i >= 15 && i <= 45)
            LongLineSum += MidLine[i];
        else if(i > 55 && i < 65)
            MidLineSum += MidLine[i];
        else if(i >= 85 && i <= 105)
            ClearLineSum += MidLine[i];
    }
    AllLineSum = LongLineSum * 0  + MidLineSum * 0  + ClearLineSum ;
    return AllLineSum / 20;
}

void ShowMidLine(void)
{
    uint8 ShowMidLineIMG[MT9V03X_H][MT9V03X_W] = {{255}};
    for(int i = 0; i <= MT9V03X_H - 1; i++)
    {
        for(int j = 0; j <= MT9V03X_W - 1; j++)
            ShowMidLineIMG[i][j] = 255;
    }
    for(int i = 90; i <= 105; i++)
    {

        ShowMidLineIMG[i][MidLine[i]] = 0;
    }
    ips114_displayimage032_zoom(ShowMidLineIMG[0], MT9V03X_W, MT9V03X_H, 240, 135);

}
void FindMidLine_ADD(void)
{
    //DisplayIMAGE
    float CountWhitePixels = 0, FirstWhitePixels, BlackFlag = 0;
    int AllAddsum = 0;
    for(int i = 0; i <= MT9V03X_W - 1; i++)
    {
        for(int j = 0; j <= MT9V03X_W - 1; j++)
        {
            if(DisplayIMAGE[i][j] == 255)
            {
//				FirstWhitePixels=j;
                CountWhitePixels++;
//				if(CountWhitePixels>=20)
//				{
//
//				}
                AllAddsum += j;
                BlackFlag = 0;

            }
            else
            {
                BlackFlag++;
                if(BlackFlag == 5)
                {
                    if(CountWhitePixels <= 40)
                    {
                        AllAddsum = 0;
                        CountWhitePixels = 0;
                    }
                }
            }

        }
        MidLine[i] = (uint8)(AllAddsum / CountWhitePixels * 1.0);
    }
}

void GetOSTUIMAGE(void)
{
    for(int i = 0; i < 15; i++)
    {
        for(int j = 0; j < MT9V03X_W; j++)
            OSTUIMAGE[i][j] = mt9v03x_image[i + 15][j];
    }
}*/

void FindZebra(void)
{
	uint8_t Threshold;
	uint8 JudgeBToWFlag = 0;
	uint8 JudgeWToBFlag = 0;
	uint8 BlackWhiteChangeCount = 0;
	static uint8 RecognizedCorrectLineCount = 0;

	Threshold = GetOSTU(&mt9v03x_image[0]);
	if(255 - Threshold >= InGarageAdjustedValue)
		Threshold += InGarageAdjustedValue;
	else
		Threshold = 255;
	BinaryImage(&mt9v03x_image[0], Threshold);

	for(int imageH=30; imageH<=70; imageH++)
	{
		BlackWhiteChangeCount = 0;
		for(int imageW=94; imageW>=40; imageW--)
		{
			JudgeBToWFlag = 0;
			JudgeWToBFlag = 0;
			if(mt9v03x_image[imageH][imageW]==0x00 && mt9v03x_image[imageH][imageW-1]==0xfe)
			{
				for(int i=imageW-6; i<=imageW-1; i++)
					if(mt9v03x_image[imageH][i]==0x00)
					{
						JudgeBToWFlag = 1;
						break;
					}
				for(int i=imageW; i<=imageW+5; i++)
					if(mt9v03x_image[imageH][i]==0xfe)
					{
						JudgeBToWFlag = 1;
						break;
					}
				if(!JudgeBToWFlag)
					BlackWhiteChangeCount++;
			}
			if(mt9v03x_image[imageH][imageW]==0xfe && mt9v03x_image[imageH][imageW-1]==0x00)
			{
				for(int i=imageW-6; i<=imageW-1; i++)
					if(mt9v03x_image[imageH][i]==0xfe)
					{
						JudgeWToBFlag = 1;
						break;
					}
				for(int i=imageW; i<=imageW+5; i++)
					if(mt9v03x_image[imageH][i]==0x00)
					{
						JudgeWToBFlag = 1;
						break;
					}
				if(!JudgeWToBFlag)
					BlackWhiteChangeCount++;
			}
		}
		for(int imageW=94; imageW<=140; imageW++)
		{
			JudgeBToWFlag = 0;
			JudgeWToBFlag = 0;
			if(mt9v03x_image[imageH][imageW]==0x00 && mt9v03x_image[imageH][imageW+1]==0xfe)
			{
				for(int i=imageW-5; i<=imageW; i++)
					if(mt9v03x_image[imageH][i]==0xfe)
					{
						JudgeBToWFlag = 1;
						break;
					}
				for(int i=imageW+1; i<=imageW+6; i++)
					if(mt9v03x_image[imageH][i]==0x00)
					{
						JudgeBToWFlag = 1;
						break;
					}
				if(!JudgeBToWFlag)
					BlackWhiteChangeCount++;
			}
			if(mt9v03x_image[imageH][imageW]==0xfe && mt9v03x_image[imageH][imageW+1]==0x00)
			{
				for(int i=imageW-5; i<=imageW; i++)
					if(mt9v03x_image[imageH][i]==0x00)
					{
						JudgeWToBFlag = 1;
						break;
					}
				for(int i=imageW+1; i<=imageW+6; i++)
					if(mt9v03x_image[imageH][i]==0xfe)
					{
						JudgeWToBFlag = 1;
						break;
					}
				if(!JudgeWToBFlag)
					BlackWhiteChangeCount++;
			}
		}
		if(BlackWhiteChangeCount >= 8)
			RecognizedCorrectLineCount++;
	}

	if(RecognizedCorrectLineCount >= 5)
	{
			gpio_set(P20_8, 1);
			EnterGarageFlag = 1;
	}
}

#pragma section all restore

#endif
