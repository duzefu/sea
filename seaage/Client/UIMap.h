/*
**  UIMap.h
**  ui map functions header.
**
**  Jack, 2002.5.31.
*/
#ifndef _UIMAP_H_
#define _UIMAP_H_

#include "qqedit.h"

// DEFINES /////////////////////////////////////////////////////////////////////////////////////////////////////////
#define CHAT_INPUT_LEN                  64  //聊天訊息的最大長度

#define UIFLAG_MAXIMIZE                 0x00000001  //最大化顯示

//ui action defines --------------------------
#define UIACTION_OPEN                   1
#define UIACTION_CLOSE                  2
#define UIACTION_SWITCH                 3


//sub menu defines ---------------------------
#define SUBMENU_NONE        0   //沒有選單
#define SUBMENU_STATE       1   //狀態選單
#define SUBMENU_ITEM        2   //物品選單
#define SUBMENU_SKILL       3   //技能選單
#define SUBMENU_TASK        4   //任務選單
#define SUBMENU_SHIP        5   //船隻選單



typedef enum    UIMAP_ENUMS
{   UIMAP_LEFT_FRAME_BKGND          =   0,
UIMAP_LEFT_FRAME_FACE_MASK          =   1,
UIMAP_LEFT_FRAME_HP_BKGND           =   2,
UIMAP_LEFT_FRAME_MP_BKGND           =   3,
UIMAP_LEFT_FRAME_HP_BAR             =   4,
UIMAP_LEFT_FRAME_MP_BAR             =   5,
UIMAP_LEFT_FRAME_MINIMIZE           =   6,
UIMAP_LEFT_FRAME_STATE              =   9,
UIMAP_LEFT_FRAME_ITEM               =   12,
UIMAP_LEFT_FRAME_MAGIC              =   15,
UIMAP_LEFT_FRAME_TASK               =   18,
UIMAP_LEFT_FRAME_SHIP               =   21,
UIMAP_LEFT_FRAME_FIGHT_OFF          =   24,
UIMAP_LEFT_FRAME_FIGHT_ON           =   25,
UIMAP_LEFT_FRAME_FIGHT_NEXT_STATE   =   26,
UIMAP_LEFT_FRAME_FIGHT_PREV_STATE   =   29,
UIMAP_LEFT_FRAME_SMALLICON          =   32,
UIMAP_LEFT_FRAME_TITLE_STATE        =   33,
UIMAP_LEFT_FRAME_TITLE_ITEM         =   34,
UIMAP_LEFT_FRAME_TITLE_MAGIC        =   35,
UIMAP_LEFT_FRAME_TITLE_TASK         =   36,
UIMAP_LEFT_FRAME_TITLE_SHIP         =   37,
//
UIMAP_RIGHT_FRAME_BKGND             =   0,
UIMAP_RIGHT_FRAME_CHAT_RECORD       =   1,
UIMAP_RIGHT_FRAME_MINIMIZE          =   3,
UIMAP_RIGHT_FRAME_ADDRESS_BOOK      =   6,
UIMAP_RIGHT_FRAME_SMALLICON         =   9,
//
UIMAP_FACE_FRAME_MANFACE_0          =   0,
UIMAP_FACE_FRAME_MANFACE_1          =   2,
UIMAP_FACE_FRAME_MANFACE_2          =   4,
UIMAP_FACE_FRAME_MANFACE_3          =   6,
UIMAP_FACE_FRAME_MANFACE_4          =   8,
UIMAP_FACE_FRAME_MANFACE_5          =   10,
UIMAP_FACE_FRAME_MANFACE_6          =   12,
UIMAP_FACE_FRAME_MINIMIZE           =   14,
//
//UIMAP_MINIMAP_FRAME_BKGND           =   0,
//UIMAP_MINIMAP_FRAME_MINIMIZE        =   1,
//UIMAP_MINIMAP_FRAME_WEATHER_0       =   4,
//UIMAP_MINIMAP_FRAME_SMALLICON       =   9,
//UIMAP_MINIMAP_FRAME_WIND_DIR_0      =   0,
//UIMAP_MINIMAP_FRAME_SHIP_SPEED_0    =   0,

UIMAP_MINIMAP_FRAME_BKGND           =   0,
UIMAP_MINIMAP_FRAME_MINIMIZE        =   1,
UIMAP_MINIMAP_FRAME_SETTING         =   3,
UIMAP_MINIMAP_FRAME_MAXIMIZE        =   6,
UIMAP_MINIMAP_FRAME_WIND_DIR_0      =   0,
UIMAP_MINIMAP_FRAME_SHIP_SPEED_0    =   0,

//
UIMAP_EVENT                 =   3000,
//left------------
UIMAP_ID_BKGND              =   0,
UIMAP_ID_HP                 =   10,
UIMAP_ID_MP                 =   20,
UIMAP_ID_GOLD               =   30,
UIMAP_ID_LEFT_MINIMIZE      =   40,
UIMAP_ID_PLAYER_FACE        =   50,
UIMAP_ID_FIGHT_STATE        =   60,
UIMAP_ID_FIGHT_NEXT_STATE   =   61,
UIMAP_ID_FIGHT_PREV_STATE   =   62,
UIMAP_ID_STATE              =   70,
UIMAP_ID_TITLE_STATE        =   71,
UIMAP_ID_ITEM               =   80,
UIMAP_ID_TITLE_ITEM         =   81,
UIMAP_ID_MAGIC              =   90,
UIMAP_ID_TITLE_MAGIC        =   91,
UIMAP_ID_TASK               =   100,
UIMAP_ID_TITLE_TASK         =   101,
UIMAP_ID_SHIP               =   110,
UIMAP_ID_TITLE_SHIP         =   111,
UIMAP_ID_LEFT_MAXIMIZE      =   115,
//right-----------
UIMAP_ID_LEFT_QUICK_MAGIC   =   120,
UIMAP_ID_RIGHT_QUICK_MAGIC  =   130,
UIMAP_ID_CHAT_INPUT         =   140,
UIMAP_ID_ADDRESS_BOOK       =   150,
//
UIMAP_ID_QUICK_ITEM_0       =   160,
UIMAP_ID_QUICK_ITEM_1       =   161,
UIMAP_ID_QUICK_ITEM_2       =   162,
UIMAP_ID_QUICK_ITEM_3       =   163,
//
UIMAP_ID_RIGHT_MINIMIZE     =   200,
UIMAP_ID_CHAT_RECORD        =   210,
UIMAP_ID_RIGHT_MAXIMIZE     =   211,
//team manface-----
UIMAP_ID_MANFACE_0          =   220,
UIMAP_ID_MANFACE_1          =   230,
UIMAP_ID_MANFACE_2          =   240,
UIMAP_ID_MANFACE_3          =   250,
UIMAP_ID_MANFACE_4          =   260,
UIMAP_ID_MANFACE_5          =   270,
UIMAP_ID_MANFACE_6          =   280,
UIMAP_ID_MANFACE_7          =   290,

UIMAP_ID_MANFACE_MINIMIZE   =   290,
UIMAP_ID_MANFACE_MAXIMIZE   =   291,
//minimap----------

UIMAP_ID_MINIMAP_MINIMIZE   =   300,
UIMAP_ID_SHIP_SPEED         =   310,
UIMAP_ID_WIND_DIRECTION     =   320,
UIMAP_ID_SETTING            =   330,
UIMAP_ID_MINIMAP_MAXIMIZE   =   350,
// Zhang Zhaohui
UIMAP_ID_MINIMAP            = 360,
//

//left-------------
UIMAP_LEFT_BKGND_SX         =   0,
UIMAP_LEFT_BKGND_SY         =   486,
UIMAP_LEFT_BKGND_XL         =   219,
UIMAP_LEFT_BKGND_YL         =   600 - 486,
UIMAP_HP_BAR_SX             =   112,
UIMAP_HP_BAR_SY             =   526,
UIMAP_HP_BAR_XL             =   200 - 112,
UIMAP_HP_BAR_YL             =   540 - 526,
UIMAP_MP_BAR_SX             =   112,
UIMAP_MP_BAR_SY             =   544,
UIMAP_MP_BAR_XL             =   200 - 112,
UIMAP_MP_BAR_YL             =   558 - 544,
UIMAP_GOLD_BAR_SX           =   82,
UIMAP_GOLD_BAR_SY           =   576,
UIMAP_GOLD_BAR_XL           =   214 - 82,
UIMAP_GOLD_BAR_YL           =   600 - 576,
UIMAP_PLAYER_FACE_SX        =   14,
UIMAP_PLAYER_FACE_SY        =   504,
UIMAP_PLAYER_FACE_XL        =   62 - 14,
UIMAP_PLAYER_FACE_YL        =   560 - 504,
UIMAP_FIGHT_SWITCH_SX       =   6,
UIMAP_FIGHT_SWITCH_SY       =   580,
UIMAP_FIGHT_SWITCH_XL       =   68 - 6,
UIMAP_FIGHT_SWITCH_YL       =   594 - 580,
UIMAP_LEFT_MINIMIZE_SX      =   0,
UIMAP_LEFT_MINIMIZE_SY      =   474,
UIMAP_LEFT_MINIMIZE_XL      =   16 - 0,
UIMAP_LEFT_MINIMIZE_YL      =   492 - 474,
UIMAP_STATE_SX              =   86,
UIMAP_STATE_SY              =   484,
UIMAP_STATE_XL              =   108 - 86,
UIMAP_STATE_YL              =   508 - 484,
UIMAP_ITEM_SX               =   112,
UIMAP_ITEM_SY               =   484,
UIMAP_ITEM_XL               =   134 - 112,
UIMAP_ITEM_YL               =   508 - 484,
UIMAP_MAGIC_SX              =   138,
UIMAP_MAGIC_SY              =   484,
UIMAP_MAGIC_XL              =   158 - 138,
UIMAP_MAGIC_YL              =   508 - 484,
UIMAP_TASK_SX               =   162,
UIMAP_TASK_SY               =   484,
UIMAP_TASK_XL               =   184 - 162,
UIMAP_TASK_YL               =   508 - 484,
UIMAP_SHIP_SX               =   188,
UIMAP_SHIP_SY               =   484,
UIMAP_SHIP_XL               =   210 - 188,
UIMAP_SHIP_YL               =   508 - 484,
//right------------
UIMAP_RIGHT_BKGND_SX        =   226,
UIMAP_RIGHT_BKGND_SY        =   542,
UIMAP_RIGHT_BKGND_XL        =   800 - 226,
UIMAP_RIGHT_BKGND_YL        =   600 - 542,
UIMAP_LEFT_QUICK_MAGIC_SX   =   232,
UIMAP_LEFT_QUICK_MAGIC_SY   =   552,
UIMAP_LEFT_QUICK_MAGIC_XL   =   261 - 231,
UIMAP_LEFT_QUICK_MAGIC_YL   =   582 - 552,
UIMAP_RIGHT_QUICK_MAGIC_SX  =   581,
UIMAP_RIGHT_QUICK_MAGIC_SY  =   550,
UIMAP_RIGHT_QUICK_MAGIC_XL  =   609 - 581,
UIMAP_RIGHT_QUICK_MAGIC_YL  =   578 - 550,
UIMAP_CHAT_INPUT_SX         =   279,
UIMAP_CHAT_INPUT_SY         =   556,
UIMAP_CHAT_INPUT_XL         =   517 - 279,
UIMAP_CHAT_INPUT_YL         =   574 - 556,
UIMAP_ADDRESS_BOOK_SX       =   527,
UIMAP_ADDRESS_BOOK_SY       =   554,
UIMAP_ADDRESS_BOOK_XL       =   565 - 527,
UIMAP_ADDRESS_BOOK_YL       =   574 - 554,
UIMAP_QUICK_ITEM_0_SX       =   624,
UIMAP_QUICK_ITEM_0_SY       =   548,
UIMAP_QUICK_ITEM_0_XL       =   30,
UIMAP_QUICK_ITEM_0_YL       =   30,
UIMAP_QUICK_ITEM_1_SX       =   665,
UIMAP_QUICK_ITEM_1_SY       =   548,
UIMAP_QUICK_ITEM_1_XL       =   30,
UIMAP_QUICK_ITEM_1_YL       =   30,
UIMAP_QUICK_ITEM_2_SX       =   706,
UIMAP_QUICK_ITEM_2_SY       =   548,
UIMAP_QUICK_ITEM_2_XL       =   30,
UIMAP_QUICK_ITEM_2_YL       =   30,
UIMAP_QUICK_ITEM_3_SX       =   749,
UIMAP_QUICK_ITEM_3_SY       =   548,
UIMAP_QUICK_ITEM_3_XL       =   30,
UIMAP_QUICK_ITEM_3_YL       =   30,
UIMAP_RIGHT_MINIMIZE_SX     =   782,
UIMAP_RIGHT_MINIMIZE_SY     =   554,
UIMAP_RIGHT_MINIMIZE_XL     =   796 - 782,
UIMAP_RIGHT_MINIMIZE_YL     =   570 - 554,
UIMAP_CHAT_RECORD_SX        =   405,
UIMAP_CHAT_RECORD_SY        =   534,
UIMAP_CHAT_RECORD_XL        =   421 - 405,
UIMAP_CHAT_RECORD_YL        =   548 - 534,
//team manface
UIMAP_MANFACE_DX            =   56,
UIMAP_MANFACE_W             =   45,
UIMAP_MANFACE_H             =   60,

UIMAP_MANFACE_0_SX          =   7,
UIMAP_MANFACE_0_SY          =   4,
/*
UIMAP_MANFACE_0_XL          =   47 - 5,
UIMAP_MANFACE_0_YL          =   60 - 4,
UIMAP_MANFACE_1_SX          =   63,
UIMAP_MANFACE_1_SY          =   8,
UIMAP_MANFACE_1_XL          =   101 - 63,
UIMAP_MANFACE_1_YL          =   60 - 8,
UIMAP_MANFACE_2_SX          =   123,
UIMAP_MANFACE_2_SY          =   8,
UIMAP_MANFACE_2_XL          =   159 - 123,
UIMAP_MANFACE_2_YL          =   60 - 8,
UIMAP_MANFACE_3_SX          =   179,
UIMAP_MANFACE_3_SY          =   8,
UIMAP_MANFACE_3_XL          =   215 - 179,
UIMAP_MANFACE_3_YL          =   60 - 8,
UIMAP_MANFACE_4_SX          =   233,
UIMAP_MANFACE_4_SY          =   8,
UIMAP_MANFACE_4_XL          =   271 - 233,
UIMAP_MANFACE_4_YL          =   60 - 8,
UIMAP_MANFACE_5_SX          =   289,
UIMAP_MANFACE_5_SY          =   8,
UIMAP_MANFACE_5_XL          =   327 - 289,
UIMAP_MANFACE_5_YL          =   60 - 8,
UIMAP_MANFACE_6_SX          =   347,
UIMAP_MANFACE_6_SY          =   8,
UIMAP_MANFACE_6_XL          =   385 - 347,
UIMAP_MANFACE_6_YL          =   60 - 8,
*/
UIMAP_MANFACE_MINIMIZE_SX   =   190,
UIMAP_MANFACE_MINIMIZE_SY   =   67,
UIMAP_MANFACE_MINIMIZE_XL   =   206 - 190,
UIMAP_MANFACE_MINIMIZE_YL   =   84 - 67,
//minimap
UIMAP_MINIMAP_BKGND_SX      =   610,
UIMAP_MINIMAP_BKGND_SY      =   0,
UIMAP_MINIMAP_BKGND_XL      =   800 - 610,
UIMAP_MINIMAP_BKGND_YL      =   150 - 0,
UIMAP_MINIMAP_MINIMIZE_SX   =   640,
UIMAP_MINIMAP_MINIMIZE_SY   =   114,
UIMAP_MINIMAP_MINIMIZE_XL   =   659 - 640,
UIMAP_MINIMAP_MINIMIZE_YL   =   132 - 114,
UIMAP_MINIMAP_WEATHER_SX    =   767,
UIMAP_MINIMAP_WEATHER_SY    =   16,
UIMAP_MINIMAP_WEATHER_XL    =   793 - 767,
UIMAP_MINIMAP_WEATHER_YL    =   48 - 16,
} UIMAP_ENUMS;


