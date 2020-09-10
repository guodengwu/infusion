#ifndef BSP_BLE_H
#define BSP_BLE_H

/*
********************************************************************************
* Included Files
********************************************************************************
*/
#include "includes.h"

typedef struct _ble_usart{
	volatile INT8U      rx_state;
	INT8U				endflag;
	INT32U              rx_idx;
	INT32U              rx_cnt;
	INT32U              rx_len;
	INT32U              rx_bufsize;
	INT16U              rx_timeout;
	INT16U              rx_err;
	INT8U              *rx_buf;
	void (*rx_indicate)(struct _ble_usart *pUsart, INT8U rx_dat);
	
	INT8U				*tx_buf;
	INT8U 				tx_len;
	INT32U              tx_bufsize;
}_ble_usart_t;

typedef struct _ble	{
	UART_HandleTypeDef *port;
	_ble_usart_t *puart_t;
	u8 state;// «∑Ò‘⁄œﬂ
}_ble_t;

enum _bleuart_status {
	BLE_UART_IDLE,
	BLE_UART_REC,

};

extern _ble_t ble;
void bleuart_init(void);

#endif

