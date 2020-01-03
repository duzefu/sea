/*
**	UIComboBox.cpp
**	ComboBox functions
**
**	Jack, 2002/06/17.
*/
#include "mainfun.h"
#include "ClientMain.h"
#include "UIComboBox.h"



//宏(巨集)定義------------------------------------------------------------
#define MAX_COMBOBOX_FRAME	8



//變量聲明----------------------------------------------------------------
LPCOMBOBOX_LIST g_pcbb_list		= NULL;						//下拉框鏈表
CAKE_FRAME_ANI  *combobox_cfa	= NULL;						//下拉框中用到的 cak 檔
CAKE_FRAME      *combobox_cf[MAX_COMBOBOX_FRAME];			//下拉框 cak 檔中的 frame
LPCOMBOBOX		g_pcbb			= NULL;
SLONG			drag_flag = 0;

PIXEL			color_bg, color_line;
SLONG			alpha_shadow1, alpha_shadow2, alpha_shadow3, alpha_shadow4;

//局部函數聲明------------------------------------------------------------
void	draw_combobox( LPCOMBOBOX lpcbb, BMP *bitmap);
void	free_combobox_item( LPCBB_ITEM lpcbb_item);
SLONG	get_combobox_item_index( LPCOMBOBOX lpcbb, LPCBB_ITEM lpcbb_item);


LPCBB_ITEM		get_combobox_item( LPCOMBOBOX lpcbb, SLONG index);
LPCOMBOBOX		get_combobox( SLONG index);
LPCOMBOBOX_LIST get_combobox_list( LPCOMBOBOX lpcbb);


//FUNCTIONS---------------------------------------------------------------

//初始化下拉框
int init_combobox( void)
{
	SLONG	result, frames, i;
	
	if( g_pcbb_list != NULL)
		free_combobox();
	
    set_data_file(packed_menu_file);
	result = load_cake_frame_ani_from_file((USTR*)"menu\\combobox.cak", &combobox_cfa);
	if( TTN_OK != result)
		return -1;

	frames = count_cake_frames( combobox_cfa);

	if( frames > MAX_COMBOBOX_FRAME)
		frames = MAX_COMBOBOX_FRAME;

	for( i = 0; i < frames; i++)
	{
		combobox_cf[i] = get_specify_cake_frame_ani(combobox_cfa, i)->cake_frame;
	}
	color_bg		= rgb2hi( 215, 215, 215);
	color_line		= rgb2hi(  51,   1,  15);
	alpha_shadow1	= 70;
	alpha_shadow2	= 120;
	alpha_shadow3	= 180;
	alpha_shadow3	= 210;

	return 0;
}


//建立一個下拉框
LPCOMBOBOX create_combobox(void)
{
	LPCOMBOBOX lpcbb = NULL;

	lpcbb = (LPCOMBOBOX)malloc( sizeof( COMBOBOX));
	if(NULL == lpcbb)
	{
		sprintf((char*)print_rec, "ERROR: Can not alloc memory for combox.");
		log_error(1, (char*)print_rec);
		return NULL;
	}

	lpcbb->item 			= NULL;
	lpcbb->default_item  	= NULL;
	lpcbb->active_item  	= NULL;
	lpcbb->result_item  	= NULL;
	lpcbb->first_item  		= NULL;
	lpcbb->item_count  		= 0;
	lpcbb->x  				= 0;
	lpcbb->y  				= 0;
	lpcbb->edit_height  	= COMBOBOX_DEFAULT_EDIT_HEIGHT;
	lpcbb->width  			= COMBOBOX_DEFAULT_WIDTH;
	lpcbb->show_lines  		= COMBOBOX_DEFAULT_LINES;
	lpcbb->enable  			= COMBOBOX_ENABLE;
	lpcbb->open_enable  	= FALSE;
	lpcbb->style  			= COMBOBOX_STYLE_DOWN;
	lpcbb->edit_frame  		= COMBOBOX_FRAME_EDIT0;
	lpcbb->up_frame  		= COMBOBOX_FRAME_UP0;
    lpcbb->down_frame  		= COMBOBOX_FRAME_DOWN0;
    lpcbb->b_frame  		= COMBOBOX_FRAME_BUTTON;
	lpcbb->line_height		= lpcbb->edit_height - 6;
	lpcbb->b_min_y			= lpcbb->edit_height + combobox_cf[lpcbb->up_frame]->rle->h-1;
	lpcbb->b_max_y			= lpcbb->edit_height + lpcbb->line_height * lpcbb->show_lines 
				- combobox_cf[lpcbb->down_frame]->rle->h - combobox_cf[lpcbb->b_frame]->rle->h+1;
	lpcbb->b_y				= lpcbb->b_min_y;
	lpcbb->font_size		= COMBOBOX_FONT_16;


//	lpcbb->atext_color = RGB( 63, 255, 63);
//	lpcbb->ntext_color = RGB( 63, 63, 255);
//	lpcbb->stext_color = RGB( 63, 255, 255);
	lpcbb->ntext_color = 0x004040ff;
	lpcbb->stext_color = 0x00000000;
	lpcbb->atext_color = 0x0040ff40;

	return lpcbb;

}



