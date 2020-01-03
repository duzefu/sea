#ifndef _CLOSESOCKET_H_
#define _CLOSESOCKET_H_

int CloseOneSocket(SOCKET tmp_socket);
int CloseOneConnection(TPOS_CN *cn);
int CloseWorldServer(void);
int CloseDoorServer(void);

#endif