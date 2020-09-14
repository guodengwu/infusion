#ifndef __DISPLAY_UI_H__
#define __DISPLAY_UI_H__

#include "includes.h"

typedef struct _UI	{
	s8 screen_id;//µ±Ç°»­Ãæid
	u8 datlen;
	char buff[16];
}_UI_t;

enum _UI_ID	{
	UIID_MAIN,
	UIID_SPEED,
	UIID_COMPLETE,
	UIID_PWROFF,
	UIID_PAIQI,
	UIID_FORGET,
	UIID_LOWPOWER,
	UIID_POWERDEAD,
	UIID_ERR,
};

void ConfirmCapacity(u16 data);
#endif
