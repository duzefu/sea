/*
**  UI.cpp
**  user interface functions.
**
**  Jack, 2002.5.9.
**
**	Zhang Zhaohui, 2003.4.1
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
#include "qqmain.h"
#include "Config.h"
#include "MapObject.h"
#include "UIPosIME.h"
#include "SecretSkill.h"
#include "qqmsgbox.h"
#include "UILoading.h"
#include "UIQuitGame.h"
#include "UIManager.h"
//
#include "Client_RecvMsg.h"
#include "Client_SendMsg.h"
#include "Media.h"
#include "UIShowMap.h"

//
EULA_DATA           eula_data;          //eula data
UILOGIN             uilogin;            //login menu data
CREDITS_DATA        credits_data;       //credits menu data
SWS_DATA            sws_data;           //select world server menu data
SELCHAR_DATA        selchar_data;       //select character
CREATECHAR_DATA     createchar_data;    //create character
CHGCHARCOLOR_DATA	chgcharcolor_data;	//change character's color
SETCHARFACE_DATA    setcharface_data;   //set character face
SETCHARLOCATE_DATA  setcharlocate_data; //set character locate


// Zhang Zhaohui
CHAR	world_name[64];

//
//
//local functions:
SLONG   on_uilogin_login(void);
SLONG   on_uilogin_account_manager(void);
SLONG   on_uilogin_new_account(void);
SLONG   on_select_word_server_login(SLONG index);
SLONG   on_select_character_ok(SLONG index);
SLONG   on_select_character_back(void);
SLONG   on_select_character_face_ok(void);
void	update_changed_character_color(void);


//////////////////////////////////////////////////////////////////////////////////////////////
// UI(介面)                                                                                 //
//////////////////////////////////////////////////////////////////////////////////////////////
int init_ui(void)
{
    if(0 != init_image_rim())
        return  -10;
    if(0 != init_talk_rim())
        return  -20;
	if(0 != init_npc_shadow_image())
		return	-21;
    
    if(0 != init_combobox())
        return  -100;
    if(0 != init_ui_qq())
        return  -110;

    if(0 != init_map_ui())
        return  -30;
    if(0 != init_manface())
        return  -40;
    if(0 != init_ui_mapstate())
        return  -50;
    if(0 != init_ui_mapitem())
        return  -60;
    if(0 != init_ui_mapskill())
        return  -70;
    if(0 != init_ui_maptask())
        return  -80;
    if(0 != init_ui_mapship())
        return  -90;
    if(0 != init_mouse_hand())
        return  -120;
	if(0 != init_ui_msgbox())
		return	-130;
	if(0 != init_ui_quitgame())
		return	-131;

    if ( TTN_OK != init_sm( ) )
        return -132;

    return  0;
}



void    active_ui(int active)
{
}



void    free_ui(void)
{
    
    free_sm( );

	free_ui_quitgame();
	free_ui_msgbox();
    free_mouse_hand();
    free_ui_qq();
    free_combobox();
    free_ui_mapship();
    free_ui_maptask();
    free_ui_mapskill();
    free_ui_mapitem();
    free_ui_mapstate();
    free_manface();
    free_map_ui();
	free_npc_shadow_image();
    free_image_rim();
}


void    debug_redraw_mouse_position(void *vbitmap)
{
#ifdef  DEBUG
    BMP     *bitmap = (BMP *)vbitmap;
    SLONG   mouse_x, mouse_y;
    USTR    info[64];

    get_mouse_position(&mouse_x, &mouse_y);
    put_line(0, mouse_y, bitmap->w, mouse_y, SYSTEM_BLUE, bitmap);
    put_line(mouse_x, 0, mouse_x, bitmap->h, SYSTEM_BLUE, bitmap);
    sprintf((char *)info, "~C0~O3FPS=%d, MOUSE=(%d, %d)~C0~O0", get_fps(), mouse_x, mouse_y);
    print16(0, 0, (USTR*)info, COPY_PUT_COLOR(SYSTEM_BLUE), bitmap);
#endif//DEBUG
}


//////////////////////////////////////////////////////////////////////////////////////////////
// EULA(版權宣告)                                                                           //
//////////////////////////////////////////////////////////////////////////////////////////////
int     init_eula(void)
{
    USTR    filename[_MAX_FNAME];
    SLONG   result, i, frames;
    CAKE_FRAME_ANI  *cfa;
    CAKE_FRAME  *cf;

    eula_data.cfa = NULL;
    for(i=0; i<32; i++)
    {
        eula_data.cf[i] = NULL;
    }

    set_data_file(packed_menu_file);
    strcpy((char *)filename, "menu\\eula.cak");
    result = load_cake_frame_ani_from_file((USTR*)filename, &eula_data.cfa);
    if(TTN_OK != result)
        return  -1;

    frames = count_cake_frames(eula_data.cfa);
    for(i=0; i<frames; i++)
    {
        cfa = get_specify_cake_frame_ani(eula_data.cfa, i);
        eula_data.cf[i] = cfa->cake_frame;
    }

    eula_data.hilight_id = 0;
    eula_data.active_id = 0;

    cf = eula_data.cf[EULA_FRAME_VSCROLL_BAR];
    eula_data.min_scroll_y = EULA_VSCROLL_BKGND_SY + cf->rle->h / 2;
    eula_data.max_scroll_y = EULA_VSCROLL_BKGND_SY + EULA_VSCROLL_BKGND_YL - cf->rle->h / 2;
    eula_data.scroll_y_pos = eula_data.min_scroll_y;

    //
    eula_data.max_lines = 0;
    set_data_file(packed_data_file);
    eula_data.text_lines = load_text_file((USTR*)"data\\eula.txt");
    if(eula_data.text_lines)
    {
        eula_data.max_lines = count_text_line_nodes(eula_data.text_lines);
    }

    set_data_file(packed_music_file);

    play_music(13, 1);

	/*
#pragma message("The following functions call are for debug xsound.")
	//PS: channel 0 will used for SwapScr later, so, can't use it for debug.
	//play_voice(0, 1, (USTR*)"sound\\act0001.wav");
	play_voice(1, 1, (USTR*)"sound\\act0002.wav");
	play_voice(2, 1, (USTR*)"sound\\menu1011.wav");
	play_voice(3, 1, (USTR*)"sound\\menu1023.wav");
	play_voice(4, 1, (USTR*)"music\\mus001.wav");
	*/

    return 0;
}


void    active_eula(int active)
{
}


void    free_eula(void)
{
    SLONG   i;

    if(eula_data.cfa)
    {
        destroy_cake_frame_ani(&eula_data.cfa);
        eula_data.cfa = NULL;
        for(i=0; i<32; i++)
        {
            eula_data.cf[i] = NULL;
        }
    }
    if(eula_data.text_lines)
    {
        free_text_line_dlink(eula_data.text_lines);
        eula_data.text_lines = NULL;
    }

    //stop_music();
}


void    refresh_eula(void)
{
}


void    redraw_eula(SLONG sx, SLONG sy, void *vbitmap)
{
    BMP *bitmap = (BMP*)vbitmap;
    CAKE_FRAME  *cf;
    SLONG   frame, x, y, id, event;
    SLONG   i, index;
    TEXT_LINE_NODE  *node;
    USTR    info[512];

    event = EULA_EVENT;
    game_range.clear();

    //(1) background -------------------------------------------
    frame = EULA_FRAME_BKGND;
    id = EULA_ID_BKGND;
    cf = eula_data.cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

    //(2) vscroll bar ------------------------------------------
    game_range.add( EULA_VSCROLL_BKGND_SX, EULA_VSCROLL_BKGND_SY, EULA_VSCROLL_BKGND_XL, EULA_VSCROLL_BKGND_YL,
        EULA_EVENT, EULA_ID_VSCROLL_BKGND);

    frame = EULA_FRAME_VSCROLL_BAR;
    id = EULA_ID_VSCROLL_BAR;
    if(eula_data.hilight_id == id)
        frame += 1;
    cf = eula_data.cf[frame];
    x = sx + cf->frame_rx;
    y = sy + eula_data.scroll_y_pos - cf->rle->h / 2;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, EULA_EVENT, id);

    //(3) ok login button --------------------------------------
    frame = EULA_FRAME_OK;
    id = EULA_ID_OK;
    if(eula_data.active_id == id)
        frame += 2;
    else if(eula_data.hilight_id == id)
        frame += 1;
    cf = eula_data.cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

    //(4) back button ------------------------------------------
    frame = EULA_FRAME_BACK;
    id = EULA_ID_BACK;
    if(eula_data.active_id == id)
        frame += 2;
    else if(eula_data.hilight_id == id)
        frame += 1;
    cf = eula_data.cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

    //(5) eula text --------------------------------------------
    x = sx + EULA_TEXT_LINE_0_SX;
    y = sy + EULA_TEXT_LINE_0_SY;
    set_word_color(0, rgb2hi(63, 63, 255));
    for(i = 0; i<EULA_TEXT_LINES; i++)
    {
        index = eula_data.start_index + i;
        if(index >= 0 && index < eula_data.max_lines)
        {
            node = get_text_line_node(eula_data.text_lines, index);
            if(node)
            {
                sprintf((char *)info, "%s", node->text);
                print16(x, y, (USTR*)info, PEST_PUT, bitmap);
            }
        }
        x += EULA_TEXT_LINE_DX;
        y += EULA_TEXT_LINE_DY;
    }
    set_word_color(0, SYSTEM_WHITE);
}


SLONG   handle_eula(UINT message, WPARAM wParam, LPARAM lParam)
{
    SLONG   mouse_x, mouse_y, event_type, event_id;
    UCHR    ch;

    switch(message)
    {
    case WM_MOUSEMOVE:
        mouse_x = GET_X_LPARAM(lParam);
        mouse_y = GET_Y_LPARAM(lParam);
        event_type = event_id = 0;
        game_range.mapping(mouse_x, mouse_y, &event_type, &event_id);
        eula_data.hilight_id = event_id;
        if(wParam & MK_LBUTTON) //Drag
        {
            if(eula_data.mouse_event == MOUSE_EVENT_VSCROLL)
            {
                eula_data.scroll_y_pos = mouse_y;
                if(eula_data.scroll_y_pos < eula_data.min_scroll_y)
                    eula_data.scroll_y_pos = eula_data.min_scroll_y;
                if(eula_data.scroll_y_pos > eula_data.max_scroll_y)
                    eula_data.scroll_y_pos = eula_data.max_scroll_y;

                eula_data.start_index = (eula_data.scroll_y_pos - eula_data.min_scroll_y) * eula_data.max_lines
                    / (eula_data.max_scroll_y - eula_data.min_scroll_y);
                if(eula_data.start_index > eula_data.max_lines - 1)
                    eula_data.start_index = eula_data.max_lines - 1;
                if(eula_data.start_index < 0)
                    eula_data.start_index = 0;
            }
        }
        break;
    case WM_LBUTTONDOWN:
        {
            mouse_x = GET_X_LPARAM(lParam);
            mouse_y = GET_Y_LPARAM(lParam);
            event_type = event_id = 0;
            game_range.mapping(mouse_x, mouse_y, &event_type, &event_id);
            eula_data.mouse_event = 0;
            switch(event_id)
            {
            case EULA_ID_OK:
				eula_data.active_id = event_id;
				set_next_app_state(APPSTATE_INIT_LOGIN);
				change_app_state();
                break;

            case EULA_ID_BACK:
                eula_data.active_id = event_id;
                set_next_app_state(APPSTATE_SYSTEM_EXIT);
                change_app_state();
                break;

            case EULA_ID_VSCROLL_BAR:
                eula_data.mouse_event = MOUSE_EVENT_VSCROLL;
                break;
            }
        }
        break;
    case WM_LBUTTONUP:
        eula_data.active_id = 0;
        eula_data.mouse_event = 0;
        break;
    case WM_MOUSEWHEEL:
        {
            ch = read_mouse_key();
            switch(ch)
            {
            case MS_Forward:
                if(eula_data.start_index > 0)
                {
                    eula_data.start_index --;
                    if(eula_data.start_index == 0)
                    {
                        eula_data.scroll_y_pos = eula_data.min_scroll_y;
                    }
                    else
                    {
                        eula_data.scroll_y_pos = eula_data.min_scroll_y;
                        if(eula_data.max_lines > 0)
                        {
                            eula_data.scroll_y_pos += 
                                eula_data.start_index * (eula_data.max_scroll_y - eula_data.min_scroll_y) / 
                                eula_data.max_lines;
                        }
                    }
                }
                break;
            case MS_Backward:
                if(eula_data.start_index <  eula_data.max_lines - 1)
                {
                    eula_data.start_index ++;
                    if(eula_data.start_index == eula_data.max_lines -1)
                    {
                        eula_data.scroll_y_pos = eula_data.max_scroll_y;
                    }
                    else
                    {
                        eula_data.scroll_y_pos = eula_data.min_scroll_y;
                        if(eula_data.max_lines > 0)
                        {
                            eula_data.scroll_y_pos += 
                                eula_data.start_index * (eula_data.max_scroll_y - eula_data.min_scroll_y) / 
                                eula_data.max_lines;
                        }
                    }
                }
                break;
            }
        }
        break;
    }
    return  0;
}


//////////////////////////////////////////////////////////////////////////////////////////////
// LOGIN(登入介面)                                                                          //
//////////////////////////////////////////////////////////////////////////////////////////////
int init_uilogin(void)
{
    USTR    filename[_MAX_FNAME];
    SLONG   result, i, frames;
    CAKE_FRAME_ANI  *cfa;

    uilogin.cfa = NULL;
    for(i=0; i<32; i++)
    {
        uilogin.cf[i] = NULL;
    }

    set_data_file(packed_menu_file);
    strcpy((char *)filename, "menu\\login.cak");
    result = load_cake_frame_ani_from_file((USTR*)filename, &uilogin.cfa);
    if(TTN_OK != result)
        return  -1;

    frames = count_cake_frames(uilogin.cfa);
    for(i=0; i<frames; i++)
    {
        cfa = get_specify_cake_frame_ani(uilogin.cfa, i);
        uilogin.cf[i] = cfa->cake_frame;
    }
    uilogin.wheel_frame = 0;
    uilogin.wheel_dir = 1;
    memset(uilogin.account, '\0', 32);
    memset(uilogin.password, '\0', 32);
    uilogin.hilight_id = 0;
    uilogin.active_id = 0;
    uilogin.function_id = 0;

    //讓光標停在輸入帳號的位置
    uilogin.function_id = UILOGIN_ID_ACCOUNT;

    set_data_file(packed_music_file);
    play_music(13, 1);

    return 0;
}


void    free_uilogin(void)
{
    SLONG   i;

    if(uilogin.cfa)
    {
        destroy_cake_frame_ani(&uilogin.cfa);
        uilogin.cfa = NULL;
        for(i=0; i<32; i++)
        {
            uilogin.cf[i] = NULL;
        }
    }
}


void    active_uilogin(int active)
{
}


void    refresh_uilogin(void)
{
    if(timer_tick00 > 10)
    {
        uilogin.wheel_frame += uilogin.wheel_dir;
        if(uilogin.wheel_frame > 6)
        {
            uilogin.wheel_frame = 6;
            uilogin.wheel_dir = -1;
        }
        if(uilogin.wheel_frame < 0)
        {
            uilogin.wheel_frame = 0;
            uilogin.wheel_dir = 1;
        }

        timer_tick00 = 0;
    }
}


