#ifndef __DISPLAY_UI_H__
#define __DISPLAY_UI_H__

#include "includes.h"
#include "bsp_12864.h"

typedef struct _UI	{
	s8 screen_id;//当前画面id
	s8 screen_idbk;
	u8 datlen;
	char buff[16];
}_UI_t;

enum _UI_ID	{
	UIID_CAPACITY,
	UIID_CALI_ZERO,//重量0点校准界面
	UIID_LCDCONTRAST,
	UIID_BATTARY,//电量
	UIID_BLE,
	UIID_FWVER,
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
void ShutDownUI(void);
void PaiQiUI(u16 speed);
void FWVerUI(void);
void BLE_IDUI(void);
void BattaryUI(void);
void LCDContrastLevelUI(void);
void WeighZeroCalibrateUI(void);
void UIInit(void);
void BATLowPower(void);
void BATDeadPower(void);
#endif
