/*
**	UIStore.cpp 
**	Store functions.
**
**	Stephen, 2003.2.16.
**	Jack, 2003.2.17.
**  ZZH for bank, 2003.4.10. ( Pay Day :)
*/
#include "MainFun.h"
#include "NetGE_MainFunc.h"
#include "ClientMain.h"
#include "CRange.h"
#include "ErrorMsg.h"
#include "Npc.h"
#include "HrtBeat.h"
#include "UI.h"
#include "PosData.h"
#include "Config.h"
#include "MapObject.h"
#include "SecretSkill.h"
#include "UIStore.h"
#include "CmdEvent.h"
#include "QQMsgBox.h"
#include "QQEdit.h"
#include "UIManager.h"
//
#include "Client_RecvMsg.h"
#include "Client_SendMsg.h"
#include "Client_Item.h"
#include "uiinput.h"

UISTORE_DATA			uistore_data;
ITEM_STORE_DATA			item_store_data;
BANK_STORE_DATA			bank_store_data;
SAVEBOX_STORE_DATA		savebox_store_data;
STRONGBOX_STORE_DATA	strongbox_store_data;

void bank_input_box_callback( LONG id, LONG result, LONG param );
/************************************************************************************************************/
/* 商店/儲藏                                                                                                */
/************************************************************************************************************/
int		init_ui_store(void)
{
	UISTORE_DATA	*data = &uistore_data;
    USTR    filename[_MAX_FNAME];
    SLONG   result, i, frames;
    CAKE_FRAME_ANI  *cfa;
	
	// Load ui image.
	data->cfa = NULL;
	
    strcpy((char *)filename, "menu\\uistore.cak");
    result = load_cake_frame_ani_from_file((USTR*)filename, &data->cfa);
    if(TTN_OK != result)
        return  -1;
	
    frames = count_cake_frames(data->cfa);
    for(i=0; i<frames; i++)
    {
        cfa = get_specify_cake_frame_ani(data->cfa, i);
        data->cf[i] = cfa->cake_frame;
    }
	
	// Initialize parameter
	data->store_type = ITEM_STORE;
	data->is_opened = FALSE;

	// Initialize datas.
	clear_item_store_data();
	clear_bank_store_data();
	clear_savebox_store_data();
	clear_strongbox_store_data();

    return 0;
}


void    free_ui_store(void)
{
	UISTORE_DATA	*data = &uistore_data;
	SLONG	i;

    if(data->cfa)
    {
        destroy_cake_frame_ani(&data->cfa);
		for(i=0; i<14; i++)
		{
			data->cf[i] = NULL;
		}
    }
	
}

void    active_ui_store(int active)
{
	// do nothing here.
}


void	set_ui_store_type(SLONG store_type)
{
	uistore_data.store_type = store_type;
}


void	open_ui_store(SLONG flag)
{
	UISTORE_DATA	*data = &uistore_data;

	switch(data->store_type)
	{
	case ITEM_STORE:
		open_item_store(flag);
		break;
	case BANK_STORE:
		open_bank_store(flag);
		break;
	case SAVEBOX_STORE:
		open_savebox_store(flag);
		break;
	case STRONGBOX_STORE:
		open_strongbox_store(flag);
		break;
	}
}


SLONG	is_ui_store_opened(void)
{
	UISTORE_DATA	*data = &uistore_data;

	switch(data->store_type)
	{
	case ITEM_STORE:
		return	is_item_store_opened();

	case BANK_STORE:
		return	is_bank_store_opened();

	case SAVEBOX_STORE:
		return	is_savebox_store_opened();

	case STRONGBOX_STORE:
		return	is_strongbox_store_opened();

	}
	return	FALSE;
}

void	refresh_ui_store(void)
{
	UISTORE_DATA	*data = &uistore_data;

	switch(data->store_type)
	{
	case ITEM_STORE:
		refresh_item_store();
		break;
	case BANK_STORE:
		refresh_bank_store();
		break;
	case SAVEBOX_STORE:
		refresh_savebox_store();
		break;
	case STRONGBOX_STORE:
		refresh_strongbox_store();
		break;
	}
}

