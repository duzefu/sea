/*
**	PosDecodeScript.cpp 
**	decode macro functions.
**
**	Jack, 2002.12.17
**  Hawke,2003.01.20
**
*/
#include "ZoneServer_Def.h"

#define	MC_DEBUG

/************************************************************************************************************/
// GLOBALS																									*/
/************************************************************************************************************/
MAC_PIPE		mac_pipe;
//
static	TPOS_EVENT_NOTIFYNPCTALK		EventNotifyNpcTalk;//mac_npctalk_msg;
static	TPOS_EVENT_NOTIFYNPCCHOICE		EventNotifyNpcChoice;//mac_npcchoice_msg;
static	TPOS_EVENT_NOTIFYENDDIALOG		EventNotifyEndDialog;//mac_enddialog_msg;

/************************************************************************************************************/
/* DECODE MACRO STATIC FUNCTIONS                                                                            */
/************************************************************************************************************/
static	SLONG	script_cmd_talk_clear(void)
{
	memset(&EventNotifyNpcTalk, 0, sizeof(TPOS_EVENT_NOTIFYNPCTALK));

#ifdef  MC_DEBUG
    sprintf((char *)mac_pipe.debug_rec,"        TALK_CLEAR");
#endif//MC_DEBUG

	return	GAME_CONTINUE;
}
//-------------------------------------------------------------------------------
static	SLONG	script_cmd_talk_say(void)
{
	SLONG	text_index;
	USTR	*text_str_in;
	USTR	text_str_out[128];
	SLONG	npc_no;
	
	npc_no = mac_pipe.active_npc;
	text_index = get_script_number();
	text_str_in = get_script_string();	
	replace_variable_string(text_str_in, text_str_out, npc_no);
	if(text_index >= 0 && text_index < 4)
	{
		strcpy((char *)EventNotifyNpcTalk.Msg[text_index], (const char *)text_str_out);
	}

#ifdef  MC_DEBUG
    sprintf((char *)mac_pipe.debug_rec,"        TALK_SAY %d %s", text_index, text_str_out);
#endif//MC_DEBUG
	
	return	GAME_CONTINUE;
}
//-------------------------------------------------------------------------------
static	SLONG	script_cmd_talk_next(void)
{
	SLONG	next_proc;

	next_proc = get_script_number();
	EventNotifyNpcTalk.NextProc = next_proc;

#ifdef  MC_DEBUG
    sprintf((char *)mac_pipe.debug_rec,"        TALK_NEXT %d", next_proc);
#endif//MC_DEBUG

	return	GAME_CONTINUE;
}
//-------------------------------------------------------------------------------
static	SLONG	script_cmd_talk_show(void)
{
	TPOS_PACKET	send_packet;	
	SLONG		npc_no;
	SLONG		cn_index;
	char		mainname[32];

	npc_no = mac_pipe.active_npc;
	LOCK_CHARACTER(0);
	strcpy(mainname, GetCharacterMainName(npc_no));
	UNLOCK_CHARACTER(0);

	LOCK_CONNECTION(0);
	cn_index = FindConnectionByName(mainname);	
	UNLOCK_CONNECTION(0);

	if(cn_index >= 0)
	{
		//EventNpcTalk.npc_no = (SHINT)mac_pipe.macro_npc;
		
		send_packet.Header.dwType = NOTIFY_NPC_TALK;
		send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYNPCTALK);
		
		EventNotifyNpcTalk.TargetNPCIndex = (SHINT)mac_pipe.script_npc;
		memcpy(send_packet.data.cBuf, &EventNotifyNpcTalk, sizeof(TPOS_EVENT_NOTIFYNPCTALK));

		server_send_packet_to_one(&Pos_Cn[cn_index], &send_packet);
	}

#ifdef  MC_DEBUG
    sprintf((char *)mac_pipe.debug_rec,"        TALK_SHOW");
#endif//MC_DEBUG

	return	GAME_CONTINUE;
}
//-------------------------------------------------------------------------------
static	SLONG	script_cmd_choice_clear(void)
{
	memset(&EventNotifyNpcChoice, 0, sizeof(TPOS_EVENT_NOTIFYNPCCHOICE));

#ifdef  MC_DEBUG
    sprintf((char *)mac_pipe.debug_rec,"        CHOICE_CLEAR");
#endif//MC_DEBUG

	return	GAME_CONTINUE;
}
//-------------------------------------------------------------------------------
static	SLONG	script_cmd_choice_title(void)
{
	USTR	*title_str_in;
	USTR	title_str_out[128];
	SLONG	npc_no;

	npc_no = mac_pipe.active_npc;
	title_str_in = get_script_string();
	replace_variable_string(title_str_in, title_str_out, npc_no);
	strcpy((char *)EventNotifyNpcChoice.Title, (const char *)title_str_out);

#ifdef  MC_DEBUG
    sprintf((char *)mac_pipe.debug_rec,"        CHOICE_TITLE %s", title_str_out);
#endif//MC_DEBUG

	return	GAME_CONTINUE;
}
//-------------------------------------------------------------------------------

static	SLONG	script_cmd_choice_option(void)
{
	SLONG	option_index;
	SLONG	option_proc;
	USTR	*option_str_in;
	USTR	option_str_out[128];
	SLONG	npc_no;

	npc_no = mac_pipe.active_npc;

	option_index = get_script_number();
	option_proc = get_script_number();
	option_str_in = get_script_string();
	replace_variable_string(option_str_in, option_str_out, npc_no);
	if(option_index >= 0 && option_index < 4)
	{
		EventNotifyNpcChoice.NextProc[option_index] = option_proc;
		strcpy((char *)EventNotifyNpcChoice.Option[option_index], (const char *)option_str_out);
	}

#ifdef  MC_DEBUG
    sprintf((char *)mac_pipe.debug_rec,"        CHOICE_OPTION %d %d %s", option_index, option_proc, option_str_out);
#endif//MC_DEBUG

	return	GAME_CONTINUE;
}

//-------------------------------------------------------------------------------
static	SLONG	script_cmd_choice_show(void)
{
	TPOS_PACKET	send_packet;	
	SLONG		npc_no;
	SLONG		cn_index;
	char		mainname[32];

	npc_no = mac_pipe.active_npc;
	LOCK_CHARACTER(0);
	strcpy(mainname, GetCharacterMainName(npc_no));
	UNLOCK_CHARACTER(0);

	LOCK_CONNECTION(0);
	cn_index = FindConnectionByName(mainname);	
	UNLOCK_CONNECTION(0);
	if(cn_index >= 0)
	{		
		send_packet.Header.dwType = NOTIFY_NPC_CHOICE;
		send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYNPCCHOICE);

		EventNotifyNpcChoice.TargetNPCIndex = (SHINT)mac_pipe.script_npc;

		memcpy(send_packet.data.cBuf, &EventNotifyNpcChoice, sizeof(TPOS_EVENT_NOTIFYNPCCHOICE));
		server_send_packet_to_one(&Pos_Cn[cn_index], &send_packet);
	}

#ifdef  MC_DEBUG
    sprintf((char *)mac_pipe.debug_rec,"        CHOICE_SHOW");
