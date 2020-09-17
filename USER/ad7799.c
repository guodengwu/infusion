#include "ad7799.h"

#define	AD7799_REF_VOLTAGE		(5120) //参考电压 mV 3304
#define	DEFAULT_VDD						(float)(3.3)
#define	AD7799_FACTOR	((FP32)AD7799_REF_VOLTAGE/(FP32)0x1000000)
_ad7799_t ad7799;

#define AD7799_DATA_READY()		HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6)

static void AD7799ChannelEnable(void);
static void CalcADCVolAverage(u8 ch, u32 adcode, u8 aver_max, u8 discard);

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
u16 mode_r,cfg_r;
static void AD7799ChannelEnable(void)
{
	ad7799_chcfg_t g_chcfg_tbl1=\
	{uCH_0, DEF_Enable,  UNIPOLAR, 0, 1, AD7799_GAIN_1_MUL};//channel_0 配置寄存器0 单极性 内部增益64
	
	bsp_ad7799_cfg_set(ad7799.pdev, &g_chcfg_tbl1);//初始化配置寄存器0 使用内部参考电压 内部增益64 用于压力采集
	bsp_ad7799_mode_set(ad7799.pdev);
	ad7799.status = AD7799_MEASURE;
	ad7799.channel = uCH_0;//起始通道
	ad7799.channel_last = uCH_2;//最后一个通道
	mode_r = bsp_ad7799_mode_get(ad7799.pdev);
	cfg_r = bsp_ad7799_cfg_get(ad7799.pdev);
}

//返回电压值mV
float CalcADCVoltageUnipolar(u32 adcode)
{
//	float adtemp;
	
//	adtemp = (adcode*1.0)/0x1000000;//单极性电压计算公式
//	return adtemp*AD7124_REF_VOLTAGE;
	return (float)adcode*AD7799_FACTOR;
}

float CalcADCVoltageBipolar(u32 adcode)
{
	float adtemp;
	
	adtemp = (adcode*1.0/0x800000) - 1;//双极性电压计算公式
	return (adtemp * AD7799_REF_VOLTAGE);
//	return adcode*AD7799_FACTOR;
}

#define	AVER_MAX		4
#define	CH_AVERNUMS		2
#define	DISCARD_NUM		1
struct _AdcCodeAver_t {
	u32 buf[AVER_MAX];
	u8 idx;
}AdcCodeAver[CH_AVERNUMS];//adc 二进制数据 均值处理
//计算每个通道电压均值（先计算adc二进制数据均值） 去掉1个最大值 1个最小值 取平均
static void CalcADCVolAverage(u8 ch, u32 adcode, u8 aver_max, u8 discard)
{	
	u8 idx;
	
	idx = AdcCodeAver[ch].idx;
	AdcCodeAver[ch].buf[idx] = adcode;
	AdcCodeAver[ch].idx ++;
	if(AdcCodeAver[ch].idx >= aver_max)	{
		u32 temp;
		 /*---------------- 冒泡排序,由小到大排序 -----------------*/
    	s8 i,j,flag;
		i=0;
		idx = AdcCodeAver[ch].idx;

		do{
			flag=0;
			for (j=0;j<idx-i-1;j++)
			{
				if (AdcCodeAver[ch].buf[j] > AdcCodeAver[ch].buf[j+1])
				{
					temp = AdcCodeAver[ch].buf[j];
					AdcCodeAver[ch].buf[j]   = AdcCodeAver[ch].buf[j+1];
					AdcCodeAver[ch].buf[j+1] = temp;
					flag = 1;
				}
			}
			i++;
		}while ((i<idx) && flag);
		/*---------------- end -----------------*/
		/*----------- 去掉1个最大值和最小值,记录最大偏差，数据进行平均 --------------*/
		temp = 0;
		j = idx - discard;
		for (i=discard;i<j;i++)
		{
			temp += AdcCodeAver[ch].buf[i];
		}
		j = idx - discard*2;
		temp /= j;
		/*---------------- end -----------------*/
//		if(ch==uCH_0)
//			ad7799.vol[ch] = CalcADCVoltageBipolar(temp)*100; //计算电压 0.01mv
//		else
			ad7799.vol[ch] = CalcADCVoltageUnipolar(temp);
		AdcCodeAver[ch].idx = 0;
	}
}
//#define	PRESS_AVER_MAX		AVER_MAX
u8 StartADDataCollect(void)
{
	u8 ad7799_err,r_channel;
	u32 ad_code;
	
	/*if(ad7799.status == AD7799_READY)	{
		bsp_ad7799_mode_set(ad7799.pdev);
		ad7799.status = AD7799_MEASURE;
	}
	else */if(ad7799.status == AD7799_MEASURE)	{
		ad7799_cs_low();	
		if(AD7799_DATA_READY())	{
			ad7799_cs_high();
			return 0;
		}
		r_channel = bsp_ad7799_conv_ready(ad7799.pdev, &ad7799_err);//回读当前采样通道
		if(ad7799_err==AD7799_ERR_NONE)	{
//			if(r_channel != ad7799.channel)	
			{
				ad7799.channel = r_channel;
				ad_code = bsp_ad7799_value_get(ad7799.pdev); //读取ADC转换结果				
				switch(r_channel)	{
					case uCH_0:	//压力传感器1
						CalcADCVolAverage(uCH_0, ad_code, AVER_MAX, DISCARD_NUM);
						break;
					case uCH_1:
						CalcADCVolAverage(uCH_1, ad_code, AVER_MAX, DISCARD_NUM);
					default:
						break;
				}
				ad7799.status = AD7799_CHANGE_CH;
			}			
		}
		else if(ad7799_err==AD7799_ERR_ACTIVE)
			ad7799.status = AD7799_CHANGE_CH;
	}
	else if(ad7799.status == AD7799_CHANGE_CH)	{
//		ad7799_chcfg_t g_chcfg_tbl1 = {uCH_0, DEF_Enable, UNIPOLAR, 0, 1, AD7799_GAIN_1_MUL};
//		if(ad7799.channel==uCH_0)	{
//			g_chcfg_tbl1.channel = uCH_1;
//			g_chcfg_tbl1.U_B = UNIPOLAR;
//		}
//		else	if(ad7799.channel==uCH_1)	{
//			g_chcfg_tbl1.channel = uCH_0;
//			g_chcfg_tbl1.U_B = UNIPOLAR;
//		}
//		bsp_ad7799_cfg_set(ad7799.pdev, &g_chcfg_tbl1);
//		bsp_ad7799_mode_set(ad7799.pdev);
		ad7799.status = AD7799_MEASURE;
	}
	return 0;
}

