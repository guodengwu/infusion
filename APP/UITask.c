#include "UITask.h"
#include "KeyScanTask.h"
#include "ring_buffer.h"

message_pkt_t msg_pkt_ui[5];
RINGBUFF_T UI_Ringbuf;
static void RereshDisplay(s8 screen_id, u8 param);

void UITaskInit(void)
{
	RingBuffer_Init(&UI_Ringbuf,(message_pkt_t *)msg_pkt_ui, sizeof(message_pkt_t), 5);
	RereshDisplay(UIID_CAPACITY, NULL);
}

void StartUITask(message_pkt_t *pmsg)
{
	RingBuffer_Insert(&UI_Ringbuf, (message_pkt_t *)pmsg);
}

static void RereshDisplay(s8 screen_id, u8 param)
{
	u8 backupflag;
	
	backupflag = DEF_True;
	switch(screen_id)	{
		case UIID_CAPACITY:
			ConfirmCapacityUI(SysData.capacity);
			break;
		case UIID_SPEED:
			SpeedUI(SysData.speed, SysData.capacity);
			break;
		case UIID_COMPLETE:
			InfusionCompleteUI(SysData.speed);
			break;
		case UIID_SHUTDOWN:
			ShutDownUI(param);
			backupflag = DEF_False;
			break;
		case UIID_PAIQI:
			PaiQiUI(SysData.speed);
			break;
		case UIID_FORGET:
			break;
		default:
			return;
	}	
	if(backupflag)
		ui.screen_idbk = screen_id;
}
//1s 执行一次
void UITaskProcess(void)
{
	message_pkt_t msg;
	u8 keyvalue,ret;
	
	ret = RingBuffer_Pop(&UI_Ringbuf, &msg);//获取按钮值
	if(msg.Src == MSG_NONE||ret==0)
		return;
	
	switch(msg.Src)	{
		case MSG_KEYEVENT:
			keyvalue = msg.Cmd;
			if(keyvalue&KEY_LONGPRESS)	{
				keyvalue &= ~KEY_LONGPRESS;
			}
			else	{
				switch(keyvalue)	
				{
					case KEY_POWER:
						RereshDisplay(UIID_SHUTDOWN, 0);
						Sys.state |= SYSSTATE_SHUTDOWN_TB;
						Sys.state &= ~SYSSTATE_SHUTDOWN_YES;
						break;
					case KEY_ADD:
						if(Sys.state & SYSSTATE_SHUTDOWN_TB)	{
							RereshDisplay(UIID_SHUTDOWN, 1);
							Sys.state |= SYSSTATE_SHUTDOWN_YES;
						}
						break;
					case KEY_DEL:
						if(Sys.state & SYSSTATE_SHUTDOWN_TB)	{
							RereshDisplay(UIID_SHUTDOWN, 0);						
							Sys.state &= ~SYSSTATE_SHUTDOWN_YES;				
						}
						break;
					case KEY_SEL:
						if(Sys.state & SYSSTATE_SHUTDOWN_TB)	{
							Sys.state &= ~SYSSTATE_SHUTDOWN_TB;
							if(Sys.state & SYSSTATE_SHUTDOWN_YES)	{
								Sys.state &= ~SYSSTATE_SHUTDOWN_YES;
								Sys.state |= SYSSTATE_SHUTDOWN;
							}
							else	{
								RereshDisplay(ui.screen_idbk, NULL);
							}
						}
					default:
						break;
				}
			}
			break;
		case MSG_UI:
//			RereshDisplay(msg_pkt_ui.Cmd);
			break;
		default:
			break;		
	}
	msg.Src = MSG_NONE;
}

