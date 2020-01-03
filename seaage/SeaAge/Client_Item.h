/*
**	Client_Item.h 
**	Client item functions header.
**
**	Jack, 2003.1.2
*/
#pragma	once
#include "NetGE_Item.h"


// DEFINES //////////////////////////////////////////////////////////////////////////////////////////////////
#define MAX_ITEM_ICONS						1024    //���~�ϼмƶq
#define ITEM_ICON_WIDTH						30      //��쪫�~�Ŷ������I�e��
#define ITEM_ICON_HEIGHT					30      //��쪫�~�Ŷ������I����
//
#define ITEM_STAY_WIDTH						64      //�a�ϤW���~�v���e��
#define ITEM_STAY_HEIGHT					40      //�a�ϤW���~�v������
#define ITEM_STAY_MASK_WIDTH				ITEM_STAY_WIDTH         //�ƹ�����ɪ��e��
#define ITEM_STAY_MASK_HEIGHT				(ITEM_STAY_HEIGHT / 2)  //�ƹ�����ɪ�����
//
//
//
#define GAME_ITEM_STATE_MASK                0x0000000f  //�_�c��e���A��MASK
#define GAME_ITEM_STATE_LOCK                0x00000000  //���۪��_�c
#define GAME_ITEM_STATE_UNLOCK              0x00000001  //�}�۪��_�c
#define GAME_ITEM_STATE_OPEN                0x00000002  //�}�_�c
//
#define GAME_ITEM_ACTION_MASK               0x0000ff00  //�_�c�ʧ@��MASK
#define GAME_ITEM_ACTION_DISAPPEAR          0x00000100  //���}�����


typedef	enum	ITEM_INFO_TYPE
{
	ITEM_INFO_NORMAL		=	0,	//�@�����
	ITEM_INFO_BUY			=	1,	//�ө��R���~
	ITEM_INFO_SELL			=	2,	//�ө��檫�~
} ITEM_INFO_TYPE;

// GLOBALS //////////////////////////////////////////////////////////////////////////////////////////////////
//

// FUNCTIONS ////////////////////////////////////////////////////////////////////////////////////////////////
//
extern	int     init_item(void);
extern	void    active_item(int active);
extern	void    free_item(void);
//
extern	SLONG   init_item_icon_image(void);
extern	void    free_item_icon_image(void);
extern	void    get_item_icon_size(SLONG index, SLONG *hrooms, SLONG *vrooms, SLONG *xl, SLONG *yl);
extern	CAKE_FRAME_ANI  *get_item_icon_cfa(SLONG index);
extern	void    redraw_item_icon_image(SLONG cx, SLONG cy, SLONG index, BMP *bitmap);
extern	void    redraw_land_box_lock_image(SLONG cx, SLONG cy, SLONG frame, BMP *bitmap, SLONG selected);
extern	void    redraw_land_box_unlock_image(SLONG cx, SLONG cy, SLONG frame, BMP *bitmap, SLONG selected);
extern	void    redraw_land_box_open_image(SLONG cx, SLONG cy, SLONG frame, BMP *bitmap, SLONG selected);
//
extern	void	redraw_icon_item_information(SLONG item_sx, SLONG item_sy, SLONG show_for, TPOS_ITEM *item, BMP *bitmap);
extern	void    redraw_map_item( SLONG map_no, SLONG map_sx, SLONG map_sy, BMP *bitmap);
extern	void    refresh_map_item(SLONG map_no);
extern	void    open_and_disappear_game_item(SLONG index, SLONG open_npc);



