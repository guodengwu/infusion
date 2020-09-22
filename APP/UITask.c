#include "UITask.h"
#include "KeyScanTask.h"
#include "ring_buffer.h"
#include "save_data.h"

message_pkt_t msg_pkt_ui[5];
RINGBUFF_T UI_Ringbuf;
static void RereshDisplay(s8 screen_id, u8 param);

void UITaskInit(void)
{
	UIInit();
	RingBuffer_Init(&UI_Ringbuf,(message_pkt_t *)msg_pkt_ui, sizeof(message_pkt_t), 5);
	RereshDisplay(UIID_CAPACITY, NULL);
}

void StartUITask(message_pkt_t *pmsg)
{
	RingBuffer_Insert(&UI_Ringbuf, (message_pkt_t *)pmsg);
}
#include "ad7799.h"
static void RereshDisplay(s8 screen_id, u8 param)
{
	switch(screen_id)	{
		case UIID_CAPACITY:
//			ConfirmCapacityUI(SysData.capacity);
			ConfirmCapacityUI(ad7799.vol[1]);
			break;
		case UIID_CALI_ZERO://重量0点校准界面
			WeighZeroCalibrateUI();
			break;
		case UIID_LCDCONTRAST:
			LCDContrastLevelUI();
			break;
		case UIID_BATTARY://电量
			BattaryUI();
			break;
		case UIID_BLE:
			BLE_IDUI();
			break;
		case UIID_FWVER:
			FWVerUI();
			break;
		case UIID_SPEED:
			SpeedUI(SysData.speed, SysData.capacity);
			break;
		case UIID_COMPLETE:
			InfusionCompleteUI(SysData.speed);
			break;
		case UIID_SHUTDOWN:
			ShutDownUI();
			break;
		case UIID_PAIQI:
			PaiQiUI(SysData.speed);
			break;
		case UIID_FORGET:
			break;
		case UIID_LOWPOWER:
			BATLowPower();
			break;
		case UIID_POWERDEAD:
			BATDeadPower();
		default:
			return;
	}	
	ui.screen_id = screen_id;
}
//100ms 执行一次
void UITaskProcess(void)
{
	message_pkt_t msg;
	u8 keyvalue,ret;
	static u8 timecnt;
	
	ret = RingBuffer_Pop(&UI_Ringbuf, &msg);//获取按钮值
	if(msg.Src != MSG_NONE&&ret!=0)//按键事件有效
	{		
		switch(msg.Src)	{
			case MSG_KEYEVENT:
				keyvalue = msg.Cmd;
				if(keyvalue&KEY_LONGPRESS)	{
					keyvalue &= ~KEY_LONGPRESS;
					switch(keyvalue)	
					{
						case KEY_POWER:
							RereshDisplay(UIID_SHUTDOWN, NULL);
							Sys.state |= SYSSTATE_SHUTDOWN;
							break;
	//					case KEY_ADD:
	//						if(ui.screen_id == UIID_LCDCONTRAST)	{
	//							lcd12864_LCDLighter();
	//							RereshDisplay(ui.screen_id, NULL);
	//						}
	//						break;
	//					case KEY_DEL:
	//						if(ui.screen_id == UIID_LCDCONTRAST)	{
	//							lcd12864_LCDDarker();
	//							RereshDisplay(ui.screen_id, NULL);
	//						}
	//						break;
						default:
							break;
					}
				}
	//			else	
				{
					switch(keyvalue)	
					{
						case KEY_ADD:
							if(ui.screen_id == UIID_LCDCONTRAST)	{
								lcd12864_LCDLighter();
								RereshDisplay(ui.screen_id, NULL);
								eeprom_data.type = SaveDataType_SYSPARAM;
								eeprom_data.pbuf = (u8 *)&SysParm;//保存系统参数
								eeprom_data.len = sizeof(SysParm);
							}
							break;
						case KEY_DEL:
							if(ui.screen_id == UIID_LCDCONTRAST)	{
								lcd12864_LCDDarker();
								RereshDisplay(ui.screen_id, NULL);
								eeprom_data.type = SaveDataType_SYSPARAM;
								eeprom_data.pbuf = (u8 *)&SysParm;//保存系统参数	
								eeprom_data.len = sizeof(SysParm);							
							}
							break;
						case KEY_SEL:
							if(ui.screen_id == UIID_PAIQI)	{
								SysError.Y1.bits.b7 = DEF_False;//消除气泡报警
							}
							break;
						case (KEY_SEL+KEY_ADD):	
							ui.screen_id++;
							if(ui.screen_id > UIID_FWVER)	{
								ui.screen_id = UIID_CAPACITY;
							}
							RereshDisplay(ui.screen_id, NULL);						
							break;
						case (KEY_SEL+KEY_DEL):
							ui.screen_id--;
							if(ui.screen_id < UIID_CAPACITY)	{
								ui.screen_id = UIID_FWVER;
							}
							RereshDisplay(ui.screen_id, NULL);	
							break;
						default:
							break;
					}
				}
				break;
			case MSG_UI:
				RereshDisplay(msg.Cmd, NULL);
				break;
			default:
				break;		
		}
	}
	timecnt++;
	if(timecnt>10)	{//时间轮询事件 1s刷新
		if(ui.screen_id==UIID_CAPACITY)
			RereshDisplay(ui.screen_id, NULL);
		timecnt = 0;
	}
	msg.Src = MSG_NONE;
}

