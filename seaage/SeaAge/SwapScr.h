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
{   SWAP_SCREEN_LINE_SKIP       =   0,  //隔行平移切換
SWAP_SCREEN_LINE_RAND           =   1,  //逐行隨机間隔切換
SWAP_SCREEN_MOVE_DOWN           =   2,  //向下移動切換
SWAP_SCREEN_DRAG_UP             =   3,  //拉上切換(與向下移動相反)
SWAP_SCREEN_MOVE_UP             =   4,  //向上移動切換
SWAP_SCREEN_DRAG_DOWN           =   5,  //拉下切換(與向上移動相反)
SWAP_SCREEN_MOVE_RIGHT          =   6,  //向右移動切換
SWAP_SCREEN_DRAG_LEFT           =   7,	//拉左切換(與向右移動相反)
SWAP_SCREEN_MOVE_LEFT           =   8,	//向左移動切換
SWAP_SCREEN_DRAG_RIGHT          =   9,	//拉右切換(與向左移動相反)
MAX_SWAP_SCREEN_TYPES           =   10, //MAX TYPES
} SWAP_SCREEN_TYPES;



//STRUCTURES //////////////////////////////////////////////////////////////////////////
typedef void    (*FNREDRAWBITMAP)(SLONG sx, SLONG sy, void *vbitmap);

typedef struct  tagSWAPSCR_DATA
{
	BMP	*	dest_bitmap;	//目的位圖指標
	BMP	*	src_bitmap;		//源位圖指標
	SLONG	swap_type;		//切換屏幕的類型
	SLONG	curr_step;		//當前切換步數
	SLONG	total_steps;	//總共切換的步數
	SLONG	play_sound;		//開始時播放聲音
	//
	SLONG	copy_base;		//逐行隨机間隔切換
	//
	FNREDRAWBITMAP	redraw_dest_func;	//重畫背景
	//
	DWORD	dwPrevAppState;	//保留上次運行狀態
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

