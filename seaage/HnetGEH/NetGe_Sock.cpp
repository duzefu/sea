// =============================================================================
// NetGe_Sock.cpp
// Psalm of Sea DDL Socket Function Source By Hawke Hsieh
// Last Modify Date : 2002.07.04
// =============================================================================
#include "HNETGEH.h"
#ifdef __NETGE_NETWORK__

#include "Netge_sock.h"

// -----------------------------------------------------------------------------
// 變數宣告
// -----------------------------------------------------------------------------
BOOL	bGSReadingNow = FALSE;

// =============================================================================
// -----------------------------------------------------------------------------
// SaveLog
// -----------------------------------------------------------------------------
void SaveMsgToLog(char *str)
{
 FILE	*f;   
   
 f = fopen("DLL_MSG.txt", "a+"); 
 fprintf(f,"%s : %s\n",
	       "DLL_REPORT",
		   str);
 fclose(f);
}
// -----------------------------------------------------------------------------
// 關閉一個Socket
// -----------------------------------------------------------------------------
int	CloseOneSocket(SOCKET tmp_socket)
{
	LINGER				linger;

	shutdown(tmp_socket, SD_BOTH);
	linger.l_onoff = true;
	linger.l_linger = 0;
	setsockopt(tmp_socket,  SOL_SOCKET, SO_LINGER, (LPSTR)&linger, sizeof(linger));
	closesocket(tmp_socket);

	return 1;
}
// -----------------------------------------------------------------------------
// 關閉一個連接
// -----------------------------------------------------------------------------
int	CloseOneConnection(TPOS_CN *cn)
{
	TPOS_BUFFER				*tmpbuf;

	CloseOneSocket(cn->dwSocket);

	while(cn->InBuf)
	{
		tmpbuf = cn->InBuf->next;
		GlobalFree(cn->InBuf);
		cn->InBuf = tmpbuf;
	}

	while(cn->OutBuf)
	{
		tmpbuf = cn->OutBuf->next;
		GlobalFree(cn->OutBuf);
		cn->OutBuf = tmpbuf;
	}	
	memset(cn, 0x0, sizeof(TPOS_CN));

	return 1;
}
// -----------------------------------------------------------------------------
// 排列封包
// -----------------------------------------------------------------------------
int QueuePacket(TPOS_CN *cn, TPOS_COMPACKET *compacket, HWND hwnd)
{	
	TPOS_BUFFER		    *tmpbuf;    
		
	if(!cn->OutBuf)
	{
		cn->OutBuf = (TPOS_BUFFER *)GlobalAlloc(GPTR, sizeof(TPOS_BUFFER));
		if(cn->OutBuf == NULL) return 0;		
        memcpy(cn->OutBuf->cBuf, compacket, compacket->Header.dwSize);
        cn->OutBuf->dwSize = compacket->Header.dwSize;		        
		cn->OutBuf->dwLocation = 0;
		cn->OutBuf->next = NULL;
	}
	else
	{
		for(tmpbuf = cn->OutBuf; tmpbuf->next; tmpbuf = tmpbuf->next);		
        if((MAX_PACKET_SIZE - tmpbuf->dwSize) < compacket->Header.dwSize)        
		{
			tmpbuf->next = (TPOS_BUFFER *)GlobalAlloc(GPTR, sizeof(TPOS_BUFFER));
			tmpbuf = tmpbuf->next;
			tmpbuf->dwSize = 0;
			tmpbuf->dwLocation = 0;
			tmpbuf->next = NULL;
		}		
        memcpy(tmpbuf->cBuf + tmpbuf->dwSize, compacket, compacket->Header.dwSize);
        tmpbuf->dwSize += compacket->Header.dwSize;        
	}
	
	PostMessage(hwnd, WM_ASYNCSELECT, (WPARAM)cn->dwSocket, WSAMAKESELECTREPLY(FD_WRITE, 0));

	return 1;
}
// -----------------------------------------------------------------------------
// 處理封包
// -----------------------------------------------------------------------------
int ProcessPacket(TPOS_CN *cn)
{
	static	TPOS_PACKET		recv_packet;
	static	TPOS_COMPACKET	recv_compacket;
	static	char			uncompressbuf[MAX_COMPACKET_SIZE - sizeof(DWORD)];
	TPOS_BUFFER		       *tmpbuf;	
	DWORD					uncomsize;
	
    memset(&recv_compacket, 0x0, sizeof(TPOS_COMPACKET));	    
	    
    memcpy(&recv_compacket, cn->InBuf->cBuf, ((TPOS_COMPACKETHEADER*)cn->InBuf->cBuf)->dwSize);    
	tmpbuf = cn->InBuf->next;
	GlobalFree(cn->InBuf);
	cn->InBuf = tmpbuf;
	
	uncomsize = recv_compacket.Header.dwSize - sizeof(DWORD);

	/*
#ifdef	_DEBUG
	char	log_str[256];
	static	ULONG	pack_count;
	sprintf((char*)log_str, "[%d]pack size:%d", pack_count, uncomsize);
	SaveMsgToLog((char *)log_str);
#endif//_DEBUG
	*/

	recv_packet.Header.dwSize = lzo_decompress(recv_compacket.cBuf, uncomsize, uncompressbuf);

	/*
#ifdef	_DEBUG
	sprintf((char*)log_str, "[%d]orig size:%d", pack_count, recv_packet.Header.dwSize);
	SaveMsgToLog((char *)log_str);
	pack_count++;
#endif//_DEBUG
	*/

	memcpy(&recv_packet, uncompressbuf, recv_packet.Header.dwSize);

	if(recv_packet.Header.dwVersion != CURRENT_VERSION) return 0;

	memcpy(&CurrentPacket, &recv_packet, recv_packet.Header.dwSize);
	// Jack,  [1/14/2003]
	// Want to send (data ptr, data type, data size)...
    //SendMessage(ParenthWnd, WM_POSGAMEEVENT, (WPARAM)&CurrentPacket.data.cBuf, recv_packet.Header.dwType);

	LPARAM	lParam;
	lParam = (recv_packet.Header.dwType & 0xffff) << 16;
	lParam |= recv_packet.Header.dwSize & 0xffff;
    SendMessage(ParenthWnd, WM_POSGAMEEVENT, (WPARAM)&CurrentPacket.data.cBuf, lParam);


	return 1;
}
// -----------------------------------------------------------------------------
// 讀取封包
// -----------------------------------------------------------------------------
int ReadPacket(TPOS_CN *cn)
{
	int			recv_count;

	if(!cn->InBuf)
	{
		cn->InBuf = (TPOS_BUFFER *)GlobalAlloc(GPTR, sizeof(TPOS_BUFFER));
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
		TotalRecvDataSize += cn->InBuf->dwSize;
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
		TotalSendDataSize += cn->OutBuf->dwSize;
		tmpbuf = cn->OutBuf->next;
		GlobalFree(cn->OutBuf);
		cn->OutBuf = tmpbuf;
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
						 if(!ReadPacket(CnDoor)) CloseOneConnection(CnDoor); 
						bGSReadingNow = FALSE;						
						break;

					case FD_WRITE:
						 if(!WritePacket(CnDoor)) CloseOneConnection(CnDoor);						 
						break;

					case FD_CLOSE:
						 g_dwConnectedServerType &= ~CONNECTED_SERVER_DOOR;	
						 LPARAM	lParam;
						 lParam = (DOOR_SERVER_CLOSED & 0xffff) << 16;
						 lParam |= 0 & 0xffff;
						 PostMessage(ParenthWnd, WM_POSGAMEEVENT, 0, lParam);						 
						 CloseOneConnection(CnDoor);
						 if(CnDoor) { GlobalFree(CnDoor); CnDoor=NULL;}    
						 DestroyWindow(DoorSockethWnd);
						 UnregisterClass(DoorClassName, dInstance);
						break;
				}
				return 0;

        case WM_DESTROY :
             return 0;
  }
  return DefWindowProc(hWnd, iMsg, wParam, lParam);
}
// -----------------------------------------------------------------------------
// 開啟一個新的且是隱藏的視窗，以收取 socket 的訊息 For DoorServer
// -----------------------------------------------------------------------------
BOOL WINAPI DoorSocketWndInit(void)
{
	WNDCLASS	wc;
	
	dInstance = (HINSTANCE)GetWindowLong(ParenthWnd, GWL_HINSTANCE);

	wc.style			= 0; 
	wc.lpfnWndProc		= (WNDPROC)DoorSocketWndProc;
	wc.cbClsExtra		= 0;
	wc.cbWndExtra		= 0;
	wc.hInstance		= dInstance;
	wc.hIcon			= NULL; 
	wc.hCursor			= NULL; 
	wc.hbrBackground	= NULL;
	wc.lpszMenuName     = NULL;
	wc.lpszClassName	= DoorClassName;

	if(!RegisterClass(&wc))
	{
		return FALSE;
	}

	DoorSockethWnd = CreateWindow(DoorClassName, "", 0L, 0, 0, 0, 0, NULL, NULL, dInstance, NULL);

	if(DoorSockethWnd == NULL)
	{
		UnregisterClass(DoorClassName, dInstance);
		return FALSE;
	}

	ShowWindow(DoorSockethWnd, SW_HIDE);
	UpdateWindow(DoorSockethWnd);

	return TRUE;
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
						 if(!ReadPacket(CnWorld)) CloseOneConnection(CnWorld); 
						bGSReadingNow = FALSE;						
						break;

					case FD_WRITE:
						 if(!WritePacket(CnWorld)) CloseOneConnection(CnWorld);						 
						break;

					case FD_CLOSE:
						 g_dwConnectedServerType &= ~CONNECTED_SERVER_WORLD;						 
						 // Warning 以後要改回 lParam 只送 EventType
						 LPARAM	lParam;
						 lParam = (WORLD_SERVER_CLOSED & 0xffff) << 16;
						 lParam |= 0 & 0xffff;
						 PostMessage(ParenthWnd, WM_POSGAMEEVENT, 0, lParam);						 
						 CloseOneConnection(CnWorld);
						 if(CnWorld) {GlobalFree(CnWorld); CnWorld=NULL;}   
						 DestroyWindow(WorldSockethWnd);
						 UnregisterClass(WorldClassName, wInstance);
						break;
				}
				return 0;

        case WM_DESTROY :
             return 0;
  }
  return DefWindowProc(hWnd, iMsg, wParam, lParam);
}
// -----------------------------------------------------------------------------
// 開啟一個新的且是隱藏的視窗，以收取 socket 的訊息 For WorldServer
// -----------------------------------------------------------------------------
BOOL WINAPI WorldSocketWndInit(void)
{
	WNDCLASS	wc;
	
	wInstance = (HINSTANCE)GetWindowLong(ParenthWnd, GWL_HINSTANCE);

	wc.style			= 0; 
	wc.lpfnWndProc		= (WNDPROC)WorldSocketWndProc;
	wc.cbClsExtra		= 0;
	wc.cbWndExtra		= 0;
	wc.hInstance		= wInstance;
	wc.hIcon			= NULL; 
	wc.hCursor			= NULL; 
	wc.hbrBackground	= NULL;
	wc.lpszMenuName     = NULL;
	wc.lpszClassName	= WorldClassName;

	if(!RegisterClass(&wc))
	{
		return FALSE;
	}

	WorldSockethWnd = CreateWindow(WorldClassName, "", 0L, 0, 0, 0, 0, NULL, NULL, wInstance, NULL);

	if(WorldSockethWnd == NULL)
	{
		UnregisterClass(WorldClassName, wInstance);
		return FALSE;
	}

	ShowWindow(WorldSockethWnd, SW_HIDE);
	UpdateWindow(WorldSockethWnd);

	return TRUE;
}

