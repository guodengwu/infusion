#ifndef __BSP_12864_H__
#define __BSP_12864_H__

#include "includes.h"

#define DEF_FLAGS_12864_INIT       DEF_BIT00_MASK
#define	LCD_PAGE_MAX		4
#define	LCD_COL_MAX			132

typedef struct _lcd12864_dev {
    CPU_INT32U cs_mask;
    CPU_INT32U flags;
	SPI_HandleTypeDef	*p_spi;
    void *priv;	
	u8    ContrastLevel;     // for contrast setting level 
} lcd12864_t;

lcd12864_t *bsp_lcd12864_init(void);
void lcd12864_ClearRAM(void);
u8 lcd12864_HZ16_16(u8 x, u8 y, u8 *pstr, u8 num);
void lcd12864_string(u8 page, u8 col, char *pstr);
void lcd12864_FillRAM(u8 page_start, u8 page_end, u8 col_start, u8 col_end, u8 data);
#endif

