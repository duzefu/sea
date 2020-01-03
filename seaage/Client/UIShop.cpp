/*
**  UIShop.cpp
**  Class UIShop functions.
**
**  WR, 2002.11.22.
*/
#include "MainFun.h"
#include "NetGE_MainFunc.h"
#include "Map.h"
#include "ClientMain.h"
#include "ErrorMsg.h"
#include "CRange.h"
#include "MouseHand.h"
#include "UIMap.h"
#include "UIShop.h"
#include "qqmsgbox.h"
#include "Client_Item.h"
#include "UIRebuildCabin.h"


/************************************************************************************************************/
/* GLOBALS                                                                                                  */
/************************************************************************************************************/
UI_SHOP_DATA ui_shop_data;


/************************************************************************************************************/
/* UI SHOP MAIN FUNCTIONS                                                                                   */
/************************************************************************************************************/
int		init_ui_shop()
{
	USTR    filename[_MAX_FNAME];
    SLONG   result, i, frames;
    CAKE_FRAME_ANI  *cfa = NULL;
    UI_SHOP_DATA *data = &ui_shop_data;

    //shop menu image -----------------
    data->cfa = NULL;
    for(i=0; i<32; i++)
    {
        data->cf[i] = NULL;
    }
    set_data_file(packed_menu_file);
    strcpy((char *)filename, "menu\\shop.cak");
    result = load_cake_frame_ani_from_file((USTR*)filename, &data->cfa);
    if(TTN_OK != result)
        return  -1;
    frames = count_cake_frames(data->cfa);
    for(i=0; i<frames; i++)
    {
        cfa = get_specify_cake_frame_ani(data->cfa, i);
        data->cf[i] = cfa->cake_frame;
    }

    //ship image -----------------------
    data->ship_cfa = NULL;
    for(i=0; i<32; i++)
        data->ship_cf[i] = NULL;
    set_data_file(packed_menu_file);
    strcpy((char *)filename, "menu\\shipbg.cak");
    result = load_cake_frame_ani_from_file((USTR*)filename, &data->ship_cfa);
    if(TTN_OK != result)
        return  -1;
    frames = count_cake_frames(data->ship_cfa);
    for(i=0; i<frames; i++)
    {
        cfa = get_specify_cake_frame_ani(data->ship_cfa, i);
        data->ship_cf[i] = cfa->cake_frame;
    }

	//cabin image -----------------------
    data->cabin_cfa = NULL;
    for(i=0; i<32; i++)
        data->cabin_cf[i] = NULL;
    set_data_file(packed_menu_file);
    strcpy((char *)filename, "menu\\cabin.cak");
    result = load_cake_frame_ani_from_file((USTR*)filename, &data->cabin_cfa);
    if(TTN_OK != result)
        return  -1;
    frames = count_cake_frames(data->cabin_cfa);
    for(i=0; i<frames; i++)
    {
        cfa = get_specify_cake_frame_ani(data->cabin_cfa, i);
        data->cabin_cf[i] = cfa->cake_frame;
    }

    // ------------------------------------
    data->hilight_id = 0;
    data->active_id = 0;
    //data->function_id = UIMAPSHIP_ID_INFORMATION;
    
	//
    data->ship_index = 0;
    data->is_opened = FALSE;

    return  0;
}

void free_ui_shop()
{
    UI_SHOP_DATA *data = &ui_shop_data;
    SLONG   i;

    if(data->cfa)
    {
        destroy_cake_frame_ani(&data->cfa);
        for(i=0; i<32; i++)
        {
            data->cf[i] = NULL;
        }
    }
    if(data->ship_cfa)
    {
        destroy_cake_frame_ani(&data->ship_cfa);
        for(i=0; i<32; i++)
        {
            data->ship_cf[i] = NULL;
        }
    }
	if(data->cabin_cfa)
    {
        destroy_cake_frame_ani(&data->cabin_cfa);
        for(i=0; i<32; i++)
        {
            data->cabin_cf[i] = NULL;
        }
    }
    return;
}


