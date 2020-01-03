/*
**	MouseHand.h
**	mouse hand functions.
**
**	Jack, 2002/07/16.
*/
#ifndef _MOUSEHAND_H_
#define _MOUSEHAND_H_
#include "NetGE_Item.h"


// DEFINES /////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//mouse images types defines(滑鼠指標) ---------------------------------
#define MOUSE_IMAGE_ARROW               0   //箭頭


//hand doing kinds(滑鼠正在控制的類型) ---------------------------------
#define HAND_DOING_NOTHING				0   //沒有任何需要紀錄的類型
#define HAND_DOING_LEFT_ITEM			1   //點擊了地圖上的物品
#define	HAND_DOING_LEFT_MAGIC			2	//在地圖上施放法術
#define HAND_DOING_RIGHT_ITEM			3   //點擊了地圖上的物品
#define	HAND_DOING_RIGHT_MAGIC			4   //在地圖上施放法術
//Mark by lijun 2003-05-16
/*
#define HAND_DOING_NOTHING				0   //沒有任何需要紀錄的類型
#define HAND_DOING_CTRL_ITEM			1   //點擊了地圖上的物品
#define HAND_DOING_CTRL_MAP			    2   //在地圖上行走
#define	HAND_DOING_CTRL_NPC			    3	//點擊了地圖上的NPC
#define	HAND_DOING_CTRL_MAGIC			4	//在地圖上施放法術
*/

//hand point kinds(滑鼠指向的類型) --------------------------------------
#define HAND_POINT_NOTHING              0   //空指向
#define HAND_POINT_MAP_ITEM             1   //指向地圖上的道具
#define HAND_POINT_MAP_NPC              2   //指向地圖上的 NPC
#define HAND_POINT_BAG_ITEM             3   //指向背包中的物品
#define HAND_POINT_SASH_ITEM            4   //指向腰包中的物品
#define HAND_POINT_WEAPON_ITEM          5   //指向武器
#define HAND_POINT_ARMOR_ITEM           6   //指向防護
#define HAND_POINT_ORNAMENT_ITEM        7   //指向飾物


// STRUCTURES //////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct  tagUIEVENT
{
    SLONG   type;   //事件的類型
    SLONG   id;     //事件的ID
    SLONG   x;      //event x
    SLONG   y;      //event y    
	ULONG	time;	//event time
    SLONG   doing;  //	
} UIEVENT, *LPUIEVENT;


// user mouse cursor as a hand
typedef struct  tagUIHAND
{
    TPOS_ITEM	item;
    //
    SLONG   point_doing;    //當前..鼠標按鍵所帶有的doing
    //
    SLONG   x,y;            //mouse 的座標x,y;
    ULONG   time;           //紀錄時間
    //
    SLONG   point_kind;      // 類型
    SLONG   point_no;       //.紀錄編號..如npc編號...
    SLONG   point_x;        //.紀錄座標..如npc座標...
    SLONG   point_y;
} UIHAND, *LPUIHAND;

/* Mark by lijun 2003-05-16
// user interface event
typedef struct  tagUIEVENT
{
    SLONG   flag;   //event flag
    SLONG   type;   //event type
    SLONG   id;     //event id
    SLONG   para;   //event parameter
    SLONG   doing;  //event doing aim
	ULONG	time;	//event time
    SLONG   x;      //event x
    SLONG   y;      //event y
} UIEVENT, *LPUIEVENT;


// user mouse cursor as a hand
typedef struct  tagUIHAND
{
    TPOS_ITEM	item;
    //
    UIEVENT left_down;
    UIEVENT left_up;
    UIEVENT left_drag;
    //
    UIEVENT right_down;
    UIEVENT right_up;
    UIEVENT right_drag;
    //
    SLONG   x;
    SLONG   y;
    //
    SLONG   point_kind;
    SLONG   point_no;
    SLONG   point_x;
    SLONG   point_y;
} UIHAND, *LPUIHAND;
*/

// GLOBALS /////////////////////////////////////////////////////////////////////////////////////////////////////////
extern  UIHAND      mouse_hand;



// FUNCTIONS PROTOTYPE /////////////////////////////////////////////////////////////////////////////////////////////
int     init_mouse_hand(void);
void    free_mouse_hand(void);
//
void    set_mouse_hand_position(SLONG x, SLONG y);
void	set_mouse_hand_point_info(SLONG kind, SLONG no, SLONG x, SLONG y);
void    set_mouse_hand_point_kind_no(SLONG kind, SLONG no);
void    set_mouse_hand_point_position(SLONG x, SLONG y);
void    redraw_mouse_point_info(void *vbitmap);
void    redraw_event_info_bar(SLONG type, SLONG id, USTR *name, USTR *info, void *vbitmap);
void	update_mouse_hand_item(void);
//



#endif//_MOUSEHAND_H_
