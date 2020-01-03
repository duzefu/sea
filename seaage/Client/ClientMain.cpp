/*
**  ClientMain.cpp
**  client main functions.
**
**  Jack, 2002.5.6.  
*/
#include "MainFun.h"
#include "NetGE_MainFunc.h"
#include "ClientMain.h"
#include "CRange.h"
#include "Map.h"
#include "Npc.h"
#include "UI.h"
#include "UIAccMan.h"
#include "UILoading.h"
#include "FreeProcess.h"
#include "MainGame.h"
#include "ErrorMsg.h"
#include "HrtBeat.h"
#include "PosData.h"
#include "Magic.h"
#include "Sge.h"
#include "Config.h"
#include "CmdEvent.h"
#include "Fight.h"
#include "Weather.h"
#include "Resource.h"
#include "SecretSkill.h"
#include "UISystemMessage.h"
#include "UIGameMessage.h"
#include "UIManager.h"
#include "QQMsgBox.h"
//
#include "NetGE_Item.h"
#include "Client_Thread.h"
#include "Client_RecvMsg.h"
#include "Client_SendMsg.h"
#include "Client_Item.h"
#include "Media.h"
#include "GM_Main.h"
#include "SingleGame.h"
#include "RaysEdit.h"
//
#include "UIIconMessage.h"
#include "qqedit.h"
#include "uiinput.h"
//
#include "NetGE_Misc.h"

#ifdef  _DEBUG
#pragma comment(lib, "HNetGeHdbg.lib")
#pragma comment(lib, "ComLibdbg.lib")
#else//!_DEBUG
#pragma comment(lib, "HNetGeH.lib")
#pragma comment(lib, "ComLib.lib")
#endif//_DEBUG


#define ID_TIMER            1


DATA_FILE   *packed_data_file = NULL;   //(1) 數值部分	data.pos	<data>
DATA_FILE   *packed_menu_file = NULL;   //(2) 選單部分	menu.pos	<menu>
DATA_FILE   *packed_sound_file = NULL;  //(3) 音效部分	sound.pos	<sound>
DATA_FILE   *packed_music_file = NULL;  //(4) 音樂部分	music.pos	<music>
DATA_FILE   *packed_tile_file = NULL;   //(5) 圖素部分	tile.pos	<tile>
DATA_FILE   *packed_house_file = NULL;  //(6) 房屋部分	house.pos	<house>
DATA_FILE   *packed_map_file = NULL;    //(7) 地圖部分	map.pos	    <map>
DATA_FILE   *packed_object_file = NULL; //(8) 物件部分	object.pos	<object>
DATA_FILE	*packed_macro_file = NULL;  //(9) 劇本部分  macro.pos   <macro>
DATA_FILE   *packed_other_file = NULL;  //(10) 其他		sea.pos
DATA_FILE	*packed_npc_file = NULL;	//(11) LAND NPC npc.pos
DATA_FILE	*packed_seanpc_file = NULL;	//(11) SEA NPC seanpc.pos

//
HINSTANCE   g_hInstance;                // App instance
DWORD       g_dwAppState;               // Current state the app is in
DWORD       g_dwOldAppState;            // Old state the app was
DWORD       g_dwNextAppState;           //應用程式的下一個執行狀態
DWORD		g_dwAppEvent;				//應用程式的事件
DWORD       g_dwConnectedServerType;    // Current connected server type
LONG        g_lPlayerIndex = -1;        //玩家的 NPC 索引號
LONG        g_lPlayerMap = 0;           //玩家當前所在的地圖, 實際上目前只用來作 map_base[]的索引, 
                                        //並且固定為 0.
TCHAR       g_szPlayerZone[64];         //玩家當前所在的ZONE名稱
DWORD		g_dwZoneType;				//玩家當前所在的ZONE類型
TCHAR       g_szPlayerMap[64];          //玩家當前所在的地圖名稱
TCHAR       g_szPlayerMainName[64];     //玩家的名稱
DWORD       g_dwHeartBeat = 0;          //心跳次數計數
LONG		g_lIsSingleGame = 0;		//是否為單機遊戲
LONG		g_IsExitingGame = 0;		//紀錄遊戲是否正在退出(當玩家按ESC以後).

// Debug Show Range [3/28/2003] Zhang Zhaohui
//BOOL bShowRange = FALSE;

int WINAPI      WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
long FAR WINAPI ClientWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );
HRESULT FrameMove(VOID);
HRESULT RenderFrame(VOID);
HRESULT PaintWindow(VOID);
HRESULT TimerRefresh(VOID);
HRESULT HandleMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void    redraw_test_grafx(void *vbitmap);
void    exec_open_all_data_files(void);
void    exec_close_all_data_files(void);
//
void	redraw_error_exit(SLONG sx, SLONG sy, void *vbitmap);
SLONG   handle_error_exit(UINT message, WPARAM wParam, LPARAM lParam);
//--
void    test_buf(SLONG sx, SLONG sy, void *vbitmap);
//--

int gameSet(void)
{
    char    info[128];

    sprintf((char *)info, "Psalm Of Sea V%1d.%2d(Build:%s,%s)", 
		POS_CLIENT_VERSION/1000, (POS_CLIENT_VERSION % 1000) / 10,
        __DATE__, __TIME__);
    SetDDWndName( (char *)info);
    SetDDWndIcon( LoadIcon(g_hInstance, MAKEINTRESOURCE(IDI_ICON1)), 
        LoadIcon(g_hInstance, MAKEINTRESOURCE(IDI_ICON1)) );
    SetDDWndRunOnce( FALSE );
    SetDDWndScreenMode( WINDOWS_SCREEN_MODE );
//	SetDDWndScreenMode( FULL_SCREEN_MODE );
    SetDDWndScreenSize( SCREEN_WIDTH, SCREEN_HEIGHT );
    SetDDWndProc( ClientWndProc );
    SetDDWndEnableDblClk(TRUE);
    //
    return 0;
}


