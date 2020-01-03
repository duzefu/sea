/*
**  Client_RecvMsg.cpp
**  Client receive message functions.
**
**
**  Jack, 2002.5.13.
*/

#include "MainFun.h"
#include "NetGE_MainFunc.h"
#include "UI.h"
#include "ClientMain.h"
#include "ErrorMsg.h"
#include "Npc.h"
#include "CChat.h"
#include "MainGame.h"
#include "HrtBeat.h"
#include "PosData.h"
#include "Weather.h"
#include "UISystemMessage.h"
#include "UIGameMessage.h"
#include "qqmain.h"
#include "qqclient.h"
#include "UIManager.h"
#include "UIMagicArea.h"
//
#include "NetGE.h"
#include "NetGE_Event_Def.h"
#include "NetGE_Event_Struct_Def.h"
#include "Client_SendMsg.h"
#include "Client_RecvMsg.h"
#include "Client_Item.h"
#include "MagicClient.h"
#include "Media.h"
#include "Team.h"

#include "UIShowMap.h"

//GLOBALS ////////////////////////////////////////////////////////////////////////////////////////////////
WORLD_INFO      world_info[MAX_WORLD_INFO];
SLONG           max_world_info = 0;
CHARACTER_INFO  character_info[MAX_CHARACTER_INFO];
//
static  void    apply_list_player_info_to_character_npc(TPOS_EVENT_GETPLAYERLIST info);
static	void	apply_mycharacterdata_to_character_npc(SLONG index, TPOS_EVENT_MYCHARACTER info);
static	void    client_add_npc_talk_msg(SLONG npc_no, USTR *msg);
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//  LOCAL FUNCTIONS                                                                                     //
//////////////////////////////////////////////////////////////////////////////////////////////////////////
void    clear_world_info(void)
{
    max_world_info = 0;
}


void    clear_character_info(void)
{
    int i;
    
    for(i=0; i<MAX_CHARACTER_INFO; i++)
    {
        character_info[i].flag = 0;
    }
}


void    debug_init_character_info(void)
{
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////
// HANDLE DLL MESSAGE FUNCTIONS                                                                         //
//////////////////////////////////////////////////////////////////////////////////////////////////////////
static	SLONG   client_handle_default_game_event(SLONG type)
{
#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    UNKNOWN EVENT(type:%d)", type);
#endif//DEBUG_MSG
    
    return  0;
}


static	SLONG   client_handle_version_error(DWORD wParam)
{
    int		iRet;

    display_error_message((USTR*)ERRMSG_VERSION_ERROR, DISPLAY_MESSAGE_TO_SCREEN, screen_buffer);
    wait_key_time(' ', 80);

	DWORD	dwState;
	if(g_dwAppState == APPSTATE_SHOW_SWAP_SCREEN)
		dwState = get_swap_screen_prev_app_state();
	else
		dwState = g_dwAppState;
    switch(dwState)
    {
    case APPSTATE_SHOW_LOGIN:
        iRet = ClientLogoutDoor();
        break;
    case APPSTATE_SHOW_SELECT_WORLD_SERVER:
        iRet = ClientLogoutWorld();
        break;
    }
    
    
#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    VERSION_ERROR");
#endif//DEBUG_MSG
    
    return  0;
}


static	SLONG   client_handle_error_data(DWORD wParam)
{
    display_error_message((USTR*)ERRMSG_ERROR_DATA, DISPLAY_MESSAGE_TO_SCREEN, screen_buffer);
    wait_key_time(' ', 80);
	g_dwAppState = APPSTATE_ERROR_EXIT;

#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    ERROR_DATA");
#endif//DEBUG_MSG
    
    return  0;
}


static	SLONG   client_handle_door_server_closed(DWORD wParam)
{
    display_error_message((USTR*)ERRMSG_DOOR_SERVER_CLOSED, DISPLAY_MESSAGE_TO_SCREEN, screen_buffer);
    wait_key_time(' ', 80);
    
#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    DOOR_SERVER_CLOSED");
#endif//DEBUG_MSG
    
    return  0;
}


static	SLONG   client_handle_world_server_closed(DWORD wParam)
{
    display_error_message((USTR*)ERRMSG_DOOR_SERVER_CLOSED, DISPLAY_MESSAGE_TO_SCREEN, screen_buffer);
    wait_key_time(' ', 80);
    
    set_next_app_state(APPSTATE_INIT_LOGIN);
    change_app_state();
    
#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    WORLD_SERVER_CLOSED");
#endif//DEBUG_MSG
    
    return  0;
}


static	SLONG   client_handle_zone_server_closed(DWORD wParam)
{
    display_error_message((USTR*)ERRMSG_ZONE_SERVER_CLOSED, DISPLAY_MESSAGE_TO_SCREEN, screen_buffer);
    wait_key_time(' ', 80);
    
    set_next_app_state(APPSTATE_INIT_LOGIN);
    change_app_state();
    
#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    ZONE_SERVER_CLOSED");
#endif//DEBUG_MSG
    
    return  0;
}


static	SLONG   client_handle_door_login_ok(DWORD wParam)
{
    int     iRet;
    
    clear_world_info();
    iRet = ClientRequestForWorldInfo(BEGIN);
    
#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    DOOR_LOGIN_OK");
#endif//DEBUG_MSG
    
    return  0;
}


static	SLONG	client_handle_door_login_fail(DWORD wParam)
{
	int	iRet;

	display_error_message((USTR*)ERRMSG_LOGIN_DOOR_SERVER_FAILED, DISPLAY_MESSAGE_TO_SCREEN, screen_buffer);
	wait_key_time(' ', 80);
	iRet = ClientLogoutDoor();

#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    DOOR_LOGIN_FAIL");
#endif//DEBUG_MSG
    
    return  0;
}


static	SLONG	client_handle_door_login_errorid(DWORD wParam)
{
	int	iRet;
	display_error_message((USTR*)ERRMSG_LOGIN_DOOR_SERVER_ID_ERROR, DISPLAY_MESSAGE_TO_SCREEN, screen_buffer);
	wait_key_time(' ', 80);
	iRet = ClientLogoutDoor();

#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    DOOR_LOGIN_ERRORID");
#endif//DEBUG_MSG
    
    return  0;
}


static	SLONG	client_handle_door_login_errorpw(DWORD wParam)
{
	int	iRet;

	display_error_message((USTR*)ERRMSG_LOGIN_DOOR_SERVER_PASSWORD_ERROR, DISPLAY_MESSAGE_TO_SCREEN, screen_buffer);
	wait_key_time(' ', 80);
	iRet = ClientLogoutDoor();

#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    DOOR_LOGIN_ERRORID");
#endif//DEBUG_MSG
    
    return  0;
}


static	SLONG	client_handle_door_login_denied(DWORD wParam)
{
	int	iRet;

	display_error_message((USTR*)ERRMSG_LOGIN_DOOR_SERVER_ID_DENIED, DISPLAY_MESSAGE_TO_SCREEN, screen_buffer);
	wait_key_time(' ', 80);
	iRet = ClientLogoutDoor();

#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    DOOR_LOGIN_ERRORID");
#endif//DEBUG_MSG
    
    return  0;
}


static	SLONG   client_handle_door_kicked(DWORD wParam)
{
    int iRet;
    
    display_error_message((USTR*)ERRMSG_DOOR_KICKED, DISPLAY_MESSAGE_TO_SCREEN, screen_buffer);
    wait_key_time(' ', 80);
    iRet = ClientLogoutDoor();
    
    set_next_app_state(APPSTATE_INIT_LOGIN);
    change_app_state();
    
#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    DOOR_KICKED");
#endif//DEBUG_MSG
    
    return  0;
}


static	SLONG	client_handle_door_login_repeat(DWORD wParam)
{
	int	iRet;

	display_error_message((USTR*)ERRMSG_LOGIN_REPEAT, DISPLAY_MESSAGE_TO_SCREEN, screen_buffer);
	wait_key_time(' ', 80);
	iRet = ClientLogoutDoor();
    
#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    DOOR_LOGIN_REPEAT");
#endif//DEBUG_MSG
    
    return  0;
}


static	SLONG   client_handle_get_world_info(DWORD wParam)
{
	TPOS_EVENT_GETWORLDINFO	info;
    SLONG   index;

    memcpy(&info, (void*)wParam, sizeof(info));
	if(END == info.dwIndex)
    {
        change_app_state();
        
#ifdef  DEBUG_MSG
        log_encrypt_message(1, "    GET_WORLD_INFO END");
#endif//DEBUG_MSG
        
        return  0;
    }
	else
	{
		if(max_world_info < MAX_WORLD_INFO)
		{
			index = max_world_info;
			strcpy((char *)world_info[index].name, (const char *)info.cName);
			strcpy((char *)world_info[index].addr, (const char *)info.cAddr);
			world_info[index].port = info.dwPort;
			world_info[index].player_count = info.dwPlayerCount;
			world_info[index].active = info.dwActive;
			max_world_info ++;
		}

		ClientRequestForWorldInfo(info.dwIndex+1);

#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    GET_WORLD_INFO(local_index:%d, name:%s, players:%d)", 
		index, info.cName, info.dwPlayerCount);
#endif//DEBUG_MSG
    
	}
    
    return  0;
}


static	SLONG   client_handle_refresh_world_info(DWORD wParam)
{
	TPOS_EVENT_REFRESHWORLDINFO	info;
    SLONG   i;
    
	memcpy(&info, (void*)wParam, sizeof(info));
    for(i = 0; i<max_world_info; i++)
    {
        if( 0 == strcmp((const char *)world_info[i].name, (const char *)info.cName) )
        {
            world_info[i].player_count = info.dwPlayerCount;
            world_info[i].active = info.dwActive;
        }
    }
    
#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    REFRESH_WORLD_INFO(name:%s, active:%d, players:%d)",
        info.cName, info.dwActive, info.dwPlayerCount);
#endif//DEBUG_MSG
    
    return  0;
}


static	SLONG   client_handle_new_world_info(DWORD wParam)
{
	TPOS_EVENT_NEWWORLDINFO	info;
    SLONG   index;
    
	memcpy(&info, (void*)wParam, sizeof(info));
    if(max_world_info < MAX_WORLD_INFO)
    {
        index = max_world_info;
        strcpy((char *)world_info[index].name, (const char *)info.cName);
        strcpy((char *)world_info[index].addr, (const char *)info.cAddr);
        world_info[index].port = info.dwPort;
        world_info[index].player_count = info.dwPlayerCount;
        world_info[index].active = info.dwActive;
        max_world_info ++;
    }
    
#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    NEW_WORLD_INFO(name:%s, players:%d)", info.cName, info.dwPlayerCount);
#endif//DEBUG_MSG
    
    return  0;
}

static	SLONG   client_handle_world_close(DWORD wParam)
{
	TPOS_EVENT_CLOSEWORLDINFO	info;
    SLONG   i, j;

    memcpy(&info, (void *)wParam, sizeof(info));
    for(i = 0; i<max_world_info; i++)
    {
        if( 0 == strcmp((const char *)world_info[i].name, (const char *)info.cName) )
        {
            for(j = i; j<max_world_info-1; j++)
            {
				world_info[j] = world_info[j+1];
            }
            max_world_info --;
        }
    }
    
#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    WORLD_CLOSE(name:%s)", info.cName);
#endif//DEBUG_MSG
    
    return  0;
}


static	SLONG   client_handle_register_account_check_ok(DWORD wParam)
{
    //set_next_app_state(APPSTATE_INIT_SETUP_RECORD);
    change_app_state();
    
#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    REGISTER_ACCOUNT_CHECK_OK");
#endif//DEBUG_MSG
    
    return  0;
}


static	SLONG   client_handle_register_account_final_ok(DWORD wParam)
{
    int iRet;
    
    //logout user: "guest" (password is "register")
    iRet = ClientLogoutDoor();
    
    //set_next_app_state(APPSTATE_INIT_LOGIN);
    change_app_state();
    
#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    REGISTER_ACCOUNT_FINAL_OK");
#endif//DEBUG_MSG
    
    return  0;
}


static	SLONG	client_handle_register_account_check_fail(DWORD wParam)
{
#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    REGISTER_ACCOUNT_CHECK_FAIL");
#endif//DEBUG_MSG
	return	0;
}


static	SLONG   client_handle_register_account_idused(DWORD wParam)
{
    display_error_message((USTR*)ERRMSG_ACCOUNT_IDUSED, DISPLAY_MESSAGE_TO_SCREEN, screen_buffer);
    wait_key_time(' ', 80);
    
#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    REGISTER_ACCOUNT_IDUSED");
#endif//DEBUG_MSG
    
    return  0;
}


static	SLONG   client_handle_world_login_ok(DWORD wParam)
{
    int iRet;
    
    clear_character_info();
    iRet = ClientRequestForCharacterInfo((char *)uilogin.account, BEGIN);
    
#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    WORLD_LOGIN_OK");
#endif//DEBUG_MSG
    
    return  0;
}


static	SLONG	client_handle_world_login_fail(DWORD wParam)
{
	display_error_message((USTR*)ERRMSG_LOGIN_WORLD_SERVER_FAILED, DISPLAY_MESSAGE_TO_SCREEN, screen_buffer);
	wait_key_time(' ', 80);

#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    WORLD_LOGIN_FAIL");
#endif//DEBUG_MSG
    
    return  0;
}


static	SLONG	client_handle_world_login_errorid(DWORD wParam)
{
	display_error_message((USTR*)ERRMSG_WORLD_LOGIN_ERRORID, DISPLAY_MESSAGE_TO_SCREEN, screen_buffer);
	wait_key_time(' ', 80);

#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    WORLD_LOGIN_ERRORID");
#endif//DEBUG_MSG
    
    return  0;
}


static	SLONG	client_handle_world_login_errorpw(DWORD wParam)
{
	display_error_message((USTR*)ERRMSG_WORLD_LOGIN_ERRORPW, DISPLAY_MESSAGE_TO_SCREEN, screen_buffer);
	wait_key_time(' ', 80);

#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    WORLD_LOGIN_ERRORPW");
#endif//DEBUG_MSG
    
    return  0;
}


static	SLONG	client_handle_world_login_denied(DWORD wParam)
{
	display_error_message((USTR*)ERRMSG_WORLD_LOGIN_DENIED, DISPLAY_MESSAGE_TO_SCREEN, screen_buffer);
	wait_key_time(' ', 80);

#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    WORLD_LOGIN_DENIED");
#endif//DEBUG_MSG
    
    return  0;
}


static	SLONG	client_handle_world_login_kicked(DWORD wParam)
{
	display_error_message((USTR*)ERRMSG_WORLD_LOGIN_KICKED, DISPLAY_MESSAGE_TO_SCREEN, screen_buffer);
	wait_key_time(' ', 80);

#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    WORLD_LOGIN_KICKED");
#endif//DEBUG_MSG
    
    return  0;
}


static	SLONG	client_handle_world_login_repeat(DWORD wParam)
{
	display_error_message((USTR*)ERRMSG_WORLD_LOGIN_REPEAT, DISPLAY_MESSAGE_TO_SCREEN, screen_buffer);
	wait_key_time(' ', 80);

#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    WORLD_LOGIN_REPEAT");
#endif//DEBUG_MSG
    
    return  0;
}