SLONG   handle_ui_store(UINT message, WPARAM wParam, LPARAM lParam)
{
	UISTORE_DATA	*data = &uistore_data;

	switch(data->store_type)
	{
	case ITEM_STORE:
		return	handle_item_store(message, wParam, lParam);
	case BANK_STORE:
		return	handle_bank_store(message, wParam, lParam);
	case SAVEBOX_STORE:
		return	handle_savebox_store(message, wParam, lParam);
	case STRONGBOX_STORE:
		return	handle_strongbox_store(message, wParam, lParam);
	}

    return  0;
}


void    redraw_ui_store(SLONG sx, SLONG sy, void *vbitmap)
{
	UISTORE_DATA	*data = &uistore_data;

	switch(data->store_type)
	{
	case ITEM_STORE:
		redraw_item_store(sx, sy, vbitmap);
		break;
	case BANK_STORE:
		redraw_bank_store(sx, sy, vbitmap);
		break;
	case SAVEBOX_STORE:
		redraw_savebox_store(sx, sy, vbitmap);
		break;
	case STRONGBOX_STORE:
		redraw_strongbox_store(sx, sy, vbitmap);
		break;
	}
}


/************************************************************************************************************/
/* 道具商店                                                                                                 */
/************************************************************************************************************/
void	clear_item_store_data(void)
{
	SLONG	i;

	memset(&item_store_data, 0, sizeof(item_store_data));
	for(i=0; i<MAX_STORE_ITEMS; i++)
	{
		SetItemNone(&item_store_data.Item[i]);
	}
	item_store_data.NextProc = -1;
}

void	refresh_item_store(void)
{
}

void	redraw_item_store(SLONG sx, SLONG sy, void *vbitmap)
{
	enum
	{	
		BAG_DX		=	34,
		BAG_DY		=	34,
	};
	UISTORE_DATA*	uidata = &uistore_data;
    BMP *bitmap = (BMP*)vbitmap;
	SLONG x, y, cx, cy, xl, yl;
	SLONG i, j, icon_index, item_index, ammount;
	CAKE_FRAME *cf;
	TPOS_ITEM item;
	USTR	info[32];
	SLONG	frame, event, id;

	if(! uidata->is_opened)
		return;
	event = ITEMSTORE_EVENT;

	//(1) background ---------------------------------------------------------
	frame = UISTORE_FRAME_BKGND;
	id = ITEMSTORE_ID_BKGND;
	cf = uidata->cf[frame];
	x = sx + cf->frame_rx;
	y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

	//(2) title --------------------------------------------------------------
	frame = UISTORE_FRAME_STORE_MARK;
	cf = uidata->cf[frame];
	x = sx + cf->frame_rx;
	y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);

	//(3) close button -------------------------------------------------------
    frame = UISTORE_FRAME_CLOSE;
    id = ITEMSTORE_ID_CLOSE;
    if(uidata->active_id == id)
        frame += 1;
    else if(uidata->hilight_id == id)
        frame += 1;
    cf = uidata->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

	//(4) store items --------------------------------------------------------
	x = sx + UISTORE_SHOP_0_SX;
	y = sy + UISTORE_SHOP_0_SY;
	xl = (9-1) * BAG_DX + ITEM_ICON_WIDTH;
	yl = (4-1) * BAG_DY + ITEM_ICON_HEIGHT;
	game_range.add(x, y, xl, yl, event, ITEMSTORE_ID_SHOP_SHELF);
	
	for(j=0; j<4; j++)
	{
		for(i=0; i<9; i++)
		{
			item_index = j * 9 + i;
			item = item_store_data.Item[item_index];
			ammount = item_store_data.Amount[item_index];
			x = sx + UISTORE_SHOP_0_SX + i * BAG_DX;
			y = sy + UISTORE_SHOP_0_SY + j * BAG_DY;
			id = ITEMSTORE_ID_SHOP_0_ITEM + item_index;
			game_range.add(x, y, ITEM_ICON_WIDTH, ITEM_ICON_HEIGHT, event, id);

			if(!IsItemNone(&item))
			{
				icon_index = GetItemIconIndex(&item);
				cx = x + ITEM_ICON_WIDTH/2;
				cy = y + ITEM_ICON_HEIGHT/2;
                redraw_item_icon_image(cx, cy, icon_index, bitmap);
				sprintf((char *)info, "%d", item_store_data.Amount[item_index]);
				print12(x, y, info, PEST_PUT, bitmap);
			}
		}
	}

	//(5) my bag items -------------------------------------------------------
	id = ITEMSTORE_ID_BAG_0_ITEM;
	redraw_my_bag_items(sx + UISTORE_BAG_0_SX, sy + UISTORE_BAG_0_SY, event, id, bitmap);
}


