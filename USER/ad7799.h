#ifndef __AD7799_H__
#define __AD7799_H__

#include "bsp_ad7799.h"

enum _ad7799_status {
	AD7799_IDLE,
	AD7799_READY,
	AD7799_GET_STATE,	
	AD7799_MEASURE,
};

typedef struct  _ad7799
{
	ad7799_dev_t *pdev;
	u8 channel_last;
	u8 channel;
	volatile u8 status;
}_ad7799_t;

#define AD7799_DATA_READY()		HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_11)

extern _ad7799_t ad7799;
void AD7799Init(void);
#endif
