/*
**	Client_SendMsg.cpp 
**	Client send message functions.
**
**	Jack, 2003.1.2
*/
#include "MainFun.h"
#include "qqmain.h"
#include "ClientMain.h"
#include "ErrorMsg.h"
#include "NetGE_MainFunc.h"
#include "NetGE.h"
#include "NetGE_Event_Def.h"
#include "NetGE_Event_Struct_Def.h"



/************************************************************************************************************/
/* MAIN FUNCTIONS                                                                                           */
/************************************************************************************************************/
int		ClientConnectionsInit(void)
{
	return	PosInit();
}

int		ClientConnectionsFree(void)
{
	return	PosFreeMemory();
}

int		ClientGetCurrentConnectedType(void)
{
	return	PosGetCurrentConnectedType();
}


/************************************************************************************************************/
/* SEND MESSAGE TO DOOR SERVER FUNCTIONS                                                                    */
/************************************************************************************************************/
int		ClientLoginDoor(HWND hWnd, char* szServerName, SLONG lPort, CHAR *szID, char *szPassword,DWORD dwVersion)
{
	int	result;

	result  = PosLoginDoor(hWnd, szServerName, lPort, szID, szPassword, dwVersion);

#ifdef	DEBUG_MSG
    log_encrypt_message(1, "    login_door(%s:%d, id:%s, pw:%s, ver:%d)",
		szServerName, lPort, szID, szPassword, dwVersion);
#endif//DEBUG_MSG

	return	result;
}


int		ClientLogoutDoor(void)
{
	int	result;

	result = PosLogoutDoor();

#ifdef	DEBUG_MSG
    log_encrypt_message(1, "    logout_door");
#endif//DEBUG_MSG

	return	result;
}


int		ClientRequestForWorldInfo(SLONG lIndex)
{
	TPOS_EVENT_REQUESTWORLDINFO	request;
	int	result;

	request.dwIndex = lIndex;
	result = PosSendDataToDoor(REQUEST_WORLD_INFO, (char*)&request, sizeof(request));

#ifdef	DEBUG_MSG
    log_encrypt_message(1, "    request_for_world_info(%d)", lIndex);
#endif//DEBUG_MSG

	return	result;
}

int		ClientRequestRegisterAccountChecking(CHAR *szAccount, CHAR *szPassword)
{
	TPOS_EVENT_REGISTERACCOUNTCHECK	request;
	int	result;

	strcpy(request.cId, szAccount);
	strcpy(request.cPw, szPassword);
	result = PosSendDataToDoor(REGISTER_ACCOUNT_CHECK, (char *)&request, sizeof(request));

#ifdef	DEBUG_MSG
    log_encrypt_message(1, "    request_register_account_checking(ac:%s, pw:%s)", szAccount, szPassword);
#endif//DEBUG_MSG

	return	result;
}

int		ClientRequestChangeAccountPassword(CHAR *szAccount, CHAR *szPassword)
{
	TPOS_EVENT_CHANGEPASSWORD	request;
	int	result;

	//Dll saved szAccount, so skip szAccount assignment here.
	strcpy(request.cPw, szPassword);
	result = PosSendDataToDoor(CHANGE_PASSWORD, (char *)&request, sizeof(request));

#ifdef	DEBUG_MSG
    log_encrypt_message(1, "    request_change_password(ac:%s, pw:%s)", szAccount, szPassword);
#endif//DEBUG_MSG

	return	result;
}

int		ClientRequestRegisterAccountFinal(TPOS_EVENT_REGISTERACCOUNT *lpRA)
{
	int	result;

	result = PosSendDataToDoor(REGISTER_ACCOUNT_FINAL, (char *)lpRA, sizeof(*lpRA));

#ifdef	DEBUG_MSG
    log_encrypt_message(1, "    request_register_account_final");
#endif//DEBUG_MSG

	return	result;
}

/************************************************************************************************************/
/* SEND MESSAGE TO WORLD SERVER FUNCTIONS                                                                   */
/************************************************************************************************************/
int		ClientLoginWorld(HWND hWnd, char* szServerName, SLONG port, CHAR *szID, CHAR* szPassword, DWORD dwVersion)
{
	int	result;

	result = PosLoginWorld(hWnd, szServerName, port, szID, szPassword, dwVersion);

#ifdef	DEBUG_MSG
    log_encrypt_message(1, "    request_login_world(%s:%d, id:%s, pw:%s, ver:%d)", 
		szServerName, port, szID, szPassword, dwVersion);
#endif//DEBUG_MSG

	return	result;
}

int		ClientLogoutWorld(void)
{
	int	result;

	result = PosLogoutWorld();

#ifdef	DEBUG_MSG
    log_encrypt_message(1, "    request_logout_world");
#endif//DEBUG_MSG

	return	result;
}

int		ClientRequestForCharacterInfo(CHAR *szAccount, SLONG lIndex)
{
	TPOS_EVENT_REQUESTCHARACTERINFO	request;
	int	result;

	//Dll saved szAccount, so skip szAccount assignment here.
	request.iIndex = lIndex;
	result = PosSendDataToWorld(REQUEST_CHARACTER_INFO, (char*)&request, sizeof(request));

#ifdef	DEBUG_MSG
    log_encrypt_message(1, "    request_for_character_info(idx:%d)", lIndex);
#endif//DEBUG_MSG

	return	result;
}

int		ClientRequestChooseCharacter(ULONG uQQID)
{
	TPOS_EVENT_CHARACTERSELECTED	request;
	int	result;

	request.QQID = uQQID;
	result = PosSendDataToWorld(CHARACTER_SELECTED, (char*)&request, sizeof(request));

#ifdef	DEBUG_MSG
    log_encrypt_message(1, "    request_choose_character(%d)", uQQID);
#endif//DEBUG_MSG

	return	result;

}

int		ClientRequestLoginZone(CHAR *szZoneName)
{
	TPOS_EVENT_REQUESTLOGINZONE	request;
	int	result;
	
	strcpy(request.cZone, szZoneName);
	result = PosSendDataToWorld(PLAYER_REQUEST_LOGIN_ZONE, (char*)&request, sizeof(request));
	
#ifdef	DEBUG_MSG
    log_encrypt_message(1, "    request_login_zone(%s)", szZoneName);
#endif//DEBUG_MSG
	
	return	result;
}

int		ClientRequestDeleteCharacter(CHAR *szMainName)
{
	TPOS_EVENT_DELETECHARACTER	request;
	int	result;
	
	strcpy(request.cMainName, szMainName);
	result = PosSendDataToWorld(DELETE_CHARACTER, (char*)&request, sizeof(request));

#ifdef	DEBUG_MSG
    log_encrypt_message(1, "    request_delete_character(%s)", szMainName);
#endif//DEBUG_MSG

	return	result;
}

int		ClientRequestForDefaultCharacterInfo(SLONG lIndex)
{
	TPOS_EVENT_REQUESTCHARACTERDEFAULT	request;
	int	result;

	request.iIndex = lIndex;
	result = PosSendDataToWorld(REQUEST_CHARACTER_DEFAULT, (char*)&request, sizeof(request));

#ifdef	DEBUG_MSG
    log_encrypt_message(1, "    request_for_default_character_info(idx:%d)", lIndex);
#endif//DEBUG_MSG

	return	result;
}

