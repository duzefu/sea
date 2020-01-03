/*
**	Config.h
**	configuration functions header.
**
**	Jack, 2002/08/20.
*/
#ifndef _CONFIG_H_
#define _CONFIG_H_


// DEFINES /////////////////////////////////////////////////////////////////////////////////////////////////////////

// STRUCTURES //////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct  tagUSER_CONFIG
{
    SLONG   activate_sound;
    SLONG   activate_net;
    SLONG   activate_chat_save;
    //
    USTR    door_address[80];
    SLONG   door_port;
    //
    SLONG   local_game;
} USER_CONFIG, *LPUSER_CONFIG;


extern  USER_CONFIG user_config;



// FUNCTION PROTOTYPES /////////////////////////////////////////////////////////////////////////////////////////////
void    init_user_config(USER_CONFIG *uc);
void    load_user_config(USER_CONFIG *uc, USTR *config_filename);
SLONG   is_local_game(void);
void    debug_log_user_config(USER_CONFIG *uc);








#endif//_CONFIG_H_
