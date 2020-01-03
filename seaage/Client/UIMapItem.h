/*
**	UIMapItem.h
**	UI of map item menu.
**
**	Jack, 2002/07/02.
**
**  Zhang Zhaohui 2003.5.31
**
*/
#ifndef _UIMAPITEM_H_
#define _UIMAPITEM_H_


// DEFINES /////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef enum    UI_MAPITEM_ENUMS
{   UIMAPITEM_FRAME_BKGND           =   0,
UIMAPITEM_FRAME_TITLE               =   1,
UIMAPITEM_FRAME_CLOSE               =   2,
UIMAPITEM_FRAME_DEC_STRENGTH        =   4,
UIMAPITEM_FRAME_ADD_STRENGTH        =   6,
UIMAPITEM_FRAME_DEC_INSTINCT        =   8,
UIMAPITEM_FRAME_ADD_INSTINCT        =   10,
UIMAPITEM_FRAME_DEC_WIT             =   12,
UIMAPITEM_FRAME_ADD_WIT             =   14,
UIMAPITEM_FRAME_DEC_LUCK            =   16,
UIMAPITEM_FRAME_ADD_LUCK            =   18,
UIMAPITEM_FRAME_BOX                 =   20,
//
UIMAPITEM_EVENT                     =   3001,
UIMAPITEM_ID_BKGND                  =   0,
UIMAPITEM_ID_CLOSE                  =   10,
UIMAPITEM_ID_DEC_STRENGTH           =   20,
UIMAPITEM_ID_ADD_STRENGTH           =   30,
UIMAPITEM_ID_DEC_INSTINCT           =   40,
UIMAPITEM_ID_ADD_INSTINCT           =   50,
UIMAPITEM_ID_DEC_WIT                =   60,
UIMAPITEM_ID_ADD_WIT                =   70,
UIMAPITEM_ID_DEC_LUCK               =   80,
UIMAPITEM_ID_ADD_LUCK               =   90,
UIMAPITEM_ID_HEAD_ITEM              =   100,
UIMAPITEM_ID_NECK_ITEM              =   101,
UIMAPITEM_ID_BODY_ITEM              =   102,
UIMAPITEM_ID_WEAPON_ITEM            =   103,
UIMAPITEM_ID_WAIST_ITEM             =   104,
UIMAPITEM_ID_WRIST_ITEM				=   105,
UIMAPITEM_ID_GLOVE_ITEM				=   106,
UIMAPITEM_ID_FEET_ITEM              =   107,
UIMAPITEM_ID_DECK_0_ITEM            =   120,
UIMAPITEM_ID_DECK_1_ITEM            =   121,
UIMAPITEM_ID_DECK_2_ITEM            =   122,
UIMAPITEM_ID_TREASURE_ITEM          =   123,
UIMAPITEM_ID_BAG_0_ITEM             =   200,
//
UIMAPITEM_LEVEL_SX                  =   106,
UIMAPITEM_LEVEL_SY                  =   146,
UIMAPITEM_LEVEL_XL                  =   156 - 106,
UIMAPITEM_LEVEL_YL                  =   160 - 146,

UIMAPITEM_HP_SX                     =   106,
UIMAPITEM_HP_SY                     =   164,
UIMAPITEM_HP_XL                     =   156 - 106,
UIMAPITEM_HP_YL                     =   176 - 164,

UIMAPITEM_MP_SX                     =   106,
UIMAPITEM_MP_SY                     =   180,
UIMAPITEM_MP_XL                     =   156 - 106,
UIMAPITEM_MP_YL                     =   192 - 180,

UIMAPITEM_STRENGTH_SX               =   118,
UIMAPITEM_STRENGTH_SY               =   196,
UIMAPITEM_STRENGTH_XL               =   154 - 118,
UIMAPITEM_STRENGTH_YL               =   210 - 196,

UIMAPITEM_INSTINCT_SX               =   118,
UIMAPITEM_INSTINCT_SY               =   218,
UIMAPITEM_INSTINCT_XL               =   154 - 118,
UIMAPITEM_INSTINCT_YL               =   232 - 218,

UIMAPITEM_WIT_SX                    =   118,
UIMAPITEM_WIT_SY                    =   238,
UIMAPITEM_WIT_XL                    =   154 - 118,
UIMAPITEM_WIT_YL                    =   252 - 238,

UIMAPITEM_LUCK_SX                   =   118,
UIMAPITEM_LUCK_SY                   =   254,
UIMAPITEM_LUCK_XL                   =   154 - 118,
UIMAPITEM_LUCK_YL                   =   268 - 254,

UIMAPITEM_HURT_SX                   =   116,
UIMAPITEM_HURT_SY                   =   285,
UIMAPITEM_HURT_XL                   =   156 - 116,
UIMAPITEM_HURT_YL                   =   298 - 285,

UIMAPITEM_DP_SX                     =   116,
UIMAPITEM_DP_SY                     =   305,
UIMAPITEM_DP_XL                     =   156 - 116,
UIMAPITEM_DP_YL                     =   320 - 305,

UIMAPITEM_RESIST_SX                 =   116,
UIMAPITEM_RESIST_SY                 =   324,
UIMAPITEM_RESIST_XL                 =   156 - 116,
UIMAPITEM_RESIST_YL                 =   340 - 324,

UIMAPITEM_UPGRADE_POINT_SX          =   128,
UIMAPITEM_UPGRADE_POINT_SY          =   349,
UIMAPITEM_UPGRADE_POINT_XL          =   159 - 128,
UIMAPITEM_UPGRADE_POINT_YL          =   363 - 349,
//
UIMAPITEM_HEAD_ITEM_SX              =   223,
UIMAPITEM_HEAD_ITEM_SY              =   150,
UIMAPITEM_NECK_ITEM_SX              =   235,
UIMAPITEM_NECK_ITEM_SY              =   193,
UIMAPITEM_BODY_ITEM_SX              =   226,
UIMAPITEM_BODY_ITEM_SY              =   234,
UIMAPITEM_FEET_ITEM_SX              =   223,
UIMAPITEM_FEET_ITEM_SY              =   329,
UIMAPITEM_WEAPON_ITEM_SX            =   179,
UIMAPITEM_WEAPON_ITEM_SY            =   224,
UIMAPITEM_WRIST_ITEM_SX             =	179,
UIMAPITEM_WRIST_ITEM_SY             =	189,
UIMAPITEM_WAIST_ITEM_SX             =	293,
UIMAPITEM_WAIST_ITEM_SY             =	269,
UIMAPITEM_DECK_0_ITEM_SX            =	295,
UIMAPITEM_DECK_0_ITEM_SY            =	157,
UIMAPITEM_DECK_1_ITEM_SX            =	295,
UIMAPITEM_DECK_1_ITEM_SY            =	192,
UIMAPITEM_DECK_2_ITEM_SX            =	166,
UIMAPITEM_DECK_2_ITEM_SY            =	290,
UIMAPITEM_GLOVE_ITEM_SX				=	166,
UIMAPITEM_GLOVE_ITEM_SY				=	325,
UIMAPITEM_TREASURE_ITEM_SX          =   290,
UIMAPITEM_TREASURE_ITEM_SY          =   318,

//
UIMAPITEM_BAG_0_SX                  =   31,
UIMAPITEM_BAG_0_SY                  =   376,
UIMAPITEM_BAG_DX                    =   34,
UIMAPITEM_BAG_DY                    =   34,
UIMAPITEM_BAG_X_COUNT               =   9,
UIMAPITEM_BAG_Y_COUNT               =   3,
UIMAPITEM_BAG_COUNTS                =   27,
} UI_MAPITEM_ENUMS;




