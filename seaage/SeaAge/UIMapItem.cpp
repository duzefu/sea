/*
**	UIMapItem.cpp
**	UI of map item menu.
**
**	Jack, 2002/07/02.
**
**  Modified by Zhang Zhaohui 2003.5.31
*/
#include "MainFun.h"
#include "Map.h"
#include "CRange.h"
#include "MouseHand.h"
#include "UIMap.h"
#include "UIMapItem.h"
#include "ClientMain.h"
#include "ErrorMsg.h"
#include "CmdEvent.h"
//
#include "NetGE_MainFunc.h"
#include "Client_Item.h"



UI_MAPITEM_DATA ui_mapitem_data;


/******************************************************************************************************************/
/* UI MAP ITEM FUNCTIONS                                                                                          */
/******************************************************************************************************************/
int     init_ui_mapitem(void)
{
    USTR    filename[_MAX_FNAME];
    SLONG   result, i, frames;
    CAKE_FRAME_ANI  *cfa;
    UI_MAPITEM_DATA *data = &ui_mapitem_data;

    data->cfa = NULL;
    for(i=0; i<32; i++)
    {
        data->cf[i] = NULL;
    }

    set_data_file(packed_menu_file);
    strcpy((char *)filename, "menu\\uiitem.cak");
    result = load_cake_frame_ani_from_file((USTR*)filename, &data->cfa);
    if(TTN_OK != result)
        return  -1;
    frames = count_cake_frames(data->cfa);
    for(i=0; i<frames; i++)
    {
        cfa = get_specify_cake_frame_ani(data->cfa, i);
        data->cf[i] = cfa->cake_frame;
    }

    data->hilight_id = 0;
    data->active_id = 0;
    data->is_opened = FALSE;
    //
    return  0;
}


void    active_ui_mapitem(int active)
{
}


void    free_ui_mapitem(void)
{
    UI_MAPITEM_DATA *data = &ui_mapitem_data;    
    SLONG   i;

    if(data->cfa)
    {
        destroy_cake_frame_ani(&data->cfa);
        for(i=0; i<32; i++)
        {
            data->cf[i] = NULL;
        }
    }
    return;
}


