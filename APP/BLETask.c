#include "BLETask.h"
#include "sys_info.h"

#define BLE_CONNECT_STATE()		HAL_GPIO_ReadPin(BLE_STATE_GPIO_Port, BLE_STATE_Pin)
#define BLE_SEND_STATE()		HAL_GPIO_ReadPin(BLE_DIN_GPIO_Port, BLE_DIN_Pin)

char bletestdata[]={"hello word"};
void BLEPackageData(void);


void BLETaskInit(void)
{
	ble.state = DEF_OFF;
	bleuart_init();
}

//1s ִ��һ��
void BLETaskProcess(void)
{
	ble.state = BLE_CONNECT_STATE();
	if(ble.state == DEF_ON&&BLE_SEND_STATE()!=DEF_Busy)	{//CONNECTED
		BLEPackageData();
	}
}
//���������ble����
void BLEPackageData(void)
{
	u8 idx,crc8;
	
	idx = 0;
	ble.puart_t->tx_buf[idx++] = PROTOCOL_TX_SD0;
	ble.puart_t->tx_buf[idx++] = _CMD_REPORT_SYSINFOR;//ָ�� �ϱ���Ϣ
	ble.puart_t->tx_buf[idx++] = g_sys_infor.pident->product_sn.ubyte[0];//�豸���
	ble.puart_t->tx_buf[idx++] = g_sys_infor.pident->product_sn.ubyte[1];
	ble.puart_t->tx_buf[idx++] = g_sys_infor.pident->product_sn.ubyte[2];
	ble.puart_t->tx_buf[idx++] = g_sys_infor.pident->product_sn.ubyte[3];
	ble.puart_t->tx_buf[idx++] = 0;//ҩ�����
	ble.puart_t->tx_buf[idx++] = SysData.weigh&0xff;//����
	ble.puart_t->tx_buf[idx++] = SysData.weigh>>8;
	ble.puart_t->tx_buf[idx++] = SysData.bat;//��ص���
	ble.puart_t->tx_buf[idx++] = SysError.Y1.ubyte;//����
	crc8 = CRC8_Sum(ble.puart_t->tx_buf, idx);//crc
	ble.puart_t->tx_buf[idx++] = crc8;
	ble.puart_t->tx_len = idx;
	ble_senddata(&ble);
}

