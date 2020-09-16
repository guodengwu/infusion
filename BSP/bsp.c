#include "bsp.h"
#include "ad7799.h"
#include "bsp_12864.h"
#include "bsp_ble.h"
////////////////////////////////////
//IO���ú���
void	bsp_init(void)
{
//	SoftTimerInit();
	AD7799Init();
	bsp_lcd12864_init();
}

void bsp_poweron(void)
{
	PWRCTRL_SYS5V(PWR_ON);
	PWRCTRL_AD5V(PWR_ON);
	PWRCTRL_AD3_3V(PWR_ON);
	PWRCTRL_LCD5V(PWR_ON);
	PWRCTRL_LCD3_3V(PWR_ON);
	PWRCTRL_BLE(PWR_ON);
	HAL_Delay(10);
}

void bsp_selftest(void)
{
	LED_BLUE_ON();
	HAL_Delay(600);
	
	LED_BLUE_OFF();	
	LED_YELLOW_ON();
	HAL_Delay(600);
	
	LED_YELLOW_OFF();
	LED_RED_ON();
//	BEEP_ON();
	HAL_Delay(600);
	LED_RED_OFF();
	BEEP_OFF();
}

void SysShutdown(void)
{
	PWRCTRL_SYSOFF();
}
