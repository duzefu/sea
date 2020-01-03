/*
**	UIMapShip.cpp
**	UI of map ship.
**
**	Jack, 2002/07/03.
*/
#include "MainFun.h"
#include "NetGE_MainFunc.h"
#include "Map.h"
#include "UIMapShip.h"
#include "CRange.h"
#include "MouseHand.h"
#include "UIMap.h"
#include "ClientMain.h"
#include "ErrorMsg.h"
#include "CmdEvent.h"
//
#include "Client_Item.h"


UI_MAPSHIP_DATA ui_mapship_data;

/******************************************************************************************************************/
/* UI MAP SHIP FUNCTIONS                                                                                          */
/******************************************************************************************************************/
int     init_ui_mapship(void)
{
    USTR    filename[_MAX_FNAME];
    SLONG   result, i, frames;
    CAKE_FRAME_ANI  *cfa = NULL;
    UI_MAPSHIP_DATA *data = &ui_mapship_data;

    //map ship menu image -----------------
    data->cfa = NULL;
    for(i=0; i<32; i++)
    {
        data->cf[i] = NULL;
    }
    set_data_file(packed_menu_file);
    strcpy((char *)filename, "menu\\uiship.cak");
    result = load_cake_frame_ani_from_file((USTR*)filename, &data->cfa);
    if(TTN_OK != result)
        return  -1;
    frames = count_cake_frames(data->cfa);
    for(i=0; i<frames; i++)
    {
        cfa = get_specify_cake_frame_ani(data->cfa, i);
        data->cf[i] = cfa->cake_frame;
    }

    //map ship image -----------------------
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

    // ------------------------------------
    data->hilight_id = 0;
    data->active_id = 0;
    data->function_id = UIMAPSHIP_ID_INFORMATION;
    data->function_dock = 0;
    //
    data->ship_index = 0;
    //
    data->is_opened = FALSE;

    return  0;
}


void    active_ui_mapship(int active)
{
}


void    free_ui_mapship(void)
{
    UI_MAPSHIP_DATA *data = &ui_mapship_data;
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
    return;
}