//顯示下拉框
void redraw_combobox( void *vbitmap)
{
	BMP *bitmap = (BMP*)vbitmap;
	LPCOMBOBOX_LIST	p;
	LPCOMBOBOX		t;
	LPCBB_ITEM		lpcbb_item;
	SLONG			c;
//	SLONG			frame, event, id;
//	SLONG			x1, y1, x2, y2, w, h;
//	CAKE_FRAME		*cf;
//	SSTR			line[80];



	if( NULL == combobox_cfa)
	{
		sprintf((char*)print_rec, "ERROR: Combobox need Init.");
		log_error(1, (char*)print_rec);
		return;
	}

	p = g_pcbb_list;
	c = 0;

	while( p)
	{
		t = p->item;
		lpcbb_item = NULL;


		if( COMBOBOX_DISABLE == t->enable || t == g_pcbb)
		{
			p = p->next;
			c++;
			continue;
		}

		draw_combobox( t, bitmap);


		p = p->next;
		c++;
	}
	draw_combobox( g_pcbb, bitmap);
}


//處理消息
SLONG handle_combobox( UINT message, WPARAM wParam, LPARAM lParam)
{
	SLONG   mouse_x, mouse_y, event_type, event_id;
	SLONG	a, b, c, d, e;
	UCHR    ch;


	//滾論消息
	if(WM_MOUSEWHEEL == message)
	{
		if( NULL == g_pcbb || COMBOBOX_OPEN_ENABLE != g_pcbb->open_enable)
			return -1;
		
		ch = read_mouse_key();
		reset_mouse_key();
		switch(ch)
		{
		case MS_Forward:
			if( g_pcbb->first_item && NULL != g_pcbb->first_item->last)
				g_pcbb->first_item = g_pcbb->first_item->last;
			else if( NULL == g_pcbb->first_item)
				g_pcbb->first_item = g_pcbb->default_item;
			
			
			if( g_pcbb->item_count > g_pcbb->show_lines)
				g_pcbb->b_y =  g_pcbb->b_min_y + (g_pcbb->b_max_y - g_pcbb->b_min_y)*
				get_combobox_item_index(g_pcbb,g_pcbb->first_item)/
				(g_pcbb->item_count - g_pcbb->show_lines);
			
			if( g_pcbb->b_y < g_pcbb->b_min_y)
				g_pcbb->b_y = g_pcbb->b_min_y;
			break;
		case MS_Backward:
			if( g_pcbb->first_item && 
				g_pcbb->item_count - get_combobox_item_index(g_pcbb,g_pcbb->first_item) 
				> g_pcbb->show_lines )
				g_pcbb->first_item = g_pcbb->first_item->next;
			else if( NULL == g_pcbb->first_item)
				g_pcbb->first_item = g_pcbb->default_item;
			
			if( g_pcbb->item_count > g_pcbb->show_lines)
				g_pcbb->b_y = (g_pcbb->b_max_y - g_pcbb->b_min_y)*
				get_combobox_item_index(g_pcbb,g_pcbb->first_item)/
				(g_pcbb->item_count - g_pcbb->show_lines) + 
				g_pcbb->b_min_y;
			
			if( g_pcbb->b_y > g_pcbb->b_max_y)
				g_pcbb->b_y = g_pcbb->b_max_y;
			break;
		default:
			break;
		}
		return 0;
	}



	mouse_x = GET_X_LPARAM(lParam);
	mouse_y = GET_Y_LPARAM(lParam);
	game_range.mapping( mouse_x, mouse_y, &event_type, &event_id);

	if( COMBOBOX_EVENT != event_type )
	{
		if( g_pcbb && ( WM_LBUTTONDOWN == message
							  ||WM_RBUTTONDOWN  == message))
		{
			g_pcbb->open_enable = COMBOBOX_OPEN_DISABLE;
			g_pcbb->edit_frame = COMBOBOX_FRAME_EDIT0;
			g_pcbb = NULL;
		}
		return -1;
	}
	else
	{
		if( find_combobox_index(g_pcbb) != (event_id>>16) &&
			( WM_LBUTTONDOWN == message||WM_RBUTTONDOWN  == message))
		{
			if( NULL != g_pcbb)
			{
				g_pcbb->open_enable = COMBOBOX_OPEN_DISABLE;
				g_pcbb->edit_frame = COMBOBOX_FRAME_EDIT0;
			}
			g_pcbb = get_combobox( event_id>>16);
			if( NULL == g_pcbb)
			{
				return -1;
			}
		}
	}
	event_id = event_id &0x0000ffff;

	switch( message)
	{
		case WM_MOUSEMOVE:
			if( COMBOBOX_ID_TEXT == (event_id&0xff00))
			{
				if( NULL != g_pcbb->first_item)
					g_pcbb->active_item = get_combobox_item(g_pcbb, 
						get_combobox_item_index(g_pcbb, g_pcbb->first_item) + event_id&0xff);

			}
			else
			{
				if( wParam & MK_LBUTTON) //Drag
				{
					if( 1 == drag_flag && g_pcbb->item_count > g_pcbb->show_lines)
					{
						g_pcbb->b_y = mouse_y - g_pcbb->y - 
								combobox_cf[COMBOBOX_FRAME_BUTTON]->rle->h/2;

						if( COMBOBOX_STYLE_DOWN != g_pcbb->style)
						{
							g_pcbb->b_y += g_pcbb->line_height * g_pcbb->show_lines 
								+ g_pcbb->edit_height;
						}
						if( g_pcbb->b_y < g_pcbb->b_min_y)
							g_pcbb->b_y = g_pcbb->b_min_y;
						else if( g_pcbb->b_y > g_pcbb->b_max_y)
							g_pcbb->b_y = g_pcbb->b_max_y;


						a = g_pcbb->show_lines;
						b = g_pcbb->item_count;
						c = g_pcbb->b_max_y;
						d = g_pcbb->b_min_y;
						e = g_pcbb->b_y;
						g_pcbb->first_item = get_combobox_item(g_pcbb, (b-a)*(e-d)/(c-d));

					}
				}

			}
			break;
		case WM_LBUTTONDOWN:
		case WM_RBUTTONDOWN:
			switch( event_id)
			{
				case COMBOBOX_ID_EDIT_BUTTON:
					if(g_pcbb->open_enable != COMBOBOX_OPEN_ENABLE)
					{
						g_pcbb->open_enable	= COMBOBOX_OPEN_ENABLE;
						g_pcbb->enable		= COMBOBOX_ENABLE;
						g_pcbb->edit_frame	= COMBOBOX_FRAME_EDIT1;
					}
					else
					{
						g_pcbb->open_enable	= COMBOBOX_OPEN_DISABLE;
						g_pcbb->enable		= COMBOBOX_ENABLE;
						g_pcbb->edit_frame	= COMBOBOX_FRAME_EDIT0;
					}
					break;
				case COMBOBOX_ID_UP:
					if( g_pcbb->first_item && NULL != g_pcbb->first_item->last)
						g_pcbb->first_item = g_pcbb->first_item->last;
					else if( NULL == g_pcbb->first_item)
						g_pcbb->first_item = g_pcbb->default_item;
					g_pcbb->up_frame = COMBOBOX_FRAME_UP1;
					

					if( g_pcbb->item_count > g_pcbb->show_lines)
						g_pcbb->b_y =  g_pcbb->b_min_y + (g_pcbb->b_max_y - g_pcbb->b_min_y)*
										get_combobox_item_index(g_pcbb,g_pcbb->first_item)/
										(g_pcbb->item_count - g_pcbb->show_lines);

					if( g_pcbb->b_y < g_pcbb->b_min_y)
						g_pcbb->b_y = g_pcbb->b_min_y;

					break;
				case COMBOBOX_ID_DOWN:
					if( g_pcbb->first_item && 
						g_pcbb->item_count - get_combobox_item_index(g_pcbb,g_pcbb->first_item) 
								> g_pcbb->show_lines )
							g_pcbb->first_item = g_pcbb->first_item->next;
					else if( NULL == g_pcbb->first_item)
						g_pcbb->first_item = g_pcbb->default_item;
					g_pcbb->down_frame = COMBOBOX_FRAME_DOWN1;
					
					if( g_pcbb->item_count > g_pcbb->show_lines)
						g_pcbb->b_y = (g_pcbb->b_max_y - g_pcbb->b_min_y)*
										get_combobox_item_index(g_pcbb,g_pcbb->first_item)/
										(g_pcbb->item_count - g_pcbb->show_lines) + 
										g_pcbb->b_min_y;

					if( g_pcbb->b_y > g_pcbb->b_max_y)
						g_pcbb->b_y = g_pcbb->b_max_y;
					break;
				case COMBOBOX_ID_BUTTON:
					drag_flag = 1;
					break;
				default:
					break;
			}
			break;
		case WM_LBUTTONUP:
		case WM_RBUTTONUP:
			if( NULL != g_pcbb)
			{
				g_pcbb->down_frame = COMBOBOX_FRAME_DOWN0;
				g_pcbb->up_frame   = COMBOBOX_FRAME_UP0;
			}
			drag_flag = 0;
			if( COMBOBOX_ID_TEXT == (event_id&0xff00))
			{
				if( NULL != g_pcbb->first_item)
					g_pcbb->result_item = get_combobox_item(g_pcbb, 
						get_combobox_item_index(g_pcbb, g_pcbb->first_item) + event_id&0xff);
				
				
				g_pcbb->open_enable  = COMBOBOX_OPEN_DISABLE;
				g_pcbb->edit_frame	= COMBOBOX_FRAME_EDIT0;
				g_pcbb->active_item	= NULL;


				if( get_combobox_item_index(g_pcbb, g_pcbb->result_item) 
						<= g_pcbb->item_count - g_pcbb->show_lines)
					g_pcbb->first_item = g_pcbb->result_item;
				else
				{
					if( g_pcbb->item_count >= g_pcbb->show_lines)
						g_pcbb->first_item = get_combobox_item( g_pcbb, 
									g_pcbb->item_count - g_pcbb->show_lines);
					else
						g_pcbb->first_item = g_pcbb->item;

				}
			}
			break;

		default:
			break;
	}
	return 0;
}


