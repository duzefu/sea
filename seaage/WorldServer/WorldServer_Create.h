#ifndef _WORLDSERVER_CREATE_H_
#define _WORLDSERVER_CREATE_H_

#define COMPRESS_BUF_SIZE           16777216

void CreateInit();
int  Active();
int  StartWorldServer();
int  SetConnectInfo();
SLONG   server_load_macro(USTR *filename);
BOOL	CheckHaveManagerFile();

#endif