static	SLONG   client_handle_get_zone_info(DWORD wParam)
{
	TPOS_EVENT_GETZONEINFO	info;
    
	memcpy(&info, (void*)wParam, sizeof(info));

	//在此保存玩家的ZONE, MAP. 當玩家切換地圖時, 可能需要用到(比如先載地圖).
	strcpy((char *)g_szPlayerZone, (const char *)info.cZone);
	strcpy((char *)g_szPlayerMap, (const char *)info.cMapName);
	g_dwZoneType = info.dwType;
	g_lPlayerIndex = -1;

	store_change_map_data((USTR*)info.cZone, (USTR*)info.cMapName, (USTR*)info.cAddr, (SLONG)info.dwPort, 
		0, 0, 0, 0);

	set_next_app_state(APPSTATE_INIT_LOADING_MAIN_GAME);
	change_app_state();

	LOCK_GLOBALS(0);
	g_dwAppEvent = APPEVENT_START_LOGIN_ZONE;
	UNLOCK_GLOBALS(0);

	
#ifdef  DEBUG_MSG
	log_encrypt_message(1, "    GET_ZONE_INFO(zonename:%s, mapname:%s, addr:%s, port:%d, zonetype:%d)",
		info.cZone, info.cMapName, info.cAddr, info.dwPort, info.dwType);
#endif//DEBUG_MSG
	
    return  0;
}


static	SLONG   client_handle_get_character_info(DWORD wParam)
{
	TPOS_EVENT_GETCHARACTERINFO	info[4];
    int i;

	memcpy(info, (void*)wParam, sizeof(info));
	for(i=0; i<4; i++)
	{
		if(info[i].cMainName[0])
		{
			strcpy((char *)character_info[i].mainname, (const char *)info[i].cMainName);
			strcpy((char *)character_info[i].nickname, (const char *)info[i].cNickName);
			strcpy((char *)character_info[i].zone, (const char *)info[i].cZone);
			character_info[i].career = info[i].cCareer;
			character_info[i].sex = info[i].cSex;
			character_info[i].level = info[i].uhiLevel;
			character_info[i].country = info[i].cCountry;
			strcpy((char *)character_info[i].nobility, (const char *)info[i].cNobility);
			character_info[i].qqid = info[i].QQID;

			character_info[i].flag = 1;
		}

#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    GET_CHARACTER_INFO(index:%d, mainname:%s, zonename:%s, lv:%d)", 
        i, info[i].cMainName, info[i].cZone, info[i].uhiLevel);
#endif//DEBUG_MSG
    
	}

	// 如果目前不是選擇人物, 則進入到選擇人物的介面中.
	DWORD	dwState;
	if(g_dwAppState == APPSTATE_SHOW_SWAP_SCREEN)
		dwState = get_swap_screen_prev_app_state();
	else
		dwState = g_dwAppState;
	if(dwState != APPSTATE_SHOW_SELECT_CHARACTER)
	{
		set_next_app_state(APPSTATE_INIT_SELECT_CHARACTER);
		change_app_state();
	}
        
    
    return  0;
}



static	SLONG   client_handle_create_character_check_ok(DWORD wParam)
{
    set_next_app_state(APPSTATE_INIT_SET_CHAR_LOCATE);
    change_app_state();

#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    CREATE_CHARACTER_CHECK_OK");
#endif//DEBUG_MSG
    
    return  0;
}



static	SLONG   client_handle_create_character_ok(DWORD wParam)
{
    int iRet;
    
    clear_character_info();
    iRet = ClientRequestForCharacterInfo((char *)uilogin.account, BEGIN);
    
#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    CREATE_CHARACTER_OK");
#endif//DEBUG_MSG
    
    return  0;
}


static	SLONG   client_handle_create_character_final_ok(DWORD wParam)
{
    int iRet;
    
    clear_character_info();
    iRet = ClientRequestForCharacterInfo((char *)uilogin.account, BEGIN);
    
#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    CREATE_CHARACTER_FINAL_OK");
#endif//DEBUG_MSG
    
    return  0;
}


static	SLONG	client_handle_create_character_nameused(DWORD wParam)
{
	display_error_message((USTR*)ERRMSG_CHARACTER_NAME_USED, DISPLAY_MESSAGE_TO_SCREEN, screen_buffer);
	wait_key_time(' ', 80);

#ifdef	DEBUG_MSG
    log_encrypt_message(1, "    CREATE_CHARACTER_NAMEUSED");
#endif//DEBUG_MSG

	return	0;
}


static	SLONG	client_handle_create_character_fail(DWORD wParam)
{
	display_error_message((USTR*)ERRMSG_CREATE_CHARACTER_FAILED, DISPLAY_MESSAGE_TO_SCREEN, screen_buffer);
	wait_key_time(' ', 80);

#ifdef	DEBUG_MSG
    log_encrypt_message(1, "    CREATE_CHARACTER_FAIL");
#endif//DEBUG_MSG

	return	0;
}


static	SLONG	client_handle_create_character_final_fail(DWORD wParam)
{
	display_error_message((USTR*)ERRMSG_CREATE_CHARACTER_FAILED, DISPLAY_MESSAGE_TO_SCREEN, screen_buffer);
	wait_key_time(' ', 80);

#ifdef	DEBUG_MSG
    log_encrypt_message(1, "    CREATE_CHARACTER_FAIL");
#endif//DEBUG_MSG

	return	0;
}


static	SLONG   client_handle_delete_character_ok(DWORD wParam)
{
    int iRet;
    
    clear_character_info();
    iRet = ClientRequestForCharacterInfo((char *)uilogin.account, BEGIN);
    
#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    DELETE_CHARACTER_OK");
#endif//DEBUG_MSG
    
    return  0;
}


static	SLONG	client_handle_delete_character_fail(DWORD wParam)
{
	display_error_message((USTR*)ERRMSG_DELETE_CHARACTER_FAILED, DISPLAY_MESSAGE_TO_SCREEN, screen_buffer);
	wait_key_time(' ', 80);

#ifdef	DEBUG_MSG
    log_encrypt_message(1, "    DELETE_CHARACTER_OK");
#endif//DEBUG_MSG

	return	0;
}


static	SLONG   client_handle_zone_login_ok(DWORD wParam)
{
	TPOS_EVENT_ZONELOGINOK	info;
    int iRet;
    
	memcpy(&info, (void*)wParam, sizeof(info));

    LOCK_CHARACTER(0);
	InitAllZoneCharacters();
    clear_all_map_npc();
    UNLOCK_CHARACTER(0);

    LOCK_ITEM( 0 );
	InitZoneItem();
    UNLOCK_ITEM( 0 );

	g_lPlayerIndex = info.NpcIndex;

	apply_mycharacterdata_to_character_npc(g_lPlayerIndex, info.data);
    
#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    ZONE_LOGIN_OK(player:%d, career:%d, sex:%d, file:%d, dir:%d)",
		info.NpcIndex, info.data.Career, info.data.Sex, info.data.FileIndex, info.data.Dir);
#endif//DEBUG_MSG
    
    iRet = ClientRequestForPlayerList(BEGIN);
    
    return  0;
}


static	SLONG	client_handle_zone_login_fail(DWORD wParam)
{
	display_error_message((USTR*)ERRMSG_LOGIN_ZONE_SERVER_FAILED, DISPLAY_MESSAGE_TO_SCREEN, screen_buffer);
	wait_key_time(' ', 80);

	DWORD	dwState;
	if(g_dwAppState == APPSTATE_SHOW_SWAP_SCREEN)
		dwState = get_swap_screen_prev_app_state();
	else
		dwState = g_dwAppState;
    switch(dwState)
	{
	case APPSTATE_SHOW_SELECT_CHARACTER:
		selchar_data.on_linking = 0;
		break;
	default:
		break;
	}

#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    ZONE_LOGIN_FAIL");
#endif//DEBUG_MSG
    
    return  0;
}


static	SLONG	client_handle_zone_login_repeat(DWORD wParam)
{
	display_error_message((USTR*)ERRMSG_ZONE_LOGIN_REPEAT, DISPLAY_MESSAGE_TO_SCREEN, screen_buffer);
	wait_key_time(' ', 80);

#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    ZONE_LOGIN_REPEAT");
#endif//DEBUG_MSG
    
    return  0;
}


static	SLONG	client_handle_zone_login_errorid(DWORD wParam)
{
	display_error_message((USTR*)ERRMSG_ZONE_LOGIN_ERRORID, DISPLAY_MESSAGE_TO_SCREEN, screen_buffer);
	wait_key_time(' ', 80);

#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    ZONE_LOGIN_ERRORID");
#endif//DEBUG_MSG
    
    return  0;
}


static	SLONG	client_handle_zone_login_errorpw(DWORD wParam)
{
	display_error_message((USTR*)ERRMSG_ZONE_LOGIN_ERRORPW, DISPLAY_MESSAGE_TO_SCREEN, screen_buffer);
	wait_key_time(' ', 80);

#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    ZONE_LOGIN_ERRORPW");
#endif//DEBUG_MSG
    
    return  0;
}


static	SLONG	client_handle_zone_login_denied(DWORD wParam)
{
	display_error_message((USTR*)ERRMSG_ZONE_LOGIN_DENIED, DISPLAY_MESSAGE_TO_SCREEN, screen_buffer);
	wait_key_time(' ', 80);

#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    ZONE_LOGIN_DENIED");
#endif//DEBUG_MSG
    
    return  0;
}


static	SLONG	client_handle_zone_login_kicked(DWORD wParam)
{
	display_error_message((USTR*)ERRMSG_ZONE_LOGIN_KICKED, DISPLAY_MESSAGE_TO_SCREEN, screen_buffer);
	wait_key_time(' ', 80);

#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    ZONE_LOGIN_KICKED");
#endif//DEBUG_MSG
    
    return  0;
}


static	SLONG   client_handle_get_player_list(DWORD wParam)
{
	TPOS_EVENT_GETPLAYERLIST	info;
    
	memcpy(&info, (void*)wParam, sizeof(info));
	if(info.iIndex == END)
    {
#ifdef  DEBUG_MSG
        log_encrypt_message(1, "    GET_PLAYER_LIST...END");
#endif//DEBUG_MSG
        
        return  0;
    }
	else
	{
		// Jack, [1/14/2003]
		// Change for have been received mycharacterdata when received zoneloginok before.
		/*
		//當前接收到的是第 info.iIndex 個  Player 的資料.
		apply_list_player_info_to_character_npc(info);

		//與自己選擇的角色比對, 如果名稱相同, 則表示這個 Player 是自己.
		if( strcmp((const char*)g_szPlayerMainName, (const char *)info.cMainName) == 0 )
		{
			g_lPlayerIndex = info.iIndex;
		}
		*/
		// Skip my own for have been received my whole data before(LOGINZONEOK).
		if(g_lPlayerIndex != info.iIndex)
		{
			//當前接收到的是第 info.iIndex 個  Player 的資料.
			apply_list_player_info_to_character_npc(info);
		}
		
		ClientRequestForPlayerList(info.iIndex + 1);
	}

#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    GET_PLAYER_LIST(index:%d, name:%s, file_idx:%d, doingkind:%d)", 
        info.iIndex, info.cMainName, info.slFileIndex, info.slDoingKind);
#endif//DEBUG_MSG
    
    return  0;
}


static	SLONG   client_handle_player_join(DWORD wParam)
{
	TPOS_EVENT_PLAYERJOIN	info;
	USTR	rgb_data[35];
    SLONG   index;
	SLONG	i;

    memcpy(&info, (void*)wParam, sizeof(info));
	index = info.iIndex;
	if(index >= 0 && index < MAX_CHARACTER_PER_ZONE)
	{
		LOCK_CHARACTER(index);
		ClearOneCharacter(index);
		clear_one_game_npc(index);

		SetCharacterMainName(index, info.cMainName);
		SetCharacterFileIndex(index, info.slFileIndex);
		SetCharacterMoveSpeed(index, info.iMspeed);
		SetCharacterHp(index, info.iHp);
		SetCharacterMaxHp(index, info.iMaxHp);
		SetCharacterMp(index, info.iMp);
		SetCharacterMaxMp(index, info.iMaxMp);
		SetCharacterLevel(index, (UHINT)info.iLevel);
		SetCharacterColor(index, info.cColor);
		SetCharacterDoingKind(index, info.slDoingKind);
		SetCharacterSightRange(index, info.iSightRange);
		SetCharacterPosition(index, info.lX, info.lY, info.lZ);
		SetCharacterDir(index, info.cDir);
		SetCharacterBitState(index, info.ulBitState);
		SetCharacterDoingStep(index, 0);
		for(i=0; i<7; i++)
		{
			SetCharacterPartRGB(index, i, info.PartRGB[i]);
		}
		SetCharacterMainNameColor(index, info.MainNameColor);
		switch(g_dwZoneType)
		{
		case SAIL_NORMAL:
		case SAIL_NEWBIE:
		case SAIL_PK:
		case SAIL_FINDGOLD:
		case SAIL_BIRTH:
			SetCharacterOnTheSea(index, true);
			SetCharacterShipSailSize(index, info.slSailSize);
			SetCharacterShipWeight(index, info.slWeight);
			SetCharacterShipTurn(index, info.slTurn);
			//
			SetCharacterShipSpeedX(index, 0);
			SetCharacterShipSpeedY(index, 0);
			break;
		case CITY_NORMAL:
		case CITY_NEWBIE:
		case CITY_PK:
		case CITY_FINDGOLD:
		case CITY_BIRTH:
		case FIELD_NORMAL:
		case FIELD_NEWBIE:
		case FIELD_PK:
		case FIELD_FINDGOLD:
		case FIELD_BIRTH:
		default:
			SetCharacterOnTheSea(index, false);
			break;
		}

		for(i=0; i<7; i++)
		{
			rgb_data[i*5 + 0] = ((ARGB_DATA*)&info.PartRGB[i])->a;
			rgb_data[i*5 + 1] = ((ARGB_DATA*)&info.PartRGB[i])->r;
			rgb_data[i*5 + 2] = ((ARGB_DATA*)&info.PartRGB[i])->g;
			rgb_data[i*5 + 3] = ((ARGB_DATA*)&info.PartRGB[i])->b;
			rgb_data[i*5 + 4] = 0;
		}
		set_npc_rgb_scroll(index, (USTR*)rgb_data);

		active_map_npc(index);
		UNLOCK_CHARACTER(index);
	}

    USTR    msg[128];
    sprintf((char *)msg, GAMEMSG_PLAYER_JOIN, info.cMainName);
    add_game_message(GAMEMSG_TYPE_SYSTEM, (USTR*)msg);
    
#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    PLAYER_JOIN(index:%d, name:%s, file_idx:%d, dokind:%d)", 
        info.iIndex, info.cMainName, info.slFileIndex, info.slDoingKind);
#endif//DEBUG_MSG
    
    return  0;
}


static	SLONG   client_handle_player_exit(DWORD wParam)
{
	TPOS_EVENT_PLAYEREXIT	info;
	SLONG	index;
	char	name[32];
	
	memcpy(&info, (void*)wParam, sizeof(info));
    
    index = info.iIndex;
	if(index >= 0 && index < MAX_CHARACTER_PER_ZONE)
	{
		LOCK_CHARACTER(index);
		strcpy(name, GetCharacterMainName(index));
		ClearOneCharacter(index);
		del_map_npc(index);
		UNLOCK_CHARACTER(index);
		
		USTR    msg[128];
		sprintf((char *)msg, GAMEMSG_PLAYER_EXIT, name);
		add_game_message(GAMEMSG_TYPE_SYSTEM, (USTR*)msg);
		
#ifdef  DEBUG_MSG
		log_encrypt_message(1, "    PLAYER_EXIT(index:%d, name:%s)", index, name);
#endif//DEBUG_MSG
	}
	else
	{
#ifdef  DEBUG_MSG
		log_encrypt_message(1, "    PLAYER_EXIT(index:%d)", info.iIndex);
#endif//DEBUG_MSG
	}
    
    return  0;
}


static	SLONG   client_handle_get_public_talk(DWORD wParam)
{
	TPOS_EVENT_GETPUBLICTALK	info;
    char    talk[250];
    char    sender_name[32];
    
	memcpy(&info, (void*)wParam, sizeof(info));

    strcpy((char *)sender_name, (const char *)GetCharacterMainName(info.dwSendIndex));
    sprintf(talk,"%s : %s", sender_name, info.cMsg);
    game_chat.add(CHATEFF_WHITE, (USTR*)talk);
    client_add_npc_talk_msg(info.dwSendIndex, (USTR*)info.cMsg);
    
    if(info.lDoing_kind >= 0)
    {
        LOCK_CHARACTER(info.dwSendIndex);
        change_npc_doing(info.dwSendIndex, info.lDoing_kind, 0, 0, 0, 0, 0, 0);
        UNLOCK_CHARACTER(info.dwSendIndex);
    }
    
#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    GET_PUBLIC_TALK(%s:%s)", sender_name, info.cMsg);
#endif//DEBUG_MSG
    
    return  0;
}


