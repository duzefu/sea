/*----------------------------------------------------------------*\
|
|	UIInput.cpp	
|
|	Zhang Zhaohui	2003/4/11
|
|	輸入對話框.
|
|	Copyright (c) Rays Multimedia. All rights reserved.
\*----------------------------------------------------------------*/


#include "UIInput.h"

//////////////////////////////////////////////////////////////////////////

CONST CHAR INPUT_CAK[] = "menu\\uiinput.cak";

//////////////////////////////////////////////////////////////////////////

CAKE_FRAME_ANI	*input_cfa = NULL;
CAKE_FRAME		*input_cf[INPUT_MAX_FRAMES];

UI_INPUT_DATA	input_data;
UI_INPUT		ui_input;
BOOL			show_input = FALSE;
//////////////////////////////////////////////////////////////////////////

INT  init_ui_input( VOID )
{
	SLONG result;

	if ( input_cfa )
		return TTN_NOT_OK;

	// 讀取界面
	set_data_file( packed_menu_file );
	result = load_cake_frame_ani_from_file( (USTR*)INPUT_CAK, &input_cfa );
	if ( result != TTN_OK )
		return TTN_NOT_OK;
	for ( SLONG i = 0; i < INPUT_MAX_FRAMES; i++ )
		input_cf[i] = get_specify_cake_frame_ani( input_cfa, i )->cake_frame;
	
	
	// 數字輸入框
	input_data.ptext = te_create( 0, 0, INPUT_TEXT_W, INPUT_TEXT_H, INPUT_TEXT_SIZE );
	if ( !input_data.ptext )
	{
		free_ui_input( );
		return TTN_NOT_OK;
	}

	te_set_single_line( input_data.ptext, TRUE );
	te_set_number_only( input_data.ptext, TRUE );
	te_set_active( input_data.ptext, FALSE );

	return TTN_OK;
}


VOID active_ui_input( INT active )
{
}


VOID free_ui_input( VOID )
{
	if ( input_data.ptext )
	{
		te_destroy( input_data.ptext );
		input_data.ptext = NULL;
	}
	if ( input_cfa )
		destroy_cake_frame_ani( &input_cfa );

	memset( input_cf, 0, sizeof(CAKE_FRAME*) * INPUT_MAX_FRAMES );

}



VOID refresh_ui_input( VOID )
{
}


VOID redraw_ui_input( BMP* bitmap )
{
	SLONG x, y, id, event;
    CAKE_FRAME	*cf;
	SLONG d1, d2, frame;
	CHAR buf[20];
    DOUBLE d;
//	SLONG min_x, max_x;
	if ( !show_input )
		return;

	event = INPUT_EVENT;

    // 背景 ---------------------------------------
	id = INPUT_BK_ID;
	frame = INPUT_BK_FRAME;
	cf = input_cf[frame];
	x = ui_input.x + cf->frame_rx;
	y = ui_input.y + cf->frame_ry;

	put_rle( x, y, cf->rle, bitmap );
	game_range.add( x, y, cf->rle->w, cf->rle->h, event, id );


    // 取消 ----------------------------------------
	id = INPUT_CANCEL_ID;
	frame = INPUT_CANCEL_FRAME;
	if ( input_data.active_id == id )
		frame += 2;
	else if ( input_data.hilight_id  == id )
		frame++;
	cf = input_cf[frame];
	x = ui_input.x + cf->frame_rx;
	y = ui_input.y + cf->frame_ry;
	put_rle( x, y, cf->rle, bitmap );
	game_range.add( x, y, cf->rle->w, cf->rle->h, event, id );
	
	// 滑塊 ---------------------------------------
	id = INPUT_SCROLL_BN_ID;
	frame = INPUT_SCROLL_FRAME;
	if ( input_data.hilight_id == id )
		frame++;
	cf = input_cf[frame];
	y = ui_input.y + cf->frame_ry;
	d1 = ui_input.max - ui_input.min;
	if ( d1 <= 0 )
		x = ui_input.x + cf->frame_rx;
	else
	{
		d2 = ( INPUT_SCROLL_MAX_X - cf->rle->w/2 ) - INPUT_SCROLL_X - cf->rle->w/2;
        d = (DOUBLE)d2 / (DOUBLE)d1;
	
		x = (SLONG)( (DOUBLE)( input_data.curr_data - ui_input.min ) * d );
		x = MAX( x, 0 );
		x = MIN( x, d2 );
		x += ui_input.x + INPUT_SCROLL_X;
	}
	put_rle( x, y, cf->rle, bitmap );
	game_range.add( x, y, cf->rle->w, cf->rle->h, event, id );

	// 確定 ----------------------------------------
	id = INPUT_OK_ID;
	frame = INPUT_OK_FRAME;
	if ( input_data.active_id == id )
		frame += 2;
	else if ( input_data.hilight_id  == id )
		frame++;
	cf = input_cf[frame];
	x = ui_input.x + cf->frame_rx;
	y = ui_input.y + cf->frame_ry;
	put_rle( x, y, cf->rle, bitmap );
	game_range.add( x, y, cf->rle->w, cf->rle->h, event, id );


	// MIN ---------------------------------------
	id = INPUT_MIN_ID;
	frame = INPUT_MIN_FRAME;
	if ( input_data.active_id == id )
		frame += 2;
	else if ( input_data.hilight_id  == id )
		frame++;
	cf = input_cf[frame];
	x = ui_input.x + cf->frame_rx;
	y = ui_input.y + cf->frame_ry;
	put_rle( x, y, cf->rle, bitmap );
	game_range.add( x, y, cf->rle->w, cf->rle->h, event, id );

	// MAX --------------------------------------
	id = INPUT_MAX_ID;
	frame = INPUT_MAX_FRAME;
	if ( input_data.active_id == id )
		frame += 2;
	else if ( input_data.hilight_id  == id )
		frame++;
	cf = input_cf[frame];
	x = ui_input.x + cf->frame_rx;
	y = ui_input.y + cf->frame_ry;
	put_rle( x, y, cf->rle, bitmap );
	game_range.add( x, y, cf->rle->w, cf->rle->h, event, id );

	// Title -----------------------------------
	x = INPUT_TITLE_X;
	y = INPUT_TITLE_Y;
	switch ( ui_input.font_size )
	{
	case 12:
		print12( x, y, ui_input.title, PEST_PUT, bitmap );
		break;
	case 16:
		print16( x, y, ui_input.title, PEST_PUT, bitmap );
		break;
	}

	// Input -----------------------------------
	d1 = te_get_number( input_data.ptext );
	d1 = MAX( ui_input.min, d1 );
	d1 = MIN( ui_input.max, d1 );
	input_data.curr_data = d1;
	_ultoa( input_data.curr_data, buf, 10 );
	te_set_text( input_data.ptext, buf );
	redraw_te( input_data.ptext, bitmap );
}