void redraw_ui_shop(SLONG sx, SLONG sy, void *vbitmap)
{
	UI_SHOP_DATA *data = &ui_shop_data;
    BMP *bitmap = (BMP*)vbitmap;
    CAKE_FRAME  *cf;
    SLONG   frame, x, y, id, event;

	if(!data->is_opened)
		return;

    if(g_lPlayerIndex < 0)
        return;
    event = UISHOP_EVENT;

    //(1) background -------------------------------------------
    frame = UISHOP_FRAME_BKGND;
    id = UISHOP_ID_BKGND;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

	//ship-------------------------------------------
    if(data->ship_index>=0)
	{
		cf = data->ship_cf[data->ship_index];
		x = sx + UISHOP_SHIP_SX + cf->frame_rx;
		y = sy + UISHOP_SHIP_SY + cf->frame_ry;
		put_rle(x, y, cf->rle, bitmap);
	}
	
	//(2) product bar browse button -------------------------------------------
    frame = UISHOP_FRAME_PRODUCT_LEFT;
    id = UISHOP_ID_PRODUCT_LEFT;
    if(data->active_id == id)
        frame += 1;
    else if(data->hilight_id == id)
        frame += 1;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

	frame = UISHOP_FRAME_PRODUCT_RIGHT;
    id = UISHOP_ID_PRODUCT_RIGHT;
    if(data->active_id == id)
        frame += 1;
    else if(data->hilight_id == id)
        frame += 1;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

	//(3) sell bar browse button -------------------------------------------
    frame = UISHOP_FRAME_SELL_LEFT;
    id = UISHOP_ID_SELL_LEFT;
    if(data->active_id == id)
        frame += 1;
    else if(data->hilight_id == id)
        frame += 1;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

	frame = UISHOP_FRAME_SELL_RIGHT;
    id = UISHOP_ID_SELL_RIGHT;
    if(data->active_id == id)
        frame += 1;
    else if(data->hilight_id == id)
        frame += 1;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

	//(4) sell all button -------------------------------------------
    frame = UISHOP_FRAME_SELL_ALL;
    id = UISHOP_ID_SELL_ALL;
    if(data->active_id == id)
        frame += 1;
    else if(data->hilight_id == id)
        frame += 1;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

	//(5) OK button -------------------------------------------
    frame = UISHOP_FRAME_OK;
    id = UISHOP_ID_OK;
    if(data->active_id == id)
        frame += 1;
    else if(data->hilight_id == id)
        frame += 1;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

	//(6) Cancel button -------------------------------------------
    frame = UISHOP_FRAME_CANCEL;
    id = UISHOP_ID_CANCEL;
    if(data->active_id == id)
        frame += 1;
    else if(data->hilight_id == id)
        frame += 1;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

	//(7) products -------------------------------------------
    for(int idx = 0; idx < 5; idx ++)
	{
		id = UISHOP_ID_PRODUCT_BAR_0_GOODS + idx;
		x = sx + UISHOP_PRODUCT_BAR_SX + idx * UISHOP_BAR_DY;
		y = sy + UISHOP_PRODUCT_BAR_SY;
		SLONG xl = ITEM_ICON_WIDTH;
		SLONG yl = ITEM_ICON_HEIGHT;
		game_range.add(x, y, xl, yl, event, id);
		
		/*
		if(! IsItemNone(&item))
		{
			cx = x + xl / 2;
			cy = y + yl / 2;
			icon_index = GetItemIconIndex(&item);
			redraw_item_icon_image(cx, cy, icon_index, bitmap);
		}
		*/
		
	}

	//(8) player sell goods -------------------------------------------
	for(idx = 0; idx < 5; idx ++)
	{
		id = UISHOP_ID_SELL_BAR_0_GOODS + idx;
		x = sx + UISHOP_SELL_BAR_SX + idx * UISHOP_BAR_DY;
		y = sy + UISHOP_SELL_BAR_SY;
		SLONG xl = ITEM_ICON_WIDTH;
		SLONG yl = ITEM_ICON_HEIGHT;
		game_range.add(x, y, xl, yl, event, id);
	}

	//(9) player cabin and goods -------------------------------------------
	int cabin_num = g_CabinNum[data->ship_index];
	for(idx = 0; idx < cabin_num; idx ++)
	{
		int cabin_type = g_CabinPos[data->ship_index][idx][2];
		cf = data->cabin_cf[cabin_type];
		x = sx + UISHOP_SHIP_SX + g_CabinPos[data->ship_index][idx][0] + cf->frame_rx;
		y = sy + UISHOP_SHIP_SY + g_CabinPos[data->ship_index][idx][1] + cf->frame_ry;
		put_rle(x, y, cf->rle, bitmap);

		if(cabin_type == 4)
		{
			SLONG xl = ITEM_ICON_WIDTH;
			SLONG yl = ITEM_ICON_HEIGHT;
			//id = UISHOP_ID_SELL_BAR_0_GOODS + idx;
			//game_range.add(x, y, xl, yl, event, id);
		}
	}
}


