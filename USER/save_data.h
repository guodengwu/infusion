#ifndef _SAVE_DATA_H
#define _SAVE_DATA_H

#include "sys_data.h"

#define	SaveDataType_NONE					0
#define SaveDataType_SYSINFO			DEF_BIT01_MASK

#define	EEPROMAddr_SYSINFOR			0x0 //����ϵͳ��Ϣ��ַ
#define	EEPROMAddr_CALIDATA			0x80 //����ѹ��������У׼���ݵ�ַ

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