// STRUCTURES //////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct tagUI_MAPITEM_DATA 
{
    CAKE_FRAME_ANI  *cfa;       //frame ani pointer
    CAKE_FRAME      *cf[32];    //image pointer of each frame.
    //
    SLONG   hilight_id;         //hilight id
    SLONG   active_id;          //active id
    //
    SLONG   is_opened;  //物品介面是否打開
} UI_MAPITEM_DATA, *LPUI_MAPITEM_DATA;


// GLOBALS /////////////////////////////////////////////////////////////////////////////////////////////////////////
extern  UI_MAPITEM_DATA ui_mapitem_data;




// FUNCTIONS ///////////////////////////////////////////////////////////////////////////////////////////////////////
int     init_ui_mapitem(void);
void    active_ui_mapitem(int active);
void    free_ui_mapitem(void);
void    redraw_ui_mapitem(SLONG sx, SLONG sy, void *vbitmap);
void    refresh_ui_mapitem(void);
SLONG   handle_ui_mapitem(UINT message, WPARAM wParam, LPARAM lParam);
void    redraw_uimapitem_mouse_point_info(SLONG id, BMP *bitmap);
//
SLONG   is_mapitem_menu_opened(void);
void    open_mapitem_menu(SLONG flag);


#endif//_UIMAPITEM_H_
