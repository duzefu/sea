/*
**	ZoneServerMisc.cpp
**	zone server misc functions.
**
**	Hawke, 2003/01/07.
*/
#include "ZoneServer_Def.h"

//-------------------------------------------------------------------------------
//功能: 尋找可以供玩家使用的 CharacterInfo 空位(cMainname 為空)
//參數: 無
//返回: 如果找到, 返回其索引值, 否則, 返回-1.
int FindUsablePlayerCharacterInfo(void)
{
    int i;
    
    for(i = 0;i < MAX_PLAYER_PER_ZONE;i++)
    {
        if(strcmp(GetCharacterMainName(i) ,"")==0)
        {
            return(i);
        }
    }
    return  -1;
}

//-------------------------------------------------------------------------------
//功能: 尋找下一個已經被使用的CharacterInfo(玩家和NPC)
int     FindNextUsedCharacterInfo(int start)
{
    int i;

    for(i = start; i < MAX_CHARACTER_PER_ZONE; i++)
    {
        if(strcmp(GetCharacterMainName(i),"") != 0)
        {
            return(i);
        }
    }
    return  -1;
}

//-------------------------------------------------------------------------------

//功能: 尋找可以供玩家使用的連接
int     FindUsableConnection(void)
{
    int i;
    
    for(i = 0; i < MAX_PLAYER_PER_ZONE; i++)
    {
        if(Pos_Cn[i].dwSocket==0)
        {
            return(i);
        }
    }
    return  -1;
}

//-------------------------------------------------------------------------------
//功能: 依據人物名稱尋找其對應的索引值
int     FindPlayerCharacterInfoByMainName(char *mainname)
{
    int i;
    
    for(i = 0;i < MAX_PLAYER_PER_ZONE;i++)
    {
        if(strcmp(GetCharacterMainName(i), mainname)==0)
        {
            return(i);
        }
    }
    return  -1;
}
//-------------------------------------------------------------------------------
//功能: 依據帳號名稱尋找其對應的索引值
int     FindPlayerCharacterInfoByAccount(char *account)
{
    int i;
    
    for(i = 0;i < MAX_PLAYER_PER_ZONE;i++)
    {
        if(strcmp(GetCharacterAccount(i), account) == 0)
        {
            return(i);
        }
    }
    return  -1;
}
//-------------------------------------------------------------------------------

