/*
**	MagicHit.h
**	magic hit processing.
**
**	Jack, 2002/09/16.
*/
#ifndef _MAGICHIT_H_
#define _MAGICHIT_H_

void    init_magic_hits(void);
//
SLONG   exec_magic_buttondown(SLONG player_index, SLONG magic_no, WPARAM wParam, LPARAM lParam);
SLONG   exec_magic_buttonup(SLONG player_index, SLONG magic_no, WPARAM wParam, LPARAM lParam);
SLONG   exec_magic_mousemove(SLONG player_index, SLONG magic_no, WPARAM wParam, LPARAM lParam);
//


#endif//_MAGICHIT_H_
