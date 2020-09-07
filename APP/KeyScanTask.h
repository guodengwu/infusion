#ifndef __KEYSCANTASK_H__
#define __KEYSCANTASK_H__

#include "includes.h"

//key1-10 1--°´ÏÂ£»0--Ì§Æð
#define	KEY_1					DEF_BIT00_MASK
#define	KEY_2					DEF_BIT01_MASK
#define	KEY_3					DEF_BIT02_MASK
#define	KEY_4					DEF_BIT03_MASK
#define	KEY_LONGPRESS					DEF_BIT07_MASK

#define	KEY_NONE			0
#define	KEY_OK			KEY_1
#define	KEY_ADD			KEY_2
#define	KEY_DEL			KEY_3
#define	KEY_SEL			KEY_4

void KeyScanTaskInit(void);
void KeyScanTaskProcess(void);
#endif