LONG handle_ui_input( UINT msg, WPARAM wparam, LPARAM lparam )
{
	LONG event, id;
	LONG result = 1;
    DOUBLE d;
	CHAR buf[20];

	switch ( msg )
	{
	case WM_MOUSEMOVE:
		game_range.mapping( LOWORD(lparam), HIWORD(lparam), &event, &id );
		if ( event != INPUT_EVENT )
			break;

		if ( input_data.active_id == INPUT_SCROLL_BN_ID )
		{
			int max_x, min_x;
			INT x = GET_X_LPARAM( lparam ) - ui_input.x;

			max_x = INPUT_SCROLL_MAX_X - input_cf[INPUT_SCROLL_FRAME]->rle->w/2;
			min_x = INPUT_SCROLL_X + input_cf[INPUT_SCROLL_FRAME]->rle->w/2;
			
			if ( x < min_x )
				x = min_x;
			if ( x > max_x )
				x = max_x;

            d = (DOUBLE)( x - min_x ) / (DOUBLE)( max_x - min_x );
            input_data.curr_data = (LONG)( (DOUBLE)( ui_input.max - ui_input.min ) * d);
			//_ultoa( input_data.curr_data, buf, 10 );
			sprintf( buf, "%d", input_data.curr_data );
			te_set_text( input_data.ptext, buf );
		}
		else
			input_data.hilight_id = id;
		result = 0;
		break;
	case WM_LBUTTONDOWN:
		game_range.mapping( LOWORD(lparam), HIWORD(lparam), &event, &id );
		if ( event != INPUT_EVENT )
			break;
		input_data.active_id = id;
		result = 0;
		break;
	case WM_LBUTTONUP:
		game_range.mapping( LOWORD(lparam), HIWORD(lparam), &event, &id );
        if ( event == RT_MAP )
        {
            event = INPUT_EVENT;
            id = INPUT_CANCEL_ID;
        }
		if ( event != INPUT_EVENT )
			break;
		if ( input_data.active_id == id )
		{
			switch ( id )
			{
			case INPUT_OK_ID:
				if ( ui_input.pfunc )
					ui_input.pfunc( INPUT_OK_ID, input_data.curr_data, input_data.param );
				show_input = FALSE;
				break;
			case INPUT_CANCEL_ID:
				if ( ui_input.pfunc )
					ui_input.pfunc( INPUT_CANCEL_ID, 0, input_data.param );
				show_input = FALSE;
				break;
			case INPUT_MAX_ID:
				input_data.curr_data = ui_input.max;
				_ultoa( input_data.curr_data, buf, 10 );
				te_set_text( input_data.ptext, buf );
				break;
			case INPUT_MIN_ID:
				input_data.curr_data = ui_input.min;
		 		_ultoa( input_data.curr_data, buf, 10 );
				te_set_text( input_data.ptext, buf );
				break;
			}
		}
		input_data.active_id = 0;
		result = 0;
		break;
	}

	return result;
}



LONG ui_input_show( LPUI_INPUT input, LONG param )
{
	char buf[20];
	if ( !input )
		return TTN_NOT_OK;

	ui_input = *input;
	
	input_data.active_id = 0;
	input_data.hilight_id = 0;
	input_data.curr_data = ui_input.max;
	input_data.param = param;

//	_ultoa( input_data.curr_data, buf, 10 );
	sprintf( buf, "%d", input_data.curr_data );
	te_set_text( input_data.ptext, buf );
	te_set_xy( input_data.ptext, ui_input.x + INPUT_TEXT_X, 
					ui_input.y + INPUT_TEXT_Y );
	te_set_wh( input_data.ptext, INPUT_TEXT_W, INPUT_TEXT_H );
	te_set_font_size( input_data.ptext, (UI_EDIT_FONT)ui_input.font_size );
	te_set_active( input_data.ptext, TRUE );
	//te_set_read_only( input_data.ptext, TRUE );

	show_input = TRUE;

	return TTN_OK;
}