//釋放所有的下拉框所佔的記憶體
void free_combobox( void)
{
	
	clear_combobox_list();
	
	if( NULL != combobox_cfa)
	{
		destroy_cake_frame_ani( &combobox_cfa);
	}
	g_pcbb_list = NULL;
}


//釋放下拉框所佔的記憶體
void destroy_combobox( LPCOMBOBOX lpcbb)
{
	if( NULL != lpcbb)
	{
		free_combobox_item( lpcbb->item);

		free( lpcbb);
	}
}


//釋放下拉框中的項所佔的記憶體
void	free_combobox_item( LPCBB_ITEM lpcbb_item)
{
	LPCBB_ITEM p;
	LPCBB_ITEM n;

	p = lpcbb_item;

	while( p)
	{
		n = p;
		p = p->next;
		free( n);
	}
}


//根據下拉框的指針獲得下拉框在鏈表中的位置
LPCOMBOBOX_LIST get_combobox_list( LPCOMBOBOX lpcbb)
{
	LPCOMBOBOX_LIST p;

	p = g_pcbb_list;
	
	while( p)
	{
		if( p->item == lpcbb)
			return p;
		p = p->next;
	}
	return NULL;
}


//添加一個下拉框到下拉框鏈表
int add_combobox_to_list(LPCOMBOBOX lpcbb)
{
	LPCOMBOBOX_LIST *p;
	LPCOMBOBOX_LIST t;

	if( !lpcbb)
	{
		sprintf( (char*)print_rec, "ERROR: ERROR: Combobox need Init.");
		log_error( 1, (char*)print_rec);
		return -1;
	}
	
	t = g_pcbb_list;
	p = &g_pcbb_list;

	while( *p)
	{
		t = *p;
		p = &(*p)->next;
	}


	(*p) = (LPCOMBOBOX_LIST)malloc(sizeof(COMBOBOX_LIST ));
	if( !(*p))
	{
		sprintf( (char*)print_rec, "ERROR: Can not alloc memory for LPCOMBOBOX");
		log_error( 1, (char*)print_rec);
		return -1;
	}

	(*p)->item = lpcbb;
	(*p)->last = t;
	(*p)->next = NULL;

	return 0;
}


