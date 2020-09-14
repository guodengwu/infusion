#include "sys_data.h"

_sys_t Sys;
_sys_data_t SysData;

void SysDataInit(void)
{
	Sys.state = SYSSTATE_NONE;
	SysData.capacity = 0xff;
	SysData.speed = 0xff;
}

