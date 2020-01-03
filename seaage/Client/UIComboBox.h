/*
**	UIComboBox.h
**	ComboBox functions header
**
**	Jack, 2002/06/17.
**
**	modified by ZZH 2002.7.17
*/
#ifndef _UICOMBOBOX_H_
#define _UICOMBOBOX_H_

#include "mainfun.h"
#include "CRange.h"


//DEFINE ------------------------------------------------------------------
typedef enum COMBOBOX_ENUMS
{
	COMBOBOX_EVENT					= 19999,

	COMBOBOX_ID_EDIT_BG				= 310,	//編輯框
	COMBOBOX_ID_EDIT_BUTTON			= 311,	

	COMBOBOX_ID_BG					= 340,	//下拉部分
	COMBOBOX_ID_UP					= 341,
	COMBOBOX_ID_DOWN				= 342,
	COMBOBOX_ID_BUTTON				= 343,
	COMBOBOX_ID_TEXT				= 0XFF00,


	COMBOBOX_DEFAULT_EDIT_HEIGHT	= 25,
	COMBOBOX_DEFAULT_WIDTH			= 100,
	COMBOBOX_DEFAULT_LINES			= 6,

	COMBOBOX_ENABLE					= 1,		//允許顯示下拉框
	COMBOBOX_DISABLE				= 0,		//禁止顯示下拉框

	COMBOBOX_OPEN_ENABLE			= 1,		//下拉框打開
	COMBOBOX_OPEN_DISABLE			= 0,		//下拉框關閉

	COMBOBOX_STYLE_DOWN				= 60,		//向下展開
	COMBOBOX_STYLE_UP				= 70,		//向上展開

	COMBOBOX_FRAME_EDIT0			= 0,		//編輯框按鈕正常狀態
	COMBOBOX_FRAME_EDIT1			= 1,		//編輯框按鈕按下狀態
	COMBOBOX_FRAME_UP0				= 2,		//正常狀態的按鈕
	COMBOBOX_FRAME_UP1				= 3,		//按下狀態的按鈕
	COMBOBOX_FRAME_DOWN0			= 0,		//正常狀態的按鈕
	COMBOBOX_FRAME_DOWN1			= 1,		//按下狀態的按鈕
	COMBOBOX_FRAME_BUTTON			= 4,		//滑塊

	COMBOBOX_FONT_12				= 12,
	COMBOBOX_FONT_16				= 16,
};





//STURCT------------------------------------------------------------
typedef struct tagCBB_ITEM CBB_ITEM, *LPCBB_ITEM;
typedef struct tagCOMBOBOX_LIST COMBOBOX_LIST, *LPCOMBOBOX_LIST;


struct tagCBB_ITEM
{
	USTR		line[56];				//下拉框中的內容
	SLONG		data;					//下拉框中的內容所對應的數值
	CBB_ITEM	*last, *next;			//雙鏈表指針
};



typedef struct tagCOMBOBOX
{
	LPCBB_ITEM		item;					//內容
	LPCBB_ITEM		default_item;			//默認項
	LPCBB_ITEM		active_item;			//鼠標所指項
	LPCBB_ITEM		result_item;			//選中的項
	LPCBB_ITEM		first_item;				//第一個顯示的項
	SLONG			item_count;				//項的總數
	SLONG			x;		
	SLONG			y;
	SLONG			edit_height;			//編輯框的寬度
	SLONG			line_height;			//下拉框中單行的寬度
	SLONG			width;					//寬度
	SLONG			show_lines;				//下拉框中的行數
	SLONG			enable;					//是否顯示下拉框
	SLONG			open_enable;			//是否顯示下拉狀態
	SLONG			style;					//下拉框的顯示方式(向下向上)
	SLONG			edit_frame;				//編輯框按鈕圖檔索引
	SLONG			up_frame;				//下拉框向上按鈕圖檔索引
	SLONG			down_frame;				//下拉框向下按鈕圖檔索引
	SLONG			b_frame;				//滑塊的圖檔索引
	SLONG			b_y;						//滑塊的當前位置 (相對位置)
	SLONG			b_max_y;				//滑塊的最大位置 (相對位置)
	SLONG			b_min_y;				//滑塊的最小位置 (相對位置)
	DWORD			ntext_color;			//文字顏色
	DWORD			atext_color;			//鼠標指向的文字顏色
	DWORD			stext_color;			//選中文字顏色
	DWORD			font_size;				// 文字大小
}COMBOBOX, *LPCOMBOBOX;



struct tagCOMBOBOX_LIST
{
	COMBOBOX		*item;				//指向一個下拉框
	COMBOBOX_LIST	*last, *next;		//雙鏈表指針
};



//FUNCTION----------------------------------------------------------
int			init_combobox(void);
void		redraw_combobox(void *vbitmap);
SLONG		handle_combobox(UINT message, WPARAM wParam, LPARAM lParam);
void		free_combobox(void);
//
void		clear_combobox_list( void);
//
LPCOMBOBOX	create_combobox(void);
void		destroy_combobox(LPCOMBOBOX lpcbb);
//
int			add_combobox_to_list(LPCOMBOBOX lpcbb);
SLONG		find_combobox_index( LPCOMBOBOX lpcbb);
void		del_combobox_from_list( SLONG cbb_index);

void		clear_combobox_item( LPCOMBOBOX lpcbb);
void		set_combobox_default( LPCOMBOBOX lpcbb, SLONG item_index);
SLONG		get_combobox_default( LPCOMBOBOX lpcbb);
int			add_combobox_item(LPCOMBOBOX lpcbb, USTR *line, SLONG data);
void		del_combobox_item( LPCOMBOBOX lpcbb, SLONG item_index);
int			find_combobox_item_str( LPCOMBOBOX lpcbb, USTR *line);
int			find_combobox_item_data( LPCOMBOBOX lpcbb, SLONG data);
int			count_combobox_item( LPCOMBOBOX lpcbb);


void		set_combobox_pos(LPCOMBOBOX lpcbb, SLONG x, SLONG y);
void		set_combobox_edit_wh(LPCOMBOBOX lpcbb, SLONG w, SLONG h);
void		set_combobox_style(LPCOMBOBOX lpcbb, SLONG combobox_style);	
void		set_combobox_lines(LPCOMBOBOX lpcbb, SLONG lines);
void		set_combobox_enable(LPCOMBOBOX lpcbb, SLONG combobox_enable);
void		set_combobox_font_size( LPCOMBOBOX lpcbb, SLONG font_size );

USTR		*get_combobox_str(LPCOMBOBOX lpcbb);
SLONG		get_combobox_data(LPCOMBOBOX lpcbb);


#endif//_UICOMBOBOX_H_