//功能: 尋找可以供玩家使用同步的連接
int     FindUsableSyncConnection(void)
{
    int i;

    for(i = 0; i < MAX_PLAYER_PER_ZONE; i++)
    {
        if(Pos_Cn_Sync[i].dwSocket == 0)
        {
            return(i);
        }
    }
    return  -1;
}
//-------------------------------------------------------------------------------
//功能: 尋找玩家是否已登錄過
//參數: ID 玩家的ID名稱
//返回: 如果找到, 返回 TURE, 否則, 返回 FALSE.
BOOL FindLoginedPlayerCharacterInfo(char *id)
{
    int   i;
	BOOL  ret_code=FALSE;
    
    for(i = 0;i < MAX_PLAYER_PER_ZONE; i++)
    {
        if(strcmp(GetCharacterAccount(i), id)==0)
        {
			ret_code = TRUE;     
            break;
        }
		ret_code = FALSE; 
    }
    return  ret_code;
}
//-------------------------------------------------------------------------------
int     FindUsableZoneInfo(void)
{
	int i;

    for(i = 0; i < MAX_ZONE_PER_WORLD; i++)
    {
        if(ZoneInfo[i].cName[0] == '\0')
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
        if(strcmp(ZoneInfo[i].cName, name) ==0)
        {
            return(i);
        }
    }
    return  -1;
}
//-------------------------------------------------------------------------------
int     FindZoneInfoByMapName(char *name)
{	
	int i;
    
    for(i = 0; i < MAX_ZONE_PER_WORLD; i++)
    {
        if(strcmp(ZoneInfo[i].cMapName, name) ==0)
        {
            return(i);
        }
    }
    return  -1;
}
// -----------------------------------------------------------------------------
// Find CharacterInfo By QQID
// -----------------------------------------------------------------------------
int	FindCharacterInfoByQQID(ULONG ID)
{
	int		i;
	ULONG	qq_id;
    
    for(i=0; i<MAX_PLAYER_PER_ZONE; i++)
    {
        qq_id = GetCharacterQQID(i);
		if(qq_id == ID)
        {
            return(i);
        }
    }
    return  -1;
}
// -----------------------------------------------------------------------------
// Convert ZoneCharacter To DBCharacter
// -----------------------------------------------------------------------------
void	ConvertZoneCharacterToDBCharacter(TPOS_CHARACTER *character, TPOS_DB_CHARACTER *dbcharacter)
{
	int	i;

	strcpy(dbcharacter->ID, character->Name.ID);
	strcpy(dbcharacter->MainName, character->Name.MainName);
	strcpy(dbcharacter->NickName, character->Name.NickName);
	dbcharacter->QQID = character->Name.QQID;
	dbcharacter->Index = (SHINT)character->Name.Index;
	dbcharacter->Color = character->Style.Color;
	dbcharacter->Eyes = character->Style.Eyes;
	dbcharacter->Mouth = character->Style.Mouth;
	dbcharacter->MainNameColor = character->Style.MainNameColor;
	dbcharacter->NickNameColor = character->Style.NickNameColor;
	dbcharacter->MessageColor = character->Style.MessageColor;
	dbcharacter->TalkBackColor = character->Style.TalkBackColor;
	dbcharacter->Logo = character->Style.Logo;
	dbcharacter->LandFileIndex = character->Style.LandFileIndex;
	dbcharacter->SeaFileIndex = character->Style.SeaFileIndex;
	strcpy(dbcharacter->ZoneName, character->Position.ZoneName);
	dbcharacter->X = character->Position.X;
	dbcharacter->Y = character->Position.Y;
	dbcharacter->Z = character->Position.Z;
	dbcharacter->Dir = character->Position.Dir;
	dbcharacter->StopRadius = character->Position.StopRadius;
	dbcharacter->Mspeed = character->Speed.Mspeed;
	dbcharacter->FSpeedX = character->Speed.FSpeedX;
	dbcharacter->FSpeedY = character->Speed.FSpeedY;
	dbcharacter->SailSize = character->Speed.SailSize;
	dbcharacter->Turn = character->Speed.Turn;
	dbcharacter->Weight = character->Speed.Weight;
	dbcharacter->DegreeDir = character->Speed.DegreeDir;
	dbcharacter->BitState = character->State.BitState;
	dbcharacter->InitStr = character->Property.Str.InitStr;
	dbcharacter->LevUpStr = character->Property.Str.LevUpStr;
	dbcharacter->InitIns = character->Property.Ins.InitIns;
	dbcharacter->LevUpIns = character->Property.Ins.LevUpIns;
	dbcharacter->InitWit = character->Property.Wit.InitWit;
	dbcharacter->LevUpWit = character->Property.Wit.LevUpWit;
	dbcharacter->InitLucky = character->Property.Lucky.InitLucky;
	dbcharacter->LevUpLucky = character->Property.Lucky.LevUpLucky;
	dbcharacter->SightRange = character->Property.Attack.SightRange;
	dbcharacter->FinalExplodeRate = character->Property.Attack.FinalExplodeRate;
	dbcharacter->DodgeRate = character->Property.Defence.DodgeRate;
	dbcharacter->ParryRate = character->Property.Defence.ParryRate;
	dbcharacter->PropertyPoint = character->Property.PropertyPoint;
	dbcharacter->Exp = character->ExpLev.Exp;
	dbcharacter->Level = character->ExpLev.Level;
	dbcharacter->Hp = character->HpMp.Hp;
	dbcharacter->MaxHp = character->HpMp.MaxHp;
	dbcharacter->HpRes = character->HpMp.HpRes;
	dbcharacter->Mp = character->HpMp.Mp;
	dbcharacter->MaxMp = character->HpMp.MaxMp;
	dbcharacter->MpRes = character->HpMp.MpRes;
	for(i = 0;i < MAX_CHARACTER_SKILLS;i++)
	{
		dbcharacter->SkillNo[i] = character->SkillExp.Skill[i];
		dbcharacter->SkillLevel[i] = character->SkillExp.Level[i];
	}
	dbcharacter->EquHead = character->Equipment.EquHead.ID;
	dbcharacter->EquBody = character->Equipment.EquBody.ID;
	dbcharacter->EquNeck = character->Equipment.EquNeck.ID;
	dbcharacter->EquWaist = character->Equipment.EquWaist.ID;
	dbcharacter->EquGlove = character->Equipment.EquGlove.ID;
	dbcharacter->EquWeapon = character->Equipment.EquWeapon.ID;
	dbcharacter->EquWrist = character->Equipment.EquWrist.ID;
	dbcharacter->EquFeet = character->Equipment.EquFeet.ID;	
	dbcharacter->EquOtherA = character->Equipment.EquOtherA.ID;
	dbcharacter->EquOtherB = character->Equipment.EquOtherB.ID;
	dbcharacter->EquOtherC = character->Equipment.EquOtherC.ID;
	for(i = 0;i < MAX_CHARACTER_BAG_ITEMS;i++)
	{
		dbcharacter->BagItem[i] = character->BodyItemMoney.BagItem[i].ID;
	}
	for(i = 0;i < MAX_CHARACTER_SASH_ITEMS;i++)
	{
		dbcharacter->SashItem[i] = character->BodyItemMoney.SashItem[i].ID;
	}
	for(i = 0;i < MAX_CHARACTER_TRANS_ITEMS;i++)
	{
		dbcharacter->TransItem[i] = character->BodyItemMoney.TransItem[i].ID;
	}
	dbcharacter->OnMouseItem = character->BodyItemMoney.OnMouseItem.ID;
	dbcharacter->TreasureItem = character->BodyItemMoney.TreasureItem.ID;
	dbcharacter->Money = character->BodyItemMoney.Money;
	dbcharacter->Sex = character->Society.Sex;
	dbcharacter->Country = character->Society.Country;
	strcpy(dbcharacter->Guild, character->Society.Guild);
	strcpy(dbcharacter->Spouse, character->Society.Spouse);
	dbcharacter->Career = character->Society.Career;
	dbcharacter->CareerLevel = character->Society.CareerLevel;
	dbcharacter->Office = character->Society.Office;
	strcpy(dbcharacter->Nobility, character->Society.Nobility);
	dbcharacter->GoodEvil = character->Society.GoodEvil;
	dbcharacter->Prestige = character->Society.Prestige;
	dbcharacter->PkCount = character->Society.PkCount;
	dbcharacter->PkedCount = character->Society.PkedCount;
	dbcharacter->LandLeftSkill = character->QuickButton.LandLeftSkill;
	dbcharacter->LandRightSkill = character->QuickButton.LandRightSkill;
	dbcharacter->SeaLeftSkill = character->QuickButton.SeaLeftSkill;
	dbcharacter->SeaRightSkill = character->QuickButton.SeaRightSkill;
	for(i = 0;i < MAX_CHARACTER_FN_SKILLS;i++)
	{
		dbcharacter->LandFnSkillNo[i] = character->QuickButton.LandFnSkillNo[i];
		dbcharacter->LandFnSkillHand[i] = character->QuickButton.LandFnSkillHand[i];
		dbcharacter->SeaFnSkillNo[i] = character->QuickButton.SeaFnSkillNo[i];
		dbcharacter->SeaFnSkillHand[i] = character->QuickButton.SeaFnSkillHand[i];
	}
	dbcharacter->DoingKind = character->Action.DoingKind;
	dbcharacter->FinalAttack = character->Property.Attack.FinalAtt;
	dbcharacter->FinalDefence = character->Property.Defence.FinalDefence;
	for(i = 0;i < MAX_CHARACTER_PARTS;i++)
	{
		dbcharacter->PartRGB[i] = character->Style.PartRGB[i];
	}
	dbcharacter->NameColorTicks = character->Style.NameColorTicks;
	dbcharacter->TotalOnlineTicks = character->State.TotalOnlineTicks;
}
// -----------------------------------------------------------------------------
int		FindMarcoDataByMainName(char *mainname)
{
	int i;	
	
	for(i=0;i<500;i++)
	{
		if(strcmp(mainname,ZoneMacro[0].NPC[i].cName)==0)
		{
			return(i);
		}
	}
	return -1;
}
// -----------------------------------------------------------------------------
void	ServerDoGetWorldInfo(TPOS_CN *cn, TPOS_PACKET *packet)
{
	TPOS_EVENT_GETWORLDINFO	EventGetWorldInfo;
	HWND					TmphWnd;	

	memcpy(&EventGetWorldInfo, packet->data.cBuf, sizeof(TPOS_EVENT_GETWORLDINFO));
	
    if(EventGetWorldInfo.dwIndex != END)
	{
		strcpy(GetWorldInfoFromDoor[EventGetWorldInfo.dwIndex].cName,
			EventGetWorldInfo.cName);
		strcpy(GetWorldInfoFromDoor[EventGetWorldInfo.dwIndex].cAddr,
			EventGetWorldInfo.cAddr);
		GetWorldInfoFromDoor[EventGetWorldInfo.dwIndex].dwPort = 
			EventGetWorldInfo.dwPort;
		GetWorldInfoFromDoor[EventGetWorldInfo.dwIndex].dwPlayerCount = 
			EventGetWorldInfo.dwPlayerCount;
		GetWorldInfoFromDoor[EventGetWorldInfo.dwIndex].dwActive = 
			EventGetWorldInfo.dwActive;
		
		SendDlgItemMessage(SetuphWnd,
						IDC_COMBO1,
						CB_ADDSTRING,
						0,
						(LPARAM)GetWorldInfoFromDoor
						[EventGetWorldInfo.dwIndex].cName
						);  
		
		RequestForWorldInfo(NEXT);
	}else
	{   		
		TmphWnd=GetDlgItem(SetuphWnd,IDACTIVE);
		SendDlgItemMessage(SetuphWnd,IDC_COMBO1,CB_SETCURSEL,0,0);
		EnableWindow(TmphWnd,TRUE);
	}    
}
// -----------------------------------------------------------------------------
void	ServerDoWorldLoginOK(TPOS_CN *cn, TPOS_PACKET *packet) 
{
	static TPOS_PACKET				send_packet;
	static TPOS_COMPACKET			send_compacket;
	TPOS_EVENT_NEWZONEINFO	EventNewZoneInfo;
	
	send_packet.Header.dwType = SEND_ZONE_INFO;
	send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NEWZONEINFO);
		
	strcpy(EventNewZoneInfo.cName, ZoneName);
	strcpy(EventNewZoneInfo.cMapName, mapname);
	strcpy(EventNewZoneInfo.cAddr, ZoneServerIP);
	EventNewZoneInfo.dwPort = ZoneServerPort;
	EventNewZoneInfo.dwPlayerCount = dwOnlineCounter;
	EventNewZoneInfo.dwType = ZoneType;

	memcpy(send_packet.data.cBuf, &EventNewZoneInfo, sizeof(TPOS_EVENT_NEWZONEINFO));

	CompressPacket(&send_packet, &send_compacket);

	QueuePacket(World, &send_compacket, CONNECTED_SERVER_WORLD);
	
	RequestForZoneInfo(BEGIN);
}
// -----------------------------------------------------------------------------
void	ServerDoZoneNameDuplicate(TPOS_CN *cn, TPOS_PACKET *packet)
{	
	if(MessageBox(MainhWnd,"ZoneServerName Duplicate!!","Error",MB_OK|MB_ICONERROR)==IDOK)
	{
		ShutDownServer();
	}       
}
// -----------------------------------------------------------------------------
void	ServerDoGetSystemMessage(TPOS_CN *cn, TPOS_PACKET *packet) 
{
	static TPOS_PACKET					send_packet;
	TPOS_EVENT_SYSTEMMESSAGE	EventSystemMessage;
        
	memcpy(&EventSystemMessage, packet->data.cBuf, sizeof(TPOS_EVENT_SYSTEMMESSAGE));

    memset(cSystemMessage,0x0,256);
    strcpy(cWorldServerName, EventSystemMessage.WorldName);    
	strcpy(cSystemMessage, EventSystemMessage.cMsg);

	send_packet.Header.dwType = SYSTEM_MESSAGE;
	send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_SYSTEMMESSAGE);    
    memcpy(send_packet.data.cBuf, &EventSystemMessage, sizeof(TPOS_EVENT_SYSTEMMESSAGE));

    SendSystemMessageToAll(&send_packet);    
}
// -----------------------------------------------------------------------------
void	ServerDoQQPlayerLogin(TPOS_CN *cn, TPOS_PACKET *packet)
{
	return;
}
// -----------------------------------------------------------------------------
void	ServerDoQQLoginOK(TPOS_CN *cn, TPOS_PACKET *packet) 
{
	/*
	static TPOS_PACKET send_packet;	
	CHAR		mainname[32];
	int Find_Idx;
	
	strcpy(mainname,packet->data.QQOnlinePlayerList.MainName);
	LOCK_CONNECTION(0);
	Find_Idx = FindConnectionByName(mainname);		
	UNLOCK_CONNECTION(0);
	
	send_packet.Header.dType = QQ_LOGIN_OK;
	send_packet.Header.dSize = sizeof(TPOS_PACKETHEADER);
	
	server_send_packet_to_one(&Pos_Cn[Find_Idx], &send_packet);	
	*/
}
// -----------------------------------------------------------------------------
void	ServerDoQQPlayerLogout(TPOS_CN *cn, TPOS_PACKET *packet) 
{
	/*
	static TPOS_PACKET	send_packet;
	ULONG		Find_Id;

	send_packet.Header.dType = QQ_PLAYER_LOGOUT;
	send_packet.Header.dSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_QQ_FRIEND_DB);
	LOCK_CHARACTERINFO(0);
	Find_Id = FindCurrentConnectionQQID(cn);
	UNLOCK_CHARACTERINFO(0);	
	send_packet.data.QQFriendDB.ID = Find_Id;	

	QueuePacket(World,&send_packet,CONNECTED_SERVER_WORLD);
	return 0;
	*/
}
// -----------------------------------------------------------------------------
void	ServerDoQQRequestMyData(TPOS_CN *cn, TPOS_PACKET *packet) 
{
	/*
	static TPOS_PACKET	send_packet;	

	send_packet.Header.dType=QQ_REQUEST_MYDATA;
	send_packet.Header.dSize=sizeof(TPOS_PACKETHEADER)+sizeof(TPOS_QQ_MYDATA);
	memcpy(&send_packet.data.QQState,packet->data.QQState,sizeof(TPOS_QQ_STATE));

	server_send_packet_to_one(cn, &send_packet);
	*/
	return;
}
// -----------------------------------------------------------------------------
void	ServerDoQQGetMyData(TPOS_CN *cn, TPOS_PACKET *packet) 
{
	/*
	static TPOS_PACKET		send_packet;
	TPOS_QQ_MYDATA	QQMydata;
	CHAR			mainname[32];
	int				Find_Idx;

	strcpy(mainname,packet->data.QQMyData.CharacterName);
	LOCK_CONNECTION(0);
	Find_Idx = FindConnectionByName(mainname);		
	UNLOCK_CONNECTION(0);

	send_packet.Header.dType=QQ_GET_MYDATA;
	send_packet.Header.dSize=sizeof(TPOS_PACKETHEADER)+sizeof(TPOS_QQ_MYDATA);
	memcpy(&send_packet.data.QQMyData,&packet->data.QQMyData,sizeof(TPOS_QQ_STATE));

	server_send_packet_to_one(&Pos_Cn[Find_Idx], &send_packet);
	
	return;
	*/
}
// -----------------------------------------------------------------------------
void	ServerDoQQRequestFriendList(TPOS_CN *cn, TPOS_PACKET *packet) 
{
	/*
	static TPOS_PACKET	send_packet;
	ULONG		Find_Id;

	send_packet.Header.dType = QQ_REQUEST_FRIEND_LIST;
	send_packet.Header.dSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_QQ_FRIEND);
	LOCK_CHARACTERINFO(0);
	Find_Id = FindCurrentConnectionQQID(cn);
	UNLOCK_CHARACTERINFO(0);	
	send_packet.data.QQFriend.RequestID = Find_Id;
	send_packet.data.QQFriend.Index = packet->data.QQFriend.Index;

	QueuePacket(World,&send_packet,CONNECTED_SERVER_WORLD);

	return 0;
	*/
}
// -----------------------------------------------------------------------------
void	ServerDoQQGetFriendList(TPOS_CN *cn, TPOS_PACKET *packet) 
{
	/*
	static TPOS_PACKET	send_packet;
	ULONG		Find_Idx;
	char		mainname[32];

	send_packet.Header.dType = QQ_GET_FRIEND_LIST;
	send_packet.Header.dSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_QQ_FRIEND);
	LOCK_CHARACTERINFO(0);
	Find_Idx = FindCharacterInfoByQQID(packet->data.QQFriend.RequestID);
	strcpy(mainname,CharacterInfo[Find_Idx].Name.cMainname);
	UNLOCK_CHARACTERINFO(0);
	LOCK_CONNECTION(0);
	Find_Idx = FindConnectionByName(mainname);
	UNLOCK_CONNECTION(0);
	send_packet.data.QQFriend.Index = packet->data.QQFriend.Index;
	send_packet.data.QQFriend.ID = packet->data.QQFriend.ID;
	strcpy(send_packet.data.QQFriend.MainName,packet->data.QQFriend.MainName);
	send_packet.data.QQFriend.Relation = packet->data.QQFriend.Relation;
	send_packet.data.QQFriend.Career = packet->data.QQFriend.Career;
	send_packet.data.QQFriend.State = packet->data.QQFriend.State;

	server_send_packet_to_one(&Pos_Cn[Find_Idx], &send_packet);	
	
	return 0;
	*/
}
// -----------------------------------------------------------------------------
void	ServerDoQQRequestGuildFriendList(TPOS_CN *cn, TPOS_PACKET *packet) 
{
	/*
	static TPOS_PACKET	send_packet;
	ULONG		Find_Id;

	send_packet.Header.dType = QQ_REQUEST_GUILD_FRIEND_LIST;
	send_packet.Header.dSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_QQ_FRIEND);
	LOCK_CHARACTERINFO(0);
	Find_Id = FindCurrentConnectionQQID(cn);
	UNLOCK_CHARACTERINFO(0);	
	send_packet.data.QQFriend.RequestID = Find_Id;
	send_packet.data.QQFriend.Index = packet->data.QQFriend.Index;

	QueuePacket(World,&send_packet,CONNECTED_SERVER_WORLD);
	return 0;
	*/
}
// -----------------------------------------------------------------------------
void	ServerDoQQGetGuildFriendList(TPOS_CN *cn, TPOS_PACKET *packet) 
{
	/*
	static TPOS_PACKET	send_packet;
	ULONG		Find_Idx;
	char		mainname[32];

	send_packet.Header.dType = QQ_GET_GUILD_FRIEND_LIST;
	send_packet.Header.dSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_QQ_FRIEND);
	LOCK_CHARACTERINFO(0);
	Find_Idx = FindCharacterInfoByQQID(packet->data.QQFriend.RequestID);
	strcpy(mainname,CharacterInfo[Find_Idx].Name.cMainname);
	UNLOCK_CHARACTERINFO(0);
	LOCK_CONNECTION(0);
	Find_Idx = FindConnectionByName(mainname);
	UNLOCK_CONNECTION(0);
	send_packet.data.QQFriend.Index = packet->data.QQFriend.Index;
	send_packet.data.QQFriend.ID = packet->data.QQFriend.ID;
	strcpy(send_packet.data.QQFriend.MainName,packet->data.QQFriend.MainName);
	send_packet.data.QQFriend.Relation = packet->data.QQFriend.Relation;
	send_packet.data.QQFriend.Career = packet->data.QQFriend.Career;
	send_packet.data.QQFriend.State = packet->data.QQFriend.State;

	server_send_packet_to_one(&Pos_Cn[Find_Idx], &send_packet);	
	
	return 0;
	*/
}
// -----------------------------------------------------------------------------
void	ServerDoQQSetMyState(TPOS_CN *cn, TPOS_PACKET *packet) 
{
	/*
	static TPOS_PACKET	send_packet;
	ULONG	Find_Id;

	send_packet.Header.dType = QQ_SET_MYSTATE;
	send_packet.Header.dSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_QQ_STATE);
	LOCK_CHARACTERINFO(0);
	Find_Id = FindCurrentConnectionQQID(cn);
	UNLOCK_CHARACTERINFO(0);	
	if(Find_Id != -1)
	{
		send_packet.data.QQState.ID = Find_Id;
		send_packet.data.QQState.Status = packet->data.QQState.Status;
		QueuePacket(World,&send_packet,CONNECTED_SERVER_WORLD);
		return 0;
	}
	return -1;
	*/
}
// -----------------------------------------------------------------------------
void	ServerDoQQGetMyState(TPOS_CN *cn, TPOS_PACKET *packet) 
{
	/*
	static TPOS_PACKET	send_packet;
	ULONG	Find_Idx;
	CHAR	mainname[32];

	send_packet.Header.dType = QQ_GET_MYSTATE;
	send_packet.Header.dSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_QQ_STATE);
	LOCK_CHARACTERINFO(0);
	Find_Idx = FindCharacterInfoByQQID(packet->data.QQState.ID);
	UNLOCK_CHARACTERINFO(0);
	if(Find_Idx != -1)
	{
		LOCK_CHARACTERINFO(0);
		strcpy(mainname,CharacterInfo[Find_Idx].Name.cMainname);
		UNLOCK_CHARACTERINFO(0);
	}else
	{
		return -1;
	}	
	LOCK_CONNECTION(0);
	Find_Idx = FindConnectionByName(mainname);
	UNLOCK_CONNECTION(0);
	if(Find_Idx != -1)
	{		
		send_packet.data.QQState.ID = packet->data.QQState.ID;
		send_packet.data.QQState.Status = packet->data.QQState.Status;		
		server_send_packet_to_one(&Pos_Cn[Find_Idx], &send_packet);	
		return 0;
	}
	return -1;
	*/
}
// -----------------------------------------------------------------------------
void	ServerDoQQGetOtherState(TPOS_CN *cn, TPOS_PACKET *packet) 
{
	static TPOS_PACKET	send_packet;	
	TPOS_EVENT_QQGETOTHERSTATE	EventQQGetOtherState;
	TPOS_EVENT_QQGETOTHERSTATE	EventQQGetOtherStateFromWorld;

	memcpy(&EventQQGetOtherStateFromWorld, packet->data.cBuf, sizeof(TPOS_EVENT_QQGETOTHERSTATE));
	
	send_packet.Header.dwType = QQ_GET_OTHERSTATE;
	send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_QQGETOTHERSTATE);
	
	EventQQGetOtherState.ID = EventQQGetOtherStateFromWorld.ID;
	EventQQGetOtherState.State = EventQQGetOtherStateFromWorld.State;
	memcpy(send_packet.data.cBuf, &EventQQGetOtherState, sizeof(TPOS_EVENT_QQGETOTHERSTATE));
	
	server_send_packet_to_all(&send_packet);		
}
// -----------------------------------------------------------------------------
void	ServerDoQQRequestQueryAddList(TPOS_CN *cn, TPOS_PACKET *packet) 
{
	/*
	static TPOS_PACKET	send_packet;
	int			Find_Id;

	send_packet.Header.dType = QQ_REQUEST_QUERY_ADD_LIST;
	send_packet.Header.dSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_QQ_QD);
	
	LOCK_CHARACTERINFO(0);
	Find_Id = FindCurrentConnectionQQID(cn);
	UNLOCK_CHARACTERINFO(0);		
	memcpy(&send_packet.data.QQQueryData, &packet->data.QQQueryData, sizeof(TPOS_QQ_QD));
	send_packet.data.QQQueryData.RequestID = Find_Id;

	QueuePacket(World,&send_packet,CONNECTED_SERVER_WORLD);

	return 0;	
	*/
}
// -----------------------------------------------------------------------------
void	ServerDoQQRequestQueryOnlineAddList(TPOS_CN *cn, TPOS_PACKET *packet) 
{	
	static TPOS_PACKET					send_packet;
	static TPOS_COMPACKET				send_compacket;		
	TPOS_EVENT_QQREQUESTQUERYONLINELIST	EventQQRequestQueryOnLineList;
	TPOS_EVENT_QQREQUESTQUERYONLINELIST	EventQQRequestQueryOnLineListToWorld;
	int									Find_Id;

	memcpy(&EventQQRequestQueryOnLineList, packet->data.cBuf, sizeof(TPOS_EVENT_QQREQUESTQUERYONLINELIST));

	send_packet.Header.dwType = QQ_REQUEST_QUERY_ONLINE_ADDLIST;
	send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_QQREQUESTQUERYONLINELIST);
	
	LOCK_CHARACTER(0);
	Find_Id = FindCurrentConnectionQQID(cn);
	UNLOCK_CHARACTER(0);		

	EventQQRequestQueryOnLineListToWorld.BookMark = EventQQRequestQueryOnLineList.BookMark;
	EventQQRequestQueryOnLineListToWorld.ZoneIndex = EventQQRequestQueryOnLineList.ZoneIndex;
	EventQQRequestQueryOnLineListToWorld.RequestID = Find_Id;

	memcpy(&send_packet.data.cBuf, &EventQQRequestQueryOnLineListToWorld, sizeof(TPOS_EVENT_QQREQUESTQUERYONLINELIST));	

	CompressPacket(&send_packet, &send_compacket);
	
	QueuePacket(World, &send_compacket, CONNECTED_SERVER_WORLD);
}
// -----------------------------------------------------------------------------
void	ServerDoQQGetQueryAddList(TPOS_CN *cn, TPOS_PACKET *packet) 
{
	static	TPOS_PACKET				send_packet;	
	TPOS_EVENT_QQGETQUERYONLINELIST	EventQQGetQueryOnLineList;
	TPOS_EVENT_QQGETQUERYONLINELIST	EventQQGetQueryOnLineListFromWorld;
	int								Find_Idx;
	char							mainname[32];

	memcpy(&EventQQGetQueryOnLineListFromWorld, packet->data.cBuf, sizeof(TPOS_EVENT_QQGETQUERYONLINELIST));	
	
	send_packet.Header.dwType = QQ_GET_QUERY_ADD_LIST;
	send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_QQGETQUERYONLINELIST);
	LOCK_CHARACTER(0);
	Find_Idx = FindCharacterInfoByQQID(EventQQGetQueryOnLineListFromWorld.RequestID);
	strcpy(mainname, GetCharacterMainName(Find_Idx));
	UNLOCK_CHARACTER(0);

	LOCK_CONNECTION(0);
	Find_Idx = FindConnectionByName(mainname);
	UNLOCK_CONNECTION(0);
	
	EventQQGetQueryOnLineList.BookMark = EventQQGetQueryOnLineListFromWorld.BookMark;
	EventQQGetQueryOnLineList.ZoneIndex = EventQQGetQueryOnLineListFromWorld.ZoneIndex;
	memcpy(EventQQGetQueryOnLineList.QQAddList, 
		   EventQQGetQueryOnLineListFromWorld.QQAddList,
		   sizeof(TPOS_QQ_ADDLIST)*100);

	memcpy(&send_packet.data.cBuf, 
		   &EventQQGetQueryOnLineList, sizeof(TPOS_EVENT_QQGETQUERYONLINELIST));

	server_send_packet_to_one(&Pos_Cn[Find_Idx], &send_packet);	
}
// -----------------------------------------------------------------------------
void	ServerDoQQGetQueryAddListEnd(TPOS_CN *cn, TPOS_PACKET *packet) 
{
	static	TPOS_PACKET				send_packet;	
	TPOS_EVENT_QQGETQUERYONLINELIST	EventQQGetQueryOnLineList;
	TPOS_EVENT_QQGETQUERYONLINELIST	EventQQGetQueryOnLineListFromWorld;
	int								Find_Idx;
	char							mainname[32];

	memcpy(&EventQQGetQueryOnLineListFromWorld, packet->data.cBuf, sizeof(TPOS_EVENT_QQGETQUERYONLINELIST));	
	
	send_packet.Header.dwType = QQ_GET_QUERY_ADD_LIST_END;
	send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_QQGETQUERYONLINELIST);
	LOCK_CHARACTER(0);
	Find_Idx = FindCharacterInfoByQQID(EventQQGetQueryOnLineListFromWorld.RequestID);
	strcpy(mainname, GetCharacterMainName(Find_Idx));
	UNLOCK_CHARACTER(0);

	LOCK_CONNECTION(0);
	Find_Idx = FindConnectionByName(mainname);
	UNLOCK_CONNECTION(0);
	
	EventQQGetQueryOnLineList.BookMark = EventQQGetQueryOnLineListFromWorld.BookMark;
	EventQQGetQueryOnLineList.ZoneIndex = EventQQGetQueryOnLineListFromWorld.ZoneIndex;
	memcpy(EventQQGetQueryOnLineList.QQAddList, 
		   EventQQGetQueryOnLineListFromWorld.QQAddList,
		   sizeof(TPOS_QQ_ADDLIST)*100);

	memcpy(&send_packet.data.cBuf, 
		   &EventQQGetQueryOnLineList, sizeof(TPOS_EVENT_QQGETQUERYONLINELIST));

	server_send_packet_to_one(&Pos_Cn[Find_Idx], &send_packet);	
}
// -----------------------------------------------------------------------------
void	ServerDoQQRequestAddSomeone(TPOS_CN *cn, TPOS_PACKET *packet) 
{
	static	TPOS_PACKET				send_packet;
	static	TPOS_COMPACKET			send_compacket;
	TPOS_EVENT_QQREQUESTADDSOMEONE	EventQQRequestAddSomeone;
	TPOS_EVENT_QQREQUESTADDSOMEONE	EventQQRequestAddSomeoneToWorld;
	int								Find_Id;

	memcpy(&EventQQRequestAddSomeone, packet->data.cBuf, sizeof(TPOS_EVENT_QQREQUESTADDSOMEONE));
	
	send_packet.Header.dwType = QQ_REQUEST_ADD_SOMEONE;
	send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_QQREQUESTADDSOMEONE);
	
	LOCK_CHARACTER(0);
	Find_Id = FindCurrentConnectionQQID(cn);
	UNLOCK_CHARACTER(0);		

	EventQQRequestAddSomeoneToWorld.RequestID = Find_Id;
	EventQQRequestAddSomeoneToWorld.TargetID = EventQQRequestAddSomeone.TargetID;
	//EventQQRequestAddSomeoneToWorld.Relation = EventQQRequestAddSomeone.Relation;	
	EventQQRequestAddSomeoneToWorld.Relation = 0;	

	memcpy(send_packet.data.cBuf, &EventQQRequestAddSomeoneToWorld, sizeof(TPOS_EVENT_QQREQUESTADDSOMEONE));

	CompressPacket(&send_packet, &send_compacket);

	QueuePacket(World, &send_compacket, CONNECTED_SERVER_WORLD);
}
// -----------------------------------------------------------------------------
void	ServerDoQQGetAddSomeone(TPOS_CN *cn, TPOS_PACKET *packet) 
{	
	static TPOS_PACKET			send_packet;
	TPOS_EVENT_QQGETADDSOMEONE	EventQQGetAddSomeone;
	TPOS_EVENT_QQGETADDSOMEONE	EventQQGetAddSomeoneFromWorld;
	int			Find_Idx;
	char		mainname[32];
	int			valid_flag;

	memcpy(&EventQQGetAddSomeoneFromWorld, packet->data.cBuf, sizeof(TPOS_EVENT_QQGETADDSOMEONE));

	valid_flag = 0;
	LOCK_CHARACTER(0);
	Find_Idx = FindCharacterInfoByQQID(EventQQGetAddSomeoneFromWorld.RequestID);
	if(Find_Idx>=0)
	{
		strcpy(mainname, GetCharacterMainName(Find_Idx));
		valid_flag = 1;
	}
	UNLOCK_CHARACTER(0);

	if(valid_flag)
	{
		LOCK_CONNECTION(0);
		Find_Idx = FindConnectionByName(mainname);
		UNLOCK_CONNECTION(0);

		if(Find_Idx >= 0)
		{
			send_packet.Header.dwType = QQ_GET_ADD_SOMEONE;
			send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_QQGETADDSOMEONE);
			
			EventQQGetAddSomeone.Career = EventQQGetAddSomeoneFromWorld.Career;
			strcpy(EventQQGetAddSomeone.MainName, EventQQGetAddSomeoneFromWorld.MainName);
			EventQQGetAddSomeone.Relation = EventQQGetAddSomeoneFromWorld.Relation;
			EventQQGetAddSomeone.TargetID = EventQQGetAddSomeoneFromWorld.TargetID;
			EventQQGetAddSomeone.State = EventQQGetAddSomeoneFromWorld.State;
			EventQQGetAddSomeone.Index = EventQQGetAddSomeoneFromWorld.Index;
			EventQQGetAddSomeone.RequestID = 0;
			
			memcpy(send_packet.data.cBuf, &EventQQGetAddSomeone, sizeof(TPOS_EVENT_QQGETADDSOMEONE));

			server_send_packet_to_one(&Pos_Cn[Find_Idx], &send_packet);	
		}
	}
}
// -----------------------------------------------------------------------------
void	ServerDoQQGetAddGuildFriend(TPOS_CN *cn, TPOS_PACKET *packet) 
{
	/*
	static TPOS_PACKET	send_packet;
	int			Find_Idx;
	char		mainname[32];

	send_packet.Header.dType = QQ_GET_ADD_GUILD_FRIEND;
	send_packet.Header.dSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_QQ_FRIEND);
	
	LOCK_CHARACTERINFO(0);
	Find_Idx = FindCharacterInfoByQQID(packet->data.QQFriend.RequestID);
	strcpy(mainname,CharacterInfo[Find_Idx].Name.cMainname);
	UNLOCK_CHARACTERINFO(0);
	LOCK_CONNECTION(0);
	Find_Idx = FindConnectionByName(mainname);
	UNLOCK_CONNECTION(0);
	memcpy(&send_packet.data.QQFriend, 
		   &packet->data.QQFriend, sizeof(TPOS_QQ_FRIEND));
	server_send_packet_to_one(&Pos_Cn[Find_Idx], &send_packet);	

	return 0;
	*/
}
// -----------------------------------------------------------------------------
void	ServerDoQQFriendLogin(TPOS_CN *cn, TPOS_PACKET *packet) 
{
	/*
	static TPOS_PACKET	send_packet;

	send_packet.Header.dType = QQ_FRIEND_LOGIN;
	send_packet.Header.dSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_QQ_FRIEND_DB);
	send_packet.data.QQFriendDB.ID = packet->data.QQFriendDB.ID;

	server_send_packet_to_all(&send_packet);
	return 0;
	*/
}
// -----------------------------------------------------------------------------
void	ServerDoQQRequestQuerySomeone(TPOS_CN *cn, TPOS_PACKET *packet) 
{	
	static	TPOS_PACKET					send_packet;
	static	TPOS_COMPACKET				send_compacket;
	TPOS_EVENT_QQREQUESTQUERYSOMEONE	EventQQRequestQuerySomeone;
	TPOS_EVENT_QQREQUESTQUERYSOMEONE	EventQQRequestQuerySomeoneToWorld;
	int									Find_Id;

	memcpy(&EventQQRequestQuerySomeone, packet->data.cBuf, sizeof(TPOS_EVENT_QQREQUESTQUERYSOMEONE));

	send_packet.Header.dwType = QQ_REQUEST_QUERY_SOMEONE;
	send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_QQREQUESTQUERYSOMEONE);
	
	LOCK_CHARACTER(0);
	Find_Id = FindCurrentConnectionQQID(cn);
	UNLOCK_CHARACTER(0);		

	EventQQRequestQuerySomeoneToWorld.RequestID = Find_Id;
	EventQQRequestQuerySomeoneToWorld.TargetID = EventQQRequestQuerySomeone.TargetID;
	
	memcpy(send_packet.data.cBuf, &EventQQRequestQuerySomeoneToWorld, sizeof(TPOS_EVENT_QQREQUESTQUERYSOMEONE));

	CompressPacket(&send_packet, &send_compacket);

	QueuePacket(World, &send_compacket, CONNECTED_SERVER_WORLD);
}
// -----------------------------------------------------------------------------
void	ServerDoQQGetQuerySomeone(TPOS_CN *cn, TPOS_PACKET *packet) 
{	
	static TPOS_PACKET				send_packet;
	TPOS_EVENT_QQGETQUERYSOMEONE	EventQQGetQuerySomeone;
	TPOS_EVENT_QQGETQUERYSOMEONE	EventQQGetQuerySomeoneFromWorld;
	int								Find_Idx;
	char							mainname[32];

	memcpy(&EventQQGetQuerySomeoneFromWorld, packet->data.cBuf, sizeof(TPOS_EVENT_QQGETQUERYSOMEONE));
	
	send_packet.Header.dwType = QQ_GET_QUERY_SOMEONE;
	send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_QQGETQUERYSOMEONE);
	
	LOCK_CHARACTER(0);
	Find_Idx = FindCharacterInfoByQQID(EventQQGetQuerySomeoneFromWorld.RequestID);
	strcpy(mainname, GetCharacterMainName(Find_Idx));
	UNLOCK_CHARACTER(0);
	
	LOCK_CONNECTION(0);
	Find_Idx = FindConnectionByName(mainname);
	UNLOCK_CONNECTION(0);
	memcpy(&EventQQGetQuerySomeone, &EventQQGetQuerySomeoneFromWorld, sizeof(TPOS_EVENT_QQGETQUERYSOMEONE));
	EventQQGetQuerySomeone.RequestID = 0;

	memcpy(send_packet.data.cBuf, &EventQQGetQuerySomeone, sizeof(TPOS_EVENT_QQGETQUERYSOMEONE));

	server_send_packet_to_one(&Pos_Cn[Find_Idx], &send_packet);	
}
// -----------------------------------------------------------------------------
void	ServerDoQQSend2OneMsg(TPOS_CN *cn, TPOS_PACKET *packet) 
{	
	static TPOS_PACKET					send_packet;
	static TPOS_COMPACKET				send_compacket;
	TPOS_EVENT_QQREQUESTSENDMSGTOONE	EventQQRequestSendMsgToOne;
	TPOS_EVENT_QQREQUESTSENDMSGTOONE	EventQQRequestSendMsgToOneToWorld;
	int									Find_Id;

	memcpy(&EventQQRequestSendMsgToOne, packet->data.cBuf, sizeof(TPOS_EVENT_QQREQUESTSENDMSGTOONE));
	send_packet.Header.dwType = QQ_SEND_2ONE_MSG;
	send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_QQREQUESTSENDMSGTOONE);

	LOCK_CHARACTER(0);
	Find_Id = FindCurrentConnectionQQID(cn);
	UNLOCK_CHARACTER(0);		
	EventQQRequestSendMsgToOneToWorld.SendID = Find_Id;
	EventQQRequestSendMsgToOneToWorld.RecvID = EventQQRequestSendMsgToOne.RecvID;
	strcpy(EventQQRequestSendMsgToOneToWorld.Msg, EventQQRequestSendMsgToOne.Msg);
	
	memcpy(send_packet.data.cBuf,&EventQQRequestSendMsgToOneToWorld, sizeof(TPOS_EVENT_QQREQUESTSENDMSGTOONE));

	CompressPacket(&send_packet, &send_compacket);

	QueuePacket(World, &send_compacket, CONNECTED_SERVER_WORLD);		
}
// -----------------------------------------------------------------------------
void	ServerDoQQSend2SomeMsg(TPOS_CN *cn, TPOS_PACKET *packet) 
{	
	static TPOS_PACKET					send_packet;
	static TPOS_COMPACKET				send_compacket;
	TPOS_EVENT_QQREQUESTSENDMSGTOSOME	EventQQRequestSendMsgToSome;
	TPOS_EVENT_QQREQUESTSENDMSGTOSOME	EventQQRequestSendMsgToSomeToWorld;
	int									Find_Id;

	memcpy(&EventQQRequestSendMsgToSome, packet->data.cBuf, sizeof(TPOS_EVENT_QQREQUESTSENDMSGTOSOME));
	send_packet.Header.dwType = QQ_SEND_2ONE_MSG;
	send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_QQREQUESTSENDMSGTOSOME);

	LOCK_CHARACTER(0);
	Find_Id = FindCurrentConnectionQQID(cn);
	UNLOCK_CHARACTER(0);		
	EventQQRequestSendMsgToSomeToWorld.SendID = Find_Id;
	memcpy(EventQQRequestSendMsgToSomeToWorld.RecvID, 
		   EventQQRequestSendMsgToSome.RecvID,
		   sizeof(ULONG) * 50);
	strcpy(EventQQRequestSendMsgToSomeToWorld.Msg, EventQQRequestSendMsgToSome.Msg);
	
	memcpy(send_packet.data.cBuf,&EventQQRequestSendMsgToSomeToWorld, sizeof(TPOS_EVENT_QQREQUESTSENDMSGTOSOME));

	CompressPacket(&send_packet, &send_compacket);

	QueuePacket(World, &send_compacket, CONNECTED_SERVER_WORLD);		
}
// -----------------------------------------------------------------------------
void	ServerDoQQGetMsg(TPOS_CN *cn, TPOS_PACKET *packet) 
{	
	static TPOS_PACKET	send_packet;
	TPOS_EVENT_QQGETMSG	EventQQGetMsg;
	TPOS_EVENT_QQGETMSG	EventQQGetMsgFromWorld;
	int					Find_Idx;
	char				mainname[32];

	memcpy(&EventQQGetMsgFromWorld, packet->data.cBuf, sizeof(TPOS_EVENT_QQGETMSG));
	send_packet.Header.dwType = QQ_GET_MSG;
	send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_QQGETMSG);
	
	LOCK_CHARACTER(0);
	Find_Idx = FindCharacterInfoByQQID(EventQQGetMsgFromWorld.RecvID);
	if(Find_Idx!=-1)
	{	
		strcpy(mainname, GetCharacterMainName(Find_Idx));
	}
	UNLOCK_CHARACTER(0);

	if(Find_Idx != -1)
	{		
		LOCK_CONNECTION(0);
		Find_Idx = FindConnectionByName(mainname);
		UNLOCK_CONNECTION(0);
		
		EventQQGetMsg.RecvID = EventQQGetMsgFromWorld.RecvID;
		EventQQGetMsg.SendID = EventQQGetMsgFromWorld.SendID;
		strcpy(EventQQGetMsg.Msg, EventQQGetMsgFromWorld.Msg);
		
		memcpy(send_packet.data.cBuf, &EventQQGetMsg, sizeof(TPOS_EVENT_QQGETMSG));
		
		server_send_packet_to_one(&Pos_Cn[Find_Idx], &send_packet);
	}
}
// -----------------------------------------------------------------------------
void	ServerDoQQRequestPlayerCount(TPOS_CN *cn, TPOS_PACKET *packet) 
{	
	static TPOS_PACKET				send_packet;
	static TPOS_COMPACKET			send_compacket;
	TPOS_EVENT_QQREQUESTPLAYERCOUNT	EventQQRequestPlayerCount;
	TPOS_EVENT_QQREQUESTPLAYERCOUNT	EventQQRequestPlayerCountToWorld;
	int								Find_Id;

	memcpy(&EventQQRequestPlayerCount, packet->data.cBuf, sizeof(TPOS_EVENT_QQREQUESTPLAYERCOUNT));
	
	send_packet.Header.dwType = QQ_REQUEST_PLAYER_COUNT;
	send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_QQREQUESTPLAYERCOUNT);

	LOCK_CHARACTER(0);
	Find_Id = FindCurrentConnectionQQID(cn);
	UNLOCK_CHARACTER(0);

	EventQQRequestPlayerCountToWorld.RequestID = Find_Id;	

	memcpy(send_packet.data.cBuf, &EventQQRequestPlayerCountToWorld, sizeof(TPOS_EVENT_QQREQUESTPLAYERCOUNT));

	CompressPacket(&send_packet, &send_compacket);

	QueuePacket(World, &send_compacket, CONNECTED_SERVER_WORLD);
}
// -----------------------------------------------------------------------------
void	ServerDoQQGetPlayerCount(TPOS_CN *cn, TPOS_PACKET *packet) 
{	
	static	TPOS_PACKET			send_packet;
	TPOS_EVENT_QQGETPLAYERCOUNT	EventQQGetPlayerCount;
	TPOS_EVENT_QQGETPLAYERCOUNT	EventQQGetPlayerCountFromWorld;
	int							Find_Idx;
	char						mainname[32];

	memcpy(&EventQQGetPlayerCountFromWorld, packet->data.cBuf, sizeof(TPOS_EVENT_QQGETPLAYERCOUNT));
	send_packet.Header.dwType = QQ_GET_PLAYER_COUNT;
	send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_QQGETPLAYERCOUNT);

	LOCK_CHARACTER(0);
	Find_Idx = FindCharacterInfoByQQID(EventQQGetPlayerCountFromWorld.RequestID);
	strcpy(mainname, GetCharacterMainName(Find_Idx));
	UNLOCK_CHARACTER(0);
	LOCK_CONNECTION(0);
	Find_Idx = FindConnectionByName(mainname);
	UNLOCK_CONNECTION(0);

	EventQQGetPlayerCount.RequestID = 0;
	EventQQGetPlayerCount.PlayerCount = EventQQGetPlayerCountFromWorld.PlayerCount;

	memcpy(send_packet.data.cBuf, &EventQQGetPlayerCount, sizeof(TPOS_EVENT_QQGETPLAYERCOUNT));

	server_send_packet_to_one(&Pos_Cn[Find_Idx], &send_packet);	
}
// -----------------------------------------------------------------------------
void	ServerDoQQRequestDelFriend(TPOS_CN *cn, TPOS_PACKET *packet) 
{
	TPOS_EVENT_QQREQUESTDELFRIEND	EventQQRequestDelFriend;
	TPOS_EVENT_QQREQUESTDELFRIEND	EventQQRequestDelFriendToWorld;
	static TPOS_PACKET				send_packet;
	static TPOS_COMPACKET			send_compacket;
	int								Find_Id;

	memcpy(&EventQQRequestDelFriend, packet->data.cBuf, sizeof(TPOS_EVENT_QQREQUESTDELFRIEND));

	send_packet.Header.dwType = QQ_REQUEST_DEL_FRIEND;
	send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_QQREQUESTDELFRIEND);

	LOCK_CHARACTER(0);
	Find_Id = FindCurrentConnectionQQID(cn);
	UNLOCK_CHARACTER(0);		
	EventQQRequestDelFriendToWorld.RequestID = Find_Id;	
	EventQQRequestDelFriendToWorld.TargetID = EventQQRequestDelFriend.TargetID;
	memcpy(send_packet.data.cBuf, &EventQQRequestDelFriendToWorld, sizeof(TPOS_EVENT_QQREQUESTDELFRIEND));

	CompressPacket(&send_packet, &send_compacket);

	QueuePacket(World, &send_compacket, CONNECTED_SERVER_WORLD);	
}
// -----------------------------------------------------------------------------
void	ServerDoQQGetDelFriend(TPOS_CN *cn, TPOS_PACKET *packet)
{
	TPOS_EVENT_QQGETDELFRIEND	EventQQGetDelFriend;
	TPOS_EVENT_QQGETDELFRIEND	EventQQGetDelFriendFromWorld;
	static TPOS_PACKET			send_packet;	
	int							Find_Idx;
	char						mainname[32];

	memcpy(&EventQQGetDelFriendFromWorld, packet->data.cBuf, sizeof(TPOS_EVENT_QQGETDELFRIEND));

	send_packet.Header.dwType = QQ_GET_DEL_FRIEND;
	send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_QQGETDELFRIEND);
	
	LOCK_CHARACTER(0);
	Find_Idx = FindCharacterInfoByQQID(EventQQGetDelFriendFromWorld.RequestID);
	strcpy(mainname, GetCharacterMainName(Find_Idx));
	UNLOCK_CHARACTER(0);
	LOCK_CONNECTION(0);
	Find_Idx = FindConnectionByName(mainname);
	UNLOCK_CONNECTION(0);

	EventQQGetDelFriend.RequestID = 0;
	EventQQGetDelFriend.TargetID = EventQQGetDelFriendFromWorld.TargetID;
	memcpy(send_packet.data.cBuf, &EventQQGetDelFriend, sizeof(TPOS_EVENT_QQGETDELFRIEND));
	
	server_send_packet_to_one(&Pos_Cn[Find_Idx], &send_packet);		
}
// -----------------------------------------------------------------------------
void	ServerDoQQRequestDelGuildFriend(TPOS_CN *cn, TPOS_PACKET *packet) 
{
	TPOS_EVENT_QQREQUESTDELGUILDFRIEND	EventQQRequestDelGuildFriend;
	TPOS_EVENT_QQREQUESTDELGUILDFRIEND	EventQQRequestDelGuildFriendToWorld;
	static TPOS_PACKET				send_packet;
	static TPOS_COMPACKET			send_compacket;
	int								Find_Id;

	memcpy(&EventQQRequestDelGuildFriend, packet->data.cBuf, sizeof(TPOS_EVENT_QQREQUESTDELGUILDFRIEND));

	send_packet.Header.dwType = QQ_REQUEST_DEL_GUILD_FRIEND;
	send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_QQREQUESTDELGUILDFRIEND);

	LOCK_CHARACTER(0);
	Find_Id = FindCurrentConnectionQQID(cn);
	UNLOCK_CHARACTER(0);		
	EventQQRequestDelGuildFriendToWorld.RequestID = Find_Id;	
	EventQQRequestDelGuildFriendToWorld.TargetID = EventQQRequestDelGuildFriend.TargetID;
	memcpy(send_packet.data.cBuf, &EventQQRequestDelGuildFriendToWorld, sizeof(TPOS_EVENT_QQREQUESTDELGUILDFRIEND));

	CompressPacket(&send_packet, &send_compacket);

	QueuePacket(World, &send_compacket, CONNECTED_SERVER_WORLD);	
}
// -----------------------------------------------------------------------------
void	ServerDoQQGetDelGuildFriend(TPOS_CN *cn, TPOS_PACKET *packet) 
{
	TPOS_EVENT_QQGETDELGUILDFRIEND	EventQQGetDelGuildFriend;
	TPOS_EVENT_QQGETDELGUILDFRIEND	EventQQGetDelGuildFriendFromWorld;
	static TPOS_PACKET				send_packet;	
	int								Find_Idx;
	char							mainname[32];

	memcpy(&EventQQGetDelGuildFriendFromWorld, packet->data.cBuf, sizeof(TPOS_EVENT_QQGETDELGUILDFRIEND));

	send_packet.Header.dwType = QQ_GET_DEL_FRIEND;
	send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_QQGETDELGUILDFRIEND);
	
	LOCK_CHARACTER(0);
	Find_Idx = FindCharacterInfoByQQID(EventQQGetDelGuildFriendFromWorld.RequestID);
	strcpy(mainname, GetCharacterMainName(Find_Idx));
	UNLOCK_CHARACTER(0);
	LOCK_CONNECTION(0);
	Find_Idx = FindConnectionByName(mainname);
	UNLOCK_CONNECTION(0);

	EventQQGetDelGuildFriend.RequestID = 0;
	EventQQGetDelGuildFriend.TargetID = EventQQGetDelGuildFriendFromWorld.TargetID;
	memcpy(send_packet.data.cBuf, &EventQQGetDelGuildFriend, sizeof(TPOS_EVENT_QQGETDELGUILDFRIEND));
	
	server_send_packet_to_one(&Pos_Cn[Find_Idx], &send_packet);	
}
// -----------------------------------------------------------------------------
void	ServerDoQQRequestTransferItem(TPOS_CN *cn, TPOS_PACKET *packet)
{
	TPOS_EVENT_QQREQUESTTRANSFERITEM			EventQQRequestTransferItem;
	TPOS_EVENT_QQREQUESTTRANSFERITEMFROMWORLD	EventQQRequestTransferItemToWorld;
	TPOS_EVENT_QQTRANSFERITEMFAIL				EventQQTransferItemFail;
	static	TPOS_PACKET					send_packet;
	static	TPOS_COMPACKET				send_compacket;	
	int									Find_Id;
	SLONG								npc_no;
	int									i;
	TPOS_ITEM							item;
	int									trans_ok;
	SLONG								ret; 

	memcpy(&EventQQRequestTransferItem, packet->data.cBuf, sizeof(TPOS_EVENT_QQREQUESTTRANSFERITEM));

	trans_ok = FALSE;

	send_packet.Header.dwType = QQ_REQUEST_TRANSFER_ITEM;
	send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_QQREQUESTTRANSFERITEMFROMWORLD);
	
	LOCK_CHARACTER(0);
	npc_no = FindCharacterByMainName(cn->User.cId);
	Find_Id = FindCurrentConnectionQQID(cn);
	EventQQRequestTransferItemToWorld.RequestID = Find_Id;	
	EventQQRequestTransferItemToWorld.TargetID = EventQQRequestTransferItem.TargetID;
	for(i = 0;i < MAX_CHARACTER_TRANS_ITEMS;i++)
	{
		GetCharacterTransItem(npc_no, i, &item);
		EventQQRequestTransferItemToWorld.TransItem[i] = item;
		ret = IsItemNone(&item);
		if(ret == FALSE)trans_ok = TRUE;
	}	
	UNLOCK_CHARACTER(0);				

	if(trans_ok == TRUE)
	{		
		memcpy(send_packet.data.cBuf, &EventQQRequestTransferItemToWorld, sizeof(TPOS_EVENT_QQREQUESTTRANSFERITEMFROMWORLD));	
		CompressPacket(&send_packet, &send_compacket);
		QueuePacket(World, &send_compacket, CONNECTED_SERVER_WORLD);	
	}else
	{
		// 如果傳送欄物品都為空 傳送物品失敗
		send_packet.Header.dwType = QQ_TRANSFER_ITEM_FAIL;
		send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_QQTRANSFERITEMFAIL);
		EventQQTransferItemFail.RequestID = EventQQRequestTransferItem.RequestID;
		EventQQTransferItemFail.TargetID = EventQQRequestTransferItem.TargetID;

		server_send_packet_to_one(cn, &send_packet);
	}
}
// -----------------------------------------------------------------------------
void	ServerDoQQRequestTransferItemFromWorld(TPOS_CN *cn, TPOS_PACKET *packet)
{	
	TPOS_EVENT_QQREQUESTTRANSFERITEMFROMWORLD	EventQQRequestTransferItemFromWorld;
	TPOS_EVENT_QQGETTRANSFERITEM		EventQQGetTransferItem;
	TPOS_EVENT_QQTRANSFERITEMOK			EventQQTransferItemOK;
	TPOS_EVENT_QQTRANSFERITEMFAIL		EventQQTransferItemFail;
	TPOS_EVENT_NOTIFYSETTRANSITEM		EventNotifySetTransItem;
	static	TPOS_PACKET					send_packet;
	static	TPOS_COMPACKET				send_compacket;		
	SLONG								dest_npc;	
	TPOS_ITEM							item;
	int									i, Find_Idx;;
	SLONG								ret;
	int									trans_ok;
	char								mainname[32];

	memcpy(&EventQQRequestTransferItemFromWorld, packet->data.cBuf, sizeof(TPOS_EVENT_QQREQUESTTRANSFERITEMFROMWORLD));

	LOCK_CHARACTER(0);
	dest_npc = FindCharacterInfoByQQID(EventQQRequestTransferItemFromWorld.TargetID);	
	UNLOCK_CHARACTER(0);
	
	// 只要對方傳送物品欄有一個物品就不能傳送
	for(i = 0;i < MAX_CHARACTER_TRANS_ITEMS;i++)
	{
		LOCK_CHARACTER(0);
		GetCharacterTransItem(dest_npc, i, &item);
		UNLOCK_CHARACTER(0);
		ret = IsItemNone(&item);
		if(ret == FALSE)
		{
			trans_ok = FALSE;
			break;
		}
		trans_ok = TRUE;
	}		
	if(trans_ok == TRUE)
	{
		LOCK_CHARACTER(0);
		// 送給目標玩家 收取傳送物品的消息		
		Find_Idx = FindCharacterInfoByQQID(EventQQRequestTransferItemFromWorld.TargetID);
		strcpy(mainname, GetCharacterMainName(Find_Idx));			
		UNLOCK_CHARACTER(0);
		
		LOCK_CONNECTION(0);
		Find_Idx = FindConnectionByName(mainname);
		UNLOCK_CONNECTION(0);	

		// 將傳送物品給對方
		for(i = 0;i < MAX_CHARACTER_TRANS_ITEMS;i++)
		{
			LOCK_CHARACTER(0);
			SetCharacterTransItem(dest_npc, i, &EventQQRequestTransferItemFromWorld.TransItem[i]);
			UNLOCK_CHARACTER(0);		
			// 設定傳送物品
			send_packet.Header.dwType = NOTIFY_SET_TRANS_ITEM;
			send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYSETTRANSITEM);
			EventNotifySetTransItem.Item = EventQQRequestTransferItemFromWorld.TransItem[i];
			EventNotifySetTransItem.TransIndex = i;
			memcpy(send_packet.data.cBuf, &EventNotifySetTransItem, sizeof(TPOS_EVENT_NOTIFYSETTRANSITEM));
			server_send_packet_to_one(&Pos_Cn[Find_Idx], &send_packet);
		}
		// 送出取得物品消息
		send_packet.Header.dwType = QQ_GET_TRANSFER_ITEM;
		send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_QQGETTRANSFERITEM);
		EventQQGetTransferItem.RequestID = EventQQRequestTransferItemFromWorld.RequestID;
		EventQQGetTransferItem.TargetID = EventQQRequestTransferItemFromWorld.TargetID;		
		memcpy(send_packet.data.cBuf, &EventQQGetTransferItem, sizeof(TPOS_EVENT_QQGETTRANSFERITEM));		
		server_send_packet_to_one(&Pos_Cn[Find_Idx], &send_packet);

		// 回傳傳送物品 OK 消息給 World
		send_packet.Header.dwType = QQ_TRANSFER_ITEM_OK;
		send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_QQTRANSFERITEMOK);
		EventQQTransferItemOK.RequestID = EventQQRequestTransferItemFromWorld.RequestID;
		EventQQTransferItemOK.TargetID = EventQQRequestTransferItemFromWorld.TargetID;		
		memcpy(send_packet.data.cBuf, &EventQQTransferItemOK, sizeof(TPOS_EVENT_QQTRANSFERITEMOK));
	}
	else
	{
		// 回傳傳送物品 FAIL 消息給 World
		send_packet.Header.dwType = QQ_TRANSFER_ITEM_FAIL;
		send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_QQTRANSFERITEMFAIL);
		EventQQTransferItemFail.RequestID = EventQQRequestTransferItemFromWorld.RequestID;
		EventQQTransferItemFail.TargetID = EventQQRequestTransferItemFromWorld.TargetID;
		memcpy(send_packet.data.cBuf, &EventQQTransferItemFail, sizeof(TPOS_EVENT_QQTRANSFERITEMFAIL));
	}	
	CompressPacket(&send_packet, &send_compacket);

	QueuePacket(World, &send_compacket, CONNECTED_SERVER_WORLD);		
}
// -----------------------------------------------------------------------------
void	ServerDoQQTransferItemOKFromWorld(TPOS_CN *cn, TPOS_PACKET *packet)
{
	static	TPOS_PACKET						send_packet;
	TPOS_EVENT_QQTRANSFERITEMOK				EventQQTransferItemOK;
	TPOS_EVENT_QQTRANSFERITEMOKFROMWORLD	EventQQTransferItemOKFromWorld;
	TPOS_EVENT_NOTIFYSETTRANSITEM			EventNotifySetTransItem;	
	SLONG									src_npc;
	int										i, Find_Idx;
	TPOS_ITEM								item;
	char									mainname[32];

	memcpy(&EventQQTransferItemOKFromWorld, packet->data.cBuf, sizeof(TPOS_EVENT_QQTRANSFERITEMOKFROMWORLD));
	LOCK_CHARACTER(0);
	src_npc = FindCharacterInfoByQQID(EventQQTransferItemOKFromWorld.RequestID);	
	UNLOCK_CHARACTER(0);
	
	LOCK_CHARACTER(0);
	Find_Idx = FindCharacterInfoByQQID(EventQQTransferItemOKFromWorld.RequestID);
	strcpy(mainname, GetCharacterMainName(Find_Idx));	
	UNLOCK_CHARACTER(0);

	LOCK_CONNECTION(0);
	Find_Idx = FindConnectionByName(mainname);
	UNLOCK_CONNECTION(0);	
	SetItemNone(&item);	
	for(i = 0;i < MAX_CHARACTER_TRANS_ITEMS;i++)
	{
		// 清空自己身上傳送欄物品
		LOCK_CHARACTER(0);
		SetCharacterTransItem(src_npc, i, &item);
		UNLOCK_CHARACTER(0);
		send_packet.Header.dwType = NOTIFY_SET_TRANS_ITEM;
		send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYSETTRANSITEM);
		EventNotifySetTransItem.Item = item;
		EventNotifySetTransItem.TransIndex = i;
		memcpy(send_packet.data.cBuf, &EventNotifySetTransItem, sizeof(TPOS_EVENT_NOTIFYSETTRANSITEM));
		server_send_packet_to_one(&Pos_Cn[Find_Idx], &send_packet);
	}		
	
	// 傳送OK
	send_packet.Header.dwType = QQ_TRANSFER_ITEM_OK;
	send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_QQTRANSFERITEMOK);
	EventQQTransferItemOK.RequestID = EventQQTransferItemOKFromWorld.RequestID;
	EventQQTransferItemOK.TargetID = EventQQTransferItemOKFromWorld.TargetID;
	memcpy(send_packet.data.cBuf, &EventQQTransferItemOK, sizeof(TPOS_EVENT_QQTRANSFERITEMOK));
	server_send_packet_to_one(&Pos_Cn[Find_Idx], &send_packet);
}
// -----------------------------------------------------------------------------
void	ServerDoQQTransferItemFailFromWorld(TPOS_CN *cn, TPOS_PACKET *packet)
{
	static	TPOS_PACKET						send_packet;
	TPOS_EVENT_QQTRANSFERITEMFAIL			EventQQTransferItemFail;
	TPOS_EVENT_QQTRANSFERITEMFAILFROMWORLD	EventQQTransferItemFailFromWorld;
	int										Find_Idx;
	char									mainname[32];

	memcpy(&EventQQTransferItemFailFromWorld, packet->data.cBuf, sizeof(TPOS_EVENT_QQTRANSFERITEMFAILFROMWORLD));
	
	LOCK_CHARACTER(0);	
	Find_Idx = FindCharacterInfoByQQID(EventQQTransferItemFailFromWorld.RequestID);
	strcpy(mainname, GetCharacterMainName(Find_Idx));	
	UNLOCK_CHARACTER(0);

	LOCK_CONNECTION(0);
	Find_Idx = FindConnectionByName(mainname);
	UNLOCK_CONNECTION(0);	
	
	// 傳送失敗
	send_packet.Header.dwType = QQ_TRANSFER_ITEM_FAIL;
	send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_QQTRANSFERITEMFAIL);
	EventQQTransferItemFail.RequestID = EventQQTransferItemFailFromWorld.RequestID;
	EventQQTransferItemFail.TargetID = EventQQTransferItemFailFromWorld.TargetID;
	memcpy(send_packet.data.cBuf, &EventQQTransferItemFail, sizeof(TPOS_EVENT_QQTRANSFERITEMFAIL));
	server_send_packet_to_one(&Pos_Cn[Find_Idx], &send_packet);
}
// -----------------------------------------------------------------------------
void	ServerDoPlayerLogin(TPOS_CN *cn, TPOS_PACKET *packet) 
{
	TPOS_DB_CHARACTER			DbCharacter;	
	TPOS_EVENT_ZONELOGINOK		EventZoneLoginOK;
	TPOS_EVENT_PLAYERJOIN		EventPlayerJoin;
	TPOS_EVENT_LOGIN			EventLogin;
	TPOS_EVENT_QQPLAYERLOGIN	EventQQPlayerLogin;	
	TPOS_EVENT_QQPLAYERLOGOUT	EventQQPlayerLogout;	
    BOOL						odbcRet = FALSE;
    static TPOS_PACKET			send_packet;
	static TPOS_COMPACKET		send_compacket;
    char						mainname[32];
	char						account[32];
	int							npc_no;	
	int							cn_no;
	ULONG						qq_id;
	int							i;

	memcpy(&EventLogin, packet->data.cBuf, sizeof(TPOS_EVENT_LOGIN));
    strcpy(mainname, EventLogin.cId);

	memset(&DbCharacter, 0x0, sizeof(TPOS_DB_CHARACTER));
    odbcRet = GetRecordFromCharacterDBByMainName(&DbCharacter, mainname);
    if(odbcRet == FALSE)
    {
        send_packet.Header.dwType = ZONE_LOGIN_ERRORID;
        send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER);
        server_send_packet_to_one(cn, &send_packet);
		
#ifdef  DEBUG_MSG
        struct in_addr  debug_sin_addr;

        LOCK_CONNECTION(0);
        debug_sin_addr = cn->Addr.sin_addr;
        UNLOCK_CONNECTION(0);		

        SaveWorkToLog(mainname, inet_ntoa(debug_sin_addr), "PLAYER_LOGIN_ERRORID");		
#endif//DEBUG_MSG
		return;        
    }
    else
    {
        int  t;
        BOOL b = FALSE;
		strcpy(account, DbCharacter.ID);
		// 檢查是否有相同帳號登入 
		LOCK_CHARACTER(0);
		t = FindPlayerCharacterInfoByAccount(account);
		UNLOCK_CHARACTER(0);
		if(t >=0 )
		{
			char	tempmainname[32];
			npc_no = t;			
			LOCK_CHARACTER(0);
			strcpy(tempmainname, GetCharacterMainName(npc_no));
			qq_id = GetCharacterQQID(npc_no);
			UNLOCK_CHARACTER(0);
			LOCK_CONNECTION(0);				
			cn_no = FindOldConnectionByName(tempmainname, cn->dwSocket);			
			if(cn_no >= 0)
			{				
				// 送出被重複登入的消息給玩家
				send_packet.Header.dwType = ZONE_LOGIN_REPEAT;			
				send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER);
				SendRepeatLoginedPlayer(cn_no, &send_packet);

				CloseOneConnection(&Pos_Cn[cn_no]);								
			}
			UNLOCK_CONNECTION(0);
			// QQ 離線
			send_packet.Header.dwType = QQ_PLAYER_LOGOUT;
			send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_QQPLAYERLOGOUT);		
			EventQQPlayerLogout.QQID = qq_id;
			memcpy(send_packet.data.cBuf, &EventQQPlayerLogout, sizeof(TPOS_EVENT_QQPLAYERLOGOUT));
			CompressPacket(&send_packet, &send_compacket);
			QueuePacket(World, &send_compacket, CONNECTED_SERVER_WORLD);
			//通知所有玩家該人離線
			SendPlayerExitToAll(t);
			LOCK_CHARACTER(0);
			ClearOneCharacter(t);
			BadConnect[t] = FALSE;
			UNLOCK_CHARACTER(0);			
			// 更新該區域玩家數目
			if(dwOnlineCounter > 0)dwOnlineCounter--;
			SendRefreshZoneInfoToWorld();
		}

		// 檢查是否有相同角色登入
		LOCK_CHARACTER(0);
        t = FindPlayerCharacterInfoByMainName(mainname);
		UNLOCK_CHARACTER(0);
		if(t >=0 )
		{
			npc_no = t;			
			LOCK_CONNECTION(0);				
			cn_no = FindOldConnectionByName(mainname, cn->dwSocket);			
			if(cn_no >= 0)
			{					
				// 送出被重複登入的消息給玩家
				send_packet.Header.dwType = ZONE_LOGIN_REPEAT;			
				send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER);
				SendRepeatLoginedPlayer(cn_no, &send_packet);

				CloseOneConnection(&Pos_Cn[cn_no]);								
			}
			UNLOCK_CONNECTION(0);
			SendPlayerExitToAll(t);
			LOCK_CHARACTER(0);
			ClearOneCharacter(t);
			BadConnect[t] = FALSE;
			UNLOCK_CHARACTER(0);			
			if(dwOnlineCounter > 0)dwOnlineCounter--;
			SendRefreshZoneInfoToWorld();
		}		
		// 將登入的玩家加入連接
		LOCK_CONNECTION(0);
		strcpy(cn->User.cId, mainname);
		UNLOCK_CONNECTION(0);
		//找出可用的 Zone Character 陣列空間
		LOCK_CHARACTER(0);
		t = FindUsablePlayerCharacterInfo();
		UNLOCK_CHARACTER(0);
		if(t >= 0)
		{
			npc_no = t;
			LOCK_CHARACTER(0);
			ClearOneCharacter(npc_no);
			UNLOCK_CHARACTER(0);
		}		
		//改變玩家當前的Doing Kind
		DbCharacter.DoingKind = DOING_KIND_CHANGEMAP;		
				
		//將讀取到的玩家之前存的資料載入到當前內存玩家列表中
		LOCK_CHARACTER(0);
		ConvertDBCharacterDataToZoneCharacter(npc_no, &DbCharacter);								
		switch(ZoneType)
		{		
		case CITY_NEWBIE:
		case CITY_BIRTH:		
		case FIELD_NEWBIE:
		case FIELD_BIRTH:
			SetCharacterOnFightState(npc_no, FALSE);
			SetCharacterOnTheSea(npc_no, FALSE);
			EventZoneLoginOK.data.BitState = GetCharacterBitState(npc_no);							
			SetCharacterFileIndex(npc_no, DbCharacter.LandFileIndex);
			EventZoneLoginOK.data.FileIndex = DbCharacter.LandFileIndex;
			break;		
		case CITY_NORMAL:
		case CITY_PK:
		case CITY_FINDGOLD:
		case FIELD_NORMAL:		
		case FIELD_PK:
		case FIELD_FINDGOLD:		
			SetCharacterOnFightState(npc_no, TRUE);
			SetCharacterOnTheSea(npc_no, FALSE);
			EventZoneLoginOK.data.BitState = GetCharacterBitState(npc_no);							
			SetCharacterFileIndex(npc_no, DbCharacter.LandFileIndex);
			EventZoneLoginOK.data.FileIndex = DbCharacter.LandFileIndex;
			break;		
		case SAIL_BIRTH:
		case SAIL_NEWBIE:
			SetCharacterOnFightState(npc_no, FALSE);
			SetCharacterOnTheSea(npc_no, TRUE);
			EventZoneLoginOK.data.BitState = GetCharacterBitState(npc_no);								
			SetCharacterDoingKind(npc_no, DOING_KIND_SEA_IDLE);
			EventZoneLoginOK.data.DoingKind = DOING_KIND_SEA_IDLE;
			SetCharacterFileIndex(npc_no, DbCharacter.SeaFileIndex);
			EventZoneLoginOK.data.FileIndex = DbCharacter.SeaFileIndex;
			SetCharacterShipSpeedX(npc_no, 0);			
			EventZoneLoginOK.data.FSpeedX = 0;			
			SetCharacterShipSpeedY(npc_no, 0);
			EventZoneLoginOK.data.FSpeedY = 0;			
			SetCharacterShipDegreeDir(npc_no, 0);
			EventZoneLoginOK.data.DegreeDir = 0;
			SetCharacterShipSailSize(npc_no, 100);
			EventZoneLoginOK.data.SailSize = 100;
			SetCharacterShipWeight(npc_no, 0);
			EventZoneLoginOK.data.Weight = 0;
			SetCharacterShipTurn(npc_no, 6);
			EventZoneLoginOK.data.Turn = 6;				
			break;			
		case SAIL_NORMAL:
		case SAIL_PK:
		case SAIL_FINDGOLD:		
			SetCharacterOnFightState(npc_no, TRUE);
			SetCharacterOnTheSea(npc_no, TRUE);
			EventZoneLoginOK.data.BitState = GetCharacterBitState(npc_no);								
			SetCharacterDoingKind(npc_no, DOING_KIND_SEA_IDLE);
			EventZoneLoginOK.data.DoingKind = DOING_KIND_SEA_IDLE;
			SetCharacterFileIndex(npc_no, DbCharacter.SeaFileIndex);
			EventZoneLoginOK.data.FileIndex = DbCharacter.SeaFileIndex;
			SetCharacterShipSpeedX(npc_no, 0);			
			EventZoneLoginOK.data.FSpeedX = 0;			
			SetCharacterShipSpeedY(npc_no, 0);
			EventZoneLoginOK.data.FSpeedY = 0;			
			SetCharacterShipDegreeDir(npc_no, 0);
			EventZoneLoginOK.data.DegreeDir = 0;
			SetCharacterShipSailSize(npc_no, 100);
			EventZoneLoginOK.data.SailSize = 100;
			SetCharacterShipWeight(npc_no, 0);
			EventZoneLoginOK.data.Weight = 0;
			SetCharacterShipTurn(npc_no, 6);
			EventZoneLoginOK.data.Turn = 6;				
			break;
		}			
		UNLOCK_CHARACTER(0);
		// 讀取物品
		LoadCharacterItemDataByMainNameAndIndex(npc_no);
		LoadCharacterBankData(npc_no);
		LOCK_CHARACTER(0);
		ComputeCharacterDataAfterInit(npc_no);
		ExchangeZoneCharacterDataToMyCharacterData(npc_no, &EventZoneLoginOK.data);
		UNLOCK_CHARACTER(0);		
		
		EventZoneLoginOK.NpcIndex = npc_no;	
		
		//將新玩家加入的消息送給所有其他玩家.
		send_packet.Header.dwType = PLAYER_JOIN;
		send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_PLAYERJOIN);
		EventPlayerJoin.iIndex = npc_no;
		strcpy(EventPlayerJoin.cMainName, EventZoneLoginOK.data.MainName);
		EventPlayerJoin.MainNameColor = EventZoneLoginOK.data.MainNameColor;
		EventPlayerJoin.slFileIndex = EventZoneLoginOK.data.FileIndex;
		EventPlayerJoin.iHp = EventZoneLoginOK.data.Hp;
		EventPlayerJoin.iMaxHp = EventZoneLoginOK.data.MaxHp;
		EventPlayerJoin.iMp = EventZoneLoginOK.data.Mp;
		EventPlayerJoin.iMaxMp = EventZoneLoginOK.data.MaxMp;
		EventPlayerJoin.iLevel = EventZoneLoginOK.data.Level;
		EventPlayerJoin.iMspeed = EventZoneLoginOK.data.Mspeed;
		EventPlayerJoin.cColor = EventZoneLoginOK.data.Color;			
		EventPlayerJoin.slDoingKind = EventZoneLoginOK.data.DoingKind;
		EventPlayerJoin.cDir = EventZoneLoginOK.data.Dir;
		EventPlayerJoin.iSightRange = EventZoneLoginOK.data.SightRange;
		EventPlayerJoin.slSailSize = EventZoneLoginOK.data.SailSize;
		EventPlayerJoin.slWeight = EventZoneLoginOK.data.Weight;
		EventPlayerJoin.slTurn = EventZoneLoginOK.data.Turn;
		EventPlayerJoin.ulBitState = EventZoneLoginOK.data.BitState;
		for(i = 0;i < MAX_CHARACTER_PARTS;i++)
		{
			EventPlayerJoin.PartRGB[i] = EventZoneLoginOK.data.PartRGB[i];
		}		
		memcpy(send_packet.data.cBuf, &EventPlayerJoin, sizeof(TPOS_EVENT_PLAYERJOIN));	
		ServerSendPlayerJoinToOthers(cn, &send_packet);
		
		//送給WorldServerQQ玩家登入
		send_packet.Header.dwType = QQ_PLAYER_LOGIN;
		send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_QQPLAYERLOGIN);
		
		EventQQPlayerLogin.QQID = EventZoneLoginOK.data.QQID;
		memcpy(send_packet.data.cBuf, &EventQQPlayerLogin, sizeof(TPOS_EVENT_QQPLAYERLOGIN));
		
		CompressPacket(&send_packet, &send_compacket);

		QueuePacket(World, &send_compacket, CONNECTED_SERVER_WORLD);				

		//送給剛加入的玩家 ZONE_LOGIN_OK. and 送給加入的玩家自己的資料		
		send_packet.Header.dwType = ZONE_LOGIN_OK;
		send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_ZONELOGINOK);
		memcpy(send_packet.data.cBuf, &EventZoneLoginOK, sizeof(TPOS_EVENT_ZONELOGINOK));
		server_send_packet_to_one(cn, &send_packet);					

		// 如果是死亡或換區域的要檢查之前是否有在隊伍中		
		if(strcmp(DbCharacter.LeaderName, "") != 0)
		{
			i = FindCharacterByMainName(DbCharacter.LeaderName);
			if( i != -1)
			{
				int	j;
				TPOS_EVENT_NOTIFYRELOADTEAMINFO	EventNotifyReloadTeamInfo;
				
				memset(&EventNotifyReloadTeamInfo, 0x0, sizeof(TPOS_EVENT_NOTIFYRELOADTEAMINFO));
				LOCK_CHARACTER(0);
				for(j = 0; j < MAX_CHARACTER_TEAM_MEMBERS; j++)
				{
					strcpy(EventNotifyReloadTeamInfo.TeamMemberInfo[j].MainName, GetCharacterTeamMemberMainName(i, j));
					EventNotifyReloadTeamInfo.TeamMemberInfo[j].Career = (CHAR)GetCharacterTeamMemberCareer(i, j);						
					EventNotifyReloadTeamInfo.TeamMemberInfo[j].Eyes = (CHAR)GetCharacterTeamMemberEyes(i, j);
					EventNotifyReloadTeamInfo.TeamMemberInfo[j].Mouth = (CHAR)GetCharacterTeamMemberMouth(i, j);
					EventNotifyReloadTeamInfo.TeamMemberInfo[j].Hp = GetCharacterTeamMemberHp(i, j);
					EventNotifyReloadTeamInfo.TeamMemberInfo[j].MaxHp = GetCharacterTeamMemberMaxHp(i, j);
					EventNotifyReloadTeamInfo.TeamMemberInfo[j].Level = GetCharacterTeamMemberLevel(i, j);
					EventNotifyReloadTeamInfo.TeamMemberInfo[j].Sex = (CHAR)GetCharacterTeamMemberSex(i, j);					
					strcpy(EventNotifyReloadTeamInfo.TeamMemberInfo[j].ZoneName, GetCharacterTeamMemberZoneName(i, j));
				}				
				UNLOCK_CHARACTER(0);
				send_packet.Header.dwType = NOTIFY_RELOAD_TEAM_INFO;
				send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYRELOADTEAMINFO);
				memcpy(send_packet.data.cBuf, &EventNotifyReloadTeamInfo, sizeof(TPOS_EVENT_NOTIFYRELOADTEAMINFO));
				server_send_packet_to_one(cn, &send_packet);
			}
		}		
				
