#ifndef __BSP_H__
#define __BSP_H__

#include "stm32l1xx_hal.h"  
#include "main.h"  
#include "sys_bits.h"
#include "sys_types.h"
#include "sys_defs.h"

#if 1
//位操作，实现51类似的GPIO控制功能
//具体实现思想，参考《M3权威指南》第五章（87页-92页）M4同M3类似，只是寄存器地址变了
//IO口操作宏定义
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 

#define SET_L(io)               io->port->BRR  = io->pin
#define SET_H(io)               io->port->BSRR = io->pin
#define IS_HIGH(io)             (io->port->IDR&io->pin)
#else
#define SET_L(io)               GPIO_ResetBits(io->port, io->pin)
#define SET_H(io)               GPIO_SetBits(io->port, io->pin)
#define IS_HIGH(io)             GPIO_ReadInputDataBit(io->port, io->pin)
#endif

#define	PWR_ON		GPIO_PIN_RESET
#define	PWR_OFF		GPIO_PIN_SET

#define	PWRCTRL_SYSON()				HAL_GPIO_WritePin(PWR_CTRL_GPIO_Port, PWR_CTRL_Pin, GPIO_PIN_SET)
#define	PWRCTRL_SYSOFF()				HAL_GPIO_WritePin(PWR_CTRL_GPIO_Port, PWR_CTRL_Pin, GPIO_PIN_RESET)
#define	PWRCTRL_SYS5V(flag)				HAL_GPIO_WritePin(PWR_5V_CTRL_GPIO_Port, PWR_5V_CTRL_Pin,flag)
#define	PWRCTRL_BUB5V(flag)				HAL_GPIO_WritePin(Bub5V_CTRL_GPIO_Port, Bub5V_CTRL_Pin,flag)
#define	PWRCTRL_LCD3_3V(flag)				HAL_GPIO_WritePin(LCD3_3V_CTRL_GPIO_Port, LCD3_3V_CTRL_Pin,flag)
//#define	PWRCTRL_LCD5V(flag)				HAL_GPIO_WritePin(LCD5V_CTRL_GPIO_Port, LCD5V_CTRL_Pin,flag)
#define	PWRCTRL_LCDBK(flag)				HAL_GPIO_WritePin(LCD_BK_CTRL_GPIO_Port, LCD_BK_CTRL_Pin,flag)
#define	PWRCTRL_AD5V(flag)				HAL_GPIO_WritePin(AD5V_CTRL_GPIO_Port, AD5V_CTRL_Pin,flag)
#define	PWRCTRL_AD3_3V(flag)				HAL_GPIO_WritePin(AD3_3V_CTRL_GPIO_Port, AD3_3V_CTRL_Pin,flag)
#define	PWRCTRL_BLE(flag)				HAL_GPIO_WritePin(BLE_SHDN_GPIO_Port, BLE_SHDN_Pin,flag)

#define	LED_RED_ON()				HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin,GPIO_PIN_RESET)
#define	LED_RED_OFF()				HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin,GPIO_PIN_SET)
#define	LED_YELLOW_ON()				HAL_GPIO_WritePin(LED_YELLOW_GPIO_Port, LED_YELLOW_Pin,GPIO_PIN_RESET)
#define	LED_YELLOW_OFF()				HAL_GPIO_WritePin(LED_YELLOW_GPIO_Port, LED_YELLOW_Pin,GPIO_PIN_SET)
#define	LED_BLUE_ON()				HAL_GPIO_WritePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin,GPIO_PIN_RESET)
#define	LED_BLUE_OFF()				HAL_GPIO_WritePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin,GPIO_PIN_SET)

#define	BEEP_ON()		HAL_GPIO_WritePin(BEEP_GPIO_Port, BEEP_Pin, GPIO_PIN_SET)
#define	BEEP_OFF()		HAL_GPIO_WritePin(BEEP_GPIO_Port, BEEP_Pin, GPIO_PIN_RESET)

enum	{
	LED_NONE=0,
	LED_BLUE=0x01,
	LED_GREEN=0x02,
	LED_RED=0X03,
};

void	bsp_init(void);
void bsp_poweron(void);
void bsp_selftest(void);
void SysShutdown(void);
#endif
