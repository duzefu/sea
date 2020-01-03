/*
**  UI.h
**  user interface functions header.
**
**  Jack, 2002.5.9.
*/
#ifndef _UI_H_
#define _UI_H_
#include "CRange.h"
#include "ImageRim.h"
#include "SwapScr.h"
#include "LineDlink.h"
#include "UIInfoBar.h"
#include "UIAccMan.h"
#include "UIMap.h"
#include "UIManface.h"
#include "UIMapState.h"
#include "UIMapItem.h"
#include "UIMapSkill.h"
#include "UIMapTask.h"
#include "UIMapShip.h"
#include "MouseHand.h"
#include "UIComboBox.h"

#include "qqedit.h"

// DEFINES ///////////////////////////////////////////////////////////////////////////////////////
typedef enum    EULA_ENUMS
{   EULA_FRAME_BKGND            =   0,
EULA_FRAME_VSCROLL_BAR          =   1,
EULA_FRAME_OK                   =   3,
EULA_FRAME_BACK                 =   6,
//
EULA_EVENT                      =   9999,
EULA_ID_BKGND                   =   0,
EULA_ID_VSCROLL_BKGND           =   10,
EULA_ID_VSCROLL_BAR             =   20,
EULA_ID_OK                      =   30,
EULA_ID_BACK                    =   40,
//
EULA_VSCROLL_BKGND_SX           =   737,
EULA_VSCROLL_BKGND_SY           =   107,
EULA_VSCROLL_BKGND_XL           =   759 - 737,
EULA_VSCROLL_BKGND_YL           =   510 - 107,
EULA_TEXT_LINES                 =   18,
EULA_TEXT_LINE_0_SX             =   128,
EULA_TEXT_LINE_0_SY             =   120,
EULA_TEXT_LINE_DX               =   0,
EULA_TEXT_LINE_DY               =   20,
} EULA_ENUMS;


typedef enum    UILOGIN_ENUMS
{   UILOGIN_FRAME_BKGND         =   0,
UILOGIN_FRAME_NEW_ACCOUNT       =   1,
UILOGIN_FRAME_ACCOUNT_MANAGER   =   4,
UILOGIN_FRAME_BACK              =   7,
UILOGIN_FRAME_POS_TEXT          =   10,
UILOGIN_FRAME_STEERING_WHEEL    =   11,
UILOGIN_FRAME_OK_LOGIN          =   18,
//
UILOGIN_EVENT                   =   1000,
UILOGIN_ID_BKGND                =   0,
UILOGIN_ID_NEW_ACCOUNT          =   10,
UILOGIN_ID_ACCOUNT_MANAGER      =   20,
UILOGIN_ID_BACK                 =   30,
UILOGIN_ID_STEERING_WHEEL       =   40,
UILOGIN_ID_ACCOUNT              =   50,
UILOGIN_ID_PASSWORD             =   60,
UILOGIN_ID_OK_LOGIN             =   70,
//
UILOGIN_ACCOUNT_BAR_SX          =   365,
UILOGIN_ACCOUNT_BAR_SY          =   350,
UILOGIN_ACCOUNT_BAR_XL          =   673 - 365,
UILOGIN_ACCOUNT_BAR_YL          =   388 - 350,
UILOGIN_ACCOUNT_INPUT_SX        =   464,
UILOGIN_ACCOUNT_INPUT_SY        =   362,
UILOGIN_ACCOUNT_INPUT_XL        =   659 - 464,
UILOGIN_ACCOUNT_INPUT_YL        =   384 - 362,
UILOGIN_PASSWORD_BAR_SX         =   365,
UILOGIN_PASSWORD_BAR_SY         =   414,
UILOGIN_PASSWORD_BAR_XL         =   673 - 365,
UILOGIN_PASSWORD_BAR_YL         =   454 - 414,
UILOGIN_PASSWORD_INPUT_SX       =   464,
UILOGIN_PASSWORD_INPUT_SY       =   427,
UILOGIN_PASSWORD_INPUT_XL       =   659 - 464,
UILOGIN_PASSWORD_INPUT_YL       =   447 - 427,
} UILOGIN_ENUMS;


