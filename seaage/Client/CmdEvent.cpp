/*
**	CmdEvent.cpp
**	Cmd events functions.
**
**	Jack, 2002/09/13.
*/
#include "MainFun.h"
#include "NetGE_MainFunc.h"
#include "ClientMain.h"
#include "UIMap.h"
#include "Parse.h"
#include "ErrorMsg.h"
#include "Client_SendMsg.h"



/******************************************************************************************************************/
/* CMD EVENTS FUNCTIONS OF ONLINE                                                                                 */
/******************************************************************************************************************/
void    client_cmd_init_app_state(void)
{
	// Jack, for TEST. [1/28/2003]
    set_next_app_state(APPSTATE_INIT_EULA);
    //set_next_app_state(APPSTATE_INIT_CREATE_CHARACTER);
    change_app_state();
}



int     client_cmd_init_main_game(void)
{
    return  0;
}


void    client_cmd_game_start(void)
{
    //發送給ZONE SERVER消息, 開始遊戲.
    ClientRequestGameStart();
    //改變玩家控制的npc的狀態為IDLE
    SetCharacterDoingKindStep(g_lPlayerIndex, DOING_KIND_IDLE, 0);
}


int     client_cmd_left_hit_map(SLONG x, SLONG y)
{
    int result;
    result = ClientRequestLeftHitMap(x, y);
    return  result;
}


int     client_cmd_right_hit_map(SLONG x, SLONG y)
{
    int result;
    result = ClientRequestRightHitMap (x, y);
    return  result;
}


int     client_cmd_left_hit_npc(SLONG dest_npc)
{
    int result;
	result = ClientRequestLeftHitNpc(dest_npc);
    return  result;
}


int     client_cmd_right_hit_npc(SLONG dest_npc)
{
    int result;
    result = ClientRequestRightHitNpc(dest_npc);
    return  result;
}


int     client_cmd_left_hit_sash_item(SLONG sash_index)
{
    int result;
    result = ClientRequestLeftHitSashItem(sash_index);
    return  result;
}


int     client_cmd_right_hit_sash_item(SLONG sash_index)
{
    int result;
    result = ClientRequestRightHitSashItem(sash_index);
    return  result;
}


int     client_cmd_open_player_bag(void)
{
    int result;
    result = ClientRequestOpenBag();
    return  result;

}


int     client_cmd_close_player_bag(void)
{
    int result;
    result = ClientRequestCloseBag();
    return  result;
}


int     client_cmd_public_talk(char *sendname,char *msg)
{
    SLONG   result, ret;

    ret = 0;

    clear_parse_result();
    result = parse_chat_input((USTR*)msg);
    if(TTN_OK != result)
    {
        ret = ClientRequestSendPublicTalk(-1, g_lPlayerIndex, msg);
        return  ret;
    }

    switch(parse_result.type)
    {
    case PARSE_TYPE_TALK:
		SLONG	shape;
		shape = IsCharacterOnTheSea(g_lPlayerIndex);
		if(shape)
			ret = ClientRequestSendPublicTalk(-1, g_lPlayerIndex, msg);
		else
			ret = ClientRequestSendPublicTalk(parse_result.talk.doing_kind, g_lPlayerIndex, msg);
        return  ret;
        
    case PARSE_TYPE_WEATHER:
		ret = ClientRequestChangeWeather(
			parse_result.weather.type, 
			parse_result.weather.active, 
			parse_result.weather.size, 
			parse_result.weather.wind_size, 
			parse_result.weather.wind_dir);
		return	ret;

    default:
        return  0;
    }

	return	0;
}


int     client_cmd_npc_doing(SLONG npc_no, SLONG doing_kind, SLONG doing_step, SLONG d1, SLONG d2, SLONG d3, SLONG d4, SLONG d5)
{
    return  0;
}



int     client_cmd_change_fight_state(void)
{
    int result;
    result = ClientRequestSwitchAttackState();
    return  result;
}


int     client_cmd_add_base_strength(SLONG data)
{
    int result;
	result = ClientRequestAddBaseStrength(data);
    return  result;
}


int     client_cmd_add_base_instinct(SLONG data)
{
    int result;
	result = ClientRequestAddBaseInstinct(data);
    return  result;
}