void    redraw_uilogin(SLONG sx, SLONG sy, void *vbitmap)
{
    BMP *bitmap = (BMP*)vbitmap;
    CAKE_FRAME  *cf;
    SLONG   frame, x, y, xl, yl, id, event;
    SLONG   len;
    USTR    info[64], mask[64];
    UILOGIN *data = &uilogin;

    event = UILOGIN_EVENT;
    game_range.clear();

    //(1) background -------------------------------------------
    id = UILOGIN_ID_BKGND;
    frame = UILOGIN_FRAME_BKGND;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

    //(2) new account button -----------------------------------
    frame = UILOGIN_FRAME_NEW_ACCOUNT;
    id = UILOGIN_ID_NEW_ACCOUNT;
    if(data->active_id == id)
        frame += 2;
    else if(data->hilight_id == id)
        frame += 1;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    //
    // Jack, cancel this function for test. [13:42,10/18/2002]
    //
    if(is_enable_create_account())
    {
        put_rle(x, y, cf->rle, bitmap);
        game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);
    }
    else
    {
        gray_put_rle(x, y, cf->rle, bitmap);
    }


    //(3) account manager button -------------------------------
    frame = UILOGIN_FRAME_ACCOUNT_MANAGER;
    id = UILOGIN_ID_ACCOUNT_MANAGER;
    if(data->active_id == id)
        frame += 2;
    else if(data->hilight_id == id)
        frame += 1;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    //
    // Jack, cancel this function for test. [13:42,10/18/2002]
    //
    if(is_enable_create_account())
    {
        put_rle(x, y, cf->rle, bitmap);
        game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);
    }
    else
    {
        gray_put_rle(x, y, cf->rle, bitmap);
    }

    //(4) back button ------------------------------------------
    frame = UILOGIN_FRAME_BACK;
    id = UILOGIN_ID_BACK;
    if(data->active_id == id)
        frame += 2;
    else if(data->hilight_id == id)
        frame += 1;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, UILOGIN_EVENT, id);

    //(5) steering wheel(credits button) -----------------------
    frame = UILOGIN_FRAME_STEERING_WHEEL;
    id = UILOGIN_ID_STEERING_WHEEL;
    frame += data->wheel_frame;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    if(data->hilight_id == id)
        mask_edge_put_rle(x, y, SYSTEM_YELLOW, cf->rle, bitmap);
    else
        put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, UILOGIN_EVENT, id);

    //(6) psalm of sea text image ------------------------------
    frame = UILOGIN_FRAME_POS_TEXT;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);

    //(7) account string ---------------------------------------
    id = UILOGIN_ID_ACCOUNT;
    x = sx + UILOGIN_ACCOUNT_BAR_SX;
    y = sy + UILOGIN_ACCOUNT_BAR_SY;
    xl = UILOGIN_ACCOUNT_BAR_XL;
    yl = UILOGIN_ACCOUNT_BAR_YL;
    game_range.add(x, y, xl, yl, UILOGIN_EVENT, id);
    len = strlen((const char *)data->account);
    if(data->function_id == id)
        sprintf((char *)info, "~C3%s_~C0", data->account);
    else
        sprintf((char *)info, "~C3%s~C0", data->account);
    set_word_color(3, rgb2hi(237, 98, 55));
    print16(sx + UILOGIN_ACCOUNT_INPUT_SX, sy + UILOGIN_ACCOUNT_INPUT_SY, (USTR*)info, PEST_PUT, bitmap);
    set_word_color(3, rgb2hi(0, 0, 255));


    //(8) password ---------------------------------------------
    id = UILOGIN_ID_PASSWORD;
    x = sx + UILOGIN_PASSWORD_BAR_SX;
    y = sy + UILOGIN_PASSWORD_BAR_SY;
    xl = UILOGIN_PASSWORD_BAR_XL;
    yl = UILOGIN_PASSWORD_BAR_YL;
    game_range.add(x, y, xl, yl, UILOGIN_EVENT, id);
    len = strlen((const char *)data->password);
    memset(mask, '\0', 64);
    memset(mask, '*', len);
    if(data->function_id == id)
        sprintf((char *)info, "~C3%s_~C0", mask);
    else
        sprintf((char *)info, "~C3%s~C0", mask);
    set_word_color(3, rgb2hi(237, 98, 55));
    print16(sx + UILOGIN_PASSWORD_INPUT_SX, sy + UILOGIN_PASSWORD_INPUT_SY, (USTR*)info, PEST_PUT, bitmap);
    set_word_color(3, rgb2hi(0, 0, 255));

    //(9) ok login button --------------------------------------
    frame = UILOGIN_FRAME_OK_LOGIN;
    id = UILOGIN_ID_OK_LOGIN;
    if(data->active_id == id)
        frame += 1; //ok login button has only 2 states.
    else if(data->hilight_id == id)
        frame += 1;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

}


SLONG   on_uilogin_login(void)
{
    UILOGIN *data = &uilogin;
    int     iRet;

    set_new_character_account((USTR*)data->account);
    
    if( 0 == strcmpi((const char *)data->account, ""))
    {
		display_message((char*)QQMB_TITLE_WARNING, (char*)ERRMSG_MUST_INPUT_ACCOUNT, 
			UIMB_OK | UIMB_OWN_MOUSE | UIMB_OWN_KEY, 500, TE_FONT_SIZE_20);
        //display_error_message((USTR*)ERRMSG_MUST_INPUT_ACCOUNT, DISPLAY_MESSAGE_TO_SCREEN, screen_buffer);
        //wait_key_time(' ', 80);
        return  -1;
    }
    if( 0 == strcmpi((const char *)data->password, ""))
    {
        display_error_message((USTR*)ERRMSG_MUST_INPUT_PASSWORD, DISPLAY_MESSAGE_TO_SCREEN, screen_buffer);
        wait_key_time(' ', 80);
        return  -2;
    }

    iRet = ClientLoginDoor(g_hWndGameEvent, (char *)user_config.door_address, (int)user_config.door_port, 
        (char *)data->account, (char *)data->password, POS_CLIENT_VERSION);
    switch(iRet)
    {
    case WINSOCK_VER_ERROR:
        display_error_message((USTR*)ERRMSG_WINSOCKET_VERSION, DISPLAY_MESSAGE_TO_SCREEN, screen_buffer);
        update_screen(screen_buffer);
        wait_key_time(' ', 80);
        return  -3;

    case INIT_SOCKET_ERROR:
        display_error_message((USTR*)ERRMSG_INIT_SOCKET, DISPLAY_MESSAGE_TO_SCREEN, screen_buffer);
        update_screen(screen_buffer);
        wait_key_time(' ', 80);
        return  -4;

    case CANT_CONNECTED:
        display_error_message((USTR*)ERRMSG_CANT_CONNECTED, DISPLAY_MESSAGE_TO_SCREEN, screen_buffer);
        update_screen(screen_buffer);
        wait_key_time(' ', 80);
        return  -5;

    case CANT_ASYNC:
        display_error_message((USTR*)ERRMSG_CANT_ASYNC, DISPLAY_MESSAGE_TO_SCREEN, screen_buffer);
        update_screen(screen_buffer);
        wait_key_time(' ', 80);
        return  -6;
        
    case SEND_MSG_OK:
        set_next_app_state(APPSTATE_INIT_SELECT_WORLD_SERVER);
        return  0;
    }
    return  0;
}


SLONG   on_uilogin_account_manager(void)
{
    UILOGIN *data = &uilogin;
    int     iRet;

    if( 0 == strcmpi((const char *)data->account, ""))
    {
        display_error_message((USTR*)ERRMSG_MUST_INPUT_ACCOUNT, DISPLAY_MESSAGE_TO_SCREEN, screen_buffer);
        wait_key_time(' ', 80);
        return  -1;
    }
    if( 0 == strcmpi((const char *)data->password, ""))
    {
        display_error_message((USTR*)ERRMSG_MUST_INPUT_PASSWORD, DISPLAY_MESSAGE_TO_SCREEN, screen_buffer);
        wait_key_time(' ', 80);
        return  -2;
    }
    
    iRet = ClientLoginDoor(g_hWndGameEvent, (char *)user_config.door_address, (int)user_config.door_port,
        (char *)data->account, (char *)data->password, POS_CLIENT_VERSION);
    switch(iRet)
    {
    case WINSOCK_VER_ERROR:
        display_error_message((USTR*)ERRMSG_WINSOCKET_VERSION, DISPLAY_MESSAGE_TO_SCREEN, screen_buffer);
        update_screen(screen_buffer);
        wait_key_time(' ', 80);
        return  -3;

    case INIT_SOCKET_ERROR:
        display_error_message((USTR*)ERRMSG_INIT_SOCKET, DISPLAY_MESSAGE_TO_SCREEN, screen_buffer);
        update_screen(screen_buffer);
        wait_key_time(' ', 80);
        return  -4;

    case CANT_CONNECTED:
        display_error_message((USTR*)ERRMSG_CANT_CONNECTED, DISPLAY_MESSAGE_TO_SCREEN, screen_buffer);
        update_screen(screen_buffer);
        wait_key_time(' ', 80);
        return  -5;

    case CANT_ASYNC:
        display_error_message((USTR*)ERRMSG_CANT_ASYNC, DISPLAY_MESSAGE_TO_SCREEN, screen_buffer);
        update_screen(screen_buffer);
        wait_key_time(' ', 80);
        return  -6;
        
    case SEND_MSG_OK:
        set_next_app_state(APPSTATE_INIT_ACCOUNT_MANAGER);
        return  0;
    }
    return  0;
}


SLONG   on_uilogin_new_account(void)
{
    int iRet;

    iRet = ClientLoginDoor(g_hWndGameEvent, (char *)user_config.door_address, (int)user_config.door_port, 
        (char *)"guest", (char *)"register", POS_CLIENT_VERSION);
    switch(iRet)
    {
    case WINSOCK_VER_ERROR:
        display_error_message((USTR*)ERRMSG_WINSOCKET_VERSION, DISPLAY_MESSAGE_TO_SCREEN, screen_buffer);
        update_screen(screen_buffer);
        wait_key_time(' ', 80);
        return  -3;

    case INIT_SOCKET_ERROR:
        display_error_message((USTR*)ERRMSG_INIT_SOCKET, DISPLAY_MESSAGE_TO_SCREEN, screen_buffer);
        update_screen(screen_buffer);
        wait_key_time(' ', 80);
        return  -4;

    case CANT_CONNECTED:
        display_error_message((USTR*)ERRMSG_CANT_CONNECTED, DISPLAY_MESSAGE_TO_SCREEN, screen_buffer);
        update_screen(screen_buffer);
        wait_key_time(' ', 80);
        return  -5;

    case CANT_ASYNC:
        display_error_message((USTR*)ERRMSG_CANT_ASYNC, DISPLAY_MESSAGE_TO_SCREEN, screen_buffer);
        update_screen(screen_buffer);
        wait_key_time(' ', 80);
        return  -6;
        
    case SEND_MSG_OK:
        set_next_app_state(APPSTATE_INIT_CREATE_ACCOUNT);
        return  0;
    }
    return  0;
}


SLONG   handle_uilogin(UINT message, WPARAM wParam, LPARAM lParam)
{
    SLONG   mouse_x, mouse_y;
    SLONG   event_type, event_id, len;
    BYTE    kb;
    UILOGIN *data = &uilogin;

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
            case UILOGIN_ID_STEERING_WHEEL:
                set_next_app_state(APPSTATE_INIT_CREDITS);
                change_app_state();
                data->function_id = event_id;
                break;
            case UILOGIN_ID_ACCOUNT:
                data->active_id = event_id;
                data->function_id = event_id;
                break;
            case UILOGIN_ID_PASSWORD:
                data->active_id = event_id;
                data->function_id = event_id;
                break;
            case UILOGIN_ID_NEW_ACCOUNT:
                data->active_id = event_id;
                data->function_id = event_id;
                on_uilogin_new_account();
                break;
            case UILOGIN_ID_ACCOUNT_MANAGER:
                data->active_id = event_id;
                data->function_id = event_id;
                on_uilogin_account_manager();
                break;
            case UILOGIN_ID_OK_LOGIN:
                data->active_id = event_id;
                data->function_id = event_id;
                on_uilogin_login();
                break;
            case UILOGIN_ID_BACK:
                data->active_id = event_id;
                data->function_id = event_id;
                set_next_app_state(APPSTATE_SYSTEM_EXIT);
                change_app_state();
                break;
            }
        }
        break;
    case WM_LBUTTONUP:
        data->active_id = 0;
        break;
    case WM_CHAR:
        {
            switch(data->function_id)
            {
            case UILOGIN_ID_ACCOUNT:
                switch(wParam)
                {
                case VK_BACK:
                    len = strlen((const char *)data->account);
                    if(len > 0) len--;
                    data->account[len] = '\0';
                    break;
                default:
                    kb = 0;
                    if(wParam >= '0' && wParam <= '9')
                        kb = wParam;
                    else if(wParam >= 'A' && wParam <= 'Z')
                        kb = wParam - 'A' + 'a';
                    else if(wParam >= 'a' && wParam <= 'z')
                        kb = wParam;
                    if(kb)
                    {
                        len = strlen((const char *)data->account);
                        if(len < 16)
                            data->account[len++] = kb;
                        data->account[len] = '\0';
                    }
                    break;
                }
                break;
            case UILOGIN_ID_PASSWORD:
                switch(wParam)
                {
                case VK_BACK:
                    len = strlen((const char *)data->password);
                    if(len > 0) len--;
                    data->password[len] = '\0';
                    break;
                default:
                    kb = 0;
                    if(wParam >= '0' && wParam <= '9')
                        kb = wParam;
                    else if(wParam >= 'A' && wParam <= 'Z')
                        kb = wParam - 'A' + 'a';
                    else if(wParam >= 'a' && wParam <= 'z')
                        kb = wParam;
                    if(kb)
                    {
                        len = strlen((const char *)data->password);
                        if(len < 16)
                            data->password[len++] = kb;
                        data->password[len] = '\0';
                    }
                    break;
                }
                break;
            }
        }
        break;
    case WM_KEYDOWN:
        {
            switch( wParam )
            {
            case VK_TAB:
                if(data->function_id == UILOGIN_ID_ACCOUNT)
                {
                    data->active_id = UILOGIN_ID_PASSWORD;
                    data->function_id = UILOGIN_ID_PASSWORD;
                }
                else
                {
                    data->active_id = UILOGIN_ID_ACCOUNT;
                    data->function_id = UILOGIN_ID_ACCOUNT;
                }
                break;
            case VK_RETURN:
                on_uilogin_login();
                break;
            }
        }
        break;
    default:
        break;
    }
    return  0;
}

//////////////////////////////////////////////////////////////////////////////////////////////
// CREDITS(製作群介面)                                                                      //
//////////////////////////////////////////////////////////////////////////////////////////////
int     init_credits(void)
{
    USTR    filename[_MAX_FNAME];
    SLONG   result, i, frames, x, y;
    CAKE_FRAME_ANI  *cfa;
    UCHR    alpha;

    credits_data.cfa = NULL;
    for(i=0; i<32; i++)
    {
        credits_data.cf[i] = NULL;
    }
    credits_data.text_abmp = NULL;

    set_data_file(packed_menu_file);
    strcpy((char *)filename, "menu\\credits.cak");
    result = load_cake_frame_ani_from_file((USTR*)filename, &credits_data.cfa);
    if(TTN_OK != result)
        return  -1;

    frames = count_cake_frames(credits_data.cfa);
    for(i=0; i<frames; i++)
    {
        cfa = get_specify_cake_frame_ani(credits_data.cfa, i);
        credits_data.cf[i] = cfa->cake_frame;
    }
    credits_data.hilight_id = 0;
    credits_data.active_id = 0;
    credits_data.text_image_sy = CREDITS_TEXT_BAR_YL;

    credits_data.text_abmp = create_abitmap(CREDITS_TEXT_BAR_XL, CREDITS_TEXT_BAR_YL);
    if(NULL == credits_data.text_abmp)
        return  -2;
    for(y = 0; y < credits_data.text_abmp->h; y ++)
    {
        if(y < 32)
            alpha = (USTR )(y * 8);
        else if(y > credits_data.text_abmp->h - 32)
            alpha = (USTR )((credits_data.text_abmp->h - y) * 8);
        else
            alpha = 255;
        for(x = 0; x < credits_data.text_abmp->w; x++)
        {
            credits_data.text_abmp->line[y][credits_data.text_abmp->w * SIZEOFPIXEL + x] = alpha;
        }
    }
    return 0;
}


void    active_credits(int active)
{
}


void    free_credits(void)
{
    SLONG   i;

    if(credits_data.cfa)
    {
        destroy_cake_frame_ani(&credits_data.cfa);
        credits_data.cfa = NULL;
        for(i=0; i<32; i++)
        {
            credits_data.cf[i] = NULL;
        }
    }
    if(credits_data.text_abmp)
    {
        destroy_abitmap(&credits_data.text_abmp);
    }
}


void    refresh_credits(void)
{
    if(timer_tick00 > 1)
    {
        credits_data.text_image_sy --;
        timer_tick00 = 0;

        if(credits_data.text_image_sy < -credits_data.cf[CREDITS_FRAME_TEXT]->rle->h - 20)
        {
            set_next_app_state(APPSTATE_INIT_LOGIN);
            change_app_state();
        }
    }
}


void    redraw_credits(SLONG sx, SLONG sy, void *vbitmap)
{
    BMP *bitmap = (BMP*)vbitmap;
    CAKE_FRAME  *cf;
    SLONG   frame, x, y, id;

    game_range.clear();

    //(1) background -------------------------------------------
    frame = CREDITS_FRAME_BKGND;
    cf = credits_data.cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, CREDITS_EVENT, CREDITS_ID_BKGND);

    //(2) back button ------------------------------------------
    frame = CREDITS_FRAME_BACK;
    id = CREDITS_ID_BACK;
    if(credits_data.active_id == id)
        frame += 2;
    else if(credits_data.hilight_id == id)
        frame += 1;
    cf = credits_data.cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, CREDITS_EVENT, id);

    //(3) credits text image -----------------------------------
    frame = CREDITS_FRAME_TEXT;
    cf = credits_data.cf[frame];
    x = sx + CREDITS_TEXT_BAR_SX;
    y = sy + CREDITS_TEXT_BAR_SY;
    clear_abitmap_image(credits_data.text_abmp);
    get_bitmap(x, y, CREDITS_TEXT_BAR_XL, CREDITS_TEXT_BAR_YL, (BMP*)credits_data.text_abmp, bitmap);
    put_rle(CREDITS_TEXT_BAR_XL/2 - cf->rle->w/2, credits_data.text_image_sy, cf->rle, (BMP*)credits_data.text_abmp);
    put_abitmap(x, y, credits_data.text_abmp, bitmap);
}


