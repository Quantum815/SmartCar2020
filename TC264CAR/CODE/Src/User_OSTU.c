/*
  * User_OSTU.c
 *
 *  Created on: 2020年7月6日
 *      Author: Quantum815
 */

#include "..\CODE\Inc\User_OSTU.h"

#pragma section all "cpu1_psram"

/***************************************************************
*
* 函数名称：uint8_t GetOSTU(uint8_t tmImage[IMAGEH][IMAGEW])
* 功能说明：求阈值大小
* 参数说明：
* 函数返回：阈值大小
* 修改时间：2018年3月27日
* 备 注：
参考：https://blog.csdn.net/zyzhangyue/article/details/45841255
      https://www.cnblogs.com/moon1992/p/5092726.html
      https://www.cnblogs.com/zhonghuasong/p/7250540.html
Ostu方法又名最大类间差方法，通过统计整个图像的直方图特性来实现全局阈值T的自动选取，其算法步骤为：
1) 先计算图像的直方图，即将图像所有的像素点按照0~255共256个bin，统计落在每个bin的像素点数量
2) 归一化直方图，也即将每个bin中像素点数量除以总的像素点
3) i表示分类的阈值，也即一个灰度级，从0开始迭代
4) 通过归一化的直方图，统计0~i 灰度级的像素(假设像素值在此范围的像素叫做前景像素) 所占整幅图像的比例w0，并统计前景像素的平均灰度u0；统计i~255灰度级的像素(假设像素值在此范围的像素叫做背景像素) 所占整幅图像的比例w1，并统计背景像素的平均灰度u1；
5) 计算前景像素和背景像素的方差 g = w0*w1*(u0-u1) (u0-u1)
6) i++；转到4)，直到i为256时结束迭代
7）将最大g相应的i值作为图像的全局阈值
缺陷:OSTU算法在处理光照不均匀的图像的时候，效果会明显不好，因为利用的是全局像素信息。
***************************************************************/
uint8_t GetOSTU(uint8_t tmImage[IMAGEH][IMAGEW])
{
  uint32_t Amount = 0;
  uint32_t PixelBack = 0;
  uint32_t PixelIntegralBack = 0;
  uint32_t PixelIntegral = 0;
  int32_t PixelIntegralFore = 0;
  int32_t PixelFore = 0;
  double OmegaBack, OmegaFore, MicroBack, MicroFore, SigmaB, Sigma; // 类间方差;
  uint8_t MinValue, MaxValue;
  uint8_t Threshold = 0;
  uint8_t HistoGram[256];              //

  for (int j = 0; j < 256; j++)  HistoGram[j] = 0; //初始化灰度直方图

  for (int j = 0; j < IMAGEH-40; j++)
  {
    for (int i = 0; i < IMAGEW-8; i++)
    {
      HistoGram[tmImage[j][i]]++; //统计灰度级中每个像素在整幅图像中的个数
    }
  }

  for (MinValue = 0; MinValue < 256 && HistoGram[MinValue] == 0; MinValue++) ;        //获取最小灰度的值
  for (MaxValue = 255; MaxValue > MinValue && HistoGram[MinValue] == 0; MaxValue--) ; //获取最大灰度的值

  if (MaxValue == MinValue)     return MaxValue;         // 图像中只有一个颜色
  if (MinValue + 1 == MaxValue)  return MinValue;        // 图像中只有二个颜色

  for (int j = MinValue; j <= MaxValue; j++)    Amount += HistoGram[j];        //  像素总数

  PixelIntegral = 0;
  for (int j = MinValue; j <= MaxValue; j++)
  {
    PixelIntegral += HistoGram[j] * j;//灰度值总数
  }
  SigmaB = -1;
  for (int j = MinValue; j < MaxValue; j++)
  {
    PixelBack = PixelBack + HistoGram[j];    //前景像素点数
    PixelFore = Amount - PixelBack;         //背景像素点数
    OmegaBack = (double)PixelBack / Amount;//前景像素百分比
    OmegaFore = (double)PixelFore / Amount;//背景像素百分比
    PixelIntegralBack += HistoGram[j] * j;  //前景灰度值
    PixelIntegralFore = PixelIntegral - PixelIntegralBack;//背景灰度值
    MicroBack = (double)PixelIntegralBack / PixelBack;   //前景灰度百分比
    MicroFore = (double)PixelIntegralFore / PixelFore;   //背景灰度百分比
    Sigma = OmegaBack * OmegaFore * (MicroBack - MicroFore) * (MicroBack - MicroFore);//计算类间方差
    if (Sigma > SigmaB)                    //遍历最大的类间方差g //找出最大类间方差以及对应的阈值
    {
      SigmaB = Sigma;
      Threshold = (uint16_t)j;
    }
  }
  return Threshold;                        //返回最佳阈值;
}
/***************************************************************
*
* 函数名称：void BinaryImage(uint8_t tmImage[IMAGEH][IMAGEW])
* 功能说明：图像数据二值化
* 参数说明：
* 函数返回：void
* 修改时间：2018年3月27日
* 备 注：
***************************************************************/
void BinaryImage(uint8_t tmImage[IMAGEH][IMAGEW],uint8_t ThresholdV)
{

  for(int i = 0;i < IMAGEH;i++)
  {
    for(int j = 0; j< IMAGEW;j++)
    {
      if(tmImage[i][j] >= ThresholdV)
      {
        tmImage[i][j] = 0xFE;
      }
      else
      {
        tmImage[i][j] = 0X00;
      }
    }
  }
}

#pragma section all restore

