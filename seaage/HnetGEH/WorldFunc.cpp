// =============================================================================
// WorldFunc.cpp
// Psalm of Sea DDL World Server Function Source By Hawke Hsieh
// Last Modify Date : 2002.06.25
// =============================================================================

#include "HNETGEH.h"
#ifdef __NETGE_NETWORK__

#include "Netge_Extern.h"

// -----------------------------------------------------------------------------
// Login World Server
// -----------------------------------------------------------------------------
#ifdef BCBUSED
int _PosLoginWorld(HWND hWnd, char FAR *ServerName, int port, char *id, char *Password,DWORD Version)
#else
NETGE_API int NETGE_FNB PosLoginWorld(HWND hWnd, char FAR *ServerName, int port, char *id, char *Password,DWORD Version)
#endif
{	
    int					iRet;
	TPOS_EVENT_LOGIN	EventLogin;
	DWORD				dwSize;
	static	char		PacketData[MAX_PACKET_SIZE - sizeof(TPOS_PACKETHEADER)];

    if(g_dwConnectedServerType&CONNECTED_SERVER_WORLD)return DLL_OK;
    
	// 檢查是否有輸入參數
	if(ServerName == NULL || Password == NULL) return 0;

	// 保留父視窗的 hwnd
	ParenthWnd = hWnd; 	

	_snprintf(WorldServerAddr, 15, "%s", ServerName);
	
    CnWorld = (TPOS_CN *)GlobalAlloc(GPTR,sizeof(TPOS_CN));
	memset(CnWorld, 0x0, sizeof(TPOS_CN));
    
	CnWorld->dwSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(CnWorld->dwSocket == INVALID_SOCKET)
     {
		CloseOneConnection(CnWorld);
		if(CnWorld) {GlobalFree(CnWorld); CnWorld=NULL;}	    
		return -2;
     }
    
	iRet = 1;
    setsockopt(CnWorld->dwSocket, SOL_SOCKET, SO_DONTLINGER, (char *)&iRet, sizeof(iRet));

    CnWorld->Addr.sin_family       = AF_INET;
    CnWorld->Addr.sin_port         = htons(port);
    CnWorld->Addr.sin_addr.s_addr  = inet_addr(WorldServerAddr);
    iRet = connect(CnWorld->dwSocket, (struct sockaddr far *)&CnWorld->Addr, sizeof(struct sockaddr_in));
    if(iRet == SOCKET_ERROR)
     {
		CloseOneConnection(CnWorld);
		if(CnWorld) {GlobalFree(CnWorld); CnWorld=NULL;}	    
	    return CANT_CONNECTED;
     }

    if(WorldSocketWndInit() == FALSE) return 0;

    iRet = WSAAsyncSelect(CnWorld->dwSocket, WorldSockethWnd, WM_ASYNCSELECT, FD_READ | FD_WRITE | FD_CLOSE);
    if(iRet == SOCKET_ERROR)
     {
		CloseOneConnection(CnWorld);
		if(CnWorld) {GlobalFree(CnWorld); CnWorld=NULL;}	    
 	    return -4;
     }    

    strcpy(EventLogin.cId,id);
	strcpy(EventLogin.cPw,Password);
	EventLogin.dwVersion = Version;
	memcpy(PacketData,&EventLogin,sizeof(TPOS_EVENT_LOGIN));
	dwSize = sizeof(TPOS_EVENT_LOGIN);
	
	g_dwConnectedServerType |= CONNECTED_SERVER_WORLD;

	#ifdef BCBUSED
    _PosSendDataToWorld(PLAYER_LOGIN,PacketData,dwSize);
    #else
	PosSendDataToWorld(PLAYER_LOGIN,PacketData,dwSize);
    #endif  	    
	
	return DLL_OK;	
}
// -----------------------------------------------------------------------------
// LogOut World Server
// -----------------------------------------------------------------------------
#ifdef BCBUSED
int _PosLogoutWorld(void)
#else
NETGE_API int NETGE_FNB PosLogoutWorld(void)
#endif
{
	if(!(g_dwConnectedServerType&CONNECTED_SERVER_WORLD))return DLL_OK;
	CloseOneConnection(CnWorld);
	if(CnWorld) {GlobalFree(CnWorld); CnWorld=NULL;}   
	DestroyWindow(WorldSockethWnd);
	UnregisterClass(WorldClassName, wInstance);

	g_dwConnectedServerType &= ~CONNECTED_SERVER_WORLD;
	return DLL_OK;
}
// -----------------------------------------------------------------------------
// Send Data To World Server
// -----------------------------------------------------------------------------
#ifdef BCBUSED
int _PosSendDataToWorld(DWORD dwEventType, char FAR *cData, DWORD dwSize)
#else
NETGE_API int NETGE_FNB PosSendDataToWorld(DWORD dwEventType, char FAR *cData, DWORD dwSize)
#endif
{
	static	TPOS_PACKET		send_packet;
	static	TPOS_COMPACKET	send_compacket;
	static	char			compressbuf[MAX_PACKET_SIZE - sizeof(DWORD)];
	DWORD			comsize;
	
    if(!(g_dwConnectedServerType&CONNECTED_SERVER_WORLD))
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

	QueuePacket(CnWorld, &send_compacket, WorldSockethWnd);	

	return	DLL_OK;
}
// -----------------------------------------------------------------------------
// Recv Data To World Server
// -----------------------------------------------------------------------------
#ifdef BCBUSED
int _PosRecvDataFromWorld(DWORD &dwEventType, char FAR *cData, DWORD &dwSize)
#else
NETGE_API int NETGE_FNB PosRecvDataFromWorld(DWORD &dwEventType, char FAR *cData, DWORD &dwSize)
#endif
{	
	// Jack,  [1/14/2003]
	// In ProcessPacket, we have combine dwEventType and dwSize to SendMessage's lParam.
	// So, remark for make this function invalid.
	/*
	dwEventType = CurrentPacket.Header.dwType;
	dwSize = CurrentPacket.Header.dwSize - sizeof(TPOS_PACKETHEADER);
	memcpy(cData, CurrentPacket.data.cBuf, dwSize);
	return	DLL_OK;
	*/
	return	DLL_ERROR;
}

#endif