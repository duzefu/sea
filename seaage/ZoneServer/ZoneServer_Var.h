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

DWORD               dwConnectedCounter;	       //�w�s�u�`�H��
DWORD               dwOnlineCounter;	       //�ثe�u�W�H��

BOOL                bZoneServerStart=false;    //Server�O�_�Ұ�

BOOL                bDSReadingNow = false;     //�O�_Ū�����

DWORD               dwRequestForWorldInfoIndex;

//LPTCPOS_WORLDINFO   lpWorldInfo=NULL;
TPOS_WORLDINFO      *GetWorldInfoFromDoor;      // �q DoorServer ����
                                                // �ثe�Ҧ��� World Server Info
TPOS_ZONEINFO       *GetZoneInfoFromMarco;		// �q Marco �Ѷ}
//                                              // �ثe�Ҧ��� Zone Server Info

bool                bCheckCharacterState=false; // �O�_�ˬd���⪬�A
bool                bCheckSYNC=false;           // �O�_�ˬd�P�B

bool                UDP_Connected=false;
bool                UDP_Group_Connected=false;

DATA_FILE          *sea_data_file;              // �a�Ϫ��ץ��]

DWORD               refresh=0;                  // �B���s�p��
DWORD				savecount=0;				// �x�s���������

TPOS_ZONEWEATHER    *ZoneWeather;               // �ϰ�Ѯ𵲺c  
TPOS_MACRO_WORLD    *Macro=NULL;                // �@�����c
TPOS_MACRO_ZONE		*ZoneMacro=NULL;
TPOS_NPC            *NPCType;                   // NPC ������
//TPOS_MAGIC          *MagicType;                 // �ۦ�������
//TPOS_ITEM           *ItemType;                  // ���~������
int                 uncompresssize=0;
int                 compresssize=0;
char                *compressbuf=NULL;          // ���Y�Ȧs��
char                *SyncCompressBuf=NULL;      // �P�B���Y�Ȧs  
char                mapname[32];
int                 ZoneActive=0;

char                cWorldServerName[32];       // �t�Τ��i �@�ɦ��A���W��     
char                cSystemMessage[256];		// �t�Τ��i ���i���e

DWORD               ServerType=0x00000000;      // �ʥ]�e�X���ؼЦ��A������ 
bool                ServerStart = FALSE; 
TPOS_ZONEMAPDEFAULT ZoneMapDefault[MAX_ZONE_PER_MACRO];         // �w�]�ϰ�a�ϦW�� 
DWORD				ZoneType=0;					 // �a�Ϫ����� 

TPOS_MAPLINK        MapLink[1];	                 // �s���f����� 
DWORD               MapIndex;                    // ��e�a�Ϫ��s�� (�����w�]�ϰ���)    
BOOL				BadConnect[MAX_PLAYER_PER_ZONE];// �����`�_�u���s���C��
DWORD				DoCloseBadConnectCount = 0;  // �B�z�����`�_�u��Counter;

BOOL				HaveManagerFile=FALSE;		 // ���޲z�t�Ϊ��Ұ���	
char				WindowCaption[256];

//TPOS_QQ_ONLINE_PLAYER_LIST *QQOnlinePlayerList;

//-------------------------------------------------------------------------------
#endif