#ifndef _UITASK_H
#define _UITASK_H

/*
********************************************************************************
* Included Files
********************************************************************************
*/
#include "includes.h"
#include "display_ui.h"

void UITaskInit(void);
void UITaskProcess(void);
void StartUITask(message_pkt_t *pmsg);
#endif
