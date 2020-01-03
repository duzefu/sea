//---------------------------------------------------------------------------
// Psalm of Sea WorldServer Doing Process
// By Hawke Hsieh 
// 2002-10-07
//---------------------------------------------------------------------------

#include "WorldServer_Def.h"

BOOL	bGSReadingNow = FALSE;

//---------------------------------------------------------------------------
// Find Current Connection
//---------------------------------------------------------------------------
int FindCurrentConnection(WPARAM wParam)
{
    int i, find_idx;

    find_idx = -1;
    for(i=0; i<MAX_PLAYER_PER_WORLD; i++)
    {
        if((WPARAM)Pos_Cn[i].dwSocket == wParam) 
        {
            find_idx = i;
            break;
        }
    }
    return find_idx;
}
// ------------------------------------------------------------------------------
// 尋找可以供玩家使用的連接
// ------------------------------------------------------------------------------
int     FindUsableConnection(void)
{
    int i;
    
    for(i=0; i<MAX_PLAYER_PER_WORLD; i++)
    {
        if(Pos_Cn[i].dwSocket==0)
        {
            return(i);            
        }
    }
    return  -1;
}
//-------------------------------------------------------------------------------
// 搜尋該連接是否為 Zone Server
//-------------------------------------------------------------------------------
DWORD FindConnectionIsZone(int index)
{
	DWORD i;		
	DWORD socket;
	
	LOCK_CONNECTION(0);
	socket= Pos_Cn[index].dwSocket;
	UNLOCK_CONNECTION(0);
	LOCK_ZONEINFO(0);
	for(i=0;i<MAX_ZONE_PER_WORLD; i++)
	{
		if(socket == ZoneInfo[i].dwSocket)
		{		
			DeleteOneLVItem(hListViewWnd,ZoneInfo[i].cName);
			return (i);				
		}		
	}
	UNLOCK_ZONEINFO(0);
	return -1;
}
//-------------------------------------------------------------------------------
// 搜尋該區域名稱的 Zone Server 連接
//-------------------------------------------------------------------------------
DWORD FindConnectionByZoneName(CHAR *zonename)
{
	DWORD i;	
	for(i=0;i<MAX_PLAYER_PER_WORLD;i++)
	{
		if(strcmp(Pos_Cn[i].User.cId, zonename)==0)
		{
			return(i);			
		}
	}
	return -1;
}
//-------------------------------------------------------------------------------
// 搜尋這個 Socket 值的連接
//-------------------------------------------------------------------------------
int FindConnectionBySocket(DWORD socket)
{
	int i;
    
	for(i=0; i<MAX_PLAYER_PER_WORLD; i++)
    {
	    if(Pos_Cn[i].dwSocket==socket)
		{
			return(i);		    
		}
    }
    return  -1;
}
//-------------------------------------------------------------------------------
// 搜尋該 ID 的連接
//-------------------------------------------------------------------------------
int FindConnectionByID(char *id)
{
	int i;
	
	for(i=0; i<MAX_PLAYER_PER_WORLD; i++)
    {
		if(strcmp(Pos_Cn[i].User.cId,id)==0)
	    {
			return(i);		    
		}
    }
    return  -1;
}
//-------------------------------------------------------------------------------
// 關掉舊的連接
//-------------------------------------------------------------------------------
int CloseOldConnection(CHAR *ID)
{
	int i;
    
	for(i=0; i<MAX_PLAYER_PER_WORLD; i++)
    {
	    if(Pos_Cn[i].User.cId == ID)
		{	
			dwOnlineCounter--;
			dwOnlineLoginer--;
			CloseOneConnection(&Pos_Cn[i]);
			return(i);		    
		}
    }
    return  -1;
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
	ProcessPacket(cn);    

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
 TPOS_BUFFER   *tmpbuf;
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
   } 

   return 1;
}
//---------------------------------------------------------------------------
// Process Packet
//---------------------------------------------------------------------------
int ProcessPacket(TPOS_CN *cn)
{
	TPOS_COMPACKET		recv_compacket;
	TPOS_PACKET			recv_packet;
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
	case DOOR_LOGIN_OK:
		ServerDoDoorLoginOK(cn, &recv_packet);
		break;
		// QQ
	case QQ_PLAYER_LOGIN:
		ServerDoQQPlayerLogin(cn, &recv_packet);
		break;
	case QQ_PLAYER_LOGOUT:
		ServerDoQQPlayerLogout(cn, &recv_packet);
		break;
	case QQ_REQUEST_FRIEND_LIST:
		ServerDoQQRequestFriendList(cn, &recv_packet);
		break;
	case QQ_REQUEST_GUILD_FRIEND_LIST:
		ServerDoQQRequestGuildFriendList(cn, &recv_packet);
		break;
	case QQ_SEND_2ONE_MSG:
		ServerDoQQsend2OneMsg(cn, &recv_packet);
		break;
	case QQ_SEND_2SOME_MSG:
		//ServerDoQQSend2SomeMsg(cn, &recv_packet);
		break;	
	case QQ_REQUEST_PLAYER_COUNT:
		ServerDoQQRequestPlayerCount(cn, &recv_packet);
		break;
	case QQ_SET_MYSTATE:
		ServerDoQQSetMyState(cn, &recv_packet);
		break;
	case QQ_REQUEST_QUERY_ADD_LIST:
		ServerDoQQRequestQueryAddList(cn, &recv_packet);
		break;
	case QQ_REQUEST_QUERY_ONLINE_ADDLIST:
		ServerDoQQRequestQueryOnlineAddList(cn, &recv_packet);
		break;
	case QQ_REQUEST_ADD_SOMEONE:
		ServerDoQQRequestAddSomeone(cn, &recv_packet);
		break;
	case QQ_REQUEST_QUERY_SOMEONE:
		ServerDoQQRequestQuerySomeone(cn, &recv_packet);
		break;
	case QQ_REQUEST_DEL_FRIEND:
		ServerDoQQRequestDeleteFriend(cn, &recv_packet);
		break;
	case QQ_REQUEST_DEL_GUILD_FRIEND:
		ServerDoQQRequestDeleteGuildFriend(cn, &recv_packet);
		break;
	case QQ_REQUEST_TRANSFER_ITEM:
		ServerDoQQRequestTransferItem(cn, &recv_packet);		
		break;
	case QQ_TRANSFER_ITEM_OK:
		ServerDoQQTransferItemOK(cn, &recv_packet);		
		break;
	case QQ_TRANSFER_ITEM_FAIL:
		ServerDoQQTransferItemFail(cn, &recv_packet);		
		break;
		// 玩家登入
	case PLAYER_LOGIN:
		ServerDoPlayerLogin(cn, &recv_packet);
		break;
		// 玩家要求角色資料
	case REQUEST_CHARACTER_INFO:
		ServerDoRequestCharacterInfo(cn, &recv_packet);
		break;
		// 玩家要求創見角色初始值
	case REQUEST_CHARACTER_DEFAULT:
		ServerDoRequestCharacterDefault(cn, &recv_packet);
		break;
		// 玩家創建角色檢查名稱是否有重複
	case CREATE_CHARACTER_CHECK:
		ServerDoCreateCharacterCheck(cn, &recv_packet);
		break;
		// 玩家創建角色
	case CREATE_CHARACTER_FINAL:
		ServerDoCreateCharacterFinal(cn, &recv_packet);
		break;
		// 玩家刪除角色
	case DELETE_CHARACTER:
		ServerDoDeleteCharacter(cn, &recv_packet);
		break;
		// 玩家選擇角色
	case CHARACTER_SELECTED:
		ServerDoCharacterSelected(cn, &recv_packet);
		break;	
		// 區域伺服器登入
	case ZONE_LOGIN:
		ServerDoZoneLogin(cn, &recv_packet);
		break;
		// 區域伺服器送出資訊
	case SEND_ZONE_INFO:
		ServerDoNewZoneInfo(cn, &recv_packet);
		break;
		// 區域伺服器要求其他區域伺服器的資訊
	case REQUEST_ZONE_INFO:
		ServerDoRequestZoneInfo(cn, &recv_packet);
		break;
		// 更新區域伺服器的資訊
	case REFRESH_ZONE_INFO:
		ServerDoRefreshZoneInfo(cn, &recv_packet);
		break;
		// 玩家要求登入區域伺服器
	case PLAYER_REQUEST_LOGIN_ZONE:
		ServerDoPlayerRequestLoginZone(cn, &recv_packet);
		break;
		// 組隊
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
	case ZONE_NOTIFY_SOMEONE_WANT_JOIN_TEAM:
		ServerDoZoneNotifySomeoneWantJoinTeam(cn, &recv_packet);
		break;
	case ZONE_NOTIFY_JOIN_TEAM_FULL:
		ServerDoZoneNotifyJoinTeamFull(cn, &recv_packet);
		break;	
	case ZONE_NOTIFY_SOMEONE_JOIN_TEAM:
		ServerDoZoneNotifySomeoneJoinTeam(cn, &recv_packet);
		break;
	case ZONE_NOTIFY_SOMEONE_EXIT_TEAM:
		ServerDoZoneNotifySomeoneExitTeam(cn, &recv_packet);
		break;
	case ZONE_NOTIFY_KICKED_FROM_TEAM:
		ServerDoZoneNotifyKickFromTeam(cn, &recv_packet);
		break;
	case ZONE_NOTIFY_TEAM_MEMBER_INFO:
		ServerDoZoneNotifyTeamMemberInfo(cn, &recv_packet);
		break;
	case ZONE_NOTIFY_TEAM_MEMBER_CHANGEZONE:
		ServerDoZoneNotifyTeamMemberChangeZone(cn, &recv_packet);
		break;
    }
	return 1;
}
// -----------------------------------------------------------------------------
// Socket處理函式 For WorldServer
// -----------------------------------------------------------------------------
LRESULT CALLBACK WorldSocketWndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	DWORD   AsyncEvent;
	SOCKET	tmp_socket;
	struct	sockaddr_in sa;
    int   	sa_len = sizeof(sa);
    int   	ci;
	int   t;
    BOOL	nodelay = TRUE;
	char    str[256];

	switch (iMsg)
    {
	case WM_ASYNCSELECT:
		AsyncEvent = WSAGETSELECTEVENT(lParam);
		
		switch(AsyncEvent)
		{
		case FD_ACCEPT:					
			tmp_socket = accept(World->dwSocket, (struct sockaddr far *)&sa, &sa_len);			
			if(tmp_socket != INVALID_SOCKET)
			{
				int find_usable;
				struct in_addr temp_addr;
				LOCK_CONNECTION(0);
				find_usable = FindUsableConnection();
				UNLOCK_CONNECTION(0);			
				
				if(find_usable < 0)
                {
					LOCK_CONNECTION(0);
					CloseOneSocket(tmp_socket);
					UNLOCK_CONNECTION(0);
                }
				else
                {
					WSAAsyncSelect(tmp_socket, WorldSockethWnd, WM_ASYNCSELECT, FD_READ | FD_WRITE | FD_CLOSE);
					
					LOCK_CONNECTION(0);
					Pos_Cn[find_usable].dwSocket = tmp_socket;
					memcpy(&Pos_Cn[find_usable].Addr, &sa, sizeof(struct sockaddr_in));
					temp_addr =  Pos_Cn[find_usable].Addr.sin_addr;
					UNLOCK_CONNECTION(0);
					
					dwConnectedCounter++;
					dwOnlineLoginer++;
					sprintf(str, "Now Login : %d", dwOnlineLoginer);
					MsgOut(hStatusBarWnd, 0, str);
					sprintf(str, "Connected : %d", dwConnectedCounter);
					MsgOut(hStatusBarWnd, 5, str);
					dwOnlineCounter++;
					if(dwOnlineLoginer > dwOnlineMaxLoginer)
					{
						dwOnlineMaxLoginer++;
						SaveMaxLoginer();
						sprintf(str, "Max Login : %d", dwOnlineMaxLoginer);
						MsgOut(hStatusBarWnd,2, str);
					}					
					RefreshAllWorldPlayer();
					SaveConnectedCounter(dwConnectedCounter);
					SaveIOToLog(inet_ntoa(temp_addr),"Login");
				}
			}		
			break;
		case FD_READ:
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
					CloseOneConnection(&Pos_Cn[ci]);
				}
				bGSReadingNow = FALSE;
				UNLOCK_CONNECTION(ci);
			}						
			break;
			
		case FD_WRITE:
			LOCK_CONNECTION(0);
			ci = FindCurrentConnection(wParam);
			UNLOCK_CONNECTION(0);
			if(ci >= 0)
			{
				LOCK_CONNECTION(ci);				                                               
				if(!WritePacket(&Pos_Cn[ci])) 
				{
					CloseOneConnection(&Pos_Cn[ci]);
				}
				UNLOCK_CONNECTION(ci);
			}					 
			break;
			
		case FD_CLOSE:			
			BOOL bzlc = FALSE;
			int  zlc = 0;
			
			LOCK_CONNECTION(0);
			ci = FindCurrentConnection(wParam);			
			UNLOCK_CONNECTION(0);	
			if(ci >= 0)
			{
				zlc = FindConnectionIsZone(ci);							
				if(zlc >= 0)
				{
					LOCK_ZONEINFO(zlc);
					ZoneInfo[zlc].dwIndex = 0;
					ZoneInfo[zlc].dwSocket = 0;
					strcpy(str, ZoneInfo[zlc].cName);
					UNLOCK_ZONEINFO(zlc);
					SendCloseZoneInfoToAll(str, ci);				
					LOCK_ZONEINFO(0);
					// Refresh ZoneInfo Data
					for(t = zlc;t < iZoneCount;t++)
					{
						if(t == MAX_ZONE_PER_WORLD - 1)
						{
							memset(&ZoneInfo[t], 0x0, sizeof(TPOS_ZONEINFO));
						}else
						{
							ZoneInfo[t].dwSocket = ZoneInfo[t+1].dwSocket;
							if(t == iZoneCount - 1)
							{
								ZoneInfo[t].dwIndex = 0;
							}else
							{
								ZoneInfo[t].dwIndex = ZoneInfo[t+1].dwIndex-1;
							}					
							ZoneInfo[t].dwPort = ZoneInfo[t+1].dwPort;
							ZoneInfo[t].dwPlayerCount = ZoneInfo[t+1].dwPlayerCount;
							strcpy(ZoneInfo[t].cName, ZoneInfo[t+1].cName);
							strcpy(ZoneInfo[t].cAddr, ZoneInfo[t+1].cAddr);
							strcpy(ZoneInfo[t].cMapName, ZoneInfo[t+1].cMapName);
							memcpy(ZoneInfo[t].QQOnlinePlayerList, 
								   ZoneInfo[t+1].QQOnlinePlayerList, 
								   sizeof(TPOS_QQ_ONLINE_PLAYER_LIST));
						}
					}             
					UNLOCK_ZONEINFO(0);								
					iZoneCount--;		
					sprintf(str, "Now Zone : %d", iZoneCount);
					MsgOut(hStatusBarWnd, 4, str);
					SaveIOToLog("ZONE_SERVER", "Logout");
				}else
				{
					dwOnlineLoginer--;				
					sprintf(str,"Now Login : %d",dwOnlineLoginer);
					MsgOut(hStatusBarWnd,0,str);
				}
				dwOnlineCounter--;
				LOCK_CONNECTION(ci);
				// Player Logout				
				SaveIOToLog(inet_ntoa(Pos_Cn[ci].Addr.sin_addr),"Logout");				
				CloseOneConnection(&Pos_Cn[ci]);
				UNLOCK_CONNECTION(ci);
				// Send Player Logout Message To Door Server				
				RefreshAllWorldPlayer();			
			}
			break;
		}
		return 0;
		
        case WM_DESTROY :
			return 0;
	}
	return DefWindowProc(hWnd, iMsg, wParam, lParam);
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
void RefreshAllWorldPlayer()
{
	int							i,t;
	int							tempcount;
	char						tempbuf[56];
	int							zone_count;
	TPOS_PACKET			send_packet;
	TPOS_COMPACKET		send_compacket;
	TPOS_EVENT_REFRESHWORLDINFO	EventRefreshWorldInfo;

	i = 0;
	tempcount = 0;
	memset(tempbuf, 0, 56);
	dwOnlineAllWorldPlayer = 0;
	LOCK_ZONEINFO(0);
	for(zone_count = 0;zone_count < MAX_ZONE_PER_WORLD;zone_count++)
	{
		if(ZoneInfo[zone_count].dwSocket != 0)
		{
			dwOnlineAllWorldPlayer += ZoneInfo[zone_count].dwPlayerCount;
		}		
	}
	UNLOCK_ZONEINFO(0);
	
	i = GetLVItemCount(hListViewWnd);
	for(t = 0;t < i;t++)
	{
		GetOneLVItem(hListViewWnd, tempbuf, t, 1, 56);
		tempcount = atoi(tempbuf);
		//dwOnlineAllWorldPlayer += tempcount;
	}	
	dwOnlineAllWorldPlayer += dwOnlineLoginer;	
	sprintf(tempbuf, "Now All World Player : %d", dwOnlineAllWorldPlayer);
    MsgOut(hStatusBarWnd, 1, tempbuf);	
	
	if(dwOnlineAllWorldPlayer > dwOnlineAllWorldMaxPlayer)
	{
		dwOnlineAllWorldMaxPlayer = dwOnlineAllWorldPlayer;
		sprintf(tempbuf, "Max All World Player : %d", dwOnlineAllWorldMaxPlayer);
        MsgOut(hStatusBarWnd, 3, tempbuf);
		SaveMaxPlayer();
	}

	strcpy(EventRefreshWorldInfo.cName, WorldServerName);
	EventRefreshWorldInfo.dwPlayerCount = dwOnlineAllWorldPlayer;
		
	send_packet.Header.dwType = REFRESH_WORLD_INFO;
	send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_REFRESHWORLDINFO);
	memcpy(&send_packet.data.cBuf, &EventRefreshWorldInfo, sizeof(TPOS_EVENT_REFRESHWORLDINFO));

	CompressPacket(&send_packet, &send_compacket);
	
	QueuePacket(Door, &send_compacket, CONNECTED_SERVER_DOOR);	
}
//---------------------------------------------------------------------------
void SendNewZoneInfoToAll(char *str,DWORD playercount,char *addr,DWORD port,char *mapname,DWORD zonetype)
{
	int							i, j;
	TPOS_PACKET			send_packet;
	TPOS_COMPACKET		send_compacket;
	TPOS_EVENT_NEWZONEINFO		EventNewZoneInfo;
	DWORD						tempsocket; 
	
	j = 0;
	
	strcpy(EventNewZoneInfo.cName, str);
	strcpy(EventNewZoneInfo.cMapName, mapname);
	strcpy(EventNewZoneInfo.cAddr, addr);
	EventNewZoneInfo.dwPlayerCount = playercount;
	EventNewZoneInfo.dwPort = port;
	EventNewZoneInfo.dwType = zonetype;

	send_packet.Header.dwType = NEW_ZONE_INFO;
	send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NEWZONEINFO);
	memcpy(&send_packet.data.cBuf, &EventNewZoneInfo, sizeof(TPOS_EVENT_NEWZONEINFO));

	CompressPacket(&send_packet, &send_compacket);

	for(j=0;j<MAX_ZONE_PER_WORLD;j++)
	{	 
		LOCK_ZONEINFO(j);
		tempsocket=ZoneInfo[j].dwSocket;
		UNLOCK_ZONEINFO(j);
		LOCK_CONNECTION(0);	
		i = FindConnectionBySocket(tempsocket);	 
		QueuePacket(&Pos_Cn[i], &send_compacket,CONNECTED_SERVER_WORLD);
		UNLOCK_CONNECTION(0);
		if(j == iZoneCount) break;
	} 
}
//---------------------------------------------------------------------------
void SendZoneRefreshInfoToAll(char *str,DWORD playercount)
{
	int 						i, j;
	TPOS_PACKET			send_packet;
	TPOS_COMPACKET		send_compacket;
	TPOS_EVENT_REFRESHZONEINFO	EventRefreshZoneInfo;
	DWORD						tempsocket;
	
	j = 0;

	strcpy(EventRefreshZoneInfo.cName, str);
	EventRefreshZoneInfo.dwPlayerCount = playercount;

	send_packet.Header.dwType = REFRESH_ZONE_INFO;
	send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER)+sizeof(TPOS_EVENT_REFRESHZONEINFO);
	memcpy(&send_packet.data.cBuf, &EventRefreshZoneInfo, sizeof(TPOS_EVENT_REFRESHZONEINFO));
	
	CompressPacket(&send_packet, &send_compacket);

	for(j=0;j<MAX_ZONE_PER_WORLD;j++)
	{	 
		LOCK_ZONEINFO(j);
		tempsocket = ZoneInfo[j].dwSocket;
		UNLOCK_ZONEINFO(j);
		LOCK_CONNECTION(0);	
		i = FindConnectionBySocket(tempsocket);	 
		QueuePacket(&Pos_Cn[i], &send_compacket,CONNECTED_SERVER_WORLD);
		UNLOCK_CONNECTION(0);
		if(j == iZoneCount) break;
	} 
}
// ---------------------------------------------------------------------------
void SendSystemMessageToAll(char *msg)
{
	int 						i, j;
	TPOS_PACKET			send_packet;
	TPOS_COMPACKET		send_compacket;
	TPOS_EVENT_SYSTEMMESSAGE	EventSystemMessage;
	DWORD						tmpsocket;
	
	j = 0;
	
	strcpy(EventSystemMessage.WorldName, WorldServerName);
	strcpy(EventSystemMessage.cMsg ,msg);
	
	send_packet.Header.dwType = SYSTEM_MESSAGE;
	send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_SYSTEMMESSAGE);
	memcpy(&send_packet.data.cBuf, &EventSystemMessage, sizeof(TPOS_EVENT_SYSTEMMESSAGE));

	CompressPacket(&send_packet, &send_compacket);
	
	for(j = 0 ; j < MAX_ZONE_PER_WORLD ; j++)
	{
		LOCK_ZONEINFO(0);
		tmpsocket = ZoneInfo[j].dwSocket;
		UNLOCK_ZONEINFO(0);		
		LOCK_CONNECTION(0);	 
		i = FindConnectionBySocket(tmpsocket);	 
		QueuePacket(&Pos_Cn[i], &send_compacket, CONNECTED_SERVER_WORLD);
		UNLOCK_CONNECTION(0);
		if(j == iZoneCount) break;
	}
}
// ---------------------------------------------------------------------------
void SendCloseZoneInfoToAll(char *str,DWORD index)
{
	int 						i, j;
	TPOS_PACKET			send_packet;
	TPOS_COMPACKET		send_compacket;
	TPOS_EVENT_CLOSEZONEINFO	EventCloseZoneInfo;
	DWORD						tempsocket;
	
	j = 0; 
	
	strcpy(EventCloseZoneInfo.cName, str);
	
	send_packet.Header.dwType = ONE_ZONE_CLOSE;
	send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_CLOSEZONEINFO); 
	
	memcpy(&send_packet.data.cBuf, &EventCloseZoneInfo, sizeof(TPOS_EVENT_CLOSEZONEINFO));
	
	CompressPacket(&send_packet, &send_compacket);
	
	for(j=0;j<MAX_ZONE_PER_WORLD;j++)
	{	 
		LOCK_ZONEINFO(j);
		tempsocket = ZoneInfo[j].dwSocket;
		UNLOCK_ZONEINFO(j);
		LOCK_CONNECTION(0);	
		i = FindConnectionBySocket(tempsocket);	 
		QueuePacket(&Pos_Cn[i], &send_compacket, CONNECTED_SERVER_WORLD);
		UNLOCK_CONNECTION(0);
		if(j == iZoneCount) break;
	} 
}
// ---------------------------------------------------------------------------
void SendRepeatLoginedPlayer(DWORD index, TPOS_PACKET *packet)
{	
	TPOS_COMPACKET	send_compacket;

	CompressPacket(packet, &send_compacket);
	LOCK_CONNECTION(0);
	QueuePacket(&Pos_Cn[index], &send_compacket, CONNECTED_SERVER_WORLD);
	UNLOCK_CONNECTION(0);
}
// ---------------------------------------------------------------------------
int  ServerSendPacketToOne(void *connect, void *packet)
{
	TPOS_PACKET *send_packet = (TPOS_PACKET *)packet;
	TPOS_COMPACKET	send_compacket;
    TPOS_CN		*send_conn = (TPOS_CN *)connect;
    int result;

	CompressPacket(send_packet, &send_compacket);

    LOCK_CONNECTION(0);
    result = QueuePacket(send_conn, &send_compacket, CONNECTED_SERVER_WORLD);
    UNLOCK_CONNECTION(0);

    if(result)
        return  DLL_OK;
    else
        return  DLL_ERROR;
}
// ---------------------------------------------------------------------------
void CompressPacket(TPOS_PACKET	*packet, TPOS_COMPACKET *compacket)
{
	TPOS_PACKET		send_packet;	
	TPOS_COMPACKET	send_compacket;
	char				compressbuf[MAX_PACKET_SIZE - sizeof(DWORD)];
	DWORD			comsize;
	
	memcpy(&send_packet, packet, sizeof(TPOS_PACKET));
	send_packet.Header.dwVersion = CURRENT_VERSION;
	memcpy(compressbuf, &send_packet, send_packet.Header.dwSize);
	
	comsize = lzo_compress(compressbuf, send_packet.Header.dwSize, send_compacket.cBuf);
	send_compacket.Header.dwSize = comsize + sizeof(DWORD);
	
	memcpy(compacket, &send_compacket, sizeof(TPOS_COMPACKET));
}
// ---------------------------------------------------------------------------