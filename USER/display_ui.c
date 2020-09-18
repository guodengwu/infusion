#include "display_ui.h"

#define 	RETRACT_ACSII		8
#define 	RETRACT_0_SIZE		16	
#define 	RETRACT_1_SIZE		24		
#define 	RETRACT_2_SIZE		32	
#define 	RETRACT_3_SIZE		64
#define 	RETRACT_4_SIZE		96

_UI_t	ui;
u8 CodeData[8];

void UIInit(void)
{
	ui.screen_id = UIID_CAPACITY;
}

void ConfirmCapacityUI(u16 cap)
{
	u8 i;
	
	lcd12864_FillRAM(0, LCD_PAGE_MAX, 0, LCD_COL_MAX, 0);//清屏
	for(i=0;i<5;i++)	{
		CodeData[i] = i;
	}		
	lcd12864_HZ16_16(0, RETRACT_1_SIZE, CodeData, i);
	if(cap == 0xffff)	{
		ui.datlen = sprintf(ui.buff, "**** ml");
	}
	else	{
		ui.datlen = sprintf(ui.buff, "%d mv", cap);		
	}
	lcd12864_string(2, RETRACT_2_SIZE, ui.buff);
}

void SpeedUI(u16 speed, u16 cap)
{
	u8 col_addr;
	u8 i;
	
	lcd12864_FillRAM(0, LCD_PAGE_MAX, 0, LCD_COL_MAX, 0);//清屏
	for(i=0;i<2;i++)	{
		CodeData[i] = 5+i;
	}
	col_addr = lcd12864_HZ16_16(0, RETRACT_ACSII, CodeData, 2);
	if(speed == 0xffff)	{
		ui.datlen = sprintf(ui.buff, "** ml/h");		
	}
	else
		ui.datlen = sprintf(ui.buff, "%d.%d ml/h", speed/10,speed%10);	
	lcd12864_string(0, col_addr + RETRACT_ACSII, ui.buff);
	
	CodeData[0] = 7;CodeData[1] = 8;
	col_addr = lcd12864_HZ16_16(2, RETRACT_ACSII, CodeData, 2);
	if(cap == 0xffff)	{
		ui.datlen = sprintf(ui.buff, "** ml");		
	}
	else
		ui.datlen = sprintf(ui.buff, "%d ml   ", cap);	
	lcd12864_string(2, col_addr, ui.buff);
}

void InfusionCompleteUI(u16 speed)
{
	u8 col_addr;
	u8 i;
	
	lcd12864_FillRAM(0, LCD_PAGE_MAX, 0, LCD_COL_MAX, 0);//清屏
	for(i=0;i<4;i++)	{
		CodeData[i] = 9+i;
	}
	lcd12864_HZ16_16(0, RETRACT_2_SIZE, CodeData, i);
	CodeData[0] = 5;CodeData[1] = 6;
	col_addr = lcd12864_HZ16_16(2, RETRACT_ACSII, CodeData, 2);
	ui.datlen = sprintf(ui.buff, "%d.%d ml/h", speed/10,speed%10);	
	lcd12864_string(2, col_addr + RETRACT_ACSII, ui.buff);
}

void PaiQiUI(u16 speed)
{
	u8 col_addr;
	u8 i;
	
	lcd12864_FillRAM(0, LCD_PAGE_MAX, 0, LCD_COL_MAX, 0);//清屏
	CodeData[0] = 0;
	for(i=1;i<5;i++)	{
		CodeData[i] = 12+i;
	}
	lcd12864_HZ16_16(0, RETRACT_1_SIZE, CodeData, i);
	CodeData[0] = 5;CodeData[1] = 6;
	col_addr = lcd12864_HZ16_16(2, RETRACT_ACSII, CodeData, 2);
	if(speed == 0xffff)	
		ui.datlen = sprintf(ui.buff, "**** ml/h");	
	else
		ui.datlen = sprintf(ui.buff, "%d.%d ml/h", speed/10,speed%10);	
	lcd12864_string(2, col_addr + RETRACT_ACSII, ui.buff);
}

void ShutDownUI(void)
{
	u8 i;
	
	lcd12864_FillRAM(0, LCD_PAGE_MAX, 0, LCD_COL_MAX, 0);//清屏
	for(i=0;i<4;i++)	{
		CodeData[i] = 31+i;
	}
	lcd12864_HZ16_16(0, RETRACT_2_SIZE, CodeData, i);
	lcd12864_string(2, RETRACT_ACSII*7, "...");
}