int		ClientRequestCreateCharacterChecking(CHAR *szMainName)
{
	TPOS_EVENT_CREATECHARACTERCHECK	request;
	int	result;

	strcpy(request.cMainName, szMainName);
	result = PosSendDataToWorld(CREATE_CHARACTER_CHECK, (char*)&request, sizeof(request));

#ifdef	DEBUG_MSG
    log_encrypt_message(1, "    request_create_character_checking(%s)", szMainName);
#endif//DEBUG_MSG

	return	result;
}


int		ClientRequestCreateCharacterFinal(TPOS_EVENT_CREATECHARACTERFINAL *lpCCF)
{
	int	result;

	result = PosSendDataToWorld(CREATE_CHARACTER_FINAL, (char*)lpCCF, sizeof(*lpCCF));

#ifdef	DEBUG_MSG
    log_encrypt_message(1, "    request_create_character_final");
#endif//DEBUG_MSG

	return	result;
}

/************************************************************************************************************/
/* SEND MESSAGE TO ZONE SERVER FUNCTIONS                                                                    */
/************************************************************************************************************/
int		ClientLoginZone(HWND hWnd, char *szServerName, int lPort, char *szMainName, DWORD dwVersion)
{
	int	result;

	result = PosLoginZone(hWnd, szServerName, lPort, szMainName, dwVersion);

#ifdef	DEBUG_MSG
    log_encrypt_message(1, "    request_login_zone(%s:%d, mainname:%s, ver:%d)",
		szServerName, lPort, szMainName, dwVersion);
#endif//DEBUG_MSG

	return	result;
}

int		ClientLogoutZone(void)
{
	int	result;

	result = PosLogoutZone();

#ifdef	DEBUG_MSG
    log_encrypt_message(1, "    request_logout_zone");
#endif//DEBUG_MSG

	return	result;
}

int		ClientRequestExitGame(void)
{
	int	result;

	result = PosSendDataToZone(REQUEST_EXIT_GAME, NULL, 0);

#ifdef	DEBUG_MSG
    log_encrypt_message(1, "    request_exit_game");
#endif//DEBUG_MSG

	return	result;
}


int		ClientRequestForPlayerList(SLONG lIndex)
{
	TPOS_EVENT_REQUESTPLAYERLIST	request;
	int	result;

	request.iIndex = lIndex;
	result = PosSendDataToZone(REQUEST_PLAYER_LIST, (char*)&request, sizeof(request));

#ifdef	DEBUG_MSG
    log_encrypt_message(1, "    request_player_list(%d)", lIndex);
#endif//DEBUG_MSG

	return	result;
}



int		ClientRequestGameStart(void)
{
	int	result;

	result = PosSendDataToZone(GAME_START, NULL, 0);

#ifdef	DEBUG_MSG
    log_encrypt_message(1, "    request_game_start");
#endif//DEBUG_MSG

	return	result;
}


int		ClientRequestLeftHitMap(SLONG lX, SLONG lY)
{
	TPOS_EVENT_HITMAP	request;
	int	result;

	request.dwLeftRight = LEFT;
	request.lX = lX;
	request.lY = lY;
	request.lZ = 0;

	result = PosSendDataToZone(HIT_MAP, (char*)&request, sizeof(request));

#ifdef	DEBUG_MSG
    log_encrypt_message(1, "    request_left_hit_map(%d,%d)", lX, lY);
#endif//DEBUG_MSG

	return	result;
}


int		ClientRequestRightHitMap(SLONG lX, SLONG lY)
{
	TPOS_EVENT_HITMAP	request;
	int	result;

	request.dwLeftRight = RIGHT;
	request.lX = lX;
	request.lY = lY;
	request.lZ = 0;

	result = PosSendDataToZone(HIT_MAP, (char*)&request, sizeof(request));

#ifdef	DEBUG_MSG
    log_encrypt_message(1, "    request_right_hit_map(%d, %d)", lX, lY);
#endif//DEBUG_MSG

	return	result;
}


int		ClientRequestLeftHitNpc(SLONG lDestIndex)
{
	TPOS_EVENT_HITNPC	request;
	int	result;

	request.dwLeftRight = LEFT;
	request.dwDestNPC = lDestIndex;

	result = PosSendDataToZone(HIT_NPC, (char*)&request, sizeof(request));

#ifdef	DEBUG_MSG
    log_encrypt_message(1, "    request_left_hit_npc(%d)", lDestIndex);
#endif//DEBUG_MSG

	return	result;
}


int		ClientRequestRightHitNpc(SLONG lDestIndex)
{
	TPOS_EVENT_HITNPC	request;
	int	result;

	request.dwLeftRight = RIGHT;
	request.dwDestNPC = lDestIndex;

	result = PosSendDataToZone(HIT_NPC, (char*)&request, sizeof(request));

#ifdef	DEBUG_MSG
    log_encrypt_message(1, "    request_right_hit_npc(%d)", lDestIndex);
#endif//DEBUG_MSG

	return	result;
}


int		ClientRequestOpenBag(void)
{
	TPOS_EVENT_BAGSWITCH	request;
	int	result;

	request.dwBag = OPEN_BAG;
	result = PosSendDataToZone(SEND_BAG_SWITCH, (char*)&request, sizeof(request));

#ifdef	DEBUG_MSG
    log_encrypt_message(1, "    request_open_bag");
#endif//DEBUG_MSG

	return	result;
}


int		ClientRequestCloseBag(void)
{
	TPOS_EVENT_BAGSWITCH	request;
	int	result;

	request.dwBag = CLOSE_BAG;
	result = PosSendDataToZone(SEND_BAG_SWITCH, (char*)&request, sizeof(request));

#ifdef	DEBUG_MSG
    log_encrypt_message(1, "    request_close_bag");
#endif//DEBUG_MSG

	return	result;
}


int		ClientRequestSwitchAttackState(void)
{
	int	result;

	result = PosSendDataToZone(SEND_ATTACK_SWITCH, NULL, 0);

#ifdef	DEBUG_MSG
    log_encrypt_message(1, "    request_switch_attack_state");
#endif//DEBUG_MSG

	return	result;
}


int		ClientRequestAddBaseStrength(SLONG lData)
{
	TPOS_EVENT_UPDATENPCBASEDATA	request;
	int	result;

	request.update_type = UPDATE_NPC_BASE_STRENGTH;
	request.update_value = lData;
	result = PosSendDataToZone(UPDATE_NPC_BASE_DATA, (char*)&request, sizeof(request));

#ifdef	DEBUG_MSG
    log_encrypt_message(1, "    request_add_base_strength(%d)", lData);
#endif//DEBUG_MSG

	return	result;
}


