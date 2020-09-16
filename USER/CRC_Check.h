#ifndef _CRC_CHECK_H
#define _CRC_CHECK_H

#include "stm32l1xx_hal.h"
#include "sys_bits.h"
#include "sys_types.h"
#include "sys_defs.h"

u16 CRC16(u8 *puchMsg, u16 usDataLen);
u8 CRC8(u8 *ptr, u16 len);
u8 SumCheck(u8 *data, u8 num );
uint16_t CRC16_Sum(uint8_t *dat, uint8_t len);

#endif




























