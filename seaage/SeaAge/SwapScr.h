/*
**  SWAPSCR.H
**  swap screen functions header.
**  
**  Jack, 2002.5.10.
*/
#ifndef _SWAPSCR_H_
#define _SWAPSCR_H_


//DEFINES /////////////////////////////////////////////////////////////////////////////
typedef enum    SWAP_SCREEN_TYPES
{   SWAP_SCREEN_LINE_SKIP       =   0,  //�j�業������
SWAP_SCREEN_LINE_RAND           =   1,  //�v���H�󶡹j����
SWAP_SCREEN_MOVE_DOWN           =   2,  //�V�U���ʤ���
SWAP_SCREEN_DRAG_UP             =   3,  //�ԤW����(�P�V�U���ʬۤ�)
SWAP_SCREEN_MOVE_UP             =   4,  //�V�W���ʤ���
SWAP_SCREEN_DRAG_DOWN           =   5,  //�ԤU����(�P�V�W���ʬۤ�)
SWAP_SCREEN_MOVE_RIGHT          =   6,  //�V�k���ʤ���
SWAP_SCREEN_DRAG_LEFT           =   7,	//�ԥ�����(�P�V�k���ʬۤ�)
SWAP_SCREEN_MOVE_LEFT           =   8,	//�V�����ʤ���
SWAP_SCREEN_DRAG_RIGHT          =   9,	//�ԥk����(�P�V�����ʬۤ�)
MAX_SWAP_SCREEN_TYPES           =   10, //MAX TYPES
} SWAP_SCREEN_TYPES;



//STRUCTURES //////////////////////////////////////////////////////////////////////////
typedef void    (*FNREDRAWBITMAP)(SLONG sx, SLONG sy, void *vbitmap);

typedef struct  tagSWAPSCR_DATA
{
	BMP	*	dest_bitmap;	//�ت���ϫ���
	BMP	*	src_bitmap;		//����ϫ���
	SLONG	swap_type;		//�����̹�������
	SLONG	curr_step;		//��e�����B��
	SLONG	total_steps;	//�`�@�������B��
	SLONG	play_sound;		//�}�l�ɼ����n��
	//
	SLONG	copy_base;		//�v���H�󶡹j����
	//
	FNREDRAWBITMAP	redraw_dest_func;	//���e�I��
	//
	DWORD	dwPrevAppState;	//�O�d�W���B�檬�A
	//
} SWAPSCR_DATA, *LPSWAPSCR_DATA;




//GLOBALS /////////////////////////////////////////////////////////////////////////////


//FUNCTIONS ///////////////////////////////////////////////////////////////////////////
int		init_swap_screen(void);
void	free_swap_screen(void);
void	refresh_swap_screen(void);
void	redraw_swap_screen(SLONG sx, SLONG sy, void *vbitmap);
SLONG	handle_swap_screen(UINT message, WPARAM wParam, LPARAM lParam);
//
SLONG   rand_swap_screen_type(void);
void    set_swap_screen_redraw_dest_function(FNREDRAWBITMAP func);
void    swap_screen(SLONG type, BMP *dest_bitmap, BMP *src_bitmap);
DWORD	get_swap_screen_prev_app_state(void);
//

#endif//_SWAPSCR_H_

