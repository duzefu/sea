#ifndef ZONESERVER_DEF_H
#define ZONESERVER_DEF_H
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

#pragma comment(lib,"winmm")
#pragma comment(lib,"comctl32")

//#include "Netge_Struct_Def.h"
//#include "Netge.h"
#include "Netge_Mainfunc.h"
#include "Netge_Packet.h"
#include "Netge_Connection.h"
#include "Netge_NPC_def.h"
#include "Netge_Event_Def.h"
#include "Netge_Event_Struct_Def.h"
#include "Netge_Marco_Def.h"
#include "Netge_NPC_Def.h"
#include "Netge_Weather_Def.h"
#include "ServerCharacterDoing.h"	
#include "ServerMagicHit.h"
#include "ZoneServerMisc.h"
#include "Resource.h"
#include "InitZoneData.h"
#include "Log.h"
//#include "ServerLzo.h"

#include "CloseSocket.h"
#include "ProcessSocket.h"
#include "InitSocket.h"

#include "ZoneServer_Create.h"
#include "ZoneServerShutDown.h"

#include "HeartBeat.h"
#include "SyncHeartBeat.h"
#include "SyncPositionHeartBeat.h"
#include "SaveDataHeartBeat.h"

#include "ZoneServer_Ext_Var.h"
#include "ServerCharacterDoing.h"
#include "ServerDoingFunction.h"
#include "ServerFight.h"
#include "ServerRefreshGame.h"
#include "mcdef.h"		
#include "ServerDecodeMacro.h"
#include "ServerMagic.h"	
#include "ServerItem.h"
#include "ServerTeam.h"
#include "ServerQuest.h"
#include "ServerEnemy.h"
#include "ServerFindGold.h"
// 2002-12-04 Add for QQ by Hawke
//#include "QQDataMisc.h"
// 2002-12-17 Add for Sync Sea Position
#include "SyncSeaPositionHeartBeat.h"
//-------------------------------------------------------------------------------

#define     WM_ASYNCSELECT			     WM_USER+1000
#define     WM_SYNC                      WM_USER+1001
#define     CURRENT_VERSION              500


//-------------------------------------------------------------------------------
// Main.cpp
//-------------------------------------------------------------------------------
int _stdcall WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow);
BOOL Main_Init(HINSTANCE hInstance, int nCmdShow);
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK DlgSetupProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK DlgReloginProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

#endif // ZONESERVER_DEF_H
