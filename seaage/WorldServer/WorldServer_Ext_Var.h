#ifndef WORLDSERVER_EXTVAR_H
#define WORLDSERVER_EXTVAR_H
//-------------------------------------------------------------------------------
//#include "ZoneServer_Def.h"

extern HINSTANCE			MainInst;
extern HINSTANCE		    dInstance;
extern HINSTANCE			wInstance;
extern HINSTANCE			zInstance;
extern HINSTANCE	        zsInstance;
extern HINSTANCE	        qInstance;
extern HWND                 ParenthWnd;
extern HWND                 dParenthWnd;
extern HWND                 wParenthWnd;
extern HWND                 zParenthWnd;
extern HWND                 qParenthWnd;
extern char					szClassName[];
extern char             	DoorClassName[];
extern char             	WorldClassName[];
extern char             	QQClassName[];
extern HWND		    		DoorSockethWnd;
extern HWND		    		WorldSockethWnd;
extern HWND			    	QQSockethWnd;
extern HWND                 MainhWnd;
extern HWND                 SetuphWnd; 
extern HWND					hStatusBarWnd;
extern HWND					hListViewWnd; 
extern struct _timeb        timebuffer;

extern TPOS_CN	           *Pos_Cn;
extern TPOS_CN	           *World;
extern TPOS_CN	           *Door;
extern TPOS_CN	           *QQ;
extern char                 WorldServerName[32];
extern int					WorldServerPort;
extern char   	            WorldServerAddr[16];
extern char   	            DoorServerAddr[16];
extern DWORD	            DoorServerPort;
extern char                 QQServerName[32];
extern char   	            QQServerAddr[16];
extern DWORD                QQServerPort;

extern TPOS_ZONEINFO		ZoneInfo[MAX_ZONE_PER_WORLD];

//extern TPOS_QQ_SERVER_INFO *GetQQServerInfoFromDoor;		// 眖 DoorServer Μ
															// ヘ玡┮Τ QQ Server Info

extern WORD                 WSA_EVENT;

extern DWORD				dwQQIDCounter;			   //ㄏノQQID
extern DWORD				dwQQOnlineCounter;		//硈絬QQノめ
extern DWORD                dwConnectedCounter;	       //硈絬羆计
extern DWORD                dwOnlineCounter;	       //ヘ玡絬计
extern DWORD	            dwOnlineLoginer;           //ヘ玡祅计(Player)
extern DWORD		        dwOnlineMaxLoginer;		   //程蔼祅计
extern DWORD		        dwOnlineAllWorldPlayer;    //ヘ玡絬羆计
extern DWORD	            dwOnlineAllWorldMaxPlayer; //程蔼絬羆计
extern int			        iZoneCount;                //硈絬跋办狝竟计秖(Zone)

//extern FINAL_DATA	       *WorldWeather;              //ぱ
 
extern BOOL                 bWorldServerStart;		   //Server琌币笆
extern TPOS_CHARACTER_DEFAULT CharacterDefault[MAX_CHARACTER_TYPE];
extern	TPOS_COUNTRYCITY	    CountryCity[MAX_COUNTRYSEL_PER_WORLD];
extern	TPOS_MACRO_WORLD    *Macro;	
extern	TPOS_MACRO_ZONE		*ZoneMacro;		
extern	int                 uncompresssize;
extern	int                 compresssize;
extern	char                *compressbuf;          // 溃罽既跋	

extern	BOOL				HaveManagerFile;

//-------------------------------------------------------------------------------
#endif
