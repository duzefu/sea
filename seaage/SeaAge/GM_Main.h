/*
**	GM_Main.h 
**	gm main function header.
**
**	Jack, 2003.2.13.
*/
#pragma once


int		init_gm_console(void);
void	active_gm_console(int active);
void	free_gm_console(void);
//
void	redraw_gm_console(SLONG sx, SLONG sy, void *vbitmap);
void	refresh_gm_console(void);
SLONG	handle_gm_console(UINT message, WPARAM wParam, LPARAM lParam);
//
SLONG	is_gm_console_opened(void);
void	open_gm_console(void);
void	close_gm_console(void);
//
