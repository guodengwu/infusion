#include "display_ui.h"
#include "bsp_12864.h"

#define 	RETRACT_ACSII		8
#define 	RETRACT_0_SIZE		16	
#define 	RETRACT_1_SIZE		24		
#define 	RETRACT_2_SIZE		32	
#define 	RETRACT_3_SIZE		64

_UI_t	ui;

void ConfirmCapacityUI(u16 cap)
{
	u8 CodeData[] = {0,1,2,3,4};
	
	lcd12864_HZ16_16(0, RETRACT_1_SIZE, CodeData, 5);
	if(cap == 0xff)	{
		ui.datlen = sprintf(ui.buff, "**** ml");
	}
	else	{
		ui.datlen = sprintf(ui.buff, "%d  ml", cap);		
	}
	lcd12864_string(2, RETRACT_2_SIZE, ui.buff);
}

void SpeedUI(u16 speed, u16 cap)
{
	u8 CodeData[] = {5,6};
	u8 col_addr;
	
	col_addr = lcd12864_HZ16_16(0, RETRACT_ACSII, CodeData, 2);
	if(speed == 0xff)	{
		ui.datlen = sprintf(ui.buff, "** ml/h");		
	}
	else
		ui.datlen = sprintf(ui.buff, "%d.%d ml/h", speed/10,speed%10);	
	lcd12864_string(0, col_addr + RETRACT_ACSII, ui.buff);
	
	CodeData[0] = 7;CodeData[1] = 8;
	col_addr = lcd12864_HZ16_16(2, RETRACT_ACSII, CodeData, 2);
	if(cap == 0xff)	{
		ui.datlen = sprintf(ui.buff, "** ml");		
	}
	else
		ui.datlen = sprintf(ui.buff, "%d ml   ", cap);	
	lcd12864_string(2, col_addr, ui.buff);
}

void InfusionCompleteUI(u16 speed)
{
	u8 CodeData[] = {9,10,11,12};
	u8 col_addr;
	
	lcd12864_HZ16_16(0, RETRACT_2_SIZE, CodeData, 4);
	CodeData[0] = 5;CodeData[1] = 6;
	col_addr = lcd12864_HZ16_16(2, RETRACT_ACSII, CodeData, 2);
	ui.datlen = sprintf(ui.buff, "%d.%d ml/h", speed/10,speed%10);	
	lcd12864_string(2, col_addr + RETRACT_ACSII, ui.buff);
}

void PaiQiUI(u16 speed)
{
	u8 CodeData[] = {0,13,14,15,16};
	u8 col_addr;
	
	lcd12864_HZ16_16(0, RETRACT_1_SIZE, CodeData, 5);
	CodeData[0] = 5;CodeData[1] = 6;
	col_addr = lcd12864_HZ16_16(2, RETRACT_ACSII, CodeData, 2);
	ui.datlen = sprintf(ui.buff, "%d.%d ml/h", speed/10,speed%10);	
	lcd12864_string(2, col_addr + RETRACT_ACSII, ui.buff);
}

void PowerOffUI(void)
{
	
}