int gameInit(void)
{
    if( FAILED( install(system)         )) FailMsg("install system failed");
    if( FAILED( install(draw)           )) FailMsg("install draw failed");
    if( FAILED( install(timer)          )) FailMsg("install timer failed");
    if( FAILED( install(input)          )) FailMsg("install input failed");
    //
    init_user_config(&user_config);
    load_user_config(&user_config, (USTR*)"CONFIG.INI");
    debug_log_user_config(&user_config);
    //
#ifdef  BIG5_VERSION
    set_winfont_name((USTR*)GAME_FONT_NAME);
    set_winfont_support_system(SUPPORT_FONT_SYSTEM_BIG5 | SUPPORT_FONT_SYSTEM_GB );
    set_winfont_weight(FW_NORMAL);
    set_winfont_convert_big5_to_gb(true);
#endif//BIG5_VERSION

#ifdef  GB_VERSION
    set_winfont_name((USTR*)GAME_FONT_NAME);
    set_winfont_support_system(SUPPORT_FONT_SYSTEM_GB );
    set_winfont_weight(FW_NORMAL);
    set_winfont_convert_big5_to_gb(false);
#endif//GB_VERSION

    if( FAILED( install(winfont)        )) FailMsg("install winfont failed");
//    if( FAILED( install(ime)            )) FailMsg("install ime failed");
    //
    set_music_type(MUSIC_TYPE_WAVE);
    if(user_config.activate_sound)
    {
        if( FAILED( install(sound)          )) FailMsg("install sound failed");
    }
    //if( FAILED( install(cdrom_music)  )) FailMsg("install cdrom music failed");
    //if( FAILED( install(mp3)            )) FailMsg("install mp3 failed");
    //if( FAILED( install(global)         )) FailMsg("install global failed");
	InitCriticalSectionGlobals();

    if( FAILED( install(client)         )) FailMsg("install client failed");
    if( FAILED( install(heartbeat)      )) FailMsg("install heartbeat failed");

    exec_open_all_data_files();

	ClientConnectionsInit();

    if( FAILED( install(ui)             )) FailMsg("install ui failed");
    //if( FAILED( install(ripple)           )) FailMsg("install ripple failed");
    if( FAILED( install(map)            )) FailMsg("install map system failed");
    if( FAILED( install(npc)            )) FailMsg("install npc system failed");
    if( FAILED( install(sge)            )) FailMsg("install sge system failed");
    if( FAILED( install(magic)          )) FailMsg("install magic system failed");

    if( FAILED( install(weather)        )) FailMsg("install weather system failed");
    if( FAILED( install(game_data)      )) FailMsg("install game data failed");
	if( FAILED( install(item)			)) FailMsg("install item system failed");
	if( FAILED( install(event_ui)		)) FailMsg("install event ui failed");
	if( FAILED( install(gm_console)		)) FailMsg("install gm console failed");

	if( FAILED( install(iconmsg)        )) FailMsg( "Can not init Icon message." );
	if( FAILED( install(ui_input)		)) FailMsg( "Can not init ui_input." );

	set_data_file(packed_data_file);
	if(0 != InitSkillSystem())
	{
		FailMsg("Initialize skill system failed");
	}


    set_data_file(packed_menu_file);
    load_mouse_image_cursor(MOUSE_IMAGE_ARROW, (USTR *)"menu\\mouse00.cak");
    set_mouse_cursor(MOUSE_IMAGE_ARROW);
    set_mouse_spot(MOUSE_IMAGE_ARROW, 6, 1);

#ifdef  DEBUG
    //show_mouse(SHOW_WINDOW_CURSOR);
    show_mouse(SHOW_IMAGE_CURSOR);
#else//!DEBUG
    show_mouse(SHOW_IMAGE_CURSOR);
    //show_mouse(SHOW_IMAGE_CURSOR | SHOW_WINDOW_CURSOR);
#endif//DEBUG

    init_game_colors();

    //--------------------------------------------------------------------------------
    get_time((USTR*)print_rec);
    log_error(1, "System start time : %s.", print_rec);

    g_dwAppState = APPSTATE_SYSTEM_INIT;
    g_dwOldAppState = 0;
    g_dwNextAppState = 0;
	g_dwAppEvent = 0;
	g_lIsSingleGame = 0;

	set_npc_doing_functions();
    set_npc_ai_function();
    //	
	set_fight_functions();
    //
    init_secret_skill();
    init_system_message();
    init_game_message();
    init_uimap_data();
    init_minimap();

	init_media_data();

    return 0;
}


int gameMain2(void)
{
    BOOL bGotMsg;
    MSG  msg;

    
    PeekMessage( &msg, NULL, 0U, 0U, PM_NOREMOVE );
    while( WM_QUIT != msg.message  )
    {
        // Use PeekMessage() if the app is active, so we can use idle time to
        // render the scene. Else, use GetMessage() to avoid eating CPU time.
        if( g_bProgramActive )
            bGotMsg = PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE );
        else
            bGotMsg = GetMessage( &msg, NULL, 0U, 0U );

        if( bGotMsg )
        {
            // Translate and dispatch the message
            TranslateMessage( &msg );
            DispatchMessage( &msg );
        }
        else
        {
            // Render a frame during idle time (no messages are waiting)
            FrameMove();
            RenderFrame();
        }
    }
    return 0;
}


int gameMain(void)
{
	enum {MS_PER_FRAME = 40};
	DWORD	last_time, curr_time;
	SLONG	doing_flag, dur_time;
    MSG		msg;

	last_time = 0;
    while(TRUE)
    {
		doing_flag = 1;
        if(PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
        {
            if(GetMessage(&msg, NULL, 0, 0))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
				doing_flag = 0;
            }
        }

		if(doing_flag)
		{
			curr_time = timeGetTime();
			dur_time = curr_time - last_time;
			if(dur_time >= MS_PER_FRAME)
			{
				last_time = curr_time;
				FrameMove();
				RenderFrame();
			}
			else
			{
				Sleep(MS_PER_FRAME - dur_time);
			}
		}
    }
	return	0;
}


void gameExit(void)
{
	FreeSkillSystem();

    free_system_message();
    stop_heartbeat();

    exec_free_process();
    exec_close_all_data_files();

	ClientConnectionsFree();

	FreeCriticalSectionGlobals();

    get_time((USTR*)print_rec);
    log_error(1, "System end time : %s.", print_rec);
}


HRESULT PaintWindow(VOID)
{
    PAINTSTRUCT ps;

    switch(g_dwAppState)
    {
    case 0:
    default:
        BeginPaint(g_hDDWnd,&ps);
        EndPaint(g_hDDWnd,&ps);
        if( screen_buffer && g_bIsInitialized && g_hDDWnd )
            update_screen(screen_buffer);
        break;
    }
    return  0;
}



