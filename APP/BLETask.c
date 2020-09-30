#include "BLETask.h"
#include "protocol.h"
#include "sys_info.h"

#define BLE_CONNECT_STATE()		HAL_GPIO_ReadPin(BLE_STATE_GPIO_Port, BLE_STATE_Pin)
#define BLE_SEND_STATE()		HAL_GPIO_ReadPin(BLE_DIN_GPIO_Port, BLE_DIN_Pin)

char bletestdata[]={"hello word"};
static uint8_t 			 data_buf	[20];
void BLEPackageData(void);
static uint8_t uart_message_rx_handler(_ble_usart_t *pUsart, uint8_t rx_dat);
static void BLECmdReply(void);
static void BLECmdProcess();

void BLETaskInit(void)
{
	ble.state = DEF_OFF;
	bleuart_init();
    ble.puart_t->rx_indicate = &uart_message_rx_handler;
}

//1s 执行一次
void BLETaskProcess(void)
{
	ble.state = BLE_CONNECT_STATE();
	if(ble.state == DEF_ON&&BLE_SEND_STATE()!=DEF_Busy)	{//CONNECTED
		ble.puart_t->tx_state = _CMD_REPORT_STATUS;
	}
    BLECmdProcess();//串口指令处理函数
	BLECmdReply();  //串口指令回复函数
}


static uint8_t uart_message_rx_handler(_ble_usart_t *pUsart, uint8_t rx_dat)
{
    switch (pUsart->rx_state) {
        case PRO_RX_STATE_SD0:                     /* waiting for start first  start delimiter (SD0)  */
            if(rx_dat == g_sys_infor.pident->product_sn.ubyte[0])
                pUsart->rx_state = PRO_RX_STATE_SD1; 
            else 
                pUsart->rx_state = PRO_RX_STATE_SD0;
            break;
        case PRO_RX_STATE_SD1:
            if(rx_dat == g_sys_infor.pident->product_sn.ubyte[1])
                pUsart->rx_state = PRO_RX_STATE_SD2; 
            else 
                pUsart->rx_state = PRO_RX_STATE_SD0; 
            break;
        case PRO_RX_STATE_SD2:
            if(rx_dat == g_sys_infor.pident->product_sn.ubyte[2])
                pUsart->rx_state = PRO_RX_STATE_SD3; 
            else 
                pUsart->rx_state = PRO_RX_STATE_SD0;
            break;
        case PRO_RX_STATE_SD3:
            if(rx_dat == g_sys_infor.pident->product_sn.ubyte[3]) {
                pUsart->rx_state = PRO_RX_STATE_LEN;              
                pUsart->rx_idx   = 0;
                pUsart->rx_cnt   = 0;
            }else
                pUsart->rx_state = PRO_RX_STATE_SD0; 
            break;
        case PRO_RX_STATE_LEN: 
            pUsart->rx_len      = rx_dat;
            if ((pUsart->rx_len < PRO_EXTENT_LEN) || (pUsart->rx_len > pUsart->rx_bufsize)) {
                pUsart->rx_state = PRO_RX_STATE_SD0;/* Can not handle this size ...                    */
                pUsart->rx_err   = MSG_ERR_LENGTH;
				pUsart->rx_flag		 = DEF_True;
            } else {
                pUsart->rx_crc  = rx_dat;
                pUsart->rx_state = PRO_RX_STATE_DATA;
            }
            break;
            break;
        case PRO_RX_STATE_DATA:                    /* waiting for data                                */
            if (pUsart->rx_cnt < pUsart->rx_bufsize) {
                pUsart->rx_buf[pUsart->rx_cnt++] = rx_dat;
            }
            pUsart->rx_crc += rx_dat;
            if ((pUsart->rx_len - PRO_END_LEN) <= pUsart->rx_cnt) {
                pUsart->rx_state = PRO_RX_STATE_CHKSUM;
            }
            break;
        case PRO_RX_STATE_CHKSUM:                 /* waiting for checksum                            */
             if ((pUsart->rx_crc &0XFF) == rx_dat) {
                pUsart->rx_state = PRO_RX_STATE_END;
            } else {
                pUsart->rx_state = PRO_RX_STATE_SD0;
                pUsart->rx_err   = MSG_ERR_CHECKSUM;
				pUsart->rx_flag		 = DEF_True;
            }
            break;

        case PRO_RX_STATE_END:
            if (rx_dat != PROTOCOL_TX_END) {   /* End delimiter ?                                 */
                pUsart->rx_err = MSG_ERR_ETX_WORD;
            }
			pUsart->rx_flag		 = DEF_True;
            pUsart->rx_state = PRO_RX_STATE_SD0;
            break;
        default:
            pUsart->rx_state = PRO_RX_STATE_SD0;
            pUsart->rx_err   = MSG_ERR_STATE;
			pUsart->rx_flag		 = DEF_True;
            break;
    }
	return 1;
}

