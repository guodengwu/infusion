#include "KeyScanTask.h"

#define	READ_KEY1()				HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_Pin)
#define	READ_KEY2()				HAL_GPIO_ReadPin(KEY2_GPIO_Port, KEY2_Pin)
#define	READ_KEY3()				HAL_GPIO_ReadPin(KEY3_GPIO_Port, KEY3_Pin)
#define	READ_KEY4()				HAL_GPIO_ReadPin(KEY4_GPIO_Port, KEY4_Pin)

#define KEYSCAN_NUM				10
#define KEYLONGPRESS_NUM		300
#define KEYNIANLIAN_NUM			3000

u8 gKeyValue;

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
	static u16 ShortPressCnt,LongPressCnt;
	
	KeyVal = (~ReadKeyVal())&0x0f;
	if(KeyVal != KeyVal_bk)	{//�а���״̬�仯
		if(ShortPressCnt >= KEYSCAN_NUM)	{				
			if(KeyVal==0)	{//
					//BSP_PRINTF("KEY Release:%x",keyscan.keyval);
			}
			else	{//�а�������
				gKeyValue = KeyVal&~KeyVal_bk;//���ϴ�δrelease�İ��� ���˵�
//					BSP_PRINTF("KEY Press:%x",keyscan.keyval);
			}
			KeyVal_bk = KeyVal;
		}
		else	{
			ShortPressCnt ++;
		}
	}
	else	{
		if(KeyVal!=0)	{//�������ʹ���
			if(LongPressCnt >= KEYNIANLIAN_NUM)	{//������� ��������30s
			}		
			else if(LongPressCnt >= KEYLONGPRESS_NUM)	{//���� ��������2s
				gKeyValue |= KEY_LONGPRESS;
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
//10ms ִ��һ��
void KeyScanTaskProcess(void)
{
	KeyScan();
	if(gKeyValue&KEY_LONGPRESS)	{
		gKeyValue = KEY_NONE;
	}
	else	{
		if(gKeyValue == KEY_OK)	{
			PWRCTRL_SYSOFF();
		}
		gKeyValue = KEY_NONE;
	}
}