void    redraw_test_grafx(void *vbitmap)
{
    put_image_rim(380, 380, 0, 0, vbitmap);
    put_image_rim(300, 300, 210, 110, vbitmap);
}


int WINAPI  WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    g_hInstance = hInstance;
	SetRaysSDKVersion(0x00020000);
    return RaysDDWinMain( hInstance, hPrevInstance, lpCmdLine, nCmdShow );
}


long FAR WINAPI ClientWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
    switch(message)
    {
    case WM_CREATE:
        /*
        if (!SetTimer (hWnd, ID_TIMER, 50, NULL))
        {
            log_error(1, "too many clocks or timers!");
            return FALSE ;
        }
        break;
        */
        return  0;

        /*
    case WM_TIMER:
        TimerRefresh();
        return  0;
        */

    case WM_ACTIVATEAPP:
        {
            g_bProgramActive = wParam;
            if (g_bIsInitialized)
                active_modules(g_bProgramActive);
            break;
        }
    case WM_SYSCOMMAND:
        // Prevent moving/sizing and power loss in fullscreen mode
        {
            switch( wParam )
            {
            case SC_MOVE:
            case SC_SIZE:
            case SC_MAXIMIZE:
            case SC_MONITORPOWER:
                if( g_dwScreenMode == FULL_SCREEN_MODE)
                    return TRUE;
            }
            break;
        }
    case WM_GETMINMAXINFO:
        {
            // Don't allow resizing in windowed mode.  
            // Fix the size of the window to (screen width * screen height) (client size)
            MINMAXINFO* pMinMax = (MINMAXINFO*) lParam;
            DWORD   dwStyle, dwExStyle;
            RECT    rc;

            dwStyle = GetWindowLong( hWnd, GWL_STYLE );
            dwExStyle = GetWindowLong( hWnd, GWL_EXSTYLE );
            SetRect( &rc, 0, 0, g_nScreenWidth, g_nScreenHeight);
            AdjustWindowRectEx( &rc, dwStyle, NULL, dwExStyle );

            pMinMax->ptMinTrackSize.x = rc.right - rc.left;
            pMinMax->ptMinTrackSize.y = rc.bottom - rc.top;
            
            pMinMax->ptMaxTrackSize.x = pMinMax->ptMinTrackSize.x;
            pMinMax->ptMaxTrackSize.y = pMinMax->ptMinTrackSize.y;
            return 0L;
        }

    case WM_MOVE:
        {
            // Retrieve the window position after a move.
            update_display_bounds();
            return 0L;
        }
        
    case WM_SIZE:
        {
            // Check to see if we are losing our window...
            if( SIZE_MAXHIDE == wParam || SIZE_MINIMIZED == wParam )
                g_bProgramActive = FALSE;
            else
                g_bProgramActive = TRUE;

            update_display_bounds();

            if (g_bIsInitialized)
                active_modules(g_bProgramActive);
            break;
        }
        
    case WM_PAINT:
        PaintWindow();
        return  0;

    case WM_CLOSE:
    case WM_DESTROY:
        {
            //KillTimer (hWnd, ID_TIMER);
            if (g_bIsInitialized)
            {
                gameExit();
                g_bIsInitialized = 0;
            }
            FinishProc();
            PostQuitMessage(0);
            exit(0);
        }
        break;
    case WM_NCDESTROY:
        break;

    case WM_SETCURSOR:
		if((HWND)wParam != hWnd)
		{
			fnMouseInterrupt(message,wParam,lParam);
			show_mouse(SHOW_WINDOW_CURSOR);
			HandleMessage(hWnd, message, wParam, lParam);
		}
		else
		{
			fnMouseInterrupt(message,wParam,lParam);
			show_mouse(SHOW_IMAGE_CURSOR);
			HandleMessage(hWnd, message, wParam, lParam);
		}
		break;

    case WM_MOUSEMOVE:
    case WM_LBUTTONDOWN:
    case WM_LBUTTONUP:
    case WM_LBUTTONDBLCLK:
    case WM_RBUTTONDOWN:
    case WM_RBUTTONUP:
    case WM_RBUTTONDBLCLK:
    case WM_MBUTTONDOWN:
    case WM_MBUTTONUP:
    case WM_MBUTTONDBLCLK:
    case WM_MOUSEWHEEL:
    //case WM_XBUTTONDBLCLK:
    //case WM_XBUTTONDOWN:
    //case WM_XBUTTONUP:
	// Zhang Zhaohi for qqedit input 2002.4.17
        fnMouseInterrupt(message,wParam,lParam);
        HandleMessage(hWnd, message, wParam, lParam);
    return  0;

    case WM_NCMOUSEMOVE:
        fnMouseInterrupt(message,wParam,lParam);
        return  0;

    case WM_CHAR:
    case WM_IME_STRING:
        HandleMessage(hWnd, message, wParam, lParam);
        return  0;

    case WM_SYSKEYDOWN:
        HandleMessage(hWnd, message, wParam, lParam);
        return 0;

    case WM_SYSKEYUP:
        HandleMessage(hWnd, message, wParam, lParam);
        return 0;

    case WM_KEYDOWN:
        {
            switch( wParam )
            {
            case VK_SHIFT:
                break;

            case VK_F12:
                return 0;
// Zhang Zhaohui 2003.5.29
//			case VK_F9:
//				bShowRange = !bShowRange;
//				break;

            default:
                //Jack, 2002.5.6.
                //fnKeyBoardInterrupt((UCHR)(( HIWORD(lParam))%256 ));
                HandleMessage(hWnd, message, wParam, lParam);
                return 0;
            }
            break;
        }
    case WM_KEYUP:
        {
            switch (wParam)
            {
            case VK_F12:
				{
					SHORT   nState;

					nState = GetKeyState(VK_CONTROL);
					if(nState & 0x8000)
					{
						SLONG	is_opened;

						is_opened = is_gm_console_opened();
						if(is_opened)
							close_gm_console();
						else
							open_gm_console();
					}
					else
					{
						if(g_enable_f12_switch_screen)
						{
							if( g_dwScreenMode == WINDOWS_SCREEN_MODE )
								GetWindowRect( hWnd, &g_rcWindow );
							
							switch_screen_mode();
						}
					}
				}
                return  0;
                
            case VK_SNAPSHOT:
                capture_screen();
                return  0;

            case VK_SHIFT:
                break;

            default:
                //Jack, 2002.5.6.
                //fnKeyBoardInterrupt((UCHR)((( HIWORD(lParam))%256 ) | 0x80));
                HandleMessage(hWnd, message, wParam, lParam);
                return  0;
            }
        }
        break;

        //IME -----------------------------------------------------------------------------------
	// Zhang Zhaohui	2003.4.21
	case WM_IME_CHAR:
	case WM_IME_NOTIFY:
	case WM_INPUTLANGCHANGEREQUEST:
	case WM_INPUTLANGCHANGE:
		if ( HandleMessage( hWnd, message, wParam, lParam ) )
			return 0;
		break;

/*
    case WM_IME_SETCONTEXT:
        if( ime_on_WM_IME_SETCONTEXT( hWnd, message, wParam, lParam) )
            return  0;
        break;

    case WM_INPUTLANGCHANGEREQUEST:
        if( ime_on_WM_INPUTLANGCHANGEREQUEST( hWnd, message, wParam, lParam ) )
            return  0;
        break;

    case WM_INPUTLANGCHANGE:
        if( ime_on_WM_INPUTLANGCHANGE( hWnd, message, wParam, lParam ) )
            return  0;
        break;

    case WM_IME_STARTCOMPOSITION:
        if( ime_on_WM_IME_STARTCOMPOSITION( hWnd, message, wParam, lParam ) )
            return  0;
        break;

    case WM_IME_ENDCOMPOSITION:
        if( ime_on_WM_IME_ENDCOMPOSITION( hWnd, message, wParam, lParam ))
            return  0;
        break;

    case WM_IME_NOTIFY:
        if( ime_on_WM_IME_NOTIFY( hWnd, message, wParam, lParam ))
            return  0;
        break;

    case WM_IME_COMPOSITION: //輸入改變
        if( ime_on_WM_IME_COMPOSITION( hWnd, message, wParam, lParam ) )
            return  0;
        break;
*/

//	case WM_CTLCOLOREDIT:
//	case WM_CTLCOLORSTATIC:
//		return	OnCtlColor(wParam, lParam);
		//break;

        //GAME EVENT ----------------------------------------------------------------------------
    case WM_POSGAMEEVENT:
		{
			DWORD	dwType, dwSize;
			
			dwType = (lParam & 0xffff0000) >> 16;
			dwSize = lParam & 0xffff;
			AddClientRecvMsg((LPVOID)wParam, dwType, dwSize, 0, 0);
		}
        return  0;

    default:
        break;
    }
    return DefWindowProc(hWnd,message,wParam,lParam);
}



