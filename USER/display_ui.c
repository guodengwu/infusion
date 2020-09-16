#include "display_ui.h"

#define 	RETRACT_ACSII		8
#define 	RETRACT_0_SIZE		16	
#define 	RETRACT_1_SIZE		24		
#define 	RETRACT_2_SIZE		32	
#define 	RETRACT_3_SIZE		64
#define 	RETRACT_4_SIZE		96

_UI_t	ui;
u8 CodeData[8];

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
		ui.datlen = sprintf(ui.buff, "%d  ml", cap);		
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
		CodeData[i] = 13+i;
	}
	lcd12864_HZ16_16(0, RETRACT_1_SIZE, CodeData, i);
	CodeData[0] = 5;CodeData[1] = 6;
	col_addr = lcd12864_HZ16_16(2, RETRACT_ACSII, CodeData, 2);
	ui.datlen = sprintf(ui.buff, "%d.%d ml/h", speed/10,speed%10);	
	lcd12864_string(2, col_addr + RETRACT_ACSII, ui.buff);
}

void ShutDownUI(u8 flag)
{
	u8 i;
	
	lcd12864_FillRAM(0, LCD_PAGE_MAX, 0, LCD_COL_MAX, 0);//清屏
	for(i=0;i<4;i++)	{
		CodeData[i] = 35+i;
	}
	lcd12864_HZ16_16(0, RETRACT_2_SIZE, CodeData, i);
	lcd12864_FillRAM(2, LCD_PAGE_MAX, 0, LCD_COL_MAX, 0);
	if(!flag)	{
		CodeData[0] = 33;CodeData[1] = 36;CodeData[2] = 34;CodeData[3] = 35;
		lcd12864_HZ16_16(2, RETRACT_0_SIZE, CodeData, 3);
		lcd12864_HZ16_16(2, RETRACT_4_SIZE, &CodeData[3], 1);
	}
	else	{
		CodeData[0] = 33;CodeData[1] = 35;CodeData[2] = 34;CodeData[3] = 36;		
		lcd12864_HZ16_16(2, RETRACT_4_SIZE-16, CodeData, 3);
		lcd12864_HZ16_16(2, RETRACT_0_SIZE+16, &CodeData[3], 1);
	}
}