void	redraw_item_store_mouse_point_info(SLONG id, void *vbitmap)
{
	SLONG		event = ITEMSTORE_EVENT;
	SLONG		index, item_sx, item_sy;
	TPOS_ITEM	item;

	switch(id)
	{
	case ITEMSTORE_ID_CLOSE:
        redraw_event_info_bar(event, id, (USTR*)TEXTMSG_MENU_CLOSE, (USTR*)TEXTMSG_MENU_CLOSE_INFO, vbitmap);
		break;
	default:
        if(id >= ITEMSTORE_ID_BAG_0_ITEM && id < ITEMSTORE_ID_BAG_0_ITEM + 27)
        {
            index = id - ITEMSTORE_ID_BAG_0_ITEM;

            LOCK_CHARACTER(g_lPlayerIndex);
			GetCharacterBagItem(g_lPlayerIndex, index, &item);
            UNLOCK_CHARACTER(g_lPlayerIndex);

            if(! IsItemNone(&item))
            {
                item_sx = UISTORE_BAG_0_SX + (index % 9) * UISTORE_ITEM_DX;
                item_sy = UISTORE_BAG_0_SY + (index / 9) * UISTORE_ITEM_DY;
                redraw_icon_item_information(item_sx, item_sy, ITEM_INFO_SELL, &item, (BMP*)vbitmap);
            }
        }
		else if(id >= ITEMSTORE_ID_SHOP_0_ITEM && id < ITEMSTORE_ID_SHOP_0_ITEM + 36)
		{
			index = id - ITEMSTORE_ID_SHOP_0_ITEM;
			item = item_store_data.Item[index];
            if(! IsItemNone(&item))
            {
                item_sx = UISTORE_SHOP_0_SX + (index % 9) * UISTORE_ITEM_DX;
                item_sy = UISTORE_SHOP_0_SY + (index / 9) * UISTORE_ITEM_DY;
                redraw_icon_item_information(item_sx, item_sy, ITEM_INFO_BUY, &item, (BMP*)vbitmap);
            }
		}
		break;
	}
}

