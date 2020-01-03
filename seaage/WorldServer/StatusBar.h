#ifndef STATUSBAR_H
#define STATUSBAR_H

void MsgOut(HWND hwnd, DWORD column, char *s);
void InitStatusBar(HWND hpWnd, HWND hwnd);
HWND CreateStatusBar(HINSTANCE hinst, HWND hwndParent);

#endif