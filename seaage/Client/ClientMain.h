/*
**  ClientMain.h
**  client main functions header.
**
**  Jack, 2002.5.6.
*/
#ifndef _CLIENTMAIN_H_
#define _CLIENTMAIN_H_


//DEFINES //////////////////////////////////////////////////////////////////////////////////////
//
#define WM_IME_STRING       (WM_USER+999)   //用戶輸入的漢字字串消息


typedef enum    APPSTATE_ENUMS
{   APPSTATE_SYSTEM_INIT                    =   0,      //系統初始化
APPSTATE_SHOW_SWAP_SCREEN					=	1,		//屏幕切換(特效)
//
APPSTATE_INIT_EULA                          =   5,      //準備版權宣告
APPSTATE_SHOW_EULA                          =   6,      //版權宣告
//
APPSTATE_INIT_LOGIN                         =   10,     //準備登錄介面
APPSTATE_SHOW_LOGIN                         =   20,     //登錄介面
//
APPSTATE_INIT_CREDITS                       =   30,     //準備製作群
APPSTATE_SHOW_CREDITS                       =   40,     //製作群
//
APPSTATE_INIT_ACCOUNT_MANAGER               =   50,     //準備帳號管理
APPSTATE_SHOW_ACCOUNT_MANAGER               =   60,     //帳號管理
//
APPSTATE_INIT_SELECT_WORLD_SERVER           =   70,     //準備選擇世界伺服器
APPSTATE_SHOW_SELECT_WORLD_SERVER           =   80,     //選擇世界伺服器
//
APPSTATE_INIT_SELECT_CHARACTER              =   90,     //準備選擇角色
APPSTATE_SHOW_SELECT_CHARACTER              =   100,    //選擇角色
//
APPSTATE_INIT_CREATE_CHARACTER              =   110,    //準備創建角色
APPSTATE_SHOW_CREATE_CHARACTER              =   120,    //創建角色
//
APPSTATE_INIT_CHG_CHAR_COLOR				=	121,	//準備修改人物顏色
APPSTATE_SHOW_CHG_CHAR_COLOR				=	122,	//設置人物肖像顏色
//
APPSTATE_INIT_SET_CHAR_FACE                 =   130,    //準備設置人物肖像
APPSTATE_SHOW_SET_CHAR_FACE                 =   140,    //設置人物肖像
//
APPSTATE_INIT_SET_CHAR_LOCATE               =   150,    //準備設置人物出生地
APPSTATE_SHOW_SET_CHAR_LOCATE               =   160,    //設置人物出生地
//
APPSTATE_INIT_LOADING_MAIN_GAME             =   170,    //準備載入主遊戲
APPSTATE_SHOW_LOADING_MAIN_GAME             =   180,    //載入主遊戲
//
APPSTATE_INIT_MAIN_GAME                     =   200,    //準備進入主遊戲
APPSTATE_SHOW_MAIN_GAME                     =   210,    //主遊戲
//
APPSTATE_INIT_CREATE_ACCOUNT                =   220,    //準備創建新帳號
APPSTATE_SHOW_CREATE_ACCOUNT                =   230,    //輸入帳號和密碼
//
APPSTATE_INIT_SETUP_RECORD                  =   240,    //準備建立資料
APPSTATE_SHOW_SETUP_RECORD                  =   250,    //建立資料
//
APPSTATE_INIT_SELECT_PAYMENT                =   260,    //準備選擇付款方式
APPSTATE_SHOW_SELECT_PAYMENT                =   270,    //選擇付款方式
//
APPSTATE_INIT_MODIFY_RECORD                 =   290,    //準備修改資料
APPSTATE_SHOW_MODIFY_RECORD                 =   300,    //修改資料
//
APPSTATE_INIT_CHANGE_PASSWORD               =   310,    //準備修改密碼
APPSTATE_SHOW_CHANGE_PASSWORD               =   320,    //修改密碼
//
APPSTATE_INIT_SUPPLY_POINTS                 =   330,    //準備充值點數
APPSTATE_SHOW_SUPPLY_POINTS                 =   340,    //充值點數
//
APPSTATE_INIT_CHANGEMAP_LOADING             =   350,    //切換地圖前的等待畫面
APPSTATE_SHOW_CHANGEMAP_LOADING             =   360,    //切換地圖前的等待
//
APPSTATE_INIT_STARTING_SINGLE_GAME			=	99980,	//準備開始單機遊戲(模擬)
APPSTATE_SHOW_STARTING_SINGLE_GAME			=	99981,	//開始單機遊戲(模擬)
//
APPSTATE_ERROR_EXIT                         =   99990,  //出現錯誤，退出
APPSTATE_SYSTEM_EXIT                        =   100000, //系統正常退出
//
APPSTATE_TEST_GRAFX                         =   100001,  //測試
//
} APPSTATE_ENUMS;