int		ClientRequestAddBaseInstinct(SLONG lData)
{
	TPOS_EVENT_UPDATENPCBASEDATA	request;
	int	result;

	request.update_type = UPDATE_NPC_BASE_INSTINCT;
	request.update_value = lData;
	result = PosSendDataToZone(UPDATE_NPC_BASE_DATA, (char*)&request, sizeof(request));

#ifdef	DEBUG_MSG
    log_encrypt_message(1, "    request_add_base_instinct(%d)", lData);
#endif//DEBUG_MSG

	return	result;
}


int		ClientRequestAddBaseWit(SLONG lData)
{
	TPOS_EVENT_UPDATENPCBASEDATA	request;
	int	result;

	request.update_type = UPDATE_NPC_BASE_WIT;
	request.update_value = lData;
	result = PosSendDataToZone(UPDATE_NPC_BASE_DATA, (char*)&request, sizeof(request));

#ifdef	DEBUG_MSG
    log_encrypt_message(1, "    request_add_base_wit(%d)", lData);
#endif//DEBUG_MSG

	return	result;
}


int		ClientRequestAddBaseLucky(SLONG lData)
{
	TPOS_EVENT_UPDATENPCBASEDATA	request;
	int	result;

	request.update_type = UPDATE_NPC_BASE_LUCK;
	request.update_value = lData;
	result = PosSendDataToZone(UPDATE_NPC_BASE_DATA, (char*)&request, sizeof(request));

#ifdef	DEBUG_MSG
    log_encrypt_message(1, "    request_add_lucky(%d)", lData);
#endif//DEBUG_MSG

	return	result;
}


int		ClientRequestSubBaseStrength(SLONG lData)
{
	TPOS_EVENT_UPDATENPCBASEDATA	request;
	int	result;

	request.update_type = UPDATE_NPC_BASE_STRENGTH;
	request.update_value = -lData;
	result = PosSendDataToZone(UPDATE_NPC_BASE_DATA, (char*)&request, sizeof(request));

#ifdef	DEBUG_MSG
    log_encrypt_message(1, "    request_sub_strength(%d)", lData);
#endif//DEBUG_MSG

	return	result;
}


int		ClientRequestSubBaseInstinct(SLONG lData)
{
	TPOS_EVENT_UPDATENPCBASEDATA	request;
	int	result;

	request.update_type = UPDATE_NPC_BASE_INSTINCT;
	request.update_value = -lData;
	result = PosSendDataToZone(UPDATE_NPC_BASE_DATA, (char*)&request, sizeof(request));

#ifdef	DEBUG_MSG
    log_encrypt_message(1, "    request_sub_instinct(%d)", lData);
#endif//DEBUG_MSG

	return	result;
}


int		ClientRequestSubBaseWit(SLONG lData)
{
	TPOS_EVENT_UPDATENPCBASEDATA	request;
	int result;

	request.update_type = UPDATE_NPC_BASE_WIT;
	request.update_value = -lData;
	result = PosSendDataToZone(UPDATE_NPC_BASE_DATA, (char*)&request, sizeof(request));

#ifdef	DEBUG_MSG
    log_encrypt_message(1, "    request_sub_wit(%d)", lData);
#endif//DEBUG_MSG

	return	result;
}


int		ClientRequestSubBaseLucky(SLONG lData)
{
	TPOS_EVENT_UPDATENPCBASEDATA	request;
	int	result;

	request.update_type = UPDATE_NPC_BASE_LUCK;
	request.update_value = -lData;
	result = PosSendDataToZone(UPDATE_NPC_BASE_DATA, (char*)&request, sizeof(request));

#ifdef	DEBUG_MSG
    log_encrypt_message(1, "    request_sub_lucky(%d)", lData);
#endif//DEBUG_MSG

	return	result;
}


int		ClientRequestLeftHitEquipHead(void)
{
	TPOS_EVENT_REQUESTHITHEADITEM	request;
	SLONG	result;

	request.LR = LEFT;

	result = PosSendDataToZone(REQUEST_HIT_HEAD_ITEM, (char *)&request, sizeof(request));

#ifdef	DEBUG_MSG
    log_encrypt_message(1, "    request_left_hit_head_item");
#endif//DEBUG_MSG

	return	result;
}


int		ClientRequestRightHitEquipHead(void)
{
	TPOS_EVENT_REQUESTHITHEADITEM	request;
	SLONG	result;

	request.LR = RIGHT;

	result = PosSendDataToZone(REQUEST_HIT_HEAD_ITEM, (char *)&request, sizeof(request));

#ifdef	DEBUG_MSG
    log_encrypt_message(1, "    request_right_hit_head_item");
#endif//DEBUG_MSG

	return	result;
}


int		ClientRequestLeftHitEquipNeck(void)
{
	TPOS_EVENT_REQUESTHITNECKITEM	request;
	SLONG	result;

	request.LR = LEFT;

	result = PosSendDataToZone(REQUEST_HIT_NECK_ITEM, (char *)&request, sizeof(request));

#ifdef	DEBUG_MSG
    log_encrypt_message(1, "    request_left_hit_neck_item");
#endif//DEBUG_MSG

	return	result;
}


int		ClientRequestRightHitEquipNeck(void)
{
	TPOS_EVENT_REQUESTHITNECKITEM	request;
	SLONG	result;

	request.LR = RIGHT;

	result = PosSendDataToZone(REQUEST_HIT_NECK_ITEM, (char *)&request, sizeof(request));

#ifdef	DEBUG_MSG
    log_encrypt_message(1, "    request_right_hit_neck_item");
#endif//DEBUG_MSG

	return	result;
}


int		ClientRequestLeftHitEquipBody(void)
{
	TPOS_EVENT_REQUESTHITBODYITEM	request;
	SLONG	result;

	request.LR = LEFT;

	result = PosSendDataToZone(REQUEST_HIT_BODY_ITEM, (char *)&request, sizeof(request));

#ifdef	DEBUG_MSG
    log_encrypt_message(1, "    request_left_hit_body_item");
#endif//DEBUG_MSG

	return	result;
}


int		ClientRequestRightHitEquipBody(void)
{
	TPOS_EVENT_REQUESTHITBODYITEM	request;
	SLONG	result;

	request.LR = RIGHT;

	result = PosSendDataToZone(REQUEST_HIT_BODY_ITEM, (char *)&request, sizeof(request));

#ifdef	DEBUG_MSG
    log_encrypt_message(1, "    request_left_hit_body_item");
#endif//DEBUG_MSG

	return	result;
}


int		ClientRequestLeftHitEquipWeapon(void)
{
	TPOS_EVENT_REQUESTHITWEAPONITEM	request;
	SLONG	result;

	request.LR = LEFT;

	result = PosSendDataToZone(REQUEST_HIT_WEAPON_ITEM, (char *)&request, sizeof(request));

#ifdef	DEBUG_MSG
    log_encrypt_message(1, "    request_left_hit_weapon_item");
#endif//DEBUG_MSG

	return	result;
}