void    redraw_ui_mapitem(SLONG sx, SLONG sy, void *vbitmap)
{
    UI_MAPITEM_DATA *data = &ui_mapitem_data;
    BMP *bitmap = (BMP*)vbitmap;
    CAKE_FRAME  *cf;
    SLONG   frame, x, y, id, event, cx, cy, xl, yl;
    USTR    info[80];
    SLONG   ix, iy, idx, icon_index;
	TPOS_ITEM	item;

    event = UIMAPITEM_EVENT;

    //(1) background -------------------------------------------
    frame = UIMAPITEM_FRAME_BKGND;
    id = UIMAPITEM_ID_BKGND;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

    //(2) close button -----------------------------------------
    frame = UIMAPITEM_FRAME_CLOSE;
    id = UIMAPITEM_ID_CLOSE;
    if(data->active_id == id)
        frame += 1;
    else if(data->hilight_id == id)
        frame += 1;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

    //(3) dec strength ------------------------------------------
    frame = UIMAPITEM_FRAME_DEC_STRENGTH;
    id = UIMAPITEM_ID_DEC_STRENGTH;
    if(data->active_id == id)
        frame += 1;
    else if(data->hilight_id == id)
        frame += 1;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

    //(4) add strength ------------------------------------------
    frame = UIMAPITEM_FRAME_ADD_STRENGTH;
    id = UIMAPITEM_ID_ADD_STRENGTH;
    if(data->active_id == id)
        frame += 1;
    else if(data->hilight_id == id)
        frame += 1;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

    //(5) dec instinct ------------------------------------------
    frame = UIMAPITEM_FRAME_DEC_INSTINCT;
    id = UIMAPITEM_ID_DEC_INSTINCT;
    if(data->active_id == id)
        frame += 1;
    else if(data->hilight_id == id)
        frame += 1;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

    //(6) add instinct ------------------------------------------
    frame = UIMAPITEM_FRAME_ADD_INSTINCT;
    id = UIMAPITEM_ID_ADD_INSTINCT;
    if(data->active_id == id)
        frame += 1;
    else if(data->hilight_id == id)
        frame += 1;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

    //(7) dec wit -----------------------------------------------
    frame = UIMAPITEM_FRAME_DEC_WIT;
    id = UIMAPITEM_ID_DEC_WIT;
    if(data->active_id == id)
        frame += 1;
    else if(data->hilight_id == id)
        frame += 1;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

    //(8) add wit -----------------------------------------------
    frame = UIMAPITEM_FRAME_ADD_WIT;
    id = UIMAPITEM_ID_ADD_WIT;
    if(data->active_id == id)
        frame += 1;
    else if(data->hilight_id == id)
        frame += 1;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

    //(9) dec luck -----------------------------------------------
    frame = UIMAPITEM_FRAME_DEC_LUCK;
    id = UIMAPITEM_ID_DEC_LUCK;
    if(data->active_id == id)
        frame += 1;
    else if(data->hilight_id == id)
        frame += 1;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

    //(10) add luck ----------------------------------------------
    frame = UIMAPITEM_FRAME_ADD_LUCK;
    id = UIMAPITEM_ID_ADD_LUCK;
    if(data->active_id == id)
        frame += 1;
    else if(data->hilight_id == id)
        frame += 1;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

    //(11) player information -----------------------------------
    set_word_color(0, SYSTEM_BLUE);
    //level
    sprintf((char *)info, "%d", 1 + GetCharacterLevel(g_lPlayerIndex));
    x = sx + UIMAPITEM_LEVEL_SX;
    y = sy + UIMAPITEM_LEVEL_SY;
    print12(x, y, (USTR*)info, PEST_PUT, bitmap);

    //hp
    sprintf((char *)info, "%d/%d", GetCharacterHp(g_lPlayerIndex), GetCharacterMaxHp(g_lPlayerIndex));
    x = sx + UIMAPITEM_HP_SX;
    y = sy + UIMAPITEM_HP_SY;
    print12(x, y, (USTR*)info, PEST_PUT, bitmap);

    //mp
    sprintf((char *)info, "%d/%d", GetCharacterMp(g_lPlayerIndex), GetCharacterMaxMp(g_lPlayerIndex));
    x = sx + UIMAPITEM_MP_SX;
    y = sy + UIMAPITEM_MP_SY;
    print12(x, y, (USTR*)info, PEST_PUT, bitmap);

    //strength
    sprintf((char *)info, "%d", GetCharacterFinalStr(g_lPlayerIndex));
    x = sx + UIMAPITEM_STRENGTH_SX;
    y = sy + UIMAPITEM_STRENGTH_SY;
    print12(x, y, (USTR*)info, PEST_PUT, bitmap);

    //instinct
    sprintf((char *)info, "%d", GetCharacterFinalIns(g_lPlayerIndex));
    x = sx + UIMAPITEM_INSTINCT_SX;
    y = sy + UIMAPITEM_INSTINCT_SY;
    print12(x, y, (USTR*)info, PEST_PUT, bitmap);

    //wit
    sprintf((char *)info, "%d", GetCharacterFinalWit(g_lPlayerIndex));
    x = sx + UIMAPITEM_WIT_SX;
    y = sy + UIMAPITEM_WIT_SY;
    print12(x, y, (USTR*)info, PEST_PUT, bitmap);

    //luck
    sprintf((char *)info, "%d", GetCharacterFinalLucky(g_lPlayerIndex));
    x = sx + UIMAPITEM_LUCK_SX;
    y = sy + UIMAPITEM_LUCK_SY;
    print12(x, y, (USTR*)info, PEST_PUT, bitmap);

    //ahurt
    sprintf((char *)info, "%d", GetCharacterFinalAtt(g_lPlayerIndex));
    x = sx + UIMAPITEM_HURT_SX;
    y = sy + UIMAPITEM_HURT_SY;
    print12(x, y, (USTR*)info, PEST_PUT, bitmap);

    //dp
    sprintf((char *)info, "%d", GetCharacterFinalDefence(g_lPlayerIndex));
    x = sx + UIMAPITEM_DP_SX;
    y = sy + UIMAPITEM_DP_SY;
    print12(x, y, (USTR*)info, PEST_PUT, bitmap);

    //mresist
    sprintf((char *)info, "%d", GetCharacterSkillDefence(g_lPlayerIndex));
    x = sx + UIMAPITEM_RESIST_SX;
    y = sy + UIMAPITEM_RESIST_SY;
    print12(x, y, (USTR*)info, PEST_PUT, bitmap);

    //upgrade point
    sprintf((char *)info, "%d", GetCharacterPropertyPoint(g_lPlayerIndex));
    x = sx + UIMAPITEM_UPGRADE_POINT_SX;
    y = sy + UIMAPITEM_UPGRADE_POINT_SY;
    print12(x, y, (USTR*)info, PEST_PUT, bitmap);

    set_word_color(0, SYSTEM_WHITE);

    //(12) player head item -------------------------------------
    id = UIMAPITEM_ID_HEAD_ITEM;
	GetCharacterEquipHead(g_lPlayerIndex, &item);
    x = sx + UIMAPITEM_HEAD_ITEM_SX;
    y = sy + UIMAPITEM_HEAD_ITEM_SY;
    xl = ITEM_ICON_WIDTH;
    yl = ITEM_ICON_HEIGHT;
    game_range.add(x, y, xl, yl, event, id);
    cx = x + xl / 2;
    cy = y + yl / 2;
    if(!IsItemNone(&item))
    {
        icon_index = GetItemIconIndex(&item);
        redraw_item_icon_image(cx, cy, icon_index, bitmap);
    }

    //(13) player neck item -------------------------------------
    id = UIMAPITEM_ID_NECK_ITEM;
	GetCharacterEquipNeck(g_lPlayerIndex, &item);
    x = sx + UIMAPITEM_NECK_ITEM_SX;
    y = sy + UIMAPITEM_NECK_ITEM_SY;
    xl = ITEM_ICON_WIDTH;
    yl = ITEM_ICON_HEIGHT;
    game_range.add(x, y, xl, yl, event, id);
    cx = x + xl / 2;
    cy = y + yl / 2;
    if(! IsItemNone(&item))
    {
        icon_index = GetItemIconIndex(&item);
        redraw_item_icon_image(cx, cy, icon_index, bitmap);
    }

    //(14) player body item -------------------------------------
    id = UIMAPITEM_ID_BODY_ITEM;
	GetCharacterEquipBody(g_lPlayerIndex, &item);
    x = sx + UIMAPITEM_BODY_ITEM_SX;
    y = sy + UIMAPITEM_BODY_ITEM_SY;
    xl = ITEM_ICON_WIDTH;
    yl = ITEM_ICON_HEIGHT;
    game_range.add(x, y, xl, yl, event, id);
    cx = x + xl / 2;
    cy = y + yl / 2;
    if(! IsItemNone(&item))
    {
        icon_index = GetItemIconIndex(&item);
        redraw_item_icon_image(cx, cy, icon_index, bitmap);
    }

    //(15) player hands item -------------------------------------
    id = UIMAPITEM_ID_WEAPON_ITEM;
	GetCharacterEquipWeapon(g_lPlayerIndex, &item);
    x = sx + UIMAPITEM_WEAPON_ITEM_SX;
    y = sy + UIMAPITEM_WEAPON_ITEM_SY;
    xl = ITEM_ICON_WIDTH;
    yl = ITEM_ICON_HEIGHT;
    game_range.add(x, y, xl, yl, event, id);
    cx = x + xl / 2;
    cy = y + yl / 2;
    if(! IsItemNone(&item))
    {
        icon_index = GetItemIconIndex(&item);
        redraw_item_icon_image(cx, cy, icon_index, bitmap);
    }

    //(16) player waist item -------------------------------------
    id = UIMAPITEM_ID_WAIST_ITEM;
	GetCharacterEquipWaist(g_lPlayerIndex, &item);
    x = sx + UIMAPITEM_WAIST_ITEM_SX;
    y = sy + UIMAPITEM_WAIST_ITEM_SY;
    xl = ITEM_ICON_WIDTH;
    yl = ITEM_ICON_HEIGHT;
    game_range.add(x, y, xl, yl, event, id);
    cx = x + xl / 2;
    cy = y + yl / 2;
    if(! IsItemNone(&item))
    {
        icon_index = GetItemIconIndex(&item);
        redraw_item_icon_image(cx, cy, icon_index, bitmap);
    }

    //(17) player lwrist item -------------------------------------
    id = UIMAPITEM_ID_WRIST_ITEM;
	GetCharacterEquipWrist(g_lPlayerIndex, &item);
    x = sx + UIMAPITEM_WRIST_ITEM_SX;
    y = sy + UIMAPITEM_WRIST_ITEM_SY;
    xl = ITEM_ICON_WIDTH;
    yl = ITEM_ICON_HEIGHT;
    game_range.add(x, y, xl, yl, event, id);
    cx = x + xl / 2;
    cy = y + yl / 2;
    if(! IsItemNone(&item))
    {
        icon_index = GetItemIconIndex(&item);
        redraw_item_icon_image(cx, cy, icon_index, bitmap);
    }

    //(18) player glove item -------------------------------------
    id = UIMAPITEM_ID_GLOVE_ITEM;
	GetCharacterEquipGlove(g_lPlayerIndex, &item);
    x = sx + UIMAPITEM_GLOVE_ITEM_SX;
    y = sy + UIMAPITEM_GLOVE_ITEM_SY;
    xl = ITEM_ICON_WIDTH;
    yl = ITEM_ICON_HEIGHT;
    game_range.add(x, y, xl, yl, event, id);
    cx = x + xl / 2;
    cy = y + yl / 2;
    if(! IsItemNone(&item))
    {
        icon_index = GetItemIconIndex(&item);
        redraw_item_icon_image(cx, cy, icon_index, bitmap);
    }

    //(19) player feet item -------------------------------------
    id = UIMAPITEM_ID_FEET_ITEM;
	GetCharacterEquipFeet(g_lPlayerIndex, &item);
    x = sx + UIMAPITEM_FEET_ITEM_SX;
    y = sy + UIMAPITEM_FEET_ITEM_SY;
    xl = ITEM_ICON_WIDTH;
    yl = ITEM_ICON_HEIGHT;
    game_range.add(x, y, xl, yl, event, id);
    cx = x + xl / 2;
    cy = y + yl / 2;
    if(! IsItemNone(&item))
    {
        icon_index = GetItemIconIndex(&item);
        redraw_item_icon_image(cx, cy, icon_index, bitmap);
    }

    //(20) player deck0 item -------------------------------------
    id = UIMAPITEM_ID_DECK_0_ITEM;
	GetCharacterEquipOtherA(g_lPlayerIndex, &item);
    x = sx + UIMAPITEM_DECK_0_ITEM_SX;
    y = sy + UIMAPITEM_DECK_0_ITEM_SY;
    xl = ITEM_ICON_WIDTH;
    yl = ITEM_ICON_HEIGHT;
    game_range.add(x, y, xl, yl, event, id);
    cx = x + xl / 2;
    cy = y + yl / 2;
    if(! IsItemNone(&item))
    {
        icon_index = GetItemIconIndex(&item);
        redraw_item_icon_image(cx, cy, icon_index, bitmap);
    }

    //(21) player deck1 item -------------------------------------
    id = UIMAPITEM_ID_DECK_1_ITEM;
	GetCharacterEquipOtherB(g_lPlayerIndex, &item);
    x = sx + UIMAPITEM_DECK_1_ITEM_SX;
    y = sy + UIMAPITEM_DECK_1_ITEM_SY;
    xl = ITEM_ICON_WIDTH;
    yl = ITEM_ICON_HEIGHT;
    game_range.add(x, y, xl, yl, event, id);
    cx = x + xl / 2;
    cy = y + yl / 2;
    if(! IsItemNone(&item))
    {
        icon_index = GetItemIconIndex(&item);
        redraw_item_icon_image(cx, cy, icon_index, bitmap);
    }

    //(22) player deck2 item -------------------------------------
    id = UIMAPITEM_ID_DECK_2_ITEM;
	GetCharacterEquipOtherC(g_lPlayerIndex, &item);
    x = sx + UIMAPITEM_DECK_2_ITEM_SX;
    y = sy + UIMAPITEM_DECK_2_ITEM_SY;
    xl = ITEM_ICON_WIDTH;
    yl = ITEM_ICON_HEIGHT;
    game_range.add(x, y, xl, yl, event, id);
    cx = x + xl / 2;
    cy = y + yl / 2;
    if(! IsItemNone(&item))
    {
        icon_index = GetItemIconIndex(&item);
        redraw_item_icon_image(cx, cy, icon_index, bitmap);
    }
    

    // 寶藏裝備 -------------------------------------------------
    // Zhang Zhaohui 2003.5.31
    id = UIMAPITEM_ID_TREASURE_ITEM;
    GetCharacterTreasureItem( g_lPlayerIndex, &item );
    x = sx + UIMAPITEM_TREASURE_ITEM_SX;
    y = sy + UIMAPITEM_TREASURE_ITEM_SY;
    xl = ITEM_ICON_WIDTH;
    yl = ITEM_ICON_HEIGHT;
    game_range.add( x, y, xl, yl, event, id );
    if ( !IsItemNone( &item ) )
    {
        // 畫藏寶圖
    }



    //(24) player bag items -------------------------------------
    for(iy = 0; iy < UIMAPITEM_BAG_Y_COUNT; iy ++)
    {
        for(ix = 0; ix < UIMAPITEM_BAG_X_COUNT; ix ++)
        {
            idx = iy * UIMAPITEM_BAG_X_COUNT + ix;
            id = UIMAPITEM_ID_BAG_0_ITEM + idx;
            x = sx + UIMAPITEM_BAG_0_SX + ix * UIMAPITEM_BAG_DX;
            y = sy + UIMAPITEM_BAG_0_SY + iy * UIMAPITEM_BAG_DY;
            xl = ITEM_ICON_WIDTH;
            yl = ITEM_ICON_HEIGHT;
            game_range.add(x, y, xl, yl, event, id);

			GetCharacterBagItem(g_lPlayerIndex, idx, &item);
			if(! IsItemNone(&item))
            {
                cx = x + xl / 2;
                cy = y + yl / 2;
                icon_index = GetItemIconIndex(&item);
                redraw_item_icon_image(cx, cy, icon_index, bitmap);
            }
        }
    }
}


