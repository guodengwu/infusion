#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__

#include "sys_bits.h"
#include "sys_types.h"
#include "sys_defs.h"
#include "stm32l1xx_hal.h"

#define BUFF_SIZE                      100u

//#define MSG_SYSTEM_ACK_CMD              0x78    // ϵͳӦ������
//#define MSG_ABNORMAL_CMD                0x79    // ��Ϣ��������
#define  PROTOCOL_RX_SD0        0x02           /* Start delimiters                                */
//#define  PROTOCOL_RX_SD1        0x7E
#define  PROTOCOL_RX_END        0x03           /* End   delimiter                                 */
                                                     /* Outbound packets (to NIOS-II)                   */
#define  PROTOCOL_TX_SD0        0x02           /* Start delimiters                                */
//#define  PROTOCOL_TX_SD1        0x7E
#define  PROTOCOL_TX_END        0x03           /* End   delimiter                                 */

#define	 PRO_CMD_POSITION     6
#define	 PRO_LENGTH_SIZE     4                                               ///< ��Ϣ��Length��ռ�ֽ���
#define  PRO_START_LEN       5                                               ///< 4�ֽڳ��� + 1�ֽ�����
#define  PRO_EXTENT_LEN      3                                               ///< 1�ֽ����� + 2�ֽ�У��� + 1�ֽڽ�����
#define  PRO_END_LEN         2                                               ///< 2�ֽ�У��� + 1�ֽڽ�����

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
    _CMD_REPORT_STATUS			=	0X00,//�ϱ��豸״̬
    _CMD_EXECUTE_SYS_INFOR			=	0X02,//ִ��ϵͳ������Ϣ�޸�
	_CMD_GET_ADVALUE 	=	0xE0,//��ȡAD����ֵ
	_CMD_GET_WEIGH 	=	0xE1,//��ȡ����ֵ
	_CMD_GET_SYSINFOR 	=	0xE2,//��ȡ�豸��Ϣ
	_CMD_SET_WEIGHZERO 	=	0xE3,//�������궨
	_CMD_SET_WEIGH_CALIPARAM 	=	0xE4,//��������У׼����
    _CMD_NONE = 0xff,
} EMessageCmd;

enum MSG_ERR {
    MSG_ERR_NONE              =  0x0000u, // ����Ϣ����
    MSG_ERR_LENGTH      =  0xFFF8u, 
	MSG_ERR_DEVID      		 =  0xFFF9u, // ��Ϣ���ȴ������
	MSG_ERR_CHECKSUM          =  0xFFFAu, // ��ϢУ��ʹ������
	MSG_ERR_ETX_WORD          =  0xFFFBu, // ��Ϣ�������������
	MSG_ERR_UNDEFINITION      =  0xFFFCu, // ��Ϣ����δ����������
	MSG_ERR_IAP_MODE          =  0xFFFDu, // ��ǰ����IAPģʽ
	MSG_ERR_STATE             =  0xFFFEu, // ��Ϣδ����״̬
	MSG_ERR_TIMEOUT		     =  0xFFF7u, // ��Ϣ���ճ�ʱ
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
