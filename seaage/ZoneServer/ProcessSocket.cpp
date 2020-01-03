//---------------------------------------------------------------------------
// Psalm of Sea ZoneServer Doing Process
// By Hawke Hsieh 
// 2002-10-07
//---------------------------------------------------------------------------
#include "ZoneServer_Def.h"
#include "ServerCharacterDoing.h"
//#include "DoingPlayerCommand.h"

BOOL	bGSReadingNow = FALSE;
//---------------------------------------------------------------------------
// Find Connection By MainName
//---------------------------------------------------------------------------
int FindConnectionByName(char *mainname)
{
    int i;    
    
    for(i=0; i<MAX_PLAYER_PER_ZONE; i++)
    {
        if(strcmp(Pos_Cn[i].User.cId , mainname)==0) 
        {
            return(i);
        }
    }
    return -1;
}
//---------------------------------------------------------------------------
// Find Old Connection By MainName
//---------------------------------------------------------------------------
int FindOldConnectionByName(char *mainname,WPARAM wParam)
{
    int i;
   
    for(i=0; i<MAX_PLAYER_PER_ZONE; i++)
    {
		if((WPARAM)Pos_Cn[i].dwSocket != wParam)
		{
			if(strcmp(Pos_Cn[i].User.cId , mainname)==0) 
			{
				return(i);
			}
        }
    }
    return -1;
}
//---------------------------------------------------------------------------
// Find Current Connection
//---------------------------------------------------------------------------
int FindCurrentConnection(WPARAM wParam)
{
    int i;
    
    for(i=0; i<MAX_PLAYER_PER_ZONE; i++)
    {
        if((WPARAM)Pos_Cn[i].dwSocket == wParam) 
        {
            return(i);
        }
    }
    return -1;
}
//---------------------------------------------------------------------------
// Find Current SYNC Connection
//---------------------------------------------------------------------------
int FindCurrentSyncConnection(WPARAM wParam)
{
    int i;
    
    for(i=0; i<MAX_PLAYER_PER_ZONE; i++)
    {
        if((WPARAM)Pos_Cn_Sync[i].dwSocket == wParam) 
        {
            return(i);
        }
    }
    return -1;
}
//---------------------------------------------------------------------------
// Find Current Connection Character
//---------------------------------------------------------------------------
int FindCurrentConnectionCharacter(TPOS_CN *cn)
{
    int		i;

    for(i = 0;i < (MAX_NPC_PER_ZONE + MAX_PLAYER_PER_ZONE);i++)
    {		
        if(strcmp(cn->User.cId, GetCharacterMainName(i))==0)
        {
            return(i);
        }
    }
    return -1;
}
// -----------------------------------------------------------------------------
// Find Current Connection's QQID
// -----------------------------------------------------------------------------
SLONG FindCurrentConnectionQQID(TPOS_CN *cn)
{
	int i;
        
    for(i = 0;i < 1000;i++)
    {		
        if(strcmp(cn->User.cId, GetCharacterMainName(i))==0)
        {
            return GetCharacterQQID(i);            
        }
    }
    return -1;
}
// -----------------------------------------------------------------------------
// 讀取封包
// -----------------------------------------------------------------------------
int ReadPacket(TPOS_CN *cn)
{
    int			recv_count;
       
    if(!cn->InBuf)
    {
        cn->InBuf = (TPOS_BUFFER *)malloc(sizeof(TPOS_BUFFER));
        if(cn->InBuf == NULL) return 0;
        cn->InBuf->dwSize = 0;
        cn->InBuf->dwLocation = 0;
        cn->InBuf->next = NULL;
    }
    if(cn->InBuf->dwSize < sizeof(TPOS_COMPACKETHEADER))        
    {		
        recv_count = recv(cn->dwSocket, 
            (char *)cn->InBuf->cBuf + cn->InBuf->dwSize,
            sizeof(TPOS_COMPACKETHEADER) - cn->InBuf->dwSize, 0);        
    }
    else
    {
        if(((TPOS_COMPACKETHEADER*)cn->InBuf->cBuf)->dwSize > MAX_PACKET_SIZE)	return 0;     
        recv_count = recv(cn->dwSocket, 
            (char *)cn->InBuf->cBuf + cn->InBuf->dwSize,
            ((TPOS_COMPACKETHEADER *)cn->InBuf->cBuf)->dwSize - cn->InBuf->dwSize,
            0);
    }
    
    if(recv_count == 0)	return 0;
    if(recv_count == SOCKET_ERROR)
    {
        if(WSAGetLastError() == WSAEWOULDBLOCK) return 1;
        return 0;
    }
    cn->InBuf->dwSize += recv_count;
    
    if(cn->InBuf->dwSize == ((TPOS_COMPACKETHEADER*)cn->InBuf->cBuf)->dwSize)
	{
		ProcessPacket(cn);   
	}
    
    return 1;
}
// -----------------------------------------------------------------------------
// 寫入封包
// -----------------------------------------------------------------------------
int WritePacket(TPOS_CN *cn)
{
    int			send_count;
    TPOS_BUFFER		*tmpbuf;
    
    
    if(!cn->OutBuf) return 1;
    
    send_count = send(cn->dwSocket,
        (char *)cn->OutBuf->cBuf + cn->OutBuf->dwLocation,
        cn->OutBuf->dwSize - cn->OutBuf->dwLocation,
        0);
    if(send_count == SOCKET_ERROR)
    {
        if(WSAGetLastError() == WSAEWOULDBLOCK) return 1;
        return 0;
    }
    cn->OutBuf->dwLocation += send_count;
    
    if(cn->OutBuf->dwLocation == cn->OutBuf->dwSize)
    {
        tmpbuf = cn->OutBuf->next;
        free(cn->OutBuf);
        cn->OutBuf = tmpbuf;
    }
    
    return 1;
}
//---------------------------------------------------------------------------
// Queue Packet
//---------------------------------------------------------------------------
int QueuePacket(TPOS_CN *cn, TPOS_COMPACKET *compacket, DWORD ServerType)
{
    TPOS_BUFFER		*tmpbuf;
	TPOS_COMPACKET	send_compacket;
	
	memcpy(&send_compacket, compacket, sizeof(TPOS_COMPACKET)); 
	
	if(!cn->OutBuf)
	{
		cn->OutBuf = (TPOS_BUFFER *)malloc(sizeof(TPOS_BUFFER));
		if(cn->OutBuf == NULL) return 0;
		//=====  Modify By Hawke Hsieh 20020617  =====
		memcpy(cn->OutBuf->cBuf, &send_compacket, send_compacket.Header.dwSize);
		cn->OutBuf->dwSize = send_compacket.Header.dwSize;    
		cn->OutBuf->dwLocation = 0;
		cn->OutBuf->next = NULL;
	}
	else
	{
		for(tmpbuf = cn->OutBuf; tmpbuf->next; tmpbuf = tmpbuf->next);
		//=====  Modify By hawke Hsieh  =====
		if((MAX_PACKET_SIZE - tmpbuf->dwSize) < send_compacket.Header.dwSize)    
		{
			tmpbuf->next = (TPOS_BUFFER *)malloc(sizeof(TPOS_BUFFER));
			if(tmpbuf->next == NULL)return 0;
			tmpbuf = tmpbuf->next;
			tmpbuf->dwSize = 0;
			tmpbuf->dwLocation = 0;
			tmpbuf->next = NULL;
		}
		//=====  Modify By Hawke Hsieh 20020617  =====
		memcpy(tmpbuf->cBuf + tmpbuf->dwSize, &send_compacket, send_compacket.Header.dwSize);
		tmpbuf->dwSize += send_compacket.Header.dwSize;    
	}
    switch(ServerType)
    {
    case CONNECTED_SERVER_DOOR:
        PostMessage(DoorSockethWnd, WM_ASYNCSELECT, (WPARAM)cn->dwSocket, 
			         WSAMAKESELECTREPLY(FD_WRITE, 0));
        break;
    case CONNECTED_SERVER_WORLD:
        PostMessage(WorldSockethWnd, WM_ASYNCSELECT, (WPARAM)cn->dwSocket, 
			         WSAMAKESELECTREPLY(FD_WRITE, 0));
        break;
    case CONNECTED_SERVER_ZONE:		 
        PostMessage(ZoneSockethWnd, WM_ASYNCSELECT, (WPARAM)cn->dwSocket, 
			         WSAMAKESELECTREPLY(FD_WRITE, 0));
        break;
	case CONNECTED_SERVER_ZONESYNC:	
		PostMessage(ZoneSyncSockethWnd, WM_SYNC, (WPARAM)cn->dwSocket, 
					 WSAMAKESELECTREPLY(FD_WRITE, 0));
		break;
    } 
    
    return 1;
}
//---------------------------------------------------------------------------
// Process Packet
//---------------------------------------------------------------------------
int ProcessPacket(TPOS_CN *cn)
{
    static TPOS_COMPACKET		recv_compacket;
	static TPOS_PACKET			recv_packet;
    TPOS_BUFFER			*tmpbuf;
    BOOL				odbcRet=FALSE;     
    
    memset(&recv_compacket,0x0,sizeof(TPOS_COMPACKET));
    memcpy(&recv_compacket, cn->InBuf->cBuf, ((TPOS_COMPACKETHEADER*)cn->InBuf->cBuf)->dwSize);	

    tmpbuf = cn->InBuf->next;
    free(cn->InBuf);
    cn->InBuf = tmpbuf;

	recv_packet.Header.dwSize = lzo_decompress(recv_compacket.cBuf, recv_compacket.Header.dwSize - sizeof(DWORD), &recv_packet);
	if(recv_packet.Header.dwVersion != CURRENT_VERSION)	
    {
        SaveMsgToLog(cn->User.cId, "Not my packet!!");    
        return 0;
    }	
    switch(recv_packet.Header.dwType)
    {
		// From Door Server  --------------------------------------------------------
        
        // 登入大門伺服器成功
        // Login Door Server Successfull
    case DOOR_LOGIN_OK:
        SaveMsgToLog("SYSTEM","DOOR_LOGIN_OK");	         
        RequestForWorldInfo(BEGIN);
        break;
        // 登入大門伺服器失敗
        // Login Door Server Fail
    case DOOR_LOGIN_FAIL:
        SaveMsgToLog("SYSTEM","DOOR_LOGIN_FAIL");
        break;
	case GET_WORLD_INFO:
		ServerDoGetWorldInfo(cn, &recv_packet);
		break;
	case WORLD_LOGIN_OK:
		ServerDoWorldLoginOK(cn, &recv_packet);
		break;
	case ZONENAME_DUPLICATE:
		ServerDoZoneNameDuplicate(cn, &recv_packet);
		break;	
	case SYSTEM_MESSAGE:
		ServerDoGetSystemMessage(cn, &recv_packet);
		break;
	// QQ System
	case QQ_PLAYER_LOGIN:
		ServerDoQQPlayerLogin(cn, &recv_packet);
		break;
	case QQ_LOGIN_OK:
		ServerDoQQLoginOK(cn, &recv_packet);
		break;
	case QQ_PLAYER_LOGOUT:
		ServerDoQQPlayerLogout(cn, &recv_packet);
		break;
	case QQ_REQUEST_MYDATA:
		ServerDoQQRequestMyData(cn, &recv_packet);
		break;
	case QQ_GET_MYDATA:
		ServerDoQQGetMyData(cn, &recv_packet);
		break;
	case QQ_REQUEST_FRIEND_LIST:
		ServerDoQQRequestFriendList(cn, &recv_packet);
		break;
	case QQ_GET_FRIEND_LIST:
		ServerDoQQGetFriendList(cn, &recv_packet);
		break;
	case QQ_REQUEST_GUILD_FRIEND_LIST:
		ServerDoQQRequestGuildFriendList(cn, &recv_packet);
		break;
	case QQ_GET_GUILD_FRIEND_LIST:
		ServerDoQQGetGuildFriendList(cn, &recv_packet);
		break;
	case QQ_SET_MYSTATE:
		ServerDoQQSetMyState(cn, &recv_packet);
		break;
	case QQ_GET_MYSTATE:
		ServerDoQQGetMyState(cn, &recv_packet);
		break;
	case QQ_GET_OTHERSTATE:
		ServerDoQQGetOtherState(cn, &recv_packet);
		break;
	case QQ_REQUEST_QUERY_ADD_LIST:
		ServerDoQQRequestQueryAddList(cn, &recv_packet);
		break;
	case QQ_REQUEST_QUERY_ONLINE_ADDLIST:
		ServerDoQQRequestQueryOnlineAddList(cn, &recv_packet);
		break;
	case QQ_GET_QUERY_ADD_LIST_END:
		ServerDoQQGetQueryAddListEnd(cn, &recv_packet);
		break;
	case QQ_GET_QUERY_ADD_LIST:
		ServerDoQQGetQueryAddList(cn, &recv_packet);
		break;
	case QQ_REQUEST_ADD_SOMEONE:
		ServerDoQQRequestAddSomeone(cn, &recv_packet);
		break;
	case QQ_GET_ADD_SOMEONE:
		ServerDoQQGetAddSomeone(cn, &recv_packet);
		break;
	case QQ_GET_ADD_GUILD_FRIEND:
		ServerDoQQGetAddGuildFriend(cn, &recv_packet);
		break;
	case QQ_FRIEND_LOGIN:
		ServerDoQQFriendLogin(cn, &recv_packet);
		break;
	case QQ_REQUEST_QUERY_SOMEONE:
		ServerDoQQRequestQuerySomeone(cn, &recv_packet);
		break;
	case QQ_GET_QUERY_SOMEONE:
		ServerDoQQGetQuerySomeone(cn, &recv_packet);
		break;
	case QQ_SEND_2ONE_MSG:
		ServerDoQQSend2OneMsg(cn, &recv_packet);
		break;
	case QQ_SEND_2SOME_MSG:
		ServerDoQQSend2SomeMsg(cn, &recv_packet);
		break;
	case QQ_GET_MSG:
		ServerDoQQGetMsg(cn, &recv_packet);
		break;
	case QQ_REQUEST_PLAYER_COUNT:
		ServerDoQQRequestPlayerCount(cn, &recv_packet);
		break;
	case QQ_GET_PLAYER_COUNT:
		ServerDoQQGetPlayerCount(cn, &recv_packet);
		break;
	case QQ_REQUEST_DEL_FRIEND:
		ServerDoQQRequestDelFriend(cn, &recv_packet);
		break;
	case QQ_GET_DEL_FRIEND:
		ServerDoQQGetDelFriend(cn, &recv_packet);
		break;
	case QQ_REQUEST_DEL_GUILD_FRIEND:
		ServerDoQQRequestDelGuildFriend(cn, &recv_packet);
		break;
	case QQ_GET_DEL_GUILD_FRIEND:
		ServerDoQQGetDelGuildFriend(cn, &recv_packet);
		break;
	case QQ_REQUEST_TRANSFER_ITEM:
		ServerDoQQRequestTransferItem(cn, &recv_packet);
		break;	
	case QQ_REQUEST_TRANSFER_ITEM_FROM_WORLD:
		ServerDoQQRequestTransferItemFromWorld(cn, &recv_packet);
		break;	
	case QQ_TRANSFER_ITEM_OK_FROM_WORLD:
		ServerDoQQTransferItemOKFromWorld(cn, &recv_packet);
		break;
	case QQ_TRANSFER_ITEM_FAIL_FROM_WORLD:
		ServerDoQQTransferItemFailFromWorld(cn, &recv_packet);
		break;
	case PLAYER_LOGOUT:
		ServerDoPlayerLogout(cn, &recv_packet);
		break;
	case PLAYER_LOGIN:
		ServerDoPlayerLogin(cn, &recv_packet);
		break;
	case REQUEST_PLAYER_LIST:
		ServerDoRequestPlayerList(cn, &recv_packet);
		break;
	case GET_PUBLIC_TALK:
		ServerDoGetPublicTalk(cn, &recv_packet);
		break;
	case GET_WORLD_TALK:
		ServerDoGetWorldTalk(cn, &recv_packet);
		break;
	case SAVE_USER_DETAIL:
		ServerDoSaveUserDetail(cn, &recv_packet);
		break;
	case HIT_MAP:
		ServerDoHitMap(cn, &recv_packet);
		break;
	case END_HIT_MAP:
		ServerDoEndHitMap(cn, &recv_packet);
		break;
	case HIT_NPC:
		ServerDoHitNPC(cn, &recv_packet);
		break;
	case HIT_ITEM:
		ServerDoHitItem(cn, &recv_packet);
		break;
	case SEND_ATTACK_SWITCH:
		ServerDoSendAttackSwitch(cn, &recv_packet);
		break;
	case SEND_BAG_SWITCH:
		ServerDoSendBagSwitch(cn, &recv_packet);
		break;
	case CHANGE_MOUSE_SKILL:
		ServerDoChangeMouseSkill(cn, &recv_packet);
		break;
	case UPDATE_NPC_BASE_DATA:
		ServerDoUpdateNPCBaseData(cn, &recv_packet);
		break;
	case REQUEST_CHANGE_WEATHER:
		ServerDoRequestChangeWeather(cn, &recv_packet);
		break;
	case GAME_START:
		ServerDoGameStart(cn, &recv_packet);
		break;
	case REQUEST_EXIT_GAME:
		ServerDoRequestExitGame(cn, &recv_packet);
		break;
	case NEW_ZONE_INFO:
		ServerDoNewZoneInfo(cn, &recv_packet);
		break;
	case ONE_ZONE_CLOSE:
		ServerDoOneZoneClose(cn, &recv_packet);
		break;
	case REFRESH_ZONE_INFO:
		ServerDoRefreshZoneInfo(cn, &recv_packet);
		break;
	case GET_ZONE_INFO:
		ServerDoGetZoneInfo(cn, &recv_packet);
		break;
	case ZONE_GET_ITEM_ID:
		ServerDoZoneGetItemID(cn, &recv_packet);
		break;
	case REQUEST_SET_HAND_QUICK_SKILL:
		ServerDoRequestSetHandQuickSkill(cn, &recv_packet);
		break;
	case REQUEST_USE_HAND_QUICK_SKILL:
		ServerDoRequestUseHandQuickSkill(cn, &recv_packet);
		break;
	case REQUEST_HIT_BAG_ITEM:
		ServerDoRequestHitBagItem(cn, &recv_packet);
		break;
	case REQUEST_HIT_HEAD_ITEM:
		ServerDoRequestHitHeadItem(cn, &recv_packet);
		break;
	case REQUEST_HIT_NECK_ITEM:
		ServerDoRequestHitNeckItem(cn, &recv_packet);
		break;
	case REQUEST_HIT_BODY_ITEM:
		ServerDoRequestHitBodyItem(cn, &recv_packet);
		break;
	case REQUEST_HIT_WAIST_ITEM:
		ServerDoRequestHitWaistItem(cn, &recv_packet);
		break;
	case REQUEST_HIT_GLOVE_ITEM:
		ServerDoRequestHitGloveItem(cn, &recv_packet);
		break;
	case REQUEST_HIT_WEAPON_ITEM:
		ServerDoRequestHitWeaponItem(cn, &recv_packet);
		break;
	case REQUEST_HIT_WRIST_ITEM:
		ServerDoRequestHitWristItem(cn, &recv_packet);
		break;
	case REQUEST_HIT_FEET_ITEM:
		ServerDoRequestHitFeetItem(cn, &recv_packet);
		break;
	case REQUEST_HIT_OTHERA_ITEM:
		ServerDoRequestHitOtherAItem(cn, &recv_packet);
		break;
	case REQUEST_HIT_OTHERB_ITEM:
		ServerDoRequestHitOtherBItem(cn, &recv_packet);
		break;
	case REQUEST_HIT_OTHERC_ITEM:
		ServerDoRequestHitOtherCItem(cn, &recv_packet);
		break;
	case REQUEST_HIT_SASH_ITEM:
		ServerDoRequestHitSashItem(cn, &recv_packet);
		break;
	case REQUEST_HIT_TRANS_ITEM:
		ServerDoRequestHitTransItem(cn, &recv_packet);
		break;
	case REQUEST_HIT_TREASURE_ITEM:
		ServerDoRequestHitTreasureItem(cn, &recv_packet);
		break;		
	case REQUEST_DROP_ITEM:
		ServerDoRequestDropItem(cn, &recv_packet);
		break;
	case REQUEST_HIT_MAP_ITEM:
		ServerDoRequestHitMapItem(cn, &recv_packet);
		break;
	case REQUEST_SEPARATE_MAP:
		ServerDoRequestSeparateMap(cn, &recv_packet);
		break;
	case NOTIFY_MAP_INFO:
		break;
	case REQUEST_NPC_PROC:
		ServerDoRequestNpcProc(cn, &recv_packet);
		break;
	case REQUEST_CHANGE_DIR:
		ServerDoRequestChangeDir(cn, &recv_packet);
		break;
	case REQUEST_BUY_ITEM:
		ServerDoRequestBuyItem(cn, &recv_packet);
		break;
	case REQUEST_SELL_ITEM:
		ServerDoRequestSellItem(cn, &recv_packet);
		break;
	case GOD_REQUEST_FULLHPMP:
		ServerDoGodRequestFullHpMp(cn, &recv_packet);
		break;
	case GOD_REQUEST_JUMPTO:
		ServerDoGodRequestJumpTo(cn, &recv_packet);
		break;
	case GOD_REQUEST_ITEM:
		ServerDoGodRequestItem(cn, &recv_packet);
		break;
	case GOD_REQUEST_MONEY:
		ServerDoGodRequestMoney(cn, &recv_packet);
		break;
	case GOD_REQUEST_EXP:
		ServerDoGodRequestExp(cn, &recv_packet);
		break;
	case GOD_REQUEST_MOVEFAST:
		ServerDoGodRequestMoveFast(cn, &recv_packet);
		break;
	case GOD_REQUEST_SUPERMAN:
		ServerDoGodRequestSuperMan(cn, &recv_packet);
		break;
	case GOD_REQUEST_DEAD:
		ServerDoGodRequestDead(cn, &recv_packet);
		break;
	case GOD_REQUEST_CHANGEZONE:
		ServerDoGodRequestChangeZone(cn, &recv_packet);
		break;
	case GOD_REQUEST_GET_MAP:
		ServerDoGodRequestGetMap(cn, &recv_packet);
		break;
	case GOD_REQUEST_PROPERTYPOINT:
		ServerDoGodRequestPropertyPoint(cn, &recv_packet);
		break;
	case REQUEST_JOIN_TEAM:
		ServerDoRequestJoinTeam(cn, &recv_packet);
		break;
	case REQUEST_AGREE_JOIN_TEAM:
		ServerDoReequestAgreeJoinTeam(cn, &recv_packet);
		break;
	case REQUEST_EXIT_TEAM:
		ServerDoRequestExitTeam(cn, &recv_packet);
		break;
	case REQUEST_KICK_TEAM_MEMBER:
		ServerDoRequestKickTeamMember(cn, &recv_packet);
		break;		
	case ZONE_REQUEST_JOIN_TEAM:
		ServerDoZoneRequestJoinTeam(cn, &recv_packet);
		break;
	case ZONE_REQUEST_AGREE_JOIN_TEAM:
		ServerDoZoneRequestAgreeJoinTeam(cn, &recv_packet);
		break;
	case ZONE_REQUEST_EXIT_TEAM:
		ServerDoZoneRequestExitTeam(cn, &recv_packet);
		break;	
	case ZONE_REQUEST_KICK_TEAM_MEMBER:
		ServerDoZoneRequestKickTeamMember(cn, &recv_packet);
		break;
	case ZONE_NOTIFY_JOIN_TEAM_FULL:
		ServerDoZoneNotifyJoinTeamFull(cn, &recv_packet);
		break;	
	case REQUEST_SAVE_MONEY:
		ServerDoRequestSaveMoney(cn, &recv_packet);
		break;
	case REQUEST_LOAD_MONEY:
		ServerDoRequestLoadMoney(cn, &recv_packet);
		break;
	case REQUEST_HIT_BANK_ITEM:
		ServerDoRequestHitBankItem(cn, &recv_packet);
		break;	
	}
    return 1;
}
// -----------------------------------------------------------------------------
// Socket處理函式 For DoorServer
// -----------------------------------------------------------------------------
LRESULT CALLBACK DoorSocketWndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
    DWORD   AsyncEvent;
    
    switch (iMsg)
    {
    case WM_ASYNCSELECT:
        AsyncEvent = WSAGETSELECTEVENT(lParam);
        
        switch(AsyncEvent)
        {
        case FD_READ:
            if(bGSReadingNow) break;
            bGSReadingNow = TRUE;
            if(!ReadPacket(Door)) CloseOneConnection(Door);						 
            bGSReadingNow = FALSE;						
            break;
            
        case FD_WRITE:
            if(!WritePacket(Door)) CloseOneConnection(Door);						 
            break;
            
        case FD_CLOSE:
            PostMessage(MainhWnd, WM_POSGAMEEVENT, 0, DOOR_SERVER_CLOSED);
            break;
        }
        return 0;
        
        case WM_DESTROY :
            return 0;
    }
    return DefWindowProc(hWnd, iMsg, wParam, lParam);
}
// -----------------------------------------------------------------------------
// Socket處理函式 For WorldServer
// -----------------------------------------------------------------------------
LRESULT CALLBACK WorldSocketWndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
    DWORD   AsyncEvent;
    
    switch (iMsg)
    {
    case WM_ASYNCSELECT:
        AsyncEvent = WSAGETSELECTEVENT(lParam);
        
        switch(AsyncEvent)
        {
        case FD_READ:
            if(bGSReadingNow) break;
            bGSReadingNow = TRUE;
            if(!ReadPacket(World)) CloseOneConnection(World); 
            bGSReadingNow = FALSE;						
            break;
            
        case FD_WRITE:
            if(!WritePacket(World)) CloseOneConnection(World);						 
            break;
            
        case FD_CLOSE:
            SendMessage(MainhWnd, WM_POSGAMEEVENT, 0, WORLD_SERVER_CLOSED);
            break;
        }
        return 0;
        
        case WM_DESTROY :
            return 0;
    }
    return DefWindowProc(hWnd, iMsg, wParam, lParam);
}
// -----------------------------------------------------------------------------
// Socket處理函式 For ZoneServer
// -----------------------------------------------------------------------------
LRESULT CALLBACK ZoneSocketWndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
    DWORD   AsyncEvent;
    SOCKET	tmp_socket;
    struct	sockaddr_in sa;
    int   	sa_len = sizeof(sa);
    int  	ci;
    BOOL	nodelay = TRUE;
	BOOL	killonebadconnect = FALSE;
	char	mainname[32];
	LONG	characterindex;
    
    switch (iMsg)
    {
    case WM_ASYNCSELECT:
        {
            AsyncEvent = WSAGETSELECTEVENT(lParam);
            
            switch(AsyncEvent)
            {
            case FD_ACCEPT:
                {
                    tmp_socket = accept(Zone->dwSocket, (struct sockaddr far *)&sa, &sa_len);
                    if(tmp_socket != INVALID_SOCKET)
                    {
                        int find_usable;
                        struct in_addr temp_addr;
                        
                        LOCK_CONNECTION(0);
                        find_usable = FindUsableConnection();
                        UNLOCK_CONNECTION(0);
                        
                        // if no any free room then closed the in-coming socket
                        if(find_usable < 0)
                        {
                            CloseOneSocket(tmp_socket);
                        }
                        else
                        {
                            WSAAsyncSelect(tmp_socket, ZoneSockethWnd, WM_ASYNCSELECT, FD_READ | FD_WRITE | FD_CLOSE);
                            
                            LOCK_CONNECTION(0);
                            Pos_Cn[find_usable].dwSocket = tmp_socket;
                            memcpy(&Pos_Cn[find_usable].Addr, &sa, sizeof(struct sockaddr_in));
                            temp_addr =  Pos_Cn[find_usable].Addr.sin_addr;
                            UNLOCK_CONNECTION(0);
                            
                            dwConnectedCounter++;
                            dwOnlineCounter++;
                            
							SendRefreshZoneInfoToWorld();                            
                            
                            SaveConnectedCounter(dwConnectedCounter);
                            SaveIOToLog(inet_ntoa(temp_addr),"Login");
                        }
                    }
                }
                break;
            case FD_READ:
                {
                    if(bGSReadingNow) break;
                    
                    LOCK_CONNECTION(0);
                    ci = FindCurrentConnection(wParam);
                    UNLOCK_CONNECTION(0);					
                    if(ci >= 0)
                    {						
                        bGSReadingNow = TRUE;                        
                        LOCK_CONNECTION(ci);                        
                        if(! ReadPacket(&Pos_Cn[ci]))
                        {
							strcpy(mainname, Pos_Cn[ci].User.cId);
                            CloseOneConnection(&Pos_Cn[ci]);
							if(dwOnlineCounter > 0)dwOnlineCounter--;
							killonebadconnect = TRUE;
                        }                        
                        UNLOCK_CONNECTION(ci);
						if(killonebadconnect == TRUE)
						{
							LOCK_CHARACTER(0);
							characterindex = FindCharacterByMainName(mainname);
							UNLOCK_CHARACTER(0);
							if(characterindex >= 0)BadConnect[characterindex] = TRUE;							
							killonebadconnect = FALSE;
						}
						bGSReadingNow = FALSE;
                    }
                }
                break;
                
            case FD_WRITE:
                {
                    LOCK_CONNECTION(0);
                    ci = FindCurrentConnection(wParam);
                    UNLOCK_CONNECTION(0);
                    if(ci >= 0)
                    {
                        LOCK_CONNECTION(ci);                                                                  
                        if(!WritePacket(&Pos_Cn[ci])) 
                        {
                            strcpy(mainname, Pos_Cn[ci].User.cId);
                            CloseOneConnection(&Pos_Cn[ci]);
							if(dwOnlineCounter > 0)dwOnlineCounter--;
							killonebadconnect = TRUE;
                        }
                        UNLOCK_CONNECTION(ci);
						if(killonebadconnect == TRUE)
						{
							LOCK_CHARACTER(0);
							characterindex = FindCharacterByMainName(mainname);							
							if(characterindex >= 0)BadConnect[characterindex] = TRUE;
							UNLOCK_CHARACTER(0);	
							killonebadconnect = FALSE;
						}
                    }
                }
                break;
                
            case FD_CLOSE:
                {                                   
                    int     matched_index;
                    char	mainname[64];
                    
                    LOCK_CONNECTION(0);
                    ci = FindCurrentConnection(wParam);
                    UNLOCK_CONNECTION(0);
                    if(ci >= 0)
                    {
                        matched_index = -1;
                        LOCK_CONNECTION(ci);
                        strcpy((char *)mainname, Pos_Cn[ci].User.cId);
                        UNLOCK_CONNECTION(ci);
                        
                        LOCK_CHARACTER(0);
                        matched_index = FindPlayerCharacterInfoByMainName(mainname);
                        UNLOCK_CHARACTER(0);
                        if(matched_index >= 0)
                        {
                            //清除該玩家資料
                            LOCK_CHARACTER(0);                            
							ClearOneCharacter(matched_index); 
							BadConnect[matched_index] = FALSE;
                            UNLOCK_CHARACTER(0);
                            
							SendPlayerExitToAll(matched_index);                            
#ifdef  DEBUG_MSG
							LOCK_CONNECTION(ci);                            
                            sprintf(str,
                                "Player :%s , Index : %d , From %s Logout OK",
                                mainname,
                                matched_index,
                                inet_ntoa(Pos_Cn[ci].Addr.sin_addr)
                                );						   
                            SaveMsgToLog("SYSTEM",str);
                            UNLOCK_CONNECTION(ci);
#endif//DEBUG_MSG                            
                        }                        
                        LOCK_CONNECTION(ci);
                        SaveIOToLog(inet_ntoa(Pos_Cn[ci].Addr.sin_addr),"Logout");
                        CloseOneConnection(&Pos_Cn[ci]);
                        //清除該連接資料
                        Pos_Cn[ci].dwSocket = 0;
                        sprintf(Pos_Cn[ci].User.cId, "");
                        UNLOCK_CONNECTION(ci);
                        
                        //修改當前玩家數量值
                        if(dwOnlineCounter > 0)dwOnlineCounter--;
                        
                        SendRefreshZoneInfoToWorld();
                    }
                }
                break;
            }
        }
        return 0;
        
    case WM_DESTROY:
        return 0;
    }
    return DefWindowProc(hWnd, iMsg, wParam, lParam);
}
// -----------------------------------------------------------------------------
// Sync Socket處理函式 For ZoneServer Sync
// -----------------------------------------------------------------------------
LRESULT CALLBACK ZoneSyncSocketWndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
    DWORD   AsyncEvent;
    struct	sockaddr_in sa;
    int	sa_len = sizeof(sa);
    SOCKET	tmp_socket;
    int	ci;
    BOOL	nodelay = TRUE;
    int     find_idx;
    //char	str[512];
    
    switch (iMsg)
    {
    case WM_SYNC:
        {
            AsyncEvent = WSAGETSELECTEVENT(lParam);
            switch(AsyncEvent)
            {
            case FD_ACCEPT:
                {
                    tmp_socket = accept(ZoneSync->dwSocket, (struct sockaddr far *)&sa, &sa_len);
                    if(tmp_socket != INVALID_SOCKET)
                    {
                        LOCK_SYNCCONNECTION(0);
                        find_idx = FindUsableSyncConnection();
                        UNLOCK_SYNCCONNECTION(0);
                        
                        // if no any free room then closed the in-coming socket
                        if(find_idx < 0)
                        {
                            CloseOneSocket(tmp_socket);
                        }
                        else
                        {
                            WSAAsyncSelect(tmp_socket, ZoneSyncSockethWnd, WM_SYNC, FD_READ | FD_WRITE | FD_CLOSE);
                            
                            LOCK_SYNCCONNECTION(find_idx);
                            Pos_Cn_Sync[find_idx].dwSocket = tmp_socket;
                            memcpy(&Pos_Cn_Sync[find_idx].Addr, &sa, sizeof(struct sockaddr_in));
                            UNLOCK_SYNCCONNECTION(find_idx);
                        }
                    }
                }
                break;
                
            case FD_READ:             					
                break;
                
            case FD_WRITE:
                {
                    //TPOS_CN TempCN;
                    
                    LOCK_SYNCCONNECTION(0);
                    ci = FindCurrentSyncConnection(wParam);
                    UNLOCK_SYNCCONNECTION(0);
                    if(ci >= 0)
                    {
                        LOCK_SYNCCONNECTION(ci);
                        if(!WritePacket(&Pos_Cn_Sync[ci]))
                        {
                            CloseOneConnection(&Pos_Cn_Sync[ci]);                            
                            Pos_Cn_Sync[ci].dwSocket = 0;                            
                        }
                        UNLOCK_SYNCCONNECTION(ci);
                    }
                }
                break;
                
            case FD_CLOSE:
                {
                    
                    
                    LOCK_SYNCCONNECTION(0);
                    ci = FindCurrentSyncConnection(wParam);
                    UNLOCK_SYNCCONNECTION(0);
                    if(ci >= 0)
                    {
                        LOCK_SYNCCONNECTION(ci);           
                        CloseOneConnection(&Pos_Cn_Sync[ci]);
                        Pos_Cn_Sync[ci].dwSocket=0;
                        UNLOCK_SYNCCONNECTION(ci);
                    }
                }
                break;
            }
        }
        return 0;
        
    case WM_DESTROY :
        return 0;
    }
    return DefWindowProc(hWnd, iMsg, wParam, lParam);
}
// ---------------------------------------------------------------------------
// Request WorldServer Info From DoorServer
//---------------------------------------------------------------------------
int RequestForWorldInfo(DWORD index)
{
    static TPOS_PACKET					send_packet;
	static TPOS_COMPACKET				send_compacket;
	TPOS_EVENT_REQUESTWORLDINFO	EventRequestWorldInfo;
    
    //if(index == 0) dwRequestForWorldInfoIndex = 0;    
	EventRequestWorldInfo.dwIndex = index;
    
	send_packet.Header.dwType = REQUEST_WORLD_INFO;
    send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_REQUESTWORLDINFO);
    
    memcpy(send_packet.data.cBuf, &EventRequestWorldInfo, sizeof(TPOS_EVENT_REQUESTWORLDINFO));
    
	CompressPacket(&send_packet, &send_compacket);

    if(QueuePacket(Door, &send_compacket, CONNECTED_SERVER_DOOR)) return DLL_OK;
    
    return DLL_ERROR;
}
//---------------------------------------------------------------------------
int RequestForZoneInfo(DWORD index)
{
    static TPOS_PACKET					send_packet;
	static TPOS_COMPACKET				send_compacket;
	TPOS_EVENT_REQUESTZONEINFO	EventRequestZoneInfo;
    
	EventRequestZoneInfo.dwIndex = index;
    send_packet.Header.dwType = REQUEST_ZONE_INFO;
    send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_REQUESTZONEINFO);
    
	memcpy(send_packet.data.cBuf, &EventRequestZoneInfo, sizeof(TPOS_EVENT_REQUESTZONEINFO));
    
	CompressPacket(&send_packet, &send_compacket);
    	
    if(QueuePacket(World, &send_compacket, CONNECTED_SERVER_WORLD)==TRUE)return DLL_OK;
    
    return DLL_ERROR;
}
// ---------------------------------------------------------------------------
void SendRefreshZoneInfoToWorld()
{
	static TPOS_PACKET					send_packet;
	static TPOS_COMPACKET			    send_compacket;
	TPOS_EVENT_REFRESHZONEINFO	EventRefreshZoneInfo;
	
	strcpy(EventRefreshZoneInfo.cName, ZoneName);
	EventRefreshZoneInfo.dwPlayerCount = dwOnlineCounter;

	send_packet.Header.dwType = REFRESH_ZONE_INFO;
	send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_REFRESHZONEINFO);
	memcpy(send_packet.data.cBuf, &EventRefreshZoneInfo, sizeof(TPOS_EVENT_REFRESHZONEINFO));

	CompressPacket(&send_packet, &send_compacket);
	
	QueuePacket(World, &send_compacket, CONNECTED_SERVER_WORLD);
}
// ---------------------------------------------------------------------------
void SendPlayerExitToAll(int index)
{
    static TPOS_PACKET				send_packet;	
	static TPOS_EVENT_PLAYEREXIT	EventPlayerExit;

    EventPlayerExit.iIndex = index;
    
    send_packet.Header.dwType = PLAYER_EXIT;
    send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_PLAYEREXIT);
    memcpy(send_packet.data.cBuf, &EventPlayerExit, sizeof(TPOS_EVENT_PLAYEREXIT));

	server_send_packet_to_all(&send_packet);
}
//---------------------------------------------------------------------------
void SendPlayerJoinToAll(TPOS_CN *cn,TPOS_EVENT_PLAYERJOIN *EventPlayerJoin)
{
    static TPOS_PACKET		send_packet;	
       
    send_packet.Header.dwType = PLAYER_JOIN;
    send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_PLAYERJOIN);
    memcpy(&send_packet.data.cBuf, EventPlayerJoin, sizeof(TPOS_EVENT_PLAYERJOIN));    

	server_send_packet_to_all(&send_packet);
}
//---------------------------------------------------------------------------
void CompressPacket(TPOS_PACKET	*packet, TPOS_COMPACKET *compacket)
{
	static TPOS_PACKET		send_packet;	
	static TPOS_COMPACKET	send_compacket;
	static char			compressbuf[MAX_PACKET_SIZE - sizeof(DWORD)];
	DWORD			comsize;
	
	memcpy(&send_packet, packet, sizeof(TPOS_PACKET));
	send_packet.Header.dwVersion = CURRENT_VERSION;
	memcpy(compressbuf, &send_packet, send_packet.Header.dwSize);
	
	comsize = lzo_compress(compressbuf, send_packet.Header.dwSize, send_compacket.cBuf);
	send_compacket.Header.dwSize = comsize + sizeof(DWORD);
	
	memcpy(compacket, &send_compacket, sizeof(TPOS_COMPACKET));
}
// ---------------------------------------------------------------------------
int     server_send_packet_to_one(void *connect, void *packet)
{
    TPOS_PACKET *send_packet = (TPOS_PACKET *)packet;
	static TPOS_COMPACKET	send_compacket;
    TPOS_CN		*send_conn = (TPOS_CN *)connect;
    int result;

	CompressPacket(send_packet, &send_compacket);

    LOCK_CONNECTION(0);
    result = QueuePacket(send_conn, &send_compacket, CONNECTED_SERVER_ZONE);
    UNLOCK_CONNECTION(0);

    if(result)
        return  DLL_OK;
    else
        return  DLL_ERROR;
}
// ---------------------------------------------------------------------------