typedef enum    CREDITS_ENUMS
{   CREDITS_FRAME_BKGND         =   0,
CREDITS_FRAME_BACK              =   1,
CREDITS_FRAME_TEXT              =   4,
//
CREDITS_EVENT                   =   1001,
CREDITS_ID_BKGND                =   0,
CREDITS_ID_BACK                 =   10,
//
CREDITS_TEXT_BAR_SX             =   415,
CREDITS_TEXT_BAR_SY             =   62,
CREDITS_TEXT_BAR_XL             =   715 - 415,
CREDITS_TEXT_BAR_YL             =   474 - 62,
} CREDITS_ENUMS;


typedef enum    SWS_ENUMS   //select world server
{   SWS_FRAME_BKGND             =   0,
SWS_FRAME_OK                    =   1,
SWS_FRAME_BACK                  =   4,
SWS_FRAME_VSCROLL_BAR           =   7,
SWS_FRAME_SELECT_BKGND          =   9,
//
SWS_EVENT                       =   1002,
SWS_ID_BKGND                    =   0,
SWS_ID_OK                       =   10,
SWS_ID_BACK                     =   20,
SWS_ID_VSCROLL_BKGND            =   30,                  
SWS_ID_VSCROLL_BAR              =   40,
SWS_ID_SERVER_LIST_0            =   50,
//
SWS_SERVER_LIST_0_BAR_SX        =   219,
SWS_SERVER_LIST_0_BAR_SY        =   166,
SWS_SERVER_LIST_BAR_DY          =   71,
SWS_SERVER_LIST_BAR_XL          =   707 - 219,
SWS_SERVER_LIST_BAR_YL          =   228 - 166,
SWS_SERVER_LIST_INFO_RX         =   52,
SWS_SERVER_LIST_INFO_RY         =   23,
SWS_SERVER_LIST_NUM             =   5,
SWS_VSCROLL_BKGND_SX            =   737,
SWS_VSCROLL_BKGND_SY            =   107,
SWS_VSCROLL_BKGND_XL            =   759 - 737,
SWS_VSCROLL_BKGND_YL            =   510 - 107,

//
MOUSE_EVENT_VSCROLL             =   1,
} SWS_ENUMS;


typedef enum    SELCHAR_ENUMS
{   SELCHAR_FRAME_BKGND         =   0,
SELCHAR_FRAME_NEW_CHAR          =   1,
SELCHAR_FRAME_CHAR_0            =   2,
SELCHAR_FRAME_DELETE_CHAR       =   16,
SELCHAR_FRAME_OK                =   19,
SELCHAR_FRAME_BACK              =   22,
//
SELCHAR_EVENT                   =   1003,
SELCHAR_ID_BKGND                =   0,
SELCHAR_ID_DELETE_CHAR          =   10,
SELCHAR_ID_OK                   =   20,
SELCHAR_ID_BACK                 =   30,
SELCHAR_ID_CHAR_0               =   100,
//
SELCHAR_MAINNAME_SX             =   182,
SELCHAR_MAINNAME_SY             =   364,
SELCHAR_NICKNAME_SX             =   182,
SELCHAR_NICKNAME_SY             =   400,
SELCHAR_CAREER_SX               =   182,
SELCHAR_CAREER_SY               =   436,
SELCHAR_LEVEL_SX                =   182,
SELCHAR_LEVEL_SY                =   472,
SELCHAR_COUNTRY_SX              =   320,
SELCHAR_COUNTRY_SY              =   472,
SELCHAR_RANK_SX                 =   182,
SELCHAR_RANK_SY                 =   508,
SELCHAR_CHAR_0_SX               =   70,
SELCHAR_CHAR_0_SY               =   80,
SELCHAR_CHAR_DX                 =   170,
SELCHAR_CHAR_DY                 =   0,
} SELCHAR_ENUMS;


