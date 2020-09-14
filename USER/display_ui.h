#ifndef __DISPLAY_UI_H__
#define __DISPLAY_UI_H__

#include "includes.h"
#include "bsp_12864.h"

typedef struct _UI	{
	s8 screen_id;//µ±Ç°»­Ãæid
	s8 screen_idbk;
	u8 datlen;
	char buff[16];
}_UI_t;

enum _UI_ID	{
	UIID_CAPACITY,
	UIID_SPEED,
	UIID_COMPLETE,
	UIID_SHUTDOWN,
	UIID_PAIQI,
	UIID_FORGET,
	UIID_LOWPOWER,
	UIID_POWERDEAD,
	UIID_ERR,
};

extern _UI_t ui;
void ConfirmCapacityUI(u16 cap);
void InfusionCompleteUI(u16 speed);
void SpeedUI(u16 speed, u16 cap);
void ShutDownUI(u8 flag);
void PaiQiUI(u16 speed);
#endif