HRESULT FrameMove(VOID)
{
    SLONG   result;

	// Jack, message processed in GameEventWndProc [1/16/2003]
	// ClientProcessMsg();

    switch(g_dwAppState)
    {
	case APPSTATE_SYSTEM_INIT:
        client_cmd_init_app_state();
        break;
	case APPSTATE_SHOW_SWAP_SCREEN:
		refresh_swap_screen();
		break;

        //版權宣告 ---------------------------------------------------------------
    case APPSTATE_INIT_EULA:
        exec_free_process();
        result = init_eula();
        if(0 == result)
        {
            push_free_process(free_eula);
            get_bitmap(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, screen_channel1, screen_buffer);
            redraw_eula(0, 0, screen_channel0);
            swap_screen(rand_swap_screen_type(), screen_channel0, screen_channel1);
            set_next_app_state(APPSTATE_SHOW_EULA);
            //change_app_state();
        }
        else
        {
            set_next_app_state(APPSTATE_ERROR_EXIT);
            change_app_state();
        }
        break;
    case APPSTATE_SHOW_EULA:
        refresh_eula();
        break;

        //登錄--------------------------------------------------------------------
    case APPSTATE_INIT_LOGIN:
        exec_free_process();
        result = init_uilogin();
        if(0 == result)
        {
            push_free_process(free_uilogin);
            get_bitmap(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, screen_channel1, screen_buffer);
            redraw_uilogin(0, 0, screen_channel0);
            swap_screen(rand_swap_screen_type(), screen_channel0, screen_channel1);
            set_next_app_state(APPSTATE_SHOW_LOGIN);
            //change_app_state();
        }
        else
        {
            set_next_app_state(APPSTATE_ERROR_EXIT);
            change_app_state();
        }
        break;
    case APPSTATE_SHOW_LOGIN:
        refresh_uilogin();
        break;

        //製作群------------------------------------------------------------------
    case APPSTATE_INIT_CREDITS:
        exec_free_process();
        result = init_credits();
        if(0 == result)
        {
            push_free_process(free_credits);
            get_bitmap(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, screen_channel1, screen_buffer);
            redraw_credits(0, 0, screen_channel0);
            swap_screen(rand_swap_screen_type(), screen_channel0, screen_channel1);
            set_next_app_state(APPSTATE_SHOW_CREDITS);
            //change_app_state();
        }
        else
        {
            set_next_app_state(APPSTATE_ERROR_EXIT);
            change_app_state();
        }
        break;
    case APPSTATE_SHOW_CREDITS:
        refresh_credits();
        break;

        //帳號管理----------------------------------------------------------------
    case APPSTATE_INIT_ACCOUNT_MANAGER:
        exec_free_process();
        result = init_account_manager();
        if(0 == result)
        {
            push_free_process(free_account_manager);
            get_bitmap(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, screen_channel1, screen_buffer);
            redraw_account_manager(0, 0, screen_channel0);
            swap_screen(rand_swap_screen_type(), screen_channel0, screen_channel1);
            set_next_app_state(APPSTATE_SHOW_ACCOUNT_MANAGER);
            //change_app_state();
        }
        else
        {
            set_next_app_state(APPSTATE_ERROR_EXIT);
            change_app_state();
        }
        break;
    case APPSTATE_SHOW_ACCOUNT_MANAGER:
        refresh_account_manager();
        break;

        //創建新帳號 ---------------------------------------------------------------
    case APPSTATE_INIT_CREATE_ACCOUNT:
        exec_free_process();
        result = init_create_account();
        if(0 == result)
        {
            push_free_process(free_create_account);
            get_bitmap(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, screen_channel1, screen_buffer);
            redraw_create_account(0, 0, screen_channel0);
            swap_screen(rand_swap_screen_type(), screen_channel0, screen_channel1);
            set_next_app_state(APPSTATE_SHOW_CREATE_ACCOUNT);
            //change_app_state();
        }
        else
        {
            set_next_app_state(APPSTATE_ERROR_EXIT);
            change_app_state();
        }
        break;
    case APPSTATE_SHOW_CREATE_ACCOUNT:
        refresh_create_account();
        break;

        //創建資料 ---------------------------------------------------------------
    case APPSTATE_INIT_SETUP_RECORD:
        exec_free_process();
        result = init_setup_record();
        if(0 == result)
        {
            push_free_process(free_setup_record);
            get_bitmap(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, screen_channel1, screen_buffer);
            redraw_setup_record(0, 0, screen_channel0);
            swap_screen(rand_swap_screen_type(), screen_channel0, screen_channel1);
            set_next_app_state(APPSTATE_SHOW_SETUP_RECORD);
            //change_app_state();
        }
        else
        {
            set_next_app_state(APPSTATE_ERROR_EXIT);
            change_app_state();
        }
        break;
    case APPSTATE_SHOW_SETUP_RECORD:
        refresh_setup_record();
        break;


        //選擇付款方式 -------------------------------------------------------------
    case APPSTATE_INIT_SELECT_PAYMENT:
        exec_free_process();
        result = init_select_payment();
        if(0 == result)
        {
            push_free_process(free_select_payment);
            get_bitmap(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, screen_channel1, screen_buffer);
            redraw_select_payment(0, 0, screen_channel0);
            swap_screen(rand_swap_screen_type(), screen_channel0, screen_channel1);
            set_next_app_state(APPSTATE_SHOW_SELECT_PAYMENT);
            //change_app_state();
        }
        else
        {
            set_next_app_state(APPSTATE_ERROR_EXIT);
            change_app_state();
        }
        break;
    case APPSTATE_SHOW_SELECT_PAYMENT:
        refresh_select_payment();
        break;

        //修改密碼----------------------------------------------------------------
    case APPSTATE_INIT_CHANGE_PASSWORD:
        exec_free_process();
        result = init_change_password();
        if(0 == result)
        {
            push_free_process(free_change_password);
            get_bitmap(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, screen_channel1, screen_buffer);
            redraw_change_password(0, 0, screen_channel0);
            swap_screen(rand_swap_screen_type(), screen_channel0, screen_channel1);
            set_next_app_state(APPSTATE_SHOW_CHANGE_PASSWORD);
            //change_app_state();
        }
        else
        {
            set_next_app_state(APPSTATE_ERROR_EXIT);
            change_app_state();
        }
        break;
    case APPSTATE_SHOW_CHANGE_PASSWORD:
        refresh_change_password();
        break;

        //選擇世界伺服器----------------------------------------------------------
    case APPSTATE_INIT_SELECT_WORLD_SERVER:
        exec_free_process();
        result = init_select_world_server();
        if(0 == result)
        {
            push_free_process(free_select_world_server);
            get_bitmap(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, screen_channel1, screen_buffer);
            redraw_select_world_server(0, 0, screen_channel0);
            swap_screen(rand_swap_screen_type(), screen_channel0, screen_channel1);
            set_next_app_state(APPSTATE_SHOW_SELECT_WORLD_SERVER);
            //change_app_state();
        }
        else
        {
            set_next_app_state(APPSTATE_ERROR_EXIT);
            change_app_state();
        }
        break;
    case APPSTATE_SHOW_SELECT_WORLD_SERVER:
        refresh_select_world_server();
        break;


        //選擇角色----------------------------------------------------------------
    case APPSTATE_INIT_SELECT_CHARACTER:
        exec_free_process();
        result = init_select_character();
        if(0 == result)
        {
            push_free_process(free_select_character);
            get_bitmap(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, screen_channel1, screen_buffer);
            redraw_select_character(0, 0, screen_channel0);
            swap_screen(rand_swap_screen_type(), screen_channel0, screen_channel1);
            set_next_app_state(APPSTATE_SHOW_SELECT_CHARACTER);
            //change_app_state();
        }
        else
        {
            set_next_app_state(APPSTATE_ERROR_EXIT);
            change_app_state();
        }
        break;
    case APPSTATE_SHOW_SELECT_CHARACTER:
        refresh_select_character();
        break;

        //創建角色----------------------------------------------------------------
    case APPSTATE_INIT_CREATE_CHARACTER:
        exec_free_process();
        result = init_create_character();
        if(0 == result)
        {
            push_free_process(free_create_character);
            get_bitmap(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, screen_channel1, screen_buffer);
            redraw_create_character(0, 0, screen_channel0);
            swap_screen(rand_swap_screen_type(), screen_channel0, screen_channel1);
            set_next_app_state(APPSTATE_SHOW_CREATE_CHARACTER);
            //change_app_state();
        }
        else
        {
            set_next_app_state(APPSTATE_ERROR_EXIT);
            change_app_state();
        }
        break;
    case APPSTATE_SHOW_CREATE_CHARACTER:
        refresh_create_character();
        break;

		//配置角色顏色------------------------------------------------------------
	case APPSTATE_INIT_CHG_CHAR_COLOR:
        exec_free_process();
        result = init_change_character_color();
        if(0 == result)
        {
            push_free_process(free_create_character);
            get_bitmap(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, screen_channel1, screen_buffer);
            redraw_change_character_color(0, 0, screen_channel0);
            swap_screen(rand_swap_screen_type(), screen_channel0, screen_channel1);
            set_next_app_state(APPSTATE_SHOW_CHG_CHAR_COLOR);
            //change_app_state();
        }
        else
        {
            set_next_app_state(APPSTATE_ERROR_EXIT);
            change_app_state();
        }
		break;
	case APPSTATE_SHOW_CHG_CHAR_COLOR:
		refresh_change_character_color();
		break;

        //設置人物肖像------------------------------------------------------------
    case APPSTATE_INIT_SET_CHAR_FACE:
        exec_free_process();
        result = init_set_character_face();
        if(0 == result)
        {
            push_free_process(free_set_character_face);
            get_bitmap(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, screen_channel1, screen_buffer);
            redraw_set_character_face(0, 0, screen_channel0);
            swap_screen(rand_swap_screen_type(), screen_channel0, screen_channel1);
            set_next_app_state(APPSTATE_SHOW_SET_CHAR_FACE);
            //change_app_state();
        }
        else
        {
            set_next_app_state(APPSTATE_ERROR_EXIT);
            change_app_state();
        }
        break;
    case APPSTATE_SHOW_SET_CHAR_FACE:
        refresh_set_character_face();
        break;

        //設置人物出生地----------------------------------------------------------
    case APPSTATE_INIT_SET_CHAR_LOCATE:
        exec_free_process();
        result = init_set_character_locate();
        if(0 == result)
        {
            push_free_process(free_set_character_locate);
            get_bitmap(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, screen_channel1, screen_buffer);
            redraw_set_character_locate(0, 0, screen_channel0);
            swap_screen(rand_swap_screen_type(), screen_channel0, screen_channel1);
            set_next_app_state(APPSTATE_SHOW_SET_CHAR_LOCATE);
            //change_app_state();
        }
        else
        {
            set_next_app_state(APPSTATE_ERROR_EXIT);
            change_app_state();
        }
        break;
    case APPSTATE_SHOW_SET_CHAR_LOCATE:
        refresh_set_character_locate();
        break;

        //載入主遊戲--------------------------------------------------------------
    case APPSTATE_INIT_LOADING_MAIN_GAME:
        exec_free_process();
        result = init_loading_main_game();
        if(0 == result)
        {
            push_free_process(free_loading_main_game);
            get_bitmap(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, screen_channel1, screen_buffer);
            redraw_loading_main_game(0, 0, screen_channel0);
            swap_screen(rand_swap_screen_type(), screen_channel0, screen_channel1);
            set_next_app_state(APPSTATE_SHOW_LOADING_MAIN_GAME);
            //change_app_state();
        }
        else
        {
            set_next_app_state(APPSTATE_ERROR_EXIT);
            change_app_state();
        }
        break;
    case APPSTATE_SHOW_LOADING_MAIN_GAME:
        refresh_loading_main_game();
        break;

        //主遊戲------------------------------------------------------------------
    case APPSTATE_INIT_MAIN_GAME:
        exec_free_process();
        result = init_main_game();
        if(0 == result)
        {
            push_free_process(free_main_game);
            get_bitmap(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, screen_channel1, screen_buffer);
            redraw_main_game(0, 0, screen_channel0);
            swap_screen(rand_swap_screen_type(), screen_channel0, screen_channel1);
            set_next_app_state(APPSTATE_SHOW_MAIN_GAME);
            //change_app_state();
        }
        else
        {
            set_next_app_state(APPSTATE_ERROR_EXIT);
            change_app_state();
        }
        break;
    case APPSTATE_SHOW_MAIN_GAME:
        refresh_main_game();
        refresh_secret_skill();
		refresh_gm_console();
        break;

        //切換地圖前的等待--------------------------------------------------------
    case APPSTATE_INIT_CHANGEMAP_LOADING:
        exec_free_process();
        result = init_changemap_loading();
        if(0 == result)
        {
            push_free_process(free_changemap_loading);
            get_bitmap(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, screen_channel1, screen_buffer);
            redraw_changemap_loading(0, 0, screen_channel0);
            swap_screen(rand_swap_screen_type(), screen_channel0, screen_channel1);
            set_next_app_state(APPSTATE_SHOW_CHANGEMAP_LOADING);
            //change_app_state();
        }
        else
        {
            set_next_app_state(APPSTATE_ERROR_EXIT);
            change_app_state();
        }
        break;
    case APPSTATE_SHOW_CHANGEMAP_LOADING:
        refresh_changemap_loading();
        break;

        //------------------------------------------------------------------------
        //------------------------------------------------------------------------
        //------------------------------------------------------------------------
        //------------------------------------------------------------------------

		//開始單機遊戲(模擬) -----------------------------------------------------
	case APPSTATE_INIT_STARTING_SINGLE_GAME:
        exec_free_process();
        result = init_starting_single_game();
        if(0 == result)
        {
            push_free_process(free_starting_single_game);
            get_bitmap(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, screen_channel1, screen_buffer);
            redraw_starting_single_game(0, 0, screen_channel0);
            swap_screen(rand_swap_screen_type(), screen_channel0, screen_channel1);
            set_next_app_state(APPSTATE_SHOW_STARTING_SINGLE_GAME);
            //change_app_state();
        }
        else
        {
            set_next_app_state(APPSTATE_ERROR_EXIT);
            change_app_state();
        }
		break;
	case APPSTATE_SHOW_STARTING_SINGLE_GAME:
		refresh_starting_single_game();
		break;

        //出現錯誤，退出----------------------------------------------------------
    case APPSTATE_ERROR_EXIT:
        break;

        //系統正常退出------------------------------------------------------------
    case APPSTATE_SYSTEM_EXIT:
        PostMessage(g_hDDWnd, WM_DESTROY, 0, 0);
        break;

    default:
        break;
    }
	if ( g_dwAppState != APPSTATE_ERROR_EXIT &&
		 g_dwAppState != APPSTATE_SYSTEM_EXIT )
	{
		refresh_iconmsg( );
	}

    return  0;
}


