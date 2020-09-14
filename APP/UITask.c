#include "UITask.h"
#include "display_ui.h"

message_pkt_t msg_pkt_ui;

void UITaskInit(void)
{
	ConfirmCapacityUI(0xff);
}

void StartUITask(message_pkt_t *pmsg)
{
	msg_pkt_ui.Src = pmsg->Src;
	msg_pkt_ui.Cmd = pmsg->Cmd;
}

void RereshDisplay(s8 screen_id)
{
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
//			ShutDownUI(0);
			break;
		case UIID_PAIQI:
			PaiQiUI(SysData.speed);
			break;
		case UIID_FORGET:
			break;
		default:
			return;
	}
	ui.screen_idbk = screen_id;
}
//1s Ö´ÐÐÒ»´Î
void UITaskProcess(void)
{
	switch(msg_pkt_ui.Src)	{
		case UI_MSG:
			RereshDisplay(msg_pkt_ui.Cmd);
			break;
		case UIBK_MSG:
			RereshDisplay(ui.screen_idbk);
			break;
		default:
			msg_pkt_ui.Src = MSG_NONE;
			return;
		msg_pkt_ui.Src = MSG_NONE;
	}
}