/*
**	ServerFight.h
**	server fight functions.
**
**	Jack, 2002/10/31.
*/
#ifndef _SERVERFIGHT_H_
#define _SERVERFIGHT_H_

// DEFINES /////////////////////////////////////////////////////////////////////////////////////////////////////////
// STRUCTURES //////////////////////////////////////////////////////////////////////////////////////////////////////
// GLOBALS /////////////////////////////////////////////////////////////////////////////////////////////////////////
// FUNCTIONS ///////////////////////////////////////////////////////////////////////////////////////////////////////
extern  SLONG   server_process_npc_muse_effect(SLONG npc_no);
extern  SLONG   server_process_npc_dead_relive(SLONG npc_no);
extern  SLONG   server_process_npc_attack_npc_effect(SLONG src_npc, SLONG dest_npc, SLONG magic_no);
extern  SLONG   server_process_npc_final_attack_npc_effect(SLONG src_npc, SLONG dest_npc, SLONG magic_no);
extern  SLONG   server_process_npc_clash_effect(SLONG npc_no);
//
extern  SLONG   server_is_player_can_change_fight_state(SLONG npc_no, SLONG fight_flag);
//
extern  SLONG   server_process_magic_attack_line(SLONG magic_index, SLONG src_npc,
                                                 SLONG magic_orig_x, SLONG magic_orig_y,
                                                 SLONG magic_dest_x, SLONG magic_dest_y);
extern  SLONG   server_process_line_attack_effect(SLONG magic_no, SLONG src_npc, SLONG dest_npc, SLONG src_attack_x, SLONG src_attack_y);
//
extern  SLONG   server_process_npc_dead_operation(SLONG npc_no);
extern	SLONG	server_process_npc_drop_item(SLONG npc_no, SLONG beated_by, SLONG x, SLONG y, SLONG z);
extern  SLONG   server_process_npc_get_exp(SLONG npc_no, SLONG get_exp);
//
// mark by lijun 2003-05-22
/*
//AI FUNCTIONS
extern	void    server_execute_npc_ai_when_move( SLONG npc_no );
extern	void    server_execute_npc_ai_after_attack( SLONG npc_no );
extern	void    server_execute_npc_ai_after_magic( SLONG npc_no );
extern	void    server_execute_npc_ai_after_beated( SLONG npc_no );
extern	void    server_execute_npc_ai_after_dodge( SLONG npc_no );
//
extern	void    server_choose_npc_magic_npc( SLONG src_npc, SLONG dest_npc );
extern	void    server_choose_npc_attack_npc( SLONG npc_no, SLONG dest_npc );
extern	void    server_choose_npc_move_type( SLONG npc_no );
extern	void    server_choose_npc_mixed_attack_npc( SLONG npc_no, SLONG dest_npc );
extern	void    server_choose_npc_dodge_npc( SLONG npc_no, SLONG dest_npc );
extern	void    server_choose_npc_fight_idle( SLONG npc_no );
extern	void    server_choose_npc_fight_gad( SLONG npc_no );
extern	void    server_choose_npc_run_attack_npc( SLONG npc_no, SLONG dest_npc );
extern	void	server_choose_npc_trance(SLONG npc_no);
*/


#endif//_SERVERFIGHT_H_
