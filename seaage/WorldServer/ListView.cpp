//-------------------------------------------------------------------------------
// Psalm of Sea WorldServer ListView
// By Hawke Hsieh
// 2002-10-7
//-------------------------------------------------------------------------------
#include "WorldServer_Def.h"
//---------------------------------------------------------------------------
BOOL DoContextMenu(HWND hWnd, HINSTANCE hInst, WPARAM wParam, LPARAM lParam)
{
	HWND  hwndListView = (HWND)wParam;
	HMENU hMenuLoad, hMenu;


	if(hwndListView != GetDlgItem(hWnd, ID_LISTVIEW))
	return FALSE;

	hMenuLoad = LoadMenu(hInst, MAKEINTRESOURCE(IDR_MENU2));
	hMenu = GetSubMenu(hMenuLoad, 0);

	TrackPopupMenu(hMenu,
                  TPM_LEFTALIGN | TPM_RIGHTBUTTON,
                  LOWORD(lParam),
                  HIWORD(lParam),
                  0,
                  hWnd,
                  NULL);

	DestroyMenu(hMenuLoad);

	return TRUE;
}

//---------------------------------------------------------------------------
void ClearListView(HWND hwnd)
{
	ListView_DeleteAllItems(hwnd); 
}
// ---------------------------------------------------------------------------
int GetLVItemCount(HWND hwnd)
{
	int count = 0;

	count = ListView_GetItemCount(hwnd);
	return count;
}
// ---------------------------------------------------------------------------
void GetOneLVItem(HWND hwnd, char *str,DWORD index,DWORD subindex,DWORD str_len)
{
	ListView_GetItemText(hwnd, index, subindex, str, str_len);
}
// ---------------------------------------------------------------------------
void GetSelectLVItem(HWND hwnd, char *str,DWORD str_len)
{
	DWORD		index;

	index = SendMessage(hwnd, LVM_GETNEXTITEM, -1, MAKELPARAM((UINT)LVNI_SELECTED, 0));
	ListView_GetItemText(hwnd, index, 0, str, str_len);
}
// ---------------------------------------------------------------------------
void SetLVItem(HWND hwnd,DWORD index,char *desc)
{
	ListView_SetItemText(hwnd,index,1,desc);
}
// ---------------------------------------------------------------------------
DWORD FindLVItem(HWND hwnd,char *desc)
{
	LVFINDINFO	lvfi;
	char		str[256];
	int			ret;	

	lvfi.flags = LVFI_PARTIAL;
	wsprintf(str, "%s", desc);
	lvfi.psz = str;
	ret = ListView_FindItem(hwnd, -1, &lvfi);
	if(ret!=-1)return ret;
	return -1;
}
// ---------------------------------------------------------------------------
void DeleteOneLVItem(HWND hwnd, char *desc)
{
	LVFINDINFO	lvfi;
	char		str[256];
	int			ret;

	lvfi.flags = LVFI_PARTIAL;
	wsprintf(str, "%s", desc);
	lvfi.psz = str;
	ret = ListView_FindItem(hwnd, -1, &lvfi);
	if(ret != -1) SendMessage(hwnd, LVM_DELETEITEM, ret, 0);
}

//---------------------------------------------------------------------------
BOOL InsertLVItem(HWND hwnd, DWORD index, LPSTR str1, LPSTR str2, LPSTR str3,LPSTR str4,LPSTR str5,LPSTR str6)
{
	LV_ITEM		lvI;        // List view item structure


	lvI.mask = LVIF_TEXT;

	lvI.iItem = index;
	lvI.iSubItem = 0;
	lvI.pszText = str1; 
	lvI.cchTextMax = strlen(str1);

	if(ListView_InsertItem(hwnd, &lvI) == -1) return FALSE;
	
	ListView_SetItemText(hwnd, index, 1, str2);
	ListView_SetItemText(hwnd, index, 2, str3);
	ListView_SetItemText(hwnd, index, 3, str4);
	ListView_SetItemText(hwnd, index, 4, str5);
	ListView_SetItemText(hwnd, index, 5, str6);

	return TRUE;
}

//---------------------------------------------------------------------------
HWND CreateListView(HINSTANCE hinst, HWND hwndParent)
{
	HWND		hwnd;
	RECT		r;
	LV_COLUMN	part;


	GetClientRect(hwndParent, &r);
	hwnd = CreateWindow(TEXT("SysListView32"), 
								NULL, 
								WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_BORDER |
								LVS_REPORT | LVS_SHOWSELALWAYS | LVS_SINGLESEL ,								
								r.left, r.top, r.right, r.bottom-20,
								hwndParent, (HMENU)ID_LISTVIEW, hinst, NULL);
	
	if(hwnd == NULL) 
	{ 
		char	str[256];
		wsprintf(str, "%d", GetLastError());
//		dout(str); 
		return NULL; 
	}
	
	part.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_FMT;
	part.fmt = LVCFMT_LEFT;
	part.cchTextMax = 10;
	part.pszText = "ZoneServer";
	part.cx = 150;
	ListView_InsertColumn(hwnd, 0, &part);
	part.pszText = "Online Player Count";
	part.cx = 120;
	ListView_InsertColumn(hwnd, 1, &part);
	part.pszText = "IP";
	part.cx = 100;
	ListView_InsertColumn(hwnd, 2, &part);
	part.pszText = "Port";
	part.cx = 100;
	ListView_InsertColumn(hwnd, 3, &part);
	part.pszText = "MapName";
	part.cx = 100;
	ListView_InsertColumn(hwnd, 4, &part);
	part.pszText = "Status";
	part.cx = 80;
	ListView_InsertColumn(hwnd, 5, &part);

	SendMessage(hwnd,LVM_SETEXTENDEDLISTVIEWSTYLE,0,
		        LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP | LVS_EX_GRIDLINES);	   
	
	return hwnd;    
}

//---------------------------------------------------------------------------