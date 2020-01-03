//===============================================================================
// Netge_Def.h
//===============================================================================
#ifndef NETGE_DEF_H
#define NETGE_DEF_H
//===============================================================================

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//===============================================================================

#define WIN32_LEAN_AND_MEAN		

#include <stdio.h>
#include <windows.h>
#include <windowsx.h>
#include <winsock2.h>
#include <dos.h>
#include <string.h>
#include <malloc.h>
#include <process.h>
#include <conio.h>
#include <shellapi.h>
#include <commctrl.h>
#include <malloc.h>
#include <io.h>

#include "NetGe.h"
#include "Netge_Mainfunc.h"
#include "Netge_Event_Def.h"
#include "NetGE_Packet.h"
#include "NetGE_Connection.h"
#include "Netge_Door.h"

//===============================================================================

#define     WM_ASYNCSELECT			    WM_USER+1000
#define     WM_SYNC     			    WM_USER+999
#define		CURRENT_VERSION				500

//===============================================================================
//-------------------------------------------------------------------------------
// Login Door and World
//-------------------------------------------------------------------------------
typedef	struct POS_EVENT_LOGIN
{
	char	cId[32];
	char	cPw[32];
	DWORD	dwVersion;
}TPOS_EVENT_LOGIN;
//===============================================================================
#endif // NETGE_DEF_H