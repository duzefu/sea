//---------------------------------------------------------------------------
// Psalm of Sea ZoneServer Init Socket
// By Hawke Hsieh 
// 2002-10-07
//---------------------------------------------------------------------------

#include "ZoneServer_Def.h"

//---------------------------------------------------------------------------
// 起始WinSock
//---------------------------------------------------------------------------
int ZoneWinSockInit(HWND hWnd,int port)
{
    int        iRet;
    int	    sa_len = sizeof(struct sockaddr_in);
    BOOL	    nodelay = TRUE;
    
    LOCK_CONNECTION(0);
    Pos_Cn = (TPOS_CN *)malloc(sizeof(TPOS_CN) * MAX_PLAYER_PER_ZONE);
    memset(Pos_Cn, 0x0, sizeof(TPOS_CN) * MAX_PLAYER_PER_ZONE);
    UNLOCK_CONNECTION(0);
    
    
    Pos_Cn_Sync = (TPOS_CN *)malloc(sizeof(TPOS_CN) * MAX_PLAYER_PER_ZONE);
    memset(Pos_Cn_Sync, 0x0, sizeof(TPOS_CN) * MAX_PLAYER_PER_ZONE);
    Zone = (TPOS_CN *)malloc(sizeof(TPOS_CN));
    memset(Zone, 0x0, sizeof(TPOS_CN));
    ZoneSync = (TPOS_CN *)malloc(sizeof(TPOS_CN));
    memset(ZoneSync, 0x0, sizeof(TPOS_CN)); 
    
    // ---------  Init Socket  ----------------
    Zone->dwSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(Zone->dwSocket == INVALID_SOCKET)
    {
        WSACleanup();
        return -2;
    }
    
    iRet = 1;
    setsockopt(Zone->dwSocket, SOL_SOCKET, SO_DONTLINGER, (char *)&iRet, sizeof(iRet));
    setsockopt(Zone->dwSocket, IPPROTO_TCP, TCP_NODELAY, (char *)&nodelay, sizeof(BOOL));
    
    Zone->Addr.sin_family = AF_INET;
    Zone->Addr.sin_port = htons(port);
    //Zone->addr.sin_addr.s_addr =INADDR_ANY;
    Zone->Addr.sin_addr.s_addr = inet_addr(ZoneServerIP);
    iRet = bind(Zone->dwSocket, (struct sockaddr far *)&(Zone->Addr), sa_len);
    if(iRet == SOCKET_ERROR)
    {
        return DLL_ERROR;
    }
    
    iRet = listen(Zone->dwSocket, 5);
    if(iRet == SOCKET_ERROR)
    {
        CloseZoneServer();
        return DLL_ERROR;
    }
    if(ZoneSocketWndInit() == FALSE) return 0;
    iRet = WSAAsyncSelect(Zone->dwSocket, ZoneSockethWnd,
        WM_ASYNCSELECT, FD_ACCEPT | FD_READ | FD_WRITE | FD_CLOSE);
    if(iRet == SOCKET_ERROR)
    {
        CloseZoneServer();
        return -4;
    }
    
    // ---------   Init Sync Socket   ----------
    
    ZoneSync->dwSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(ZoneSync->dwSocket == INVALID_SOCKET)
    {
        WSACleanup();
        return -2;
    }
    
    iRet = 1;
    setsockopt(ZoneSync->dwSocket, SOL_SOCKET, SO_DONTLINGER, (char *)&iRet, sizeof(iRet));
    setsockopt(ZoneSync->dwSocket, IPPROTO_TCP, TCP_NODELAY, (char *)&nodelay, sizeof(BOOL));
    
    ZoneSync->Addr.sin_family = AF_INET;
    ZoneSync->Addr.sin_port = htons(port+500);
    //Zone->addr.sin_addr.s_addr =INADDR_ANY;
    ZoneSync->Addr.sin_addr.s_addr = inet_addr(ZoneServerIP);
    iRet = bind(ZoneSync->dwSocket, (struct sockaddr far *)&(ZoneSync->Addr), sa_len);
    if(iRet == SOCKET_ERROR)
    {
        return DLL_ERROR;
    }
    
    iRet = listen(ZoneSync->dwSocket, 5);
    if(iRet == SOCKET_ERROR)
    {
        CloseZoneSyncServer();
        return DLL_ERROR;
    }
    
    if(ZoneSyncSocketWndInit() == FALSE) return 0; 
    iRet = WSAAsyncSelect(ZoneSync->dwSocket, ZoneSyncSockethWnd, 
        WM_SYNC, FD_ACCEPT | FD_READ | FD_WRITE | FD_CLOSE);
    if(iRet == SOCKET_ERROR)
    {
        CloseZoneSyncServer();
        return -4;
    } 
    
    return DLL_OK;
}
//---------------------------------------------------------------------------
// Connect WorldServer Winsocket Init
//---------------------------------------------------------------------------
int WorldWinSockInit(HWND hWnd,int port,char FAR *ServerName)
{
    int iRet;
    int	    sa_len = sizeof(struct sockaddr_in);
    BOOL	    nodelay = TRUE;
    
    // 檢查是否有輸入參數
    if(ServerName == NULL) return 0;
    
    // 保留父視窗的 hwnd
    //hDoorParenthWnd = hWnd; 
    
    _snprintf(WorldServerAddr, 15, "%s", ServerName);
    
    World = (TPOS_CN *)malloc(sizeof(TPOS_CN));
    memset(World, 0x0, sizeof(TPOS_CN));
    
    World->dwSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(World->dwSocket == INVALID_SOCKET)
    {
        CloseOneConnection(World);
        free(World);
        WSACleanup();
        return -2;
    }
    
    iRet = 1;
    setsockopt(World->dwSocket, SOL_SOCKET, SO_DONTLINGER, (char *)&iRet, sizeof(iRet));
    
    World->Addr.sin_family       = AF_INET;
    World->Addr.sin_port         = htons(port);
    World->Addr.sin_addr.s_addr  = inet_addr(WorldServerAddr);
    iRet = connect(World->dwSocket, (struct sockaddr far *)&World->Addr, sizeof(struct sockaddr_in));
    if(iRet == SOCKET_ERROR)
    {
        CloseOneConnection(World);
        free(World);
        WSACleanup();
        return CANT_CONNECTED;
    }
    
    if(WorldSocketWndInit() == FALSE) return 0;
    iRet = WSAAsyncSelect(World->dwSocket, WorldSockethWnd, 
        WM_ASYNCSELECT, FD_READ | FD_WRITE | FD_CLOSE);
    if(iRet == SOCKET_ERROR)
    {
        CloseOneConnection(World);
        free(World);
        WSACleanup();
        return -4;
    }
	
	static TPOS_PACKET			send_packet;
	static TPOS_COMPACKET		send_compacket;
	TPOS_EVENT_ZONELOGIN		EventZoneLogin;

	send_packet.Header.dwType = ZONE_LOGIN;
	send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_ZONELOGIN);
	strcpy(EventZoneLogin.cZone, ZoneName);
	memcpy(send_packet.data.cBuf, &EventZoneLogin, sizeof(TPOS_EVENT_ZONELOGIN));

	CompressPacket(&send_packet, &send_compacket);    
    
    QueuePacket(World, &send_compacket, CONNECTED_SERVER_WORLD);
    
    return DLL_OK;
}
//---------------------------------------------------------------------------
// Cooect DoorServer Winsocket Init
//---------------------------------------------------------------------------
int DoorWinSockInit(HWND hWnd)
{ 
    int        iRet;
    int	    sa_len = sizeof(struct sockaddr_in);
    BOOL	    nodelay = TRUE; 
    
    Door = (TPOS_CN *)malloc(sizeof(TPOS_CN));
    memset(Door, 0x0, sizeof(TPOS_CN));
    
    Door->dwSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(Door->dwSocket == INVALID_SOCKET)
    {
        CloseOneConnection(Door);
        free(Door);
        WSACleanup();
        return INIT_SOCKET_ERROR;
    }
    
    iRet = 1;
    setsockopt(Door->dwSocket, SOL_SOCKET, SO_DONTLINGER, (char *)&iRet, sizeof(iRet));
    
    Door->Addr.sin_family       = AF_INET;
    Door->Addr.sin_port         = htons((int)DoorServerPort);
    Door->Addr.sin_addr.s_addr  = inet_addr(DoorServerAddr);
    iRet = connect(Door->dwSocket, (struct sockaddr far *)&Door->Addr,
        sizeof(struct sockaddr_in));
    if(iRet == SOCKET_ERROR)
    {
        CloseOneConnection(Door);
        free(Door);
        WSACleanup();
        return CANT_CONNECTED;
    }
    
    if(DoorSocketWndInit() == FALSE) return 0;
    
    iRet = WSAAsyncSelect(Door->dwSocket, DoorSockethWnd, 
        WM_ASYNCSELECT, FD_READ | FD_WRITE | FD_CLOSE);
    if(iRet == SOCKET_ERROR)
    {
        CloseOneConnection(Door);
        free(Door);
        WSACleanup();
        return CANT_ASYNC;
    }
	static TPOS_PACKET			send_packet;
	static TPOS_COMPACKET		send_compacket;

	send_packet.Header.dwType = ZONE_LOGIN;
	send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER);
	
	CompressPacket(&send_packet, &send_compacket);
    
    QueuePacket(Door, &send_compacket, CONNECTED_SERVER_DOOR);
    
    return DLL_OK;
}
// -----------------------------------------------------------------------------
// 開啟一個新的且是隱藏的視窗，以收取 socket 的訊息 For DoorServer
// -----------------------------------------------------------------------------
BOOL WINAPI DoorSocketWndInit(void)
{
    WNDCLASS	wc;
    
    dInstance = (HINSTANCE)GetWindowLong(MainhWnd, GWL_HINSTANCE);
    
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
// 開啟一個新的且是隱藏的視窗，以收取 socket 的訊息 For WorldServer
// -----------------------------------------------------------------------------
BOOL WINAPI WorldSocketWndInit(void)
{
    WNDCLASS	wc;
    
    wInstance = (HINSTANCE)GetWindowLong(MainhWnd, GWL_HINSTANCE);
    
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
// 開啟一個新的且是隱藏的視窗，以收取 socket 的訊息 For ZoneServer
// -----------------------------------------------------------------------------
BOOL WINAPI ZoneSocketWndInit(void)
{
    WNDCLASS	wc;
    
    zInstance = (HINSTANCE)GetWindowLong(MainhWnd, GWL_HINSTANCE);
    
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
// 開啟一個新的且是隱藏的視窗，以收取 socket 的訊息 For ZoneServer Sync
// -----------------------------------------------------------------------------
BOOL WINAPI ZoneSyncSocketWndInit(void)
{
    WNDCLASS	wc;
    
    zsInstance = (HINSTANCE)GetWindowLong(MainhWnd, GWL_HINSTANCE);
    
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
// -----------------------------------------------------------------------------
