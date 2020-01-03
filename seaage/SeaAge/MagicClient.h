/*
**	MagicClient.h
**	client magic functions.
**
**	Jack, 2002/06/24.
*/
#ifndef _MAGICCLIENT_H_
#define _MAGICCLIENT_H_

void	client_break_magic(SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG magic_no, SLONG dest_no,SLONG type);
void    client_refresh_magic(void);
//
SLONG   client_check_is_magic_broken( SLONG magic_index, SLONG src_npc, SLONG map_no, SLONG magic_x, SLONG magic_y );
SLONG   client_process_magic_roll(SLONG magic_index, SLONG src_npc, SLONG map_no, SLONG magic_x, SLONG magic_y,
                                  SLONG magic_orig_x, SLONG magic_orig_y, SLONG magic_dest_x, SLONG magic_dest_y );
SLONG   client_process_magic_shake(SLONG magic_index, SLONG src_npc, SLONG map_no, SLONG magic_orig_x, SLONG magic_orig_y);
//
void	client_play_magic_voice(SLONG map_no, SLONG magic_index, SLONG kind, SLONG map_x, SLONG map_y);


SLONG   BreakMagic_ShipCannon( SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no );

 

#endif//_MAGICCLIENT_H_