int		ClientRequestRightHitEquipWeapon(void)
{
	TPOS_EVENT_REQUESTHITWEAPONITEM	request;
	SLONG	result;

	request.LR = RIGHT;

	result = PosSendDataToZone(REQUEST_HIT_WEAPON_ITEM, (char *)&request, sizeof(request));

#ifdef	DEBUG_MSG
    log_encrypt_message(1, "    request_right_hit_weapon_item");
#endif//DEBUG_MSG

	return	result;
}


int		ClientRequestLeftHitEquipWaist(void)
{
	TPOS_EVENT_REQUESTHITWAISTITEM	request;
	SLONG	result;

	request.LR = LEFT;

	result = PosSendDataToZone(REQUEST_HIT_WAIST_ITEM, (char *)&request, sizeof(request));

#ifdef	DEBUG_MSG
    log_encrypt_message(1, "    request_left_hit_waist_item");
#endif//DEBUG_MSG

	return	result;
}


int		ClientRequestRightHitEquipWaist(void)
{
	TPOS_EVENT_REQUESTHITWAISTITEM	request;
	SLONG	result;

	request.LR = RIGHT;

	result = PosSendDataToZone(REQUEST_HIT_WAIST_ITEM, (char *)&request, sizeof(request));

#ifdef	DEBUG_MSG
    log_encrypt_message(1, "    request_right_hit_waist_item");
#endif//DEBUG_MSG

	return	result;
}


int		ClientRequestLeftHitEquipWrist(void)
{
	TPOS_EVENT_REQUESTHITWRISTITEM	request;
	SLONG	result;

	request.LR = LEFT;

	result = PosSendDataToZone(REQUEST_HIT_WRIST_ITEM, (char *)&request, sizeof(request));

#ifdef	DEBUG_MSG
    log_encrypt_message(1, "    request_left_hit_wrist_item");
#endif//DEBUG_MSG

	return	result;
}


int		ClientRequestRightHitEquipWrist(void)
{
	TPOS_EVENT_REQUESTHITWRISTITEM	request;
	SLONG	result;

	request.LR = RIGHT;

	result = PosSendDataToZone(REQUEST_HIT_WRIST_ITEM, (char *)&request, sizeof(request));

#ifdef	DEBUG_MSG
    log_encrypt_message(1, "    request_right_hit_wrist_item");
#endif//DEBUG_MSG

	return	result;
}


int		ClientRequestLeftHitEquipGlove(void)
{
	TPOS_EVENT_REQUESTHITGLOVEITEM	request;
	SLONG	result;

	request.LR = LEFT;

	result = PosSendDataToZone(REQUEST_HIT_GLOVE_ITEM, (char *)&request, sizeof(request));

#ifdef	DEBUG_MSG
    log_encrypt_message(1, "    request_left_hit_glove_item");
#endif//DEBUG_MSG

	return	result;
}


int		ClientRequestRightHitEquipGlove(void)
{
	TPOS_EVENT_REQUESTHITGLOVEITEM	request;
	SLONG	result;

	request.LR = RIGHT;

	result = PosSendDataToZone(REQUEST_HIT_GLOVE_ITEM, (char *)&request, sizeof(request));

#ifdef	DEBUG_MSG
    log_encrypt_message(1, "    request_right_hit_glove_item");
#endif//DEBUG_MSG

	return	result;
}


int		ClientRequestLeftHitEquipFeet(void)
{
	TPOS_EVENT_REQUESTHITFEETITEM	request;
	SLONG	result;

	request.LR = LEFT;

	result = PosSendDataToZone(REQUEST_HIT_FEET_ITEM, (char *)&request, sizeof(request));

#ifdef	DEBUG_MSG
    log_encrypt_message(1, "    request_left_hit_feet_item");
#endif//DEBUG_MSG

	return	result;
}


int		ClientRequestRightHitEquipFeet(void)
{
	TPOS_EVENT_REQUESTHITFEETITEM	request;
	SLONG	result;

	request.LR = RIGHT;

	result = PosSendDataToZone(REQUEST_HIT_FEET_ITEM, (char *)&request, sizeof(request));

#ifdef	DEBUG_MSG
    log_encrypt_message(1, "    request_right_hit_feet_item");
#endif//DEBUG_MSG

	return	result;
}


int		ClientRequestLeftHitEquipOtherA(void)
{
	TPOS_EVENT_REQUESTHITOTHERAITEM	request;
	SLONG	result;

	request.LR = LEFT;

	result = PosSendDataToZone(REQUEST_HIT_OTHERA_ITEM, (char *)&request, sizeof(request));

#ifdef	DEBUG_MSG
    log_encrypt_message(1, "    request_left_hit_othera_item");
#endif//DEBUG_MSG

	return	result;
}

int		ClientRequestRightHitEquipOtherA(void)
{
	TPOS_EVENT_REQUESTHITOTHERAITEM	request;
	SLONG	result;

	request.LR = RIGHT;

	result = PosSendDataToZone(REQUEST_HIT_OTHERA_ITEM, (char *)&request, sizeof(request));

#ifdef	DEBUG_MSG
    log_encrypt_message(1, "    request_right_hit_othera_item");
#endif//DEBUG_MSG

	return	result;
}


int		ClientRequestLeftHitEquipOtherB(void)
{
	TPOS_EVENT_REQUESTHITOTHERBITEM	request;
	SLONG	result;

	request.LR = LEFT;

	result = PosSendDataToZone(REQUEST_HIT_OTHERB_ITEM, (char *)&request, sizeof(request));

#ifdef	DEBUG_MSG
    log_encrypt_message(1, "    request_left_hit_otherb_item");
#endif//DEBUG_MSG

	return	result;
}

int		ClientRequestRightHitEquipOtherB(void)
{
	TPOS_EVENT_REQUESTHITOTHERBITEM	request;
	SLONG	result;

	request.LR = RIGHT;

	result = PosSendDataToZone(REQUEST_HIT_OTHERB_ITEM, (char *)&request, sizeof(request));

#ifdef	DEBUG_MSG
    log_encrypt_message(1, "    request_right_hit_otherb_item");
#endif//DEBUG_MSG

	return	result;
}


int		ClientRequestLeftHitEquipOtherC(void)
{
	TPOS_EVENT_REQUESTHITOTHERCITEM	request;
	SLONG	result;

	request.LR = LEFT;

	result = PosSendDataToZone(REQUEST_HIT_OTHERC_ITEM, (char *)&request, sizeof(request));

#ifdef	DEBUG_MSG
    log_encrypt_message(1, "    request_left_hit_otherc_item");
#endif//DEBUG_MSG

	return	result;
}


int		ClientRequestRightHitEquipOtherC(void)
{
	TPOS_EVENT_REQUESTHITOTHERCITEM	request;
	SLONG	result;

	request.LR = RIGHT;

	result = PosSendDataToZone(REQUEST_HIT_OTHERC_ITEM, (char *)&request, sizeof(request));

#ifdef	DEBUG_MSG
    log_encrypt_message(1, "    request_left_hit_otherc_item");
#endif//DEBUG_MSG

	return	result;
}


