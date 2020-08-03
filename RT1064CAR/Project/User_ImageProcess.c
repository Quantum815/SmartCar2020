#include "User_ImageProcess.h"
int x1, x2, x3, x4;
uint8 ProcessImageFlag=0;
uint8 DisplayIMAG[MT9V03X_CSI_H][MT9V03X_CSI_W];
void ImagePretreatment(void)
{
    for (int i = 0; i <= MT9V03X_CSI_H-1; i++)
    {
        for(int j = 0; j <= MT9V03X_CSI_W-1; j++)
        {
            
                if((i <= 50 && (j <= 50 || j >= 138)) || (i >= 70 && (j <= 50 || j >= 138)))
                {
                    mt9v03x_csi_image[i][j] = mt9v03x_csi_image[i][j] + 0;
                }
            
        }
    }
		for(int i =0;i<=MT9V03X_CSI_H-1;i++)
		{
			for(int j= 0;j<=MT9V03X_CSI_W-1;j++)
			{
				                if(i >= 50)
                {
                    if(mt9v03x_csi_image[i][j] <= CloseThresholds)
                    {
                        mt9v03x_csi_image[i][j] = 0;
                    }
                    else
                    {
                        mt9v03x_csi_image[i][j] = 255;
                    }
                }
                else
                {
                    if(mt9v03x_csi_image[i][j] <= FarThresholds)
                    {
                        mt9v03x_csi_image[i][j] = 0;
                    }
                    else
                    {
                        mt9v03x_csi_image[i][j] = 255;
                    }
                }
			}
		}

}
void FindMedLine(void)
{
    for (int i = 0; i <= MT9V03X_CSI_H-1; i++)
    {
        if(i <= 10)
        {
            for (int j = 0; j <= MT9V03X_CSI_W-1; j++)
            {
                if (mt9v03x_csi_image[i][j] == 0)
                {
                    x1 = j;
                    break;
                }
            }
            for(int k = MT9V03X_CSI_W; k >= 0; k--)
            {
                if(mt9v03x_csi_image[i][k] == 0)
                {
                    x2 = k;
                    break;
                }
            }
            mt9v03x_csi_image[i][(int)((x1 + x2) / 2)] = 0;
        }
        else
        {
            for (int f = ((int)((x1 + x2) / 2)); f >= 0; f--)
            {
                if (mt9v03x_csi_image[i][f] == 0)
                {
                    x3 = f;
                    break;
                }
            }
            for (int g = (int)((x1 + x2) / 2); g <= 188; g++)
            {
                if (mt9v03x_csi_image[i][g] == 0)
                {
                    x4 = g;
                    break;
                }
            }
            mt9v03x_csi_image[i][(int)((x3 + x4) / 2)] = 0;
						if(x4 == 188 && x3==0)
						{
							  x2 = x4;
                x1 = x3;
						}
            if(fabs(((x3 + x4) / 2) - ((x1 + x2) / 2)) < 5)
            {
                x2 = x4;
                x1 = x3;
            }
        }
    }
}

void CameraProcess(void)
{


	
//		    ImagePretreatment();
//				//if(ReturnFSMState(&Car_Fsm)==GoLine)
//        FindMedLine();
//				ProcessImageFlag=0;
//				mt9v03x_csi_finish_flag=0;
//				if(DebugRx_Buffer==0x06)
//				{
					for(uint8 i=0;i<=MT9V03X_CSI_H-1;i++)
					for(uint8 j=0;j<=MT9V03X_CSI_W-1;j++)
					DisplayIMAG[i][j]=mt9v03x_csi_image[i][j];
					ips114_displayimage032_zoom(DisplayIMAG[0], MT9V03X_CSI_W, MT9V03X_CSI_H, 240, 135);
				//}


}