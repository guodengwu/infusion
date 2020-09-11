#include "BLETask.h"
#include "bsp_ble.h"

#define BLE_CONNECT_STATE()		HAL_GPIO_ReadPin(BLE_STATE_GPIO_Port, BLE_STATE_Pin)
#define BLE_SEND_STATE()		HAL_GPIO_ReadPin(BLE_DIN_GPIO_Port, BLE_DIN_Pin)

char bletestdata[]={"hello word"};
void BLETaskInit(void)
{
	ble.state = DEF_OFF;
	bleuart_init();
}
//1s Ö´ÐÐÒ»´Î
void BLETaskProcess(void)
{
	ble.state = BLE_CONNECT_STATE();
	if(ble.state == DEF_ON&&BLE_SEND_STATE()!=DEF_Busy)	{//CONNECTED
		ble_senddata((u8 *)bletestdata, strlen(bletestdata));
	}
}
