/*
**	CmdEvent.h
**	Cmd events of game.
**
**	Jack, 2002/09/13.
*/
#ifndef _CMDEVENT_H_
#define _CMDEVENT_H_


extern	void    client_cmd_init_app_state(void);
extern	int     client_cmd_init_main_game(void);
extern	void    client_cmd_game_start(void);
//
extern	int     client_cmd_left_hit_map(SLONG x, SLONG y);
extern	int     client_cmd_right_hit_map(SLONG x, SLONG y);
extern	int     client_cmd_left_hit_npc(SLONG dest_npc);
extern	int     client_cmd_right_hit_npc(SLONG dest_npc);
extern	int     client_cmd_left_hit_sash_item(SLONG sash_index);
extern	int     client_cmd_right_hit_sash_item(SLONG sash_index);
extern	int     client_cmd_open_player_bag(void);
extern	int     client_cmd_close_player_bag(void);
extern	int     client_cmd_left_hit_map_item(SLONG item_x, SLONG item_y);
extern	int     client_cmd_right_hit_map_item(SLONG item_x, SLONG item_y);
extern	int		client_cmd_request_change_dir(SLONG dir);
//
extern	int     client_cmd_left_end_hit_map(SLONG x, SLONG y);
extern	int     client_cmd_right_end_hit_map(SLONG x, SLONG y);
//
extern	int     client_cmd_public_talk(char *sendname,char *msg);
extern	int     client_cmd_npc_doing(SLONG npc_no, SLONG doing_kind, SLONG doing_step, SLONG d1, SLONG d2, SLONG d3, SLONG d4, SLONG d5);
extern	int     client_cmd_change_fight_state(void);
//
extern	int     client_cmd_add_base_strength(SLONG data);
extern	int     client_cmd_add_base_instinct(SLONG data);
extern	int     client_cmd_add_base_wit(SLONG data);
extern	int     client_cmd_add_base_luck(SLONG data);
extern	int     client_cmd_sub_base_strength(SLONG data);
extern	int     client_cmd_sub_base_instinct(SLONG data);
extern	int     client_cmd_sub_base_wit(SLONG data);
extern	int     client_cmd_sub_base_luck(SLONG data);
//
extern	int     client_cmd_left_hit_head_item(void);
extern	int     client_cmd_right_hit_head_item(void);
extern	int     client_cmd_left_hit_neck_item(void);
extern	int     client_cmd_right_hit_neck_item(void);
extern	int     client_cmd_left_hit_body_item(void);
extern	int     client_cmd_right_hit_body_item(void);
extern	int     client_cmd_left_hit_hands_item(void);
extern	int     client_cmd_right_hit_hands_item(void);
extern	int     client_cmd_left_hit_waist_item(void);
extern	int     client_cmd_right_hit_waist_item(void);
extern	int     client_cmd_left_hit_wrist_item(void);
extern	int     client_cmd_right_hit_wrist_item(void);
extern	int     client_cmd_left_hit_glove_item(void);
extern	int     client_cmd_right_hit_glove_item(void);
extern	int     client_cmd_left_hit_feet_item(void);
extern	int     client_cmd_right_hit_feet_item(void);
extern	int     client_cmd_left_hit_bag_item(SLONG bag_index);
extern	int     client_cmd_right_hit_bag_item(SLONG bag_index);
extern	int		client_cmd_left_hit_othera_item(void);
extern	int		client_cmd_right_hit_othera_item(void);
extern	int		client_cmd_left_hit_otherb_item(void);
extern	int		client_cmd_right_hit_otherb_item(void);
extern	int		client_cmd_left_hit_otherc_item(void);
extern	int		client_cmd_right_hit_otherc_item(void);
extern  int     client_cmd_left_hit_treasure_item( VOID );
extern  int     client_cmd_right_hit_treasure_item( VOID );
//
extern	int     client_cmd_drop_item(SLONG map_x, SLONG map_y);
//
extern	int     client_cmd_set_lhand_quick_magic(SLONG quick_index, SLONG magic_no);
extern	int     client_cmd_set_rhand_quick_magic(SLONG quick_index, SLONG magic_no);
extern	int     client_cmd_quick_set_hand_magic(SLONG quick_index);
extern	int     client_cmd_set_lhand_magic(SLONG magic_no);
extern	int     client_cmd_set_rhand_magic(SLONG magic_no);
//
extern	int		client_cmd_request_npc_proc(SLONG npc_no, SLONG proc_no);
extern	int		client_cmd_left_hit_item_store_item(SLONG store_index, SLONG index);
extern	int		client_cmd_request_sell_item(SLONG store_index);

extern	int		client_cmd_hit_bank_item( UHINT bank_index );
extern	int		client_cmd_request_bank_save_money( SLONG money );
extern	int		client_cmd_request_bank_load_money( SLONG money );
//
extern	int		client_cmd_request_join_team(char *mainname, char *zone_name );
extern	int		client_cmd_request_agree_join_team(char *mainname, char *zone_name );
extern	int		client_cmd_request_exit_team(char *mainname );
extern	int		client_cmd_request_kick_team_member(char *mainname, char *zone_name );


#endif//_CMDEVENT_H_