HRESULT RenderFrame(VOID)
{
    switch(g_dwAppState)
    {
    case APPSTATE_SYSTEM_INIT:
        fill_bitmap(screen_buffer, SYSTEM_PINK);
        sprintf((char *)print_rec, "~C0~O3FPS=%d~C0~O0", get_fps());
        print16(0, 0, (USTR*)print_rec, COPY_PUT, screen_buffer);
        break;
	case APPSTATE_SHOW_SWAP_SCREEN:
		redraw_swap_screen(0, 0, screen_buffer);
		break;

        //版權宣告----------------------------------------------------------------
    case APPSTATE_SHOW_EULA:
        redraw_eula(0, 0, screen_buffer);
        //test
        //test_buf(0, 0, screen_buffer);
        break;

        //登錄--------------------------------------------------------------------
    case APPSTATE_SHOW_LOGIN:
        redraw_uilogin(0, 0, screen_buffer);
        break;

        //製作群------------------------------------------------------------------
    case APPSTATE_SHOW_CREDITS:
        redraw_credits(0, 0, screen_buffer);
        break;

        //帳號管理----------------------------------------------------------------
    case APPSTATE_SHOW_ACCOUNT_MANAGER:
        redraw_account_manager(0, 0, screen_buffer);
        break;

        //創建新帳號 ---------------------------------------------------------------
    case APPSTATE_SHOW_CREATE_ACCOUNT:
        redraw_create_account(0, 0, screen_buffer);
        break;

        //創建資料 ---------------------------------------------------------------
    case APPSTATE_SHOW_SETUP_RECORD:
        redraw_setup_record(0, 0, screen_buffer);
        break;
        
        //選擇付款方式 -------------------------------------------------------------
    case APPSTATE_SHOW_SELECT_PAYMENT:
        redraw_select_payment(0, 0, screen_buffer);
        break;

        //修改密碼----------------------------------------------------------------
    case APPSTATE_SHOW_CHANGE_PASSWORD:
        redraw_change_password(0, 0, screen_buffer);
        break;

        //選擇世界伺服器----------------------------------------------------------
    case APPSTATE_SHOW_SELECT_WORLD_SERVER:
        redraw_select_world_server(0, 0, screen_buffer);
        break;

        //選擇角色----------------------------------------------------------------
    case APPSTATE_SHOW_SELECT_CHARACTER:
        redraw_select_character(0, 0, screen_buffer);
        break;

        //創建角色----------------------------------------------------------------
    case APPSTATE_SHOW_CREATE_CHARACTER:
        redraw_create_character(0, 0, screen_buffer);
        break;

		//配置角色顏色------------------------------------------------------------
	case APPSTATE_SHOW_CHG_CHAR_COLOR:
		redraw_change_character_color(0, 0, screen_buffer);
		break;

        //設置人物肖像------------------------------------------------------------
    case APPSTATE_SHOW_SET_CHAR_FACE:
        redraw_set_character_face(0, 0, screen_buffer);
        break;

        //設置人物出生地----------------------------------------------------------
    case APPSTATE_SHOW_SET_CHAR_LOCATE:
        redraw_set_character_locate(0, 0, screen_buffer);
        break;

        //載入主遊戲--------------------------------------------------------------
    case APPSTATE_SHOW_LOADING_MAIN_GAME:
        redraw_loading_main_game(0, 0, screen_buffer);
        break;

        //主遊戲------------------------------------------------------------------
    case APPSTATE_SHOW_MAIN_GAME:
        redraw_main_game(0, 0, screen_buffer);
		redraw_gm_console(0, 0, screen_buffer);
        break;

        //切換地圖前的等待--------------------------------------------------------
    case APPSTATE_SHOW_CHANGEMAP_LOADING:
        redraw_changemap_loading(0, 0, screen_buffer);
        break;

        //切換地圖 ---------------------------------------------------------------
        //------------------------------------------------------------------------
        //------------------------------------------------------------------------
        //------------------------------------------------------------------------
        //------------------------------------------------------------------------
        //------------------------------------------------------------------------

		//單機遊戲(模擬)
	case APPSTATE_SHOW_STARTING_SINGLE_GAME:
        redraw_starting_single_game(0, 0, screen_buffer);
		break;

        //出現錯誤，退出----------------------------------------------------------
    case APPSTATE_ERROR_EXIT:
		redraw_error_exit(0, 0, screen_buffer);
        break;

        //系統正常退出------------------------------------------------------------
    case APPSTATE_SYSTEM_EXIT:
        break;

        //測試--------------------------------------------------------------------
    case APPSTATE_TEST_GRAFX:
        fill_bitmap(screen_buffer, SYSTEM_PINK);
        redraw_test_grafx(screen_buffer);
        break;

    default:
        update_screen(screen_buffer);
        break;
    }

	debug_redraw_mouse_position(screen_buffer);
	redraw_ui_msgbox(screen_buffer);
	debug_redraw_game_range(screen_buffer);

// Zhang Zhaohui 2003.5.29
//	if ( bShowRange )
//		game_range.redraw( 0, 0, screen_buffer );

	update_screen(screen_buffer);

    return  0;
}


