#ifndef DOORSERVER_VAR_H
#define DOORSERVER_VAR_H
//-------------------------------------------------------------------------------

HINSTANCE			MainInst;
HINSTANCE        	dInstance;

HWND		    	DoorSockethWnd;
HWND                MainhWnd;

char	            szClassName[] = "DoorServer_VC";
char             	DoorClassName[] = "DOORSOCKET";

HWND			    hStatusBarWnd;
HWND		        hListViewWnd; 

POS_PACKET			Pos_Packet;

TPOS_CN	           *Door;
TPOS_CN	           *Pos_Cn;

TPOS_WORLDINFO		WorldInfo[MAX_WORLD_PER_DOOR];
//LPTCPOS_EVENT_WORLDINFO	lpWorldInfo;

TPOS_PACKET		    CurrentPacket;

WORD				WSA_EVENT;

struct _timeb		timebuffer;

char				DoorServerAddr[16];
DWORD				DoorServerPort=8699; 
DWORD				dwConnectedCounter=0;	            //已連線總人數
DWORD				dwOnlineCounter=0;					//目前連線總數
DWORD				dwOnlinePlayer=0;					//目前線上人數
int					iWorldCount=0;						//世界伺服器的連線數目

BOOL				bDoorServerStart=false;				//Server是否啟動

BOOL				bDSReadingNow = false;				//是否讀取資料
//-------------------------------------------------------------------------------
#endif //DOORSERVER_VAR_H