#ifdef  DEBUG_MSG
		char    debug_str[256];
		struct in_addr  debug_sin_addr;
			
		LOCK_CONNECTION(0);
		debug_sin_addr = cn->Addr.sin_addr;
		UNLOCK_CONNECTION(0);
				
		sprintf(debug_str, "PLAYER :%s , INDEX : %d , FROM %s LOGIN OK", mainname, t, inet_ntoa(debug_sin_addr) );
		SaveMsgToLog("SYSTEM", debug_str);
#endif//DEBUG_MSG		
	}
    return  ;
}
// -----------------------------------------------------------------------------
void	ServerDoPlayerLogout(TPOS_CN *cn, TPOS_PACKET *packet) 
{
	TPOS_DB_CHARACTER  DbCharacter;
    int find_idx;

    LOCK_CHARACTER(0);
    find_idx = FindCurrentConnectionCharacter(cn);
    UNLOCK_CHARACTER(0);

    if(find_idx >= 0)
    {
        LOCK_CHARACTER(0);
        SetCharacterDoingKind(find_idx, DOING_KIND_CHANGEMAP);
		ConvertZoneCharacterDataToDBCharacter(find_idx, &DbCharacter);        
		ClearOneCharacter(find_idx);
        UNLOCK_CHARACTER(0);
        
        UpdateRecordOfCharacterDB(&DbCharacter);
        
        //SendPlayerExitToAll(...)

#ifdef  DEBUG_MSG
        SaveWorkToLog(DbCharacter.MainName, inet_ntoa(cn->Addr.sin_addr), "LOGOUT"); 
#endif//DEBUG_MSG
    }    
}
// -----------------------------------------------------------------------------
void	ServerDoRequestPlayerList(TPOS_CN *cn, TPOS_PACKET *packet) 
{	
	TPOS_EVENT_REQUESTPLAYERLIST	EventRequestPlayerList;
	TPOS_EVENT_GETPLAYERLIST		EventGetPlayerList;
    static TPOS_PACKET send_packet;
    int     start, next, find_idx;
    char    user_id[64];
    struct in_addr debug_sin_addr;

    LOCK_CONNECTION(0);
    strcpy((char *)user_id, cn->User.cId);
    debug_sin_addr = cn->Addr.sin_addr;
    UNLOCK_CONNECTION(0);

#ifdef  DEBUG_MSG
    SaveWorkToLog(user_id, inet_ntoa(debug_sin_addr), "GET_PLAYER_LIST");
#endif//DEBUG_MSG

	memcpy(&EventRequestPlayerList, packet->data.cBuf, sizeof(TPOS_EVENT_REQUESTPLAYERLIST));
    //尋找下一個角色, 如果找到, 將該角色資料存入TmpListCharacterInfo.
    start = EventRequestPlayerList.iIndex;
    LOCK_CHARACTER(0);
    next = FindNextUsedCharacterInfo(start);
    if(next >= 0)
    {
        ConvertZoneCharacterDataToEventGetPlayerList(next, &EventGetPlayerList);
    }
    UNLOCK_CHARACTER(0);
    
    if(next >= 0)
    {
        //傳送找到的角色資料
        send_packet.Header.dwType = GET_PLAYER_LIST;
        send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_GETPLAYERLIST);
        memcpy(send_packet.data.cBuf, &EventGetPlayerList, sizeof(TPOS_EVENT_GETPLAYERLIST));
        		
        server_send_packet_to_one(cn, &send_packet);
        
#ifdef  DEBUG_MSG
        char    debug_str[256];
        sprintf(debug_str, "Send Character List : %s , Index : %d , To : %s",
            EventGetPlayerList.cMainName,
            next,
            user_id);
        SaveMsgToLog("SYSTEM", debug_str);
#endif//DEBUG_MSG
    }
    else
    {
        //傳送找角色資料結束
        send_packet.Header.dwType = GET_PLAYER_LIST;
        send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_GETPLAYERLIST);
		memset(&EventGetPlayerList, 0x0, sizeof(TPOS_EVENT_GETPLAYERLIST));
        EventGetPlayerList.iIndex = END;
        memcpy(send_packet.data.cBuf, &EventGetPlayerList, sizeof(TPOS_EVENT_GETPLAYERLIST));
        server_send_packet_to_one(cn, &send_packet);

#ifdef  DEBUG_MSG
        SaveWorkToLog(user_id, inet_ntoa(debug_sin_addr), "GET_PLAYER_LIST_END");
#endif//DEBUG_MSG

		
        LOCK_CHARACTER(0);
        find_idx = FindPlayerCharacterInfoByMainName(user_id);
        UNLOCK_CHARACTER(0);

        if(find_idx >= 0)
        {			
			//傳送系統消息
            SendSystemMessage(cn);
			//傳送該區域的地上物品
			ServerDoGatherZoneItem(cn);
			//傳送法術組件
			// Hawke  [4/28/2003]
			// To Do...
			//傳送區域天氣
            SendCurrentWeatherToNewPlayer(cn);			
        }
    }
}
// -----------------------------------------------------------------------------
void	ServerDoGetPublicTalk(TPOS_CN *cn, TPOS_PACKET *packet) 
{
	static TPOS_PACKET					send_packet;	
    int         find_idx;
    SLONG       hp, send_enable;

    send_enable = false;

    LOCK_CONNECTION(0);
    find_idx = FindCurrentConnectionCharacter(cn);
    UNLOCK_CONNECTION(0);

    if(find_idx >= 0)
    {
        LOCK_CHARACTER(0);
        hp = GetCharacterHp(find_idx);
        if(hp > 0)
            send_enable = true;
        UNLOCK_CHARACTER(0);
        
        if(send_enable)
        {
            send_packet.Header.dwType = GET_PUBLIC_TALK;
            send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_GETPUBLICTALK);
			memcpy(send_packet.data.cBuf, packet->data.cBuf, sizeof(TPOS_EVENT_GETPUBLICTALK));			
            
			server_send_packet_to_all(&send_packet);

#ifdef  DEBUG_MSG
            struct in_addr  debug_sin_addr;
            char    debug_mainname[32];

            LOCK_CONNECTION(0);
            debug_sin_addr = cn->Addr.sin_addr;
            UNLOCK_CONNECTION(0);

            LOCK_CHARACTER(0);
            strcpy((char *)debug_mainname, GetCharacterMainName(find_idx));
            UNLOCK_CHARACTER(0);

            SaveWorkToLog(debug_mainname, inet_ntoa(debug_sin_addr), "SEND_PUBLIC_TALK");
#endif//DEBUG_MSG
        }
    }
}
// -----------------------------------------------------------------------------
void	ServerDoGetWorldTalk(TPOS_CN *cn, TPOS_PACKET *packet) 
{
	static TPOS_PACKET send_packet;

    send_packet.Header.dwType = GET_PUBLIC_TALK;
    send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_GETPUBLICTALK);
    memcpy(send_packet.data.cBuf, packet->data.cBuf, sizeof(TPOS_EVENT_GETPUBLICTALK));

    server_send_packet_to_all(&send_packet);
}
// -----------------------------------------------------------------------------
void	ServerDoSaveUserDetail(TPOS_CN *cn, TPOS_PACKET *packet) 
{
}
// -----------------------------------------------------------------------------
void	ServerDoHitMap(TPOS_CN *cn, TPOS_PACKET *packet) 
{
	TPOS_EVENT_HITMAP	EventHitMap;
    DWORD				dwLR;
    SLONG				magic_no, index, x, y, hp;

	memcpy(&EventHitMap, packet->data.cBuf, sizeof(TPOS_EVENT_HITMAP));
    dwLR = EventHitMap.dwLeftRight;
	x = EventHitMap.lX;
    y = EventHitMap.lY;
    LOCK_CHARACTER(0);
	index = FindCharacterByMainName(cn->User.cId);
    switch(dwLR)
    {
    case LEFT:
        magic_no = GetCharacterLeftSkill(index);
        break;
    case RIGHT:
        magic_no = GetCharacterRightSkill(index);
        break;
    }
    hp = GetCharacterHp(index);
    UNLOCK_CHARACTER(0);

    if(magic_no >= 0 && magic_no < MAX_GAME_SKILL_BASES && hp > 0)
    {		
        server_exec_magic_hit_map_func(index, magic_no, x, y);
    }    
}
// -----------------------------------------------------------------------------
void	ServerDoEndHitMap(TPOS_CN *cn, TPOS_PACKET *packet) 
{
	TPOS_EVENT_HITMAP	EventEndHitMap;
    DWORD   dwLR;
    SLONG   magic_no, index, x, y, hp;

	memcpy(&EventEndHitMap, packet->data.cBuf, sizeof(TPOS_EVENT_HITMAP));
    dwLR = EventEndHitMap.dwLeftRight;    
    x = EventEndHitMap.lX;
    y = EventEndHitMap.lY;
    LOCK_CHARACTER(0);
	index = FindCharacterByMainName(cn->User.cId);
    switch(dwLR)
    {
    case LEFT:
        magic_no = GetCharacterLeftSkill(index);
        break;
    case RIGHT:
        magic_no = GetCharacterRightSkill(index);
        break;
    }
    hp = GetCharacterHp(index);
    UNLOCK_CHARACTER(0);
	switch(ZoneType)
	{
	case CITY_BIRTH:
	case CITY_NEWBIE:
	case FIELD_BIRTH:
	case FIELD_NEWBIE:
	case SAIL_BIRTH:
	case SAIL_NEWBIE:
		if(magic_no != MAGIC_NO_CLASH)
		{
			if(magic_no >= 0 && magic_no < MAX_GAME_SKILL_BASES && hp > 0)
			{
				server_exec_magic_end_hit_map_func(index, magic_no, x, y);
			}    
		}
		break;
	default:
		if(magic_no >= 0 && magic_no < MAX_GAME_SKILL_BASES && hp > 0)
		{
			server_exec_magic_end_hit_map_func(index, magic_no, x, y);
		}
		break;
	}        
}
// -----------------------------------------------------------------------------
void	ServerDoHitNPC(TPOS_CN *cn, TPOS_PACKET *packet) 
{
	TPOS_EVENT_HITNPC   EventHitNpc;
    DWORD       dwLR;
    SLONG       index, dest_npc;
    SLONG       magic_no, hp, is_fight;
	SLONG		is_team_member;
	int			i;
	char		dest_mainname[32];

	is_team_member = FALSE;
	memcpy(&EventHitNpc, packet->data.cBuf, sizeof(TPOS_EVENT_HITNPC));
    dwLR = EventHitNpc.dwLeftRight;    
    dest_npc = EventHitNpc.dwDestNPC;
    LOCK_CHARACTER(0);
	strcpy(dest_mainname, GetCharacterMainName(dest_npc));
	index = FindCharacterByMainName(cn->User.cId);
    switch(dwLR)
    {
    case LEFT:
        magic_no = GetCharacterLeftSkill(index);
        break;
    case RIGHT:
        magic_no = GetCharacterRightSkill(index);
        break;
    }
    hp = GetCharacterHp(index);
	is_fight = IsCharacterOnFightState(index);
	// 檢查對方是否為隊員
	for(i = 0; i < MAX_CHARACTER_TEAM_MEMBERS; i++)
	{
		if(strcmp(dest_mainname, GetCharacterTeamMemberMainName(index, i)) == 0)
		{
			is_team_member = TRUE;
			break;
		}
	}
    UNLOCK_CHARACTER(0);
	if(magic_no >= 0 && magic_no < MAX_GAME_SKILL_BASES && hp > 0 && is_team_member == FALSE)
	{
		server_exec_magic_hit_npc_func(index, magic_no, dest_npc);		
	}	
	
}
// -----------------------------------------------------------------------------
void	ServerDoHitItem(TPOS_CN *cn, TPOS_PACKET *packet) 
{
	TPOS_EVENT_HITITEM	EventHitItem;
    DWORD   dwLR;
    SLONG   magic_no, index, item_x, item_y, hp;

	memcpy(&EventHitItem, packet->data.cBuf, sizeof(TPOS_EVENT_HITITEM));
    dwLR = EventHitItem.dwLeftRight;    
    item_x = EventHitItem.lX;
    item_y = EventHitItem.lY;
    LOCK_CHARACTER(0);
	index = FindCharacterByMainName(cn->User.cId);
    switch(dwLR)
    {
    case LEFT:
        magic_no = GetCharacterLeftSkill(index);
        break;
    case RIGHT:
        magic_no = GetCharacterRightSkill(index);
        break;
    }
    hp = GetCharacterHp(index);
    UNLOCK_CHARACTER(0);

    if(magic_no >= 0 && magic_no < MAX_GAME_SKILL_BASES && hp > 0)
    {
        server_exec_magic_hit_map_item_func(index, magic_no, item_x, item_y);
    }
}
// -----------------------------------------------------------------------------
void	ServerDoSendAttackSwitch(TPOS_CN *cn, TPOS_PACKET *packet) 
{
	TPOS_EVENT_ATTACKSWITCH	EventAttackSwitch;
	static TPOS_PACKET				send_packet;
    int						index;
    SLONG					is_fight, change_successful, was_fight;
    SLONG					hp;
		
	//if(ZoneType == SAIL_NORMAL)return;
	//if(ZoneType == SAIL_PK)return;
	if(ZoneType == SAIL_FINDGOLD)return;
	if(ZoneType == SAIL_NEWBIE)return;	
	if(ZoneType == SAIL_BIRTH)return;
	if(ZoneType == CITY_BIRTH)return;
	if(ZoneType == CITY_NEWBIE)return;
	if(ZoneType == FIELD_BIRTH)return;
	//if(ZoneType == FIELD_NEWBIE)return;

	memset(&EventAttackSwitch, 0x0, sizeof(TPOS_EVENT_ATTACKSWITCH));
    //試圖改變NPC的戰鬥與非戰鬥狀態, 如果可以改變, 將NPC設為IDLE.-------------
    change_successful = false;    
    LOCK_CHARACTER(0);
	index = FindCharacterByMainName(cn->User.cId);
    hp = GetCharacterHp(index);
    if(hp > 0)
    {
        was_fight = IsCharacterOnFightState(index);
		
        if(was_fight)
        {
            //change_successful = server_is_player_can_change_fight_state(index, false);
			change_successful = true;
            if(change_successful)
            {
                SetCharacterOnFightState(index, false);
				SetCharacterDoingKindStep(index, DOING_KIND_IDLE, 0);			       
                is_fight = false;
            }
        }
        else
        {
            //change_successful = server_is_player_can_change_fight_state(index, true);
			change_successful = true;
            if(change_successful)
            {
                SetCharacterOnFightState(index, true);
                SetCharacterDoingKindStep(index, DOING_KIND_IDLE, 0);
                is_fight = true;
            }
        }
    }
    UNLOCK_CHARACTER(0);

    //假如改變成功, 則將結果送給所有人. ---------------------
    if(change_successful)
    {
        send_packet.Header.dwType = GET_ATTACK_SWITCH;
        send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_ATTACKSWITCH);

		EventAttackSwitch.dwIndex = index;
		EventAttackSwitch.dwPk = is_fight;
		EventAttackSwitch.lDoing_kind = DOING_KIND_IDLE;
		
		memcpy(send_packet.data.cBuf, &EventAttackSwitch, sizeof(TPOS_EVENT_ATTACKSWITCH));	
        
        server_send_packet_to_all(&send_packet);
    }
    
#ifdef  DEBUG_MSG
    char    name[64];
    LOCK_CHARACTER(index);
    strcpy((char *)name, GetCharacterMainName(index));
    UNLOCK_CHARACTER(index);
    SaveWorkToLog(name, inet_ntoa(cn->Addr.sin_addr), "GET_ATTACK_SWITCH");
#endif//DEBUG_MSG
}
// -----------------------------------------------------------------------------
void	ServerDoSendBagSwitch(TPOS_CN *cn, TPOS_PACKET *packet) 
{
	TPOS_EVENT_BAGSWITCH	EventBagSwitch; 
	static TPOS_PACKET		send_packet;
    int						index;
    SLONG					hp;
    DWORD					dwBag, dwNewBag;
    SLONG					process_result;

	memcpy(&EventBagSwitch, packet->data.cBuf, sizeof(TPOS_EVENT_BAGSWITCH));
    //改變npc的背包開啟狀態 --------------------------------    
    dwBag = EventBagSwitch.dwBag;
    process_result = FALSE;
    LOCK_CHARACTER(0);
	index = FindCharacterByMainName(cn->User.cId);
    hp = GetCharacterHp(index);
    if(hp > 0)
    {		
		if(dwBag == CLOSE_BAG)
		{
			dwNewBag = CLOSE_BAG;
			SetCharacterBagOpened(index, FALSE);
			process_result = TRUE;
			EndAdjustCharacterPropertyPoint(index);
		}
		if(dwBag == OPEN_BAG)
		{
			dwNewBag = OPEN_BAG;
			SetCharacterBagOpened(index, TRUE);
			process_result = TRUE;
		}        
    }
    UNLOCK_CHARACTER(0);
	
    //將改變後的結果送給該玩家 --------------------------------
    if(process_result)
    {
		send_packet.Header.dwType = GET_BAG_SWITCH;
        send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_BAGSWITCH);
		EventBagSwitch.dwBag = dwNewBag;             
		memcpy(send_packet.data.cBuf, &EventBagSwitch, sizeof(TPOS_EVENT_BAGSWITCH));

        server_send_packet_to_one(cn, &send_packet);

#ifdef  DEBUG_MSG
        char    name[32];
        LOCK_CHARACTER(index);
        strcpy((char *)name, GetCharacterMainName(index));
        SaveWorkToLog(name, inet_ntoa(cn->Addr.sin_addr), "GET_BAG_SWITCH");
        UNLOCK_CHARACTER(index);
#endif//DEBUG_MSG
    }    
}
// -----------------------------------------------------------------------------
void	ServerDoChangeMouseSkill(TPOS_CN *cn, TPOS_PACKET *packet) 
{
	TPOS_EVENT_CHANGEMOUSESKILL	EventChangeMouseSkill;
	static TPOS_PACKET					send_packet;
    int							index;
	UHINT						hp;
    DWORD						dLeftRight, dSkill;
    SLONG						last_magic, magic_no, is_fight;
    SLONG						set_successful;
    
	memcpy(&EventChangeMouseSkill, packet->data.cBuf, sizeof(TPOS_EVENT_CHANGEMOUSESKILL));    
    dLeftRight = EventChangeMouseSkill.dwLeftRight;
    magic_no = dSkill = EventChangeMouseSkill.dwSkill;
    set_successful = false;
    //設置玩家npc對應的左手或者右手的技能------------------------------
    LOCK_CHARACTER(0);
	index = FindCharacterByMainName(cn->User.cId);
	hp = GetCharacterHp(index);
	if(hp > 0)
	{
		switch(dLeftRight)
		{
		case LEFT:
			last_magic = GetCharacterLeftSkill(index);
			if(last_magic != magic_no)
			{
				SetCharacterLeftSkill(index, (SHINT)magic_no);
				set_successful = true;
			}
			break;
		case RIGHT:
			last_magic = GetCharacterRightSkill(index);
			if(last_magic != magic_no)
			{
				SetCharacterRightSkill(index, (SHINT)magic_no);
				InitCharacterRightSkillState(index);
				set_successful = true;
			}
			break;
		}    
	}
    UNLOCK_CHARACTER(0);

    if(set_successful)
    {
        switch(last_magic)
        {
        case MAGIC_NO_MUSE: //冥想
            LOCK_CHARACTER(index);
            is_fight = IsCharacterOnFightState(index);
            if(is_fight)
            {
                ServerChangeCharacterDoing(index, DOING_KIND_IDLE, 0, 0, 0, 0, 0, magic_no);
            }
            UNLOCK_CHARACTER(index);
            break;

        case MAGIC_NO_DEFENCE:  //格擋
            LOCK_CHARACTER(index);
            SetCharacterOnDefenceState(index, FALSE);
            UNLOCK_CHARACTER(index);
            break;

        default:
            break;
        }
        
        switch(magic_no)
        {
        case MAGIC_NO_MUSE: //冥想
            LOCK_CHARACTER(index);
            is_fight = IsCharacterOnFightState(index);
            if(is_fight)
            {
                ServerChangeCharacterDoing(index, DOING_KIND_MUSE, 0, 0, 0, 0, 0, magic_no);
            }
            UNLOCK_CHARACTER(index);
            break;

        case MAGIC_NO_DEFENCE:  //格擋
            LOCK_CHARACTER(index);
            SetCharacterOnDefenceState(index, TRUE);
            UNLOCK_CHARACTER(index);
            break;

        default:
            break;
        }

        //將結果傳給該玩家 -------------------------------------------------
        {           
            send_packet.Header.dwType = GET_CHANGE_MOUSE_SKILL;
            send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_CHANGEMOUSESKILL);			
			EventChangeMouseSkill.dwLeftRight = dLeftRight;
			EventChangeMouseSkill.dwSkill = dSkill;
            memcpy(send_packet.data.cBuf, &EventChangeMouseSkill, sizeof(TPOS_EVENT_CHANGEMOUSESKILL));
            
			server_send_packet_to_one(cn, &send_packet);
            
#ifdef  DEBUG_MSG
            char  name[32];
            LOCK_CHARACTER(index);
            strcpy(name, GetCharacterMainName(index));
            SaveWorkToLog(name, inet_ntoa(cn->Addr.sin_addr), "CHANGE_MOUSE_SKILL");
            UNLOCK_CHARACTER(index);
#endif//DEBUG_MSG
        }
    }    
}
// -----------------------------------------------------------------------------
void	ServerDoUpdateNPCBaseData(TPOS_CN *cn, TPOS_PACKET *packet) 
{
	TPOS_EVENT_UPDATENPCBASEDATA		EventUpdataNpcbaseData;
	TPOS_EVENT_SETNPCUPGRADEBASEDATA	EventSetNpcUpgradeBaseData;	
	static TPOS_PACKET		send_packet;
    SLONG   index, update_type, update_value;
    SLONG   update_ok;    
    SLONG   update_result_type;    

	memcpy(&EventUpdataNpcbaseData, packet->data.cBuf, sizeof(TPOS_EVENT_UPDATENPCBASEDATA));
    update_type = EventUpdataNpcbaseData.update_type;
    update_value = EventUpdataNpcbaseData.update_value;
    update_ok = FALSE;
    LOCK_CHARACTER(0);
	index = FindCharacterByMainName(cn->User.cId);
    switch(update_type)
    {
    case UPDATE_NPC_BASE_STRENGTH:  //力量				
		POINTSTR_UPDATE_RESULT				StrResult;	
        if(update_value > 0) //增加基本力量
        {
			if(ComputeCharacterPropertyPointToPointStr(index, update_value, &StrResult) == TRUE)
			{
				update_result_type = UPDATE_NPC_BASE_STRENGTH;
				update_ok = TRUE;	
			}			
        }
        else if(update_value < 0) //減少基本力量
        {
			if(ComputeCharacterPointStrToPropertyPoint(index, -(update_value), &StrResult) == TRUE)
			{				
				update_result_type = UPDATE_NPC_BASE_STRENGTH;
				update_ok = TRUE;        
			}			
        }
		if(update_ok == TRUE)
		{			
			EventSetNpcUpgradeBaseData.rest_point = StrResult.property_point;
			EventSetNpcUpgradeBaseData.update_type = update_result_type;
			EventSetNpcUpgradeBaseData.value = StrResult.str;
			EventSetNpcUpgradeBaseData.att = StrResult.att;
			EventSetNpcUpgradeBaseData.defence = StrResult.defence;
			EventSetNpcUpgradeBaseData.max_hp = StrResult.max_hp;
			EventSetNpcUpgradeBaseData.hp = StrResult.hp;
			EventSetNpcUpgradeBaseData.max_mp = StrResult.max_mp;
			EventSetNpcUpgradeBaseData.mp = StrResult.mp;
		}
        break;

    case UPDATE_NPC_BASE_INSTINCT:  //直覺		
		POINTINS_UPDATE_RESULT				InsResult;
		if(update_value > 0) //增加基本直覺
		{
			if(ComputeCharacterPropertyPointToPointIns(index, update_value, &InsResult) == TRUE)
			{				
				update_result_type = UPDATE_NPC_BASE_INSTINCT;
				update_ok = TRUE;            				
			}
		}
		else if(update_value < 0) //減少基本直覺
		{
			if(ComputeCharacterPointInsToPropertyPoint(index, -(update_value), &InsResult) == TRUE)
			{			
				update_result_type = UPDATE_NPC_BASE_INSTINCT;		
				update_ok = TRUE;
			}
		}
		if(update_ok == TRUE)
		{			
			EventSetNpcUpgradeBaseData.rest_point = InsResult.property_point;
			EventSetNpcUpgradeBaseData.update_type = update_result_type;
			EventSetNpcUpgradeBaseData.value = InsResult.ins;
			EventSetNpcUpgradeBaseData.att = InsResult.att;
			EventSetNpcUpgradeBaseData.defence = InsResult.defence;
			EventSetNpcUpgradeBaseData.max_hp = InsResult.max_hp;
			EventSetNpcUpgradeBaseData.hp = InsResult.hp;
			EventSetNpcUpgradeBaseData.max_mp = InsResult.max_mp;
			EventSetNpcUpgradeBaseData.mp = InsResult.mp;		        
		}
		break;
    case UPDATE_NPC_BASE_WIT:       //智力
		POINTWIT_UPDATE_RESULT				WitResult;
        if(update_value > 0) //增加基本智力
        {
			if(ComputeCharacterPropertyPointToPointWit(index, update_value, &WitResult) == TRUE)
			{
				update_result_type = UPDATE_NPC_BASE_WIT;
				update_ok = TRUE;            
			}            
        }
        else if(update_value < 0) //減少基本智力
        {
			if(ComputeCharacterPointWitToPropertyPoint(index, -(update_value), &WitResult) == TRUE)
			{
				update_result_type = UPDATE_NPC_BASE_WIT;
				update_ok = TRUE;            
			}            
        }
		if(update_ok == TRUE)
		{			
			EventSetNpcUpgradeBaseData.rest_point = WitResult.property_point;
			EventSetNpcUpgradeBaseData.update_type = update_result_type;
			EventSetNpcUpgradeBaseData.value = WitResult.wit;
			EventSetNpcUpgradeBaseData.att = WitResult.att;
			EventSetNpcUpgradeBaseData.defence = WitResult.defence;
			EventSetNpcUpgradeBaseData.max_hp = WitResult.max_hp;
			EventSetNpcUpgradeBaseData.hp = WitResult.hp;
			EventSetNpcUpgradeBaseData.max_mp = WitResult.max_mp;
			EventSetNpcUpgradeBaseData.mp = WitResult.mp;		        
		}
        break;
    case UPDATE_NPC_BASE_LUCK:      //運氣
		POINTLUCKY_UPDATE_RESULT				LuckyResult;
        if(update_value > 0) //增加基本運氣
        {
			if(ComputeCharacterPropertyPointToPointLucky(index, update_value, &LuckyResult) == TRUE)
			{
				update_result_type = UPDATE_NPC_BASE_LUCK;
				update_ok = TRUE;            
			}            
        }
        else if(update_value < 0) //減少基本運氣
        {
			if(ComputeCharacterPointLuckyToPropertyPoint(index, -(update_value), &LuckyResult) == TRUE)
			{
				update_result_type = UPDATE_NPC_BASE_LUCK;
	            update_ok = TRUE;            
			}            
        }
		if(update_ok == TRUE)
		{			
			EventSetNpcUpgradeBaseData.rest_point = LuckyResult.property_point;
			EventSetNpcUpgradeBaseData.update_type = update_result_type;
			EventSetNpcUpgradeBaseData.value = LuckyResult.lucky;
			EventSetNpcUpgradeBaseData.att = LuckyResult.att;
			EventSetNpcUpgradeBaseData.defence = LuckyResult.defence;
			EventSetNpcUpgradeBaseData.max_hp = LuckyResult.max_hp;
			EventSetNpcUpgradeBaseData.hp = LuckyResult.hp;
			EventSetNpcUpgradeBaseData.max_mp = LuckyResult.max_mp;
			EventSetNpcUpgradeBaseData.mp = LuckyResult.mp;		        
		}
        break;
    }
    UNLOCK_CHARACTER(0);

    if(update_ok == TRUE)
    {
        send_packet.Header.dwType = SET_NPC_UPGRADE_BASE_DATA;
        send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_SETNPCUPGRADEBASEDATA);	
        
		memcpy(send_packet.data.cBuf, &EventSetNpcUpgradeBaseData, sizeof(TPOS_EVENT_SETNPCUPGRADEBASEDATA));
        server_send_packet_to_one(cn, &send_packet);
    }
}
// -----------------------------------------------------------------------------
void	ServerDoRequestChangeWeather(TPOS_CN *cn, TPOS_PACKET *packet) 
{
	TPOS_EVENT_REQUESTCHANGEWEATHER	EventRequestChangeWeather;    	
    static TPOS_PACKET						send_packet;
    TPOS_ZONEWEATHER				temp_zone_weather;
    SLONG							update_ok;
    
    update_ok = false;
    memcpy(&EventRequestChangeWeather, packet->data.cBuf, sizeof(TPOS_EVENT_REQUESTCHANGEWEATHER));

    LOCK_WEATHER(0);
    if(DLL_OK == SetWeather((TPOS_WEATHER *)&EventRequestChangeWeather))
    {
        temp_zone_weather = *ZoneWeather;
        update_ok = true;
    }
    UNLOCK_WEATHER(0);

    if(update_ok)
    {
        send_packet.Header.dwType = GET_ZONE_NOW_WEATHER;
        send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_GETZONENOWWEATHER);
        memcpy(send_packet.data.cBuf, &temp_zone_weather,sizeof(TPOS_EVENT_GETZONENOWWEATHER));

        server_send_packet_to_all(&send_packet);
        
#ifdef  DEBUG_MSG
        char    debug_user_id[64];
        struct in_addr debug_in_addr;

        LOCK_CONNECTION(0);
        strcpy((char *)debug_user_id, cn->User->cId);
        debug_in_addr = cn->Addr.sin_addr;
        UNLOCK_CONNECTION(0);

        SaveWorkToLog(debug_user_id, debug_in_addr, "REQUEST_CHANGE_WEATHER");
#endif//DEBUG_MSG
    }
    else
    {
        send_packet.Header.dwType = SET_WEATHER_FAIL;
        send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER);
        server_send_packet_to_one(cn, &send_packet);
        
#ifdef  DEBUG_MSG
        char    debug_user_id[64];
        struct in_addr debug_in_addr;

        LOCK_CONNECTION(0);
        strcpy((char *)debug_user_id, cn->User->cId);
        debug_in_addr = cn->Addr.sin_addr;
        UNLOCK_CONNECTION(0);

        SaveWorkToLog(debug_user_id, inet_ntoa(debug_in_addr), "CHANGE_WEATHER_FAIL");
