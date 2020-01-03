#ifndef LISTVIEW_H
#define LISTVIEW_H
//---------------------------------------------------------------------------
#define		ID_LISTVIEW				2000

BOOL DoContextMenu(HWND hWnd, HINSTANCE hInst, WPARAM wParam, LPARAM lParam);
void ClearListView(HWND hwnd);
int GetSelectLVItem(HWND hwnd);
void DeleteOneLVItem(HWND hwnd, char *desc);
BOOL InsertLVItem(HWND hwnd, DWORD index, LPSTR str1, LPSTR str2, LPSTR str3,LPSTR str4,LPSTR str5);
HWND CreateListView(HINSTANCE hinst, HWND hwndParent);
DWORD FindLVItem(HWND hwnd,char *desc);
void SetLVItem(HWND hwnd,DWORD index,DWORD subindex,char *desc);
void GetOneLVItem(HWND hwnd, char *str,DWORD index,DWORD subindex,DWORD str_len);
int  GetLVItemCount(HWND hwnd);

#endif