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

//extern TPOS_QQ_SERVER_INFO *GetQQServerInfoFromDoor;		// �q DoorServer ����
															// �ثe�Ҧ��� QQ Server Info

extern WORD                 WSA_EVENT;

extern DWORD				dwQQIDCounter;			   //�w�ϥΪ�QQID
extern DWORD				dwQQOnlineCounter;		//�w�s�u��QQ�Τ�
extern DWORD                dwConnectedCounter;	       //�w�s�u�`�H��
extern DWORD                dwOnlineCounter;	       //�ثe�u�W�H��
extern DWORD	            dwOnlineLoginer;           //�ثe�n�J�H��(Player)
extern DWORD		        dwOnlineMaxLoginer;		   //�̰��P�ɵn�J�H��
extern DWORD		        dwOnlineAllWorldPlayer;    //�@�ɥثe�u�W�`�H��
extern DWORD	            dwOnlineAllWorldMaxPlayer; //�@�ɳ̰��P�ɽu�W�`�H��
extern int			        iZoneCount;                //�s�u�ϰ���A���ƶq(Zone)

//extern FINAL_DATA	       *WorldWeather;              //�@�ɤѮ�
 
extern BOOL                 bWorldServerStart;		   //Server�O�_�Ұ�
extern TPOS_CHARACTER_DEFAULT CharacterDefault[MAX_CHARACTER_TYPE];
extern	TPOS_COUNTRYCITY	    CountryCity[MAX_COUNTRYSEL_PER_WORLD];
extern	TPOS_MACRO_WORLD    *Macro;	
extern	TPOS_MACRO_ZONE		*ZoneMacro;		
extern	int                 uncompresssize;
extern	int                 compresssize;
extern	char                *compressbuf;          // ���Y�Ȧs��	

extern	BOOL				HaveManagerFile;

//-------------------------------------------------------------------------------
#endif
