#include "save_data.h"
#include "CRC_Check.h"
#include "eeprom.h"

static u8 eeprom_buff[128];

eeprom_data_t eeprom_data = {
	.type = SaveDataType_NONE,
};

//save用户数据
void SaveUserDataToEEPROM(void)
{
	u16 crc16;
	
	if(eeprom_data.type == SaveDataType_NONE||eeprom_data.pbuf==NULL||eeprom_data.len == 0)	{
		return;
	}
	memcpy(eeprom_buff, (u8 *)eeprom_data.pbuf, eeprom_data.len);
	crc16 = CRC16(eeprom_buff, eeprom_data.len);
	memcpy(eeprom_buff + eeprom_data.len, (u8 *)&crc16, 2);	//多写两个字节的CRC
	eeprom_data.len += 2;
	if(eeprom_data.type & SaveDataType_SYSINFO)	{//保存系统数据
		eeprom_data.type &= ~SaveDataType_SYSINFO;
		EEPROM_WriteBytes(EEPROMAddr_SYSINFOR, eeprom_buff, eeprom_data.len);
	}
	if(eeprom_data.type & SaveDataType_SYSPARAM)	{//保存系统参数
		eeprom_data.type &= ~SaveDataType_SYSPARAM;
		EEPROM_WriteBytes(EEPROMAddr_SYSPARAM, eeprom_buff, eeprom_data.len);
	}
	if(eeprom_data.type & SaveDataType_WEIGHPARAM)	{//保存称重参数
		eeprom_data.type &= ~SaveDataType_SYSPARAM;
		EEPROM_WriteBytes(EEPROMAddr_WEIGHPARAM, eeprom_buff, eeprom_data.len);
	}
}

//读取用户数据
u8 ReadUserData(u32 addr, u8 *pbuf, u8 len)
{
	u16 crc16;
	
	EEPROM_ReadBytes(addr, eeprom_buff, len+2);//多读两个字节的CRC
	crc16 = eeprom_buff[len] | eeprom_buff[len+1]<<8;
	if(crc16 == CRC16(eeprom_buff, len))	{
		memcpy(pbuf, eeprom_buff, len);
		return 1;
	}
	return 0;
}

