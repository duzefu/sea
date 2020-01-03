/*
**	Fight.h
**	fight functions header.
**
**	Jack, 2002/09/24.
*/
#ifndef _FIGHT_H_
#define _FIGHT_H_


//GLOBALS /////////////////////////////////////////////////////////////////////////////////////////////
extern  void    (*refresh_npc_foot_speed_state) (SLONG npc_no);
extern  void    (*compute_npc_muse_effect) (SLONG npc_no);
extern  void    (*compute_npc_attack_npc_effect) (SLONG npc_no, SLONG dest_npc, SLONG magic_no);
extern  void    (*compute_npc_final_attack_npc_effect) (SLONG npc_no, SLONG dest_npc, SLONG magic_no);
//
extern  void	(*play_fight_voice) (SLONG map_no, SLONG npc_no, SLONG file_index, SLONG doing_kind, 
                                     SLONG doing_step, SLONG dest_x, SLONG dest_y);


//FUNCTIONS ///////////////////////////////////////////////////////////////////////////////////////////
extern  void    set_fight_functions(void);


#endif//_FIGHT_H_