//從下拉框鏈表中移除
void del_combobox_from_list( SLONG index)
{
	LPCOMBOBOX_LIST p;
	LPCOMBOBOX		lpcbb;
	lpcbb = get_combobox( index);
	if( NULL != lpcbb)
	{
		p = get_combobox_list( lpcbb);
		if( NULL == p)
			return;
		
		if( NULL == p->last)
		{
			g_pcbb_list = p->next;
			if( NULL != p->next)
				p->next->last = NULL;
		}
		else if( NULL == p->next)
			p->last->next = NULL;
		else
		{
			p->last->next = p->next;
			p->next->last = p->last;
		}

		free( p);
	}
}


//向指定的下拉框中添加一項
int add_combobox_item( LPCOMBOBOX lpcbb, USTR *line, SLONG data)
{
	LPCBB_ITEM *p;
	LPCBB_ITEM t;

	p = &lpcbb->item;
	t = lpcbb->item;

	while( *p)
	{
		if( 0 == strcmp((const char*)(*p)->line, (const char*)line))
			return 1;
		t = *p;
		p = &(*p)->next;
	}

	(*p) = (LPCBB_ITEM)malloc( sizeof( CBB_ITEM));
	if( !(*p))
	{
		sprintf( (char*)print_rec, "ERROR: Can not alloc memory for LPCBB_ITEM");
		log_error( 1, (char*)print_rec);
		return -1;
	}


	if( NULL != line && strlen( (const char*)line) < 56)
		strcpy( (char*)(*p)->line, (const char*)line);
	else
	{
		(*p)->line[0] = '\0';
	}
	
	(*p)->data = data;
	(*p)->last = t;
	(*p)->next = NULL;
	lpcbb->item_count++;
	if( lpcbb->item_count >= 1)
	{
		lpcbb->default_item = lpcbb->item;
		lpcbb->first_item = lpcbb->default_item;
	}
	return 0;
}


