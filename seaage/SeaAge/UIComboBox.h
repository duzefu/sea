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

	COMBOBOX_ID_EDIT_BG				= 310,	//�s���
	COMBOBOX_ID_EDIT_BUTTON			= 311,	

	COMBOBOX_ID_BG					= 340,	//�U�Գ���
	COMBOBOX_ID_UP					= 341,
	COMBOBOX_ID_DOWN				= 342,
	COMBOBOX_ID_BUTTON				= 343,
	COMBOBOX_ID_TEXT				= 0XFF00,


	COMBOBOX_DEFAULT_EDIT_HEIGHT	= 25,
	COMBOBOX_DEFAULT_WIDTH			= 100,
	COMBOBOX_DEFAULT_LINES			= 6,

	COMBOBOX_ENABLE					= 1,		//���\��ܤU�Ԯ�
	COMBOBOX_DISABLE				= 0,		//�T����ܤU�Ԯ�

	COMBOBOX_OPEN_ENABLE			= 1,		//�U�Ԯإ��}
	COMBOBOX_OPEN_DISABLE			= 0,		//�U�Ԯ�����

	COMBOBOX_STYLE_DOWN				= 60,		//�V�U�i�}
	COMBOBOX_STYLE_UP				= 70,		//�V�W�i�}

	COMBOBOX_FRAME_EDIT0			= 0,		//�s��ث��s���`���A
	COMBOBOX_FRAME_EDIT1			= 1,		//�s��ث��s���U���A
	COMBOBOX_FRAME_UP0				= 2,		//���`���A�����s
	COMBOBOX_FRAME_UP1				= 3,		//���U���A�����s
	COMBOBOX_FRAME_DOWN0			= 0,		//���`���A�����s
	COMBOBOX_FRAME_DOWN1			= 1,		//���U���A�����s
	COMBOBOX_FRAME_BUTTON			= 4,		//�ƶ�

	COMBOBOX_FONT_12				= 12,
	COMBOBOX_FONT_16				= 16,
};





//STURCT------------------------------------------------------------
typedef struct tagCBB_ITEM CBB_ITEM, *LPCBB_ITEM;
typedef struct tagCOMBOBOX_LIST COMBOBOX_LIST, *LPCOMBOBOX_LIST;


struct tagCBB_ITEM
{
	USTR		line[56];				//�U�Ԯؤ������e
	SLONG		data;					//�U�Ԯؤ������e�ҹ������ƭ�
	CBB_ITEM	*last, *next;			//�������w
};



typedef struct tagCOMBOBOX
{
	LPCBB_ITEM		item;					//���e
	LPCBB_ITEM		default_item;			//�q�{��
	LPCBB_ITEM		active_item;			//���Щҫ���
	LPCBB_ITEM		result_item;			//�襤����
	LPCBB_ITEM		first_item;				//�Ĥ@����ܪ���
	SLONG			item_count;				//�����`��
	SLONG			x;		
	SLONG			y;
	SLONG			edit_height;			//�s��ت��e��
	SLONG			line_height;			//�U�Ԯؤ���檺�e��
	SLONG			width;					//�e��
	SLONG			show_lines;				//�U�Ԯؤ������
	SLONG			enable;					//�O�_��ܤU�Ԯ�
	SLONG			open_enable;			//�O�_��ܤU�Ԫ��A
	SLONG			style;					//�U�Ԯت���ܤ覡(�V�U�V�W)
	SLONG			edit_frame;				//�s��ث��s���ɯ���
	SLONG			up_frame;				//�U�ԮئV�W���s���ɯ���
	SLONG			down_frame;				//�U�ԮئV�U���s���ɯ���
	SLONG			b_frame;				//�ƶ������ɯ���
	SLONG			b_y;						//�ƶ�����e��m (�۹��m)
	SLONG			b_max_y;				//�ƶ����̤j��m (�۹��m)
	SLONG			b_min_y;				//�ƶ����̤p��m (�۹��m)
	DWORD			ntext_color;			//��r�C��
	DWORD			atext_color;			//���Ы��V����r�C��
	DWORD			stext_color;			//�襤��r�C��
	DWORD			font_size;				// ��r�j�p
}COMBOBOX, *LPCOMBOBOX;



struct tagCOMBOBOX_LIST
{
	COMBOBOX		*item;				//���V�@�ӤU�Ԯ�
	COMBOBOX_LIST	*last, *next;		//�������w
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
