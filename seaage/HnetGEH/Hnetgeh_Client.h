#ifndef HNETGEH_CLIENT_H
#define HNETGEH_CLIENT_H

#define NETGE_EXPORTS
// ---------------------------------------------------------------------------
#ifdef NETGE_EXPORTS
#define NETGE_API __declspec(dllexport)
#define NETGE_FNB 
#else
#define NETGE_API __declspec(dllimport)
#define NETGE_FNB
#endif

// ---------------------------------------------------------------------------
// POSGAMEEVENT 
// ---------------------------------------------------------------------------
#define		WM_POSGAMEEVENT		 	WM_USER+1001
// ---------------------------------------------------------------------------
// Init Winsocket Erroe Message
// ---------------------------------------------------------------------------
#define		WINSOCK_VER_ERROR            	-1    // WINSOCKET 版本錯誤
#define		INIT_SOCKET_ERROR           	-2    // 起始 SOCKET 錯誤
#define		CANT_CONNECTED		         	-3    // 無法連結伺服器
#define		CANT_ASYNC   		         	-4    // 無法非同步連結

// ---------------------------------------------------------------------------
// Buffer Langeth Set
// ---------------------------------------------------------------------------
#define		MSG_STR_LEN		        		450   // 字串長度
#define		MAX_PACKET_SIZE	        	   1024   // 最大封包大小
#define     BUFSIZE                        1024   // 緩衝區大小
// ---------------------------------------------------------------------------
// ZoneInfo and WorldInfo and PlayerInfo Use
// ---------------------------------------------------------------------------
#define		BEGIN			        		0     
#define		NEXT			        		1
#define     END                             99999 
// ---------------------------------------------------------------------------
// DLL Status Reply
// ---------------------------------------------------------------------------
#define		DLL_ERROR				        0				// return error from DLL
#define		DLL_OK					        1				// return ok from DLL
// ---------------------------------------------------------------------------
// Current Connected Server Type
// ---------------------------------------------------------------------------
#define     CONNECTED_SERVER_NONE           0x00000000      // 未連接任何伺服器
#define     CONNECTED_SERVER_DOOR           0x00000001      // 連接Door伺服器
#define     CONNECTED_SERVER_WORLD          0x00000002      // 連接World伺服器
#define     CONNECTED_SERVER_ZONE           0x00000004      // 連接Zone伺服器
// ---------------------------------------------------------------------------

//===============================================================================
#endif