SLONG   handle_credits(UINT message, WPARAM wParam, LPARAM lParam)
{
    SLONG   mouse_x, mouse_y, event_type, event_id;
	USHORT	fwKeys;

    switch(message)
    {
    case WM_MOUSEMOVE:
        mouse_x = GET_X_LPARAM(lParam);
        mouse_y = GET_Y_LPARAM(lParam);
        event_type = event_id = 0;
        game_range.mapping(mouse_x, mouse_y, &event_type, &event_id);
        credits_data.hilight_id = event_id;
        break;
    case WM_LBUTTONDOWN:
        mouse_x = GET_X_LPARAM(lParam);
        mouse_y = GET_Y_LPARAM(lParam);
        event_type = event_id = 0;
        game_range.mapping(mouse_x, mouse_y, &event_type, &event_id);
        switch(event_id)
        {
        case CREDITS_ID_BACK:
			fwKeys = LOWORD(wParam);
			if( (fwKeys & MK_SHIFT) && (fwKeys & MK_CONTROL) )
			{
				set_next_app_state(APPSTATE_INIT_STARTING_SINGLE_GAME);
				change_app_state();
			}
			else
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

//////////////////////////////////////////////////////////////////////////////////////////////
// SELECT WORLD SERVER(選擇世界伺服器)                                                      //
//////////////////////////////////////////////////////////////////////////////////////////////
int     init_select_world_server(void)
{
    USTR    filename[_MAX_FNAME];
    SLONG   result, i, frames;
    CAKE_FRAME_ANI  *cfa;
    CAKE_FRAME  *cf;

    sws_data.cfa = NULL;
    for(i=0; i<32; i++)
    {
        sws_data.cf[i] = NULL;
    }

    set_data_file(packed_menu_file);
    strcpy((char *)filename, "menu\\server.cak");
    result = load_cake_frame_ani_from_file((USTR*)filename, &sws_data.cfa);
    if(TTN_OK != result)
        return  -1;

    frames = count_cake_frames(sws_data.cfa);
    for(i=0; i<frames; i++)
    {
        cfa = get_specify_cake_frame_ani(sws_data.cfa, i);
        sws_data.cf[i] = cfa->cake_frame;
    }

    //
    cf = sws_data.cf[SWS_FRAME_VSCROLL_BAR];
    sws_data.min_scroll_y = SWS_VSCROLL_BKGND_SY + cf->rle->h / 2;
    sws_data.max_scroll_y = SWS_VSCROLL_BKGND_SY + SWS_VSCROLL_BKGND_YL - cf->rle->h / 2;
    sws_data.scroll_y_pos = sws_data.min_scroll_y;

    sws_data.hilight_id = 0;
    sws_data.active_id = 0;
    sws_data.start_index = 0;
    sws_data.select_index = 0;

    return  0;
}


void    active_select_world_server(int active)
{
}


void    free_select_world_server(void)
{
    SLONG   i;

    if(sws_data.cfa)
    {
        destroy_cake_frame_ani(&sws_data.cfa);
        sws_data.cfa = NULL;
        for(i=0; i<32; i++)
        {
            sws_data.cf[i] = NULL;
        }
    }
}


void    refresh_select_world_server(void)
{
}


void    redraw_select_world_server(SLONG sx, SLONG sy, void *vbitmap)
{
    BMP *bitmap = (BMP*)vbitmap;
    CAKE_FRAME  *cf;
    SLONG   frame, x, y, id;
    SLONG   i, info_x, info_y, index;
    USTR    info[128];

    game_range.clear();

    //(1) background -------------------------------------------
    frame = SWS_FRAME_BKGND;
    cf = sws_data.cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, SWS_EVENT, SWS_ID_BKGND);

    //(2) ok button ---------------------------------------------
	frame = SWS_FRAME_OK;
	id = SWS_ID_OK;
	if(sws_data.active_id == id)
		frame += 2;
	else if(sws_data.hilight_id == id)
		frame += 1;
	cf = sws_data.cf[frame];
	x = sx + cf->frame_rx;
	y = sy + cf->frame_ry;

    g_dwConnectedServerType = ClientGetCurrentConnectedType();
    if(g_dwConnectedServerType & CONNECTED_SERVER_WORLD)
	{
		gray_put_rle(x, y, cf->rle, bitmap);
	}
	else
	{
		put_rle(x, y, cf->rle, bitmap);
		game_range.add(x, y, cf->rle->w, cf->rle->h, SWS_EVENT, id);
	}


    //(3) back button ------------------------------------------
    frame = SWS_FRAME_BACK;
    id = SWS_ID_BACK;
    if(sws_data.active_id == id)
        frame += 2;
    else if(sws_data.hilight_id == id)
        frame += 1;
    cf = sws_data.cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, SWS_EVENT, id);

    //(4) vscroll bar ------------------------------------------
    game_range.add( SWS_VSCROLL_BKGND_SX, SWS_VSCROLL_BKGND_SY, SWS_VSCROLL_BKGND_XL, SWS_VSCROLL_BKGND_YL,
        SWS_EVENT, SWS_ID_VSCROLL_BKGND);

    frame = SWS_FRAME_VSCROLL_BAR;
    id = SWS_ID_VSCROLL_BAR;
    if(sws_data.hilight_id == id)
        frame += 1;
    cf = sws_data.cf[frame];
    x = sx + cf->frame_rx;
    y = sy + sws_data.scroll_y_pos - cf->rle->h / 2;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, SWS_EVENT, id);
    

    //(5) world server info list -------------------------------
    set_word_color(1, rgb2hi(128, 128, 128));
    set_word_color(2, rgb2hi(0, 110, 0));
    set_word_color(3, rgb2hi(237, 98, 55));
    for(i = 0; i < SWS_SERVER_LIST_NUM; i++)
    {
        x = sx + SWS_SERVER_LIST_0_BAR_SX;
        y = sy + SWS_SERVER_LIST_0_BAR_SY + SWS_SERVER_LIST_BAR_DY * i;
        info_x = x + SWS_SERVER_LIST_INFO_RX;
        info_y = y + SWS_SERVER_LIST_INFO_RY;

        if(sws_data.select_index == i)
        {
            frame = SWS_FRAME_SELECT_BKGND;
            cf = sws_data.cf[frame];
            put_rle(sx+cf->frame_rx, sy+cf->frame_ry + i* SWS_SERVER_LIST_BAR_DY, cf->rle, bitmap);
        }

        index = sws_data.start_index + i;
        if(index >= 0 && index < max_world_info)
        {
            if(world_info[index].active) 
                sprintf((char *)info, "~C3%-16s ~C2%s~C3    %-5d~C0", world_info[index].name, 
                TEXTMSG_SERVER_ACTIVE, world_info[index].player_count);
            else
                sprintf((char *)info, "~C1%-16s ~C1%s~C1  %-5d~C0", world_info[index].name, 
                TEXTMSG_SERVER_MAINTAIN, world_info[index].player_count);
            print24(info_x, info_y, (USTR*)info, PEST_PUT, bitmap);

            game_range.add(x, y, SWS_SERVER_LIST_BAR_XL, SWS_SERVER_LIST_BAR_YL, SWS_EVENT, SWS_ID_SERVER_LIST_0 + i);
        }
    }
    set_word_color(1, rgb2hi(255, 0, 0));
    set_word_color(2, rgb2hi(0, 255, 0));
    set_word_color(3, rgb2hi(0, 0, 255));
}



SLONG   on_select_word_server_login(SLONG index)
{
    int iRet;

    if(index < 0 || index >= max_world_info)
        return  -1;

    if(!world_info[index].active)
        return  -2;

    iRet = ClientLoginWorld(g_hWndGameEvent, (char *)world_info[index].addr, (int)world_info[index].port,
        (char *)uilogin.account, (char *)uilogin.password, POS_CLIENT_VERSION);
    switch(iRet)
    {
    case SEND_MSG_OK:
        iRet = ClientLogoutDoor();

		// 保存 World Server 的名字
		lstrcpyn( world_name, world_info[index].name, 64 );
        break;
    default:
        break;
    }

    return  0;
}


SLONG   handle_select_world_server(UINT message, WPARAM wParam, LPARAM lParam)
{
    SLONG   mouse_x, mouse_y, event_type, event_id;
    SLONG   index;
    int     iRet;

    switch(message)
    {
    case WM_MOUSEMOVE:
        mouse_x = GET_X_LPARAM(lParam);
        mouse_y = GET_Y_LPARAM(lParam);
        event_type = event_id = 0;
        game_range.mapping(mouse_x, mouse_y, &event_type, &event_id);
        sws_data.hilight_id = event_id;
        if(wParam & MK_LBUTTON) //Drag
        {
            if(sws_data.mouse_event == MOUSE_EVENT_VSCROLL)
            {
                sws_data.scroll_y_pos = mouse_y;
                if(sws_data.scroll_y_pos < sws_data.min_scroll_y)
                    sws_data.scroll_y_pos = sws_data.min_scroll_y;
                if(sws_data.scroll_y_pos > sws_data.max_scroll_y)
                    sws_data.scroll_y_pos = sws_data.max_scroll_y;

                sws_data.start_index = (sws_data.scroll_y_pos - sws_data.min_scroll_y) * max_world_info 
                    / (sws_data.max_scroll_y - sws_data.min_scroll_y);
                if(sws_data.start_index > max_world_info - 1)
                    sws_data.start_index = max_world_info - 1;
                if(sws_data.start_index < 0)
                    sws_data.start_index = 0;
                if(sws_data.select_index > max_world_info - 1 - sws_data.start_index)
                    sws_data.select_index = max_world_info - 1 - sws_data.start_index;
            }
        }
        break;
    case WM_LBUTTONDOWN:
        {
            mouse_x = GET_X_LPARAM(lParam);
            mouse_y = GET_Y_LPARAM(lParam);
            event_type = event_id = 0;
            game_range.mapping(mouse_x, mouse_y, &event_type, &event_id);
            sws_data.mouse_event = 0;
            switch(event_id)
            {
            case SWS_ID_OK:
                sws_data.active_id = event_id;
                index = sws_data.start_index + sws_data.select_index;
                on_select_word_server_login(index);
                break;
            case SWS_ID_BACK:
                sws_data.active_id = event_id;
                iRet = ClientLogoutDoor();
                set_next_app_state(APPSTATE_INIT_LOGIN);
                change_app_state();
                break;
            case SWS_ID_SERVER_LIST_0:
            case SWS_ID_SERVER_LIST_0 + 1:
            case SWS_ID_SERVER_LIST_0 + 2:
            case SWS_ID_SERVER_LIST_0 + 3:
            case SWS_ID_SERVER_LIST_0 + 4:
                sws_data.select_index = event_id - SWS_ID_SERVER_LIST_0;
                break;
            case SWS_ID_VSCROLL_BAR:
                sws_data.mouse_event = MOUSE_EVENT_VSCROLL;
                break;
            }
        }
        break;
    case WM_LBUTTONDBLCLK:
        {
            mouse_x = GET_X_LPARAM(lParam);
            mouse_y = GET_Y_LPARAM(lParam);
            event_type = event_id = 0;
            game_range.mapping(mouse_x, mouse_y, &event_type, &event_id);
            switch(event_id)
            {
            case SWS_ID_SERVER_LIST_0:
            case SWS_ID_SERVER_LIST_0 + 1:
            case SWS_ID_SERVER_LIST_0 + 2:
            case SWS_ID_SERVER_LIST_0 + 3:
            case SWS_ID_SERVER_LIST_0 + 4:
                sws_data.active_id = event_id;
                sws_data.select_index = event_id - SWS_ID_SERVER_LIST_0;
                index = sws_data.start_index + sws_data.select_index;
                on_select_word_server_login(index);
                break;
            }
        }
        break;
    case WM_LBUTTONUP:
        sws_data.active_id = 0;
        sws_data.mouse_event = 0;
        break;
    }
    return  0;
}

//////////////////////////////////////////////////////////////////////////////////////////////
// SELECT CHARACTER(選擇角色)                                                               //
//////////////////////////////////////////////////////////////////////////////////////////////
int     init_select_character(void)
{
    USTR    filename[_MAX_FNAME];
    SLONG   result, i, frames;
    CAKE_FRAME_ANI  *cfa;

    selchar_data.cfa = NULL;
    for(i=0; i<32; i++)
    {
        selchar_data.cf[i] = NULL;
    }

    set_data_file(packed_menu_file);
    strcpy((char *)filename, "menu\\selchar.cak");
    result = load_cake_frame_ani_from_file((USTR*)filename, &selchar_data.cfa);
    if(TTN_OK != result)
        return  -1;

    frames = count_cake_frames(selchar_data.cfa);
    for(i=0; i<frames; i++)
    {
        cfa = get_specify_cake_frame_ani(selchar_data.cfa, i);
        selchar_data.cf[i] = cfa->cake_frame;
    }
    selchar_data.hilight_id = 0;
    selchar_data.active_id = 0;
    selchar_data.select_index = 0;
	selchar_data.on_linking = 0;

    return 0;
}

void    active_select_character(int active)
{
}


void    free_select_character(void)
{
    SLONG   i;

    if(selchar_data.cfa)
    {
        destroy_cake_frame_ani(&selchar_data.cfa);
        selchar_data.cfa = NULL;
        for(i=0; i<32; i++)
        {
            selchar_data.cf[i] = NULL;
        }
    }
}


void    refresh_select_character(void)
{
}


void    redraw_select_character(SLONG sx, SLONG sy, void *vbitmap)
{
    BMP *bitmap = (BMP*)vbitmap;
    CAKE_FRAME  *cf;
    SLONG   frame, x, y, id, event;
    SLONG   index, i, career, sex, country;
    USTR    info[80];

    event = SELCHAR_EVENT;
    game_range.clear();

    //(1) background -------------------------------------------
    frame = SELCHAR_FRAME_BKGND;
    id = SELCHAR_ID_BKGND;
    cf = selchar_data.cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

    //(2) delete character button ------------------------------
    frame = SELCHAR_FRAME_DELETE_CHAR;
    id = SELCHAR_ID_DELETE_CHAR;
    if(selchar_data.active_id == id)
        frame += 2;
    else if(selchar_data.hilight_id == id)
        frame += 1;
    cf = selchar_data.cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
	if(selchar_data.on_linking)
	{
		gray_put_rle(x, y, cf->rle, bitmap);
	}
	else
	{
		put_rle(x, y, cf->rle, bitmap);
		game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);
	}


    //(3) ok button ---------------------------------------------
    frame = SELCHAR_FRAME_OK;
    id = SELCHAR_ID_OK;
    if(selchar_data.active_id == id)
        frame += 2;
    else if(selchar_data.hilight_id == id)
        frame += 1;
    cf = selchar_data.cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
	if(selchar_data.on_linking)
	{
		gray_put_rle(x, y, cf->rle, bitmap);
	}
	else
	{
		put_rle(x, y, cf->rle, bitmap);
		game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);
	}


    //(4) back button ------------------------------------------
    frame = SELCHAR_FRAME_BACK;
    id = SELCHAR_ID_BACK;
    if(selchar_data.active_id == id)
        frame += 2;
    else if(selchar_data.hilight_id == id)
        frame += 1;
    cf = selchar_data.cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);


    //(5) character photos -------------------------------------
    for(i = 0; i<MAX_CHARACTER_INFO; i++)
    {
        index = i;
        if(character_info[index].flag)
        {
            career = character_info[index].career;
            sex = character_info[index].sex;
            frame = SELCHAR_FRAME_CHAR_0 + get_character_main_face(career, sex);
        }
        else
        {
            frame = SELCHAR_FRAME_NEW_CHAR;
        }
        id = SELCHAR_ID_CHAR_0 + i;
        cf = selchar_data.cf[frame];
        x = sx + SELCHAR_CHAR_0_SX + SELCHAR_CHAR_DX * i;
        y = sy + SELCHAR_CHAR_0_SY + SELCHAR_CHAR_DY * i;
        if(selchar_data.select_index == i)
            put_rle(x, y, cf->rle, bitmap);
        else
            gray_put_rle(x, y, cf->rle, bitmap);

		if(! selchar_data.on_linking)
		{
			game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);
		}
    }

    //(6) character information --------------------------------
    index = selchar_data.select_index;
    if(index >= 0 && index < MAX_CHARACTER_INFO)
    {
        if(character_info[index].flag)
        {
            set_word_color(2, rgb2hi(237, 98, 55));

            //mainname
            x = sx + SELCHAR_MAINNAME_SX;
            y = sy + SELCHAR_MAINNAME_SY;
            sprintf((char *)info, "~C2%s~C0", character_info[index].mainname);
            print24(x, y, (USTR*)info, PEST_PUT, bitmap);

            //nickname
            x = sx + SELCHAR_NICKNAME_SX;
            y = sy + SELCHAR_NICKNAME_SY;
            sprintf((char *)info, "~C2%s~C0", character_info[index].nickname);
            print24(x, y, (USTR*)info, PEST_PUT, bitmap);

            //career
            x = sx + SELCHAR_CAREER_SX;
            y = sy + SELCHAR_CAREER_SY;
            career = character_info[index].career;
            sprintf((char *)info, "~C2%s~C0", get_career_name(career));
            print24(x, y, (USTR*)info, PEST_PUT, bitmap);

            //level
            x = sx + SELCHAR_LEVEL_SX;
            y = sy + SELCHAR_LEVEL_SY;
            sprintf((char *)info, "~C2%d~C0", character_info[index].level + 1);
            print24(x, y, (USTR*)info, PEST_PUT, bitmap);

            //country
            x = sx + SELCHAR_COUNTRY_SX;
            y = sy + SELCHAR_COUNTRY_SY;
            country = character_info[index].country;
            sprintf((char *)info, "~C2%s~C0", get_country_name(country));
            print24(x, y, (USTR*)info, PEST_PUT, bitmap);

            //rank
            x = sx + SELCHAR_RANK_SX;
            y = sy + SELCHAR_RANK_SY;
            sprintf((char *)info, "~C2%s~C0", character_info[index].nobility);
            print24(x, y, (USTR*)info, PEST_PUT, bitmap);

            set_word_color(2, rgb2hi(0, 0, 255));
        }
    }
}