int		ClientRequestLeftHitBagItem(SLONG lBagIndex)
{
	TPOS_EVENT_REQUESTHITBAGITEM	request;
	SLONG	result;

	request.LR = LEFT;
	request.BagIndex = (UCHAR)lBagIndex;

	result = PosSendDataToZone(REQUEST_HIT_BAG_ITEM, (char *)&request, sizeof(request));

#ifdef	DEBUG_MSG
    log_encrypt_message(1, "    request_left_hit_bag_item(%d)", lBagIndex);
#endif//DEBUG_MSG

	return	result;
}


int		ClientRequestRightHitBagItem(SLONG lBagIndex)
{
	TPOS_EVENT_REQUESTHITBAGITEM	request;
	SLONG	result;

	request.LR = RIGHT;
	request.BagIndex = (UCHAR)lBagIndex;

	result = PosSendDataToZone(REQUEST_HIT_BAG_ITEM, (char *)&request, sizeof(request));

#ifdef	DEBUG_MSG
    log_encrypt_message(1, "    request_right_hit_bag_item(%d)", lBagIndex);
#endif//DEBUG_MSG

	return	result;
}


int		ClientRequestLeftHitSashItem(SLONG lSashIndex)
{
	TPOS_EVENT_REQUESTHITSASHITEM	request;
	SLONG	result;

	request.LR = LEFT;
	request.SashIndex = (UCHAR)lSashIndex;

	result = PosSendDataToZone(REQUEST_HIT_SASH_ITEM, (char *)&request, sizeof(request));

#ifdef	DEBUG_MSG
    log_encrypt_message(1, "    request_left_hit_sash_item(%d)", lSashIndex);
#endif//DEBUG_MSG

	return	result;
}


int		ClientRequestRightHitSashItem(SLONG lSashIndex)
{
	TPOS_EVENT_REQUESTHITSASHITEM	request;
	SLONG	result;

	request.LR = RIGHT;
	request.SashIndex = (UCHAR)lSashIndex;

	result = PosSendDataToZone(REQUEST_HIT_SASH_ITEM, (char *)&request, sizeof(request));

#ifdef	DEBUG_MSG
    log_encrypt_message(1, "    request_right_hit_sash_item(%d)", lSashIndex);
#endif//DEBUG_MSG

	return	result;
}


int		ClientRequestDropItem(SLONG map_x, SLONG map_y)
{
	TPOS_EVENT_REQUESTDROPITEM	request;
	SLONG	result;

	request.X = map_x;
	request.Y = map_y;

	result = PosSendDataToZone(REQUEST_DROP_ITEM, (char *)&request, sizeof(request));

#ifdef	DEBUG_MSG
    log_encrypt_message(1, "    request_drop_item(%d, %d)", map_x, map_y);
#endif//DEBUG_MSG

	return	result;
}


int		ClientRequestLeftHitMapItem(SLONG item_x, SLONG item_y)
{
	TPOS_EVENT_REQUESTHITMAPITEM	request;
	int	result;

	request.LR = LEFT;
	request.X = item_x;
	request.Y = item_y;

	result = PosSendDataToZone(REQUEST_HIT_MAP_ITEM, (char *)&request, sizeof(request));

#ifdef	DEBUG_MSG
    log_encrypt_message(1, "    request_left_hit_map_item(%d, %d)", item_x, item_y);
#endif//DEBUG_MSG

	return	result;
}


int		ClientRequestRightHitMapItem(SLONG item_x, SLONG item_y)
{
	TPOS_EVENT_REQUESTHITMAPITEM	request;
	int	result;

	request.LR = RIGHT;
	request.X = item_x;
	request.Y = item_y;

	result = PosSendDataToZone(REQUEST_HIT_MAP_ITEM, (char *)&request, sizeof(request));

#ifdef	DEBUG_MSG
    log_encrypt_message(1, "    request_right_hit_map_item(%d, %d)", item_x, item_y);
#endif//DEBUG_MSG

	return	result;
}


int		ClientRequestChangeLeftHandMagic(SLONG lMagicNo)
{
	TPOS_EVENT_CHANGEMOUSESKILL	request;
	int	result;

	request.dwLeftRight = LEFT;
	request.dwSkill = lMagicNo;

	result = PosSendDataToZone(CHANGE_MOUSE_SKILL, (char*)&request, sizeof(request));

#ifdef	DEBUG_MSG
    log_encrypt_message(1, "    request_change_left_hand_magic(%d)", lMagicNo);
#endif//DEBUG_MSG

	return	result;
}


int		ClientRequestChangeRightHandMagic(SLONG lMagicNo)
{
	TPOS_EVENT_CHANGEMOUSESKILL	request;
	int	result;

	request.dwLeftRight = RIGHT;
	request.dwSkill = lMagicNo;

	result = PosSendDataToZone(CHANGE_MOUSE_SKILL, (char*)&request, sizeof(request));

#ifdef	DEBUG_MSG
    log_encrypt_message(1, "    request_change_right_hand_magic(%d)", lMagicNo);
#endif//DEBUG_MSG

	return	result;
}


int		ClientRequestLeftEndHitMap(SLONG lX, SLONG lY)
{
	TPOS_EVENT_HITMAP	request;
	int	result;

	request.dwLeftRight = LEFT;
	request.lX = lX;
	request.lY = lY;
	request.lZ = 0;

	result = PosSendDataToZone(END_HIT_MAP, (char*)&request, sizeof(request));

#ifdef	DEBUG_MSG
    log_encrypt_message(1, "    request_left_end_hit_map(x:%d, y:%d)", lX, lY);
#endif//DEBUG_MSG

	return	result;
}


int		ClientRequestRightEndHitMap(SLONG lX, SLONG lY)
{
	TPOS_EVENT_HITMAP	request;
	int	result;

	request.dwLeftRight = RIGHT;
	request.lX = lX;
	request.lY = lY;
	request.lZ = 0;

	result = PosSendDataToZone(END_HIT_MAP, (char*)&request, sizeof(request));

#ifdef	DEBUG_MSG
    log_encrypt_message(1, "    request_right_end_hit_map(x:%d, y:%d)", lX, lY);
#endif//DEBUG_MSG

	return	result;
}


int		ClientRequestSendPublicTalk(SLONG lDoingKind, SLONG lPlayerIndex, char *szMsg)
{
	TPOS_EVENT_GETPUBLICTALK	request;
	SLONG	result;

	request.dwSendIndex = lPlayerIndex;
	request.dwTargetIndex = 0;
	request.dwType = 0;
	request.lDoing_kind = lDoingKind;
	strcpy((char *)request.cMsg, (const char *)szMsg);

	result = PosSendDataToZone(GET_PUBLIC_TALK, (char*)&request, sizeof(request));

#ifdef	DEBUG_MSG
    log_encrypt_message(1, "    request_send_public_talk(do:%d, player:%d, msg:%s", lDoingKind, lPlayerIndex, szMsg);
#endif//DEBUG_MSG

	return	result;
}