// STRUCTURES //////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct tagUIIMAGE
{
    CAKE_FRAME_ANI  *cfa;       //image ani pointer
    CAKE_FRAME      *cf[256];   //each image frame pointer
    //
    SLONG   hilight_id;         //hilight id
    SLONG   active_id;          //active id
    SLONG   function_id;        //function id
} UIIMAGE, *LPUIIMAGE;


typedef struct tagUI_HPBAR 
{
    CAKE_FRAME_ANI  *cfa;       //npc hp bar images pointer
    CAKE_FRAME      *cf[4];     //npc hp bar image frames pointer
} UI_HPBAR, *LPUI_HPBAR;


typedef struct tagUIMAP_DATA
{
    SLONG   left_alpha;
    SLONG   left_alpha_update;

    SLONG   right_alpha;
    SLONG   right_alpha_update;

    SLONG   minimap_alpha;
    SLONG   minimap_alpha_update;

    SLONG   manface_y;
    SLONG   manface_y_update;
    SLONG   manface_y_limited;
    SLONG   manface_alpha;
    SLONG   manface_alpha_update;
    //
    SLONG   hilight_id;         //hilight id
    SLONG   active_id;          //active id
    SLONG   function_id;        //function id
    //
    UI_TEXT     *pchat;
/*
    USTR    chat_input[CHAT_INPUT_LEN];    //輸入的對話訊息
    SLONG   chat_input_index;   //輸入對話訊息的光標位置
    SLONG   chat_input_max;     //當前輸入的文字的長度(BYTES)
    SLONG   chat_show_index;    //顯示輸入的文字起始位置
    SLONG   chat_show_len;      //顯示輸入的文字的字節長度
    SLONG   enable_chat_ime;    //紀錄聊天時是否打開ime輸入
    USTR    chat_ime_name[64];  //紀錄聊天時ime輸入法的名稱
*/
    //
    SLONG   wind_dir;           //當前顯示的風向
    SLONG   ship_speed;         //船速(0~20)
    SLONG   map_dark;           //地圖黑暗狀況(白天黑夜)
    //
    SLONG   opened_submenu;     //目前打開的子選單(SUBMENU_$$$)
    SLONG   show_chat_records;  //顯示聊天紀錄
    SLONG   show_quick_magics;  //顯示快捷技能設置
    //
    // backup F10 switch map menu state ---------
    SLONG   backuped;                       //1 for backuped, 0 for restored.
    SLONG   backup_minimap_flags;
    SLONG   backup_left_flags;
    SLONG   backup_right_flags;
    SLONG   backup_manface_flags;

    SLONG   backup_opened_submenu;
    SLONG   backup_show_chat_records;
    SLONG   backup_show_qq;

} UIMAP_DATA, *LPUIMAP_DATA;