//移除下拉框的一項
void del_combobox_item( LPCOMBOBOX lpcbb, SLONG item_index)
{
	LPCBB_ITEM p;

	if( NULL != lpcbb)
	{
		p = get_combobox_item( lpcbb, item_index);

		if( NULL != p)
		{
			if( NULL == p->last)
			{
				lpcbb->item = p->next;
				if( NULL !=p->next)
					p->next->last = NULL;
			}
			else if( NULL == p->next)
			{
				p->last->next = NULL;
			}
			else
			{
				p->last->next = p->next;
				p->next->last = p->last;
			}
			free( p);
			lpcbb->item_count--;										
		}
	}
}


//設定左上角位置
void set_combobox_pos( LPCOMBOBOX lpcbb, SLONG x, SLONG y)
{
	if( NULL != lpcbb)
	{
		lpcbb->x = x;
		lpcbb->y = y;
	}
}

//設定下拉框的寬和行高
void set_combobox_edit_wh( LPCOMBOBOX lpcbb, SLONG w, SLONG h)
{
	if( NULL != lpcbb)
	{
		lpcbb->edit_height	= h;
		lpcbb->width		= w;
		if( COMBOBOX_DEFAULT_EDIT_HEIGHT != lpcbb->edit_height)
		{
			lpcbb->line_height		= lpcbb->edit_height - 6;
			lpcbb->b_min_y = lpcbb->edit_height + combobox_cf[lpcbb->up_frame]->rle->h-1;
			lpcbb->b_max_y = lpcbb->edit_height + lpcbb->line_height * lpcbb->show_lines
				- combobox_cf[lpcbb->down_frame]->rle->h - combobox_cf[lpcbb->b_frame]->rle->h+1;
			
		}
	}


}


//設定向上打開還是向下打開
void set_combobox_style( LPCOMBOBOX lpcbb, SLONG style)
{
	if( NULL != lpcbb)
	{
		lpcbb->style = style;
	}
}

//設定是否顯示
void set_combobox_enable( LPCOMBOBOX lpcbb, SLONG combobox_enable)
{
	if( NULL != lpcbb)
	{
		lpcbb->enable = combobox_enable;
	}
}

// 設定文字大小
void set_combobox_font_size( LPCOMBOBOX lpcbb, SLONG font_size )
{
	if ( lpcbb )
	{
		switch ( font_size )
		{
		case COMBOBOX_FONT_12:
			lpcbb->font_size = COMBOBOX_FONT_12;
			break;
		case COMBOBOX_FONT_16:
			lpcbb->font_size = COMBOBOX_FONT_16;
			break;
		}
	}
}

//獲得下拉框中的項的索引值
SLONG get_combobox_item_index( LPCOMBOBOX lpcbb, LPCBB_ITEM lpcbb_item)
{
	LPCBB_ITEM p;
	SLONG result = 0;

	p = lpcbb->item;
	while( p)
	{
		if( p == lpcbb_item)
			return result;
		p = p->next;
		result++;
	}

	return -1;
}


//獲得下拉框的索引值
SLONG find_combobox_index( LPCOMBOBOX lpcbb)
{
	LPCOMBOBOX_LIST p;
	SLONG result = 0;

	p = g_pcbb_list;

	while( p)
	{
		if( p->item == lpcbb)
			return result;
		p = p->next;
		result++;
	}

	return -1;
}

//根據索引值獲得指定的項
LPCBB_ITEM get_combobox_item( LPCOMBOBOX lpcbb, SLONG index)
{
	LPCBB_ITEM	p;
	SLONG		c = 0;

	p = lpcbb->item;
	while( p)
	{
		if( c == index)
			return p;
		c++;
		p = p->next;
	}
	return NULL;
}

//根據索引值獲得指定的下拉框
LPCOMBOBOX get_combobox( SLONG index)
{
	SLONG c = 0;
	LPCOMBOBOX_LIST p;
	p = g_pcbb_list;

	while( p)
	{
		if( c == index)
			return p->item;
		c++;
		p = p->next;
	}

	return NULL;
}


