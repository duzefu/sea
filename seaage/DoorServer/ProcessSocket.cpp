//---------------------------------------------------------------------------
// Psalm of Sea DoorServer Process Socket
// By Hawke Hsieh 
// 2002-10-07
//---------------------------------------------------------------------------

#include "DoorServer_Def.h"

BOOL	bGSReadingNow = FALSE;
//extern  TODBC *ODBC;

//---------------------------------------------------------------------------
// Find Current Connection
//---------------------------------------------------------------------------
int FindCurrentConnection(WPARAM wParam)
{
    int i;
    
    for(i=0; i<MAX_PLAYER_PER_WORLD; i++)
    {
        if((WPARAM)Pos_Cn[i].dwSocket == wParam) 
        {
            return(i);
        }
    }
    return -1;
}
//---------------------------------------------------------------------------
// Find Connection By ID
//---------------------------------------------------------------------------
int FindConnectionByID(char *ID)
{
    int i;
    
    for(i=0; i<MAX_PLAYER_PER_DOOR; i++)
    {
        if(strcmp(Pos_Cn[i].User.cPw, ID)==0) 
        {
            return(i);
        }
    }
    return -1;
}
//-------------------------------------------------------------------------------
// 尋找可以供玩家使用的連接
//-------------------------------------------------------------------------------
int     FindUsableConnection(void)
{
    int i;

    for(i=0; i<MAX_PLAYER_PER_DOOR; i++)
    {
        if(Pos_Cn[i].dwSocket==0)
        {
            return(i);
        }
    }
    return  -1;
}
//-------------------------------------------------------------------------------
// 尋找是 World Server 的連接
//-------------------------------------------------------------------------------
int FindConnectionIsWorld(int index)
{
	// Jack, modified. [1/6/2003]
	int i, find_index;
	DWORD socket;

	find_index = -1;

	LOCK_CONNECTION(0);
	socket= Pos_Cn[index].dwSocket;
	UNLOCK_CONNECTION(0);    

	LOCK_WORLDINFO(0);
	for(i=0;i<MAX_WORLD_PER_DOOR; i++)
	{
		if(socket==WorldInfo[i].dwSocket)
		{		
			DeleteOneLVItem(hListViewWnd,WorldInfo[i].cName);
			find_index = i;
			break;
		}
	}
	UNLOCK_WORLDINFO(0);

	return find_index;
}
//-------------------------------------------------------------------------------
// 尋找該 Socket 值的連接
//-------------------------------------------------------------------------------
int FindConnectionBySocket(DWORD socket)
{
	int i;

    for(i=0; i<MAX_PLAYER_PER_DOOR; i++)
    {
	    if(Pos_Cn[i].dwSocket==socket)
		{
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
int QueuePacket(TPOS_CN *cn, TPOS_COMPACKET *compacket)
{
	TPOS_BUFFER	   *tmpbuf;			
	TPOS_COMPACKET	send_compacket;

	memcpy(&send_compacket, compacket, sizeof(TPOS_COMPACKET));

	if(!cn->OutBuf)
	{
		cn->OutBuf = (TPOS_BUFFER *)malloc(sizeof(TPOS_BUFFER));
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
			tmpbuf = tmpbuf->next;
			tmpbuf->dwSize = 0;
			tmpbuf->dwLocation = 0;
			tmpbuf->next = NULL;
		}
		//=====  Modify By Hawke Hsieh 20020617  =====
		memcpy(tmpbuf->cBuf + tmpbuf->dwSize, &send_compacket, send_compacket.Header.dwSize);
		tmpbuf->dwSize += send_compacket.Header.dwSize;    
	}
	PostMessage(DoorSockethWnd, WM_ASYNCSELECT, (WPARAM)cn->dwSocket, 
				WSAMAKESELECTREPLY(FD_WRITE, 0));	
	
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
        SaveMsgToLog(inet_ntoa(cn->Addr.sin_addr),  "Not my packet!!");    
        return 0;
    }	
    switch(recv_packet.Header.dwType)
    {
	case PLAYER_LOGIN:
		ServerDoPlayerLogin(cn, &recv_packet);
		break;

	case REGISTER_ACCOUNT_CHECK:
		ServerDoRegisterAccountCheck(cn, &recv_packet);
		break;

	case REGISTER_ACCOUNT_FINAL:
		ServerDoRegisterAccountFinal(cn, &recv_packet);
		break;
		
	case CHANGE_PROFILE:
		ServerDoChangeProfile(cn, &recv_packet);
		break;

	case CHANGE_PASSWORD:
		ServerDoChangePassword(cn, &recv_packet);
		break;

	case WORLD_LOGIN:
		ServerDoWorldServerLogin(cn, &recv_packet);
		break;

	case ZONE_LOGIN:
		ServerDoZoneServerLogin(cn, &recv_packet);
		break;		
		
	case NEW_WORLD_INFO:		
		ServerDoRecvWorldServerInfo(cn, &recv_packet);
		break;
		
	case REQUEST_WORLD_INFO:
		ServerDoRequestWorldServerInfo(cn, &recv_packet);
		break;
		
	case REFRESH_WORLD_INFO:
		ServerDoRefreshWorldServerInfo(cn, &recv_packet);
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
	SOCKET	tmp_socket;
	struct	sockaddr_in sa;
    int   	sa_len = sizeof(sa);
    int 	ci;
	int     t;
    BOOL	nodelay = TRUE;
	char    str[256];

	switch (iMsg)
    {
	case WM_ASYNCSELECT:
		AsyncEvent = WSAGETSELECTEVENT(lParam);
		
		switch(AsyncEvent)
		{
		case FD_ACCEPT:					
			tmp_socket = accept(Door->dwSocket, (struct sockaddr far *)&sa, &sa_len);			
			if(tmp_socket != INVALID_SOCKET)
			{
				int find_usable;
				struct in_addr temp_addr;
				LOCK_CONNECTION(0);
				find_usable = FindUsableConnection();
				UNLOCK_CONNECTION(0);			
				
				if(find_usable < 0)
                {
					CloseOneSocket(tmp_socket);
                }
				else
                {
					WSAAsyncSelect(tmp_socket, DoorSockethWnd, WM_ASYNCSELECT, FD_READ | FD_WRITE | FD_CLOSE);
					
					LOCK_CONNECTION(0);
					Pos_Cn[find_usable].dwSocket = tmp_socket;
					memcpy(&Pos_Cn[find_usable].Addr, &sa, sizeof(struct sockaddr_in));
					temp_addr =  Pos_Cn[find_usable].Addr.sin_addr;
					UNLOCK_CONNECTION(0);
					
					dwConnectedCounter++;
					dwOnlinePlayer++;
					sprintf(str,"Now Player : %d",dwOnlinePlayer);
					MsgOut(hStatusBarWnd,0,str);
					sprintf(str,"Connected : %d",dwConnectedCounter);
					MsgOut(hStatusBarWnd,2,str);
					dwOnlineCounter++;
					
					SaveConnectedCounter(dwConnectedCounter);
					SaveIOToLog(inet_ntoa(temp_addr),"Login");
				}
			}		
			//SaveMsgToLog("SYSTEM","FD_ACCEPT");
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
			//SaveMsgToLog("SYSTEM","FD_READ");
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
			//SaveMsgToLog("SYSTEM","FD_WRITE");
			break;
			
		case FD_CLOSE:			
			BOOL bwlc = FALSE;
			int  wlc = 0;
			
			LOCK_CONNECTION(0);
			ci = FindCurrentConnection(wParam);			
			UNLOCK_CONNECTION(0);			
			if(ci >= 0)
			{
				wlc = FindConnectionIsWorld(ci);
				if(wlc>=0)
				{
					LOCK_WORLDINFO(wlc);
					WorldInfo[wlc].dwIndex = 0;
					WorldInfo[wlc].dwSocket = 0;
					strcpy(str,WorldInfo[wlc].cName);
					UNLOCK_WORLDINFO(wlc);
					SendCloseWorldInfoToAll(str,ci);				
					LOCK_WORLDINFO(0);
					// Refresh WorldInfo Data
					for(t=wlc;t<iWorldCount;t++)
					{
						if(t==MAX_WORLD_PER_DOOR-1)
						{
							WorldInfo[t].dwSocket=0;
							WorldInfo[t].dwIndex=0;
							WorldInfo[t].dwPort=0;
							WorldInfo[t].dwPlayerCount=0;
							strcpy(WorldInfo[t].cName,"");
							strcpy(WorldInfo[t].cAddr,"");						
						}else
						{
							WorldInfo[t].dwSocket=WorldInfo[t+1].dwSocket;
							if(t==iWorldCount-1)
							{
								WorldInfo[t].dwIndex=0;
							}else
							{
								WorldInfo[t].dwIndex=WorldInfo[t+1].dwIndex-1;
							}					
							WorldInfo[t].dwPort=WorldInfo[t+1].dwPort;
							WorldInfo[t].dwPlayerCount=WorldInfo[t+1].dwPlayerCount;
							strcpy(WorldInfo[t].cName,WorldInfo[t+1].cName);
							strcpy(WorldInfo[t].cAddr,WorldInfo[t+1].cAddr);						
						}
					}             
					UNLOCK_WORLDINFO(0);								
					iWorldCount--;		
					sprintf(str, "Now World : %d",iWorldCount);
					MsgOut(hStatusBarWnd,1,str);
					SaveIOToLog("WORLD_SERVER","Logout");
				}else 
				{			
					dwOnlinePlayer--;				
					sprintf(str,"Now Player : %d",dwOnlinePlayer);
					MsgOut(hStatusBarWnd,0,str);
				}
				dwOnlineCounter--;			
				LOCK_CONNECTION(ci);
				// Player Logout				
				SaveIOToLog(inet_ntoa(Pos_Cn[ci].Addr.sin_addr),"Logout");
				strcpy(Pos_Cn[ci].User.cId,"");
				strcpy(Pos_Cn[ci].User.cPw,"");
				CloseOneConnection(&Pos_Cn[ci]);
				UNLOCK_CONNECTION(ci);			
				//SaveMsgToLog("SYSTEM","FD_CLOSE");
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
void SendCloseWorldInfoToAll(char *str,DWORD index)
{
	DWORD						i, j;
	TPOS_PACKET					send_packet;
	TPOS_COMPACKET				send_compacket;
	TPOS_EVENT_CLOSEWORLDINFO	closeworld;	
	j = 0;
	send_packet.Header.dwType=ONE_WORLD_CLOSE;
	send_packet.Header.dwSize=sizeof(TPOS_PACKETHEADER)+sizeof(TPOS_EVENT_CLOSEWORLDINFO);
	strcpy(closeworld.cName,str);

	memcpy(send_packet.data.cBuf, &closeworld,sizeof(TPOS_EVENT_CLOSEWORLDINFO));

	CompressPacket(&send_packet, &send_compacket);
	
	LOCK_CONNECTION(0);
	for(i=0; i<MAX_PLAYER_PER_DOOR; i++)
    {
		if(i!=index)
		{
			if(Pos_Cn[i].dwSocket!=0)
			{
				QueuePacket(&Pos_Cn[i], &send_compacket);
				j++;
			}
			if(j == dwOnlineCounter) break;
		}
    }
	UNLOCK_CONNECTION(0);
}
// -----------------------------------------------------------------------------
void SendNewWorldInfoToAll(char *str,DWORD playercount,char *addr,DWORD port,DWORD active)
{
	DWORD					i, j;
	TPOS_PACKET				send_packet;
	TPOS_COMPACKET			send_compacket;
	TPOS_EVENT_NEWWORLDINFO	EventNewWorldInfo;
	
	j = 0;
	send_packet.Header.dwType = NEW_WORLD_INFO;
	send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NEWWORLDINFO);
	
	strcpy(EventNewWorldInfo.cName, str);
	strcpy(EventNewWorldInfo.cAddr, addr);
	EventNewWorldInfo.dwPlayerCount = playercount;
	EventNewWorldInfo.dwPort = port;
	EventNewWorldInfo.dwActive = active;
	
	memcpy(send_packet.data.cBuf, &EventNewWorldInfo, sizeof(TPOS_EVENT_NEWWORLDINFO));

	CompressPacket(&send_packet, &send_compacket);
	
	LOCK_CONNECTION(0);
	for(i = 0; i < MAX_PLAYER_PER_DOOR; i++)
    {
		if(Pos_Cn[i].dwSocket != 0)
		{
			QueuePacket(&Pos_Cn[i], &send_compacket);
			j++;
		}
		if(j == dwOnlineCounter) break;
    }
	UNLOCK_CONNECTION(0);
}
// ---------------------------------------------------------------------------
void SendWorldRefreshInfoToAll(char *str,DWORD playercount,DWORD active)
{
	DWORD						i, j;
	TPOS_PACKET					send_packet;
	TPOS_EVENT_REFRESHWORLDINFO	refreshworld;
	TPOS_COMPACKET				send_compacket;
	
	j = 0;
	send_packet.Header.dwType = REFRESH_WORLD_INFO;
	send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER)+sizeof(TPOS_EVENT_REFRESHWORLDINFO);
	strcpy(refreshworld.cName, str);
	refreshworld.dwPlayerCount = playercount;
	refreshworld.dwActive = active;
	
	memcpy(send_packet.data.cBuf, &refreshworld, sizeof(TPOS_EVENT_REFRESHWORLDINFO));

	CompressPacket(&send_packet, &send_compacket);
	
	LOCK_CONNECTION(0);
	for(i = 0; i < MAX_PLAYER_PER_DOOR; i++)
    {
		if(Pos_Cn[i].dwSocket != 0)
		{
			QueuePacket(&Pos_Cn[i], &send_compacket);
			j++;
		}
		if(j == dwOnlineCounter) break;
    }
	UNLOCK_CONNECTION(0);
}
// ---------------------------------------------------------------------------
void CompressPacket(TPOS_PACKET	*packet, TPOS_COMPACKET *compacket)
{
	TPOS_PACKET		send_packet;	
	TPOS_COMPACKET	send_compacket;
	char			compressbuf[MAX_PACKET_SIZE - sizeof(DWORD)];
	DWORD			comsize;
	
	memcpy(&send_packet, packet, sizeof(TPOS_PACKET));
	send_packet.Header.dwVersion = CURRENT_VERSION;
	memcpy(compressbuf, &send_packet, send_packet.Header.dwSize);
	
	comsize = lzo_compress(compressbuf, send_packet.Header.dwSize, send_compacket.cBuf);
	send_compacket.Header.dwSize = comsize + sizeof(DWORD);
	
	memcpy(compacket, &send_compacket, sizeof(TPOS_COMPACKET));
}
// ---------------------------------------------------------------------------