HRESULT HandleMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	SLONG	result;

	result = handle_ui_msgbox(message, wParam, lParam);	// 消息框
	if(0 == result)
		return	0;

	if ( 0 == handle_te( message, wParam, lParam ) )	// 編輯區
		return 1;	

    switch(g_dwAppState)
    {
	case APPSTATE_SHOW_SWAP_SCREEN:
		handle_swap_screen(message, wParam, lParam);
		break;
    case APPSTATE_SHOW_EULA:
        handle_eula(message, wParam, lParam);
        break;
    case APPSTATE_SHOW_LOGIN:
        handle_uilogin(message, wParam, lParam);
        break;
    case APPSTATE_SHOW_CREDITS:
        handle_credits(message, wParam, lParam);
        break;
    case APPSTATE_SHOW_ACCOUNT_MANAGER:
        handle_account_manager(message, wParam, lParam);
        break;
    case APPSTATE_SHOW_CREATE_ACCOUNT:
        handle_create_account(message, wParam, lParam);
        break;
    case APPSTATE_SHOW_SETUP_RECORD:
        handle_combobox(message, wParam, lParam);
        handle_setup_record(message, wParam, lParam);
        break;
    case APPSTATE_SHOW_SELECT_PAYMENT:
        handle_combobox(message, wParam, lParam);
        handle_select_payment(message, wParam, lParam);
        break;
    case APPSTATE_SHOW_CHANGE_PASSWORD:
        handle_change_password(message, wParam, lParam);
        break;
    case APPSTATE_SHOW_SELECT_WORLD_SERVER:
        handle_select_world_server(message, wParam, lParam);
        break;
    case APPSTATE_SHOW_SELECT_CHARACTER:
        handle_select_character(message, wParam, lParam);
        break;
    case APPSTATE_SHOW_CREATE_CHARACTER:
        handle_create_character(message, wParam, lParam);
        break;
	case APPSTATE_SHOW_CHG_CHAR_COLOR:
		handle_change_character_color(message, wParam, lParam);
		break;
    case APPSTATE_SHOW_LOADING_MAIN_GAME:
        handle_loading_main_game(message, wParam, lParam);
        break;
    case APPSTATE_SHOW_MAIN_GAME:
		result = handle_gm_console(message, wParam, lParam);
		if(0 != result)
			result = handle_main_game(message, wParam, lParam);
        break;
    case APPSTATE_SHOW_SET_CHAR_FACE:
        handle_set_character_face(message, wParam, lParam);
        break;
    case APPSTATE_SHOW_SET_CHAR_LOCATE:
        handle_set_character_locate(message, wParam, lParam);
        break;
    case APPSTATE_SHOW_CHANGEMAP_LOADING:
        handle_changemap_loading(message, wParam, lParam);
        break;
	case APPSTATE_SHOW_STARTING_SINGLE_GAME:
		handle_starting_single_game(message, wParam, lParam);
		break;
	case APPSTATE_ERROR_EXIT:
		handle_error_exit(message, wParam, lParam);
		break;
    default:
        break;
    }
    return  0;
}



