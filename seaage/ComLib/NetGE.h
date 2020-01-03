#ifndef __NETGE_H__
#define __NETGE_H__

#define NETGE_EXPORTS
// ---------------------------------------------------------------------------
#ifdef NETGE_EXPORTS
#define NETGE_API __declspec(dllexport)
#define NETGE_FNB 
#else
#define NETGE_API __declspec(dllimport)
#define NETGE_FNB
#endif

extern "C"
{
#ifdef BCBUSED
	
NETGE_API int _PosGetCurrentConnectedType();
NETGE_API int _PosFreeMemory();
NETGE_API int _PosInit();
NETGE_API ULONG _PosGetTotalRecvDataSize();
NETGE_API ULONG _PosGetTotalSendDataSize();
NETGE_API int _PosSetTotalRecvDataSize(ULONG size);
NETGE_API int _PosSetTotalSendDataSize(ULONG size);

NETGE_API int _PosLoginDoor(HWND hWnd, char FAR *ServerName, int port, char *id, char *Password,DWORD Version);
NETGE_API int _PosLogoutDoor();	
NETGE_API int _PosSendDataToDoor(DWORD dwEventType, char FAR *cData, DWORD dwSize);
NETGE_API int _PosRecvDataFromDoor(DWORD &dwEventType, char FAR *cData, DWORD &dwSize);
NETGE_API int _PosLoginWorld(HWND hWnd, char FAR *ServerName, int port, char *id, char *Password,DWORD Version);
NETGE_API int _PosLogoutWorld();	
NETGE_API int _PosSendDataToWorld(DWORD dwEventType, char FAR *cData, DWORD dwSize);
NETGE_API int _PosRecvDataFromWorld(DWORD &dwEventType, char FAR *cData, DWORD &dwSize);
NETGE_API int _PosLoginZone(HWND hWnd, char FAR *ServerName, int port, char *MainName,DWORD Version);
NETGE_API int _PosLogoutZone();	
NETGE_API int _PosSendDataToZone(DWORD dwEventType, char FAR *cData, DWORD dwSize);
NETGE_API int _PosRecvDataFromZone(DWORD &dwEventType, char FAR *cData, DWORD &dwSize);

#else

NETGE_API int NETGE_FNB PosGetCurrentConnectedType();
NETGE_API int NETGE_FNB PosFreeMemory();
NETGE_API int NETGE_FNB PosInit();
NETGE_API ULONG NETGE_FNB PosGetTotalRecvDataSize();
NETGE_API ULONG NETGE_FNB PosGetTotalSendDataSize();
NETGE_API int NETGE_FNB PosSetTotalRecvDataSize(ULONG size);
NETGE_API int NETGE_FNB PosSetTotalSendDataSize(ULONG size);

NETGE_API int NETGE_FNB PosLoginDoor(HWND hWnd, char FAR *ServerName, int port, char *id, char *Password,DWORD Version);
NETGE_API int NETGE_FNB PosLogoutDoor();	
NETGE_API int NETGE_FNB PosSendDataToDoor(DWORD dwEventType, char FAR *cData, DWORD dwSize);
NETGE_API int NETGE_FNB PosRecvDataFromDoor(DWORD &dwEventType, char FAR *cData, DWORD &dwSize);
NETGE_API int NETGE_FNB PosLoginWorld(HWND hWnd, char FAR *ServerName, int port, char *id, char *Password,DWORD Version);
NETGE_API int NETGE_FNB PosLogoutWorld();	
NETGE_API int NETGE_FNB PosSendDataToWorld(DWORD dwEventType, char FAR *cData, DWORD dwSize);
NETGE_API int NETGE_FNB PosRecvDataFromWorld(DWORD &dwEventType, char FAR *cData, DWORD &dwSize);
NETGE_API int NETGE_FNB PosLoginZone(HWND hWnd, char FAR *ServerName, int port, char *MainName,DWORD Version);
NETGE_API int NETGE_FNB PosLogoutZone();	
NETGE_API int NETGE_FNB PosSendDataToZone(DWORD dwEventType, char FAR *cData, DWORD dwSize);
NETGE_API int NETGE_FNB PosRecvDataFromZone(DWORD &dwEventType, char FAR *cData, DWORD &dwSize);

#endif
}

#endif // __NETGE_H__