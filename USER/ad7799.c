#include "ad7799.h"

#define	AD7799_REF_VOLTAGE		(3300) //参考电压 mV 3304
#define	DEFAULT_VDD						(float)(3.3)
#define	AD7799_FACTOR	((FP32)AD7124_REF_VOLTAGE/(FP32)0x1000000)
_ad7799_t ad7799;

static void AD7799ChannelEnable(void);

u8 ad7799_id;
void AD7799Init(void)
{
//	u8 ad7124_id;

	ad7799.status = AD7799_IDLE;
	ad7799.channel = uCH_0;
	ad7799.channel_last = uCH_0;
	
	ad7799.pdev = bsp_ad7799_init(AD7799_ID1);
	ad7799_id = bsp_ad7799_id_get(ad7799.pdev);
	if((ad7799_id&0x0f) == AD7799_ID)	{\
	
	}
	AD7799ChannelEnable();
}

static void AD7799ChannelEnable(void)
{
	ad7799_chcfg_t g_chcfg_tbl1=\
	{uCH_0, DEF_Enable,  BIPOLAR, 0, 1, AD7799_GAIN_1_MUL};//channel_0 配置寄存器0 单极性 内部增益64
	
	bsp_ad7799_cfg_set(ad7799.pdev, &g_chcfg_tbl1);//初始化配置寄存器0 使用内部参考电压 内部增益64 用于压力采集
	bsp_ad7799_mode_set(ad7799.pdev);
}

u8 StartADDataCollect(void)
{
	
}