HRESULT TimerRefresh(VOID)
{
    switch(g_dwAppState)
    {
    case APPSTATE_SHOW_MAIN_GAME:
        //refresh_main_game();
        break;
    }
    return  0;
}


void    change_app_state(void)
{
    g_dwOldAppState = g_dwAppState;
    g_dwAppState = g_dwNextAppState;
}


void    set_next_app_state(DWORD dwNextState)
{
    g_dwNextAppState = dwNextState;
}


void    exec_open_all_data_files(void)
{
    packed_data_file = open_data_file("data.pos");  //(1) 數值部分	data.pos	<data>
    packed_menu_file = open_data_file("menu.pos");  //(2) 選單部分	menu.pos	<menu>
    packed_sound_file = open_data_file("sound.pos");//(3) 音效部分	sound.pos	<sound>
    packed_music_file = open_data_file("music.pos");//(4) 音樂部分	music.pos	<music>
    packed_tile_file = open_data_file("tile.pos");  //(5) 圖素部分	tile.pos	<tile>
    packed_house_file = open_data_file("house.pos");//(6) 房屋部分	house.pos	<house>
    packed_map_file = open_data_file("map.pos");    //(7) 地圖部分	map.pos	    <map>
    packed_object_file = open_data_file("object.pos");//(8) 物件部分	object.pos	<object>
	packed_macro_file = open_data_file("macro.pos");	//(9)劇本部分  macro.pos   <macro>
    packed_other_file = open_data_file("sea.pos"); //(10) 其他		sea.pos
    packed_npc_file = open_data_file("npc.pos"); //(11) land npc file	npc.pos
    packed_seanpc_file = open_data_file("seanpc.pos"); //(12) sea npc file 	seanpc.pos
}