void WeighZeroCalibrateUI(void)
{
	u8 i;
	
	lcd12864_FillRAM(0, LCD_PAGE_MAX, 0, LCD_COL_MAX, 0);//清屏
	for(i=0;i<4;i++)	{
		CodeData[i] = 35+i;
	}
	lcd12864_HZ16_16(0, RETRACT_1_SIZE+RETRACT_ACSII, CodeData, i);
}

void LCDContrastLevelUI(void)
{
	u8 col_addr;
	
	lcd12864_FillRAM(0, LCD_PAGE_MAX, 0, LCD_COL_MAX, 0);
	col_addr = lcd12864_string(0, RETRACT_1_SIZE+RETRACT_ACSII, "LCD");
	CodeData[0] = 45;CodeData[1] = 46;CodeData[2] = 47;
	lcd12864_HZ16_16(0, col_addr, CodeData, 3);
	ui.datlen = sprintf(ui.buff, "%d", lcd12864_GetContrast());
	lcd12864_string(2, RETRACT_2_SIZE+RETRACT_0_SIZE, ui.buff);
}

void BattaryUI(void)
{
	lcd12864_FillRAM(0, LCD_PAGE_MAX, 0, LCD_COL_MAX, 0);
	CodeData[0] = 27;CodeData[1] = 28;CodeData[2] = 27;CodeData[3] = 4;
	lcd12864_HZ16_16(0, RETRACT_2_SIZE, CodeData, 4);
	if(SysData.bat == BAT_3)
		lcd12864_PaintPic(2, RETRACT_2_SIZE+RETRACT_ACSII, 2, 48, &bat_icon[0][0]);
	if(SysData.bat == BAT_2)
		lcd12864_PaintPic(2, RETRACT_2_SIZE+RETRACT_ACSII, 2, 48, &bat_icon[1][0]);
	if(SysData.bat == BAT_1)
		lcd12864_PaintPic(2, RETRACT_2_SIZE+RETRACT_ACSII, 2, 48, &bat_icon[2][0]);
	if(SysData.bat == BAT_0)
		lcd12864_PaintPic(2, RETRACT_2_SIZE+RETRACT_ACSII, 2, 48, &bat_icon[3][0]);
}

void BLE_IDUI(void)
{
	u8 col_addr;
	
	lcd12864_FillRAM(0, LCD_PAGE_MAX, 0, LCD_COL_MAX, 0);
	CodeData[0] = 39;CodeData[1] = 40;
	col_addr = lcd12864_HZ16_16(0, RETRACT_2_SIZE, CodeData, 2);
	lcd12864_string(0, col_addr, "ID");
}

#include "sys_info.h"
void FWVerUI(void)
{
	u8 i;
	
	lcd12864_FillRAM(0, LCD_PAGE_MAX, 0, LCD_COL_MAX, 0);//清屏
	for(i=0;i<4;i++)	{
		CodeData[i] = 41+i;
	}
	lcd12864_HZ16_16(0, RETRACT_1_SIZE+RETRACT_ACSII, CodeData, i);
	lcd12864_string(2, RETRACT_2_SIZE, CONFIG_SYSINFO_FW_Version);
}

void BATLowPower(void)
{
	lcd12864_FillRAM(0, LCD_PAGE_MAX, 0, LCD_COL_MAX, 0);
	CodeData[0] = 26;CodeData[1] = 27;CodeData[2] = 4;
	lcd12864_HZ16_16(0, RETRACT_2_SIZE+RETRACT_ACSII, CodeData, 2);
	
}

void BATDeadPower(void)
{
	lcd12864_FillRAM(0, LCD_PAGE_MAX, 0, LCD_COL_MAX, 0);
	CodeData[0] = 27;CodeData[1] = 28;CodeData[2] = 29;CodeData[3] = 30;
	lcd12864_HZ16_16(0, RETRACT_1_SIZE+RETRACT_ACSII, CodeData, 4);
	CodeData[0] = 31;CodeData[1] = 32;CodeData[2] = 33;CodeData[3] = 34;
	lcd12864_HZ16_16(0, RETRACT_1_SIZE+RETRACT_ACSII, CodeData, 4);	
}


