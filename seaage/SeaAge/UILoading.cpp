/*
**  UILoading.cpp
**  user interface of loading.
**
**  Jack, 2002.5.9.
*/
#include "MainFun.h"
#include "ClientMain.h"
#include "UILoading.h"
#include "ErrorMsg.h"
#include "PosData.h"
#include "HrtBeat.h"
#include "Client_RecvMsg.h"
#include "Client_SendMsg.h"


LOADING_MAINGAME_DATA   loading_maingame_data;
UI_CHANGEMAP_LOADING    ui_changemap_loading;


/******************************************************************************************************************/
/* LOADING MAIN GAME FUNCTIONS                                                                                    */
/******************************************************************************************************************/
int     init_loading_main_game(void)
{
    LOADING_MAINGAME_DATA   *data = &loading_maingame_data;
    CAKE_FRAME_ANI  *cfa;
    USTR    filename[MAX_PATH];
    SLONG   result;

    set_data_file(packed_menu_file);
    strcpy((char *)filename, "menu\\loading.cak");
    result = load_cake_frame_ani_from_file((USTR*)filename, &data->cfa);
    if(TTN_OK != result)
        return  -1;

    cfa = get_specify_cake_frame_ani(data->cfa, 0);
    data->cf[0] = cfa->cake_frame;

    //
    strcpy((char *)data->title, TEXTMSG_WAIT_FOR_LOADING);
    data->effect = 0;

    return  0;
}


void    active_loading_main_game(int active)
{
}


void    free_loading_main_game(void)
{
    LOADING_MAINGAME_DATA   *data = &loading_maingame_data;

    destroy_cake_frame_ani(&data->cfa);
    data->cf[0] = NULL;
}


void    refresh_loading_main_game(void)
{
    LOADING_MAINGAME_DATA   *data = &loading_maingame_data;
    USTR    addr[32];
    SLONG	result, got, port;
	DWORD	event;

    if(timer_tick02 > 5)
    {
        data->effect ++;
        timer_tick02 = 0;
    }
	
	LOCK_GLOBALS(0);
	event = g_dwAppEvent;
	UNLOCK_GLOBALS(0);

	if(event == APPEVENT_START_LOGIN_ZONE)
	{
		got = get_change_map_addr_port((USTR*)addr, &port);
		if(got == TTN_OK)
		{
			init_heartbeat_data();
			result = ClientLoginZone(g_hWndGameEvent, (char *)addr, port, (char *)g_szPlayerMainName, POS_CLIENT_VERSION);
			switch(result)
			{
			case DLL_OK:
				result = ClientLogoutWorld();
				break;
			default:
				sprintf((char *)print_rec, ERRMSG_CANT_LOGIN_ZONE_SERVER);
				display_error_message((USTR*)print_rec, DISPLAY_MESSAGE_TO_SCREEN, screen_buffer);
				wait_key_time(' ', 80);
				break;
			}
		}

		LOCK_GLOBALS(0);
		g_dwAppEvent = 0;
		UNLOCK_GLOBALS(0);
	}
}


void    redraw_loading_main_game(SLONG sx, SLONG sy, void *vbitmap)
{
    LOADING_MAINGAME_DATA   *data = &loading_maingame_data;
    BMP *   bitmap = (BMP*)vbitmap;
    USTR    info[80], tmp[16];
    CAKE_FRAME  *cf;
    SLONG   dots;

    cf = data->cf[0];
    if(cf)
    {
        put_rle(cf->frame_rx, cf->frame_ry, cf->rle, bitmap);
    }
    sprintf((char *)info, "%s", data->title);
    memset(tmp, 0, 16);
    dots = data->effect % 3;
    memset(tmp, '.', dots);
    memset(&tmp[dots], ' ', 3-dots);
    strcat((char *)info, (const char *)tmp);
    display_error_message((USTR*)info, DISPLAY_MESSAGE_TO_BUFFER, bitmap);
}


SLONG   handle_loading_main_game(UINT message, WPARAM wParam, LPARAM lParam)
{
    int iRet;
    switch(message)
    {
    case WM_KEYDOWN:
        switch( wParam )
        {
        case VK_ESCAPE:
            iRet = ClientLogoutZone();
            if(iRet == SEND_MSG_OK)
            {
                set_next_app_state(APPSTATE_INIT_LOGIN);
                change_app_state();
            }
            break;
        }
        break;
    }
    return  0;
}



