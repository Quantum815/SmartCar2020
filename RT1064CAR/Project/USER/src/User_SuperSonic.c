#include "User_SuperSonic.h"

extern long SuperSonic_HighTime;
extern uint16_t SuperSonic_Distance;
extern uint8_t SuperSonic_UpdateState;


/*
函数名称：SuperSonic_GetDistance
函数作用：获取你追我赶分体超声波测距模块返回的前车距离 单位为 mm 例如 1000 表示前车距离 1000mm 也就是 1m
函数输入：无
函数输出：前车距离 单位为mm(毫米)
注意事项：每次调用都会清除超声波测距的就绪位
*/
uint16_t SuperSonic_GetDistance(void)
{
	//限幅
	if(SuperSonic_Distance > 4000)
	{
		SuperSonic_Distance = 4000;
	}
	SuperSonic_UpdateState = 0;
	return SuperSonic_Distance;
}


/*
函数名称：SuperSonic_CheckUpdateState
函数作用：获取你追我赶分体超声波测距模块距离信息的更新状态
函数输入：无
函数输出：距离信息更新状态 0为数据未更新 1为数据已更新且没有被读取
注意事项：
*/
uint8_t  SuperSonic_CheckUpdateState(void)
{
	return SuperSonic_UpdateState;
}


