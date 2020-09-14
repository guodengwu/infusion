#include "bsp_12864.h"

#define	LCD12864_CS_LOW()				HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET)
#define	LCD12864_CS_HITH()				HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET)
#define	LCD12864_TIMEOUT				10

lcd12864_t  lcd12864;

static void bsp_lcd12864_reset(void)
{
	HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, GPIO_PIN_RESET);
	HAL_Delay(100);
	HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, GPIO_PIN_SET);
}
u8 lcd_txbuf[5];
static void lcd12864_wrcmd(u8 cmd)
{
	lcd12864_t *pdev = &lcd12864;
	
	LCD12864_CS_HITH();
	lcd_txbuf[0] = 0xf8;
	lcd_txbuf[1] = cmd&0xf0;
	lcd_txbuf[2] = (cmd<<4)&0xf0;
	HAL_SPI_Transmit(pdev->p_spi, lcd_txbuf, 3, LCD12864_TIMEOUT);
	LCD12864_CS_LOW();
	HAL_Delay(1);
}

static void lcd12864_wrdata(u8 data)
{
	lcd12864_t *pdev = &lcd12864;
	
	LCD12864_CS_HITH();
	lcd_txbuf[0] = 0xfa;
	lcd_txbuf[1] = data&0xf0;
	lcd_txbuf[2] = (data<<4)&0xf0;
	HAL_SPI_Transmit(pdev->p_spi, lcd_txbuf, 3, LCD12864_TIMEOUT);
	LCD12864_CS_LOW();
	HAL_Delay(1);
}
//清屏
void lcd12864_cls(void)
{
    lcd12864_wrcmd(0x30);    // 8-bit interface, Extended instruction
	lcd12864_wrcmd(0x01);
	HAL_Delay(5);
}

void lcd12864_displaystring(char *ptString)
{
	while((*ptString)!='\0')
	{
		lcd12864_wrdata(*ptString++);
	}
}

void lcd12864_gotoxy(u8 row, u8 col)
{
    switch(row)
    {
        case 1: lcd12864_wrcmd(0x80+col);break;
        case 2: lcd12864_wrcmd(0x90+col);break;
        case 3: lcd12864_wrcmd(0x88+col);break;
        case 4: lcd12864_wrcmd(0x98+col);break;
		default:break;
    }
}

lcd12864_t *bsp_lcd12864_init(void)
{
	lcd12864_t *pdev = &lcd12864;
	
	if (pdev->flags & DEF_FLAGS_12864_INIT) return pdev;

	pdev->p_spi = &hspi2;
    bsp_lcd12864_reset();

	lcd12864_wrcmd(0x30);           //设定为8位控制，基本指令起动
    lcd12864_wrcmd(0x34);            //设定为8位控制，扩充指令起动
	lcd12864_wrcmd(0x0c);            // 显示打开
	lcd12864_cls();                //清屏	  
	lcd12864_wrcmd(0x06);	          // 设定AC加1  
	
    pdev->flags |= DEF_FLAGS_12864_INIT;
    return pdev;
}

void lcd12864_test(void)
{
//	lcd12864_wrcmd(0x30);
	lcd12864_gotoxy(1,0);
    lcd12864_displaystring("航航航航航航航航航");
}

void  testshow(u8 fst, u8 snd)
{ 
  u8 x,y,i,k;
    
	for(i=0;i<10;i+=8)	{            //当i=0时显示上面128×32,当i=8时显示下面12*3
		for(y=0;y<32;y++)
		{     
			if((y%2)==1)
				k=fst;
			else
				k=snd;
			for(x=0;x<10;x++)
			{ 
				lcd12864_wrcmd(0x36);     //扩充指令 绘图显示
				lcd12864_wrcmd(y+0x80);    //行地址
				lcd12864_wrcmd(x+0x80+i);    //列地址            
				lcd12864_wrdata(k);
				lcd12864_wrdata(k);
				lcd12864_wrcmd(0x30);               //扩充指令 绘图关闭  
			}
		}  
	}	  
}  

