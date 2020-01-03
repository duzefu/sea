/*
**	Client_Item.cpp 
**	Client item functions.
**
**	Jack, 2003.1.2
**
**	Zhang Zhaohui modified, 2003.4.3
*/
#include "MainFun.h"
#include "NetGE_MainFunc.h"
//
#include "UIInfoBar.h"
#include "ClientMain.h"
#include "Client_Item.h"
#include "CRange.h"
#include "MouseHand.h"

#include "UiItemInfo.h"

// ZZH
CONST DWORD MAX_INFO = 256;
CONST DWORD MAX_INFO_LEN = 80;
CONST CHAR  ITEM_INFO_INI[] = "data\\itemhint.ini";
/************************************************************************************************************/
/* STRUCTURES                                                                                               */
/************************************************************************************************************/
//道具圖標
typedef struct tagITEM_ICON_IMAGE
{
    CAKE_FRAME_ANI  *cfa;       //所有道具圖標影像指標
    CAKE_FRAME      *cf[MAX_ITEM_ICONS]; //道具圖標
    //
    CAKE_FRAME_ANI  *box_lock_cfa;      //放置在陸地上的,關著的寶箱.
    SLONG   box_lock_ox;    //顯示時的偏移位置
    SLONG   box_lock_oy;    //顯示時的偏移位置
    //
    CAKE_FRAME_ANI  *box_unlock_cfa;    //放置在陸地上的,開著的寶箱.
    SLONG   box_unlock_ox;  //顯示時的偏移位置
    SLONG   box_unlock_oy;  //顯示時的偏移位置
    //
    CAKE_FRAME_ANI  *box_open_cfa;      //放置在陸地上的,寶箱打開.
    SLONG   box_open_ox;    //顯示時的偏移位置
    SLONG   box_open_oy;    //顯示時的偏移位置
    //
    //CAKE_FRAME_ANI  *one_gold_cfa;      //一個單位金錢
    //CAKE_FRAME_ANI  *some_golds_cfa;    //多個金錢
    //
} ITEM_ICON_IMAGE, *LPITEM_ICON_IMAGE;


// ZZH
typedef struct tagITEM_INFO_DATA
{
	SLONG data[MAX_INFO];
} ITEM_INFO_DATA;

CHAR item_info[MAX_INFO][MAX_INFO_LEN];

static SLONG init_item_info( VOID );
static VOID  free_item_info( VOID );
static SLONG calc_item_info( TPOS_ITEM *item, CHAR (*info)[80], DWORD info_count, SLONG *max_len );
static SLONG calc_item_data( TPOS_ITEM *item, ITEM_INFO_DATA * data );

/************************************************************************************************************/
/* GLOBALS                                                                                                  */
/************************************************************************************************************/
ITEM_ICON_IMAGE     item_icon_image;
//

extern	DATA_FILE	*packed_menu_file;

/************************************************************************************************************/
/* FUNCTIONS                                                                                                */
/************************************************************************************************************/
int     init_item(void)
{
    SLONG   result;

	set_data_file(packed_data_file);
	result = InitItemSystem();
	if(0 != result)
		return	-1;
	
    result = init_item_icon_image();
    if(TTN_OK != result)
        return  -1;

	// ZZH
	result = init_item_info();
	if ( TTN_OK != result )
		return -2;

    return  0;
}

void    active_item(int active)
{
}


void    free_item(void)
{
    free_item_icon_image();
	FreeItemSystem();
}



