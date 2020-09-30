#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__

#include "sys_bits.h"
#include "sys_types.h"
#include "sys_defs.h"
#include "stm32l1xx_hal.h"

#define BUFF_SIZE                      100u

//#define MSG_SYSTEM_ACK_CMD              0x78    // 系统应答命令
//#define MSG_ABNORMAL_CMD                0x79    // 消息错误命令
#define  PROTOCOL_RX_SD0        0x02           /* Start delimiters                                */
//#define  PROTOCOL_RX_SD1        0x7E
#define  PROTOCOL_RX_END        0x03           /* End   delimiter                                 */
                                                     /* Outbound packets (to NIOS-II)                   */
#define  PROTOCOL_TX_SD0        0x02           /* Start delimiters                                */
//#define  PROTOCOL_TX_SD1        0x7E
#define  PROTOCOL_TX_END        0x03           /* End   delimiter                                 */

#define	 PRO_CMD_POSITION     6
#define	 PRO_LENGTH_SIZE     4                                               ///< 消息中Length所占字节数
#define  PRO_START_LEN       5                                               ///< 4字节长度 + 1字节命令
#define  PRO_EXTENT_LEN      3                                               ///< 1字节命令 + 2字节校验和 + 1字节结束符
#define  PRO_END_LEN         2                                               ///< 2字节校验和 + 1字节结束符

#define  PRO_RX_STATE_SD0              0           /* waiting for start first  start delimiter (SD0)  */
#define  PRO_RX_STATE_SD1              1
#define  PRO_RX_STATE_SD2              2
#define  PRO_RX_STATE_SD3              3
#define  PRO_RX_STATE_LEN              4
#define  PRO_RX_STATE_CMD              5
#define  PRO_RX_STATE_DATA             6           /* waiting for data                                */
#define  PRO_RX_STATE_CHKSUM          7           /* waiting for checksum0 low byte                  */
#define  PRO_RX_STATE_END              8           /* waiting for end delimiter                       */

#define  _CMD_READ          1
#define  _CMD_WRITE         2

typedef enum { 
    _CMD_REPORT_STATUS			=	0X00,//上报设备状态
    _CMD_EXECUTE_SYS_INFOR			=	0X02,//执行系统配置信息修改
	_CMD_GET_ADVALUE 	=	0xE0,//读取AD测量值
	_CMD_GET_WEIGH 	=	0xE1,//读取重量值
	_CMD_GET_SYSINFOR 	=	0xE2,//读取设备信息
	_CMD_SET_WEIGHZERO 	=	0xE3,//重量零点标定
	_CMD_SET_WEIGH_CALIPARAM 	=	0xE4,//设置重量校准参数
    _CMD_NONE = 0xff,
} EMessageCmd;

enum MSG_ERR {
    MSG_ERR_NONE              =  0x0000u, // 无消息错误
    MSG_ERR_LENGTH      =  0xFFF8u, 
	MSG_ERR_DEVID      		 =  0xFFF9u, // 消息长度错误代码
	MSG_ERR_CHECKSUM          =  0xFFFAu, // 消息校验和错误代码
	MSG_ERR_ETX_WORD          =  0xFFFBu, // 消息结束符错误代码
	MSG_ERR_UNDEFINITION      =  0xFFFCu, // 消息命令未定义错误代码
	MSG_ERR_IAP_MODE          =  0xFFFDu, // 当前处于IAP模式
	MSG_ERR_STATE             =  0xFFFEu, // 消息未定义状态
	MSG_ERR_TIMEOUT		     =  0xFFF7u, // 消息接收超时
};

typedef enum { 
	ACK_Fail = 0x00,//
	ACK_OK = 0x01, //
	ACK_Error = 0x02, 
	ACK_Busy = 0x03 
} AckType;

uint8_t  UsartRxGetINT8U (uint8_t *buf,uint32_t *idx);
uint16_t  UsartRxGetINT16U (uint8_t *buf,uint32_t *idx);
uint32_t  UsartRxGetINT32U (uint8_t *buf,uint32_t *idx);
void GetProductInfor(void);
#endif
