/*
**	ServerFight.cpp
**	server fight functions.
**
**	Jack, 2002/10/31.
*/
//#include "MainFun.h"
#include "ZoneServer_def.h"
/******************************************************************************************************************/
/* SERVER FIGHT MAIN FUNCTIONS                                                                                    */
/******************************************************************************************************************/
//NPC冥想的數值運算
SLONG   server_process_npc_muse_effect(SLONG npc_no)
{
    // Jack, TODO [00:49,10/31/2002]
    return  0;
}


//NPC被擊斃後的處理:死亡或者重生
SLONG   server_process_npc_dead_relive(SLONG npc_no)
{
	int						index,i;
	int						npc_type; 
	char					mainname[20];
	SLONG					x, y, z;
	SLONG					hp, mp;
	TPOS_DB_CHARACTER		dbcharacterinfo;	
	TPOS_CHARACTER			characterinfo;
	char					dbretzonename[32];
	char					RetCountry;
	TPOS_EVENT_GETCHANGEMAP	EventGetChangeMap;
	TPOS_EVENT_GETNPCRELIVE	EventGetNPCRelive;
	static TPOS_PACKET				send_packet;	
	static TPOS_PACKET				send_packet2;	
	
	// 玩家死亡的處理
	if(npc_no >= 0 && npc_no < 500)
	{
		LOCK_CHARACTER(0);		
		RetCountry = (char)GetCharacterCountry(npc_no);
		SetCharacterDoingKind(npc_no, DOING_KIND_CHANGEMAP);
		UNLOCK_CHARACTER(0);
		LOCK_MACRO(0);
		for(i = 0;i < MAX_ZONE_PER_WORLD;i++)
		{
			if(Macro[0].Zone[i].cCountry == RetCountry)
			{
				strcpy(dbretzonename, Macro[0].Zone[i].cName);
				x = Macro[0].Zone[i].lBirthPointX;
				y = Macro[0].Zone[i].lBirthPointY;
				z = Macro[0].Zone[i].lBirthPointZ;
				break;
			}
		}
		UNLOCK_MACRO(0);
		LOCK_CHARACTER(npc_no);		
		characterinfo = ZoneCharacter[npc_no];
		ServerDoClearOnMouseItemForPlayerExit(npc_no);		
		UNLOCK_CHARACTER(npc_no);
		strcpy(characterinfo.Position.ZoneName, dbretzonename);
		characterinfo.Position.X = x;		
		characterinfo.Position.Y = y;		
		characterinfo.Position.Z = z;		
		characterinfo.HpMp.Hp = characterinfo.HpMp.MaxHp;
		characterinfo.HpMp.Mp = characterinfo.HpMp.MaxMp;
		memset(&dbcharacterinfo, 0x0, sizeof(TPOS_DB_CHARACTER));
		ConvertZoneCharacterToDBCharacter(&characterinfo, &dbcharacterinfo);
		// 如果有在隊伍內, 存下隊長的名字
		if(strcmp(characterinfo.Team.Member[0].MainName, "") != 0)
		{
			strcpy(dbcharacterinfo.LeaderName, characterinfo.Team.Member[0].MainName);
		}

		SaveCharacterItemDataByMainNameAndIndex(npc_no);

		UpdateRecordOfCharacterDB(&dbcharacterinfo);			
		LOCK_ZONEINFO(0);
		index = FindZoneInfoByName(dbretzonename);
		UNLOCK_ZONEINFO(0);
		if(index >= 0)
		{
			// 傳給玩家改變地圖的資訊
			send_packet.Header.dwType = GET_CHANGE_MAP;
			send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_GETCHANGEMAP);												
			LOCK_ZONEINFO(0);				
			strcpy(EventGetChangeMap.cZoneName, ZoneInfo[index].cName);
			strcpy(EventGetChangeMap.cMapName, ZoneInfo[index].cMapName);
			strcpy(EventGetChangeMap.cAddr,ZoneInfo[index].cAddr);
			EventGetChangeMap.dwPort = ZoneInfo[index].dwPort;
			EventGetChangeMap.dwType = ZoneInfo[index].dwType;
			UNLOCK_ZONEINFO(0);			
			EventGetChangeMap.lX = x;
			EventGetChangeMap.lY = y;         
			EventGetChangeMap.lZ = z;
			EventGetChangeMap.cDir = 0;
			
			memcpy(send_packet.data.cBuf, &EventGetChangeMap, sizeof(TPOS_EVENT_GETCHANGEMAP));
			LOCK_CONNECTION(index);				
			index = FindConnectionByName(characterinfo.Name.MainName);				
			UNLOCK_CONNECTION(index);

			server_send_packet_to_one(&Pos_Cn[index], &send_packet);			
			
			send_packet2.Header.dwType = START_CHANGE_MAP;
			send_packet2.Header.dwSize = sizeof(TPOS_PACKETHEADER);
			
			server_send_packet_to_one(&Pos_Cn[index], &send_packet2);
			
		}		
		LOCK_CHARACTER(0);
		ClearOneCharacter(npc_no);
		BadConnect[npc_no] = FALSE;
		UNLOCK_CHARACTER(0);
	}
	// 怪物死亡的處理
	if(npc_no >= 500)
	{
		//------------------------------------------------
		LOCK_CHARACTER(0);
		strcpy(mainname, GetCharacterMainName(npc_no));
		UNLOCK_CHARACTER(0);

		LOCK_ZONEMACRO(0);
		index = FindMarcoDataByMainName(mainname);
		npc_type = ZoneMacro[0].NPC[index].dNPCType;
		x = ZoneMacro[0].NPC[index].dX;
		y = ZoneMacro[0].NPC[index].dY;
		z = ZoneMacro[0].NPC[index].dZ;
		UNLOCK_ZONEMACRO(0);

		LOCK_NPCTYPE(0);
		hp = (UHINT)NPCType[npc_type].Basic.dHP;		
		mp = (UHINT)NPCType[npc_type].Basic.dMP;		
		UNLOCK_NPCTYPE(0);

		EventGetNPCRelive.Index = npc_no;
		EventGetNPCRelive.iHp = (UHINT)hp;
		EventGetNPCRelive.iMp = (UHINT)mp;
		EventGetNPCRelive.lX = x;			
		EventGetNPCRelive.lY = y;			
		EventGetNPCRelive.lZ = z;
		EventGetNPCRelive.cDir = 0;
		// mark by lijun 2003-05-22
		//EventGetNPCRelive.slDoingKind = DOING_KIND_FIGHT_GAD;
		EventGetNPCRelive.slDoingKind = DOING_KIND_IDLE;

		LOCK_CHARACTER(0);
		SetCharacterHp(npc_no, (UHINT)hp);		
		SetCharacterMp(npc_no, (UHINT)mp);
		SetCharacterPosition(npc_no, x, y, z);
		// mark by lijun 2003-05-22
		//SetCharacterDoingKindStep(npc_no,DOING_KIND_FIGHT_GAD,0);				
		SetCharacterDoingKindStep(npc_no,DOING_KIND_IDLE,0);
        // 技能....假的!!!!!需要工具裡面取增加....
        SetCharacterSkillNo(npc_no, 0, MAGIC_NO_ESCRIME);
        SetCharacterSkillLevel(npc_no, 0, 0);
		UNLOCK_CHARACTER(0);		
		
		send_packet.Header.dwType = GET_NPC_RELIVE;
		send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_GETNPCRELIVE);
		memcpy(send_packet.data.cBuf, &EventGetNPCRelive, sizeof(TPOS_EVENT_GETNPCRELIVE));

		SendNPCReliveToAll(&send_packet);
	}
    return  0;
}