typedef enum    CREATECHAR_ENUMS
{   CREATECHAR_FRAME_BKGND      =   0,
CREATECHAR_FRAME_OK             =   1,
CREATECHAR_FRAME_BACK           =   4,

//
CREATECHAR_EVENT                =   1004,
CREATECHAR_ID_BKGND             =   0,
CREATECHAR_ID_OK                =   10,
CREATECHAR_ID_BACK              =   40,
CREATECHAR_ID_BODY_0            =   100,
//
CREATECHAR_BODY_0_SX            =   47,
CREATECHAR_BODY_0_SY            =   72,
CREATECHAR_BODY_1_SX            =   165,
CREATECHAR_BODY_1_SY            =   98,
CREATECHAR_BODY_2_SX            =   295,
CREATECHAR_BODY_2_SY            =   116,
CREATECHAR_BODY_3_SX            =   423,
CREATECHAR_BODY_3_SY            =   116,
CREATECHAR_BODY_4_SX            =   553,
CREATECHAR_BODY_4_SY            =   120,
CREATECHAR_BODY_5_SX            =   677,
CREATECHAR_BODY_5_SY            =   60,
CREATECHAR_BODY_6_SX            =   79,
CREATECHAR_BODY_6_SY            =   250,
CREATECHAR_BODY_7_SX            =   529,
CREATECHAR_BODY_7_SY            =   273,
CREATECHAR_BODY_8_SX            =   652,
CREATECHAR_BODY_8_SY            =   236,
CREATECHAR_BODY_9_SX            =   37,
CREATECHAR_BODY_9_SY            =   380,
CREATECHAR_BODY_10_SX           =   145,
CREATECHAR_BODY_10_SY           =   432,
CREATECHAR_BODY_11_SX           =   269,
CREATECHAR_BODY_11_SY           =   472,
CREATECHAR_BODY_12_SX           =   403,
CREATECHAR_BODY_12_SY           =   452,
CREATECHAR_BODY_13_SX           =   537,
CREATECHAR_BODY_13_SY           =   440,
CREATECHAR_BODY_XL              =   113 - 47,
CREATECHAR_BODY_YL              =   168 - 72,
CREATECHAR_MAX_BODY             =   14,
//
CREATECHAR_TEXT_BAR_SX          =   291,
CREATECHAR_TEXT_BAR_SY          =   272,
CREATECHAR_TEXT_BAR_XL          =   459 - 291,
CREATECHAR_TEXT_BAR_YL          =   395 - 272,
CREATECHAR_TEXT_DY              =   20,
//
} CREATECHAR_ENUMS;