#endif//DEBUGMSG
    }
}
// -----------------------------------------------------------------------------
void	ServerDoGameStart(TPOS_CN *cn, TPOS_PACKET *packet) 
{
	int		find_index;
	UHINT	hp;
    
    LOCK_CHARACTER(0);
    find_index = FindCurrentConnectionCharacter(cn);
	hp = GetCharacterHp(find_index);
    UNLOCK_CHARACTER(0);
    
    if(find_index >= 0)
    {        
		switch(ZoneType)
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
			LOCK_CHARACTER(find_index);
			if(hp <= 0)			
			{
				SetCharacterDeadState(find_index, NPC_DEAD);
				SetCharacterDeadTicks(find_index, 100);
				ServerChangeCharacterDoing(find_index, DOING_KIND_DEAD, 0, find_index, 100, 0, 0, 0);
				ServerSendChangeNpcDoing(find_index, DOING_KIND_DEAD, 0, find_index, 100, 0, 0, 0);
			}
			if(hp > 0)
			{
			    // modify by lijun 2003-05-23
			    //SetCharacterDoingKindStep(find_index, DOING_KIND_IDLE, 0);
				ServerChangeCharacterDoing(find_index, DOING_KIND_IDLE, 0, 0, 0, 0, 0, 0);
				ServerSendChangeNpcDoing(find_index, DOING_KIND_IDLE, 0, 0, 0, 0, 0, 0);
            }			    
			UNLOCK_CHARACTER(find_index);
			break;
		case SAIL_NORMAL:
		case SAIL_NEWBIE:
		case SAIL_PK:
		case SAIL_FINDGOLD:
		case SAIL_BIRTH:
			LOCK_CHARACTER(find_index);
			if(hp <= 0)
			{
				SetCharacterDeadState(find_index, NPC_DEAD);
				SetCharacterDeadTicks(find_index, 100);
				ServerChangeCharacterDoing(find_index, DOING_KIND_DEAD, 0, find_index, 100, 0, 0, 0);
				ServerSendChangeNpcDoing(find_index, DOING_KIND_DEAD, 0, find_index, 100, 0, 0, 0);
			}
			if(hp > 0)
            {			
			    
			    // modify by lijun 2003-05-23
			    //SetCharacterDoingKindStep(find_index, DOING_KIND_SEA_IDLE, 0);
				ServerChangeCharacterDoing(find_index, DOING_KIND_SEA_IDLE, 0, 0, 0, 0, 0, 0);
				ServerSendChangeNpcDoing(find_index, DOING_KIND_SEA_IDLE, 0, 0, 0, 0, 0, 0);			    
            }			    
			UNLOCK_CHARACTER(find_index);
			break;
		}        

#ifdef  DEBUG_MSG
        char  debug_name[32];
        struct in_addr debug_in_addr;

        LOCK_CHARACTER(find_index);
        strcpy((char *)debug_name, GetCharacterMainName(find_index));
        UNLOCK_CHARACTER(find_index);

        LOCK_CONNECTION(0);
        debug_in_addr = cn->Addr.sin_addr;
        UNLOCK_CONNECTION(0);

        SaveWorkToLog(debug_name, inet_ntoa(debug_in_addr), "GAME_START");
#endif//DEBUG_MSG
    }
}
// -----------------------------------------------------------------------------
void	ServerDoRequestExitGame(TPOS_CN *cn, TPOS_PACKET *packet) 
{
	TPOS_DB_CHARACTER			DbCharacter;
	static TPOS_PACKET			send_packet;
	static TPOS_COMPACKET		send_compacket;
	TPOS_EVENT_QQPLAYERLOGOUT	EventQQPlayerLogout;		
	ULONG						Find_Id;
	int							Find_Idx;
	int							iRet;	
	int							i, j;
	char						leader_mainname[32];

	LOCK_CHARACTER(0);
	Find_Id = FindCurrentConnectionQQID(cn);
	UNLOCK_CHARACTER(0);	

	// QQ 離線
	send_packet.Header.dwType = QQ_PLAYER_LOGOUT;
	send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_QQPLAYERLOGOUT);		
	EventQQPlayerLogout.QQID = Find_Id;
	memcpy(send_packet.data.cBuf, &EventQQPlayerLogout, sizeof(TPOS_EVENT_QQPLAYERLOGOUT));
	CompressPacket(&send_packet, &send_compacket);
	QueuePacket(World, &send_compacket, CONNECTED_SERVER_WORLD);
	
	LOCK_CHARACTER(0);
	Find_Idx = FindCharacterInfoByQQID(Find_Id);		
	UNLOCK_CHARACTER(0);
	if(Find_Idx != -1)
	{
		LOCK_CHARACTER(0);
		// 處理如果在隊伍裡面必須離隊
		strcpy(leader_mainname, GetCharacterTeamMemberMainName(Find_Idx, 0));
		UNLOCK_CHARACTER(0);
		if(strcmp(leader_mainname, "") != 0)
		{
			TPOS_EVENT_NOTIFYSOMEONEEXITTEAM	EventNotifySomeoneExitTeam;
			char								tempmainname[32];			
			int									leader_npc_no, temp_npc_no;
			int									cn_index;

			LOCK_CHARACTER(0);
			leader_npc_no = FindCharacterByMainName(leader_mainname);
			// 將離開隊員的資料清空
			for(i = 1; i < MAX_CHARACTER_TEAM_MEMBERS; i++)
			{
				if(strcmp(GetCharacterTeamMemberMainName(leader_npc_no, i), GetCharacterMainName(Find_Idx)) == 0)
				{
					SetCharacterTeamMemberMainName(leader_npc_no, i, "");			
					SetCharacterTeamMemberHp(leader_npc_no, i, 0);
					SetCharacterTeamMemberMaxHp(leader_npc_no, i, 0);
					SetCharacterTeamMemberEyes(leader_npc_no, i, 0);
					SetCharacterTeamMemberMouth(leader_npc_no, i, 0);			
					SetCharacterTeamMemberLevel(leader_npc_no, i, 0);
					SetCharacterTeamMemberCareer(leader_npc_no, i, 0);
					SetCharacterTeamMemberSex(leader_npc_no, i, 0);			
					SetCharacterTeamMemberZoneName(leader_npc_no, i, "");
					break;
				}
			}			
			// 將隊伍資訊更新給隊員
			for(j = 1; j < MAX_CHARACTER_TEAM_MEMBERS; j++)
			{
				temp_npc_no = FindCharacterByMainName(GetCharacterTeamMemberMainName(leader_npc_no, j));
				if(temp_npc_no != -1)
				{
					for(i = 0; i < MAX_CHARACTER_TEAM_MEMBERS; i++)
					{
						SetCharacterTeamMemberMainName(temp_npc_no, i, GetCharacterTeamMemberMainName(leader_npc_no, i));			
						SetCharacterTeamMemberHp(temp_npc_no, i, GetCharacterTeamMemberHp(leader_npc_no, i));
						SetCharacterTeamMemberMaxHp(temp_npc_no, i, GetCharacterTeamMemberMaxHp(leader_npc_no, i));
						SetCharacterTeamMemberEyes(temp_npc_no, i, GetCharacterTeamMemberEyes(leader_npc_no, i));
						SetCharacterTeamMemberMouth(temp_npc_no, i, GetCharacterTeamMemberMouth(leader_npc_no, i));
						SetCharacterTeamMemberLevel(temp_npc_no, i, GetCharacterTeamMemberLevel(leader_npc_no, i));
						SetCharacterTeamMemberCareer(temp_npc_no, i, GetCharacterTeamMemberCareer(leader_npc_no, i));
						SetCharacterTeamMemberSex(temp_npc_no, i, GetCharacterTeamMemberSex(leader_npc_no, i));			
						SetCharacterTeamMemberZoneName(temp_npc_no, i, GetCharacterTeamMemberZoneName(leader_npc_no, i));
					}
				}			
			}
			UNLOCK_CHARACTER(0);
			send_packet.Header.dwType = NOTIFY_SOMEONE_EXIT_TEAM;
			send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYSOMEONEEXITTEAM);
			strcpy(EventNotifySomeoneExitTeam.MemberMainName, cn->User.cId);
			memcpy(send_packet.data.cBuf, &EventNotifySomeoneExitTeam, sizeof(TPOS_EVENT_NOTIFYSOMEONEEXITTEAM));
			// 給隊長
			LOCK_CONNECTION(0);
			cn_index = FindConnectionByName(leader_mainname);
			UNLOCK_CONNECTION(0);			
			if(cn_index >= 0 && cn_index < 500)
			{
				server_send_packet_to_one(&Pos_Cn[cn_index], &send_packet);
			}
			// 給隊友
			for(i = 1; i < MAX_CHARACTER_TEAM_MEMBERS; i++)
			{
				LOCK_CHARACTER(0);
				strcpy(tempmainname, GetCharacterTeamMemberMainName(leader_npc_no, i));
				UNLOCK_CHARACTER(0);
				if(strcmp(tempmainname, "") != 0)
				{			
					LOCK_CONNECTION(0);
					cn_index = FindConnectionByName(tempmainname);
					UNLOCK_CONNECTION(0);			
					if(cn_index >= 0 && cn_index < 500)
					{
						server_send_packet_to_one(&Pos_Cn[cn_index], &send_packet);
					}
				}			
			}						
		}	
		LOCK_CHARACTER(0);
		// 處理滑鼠上的物品
		ServerDoClearOnMouseItemForPlayerExit(Find_Idx);
		// 將玩家角色資料轉成資料庫格式
		ConvertZoneCharacterDataToDBCharacter(Find_Idx, &DbCharacter);		
		UNLOCK_CHARACTER(0);
		// 存物品
		SaveCharacterBankData(Find_Idx);
		SaveCharacterItemDataByMainNameAndIndex(Find_Idx);		
		// 存玩家繳色其他資料
		strcpy(DbCharacter.ZoneName, ZoneName);
		strcpy(DbCharacter.LeaderName, "");
		iRet = UpdateRecordOfCharacterDB(&DbCharacter);
		// 將該資料清為零
		LOCK_CHARACTER(0);
		ClearOneCharacter(Find_Idx);
		UNLOCK_CHARACTER(0);
		if(iRet == TRUE)
		{
			send_packet.Header.dwType = PREPARE_PLAYER_EXIT_GAME_OK;
			send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER);

			CompressPacket(&send_packet, &send_compacket);
			
			LOCK_CONNECTION(0);
			QueuePacket(cn, &send_compacket, CONNECTED_SERVER_ZONE);
			UNLOCK_CONNECTION(0);
		}
	}
}
// -----------------------------------------------------------------------------
void	ServerDoNewZoneInfo(TPOS_CN *cn, TPOS_PACKET *packet) 
{	
	TPOS_EVENT_NEWZONEINFO	EventNewZoneInfo;
	int x;

	memcpy(&EventNewZoneInfo, packet->data.cBuf, sizeof(TPOS_EVENT_NEWZONEINFO));
    LOCK_ZONEINFO(0);
    x = FindUsableZoneInfo();
    if(x >= 0)
    {
		strcpy(ZoneInfo[x].cName , EventNewZoneInfo.cName);
        strcpy(ZoneInfo[x].cMapName, EventNewZoneInfo.cMapName);
        strcpy(ZoneInfo[x].cAddr, EventNewZoneInfo.cAddr);
        ZoneInfo[x].dwPort = EventNewZoneInfo.dwPort;
        ZoneInfo[x].dwPlayerCount = 0;
		ZoneInfo[x].dwType = EventNewZoneInfo.dwType;
	}
    UNLOCK_ZONEINFO(0);	

}
// -----------------------------------------------------------------------------
void	ServerDoOneZoneClose(TPOS_CN *cn, TPOS_PACKET *packet) 
{
	TPOS_EVENT_CLOSEZONEINFO	EventCloseZoneInfo;
	int x;
	
	memcpy(&EventCloseZoneInfo, packet->data.cBuf, sizeof(TPOS_EVENT_CLOSEZONEINFO));
	LOCK_ZONEINFO(0);	
	x = FindZoneInfoByName(EventCloseZoneInfo.cName);
	if(x >= 0)
	{
		strcpy(ZoneInfo[x].cName, "");
		strcpy(ZoneInfo[x].cMapName, "");
		strcpy(ZoneInfo[x].cAddr, "");
		ZoneInfo[x].dwPort = 0;
		ZoneInfo[x].dwPlayerCount = 0;
	}
	UNLOCK_ZONEINFO(0);
}
// -----------------------------------------------------------------------------
void	ServerDoRefreshZoneInfo(TPOS_CN *cn, TPOS_PACKET *packet) 
{	
	TPOS_EVENT_REFRESHZONEINFO	EventRefreshZoneInfo;
	int x;

	memcpy(&EventRefreshZoneInfo, packet->data.cBuf, sizeof(TPOS_EVENT_REFRESHZONEINFO));
	LOCK_ZONEINFO(0);
	x = FindZoneInfoByName(EventRefreshZoneInfo.cName);
	if(x >= 0)
	{
		ZoneInfo[x].dwPlayerCount = EventRefreshZoneInfo.dwPlayerCount;
	}
	UNLOCK_ZONEINFO(0);
}
// -----------------------------------------------------------------------------
void	ServerDoGetZoneInfo(TPOS_CN *cn, TPOS_PACKET *packet) 
{	
	TPOS_EVENT_GETZONEINFO	EventGetZoneInfo;
	int						x;
	char					str[256];
	
	memcpy(&EventGetZoneInfo, packet->data.cBuf, sizeof(TPOS_EVENT_GETZONEINFO));
	if(EventGetZoneInfo.dwIndex != END) 
	{
		x = EventGetZoneInfo.dwIndex;
		LOCK_ZONEINFO(0);
		//x = FindUsableZoneInfo();
		if(x >= 0)
		{
			strcpy(ZoneInfo[x].cName, EventGetZoneInfo.cZone);
			strcpy(ZoneInfo[x].cMapName, EventGetZoneInfo.cMapName);
			strcpy(ZoneInfo[x].cAddr, EventGetZoneInfo.cAddr);
			ZoneInfo[x].dwPort = EventGetZoneInfo.dwPort;
			ZoneInfo[x].dwPlayerCount = EventGetZoneInfo.dwPlayerCount;
			ZoneInfo[x].dwType = EventGetZoneInfo.dwType;
			sprintf(str,"ZoneName : %s , ZoneIndex : %d , ZoneMap : %s , ZoneAddr : %s , ZonePort : %d , ZoneType : %d",
						ZoneInfo[x].cName,
						x,
						ZoneInfo[x].cMapName,
						ZoneInfo[x].cAddr,
						ZoneInfo[x].dwPort,
						ZoneInfo[x].dwType);
		}
		UNLOCK_ZONEINFO(0);
		
		SaveMsgToLog("SYSTEM",str);
		
		RequestForZoneInfo(EventGetZoneInfo.dwIndex + 1);
	}	
}
// -----------------------------------------------------------------------------
void	ConvertDBCharacterDataToZoneCharacter(DWORD npc_no, TPOS_DB_CHARACTER *dbcharacter)
{
	int	i;
	TPOS_ITEM	tempitem;	

	for(i = 0;i < MAX_CHARACTER_BAG_ITEMS;i++)
	{
		memset(&tempitem, 0x0, sizeof(TPOS_ITEM));
		SetItemID(&tempitem, dbcharacter->BagItem[i]);
		SetCharacterBagItem(npc_no, i, &tempitem);
	}
	SetCharacterBitState(npc_no, dbcharacter->BitState);
	SetCharacterCareer(npc_no, dbcharacter->Career);
	SetCharacterCareerLevel(npc_no, dbcharacter->CareerLevel);
	SetCharacterColor(npc_no, dbcharacter->Color);
	SetCharacterCountry(npc_no, dbcharacter->Country);
	SetCharacterShipDegreeDir(npc_no, dbcharacter->DegreeDir);
	SetCharacterDir(npc_no, dbcharacter->Dir);
	SetCharacterDodgeRate(npc_no, dbcharacter->DodgeRate);
	SetCharacterDoingKind(npc_no, dbcharacter->DoingKind);
	memset(&tempitem, 0x0, sizeof(TPOS_ITEM));
	SetItemID(&tempitem, dbcharacter->EquBody);
	SetCharacterEquipBody(npc_no, &tempitem);
	memset(&tempitem, 0x0, sizeof(TPOS_ITEM));
	SetItemID(&tempitem, dbcharacter->EquFeet);
	SetCharacterEquipFeet(npc_no, &tempitem);
	memset(&tempitem, 0x0, sizeof(TPOS_ITEM));
	SetItemID(&tempitem, dbcharacter->EquGlove);
	SetCharacterEquipGlove(npc_no, &tempitem);
	memset(&tempitem, 0x0, sizeof(TPOS_ITEM));
	SetItemID(&tempitem, dbcharacter->EquHead);
	SetCharacterEquipHead(npc_no, &tempitem);
	memset(&tempitem, 0x0, sizeof(TPOS_ITEM));
	SetItemID(&tempitem, dbcharacter->EquNeck);
	SetCharacterEquipNeck(npc_no, &tempitem);
	memset(&tempitem, 0x0, sizeof(TPOS_ITEM));
	SetItemID(&tempitem, dbcharacter->EquOtherA);
	SetCharacterEquipOtherA(npc_no, &tempitem);
	memset(&tempitem, 0x0, sizeof(TPOS_ITEM));
	SetItemID(&tempitem, dbcharacter->EquOtherB);
	SetCharacterEquipOtherB(npc_no, &tempitem);
	memset(&tempitem, 0x0, sizeof(TPOS_ITEM));
	SetItemID(&tempitem, dbcharacter->EquOtherC);
	SetCharacterEquipOtherC(npc_no, &tempitem);
	memset(&tempitem, 0x0, sizeof(TPOS_ITEM));
	SetItemID(&tempitem, dbcharacter->EquWaist);
	SetCharacterEquipWaist(npc_no, &tempitem);		
	memset(&tempitem, 0x0, sizeof(TPOS_ITEM));
	SetItemID(&tempitem, dbcharacter->EquWeapon);
	SetCharacterEquipWeapon(npc_no, &tempitem);
	memset(&tempitem, 0x0, sizeof(TPOS_ITEM));
	SetItemID(&tempitem, dbcharacter->EquWrist);
	SetCharacterEquipWrist(npc_no, &tempitem);
	SetCharacterExp(npc_no, dbcharacter->Exp);
	SetCharacterEyes(npc_no, dbcharacter->Eyes);
	SetCharacterLandFileIndex(npc_no, dbcharacter->LandFileIndex);
	SetCharacterSeaFileIndex(npc_no, dbcharacter->SeaFileIndex);
	SetCharacterFinalAtt(npc_no, dbcharacter->FinalAttack);
	SetCharacterFinalDefence(npc_no, dbcharacter->FinalDefence);
	SetCharacterFinalExplodeRate(npc_no, dbcharacter->FinalExplodeRate);
	SetCharacterShipSpeedX(npc_no, dbcharacter->FSpeedX);
	SetCharacterShipSpeedY(npc_no, dbcharacter->FSpeedY);
	SetCharacterGoodEvil(npc_no, dbcharacter->GoodEvil);
	SetCharacterGuildName(npc_no, dbcharacter->Guild);
	SetCharacterHp(npc_no, dbcharacter->Hp);
	SetCharacterMaxHp(npc_no, dbcharacter->MaxHp);
	SetCharacterHpRes(npc_no, dbcharacter->HpRes);
	SetCharacterMp(npc_no, dbcharacter->Mp);
	SetCharacterMaxMp(npc_no, dbcharacter->MaxMp);
	SetCharacterMpRes(npc_no, dbcharacter->MpRes);
	SetCharacterAccount(npc_no, dbcharacter->ID);
	SetCharacterIndex(npc_no, dbcharacter->Index);
	SetCharacterInitIns(npc_no, dbcharacter->InitIns);
	SetCharacterInitLucky(npc_no, dbcharacter->InitLucky);
	SetCharacterInitStr(npc_no, dbcharacter->InitStr);
	SetCharacterInitWit(npc_no, dbcharacter->InitWit);
	SetCharacterLevelUpStr(npc_no, dbcharacter->LevUpStr);
	SetCharacterLevelUpIns(npc_no, dbcharacter->LevUpIns);
	SetCharacterLevelUpWit(npc_no, dbcharacter->LevUpWit);
	SetCharacterLevelUpLucky(npc_no, dbcharacter->LevUpLucky);
	// Hawke  [1/16/2003]
	SetCharacterFinalStr(npc_no, dbcharacter->InitStr + dbcharacter->LevUpStr);
	SetCharacterFinalIns(npc_no, dbcharacter->InitIns + dbcharacter->LevUpIns);
	SetCharacterFinalWit(npc_no, dbcharacter->InitWit + dbcharacter->LevUpWit);
	SetCharacterFinalLucky(npc_no, dbcharacter->InitLucky + dbcharacter->LevUpLucky);
	for(i = 0;i<MAX_CHARACTER_FN_SKILLS;i++)
	{
		SetCharacterLandFnSkillHand(npc_no, i, dbcharacter->LandFnSkillHand[i]);
		SetCharacterLandFnSkillNo(npc_no, i, dbcharacter->LandFnSkillNo[i]);
		SetCharacterSeaFnSkillHand(npc_no, i, dbcharacter->SeaFnSkillHand[i]);
		SetCharacterSeaFnSkillNo(npc_no, i, dbcharacter->SeaFnSkillNo[i]);
	}
	
	SetCharacterLandLeftSkill(npc_no, dbcharacter->LandLeftSkill);
	SetCharacterLandRightSkill(npc_no, dbcharacter->LandRightSkill);
	SetCharacterLevel(npc_no, dbcharacter->Level);	
	SetCharacterLogo(npc_no, dbcharacter->Logo);
	SetCharacterMainName(npc_no, dbcharacter->MainName);
	SetCharacterMainNameColor(npc_no, dbcharacter->MainNameColor);
	SetCharacterMessageColor(npc_no, dbcharacter->MessageColor);
	SetCharacterBodyMoney(npc_no ,dbcharacter->Money);
	SetCharacterMouth(npc_no, dbcharacter->Mouth);
	SetCharacterMoveSpeed(npc_no, dbcharacter->Mspeed);
	SetCharacterNickName(npc_no, dbcharacter->NickName);
	SetCharacterNickNameColor(npc_no, dbcharacter->NickNameColor);
	SetCharacterNobilityName(npc_no, dbcharacter->Nobility);
	SetCharacterOffice(npc_no, dbcharacter->Office);
	memset(&tempitem, 0x0, sizeof(TPOS_ITEM));
	SetItemID(&tempitem, dbcharacter->OnMouseItem);
	SetCharacterOnMouseItem(npc_no, &tempitem);
	SetCharacterParryRate(npc_no, dbcharacter->ParryRate);
	SetCharacterPkCount(npc_no, dbcharacter->PkCount);
	SetCharacterPkedCount(npc_no, dbcharacter->PkedCount);
	SetCharacterPrestige(npc_no, dbcharacter->Prestige);
	SetCharacterPropertyPoint(npc_no, dbcharacter->PropertyPoint);
	SetCharacterQQID(npc_no, dbcharacter->QQID);
	SetCharacterShipSailSize(npc_no, dbcharacter->SailSize);
	for(i = 0;i < MAX_CHARACTER_SASH_ITEMS;i++)
	{	
		memset(&tempitem, 0x0, sizeof(TPOS_ITEM));
		SetItemID(&tempitem, dbcharacter->SashItem[i]);
		SetCharacterSashItem(npc_no, i, &tempitem);
	}	
	SetCharacterSeaLeftSkill(npc_no, dbcharacter->SeaLeftSkill);
	SetCharacterSeaRightSkill(npc_no, dbcharacter->SeaRightSkill);
	SetCharacterSex(npc_no, dbcharacter->Sex);
	SetCharacterSightRange(npc_no, dbcharacter->SightRange);
	for(i = 0;i < MAX_CHARACTER_SKILLS;i++)
	{
		SetCharacterSkillLevel(npc_no, i, dbcharacter->SkillLevel[i]);
		SetCharacterSkillNo(npc_no, i, dbcharacter->SkillNo[i]);
	}
	SetCharacterSpouseName(npc_no, dbcharacter->Spouse);
	SetCharacterStopRadius(npc_no, dbcharacter->StopRadius);
	SetCharacterTalkBackColor(npc_no, dbcharacter->TalkBackColor);
	for(i = 0;i< MAX_CHARACTER_TRANS_ITEMS;i++)
	{	
		memset(&tempitem, 0x0, sizeof(TPOS_ITEM));
		SetItemID(&tempitem, dbcharacter->TransItem[i]);
		SetCharacterTransItem(npc_no, i, &tempitem);
	}
	memset(&tempitem, 0x0, sizeof(TPOS_ITEM));
	SetItemID(&tempitem, dbcharacter->TreasureItem);	
	SetCharacterTreasureItem(npc_no, &tempitem);
	SetCharacterShipTurn(npc_no, dbcharacter->Turn);
	SetCharacterShipWeight(npc_no, dbcharacter->Weight);
	SetCharacterPosition(npc_no, dbcharacter->X, dbcharacter->Y, dbcharacter->Z);
	SetCharacterZoneName(npc_no, dbcharacter->ZoneName);
	for(i = 0;i < MAX_CHARACTER_PARTS;i++)
	{
		SetCharacterPartRGB(npc_no, i, dbcharacter->PartRGB[i]);
	}	
	SetCharacterNameColorTicks(npc_no, dbcharacter->NameColorTicks);
	SetCharacterTotalOnlineTicks(npc_no, dbcharacter->TotalOnlineTicks);
}
// -----------------------------------------------------------------------------
void	ConvertZoneCharacterDataToDBCharacter(DWORD npc_no, TPOS_DB_CHARACTER *dbcharacter)
{
	int			i;
	TPOS_ITEM	tempitem;

	memset(dbcharacter, 0x0, sizeof(TPOS_DB_CHARACTER));

	for(i = 0;i < MAX_CHARACTER_BAG_ITEMS;i++)
	{
		memset(&tempitem, 0x0, sizeof(TPOS_ITEM));
		GetCharacterBagItem(npc_no, i, &tempitem);
		dbcharacter->BagItem[i] = tempitem.ID;
	}	
	strcpy(dbcharacter->ID, GetCharacterAccount(npc_no));
	dbcharacter->BitState = GetCharacterBitState(npc_no);
	dbcharacter->Career = (char)GetCharacterCareer(npc_no);
	dbcharacter->CareerLevel = (UCHAR)GetCharacterCareerLevel(npc_no);
	dbcharacter->Color = (char)GetCharacterColor(npc_no);
	dbcharacter->Country = (char)GetCharacterCountry(npc_no);
	dbcharacter->DegreeDir = (char)GetCharacterShipDegreeDir(npc_no);
	dbcharacter->Dir = (char)GetCharacterDir(npc_no);
	dbcharacter->DodgeRate = GetCharacterDodgeRate(npc_no);
	dbcharacter->DoingKind = GetCharacterDoingKind(npc_no);
	memset(&tempitem, 0x0, sizeof(TPOS_ITEM));
	GetCharacterEquipBody(npc_no, &tempitem);
	dbcharacter->EquBody = tempitem.ID;
	memset(&tempitem, 0x0, sizeof(TPOS_ITEM));	
	GetCharacterEquipFeet(npc_no, &tempitem);
	dbcharacter->EquFeet = tempitem.ID;
	memset(&tempitem, 0x0, sizeof(TPOS_ITEM));
	GetCharacterEquipGlove(npc_no, &tempitem);
	dbcharacter->EquGlove = tempitem.ID;
	memset(&tempitem, 0x0, sizeof(TPOS_ITEM));	
	GetCharacterEquipHead(npc_no, &tempitem);
	dbcharacter->EquHead = tempitem.ID;
	memset(&tempitem, 0x0, sizeof(TPOS_ITEM));	
	GetCharacterEquipNeck(npc_no, &tempitem);
	dbcharacter->EquNeck = tempitem.ID;
	memset(&tempitem, 0x0, sizeof(TPOS_ITEM));	
	GetCharacterEquipOtherA(npc_no, &tempitem);
	dbcharacter->EquOtherA = tempitem.ID;
	memset(&tempitem, 0x0, sizeof(TPOS_ITEM));	
	GetCharacterEquipOtherB(npc_no, &tempitem);
	dbcharacter->EquOtherB = tempitem.ID;
	memset(&tempitem, 0x0, sizeof(TPOS_ITEM));	
	GetCharacterEquipOtherC(npc_no, &tempitem);
	dbcharacter->EquOtherC = tempitem.ID;
	memset(&tempitem, 0x0, sizeof(TPOS_ITEM));	
	GetCharacterEquipWaist(npc_no, &tempitem);		
	dbcharacter->EquWaist = tempitem.ID;
	memset(&tempitem, 0x0, sizeof(TPOS_ITEM));	
	GetCharacterEquipWeapon(npc_no, &tempitem);
	dbcharacter->EquWeapon = tempitem.ID;
	memset(&tempitem, 0x0, sizeof(TPOS_ITEM));	
	GetCharacterEquipWrist(npc_no, &tempitem);
	dbcharacter->EquWrist = tempitem.ID;
	dbcharacter->Exp = GetCharacterExp(npc_no);
	dbcharacter->Eyes = (char)GetCharacterEyes(npc_no);	
	dbcharacter->LandFileIndex = GetCharacterLandFileIndex(npc_no);
	dbcharacter->SeaFileIndex = GetCharacterSeaFileIndex(npc_no);
	dbcharacter->FinalAttack = GetCharacterFinalAtt(npc_no);
	dbcharacter->FinalDefence = GetCharacterFinalDefence(npc_no);
	dbcharacter->FinalExplodeRate = GetCharacterFinalExplodeRate(npc_no);
	dbcharacter->FSpeedX = GetCharacterShipSpeedX(npc_no);
	dbcharacter->FSpeedY = GetCharacterShipSpeedY(npc_no);
	dbcharacter->GoodEvil = GetCharacterGoodEvil(npc_no);
	strcpy(dbcharacter->Guild, GetCharacterGuildName(npc_no));
	dbcharacter->Hp = GetCharacterHp(npc_no);
	dbcharacter->MaxHp = GetCharacterMaxHp(npc_no);
	dbcharacter->HpRes = GetCharacterHpRes(npc_no);
	dbcharacter->Mp = GetCharacterMp(npc_no);
	dbcharacter->MaxMp = GetCharacterMaxMp(npc_no);
	dbcharacter->MpRes = GetCharacterMpRes(npc_no);
	strcpy(dbcharacter->ID,GetCharacterAccount(npc_no));
	dbcharacter->Index = (UHINT)GetCharacterIndex(npc_no);
	dbcharacter->InitIns = GetCharacterInitIns(npc_no);
	dbcharacter->InitLucky = GetCharacterInitLucky(npc_no);
	dbcharacter->InitStr = GetCharacterInitStr(npc_no);
	dbcharacter->InitWit = GetCharacterInitWit(npc_no);
	dbcharacter->LevUpIns = GetCharacterLevelUpIns(npc_no);
	dbcharacter->LevUpStr = GetCharacterLevelUpStr(npc_no);
	dbcharacter->LevUpWit = GetCharacterLevelUpWit(npc_no);
	dbcharacter->LevUpLucky = GetCharacterLevelUpLucky(npc_no);
	
	for(i = 0;i<MAX_CHARACTER_FN_SKILLS;i++)
	{
		dbcharacter->LandFnSkillHand[i] = (char)GetCharacterLandFnSkillHand(npc_no, i);
		dbcharacter->LandFnSkillNo[i] = GetCharacterLandFnSkillNo(npc_no, i);
		dbcharacter->SeaFnSkillHand[i] = (char)GetCharacterSeaFnSkillHand(npc_no, i);
		dbcharacter->SeaFnSkillNo[i] = GetCharacterSeaFnSkillNo(npc_no, i);
	}
	
	dbcharacter->LandLeftSkill = GetCharacterLandLeftSkill(npc_no);
	dbcharacter->LandRightSkill = GetCharacterLandRightSkill(npc_no);
	dbcharacter->Level = GetCharacterLevel(npc_no);	
	dbcharacter->Logo = GetCharacterLogo(npc_no);
	strcpy(dbcharacter->MainName, GetCharacterMainName(npc_no));
	dbcharacter->MainNameColor = (char)GetCharacterMainNameColor(npc_no);
	dbcharacter->MessageColor = (char)GetCharacterMessageColor(npc_no);
	dbcharacter->Money = GetCharacterBodyMoney(npc_no);
	dbcharacter->Mouth = (char)GetCharacterMouth(npc_no);
	dbcharacter->Mspeed = GetCharacterMoveSpeed(npc_no);
	strcpy(dbcharacter->NickName, GetCharacterNickName(npc_no));
	dbcharacter->NickNameColor = (char)GetCharacterNickNameColor(npc_no);
	strcpy(dbcharacter->Nobility, GetCharacterNobilityName(npc_no));
	dbcharacter->Office = GetCharacterOffice(npc_no);
	memset(&tempitem, 0x0, sizeof(TPOS_ITEM));	
	GetCharacterOnMouseItem(npc_no, &tempitem);
	dbcharacter->OnMouseItem = tempitem.ID;
	dbcharacter->ParryRate = GetCharacterParryRate(npc_no);
	dbcharacter->PkCount = GetCharacterPkCount(npc_no);
	dbcharacter->PkedCount = GetCharacterPkedCount(npc_no);
	dbcharacter->Prestige = GetCharacterPrestige(npc_no);
	dbcharacter->PropertyPoint = GetCharacterPropertyPoint(npc_no);
	dbcharacter->QQID = GetCharacterQQID(npc_no);
	dbcharacter->SailSize = (UHINT)GetCharacterShipSailSize(npc_no);
	for(i = 0;i < MAX_CHARACTER_SASH_ITEMS;i++)
	{	
		memset(&tempitem, 0x0, sizeof(TPOS_ITEM));		
		GetCharacterSashItem(npc_no, i, &tempitem);
		dbcharacter->SashItem[i] = tempitem.ID;
	}	
	dbcharacter->SeaLeftSkill = GetCharacterSeaLeftSkill(npc_no);
	dbcharacter->SeaRightSkill = GetCharacterSeaRightSkill(npc_no);
	dbcharacter->Sex = (char)GetCharacterSex(npc_no);
	dbcharacter->SightRange = GetCharacterSightRange(npc_no);
	for(i = 0;i < MAX_CHARACTER_SKILLS;i++)
	{
		dbcharacter->SkillLevel[i] = GetCharacterSkillLevel(npc_no, i);
		dbcharacter->SkillNo[i] = (SHINT)GetCharacterSkillNo(npc_no, i);
	}
	strcpy(dbcharacter->Spouse, GetCharacterSpouseName(npc_no));
	dbcharacter->StopRadius = GetCharacterStopRadius(npc_no);
	dbcharacter->TalkBackColor = (char)GetCharacterTalkBackColor(npc_no);
	for(i = 0;i< MAX_CHARACTER_TRANS_ITEMS;i++)
	{	
		memset(&tempitem, 0x0, sizeof(TPOS_ITEM));		
		GetCharacterTransItem(npc_no, i, &tempitem);
		dbcharacter->TransItem[i] = tempitem.ID;
	}
	memset(&tempitem, 0x0, sizeof(TPOS_ITEM));	
	GetCharacterTreasureItem(npc_no, &tempitem);
	dbcharacter->TreasureItem = tempitem.ID;
	dbcharacter->Turn = (UHINT)GetCharacterShipTurn(npc_no);
	dbcharacter->Weight = (UHINT)GetCharacterShipWeight(npc_no);
	GetCharacterPosition(npc_no, &dbcharacter->X, &dbcharacter->Y, &dbcharacter->Z);
	strcpy(dbcharacter->ZoneName, GetCharacterZoneName(npc_no));	
	for(i = 0;i < MAX_CHARACTER_PARTS;i++)
	{
		dbcharacter->PartRGB[i] = GetCharacterPartRGB(npc_no, i);
	}
	dbcharacter->NameColorTicks = GetCharacterNameColorTicks(npc_no);
	dbcharacter->TotalOnlineTicks = GetCharacterTotalOnlineTicks(npc_no);
}
// -----------------------------------------------------------------------------
void	ConvertZoneCharacterDataToEventGetPlayerList(SLONG npc_no,TPOS_EVENT_GETPLAYERLIST *eventplayerlist)
{
	int i;

	memset(eventplayerlist ,0x0, sizeof(TPOS_EVENT_GETPLAYERLIST));

	eventplayerlist->cColor = (char)GetCharacterColor(npc_no);
	eventplayerlist->cEyes = (char)GetCharacterEyes(npc_no);
	strcpy(eventplayerlist->cMainName, GetCharacterMainName(npc_no));
	eventplayerlist->cMouth = (char)GetCharacterMouth(npc_no);
	eventplayerlist->iHp = GetCharacterHp(npc_no);
	eventplayerlist->iIndex = npc_no;
	eventplayerlist->iMp = GetCharacterMp(npc_no);
	eventplayerlist->iMspeed = GetCharacterMoveSpeed(npc_no);
	GetCharacterPosition(npc_no, &eventplayerlist->lX, &eventplayerlist->lY, &eventplayerlist->lZ);
	eventplayerlist->slDoingKind = GetCharacterDoingKind(npc_no);
	eventplayerlist->slFileIndex = GetCharacterFileIndex(npc_no);
	eventplayerlist->lDoingStep = GetCharacterDoingStep(npc_no);		
    eventplayerlist->iMaxHp = GetCharacterMaxHp(npc_no);
	eventplayerlist->iMaxMp = GetCharacterMaxMp(npc_no);
    eventplayerlist->Picture = (char)GetCharacterPicture(npc_no);
    eventplayerlist->cMainNameColor = (char)GetCharacterMainNameColor(npc_no);
    eventplayerlist->cNickNameColor = (char)GetCharacterNickNameColor(npc_no);
    eventplayerlist->cMessageColor = (char)GetCharacterMessageColor(npc_no);
    eventplayerlist->cTalkBackColor = (char)GetCharacterTalkBackColor(npc_no);
	eventplayerlist->dwLogo = GetCharacterLogo(npc_no);
    eventplayerlist->iLevel = GetCharacterLevel(npc_no);
    eventplayerlist->iSightRange = GetCharacterSightRange(npc_no);
	eventplayerlist->BitState = GetCharacterBitState(npc_no);
	eventplayerlist->iDirFrame = (UHINT)GetCharacterDirFrame(npc_no);
	eventplayerlist->lDestNo = GetCharacterDestID(npc_no);
	eventplayerlist->lOrigNo = GetCharacterOrigID(npc_no);
	GetCharacterDestPosition(npc_no, &eventplayerlist->lDestX, 
									 &eventplayerlist->lDestY,
									 &eventplayerlist->lDestZ);
	GetCharacterOrigPosition(npc_no, &eventplayerlist->lOrigX,
									 &eventplayerlist->lOrigY,
									 &eventplayerlist->lOrigZ);	
	eventplayerlist->cDir = (char)GetCharacterDir(npc_no);
	eventplayerlist->SailSize = (UHINT)GetCharacterShipSailSize(npc_no);
	eventplayerlist->Turn = (UHINT)GetCharacterShipTurn(npc_no);
	eventplayerlist->Weight = (UHINT)GetCharacterShipWeight(npc_no);
	eventplayerlist->DegreeDir = GetCharacterShipDegreeDir(npc_no);
	for(i = 0;i < MAX_CHARACTER_PARTS;i++)
	{
		eventplayerlist->PartRGB[i] = GetCharacterPartRGB(npc_no, i);
	}
}
// -----------------------------------------------------------------------------
void	encode_sea_npc_sync_position(SLONG &sync_x,SLONG &sync_y,SLONG &sync_z,SLONG degree_dir, SLONG x, SLONG y,SLONG speed_x, SLONG speed_y)
{	
	// degree_dir (0-359) 9b
	// speed_x (+-500)    10b
	// speed_y (+-500)	  10b	
	// sync_z: 3bit + 9bit(degree_dir) + 10bit(speedx) + 10bit(speedy)
	ULONG	ulong_speed_x, ulong_speed_y, ulong_degree_dir;	

	ulong_speed_x = (ULONG)(500 + speed_x);
	ulong_speed_y = (ULONG)(500 + speed_y);
	ulong_speed_x = (ulong_speed_x << 10) & 0x000ffc00;
	ulong_speed_y = ulong_speed_y & 0x000003ff;
	ulong_degree_dir = (ULONG)degree_dir;
	ulong_degree_dir = (ulong_degree_dir << 20) & 0x3ff00000;
	sync_z = ulong_degree_dir | ulong_speed_x | ulong_speed_y;
	sync_x = x;
	sync_y = y;
}
// -----------------------------------------------------------------------------

void	decode_sea_npc_sync_position(SLONG sync_x, SLONG sync_y, SLONG sync_z, 
									 SLONG &degree_dir, SLONG &x, SLONG &y, 
									 SLONG &speed_x, SLONG &speed_y)
{
	ULONG	ulong_z;
	ULONG	ulong_speed_x, ulong_speed_y, ulong_degree_dir;

	ulong_z = (ULONG)sync_z;
	ulong_speed_y = ulong_z & 0x000003ff;
	ulong_speed_x = (ulong_z & 0x000ffc00) >> 10;
	ulong_degree_dir = (ulong_z & 0x3ff00000) >> 20;
	degree_dir = (SLONG)ulong_degree_dir;
	speed_x = (SLONG)ulong_speed_x - 500;
	speed_y = (SLONG)ulong_speed_y - 500;
	x = sync_x;
	y = sync_y;
}
// -----------------------------------------------------------------------------