//NPC攻擊的運算
SLONG   server_process_npc_attack_npc_effect(SLONG src_npc, SLONG dest_npc, SLONG magic_no)
{
	enum 
	{	RESULT_BEATED = 0, 
	RESULT_DEAD = 1
	};
	SLONG	dest_hp, dest_dp;
	SLONG	src_att, damage, result;
    SLONG   src_x, src_y, src_z;	

    // Jack, todo [03:39,10/31/2002]
    //npc攻擊npc時的判定和結果運算	
	switch(magic_no)
	{	 
	case 0:
	default :
		LOCK_CHARACTER(0);
        GetCharacterPosition(src_npc, &src_x, &src_y, &src_z);
		dest_hp = GetCharacterHp(dest_npc);
		//dest_dp = GetCharacterBaseDefence(dest_npc);
		dest_dp = GetCharacterFinalDefence(dest_npc);
		//src_att = GetCharacterEquipBaseAtt(src_npc);
		src_att = GetCharacterFinalAtt(src_npc);				
		UNLOCK_CHARACTER(0);

		// 如果是玩家 , 判斷是否要變成嫌疑犯
		if(src_npc < 500)
		{
			ServerDoChangeMainNameColorAtFirstFight(src_npc, dest_npc);
		}		
		
		// 計算傷害值
		damage = src_att - dest_dp/2;
		if(damage < 1)
			damage = 1;
		dest_hp -= damage;
		if(dest_hp <= 0)	//RESULT_DEAD
		{			
			// 做善惡及 PK 值的運算					
			if(src_npc < 500)
			{			
				ServerDoChangeMainNameColorAtLastFight(src_npc, dest_npc);							
			}
			LOCK_CHARACTER(0);
			SetCharacterHp(dest_npc, 0);
			SetCharacterDeadState(dest_npc, NPC_DEAD);
			SetCharacterDeadTicks(dest_npc, 100);
			ServerChangeCharacterDoing(dest_npc, DOING_KIND_DEAD, 0, src_npc, 100, 0, 0, magic_no);
			result = RESULT_DEAD;
			UNLOCK_CHARACTER(0);
		}
		else	//RESULT_BEATED
		{
			LOCK_CHARACTER(0);
			SetCharacterHp(dest_npc, (UHINT)dest_hp);
			ServerChangeCharacterDoing(dest_npc, DOING_KIND_BEATED, 0, src_npc, 0, 0, 0, magic_no);
			result = RESULT_BEATED;
			UNLOCK_CHARACTER(0);
		}

		//send to all ----------------------------------
		if(result == RESULT_DEAD)
		{
			// Jack, TODO [1/8/2003]
			ServerSendChangeNpcDoing(dest_npc, DOING_KIND_DEAD, 0,
									 src_npc, 100, src_x, src_y, magic_no);			
		}
		else
		{
			// Jack, TODO [1/8/2003]
			ServerSendChangeNpcDoing(dest_npc, DOING_KIND_BEATED, 0,
									 src_npc, dest_hp, src_x, src_y, magic_no);							
		}
		break;
	}
    return  0;
}