typedef enum    SETCHARFACE_ENUMS
{   SETCHARFACE_FRAME_BKGND     =   0,
SETCHARFACE_FRAME_OK            =   1,
SETCHARFACE_FRAME_BACK          =   4,
SETCHARFACE_FRAME_PREV_EYE      =   7,
SETCHARFACE_FRAME_NEXT_EYE      =   10,
SETCHARFACE_FRAME_PREV_MOUTH    =   13,
SETCHARFACE_FRAME_NEXT_MOUTH    =   16,
//
SETCHARFACE_EVENT               =   1005,
SETCHARFACE_ID_BKGND            =   0,
SETCHARFACE_ID_MAINNAME         =   10,
SETCHARFACE_ID_NICKNAME         =   20,
SETCHARFACE_ID_PREV_EYE         =   30,
SETCHARFACE_ID_NEXT_EYE         =   40,
SETCHARFACE_ID_PREV_MOUTH       =   50,
SETCHARFACE_ID_NEXT_MOUTH       =   60,
SETCHARFACE_ID_OK               =   70,
SETCHARFACE_ID_BACK             =   80,
//
SETCHARFACE_MAINNAME_SX         =   130,
SETCHARFACE_MAINNAME_SY         =   165,
SETCHARFACE_MAINNAME_XL         =   398 - 130,
SETCHARFACE_MAINNAME_YL         =   190 - 165,
SETCHARFACE_NICKNAME_SX         =   130,
SETCHARFACE_NICKNAME_SY         =   232,
SETCHARFACE_NICKNAME_XL         =   398 - 130,
SETCHARFACE_NICKNAME_YL         =   257 - 232,
SETCHARFACE_FACE_SX             =   262,
SETCHARFACE_FACE_SY             =   310,
SETCHARFACE_CAREER_SX           =   129,
SETCHARFACE_CAREER_SY           =   464,
SETCHARFACE_STRENGTH_SX         =   591,    //力量
SETCHARFACE_STRENGTH_SY         =   156,
SETCHARFACE_FACILITY_SX         =   591,    //靈巧
SETCHARFACE_FACILITY_SY         =   214,
SETCHARFACE_WIT_SX              =   591,    //智力
SETCHARFACE_WIT_SY              =   268,
SETCHARFACE_STAMINA_SX          =   591,    //耐力
SETCHARFACE_STAMINA_SY          =   326,
SETCHARFACE_HP_SX               =   591,    //生命力
SETCHARFACE_HP_SY               =   380,
SETCHARFACE_MP_SX               =   591,    //魔力
SETCHARFACE_MP_SY               =   440,
SETCHARFACE_MAX_EYE             =   5,
SETCHARFACE_MAX_MOUTH           =   5,
//
} SETCHARFACE_ENUMS;


typedef enum    SETCHARLOCATE_ENUMS
{   SETCHARLOCATE_FRAME_BKGND   =   0,
SETCHARLOCATE_FRAME_OK          =   1,
SETCHARLOCATE_FRAME_BACK        =   4,
SETCHARLOCATE_FRAME_COUNTRY_0   =   7,
//
SETCHARLOCATE_EVENT             =   1006,
SETCHARLOCATE_ID_BKGND          =   0,
SETCHARLOCATE_ID_OK             =   10,
SETCHARLOCATE_ID_BACK           =   20,
SETCHARLOCATE_ID_COUNTRY_0      =   300,
//
SETCHARLOCATE_MAX_COUNTRY       =   6,
//
SETCHARLOCATE_TEXT_BAR_SX       =   458,
SETCHARLOCATE_TEXT_BAR_SY       =   256,
SETCHARLOCATE_TEXT_BAR_XL       =   706 - 458,
SETCHARLOCATE_TEXT_BAR_YL       =   440 - 256,
SETCHARLOCATE_TEXT_DY           =   20,
} SETCHARLOCATE_ENUMS;