SLONG   init_item_icon_image(void)
{
    ITEM_ICON_IMAGE *data = &item_icon_image;
    USTR    filename[_MAX_FNAME];
    SLONG   result, i, frames, valid_frames;
    CAKE_FRAME_ANI  *cfa;
    CAKE_FRAME  *cf;

    //(0) init images pointer ------------------------------------------------
    data->cfa = NULL;
    for(i=0; i<MAX_ITEM_ICONS; i++)
    {
        data->cf[i] = NULL;
    }

    //(1) load item icon images ----------------------------------------------
    set_data_file(packed_menu_file);
    strcpy((char *)filename, "menu\\itemicon.cak");
    result = load_cake_frame_ani_from_file((USTR*)filename, &data->cfa);
    if(TTN_OK != result)
        return  TTN_ERROR;

    frames = count_cake_frames(data->cfa);
    valid_frames = min(frames, MAX_ITEM_ICONS);
    for(i=0; i<valid_frames; i++)
    {
        cfa = get_specify_cake_frame_ani(data->cfa, i);
        data->cf[i] = cfa->cake_frame;
    }

    //(2) load item box images -----------------------------------------------
    set_data_file(packed_menu_file);
    strcpy((char *)filename, "menu\\boxlock.cak");
    result = load_cake_frame_ani_from_file((USTR*)filename, &data->box_lock_cfa);
    if(TTN_OK != result)
        return  TTN_ERROR;
    cfa = get_specify_cake_frame_ani(data->box_lock_cfa, 0);
    cf = cfa->cake_frame;
    data->box_lock_ox = -(cf->frame_rx + cf->rle->w/2);
    data->box_lock_oy = -(cf->frame_ry + cf->rle->h/2);

    set_data_file(packed_menu_file);
    strcpy((char *)filename, "menu\\boxulock.cak");
    result = load_cake_frame_ani_from_file((USTR*)filename, &data->box_unlock_cfa);
    if(TTN_OK != result)
        return  TTN_ERROR;
    cfa = get_specify_cake_frame_ani(data->box_unlock_cfa, 0);
    cf = cfa->cake_frame;
    data->box_unlock_ox = -(cf->frame_rx + cf->rle->w/2);
    data->box_unlock_oy = -(cf->frame_ry + cf->rle->h/2);

    set_data_file(packed_menu_file);
    strcpy((char *)filename, "menu\\boxopen.cak");
    result = load_cake_frame_ani_from_file((USTR*)filename, &data->box_open_cfa);
    if(TTN_OK != result)
        return  TTN_ERROR;
    cfa = get_specify_cake_frame_ani(data->box_open_cfa, 0);
    cf = cfa->cake_frame;
    data->box_open_ox = -(cf->frame_rx + cf->rle->w/2);
    data->box_open_oy = -(cf->frame_ry + cf->rle->h/2);
    //

    return  TTN_OK;
}


void    free_item_icon_image(void)
{
    ITEM_ICON_IMAGE *data = &item_icon_image;
    SLONG   i;

    destroy_cake_frame_ani(&data->cfa);
    for(i=0; i<MAX_ITEM_ICONS; i++)
    {
        data->cf[i] = NULL;
    }
    destroy_cake_frame_ani(&data->box_lock_cfa);
    destroy_cake_frame_ani(&data->box_unlock_cfa);
    destroy_cake_frame_ani(&data->box_open_cfa);
}


void    get_item_icon_size(SLONG index, SLONG *hrooms, SLONG *vrooms, SLONG *xl, SLONG *yl)
{
    *hrooms = 1;
    *vrooms = 1;
    *xl = *hrooms * ITEM_ICON_WIDTH;
    *yl = *vrooms * ITEM_ICON_HEIGHT;
}


CAKE_FRAME_ANI  *get_item_icon_cfa(SLONG index)
{
    ITEM_ICON_IMAGE *data = &item_icon_image;
    CAKE_FRAME_ANI  *cfa;

    cfa = get_specify_cake_frame_ani(data->cfa, index);
    return  cfa;
}


void    redraw_item_icon_image(SLONG cx, SLONG cy, SLONG index, BMP* bitmap)
{
    ITEM_ICON_IMAGE *data = &item_icon_image;
    CAKE_FRAME  *cf;
    RLE *rle;

    if(index < 0 || index >= MAX_ITEM_ICONS)
        return;
    cf = data->cf[index];
    if(! cf)
        return;

    rle = cf->rle;
    if(! rle)
        return;

    put_rle(cx - rle->w/2, cy - rle->h/2, rle, bitmap);
}


void    redraw_land_box_lock_image(SLONG cx, SLONG cy, SLONG frame, BMP *bitmap, SLONG selected)
{
    ITEM_ICON_IMAGE *data = &item_icon_image;
    CAKE_FRAME_ANI  *cfa;
    CAKE_FRAME  *cf;
    SLONG   sx, sy;

    cfa = get_specify_cake_frame_ani(data->box_lock_cfa, frame);
    if(cfa)
    {
        cf = cfa->cake_frame;
        sx = cx + cf->frame_rx + data->box_lock_ox;
        sy = cy + cf->frame_ry + data->box_lock_oy;
        if(selected)
		{
            //mask_edge_put_rle(sx, sy, SYSTEM_YELLOW, cf->rle, (BMP*)vbitmap);
            additive_put_rle(sx, sy, cf->rle, bitmap);
		}
        else
		{
            put_rle(sx, sy, cf->rle, bitmap);
		}
    }
}


void    redraw_land_box_unlock_image(SLONG cx, SLONG cy, SLONG frame, BMP* bitmap, SLONG selected)
{
    ITEM_ICON_IMAGE *data = &item_icon_image;
    CAKE_FRAME_ANI  *cfa;
    CAKE_FRAME  *cf;
    SLONG   sx, sy;

    cfa = get_specify_cake_frame_ani(data->box_unlock_cfa, frame);
    if(cfa)
    {
        cf = cfa->cake_frame;
        sx = cx + cf->frame_rx + data->box_unlock_ox;
        sy = cy + cf->frame_ry + data->box_unlock_oy;
        if(selected)
            //mask_edge_put_rle(sx, sy, SYSTEM_YELLOW, cf->rle, (BMP*)vbitmap);
            additive_put_rle(sx, sy, cf->rle, bitmap);
        else
            put_rle(sx, sy, cf->rle, bitmap);
    }
}