__inline	float	float_to_precision_10_float(float value)
{
	return	(float)((long)(value * 10) / 10.0);
}
//-------------------------------------------------------------------------------
// Set Weather
//-------------------------------------------------------------------------------
int SetWeather(TPOS_WEATHER *Weather)
{
    switch(Weather->dType)
    {
    case WEATHER_DUMMY:
        break;
    case WEATHER_NORMAL:
        ZoneWeather->dWeatherType=WEATHER_NORMAL;
        ZoneWeather->dRainActive=WEATHER_STOP;
        ZoneWeather->dSnowActive=WEATHER_STOP;
        ZoneWeather->dCloudActive=WEATHER_STOP;
        ZoneWeather->dThunderActive=WEATHER_STOP;
        ZoneWeather->dEarthQuakeActive=WEATHER_STOP;
        break;	 
    case WEATHER_RAIN:
        {
            switch(Weather->dActive)
            {
            case WEATHER_STARTUP:
                ZoneWeather->dWeatherType |= WEATHER_RAIN;
                ZoneWeather->dRainActive = WEATHER_STARTUP;
                ZoneWeather->dRainSize = Weather->dSize;		  
                break;
            case WEATHER_STOP:
                ZoneWeather->dWeatherType &= ~WEATHER_RAIN;
                ZoneWeather->dRainActive = WEATHER_STOP;
                break;
            }
        }
        break;
    case WEATHER_SNOW:
        {
            switch(Weather->dActive)
            {
            case WEATHER_STARTUP:
                ZoneWeather->dWeatherType |= WEATHER_SNOW;
                ZoneWeather->dSnowActive = WEATHER_STARTUP;
                ZoneWeather->dSnowSize = Weather->dSize;
                
                break;
            case WEATHER_STOP:
                ZoneWeather->dWeatherType &= ~WEATHER_SNOW;
                ZoneWeather->dSnowActive = WEATHER_STOP;
                break;
            }
        }
        break;

    case WEATHER_CLOUD:
        {
            switch(Weather->dActive)
            {
            case WEATHER_STARTUP:
                ZoneWeather->dWeatherType |= WEATHER_CLOUD;
                ZoneWeather->dCloudActive = WEATHER_STARTUP;
                ZoneWeather->dCloudSize = Weather->dSize;
                break;
            case WEATHER_STOP:
                ZoneWeather->dWeatherType &= ~WEATHER_CLOUD;
                ZoneWeather->dCloudActive = WEATHER_STOP;
                break;
            }
        }
        break;

    case WEATHER_THUNDER:
        {
            switch(Weather->dActive)
            {
            case WEATHER_STARTUP:
                ZoneWeather->dWeatherType |= WEATHER_THUNDER;
                ZoneWeather->dThunderActive = WEATHER_STARTUP;
                ZoneWeather->dThunderSize = Weather->dSize;
                break;
            case WEATHER_STOP:
                ZoneWeather->dWeatherType &= ~WEATHER_THUNDER;
                ZoneWeather->dThunderActive = WEATHER_STOP;
                break;
            }
        }
        break;

    case WEATHER_EARTHQUAKE:
        {
            switch(Weather->dActive)
            {
            case WEATHER_STARTUP:
                ZoneWeather->dWeatherType |= WEATHER_EARTHQUAKE;
                ZoneWeather->dEarthQuakeActive = WEATHER_STARTUP;
                ZoneWeather->dEarthQuakeSize = Weather->dSize;
                break;
            case WEATHER_STOP:
                ZoneWeather->dWeatherType &= ~WEATHER_EARTHQUAKE;
                ZoneWeather->dEarthQuakeActive = WEATHER_STOP;
                break;
            }
        }
        break;
    }

    if(Weather->dWindSize!=WIND_DUMMY)
    {
        ZoneWeather->dWindDir=Weather->dWindDir;
        ZoneWeather->dWindSize=Weather->dWindSize; 
    }
    return DLL_OK;
}
// -----------------------------------------------------------------------------
int	ReturnZoneType(DWORD zonetype)
{
	int city,field,sail,newbie,pk,findgold,birth,normal;
	
	city	 = (zonetype & 0x0000000f);
	field    = (zonetype & 0x000000f0) >> 4;
	sail     = (zonetype & 0x00000f00) >> 8;
	newbie   = (zonetype & 0x0000f000) >> 12;
	pk		 = (zonetype & 0x000f0000) >> 16;
	findgold = (zonetype & 0x00f00000) >> 20;	
	birth	 = (zonetype & 0x0f000000) >> 24;	
	normal	 = (zonetype & 0xf0000000) >> 28;

	if(city == 1)
	{
		if(normal == 1)return CITY_NORMAL;
		if(newbie == 1)return CITY_NEWBIE;
		if(pk == 1)return CITY_PK;
		if(findgold == 1)return CITY_FINDGOLD;
		if(birth == 1)return CITY_BIRTH;	
	}
	if(field == 1)
	{
		if(normal == 1)return FIELD_NORMAL;
		if(newbie == 1)return FIELD_NEWBIE;
		if(pk == 1)return FIELD_PK;
		if(findgold == 1)return FIELD_FINDGOLD;
		if(birth == 1)return FIELD_BIRTH;	
	}
	if(sail == 1)
	{
		if(normal == 1)return SAIL_NORMAL;
		if(newbie == 1)return SAIL_NEWBIE;
		if(pk == 1)return SAIL_PK;
		if(findgold == 1)return SAIL_FINDGOLD;
		if(birth == 1)return SAIL_BIRTH;	
	}
	return CITY_NORMAL;
}
// -----------------------------------------------------------------------------
void	ServerDoClearBadConnect()
{
	int		i;
	SLONG	dialog_dest_index;
	SLONG	dialog_with_count;
	ULONG	qq_id;	
	TPOS_PACKET					send_packet;
	TPOS_COMPACKET				send_compacket;
	TPOS_EVENT_QQPLAYERLOGOUT	EventQQPlayerLogout;
	
	for(i = 0;i < MAX_PLAYER_PER_ZONE;i++)
	{
		if(BadConnect[i] == TRUE)
		{	
			LOCK_CHARACTER(0);
			dialog_dest_index = GetCharacterDialogDestIndex(i);
			qq_id = GetCharacterQQID(i);
			UNLOCK_CHARACTER(0);
			
			// QQ 離線
			send_packet.Header.dwType = QQ_PLAYER_LOGOUT;
			send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_QQPLAYERLOGOUT);		
			EventQQPlayerLogout.QQID = qq_id;
			memcpy(send_packet.data.cBuf, &EventQQPlayerLogout, sizeof(TPOS_EVENT_QQPLAYERLOGOUT));
			CompressPacket(&send_packet, &send_compacket);
			QueuePacket(World, &send_compacket, CONNECTED_SERVER_WORLD);

			SendPlayerExitToAll(i);			

			// 清除如果有在跟 NPC 的對話
			if(dialog_dest_index != 0)
			{
				LOCK_CHARACTER(0);
				dialog_with_count = GetCharacterDialogWithCount(dialog_dest_index);
				dialog_with_count--;
				if(dialog_with_count >= 0)
				{
					SetCharacterDialogWithCount(dialog_dest_index, dialog_with_count);
				}else
				{
					SetCharacterDialogWithCount(dialog_dest_index, 0);
				}				
				UNLOCK_CHARACTER(0);
				if(dialog_with_count == 0)
				{
					LOCK_CHARACTER(0);
					SetCharacterOnPauseState(dialog_dest_index, FALSE);
					UNLOCK_CHARACTER(0);
					ServerDoSendNotifyNpcNoPauseToAll(dialog_dest_index);				
				}										
			}

			LOCK_CHARACTER(0);
			ClearOneCharacter(i);
			BadConnect[i] = FALSE;
			UNLOCK_CHARACTER(0);
		}
	}
}
// -----------------------------------------------------------------------------
void	ServerDoRequestSetHandQuickSkill(TPOS_CN *cn, TPOS_PACKET *packet) 
{
	TPOS_EVENT_SETHANDQUICKSKILL	EventSetHandQuickSkill;
	static TPOS_PACKET			send_packet;
    int		index;
	UHINT	hp;
    DWORD	dLeftRight;
    SLONG	magic_no;
    SLONG	set_successful;
	SLONG	quick_index;
    
	memcpy(&EventSetHandQuickSkill, packet->data.cBuf, sizeof(TPOS_EVENT_SETHANDQUICKSKILL));
    dLeftRight = EventSetHandQuickSkill.Hand;
    magic_no = EventSetHandQuickSkill.SkillNo;
	quick_index = EventSetHandQuickSkill.QuickIndex;

    set_successful = false;
    LOCK_CHARACTER(0);
	index = FindCharacterByMainName(cn->User.cId);
	if(index >= 0)
	{
		hp = GetCharacterHp(index);
		if(hp > 0)
		{
			if(TTN_OK == SetupCharacterHandQuickSkill(index, quick_index, dLeftRight, magic_no))
			{
				set_successful = true;
			}
		}
	}
    UNLOCK_CHARACTER(0);

    if(set_successful)
    {
		send_packet.Header.dwType = NOTIFY_SET_HAND_QUICK_SKILL;
		send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_SETHANDQUICKSKILL);
		EventSetHandQuickSkill.Hand = dLeftRight;
		EventSetHandQuickSkill.SkillNo = magic_no;
		EventSetHandQuickSkill.QuickIndex = quick_index;
		memcpy(send_packet.data.cBuf, &EventSetHandQuickSkill, sizeof(TPOS_EVENT_SETHANDQUICKSKILL));
		
		server_send_packet_to_one(cn, &send_packet);
		
#ifdef  DEBUG_MSG
		char  name[32];
		LOCK_CHARACTER(index);
		strcpy(name, GetCharacterMainName(index));
		SaveWorkToLog(name, inet_ntoa(cn->Addr.sin_addr), "REQUEST_SET_HAND_QUICK_SKILL");
		UNLOCK_CHARACTER(index);
#endif//DEBUG_MSG
    }    
}
// -----------------------------------------------------------------------------
void	ServerDoRequestUseHandQuickSkill(TPOS_CN *cn, TPOS_PACKET *packet)
{
	TPOS_EVENT_USEHANDQUICKSKILL	request;
	TPOS_EVENT_CHANGEMOUSESKILL		notify;
	static TPOS_PACKET			send_packet;
    SLONG	index, hp, quick_index;
	SLONG	skill_no, hand;
	SLONG	set_result;

	memcpy(&request, packet->data.cBuf, sizeof(request));
	quick_index = request.QuickIndex;

	set_result = false;
    LOCK_CHARACTER(0);
	index = FindCharacterByMainName(cn->User.cId);
	if(index >= 0)
	{
		hp = GetCharacterHp(index);
		if(hp > 0)
		{
			GetCharacterFnSkill(index, quick_index, &skill_no, &hand);
			if(skill_no >= 0)
			{
				switch(hand)
				{
				case LEFT:
					SetCharacterLeftSkill(index, (SHINT)skill_no);
					set_result = true;
					break;
				case RIGHT:
					SetCharacterRightSkill(index, (SHINT)skill_no);
					set_result = true;
					break;
				}
			}
		}
	}
	UNLOCK_CHARACTER(0);

	if(set_result)
	{
		send_packet.Header.dwType = GET_CHANGE_MOUSE_SKILL;
		send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(notify);
		notify.dwLeftRight = hand;
		notify.dwSkill = skill_no;
		memcpy(send_packet.data.cBuf, &notify, sizeof(notify));
		server_send_packet_to_one(cn, &send_packet);
	}
}
// -----------------------------------------------------------------------------
void	ExchangeZoneCharacterDataToMyCharacterData(DWORD npc_no, TPOS_EVENT_MYCHARACTER *eventmycharacter)
{	
	int	i;

	//Name
	strcpy(eventmycharacter->ID, GetCharacterAccount(npc_no));
	strcpy(eventmycharacter->MainName, GetCharacterMainName(npc_no));
	strcpy(eventmycharacter->NickName, GetCharacterNickName(npc_no));
	eventmycharacter->QQID = GetCharacterQQID(npc_no);
	eventmycharacter->Index = (SHINT)GetCharacterIndex(npc_no);
	//Style	
	eventmycharacter->Color = (char)GetCharacterColor(npc_no);
	eventmycharacter->Eyes = (char)GetCharacterEyes(npc_no);
	eventmycharacter->Mouth = (char)GetCharacterMouth(npc_no);
	eventmycharacter->MainNameColor = (char)GetCharacterMainNameColor(npc_no);
	eventmycharacter->NickNameColor = (char)GetCharacterNickNameColor(npc_no);
	eventmycharacter->MessageColor = (char)GetCharacterMessageColor(npc_no);
	eventmycharacter->TalkBackColor = (char)GetCharacterTalkBackColor(npc_no);		
	eventmycharacter->Logo = GetCharacterLogo(npc_no);
	eventmycharacter->FileIndex = GetCharacterFileIndex(npc_no);
	//Position
	strcpy(eventmycharacter->ZoneName, GetCharacterZoneName(npc_no));
	GetCharacterPosition(npc_no, &eventmycharacter->X, &eventmycharacter->Y, &eventmycharacter->Z);
	eventmycharacter->Dir = (char)GetCharacterDir(npc_no);
	eventmycharacter->StopRadius = GetCharacterStopRadius(npc_no);
	//Speed
	eventmycharacter->Mspeed = GetCharacterMoveSpeed(npc_no);
	eventmycharacter->FSpeedX = GetCharacterShipSpeedX(npc_no);
	eventmycharacter->FSpeedY = GetCharacterShipSpeedY(npc_no);
	eventmycharacter->SailSize = (UHINT)GetCharacterShipSailSize(npc_no);
	eventmycharacter->Turn = (UHINT)GetCharacterShipTurn(npc_no);
	eventmycharacter->Weight = (UHINT)GetCharacterShipWeight(npc_no);
	eventmycharacter->DegreeDir = GetCharacterShipDegreeDir(npc_no);
	//State
	eventmycharacter->BitState = GetCharacterBitState(npc_no);
	//屬性 
	eventmycharacter->FinalStr = GetCharacterFinalStr(npc_no);
	eventmycharacter->FinalIns = GetCharacterFinalIns(npc_no);
	eventmycharacter->FinalWit = GetCharacterFinalWit(npc_no);
	eventmycharacter->FinalLucky = GetCharacterFinalLucky(npc_no);	
	eventmycharacter->FinalAttack = GetCharacterFinalAtt(npc_no);
	eventmycharacter->FinalDefence = GetCharacterFinalDefence(npc_no);
	eventmycharacter->SightRange = GetCharacterSightRange(npc_no);
	//Property
	eventmycharacter->PropertyPoint = GetCharacterPropertyPoint(npc_no);
	//Exp Lev
	eventmycharacter->Exp = GetCharacterExp(npc_no);
	eventmycharacter->Level = GetCharacterLevel(npc_no);
	//Hp Mp
	eventmycharacter->Hp = GetCharacterHp(npc_no);
	eventmycharacter->MaxHp = GetCharacterMaxHp(npc_no);
	eventmycharacter->HpRes = GetCharacterHpRes(npc_no);
	eventmycharacter->Mp = GetCharacterMp(npc_no);
	eventmycharacter->MaxMp = GetCharacterMaxMp(npc_no);
	eventmycharacter->MpRes = GetCharacterMpRes(npc_no);
	//Skill
	for(i = 0;i < MAX_CHARACTER_SKILLS;i++)
	{
		eventmycharacter->SkillNo[i] = (SHINT)GetCharacterSkillNo(npc_no, i);
		eventmycharacter->SkillLevel[i] = (UHINT)GetCharacterSkillLevel(npc_no, i);
	}	
	//Equip
	GetCharacterEquipHead(npc_no, &eventmycharacter->EquHead);
	GetCharacterEquipNeck(npc_no, &eventmycharacter->EquNeck);
	GetCharacterEquipBody(npc_no, &eventmycharacter->EquBody);
	GetCharacterEquipWaist(npc_no, &eventmycharacter->EquWaist);
	GetCharacterEquipGlove(npc_no, &eventmycharacter->EquGlove);
	GetCharacterEquipWeapon(npc_no, &eventmycharacter->EquWeapon);
	GetCharacterEquipWrist(npc_no, &eventmycharacter->EquWrist);
	GetCharacterEquipFeet(npc_no, &eventmycharacter->EquFeet);
	GetCharacterEquipOtherA(npc_no, &eventmycharacter->EquOtherA);
	GetCharacterEquipOtherB(npc_no, &eventmycharacter->EquOtherB);
	GetCharacterEquipOtherC(npc_no, &eventmycharacter->EquOtherC);
	//Body Item
	for(i = 0;i < MAX_CHARACTER_BAG_ITEMS;i++)
	{
		GetCharacterBagItem(npc_no, i, &eventmycharacter->BagItem[i]);
	}
	for(i = 0;i < MAX_CHARACTER_SASH_ITEMS;i++)
	{
		GetCharacterSashItem(npc_no, i, &eventmycharacter->SashItem[i]);
	}
	for(i = 0;i < MAX_CHARACTER_TRANS_ITEMS;i++)
	{
		GetCharacterTransItem(npc_no, i, &eventmycharacter->TransItem[i]);
	}
	GetCharacterOnMouseItem(npc_no, &eventmycharacter->OnMouseItem);	
	GetCharacterTreasureItem(npc_no, &eventmycharacter->TreasureItem);
	eventmycharacter->Money = GetCharacterBodyMoney(npc_no);
	//Society
	eventmycharacter->Sex = (char)GetCharacterSex(npc_no);
	eventmycharacter->Country = (char)GetCharacterCountry(npc_no);
	strcpy(eventmycharacter->Guild, GetCharacterGuildName(npc_no));
	strcpy(eventmycharacter->Spouse, GetCharacterSpouseName(npc_no));
	eventmycharacter->Career = (char)GetCharacterCareer(npc_no);
	eventmycharacter->CareerLevel = (UCHAR) GetCharacterCareerLevel(npc_no);
	eventmycharacter->Office = GetCharacterOffice(npc_no);
	strcpy(eventmycharacter->Nobility, GetCharacterNobilityName(npc_no));
	eventmycharacter->GoodEvil = GetCharacterGoodEvil(npc_no);
	eventmycharacter->Prestige = GetCharacterPrestige(npc_no);
	eventmycharacter->PkCount = GetCharacterPkCount(npc_no);
	eventmycharacter->PkedCount = GetCharacterPkedCount(npc_no);
	//Mouse skill and Hot Key
	eventmycharacter->LandLeftSkill = GetCharacterLandLeftSkill(npc_no);
	eventmycharacter->LandRightSkill = GetCharacterLandRightSkill(npc_no);
	for(i = 0;i < MAX_CHARACTER_FN_SKILLS;i++)
	{
		eventmycharacter->LandFnSkillNo[i] = GetCharacterLandFnSkillNo(npc_no, i);
		eventmycharacter->LandFnSkillHand[i] = (char)GetCharacterLandFnSkillHand(npc_no, i);
	}	
	eventmycharacter->SeaLeftSkill = GetCharacterSeaLeftSkill(npc_no);
	eventmycharacter->SeaRightSkill = GetCharacterSeaRightSkill(npc_no);
	for(i = 0;i < MAX_CHARACTER_FN_SKILLS;i++)
	{
		eventmycharacter->SeaFnSkillNo[i] = GetCharacterSeaFnSkillNo(npc_no, i);
		eventmycharacter->SeaFnSkillHand[i] = (char)GetCharacterSeaFnSkillHand(npc_no, i);
	}	
	//Doing
	eventmycharacter->DoingKind = GetCharacterDoingKind(npc_no);	
	for(i = 0;i < MAX_CHARACTER_PARTS;i++)
	{
		eventmycharacter->PartRGB[i] = GetCharacterPartRGB(npc_no, i);
	}
}
// -----------------------------------------------------------------------------
void	ServerDoRequestHitBagItem(TPOS_CN *cn, TPOS_PACKET *packet)
{
	SLONG							npc_no;
	TPOS_EVENT_REQUESTHITBAGITEM	EventRequestHitBagItem;
	TPOS_EVENT_NOTIFYSETONMOUSEITEM	EventNotifySetOnMouseItem;
	TPOS_EVENT_NOTIFYSETBAGITEM		EventNotifySetBagItem;	
	TPOS_ITEM						OnMouseItem;
	TPOS_ITEM						DestItem;
	TPOS_PACKET						send_packet;
	int								LR;	
	
	memcpy(&EventRequestHitBagItem, packet->data.cBuf, sizeof(TPOS_EVENT_REQUESTHITBAGITEM));

	LR = EventRequestHitBagItem.LR;	
	LOCK_CHARACTER(0);
	npc_no = FindCharacterByMainName(cn->User.cId);
	GetCharacterOnMouseItem(npc_no, &OnMouseItem);
	GetCharacterBagItem(npc_no, EventRequestHitBagItem.BagIndex, &DestItem);
	UNLOCK_CHARACTER(0);
	
	if(LR == LEFT)
	{		
		if(ServerDoCheckIsTreasureMapItem(&OnMouseItem) == TRUE)
		{			
			if(ServerDoCheckIsTreasureMapItem(&DestItem) == TRUE)
			{
				TPOS_ITEM	FinalItem;
				memset(&FinalItem, 0x0, sizeof(TPOS_ITEM));
				//組合地圖
				if(ServerDoComposeMap(&OnMouseItem, &DestItem, &FinalItem) == TRUE)
				{
					SetItemNone(&OnMouseItem);
					LOCK_CHARACTER(0);									
					SetCharacterBagItem(npc_no, EventRequestHitBagItem.BagIndex, &FinalItem);			
					SetCharacterOnMouseItem(npc_no, &OnMouseItem);
					UNLOCK_CHARACTER(0);
					// 送出滑鼠物品的信息
					send_packet.Header.dwType = NOTIFY_SET_ONMOUSE_ITEM;
					send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYSETONMOUSEITEM);
					EventNotifySetOnMouseItem.Item = OnMouseItem;
					memcpy(send_packet.data.cBuf, &EventNotifySetOnMouseItem, sizeof(TPOS_EVENT_NOTIFYSETONMOUSEITEM));
					server_send_packet_to_one(cn, &send_packet);
					// 送出包包物品的信息
					send_packet.Header.dwType = NOTIFY_SET_BAG_ITEM;
					send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYSETBAGITEM);
					EventNotifySetBagItem.BagIndex = EventRequestHitBagItem.BagIndex;
					EventNotifySetBagItem.Item = FinalItem;
					memcpy(send_packet.data.cBuf, &EventNotifySetBagItem, sizeof(TPOS_EVENT_NOTIFYSETBAGITEM));
					server_send_packet_to_one(cn, &send_packet);

					return;
				}				
			}
		}		
		LOCK_CHARACTER(0);									
		SetCharacterBagItem(npc_no, EventRequestHitBagItem.BagIndex, &OnMouseItem);			
		SetCharacterOnMouseItem(npc_no, &DestItem);
		UNLOCK_CHARACTER(0);
		// 送出滑鼠物品的信息
		send_packet.Header.dwType = NOTIFY_SET_ONMOUSE_ITEM;
		send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYSETONMOUSEITEM);
		EventNotifySetOnMouseItem.Item = DestItem;
		memcpy(send_packet.data.cBuf, &EventNotifySetOnMouseItem, sizeof(TPOS_EVENT_NOTIFYSETONMOUSEITEM));
		server_send_packet_to_one(cn, &send_packet);
		// 送出包包物品的信息
		send_packet.Header.dwType = NOTIFY_SET_BAG_ITEM;
		send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYSETBAGITEM);
		EventNotifySetBagItem.BagIndex = EventRequestHitBagItem.BagIndex;
		EventNotifySetBagItem.Item = OnMouseItem;
		memcpy(send_packet.data.cBuf, &EventNotifySetBagItem, sizeof(TPOS_EVENT_NOTIFYSETBAGITEM));
		server_send_packet_to_one(cn, &send_packet);	
	}
	if(LR== RIGHT)
	{		
		SLONG				item_type;

		if(IsItemNone(&DestItem) == FALSE)
		{
			item_type = GetItemType(&DestItem);
			
			switch(item_type)
			{
			case ITEM_TYPE_DRUG:
				ServerDoUseDrugItem(npc_no, &DestItem, EventRequestHitBagItem.BagIndex);
				break;
			case ITEM_TYPE_TREASURE_MAP:
				ServerDoUseTreasureMapItem(npc_no, &DestItem, EventRequestHitBagItem.BagIndex);
				break;
			}
		}		
	}
}
// -----------------------------------------------------------------------------
void	ServerDoRequestHitHeadItem(TPOS_CN *cn, TPOS_PACKET *packet)
{
	SLONG							npc_no;
	TPOS_PACKET						send_packet;
	TPOS_ITEM						OnMouseItem;
	TPOS_ITEM						DestItem;	
	TPOS_EVENT_NOTIFYSETONMOUSEITEM	EventNotifySetOnMouseItem;
	TPOS_EVENT_NOTIFYSETHEADITEM	EventNotifySetHeadItem;
	TPOS_EVENT_REQUESTHITHEADITEM	EventRequestHitHeadItem;
	EQUIP_UPDATE_RESULT				Result;
	TPOS_EVENT_NOTIFYAFTERCHANGEEQUIP	EventNotifyAfterChangeEquip;	
	char							career, sex;
	SLONG							Ret;	

	memcpy(&EventRequestHitHeadItem, packet->data.cBuf, sizeof(TPOS_EVENT_REQUESTHITHEADITEM));

	Ret = FALSE;	
	LOCK_CHARACTER(0);
	npc_no = FindCharacterByMainName(cn->User.cId);
	GetCharacterOnMouseItem(npc_no, &OnMouseItem);
	GetCharacterEquipHead(npc_no, &DestItem);
	career = (char)GetCharacterCareer(npc_no);
	sex = (char)GetCharacterSex(npc_no);
	UNLOCK_CHARACTER(0);
	
	if(IsItemNone(&OnMouseItem) != TRUE)
	{
		Ret = IsItemForMyHead(&OnMouseItem, (SLONG)career, (SLONG)sex);			
	}else
	{
		Ret = TRUE;
	}
	if(Ret == TRUE)
	{
		LOCK_CHARACTER(0);									
		SetCharacterEquipHead(npc_no, &OnMouseItem);			
		SetCharacterOnMouseItem(npc_no, &DestItem);
		ComputeCharacterDataAfterChangeEquipHead(npc_no,  &Result);
		memcpy(&EventNotifyAfterChangeEquip, &Result, sizeof(TPOS_EVENT_NOTIFYAFTERCHANGEEQUIP));
		UNLOCK_CHARACTER(0);

		// 送出滑鼠物品的信息
		send_packet.Header.dwType = NOTIFY_SET_ONMOUSE_ITEM;
		send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYSETONMOUSEITEM);
		EventNotifySetOnMouseItem.Item = DestItem;
		memcpy(send_packet.data.cBuf, &EventNotifySetOnMouseItem, sizeof(TPOS_EVENT_NOTIFYSETONMOUSEITEM));
		server_send_packet_to_one(cn, &send_packet);
		// 送出頭部物品的信息
		send_packet.Header.dwType = NOTIFY_SET_HEAD_ITEM;
		send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYSETHEADITEM);	
		EventNotifySetHeadItem.Item = OnMouseItem;
		memcpy(send_packet.data.cBuf, &EventNotifySetHeadItem, sizeof(TPOS_EVENT_NOTIFYSETHEADITEM));
		server_send_packet_to_one(cn, &send_packet);
		// 送出改變裝備後的數值改變
		send_packet.Header.dwType = NOTIFY_AFTER_CHANGE_EQUIP;
		send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYAFTERCHANGEEQUIP);			
		memcpy(send_packet.data.cBuf, &EventNotifyAfterChangeEquip, sizeof(TPOS_EVENT_NOTIFYAFTERCHANGEEQUIP));
		server_send_packet_to_one(cn, &send_packet);				
	}
}
// -----------------------------------------------------------------------------
void	ServerDoRequestHitNeckItem(TPOS_CN *cn, TPOS_PACKET *packet)
{
	SLONG							npc_no;
	TPOS_PACKET						send_packet;
	TPOS_ITEM						OnMouseItem;
	TPOS_ITEM						DestItem;	
	TPOS_EVENT_NOTIFYSETONMOUSEITEM	EventNotifySetOnMouseItem;
	TPOS_EVENT_NOTIFYSETNECKITEM	EventNotifySetNeckItem;
	TPOS_EVENT_REQUESTHITNECKITEM	EventRequestHitNecktem;
	EQUIP_UPDATE_RESULT				Result;
	TPOS_EVENT_NOTIFYAFTERCHANGEEQUIP	EventNotifyAfterChangeEquip;	
	char							career, sex;
	SLONG							Ret;

	memcpy(&EventRequestHitNecktem, packet->data.cBuf, sizeof(TPOS_EVENT_REQUESTHITNECKITEM));

	Ret = FALSE;
	LOCK_CHARACTER(0);
	npc_no = FindCharacterByMainName(cn->User.cId);
	GetCharacterOnMouseItem(npc_no, &OnMouseItem);
	GetCharacterEquipNeck(npc_no, &DestItem);
	career = (char)GetCharacterCareer(npc_no);
	sex = (char)GetCharacterSex(npc_no);
	UNLOCK_CHARACTER(0);
	
	if(IsItemNone(&OnMouseItem) != TRUE)
	{
		Ret = IsItemForMyNeck(&OnMouseItem, (SLONG)career, (SLONG)sex);				
	}else
	{
		Ret = TRUE;
	}
	if(Ret == TRUE)
	{
		LOCK_CHARACTER(0);									
		SetCharacterEquipNeck(npc_no, &OnMouseItem);			
		SetCharacterOnMouseItem(npc_no, &DestItem);
		ComputeCharacterDataAfterChangeEquipNeck(npc_no,  &Result);
		memcpy(&EventNotifyAfterChangeEquip, &Result, sizeof(TPOS_EVENT_NOTIFYAFTERCHANGEEQUIP));				
		UNLOCK_CHARACTER(0);

		// 送出滑鼠物品的信息
		send_packet.Header.dwType = NOTIFY_SET_ONMOUSE_ITEM;
		send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYSETONMOUSEITEM);
		EventNotifySetOnMouseItem.Item = DestItem;
		memcpy(send_packet.data.cBuf, &EventNotifySetOnMouseItem, sizeof(TPOS_EVENT_NOTIFYSETONMOUSEITEM));
		server_send_packet_to_one(cn, &send_packet);
		// 送出頸部物品的信息
		send_packet.Header.dwType = NOTIFY_SET_NECK_ITEM;
		send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYSETNECKITEM);	
		EventNotifySetNeckItem.Item = OnMouseItem;
		memcpy(send_packet.data.cBuf, &EventNotifySetNeckItem, sizeof(TPOS_EVENT_NOTIFYSETNECKITEM));
		server_send_packet_to_one(cn, &send_packet);
		// 送出改變裝備後的數值改變
		send_packet.Header.dwType = NOTIFY_AFTER_CHANGE_EQUIP;
		send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYAFTERCHANGEEQUIP);			
		memcpy(send_packet.data.cBuf, &EventNotifyAfterChangeEquip, sizeof(TPOS_EVENT_NOTIFYAFTERCHANGEEQUIP));
		server_send_packet_to_one(cn, &send_packet);		
	}
}
// -----------------------------------------------------------------------------
void	ServerDoRequestHitBodyItem(TPOS_CN *cn, TPOS_PACKET *packet)
{
	SLONG							npc_no;
	TPOS_PACKET						send_packet;
	TPOS_ITEM						OnMouseItem;
	TPOS_ITEM						DestItem;	
	TPOS_EVENT_NOTIFYSETONMOUSEITEM	EventNotifySetOnMouseItem;
	TPOS_EVENT_NOTIFYSETBODYITEM	EventNotifySetBodyItem;
	TPOS_EVENT_REQUESTHITBODYITEM	EventRequestHitBodyItem;
	EQUIP_UPDATE_RESULT				Result;
	TPOS_EVENT_NOTIFYAFTERCHANGEEQUIP	EventNotifyAfterChangeEquip;
	char							career, sex;
	SLONG							Ret;

	memcpy(&EventRequestHitBodyItem, packet->data.cBuf, sizeof(TPOS_EVENT_REQUESTHITBODYITEM));

	Ret = FALSE;
	LOCK_CHARACTER(0);
	npc_no = FindCharacterByMainName(cn->User.cId);
	GetCharacterOnMouseItem(npc_no, &OnMouseItem);
	GetCharacterEquipBody(npc_no, &DestItem);
	career = (char)GetCharacterCareer(npc_no);
	sex = (char)GetCharacterSex(npc_no);
	UNLOCK_CHARACTER(0);	

	if(IsItemNone(&OnMouseItem) != TRUE)
	{
		Ret = IsItemForMyBody(&OnMouseItem, (SLONG)career, (SLONG)sex);		
	}else
	{
		Ret = TRUE;
	}
	if(Ret == TRUE)
	{
		LOCK_CHARACTER(0);									
		SetCharacterEquipBody(npc_no, &OnMouseItem);			
		SetCharacterOnMouseItem(npc_no, &DestItem);
		ComputeCharacterDataAfterChangeEquipBody(npc_no,  &Result);
		memcpy(&EventNotifyAfterChangeEquip, &Result, sizeof(TPOS_EVENT_NOTIFYAFTERCHANGEEQUIP));				
		UNLOCK_CHARACTER(0);

		// 送出滑鼠物品的信息
		send_packet.Header.dwType = NOTIFY_SET_ONMOUSE_ITEM;
		send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYSETONMOUSEITEM);
		EventNotifySetOnMouseItem.Item = DestItem;
		memcpy(send_packet.data.cBuf, &EventNotifySetOnMouseItem, sizeof(TPOS_EVENT_NOTIFYSETONMOUSEITEM));
		server_send_packet_to_one(cn, &send_packet);
		// 送出身體物品的信息
		send_packet.Header.dwType = NOTIFY_SET_BODY_ITEM;
		send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYSETBODYITEM);	
		EventNotifySetBodyItem.Item = OnMouseItem;
		memcpy(send_packet.data.cBuf, &EventNotifySetBodyItem, sizeof(TPOS_EVENT_NOTIFYSETBODYITEM));
		server_send_packet_to_one(cn, &send_packet);
		// 送出改變裝備後的數值改變
		send_packet.Header.dwType = NOTIFY_AFTER_CHANGE_EQUIP;
		send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYAFTERCHANGEEQUIP);			
		memcpy(send_packet.data.cBuf, &EventNotifyAfterChangeEquip, sizeof(TPOS_EVENT_NOTIFYAFTERCHANGEEQUIP));
		server_send_packet_to_one(cn, &send_packet);		
	}
}
// -----------------------------------------------------------------------------
void	ServerDoRequestHitWaistItem(TPOS_CN *cn, TPOS_PACKET *packet)
{
	SLONG							npc_no;
	TPOS_PACKET						send_packet;
	TPOS_ITEM						OnMouseItem;
	TPOS_ITEM						DestItem;	
	TPOS_EVENT_NOTIFYSETONMOUSEITEM	EventNotifySetOnMouseItem;
	TPOS_EVENT_NOTIFYSETWAISTITEM	EventNotifySetWaistItem;
	TPOS_EVENT_REQUESTHITWAISTITEM	EventRequestHitWaistItem;
	EQUIP_UPDATE_RESULT				Result;
	TPOS_EVENT_NOTIFYAFTERCHANGEEQUIP	EventNotifyAfterChangeEquip;	
	char							career, sex;
	SLONG							Ret;

	memcpy(&EventRequestHitWaistItem, packet->data.cBuf, sizeof(TPOS_EVENT_REQUESTHITWAISTITEM));

	Ret = FALSE;
	LOCK_CHARACTER(0);
	npc_no = FindCharacterByMainName(cn->User.cId);
	GetCharacterOnMouseItem(npc_no, &OnMouseItem);
	GetCharacterEquipWaist(npc_no, &DestItem);
	career = (char)GetCharacterCareer(npc_no);
	sex = (char)GetCharacterSex(npc_no);
	UNLOCK_CHARACTER(0);

	if(IsItemNone(&OnMouseItem) != TRUE)
	{
		Ret = IsItemForMyWaist(&OnMouseItem, (SLONG)career, (SLONG)sex);		
	}else
	{
		Ret = TRUE;
	}
	if(Ret == TRUE)
	{
		LOCK_CHARACTER(0);									
		SetCharacterEquipWaist(npc_no, &OnMouseItem);			
		SetCharacterOnMouseItem(npc_no, &DestItem);
		ComputeCharacterDataAfterChangeEquipWaist(npc_no,  &Result);
		memcpy(&EventNotifyAfterChangeEquip, &Result, sizeof(TPOS_EVENT_NOTIFYAFTERCHANGEEQUIP));
		UNLOCK_CHARACTER(0);
		// 送出滑鼠物品的信息
		send_packet.Header.dwType = NOTIFY_SET_ONMOUSE_ITEM;
		send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYSETONMOUSEITEM);
		EventNotifySetOnMouseItem.Item = DestItem;
		memcpy(send_packet.data.cBuf, &EventNotifySetOnMouseItem, sizeof(TPOS_EVENT_NOTIFYSETONMOUSEITEM));
		server_send_packet_to_one(cn, &send_packet);
		// 送出腰部物品的信息
		send_packet.Header.dwType = NOTIFY_SET_WAIST_ITEM;
		send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYSETWAISTITEM);	
		EventNotifySetWaistItem.Item = OnMouseItem;
		memcpy(send_packet.data.cBuf, &EventNotifySetWaistItem, sizeof(TPOS_EVENT_NOTIFYSETWAISTITEM));
		server_send_packet_to_one(cn, &send_packet);
		// 送出改變裝備後的數值改變
		send_packet.Header.dwType = NOTIFY_AFTER_CHANGE_EQUIP;
		send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYAFTERCHANGEEQUIP);			
		memcpy(send_packet.data.cBuf, &EventNotifyAfterChangeEquip, sizeof(TPOS_EVENT_NOTIFYAFTERCHANGEEQUIP));
		server_send_packet_to_one(cn, &send_packet);		
	}
}
// -----------------------------------------------------------------------------
void	ServerDoRequestHitGloveItem(TPOS_CN *cn, TPOS_PACKET *packet)
{
	SLONG							npc_no;
	TPOS_PACKET						send_packet;
	TPOS_ITEM						OnMouseItem;
	TPOS_ITEM						DestItem;	
	TPOS_EVENT_NOTIFYSETONMOUSEITEM	EventNotifySetOnMouseItem;
	TPOS_EVENT_NOTIFYSETGLOVEITEM	EventNotifySetGloveItem;
	TPOS_EVENT_REQUESTHITGLOVEITEM	EventRequestHitGloveItem;
	EQUIP_UPDATE_RESULT				Result;
	TPOS_EVENT_NOTIFYAFTERCHANGEEQUIP	EventNotifyAfterChangeEquip;
	char							career, sex;
	SLONG							Ret;

	memcpy(&EventRequestHitGloveItem, packet->data.cBuf, sizeof(TPOS_EVENT_REQUESTHITGLOVEITEM));

	Ret = FALSE;
	LOCK_CHARACTER(0);
	npc_no = FindCharacterByMainName(cn->User.cId);
	GetCharacterOnMouseItem(npc_no, &OnMouseItem);
	GetCharacterEquipGlove(npc_no, &DestItem);
	career = (char)GetCharacterCareer(npc_no);
	sex = (char)GetCharacterSex(npc_no);
	UNLOCK_CHARACTER(0);
	
	if(IsItemNone(&OnMouseItem) != TRUE)
	{
		Ret = IsItemForMyGlove(&OnMouseItem, (SLONG)career, (SLONG)sex);		
	}else
	{
		Ret = TRUE;
	}
	if(Ret == TRUE)
	{
		LOCK_CHARACTER(0);									
		SetCharacterEquipGlove(npc_no, &OnMouseItem);			
		SetCharacterOnMouseItem(npc_no, &DestItem);
		ComputeCharacterDataAfterChangeEquipGlove(npc_no,  &Result);
		memcpy(&EventNotifyAfterChangeEquip, &Result, sizeof(TPOS_EVENT_NOTIFYAFTERCHANGEEQUIP));
		UNLOCK_CHARACTER(0);
		// 送出滑鼠物品的信息
		send_packet.Header.dwType = NOTIFY_SET_ONMOUSE_ITEM;
		send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYSETONMOUSEITEM);
		EventNotifySetOnMouseItem.Item = DestItem;
		memcpy(send_packet.data.cBuf, &EventNotifySetOnMouseItem, sizeof(TPOS_EVENT_NOTIFYSETONMOUSEITEM));
		server_send_packet_to_one(cn, &send_packet);
		// 送出手套物品的信息
		send_packet.Header.dwType = NOTIFY_SET_GLOVE_ITEM;
		send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYSETGLOVEITEM);	
		EventNotifySetGloveItem.Item = OnMouseItem;
		memcpy(send_packet.data.cBuf, &EventNotifySetGloveItem, sizeof(TPOS_EVENT_NOTIFYSETGLOVEITEM));
		server_send_packet_to_one(cn, &send_packet);
		// 送出改變裝備後的數值改變
		send_packet.Header.dwType = NOTIFY_AFTER_CHANGE_EQUIP;
		send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYAFTERCHANGEEQUIP);			
		memcpy(send_packet.data.cBuf, &EventNotifyAfterChangeEquip, sizeof(TPOS_EVENT_NOTIFYAFTERCHANGEEQUIP));
		server_send_packet_to_one(cn, &send_packet);		
	}
}
// -----------------------------------------------------------------------------
void	ServerDoRequestHitWeaponItem(TPOS_CN *cn, TPOS_PACKET *packet)
{
	SLONG							npc_no;
	TPOS_PACKET						send_packet;
	TPOS_ITEM						OnMouseItem;
	TPOS_ITEM						DestItem;	
	TPOS_EVENT_NOTIFYSETONMOUSEITEM	EventNotifySetOnMouseItem;
	TPOS_EVENT_NOTIFYSETWEAPONITEM	EventNotifySetWeaponItem;
	TPOS_EVENT_REQUESTHITWEAPONITEM	EventRequestHitWeaponItem;
	EQUIP_UPDATE_RESULT				Result;
	TPOS_EVENT_NOTIFYAFTERCHANGEEQUIP	EventNotifyAfterChangeEquip;	
	char							career, sex;
	SLONG							Ret;

	memcpy(&EventRequestHitWeaponItem, packet->data.cBuf, sizeof(TPOS_EVENT_REQUESTHITWEAPONITEM));

	Ret = FALSE;
	LOCK_CHARACTER(0);
	npc_no = FindCharacterByMainName(cn->User.cId);
	GetCharacterOnMouseItem(npc_no, &OnMouseItem);
	GetCharacterEquipWeapon(npc_no, &DestItem);
	career = (char)GetCharacterCareer(npc_no);
	sex = (char)GetCharacterSex(npc_no);
	UNLOCK_CHARACTER(0);

	if(IsItemNone(&OnMouseItem) != TRUE)
	{
		Ret = IsItemForMyWeapon(&OnMouseItem, (SLONG)career, (SLONG)sex);		
	}else
	{
		Ret = TRUE;
	}
	if(Ret == TRUE)
	{
		LOCK_CHARACTER(0);									
		SetCharacterEquipWeapon(npc_no, &OnMouseItem);			
		SetCharacterOnMouseItem(npc_no, &DestItem);
		ComputeCharacterDataAfterChangeEquipWeapon(npc_no,  &Result);
		memcpy(&EventNotifyAfterChangeEquip, &Result, sizeof(TPOS_EVENT_NOTIFYAFTERCHANGEEQUIP));
		UNLOCK_CHARACTER(0);
		// 送出滑鼠物品的信息
		send_packet.Header.dwType = NOTIFY_SET_ONMOUSE_ITEM;
		send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYSETONMOUSEITEM);
		EventNotifySetOnMouseItem.Item = DestItem;
		memcpy(send_packet.data.cBuf, &EventNotifySetOnMouseItem, sizeof(TPOS_EVENT_NOTIFYSETONMOUSEITEM));
		server_send_packet_to_one(cn, &send_packet);
		// 送出武器物品的信息
		send_packet.Header.dwType = NOTIFY_SET_WEAPON_ITEM;
		send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYSETWEAPONITEM);	
		EventNotifySetWeaponItem.Item = OnMouseItem;
		memcpy(send_packet.data.cBuf, &EventNotifySetWeaponItem, sizeof(TPOS_EVENT_NOTIFYSETWEAPONITEM));
		server_send_packet_to_one(cn, &send_packet);
		// 送出改變裝備後的數值改變
		send_packet.Header.dwType = NOTIFY_AFTER_CHANGE_EQUIP;
		send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYAFTERCHANGEEQUIP);			
		memcpy(send_packet.data.cBuf, &EventNotifyAfterChangeEquip, sizeof(TPOS_EVENT_NOTIFYAFTERCHANGEEQUIP));
		server_send_packet_to_one(cn, &send_packet);		
	}
}
// -----------------------------------------------------------------------------
void	ServerDoRequestHitWristItem(TPOS_CN *cn, TPOS_PACKET *packet)
{
	SLONG							npc_no;
	TPOS_PACKET						send_packet;
	TPOS_ITEM						OnMouseItem;
	TPOS_ITEM						DestItem;	
	TPOS_EVENT_NOTIFYSETONMOUSEITEM	EventNotifySetOnMouseItem;
	TPOS_EVENT_NOTIFYSETWRISTITEM	EventNotifySetWristItem;
	TPOS_EVENT_REQUESTHITWRISTITEM	EventRequestHitWristItem;
	EQUIP_UPDATE_RESULT				Result;
	TPOS_EVENT_NOTIFYAFTERCHANGEEQUIP	EventNotifyAfterChangeEquip;	
	char							career, sex;
	SLONG							Ret;

	memcpy(&EventRequestHitWristItem, packet->data.cBuf, sizeof(TPOS_EVENT_REQUESTHITWRISTITEM));

	Ret = FALSE;
	LOCK_CHARACTER(0);
	npc_no = FindCharacterByMainName(cn->User.cId);
	GetCharacterOnMouseItem(npc_no, &OnMouseItem);
	GetCharacterEquipWrist(npc_no, &DestItem);
	career = (char)GetCharacterCareer(npc_no);
	sex = (char)GetCharacterSex(npc_no);
	UNLOCK_CHARACTER(0);

	if(IsItemNone(&OnMouseItem) != TRUE)
	{
		Ret = IsItemForMyWrist(&OnMouseItem, (SLONG)career, (SLONG)sex);		
	}else
	{
		Ret = TRUE;
	}
	if(Ret == TRUE)
	{
		LOCK_CHARACTER(0);									
		SetCharacterEquipWrist(npc_no, &OnMouseItem);			
		SetCharacterOnMouseItem(npc_no, &DestItem);
		ComputeCharacterDataAfterChangeEquipWrist(npc_no,  &Result);
		memcpy(&EventNotifyAfterChangeEquip, &Result, sizeof(TPOS_EVENT_NOTIFYAFTERCHANGEEQUIP));
		UNLOCK_CHARACTER(0);
		// 送出滑鼠物品的信息
		send_packet.Header.dwType = NOTIFY_SET_ONMOUSE_ITEM;
		send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYSETONMOUSEITEM);
		EventNotifySetOnMouseItem.Item = DestItem;
		memcpy(send_packet.data.cBuf, &EventNotifySetOnMouseItem, sizeof(TPOS_EVENT_NOTIFYSETONMOUSEITEM));
		server_send_packet_to_one(cn, &send_packet);
		// 送出手腕物品的信息
		send_packet.Header.dwType = NOTIFY_SET_WRIST_ITEM;
		send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYSETWRISTITEM);	
		EventNotifySetWristItem.Item = OnMouseItem;
		memcpy(send_packet.data.cBuf, &EventNotifySetWristItem, sizeof(TPOS_EVENT_NOTIFYSETWRISTITEM));
		server_send_packet_to_one(cn, &send_packet);
		// 送出改變裝備後的數值改變
		send_packet.Header.dwType = NOTIFY_AFTER_CHANGE_EQUIP;
		send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYAFTERCHANGEEQUIP);			
		memcpy(send_packet.data.cBuf, &EventNotifyAfterChangeEquip, sizeof(TPOS_EVENT_NOTIFYAFTERCHANGEEQUIP));
		server_send_packet_to_one(cn, &send_packet);		
	}
}
// -----------------------------------------------------------------------------
void	ServerDoRequestHitFeetItem(TPOS_CN *cn, TPOS_PACKET *packet)
{
	SLONG							npc_no;
	TPOS_PACKET						send_packet;
	TPOS_ITEM						OnMouseItem;
	TPOS_ITEM						DestItem;	
	TPOS_EVENT_NOTIFYSETONMOUSEITEM	EventNotifySetOnMouseItem;
	TPOS_EVENT_NOTIFYSETFEETITEM	EventNotifySetFeetItem;
	TPOS_EVENT_REQUESTHITFEETITEM	EventRequestHitFeetItem;
	EQUIP_UPDATE_RESULT				Result;
	TPOS_EVENT_NOTIFYAFTERCHANGEEQUIP	EventNotifyAfterChangeEquip;	
	char							career, sex;
	SLONG							Ret;

	memcpy(&EventRequestHitFeetItem, packet->data.cBuf, sizeof(TPOS_EVENT_REQUESTHITFEETITEM));

	Ret = FALSE;
	LOCK_CHARACTER(0);
	npc_no = FindCharacterByMainName(cn->User.cId);
	GetCharacterOnMouseItem(npc_no, &OnMouseItem);
	GetCharacterEquipFeet(npc_no, &DestItem);
	career = (char)GetCharacterCareer(npc_no);
	sex = (char)GetCharacterSex(npc_no);
	UNLOCK_CHARACTER(0);

	if(IsItemNone(&OnMouseItem) != TRUE)
	{
		Ret = IsItemForMyFeet(&OnMouseItem, (SLONG)career, (SLONG)sex);		
	}else
	{
		Ret = TRUE;
	}
	if(Ret == TRUE)
	{
		LOCK_CHARACTER(0);									
		SetCharacterEquipFeet(npc_no, &OnMouseItem);			
		SetCharacterOnMouseItem(npc_no, &DestItem);
		ComputeCharacterDataAfterChangeEquipFeet(npc_no,  &Result);
		memcpy(&EventNotifyAfterChangeEquip, &Result, sizeof(TPOS_EVENT_NOTIFYAFTERCHANGEEQUIP));
		UNLOCK_CHARACTER(0);
		// 送出滑鼠物品的信息
		send_packet.Header.dwType = NOTIFY_SET_ONMOUSE_ITEM;
		send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYSETONMOUSEITEM);
		EventNotifySetOnMouseItem.Item = DestItem;
		memcpy(send_packet.data.cBuf, &EventNotifySetOnMouseItem, sizeof(TPOS_EVENT_NOTIFYSETONMOUSEITEM));
		server_send_packet_to_one(cn, &send_packet);
		// 送出腳部物品的信息
		send_packet.Header.dwType = NOTIFY_SET_FEET_ITEM;
		send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYSETFEETITEM);	
		EventNotifySetFeetItem.Item = OnMouseItem;
		memcpy(send_packet.data.cBuf, &EventNotifySetFeetItem, sizeof(TPOS_EVENT_NOTIFYSETFEETITEM));
		server_send_packet_to_one(cn, &send_packet);
		// 送出改變裝備後的數值改變
		send_packet.Header.dwType = NOTIFY_AFTER_CHANGE_EQUIP;
		send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYAFTERCHANGEEQUIP);			
		memcpy(send_packet.data.cBuf, &EventNotifyAfterChangeEquip, sizeof(TPOS_EVENT_NOTIFYAFTERCHANGEEQUIP));
		server_send_packet_to_one(cn, &send_packet);		
	}
}
// -----------------------------------------------------------------------------
void	ServerDoRequestHitOtherAItem(TPOS_CN *cn, TPOS_PACKET *packet)
{
	SLONG							npc_no;
	TPOS_PACKET						send_packet;
	TPOS_ITEM						OnMouseItem;
	TPOS_ITEM						DestItem;	
	TPOS_EVENT_NOTIFYSETONMOUSEITEM	EventNotifySetOnMouseItem;
	TPOS_EVENT_NOTIFYSETOTHERAITEM	EventNotifySetOtherAItem;
	TPOS_EVENT_REQUESTHITOTHERAITEM	EventRequestHitOtherAItem;
	EQUIP_UPDATE_RESULT				Result;
	TPOS_EVENT_NOTIFYAFTERCHANGEEQUIP	EventNotifyAfterChangeEquip;	
	char							career, sex;
	SLONG							Ret;

	memcpy(&EventRequestHitOtherAItem, packet->data.cBuf, sizeof(TPOS_EVENT_REQUESTHITOTHERAITEM));

	Ret = FALSE;
	LOCK_CHARACTER(0);
	npc_no = FindCharacterByMainName(cn->User.cId);
	GetCharacterOnMouseItem(npc_no, &OnMouseItem);
	GetCharacterEquipOtherA(npc_no, &DestItem);
	career = (char)GetCharacterCareer(npc_no);
	sex = (char)GetCharacterSex(npc_no);
	UNLOCK_CHARACTER(0);

	if(IsItemNone(&OnMouseItem) != TRUE)
	{
		Ret = IsItemForMyDeck(&OnMouseItem, (SLONG)career, (SLONG)sex);		
	}else
	{
		Ret = TRUE;
	}
	if(Ret == TRUE)
	{
		LOCK_CHARACTER(0);									
		SetCharacterEquipOtherA(npc_no, &OnMouseItem);			
		SetCharacterOnMouseItem(npc_no, &DestItem);
		ComputeCharacterDataAfterChangeEquipOtherA(npc_no,  &Result);
		memcpy(&EventNotifyAfterChangeEquip, &Result, sizeof(TPOS_EVENT_NOTIFYAFTERCHANGEEQUIP));
		UNLOCK_CHARACTER(0);
		// 送出滑鼠物品的信息
		send_packet.Header.dwType = NOTIFY_SET_ONMOUSE_ITEM;
		send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYSETONMOUSEITEM);
		EventNotifySetOnMouseItem.Item = DestItem;
		memcpy(send_packet.data.cBuf, &EventNotifySetOnMouseItem, sizeof(TPOS_EVENT_NOTIFYSETONMOUSEITEM));
		server_send_packet_to_one(cn, &send_packet);
		// 送出其他物品的信息
		send_packet.Header.dwType = NOTIFY_SET_OTHERA_ITEM;
		send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYSETOTHERAITEM);	
		EventNotifySetOtherAItem.Item = OnMouseItem;
		memcpy(send_packet.data.cBuf, &EventNotifySetOtherAItem, sizeof(TPOS_EVENT_NOTIFYSETOTHERAITEM));
		server_send_packet_to_one(cn, &send_packet);
		// 送出改變裝備後的數值改變
		send_packet.Header.dwType = NOTIFY_AFTER_CHANGE_EQUIP;
		send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYAFTERCHANGEEQUIP);			
		memcpy(send_packet.data.cBuf, &EventNotifyAfterChangeEquip, sizeof(TPOS_EVENT_NOTIFYAFTERCHANGEEQUIP));
		server_send_packet_to_one(cn, &send_packet);
	}
}
// -----------------------------------------------------------------------------
void	ServerDoRequestHitOtherBItem(TPOS_CN *cn, TPOS_PACKET *packet)
{
	SLONG							npc_no;
	TPOS_PACKET						send_packet;
	TPOS_ITEM						OnMouseItem;
	TPOS_ITEM						DestItem;	
	TPOS_EVENT_NOTIFYSETONMOUSEITEM	EventNotifySetOnMouseItem;
	TPOS_EVENT_NOTIFYSETOTHERBITEM	EventNotifySetOtherBItem;
	TPOS_EVENT_REQUESTHITOTHERBITEM	EventRequestHitOtherBItem;
	EQUIP_UPDATE_RESULT				Result;
	TPOS_EVENT_NOTIFYAFTERCHANGEEQUIP	EventNotifyAfterChangeEquip;	
	char							career, sex;
	SLONG							Ret;

	memcpy(&EventRequestHitOtherBItem, packet->data.cBuf, sizeof(TPOS_EVENT_REQUESTHITOTHERBITEM));

	Ret = FALSE;
	LOCK_CHARACTER(0);
	npc_no = FindCharacterByMainName(cn->User.cId);
	GetCharacterOnMouseItem(npc_no, &OnMouseItem);
	GetCharacterEquipOtherB(npc_no, &DestItem);
	career = (char)GetCharacterCareer(npc_no);
	sex = (char)GetCharacterSex(npc_no);
	UNLOCK_CHARACTER(0);
	
	if(IsItemNone(&OnMouseItem) != TRUE)
	{
		Ret = IsItemForMyDeck(&OnMouseItem, (SLONG)career, (SLONG)sex);		
	}else
	{
		Ret = TRUE;
	}
	if(Ret == TRUE)
	{
		LOCK_CHARACTER(0);									
		SetCharacterEquipOtherB(npc_no, &OnMouseItem);			
		SetCharacterOnMouseItem(npc_no, &DestItem);
		ComputeCharacterDataAfterChangeEquipOtherB(npc_no,  &Result);
		memcpy(&EventNotifyAfterChangeEquip, &Result, sizeof(TPOS_EVENT_NOTIFYAFTERCHANGEEQUIP));
		UNLOCK_CHARACTER(0);
		// 送出滑鼠物品的信息
		send_packet.Header.dwType = NOTIFY_SET_ONMOUSE_ITEM;
		send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYSETONMOUSEITEM);
		EventNotifySetOnMouseItem.Item = DestItem;
		memcpy(send_packet.data.cBuf, &EventNotifySetOnMouseItem, sizeof(TPOS_EVENT_NOTIFYSETONMOUSEITEM));
		server_send_packet_to_one(cn, &send_packet);
		// 送出其他物品的信息
		send_packet.Header.dwType = NOTIFY_SET_OTHERB_ITEM;
		send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYSETOTHERBITEM);	
		EventNotifySetOtherBItem.Item = OnMouseItem;
		memcpy(send_packet.data.cBuf, &EventNotifySetOtherBItem, sizeof(TPOS_EVENT_NOTIFYSETOTHERBITEM));
		server_send_packet_to_one(cn, &send_packet);
		// 送出改變裝備後的數值改變
		send_packet.Header.dwType = NOTIFY_AFTER_CHANGE_EQUIP;
		send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYAFTERCHANGEEQUIP);			
		memcpy(send_packet.data.cBuf, &EventNotifyAfterChangeEquip, sizeof(TPOS_EVENT_NOTIFYAFTERCHANGEEQUIP));
		server_send_packet_to_one(cn, &send_packet);
	}
}
// -----------------------------------------------------------------------------
void	ServerDoRequestHitOtherCItem(TPOS_CN *cn, TPOS_PACKET *packet)
{
	SLONG							npc_no;
	TPOS_PACKET						send_packet;
	TPOS_ITEM						OnMouseItem;
	TPOS_ITEM						DestItem;	
	TPOS_EVENT_NOTIFYSETONMOUSEITEM	EventNotifySetOnMouseItem;
	TPOS_EVENT_NOTIFYSETOTHERCITEM	EventNotifySetOtherCItem;
	TPOS_EVENT_REQUESTHITOTHERCITEM	EventRequestHitOtherCItem;
	EQUIP_UPDATE_RESULT				Result;
	TPOS_EVENT_NOTIFYAFTERCHANGEEQUIP	EventNotifyAfterChangeEquip;	
	char							career, sex;
	SLONG							Ret;

	memcpy(&EventRequestHitOtherCItem, packet->data.cBuf, sizeof(TPOS_EVENT_REQUESTHITOTHERCITEM));

	Ret = FALSE;
	LOCK_CHARACTER(0);
	npc_no = FindCharacterByMainName(cn->User.cId);
	GetCharacterOnMouseItem(npc_no, &OnMouseItem);
	GetCharacterEquipOtherC(npc_no, &DestItem);
	career = (char)GetCharacterCareer(npc_no);
	sex = (char)GetCharacterSex(npc_no);
	UNLOCK_CHARACTER(0);
	
	if(IsItemNone(&OnMouseItem) != TRUE)
	{
		Ret = IsItemForMyDeck(&OnMouseItem, (SLONG)career, (SLONG)sex);		
	}else
	{
		Ret = TRUE;
	}
	if(Ret == TRUE)
	{
		LOCK_CHARACTER(0);									
		SetCharacterEquipOtherC(npc_no, &OnMouseItem);			
		SetCharacterOnMouseItem(npc_no, &DestItem);
		ComputeCharacterDataAfterChangeEquipOtherC(npc_no,  &Result);
		memcpy(&EventNotifyAfterChangeEquip, &Result, sizeof(TPOS_EVENT_NOTIFYAFTERCHANGEEQUIP));
		UNLOCK_CHARACTER(0);
		// 送出滑鼠物品的信息
		send_packet.Header.dwType = NOTIFY_SET_ONMOUSE_ITEM;
		send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYSETONMOUSEITEM);
		EventNotifySetOnMouseItem.Item = DestItem;
		memcpy(send_packet.data.cBuf, &EventNotifySetOnMouseItem, sizeof(TPOS_EVENT_NOTIFYSETONMOUSEITEM));
		server_send_packet_to_one(cn, &send_packet);
		// 送出其他物品的信息
		send_packet.Header.dwType = NOTIFY_SET_OTHERC_ITEM;
		send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYSETOTHERCITEM);	
		EventNotifySetOtherCItem.Item = OnMouseItem;
		memcpy(send_packet.data.cBuf, &EventNotifySetOtherCItem, sizeof(TPOS_EVENT_NOTIFYSETOTHERCITEM));
		server_send_packet_to_one(cn, &send_packet);
		// 送出改變裝備後的數值改變
		send_packet.Header.dwType = NOTIFY_AFTER_CHANGE_EQUIP;
		send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYAFTERCHANGEEQUIP);			
		memcpy(send_packet.data.cBuf, &EventNotifyAfterChangeEquip, sizeof(TPOS_EVENT_NOTIFYAFTERCHANGEEQUIP));
		server_send_packet_to_one(cn, &send_packet);
	}
}
// -----------------------------------------------------------------------------
void	ServerDoRequestHitSashItem(TPOS_CN *cn, TPOS_PACKET *packet)
{
	SLONG							npc_no;
	TPOS_PACKET						send_packet;
	TPOS_ITEM						OnMouseItem;
	TPOS_ITEM						DestItem;	
	TPOS_EVENT_NOTIFYSETONMOUSEITEM	EventNotifySetOnMouseItem;
	TPOS_EVENT_NOTIFYSETSASHITEM	EventNotifySetSashItem;
	TPOS_EVENT_REQUESTHITSASHITEM	EventRequestHitSashItem;
	char							career, sex;
	SLONG							Ret;
	int								LR;

	memcpy(&EventRequestHitSashItem, packet->data.cBuf, sizeof(TPOS_EVENT_REQUESTHITSASHITEM));
	
	LR = EventRequestHitSashItem.LR;
	Ret = FALSE;
	LOCK_CHARACTER(0);
	npc_no = FindCharacterByMainName(cn->User.cId);
	GetCharacterOnMouseItem(npc_no, &OnMouseItem);
	GetCharacterSashItem(npc_no, EventRequestHitSashItem.SashIndex ,&DestItem);
	career = (char)GetCharacterCareer(npc_no);
	sex = (char)GetCharacterSex(npc_no);
	UNLOCK_CHARACTER(0);
	
	if(LR == LEFT)
	{	
		if(IsItemNone(&OnMouseItem) != TRUE)
		{
			Ret = IsItemForMySash(&OnMouseItem, (SLONG)career, (SLONG)sex);		
		}else
		{
			Ret = TRUE;
		}
		if(Ret == TRUE)
		{
			LOCK_CHARACTER(0);									
			SetCharacterSashItem(npc_no, EventRequestHitSashItem.SashIndex, &OnMouseItem);			
			SetCharacterOnMouseItem(npc_no, &DestItem);
			UNLOCK_CHARACTER(0);
			// 送出滑鼠物品的信息
			send_packet.Header.dwType = NOTIFY_SET_ONMOUSE_ITEM;
			send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYSETONMOUSEITEM);
			EventNotifySetOnMouseItem.Item = DestItem;
			memcpy(send_packet.data.cBuf, &EventNotifySetOnMouseItem, sizeof(TPOS_EVENT_NOTIFYSETONMOUSEITEM));
			server_send_packet_to_one(cn, &send_packet);
			// 送出快捷欄物品的信息
			send_packet.Header.dwType = NOTIFY_SET_SASH_ITEM;
			send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYSETSASHITEM);
			EventNotifySetSashItem.SashIndex = EventRequestHitSashItem.SashIndex;
			EventNotifySetSashItem.Item = OnMouseItem;
			memcpy(send_packet.data.cBuf, &EventNotifySetSashItem, sizeof(TPOS_EVENT_NOTIFYSETSASHITEM));
			server_send_packet_to_one(cn, &send_packet);
		}
	}
	if(LR == RIGHT)
	{
		UINT		hp, maxhp, mp, maxmp;		
		int			addkind = 0;	// 0:無,1:HP,2:MP,3:HP+MP
		TPOS_EVENT_SETNPCHP	EventSetNpcHp;
		TPOS_EVENT_SETNPCMP	EventSetNpcMp;

		LOCK_CHARACTER(0);
		hp = GetCharacterHp(npc_no);
		maxhp = GetCharacterMaxHp(npc_no);
		mp = GetCharacterMp(npc_no);
		maxmp = GetCharacterMaxMp(npc_no);
		UNLOCK_CHARACTER(0);
		if(hp > 0)
		{			
			switch(DestItem.BaseID)
			{
			case 3100:	//傷藥
				hp += maxhp/3;
				addkind = 1;
				break;
			case 3101:	//生命之水
				hp = maxhp;
				addkind = 1;
				break;
			case 3102:	//提神劑
				mp += maxmp/3;
				addkind = 2;
				break;
			case 3103:	//魔力之水
				mp = maxmp;
				addkind = 2;
				break;
			case 3104:	//神秘之水
				hp = maxhp;
				mp = maxmp;
				addkind = 3;
				break;
			}
			if(addkind > 0 && addkind < 4)
			{		
				SetItemNone(&DestItem);
				LOCK_CHARACTER(0);
				SetCharacterHp(npc_no, hp);
				SetCharacterMp(npc_no, mp);
				SetCharacterSashItem(npc_no, EventRequestHitSashItem.SashIndex, &DestItem);
				UNLOCK_CHARACTER(0);
				
				// 送出快捷欄物品的信息
				send_packet.Header.dwType = NOTIFY_SET_SASH_ITEM;
				send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYSETSASHITEM);
				EventNotifySetSashItem.SashIndex = EventRequestHitSashItem.SashIndex;		
				EventNotifySetSashItem.Item = DestItem;
				memcpy(send_packet.data.cBuf, &EventNotifySetSashItem, sizeof(TPOS_EVENT_NOTIFYSETSASHITEM));
				server_send_packet_to_one(cn, &send_packet);
				
				if(addkind == 1 || addkind ==3)
				{			
					// 送出 HP 
					send_packet.Header.dwType = SET_NPC_HP;
					send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_SETNPCHP);
					EventSetNpcHp.iHp = hp;
					EventSetNpcHp.Index = npc_no;
					memcpy(send_packet.data.cBuf, &EventSetNpcHp, sizeof(TPOS_EVENT_SETNPCHP));
					server_send_packet_to_all(&send_packet);			
				}
				if(addkind == 2 || addkind ==3)
				{
					// 送出 MP
					send_packet.Header.dwType = SET_NPC_MP;
					send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_SETNPCMP);
					EventSetNpcMp.iMp = mp;
					EventSetNpcMp.Index = npc_no;
					memcpy(send_packet.data.cBuf, &EventSetNpcMp, sizeof(TPOS_EVENT_SETNPCMP));
					server_send_packet_to_all(&send_packet);			
					
				}
			}
		}
	}
}
// -----------------------------------------------------------------------------
void	ServerDoRequestHitTransItem(TPOS_CN *cn, TPOS_PACKET *packet)
{
	SLONG							npc_no;
	TPOS_PACKET						send_packet;
	TPOS_ITEM						OnMouseItem;
	TPOS_ITEM						DestItem;	
	TPOS_EVENT_NOTIFYSETONMOUSEITEM	EventNotifySetOnMouseItem;
	TPOS_EVENT_NOTIFYSETTRANSITEM	EventNotifySetTransItem;
	TPOS_EVENT_REQUESTHITTRANSITEM	EventRequestHitTransItem;
	SLONG							Ret;

	memcpy(&EventRequestHitTransItem, packet->data.cBuf, sizeof(TPOS_EVENT_REQUESTHITTRANSITEM));
	
	Ret = TRUE; // For Debug 20020129 By Hawke 測傳送物品不判斷
	//Ret = FALSE;
	LOCK_CHARACTER(0);
	npc_no = FindCharacterByMainName(cn->User.cId);
	GetCharacterOnMouseItem(npc_no, &OnMouseItem);
	GetCharacterTransItem(npc_no, EventRequestHitTransItem.TransIndex ,&DestItem);
	UNLOCK_CHARACTER(0);
	// Hawke  [1/29/2003]
	/*
	if(IsItemNone(&OnMouseItem) != TRUE)
	{
		Ret = IsItemTransferable(&OnMouseItem);		
	}else
	{
		Ret = TRUE;
	}
	*/
	if(Ret == TRUE)
	{
		LOCK_CHARACTER(0);									
		SetCharacterTransItem(npc_no, EventRequestHitTransItem.TransIndex, &OnMouseItem);			
		SetCharacterOnMouseItem(npc_no, &DestItem);
		UNLOCK_CHARACTER(0);
		// 送出滑鼠物品的信息
		send_packet.Header.dwType = NOTIFY_SET_ONMOUSE_ITEM;
		send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYSETONMOUSEITEM);
		EventNotifySetOnMouseItem.Item = DestItem;
		memcpy(send_packet.data.cBuf, &EventNotifySetOnMouseItem, sizeof(TPOS_EVENT_NOTIFYSETONMOUSEITEM));
		server_send_packet_to_one(cn, &send_packet);
		// 送出包包物品的信息
		send_packet.Header.dwType = NOTIFY_SET_TRANS_ITEM;
		send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYSETTRANSITEM);
		EventNotifySetTransItem.TransIndex = EventRequestHitTransItem.TransIndex;
		EventNotifySetTransItem.Item = OnMouseItem;
		memcpy(send_packet.data.cBuf, &EventNotifySetTransItem, sizeof(TPOS_EVENT_NOTIFYSETTRANSITEM));
		server_send_packet_to_one(cn, &send_packet);
	}
}
// -----------------------------------------------------------------------------
void	ServerDoRequestHitTreasureItem(TPOS_CN *cn, TPOS_PACKET *packet)
{
	SLONG							npc_no;
	TPOS_PACKET						send_packet;
	TPOS_ITEM						OnMouseItem;
	TPOS_ITEM						DestItem;	
	TPOS_EVENT_NOTIFYSETONMOUSEITEM	EventNotifySetOnMouseItem;
	TPOS_EVENT_NOTIFYSETTREASUREITEM	EventNotifySetTreasureItem;
	TPOS_EVENT_REQUESTHITTREASUREITEM	EventRequestHitTreasureItem;
	int									LR;

	memcpy(&EventRequestHitTreasureItem, packet->data.cBuf, sizeof(TPOS_EVENT_REQUESTHITTREASUREITEM));

	LR = EventRequestHitTreasureItem.LR;
	LOCK_CHARACTER(0);
	npc_no = FindCharacterByMainName(cn->User.cId);
	GetCharacterOnMouseItem(npc_no, &OnMouseItem);
	GetCharacterTreasureItem(npc_no, &DestItem);
	UNLOCK_CHARACTER(0);
	
	if(LR == LEFT)
	{	
		SLONG	can_swap;
		UHINT	BaseId;

		can_swap = FALSE;

		LOCK_CHARACTER(0);									
		SetCharacterTreasureItem(npc_no, &OnMouseItem);			
		SetCharacterOnMouseItem(npc_no, &DestItem);
		UNLOCK_CHARACTER(0);
		BaseId = GetItemBaseID(&OnMouseItem);
		// 如果滑鼠上的物品為空, 可以交換
		if(IsItemNone(&OnMouseItem) == TRUE)can_swap = TRUE;
		// 如果滑鼠上的物品為拼好完整的藏寶圖, 可以交換
		if(BaseId == 300)
		{
			UHINT	whole_piece, current_piece;

			whole_piece = GetTreasureMapItemWholePieces(&OnMouseItem);
			current_piece = GetTreasureMapItemCurrentPieces(&OnMouseItem);

			if(Involution(2, whole_piece) - 1 == current_piece)can_swap = TRUE;
		}
		// 送出滑鼠物品的信息
		send_packet.Header.dwType = NOTIFY_SET_ONMOUSE_ITEM;
		send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYSETONMOUSEITEM);
		EventNotifySetOnMouseItem.Item = DestItem;
		memcpy(send_packet.data.cBuf, &EventNotifySetOnMouseItem, sizeof(TPOS_EVENT_NOTIFYSETONMOUSEITEM));
		server_send_packet_to_one(cn, &send_packet);
		// 送出藏寶圖物品的信息
		send_packet.Header.dwType = NOTIFY_SET_TREASURE_ITEM;
		send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYSETTREASUREITEM);	
		EventNotifySetTreasureItem.Item = OnMouseItem;
		memcpy(send_packet.data.cBuf, &EventNotifySetTreasureItem, sizeof(TPOS_EVENT_NOTIFYSETTREASUREITEM));
		server_send_packet_to_one(cn, &send_packet);
	}
	if(LR == RIGHT)
	{
		if(IsItemNone(&DestItem) == FALSE)
		{
			ServerDoUseTreasureMapItem(npc_no, &DestItem, 255);
		}	
	}
}
// -----------------------------------------------------------------------------
void	ServerDoRequestDropItem(TPOS_CN *cn, TPOS_PACKET *packet)
{
	SLONG							npc_no, x, y, z;
	TPOS_PACKET						send_packet;
	TPOS_ITEM						OnMouseItem;
	TPOS_ITEM						MapItem;
	TPOS_EVENT_REQUESTDROPITEM		EventRequestDropItem;
	TPOS_EVENT_NOTIFYADDMAPITEM		EventNotifyAddMapItem;
	TPOS_EVENT_NOTIFYSETONMOUSEITEM	EventNotifySetOnMouseItem;
	SLONG							Ret;	

	// 船隻裝備可以扔陸地
	// 船隻貨物,糧食,藥材,木材不可扔到陸地
	// 陸上裝備都可以扔到海面上
	// 不可丟棄的物品無法丟到任何地方
	// 水手不可丟棄

	memcpy(&EventRequestDropItem, packet->data.cBuf, sizeof(TPOS_EVENT_REQUESTDROPITEM));

	LOCK_CHARACTER(0);
	npc_no = FindCharacterByMainName(cn->User.cId);
	GetCharacterPosition(npc_no, &x, &y, &z);
	GetCharacterOnMouseItem(npc_no, &OnMouseItem);
	UNLOCK_CHARACTER(0);
	Ret = FindContainItemPosition(&x, &y);
	if(Ret == TTN_OK)
	{
		MapItem = OnMouseItem;
		SetItemNone(&OnMouseItem);
		LOCK_CHARACTER(0);
		SetCharacterOnMouseItem(npc_no, &OnMouseItem);
		UNLOCK_CHARACTER(0);

		LOCK_ITEM(0);
		AddZoneItem(x, y, "", &MapItem);
		UNLOCK_ITEM(0);

		send_packet.Header.dwType = NOTIFY_ADD_MAP_ITEM;
		send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYADDMAPITEM);
		EventNotifyAddMapItem.Item = MapItem;
		EventNotifyAddMapItem.X = x;
		EventNotifyAddMapItem.Y = y;
		memcpy(send_packet.data.cBuf, &EventNotifyAddMapItem, sizeof(TPOS_EVENT_NOTIFYADDMAPITEM));
		server_send_packet_to_all(&send_packet);

		send_packet.Header.dwType = NOTIFY_SET_ONMOUSE_ITEM;
		send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYSETONMOUSEITEM);
		EventNotifySetOnMouseItem.Item = OnMouseItem;
		memcpy(send_packet.data.cBuf, &EventNotifySetOnMouseItem, sizeof(TPOS_EVENT_NOTIFYSETONMOUSEITEM));
		server_send_packet_to_one(cn, &send_packet);
	}
}
// -----------------------------------------------------------------------------
void	ServerDoRequestHitMapItem(TPOS_CN *cn, TPOS_PACKET *packet)
{
	SLONG							npc_no, x, y;
	TPOS_PACKET						send_packet;	
	TPOS_ITEM						MapItem;
	TPOS_ITEM						DestItem;
	TPOS_EVENT_REQUESTHITMAPITEM	EventRequestHitMapItem;
	TPOS_EVENT_NOTIFYDELETEMAPITEM	EventNotifyDeleteMapItem;	
	TPOS_EVENT_NOTIFYSETONMOUSEITEM	EventNotifySetOnMouseItem;
	//TPOS_ITEM						OnMouseItem;
	SLONG							Ret;
	char							career, sex;
	SLONG							bagopen;	
	char							ownername[32];
	char							srcname[32];
	char							srcleadername[32];
	SLONG							pickup;
	ULONG							money;

	pickup = FALSE;
	memcpy(&EventRequestHitMapItem, packet->data.cBuf, sizeof(TPOS_EVENT_REQUESTHITMAPITEM));
	x = EventRequestHitMapItem.X;
	y = EventRequestHitMapItem.Y;

	LOCK_CHARACTER(0);
	npc_no = FindCharacterByMainName(cn->User.cId);	
	career = (char)GetCharacterCareer(npc_no);
	sex = (char)GetCharacterSex(npc_no);
	bagopen = IsCharacterBagOpened(npc_no);
	strcpy(srcname, GetCharacterMainName(npc_no));
	strcpy(srcleadername, GetCharacterTeamMemberMainName(npc_no, 0));
	UNLOCK_CHARACTER(0);

	Ret = CatchZoneItem(x, y, &MapItem);
	if(Ret != -1)
	{	
		LOCK_ITEM(0);		
		strcpy(ownername, GetZoneItemOwner(Ret));		
		UNLOCK_ITEM(0);

		if(strcmp(ownername, srcleadername) == 0)pickup = TRUE;
		if(strcmp(ownername, srcname) == 0)pickup = TRUE;
		if(strcmp(ownername, "") == 0)pickup = TRUE;		
		if(pickup == TRUE)
		{			
			LOCK_ITEM(0);		
			DeleteZoneItem(x, y);
			UNLOCK_ITEM(0);
			send_packet.Header.dwType = NOTIFY_DELETE_MAP_ITEM;
			send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYDELETEMAPITEM);
			EventNotifyDeleteMapItem.X = x;
			EventNotifyDeleteMapItem.Y = y;
			memcpy(send_packet.data.cBuf, &EventNotifyDeleteMapItem, sizeof(TPOS_EVENT_NOTIFYDELETEMAPITEM));
			server_send_packet_to_all(&send_packet);
			
			if(MapItem.BaseID == 200)
			{
				TPOS_EVENT_SETMONEY	EventSetMoney;

				LOCK_CHARACTER(0);
				money = GetCharacterBodyMoney(npc_no);
				money += MapItem.IR.Money.Amount;
				SetCharacterBodyMoney(npc_no, money);
				UNLOCK_CHARACTER(0);
				send_packet.Header.dwType = SET_MONEY;
				send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_SETMONEY);
				EventSetMoney.Money = money;
				memcpy(send_packet.data.cBuf, &EventSetMoney, sizeof(TPOS_EVENT_SETMONEY));
				server_send_packet_to_one(cn, &send_packet);
				return;
			}
			// 如果包包打開 , 直接放到滑鼠上
			if(bagopen == TRUE)
			{			
				LOCK_CHARACTER(0);
				SetCharacterOnMouseItem(npc_no, &MapItem);
				UNLOCK_CHARACTER(0);
				send_packet.Header.dwType = NOTIFY_SET_ONMOUSE_ITEM;
				send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYSETONMOUSEITEM);
				EventNotifySetOnMouseItem.Item = MapItem;
				memcpy(send_packet.data.cBuf, &EventNotifySetOnMouseItem, sizeof(TPOS_EVENT_NOTIFYSETONMOUSEITEM));
				server_send_packet_to_one(cn, &send_packet);
				return;
			}
			
			// 判斷是否為頭部可用之物
			LOCK_CHARACTER(0);
			GetCharacterEquipHead(npc_no, &DestItem);
			UNLOCK_CHARACTER(0);
			if(IsItemNone(&DestItem))
			{
				if(IsItemForMyHead(&MapItem, career, sex))			
				{
					TPOS_EVENT_NOTIFYSETHEADITEM	EventNotifySetHeadItem;
					
					LOCK_CHARACTER(0);
					SetCharacterEquipHead(npc_no, &MapItem);
					UNLOCK_CHARACTER(0);
					send_packet.Header.dwType = NOTIFY_SET_HEAD_ITEM;
					send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYSETHEADITEM);
					EventNotifySetHeadItem.Item = MapItem;
					memcpy(send_packet.data.cBuf, &EventNotifySetHeadItem, sizeof(TPOS_EVENT_NOTIFYSETHEADITEM));
					server_send_packet_to_one(cn, &send_packet);
					return;
				}
			}
			
			// 判斷是否為頸部可用之物
			LOCK_CHARACTER(0);
			GetCharacterEquipNeck(npc_no, &DestItem);
			UNLOCK_CHARACTER(0);
			if(IsItemNone(&DestItem))
			{
				if(IsItemForMyNeck(&MapItem, career, sex))			
				{
					TPOS_EVENT_NOTIFYSETNECKITEM	EventNotifySetNeckItem;
					
					LOCK_CHARACTER(0);
					SetCharacterEquipNeck(npc_no, &MapItem);
					UNLOCK_CHARACTER(0);
					send_packet.Header.dwType = NOTIFY_SET_NECK_ITEM;
					send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYSETNECKITEM);
					EventNotifySetNeckItem.Item = MapItem;
					memcpy(send_packet.data.cBuf, &EventNotifySetNeckItem, sizeof(TPOS_EVENT_NOTIFYSETNECKITEM));
					server_send_packet_to_one(cn, &send_packet);
					return;
				}
			}
			
			// 判斷是否為身體可用之物
			LOCK_CHARACTER(0);
			GetCharacterEquipBody(npc_no, &DestItem);
			UNLOCK_CHARACTER(0);
			if(IsItemNone(&DestItem))
			{
				if(IsItemForMyBody(&MapItem, career, sex))			
				{
					TPOS_EVENT_NOTIFYSETBODYITEM	EventNotifySetBodyItem;
					
					LOCK_CHARACTER(0);
					SetCharacterEquipBody(npc_no, &MapItem);
					UNLOCK_CHARACTER(0);
					send_packet.Header.dwType = NOTIFY_SET_BODY_ITEM;
					send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYSETBODYITEM);
					EventNotifySetBodyItem.Item = MapItem;
					memcpy(send_packet.data.cBuf, &EventNotifySetBodyItem, sizeof(TPOS_EVENT_NOTIFYSETBODYITEM));
					server_send_packet_to_one(cn, &send_packet);
					return;
				}
			}
			
			// 判斷是否為腰部可用之物
			LOCK_CHARACTER(0);
			GetCharacterEquipWaist(npc_no, &DestItem);
			UNLOCK_CHARACTER(0);
			if(IsItemNone(&DestItem))
			{
				if(IsItemForMyWaist(&MapItem, career, sex))			
				{
					TPOS_EVENT_NOTIFYSETWAISTITEM	EventNotifySetWaistItem;
					
					LOCK_CHARACTER(0);
					SetCharacterEquipWaist(npc_no, &MapItem);
					UNLOCK_CHARACTER(0);
					send_packet.Header.dwType = NOTIFY_SET_WAIST_ITEM;
					send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYSETWAISTITEM);
					EventNotifySetWaistItem.Item = MapItem;
					memcpy(send_packet.data.cBuf, &EventNotifySetWaistItem, sizeof(TPOS_EVENT_NOTIFYSETWAISTITEM));
					server_send_packet_to_one(cn, &send_packet);
					return;
				}
			}
			
			// 判斷是否為手套可用之物
			LOCK_CHARACTER(0);
			GetCharacterEquipGlove(npc_no, &DestItem);
			UNLOCK_CHARACTER(0);
			if(IsItemNone(&DestItem))
			{
				if(IsItemForMyGlove(&MapItem, career, sex))			
				{
					TPOS_EVENT_NOTIFYSETGLOVEITEM	EventNotifySetGloveItem;
					
					LOCK_CHARACTER(0);
					SetCharacterEquipGlove(npc_no, &MapItem);
					UNLOCK_CHARACTER(0);
					send_packet.Header.dwType = NOTIFY_SET_GLOVE_ITEM;
					send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYSETGLOVEITEM);
					EventNotifySetGloveItem.Item = MapItem;
					memcpy(send_packet.data.cBuf, &EventNotifySetGloveItem, sizeof(TPOS_EVENT_NOTIFYSETGLOVEITEM));
					server_send_packet_to_one(cn, &send_packet);
					return;
				}
			}
			
			// 判斷是否為手腕可用之物
			LOCK_CHARACTER(0);
			GetCharacterEquipWrist(npc_no, &DestItem);
			UNLOCK_CHARACTER(0);
			if(IsItemNone(&DestItem))
			{
				if(IsItemForMyWrist(&MapItem, career, sex))			
				{
					TPOS_EVENT_NOTIFYSETWRISTITEM	EventNotifySetWristItem;
					
					LOCK_CHARACTER(0);
					SetCharacterEquipWrist(npc_no, &MapItem);
					UNLOCK_CHARACTER(0);
					send_packet.Header.dwType = NOTIFY_SET_WRIST_ITEM;
					send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYSETWRISTITEM);
					EventNotifySetWristItem.Item = MapItem;
					memcpy(send_packet.data.cBuf, &EventNotifySetWristItem, sizeof(TPOS_EVENT_NOTIFYSETWRISTITEM));
					server_send_packet_to_one(cn, &send_packet);
					return;
				}
			}
			
			// 判斷是否為武器
			LOCK_CHARACTER(0);
			GetCharacterEquipWeapon(npc_no, &DestItem);
			UNLOCK_CHARACTER(0);
			if(IsItemNone(&DestItem))
			{
				if(IsItemForMyWeapon(&MapItem, career, sex))			
				{
					TPOS_EVENT_NOTIFYSETWEAPONITEM	EventNotifySetWeaponItem;
					
					LOCK_CHARACTER(0);
					SetCharacterEquipWeapon(npc_no, &MapItem);
					UNLOCK_CHARACTER(0);
					send_packet.Header.dwType = NOTIFY_SET_WEAPON_ITEM;
					send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYSETWEAPONITEM);
					EventNotifySetWeaponItem.Item = MapItem;
					memcpy(send_packet.data.cBuf, &EventNotifySetWeaponItem, sizeof(TPOS_EVENT_NOTIFYSETWEAPONITEM));
					server_send_packet_to_one(cn, &send_packet);
					return;
				}
			}
			
			// 判斷是否為腳部可用之物
			LOCK_CHARACTER(0);
			GetCharacterEquipFeet(npc_no, &DestItem);
			UNLOCK_CHARACTER(0);
			if(IsItemNone(&DestItem))
			{
				if(IsItemForMyFeet(&MapItem, career, sex))			
				{
					TPOS_EVENT_NOTIFYSETFEETITEM	EventNotifySetFeetItem;
					
					LOCK_CHARACTER(0);
					SetCharacterEquipFeet(npc_no, &MapItem);
					UNLOCK_CHARACTER(0);
					send_packet.Header.dwType = NOTIFY_SET_FEET_ITEM;
					send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYSETFEETITEM);
					EventNotifySetFeetItem.Item = MapItem;
					memcpy(send_packet.data.cBuf, &EventNotifySetFeetItem, sizeof(TPOS_EVENT_NOTIFYSETFEETITEM));
					server_send_packet_to_one(cn, &send_packet);
					return;
				}
			}
			
			// 判斷是否為其他部分A可用之物
			LOCK_CHARACTER(0);
			GetCharacterEquipOtherA(npc_no, &DestItem);
			UNLOCK_CHARACTER(0);
			if(IsItemNone(&DestItem))
			{
				if(IsItemForMyDeck(&MapItem, career, sex))			
				{
					TPOS_EVENT_NOTIFYSETOTHERAITEM	EventNotifySetOtherAItem;
					
					LOCK_CHARACTER(0);
					SetCharacterEquipOtherA(npc_no, &MapItem);
					UNLOCK_CHARACTER(0);
					send_packet.Header.dwType = NOTIFY_SET_OTHERA_ITEM;
					send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYSETOTHERAITEM);
					EventNotifySetOtherAItem.Item = MapItem;
					memcpy(send_packet.data.cBuf, &EventNotifySetOtherAItem, sizeof(TPOS_EVENT_NOTIFYSETOTHERAITEM));
					server_send_packet_to_one(cn, &send_packet);
					return;
				}
			}
			
			// 判斷是否為其他部分B可用之物
			LOCK_CHARACTER(0);
			GetCharacterEquipOtherB(npc_no, &DestItem);
			UNLOCK_CHARACTER(0);
			if(IsItemNone(&DestItem))
			{
				if(IsItemForMyDeck(&MapItem, career, sex))			
				{
					TPOS_EVENT_NOTIFYSETOTHERBITEM	EventNotifySetOtherBItem;
					
					LOCK_CHARACTER(0);
					SetCharacterEquipOtherB(npc_no, &MapItem);
					UNLOCK_CHARACTER(0);
					send_packet.Header.dwType = NOTIFY_SET_OTHERB_ITEM;
					send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYSETOTHERBITEM);
					EventNotifySetOtherBItem.Item = MapItem;
					memcpy(send_packet.data.cBuf, &EventNotifySetOtherBItem, sizeof(TPOS_EVENT_NOTIFYSETOTHERBITEM));
					server_send_packet_to_one(cn, &send_packet);
					return;
				}
			}
			
			// 判斷是否為其他部分C可用之物
			LOCK_CHARACTER(0);
			GetCharacterEquipOtherC(npc_no, &DestItem);
			UNLOCK_CHARACTER(0);
			if(IsItemNone(&DestItem))
			{
				if(IsItemForMyDeck(&MapItem, career, sex))			
				{
					TPOS_EVENT_NOTIFYSETOTHERCITEM	EventNotifySetOtherCItem;
					
					LOCK_CHARACTER(0);
					SetCharacterEquipOtherC(npc_no, &MapItem);
					UNLOCK_CHARACTER(0);
					send_packet.Header.dwType = NOTIFY_SET_OTHERC_ITEM;
					send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYSETOTHERCITEM);
					EventNotifySetOtherCItem.Item = MapItem;
					memcpy(send_packet.data.cBuf, &EventNotifySetOtherCItem, sizeof(TPOS_EVENT_NOTIFYSETOTHERCITEM));
					server_send_packet_to_one(cn, &send_packet);
					return;
				}
			}
			
			// 判斷是否為其他部分C可用之物
			LOCK_CHARACTER(0);
			GetCharacterEquipOtherC(npc_no, &DestItem);
			UNLOCK_CHARACTER(0);
			if(IsItemNone(&DestItem))
			{
				if(IsItemForMyDeck(&MapItem, career, sex))			
				{
					TPOS_EVENT_NOTIFYSETOTHERCITEM	EventNotifySetOtherCItem;
					
					LOCK_CHARACTER(0);
					SetCharacterEquipOtherC(npc_no, &MapItem);
					UNLOCK_CHARACTER(0);
					send_packet.Header.dwType = NOTIFY_SET_OTHERC_ITEM;
					send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYSETOTHERCITEM);
					EventNotifySetOtherCItem.Item = MapItem;
					memcpy(send_packet.data.cBuf, &EventNotifySetOtherCItem, sizeof(TPOS_EVENT_NOTIFYSETOTHERCITEM));
					server_send_packet_to_one(cn, &send_packet);
					return;
				}
			}
			
			// 判斷是否為藥品		
			int	t;
			if(IsItemForMySash(&MapItem, career, sex))
			{			
				for(t = 0;t < MAX_CHARACTER_SASH_ITEMS;t++)
				{
					LOCK_CHARACTER(0);
					GetCharacterSashItem(npc_no, t, &DestItem);
					UNLOCK_CHARACTER(0);
					if(IsItemNone(&DestItem))
					{
						LOCK_CHARACTER(0);
						SetCharacterSashItem(npc_no, t, &MapItem);
						UNLOCK_CHARACTER(0);
						
						TPOS_EVENT_NOTIFYSETSASHITEM	EventNotifySetSashItem;				
						
						send_packet.Header.dwType = NOTIFY_SET_SASH_ITEM;
						send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYSETSASHITEM);
						EventNotifySetSashItem.Item = MapItem;
						EventNotifySetSashItem.SashIndex = t;
						memcpy(send_packet.data.cBuf, &EventNotifySetSashItem, sizeof(TPOS_EVENT_NOTIFYSETSASHITEM));
						server_send_packet_to_one(cn, &send_packet);
						return;
					}					
				}		
			}
			
			// 包包是否有空位 , 有的話放進去
			t = ServerDoFindBagSpace(npc_no);
			if(t != -1)			
			{
				LOCK_CHARACTER(0);
				SetCharacterBagItem(npc_no, t, &MapItem);
				UNLOCK_CHARACTER(0);
					
				TPOS_EVENT_NOTIFYSETBAGITEM	EventNotifySetBagItem;				
					
				send_packet.Header.dwType = NOTIFY_SET_BAG_ITEM;
				send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYSETBAGITEM);
				EventNotifySetBagItem.Item = MapItem;
				EventNotifySetBagItem.BagIndex = t;
				memcpy(send_packet.data.cBuf, &EventNotifySetBagItem, sizeof(TPOS_EVENT_NOTIFYSETBAGITEM));
				server_send_packet_to_one(cn, &send_packet);
				return;				
			}
			
			// 全部條件判斷過 , 無符合就直接放滑鼠上
			LOCK_CHARACTER(0);
			SetCharacterOnMouseItem(npc_no, &MapItem);
			UNLOCK_CHARACTER(0);
			
			send_packet.Header.dwType = NOTIFY_SET_ONMOUSE_ITEM;
			send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYSETONMOUSEITEM);
			EventNotifySetOnMouseItem.Item = MapItem;
			memcpy(send_packet.data.cBuf, &EventNotifySetOnMouseItem, sizeof(TPOS_EVENT_NOTIFYSETONMOUSEITEM));
			server_send_packet_to_one(cn, &send_packet);	
		}else
		{
			// Hawke  [2/20/2003]
			// TO DO
			// 要返回不能撿的訊息
		}
	}
}
// -----------------------------------------------------------------------------
void	ServerDoClearOnMouseItemForPlayerExit(int npc_no)
{
	TPOS_ITEM						OnMouseItem;
	TPOS_ITEM						BagItem;
	TPOS_PACKET						send_packet;
	TPOS_EVENT_NOTIFYSETBAGITEM		EventNotifySetBagItem;
	TPOS_EVENT_NOTIFYSETONMOUSEITEM	EventNotifySetOnMouseItem;
	TPOS_EVENT_NOTIFYADDMAPITEM		EventNotifyAddMapItem;
	int								t;
	int								putinbag = FALSE;
	int								cn_index;	
	SLONG							Ret, x, y, z;
	
	LOCK_CONNECTION(0);
	cn_index = FindConnectionByName(GetCharacterMainName(npc_no));	
	UNLOCK_CONNECTION(0);

	GetCharacterPosition(npc_no, &x, &y, &z);
	GetCharacterOnMouseItem(npc_no, &OnMouseItem);
	if(!IsItemNone(&OnMouseItem))
	{
		for(t = 0;t < MAX_CHARACTER_BAG_ITEMS;t++)
		{
			GetCharacterBagItem(npc_no, t, &BagItem);
			if(IsItemNone(&BagItem))
			{
				SetCharacterBagItem(npc_no, t, &OnMouseItem);
				send_packet.Header.dwType = NOTIFY_SET_BAG_ITEM;
				send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYADDMAPITEM);
				EventNotifySetBagItem.BagIndex = t;
				EventNotifySetBagItem.Item = OnMouseItem;
				memcpy(send_packet.data.cBuf, &EventNotifySetBagItem, sizeof(TPOS_EVENT_NOTIFYADDMAPITEM));

				server_send_packet_to_one(&Pos_Cn[cn_index], &send_packet);

				putinbag = TRUE;
				break;
			}
		}
		if(putinbag == FALSE)
		{
			Ret = FindContainItemPosition(&x, &y);
			if(Ret == TTN_OK)
			{
				LOCK_ITEM(0);
				AddZoneItem(x, y, "", &OnMouseItem);
				UNLOCK_ITEM(0);				
				send_packet.Header.dwType = NOTIFY_ADD_MAP_ITEM;
				send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYSETBAGITEM);			
				EventNotifyAddMapItem.Item = OnMouseItem;
				EventNotifyAddMapItem.X = x;
				EventNotifyAddMapItem.Y = y;
				memcpy(send_packet.data.cBuf, &EventNotifyAddMapItem, sizeof(TPOS_EVENT_NOTIFYSETBAGITEM));
				
				server_send_packet_to_one(&Pos_Cn[cn_index], &send_packet);
			}
			
		}
		SetItemNone(&OnMouseItem);
		SetCharacterOnMouseItem(npc_no, &OnMouseItem);

		send_packet.Header.dwType = NOTIFY_SET_ONMOUSE_ITEM;
		send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYSETONMOUSEITEM);		
		EventNotifySetOnMouseItem.Item = OnMouseItem;
		memcpy(send_packet.data.cBuf, &EventNotifySetOnMouseItem, sizeof(TPOS_EVENT_NOTIFYSETONMOUSEITEM));

		server_send_packet_to_one(&Pos_Cn[cn_index], &send_packet);
	}
}
// -----------------------------------------------------------------------------
void	ServerDoRequestNpcProc(TPOS_CN *cn, TPOS_PACKET *packet)
{
	TPOS_EVENT_REQUESTNPCPROC	EventRequestNpcProc;
	int							npc_no;

	memcpy(&EventRequestNpcProc, packet->data.cBuf, sizeof(TPOS_EVENT_REQUESTNPCPROC));

	LOCK_CHARACTER(0);
	npc_no = FindCharacterByMainName(cn->User.cId);
	UNLOCK_CHARACTER(0);
		
	LOCK_SCRIPT(0);
	mac_pipe.active_npc = npc_no;
	mac_pipe.script_npc = EventRequestNpcProc.TargetNPCIndex;
	process_script(EventRequestNpcProc.NextProc);
	UNLOCK_SCRIPT(0);
}
// -----------------------------------------------------------------------------
void	ServerDoSendNotifyNpcOnPauseToAll(SLONG	npc_index)
{
	TPOS_EVENT_NOTIFYNPCONPAUSE	EventNotifyNpcOnPause;
	TPOS_PACKET					send_packet;	
	
	send_packet.Header.dwType = NOTIFY_NPC_ON_PAUSE;
	send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYNPCONPAUSE);
	
	EventNotifyNpcOnPause.OnPauseNpcIndex = npc_index;
	memcpy(send_packet.data.cBuf, &EventNotifyNpcOnPause, sizeof(TPOS_EVENT_NOTIFYNPCONPAUSE));
	
	server_send_packet_to_all(&send_packet);
}
// -----------------------------------------------------------------------------
void	ServerDoSendNotifyNpcNoPauseToAll(SLONG	npc_index)
{
	TPOS_EVENT_NOTIFYNPCNOPAUSE	EventNotifyNpcNoPause;
	TPOS_PACKET					send_packet;	
	
	send_packet.Header.dwType = NOTIFY_NPC_NO_PAUSE;
	send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYNPCNOPAUSE);
	
	EventNotifyNpcNoPause.NoPauseNpcIndex = npc_index;
	memcpy(send_packet.data.cBuf, &EventNotifyNpcNoPause, sizeof(TPOS_EVENT_NOTIFYNPCNOPAUSE));
	
	server_send_packet_to_all(&send_packet);
}
// -----------------------------------------------------------------------------
void	ServerDoRequestChangeDir(TPOS_CN *cn, TPOS_PACKET *packet)
{
	TPOS_EVENT_REQUESTCHANGEDIR		EventRequestChangeDir;
	TPOS_EVENT_GETCHANGENPCDOING	EventGetChangeNpcDoing;
	TPOS_PACKET						send_packet;
	int								npc_no;	

	memcpy(&EventRequestChangeDir, packet->data.cBuf, sizeof(TPOS_EVENT_REQUESTCHANGEDIR));

	switch(ZoneType)
	{
	case CITY_NORMAL:
	case CITY_FINDGOLD:
	case CITY_PK:
	case CITY_NEWBIE:
	case CITY_BIRTH:
	case FIELD_NORMAL:
	case FIELD_FINDGOLD:
	case FIELD_PK:
	case FIELD_NEWBIE:
	case FIELD_BIRTH:
		LOCK_CHARACTER(0);
		npc_no = FindCharacterByMainName(cn->User.cId);
		SetCharacterDir(npc_no, EventRequestChangeDir.Dir);
		UNLOCK_CHARACTER(0);		
		
		send_packet.Header.dwType = CHANGE_NPC_DOING;
		send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_GETCHANGENPCDOING);
		
		EventGetChangeNpcDoing.Index = npc_no;
		EventGetChangeNpcDoing.DoingKind = DOING_KIND_STAND;
		EventGetChangeNpcDoing.DoingStep = 0;
		EventGetChangeNpcDoing.d1 = (SLONG)EventRequestChangeDir.Dir;
		EventGetChangeNpcDoing.d2 = 0;
		EventGetChangeNpcDoing.d3 = 0;
		EventGetChangeNpcDoing.d4 = 0;
		EventGetChangeNpcDoing.d5 = 0;
		
		memcpy(send_packet.data.cBuf, &EventGetChangeNpcDoing, sizeof(TPOS_EVENT_GETCHANGENPCDOING));
		
		server_send_packet_to_all(&send_packet);
		break;
		
	case SAIL_NORMAL:
	case SAIL_FINDGOLD:
	case SAIL_PK:
	case SAIL_NEWBIE:
	case SAIL_BIRTH:
		break;
	}	
}
// -----------------------------------------------------------------------------
void	ServerDoZoneGetItemID(TPOS_CN *cn, TPOS_PACKET *packet)
{
	//TPOS_EVENT_ZONEGETITEMID	EventZoneGetItemID;
}
// -----------------------------------------------------------------------------
void	ServerDoZoneRequestItemID(TPOS_CN *cn, TPOS_PACKET *packet)
{
}
// -----------------------------------------------------------------------------
void	ServerDoChangeMainNameColorAtFirstFight(ULONG src_npcno, ULONG dest_npcno)
{
	SLONG						src_mainname_color;
	SLONG						src_mainname_color_2;
	SLONG						dest_mainname_color;
	TPOS_EVENT_SETMAINNAMECOLOR	EventSetMainNameColor;
	TPOS_PACKET					send_packet;

	LOCK_CHARACTER(0);
	src_mainname_color = GetCharacterMainNameColor(src_npcno);
	dest_mainname_color = GetCharacterMainNameColor(dest_npcno);
	src_mainname_color_2 = src_mainname_color;

	if(dest_npcno >= 500)
	{
		if(GetCharacterKind(dest_npcno) == 8)
		{
			src_mainname_color_2 = COLOR_GRAY;
			SetCharacterMainNameColor(src_npcno, src_mainname_color_2);
			SetCharacterNameColorTicks(src_npcno, 0); // 15 分鐘後恢復
		}
	}else
	{		
		switch(src_mainname_color)
		{
		case COLOR_RED:		
			break;
		case COLOR_GRAY:	
			SetCharacterNameColorTicks(src_npcno, 0);
			break;
		case COLOR_BLUE:
		case COLOR_YELLOW:
			switch(dest_mainname_color)
			{
			case COLOR_RED:			
			case COLOR_GRAY:
				break;
			case COLOR_BLUE:
			case COLOR_YELLOW:
				src_mainname_color_2 = COLOR_GRAY;
				SetCharacterMainNameColor(src_npcno, src_mainname_color_2);
				SetCharacterNameColorTicks(src_npcno, 0); // 15 分鐘後恢復
				break;
			}
			break;	
		}
	}
	UNLOCK_CHARACTER(0);
	if(src_mainname_color != src_mainname_color_2)
	{
		send_packet.Header.dwType = SET_MAINNAME_COLOR;
		send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_SETMAINNAMECOLOR);
		EventSetMainNameColor.Npc_No = src_npcno;
		EventSetMainNameColor.MainNameColor = (char)src_mainname_color_2;
		memcpy(send_packet.data.cBuf, &EventSetMainNameColor, sizeof(TPOS_EVENT_SETMAINNAMECOLOR));
		server_send_packet_to_all(&send_packet);
	}
}
// -----------------------------------------------------------------------------
void	ServerDoChangeMainNameColorAtLastFight(ULONG src_npcno, ULONG dest_npcno)
{
	enum 
	{	
		REDVSRED		= 0,		
		REDVSBLUE		= 1,
		REDVSYELLOW		= 2,		
		BLUEVSRED		= 3,
		BLUEVSBLUE		= 4,
		BLUEVSYELLOW	= 5,
		YELLOWVSRED		= 6,
		YELLOWVSBLUE	= 7,
		YELLOWVSYELLOW	= 8,
		BLUEVSGBLUE		= 9,
		BLUEVSGYELLOW	= 10,
		YELLOWVSGBLUE	= 11,
		YELLOWVSGYELLOW	= 12
	};
	SLONG						src_mainname_color;
	SLONG						src_mainname_color_2;
	SLONG						dest_mainname_color;
	SLONG						dest_mainname_color_2;
	TPOS_EVENT_SETMAINNAMECOLOR	EventSetMainNameColor;
	TPOS_PACKET					send_packet;
	ULONG						SrcPkCount, DestPkCount;	
	ULONG						SrcPkedCount, DestPkedCount;	
	SLONG						SrcGoodEvil, DestGoodEvil;
	int							CheckKind = -1;	
	
	LOCK_CHARACTER(0);	
	// 計算 PK 值和善惡值
	SrcPkCount = GetCharacterPkCount(src_npcno);
	DestPkCount = GetCharacterPkCount(dest_npcno);
	SrcPkedCount = GetCharacterPkedCount(src_npcno);
	DestPkedCount = GetCharacterPkedCount(dest_npcno);
	SrcGoodEvil = GetCharacterGoodEvil(src_npcno);
	DestGoodEvil = GetCharacterGoodEvil(dest_npcno);
	src_mainname_color = GetCharacterMainNameColor(src_npcno);
	dest_mainname_color = GetCharacterMainNameColor(dest_npcno);
	src_mainname_color_2 = src_mainname_color;
	dest_mainname_color_2 = dest_mainname_color;
	SrcPkCount++;
	DestPkedCount++;	
	SetCharacterPkCount(src_npcno, SrcPkCount);
	SetCharacterPkedCount(dest_npcno, DestPkedCount);	
	UNLOCK_CHARACTER(0);

	if(dest_npcno < 500)
	{	
		switch(src_mainname_color)
		{
		case COLOR_RED:
			switch(dest_mainname_color)
			{
			case COLOR_RED:
				CheckKind = REDVSRED;
				break;
			case COLOR_GRAY:				
				if(DestGoodEvil == 0)	CheckKind = REDVSBLUE;
				if(DestGoodEvil > 0)	CheckKind = REDVSYELLOW;
				break;
			case COLOR_BLUE:
				CheckKind = REDVSBLUE;
				break;
			case COLOR_YELLOW:
				CheckKind = REDVSYELLOW;
				break;
			}
			break;
		case COLOR_GRAY:
			switch(dest_mainname_color)
			{
			case COLOR_RED:
				if(SrcGoodEvil < 0)	CheckKind = REDVSRED;
				if(SrcGoodEvil == 0)CheckKind = BLUEVSRED;
				if(SrcGoodEvil > 0)	CheckKind = YELLOWVSRED;
				break;
			case COLOR_GRAY:
				if(SrcGoodEvil < 0)
				{					
					if(DestGoodEvil == 0)	CheckKind = REDVSBLUE;
					if(DestGoodEvil > 0)	CheckKind = REDVSYELLOW;
				}
				if(SrcGoodEvil == 0)
				{					
					if(DestGoodEvil == 0)	CheckKind = BLUEVSGBLUE;
					if(DestGoodEvil > 0)	CheckKind = BLUEVSGYELLOW;
				}
				if(SrcGoodEvil > 0)
				{					
					if(DestGoodEvil == 0)	CheckKind = YELLOWVSGBLUE;
					if(DestGoodEvil > 0)	CheckKind = YELLOWVSGYELLOW;
				}
				break;
			case COLOR_BLUE:
				if(SrcGoodEvil < 0)	CheckKind = REDVSBLUE;
				if(SrcGoodEvil == 0)CheckKind = BLUEVSBLUE;
				if(SrcGoodEvil > 0)	CheckKind = YELLOWVSBLUE;
				break;
			case COLOR_YELLOW:
				if(SrcGoodEvil < 0)	CheckKind = REDVSYELLOW;
				if(SrcGoodEvil == 0)CheckKind = BLUEVSYELLOW;
				if(SrcGoodEvil > 0)	CheckKind = YELLOWVSYELLOW;
				break;
			}
			break;			
		case COLOR_BLUE:
			switch(dest_mainname_color)
			{
			case COLOR_RED:
				CheckKind = BLUEVSRED;
				break;
			case COLOR_GRAY:				
				if(DestGoodEvil == 0)	CheckKind = BLUEVSGBLUE;
				if(DestGoodEvil > 0)	CheckKind = BLUEVSGYELLOW;
				break;
			case COLOR_BLUE:
				CheckKind = BLUEVSBLUE;
				break;
			case COLOR_YELLOW:
				CheckKind = BLUEVSYELLOW;
				break;
			}
			break;
		case COLOR_YELLOW:
			switch(dest_mainname_color)
			{
			case COLOR_RED:
				CheckKind = YELLOWVSRED;
				break;
			case COLOR_GRAY:
				if(DestGoodEvil == 0)	CheckKind = YELLOWVSGBLUE;
				if(DestGoodEvil > 0)	CheckKind = YELLOWVSGYELLOW;
				break;
			case COLOR_BLUE:
				CheckKind = YELLOWVSBLUE;
				break;
			case COLOR_YELLOW:
				CheckKind = YELLOWVSBLUE;
				break;
			}
			break;
		}

		LOCK_CHARACTER(0);
		switch(CheckKind)
		{
		case REDVSRED:
			if(abs(DestGoodEvil) > 5 && abs(SrcGoodEvil) <= 10)
			{			
				SrcGoodEvil -= (ROUND((abs(DestGoodEvil) * 0.2) + 0.5) + 1);							   
				SetCharacterGoodEvil(src_npcno, SrcGoodEvil);
			}			
			DestGoodEvil += (ROUND((abs(DestGoodEvil) * 0.2) + 0.5) + 5);
			if(DestGoodEvil > 0)
			{
				DestGoodEvil = 0;
				dest_mainname_color_2 = COLOR_BLUE;
				SetCharacterMainNameColor(dest_npcno, dest_mainname_color_2);
				SetCharacterNameColorTicks(src_npcno, 0);
			}
			SetCharacterGoodEvil(dest_npcno, DestGoodEvil);
			// Hawke  [2/17/2003]
			// ToDo... 隨機降低技能等級		
			break;
		case REDVSBLUE:
			if(GetCharacterPrestige(dest_npcno) + 5 > abs(SrcGoodEvil))
			{						
				SrcGoodEvil --;
				SetCharacterGoodEvil(src_npcno, SrcGoodEvil);
			}			
			break;
		case REDVSYELLOW:
			if(abs(DestGoodEvil) <= 5 && abs(SrcGoodEvil) >= 10)break;
			
			SrcGoodEvil -= (ROUND((abs(DestGoodEvil) * 0.2) + 0.5) + 1);							   
			SetCharacterGoodEvil(src_npcno, SrcGoodEvil);
			
			DestGoodEvil -= (ROUND((abs(DestGoodEvil) * 0.2) + 0.5) + 5);
			if(DestGoodEvil <= 0)
			{
				DestGoodEvil = 0;
				dest_mainname_color_2 = COLOR_BLUE;
				SetCharacterMainNameColor(dest_npcno, dest_mainname_color_2);
				SetCharacterNameColorTicks(src_npcno, 0);
			}
			SetCharacterGoodEvil(dest_npcno, DestGoodEvil);
			break;
		case BLUEVSRED:			
			src_mainname_color_2 = COLOR_YELLOW;
			SetCharacterMainNameColor(src_npcno, src_mainname_color_2);			
			SetCharacterNameColorTicks(src_npcno, 0);
			SrcGoodEvil += (ROUND((abs(DestGoodEvil) * 0.2) + 0.5) + 1);
			SetCharacterGoodEvil(src_npcno, SrcGoodEvil);
			
			DestGoodEvil += (ROUND((abs(DestGoodEvil) * 0.2) + 0.5) + 5);
			if(DestGoodEvil > 0)
			{
				DestGoodEvil = 0;
				dest_mainname_color_2 = COLOR_BLUE;
				SetCharacterMainNameColor(dest_npcno, dest_mainname_color_2);
				SetCharacterNameColorTicks(src_npcno, 0);
			}
			SetCharacterGoodEvil(dest_npcno, DestGoodEvil);
			// Hawke  [2/17/2003]
			// ToDo... 隨機降低技能等級
			break;
		case BLUEVSGBLUE:
		case BLUEVSGYELLOW:		
		case YELLOWVSGBLUE:			
		case YELLOWVSGYELLOW:								
			break;
		case BLUEVSBLUE:
		case BLUEVSYELLOW:		
		case YELLOWVSBLUE:			
		case YELLOWVSYELLOW:		
			src_mainname_color_2 = COLOR_RED;
			SetCharacterMainNameColor(src_npcno, src_mainname_color_2);
			SetCharacterNameColorTicks(src_npcno, 0);
			SrcGoodEvil = 0;
			SrcGoodEvil --;
			SetCharacterGoodEvil(src_npcno, SrcGoodEvil);
			break;
		case YELLOWVSRED:
			if(abs(DestGoodEvil) > 5 && abs(SrcGoodEvil) <= 10)
			{						
				SrcGoodEvil += (ROUND((abs(DestGoodEvil) * 0.2) + 0.5) + 1);
				SetCharacterGoodEvil(src_npcno, SrcGoodEvil);
			}
			
			DestGoodEvil += (ROUND((abs(DestGoodEvil) * 0.2) + 0.5) + 5);
			if(DestGoodEvil > 0)
			{
				DestGoodEvil = 0;
				dest_mainname_color_2 = COLOR_BLUE;
				SetCharacterMainNameColor(dest_npcno, dest_mainname_color_2);
				SetCharacterNameColorTicks(src_npcno, 0);
			}
			SetCharacterGoodEvil(dest_npcno, DestGoodEvil);
			// Hawke  [2/17/2003]
			// ToDo... 隨機降低技能等級
			break;
		}
		UNLOCK_CHARACTER(0);
	}

	ServerSendGoodEvilToPlayer(src_npcno, SrcGoodEvil, SrcPkCount, SrcPkedCount);	
	ServerSendGoodEvilToPlayer(dest_npcno, DestGoodEvil, DestPkCount, DestPkedCount);	
	
	if(src_mainname_color != src_mainname_color_2)
	{
		send_packet.Header.dwType = SET_MAINNAME_COLOR;
		send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_SETMAINNAMECOLOR);
		EventSetMainNameColor.Npc_No = src_npcno;
		EventSetMainNameColor.MainNameColor = (char)src_mainname_color_2;
		memcpy(send_packet.data.cBuf, &EventSetMainNameColor, sizeof(TPOS_EVENT_SETMAINNAMECOLOR));
		server_send_packet_to_all(&send_packet);
	}
	if(dest_mainname_color != dest_mainname_color_2)
	{
		send_packet.Header.dwType = SET_MAINNAME_COLOR;
		send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_SETMAINNAMECOLOR);
		EventSetMainNameColor.Npc_No = dest_npcno;
		EventSetMainNameColor.MainNameColor = (char)dest_mainname_color_2;
		memcpy(send_packet.data.cBuf, &EventSetMainNameColor, sizeof(TPOS_EVENT_SETMAINNAMECOLOR));
		server_send_packet_to_all(&send_packet);
	}	
}
// -----------------------------------------------------------------------------
void	ServerSendGoodEvilToPlayer(ULONG npc_no, SLONG	goodevil, ULONG pkcount, ULONG pkedcount)
{
	TPOS_PACKET				send_packet;
	TPOS_EVENT_SETGOODEVIL	EventSetGoodEvil;
		
	send_packet.Header.dwType = SET_GOODEVIL;
	send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_SETGOODEVIL);
	EventSetGoodEvil.GoodEvil = goodevil;
	EventSetGoodEvil.PkedCount = pkedcount;
	EventSetGoodEvil.PkCount = pkcount;
	memcpy(send_packet.data.cBuf, &EventSetGoodEvil, sizeof(TPOS_EVENT_SETGOODEVIL));
	server_send_packet_to_player(npc_no, &send_packet);	
}
// -----------------------------------------------------------------------------
void	ServerDoGodRequestFullHpMp(TPOS_CN *cn, TPOS_PACKET *packet)
{	
	TPOS_EVENT_SETNPCHP			EventSetNpcHp;
	TPOS_EVENT_SETNPCMP			EventSetNpcMp;
	TPOS_PACKET					send_packet;
	SLONG						npc_no;
	UHINT						maxhp,maxmp;

	LOCK_CHARACTER(0);
	npc_no = FindCharacterByMainName(cn->User.cId);
	UNLOCK_CHARACTER(0);
	if(npc_no >= 0)
	{
		LOCK_CHARACTER(0);
		maxhp = GetCharacterMaxHp(npc_no);
		maxmp = GetCharacterMaxMp(npc_no);
		SetCharacterHp(npc_no, maxhp);
		SetCharacterMp(npc_no, maxmp);
		UNLOCK_CHARACTER(0);

		send_packet.Header.dwType = SET_NPC_HP;
		send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_SETNPCHP);

		EventSetNpcHp.Index = npc_no;
		EventSetNpcHp.iHp = maxhp;
		memcpy(send_packet.data.cBuf, &EventSetNpcHp, sizeof(TPOS_EVENT_SETNPCHP));
		server_send_packet_to_all(&send_packet);

		send_packet.Header.dwType = SET_NPC_MP;
		send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_SETNPCMP);

		EventSetNpcMp.Index = npc_no;
		EventSetNpcMp.iMp = maxmp;
		memcpy(send_packet.data.cBuf, &EventSetNpcMp, sizeof(TPOS_EVENT_SETNPCMP));
		server_send_packet_to_all(&send_packet);
	}		
}
// -----------------------------------------------------------------------------
void	ServerDoGodRequestJumpTo(TPOS_CN *cn, TPOS_PACKET *packet)
{
}
// -----------------------------------------------------------------------------
void	ServerDoGodRequestItem(TPOS_CN *cn, TPOS_PACKET *packet)
{
	TPOS_GOD_REQUESTITEM			GodRequestItem;
	TPOS_PACKET						send_packet;
	TPOS_EVENT_NOTIFYADDMAPITEM		EventNotifyAddMapItem;
	TPOS_ITEM						MapItem;
	SLONG							npc_no, x, y, z;
	SLONG							Ret;

	memcpy(&GodRequestItem, packet->data.cBuf, sizeof(TPOS_GOD_REQUESTITEM));

	LOCK_CHARACTER(0);
	npc_no = FindCharacterByMainName(cn->User.cId);
	GetCharacterPosition(npc_no, &x, &y, &z);	
	UNLOCK_CHARACTER(0);
	Ret = FindContainItemPosition(&x, &y);
	if(Ret == TTN_OK)
	{
		SetItemID(&MapItem, 50);
		SetItemBaseID(&MapItem, GodRequestItem.BaseID);

		LOCK_ITEM(0);
		AddZoneItem(x, y, "", &MapItem);
		UNLOCK_ITEM(0);

		send_packet.Header.dwType = NOTIFY_ADD_MAP_ITEM;
		send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYADDMAPITEM);
		EventNotifyAddMapItem.Item = MapItem;
		EventNotifyAddMapItem.X = x;
		EventNotifyAddMapItem.Y = y;
		memcpy(send_packet.data.cBuf, &EventNotifyAddMapItem, sizeof(TPOS_EVENT_NOTIFYADDMAPITEM));
		server_send_packet_to_all(&send_packet);
	}
	//41
	//GodRequestItem.BaseID 	
}
// -----------------------------------------------------------------------------
void	ServerDoGodRequestMoney(TPOS_CN *cn, TPOS_PACKET *packet)
{
	TPOS_GOD_REQUESTMONEY	GodRequestMoney;
	TPOS_EVENT_SETMONEY		EventSetMoney;
	TPOS_PACKET				send_packet;
	SLONG					npc_no;
	ULONG					money;

	memcpy(&GodRequestMoney, packet->data.cBuf, sizeof(TPOS_GOD_REQUESTMONEY));

	LOCK_CHARACTER(0);
	npc_no = FindCharacterByMainName(cn->User.cId);
	UNLOCK_CHARACTER(0);
	if(npc_no >= 0)
	{
		LOCK_CHARACTER(0);
		money = GetCharacterBodyMoney(npc_no);
		money += GodRequestMoney.Money;
		SetCharacterBodyMoney(npc_no, money);
		UNLOCK_CHARACTER(0);
		
		send_packet.Header.dwType = SET_MONEY;
		send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_SETMONEY);
		EventSetMoney.Money = money;		
		memcpy(send_packet.data.cBuf, &EventSetMoney, sizeof(TPOS_EVENT_SETMONEY));

		server_send_packet_to_player(npc_no, &send_packet);
	}
}
// -----------------------------------------------------------------------------
void	ServerDoGodRequestExp(TPOS_CN *cn, TPOS_PACKET *packet)
{
	TPOS_GOD_REQUESTEXP		GodRequestExp;
	TPOS_PACKET				send_packet;
	TPOS_EVENT_SETNPCEXP	EventSetNpcExp;
	SLONG					npc_no;
	
	memcpy(&GodRequestExp, packet->data.cBuf, sizeof(TPOS_GOD_REQUESTEXP));

	LOCK_CHARACTER(0);
	npc_no = FindCharacterByMainName(cn->User.cId);
	UNLOCK_CHARACTER(0);
	if(npc_no >= 0)
	{
		LOCK_CHARACTER(0);
		SetCharacterExp(npc_no, GodRequestExp.Exp);
		UNLOCK_CHARACTER(0);
		
		send_packet.Header.dwType = SET_NPC_EXP;
		send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_SETNPCEXP);
		EventSetNpcExp.Exp = GodRequestExp.Exp;
		EventSetNpcExp.Index = npc_no;
		memcpy(send_packet.data.cBuf, &EventSetNpcExp, sizeof(TPOS_EVENT_SETNPCEXP));

		server_send_packet_to_player(npc_no, &send_packet);
	}
}
// -----------------------------------------------------------------------------
void	ServerDoGodRequestMoveFast(TPOS_CN *cn, TPOS_PACKET *packet)
{
	TPOS_GOD_REQUESTMOVEFAST	GodRequestMoveFast;
	TPOS_EVENT_SETNPCMOVESPEED	EventSetNpcMoveSpeed;
	TPOS_PACKET					send_packet;
	SLONG						npc_no;
		
	memcpy(&GodRequestMoveFast, packet->data.cBuf, sizeof(TPOS_GOD_REQUESTMOVEFAST));

	LOCK_CHARACTER(0);
	npc_no = FindCharacterByMainName(cn->User.cId);
	UNLOCK_CHARACTER(0);
	if(npc_no >= 0)
	{
		LOCK_CHARACTER(0);
		SetCharacterMoveSpeed(npc_no, GodRequestMoveFast.MoveSpeed);
		UNLOCK_CHARACTER(0);

		send_packet.Header.dwType = SET_NPC_MOVESPEED;
		send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_SETNPCMOVESPEED);
		EventSetNpcMoveSpeed.MoveSpeed = GodRequestMoveFast.MoveSpeed;
		EventSetNpcMoveSpeed.Npc_No = npc_no;
		memcpy(send_packet.data.cBuf, &EventSetNpcMoveSpeed, sizeof(TPOS_EVENT_SETNPCMOVESPEED));

		server_send_packet_to_all(&send_packet);
	}
}
// -----------------------------------------------------------------------------
void	ServerDoGodRequestSuperMan(TPOS_CN *cn, TPOS_PACKET *packet)
{
}
// -----------------------------------------------------------------------------
void	ServerDoGodRequestDead(TPOS_CN *cn, TPOS_PACKET *packet)
{
}
// -----------------------------------------------------------------------------
void	ServerDoGodRequestChangeZone(TPOS_CN *cn, TPOS_PACKET *packet)
{
}
// -----------------------------------------------------------------------------
void	ServerDoGodRequestGetMap(TPOS_CN *cn, TPOS_PACKET *packet)
{
	TPOS_GOD_REQUESTGETMAP	GodRequestGetMap;
	TPOS_PACKET				send_packet;
	SLONG					npc_no;
	int						t;	
	TPOS_ITEM				Item;
	
	memcpy(&GodRequestGetMap, packet->data.cBuf, sizeof(TPOS_GOD_REQUESTGETMAP));
	memset(&Item, 0x0, sizeof(TPOS_ITEM));
	
	SetItemBaseID(&Item, 300);
	SetItemHp(&Item, 100);		
	SetTreasureMapItemIndex(&Item, (UCHAR)GodRequestGetMap.Index);
	SetTreasureMapItemWholePieces(&Item, GetTreasuryMapPartNo((ULONG)GodRequestGetMap.Index));
	SetTreasureMapItemCurrentPieces(&Item, GodRequestGetMap.PieceIndex);

	LOCK_CHARACTER(0);
	npc_no = FindCharacterByMainName(cn->User.cId);
	UNLOCK_CHARACTER(0);
	if(npc_no >= 0)
	{
		// 包包是否有空位 , 有的話放進去
		t = ServerDoFindBagSpace(npc_no);
		if(t != -1)
		{
			LOCK_CHARACTER(0);
			SetCharacterBagItem(npc_no, t, &Item);
			UNLOCK_CHARACTER(0);
			TPOS_EVENT_NOTIFYSETBAGITEM	EventNotifySetBagItem;				
			
			send_packet.Header.dwType = NOTIFY_SET_BAG_ITEM;
			send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYSETBAGITEM);
			EventNotifySetBagItem.Item = Item;
			EventNotifySetBagItem.BagIndex = t;
			memcpy(send_packet.data.cBuf, &EventNotifySetBagItem, sizeof(TPOS_EVENT_NOTIFYSETBAGITEM));
			server_send_packet_to_one(cn, &send_packet);
		}					
	}
}
// -----------------------------------------------------------------------------
void	ServerDoGodRequestPropertyPoint(TPOS_CN *cn, TPOS_PACKET *packet)
{
	TPOS_GOD_REQUESTPROPERTYPOINT		GodRequestPropertyPoint;
	TPOS_GOD_NOTIFYPROPERTYPOINT		GodNotifyPropertyPoint;
	TPOS_PACKET							send_packet;	
	SLONG								npc_no;

	memcpy(&GodRequestPropertyPoint, packet->data.cBuf, sizeof(TPOS_GOD_REQUESTPROPERTYPOINT));

	LOCK_CHARACTER(0);
	npc_no = FindCharacterByMainName(cn->User.cId);
	UNLOCK_CHARACTER(0);
	if(npc_no >= 0)
	{
		LOCK_CHARACTER(0);
		SetCharacterPropertyPoint(npc_no, (UHINT)GodRequestPropertyPoint.Point);
		UNLOCK_CHARACTER(0);
		
		send_packet.Header.dwType = GOD_NOTIFY_PROPERTYPOINT;
		send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_GOD_NOTIFYPROPERTYPOINT);
		GodNotifyPropertyPoint.Point = GodRequestPropertyPoint.Point;
		memcpy(send_packet.data.cBuf, &GodNotifyPropertyPoint, sizeof(TPOS_GOD_NOTIFYPROPERTYPOINT));

		server_send_packet_to_player(npc_no, &send_packet);
	}
}
// -----------------------------------------------------------------------------
void	ServerDoRequestBuyItem(TPOS_CN *cn, TPOS_PACKET *packet)
{
	TPOS_PACKET					send_packet;
	TPOS_EVENT_REQUESTBUYITEM	EventRequestBuyItem;
	SLONG						npc_no;
	TPOS_ITEM					OnMouseItem;
	TPOS_STORE_ITEM				StoreItem;
	ULONG						money;	
	SLONG						buy;	
	
	memcpy(&EventRequestBuyItem, packet->data.cBuf, sizeof(TPOS_EVENT_REQUESTBUYITEM));
	
	buy = FALSE;	
	LOCK_CHARACTER(0);
	npc_no = FindCharacterByMainName(cn->User.cId);
	UNLOCK_CHARACTER(0);
	if(npc_no >= 0)
	{
		LOCK_CHARACTER(0);
		GetCharacterOnMouseItem(npc_no, &OnMouseItem);
		money = GetCharacterBodyMoney(npc_no);
		UNLOCK_CHARACTER(0);
		// Buy
		if(IsItemNone(&OnMouseItem) == TRUE)
		{
			GetZoneStoreItem(EventRequestBuyItem.ZoneStoreIndex, EventRequestBuyItem.ItemIndex, &StoreItem);
			if(StoreItem.Count > 0)
			{			
				if(money > StoreItem.Price)
				{
					money -= StoreItem.Price;
					OnMouseItem = StoreItem.Item;
					StoreItem.Count --;
					SetZoneStoreItem(EventRequestBuyItem.ZoneStoreIndex, EventRequestBuyItem.ItemIndex, &StoreItem);
					LOCK_CHARACTER(0);
					SetCharacterOnMouseItem(npc_no, &OnMouseItem);
					SetCharacterBodyMoney(npc_no, money);
					UNLOCK_CHARACTER(0);
					buy = TRUE;
				}
			}
		}		
		if(buy == TRUE)
		{
			// 傳送商店的變化
			TPOS_EVENT_REFRESHSTOREDATA	EventRefreshStoreData;
			TPOS_STORE_ITEM				item;
			int							i;
			memset(&EventRefreshStoreData, 0x0, sizeof(TPOS_EVENT_REFRESHSTOREDATA));
			
			for(i = 0;i < MAX_STORE_ITEMS;i++)
			{
				GetZoneStoreItem(EventRequestBuyItem.ZoneStoreIndex, i, &item);		
				EventRefreshStoreData.Item[i] = item.Item;
				EventRefreshStoreData.Amount[i] = item.Count;
				EventRefreshStoreData.Money[i] = item.Price;
			}				
			
			send_packet.Header.dwType = REFRESH_STORE_DATA;
			send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_REFRESHSTOREDATA);
			memcpy(send_packet.data.cBuf, &EventRefreshStoreData, sizeof(TPOS_EVENT_REFRESHSTOREDATA));
			
			server_send_packet_to_player(npc_no, &send_packet);
			// 傳送金錢的變化
			TPOS_EVENT_SETMONEY	EventSetMoney;
			send_packet.Header.dwType = SET_MONEY;
			send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_SETMONEY);
			EventSetMoney.Money = money;
			memcpy(send_packet.data.cBuf, &EventSetMoney, sizeof(TPOS_EVENT_SETMONEY));
			server_send_packet_to_player(npc_no, &send_packet);
			// 傳送物品
			TPOS_EVENT_NOTIFYSETONMOUSEITEM	EventNotifySetOnMouseItem;
			send_packet.Header.dwType = NOTIFY_SET_ONMOUSE_ITEM;
			send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYSETONMOUSEITEM);
			EventNotifySetOnMouseItem.Item = OnMouseItem;
			memcpy(send_packet.data.cBuf, &EventNotifySetOnMouseItem, sizeof(TPOS_EVENT_NOTIFYSETONMOUSEITEM));
			server_send_packet_to_player(npc_no, &send_packet);			
		}		
	}
}
// -----------------------------------------------------------------------------
void	ServerDoRequestSellItem(TPOS_CN *cn, TPOS_PACKET *packet)
{
	TPOS_PACKET					send_packet;
	TPOS_EVENT_REQUESTSELLITEM	EventRequestSellItem;
	SLONG						npc_no;
	TPOS_ITEM					OnMouseItem;	
	ULONG						money;
	ULONG						sellprice;	
	SLONG						sell;
	
	memcpy(&EventRequestSellItem, packet->data.cBuf, sizeof(TPOS_EVENT_REQUESTSELLITEM));
		
	sell = FALSE;
	LOCK_CHARACTER(0);
	npc_no = FindCharacterByMainName(cn->User.cId);
	UNLOCK_CHARACTER(0);
	if(npc_no >= 0)
	{
		LOCK_CHARACTER(0);
		GetCharacterOnMouseItem(npc_no, &OnMouseItem);
		money = GetCharacterBodyMoney(npc_no);
		UNLOCK_CHARACTER(0);
		if(IsItemNone(&OnMouseItem) == FALSE)
		{
			// Sell		
			sellprice = ComputeItemSellPrice(&OnMouseItem);
			money += sellprice;
			SetItemNone(&OnMouseItem);
			LOCK_CHARACTER(0);
			SetCharacterOnMouseItem(npc_no, &OnMouseItem);
			SetCharacterBodyMoney(npc_no, money);
			UNLOCK_CHARACTER(0);
			sell = TRUE;
		}
		if(sell == TRUE)
		{			
			// 傳送金錢的變化
			TPOS_EVENT_SETMONEY	EventSetMoney;
			send_packet.Header.dwType = SET_MONEY;
			send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_SETMONEY);
			EventSetMoney.Money = money;
			memcpy(send_packet.data.cBuf, &EventSetMoney, sizeof(TPOS_EVENT_SETMONEY));
			server_send_packet_to_player(npc_no, &send_packet);
			// 傳送物品
			TPOS_EVENT_NOTIFYSETONMOUSEITEM	EventNotifySetOnMouseItem;
			send_packet.Header.dwType = NOTIFY_SET_ONMOUSE_ITEM;
			send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYSETONMOUSEITEM);
			EventNotifySetOnMouseItem.Item = OnMouseItem;
			memcpy(send_packet.data.cBuf, &EventNotifySetOnMouseItem, sizeof(TPOS_EVENT_NOTIFYSETONMOUSEITEM));
			server_send_packet_to_player(npc_no, &send_packet);			
		}
	}
}
// -----------------------------------------------------------------------------
void	ServerDoRequestJoinTeam(TPOS_CN *cn, TPOS_PACKET *packet)
{
	TPOS_EVENT_REQUESTJOINTEAM				EventRequestJoinTeam;		
	TPOS_PACKET		send_packet;
	ULONG			leader_npc_no, member_npc_no;		
	SLONG			temp_npc_no;
	char			temp_mainname[32];
	char			leader_mainname[32];	
	char			member_mainname[32];
	char			leader_zonename[32];
	char			member_zonename[32];
	SLONG			leader_at_other_zone;

	memcpy(&EventRequestJoinTeam, packet->data.cBuf, sizeof(TPOS_EVENT_REQUESTJOINTEAM));
	
	leader_at_other_zone = FALSE;
	strcpy(temp_mainname, EventRequestJoinTeam.LeaderMainName);
	strcpy(member_mainname, cn->User.cId);
	LOCK_CHARACTER(0);
	member_npc_no = FindCharacterByMainName(member_mainname);
	temp_npc_no = FindCharacterByMainName(temp_mainname);		
	strcpy(leader_mainname, GetCharacterTeamMemberMainName(temp_npc_no, 0));
	if(strcmp(leader_mainname, "") == 0)
	{
		strcpy(leader_mainname, EventRequestJoinTeam.LeaderMainName);
	}
	leader_npc_no = FindCharacterByMainName(leader_mainname);
	if(leader_npc_no == -1)
	{
		leader_at_other_zone = TRUE;
	}else
	{		
		strcpy(leader_zonename, ZoneName);				
	}	
	strcpy(member_zonename, ZoneName);	
	UNLOCK_CHARACTER(0);	

	// 已經在別的隊伍
	if(ServerCheckIsInTeam(member_npc_no) == TRUE)
	{			
		send_packet.Header.dwType = NOTIFY_ALREADY_IN_TEAM;
		send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER);
		
		server_send_packet_to_one(cn, &send_packet);
		return;
	}
	// 隊長在同區域
	if(leader_at_other_zone == FALSE)
	{			
		if(ServerCheckTeamIsFull(leader_npc_no) == TRUE)
		{	
			// 隊伍已滿
			ServerDoSendTeamFull(cn, leader_npc_no);			
			return;
		}
		// 發送加入隊伍請求給隊長		
		ServerDoSendSomeoneWantJoinTeam(leader_mainname, member_mainname, member_zonename);		
	}else
	// 隊長在不同區域
	{
		TPOS_EVENT_ZONEREQUESTJOINTEAM	EventZoneRequestJoinTeam;

		strcpy(EventZoneRequestJoinTeam.LeaderMainName, leader_mainname); 
		strcpy(EventZoneRequestJoinTeam.LeaderZoneName, leader_zonename); 
		strcpy(EventZoneRequestJoinTeam.MemberMainName, member_mainname); 
		strcpy(EventZoneRequestJoinTeam.MemberZoneName, ZoneName); 
		send_packet.Header.dwType = ZONE_REQUEST_JOIN_TEAM;
		send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_ZONEREQUESTJOINTEAM);
		memcpy(send_packet.data.cBuf, &EventZoneRequestJoinTeam, sizeof(TPOS_EVENT_ZONEREQUESTJOINTEAM));

		server_send_packet_to_one(&World, &send_packet);
	}
}
// -----------------------------------------------------------------------------
void	ServerDoReequestAgreeJoinTeam(TPOS_CN *cn, TPOS_PACKET *packet)
{
	TPOS_EVENT_REQUESTAGREEJOINTEAM		EventRequestAgreeJoinTeam;		
	ULONG			leader_npc_no, member_npc_no;		
	char			leader_mainname[32];
	char			member_mainname[32];
	char			member_zonename[32];		
	SLONG			member_at_other_zone;
	
	member_at_other_zone = FALSE;
	memcpy(&EventRequestAgreeJoinTeam, packet->data.cBuf, sizeof(TPOS_EVENT_REQUESTAGREEJOINTEAM));

	strcpy(member_mainname, EventRequestAgreeJoinTeam.MemberMainName);
	strcpy(member_zonename, EventRequestAgreeJoinTeam.MemberZoneName);
	strcpy(leader_mainname, cn->User.cId);	
	LOCK_CHARACTER(0);
	leader_npc_no = FindCharacterByMainName(leader_mainname);
	member_npc_no = FindCharacterByMainName(member_mainname);
	UNLOCK_CHARACTER(0);
	if(ServerCheckSomeoneIsInTeam(leader_npc_no, member_mainname) == TRUE)return;
	// 檢查加入隊友是否在同區域
	if(strcmp(member_zonename, ZoneName) != 0)
	{
		member_at_other_zone = TRUE;		
	}
	// 加入隊友在同區域
	if(member_at_other_zone == FALSE)
	{		
		if(ServerCheckIsInTeam(leader_npc_no) == FALSE)
		{
			ServerDoSendMakeTeam(leader_npc_no, member_npc_no);
		}else
		{
			ServerDoSendSomeoneJoinTeam(leader_npc_no, member_npc_no);
		}							
	}else
	// 加入隊友在不同區域
	{

	}
}
// -----------------------------------------------------------------------------
void	ServerDoRequestExitTeam(TPOS_CN *cn, TPOS_PACKET *packet)
{
	TPOS_EVENT_REQUESTEXITTEAM	EventRequestExitTeam;	
	ULONG			leader_npc_no, member_npc_no;		
	char			leader_mainname[32];
	char			member_mainname[32];	
	int				leader_exit;
	SLONG			member_number;
		
	leader_exit = FALSE;
	memcpy(&EventRequestExitTeam, packet->data.cBuf, sizeof(TPOS_EVENT_REQUESTEXITTEAM));

	strcpy(leader_mainname, EventRequestExitTeam.LeaderMainName);
	strcpy(member_mainname, cn->User.cId);

	LOCK_CHARACTER(0);
	member_npc_no = FindCharacterByMainName(member_mainname);		
	leader_npc_no = FindCharacterByMainName(leader_mainname);
	UNLOCK_CHARACTER(0);	

	if(strcmp(leader_mainname, member_mainname) == 0)leader_exit = TRUE;
	member_number = ServerCheckTeamMemberNumber(leader_npc_no);

	if(leader_exit == FALSE)
	{		
		if(member_number == 2)
		{
			ServerDoSendKillTeam(leader_npc_no);
		}
		if(member_number > 2)
		{
			ServerDoSendSomeoneExitTeam(leader_npc_no, leader_mainname, member_mainname);
		}	
	}
	if(leader_exit == TRUE)
	{
		if(member_number == 2)
		{
			ServerDoSendKillTeam(leader_npc_no);
		}
		if(member_number > 2)
		{
			ServerDoSendChangeLeader(leader_npc_no);
		}		
	}
}
// -----------------------------------------------------------------------------
void	ServerDoRequestKickTeamMember(TPOS_CN *cn, TPOS_PACKET *packet)
{
	TPOS_EVENT_REQUESTKICKMEMBER		EventRequestKickMember;
	TPOS_EVENT_NOTIFYSOMEONEEXITTEAM	EventNotifySomeoneExitTeam;
	TPOS_PACKET		send_packet;
	ULONG			leader_npc_no, member_npc_no;		
	char			leader_mainname[32];
	char			member_mainname[32];
	int				i;	
	char			tempmainname[32];
	int				index;	
	
	memcpy(&EventRequestKickMember, packet->data.cBuf, sizeof(TPOS_EVENT_REQUESTKICKMEMBER));

	strcpy(member_mainname, EventRequestKickMember.MemberMainName);
	strcpy(leader_mainname, cn->User.cId);
	LOCK_CHARACTER(0);
	member_npc_no = FindCharacterByMainName(member_mainname);		
	leader_npc_no = FindCharacterByMainName(leader_mainname);
	for(i = 0;i < 7;i++)
	{
		if(strcmp(GetCharacterTeamMemberMainName(leader_npc_no, i), member_mainname) == 0)
		{
			SetCharacterTeamMemberMainName(leader_npc_no, i, "");			
			SetCharacterTeamMemberHp(leader_npc_no, i, 0);
			SetCharacterTeamMemberMaxHp(leader_npc_no, i, 0);
			SetCharacterTeamMemberEyes(leader_npc_no, i, 0);
			SetCharacterTeamMemberMouth(leader_npc_no, i, 0);			
			SetCharacterTeamMemberLevel(leader_npc_no, i, 0);
			SetCharacterTeamMemberCareer(leader_npc_no, i, 0);
			SetCharacterTeamMemberSex(leader_npc_no, i, 0);			
			SetCharacterTeamMemberZoneName(leader_npc_no, i, 0);
			break;
		}
	}
	UNLOCK_CHARACTER(0);
	send_packet.Header.dwType = NOTIFY_SOMEONE_EXIT_TEAM;
	send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYSOMEONEEXITTEAM);
	strcpy(EventNotifySomeoneExitTeam.MemberMainName, member_mainname);
	memcpy(send_packet.data.cBuf, &EventNotifySomeoneExitTeam, sizeof(TPOS_EVENT_NOTIFYSOMEONEEXITTEAM));
	// 給隊長
	server_send_packet_to_one(cn, &send_packet);	
	// 給隊友
	for(i = 0;i < 7;i++)
	{
		LOCK_CHARACTER(0);
		strcpy(tempmainname, GetCharacterTeamMemberMainName(leader_npc_no, i));
		UNLOCK_CHARACTER(0);
		if(strcmp(tempmainname, "") != 0)
		{			
			LOCK_CONNECTION(0);
			index = FindConnectionByName(tempmainname);
			UNLOCK_CONNECTION(0);			
			if(index >= 0 && index < 500)
			{
				server_send_packet_to_one(&Pos_Cn[index], &send_packet);
			}
		}			
	}
}
// -----------------------------------------------------------------------------
void	ServerDoZoneRequestJoinTeam(TPOS_CN *cn, TPOS_PACKET *packet)
{
	TPOS_EVENT_ZONEREQUESTJOINTEAM			EventZoneRequestJoinTeam;	
	TPOS_EVENT_ZONENOTIFYJOINTEAMFULL		EventZoneNotifyJoinTeamFull;
	TPOS_EVENT_NOTIFYSOMEONEWANTJOINTEAM	EventNotifySomeoneWantJoinTeam;
	TPOS_PACKET		send_packet;
	ULONG			leader_npc_no;		
	char			leader_mainname[32];
	char			temp_mainname[32];
	SLONG			temp_npc_no;
	char			member_mainname[32];
	char			leader_zonename[32];
	char			member_zonename[32];
	int				cn_index;
	int				i;	
	SLONG			team_full;
	SLONG			leader_at_other_zone;

	memcpy(&EventZoneRequestJoinTeam, packet->data.cBuf, sizeof(TPOS_EVENT_ZONEREQUESTJOINTEAM));

	team_full = TRUE;	
	leader_at_other_zone = FALSE;

	strcpy(temp_mainname, EventZoneRequestJoinTeam.LeaderMainName);
	strcpy(leader_zonename, EventZoneRequestJoinTeam.LeaderZoneName);
	strcpy(member_mainname, EventZoneRequestJoinTeam.MemberMainName);
	strcpy(member_zonename, EventZoneRequestJoinTeam.MemberZoneName);	
	
	LOCK_CHARACTER(0);
	temp_npc_no = FindCharacterByMainName(temp_mainname);			
	strcpy(leader_mainname, GetCharacterTeamMemberMainName(temp_npc_no, 0));
	if(strcmp(leader_mainname, "") == 0)
	{
		strcpy(leader_mainname, EventZoneRequestJoinTeam.LeaderMainName);
	}
	leader_npc_no = FindCharacterByMainName(leader_mainname);	
	if(leader_npc_no == -1)leader_at_other_zone = TRUE;
	UNLOCK_CHARACTER(0);	
	
	// 隊長在同區域
	if(leader_at_other_zone == FALSE)
	{	
		LOCK_CHARACTER(0);
		for(i = 1;i < 8;i++)
		{
			if(strcmp(GetCharacterTeamMemberMainName(leader_npc_no, i), "") == 0)
			{
				team_full = FALSE;
			}
		}		
		UNLOCK_CHARACTER(0);				
		if(team_full == TRUE)
		{	
			// 隊伍已滿
			send_packet.Header.dwType = ZONE_NOTIFY_JOIN_TEAM_FULL;
			send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_ZONENOTIFYJOINTEAMFULL);			
			strcpy(EventZoneNotifyJoinTeamFull.MemberMainName, member_mainname);
			strcpy(EventZoneNotifyJoinTeamFull.MemberZoneName, member_zonename);
			memcpy(send_packet.data.cBuf, &EventZoneNotifyJoinTeamFull, sizeof(TPOS_EVENT_ZONENOTIFYJOINTEAMFULL));
			server_send_packet_to_one(&World, &send_packet);
			return;
		}
		// 發送加入隊伍請求給隊長		
		strcpy(EventNotifySomeoneWantJoinTeam.MemberMainName, member_mainname);
		strcpy(EventNotifySomeoneWantJoinTeam.MemberZoneName, member_zonename);
		send_packet.Header.dwType = NOTIFY_SOMEONE_WANT_JOIN_TEAM;
		send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYSOMEONEWANTJOINTEAM);
		memcpy(send_packet.data.cBuf, &EventNotifySomeoneWantJoinTeam, sizeof(TPOS_EVENT_NOTIFYSOMEONEWANTJOINTEAM));
		LOCK_CONNECTION(0);
		cn_index = FindConnectionByName(leader_mainname);
		UNLOCK_CONNECTION(0);
		if(cn_index >= 0)
		{
			server_send_packet_to_one(&Pos_Cn[cn_index], &send_packet);
		}	
	}else
	// 隊長在不同區域
	{
		TPOS_EVENT_ZONEREQUESTJOINTEAM	EventZoneRequestJoinTeam;
		strcpy(EventZoneRequestJoinTeam.LeaderMainName, leader_mainname); 
		strcpy(EventZoneRequestJoinTeam.LeaderMainName, leader_zonename); 
		strcpy(EventZoneRequestJoinTeam.MemberMainName, member_mainname); 
		strcpy(EventZoneRequestJoinTeam.MemberZoneName, member_zonename); 
		send_packet.Header.dwType = ZONE_REQUEST_JOIN_TEAM;
		send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_ZONEREQUESTJOINTEAM);
		memcpy(send_packet.data.cBuf, &EventZoneRequestJoinTeam, sizeof(TPOS_EVENT_ZONEREQUESTJOINTEAM));

		server_send_packet_to_one(&World, &send_packet);
	}
}
// -----------------------------------------------------------------------------
void	ServerDoZoneRequestAgreeJoinTeam(TPOS_CN *cn, TPOS_PACKET *packet)
{
}
// -----------------------------------------------------------------------------
void	ServerDoZoneRequestExitTeam(TPOS_CN *cn, TPOS_PACKET *packet)
{
}
// -----------------------------------------------------------------------------
void	ServerDoZoneRequestKickTeamMember(TPOS_CN *cn, TPOS_PACKET *packet)
{
}
// -----------------------------------------------------------------------------
void	ServerDoZoneNotifyJoinTeamFull(TPOS_CN *cn, TPOS_PACKET *packet)
{
	TPOS_EVENT_ZONENOTIFYJOINTEAMFULL		EventZoneNotifyJoinTeamFull;
	TPOS_PACKET		send_packet;	
	char			member_mainname[32];		
	int				cn_index;
	//int				i;		

	memcpy(&EventZoneNotifyJoinTeamFull, packet->data.cBuf, sizeof(TPOS_EVENT_ZONENOTIFYJOINTEAMFULL));
	strcpy(member_mainname, EventZoneNotifyJoinTeamFull.MemberMainName);
	LOCK_CONNECTION(0);
	cn_index = FindConnectionByName(member_mainname);
	UNLOCK_CONNECTION(0);
	if(cn_index >= 0)
	{
		send_packet.Header.dwType = NOTIFY_JOIN_TEAM_FULL;
		send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER);		
		server_send_packet_to_one(&Pos_Cn[cn_index], &send_packet);
	}	
}
// -----------------------------------------------------------------------------
void	ServerDoRequestSaveMoney(TPOS_CN *cn, TPOS_PACKET *packet)
{
	TPOS_EVENT_REQUESTSAVEMONEY		EventRequestSaveMoney;
	TPOS_EVENT_SETMONEY				EventSetMoney;
	TPOS_EVENT_SETBANKMONEY			EventSetBankMoney;
	TPOS_PACKET						send_packet;
	char							mainname[32];
	int								index;
	ULONG							bank_money,body_money;
	
	memcpy(&EventRequestSaveMoney, packet->data.cBuf, sizeof(TPOS_EVENT_REQUESTSAVEMONEY));

	strcpy(mainname, cn->User.cId);
	LOCK_CHARACTER(0);
	index = FindCharacterByMainName(mainname);
	UNLOCK_CHARACTER(0);
	if(index != -1)
	{
		LOCK_CHARACTER(0);
		body_money = GetCharacterBodyMoney(index);
		bank_money = GetCharacterBankMoney(index);
		body_money -= EventRequestSaveMoney.Money;
		bank_money += EventRequestSaveMoney.Money;
		SetCharacterBodyMoney(index, body_money);
		SetCharacterBankMoney(index, bank_money);
		UNLOCK_CHARACTER(0);
		
		EventSetMoney.Money = body_money;
		
		send_packet.Header.dwType = SET_MONEY;
		send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_SETMONEY);
		memcpy(send_packet.data.cBuf, &EventSetMoney, sizeof(TPOS_EVENT_SETMONEY));

		server_send_packet_to_one(cn, &send_packet);

		EventSetBankMoney.Money = bank_money;

		send_packet.Header.dwType = SET_BANK_MONEY;
		send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_SETBANKMONEY);
		memcpy(send_packet.data.cBuf, &EventSetBankMoney, sizeof(TPOS_EVENT_SETBANKMONEY));

		server_send_packet_to_one(cn, &send_packet);
	}	
}
// -----------------------------------------------------------------------------
void	ServerDoRequestLoadMoney(TPOS_CN *cn, TPOS_PACKET *packet)
{
	TPOS_EVENT_REQUESTLOADMONEY		EventRequestLoadMoney;
	TPOS_EVENT_SETMONEY				EventSetMoney;
	TPOS_EVENT_SETBANKMONEY			EventSetBankMoney;
	TPOS_PACKET						send_packet;
	char							mainname[32];
	int								index;
	ULONG							bank_money;
	ULONG							body_money;

	memcpy(&EventRequestLoadMoney, packet->data.cBuf, sizeof(TPOS_EVENT_REQUESTLOADMONEY));

	strcpy(mainname, cn->User.cId);
	LOCK_CHARACTER(0);
	index = FindCharacterByMainName(mainname);
	UNLOCK_CHARACTER(0);
	if(index != -1)
	{
		LOCK_CHARACTER(0);
		bank_money = GetCharacterBankMoney(index);
		body_money = GetCharacterBodyMoney(index);
		UNLOCK_CHARACTER(0);
		bank_money -= EventRequestLoadMoney.Money;
		body_money += EventRequestLoadMoney.Money;
		if(bank_money >= 0)
		{
			LOCK_CHARACTER(0);
			SetCharacterBankMoney(index, bank_money);
			SetCharacterBodyMoney(index, body_money);
			UNLOCK_CHARACTER(0);

			EventSetMoney.Money = body_money;		

			send_packet.Header.dwType = SET_MONEY;
			send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_SETMONEY);
			memcpy(send_packet.data.cBuf, &EventSetMoney, sizeof(TPOS_EVENT_SETMONEY));

			server_send_packet_to_one(cn, &send_packet);

			EventSetBankMoney.Money = bank_money;		

			send_packet.Header.dwType = SET_BANK_MONEY;
			send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_SETBANKMONEY);
			memcpy(send_packet.data.cBuf, &EventSetBankMoney, sizeof(TPOS_EVENT_SETBANKMONEY));

			server_send_packet_to_one(cn, &send_packet);
		}else
		{
			send_packet.Header.dwType = NOTIFY_MONEY_NOT_ENOUGH;
			send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER);	

			server_send_packet_to_one(cn, &send_packet);
		}
	}	
}
// -----------------------------------------------------------------------------
void	ServerDoRequestHitBankItem(TPOS_CN *cn, TPOS_PACKET *packet)
{
	SLONG							npc_no;
	TPOS_PACKET						send_packet;
	TPOS_ITEM						OnMouseItem;
	TPOS_ITEM						DestItem;	
	TPOS_EVENT_NOTIFYSETONMOUSEITEM	EventNotifySetOnMouseItem;
	TPOS_EVENT_NOTIFYSETBANKITEM	EventNotifySetBankItem;
	TPOS_EVENT_REQUESTHITBANKITEM	EventRequestHitBankItem;
	SLONG							index;

	memcpy(&EventRequestHitBankItem, packet->data.cBuf, sizeof(TPOS_EVENT_REQUESTHITBANKITEM));

	index = (SLONG)EventRequestHitBankItem.Index;
	LOCK_CHARACTER(0);
	npc_no = FindCharacterByMainName(cn->User.cId);
	UNLOCK_CHARACTER(0);
	if(npc_no != -1)
	{
		LOCK_CHARACTER(0);
		GetCharacterOnMouseItem(npc_no, &OnMouseItem);
		GetCharacterBankItem(npc_no, index, &DestItem);									
		SetCharacterBankItem(npc_no, index, &OnMouseItem);			
		SetCharacterOnMouseItem(npc_no, &DestItem);
		UNLOCK_CHARACTER(0);	
		
		// 送出滑鼠物品的信息
		send_packet.Header.dwType = NOTIFY_SET_ONMOUSE_ITEM;
		send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYSETONMOUSEITEM);
		EventNotifySetOnMouseItem.Item = DestItem;
		memcpy(send_packet.data.cBuf, &EventNotifySetOnMouseItem, sizeof(TPOS_EVENT_NOTIFYSETONMOUSEITEM));
		server_send_packet_to_one(cn, &send_packet);
		// 送出銀行物品的信息
		send_packet.Header.dwType = NOTIFY_SET_BANK_ITEM;
		send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYSETBANKITEM);	
		EventNotifySetBankItem.Index = (UHINT)index;
		EventNotifySetBankItem.Item = OnMouseItem;
		memcpy(send_packet.data.cBuf, &EventNotifySetBankItem, sizeof(TPOS_EVENT_NOTIFYSETBANKITEM));
		server_send_packet_to_one(cn, &send_packet);
	}
}
// -----------------------------------------------------------------------------
void	ServerDoRequestSeparateMap(TPOS_CN *cn, TPOS_PACKET *packet)
{
	SLONG							npc_no;
	SLONG							separate_ok;
	TPOS_ITEM						Item;
	TPOS_EVENT_REQUESTSEPARATEMAP	EventRequestSeparateMap;

	memcpy(&EventRequestSeparateMap, packet->data.cBuf, sizeof(TPOS_EVENT_REQUESTSEPARATEMAP));
	LOCK_CHARACTER(0);
	npc_no = FindCharacterByMainName(cn->User.cId);
	if(EventRequestSeparateMap.BagIndex == 255)
	{
		GetCharacterTreasureItem(npc_no, &Item);
	}else
	{
		GetCharacterBagItem(npc_no, EventRequestSeparateMap.BagIndex, &Item);
	}	
	UNLOCK_CHARACTER(0);
	separate_ok = ServerDoSeparateMap(npc_no, &Item);		
	if(separate_ok == TRUE)
	{
		TPOS_EVENT_NOTIFYSETBAGITEM	EventNotifySetBagItem;
		TPOS_PACKET					send_packet;

		// 清空原來的地圖
		SetItemNone(&Item);
		LOCK_CHARACTER(0);
		SetCharacterBagItem(npc_no, EventRequestSeparateMap.BagIndex, &Item);
		UNLOCK_CHARACTER(0);		

		send_packet.Header.dwType = NOTIFY_SET_BAG_ITEM;
		send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYSETBAGITEM);		
		EventNotifySetBagItem.BagIndex = (UCHAR)EventRequestSeparateMap.BagIndex;
		EventNotifySetBagItem.Item = Item;
		memcpy(send_packet.data.cBuf, &EventNotifySetBagItem, sizeof(TPOS_EVENT_NOTIFYSETBAGITEM));

		server_send_packet_to_one(cn, &send_packet);
	}
}
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

