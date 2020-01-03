#ifndef _ZONESERVER_CREATE_H_
#define _ZONESERVER_CREATE_H_

int CreateInit();
int Active();
int StartZoneServer();
int SetConnectInfo();
int	ReLoginDoorAndWorld();
SLONG	LoadZoneMacroFile(char *Name);
BOOL	CheckHaveManagerFile();

#endif