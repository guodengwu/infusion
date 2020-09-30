#include "sys_data.h"
#include "sys_info.h"
#include "save_data.h"

_sys_t Sys;
_sys_data_t SysData;
_sys_setparam_t SysParm;
_weighparam_t WeighParam;
_syserror_t SysError;
_syserror_t SysErrorBk;

void SysDataInit(void)
{
	Sys.state = SYSSTATE_NONE;
    Sys.ledstate = LED_NONE;
	SysData.capacity = 0xffff;
	SysData.speed = 0xffff;
	SysData.bat = BAT_3;
	
	SysParm.LcdContrastLevel = 0x18;//lcd对比度参数
	
	WeighParam.WeighDataZero = 0;
	WeighParam.A = 0.0;
	
	SysError.Y1.ubyte = DEF_False;
}
//从eeprom读取系统信息，系统设置参数，称重参数等
void ReadUserDataFromEEPROM(void)
{
	ReadUserData(EEPROMAddr_SYSINFOR, (u8 *)g_sys_infor.pident, sizeof(ident_infor_t));
	ReadUserData(EEPROMAddr_SYSPARAM, (u8 *)&SysParm, sizeof(_sys_setparam_t));
	ReadUserData(EEPROMAddr_WEIGHPARAM, (u8 *)&WeighParam, sizeof(_weighparam_t));
}