//獲得下拉框的子符串數據
USTR *get_combobox_str(LPCOMBOBOX lpcbb)
{
	if( NULL != lpcbb->result_item)
		return (USTR*)lpcbb->result_item->line;
	else if( NULL != lpcbb->default_item)
		return (USTR*)lpcbb->default_item->line;
	else
		return NULL;
}


//獲得下拉框的數據
SLONG get_combobox_data(LPCOMBOBOX lpcbb)
{
	if( NULL != lpcbb->result_item)
		return lpcbb->result_item->data;
	else if( NULL != lpcbb->default_item)
		return lpcbb->default_item->data;
	else
		return -1;
}


//設置顯示行數
void set_combobox_lines(LPCOMBOBOX lpcbb, SLONG lines)
{
	if( NULL != lpcbb)
	{
		if( lines <= 0)
			return;

		lpcbb->show_lines = lines;
		if( COMBOBOX_DEFAULT_LINES != lpcbb->show_lines)
		{
			lpcbb->b_min_y = lpcbb->edit_height + combobox_cf[lpcbb->up_frame]->rle->h-1;
			lpcbb->b_max_y = lpcbb->edit_height + lpcbb->line_height * lpcbb->show_lines 
				- combobox_cf[lpcbb->down_frame]->rle->h - combobox_cf[lpcbb->b_frame]->rle->h+1;
		}
	}
}

//清空下拉框的項
void clear_combobox_item( LPCOMBOBOX lpcbb)
{
	if( NULL != lpcbb)
	{
		free_combobox_item( lpcbb->item);
		lpcbb->item = NULL;
		lpcbb->item_count = 0;
	}
}


