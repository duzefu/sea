#ifndef DOORSERVER_DEF_H
#define DOORSERVER_DEF_H
//-------------------------------------------------------------------------------

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//-------------------------------------------------------------------------------

#define WIN32_LEAN_AND_MEAN		

#include <stdio.h>
#include <dos.h>
#include <windows.h>
#include <windowsx.h>
#include <winsock2.h>
#include <time.h>
#include <string.h>
#include <malloc.h>
#include <process.h>
#include <conio.h>
#include <shellapi.h>
#include <commctrl.h>
#include <malloc.h>
#include <io.h>
#include <mmsystem.h>
#include <sys/types.h>
#include <sys/timeb.h>

#include "NetGE_Mainfunc.h"
#include "Netge_Packet.h"
#include "Netge_Connection.h"
#include "Netge_Event_Def.h"
#include "Netge_Event_Struct_Def.h"
#pragma comment(lib,"winmm")
#pragma comment(lib,"comctl32")

//#include "Netge.h"

#include "DoorServer_Create.h"
#include "DoorServerShutDown.h"
#include "Log.h"

#include "CloseSocket.h"
#include "ProcessSocket.h"
#include "InitSocket.h"

#include "Resource.h"
#include "StatusBar.h"
#include "ListView.h"

//#include "InitWorldData.h"
//#include "Netge_NPC_def.h"

//#include "DoorServerGlobal.h"
#include "DoorServerMisc.h"	
//#include "ServerLzo.h"

//-------------------------------------------------------------------------------

#define     WM_ASYNCSELECT			     WM_USER+1000
#define     WM_SYNC                      WM_USER+1001
#define     CURRENT_VERSION              500
// ---------------------------------------------------------------------------
// WorldServer Information Struct Define
// 世界伺服器資訊
// ---------------------------------------------------------------------------
typedef struct POS_WORLDINFO                  
{
 DWORD          dwSocket;
 DWORD          dwIndex;
 DWORD		   	dwPort;
 char        	cAddr[16];
 DWORD	        dwPlayerCount;
 char	        cName[32]; 
 DWORD          dwActive;        // 1-ON , 0-OFF
}TPOS_WORLDINFO;

#include "DoorServer_Ext_Var.h"
//-------------------------------------------------------------------------------
#endif // DOORSERVER_DEF_H
