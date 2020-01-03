/*
**	UIMapState.cpp
**	UI of map state.
**
**	Jack, 2002/07/03.
*/
#include "MainFun.h"
#include "NetGE_MainFunc.h"
#include "Map.h"
#include "CRange.h"
#include "MouseHand.h"
#include "UIMap.h"
#include "UIMapState.h"
#include "ClientMain.h"
#include "UIManFace.h"
#include "ErrorMsg.h"
#include "PosData.h"


UI_MAPSTATE_DATA    ui_mapstate_data;


/******************************************************************************************************************/
/* UI MAP STATE FUNCTIONS                                                                                         */
/******************************************************************************************************************/
int     init_ui_mapstate(void)
{
    USTR    filename[_MAX_FNAME];
    SLONG   result, i, frames;
    CAKE_FRAME_ANI  *cfa;
    UI_MAPSTATE_DATA *data = &ui_mapstate_data;

    //map state image -----------------
    data->cfa = NULL;
    for(i=0; i<32; i++)
    {
        data->cf[i] = NULL;
    }

    set_data_file(packed_menu_file);
    strcpy((char *)filename, "menu\\uistate.cak");
    result = load_cake_frame_ani_from_file((USTR*)filename, &data->cfa);
    if(TTN_OK != result)
        return  -1;
    frames = count_cake_frames(data->cfa);
    for(i=0; i<frames; i++)
    {
        cfa = get_specify_cake_frame_ani(data->cfa, i);
        data->cf[i] = cfa->cake_frame;
    }

    data->hilight_id = 0;
    data->active_id = 0;

    //load logbook ani image ----------------
    data->book_cfa = NULL;
    for(i=0; i<16; i++)
    {
        data->book_cf[i] = NULL;
    }
    set_data_file(packed_menu_file);
    strcpy((char *)filename, "menu\\logbook.cak");
    result = load_cake_frame_ani_from_file((USTR*)filename, &data->book_cfa);
    if(TTN_OK != result)
        return  -2;
    frames = count_cake_frames(data->book_cfa);
    for(i=0; i<frames; i++)
    {
        cfa = get_specify_cake_frame_ani(data->book_cfa, i);
        data->book_cf[i] = cfa->cake_frame;
    }
    data->book_frames = frames;

    // ------------------------------------
    data->book_page = 0;
    data->total_pages = 5;  //temp set.
    data->menu_state = UIMAPSTATE_MENU_SHOW_PAGE;
    data->menu_time = timeGetTime();

    // ------------------------------------
    data->is_opened = FALSE;


    return  0;
}


void    active_ui_mapstate(int active)
{
}


void    free_ui_mapstate(void)
{
    UI_MAPSTATE_DATA *data = &ui_mapstate_data;
    SLONG   i;

    if(data->cfa)
    {
        destroy_cake_frame_ani(&data->cfa);
        for(i=0; i<32; i++)
        {
            data->cf[i] = NULL;
        }
    }
    if(data->book_cfa)
    {
        destroy_cake_frame_ani(&data->book_cfa);
        for(i=0; i<16; i++)
        {
            data->book_cf[i] = NULL;
        }
    }
    return;
}