static	SLONG   client_handle_sync_position(DWORD wParam)
{
    static	TPOS_SYNCMOVE sm[MAX_CHARACTER_PER_ZONE];
    SLONG   i;

	memcpy(sm, (void*)wParam, sizeof(sm));
    
    LOCK_CHARACTER(i);
    for(i=0; i<MAX_CHARACTER_PER_ZONE; i++)
    {
		SetCharacterPosition(i, sm[i].lX, sm[i].lY, 0);
    }
    UNLOCK_CHARACTER(i);
    
#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    SYNC_POSITION( Player: %d, %d ) ", 
                        sm[g_lPlayerIndex].lX, sm[g_lPlayerIndex].lY );
#endif//DEBUG_MSG
    
    return  0;
}


static	SLONG   client_handle_get_refresh(DWORD wParam)
{
	TPOS_EVENT_REFRESHFLAG	info;
	
	memcpy(&info, (void*)wParam, sizeof(info));
    
	DWORD	dwState;
	if(g_dwAppState == APPSTATE_SHOW_SWAP_SCREEN)
		dwState = get_swap_screen_prev_app_state();
	else
		dwState = g_dwAppState;
    if(dwState == APPSTATE_SHOW_MAIN_GAME)
    {
		// Jack, remark for cancel the heartbeat sync for test. [1/16/2003]
        //sync_heartbeat_data(info.dwHeartBeat);
    }
    
#ifdef  DEBUG_MSG
    //log_encrypt_message(1, "    GET_REFRESH(%d)", info.dwHeartBeat);
#endif//DEBUG_MSG
    
    return  0;
}


static	SLONG   client_handle_get_attack_switch(DWORD wParam)
{
	TPOS_EVENT_ATTACKSWITCH	info;
    
	memcpy(&info, (void*)wParam, sizeof(info));
    
    LOCK_CHARACTER(info.dwIndex);
    SetCharacterOnFightState(info.dwIndex, info.dwPk == ATTACK_ENABLED ? true : false);
    change_npc_doing(info.dwIndex, info.lDoing_kind, 0, 0, 0, 0, 0, 0);
    UNLOCK_CHARACTER(info.dwIndex);
    
    if((SLONG)info.dwIndex == g_lPlayerIndex)
    {
        add_game_message(GAMEMSG_TYPE_MYSELF, 
            info.dwPk == ATTACK_ENABLED ? (USTR*)GAMEMSG_PLAYER_FIGHT_ENABLED : (USTR*)GAMEMSG_PLAYER_FIGHT_DISABLED);
    }
    
#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    GET_ATTACK_SWITCH(%d, %d, %d)", info.dwIndex, info.dwPk, info.lDoing_kind);
#endif//DEBUG_MSG
        
    return  0;
}



static	SLONG   client_handle_get_bag_switch(DWORD wParam)
{
	TPOS_EVENT_BAGSWITCH	info;

	memcpy(&info, (void*)wParam, sizeof(info));

    switch(info.dwBag)
    {
    case OPEN_BAG:
        LOCK_CHARACTER(g_lPlayerIndex);
        SetCharacterBagOpened(g_lPlayerIndex, true);
        UNLOCK_CHARACTER(g_lPlayerIndex);
        direct_open_map_submenu(SUBMENU_ITEM);
        break;

    case CLOSE_BAG:
        LOCK_CHARACTER(g_lPlayerIndex);
        SetCharacterBagOpened(g_lPlayerIndex, false);
        UNLOCK_CHARACTER(g_lPlayerIndex);
        direct_close_map_submenu(SUBMENU_ITEM);
        break;
    }
    
#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    GET_BAG_SWITCH(%d)", info.dwBag);
#endif//DEBUG_MSG
    
    return  0;
    
}


static	SLONG   client_handle_get_change_mouse_skill(DWORD wParam)
{
	TPOS_EVENT_CHANGEMOUSESKILL	info;
    DWORD	last_magic;
    SLONG   set_successful, is_fight;
    
	memcpy(&info, (void*)wParam, sizeof(info));

    set_successful = false;
    switch(info.dwLeftRight)
    {
    case LEFT:
        LOCK_CHARACTER(g_lPlayerIndex);
        last_magic = GetCharacterLeftSkill(g_lPlayerIndex);
        if(last_magic != info.dwSkill)
        {
            SetCharacterLeftSkill(g_lPlayerIndex, (SHINT)info.dwSkill);
            set_successful = true;
        }
        UNLOCK_CHARACTER(g_lPlayerIndex);
        break;

    case RIGHT:
        LOCK_CHARACTER(g_lPlayerIndex);
        last_magic = GetCharacterRightSkill(g_lPlayerIndex);
        if(last_magic != info.dwSkill)
        {
            SetCharacterRightSkill(g_lPlayerIndex, (SHINT)info.dwSkill);
            InitCharacterRightSkillState(g_lPlayerIndex);
            set_successful = true;
        }
        UNLOCK_CHARACTER(g_lPlayerIndex);
        break;
    }

    if(set_successful)
    {
        switch(last_magic)
        {
        case MAGIC_NO_MUSE: //冥想
            LOCK_CHARACTER(g_lPlayerIndex);
            is_fight = IsCharacterOnFightState(g_lPlayerIndex);
            if(is_fight)
            {
                change_npc_doing(g_lPlayerIndex, DOING_KIND_IDLE, 0, 0, 0, 0, 0, info.dwSkill);
            }
            UNLOCK_CHARACTER(g_lPlayerIndex);
            break;

        case MAGIC_NO_DEFENCE:  //格擋
            LOCK_CHARACTER(g_lPlayerIndex);
            SetCharacterOnDefenceState(g_lPlayerIndex, FALSE);
            UNLOCK_CHARACTER(g_lPlayerIndex);
            break;

        default:
            break;
        }
        
        switch(info.dwSkill)
        {
        case MAGIC_NO_MUSE: //冥想
            LOCK_CHARACTER(g_lPlayerIndex);
            is_fight = IsCharacterOnFightState(g_lPlayerIndex);
            if(is_fight)
            {
                change_npc_doing(g_lPlayerIndex, DOING_KIND_MUSE, 0, 0, 0, 0, 0, info.dwSkill);
            }
            UNLOCK_CHARACTER(g_lPlayerIndex);
            break;

        case MAGIC_NO_DEFENCE:  //格擋
            LOCK_CHARACTER(g_lPlayerIndex);
            SetCharacterOnDefenceState(g_lPlayerIndex, TRUE);
            UNLOCK_CHARACTER(g_lPlayerIndex);
            break;

        default:
            break;
        }
        
    }

#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    GET_CHANGE_MOUSE_SKILL(%d,%d)", info.dwLeftRight, info.dwSkill);
#endif//DEBUG_MSG
    
    return  0;
}


static	SLONG   client_handle_get_character_default(DWORD wParam)
{
	TPOS_EVENT_GETCHARACTERDEFAULT	info;

	memcpy(&info, (void*)wParam, sizeof(info));
    
    set_new_character_career(info.cCareer);
    set_new_character_sex(info.cSex);
    set_new_character_color(info.cColor);
    set_new_character_strength(info.iStr);
    set_new_character_instinct(info.iIns);
    set_new_character_wit(info.iWis);
    set_new_character_luck(info.iLucky);
    set_new_character_hp(info.iHp);
    set_new_character_mp(info.iMp);
    
    set_next_app_state(APPSTATE_INIT_SET_CHAR_FACE);
    change_app_state();
    
#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    GET_CHARACTER_DEFAULT(career:%d, sex:%d, str:%d, ins:%d, wit:%d, luck:%d, hp:%d, mp:%d)", 
		info.cCareer, info.cSex, info.iStr, info.iIns, info.iWis, info.iLucky, info.iHp, info.iMp);
#endif//DEBUG_MSG
    
    return 0;
}


static	SLONG   client_handle_get_zone_now_weather(DWORD wParam)
{
	TPOS_EVENT_GETZONENOWWEATHER	info;
    
	memcpy(&info, (void*)wParam, sizeof(info));
    
    control_weather(WEATHER_RAIN, (info.dWeatherType & WEATHER_RAIN) ? WEATHER_STARTUP : WEATHER_STOP, info.dRainSize);
    control_weather(WEATHER_SNOW, (info.dWeatherType & WEATHER_SNOW) ? WEATHER_STARTUP : WEATHER_STOP, info.dSnowSize);
    control_weather(WEATHER_CLOUD, (info.dWeatherType & WEATHER_CLOUD) ? WEATHER_STARTUP : WEATHER_STOP, info.dCloudSize);
    control_weather(WEATHER_THUNDER, (info.dWeatherType & WEATHER_THUNDER) ? WEATHER_STARTUP : WEATHER_STOP, info.dThunderSize);
    control_weather(WEATHER_EARTHQUAKE, (info.dWeatherType & WEATHER_EARTHQUAKE) ? WEATHER_STARTUP : WEATHER_STOP, info.dEarthQuakeSize);
    control_wind(info.dWindDir, info.dWindSize);
    
#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    GET_ZONE_NOW_WEATHER(type:0x%0x, rain_size:%d, snow_size:%d, cloud_size:%d, "\
        "thunder_size:%d, earthquake_size:%d, wind_size:%d, wind_dir:%d)",
        info.dWeatherType, info.dRainSize, info.dSnowSize, info.dCloudSize, info.dThunderSize, info.dEarthQuakeSize,
        info.dWindSize, info.dWindDir);
#endif//DEBUG_MSG
    
    return  0;
}



static	SLONG   client_handle_init_zone_weather(DWORD wParam)
{
	TPOS_EVENT_INITZONEWEATHER	info;

    memcpy(&info, (void*)wParam, sizeof(info));

    control_weather(WEATHER_RAIN, (info.dWeatherType & WEATHER_RAIN) ? WEATHER_STARTUP : WEATHER_STOP, info.dRainSize);
    control_weather(WEATHER_SNOW, (info.dWeatherType & WEATHER_SNOW) ? WEATHER_STARTUP : WEATHER_STOP, info.dSnowSize);
    control_weather(WEATHER_CLOUD, (info.dWeatherType & WEATHER_CLOUD) ? WEATHER_STARTUP : WEATHER_STOP, info.dCloudSize);
    control_weather(WEATHER_THUNDER, (info.dWeatherType & WEATHER_THUNDER) ? WEATHER_STARTUP : WEATHER_STOP, info.dThunderSize);
    control_weather(WEATHER_EARTHQUAKE, (info.dWeatherType & WEATHER_EARTHQUAKE) ? WEATHER_STARTUP : WEATHER_STOP, info.dEarthQuakeSize);
    control_wind(info.dWindDir, info.dWindSize);
    
	// ZONE內全部資料接收完畢, 開始進入遊戲.
	set_next_app_state(APPSTATE_INIT_MAIN_GAME);
	change_app_state();

	LOCK_GLOBALS(0);
	g_dwAppEvent = APPEVENT_START_PLAY_MAINGAME;
	UNLOCK_GLOBALS(0);
    
    USTR    msg[128];
    sprintf((char *)msg, GAMEMSG_ENTER_ZONE, g_szPlayerZone);
    add_game_message(GAMEMSG_TYPE_MYSELF, (USTR*)msg);
    
#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    INIT_ZONE_WEATHER(type:0x%0x, rain_size:%d, snow_size:%d, cloud_size:%d, "\
        "thunder_size:%d, earthquake_size:%d, wind_size:%d, wind_dir:%d)",
        info.dWeatherType, info.dRainSize, info.dSnowSize, info.dCloudSize, info.dThunderSize, info.dEarthQuakeSize,
        info.dWindSize, info.dWindDir);
#endif//DEBUG_MSG
    
    return  0;
}



static	SLONG   client_handle_get_change_map(DWORD wParam)
{
	TPOS_EVENT_GETCHANGEMAP	info;

    memcpy(&info, (void*)wParam, sizeof(info));

	//在此保存玩家的ZONE, MAP. 當玩家切換地圖時, 可能需要用到(比如先載地圖).
	strcpy((char *)g_szPlayerZone, (const char *)info.cZoneName);
	strcpy((char *)g_szPlayerMap, (const char *)info.cMapName);
	g_dwZoneType = info.dwType;
	
	store_change_map_data((USTR*)info.cZoneName, (USTR*)info.cMapName, (USTR*)info.cAddr, 
		(SLONG)info.dwPort, info.lX, info.lY, info.lZ, (SLONG)info.cDir);

	set_next_app_state(APPSTATE_INIT_CHANGEMAP_LOADING);
	change_app_state();
    
#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    GET_CHANGE_MAP(zone:%s, map:%s, addr:%s, port:%d, x:%d, y:%d, z:%d, dir:%d, zonetype:%d)", 
        info.cZoneName, info.cMapName, info.cAddr, info.dwPort, info.lX, info.lY, info.lZ, info.cDir, info.dwType);
#endif//DEBUG_MSG
    
    return  0;
}


static	SLONG   client_handle_start_change_map(DWORD wParam)
{
	// 設置應用程式的事件為開始切換區域, 待 SHOW_CHANGEMAP_LOAD 的 REFRESH 獲取
	// 到該事件後作對應的處理.

	LOCK_GLOBALS(0);
	g_dwAppEvent = APPEVENT_START_CHANGE_ZONE;
	UNLOCK_GLOBALS(0);

#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    START_CHANGE_MAP");
#endif//DEBUG_MSG
    
    return  0;
}


static	SLONG   client_handle_get_player_skill(DWORD wParam)
{
	TPOS_EVENT_GETPLAYERSKILL	info;
	SLONG	i;

    memcpy(&info, (void*)wParam, sizeof(info));

    LOCK_CHARACTER(g_lPlayerIndex);
    ClearCharacterSkills(g_lPlayerIndex);
    for(i=0; i<MAX_CHARACTER_SKILLS; i++)
    {
        SetCharacterSkillNo(g_lPlayerIndex, i, (SLONG)info.SkillNo[i]);
        SetCharacterSkillLevel(g_lPlayerIndex, i, (UHINT)info.SkillLevel[i]);
    }
    UNLOCK_CHARACTER(g_lPlayerIndex);
    
#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    GET_PLAYER_SKILL("\
        "%d,%d,%d,%d,%d,%d,%d,%d,"\
        "%d,%d,%d,%d,%d,%d,%d,%d,"\
        "%d,%d,%d,%d,%d,%d,%d,%d,"\
        "%d,%d,%d,%d,%d,%d,%d,%d)",
        info.SkillNo[0], info.SkillNo[1], info.SkillNo[2], info.SkillNo[3],
        info.SkillNo[4], info.SkillNo[5], info.SkillNo[6], info.SkillNo[7],
        info.SkillNo[8], info.SkillNo[9], info.SkillNo[10], info.SkillNo[11],
        info.SkillNo[12], info.SkillNo[13], info.SkillNo[14], info.SkillNo[15],
        info.SkillNo[16], info.SkillNo[17], info.SkillNo[18], info.SkillNo[19],
        info.SkillNo[20], info.SkillNo[21], info.SkillNo[22], info.SkillNo[23],
        info.SkillNo[24], info.SkillNo[25], info.SkillNo[26], info.SkillNo[27],
        info.SkillNo[28], info.SkillNo[29], info.SkillNo[30], info.SkillNo[31]
        );
#endif//DEBUG_MSG
    
    return  0;
}


