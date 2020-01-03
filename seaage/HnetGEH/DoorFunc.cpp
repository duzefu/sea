// =============================================================================
// DoorFunc.cpp
// Psalm of Sea DDL Door Server Function Source By Hawke Hsieh
// Last Modify Date : 2001.12.28
// =============================================================================

#include "HNETGEH.h"
#ifdef __NETGE_NETWORK__

#include "Netge_Extern.h"
// -----------------------------------------------------------------------------
// Login Door Server
// -----------------------------------------------------------------------------
#ifdef BCBUSED
int _PosLoginDoor(HWND hWnd, char FAR *ServerName, int port, char *id, char *Password,DWORD Version)
#else
NETGE_API int NETGE_FNB PosLoginDoor(HWND hWnd, char FAR *ServerName, int port, char *id, char *Password,DWORD Version)
#endif
{
	int					iRet;
	TPOS_EVENT_LOGIN	EventLogin;
	DWORD				dwSize;
	char				PacketData[MAX_PACKET_SIZE - sizeof(TPOS_PACKETHEADER)];

	if(g_dwConnectedServerType&CONNECTED_SERVER_DOOR)return DLL_OK;
	
    // 檢查是否有輸入參數
	if(ServerName == NULL || Password == NULL) return DLL_ERROR;
	
	// 保留父視窗的 hwnd
	ParenthWnd = hWnd; 
	
	_snprintf(DoorServerAddr, 15, "%s", ServerName);
	
    CnDoor = (TPOS_CN *)GlobalAlloc(GPTR, sizeof(TPOS_CN));
	FillMemory(CnDoor, 0x0, sizeof(TPOS_CN));
    
	CnDoor->dwSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(CnDoor->dwSocket == INVALID_SOCKET)
	{ 
		CloseOneConnection(CnDoor);
		if(CnDoor)
		{
			GlobalFree(CnDoor);
			CnDoor = NULL;
		}	    
		return -2;
	}
    
	iRet = 1;
    setsockopt(CnDoor->dwSocket, SOL_SOCKET, SO_DONTLINGER, (char *)&iRet, sizeof(iRet));
	
    CnDoor->Addr.sin_family       = AF_INET;
    CnDoor->Addr.sin_port         = htons(port);
    CnDoor->Addr.sin_addr.s_addr  = inet_addr(DoorServerAddr);
    iRet = connect(CnDoor->dwSocket, (struct sockaddr far *)&CnDoor->Addr, sizeof(struct sockaddr_in));
    if(iRet == SOCKET_ERROR)
	{
		CloseOneConnection(CnDoor);
		if(CnDoor) { GlobalFree(CnDoor); CnDoor=NULL;}	    
		return CANT_CONNECTED;
	}
	
    if(DoorSocketWndInit() == FALSE) return 0;
	
    iRet = WSAAsyncSelect(CnDoor->dwSocket, DoorSockethWnd, WM_ASYNCSELECT, FD_READ | FD_WRITE | FD_CLOSE);
    if(iRet == SOCKET_ERROR)
	{
		CloseOneConnection(CnDoor);
		if(CnDoor) { GlobalFree(CnDoor); CnDoor=NULL;}	    
		return CANT_ASYNC;
	}    

	strcpy(EventLogin.cId,id);
	strcpy(EventLogin.cPw,Password);
	EventLogin.dwVersion = Version;
	memcpy(PacketData,&EventLogin,sizeof(TPOS_EVENT_LOGIN));
	dwSize = sizeof(TPOS_EVENT_LOGIN);
	
	g_dwConnectedServerType |= CONNECTED_SERVER_DOOR;

	#ifdef BCBUSED
    _PosSendDataToDoor(PLAYER_LOGIN,PacketData,dwSize);
    #else
	PosSendDataToDoor(PLAYER_LOGIN,PacketData,dwSize);
    #endif  	    
	
	return DLL_OK;		
}
// -----------------------------------------------------------------------------
// Logout Door Server
// -----------------------------------------------------------------------------
#ifdef BCBUSED
int _PosLogoutDoor()
#else
NETGE_API int NETGE_FNB PosLogoutDoor()
#endif
{
	if(!(g_dwConnectedServerType&CONNECTED_SERVER_DOOR))return DLL_OK;      
	CloseOneConnection(CnDoor);
	if(CnDoor) { GlobalFree(CnDoor); CnDoor=NULL;}    
	DestroyWindow(DoorSockethWnd);
	UnregisterClass(DoorClassName, dInstance);

	g_dwConnectedServerType &= ~CONNECTED_SERVER_DOOR;
	return DLL_OK;
}
// -----------------------------------------------------------------------------
// Send Data To Door Server
// -----------------------------------------------------------------------------
#ifdef BCBUSED
int _PosSendDataToDoor(DWORD dwEventType, char FAR *cData, DWORD dwSize)
#else
NETGE_API int NETGE_FNB PosSendDataToDoor(DWORD dwEventType, char FAR *cData, DWORD dwSize)
#endif
{
	static	TPOS_PACKET		send_packet;
	static	TPOS_COMPACKET	send_compacket;
	static	char			compressbuf[MAX_PACKET_SIZE - sizeof(DWORD)];
	DWORD			comsize;
	
    if(!(g_dwConnectedServerType&CONNECTED_SERVER_DOOR))
		return DLL_OK;

	send_packet.Header.dwType = dwEventType;
	send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + dwSize;
	send_packet.Header.dwVersion = CURRENT_VERSION;

	if(cData != NULL && dwSize != 0)
	{
		memcpy(&send_packet.data.cBuf, cData, dwSize);		
	}
	memcpy(compressbuf, &send_packet, send_packet.Header.dwSize);

	comsize = lzo_compress(compressbuf, send_packet.Header.dwSize, send_compacket.cBuf);
	send_compacket.Header.dwSize = comsize + sizeof(DWORD);

	QueuePacket(CnDoor, &send_compacket, DoorSockethWnd);	

	return	DLL_OK;
}
// -----------------------------------------------------------------------------
// Recv Data To Door Server
// -----------------------------------------------------------------------------
#ifdef BCBUSED
int _PosRecvDataFromDoor(DWORD &dwEventType, char FAR *cData, DWORD &dwSize)
#else
NETGE_API int NETGE_FNB PosRecvDataFromDoor(DWORD &dwEventType, char FAR *cData, DWORD &dwSize)
#endif
{	
	// Jack,  [1/14/2003]
	// In ProcessPacket, we have combine dwEventType and dwSize to SendMessage's lParam.
	// So, remark for make this function invalid.
	/*
	dwEventType = CurrentPacket.Header.dwType;
	dwSize = CurrentPacket.Header.dwSize - sizeof(TPOS_PACKETHEADER);
	memcpy(cData,CurrentPacket.data.cBuf,dwSize);
	return	DLL_OK;
	*/
	return	DLL_ERROR;
}
#endif