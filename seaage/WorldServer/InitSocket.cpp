//---------------------------------------------------------------------------
// Psalm of Sea WorldServer Winsocket Init
// By Hawke Hsieh 
// 2002-10-1
//---------------------------------------------------------------------------

#include "WorldServer_Def.h"

//---------------------------------------------------------------------------
// Cooect DoorServer Winsocket Init
//---------------------------------------------------------------------------
int DoorWinSockInit(HWND hWnd)
{	
	int         iRet;
	int  	    sa_len = sizeof(struct sockaddr_in);
	BOOL	    nodelay = TRUE;	
	
	Door = (TPOS_CN *)malloc(sizeof(TPOS_CN));
	if(Door == NULL)return DLL_ERROR;
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
	
	if(DoorSocketWndInit(hWnd) == FALSE) return 0;
	
	iRet = WSAAsyncSelect(Door->dwSocket, DoorSockethWnd, 
		WM_ASYNCSELECT, FD_READ | FD_WRITE | FD_CLOSE);
	if(iRet == SOCKET_ERROR)
	{
		CloseOneConnection(Door);
		free(Door);
		WSACleanup();
		return CANT_ASYNC;
	}

	TPOS_PACKET			send_packet;
	TPOS_COMPACKET		send_compacket;

	send_packet.Header.dwType = WORLD_LOGIN;
	send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER);
	
	CompressPacket(&send_packet, &send_compacket);

	QueuePacket(Door, &send_compacket,CONNECTED_SERVER_DOOR);
	
	return DLL_OK;
}
//---------------------------------------------------------------------------
// Connect WorldServer Winsocket Init
//---------------------------------------------------------------------------
int WorldWinSockInit(HWND hWnd,int port,char FAR *ServerName)
{	
	int			iRet;
	int			sa_len = sizeof(struct sockaddr_in);
	BOOL	    nodelay = TRUE;
	
	LOCK_CONNECTION(0);
	Pos_Cn = (TPOS_CN *)malloc(sizeof(TPOS_CN) * MAX_PLAYER_PER_WORLD);
	if(Pos_Cn == NULL)return DLL_ERROR;
	memset(Pos_Cn, 0x0, sizeof(TPOS_CN) * MAX_PLAYER_PER_WORLD);
	UNLOCK_CONNECTION(0);

	World = (TPOS_CN *)malloc(sizeof(TPOS_CN));
	if(World == NULL)return DLL_ERROR;
	memset(World, 0x0, sizeof(TPOS_CN));	
	
	World->dwSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(World->dwSocket == INVALID_SOCKET)
	{
		WSACleanup();
		return -2;
	}
	
	iRet = 1;
	setsockopt(World->dwSocket, SOL_SOCKET, SO_DONTLINGER, (char *)&iRet, sizeof(iRet));
	setsockopt(World->dwSocket, IPPROTO_TCP, TCP_NODELAY, (char *)&nodelay, sizeof(BOOL));
	
	World->Addr.sin_family = AF_INET;
	World->Addr.sin_port = htons(port);
	World->Addr.sin_addr.s_addr = inet_addr(WorldServerAddr);
	iRet = bind(World->dwSocket, (struct sockaddr far *)&(World->Addr), sa_len);
	if(iRet == SOCKET_ERROR)
	{
		return DLL_ERROR;
	}
	
	iRet = listen(World->dwSocket, 5);
	if(iRet == SOCKET_ERROR)
	{
		CloseDoorServer();
		return DLL_ERROR;
	}
	
	if(WorldSocketWndInit(hWnd) == FALSE) return 0;
	
	iRet = WSAAsyncSelect(World->dwSocket, WorldSockethWnd, WM_ASYNCSELECT, FD_ACCEPT | FD_READ | FD_WRITE | FD_CLOSE);
	if(iRet == SOCKET_ERROR)
	{
		CloseDoorServer();
		return CANT_ASYNC;
	}
	
	return DLL_OK;
}
// -----------------------------------------------------------------------------
// 開啟一個新的且是隱藏的視窗，以收取 socket 的訊息 For DoorServer
// -----------------------------------------------------------------------------
BOOL WINAPI DoorSocketWndInit(HWND hWnd)
{
	WNDCLASS	wc;
	
	dInstance = (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE);
	
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
BOOL WINAPI WorldSocketWndInit(HWND hWnd)
{
	WNDCLASS	wc;
	
	wInstance = (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE);

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
/* //預留以後 QQ Server 獨立使用
// -----------------------------------------------------------------------------
// 開啟一個新的且是隱藏的視窗，以收取 socket 的訊息 For QQServer
// -----------------------------------------------------------------------------
BOOL WINAPI QQSocketWndInit(HWND hWnd)
{
	WNDCLASS	wc;
	
	wInstance = (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE);

	wc.style			= 0; 
	wc.lpfnWndProc		= (WNDPROC)QQSocketWndProc;
	wc.cbClsExtra		= 0;
	wc.cbWndExtra		= 0;
	wc.hInstance		= qInstance;
	wc.hIcon			= NULL; 
	wc.hCursor			= NULL; 
	wc.hbrBackground	= NULL;
	wc.lpszMenuName     = NULL;
	wc.lpszClassName	= QQClassName;

	if(!RegisterClass(&wc))
	{
		return FALSE;
	}

	QQSockethWnd = CreateWindow(QQClassName, "", 0L, 0, 0, 0, 0, NULL, NULL, qInstance, NULL);

	if(QQSockethWnd == NULL)
	{
		UnregisterClass(QQClassName, qInstance);
		return FALSE;
	}

	ShowWindow(QQSockethWnd, SW_HIDE);
	UpdateWindow(QQSockethWnd);

	return TRUE;
}
*/
// -----------------------------------------------------------------------------

