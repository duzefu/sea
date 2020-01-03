#ifndef ZONESERVER_VAR_H
#define ZONESERVER_VAR_H
//-------------------------------------------------------------------------------
//#include "ZoneServer_Def.h"

HINSTANCE           MainhInst;
HINSTANCE        	dInstance;
HINSTANCE	        wInstance;
HINSTANCE	        zInstance;
HINSTANCE	        zsInstance;
HWND                ParenthWnd;
HWND                dParenthWnd;
HWND                wParenthWnd;
HWND                zParenthWnd;
char	            szClassName[] = "ZoneServer_VC";
char             	DoorClassName[] = "DOORSOCKET";
char             	WorldClassName[] = "WORLDSOCKET";
char             	ZoneClassName[] = "ZONESOCKET";
char             	ZoneSyncClassName[] = "ZONESYNCSOCKET";
HWND		    	DoorSockethWnd;
HWND		    	WorldSockethWnd;
HWND		    	ZoneSockethWnd;
HWND		    	ZoneSyncSockethWnd;
HWND                MainhWnd;
HWND                SetuphWnd; 
HWND                ReloginhWnd; 
HWND			    hStatusBarWnd;
HWND		        hListViewWnd;; 

struct _timeb       timebuffer;
//struct  tm        nowtime;
//struct          nowdate;

POS_PACKET          Pos_Packet;

TPOS_CN	           *Pos_Cn;
TPOS_CN	           *Pos_Cn_Sync;
TPOS_CN	           *World;
TPOS_CN	           *Zone;
TPOS_CN	           *ZoneSync;
TPOS_CN	           *Door;

int                 ZoneServerPort;
char                ZoneServerIP[16];
char   		        ZoneName[32];
char				WorldServerName[32];
int                 WorldServerPort;
char   	            WorldServerAddr[16];
char   	            DoorServerAddr[16];

DWORD               DoorServerPort;

TPOS_ZONEINFO       ZoneInfo[MAX_ZONE_PER_WORLD];

//char                CurrentPacket[MAX_PACKET_SIZE];
TPOS_SYNCMOVE       *SyncMove;
TPOS_SYNCSEAMOVE	*SyncSeaMove;
//char                buf[10240];

WORD                WSA_EVENT;

DWORD               dwConnectedCounter;	       //已連線總人數
DWORD               dwOnlineCounter;	       //目前線上人數

BOOL                bZoneServerStart=false;    //Server是否啟動

BOOL                bDSReadingNow = false;     //是否讀取資料

DWORD               dwRequestForWorldInfoIndex;

//LPTCPOS_WORLDINFO   lpWorldInfo=NULL;
TPOS_WORLDINFO      *GetWorldInfoFromDoor;      // 從 DoorServer 收到
                                                // 目前所有的 World Server Info
TPOS_ZONEINFO       *GetZoneInfoFromMarco;		// 從 Marco 解開
//                                              // 目前所有的 Zone Server Info

bool                bCheckCharacterState=false; // 是否檢查角色狀態
bool                bCheckSYNC=false;           // 是否檢查同步

bool                UDP_Connected=false;
bool                UDP_Group_Connected=false;

DATA_FILE          *sea_data_file;              // 地圖阻擋打包

DWORD               refresh=0;                  // 運算更新計數
DWORD				savecount=0;				// 儲存的角色索引

TPOS_ZONEWEATHER    *ZoneWeather;               // 區域天氣結構  
TPOS_MACRO_WORLD    *Macro=NULL;                // 劇本結構
TPOS_MACRO_ZONE		*ZoneMacro=NULL;
TPOS_NPC            *NPCType;                   // NPC 類型表
//TPOS_MAGIC          *MagicType;                 // 招式類型表
//TPOS_ITEM           *ItemType;                  // 物品類型表
int                 uncompresssize=0;
int                 compresssize=0;
char                *compressbuf=NULL;          // 壓縮暫存區
char                *SyncCompressBuf=NULL;      // 同步壓縮暫存  
char                mapname[32];
int                 ZoneActive=0;

char                cWorldServerName[32];       // 系統公告 世界伺服器名稱     
char                cSystemMessage[256];		// 系統公告 公告內容

DWORD               ServerType=0x00000000;      // 封包送出的目標伺服器種類 
bool                ServerStart = FALSE; 
TPOS_ZONEMAPDEFAULT ZoneMapDefault[MAX_ZONE_PER_MACRO];         // 預設區域地圖名稱 
DWORD				ZoneType=0;					 // 地圖的類型 

TPOS_MAPLINK        MapLink[1];	                 // 連接口的資料 
DWORD               MapIndex;                    // 當前地圖的編號 (對應預設區域資料)    
BOOL				BadConnect[MAX_PLAYER_PER_ZONE];// 不正常斷線的連接列表
DWORD				DoCloseBadConnectCount = 0;  // 處理不正常斷線的Counter;

BOOL				HaveManagerFile=FALSE;		 // 有管理系統的啟動檔	
char				WindowCaption[256];

//TPOS_QQ_ONLINE_PLAYER_LIST *QQOnlinePlayerList;

//-------------------------------------------------------------------------------
#endif