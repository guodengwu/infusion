#ifndef __AD7799_H__
#define __AD7799_H__

#include "bsp_ad7799.h"

enum _ad7799_status {
	AD7799_IDLE,
	AD7799_READY,
	AD7799_CHANGE_CH,	
	AD7799_MEASURE,
};

typedef struct  _ad7799
{
	ad7799_dev_t *pdev;
	u8 channel_last;
	u8 channel;
	volatile u8 status;
	u32 vol[3];
}_ad7799_t;

extern _ad7799_t ad7799;
void AD7799Init(void);
u8 StartADDataCollect(void);
u16 GetBattaryVol(void);
#endif