SLONG   on_select_character_ok(SLONG index)
{
    int     iRet;

    if(character_info[index].flag)  //已經存在該人物, 選擇以進入ZONE
    {   
        //保存玩家的MAINNAME. 以後當玩家進入地圖時需要用到.
        strcpy((char *)g_szPlayerMainName, (const char *)character_info[index].mainname);
		//保存玩家的ZONE, 以後當玩家LOGIN ZONE 時會引用到.
		strcpy((char *)g_szPlayerZone, (const char *)character_info[index].zone);
        
		iRet = ClientRequestChooseCharacter(character_info[index].qqid);
		if(iRet != SEND_MSG_OK)
		{
			//TODO:
		}
		selchar_data.on_linking = 1;
    }
    else    //該人物不存在, 選擇以創建新的人物.
    {
        //設置新建人物是該帳號的第幾個人物.
        set_new_character_index(index);
        set_next_app_state(APPSTATE_INIT_CREATE_CHARACTER);
        change_app_state();
    }
    return  0;
}


SLONG   on_select_character_back(void)
{
    int iRet;

    iRet = ClientLogoutWorld();
    iRet = ClientLoginDoor(g_hWndGameEvent, (char *)user_config.door_address, (int)user_config.door_port,
        (char *)uilogin.account, (char *)uilogin.password, POS_CLIENT_VERSION);
    switch(iRet)
    {
    case SEND_MSG_OK:
        set_next_app_state(APPSTATE_INIT_SELECT_WORLD_SERVER);
        break;
    default:
        break;
    }
    return  0;
}


SLONG   on_select_character_delete(SLONG index)
{
	UIMSGBOX	mb;
	char		text[80];
	
    if(character_info[index].flag)
	{
		memset(&mb, 0, sizeof(mb));
		mb.pfunc = yes_no_message_box_callback;
		mb.disp_time = 0;
		mb.font_size = TE_FONT_SIZE_12;
		mb.msgbox_type = UIMB_YESNO | UIMB_OWN_MOUSE;
		
		sprintf((char *)text, TEXTMSG_ASK_DEL_CHARACTER, character_info[index].mainname);
		strcpy(mb.title_info, "");
		strcpy(mb.text_info, (const char *)text);
		
		mb.param.event_id = ASK_DEL_CHARACTER_AT_WORLD;
		strcpy(mb.param.str, (const char*)character_info[index].mainname);
		msg_box(MB_CENTER_X, MB_CENTER_Y, &mb);
	}
	/*
    int iRet;
    
    if(character_info[index].flag)
    {
		iRet = ClientRequestDeleteCharacter((char *)character_info[index].mainname);
        switch(iRet)
        {
        case SEND_MSG_OK:
            break;
        default:
            //display_error_message((USTR*)"刪除角色失敗", DISPLAY_MESSAGE_TO_SCREEN, screen_buffer);
            display_error_message((USTR*)"DELETE CHARACTER FAILED", DISPLAY_MESSAGE_TO_SCREEN, screen_buffer);
            update_screen(screen_buffer);
            wait_key_time(' ', 80);
            break;
        }
    }
	*/
    return  0;
}


SLONG   handle_select_character(UINT message, WPARAM wParam, LPARAM lParam)
{
    SLONG   mouse_x, mouse_y;
    SLONG   event_type, event_id, index;

    switch(message)
    {
    case WM_MOUSEMOVE:
        mouse_x = GET_X_LPARAM(lParam);
        mouse_y = GET_Y_LPARAM(lParam);
        event_type = event_id = 0;
        game_range.mapping(mouse_x, mouse_y, &event_type, &event_id);
        selchar_data.hilight_id = event_id;
        break;
    case WM_LBUTTONDOWN:
        {
            mouse_x = GET_X_LPARAM(lParam);
            mouse_y = GET_Y_LPARAM(lParam);
            event_type = event_id = 0;
            game_range.mapping(mouse_x, mouse_y, &event_type, &event_id);
            switch(event_id)
            {
            case SELCHAR_ID_DELETE_CHAR:
                selchar_data.active_id = event_id;
                index = selchar_data.select_index;
                on_select_character_delete(index);
                break;
            case SELCHAR_ID_OK:
                selchar_data.active_id = event_id;
                index = selchar_data.select_index;
                on_select_character_ok(index);
                break;
            case SELCHAR_ID_BACK:
                selchar_data.active_id = event_id;
                on_select_character_back();
                break;
            case SELCHAR_ID_CHAR_0 + 0:
            case SELCHAR_ID_CHAR_0 + 1:
            case SELCHAR_ID_CHAR_0 + 2:
            case SELCHAR_ID_CHAR_0 + 3:
                selchar_data.active_id = event_id;
                selchar_data.select_index = event_id - SELCHAR_ID_CHAR_0;
                break;
            }
        }
        break;
    case WM_LBUTTONDBLCLK:
        {
            mouse_x = GET_X_LPARAM(lParam);
            mouse_y = GET_Y_LPARAM(lParam);
            event_type = event_id = 0;
            game_range.mapping(mouse_x, mouse_y, &event_type, &event_id);
            switch(event_id)
            {
            case SELCHAR_ID_CHAR_0 + 0:
            case SELCHAR_ID_CHAR_0 + 1:
            case SELCHAR_ID_CHAR_0 + 2:
            case SELCHAR_ID_CHAR_0 + 3:
                selchar_data.active_id = event_id;
                selchar_data.select_index = event_id - SELCHAR_ID_CHAR_0;
                index = selchar_data.select_index;
                on_select_character_ok(index);
                break;
            }
        }
        break;
    case WM_LBUTTONUP:
        selchar_data.active_id = 0;
        break;
    case WM_KEYDOWN:
        {
            switch( wParam )
			{
			case VK_ESCAPE:
                on_select_character_back();
				break;
			}
		}
		break;
	}
    return  0;
}

//////////////////////////////////////////////////////////////////////////////////////////////
// CREATE CHARACTER(創建角色)                                                               //
//////////////////////////////////////////////////////////////////////////////////////////////
int     init_create_character(void)
{
    static  POINT   char_pos[CREATECHAR_MAX_BODY] = 
    {
        {   CREATECHAR_BODY_0_SX,   CREATECHAR_BODY_0_SY    },
        {   CREATECHAR_BODY_1_SX,   CREATECHAR_BODY_1_SY    },
        {   CREATECHAR_BODY_2_SX,   CREATECHAR_BODY_2_SY    },
        {   CREATECHAR_BODY_3_SX,   CREATECHAR_BODY_3_SY    },
        {   CREATECHAR_BODY_4_SX,   CREATECHAR_BODY_4_SY    },
        {   CREATECHAR_BODY_5_SX,   CREATECHAR_BODY_5_SY    },
        {   CREATECHAR_BODY_6_SX,   CREATECHAR_BODY_6_SY    },
        {   CREATECHAR_BODY_7_SX,   CREATECHAR_BODY_7_SY    },
        {   CREATECHAR_BODY_8_SX,   CREATECHAR_BODY_8_SY    },
        {   CREATECHAR_BODY_9_SX,   CREATECHAR_BODY_9_SY    },
        {   CREATECHAR_BODY_10_SX,  CREATECHAR_BODY_10_SY   },
        {   CREATECHAR_BODY_11_SX,  CREATECHAR_BODY_11_SY   },
        {   CREATECHAR_BODY_12_SX,  CREATECHAR_BODY_12_SY   },
        {   CREATECHAR_BODY_13_SX,  CREATECHAR_BODY_13_SY   },
    };
    CREATECHAR_DATA *data = &createchar_data;
    USTR    filename[_MAX_FNAME];
    SLONG   result, i, frames;
    CAKE_FRAME_ANI  *cfa;
	SLONG	style_index;

    //main menu images ------------------------------------
    data->cfa = NULL;
    for(i=0; i<32; i++)
    {
        data->cf[i] = NULL;
    }

    set_data_file(packed_menu_file);
    strcpy((char *)filename, "menu\\found.cak");
    result = load_cake_frame_ani_from_file((USTR*)filename, &data->cfa);
    if(TTN_OK != result)
        return  -1;

    frames = count_cake_frames(data->cfa);
    for(i=0; i<frames; i++)
    {
        cfa = get_specify_cake_frame_ani(data->cfa, i);
        data->cf[i] = cfa->cake_frame;
    }

    //ani images ------------------------------------------
    data->ani_cfa = NULL;
    set_data_file(packed_menu_file);
    strcpy((char *)filename, "menu\\triani.cak");
    result = load_cake_frame_ani_from_file((USTR*)filename, &data->ani_cfa);
    if(TTN_OK != result)
        return  -1;
    data->ani_ptr = data->ani_cfa->next;

    //使用遊戲中NPC的數據結構, 將待選影像作為NPC來對待 -----------------------------------
    //MAX_GAME_MANCHAR = CREATECHAR_MAX_BODY
    //設置NPC的數據資料-------------
	LOCK_CHARACTER(0);
    clear_all_map_npc();
	InitAllZoneCharacters();
    for(i=0; i<MAX_GAME_MANCHAR; i++)
    {
        if(manchar_set[i].flag)
        {
			// We use DoingMagic for style_index([0~2]).
			style_index = 0;
			//SetCharacterDoingMagic(i, (SHINT)style_index); 
			//
			SetCharacterFileIndex(i, manchar_set[i].file_index[style_index]);
            SetCharacterImageID(i, INVALID_OBJECT_ID);
			SetCharacterDirFrame(i, 0);
            SetCharacterMoveSpeed(i, 8);
            SetCharacterPosition(i, char_pos[i].x + CREATECHAR_BODY_XL / 2, char_pos[i].y + CREATECHAR_BODY_YL, 0);
            SetCharacterDir(i, NPC_DOWN);
            SetCharacterOnFightState(i, true);
			SetCharacterDoingKindStep(i, DOING_KIND_IDLE, 0);
            SetCharacterOnFightState(i, false);
			set_npc_ext_id(i, INVALID_OBJECT_ID);
            active_map_npc(i);
        }
    }
	UNLOCK_CHARACTER(0);
    //通過刷新一次以載入NPC的影像資料
    refresh_ui_npc();
    update_ui_npc_object();


    //載入角色說明文字 -----------------------------------------------------------------
    //MAX_GAME_MANCHAR = CREATECHAR_MAX_BODY
    set_data_file(packed_data_file);
    for(i=0; i<MAX_GAME_MANCHAR; i++)
    {
        data->text_lines[i] = NULL;
        data->max_lines[i] = 0;

        sprintf((char *)filename, "data\\career%02d.txt", i);
        data->text_lines[i] = load_text_file((USTR*)filename);
        if(data->text_lines[i])
        {
            data->max_lines[i] = count_text_line_nodes(data->text_lines[i]);
        }
    }

    //創建並準備文字顯示效果的影像 -----------------------------------------------------
    SLONG   x, y;
    UCHR    alpha;
    data->text_abmp = create_abitmap(CREATECHAR_TEXT_BAR_XL, CREATECHAR_TEXT_BAR_YL);
    if(NULL == data->text_abmp)
        return  -2;
    for(y = 0; y < data->text_abmp->h; y ++)
    {
        if(y < 32)
            alpha = (USTR )(y * 8);
        else if(y > data->text_abmp->h - 32)
            alpha = (USTR )((data->text_abmp->h - y) * 8);
        else
            alpha = 255;
        for(x = 0; x < data->text_abmp->w; x++)
        {
            data->text_abmp->line[y][data->text_abmp->w * SIZEOFPIXEL + x] = alpha;
        }
    }

    //初始化數值資料 ----------------------------------------------------
    data->text_start_y = CREATECHAR_TEXT_BAR_YL + CREATECHAR_TEXT_DY;
    data->hilight_id = 0;
    data->active_id = 0;
    data->select_index = 2; // Jack, 測試版本,目前默認設定為男劍客 [03:56,10/17/2002]

    return 0;
}


void    active_create_character(int active)
{
}


void    free_create_character(void)
{
    CREATECHAR_DATA *data = &createchar_data;
    SLONG   i;

    //釋放介面圖像 --------------------------------------
    destroy_cake_frame_ani(&data->cfa);
    for(i=0; i<32; i++)
    {
        data->cf[i] = NULL;
    }
    destroy_cake_frame_ani(&data->ani_cfa);

    //釋放角色選擇圖(角色戰鬥待機圖) --------------------
    free_ui_npc_object();
    clear_all_map_npc();

    //釋放人物文字介紹資料 -----------------------------
    for(i=0; i<MAX_GAME_MANCHAR; i++)
    {
        if(data->text_lines[i])
        {
            free_text_line_dlink(data->text_lines[i]);
            data->text_lines[i] = NULL;
            data->max_lines[i] = 0;
        }
    }
}


void    refresh_create_character(void)
{
    CREATECHAR_DATA *data = &createchar_data;
    SLONG   body_index, min_sy;

    //刷新動畫指標 --------------------------
    if(timer_tick02 > 5)
    {
        if(data->ani_ptr->next)
            data->ani_ptr = data->ani_ptr->next;
        else
            data->ani_ptr = data->ani_cfa->next;
        timer_tick02 = 0;
    }

    //刷新人物動作 --------------------------
    if(timer_tick03 > 4)
    {
        refresh_ui_npc();
        timer_tick03 = 0;
    }

    //刷新人物介紹文字 ----------------------
    if(timer_tick04 > 3)
    {
        if(data->select_index >= 0)
        {
            body_index = data->select_index;
            min_sy =  - data->max_lines[body_index] * CREATECHAR_TEXT_DY - CREATECHAR_TEXT_DY;
            data->text_start_y --;
            if(data->text_start_y < min_sy)
            {
                data->text_start_y = CREATECHAR_TEXT_BAR_YL + CREATECHAR_TEXT_DY;
            }
        }
        timer_tick04 = 0;
    }
}


void    redraw_create_character(SLONG sx, SLONG sy, void *vbitmap)
{
    CREATECHAR_DATA *data = &createchar_data;
    BMP *bitmap = (BMP*)vbitmap;
    CAKE_FRAME_ANI *cfa;
    CAKE_FRAME  *cf;
    SLONG   frame, x, y, id, event;
    SLONG   index, i, npc_x, npc_y, npc_z;
	SLONG	flag;

    event = CREATECHAR_EVENT;
    game_range.clear();

    //(1) background -------------------------------------------
    frame = CREATECHAR_FRAME_BKGND;
    id = CREATECHAR_ID_BKGND;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

    //(2) ok button ---------------------------------------------
    frame = CREATECHAR_FRAME_OK;
    id = CREATECHAR_ID_OK;
    if(data->active_id == id)
        frame += 2;
    else if(data->hilight_id == id)
        frame += 1;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

    //(5) back button ---------------------------------------------
    frame = CREATECHAR_FRAME_BACK;
    id = CREATECHAR_ID_BACK;
    if(data->active_id == id)
        frame += 2;
    else if(data->hilight_id == id)
        frame += 1;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

    //(7) character body images ----------------------------------------
    update_ui_npc_object();
    for(i=0; i<CREATECHAR_MAX_BODY; i++)
    {
        index = i;

		flag = get_npc_flag(i);

        if(flag)
        {
            ui_redraw_one_npc_object(i, bitmap);
            
            //show selected ani pointer.
			GetCharacterPosition(i, &npc_x, &npc_y, &npc_z);
            if(data->select_index == i)
            {
                cfa = data->ani_ptr;
                x = sx + npc_x - CREATECHAR_BODY_XL/2 + cfa->cake_frame->frame_rx;
                y = sy + npc_y - CREATECHAR_BODY_YL + cfa->cake_frame->frame_ry - 40;
                put_rle(x, y, cfa->cake_frame->rle, bitmap);
            }
            
            game_range.add(npc_x - CREATECHAR_BODY_XL/2, npc_y - CREATECHAR_BODY_YL, 
                CREATECHAR_BODY_XL, CREATECHAR_BODY_YL, 
                event, CREATECHAR_ID_BODY_0 + i);
        }
    }

    //(8) character introduce text -----------------------------------------
    if(data->select_index >= 0)
    {
        SLONG   body_index, text_x, text_y;
        TEXT_LINE_NODE  *node;

        clear_abitmap_image(data->text_abmp);
        x = CREATECHAR_TEXT_BAR_SX;
        y = CREATECHAR_TEXT_BAR_SY;
        get_bitmap(x, y, CREATECHAR_TEXT_BAR_XL, CREATECHAR_TEXT_BAR_YL, (BMP*)data->text_abmp, bitmap);

        body_index = data->select_index;
        text_x = 0;
        text_y = data->text_start_y;

        set_word_color(0, rgb2hi(63, 63, 255));
        for(i = 0; i < data->max_lines[body_index]; i ++)
        {
            if(text_y >= -20 && text_y < CREATECHAR_TEXT_BAR_YL + 4)
            {
                node = get_text_line_node(data->text_lines[body_index], i);
                if(node)
                {
                    print16(text_x, text_y, node->text, PEST_PUT, (BMP*)data->text_abmp);
                }
            }
            text_y += CREATECHAR_TEXT_DY;
        }
        set_word_color(0, SYSTEM_WHITE);

        put_abitmap(x, y, data->text_abmp, bitmap);
    }
}