//NPC連擊的最後一擊的運算
SLONG   server_process_npc_final_attack_npc_effect(SLONG src_npc, SLONG dest_npc, SLONG magic_no)
{
	enum 
	{	RESULT_DOWN_AND_OUT     = 0,    //被擊倒
	RESULT_DEAD                 = 1,    //被擊斃
	};
	SLONG	dest_hp, dest_dp;
	SLONG	src_att, damage, result;
    SLONG   src_x, src_y, src_z;

	switch(magic_no)
	{	 
	case 0:
	default :
		LOCK_CHARACTER(0);
        GetCharacterPosition(src_npc, &src_x, &src_y, &src_z);
		dest_hp = GetCharacterHp(dest_npc);
		//dest_dp = GetCharacterBaseDefence(dest_npc);
		dest_dp = GetCharacterFinalDefence(dest_npc);
		//src_att = GetCharacterEquipBaseAtt(src_npc);
		src_att = GetCharacterFinalAtt(src_npc);
		UNLOCK_CHARACTER(0);
		damage = src_att - dest_dp/10;
		if(damage < 5)
			damage = 5;
		dest_hp -= damage;
		if(dest_hp <= 0)	//RESULT_DEAD
		{
			// 如果是玩家打死玩家或 NPC , 做善惡及 PK 值的運算
			if(src_npc < 500)
			{			
				ServerDoChangeMainNameColorAtLastFight(src_npc, dest_npc);				
			}
			LOCK_CHARACTER(0);
			SetCharacterHp(dest_npc, 0);
			SetCharacterDeadState(dest_npc, NPC_DEAD);
			SetCharacterDeadTicks(dest_npc, 100);
			ServerChangeCharacterDoing(dest_npc, DOING_KIND_DEAD, 0, src_npc, 100, 0, 0, magic_no);
			UNLOCK_CHARACTER(0);
			result = RESULT_DEAD;
		}
		else	//RESULT_DOWN_AND_OUT
		{
			LOCK_CHARACTER(0);
			SetCharacterHp(dest_npc, (UHINT)dest_hp);
			ServerChangeCharacterDoing(dest_npc, DOING_KIND_DOWN_AND_OUT, 0, src_npc, 0, 0, 0, magic_no);
			UNLOCK_CHARACTER(0);
			result = RESULT_DOWN_AND_OUT;
		}

		//send to all ----------------------------------
		if(result == RESULT_DEAD)
		{
			// Jack, TODO [1/8/2003]			
			ServerSendChangeNpcDoing(dest_npc, DOING_KIND_DEAD, 0,
									 src_npc, 100, src_x, src_y, magic_no);				
		}
		else
		{
			// Jack, TODO [1/8/2003]			
			ServerSendChangeNpcDoing(dest_npc, DOING_KIND_DOWN_AND_OUT, 0,
									 src_npc, dest_hp, src_x, src_y, magic_no);				
		}
		break;
	}
    return  0;
}


SLONG   server_is_player_can_change_fight_state(SLONG npc_no, SLONG fight_flag)
{
    // Jack, todo [09:42,10/31/2002]
    //判斷玩家此時是否可以切換自己的戰鬥狀態(如果切換, 可能會改變該玩家的DOING_KIND)
    //以後需要根據NPC當前進行的事情來確定是否可以改變, 比如被擊時改變就無效...
    return  true;
}


//NPC衝撞後的運算
SLONG   server_process_npc_clash_effect(SLONG npc_no)
{
    SLONG   orig_x, orig_y, orig_z;
    SLONG   curr_x, curr_y, curr_z;
    SLONG   magic_no;

    LOCK_CHARACTER(npc_no);
    GetCharacterOrigPosition(npc_no, &orig_x, &orig_y, &orig_z);
    GetCharacterPosition(npc_no, &curr_x, &curr_y, &curr_z);
    magic_no = GetCharacterDoingMagic(npc_no);
    UNLOCK_CHARACTER(npc_no);

    server_process_magic_attack_line(magic_no, npc_no, orig_x, orig_y, curr_x, curr_y);

    return  0;
}



//法術攻擊一條直線段區域
SLONG   server_process_magic_attack_line(SLONG magic_index, SLONG src_npc,
                                         SLONG magic_orig_x, SLONG magic_orig_y,
                                         SLONG magic_dest_x, SLONG magic_dest_y)
{
    enum
    {   ATTACK_LINE_LEN =   SCREEN_HEIGHT / 2,
    };
    SLONG   attack_radius;  //與攻擊直線的距離
    SLONG   found_dest_npc;
    //SLONG   magic_relation;
    //SLONG   npc_flag;
    SLONG   dest_npc, dest_npc_x, dest_npc_y, dest_npc_z;
    SLONG   dest_npc_hp;
    //SLONG   dest_npc_kind;
    //SLONG   relation;
    SLONG   distance;
    SLONG   dx, dy;
    SLONG   is_available;
    double  dr, kx, ky;
    double  upright_kx, upright_ky;
    //SLONG   droop_distance;
    SLONG   droop_x, droop_y, droop_z;
    SLONG   through_result;
    double  t;
	SLONG	dest_doing_kind;

    //attack_radius = magic_data[magic_index].radius;
    attack_radius = 100;
    //magic_relation = magic_data[magic_index].relation;

    dx = magic_dest_x - magic_orig_x;
    dy = magic_dest_y - magic_orig_y;
    dr = sqrt( dx * dx + dy * dy );
    if(dr == 0)
        return  0;

    kx = dx / dr;
    ky = dy / dr;
    upright_kx = ky;
    upright_ky = -kx;
    
    found_dest_npc = FALSE;
    for(dest_npc = 0; dest_npc < 1000; dest_npc ++)
    {
        if(dest_npc == src_npc)
            continue;

        LOCK_CHARACTER(dest_npc);
        //dest_npc_kind = game_npc[dest_npc].kind;
        GetCharacterPosition(dest_npc, &dest_npc_x, &dest_npc_y, &dest_npc_z);
        is_available = IsCharacterAvailable(dest_npc);
        dest_npc_hp = GetCharacterHp(dest_npc);
		dest_doing_kind = GetCharacterDoingKind(dest_npc);		
        UNLOCK_CHARACTER(dest_npc);
        if( (! is_available) || dest_npc_hp <= 0 )
            continue;
		if( dest_doing_kind == DOING_KIND_CHANGEMAP)
			continue;
        //relation = get_npc_magic_standpoint_relation(src_npc, dest_npc);
        //if(!(relation & magic_relation))
          //  continue;

        //計算目標點到攻擊直線的垂足
        D3_droop_point_line(dest_npc_x, dest_npc_y, 0, magic_orig_x, magic_orig_y, 0, 
            magic_dest_x, magic_dest_y, 0, &droop_x, &droop_y, &droop_z);

        //檢查目標點到垂足的距離, 如果距離大於攻擊距離, 則不在範圍
        distance = D2_distance_point_point(dest_npc_x, dest_npc_y, droop_x, droop_y);
        if(distance > attack_radius)
            continue;

        //檢查垂足是否在攻擊線段上
        if(magic_dest_x != magic_orig_x)
            t = (double)(droop_x - magic_orig_x) / (double)(magic_dest_x - magic_orig_x);
        else if(magic_dest_y != magic_orig_y)
            t = (double)(droop_y - magic_orig_y) / (double)(magic_dest_y - magic_orig_y);
        if(t < 0 || t >= 1.0)
            continue;

        //計算目標點和攻擊起點之間是否有阻擋, 如果被
        LOCK_MAPMASK(0);
        through_result = IsPixelLineThrough(droop_x, droop_y, dest_npc_x, dest_npc_y, MASK_STOP);
        UNLOCK_MAPMASK(0);
        
        if(TRUE == through_result)
        {
            found_dest_npc = TRUE;
            
            server_process_line_attack_effect(magic_index, src_npc, dest_npc, droop_x, droop_y);
        }
    }
    return  found_dest_npc;
}