SLONG handle_ui_shop(UINT message, WPARAM wParam, LPARAM lParam)
{
    UI_SHOP_DATA *data = &ui_shop_data;
    static  SLONG   mouse_x, mouse_y;
    SLONG   event_type, event_id, result;

	if(!data->is_opened)
		return	1;

	result = 1;
    switch(message)
    {
    case WM_MOUSEMOVE:
        mouse_x = GET_X_LPARAM(lParam);
        mouse_y = GET_Y_LPARAM(lParam);
        event_type = event_id = 0;
        game_range.mapping(mouse_x, mouse_y, &event_type, &event_id);
		if(event_type == UISHOP_EVENT)
		{
			data->hilight_id = event_id;
			result = 0;
		}
        break;
    case WM_LBUTTONDOWN:
        {
            mouse_x = GET_X_LPARAM(lParam);
            mouse_y = GET_Y_LPARAM(lParam);
            event_type = event_id = 0;
            game_range.mapping(mouse_x, mouse_y, &event_type, &event_id);
			if(event_type == UISHOP_EVENT)
			{
				switch(event_id)
				{
				case UISHOP_ID_PRODUCT_LEFT:
					break;
				case UISHOP_ID_PRODUCT_RIGHT:
					break;
				case UISHOP_ID_SELL_LEFT:
					break;
				case UISHOP_ID_SELL_RIGHT:
					break;
				case UISHOP_ID_SELL_ALL:
					break;
				case UISHOP_ID_OK:
					break;
				case UISHOP_ID_CANCEL:
					break;
					/*
					default:
					data->active_id = event_id;
					if(event_id >= UIMAPSHIP_ID_BAG_0_ITEM && event_id < UIMAPSHIP_ID_BAG_0_ITEM + UIMAPSHIP_BAG_COUNTS)
					{
					index = event_id - UIMAPSHIP_ID_BAG_0_ITEM;
					client_cmd_left_hit_bag_item(index);
					}
					break;
					*/
				}
				result = 0;
			}
        }
        break;
    case WM_LBUTTONUP:
        data->active_id = 0;
        break;
    }
    return  result;
}



void open_ui_shop(SLONG flag)
{
	ui_shop_data.is_opened = flag ? TRUE : FALSE;
}

SLONG	is_ui_shop_open(void)
{
	return	ui_shop_data.is_opened ? TRUE : FALSE;
}


void	uishop_MsgCallback(ULONG event_id, SLONG result)
{
    //pUIShop->bActive=TRUE;
}


void	uishop_MsgBox(char* title,char* text)
{
    LPUIMSGBOX p;
    p = new_msgbox();

    p->msgbox_type = UIMB_OK;
    lstrcpy((LPTSTR)p->text_info, text);
    lstrcpy((LPTSTR)p->title_info, title);
    p->pfunc = uishop_MsgCallback;
    p->font_size = 16;
    msg_box(-1, -1, p);

    del_msgbox(p);
}



