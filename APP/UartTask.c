#include "UartTask.h"
#include "sys_info.h"

#define USART_TXBUFF_SIZE		50
#define USART_RXBUFF_SIZE		50

usart_t      usart;
//_ACKData_t ack_data;
//===================================================================================================
static uint8_t       usart_rx_buf        [USART_RXBUFF_SIZE];
static uint8_t       usart_tx_buf        [USART_TXBUFF_SIZE];
static uint8_t 			 data_buf	[20];
static uint8_t uart_message_rx_handler(usart_t *pUsart, uint8_t rx_dat);
usart_t      usart;

static void UART_DataInit(void)
{
	usart.port = &huart2;
	usart.rx_state     = PRO_RX_STATE_SD0;
    usart.rx_idx       = 0;
    usart.rx_cnt       = 0;
    usart.rx_len       = 0;
    usart.rx_bufsize     = USART_RXBUFF_SIZE;
    usart.rx_crc       = 0;
    usart.rx_err       = MSG_ERR_NONE;
    usart.rx_buf       = usart_rx_buf;
	usart.rx_flag			= 0;
    usart.tx_state     = TX_STATE_NONE;
    usart.tx_idx       = 0;
    usart.tx_len       = 0;
    usart.tx_bufsize      = USART_TXBUFF_SIZE;
    usart.tx_crc       = 0;
    usart.tx_err       = MSG_ERR_NONE;
    usart.tx_buf       = usart_tx_buf;
	usart.tx_flag 			= DEF_Idle;
    usart.rx_indicate  = &uart_message_rx_handler;
    //usart.tx_complete  = &uart_message_tx_handler;
}
//串口数据发送完成
//void usart1_dma_callback(DMA_HandleTypeDef *hdma)
//{
//	usart.tx_flag = DEF_Idle;
//	usart.tx_state = TX_STATE_NONE;
//}
//打包发送数据
static void usart_senddata(uint8_t cmd, uint8_t *pdata, uint8_t len)
{
	uint8_t idx,datlen;
	uint8_t crc;

	idx = 0;
	usart.tx_flag = DEF_Busy;//串口发送忙标记
    usart.tx_buf[idx++] = g_sys_infor.pident->product_sn.ubyte[0];//设备编号
	usart.tx_buf[idx++] = g_sys_infor.pident->product_sn.ubyte[1];
	usart.tx_buf[idx++] = g_sys_infor.pident->product_sn.ubyte[2];
	usart.tx_buf[idx++] = g_sys_infor.pident->product_sn.ubyte[3];
    usart.tx_buf[idx++] = len + PRO_EXTENT_LEN;
	usart.tx_buf[idx++] = cmd;
	if (len) {
        memcpy(&usart.tx_buf[idx], pdata, len);
    }
	idx += len;
	crc = CRC8_Sum(usart.tx_buf,idx);
	usart.tx_buf[idx++] = crc;
	usart.tx_buf[idx++] = PROTOCOL_TX_END;
	usart.tx_len = idx;
	HAL_UART_Transmit(usart.port, usart.tx_buf, usart.tx_len, TX_TIMEOUT);
}

static uint8_t uart_message_rx_handler(usart_t *pUsart, uint8_t rx_dat)
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
static void UsartCmdReply(void)
{
	uint8_t idx=0;
	usart_t *pUsart = &usart;
	
	if(pUsart->tx_flag == DEF_Busy)	{//发送忙 等待空闲
		return;
	}
	switch(pUsart->tx_state)	{
        case _CMD_GET_ADVALUE:
            usart_senddata(_CMD_GET_ADVALUE, data_buf, pUsart->tx_idx);
            break;
		case _CMD_GET_WEIGH:
            usart_senddata(_CMD_GET_WEIGH, data_buf, pUsart->tx_idx);
            break;
        case _CMD_GET_SYSINFOR:
            break;
        case _CMD_SET_WEIGHZERO:
            break;
        case _CMD_SET_WEIGH_CALIPARAM:
            break;
	}
}

//串口指令处理函数
static void  UsartCmdProcess (void)
{
	uint8_t cmd,iPara,idx;
	usart_t *pUsart = &usart;
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
	__HAL_UART_ENABLE_IT(&huart1, UART_IT_RXNE);
}

void UartTaskInit(void)
{
	UART_DataInit();
}

//1s 执行一次
void UartTaskProcess(void)
{
    UsartCmdProcess();//串口指令处理函数
	UsartCmdReply();  //串口指令回复函数
}