//計算直線攻擊效果
SLONG   server_process_line_attack_effect(SLONG magic_no, SLONG src_npc, SLONG dest_npc, SLONG src_attack_x, SLONG src_attack_y)
{
	enum 
	{	RESULT_DOWN_AND_OUT     = 0, 
	RESULT_DEAD                 = 1
	};
	SLONG	dest_hp, dest_dp;
	SLONG	src_att, damage, result;

    // Jack, todo(需要設定被擊NPC的方向參數) [03:39,10/31/2002]
	switch(magic_no)
	{	 
	case 0:
	default :
		LOCK_CHARACTER(0);
		dest_hp = GetCharacterHp(dest_npc);
		//dest_dp = GetCharacterBaseDefence(dest_npc);		
		dest_dp = GetCharacterFinalDefence(dest_npc);
		//src_att = GetCharacterEquipBaseAtt(src_npc);
		src_att = GetCharacterFinalAtt(src_npc);
		UNLOCK_CHARACTER(0);

		// 如果是玩家 , 判斷是否要變成嫌疑犯
		if(src_npc < 500)
		{
			ServerDoChangeMainNameColorAtFirstFight(src_npc, dest_npc);
		}
		
		damage = src_att - dest_dp/2;
		if(damage < 1)
			damage = 1;
		dest_hp -= damage;
		if(dest_hp <= 0)	//RESULT_DEAD
		{
			// 如果是玩家打死玩家或 NPC , 做善惡及 PK 值的運算
			if(src_npc < 500)
			{			
				ServerDoChangeMainNameColorAtLastFight(src_npc, dest_npc);				
			}
			LOCK_CHARACTER(0);
			SetCharacterHp(dest_npc, 0);
			SetCharacterDeadState(dest_npc, NPC_DEAD);
			SetCharacterDeadTicks(dest_npc, 100);			
			ServerChangeCharacterDoing(dest_npc, DOING_KIND_DEAD, 0, src_npc, 100, 0, 0, magic_no);
			UNLOCK_CHARACTER(0);
			result = RESULT_DEAD;
		}
		else	//RESULT_BEATED
		{
			LOCK_CHARACTER(0);
			SetCharacterHp(dest_npc, (UHINT)dest_hp);
			ServerChangeCharacterDoing(dest_npc, DOING_KIND_DOWN_AND_OUT, 0, src_npc, 0, 0, 0, magic_no);
			UNLOCK_CHARACTER(0);
			result = RESULT_DOWN_AND_OUT;
		}
		


		//send to all ----------------------------------
		if(result == RESULT_DEAD)
		{
			// Jack, TODO [1/8/2003]
			ServerSendChangeNpcDoing(dest_npc, DOING_KIND_DEAD, 0,
									 src_npc, 100, src_attack_x, src_attack_y, magic_no);				
		}
		else
		{
			// Jack, TODO [1/8/2003]			
			ServerSendChangeNpcDoing(dest_npc, DOING_KIND_DOWN_AND_OUT, 0,
									 src_npc, dest_hp, src_attack_x, src_attack_y, magic_no);				
		}
		break;
	}
    return  0;
}


/******************************************************************************************************************/
/* NPC死亡後的數值運算                                                                                            */
/******************************************************************************************************************/
SLONG   server_process_npc_dead_operation(SLONG npc_no)
{
    SLONG	beated_by, level;
    SLONG	exp, cash;		
	SLONG	x,y,z;
	UHINT	attack_level;	
	UHINT	monster_type;
	SLONG	base_exp;
	UHINT	npc_kind;


    if(npc_no < 500)    //先略過是玩家的處理
        return  0;
    
    LOCK_CHARACTER(npc_no);
    beated_by = GetCharacterBeatedBy(npc_no);
    exp = GetCharacterExp(npc_no);
    cash = GetCharacterBodyMoney(npc_no);
    level = GetCharacterLevel(npc_no);
	GetCharacterPosition(npc_no, &x, &y, &z);	
	npc_kind = (UHINT)GetCharacterKind(npc_no);	
	attack_level = GetCharacterLevel(beated_by);	
    UNLOCK_CHARACTER(npc_no);

	LOCK_NPCTYPE(0);
	monster_type = NPCType[npc_kind].Name.uiKind;
	UNLOCK_NPCTYPE(0);
    // Hawke Add 2003-04-28 For Process Computer Get Exp
	switch(monster_type)
	{
	case NPC_KIND_NORMAL_MONSTER: 	
		base_exp = 100;	
		break;
	case NPC_KIND_HEADER_MONSTER:		
		base_exp = 200;	
		break;
	case NPC_KIND_BOSS_MONSTER:		
		base_exp = 500;	
		break;
	}
    if(attack_level == level)
	{
		exp = base_exp;
	}else
	{
		if(attack_level > level)
		{
			exp = base_exp + ((attack_level - level) * 0.1);
			if(exp >= base_exp * 2)exp = base_exp * 2;
		}
		if(level > attack_level)
		{
			exp = base_exp - ((level - attack_level) * 0.1);
			if(exp < 0)exp = 0;
		}
	}
    
    //掉下物品
	server_process_npc_drop_item(npc_no, beated_by, x, y, z);

    //掉下金錢

    //攻擊者獲得經驗值
    if(exp > 0)
    {
        server_process_npc_get_exp(beated_by, exp);
    }

    //其他運算, 比如是否該NPC帶有劇本需要執行, 
    //是否該地圖上所有同組怪物死亡帶有劇本需要執行,
    //是否該地圖上所有怪物死亡帶有劇本需要執行
    //等等

    return  0;
}