SLONG   handle_create_character(UINT message, WPARAM wParam, LPARAM lParam)
{
    CREATECHAR_DATA *data = &createchar_data;
    SLONG   mouse_x, mouse_y;
    SLONG   event_type, event_id;
    SLONG   index;
	SLONG	request_index;

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
            case CREATECHAR_ID_OK:
                data->active_id = event_id;
                index = data->select_index;
				request_index = index;	//0~13
                set_new_character_body_index(request_index);
				// Jack, Add for inserting ui here. [1/28/2003]
                //iRet = ClientRequestForDefaultCharacterInfo(request_index);
				set_next_app_state(APPSTATE_INIT_CHG_CHAR_COLOR);
				change_app_state();
                break;
            case CREATECHAR_ID_BACK:
                data->active_id = event_id;
                set_next_app_state(APPSTATE_INIT_SELECT_CHARACTER);
                change_app_state();
                break;
            default:
                if(event_id >= CREATECHAR_ID_BODY_0 && event_id < CREATECHAR_ID_BODY_0 + CREATECHAR_MAX_BODY)
                {
                    SLONG   npc_index;

                    data->active_id = event_id;
                    if(data->select_index != event_id - CREATECHAR_ID_BODY_0)
                    {
                        data->text_start_y = CREATECHAR_TEXT_BAR_YL + CREATECHAR_TEXT_DY;
                    }
                    data->select_index = event_id - CREATECHAR_ID_BODY_0;
                    //
                    npc_index = data->select_index;
                    change_npc_doing(npc_index, DOING_KIND_BECKON, 0, 0, 0, 0, 0, 0);
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

//////////////////////////////////////////////////////////////////////////////////////////////
// SET CHARACTER FACE(設置角色的肖像)                                                       //
//////////////////////////////////////////////////////////////////////////////////////////////
int     init_set_character_face(void)
{
    USTR    filename[_MAX_FNAME];
    SLONG   result, i, frames;
    CAKE_FRAME_ANI  *cfa;

    //main menu images ------------------------------------
    setcharface_data.cfa = NULL;
    for(i=0; i<32; i++)
    {
        setcharface_data.cf[i] = NULL;
    }

    set_data_file(packed_menu_file);
    strcpy((char *)filename, "menu\\install.cak");
    result = load_cake_frame_ani_from_file((USTR*)filename, &setcharface_data.cfa);
    if(TTN_OK != result)
        return  -1;

    frames = count_cake_frames(setcharface_data.cfa);
    for(i=0; i<frames; i++)
    {
        cfa = get_specify_cake_frame_ani(setcharface_data.cfa, i);
        setcharface_data.cf[i] = cfa->cake_frame;
    }
    setcharface_data.hilight_id = 0;
    setcharface_data.active_id = 0;
    setcharface_data.function_id = SETCHARFACE_ID_MAINNAME; //讓輸入光標停留在mainname的位置
    //
//  memset(setcharface_data.mainname, 0x00, 12);
//  memset(setcharface_data.nickname, 0x00, 12);

    setcharface_data.mainname = te_create( SETCHARFACE_MAINNAME_SX, 
                                           SETCHARFACE_MAINNAME_SY, 
                                           SETCHARFACE_MAINNAME_XL, 
                                           SETCHARFACE_MAINNAME_YL, 
                                           32 );
    if ( !setcharface_data.mainname )
        return -2;

    setcharface_data.nickname = te_create( SETCHARFACE_NICKNAME_SX,
                                           SETCHARFACE_NICKNAME_SY,
                                           SETCHARFACE_NICKNAME_XL,
                                           SETCHARFACE_NICKNAME_YL,
                                           32 );
    if ( !setcharface_data.nickname )
        return -3;

    te_set_single_line( setcharface_data.mainname, TRUE );
    te_set_font_size( setcharface_data.mainname, TE_FONT_SIZE_24 );
    te_set_focus( setcharface_data.mainname );
    te_enable_v_scroll( setcharface_data.mainname, TRUE );
    te_set_color( setcharface_data.mainname, rgb2hi(237, 98, 55) );
    te_set_active( setcharface_data.mainname, TRUE );

    te_set_single_line( setcharface_data.nickname, TRUE );
    te_set_font_size( setcharface_data.nickname, TE_FONT_SIZE_24 );
    te_enable_v_scroll( setcharface_data.nickname, TRUE );
    te_set_color( setcharface_data.nickname, rgb2hi(237, 98, 55) );
    te_set_active( setcharface_data.nickname, TRUE );

    //
    setcharface_data.eye_index = 0;
    setcharface_data.mouth_index = 0;
    /*
    setcharface_data.strength = 20;
    setcharface_data.facility = 25;
    setcharface_data.wit = 30;
    setcharface_data.stamina = 20;
    setcharface_data.hp = 50;
    setcharface_data.mp = 30;
    */

    return 0;
}


void    active_set_character_face(int active)
{
    return;
}


void    free_set_character_face(void)
{
    SLONG   i;

    if ( setcharface_data.mainname )
    {
        te_destroy( setcharface_data.mainname );
        setcharface_data.mainname = NULL;
    }
    if ( setcharface_data.nickname )
    {
        te_destroy( setcharface_data.nickname );
        setcharface_data.nickname = NULL;
    }

    if(setcharface_data.cfa)
    {
        destroy_cake_frame_ani(&setcharface_data.cfa);
        for(i=0; i<32; i++)
        {
            setcharface_data.cf[i] = NULL;
        }
    }
    return;
}


void    refresh_set_character_face(void)
{
}


void    redraw_set_character_face(SLONG sx, SLONG sy, void *vbitmap)
{
    BMP *bitmap = (BMP*)vbitmap;
    CAKE_FRAME  *cf;
    SLONG   frame, x, y, id, event; //, xl, yl;
//    SLONG   len;
    USTR    info[64];
    MANFACE_DATA    mf;
    SLONG   career, sex;
    SLONG   manchar_index, eye_index, mouth_index;

    career = get_new_character_career();
    sex = get_new_character_sex();
    manchar_index = get_character_main_face(career, sex);

    event = SETCHARFACE_EVENT;
    game_range.clear();

    //(1) background -------------------------------------------
    frame = SETCHARFACE_FRAME_BKGND;
    id = SETCHARFACE_ID_BKGND;
    cf = setcharface_data.cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);


/*  Zhang Zhaohui 2003.5.15 使用 qqedit 處理輸入

    //(2) main name --------------------------------------------
    id = SETCHARFACE_ID_MAINNAME;
    x = sx + SETCHARFACE_MAINNAME_SX;
    y = sy + SETCHARFACE_MAINNAME_SY;
    xl = SETCHARFACE_MAINNAME_XL;
    yl = SETCHARFACE_MAINNAME_YL;
    game_range.add(x, y, xl, yl, event, id);

    len = strlen((const char *)setcharface_data.mainname);
    if(setcharface_data.function_id == id)
        sprintf((char *)info, "~C3%s_~C0", setcharface_data.mainname);
    else
        sprintf((char *)info, "~C3%s~C0", setcharface_data.mainname);
    set_word_color(3, rgb2hi(237, 98, 55));
    print24(x + 24, y + 4, (USTR*)info, PEST_PUT, bitmap);
    set_word_color(3, rgb2hi(0, 0, 255));

    //(3) nick name --------------------------------------------
    id = SETCHARFACE_ID_NICKNAME;
    x = sx + SETCHARFACE_NICKNAME_SX;
    y = sy + SETCHARFACE_NICKNAME_SY;
    xl = SETCHARFACE_NICKNAME_XL;
    yl = SETCHARFACE_NICKNAME_YL;
    game_range.add(x, y, xl, yl, event, id);

    len = strlen((const char *)setcharface_data.nickname);
    if(setcharface_data.function_id == id)
        sprintf((char *)info, "~C3%s_~C0", setcharface_data.nickname);
    else
        sprintf((char *)info, "~C3%s~C0", setcharface_data.nickname);
    set_word_color(3, rgb2hi(237, 98, 55));
    print24(x + 24, y + 4, (USTR*)info, PEST_PUT, bitmap);
    set_word_color(3, rgb2hi(0, 0, 255));
*/
    // (2, 3) main name, nick name -----------------------------
    redraw_te( setcharface_data.mainname, bitmap );
    redraw_te( setcharface_data.nickname, bitmap );

    //(4) prev eye button --------------------------------------
    frame = SETCHARFACE_FRAME_PREV_EYE;
    id = SETCHARFACE_ID_PREV_EYE;
    if(setcharface_data.active_id == id)
        frame += 2;
    else if(setcharface_data.hilight_id == id)
        frame += 1;
    cf = setcharface_data.cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

    //(5) next eye button --------------------------------------
    frame = SETCHARFACE_FRAME_NEXT_EYE;
    id = SETCHARFACE_ID_NEXT_EYE;
    if(setcharface_data.active_id == id)
        frame += 2;
    else if(setcharface_data.hilight_id == id)
        frame += 1;
    cf = setcharface_data.cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

    //(6) prev mouth button ------------------------------------
    frame = SETCHARFACE_FRAME_PREV_MOUTH;
    id = SETCHARFACE_ID_PREV_MOUTH;
    if(setcharface_data.active_id == id)
        frame += 2;
    else if(setcharface_data.hilight_id == id)
        frame += 1;
    cf = setcharface_data.cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

    //(7) next mouth button ------------------------------------
    frame = SETCHARFACE_FRAME_NEXT_MOUTH;
    id = SETCHARFACE_ID_NEXT_MOUTH;
    if(setcharface_data.active_id == id)
        frame += 2;
    else if(setcharface_data.hilight_id == id)
        frame += 1;
    cf = setcharface_data.cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

    //(8) ok button --------------------------------------------
    frame = SETCHARFACE_FRAME_OK;
    id = SETCHARFACE_ID_OK;
    if(setcharface_data.active_id == id)
        frame += 2;
    else if(setcharface_data.hilight_id == id)
        frame += 1;
    cf = setcharface_data.cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

    //(9) back button ------------------------------------------
    frame = SETCHARFACE_FRAME_BACK;
    id = SETCHARFACE_ID_BACK;
    if(setcharface_data.active_id == id)
        frame += 2;
    else if(setcharface_data.hilight_id == id)
        frame += 1;
    cf = setcharface_data.cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

    //(10) character face --------------------------------------
    eye_index = setcharface_data.eye_index;
    mouth_index = setcharface_data.mouth_index;;
    set_manface(&mf, manchar_index, eye_index, mouth_index);
    redraw_manface(SETCHARFACE_FACE_SX+4, SETCHARFACE_FACE_SY+5, &mf, bitmap);

    //(11) career name -----------------------------------------
    set_word_color(3, rgb2hi(237, 98, 55));
    x = sx + SETCHARFACE_CAREER_SX;
    y = sy + SETCHARFACE_CAREER_SY;
    sprintf((char *)info, "~C3%s~C0", get_career_name(career));
    print24(x + 24, y + 4, (USTR*)info, PEST_PUT, bitmap);

    //(12) strength value --------------------------------------
    x = sx + SETCHARFACE_STRENGTH_SX;
    y = sy + SETCHARFACE_STRENGTH_SY;
    sprintf((char *)info, "~C3%d~C0", get_new_character_strength());
    print24(x + 24, y + 4, (USTR*)info, PEST_PUT, bitmap);

    //(13) instinct value --------------------------------------
    x = sx + SETCHARFACE_FACILITY_SX;
    y = sy + SETCHARFACE_FACILITY_SY;
    sprintf((char *)info, "~C3%d~C0", get_new_character_instinct());
    print24(x + 24, y + 4, (USTR*)info, PEST_PUT, bitmap);

    //(14) wit value -------------------------------------------
    x = sx + SETCHARFACE_WIT_SX;
    y = sy + SETCHARFACE_WIT_SY;
    sprintf((char *)info, "~C3%d~C0", get_new_character_wit());
    print24(x + 24, y + 4, (USTR*)info, PEST_PUT, bitmap);

    //(15) luck value ---------------------------------------
    x = sx + SETCHARFACE_STAMINA_SX;
    y = sy + SETCHARFACE_STAMINA_SY;
    sprintf((char *)info, "~C3%d~C0", get_new_character_luck());
    print24(x + 24, y + 4, (USTR*)info, PEST_PUT, bitmap);

    //(16) hp value --------------------------------------------
    x = sx + SETCHARFACE_HP_SX;
    y = sy + SETCHARFACE_HP_SY;
    sprintf((char *)info, "~C3%d~C0", get_new_character_hp());
    print24(x + 24, y + 4, (USTR*)info, PEST_PUT, bitmap);

    //(17) mp value --------------------------------------------
    x = sx + SETCHARFACE_MP_SX;
    y = sy + SETCHARFACE_MP_SY;
    sprintf((char *)info, "~C3%d~C0", get_new_character_mp());
    print24(x + 24, y + 4, (USTR*)info, PEST_PUT, bitmap);

    set_word_color(3, rgb2hi(0, 0, 255));

//    pos_redraw_ime(bitmap);
}



SLONG   on_select_character_face_ok(void)
{
    int iRet;
    
	if( te_get_size( setcharface_data.mainname ) == 0 )
	{
		display_error_message((USTR*)ERRMSG_PLEASE_INPUT_MAINNAME, DISPLAY_MESSAGE_TO_SCREEN, screen_buffer);
		update_screen(screen_buffer);
		wait_key_time(' ', 80);
		goto _error;
		return	0;
	}

    //set_new_character_mainname((USTR*)setcharface_data.mainname);
    //set_new_character_nickname((USTR*)setcharface_data.nickname);
    set_new_character_mainname( (USTR*)setcharface_data.mainname->ptext_buf );
    set_new_character_nickname( (USTR*)setcharface_data.nickname->ptext_buf );
    set_new_character_eyes_index(setcharface_data.eye_index);
    set_new_character_mouth_index(setcharface_data.mouth_index);
    
	iRet = ClientRequestCreateCharacterChecking((char *)get_new_character_mainname());
    switch(iRet)
    {
    case SEND_MSG_OK:
        break;
    default:
        display_error_message((USTR*)"CREATE CHARACTER FAILED!", DISPLAY_MESSAGE_TO_SCREEN, screen_buffer);
        update_screen(screen_buffer);
        wait_key_time(' ', 80);
        break;
    }
	return	0;

_error:
    return  0;
}



SLONG   handle_set_character_face(UINT message, WPARAM wParam, LPARAM lParam)
{
    static  SLONG   mouse_x, mouse_y;
    SLONG   event_type, event_id;
//    BYTE    kb;
//    SLONG   len, ime_len;

    switch(message)
    {
    case WM_KEYDOWN:
        {
            switch( wParam )
            {
                /*
            case VK_F1:
                next_ime();
                break;
            case VK_F2:
                sharp_ime(g_hDDWnd);
                break;
            case VK_F3:
                symbol_ime(g_hDDWnd);
                break;
            case VK_F5:
                enable_ime();
                break;
            case VK_F6:
                disable_ime();
                break;
                */
/*
            case VK_TAB:

                if(setcharface_data.function_id != SETCHARFACE_ID_MAINNAME)
                {
                    setcharface_data.active_id = SETCHARFACE_ID_MAINNAME;
                    setcharface_data.function_id = SETCHARFACE_ID_MAINNAME;
                }
                else
                {
                    setcharface_data.active_id = SETCHARFACE_ID_NICKNAME;
                    setcharface_data.function_id = SETCHARFACE_ID_NICKNAME;
                }
*/
            case VK_TAB:
                if ( te_get_focus( ) != setcharface_data.mainname )
                {
                    te_force_set_focus( setcharface_data.mainname );
                    setcharface_data.active_id = 0;
                    setcharface_data.function_id = 0;
                }
                else
                {
                    te_force_set_focus( setcharface_data.nickname );
                    setcharface_data.active_id = 0;
                    setcharface_data.function_id = 0;
                }
                break;
            }
        }
        break;
    case WM_MOUSEMOVE:
        mouse_x = GET_X_LPARAM(lParam);
        mouse_y = GET_Y_LPARAM(lParam);
        event_type = event_id = 0;
        game_range.mapping(mouse_x, mouse_y, &event_type, &event_id);
        setcharface_data.hilight_id = event_id;
        break;
    case WM_LBUTTONDOWN:
        {
            mouse_x = GET_X_LPARAM(lParam);
            mouse_y = GET_Y_LPARAM(lParam);
            event_type = event_id = 0;
            game_range.mapping(mouse_x, mouse_y, &event_type, &event_id);
            switch(event_id)
            {
            case SETCHARFACE_ID_OK:
                setcharface_data.active_id = event_id;
                setcharface_data.function_id = event_id;
                on_select_character_face_ok();
                break;
            case SETCHARFACE_ID_BACK:
                setcharface_data.active_id = event_id;
                setcharface_data.function_id = event_id;
                set_next_app_state(APPSTATE_INIT_CREATE_CHARACTER);
                change_app_state();
                break;
/*
            case SETCHARFACE_ID_MAINNAME:
                setcharface_data.active_id = event_id;
                setcharface_data.function_id = event_id;
                break;
            case SETCHARFACE_ID_NICKNAME:
                setcharface_data.active_id = event_id;
                setcharface_data.function_id = event_id;
                break;
*/
            case SETCHARFACE_ID_PREV_EYE:
                setcharface_data.active_id = event_id;
                setcharface_data.function_id = event_id;
                if(setcharface_data.eye_index > 0)
                    setcharface_data.eye_index --;
                break;
            case SETCHARFACE_ID_NEXT_EYE:
                setcharface_data.active_id = event_id;
                setcharface_data.function_id = event_id;
                if(setcharface_data.eye_index < SETCHARFACE_MAX_EYE - 1)
                    setcharface_data.eye_index ++;
                break;
            case SETCHARFACE_ID_PREV_MOUTH:
                setcharface_data.active_id = event_id;
                setcharface_data.function_id = event_id;
                if(setcharface_data.mouth_index > 0)
                    setcharface_data.mouth_index --;
                break;
            case SETCHARFACE_ID_NEXT_MOUTH:
                setcharface_data.active_id = event_id;
                setcharface_data.function_id = event_id;
                if(setcharface_data.mouth_index < SETCHARFACE_MAX_MOUTH - 1)
                    setcharface_data.mouth_index ++;
                break;
            }
        }
        break;
    case WM_LBUTTONUP:
        setcharface_data.active_id = 0;
        break;
/*
    case WM_IME_STRING:
        {
            switch(setcharface_data.function_id)
            {
            case SETCHARFACE_ID_MAINNAME:
                ime_len = strlen((const char *)wParam);
                len = strlen((const char *)setcharface_data.mainname);
                if(ime_len + len <= 16)
                {
                    strcat((char *)setcharface_data.mainname, (const char *)wParam);
                }
                break;
            case SETCHARFACE_ID_NICKNAME:
                ime_len = strlen((const char *)wParam);
                len = strlen((const char *)setcharface_data.nickname);
                if(ime_len + len <= 16)
                {
                    strcat((char *)setcharface_data.nickname, (const char *)wParam);
                }
                break;
            }
        }

        break;
    case WM_CHAR:
        {
            switch(setcharface_data.function_id)
            {
            case SETCHARFACE_ID_MAINNAME:
                switch(wParam)
                {
                case VK_BACK:
                    delete_last_word((char *)setcharface_data.mainname);
                    break;
                default:
                    kb = 0;
                    if((wParam >= '0' && wParam <= '9') || (wParam >= 'A' && wParam <= 'Z')
                        || (wParam >= 'a' && wParam <= 'z') || wParam == '_' )
                        kb = wParam;
                    if(kb)
                    {
                        len = strlen((const char *)setcharface_data.mainname);
                        if(len + 1 <= 16)
                            setcharface_data.mainname[len++] = kb;
                        setcharface_data.mainname[len] = '\0';
                    }
                    break;
                }
                break;
            case SETCHARFACE_ID_NICKNAME:
                switch(wParam)
                {
                case VK_BACK:
                    delete_last_word((char *)setcharface_data.nickname);
                    break;
                default:
                    kb = 0;
                    if((wParam >= '0' && wParam <= '9') || (wParam >= 'A' && wParam <= 'Z')
                        || (wParam >= 'a' && wParam <= 'z') || (wParam == '_' ))
                        kb = wParam;
                    if(kb)
                    {
                        len = strlen((const char *)setcharface_data.nickname);
                        if(len + 1 <= 16)
                            setcharface_data.nickname[len++] = kb;
                        setcharface_data.nickname[len] = '\0';
                    }
                    break;
                }
                break;
            }
        }
*/
        break;
    }
    return  0;
}


//////////////////////////////////////////////////////////////////////////////////////////////
// SET CHARACTER LOCATE(設置角色的出生地)                                                   //
//////////////////////////////////////////////////////////////////////////////////////////////
static  SLONG   local_born_country[16] = 
{   
    COUNTRY_CHINA,      //00 
    COUNTRY_CHINA,      //01 
    COUNTRY_ITALY,      //02 義大利(威尼斯)
    COUNTRY_SPAIN,      //03 西班牙
    COUNTRY_PORTUGAL,   //04 葡萄牙
    COUNTRY_TURKEY,     //05 土耳其(伊斯坦布爾)
    COUNTRY_CHINA,      //06
    COUNTRY_CHINA,      //07
    COUNTRY_CHINA,      //08
    COUNTRY_CHINA,      //09
    COUNTRY_CHINA,      //10
    COUNTRY_CHINA,      //11
    COUNTRY_CHINA,      //12
    COUNTRY_CHINA,      //13
    COUNTRY_CHINA,      //14
    COUNTRY_CHINA       //15
};
// Jack,  [1/29/2003]
//目前支援出生地: 西班牙 和 葡萄牙.
static  SLONG   local_supportted_country[16] = { 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };


int     init_set_character_locate(void)
{
    USTR    filename[_MAX_FNAME];
    SLONG   result, i, frames;
    CAKE_FRAME_ANI  *cfa;
    SETCHARLOCATE_DATA  *data = &setcharlocate_data;
    SLONG   x, y;
    UCHR    alpha;

    //main menu images ------------------------------------
    data->cfa = NULL;
    for(i=0; i<32; i++)
    {
        data->cf[i] = NULL;
    }

    set_data_file(packed_menu_file);
    strcpy((char *)filename, "menu\\birth.cak");
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
    data->select_index = -1;
    data->text_start_y = SETCHARLOCATE_TEXT_BAR_YL + SETCHARLOCATE_TEXT_DY;

    //locate introduce text --------------------------------
    set_data_file(packed_data_file);
    for(i = 0; i<SETCHARLOCATE_MAX_COUNTRY; i++)
    {
        data->text_lines[i] = NULL;
        data->max_lines[i] = 0;

        sprintf((char *)filename, "data\\cntry%02d.txt", i);
        data->text_lines[i] = load_text_file((USTR*)filename);
        if(data->text_lines[i])
        {
            data->max_lines[i] = count_text_line_nodes(data->text_lines[i]);
        }
    }

    //locate text abitmap -----------------------------------
    data->text_abmp = create_abitmap(SETCHARLOCATE_TEXT_BAR_XL, SETCHARLOCATE_TEXT_BAR_YL);
    if(NULL == data->text_abmp)
        return  -2;
    for(y = 0; y < data->text_abmp->h; y ++)
    {
        if(y < 32)
            alpha = (USTR )(y * 8);
        else if(y > data->text_abmp->h - 32)
            alpha = (USTR )((data->text_abmp->h - y) * 8);
        else
            alpha = 255;
        for(x = 0; x < data->text_abmp->w; x++)
        {
            data->text_abmp->line[y][data->text_abmp->w * SIZEOFPIXEL + x] = alpha;
        }
    }
    
    return 0;
}


void    active_set_character_locate(int active)
{
}


void    free_set_character_locate(void)
{
    SETCHARLOCATE_DATA  *data = &setcharlocate_data;
    SLONG   i;

    destroy_cake_frame_ani(&data->cfa);
    for(i=0; i<32; i++)
    {
        data->cf[i] = NULL;
    }

    destroy_abitmap(&data->text_abmp);

    for(i = 0; i<SETCHARLOCATE_MAX_COUNTRY; i++)
    {
        if(data->text_lines[i])
        {
            free_text_line_dlink(data->text_lines[i]);
            data->text_lines[i] = NULL;
            data->max_lines[i] = 0;
        }
    }
}


void    refresh_set_character_locate(void)
{
    SETCHARLOCATE_DATA  *data = &setcharlocate_data;
    SLONG   country_index, min_sy;

    if(timer_tick00 > 3)
    {
        if(data->select_index >= 0)
        {
            country_index = data->select_index;
            min_sy =  - data->max_lines[country_index] * SETCHARLOCATE_TEXT_DY - SETCHARLOCATE_TEXT_DY;
            data->text_start_y --;
            if(data->text_start_y < min_sy)
            {
                data->text_start_y = SETCHARLOCATE_TEXT_BAR_YL + SETCHARLOCATE_TEXT_DY;
            }
        }

        timer_tick00 = 0;
    }
}


void    redraw_set_character_locate(SLONG sx, SLONG sy, void *vbitmap)
{
    BMP *bitmap = (BMP*)vbitmap;
    CAKE_FRAME  *cf;
    SLONG   frame, x, y, id, event;
    SLONG   char_index;
    SETCHARLOCATE_DATA  *data = &setcharlocate_data;
    SLONG   i;

    char_index = selchar_data.select_index;

    event = SETCHARLOCATE_EVENT;
    game_range.clear();

    //(1) background -------------------------------------------
    frame = SETCHARLOCATE_FRAME_BKGND;
    id = SETCHARLOCATE_ID_BKGND;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

    //(2) locates list -----------------------------------------
    for(i = 0; i < SETCHARLOCATE_MAX_COUNTRY; i++)
    {
        // Jack, 過濾掉目前不支持的出生地 [05:33,10/17/2002]
        if(!local_supportted_country[i])
            continue;

        frame = SETCHARLOCATE_FRAME_COUNTRY_0 + i * 3;
        id = SETCHARLOCATE_ID_COUNTRY_0 + i;
        if(data->active_id == id)
            frame += 2;
        else if(data->hilight_id == id)
            frame += 1;
        cf = data->cf[frame];
        x = sx + cf->frame_rx;
        y = sy + cf->frame_ry;
        if(data->select_index == i)
            mask_edge_put_rle(x, y, SYSTEM_YELLOW, cf->rle, bitmap);
        else
            put_rle(x, y, cf->rle, bitmap);
        game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);
    }

    //(3) ok button --------------------------------------------
    if(data->select_index >= 0)
    {
        frame = SETCHARLOCATE_FRAME_OK;
        id = SETCHARLOCATE_ID_OK;
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

    //(4) back button ------------------------------------------
    frame = SETCHARLOCATE_FRAME_BACK;
    id = SETCHARLOCATE_ID_BACK;
    if(data->active_id == id)
        frame += 2;
    else if(data->hilight_id == id)
        frame += 1;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

    //(5) current country introduce ----------------------------
    if(data->select_index >= 0)
    {
        SLONG   country_index, text_x, text_y;
        TEXT_LINE_NODE  *node;

        clear_abitmap_image(data->text_abmp);
        x = SETCHARLOCATE_TEXT_BAR_SX;
        y = SETCHARLOCATE_TEXT_BAR_SY;
        get_bitmap(x, y, SETCHARLOCATE_TEXT_BAR_XL, SETCHARLOCATE_TEXT_BAR_YL, (BMP*)data->text_abmp, bitmap);

        country_index = data->select_index;
        text_x = 0;
        text_y = data->text_start_y;

        set_word_color(0, rgb2hi(63, 63, 255));
        for(i = 0; i < data->max_lines[country_index]; i ++)
        {
            if(text_y >= -20 && text_y < SETCHARLOCATE_TEXT_BAR_YL + 4)
            {
                node = get_text_line_node(data->text_lines[country_index], i);
                if(node)
                {
                    print16(text_x, text_y, node->text, PEST_PUT, (BMP*)data->text_abmp);
                }
            }
            text_y += 20;
        }
        set_word_color(0, SYSTEM_WHITE);

        put_abitmap(x, y, data->text_abmp, bitmap);
    }
}


SLONG   on_select_character_locate_ok(SLONG index)
{
	TPOS_EVENT_CREATECHARACTERFINAL	request;
	SLONG	i;
    int iRet;

    set_new_character_country(local_born_country[index]);

	request.dwCharacterDefaultIndex = get_new_character_body_index(); //所選的職業角色, 0~41.
	request.dwIndex = get_new_character_index();	//此帳號的第幾個角色, 0~3
	strcpy((char *)request.cMainName, (const char *)get_new_character_mainname());	//名稱
	strcpy((char *)request.cNickName, (const char *)get_new_character_nickname());	//暱稱
	request.Color = 0;			//顏色
	request.Eyes = (CHAR)(get_new_character_eyes_index());			//眼睛
	request.Mouth = (CHAR)(get_new_character_mouth_index());	//嘴
	request.Country = (CHAR)get_new_character_country();		//所屬國家
	for(i=0; i<7; i++)
	{
		request.PartRGB[i] = get_new_character_part_color(i);
	}
	iRet = ClientRequestCreateCharacterFinal(&request);
    switch(iRet)
    {
    case SEND_MSG_OK:
        break;
    default:
        display_error_message((USTR*)"CREATE CHARACTER FAILED!", DISPLAY_MESSAGE_TO_SCREEN, screen_buffer);
        update_screen(screen_buffer);
        wait_key_time(' ', 80);
        break;
    }
    return  0;
}


SLONG   handle_set_character_locate(UINT message, WPARAM wParam, LPARAM lParam)
{
    SLONG   mouse_x, mouse_y;
    SLONG   event_type, event_id;
    SETCHARLOCATE_DATA  *data = &setcharlocate_data;

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
            case SETCHARLOCATE_ID_OK:
                data->active_id = event_id;
                if(data->select_index >= 0)
                {
                    on_select_character_locate_ok(data->select_index);
                }
                break;
            case SETCHARLOCATE_ID_BACK:
                data->active_id = event_id;
                set_next_app_state(APPSTATE_INIT_SET_CHAR_FACE);
                change_app_state();
                break;
            default:
                if(event_id >= SETCHARLOCATE_ID_COUNTRY_0 
                    && event_id < SETCHARLOCATE_ID_COUNTRY_0 + SETCHARLOCATE_MAX_COUNTRY)
                {
                    data->active_id = event_id;
                    if(data->select_index != event_id - SETCHARLOCATE_ID_COUNTRY_0)
                    {
                        data->text_start_y = SETCHARLOCATE_TEXT_BAR_YL + SETCHARLOCATE_TEXT_DY;
                    }
                    data->select_index = event_id - SETCHARLOCATE_ID_COUNTRY_0;
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


/************************************************************************************************************/
/* UI CHANGE CHARACTER COLOR                                                                                */
/************************************************************************************************************/
int		init_change_character_color(void)
{
	CHGCHARCOLOR_DATA	*data = &chgcharcolor_data;
	CAKE_FRAME_ANI	*cfa = NULL;
	CAKE_FRAME	*cf = NULL;
    USTR    filename[_MAX_FNAME];
    SLONG   result, body_index, style_index;
	SLONG	frames;
	SLONG	i;

    //main menu images ------------------------------------
    data->cfa = NULL;

    set_data_file(packed_menu_file);
    strcpy((char *)filename, "menu\\changecl.cak");
    result = load_cake_frame_ani_from_file((USTR*)filename, &data->cfa);
    if(TTN_OK != result)
        return  -1;
    frames = count_cake_frames(data->cfa);
    for(i=0; i<frames; i++)
    {
        cfa = get_specify_cake_frame_ani(data->cfa, i);
        data->cf[i] = cfa->cake_frame;
    }

	body_index = get_new_character_body_index();
	style_index = 0;

    //使用遊戲中NPC的數據結構, 將待選影像作為NPC來對待 -----------------------------------
    //MAX_GAME_MANCHAR = CREATECHAR_MAX_BODY
    //設置NPC的數據資料-------------
	LOCK_CHARACTER(0);
    clear_all_map_npc();
	InitAllZoneCharacters();
	SetCharacterFileIndex(0, manchar_set[body_index].file_index[style_index]);
	SetCharacterImageID(0, INVALID_OBJECT_ID);
	SetCharacterDirFrame(0, 0);
	SetCharacterMoveSpeed(0, 8);
	SetCharacterPosition(0, 164, 326, 0);
	SetCharacterDir(0, NPC_DOWN);
	SetCharacterOnFightState(0, true);
	SetCharacterDoingKindStep(0, DOING_KIND_IDLE, 0);
	SetCharacterOnFightState(0, false);
	set_npc_ext_id(0, INVALID_OBJECT_ID);
	active_map_npc(0);
	UNLOCK_CHARACTER(0);

    //通過刷新一次以載入NPC的影像資料
    refresh_ui_npc();
    update_ui_npc_object();

    cf = data->cf[CHGCHARCOLOR_FRAME_R_SCROLL_BAR];
    data->min_scroll_x = CHGCHARCOLOR_R_SCROLL_BKGND_SX + cf->rle->w / 2;
    data->max_scroll_x = CHGCHARCOLOR_R_SCROLL_BKGND_SX + CHGCHARCOLOR_R_SCROLL_BKGND_XL - cf->rle->w / 2;

    data->hilight_id = 0;
    data->active_id = 0;
	data->is_setting_rgb = 0;
	data->set_part_index = 0;
	data->suit_index = 0;
	for(i=0; i<7; i++)
	{
		data->color_index[i] = -1;
		data->rgb_data[i][0] = 128;	//128 for no change, 0~127 for dec color value, 129~255 for add color value.
		data->rgb_data[i][1] = 128;
		data->rgb_data[i][2] = 128;
		data->scroll_r_pos[i] = (data->min_scroll_x + data->max_scroll_x) / 2;
		data->scroll_g_pos[i] = (data->min_scroll_x + data->max_scroll_x) / 2;
		data->scroll_b_pos[i] = (data->min_scroll_x + data->max_scroll_x) / 2;
		data->scroll_a_pos[i] = (data->min_scroll_x + data->max_scroll_x) / 2;
	}

	data->set_r = 128;
	data->set_g = 128;
	data->set_b = 128;
	data->set_a = 128;
	data->set_a_last = 0;

    return 0;
}

void	active_change_character_color(int active)
{
}

void	free_change_character_color(void)
{
	CHGCHARCOLOR_DATA	*data = &chgcharcolor_data;

	destroy_cake_frame_ani(&data->cfa);

    //釋放角色選擇圖(角色戰鬥待機圖) --------------------
    free_ui_npc_object();
    clear_all_map_npc();
}

void	refresh_change_character_color(void)
{
    //刷新人物動作 --------------------------
    if(timer_tick03 > 4)
    {
        refresh_ui_npc();
        timer_tick03 = 0;
    }
}

void	redraw_change_character_color(SLONG sx, SLONG sy, void *vbitmap)
{
    CHGCHARCOLOR_DATA *data = &chgcharcolor_data;
    BMP *bitmap = (BMP*)vbitmap;
    //CAKE_FRAME_ANI *cfa;
    CAKE_FRAME  *cf;
    SLONG   frame, x, y, xl, yl, id, event;
    //SLONG   index, i, npc_x, npc_y;
	//SLONG	npc_z;
	//SLONG	flag;
	SLONG	part_index, i;
	SLONG	body_index;
	UCHR	r, g, b;
	PIXEL	color;
	SLONG	grid_sx, grid_sy;

	body_index = get_new_character_body_index();

    event = CHGCHARCOLOR_EVENT;
    game_range.clear();

    //(1) background -------------------------------------------
    frame = CHGCHARCOLOR_FRAME_BKGND;
    id = CHGCHARCOLOR_ID_BKGND;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

	//(2) character body image ----------------------------------
    update_ui_npc_object();
	ui_redraw_one_npc_object(0, bitmap);

	//(3) turn left --------------------------------------------
    frame = CHGCHARCOLOR_FRAME_TURN_LEFT;
    id = CHGCHARCOLOR_ID_TURN_LEFT;
    if(data->active_id == id)
        frame += 2;
    else if(data->hilight_id == id)
        frame += 1;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

	//(4) turn right -------------------------------------------
    frame = CHGCHARCOLOR_FRAME_TURN_RIGHT;
    id = CHGCHARCOLOR_ID_TURN_RIGHT;
    if(data->active_id == id)
        frame += 2;
    else if(data->hilight_id == id)
        frame += 1;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

	//(5) a style -----------------------------------------------
    frame = CHGCHARCOLOR_FRAME_A_STYLE;
    id = CHGCHARCOLOR_ID_A_STYLE;
    if(data->active_id == id)
        frame += 2;
    else if(data->hilight_id == id)
        frame += 1;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
	if(data->is_setting_rgb)
	{
		gray_put_rle(x, y, cf->rle, bitmap);
	}
	else
	{
		put_rle(x, y, cf->rle, bitmap);
		game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);
	}

	//(6) b style -----------------------------------------------
    frame = CHGCHARCOLOR_FRAME_B_STYLE;
    id = CHGCHARCOLOR_ID_B_STYLE;
    if(data->active_id == id)
        frame += 2;
    else if(data->hilight_id == id)
        frame += 1;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
	if(data->is_setting_rgb)
	{
		gray_put_rle(x, y, cf->rle, bitmap);
	}
	else
	{
		put_rle(x, y, cf->rle, bitmap);
		game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);
	}

	//(7) c style -----------------------------------------------
    frame = CHGCHARCOLOR_FRAME_C_STYLE;
    id = CHGCHARCOLOR_ID_C_STYLE;
    if(data->active_id == id)
        frame += 2;
    else if(data->hilight_id == id)
        frame += 1;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
	if(data->is_setting_rgb)
	{
		gray_put_rle(x, y, cf->rle, bitmap);
	}
	else
	{
		put_rle(x, y, cf->rle, bitmap);
		game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);
	}

	// (8) colors about ------------------------------------------
	if(!data->is_setting_rgb)
	{
		//(a) colors grid grids & background ---
		grid_sy = CHGCHARCOLOR_COLOR_GRID_SY;
		for(part_index = 0; part_index < 7; part_index ++)
		{
			if(char_color_set[body_index].part_flag[part_index])
			{
				// default set colors
				grid_sx = CHGCHARCOLOR_COLOR_GRID_SX;
				for(i=0; i<3; i++)
				{
					r = oper_and_color(char_color_set[body_index].init_rgb[part_index][0],
						char_color_set[body_index].and_rgb[i][part_index][0]);
					g = oper_and_color(char_color_set[body_index].init_rgb[part_index][1], 
						char_color_set[body_index].and_rgb[i][part_index][1]);
					b = oper_and_color(char_color_set[body_index].init_rgb[part_index][2],
						char_color_set[body_index].and_rgb[i][part_index][2]);

					color = rgb2hi(r, g, b);
					put_bar(grid_sx, grid_sy, CHGCHARCOLOR_COLOR_GRID_XL, CHGCHARCOLOR_COLOR_GRID_YL, color, bitmap);
					game_range.add(grid_sx, grid_sy, CHGCHARCOLOR_COLOR_GRID_XL, CHGCHARCOLOR_COLOR_GRID_YL,
						event, CHGCHARCOLOR_ID_GRID_COLOR + part_index * 4 + i);
					if(data->color_index[part_index] == i)
					{
						put_box(grid_sx - 6, grid_sy - 6, CHGCHARCOLOR_COLOR_GRID_XL + 12, CHGCHARCOLOR_COLOR_GRID_YL + 12,
							SYSTEM_BLACK, bitmap);
						put_box(grid_sx - 5, grid_sy - 5, CHGCHARCOLOR_COLOR_GRID_XL + 10, CHGCHARCOLOR_COLOR_GRID_YL + 10,
							SYSTEM_WHITE, bitmap);
						put_box(grid_sx - 4, grid_sy - 4, CHGCHARCOLOR_COLOR_GRID_XL + 8, CHGCHARCOLOR_COLOR_GRID_YL + 8,
							SYSTEM_BLACK, bitmap);
					}
					
					grid_sx += CHGCHARCOLOR_COLOR_GRID_DX;
				}

				// user set area's colors
				grid_sx = CHGCHARCOLOR_COLOR_USER_SX;

				r = oper_and_color(char_color_set[body_index].init_rgb[part_index][0], data->rgb_data[part_index][0]);
				g = oper_and_color(char_color_set[body_index].init_rgb[part_index][1], data->rgb_data[part_index][1]);
				b = oper_and_color(char_color_set[body_index].init_rgb[part_index][2], data->rgb_data[part_index][2]);

				color = rgb2hi(r, g, b);
				put_bar(grid_sx, grid_sy, CHGCHARCOLOR_COLOR_GRID_XL, CHGCHARCOLOR_COLOR_GRID_YL, color, bitmap);
				game_range.add(grid_sx, grid_sy, CHGCHARCOLOR_COLOR_GRID_XL, CHGCHARCOLOR_COLOR_GRID_YL,
					event, CHGCHARCOLOR_ID_GRID_COLOR + part_index * 4 + 3);
				if(data->color_index[part_index] == 3)
				{
					put_box(grid_sx - 6, grid_sy - 6, CHGCHARCOLOR_COLOR_GRID_XL + 12, CHGCHARCOLOR_COLOR_GRID_YL + 12,
						SYSTEM_BLACK, bitmap);
					put_box(grid_sx - 5, grid_sy - 5, CHGCHARCOLOR_COLOR_GRID_XL + 10, CHGCHARCOLOR_COLOR_GRID_YL + 10,
						SYSTEM_WHITE, bitmap);
					put_box(grid_sx - 4, grid_sy - 4, CHGCHARCOLOR_COLOR_GRID_XL + 8, CHGCHARCOLOR_COLOR_GRID_YL + 8,
						SYSTEM_BLACK, bitmap);
				}
			}
			grid_sy += CHGCHARCOLOR_COLOR_GRID_DY;
		}

		// grid background mask ---
		frame = CHGCHARCOLOR_FRAME_COLOR_GRID;
		cf = data->cf[frame];
		x = sx + cf->frame_rx;
		y = sy + cf->frame_ry;
		put_rle(x, y, cf->rle, bitmap);

		//(b) set my cap ------
		frame = CHGCHARCOLOR_FRAME_SET_MY_CAP;
		id = CHGCHARCOLOR_ID_SET_MY_CAP;
		if(data->active_id == id)
			frame += 2;
		else if(data->hilight_id == id)
			frame += 1;
		cf = data->cf[frame];
		x = sx + cf->frame_rx;
		y = sy + cf->frame_ry;
		if(char_color_set[body_index].part_flag[0])
		{
			put_rle(x, y, cf->rle, bitmap);
			game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);
		}
		else
		{
			gray_put_rle(x, y, cf->rle, bitmap);
		}

		//(c) set my hair ------
		frame = CHGCHARCOLOR_FRAME_SET_MY_HAIR;
		id = CHGCHARCOLOR_ID_SET_MY_HAIR;
		if(data->active_id == id)
			frame += 2;
		else if(data->hilight_id == id)
			frame += 1;
		cf = data->cf[frame];
		x = sx + cf->frame_rx;
		y = sy + cf->frame_ry;
		if(char_color_set[body_index].part_flag[1])
		{
			put_rle(x, y, cf->rle, bitmap);
			game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);
		}
		else
		{
			gray_put_rle(x, y, cf->rle, bitmap);
		}


		//(d) set my skin ------
		frame = CHGCHARCOLOR_FRAME_SET_MY_SKIN;
		id = CHGCHARCOLOR_ID_SET_MY_SKIN;
		if(data->active_id == id)
			frame += 2;
		else if(data->hilight_id == id)
			frame += 1;
		cf = data->cf[frame];
		x = sx + cf->frame_rx;
		y = sy + cf->frame_ry;
		if(char_color_set[body_index].part_flag[2])
		{
			put_rle(x, y, cf->rle, bitmap);
			game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);
		}
		else
		{
			gray_put_rle(x, y, cf->rle, bitmap);
		}


		//(e) set my cloth ------
		frame = CHGCHARCOLOR_FRAME_SET_MY_CLOTH;
		id = CHGCHARCOLOR_ID_SET_MY_CLOTH;
		if(data->active_id == id)
			frame += 2;
		else if(data->hilight_id == id)
			frame += 1;
		cf = data->cf[frame];
		x = sx + cf->frame_rx;
		y = sy + cf->frame_ry;
		if(char_color_set[body_index].part_flag[3])
		{
			put_rle(x, y, cf->rle, bitmap);
			game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);
		}
		else
		{
			gray_put_rle(x, y, cf->rle, bitmap);
		}


		//(f) set my glove ------
		frame = CHGCHARCOLOR_FRAME_SET_MY_GLOVE;
		id = CHGCHARCOLOR_ID_SET_MY_GLOVE;
		if(data->active_id == id)
			frame += 2;
		else if(data->hilight_id == id)
			frame += 1;
		cf = data->cf[frame];
		x = sx + cf->frame_rx;
		y = sy + cf->frame_ry;
		if(char_color_set[body_index].part_flag[4])
		{
			put_rle(x, y, cf->rle, bitmap);
			game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);
		}
		else
		{
			gray_put_rle(x, y, cf->rle, bitmap);
		}


		//(g) set my shoes ------
		frame = CHGCHARCOLOR_FRAME_SET_MY_SHOES;
		id = CHGCHARCOLOR_ID_SET_MY_SHOES;
		if(data->active_id == id)
			frame += 2;
		else if(data->hilight_id == id)
			frame += 1;
		cf = data->cf[frame];
		x = sx + cf->frame_rx;
		y = sy + cf->frame_ry;
		if(char_color_set[body_index].part_flag[5])
		{
			put_rle(x, y, cf->rle, bitmap);
			game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);
		}
		else
		{
			gray_put_rle(x, y, cf->rle, bitmap);
		}

	}
	else
	{
		part_index = data->set_part_index;

		//(a) color rgb background -----
		frame = CHGCHARCOLOR_FRAME_RGB_BKGND;
		cf = data->cf[frame];
		x = sx + cf->frame_rx;
		y = sy + cf->frame_ry;
		put_rle(x, y, cf->rle, bitmap);

		//(b) r scroll bar -------------
		id = CHGCHARCOLOR_ID_R_SCROLL_BKGND;
		x = sx + CHGCHARCOLOR_R_SCROLL_BKGND_SX;
		y = sy + CHGCHARCOLOR_R_SCROLL_BKGND_SY;
		xl = CHGCHARCOLOR_R_SCROLL_BKGND_XL;
		yl = CHGCHARCOLOR_R_SCROLL_BKGND_YL;
		game_range.add(x, y, xl, yl, event, id);

		frame = CHGCHARCOLOR_FRAME_R_SCROLL_BAR;
		id = CHGCHARCOLOR_ID_R_SCROLL_BAR;
		if(data->hilight_id == id)
			frame += 1;
		cf = data->cf[frame];
		x = sx + data->scroll_r_pos[part_index] - cf->rle->w / 2;
		y = sy + cf->frame_ry;
		put_rle(x, y, cf->rle, bitmap);
		game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

		//(c) g scroll bar -------------
		id = CHGCHARCOLOR_ID_G_SCROLL_BKGND;
		x = sx + CHGCHARCOLOR_G_SCROLL_BKGND_SX;
		y = sy + CHGCHARCOLOR_G_SCROLL_BKGND_SY;
		xl = CHGCHARCOLOR_G_SCROLL_BKGND_XL;
		yl = CHGCHARCOLOR_G_SCROLL_BKGND_YL;
		game_range.add(x, y, xl, yl, event, id);

		frame = CHGCHARCOLOR_FRAME_G_SCROLL_BAR;
		id = CHGCHARCOLOR_ID_G_SCROLL_BAR;
		if(data->hilight_id == id)
			frame += 1;
		cf = data->cf[frame];
		x = sx + data->scroll_g_pos[part_index] - cf->rle->w / 2;
		y = sy + cf->frame_ry;
		put_rle(x, y, cf->rle, bitmap);
		game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

		//(d) b scroll bar -------------
		id = CHGCHARCOLOR_ID_B_SCROLL_BKGND;
		x = sx + CHGCHARCOLOR_B_SCROLL_BKGND_SX;
		y = sy + CHGCHARCOLOR_B_SCROLL_BKGND_SY;
		xl = CHGCHARCOLOR_B_SCROLL_BKGND_XL;
		yl = CHGCHARCOLOR_B_SCROLL_BKGND_YL;
		game_range.add(x, y, xl, yl, event, id);

		frame = CHGCHARCOLOR_FRAME_B_SCROLL_BAR;
		id = CHGCHARCOLOR_ID_B_SCROLL_BAR;
		if(data->hilight_id == id)
			frame += 1;
		cf = data->cf[frame];
		x = sx + data->scroll_b_pos[part_index] - cf->rle->w / 2;
		y = sy + cf->frame_ry;
		put_rle(x, y, cf->rle, bitmap);
		game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

		//(e) all scroll bar -----------
		id = CHGCHARCOLOR_ID_ALL_SCROLL_BKGND;
		x = sx + CHGCHARCOLOR_ALL_SCROLL_BKGND_SX;
		y = sy + CHGCHARCOLOR_ALL_SCROLL_BKGND_SY;
		xl = CHGCHARCOLOR_ALL_SCROLL_BKGND_XL;
		yl = CHGCHARCOLOR_ALL_SCROLL_BKGND_YL;
		game_range.add(x, y, xl, yl, event, id);

		frame = CHGCHARCOLOR_FRAME_ALL_SCROLL_BAR;
		id = CHGCHARCOLOR_ID_ALL_SCROLL_BAR;
		if(data->hilight_id == id)
			frame += 1;
		cf = data->cf[frame];
		x = sx + data->scroll_a_pos[part_index] - cf->rle->w / 2;
		y = sy + cf->frame_ry;
		put_rle(x, y, cf->rle, bitmap);
		game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

		//(f) rgb final ----------------
		frame = CHGCHARCOLOR_FRAME_RGB_OK;
		id = CHGCHARCOLOR_ID_RGB_OK;
		if(data->active_id == id)
			frame += 2;
		else if(data->hilight_id == id)
			frame += 1;
		cf = data->cf[frame];
		x = sx + cf->frame_rx;
		y = sy + cf->frame_ry;
		put_rle(x, y, cf->rle, bitmap);
		game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

		//(g) rgb cancel ---------------
		frame = CHGCHARCOLOR_FRAME_RGB_CANCEL;
		id = CHGCHARCOLOR_ID_RGB_CANCEL;
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

	// final ok -----------------------------------------------
	frame = CHGCHARCOLOR_FRAME_FINAL_OK;
	id = CHGCHARCOLOR_ID_FINAL_OK;
	if(data->active_id == id)
		frame += 2;
	else if(data->hilight_id == id)
		frame += 1;
	cf = data->cf[frame];
	x = sx + cf->frame_rx;
	y = sy + cf->frame_ry;
	if(data->is_setting_rgb)
	{
		gray_put_rle(x, y, cf->rle, bitmap);
	}
	else
	{
		put_rle(x, y, cf->rle, bitmap);
		game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);
	}
	
	// final cancel ------------------------------------------
	frame = CHGCHARCOLOR_FRAME_FINAL_CANCEL;
	id = CHGCHARCOLOR_ID_FINAL_CANCEL;
	if(data->active_id == id)
		frame += 2;
	else if(data->hilight_id == id)
		frame += 1;
	cf = data->cf[frame];
	x = sx + cf->frame_rx;
	y = sy + cf->frame_ry;
	if(data->is_setting_rgb)
	{
		gray_put_rle(x, y, cf->rle, bitmap);
	}
	else
	{
		put_rle(x, y, cf->rle, bitmap);
		game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);
	}
}