void	draw_combobox( LPCOMBOBOX lpcbb, BMP *bitmap)
{
	SLONG			x1, y1, x2, y2, w, h, d, c;
	LPCOMBOBOX		t;
	LPCBB_ITEM		lpcbb_item;

	if( -1 == ( c = find_combobox_index(lpcbb)))
		return;

	t = lpcbb;
	h = t->line_height;
	//畫編輯框------------------
	put_bar( t->x, t->y, t->width, t->edit_height, color_bg, bitmap);
	
	x1 = t->x+1;
	x2 = t->width - 2;
	put_line( x1, t->y, t->x+t->width-2, t->y, color_line, bitmap);
	alpha_put_bar( x1, t->y-1, x2, 1, color_line, bitmap, alpha_shadow1);
	alpha_put_bar( x1, t->y+1, x2, 1, color_line, bitmap, alpha_shadow1);
	
	y1 = t->y  + t->edit_height - 1;
	put_line( x1, y1, t->x+t->width-2, y1, color_line, bitmap);
	alpha_put_bar( x1, y1-1, x2, 1, color_line, bitmap, alpha_shadow1);
	alpha_put_bar( x1, y1+1, x2, 1, color_line, bitmap, alpha_shadow1);
	
	y1 = t->y + 1;
	y2 = t->y + t->edit_height - 2;
	x1 = t->x;
	w = t->edit_height - 2;
	put_line( x1, y1, x1, y2, color_line, bitmap);
	alpha_put_bar( x1-1, y1, 1, w, color_line, bitmap, alpha_shadow1);
	alpha_put_bar( x1+1, y1, 1, w, color_line, bitmap, alpha_shadow1);
	
	x1 = x1 + t->width - 2 - combobox_cf[t->edit_frame]->rle->w;
	put_line( x1, y1, x1, y2, color_line, bitmap);
	alpha_put_bar( x1-1, y1, 1, w, color_line, bitmap, alpha_shadow1);
	alpha_put_bar( x1+1, y1, 1, w, color_line, bitmap, alpha_shadow1);
	
	x1 = x1 + combobox_cf[t->edit_frame]->rle->w + 1;
	put_line( x1, y1, x1, y2, color_line, bitmap);
	alpha_put_bar( x1-1, y1, 1, w, color_line, bitmap, alpha_shadow1);
	alpha_put_bar( x1+1, y1, 1, w, color_line, bitmap, alpha_shadow1);
	
	alpha_put_bar( t->x, t->y, 1, 1, color_line, bitmap, alpha_shadow3);
	alpha_put_bar( t->x, t->y+t->edit_height-1, 1, 1, color_line, bitmap, alpha_shadow1);
	alpha_put_bar( t->x + t->width-1, t->y, 1, 1, color_line, bitmap, alpha_shadow3);
	alpha_put_bar( t->x + t->width-1, t->y+t->edit_height-1, 1, 1, color_line, bitmap, alpha_shadow2);
	
	game_range.add( t->x, t->y, t->width, t->edit_height, 
		COMBOBOX_EVENT, COMBOBOX_ID_EDIT_BG | (c<<16));
	
	
	//畫編輯框按鈕--------------
	x1 = t->x + t->width - combobox_cf[t->edit_frame]->rle->w-1;
	y1 = t->y+1;
	// put_rle( x1, y1, combobox_cf[t->edit_frame]->rle, bitmap);
	scale_put_rle( x1, y1, combobox_cf[t->edit_frame]->rle->w, t->edit_height, 
					combobox_cf[t->edit_frame]->rle, bitmap );
	game_range.add( x1, y1, 
		combobox_cf[t->edit_frame]->rle->w, t->edit_height,
		COMBOBOX_EVENT,
		COMBOBOX_ID_EDIT_BUTTON | (c<<16));
	
	
	//顯示編輯框文字------------
	lpcbb_item = t->result_item?t->result_item:t->default_item;
	set_word_color(0, true2hi(t->ntext_color));
	if( lpcbb_item)		
	{
		switch ( lpcbb->font_size )
		{
		case COMBOBOX_FONT_16:
			print16(t->x + 4, t->y + 5, (USTR*)lpcbb_item->line, PEST_PUT, bitmap);
			break;
		case COMBOBOX_FONT_12:
			print12(t->x + 2, t->y + 3, (USTR*)lpcbb_item->line, PEST_PUT, bitmap);
			break;
		}
	}
	set_word_color(0, SYSTEM_WHITE);	

	if( COMBOBOX_OPEN_ENABLE != t->open_enable)
	{
		return;
	}
	
	//畫下拉框------------------
	x1 = t->x + 1;
	x2 = t->width-2;
	if( COMBOBOX_STYLE_DOWN == t->style)
	{
		y1 = t->y + t->edit_height;
		y2 = h * t->show_lines-1;
	}
	else
	{
		y1 = t->y - h * t->show_lines;
		y2 = t->y - y1 - 1;
	}

	alpha_put_bar( x1, y1, x2, y2,	color_bg, bitmap, alpha_shadow3);
	alpha_put_bar( x1, y1, x2, 1, color_line, bitmap, alpha_shadow1);
	alpha_put_bar( x1, y1, 1, y2, color_line, bitmap, alpha_shadow1);
	alpha_put_bar( x1, y1+y2, x2, 1, color_line, bitmap, alpha_shadow1);
	alpha_put_bar( x1+x2-1, y1, 1, y2, color_line, bitmap, alpha_shadow1);
	
	x1 = x1 + t->width - 4 - combobox_cf[t->edit_frame]->rle->w;
	alpha_put_bar( x1, y1, 3, y2, color_line, bitmap, alpha_shadow1);
	
	game_range.add( t->x+1, y1, x2, y2, COMBOBOX_EVENT, COMBOBOX_ID_BG | (c << 16));
	
	//畫下拉框滾動條按鈕--------
	if( COMBOBOX_STYLE_DOWN == t->style)
	{
		y1 = t->y + t->edit_height;
	}
	else
	{
		y1 = t->y - h*t->show_lines;
	}
	x1 = t->x + t->width - combobox_cf[t->up_frame]->rle->w-1;
	scale_put_rle( x1, y1, combobox_cf[t->up_frame]->rle->w, h, 
					combobox_cf[t->up_frame]->rle, bitmap );

	game_range.add( x1, y1, combobox_cf[t->up_frame]->rle->w, h,
		COMBOBOX_EVENT, COMBOBOX_ID_UP | (c<<16));

	if( COMBOBOX_STYLE_DOWN == t->style)
	{
		y1 = y1 + h * t->show_lines - h;//combobox_cf[t->down_frame]->rle->h;
	}
	else
	{
		y1 = t->y - h -1; //combobox_cf[t->down_frame]->rle->h - 1;
	}
	
	// put_rle( x1, y1, combobox_cf[t->down_frame]->rle, bitmap);
	scale_put_rle( x1, y1, combobox_cf[t->down_frame]->rle->w, h, 
					combobox_cf[t->down_frame]->rle, bitmap );

	game_range.add( x1, y1, combobox_cf[t->down_frame]->rle->w, h,
		COMBOBOX_EVENT, COMBOBOX_ID_DOWN | (c<<16));
	
	//畫下拉框滾動條滑塊--------
	y1 = t->b_y;
	x1++;
	if( y1 > t->b_max_y) y1 = t->b_max_y;
	if( y1 < t->b_min_y) y1 = t->b_min_y;
	
	if( COMBOBOX_STYLE_DOWN == t->style)
	{
		put_rle(x1, y1+t->y, combobox_cf[t->b_frame]->rle, bitmap);
		game_range.add( x1, y1+t->y, combobox_cf[t->b_frame]->rle->w,
			combobox_cf[t->b_frame]->rle->h,
			COMBOBOX_EVENT, COMBOBOX_ID_BUTTON | (c<<16));
	}
	else
	{
		y2 = t->y - h * t->show_lines - t->edit_height + y1;
		put_rle(x1, y2, combobox_cf[t->b_frame]->rle, bitmap);
		game_range.add( x1, y2, combobox_cf[t->b_frame]->rle->w,
			combobox_cf[t->b_frame]->rle->h,
			COMBOBOX_EVENT, COMBOBOX_ID_BUTTON | (c<<16));
	}
	
	//顯示下拉框文字------------
	lpcbb_item = t->item;
	x1 = t->x + 1;
	if( COMBOBOX_STYLE_DOWN == t->style)
	{
		y1 = t->y + t->edit_height - 2;
	}
	else
	{
		y1 = t->y - h*t->show_lines;
	}
	
	if( NULL != t->first_item)
	{
		while( lpcbb_item != t->first_item)
		{
			if( NULL == lpcbb_item)
			{
				lpcbb_item = t->item;
				t->first_item = lpcbb_item;
				break;
			}
			lpcbb_item = lpcbb_item->next;
		}
	}
	
	d = 0;
	w = t->width - 5 - combobox_cf[t->edit_frame]->rle->w;
	while( lpcbb_item)
	{
		if( lpcbb_item == t->active_item)
		{
			set_word_color(0, true2hi(t->atext_color));
			alpha_put_bar( x1, y1+2, w, h, true2hi(t->ntext_color), bitmap, alpha_shadow3);
		}
		else if( lpcbb_item == t->result_item )
			set_word_color(0, true2hi(t->stext_color));
		else if( NULL == t->result_item && lpcbb_item == t->default_item)
			set_word_color(0, true2hi(t->stext_color));
		else
			set_word_color(0, true2hi(t->ntext_color));

		switch ( lpcbb->font_size )
		{
		case COMBOBOX_FONT_16:
			print16( x1 + 3, y1 + 3, (USTR*)lpcbb_item->line, PEST_PUT, bitmap);
			break;
		case COMBOBOX_FONT_12:
			print12( x1 + 3, y1 + 3, (USTR*)lpcbb_item->line, PEST_PUT, bitmap);
			break;
		}

		game_range.add( x1, y1+2, w, h, COMBOBOX_EVENT, COMBOBOX_ID_TEXT | (c<<16) | d);
		d++;
		if( d >= t->show_lines)
		{
			break;
		}
		y1 += h;
		lpcbb_item = lpcbb_item->next;
	}
	set_word_color( 0, SYSTEM_WHITE);
}