/******************************************************************************************************************/
/* CHANGEMAP LOADING FUNCTIONS                                                                                    */
/******************************************************************************************************************/
int     init_changemap_loading(void)
{
    UI_CHANGEMAP_LOADING    *data = &ui_changemap_loading;

    strcpy((char *)data->title, TEXTMSG_WAIT_FOR_LOADING);
    data->effect = 0;
    get_bitmap(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, screen_channel2, screen_buffer);

    return  0;
}


void    active_changemap_loading(int active)
{
}


void    free_changemap_loading(void)
{
}


void    refresh_changemap_loading(void)
{
    UI_CHANGEMAP_LOADING    *data = &ui_changemap_loading;
    USTR    addr[32];
    SLONG	result, got, port;
	DWORD	event;
    
    if(timer_tick02 > 5)
    {
        data->effect ++;
        timer_tick02 = 0;
    }

	LOCK_GLOBALS(0);
	event = g_dwAppEvent;
	UNLOCK_GLOBALS(0);

	if(event == APPEVENT_START_CHANGE_ZONE)
	{
		result = ClientLogoutZone();
		if(result == DLL_OK)
		{
			got = get_change_map_addr_port((USTR*)addr, &port);
			if(TTN_OK == got)
			{
				init_heartbeat_data();
				result = ClientLoginZone(g_hWndGameEvent, (char *)addr, port, (char *)g_szPlayerMainName, POS_CLIENT_VERSION);
			}
			else
			{
				sprintf((char *)print_rec, ERRMSG_CANT_GET_ZONE_SERVER_ADDRESS);
				display_error_message((USTR*)print_rec, DISPLAY_MESSAGE_TO_SCREEN, screen_buffer);
			}
		}

		LOCK_GLOBALS(0);
		g_dwAppEvent = 0;
		UNLOCK_GLOBALS(0);
	}
}


void    redraw_changemap_loading(SLONG sx, SLONG sy, void *vbitmap)
{
    UI_CHANGEMAP_LOADING    *data = &ui_changemap_loading;
    BMP *   bitmap = (BMP*)vbitmap;
    USTR    info[80], tmp[16];
    SLONG   dots;

    gray_put_bitmap(0, 0, screen_channel2, bitmap);
    sprintf((char *)info, "%s", data->title);
    memset(tmp, 0, 16);
    dots = data->effect % 3;
    memset(tmp, '.', dots);
    memset(&tmp[dots], ' ', 3-dots);
    strcat((char *)info, (const char *)tmp);
    display_error_message((USTR*)info, DISPLAY_MESSAGE_TO_BUFFER, bitmap);
}


SLONG   handle_changemap_loading(UINT message, WPARAM wParam, LPARAM lParam)
{
    int iRet;
    switch(message)
    {
    case WM_KEYDOWN:
        switch( wParam )
        {
        case VK_ESCAPE:
            iRet = ClientLogoutZone();
            if(iRet == SEND_MSG_OK)
            {
                set_next_app_state(APPSTATE_INIT_LOGIN);
                change_app_state();
            }
            break;
        }
        break;
    }
    return  0;
}


/******************************************************************************************************************/
/* TRANSFERING LOADING FUNCTIONS                                                                                  */
/******************************************************************************************************************/
void    redraw_transfer_waiting(void *vbitmap)
{
    UI_CHANGEMAP_LOADING    *data = &ui_changemap_loading;
    BMP *   bitmap = (BMP*)vbitmap;
    USTR    info[80], tmp[16];
    SLONG   dots;
	static	ULONG	effect = 0;

    sprintf((char *)info, "%s", TEXTMSG_WAIT_FOR_TRANSFER);
    memset(tmp, 0, 16);
    dots = effect % 3;
    memset(tmp, '.', dots);
    memset(&tmp[dots], ' ', 3-dots);
    strcat((char *)info, (const char *)tmp);
    display_error_message((USTR*)info, DISPLAY_MESSAGE_TO_BUFFER, bitmap);

    if(timer_tick02 > 5)
    {
        effect ++;
        timer_tick02 = 0;
    }
}

