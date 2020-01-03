/*
**  MainGame.cpp
**  main game functions.
**
**  Jack, 2002.5.15.
*/
#include "MainFun.h"
#include "NetGE_MainFunc.h"
#include "Map.h"
#include "MapHouse.h"
#include "Npc.h"
#include "MainGame.h"
#include "ClientMain.h"
#include "CRange.h"
#include "CChat.h"
#include "UI.h"
#include "ErrorMsg.h"
#include "UIMap.h"
#include "UIPosIME.h"
#include "Magic.h"
#include "HrtBeat.h"
#include "qqmain.h"
#include "SGE.h"
#include "UIMapQuickMagic.h"
#include "CmdEvent.h"
#include "UIMagicArea.h"
#include "CHear.h"
#include "Weather.h"
#include "UISystemMessage.h"
#include "UIGameMessage.h"
#include "MagicHit.h"
#include "UIMapChat.h"
#include "PosData.h"
#include "qqmsgbox.h"
#include "TileField.h"
#include "UILoading.h"
#include "UIManager.h"
#include "UIShop.h"
#include "UIQuitGame.h"
//
#include "Client_Item.h"
#include "Client_SendMsg.h"
#include "Client_RecvMsg.h"
#include "Team.h"

#include "UIIconMessage.h"
#include "uishowmap.h"

#undef  DEBUG_MSG

// DEFINES /////////////////////////////////////////////////////////////////////////////////////////////////////////


//GLOBALS ////////////////////////////////////////////////////////////////////////////////////////////////
RGB_COLOR   game_font_colors[MAX_GAME_FONT_COLORS] = 
{
    {1		,166	,98		,0  },  //00
    {237	,187	,54		,0  },  //01
    {183	,54		,237	,0  },  //02
    {237	,54		,54		,0  },  //03
    {128	,128	,128	,0  },  //04
    {128	,128	,64		,0  },  //05
    {0		,0		,160	,0  },  //06
    {255	,128	,0		,0  },  //07
    {64		,128	,128	,0  },  //08
    {21		,42		,1		,0  },  //09
    {0		,128	,255	,0  },  //10
    {255	,128	,192	,0  },  //11
    {128	,64		,64		,0  },  //12
    {56		,79		,138	,0  },  //13
    {64		,0		,128	,0  },  //14
    {0		,0		,0		,0  },  //15
};

GAME_CONFIG game_config;

// Jack, add for use windows' edit as chat input [3/10/2003]
//rEdit	* reChatInput;
//
SLONG   handle_control_ui(UINT message, WPARAM wParam, LPARAM lParam);
SLONG   handle_control_input(UINT message, WPARAM wParam, LPARAM lParam);
SLONG   handle_noshift_press(UINT message, WPARAM wParam, LPARAM lParam);
SLONG   handle_noshift_press_left_mouse(UINT message, WPARAM wParam, LPARAM lParam);
SLONG   handle_noshift_press_left_mouse_item(UINT message, WPARAM wParam, LPARAM lParam);
SLONG   handle_noshift_press_left_mouse_skill(UINT message, WPARAM wParam, LPARAM lParam);
SLONG   handle_noshift_press_right_mouse(UINT message, WPARAM wParam, LPARAM lParam);
SLONG   handle_noshift_press_right_mouse_item(UINT message, WPARAM wParam, LPARAM lParam);
SLONG   handle_noshift_press_right_mouse_skill(UINT message, WPARAM wParam, LPARAM lParam);
SLONG   handle_shift_press(UINT message, WPARAM wParam, LPARAM lParam);
SLONG   handle_shift_press_left_mouse(UINT message, WPARAM wParam, LPARAM lParam);
SLONG   handle_shift_press_left_mouse_item(UINT message, WPARAM wParam, LPARAM lParam);
SLONG   handle_shift_press_left_mouse_skill(UINT message, WPARAM wParam, LPARAM lParam);
SLONG   handle_shift_press_right_mouse(UINT message, WPARAM wParam, LPARAM lParam);
SLONG   handle_shift_press_right_mouse_item(UINT message, WPARAM wParam, LPARAM lParam);
SLONG   handle_shift_press_right_mouse_skill(UINT message, WPARAM wParam, LPARAM lParam);
SLONG   handle_release_mouse(UINT message, WPARAM wParam, LPARAM lParam);
//
void    refresh_map_house(void);
//SLONG   handle_map_map(UINT message, WPARAM wParam, LPARAM lParam);
//SLONG   handle_map_npc(UINT message, WPARAM wParam, LPARAM lParam);
//SLONG   handle_map_item(UINT message, WPARAM wParam, LPARAM lParam);
//SLONG   handle_maingame_lbuttondown(UINT message, WPARAM wParam, LPARAM lParam);
//SLONG   handle_maingame_lbuttonup(UINT message, WPARAM wParam, LPARAM lParam);
//SLONG   handle_maingame_rbuttondown(UINT message, WPARAM wParam, LPARAM lParam);
//SLONG   handle_maingame_rbuttonup(UINT message, WPARAM wParam, LPARAM lParam);
SLONG   handle_maingame_mousemove(UINT message, WPARAM wParam, LPARAM lParam);
SLONG   handle_maingame_hotkey_down(UINT message, WPARAM wParam, LPARAM lParam);
SLONG   handle_maingame_hotkey_up(UINT message, WPARAM wParam, LPARAM lParam);
SLONG   process_shortkey_hide_or_restore_all_ui(void);
SLONG   process_shortkey_emotion(SLONG index);
SLONG   process_shortkey_use_item(SLONG index);
SLONG	exec_maingame_escape_key_up(void);
void	debug_repeat_prev_chat_input(void);


