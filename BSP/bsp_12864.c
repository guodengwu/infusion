#include "bsp_12864.h"

#define	LCD12864_A0_LOW()				HAL_GPIO_WritePin(LCD_A0_GPIO_Port, LCD_A0_Pin, GPIO_PIN_RESET)
#define	LCD12864_A0_HIGH()				HAL_GPIO_WritePin(LCD_A0_GPIO_Port, LCD_A0_Pin, GPIO_PIN_SET)
#define	LCD12864_CS_LOW()				HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET)
#define	LCD12864_CS_HIGH()				HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET)

#define	LCD12864_SDA(state)				HAL_GPIO_WritePin(LCD_SDA_GPIO_Port, LCD_SDA_Pin, state)
#define	LCD12864_SCK(state)				HAL_GPIO_WritePin(LCD_SCK_GPIO_Port, LCD_SCK_Pin, state)

#define	LCD12864_TIMEOUT				100

lcd12864_t  lcd12864;

static void bsp_lcd12864_reset(void)
{
	HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, GPIO_PIN_RESET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, GPIO_PIN_SET);
	HAL_Delay(100);
}

static void lcd12864_wrcmd(u8 cmd)
{
	lcd12864_t *pdev = &lcd12864;
	u8 sdat,i;
	
	LCD12864_SCK(GPIO_PIN_SET);
	LCD12864_A0_LOW();// 选择指令通道
	LCD12864_CS_LOW(); // 选通模块
	sdat = cmd;
//	HAL_SPI_Transmit(pdev->p_spi, &sdat, 1, LCD12864_TIMEOUT);
	for(i=0;i<8;i++)	{
		if(sdat&0x80)	{
			LCD12864_SDA(GPIO_PIN_SET);
		}
		else
			LCD12864_SDA(GPIO_PIN_RESET);
		LCD12864_SCK(GPIO_PIN_RESET);
		LCD12864_SCK(GPIO_PIN_SET);
		sdat <<= 1;
	}
	LCD12864_CS_HIGH();
}

static void lcd12864_wrdata(u8 data)
{
	lcd12864_t *pdev = &lcd12864;
	u8 sdat,i;
	
	LCD12864_SCK(GPIO_PIN_SET);
	LCD12864_A0_HIGH();// 选择数据通道
	LCD12864_CS_LOW(); // 选通模块
	sdat = data;
//	HAL_SPI_Transmit(pdev->p_spi, &sdat, 1, LCD12864_TIMEOUT);
	for(i=0;i<8;i++)	{
		if(sdat&0x80)	{
			LCD12864_SDA(GPIO_PIN_SET);
		}
		else
			LCD12864_SDA(GPIO_PIN_RESET);
		LCD12864_SCK(GPIO_PIN_RESET);
		LCD12864_SCK(GPIO_PIN_SET);
		sdat <<= 1;
	}
	LCD12864_CS_HIGH();
}
//-----------------------------------
// Contrast control
//-----------------------------------
void lcd12864_LCDDarker(void)
{
	if (SysParm.LcdContrastLevel<0x3F)
	{
		SysParm.LcdContrastLevel++;
	}
    lcd12864_wrcmd(0x81);     		// E-Vol setting
	lcd12864_wrcmd(SysParm.LcdContrastLevel);   // (2byte command)
}

void lcd12864_LCDLighter(void)
{
	if (SysParm.LcdContrastLevel>0x00)
	{
		SysParm.LcdContrastLevel--;
	}
    lcd12864_wrcmd(0x81);            // E-Vol setting
	lcd12864_wrcmd(SysParm.LcdContrastLevel);   // (2byte command)
}

u8 lcd12864_GetContrast(void)
{
	return SysParm.LcdContrastLevel;
}

u8 lcd12864_SetContrast(u8 contrast)
{
	if(SysParm.LcdContrastLevel != contrast)	{
		SysParm.LcdContrastLevel = contrast;
		lcd12864_wrcmd(0x81);            // E-Vol setting
		lcd12864_wrcmd(SysParm.LcdContrastLevel);   // (2byte command)
	}
}
//-----------------------------------
// 显示任意一副图片
//-----------------------------------
void lcd12864_PaintPic(u8 page_start, u8 col_start, u8 page_num, u8 col_num, const u8 *pdata)
{
	u8 TempData;
	u16 i,j,m,n;
	u8 page_end;
	
	page_end = page_start + page_num;
//	col_end = col_start + col_num;
	m = 0;
	for(i=page_start;i<page_end;i++)
	{
		lcd12864_wrcmd(0xb0 | i);	// select page
		lcd12864_wrcmd(0x10|col_start>>4);		    // start form column 0
		lcd12864_wrcmd(col_start&0x0f);		    // (2byte command)
		n = m*col_num;
		for(j=0;j<col_num;j++)
		{
			TempData = (*(pdata+n+j));
			lcd12864_wrdata(TempData);
		}
		m++;
	}
}

