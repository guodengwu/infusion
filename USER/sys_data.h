#ifndef __SYS_H
#define __SYS_H

#include "includes.h"

#define SYSSTATE_NONE							0
#define SYSSTATE_INFUSION_COMPLETE				DEF_BIT00_MASK
#define SYSSTATE_INFUSION_TBE				DEF_BIT01_MASK
//#define SYSSTATE_RLED_TWINKLE				DEF_BIT02_MASK
#define SYSSTATE_SHUTDOWN					DEF_BIT03_MASK

enum _battary {
	BAT_3,
	BAT_2,
	BAT_1,	
	BAT_0,
};

typedef struct _sys_status	{
	volatile u32 state;
    u8 ledstate;
}_sys_t;
//系统设置参数
typedef struct _sys_setparam	{
	u8 LcdContrastLevel;	
}_sys_setparam_t;
//称重参数
typedef struct _weighparam	{
	s16 WeighDataZero;//零点校准
	float A;//校准多项式参数
	float B;
	float C;
}_weighparam_t;
//系统数据
typedef struct _sys_data	{
	u16 capacity;
	u16 speed;
	u16 weigh;//实际测得的重量，单位为克
	u16 bat;
	
}_sys_data_t;
//Y1
//Bit0 – 保留；
//Bit1 – 保留；
//Bit2 – 保留；
//Bit3 – 保留；
//Bit4 – 重量突变；
//Bit5—设置药袋异常；
//Bit6—电池电量低；
//Bit7—气泡报警
typedef struct _syserror	{
	BIT8 Y1;
}_syserror_t;

extern _sys_t Sys;
extern _sys_data_t SysData;
extern _sys_setparam_t SysParm;
extern _weighparam_t WeighParam;
extern _syserror_t SysError;
extern _syserror_t SysErrorBk;

void SysDataInit(void);
void ReadUserDataFromEEPROM(void);
#endif
