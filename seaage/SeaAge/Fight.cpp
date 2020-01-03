/*
**	Fight.cpp
**	fight functions.
**
**	Jack, 2002/09/24.
*/
#include "MainFun.h"
#include "ClientMain.h"
#include "FightClient.h"
#include "Fight.h"


void    (*refresh_npc_foot_speed_state) (SLONG npc_no);
void    (*compute_npc_muse_effect) (SLONG npc_no);
void    (*compute_npc_attack_npc_effect) (SLONG npc_no, SLONG dest_npc, SLONG magic_no);
void    (*compute_npc_final_attack_npc_effect) (SLONG npc_no, SLONG dest_npc, SLONG magic_no);
void	(*play_fight_voice) (SLONG map_no, SLONG npc_no, SLONG file_index, SLONG doing_kind, 
                             SLONG doing_step, SLONG dest_x, SLONG dest_y);



/******************************************************************************************************************/
/* FIGHT MAIN FUNCTIONS                                                                                           */
/******************************************************************************************************************/
void    set_fight_functions(void)
{
	refresh_npc_foot_speed_state = client_refresh_npc_foot_speed_state;
	compute_npc_muse_effect = client_compute_npc_muse_effect;
	compute_npc_attack_npc_effect = client_compute_npc_attack_npc_effect;
	compute_npc_final_attack_npc_effect = client_compute_npc_final_attack_npc_effect;
	//
	play_fight_voice = client_play_fight_voice;
}