#endif//MC_DEBUG

	return	GAME_CONTINUE;
}
//-------------------------------------------------------------------------------
static	SLONG	script_cmd_end_dialog(void)
{
	TPOS_PACKET	send_packet;	
	SLONG		npc_no;
	SLONG		cn_index;
	char		mainname[32];
	SLONG		dialog_with_count;

	npc_no = mac_pipe.active_npc;	
	
	LOCK_CHARACTER(0);
	strcpy(mainname, GetCharacterMainName(npc_no));	
	SetCharacterDialogDestIndex(npc_no, 0);
	dialog_with_count = GetCharacterDialogWithCount(mac_pipe.script_npc);
	dialog_with_count--;
	if(dialog_with_count >= 0)
	{
		SetCharacterDialogWithCount(mac_pipe.script_npc, dialog_with_count);
	}else
	{
		SetCharacterDialogWithCount(mac_pipe.script_npc, 0);
	}
	UNLOCK_CHARACTER(0);
	if(dialog_with_count == 0)
	{
		LOCK_CHARACTER(0);
		SetCharacterOnPauseState(mac_pipe.script_npc, FALSE);
		UNLOCK_CHARACTER(0);
		// 通知玩家該 NPC 取消動作暫停		
		ServerDoSendNotifyNpcNoPauseToAll(mac_pipe.script_npc);
	}
	
	LOCK_CONNECTION(0);
	cn_index = FindConnectionByName(mainname);	
	UNLOCK_CONNECTION(0);
	if(cn_index >= 0)
	{
		EventNotifyEndDialog.TargetNPCIndex = (SHINT)mac_pipe.script_npc;
		
		send_packet.Header.dwType = NOTIFY_END_DIALOG;
		send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYENDDIALOG);

		memcpy(send_packet.data.cBuf, &EventNotifyEndDialog, sizeof(TPOS_EVENT_NOTIFYENDDIALOG));
		server_send_packet_to_one(&Pos_Cn[cn_index], &send_packet);
	}

#ifdef  MC_DEBUG
    sprintf((char *)mac_pipe.debug_rec,"        DIALOG_FINISH");
