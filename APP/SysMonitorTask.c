#include "SysMonitorTask.h"
#include "UITask.h"
#include "save_data.h"

message_pkt_t msg_pkt_monitor;

void SysMonitorTaskInit(void)
{

}

void CheckSysAlarm(void)
{
	if(SysError.Y1.ubyte == SysErrorBk.Y1.ubyte)	
		return;
	
	if(SysError.Y1.bits.b7==DEF_True&&SysErrorBk.Y1.bits.b7==DEF_False)	{//气泡报警
		msg_pkt_monitor.Src = MSG_UI;
		msg_pkt_monitor.Cmd = UIID_PAIQI;
		StartUITask(&msg_pkt_monitor);
	}
	if(SysError.Y1.bits.b6==DEF_True&&SysErrorBk.Y1.bits.b6==DEF_False)	{//电量低报警
		msg_pkt_monitor.Src = MSG_UI;
		msg_pkt_monitor.Cmd = UIID_LOWPOWER;
		StartUITask(&msg_pkt_monitor);
	}
	if(SysError.Y1.bits.b5==DEF_True&&SysErrorBk.Y1.bits.b5==DEF_False)	{
		
	}
	if(SysError.Y1.bits.b4==DEF_True&&SysErrorBk.Y1.bits.b4==DEF_False)	{
		
	}
	if(SysError.Y1.bits.b3==DEF_True&&SysErrorBk.Y1.bits.b3==DEF_False)	{
		
	}
	if(SysError.Y1.bits.b2==DEF_True&&SysErrorBk.Y1.bits.b2==DEF_False)	{
		
	}
	if(SysError.Y1.bits.b1==DEF_True&&SysErrorBk.Y1.bits.b1==DEF_False)	{
		
	}
	if(SysError.Y1.bits.b0==DEF_True&&SysErrorBk.Y1.bits.b0==DEF_False)	{
		
	}
	SysErrorBk.Y1.ubyte = SysError.Y1.ubyte;
}

#include "ad7799.h"
void CalcBattray(void)
{
	u16 advol,bat_vol;
	
	advol = GetBattaryVol();
	if(advol<1000)	
		return;
	bat_vol =advol*2;
	if(bat_vol>=5000)	{
		SysData.bat = BAT_3;
		SysError.Y1.bits.b6 = DEF_False;
	}
	else if(bat_vol>=4300&&bat_vol<4900)	{
		SysData.bat = BAT_2;
		SysError.Y1.bits.b6 = DEF_False;
	}
	else if(bat_vol>=4000&&bat_vol<4200)	{
		SysData.bat = BAT_1;
	}
	else if(bat_vol<3900/*00&&bat_vol>=3850*/)	{//电量低报警
//		SysData.bat = BAT_0;
//		SysError.Y1.bits.b6 = DEF_True;
//		if(bat_vol<3800)	{//电量耗尽
//			msg_pkt_monitor.Src = MSG_UI;
//			msg_pkt_monitor.Cmd = UIID_POWERDEAD;
//			StartUITask(&msg_pkt_monitor);
//		}
	}
}

void SysMonitorTaskProcess(void)
{
	CalcBattray();
	CheckSysAlarm();
	SaveUserDataToEEPROM();
	if(Sys.state & SYSSTATE_SHUTDOWN)	{
		static u8 shutdowncnt;
		shutdowncnt ++;
		if(shutdowncnt>10)	{
			shutdowncnt = 0;
//			Sys.state &= ~SYSSTATE_SHUTDOWN;
			lcd12864_FillRAM(0, LCD_PAGE_MAX, 0, LCD_COL_MAX, 0);			
			SysShutdown();
		}
	}
}