//协议指令回复
static void BLECmdReply(void)
{
	uint8_t idx;
	_ble_usart_t *pUsart = ble.puart_t;
	
	if(pUsart->tx_flag == DEF_Busy)	{//发送忙 等待空闲
		return;
	}
    idx = 0;
	switch(pUsart->tx_state)	{
        case _CMD_REPORT_STATUS:       {   
            data_buf[idx++] = 0;//药袋规格
            data_buf[idx++] = SysData.weigh&0xff;//重量
            data_buf[idx++] = SysData.weigh>>8;
            data_buf[idx++] = SysData.bat;//电池电量
            data_buf[idx++] = SysError.Y1.ubyte;//故障
            pUsart->tx_idx = idx;
            ble_senddata(_CMD_REPORT_STATUS, data_buf, pUsart->tx_idx);
            break;
        }
        case _CMD_GET_ADVALUE:
            ble_senddata(_CMD_GET_ADVALUE, data_buf, pUsart->tx_idx);
            break;
		case _CMD_GET_WEIGH:
            ble_senddata(_CMD_GET_WEIGH, data_buf, pUsart->tx_idx);
            break;
        case _CMD_GET_SYSINFOR:
            break;
        case _CMD_SET_WEIGHZERO:
            break;
        case _CMD_SET_WEIGH_CALIPARAM:
            break;
        default:
            break;
	}
}

//串口指令处理函数
static void  BLECmdProcess (void)
{
	uint8_t cmd,iPara,idx;
	_ble_usart_t *pUsart = ble.puart_t;
    u16 data;

	if(pUsart->rx_flag==DEF_False)	{//无数据接收 返回
		return;
	}
    idx = 0;
	if (pUsart->rx_err == MSG_ERR_NONE) {//数据解析无错误
		cmd = UsartRxGetINT8U(pUsart->rx_buf,&pUsart->rx_idx);                                 /* First byte contains command      */
		switch(cmd)	{	
			case _CMD_GET_ADVALUE:
                iPara = UsartRxGetINT8U(pUsart->rx_buf,&pUsart->rx_idx);
                if(iPara==0x00) {//读取称重传感器电压
                    data = GetWeighVol();
                    
                }else if(iPara==0x01)   {//读取电池电压
                    data = GetBattaryVol();
                }else
                    return;
                data_buf[idx++] = data&0xff;
                data_buf[idx++] = data>>8;
                pUsart->tx_idx = idx;
                pUsart->tx_state = cmd;
                break;
            case _CMD_GET_WEIGH:
                data_buf[idx++] = SysData.weigh&0xff;
                data_buf[idx++] = SysData.weigh>>8;
                pUsart->tx_idx = idx;
                pUsart->tx_state = cmd;
                break;
            case _CMD_GET_SYSINFOR:
                iPara = UsartRxGetINT8U(pUsart->rx_buf,&pUsart->rx_idx);
//                if(iPara==)
                break;
            case _CMD_SET_WEIGHZERO:
                break;
            case _CMD_SET_WEIGH_CALIPARAM:
                break;
		}
	}else {//数据解析异常
        pUsart->rx_err = MSG_ERR_NONE;        // clear rx error
    }
    pUsart->rx_flag = 0;//清解析完成标志
	__HAL_UART_ENABLE_IT(ble.port, UART_IT_RXNE);
}