//----任意字节填充屏幕----------------
void lcd12864_FillRAM(u8 page_start, u8 page_end, u8 col_start, u8 col_end, u8 data)
{
	u8 i,j;
	
	for(i=page_start;i<page_end;i++)
	{
		lcd12864_wrcmd(0xb0 | i);	// select page
		lcd12864_wrcmd(0x10|col_start>>4);	    // start form column 0
		lcd12864_wrcmd(col_start&0x0f);	    // (2byte command)
		for(j=col_start;j<col_end;j++)
		{
			lcd12864_wrdata(data);
		}
	}
}

//------ASCII字符写入函数---------------
 // 坐标(x,y)，x为水平方向像素列；y为垂直方向字符行（8点像素/行）
u8 lcd12864_string(u8 page, u8 col, char *pstr)
{
	u8 j,page_addr, col_addr;
	char addr;

	col_addr = col;
	while(*pstr>0)
	{
		addr = *pstr++;                // 取字符代码
		addr = addr-0x20;          // 计算字符字模起始地址
		page_addr = page;		
		lcd12864_wrcmd(page|0xb0);               // 设置页地址
		lcd12864_wrcmd((col_addr>>4)|0x10);          // 设置列地址高4位
		lcd12864_wrcmd(col_addr&0x0f);               // 设置列地址低4位
		for(j=0;j<8;j++)            // 设置循环量，显示6*8点阵字符
		{
			lcd12864_wrdata(ASCIITAB[addr][j]);  //  写字模数据
		}
		page_addr += 1;
		lcd12864_wrcmd(page_addr|0xb0);               // 设置页地址
		lcd12864_wrcmd((col_addr>>4)|0x10);          // 设置列地址高4位
		lcd12864_wrcmd(col_addr&0x0f);               // 设置列地址低4位
		for(j=8;j<16;j++)            // 设置循环量，显示6*8点阵字符
		{
			lcd12864_wrdata(ASCIITAB[addr][j]);  //  写字模数据
		}
		col_addr += 8;
	}
	return col_addr;
}

//------汉字字符写入函数----------------
// 坐标(x,y)，x为水平方向像素列；y为垂直方向字符行（8点像素/行）
u8 lcd12864_HZ16_16(u8 page, u8 col, u8 *pstr, u8 num)
{
	u16 page_addr, col_addr;
	u8 j,n;
	
	col_addr = col;
	for(n=0;n<num;n++)	{		
		page_addr = page;
		lcd12864_wrcmd(0xb0 | page_addr);	// select page
		lcd12864_wrcmd(0x10 | (col_addr>>4));	    // start form column 0
		lcd12864_wrcmd(col_addr&0x0f);
		for(j=0;j<16;j++)	{
			lcd12864_wrdata(HZ16_16_CODE[*pstr][j]);
		}
		page_addr += 1;
		lcd12864_wrcmd(0xb0 | page_addr);	// select page
		lcd12864_wrcmd(0x10 | (col_addr>>4));	    // start form column 0
		lcd12864_wrcmd(0x00 | (col_addr&0x0f));
		for(j=16;j<32;j++)	{
			lcd12864_wrdata(HZ16_16_CODE[*pstr][j]);
		}
		pstr++;						
		col_addr += 16;
	}
	return col_addr;
}

lcd12864_t *bsp_lcd12864_init(void)
{
	lcd12864_t *pdev = &lcd12864;
	
	if (pdev->flags & DEF_FLAGS_12864_INIT) return pdev;

//	pdev->p_spi = &hspi2;
    bsp_lcd12864_reset();
	
//	pdev->ContrastLevel = 0x18;// default Contrast Level
	lcd12864_wrcmd(0xaf);            // display on
	lcd12864_wrcmd(0x40);            // display start line=0
    lcd12864_wrcmd(0xa0);            // ADC=0
    lcd12864_wrcmd(0xa6);            // normal display
    lcd12864_wrcmd(0xa4);            // Display all point = off
    lcd12864_wrcmd(0xa2);            // LCD bias = 1/6 (duty=1/33)
    lcd12864_wrcmd(0xc8);            // Common output mode select=reverse

    lcd12864_wrcmd(0x2f);            // Power control = all on
   	lcd12864_wrcmd(0x23);			// RA/RB setting
   	lcd12864_wrcmd(0xf8);
	lcd12864_wrcmd(0x00);// Booster Ratio Set= 2x,3x,4x (2byte command)

	lcd12864_wrcmd(0x81);            // E-Vol setting
    lcd12864_wrcmd(SysParm.LcdContrastLevel);   // (2byte command)
	lcd12864_FillRAM(0, LCD_PAGE_MAX, 0, LCD_COL_MAX, 0);//清屏
	
    pdev->flags |= DEF_FLAGS_12864_INIT;
    return pdev;
}
u8 testbuf[] = {33,0,1,2,3,4,34};
void lcd12864_test(void)
{
//lcd12864_PaintPic(2, 32, 2, 48, &bat_icon[0][0]);
//	HAL_Delay(1000);
//	lcd12864_PaintPic(2, 32, 2, 48, &bat_icon[1][0]);
//	HAL_Delay(1000);
//	lcd12864_PaintPic(2, 32, 2, 48, &bat_icon[2][0]);
//	HAL_Delay(1000);
//	lcd12864_PaintPic(2, 32, 2, 48, &bat_icon[3][0]);
//	lcd12864_HZ16_16(0, 0, testbuf, 7);
//	lcd12864_string(2,0, "ml");
}


