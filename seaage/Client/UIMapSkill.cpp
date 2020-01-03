/*
**	UIMapSkill.cpp
**	UI of map skill.
**
**	Jack, 2002/07/03.
*/
#include "MainFun.h"
#include "NetGE_MainFunc.h"
#include "Map.h"
#include "ClientMain.h"
#include "ErrorMsg.h"
#include "CRange.h"
#include "MouseHand.h"
#include "UIMap.h"
#include "UIMapSkill.h"
#include "UIMagicIcon.h"


//GLOBALS ///////////////////////////////////////////////////////////////////////////////////////////////////////////
UI_MAPSKILL_DATA    ui_mapskill_data;


//FUNCTIONS /////////////////////////////////////////////////////////////////////////////////////////////////////////

int     init_ui_mapskill(void)
{
    USTR    filename[_MAX_FNAME];
    SLONG   result, i, frames;
    CAKE_FRAME_ANI  *cfa;
    UI_MAPSKILL_DATA *data = &ui_mapskill_data;

    //map skill image ------------------------------------
    data->cfa = NULL;
    for(i=0; i<32; i++)
    {
        data->cf[i] = NULL;
    }

    set_data_file(packed_menu_file);
    strcpy((char *)filename, "menu\\uiskill.cak");
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
    data->is_opened = FALSE;

    return  0;
}


void    active_ui_mapskill(int active)
{
}


void    free_ui_mapskill(void)
{
    UI_MAPSKILL_DATA *data = &ui_mapskill_data;
    SLONG   i;

    if(data->cfa)
    {
        destroy_cake_frame_ani(&data->cfa);
        for(i=0; i<32; i++)
        {
            data->cf[i] = NULL;
        }
    }
    return;
}



void    redraw_ui_mapskill(SLONG sx, SLONG sy, void *vbitmap)
{
    UI_MAPSKILL_DATA *data = &ui_mapskill_data;
    BMP *bitmap = (BMP*)vbitmap;
    CAKE_FRAME  *cf;
    SLONG   frame, x, y, id, event, sx2, sy2;
    SLONG   i, j;
    SLONG   visible_magics, on_the_sea;
    SLONG   magic_no, level, icon_index, stars;
    char    info[80];
	SLONG	list_magic_no[MAX_CHARACTER_SKILLS];
	SLONG	list_magic_level[MAX_CHARACTER_SKILLS];

    if(g_lPlayerIndex < 0)
        return;

    //gather player's current visible magics. ----------------------
    LOCK_CHARACTER(g_lPlayerIndex);
    on_the_sea = IsCharacterOnTheSea(g_lPlayerIndex);
    visible_magics = 0;
    if(on_the_sea)
    {
        for(i=0; i<MAX_CHARACTER_SKILLS; i++)
        {
            magic_no = GetCharacterSkillNo(g_lPlayerIndex, i);
            if (IsListVisibleSkill(magic_no, 0)  && IsSeaSkill(magic_no, 0))
            {
				list_magic_level[visible_magics] = GetCharacterSkillLevel(g_lPlayerIndex, i);
                list_magic_no[visible_magics++] = magic_no;
            }
        }
	}
	else
	{
        for(i=0; i<MAX_CHARACTER_SKILLS; i++)
        {
            magic_no = GetCharacterSkillNo(g_lPlayerIndex, i);
            if( IsListVisibleSkill(magic_no, 0)  && IsLandSkill(magic_no, 0))
            {
				list_magic_level[visible_magics] = GetCharacterSkillLevel(g_lPlayerIndex, i);
                list_magic_no[visible_magics++] = magic_no;
            }
        }
    }
    UNLOCK_CHARACTER(g_lPlayerIndex);

    event = UIMAPSKILL_EVENT;

    //(1) background -------------------------------------------
    frame = UIMAPSKILL_FRAME_BKGND;
    id = UIMAPSKILL_ID_BKGND;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

    //(2) close button -----------------------------------------
    frame = UIMAPSKILL_FRAME_CLOSE;
    id = UIMAPSKILL_ID_CLOSE;
    if(data->active_id == id)
        frame += 1;
    else if(data->hilight_id == id)
        frame += 1;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

    //(3) skill icon & information list ------------------------
    for(i=0; i<visible_magics; i++)
    {
        sx2 = UIMAPSKILL_LIST_0_SX + UIMAPSKILL_LIST_DX * i;
        sy2 = UIMAPSKILL_LIST_0_SY + UIMAPSKILL_LIST_DY * i;

        magic_no = list_magic_no[i];
        level = list_magic_level[i];
        icon_index = GetSkillIconIndex(magic_no);
        if(icon_index >= 0)
        {
            //icon.
            x = sx2 + UIMAPSKILL_ICON_SX;
            y = sy2 + UIMAPSKILL_ICON_SY;
            redraw_magic_icon_image(x+MAGIC_ICON_WIDTH/2, y+MAGIC_ICON_HEIGHT/2, icon_index, bitmap, 0);
            
            //name
            x = sx2 + UIMAPSKILL_NAME_SX;
            y = sy2 + UIMAPSKILL_NAME_SY;
            sprintf((char *)info, "~C6~F2%s~C0~F0", GetSkillName(magic_no));
            print12(x, y, (USTR*)info, PEST_PUT, bitmap);

            //level(data/10)
            x = sx2 + UIMAPSKILL_LEVEL_SX;
            y = sy2 + UIMAPSKILL_LEVEL_SY;
            sprintf((char *)info, "~C6~F2%s:%d.%d~C0~F0", TEXTMSG_NAME_LEVEL, level/10, level%10);
            print12(x, y, (USTR*)info, PEST_PUT, bitmap);
            //stars.(count = data%10)
            frame = UIMAPSKILL_FRAME_STAR;
            cf = data->cf[frame];
            if(cf->rle)
            {
                stars = level % 10;
                x = sx2 + UIMAPSKILL_STAR_SX;
                y = sy2 + UIMAPSKILL_STAR_SY;
                
                for(j=0; j<stars; j++)
                {
                    put_rle(x, y, cf->rle, bitmap);
                    x += UIMAPSKILL_STAR_DX;
                    y += UIMAPSKILL_STAR_DY;
                }
            }

        }
    }
}


void    refresh_ui_mapskill(void)
{
}



SLONG   handle_ui_mapskill(UINT message, WPARAM wParam, LPARAM lParam)
{
    UI_MAPSKILL_DATA *data = &ui_mapskill_data;
    SLONG   mouse_x, mouse_y;
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
            case UIMAPSKILL_ID_CLOSE:
                data->active_id = event_id;
                close_map_submenu(SUBMENU_SKILL);
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


void    redraw_uimapskill_mouse_point_info(SLONG id, BMP *bitmap)
{
    SLONG   event = UIMAPSKILL_EVENT;

    switch(id)
    {
    case UIMAPSKILL_ID_CLOSE:
        redraw_event_info_bar(event, id, (USTR*)TEXTMSG_MENU_CLOSE, (USTR*)TEXTMSG_MENU_CLOSE_INFO, bitmap);
        break;
    }
    
}


SLONG   is_mapskill_menu_opened(void)
{
    if(ui_mapskill_data.is_opened)
        return  TRUE;
    return  FALSE;
}


void    open_mapskill_menu(SLONG flag)
{
	if(flag)
	{
		ui_mapskill_data.is_opened = TRUE;
		set_map_view_range(SCREEN_WIDTH/2, 0, SCREEN_WIDTH/2, SCREEN_HEIGHT);
	}
	else
	{
		ui_mapskill_data.is_opened = FALSE;
		set_map_view_range(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	}
}


