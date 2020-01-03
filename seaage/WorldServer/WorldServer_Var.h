#ifndef WORLDSERVER_VAR_H
#define WORLDSERVER_VAR_H
//-------------------------------------------------------------------------------
//#include "ZoneServer_Def.h"

HINSTANCE           MainInst;
HINSTANCE        	dInstance;
HINSTANCE	        wInstance;
HINSTANCE	        zInstance;
HINSTANCE	        zsInstance;
HINSTANCE	        qInstance;
HWND                ParenthWnd;
HWND                dParenthWnd;
HWND                wParenthWnd;
HWND                zParenthWnd;
HWND                qParenthWnd;
char	            szClassName[] = "WorldServer_VC";
char             	DoorClassName[] = "DOORSOCKET";
char             	WorldClassName[] = "WORLDSOCKET";
char             	QQClassName[] = "QQSOCKET";
HWND		    	DoorSockethWnd;
HWND		    	WorldSockethWnd;
HWND		    	QQSockethWnd;
HWND                MainhWnd;
HWND                SetuphWnd; 
HWND			    hStatusBarWnd;
HWND		        hListViewWnd; 
struct _timeb       timebuffer;

TPOS_CN	           *Pos_Cn=NULL;
TPOS_CN	           *World=NULL;
TPOS_CN	           *Door=NULL;
TPOS_CN	           *QQ=NULL;
char                WorldServerName[32];
int                 WorldServerPort;
char   	            WorldServerAddr[16];
char   	            DoorServerAddr[16];
DWORD               DoorServerPort;
char                QQServerName[32];
char   	            QQServerAddr[16];
DWORD               QQServerPort;

TPOS_ZONEINFO		ZoneInfo[MAX_ZONE_PER_WORLD];

//TPOS_QQ_SERVER_INFO *GetQQServerInfoFromDoor;		// 眖 DoorServer Μ
													// ヘ玡┮Τ QQ Server Info
WORD                WSA_EVENT;

DWORD				dwQQIDCounter=0;			//ㄏノQQID
DWORD				dwQQOnlineCounter=0;		//硈絬QQノめ
DWORD               dwConnectedCounter=0;	    //硈絬羆计
DWORD               dwOnlineCounter=0;			//ヘ玡絬计
DWORD	            dwOnlineLoginer=0;          //ヘ玡祅计(Player)
DWORD		        dwOnlineMaxLoginer=0;		//程蔼祅计
DWORD		        dwOnlineAllWorldPlayer=0;   //ヘ玡絬羆计
DWORD	            dwOnlineAllWorldMaxPlayer=0;//程蔼絬羆计
int			        iZoneCount=0;              //硈絬跋办狝竟计秖(Zone)

//FINAL_DATA          *WorldWeather=NULL;              //ぱ

BOOL                bWorldServerStart=false;    //Server琌币笆
TPOS_CHARACTER_DEFAULT CharacterDefault[MAX_CHARACTER_TYPE];
TPOS_COUNTRYCITY      CountryCity[MAX_COUNTRYSEL_PER_WORLD];
TPOS_MACRO_WORLD    *Macro = NULL;
TPOS_MACRO_ZONE		*ZoneMacro=NULL;		
int                 uncompresssize=0;
int                 compresssize=0;
char                *compressbuf=NULL;          // 溃罽既跋

BOOL				HaveManagerFile=FALSE;

#endif