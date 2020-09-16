#include "SysMonitorTask.h"
#include "save_data.h"

void SysMonitorTaskInit(void)
{

}

void SysMonitorTaskProcess(void)
{
	SaveUserDataToEEPROM();
	if(Sys.state & SYSSTATE_SHUTDOWN)	{
		SysShutdown();
	}
}
