/*
**	SecretSkill.h
**	secret skill functions.
**
**	Jack, 2002/10/18.
*/
#pragma	once

extern	void    init_secret_skill(void);
extern	void    enable_secret_skill(void);
extern	void    disable_secret_skill(void);

extern	void    set_secret_skill_rand_move(SLONG flag);
extern	void    set_secret_skill_rand_weather(SLONG flag);
extern	void    set_secret_skill_follow_npc(SLONG flag, USTR *mainname);
extern	void    set_secret_skill_create_account(SLONG flag);
extern	SLONG   is_enable_create_account(void);

extern	void    refresh_secret_skill(void);

extern	void    process_secret_skill_rand_move(void);
extern	void    process_secret_skill_rand_weather(void);
extern	void    process_secret_skill_follow_npc(void);

extern	SLONG   find_map_npc_by_name(USTR *name);

