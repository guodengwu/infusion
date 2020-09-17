#ifndef _SAVE_DATA_H
#define _SAVE_DATA_H

#include "includes.h"

#define	SaveDataType_NONE				0
#define SaveDataType_SYSINFO			DEF_BIT01_MASK
#define SaveDataType_SYSPARAM			DEF_BIT02_MASK
#define SaveDataType_WEIGHPARAM			DEF_BIT03_MASK

#define	EEPROMAddr_SYSINFOR			0x0 //保存系统信息地址
#define	EEPROMAddr_SYSPARAM			0x80 //保存系统参数地址
#define	EEPROMAddr_WEIGHPARAM		0x90//保存称重参数

typedef struct _eeprom_data{
	u32 type;
	u32 addr;
	u8 *pbuf;
	u8 len;
}eeprom_data_t;

extern eeprom_data_t eeprom_data;
void SaveUserDataToEEPROM(void);
u8 ReadUserData(u32 addr, u8 *pbuf, u8 len);
#endif