static	SLONG   client_handle_get_player_quick_skillitem(DWORD wParam)
{
	TPOS_EVENT_GETPLAYERQUICKSKILLITEM	info;
	SLONG	i;

    memcpy(&info, (void*)wParam, sizeof(info));

	LOCK_CHARACTER(g_lPlayerIndex);
	SetCharacterLeftSkill(g_lPlayerIndex, info.LeftSkillNo);
	SetCharacterRightSkill(g_lPlayerIndex, info.RightSkillNo);
	for(i=0; i<MAX_CHARACTER_FN_SKILLS; i++)
	{
		SetCharacterFnSkill(g_lPlayerIndex, i, info.FnSkillNo[i], info.FnSkillHand[i]);
	}
	// Jack, ??? [1/11/2003]
	//DWORD	SashItem[MAX_CHARACTER_SASH_ITEMS];		//腰包內物品
	UNLOCK_CHARACTER(g_lPlayerIndex);
	
    
#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    GET_PLAYER_QUICK_SKILLITEM(L:%d, R:%d)", info.LeftSkillNo, info.RightSkillNo);
#endif//DEBUG_MSG
    
    return  0;
}


static	SLONG   client_handle_system_message(DWORD wParam)
{
	TPOS_EVENT_SYSTEMMESSAGE	info;
    
	memcpy(&info, (void*)wParam, sizeof(info));

    if(0 != info.cMsg[0])
    {
        add_system_message((USTR*)info.WorldName, (USTR*)info.cMsg);
    }
    
#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    SYSTEM_MESSAGE(%s:%s)", info.WorldName, info.cMsg);
#endif//DEBUG_MSG

    return  0;
}


static	SLONG   client_handle_change_npc_doing(DWORD wParam)
{
	TPOS_EVENT_GETCHANGENPCDOING	info;
    SLONG   src_attack_x, src_attack_y;
    
	memcpy(&info, (void*)wParam, sizeof(info));
    
    switch(info.DoingKind)
    {
    case DOING_KIND_IDLE:   //待機
        {
            switch(info.d4)
            {
            case 0: //do nothing
                LOCK_CHARACTER(info.Index);
                change_npc_doing(info.Index, info.DoingKind, info.DoingStep, info.d1, info.d2, info.d3, 0, info.d5);
                UNLOCK_CHARACTER(info.Index);
                break;

            case 1: //init rhand magic state
                LOCK_CHARACTER(info.Index);;
                change_npc_doing(info.Index, info.DoingKind, info.DoingStep, info.d1, info.d2, info.d3, 0, info.d5);
                InitCharacterRightSkillState(info.Index);
                UNLOCK_CHARACTER(info.Index);;
                break;
            }
        }
        break;
        
    case DOING_KIND_BEATED:         //被擊
    case DOING_KIND_DOWN_AND_OUT:   //被擊倒
        LOCK_CHARACTER(info.Index);
        SetCharacterHp(info.Index, (UHINT)info.d2);
        src_attack_x = info.d3;
        src_attack_y = info.d4;
        change_npc_doing(info.Index, info.DoingKind, info.DoingStep, info.d1, 0, src_attack_x, src_attack_y, info.d5);
        UNLOCK_CHARACTER(info.Index);
        break;

    case DOING_KIND_DEAD:   //被擊斃
        LOCK_CHARACTER(info.Index);
        SetCharacterHp(info.Index, 0);
        SetCharacterDeadTicks(info.Index, (UHINT)info.d2);
        src_attack_x = info.d3;
        src_attack_y = info.d4;
        change_npc_doing(info.Index, info.DoingKind, info.DoingStep, info.d1, 0, src_attack_x, src_attack_y, info.d5);
        UNLOCK_CHARACTER(info.Index);
        break;

    case DOING_KIND_SPOWER: //蓄力
        LOCK_CHARACTER(info.Index);
        change_npc_doing(info.Index, info.DoingKind, info.DoingStep, info.d1, info.d2, info.d3, info.d4, info.d5);
        SetCharacterRightHandMagicStartSpower(info.Index);
        UNLOCK_CHARACTER(info.Index);
        break;

    case DOING_KIND_CLASH:  //衝撞
        LOCK_CHARACTER(info.Index);
        change_npc_doing(info.Index, info.DoingKind, info.DoingStep, info.d1, info.d2, info.d3, info.d4, info.d5);
        InitCharacterRightSkillState(info.Index);
        UNLOCK_CHARACTER(info.Index);
        break;
        
    default:
        LOCK_CHARACTER(0);
        change_npc_doing(info.Index, info.DoingKind, info.DoingStep, info.d1, info.d2, info.d3, info.d4, info.d5);
        UNLOCK_CHARACTER(0);
        break;
    }
    
    
#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    CHANGE_NPC_DOING(%d, %d, %d, %d, %d, %d, %d, %d)",
        info.Index, info.DoingKind, info.DoingStep, info.d1, info.d2, info.d3, info.d4, info.d5);
#endif//DEBUG_MSG
    
    return  0;
}

static	SLONG   client_handle_change_npc_aiblock(DWORD wParam)
{
	TPOS_EVENT_NOTIFYNPCAIBLOCK	info;
    //    
	memcpy(&info, (void*)wParam, sizeof(info));
    //
    LOCK_CHARACTER(info.Index);
    AIBlockChange(info.Index,info.AIBlock);
    SetCharacterDestID(info.Index,info.DestNpcNo);
    SetCharacterDestPosition(info.Index, info.X, info.Y, info.Z);
    SetCharacterDoingMagic(info.Index, info.SkillNo);
    UNLOCK_CHARACTER(info.Index);
    //
#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    CHANGE_NPC_AI_BLOCK(%d, %d, %d, %d, %d, %d, %d)",
        info.Index, info.AIBlock,  info.DestNpcNo, info.X, info.Y, info.Z, info.SkillNo);
#endif//DEBUG_MSG    
    return 0;
}
static	SLONG   client_handle_create_magic_area(DWORD wParam)
{
    TPOS_EVENT_NOTIFYCREATEMAGICAREA   info;
    //
	memcpy(&info, (void*)wParam, sizeof(info));
    //
    if (info.Type)
        add_magic_area(info.X, info.Y, info.Dir, info.NpcNo, info.MagicNo, 0);
    else
        delete_magic_area(info.NpcNo, info.MagicNo);
#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    NOTIFY_CREATE_MAGIC_AREA(%d, %d, %d, %d, %d, %d)",
                        info.Type, info.Dir,  info.X, info.Y, info.NpcNo, info.MagicNo);
#endif//DEBUG_MSG    
    return 0;
    
}

static	SLONG   client_handle_get_npc_relive(DWORD wParam)
{
	TPOS_EVENT_GETNPCRELIVE	info;
    
	memcpy(&info, (void*)wParam, sizeof(info));

	LOCK_CHARACTER(info.Index);
	// Defferent with PlayerList, only clear images associated datas here.
	clear_one_game_npc(info.Index);

	SetCharacterHp(info.Index, info.iHp);
	SetCharacterMaxHp(info.Index, info.iHp);
	SetCharacterMp(info.Index, info.iMp);
	SetCharacterMaxMp(info.Index, info.iMp);
	SetCharacterPosition(info.Index, info.lX, info.lY, info.lZ);
	SetCharacterDir(info.Index, info.cDir);
	// Jack, TODO [1/11/2003]
	// Need much more data ...
	SetCharacterDoingKindStep(info.Index, info.slDoingKind, 0);
	active_map_npc(info.Index);
	UNLOCK_CHARACTER(info.Index);

#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    GET_NPC_RELIVE(index:%d, dokind:%d, hp:%d)", 
        info.Index, info.slDoingKind, info.iHp);
#endif//DEBUG_MSG
    
    return  0;
}


static	SLONG   client_handle_update_npc_doing(DWORD wParam)
{
    SLONG   step;
    TPOS_EVENT_GETCHANGENPCDOING info;

	memcpy(&info, (void*)wParam, sizeof(info));

    switch(info.DoingKind)
    {
    case DOING_KIND_SEQUENTIAL_ATTACK_NPC:  //連擊
        LOCK_CHARACTER(info.Index);
        step = GetCharacterSequentialStep(info.Index);
        SetCharacterSequentialStep(info.Index, (step+1));
        UNLOCK_CHARACTER(info.Index);
        break;
    }

#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    UPDATE_NPC_DOING(%d, %d, %d, %d, %d, %d, %d, %d)",
        info.Index, info.DoingKind, info.DoingStep, info.d1, info.d2, info.d3, info.d4, info.d5);
#endif//DEBUG_MSG

    return  0;
}


static	SLONG   client_handle_set_npc_hp(WPARAM wParam)
{
	TPOS_EVENT_SETNPCHP	info;
	SLONG	npc_no;

    memcpy(&info, (void*)wParam, sizeof(info));
	npc_no = info.Index;
    if(npc_no >= 0 && npc_no < MAX_CHARACTER_PER_ZONE)
    {
        LOCK_CHARACTER(npc_no);
        SetCharacterHp(npc_no, info.iHp);
        UNLOCK_CHARACTER(npc_no);
    }

#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    SET_NPC_HP(%d, %d)", info.Index, info.iHp);
#endif//DEBUG_MSG

    return  0;
}


static	SLONG   client_handle_set_npc_exp(WPARAM wParam)
{
    TPOS_EVENT_SETNPCEXP	info;
    SLONG   npc_no;

    memcpy(&info, (void*)wParam, sizeof(info));
	npc_no = info.Index;
    if(npc_no >= 0 && npc_no < MAX_CHARACTER_PER_ZONE)
    {
        LOCK_CHARACTER(npc_no);
        SetCharacterExp(npc_no, info.Exp);
        UNLOCK_CHARACTER(npc_no);
    }

#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    SET_NPC_EXP(%d, %d)", info.Index, info.Exp);
#endif//DEBUG_MSG

    return  0;
}
//
static	SLONG   client_handle_set_npc_skill(WPARAM wParam)
{
    //
    TPOS_EVENT_SETNPCSKILL  info;
    SLONG   npc_no;
    //
    memcpy(&info, (void*)wParam, sizeof(info));
    npc_no = (SLONG)info.NpcNo;    
    //
    LOCK_CHARACTER(npc_no);    
    SetCharacterSkillNo(npc_no, info.SkillIndex, info.SkillNo);
    SetCharacterSkillLevel(npc_no, info.SkillIndex, 0);
    UNLOCK_CHARACTER(npc_no);    
#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    SET_NPC_SKILL(%d, %d, %d)", info.NpcNo, info.SkillIndex, info.SkillNo);
#endif//DEBUG_MSG    
    return  0;
}


static	SLONG   client_handle_npc_level_up(WPARAM wParam)
{
    TPOS_EVENT_NPCLEVELUP info;
    SLONG   npc_no;

    memcpy(&info, (void*)wParam, sizeof(info));
    npc_no = info.Index;
    if(npc_no >= 0 && npc_no < MAX_CHARACTER_PER_ZONE)
    {
        LOCK_CHARACTER(npc_no);
		SetCharacterLevel(npc_no, info.Level);
        SetCharacterHp(npc_no, info.MaxHp);
        SetCharacterMaxHp(npc_no, info.MaxHp);
        SetCharacterMp(npc_no, info.MaxMp);
        SetCharacterMaxMp(npc_no, info.MaxMp);
		SetCharacterPropertyPoint(npc_no, info.AttribPoint);
        SetCharacterExp(npc_no, info.Exp);
        SetCharacterNextExp(npc_no, info.NextExp);
        UNLOCK_CHARACTER(npc_no);

		if(npc_no == g_lPlayerIndex)
		{
			USTR    info[128];
			sprintf((char *)info, "%s", TEXTMSG_LEVEL_UPGRADE);
			add_game_message(GAMEMSG_TYPE_MYSELF, (USTR *)info);
		}
    }

#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    NPC_LEVEL_UP(IDX:%d, LV:%d, HP:%d, MP:%d, AP:%d, EXP:%d, NEXTEXP:%d)", 
        info.Index, info.Level, info.MaxHp, info.MaxMp, info.AttribPoint, info.Exp, info.NextExp);
#endif//DEBUG_MSG

    return  0;
}


static	SLONG   client_handle_set_npc_upgrade_base_data(WPARAM wParam)
{
	TPOS_EVENT_SETNPCUPGRADEBASEDATA	info;

    memcpy(&info, (void*)wParam, sizeof(info));

	LOCK_CHARACTER(g_lPlayerIndex);
	switch(info.update_type)
	{
	case UPDATE_NPC_BASE_STRENGTH:
		SetCharacterFinalStr(g_lPlayerIndex, (UHINT)info.value);
		SetCharacterPropertyPoint(g_lPlayerIndex, (UHINT)info.rest_point);
		break;
	case UPDATE_NPC_BASE_INSTINCT:
		SetCharacterFinalIns(g_lPlayerIndex, (UHINT)info.value);
		SetCharacterPropertyPoint(g_lPlayerIndex, (UHINT)info.rest_point);
		break;
	case UPDATE_NPC_BASE_WIT:
		SetCharacterFinalWit(g_lPlayerIndex, (UHINT)info.value);
		SetCharacterPropertyPoint(g_lPlayerIndex, (UHINT)info.rest_point);
		break;
	case UPDATE_NPC_BASE_LUCK:
		SetCharacterFinalLucky(g_lPlayerIndex, (UHINT)info.value);
		SetCharacterPropertyPoint(g_lPlayerIndex, (UHINT)info.rest_point);
		break;
	}
	SetCharacterFinalAtt(g_lPlayerIndex, info.att);
	SetCharacterFinalDefence(g_lPlayerIndex, info.defence);
	SetCharacterMaxHp(g_lPlayerIndex, info.max_hp);
	SetCharacterHp(g_lPlayerIndex, info.hp);
	SetCharacterMaxMp(g_lPlayerIndex, info.max_mp);
	SetCharacterMp(g_lPlayerIndex, info.mp);
	UNLOCK_CHARACTER(g_lPlayerIndex);

#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    SET_NPC_UPGRADE_BASE_DATA(type:%d, data:%d, rest_point:%d, att:%d, def:%d, "
		"hp:%d/%d, mp:%d/%d )", 
        info.update_type, info.value, info.rest_point, info.att, info.defence, info.hp, info.max_hp, 
		info.mp, info.max_mp);
#endif//DEBUG_MSG

    return  0;
}



static	SLONG	client_handle_prepare_player_exit_game_ok(DWORD wParam)
{
	int	iRet, index;

	iRet = ClientLogoutZone();
	if(iRet == DLL_OK)
	{
		index = sws_data.start_index + sws_data.select_index;
		
		// ZZH, [2002.12.10 21:05]
		qq_clear();
		if(index >= 0 && index < max_world_info)
		{
			log_error(1, "debug: start login world: addr=%s, port=%d", world_info[index].addr, world_info[index].port);
			iRet = ClientLoginWorld(g_hWndGameEvent, (char *)world_info[index].addr, (int)world_info[index].port,
				(char *)uilogin.account, (char *)uilogin.password, POS_CLIENT_VERSION);
			log_error(1, "debug: login world result:%d", iRet);
		}
	}
	
#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    PRPARE_PLAYER_EXIT_GAME_OK" );
#endif//DEBUG_MSG

	return	0;
}


static	SLONG   client_handle_sea_sync_position(WPARAM wParam)
{
    TPOS_SYNCSEAMOVE sm[MAX_CHARACTER_PER_ZONE];
    SLONG   i;
	SLONG	degree_dir, x, y;
	SLONG	speed_x, speed_y;
    
	//sm = (TPOS_SYNCSEAMOVE *)wParam;
	memcpy(sm, (void*)wParam, sizeof(sm));
    
    for(i=0; i<MAX_CHARACTER_PER_ZONE; i++)
    {
		DecodeSeaNpcSyncPosition(sm[i].X, sm[i].Y, sm[i].Z, degree_dir, x, y, speed_x, speed_y);

		LOCK_CHARACTER(i);
		SetCharacterPosition(i, x, y, 0);
		SetCharacterShipSpeedX(i, speed_x);
		SetCharacterShipSpeedY(i, speed_y);
		SetCharacterShipDegreeDir(i, degree_dir);
		UNLOCK_CHARACTER(i);
    }
    
#ifdef  DEBUG_MSG
    //log_encrypt_message(1, "    SEA_SYNC_POSITION()");
#endif//DEBUG_MSG
    
    return  0;
}

