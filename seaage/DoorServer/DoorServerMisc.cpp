//-------------------------------------------------------------------------------
// Psalm of Sea DoorServer ListView
// By Hawke Hsieh
// 2002-10-7
//-------------------------------------------------------------------------------

#include "DoorServer_Def.h"

//-------------------------------------------------------------------------------
int     FindUsableWorldInfo(void)
{
	int i;
    
    for(i=0; i<MAX_WORLD_PER_DOOR; i++)
    {
        if(WorldInfo[i].dwIndex ==0)
        {
            return(i);
        }
    }
    return  -1;
}
//-------------------------------------------------------------------------------
int     FindWorldInfoByName(char *name)
{
	int i;

    for(i=0; i<MAX_WORLD_PER_DOOR; i++)
    {
        if(strcmp(WorldInfo[i].cName, name) ==0)
        {
            return(i);
        }
    }
    return  -1;
}
//-------------------------------------------------------------------------------
void ChangeWorldStateToDisable()
{
	int i;
	char str[256];
	DWORD tmpcount;
	DWORD tmpactive;
	
	i = GetSelectLVItem(hListViewWnd);	
	SetLVItem(hListViewWnd, i, 4, "Disabled");
	GetOneLVItem(hListViewWnd, str, i, 0, 50);

	LOCK_WORLDINFO(0);
	i = FindWorldInfoByName(str);
	WorldInfo[i].dwActive = 0;
	tmpcount = WorldInfo[i].dwPlayerCount;
	tmpactive = WorldInfo[i].dwActive;
	UNLOCK_WORLDINFO(0);
	SendWorldRefreshInfoToAll(str, tmpcount, tmpactive);	
}
//-------------------------------------------------------------------------------
void ChangeWorldStateToEnable()
{
	int i;
	char str[56];
	DWORD tmpcount;
	DWORD tmpactive;
	
	i = GetSelectLVItem(hListViewWnd);	
	SetLVItem(hListViewWnd, i, 4, "Enabled");
	GetOneLVItem(hListViewWnd, str, i, 0, 50);

	LOCK_WORLDINFO(0);
	i = FindWorldInfoByName(str);
	WorldInfo[i].dwActive = 1;
	tmpcount = WorldInfo[i].dwPlayerCount;
	tmpactive = WorldInfo[i].dwActive;
	UNLOCK_WORLDINFO(0);
	SendWorldRefreshInfoToAll(str, tmpcount, tmpactive);
}
//-------------------------------------------------------------------------------
void	ServerDoPlayerLogin(TPOS_CN	*cn, TPOS_PACKET *recv_packet)
{
	int					cn_index;
	SLONG				dbRet;
	TPOS_EVENT_LOGIN	EventLogin;
	TPOS_PACKET			send_packet;
	TPOS_COMPACKET		send_compacket;
	int					i;
	
	memcpy(&EventLogin, recv_packet->data.cBuf, sizeof(TPOS_EVENT_LOGIN));
	
	LOCK_CONNECTION(0);
	cn_index = FindConnectionBySocket(cn->dwSocket);
	UNLOCK_CONNECTION(0);
	
	// 檢查是否註冊人員
	if(strcmp(EventLogin.cId, "guest")==0)
	{
		if(strcmp(EventLogin.cPw, "register")==0)
		{
			send_packet.Header.dwType = DOOR_LOGIN_OK;
			LOCK_CONNECTION(0);
			strcpy(Pos_Cn[cn_index].User.cId, "guest");
			strcpy(Pos_Cn[cn_index].User.cPw, "Register");                
			UNLOCK_CONNECTION(0);
			SaveWorkToLog("guest", inet_ntoa(cn->Addr.sin_addr), "GUEST_LOGIN_OK");
		}else
		{
			send_packet.Header.dwType = DOOR_LOGIN_ERRORID;
			SaveWorkToLog("guest", inet_ntoa(cn->Addr.sin_addr), "PLAYER_LOGIN_ERRORID");			
		}
	}
	else
	{
		// 檢查密碼和ID 
		dbRet = CheckPasswordOfAccountDB(EventLogin.cId, EventLogin.cPw);
		switch(dbRet)
		{
		case NETGE_DB_ERROR_ACCOUNT:
			send_packet.Header.dwType = DOOR_LOGIN_ERRORID;
			SaveWorkToLog(EventLogin.cId,
						  inet_ntoa(cn->Addr.sin_addr),
						  "PLAYER_LOGIN_ERRORID");
			break;
		case NETGE_DB_ERROR_PASSWORD:
			send_packet.Header.dwType = DOOR_LOGIN_ERRORPW;
			SaveWorkToLog(EventLogin.cId,
						  inet_ntoa(cn->Addr.sin_addr),
						  "PLAYER_LOGIN_ERRORPW");
			break;
		//case DOOR_LOGIN_DENIED:
		//	send_packet.Header.dwType = DOOR_LOGIN_DENIED;
		//	SaveWorkToLog(EventLogin.cId,
		//				  inet_ntoa(cn->Addr.sin_addr),
		//				  "PLAYER_LOGIN_DENIED");
		//	break;		
		case NETGE_DB_SUCCESS:
			LOCK_CONNECTION(0);
			i = FindConnectionByID(EventLogin.cId);
			UNLOCK_CONNECTION(0);
			if(i >= 0)
			{
				send_packet.Header.dwType = DOOR_LOGIN_REPEAT;
				SaveWorkToLog(EventLogin.cId,
							  inet_ntoa(cn->Addr.sin_addr),
						      "DOOR_LOGIN_REPEAT");			
			}else
			{
				LOCK_CONNECTION(0);
				strcpy(Pos_Cn[cn_index].User.cPw, EventLogin.cId);					
				strcpy(Pos_Cn[cn_index].User.cId, "Player");
				UNLOCK_CONNECTION(0);
				send_packet.Header.dwType = DOOR_LOGIN_OK;
				SaveWorkToLog(EventLogin.cId,
							  inet_ntoa(cn->Addr.sin_addr),
							  "PLAYER_LOGIN_OK");
			}			
			break;					
		}
	}		
	send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER);

	CompressPacket(&send_packet, &send_compacket);

	LOCK_CONNECTION(0);	
	QueuePacket(cn, &send_compacket);
	UNLOCK_CONNECTION(0);	   	
}
//-------------------------------------------------------------------------------
void	ServerDoRegisterAccountCheck(TPOS_CN *cn, TPOS_PACKET *packet)
{
	TPOS_EVENT_REGISTERACCOUNTCHECK	EventRegisterAccountCheck;
	TPOS_DB_ACCOUNT					DbAccount;	
	TPOS_PACKET						send_packet;
	TPOS_COMPACKET					send_compacket;
	DWORD							i = 0;
	int								x = 0;		
	SLONG							dbRet;
	
	memcpy(&EventRegisterAccountCheck, packet->data.cBuf, sizeof(TPOS_EVENT_REGISTERACCOUNTCHECK));

	SaveWorkToLog(EventRegisterAccountCheck.cId,
				  inet_ntoa(cn->Addr.sin_addr),
				  "REGISTER_ACCOUNT_CHECK");
		
	dbRet = CheckAccountOfAccountDB(EventRegisterAccountCheck.cId);
	switch(dbRet)
	{
	case NETGE_DB_ACCOUNT_EXIST:
		send_packet.Header.dwType = REGISTER_ACCOUNT_IDUSED;
		SaveWorkToLog(EventRegisterAccountCheck.cId, 
					  inet_ntoa(cn->Addr.sin_addr), 
			          "REGISTER_ACCOUNT_IDUSED");				
		break;				
	case NETGE_DB_ACCOUNT_AVAILABLE:
		LOCK_CONNECTION(0);
		x = FindConnectionBySocket(cn->dwSocket);				
		UNLOCK_CONNECTION(0);
		if(x >= 0 )
		{				
			LOCK_CONNECTION(0);
			strcpy(Pos_Cn[x].User.cId, EventRegisterAccountCheck.cId);
			UNLOCK_CONNECTION(0);
			memset(&DbAccount, 0x0, sizeof(DbAccount));
			strcpy(DbAccount.cId, EventRegisterAccountCheck.cId);
			strcpy(DbAccount.cPw, EventRegisterAccountCheck.cPw);
			if(AppendRecordToAccountDB(&DbAccount)==TRUE)
			{
				send_packet.Header.dwType = REGISTER_ACCOUNT_CHECK_OK;
				SaveWorkToLog(EventRegisterAccountCheck.cId, 
							  inet_ntoa(cn->Addr.sin_addr),
							  "REGISTER_ACCOUNT_CHECK_OK");
			}else
			{
				send_packet.Header.dwType = REGISTER_ACCOUNT_CHECK_FAIL;
				SaveWorkToLog(EventRegisterAccountCheck.cId,
							  inet_ntoa(cn->Addr.sin_addr),
							  "REGISTER_ACCOUNT_CHECK_FAIL");
			}
		}
		break;
	}
	send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER);
	send_packet.Header.dwVersion = CURRENT_VERSION;

	CompressPacket(&send_packet, &send_compacket);

	LOCK_CONNECTION(0);	
	QueuePacket(cn, &send_compacket);	
	UNLOCK_CONNECTION(0);
	
}
//-------------------------------------------------------------------------------
void	ServerDoRegisterAccountFinal(TPOS_CN *cn, TPOS_PACKET *packet)
{
	int							s;
	TPOS_EVENT_REGISTERACCOUNT	EventRegisterAccount;
	TPOS_DB_ACCOUNT				DbAccount;
	TPOS_PACKET					send_packet;
	TPOS_COMPACKET				send_compacket;
	
	memcpy(&EventRegisterAccount, packet->data.cBuf, sizeof(TPOS_EVENT_REGISTERACCOUNT));

	SaveWorkToLog(EventRegisterAccount.cId,
				  inet_ntoa(cn->Addr.sin_addr),
				  "REGISTER_ACCOUNT_FINAL");
				
	// 修改登入者的型態
	LOCK_CONNECTION(0);
	s = FindConnectionBySocket(cn->dwSocket);	
	UNLOCK_CONNECTION(0);
	if(s >= 0)
	{
		LOCK_CONNECTION(0);
		strcpy(Pos_Cn[s].User.cPw,"Player");
		UNLOCK_CONNECTION(0);			
		memcpy(&DbAccount, &EventRegisterAccount, sizeof(TPOS_EVENT_REGISTERACCOUNT));
		ConvertEventRegisterAccountToDbAccout(&EventRegisterAccount, &DbAccount);
		if(UpdateRecordOfAccountDB(&DbAccount)==TRUE)
		{
			send_packet.Header.dwType = REGISTER_ACCOUNT_FINAL_OK;
		}else
		{
			send_packet.Header.dwType = REGISTER_ACCOUNT_FINAL_FAIL;
		}		
		send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER);
		send_packet.Header.dwVersion = CURRENT_VERSION;

		CompressPacket(&send_packet, &send_compacket);

		LOCK_CONNECTION(0);
		QueuePacket(cn, &send_compacket);	
		UNLOCK_CONNECTION(0);
		SaveWorkToLog(EventRegisterAccount.cId,
					  inet_ntoa(cn->Addr.sin_addr),
					  "REGISTER_ACCOUNT_FINAL_OK");
	}
}
//-------------------------------------------------------------------------------
void	ServerDoChangeProfile(TPOS_CN *cn, TPOS_PACKET *packet)
{
	TPOS_EVENT_CHANGEPROFILE	EventChangeProfile;
	TPOS_DB_ACCOUNT				DbAccount;
	TPOS_PACKET					send_packet;
	TPOS_COMPACKET				send_compacket;

	memcpy(&EventChangeProfile, packet->data.cBuf, sizeof(TPOS_EVENT_CHANGEPROFILE));

	SaveWorkToLog(cn->User.cId,
				  inet_ntoa(cn->Addr.sin_addr),
				  "CHANGE_PROFILE");	

	ConvertEventChangeProfileToDbAccout(&EventChangeProfile, &DbAccount);

	strcpy(DbAccount.cId, cn->User.cId);
	strcpy(DbAccount.cPw, cn->User.cPw);

	if(UpdateRecordOfAccountDB(&DbAccount)==TRUE)
	{
		send_packet.Header.dwType = CHANGE_PROFILE_OK;
		SaveWorkToLog(cn->User.cId,inet_ntoa(cn->Addr.sin_addr),"CHANGE_PROFILE_OK");
	}else
	{
		send_packet.Header.dwType = CHANGE_PROFILE_FAIL;
		SaveWorkToLog(cn->User.cId,inet_ntoa(cn->Addr.sin_addr),"CHANGE_PROFILE_FAIL");
	}				
	send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER);
	send_packet.Header.dwVersion = CURRENT_VERSION;

	CompressPacket(&send_packet, &send_compacket);

	LOCK_CONNECTION(0);
	QueuePacket(cn, &send_compacket);
	UNLOCK_CONNECTION(0);
}
//-------------------------------------------------------------------------------
void	ServerDoChangePassword(TPOS_CN *cn, TPOS_PACKET *packet)
{
	TPOS_EVENT_CHANGEPASSWORD	EventChangePassword;
	TPOS_PACKET					send_packet;
	TPOS_COMPACKET				send_compacket;

	memcpy(&EventChangePassword, packet->data.cBuf, sizeof(TPOS_EVENT_CHANGEPASSWORD));

	SaveWorkToLog(cn->User.cId ,
				  inet_ntoa(cn->Addr.sin_addr),
				  "CHANGE_PASSWORD");
	if(ChangePasswordOfAccountDB(cn->User.cId, EventChangePassword.cPw)==TRUE)
	{
		send_packet.Header.dwType = CHANGE_PASSWORD_OK;
		SaveWorkToLog(cn->User.cId,
					  inet_ntoa(cn->Addr.sin_addr),
					  "CHANGE_PASSWORD_OK");
	}else
	{
		send_packet.Header.dwType = CHANGE_PASSWORD_FAIL;
		SaveWorkToLog(cn->User.cId,
					  inet_ntoa(cn->Addr.sin_addr),
					  "CHANGE_PASSWORD_FAIL");
	}
	send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER);
	send_packet.Header.dwVersion = CURRENT_VERSION;

	CompressPacket(&send_packet, &send_compacket);

	LOCK_CONNECTION(0);
	QueuePacket(cn, &send_compacket);	
	UNLOCK_CONNECTION(0);
}
//-------------------------------------------------------------------------------
void	ServerDoWorldServerLogin(TPOS_CN *cn, TPOS_PACKET *packet)
{
	TPOS_PACKET		send_packet;
	TPOS_COMPACKET	send_compacket;
	
	send_packet.Header.dwType = DOOR_LOGIN_OK;
	send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER);
	send_packet.Header.dwVersion = CURRENT_VERSION;

	CompressPacket(&send_packet, &send_compacket);

	LOCK_CONNECTION(0);
	QueuePacket(cn, &send_compacket);
	UNLOCK_CONNECTION(0);
}
//-------------------------------------------------------------------------------
void	ServerDoZoneServerLogin(TPOS_CN *cn, TPOS_PACKET *packet)
{
	TPOS_PACKET		send_packet;
	TPOS_COMPACKET	send_compacket;
		
	send_packet.Header.dwType = DOOR_LOGIN_OK;
	send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER);
	send_packet.Header.dwVersion = CURRENT_VERSION;

	CompressPacket(&send_packet, &send_compacket);

	LOCK_CONNECTION(0);
	QueuePacket(cn, &send_compacket);
	UNLOCK_CONNECTION(0);
}
//-------------------------------------------------------------------------------
void	ServerDoRecvWorldServerInfo(TPOS_CN *cn, TPOS_PACKET *packet)
{
	int						i;
	char					tmpcount[20];
	char					tmpport[20];
	TPOS_EVENT_NEWWORLDINFO	EventNewWorldInfo;
	char					str[256];

	LOCK_WORLDINFO(0);
	i = FindUsableWorldInfo();
	UNLOCK_WORLDINFO(0);	
	
	memcpy(&EventNewWorldInfo, packet->data.cBuf, sizeof(TPOS_EVENT_NEWWORLDINFO));
	
	sprintf(tmpcount, "%d", EventNewWorldInfo.dwPlayerCount);
	sprintf(tmpport, "%d", EventNewWorldInfo.dwPort);
	InsertLVItem(hListViewWnd, 0, EventNewWorldInfo.cName, tmpcount,
				 EventNewWorldInfo.cAddr, tmpport, "Disabled");
	LOCK_WORLDINFO(i);	
	WorldInfo[i].dwIndex=(DWORD)i+1;
	WorldInfo[i].dwSocket=cn->dwSocket;
	strcpy(WorldInfo[i].cName,EventNewWorldInfo.cName);
	strcpy(WorldInfo[i].cAddr,EventNewWorldInfo.cAddr);
	WorldInfo[i].dwPort=EventNewWorldInfo.dwPort;
	WorldInfo[i].dwPlayerCount=EventNewWorldInfo.dwPlayerCount;
	WorldInfo[i].dwActive=0;
	UNLOCK_WORLDINFO(i);

	iWorldCount++;
	sprintf(str, "Now World : %d",iWorldCount);	
	MsgOut(hStatusBarWnd, 1, str);
	dwOnlinePlayer--;
	sprintf(str, "Now Player : %d",dwOnlinePlayer);
	MsgOut(hStatusBarWnd, 0, str);
	SaveMsgToLog("SYSTEM","NEW_WORLD_INFO");
	SendNewWorldInfoToAll(EventNewWorldInfo.cName,
						  EventNewWorldInfo.dwPlayerCount,
						  EventNewWorldInfo.cAddr,
						  EventNewWorldInfo.dwPort,
						  0);
}
//-------------------------------------------------------------------------------
void	ServerDoRequestWorldServerInfo(TPOS_CN *cn, TPOS_PACKET *packet)
{
	int							i;
	TPOS_EVENT_GETWORLDINFO		EventGetWorldInfo;
	TPOS_EVENT_REQUESTWORLDINFO	EventRequestWorldInfo;
	TPOS_PACKET					send_packet;
	TPOS_COMPACKET				send_compacket;
	
	memcpy(&EventRequestWorldInfo, packet->data.cBuf, sizeof(TPOS_EVENT_REQUESTWORLDINFO));

	i = EventRequestWorldInfo.dwIndex;
	
	// 填入該索引的 World info
	// If the index World is an empty slot .. then response zero to Port
	if(i < 0)return;
	
	LOCK_WORLDINFO(i);
	if(WorldInfo[i].dwSocket != 0)
	{
		wsprintf(EventGetWorldInfo.cAddr, "%s", WorldInfo[i].cAddr);
		EventGetWorldInfo.dwIndex=WorldInfo[i].dwIndex;
		EventGetWorldInfo.dwPort=WorldInfo[i].dwPort;
		EventGetWorldInfo.dwPlayerCount = WorldInfo[i].dwPlayerCount;
		EventGetWorldInfo.dwActive = WorldInfo[i].dwActive;
		wsprintf(EventGetWorldInfo.cName, "%s", WorldInfo[i].cName);
	}else
	{
		EventGetWorldInfo.dwIndex = END;
	}
	UNLOCK_WORLDINFO(i);

	send_packet.Header.dwType = GET_WORLD_INFO;
	send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_GETWORLDINFO);
	send_packet.Header.dwVersion = CURRENT_VERSION;

	memcpy(&send_packet.data.cBuf, &EventGetWorldInfo, sizeof(TPOS_EVENT_GETWORLDINFO));

	CompressPacket(&send_packet, &send_compacket);
	
	LOCK_CONNECTION(0);
	QueuePacket(cn, &send_compacket);
	UNLOCK_CONNECTION(0);
}
//-------------------------------------------------------------------------------
void	ServerDoRefreshWorldServerInfo(TPOS_CN *cn, TPOS_PACKET *packet)
{
	DWORD						tempactive;
	int							i,x;
	TPOS_EVENT_REFRESHWORLDINFO	EventRefreshWorldInfo;
	char						str[256];

	memcpy(&EventRefreshWorldInfo, packet->data.cBuf, sizeof(TPOS_EVENT_REFRESHWORLDINFO));

	LOCK_WORLDINFO(0);
	i = FindWorldInfoByName(EventRefreshWorldInfo.cName);
	UNLOCK_WORLDINFO(0);
	if(i < 0)return;
	LOCK_WORLDINFO(i);			
	WorldInfo[i].dwPlayerCount = EventRefreshWorldInfo.dwPlayerCount;
	x = FindLVItem(hListViewWnd, EventRefreshWorldInfo.cName);
	sprintf(str, "%d", WorldInfo[i].dwPlayerCount);
	tempactive = WorldInfo[i].dwActive;
	UNLOCK_WORLDINFO(i);
	
	SetLVItem(hListViewWnd, x, 1, str);
	SaveMsgToLog("SYSTEM", "REFRESH_WORLD_INFO");
	SendWorldRefreshInfoToAll(EventRefreshWorldInfo.cName,
							  EventRefreshWorldInfo.dwPlayerCount,
							  tempactive);	
}
//-------------------------------------------------------------------------------
void	ConvertEventRegisterAccountToDbAccout(TPOS_EVENT_REGISTERACCOUNT *erc, TPOS_DB_ACCOUNT *da)
{
	strcpy(da->cId, erc->cId);
	strcpy(da->cPw, erc->cPw);
	strcpy(da->cAddress, erc->cAddress);
	strcpy(da->cBirthday, erc->cBirthday);
	strcpy(da->cCity, erc->cCity);
	strcpy(da->cCountry, erc->cCountry);
	strcpy(da->cEmail, erc->cEmail);
	strcpy(da->cPhone, erc->cPhone);
	da->cStatus = 0;
	da->dwJob = erc->dwJob;
	da->dwNetStyle = erc->dwNetStyle;
	da->dwPayType = erc->dwPayType;
	da->Sex = (char)erc->dwSex;	
}
//-------------------------------------------------------------------------------
void	ConvertEventChangeProfileToDbAccout(TPOS_EVENT_CHANGEPROFILE *ecp, TPOS_DB_ACCOUNT *da)
{	
	strcpy(da->cAddress, ecp->cAddress);
	strcpy(da->cBirthday, ecp->cBirthday);
	strcpy(da->cCity, ecp->cCity);
	strcpy(da->cCountry, ecp->cCountry);
	strcpy(da->cEmail, ecp->cEmail);
	strcpy(da->cPhone, ecp->cPhone);
	da->cStatus = 0;
	da->dwJob = ecp->dwJob;
	da->dwNetStyle = ecp->dwNetStyle;
	da->dwPayType = ecp->dwPayType;
	da->Sex = (char)ecp->dwSex;	
}