typedef	enum	APPEVENT_ENUMS
{	APPEVENT_NOTHING						=	0,		//沒有任何事件
APPEVENT_START_CHANGE_ZONE					=	1,		//開始切換ZONE
APPEVENT_START_LOGIN_ZONE					=	2,		//開始登入ZONE
APPEVENT_START_PLAY_MAINGAME				=	3,		//開始遊戲
} APPEVENT_ENUMS;


//GLOBALS ////////////////////////////////////////////////////////////////////////////////////////// 
extern  HINSTANCE   g_hInstance;                // App instance
extern  DWORD   g_dwAppState;               //應用程式的當前執行狀態
extern  DWORD   g_dwOldAppState;            //應用程式的以前執行狀態
extern  DWORD   g_dwNextAppState;           //應用程式的下一個執行狀態
extern	DWORD	g_dwAppEvent;				//應用程式的事件
extern  DWORD   g_dwConnectedServerType;    //應用程式目前連接的伺服器類型
extern  LONG    g_lPlayerIndex;             //玩家的 NPC 索引號
extern  LONG    g_lPlayerMap;               //玩家當前所在的地圖, 實際上目前只用來作 map_base[]的索引, 
                                            //並且固定為 0.
extern  TCHAR   g_szPlayerZone[64];         //玩家當前所在的ZONE名稱
extern	DWORD	g_dwZoneType;				//玩家當前所在的ZONE類型
extern  TCHAR   g_szPlayerMap[64];          //玩家當前所在的地圖名稱
extern  TCHAR   g_szPlayerMainName[64];     //玩家的名稱
extern  DWORD   g_dwHeartBeat;              //心跳次數計數
extern	LONG	g_lIsSingleGame;			//是否為單機遊戲
extern	LONG	g_IsExitingGame;			//紀錄遊戲是否正在退出(當玩家按ESC以後).
//
extern  DATA_FILE   *packed_data_file;   //(1) 數值部分	data.pos	<data>
extern  DATA_FILE   *packed_menu_file;   //(2) 選單部分	menu.pos	<menu>
extern  DATA_FILE   *packed_sound_file;  //(3) 音效部分	sound.pos	<sound>
extern  DATA_FILE   *packed_music_file;  //(4) 音樂部分	music.pos	<music>
extern  DATA_FILE   *packed_tile_file;   //(5) 圖素部分	tile.pos	<tile>
extern  DATA_FILE   *packed_house_file;  //(6) 房屋部分	house.pos	<house>
extern  DATA_FILE   *packed_map_file;    //(7) 地圖部分	map.pos	    <map>
extern  DATA_FILE   *packed_object_file; //(8) 物件部分	object.pos	<object>
extern	DATA_FILE	*packed_macro_file;	 //(9) 劇本部分 macro.pos   <macro>
extern  DATA_FILE   *packed_other_file;  //(10) 其他		sea.pos
extern	DATA_FILE	*packed_npc_file;	//(11) LAND NPC npc.pos
extern	DATA_FILE	*packed_seanpc_file;	//(11) SEA NPC seanpc.pos

//FUNCTIONS /////////////////////////////////////////////////////////////////////////////////////////
extern  void    change_app_state(void);
extern  void    set_next_app_state(DWORD dwNextState);




#endif//_CLIENTMAIN_H_
