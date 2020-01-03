/*
**	UIQuitGame.cpp 
**	ui of quit game functions.
**
**	Jack, 2003.2.20.
*/
#include "MainFun.h"
#include "ClientMain.h"
#include "CRange.h"
#include "UILoading.h"
#include "ErrorMsg.h"
#include "PosData.h"
#include "HrtBeat.h"
#include "Client_RecvMsg.h"
#include "Client_SendMsg.h"
#include "UIQuitGame.h"
#include "QQ.H"



QUITGAME_DATA	quitgame_data;

/************************************************************************************************************/
/* UI QUITGAME MAIN FUNCTIONS                                                                               */
/************************************************************************************************************/
int		init_ui_quitgame(void)
{
    USTR    filename[_MAX_FNAME];
    SLONG   result, i, frames;
    CAKE_FRAME_ANI  *cfa;
    QUITGAME_DATA	*data = &quitgame_data;

    data->cfa = NULL;
    for(i=0; i<32; i++)
    {
        data->cf[i] = NULL;
    }

    set_data_file(packed_menu_file);
    strcpy((char *)filename, "menu\\sysmenu.cak");
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
	//
    return  0;
}


void	active_ui_quitgame(int active)
{
}

void	free_ui_quitgame(void)
{
    QUITGAME_DATA	*data = &quitgame_data;
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

void	refresh_ui_quitgame(void)
{
}

void	redraw_ui_quitgame(SLONG sx, SLONG sy, void *vbitmap)
{
    QUITGAME_DATA	*data = &quitgame_data;
    BMP *bitmap = (BMP*)vbitmap;
    CAKE_FRAME  *cf;
    SLONG   frame, x, y, id, event;

	if(!data->is_opened)
		return;

    event = UIQUITGAME_EVENT;

    //(1) background -------------------------------------------
    frame = UIQUITGAME_FRAME_BKGND;
    id = UIQUITGAME_ID_BKGND;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

    //(2) return game button -----------------------------------
    frame = UIQUITGAME_FRAME_RETURN_GAME;
    id = UIQUITGAME_ID_RETURN_GAME;
    if(data->active_id == id)
        frame += 2;
    else if(data->hilight_id == id)
        frame += 1;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

    //(3) video options button ----------------------------------
    frame = UIQUITGAME_FRAME_VIDEO_OPTIONS;
    id = UIQUITGAME_ID_VIDEO_OPTIONS;
    if(data->active_id == id)
        frame += 2;
    else if(data->hilight_id == id)
        frame += 1;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

    //(4) audio options button ----------------------------------
    frame = UIQUITGAME_FRAME_AUDIO_OPTIONS;
    id = UIQUITGAME_ID_AUDIO_OPTIONS;
    if(data->active_id == id)
        frame += 2;
    else if(data->hilight_id == id)
        frame += 1;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

    //(5) myself settings button ---------------------------------
    frame = UIQUITGAME_FRAME_MYSELF_SETTINGS;
    id = UIQUITGAME_ID_MYSELF_SETTINGS;
    if(data->active_id == id)
        frame += 2;
    else if(data->hilight_id == id)
        frame += 1;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

    //(6) quit game button ---------------------------------------
    frame = UIQUITGAME_FRAME_QUIT_GAME;
    id = UIQUITGAME_ID_QUIT_GAME;
    if(data->active_id == id)
        frame += 2;
    else if(data->hilight_id == id)
        frame += 1;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);
}


SLONG	handle_ui_quitgame(UINT message, WPARAM wParam, LPARAM lParam)
{
    QUITGAME_DATA	*data = &quitgame_data;
    static  SLONG   mouse_x, mouse_y;
    SLONG   event_type, event_id, result;
    int iRet;

	result = 1;
    switch(message)
    {
    case WM_MOUSEMOVE:
        mouse_x = GET_X_LPARAM(lParam);
        mouse_y = GET_Y_LPARAM(lParam);
        event_type = event_id = 0;
        game_range.mapping(mouse_x, mouse_y, &event_type, &event_id);
		if(event_type == UIQUITGAME_EVENT)
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
			if(event_type == UIQUITGAME_EVENT)
			{
				switch(event_id)
				{
				case UIQUITGAME_ID_RETURN_GAME:
					data->is_opened = FALSE;
					break;
					
				case UIQUITGAME_ID_VIDEO_OPTIONS:
				case UIQUITGAME_ID_AUDIO_OPTIONS:
				case UIQUITGAME_ID_MYSELF_SETTINGS:
					break;
				case UIQUITGAME_ID_QUIT_GAME:
					data->active_id = event_id;
					qq_clear();
					iRet = ClientRequestExitGame();
					
					// 設置為正在退出遊戲狀態.
					g_IsExitingGame = 1;
					open_ui_quitgame( FALSE );
					break;
				}
				result = 0;
			}
        }
        break;
    case WM_LBUTTONUP:
		mouse_x = GET_X_LPARAM(lParam);
		mouse_y = GET_Y_LPARAM(lParam);
		event_type = event_id = 0;
		game_range.mapping(mouse_x, mouse_y, &event_type, &event_id);
		if(event_type == UIQUITGAME_EVENT)
		{
			data->active_id = 0;
			result = 0;
		}
        break;
    }
    return  result;
}


void	open_ui_quitgame(SLONG flag)
{
	quitgame_data.is_opened = flag ? TRUE : FALSE;
    ui_quitgame_clear( );
}

SLONG	is_ui_quitgame_opened(void)
{
	return	quitgame_data.is_opened ? TRUE : FALSE;
}

VOID   ui_quitgame_clear( VOID )
{
    quitgame_data.active_id = 0;
    quitgame_data.hilight_id = 0;
}