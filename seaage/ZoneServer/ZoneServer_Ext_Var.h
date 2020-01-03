#ifndef ZONESERVER_EXT_VAR_H
#define ZONESERVER_EXT_VAR_H
//-------------------------------------------------------------------------------
//#include "ZoneServer_Def.h"

extern HINSTANCE            MainhInst;
extern HINSTANCE        	dInstance;
extern HINSTANCE	        wInstance;
extern HINSTANCE	        zInstance;
extern HINSTANCE	        zsInstance;
extern HWND                ParenthWnd;
extern HWND                dParenthWnd;
extern HWND                wParenthWnd;
extern HWND                zParenthWnd;
extern char             	DoorClassName[];// = "DOORSOCKET";
extern char             	WorldClassName[];// = "WORLDSOCKET";
extern char             	ZoneClassName[];// = "ZONESOCKET";
extern char             	ZoneSyncClassName[];/// = "ZONESYNCSOCKET";
extern char	               szClassName[];// = "ZoneServer_VC";
extern HWND		    	   DoorSockethWnd;
extern HWND		    	   WorldSockethWnd;
extern HWND		    	   ZoneSockethWnd;
extern HWND		    	   ZoneSyncSockethWnd;
extern HWND                MainhWnd;
extern HWND                SetuphWnd;
extern HWND                ReloginhWnd; 
extern HWND			       hStatusBarWnd;
extern HWND		           hListViewWnd;; 

extern struct  tm        nowtime;
//struct          nowdate;

extern POS_PACKET          Pos_Packet;
	
extern	TPOS_CN	           *Pos_Cn;
extern	TPOS_CN	           *Pos_Cn_Sync;
extern	TPOS_CN	           *World;
extern	TPOS_CN	           *Zone;
extern	TPOS_CN	           *ZoneSync;
extern	TPOS_CN	           *Door;

extern	int                 ZoneServerPort;
extern	char                ZoneServerIP[16];
extern	char   		        ZoneName[32];
extern	char				WorldServerName[32];
extern	int			        WorldServerPort;
extern	char   			    WorldServerAddr[16];
extern	char   	            DoorServerAddr[16];

extern	DWORD               DoorServerPort;

extern	TPOS_ZONEINFO       ZoneInfo[MAX_ZONE_PER_WORLD];

extern	TPOS_SYNCMOVE       *SyncMove;
extern	TPOS_SYNCSEAMOVE    *SyncSeaMove;

extern	WORD                WSA_EVENT;

extern	DWORD               dwConnectedCounter;	       //�w�s�u�`�H��
extern	DWORD               dwOnlineCounter;	       //�ثe�u�W�H��

extern	BOOL                bZoneServerStart;//=false;    //Server�O�_�Ұ�

extern	BOOL                bDSReadingNow;// = false;     //�O�_Ū�����

extern	DWORD               dwRequestForWorldInfoIndex;

//extern LPTCPOS_WORLDINFO   lpWorldInfo;//=NULL;
extern	TPOS_WORLDINFO      *GetWorldInfoFromDoor;      // �q DoorServer ����
                                                // �ثe�Ҧ��� World Server Info
extern	TPOS_ZONEINFO       *GetZoneInfoFromMarco;     // �q Marco �Ѷ}
//                                                // �ثe�Ҧ��� Zone Server Info

extern	bool                bCheckCharacterState;//=false; // �O�_�ˬd���⪬�A
extern	bool                bCheckSYNC;//=false;           // �O�_�ˬd�P�B

extern	bool                UDP_Connected;//=false;
extern	bool                UDP_Group_Connected;//=false;

extern	DATA_FILE          *sea_data_file;              // �a�Ϫ��ץ��]

extern	DWORD               refresh;//=0;                // �B���s�p��
extern	DWORD				savecount;					// �x�s���������

extern	TPOS_ZONEWEATHER    *ZoneWeather;                   // �ϰ�Ѯ𵲺c  
extern	TPOS_MACRO_WORLD    *Macro;                     // �@�����c
extern	TPOS_MACRO_ZONE		*ZoneMacro;
extern	TPOS_NPC            *NPCType;                   // NPC ������

extern	int                 uncompresssize;//=0;
extern	int                 compresssize;//=0;
extern	char                *compressbuf;//=NULL;          // ���Y�Ȧs��
extern	char                *SyncCompressBuf;//=NULL;      // �P�B���Y�Ȧs  
extern	char                mapname[32];
extern	int                 ZoneActive;
extern	DWORD               ServerType;                 // �ʥ]�e�X���ؼЦ��A������ 

extern	char                cWorldServerName[32];       // �t�Τ��i �@�ɦ��A���W��     
extern	char                cSystemMessage[256];		// �t�Τ��i ���i���e
extern	DWORD				ZoneType;					 // �a�Ϫ����� 

extern	struct _timeb       timebuffer;
extern	bool                ServerStart; 
extern	TPOS_ZONEMAPDEFAULT ZoneMapDefault[MAX_ZONE_PER_MACRO];          // �w�]�ϰ�a�ϦW�� 
extern	TPOS_MAPLINK        MapLink[1];		                // �s���f����� 
extern	DWORD               MapIndex;                    // ��e�a�Ϫ��s�� (�����w�]�ϰ���)
extern	BOOL				BadConnect[MAX_PLAYER_PER_ZONE];// �����`�_�u���s���C��
extern	DWORD				DoCloseBadConnectCount;  // �B�z�����`�_�u��Counter;

extern	BOOL				HaveManagerFile;		 // ���޲z�t�Ϊ��Ұ���	
extern	char				WindowCaption[256];

//extern TPOS_QQ_ONLINE_PLAYER_LIST *QQOnlinePlayerList;
//-------------------------------------------------------------------------------
#endif