void	update_changed_character_color(void)
{
    CHGCHARCOLOR_DATA *data = &chgcharcolor_data;
	SLONG	body_index, color_index, suit_index;
	ARGB_DATA	argb_data;
	SLONG	i;
	UCHR	npc_colors[35];

	body_index = get_new_character_body_index();
	suit_index = data->suit_index;
	for(i=0; i<7; i++)
	{
		argb_data.u4 = 0x00000000;
		if(char_color_set[body_index].part_flag[i])
		{
			color_index = data->color_index[i];
			switch(color_index)
			{
			case 0:
			case 1:
			case 2:
				argb_data.r = char_color_set[body_index].and_rgb[color_index][i][0];
				argb_data.g = char_color_set[body_index].and_rgb[color_index][i][1];
				argb_data.b = char_color_set[body_index].and_rgb[color_index][i][2];
				argb_data.a = RGB_EFFECT_AND;
				break;
			case 3:
				argb_data.r = (UCHR)data->rgb_data[i][0];
				argb_data.g = (UCHR)data->rgb_data[i][1];
				argb_data.b = (UCHR)data->rgb_data[i][2];
				argb_data.a = RGB_EFFECT_AND;
				break;
			default:
				argb_data.r = char_color_set[body_index].suit_rgb[suit_index][i][0];
				argb_data.g = char_color_set[body_index].suit_rgb[suit_index][i][1];
				argb_data.b = char_color_set[body_index].suit_rgb[suit_index][i][2];
				argb_data.a = char_color_set[body_index].suit_rgb[suit_index][i][3];
				break;
			}
		}
		SetCharacterPartRGB(0, i, argb_data.u4);
		
		npc_colors[i * 5 + 0] = argb_data.a;
		npc_colors[i * 5 + 1] = argb_data.r;
		npc_colors[i * 5 + 2] = argb_data.g;
		npc_colors[i * 5 + 3] = argb_data.b;
		npc_colors[i * 5 + 4] = 0;
		set_npc_rgb_scroll(0, (UCHR*)npc_colors);
	}
}