SLONG	server_process_npc_drop_item(SLONG npc_no, SLONG beated_by, SLONG x, SLONG y, SLONG z)
{	
	TPOS_PACKET					send_packet;
	TPOS_EVENT_NOTIFYADDMAPITEM	EventNotifyAddMapItem;
	TPOS_ITEM					dropitem;
	TPOS_ITEM_MF				itemmf;
	SLONG						drop;
	SLONG						Ret;
	char						ownername[32];
	char						leadername[32];
	int							i;	


	drop = -1;	
	
	itemmf.CurrentZoneType = ZoneType;
	itemmf.DestNpc = npc_no;
	itemmf.PlayerIndex = beated_by;
	LOCK_MACRO(0);
	itemmf.FindGoldZoneItemMFProbability = Macro[0].dFindGoldZoneItemMFProbability;
	itemmf.OtherZoneItemMFProbability = Macro[0].dOtherZoneItemMFProbability;
	for(i = 0;i < 17;i++)
	{
		itemmf.NPCTypeDropItemProbability[i] = Macro[0].uiNPCTypeDropItemProbability[i];
	}	
	UNLOCK_MACRO(0);
	LOCK_ZONEMACRO(0);
	itemmf.NormalProbability = ZoneMacro[0].uiNormalProbability;
	itemmf.DrugProbability = ZoneMacro[0].uiDrugProbability;
	itemmf.MoneyProbability = ZoneMacro[0].uiMoneyProbability;
	itemmf.TreasureMapProbability = ZoneMacro[0].uiTreasureMapProbability;
	UNLOCK_ZONEMACRO(0);
	LOCK_CHARACTER(0);
	itemmf.MonsterLevel = GetCharacterLevel(npc_no);
	itemmf.MonsterType = NPCType[GetCharacterKind(npc_no)].Name.uiKind;
	UNLOCK_CHARACTER(0);	
	
	// 判斷東西所有權
	LOCK_CHARACTER(0);
	// Hawke  [2/20/2003]
	// TO DO 
	// 以後要判斷他是否加入團隊,如果是就歸為團隊的
	strcpy(leadername, GetCharacterTeamMemberMainName(npc_no, 0));
	if(strcmp(leadername, "") != 0)
	{
		strcpy(ownername, leadername);
	}else
	{
		strcpy(ownername, GetCharacterMainName(beated_by));
	}	
	UNLOCK_CHARACTER(0);	
	
	drop = MakeItem(&dropitem,itemmf);
		
	if(drop == 0)
	{
		Ret = FindContainItemPosition(&x, &y);
		if(Ret == TTN_OK)
		{			
			LOCK_ITEM(0);
			AddZoneItem(x, y, ownername, &dropitem);
			UNLOCK_ITEM(0);
			send_packet.Header.dwType = NOTIFY_ADD_MAP_ITEM;
			send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYADDMAPITEM);
			EventNotifyAddMapItem.Item = dropitem;
			EventNotifyAddMapItem.X = x;
			EventNotifyAddMapItem.Y = y;
			memcpy(send_packet.data.cBuf, &EventNotifyAddMapItem, sizeof(TPOS_EVENT_NOTIFYADDMAPITEM));
			server_send_packet_to_all(&send_packet);
		}
	}
	return 0;
}

SLONG   server_process_npc_get_exp(SLONG npc_no, SLONG get_exp)
{
    UHINT   level;
	SLONG	exp;
    CHARACTER_UPGRADE_RESULT  Result;
	SLONG	Ret;	

    if(npc_no >= 500)   //如果不是玩家, 則略過.
        return  0;

    //npc get exp ---------------------------
    LOCK_CHARACTER(npc_no);
    exp = GetCharacterExp(npc_no);
    level = GetCharacterLevel(npc_no);    
    UNLOCK_CHARACTER(npc_no);    

    exp += get_exp;
    if(exp > MAX_CAREER_EXP)
        exp = MAX_CAREER_EXP;

    //check if npc upgrade ------------------
	LOCK_CHARACTER(0);
	Ret = ComputeCharacterUpgradeResult(npc_no, level, exp, &Result);
	UNLOCK_CHARACTER(0);
    if(Ret == TRUE)
	{	          
		// Jack, TODO [1/8/2003]
		//將改變送給玩家
		static TPOS_PACKET				send_packet;
		TPOS_EVENT_NPCLEVELUP	EventNpcLevelUp;

        send_packet.Header.dwType = NPC_LEVEL_UP;
        send_packet.Header.dwSize= sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NPCLEVELUP);

		EventNpcLevelUp.Index = npc_no;
        EventNpcLevelUp.Level = (UHINT)Result.level;
        EventNpcLevelUp.MaxHp = Result.max_hp;
        EventNpcLevelUp.MaxMp = Result.max_mp;
        EventNpcLevelUp.AttribPoint = Result.property_point;
        EventNpcLevelUp.Exp = exp;
        EventNpcLevelUp.NextExp = Result.next_exp;
		memcpy(send_packet.data.cBuf, &EventNpcLevelUp, sizeof(TPOS_EVENT_NPCLEVELUP));
        server_send_packet_to_all(&send_packet);              
    }
    else
    {
        //改變玩家的經驗值
        LOCK_CHARACTER(npc_no);
        SetCharacterExp(npc_no, exp);
        UNLOCK_CHARACTER(npc_no);

		// Jack, TODO [1/8/2003]		
        //將改變送給玩家
        static TPOS_PACKET				send_packet;
		TPOS_EVENT_SETNPCEXP	EventSetNpcExp;

        send_packet.Header.dwType = SET_NPC_EXP;
        send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_SETNPCEXP);
		EventSetNpcExp.Index = npc_no;
		EventSetNpcExp.Exp = exp;
        memcpy(send_packet.data.cBuf, &EventSetNpcExp, sizeof(TPOS_EVENT_SETNPCEXP));
        server_send_packet_to_player(npc_no, &send_packet);		
    }

    return  0;
}

