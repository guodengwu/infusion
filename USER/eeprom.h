#ifndef __EEPROM_H__
#define __EEPROM_H__


#include "stm32l1xx_hal.h"

#define EEPROM_BASE_ADDR	0x08080000	
#define EEPROM_BYTE_SIZE	0x07FF


#define EN_INT      	__enable_irq();		//系统开全局中断
#define DIS_INT     	__disable_irq();	//系统关全局中断

void  EEPROM_ReadBytes(uint16_t Addr,uint8_t *Buffer,uint16_t Length);
void  EEPROM_ReadWords(uint16_t Addr,uint16_t *Buffer,uint16_t Length);
void EEPROM_WriteBytes(uint16_t Addr,uint8_t *Buffer,uint16_t Length);
void EEPROM_WriteWords(uint16_t Addr,uint16_t *Buffer,uint16_t Length);

#endif
