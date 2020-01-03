#ifndef	_INITZONEDATA_H_
#define	_INITZONEDATA_H_

#define SYNC_COMPRESS_BUF_SIZE      16384
#define COMPRESS_BUF_SIZE           16777216
#define MAX_WORLD_INFO              500

// ---------------------------------------------------------------------------
// ZoneServer Information Struct Define
// 區域伺服器資訊 
// ---------------------------------------------------------------------------
typedef struct POS_ZONEINFO
{
	DWORD			dwSocket;
	DWORD			dwIndex;
	DWORD		   	dwPort;
	char           	cAddr[16];
	DWORD	        dwPlayerCount;
	char	        cName[32];
	char            cMapName[32]; 
	DWORD			dwType;		// 0 - 陸地 , 1 -海上 
}TPOS_ZONEINFO;
// ---------------------------------------------------------------------------
// WorldServer Information Struct Define
// 世界伺服器資訊
// ---------------------------------------------------------------------------
typedef struct POS_WORLDINFO                  
{
 DWORD          dwSocket;
 DWORD          dwIndex;
 DWORD		   	dwPort;
 char        	cAddr[16];
 DWORD	        dwPlayerCount;
 char	        cName[32]; 
 DWORD          dwActive;        // 1-ON , 0-OFF
}TPOS_WORLDINFO;
//----------------------------------------------------------------------------------
// 區域名稱和地圖名稱相對應的結構
//----------------------------------------------------------------------------------
typedef struct
{
    char   cZoneName[32];
    char   cMapName[32];
	DWORD  dType;	 	
}TPOS_ZONEMAPDEFAULT;
//-----------------------------------------------------------------------------------
// 單一連接點的資料
//-----------------------------------------------------------------------------------
typedef struct
{ 
    DWORD   ZoneData;       // 連接的區域編號  對應  ZoneMapDefault 的資料
    // 索取區域名稱和地圖名稱 
    long    lDestX;         // 目標城市座標
    long    lDestY;                  
    long    lDestZ;
    char    cDir[1];        //當前方向
	UHINT	LocalProcessID;			//本地的事件區 ID
	UHINT	RemoteProcessID;		//目的地事件區 ID
	SLONG	RemoteLineStartPointX;	//目的地線段起始點
	SLONG	RemoteLineStartPointY;	//目的地線段起始點
	SLONG	RemoteLineEndPointX;	//目的地線段終點
	SLONG	RemoteLineEndPointY;	//目的地線段終點
}TPOS_MAPLINK_POINT;
//-----------------------------------------------------------------------------------
// 每個城市連接點的資料陣列
//-----------------------------------------------------------------------------------
typedef struct
{
    DWORD              ZoneIndex;      // 城市編號
    TPOS_MAPLINK_POINT Point[MAX_MAPLINK_PER_ZONE];
}TPOS_MAPLINK;

extern  int     InitZoneServerData(void);
extern  void    FreeZoneServerData(void);
extern	void	InitZoneMapDefault();
extern	void	FreeZoneMapDefault();
extern	void	InitMapLinkData();
extern	void	FreeMapLinkData();
extern	void	LoadNPCDataFormMacro();
extern	void	LoadZoneWeather();
extern	SLONG   server_load_macro(char *filename);
extern	SLONG   server_load_npc_type(USTR *filename);
extern	SLONG   server_load_door_addr_port(void);

#endif