//設置默認的顯示項
void set_combobox_default( LPCOMBOBOX lpcbb, SLONG item_index)
{
	LPCBB_ITEM p;
	if( NULL != lpcbb)
	{
		if( NULL == ( p = get_combobox_item( lpcbb, item_index)))
			return;
		lpcbb->default_item = p;
		lpcbb->result_item = p;
	}
}

//獲得當前默認項的索引值
SLONG get_combobox_default( LPCOMBOBOX lpcbb)
{
	if( NULL != lpcbb)
	{
		if( NULL != lpcbb->result_item)
		{
			return get_combobox_item_index( lpcbb, lpcbb->result_item);
		}
		else if( NULL != lpcbb->default_item)
		{
			return get_combobox_item_index( lpcbb, lpcbb->default_item);
		}
	}
	return -1;
}


//根據子符串返回下拉框項的索引值
int find_combobox_item_str( LPCOMBOBOX lpcbb, USTR *line)
{
	LPCBB_ITEM p;
	int			index;

	if( !lpcbb || !line)
		return -1;

	p = lpcbb->item;
	index = 0;

	while( p)
	{
		if( 0 == strcmp((const char*)line, (const char*)p->line))
			return index;
		p = p->next;
		index ++;
	}
	return -1;
}


//根據數值返回下拉框項的索引值
int find_combobox_item_data( LPCOMBOBOX lpcbb, SLONG data)
{
	LPCBB_ITEM p;
	int			index;

	if( !lpcbb)
		return -1;

	p = lpcbb->item;
	index = 0;

	while( p)
	{
		if( data == p->data)
			return index;
		p = p->next;
		index ++;
	}
	return -1;
}


//返回下拉框的總項數
int count_combobox_item( LPCOMBOBOX lpcbb)
{
	if( NULL != lpcbb)
	{
		return lpcbb->item_count;
	}
	return -1;
}

//清空下拉框鏈表
void clear_combobox_list( void)
{

	LPCOMBOBOX_LIST p;
	LPCOMBOBOX_LIST t;

	p = g_pcbb_list;

	while( p)
	{
		t = p;
		p = p->next;
		free(t);
	}
	g_pcbb_list = NULL;
}