void    redraw_land_box_open_image(SLONG cx, SLONG cy, SLONG frame, BMP *bitmap, SLONG selected)
{
    ITEM_ICON_IMAGE *data = &item_icon_image;
    CAKE_FRAME_ANI  *cfa;
    CAKE_FRAME  *cf;
    SLONG   sx, sy;

    cfa = get_specify_cake_frame_ani(data->box_open_cfa, frame);
    if(cfa)
    {
        cf = cfa->cake_frame;
        sx = cx + cf->frame_rx + data->box_open_ox;
        sy = cy + cf->frame_ry + data->box_open_oy;
        if(selected)
            //mask_edge_put_rle(sx, sy, SYSTEM_YELLOW, cf->rle, (BMP*)vbitmap);
            additive_put_rle(sx, sy, cf->rle, bitmap);
        else
            put_rle(sx, sy, cf->rle, bitmap);
    }
}



void	redraw_icon_item_information(SLONG item_sx, SLONG item_sy, SLONG show_for, TPOS_ITEM *item, BMP *bitmap)
{
    enum
    {   MAX_INFO_LINES      =   55,
    INFO_LINE_LEN           =   80,
    INFO_LINE_HEIGHT        =   16,
    INFO_WIN_GAP_X          =   12,
    INFO_WIN_GAP_Y          =   12,
    INFO_FONT_WIDTH         =   12,
    INFO_FONT_HEIGHT        =   12,
    //
    TEMP_STR_LEN            =   INFO_LINE_LEN,
    };
    SLONG   base;
    CHAR    info_str[MAX_INFO_LINES][INFO_LINE_LEN];
    CHAR    temp[TEMP_STR_LEN];
    SLONG   info_len[MAX_INFO_LINES];
    SLONG   info_lines, max_info_len ;
    SLONG   win_sx, win_sy, win_xl, win_yl, win_cx;
    SLONG   disp_x, disp_y;
    SLONG   i;
    SLONG   icon_index;

    icon_index = GetItemIconIndex(item);
    base = GetItemBaseID(item);

    for(i = 0; i < MAX_INFO_LINES; i ++)
    {
        info_len[i] = 0;
        memset(info_str[i], '\0', INFO_LINE_LEN);
    }
    info_lines = 0;

    //get item informations ---------------------------------------------------------------------------------
    //name info
    sprintf((char *)temp, "%s", GetItemName(item));
    info_len[info_lines] = strlen((const char *)temp);
    sprintf((char *)info_str[info_lines], "~C4%s~C0", temp);
    info_lines ++;
	
	switch(show_for)
	{
	case ITEM_INFO_NORMAL:
		break;
	case ITEM_INFO_BUY:
		sprintf((char *)temp, "NEED: %d", ComputeItemBuyCost(item));
		info_len[info_lines] = strlen((const char *)temp);
		sprintf((char *)info_str[info_lines], "~C4%s~C0", temp);
		info_lines ++;
		break;
	case ITEM_INFO_SELL:
		sprintf((char *)temp, "SELL: %d", ComputeItemSellPrice(item));
		info_len[info_lines] = strlen((const char *)temp);
		sprintf((char *)info_str[info_lines], "~C4%s~C0", temp);
		info_lines ++;
		break;
	}

	//append new info lines...
	// Zhang Zhaohui 2003.4.4
	DWORD lines;
	lines = 0;
	lines = calc_item_info( item, &info_str[info_lines], MAX_INFO_LINES-info_lines, &info_len[info_lines] );
	info_lines += lines;

    max_info_len = 0;
    for(i=0; i<info_lines; i++)
    {
        if(info_len[i] > max_info_len)
            max_info_len = info_len[i];
    }

    //redraw item informations -------------------------------------------------------------------------------
    win_xl = (max_info_len + 1) / 2 * INFO_FONT_WIDTH + INFO_WIN_GAP_X ;
    win_yl = info_lines * INFO_LINE_HEIGHT + INFO_WIN_GAP_Y;
    find_appropriate_window_position(item_sx, item_sy, ITEM_ICON_WIDTH, ITEM_ICON_HEIGHT, 
		bitmap->w, bitmap->h, win_xl, win_yl,
        &win_sx, &win_sy);
    win_cx = win_sx + win_xl / 2;
    dark_put_bar(win_sx, win_sy, win_xl, win_yl, bitmap, 10);
    disp_x = win_sx + INFO_WIN_GAP_X / 2;
    disp_y = win_sy + INFO_WIN_GAP_Y / 2;
    for(i=0; i<info_lines; i++)
    {
        disp_x = win_cx - (info_len[i] + 1) / 2 * INFO_FONT_WIDTH / 2;
        print12(disp_x, disp_y, (USTR*)info_str[i], PEST_PUT, bitmap);
        disp_y += INFO_LINE_HEIGHT;
    }
}