#endif//MC_DEBUG

	return	GAME_CONTINUE;
}
//-------------------------------------------------------------------------------
static	SLONG	script_cmd_check_item(void)
{
	SLONG	variable_index, item_count, item_base_id;
	int		i, npc_no;
	SLONG	check_type;
	SLONG	check_where;
	TPOS_ITEM	Item;

	variable_index = get_script_number();
	item_base_id = get_script_number();
	check_type = get_script_number();
	check_where = get_script_number();
	// To Add ... 
	// 是否為信物  0 - 非信物 , 1 - 信物
	// 0 - 檢查包包 , 1 - 檢查腰帶 , 2 - 包包和腰帶 , 3 - 船隻貨艙 , 4 - 船隻所有

	item_count = 0;
	npc_no = mac_pipe.active_npc;

	LOCK_CHARACTER(0);
	switch(check_where)
	{	
	case 0:
		for(i = 0;i < MAX_CHARACTER_BAG_ITEMS;i++)
		{
			GetCharacterBagItem(npc_no, i, &Item);
			if(item_base_id == GetItemBaseID(&Item))
			{
				if(check_type == 1)
				{			
					if(IsItemKeepsake(&Item) == TRUE)
					{
						item_count ++;			
					}
				}else
				{
					item_count ++;			
				}				
			}		
		}	
		break;
	case 1:
		for(i = 0;i < MAX_CHARACTER_SASH_ITEMS;i++)
		{
			GetCharacterSashItem(npc_no, i, &Item);
			if(item_base_id == GetItemBaseID(&Item))
			{
				if(check_type == 1)
				{			
					if(IsItemKeepsake(&Item) == TRUE)
					{
						item_count ++;			
					}
				}else
				{
					item_count ++;			
				}			
			}		
		}	
		break;
	case 2:
		for(i = 0;i < MAX_CHARACTER_BAG_ITEMS;i++)
		{
			GetCharacterBagItem(npc_no, i, &Item);
			if(item_base_id == GetItemBaseID(&Item))
			{
				if(check_type == 1)
				{			
					if(IsItemKeepsake(&Item) == TRUE)
					{
						item_count ++;			
					}
				}else
				{
					item_count ++;			
				}		
			}		
		}
		for(i = 0;i < MAX_CHARACTER_SASH_ITEMS;i++)
		{
			GetCharacterSashItem(npc_no, i, &Item);
			if(item_base_id == GetItemBaseID(&Item))
			{
				if(check_type == 1)
				{			
					if(IsItemKeepsake(&Item) == TRUE)
					{
						item_count ++;			
					}
				}else
				{
					item_count ++;			
				}			
			}		
		}
		break;
	case 3:
		break;
	case 4:
		break;
	}	
	UNLOCK_CHARACTER(0);

	set_script_variable(variable_index, item_count);

	return GAME_CONTINUE;		
}
//-------------------------------------------------------------------------------
static	SLONG	script_cmd_get_item()
{
	TPOS_EVENT_NOTIFYSETBAGITEM	EventNotifySetBagItem;
	TPOS_PACKET					send_packet;
	SLONG						variable_index, item_count, item_base_id;
	int							i, npc_no;
	TPOS_ITEM					Item;
	SLONG						cn_index;
	char						mainname[32];

	variable_index = get_script_number();	// 1 - 給成功 , 0 - 給不成功
	item_count = get_script_number();		// 數量		
	item_base_id = get_script_number();		// 物品

	npc_no = mac_pipe.active_npc;

	LOCK_CHARACTER(0);
	strcpy(mainname, GetCharacterMainName(npc_no));
	UNLOCK_CHARACTER(0);

	LOCK_CONNECTION(0);
	cn_index = FindConnectionByName(mainname);	
	UNLOCK_CONNECTION(0);
	
	for(i = 0;i< MAX_CHARACTER_BAG_ITEMS;i++)
	{
		LOCK_CHARACTER(0);
		GetCharacterBagItem(npc_no, i, &Item);
		UNLOCK_CHARACTER(0);
		if(IsItemNone(&Item))
		{
			SetItemBaseID(&Item, (UHINT)item_base_id);
			SetItemHp(&Item, 100);
			SetItemID(&Item, 2);				
			LOCK_CHARACTER(0);
			SetCharacterBagItem(npc_no, i, &Item);
			UNLOCK_CHARACTER(0);

			send_packet.Header.dwType = NOTIFY_SET_BAG_ITEM;
			send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYSETBAGITEM);

			EventNotifySetBagItem.BagIndex = i;
			EventNotifySetBagItem.Item = Item;
			memcpy(send_packet.data.cBuf, &EventNotifySetBagItem, sizeof(TPOS_EVENT_NOTIFYSETBAGITEM));

			server_send_packet_to_one(&Pos_Cn[cn_index], &send_packet);

			set_script_variable(variable_index, 1);
			return GAME_CONTINUE;
		}
	}
	set_script_variable(variable_index, 0);
	return GAME_CONTINUE;
}
//-------------------------------------------------------------------------------
static	SLONG	script_cmd_get_heal()
{
	TPOS_EVENT_SETNPCHP	EventSetNpcHp;
	TPOS_PACKET			send_packet;	
	int					npc_no;
	UHINT				maxhp, hp;
	SLONG				variable_index;

	npc_no = mac_pipe.active_npc;
	variable_index = get_script_number();	// 1 - 成功 , 0 - 非成功

	LOCK_CHARACTER(0);
	hp = GetCharacterHp(npc_no);
	maxhp = GetCharacterMaxHp(npc_no);
	UNLOCK_CHARACTER(0);
	if(hp < maxhp)
	{
		LOCK_CHARACTER(0);
		SetCharacterHp(npc_no, maxhp);
		UNLOCK_CHARACTER(0);

		send_packet.Header.dwType = SET_NPC_HP;
		send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_SETNPCHP);
		
		EventSetNpcHp.iHp = maxhp;
		EventSetNpcHp.Index = npc_no;
		
		memcpy(send_packet.data.cBuf, &EventSetNpcHp, sizeof(TPOS_EVENT_SETNPCHP));
		
		server_send_packet_to_all(&send_packet);
	
		set_script_variable(variable_index, 1);
		return GAME_CONTINUE;
	}
	set_script_variable(variable_index, 0);
	return GAME_CONTINUE;
}
//-------------------------------------------------------------------------------
static	SLONG	script_cmd_check_level()
{		
	int					npc_no;	
	SLONG				check_level;	
	SLONG				level;
	SLONG				variable_index;

	npc_no = mac_pipe.active_npc;
	variable_index = get_script_number();	// 0 - 大於等級 , 1 - 等於 , 2 - 小於
	check_level = get_script_number();		// 檢查的等級	  

	LOCK_CHARACTER(0);
	level = GetCharacterLevel(npc_no);	
	UNLOCK_CHARACTER(0);
	if(level > check_level)
	{
		set_script_variable(variable_index, 0);		
	}
	if(level == check_level)
	{
		set_script_variable(variable_index, 1);		
	}
	if(level < check_level)
	{
		set_script_variable(variable_index, 2);		
	}
	return GAME_CONTINUE;
}
//-------------------------------------------------------------------------------
static	SLONG	script_cmd_check_money()
{		
	int					npc_no;	
	SLONG				check_money;	
	SLONG				money;
	SLONG				variable_index;

	npc_no = mac_pipe.active_npc;
	variable_index = get_script_number();	// 0 - 大於 , 1 - 等於 , 2 - 小於
	check_money = get_script_number();		// 檢查的金錢數

	LOCK_CHARACTER(0);
	money = GetCharacterBodyMoney(npc_no);	
	UNLOCK_CHARACTER(0);
	if(money > check_money)
	{
		set_script_variable(variable_index, 0);		
	}
	if(money == check_money)
	{
		set_script_variable(variable_index, 1);		
	}
	if(money < check_money)
	{
		set_script_variable(variable_index, 2);		
	}
	return GAME_CONTINUE;
}
//-------------------------------------------------------------------------------
static	SLONG	script_cmd_request_change_zone()
{
	int					npc_no;			
	SLONG				variable_index;

	npc_no = mac_pipe.active_npc;
	variable_index = get_script_number();	// 0 - 成功

	LOCK_CHARACTER(0);
	//money = GetCharacterBodyMoney(npc_no);	
	UNLOCK_CHARACTER(0);
	// Hawke  [1/28/2003]
	// 以後要檢查玩家的船,水,食物,水手
	set_script_variable(variable_index, 0);
	
	return GAME_CONTINUE;
}
//-------------------------------------------------------------------------------	
static	SLONG	script_cmd_change_zone()
{
	int							npc_no;			
	int							proc_id;
	int							k;
	char						mainname[32];
	DWORD						dest_zonetype;
	ULONG						qq_id;
	SLONG						cnIndex;
	static TPOS_PACKET			send_packet;
	static TPOS_COMPACKET		send_compacket;
	TPOS_DB_CHARACTER			DbCharacter;
	TPOS_EVENT_QQPLAYERLOGOUT	EventQQPlayerLogout;
	TPOS_EVENT_GETCHANGEMAP		EventGetChangeMap;
	
	npc_no = mac_pipe.active_npc;
	proc_id = get_script_number();	//事件區編號

	LOCK_CHARACTER(npc_no);
	SetCharacterDoingKind(npc_no, DOING_KIND_CHANGEMAP);
	strcpy(mainname, GetCharacterMainName(npc_no));
	qq_id = GetCharacterQQID(npc_no);
	UNLOCK_CHARACTER(npc_no);
	
	LOCK_CONNECTION(cnIndex);
	cnIndex = FindConnectionByName((char *)mainname);
	UNLOCK_CONNECTION(cnIndex);           
	if(cnIndex >= 0)
	{   
		// QQ 離線
		send_packet.Header.dwType = QQ_PLAYER_LOGOUT;
		send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_QQPLAYERLOGOUT);		
		EventQQPlayerLogout.QQID = qq_id;
		memcpy(send_packet.data.cBuf, &EventQQPlayerLogout, sizeof(TPOS_EVENT_QQPLAYERLOGOUT));
		CompressPacket(&send_packet, &send_compacket);
		QueuePacket(World, &send_compacket, CONNECTED_SERVER_WORLD);
		
		// 傳給玩家改變地圖的資訊
		send_packet.Header.dwType = GET_CHANGE_MAP;
		send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER)+sizeof(TPOS_EVENT_GETCHANGEMAP);
		
		strcpy(EventGetChangeMap.cZoneName,
			ZoneMapDefault[MapLink[0].Point[proc_id].ZoneData].cZoneName);		 
		strcpy(EventGetChangeMap.cMapName,
			ZoneMapDefault[MapLink[0].Point[proc_id].ZoneData].cMapName);
		EventGetChangeMap.lX = MapLink[0].Point[proc_id].lDestX;
		EventGetChangeMap.lY = MapLink[0].Point[proc_id].lDestY;
		EventGetChangeMap.lZ = MapLink[0].Point[proc_id].lDestZ;         
		EventGetChangeMap.cDir = MapLink[0].Point[proc_id].cDir[0];						
		
		LOCK_ZONEINFO(0);
		k = FindZoneInfoByName(EventGetChangeMap.cZoneName);					
		strcpy(EventGetChangeMap.cAddr, ZoneInfo[k].cAddr);
		EventGetChangeMap.dwPort = ZoneInfo[k].dwPort;
		EventGetChangeMap.dwType = ZoneInfo[k].dwType;
		dest_zonetype = ZoneInfo[k].dwType;
		UNLOCK_ZONEINFO(0);
		memcpy(send_packet.data.cBuf, &EventGetChangeMap, sizeof(TPOS_EVENT_GETCHANGEMAP));						
		
		CompressPacket(&send_packet, &send_compacket);
		
		LOCK_CONNECTION(cnIndex);				
		QueuePacket(&Pos_Cn[cnIndex] ,&send_compacket, CONNECTED_SERVER_ZONE);
		UNLOCK_CONNECTION(cnIndex);
		
		LOCK_CHARACTER(npc_no);
		ServerDoClearOnMouseItemForPlayerExit(npc_no);
		ConvertZoneCharacterDataToDBCharacter(npc_no, &DbCharacter);
		UNLOCK_CHARACTER(npc_no);
		
		// 設定要儲存玩家的資訊
		strcpy(DbCharacter.MainName, mainname);
		strcpy(DbCharacter.ZoneName,
				ZoneMapDefault[MapLink[0].Point[proc_id].ZoneData].cZoneName);
		DbCharacter.X = MapLink[0].Point[proc_id].lDestX;
		DbCharacter.Y = MapLink[0].Point[proc_id].lDestY;
		DbCharacter.Z = MapLink[0].Point[proc_id].lDestZ;
		DbCharacter.Dir = MapLink[0].Point[proc_id].cDir[0];                        						
		
		switch(dest_zonetype)
		{
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
			SetCharacterOnTheSea(npc_no, FALSE);
			DbCharacter.BitState = GetCharacterBitState(npc_no);							
			break;
		case SAIL_NORMAL:
		case SAIL_NEWBIE:
		case SAIL_PK:
		case SAIL_FINDGOLD:
		case SAIL_BIRTH:
			SetCharacterOnTheSea(npc_no, TRUE);
			DbCharacter.BitState = GetCharacterBitState(npc_no);													
		}
		SaveCharacterInfo(cnIndex, &DbCharacter);												
	}
	else
	{
		// Jack, TODO [20:12,10/20/2002]
	}
	
	return GAME_CONTINUE;
}
//-------------------------------------------------------------------------------	
static	SLONG	script_cmd_init_store()
{
	int					npc_no;			
	SLONG				zone_store_index;
	SLONG				store_base_index;

	npc_no = mac_pipe.active_npc;

	zone_store_index = get_script_number();	// 區域商店編號
	store_base_index = get_script_number();	// 商店種類

	SetupZoneStore(zone_store_index, store_base_index);
	return GAME_CONTINUE;
}
//-------------------------------------------------------------------------------	
static	SLONG	script_cmd_npc_store()
{
	int							npc_no;			
	int							src_npc_no;			
	SLONG						zone_store_index;
	SLONG						next_proc;
	TPOS_EVENT_NOTIFYSTOREDATA	EventNotifyStoreData;
	TPOS_PACKET					send_packet;	
	int							i;
	TPOS_STORE_ITEM				item;
	
	npc_no = mac_pipe.active_npc;
	src_npc_no = mac_pipe.script_npc;
	zone_store_index = get_script_number();	// 區域商店編號
	next_proc = get_script_number();		// 下一個腳本編號
	SetZoneStorePriceQuotiety(zone_store_index, 100);
	memset(&EventNotifyStoreData, 0x0, sizeof(TPOS_EVENT_NOTIFYSTOREDATA));

	for(i = 0;i < MAX_STORE_ITEMS;i++)
	{
		memset(&item, 0x0, sizeof(TPOS_STORE_ITEM));
		GetZoneStoreItem(zone_store_index, i, &item);		
		EventNotifyStoreData.Item[i] = item.Item;
		EventNotifyStoreData.Amount[i] = item.Count;
		EventNotifyStoreData.Money[i] = item.Price;
	}	
	EventNotifyStoreData.NextProc = next_proc;
	EventNotifyStoreData.NpcNo = src_npc_no;
	EventNotifyStoreData.ZoneStoreIndex = zone_store_index;
	
	send_packet.Header.dwType = NOTIFY_STORE_DATA;
	send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYSTOREDATA);
	memcpy(send_packet.data.cBuf, &EventNotifyStoreData, sizeof(TPOS_EVENT_NOTIFYSTOREDATA));
	
	server_send_packet_to_player(npc_no, &send_packet);
	return GAME_CONTINUE;
}
//-------------------------------------------------------------------------------	
static	SLONG	script_cmd_get_skill()
{
	int							npc_no;		
	TPOS_PACKET					send_packet;	
	int							i;
	SLONG						get_skill, skill;
	SLONG						active;
	TPOS_EVENT_SETNPCSKILL		EventSetNpcSkill;
	SLONG						variable_index;
	SLONG						checkskill;
	
	active = FALSE;
	checkskill = FALSE;

	npc_no = mac_pipe.active_npc;	
	variable_index = get_script_number();	// 0 - 成功給了技能 , 1 - 他已有該技能 , 2 - 他沒有技能空格
	get_skill = get_script_number();		// 技能編號	
	LOCK_CHARACTER(0);
	// 檢查是否已有該技能
	for(i = 0;i < MAX_CHARACTER_SKILLS;i++)
	{
		skill = GetCharacterSkillNo(npc_no, i);
		if(get_skill == skill)
		{
			active = FALSE;
			break;
		}
		active = TRUE;
	}		
	UNLOCK_CHARACTER(0);
	// 檢查是否有空的技能格的處理
	if(active == TRUE)
	{
		for(i = 0;i < MAX_CHARACTER_SKILLS;i++)
		{
			LOCK_CHARACTER(0);
			skill = GetCharacterSkillNo(npc_no, i);
			UNLOCK_CHARACTER(0);
			if(skill == -1)
			{
				checkskill = TRUE;
				LOCK_CHARACTER(0);
				SetCharacterSkillNo(npc_no, i, get_skill);
				UNLOCK_CHARACTER(0);
				set_script_variable(variable_index, 0);	// 技能設置OK
				
				// 送出改變的技能
				send_packet.Header.dwType = SET_NPC_SKILL;
				send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_SETNPCSKILL);
				EventSetNpcSkill.NpcNo = npc_no;
				EventSetNpcSkill.SkillIndex = i;
				EventSetNpcSkill.SkillNo = get_skill;
				memcpy(send_packet.data.cBuf, &EventSetNpcSkill, sizeof(TPOS_EVENT_SETNPCSKILL));
				server_send_packet_to_player(npc_no, &send_packet);
				break;
			}						
		}
	}else
	{		
		set_script_variable(variable_index, 1);	// 已經有該技能
	}
	if(checkskill == FALSE)set_script_variable(variable_index, 2);	// 沒有空的技能格

	return GAME_CONTINUE;
}
//-------------------------------------------------------------------------------	
static	SLONG	script_cmd_check_career()
{
	int							npc_no;			
	SLONG						get_career, career;	
	SLONG						variable_index;		
	SLONG						check;
	
	check = FALSE;
	npc_no = mac_pipe.active_npc;	
	variable_index = get_script_number();		
	get_career = get_script_number();		
	LOCK_CHARACTER(0);
	career = GetCharacterCareer(npc_no);
	UNLOCK_CHARACTER(0);
	switch(get_career)
	{
		//提督
	case 1:
		if(career == 'A') check = TRUE;		
		break;
		//劍士
	case 2:
		if(career == 'B') check = TRUE;		
		break;
		//小偷
	case 3:
		if(career == 'C') check = TRUE;		
		break;
		//商人
	case 4:
		if(career == 'D') check = TRUE;		
		break;
		//探險家 
	case 5:
		if(career == 'E') check = TRUE;		
		break;
		//牧師
	case 6:
		if(career == 'F') check = TRUE;		
		break;
		//占星術士
	case 7:
		if(career == 'G') check = TRUE;		
		break;	
	}
	if(check == TRUE)
	{		
		set_script_variable(variable_index, 0);	// 與條件職業相同
	}else
	{
		set_script_variable(variable_index, 1);	// 與條件職業不相同
	}
	
	return GAME_CONTINUE;
}
//-------------------------------------------------------------------------------	
static	SLONG	script_cmd_check_sex()
{
	int							npc_no;			
	SLONG						get_sex, sex;	
	SLONG						variable_index;		
	
	npc_no = mac_pipe.active_npc;	
	variable_index = get_script_number();		
	get_sex = get_script_number();			// 1 - 男 , 2 - 女
	LOCK_CHARACTER(0);
	sex = GetCharacterSex(npc_no);
	UNLOCK_CHARACTER(0);
	switch(get_sex)
	{
	case 1:
		if(sex == 'A')
		{
			set_script_variable(variable_index, 0);	// 與條件性別相同
		}else
		{
			set_script_variable(variable_index, 1);	// 與條件性別不相同
		}
		
		break;
	case 2:
		if(sex == 'B')
		{
			set_script_variable(variable_index, 0);	// 與條件性別相同
		}else
		{
			set_script_variable(variable_index, 1);	// 與條件性別不相同
		}
		
		break;
	}	
	
	return GAME_CONTINUE;	
}
//-------------------------------------------------------------------------------	
static	SLONG	script_cmd_check_hp()
{
	int							npc_no;			
	SLONG						get_hp, hp;	
	SLONG						variable_index;		
	
	npc_no = mac_pipe.active_npc;	
	variable_index = get_script_number();		
	get_hp = get_script_number();		
	LOCK_CHARACTER(0);
	hp = GetCharacterHp(npc_no);
	UNLOCK_CHARACTER(0);
	if(get_hp <= hp)
	{
		set_script_variable(variable_index, 0);	// 達到條件生命值
	}else
	{
		set_script_variable(variable_index, 1);	// 未達到條件生命值
	}

	return GAME_CONTINUE;
}
//-------------------------------------------------------------------------------	
static	SLONG	script_cmd_check_mp()
{
	int							npc_no;			
	SLONG						get_mp, mp;	
	SLONG						variable_index;		
	
	npc_no = mac_pipe.active_npc;	
	variable_index = get_script_number();		
	get_mp = get_script_number();		
	LOCK_CHARACTER(0);
	mp = GetCharacterMp(npc_no);
	UNLOCK_CHARACTER(0);
	if(get_mp < mp)
	{
		set_script_variable(variable_index, 0);	// 達到條件魔法值
	}else
	{
		set_script_variable(variable_index, 1);	// 未達到條件魔法值
	}

	return GAME_CONTINUE;
}
//-------------------------------------------------------------------------------	
static	SLONG	script_cmd_check_country()
{
	int							npc_no;			
	SLONG						country;	
	SLONG						variable_index;		
	
	npc_no = mac_pipe.active_npc;		
	variable_index = get_script_number();		
	LOCK_CHARACTER(0);
	country = GetCharacterCountry(npc_no);
	UNLOCK_CHARACTER(0);
	switch(country)
	{
	case 'A':
		set_script_variable(variable_index, 1);
		break;
	case 'B':
		set_script_variable(variable_index, 2);
		break;
	case 'C':
		set_script_variable(variable_index, 3);
		break;
	case 'D':
		set_script_variable(variable_index, 4);
		break;
	case 'E':
		set_script_variable(variable_index, 5);
		break;
	case 'F':
		set_script_variable(variable_index, 6);
		break;
	case 'G':
		set_script_variable(variable_index, 7);
		break;
	case 'H':
		set_script_variable(variable_index, 8);
		break;
	case 'I':
		set_script_variable(variable_index, 9);
		break;
	case 'J':
		set_script_variable(variable_index, 10);
		break;
	case 'K':
		set_script_variable(variable_index, 11);
		break;
	case 'L':
		set_script_variable(variable_index, 12);
		break;
	case 'M':
		set_script_variable(variable_index, 13);
		break;
	case 'N':
		set_script_variable(variable_index, 14);
		break;
	case 'O':
		set_script_variable(variable_index, 15);
		break;
	case 'P':
		set_script_variable(variable_index, 16);
		break;
	case 'Q':
		set_script_variable(variable_index, 17);
		break;
	case 'R':
		set_script_variable(variable_index, 18);
		break;
	case 'S':
		set_script_variable(variable_index, 19);
		break;
	case 'T':
		set_script_variable(variable_index, 20);
		break;
	default:
		set_script_variable(variable_index, 0);
		break;
	}	
	return GAME_CONTINUE;
}
//-------------------------------------------------------------------------------	
static	SLONG	script_cmd_check_pkcount()
{
	return GAME_CONTINUE;
}
//-------------------------------------------------------------------------------	
static	SLONG	script_cmd_check_pkedcount()
{
	return GAME_CONTINUE;
}
//-------------------------------------------------------------------------------	
static	SLONG	script_cmd_check_goodevil()
{
	int							npc_no;			
	SLONG						get_goodevil, goodevil;	
	SLONG						variable_index;		
	
	npc_no = mac_pipe.active_npc;	
	variable_index = get_script_number();		
	get_goodevil = get_script_number();
	LOCK_CHARACTER(0);
	goodevil = GetCharacterGoodEvil(npc_no); 
	UNLOCK_CHARACTER(0);
	if(get_goodevil > goodevil)
	{
		set_script_variable(variable_index, 0);	// 大於條件善惡值		
	}
	if(get_goodevil == goodevil)
	{
		set_script_variable(variable_index, 1);	// 等於條件善惡值		
	}
	if(get_goodevil < goodevil)
	{
		set_script_variable(variable_index, 2);	// 小於條件善惡值		
	}		
	
	return GAME_CONTINUE;
}
//-------------------------------------------------------------------------------	
static	SLONG	script_cmd_check_bag_space()
{
	int							npc_no;				
	SLONG						variable_index;	
	int							i, count;
	TPOS_ITEM					Item;

	count = 0;
	npc_no = mac_pipe.active_npc;
	variable_index = get_script_number();
	for(i = 0;i< MAX_CHARACTER_BAG_ITEMS;i++)
	{
		LOCK_CHARACTER(0);
		GetCharacterBagItem(npc_no, i, &Item);
		UNLOCK_CHARACTER(0);
		if(IsItemNone(&Item))
		{
			count++;
		}
	}
	set_script_variable(variable_index, count);	// 返回空格數
	
	return GAME_CONTINUE;
}
//-------------------------------------------------------------------------------	
static	SLONG	script_cmd_check_str()
{
	int							npc_no;			
	SLONG						get_str, init_str, levup_str;	
	SLONG						variable_index;	

	npc_no = mac_pipe.active_npc;	
	variable_index = get_script_number();		
	get_str = get_script_number();		
	LOCK_CHARACTER(0);
	init_str = (SLONG)GetCharacterInitStr(npc_no);
	levup_str = (SLONG)GetCharacterLevelUpStr(npc_no);
	UNLOCK_CHARACTER(0);

	if((init_str + levup_str) >= get_str)
	{
		set_script_variable(variable_index, 0);	// 達到條件力量
	}else
	{
		set_script_variable(variable_index, 1);	// 未達到條件力量
	}
	return GAME_CONTINUE;
}
//-------------------------------------------------------------------------------	
static	SLONG	script_cmd_check_ins()
{
	int							npc_no;			
	SLONG						get_ins, init_ins, levup_ins;	
	SLONG						variable_index;	

	npc_no = mac_pipe.active_npc;	
	variable_index = get_script_number();		
	get_ins = get_script_number();		
	LOCK_CHARACTER(0);
	init_ins = (SLONG)GetCharacterInitIns(npc_no);
	levup_ins = (SLONG)GetCharacterLevelUpIns(npc_no);
	UNLOCK_CHARACTER(0);

	if((init_ins + levup_ins) >= get_ins)
	{
		set_script_variable(variable_index, 0);	// 達到條件智力
	}else
	{
		set_script_variable(variable_index, 1);	// 未達到條件智力
	}

	return GAME_CONTINUE;
}
//-------------------------------------------------------------------------------	
static	SLONG	script_cmd_check_wit()
{
	int							npc_no;			
	SLONG						get_wit, init_wit, levup_wit;	
	SLONG						variable_index;	

	npc_no = mac_pipe.active_npc;	
	variable_index = get_script_number();		
	get_wit = get_script_number();		
	LOCK_CHARACTER(0);
	init_wit = (SLONG)GetCharacterInitWit(npc_no);
	levup_wit = (SLONG)GetCharacterLevelUpWit(npc_no);
	UNLOCK_CHARACTER(0);

	if((init_wit + levup_wit) >= get_wit)
	{
		set_script_variable(variable_index, 0);	// 達到條件直覺
	}else
	{
		set_script_variable(variable_index, 1);	// 未達到條件直覺
	}

	return GAME_CONTINUE;
}
//-------------------------------------------------------------------------------	
static	SLONG	script_cmd_check_lucky()
{
	int							npc_no;			
	SLONG						get_lucky, init_lucky, levup_lucky;	
	SLONG						variable_index;	

	npc_no = mac_pipe.active_npc;	
	variable_index = get_script_number();		
	get_lucky = get_script_number();		
	LOCK_CHARACTER(0);
	init_lucky = (SLONG)GetCharacterInitLucky(npc_no);
	levup_lucky = (SLONG)GetCharacterLevelUpLucky(npc_no);
	UNLOCK_CHARACTER(0);

	if((init_lucky + levup_lucky) >= get_lucky)
	{
		set_script_variable(variable_index, 0);	// 達到條件運氣
	}else
	{
		set_script_variable(variable_index, 1);	// 未達到條件運氣
	}

	return GAME_CONTINUE;
}
//-------------------------------------------------------------------------------	
static	SLONG	script_cmd_check_quest_time()
{
	
	return GAME_CONTINUE;
}
//-------------------------------------------------------------------------------	
static	SLONG	script_cmd_get_str()
{
	int									npc_no;			
	SLONG								get_str;	
	TPOS_PACKET							send_packet;	
	TPOS_EVENT_SETNPCUPGRADEBASEDATA	EventSetNpcUpgradeBaseData;
	POINTSTR_UPDATE_RESULT				StrResult;
	SLONG								update_ok;	
	char								mainname[32];
	SLONG								cn_index;

	update_ok = FALSE;

	npc_no = mac_pipe.active_npc;	
	get_str = get_script_number();		
	LOCK_CHARACTER(0);	
	strcpy(mainname,GetCharacterMainName(npc_no));
	if(ComputeCharacterPropertyPointToPointStr(npc_no, get_str, &StrResult) == TRUE)
	{
		update_ok = TRUE;
	}
	UNLOCK_CHARACTER(0);		
	if(update_ok == TRUE)
	{
		EventSetNpcUpgradeBaseData.rest_point = StrResult.property_point;
		EventSetNpcUpgradeBaseData.update_type = UPDATE_NPC_BASE_STRENGTH;
		EventSetNpcUpgradeBaseData.value = StrResult.str;
		EventSetNpcUpgradeBaseData.att = StrResult.att;
		EventSetNpcUpgradeBaseData.defence = StrResult.defence;
		EventSetNpcUpgradeBaseData.max_hp = StrResult.max_hp;
		EventSetNpcUpgradeBaseData.hp = StrResult.hp;
		EventSetNpcUpgradeBaseData.max_mp = StrResult.max_mp;
		EventSetNpcUpgradeBaseData.mp = StrResult.mp;

		LOCK_CONNECTION(0);
		cn_index = FindConnectionByName(mainname);
		UNLOCK_CONNECTION(0);

		send_packet.Header.dwType = SET_NPC_UPGRADE_BASE_DATA;
		send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_SETNPCUPGRADEBASEDATA);

		memcpy(send_packet.data.cBuf, &EventSetNpcUpgradeBaseData, sizeof(TPOS_EVENT_SETNPCUPGRADEBASEDATA));
        server_send_packet_to_one(&Pos_Cn[cn_index], &send_packet);
	}	

	return GAME_CONTINUE;
}		
//-------------------------------------------------------------------------------	
static	SLONG	script_cmd_get_ins()
{
	int									npc_no;			
	SLONG								get_ins;	
	TPOS_PACKET							send_packet;	
	TPOS_EVENT_SETNPCUPGRADEBASEDATA	EventSetNpcUpgradeBaseData;
	POINTINS_UPDATE_RESULT				InsResult;
	SLONG								update_ok;	
	char								mainname[32];
	SLONG								cn_index;

	update_ok = FALSE;

	npc_no = mac_pipe.active_npc;	
	get_ins = get_script_number();		
	LOCK_CHARACTER(0);	
	strcpy(mainname,GetCharacterMainName(npc_no));
	if(ComputeCharacterPropertyPointToPointIns(npc_no, get_ins, &InsResult) == TRUE)
	{
		update_ok = TRUE;
	}
	UNLOCK_CHARACTER(0);		
	if(update_ok == TRUE)
	{
		EventSetNpcUpgradeBaseData.rest_point = InsResult.property_point;
		EventSetNpcUpgradeBaseData.update_type = UPDATE_NPC_BASE_INSTINCT;
		EventSetNpcUpgradeBaseData.value = InsResult.ins;
		EventSetNpcUpgradeBaseData.att = InsResult.att;
		EventSetNpcUpgradeBaseData.defence = InsResult.defence;
		EventSetNpcUpgradeBaseData.max_hp = InsResult.max_hp;
		EventSetNpcUpgradeBaseData.hp = InsResult.hp;
		EventSetNpcUpgradeBaseData.max_mp = InsResult.max_mp;
		EventSetNpcUpgradeBaseData.mp = InsResult.mp;

		LOCK_CONNECTION(0);
		cn_index = FindConnectionByName(mainname);
		UNLOCK_CONNECTION(0);

		send_packet.Header.dwType = SET_NPC_UPGRADE_BASE_DATA;
		send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_SETNPCUPGRADEBASEDATA);

		memcpy(send_packet.data.cBuf, &EventSetNpcUpgradeBaseData, sizeof(TPOS_EVENT_SETNPCUPGRADEBASEDATA));
        server_send_packet_to_one(&Pos_Cn[cn_index], &send_packet);
	}	

	return GAME_CONTINUE;
}
//-------------------------------------------------------------------------------	
static	SLONG	script_cmd_get_wit()
{
	int									npc_no;			
	SLONG								get_wit;	
	TPOS_PACKET							send_packet;	
	TPOS_EVENT_SETNPCUPGRADEBASEDATA	EventSetNpcUpgradeBaseData;
	POINTWIT_UPDATE_RESULT				WitResult;
	SLONG								update_ok;	
	char								mainname[32];
	SLONG								cn_index;

	update_ok = FALSE;

	npc_no = mac_pipe.active_npc;	
	get_wit = get_script_number();		
	LOCK_CHARACTER(0);	
	strcpy(mainname,GetCharacterMainName(npc_no));
	if(ComputeCharacterPropertyPointToPointWit(npc_no, get_wit, &WitResult) == TRUE)
	{
		update_ok = TRUE;
	}
	UNLOCK_CHARACTER(0);		
	if(update_ok == TRUE)
	{
		EventSetNpcUpgradeBaseData.rest_point = WitResult.property_point;
		EventSetNpcUpgradeBaseData.update_type = UPDATE_NPC_BASE_WIT;
		EventSetNpcUpgradeBaseData.value = WitResult.wit;
		EventSetNpcUpgradeBaseData.att = WitResult.att;
		EventSetNpcUpgradeBaseData.defence = WitResult.defence;
		EventSetNpcUpgradeBaseData.max_hp = WitResult.max_hp;
		EventSetNpcUpgradeBaseData.hp = WitResult.hp;
		EventSetNpcUpgradeBaseData.max_mp = WitResult.max_mp;
		EventSetNpcUpgradeBaseData.mp = WitResult.mp;

		LOCK_CONNECTION(0);
		cn_index = FindConnectionByName(mainname);
		UNLOCK_CONNECTION(0);

		send_packet.Header.dwType = SET_NPC_UPGRADE_BASE_DATA;
		send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_SETNPCUPGRADEBASEDATA);

		memcpy(send_packet.data.cBuf, &EventSetNpcUpgradeBaseData, sizeof(TPOS_EVENT_SETNPCUPGRADEBASEDATA));
        server_send_packet_to_one(&Pos_Cn[cn_index], &send_packet);
	}	

	return GAME_CONTINUE;
}
//-------------------------------------------------------------------------------	
static	SLONG	script_cmd_get_lucky()
{
	int									npc_no;			
	SLONG								get_lucky;	
	TPOS_PACKET							send_packet;	
	TPOS_EVENT_SETNPCUPGRADEBASEDATA	EventSetNpcUpgradeBaseData;
	POINTLUCKY_UPDATE_RESULT			LuckyResult;
	SLONG								update_ok;	
	char								mainname[32];
	SLONG								cn_index;

	update_ok = FALSE;

	npc_no = mac_pipe.active_npc;	
	get_lucky = get_script_number();		
	LOCK_CHARACTER(0);	
	strcpy(mainname,GetCharacterMainName(npc_no));
	if(ComputeCharacterPropertyPointToPointLucky(npc_no, get_lucky, &LuckyResult) == TRUE)
	{
		update_ok = TRUE;
	}
	UNLOCK_CHARACTER(0);		
	if(update_ok == TRUE)
	{
		EventSetNpcUpgradeBaseData.rest_point = LuckyResult.property_point;
		EventSetNpcUpgradeBaseData.update_type = UPDATE_NPC_BASE_LUCK;
		EventSetNpcUpgradeBaseData.value = LuckyResult.lucky;
		EventSetNpcUpgradeBaseData.att = LuckyResult.att;
		EventSetNpcUpgradeBaseData.defence = LuckyResult.defence;
		EventSetNpcUpgradeBaseData.max_hp = LuckyResult.max_hp;
		EventSetNpcUpgradeBaseData.hp = LuckyResult.hp;
		EventSetNpcUpgradeBaseData.max_mp = LuckyResult.max_mp;
		EventSetNpcUpgradeBaseData.mp = LuckyResult.mp;

		LOCK_CONNECTION(0);
		cn_index = FindConnectionByName(mainname);
		UNLOCK_CONNECTION(0);

		send_packet.Header.dwType = SET_NPC_UPGRADE_BASE_DATA;
		send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_SETNPCUPGRADEBASEDATA);

		memcpy(send_packet.data.cBuf, &EventSetNpcUpgradeBaseData, sizeof(TPOS_EVENT_SETNPCUPGRADEBASEDATA));
        server_send_packet_to_one(&Pos_Cn[cn_index], &send_packet);
	}	

	return GAME_CONTINUE;
}	
//-------------------------------------------------------------------------------	
static	SLONG	script_cmd_get_ship()
{
	return GAME_CONTINUE;
}	
//-------------------------------------------------------------------------------	
static	SLONG	script_cmd_change_position()
{
	int							npc_no;				
	SLONG						x,y,z;
	TPOS_PACKET					send_packet;
	TPOS_EVENT_SETNPCPOSITION	EventSetNpcPosition;
	char						mainname[32];
	SLONG						cn_index;
	
	npc_no = mac_pipe.active_npc;	
	x = get_script_number();
	y = get_script_number();
	z = get_script_number();

	LOCK_CHARACTER(0);
	strcpy(mainname,GetCharacterMainName(npc_no));
	UNLOCK_CHARACTER(0);
	LOCK_CONNECTION(0);
	cn_index = FindConnectionByName(mainname);
	UNLOCK_CONNECTION(0);	
	
	EventSetNpcPosition.x = x;
	EventSetNpcPosition.y = y;
	EventSetNpcPosition.z = z;

	send_packet.Header.dwType = SET_NPC_POSITION;
	send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_SETNPCPOSITION);

	memcpy(send_packet.data.cBuf, &EventSetNpcPosition, sizeof(TPOS_EVENT_SETNPCPOSITION));

	LOCK_CHARACTER(0);
	SetCharacterPosition(npc_no, x, y, z);
	UNLOCK_CHARACTER(0);

	server_send_packet_to_one(&Pos_Cn[cn_index], &send_packet);

	return GAME_CONTINUE;
}
//-------------------------------------------------------------------------------	
static	SLONG	script_cmd_change_item()
{
	return GAME_CONTINUE;
}	
//-------------------------------------------------------------------------------	
static	SLONG	script_cmd_post_systemmsg()
{
	return GAME_CONTINUE;
}
//-------------------------------------------------------------------------------	
static	SLONG	script_cmd_deposit_money()
{
	return GAME_CONTINUE;
}
//-------------------------------------------------------------------------------	
static	SLONG	script_cmd_draw_money()
{
	return GAME_CONTINUE;
}
//-------------------------------------------------------------------------------	
static	SLONG	script_cmd_init_quest_npc()
{	
	SLONG	quest_npc_no;	

	quest_npc_no = get_script_number();		

	LOCK_QUESTLIST(0);
	NpcQuestList.NpcNo = quest_npc_no;
	UNLOCK_QUESTLIST(0);

	return GAME_CONTINUE;
}
//-------------------------------------------------------------------------------	
static	SLONG	script_cmd_get_quest_list()
{
	int		i, j, npc_no;
	TPOS_EVENT_NOTIFYNPCQUESTLIST	EventNotifyNpcQuestList;
	TPOS_PACKET						send_packet;
	char							mainname[32];
	SLONG							cn_index;

	npc_no = mac_pipe.active_npc;
	memset(&EventNotifyNpcQuestList, 0x0, sizeof(TPOS_EVENT_NOTIFYNPCQUESTLIST));

	LOCK_CHARACTER(0);
	strcpy(mainname,GetCharacterMainName(npc_no));
	UNLOCK_CHARACTER(0);
	LOCK_CONNECTION(0);
	cn_index = FindConnectionByName(mainname);
	UNLOCK_CONNECTION(0);	

	j = 0;
	LOCK_QUESTLIST(0);
	for(i = 0; i < 20; i++)
	{
		if(NpcQuestList.Quest[i].IsAccepted == QUEST_FREE)
		{
			strcpy(EventNotifyNpcQuestList.QuestList[j].TargetNpc, 
				   NpcQuestList.Quest[i].TargetNpc);
			strcpy(EventNotifyNpcQuestList.QuestList[j].Memo,
				   NpcQuestList.Quest[i].Memo);	
			EventNotifyNpcQuestList.QuestList[j].PayType = NpcQuestList.Quest[i].PayType;
			EventNotifyNpcQuestList.QuestList[j].PayData = NpcQuestList.Quest[i].PayData;
			EventNotifyNpcQuestList.QuestList[j].PunishType = NpcQuestList.Quest[i].PunishType;
			EventNotifyNpcQuestList.QuestList[j].PunishData = NpcQuestList.Quest[i].PunishData;
			EventNotifyNpcQuestList.QuestList[j].Deadline = NpcQuestList.Quest[i].Deadline;
			EventNotifyNpcQuestList.QuestList[j].RequestCareer = NpcQuestList.Quest[i].RequestCareer;
			EventNotifyNpcQuestList.QuestList[j].RequestCareerLevel = NpcQuestList.Quest[i].RequestCareerLevel;
			EventNotifyNpcQuestList.QuestList[j].RequestLevel = NpcQuestList.Quest[i].RequestLevel;
			EventNotifyNpcQuestList.QuestList[j].RequestPrestige = NpcQuestList.Quest[i].RequestPrestige;
			j++;
		}
	}
	UNLOCK_QUESTLIST(0);
	
	send_packet.Header.dwType = NOTIFY_NPC_QUEST_LIST;
	send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYNPCQUESTLIST);
	memcpy(send_packet.data.cBuf, &EventNotifyNpcQuestList, sizeof(TPOS_EVENT_NOTIFYNPCQUESTLIST));

	server_send_packet_to_one(&Pos_Cn[cn_index], &send_packet);

	return GAME_CONTINUE;
}
//-------------------------------------------------------------------------------	
static	SLONG	script_cmd_repair_item()
{
	int		npc_no;
	SLONG	next_proc;

	//npc_no = mac_pipe.active_npc;		
	//src_npc_no = mac_pipe.script_npc;	

	return GAME_CONTINUE;
}
//-------------------------------------------------------------------------------	
static	SLONG	script_cmd_full_food()
{
	return GAME_CONTINUE;
}
//-------------------------------------------------------------------------------			
static	SLONG	script_cmd_full_sailer()
{
	return GAME_CONTINUE;
}
//-------------------------------------------------------------------------------			
static	SLONG	script_cmd_npc_bank()
{
	int								npc_no;		
	int								src_npc_no;	
	TPOS_PACKET						send_packet;
	TPOS_EVENT_NOTIFYBANKMONEYITEM	EventNotifyBankMoneyItem;
	TPOS_ITEM						item;
	int								i;
	char							mainname[32];
	SLONG							cn_index;
	SLONG							next_proc;

	npc_no = mac_pipe.active_npc;		
	src_npc_no = mac_pipe.script_npc;
	next_proc = get_script_number();		// 下一個腳本編號

	LOCK_CHARACTER(0);
	strcpy(mainname,GetCharacterMainName(npc_no));
	for(i = 0;i < MAX_CHARACTER_BANK_ITEMS;i++)
	{
		GetCharacterBankItem(npc_no, i, &item);
		EventNotifyBankMoneyItem.Item[i] = item;
	}	
	EventNotifyBankMoneyItem.Money = GetCharacterBankMoney(npc_no);
	UNLOCK_CHARACTER(0);	
	LOCK_CONNECTION(0);
	cn_index = FindConnectionByName(mainname);
	UNLOCK_CONNECTION(0);	

	EventNotifyBankMoneyItem.NpcNo = src_npc_no;
	EventNotifyBankMoneyItem.NextProc = next_proc;
	send_packet.Header.dwType = NOTIFY_BANK_MONEY_ITEM;
	send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYBANKMONEYITEM);
	memcpy(send_packet.data.cBuf, &EventNotifyBankMoneyItem, sizeof(TPOS_EVENT_NOTIFYBANKMONEYITEM));

	server_send_packet_to_one(&Pos_Cn[cn_index], &send_packet);

	return GAME_CONTINUE;
}
/************************************************************************************************************/
/* DECODE MACRO MAIN FUNCTIONS                                                                              */
/************************************************************************************************************/
void    replace_variable_string(USTR *in, USTR *out, SLONG player_index)
{
    SLONG   in_index, out_index, len;
    SLONG   i;
	SLONG	temp_len;
    USTR    temp[64];

    in_index = 0;
    out_index = 0;
    len = (SLONG)strlen((const char *)in);
    while(in_index < len)
    {
        if( (in[in_index] == '$') && (in_index+3 < len) )
        {
            if(in[in_index+3] == '$')
            {
                //$PN$ 玩家的名字(PlayerName)
				
                if(in[in_index+1] == 'P' && in[in_index+2] == 'N')  
                {
                    memset((char *)temp, '\0', 64);

                    LOCK_CHARACTER(player_index);
                    strcpy((char *)temp, GetCharacterMainName(player_index));
                    UNLOCK_CHARACTER(player_index);

                    temp_len = (SLONG)strlen((const char *)temp);
                    for(i=0; i<temp_len; i++)
                    {
                        out[out_index++] = temp[i];
                    }
                }
                else
                {
                    for(i=0; i<4; i++)
                    {
                        out[out_index++] = in[in_index+i];
                    }
                }
                in_index += 4;
            }
            else
            {
                out[out_index] = in[in_index];
                out_index ++;
                in_index ++;
            }
        }
        else
        {
            out[out_index] = in[in_index];
            out_index ++;
            in_index ++;
        }
    }
    out[out_index] = '\0';
}