void    redraw_ui_mapship(SLONG sx, SLONG sy, void *vbitmap)
{
    UI_MAPSHIP_DATA *data = &ui_mapship_data;
    BMP *bitmap = (BMP*)vbitmap;
    CAKE_FRAME  *cf;
    SLONG   frame, x, y, id, event;

    if(g_lPlayerIndex < 0)
        return;
    event = UIMAPSHIP_EVENT;

    //(1) background -------------------------------------------
    frame = UIMAPSHIP_FRAME_BKGND;
    id = UIMAPSHIP_ID_BKGND;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

    //(2) close button -----------------------------------------
    frame = UIMAPSHIP_FRAME_CLOSE;
    id = UIMAPSHIP_ID_CLOSE;
    if(data->active_id == id)
        frame += 1;
    else if(data->hilight_id == id)
        frame += 1;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

    //(3) command button(information or equip) ------------------
    if(data->function_id == UIMAPSHIP_ID_INFORMATION)
    {
        frame = UIMAPSHIP_FRAME_EQUIP;
        id = UIMAPSHIP_ID_EQUIP;
        if(data->active_id == id)
            frame += 1;
        else if(data->hilight_id == id)
            frame += 2;
        cf = data->cf[frame];
        x = sx + cf->frame_rx;
        y = sy + cf->frame_ry;
        put_rle(x, y, cf->rle, bitmap);
        game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);
    }
    else if(data->function_id == UIMAPSHIP_ID_EQUIP)
    {
        frame = UIMAPSHIP_FRAME_INFORMATION;
        id = UIMAPSHIP_ID_INFORMATION;
        if(data->active_id == id)
            frame += 1;
        else if(data->hilight_id == id)
            frame += 2;
        cf = data->cf[frame];
        x = sx + cf->frame_rx;
        y = sy + cf->frame_ry;
        put_rle(x, y, cf->rle, bitmap);
        game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);
    }

    //(4) dock button ---------------------------------------------
    frame = UIMAPSHIP_FRAME_DOCK;
    id = UIMAPSHIP_ID_DOCK;
    if(data->active_id == id)
        frame += 1;
    else if(data->hilight_id == id)
        frame += 2;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

    //(5) ship background & datas ---------------------------------
    if(data->ship_index >= 0)
    {
        //ship background -----------------------
        frame = data->ship_index;
        cf = data->ship_cf[frame];
        x = sx + 28 + cf->frame_rx;
        y = sy + 146 + cf->frame_ry;
        put_rle(x, y, cf->rle, bitmap);

        //ship items ----------------------------
        // todo: [16:30,9/17/2002]
    }

    //(6) list informations ----------------------------------------
    if(data->function_id == UIMAPSHIP_ID_INFORMATION)
    {
    }
    else if(data->function_id == UIMAPSHIP_ID_EQUIP)
    {
        SLONG   ix, iy, idx, icon_index, xl, yl, cx, cy;
		TPOS_ITEM	item;

        //equip background ------------------------
        frame = UIMAPSHIP_FRAME_EQUIP_BKGND;
        cf = data->cf[frame];
        x = sx + cf->frame_rx;
        y = sy + cf->frame_ry;
        put_rle(x, y, cf->rle, bitmap);

        //equip items -----------------------------
        for(iy = 0; iy < UIMAPSHIP_BAG_Y_COUNT; iy ++)
        {
            for(ix = 0; ix < UIMAPSHIP_BAG_X_COUNT; ix ++)
            {
                idx = iy * UIMAPSHIP_BAG_X_COUNT + ix;
                id = UIMAPSHIP_ID_BAG_0_ITEM + idx;
                x = sx + UIMAPSHIP_BAG_0_SX + ix * UIMAPSHIP_BAG_DX;
                y = sy + UIMAPSHIP_BAG_0_SY + iy * UIMAPSHIP_BAG_DY;
                xl = ITEM_ICON_WIDTH;
                yl = ITEM_ICON_HEIGHT;
                game_range.add(x, y, xl, yl, event, id);
                
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

    //(7) dock informations ----------------------------------------
    if(data->function_dock == UIMAPSHIP_ID_DOCK)
    {
        // todo: [16:33,9/17/2002]
    }
}


void    refresh_ui_mapship(void)
{
}


SLONG   handle_ui_mapship(UINT message, WPARAM wParam, LPARAM lParam)
{
    UI_MAPSHIP_DATA *data = &ui_mapship_data;
    static  SLONG   mouse_x, mouse_y;
    SLONG   event_type, event_id, index;

    switch(message)
    {
    case WM_MOUSEMOVE:
        mouse_x = GET_X_LPARAM(lParam);
        mouse_y = GET_Y_LPARAM(lParam);
        event_type = event_id = 0;
        game_range.mapping(mouse_x, mouse_y, &event_type, &event_id);
        data->hilight_id = event_id;
        break;
    case WM_LBUTTONDOWN:
        {
            mouse_x = GET_X_LPARAM(lParam);
            mouse_y = GET_Y_LPARAM(lParam);
            event_type = event_id = 0;
            game_range.mapping(mouse_x, mouse_y, &event_type, &event_id);
            switch(event_id)
            {
            case UIMAPSHIP_ID_CLOSE:
                data->active_id = event_id;
                close_map_submenu(SUBMENU_SHIP);
                break;
            case UIMAPSHIP_ID_EQUIP:
                data->active_id = event_id;
                data->function_id = UIMAPSHIP_ID_EQUIP;
                //data->function_dock = 0;
                break;
            case UIMAPSHIP_ID_INFORMATION:
                data->active_id = event_id;
                data->function_id = UIMAPSHIP_ID_INFORMATION;
                //data->function_dock = 0;
                break;
            case UIMAPSHIP_ID_DOCK:
                data->active_id = event_id;
                data->function_dock = UIMAPSHIP_ID_DOCK;
                break;
            default:
                data->active_id = event_id;
                if(event_id >= UIMAPSHIP_ID_BAG_0_ITEM && event_id < UIMAPSHIP_ID_BAG_0_ITEM + UIMAPSHIP_BAG_COUNTS)
                {
                    index = event_id - UIMAPSHIP_ID_BAG_0_ITEM;
                    client_cmd_left_hit_bag_item(index);
                }
                break;
            }
        }
        break;
    case WM_LBUTTONUP:
        data->active_id = 0;
        break;
    }
    return  0;
}


void    redraw_uimapship_mouse_point_info(SLONG id, BMP *bitmap)
{
    SLONG   event = UIMAPSHIP_EVENT;

    switch(id)
    {
    case UIMAPSHIP_ID_CLOSE:
        redraw_event_info_bar(event, id, (USTR*)TEXTMSG_MENU_CLOSE, (USTR*)TEXTMSG_MENU_CLOSE_INFO, bitmap);
        break;
    default:
        if(id >= UIMAPSHIP_ID_BAG_0_ITEM && id < UIMAPSHIP_ID_BAG_0_ITEM + UIMAPSHIP_BAG_COUNTS)
        {
            SLONG   index, item_sx, item_sy;
			TPOS_ITEM	item;

            index = id - UIMAPSHIP_ID_BAG_0_ITEM;

            LOCK_CHARACTER(g_lPlayerIndex);
			GetCharacterBagItem(g_lPlayerIndex, index, &item);
            UNLOCK_CHARACTER(g_lPlayerIndex);

            if(! IsItemNone(&item))
            {
                item_sx = UIMAPSHIP_BAG_0_SX + (index % UIMAPSHIP_BAG_X_COUNT) * UIMAPSHIP_BAG_DX;
                item_sy = UIMAPSHIP_BAG_0_SY + (index / UIMAPSHIP_BAG_X_COUNT) * UIMAPSHIP_BAG_DY;
                redraw_icon_item_information(item_sx, item_sy, ITEM_INFO_NORMAL, &item, bitmap);
            }
        }
    }
}


SLONG   is_mapship_menu_opened(void)
{
    if(ui_mapship_data.is_opened)
        return  TRUE;
    return  FALSE;
}


void    open_mapship_menu(SLONG flag)
{
	if(flag)
	{
		ui_mapship_data.is_opened = TRUE;
		set_map_view_range(SCREEN_WIDTH/2, 0, SCREEN_WIDTH/2, SCREEN_HEIGHT);
	}
	else
	{
		ui_mapship_data.is_opened = FALSE;
		set_map_view_range(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	}
}