void    redraw_map_item( SLONG map_no, SLONG map_sx, SLONG map_sy, BMP *bitmap)
{
    SLONG   p;
    SLONG   x, y;
    TPOS_ITEM	item;
    SLONG   frame, state;

    p = GetZoneItemNext(map_no);
    while(p != map_no)
	{
		LOCK_ITEM(0);
		GetZoneItemPosition(p, &x, &y);
		GetZoneItem(p, &item);
		frame = GetZoneItemFrame(p);
		state = GetZoneItemState(p);
		UNLOCK_ITEM(0);

		if(! IsItemNone(&item))
		{
			x -= map_sx;
			y -= map_sy;
			frame = min(frame, 7); //圖像只有8幀
			state &= GAME_ITEM_STATE_MASK;
			
			if( x >=  - ITEM_STAY_WIDTH/2 && x < bitmap->w + ITEM_STAY_WIDTH/2
				&& y >=  - ITEM_STAY_HEIGHT/2 && y < bitmap->h + ITEM_STAY_HEIGHT/2 )
			{
				if(mouse_hand.point_kind == RT_MAP_ITEM && mouse_hand.point_no == p)
				{
					switch(state)
					{
					case GAME_ITEM_STATE_LOCK:
						redraw_land_box_lock_image(x, y, frame, bitmap, TRUE);
						game_range.add( x - ITEM_STAY_MASK_WIDTH / 2, y - ITEM_STAY_MASK_HEIGHT/2,
							ITEM_STAY_MASK_WIDTH, ITEM_STAY_MASK_HEIGHT, RT_MAP_ITEM, p);
						break;
					case GAME_ITEM_STATE_OPEN:
						redraw_land_box_open_image(x, y, frame, bitmap, TRUE);
						break;
					case GAME_ITEM_STATE_UNLOCK:
						redraw_land_box_unlock_image(x, y, frame, bitmap, TRUE);
						game_range.add( x - ITEM_STAY_MASK_WIDTH / 2, y - ITEM_STAY_MASK_HEIGHT/2,
							ITEM_STAY_MASK_WIDTH, ITEM_STAY_MASK_HEIGHT, RT_MAP_ITEM, p);
						break;
					}
				}
				else
				{
					switch(state)
					{
					case GAME_ITEM_STATE_LOCK:
						redraw_land_box_lock_image(x, y, frame, bitmap, FALSE);
						game_range.add( x - ITEM_STAY_MASK_WIDTH / 2, y - ITEM_STAY_MASK_HEIGHT/2,
							ITEM_STAY_MASK_WIDTH, ITEM_STAY_MASK_HEIGHT, RT_MAP_ITEM, p);
						break;
					case GAME_ITEM_STATE_OPEN:
						redraw_land_box_open_image(x, y, frame, bitmap, FALSE);
						break;
					case GAME_ITEM_STATE_UNLOCK:
						redraw_land_box_unlock_image(x, y, frame, bitmap, FALSE);
						game_range.add( x - ITEM_STAY_MASK_WIDTH / 2, y - ITEM_STAY_MASK_HEIGHT/2,
							ITEM_STAY_MASK_WIDTH, ITEM_STAY_MASK_HEIGHT, RT_MAP_ITEM, p);
						break;
					}
				}
			}
		}

        p = GetZoneItemNext(p);
    }
}



void    refresh_map_item(SLONG map_no)
{
	SLONG	p;
	TPOS_ITEM	item;
    SLONG   state, action, frame;

    p = GetZoneItemNext(map_no);
    while(p != map_no)
	{
		LOCK_ITEM(0);
		GetZoneItem(p, &item);
		frame = GetZoneItemFrame(p);
		state = GetZoneItemState(p);
		UNLOCK_ITEM(0);

		if(! IsItemNone(&item))
		{
			//refresh data
			switch(state  & GAME_ITEM_STATE_MASK)
			{
			case GAME_ITEM_STATE_LOCK:
				frame ++;
				if(frame > 80 + rand() % 30 )  //每隔5,6秒鍾閃爍一下.
				{
					LOCK_ITEM(0);
					SetZoneItemFrame(p, 0);
					UNLOCK_ITEM(0);
				}
				break;
			case GAME_ITEM_STATE_OPEN:
				frame ++;
				if(frame >= 8)
				{
					action = state & GAME_ITEM_ACTION_MASK;
					if(action == GAME_ITEM_ACTION_DISAPPEAR)
					{
						//ready for delete this item.
						LOCK_ITEM(0);
						SetItemNone(&item);
						SetZoneItem(p, &item);
						UNLOCK_ITEM(0);
					}
					else
					{
						SetZoneItemState(p, GAME_ITEM_STATE_UNLOCK);
					}
				}
				break;
			case GAME_ITEM_STATE_UNLOCK:
				frame ++;
				if(frame > 80 + rand() % 30 )  //每隔5,6秒鍾閃爍一下.
				{
					SetZoneItemFrame(p, 0);
				}
				break;
			}
		}

		p = GetZoneItemNext(p);
    }
    return;
}


