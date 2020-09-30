#ifndef BSP_BLE_H
#define BSP_BLE_H

/*
********************************************************************************
* Included Files
********************************************************************************
*/
#include "includes.h"

typedef struct _ble_usart{
	UART_HandleTypeDef *port;
    volatile uint8_t               rx_state;
	uint32_t              rx_devid;
    uint32_t              rx_idx;
    uint32_t              rx_cnt;
    uint32_t              rx_len;
    uint32_t              rx_bufsize;
    uint16_t              rx_crc;
    uint16_t              rx_err;
    uint8_t              *rx_buf;
	volatile uint8_t	 rx_flag;
    uint8_t (*rx_indicate)(struct _ble_usart *pUsart, uint8_t rx_dat);

    volatile uint8_t               tx_state;
    uint32_t              tx_idx;
    uint32_t              tx_len;
    uint32_t              tx_bufsize;
    uint16_t              tx_crc;
    uint16_t              tx_err;
    uint8_t              *tx_buf;
	volatile uint8_t								tx_flag;
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
void ble_senddata(uint8_t cmd, uint8_t *pdata, uint8_t len);
#endif