static	SLONG	client_handle_notify_set_hand_quick_skill(WPARAM wParam)
{
	TPOS_EVENT_SETHANDQUICKSKILL	info;

	memcpy(&info, (void*)wParam, sizeof(info));
	SetupCharacterHandQuickSkill(g_lPlayerIndex, info.QuickIndex, info.Hand, info.SkillNo);

#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    NOTIFY_SET_HAND_QUICK_SKILL(quick:%d, hand:%c, skill:%d)",
		info.QuickIndex, info.Hand == LEFT ? 'L' : 'R', info.SkillNo);
#endif//DEBUG_MSG

	return	0;
}


static	SLONG	client_handle_notify_add_map_item(WPARAM wParam)
{
	TPOS_EVENT_NOTIFYADDMAPITEM	info;

	memcpy(&info, (void*)wParam, sizeof(info));

	LOCK_ITEM(0);
	AddZoneItem(info.X, info.Y, "", &info.Item);
	UNLOCK_ITEM(0);

#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    NOTIFY_ADD_MAP_ITEM(x:%d, y:%d, base:%d)", info.X, info.Y, info.Item.BaseID);
#endif//DEBUG_MSG

	return	0;
}

static	SLONG	client_handle_notify_delete_map_item(WPARAM wParam)
{
	TPOS_EVENT_NOTIFYDELETEMAPITEM	info;
	//SLONG		index;
	//TPOS_ITEM	item;

	memcpy(&info, (void*)wParam, sizeof(info));

	// Jack,  [1/17/2003]
	// If you want to delete zone item directly, just call this.
	///*
	LOCK_ITEM(0);
	DeleteZoneItem(info.X, info.Y);
	UNLOCK_ITEM(0);
	//*/

	/*
	LOCK_ITEM(0);
	index = CatchZoneItem(info.X, info.Y, &item);
	if(index >= 0)
	{
		open_and_disappear_game_item(index, -1);
	}
	UNLOCK_ITEM(0);
	*/

#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    NOTIFY_DELETE_MAP_ITEM(x:%d, y:%d)", info.X, info.Y);
#endif//DEBUG_MSG

	return	0;
}

static	SLONG	client_handle_notify_set_onmouse_item(WPARAM wParam)
{
	TPOS_EVENT_NOTIFYSETONMOUSEITEM	info;

	memcpy(&info, (void*)wParam, sizeof(info));

	LOCK_ITEM(0);
	SetCharacterOnMouseItem(g_lPlayerIndex, &info.Item);
	UNLOCK_ITEM(0);

#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    NOTIFY_SET_ONMOUSE_ITEM(base:%d)", info.Item.BaseID);
#endif//DEBUG_MSG

	return	0;
}

static	SLONG	client_handle_notify_set_bag_item(WPARAM wParam)
{
	TPOS_EVENT_NOTIFYSETBAGITEM	info;

	memcpy(&info, (void*)wParam, sizeof(info));

	LOCK_ITEM(0);
	SetCharacterBagItem(g_lPlayerIndex, info.BagIndex, &info.Item);
	UNLOCK_ITEM(0);

#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    NOTIFY_SET_BAG_ITEM(idx:%d, base:%d)", info.BagIndex, info.Item.BaseID);
#endif//DEBUG_MSG

	return	0;
}

static	SLONG	client_handle_notify_set_head_item(WPARAM wParam)
{
	TPOS_EVENT_NOTIFYSETHEADITEM	info;

	memcpy(&info, (void*)wParam, sizeof(info));

	LOCK_ITEM(0);
	SetCharacterEquipHead(g_lPlayerIndex, &info.Item);
	UNLOCK_ITEM(0);

#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    NOTIFY_SET_HEAD_ITEM(base:%d)", info.Item.BaseID);
#endif//DEBUG_MSG

	return	0;
}

static	SLONG	client_handle_notify_set_neck_item(WPARAM wParam)
{
	TPOS_EVENT_NOTIFYSETNECKITEM	info;

	memcpy(&info, (void*)wParam, sizeof(info));

	LOCK_ITEM(0);
	SetCharacterEquipNeck(g_lPlayerIndex, &info.Item);
	UNLOCK_ITEM(0);

#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    NOTIFY_SET_NECK_ITEM(base:%d)", info.Item.BaseID);
#endif//DEBUG_MSG

	return	0;
}

static	SLONG	client_handle_notify_set_body_item(WPARAM wParam)
{
	TPOS_EVENT_NOTIFYSETBODYITEM	info;

	memcpy(&info, (void*)wParam, sizeof(info));

	LOCK_ITEM(0);
	SetCharacterEquipBody(g_lPlayerIndex, &info.Item);
	UNLOCK_ITEM(0);

#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    NOTIFY_SET_BODY_ITEM(base:%d)", info.Item.BaseID);
#endif//DEBUG_MSG

	return	0;
}

static	SLONG	client_handle_notify_set_waist_item(WPARAM wParam)
{
	TPOS_EVENT_NOTIFYSETWAISTITEM	info;

	memcpy(&info, (void*)wParam, sizeof(info));

	LOCK_ITEM(0);
	SetCharacterEquipWaist(g_lPlayerIndex, &info.Item);
	UNLOCK_ITEM(0);

#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    NOTIFY_SET_WAIST_ITEM(base:%d)", info.Item.BaseID);
#endif//DEBUG_MSG

	return	0;
}

static	SLONG	client_handle_notify_set_glove_item(WPARAM wParam)
{
	TPOS_EVENT_NOTIFYSETGLOVEITEM	info;

	memcpy(&info, (void*)wParam, sizeof(info));

	LOCK_ITEM(0);
	SetCharacterEquipGlove(g_lPlayerIndex, &info.Item);
	UNLOCK_ITEM(0);

#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    NOTIFY_SET_GLOVE_ITEM(base:%d)", info.Item.BaseID);
#endif//DEBUG_MSG

	return	0;
}

static	SLONG	client_handle_notify_set_weapon_item(WPARAM wParam)
{
	TPOS_EVENT_NOTIFYSETWEAPONITEM	info;

	memcpy(&info, (void*)wParam, sizeof(info));

	LOCK_ITEM(0);
	SetCharacterEquipWeapon(g_lPlayerIndex, &info.Item);
	UNLOCK_ITEM(0);

#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    NOTIFY_SET_WEAPON_ITEM(base:%d)", info.Item.BaseID);
#endif//DEBUG_MSG

	return	0;
}

static	SLONG	client_handle_notify_set_wrist_item(WPARAM wParam)
{
	TPOS_EVENT_NOTIFYSETWRISTITEM	info;

	memcpy(&info, (void*)wParam, sizeof(info));

	LOCK_ITEM(0);
	SetCharacterEquipWrist(g_lPlayerIndex, &info.Item);
	UNLOCK_ITEM(0);

#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    NOTIFY_SET_WRIST_ITEM(base:%d)", info.Item.BaseID);
#endif//DEBUG_MSG

	return	0;
}

static	SLONG	client_handle_notify_set_feet_item(WPARAM wParam)
{
	TPOS_EVENT_NOTIFYSETFEETITEM	info;

	memcpy(&info, (void*)wParam, sizeof(info));

	LOCK_ITEM(0);
	SetCharacterEquipFeet(g_lPlayerIndex, &info.Item);
	UNLOCK_ITEM(0);

#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    NOTIFY_SET_FEET_ITEM(base:%d)", info.Item.BaseID);
#endif//DEBUG_MSG

	return	0;
}

static	SLONG	client_handle_notify_set_othera_item(WPARAM wParam)
{
	TPOS_EVENT_NOTIFYSETOTHERAITEM	info;

	memcpy(&info, (void*)wParam, sizeof(info));

	LOCK_ITEM(0);
	SetCharacterEquipOtherA(g_lPlayerIndex, &info.Item);
	UNLOCK_ITEM(0);

#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    NOTIFY_SET_OTHERA_ITEM(base:%d)", info.Item.BaseID);
#endif//DEBUG_MSG

	return	0;
}

static	SLONG	client_handle_notify_set_otherb_item(WPARAM wParam)
{
	TPOS_EVENT_NOTIFYSETOTHERBITEM	info;

	memcpy(&info, (void*)wParam, sizeof(info));

	LOCK_ITEM(0);
	SetCharacterEquipOtherB(g_lPlayerIndex, &info.Item);
	UNLOCK_ITEM(0);

#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    NOTIFY_SET_OTHERB_ITEM(base:%d)", info.Item.BaseID);
#endif//DEBUG_MSG

	return	0;
}

static	SLONG	client_handle_notify_set_otherc_item(WPARAM wParam)
{
	TPOS_EVENT_NOTIFYSETOTHERCITEM	info;

	memcpy(&info, (void*)wParam, sizeof(info));

	LOCK_ITEM(0);
	SetCharacterEquipOtherC(g_lPlayerIndex, &info.Item);
	UNLOCK_ITEM(0);

#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    NOTIFY_SET_OTHERC_ITEM(base:%d)", info.Item.BaseID);
#endif//DEBUG_MSG

	return	0;
}

static	SLONG	client_handle_notify_set_sash_item(WPARAM wParam)
{
	TPOS_EVENT_NOTIFYSETSASHITEM	info;

	memcpy(&info, (void*)wParam, sizeof(info));

	LOCK_ITEM(0);
	SetCharacterSashItem(g_lPlayerIndex, info.SashIndex, &info.Item);
	UNLOCK_ITEM(0);

#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    NOTIFY_SET_SASH_ITEM(idx:%d, base:%d)", info.SashIndex, info.Item.BaseID);
#endif//DEBUG_MSG

	return	0;
}

static	SLONG	client_handle_notify_set_trans_item(WPARAM wParam)
{
	TPOS_EVENT_NOTIFYSETTRANSITEM	info;

	memcpy(&info, (void*)wParam, sizeof(info));

	LOCK_ITEM(0);
	SetCharacterTransItem(g_lPlayerIndex, info.TransIndex, &info.Item);
	UNLOCK_ITEM(0);

#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    NOTIFY_SET_TRANS_ITEM(idx:%d, base:%d)", info.TransIndex, info.Item.BaseID);
#endif//DEBUG_MSG

	return	0;
}

static	SLONG	client_handle_notify_set_treasure_item(WPARAM wParam)
{
	TPOS_EVENT_NOTIFYSETTREASUREITEM	info;

	memcpy(&info, (void*)wParam, sizeof(info));

	LOCK_ITEM(0);
	SetCharacterTreasureItem(g_lPlayerIndex, &info.Item);
	UNLOCK_ITEM(0);

#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    NOTIFY_SET_TREASURE_ITEM(base:%d)", info.Item.BaseID);
#endif//DEBUG_MSG

	return	0;
}

static	SLONG	client_handle_notify_npc_talk(WPARAM wParam)
{
	TPOS_EVENT_NOTIFYNPCTALK	info;
	SLONG	i;

	memcpy(&info, (void*)wParam, sizeof(info));

	close_last_event_ui();
	clear_game_talk();
	set_game_talk_offer_npc(info.TargetNPCIndex);
	set_game_talk_next_proc(info.NextProc);
	for(i=0; i<5; i++)
	{
		if(info.Msg[i][0])
		{
			add_game_talk_text((char*)info.Msg[i]);
		}
	}
	open_event_ui(UI_TYPE_GAME_TALK);

#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    NOTIFY_NPC_TALK(npc:%d)", info.TargetNPCIndex);
	for(i=0; i<5; i++)
		log_encrypt_message(1, "        TALK_SAY %d %s", i, info.Msg[i]);
	log_encrypt_message(1, "        TALK_NEXT %d", info.NextProc);
#endif//DEBUG_MSG

	return	0;
}

static	SLONG	client_handle_notify_npc_choice(WPARAM wParam)
{
	TPOS_EVENT_NOTIFYNPCCHOICE	info;
	SLONG	i;

	memcpy(&info, (void*)wParam, sizeof(info));

	close_last_event_ui();
	clear_game_choice();
	set_game_choice_offer_npc(info.TargetNPCIndex);
	set_game_choice_title(info.Title);
	for(i=0; i<5; i++)
	{
		if(info.Option[i][0])
		{
			add_game_choice_option(info.NextProc[i], info.Option[i]);
		}
	}
	open_event_ui(UI_TYPE_GAME_CHOICE);

#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    NOTIFY_NPC_CHOICE(npc:%d)", info.TargetNPCIndex);
	log_encrypt_message(1, "        CHOICE_TITLE %s", info.Title);
	for(i=0; i<5; i++)
		log_encrypt_message(1, "        CHOICE_OPTION %d %d %s", i, info.NextProc[i], info.Option[i]);
#endif//DEBUG_MSG

	return	0;
}

static	SLONG	client_handle_notify_end_dialog(WPARAM wParam)
{
	TPOS_EVENT_NOTIFYENDDIALOG	info;

	memcpy(&info, (void*)wParam, sizeof(info));

	close_last_event_ui();

#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    NOTIFY_END_DIALOG(npc:%d)", info.TargetNPCIndex);
#endif//DEBUG_MSG

	return	0;
}

static	SLONG	client_handle_notify_npc_on_pause(WPARAM wParam)
{
	TPOS_EVENT_NOTIFYNPCONPAUSE	info;

	memcpy(&info, (void*)wParam, sizeof(info));

	LOCK_CHARACTER(0);
	SetCharacterOnPauseState(info.OnPauseNpcIndex, TRUE);
	UNLOCK_CHARACTER(0);


#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    NOTIFY_NPC_ON_PAUSE(npc:%d)", info.OnPauseNpcIndex);
#endif//DEBUG_MSG

	return	0;
}

static	SLONG	client_handle_notify_npc_no_pause(WPARAM wParam)
{
	TPOS_EVENT_NOTIFYNPCNOPAUSE	info;

	memcpy(&info, (void*)wParam, sizeof(info));

	LOCK_CHARACTER(0);
	SetCharacterOnPauseState(info.NoPauseNpcIndex, FALSE);
	UNLOCK_CHARACTER(0);


#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    NOTIFY_NPC_NO_PAUSE(npc:%d)", info.NoPauseNpcIndex);
#endif//DEBUG_MSG

	return	0;
}

static	SLONG	client_handle_notify_break_magic(WPARAM wParam)
{
	TPOS_EVENT_NOTIFYBREAKMAGIC	info;

	memcpy(&info, (void*)wParam, sizeof(info));
	//服務器發過來的只會是炸開的法術效果
	client_break_magic(info.npc_no, info.dest_x, info.dest_y, info.magic_index, -1,MAGIC_BREAK_TYPE_TAG);

#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    NOTIFY_BREAK_MAGIC(npc:%d, dest_x:%d, dest_y:%d, magic:%d)", 
		info.npc_no, info.dest_x, info.dest_y, info.magic_index);
#endif//DEBUG_MSG

	return	0;
}
		
static	SLONG   client_handle_set_npc_mp(WPARAM wParam)
{
	TPOS_EVENT_SETNPCMP	info;
	SLONG	npc_no;

    memcpy(&info, (void*)wParam, sizeof(info));
	npc_no = info.Index;
    if(npc_no >= 0 && npc_no < MAX_CHARACTER_PER_ZONE)
    {
        LOCK_CHARACTER(npc_no);
        SetCharacterMp(npc_no, info.iMp);
        UNLOCK_CHARACTER(npc_no);
    }

#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    SET_NPC_MP(%d, %d)", info.Index, info.iMp);
#endif//DEBUG_MSG

    return  0;
}

