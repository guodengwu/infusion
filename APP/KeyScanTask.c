#include "KeyScanTask.h"
#include "UITask.h"

#define	READ_KEY1()				HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_Pin)
#define	READ_KEY2()				HAL_GPIO_ReadPin(KEY2_GPIO_Port, KEY2_Pin)
#define	READ_KEY3()				HAL_GPIO_ReadPin(KEY3_GPIO_Port, KEY3_Pin)
#define	READ_KEY4()				HAL_GPIO_ReadPin(KEY4_GPIO_Port, KEY4_Pin)

#define KEYSCAN_NUM				10//每10ms扫描一次按键，确认10次
#define KEYLONGPRESS_NUM		300
#define KEYNIANLIAN_NUM			3000

u8 gKeyValue;
message_pkt_t msg_pkt_keyscan;

static u8 ReadKeyVal(void)
{
	BIT8 key;
	
	do	{
		key.bits.b0 = READ_KEY1();
		key.bits.b1 = READ_KEY2();
		key.bits.b2 = READ_KEY3();
		key.bits.b3 = READ_KEY4();
	}while(0);
	return key.ubyte;
}

static void KeyScan(void)
{
	static u8 KeyVal,KeyVal_bk;
	static u16 ShortPressCnt,LongPressCnt,PressSendCnt;
	
	KeyVal = (~ReadKeyVal())&0x0f;
	if(KeyVal != KeyVal_bk)	{//有按键状态变化
		if(ShortPressCnt >= KEYSCAN_NUM)	{				
			if(KeyVal==0)	{//
					//BSP_PRINTF("KEY Release:%x",keyscan.keyval);
			}
			else	{//有按键按下
//				gKeyValue = KeyVal&~KeyVal_bk;//将上次未release的按键 过滤掉
				gKeyValue = KeyVal;
			}
			KeyVal_bk = KeyVal;
		}
		else	{
			ShortPressCnt ++;
		}
	}
	else	{
		if(KeyVal!=0)	{//长按类型处理
			if(LongPressCnt >= KEYNIANLIAN_NUM)	{//按键黏连 连续按下30s
			}		
			else if(LongPressCnt >= KEYLONGPRESS_NUM)	{//长按 连续按下3s
				if(PressSendCnt>=60)	{//600ms通报一次长按事件
					PressSendCnt = 0;
					gKeyValue = KeyVal| KEY_LONGPRESS;
				}
				else
					PressSendCnt ++;
			}
			LongPressCnt++;
		}
		else {
			LongPressCnt = 0;
			ShortPressCnt = 0;			
		}
	}
}

void KeyScanTaskInit(void)
{
	gKeyValue = KEY_NONE;
}
//10ms 执行一次
void KeyScanTaskProcess(void)
{
	KeyScan();
	if(gKeyValue != KEY_NONE)	{
		msg_pkt_keyscan.Src = MSG_KEYEVENT;
		msg_pkt_keyscan.Cmd = gKeyValue;
		StartUITask(&msg_pkt_keyscan);
		gKeyValue = KEY_NONE;
	}
}
