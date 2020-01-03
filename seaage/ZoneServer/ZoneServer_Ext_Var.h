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

extern	DWORD               dwConnectedCounter;	       //已連線總人數
extern	DWORD               dwOnlineCounter;	       //目前線上人數

extern	BOOL                bZoneServerStart;//=false;    //Server是否啟動

extern	BOOL                bDSReadingNow;// = false;     //是否讀取資料

extern	DWORD               dwRequestForWorldInfoIndex;

//extern LPTCPOS_WORLDINFO   lpWorldInfo;//=NULL;
extern	TPOS_WORLDINFO      *GetWorldInfoFromDoor;      // 從 DoorServer 收到
                                                // 目前所有的 World Server Info
extern	TPOS_ZONEINFO       *GetZoneInfoFromMarco;     // 從 Marco 解開
//                                                // 目前所有的 Zone Server Info

extern	bool                bCheckCharacterState;//=false; // 是否檢查角色狀態
extern	bool                bCheckSYNC;//=false;           // 是否檢查同步

extern	bool                UDP_Connected;//=false;
extern	bool                UDP_Group_Connected;//=false;

extern	DATA_FILE          *sea_data_file;              // 地圖阻擋打包

extern	DWORD               refresh;//=0;                // 運算更新計數
extern	DWORD				savecount;					// 儲存的角色索引

extern	TPOS_ZONEWEATHER    *ZoneWeather;                   // 區域天氣結構  
extern	TPOS_MACRO_WORLD    *Macro;                     // 劇本結構
extern	TPOS_MACRO_ZONE		*ZoneMacro;
extern	TPOS_NPC            *NPCType;                   // NPC 類型表

extern	int                 uncompresssize;//=0;
extern	int                 compresssize;//=0;
extern	char                *compressbuf;//=NULL;          // 壓縮暫存區
extern	char                *SyncCompressBuf;//=NULL;      // 同步壓縮暫存  
extern	char                mapname[32];
extern	int                 ZoneActive;
extern	DWORD               ServerType;                 // 封包送出的目標伺服器種類 

extern	char                cWorldServerName[32];       // 系統公告 世界伺服器名稱     
extern	char                cSystemMessage[256];		// 系統公告 公告內容
extern	DWORD				ZoneType;					 // 地圖的類型 

extern	struct _timeb       timebuffer;
extern	bool                ServerStart; 
extern	TPOS_ZONEMAPDEFAULT ZoneMapDefault[MAX_ZONE_PER_MACRO];          // 預設區域地圖名稱 
extern	TPOS_MAPLINK        MapLink[1];		                // 連接口的資料 
extern	DWORD               MapIndex;                    // 當前地圖的編號 (對應預設區域資料)
extern	BOOL				BadConnect[MAX_PLAYER_PER_ZONE];// 不正常斷線的連接列表
extern	DWORD				DoCloseBadConnectCount;  // 處理不正常斷線的Counter;

extern	BOOL				HaveManagerFile;		 // 有管理系統的啟動檔	
extern	char				WindowCaption[256];

//extern TPOS_QQ_ONLINE_PLAYER_LIST *QQOnlinePlayerList;
//-------------------------------------------------------------------------------
#endif