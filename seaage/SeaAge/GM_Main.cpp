/*
**	GM_Main.cpp 
**	gm tool main functions.
**
**	Jack, 2003.2.13.
*/
#include "MainFun.h"
#include "ClientMain.h"

/************************************************************************************************************/
/* DEFINES & STRUCTURES                                                                                     */
/************************************************************************************************************/
typedef	struct tagGM_CONSOLE_DATA 
{
	SLONG	is_opened;
} GM_CONSOLE_DATA, *LPGM_CONSOLE_DATA;


GM_CONSOLE_DATA	*lp_gm_console = NULL;
/************************************************************************************************************/
/* GM CONSOLE FUNCTIONS                                                                                     */
/************************************************************************************************************/
int		init_gm_console(void)
{
	return	0;
}


void	active_gm_console(int active)
{
}


void	free_gm_console(void)
{
}


void	redraw_gm_console(SLONG sx, SLONG sy, void *vbitmap)
{
}


void	refresh_gm_console(void)
{
}


SLONG	handle_gm_console(UINT message, WPARAM wParam, LPARAM lParam)
{
	return	1;
}


SLONG	is_gm_console_opened(void)
{
	return	false;
}


void	open_gm_console(void)
{
}


void	close_gm_console(void)
{
}

