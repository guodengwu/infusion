#include "bsp.h"
#include "ad7799.h"

////////////////////////////////////
//IO≈‰÷√∫Ø ˝
void	bsp_init(void)
{
//	SoftTimerInit();
	AD7799Init();
}

void bsp_poweron(void)
{
	PWRCTRL_SYS5V(PWR_ON);
	PWRCTRL_AD5V(PWR_ON);
	PWRCTRL_AD3_3V(PWR_ON);
	HAL_Delay(10);
}

void bsp_selftest(void)
{
	LED_BLUE_ON();
	HAL_Delay(800);
	
	LED_BLUE_OFF();	
	LED_YELLOW_ON();
	HAL_Delay(800);
	
	LED_YELLOW_OFF();
	LED_RED_ON();
	BEEP_ON();
	HAL_Delay(800);
	LED_RED_OFF();
	BEEP_OFF();
}