int		ClientRequestChangeWeather(SLONG lType, SLONG lActive, SLONG lSize, SLONG lWindSize, SLONG lWindDir)
{
	TPOS_EVENT_REQUESTCHANGEWEATHER	request;
	SLONG	result;

	request.dType = lType;
	request.dActive = lActive;
	request.dSize = lSize;
	request.dWindSize = lWindSize;
	request.dWindDir = lWindDir;

	result = PosSendDataToZone(REQUEST_CHANGE_WEATHER, (char*)&request, sizeof(request));

#ifdef	DEBUG_MSG
    log_encrypt_message(1, "    request_change_weather(type:%d, active:%d, size:%d, winsize:%d, windir:%d)",
		lType, lActive, lSize, lWindSize, lWindDir);
#endif//DEBUG_MSG

	return	result;
}


int		ClientRequestSetLeftHandQuickSkill(SLONG quick_index, SLONG magic_no)
{
	TPOS_EVENT_SETHANDQUICKSKILL	request;
	SLONG	result;

	request.Hand = LEFT;
	request.QuickIndex = quick_index;
	request.SkillNo = magic_no;
	result = PosSendDataToZone(REQUEST_SET_HAND_QUICK_SKILL, (char *)&request, sizeof(request));

#ifdef	DEBUG_MSG
    log_encrypt_message(1, "    request_set_left_hand_quick_skill(idx:%d, skill:%d)", 
		quick_index, magic_no);
#endif//DEBUG_MSG

	return	result;
}

int		ClientRequestSetRightHandQuickSkill(SLONG quick_index, SLONG magic_no)
{
	TPOS_EVENT_SETHANDQUICKSKILL	request;
	SLONG	result;

	request.Hand = RIGHT;
	request.QuickIndex = quick_index;
	request.SkillNo = magic_no;
	result = PosSendDataToZone(REQUEST_SET_HAND_QUICK_SKILL, (char *)&request, sizeof(request));

#ifdef	DEBUG_MSG
    log_encrypt_message(1, "    request_set_right_hand_quick_skill(idx:%d, skill:%d)", 
		quick_index, magic_no);
#endif//DEBUG_MSG

	return	result;
}

int		ClientRequestQuickSetHandSkill(SLONG quick_index)
{
	TPOS_EVENT_USEHANDQUICKSKILL	request;
	SLONG	result;

	request.QuickIndex = quick_index;
	result = PosSendDataToZone(REQUEST_USE_HAND_QUICK_SKILL, (char *)&request, sizeof(request));

#ifdef	DEBUG_MSG
    log_encrypt_message(1, "    request_quick_set_hand_skill(idx:%d)", quick_index);
#endif//DEBUG_MSG

	return	result;
}

/************************************************************************************************************/
/* QQ FUNCTIONS                                                                                             */
/************************************************************************************************************/
int		ClientRequestQQMyData(void)
{
	// Jack, TODO [1/3/2003]
	return	0;
}

int		ClientRequestQQFriendList(SLONG lIndex)
{
	// Jack, TODO [1/3/2003]
	return	0;
}

int		ClientRequestQQGuildFriendList(SLONG lIndex)
{
	// Jack, TODO [1/3/2003]
	return	0;
}

int		ClientRequestQQTeamFriendList(SLONG lIndex)
{
	// Jack, TODO [1/3/2003]
	return	0;
}

int		ClientRequestQQSetMyState(CHAR cState)
{
	TPOS_EVENT_QQREQUESTSETMYSTATE MyState;
	SLONG result;

	MyState.ID = qfm_get_sid( );
	MyState.State = cState;

	result = PosSendDataToZone( QQ_SET_MYSTATE, (CHAR*)&MyState, sizeof(MyState) );

#ifdef	DEBUG_MSG
    log_encrypt_message(1, "    request_qq_set_my_state" );
#endif//DEBUG_MSG

	return	result;
}

int		ClientRequestQQSetMyConfig(ULONG uSettings)
{
	// Jack, TODO [1/3/2003]
	return	0;
}

int		ClientRequestQQQuerySomeone(ULONG uID)
{
	TPOS_EVENT_QQREQUESTQUERYSOMEONE SomeOne;
	SLONG result;

	SomeOne.TargetID = uID;
	SomeOne.RequestID = qfm_get_sid( );
	
	result = PosSendDataToZone( QQ_REQUEST_QUERY_SOMEONE, (CHAR*)&SomeOne, sizeof( SomeOne ) );

#ifdef	DEBUG_MSG
    log_encrypt_message(1, "    request_qq_query_someone(id : %d)", uID );
#endif//DEBUG_MSG

	return	result;
}

int		ClientRequestQQAddSomeone(ULONG uID, UCHAR cRelation )
{
	TPOS_EVENT_QQREQUESTADDSOMEONE AddSomeone;
	SLONG result;
	
	AddSomeone.Relation = cRelation;
	AddSomeone.TargetID = uID;
	AddSomeone.RequestID = qfm_get_sid( );
	
	result = PosSendDataToZone( QQ_REQUEST_ADD_SOMEONE, (CHAR*)&AddSomeone, sizeof( AddSomeone ) );

#ifdef	DEBUG_MSG
    log_encrypt_message(1, "    request_qq_add_someone(id : %d)", uID );
#endif//DEBUG_MSG

	return	result;
}

int		ClientRequestQQDeleteFriend(ULONG uID)
{
	POS_EVENT_QQGETDELFRIEND DelFriend;
	SLONG result;
	
	DelFriend.TargetID = uID;
	DelFriend.RequestID = qfm_get_sid( );
	
	result = PosSendDataToZone( QQ_REQUEST_DEL_FRIEND, (CHAR*)&DelFriend, sizeof(DelFriend) );
	
#ifdef DEBUG_MSG
	log_encrypt_message(1,"    ClientRequestQQDeleteFriend(id : %d)", uID );
#endif
	return	result;
}

int		ClientRequestQQDeleteGuildFriend(ULONG uID)
{
	POS_EVENT_QQREQUESTDELGUILDFRIEND DelFriend;
	SLONG result;
	
	DelFriend.TargetID = uID;
	DelFriend.RequestID = qfm_get_sid( );
	
	result = PosSendDataToZone( QQ_REQUEST_DEL_GUILD_FRIEND, (CHAR*)&DelFriend, sizeof(DelFriend) );
	
#ifdef DEBUG_MSG
	log_encrypt_message(1,"    ClientRequestQQDeleteFriend(id : %d)", uID );
#endif
	return	result;
}

int		ClientRequestQQPlayerCount(void)
{
	TPOS_EVENT_QQREQUESTPLAYERCOUNT PlayerCount;
	SLONG result;

	PlayerCount.RequestID = qfm_get_sid( );

	result = PosSendDataToZone( QQ_REQUEST_PLAYER_COUNT, (CHAR*)&PlayerCount, sizeof(PlayerCount) );

#ifdef	DEBUG_MSG
    log_encrypt_message(1, "    request_qq_player_count" );
#endif//DEBUG_MSG

	return	result;
}

