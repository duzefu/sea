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
#define		WINSOCK_VER_ERROR            	-1    // WINSOCKET �������~
#define		INIT_SOCKET_ERROR           	-2    // �_�l SOCKET ���~
#define		CANT_CONNECTED		         	-3    // �L�k�s�����A��
#define		CANT_ASYNC   		         	-4    // �L�k�D�P�B�s��

// ---------------------------------------------------------------------------
// Buffer Langeth Set
// ---------------------------------------------------------------------------
#define		MSG_STR_LEN		        		450   // �r�����
#define		MAX_PACKET_SIZE	        	   1024   // �̤j�ʥ]�j�p
#define     BUFSIZE                        1024   // �w�İϤj�p
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
#define     CONNECTED_SERVER_NONE           0x00000000      // ���s��������A��
#define     CONNECTED_SERVER_DOOR           0x00000001      // �s��Door���A��
#define     CONNECTED_SERVER_WORLD          0x00000002      // �s��World���A��
#define     CONNECTED_SERVER_ZONE           0x00000004      // �s��Zone���A��
// ---------------------------------------------------------------------------

//===============================================================================
#endif