void    redraw_ui_mapstate(SLONG sx, SLONG sy, void *vbitmap)
{
    UI_MAPSTATE_DATA *data = &ui_mapstate_data;
    BMP *bitmap = (BMP*)vbitmap;
    CAKE_FRAME  *cf;
    SLONG   frame, x, y, id, event;
    //
    MANFACE_DATA    manface;
    USTR    info[128], temp[128];
    SLONG   len;
    SLONG   index;


    if(g_lPlayerIndex < 0)
        return;

    event = UIMAPSTATE_EVENT;

    //(1) background -------------------------------------------
    frame = UIMAPSTATE_FRAME_BKGND;
    id = UIMAPSTATE_ID_BKGND;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

    //(2) close button -----------------------------------------
    frame = UIMAPSTATE_FRAME_CLOSE;
    id = UIMAPSTATE_ID_CLOSE;
    if(data->active_id == id)
        frame += 1;
    else if(data->hilight_id == id)
        frame += 1;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

    //(3) prev page button -------------------------------------
    frame = UIMAPSTATE_FRAME_PREV_PAGE;
    id = UIMAPSTATE_ID_PREV_PAGE;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    if( (data->active_id == id) || (data->hilight_id == id) )
        put_rle(x, y, cf->rle, bitmap);
    if(data->menu_state == UIMAPSTATE_MENU_SHOW_PAGE)
        game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

    //(4) next page button -------------------------------------
    frame = UIMAPSTATE_FRAME_NEXT_PAGE;
    id = UIMAPSTATE_ID_NEXT_PAGE;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    if( (data->active_id == id) || (data->hilight_id == id) )
        put_rle(x, y, cf->rle, bitmap);
    if(data->menu_state == UIMAPSTATE_MENU_SHOW_PAGE)
        game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

    //(5) player's information ---------------------------------
    set_word_color(0, rgb2hi(20, 20, 255));
    //photo
    x = sx + UIMAPSTATE_PHOTO_SX;
    y = sy + UIMAPSTATE_PHOTO_SY;
    get_character_manface(g_lPlayerIndex, &manface);
    redraw_manface(x, y, &manface, bitmap);

    //mainname
    x = sx + UIMAPSTATE_MAINNAME_SX;
    y = sy + UIMAPSTATE_MAINNAME_SY;
    sprintf((char *)info, "~C0%s~C0", GetCharacterMainName(g_lPlayerIndex));
    print12(x, y, (USTR*)info, PEST_PUT, bitmap);

    //nickname
    x = sx + UIMAPSTATE_NICKNAME_SX;
    y = sy + UIMAPSTATE_NICKNAME_SY;
    sprintf((char *)info, "~C0%s~C0", GetCharacterNickName(g_lPlayerIndex));
    print12(x, y, (USTR*)info, PEST_PUT, bitmap);

    //career
    x = sx + UIMAPSTATE_CAREER_SX;
    y = sy + UIMAPSTATE_CAREER_SY;
    index = GetCharacterCareer(g_lPlayerIndex);
    sprintf((char *)info, "~C0%s~C0", get_career_name(index));
    print12(x, y, (USTR*)info, PEST_PUT, bitmap);

    //spouse
    x = sx + UIMAPSTATE_SPOUSE_SX;
    y = sy + UIMAPSTATE_SPOUSE_SY;
    sprintf((char *)info, "~C0%s~C0", GetCharacterSpouseName(g_lPlayerIndex));
    print12(x, y, (USTR*)info, PEST_PUT, bitmap);

    //exp
    x = sx + UIMAPSTATE_EXP_SX;
    y = sy + UIMAPSTATE_EXP_SY;
    sprintf((char *)info, "~C0%d~C0", GetCharacterExp(g_lPlayerIndex));
    print12(x, y, (USTR*)info, PEST_PUT, bitmap);
    set_word_color(0, SYSTEM_WHITE);

    //(6) show page --------------------------------------------
    if(data->menu_state == UIMAPSTATE_MENU_SHOW_PAGE)
    {
        //the first page is some information of the player.
        if(data->book_page == 0)
        {
            //page background.--------------
            frame = UIMAPSTATE_FRAME_LOGBOOK;
            cf = data->cf[frame];
            x = sx + cf->frame_rx;
            y = sy + cf->frame_ry;
            put_rle(x, y, cf->rle, bitmap);

            //page context -----------------
            set_word_color(0, rgb2hi(20, 20, 255));

            //country
            x = sx + UIMAPSTATE_COUNTRY_SX;
            y = sy + UIMAPSTATE_COUNTRY_SY;
            index = GetCharacterCountry(g_lPlayerIndex);
            sprintf((char *)info, "~C0%s~C0", get_country_name(index));
            print12(x, y, (USTR*)info, PEST_PUT, bitmap);

            //nobility
            x = sx + UIMAPSTATE_NOBILITY_SX;
            y = sy + UIMAPSTATE_NOBILITY_SY;
            sprintf((char *)info, "~C0%s~C0", GetCharacterNobilityName(g_lPlayerIndex));
            print12(x, y, (USTR*)info, PEST_PUT, bitmap);

            //guild
            x = sx + UIMAPSTATE_GUILD_SX;
            y = sy + UIMAPSTATE_GUILD_SY;
            sprintf((char *)info, "~C0%s~C0", GetCharacterGuildName(g_lPlayerIndex));
            print12(x, y, (USTR*)info, PEST_PUT, bitmap);

            //prestige
            sprintf((char *)temp, "%d", GetCharacterPrestige(g_lPlayerIndex));
            sprintf((char *)info, "~C0%s~C0", temp);
            len = strlen((const char *)temp);
            x = sx + UIMAPSTATE_PRESTIGE_SX + UIMAPSTATE_PRESTIGE_XL/2 - len * 3;
            y = sy + UIMAPSTATE_PRESTIGE_SY;
            print12(x, y, (USTR*)info, PEST_PUT, bitmap);

            //pkvalue
            sprintf((char *)temp, "%d", GetCharacterGoodEvil(g_lPlayerIndex));
            sprintf((char *)info, "~C0%s~C0", temp);
            x = sx + UIMAPSTATE_PKVALUE_SX + UIMAPSTATE_PKVALUE_XL/2 - len * 3;
            y = sy + UIMAPSTATE_PKVALUE_SY;
            print12(x, y, (USTR*)info, PEST_PUT, bitmap);

            //deposit
            sprintf((char *)temp, "%d", GetCharacterBodyMoney(g_lPlayerIndex));
            sprintf((char *)info, "~C0%s~C0", temp);
            x = sx + UIMAPSTATE_DEPOSIT_SX + UIMAPSTATE_DEPOSIT_XL/2 - len * 3;
            y = sy + UIMAPSTATE_DEPOSIT_SY;
            print12(x, y, (USTR*)info, PEST_PUT, bitmap);

            set_word_color(0, SYSTEM_WHITE);
        }
        //the other pages are logbook pages.
        else
        {
        }
    }

    //(7) turn page --------------------------------------------
    if(data->menu_state == UIMAPSTATE_MENU_TURN_TO_NEXT_PAGE)
    {
        frame = data->book_frame;
        cf = data->book_cf[frame];
        x = sx + cf->frame_rx;
        y = sy + cf->frame_ry;
        put_rle(x, y, cf->rle, bitmap);
    }

    if(data->menu_state == UIMAPSTATE_MENU_TURN_TO_PREV_PAGE)
    {
        frame = data->book_frame;
        cf = data->book_cf[frame];
        x = sx + cf->frame_rx;
        y = sy + cf->frame_ry;
        put_rle(x, y, cf->rle, bitmap);
    }
}


