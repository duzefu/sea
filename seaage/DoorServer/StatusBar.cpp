//-------------------------------------------------------------------------------
// Psalm of Sea DoorServer StatusBar
// By Hawke Hsieh
// 2002-10-7
//-------------------------------------------------------------------------------
#include "DoorServer_Def.h"
// ---------------------------------------------------------------------------
void MsgOut(HWND hwnd, DWORD column, char *s)
{
	SendMessage(hwnd, SB_SETTEXT, column, (long)s);
}
// ---------------------------------------------------------------------------
void InitStatusBar(HWND hpWnd, HWND hwnd)
{
	RECT			r;
	TEXTMETRIC		tm;
	HDC				hDc;
	DWORD			parts[3];
	char			str[20];


	hDc = GetDC(hpWnd);
	GetClientRect(hpWnd, &r);
	GetTextMetrics(hDc, &tm);

	parts[0] = tm.tmMaxCharWidth * 10;
	parts[1] = tm.tmMaxCharWidth * 30;
	parts[2] = tm.tmMaxCharWidth * 50;	

	SendMessage(hwnd, SB_SETPARTS, 3, (long)parts);
	

	sprintf(str, "Now Player : %d",dwOnlinePlayer);
	SendMessage(hwnd, SB_SETTEXT, 0, (long)str);	
	sprintf(str, "Now World : %d",iWorldCount);	
	SendMessage(hwnd, SB_SETTEXT, 1, (long)str);
	sprintf(str, "Connected : %d",dwConnectedCounter);	
	SendMessage(hwnd, SB_SETTEXT, 2, (long)str);
	

	ReleaseDC(hpWnd, hDc);
}

// ---------------------------------------------------------------------------
// HWND CreateStatusBar(HINSTANCE hinst, HWND hwndParent)
HWND CreateStatusBar(HINSTANCE hinst, HWND hwndParent)
{
	HWND		hwnd;


	hwnd = CreateWindow(STATUSCLASSNAME,
					   "", 
					   WS_CHILD | WS_VISIBLE,
					   0,0,0,0,
					   hwndParent, NULL, hinst, NULL);
	if(hwnd == NULL) 
	{ 
		char	str[20];
		wsprintf(str, "%d", GetLastError());
//		dout(str); 
		return NULL;
	}

	InitStatusBar(hwndParent, hwnd);

	return hwnd;
}
// ---------------------------------------------------------------------------