void    reset_mac_pipe(void)
{
	memset(&mac_pipe, 0x0, sizeof(MAC_PIPE));
}


void	set_mac_pipe_with_npc_proc(SLONG active_npc, SLONG script_npc)
{
	mac_pipe.proc_type = NPC_MACRO_PROC;
	mac_pipe.active_npc = active_npc;
	mac_pipe.script_npc = script_npc;
}



SLONG   pos_decode_script(UCHR code)
{
	SLONG	ret;

	ret = GAME_CONTINUE;
	switch(code)
	{
    case CMD_TALK_CLEAR:	// 清除對話
        ret = script_cmd_talk_clear();		
        break;
    case CMD_TALK_SAY:		// NPC 對話
        ret = script_cmd_talk_say();
        break;
    case CMD_TALK_NEXT:		// 下一個 script
        ret = script_cmd_talk_next();
        break;
    case CMD_TALK_SHOW:		// 秀出對話
        ret = script_cmd_talk_show();
        break;
    case CMD_CHOICE_CLEAR:	// 清除選擇框
        ret = script_cmd_choice_clear();
        break;
    case CMD_CHOICE_TITLE:	// 選擇攔的提語
        ret = script_cmd_choice_title();
        break;
    case CMD_CHOICE_OPTION:	// 選擇項目
        ret = script_cmd_choice_option();
        break;
    case CMD_CHOICE_SHOW:	// 秀出選擇項目
        ret = script_cmd_choice_show();
        break;
    case CMD_END_DIALOG:	// 結束對話框
        ret = script_cmd_end_dialog();
        break;
	case CMD_CHECK_ITEM:	// 檢查物品
		ret = script_cmd_check_item();
		break;
	case CMD_CHECK_CAREER:	// 檢查職業
		ret = script_cmd_check_career();
		break;
	case CMD_CHECK_SEX:		// 檢查性別
		ret = script_cmd_check_sex();
		break;
	case CMD_CHECK_HP:		// 檢查生命
		ret = script_cmd_check_hp();
		break;
	case CMD_CHECK_MP:		// 檢查魔法
		ret = script_cmd_check_mp();
		break;
	case CMD_CHECK_COUNTRY:	// 檢查國家
		ret = script_cmd_check_country();
		break;
	case CMD_CHECK_PKCOUNT:	// 檢查PK過多少人
		ret = script_cmd_check_pkcount();
		break;
	case CMD_CHECK_PKEDCOUNT:	// 檢查被PK幾次
		ret = script_cmd_check_pkedcount();
		break;
	case CMD_CHECK_GOODEVIL:	// 檢查善惡
		ret = script_cmd_check_goodevil();
		break;
	case CMD_CHECK_GUILDNAME:	// 檢查工會名稱		
		break;
	case CMD_CHECK_LEVEL:		// 檢查等級
		ret = script_cmd_check_level();
		break;
	case CMD_CHECK_MONEY:		// 檢查金錢
		ret = script_cmd_check_money();
		break;
	case CMD_CHECK_STR:			// 檢查力量	
		ret = script_cmd_check_str();
		break;
	case CMD_CHECK_INS:			// 檢查智力
		ret = script_cmd_check_ins();
		break;
	case CMD_CHECK_WIT:			// 檢查直覺
		ret = script_cmd_check_wit();
		break;
	case CMD_CHECK_LUCKY:		// 檢查運氣
		ret = script_cmd_check_lucky();
		break;
	case CMD_CHECK_QUEST_TIME:	// 檢查任務時間	
		ret = script_cmd_check_quest_time();
		break;
	case CMD_GET_STR:			// 取得力量
		ret = script_cmd_get_str();
		break;
	case CMD_GET_INS:			// 取得智力
		ret = script_cmd_get_ins();
		break;
	case CMD_GET_WIT:			// 取得直覺
		ret = script_cmd_get_wit();
		break;
	case CMD_GET_LUCKY:			// 取得運氣
		ret = script_cmd_get_lucky();
		break;
	case CMD_GET_SHIP:			// 取得船隻
		ret = script_cmd_get_ship();
		break;
	case CMD_CHANGE_POSITION:	// 改變座標
		ret = script_cmd_change_position();
		break;
	case CMD_CHANGE_ITEM:		// 改變物品
		ret = script_cmd_change_item();
		break;
	case CMD_POST_SYSTEMMSG:	// 發出公告	
		ret = script_cmd_post_systemmsg();
		break;
	case CMD_GET_ITEM:			// 取得物品
		ret = script_cmd_get_item();
		break;
	case CMD_GET_HEAL:			// 得到醫療
		ret = script_cmd_get_heal();
		break;
	case CMD_GET_SKILL:			// 得到技能
		ret = script_cmd_get_skill();
		break;
	case CMD_REQUEST_CHANGE_ZONE:	// 要求換區域
		ret = script_cmd_request_change_zone();
		break;
	case CMD_CHANGE_ZONE:			// 換區域
		ret = script_cmd_change_zone();
		break;	
	case CMD_INIT_STORE:			// 初始商店
		ret = script_cmd_init_store();
		break;
	case CMD_NPC_STORE:				// NPC 商店
		ret = script_cmd_npc_store();
		break;
	case CMD_NPC_BANK:				// NPC 銀行
		ret = script_cmd_npc_bank();
		break;
	case CMD_CHECK_BAG_SPACE:		// 檢查包包空格
		ret = script_cmd_check_bag_space();
		break;	
	case CMD_DEPOSIT_MONEY:			// 取錢
		ret = script_cmd_deposit_money();
		break;
	case CMD_DRAW_MONEY:			// 存錢
		ret = script_cmd_draw_money();
		break;
// 	case CMD_INIT_QUEST_NPC:		// 設定發布隨機任務 NPC 
// 		ret = script_cmd_init_quest_npc();
// 		break;
	case CMD_GET_QUEST_LIST:		// 要求任務列表
		ret = script_cmd_get_quest_list();
		break;
	case CMD_REPAIR_ITEM:			// 修理物品
		ret = script_cmd_repair_item();
		break;
	case CMD_FULL_FOOD:				// 補充食物
		ret = script_cmd_full_food();
		break;
	//case CMD_FULL_SAILER:			// 補充水手
	//	ret = script_cmd_full_sailer();
	//	break;
	}

#ifdef  MC_DEBUG
    log_error(1, mac_pipe.debug_rec);
#endif//MC_DEBUG

	return	ret;
}

