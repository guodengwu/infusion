#ifndef __UARTTASK_H__
#define __UARTTASK_H__

#include "protocol.h"

#define  TX_STATE_NONE      0
#define  TX_TIMEOUT      50

typedef struct _usart {
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
	volatile uint8_t								rx_flag;
    uint8_t (*rx_indicate)(struct _usart *pUsart, uint8_t rx_dat);

    volatile uint8_t               tx_state;
    uint32_t              tx_idx;
    uint32_t              tx_len;
    uint32_t              tx_bufsize;
    uint16_t              tx_crc;
    uint16_t              tx_err;
    uint8_t              *tx_buf;
	volatile uint8_t								tx_flag;
	//volatile uint8_t								tx_busy;
    //void (*tx_complete)(struct _usart *pUsart);
} usart_t;

extern usart_t      usart;
void UartTaskInit(void);
void UartTaskProcess(void);

#endif
