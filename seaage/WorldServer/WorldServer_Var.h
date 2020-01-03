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

//TPOS_QQ_SERVER_INFO *GetQQServerInfoFromDoor;		// �q DoorServer ����
													// �ثe�Ҧ��� QQ Server Info
WORD                WSA_EVENT;

DWORD				dwQQIDCounter=0;			//�w�ϥΪ�QQID
DWORD				dwQQOnlineCounter=0;		//�w�s�u��QQ�Τ�
DWORD               dwConnectedCounter=0;	    //�w�s�u�`�H��
DWORD               dwOnlineCounter=0;			//�ثe�u�W�H��
DWORD	            dwOnlineLoginer=0;          //�ثe�n�J�H��(Player)
DWORD		        dwOnlineMaxLoginer=0;		//�̰��P�ɵn�J�H��
DWORD		        dwOnlineAllWorldPlayer=0;   //�@�ɥثe�u�W�`�H��
DWORD	            dwOnlineAllWorldMaxPlayer=0;//�@�ɳ̰��P�ɽu�W�`�H��
int			        iZoneCount=0;              //�s�u�ϰ���A���ƶq(Zone)

//FINAL_DATA          *WorldWeather=NULL;              //�@�ɤѮ�

BOOL                bWorldServerStart=false;    //Server�O�_�Ұ�
TPOS_CHARACTER_DEFAULT CharacterDefault[MAX_CHARACTER_TYPE];
TPOS_COUNTRYCITY      CountryCity[MAX_COUNTRYSEL_PER_WORLD];
TPOS_MACRO_WORLD    *Macro = NULL;
TPOS_MACRO_ZONE		*ZoneMacro=NULL;		
int                 uncompresssize=0;
int                 compresssize=0;
char                *compressbuf=NULL;          // ���Y�Ȧs��

BOOL				HaveManagerFile=FALSE;

#endif