// GLOBALS /////////////////////////////////////////////////////////////////////////////////////////////////////////
extern  UIMAP_DATA  uimap_data;
extern  UI_HPBAR    ui_hpbar;


// FUNCTIONS ///////////////////////////////////////////////////////////////////////////////////////////////////////
int     init_map_ui(void);
void    active_map_ui(int active);
void    free_map_ui(void);
//
SLONG   load_ui_image(USTR *fname, UIIMAGE **ui);
void    free_ui_image(UIIMAGE **ui);
//
void    init_uimap_data(void);
void    redraw_map_ui(BMP *bitmap);
//
void    full_redraw_map_ui_left(BMP *bitmap);
void    fade_redraw_map_ui_left(BMP *bitmap);
void    minimize_redraw_map_ui_left(BMP *bitmap);
void    redraw_map_ui_left(BMP *bitmap);
void    redraw_map_ui_left_title(SLONG sx, SLONG sy, SLONG active_id, BMP *bitmap);
void    refresh_map_ui_left(void);
void    minimize_map_ui_left(void);
void    maximize_map_ui_left(void);
//
void    full_redraw_map_ui_right(BMP *bitmap);
void    fade_redraw_map_ui_right(BMP *bitmap);
void    minimize_redraw_map_ui_right(BMP *bitmap);
void    redraw_map_ui_right(BMP *bitmap);
void    refresh_map_ui_right(void);
void    minimize_map_ui_right(void);
void    maximize_map_ui_right(void);
//
void    full_redraw_map_ui_minimap(BMP *bitmap);
void    fade_redraw_map_ui_minimap(BMP *bitmap);
void    minimize_redraw_map_ui_minimap(BMP *bitmap);
void    redraw_map_ui_minimap(BMP *bitmap);
void    refresh_map_ui_minimap(void);
void    minimize_map_ui_minimap(void);
void    maximize_map_ui_minimap(void);
//
void    full_redraw_map_ui_manface(BMP *bitmap);
void    fade_redraw_map_ui_manface(BMP *bitmap);
void    minimize_redraw_map_ui_manface(BMP *bitmap);
void    redraw_map_ui_manface(BMP *bitmap);
void    refresh_map_ui_manface(void);
void    minimize_map_ui_manface(void);
void    maximize_map_ui_manface(void);
//
void    refresh_map_ui(void);
//
void    redraw_map_ui_mouse_point_info(SLONG id, BMP *bitmap);
//
SLONG   get_map_dark(void);
void    set_map_dark(SLONG dark);
SLONG   is_maingame_enable_chat_ime(void);
void    set_maingame_enable_chat_ime(SLONG flag);
//
SLONG   get_show_chat_records_flag(void);
void    set_show_chat_records_flag(SLONG flag);
void    switch_show_chat_records_flag(void);
//
SLONG   is_map_submenu_opened(SLONG submenu_index);
void    direct_open_map_submenu(SLONG submenu_index);
void    direct_close_map_submenu(SLONG submenu_index);
void    open_map_submenu(SLONG submenu_index);
void    close_map_submenu(SLONG submenu_index);
//
int     init_ui_hpbar(void);
void    free_ui_hpbar(void);
void    redraw_ui_hpbar_background(BMP *bitmap);
void    redraw_npc_mouse_point_info(SLONG id, BMP *bitmap);
//
SLONG   exec_left_hit_uimap(SLONG event_id);
SLONG	exec_right_hit_uimap(SLONG event_id);
//
//
BMP*    load_fff(char *filename);
void    init_minimap(void);
SLONG   load_minimap_of_jpg(USTR *filename);
SLONG   load_minimap_of_fff(USTR *filename);
void    redraw_minimap(BMP *bitmap);
void    free_minimap(void);
//
void	debug_redraw_game_minimap(BMP *bitmap);



#endif//_UIMAP_H_
