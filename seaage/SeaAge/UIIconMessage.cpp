/*
**	UIIconMessage.cpp 
**	icon control message functions.
**
**	Jack, 2003.3.18.
**  Modify Zhang Zhaohui, 2003.3.28
*/
#include "MainFun.h"
#include "ClientMain.h"
#include "CRange.h"
#include "UIIconMessage.h"
#include "Team.h"

/************************************************************************/
/* Define                                                               */
/************************************************************************/
#define IM_PARAM_NONE	0x00000000
#define IM_PARAM_STR	0X00000001
#define IM_PARAM_INT	0X00000002


/************************************************************************/
/* Const                                                                */
/************************************************************************/
// 最大消息模板數
CONST DWORD IM_MAX_MSG_TMP = 100; 

CONST CHAR IM_ICON[] = "menu\\sysmsg.cak";
CONST CHAR IM_INI[] = "data\\sysmsg.ini";
CONST DWORD IM_SX = 0;
CONST DWORD IM_SY = 400;
CONST DWORD IM_YL = 20;
CONST DWORD IM_ABMP_W = 400;
CONST DWORD IM_DALPHA = 16;
CONST DWORD IM_FLASH_RATE = 0x8;

/************************************************************************/
/* Globals                                                              */
/************************************************************************/
MSG_DEFINE		*im_def = NULL;
ICONMSG_NODE	*im = NULL;
CAKE_FRAME_ANI	*im_cfa = NULL;
CAKE_FRAME		*im_cf[IM_FRAMES];
DWORD			im_count = 0;
ABMP			*im_abitmap = NULL;


/************************************************************************/
/* Static Functions                                                     */
/************************************************************************/
static INT	add_im( ICONMSG_NODE* node );
static INT  del_im( INT index );
static ICONMSG_NODE	*get_im( INT index );
static VOID draw_im( SLONG x, SLONG y, ICONMSG_NODE* p, BMP* bitmap );
static VOID im_proc( DWORD event, DWORD action, ICONMSG_PARA * para );

/************************************************************************/
/* Functions                                                            */
/************************************************************************/

INT		init_iconmsg( VOID )
{
	USTR  line[1024];
	SLONG result, file_size, buf_index = 0;
	USTR *file_buf = NULL;
	UINT len;
	SLONG ini_index = 0;
	SLONG line_index = 0;

	im_abitmap = create_abitmap( IM_ABMP_W, IM_YL );

	im_def = ( MSG_DEFINE*)GlobalAlloc( GPTR,  sizeof( MSG_DEFINE ) * IM_MAX_MSG_TMP );
	im = ( ICONMSG_NODE*)GlobalAlloc( GPTR, sizeof( ICONMSG_NODE) * IM_MAX );

	if ( !im_abitmap || !im || !im_def )
	{
		log_error( 1, "Error: No enough memory for iconmsg" );
		free_iconmsg();
		return TTN_NOT_OK;
	}

	// 讀取圖標
	set_data_file( packed_menu_file );
	result = load_cake_frame_ani_from_file( (UCHR*)IM_ICON, &im_cfa );
	if ( result != TTN_OK )
		return TTN_NOT_OK;
	im_cf[IM_IMG_YES] = get_specify_cake_frame_ani( im_cfa, 0 )->cake_frame;
	im_cf[IM_IMG_NO] = get_specify_cake_frame_ani( im_cfa, 0 )->cake_frame;
	im_cf[IM_IMG_INFO] = get_specify_cake_frame_ani( im_cfa, 0 )->cake_frame;

	
	// 讀取消息文字
	set_data_file( packed_data_file );
	file_size = load_file_to_buffer( (UCHAR*)IM_INI, &file_buf );
	if ( file_size < 0 )
	{
		free_iconmsg();
		return TTN_NOT_OK;
	}
	result = get_buffer_line( (CHAR*)file_buf, &buf_index, file_size, (CHAR*)line, 1024 );
	while( result == TTN_OK )
	{
		len = strlen( ( CHAR* )line );
		if ( len > 0 && line[0] != ';' )
		{
			line_index = 0;
			ini_index = get_buffer_number( line, &line_index );
			if ( ini_index >= 0 && ini_index <= IM_MAX_MSG_TMP )
			{
				im_def[ini_index].para_type = (DWORD)get_buffer_number( line, &line_index );
				strcpy( im_def[ini_index].text, 
							(const char*)get_buffer_string( line, &line_index ) );
			}
		}
		result = get_buffer_line( (CHAR*)file_buf, &buf_index, file_size, (CHAR*)line, 1024 );
	}

	// 初始化消息鏈
	for( SLONG i = 0; i < IM_MAX; i++ )
		im[i].index = -1;

	if ( file_buf )
		free( file_buf );

	return TTN_OK;
}