static	SLONG	client_handle_set_mainname_color(WPARAM wParam)
{
	TPOS_EVENT_SETMAINNAMECOLOR	info;
	SLONG	npc_no;

	memcpy(&info, (void*)wParam, sizeof(info));
	npc_no = info.Npc_No;
	if(npc_no >= 0 && npc_no < MAX_CHARACTER_PER_ZONE)
	{
		LOCK_CHARACTER(npc_no);
		SetCharacterMainNameColor(npc_no, info.MainNameColor);
		UNLOCK_CHARACTER(npc_no);
	}

#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    SET_MAINNAME_COLOR(%d, %d)", info.Npc_No, info.MainNameColor);
#endif//DEBUG_MSG
	
	return	0;
}


static	SLONG	client_handle_set_goodevil(WPARAM wParam)
{
	TPOS_EVENT_SETGOODEVIL	info;

	memcpy(&info, (void*)wParam, sizeof(info));

	LOCK_CHARACTER(g_lPlayerIndex);
	SetCharacterGoodEvil(g_lPlayerIndex, info.GoodEvil);
	SetCharacterPkCount(g_lPlayerIndex, info.PkCount);
	SetCharacterPkedCount(g_lPlayerIndex, info.PkedCount);
	UNLOCK_CHARACTER(g_lPlayerIndex);

#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    SET_GOODEVIL(goodevil:%d, pk:%d, pked:%d)", 
		info.GoodEvil, info.PkCount, info.PkedCount);
#endif//DEBUG_MSG
	
	return	0;
}

static	SLONG	client_handle_set_npc_move_speed(WPARAM wParam)
{
	TPOS_EVENT_SETNPCMOVESPEED	info;
	SLONG	npc_no;

	memcpy(&info, (void*)wParam, sizeof(info));
	npc_no = info.Npc_No;
	if(npc_no >= 0 && npc_no < MAX_CHARACTER_PER_ZONE)
	{
		LOCK_CHARACTER(npc_no);
		SetCharacterMoveSpeed(npc_no, info.MoveSpeed);
		UNLOCK_CHARACTER(npc_no);
	}

#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    SET_NPC_MOVESPEED(npc:%d, movespeed:%d)", 
		info.Npc_No, info.MoveSpeed);
#endif//DEBUG_MSG
	
	return	0;
}

static	SLONG	client_handle_set_money(WPARAM wParam)
{
	TPOS_EVENT_SETMONEY	info;

	memcpy(&info, (void*)wParam, sizeof(info));

	LOCK_CHARACTER(g_lPlayerIndex);
	SetCharacterBodyMoney(g_lPlayerIndex, info.Money);
	UNLOCK_CHARACTER(g_lPlayerIndex);

#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    SET_MONEY(%u)", info.Money);
#endif//DEBUG_MSG
	
	return	0;
}


static	SLONG	client_handle_notify_after_change_equip(WPARAM wParam)
{
	POS_EVENT_NOTIFYAFTERCHANGEEQUIP	info;

	memcpy(&info, (void*)wParam, sizeof(info));

	LOCK_CHARACTER(g_lPlayerIndex);
	SetCharacterFinalAtt(g_lPlayerIndex, info.att);
	SetCharacterFinalDefence(g_lPlayerIndex, info.defence);
	SetCharacterFinalResist(g_lPlayerIndex, info.resist);
	SetCharacterMaxHp(g_lPlayerIndex, info.max_hp);
	SetCharacterHp(g_lPlayerIndex, info.hp);
	SetCharacterMaxMp(g_lPlayerIndex, info.max_mp);
	SetCharacterMp(g_lPlayerIndex, info.mp);
	UNLOCK_CHARACTER(g_lPlayerIndex);

#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    NOTIFY_AFTER_CHANGE_EQUIP(att:%d, def:%d, resist:%d, hp:%d/%d, mp:%d/%d)",
		info.att, info.defence, info.resist, info.hp, info.max_hp, info.mp, info.max_mp);
#endif//DEBUG_MSG
	
	return	0;
}



static	SLONG	client_handle_god_notify_property_point(WPARAM wParam)
{
	TPOS_GOD_NOTIFYPROPERTYPOINT	info;

	memcpy(&info, (void*)wParam, sizeof(info));

	LOCK_CHARACTER(g_lPlayerIndex);
	SetCharacterPropertyPoint(g_lPlayerIndex, (UHINT)info.Point);
	UNLOCK_CHARACTER(g_lPlayerIndex);

#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    GOD_NOTIFY_PROPERTYPOINT(point:%d)", 
		info.Point);
#endif//DEBUG_MSG
	
	return	0;
}



static	SLONG	client_handle_notify_store_data(WPARAM wParam)
{
	TPOS_EVENT_NOTIFYSTOREDATA	info;
	SLONG	i;

	memcpy(&info, (void*)wParam, sizeof(info));
	item_store_data.OfferNpc = info.NpcNo;
	item_store_data.NextProc = info.NextProc;
	item_store_data.StoreIndex = info.ZoneStoreIndex;
	for(i=0; i<36; i++)
	{
		item_store_data.Item[i] = info.Item[i];
		item_store_data.Amount[i] = info.Amount[i];
		item_store_data.Money[i] = info.Money[i];
	}

	close_last_event_ui();
	clear_bank_store_data();
	set_ui_store_type(ITEM_STORE);
	open_event_ui(UI_TYPE_STORE_SHOP);

#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    NOTIFY_STORE_DATA(offer_npc:%d, next_proc:%d, store_index:%d)",
		info.NpcNo, info.NextProc, info.ZoneStoreIndex);
#endif//DEBUG_MSG
	
	return	0;
}


SLONG	client_handle_refresh_store_data(WPARAM wParam)
{
	TPOS_EVENT_REFRESHSTOREDATA	info;
	SLONG	i;

	memcpy(&info, (void*)wParam, sizeof(info));
	for(i=0; i<36; i++)
	{
		item_store_data.Item[i] = info.Item[i];
		item_store_data.Amount[i] = info.Amount[i];
		item_store_data.Money[i] = info.Money[i];
	}

#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    REFRESH_STORE_DATA()");
#endif//DEBUG_MSG
	
	return	0;
}

// 銀行消息, ZZH, 2003.4.18 ----------------------------------------------

SLONG	client_handle_notify_bank_money_item( WPARAM wParam )
{
	TPOS_EVENT_NOTIFYBANKMONEYITEM	info;
	SLONG i;

	info = *(TPOS_EVENT_NOTIFYBANKMONEYITEM*)wParam;

	bank_store_data.OfferNpc = info.NpcNo;
	bank_store_data.NextProc = info.NextProc;

	LOCK_CHARACTER( g_lPlayerIndex );
	SetCharacterBankMoney( g_lPlayerIndex, info.Money );
	UNLOCK_CHARACTER( g_lPlayerIndex );
	for( i = 0; i < MAX_CHARACTER_BANK_ITEMS; i++ )
	{
		LOCK_CHARACTER( g_lPlayerIndex );
		SetCharacterBankItem( g_lPlayerIndex, i, &info.Item[i] );
		UNLOCK_CHARACTER( g_lPlayerIndex );
	}

	close_last_event_ui();
	set_ui_store_type(BANK_STORE);
	open_event_ui(UI_TYPE_STORE_SHOP);

#ifdef DEBUG_MSG
	log_encrypt_message( 1, "    NOTIFY_BANK_MONEY_ITEM()" );
#endif

	return 0;
}

SLONG	client_handle_notify_money_not_enough( WPARAM wParam )
{
	
	bank_money_not_enough( );

#ifdef DEBUG_MSG
	log_encrypt_message( 1, "    NOTIFY_MONEY_NOT_ENOUGH()" );
#endif
	return 0;
}

SLONG	client_handle_notify_no_item_room( WPARAM wParam )
{
	
	bank_no_item_room( );

#ifdef DEBUG_MSG
	log_encrypt_message( 1, "    NOTIFY_NO_ITEM_ROOM()" );
#endif
	return 0;
}


SLONG	client_handle_notify_set_bank_item( WPARAM wParam )
{
	TPOS_EVENT_NOTIFYSETBANKITEM info;

	info = *(TPOS_EVENT_NOTIFYSETBANKITEM*)wParam;

	if ( info.Index >= 0 && info.Index < MAX_CHARACTER_BANK_ITEMS )
	{
		LOCK_CHARACTER( g_lPlayerIndex );
		SetCharacterBankItem( g_lPlayerIndex, info.Index, &info.Item );
		UNLOCK_CHARACTER( g_lPlayerIndex );
	}

#ifdef DEBUG_MSG
	log_encrypt_message( 1, "    NOTIFY_SET_BANK_ITEM( Index: %d)", info.Index );
#endif
	return 0;
}

SLONG	client_handle_set_bank_money( WPARAM wParam )
{
	TPOS_EVENT_SETBANKMONEY	info;

	info = *(TPOS_EVENT_SETBANKMONEY*)wParam;

	LOCK_CHARACTER( g_lPlayerIndex );
	SetCharacterBankMoney( g_lPlayerIndex, info.Money );
	UNLOCK_CHARACTER( g_lPlayerIndex );

#ifdef DEBUG_MSG
	log_encrypt_message( 1, "    SET_BANK_MONEY( Money: %d)", info.Money );
#endif
	return 0;
}

// 組隊消息  ZZH, 2003.4.22-----------------------------------------------

SLONG	client_handle_notify_someone_want_join_team(WPARAM wParam)
{
	TPOS_EVENT_NOTIFYSOMEONEWANTJOINTEAM	info;

	info = *( TPOS_EVENT_NOTIFYSOMEONEWANTJOINTEAM*)wParam;
    team_want_join( &info );

#ifdef	DEBUG_MSG
	log_encrypt_message(1, "    NOTIFY_SOMEONE_WANT_JOIN_TEAM(%s)", info.MemberMainName);
#endif//DEBUG_MSG

	return	0;
}

SLONG	client_handle_notify_join_team_full(WPARAM wParam)
{
	TPOS_EVENT_NOTIFYJOINTEAMFULL	info;

	info = *(TPOS_EVENT_NOTIFYJOINTEAMFULL*)wParam;
    team_target_full( &info );

#ifdef	DEBUG_MSG
	log_encrypt_message(1, "    NOTIFY_JOIN_TEAM_FULL(%s)", info.LeaderMainName);
#endif//DEBUG_MSG

	return	0;
}

SLONG	client_handle_notify_already_in_team(WPARAM wParam)
{
    team_already_in_team();

#ifdef	DEBUG_MSG
	log_encrypt_message(1, "    NOTIFY_ALREADY_IN_TEAM()");
#endif//DEBUG_MSG

	return	0;
}

SLONG	client_handle_notify_someone_join_team(WPARAM wParam)
{
	TPOS_EVENT_NOTIFYSOMEONEJOINTEAM	info;

    info = *(TPOS_EVENT_NOTIFYSOMEONEJOINTEAM*)wParam;

    team_join( &info );

#ifdef	DEBUG_MSG
	log_encrypt_message(1, "    NOTIFY_SOMEONE_JOIN_TEAM(%s)", info.MainName);
#endif//DEBUG_MSG

	return	0;
}

SLONG	client_handle_notify_someone_exit_team(WPARAM wParam)
{
	TPOS_EVENT_NOTIFYSOMEONEEXITTEAM	info;

	//memcpy(&info, (void*)wParam, sizeof(info));
    info = *( TPOS_EVENT_NOTIFYSOMEONEEXITTEAM *)wParam;
    team_exit( &info );

#ifdef	DEBUG_MSG
	log_encrypt_message(1, "    NOTIFY_SOMEONE_EXIT_TEAM(%s)", info.MemberMainName);
#endif//DEBUG_MSG

	return	0;
}

SLONG	client_handle_notify_kicked_from_team(WPARAM wParam)
{

    team_kick();

#ifdef	DEBUG_MSG
	log_encrypt_message(1, "    NOTIFY_KICKED_FROM_TEAM()");
#endif//DEBUG_MSG

	return	0;
}

SLONG	client_handle_notify_team_member_info(WPARAM wParam)
{
	TPOS_EVENT_NOTIFYTEAMMEMBERINFO	info;

    info = *(TPOS_EVENT_NOTIFYTEAMMEMBERINFO*)wParam;
    team_set_info( &info );

#ifdef	DEBUG_MSG
	log_encrypt_message(1, "    NOTIFY_TEAM_MEMBER_INFO()" );
#endif//DEBUG_MSG

	return	0;
}

SLONG	client_notify_team_member_changezone(WPARAM wParam)
{
	// Jack, TODO [3/18/2003]
	return	0;
}

SLONG client_notify_make_team( WPARAM wParam )
{
    TPOS_EVENT_NOTIFYMAKETEAM info;

    info = *(TPOS_EVENT_NOTIFYMAKETEAM*)wParam;
    
    team_make_team( &info );

#ifdef DEBUG_MSG
    log_encrypt_message( 1, "   NOTIFY_MAKE_TEAM()" );
#endif

    return 0;
}

SLONG client_notify_kill_team( WPARAM wParam )
{
    team_kill_team( );

#ifdef DEBUG_MSG
    log_encrypt_message( 1, "   NOTITY_KILL_TEAM()" );
#endif 

    return 0;
}

SLONG client_notify_change_leader( WPARAM wParam )
{
    TPOS_EVENT_NOTIFYCHANGELEADER info;

    info = *(TPOS_EVENT_NOTIFYCHANGELEADER*)wParam;

    team_change_leader( &info );

#ifdef DEBUG_MSG
    log_encrypt_message( 1, "    NOTIFY_CHANE_LEADER()" );
#endif

    return 0;
}

SLONG client_notify_reload_team_info( WPARAM wParam )
{
    TPOS_EVENT_NOTIFYRELOADTEAMINFO info;
    
    info = *(TPOS_EVENT_NOTIFYRELOADTEAMINFO*)wParam;

    team_set_info( (TPOS_EVENT_NOTIFYTEAMMEMBERINFO *)&info );

#ifdef DEBUG_MSG
    log_encrypt_message( 1, "    NOTIFY_RELAD_TEAM_INFO()" );
#endif

    return 0;
}

// 獲得地圖物品 ------------------------------------------------
SLONG client_handle_notify_zone_item_list( WPARAM wParam)
{
    TPOS_EVENT_NOTIFYZONEITEMLIST info;
    SLONG i;

    info = *(TPOS_EVENT_NOTIFYZONEITEMLIST *)wParam;

    LOCK_ITEM( 0 );
    for ( i = 0; i < 500; i++ )
    {
        if ( IsItemNone( &info.Item[i]) )
            break;
        AddZoneItem( info.X[i], info.Y[i], NULL, &info.Item[i]);
    }
    UNLOCK_ITEM( 0 );


#ifdef DEBUG_MSG
	log_encrypt_message(1, "    NOTIFY_ZONE_ITEM_LIST" );
#endif
    return 0;
}

// 藏寶圖消息 ------------------------------------------------------
SLONG client_handle_notify_map_info( WPARAM wParam )
{
    TPOS_EVENT_NOTIFYMAPINFO info;
    TPOS_ITEM item;
    TM tm_info;

    info = *(TPOS_EVENT_NOTIFYMAPINFO*)wParam;
    SetItemNone( &item );
    
    tm_info.top     = info.MapLeftUpX;
    tm_info.left    = info.MapLeftUpY;
    tm_info.x       = info.RedPointX;
    tm_info.y       = info.RedPointY;
    tm_info.index   = info.BagIndex;

    memcpy( tm_info.info, info.Memo, 256 );
    
    if ( info.BagIndex == 0xff )        // 藏寶圖裝備格
    {
        LOCK_CHARACTER( g_lPlayerIndex );
        GetCharacterTreasureItem( g_lPlayerIndex, &item );
        UNLOCK_CHARACTER( g_lPlayerIndex );

    }
    else if ( info.BagIndex >= 0 && info.BagIndex < 27 )
    {
        LOCK_CHARACTER( g_lPlayerIndex );
        GetCharacterBagItem( g_lPlayerIndex, info.BagIndex, &item );
        UNLOCK_CHARACTER( g_lPlayerIndex );


    }
    else
    {
        // Bag Index Error
        log_encrypt_message( 1, "    NOTIFY_MAP_INFO ( Error Bag Index: %d )", info.BagIndex );
        return 0;
    }
    
    if ( !IsItemNone( &item ) )
    {
        LOCK_CHARACTER( g_lPlayerIndex );
        tm_info.style = GetTreasureMapItemWholePieces( &item );
        tm_info.mask  = GetTreasureMapItemCurrentPieces( &item );
        LOCK_CHARACTER( g_lPlayerIndex );
        sm_set_tm_info( &tm_info );
        sm_set( TYPE_TM );
    }


#ifdef DEBUG_MSG
    log_encrypt_message( 1, "    NOTIFY_MAP_INFO" );
#endif 

    return 0;
}


