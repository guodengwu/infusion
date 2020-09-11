#ifndef __BSP_12864_H__
#define __BSP_12864_H__

#include "includes.h"

#define DEF_FLAGS_12864_INIT       DEF_BIT00_MASK

typedef struct _lcd12864_dev {
    CPU_INT32U cs_mask;
    CPU_INT32U flags;
	SPI_HandleTypeDef	*p_spi;
    void *priv;	
	u8    ContrastLevel;     // for contrast setting level 
} lcd12864_t;

lcd12864_t *bsp_lcd12864_init(void);

#endif