int		ClientRequestQQSendMessageToSomeone(ULONG uToID, CHAR* szText)
{
	TPOS_EVENT_QQREQUESTSENDMSGTOONE SendMsg;
	SLONG result;

	SendMsg.RecvID = uToID;
	SendMsg.SendID = qfm_get_sid( );
	lstrcpyn( SendMsg.Msg, szText, 200 );

	result = PosSendDataToZone( QQ_SEND_2ONE_MSG, (CHAR*)&SendMsg, sizeof(SendMsg) );

#ifdef	DEBUG_MSG
    log_encrypt_message(1, "    request_qq_send_message_to_someone(id: %d)", uToID );
#endif//DEBUG_MSG

	return	0;
}

int		ClientRequestQQQueryOnlineAddList( ULONG uIndex )
{
	SLONG result;
	TPOS_EVENT_QQREQUESTQUERYONLINELIST OnlineList;

	OnlineList.BookMark = uIndex;
	OnlineList.RequestID = qfm_get_sid( );
	OnlineList.ZoneIndex = 0;

	result = PosSendDataToZone( QQ_REQUEST_QUERY_ONLINE_ADDLIST, (CHAR*)&OnlineList, sizeof( OnlineList ) );

#ifdef	DEBUG_MSG
    log_encrypt_message(1, "    request_qq_query_online_add_list(index: %d)", uIndex);
#endif//DEBUG_MSG

	return result;
}


int		ClientRequestQQHitTransItem( char r_l, UCHAR index )
{
	SLONG result;
	TPOS_EVENT_REQUESTHITTRANSITEM TransItem;

	TransItem.LR = r_l;
	TransItem.TransIndex = index;

	result = PosSendDataToZone( REQUEST_HIT_TRANS_ITEM, (CHAR*)&TransItem, sizeof(TransItem) );

#ifdef DEBUG_MSG
	log_encrypt_message( 1, "    request_qq_hit_trans_item(index: %d)", index);
#endif	//DEBUG_MSG

	return result;
}


int		ClientRequestQQTransferItem( DWORD ID )
{
	SLONG result;
	TPOS_EVENT_QQREQUESTTRANSFERITEM TransItem;

	TransItem.RequestID = qfm_get_sid( );
	TransItem.TargetID = ID;

	result = PosSendDataToZone( QQ_REQUEST_TRANSFER_ITEM, (CHAR*)&TransItem, sizeof(TransItem) );

#ifdef DEBUG_MSG
	log_encrypt_message( 1, "    request_qq_transfer_item(id: %d )", ID );
#endif	// DEBUG_MSG

	return result;
}

/************************************************************************************************************/
/* SCRIPT FUNCTIONS                                                                                         */
/************************************************************************************************************/
int		ClientRequestNpcProc(SLONG lNpcNo, SLONG lProcNo)
{
	TPOS_EVENT_REQUESTNPCPROC	request;
	SLONG	result;

	request.TargetNPCIndex = lNpcNo;
	request.NextProc = lProcNo;

	result = PosSendDataToZone(REQUEST_NPC_PROC, (char *)&request, sizeof(request));

#ifdef	DEBUG_MSG
    log_encrypt_message(1, "    request_npc_proc(npc:%d, proc:%d)", lNpcNo, lProcNo);
#endif//DEBUG_MSG

	return	result;
}


int		ClientRequestChangeDir(SLONG lDir)
{
	TPOS_EVENT_REQUESTCHANGEDIR	request;
	SLONG	result;

	request.Dir = (char)lDir;
	result = PosSendDataToZone(REQUEST_CHANGE_DIR, (char *)&request, sizeof(request));

#ifdef	DEBUG_MSG
    log_encrypt_message(1, "    request_change_dir(dir:%d)", lDir);
#endif//DEBUG_MSG

	return	result;
}


int		ClientRequestBuyItem(SLONG lStoreIndex, SLONG lIndex)
{
	TPOS_EVENT_REQUESTBUYITEM	request;
	SLONG	result;

	request.ZoneStoreIndex = lStoreIndex;
	request.ItemIndex = lIndex;
	result = PosSendDataToZone(REQUEST_BUY_ITEM, (char *)&request, sizeof(request));

#ifdef	DEBUG_MSG
    log_encrypt_message(1, "    request_buy_item(store:%d, item_index:%d)", lStoreIndex, lIndex);
#endif//DEBUG_MSG
	return	result;
}

int		ClientRequestSellItem(SLONG lStoreIndex)
{
	TPOS_EVENT_REQUESTSELLITEM	request;
	SLONG	result;

	request.ZoneStoreIndex = lStoreIndex;
	result = PosSendDataToZone(REQUEST_SELL_ITEM, (char *)&request, sizeof(request));

#ifdef	DEBUG_MSG
    log_encrypt_message(1, "    request_sell_item(store:%d)", lStoreIndex);
#endif//DEBUG_MSG
	return	result;
}

//銀行相關 ---------------------------------------------------------------

int		ClientRequestSaveMoney( SLONG lMoney )
{
	TPOS_EVENT_REQUESTSAVEMONEY	request;
	SLONG	result;
	
	request.Money = lMoney;
	result = PosSendDataToZone( REQUEST_SAVE_MONEY, (char*)&request, sizeof(request) );

#ifdef DEBUG_MSG
    log_encrypt_message(1, "    request_save_money( money: %d )", request.Money);
#endif

	return result;
}

int		ClientRequestLoadMoney( SLONG lMoney )
{
	TPOS_EVENT_REQUESTLOADMONEY	request;
	SLONG	result;

	request.Money = lMoney;
	result = PosSendDataToZone( REQUEST_LOAD_MONEY, (char*)&request, sizeof(request) );

#ifdef DEBUG_MSG
	log_encrypt_message(1, "    request_load_money( money: %d )", request.Money );
#endif

	return result;
}

int		ClientRequestHitBankItem( UHINT lBankIndex )
{
	TPOS_EVENT_REQUESTHITBANKITEM	request;
	SLONG	result;

	request.Index = lBankIndex;
	result = PosSendDataToZone( REQUEST_HIT_BANK_ITEM, (char*)&request, sizeof(request) );

#ifdef DEBUG_MSG
	log_encrypt_message( 1, "    request_hit_bank_item( index: %d )", request.Index );
#endif
	return result;
}

//------------------------------------------------------------------------
int		ClientGodRequestPropertyPoint(SLONG points)
{
	TPOS_GOD_REQUESTPROPERTYPOINT	request;
	SLONG	result;

	request.Point = points;
	result = PosSendDataToZone(GOD_REQUEST_PROPERTYPOINT, (char *)&request, sizeof(request));

#ifdef	DEBUG_MSG
    log_encrypt_message(1, "    god_request_property_point(point:%d)", points);
#endif//DEBUG_MSG

	return	result;
}


int		ClientGodRequestFullHpMp(void)
{
	SLONG	result;

	result = PosSendDataToZone(GOD_REQUEST_FULLHPMP, NULL, 0);

#ifdef	DEBUG_MSG
    log_encrypt_message(1, "    god_request_full_hpmp()");
#endif//DEBUG_MSG

	return	result;
}


