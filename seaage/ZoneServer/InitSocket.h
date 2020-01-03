#ifndef _INITSOCKET_H_
#define _INITSOCKET_H_

int ZoneWinSockInit(HWND hWnd,int port);
int WorldWinSockInit(HWND hWnd,int port,char FAR *ServerName);
int DoorWinSockInit(HWND hWnd);
BOOL WINAPI DoorSocketWndInit(void);
BOOL WINAPI WorldSocketWndInit(void);
BOOL WINAPI ZoneSocketWndInit(void);
BOOL WINAPI ZoneSyncSocketWndInit(void);

#endif