// 藏寶圖拆開失敗
SLONG client_handle_notify_bag_space_not_enough( WPARAM wParam )
{
    return 0;
}

/******************************************************************************************************************/
/* CLIENT MISC FUNCTIONS                                                                                          */
/******************************************************************************************************************/
static	void    client_add_npc_talk_msg(SLONG npc_no, USTR *msg)
{
    DWORD   talk_time;
    char**  ppmsg;
    SLONG   lines, i;
    
    talk_time = timeGetTime();
    ppmsg = divide_chine_string((char *)msg, NPC_TALK_LEN, &lines);

    LOCK_CHARACTER(npc_no);
    for(i=0; i<lines; i++)
    {
        add_npc_talk(npc_no, talk_time, (USTR*)ppmsg[i]);
    }
    UNLOCK_CHARACTER(npc_no);
}


static  void    apply_list_player_info_to_character_npc(TPOS_EVENT_GETPLAYERLIST info)
{
	USTR	rgb_data[35];
	SLONG	index, i;

	index = info.iIndex;
	if(index < 0 || index >= MAX_CHARACTER_PER_ZONE)
		return;

    LOCK_CHARACTER(index);
	ClearOneCharacter(index);
    clear_one_game_npc(index);
	//
    SetCharacterMainName(index, info.cMainName);
	SetCharacterFileIndex(index, info.slFileIndex);
    SetCharacterHp(index, (UHINT)info.iHp);
    SetCharacterMp(index, (UHINT)info.iMp);
    SetCharacterMaxHp(index, (UHINT)info.iHp);	//temp set
    SetCharacterMaxMp(index, (UHINT)info.iMp);	//temp set
	SetCharacterMoveSpeed(index, (SLONG)info.iMspeed);
    SetCharacterColor(index, (SLONG)info.cColor-'0');
    SetCharacterEyes(index, (SLONG)info.cEyes-'0');
    SetCharacterMouth(index, (SLONG)info.cMouth-'0');
	SetCharacterPosition(index, info.lX, info.lY, info.lZ);
	SetCharacterDoingKindStep(index, info.slDoingKind, info.lDoingStep);
	for(i=0; i<7; i++)
	{
		SetCharacterPartRGB(index, i, info.PartRGB[i]);
	}

    SetCharacterMaxHp(index, (UHINT)info.iMaxHp);
    SetCharacterMaxMp(index, (UHINT)info.iMaxMp);
    SetCharacterPicture(index, (SLONG)info.Picture);
    SetCharacterMainNameColor(index, (SLONG)info.cMainNameColor);
    SetCharacterNickNameColor(index, (SLONG)info.cNickNameColor);
    SetCharacterMessageColor(index, (SLONG)info.cMessageColor);
    SetCharacterTalkBackColor(index, (SLONG)info.cTalkBackColor);
    SetCharacterLogo(index, info.dwLogo);
    SetCharacterLevel(index, info.iLevel);
    SetCharacterSightRange(index, info.iSightRange);
	SetCharacterBitState(index, info.BitState);
	SetCharacterDirFrame(index, info.iDirFrame);
	SetCharacterDestID(index, info.lDestNo);
	SetCharacterOrigID(index, info.lOrigNo);
	SetCharacterDestPosition(index, info.lDestX, info.lDestY, info.lDestZ);
	SetCharacterOrigPosition(index, info.lOrigX, info.lOrigY, info.lOrigZ);
	SetCharacterDir(index, info.cDir);

	// Jack, TODO [1/11/2003]
	// Other status, ticks and much more are needed:

	switch(g_dwZoneType)
	{
	case SAIL_NORMAL:
	case SAIL_NEWBIE:
	case SAIL_PK:
	case SAIL_FINDGOLD:
	case SAIL_BIRTH:
		SetCharacterOnTheSea(index, true);
		SetCharacterShipSailSize(index, info.SailSize);
		SetCharacterShipWeight(index, info.Weight);
		SetCharacterShipTurn(index, info.Turn);
		//
		SetCharacterShipSpeedX(index, 0);
		SetCharacterShipSpeedY(index, 0);
		break;
	case CITY_NORMAL:
	case CITY_NEWBIE:
	case CITY_PK:
	case CITY_FINDGOLD:
	case CITY_BIRTH:
	case FIELD_NORMAL:
	case FIELD_NEWBIE:
	case FIELD_PK:
	case FIELD_FINDGOLD:
	case FIELD_BIRTH:
	default:
		SetCharacterOnTheSea(index, false);
		break;
	}

	for(i=0; i<7; i++)
	{
		rgb_data[i*5 + 0] = ((ARGB_DATA*)&info.PartRGB[i])->a;
		rgb_data[i*5 + 1] = ((ARGB_DATA*)&info.PartRGB[i])->r;
		rgb_data[i*5 + 2] = ((ARGB_DATA*)&info.PartRGB[i])->g;
		rgb_data[i*5 + 3] = ((ARGB_DATA*)&info.PartRGB[i])->b;
		rgb_data[i*5 + 4] = 0;
	}
	set_npc_rgb_scroll(index, (USTR*)rgb_data);
    active_map_npc(index);
    LOCK_CHARACTER(index);
}


static	void	apply_mycharacterdata_to_character_npc(SLONG index, TPOS_EVENT_MYCHARACTER info)
{
	static	USTR	rgb_data[35];
	SLONG	i;

    LOCK_CHARACTER(index);
	ClearOneCharacter(index);
    clear_one_game_npc(index);
	//
	//Name
	SetCharacterAccount(index, info.ID);
	SetCharacterMainName(index, info.MainName);
	SetCharacterNickName(index, info.NickName);
	SetCharacterQQID(index, info.QQID);
	SetCharacterIndex(index, info.Index);
	//Style	
	SetCharacterColor(index, info.Color);
	SetCharacterEyes(index, info.Eyes);
	SetCharacterMouth(index, info.Mouth);
	SetCharacterMainNameColor(index, info.MainNameColor);
	SetCharacterNickNameColor(index, info.NickNameColor);
	SetCharacterMessageColor(index, info.MessageColor);
	SetCharacterTalkBackColor(index, info.TalkBackColor);
	SetCharacterLogo(index, info.Logo);
	SetCharacterFileIndex(index, info.FileIndex);
	for(i=0; i<7; i++)
	{
		SetCharacterPartRGB(index, i, info.PartRGB[i]);
	}

	//Position
	SetCharacterZoneName(index, info.ZoneName);
	SetCharacterPosition(index, info.X, info.Y, info.Z);
	SetCharacterDir(index, info.Dir);
	SetCharacterStopRadius(index, info.StopRadius);
	//Speed
	SetCharacterMoveSpeed(index, info.Mspeed);
	SetCharacterShipSpeedX(index, info.FSpeedX);
	SetCharacterShipSpeedY(index, info.FSpeedY);
	SetCharacterShipSailSize(index, info.SailSize);
	SetCharacterShipTurn(index, info.Turn);
	SetCharacterShipWeight(index, info.Weight);
	SetCharacterShipDegreeDir(index, info.DegreeDir);
	//State
	SetCharacterBitState(index, info.BitState);
	//Str
	SetCharacterFinalStr(index, info.FinalStr);
	//Ins
	SetCharacterFinalIns(index, info.FinalIns);
	//Wit
	SetCharacterFinalWit(index, info.FinalWit);
	//Lucky
	SetCharacterFinalLucky(index, info.FinalLucky);
	//Attack
	SetCharacterSightRange(index, info.SightRange);
	//Property
	SetCharacterPropertyPoint(index, info.PropertyPoint);
	//Exp Lev
	SetCharacterExp(index, info.Exp);
	SetCharacterLevel(index, info.Level);
	//Hp Mp
	SetCharacterHp(index, info.Hp);
	SetCharacterMaxHp(index, info.MaxHp);
	SetCharacterHpRes(index, info.HpRes);
	SetCharacterMp(index, info.Mp);
	SetCharacterMaxMp(index, info.MaxMp);
	SetCharacterMpRes(index, info.MpRes);
	//Skill
	for(i = 0; i < MAX_CHARACTER_SKILLS; i++)
	{
		SetCharacterSkillNo(index, i, info.SkillNo[i]);
		SetCharacterSkillLevel(index, i, info.SkillLevel[i]);
	}

	SetCharacterEquipHead(index, &info.EquHead);
	SetCharacterEquipNeck(index, &info.EquNeck);
	SetCharacterEquipBody(index, &info.EquBody);
	SetCharacterEquipWaist(index, &info.EquWaist);
	SetCharacterEquipGlove(index, &info.EquGlove);
	SetCharacterEquipWeapon(index, &info.EquWeapon);
	SetCharacterEquipWrist(index, &info.EquWrist);
	SetCharacterEquipFeet(index, &info.EquFeet);
	SetCharacterEquipOtherA(index, &info.EquOtherA);
	SetCharacterEquipOtherB(index, &info.EquOtherB);
	SetCharacterEquipOtherC(index, &info.EquOtherC);
	for(i=0; i<MAX_CHARACTER_BAG_ITEMS; i++)
	{
		SetCharacterBagItem(index, i, &info.BagItem[i]);
	}
	for(i=0; i<MAX_CHARACTER_SASH_ITEMS; i++)
	{
		SetCharacterSashItem(index, i, &info.SashItem[i]);
	}
	for(i=0; i<MAX_CHARACTER_TRANS_ITEMS; i++)
	{
		SetCharacterTransItem(index, i, &info.TransItem[i]);
	}

	// Jack, temp use onmouseitem, later will be none for server have been drop it to the ground. [1/17/2003]
	SetCharacterOnMouseItem(index, &info.OnMouseItem);

	SetCharacterTreasureItem(index, &info.TreasureItem);

	SetCharacterBodyMoney(index, info.Money);
	//Society
	SetCharacterSex(index, info.Sex);
	SetCharacterCountry(index, info.Country);
	SetCharacterGuildName(index, info.Guild);
	SetCharacterSpouseName(index, info.Spouse);
	SetCharacterCareer(index, info.Career);
	SetCharacterOffice(index, info.Office);
	SetCharacterNobilityName(index, info.Nobility);
	SetCharacterGoodEvil(index, info.GoodEvil);
	SetCharacterPrestige(index, info.Prestige);
	SetCharacterPkCount(index, info.PkCount);
	SetCharacterPkedCount(index, info.PkedCount);
	//Mouse skill and Hot Key
	SetCharacterLandLeftSkill(index, info.LandLeftSkill);
	SetCharacterLandRightSkill(index, info.LandRightSkill);
	for(i=0; i<MAX_CHARACTER_FN_SKILLS; i++)
	{
		SetCharacterLandFnSkillNo(index, i, info.LandFnSkillNo[i]);
		SetCharacterLandFnSkillHand(index, i, info.LandFnSkillHand[i]);
	}
	//
	SetCharacterSeaLeftSkill(index, info.SeaLeftSkill);
	SetCharacterSeaRightSkill(index, info.SeaRightSkill);
	for(i=0; i<MAX_CHARACTER_FN_SKILLS; i++)
	{
		SetCharacterSeaFnSkillNo(index, i, info.SeaFnSkillNo[i]);
		SetCharacterSeaFnSkillHand(index, i, info.SeaFnSkillHand[i]);
	}
	//Datas
	SetCharacterFinalAtt(index, info.FinalAttack);
	SetCharacterFinalDefence(index, info.FinalDefence);
	//Doing
	SetCharacterDoingKind(index, info.DoingKind);

	switch(g_dwZoneType)
	{
	case SAIL_NORMAL:
	case SAIL_NEWBIE:
	case SAIL_PK:
	case SAIL_FINDGOLD:
	case SAIL_BIRTH:
		SetCharacterOnTheSea(index, true);
		SetCharacterShipSpeedX(index, 0);
		SetCharacterShipSpeedY(index, 0);
		break;
	case CITY_NORMAL:
	case CITY_NEWBIE:
	case CITY_PK:
	case CITY_FINDGOLD:
	case CITY_BIRTH:
	case FIELD_NORMAL:
	case FIELD_NEWBIE:
	case FIELD_PK:
	case FIELD_FINDGOLD:
	case FIELD_BIRTH:
	default:
		SetCharacterOnTheSea(index, false);
		break;
	}

	for(i=0; i<7; i++)
	{
		rgb_data[i*5 + 0] = ((ARGB_DATA*)&info.PartRGB[i])->a;
		rgb_data[i*5 + 1] = ((ARGB_DATA*)&info.PartRGB[i])->r;
		rgb_data[i*5 + 2] = ((ARGB_DATA*)&info.PartRGB[i])->g;
		rgb_data[i*5 + 3] = ((ARGB_DATA*)&info.PartRGB[i])->b;
		rgb_data[i*5 + 4] = 0;
	}
	set_npc_rgb_scroll(index, (USTR*)rgb_data);

    active_map_npc(index);
    LOCK_CHARACTER(index);
}