void    refresh_ui_mapstate(void)
{
    enum { TURN_PAGE_MS = 50 };
    UI_MAPSTATE_DATA *data = &ui_mapstate_data;
    DWORD   curr_time;

    switch(data->menu_state)
    {
    case UIMAPSTATE_MENU_TURN_TO_NEXT_PAGE:
        curr_time = timeGetTime();
        if(curr_time - data->menu_time > TURN_PAGE_MS)
        {
            data->book_frame ++;
            if(data->book_frame >= data->book_frames)
            {
                data->book_frame = data->book_frames-1;
                
                data->menu_state = UIMAPSTATE_MENU_SHOW_PAGE;
                data->book_page ++;
            }
            data->menu_time = curr_time;
        }
        break;
    case UIMAPSTATE_MENU_TURN_TO_PREV_PAGE:
        curr_time = timeGetTime();
        if(curr_time - data->menu_time > TURN_PAGE_MS)
        {
            data->book_frame --;
            if(data->book_frame < 0)
            {
                data->book_frame = 0;
                
                data->menu_state = UIMAPSTATE_MENU_SHOW_PAGE;
                data->book_page --;
            }
            data->menu_time = curr_time;
        }
        break;
    }
}


SLONG   handle_ui_mapstate(UINT message, WPARAM wParam, LPARAM lParam)
{
    UI_MAPSTATE_DATA *data = &ui_mapstate_data;
    static  SLONG   mouse_x, mouse_y;
    SLONG   event_type, event_id;

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
            case UIMAPSTATE_ID_CLOSE:
                data->active_id = event_id;
                close_map_submenu(SUBMENU_STATE);
                break;
            case UIMAPSTATE_ID_NEXT_PAGE:
                data->active_id = event_id;
                if(data->book_page < data->total_pages-1)
                {
                    data->menu_state = UIMAPSTATE_MENU_TURN_TO_NEXT_PAGE;
                    data->menu_time = timeGetTime();
                    data->book_frame = 0;
                }
                break;
            case UIMAPSTATE_ID_PREV_PAGE:
                data->active_id = event_id;
                if(data->book_page > 0)
                {
                    data->menu_state = UIMAPSTATE_MENU_TURN_TO_PREV_PAGE;
                    data->menu_time = timeGetTime();
                    data->book_frame = data->book_frames - 1;
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


void    redraw_uimapstate_mouse_point_info(SLONG id, BMP *bitmap)
{
    SLONG   event = UIMAPSTATE_EVENT;

    switch(id)
    {
    case UIMAPSTATE_ID_PREV_PAGE:
        redraw_event_info_bar(event, id, (USTR*)TEXTMSG_PREV_PAGE, (USTR*)TEXTMSG_PREV_PAGE, bitmap);
        break;
    case UIMAPSTATE_ID_NEXT_PAGE:
        redraw_event_info_bar(event, id, (USTR*)TEXTMSG_NEXT_PAGE, (USTR*)TEXTMSG_NEXT_PAGE, bitmap);
        break;
    case UIMAPSTATE_ID_CLOSE:
        redraw_event_info_bar(event, id, (USTR*)TEXTMSG_MENU_CLOSE, (USTR*)TEXTMSG_MENU_CLOSE_INFO, bitmap);
        break;
    }
}


SLONG   is_mapstate_menu_opened(void)
{
    if(ui_mapstate_data.is_opened)
        return  TRUE;
    return  FALSE;
}


void    open_mapstate_menu(SLONG flag)
{
	if(flag)
	{
		ui_mapstate_data.is_opened = TRUE;
		set_map_view_range(SCREEN_WIDTH/2, 0, SCREEN_WIDTH/2, SCREEN_HEIGHT);
	}
	else
	{
		ui_mapstate_data.is_opened = FALSE;
		set_map_view_range(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	}
}