VOID	active_iconmsg( INT active )
{
}

VOID	free_iconmsg( VOID )
{
	if ( im_cfa )
		destroy_cake_frame_ani( &im_cfa );

	if ( im )
	{
		GlobalFree( im );
		im = NULL;
	}

	if ( im_def )
	{
		GlobalFree( im_def );
		im_def = NULL;
	}

	if ( im_abitmap )
		destroy_abitmap( &im_abitmap );

}


//
// 添加一個消息
//		id :   對應 ini 文件的索引
//		type:  IM_HINT 或 IM_YESNO
//		para:  參數，用於回調函數
//		event: 用戶設定的參數，用於回調函數
INT		add_iconmsg( DWORD id, DWORD type, ICONMSG_PARA* para, DWORD event )
{
	enum { BUF_SIZE = 200 };

	CHAR text_buf[BUF_SIZE];
	DWORD para_type, str_count, int_count;
	ICONMSG_NODE node;
	MSG_DEFINE *data;
	DWORD tmp_para[IM_MAX_PARA];
	DWORD para_index;

	if ( id < 0 || id >= IM_MAX_MSG_TMP )
		return TTN_NOT_OK;
	
	data = &im_def[id];

	if ( strlen( (const char*)data->text ) == 0 )
		return TTN_NOT_OK;

	para_type = data->para_type;

	str_count = 0;
	int_count = 0;
	para_index = 0;

	// 根據 para_type 的值初始化參數表 tmp_para
	while ( para_type != 0 )
	{
		switch ( para_type & 0x0000000f )
		{
		case IM_PARAM_STR:
			tmp_para[para_index] = (DWORD)para->str[str_count];
			str_count++;
			break;
		case IM_PARAM_INT:
			tmp_para[para_index] = (DWORD)para->num[int_count];
			int_count++;
			break;
		case IM_PARAM_NONE:
			break;
		default:
			break;
		}
		para_type = para_type >> 4;
		para_index++;
		if ( para_index >= IM_MAX_PARA )
			break;
	}

	wsprintf( text_buf, data->text, tmp_para[0], tmp_para[1], tmp_para[2], tmp_para[3] );

	lstrcpyn( node.content.msg, text_buf, IM_MSGLEN );
	node.para = *para;
	node.event = event;
	node.type = type;

	node.content.start_time = timeGetTime();
	node.content.state = IMS_FLASH;
	node.content.flash = 0;
	
	add_im( &node );


	return TTN_OK;
}

VOID	refresh_iconmsg( VOID )
{
	DWORD time;
	DWORD i;

	time = timeGetTime();

	for ( i = 0; i < IM_MAX; i++ )
		if ( im[i].index != -1 )
		{
			switch ( im[i].content.state )
			{
			case IMS_FLASH:
				im[i].content.flash++;
				if ( time - im[i].content.start_time > IMT_FLASH )
				{
					im[i].content.state = IMS_NORMAL;
					im[i].content.start_time = time;
				}
				break;
			case IMS_NORMAL:
				if ( time - im[i].content.start_time > IMT_NORMAL )
				{
					im[i].content.state = IMS_DISAPPEAR;
					im[i].content.start_time = time;
					im[i].content.alpha = 255;
				}
				break;
			case IMS_DISAPPEAR:
				im[i].content.alpha -= IM_DALPHA;
				if ( im[i].content.alpha < 0 )
					im[i].content.alpha = 0;
				if ( im[i].content.alpha == 0 )
					del_im( im[i].index );
				break;
			default:
				break;
			}
		}
}

LONG	handle_iconmsg( UINT msg, WPARAM wparam, LPARAM lparam )
{
	LONG result = 1;
	SLONG event, id;
	ICONMSG_NODE *p_node = NULL;

	switch ( msg )
	{
	case WM_LBUTTONDOWN:
		game_range.mapping( LOWORD(lparam) , HIWORD(lparam), &event, &id );
		if ( event == IM_EVENT )
		{
			p_node = get_im( HIWORD(id) );
			im_proc( p_node->event, LOWORD( id ), &p_node->para );
			p_node->content.state = IMS_DISAPPEAR;
			p_node->content.alpha = 255;
			result = 0;
		}
		break;
	}

	return result;
}

