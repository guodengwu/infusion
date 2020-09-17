#ifndef _MISC_H
#define _MISC_H

#include "includes.h"

float CalculateTemperature(u32 Rt,const u32 Rp,const u32 Bx);
void delay_ms(u16 ms);
s32 floatToInt(float f);
INT16U CRC16_Sum(INT8U *dat, INT8U len);
u8 BubbleSort(u8 *pbuf,u32 size);
u8 BCD_Decimal(u8 bcd);
s16 FUN_MIN16S(s16 x, s16 y);
void split(char *src,const char *separator,char **dest,u16 *num);
void findbuff_min(s32 *pbuf, u8 size, u32 *max, u8 *idx);
void findbuff_max(s32 *pbuf, u8 size, u32 *max, u8 *idx);
#endif
