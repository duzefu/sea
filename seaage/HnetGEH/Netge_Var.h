#ifndef NETGE_VAR_H
#define NETGE_VAR_H

#include "HNETGEH.h"
#include "Netge_Def.h"

//===============================================================================

HINSTANCE        	dInstance;
HINSTANCE	        wInstance;
HINSTANCE	        zInstance;
HINSTANCE	        zsInstance;
       
WORD                wVersionRequested;
WSADATA             wd;

TPOS_CN				*CnDoor;
TPOS_CN				*CnWorld;
TPOS_CN				*CnZone;
TPOS_CN	            *CnZoneSync;

char                buf[10240];

char				DoorServerAddr[16];
char				WorldServerAddr[16];
char				ZoneServerAddr[16];

int                 port;

HWND                ParenthWnd;
HWND                dParenthWnd;
HWND                wParenthWnd;
HWND                zParenthWnd;
  
char             	DoorClassName[] = "DOORSOCKET";
char             	WorldClassName[] = "WORLDSOCKET";
char             	ZoneClassName[] = "ZONESOCKET";
char             	ZoneSyncClassName[] = "ZONESYNCSOCKET";

TPOS_PACKET	    	CurrentPacket;

HWND		    	DoorSockethWnd;
HWND		    	WorldSockethWnd;
HWND		    	ZoneSockethWnd;
HWND		    	ZoneSyncSockethWnd;

HWND                hWnd;
DWORD       		dwRequestForWorldInfoIndex;
DWORD       		dwRequestForZoneInfoIndex;
DWORD               dwRequestForPlayerListIndex;

ULONG				TotalSendDataSize;
ULONG				TotalRecvDataSize;

DWORD               g_dwConnectedServerType=0x00000000;      

#endif	// NETGE_VAR_H