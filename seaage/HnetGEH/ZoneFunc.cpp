// =============================================================================
// ZoneFunc.cpp
// Psalm of Sea DDL Zone Server Function Source By Hawke Hsieh
// Last Modify Date : 2002.07.04
// =============================================================================

#include "HNETGEH.h"
#include "Netge_Extern.h"
#ifdef __NETGE_NETWORK__

// -----------------------------------------------------------------------------
// Login Zone Server
// -----------------------------------------------------------------------------
#ifdef BCBUSED
int _PosLoginZone(HWND hWnd, char FAR *ServerName, int port, char *MainName,DWORD Version)
#else
NETGE_API int NETGE_FNB PosLoginZone(HWND hWnd, char FAR *ServerName, int port, char *MainName,DWORD Version)
#endif
{	 
	int					iRet;
	TPOS_EVENT_LOGIN	EventLogin;
	DWORD				dwSize;
	static	char		PacketData[MAX_PACKET_SIZE - sizeof(TPOS_PACKETHEADER)];

    //SaveMsgToLog("PLAYER_LOGIN");
    BOOL  nodelay = TRUE;
    
    if(g_dwConnectedServerType&CONNECTED_SERVER_ZONE)return DLL_OK;
    
    if(ServerName == NULL) return 0;
    
    // «O¯d¤÷µøµ¡ªº hwnd
    ParenthWnd = hWnd; 
    
    _snprintf(ZoneServerAddr, 15, "%s", ServerName);
    
    // ------- Init Normal Socket -----------	
    CnZone = (TPOS_CN *)GlobalAlloc(GPTR,sizeof(TPOS_CN));
    memset(CnZone, 0x0, sizeof(TPOS_CN));
    
    CnZone->dwSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(CnZone->dwSocket == INVALID_SOCKET)
    {
        CloseOneConnection(CnZone);
        if(CnZone) {GlobalFree(CnZone); CnZone=NULL;}	    
        return -2;
    }
    //    SaveMsgToLog("INIT_SOCKET"); 
    
    iRet = 1;
    setsockopt(CnZone->dwSocket, SOL_SOCKET, SO_DONTLINGER, (char *)&iRet, sizeof(iRet));
    // ======  Modify by Hawke Hsieh    2002/07/04  =====
    iRet = setsockopt(CnZone->dwSocket, IPPROTO_TCP, TCP_NODELAY, (char *)&nodelay, sizeof(BOOL));
    // ==================================================
    CnZone->Addr.sin_family       = AF_INET;
    CnZone->Addr.sin_port         = htons(port);
    CnZone->Addr.sin_addr.s_addr  = inet_addr(ZoneServerAddr);
    iRet = connect(CnZone->dwSocket, (struct sockaddr far *)&CnZone->Addr, sizeof(struct sockaddr_in));
    if(iRet == SOCKET_ERROR)
    {
        CloseOneConnection(CnZone);
        if(CnZone) {GlobalFree(CnZone); CnZone=NULL;}	    
        return CANT_CONNECTED;
    }
    
    //    SaveMsgToLog("CONNECT_ZONE"); 
    
    if(ZoneSocketWndInit() == FALSE) return 0;
    
    iRet = WSAAsyncSelect(CnZone->dwSocket, ZoneSockethWnd, WM_ASYNCSELECT, FD_READ | FD_WRITE | FD_CLOSE);
    if(iRet == SOCKET_ERROR)
    {
        CloseOneConnection(CnZone);
        if(CnZone) {GlobalFree(CnZone); CnZone=NULL;}	    
        return -4;
    }    	
    //    SaveMsgToLog("SOCKET_SYNC"); 	
    
    // ------- Init Sync Socket -----------	
    
    CnZoneSync = (TPOS_CN *)GlobalAlloc(GPTR,sizeof(TPOS_CN));
    memset(CnZoneSync, 0x0, sizeof(TPOS_CN));
    
    CnZoneSync->dwSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(CnZoneSync->dwSocket == INVALID_SOCKET)
    {
        CloseOneConnection(CnZoneSync);
        if(CnZoneSync) {GlobalFree(CnZoneSync); CnZoneSync=NULL;}	    
        return -2;
    }
    
    iRet = 1;
    setsockopt(CnZoneSync->dwSocket, SOL_SOCKET, SO_DONTLINGER, (char *)&iRet, sizeof(iRet));
    // ======  Modify by Hawke Hsieh    2002/07/04  =====
    iRet = setsockopt(CnZoneSync->dwSocket, IPPROTO_TCP, TCP_NODELAY, (char *)&nodelay, sizeof(BOOL));
    // ==================================================
    CnZoneSync->Addr.sin_family       = AF_INET;
    CnZoneSync->Addr.sin_port         = htons(port + 500);
    CnZoneSync->Addr.sin_addr.s_addr  = inet_addr(ZoneServerAddr);
    iRet = connect(CnZoneSync->dwSocket, (struct sockaddr far *)&CnZoneSync->Addr, sizeof(struct sockaddr_in));
    if(iRet == SOCKET_ERROR)
    {
        CloseOneConnection(CnZoneSync);
        if(CnZoneSync) {GlobalFree(CnZoneSync); CnZoneSync=NULL;}	    
        return CANT_CONNECTED;
    }
    
    if(ZoneSyncSocketWndInit() == FALSE) return 0;
    
    iRet = WSAAsyncSelect(CnZoneSync->dwSocket, ZoneSyncSockethWnd, WM_SYNC, FD_READ | FD_WRITE | FD_CLOSE);
    if(iRet == SOCKET_ERROR)
    {
        CloseOneConnection(CnZoneSync);
        if(CnZoneSync) {GlobalFree(CnZoneSync); CnZoneSync=NULL;}	    
        return -4;
    }    
    
    strcpy(EventLogin.cId, MainName);
	memcpy(PacketData, &EventLogin, sizeof(TPOS_EVENT_LOGIN));
	dwSize = sizeof(TPOS_EVENT_LOGIN);

	g_dwConnectedServerType |= CONNECTED_SERVER_ZONE;
	
	#ifdef BCBUSED
    _PosSendDataToZone(PLAYER_LOGIN, PacketData, dwSize);
    #else
	PosSendDataToZone(PLAYER_LOGIN, PacketData, dwSize);
    #endif  	              
    
    return DLL_OK;	    
}
// -----------------------------------------------------------------------------
// LogOut Zone Server
// -----------------------------------------------------------------------------
#ifdef BCBUSED
int _PosLogoutZone(void)
#else
NETGE_API int NETGE_FNB PosLogoutZone(void)
#endif
{    
    if(!(g_dwConnectedServerType&CONNECTED_SERVER_ZONE))return DLL_OK;
    
	CloseOneConnection(CnZoneSync);    
    
	if(CnZoneSync) {GlobalFree(CnZoneSync); CnZoneSync=NULL;}    
    
	DestroyWindow(ZoneSyncSockethWnd);    
    UnregisterClass(ZoneSyncClassName, zsInstance);    
    
    CloseOneConnection(CnZone);    
    if(CnZone)
    {
        GlobalFree(CnZone);
        CnZone=NULL;
    }	
    DestroyWindow(ZoneSockethWnd);
    UnregisterClass(ZoneClassName, zInstance);
        
    g_dwConnectedServerType &= ~CONNECTED_SERVER_ZONE;    
    return DLL_OK;
}
// -----------------------------------------------------------------------------
// Send Data To Zone Server
// -----------------------------------------------------------------------------
#ifdef BCBUSED
int _PosSendDataToZone(DWORD dwEventType, char FAR *cData, DWORD dwSize)
#else
NETGE_API int NETGE_FNB PosSendDataToZone(DWORD dwEventType, char FAR *cData, DWORD dwSize)
#endif
{
	static	TPOS_PACKET		send_packet;
	static	TPOS_COMPACKET	send_compacket;
	static	char			compressbuf[MAX_PACKET_SIZE - sizeof(DWORD)];
	DWORD			comsize;
	
    if(!(g_dwConnectedServerType&CONNECTED_SERVER_ZONE))
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

	QueuePacket(CnZone, &send_compacket, ZoneSockethWnd);	

	return	DLL_OK;
}
// -----------------------------------------------------------------------------
// Recv Data To Zone Server
// -----------------------------------------------------------------------------
#ifdef BCBUSED
int _PosRecvDataFromZone(DWORD &dwEventType, char FAR *cData, DWORD &dwSize)
#else
NETGE_API int NETGE_FNB PosRecvDataFromZone(DWORD &dwEventType, char FAR *cData, DWORD &dwSize)
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