int		ClientGodRequestJumpTo(SLONG lX, SLONG lY, SLONG lZ)
{
	TPOS_GOD_REQUESTJUMPTO	request;
	SLONG	result;

	request.X = lX;
	request.Y = lY;
	request.Z = lZ;
	result = PosSendDataToZone(GOD_REQUEST_JUMPTO, (char *)&request, sizeof(request));

#ifdef	DEBUG_MSG
    log_encrypt_message(1, "    god_request_jumpto(%d, %d, %d)", lX, lY, lZ);
#endif//DEBUG_MSG

	return	result;
}

int		ClientGodRequestItem(UHINT uBaseID)
{
	TPOS_GOD_REQUESTITEM	request;
	SLONG	result;

	request.BaseID = uBaseID;
	result = PosSendDataToZone(GOD_REQUEST_ITEM, (char *)&request, sizeof(request));

#ifdef	DEBUG_MSG
    log_encrypt_message(1, "    god_request_item(%d)", uBaseID);
#endif//DEBUG_MSG

	return	result;
}

int		ClientGodRequestMoney(ULONG uMoney)
{
	TPOS_GOD_REQUESTMONEY	request;
	SLONG	result;

	request.Money = uMoney;
	result = PosSendDataToZone(GOD_REQUEST_MONEY, (char *)&request, sizeof(request));

#ifdef	DEBUG_MSG
    log_encrypt_message(1, "    god_request_money(%d)", uMoney);
#endif//DEBUG_MSG

	return	result;
}

int		ClientGodRequestExp(ULONG uExp)
{
	TPOS_GOD_REQUESTEXP	request;
	SLONG	result;

	request.Exp = uExp;
	result = PosSendDataToZone(GOD_REQUEST_EXP, (char *)&request, sizeof(request));

#ifdef	DEBUG_MSG
    log_encrypt_message(1, "    god_request_exp(%u)", uExp);
#endif//DEBUG_MSG

	return	result;
}

int		ClientGodRequestMoveFast(ULONG uSpeed)
{
	TPOS_GOD_REQUESTMOVEFAST	request;
	SLONG	result;

	request.MoveSpeed = uSpeed;
	result = PosSendDataToZone(GOD_REQUEST_MOVEFAST, (char *)&request, sizeof(request));

#ifdef	DEBUG_MSG
    log_encrypt_message(1, "    god_request_movefast(%d)", uSpeed);
#endif//DEBUG_MSG

	return	result;
}

int		ClientGodRequestChangeZone(CHAR *szZoneName, SLONG lX, SLONG lY, SLONG lZ)
{
	TPOS_GOD_REQUESTCHANGEZONE	request;
	SLONG	result;

	strcpy(request.ZoneName, szZoneName);
	request.X = lX;
	request.Y = lY;
	request.Z = lZ;
	result = PosSendDataToZone(GOD_REQUEST_CHANGEZONE, (char *)&request, sizeof(request));

#ifdef	DEBUG_MSG
    log_encrypt_message(1, "    god_request_changezone(%s, %d, %d, %d)", szZoneName, lX, lY, lZ);
#endif//DEBUG_MSG

	return	result;
}


int		ClientGodRequestDead(void)
{
	SLONG	result;

	result = PosSendDataToZone(GOD_REQUEST_DEAD, NULL, 0);

#ifdef	DEBUG_MSG
    log_encrypt_message(1, "    god_request_dead()");
#endif//DEBUG_MSG

	return	result;
}

int ClientGodRequestTreasureMap( SLONG Index, SLONG PieceIndex )
{
    SLONG result;
    TPOS_GOD_REQUESTGETMAP Info;
    
    Info.Index = (UHINT)Index;
    Info.PieceIndex = (UHINT)PieceIndex;

    result = PosSendDataToZone( GOD_REQUEST_GET_MAP, (char*)&Info, sizeof( Info ) );
#ifdef DEBUG_MSG
    log_encrypt_message( 1, "    god_request_map_info( %d, %d )", Index, PieceIndex );
#endif

    return result;
}

/************************************************************************************************************/
/* TEAM ASSOCIATED FUNCTIONS                                                                                */
/************************************************************************************************************/
int		ClientRequestJoinTeam(CHAR *szMainName, CHAR *szZoneName )
{
	TPOS_EVENT_REQUESTJOINTEAM	request;
	SLONG	result;

	strcpy((char *)request.LeaderMainName, (const char *)szMainName);
    strcpy((char *)request.LeaderZoneName, (const char *)szZoneName );
	result = PosSendDataToZone(REQUEST_JOIN_TEAM, (char*)&request, sizeof(request));

#ifdef	DEBUG_MSG
	log_encrypt_message(1, "    request_join_team(%s)", szMainName);
#endif//DEBUG_MSG

	return	result;
}

int		ClientRequestAgreeJoinTeam(CHAR *szMainName, CHAR *szZoneName )
{
	TPOS_EVENT_REQUESTAGREEJOINTEAM	request;
	SLONG	result;

	strcpy((char *)request.MemberMainName, (const char *)szMainName);
    strcpy((char *)request.MemberZoneName, (const char *)szZoneName );
	result = PosSendDataToZone(REQUEST_AGREE_JOIN_TEAM, (char*)&request, sizeof(request));

#ifdef	DEBUG_MSG
	log_encrypt_message(1, "   request_agree_join_team(%s)", szMainName);
#endif//DEBUG_MSG

	return	result;
}

int		ClientRequestExitTeam(CHAR *szMainName )
{
	TPOS_EVENT_REQUESTEXITTEAM	request;
	SLONG	result;

	strcpy((char *)request.LeaderMainName, (const char *)szMainName);
    strcpy((char *)request.LeaderZoneName, "" );
	result = PosSendDataToZone(REQUEST_EXIT_TEAM, (char*)&request, sizeof(request));

#ifdef	DEBUG_MSG
	log_encrypt_message(1, "   request_exit_team(%s)", szMainName);
#endif//DEBUG_MSG

	return	result;
}


int		ClientRequestKickTeamMember(CHAR *szMainName, CHAR *szZoneName )
{
	TPOS_EVENT_REQUESTKICKMEMBER	request;
	SLONG	result;

	strcpy((char *)request.MemberMainName, (const char *)szMainName);
    strcpy((char *)request.MemberZoneName, (const char *)szZoneName );
	result = PosSendDataToZone(REQUEST_KICK_TEAM_MEMBER, (char*)&request, sizeof(request));

#ifdef	DEBUG_MSG
	log_encrypt_message(1, "   request_kick_team_member(%s)", szMainName);
#endif//DEBUG_MSG

	return	result;
}

/************************************************************************/
/* 拆開藏寶圖                                                           */
/************************************************************************/

int     ClientRequestSeparateMap( DWORD dwBagIndex )
{
    TPOS_EVENT_REQUESTSEPARATEMAP request;
    SLONG result;

    request.BagIndex = dwBagIndex;

    result = PosSendDataToZone( REQUEST_SEPARATE_MAP, (char*)&request, sizeof( request ) );

#ifdef DEBUG_MSG
    log_encrypt_message( 1, "    request_separate_map( index: %d )", dwBagIndex );
#endif

    return result;
}

