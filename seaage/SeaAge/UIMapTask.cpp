/*
**	UIMapTask.cpp
**	UI of map task.
**
**	Jack, 2002/07/03.
*/
#include "MainFun.h"
#include "CRange.h"
#include "MouseHand.h"
#include "UIMap.h"
#include "UIMapTask.h"
#include "ClientMain.h"
#include "ErrorMsg.h"
#include "CmdEvent.h"
#include "Map.h"


UI_MAPTASK_DATA ui_maptask_data;

/******************************************************************************************************************/
/* UI MAP TASK FUNCTIONS                                                                                          */
/******************************************************************************************************************/
int     init_ui_maptask(void)
{
    USTR    filename[_MAX_FNAME];
    SLONG   result, i, frames;
    CAKE_FRAME_ANI  *cfa;
    CAKE_FRAME  *cf;
    UI_MAPTASK_DATA *data = &ui_maptask_data;

    data->cfa = NULL;
    for(i=0; i<32; i++)
    {
        data->cf[i] = NULL;
    }

    set_data_file(packed_menu_file);
    strcpy((char *)filename, "menu\\uitask.cak");
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
    //
    cf = data->cf[UIMAPTASK_FRAME_VSCROLL_BAR];
    data->min_scroll_y = UIMAPTASK_VSCROLL_BKGND_SY + cf->rle->h / 2;
    data->max_scroll_y = UIMAPTASK_VSCROLL_BKGND_SY + UIMAPTASK_VSCROLL_BKGND_YL - cf->rle->h / 2;
    data->scroll_y_pos = data->min_scroll_y;

    return  0;
}


void    active_ui_maptask(int active)
{
}


void    free_ui_maptask(void)
{
    UI_MAPTASK_DATA *data = &ui_maptask_data;
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



void    redraw_ui_maptask(SLONG sx, SLONG sy, void *vbitmap)
{
    UI_MAPTASK_DATA *data = &ui_maptask_data;
    BMP *bitmap = (BMP*)vbitmap;
    CAKE_FRAME  *cf;
    SLONG   frame, x, y, id, event, xl, yl;

    event = UIMAPTASK_EVENT;

    //(1) background -------------------------------------------
    frame = UIMAPTASK_FRAME_BKGND;
    id = UIMAPTASK_ID_BKGND;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

    //(2) vscroll bar ------------------------------------------
    id = UIMAPTASK_ID_VSCROLL_BKGND;
    x = sx + UIMAPTASK_VSCROLL_BKGND_SX;
    y = sy + UIMAPTASK_VSCROLL_BKGND_SY;
    xl = UIMAPTASK_VSCROLL_BKGND_XL;
    yl = UIMAPTASK_VSCROLL_BKGND_YL;
    game_range.add( x, y, xl, yl, event, id);
    //
    id = UIMAPTASK_ID_VSCROLL_BAR;
    frame = UIMAPTASK_FRAME_VSCROLL_BAR;
    if(data->hilight_id == id)
        frame += 1;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + data->scroll_y_pos - cf->rle->h / 2;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

    //(3) task list --------------------------------------------
    //TODO:

    //(4) close button -----------------------------------------
    frame = UIMAPTASK_FRAME_CLOSE;
    id = UIMAPTASK_ID_CLOSE;
    if(data->active_id == id)
        frame += 1;
    else if(data->hilight_id == id)
        frame += 1;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);
}


void    refresh_ui_maptask(void)
{
}



SLONG   handle_ui_maptask(UINT message, WPARAM wParam, LPARAM lParam)
{
    UI_MAPTASK_DATA *data = &ui_maptask_data;
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
            case UIMAPTASK_ID_CLOSE:
                data->active_id = event_id;
                close_map_submenu(SUBMENU_TASK);
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


void    redraw_uimaptask_mouse_point_info(SLONG id, BMP *bitmap)
{
    SLONG   event = UIMAPTASK_EVENT;

    switch(id)
    {
    case UIMAPTASK_ID_CLOSE:
        redraw_event_info_bar(event, id, (USTR*)TEXTMSG_MENU_CLOSE, (USTR*)TEXTMSG_MENU_CLOSE_INFO, bitmap);
        break;
    }
}


SLONG   is_maptask_menu_opened(void)
{
    if(ui_maptask_data.is_opened)
        return  TRUE;
    return  FALSE;
}


void    open_maptask_menu(SLONG flag)
{
	if(flag)
	{
		ui_maptask_data.is_opened = TRUE;
		set_map_view_range(SCREEN_WIDTH/2, 0, SCREEN_WIDTH/2, SCREEN_HEIGHT);
	}
	else
	{
		ui_maptask_data.is_opened = FALSE;
		set_map_view_range(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	}
}