void    open_and_disappear_game_item(SLONG index, SLONG open_npc)
{
	SetZoneItemState(index, GAME_ITEM_STATE_OPEN | GAME_ITEM_ACTION_DISAPPEAR);
	SetZoneItemFrame(index, 0);
    //game_item[index].opener = open_npc;
}

/************************************************************************/
/* 計算物品的屬性                                                       */
/************************************************************************/

SLONG init_item_info( VOID )
{
	USTR  line[1024];
	SLONG result, file_size, buf_index = 0;
	USTR *file_buf = NULL;
	UINT len;
	SLONG ini_index = 0;
	SLONG line_index = 0;


	memset( item_info, 0, MAX_INFO*MAX_INFO_LEN*sizeof(CHAR) );

	set_data_file( packed_data_file );
	file_size = load_file_to_buffer( (USTR*)ITEM_INFO_INI, &file_buf );
	if ( file_size <= 0 )
	{
		log_error( 1, "Error: read file failed. %s ", ITEM_INFO_INI );
		return TTN_NOT_OK;
	}
	
	result = get_buffer_line( (CHAR*)file_buf, &buf_index, file_size, (CHAR*)line, 1024 );
	while ( result == TTN_OK )
	{
		len = strlen( (CHAR*)line );
		if ( len > 0 && line[0] !=';' )
		{
			line_index = 0;
			ini_index = get_buffer_number( line, &line_index );
			if ( ini_index >= 0 && ini_index < MAX_INFO )
			{
				strcpy( item_info[ini_index], 
							(CONST CHAR*)get_buffer_string( line, &line_index ) );
			}
		}

		result = get_buffer_line( (CHAR*)file_buf, &buf_index, file_size, (CHAR*)line, 1024 );
	}
	
	if ( file_buf )
		free( file_buf );

	return TTN_OK;
}

VOID free_item_info( VOID )
{
}

// ZZH
// 如果成功返回 hint 的行數
//		max_len 返回最長的字符串
SLONG calc_item_info( TPOS_ITEM *item, CHAR (*info)[80], DWORD info_count, SLONG *max_len )
{
	static CHAR buf1[128];
	static CHAR buf2[32];
	ITEM_INFO_DATA data;
	DWORD i;
	DWORD info_line = 0;
	BOOL sex_dis = FALSE;
	BOOL only = FALSE;
	DWORD j = 0;
	
	buf1[0] = '\0';

	if ( !item )
		return TTN_NOT_OK;

	if ( calc_item_data( item, &data ) != TTN_OK )
		return TTN_NOT_OK;

	for ( i = ITEM_INFO_GENERAL_ONLY; i <= ITEM_INFO_HOROSCOPER_ONLY; i++ )
	{
		if ( !data.data[i] )
			continue;

		if ( data.data[ITEM_INFO_MAN_ONLY] && !data.data[ITEM_INFO_WOMAN_ONLY])
		{
			strcpy( buf2, item_info[ITEM_INFO_MAN_ONLY] );
			strcat( buf2, item_info[i] );
		}
		else if ( !data.data[ITEM_INFO_MAN_ONLY] && data.data[ITEM_INFO_WOMAN_ONLY])
		{
			strcpy( buf2, item_info[ITEM_INFO_WOMAN_ONLY] );
			strcat( buf2, item_info[i] );

		}
		else
			strcpy( buf2, item_info[i] );

		strcat( buf1, buf2 );
		strcat( buf1, " ");
		only = TRUE;
		j++;
	}

	// 適用於所有人
	if ( j == ITEM_INFO_HOROSCOPER_ONLY - ITEM_INFO_GENERAL_ONLY + 1 )
		only = FALSE;

	for ( i = 0; i < MAX_INFO; i++ )
	{
		if ( i >= ITEM_INFO_MAN_ONLY &&  i < ITEM_INFO_USER )
			continue;

		if ( i == ITEM_INFO_USER && only )
		{
			sprintf( info[info_line], ( LPCSTR)item_info[i], buf1 );
			max_len[info_line] = strlen( info[info_line] );

			info_line++;
			
			if ( info_line >= info_count)
				break;

		}

		if ( data.data[i] )
		{
			sprintf( info[info_line], (LPCSTR)item_info[i], data.data[i] );
		
			max_len[info_line] = strlen( info[info_line] );

			info_line++;
			
			if ( info_line >= info_count)
				break;
		}
	}

	// 顯示裝備的使用人

	return info_line;
}