//FUNCTIONS //////////////////////////////////////////////////////////////////////////////////////////////
void    init_game_colors(void)
{
    SLONG   i;

    for(i=0; i<MAX_GAME_FONT_COLORS; i++)
    {
        game_font_colors[i].color = rgb2hi(game_font_colors[i].r, game_font_colors[i].g, game_font_colors[i].b);
    }
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////
// MAIN GAME FUNCTIONS(主遊戲)                                                                          //
//////////////////////////////////////////////////////////////////////////////////////////////////////////
int     init_main_game(void)
{
    USTR    map_filename[_MAX_FNAME];
    USTR    filename[_MAX_FNAME];
    USTR    mask_filename[_MAX_FNAME];
    SLONG   redraw_map_flags;
    USTR    minimap_filename[_MAX_FNAME];

    //(0) 客戶端測試初始化
    client_cmd_init_main_game();

    //(1) 載入地圖.
    set_data_file(packed_map_file);
    sprintf((char *)map_filename, "map\\%s.map", g_szPlayerMap);
    if(TTN_OK != load_map((USTR*)map_filename))
    {
        log_error(1, "ERROR: load map file %s failed", map_filename);
        return  -1;
    }

    //載入地圖的縮小圖
    set_data_file(packed_map_file);
    sprintf((char *)minimap_filename, "map\\%s.fff", g_szPlayerMap);
    load_minimap_of_fff((USTR*)minimap_filename);

    //(2) 載入地圖阻擋.
    //init_map_base(g_lPlayerMap);
    change_file_extension((USTR*)filename, (USTR*)map_data.filename, (USTR*)MASK_FILE_EXT);
    sprintf((char *)mask_filename, "map\\%s", filename);
    //if(TTN_OK != load_map_base(g_lPlayerMap, (USTR*)mask_filename))
	if(TTN_OK != LoadZoneMapMask((char *)mask_filename))
    {
        log_error(1, "ERROR: load map mask file %s failed", mask_filename);
        return  -2;
    }

    //(3) 開始加入地圖 NPC.
    set_map_move_follow_npc(g_lPlayerIndex);
    redraw_map_flags = 0
        | REDRAW_MAP_TILE_IMAGE 
        //| REDRAW_MAP_TILE_GRID 
        | REDRAW_MAP_UPPER_IMAGE
        | REDRAW_MAP_UNDER_OBJECT 
        | REDRAW_MAP_NORMAL_OBJECT 
        //| REDRAW_MAP_TRACK_IMAGE
        //| REDRAW_MAP_BLOCK_INFO
        //| REDRAW_MAP_PROC_INFO
        //| REDRAW_MAP_RECT_RANGE
        //| REDRAW_MAP_DIAMOND_RANGE
        //| REDRAW_MAP_REFRESH_OBJECT
        //| REDRAW_MAP_REFRESH_NPC
        //| REDRAW_MAP_CURRENT_PATH
        //| REDRAW_MAP_ADJUST_START
        | REDRAW_MAP_CLEAR_BITMAP
        ;
    set_map_redraw_flags(redraw_map_flags);

    //(x) 設置地圖介面數據.
    game_chat.clear();
	clear_magic_area();
	// Jack, [12/27/2002]
	// can't do this just client, but also server... 
	//InitCharacterRightHandMagicState(g_lPlayerIndex);
	reset_map_tile_plat();

    //(x) HEARTBEAT
    start_heartbeat();

	// Jack, temp use  [1/29/2003]
	InitZoneMagicPart();
	
    game_hear.clear();

    set_data_file(packed_music_file);
    play_music(1, 1);

    //呼叫 REFRESH 2 次以載入npc的圖檔
    refresh_main_game_once();
    refresh_main_game_once();

//    enable_ime();

	// Jack, add for use windows edit input [3/10/2003]
	/*
	RECT	rc;
	reChatInput = new rEdit();
	SetRect( &rc, 100, 200, 540, 224 );
	reChatInput->Create(g_hDDWnd, &rc, ES_LEFT | ES_AUTOHSCROLL);
	reChatInput->SetFont(NULL, 12);
	reChatInput->LimitText(CHAT_INPUT_LEN);
	reChatInput->Show(TRUE);
	*/


	//設置為當前沒有在退出遊戲狀態
	g_IsExitingGame = 0;

    return  0;
}



void    active_main_game(int active)
{
}


void    free_main_game(void)
{
    stop_heartbeat();

    clear_all_map_npc();
    clear_map();
    //free_map_base(g_lPlayerMap);
	FreeZoneMapMask();
    free_minimap();

    game_hear.clear();
    //stop_music();
//    disable_ime();

	// Jack, add for use windows' edit as chat input [3/10/2003]
	//delete reChatInput;
}



void    refresh_map_house(void)
{
    SLONG   npc_x, npc_y, npc_z, stay_house;
    SLONG   roof_index, i, npc_no;

    npc_no = g_lPlayerIndex;

    //預先假設人物離開了所有的房屋，將所有屋頂蓋上。
    for(i=0; i<map_house_max; i++)
    {
        roof_index = map_house[i].roof_index;
        if(roof_index >= 0)
        {
            map_object[roof_index].update_alpha = 1;    //屋頂蓋上。
        }
    }
    
    //檢測人物所處的房屋，將對應房屋的屋頂掀開。
	GetCharacterPosition(npc_no, &npc_x, &npc_y, &npc_z);
    stay_house = get_in_house_index_by_pixel_position(map_tile_field, npc_x, npc_y);
    if(stay_house >= 0)
    {
        roof_index = map_house[stay_house].roof_index;
        if(roof_index >= 0)
        {
            map_object[roof_index].update_alpha = -1;    //屋頂掀開。
        }
    }
}


void    refresh_main_game(void)
{
    SLONG   times;
	DWORD	event;

    times = (SLONG)get_heartbeat_refresh_times();
    while(--times >= 0)
    {
        refresh_main_game_once();
    }

	LOCK_GLOBALS(0);
	event = g_dwAppEvent;
	UNLOCK_GLOBALS(0);

	if(event == APPEVENT_START_PLAY_MAINGAME)
	{
		//通知SERVER載入地圖完成, 可以開始遊戲了.
		client_cmd_game_start();

		LOCK_GLOBALS(0);
		g_dwAppEvent = 0;
		UNLOCK_GLOBALS(0);
	}
}


void    refresh_main_game_once(void)
{
	// Jack, remark for test. [2/12/2003]
    //refresh_map_item(g_lPlayerMap);
    refresh_map_npc();
    refresh_map_magic();
    refresh_map_house();
    refresh_map_ui();
    refresh_mouse_hand_doing();
    refresh_weather();
    refresh_system_message();
    refresh_game_message();
}


void    redraw_main_game(SLONG sx, SLONG sy, void *vbitmap)
{
    BMP *bitmap = (BMP*)vbitmap;
    SLONG   dark;
    SLONG   mx, my;

    get_mouse_position(&mx, &my);
	update_mouse_hand_item();

    //adjust_map_move();
    weather_adjust_map_move();
    local_refresh_npc_talk();

    game_range.clear();
    game_range.add(0, 0, bitmap->w, bitmap->h, RT_MAP, 0);
    redraw_map(bitmap);

    // Jack. [7/30/2002]
    //sge_show_light(g_lPlayerMap, mx, my, bitmap);
    //refresh_sge();

    dark = get_map_dark();
    if(dark > 0)
    {
        // Jack, for test. [14:29,9/3/2002]
        alpha_put_bar(0, 0, bitmap->w, bitmap->h, SYSTEM_BLACK, bitmap, dark);
        //alpha_put_bar(0, 0, bitmap->w, bitmap->h, SYSTEM_BLUE, bitmap, dark);
    }
    debug_redraw_game_map_mask(bitmap);
    debug_redraw_game_map_proc(bitmap);

    exec_weather(bitmap);

    redraw_game_message(bitmap);
	redraw_iconmsg( screen_buffer );

    redraw_map_ui(bitmap);

	redraw_event_ui(bitmap);

    redraw_system_message(bitmap);
	//redraw_ui_msgbox(bitmap);

//    pos_main_game_redraw_ime(bitmap);
    debug_redraw_game_info(bitmap);
	debug_redraw_game_minimap(bitmap);

    SLONG   npc_x, npc_y, npc_z;

    LOCK_CHARACTER(g_lPlayerIndex);
	GetCharacterPosition(g_lPlayerIndex, &npc_x, &npc_y, &npc_z);
    UNLOCK_CHARACTER(g_lPlayerIndex);
    game_hear.check_play(npc_x, npc_y, 0);

	// Jack. [12/18/2002]
	// 如果當前正在退出遊戲中, 則不響應玩家的滑鼠消息
	if(g_IsExitingGame)
	{
		game_range.clear();
		redraw_transfer_waiting(bitmap);
	}
	// 
}

SLONG   handle_main_game(UINT message, WPARAM wParam, LPARAM lParam)
{
	// Jack. [12/18/2002]
	// 如果當前正在退出遊戲中, 則不響應玩家的滑鼠消息
	if(g_IsExitingGame)
	{
		return	0;
	}

    //快捷方式的過濾
    if(filter_map_quick_magics(message, wParam, lParam))
        return  0;
    //        
    if(filter_map_chat_input(message, wParam, lParam))
        return  0;

    // 藏寶圖 世界地圖
    if ( 0 == handle_sm( message, wParam, lParam ) )
        return 0;

    //qq介面輸入..過濾        
    if(0 == handle_ui_qq(message, wParam, lParam))
        return  0;
    //消息框
	if(0 == handle_ui_msgbox(message, wParam, lParam))
		return	0;
    //貿易店
	if(0 == handle_ui_shop(message, wParam, lParam))
		return	0;
    //離開遊戲的介面		
	if(0 == handle_ui_quitgame(message, wParam, lParam))
		return	0;
    //道具店
	if(0 == handle_ui_store(message, wParam, lParam))
		return	0;
    //		
	if(0 == handle_iconmsg( message, wParam, lParam ))
		return 0;
    //控制介面的消息處理
	if(0 == handle_control_ui( message, wParam, lParam ))
		return 0;    
    //
//    TM info;
//    WM info2;

    // 調試藏寶圖
    switch ( message )
    {
    case WM_MOUSEMOVE:
        handle_maingame_mousemove(message, wParam, lParam);
        break;
//    case WM_KEYDOWN:
//        switch ( wParam )
//        {
//        case VK_F6:
//            info.kind  = 0;
//            info.left  = 0;
//            info.top   = 0;
//            info.mask  = TM_MASK_FULL[0]&TM_MASK_FULL[2];
//            info.style = 3;
//            info.x     = 100;
//            info.y     = 100;
//            strcpy( info.name, "Solomon" );
//            sm_set_tm_info( &info );
//            
//            info2.left  = 200;
//            info2.top   = 200;
//            info2.x     = 300;
//            info2.y     = 300;
//            sm_set_wm_info( &info2 );
//            sm_set( TYPE_TM );
//            break;
//        case VK_F7:
//            info.kind  = 0;
//            info.left  = 0;
//            info.top   = 0;
//            info.mask  = TM_MASK_FULL[0]&TM_MASK_FULL[2];
//            info.style = 3;
//            info.x     = 100;
//            info.y     = 100;
//            strcpy( info.name, "Solomon" );
//            sm_set_tm_info( &info );
//            
//            info2.left  = 200;
//            info2.top   = 200;
//            info2.x     = 300;
//            info2.y     = 300;
//            sm_set_wm_info( &info2 );
//            sm_set( TYPE_WM );
//            break;
//        case VK_F8:
//            sm_set( TYPE_CLOSE );
//            break;
//        }
        break;
    }

    return handle_control_input(message, wParam, lParam);
    
    // mark by lijun 2003-04-16
    /*    
    switch(message)
    {
    case WM_MOUSEMOVE:
        handle_maingame_mousemove(message, wParam, lParam);
        return  0;

    case WM_LBUTTONDOWN:
        handle_maingame_lbuttondown(message, wParam, lParam);
        return  0;

    case WM_LBUTTONUP:
        handle_maingame_lbuttonup(message, wParam, lParam);
        return  0;

    case WM_RBUTTONDOWN:
        handle_maingame_rbuttondown(message, wParam, lParam);
        return  0;

    case WM_RBUTTONUP:
        handle_maingame_rbuttonup(message, wParam, lParam);
        return  0;

    case WM_IME_STRING:
        return  0;

    case WM_KEYDOWN:
        handle_maingame_hotkey_down(message, wParam, lParam);
        return  0;

    case WM_KEYUP:
        handle_maingame_hotkey_up(message, wParam, lParam);
        return  0;

    case WM_SYSKEYDOWN:
        if(wParam == VK_F10) process_shortkey_hide_or_restore_all_ui();
        return  0;
    }
    return  0;
    */    
}

//-------------------------------------------------------------------------
void    refresh_mouse_hand_doing(void)
{
    return;
}
// mark by lijun 2003-05-016
/*
void    refresh_mouse_hand_doing(void)
{
    DWORD   curr_time;
    SLONG   map_x, map_y, npc_x, npc_y, npc_z, dx, dy;

    switch(mouse_hand.left_down.doing)
    {
    case HAND_DOING_CTRL_MAP:
        curr_time = timeGetTime();
        if(curr_time - mouse_hand.left_down.time > DRAG_EVENT_PERIOD_MAP)
        {
            map_x = mouse_hand.left_down.x + map_data.map_sx;
            map_y = mouse_hand.left_down.y + map_data.map_sy;

            LOCK_CHARACTER(g_lPlayerIndex);
			GetCharacterPosition(g_lPlayerIndex, &npc_x, &npc_y, &npc_z);
            UNLOCK_CHARACTER(g_lPlayerIndex);
            dx = abs(map_x - npc_x);
            dy = abs(map_y - npc_y);
            if(dx >= INVALID_MOUSE_RANGE_HALF_WIDTH || dy >= INVALID_MOUSE_RANGE_HALF_HEIGHT)
            {
                client_cmd_left_hit_map(map_x, map_y);
            }
            mouse_hand.left_down.time = curr_time;
        }
        return;

    default:
        break;
    }

    switch(mouse_hand.right_down.doing)
    {
    case HAND_DOING_CTRL_MAP:
        curr_time = timeGetTime();
        if(curr_time - mouse_hand.right_down.time > DRAG_EVENT_PERIOD_MAP)
        {
            map_x = mouse_hand.right_down.x + map_data.map_sx;
            map_y = mouse_hand.right_down.y + map_data.map_sy;

            LOCK_CHARACTER(g_lPlayerIndex);
			GetCharacterPosition(g_lPlayerIndex, &npc_x, &npc_y, &npc_z);
            UNLOCK_CHARACTER(g_lPlayerIndex);
            dx = abs(map_x - npc_x);
            dy = abs(map_y - npc_y);
            if(dx >= INVALID_MOUSE_RANGE_HALF_WIDTH || dy >= INVALID_MOUSE_RANGE_HALF_HEIGHT)
            {
                client_cmd_left_hit_map(map_x, map_y);
            }
            mouse_hand.right_down.time = curr_time;
        }
        return;

    default:
        break;
    }
}
*/

/******************************************************************************************************************/
/* GAME DEBUG CONFIG FUNCTIONS                                                                                    */
/******************************************************************************************************************/
int     init_game_config(void)
{
    memset(&game_config, 0, sizeof(game_config));
    return  0;
}

void    active_game_config(int active)
{
    //nothing to do.
}

void    free_game_config(void)
{
    //nothing to do.
}


void    set_game_config_show_npc_name(SLONG flag)
{
    if(flag) 
        game_config.show_flags |= CONFIG_SHOW_NPC_NAME;
    else
        game_config.show_flags &= ~CONFIG_SHOW_NPC_NAME;
}


SLONG   get_game_config_show_npc_name(void)
{
    return  game_config.show_flags & CONFIG_SHOW_NPC_NAME ? 1 : 0;
}


void    set_game_config_show_map_mask(SLONG flag)
{
    if(flag)
        game_config.show_flags |= CONFIG_SHOW_MAP_MASK;
    else
        game_config.show_flags &= ~CONFIG_SHOW_MAP_MASK;
}

SLONG   get_game_config_show_map_mask(void)
{
    return  game_config.show_flags & CONFIG_SHOW_MAP_MASK ? 1 : 0;
}


void    set_game_config_show_map_proc(SLONG flag)
{
    if(flag) 
        game_config.show_flags |= CONFIG_SHOW_MAP_PROC;
    else
        game_config.show_flags &= ~CONFIG_SHOW_MAP_PROC;
}

SLONG   get_game_config_show_map_proc(void)
{
    return  game_config.show_flags & CONFIG_SHOW_MAP_PROC ? 1 : 0;
}

void    set_game_config_show_game_info(SLONG flag)
{
    if(flag)
        game_config.show_flags |= CONFIG_SHOW_GAME_INFO;
    else
        game_config.show_flags &= ~CONFIG_SHOW_GAME_INFO;
}

SLONG   get_game_config_show_game_info(void)
{
    return  game_config.show_flags & CONFIG_SHOW_GAME_INFO ? 1 : 0;
}

void	set_game_config_show_debug_minimap(SLONG flag)
{
	if(flag)
		game_config.show_flags |= CONFIG_SHOW_DEBUG_MINIMAP;
	else
		game_config.show_flags &= ~CONFIG_SHOW_DEBUG_MINIMAP;
}


SLONG	get_game_config_show_debug_minimap(void)
{
	return	game_config.show_flags & CONFIG_SHOW_DEBUG_MINIMAP ? 1 : 0;
}

void	set_game_config_show_game_range(SLONG flag)
{
	if(flag)
		game_config.show_flags |= CONFIG_SHOW_GAME_RANGE;
	else
		game_config.show_flags &= ~CONFIG_SHOW_GAME_RANGE;
}

SLONG	get_game_config_show_game_range(void)
{
	return	game_config.show_flags & CONFIG_SHOW_GAME_RANGE ? 1 : 0;
}

void    debug_redraw_game_map_mask(BMP *bitmap)
{
    SLONG   flag, show_flags;
    MAP_MASK*   mm;

    flag = get_game_config_show_map_mask();
    if(flag)
    {
        mm = GetZoneMapMask();
        show_flags = MASK_SHOW_STOP | MASK_SHOW_MID_MAGIC;
        redraw_map_mask(map_data.map_sx, map_data.map_sy, mm, show_flags, bitmap);
    }
}


void    debug_redraw_game_map_proc(BMP *bitmap)
{
    SLONG   flag, redraw_flag;

    flag = get_game_config_show_map_proc();
    if(flag)
    {
        redraw_flag = 1;
        redraw_map_proc_layer(map_data.map_sx, map_data.map_sy, redraw_flag, bitmap);
    }
}


void    debug_redraw_game_info(BMP *bitmap)
{
    enum
    {   INFO_SX =   4,    
    INFO_SY     =   20,
    INFO_DX     =   0,
    INFO_DY     =   14,
    };
    SLONG   info_x, info_y;
    SLONG   flag, npc_no;
	SLONG	x, y, z, dir, file_index, doing_kind, doing_step;
	SLONG	image_id, object_index;
	SLONG	on_the_sea, speed, speedx, speedy, sight_range;
	SLONG	npc_flag;

    flag = get_game_config_show_game_info();
    if(!flag)
        return;

	// Set start position and chine effect -------------
    info_x = INFO_SX;
    info_y = INFO_SY;
	sprintf((char *)print_rec, "~C8~O7");
    print12(info_x, info_y, (USTR*)print_rec, PEST_PUT, bitmap);

    sprintf((char *)print_rec, " FPS=%d  SEND:%d  RECV:%d  HRT=%d",
        get_fps(), 
		get_send_bps(),
		get_recv_bps(),
        get_heartbeat_timeout_milliseconds()
        );
    print12(info_x, info_y, (USTR*)print_rec, PEST_PUT, bitmap);
    info_x += INFO_DX;
    info_y += INFO_DY;

    sprintf((char *)print_rec, " ALF:%d  APP:%d  ZONE=%s, MAP=%s(%d,%d)",
        uimap_data.map_dark,
        g_dwAppState,
        g_szPlayerZone, 
        g_szPlayerMap,
        map_data.map_sx,
        map_data.map_sy
        );
    print12(info_x, info_y, (USTR*)print_rec, PEST_PUT, bitmap);
    info_x += INFO_DX;
    info_y += INFO_DY;

	LOCK_CHARACTER(0);
	GetCharacterPosition(g_lPlayerIndex, &x, &y, &z);
	dir = GetCharacterDir(g_lPlayerIndex);
	file_index = GetCharacterFileIndex(g_lPlayerIndex);
	doing_kind = GetCharacterDoingKind(g_lPlayerIndex);
	doing_step = GetCharacterDoingStep(g_lPlayerIndex);
	image_id = GetCharacterImageID(g_lPlayerIndex);
	on_the_sea = IsCharacterOnTheSea(g_lPlayerIndex);
	speedx = GetCharacterShipSpeedX(g_lPlayerIndex);
	speedy = GetCharacterShipSpeedX(g_lPlayerIndex);
	speed = GetCharacterMoveSpeed(g_lPlayerIndex);
	sight_range = GetCharacterSightRange(g_lPlayerIndex);

	object_index = get_npc_object_index(g_lPlayerIndex);
	npc_flag = get_npc_flag(g_lPlayerIndex);
	UNLOCK_CHARACTER(0);

    sprintf((char *)print_rec, " PLAYER:%d  POS:%d,%d,%d DIR:%d FILE:%d DO:%d,%d IMG:0x%08x OBJ:%d",
        g_lPlayerIndex, 
        x, y, z,
        dir,
        file_index,
        doing_kind,
        doing_step,
		image_id,
		object_index
        );
    print12(info_x, info_y, (USTR*)print_rec, PEST_PUT, bitmap);
    info_x += INFO_DX;
    info_y += INFO_DY;

	sprintf((char *)print_rec, " FLAG:%d SIGHT:%d", npc_flag, sight_range);
    print12(info_x, info_y, (USTR*)print_rec, PEST_PUT, bitmap);
    info_x += INFO_DX;
    info_y += INFO_DY;

	if(on_the_sea)
		sprintf((char *)print_rec, " SPD:%d,%d", speedx, speedy);
	else
		sprintf((char *)print_rec, " SPD:%d", speed);
    print12(info_x, info_y, (USTR*)print_rec, PEST_PUT, bitmap);
    info_x += INFO_DX;
    info_y += INFO_DY;

    if(mouse_hand.point_kind == RT_NPC)
    {
        npc_no =  mouse_hand.point_no;
		GetCharacterPosition(npc_no, &x, &y, &z);
        sprintf((char *)print_rec, " NPC:%d, (%d,%d,%d)", npc_no, x, y, z);
        print12(info_x, info_y, (USTR*)print_rec, PEST_PUT, bitmap);
        info_x += INFO_DX;
        info_y += INFO_DY;
    }

	// Reset chine effect --------------------
	sprintf((char *)print_rec, "~C0~O0");
    print12(info_x, info_y, (USTR*)print_rec, PEST_PUT, bitmap);
}


void	debug_redraw_game_range(void *vbitmap)
{
	BMP	*bitmap = (BMP*)vbitmap;
	SLONG mx, my, type, id;
	char info[80];
	SLONG flag;

	flag = get_game_config_show_game_range();
	if(flag)
	{
		game_range.redraw(0, 0, vbitmap);
		get_mouse_position(&mx, &my);
		type = id = 0;
		game_range.mapping(mx, my, &type, &id);
		sprintf((char *)info, "~C0~O3%d:%d~C0~O0", type, id);
		print16(4, SCREEN_HEIGHT-20, info, PEST_PUT, bitmap);
	}
}

/******************************************************************************************************************/
/* HANDLE MAINGAME MOUSE BUTTON EVENTS                                                                            */
/******************************************************************************************************************/


SLONG   process_shortkey_emotion(SLONG index)
{
    SLONG   doings[10] = 
    {
        DOING_KIND_SWASH,       // Ctrl 0 = 嚇唬(假裝攻擊)
        DOING_KIND_BECKON,      // Ctrl 1 = 招手
        DOING_KIND_SAY_NO,      // Ctrl 2 = 說不
        DOING_KIND_ANGRY,       // Ctrl 3 = 生氣
        DOING_KIND_FAINT,       // Ctrl 4 = 暈倒
        DOING_KIND_XXPOWER,     // Ctrl 5 = 假裝蓄力
        DOING_KIND_XXBEATED,    // Ctrl 6 = 假裝被擊
    };

    client_cmd_npc_doing(g_lPlayerIndex, doings[index], 0, 0, 0, 0, 0, 0);

    return  0;
}


SLONG   process_shortkey_use_item(SLONG index)
{
    if(index >= 1 && index <= 4) //物品操作快捷鍵為'1'~'4'
    {
		client_cmd_right_hit_sash_item(index-1);
    }
    return  0;
}


SLONG   handle_maingame_hotkey_down(UINT message, WPARAM wParam, LPARAM lParam)
{
    //DWORD   dwTime;

    switch(wParam)
    {
    case 'A':   //切換人物的戰鬥與和平模式
        client_cmd_change_fight_state();
        return  0;
        
    case 'C':   //開啟和關閉人物狀態選單
        if(is_map_submenu_opened(SUBMENU_STATE))
            close_map_submenu(SUBMENU_STATE);
        else
            open_map_submenu(SUBMENU_STATE);
        return  0;

    case 'I':   //開啟和關閉人物物品選單
        if(is_map_submenu_opened(SUBMENU_ITEM))
            close_map_submenu(SUBMENU_ITEM);
        else
            open_map_submenu(SUBMENU_ITEM);
        return  0;

    case 'T':   //開啟和關閉人物技能選單
        if(is_map_submenu_opened(SUBMENU_SKILL))
            close_map_submenu(SUBMENU_SKILL);
        else
            open_map_submenu(SUBMENU_SKILL);
        return  0;

    case 'Q':   //開啟和關閉人物任務選單
        if(is_map_submenu_opened(SUBMENU_TASK))
            close_map_submenu(SUBMENU_TASK);
        else
            open_map_submenu(SUBMENU_TASK);
        return  0;

    case 'S':   //開啟和關閉船隻選單
        if(is_map_submenu_opened(SUBMENU_SHIP))
            close_map_submenu(SUBMENU_SHIP);
        else
            open_map_submenu(SUBMENU_SHIP);
        return  0;
        
    case 'H':   //開啟和關閉聊天紀錄
        switch_show_chat_records_flag();
        return  0;

    case VK_OEM_COMMA:  // ',' 使地圖變暗
        uimap_data.map_dark -= 16;
        if(uimap_data.map_dark < 0)
            uimap_data.map_dark = 0;
        return  0;
        
    case VK_OEM_PERIOD: // '.' 使地圖變亮
        uimap_data.map_dark += 16;
        if(uimap_data.map_dark > 255)
            uimap_data.map_dark = 255;
        return  0;
        
    case VK_F1: //0x70  使用快捷法術來改變人物的左右手技能
    case VK_F2: //0x71
    case VK_F3: //0x72
    case VK_F4: //0x73
    case VK_F5: //0x74
    case VK_F6: //0x75
    case VK_F7: //0x76
    case VK_F8: //0x77
        if( (mouse_hand.point_kind == UIMAP_EVENT) 
            && ( mouse_hand.point_no >= UIMAP_ID_QUICK_MAGIC_0 )
            && (mouse_hand.point_no < UIMAP_ID_QUICK_MAGIC_0 + MAX_GAME_SKILL_BASES) )
        {/* setup hotkey magic */
            SLONG   magic_no, quick_index;
            
            quick_index = wParam - VK_F1;
            magic_no = mouse_hand.point_no - UIMAP_ID_QUICK_MAGIC_0;
            if( is_left_quick_magics_ui_visible() )
            {
                client_cmd_set_lhand_quick_magic(quick_index, magic_no);
            }
            else if(is_right_quick_magics_ui_visible())
            {
                client_cmd_set_rhand_quick_magic(quick_index, magic_no);
            }
        }
        else
        {/* change current hand magic by hotkey magic */
            SLONG   quick_index;
            
            quick_index = wParam - VK_F1;
            client_cmd_quick_set_hand_magic(quick_index);
        }
        return  0;
        
    case VK_F9:
		debug_repeat_prev_chat_input();
        //dwTime = get_heartbeat_timeout_milliseconds();
        //dwTime += 10;
        //set_heartbeat_timeout_milliseconds(dwTime);
        return  0;
        
    case VK_F11:
        //dwTime = get_heartbeat_timeout_milliseconds();
        //if(dwTime > 20)
            //dwTime -= 10;
        //set_heartbeat_timeout_milliseconds(dwTime);
        return  0;
    }
    return  0;
}


SLONG   handle_maingame_hotkey_up(UINT message, WPARAM wParam, LPARAM lParam)
{
    switch(wParam)
    {
    case VK_ESCAPE: //退出遊戲
		exec_maingame_escape_key_up();
        return 0;
        
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
        {
            SHORT   nState;
            SLONG   index;
            
            nState = GetKeyState(VK_CONTROL);
            if(nState & 0x8000)
            {
                process_shortkey_emotion(wParam - '0');
            }
            else
            {
                index = wParam - '0';
                process_shortkey_use_item(index);
            }
        }
        return  0;

    case 'N':
        {
            SLONG   show_flag;

            show_flag = get_game_config_show_npc_name();
            set_game_config_show_npc_name(! show_flag);
        }
        return  0;
    }
    return  0;
}



SLONG   process_shortkey_hide_or_restore_all_ui(void)
{
    if(uimap_data.backuped)
    {
        //restore processing ----------------------------
        close_map_submenu(uimap_data.opened_submenu);
        open_map_submenu(uimap_data.backup_opened_submenu);

        if(uimap_data.backup_minimap_flags)
            uimap_data.minimap_alpha_update = 1;
        if(uimap_data.backup_left_flags)
            uimap_data.left_alpha_update = 1;
        if(uimap_data.backup_right_flags)
            uimap_data.right_alpha_update = 1;
        if(uimap_data.backup_manface_flags)
            uimap_data.manface_alpha_update = 1;
        uimap_data.show_chat_records = uimap_data.backup_show_chat_records;
        if(uimap_data.backup_show_qq)
            ui_qq_set_max();
        uimap_data.backuped = 0;
    }
    else
    {
        //backup current ui flags. --------------------
        uimap_data.backup_minimap_flags = (uimap_data.minimap_alpha == 255 || uimap_data.minimap_alpha_update == 1);
        uimap_data.backup_left_flags = (uimap_data.left_alpha == 255 || uimap_data.left_alpha_update == 1);
        uimap_data.backup_right_flags = (uimap_data.right_alpha == 255 || uimap_data.right_alpha_update == 1);
        uimap_data.backup_manface_flags = (uimap_data.manface_alpha == 255 || uimap_data.manface_alpha_update == 1);

        uimap_data.backup_opened_submenu = uimap_data.opened_submenu;
        uimap_data.backup_show_chat_records = uimap_data.show_chat_records;
        uimap_data.backup_show_qq = ui_qq_is_max();
        
        //process close actions. ----------------------
        close_map_submenu(uimap_data.opened_submenu);
        uimap_data.minimap_alpha_update = -1;
        uimap_data.left_alpha_update = -1;
        uimap_data.right_alpha_update = -1;
        uimap_data.manface_alpha_update = -1;
        uimap_data.show_chat_records = FALSE;
        ui_qq_set_min();
        
        //update backuped flag.
        uimap_data.backuped = 1;
    }
    return  0;
}


SLONG	exec_maingame_escape_key_up(void)
{
	SLONG	hp;
	SLONG	can_exit;

	can_exit = false;
	if(g_lPlayerIndex >= 0)
	{
		LOCK_CHARACTER(g_lPlayerIndex);
		hp = GetCharacterHp(g_lPlayerIndex);
		UNLOCK_CHARACTER(g_lPlayerIndex);
		if(hp)
		{
			can_exit = true;
		}
	}

	if(can_exit)
	{
		SLONG	is_opened;

		is_opened = is_ui_quitgame_opened();
		open_ui_quitgame(1 - is_opened);
		
		// Jack, modified [2/20/2003]
		// removed to uiquitgame.cpp.
		/*
		qq_clear();
		iRet = ClientRequestExitGame();
		
		// Jack. [12/18/2002]
		// 設置為正在退出遊戲狀態.
		g_IsExitingGame = 1;
		*/
	}
	return	0;
}


SLONG	get_send_bps(void)
{
    static ULONG start_time = 0;
    static ULONG bps = 0;	//bytes per second
    static ULONG count = 0, last_count = 0;
    static SLONG init_flag = 0;
    ULONG	time;

    if(0 == init_flag)
    {
		PosSetTotalSendDataSize(0);
        start_time = timeGetTime();
        init_flag = 1;
    }
    else
    {
        time = timeGetTime();
        if(time - start_time > 1000)
        {
			count = PosGetTotalSendDataSize();
            bps = count * 1000 / (time-start_time);
            init_flag = 0;
        }
    }
    return(bps);
}


SLONG	get_recv_bps(void)
{
    static ULONG start_time = 0;
    static ULONG bps = 0;	//bytes per second
    static ULONG count = 0, last_count = 0;
    static SLONG init_flag = 0;
    ULONG	time;

    if(0 == init_flag)
    {
		PosSetTotalRecvDataSize(0);
        start_time = timeGetTime();
        init_flag = 1;
    }
    else
    {
        time = timeGetTime();
        if(time - start_time > 1000)
        {
			count = PosGetTotalRecvDataSize();
            bps = count * 1000 / (time-start_time);
            init_flag = 0;
        }
    }
    return(bps);
}


void	debug_repeat_prev_chat_input(void)
{
	USTR	buffer[256];

	if(TTN_OK == game_chat.get_prev_input(NULL, buffer, false))
	{
		client_cmd_public_talk((char *)GetCharacterMainName(g_lPlayerIndex), (char *)buffer);
		game_chat.add_input(CHATEFF_WHITE, (USTR*)buffer);
	}
}
//-----
//  對遊戲控制介面的處理
//-----
SLONG   handle_control_ui(UINT message, WPARAM wParam, LPARAM lParam)
{
    //
    SLONG   mouse_x, mouse_y, map_x, map_y;
    SLONG   event_type, event_id;
    //
    if(g_lPlayerIndex < 0)
        return  0;
    //

    switch(message)
    {
    case WM_RBUTTONDOWN:
        mouse_x = GET_X_LPARAM(lParam);
        mouse_y = GET_Y_LPARAM(lParam);
        map_x = map_data.map_sx + mouse_x;
        map_y = map_data.map_sy + mouse_y;
        event_type = event_id = 0;
        game_range.mapping(mouse_x, mouse_y, &event_type, &event_id);
        set_mouse_hand_position(mouse_x, mouse_y);
        set_mouse_hand_point_info(event_type, event_id, map_x, map_y);    
        switch(event_type)        
        {
        case UIMAP_EVENT:
            exec_right_hit_uimap(event_id);
            break;
        case UIMAPITEM_EVENT:
            handle_ui_mapitem(message, wParam, lParam);
            break;
        }
        break;    
    case WM_LBUTTONDOWN:
        mouse_x = GET_X_LPARAM(lParam);
        mouse_y = GET_Y_LPARAM(lParam);
        map_x = map_data.map_sx + mouse_x;
        map_y = map_data.map_sy + mouse_y;
        event_type = event_id = 0;
        game_range.mapping(mouse_x, mouse_y, &event_type, &event_id);
        set_mouse_hand_position(mouse_x, mouse_y);
        set_mouse_hand_point_info(event_type, event_id, map_x, map_y);    
        switch(event_type)
        {
        case UIMAP_EVENT:
            exec_left_hit_uimap(event_id);
            return 0;
            break;
        case UIMAPSTATE_EVENT:
            handle_ui_mapstate(message, wParam, lParam);
            return 0;
            break;
        case UIMAPITEM_EVENT:
            handle_ui_mapitem(message, wParam, lParam);
            return 0;
            break;
        case UIMAPTASK_EVENT:
            handle_ui_maptask(message, wParam, lParam);
            return 0;
            break;
        case UIMAPSHIP_EVENT:
            handle_ui_mapship(message, wParam, lParam);
            return 0;
            break;
        case UIMAPSKILL_EVENT:
            handle_ui_mapskill(message, wParam, lParam);
            return 0;
            break;
        case RT_TALK:
            handle_game_talk(message, wParam, lParam);
            return 0;
            break;
        case RT_CHOICE:
            handle_game_choice(message, wParam, lParam);
            return 0;
            break;
        default:
            break;
        }
        break;        
    case WM_LBUTTONUP:
        mouse_x = GET_X_LPARAM(lParam);
        mouse_y = GET_Y_LPARAM(lParam);
        map_x = map_data.map_sx + mouse_x;
        map_y = map_data.map_sy + mouse_y;
        event_type = event_id = 0;
        game_range.mapping(mouse_x, mouse_y, &event_type, &event_id);
        set_mouse_hand_position(mouse_x, mouse_y);
        set_mouse_hand_point_info(event_type, event_id, map_x, map_y);    
        switch(event_type)
        {
        case RT_TALK:
            handle_game_talk(message, wParam, lParam);
            break;
        case RT_CHOICE:
            handle_game_choice(message, wParam, lParam);
            break;
        default:
            break;        
        }            
        break;                
    }
    return  1;
}
//-------------------------------------------------------------------------
//沒有SHIFT鍵按住的情況     handle_noshift_press
//      左鍵控制            handle_noshift_press_left_mouse
//        點在道具上面      handle_noshift_press_left_mouse_item
//              在原地丟棄道具
//        點在非道具上面    handle_noshift_press_left_mouse_skill
//              使用技能
//                  蓄力技能---------------------原地釋放
//                  有炸法術組件的技能-----------移動到釋放範圍的釋放
//                  沒有法術組件的技能-----------移動到釋放範圍的釋放
//                  光環技能---------------------甚麼都不作
//      右鍵控制            handle_noshift_press_right_mouse
//        點在道具上面      handle_noshift_press_right_mouse_item
//              甚麼都不作
//        點在非道具上面    handle_noshift_press_right_mouse_skill
//              使用技能
//                  蓄力技能---------------------原地釋放
//                  有炸法術組件的技能-----------原地釋放
//                  沒有法術組件的技能-----------移動到釋放範圍的釋放
//                  光環技能---------------------甚麼都不作
//
//有SHIFT鍵按住的情況       handle_shift_press
//      左鍵控制            handle_shift_press_left_mouse
//        點在道具上面      handle_shift_press_left_mouse_item
//              在原地丟棄道具
//        點在非道具上面        
//              使用技能    handle_shift_press_left_mouse_skill
//                  蓄力技能---------------------原地釋放
//                  有炸法術組件的技能-----------原地釋放
//                  沒有法術組件的技能-----------原地釋放
//                  光環技能---------------------甚麼都不作
//      右鍵控制            handle_shift_press_right_mouse
//        點在道具上面      handle_shift_press_right_mouse_item
//              甚麼都不作
//        點在非道具上面    handle_shift_press_right_mouse_skill
//              使用技能
//                  蓄力技能---------------------原地釋放
//                  有炸法術組件的技能-----------原地釋放
//                  沒有法術組件的技能-----------原地釋放
//                  光環技能---------------------甚麼都不作
//
//
//-------------------------------------------------------------------------
//沒有SHIFT鍵按住的情況     handle_noshift_press
//      左鍵控制            handle_noshift_press_left_mouse
//        點在道具上面      handle_noshift_press_left_mouse_item
//              在原地丟棄道具
//        點在非道具上面    handle_noshift_press_left_mouse_skill
//              使用技能
//                  蓄力技能---------------------原地釋放
//                  有炸法術組件的技能-----------移動到釋放範圍的釋放
//                  沒有法術組件的技能-----------移動到釋放範圍的釋放
//                  光環技能---------------------甚麼都不作
//      右鍵控制            handle_noshift_press_right_mouse
//        點在道具上面      handle_noshift_press_right_mouse_item
//              甚麼都不作
//        點在非道具上面    handle_noshift_press_right_mouse_skill
//              使用技能
//                  蓄力技能---------------------原地釋放
//                  有炸法術組件的技能-----------原地釋放
//                  沒有法術組件的技能-----------移動到釋放範圍的釋放
//                  光環技能---------------------甚麼都不作
//
//有SHIFT鍵按住的情況       handle_shift_press
//      左鍵控制            handle_shift_press_left_mouse
//        點在道具上面      handle_shift_press_left_mouse_item
//              在原地丟棄道具
//        點在非道具上面        
//              使用技能    handle_shift_press_left_mouse_skill
//                  蓄力技能---------------------原地釋放
//                  有炸法術組件的技能-----------原地釋放
//                  沒有法術組件的技能-----------原地釋放
//                  光環技能---------------------甚麼都不作
//      右鍵控制            handle_shift_press_right_mouse
//        點在道具上面      handle_shift_press_right_mouse_item
//              甚麼都不作
//        點在非道具上面    handle_shift_press_right_mouse_skill
//-------------------------------------------------------------------------
//對玩家輸入消息的處理
SLONG   handle_control_input(UINT message, WPARAM wParam, LPARAM lParam)
{
    USHORT	    fwKeys;
    //
    //如果沒有可以控制的..npc直接返回
    if(g_lPlayerIndex < 0)
        return  0;    
    //
    switch(message)
    {
    case WM_MOUSEMOVE:
    case WM_LBUTTONDOWN:
    case WM_LBUTTONUP:
    case WM_RBUTTONDOWN:
    case WM_RBUTTONUP:
        //和遊戲的輸入控制相關的一些消息
        fwKeys = LOWORD(wParam);
        if(fwKeys & MK_SHIFT) //判斷shift鍵是否按了下來
            handle_shift_press(message, wParam, lParam);
        else
            handle_noshift_press(message, wParam, lParam);        
        return  0;
        break;        
    case WM_IME_STRING:
        return  0;
    case WM_KEYDOWN:
        handle_maingame_hotkey_down(message, wParam, lParam);
        return  0;
    case WM_KEYUP:
        handle_maingame_hotkey_up(message, wParam, lParam);
        return  0;

    case WM_SYSKEYDOWN:
        if(wParam == VK_F10) process_shortkey_hide_or_restore_all_ui();
        return  0;
    }
    //
    return 0;
}
//沒有SHIFT鍵按住的情況
SLONG   handle_noshift_press(UINT message, WPARAM wParam, LPARAM lParam)
{
    switch(message)
    {
    case WM_LBUTTONDOWN:
        //關於鼠標左鍵的處理
        handle_noshift_press_left_mouse(message, wParam, lParam);
        return  0;    
        break;
    case WM_LBUTTONUP:
        handle_release_mouse(message, wParam, lParam);
        break;
    case WM_RBUTTONDOWN:
        handle_noshift_press_right_mouse(message, wParam, lParam);
        break;    
    case WM_RBUTTONUP:        
        handle_release_mouse(message, wParam, lParam);    
        break;    
    }
    return 0;
}
//左鍵控制            
SLONG   handle_noshift_press_left_mouse(UINT message, WPARAM wParam, LPARAM lParam)
{
    SLONG   mouse_x, mouse_y, map_x, map_y;
    SLONG   event_type, event_id;
    // 組隊
    if ( team_handle_message( message, wParam, lParam ) )
        return 0;    
    //
    mouse_x = GET_X_LPARAM(lParam);
    mouse_y = GET_Y_LPARAM(lParam);
    map_x = map_data.map_sx + mouse_x;
    map_y = map_data.map_sy + mouse_y;
    event_type = 0;
    event_id = 0;
    game_range.mapping(mouse_x, mouse_y, &event_type, &event_id);
    set_mouse_hand_position(mouse_x, mouse_y);
    set_mouse_hand_point_info(event_type, event_id, map_x, map_y);
    //
    switch(event_type)
    {
    case RT_MAP_ITEM:
        set_mouse_hand_point_kind_no(event_type, event_id);
        handle_noshift_press_left_mouse_item(message, wParam, lParam);
        break;
    case RT_NPC:
        set_mouse_hand_point_kind_no(event_type, event_id);
        handle_noshift_press_left_mouse_skill(message, wParam, lParam);
        break;        
    case RT_MAP:    
        set_mouse_hand_point_kind_no(event_type, -1);    
        handle_noshift_press_left_mouse_skill(message, wParam, lParam);
        break;        
    default:
        break;
    }
    return  0;
}
//點在道具上面      
SLONG   handle_noshift_press_left_mouse_item(UINT message, WPARAM wParam, LPARAM lParam)
{
    TPOS_ITEM	item;    
    SLONG       item_index;
    SLONG       item_x,item_y;
    //
    LOCK_CHARACTER(g_lPlayerIndex);
    GetCharacterOnMouseItem(g_lPlayerIndex, &item);
    UNLOCK_CHARACTER(g_lPlayerIndex);
    
    if(! IsItemNone(&item)) //判斷 mouse 上面是否有道具
    {
        //有道具...丟棄道具
        client_cmd_drop_item(mouse_hand.point_x, mouse_hand.point_y);
    }
    else
    {
        //沒有道具...走過..取得需要的道具
        mouse_hand.point_doing = HAND_DOING_LEFT_ITEM;
        //
        item_index = mouse_hand.point_no;
        LOCK_ITEM(item_index);
        GetZoneItemPosition(item_index, &item_x, &item_y);
        UNLOCK_ITEM(item_index);
        client_cmd_left_hit_map_item(item_x, item_y);        
    }
    return 0;    
}
//點在非道具上面    
SLONG   handle_noshift_press_left_mouse_skill(UINT message, WPARAM wParam, LPARAM lParam)
{
    TPOS_ITEM	item;
    SLONG   magic_no;
    //
    LOCK_CHARACTER(g_lPlayerIndex);
    GetCharacterOnMouseItem(g_lPlayerIndex, &item);
    magic_no = GetCharacterLeftSkill(g_lPlayerIndex);    
    UNLOCK_CHARACTER(g_lPlayerIndex);
    //    
    if(! IsItemNone(&item)) //判斷 mouse 上面是否有道具
    {
        //有道具...丟棄道具
        client_cmd_drop_item(mouse_hand.point_x, mouse_hand.point_y);
    }
    else
    {
        //
		if(magic_no >= 0 && magic_no < MAX_GAME_SKILL_BASES)
		{
            mouse_hand.point_doing = HAND_DOING_LEFT_MAGIC;
            mouse_hand.time = timeGetTime();
            //		
			exec_magic_buttondown(g_lPlayerIndex, magic_no, wParam, lParam);
		}            
        //
    }
    //
    return 0;
}
//------------------------------------------------------------------------
//----
//右鍵控制            
SLONG   handle_noshift_press_right_mouse(UINT message, WPARAM wParam, LPARAM lParam)
{
    SLONG   mouse_x, mouse_y, map_x, map_y;
    SLONG   event_type, event_id;
    // 組隊
    if ( team_handle_message( message, wParam, lParam ) )
        return 0;        
    //        
    mouse_x = GET_X_LPARAM(lParam);
    mouse_y = GET_Y_LPARAM(lParam);
    map_x = map_data.map_sx + mouse_x;
    map_y = map_data.map_sy + mouse_y;
    event_type = 0;
    event_id = 0;
    game_range.mapping(mouse_x, mouse_y, &event_type, &event_id);
    set_mouse_hand_position(mouse_x, mouse_y);
    set_mouse_hand_point_info(event_type, event_id, map_x, map_y);
    //
    switch(event_type)
    {
    case RT_MAP_ITEM:
        set_mouse_hand_point_kind_no(event_type, event_id);
        handle_noshift_press_right_mouse_item(message, wParam, lParam);
        break;
    case RT_NPC:
        set_mouse_hand_point_kind_no(event_type, event_id);
        handle_noshift_press_right_mouse_skill(message, wParam, lParam);
        break;        
    case RT_MAP:    
        set_mouse_hand_point_kind_no(event_type, -1);    
        handle_noshift_press_right_mouse_skill(message, wParam, lParam);
        break;        
    default:
        break;
    }
    return  0;
}
//點在道具上面
SLONG   handle_noshift_press_right_mouse_item(UINT message, WPARAM wParam, LPARAM lParam)
{
    TPOS_ITEM	item;    
    //
    LOCK_CHARACTER(g_lPlayerIndex);
    GetCharacterOnMouseItem(g_lPlayerIndex, &item);
    UNLOCK_CHARACTER(g_lPlayerIndex);
    
    if(! IsItemNone(&item)) //判斷 mouse 上面是否有道具
    {
        //有道具..
        handle_noshift_press_right_mouse_skill(message, wParam, lParam);
    }
    else
    {
        //沒有道具..
        handle_noshift_press_right_mouse_skill(message, wParam, lParam);
        //
    }
    return 0;    

}
//點在非道具上面
SLONG   handle_noshift_press_right_mouse_skill(UINT message, WPARAM wParam, LPARAM lParam)
{
    TPOS_ITEM	item;
    SLONG   magic_no;
    //
    LOCK_CHARACTER(g_lPlayerIndex);
    GetCharacterOnMouseItem(g_lPlayerIndex, &item);
    magic_no = GetCharacterRightSkill(g_lPlayerIndex);    
    UNLOCK_CHARACTER(g_lPlayerIndex);

    
    if(! IsItemNone(&item)) //判斷 mouse 上面是否有道具
    {
        //有道具...丟棄道具
        client_cmd_drop_item(mouse_hand.point_x, mouse_hand.point_y);
    }
    else
    {
        //
		if(magic_no >= 0 && magic_no < MAX_GAME_SKILL_BASES)
		{
            mouse_hand.point_doing = HAND_DOING_RIGHT_MAGIC;
            mouse_hand.time = timeGetTime();    		
            //
			exec_magic_buttondown(g_lPlayerIndex, magic_no, wParam, lParam);
		}            
        //
    }
    //
    return 0;
}
//有SHIFT鍵按住的情況
SLONG   handle_shift_press(UINT message, WPARAM wParam, LPARAM lParam)
{
    switch(message)
    {
    case WM_LBUTTONDOWN:
    case WM_LBUTTONUP:
        //關於鼠標左鍵的處理
        handle_shift_press_left_mouse(message, wParam, lParam);
        return  0;
    case WM_RBUTTONDOWN:
    case WM_RBUTTONUP:        
        handle_shift_press_right_mouse(message, wParam, lParam);
        break;    
    }
    return 0;
}
//左鍵控制
SLONG   handle_shift_press_left_mouse(UINT message, WPARAM wParam, LPARAM lParam)
{
    SLONG   mouse_x, mouse_y, map_x, map_y;
    SLONG   event_type, event_id;
    //
    mouse_x = GET_X_LPARAM(lParam);
    mouse_y = GET_Y_LPARAM(lParam);
    map_x = map_data.map_sx + mouse_x;
    map_y = map_data.map_sy + mouse_y;
    event_type = 0;
    event_id = 0;
    game_range.mapping(mouse_x, mouse_y, &event_type, &event_id);
    set_mouse_hand_position(mouse_x, mouse_y);
    set_mouse_hand_point_info(event_type, event_id, map_x, map_y);
    //
    switch(event_type)
    {
    case RT_MAP_ITEM:
        set_mouse_hand_point_kind_no(event_type, event_id);
        handle_shift_press_left_mouse_item(message, wParam, lParam);
        break;
    case RT_NPC:
        set_mouse_hand_point_kind_no(event_type, event_id);
        handle_shift_press_left_mouse_skill(message, wParam, lParam);
        break;        
    case RT_MAP:    
        set_mouse_hand_point_kind_no(event_type, -1);    
        handle_shift_press_left_mouse_skill(message, wParam, lParam);
        break;        
    default:
        break;
    }
    return  0;

}
//點在道具上面
SLONG   handle_shift_press_left_mouse_item(UINT message, WPARAM wParam, LPARAM lParam)
{
    TPOS_ITEM	item;    
    //
    LOCK_CHARACTER(g_lPlayerIndex);
    GetCharacterOnMouseItem(g_lPlayerIndex, &item);
    UNLOCK_CHARACTER(g_lPlayerIndex);
    
    if(! IsItemNone(&item)) //判斷 mouse 上面是否有道具
    {
        //有道具...丟棄道具
        client_cmd_drop_item(mouse_hand.point_x, mouse_hand.point_y);
    }
    else
    {
        //沒有道具...在原地使用技能
        handle_shift_press_left_mouse_skill(message, wParam, lParam);
        //
    }
    return 0;    

}
//使用技能
SLONG   handle_shift_press_left_mouse_skill(UINT message, WPARAM wParam, LPARAM lParam)
{
    //原地使用技能
    TPOS_ITEM	item;
    SLONG   magic_no;
    //
    LOCK_CHARACTER(g_lPlayerIndex);
    GetCharacterOnMouseItem(g_lPlayerIndex, &item);
    magic_no = GetCharacterLeftSkill(g_lPlayerIndex);    
    UNLOCK_CHARACTER(g_lPlayerIndex);

    
    if(! IsItemNone(&item)) //判斷 mouse 上面是否有道具
    {
        //有道具...丟棄道具
        client_cmd_drop_item(mouse_hand.point_x, mouse_hand.point_y);
    }
    else
    {
        //
		if(magic_no >= 0 && magic_no < MAX_GAME_SKILL_BASES)
		{
            mouse_hand.point_doing = HAND_DOING_LEFT_MAGIC;
            mouse_hand.time = timeGetTime();
            //		
			exec_magic_buttondown(g_lPlayerIndex, magic_no, wParam, lParam);
		}            
        //
    }
    //
    return 0;
}
//右鍵控制
SLONG   handle_shift_press_right_mouse(UINT message, WPARAM wParam, LPARAM lParam)
{
    SLONG   mouse_x, mouse_y, map_x, map_y;
    SLONG   event_type, event_id;
    //
    mouse_x = GET_X_LPARAM(lParam);
    mouse_y = GET_Y_LPARAM(lParam);
    map_x = map_data.map_sx + mouse_x;
    map_y = map_data.map_sy + mouse_y;
    event_type = 0;
    event_id = 0;
    game_range.mapping(mouse_x, mouse_y, &event_type, &event_id);
    set_mouse_hand_position(mouse_x, mouse_y);
    set_mouse_hand_point_info(event_type, event_id, map_x, map_y);
    //
    switch(event_type)
    {
    case RT_MAP_ITEM:
        set_mouse_hand_point_kind_no(event_type, event_id);
        handle_shift_press_right_mouse_item(message, wParam, lParam);
        break;
    case RT_NPC:
        set_mouse_hand_point_kind_no(event_type, event_id);
        handle_shift_press_right_mouse_skill(message, wParam, lParam);
        break;        
    case RT_MAP:    
        set_mouse_hand_point_kind_no(event_type, -1);    
        handle_shift_press_right_mouse_skill(message, wParam, lParam);
        break;        
    default:
        break;
    }
    return  0;
}
//點在道具上面
SLONG   handle_shift_press_right_mouse_item(UINT message, WPARAM wParam, LPARAM lParam)
{
    TPOS_ITEM	item;    
    //
    LOCK_CHARACTER(g_lPlayerIndex);
    GetCharacterOnMouseItem(g_lPlayerIndex, &item);
    UNLOCK_CHARACTER(g_lPlayerIndex);
    
    if(! IsItemNone(&item)) //判斷 mouse 上面是否有道具
    {
        //有道具...丟棄道具
        //不作任何的事情
    }
    else
    {
        //沒有道具..
        handle_shift_press_right_mouse_skill(message, wParam, lParam);
        //
    }
    return 0;    
}
//點在非道具上面
SLONG   handle_shift_press_right_mouse_skill(UINT message, WPARAM wParam, LPARAM lParam)
{
    TPOS_ITEM	item;
    SLONG   magic_no;
    //
    LOCK_CHARACTER(g_lPlayerIndex);
    GetCharacterOnMouseItem(g_lPlayerIndex, &item);
    magic_no = GetCharacterRightSkill(g_lPlayerIndex);    
    UNLOCK_CHARACTER(g_lPlayerIndex);

    
    if(! IsItemNone(&item)) //判斷 mouse 上面是否有道具
    {
        //有道具...丟棄道具
        //不作任何的事情
    }
    else
    {
        //
		if(magic_no >= 0 && magic_no < MAX_GAME_SKILL_BASES)
		{
            mouse_hand.point_doing = HAND_DOING_RIGHT_MAGIC;
            mouse_hand.time = timeGetTime();    		
            //
			exec_magic_buttondown(g_lPlayerIndex, magic_no, wParam, lParam);
		}            
        //
    }
    //
    return 0;
}
//所有的鼠標的..up消息的處理都一樣..使用同樣的函數...釋放鼠標按鍵
SLONG   handle_release_mouse(UINT message, WPARAM wParam, LPARAM lParam)
{
    SLONG   magic_no;
    //
    //
    LOCK_CHARACTER(g_lPlayerIndex);
    magic_no = GetCharacterRightSkill(g_lPlayerIndex);    
    UNLOCK_CHARACTER(g_lPlayerIndex);
    //
    if(magic_no >= 0 && magic_no < MAX_GAME_SKILL_BASES)
    {
        //
        exec_magic_buttonup(g_lPlayerIndex, magic_no, wParam, lParam);
        //
        mouse_hand.point_doing = HAND_DOING_NOTHING;
        mouse_hand.time = timeGetTime();
    }        
    //    
        
    return 0;
}
SLONG   handle_maingame_mousemove(UINT message, WPARAM wParam, LPARAM lParam)
{
    SLONG   mouse_x, mouse_y, map_x, map_y;
    SLONG   event_type, event_id;
    //ULONG   curr_time;
    //SLONG   npc_x, npc_y, npc_z, dx, dy;

    mouse_x = GET_X_LPARAM(lParam);
    mouse_y = GET_Y_LPARAM(lParam);
    map_x = map_data.map_sx + mouse_x;
    map_y = map_data.map_sy + mouse_y;
    event_type = event_id = 0;
    game_range.mapping(mouse_x, mouse_y, &event_type, &event_id);
    set_mouse_hand_position(mouse_x, mouse_y);
    set_mouse_hand_point_position(map_x, map_y);
    //set_mouse_hand_point_info(event_type, event_id, map_x, map_y);
    if(wParam & MK_LBUTTON) //Left drag
    {
    }
    else if(wParam & MK_RBUTTON) //Right drag
    {
    }
    else //No drag, just move.
    {
        switch(event_type)
        {
        case UIMAP_EVENT:
            set_mouse_hand_point_info(event_type, event_id, map_x, map_y);
            uimap_data.hilight_id = mouse_hand.point_no;    //point_no as event_id
            break;

        case UIMAPSTATE_EVENT:
            set_mouse_hand_point_info(event_type, event_id, map_x, map_y);
            handle_ui_mapstate(message, wParam, lParam);
            break;

        case UIMAPITEM_EVENT:
            set_mouse_hand_point_info(event_type, event_id, map_x, map_y);
            handle_ui_mapitem(message, wParam, lParam);
            break;

        case UIMAPTASK_EVENT:
            set_mouse_hand_point_info(event_type, event_id, map_x, map_y);
            handle_ui_maptask(message, wParam, lParam);
            break;

        case UIMAPSHIP_EVENT:
            set_mouse_hand_point_info(event_type, event_id, map_x, map_y);
            handle_ui_mapship(message, wParam, lParam);
            break;

        case UIMAPSKILL_EVENT:
            set_mouse_hand_point_info(event_type, event_id, map_x, map_y);
            handle_ui_mapskill(message, wParam, lParam);
            break;

        default:
            set_mouse_hand_point_info(event_type, event_id, map_x, map_y);
            uimap_data.hilight_id = 0;
            break;
        }
    }
    return  0;
}

// mark by lijun 2003-04-16
/*

SLONG   handle_maingame_lbuttondown(UINT message, WPARAM wParam, LPARAM lParam)
{
    SLONG   mouse_x, mouse_y, map_x, map_y;
    SLONG   event_type, event_id;
    //SLONG   magic_no;

    //如果左鍵或者右鍵一直被按下而沒有放開, 則直接返回.
    if(mouse_hand.left_down.doing != HAND_DOING_NOTHING 
        || mouse_hand.right_down.doing != HAND_DOING_NOTHING)
        return  0;

    if(g_lPlayerIndex < 0)
        return  0;

    // 組隊
    if ( team_handle_message( message, wParam, lParam ) )
        return 0;
    //
    mouse_x = GET_X_LPARAM(lParam);
    mouse_y = GET_Y_LPARAM(lParam);
    map_x = map_data.map_sx + mouse_x;
    map_y = map_data.map_sy + mouse_y;
    event_type = event_id = 0;
    game_range.mapping(mouse_x, mouse_y, &event_type, &event_id);
    set_mouse_hand_position(mouse_x, mouse_y);
    set_mouse_hand_point_info(event_type, event_id, map_x, map_y);

    switch(event_type)
    {
    case RT_MAP:
        handle_map_map(message, wParam, lParam);
        break;
    case RT_MAP_ITEM:
        handle_map_item(message, wParam, lParam);
        break;
    case RT_NPC:
        handle_map_npc(message, wParam, lParam);
        break;

    case UIMAP_EVENT:
        exec_left_hit_uimap(event_id);
        break;
    case UIMAPSTATE_EVENT:
        handle_ui_mapstate(message, wParam, lParam);
        break;
    case UIMAPITEM_EVENT:
        handle_ui_mapitem(message, wParam, lParam);
        break;
    case UIMAPTASK_EVENT:
        handle_ui_maptask(message, wParam, lParam);
        break;
    case UIMAPSHIP_EVENT:
        handle_ui_mapship(message, wParam, lParam);
        break;
    case UIMAPSKILL_EVENT:
        handle_ui_mapskill(message, wParam, lParam);
        break;

	case RT_TALK:
		handle_game_talk(message, wParam, lParam);
		break;
	case RT_CHOICE:
		handle_game_choice(message, wParam, lParam);
		break;

    default:
        break;
    }
    return  0;
}


SLONG   handle_maingame_lbuttonup(UINT message, WPARAM wParam, LPARAM lParam)
{
    SLONG   mouse_x, mouse_y, map_x, map_y;
    SLONG   event_type, event_id;
    SLONG   item_index, item_x, item_y;
	TPOS_ITEM	item;

    mouse_x = GET_X_LPARAM(lParam);
    mouse_y = GET_Y_LPARAM(lParam);
    map_x = map_data.map_sx + mouse_x;
    map_y = map_data.map_sy + mouse_y;
    event_type = event_id = 0;
    game_range.mapping(mouse_x, mouse_y, &event_type, &event_id);
    set_mouse_hand_position(mouse_x, mouse_y);
    set_mouse_hand_point_info(event_type, event_id, map_x, map_y);

    switch(mouse_hand.left_down.doing)
    {
    case HAND_DOING_CTRL_ITEM:
        if(mouse_hand.left_down.type == mouse_hand.point_kind && mouse_hand.left_down.id == mouse_hand.point_no)
        {
            LOCK_CHARACTER(g_lPlayerIndex);
			GetCharacterOnMouseItem(g_lPlayerIndex, &item);
            UNLOCK_CHARACTER(g_lPlayerIndex);
            
            if(! IsItemNone(&item))
            {
                client_cmd_drop_item(mouse_hand.point_x, mouse_hand.point_y);
            }
            else
            {
                item_index = mouse_hand.point_no;
                LOCK_ITEM(item_index);
				GetZoneItemPosition(item_index, &item_x, &item_y);
                UNLOCK_ITEM(item_index);
                
                client_cmd_left_hit_map_item(item_x, item_y);
            }

            mouse_hand.left_down.type = 0;
            mouse_hand.left_down.id = 0;
        }
        break;
    default:
		{
			switch(event_type)
			{
			case RT_TALK:
				handle_game_talk(message, wParam, lParam);
				break;
			case RT_CHOICE:
				handle_game_choice(message, wParam, lParam);
				break;
			}
		}
        break;
    }
    mouse_hand.left_down.doing = HAND_DOING_NOTHING;

    return  0;
}


SLONG   handle_maingame_rbuttondown(UINT message, WPARAM wParam, LPARAM lParam)
{
    SLONG   mouse_x, mouse_y, map_x, map_y;
    SLONG   event_type, event_id;
	TPOS_ITEM	item;
    SLONG   magic_no;
	//SLONG	npc_x, npc_y, npc_z;
	//SLONG	is_fight;
    //SLONG   dx, dy;

    //如果左鍵或者右鍵一直被按下而沒有放開, 則直接返回.
    if(mouse_hand.left_down.doing != HAND_DOING_NOTHING 
        || mouse_hand.right_down.doing != HAND_DOING_NOTHING)
        return  0;

    if(g_lPlayerIndex < 0)
        return  0;

    // 組隊
    if ( team_handle_message( message, wParam, lParam ) )
        return 0;

    LOCK_CHARACTER(g_lPlayerIndex);
	GetCharacterOnMouseItem(g_lPlayerIndex, &item);
    magic_no = GetCharacterRightSkill(g_lPlayerIndex);
    UNLOCK_CHARACTER(g_lPlayerIndex);

    mouse_x = GET_X_LPARAM(lParam);
    mouse_y = GET_Y_LPARAM(lParam);
    map_x = map_data.map_sx + mouse_x;
    map_y = map_data.map_sy + mouse_y;
    event_type = event_id = 0;
    game_range.mapping(mouse_x, mouse_y, &event_type, &event_id);
    set_mouse_hand_position(mouse_x, mouse_y);
    set_mouse_hand_point_info(event_type, event_id, map_x, map_y);
    switch(event_type)
    {
    case UIMAP_EVENT:
        exec_right_hit_uimap(event_id);
        break;
    case UIMAPITEM_EVENT:
		handle_ui_mapitem(message, wParam, lParam);
		break;
    default:
		if(magic_no >= 0 && magic_no < MAX_GAME_SKILL_BASES)
		{
			exec_magic_buttondown(g_lPlayerIndex, magic_no, wParam, lParam);
		}
        break;
	}
    return  0;
}


SLONG   handle_maingame_rbuttonup(UINT message, WPARAM wParam, LPARAM lParam)
{
    SLONG   magic_no;
    //
    LOCK_CHARACTER(g_lPlayerIndex);
    magic_no = GetCharacterRightSkill(g_lPlayerIndex);
    UNLOCK_CHARACTER(g_lPlayerIndex);
    //
    if(magic_no >= 0 && magic_no < MAX_GAME_SKILL_BASES)
    {
        exec_magic_buttonup(g_lPlayerIndex, magic_no, wParam, lParam);
    }
    return 0;
}


SLONG   handle_maingame_mousemove(UINT message, WPARAM wParam, LPARAM lParam)
{
    SLONG   mouse_x, mouse_y, map_x, map_y;
    SLONG   event_type, event_id;
    ULONG   curr_time;
    SLONG   npc_x, npc_y, npc_z, dx, dy;

    mouse_x = GET_X_LPARAM(lParam);
    mouse_y = GET_Y_LPARAM(lParam);
    map_x = map_data.map_sx + mouse_x;
    map_y = map_data.map_sy + mouse_y;
    event_type = event_id = 0;
    game_range.mapping(mouse_x, mouse_y, &event_type, &event_id);
    set_mouse_hand_position(mouse_x, mouse_y);
    set_mouse_hand_point_position(map_x, map_y);
    //set_mouse_hand_point_info(event_type, event_id, map_x, map_y);

    if(wParam & MK_LBUTTON) //Left drag
    {
        switch(mouse_hand.left_down.doing)
        {
        case HAND_DOING_CTRL_MAP:
            mouse_hand.left_down.x = mouse_hand.x;
            mouse_hand.left_down.y = mouse_hand.y;
            
            curr_time = timeGetTime();
            if(curr_time - mouse_hand.left_down.time > DRAG_EVENT_PERIOD_MAP)
            {
                LOCK_CHARACTER(g_lPlayerIndex);
				GetCharacterPosition(g_lPlayerIndex, &npc_x, &npc_y, &npc_z);
                UNLOCK_CHARACTER(g_lPlayerIndex);
                dx = abs(mouse_hand.point_x - npc_x);
                dy = abs(mouse_hand.point_y - npc_y);
                if(dx >= INVALID_MOUSE_RANGE_HALF_WIDTH || dy >= INVALID_MOUSE_RANGE_HALF_HEIGHT)
                {
                    client_cmd_left_hit_map(mouse_hand.point_x, mouse_hand.point_y);
                }
                mouse_hand.left_down.time = curr_time;
            }
            set_mouse_hand_point_kind_no(0, 0);
            break;

        default:
            set_mouse_hand_point_kind_no(event_type, event_id);
            break;
        }
    }
    else if(wParam & MK_RBUTTON) //Right drag
    {
        switch(mouse_hand.right_down.doing)
        {
        case HAND_DOING_CTRL_MAP:
            mouse_hand.right_down.x = mouse_hand.x;
            mouse_hand.right_down.y = mouse_hand.y;
            
            curr_time = timeGetTime();
            if(curr_time - mouse_hand.right_down.time > DRAG_EVENT_PERIOD_MAP)
            {
                LOCK_CHARACTER(g_lPlayerIndex);
				GetCharacterPosition(g_lPlayerIndex, &npc_x, &npc_y, &npc_z);
                UNLOCK_CHARACTER(g_lPlayerIndex);

                dx = abs(mouse_hand.point_x - npc_x);
                dy = abs(mouse_hand.point_y - npc_y);
                if(dx >= INVALID_MOUSE_RANGE_HALF_WIDTH || dy >= INVALID_MOUSE_RANGE_HALF_HEIGHT)
                {
                    client_cmd_right_hit_map(mouse_hand.point_x, mouse_hand.point_y);
                }
                mouse_hand.right_down.time = curr_time;
            }
            set_mouse_hand_point_kind_no(0, 0);
            break;

        case HAND_DOING_CTRL_MAGIC:
            set_magic_area_dest_position(mouse_hand.point_x, mouse_hand.point_y);
            set_mouse_hand_point_kind_no(0, 0);
            break;

        default:
            set_mouse_hand_point_kind_no(event_type, event_id);
            break;
        }
    }
    else //No drag, just move.
    {
        switch(event_type)
        {
        case UIMAP_EVENT:
            set_mouse_hand_point_info(event_type, event_id, map_x, map_y);
            uimap_data.hilight_id = mouse_hand.point_no;    //point_no as event_id
            break;

        case UIMAPSTATE_EVENT:
            set_mouse_hand_point_info(event_type, event_id, map_x, map_y);
            handle_ui_mapstate(message, wParam, lParam);
            break;

        case UIMAPITEM_EVENT:
            set_mouse_hand_point_info(event_type, event_id, map_x, map_y);
            handle_ui_mapitem(message, wParam, lParam);
            break;

        case UIMAPTASK_EVENT:
            set_mouse_hand_point_info(event_type, event_id, map_x, map_y);
            handle_ui_maptask(message, wParam, lParam);
            break;

        case UIMAPSHIP_EVENT:
            set_mouse_hand_point_info(event_type, event_id, map_x, map_y);
            handle_ui_mapship(message, wParam, lParam);
            break;

        case UIMAPSKILL_EVENT:
            set_mouse_hand_point_info(event_type, event_id, map_x, map_y);
            handle_ui_mapskill(message, wParam, lParam);
            break;

        default:
            set_mouse_hand_point_info(event_type, event_id, map_x, map_y);
            uimap_data.hilight_id = 0;
            break;
        }
    }
    return  0;
}

//---
//  當mouse點在地圖上的時候需要做的輸入處理
//---
SLONG   handle_map_map(UINT message, WPARAM wParam, LPARAM lParam)
{
    ULONG   curr_time;
    SLONG   dx, dy, npc_x, npc_y, npc_z;
    SLONG   magic_no, is_fight;

    switch(message)
    {
    case WM_LBUTTONDOWN:
        {
    
			TPOS_ITEM	item;
			USHORT	fwKeys;

			fwKeys = LOWORD(wParam);
			if(fwKeys & MK_SHIFT) //Mouse left button down with shift.
			{
				SLONG	dx, dy;
				SLONG	dir;
				//
				LOCK_CHARACTER(g_lPlayerIndex);
				GetCharacterPosition(g_lPlayerIndex, &npc_x, &npc_y, &npc_z);
				UNLOCK_CHARACTER(g_lPlayerIndex);
				dx = mouse_hand.point_x - npc_x;
				dy = mouse_hand.point_y - npc_y;
				if(dx != 0 || dy != 0)
					dir = ApproachCharacterDir(dx, dy);

				client_cmd_request_change_dir(dir);
			}
			else
			{
				LOCK_CHARACTER(g_lPlayerIndex);
				GetCharacterOnMouseItem(g_lPlayerIndex, &item);
				UNLOCK_CHARACTER(g_lPlayerIndex);

				if(! IsItemNone(&item))
				{
					client_cmd_drop_item(mouse_hand.point_x, mouse_hand.point_y);
				}
				else
				{
					
					LOCK_CHARACTER(g_lPlayerIndex);
					GetCharacterPosition(g_lPlayerIndex, &npc_x, &npc_y, &npc_z);
					UNLOCK_CHARACTER(g_lPlayerIndex);
					
					if(mouse_hand.left_down.doing != HAND_DOING_CTRL_MAP)
					{
						dx = abs(mouse_hand.point_x - npc_x);
						dy = abs(mouse_hand.point_y - npc_y);
						if(dx >= INVALID_MOUSE_RANGE_HALF_WIDTH || dy >= INVALID_MOUSE_RANGE_HALF_HEIGHT)
						{
							client_cmd_left_hit_map(mouse_hand.point_x, mouse_hand.point_y);
							
							mouse_hand.left_down.type = mouse_hand.point_kind;
							mouse_hand.left_down.doing = HAND_DOING_CTRL_MAP;
							mouse_hand.left_down.time = timeGetTime();
							mouse_hand.left_down.x = mouse_hand.x;
							mouse_hand.left_down.y = mouse_hand.y;
						}
					}
					else
					{
						mouse_hand.left_down.x = mouse_hand.x;
						mouse_hand.left_down.y = mouse_hand.y;
						curr_time = timeGetTime();
						if(curr_time - mouse_hand.left_down.time > DRAG_EVENT_PERIOD_MAP)
						{
							dx = abs(mouse_hand.point_x - npc_x);
							dy = abs(mouse_hand.point_y - npc_y);
							if(dx >= INVALID_MOUSE_RANGE_HALF_WIDTH || dy >= INVALID_MOUSE_RANGE_HALF_HEIGHT)
							{
								client_cmd_left_hit_map(mouse_hand.point_x, mouse_hand.point_y);
							}
							
							mouse_hand.left_down.time = curr_time;
						}
					}
				}
			}
        }
        break;
    case WM_RBUTTONDOWN:
        {
			TPOS_ITEM	item;
            
            LOCK_CHARACTER(g_lPlayerIndex);
			GetCharacterOnMouseItem(g_lPlayerIndex, &item);
            UNLOCK_CHARACTER(g_lPlayerIndex);
            
            if(! IsItemNone(&item))
            {
                client_cmd_drop_item(mouse_hand.point_x, mouse_hand.point_y);
            }
            else
            {
                LOCK_CHARACTER(g_lPlayerIndex);
                GetCharacterPosition(g_lPlayerIndex, &npc_x, &npc_y, &npc_z);
                is_fight = IsCharacterOnFightState(g_lPlayerIndex);
                UNLOCK_CHARACTER(g_lPlayerIndex);

                switch(mouse_hand.right_down.doing)
                {
                case HAND_DOING_CTRL_MAP:
                    mouse_hand.right_down.x = mouse_hand.x;
                    mouse_hand.right_down.y = mouse_hand.y;
                    curr_time = timeGetTime();
                    if(curr_time - mouse_hand.right_down.time > DRAG_EVENT_PERIOD_MAP)
                    {
                        dx = abs(mouse_hand.point_x - npc_x);
                        dy = abs(mouse_hand.point_y - npc_y);
                        if(dx >= INVALID_MOUSE_RANGE_HALF_WIDTH || dy >= INVALID_MOUSE_RANGE_HALF_HEIGHT)
                        {
                            client_cmd_right_hit_map(mouse_hand.point_x, mouse_hand.point_y);
                        }
                        mouse_hand.right_down.time = curr_time;
                    }
                    break;
                default:
                    {
                        LOCK_CHARACTER(g_lPlayerIndex);
                        magic_no = GetCharacterRightSkill(g_lPlayerIndex);
                        UNLOCK_CHARACTER(g_lPlayerIndex);

                        switch(magic_no)
                        {
                        case MAGIC_NO_CLASH:    //衝撞
                            dx = abs(mouse_hand.point_x - npc_x);
                            dy = abs(mouse_hand.point_y - npc_y);
                            if(dx >= INVALID_MOUSE_RANGE_HALF_WIDTH || dy >= INVALID_MOUSE_RANGE_HALF_HEIGHT)
                            {
                                client_cmd_right_hit_map(mouse_hand.point_x, mouse_hand.point_y);

                                mouse_hand.right_down.type = mouse_hand.point_kind;
                                mouse_hand.right_down.doing = HAND_DOING_CTRL_MAGIC;
                                mouse_hand.right_down.time = timeGetTime();
                                mouse_hand.right_down.x = mouse_hand.x;
                                mouse_hand.right_down.y = mouse_hand.y;

                                set_magic_area_type(MAGIC_AREA_TYPE_LINE);
                                set_magic_area_orig_position(npc_x, npc_y);
                                set_magic_area_dest_position(mouse_hand.point_x, mouse_hand.point_y);
                                if(is_fight) set_magic_area_visible(true);
                            }
                            break;
                        default:
                            dx = abs(mouse_hand.point_x - npc_x);
                            dy = abs(mouse_hand.point_y - npc_y);
                            if(dx >= INVALID_MOUSE_RANGE_HALF_WIDTH || dy >= INVALID_MOUSE_RANGE_HALF_HEIGHT)
                            {
                                client_cmd_right_hit_map(mouse_hand.point_x, mouse_hand.point_y);

                                mouse_hand.right_down.type = mouse_hand.point_kind;
                                mouse_hand.right_down.doing = HAND_DOING_CTRL_MAP;
                                mouse_hand.right_down.time = timeGetTime();
                                mouse_hand.right_down.x = mouse_hand.x;
                                mouse_hand.right_down.y = mouse_hand.y;
                            }
                            break;
                        }
                    }
                    break;
                }
            }
        }
        break;
    }
    return  0;
}


SLONG   handle_map_npc(UINT message, WPARAM wParam, LPARAM lParam)
{
    ULONG   curr_time;
    SLONG   magic_no;

    switch(message)
    {
    case WM_LBUTTONDOWN:
        {
            LOCK_CHARACTER(g_lPlayerIndex);
            magic_no = GetCharacterLeftSkill(g_lPlayerIndex);
            UNLOCK_CHARACTER(g_lPlayerIndex);
            

            if(mouse_hand.left_down.doing != HAND_DOING_CTRL_NPC)
            {
                client_cmd_left_hit_npc(mouse_hand.point_no);
                mouse_hand.left_down.type = mouse_hand.point_kind;
                mouse_hand.left_down.id = mouse_hand.point_no;
                mouse_hand.left_down.doing = HAND_DOING_CTRL_NPC;
                mouse_hand.left_down.time = timeGetTime();
            }
            else
            {
                curr_time = timeGetTime();
                if(curr_time - mouse_hand.left_down.time > DRAG_EVENT_PERIOD_NPC)
                {
                    client_cmd_left_hit_npc(mouse_hand.point_no);
                    mouse_hand.left_down.time = curr_time;
                }
            }
        }
        break;
    case WM_RBUTTONDOWN:
        if(timer_tick03 > 33)
        {
            LOCK_CHARACTER(g_lPlayerIndex);
            magic_no = GetCharacterRightSkill(g_lPlayerIndex);
            UNLOCK_CHARACTER(g_lPlayerIndex);
            switch(magic_no)
            {
            case MAGIC_NO_CLASH:    //衝撞
                client_cmd_right_hit_map(mouse_hand.point_x, mouse_hand.point_y);
                break;
            default:
                client_cmd_right_hit_npc(mouse_hand.point_no);
                break;
            }
            timer_tick03 = 0;
        }
        break;
    }
    

    return  0;
}



SLONG   handle_map_item(UINT message, WPARAM wParam, LPARAM lParam)
{
    //SLONG   item_index, item_x, item_y;
    //ITEM_ESSE ie;

    switch(message)
    {
    case WM_LBUTTONDOWN:
        mouse_hand.left_down.type = mouse_hand.point_kind;
        mouse_hand.left_down.id = mouse_hand.point_no;
        mouse_hand.left_down.doing = HAND_DOING_CTRL_ITEM;
        break;
    case WM_RBUTTONDOWN:
        break;
    default:
        break;
    }
    return  0;
}

*/
//-------------------------------------------------------------------------
//  End.
//-------------------------------------------------------------------------