VOID	redraw_iconmsg( BMP *bitmap )
{
	static ww = IM_ABMP_W * SIZEOFPIXEL;
	SLONG y;
	DWORD i, j;
	ICONMSG_NODE *p_node;


	for ( i = 0; i < im_count; i ++ )
	{
		p_node = get_im( i );
		if ( !p_node )
			break;

		y = IM_SY - IM_YL * i;
		
		// 正在逐漸消失的消息條
		if ( p_node->content.state == IMS_DISAPPEAR )
		{
			for ( j = 0; j < IM_YL; j++ )
				memset( &im_abitmap->line[j][ww], p_node->content.alpha, IM_ABMP_W );

			get_bitmap( IM_SX, y, IM_ABMP_W, IM_YL, (BMP*)im_abitmap, bitmap );
			draw_im( 0, 0, p_node, (BMP*)im_abitmap );
			put_abitmap( IM_SX, y, im_abitmap, bitmap );
			continue;
		}
		else 
		{
			// 是否閃爍
			if ( p_node->content.state == IMS_FLASH &&
				 p_node->content.flash & IM_FLASH_RATE )
				continue;

			draw_im( IM_SX, y, p_node, bitmap );
		}
	}
}


/************************************************************************/
/* Local Functions                                                      */
/************************************************************************/
// 添加一個節點
INT	add_im( ICONMSG_NODE* node )
{
	INT i;
	INT result = -1;
	INT tmp;

	if ( !node || ! im )
		return -1;

	// 所有節點的索引值加 1
	for ( i = 0; i < IM_MAX; i++ )
		if ( im[i].index != -1 )
			im[i].index ++;

	for ( i = 0; i < IM_MAX; i++ )
	{
		if ( im[i].index == -1 )
		{
			memcpy( &im[i], node, sizeof( ICONMSG_NODE ) );
			im[i].index = 0;
			result = i;
			im_count++;
			break;
		}
		// 記住最後一個節點
		if ( im[i].index == ( IM_MAX ) )
			tmp = i;
	}

	// 消息鏈滿了, 刪除最後一個
	if ( i == IM_MAX )
	{
		i = tmp;
		memcpy( &im[i], node, sizeof( ICONMSG_NODE ) );
		im[i].index = 0;
		result = i;
	}

	return i;
}


// 刪除一個節點
INT	del_im( INT index)
{
	SLONG i;

	if ( !im || index < 0 || index >= IM_MAX )
		return -1;

	for ( i = 0; i < IM_MAX; i++ )
	{
		if ( im[i].index == index )
		{
			im[i].index = -1;
			im[i].content.state = IMS_FLASH;
			break;
		}
	}

	for ( i = 0; i < IM_MAX; i++ )
		if ( im[i].index > index )
			im[i].index--;

	im_count--;

	return TTN_OK;
}


// 獲得索引所對應的節點
ICONMSG_NODE	*get_im( INT index )
{
	SLONG i;

	if ( !im || index < 0 || index > IM_MAX )
		return NULL;

	for ( i = 0; i < IM_MAX; i++ )
		if ( im[i].index == index )
			return &im[i];

	return NULL;
}

// 畫一條消息
VOID draw_im( SLONG x, SLONG y, ICONMSG_NODE* p, BMP* bitmap )
{
	RLE *rle;
	SLONG id;

	if ( p->type == IM_HINT )
	{
		id = MAKELONG( IMA_YES, p->index );

		rle = im_cf[IM_IMG_INFO]->rle;
		put_rle( x, y, rle, bitmap );
		
		game_range.add( x, y, rle->w, rle->h, IM_EVENT, id );
		
		x += im_cf[IM_IMG_INFO]->rle->w;
	}
	else if ( p->type == IM_YESNO )
	{
		id = MAKELONG( IMA_YES, p->index );

		rle = im_cf[IM_IMG_YES]->rle;
		put_rle( x, y, rle, bitmap );

		game_range.add( x, y, rle->w, rle->h, IM_EVENT, id );

		x += im_cf[IM_IMG_YES]->rle->w;

		id = MAKELONG( IMA_NO, p->index );

		rle = im_cf[IM_IMG_NO]->rle;
		put_rle( x, y, rle, bitmap );

		game_range.add( x, y, rle->w, rle->h , IM_EVENT, id );
		x += im_cf[IM_IMG_NO]->rle->w;
	}
	print12( x, y, p->content.msg, PEST_PUT, bitmap );
}


VOID im_proc( DWORD event, DWORD action, ICONMSG_PARA * para )
{
    switch ( event )
    {
    case TEAM_WANT_JOIN:
        if ( action == IMA_YES )
            team_agree_join( para->str[0], para->str[1] );
        break;
    case TEAM_TARGET_FULL:
        break;
    case TEAM_ALREADY_IN_TEAM:
        break;
    case TEAM_JOIN:
        break;
    case TEAM_EXIT:
        break;
    case TEAM_KICK:
        break;
    }
}