int     server_send_packet_to_player(int player_index, void *packet)
{
    TPOS_PACKET *send_packet = (TPOS_PACKET *)packet;
	static TPOS_COMPACKET	send_compacket;
    int		result;
	char	temp_mainname[32];
	int		cn_index;

    result = DLL_OK;

	CompressPacket(send_packet, &send_compacket);

	LOCK_CHARACTER(0);
	strcpy(temp_mainname, GetCharacterMainName(player_index));	
	UNLOCK_CHARACTER(0);
    
	LOCK_CONNECTION(0);
	cn_index = FindConnectionByName(temp_mainname);
    if(cn_index != -1)
    {
        result = QueuePacket(&Pos_Cn[cn_index], &send_compacket, CONNECTED_SERVER_ZONE);
    }
    UNLOCK_CONNECTION(0);

    if(result)  
        return  DLL_OK;
    else        
        return  DLL_ERROR;
}
// ---------------------------------------------------------------------------
int     server_send_packet_to_all(void *packet)
{   
	
	TPOS_COMPACKET	send_compacket;
	SLONG   i;
    DWORD   total;    

	total = 0;
	
	CompressPacket((TPOS_PACKET*)packet, &send_compacket);

	LOCK_CONNECTION(0);
    for(i=0; i<MAX_PLAYER_PER_ZONE; i++)
    {
        if(Pos_Cn[i].dwSocket!=0)
        {
            QueuePacket(&Pos_Cn[i], &send_compacket, CONNECTED_SERVER_ZONE);            
            total ++;
        }
        if(total == dwOnlineCounter) break;
    } 
    UNLOCK_CONNECTION(0);

	return DLL_OK;
}
// ---------------------------------------------------------------------------
int     server_send_packet_to_teammember(int npc_no, void *packet)
{   
	int		i;
	char	temp_mainname[32];
	SLONG	temp_npc_no, temp_cn_index;
	TPOS_COMPACKET	send_compacket;

	CompressPacket((TPOS_PACKET*)packet, &send_compacket);
	
	LOCK_CHARACTER(0);
	strcpy(temp_mainname, GetCharacterTeamMemberMainName(npc_no, 0));
	UNLOCK_CHARACTER(0);
	if(strcmp(temp_mainname, "") == 0)return DLL_OK;	
	for(i = 0; i < MAX_CHARACTER_TEAM_MEMBERS; i++)
	{
		LOCK_CHARACTER(0);
		strcpy(temp_mainname, GetCharacterTeamMemberMainName(npc_no, i));
		temp_npc_no = FindCharacterByMainName(temp_mainname);
		UNLOCK_CHARACTER(0);
		if(temp_npc_no != -1 && temp_npc_no != npc_no)
		{
			LOCK_CONNECTION(0);
			temp_cn_index = FindConnectionByName(temp_mainname);			
			if(temp_cn_index != -1)
			{
				QueuePacket(&Pos_Cn[temp_cn_index], &send_compacket, CONNECTED_SERVER_ZONE);
			}			
			UNLOCK_CONNECTION(0);
		}
	}	

	return DLL_OK;
}
//---------------------------------------------------------------------------
// Send Refresh To All Function
//---------------------------------------------------------------------------
void SendRefreshToAll(DWORD s)
{
    static TPOS_PACKET				send_packet;
	TPOS_EVENT_REFRESHFLAG	EventRefreshFlag;
    
    EventRefreshFlag.dwHeartBeat = s;

	send_packet.Header.dwType = GET_REFRESH;
    send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_REFRESHFLAG);
    
	memcpy(send_packet.data.cBuf, &EventRefreshFlag, sizeof(TPOS_EVENT_REFRESHFLAG));
    
	server_send_packet_to_all(&send_packet);    
}
//---------------------------------------------------------------------------
// Send Position To All
//---------------------------------------------------------------------------
void SendPositionToAll(void)
{
    DWORD					i;
    static TPOS_PACKET				send_packet;
	static TPOS_COMPACKET			send_compacket;
	SLONG					x,y,z;
	    
    LOCK_CHARACTER(0);
    for(int C_Index = 0;C_Index < MAX_CHARACTER_PER_ZONE;C_Index++)
    {
		GetCharacterPosition(C_Index, &x, &y, &z);
        SyncMove[C_Index].lX = x;
        SyncMove[C_Index].lY = y;
    }	
    UNLOCK_CHARACTER(0);

	send_packet.Header.dwType = SYNC_POSITION;
	send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + (sizeof(TPOS_SYNCMOVE)*MAX_CHARACTER_PER_ZONE);
    memcpy(send_packet.data.cBuf, SyncMove, sizeof(TPOS_SYNCMOVE) * MAX_CHARACTER_PER_ZONE);

	CompressPacket(&send_packet, &send_compacket);

    LOCK_SYNCCONNECTION(0);    
    for(i = 0; i<MAX_PLAYER_PER_ZONE; i++)
    {
        if(Pos_Cn_Sync[i].dwSocket != 0)
        {
            QueuePacket(&Pos_Cn_Sync[i], &send_compacket ,CONNECTED_SERVER_ZONESYNC);            
        }         
    } 
    UNLOCK_SYNCCONNECTION(0);

    bCheckSYNC = false;
}
//---------------------------------------------------------------------------
// Send Sea Position To All
//---------------------------------------------------------------------------
void SendSeaPositionToAll(void)
{
    DWORD			i;
    static TPOS_PACKET		send_packet;
	static TPOS_COMPACKET	send_compacket;
	SLONG			sync_x,sync_y,sync_z;
	SLONG			degree_dir, x, y, z, speed_x, speed_y;	
	   
    LOCK_CHARACTER(0);
    for(int C_Index = 0;C_Index < MAX_CHARACTER_PER_ZONE;C_Index++)
    {
		degree_dir = GetCharacterShipDegreeDir(C_Index);
		GetCharacterPosition(C_Index, &x, &y, &z);
		speed_x = GetCharacterShipSpeedX(C_Index);
		speed_y = GetCharacterShipSpeedY(C_Index);
		encode_sea_npc_sync_position(sync_x, sync_y, sync_z, degree_dir, x, y,
							 		 speed_x, speed_y);
		SyncSeaMove[C_Index].X = sync_x;
		SyncSeaMove[C_Index].Y = sync_y;
		SyncSeaMove[C_Index].Z = sync_z;
    }	
    UNLOCK_CHARACTER(0);	
        
    send_packet.Header.dwType = SEA_SYNC_POSITION;    
    send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + (sizeof(TPOS_SYNCSEAMOVE) * MAX_CHARACTER_PER_ZONE);	
	memcpy(send_packet.data.cBuf, SyncSeaMove, (sizeof(TPOS_SYNCSEAMOVE) * MAX_CHARACTER_PER_ZONE));

	CompressPacket(&send_packet, &send_compacket);

    LOCK_SYNCCONNECTION(0);    
    for(i=0; i<MAX_PLAYER_PER_ZONE; i++)
    {
        if(Pos_Cn_Sync[i].dwSocket != 0)
        {
            QueuePacket(&Pos_Cn_Sync[i], &send_compacket, CONNECTED_SERVER_ZONESYNC);        
        }        
    } 
    UNLOCK_SYNCCONNECTION(0);

    bCheckSYNC = false;
}
//-------------------------------------------------------------------------------
// 將怪物重生傳送給所有玩家
//-------------------------------------------------------------------------------
int SendNPCReliveToAll(TPOS_PACKET *packet)
{
	DWORD i;
	TPOS_COMPACKET	send_compacket;

	i = 0;
	CompressPacket(packet, &send_compacket);

	LOCK_CONNECTION(0);
    for(i=0; i<MAX_PLAYER_PER_ZONE; i++)
    {
        if(Pos_Cn[i].dwSocket!=0)
        {
            QueuePacket(&Pos_Cn[i], &send_compacket, CONNECTED_SERVER_ZONE);            
        }        
    } 
    UNLOCK_CONNECTION(0);
	return DLL_OK;
}
//-------------------------------------------------------------------------------
// 送出系統公告給全部玩家
//-------------------------------------------------------------------------------
int SendSystemMessageToAll(TPOS_PACKET *packet)
{
	DWORD i;
	TPOS_COMPACKET	send_compacket;

	i=0;	
	CompressPacket(packet, &send_compacket);
	LOCK_CONNECTION(0);
    for(i=0; i<MAX_PLAYER_PER_ZONE; i++)
    {
        if(Pos_Cn[i].dwSocket!=0)
        {
            QueuePacket(&Pos_Cn[i], &send_compacket, CONNECTED_SERVER_ZONE);            
        }        
    } 
    UNLOCK_CONNECTION(0);
	return DLL_OK;
}
//-------------------------------------------------------------------------------
// 送出系統公告
//-------------------------------------------------------------------------------
int  SendSystemMessage(TPOS_CN *cn)
{
	static TPOS_PACKET					send_packet;
	static TPOS_COMPACKET				send_compacket;
	TPOS_EVENT_SYSTEMMESSAGE	EventSystemMessage;
    int result;	

	send_packet.Header.dwType = SYSTEM_MESSAGE;
	send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_SYSTEMMESSAGE);
	strcpy(EventSystemMessage.WorldName, cWorldServerName);
	strcpy(EventSystemMessage.cMsg, cSystemMessage);
	memcpy(send_packet.data.cBuf, &EventSystemMessage, sizeof(TPOS_EVENT_SYSTEMMESSAGE));
		
	CompressPacket(&send_packet, &send_compacket);
    
    LOCK_CONNECTION(0);
	result = QueuePacket(cn, &send_compacket, CONNECTED_SERVER_ZONE);
    UNLOCK_CONNECTION(0);

    if( result )
        return  DLL_OK;
    else 
        return  DLL_ERROR;
}
//-------------------------------------------------------------------------------
// 送出玩家的技能
//-------------------------------------------------------------------------------
int SendCharacterSkill(DWORD index, TPOS_CN *cn)
{
	static TPOS_PACKET					send_packet;	
	static TPOS_COMPACKET				send_compacket;
	TPOS_EVENT_GETPLAYERSKILL	EventGetPlayerSkill;
    int							result, i;

	send_packet.Header.dwType = GET_PLAYER_SKILL;
	send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_GETPLAYERSKILL);

    LOCK_CHARACTER(index);
	for(i = 0;i < MAX_CHARACTER_SKILLS;i++)
	{
		EventGetPlayerSkill.SkillNo[i] = (SHINT)GetCharacterSkillNo(index, i);
		EventGetPlayerSkill.SkillLevel[i] = GetCharacterSkillLevel(index, i);
	}
	UNLOCK_CHARACTER(index);
	memcpy(send_packet.data.cBuf, &EventGetPlayerSkill, sizeof(TPOS_EVENT_GETPLAYERSKILL));
    
	CompressPacket(&send_packet, &send_compacket);

    LOCK_CONNECTION(0);
	result = QueuePacket(cn, &send_compacket, CONNECTED_SERVER_ZONE);
    UNLOCK_CONNECTION(0);
    
    if(result)
        return  DLL_OK;
    else
        return DLL_ERROR;
}
//-------------------------------------------------------------------------------
// 送出玩家的快捷技能和快捷物品
//-------------------------------------------------------------------------------
int SendCharacterQuickSkillItem(DWORD index, DWORD zonetype, TPOS_CN *cn)
{
	static TPOS_PACKET							send_packet;
	static TPOS_COMPACKET						send_compacket;
	TPOS_EVENT_GETPLAYERQUICKSKILLITEM	EventGetPlayerQuickSkillItem;
    int									result, i;
	TPOS_ITEM							tempitem;

	send_packet.Header.dwType = GET_PLAYER_QUICK_SKILLITEM;
	send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_GETPLAYERQUICKSKILLITEM);

    LOCK_CHARACTER(index);
	switch(zonetype)
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
		for(i = 0;i < MAX_CHARACTER_FN_SKILLS;i++)
		{
			EventGetPlayerQuickSkillItem.FnSkillNo[i] = GetCharacterLandFnSkillNo(index, i);
			EventGetPlayerQuickSkillItem.FnSkillHand[i] = (char)GetCharacterLandFnSkillHand(index, i);
		}
		EventGetPlayerQuickSkillItem.LeftSkillNo = GetCharacterLandLeftSkill(index);
		EventGetPlayerQuickSkillItem.RightSkillNo = GetCharacterLandRightSkill(index);		
		break;
	case SAIL_NORMAL:
	case SAIL_NEWBIE:
	case SAIL_PK:
	case SAIL_FINDGOLD:
	case SAIL_BIRTH:	
		for(i = 0;i < MAX_CHARACTER_FN_SKILLS;i++)
		{
			EventGetPlayerQuickSkillItem.FnSkillNo[i] = GetCharacterSeaFnSkillNo(index, i);
			EventGetPlayerQuickSkillItem.FnSkillHand[i] = (char)GetCharacterSeaFnSkillHand(index, i);
		}
		EventGetPlayerQuickSkillItem.LeftSkillNo = GetCharacterSeaLeftSkill(index);
		EventGetPlayerQuickSkillItem.RightSkillNo = GetCharacterSeaRightSkill(index);				
		break;
	}
	for(i = 0;i < MAX_CHARACTER_SASH_ITEMS;i++)
	{
		memset(&tempitem, 0x0, sizeof(TPOS_ITEM));
		GetCharacterSashItem(index, i, &tempitem);
		EventGetPlayerQuickSkillItem.SashItem[i] = tempitem.ID;
	}
	UNLOCK_CHARACTER(index);
	memcpy(send_packet.data.cBuf, &EventGetPlayerQuickSkillItem, sizeof(TPOS_EVENT_GETPLAYERQUICKSKILLITEM));

	CompressPacket(&send_packet, &send_compacket);

    // Jack, add lock here. [18:18,11/5/2002]
    LOCK_CONNECTION(0);
	result = QueuePacket(cn, &send_compacket, CONNECTED_SERVER_ZONE);
    UNLOCK_CONNECTION(0);

    if(result) 
        return DLL_OK;
    else
        return DLL_ERROR;
}
//---------------------------------------------------------------------------
// Send Current Weather To New Player
//-------------------------------------------------------------------------------
void SendCurrentWeatherToNewPlayer(TPOS_CN *cn)
{
    static TPOS_PACKET						send_packet;
	static TPOS_COMPACKET					send_compacket;
	TPOS_EVENT_INITZONEWEATHER		EventInitZoneWeather;
    int								result;
    
    send_packet.Header.dwType=INIT_ZONE_WEATHER;
    send_packet.Header.dwSize=sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_INITZONEWEATHER);
    LOCK_WEATHER(0);
    memcpy(&EventInitZoneWeather, ZoneWeather, sizeof(TPOS_ZONEWEATHER)); 
    UNLOCK_WEATHER(0);
	memcpy(send_packet.data.cBuf, &EventInitZoneWeather, sizeof(TPOS_EVENT_INITZONEWEATHER));
    
	CompressPacket(&send_packet, &send_compacket);

    // Jack, add lock here. [18:16,11/5/2002]
    LOCK_CONNECTION(0);
    result = QueuePacket(cn, &send_compacket, CONNECTED_SERVER_ZONE);
    UNLOCK_CONNECTION(0);

