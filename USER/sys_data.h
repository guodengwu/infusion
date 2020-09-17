#ifndef __SYS_H
#define __SYS_H

#include "includes.h"

#define SYSSTATE_NONE							0
//#define SYSSTATE_SHUTDOWN_TB				DEF_BIT00_MASK
//#define SYSSTATE_SHUTDOWN_YES					DEF_BIT01_MASK
#define SYSSTATE_SHUTDOWN					DEF_BIT02_MASK

typedef struct _sys_status	{
	volatile u32 state;
}_sys_t;
//ϵͳ���ò���
typedef struct _sys_setparam	{
	u8 LcdContrastLevel;	
}_sys_setparam_t;
//���ز���
typedef struct _weighparam	{
	s16 WeighDataZero;//���У׼
	float A;//У׼����ʽ����
	float B;
	float C;
}__weighparam_t;
//ϵͳ����
typedef struct _sys_data	{
	u16 capacity;
	u16 speed;
	
}_sys_data_t;

extern _sys_t Sys;
extern _sys_data_t SysData;
extern _sys_setparam_t SysParm;
extern __weighparam_t WeighParam;

void SysDataInit(void);
void ReadUserDataFromEEPROM(void);
#endif
