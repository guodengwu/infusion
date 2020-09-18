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
}_weighparam_t;
//ϵͳ����
typedef struct _sys_data	{
	u16 capacity;
	u16 speed;
	u16 weigh;//ʵ�ʲ�õ���������λΪ��
	u16 bat;
	
}_sys_data_t;
//Y1
//Bit0 �C ������
//Bit1 �C ������
//Bit2 �C ������
//Bit3 �C ������
//Bit4 �C ����ͻ�䣻
//Bit5������ҩ���쳣��
//Bit6����ص����ͣ�
//Bit7�����ݱ���
typedef struct _syserror	{
	BIT8 Y1;
}_syserror_t;

extern _sys_t Sys;
extern _sys_data_t SysData;
extern _sys_setparam_t SysParm;
extern _weighparam_t WeighParam;
extern _syserror_t SysError;

void SysDataInit(void);
void ReadUserDataFromEEPROM(void);
#endif
