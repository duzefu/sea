#ifndef DOORSERVER_EXTVAR_H
#define DOORSERVER_EXTVAR_H
//-------------------------------------------------------------------------------

extern HINSTANCE          MainInst;
extern HINSTANCE          dInstance;

extern HWND		    	  DoorSockethWnd;
extern HWND               MainhWnd;

extern char	              szClassName[];
extern char               DoorClassName[];

extern HWND			      hStatusBarWnd;
extern HWND		          hListViewWnd; 

extern POS_PACKET         Pos_Packet;

extern TPOS_CN	         *Door;
extern TPOS_CN	         *Pos_Cn;

extern TPOS_WORLDINFO	  WorldInfo[MAX_WORLD_PER_DOOR];
//extern LPTCPOS_WORLDINFO  lpWorldInfo;

extern TPOS_PACKET        CurrentPacket;

extern WORD               WSA_EVENT;

extern struct _timeb      timebuffer;

extern char               DoorServerAddr[16];
extern DWORD              DoorServerPort; 
extern DWORD              dwConnectedCounter;		//已連線總人數
extern DWORD              dwOnlineCounter;			//目前連線總數
extern DWORD              dwOnlinePlayer;			//目前線上人數
extern int                iWorldCount;				//世界伺服器的連線數目

extern BOOL               bDoorServerStart;			//Server是否啟動

extern BOOL               bDSReadingNow;			//是否讀取資料

//-------------------------------------------------------------------------------
#endif //DOORSERVER_EXTVAR_H