typedef	enum	CHGCHARCOLOR_ENUMS
{	CHGCHARCOLOR_FRAME_BKGND			=	0,
CHGCHARCOLOR_FRAME_TURN_LEFT			=	1,
CHGCHARCOLOR_FRAME_TURN_RIGHT			=	4,
CHGCHARCOLOR_FRAME_COLOR_GRID			=	7,
CHGCHARCOLOR_FRAME_A_STYLE				=	8,
CHGCHARCOLOR_FRAME_B_STYLE				=	11,
CHGCHARCOLOR_FRAME_C_STYLE				=	14,
CHGCHARCOLOR_FRAME_SET_MY_CAP			=	17,
CHGCHARCOLOR_FRAME_SET_MY_HAIR			=	20,
CHGCHARCOLOR_FRAME_SET_MY_SKIN			=	23,
CHGCHARCOLOR_FRAME_SET_MY_CLOTH			=	26,
CHGCHARCOLOR_FRAME_SET_MY_GLOVE			=	29,
CHGCHARCOLOR_FRAME_SET_MY_SHOES			=	32,
CHGCHARCOLOR_FRAME_FINAL_OK				=	35,
CHGCHARCOLOR_FRAME_FINAL_CANCEL			=	38,
CHGCHARCOLOR_FRAME_RGB_BKGND			=	41,
CHGCHARCOLOR_FRAME_R_SCROLL_BAR			=	42,
CHGCHARCOLOR_FRAME_G_SCROLL_BAR			=	44,
CHGCHARCOLOR_FRAME_B_SCROLL_BAR			=	46,
CHGCHARCOLOR_FRAME_ALL_SCROLL_BAR		=	48,
CHGCHARCOLOR_FRAME_RGB_OK				=	50,
CHGCHARCOLOR_FRAME_RGB_CANCEL			=	53,
//
CHGCHARCOLOR_EVENT						=	1007,
CHGCHARCOLOR_ID_BKGND					=	0,
CHGCHARCOLOR_ID_TURN_LEFT				=	10,
CHGCHARCOLOR_ID_TURN_RIGHT				=	20,
CHGCHARCOLOR_ID_A_STYLE					=	30,
CHGCHARCOLOR_ID_B_STYLE					=	40,
CHGCHARCOLOR_ID_C_STYLE					=	50,
CHGCHARCOLOR_ID_SET_MY_CAP				=	60,
CHGCHARCOLOR_ID_SET_MY_HAIR				=	70,
CHGCHARCOLOR_ID_SET_MY_SKIN				=	80,
CHGCHARCOLOR_ID_SET_MY_CLOTH			=	90,
CHGCHARCOLOR_ID_SET_MY_GLOVE			=	100,
CHGCHARCOLOR_ID_SET_MY_SHOES			=	110,
CHGCHARCOLOR_ID_FINAL_OK				=	120,
CHGCHARCOLOR_ID_FINAL_CANCEL			=	130,
CHGCHARCOLOR_ID_RGB_OK					=	140,
CHGCHARCOLOR_ID_RGB_CANCEL				=	150,
CHGCHARCOLOR_ID_R_SCROLL_BKGND			=   160,
CHGCHARCOLOR_ID_R_SCROLL_BAR			=   170,
CHGCHARCOLOR_ID_G_SCROLL_BKGND			=   180,
CHGCHARCOLOR_ID_G_SCROLL_BAR			=   190,
CHGCHARCOLOR_ID_B_SCROLL_BKGND			=   200,
CHGCHARCOLOR_ID_B_SCROLL_BAR			=   210,
CHGCHARCOLOR_ID_ALL_SCROLL_BKGND		=   220,
CHGCHARCOLOR_ID_ALL_SCROLL_BAR			=   230,
CHGCHARCOLOR_ID_GRID_COLOR				=	1000,
//
CHGCHARCOLOR_R_SCROLL_BKGND_SX			=	510,
CHGCHARCOLOR_R_SCROLL_BKGND_SY			=	198,
CHGCHARCOLOR_R_SCROLL_BKGND_XL			=	170,
CHGCHARCOLOR_R_SCROLL_BKGND_YL			=	10,
//
CHGCHARCOLOR_G_SCROLL_BKGND_SX			=	510,
CHGCHARCOLOR_G_SCROLL_BKGND_SY			=	256,
CHGCHARCOLOR_G_SCROLL_BKGND_XL			=	170,
CHGCHARCOLOR_G_SCROLL_BKGND_YL			=	10,
//
CHGCHARCOLOR_B_SCROLL_BKGND_SX			=	510,
CHGCHARCOLOR_B_SCROLL_BKGND_SY			=	316,
CHGCHARCOLOR_B_SCROLL_BKGND_XL			=	170,
CHGCHARCOLOR_B_SCROLL_BKGND_YL			=	10,
//
CHGCHARCOLOR_ALL_SCROLL_BKGND_SX		=	510,
CHGCHARCOLOR_ALL_SCROLL_BKGND_SY		=	372,
CHGCHARCOLOR_ALL_SCROLL_BKGND_XL		=	170,
CHGCHARCOLOR_ALL_SCROLL_BKGND_YL		=	10,
//
CHGCHARCOLOR_COLOR_GRID_SX				=	494,
CHGCHARCOLOR_COLOR_GRID_SY				=	164,
CHGCHARCOLOR_COLOR_GRID_XL				=	20,
CHGCHARCOLOR_COLOR_GRID_YL				=	20,
CHGCHARCOLOR_COLOR_GRID_DX				=	40,
CHGCHARCOLOR_COLOR_GRID_DY				=	37,

CHGCHARCOLOR_COLOR_USER_SX				=	693,

//
MOUSE_EVENT_R_SCROLL					=	1,
MOUSE_EVENT_G_SCROLL					=	2,
MOUSE_EVENT_B_SCROLL					=	3,
MOUSE_EVENT_A_SCROLL					=	4,
} CHGCHARCOLOR_ENUMS;