SLONG	handle_item_store(UINT message, WPARAM wParam, LPARAM lParam)
{
    SLONG   mouse_x, mouse_y, map_x, map_y;
    SLONG   event_type, event_id;
	SLONG	result, index;
	SLONG	npc_no, proc_no;
	TPOS_ITEM	item;

	if(! uistore_data.is_opened)
		return	1;

	result = 1;
	switch(message)
	{
	case WM_MOUSEMOVE:
		mouse_x = GET_X_LPARAM(lParam);
		mouse_y = GET_Y_LPARAM(lParam);
		event_type = event_id = 0;
		game_range.mapping(mouse_x, mouse_y, &event_type, &event_id);
		if(event_type == ITEMSTORE_EVENT)
		{
			uistore_data.hilight_id = event_id;
			map_x = map_data.map_sx + mouse_x;
			map_y = map_data.map_sy + mouse_y;
			set_mouse_hand_position(mouse_x, mouse_y);
			set_mouse_hand_point_position(map_x, map_y);
			set_mouse_hand_point_info(event_type, event_id, map_x, map_y);
			result = 0;
		}
		break;

	case WM_LBUTTONDOWN:
		mouse_x = GET_X_LPARAM(lParam);
		mouse_y = GET_Y_LPARAM(lParam);
		event_type = event_id = 0;
		game_range.mapping(mouse_x, mouse_y, &event_type, &event_id);
		if(event_type == ITEMSTORE_EVENT)
		{
			switch(event_id)
			{
			case ITEMSTORE_ID_CLOSE:
				npc_no = item_store_data.OfferNpc;
				proc_no = item_store_data.NextProc;
				client_cmd_request_npc_proc(npc_no, proc_no);
				break;

			case ITEMSTORE_ID_SHOP_SHELF:
				LOCK_CHARACTER(0);
				GetCharacterOnMouseItem(g_lPlayerIndex, &item);
				UNLOCK_CHARACTER(0);
				if(!IsItemNone(&item))
				{
					client_cmd_request_sell_item(item_store_data.StoreIndex);
				}
				break;
			default:
				if(event_id >= ITEMSTORE_ID_BAG_0_ITEM && event_id < ITEMSTORE_ID_BAG_0_ITEM + 27)
				{
					index = event_id - ITEMSTORE_ID_BAG_0_ITEM;
                    client_cmd_left_hit_bag_item(index);
				}
				else if(event_id >= ITEMSTORE_ID_SHOP_0_ITEM && event_id < ITEMSTORE_ID_SHOP_0_ITEM + 36)
				{
					LOCK_CHARACTER(0);
					GetCharacterOnMouseItem(g_lPlayerIndex, &item);
					UNLOCK_CHARACTER(0);
					if(!IsItemNone(&item))
					{
						client_cmd_request_sell_item(item_store_data.StoreIndex);
					}
					else
					{
						UIMSGBOX	mb;
						char		text[80];
						
						index = event_id - ITEMSTORE_ID_SHOP_0_ITEM;
						memset(&mb, 0, sizeof(mb));
						mb.pfunc = yes_no_message_box_callback;
						mb.disp_time = 0;
						mb.font_size = TE_FONT_SIZE_12;
						mb.msgbox_type = UIMB_YESNO | UIMB_OWN_MOUSE;
						sprintf((char *)text, TEXTMSG_ASK_BUY_ITEM, GetItemName(&item_store_data.Item[index]), item_store_data.Money[index]);
						strcpy(mb.title_info, "");
						strcpy(mb.text_info, (const char *)text);
						
						mb.param.event_id = ASK_BUY_ITEM_AT_ITEM_STORE;
						mb.param.param1 = item_store_data.StoreIndex;
						mb.param.param2 = index;
						msg_box(MB_CENTER_X, MB_CENTER_Y, &mb);
						//client_cmd_left_hit_item_store_item(item_store_data.StoreIndex, index);
					}
				}
				break;
			}
			result = 0;
		}
		break;

	case WM_RBUTTONDOWN:
		mouse_x = GET_X_LPARAM(lParam);
		mouse_y = GET_Y_LPARAM(lParam);
		event_type = event_id = 0;
		game_range.mapping(mouse_x, mouse_y, &event_type, &event_id);
		if(event_type == ITEMSTORE_EVENT)
		{
			result = 0;
		}
		break;
	}

	return	result;
}

void	open_item_store(SLONG flag)
{
	uistore_data.store_type = ITEM_STORE;
	uistore_data.is_opened = flag ? TRUE : FALSE;
}

SLONG	is_item_store_opened(void)
{
	return	uistore_data.is_opened ? TRUE : FALSE;
}


/************************************************************************************************************/
/* 銀行 (ZZH)                                                                                               */
/************************************************************************************************************/
void	clear_bank_store_data(void)
{
	SLONG i;
	TPOS_ITEM Item;

	memset( &bank_store_data, 0, sizeof( bank_store_data ) );
	bank_store_data.ShowInput = FALSE;

	SetItemNone( &Item );

	for ( i = 0; i < MAX_CHARACTER_BANK_ITEMS; i++ )
	{
		LOCK_CHARACTER( g_lPlayerIndex );
		SetCharacterBankItem( g_lPlayerIndex, i, &Item );
		UNLOCK_CHARACTER( g_lPlayerIndex );
	}

	LOCK_CHARACTER( g_lPlayerIndex );
	SetCharacterBankMoney( g_lPlayerIndex, 0 );
	UNLOCK_CHARACTER( g_lPlayerIndex );
}

void	refresh_bank_store(void)
{
}

