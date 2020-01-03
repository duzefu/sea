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
//mouse images types defines(�ƹ�����) ---------------------------------
#define MOUSE_IMAGE_ARROW               0   //�b�Y


//hand doing kinds(�ƹ����b�������) ---------------------------------
#define HAND_DOING_NOTHING				0   //�S������ݭn����������
#define HAND_DOING_LEFT_ITEM			1   //�I���F�a�ϤW�����~
#define	HAND_DOING_LEFT_MAGIC			2	//�b�a�ϤW�I��k�N
#define HAND_DOING_RIGHT_ITEM			3   //�I���F�a�ϤW�����~
#define	HAND_DOING_RIGHT_MAGIC			4   //�b�a�ϤW�I��k�N
//Mark by lijun 2003-05-16
/*
#define HAND_DOING_NOTHING				0   //�S������ݭn����������
#define HAND_DOING_CTRL_ITEM			1   //�I���F�a�ϤW�����~
#define HAND_DOING_CTRL_MAP			    2   //�b�a�ϤW�樫
#define	HAND_DOING_CTRL_NPC			    3	//�I���F�a�ϤW��NPC
#define	HAND_DOING_CTRL_MAGIC			4	//�b�a�ϤW�I��k�N
*/

//hand point kinds(�ƹ����V������) --------------------------------------
#define HAND_POINT_NOTHING              0   //�ū��V
#define HAND_POINT_MAP_ITEM             1   //���V�a�ϤW���D��
#define HAND_POINT_MAP_NPC              2   //���V�a�ϤW�� NPC
#define HAND_POINT_BAG_ITEM             3   //���V�I�]�������~
#define HAND_POINT_SASH_ITEM            4   //���V�y�]�������~
#define HAND_POINT_WEAPON_ITEM          5   //���V�Z��
#define HAND_POINT_ARMOR_ITEM           6   //���V���@
#define HAND_POINT_ORNAMENT_ITEM        7   //���V����


// STRUCTURES //////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct  tagUIEVENT
{
    SLONG   type;   //�ƥ�����
    SLONG   id;     //�ƥ�ID
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
    SLONG   point_doing;    //��e..���Ы���ұa����doing
    //
    SLONG   x,y;            //mouse ���y��x,y;
    ULONG   time;           //�����ɶ�
    //
    SLONG   point_kind;      // ����
    SLONG   point_no;       //.�����s��..�pnpc�s��...
    SLONG   point_x;        //.�����y��..�pnpc�y��...
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