// STRUCTURES ////////////////////////////////////////////////////////////////////////////////////
typedef struct  tagEULA_DATA
{
    CAKE_FRAME_ANI  *cfa;       //frame ani pointer
    CAKE_FRAME      *cf[32];    //image pointer of each frame.
    //
    SLONG   hilight_id;         //hilight id
    SLONG   active_id;          //active id
    SLONG   start_index;
    //
    SLONG   scroll_y_pos;       //scroll button y position
    SLONG   min_scroll_y;       //minimize scroll y position
    SLONG   max_scroll_y;       //maximize scroll y position
    SLONG   mouse_event;        //mouse event 
    //
    TEXT_LINE_DLINK *text_lines;    //text lines
    SLONG   max_lines;              //max text lines
} EULA_DATA, *LPEULA_DATA;


typedef struct  tagUILOGIN
{
    CAKE_FRAME_ANI  *cfa;       //frame ani pointer
    CAKE_FRAME      *cf[32];    //image pointer of each frame
    //
    SLONG   wheel_frame;        //steering wheel frame
    SLONG   wheel_dir;          //steering wheel direction
    USTR    account[32];        //account string
    USTR    password[32];       //password string
    SLONG   hilight_id;         //hilight id
    SLONG   active_id;          //active id
    SLONG   function_id;        //function id
} UILOGIN, *LPUILOGIN;


typedef struct  tagCREDITS_DATA
{
    CAKE_FRAME_ANI  *cfa;       //frame ani pointer
    CAKE_FRAME      *cf[32];    //image pointer of each frame
    ABMP            *text_abmp; //text abitmap
    //
    SLONG   hilight_id;         //hilight id
    SLONG   active_id;          //active id
    SLONG   text_image_sy;      //credits text image show start y position
} CREDITS_DATA, CREDITS_DATA;


typedef struct  tagSWS_DATA     //select world server data
{
    CAKE_FRAME_ANI  *cfa;       //frame ani pointer
    CAKE_FRAME      *cf[32];    //image pointer of each frame
    //
    SLONG   hilight_id;         //hilight id
    SLONG   active_id;          //active id
    SLONG   start_index;        //start world server info index
    SLONG   select_index;       //selected world server index
    //
    SLONG   scroll_y_pos;       //scroll button y position
    SLONG   min_scroll_y;       //minimize scroll y position
    SLONG   max_scroll_y;       //maximize scroll y position
    SLONG   mouse_event;        //mouse event 
} SWS_DATA, *LPSWS_DATA;


typedef struct  tagSELCHAR_DATA //select character data
{
    CAKE_FRAME_ANI  *cfa;       //frame ani pointer
    CAKE_FRAME      *cf[32];    //image pointer of each frame
    //
    SLONG   hilight_id;         //hilight id
    SLONG   active_id;          //active id
    SLONG   select_index;       //selected character index
    //
	// Jack, add for [12/18/2002]
	SLONG	on_linking;			//是否已經選擇好人物, 正在準備進入遊戲.
} SELCHAR_DATA, *LPSELCHAR_DATA;


