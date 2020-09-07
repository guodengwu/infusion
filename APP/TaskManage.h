#ifndef __TASKMANAGE_H__
#define __TASKMANAGE_H__

#include "includes.h"

typedef struct _SYS_TIM
{
    volatile uint32_t  SumNumber;       //累加计数
    volatile uint32_t  SumMs;          //累加ms数
    volatile uint32_t  SumSec;         //累加秒数
    volatile uint32_t  SumMinute;      //累加分钟数
}SYS_TIM;

//extern SYS_TIM  SysTim;
//extern volatile u8	_1MS_Event;
//extern volatile u8	_5MS_Event;
void SysTaskInit(void);
void RunTask(void);
void TaskTick(void);
#endif
