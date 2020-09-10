#include "TaskManage.h"
#include "KeyScanTask.h"
#include "WeighTask.h"
#include "BLETask.h"

SYS_TIM  SysTim;
volatile u8	_1MS_Event;
volatile u8	_5MS_Event;
volatile u8	_10MS_Event;
volatile u8	_100MS_Event;
volatile u8 _1S_Event;

//�����ʼ��
void SysTaskInit(void)
{
	SysTim.SumMs = 0;
	SysTim.SumSec = 0;
	SysTim.SumMinute = 0;
	SysTim.SumNumber = 0;
	
	KeyScanTaskInit();
	WeighTaskInit();
	BLETaskInit();
}
//�������е�����
void RunTask(void)
{
	if(_10MS_Event)	{
		_10MS_Event = 0;
		KeyScanTaskProcess();
		WeighTaskProcess();
	}
	if(_1S_Event)	{
		_1S_Event = 0;
		BLETaskProcess();
	}
}
//����tick
void TaskTick(void)
{
	SysTim.SumMs++;
	if(SysTim.SumMs>=1000)	{//1s
		SysTim.SumMs = 0;
		SysTim.SumSec++;
		_1S_Event = 1;//1s�¼�
	}
	
	_1MS_Event = 1;
	if((SysTim.SumMs%5) == 0)	{//5ms�¼�
		_5MS_Event = 1;
	}
	if((SysTim.SumMs%10) == 0)	{//10ms�¼�
		_10MS_Event = 1;
	}
	if((SysTim.SumMs%100) == 0)	{//100ms�¼�
		_100MS_Event = 1;
	}
}