typedef struct  tagCREATECHAR_DATA
{
    CAKE_FRAME_ANI  *cfa;       //frame ani pointer
    CAKE_FRAME      *cf[32];    //image pointer of each frame
    //
    SLONG   hilight_id;         //hilight id
    SLONG   active_id;          //active id
    SLONG   select_index;       //select character body index
    //
    CAKE_FRAME_ANI  *ani_cfa;   //ani image pointer
    CAKE_FRAME_ANI  *ani_ptr;   //current ani image frame pointer
    //
    TEXT_LINE_DLINK *text_lines[CREATECHAR_MAX_BODY];   //text line datas
    SLONG   max_lines[CREATECHAR_MAX_BODY];             //max text lines
    SLONG   text_start_y;       //text start y position(of text_abmp)
    ABMP    *text_abmp;         //text abitmap
    //
} CREATECHAR_DATA, *LPCREATECHAR_DATA;


typedef struct  tagSETCHARFACE_DATA
{
    CAKE_FRAME_ANI  *cfa;       //frame ani pointer.
    CAKE_FRAME      *cf[32];    //image pointer of each frame.
    //
    SLONG   hilight_id;         //hilight id
    SLONG   active_id;          //active id
    SLONG   function_id;        //current function id
    //
//    char    mainname[32];       //character's main name
//    char    nickname[32];       //character's nick name
    UI_TEXT *mainname;          // character's main name input
    UI_TEXT *nickname;          // character's nick name input

    SLONG   eye_index;          //character's eye index
    SLONG   mouth_index;        //character's mouth index
    SLONG   strength;           //strength value
    SLONG   facility;           //facility value
    SLONG   wit;                //wit value
    SLONG   stamina;            //stamina value
    SLONG   hp;                 //hp value
    SLONG   mp;                 //mp value
    //
} SETCHARFACE_DATA, *LPSETCHARFACE_DATA;


typedef struct  tagSETCHARLOCATE_DATA
{
    CAKE_FRAME_ANI  *cfa;       //frame ani pointer.
    CAKE_FRAME      *cf[32];    //image pointer of each frame.
    ABMP            *text_abmp; //text abitmap
    //
    SLONG   hilight_id;         //hilight id
    SLONG   active_id;          //active id
    SLONG   select_index;       //locate country index
    SLONG   text_start_y;       //text start y position(of text_abmp)
    //
    TEXT_LINE_DLINK *text_lines[SETCHARLOCATE_MAX_COUNTRY]; //country introduce text datas
    SLONG   max_lines[SETCHARLOCATE_MAX_COUNTRY];           //max text lines
    //
} SETCHARLOCATE_DATA, *LPSETCHARLOCATE_DATA;


typedef	struct tagCHGCHARCOLOR_DATA 
{
	CAKE_FRAME_ANI	*cfa;
	CAKE_FRAME		*cf[64];
	//
	SLONG	hilight_id;
	SLONG	active_id;
	//
	SLONG	is_setting_rgb;		// Is setting rgb now ?
	SLONG	set_part_index;		// Part index which currently scroll set rgb.
	SLONG	suit_index;			// Currently used suit index.
	UCHR	rgb_data[7][3];		// Current RGB colors.
	SLONG	color_index[7];		// 0,1,2 for edit colors, 3 for user colors, -1 for non edit colors.
	//
	SLONG	set_r;
	SLONG	set_g;
	SLONG	set_b;
	SLONG	set_a;
	SLONG	set_a_last;

	SLONG	min_scroll_x;
	SLONG	max_scroll_x;
	SLONG	scroll_r_pos[7];
	SLONG	scroll_g_pos[7];
	SLONG	scroll_b_pos[7];
	SLONG	scroll_a_pos[7];

	SLONG	mouse_event;

} CHGCHARCOLOR_DATA, *LPCHGCHARCOLOR_DATA;