/******************************************************************************************************************/
/* CLIENT RECV & PROCESS GAME EVENT FUNCTIONS                                                                     */
/******************************************************************************************************************/
HRESULT HandlePosGameEvent(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch(lParam)
    {
    case VERSION_ERROR:
        client_handle_version_error(wParam);
        break;
	case ERROR_DATA:
		client_handle_error_data(wParam);
		break;
        
        //有關 DOOR SERVER 時的消息 ---------------------------------------------------------------
    case DOOR_SERVER_CLOSED: //伺服器關閉
        client_handle_door_server_closed(wParam);
        break;
    case DOOR_LOGIN_OK: //登錄 DOOR SERVER 成功
        client_handle_door_login_ok(wParam);
        break;
    case DOOR_LOGIN_FAIL:
		client_handle_door_login_fail(wParam);
        break;
    case DOOR_LOGIN_ERRORID:
		client_handle_door_login_errorid(wParam);
        break;
    case DOOR_LOGIN_ERRORPW:
		client_handle_door_login_errorpw(wParam);
        break;
    case DOOR_LOGIN_DENIED:
		client_handle_door_login_denied(wParam);
        break;
    case DOOR_KICKED:
        client_handle_door_kicked(wParam);
        break;
    case DOOR_LOGIN_REPEAT:
		client_handle_door_login_repeat(wParam);
        break;
    case GET_WORLD_INFO:
        client_handle_get_world_info(wParam);
        break;
    case REFRESH_WORLD_INFO:
        client_handle_refresh_world_info(wParam);
        break;
    case NEW_WORLD_INFO:
        client_handle_new_world_info(wParam);
        break;
    case ONE_WORLD_CLOSE:
        client_handle_world_close(wParam);
        break;
    case REGISTER_ACCOUNT_CHECK_OK:
        client_handle_register_account_check_ok(wParam);
        break;
    case REGISTER_ACCOUNT_FINAL_OK:
        client_handle_register_account_final_ok(wParam);
        break;
    case REGISTER_ACCOUNT_CHECK_FAIL:
		client_handle_register_account_check_fail(wParam);
        break;
    case REGISTER_ACCOUNT_IDUSED:
        client_handle_register_account_idused(wParam);
        break;
        
        //有關 WORLD SERVER 時的消息 ---------------------------------------------------------------
    case WORLD_SERVER_CLOSED: //伺服器關閉
        client_handle_world_server_closed(wParam);
        break;
    case WORLD_LOGIN_OK:
        client_handle_world_login_ok(wParam);
        break;
    case WORLD_LOGIN_FAIL:
		client_handle_world_login_fail(wParam);
        break;
	case WORLD_LOGIN_ERRORID:
		client_handle_world_login_errorid(wParam);
		break;
	case WORLD_LOGIN_ERRORPW:
		client_handle_world_login_errorpw(wParam);
		break;
	case WORLD_LOGIN_DENIED:
		client_handle_world_login_denied(wParam);
		break;
	case WORLD_KICKED:
		client_handle_world_login_kicked(wParam);
		break;
	case WORLD_LOGIN_REPEAT:
		client_handle_world_login_repeat(wParam);
		break;
    case GET_ZONE_INFO:
        client_handle_get_zone_info(wParam);
        break;
    case GET_CHARACTER_INFO:
        client_handle_get_character_info(wParam);
        break;
    case CREATE_CHARACTER_CHECK_OK:
        client_handle_create_character_check_ok(wParam);
        break;
    case CREATE_CHARACTER_OK:
        client_handle_create_character_ok(wParam);
        break;
    case CREATE_CHARACTER_FINAL_OK:
        client_handle_create_character_final_ok(wParam);
        break;
	case CREATE_CHARACTER_FINAL_FAIL:
        client_handle_create_character_final_fail(wParam);
		break;
    case CREATE_CHARACTER_NAMEUSED:
		client_handle_create_character_nameused(wParam);
        break;
    case CREATE_CHARACTER_FAIL:
		client_handle_create_character_fail(wParam);
        break;
    case DELETE_CHARACTER_OK:
        client_handle_delete_character_ok(wParam);
        break;
    case DELETE_CHARACTER_FAIL:
		client_handle_delete_character_fail(wParam);
        break;
        
        //有關 ZONE SERVER 時的消息 ---------------------------------------------------------------
    case ZONE_SERVER_CLOSED: //伺服器關閉
        client_handle_zone_server_closed(wParam);
        break;
        
    case ZONE_LOGIN_OK:
        client_handle_zone_login_ok(wParam);
        break;
    case ZONE_LOGIN_FAIL:
		client_handle_zone_login_fail(wParam);
        break;
	case ZONE_LOGIN_REPEAT:
		client_handle_zone_login_repeat(wParam);
		break;
	case ZONE_LOGIN_ERRORID:
		client_handle_zone_login_errorid(wParam);
		break;
	case ZONE_LOGIN_ERRORPW:
		client_handle_zone_login_errorpw(wParam);
		break;
	case ZONE_LOGIN_DENIED:
		client_handle_zone_login_denied(wParam);
		break;
	case ZONE_KICKED:
		client_handle_zone_login_kicked(wParam);
		break;
    case GET_PLAYER_LIST:
        client_handle_get_player_list(wParam);
        break;
    case PLAYER_JOIN:
        client_handle_player_join(wParam);
        break;
    case PLAYER_EXIT:
        client_handle_player_exit(wParam);
        break;
    case GET_PUBLIC_TALK:
        client_handle_get_public_talk(wParam);
        break;
    case SYNC_POSITION:
        client_handle_sync_position(wParam);
        break;
    case GET_REFRESH:
        client_handle_get_refresh(wParam);
        break;
    case GET_ATTACK_SWITCH:
        client_handle_get_attack_switch(wParam);
        break;
    case GET_BAG_SWITCH:
        client_handle_get_bag_switch(wParam);
        break;
    case GET_CHANGE_MOUSE_SKILL:
        client_handle_get_change_mouse_skill(wParam);
        break;
    case GET_CHARACTER_DEFAULT:
        client_handle_get_character_default(wParam);
        break;
    case GET_ZONE_NOW_WEATHER:
        client_handle_get_zone_now_weather(wParam);
        break;
    case INIT_ZONE_WEATHER:
        client_handle_init_zone_weather(wParam);
        break;
    case GET_CHANGE_MAP:
        client_handle_get_change_map(wParam);
        break;
    case START_CHANGE_MAP:
        client_handle_start_change_map(wParam);
        break;
    case GET_PLAYER_SKILL:
        client_handle_get_player_skill(wParam);
        break;
    case GET_PLAYER_QUICK_SKILLITEM:
        client_handle_get_player_quick_skillitem(wParam);
        break;
    case SYSTEM_MESSAGE:
        client_handle_system_message(wParam);
        break;
    case CHANGE_NPC_DOING:
        client_handle_change_npc_doing(wParam);
        break;
    case NOTIFY_NPC_AI_BLOCK:
        client_handle_change_npc_aiblock(wParam);
        break;
    case NOTIFY_CREATE_MAGIC_AREA:
        client_handle_create_magic_area(wParam);
        break;
    case GET_NPC_RELIVE:
        client_handle_get_npc_relive(wParam);
        break;
    case UPDATE_NPC_DOING:
        client_handle_update_npc_doing(wParam);
        break;
    case SET_NPC_HP:
        client_handle_set_npc_hp(wParam);
        break;
    case SET_NPC_EXP:
        client_handle_set_npc_exp(wParam);
        break;
    case SET_NPC_SKILL:
        client_handle_set_npc_skill(wParam);    
        break;
    case NPC_LEVEL_UP:
        client_handle_npc_level_up(wParam);
        break;
    case SET_NPC_UPGRADE_BASE_DATA:
        client_handle_set_npc_upgrade_base_data(wParam);
        break;
	case PREPARE_PLAYER_EXIT_GAME_OK:
		client_handle_prepare_player_exit_game_ok(wParam);
		break;
	case SEA_SYNC_POSITION:
		client_handle_sea_sync_position(wParam);
		break;
	case NOTIFY_SET_HAND_QUICK_SKILL:
		client_handle_notify_set_hand_quick_skill(wParam);
		break;
	case NOTIFY_ADD_MAP_ITEM:
		client_handle_notify_add_map_item(wParam);
		break;
	case NOTIFY_DELETE_MAP_ITEM:
		client_handle_notify_delete_map_item(wParam);
		break;
	case NOTIFY_SET_ONMOUSE_ITEM:
		client_handle_notify_set_onmouse_item(wParam);
		break;
	case NOTIFY_SET_BAG_ITEM:
		client_handle_notify_set_bag_item(wParam);
		break;
	case NOTIFY_SET_HEAD_ITEM:
		client_handle_notify_set_head_item(wParam);
		break;
	case NOTIFY_SET_NECK_ITEM:
		client_handle_notify_set_neck_item(wParam);
		break;
	case NOTIFY_SET_BODY_ITEM:
		client_handle_notify_set_body_item(wParam);
		break;
	case NOTIFY_SET_WAIST_ITEM:
		client_handle_notify_set_waist_item(wParam);
		break;
	case NOTIFY_SET_GLOVE_ITEM:
		client_handle_notify_set_glove_item(wParam);
		break;
	case NOTIFY_SET_WEAPON_ITEM:
		client_handle_notify_set_weapon_item(wParam);
		break;
	case NOTIFY_SET_WRIST_ITEM:
		client_handle_notify_set_wrist_item(wParam);
		break;
	case NOTIFY_SET_FEET_ITEM:
		client_handle_notify_set_feet_item(wParam);
		break;
	case NOTIFY_SET_OTHERA_ITEM:
		client_handle_notify_set_othera_item(wParam);
		break;
	case NOTIFY_SET_OTHERB_ITEM:
		client_handle_notify_set_otherb_item(wParam);
		break;
	case NOTIFY_SET_OTHERC_ITEM:
		client_handle_notify_set_otherc_item(wParam);
		break;
	case NOTIFY_SET_SASH_ITEM:
		client_handle_notify_set_sash_item(wParam);
		break;
	case NOTIFY_SET_TRANS_ITEM:
		client_handle_notify_set_trans_item(wParam);
		break;
	case NOTIFY_SET_TREASURE_ITEM:
		client_handle_notify_set_treasure_item(wParam);
		break;
	case NOTIFY_NPC_TALK:
		client_handle_notify_npc_talk(wParam);
		break;
	case NOTIFY_NPC_CHOICE:
		client_handle_notify_npc_choice(wParam);
		break;
	case NOTIFY_END_DIALOG:
		client_handle_notify_end_dialog(wParam);
		break;
	case NOTIFY_NPC_ON_PAUSE:
		client_handle_notify_npc_on_pause(wParam);
		break;
	case NOTIFY_NPC_NO_PAUSE:
		client_handle_notify_npc_no_pause(wParam);
		break;
	case NOTIFY_BREAK_MAGIC:
		client_handle_notify_break_magic(wParam);
		break;
	case SET_NPC_MP:
		client_handle_set_npc_mp(wParam);
		break;
	case SET_MAINNAME_COLOR:
		client_handle_set_mainname_color(wParam);
		break;
	case SET_GOODEVIL:
		client_handle_set_goodevil(wParam);
		break;
	case SET_NPC_MOVESPEED:
		client_handle_set_npc_move_speed(wParam);
		break;
	case SET_MONEY:
		client_handle_set_money(wParam);
		break;
	case NOTIFY_AFTER_CHANGE_EQUIP:
		client_handle_notify_after_change_equip(wParam);
		break;
	case NOTIFY_STORE_DATA:
		client_handle_notify_store_data(wParam);
		break;
	case REFRESH_STORE_DATA:
		client_handle_refresh_store_data(wParam);
		break;
	// 銀行消息 ----------------------------------------------------------
	case NOTIFY_BANK_MONEY_ITEM:
		client_handle_notify_bank_money_item( wParam );
		break;
	case NOTIFY_MONEY_NOT_ENOUGH:
		client_handle_notify_money_not_enough( wParam );
		break;
	case NOTIFY_NO_ITEM_ROOM:
		client_handle_notify_no_item_room( wParam );
		break;
	case NOTIFY_SET_BANK_ITEM:
		client_handle_notify_set_bank_item( wParam );
		break;
	case SET_BANK_MONEY:
		client_handle_set_bank_money( wParam );
		break;
		// 組隊消息 ------------------------------------------------------
	case NOTIFY_SOMEONE_WANT_JOIN_TEAM:
		client_handle_notify_someone_want_join_team(wParam);
		break;
	case NOTIFY_JOIN_TEAM_FULL:
		client_handle_notify_join_team_full(wParam);
		break;
	case NOTIFY_ALREADY_IN_TEAM:
		client_handle_notify_already_in_team(wParam);
		break;
	case NOTIFY_SOMEONE_JOIN_TEAM:
		client_handle_notify_someone_join_team(wParam);
		break;
	case NOTIFY_SOMEONE_EXIT_TEAM:
		client_handle_notify_someone_exit_team(wParam);
		break;
	case NOTIFY_KICKED_FROM_TEAM:
		client_handle_notify_kicked_from_team(wParam);
		break;
	case NOTIFY_TEAM_MEMBER_INFO:
		client_handle_notify_team_member_info(wParam);
		break;
	case NOTIFY_TEAM_MEMBER_CHANGEZONE:
		client_notify_team_member_changezone(wParam);
		break;
    case NOTIFY_MAKE_TEAM:
        client_notify_make_team( wParam );
        break;
    case NOTIFY_KILL_TEAM:
        client_notify_kill_team( wParam );
        break;
    case NOTIFY_CHANGE_LEADER:
        client_notify_change_leader( wParam );
        break;
    case NOTIFY_RELOAD_TEAM_INFO:
        client_notify_reload_team_info( wParam );
        break;
		
		// God messages ----------------------------------------------------
	case GOD_NOTIFY_PROPERTYPOINT:
		client_handle_god_notify_property_point(wParam);
		break;
        //QQ messages ------------------------------------------------------
	case QQ_PLAYER_LOGIN:
		client_handle_qq_player_login(wParam);
		break;
	case QQ_LOGIN_OK:
		client_handle_qq_login_ok(wParam);
		break;
	case QQ_LOGIN_FAIL:
		client_handle_qq_login_fail(wParam);
		break;
	case QQ_LOGIN_ERRPW:
		client_handle_qq_login_errpw(wParam);
		break;
	case QQ_LOGIN_ERRID:
		client_handle_qq_login_errid(wParam);
		break;
	case QQ_LOGIN_DENIED:
		client_handle_qq_login_denied(wParam);
		break;
	case QQ_LOGIN_REPEAT:
		client_handle_qq_login_repeat(wParam);
		break;
	case QQ_PLAYER_LOGOUT:
		client_handle_qq_player_logout(wParam);
		break;
	case QQ_GET_MYDATA:
		client_handle_qq_get_mydata(wParam);
		break;
	case QQ_GET_FRIEND_LIST:
		client_handle_qq_get_friend_list(wParam);
		break;
	case QQ_GET_GUILD_FRIEND_LIST:
		client_handle_qq_get_guild_friend_list(wParam);
		break;
	case QQ_GET_MYSTATE:
		client_handle_qq_get_mystate(wParam);
		break;
	case QQ_GET_OTHERSTATE:
		client_handle_qq_get_otherstate(wParam);
		break;
	case QQ_GET_MYCONFIG:
		client_handle_qq_get_myconfig(wParam);
		break;
	case QQ_GET_QUERY_SOMEONE:
		client_handle_qq_get_query_someone(wParam);
		break;
	case QQ_GET_QUERY_ADD_LIST:
		client_handle_qq_get_query_add_list(wParam);
		break;
	case QQ_GET_QUERY_ADD_LIST_END:
		client_handle_qq_get_query_add_list_end(wParam);
		break;
	case QQ_GET_ADD_SOMEONE:
		client_handle_qq_get_add_someone(wParam);
		break;
	case QQ_FRIEND_LOGIN:
		client_handle_qq_friend_login(wParam);
		break;
	case QQ_FRIEND_LOGOUT:
		client_handle_qq_friend_logout(wParam);
		break;
	case QQ_GET_TEAM_LIST:
		client_handle_qq_get_team_list(wParam);
		break;
	case QQ_TEAM_JOIN:
		client_handle_qq_team_join(wParam);
		break;
	case QQ_TEAM_EXIT:
		client_handle_qq_team_exit(wParam);
		break;
	case QQ_GET_DEL_FRIEND:
		client_handle_qq_get_del_friend(wParam);
		break;
	case QQ_GET_MSG:
		client_handle_qq_get_msg(wParam);
		break;
	case QQ_GET_PLAYER_COUNT:
		client_handle_qq_get_player_count(wParam);
		break;
	case QQ_GET_ADD_GUILD_FRIEND:
		client_handle_qq_get_add_guild_friend(wParam);
		break;
	case QQ_GET_DEL_GUILD_FRIEND:
		client_handle_qq_get_del_guild_friend(wParam);
		break;
	case QQ_GET_TRANSFER_ITEM:
		client_handle_qq_get_item( wParam );
		break;
	case QQ_TRANSFER_ITEM_OK:
		client_handle_qq_get_item_ok( wParam );
		break;
	case QQ_TRANSFER_ITEM_FAIL:
		client_handle_qq_get_item_fail( wParam );
		break;
        // 獲得地圖物品 ------------------------------------------------
    case NOTIFY_ZONE_ITEM_LIST:
        client_handle_notify_zone_item_list( wParam);
        break;
        // 藏寶圖消息 ------------------------------------------------------
    case NOTIFY_MAP_INFO:
        client_handle_notify_map_info( wParam );
        break;
    case NOTIFY_BAG_SPACE_NOT_ENOUGH:
        client_handle_notify_bag_space_not_enough( wParam );
        break;
		// Default message -------------------------------------------------
    default:
        client_handle_default_game_event((SLONG)lParam);
        break;
    }
    return  0;
}

