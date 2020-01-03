#ifndef _PROCESSSOCKET_H_
#define _PROCESSSOCKET_H_

int FindCurrentConnection(WPARAM wParam);
int FindConnectionByID(char *ID);
int FindUsableConnection(void);
int	FindConnectionBySocket(DWORD socket);
int FindConnectionIsWorld(int index);
int ReadPacket(TPOS_CN *cn);
int WritePacket(TPOS_CN *cn);
int QueuePacket(TPOS_CN *cn, TPOS_COMPACKET *compacket);
int ProcessPacket(TPOS_CN *cn);
LRESULT CALLBACK DoorSocketWndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
void SendCloseWorldInfoToAll(char *str,DWORD index);
void SendNewWorldInfoToAll(char *str,DWORD playercount,char *addr,DWORD port,DWORD active);
void SendWorldRefreshInfoToAll(char *str,DWORD playercount,DWORD active);
void CompressPacket(TPOS_PACKET	*packet, TPOS_COMPACKET *compacket);		
#endif