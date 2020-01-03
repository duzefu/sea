//-------------------------------------------------------------------------------
// Psalm of Sea WorldServer StatusBar
// By Hawke Hsieh
// 2002-10-7
//-------------------------------------------------------------------------------
#include "WorldServer_Def.h"
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
	DWORD			parts[6];
	char			str[256];

	hDc = GetDC(hpWnd);
	GetClientRect(hpWnd, &r);
	GetTextMetrics(hDc, &tm);

	parts[0] = tm.tmMaxCharWidth * 7;
	parts[1] = tm.tmMaxCharWidth * 19;
	parts[2] = tm.tmMaxCharWidth * 26;
	parts[3] = tm.tmMaxCharWidth * 38;
	parts[4] = tm.tmMaxCharWidth * 45;
	parts[5] = r.right;

	SendMessage(hwnd, SB_SETPARTS, 6, (long)parts);
	

	sprintf(str, "Now Login : %d",dwOnlineLoginer);
	SendMessage(hwnd, SB_SETTEXT, 0, (long)str);
	sprintf(str, "Now All World Player : %d",dwOnlineAllWorldPlayer);
	//strcpy(str, "Now All World Player : 0");	
	SendMessage(hwnd, SB_SETTEXT, 1, (long)str);
	sprintf(str, "Max Login : %d",dwOnlineMaxLoginer);
	//strcpy(str, "Max Login : 0");
	SendMessage(hwnd, SB_SETTEXT, 2, (long)str);
	sprintf(str, "Max All World Player : %d",dwOnlineAllWorldMaxPlayer);
	//strcpy(str, "Max All World Player : 0");
	SendMessage(hwnd, SB_SETTEXT, 3, (long)str);
	sprintf(str, "Now Zone : %d",iZoneCount);
	//strcpy(str, "Now Zone : 0");
	SendMessage(hwnd, SB_SETTEXT, 4, (long)str);
	sprintf(str, "Connected : %d",dwConnectedCounter);
	//strcpy(str, "Connected : 0");
	SendMessage(hwnd, SB_SETTEXT, 5, (long)str);
	

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
		char	str[256];
		wsprintf(str, "%d", GetLastError());
//		dout(str); 
		return NULL;
	}

	InitStatusBar(hwndParent, hwnd);

	return hwnd;
}
// ---------------------------------------------------------------------------