SLONG	handle_bank_store(UINT message, WPARAM wParam, LPARAM lParam)
{
    SLONG   mouse_x, mouse_y, map_x, map_y;
    SLONG   event_type, event_id;
	SLONG	result, index;
	SLONG	npc_no, proc_no;
	ULONG	money;
	TPOS_ITEM	item;
	UI_INPUT input;

	if(! uistore_data.is_opened)
		return	1;

	if ( bank_store_data.ShowInput )
		return handle_ui_input( message, wParam, lParam );		

	result = 1;
	switch(message)
	{
	case WM_MOUSEMOVE:
		mouse_x = GET_X_LPARAM(lParam);
		mouse_y = GET_Y_LPARAM(lParam);
		event_type = event_id = 0;
		game_range.mapping(mouse_x, mouse_y, &event_type, &event_id);
		if(event_type == BANKSTORE_EVENT)
		{
			uistore_data.hilight_id = event_id;
			map_x = map_data.map_sx + mouse_x;
			map_y = map_data.map_sy + mouse_y;
			set_mouse_hand_position(mouse_x, mouse_y);
			set_mouse_hand_point_position(map_x, map_y);
			set_mouse_hand_point_info(event_type, event_id, map_x, map_y);
			result = 0;
		}
		break;

	case WM_LBUTTONDOWN:
		mouse_x = GET_X_LPARAM(lParam);
		mouse_y = GET_Y_LPARAM(lParam);
		event_type = event_id = 0;
		game_range.mapping(mouse_x, mouse_y, &event_type, &event_id);
        if ( event_type == RT_MAP )
        {
            event_type = BANKSTORE_EVENT;
            event_id = ITEMSTORE_ID_CLOSE;
        }
		if ( event_type == BANKSTORE_EVENT )
		{
			switch ( event_id )
			{
			case ITEMSTORE_ID_CLOSE:
				// 發給服務器下一步的事件編號
				npc_no = bank_store_data.OfferNpc;
				proc_no = bank_store_data.NextProc;
				client_cmd_request_npc_proc(npc_no, proc_no);
				break;
			case ITEMSTORE_ID_SHOP_SHELF:
				LOCK_CHARACTER(0);
				GetCharacterOnMouseItem(g_lPlayerIndex, &item);
				UNLOCK_CHARACTER(0);
				if(!IsItemNone(&item))
				{
					//client_cmd_request_sell_item(item_store_data.StoreIndex);
					// 從銀行獲得物品
				}
				break;
			case BANKSTORE_ID_SAVE:
				LOCK_CHARACTER( g_lPlayerIndex );
				money = GetCharacterBodyMoney( g_lPlayerIndex );
				UNLOCK_CHARACTER( g_lPlayerIndex );
				input.x = BANKSTORE_INPUT_BOX_X;
				input.y = BANKSTORE_INPUT_BOX_Y;
				input.max = money;
				input.min = 0;
				input.font_size = 16;
				input.pfunc = bank_input_box_callback;
				strcpy( input.title, TEXTMSG_BANK_LOAD_MONEY);
				ui_input_show( &input, BANKSTORE_SAVE_MONEY );
				bank_store_data.ShowInput = TRUE;
				break;
			case BANKSTORE_ID_LOAD:
				LOCK_CHARACTER( g_lPlayerIndex );
				money = GetCharacterBankMoney( g_lPlayerIndex );
				UNLOCK_CHARACTER( g_lPlayerIndex );
				input.x = BANKSTORE_INPUT_BOX_X;
				input.y = BANKSTORE_INPUT_BOX_Y;
				input.max = money;
				input.min = 0;
				input.font_size = 16;
				input.pfunc = bank_input_box_callback;
				strcpy( input.title, TEXTMSG_BANK_SAVE_MONEY);
				ui_input_show( &input, BANKSTORE_LOAD_MONEY );
				bank_store_data.ShowInput = TRUE;
				break;
			default:
				if(event_id >= ITEMSTORE_ID_BAG_0_ITEM && event_id < ITEMSTORE_ID_BAG_0_ITEM + 27)
				{
					index = event_id - ITEMSTORE_ID_BAG_0_ITEM;
                    client_cmd_left_hit_bag_item(index);
				}
				else if(event_id >= ITEMSTORE_ID_SHOP_0_ITEM && event_id < ITEMSTORE_ID_SHOP_0_ITEM + 36)
				{
					index = event_id - ITEMSTORE_ID_SHOP_0_ITEM;
					client_cmd_hit_bank_item( (UHINT)index );
				}
				break;
			}
			result = 0;
		}
		break;

	case WM_RBUTTONDOWN:
		mouse_x = GET_X_LPARAM(lParam);
		mouse_y = GET_Y_LPARAM(lParam);
		event_type = event_id = 0;
		game_range.mapping(mouse_x, mouse_y, &event_type, &event_id);
		if(event_type == ITEMSTORE_EVENT)
		{
			result = 0;
		}
		break;
	}

	return	result;
}

