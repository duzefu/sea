/*
**	Config.cpp
**	configuration functions.
**
**	Jack, 2002/08/20.
*/
#include "mainfun.h"
#include "config.h"



// GLOBALS /////////////////////////////////////////////////////////////////////////////////////////////////////////
USER_CONFIG user_config;


/******************************************************************************************************************/
/* USER CONFIG FUNCTIONS                                                                                          */
/******************************************************************************************************************/
void    init_user_config(USER_CONFIG *uc)
{
    uc->activate_net = FALSE;
    uc->activate_sound = FALSE;
    uc->activate_chat_save = FALSE;
    strcpy((char *)uc->door_address, "192.168.0.8");
    uc->door_port = 8699;
    uc->local_game = FALSE;
}


void    load_user_config(USER_CONFIG *uc, USTR *config_filename)
{
    USTR    group[80];
    USTR    keyword[80];
    USTR    value[80];

    //(1) load config ini file--------------------------------------------------
    if(TTN_OK != load_ini_information((USTR*)config_filename))
        return;
    //list_ini_information();

    //[SYSTEM]
    strcpy((char *)group,"SYSTEM");
    {
        memset(value, 0, 80);
        strcpy((char *)keyword,"SOUND");
        get_ini_information((USTR *)group,(USTR *)keyword,(USTR *)value);
        if(value[0] == '1')
            uc->activate_sound = TRUE;
        
        memset(value, 0, 80);
        strcpy((char *)keyword,"NET");
        get_ini_information((USTR *)group,(USTR *)keyword,(USTR *)value);
        if(value[0] == '1')
            uc->activate_net = TRUE;

        // Zhang Zhaohui 是否保存聊天記錄 2003.5.29
        memset( value, 0, 80 );
        strcpy( (char *)keyword, "CHAT_SAVE" );
        get_ini_information( (USTR*)group, (USTR*)keyword, (USTR*)value );
        if ( value[0] == '1' )
            uc->activate_chat_save = TRUE;

        memset(value, 0, 80);
        strcpy((char *)keyword,"DOORADDRESS");
        get_ini_information((USTR *)group,(USTR *)keyword,(USTR *)value);
        if(value[0] != 0)
        {
            strcpy((char *)uc->door_address, (const char *)value);
        }

        memset(value, 0, 80);
        strcpy((char *)keyword,"DOORPORT");
        get_ini_information((USTR *)group,(USTR *)keyword,(USTR *)value);
        if(value[0] != 0)
        {
            uc->door_port = atoi((const char *)value);
        }
        
        memset(value, 0, 80);
        strcpy((char *)keyword, "LOCALGAME");
        get_ini_information((USTR *)group,(USTR *)keyword,(USTR *)value);
        if(value[0] == '1')
        {
            uc->local_game = TRUE;
        }
    }

    //(X) free config ini file --------------------------------------------------
    free_ini_information();
}


SLONG   is_local_game(void)
{
    return  user_config.local_game;
}

void    debug_log_user_config(USER_CONFIG *uc)
{
#ifdef  DEBUG
    log_error(1, ";user config");
    log_error(1, "[SYSTEM]");
    log_error(1, "SOUND=%d", uc->activate_sound);
    log_error(1, "NET=%d", uc->activate_net);
    log_error(1, "DOORADDRESS=%s", uc->door_address);
    log_error(1, "DOORPORT=%d", uc->door_port);
    log_error(1, "LOCALGAME=%d", uc->local_game);
    log_error(1, "CAHT_SAVE=%d", uc->activate_chat_save );
#endif//DEBUG
}