extern  UILOGIN             uilogin;
extern  CREDITS_DATA        credits_data;
extern  SWS_DATA            sws_data;
extern  SELCHAR_DATA        selchar_data;
extern  CREATECHAR_DATA     createchar_data;
extern	CHGCHARCOLOR_DATA	chgcharcolor_data;
extern  SETCHARFACE_DATA    setcharface_data;
extern  SETCHARLOCATE_DATA  setcharlocate_data;

extern	CHAR world_name[64];

// FUNCTIONS /////////////////////////////////////////////////////////////////////////////////////
//ui -------------------------------------------
int     init_ui(void);
void    active_ui(int active);
void    free_ui(void);
void    debug_redraw_mouse_position(void *vbitmap);
//
//ui end user licence agreemend ----------------
int     init_eula(void);
void    active_eula(int active);
void    free_eula(void);
void    refresh_eula(void);
void    redraw_eula(SLONG sx, SLONG sy, void *vbitmap);
SLONG   handle_eula(UINT message, WPARAM wParam, LPARAM lParam);
SLONG   load_eula_text(void);

//ui login -------------------------------------
int     init_uilogin(void);
void    active_uilogin(int active);
void    free_uilogin(void);
void    refresh_uilogin(void);
void    redraw_uilogin(SLONG sx, SLONG sy, void *vbitmap);
SLONG   handle_uilogin(UINT message, WPARAM wParam, LPARAM lParam);

//ui credits -----------------------------------
int     init_credits(void);
void    active_credits(int active);
void    free_credits(void);
void    refresh_credits(void);
void    redraw_credits(SLONG sx, SLONG sy, void *vbitmap);
SLONG   handle_credits(UINT message, WPARAM wParam, LPARAM lParam);

//ui select world server -----------------------
int     init_select_world_server(void);
void    active_select_world_server(int active);
void    free_select_world_server(void);
void    refresh_select_world_server(void);
void    redraw_select_world_server(SLONG sx, SLONG sy, void *vbitmap);
SLONG   handle_select_world_server(UINT message, WPARAM wParam, LPARAM lParam);

//ui select character --------------------------
int     init_select_character(void);
void    active_select_character(int active);
void    free_select_character(void);
void    refresh_select_character(void);
void    redraw_select_character(SLONG sx, SLONG sy, void *vbitmap);
SLONG   handle_select_character(UINT message, WPARAM wParam, LPARAM lParam);

//ui create character --------------------------
int     init_create_character(void);
void    active_create_character(int active);
void    free_create_character(void);
void    refresh_create_character(void);
void    redraw_create_character(SLONG sx, SLONG sy, void *vbitmap);
SLONG   handle_create_character(UINT message, WPARAM wParam, LPARAM lParam);

//ui set character face -------------------------
int     init_set_character_face(void);
void    active_set_character_face(int active);
void    free_set_character_face(void);
void    refresh_set_character_face(void);
void    redraw_set_character_face(SLONG sx, SLONG sy, void *vbitmap);
SLONG   handle_set_character_face(UINT message, WPARAM wParam, LPARAM lParam);

//ui set character locate -----------------------
int     init_set_character_locate(void);
void    active_set_character_locate(int active);
void    free_set_character_locate(void);
void    refresh_set_character_locate(void);
void    redraw_set_character_locate(SLONG sx, SLONG sy, void *vbitmap);
SLONG   handle_set_character_locate(UINT message, WPARAM wParam, LPARAM lParam);

//ui change character color ---------------------
int		init_change_character_color(void);
void	active_change_character_color(int active);
void	free_change_character_color(void);
void	refresh_change_character_color(void);
void	redraw_change_character_color(SLONG sx, SLONG sy, void *vbitmap);
SLONG	handle_change_character_color(UINT message, WPARAM wParam, LPARAM lParam);



#endif//_UI_H_