void	redraw_bank_store(SLONG sx, SLONG sy, void *vbitmap)
{
	enum
	{	
		BAG_DX		=	34,
		BAG_DY		=	34,
	};
	UISTORE_DATA*	uidata = &uistore_data;
    BMP *bitmap = (BMP*)vbitmap;
	SLONG x, y, cx, cy, xl, yl;
	SLONG i, j, icon_index, item_index;
	CAKE_FRAME *cf;
	TPOS_ITEM item;
	USTR	info[32];
	SLONG	frame, event, id;
	ULONG	money;

	if(! uidata->is_opened)
		return;
	event = BANKSTORE_EVENT;

    //(1) background ---------------------------------------------------------
	frame = UISTORE_FRAME_BKGND;
	id = ITEMSTORE_ID_BKGND;
	cf = uidata->cf[frame];
	x = sx + cf->frame_rx;
	y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
	if ( !bank_store_data.ShowInput )
		game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

	//(2) close button -------------------------------------------------------
    frame = UISTORE_FRAME_CLOSE;
    id = ITEMSTORE_ID_CLOSE;
    if(uidata->active_id == id)
        frame += 1;
    else if(uidata->hilight_id == id)
        frame += 1;
    cf = uidata->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
	game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

	//(3) title --------------------------------------------------------------
	frame = UISTORE_FRAME_BANK_MARK;
	cf = uidata->cf[frame];
	x = sx + cf->frame_rx;
	y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);


	//(4) bank items --------------------------------------------------------
	x = sx + UISTORE_SHOP_0_SX;
	y = sy + UISTORE_SHOP_0_SY;
	xl = (9-1) * BAG_DX + ITEM_ICON_WIDTH;
	yl = (4-1) * BAG_DY + ITEM_ICON_HEIGHT;
	if ( !bank_store_data.ShowInput )
		game_range.add(x, y, xl, yl, event, ITEMSTORE_ID_SHOP_SHELF);
	
	for(j=0; j<4; j++)
	{
		for(i=0; i<9; i++)
		{
			item_index = j * 9 + i;
			LOCK_CHARACTER( g_lPlayerIndex );
			GetCharacterBankItem( g_lPlayerIndex, item_index, &item );
			LOCK_CHARACTER( g_lPlayerIndex );
			x = sx + UISTORE_SHOP_0_SX + i * BAG_DX;
			y = sy + UISTORE_SHOP_0_SY + j * BAG_DY;
			id = ITEMSTORE_ID_SHOP_0_ITEM + item_index;
			if ( !bank_store_data.ShowInput )
				game_range.add(x, y, ITEM_ICON_WIDTH, ITEM_ICON_HEIGHT, event, id);

			if(!IsItemNone(&item))
			{
				icon_index = GetItemIconIndex(&item);
				cx = x + ITEM_ICON_WIDTH/2;
				cy = y + ITEM_ICON_HEIGHT/2;
                redraw_item_icon_image(cx, cy, icon_index, bitmap);
				//sprintf((char *)info, "%d", item_store_data.Amount[item_index]);
				//print12(x, y, info, PEST_PUT, bitmap);
			}
		}
	}

	//(5) my bag items -------------------------------------------------------
	id = ITEMSTORE_ID_BAG_0_ITEM;
	redraw_my_bag_items(sx + UISTORE_BAG_0_SX, sy + UISTORE_BAG_0_SY, event, id, bitmap);	

	//(6) money --------------------------------------------------------------
	id = BANKSTORE_ID_MONEY;
	frame = UISTORE_FRAME_GOLD_BKGND;
	cf = uidata->cf[frame];
	x = sx + cf->frame_rx;
	y = sy + cf->frame_ry;
	if ( !bank_store_data.ShowInput )
		put_rle(x, y, cf->rle, bitmap);

	LOCK_CHARACTER( g_lPlayerIndex );
	money = GetCharacterBankMoney( g_lPlayerIndex );
	UNLOCK_CHARACTER( g_lPlayerIndex );
	sprintf( (CHAR*)info, "%d", money );
	print12( BANKSTORE_MONEY_SX + sx, BANKSTORE_MONEY_SY + sy, info, PEST_PUT, bitmap );
	
	//(7) load/save button ---------------------------------------------------
	id = BANKSTORE_ID_LOAD;
	frame = UISTORE_FRAME_LOAD;
	if ( uidata->active_id == id )
		frame += 4;
	else if ( uidata->hilight_id == id )
		frame += 2;
	cf = uidata->cf[frame];
	x = sx + cf->frame_rx;
	y = sy + cf->frame_ry;

	if ( money == 0 )
	{
		gray_put_rle( x, y, cf->rle, bitmap );
	}
	else
	{
		put_rle( x, y, cf->rle, bitmap );
		if ( !bank_store_data.ShowInput )
			game_range.add( x, y, cf->rle->w, cf->rle->h, event, id );
	}
	

	id = BANKSTORE_ID_SAVE;
	frame = UISTORE_FRAME_SAVE;
	if ( uidata->active_id == id )
		frame += 4;
	else if ( uidata->hilight_id == id )
		frame += 2;
	cf = uidata->cf[frame];
	x = sx + cf->frame_rx;
	y = sy + cf->frame_ry;
	LOCK_CHARACTER( g_lPlayerIndex );
	money = GetCharacterBodyMoney( g_lPlayerIndex );
	UNLOCK_CHARACTER( g_lPlayerIndex );

	if ( money == 0 )
	{
		gray_put_rle( x, y, cf->rle, bitmap );
	}
	else
	{
		put_rle( x, y, cf->rle, bitmap );
		if ( !bank_store_data.ShowInput )
			game_range.add( x, y, cf->rle->w, cf->rle->h, event, id );
	}


	if ( bank_store_data.ShowInput )
		redraw_ui_input( bitmap );

}

