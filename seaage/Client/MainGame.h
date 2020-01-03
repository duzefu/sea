/*
**  MainGame.h
**  game main functions.
**
**  Jack, 2002.5.15.
*/
#ifndef _MAINGAME_H_
#define _MAINGAME_H_


//DEFINES ////////////////////////////////////////////////////////////////////////////////////////////////////////
#define MAX_GAME_FONT_COLORS        16

typedef	enum	UI_KEEP_ENUMS
{	DRAG_EVENT_PERIOD_MAP		=   250,	//ms
DRAG_EVENT_PERIOD_NPC			=	200,	//ms
//
INVALID_MOUSE_RANGE_HALF_WIDTH	=	40,		//pixels
INVALID_MOUSE_RANGE_HALF_HEIGHT	=	24,		//pixels
} UI_KEEP_ENUMS;


//GAME CONFIG SHOW FLAGS
#define CONFIG_SHOW_MAP_MASK        0x00000001  //顯示地圖阻擋
#define CONFIG_SHOW_MAP_PROC        0x00000002  //顯示地圖事件
#define CONFIG_SHOW_GAME_INFO       0x00000004  //顯示地圖debug訊息
#define CONFIG_SHOW_NPC_NAME        0x00000008  //顯示npc的名稱
#define	CONFIG_SHOW_DEBUG_MINIMAP	0x00000010	//顯示DEBUG用的縮小地圖
#define	CONFIG_SHOW_GAME_RANGE		0x00000020	//顯示DEBUG用的GAME-RANGE.


// STRUCTURES //////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct  tagRGB_COLOR
{
    UCHR    r;
    UCHR    g;
    UCHR    b;
    PIXEL   color;
} RGB_COLOR, *LPRGB_COLOR;


typedef struct tagGAME_CONFIG 
{
    ULONG   show_flags;             //顯示標誌
} GAME_CONFIG, *LPGAME_CONFIG;


//GLOBALS ////////////////////////////////////////////////////////////////////////////////////////////////////////
extern  RGB_COLOR   game_font_colors[MAX_GAME_FONT_COLORS];
extern	SLONG		g_IsExitingGame; //紀錄遊戲是否正在退出(當玩家按ESC以後).


//FUNCTIONS //////////////////////////////////////////////////////////////////////////////////////////////////////
extern  void    init_game_colors(void);
//
extern  int     init_main_game(void);
extern  void    active_main_game(int active);
extern  void    free_main_game(void);
extern  void    refresh_main_game(void);
extern  void    refresh_main_game_once(void);
extern  void    redraw_main_game(SLONG sx, SLONG sy, void *vbitmap);
extern  SLONG   handle_main_game(UINT message, WPARAM wParam, LPARAM lParam);
//
extern  void    refresh_mouse_hand_doing(void);
//
//game config functions -----------------------------------------------------------
extern  int     init_game_config(void);
extern  void    free_game_config(void);
extern  void    active_game_config(int active);
//
extern  void    set_game_config_show_map_mask(SLONG flag);
extern  SLONG   get_game_config_show_map_mask(void);
extern  void    set_game_config_show_map_proc(SLONG flag);
extern  SLONG   get_game_config_show_map_proc(void);
extern  void    set_game_config_show_game_info(SLONG flag);
extern  SLONG   get_game_config_show_game_info(void);
extern  void    set_game_config_show_npc_name(SLONG flag);
extern  SLONG   get_game_config_show_npc_name(void);
extern	void	set_game_config_show_debug_minimap(SLONG flag);
extern	SLONG	get_game_config_show_debug_minimap(void);
extern	void	set_game_config_show_game_range(SLONG flag);
extern	SLONG	get_game_config_show_game_range(void);
//
extern  void    debug_redraw_game_map_mask(BMP *bitmap);
extern  void    debug_redraw_game_map_proc(BMP *bitmap);
extern  void    debug_redraw_game_info(BMP *bitmap);
extern	void	debug_redraw_game_minimap(BMP *bitmap);
extern	void	debug_redraw_game_range(void *vbitmap);
//
extern	SLONG	get_send_bps(void);
extern	SLONG	get_recv_bps(void);




#endif//_GAMEGAME_H_
