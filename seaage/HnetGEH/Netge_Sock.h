#ifndef NETGE_SOCK_H
#define NETGE_SOCK_H

#include "Netge_Extern.h"
#include "ServerLzo.h"

BOOL WINAPI DoorSocketWndInit(void);
BOOL WINAPI WorldSocketWndInit(void);
BOOL WINAPI ZoneSocketWndInit(void);
BOOL WINAPI ZoneSyncSocketWndInit(void);
int	CloseOneSocket(SOCKET tmp_socket);
int CloseOneConnection(TPOS_CN *cn);
int QueuePacket(TPOS_CN *cn, TPOS_COMPACKET *packet, HWND hwnd);
int ReadPacket(TPOS_CN *cn);
int WritePacket(TPOS_CN *cn);
void SaveMsgToLog(char *str);

#endif // NETGE_SOCK_H