void	redraw_bank_store_mouse_point_info(SLONG id, void *vbitmap)
{
	SLONG		event = ITEMSTORE_EVENT;
	SLONG		index, item_sx, item_sy;
	TPOS_ITEM	item;

	switch(id)
	{
	case ITEMSTORE_ID_CLOSE:
        redraw_event_info_bar(event, id, (USTR*)TEXTMSG_MENU_CLOSE, (USTR*)TEXTMSG_MENU_CLOSE_INFO, vbitmap);
		break;
	default:
        if(id >= ITEMSTORE_ID_BAG_0_ITEM && id < ITEMSTORE_ID_BAG_0_ITEM + 27)
        {
            index = id - ITEMSTORE_ID_BAG_0_ITEM;

            LOCK_CHARACTER(g_lPlayerIndex);
			GetCharacterBagItem(g_lPlayerIndex, index, &item);
            UNLOCK_CHARACTER(g_lPlayerIndex);

            if(! IsItemNone(&item))
            {
                item_sx = UISTORE_BAG_0_SX + (index % 9) * UISTORE_ITEM_DX;
                item_sy = UISTORE_BAG_0_SY + (index / 9) * UISTORE_ITEM_DY;
                redraw_icon_item_information(item_sx, item_sy, ITEM_INFO_NORMAL, &item, (BMP*)vbitmap);
            }
        }
		else if(id >= ITEMSTORE_ID_SHOP_0_ITEM && id < ITEMSTORE_ID_SHOP_0_ITEM + 36)
		{
			index = id - ITEMSTORE_ID_SHOP_0_ITEM;
			LOCK_CHARACTER( g_lPlayerIndex );
			GetCharacterBankItem( g_lPlayerIndex, index, &item );
			UNLOCK_CHARACTER( g_lPlayerIndex );
            if(! IsItemNone(&item))
            {
                item_sx = UISTORE_SHOP_0_SX + (index % 9) * UISTORE_ITEM_DX;
                item_sy = UISTORE_SHOP_0_SY + (index / 9) * UISTORE_ITEM_DY;
                redraw_icon_item_information(item_sx, item_sy, ITEM_INFO_NORMAL, &item, (BMP*)vbitmap);
            }
		}
		break;
	}
}

