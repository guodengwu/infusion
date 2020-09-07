#ifndef __TASKMANAGE_H__
#define __TASKMANAGE_H__

#include "includes.h"

typedef struct _SYS_TIM
{
    volatile uint32_t  SumNumber;       //�ۼӼ���
    volatile uint32_t  SumMs;          //�ۼ�ms��
    volatile uint32_t  SumSec;         //�ۼ�����
    volatile uint32_t  SumMinute;      //�ۼӷ�����
}SYS_TIM;

//extern SYS_TIM  SysTim;
//extern volatile u8	_1MS_Event;
//extern volatile u8	_5MS_Event;
void SysTaskInit(void);
void RunTask(void);
void TaskTick(void);
#endif
