/*
**	FightClient.h
**	client fight functions.
**
**	Jack, 2002/09/24.
*/
#ifndef _FIGHTCLIENT_H_
#define _FIGHTCLIENT_H_

void    client_refresh_npc_foot_speed_state(SLONG npc_no);
void    client_compute_npc_muse_effect(SLONG npc_no);
void    client_compute_npc_attack_npc_effect(SLONG npc_no, SLONG dest_npc, SLONG magic_no);
void    client_compute_npc_final_attack_npc_effect(SLONG npc_no, SLONG dest_npc, SLONG magic_no);
void	client_play_fight_voice(SLONG map_no, SLONG npc_no, SLONG file_index, SLONG doing_kind, 
                                SLONG doing_step, SLONG dest_x, SLONG dest_y);


#endif//_FIGHTCLIENT_H_
