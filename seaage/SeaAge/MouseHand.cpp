/*
**	MouseHand.cpp
**	mouse hand functions.
**
**	Jack, 2002/07/16.
*/
#include "mainfun.h"
#include "NetGE_MainFunc.h"
#include "crange.h"
#include "clientmain.h"
#include "errormsg.h"
#include "ui.h"
#include "mousehand.h"
#include "qqmain.h"
#include "Client_Item.h"
#include "UIStore.h"


/******************************************************************************************************************/
/* GLOBALS                                                                                                        */
/******************************************************************************************************************/
UIHAND      mouse_hand;


/******************************************************************************************************************/
/* MOUSE HAND FUNCTIONS                                                                                           */
/******************************************************************************************************************/
int     init_mouse_hand(void)
{
    memset(&mouse_hand, 0x00, sizeof(mouse_hand));
	SetItemNone(&mouse_hand.item);
    return  0;
}


void    free_mouse_hand(void)
{
}


void    set_mouse_hand_position(SLONG x, SLONG y)
{
    mouse_hand.x = x;
    mouse_hand.y = y;
}


void	set_mouse_hand_point_info(SLONG kind, SLONG no, SLONG x, SLONG y)
{
	mouse_hand.point_kind = kind;
	mouse_hand.point_no = no;
	mouse_hand.point_x = x;
	mouse_hand.point_y = y;
}


void    set_mouse_hand_point_position(SLONG x, SLONG y)
{
	mouse_hand.point_x = x;
	mouse_hand.point_y = y;
}


void    set_mouse_hand_point_kind_no(SLONG kind, SLONG no)
{
    mouse_hand.point_kind = kind;
    mouse_hand.point_no = no;
}


void    redraw_mouse_point_info(void *vbitmap)
{
	enum	
	{	INFO_WIN_GAP_X          =   16,
    INFO_WIN_GAP_Y				=   16,
	INFO_FONT_WIDTH				=	16,
	INFO_FONT_HEIGHT			=	16,
	};
    BMP *bitmap = (BMP *)vbitmap;
	SLONG	type, id;

	type = mouse_hand.point_kind;
	id = mouse_hand.point_no;
    switch(type)
    {
    case RT_MAP:
        break;
    case RT_NPC:
        redraw_npc_mouse_point_info(id, bitmap);
        break;
    case UIMAP_EVENT:
        redraw_map_ui_mouse_point_info(id, bitmap);
        break;
    case UIMAPSTATE_EVENT:
        redraw_uimapstate_mouse_point_info(id, bitmap);
        break;
    case UIMAPITEM_EVENT:
        redraw_uimapitem_mouse_point_info(id, bitmap);
        break;
    case UIMAPSKILL_EVENT:
        redraw_uimapskill_mouse_point_info(id, bitmap);
        break;
    case UIMAPTASK_EVENT:
        redraw_uimaptask_mouse_point_info(id, bitmap);
        break;
    case UIMAPSHIP_EVENT:
        redraw_uimapship_mouse_point_info(id, bitmap);
        break;
	case QQMAIN_EVENT:
		redraw_uiqq_mouse_point_info(type, id, bitmap);
		break;
	case ITEMSTORE_EVENT:
		redraw_item_store_mouse_point_info(id, vbitmap);
		break;
	case BANKSTORE_EVENT:
		redraw_bank_store_mouse_point_info(id, vbitmap);
		break;
	case SAVEBOXSTORE_EVENT:
		redraw_savebox_store_mouse_point_info(id, vbitmap);
		break;
	case STRONGBOXSTORE_EVENT:
		redraw_strongbox_store_mouse_point_info(id, vbitmap);
		break;
    }
}


void    redraw_event_info_bar(SLONG type, SLONG id, USTR *name, USTR *info, void *vbitmap)
{
    INFO_BAR    info_bar;
    SLONG   sx, sy, xl, yl;

    clear_info_bar(&info_bar);
    add_info_bar_string(&info_bar, name, info);
    game_range.get_range(type, id, &sx, &sy, &xl, &yl);
    set_info_bar_range(&info_bar, sx, sy, xl, yl);
    set_info_bar_gap(&info_bar, 8, 8 );
    redraw_info_bar(&info_bar, vbitmap);
}


void	update_mouse_hand_item(void)
{
	SLONG	now_base, new_base;
	TPOS_ITEM	onmouse_item;

	if(g_lPlayerIndex < 0)
	{
        set_mouse_cursor(MOUSE_IMAGE_ARROW);
		return;
	}

	LOCK_CHARACTER(0);
	GetCharacterOnMouseItem(g_lPlayerIndex, &onmouse_item);
	UNLOCK_CHARACTER(0);

	new_base = GetItemBaseID(&onmouse_item);
	now_base = GetItemBaseID(&mouse_hand.item);
	if(new_base == now_base)
		return;

	if(IsItemNone(&onmouse_item))
	{
        set_mouse_cursor(MOUSE_IMAGE_ARROW);
	}
	else
	{
        CAKE_FRAME_ANI  *cfa;
        SLONG   icon_index;
        SLONG   hrooms, vrooms, item_xl, item_yl;

        icon_index = GetItemIconIndex(&onmouse_item);
        cfa = get_item_icon_cfa(icon_index);
        get_item_icon_size(icon_index, &hrooms, &vrooms, &item_xl, &item_yl);
        make_mouse_image_cursor(5, cfa, 1);
        set_mouse_spot(5, item_xl/2, item_yl/2);
        set_mouse_cursor(5);
	}
	mouse_hand.item = onmouse_item;
}
