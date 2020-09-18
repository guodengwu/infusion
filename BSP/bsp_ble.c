#include "bsp_ble.h"

_ble_usart_t ble_uart;
_ble_t ble;
#define 	BLEUSART_RXSIZE	32
#define	BLE_TIMEOUT_VALUE	10
u8 usart_rx_buf[BLEUSART_RXSIZE];
u8 usart_tx_buf[BLEUSART_RXSIZE];
static void uart_message_rx_handler(_ble_usart_t *pUsart, INT8U rx_dat);

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
	ble.puart_t->rx_indicate = &uart_message_rx_handler;
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

void ble_senddata(_ble_t *pBle_t)
{
	HAL_UART_Transmit(pBle_t->port, pBle_t->puart_t->tx_buf, pBle_t->puart_t->tx_len, BLE_TIMEOUT_VALUE);
}

void ble_ready2rec(u8 data)
{
//	if(data==DEF_True)	{
//		ble.puart_t->rx_state = BLE_UART_REC;
//		ble.puart_t->rx_cnt = 0;
//		__HAL_UART_ENABLE_IT(ble.port, UART_IT_RXNE);          //使能串口接收FIFO非空中断
//	}
//	else if(data==DEF_False)	{
//		ble.puart_t->rx_state = BLE_UART_IDLE;
//		__HAL_UART_DISABLE_IT(ble.port, UART_IT_RXNE); 
//	}
}

static void uart_message_rx_handler(_ble_usart_t *pUsart, uint8_t rx_dat)
{
	if(pUsart->rx_state == BLE_UART_REC)	{
		pUsart->rx_buf[pUsart->rx_cnt] = rx_dat;
		pUsart->rx_cnt++;
	}
}