void	open_bank_store(SLONG flag)
{
	uistore_data.store_type = BANK_STORE;
	uistore_data.is_opened = flag ? TRUE : FALSE;
}

SLONG	is_bank_store_opened(void)
{
	return	uistore_data.is_opened ? TRUE : FALSE;
}

VOID	bank_money_not_enough( VOID )
{
	// 顯示對話框, 通知玩家銀行中的錢不夠
}

VOID	bank_no_item_room( VOID )
{
	// 顯示對話框, 通知玩家銀行中物品空位不夠
}

/************************************************************************************************************/
/* 儲物箱                                                                                                   */
/************************************************************************************************************/
void	clear_savebox_store_data(void)
{
}

void	refresh_savebox_store(void)
{
}

SLONG	handle_savebox_store(UINT message, WPARAM wParam, LPARAM lParam)
{
	return	0;
}

void	redraw_savebox_store(SLONG sx, SLONG sy, void *vbitmap)
{
}

void	redraw_savebox_store_mouse_point_info(SLONG id, void *vbitmap)
{
}

void	open_savebox_store(SLONG flag)
{
}

SLONG	is_savebox_store_opened(void)
{
	return	FALSE;
}

/************************************************************************************************************/
/* 保險箱                                                                                                   */
/************************************************************************************************************/
void	clear_strongbox_store_data(void)
{
}

void	refresh_strongbox_store(void)
{
}

SLONG	handle_strongbox_store(UINT message, WPARAM wParam, LPARAM lParam)
{
	return	0;
}

void	redraw_strongbox_store(SLONG sx, SLONG sy, void *vbitmap)
{
}

void	redraw_strongbox_store_mouse_point_info(SLONG id, void *vbitmap)
{
}

void	open_strongbox_store(SLONG flag)
{
}

SLONG	is_strongbox_store_opened(void)
{
	return	TRUE;
}



/************************************************************************************************************/
/* MISC                                                                                                     */
/************************************************************************************************************/
void	redraw_my_bag_items(SLONG sx, SLONG sy, SLONG event, SLONG id, BMP *bitmap)
{
	enum
	{
		BAG_X_COUNT =	9,
		BAG_Y_COUNT	=	3,
		BAG_DX		=	34,
		BAG_DY		=	34,
	};
	TPOS_ITEM	item;
	SLONG	ix, iy, idx, x, y, xl, yl, cx, cy;
	SLONG	icon_index;
	SLONG	event_id;

    for(iy = 0; iy < BAG_Y_COUNT; iy ++)
    {
        for(ix = 0; ix < BAG_X_COUNT; ix ++)
        {
            idx = iy * BAG_X_COUNT + ix;
            event_id = id + idx;
            x = sx + ix * BAG_DX;
            y = sy + iy * BAG_DY;
            xl = ITEM_ICON_WIDTH;
            yl = ITEM_ICON_HEIGHT;
			if ( !bank_store_data.ShowInput )
			    game_range.add(x, y, xl, yl, event, event_id);

			GetCharacterBagItem(g_lPlayerIndex, idx, &item);
			if(! IsItemNone(&item))
            {
                cx = x + xl / 2;
                cy = y + yl / 2;
                icon_index = GetItemIconIndex(&item);
                redraw_item_icon_image(cx, cy, icon_index, bitmap);
            }
        }
    }
}



//////////////////////////////////////////////////////////////////////////
void bank_input_box_callback( LONG id, LONG result, LONG param )
{
	switch ( param )
	{
	case BANKSTORE_SAVE_MONEY:
		if ( id == INPUT_OK_ID )
		{
			// 存錢
			client_cmd_request_bank_save_money( result );
		}

		bank_store_data.ShowInput = FALSE;
		break;
	case BANKSTORE_LOAD_MONEY:
		if ( id == INPUT_OK_ID )
		{
			// 取錢
			client_cmd_request_bank_load_money( result );
		}
		bank_store_data.ShowInput = FALSE;
		break;
	}
}