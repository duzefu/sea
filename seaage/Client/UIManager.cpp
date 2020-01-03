/*
**	UIManager.cpp 
**	UI manager functions
**
**	Jack, 2003.1.21
*/
#include "MainFun.h"
#include "NetGE_MainFunc.h"
#include "UIManager.h"
#include "QQMsgBox.h"
#include "QQEdit.h"
#include "CmdEvent.h"
#include "Client_SendMsg.h"


/************************************************************************************************************/
/* DEFINES & STRUCTURES                                                                                     */
/************************************************************************************************************/
typedef	struct tagEVENT_UI_CONTROL
{
	SLONG	current_ui;
} EVENT_UI_CONTROL, *LPEVENT_UI_CONTROL;


EVENT_UI_CONTROL	l_event_ui_control;


/************************************************************************************************************/
/* UI MANAGER FUNCTIONS                                                                                     */
/************************************************************************************************************/
int		init_event_ui(void)
{
	if(0 != init_game_talk())
	{
		log_error(1, "init game talk error");
		return	-1;
	}
	if(0 != init_game_choice())
	{
		log_error(1, "init game choice error");
		return	-2;
	}
	if(0 != init_ui_shop())
	{
		log_error(1, "init game trade shop error");
		return	-3;
	}
	if(0 != init_ui_store())
	{
		log_error(1, "init game store shop error");
		return	-4;
	}

	memset(&l_event_ui_control, 0, sizeof(l_event_ui_control));

	return	0;
}


void	free_event_ui(void)
{
	free_game_choice();
	free_game_talk();
	free_ui_shop();
	free_ui_store();

	memset(&l_event_ui_control, 0, sizeof(l_event_ui_control));
}


void	active_event_ui(int active)
{
	active_game_talk(active);
	active_game_choice(active);
	//active_ui_shop(active);
	active_ui_store(active);
}


void	close_last_event_ui(void)
{
	switch(l_event_ui_control.current_ui)
	{
	case UI_TYPE_GAME_TALK:
		open_game_talk(FALSE);
		break;
	case UI_TYPE_GAME_CHOICE:
		open_game_choice(FALSE);
		break;
	case UI_TYPE_TRADE_SHOP:
		open_ui_shop(FALSE);
		break;
	case UI_TYPE_STORE_SHOP:
		open_ui_store(FALSE);
		break;
	default:
		break;
	}
	l_event_ui_control.current_ui = 0;
}

void	open_event_ui(SLONG ui_type)
{
	switch(ui_type)
	{
	case UI_TYPE_GAME_TALK:
		open_game_talk(TRUE);
		break;
	case UI_TYPE_GAME_CHOICE:
		open_game_choice(TRUE);
		break;
	case UI_TYPE_TRADE_SHOP:
		open_ui_shop(TRUE);
		break;
	case UI_TYPE_STORE_SHOP:
		open_ui_store(TRUE);
		break;
	}
	l_event_ui_control.current_ui = ui_type;
}


void    redraw_event_ui(void *vbitmap)
{
	switch(l_event_ui_control.current_ui)
	{
	case UI_TYPE_GAME_TALK:
		redraw_game_talk(vbitmap);
		break;
	case UI_TYPE_GAME_CHOICE:
		redraw_game_choice(vbitmap);
		break;
	case UI_TYPE_TRADE_SHOP:
		//PS: 本介面不是在遊戲畫面的最上層顯示, 所以, 重劃部分移至 redraw_map_ui() 中.
		//redraw_ui_shop(0, 0, vbitmap);
		break;
	case UI_TYPE_STORE_SHOP:
		//PS: 本介面不是在遊戲畫面的最上層顯示, 所以, 重劃部分移至 redraw_map_ui() 中.
		//redraw_ui_store(0, 0, vbitmap);
		break;
	default:
		break;
	}
}


/************************************************************************************************************/
/* YES/NO MESSAGE BOX CALLBACK FUNCTION                                                                     */
/************************************************************************************************************/
void	yes_no_message_box_callback(DWORD param, SLONG result)
{
	UIMB_PARAM *p;

	p = (UIMB_PARAM *)param;
	switch(p->event_id)
	{
		// --------------------------------------------------------------
		// 商店中買賣：詢問是否確定購買物品
		// --------------------------------------------------------------
	case ASK_BUY_ITEM_AT_ITEM_STORE:
		{
			switch(result) 
			{
			case MSG_BOX_ID_YES:
				SLONG	store_index, item_index;
				store_index = p->param1;
				item_index = p->param2;
				client_cmd_left_hit_item_store_item(store_index, item_index);
				break;
			case MSG_BOX_ID_NO:
				break;
			}
		}
		break;

		// --------------------------------------------------------------
		// 世界伺服器：詢問是否確定刪除人物
		// --------------------------------------------------------------
	case ASK_DEL_CHARACTER_AT_WORLD:
		{
			switch(result) 
			{
			case MSG_BOX_ID_YES:
				{
					int iRet;
					iRet = ClientRequestDeleteCharacter((char *)p->str);
					switch(iRet)
					{
					case SEND_MSG_OK:
						break;
					default:
						error_message_box(NULL, "DELETE CHARACTER FAILED");
						break;
					}
				}
				break;
			case MSG_BOX_ID_NO:
				break;
			}
		}
		break;
	}
}


void	error_message_box(char *title, char *text)
{
	UIMSGBOX	mb;

	memset(&mb, 0, sizeof(mb));
	mb.pfunc = NULL;
	mb.disp_time = 0;
	mb.font_size = TE_FONT_SIZE_12;
	mb.msgbox_type = UIMB_OK;
	if(title) strcpy(mb.title_info, title);
	if(text) strcpy(mb.text_info, text);
	msg_box(MB_CENTER_X, MB_CENTER_Y, &mb);
}


