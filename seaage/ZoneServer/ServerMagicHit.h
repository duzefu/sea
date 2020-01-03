/*
**	ServerMagicHit.h
**	server magic hit functions header.
**
**	Jack, 2002/11/05.
*/
#ifndef _SERVERMAGICHIT_H_
#define _SERVERMAGICHIT_H_

extern  int     server_init_magic_hit(void);
extern  void    server_free_magic_hit(void);
extern  SLONG   server_exec_magic_hit_map_func(SLONG player_index, SLONG magic_no, SLONG x, SLONG y);
extern  SLONG   server_exec_magic_hit_npc_func(SLONG player_index, SLONG magic_no, SLONG npc_no);
extern  SLONG   server_exec_magic_hit_map_item_func(SLONG player_index, SLONG magic_no, SLONG x, SLONG y);
extern  SLONG   server_exec_magic_end_hit_map_func(SLONG player_index, SLONG magic_no, SLONG x, SLONG y);


#endif//_SERVERMAGICHIT_H_