void    refresh_ui_mapitem(void)
{
}


void    redraw_uimapitem_mouse_point_info(SLONG id, BMP *bitmap)
{
    SLONG   event, item_sx, item_sy, index;
    TPOS_ITEM	item;

    event = UIMAPITEM_EVENT;
    switch(id)
    {
    case UIMAPITEM_ID_CLOSE:
        redraw_event_info_bar(event, id, (USTR*)TEXTMSG_MENU_CLOSE, (USTR*)TEXTMSG_MENU_CLOSE_INFO, bitmap);
        break;
    case UIMAPITEM_ID_DEC_STRENGTH:
        redraw_event_info_bar(event, id, (USTR*)TEXTMSG_SUB_BASE_STRENGTH, (USTR*)TEXTMSG_SUB_BASE_STRENGTH, bitmap);
        break;
    case UIMAPITEM_ID_ADD_STRENGTH:
        redraw_event_info_bar(event, id, (USTR*)TEXTMSG_ADD_BASE_STRENGTH, (USTR*)TEXTMSG_ADD_BASE_STRENGTH, bitmap);
        break;
    case UIMAPITEM_ID_DEC_INSTINCT:
        redraw_event_info_bar(event, id, (USTR*)TEXTMSG_SUB_BASE_INSTINCT, (USTR*)TEXTMSG_SUB_BASE_INSTINCT, bitmap);
        break;
    case UIMAPITEM_ID_ADD_INSTINCT:
        redraw_event_info_bar(event, id, (USTR*)TEXTMSG_ADD_BASE_INSTINCT, (USTR*)TEXTMSG_ADD_BASE_INSTINCT, bitmap);
        break;
    case UIMAPITEM_ID_DEC_WIT:
        redraw_event_info_bar(event, id, (USTR*)TEXTMSG_SUB_BASE_WIT, (USTR*)TEXTMSG_SUB_BASE_WIT, bitmap);
        break;
    case UIMAPITEM_ID_ADD_WIT:
        redraw_event_info_bar(event, id, (USTR*)TEXTMSG_ADD_BASE_WIT, (USTR*)TEXTMSG_ADD_BASE_WIT, bitmap);
        break;
    case UIMAPITEM_ID_DEC_LUCK:
        redraw_event_info_bar(event, id, (USTR*)TEXTMSG_SUB_BASE_LUCK, (USTR*)TEXTMSG_SUB_BASE_LUCK, bitmap);
        break;
    case UIMAPITEM_ID_ADD_LUCK:
        redraw_event_info_bar(event, id, (USTR*)TEXTMSG_ADD_BASE_LUCK, (USTR*)TEXTMSG_ADD_BASE_LUCK, bitmap);
        break;
    case UIMAPITEM_ID_TREASURE_ITEM:
        {
            LOCK_CHARACTER( g_lPlayerIndex );
            GetCharacterTreasureItem( g_lPlayerIndex, &item );
            UNLOCK_CHARACTER( g_lPlayerIndex );
            
            if ( !IsItemNone( &item ) )
            {
                item_sx = UIMAPITEM_TREASURE_ITEM_SX;
                item_sy = UIMAPITEM_TREASURE_ITEM_SY;
                redraw_icon_item_information( item_sx, item_sy, ITEM_INFO_NORMAL, &item, bitmap );
            }
        }
        break;
    case UIMAPITEM_ID_HEAD_ITEM:
        {
            LOCK_CHARACTER(g_lPlayerIndex);
			GetCharacterEquipHead(g_lPlayerIndex, &item);
            UNLOCK_CHARACTER(g_lPlayerIndex);

            if(!IsItemNone(&item))
            {
                item_sx = UIMAPITEM_HEAD_ITEM_SX;
                item_sy = UIMAPITEM_HEAD_ITEM_SY;
                redraw_icon_item_information(item_sx, item_sy, ITEM_INFO_NORMAL, &item, bitmap);
            }
        }
        break;
    case UIMAPITEM_ID_NECK_ITEM:
        {
            LOCK_CHARACTER(g_lPlayerIndex);
			GetCharacterEquipNeck(g_lPlayerIndex, &item);
            UNLOCK_CHARACTER(g_lPlayerIndex);

            if(!IsItemNone(&item))
            {
                item_sx = UIMAPITEM_NECK_ITEM_SX;
                item_sy = UIMAPITEM_NECK_ITEM_SY;
                redraw_icon_item_information(item_sx, item_sy, ITEM_INFO_NORMAL, &item, bitmap);
            }
        }
        break;
    case UIMAPITEM_ID_BODY_ITEM:
        {
            LOCK_CHARACTER(g_lPlayerIndex);
			GetCharacterEquipBody(g_lPlayerIndex, &item);
            UNLOCK_CHARACTER(g_lPlayerIndex);

            if(!IsItemNone(&item))
            {
                item_sx = UIMAPITEM_BODY_ITEM_SX;
                item_sy = UIMAPITEM_BODY_ITEM_SY;
                redraw_icon_item_information(item_sx, item_sy, ITEM_INFO_NORMAL, &item, bitmap);
            }
        }
        break;
    case UIMAPITEM_ID_WEAPON_ITEM:
        {
            LOCK_CHARACTER(g_lPlayerIndex);
			GetCharacterEquipWeapon(g_lPlayerIndex, &item);
            UNLOCK_CHARACTER(g_lPlayerIndex);

            if(! IsItemNone(&item))
            {
                item_sx = UIMAPITEM_WEAPON_ITEM_SX;
                item_sy = UIMAPITEM_WEAPON_ITEM_SY;
                redraw_icon_item_information(item_sx, item_sy, ITEM_INFO_NORMAL, &item, bitmap);
            }
        }
        break;
    case UIMAPITEM_ID_WAIST_ITEM:
        {
            LOCK_CHARACTER(g_lPlayerIndex);
			GetCharacterEquipWaist(g_lPlayerIndex, &item);
            UNLOCK_CHARACTER(g_lPlayerIndex);

            if(! IsItemNone(&item))
            {
                item_sx = UIMAPITEM_WAIST_ITEM_SX;
                item_sy = UIMAPITEM_WAIST_ITEM_SY;
                redraw_icon_item_information(item_sx, item_sy, ITEM_INFO_NORMAL, &item, bitmap);
            }
        }
        break;
    case UIMAPITEM_ID_WRIST_ITEM:
        {
            LOCK_CHARACTER(g_lPlayerIndex);
			GetCharacterEquipWrist(g_lPlayerIndex, &item);
            UNLOCK_CHARACTER(g_lPlayerIndex);

            if(! IsItemNone(&item))
            {
                item_sx = UIMAPITEM_WRIST_ITEM_SX;
                item_sy = UIMAPITEM_WRIST_ITEM_SY;
                redraw_icon_item_information(item_sx, item_sy, ITEM_INFO_NORMAL, &item, bitmap);
            }
        }
        break;
    case UIMAPITEM_ID_GLOVE_ITEM:
        {
            LOCK_CHARACTER(g_lPlayerIndex);
			GetCharacterEquipGlove(g_lPlayerIndex, &item);
            UNLOCK_CHARACTER(g_lPlayerIndex);

            if(! IsItemNone(&item))
            {
                item_sx = UIMAPITEM_GLOVE_ITEM_SX;
                item_sy = UIMAPITEM_GLOVE_ITEM_SY;
                redraw_icon_item_information(item_sx, item_sy, ITEM_INFO_NORMAL, &item, bitmap);
            }
        }
        break;
    case UIMAPITEM_ID_FEET_ITEM:
        {
            LOCK_CHARACTER(g_lPlayerIndex);
			GetCharacterEquipFeet(g_lPlayerIndex, &item);
            UNLOCK_CHARACTER(g_lPlayerIndex);

            if(! IsItemNone(&item))
            {
                item_sx = UIMAPITEM_FEET_ITEM_SX;
                item_sy = UIMAPITEM_FEET_ITEM_SY;
                redraw_icon_item_information(item_sx, item_sy, ITEM_INFO_NORMAL, &item, bitmap);
            }
        }
        break;
    case UIMAPITEM_ID_DECK_0_ITEM:
        {
            LOCK_CHARACTER(g_lPlayerIndex);
			GetCharacterEquipOtherA(g_lPlayerIndex, &item);
            UNLOCK_CHARACTER(g_lPlayerIndex);

            if(! IsItemNone(&item))
            {
                item_sx = UIMAPITEM_DECK_0_ITEM_SX;
                item_sy = UIMAPITEM_DECK_0_ITEM_SY;
                redraw_icon_item_information(item_sx, item_sy, ITEM_INFO_NORMAL, &item, bitmap);
            }
        }
        break;
    case UIMAPITEM_ID_DECK_1_ITEM:
        {
            LOCK_CHARACTER(g_lPlayerIndex);
			GetCharacterEquipOtherB(g_lPlayerIndex, &item);
            UNLOCK_CHARACTER(g_lPlayerIndex);

            if(! IsItemNone(&item))
            {
                item_sx = UIMAPITEM_DECK_1_ITEM_SX;
                item_sy = UIMAPITEM_DECK_1_ITEM_SY;
                redraw_icon_item_information(item_sx, item_sy, ITEM_INFO_NORMAL, &item, bitmap);
            }
        }
        break;
    case UIMAPITEM_ID_DECK_2_ITEM:
        {
            LOCK_CHARACTER(g_lPlayerIndex);
			GetCharacterEquipOtherC(g_lPlayerIndex, &item);
            UNLOCK_CHARACTER(g_lPlayerIndex);

            if(! IsItemNone(&item))
            {
                item_sx = UIMAPITEM_DECK_2_ITEM_SX;
                item_sy = UIMAPITEM_DECK_2_ITEM_SY;
                redraw_icon_item_information(item_sx, item_sy, ITEM_INFO_NORMAL, &item, bitmap);
            }
        }
        break;
    case UIMAPITEM_ID_BAG_0_ITEM:
    default:
        if(id >= UIMAPITEM_ID_BAG_0_ITEM && id < UIMAPITEM_ID_BAG_0_ITEM + UIMAPITEM_BAG_COUNTS)
        {
            index = id - UIMAPITEM_ID_BAG_0_ITEM;

            LOCK_CHARACTER(g_lPlayerIndex);
			GetCharacterBagItem(g_lPlayerIndex, index, &item);
            UNLOCK_CHARACTER(g_lPlayerIndex);

            if(! IsItemNone(&item))
            {
                item_sx = UIMAPITEM_BAG_0_SX + (index % UIMAPITEM_BAG_X_COUNT) * UIMAPITEM_BAG_DX;
                item_sy = UIMAPITEM_BAG_0_SY + (index / UIMAPITEM_BAG_X_COUNT) * UIMAPITEM_BAG_DY;
                redraw_icon_item_information(item_sx, item_sy, ITEM_INFO_NORMAL, &item, bitmap);
            }
        }
        break;
    }
}



