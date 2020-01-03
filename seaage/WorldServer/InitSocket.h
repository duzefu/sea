#ifndef _INITSOCKET_H_
#define _WINSOCKETINIT_H_

int DoorWinSockInit(HWND hWnd);
int WorldWinSockInit(HWND hWnd,int port,char FAR *ServerName);
BOOL WINAPI DoorSocketWndInit(HWND hWnd);
BOOL WINAPI WorldSocketWndInit(HWND hWnd);

#endif