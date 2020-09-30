#include "bsp_ble.h"
#include "sys_info.h"

_ble_usart_t ble_uart;
_ble_t ble;
#define 	BLEUSART_RXSIZE	        32
#define 	BLE_TIMEOUT_VALUE	    10
u8 usart_rx_buf[BLEUSART_RXSIZE];
u8 usart_tx_buf[BLEUSART_RXSIZE];


//数据初始化
void bleuart_init(void)
{
	ble.port = &huart1;
	ble.puart_t = &ble_uart;
	ble.puart_t->rx_buf = usart_rx_buf;
	ble.puart_t->rx_bufsize = BLEUSART_RXSIZE;
	ble.puart_t->rx_idx = 0;
	ble.puart_t->rx_cnt = 0;
	ble.puart_t->tx_buf = (u8 *)usart_tx_buf;//usart_tx_buf;
	ble.puart_t->tx_bufsize = BLEUSART_RXSIZE;
	ble.puart_t->tx_len = 0;
	ble.state = DEF_OFF;
	__HAL_UART_ENABLE(ble.port);
}

void ble_getmac(void)
{
	ble.puart_t->tx_len = sprintf((char *)ble.puart_t->tx_buf, "AT+MAC=?");
	HAL_UART_Transmit(ble.port, ble.puart_t->tx_buf, ble.puart_t->tx_len,BLE_TIMEOUT_VALUE);
	HAL_UART_Receive(ble.port, ble.puart_t->rx_buf, 25, BLE_TIMEOUT_VALUE);
}

void ble_getfwver(void)
{
	ble.puart_t->tx_len = sprintf((char *)ble.puart_t->tx_buf, "AT+FWNM=?");
	HAL_UART_Transmit(ble.port, ble.puart_t->tx_buf, ble.puart_t->tx_len,BLE_TIMEOUT_VALUE);
	HAL_UART_Receive(ble.port, ble.puart_t->rx_buf, 13, BLE_TIMEOUT_VALUE);
}

void ble_settxpower(u8 power)
{	
	ble.puart_t->tx_len = sprintf((char *)ble.puart_t->tx_buf, "AT+TXPW=%d", power);
	HAL_UART_Transmit(ble.port, ble.puart_t->tx_buf, ble.puart_t->tx_len,BLE_TIMEOUT_VALUE);
}

void ble_setadvname(char *pstr)
{
	ble.puart_t->tx_len = sprintf((char *)ble.puart_t->tx_buf, "AT+NAME=%s", pstr);
	HAL_UART_Transmit(ble.port, ble.puart_t->tx_buf, ble.puart_t->tx_len,BLE_TIMEOUT_VALUE);
	HAL_UART_Receive(ble.port, ble.puart_t->rx_buf, 8, BLE_TIMEOUT_VALUE);
}

void ble_setadvinter(u8 dat)
{
	ble.puart_t->tx_len = sprintf((char *)ble.puart_t->tx_buf, "AT+ADIT=%d", dat);
	HAL_UART_Transmit(ble.port, ble.puart_t->tx_buf, ble.puart_t->tx_len,BLE_TIMEOUT_VALUE);
	HAL_UART_Receive(ble.port, ble.puart_t->rx_buf, 8, BLE_TIMEOUT_VALUE);
}
//串口数据发送完成
void usart1_dma_callback(DMA_HandleTypeDef *hdma)
{
	ble.puart_t->tx_flag = DEF_Idle;
	ble.puart_t->tx_state = _CMD_NONE;
}
//打包发送数据
void ble_senddata(uint8_t cmd, uint8_t *pdata, uint8_t len)
{
	uint8_t idx,datlen;
	uint8_t crc;

	idx = 0;
	ble.puart_t->tx_flag = DEF_Busy;//串口发送忙标记
    ble.puart_t->tx_buf[idx++] = g_sys_infor.pident->product_sn.ubyte[0];//设备编号
	ble.puart_t->tx_buf[idx++] = g_sys_infor.pident->product_sn.ubyte[1];
	ble.puart_t->tx_buf[idx++] = g_sys_infor.pident->product_sn.ubyte[2];
	ble.puart_t->tx_buf[idx++] = g_sys_infor.pident->product_sn.ubyte[3];
    ble.puart_t->tx_buf[idx++] = len + PRO_EXTENT_LEN;
	ble.puart_t->tx_buf[idx++] = cmd;
	if (len) {
        memcpy(&ble.puart_t->tx_buf[idx], pdata, len);
    }
	idx += len;
	crc = CRC8_Sum(ble.puart_t->tx_buf,idx);
	ble.puart_t->tx_buf[idx++] = crc;
	ble.puart_t->tx_buf[idx++] = PROTOCOL_TX_END;
	ble.puart_t->tx_len = idx;
	HAL_UART_Transmit_DMA(ble.puart_t->port, ble.puart_t->tx_buf, ble.puart_t->tx_len);
}
//ble接受数据
void ble_ready2rec(u8 data)
{
	if(data==DEF_True)	{
		ble.puart_t->rx_state = BLE_UART_REC;
		ble.puart_t->rx_cnt = 0;
		__HAL_UART_ENABLE_IT(ble.port, UART_IT_RXNE);          //使能串口接收FIFO非空中断
	}
	else if(data==DEF_False)	{
		ble.puart_t->rx_state = BLE_UART_IDLE;
		__HAL_UART_DISABLE_IT(ble.port, UART_IT_RXNE); 
	}
}


