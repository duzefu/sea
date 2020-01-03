/*
**	SingleGame.h 
**	single game functions.
**
**	Jack, 2003.2.19.
*/
#pragma once



//
// STRUCT ///////////////////////////////////////////////////////////////////////////////////////////////////
//
typedef	struct tagSTARTING_SINGLE_GAME_DATA 
{
	SLONG	wait_counts;	//µ¥«Ý®É¶¡
} STARTING_SINGLE_GAME_DATA, *LPSTARTING_SINGLE_GAME_DATA;

//
// FUNCTIONS ////////////////////////////////////////////////////////////////////////////////////////////////
//


//
// FUNCTIONS ////////////////////////////////////////////////////////////////////////////////////////////////
//
//starting single game -------------------------------
int     init_starting_single_game(void);
void    active_starting_single_game(int active);
void    free_starting_single_game(void);
void    refresh_starting_single_game(void);
void    redraw_starting_single_game(SLONG sx, SLONG sy, void *vbitmap);
SLONG   handle_starting_single_game(UINT message, WPARAM wParam, LPARAM lParam);


