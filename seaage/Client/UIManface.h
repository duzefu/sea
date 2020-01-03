/*
**	UIManface.h
**	UI of manchar face.
**
**	Jack, 2002/06/21.
**
**	Zhang Zhaohui, 2003.2.12
**			modified for qq manface			
*/
#ifndef _UIMANFACE_H_
#define _UIMANFACE_H_


// DEFINES /////////////////////////////////////////////////////////////////////////////////////////////////////////
#define MAX_MANFACE_IMAGE			1

#define MAX_MANFACE_GROUPS          14
#define MAX_MANFACE_MOUTH           5
#define MAX_MANFACE_EYES            5

// STRUCTURES //////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct tagMANFACE_DATA
{
    SLONG   manchar_index;  //角色形態索引,0~13
    SLONG   eye_index;      //眼睛的形態索引
    SLONG   mouth_index;    //口的形態索引
} MANFACE_DATA, *LPMANFACE_DATA;


// FUNCTIONS PROTOTYPES ////////////////////////////////////////////////////////////////////////////////////////////
int     init_manface(void);
void    free_manface(void);
//
void    set_manface(MANFACE_DATA *mf, SLONG manchar_index, SLONG eye_index, SLONG mouth_index);
void    redraw_manface(SLONG sx, SLONG sy, MANFACE_DATA *mf, BMP *bitmap);
//
void    get_character_manface(SLONG index, MANFACE_DATA *face);

SLONG	set_manface_index( SLONG index );		// 0 ~ MAX_MANFACE_IMAGE
void	redraw_scale_manface( SLONG sx, SLONG sy, SLONG w, SLONG h, MANFACE_DATA *mf, BMP *bitmap );

#endif//_UIMANFACE_H_
