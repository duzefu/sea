// =============================================================================
// NetGe_Extern.h
// =============================================================================
#ifndef NETGE_EXTERN_H
#define NETGE_EXTERN_H


#include "HNETGEH.h"
#include "Netge_Def.h"
#include "Netge_Sock.h"

// -----------------------------------------------------------------------------

extern HINSTANCE	dInstance;
extern HINSTANCE	wInstance;
extern HINSTANCE	zInstance;
extern HINSTANCE	zsInstance;
       
extern WORD         wVersionRequested;
extern WSADATA      wd;

extern TPOS_CN		*CnDoor;
extern TPOS_CN		*CnWorld;
extern TPOS_CN		*CnZone;
extern TPOS_CN	    *CnZoneSync;

extern char          buf[10240];

extern char			DoorServerAddr[16];
extern char			WorldServerAddr[16];
extern char			ZoneServerAddr[16];

extern int          port;
extern TPOS_PACKET 	CurrentPacket;
extern HWND         ParenthWnd;
extern HWND         dParenthWnd;
extern HWND         wParenthWnd;
extern HWND         zParenthWnd;
extern DWORD		dwRequestForWorldInfoIndex;
extern DWORD   		dwRequestForZoneInfoIndex;
extern DWORD        dwRequestForPlayerListIndex;

extern ULONG		TotalSendDataSize;
extern ULONG		TotalRecvDataSize;

extern DWORD        g_dwConnectedServerType;


extern char			DoorClassName[];
extern char			WorldClassName[];
extern char			ZoneClassName[];
extern char         ZoneSyncClassName[];

extern HWND	        DoorSockethWnd;
extern HWND	        WorldSockethWnd;
extern HWND	        ZoneSockethWnd;
extern HWND	        ZoneSyncSockethWnd;

extern HWND         hWnd;

#endif