int     client_cmd_add_base_wit(SLONG data)
{
    int result;
	result = ClientRequestAddBaseWit(data);
    return  result;
}


int     client_cmd_add_base_luck(SLONG data)
{
    int result;
	result = ClientRequestAddBaseLucky(data);
    return  result;
}


int     client_cmd_sub_base_strength(SLONG data)
{
    int result;
	result = ClientRequestSubBaseStrength(data);
    return  result;
}


int     client_cmd_sub_base_instinct(SLONG data)
{
    int result;
	result = ClientRequestSubBaseInstinct(data);
    return  result;
}


int     client_cmd_sub_base_wit(SLONG data)
{
    int result;
	result = ClientRequestSubBaseWit(data);
    return  result;
}


int     client_cmd_sub_base_luck(SLONG data)
{
    int result;
	result = ClientRequestSubBaseLucky(data);
    return  result;
}


int     client_cmd_left_hit_head_item(void)
{
	int	result;
	result = ClientRequestLeftHitEquipHead();
    return  result;
}


int     client_cmd_right_hit_head_item(void)
{
	int	result;
	result = ClientRequestRightHitEquipHead();
    return  result;
}


int     client_cmd_left_hit_neck_item(void)
{
	int	result;
	result = ClientRequestLeftHitEquipNeck();
    return  result;
}


int     client_cmd_right_hit_neck_item(void)
{
	int	result;
	result = ClientRequestRightHitEquipNeck();
    return  result;
}


int     client_cmd_left_hit_body_item(void)
{
	int		result;
	result = ClientRequestLeftHitEquipBody();
    return  result;
}


int     client_cmd_right_hit_body_item(void)
{
	int	result;
	result = ClientRequestRightHitEquipBody();
    return  result;
}


int     client_cmd_left_hit_hands_item(void)
{
	int	result;
	result = ClientRequestLeftHitEquipWeapon();
    return  result;
}


int     client_cmd_right_hit_hands_item(void)
{
	int	result;
	result = ClientRequestRightHitEquipWeapon();
    return  result;
}


int     client_cmd_left_hit_waist_item(void)
{
	int	result;
	result = ClientRequestLeftHitEquipWaist();
    return  result;
}


int     client_cmd_right_hit_waist_item(void)
{
	int	result;
	result = ClientRequestRightHitEquipWaist();
    return  result;
}


int     client_cmd_left_hit_wrist_item(void)
{
	int	result;
	result = ClientRequestLeftHitEquipWrist();
    return  result;
}


int     client_cmd_right_hit_wrist_item(void)
{
	int	result;
	result = ClientRequestRightHitEquipWrist();
    return  result;
}


int     client_cmd_left_hit_glove_item(void)
{
	int	result;
	result = ClientRequestLeftHitEquipGlove();
    return  result;
}


int     client_cmd_right_hit_glove_item(void)
{
	int	result;
	result = ClientRequestRightHitEquipGlove();
    return  result;
}


int     client_cmd_left_hit_feet_item(void)
{
	int	result;
	result = ClientRequestLeftHitEquipFeet();
    return  result;
}


int     client_cmd_right_hit_feet_item(void)
{
	int	result;
	result = ClientRequestRightHitEquipFeet();
    return  result;
}


int     client_cmd_left_hit_bag_item(SLONG bag_index)
{
	int	result;
	result = ClientRequestLeftHitBagItem(bag_index);
    return  result;
}


int     client_cmd_right_hit_bag_item(SLONG bag_index)
{
	int	result;
	result = ClientRequestRightHitBagItem(bag_index);
    return  result;
}


int		client_cmd_left_hit_othera_item(void)
{
	int	result;
	result = ClientRequestLeftHitEquipOtherA();
    return  result;
}

int		client_cmd_right_hit_othera_item(void)
{
	int	result;
	result = ClientRequestRightHitEquipOtherA();
	return	0;
}

int		client_cmd_left_hit_otherb_item(void)
{
	int	result;
	result = ClientRequestLeftHitEquipOtherB();
	return	0;
}

int		client_cmd_right_hit_otherb_item(void)
{
	int	result;
	result = ClientRequestRightHitEquipOtherB();
	return	0;
}

int		client_cmd_left_hit_otherc_item(void)
{
	int	result;
	result = ClientRequestLeftHitEquipOtherC();
    return  result;
}