SLONG	handle_change_character_color(UINT message, WPARAM wParam, LPARAM lParam)
{
    CHGCHARCOLOR_DATA *data = &chgcharcolor_data;
    SLONG   mouse_x, mouse_y;
    SLONG   event_type, event_id;
	SLONG	request_index;
    int     iRet;
	SLONG	dir;
	SLONG	scroll_a_pos;
	SLONG	scroll_a_dist;
	SLONG	body_index, part_index, index;
	SLONG	i;
	ULONG	part_color;

    switch(message)
    {
    case WM_MOUSEMOVE:
        mouse_x = GET_X_LPARAM(lParam);
        mouse_y = GET_Y_LPARAM(lParam);
        event_type = event_id = 0;
        game_range.mapping(mouse_x, mouse_y, &event_type, &event_id);
        data->hilight_id = event_id;
        if(wParam & MK_LBUTTON) //Drag
        {
			switch(data->mouse_event)
			{
			case MOUSE_EVENT_R_SCROLL:
				part_index = data->set_part_index;
				data->scroll_r_pos[part_index] = CLAMP(mouse_x, data->min_scroll_x, data->max_scroll_x);
				data->set_r = (data->scroll_r_pos[part_index] - data->min_scroll_x) * 256 / (data->max_scroll_x - data->min_scroll_x);
				data->set_r = CLAMP(data->set_r, 0, 255);
				data->rgb_data[part_index][0] = (UCHR)data->set_r;
				update_changed_character_color();
				break;
			case MOUSE_EVENT_G_SCROLL:
				part_index = data->set_part_index;
				data->scroll_g_pos[part_index] = CLAMP(mouse_x, data->min_scroll_x, data->max_scroll_x);
				data->set_g = (data->scroll_g_pos[part_index] - data->min_scroll_x) * 256 / (data->max_scroll_x - data->min_scroll_x);
				data->set_g = CLAMP(data->set_g, 0, 255);
				data->rgb_data[part_index][1] = (UCHR)data->set_g;
				update_changed_character_color();
				break;

			case MOUSE_EVENT_B_SCROLL:
				part_index = data->set_part_index;
				data->scroll_b_pos[part_index] = CLAMP(mouse_x, data->min_scroll_x, data->max_scroll_x);
				data->set_b = (data->scroll_b_pos[part_index] - data->min_scroll_x) * 256 / (data->max_scroll_x - data->min_scroll_x);
				data->set_b = CLAMP(data->set_b, 0, 255);
				data->rgb_data[part_index][2] = (UCHR)data->set_b;
				update_changed_character_color();
				break;

			case MOUSE_EVENT_A_SCROLL:
				part_index = data->set_part_index;
				scroll_a_pos = CLAMP(mouse_x, data->min_scroll_x, data->max_scroll_x);
				scroll_a_dist = scroll_a_pos - data->scroll_a_pos[part_index];
				data->scroll_r_pos[part_index] = CLAMP(data->scroll_r_pos[part_index] + scroll_a_dist, data->min_scroll_x, data->max_scroll_x);
				data->scroll_g_pos[part_index] = CLAMP(data->scroll_g_pos[part_index] + scroll_a_dist, data->min_scroll_x, data->max_scroll_x);
				data->scroll_b_pos[part_index] = CLAMP(data->scroll_b_pos[part_index] + scroll_a_dist, data->min_scroll_x, data->max_scroll_x);
				data->set_r = (data->scroll_r_pos[part_index] - data->min_scroll_x) * 256 / (data->max_scroll_x - data->min_scroll_x);
				data->set_r = CLAMP(data->set_r, 0, 255);
				data->rgb_data[part_index][0] = (UCHR)data->set_r;
				data->set_g = (data->scroll_g_pos[part_index] - data->min_scroll_x) * 256 / (data->max_scroll_x - data->min_scroll_x);
				data->set_g = CLAMP(data->set_g, 0, 255);
				data->rgb_data[part_index][1] = (UCHR)data->set_g;
				data->set_b = (data->scroll_g_pos[part_index] - data->min_scroll_x) * 256 / (data->max_scroll_x - data->min_scroll_x);
				data->set_b = CLAMP(data->set_b, 0, 255);
				data->rgb_data[part_index][2] = (UCHR)data->set_b;
                data->scroll_a_pos[part_index] = scroll_a_pos;
				data->set_a = (data->scroll_a_pos[part_index] - data->min_scroll_x) * 256 / (data->max_scroll_x - data->min_scroll_x);
				data->set_a = CLAMP(data->set_a, 0, 255);
				update_changed_character_color();
				break;
			}
        }
        break;
    case WM_LBUTTONDOWN:
        {
            mouse_x = GET_X_LPARAM(lParam);
            mouse_y = GET_Y_LPARAM(lParam);
            event_type = event_id = 0;
            game_range.mapping(mouse_x, mouse_y, &event_type, &event_id);
            data->mouse_event = 0;
            switch(event_id)
            {
			case CHGCHARCOLOR_ID_TURN_LEFT:
                data->active_id = event_id;
				dir = GetCharacterDir(0);
				dir = ClockwiseLoopCharacterDir(dir);
				SetCharacterDir(0, dir);
                DirHeadCharacterFrame(0);
				break;

			case CHGCHARCOLOR_ID_TURN_RIGHT:
                data->active_id = event_id;
				dir = GetCharacterDir(0);
				dir = AntiClockwiseLoopCharacterDir(dir);
				SetCharacterDir(0, dir);
                DirHeadCharacterFrame(0);
				break;

			case CHGCHARCOLOR_ID_A_STYLE:
                data->active_id = event_id;
				body_index = get_new_character_body_index();
				data->suit_index = 0;
				for(i=0; i<7; i++)
				{
					data->color_index[i] = -1;
				}
				update_changed_character_color();
				break;

			case CHGCHARCOLOR_ID_B_STYLE:
                data->active_id = event_id;
				body_index = get_new_character_body_index();
				data->suit_index = 1;
				for(i=0; i<7; i++)
				{
					data->color_index[i] = -1;
				}
				update_changed_character_color();
				break;

			case CHGCHARCOLOR_ID_C_STYLE:
                data->active_id = event_id;
				body_index = get_new_character_body_index();
				data->suit_index = 2;
				for(i=0; i<7; i++)
				{
					data->color_index[i] = -1;
				}
				update_changed_character_color();
				break;

			case CHGCHARCOLOR_ID_SET_MY_CAP:
                data->active_id = event_id;
				data->set_part_index = 0;
				data->color_index[0] = 3;
				data->is_setting_rgb = true;
				data->set_r = data->rgb_data[0][0];
				data->scroll_r_pos[0] = data->min_scroll_x + data->set_r * (data->max_scroll_x - data->min_scroll_x) / 256;
				data->set_g = data->rgb_data[0][1];
				data->scroll_g_pos[0] = data->min_scroll_x + data->set_g * (data->max_scroll_x - data->min_scroll_x) / 256;
				data->set_b = data->rgb_data[0][2];
				data->scroll_b_pos[0] = data->min_scroll_x + data->set_b * (data->max_scroll_x - data->min_scroll_x) / 256;
				break;

			case CHGCHARCOLOR_ID_SET_MY_HAIR:
                data->active_id = event_id;
				data->set_part_index = 1;
				data->color_index[1] = 3;
				data->is_setting_rgb = true;
				data->set_r = data->rgb_data[1][0];
				data->scroll_r_pos[1] = data->min_scroll_x + data->set_r * (data->max_scroll_x - data->min_scroll_x) / 256;
				data->set_g = data->rgb_data[1][1];
				data->scroll_g_pos[1] = data->min_scroll_x + data->set_g * (data->max_scroll_x - data->min_scroll_x) / 256;
				data->set_b = data->rgb_data[1][2];
				data->scroll_b_pos[1] = data->min_scroll_x + data->set_b * (data->max_scroll_x - data->min_scroll_x) / 256;
				break;

			case CHGCHARCOLOR_ID_SET_MY_SKIN:
                data->active_id = event_id;
				data->set_part_index = 2;
				data->color_index[2] = 3;
				data->is_setting_rgb = true;
				data->set_r = data->rgb_data[2][0];
				data->scroll_r_pos[2] = data->min_scroll_x + data->set_r * (data->max_scroll_x - data->min_scroll_x) / 256;
				data->set_g = data->rgb_data[2][1];
				data->scroll_g_pos[2] = data->min_scroll_x + data->set_g * (data->max_scroll_x - data->min_scroll_x) / 256;
				data->set_b = data->rgb_data[2][2];
				data->scroll_b_pos[2] = data->min_scroll_x + data->set_b * (data->max_scroll_x - data->min_scroll_x) / 256;
				break;

			case CHGCHARCOLOR_ID_SET_MY_CLOTH:
                data->active_id = event_id;
				data->set_part_index = 3;
				data->color_index[3] = 3;
				data->is_setting_rgb = true;
				data->set_r = data->rgb_data[3][0];
				data->scroll_r_pos[3] = data->min_scroll_x + data->set_r * (data->max_scroll_x - data->min_scroll_x) / 256;
				data->set_g = data->rgb_data[3][1];
				data->scroll_g_pos[3] = data->min_scroll_x + data->set_g * (data->max_scroll_x - data->min_scroll_x) / 256;
				data->set_b = data->rgb_data[3][2];
				data->scroll_b_pos[3] = data->min_scroll_x + data->set_b * (data->max_scroll_x - data->min_scroll_x) / 256;
				break;

			case CHGCHARCOLOR_ID_SET_MY_GLOVE:
                data->active_id = event_id;
				data->set_part_index = 4;
				data->color_index[4] = 3;
				data->is_setting_rgb = true;
				data->set_r = data->rgb_data[4][0];
				data->scroll_r_pos[4] = data->min_scroll_x + data->set_r * (data->max_scroll_x - data->min_scroll_x) / 256;
				data->set_g = data->rgb_data[4][1];
				data->scroll_g_pos[4] = data->min_scroll_x + data->set_g * (data->max_scroll_x - data->min_scroll_x) / 256;
				data->set_b = data->rgb_data[4][2];
				data->scroll_b_pos[4] = data->min_scroll_x + data->set_b * (data->max_scroll_x - data->min_scroll_x) / 256;
				break;

			case CHGCHARCOLOR_ID_SET_MY_SHOES:
                data->active_id = event_id;
				data->set_part_index = 5;
				data->color_index[5] = 3;
				data->is_setting_rgb = true;
				data->set_r = data->rgb_data[5][0];
				data->scroll_r_pos[5] = data->min_scroll_x + data->set_r * (data->max_scroll_x - data->min_scroll_x) / 256;
				data->set_g = data->rgb_data[5][1];
				data->scroll_g_pos[5] = data->min_scroll_x + data->set_g * (data->max_scroll_x - data->min_scroll_x) / 256;
				data->set_b = data->rgb_data[5][2];
				data->scroll_b_pos[5] = data->min_scroll_x + data->set_b * (data->max_scroll_x - data->min_scroll_x) / 256;
				break;

			case CHGCHARCOLOR_ID_FINAL_OK:
                data->active_id = event_id;
				for(i=0; i<7; i++)
				{
					part_color = GetCharacterPartRGB(0, i);
					set_new_character_part_color(i, part_color);
				}
				request_index = get_new_character_body_index();	//0~13
                iRet = ClientRequestForDefaultCharacterInfo(request_index);
				break;

			case CHGCHARCOLOR_ID_FINAL_CANCEL:
                data->active_id = event_id;
				set_next_app_state(APPSTATE_INIT_CREATE_CHARACTER);
				change_app_state();
				break;

			case CHGCHARCOLOR_ID_RGB_OK:
                data->active_id = event_id;
				data->is_setting_rgb = false;
				break;

			case CHGCHARCOLOR_ID_RGB_CANCEL:
                data->active_id = event_id;
				data->is_setting_rgb = false;
				break;

			//case CHGCHARCOLOR_ID_R_SCROLL_BKGND:
			case CHGCHARCOLOR_ID_R_SCROLL_BAR:
                data->mouse_event = MOUSE_EVENT_R_SCROLL;
				break;

			//case CHGCHARCOLOR_ID_G_SCROLL_BKGND:
			case CHGCHARCOLOR_ID_G_SCROLL_BAR:
                data->mouse_event = MOUSE_EVENT_G_SCROLL;
				break;

			//case CHGCHARCOLOR_ID_B_SCROLL_BKGND:
			case CHGCHARCOLOR_ID_B_SCROLL_BAR:
                data->mouse_event = MOUSE_EVENT_B_SCROLL;
				break;

			//case CHGCHARCOLOR_ID_ALL_SCROLL_BKGND:
			case CHGCHARCOLOR_ID_ALL_SCROLL_BAR:
                data->mouse_event = MOUSE_EVENT_A_SCROLL;
				break;

			default:
				if(event_id >= CHGCHARCOLOR_ID_GRID_COLOR && event_id < CHGCHARCOLOR_ID_GRID_COLOR + 7 * 4)
				{
					index = event_id - CHGCHARCOLOR_ID_GRID_COLOR;
					part_index = data->set_part_index = index / 4;
					data->color_index[part_index] = index % 4;
					update_changed_character_color();
				}
				break;
            }
        }
        break;
    case WM_LBUTTONUP:
        data->active_id = 0;
        data->mouse_event = 0;
        break;
    }
    return  0;
}


