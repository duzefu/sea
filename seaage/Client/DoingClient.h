/*
**  DoingClient.h
**  npc doing functions for online game client.
**
**  Jack, 2002.5.15.
*/
#ifndef _DOINGCLIENT_H_
#define _DOINGCLIENT_H_
 
  
SLONG   client_do_npc_dummy(SLONG npc_no);
SLONG   client_do_npc_pause(SLONG npc_no);
//
SLONG   client_do_npc_idle(SLONG npc_no);
SLONG   client_do_npc_muse(SLONG npc_no);
SLONG   client_do_npc_spower(SLONG npc_no);
SLONG   client_do_npc_change_map(SLONG npc_no);
SLONG   client_do_npc_stand(SLONG npc_no);
//
SLONG   client_do_npc_move_to(SLONG npc_no);
SLONG   client_do_npc_magic_position(SLONG npc_no);
SLONG   client_do_npc_clash(SLONG npc_no);
SLONG   client_do_npc_gad(SLONG npc_no);
SLONG   client_do_npc_patrol(SLONG npc_no);
//
SLONG   client_do_npc_talk_with_npc(SLONG npc_no);
SLONG   client_do_npc_attack_npc(SLONG npc_no);
SLONG   client_do_npc_magic_npc(SLONG npc_no);
SLONG   client_do_npc_sequential_attack_npc(SLONG npc_no);
//
SLONG   client_do_npc_pick_item(SLONG npc_no);
//
SLONG   client_do_npc_beated(SLONG npc_no);
SLONG   client_do_npc_dead(SLONG npc_no);
SLONG   client_do_npc_down_and_out(SLONG npc_no);
SLONG   client_do_npc_defence(SLONG npc_no);
SLONG   client_do_npc_defenced(SLONG npc_no);
//
SLONG   client_do_npc_cheer(SLONG npc_no);
SLONG   client_do_npc_angry(SLONG npc_no);
SLONG   client_do_npc_beckon(SLONG npc_no);
SLONG   client_do_npc_court(SLONG npc_no);
SLONG   client_do_npc_faint(SLONG npc_no);
SLONG   client_do_npc_say_no(SLONG npc_no);
SLONG   client_do_npc_bow(SLONG npc_no);
SLONG   client_do_npc_win(SLONG npc_no);
SLONG   client_do_npc_swash(SLONG npc_no);
SLONG   client_do_npc_xxpower(SLONG npc_no);
SLONG   client_do_npc_xxbeated(SLONG npc_no);
//
SLONG   client_do_sea_npc_acc_move_to(SLONG npc_no);
//
SLONG   client_do_npc_fight_idle(SLONG npc_no);
SLONG   client_do_npc_fight_gad(SLONG npc_no);
SLONG   client_do_npc_fight_patrol(SLONG npc_no);

//  通用!!!! 的npc戰鬥動畫播放函數
SLONG   client_do_npc_fight_action(SLONG npc_no);

#endif//_DOINGCLIENT_H_
