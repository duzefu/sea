/*
**	UIMagicIcon.h
**	UI of magic icon functions.
**
**	Jack, 2002/09/11.
*/
#ifndef _UIMAGICICON_H_
#define _UIMAGICICON_H_



//D E F I N E S ///////////////////////////////////////////////////////////////////////////////////////////////////
#define MAX_MAGIC_ICONS             256 //�ޯ�ICON���ƥ�
//
#define MAGIC_ICON_WIDTH            30  //�ޯ�ICON���e��
#define MAGIC_ICON_HEIGHT           30  //�ޯ�ICON������
//
//
#define MAGIC_ICON_NORMAL           0   //�@��ICON
#define MAGIC_ICON_INVALID          1   //�ثe�L�k�ϥΪ��k�NICON


//F U N C T I O N S ///////////////////////////////////////////////////////////////////////////////////////////////
SLONG   init_magic_icon_image(void);
void    free_magic_icon_image(void);
void    redraw_magic_icon_image(SLONG cx, SLONG cy, SLONG index, BMP *bitmap, SLONG redraw_flags);
void    redraw_alpha_magic_icon_image(SLONG cx, SLONG cy, SLONG index, BMP *bitmap, SLONG alpha);
void    redraw_magic_icon_clockwise_mask(SLONG cx, SLONG cy, SLONG opened_percent, BMP *bitmap);
void    redraw_magic_icon_anti_clockwise_mask(SLONG cx, SLONG cy, SLONG opened_percent, BMP *bitmap);
//
void    redraw_magic_icon_image_with_state(SLONG cx, SLONG cy, SLONG index, SLONG state, SLONG ticks, SLONG total_ticks, BMP *bitmap);


#endif//_UIMAGICICON_H_
