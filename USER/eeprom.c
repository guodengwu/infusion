#include "eeprom.h"


#define PEKEY1	0x89ABCDEF		//FLASH_PEKEYR
#define PEKEY2	0x02030405		//FLASH_PEKEYR


 /*Func: EEPROM���ݰ��ֽڶ���
 Note:
-------------------------------------------------------------*/
void EEPROM_ReadBytes(uint16_t Addr,uint8_t *Buffer,uint16_t Length)
{
	uint8_t *wAddr;
	wAddr=(uint8_t *)(EEPROM_BASE_ADDR+Addr);
	while(Length--){
		*Buffer++=*wAddr++;
	}	
}


/*------------------------------------------------------------
 Func: EEPROM���ݶ���
 Note:
-------------------------------------------------------------*/
void EEPROM_ReadWords(uint16_t Addr,uint16_t *Buffer,uint16_t Length)
{
	uint32_t *wAddr;
	wAddr=(uint32_t *)(EEPROM_BASE_ADDR+Addr);
	while(Length--){
		*Buffer++=*wAddr++;
	}	
}
//--------------------- 

//���·ֱ�ʵ�ְ��ֽں��ַ�ʽд��
/*------------------------------------------------------------
 Func: EEPROM���ݰ��ֽ�д��
 Note:
-------------------------------------------------------------*/
void EEPROM_WriteBytes(uint16_t Addr,uint8_t *Buffer,uint16_t Length)
{
	uint8_t *wAddr;
	wAddr=(uint8_t *)(EEPROM_BASE_ADDR+Addr);
	DIS_INT
	FLASH->PEKEYR=PEKEY1;				//unlock
	FLASH->PEKEYR=PEKEY2;
	while(FLASH->PECR&FLASH_PECR_PELOCK);
	FLASH->PECR|=FLASH_PECR_PRGLOCK;		//not fast write
	while(Length--){
		*wAddr++=*Buffer++;
		while(FLASH->SR&FLASH_SR_BSY);
	}
	FLASH->PECR|=FLASH_PECR_PELOCK;
	EN_INT
}

/*------------------------------------------------------------
 Func: EEPROM���ݰ���д��
 Note: �ֵ�������
-------------------------------------------------------------*/
void EEPROM_WriteWords(uint16_t Addr,uint16_t *Buffer,uint16_t Length)
{
	uint32_t *wAddr;
	wAddr=(uint32_t *)(EEPROM_BASE_ADDR+Addr);
	DIS_INT
	FLASH->PEKEYR=PEKEY1;				//unlock
	FLASH->PEKEYR=PEKEY2;
	while(FLASH->PECR&FLASH_PECR_PELOCK);
	FLASH->PECR|=FLASH_PECR_PRGLOCK;		//not fast write
	while(Length--){
		*wAddr++=*Buffer++;
		while(FLASH->SR&FLASH_SR_BSY);
	}
	FLASH->PECR|=FLASH_PECR_PELOCK;
	EN_INT
}

