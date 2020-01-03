/*
**	Client_Thread.h 
**	client thread functions header.
**
**	Jack, 2003.1.14
*/
#pragma once


//
// STRUCTURES ///////////////////////////////////////////////////////////////////////////////////////////////
//
typedef	struct tagAPPMSG 
{
	DWORD	idFrom;
	DWORD	idTo;
	DWORD	dwType;
	DWORD	dwSize;
	LPVOID	lpBuffer;
} APPMSG, *LPAPPMSG;


//
// GLOBALS //////////////////////////////////////////////////////////////////////////////////////////////////
//
extern	HWND    g_hWndGameEvent;


//
// FUNCTIONS ////////////////////////////////////////////////////////////////////////////////////////////////
//
int     init_client(void);
void    active_client(int active);
void    free_client(void);
//
void    AddClientRecvMsg( LPVOID lpBuffer, DWORD dwType, DWORD dwSize, DWORD idFrom, DWORD idTo);
void    ClientProcessMsg( void );