#ifdef  DEBUG_MSG
    SaveWorkToLog(cn->User.cId, inet_ntoa(cn->Addr.sin_addr), "GET_ZONE_NOW_WEATHER_OK");
    SaveMsgToLog("SYSTEM","SEND_ZONE_NOW_WEATHER_OK");
#endif//DEBUG_MSG
}
//-------------------------------------------------------------------------------
void	ServerSendChangeNpcDoing(DWORD Index, SLONG doingkind, LONG doingstep,
								 SLONG d1, SLONG d2, SLONG d3, SLONG d4, SLONG d5)
{
	static TPOS_PACKET	send_packet;
	TPOS_EVENT_GETCHANGENPCDOING	EventGetChangeNpcDoing;
	
	memset(&EventGetChangeNpcDoing, 0x0, sizeof(TPOS_EVENT_GETCHANGENPCDOING));
	send_packet.Header.dwType = CHANGE_NPC_DOING;
	send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_GETCHANGENPCDOING);
	EventGetChangeNpcDoing.Index = Index;
	EventGetChangeNpcDoing.DoingKind = doingkind;
	EventGetChangeNpcDoing.DoingStep = doingstep;
	EventGetChangeNpcDoing.d1 = d1; 
	EventGetChangeNpcDoing.d2 = d2; 
	EventGetChangeNpcDoing.d3 = d3; 
	EventGetChangeNpcDoing.d4 = d4;
	EventGetChangeNpcDoing.d5 = d5; 
	memcpy(send_packet.data.cBuf, &EventGetChangeNpcDoing, sizeof(TPOS_EVENT_GETCHANGENPCDOING));
	server_send_packet_to_all(&send_packet);
}
//-------------------------------------------------------------------------------
void	ServerSendUpdateNpcDoing(DWORD Index, SLONG doingkind, LONG doingstep,
								 SLONG d1, SLONG d2, SLONG d3, SLONG d4, SLONG d5)
{
	static TPOS_PACKET	send_packet;
	TPOS_EVENT_GETCHANGENPCDOING	EventGetChangeNpcDoing;
	
	memset(&EventGetChangeNpcDoing, 0x0, sizeof(TPOS_EVENT_GETCHANGENPCDOING));
	send_packet.Header.dwType = UPDATE_NPC_DOING;
	send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_GETCHANGENPCDOING);
	EventGetChangeNpcDoing.Index = Index;
	EventGetChangeNpcDoing.DoingKind = doingkind;
	EventGetChangeNpcDoing.DoingStep = doingstep;
	EventGetChangeNpcDoing.d1 = d1; 
	EventGetChangeNpcDoing.d2 = d2; 
	EventGetChangeNpcDoing.d3 = d3; 
	EventGetChangeNpcDoing.d4 = d4;
	EventGetChangeNpcDoing.d5 = d5; 
	memcpy(send_packet.data.cBuf, &EventGetChangeNpcDoing, sizeof(TPOS_EVENT_GETCHANGENPCDOING));
	server_send_packet_to_all(&send_packet);
}
//-------------------------------------------------------------------------------
void	ServerSendNpcAIBlock(SLONG	index, UHINT ai_block, SLONG dest_npc_no, SLONG x, SLONG y, 
							 SLONG z, UHINT skill_no)
{
	static TPOS_PACKET			send_packet;
	TPOS_EVENT_NOTIFYNPCAIBLOCK	EventNotifyNpcAIBlock;

	memset(&EventNotifyNpcAIBlock, 0x0, sizeof(TPOS_EVENT_NOTIFYNPCAIBLOCK));
	send_packet.Header.dwType = NOTIFY_NPC_AI_BLOCK;
	send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYNPCAIBLOCK);

	EventNotifyNpcAIBlock.Index = index;
	EventNotifyNpcAIBlock.AIBlock = ai_block;	
	EventNotifyNpcAIBlock.DestNpcNo = dest_npc_no;
	EventNotifyNpcAIBlock.X = x;
	EventNotifyNpcAIBlock.Y = y;
	EventNotifyNpcAIBlock.Z = z;
	EventNotifyNpcAIBlock.SkillNo = skill_no;

	memcpy(send_packet.data.cBuf, &EventNotifyNpcAIBlock, sizeof(TPOS_EVENT_NOTIFYNPCAIBLOCK));
	server_send_packet_to_all(&send_packet);
}
//-------------------------------------------------------------------------------
void	ServerSendMagicArea(CHAR Type, CHAR	Dir, SLONG X, SLONG Y, SLONG NpcNo, SLONG MagicNo)
{
	static TPOS_PACKET					send_packet;
	TPOS_EVENT_NOTIFYCREATEMAGICAREA	EventNotifyCreateMagicArea;

	memset(&EventNotifyCreateMagicArea, 0x0, sizeof(TPOS_EVENT_NOTIFYCREATEMAGICAREA));
	send_packet.Header.dwType = NOTIFY_CREATE_MAGIC_AREA;
	send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYCREATEMAGICAREA);

	EventNotifyCreateMagicArea.Dir = Dir;
	EventNotifyCreateMagicArea.Type = Type;
	EventNotifyCreateMagicArea.X = X;
	EventNotifyCreateMagicArea.Y = Y;
	EventNotifyCreateMagicArea.NpcNo = NpcNo;
	EventNotifyCreateMagicArea.MagicNo = (UHINT)MagicNo;

	memcpy(send_packet.data.cBuf, &EventNotifyCreateMagicArea, sizeof(TPOS_EVENT_NOTIFYCREATEMAGICAREA));
	server_send_packet_to_player(NpcNo, &send_packet);
	server_send_packet_to_teammember(NpcNo, &send_packet);
}
//-------------------------------------------------------------------------------
void	ServerSendPlayerJoinToOthers(TPOS_CN *cn, TPOS_PACKET *packet)
{
	static TPOS_PACKET		send_packet;
	static TPOS_COMPACKET	send_compacket;
	int				i;

	memcpy(&send_packet, packet, sizeof(*packet));

	CompressPacket(&send_packet, &send_compacket);

	LOCK_CONNECTION(0);
	for(i = 0; i < MAX_PLAYER_PER_ZONE; i++)
	{
		if(Pos_Cn[i].dwSocket != 0 && Pos_Cn[i].dwSocket != cn->dwSocket)
		{
			QueuePacket(&Pos_Cn[i], &send_compacket, CONNECTED_SERVER_ZONE);		
		}
	}
	UNLOCK_CONNECTION(0);
}
// ---------------------------------------------------------------------------
void SendRepeatLoginedPlayer(DWORD index, TPOS_PACKET *packet)
{	
	TPOS_COMPACKET	send_compacket;

	CompressPacket(packet, &send_compacket);
	LOCK_CONNECTION(0);
	QueuePacket(&Pos_Cn[index], &send_compacket, CONNECTED_SERVER_ZONE);
	UNLOCK_CONNECTION(0);
}
//-------------------------------------------------------------------------------
void	ServerSendNotifyBreakMagicToAll(SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG magic_index)
{
	static	TPOS_PACKET			send_packet;
	TPOS_EVENT_NOTIFYBREAKMAGIC	EventNotifyBreakMagic;	

	EventNotifyBreakMagic.npc_no = npc_no;
	EventNotifyBreakMagic.dest_x = dest_x;
	EventNotifyBreakMagic.dest_y = dest_y;
	EventNotifyBreakMagic.magic_index = magic_index;

	send_packet.Header.dwType = NOTIFY_BREAK_MAGIC;
	send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYBREAKMAGIC);
	memcpy(send_packet.data.cBuf, &EventNotifyBreakMagic, sizeof(TPOS_EVENT_NOTIFYBREAKMAGIC));

	server_send_packet_to_all(&send_packet);
}
//-------------------------------------------------------------------------------