SLONG   handle_ui_mapitem(UINT message, WPARAM wParam, LPARAM lParam)
{
    UI_MAPITEM_DATA *data = &ui_mapitem_data;
    static  SLONG   mouse_x, mouse_y;
    SLONG   event_type, event_id, index;

    switch(message)
    {
    case WM_MOUSEMOVE:
        mouse_x = GET_X_LPARAM(lParam);
        mouse_y = GET_Y_LPARAM(lParam);
        event_type = event_id = 0;
        game_range.mapping(mouse_x, mouse_y, &event_type, &event_id);
        data->hilight_id = event_id;
        break;
    case WM_LBUTTONDOWN:
        {
            mouse_x = GET_X_LPARAM(lParam);
            mouse_y = GET_Y_LPARAM(lParam);
            event_type = event_id = 0;
            game_range.mapping(mouse_x, mouse_y, &event_type, &event_id);
            switch(event_id)
            {
            case UIMAPITEM_ID_CLOSE:
                data->active_id = event_id;
                close_map_submenu(SUBMENU_ITEM);
                break;
            case UIMAPITEM_ID_ADD_STRENGTH:
                data->active_id = event_id;
                client_cmd_add_base_strength(1);
                break;
            case UIMAPITEM_ID_DEC_STRENGTH:
                data->active_id = event_id;
                client_cmd_sub_base_strength(1);
                break;
            case UIMAPITEM_ID_ADD_INSTINCT:
                data->active_id = event_id;
                client_cmd_add_base_instinct(1);
                break;
            case UIMAPITEM_ID_DEC_INSTINCT:
                data->active_id = event_id;
                client_cmd_sub_base_instinct(1);
                break;
            case UIMAPITEM_ID_ADD_WIT:
                data->active_id = event_id;
                client_cmd_add_base_wit(1);
                break;
            case UIMAPITEM_ID_DEC_WIT:
                data->active_id = event_id;
                client_cmd_sub_base_wit(1);
                break;
            case UIMAPITEM_ID_ADD_LUCK:
                data->active_id = event_id;
                client_cmd_add_base_luck(1);
                break;
            case UIMAPITEM_ID_DEC_LUCK:
                data->active_id = event_id;
                client_cmd_sub_base_luck(1);
                break;
            case UIMAPITEM_ID_HEAD_ITEM:
                data->active_id = event_id;
                client_cmd_left_hit_head_item();
                break;
            case UIMAPITEM_ID_NECK_ITEM:
                data->active_id = event_id;
                client_cmd_left_hit_neck_item();
                break;
            case UIMAPITEM_ID_BODY_ITEM:
                data->active_id = event_id;
                client_cmd_left_hit_body_item();
                break;
            case UIMAPITEM_ID_WEAPON_ITEM:
                data->active_id = event_id;
                client_cmd_left_hit_hands_item();
                break;
            case UIMAPITEM_ID_WAIST_ITEM:
                data->active_id = event_id;
                client_cmd_left_hit_waist_item();
                break;
            case UIMAPITEM_ID_WRIST_ITEM:
                data->active_id = event_id;
                client_cmd_left_hit_wrist_item();
                break;
            case UIMAPITEM_ID_GLOVE_ITEM:
                data->active_id = event_id;
                client_cmd_left_hit_glove_item();
                break;
            case UIMAPITEM_ID_FEET_ITEM:
                data->active_id = event_id;
                client_cmd_left_hit_feet_item();
                break;
            case UIMAPITEM_ID_DECK_0_ITEM:
                data->active_id = event_id;
				client_cmd_left_hit_othera_item();
				break;
            case UIMAPITEM_ID_DECK_1_ITEM:
                data->active_id = event_id;
				client_cmd_left_hit_otherb_item();
				break;
            case UIMAPITEM_ID_DECK_2_ITEM:
                data->active_id = event_id;
				client_cmd_left_hit_otherc_item();
                break;
            case UIMAPITEM_ID_TREASURE_ITEM:
                data->active_id = event_id;
                client_cmd_left_hit_treasure_item( );
                break;
            case UIMAPITEM_ID_BAG_0_ITEM:
            default:
                data->active_id = event_id;
                if(event_id >= UIMAPITEM_ID_BAG_0_ITEM && event_id < UIMAPITEM_ID_BAG_0_ITEM + UIMAPITEM_BAG_COUNTS)
                {
                    index = event_id - UIMAPITEM_ID_BAG_0_ITEM;
                    client_cmd_left_hit_bag_item(index);
                }
                break;
            }
        }
        break;
    case WM_LBUTTONUP:
        data->active_id = 0;
        break;
	case WM_RBUTTONDOWN:
		{
			mouse_x = GET_X_LPARAM(lParam);
			mouse_y = GET_Y_LPARAM(lParam);
			event_type = event_id = 0;
			game_range.mapping(mouse_x, mouse_y, &event_type, &event_id);
			switch(event_id)
			{
            case UIMAPITEM_ID_TREASURE_ITEM:
                data->active_id = event_id;
                client_cmd_right_hit_treasure_item( );
                break;
			case UIMAPITEM_ID_BAG_0_ITEM:
			default:
                data->active_id = event_id;
                if(event_id >= UIMAPITEM_ID_BAG_0_ITEM && event_id < UIMAPITEM_ID_BAG_0_ITEM + UIMAPITEM_BAG_COUNTS)
                {
                    index = event_id - UIMAPITEM_ID_BAG_0_ITEM;
                    client_cmd_right_hit_bag_item(index);
                }
				break;
			}
		}
		break;
	case WM_RBUTTONUP:
		break;
    }
    return  0;
}


SLONG   is_mapitem_menu_opened(void)
{
    if(ui_mapitem_data.is_opened)
        return  TRUE;
    return  FALSE;
}


void    open_mapitem_menu(SLONG flag)
{
	if(flag)
	{
		ui_mapitem_data.is_opened = TRUE;
		set_map_view_range(SCREEN_WIDTH/2, 0, SCREEN_WIDTH/2, SCREEN_HEIGHT);
	}
	else
	{
		ui_mapitem_data.is_opened = FALSE;
		set_map_view_range(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	}
}

