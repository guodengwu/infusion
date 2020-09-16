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
    message_src_t   Src;        // 消息来源
    u8           Cmd;        // 命令
    u16          dLen;    // 消息长度
    void         *Data;       // 消息参数
} message_pkt_t;

INT8U  UsartRxGetINT8U(u8 *buf,INT32U *idx);
INT16U  UsartRxGetINT16U(u8 *buf,INT32U *idx);
INT32U  UsartRxGetINT32U(u8 *buf,INT32U *idx);

#endif