int		client_cmd_right_hit_otherc_item(void)
{
	int	result;
	result = ClientRequestRightHitEquipOtherC();
	return	0;
}

// 藏寶圖裝備格
int     client_cmd_left_hit_treasure_item( VOID )
{
    return ClientRequestLeftHitTreasureItem( );
}

// 藏寶圖裝備格
int     client_cmd_right_hit_treasure_item( VOID )
{
    return ClientRequestRightHitTreasureItem( );
}

int     client_cmd_drop_item(SLONG map_x, SLONG map_y)
{
	int	result;
	result = ClientRequestDropItem(map_x, map_y);
    return  result;
}



int     client_cmd_left_hit_map_item(SLONG item_x, SLONG item_y)
{
	int	result;
	result = ClientRequestLeftHitMapItem(item_x, item_y);
    return  result;
}



int     client_cmd_right_hit_map_item(SLONG item_x, SLONG item_y)
{
	int	result;
	result = ClientRequestRightHitMapItem(item_x, item_y);
    return  result;
}



int     client_cmd_set_lhand_quick_magic(SLONG quick_index, SLONG magic_no)
{
	int	result;
	result = ClientRequestSetLeftHandQuickSkill(quick_index, magic_no);
    return  result;
}


int     client_cmd_set_rhand_quick_magic(SLONG quick_index, SLONG magic_no)
{
	int	result;
	result = ClientRequestSetRightHandQuickSkill(quick_index, magic_no);
    return  result;
}



int     client_cmd_quick_set_hand_magic(SLONG quick_index)
{
	int	result;
	result = ClientRequestQuickSetHandSkill(quick_index);
    return  result;
}


int     client_cmd_set_lhand_magic(SLONG magic_no)
{
    int result;
	result = ClientRequestChangeLeftHandMagic(magic_no);
    return  result;
}


int     client_cmd_set_rhand_magic(SLONG magic_no)
{
    int result;
	result = ClientRequestChangeRightHandMagic(magic_no);
    return  result;
}


int     client_cmd_left_end_hit_map(SLONG x, SLONG y)
{
    int result;
	result = ClientRequestLeftEndHitMap(x, y);
    return  result;
}


int     client_cmd_right_end_hit_map(SLONG x, SLONG y)
{
    int result;
	result = ClientRequestRightEndHitMap(x, y);
    return  result;
}


int		client_cmd_request_npc_proc(SLONG npc_no, SLONG proc_no)
{
	int	result;
	result = ClientRequestNpcProc(npc_no, proc_no);
	return	result;
}


int		client_cmd_request_change_dir(SLONG dir)
{
	int	result;
	result = ClientRequestChangeDir(dir);
	return	result;
}

int		client_cmd_left_hit_item_store_item(SLONG store_index, SLONG index)
{
	int	result;
	result = ClientRequestBuyItem(store_index, index);
	return	result;
}


int		client_cmd_request_sell_item(SLONG store_index)
{
	int		result;
	result = ClientRequestSellItem(store_index);
	return	result;
}


// 銀行相關請求  ---------------------------------------------------------

int		client_cmd_hit_bank_item( UHINT bank_index )
{
	return ClientRequestHitBankItem( bank_index );
}


int		client_cmd_request_bank_save_money( SLONG money )
{
	return ClientRequestSaveMoney( money );
}


int		client_cmd_request_bank_load_money( SLONG money )
{
	return ClientRequestLoadMoney( money );
}


// 組隊相關請求  ---------------------------------------------------------
int		client_cmd_request_join_team(char *mainname, char *zone_name )
{
	int		result;
	result = ClientRequestJoinTeam(mainname, zone_name);
	return	result;
}

int		client_cmd_request_agree_join_team(char *mainname, char *zone_name )
{
	int		result;
	result = ClientRequestAgreeJoinTeam(mainname, zone_name);
	return	result;
}

int		client_cmd_request_exit_team(char *mainname )
{
	int		result;
	result = ClientRequestExitTeam(mainname );
	return	result;
}

int		client_cmd_request_kick_team_member(char *mainname, char *zone_name )
{
	int		result;
	result = ClientRequestKickTeamMember(mainname, zone_name);
	return	result;
}