void    exec_close_all_data_files(void)
{

    //(1) 數值部分	data.pos	<data>
    if(packed_data_file)
    {
		set_data_file(packed_data_file);
        close_data_file(packed_data_file);
        packed_data_file = NULL;
    }
    //(2) 選單部分	menu.pos	<menu>
    if(packed_menu_file)
    {
		set_data_file(packed_menu_file);
        close_data_file(packed_menu_file);
        packed_menu_file = NULL;
    }
    //(3) 音效部分	sound.pos	<sound>
    if(packed_sound_file)
    {
		set_data_file(packed_sound_file);
        close_data_file(packed_sound_file);
        packed_sound_file = NULL;
    }
    //(4) 音樂部分	music.pos	<music>
    if(packed_music_file)
    {
		set_data_file(packed_music_file);
        close_data_file(packed_music_file);
        packed_music_file = NULL;
    }
    //(5) 圖素部分	tile.pos	<tile>
    if(packed_tile_file)
    {
		set_data_file(packed_tile_file);
        close_data_file(packed_tile_file);
        packed_tile_file = NULL;
    }
    //(6) 房屋部分	house.pos	<house>
    if(packed_house_file)
    {
		set_data_file(packed_house_file);
        close_data_file(packed_house_file);
        packed_house_file = NULL;
    }
    //(7) 地圖部分	map.pos	    <map>
    if(packed_map_file)
    {
		set_data_file(packed_map_file);
        close_data_file(packed_map_file);
        packed_map_file = NULL;
    }
    //(8) 物件部分	object.pos	<object>
    if(packed_object_file)
    {
		set_data_file(packed_object_file);
        close_data_file(packed_object_file);
        packed_object_file = NULL;
    }
	//(9) 劇本部分  macro.pos   <macro>
	if(packed_macro_file)
	{
		set_data_file(packed_macro_file);
		close_data_file(packed_macro_file);
		packed_macro_file = NULL;
	}
    //(10) 其他		sea.pos
    if(packed_other_file)
    {
		set_data_file(packed_other_file);
        close_data_file(packed_other_file);
        packed_other_file = NULL;
    }

    //(11) land npc file: npc.pos
    if(packed_npc_file)
    {
		set_data_file(packed_npc_file);
        close_data_file(packed_npc_file);
        packed_npc_file = NULL;
    }

    //(12) sea npc file: seanpc.pos
    if(packed_seanpc_file)
    {
		set_data_file(packed_seanpc_file);
        close_data_file(packed_seanpc_file);
        packed_seanpc_file = NULL;
    }

}



void	redraw_error_exit(SLONG sx, SLONG sy, void *vbitmap)
{
	BMP *bitmap = (BMP*)vbitmap;

	fill_bitmap(screen_buffer, rgb2hi(128,128,128));
	sprintf((char *)print_rec, "~C8SYSTEM ERROR, PRESS ANY KEY TO ABORT...~C0");
	display_error_message((USTR*)print_rec, DISPLAY_MESSAGE_TO_BUFFER, screen_buffer);
}


SLONG   handle_error_exit(UINT message, WPARAM wParam, LPARAM lParam)
{
    switch(message)
    {
    case WM_KEYDOWN:
	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
		PostMessage(g_hDDWnd, WM_DESTROY, 0, 0);
		break;
    }
    return  0;
}

//-------------------------------------------------------------------------
//  Test fun 
//-------------------------------------------------------------------------
/*
void    test_buf(SLONG sx, SLONG sy, void *vbitmap)
{
    const   c_ox = 0, c_oy = 50;
    SLONG   mouse_x, mouse_y;
    SLONG   ox, oy;
    BMP *bmp = (BMP *)vbitmap;
    SLONG   in_pos[3];
    SLONG   dir;
    
    //

    get_mouse_position(&mouse_x, &mouse_y);
    //
    in_pos[0] = mouse_x - 400;
    in_pos[1] = mouse_y - 300;
    in_pos[2] = 0;
    dir = Vertex2Dir32(in_pos);
    //
    put_bar(400,300,10,10,0,bmp);
    //
    sprintf((char *)print_rec, "~C8%d~C0", dir);
    print16(0, 100, print_rec, COPY_PUT_COLOR(SYSTEM_BLUE), bmp);    
    //
    ox = (SLONG)(c_ox * g_32dir_rotation[dir][0] - 
                c_oy * g_32dir_rotation[dir][1]);
    oy = (SLONG)(c_ox * g_32dir_rotation[dir][1] + 
                c_oy * g_32dir_rotation[dir][0]);    
    //
    put_bar(400+ox, 300+oy, 10, 10, 0xffff, bmp);    
}
*/

