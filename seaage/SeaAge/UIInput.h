/*----------------------------------------------------------------*\
|
|	UIInput.h	
|
|	Zhang Zhaohui	2003/4/11
|
|	��J��ܮ�..
|
|	Copyright (c) Rays Multimedia. All rights reserved.
\*----------------------------------------------------------------*/



#pragma once

#include "mainfun.h"
#include "ClientMain.h"
#include "qqedit.h"
#include "CRange.h"

//////////////////////////////////////////////////////////////////////////
enum INPUT_ENUM
{
	INPUT_EVENT			= 60000,
	INPUT_MAX_FRAMES	= 15,

	INPUT_BK_ID			= 0,
	INPUT_OK_ID			= 1,
	INPUT_CANCEL_ID		= 2,
	INPUT_SCROLL_BN_ID	= 3,
	INPUT_MAX_ID		= 4,
	INPUT_MIN_ID		= 5,

	INPUT_BK_FRAME		= 0,
	INPUT_SCROLL_FRAME	= 1,
	INPUT_OK_FRAME		= 3,
	INPUT_CANCEL_FRAME	= 6,
	INPUT_MIN_FRAME		= 9,
	INPUT_MAX_FRAME		= 12,

	INPUT_TEXT_X		= 80,
	INPUT_TEXT_Y		= 57,
	INPUT_TEXT_W		= 200,
	INPUT_TEXT_H		= 24,
	INPUT_TEXT_SIZE		= 11,
	
	INPUT_SCROLL_X		= 79,
	INPUT_SCROLL_MAX_X	= 254,

	INPUT_TITLE_X		= 36,
	INPUT_TITLE_Y		= 24,
};



//////////////////////////////////////////////////////////////////////////

typedef VOID (*FNIPTCB)( LONG id, LONG result, LONG param );

typedef struct tagUI_INPUT
{
	LONG	x;			// ��J�إ��W���y��
	LONG	y;			// ��J�إk�W���y��
	LONG	max;		// �̤j��
	LONG	min;		// �̤p��
	LONG	font_size;	// �r��j�p
	FNIPTCB pfunc;		// �^�ը��
	CHAR	title[40];
} UI_INPUT, *LPUI_INPUT;

typedef struct tagUI_INPUT_DATA
{
	LONG		active_id;
	LONG		hilight_id;
	LONG		curr_data;		// ��e��
	LONG		param;			// �Ѽ�
	UI_TEXT		*ptext;			// ��J��
} UI_INPUT_DATA, *LPUI_INPUT_DATA;

//////////////////////////////////////////////////////////////////////////

INT  init_ui_input( VOID );
VOID active_ui_input( INT active );
VOID free_ui_input( VOID );

VOID refresh_ui_input( VOID );
VOID redraw_ui_input( BMP* bitmap );
LONG handle_ui_input( UINT msg, WPARAM wparam, LPARAM lparam );

LONG ui_input_show( LPUI_INPUT input, LONG param );