SLONG calc_item_data( TPOS_ITEM *item, ITEM_INFO_DATA *data )
{
	TPOS_ITEM_BS *item_bs = NULL;
	TPOS_ITEM_RANDOM *item_ran = NULL;
	
	SLONG level = GetCharacterLevel( g_lPlayerIndex );


	item_bs = &GameItemBase[item->BaseID];
	item_ran = &item->IR;

	if ( !item_bs || IsItemNone( item ) )
		return TTN_NOT_OK;
	
	memset( data, 0, sizeof( ITEM_INFO_DATA ) );

	switch ( item_bs->Type )
	{
	case ITEM_TYPE_LAND_NORMAL:
		
		if ( item_bs->Special == LAND_ITEM_SPECIAL1_NEVER_SHATTER )
			data->data[ITEM_INFO_INDESTRUCTIBLE] = 1;
		else
			data->data[ITEM_INFO_DURABILITY] = item->Hp;

		// 最小需求
		data->data[ITEM_INFO_REQUIRED_GOODBAD] = item_bs->NeedGoodEvil;
		data->data[ITEM_INFO_REQUIRED_STR]     = item_bs->Land.MinNeedStr;
		data->data[ITEM_INFO_REQUIRED_INS]     = item_bs->Land.MinNeedIns;
		data->data[ITEM_INFO_REQUIRED_WIT]     = item_bs->Land.MinNeedWit;
		data->data[ITEM_INFO_REQUIRED_LUCKY]   = item_bs->Land.MinNeedLuck;

		// 命中率
		data->data[ITEM_INFO_HITCHANCE] = item_bs->Land.HitChance;
		
		// 膛爆率
		data->data[ITEM_INFO_EXPLODERATE] = item_bs->Land.ExplodeRate;

		// 攻擊力
		data->data[ITEM_INFO_BASEATT] = item_bs->Land.BaseAtt;

		// 防禦力
		data->data[ITEM_INFO_BASEDEF] = item_bs->Land.BaseDef;

		// 生命恢復速度
		data->data[ITEM_INFO_RESHPRATE] = item_bs->Land.ResHpRate;

		// 魔力恢復速度
		data->data[ITEM_INFO_RESMPRATE] = item_bs->Land.ResMpRate;

		switch ( item_ran->Land.Special1 )
		{
		case LAND_ITEM_SPECIAL1_NONE:			
			break;

		case LAND_ITEM_SPECIAL1_ACC_MUSE:				// 加速冥想
			data->data[ITEM_INFO_ACC_MUSE] = 1;
			break;

		case LAND_ITEM_SPECIAL1_ANTI_BAD:				// 負面狀態免疫
			data->data[ITEM_INFO_ANTI_BAD] = 1;
			break;

		case LAND_ITEM_SPECIAL1_LEVEL_ADD_ATT:			// 基於等級增加傷害
			data->data[ITEM_INFO_LEVEL_ADD_ATT] = (LONG)( (DOUBLE)level * LEVEL_ADD_ATT );
			data->data[ITEM_INFO_BASEATT] += data->data[ITEM_INFO_LEVEL_ADD_ATT];
			break;

		case LAND_ITEM_SPECIAL1_LEVEL_ADD_DEF:			// 基於等級增加防禦
			data->data[ITEM_INFO_LEVEL_ADD_DEF] = (LONG)( (DOUBLE)level * LEVEL_ADD_DEF );
			data->data[ITEM_INFO_BASEDEF] += data->data[ITEM_INFO_LEVEL_ADD_DEF];
			break;

		case LAND_ITEM_SPECIAL1_LEVEL_ADD_MAX_HP:		// 基於等級增加生命上限
			data->data[ITEM_INFO_LEVEL_ADD_MAX_HP] = (LONG)( (DOUBLE)level * LEVEL_ADD_MAX_HP );
			break;

		case LAND_ITEM_SPECIAL1_LEVEL_ADD_MAX_MP:		// 基於等級增加魔力上限
			data->data[ITEM_INFO_LEVEL_ADD_MAX_MP] = (LONG)( (DOUBLE)level * LEVEL_ADD_MAX_MP );
			break;


		case LAND_ITEM_SPECIAL1_NEVER_SHATTER:			// 永不磨損
			data->data[ITEM_INFO_INDESTRUCTIBLE] = 1;
			data->data[ITEM_INFO_DURABILITY] = 0;
			break;


		case LAND_ITEM_SPECIAL1_LOWER_DAMAGE:			// 減少物理傷害
			data->data[ITEM_INFO_LOWER_DAMAGE] = LOW_DAMAGE;
			break;
		}

		switch ( item_ran->Land.Special2 )
		{
		case LAND_ITEM_SPECIAL2_NONE:
			break;
		case LAND_ITEM_SPECIAL2_LOWER_REQUEST:			// 降低需求

			data->data[ITEM_INFO_REQUIRED_STR]     = (LONG)
				( (DOUBLE)data->data[ITEM_INFO_REQUIRED_STR] * ( 1 - LOWER_REQUIRED ) );

			data->data[ITEM_INFO_REQUIRED_INS]     = (LONG)
				( (DOUBLE)data->data[ITEM_INFO_REQUIRED_INS] * ( 1 - LOWER_REQUIRED ) );

			data->data[ITEM_INFO_REQUIRED_WIT]     = (LONG)
				( (DOUBLE)data->data[ITEM_INFO_REQUIRED_WIT] * ( 1 - LOWER_REQUIRED ) );

			data->data[ITEM_INFO_REQUIRED_LUCKY]   = (LONG)
				( (DOUBLE)data->data[ITEM_INFO_REQUIRED_LUCKY] * ( 1 - LOWER_REQUIRED ) );

			data->data[ITEM_INFO_LOWER_REQUIRED] = 1;

			break;
		case LAND_ITEM_SPECIAL2_BE_TORTOISE:					// 變烏龜
			data->data[ITEM_INFO_BE_TORTOISE] = 1;
			break;
		case LAND_ITEM_SPECIAL2_BE_PIG:							// 變豬
			data->data[ITEM_INFO_BE_PIG] = 1;
			break;
		case LAND_ITEM_SPECIAL2_SLEEP:							// 昏睡
			data->data[ITEM_INFO_SLEEP] = 1;
			break;
		case LAND_ITEM_SPECIAL2_ADD_SKILL_LEVEL:				// 技能等級+1
			data->data[ITEM_INFO_ADD_SKILL_LEVEL] = 1;
			break;
		case LAND_ITEM_SPECIAL2_ADD_GENERAL_SKILL_LEVEL:		// 提督技能等級+1
			data->data[ITEM_INFO_ADD_GENERAL_SKILL_LEVEL] = 1;
			break;
		case LAND_ITEM_SPECIAL2_ADD_SWORDER_SKILL_LEVEL:		// 劍客技能等級+1
			data->data[ITEM_INFO_ADD_SWORDER_SKILL_LEVEL] = 1;
			break;
		case LAND_ITEM_SPECIAL2_ADD_EXPLORER_SKILL_LEVEL:		// 探險家技能等級+1
			data->data[ITEM_INFO_ADD_EXPLORER_SKILL_LEVEL] = 1;
			break;
		case LAND_ITEM_SPECIAL2_ADD_THIEF_SKILL_LEVEL:			// 小偷技能等級+1
			data->data[ITEM_INFO_ADD_THIEF_SKILL_LEVEL] = 1;
			break;
		case LAND_ITEM_SPECIAL2_ADD_TRADER_SKILL_LEVEL:			// 商人技能等級+1
			data->data[ITEM_INFO_ADD_TRADER_SKILL_LEVEL] = 1;
			break;
		case LAND_ITEM_SPECIAL2_ADD_CLERIC_SKILL_LEVEL:			// 牧師技能等級+1
			data->data[ITEM_INFO_ADD_CLERIC_SKILL_LEVEL] = 1;
			break;
		case LAND_ITEM_SPECIAL2_ADD_HOROSCOPER_SKILL_LEVEL:		// 占星術士技能等級+1
			data->data[ITEM_INFO_ADD_HOROSCOPER_SKILL_LEVEL] = 1;
			break;
		case LAND_ITEM_SPECIAL2_ADD_SMALL_ATTACK_RATIO:			// 命中率增加
			data->data[ITEM_INFO_ADD_ATTACK_RATIO] = SMALL_ATTATCK_RATE;
			data->data[ITEM_INFO_HITCHANCE] += SMALL_ATTATCK_RATE;
			break;
		case LAND_ITEM_SPECIAL2_ADD_MIDDLE_ATTACK_RATIO:		// 命中率增加
			data->data[ITEM_INFO_ADD_ATTACK_RATIO] = MIDDLE_ATTACK_RATE;
			data->data[ITEM_INFO_HITCHANCE] += MIDDLE_ATTACK_RATE;
			break;
		case LAND_ITEM_SPECIAL2_ADD_LARGE_ATTACK_RATIO:			// 命中率增加
			data->data[ITEM_INFO_ADD_ATTACK_RATIO] = LARGE_ATTACK_RATE;
			data->data[ITEM_INFO_HITCHANCE] += LARGE_ATTACK_RATE;
			break;
		}

		switch ( item_ran->Land.Type1 )
		{
		case LAND_ITEM_DATATYPE1_ADD_MAX_HP:			// 增加生命上限
			data->data[ITEM_INFO_ADD_MAX_HP] = item_ran->Land.Data1;
			break;
		case LAND_ITEM_DATATYPE1_ADD_MAX_MP:			// 增加魔法上限
			data->data[ITEM_INFO_ADD_MAX_MP] = item_ran->Land.Data1;
			break;
		case LAND_ITEM_DATATYPE1_ADD_DEF:				// 增加防禦力
			data->data[ITEM_INFO_BASEDEF] += item_ran->Land.Data1;
			data->data[ITEM_INFO_ADD_DEF] = item_ran->Land.Data1;
			break;
		case LAND_ITEM_DATATYPE1_ENHANCE_DEF:			// 加強防禦
			data->data[ITEM_INFO_BASEDEF] = 
				( data->data[ITEM_INFO_BASEDEF] * ( 100 + item_ran->Land.Data1) ) / 100;

			data->data[ITEM_INFO_ADD_ENHANCE_DEF] = item_ran->Land.Data1;
			break;
		case LAND_ITEM_DATATYPE1_ADD_RESIST:			// 增加抵抗
			data->data[ITEM_INFO_ADD_RESIST] = item_ran->Land.Data1;
			break;
		default:
			break;
		}

		switch ( item_ran->Land.Type2 )
		{
		case LAND_ITEM_DATATYPE2_ADD_ATT:				// 增加攻擊力
			data->data[ITEM_INFO_ADD_ATT] = item_ran->Land.Data2;
			data->data[ITEM_INFO_BASEATT] = data->data[ITEM_INFO_ADD_ATT];
			break;
		case LAND_ITEM_DATATYPE2_ENHANCE_ATT:			// 加強攻擊
			data->data[ITEM_INFO_BASEATT] = 
				( data->data[ITEM_INFO_BASEATT] * ( 100 + item_ran->Land.Data2 ) ) / 100;
			data->data[ITEM_INFO_ENHANCE_ATT] = item_ran->Land.Data2;
			break;
		case LAND_ITEM_DATATYPE2_ADD_MAGIC_HURT:		// 增加魔法傷害
			data->data[ITEM_INFO_ADD_MAGIC_HURT] = item_ran->Land.Data2;
			break;
		case LAND_ITEM_DATATYPE2_ADD_SPECIAL_HURT:		// 增加特殊傷害
			data->data[ITEM_INFO_ADD_SPECIAL_HURT] = item_ran->Land.Data2;
			break;
		}

		break;
	case ITEM_TYPE_SEA_NORMAL:
		break;
	case ITEM_TYPE_TREASURE_MAP:
		break;
	case ITEM_TYPE_SEA_EXPENDABLE:
		break;
	case ITEM_TYPE_SEA_SAILOR:
		break;
	case ITEM_TYPE_MONSTER:
		break;
	case ITEM_TYPE_DRUG:
		// 增加力量
		data->data[ITEM_INFO_ADD_STR] = item_bs->Drug.AddStr;

		// 增加直覺
		data->data[ITEM_INFO_ADD_INS] = item_bs->Drug.AddIns;
		
		// 增加智慧
		data->data[ITEM_INFO_ADD_WIT] = item_bs->Drug.AddWit;

		// 增加運氣
		data->data[ITEM_INFO_ADD_LUCKY] = item_bs->Drug.AddLuck;

		// 生命值回復
		data->data[ITEM_INFO_ADD_HP] = item_bs->Drug.ResHpRate;

		// 魔力值回復
		data->data[ITEM_INFO_ADD_MP] = item_bs->Drug.ResMpRate;

		break;
	}

	data->data[ITEM_INFO_GENERAL_ONLY]  = item_bs->User & USER_CAREER_GENERAL;
	data->data[ITEM_INFO_SWORDER_ONLY]  = item_bs->User & USER_CAREER_SWORDER;
	data->data[ITEM_INFO_THIEF_ONLY]    = item_bs->User & USER_CAREER_THIEF;
	data->data[ITEM_INFO_TRADER_ONLY]   = item_bs->User & USER_CAREER_TRADER;
	data->data[ITEM_INFO_EXPLORER_ONLY] = item_bs->User & USER_CAREER_EXPLORER;
	data->data[ITEM_INFO_CLERIC_ONLY]   = item_bs->User & USER_CAREER_CLERIC;
	data->data[ITEM_INFO_HOROSCOPER_ONLY] = item_bs->User & USER_CAREER_HOROSCOPER;

	return TTN_OK;
}