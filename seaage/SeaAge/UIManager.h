/*
**	UIManager.h 
**	UI manager functions header.
**
**	Jack, 2003.1.21.
*/
#pragma once
#include "UIGameTalk.h"
#include "UIGameChoice.h"
#include "UIShop.h"
#include "UIStore.h"

//
// DEFINES //////////////////////////////////////////////////////////////////////////////////////////////////
//
#define	UI_TYPE_GAME_TALK			1	//對話
#define	UI_TYPE_GAME_CHOICE			2	//選擇
#define	UI_TYPE_TRADE_SHOP			3	//貿易介面
#define	UI_TYPE_STORE_SHOP			4	//商店介面



enum	MSGBOX_EVENT_ID
{
	ASK_BUY_ITEM_AT_ITEM_STORE		=	10,	//商店中買賣：詢問是否確定購買物品
	ASK_DEL_CHARACTER_AT_WORLD		=	20,	//世界伺服器：詢問是否確定刪除人物
};

//
// FUNCTIONS ////////////////////////////////////////////////////////////////////////////////////////////////
//
int		init_event_ui(void);
void	free_event_ui(void);
void	active_event_ui(int active);
//
void	close_last_event_ui(void);
void	open_event_ui(SLONG ui_type);
void    redraw_event_ui(void *vbitmap);
//
void	yes_no_message_box_callback(DWORD param, SLONG result);
void	error_message_box(char *title, char *text);



