#ifndef WORLDSERVER_DEF_H
#define WORLDSERVER_DEF_H
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

#pragma comment(lib,"winmm")
#pragma comment(lib,"comctl32")

//#include "Netge.h"
#include "Netge_Packet.h"
#include "Netge_Connection.h"
#include "Netge_Event_Def.h"
#include "Netge_Event_Struct_Def.h"
#include "Netge_Marco_Def.h"
#include "WorldServer_Create.h"
#include "WorldServerShutDown.h"
#include "InitWorldData.h"

#include "CloseSocket.h"
#include "ProcessSocket.h"
#include "InitSocket.h"

#include "Resource.h"
#include "StatusBar.h"
#include "ListView.h"

//#include "WorldServer_Weather.h"

//#include "Netge_Weather_Def.h"
//#include "WeatherHeartBeat.h"

//#include "Netge_NPC_def.h"

#include "WorldServerMisc.h"
#include "Log.h"	
//-------------------------------------------------------------------------------

#define     WM_ASYNCSELECT			     WM_USER+1000
#define     WM_SYNC                      WM_USER+1001
#define     CURRENT_VERSION              500   //2002.12.20. update.


//-------------------------------------------------------------------------------
#include "WorldServer_Ext_Var.h"

#endif // WORLDSERVER_DEF_H
