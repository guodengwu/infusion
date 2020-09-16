#ifndef __MSG_H__
#define __MSG_H__

#include 		"sys_defs.h"
#include 		"sys_types.h"
#include 		"sys_bits.h"

typedef enum _message_src{
	MSG_NONE=0,
	MSG_KEYEVENT,
    MSG_UI, 
} message_src_t;

typedef struct _message_pkt {
    message_src_t   Src;        // ��Ϣ��Դ
    u8           Cmd;        // ����
    u16          dLen;    // ��Ϣ����
    void         *Data;       // ��Ϣ����
} message_pkt_t;

INT8U  UsartRxGetINT8U(u8 *buf,INT32U *idx);
INT16U  UsartRxGetINT16U(u8 *buf,INT32U *idx);
INT32U  UsartRxGetINT32U(u8 *buf,INT32U *idx);

#endif
