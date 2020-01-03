#ifndef _PROCESSSOCKET_H_
#define _PROCESSSOCKET_H_

int FindCurrentConnection(WPARAM wParam);
int FindUsableConnection(void);
DWORD   FindConnectionIsZone(int index);
int		FindConnectionByID(char *id);
DWORD   FindConnectionByZoneName(CHAR *zonename);
int		FindConnectionBySocket(DWORD socket);
int		CloseOldConnection(CHAR	*ID);

int ReadPacket(TPOS_CN *cn);
int WritePacket(TPOS_CN *cn);
int QueuePacket(TPOS_CN *cn, TPOS_COMPACKET *packet,DWORD ServerType);
int ProcessPacket(TPOS_CN *cn);
LRESULT CALLBACK DoorSocketWndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WorldSocketWndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
void RefreshAllWorldPlayer();
void SendNewZoneInfoToAll(char *str,DWORD playercount,char *addr,DWORD port,char *mapname,DWORD zonetype);
void SendZoneRefreshInfoToAll(char *str,DWORD playercount);
void SendSystemMessageToAll(char *msg);
void SendCloseZoneInfoToAll(char *str,DWORD index);
void SendRepeatLoginedPlayer(DWORD index, TPOS_PACKET *packet);
int  ServerSendPacketToOne(void *connect, void *packet);
void CompressPacket(TPOS_PACKET	*packet, TPOS_COMPACKET *compacket);

#endif