// -----------------------------------------------------------------------------
// Socket處理函式 For ZoneServer
// -----------------------------------------------------------------------------
LRESULT CALLBACK ZoneSocketWndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
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
						 if(!ReadPacket(CnZone)) CloseOneConnection(CnZone); 
						bGSReadingNow = FALSE;						
						break;

					case FD_WRITE:
						 if(!WritePacket(CnZone)) CloseOneConnection(CnZone);						 
						break;

					case FD_CLOSE:
						 g_dwConnectedServerType &= ~CONNECTED_SERVER_ZONE;						 
						 // Warning 以後要改回 lParam 只送 EventType
						 LPARAM	lParam;
						 lParam = (ZONE_SERVER_CLOSED & 0xffff) << 16;
						 lParam |= 0 & 0xffff;
						 PostMessage(ParenthWnd, WM_POSGAMEEVENT, 0, lParam);
						 CloseOneConnection(CnZone);
						 if(CnZone) {GlobalFree(CnZone); CnZone=NULL;}   
						 DestroyWindow(ZoneSockethWnd);
						 UnregisterClass(ZoneClassName, zInstance);
						 CloseOneConnection(CnZoneSync);
					     if(CnZoneSync) {GlobalFree(CnZoneSync); CnZoneSync=NULL;}
						 DestroyWindow(ZoneSyncSockethWnd);
					 	 UnregisterClass(ZoneSyncClassName, zsInstance);
						break;
				}
				return 0;

        case WM_DESTROY :
             return 0;
  }
  return DefWindowProc(hWnd, iMsg, wParam, lParam);
}
// -----------------------------------------------------------------------------
// 開啟一個新的且是隱藏的視窗，以收取 socket 的訊息 For ZoneServer
// -----------------------------------------------------------------------------
BOOL WINAPI ZoneSocketWndInit(void)
{
	WNDCLASS	wc;
	
	zInstance = (HINSTANCE)GetWindowLong(ParenthWnd, GWL_HINSTANCE);

	wc.style			= 0; 
	wc.lpfnWndProc		= (WNDPROC)ZoneSocketWndProc;
	wc.cbClsExtra		= 0;
	wc.cbWndExtra		= 0;
	wc.hInstance		= zInstance;
	wc.hIcon			= NULL; 
	wc.hCursor			= NULL; 
	wc.hbrBackground	= NULL;
	wc.lpszMenuName     = NULL;
	wc.lpszClassName	= ZoneClassName;

	if(!RegisterClass(&wc))
	{
		return FALSE;
	}

	ZoneSockethWnd = CreateWindow(ZoneClassName, "", 0L, 0, 0, 0, 0, NULL, NULL, zInstance, NULL);

	if(ZoneSockethWnd == NULL)
	{
		UnregisterClass(ZoneClassName, zInstance);
		return FALSE;
	}

	ShowWindow(ZoneSockethWnd, SW_HIDE);
	UpdateWindow(ZoneSockethWnd);

	return TRUE;
}
// -----------------------------------------------------------------------------
// Sync Socket處理函式 For ZoneServer Sync
// -----------------------------------------------------------------------------
LRESULT CALLBACK ZoneSyncSocketWndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	DWORD   AsyncEvent;

	switch (iMsg)
    {
		case WM_SYNC:
			    AsyncEvent = WSAGETSELECTEVENT(lParam);

			    switch(AsyncEvent)
				{
					case FD_READ:
						if(bGSReadingNow) break;
						bGSReadingNow = TRUE;
						 if(!ReadPacket(CnZoneSync)) CloseOneConnection(CnZoneSync); 
						bGSReadingNow = FALSE;						
						break;

					case FD_WRITE:
						 if(!WritePacket(CnZoneSync)) CloseOneConnection(CnZoneSync);						 
						break;

					case FD_CLOSE:

						break;
				}
				return 0;

        case WM_DESTROY :
             return 0;
  }
  return DefWindowProc(hWnd, iMsg, wParam, lParam);
}
// -----------------------------------------------------------------------------
// 開啟一個新的且是隱藏的視窗，以收取 socket 的訊息 For ZoneServer Sync
// -----------------------------------------------------------------------------
BOOL WINAPI ZoneSyncSocketWndInit(void)
{
	WNDCLASS	wc;
	
	zsInstance = (HINSTANCE)GetWindowLong(ParenthWnd, GWL_HINSTANCE);

	wc.style			= 0; 
	wc.lpfnWndProc		= (WNDPROC)ZoneSyncSocketWndProc;
	wc.cbClsExtra		= 0;
	wc.cbWndExtra		= 0;
	wc.hInstance		= zsInstance;
	wc.hIcon			= NULL; 
	wc.hCursor			= NULL; 
	wc.hbrBackground	= NULL;
	wc.lpszMenuName     = NULL;
	wc.lpszClassName	= ZoneSyncClassName;

	if(!RegisterClass(&wc))
	{
		return FALSE;
	}

	ZoneSyncSockethWnd = CreateWindow(ZoneSyncClassName, "", 0L, 0, 0, 0, 0, NULL, NULL, zsInstance, NULL);

	if(ZoneSyncSockethWnd == NULL)
	{
		UnregisterClass(ZoneSyncClassName, zsInstance);
		return FALSE;
	}

	ShowWindow(ZoneSyncSockethWnd, SW_HIDE);
	UpdateWindow(ZoneSyncSockethWnd);

	return TRUE;
}
//==============================================================================
#endif
