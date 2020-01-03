//---------------------------------------------------------------------------
// Psalm of Sea DoorServer Init	Socket
// By Hawke Hsieh 
// 2002-10-1
//---------------------------------------------------------------------------

#include "DoorServer_Def.h"

//---------------------------------------------------------------------------
// Connect DoorServer Winsocket Init
//---------------------------------------------------------------------------
int DoorWinSockInit(HWND hWnd,int port)
{
	WORD	    wVersionRequested;
	WSADATA     wsaData;
	int			iRet;
	int			sa_len = sizeof(struct sockaddr_in);
	BOOL	    nodelay = TRUE;
	
	LOCK_CONNECTION(0);
	Pos_Cn = (TPOS_CN *)malloc(sizeof(TPOS_CN) * MAX_PLAYER_PER_DOOR);
	memset(Pos_Cn, 0x0, sizeof(TPOS_CN) * MAX_PLAYER_PER_DOOR);
	UNLOCK_CONNECTION(0);

	Door = (TPOS_CN *)malloc(sizeof(TPOS_CN));
	memset(Door, 0x0, sizeof(TPOS_CN));
	
	wVersionRequested = MAKEWORD(1, 2);
	iRet = WSAStartup(wVersionRequested, &wsaData);
	if(iRet != 0)
	{
		WSACleanup();
		return -1;
	}
	Door->dwSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(Door->dwSocket == INVALID_SOCKET)
	{
		WSACleanup();
		return -2;
	}
	
	iRet = 1;
	setsockopt(Door->dwSocket, SOL_SOCKET, SO_DONTLINGER, (char *)&iRet, sizeof(iRet));
	setsockopt(Door->dwSocket, IPPROTO_TCP, TCP_NODELAY, (char *)&nodelay, sizeof(BOOL));
	
	Door->Addr.sin_family = AF_INET;
	Door->Addr.sin_port = htons(port);
	Door->Addr.sin_addr.s_addr = inet_addr(DoorServerAddr);
	iRet = bind(Door->dwSocket, (struct sockaddr far *)&(Door->Addr), sa_len);
	if(iRet == SOCKET_ERROR)
	{
		return DLL_ERROR;
	}
	
	iRet = listen(Door->dwSocket, 5);
	if(iRet == SOCKET_ERROR)
	{
		CloseDoorServer();
		return DLL_ERROR;
	}
	
	if(DoorSocketWndInit(hWnd) == FALSE) return 0;
	
	iRet = WSAAsyncSelect(Door->dwSocket, DoorSockethWnd, WM_ASYNCSELECT, FD_ACCEPT | FD_READ | FD_WRITE | FD_CLOSE);
	if(iRet == SOCKET_ERROR)
	{
		CloseDoorServer();
		return -4;
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