/*
**	MagicC.h
**	server magic functions.
**
**	Jack, 2002/06/24.
*/
#ifndef _MAGICC_H_
#define _MAGICC_H_

// 
SLONG   server_break_magic(SLONG map_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG magic_index);
void    server_refresh_magic(void);
//
SLONG   server_check_is_magic_broken( SLONG magic_index, SLONG src_npc, SLONG map_no, SLONG magic_x, SLONG magic_y );
SLONG   server_process_magic_roll(SLONG magic_index, SLONG src_npc, SLONG map_no, SLONG magic_x, SLONG magic_y,
                                  SLONG magic_orig_x, SLONG magic_orig_y, SLONG magic_dest_x, SLONG magic_dest_y );
SLONG   server_process_magic_shake(SLONG magic_index, SLONG src_npc, SLONG map_no, SLONG magic_orig_x, SLONG magic_orig_y);

#endif//_MAGICC_H_
