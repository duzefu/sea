//-------------------------------------------------------------------------------
// Psalm of Sea WorldServer Misc
// By Hawke Hsieh
// 2002-10-7
//-------------------------------------------------------------------------------

#include "WorldServer_Def.h"

//-------------------------------------------------------------------------------
int     FindUsableZoneQQOnlinePlayerList(int zoneindex)
{
	int i, find_idx;

    find_idx = -1;
	
    for(i=0; i<MAX_PLAYER_PER_ZONE; i++)
    {
        if(ZoneInfo[zoneindex].QQOnlinePlayerList[i].ID == 0)
        {
            find_idx = i;
            break;
        }
    }
	
    return  find_idx;
}

//-------------------------------------------------------------------------------
int     FindUsableZoneInfo(void)
{
	int i;

    for(i=0; i<MAX_ZONE_PER_WORLD; i++)
    {
        if(ZoneInfo[i].dwIndex ==0)
        {
            return(i);            
        }
    }
    return  -1;
}
//-------------------------------------------------------------------------------
int     FindZoneInfoByName(char *name)
{
	int i;
    
    for(i=0; i<MAX_ZONE_PER_WORLD; i++)
    {
        if(strcmp(ZoneInfo[i].cName,name) ==0)
        {
            return(i);            
        }
    }
    return  -1;
}
//-------------------------------------------------------------------------------
int     FindZoneInfoByMapName(char *mapname)
{
	int i;
    
    for(i=0; i<MAX_ZONE_PER_WORLD; i++)
    {
        if(strcmp(ZoneInfo[i].cMapName,mapname) ==0)
        {
            return(i);            
        }
    }
    return  -1;
}
//-------------------------------------------------------------------------------
int     FindZoneInfoByConnection(TPOS_CN *cn)
{
	int i;
    
    for(i=0; i<MAX_ZONE_PER_WORLD; i++)
    {
        if(ZoneInfo[i].dwSocket == cn->dwSocket)
        {
            return(i);            
        }
    }
    return  -1;
}
//-------------------------------------------------------------------------------
int FindQQOnliePlayerZoneIndexByQQID(ULONG	QQID)
{
	int zone_index, player_index, find_idx;

	if(QQID == 0)
		return	-1;

    find_idx = -1;
	for(zone_index = 0;zone_index < MAX_ZONE_PER_WORLD;zone_index++)
	{	
		for(player_index = 0;player_index < MAX_PLAYER_PER_ZONE;player_index++)
		{
			if(QQID == ZoneInfo[zone_index].QQOnlinePlayerList[player_index].ID)
			{
				find_idx = zone_index;
				break;
			}	
		}
	}
	return	find_idx;
}
//-------------------------------------------------------------------------------
int		FindQQOnliePlayerByQQID(int	zoneindex, ULONG QQID)
{
	int i, find_idx;

	if(QQID == 0)
		return	-1;

    find_idx = -1;
	for(i = 0;i < MAX_PLAYER_PER_ZONE;i++)
	{
		if(QQID == ZoneInfo[zoneindex].QQOnlinePlayerList[i].ID)
		{
			find_idx = i;
			break;
		}	
	}
	return	find_idx;
}
//-------------------------------------------------------------------------------
int		GetQQOnlinePlayerListByQQID(ULONG QQID, ULONG zoneindex)
{
	int i, find_idx;

	if(QQID == 0)
		return	-1;

    find_idx = -1;

	for(i=0;i<MAX_PLAYER_PER_ZONE;i++)
	{
		if(QQID == ZoneInfo[zoneindex].QQOnlinePlayerList[i].ID)
		{
			find_idx = i;
			break;
		}
	}

	return	find_idx;
}
//-------------------------------------------------------------------------------
void	ServerDoDoorLoginOK(TPOS_CN	*cn, TPOS_PACKET *packet)
{
	static TPOS_PACKET		send_packet;
	static TPOS_COMPACKET	send_compacket;
	TPOS_EVENT_NEWWORLDINFO	EventNewWorldInfo;	
	
	SaveMsgToLog("SYSTEM","DOOR_LOGIN_OK");
	send_packet.Header.dwType = NEW_WORLD_INFO;
	send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NEWWORLDINFO);
	
	EventNewWorldInfo.dwPort=WorldServerPort;
	strcpy(EventNewWorldInfo.cAddr,WorldServerAddr);
	strcpy(EventNewWorldInfo.cName,WorldServerName);
	EventNewWorldInfo.dwPlayerCount=dwOnlineAllWorldPlayer;

	memcpy(&send_packet.data.cBuf, &EventNewWorldInfo, sizeof(TPOS_EVENT_NEWWORLDINFO));

	CompressPacket(&send_packet, &send_compacket);
	
	QueuePacket(Door, &send_compacket, CONNECTED_SERVER_DOOR);	
}
//-------------------------------------------------------------------------------
void	ServerDoPlayerLogin(TPOS_CN *cn, TPOS_PACKET *packet)
{
	static TPOS_PACKET		send_packet;
	static TPOS_COMPACKET	send_compacket;
	TPOS_EVENT_LOGIN		EventLogin;	
	SLONG					dbRet;
	int						index;

	memcpy(&EventLogin, packet->data.cBuf, sizeof(TPOS_EVENT_LOGIN));
	SaveWorkToLog(EventLogin.cId, inet_ntoa(cn->Addr.sin_addr), "PLAYER_LOGIN");
	
	// 檢查密碼和ID
	dbRet = CheckPasswordOfAccountDB(EventLogin.cId, EventLogin.cPw);
	switch(dbRet)
	{
	case NETGE_DB_ERROR_ACCOUNT:
		send_packet.Header.dwType = WORLD_LOGIN_ERRORID;
		SaveWorkToLog(EventLogin.cId, inet_ntoa(cn->Addr.sin_addr), "PLAYER_LOGIN_ERRORID");
		break;
	case NETGE_DB_ERROR_PASSWORD:
		send_packet.Header.dwType = WORLD_LOGIN_ERRORPW;
		SaveWorkToLog(EventLogin.cId, inet_ntoa(cn->Addr.sin_addr), "PLAYER_LOGIN_ERRORPW");
		break;
	case NETGE_DB_SUCCESS:		
		LOCK_CONNECTION(0);
		index = FindConnectionByID(EventLogin.cId);
		UNLOCK_CONNECTION(0);		  
		if(index >= 0)
		{
			// 送出被重複登入的消息給玩家
			send_packet.Header.dwType = WORLD_LOGIN_REPEAT;			
			send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER);
			SendRepeatLoginedPlayer(index, &send_packet);
			SaveWorkToLog(EventLogin.cId, inet_ntoa(cn->Addr.sin_addr), "PLAYER_LOGIN_REPEAT");			

			// 重複登入將舊的去掉			
			dwOnlineLoginer--;
			dwOnlineCounter--;
			LOCK_CONNECTION(0);
			CloseOneConnection(&Pos_Cn[index]);			
			UNLOCK_CONNECTION(0);
			RefreshAllWorldPlayer();					  				
		}	
		LOCK_CONNECTION(0);
		index = FindCurrentConnection(cn->dwSocket);		
		if(index >= 0)
		{			
			strcpy(Pos_Cn[index].User.cId, EventLogin.cId);
			strcpy(Pos_Cn[index].User.cPw, EventLogin.cPw);
			SaveWorkToLog(EventLogin.cId, inet_ntoa(cn->Addr.sin_addr), "PLAYER_LOGIN_OK");
			send_packet.Header.dwType = WORLD_LOGIN_OK;				
		}
		UNLOCK_CONNECTION(0);		  
		break;
	} 		
	send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER);
	
	CompressPacket(&send_packet, &send_compacket);
	
	LOCK_CONNECTION(0);
	QueuePacket(cn, &send_compacket, CONNECTED_SERVER_WORLD);	
	UNLOCK_CONNECTION(0);
}
//-------------------------------------------------------------------------------
void	ServerDoRequestCharacterDefault(TPOS_CN *cn, TPOS_PACKET *packet)
{
	static TPOS_PACKET					send_packet;
	static TPOS_COMPACKET				send_compacket;
	TPOS_EVENT_GETCHARACTERDEFAULT		EventGetCharacterDefault;	
	TPOS_EVENT_REQUESTCHARACTERDEFAULT	EventRequestCharacterDefault;	
	int									index;

	memcpy(&EventRequestCharacterDefault, packet->data.cBuf, sizeof(TPOS_EVENT_REQUESTCHARACTERDEFAULT));
	index = EventRequestCharacterDefault.iIndex;
	SaveWorkToLog(cn->User.cId, inet_ntoa(cn->Addr.sin_addr), "REQUEST_CHARACTER_DEFAULT");
	
	EventGetCharacterDefault.cSex = CharacterDefault[index].Sex;
	EventGetCharacterDefault.cCareer = CharacterDefault[index].Career;
	EventGetCharacterDefault.iStr = CharacterDefault[index].Str;
	EventGetCharacterDefault.iIns = CharacterDefault[index].Ins;
	EventGetCharacterDefault.iWis = CharacterDefault[index].Wis;
	EventGetCharacterDefault.iLucky = CharacterDefault[index].Lucky;
	EventGetCharacterDefault.iHp = CharacterDefault[index].Hp;
	EventGetCharacterDefault.iMp = CharacterDefault[index].Mp;
	EventGetCharacterDefault.slFileIndex = CharacterDefault[index].FileIndex;
	
	send_packet.Header.dwType = GET_CHARACTER_DEFAULT;
	send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_GETCHARACTERDEFAULT);
	memcpy(&send_packet.data.cBuf, &EventGetCharacterDefault, sizeof(TPOS_EVENT_GETCHARACTERDEFAULT));

	CompressPacket(&send_packet, &send_compacket);

	LOCK_CONNECTION(0);
	QueuePacket(cn, &send_compacket, CONNECTED_SERVER_WORLD);
	UNLOCK_CONNECTION(0);	
}
//-------------------------------------------------------------------------------
void	ServerDoCreateCharacterCheck(TPOS_CN *cn, TPOS_PACKET *packet)
{
	static TPOS_PACKET					send_packet;
	static TPOS_COMPACKET				send_compacket;
	TPOS_EVENT_CREATECHARACTERCHECK		EventCreateCharacterCheck;	

	memcpy(&EventCreateCharacterCheck, packet->data.cBuf, sizeof(TPOS_EVENT_CREATECHARACTERCHECK));
		
	if(CheckMainNameOfCharacterDB(EventCreateCharacterCheck.cMainName) == NETGE_DB_MAINNAME_AVAILABLE)
	{
		send_packet.Header.dwType = CREATE_CHARACTER_CHECK_OK;				
	}else
	{
		send_packet.Header.dwType = CREATE_CHARACTER_NAMEUSED;		
	}
	send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER);

	CompressPacket(&send_packet, &send_compacket);

	LOCK_CONNECTION(0);
	QueuePacket(cn, &send_compacket, CONNECTED_SERVER_WORLD);		
	UNLOCK_CONNECTION(0);
}
//-------------------------------------------------------------------------------
void	ServerDoCreateCharacterFinal(TPOS_CN *cn, TPOS_PACKET *packet)
{
	static TPOS_PACKET					send_packet;
	static TPOS_COMPACKET				send_compacket;
	TPOS_EVENT_CREATECHARACTERFINAL		EventCreateCharacterFinal;	
	TPOS_DB_CHARACTER					DbCharacter;	
	TPOS_DB_QQ							DbQQ;
	TPOS_DB_BANK						DbBank;
	int									Index;	
	int									i;
	SLONG								db_ret;
	
	memcpy(&EventCreateCharacterFinal, packet->data.cBuf, sizeof(TPOS_EVENT_CREATECHARACTERFINAL));
	Index = EventCreateCharacterFinal.dwCharacterDefaultIndex;
	ConvertEventCharacterFinalToDbCharacter(&EventCreateCharacterFinal, &DbCharacter);	
	// 初始角色物品資料庫
	InitItemDBWhenCreateCharacter(DbCharacter.MainName);	
	// 初始角色任務資料庫
	InitQuestDBWhenCreateCharacter(DbCharacter.MainName);
	// 初始角色銀行資料庫
	memset(&DbBank, 0x0, sizeof(TPOS_DB_BANK));
	strcpy(DbBank.MainName, DbCharacter.MainName);	
	AppendRecordToBankDB(&DbBank);

	strcpy(DbCharacter.ID, cn->User.cId);
	for(i = 0;i < MAX_COUNTRYSEL_PER_WORLD;i++)
	{
		if(DbCharacter.Country == CountryCity[i].cCountry)
		{
			strcpy(DbCharacter.ZoneName, CountryCity[i].cCityName);
			DbCharacter.X = CountryCity[i].lDefaultX;
			DbCharacter.Y = CountryCity[i].lDefaultY;
			DbCharacter.Z = CountryCity[i].lDefaultZ;
			break;
		}
	}
	DbCharacter.MainNameColor = COLOR_BLUE;
	DbCharacter.Career = CharacterDefault[Index].Career;
	DbCharacter.Sex = CharacterDefault[Index].Sex;
	DbCharacter.InitStr = CharacterDefault[Index].Str;
	DbCharacter.InitIns = CharacterDefault[Index].Ins;
	DbCharacter.InitWit = CharacterDefault[Index].Wis;
	DbCharacter.InitLucky = CharacterDefault[Index].Lucky;	
	DbCharacter.LandFileIndex = CharacterDefault[Index].FileIndex;
	DbCharacter.SeaFileIndex = 0;
	DbCharacter.FinalAttack = CharacterDefault[Index].Attack;
	DbCharacter.FinalDefence = CharacterDefault[Index].Defence;	
	DbCharacter.SkillNo[0] = CharacterDefault[Index].Skill[0];
	DbCharacter.SkillNo[1] = CharacterDefault[Index].Skill[1];
	DbCharacter.SkillNo[2] = CharacterDefault[Index].Skill[2];
	DbCharacter.SkillNo[3] = CharacterDefault[Index].Skill[3];
	DbCharacter.SkillNo[4] = CharacterDefault[Index].Skill[4];
	DbCharacter.SkillNo[5] = CharacterDefault[Index].Skill[5];
	DbCharacter.SkillNo[6] = CharacterDefault[Index].Skill[6];	
	DbCharacter.SkillNo[7] = CharacterDefault[Index].Skill[7];	
	DbCharacter.SkillNo[8] = CharacterDefault[Index].Skill[8];	
	DbCharacter.SkillNo[9] = CharacterDefault[Index].Skill[9];				
	DbCharacter.SkillNo[10] = CharacterDefault[Index].Skill[10];				
	//============================
	// Hawke  [1/29/2003]
	// 增加為了測試物品 ==========
	TPOS_DB_ITEM	Item;
	Item.BaseID = 1504;
	Item.Hp = 100;
	strcpy(Item.MainName, DbCharacter.MainName);
	Item.Index = CII_EQUIP_WEAPON;
	UpdateRecordOfItemDBByMainNameAndIndex(&Item);
	/*
	DbCharacter.BagItem[0] = 1;
	DbCharacter.BagItem[1] = 17;
	DbCharacter.BagItem[2] = 18;
	DbCharacter.BagItem[3] = 19;
	DbCharacter.BagItem[4] = 20;
	DbCharacter.BagItem[5] = 21;
	DbCharacter.BagItem[6] = 22;
	DbCharacter.BagItem[7] = 23;
	DbCharacter.BagItem[8] = 24;
	DbCharacter.BagItem[9] = 25;
	DbCharacter.BagItem[10] = 26;
	DbCharacter.BagItem[11] = 27;
	DbCharacter.BagItem[12] = 28;
	DbCharacter.BagItem[13] = 29;
	DbCharacter.BagItem[14] = 30;
	DbCharacter.BagItem[15] = 31;
	DbCharacter.BagItem[16] = 32;
	DbCharacter.BagItem[17] = 33;
	DbCharacter.BagItem[18] = 34;
	DbCharacter.BagItem[19] = 35;
	DbCharacter.BagItem[20] = 36;
	DbCharacter.BagItem[21] = 37;
	DbCharacter.BagItem[22] = 38;
	DbCharacter.BagItem[23] = 39;
	DbCharacter.BagItem[24] = 40;
	DbCharacter.BagItem[25] = 41;
	DbCharacter.BagItem[26] = 42;	
	*/
	for(i = 0;i<MAX_CHARACTER_SASH_ITEMS;i++)
	{
		DbCharacter.SashItem[i] = 0;
	}
	for(i = 0;i<MAX_CHARACTER_TRANS_ITEMS;i++)
	{
		DbCharacter.TransItem[i] = 0;
	}
	DbCharacter.TreasureItem = 0;
	//============================
	DbCharacter.Hp = CharacterDefault[Index].Hp;
	DbCharacter.MaxHp = CharacterDefault[Index].Hp;
	DbCharacter.Mp = CharacterDefault[Index].Mp;
	DbCharacter.MaxMp = CharacterDefault[Index].Mp;
	DbCharacter.Sex = CharacterDefault[Index].Sex;
	DbCharacter.SightRange = (UHINT)CharacterDefault[Index].Sight;
	DbCharacter.Mspeed = CharacterDefault[Index].Mspeed;	
	for(i = 11;i<MAX_CHARACTER_SKILLS;i++)
	{
		DbCharacter.SkillNo[i] = -1;
	}
	DbCharacter.LandLeftSkill = MAGIC_NO_WALK;
	DbCharacter.LandRightSkill = MAGIC_NO_WALK;
	DbCharacter.SeaLeftSkill = MAGIC_NO_SEAWALK;
	DbCharacter.SeaRightSkill = MAGIC_NO_SEAWALK;
	for(i = 0;i<MAX_CHARACTER_FN_SKILLS;i++)
	{
		DbCharacter.LandFnSkillNo[i] = -1;
		DbCharacter.SeaFnSkillNo[i] = -1;		
		DbCharacter.LandFnSkillHand[i] = 0;
		DbCharacter.SeaFnSkillHand[i] = 0;
	}
	DbCharacter.DoingKind = DOING_KIND_IDLE;	
	DbCharacter.StopRadius = 10;
	DbCharacter.NameColorTicks = 0;
	DbCharacter.TotalOnlineTicks = 0;

	//remark for debug worldserver 2002-12-29 hawke
	
	dwQQIDCounter++;
	SaveQQIDCounter(dwQQIDCounter);
	DbCharacter.QQID = dwQQIDCounter;
	
	memset(&DbQQ, 0x0, sizeof(TPOS_DB_QQ));		
	DbQQ.ID = dwQQIDCounter;		
	strcpy(DbQQ.AccountName,DbCharacter.ID);
	strcpy(DbQQ.CharacterName,DbCharacter.MainName);
	strcpy(DbQQ.WorldServerName,WorldServerName);		
	strcpy(DbQQ.NickName,DbCharacter.NickName);
	DbQQ.Level = DbCharacter.Level;
	DbQQ.State = 0;
	switch(DbCharacter.Career)
	{
	case 'A':
		if(DbCharacter.Sex == 'A')
		{
			DbQQ.Career = 1;
		}else
		{
			DbQQ.Career = 2;
		}
		break;
	case 'B':
		if(DbCharacter.Sex == 'A')
		{
			DbQQ.Career = 3;
		}else
		{
			DbQQ.Career = 4;
		}
		break;
	case 'C':
		if(DbCharacter.Sex == 'A')
		{
			DbQQ.Career = 5;
		}else
		{
			DbQQ.Career = 6;
		}
		break;
	case 'D':
		if(DbCharacter.Sex == 'A')
		{
			DbQQ.Career = 7;
		}else
		{
			DbQQ.Career = 8;
		}
		break;
	case 'E':
		if(DbCharacter.Sex == 'A')
		{
			DbQQ.Career = 9;
		}else
		{
			DbQQ.Career = 10;
		}
		break;
	case 'F':
		if(DbCharacter.Sex == 'A')
		{
			DbQQ.Career = 11;
		}else
		{
			DbQQ.Career = 12;
		}
		break;
	case 'G':
		if(DbCharacter.Sex == 'A')
		{
			DbQQ.Career = 13;
		}else
		{
			DbQQ.Career = 14;
		}
		break;
	}
	DbQQ.Country = DbCharacter.Country;					
	db_ret = AppendRecordToQQDB(&DbQQ);		
	if(db_ret == TRUE)
	{	
		if(AppendRecordToCharacterDB(&DbCharacter) == TRUE)
		{
			send_packet.Header.dwType = CREATE_CHARACTER_FINAL_OK;		
		}else
		{
			send_packet.Header.dwType = CREATE_CHARACTER_FINAL_FAIL;
		}
	}else
	{
		send_packet.Header.dwType = CREATE_CHARACTER_FINAL_FAIL;
	}
	send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER);

	CompressPacket(&send_packet, &send_compacket);

	LOCK_CONNECTION(0);
	QueuePacket(cn, &send_compacket, CONNECTED_SERVER_WORLD);		
	UNLOCK_CONNECTION(0);		
}
//-------------------------------------------------------------------------------
void	ServerDoDeleteCharacter(TPOS_CN *cn, TPOS_PACKET *packet)
{
	BOOL						odbcRet=FALSE;
	static TPOS_PACKET			send_packet;
	static TPOS_COMPACKET		send_compacket;
	TPOS_EVENT_DELETECHARACTER	EventDeleteCharacter;
	
	memcpy(&EventDeleteCharacter, packet->data.cBuf, sizeof(TPOS_EVENT_DELETECHARACTER));

	DeleteRecordFromBankDB(EventDeleteCharacter.cMainName);
	DeleteRecordFromItemDBByMainName(EventDeleteCharacter.cMainName);
	DeleteRecordFromQuestDBByMainName(EventDeleteCharacter.cMainName);
	odbcRet = DeleteRecordFromCharacterDB(cn->User.cId, EventDeleteCharacter.cMainName);
	if(odbcRet == TRUE)
	{
		send_packet.Header.dwType = DELETE_CHARACTER_OK;
		send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER);

		CompressPacket(&send_packet, &send_compacket);

		SaveWorkToLog(EventDeleteCharacter.cMainName,
				      inet_ntoa(cn->Addr.sin_addr),
					  "DELETE_CHARACTER_OK");

		LOCK_CONNECTION(0);
		QueuePacket(cn, &send_compacket, CONNECTED_SERVER_WORLD);
		UNLOCK_CONNECTION(0);
	}
}
//-------------------------------------------------------------------------------
void	ServerDoRequestCharacterInfo(TPOS_CN *cn, TPOS_PACKET *packet)
{
	static TPOS_PACKET				send_packet;
	static TPOS_COMPACKET			send_compacket;
	TPOS_EVENT_REQUESTCHARACTERINFO	EventRequestCharacterInfo;	
	TPOS_EVENT_GETCHARACTERINFO		EventGetCharacterInfo[4];
	static TPOS_DB_CHARACTER		DbCharacter[4];
	int								tempindex, i;
	char							tempid[32];
	
	memcpy(&EventRequestCharacterInfo, packet->data.cBuf, sizeof(TPOS_EVENT_REQUESTCHARACTERINFO));

	strcpy(tempid, cn->User.cId);
	
	for(i = 0;i < 4;i++)
	{		
		memset(&DbCharacter[i], 0x0, sizeof(TPOS_DB_CHARACTER));
		memset(&EventGetCharacterInfo[i], 0x0, sizeof(TPOS_EVENT_GETCHARACTERINFO));
		tempindex = GetRecordFromCharacterDBByAccountAndIndex(&DbCharacter[i], tempid, i);			
		ConvertDbCharacterToEventGetCharacterInfo(&DbCharacter[i], &EventGetCharacterInfo[i]);
	}	
	send_packet.Header.dwType = GET_CHARACTER_INFO;
	send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + (sizeof(TPOS_EVENT_GETCHARACTERINFO) * 4);	

	memcpy(&send_packet.data.cBuf, EventGetCharacterInfo, (sizeof(TPOS_EVENT_GETCHARACTERINFO) * 4));

	CompressPacket(&send_packet, &send_compacket);

	LOCK_CONNECTION(0);
	QueuePacket(cn, &send_compacket, CONNECTED_SERVER_WORLD);
	UNLOCK_CONNECTION(0);
}
//-------------------------------------------------------------------------------
void	ServerDoCharacterSelected(TPOS_CN *cn, TPOS_PACKET *packet)
{
	TPOS_DB_QQ						DbQQ;
	TPOS_DB_QQ						FindDbQQ;
	TPOS_EVENT_CHARACTERSELECTED	EventCharacterSelected;	
	TPOS_EVENT_QQGETMYDATA			EventQQGetMyData;	
	static TPOS_PACKET				send_packet;
	static TPOS_EVENT_QQGETFRIENDLIST		EventQQGetFriendList;
	static TPOS_EVENT_QQGETGUILDFRIENDLIST	EventQQGetGuildFriendList;
	int									i;
	SLONG								Ret;

	memcpy(&EventCharacterSelected, packet->data.cBuf, sizeof(TPOS_EVENT_CHARACTERSELECTED));
	
	memset(&DbQQ, 0x0, sizeof(TPOS_DB_QQ));
	GetRecordFromQQDBByID(&DbQQ, EventCharacterSelected.QQID);	

	// 將 QQ 資料送給該玩家
	send_packet.Header.dwType = QQ_GET_MYDATA;
	send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_QQGETMYDATA);

	EventQQGetMyData.ID = DbQQ.ID;
	strcpy(EventQQGetMyData.CharacterName, DbQQ.CharacterName);
	strcpy(EventQQGetMyData.GuildName, DbQQ.GuildName);
	EventQQGetMyData.Config = DbQQ.Config;
	EventQQGetMyData.State = DbQQ.State;	

	memcpy(send_packet.data.cBuf, &EventQQGetMyData, sizeof(TPOS_EVENT_QQGETMYDATA));
	
	ServerSendPacketToOne(cn, &send_packet);

	// 處理好友列表
	memset(&EventQQGetFriendList, 0x0, sizeof(TPOS_EVENT_QQGETFRIENDLIST));
	for(i = 0;i < 128;i++)
	{
		if(DbQQ.Friend[i].ID != 0)
		{
			memset(&FindDbQQ, 0x0, sizeof(TPOS_DB_QQ));
			Ret = GetRecordFromQQDBByID(&FindDbQQ, DbQQ.Friend[i].ID);
			if(Ret == TRUE)
			{			
				EventQQGetFriendList.FriendList[i].ID = FindDbQQ.ID;
				EventQQGetFriendList.FriendList[i].Career = FindDbQQ.Career;			
				EventQQGetFriendList.FriendList[i].Relation = DbQQ.Friend[i].Relation;
				EventQQGetFriendList.FriendList[i].State = FindDbQQ.State;
				strcpy(EventQQGetFriendList.FriendList[i].MainName, FindDbQQ.CharacterName);
			}
		}
	}
	EventQQGetFriendList.BookMark = 1;		
	send_packet.Header.dwType = QQ_GET_FRIEND_LIST;
	send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_QQGETFRIENDLIST);
	memcpy(send_packet.data.cBuf, &EventQQGetFriendList, sizeof(TPOS_EVENT_QQGETFRIENDLIST));
	ServerSendPacketToOne(cn, &send_packet);

	memset(&EventQQGetFriendList, 0x0, sizeof(TPOS_EVENT_QQGETFRIENDLIST));
	for(i = 128;i < 256;i++)
	{
		if(DbQQ.Friend[i].ID != 0)
		{
			memset(&FindDbQQ, 0x0, sizeof(TPOS_DB_QQ));
			Ret = GetRecordFromQQDBByID(&FindDbQQ, DbQQ.Friend[i].ID);
			if(Ret == TRUE)
			{			
				EventQQGetFriendList.FriendList[i-128].ID = FindDbQQ.ID;
				EventQQGetFriendList.FriendList[i-128].Career = FindDbQQ.Career;			
				EventQQGetFriendList.FriendList[i-128].Relation = DbQQ.Friend[i].Relation;
				EventQQGetFriendList.FriendList[i-128].State = FindDbQQ.State;
				strcpy(EventQQGetFriendList.FriendList[i-128].MainName, FindDbQQ.CharacterName);
			}
		}
	}
	EventQQGetFriendList.BookMark = 2;		
	send_packet.Header.dwType = QQ_GET_FRIEND_LIST;
	send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_QQGETFRIENDLIST);
	memcpy(send_packet.data.cBuf, &EventQQGetFriendList, sizeof(TPOS_EVENT_QQGETFRIENDLIST));
	ServerSendPacketToOne(cn, &send_packet);

	// 處理工會好友列表
	memset(&EventQQGetGuildFriendList, 0x0, sizeof(TPOS_EVENT_QQGETGUILDFRIENDLIST));
	for(i = 0;i < 128;i++)
	{
		if(DbQQ.GuildFriend[i].ID != 0)
		{
			memset(&FindDbQQ, 0x0, sizeof(TPOS_DB_QQ));
			GetRecordFromQQDBByID(&FindDbQQ, DbQQ.GuildFriend[i].ID);
			EventQQGetGuildFriendList.GuildFriendList[i].ID = FindDbQQ.ID;
			EventQQGetGuildFriendList.GuildFriendList[i].Career = FindDbQQ.Career;			
			EventQQGetGuildFriendList.GuildFriendList[i].Relation = DbQQ.GuildFriend[i].Relation;
			EventQQGetGuildFriendList.GuildFriendList[i].State = FindDbQQ.State;
			strcpy(EventQQGetGuildFriendList.GuildFriendList[i].MainName, FindDbQQ.CharacterName);
		}
	}
	send_packet.Header.dwType = QQ_GET_GUILD_FRIEND_LIST;
	send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_QQGETGUILDFRIENDLIST);
	memcpy(send_packet.data.cBuf, &EventQQGetGuildFriendList, sizeof(TPOS_EVENT_QQGETGUILDFRIENDLIST));
	ServerSendPacketToOne(cn, &send_packet);	
}
//-------------------------------------------------------------------------------
void	ServerDoQQPlayerLogin(TPOS_CN *cn, TPOS_PACKET *packet)
{	
	TPOS_EVENT_QQPLAYERLOGIN	EventQQPlayerLogin;
	TPOS_EVENT_QQGETOTHERSTATE	EventQQGetOtherState;
	static TPOS_PACKET			send_packet;
	TPOS_DB_QQ					DbQQ;
	int							i, j, x;
	char						zonename[32];
	
	memcpy(&EventQQPlayerLogin, packet->data.cBuf, sizeof(TPOS_EVENT_QQPLAYERLOGIN));

	memset(&DbQQ, 0x0, sizeof(TPOS_DB_QQ));
	GetRecordFromQQDBByID(&DbQQ, EventQQPlayerLogin.QQID);

	LOCK_ZONEINFO(0);
	i = FindZoneInfoByConnection(cn);
	if(i >= 0)
	{
		j = FindUsableZoneQQOnlinePlayerList(i);
		if(j != -1)
		{
			ZoneInfo[i].QQOnlinePlayerList[j].ID = DbQQ.ID;
			strcpy(ZoneInfo[i].QQOnlinePlayerList[j].MainName, DbQQ.CharacterName);
			strcpy(ZoneInfo[i].QQOnlinePlayerList[j].GuildName, DbQQ.GuildName);
			ZoneInfo[i].QQOnlinePlayerList[j].State = DbQQ.State;
			ZoneInfo[i].QQOnlinePlayerList[j].Level = DbQQ.Level;
			memcpy(ZoneInfo[i].QQOnlinePlayerList[j].Friend, DbQQ.Friend, sizeof(TPOS_QQ_FRIEND_DB)*256);
			memcpy(ZoneInfo[i].QQOnlinePlayerList[j].GuildFriend, DbQQ.GuildFriend, sizeof(TPOS_QQ_FRIEND_DB)*128);

			send_packet.Header.dwType = QQ_LOGIN_OK;
			send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER);

			ServerSendPacketToOne(cn, &send_packet);
		}
	}
	UNLOCK_ZONEINFO(0);		

	DbQQ.State = 1; // 設定上線狀態  將來要視他的 Config 做設定
	UpdateRecordOfQQDB(&DbQQ);	
	//發給所有ZoneServer,該 QQ 玩家上線
	send_packet.Header.dwType = QQ_GET_OTHERSTATE;
	send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_QQGETOTHERSTATE);

	EventQQGetOtherState.ID = EventQQPlayerLogin.QQID;				  
	EventQQGetOtherState.State = 1;
	memcpy(send_packet.data.cBuf, &EventQQGetOtherState, sizeof(TPOS_EVENT_QQGETOTHERSTATE));
	
	for(i = 0; i < MAX_ZONE_PER_WORLD;i++)
	{
		LOCK_ZONEINFO(0);
		strcpy(zonename, ZoneInfo[i].cName);
		UNLOCK_ZONEINFO(0);	
		if(strcmp(zonename, "") == 0)break;
		x = FindConnectionByZoneName(zonename);		
		if(x != -1)
		{
			ServerSendPacketToOne(&Pos_Cn[x], &send_packet);
		}		
	}
}
//-------------------------------------------------------------------------------
void	ServerDoQQPlayerLogout(TPOS_CN *cn, TPOS_PACKET *packet)
{
	TPOS_EVENT_QQPLAYERLOGOUT	EventQQPlayerLogout;
	TPOS_EVENT_QQGETOTHERSTATE	EventQQGetOtherState;
	static TPOS_PACKET			send_packet;
	TPOS_DB_QQ					DbQQ;
	int							i, j, x;
	char						zonename[32];

	memcpy(&EventQQPlayerLogout, packet->data.cBuf, sizeof(TPOS_EVENT_QQPLAYERLOGOUT));

	GetRecordFromQQDBByID(&DbQQ,EventQQPlayerLogout.QQID);
	DbQQ.State = 0;
	UpdateRecordOfQQDB(&DbQQ);
	LOCK_ZONEINFO(0);
	i = FindZoneInfoByConnection(cn);
	UNLOCK_ZONEINFO(0);
	if(i >= 0)
	{
		LOCK_ZONEINFO(0);
		j = FindQQOnliePlayerByQQID(i, EventQQPlayerLogout.QQID);
		if(j != -1)
		{			
			memset(&ZoneInfo[i].QQOnlinePlayerList[j], 0x0, sizeof(TPOS_QQ_ONLINE_PLAYER_LIST));							
		}
		UNLOCK_ZONEINFO(0);
	}
	
	//發給所有ZoneServer,該 QQ 玩家下線
	send_packet.Header.dwType = QQ_GET_OTHERSTATE;
	send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_QQGETOTHERSTATE);

	EventQQGetOtherState.ID = EventQQPlayerLogout.QQID;				  
	EventQQGetOtherState.State = 0 ;
	memcpy(send_packet.data.cBuf, &EventQQGetOtherState, sizeof(TPOS_EVENT_QQGETOTHERSTATE));
	
	for(i = 0; i < MAX_ZONE_PER_WORLD;i++)
	{
		LOCK_ZONEINFO(0);
		strcpy(zonename, ZoneInfo[i].cName);
		UNLOCK_ZONEINFO(0);	
		if(strcmp(zonename, "") == 0)break;
		x = FindConnectionByZoneName(zonename);		
		if(x != -1)
		{
			ServerSendPacketToOne(&Pos_Cn[x], &send_packet);
		}		
	}	
}
//-------------------------------------------------------------------------------
void	ServerDoQQRequestFriendList(TPOS_CN *cn, TPOS_PACKET *packet)
{
}
//-------------------------------------------------------------------------------
void	ServerDoQQRequestGuildFriendList(TPOS_CN *cn, TPOS_PACKET *packet)
{
}
//-------------------------------------------------------------------------------
void	ServerDoQQSetMyState(TPOS_CN *cn, TPOS_PACKET *packet)
{
	TPOS_EVENT_QQREQUESTSETMYSTATE	EventQQSetMyState;
	TPOS_EVENT_QQGETOTHERSTATE		EventQQGetOtherState;
	static TPOS_PACKET				send_packet;
	int								zoneindex, i, x;
	char							zonename[32];

	memcpy(&EventQQSetMyState, packet->data.cBuf, sizeof(TPOS_EVENT_QQREQUESTSETMYSTATE));

	LOCK_ZONEINFO(0);
	zoneindex = FindZoneInfoByConnection(cn);
	for(i = 0;i < MAX_PLAYER_PER_ZONE;i++)
	{
		if(ZoneInfo[zoneindex].QQOnlinePlayerList[i].ID == EventQQSetMyState.ID)
		{
			ZoneInfo[zoneindex].QQOnlinePlayerList[i].State = EventQQSetMyState.State;
			break;
		}
	}
	UNLOCK_ZONEINFO(0);

	send_packet.Header.dwType = QQ_GET_OTHERSTATE;
	send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_QQGETOTHERSTATE);

	EventQQGetOtherState.ID = EventQQSetMyState.ID;				  
	EventQQGetOtherState.State = EventQQSetMyState.State;;
	memcpy(send_packet.data.cBuf, &EventQQGetOtherState, sizeof(TPOS_EVENT_QQGETOTHERSTATE));
	
	for(i = 0; i < MAX_ZONE_PER_WORLD;i++)
	{
		LOCK_ZONEINFO(0);
		strcpy(zonename, ZoneInfo[i].cName);
		UNLOCK_ZONEINFO(0);	
		if(strcmp(zonename, "") == 0)break;
		x = FindConnectionByZoneName(zonename);		
		if(x != -1)
		{
			ServerSendPacketToOne(&Pos_Cn[x], &send_packet);
		}		
	}
}
//-------------------------------------------------------------------------------
void	ServerDoQQRequestQueryAddList(TPOS_CN *cn, TPOS_PACKET *packet)
{
	//TPOS_EVENT_QQREQUESTQUERYADDLIST	EventQQRequestQueryAddList;
	//TPOS_PACKET							send_packet;	
}
//-------------------------------------------------------------------------------
void	ServerDoQQRequestQueryOnlineAddList(TPOS_CN *cn, TPOS_PACKET *packet)
{
	TPOS_EVENT_QQREQUESTQUERYONLINELIST	EventQQRequestQueryOnLineList;
	TPOS_EVENT_QQGETQUERYONLINELIST		EventQQGetQueryOnLineList;
	static TPOS_PACKET					send_packet;
	ULONG								bookmark;	
	ULONG								zoneindex;
	char								zonename[32];
	SLONG								x, i;
	ULONG								return_list_count;
	bool								no_more_data = TRUE;
	
	memcpy(&EventQQRequestQueryOnLineList, packet->data.cBuf, sizeof(TPOS_EVENT_QQREQUESTQUERYONLINELIST));

	return_list_count = 0;
	bookmark = EventQQRequestQueryOnLineList.BookMark;	
	zoneindex = EventQQRequestQueryOnLineList.ZoneIndex;
	LOCK_ZONEINFO(0);
	strcpy(zonename, ZoneInfo[zoneindex].cName);
	UNLOCK_ZONEINFO(0);		

	memset(EventQQGetQueryOnLineList.QQAddList, 0x0, sizeof(TPOS_QQ_ADDLIST)*100);

	LOCK_ZONEINFO(0);
	for(i = zoneindex;i < MAX_ZONE_PER_WORLD;i++)
	{	
		if(strcmp(ZoneInfo[i].cName,"") != 0)
		{			
			for(x = bookmark;x < MAX_PLAYER_PER_ZONE;x++)
			{		
				if(ZoneInfo[i].QQOnlinePlayerList[x].ID != 0)
				{			
					EventQQGetQueryOnLineList.QQAddList[return_list_count].ID = 
						ZoneInfo[i].QQOnlinePlayerList[x].ID;
					strcpy(EventQQGetQueryOnLineList.QQAddList[return_list_count].MainName,
						ZoneInfo[i].QQOnlinePlayerList[x].MainName);
					strcpy(EventQQGetQueryOnLineList.QQAddList[return_list_count].GuildName,
						ZoneInfo[i].QQOnlinePlayerList[x].GuildName);
					EventQQGetQueryOnLineList.QQAddList[return_list_count].Level = 
						ZoneInfo[i].QQOnlinePlayerList[x].Level;
					return_list_count++;
					if(return_list_count == 100)
					{
						EventQQGetQueryOnLineList.BookMark = x;
						EventQQGetQueryOnLineList.ZoneIndex = i;
						EventQQGetQueryOnLineList.RequestID = EventQQRequestQueryOnLineList.RequestID;						
						no_more_data = FALSE;
						break;
					}
				}
			}
		}
	}	
	UNLOCK_ZONEINFO(0);

	if(no_more_data == FALSE)
	{
		send_packet.Header.dwType = QQ_GET_QUERY_ADD_LIST;		
	}else
	{
		EventQQGetQueryOnLineList.BookMark = x;
		EventQQGetQueryOnLineList.ZoneIndex = i;
		EventQQGetQueryOnLineList.RequestID = EventQQRequestQueryOnLineList.RequestID;
		send_packet.Header.dwType = QQ_GET_QUERY_ADD_LIST_END;
	}
	send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_QQGETQUERYONLINELIST);
		
	memcpy(send_packet.data.cBuf, &EventQQGetQueryOnLineList, sizeof(TPOS_EVENT_QQGETQUERYONLINELIST));

	ServerSendPacketToOne(cn, &send_packet);
}
//-------------------------------------------------------------------------------
void	ServerDoQQRequestQuerySomeone(TPOS_CN *cn, TPOS_PACKET *packet)
{
	static	TPOS_PACKET					send_packet;
	TPOS_EVENT_QQREQUESTQUERYSOMEONE	EventQQRequestQuerySomeone;
	TPOS_EVENT_QQGETQUERYSOMEONE		EventQQGetQuerySomeone;
	//TPOS_DB_QQ						DbQQ;
	TPOS_DB_CHARACTER					DbCharacter;	
	int									i;	
	ULONG								tagetid;
	//char								mainname[32];
	char								sex;	
	
	memcpy(&EventQQRequestQuerySomeone, packet->data.cBuf, sizeof(TPOS_EVENT_QQREQUESTQUERYSOMEONE));

	tagetid = EventQQRequestQuerySomeone.TargetID;
	memset(&EventQQGetQuerySomeone, 0x0, sizeof(TPOS_EVENT_QQGETQUERYSOMEONE));
	//memset(&DbQQ, 0x0, sizeof(TPOS_DB_QQ));
	//i = GetRecordFromQQDBByID(&DbQQ, tagetid);	
	i = GetRecordFromCharacterDBByQQID(&DbCharacter, tagetid);
	if(i == TRUE)
	{
		send_packet.Header.dwType = QQ_GET_QUERY_SOMEONE;
		send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_QQGETQUERYSOMEONE);
	
		/*
		EventQQGetQuerySomeone.ID = DbQQ.ID;			
		EventQQGetQuerySomeone.RequestID = EventQQRequestQuerySomeone.RequestID;
		strcpy(EventQQGetQuerySomeone.MainName,DbQQ.CharacterName);
		strcpy(EventQQGetQuerySomeone.NickName,DbQQ.NickName);
		strcpy(EventQQGetQuerySomeone.GuildName,DbQQ.GuildName);
		EventQQGetQuerySomeone.Level = DbQQ.Level;
		EventQQGetQuerySomeone.Country = DbQQ.Country;
		EventQQGetQuerySomeone.Career = DbQQ.Career;

		strcpy(mainname, DbQQ.CharacterName);
		
		GetRecordFromCharacterDBByMainName(&DbCharacter, mainname);
		*/
		// Remark for debug		
		
		EventQQGetQuerySomeone.ID = DbCharacter.QQID;			
		EventQQGetQuerySomeone.RequestID = EventQQRequestQuerySomeone.RequestID;
		strcpy(EventQQGetQuerySomeone.MainName, DbCharacter.MainName);
		strcpy(EventQQGetQuerySomeone.NickName, DbCharacter.NickName);
		strcpy(EventQQGetQuerySomeone.GuildName, DbCharacter.Guild);
		EventQQGetQuerySomeone.Level = DbCharacter.Level;
		EventQQGetQuerySomeone.Country = DbCharacter.Country;
		sex = DbCharacter.Sex;		
		switch(DbCharacter.Career)
		{
		case 'A':
			if(DbCharacter.Sex == 'A')
			{
				EventQQGetQuerySomeone.Career = 1;
			}else
			{
				EventQQGetQuerySomeone.Career = 2;
			}
			break;
		case 'B':
			if(DbCharacter.Sex == 'A')
			{
				EventQQGetQuerySomeone.Career = 3;
			}else
			{
				EventQQGetQuerySomeone.Career = 4;
			}
			break;
		case 'C':
			if(DbCharacter.Sex == 'A')
			{
				EventQQGetQuerySomeone.Career = 5;
			}else
			{
				EventQQGetQuerySomeone.Career = 6;
			}
			break;
		case 'D':
			if(DbCharacter.Sex == 'A')
			{
				EventQQGetQuerySomeone.Career = 7;
			}else
			{
				EventQQGetQuerySomeone.Career = 8;
			}
			break;
		case 'E':
			if(DbCharacter.Sex == 'A')
			{
				EventQQGetQuerySomeone.Career = 9;
			}else
			{
				EventQQGetQuerySomeone.Career = 10;
			}
			break;
		case 'F':
			if(DbCharacter.Sex == 'A')
			{
				EventQQGetQuerySomeone.Career = 11;
			}else
			{
				EventQQGetQuerySomeone.Career = 12;
			}
			break;
		case 'G':
			if(DbCharacter.Sex == 'A')
			{
				EventQQGetQuerySomeone.Career = 13;
			}else
			{
				EventQQGetQuerySomeone.Career = 14;
			}
			break;
		}
		//EventQQGetQuerySomeone.Career = 1;
		
		strcpy(EventQQGetQuerySomeone.Spouse, DbCharacter.Spouse);
		EventQQGetQuerySomeone.Prestige = DbCharacter.Prestige;
		EventQQGetQuerySomeone.PK = DbCharacter.PkCount;
		EventQQGetQuerySomeone.Money = DbCharacter.Money;
		
		memcpy(send_packet.data.cBuf, &EventQQGetQuerySomeone, sizeof(TPOS_EVENT_QQGETQUERYSOMEONE));
		
		ServerSendPacketToOne(cn, &send_packet);
	}	
}
//-------------------------------------------------------------------------------
void	ServerDoQQRequestAddSomeone(TPOS_CN *cn, TPOS_PACKET *packet)
{
	TPOS_EVENT_QQREQUESTADDSOMEONE	EventQQRequestAddSomeone;
	TPOS_EVENT_QQGETADDSOMEONE		EventQQGetAddSomeone;
	TPOS_DB_QQ						DbQQRequest;
	TPOS_DB_QQ						DbQQTarget;	
	static TPOS_PACKET				send_packet;
	char							guildname[32];
	int								i, x;

	memcpy(&EventQQRequestAddSomeone, packet->data.cBuf, sizeof(TPOS_EVENT_QQREQUESTADDSOMEONE));

	memset(&DbQQRequest, 0x0, sizeof(TPOS_DB_QQ));
	i = GetRecordFromQQDBByID(&DbQQRequest, EventQQRequestAddSomeone.RequestID);
	strcpy(guildname, DbQQRequest.GuildName);	  		  
	memset(&DbQQTarget, 0x0, sizeof(TPOS_DB_QQ));
	i = GetRecordFromQQDBByID(&DbQQTarget, EventQQRequestAddSomeone.TargetID);
	if(i != -1)
	{
		if(strcmp(guildname,"")!=0)
		{
			if(strcmp(guildname, DbQQTarget.GuildName) == 0)
			{
				send_packet.Header.dwType = QQ_GET_ADD_GUILD_FRIEND;
				for(x = 0; x < 128; x++)
				{
					if(DbQQRequest.GuildFriend[x].ID == 0)
					{
						DbQQRequest.GuildFriend[x].ID = EventQQRequestAddSomeone.TargetID;
						break;
					}					
				}			
				x = UpdateRecordOfQQDB(&DbQQRequest);				
			}
		}else
		{
			send_packet.Header.dwType = QQ_GET_ADD_SOMEONE;
			for(x = 0; x < 256; x++)
			{
				if(DbQQRequest.Friend[x].ID==0)
				{
					DbQQRequest.Friend[x].ID = EventQQRequestAddSomeone.TargetID;
					break;
				}					
			}			
			x = UpdateRecordOfQQDB(&DbQQRequest);			  
		}  		  
		send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_QQGETADDSOMEONE);
		
		EventQQGetAddSomeone.TargetID = DbQQTarget.ID;
		EventQQGetAddSomeone.RequestID = DbQQRequest.ID;
		EventQQGetAddSomeone.Index = 0;
		EventQQGetAddSomeone.Relation = 0;		  
		EventQQGetAddSomeone.Career = DbQQTarget.Career;
		strcpy(EventQQGetAddSomeone.MainName,DbQQTarget.CharacterName);
		EventQQGetAddSomeone.State = DbQQTarget.State;
		
		memcpy(send_packet.data.cBuf, &EventQQGetAddSomeone, sizeof(TPOS_EVENT_QQGETADDSOMEONE));

		ServerSendPacketToOne(cn, &send_packet);
	}	
}
//-------------------------------------------------------------------------------
void	ServerDoQQsend2OneMsg(TPOS_CN *cn, TPOS_PACKET *packet)
{
	TPOS_EVENT_QQREQUESTSENDMSGTOONE	EventQQRequestSendMsgToOne;
	TPOS_EVENT_QQGETMSG					EventQQGetMsg;
	static TPOS_PACKET					send_packet;
	ULONG								zoneindex;
	char								zonename[32];
	int									x;

	memcpy(&EventQQRequestSendMsgToOne, packet->data.cBuf, sizeof(TPOS_EVENT_QQREQUESTSENDMSGTOONE));	
	
	LOCK_ZONEINFO(0);
	zoneindex = FindQQOnliePlayerZoneIndexByQQID(EventQQRequestSendMsgToOne.RecvID);	
	UNLOCK_ZONEINFO(0);		
	
	if(zoneindex == -1)
	{		 
		//TO DO 該名使用者不在線上		 				
	}else
	{
		LOCK_ZONEINFO(0);
		strcpy(zonename ,ZoneInfo[zoneindex].cName);
		UNLOCK_ZONEINFO(0);

		LOCK_CONNECTION(0);
		x = FindConnectionByZoneName(zonename);
		UNLOCK_CONNECTION(0);
		if(x != -1)
		{	  	
			send_packet.Header.dwType = QQ_GET_MSG;
			send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_QQGETMSG);

			EventQQGetMsg.SendID = EventQQRequestSendMsgToOne.SendID;
			EventQQGetMsg.RecvID = EventQQRequestSendMsgToOne.RecvID;
			strcpy(EventQQGetMsg.Msg, EventQQRequestSendMsgToOne.Msg);
			memcpy(send_packet.data.cBuf, &EventQQGetMsg, sizeof(TPOS_EVENT_QQGETMSG));

			ServerSendPacketToOne(&Pos_Cn[x], &send_packet);			
		}		
	}	
}
//-------------------------------------------------------------------------------
void	ServerDoQQRequestPlayerCount(TPOS_CN *cn, TPOS_PACKET *packet)
{
	TPOS_EVENT_QQREQUESTPLAYERCOUNT	EventQQRequestPlayerCount;
	TPOS_EVENT_QQGETPLAYERCOUNT		EventQQGetPlayerCount;
	static TPOS_PACKET				send_packet;

	memcpy(&EventQQRequestPlayerCount, packet->data.cBuf, sizeof(TPOS_EVENT_QQREQUESTPLAYERCOUNT));
	
	send_packet.Header.dwType = QQ_GET_PLAYER_COUNT;
	send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_QQGETPLAYERCOUNT);
	
	EventQQGetPlayerCount.PlayerCount = dwOnlineAllWorldPlayer;
	EventQQGetPlayerCount.RequestID = EventQQRequestPlayerCount.RequestID;
	
	memcpy(send_packet.data.cBuf, &EventQQGetPlayerCount, sizeof(TPOS_EVENT_QQGETPLAYERCOUNT));

	ServerSendPacketToOne(cn, &send_packet);
}
//-------------------------------------------------------------------------------
void	ServerDoQQRequestDeleteFriend(TPOS_CN *cn, TPOS_PACKET *packet)
{
	TPOS_EVENT_QQREQUESTDELFRIEND	EventQQRequestDelFriend;
	TPOS_EVENT_QQGETDELFRIEND		EventQQGetDelFriend;
	static TPOS_PACKET				send_packet;
	TPOS_DB_QQ						DbQQ;
	SLONG							i, x;

	memcpy(&EventQQRequestDelFriend, packet->data.cBuf, sizeof(TPOS_EVENT_QQREQUESTDELFRIEND));
	i = GetRecordFromQQDBByID(&DbQQ, EventQQRequestDelFriend.RequestID);		  
	for(x = 0; x < 256; x++)
	{
		if(DbQQ.Friend[x].ID == EventQQRequestDelFriend.TargetID)
		{
			DbQQ.Friend[x].ID = 0;
			DbQQ.Friend[x].Relation = 0;
			for(i = x;i < 255;i ++)
			{
				DbQQ.Friend[i].ID = DbQQ.Friend[i + 1].ID;
				DbQQ.Friend[i].Relation = DbQQ.Friend[i + 1].Relation;
			}
			DbQQ.Friend[255].ID = 0;
			DbQQ.Friend[255].Relation = 0;
			break;
		}					
	}
	i = UpdateRecordOfQQDB(&DbQQ);
	
	send_packet.Header.dwType = QQ_GET_DEL_FRIEND;
	send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_QQGETDELFRIEND); 
	EventQQGetDelFriend.RequestID = EventQQRequestDelFriend.RequestID;
	EventQQGetDelFriend.TargetID = EventQQRequestDelFriend.TargetID;
	memcpy(send_packet.data.cBuf, &EventQQGetDelFriend, sizeof(TPOS_EVENT_QQGETDELFRIEND));

	ServerSendPacketToOne(cn, &send_packet);
}
//-------------------------------------------------------------------------------
void	ServerDoQQRequestDeleteGuildFriend(TPOS_CN *cn, TPOS_PACKET *packet)
{
	TPOS_EVENT_QQREQUESTDELGUILDFRIEND	EventQQRequestDelGuildFriend;
	TPOS_EVENT_QQGETDELGUILDFRIEND		EventQQGetDelGuildFriend;
	static TPOS_PACKET					send_packet;
	TPOS_DB_QQ							DbQQ;
	SLONG								i, x;

	memcpy(&EventQQRequestDelGuildFriend, packet->data.cBuf, sizeof(TPOS_EVENT_QQREQUESTDELGUILDFRIEND));
	i = GetRecordFromQQDBByID(&DbQQ, EventQQRequestDelGuildFriend.RequestID);		  
	for(x = 0; x < 128; x++)
	{
		if(DbQQ.GuildFriend[x].ID == EventQQRequestDelGuildFriend.TargetID)
		{
			DbQQ.GuildFriend[x].ID = 0;
			DbQQ.GuildFriend[x].Relation = 0;
			for(i = x;i < 127;i ++)
			{
				DbQQ.GuildFriend[i].ID = DbQQ.GuildFriend[i + 1].ID;
				DbQQ.GuildFriend[i].Relation = DbQQ.GuildFriend[i + 1].Relation;
			}
			DbQQ.GuildFriend[127].ID = 0;
			DbQQ.GuildFriend[127].Relation = 0;
			break;
		}					
	}
	i = UpdateRecordOfQQDB(&DbQQ);
	
	send_packet.Header.dwType = QQ_GET_DEL_GUILD_FRIEND;
	send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_QQGETDELGUILDFRIEND); 
	EventQQGetDelGuildFriend.RequestID = EventQQRequestDelGuildFriend.RequestID;
	EventQQGetDelGuildFriend.TargetID = EventQQRequestDelGuildFriend.TargetID;
	memcpy(send_packet.data.cBuf, &EventQQGetDelGuildFriend, sizeof(TPOS_EVENT_QQGETDELGUILDFRIEND));

	ServerSendPacketToOne(cn, &send_packet);
}
//-------------------------------------------------------------------------------
void	ServerDoQQRequestTransferItem(TPOS_CN *cn, TPOS_PACKET *packet)
{
	TPOS_EVENT_QQREQUESTTRANSFERITEMFROMWORLD	EventQQRequestTransferItemFromZone;
	TPOS_EVENT_QQREQUESTTRANSFERITEMFROMWORLD	EventQQRequestTransferItem;
	TPOS_EVENT_QQTRANSFERITEMFAILFROMWORLD		EventQQTransferItemFailFromWorld;
	static	TPOS_PACKET							send_packet;
	int											zoneindex, x;	
	char										zonename[32];
	
	memcpy(&EventQQRequestTransferItemFromZone, 
		   packet->data.cBuf, 
		   sizeof(TPOS_EVENT_QQREQUESTTRANSFERITEMFROMWORLD));

	LOCK_ZONEINFO(0);
	zoneindex = FindQQOnliePlayerZoneIndexByQQID(EventQQRequestTransferItemFromZone.TargetID);	
	UNLOCK_ZONEINFO(0);		
	
	if(zoneindex == -1)
	{		 
		// 該玩家不在線..送出傳送物品失敗
		send_packet.Header.dwType = QQ_TRANSFER_ITEM_FAIL_FROM_WORLD;
		send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_QQTRANSFERITEMFAILFROMWORLD);
		EventQQTransferItemFailFromWorld.RequestID = EventQQRequestTransferItemFromZone.RequestID;
		EventQQTransferItemFailFromWorld.TargetID = EventQQRequestTransferItemFromZone.TargetID;
		memcpy(send_packet.data.cBuf, &EventQQTransferItemFailFromWorld, sizeof(TPOS_EVENT_QQTRANSFERITEMFAILFROMWORLD));
		ServerSendPacketToOne(cn, &send_packet);
	}else
	{
		// 送給目標玩家所在區域, 通知要傳送物品
		LOCK_ZONEINFO(0);
		strcpy(zonename ,ZoneInfo[zoneindex].cName);
		UNLOCK_ZONEINFO(0);

		LOCK_CONNECTION(0);
		x = FindConnectionByZoneName(zonename);
		UNLOCK_CONNECTION(0);
		if(x != -1)
		{	  	
			send_packet.Header.dwType = QQ_REQUEST_TRANSFER_ITEM_FROM_WORLD;
			send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_QQREQUESTTRANSFERITEMFROMWORLD);

			EventQQRequestTransferItem.RequestID = EventQQRequestTransferItemFromZone.RequestID;
			EventQQRequestTransferItem.TargetID = EventQQRequestTransferItemFromZone.TargetID;						
			memcpy(EventQQRequestTransferItem.TransItem, 
				   EventQQRequestTransferItemFromZone.TransItem,
				   sizeof(TPOS_ITEM) * MAX_CHARACTER_TRANS_ITEMS);
			memcpy(send_packet.data.cBuf, &EventQQRequestTransferItem, sizeof(TPOS_EVENT_QQREQUESTTRANSFERITEMFROMWORLD));

			ServerSendPacketToOne(&Pos_Cn[x], &send_packet);			
		}		
	}		
}
//-------------------------------------------------------------------------------
void	ServerDoQQTransferItemOK(TPOS_CN *cn, TPOS_PACKET *packet)
{
	TPOS_EVENT_QQTRANSFERITEMOK				EventQQTransferItemOK;
	TPOS_EVENT_QQTRANSFERITEMOKFROMWORLD	EventQQTransferItemOKFromWorld;	
	static	TPOS_PACKET						send_packet;
	int										zoneindex, x;	
	char									zonename[32];
		
	memcpy(&EventQQTransferItemOK, packet->data.cBuf, sizeof(TPOS_EVENT_QQTRANSFERITEMOK));

	LOCK_ZONEINFO(0);
	zoneindex = FindQQOnliePlayerZoneIndexByQQID(EventQQTransferItemOK.RequestID);		
	strcpy(zonename ,ZoneInfo[zoneindex].cName);
	UNLOCK_ZONEINFO(0);

	LOCK_CONNECTION(0);
	x = FindConnectionByZoneName(zonename);
	UNLOCK_CONNECTION(0);
	if(x != -1)
	{
		send_packet.Header.dwType = QQ_TRANSFER_ITEM_OK_FROM_WORLD;
		send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_QQTRANSFERITEMOKFROMWORLD);
		
		EventQQTransferItemOKFromWorld.RequestID = EventQQTransferItemOK.RequestID;
		EventQQTransferItemOKFromWorld.TargetID = EventQQTransferItemOK.TargetID;						
		
		memcpy(send_packet.data.cBuf, &EventQQTransferItemOKFromWorld, sizeof(TPOS_EVENT_QQTRANSFERITEMOKFROMWORLD));
		
		ServerSendPacketToOne(&Pos_Cn[x], &send_packet);
	}	
}
//-------------------------------------------------------------------------------
void	ServerDoQQTransferItemFail(TPOS_CN *cn, TPOS_PACKET *packet)
{
	TPOS_EVENT_QQTRANSFERITEMFAIL			EventQQTransferItemFail;
	TPOS_EVENT_QQTRANSFERITEMFAILFROMWORLD	EventQQTransferItemFailFromWorld;	
	static	TPOS_PACKET						send_packet;
	int										zoneindex, x;	
	char									zonename[32];
		
	memcpy(&EventQQTransferItemFail, packet->data.cBuf, sizeof(TPOS_EVENT_QQTRANSFERITEMFAIL));

	LOCK_ZONEINFO(0);
	zoneindex = FindQQOnliePlayerZoneIndexByQQID(EventQQTransferItemFail.RequestID);		
	strcpy(zonename ,ZoneInfo[zoneindex].cName);
	UNLOCK_ZONEINFO(0);

	LOCK_CONNECTION(0);
	x = FindConnectionByZoneName(zonename);
	UNLOCK_CONNECTION(0);
	if(x != -1)
	{
		send_packet.Header.dwType = QQ_TRANSFER_ITEM_FAIL_FROM_WORLD;
		send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_QQTRANSFERITEMFAILFROMWORLD);
		
		EventQQTransferItemFailFromWorld.RequestID = EventQQTransferItemFail.RequestID;
		EventQQTransferItemFailFromWorld.TargetID = EventQQTransferItemFail.TargetID;						
		
		memcpy(send_packet.data.cBuf, &EventQQTransferItemFailFromWorld, sizeof(TPOS_EVENT_QQTRANSFERITEMFAILFROMWORLD));
		
		ServerSendPacketToOne(&Pos_Cn[x], &send_packet);
	}
}
//-------------------------------------------------------------------------------
void	ServerDoPlayerRequestLoginZone(TPOS_CN *cn, TPOS_PACKET *packet)
{
	int							x;
	static TPOS_PACKET			send_packet;
	static TPOS_COMPACKET		send_compacket;
	TPOS_EVENT_REQUESTLOGINZONE	EventRequestLoginZone;
	TPOS_EVENT_GETZONEINFO		EventGetZoneInfo;

	memcpy(&EventRequestLoginZone, packet->data.cBuf, sizeof(TPOS_EVENT_REQUESTLOGINZONE));
	LOCK_ZONEINFO(0);
	x = FindZoneInfoByName(EventRequestLoginZone.cZone);			  			
	UNLOCK_ZONEINFO(0);
	if(x >= 0 )
	{		
		LOCK_ZONEINFO(x);		  
		strcpy(EventGetZoneInfo.cZone, ZoneInfo[x].cName);
		strcpy(EventGetZoneInfo.cMapName, ZoneInfo[x].cMapName);
		strcpy(EventGetZoneInfo.cAddr, ZoneInfo[x].cAddr);
		EventGetZoneInfo.dwPort = ZoneInfo[x].dwPort;
		EventGetZoneInfo.dwType = ZoneInfo[x].dwType;
		EventGetZoneInfo.dwPlayerCount = ZoneInfo[x].dwPlayerCount;
		UNLOCK_ZONEINFO(x);
		
		send_packet.Header.dwType = GET_ZONE_INFO;
		send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_GETZONEINFO);
		memcpy(&send_packet.data.cBuf, &EventGetZoneInfo, sizeof(TPOS_EVENT_GETZONEINFO));		
	}else
	{
		send_packet.Header.dwType = ERROR_DATA;
		send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER);
	}
	CompressPacket(&send_packet, &send_compacket);

	LOCK_CONNECTION(0);
	QueuePacket(cn, &send_compacket, CONNECTED_SERVER_WORLD);
	UNLOCK_CONNECTION(0);
}
//-------------------------------------------------------------------------------
void	ServerDoZoneLogin(TPOS_CN *cn, TPOS_PACKET *packet)
{
	BOOL					b;
	static TPOS_PACKET		send_packet;
	static TPOS_COMPACKET	send_compacket;
	TPOS_EVENT_ZONELOGIN	EventZoneLogin;

	SaveMsgToLog("SYSTEM","ZONE_LOGIN");       
		
	memcpy(&EventZoneLogin, packet->data.cBuf, sizeof(TPOS_EVENT_ZONELOGIN));
	memset(&send_packet, 0x0, sizeof(TPOS_PACKETHEADER));
	b = FindLVItem(hListViewWnd, EventZoneLogin.cZone);
	if(b==TRUE)
	{
		send_packet.Header.dwType = ZONENAME_DUPLICATE;
	}else
	{
		send_packet.Header.dwType = WORLD_LOGIN_OK;
	}       
	send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER);

	CompressPacket(&send_packet, &send_compacket);

	LOCK_CONNECTION(0);
	QueuePacket(cn, &send_compacket, CONNECTED_SERVER_WORLD);
	UNLOCK_CONNECTION(0);
}
//-------------------------------------------------------------------------------
void	ServerDoNewZoneInfo(TPOS_CN *cn, TPOS_PACKET *packet)
{
	TPOS_EVENT_NEWZONEINFO	EventNewZoneInfo;	
	char					tmpbuffera[20];
	char					tmpbufferb[20];
	int						i, x;
	char					str[256];
	
	memcpy(&EventNewZoneInfo, packet->data.cBuf, sizeof(TPOS_EVENT_NEWZONEINFO));
	LOCK_ZONEINFO(0);
	i = FindUsableZoneInfo();
	UNLOCK_ZONEINFO(0);
	
	LOCK_CONNECTION(0);
	x = FindCurrentConnection((WPARAM)cn->dwSocket);		  
	strcpy(Pos_Cn[x].User.cId, EventNewZoneInfo.cName);
	UNLOCK_CONNECTION(0);
	
	itoa(0, tmpbuffera, 10);
	itoa(EventNewZoneInfo.dwPort, tmpbufferb, 10);
	InsertLVItem(hListViewWnd, 0, EventNewZoneInfo.cName,
				 tmpbuffera, EventNewZoneInfo.cAddr,
				 tmpbufferb, EventNewZoneInfo.cMapName,	"Active");              
	
	LOCK_ZONEINFO(0);
	ZoneInfo[i].dwIndex = (DWORD)i + 1;
	ZoneInfo[i].dwSocket = cn->dwSocket;
	strcpy(ZoneInfo[i].cName, EventNewZoneInfo.cName);
	strcpy(ZoneInfo[i].cMapName, EventNewZoneInfo.cMapName);
	strcpy(ZoneInfo[i].cAddr, EventNewZoneInfo.cAddr);
	ZoneInfo[i].dwPort = EventNewZoneInfo.dwPort;
	ZoneInfo[i].dwPlayerCount = EventNewZoneInfo.dwPlayerCount;
	ZoneInfo[i].dwType = EventNewZoneInfo.dwType;
	UNLOCK_ZONEINFO(0);	   
	
	iZoneCount++;
	sprintf(str, "Now Zone : %d", iZoneCount);
	MsgOut(hStatusBarWnd,4,str);
	dwOnlineLoginer--;
	sprintf(str, "Now Login : %d", dwOnlineLoginer);
	MsgOut(hStatusBarWnd, 0, str);

	RefreshAllWorldPlayer();	  	  

	SendNewZoneInfoToAll(EventNewZoneInfo.cName, EventNewZoneInfo.dwPlayerCount,
						 EventNewZoneInfo.cAddr, EventNewZoneInfo.dwPort,
						 EventNewZoneInfo.cMapName, EventNewZoneInfo.dwType);  
}
//-------------------------------------------------------------------------------
void	ServerDoRequestZoneInfo(TPOS_CN *cn, TPOS_PACKET *packet)
{
	int							tempzoneindex;
	TPOS_EVENT_REQUESTZONEINFO	EventRequestZoneInfo;
	TPOS_EVENT_GETZONEINFO		EventGetZoneInfo;
	static TPOS_PACKET			send_packet;
	static TPOS_COMPACKET		send_compacket;	
	char						tmpzonename[32];
	int							i;
	
	memcpy(&EventRequestZoneInfo, packet->data.cBuf, sizeof(TPOS_EVENT_REQUESTZONEINFO));

	tempzoneindex = EventRequestZoneInfo.dwIndex;	

	send_packet.Header.dwType = GET_ZONE_INFO;
	send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_GETZONEINFO);

	for(i = tempzoneindex;i < MAX_ZONE_PER_WORLD;i++)
	{	
		if(tempzoneindex >= iZoneCount)
		{
			EventGetZoneInfo.dwIndex = END;
			
			memcpy(send_packet.data.cBuf, &EventGetZoneInfo, sizeof(TPOS_EVENT_GETZONEINFO));				
			break;
		}	
		LOCK_ZONEINFO(0);
		strcpy(tmpzonename, ZoneInfo[i].cName);
		UNLOCK_ZONEINFO(0);
		if(strcmp(tmpzonename,"") != 0)
		{
			LOCK_ZONEINFO(0);
			EventGetZoneInfo.dwIndex = i;
			strcpy(EventGetZoneInfo.cZone , ZoneInfo[i].cName);
			strcpy(EventGetZoneInfo.cMapName , ZoneInfo[i].cMapName);
			strcpy(EventGetZoneInfo.cAddr , ZoneInfo[i].cAddr);
			EventGetZoneInfo.dwPort = ZoneInfo[i].dwPort;
			EventGetZoneInfo.dwPlayerCount = ZoneInfo[i].dwPlayerCount;
			EventGetZoneInfo.dwType = ZoneInfo[i].dwType;
			UNLOCK_ZONEINFO(0);
			
			memcpy(send_packet.data.cBuf, &EventGetZoneInfo, sizeof(TPOS_EVENT_GETZONEINFO));			
			break;
		}
	}	
	
	CompressPacket(&send_packet, &send_compacket);
		
	LOCK_CONNECTION(0);
	QueuePacket(cn, &send_compacket, CONNECTED_SERVER_WORLD);
	UNLOCK_CONNECTION(0);	
}
//-------------------------------------------------------------------------------
void	ServerDoRefreshZoneInfo(TPOS_CN *cn, TPOS_PACKET *packet)
{
	TPOS_EVENT_REFRESHZONEINFO	EventRefreshZoneInfo;
	int							i;
	char						str[256];

	memcpy(&EventRefreshZoneInfo, packet->data.cBuf, sizeof(TPOS_EVENT_REFRESHZONEINFO));
	
	LOCK_ZONEINFO(0);
	i = FindZoneInfoByName(EventRefreshZoneInfo.cName);	   
	ZoneInfo[i].dwPlayerCount=EventRefreshZoneInfo.dwPlayerCount;
	UNLOCK_ZONEINFO(0);
	
	i = FindLVItem(hListViewWnd, EventRefreshZoneInfo.cName);
	memset(str, 0, 256);
	itoa(EventRefreshZoneInfo.dwPlayerCount, str, 10);
	SetLVItem(hListViewWnd, i, str);
	
	RefreshAllWorldPlayer();
	
	SaveMsgToLog("SYSTEM","REFRESH_ZONE_INFO");
	// --- 送出區域伺服器更新資料	  
	SendZoneRefreshInfoToAll(EventRefreshZoneInfo.cName,
							 EventRefreshZoneInfo.dwPlayerCount);
}
//-------------------------------------------------------------------------------
void	ServerDoSendWorldTalk(TPOS_CN *cn, TPOS_PACKET *packet)
{
}
//-------------------------------------------------------------------------------
void	ServerDoZoneRequestJoinTeam(TPOS_CN *cn, TPOS_PACKET *packet)
{
}
//-------------------------------------------------------------------------------
void	ServerDoZoneRequestAgreeJoinTeam(TPOS_CN *cn, TPOS_PACKET *packet)
{
}
//-------------------------------------------------------------------------------
void	ServerDoZoneRequestExitTeam(TPOS_CN *cn, TPOS_PACKET *packet)
{
}
//-------------------------------------------------------------------------------
void	ServerDoZoneRequestKickTeamMember(TPOS_CN *cn, TPOS_PACKET *packet)
{
}
//-------------------------------------------------------------------------------
void	ServerDoZoneNotifySomeoneWantJoinTeam(TPOS_CN *cn, TPOS_PACKET *packet)
{
}
//-------------------------------------------------------------------------------
void	ServerDoZoneNotifyJoinTeamFull(TPOS_CN *cn, TPOS_PACKET *packet)
{
}
//-------------------------------------------------------------------------------
void	ServerDoZoneNotifySomeoneJoinTeam(TPOS_CN *cn, TPOS_PACKET *packet)
{
}
//-------------------------------------------------------------------------------
void	ServerDoZoneNotifySomeoneExitTeam(TPOS_CN *cn, TPOS_PACKET *packet)
{
}
//-------------------------------------------------------------------------------
void	ServerDoZoneNotifyKickFromTeam(TPOS_CN *cn, TPOS_PACKET *packet)
{
}
//-------------------------------------------------------------------------------
void	ServerDoZoneNotifyTeamMemberInfo(TPOS_CN *cn, TPOS_PACKET *packet)
{
}
//-------------------------------------------------------------------------------
void	ServerDoZoneNotifyTeamMemberChangeZone(TPOS_CN *cn, TPOS_PACKET *packet)
{
}
//-------------------------------------------------------------------------------
void	ConvertEventCharacterFinalToDbCharacter(TPOS_EVENT_CREATECHARACTERFINAL *eccf, TPOS_DB_CHARACTER *dc)
{
	int	i;
	memset(dc, 0x0, sizeof(TPOS_DB_CHARACTER));

	dc->Color = eccf->Color;
	dc->Country = eccf->Country;
	strcpy(dc->MainName, eccf->cMainName);
	strcpy(dc->NickName, eccf->cNickName);
	dc->Index = (UHINT)eccf->dwIndex;
	dc->Eyes = eccf->Eyes;
	dc->Mouth = eccf->Mouth;
	for(i = 0;i < MAX_CHARACTER_PARTS;i++)
	{
		dc->PartRGB[i] = eccf->PartRGB[i];
	}	
}
//-------------------------------------------------------------------------------
void	ConvertDbCharacterToEventGetCharacterInfo(TPOS_DB_CHARACTER *dc, TPOS_EVENT_GETCHARACTERINFO *egc)
{
	egc->cCareer = dc->Career;
	egc->cCountry = dc->Country;
	strcpy(egc->cMainName, dc->MainName);
	strcpy(egc->cNickName, dc->NickName);
	strcpy(egc->cNobility, dc->Nobility);
	egc->cSex = dc->Sex;
	strcpy(egc->cZone, dc->ZoneName);
	egc->uhiLevel = dc->Level;	
	egc->QQID = dc->QQID;	
}
//-------------------------------------------------------------------------------