// mark by lijun 2003-05-22
/*

//AI FUNCTIONS
void    server_execute_npc_ai_when_move( SLONG npc_no )
{
    SLONG   ai_kind;
    SLONG   ai_when_move;
    SLONG   dest_npc;

    LOCK_CHARACTER(npc_no);
    ai_kind = GetCharacterAI(npc_no);
    UNLOCK_CHARACTER(npc_no);

    ai_when_move = ai_kind & AI_KIND_MASK_WHEN_MOVE;
    switch(ai_when_move)
    {
    case AI_KIND_NONE_WHEN_MOVE:
        break;
    case AI_KIND_ATTACK_WHEN_MOVE:
        {
            dest_npc = search_near_target_npc(npc_no);
            if(dest_npc >= 0)
            {
                server_choose_npc_attack_npc( npc_no, dest_npc );
            }
        }
        break;
    case AI_KIND_MAGIC_WHEN_MOVE:
        {
            dest_npc = search_near_target_npc(npc_no);
            if(dest_npc >= 0)
            {
                server_choose_npc_magic_npc( npc_no, dest_npc );
            }
        }
        break;
    case AI_KIND_MIXED_WHEN_MOVE:
        {
            dest_npc = search_near_target_npc(npc_no);
            if(dest_npc >= 0)
            {
                server_choose_npc_mixed_attack_npc( npc_no, dest_npc );
            }
        }
        break;
    case AI_KIND_DODGE_WHEN_MOVE:
        {
            dest_npc = search_near_target_npc(npc_no);
            if(dest_npc >= 0)
            {
                server_choose_npc_dodge_npc( npc_no, dest_npc );
            }
        }
        break;
    case AI_KIND_RUN_ATTACK_WHEN_MOVE:
        {
            dest_npc = search_near_target_npc(npc_no);
            if(dest_npc >= 0)
            {
                server_choose_npc_run_attack_npc( npc_no, dest_npc );
            }
        }
        break;
	case AI_KIND_TRANCE_WHEN_MOVE:
		server_choose_npc_trance(npc_no);
		break;
    default:
        break;
    }
}


void    server_execute_npc_ai_after_attack( SLONG npc_no )
{
    SLONG   ai_kind;
    SLONG   ai_after_attack;
    SLONG   dest_npc, dest_hp;

    LOCK_CHARACTER(npc_no);
    ai_kind = GetCharacterAI(npc_no);
    dest_npc = GetCharacterDestID(npc_no);
    UNLOCK_CHARACTER(npc_no);

	if(dest_npc<0)
	{
		server_choose_npc_move_type(npc_no);
		return;
	}

	LOCK_CHARACTER(dest_npc);
	dest_hp = GetCharacterHp(dest_npc);
	UNLOCK_CHARACTER(dest_npc);
	if(dest_hp <= 0)
	{
		server_choose_npc_move_type(npc_no);
		return;
	}


    ai_after_attack = ai_kind & AI_KIND_MASK_AFTER_ATTACK;
    switch(ai_after_attack)
    {
    case AI_KIND_NONE_AFTER_ATTACK:
        server_choose_npc_move_type( npc_no );
        break;
    case AI_KIND_ATTACK_AFTER_ATTACK:
        server_choose_npc_attack_npc( npc_no, dest_npc );
        break;
    case AI_KIND_MAGIC_AFTER_ATTACK:
        server_choose_npc_magic_npc( npc_no, dest_npc );
        break;
    case AI_KIND_MIXED_AFTER_ATTACK:
        server_choose_npc_mixed_attack_npc( npc_no, dest_npc );
        break;
    case AI_KIND_DODGE_AFTER_ATTACK:
        server_choose_npc_dodge_npc( npc_no, dest_npc );
        break;
    case AI_KIND_RUN_ATTACK_AFTER_ATTACK:
        server_choose_npc_run_attack_npc( npc_no, dest_npc );
        break;
	case AI_KIND_TRANCE_AFTER_ATTACK:
		server_choose_npc_trance(npc_no);
		break;
    default:
        server_choose_npc_fight_idle( npc_no );
        break;
    }
}


void    server_execute_npc_ai_after_magic( SLONG npc_no )
{
	/----------------------------------------------------------------------
    SLONG   ai_kind;
    SLONG   ai_after_magic;
    SLONG   dest_npc;

    LOCK_CHARACTER(npc_no);
    ai_kind = GetCharacterAI(npc_no);
    dest_npc = GetCharacterDestID(npc_no);
    UNLOCK_CHARACTER(npc_no);

    ai_after_magic = ai_kind & AI_KIND_MASK_AFTER_MAGIC;
    switch(ai_after_magic)
    {
    case AI_KIND_NONE_AFTER_MAGIC:
        server_choose_npc_move_type( npc_no );
        break;
    case AI_KIND_ATTACK_AFTER_MAGIC:
        server_choose_npc_attack_npc( npc_no, dest_npc );
        break;
    case AI_KIND_MAGIC_AFTER_MAGIC:
        server_choose_npc_magic_npc( npc_no, dest_npc );
        break;
    case AI_KIND_MIXED_AFTER_MAGIC:
        server_choose_npc_mixed_attack_npc( npc_no, dest_npc );
        break;
    case AI_KIND_DODGE_AFTER_MAGIC:
        server_choose_npc_dodge_npc( npc_no, dest_npc );
        break;
    case AI_KIND_RUN_ATTACK_AFTER_MAGIC:
        server_choose_npc_run_attack_npc( npc_no, dest_npc );
        break;
	case AI_KIND_TRANCE_AFTER_MAGIC:
		server_choose_npc_trance(npc_no);
		break;
    default:
        server_choose_npc_fight_idle( npc_no );
        break;
    }
	/----------------------------------------------------------------------
}


void    server_execute_npc_ai_after_beated( SLONG npc_no )
{
    SLONG				ai_kind;
    SLONG				ai_after_beated;
    SLONG				dest_npc;		

    LOCK_CHARACTER(npc_no);
    ai_kind = GetCharacterAI(npc_no);  
	dest_npc = GetCharacterBeatedBy(npc_no);	
    UNLOCK_CHARACTER(npc_no);
	
    ai_after_beated = ai_kind & AI_KIND_MASK_AFTER_BEATED;
    switch(ai_after_beated)
    {
    case AI_KIND_NONE_AFTER_BEATED:
        server_choose_npc_move_type( npc_no );
        break;
    case AI_KIND_ATTACK_AFTER_BEATED:
        server_choose_npc_attack_npc( npc_no, dest_npc );
        break;
    case AI_KIND_MAGIC_AFTER_BEATED:
        server_choose_npc_magic_npc( npc_no, dest_npc );
        break;
    case AI_KIND_MIXED_AFTER_BEATED:
        server_choose_npc_mixed_attack_npc( npc_no, dest_npc );
        break;
    case AI_KIND_DODGE_AFTER_BEATED:
        server_choose_npc_dodge_npc( npc_no, dest_npc );
        break;
    case AI_KIND_RUN_ATTACK_AFTER_BEATED:
        server_choose_npc_run_attack_npc( npc_no, dest_npc );
        break;
	case AI_KIND_TRANCE_AFTER_BEATED:
		server_choose_npc_trance(npc_no);
		break;
    default:
        server_choose_npc_fight_idle( npc_no );
        break;
    }
}


void    server_execute_npc_ai_after_dodge( SLONG npc_no )
{
    SLONG   ai_kind;
    SLONG   ai_after_dodge;
    SLONG   dest_npc;

    LOCK_CHARACTER(npc_no);
    ai_kind = GetCharacterAI(npc_no);
    dest_npc = GetCharacterDestID(npc_no);
    UNLOCK_CHARACTER(npc_no);

    ai_after_dodge = ai_kind & AI_KIND_MASK_AFTER_DODGE;
    switch(ai_after_dodge)
    {
    case AI_KIND_NONE_AFTER_DODGE:
        server_choose_npc_move_type( npc_no );
        break;
    case AI_KIND_ATTACK_AFTER_DODGE:
        server_choose_npc_attack_npc( npc_no, dest_npc );
        break;
    case AI_KIND_MAGIC_AFTER_DODGE:
        server_choose_npc_magic_npc( npc_no, dest_npc );
        break;
    case AI_KIND_MIXED_AFTER_DODGE:
        server_choose_npc_mixed_attack_npc( npc_no, dest_npc );
        break;
    case AI_KIND_DODGE_AFTER_DODGE:
        // The npc can't dodge again after the current dodge.
        // So we will choose move type to move.
        server_choose_npc_move_type( npc_no );
        break;
    case AI_KIND_RUN_ATTACK_AFTER_DODGE:
        server_choose_npc_run_attack_npc( npc_no, dest_npc );
        break;
	case AI_KIND_TRANCE_AFTER_DODGE:
		server_choose_npc_trance(npc_no);
		break;
    default:
        server_choose_npc_fight_idle( npc_no );
        break;
    }
}
void    server_choose_npc_magic_npc( SLONG npc_no, SLONG dest_npc )
{
	/-----------------------------------------------------------------------
    SLONG   magic_index;
    SLONG   magic_times;
    SLONG   dest_x, dest_y, dest_z;
    
    {
        LOCK_CHARACTER(npc_no);
        //magic_index = GetCharacterDoingMagic(npc_no);
		//	game_npc[npc_no].magic[ system_rand() % MAX_NPC_MAGIC ];
        UNLOCK_CHARACTER(npc_no);
        
        if(magic_index < 0 || magic_index >= MAX_GAME_MAGIC) magic_index = 0;
        magic_times = magic_data[magic_index].times;
        
        if(dest_npc < 0 || dest_npc >= MAX_PLAYER_PER_ZONE) dest_npc = 0;
        LOCK_CHARACTER(dest_npc);
        GetCharacterDestPosition(npc_no, &dest_x, &dest_y, &dest_z);
        UNLOCK_CHARACTER(dest_npc);
        
        LOCK_CHARACTER(npc_no);
		ServerChangeCharacterDoing(npc_no, DOING_KIND_MAGIC_NPC, 0, dest_npc,dest_x, dest_y, magic_index, magic_times);        
        UNLOCK_CHARACTER(npc_no);
    }
    {
        MSG_UPDATE_NPC_DOING_MAGIC  msg;

        msg.dwType = UMT_UPDATE_NPC_DOING_MAGIC;
        msg.npc_no = npc_no;
        msg.doing_kind = DOING_KIND_MAGIC_NPC;
        msg.doing_step = 0;
        msg.dest_npc = dest_npc;
        msg.dest_x = dest_x;
        msg.dest_y = dest_y;
        msg.magic_index = magic_index;
        msg.magic_times = magic_times;

        AddServerSendMsg( &msg, sizeof(msg), g_dpidLocal, ALLPLAYER );
    }
	/-----------------------------------------------------------------------
}


void    server_choose_npc_attack_npc( SLONG npc_no, SLONG dest_npc )
{
	DWORD	dest_hp;
    {		
        LOCK_CHARACTER(npc_no);
		dest_hp = GetCharacterHp(dest_npc);
		if(dest_hp > 0)
		{		
			ServerChangeCharacterDoing(npc_no, DOING_KIND_ATTACK_NPC, 0, dest_npc, 0, 0, 0, 0);
		}
        UNLOCK_CHARACTER(npc_no);
    }
    {
		if(dest_hp > 0)
		{	
			// Jack, TODO [1/8/2003]
			ServerSendChangeNpcDoing(npc_no, DOING_KIND_ATTACK_NPC, 0,
									 dest_npc, 600, 0, 0, 0);				
		}
    }
}


void    server_choose_npc_mixed_attack_npc( SLONG npc_no, SLONG dest_npc )
{
    if(system_rand() % 100 >= 50)
    {
        server_choose_npc_magic_npc( npc_no, dest_npc );
    }
    else
    {
        server_choose_npc_attack_npc( npc_no, dest_npc );
    }
}


void    server_choose_npc_dodge_npc( SLONG npc_no, SLONG dest_npc )
{
	/---------------------------------------------------------------------
    {
        LOCK_CHARACTER(npc_no);
		ServerChangeCharacterDoing(npc_no, DOING_KIND_DODGE_NPC, 0, )
        game_npc[npc_no].doing_kind = DOING_KIND_DODGE_NPC;
        game_npc[npc_no].doing_step = 0;
        game_npc[npc_no].dest_no = dest_npc;
        UNLOCK_CHARACTER(npc_no);
    }
    {
        //Don't need to notify clients for we will do it in server_do_npc_dodge().
    }
	/---------------------------------------------------------------------
}


void    server_choose_npc_move_type( SLONG npc_no )
{
    SLONG   ai_kind, ai_move_type;

    LOCK_CHARACTER(npc_no);
    ai_kind = GetCharacterAI(npc_no);
    UNLOCK_CHARACTER(npc_no);

    ai_move_type = ai_kind & AI_KIND_MASK_MOVE_TYPE;
    switch(ai_move_type)
    {
    case AI_KIND_GAD_MOVE_TYPE:
        server_choose_npc_fight_gad( npc_no );
        break;
    case AI_KIND_IDLE_MOVE_TYPE:
        server_choose_npc_fight_idle( npc_no );
        break;
    default:
        server_choose_npc_fight_idle( npc_no );
        break;
    }
}


void    server_choose_npc_fight_idle( SLONG npc_no )
{
    {
        LOCK_CHARACTER(npc_no);
		ServerChangeCharacterDoing(npc_no, DOING_KIND_FIGHT_IDLE, 0, 0, 0, 0, 0, 0);        
        UNLOCK_CHARACTER(npc_no);
    }
    {
		// Jack, TODO [1/8/2003]
		ServerSendChangeNpcDoing(npc_no, DOING_KIND_FIGHT_IDLE, 0,
									 0, 0, 0, 0, 0);			
    }
}


void    server_choose_npc_fight_gad( SLONG npc_no )
{
    {
        LOCK_CHARACTER(npc_no);
		ServerChangeCharacterDoing(npc_no, DOING_KIND_FIGHT_GAD, 0, 0,0,0,0,0);        
        UNLOCK_CHARACTER(npc_no);
    }
    {
        // Don't need to notify clients for we will do it in server_do_npc_fight_gad().
    }
}


void    server_choose_npc_run_attack_npc( SLONG npc_no, SLONG dest_npc )
{
	/----------------------------------------------------------------------
    {
        LOCK_CHARACTER(npc_no);
		ServerChangeCharacterDoing(npc_no, DOING_KIND_RUN_ATTACK_NPC, 0, dest_npc, 0 ,0,0,0);        
        UNLOCK_CHARACTER(npc_no);
    }
    {
        MSG_UPDATE_NPC_DOING_RUN_ATTACK_NPC msg;

        msg.dwType = UMT_UPDATE_NPC_DOING_RUN_ATTACK_NPC;
        msg.npc_no = npc_no;
        msg.dest_no = dest_npc;
        msg.doing_kind = DOING_KIND_RUN_ATTACK_NPC;
        msg.doing_step = 0;

        AddServerSendMsg( &msg, sizeof(msg), g_dpidLocal, ALLPLAYER );
    }
	return;
	/----------------------------------------------------------------------
}


void	server_choose_npc_trance(SLONG npc_no)
{
	/----------------------------------------------------------------------
	SLONG	dest_x, dest_y, orig_x, orig_y;
	SLONG	fight_ticks;

	{
		LOCK_NPC(npc_no);
		dest_x = game_npc[npc_no].x;
		dest_y = game_npc[npc_no].y;
		orig_x = 5;	//as gad total_ticks
		orig_y = 0;	//as gad ticks
		fight_ticks = 100;
		//
		game_npc[npc_no].doing_kind = DOING_KIND_TRANCE;
		game_npc[npc_no].doing_step = 0;
		game_npc[npc_no].dest_x = dest_x;
		game_npc[npc_no].dest_y = dest_y;
		game_npc[npc_no].orig_x = orig_x;
		game_npc[npc_no].orig_y = orig_y;
		game_npc[npc_no].fight_ticks = (UCHR)fight_ticks;
		UNLOCK_NPC(npc_no);
	}
	{
		MSG_UPDATE_NPC_DOING_TRANCE	msg;

		msg.dwType = UMT_UPDATE_NPC_DOING_TRANCE;
		msg.npc_no = npc_no;
		msg.doing_kind = DOING_KIND_TRANCE;
		msg.doing_step = 0;
		msg.dest_x = dest_x;
		msg.dest_y = dest_y;
		msg.orig_x = orig_x;
		msg.orig_y = orig_y;
		msg.trance_ticks = fight_ticks;

		AddServerSendMsg( &msg, sizeof(msg), g_dpidLocal, ALLPLAYER);
	}
	return;
	/----------------------------------------------------------------------
}
*/

