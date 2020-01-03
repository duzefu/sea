#ifndef	_INITZONEDATA_H_
#define	_INITZONEDATA_H_

#define SYNC_COMPRESS_BUF_SIZE      16384
#define COMPRESS_BUF_SIZE           16777216
#define MAX_WORLD_INFO              500

// ---------------------------------------------------------------------------
// ZoneServer Information Struct Define
// �ϰ���A����T 
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
	DWORD			dwType;		// 0 - ���a , 1 -���W 
}TPOS_ZONEINFO;
// ---------------------------------------------------------------------------
// WorldServer Information Struct Define
// �@�ɦ��A����T
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
// �ϰ�W�٩M�a�ϦW�٬۹��������c
//----------------------------------------------------------------------------------
typedef struct
{
    char   cZoneName[32];
    char   cMapName[32];
	DWORD  dType;	 	
}TPOS_ZONEMAPDEFAULT;
//-----------------------------------------------------------------------------------
// ��@�s���I�����
//-----------------------------------------------------------------------------------
typedef struct
{ 
    DWORD   ZoneData;       // �s�����ϰ�s��  ����  ZoneMapDefault �����
    // �����ϰ�W�٩M�a�ϦW�� 
    long    lDestX;         // �ؼЫ����y��
    long    lDestY;                  
    long    lDestZ;
    char    cDir[1];        //��e��V
	UHINT	LocalProcessID;			//���a���ƥ�� ID
	UHINT	RemoteProcessID;		//�ت��a�ƥ�� ID
	SLONG	RemoteLineStartPointX;	//�ت��a�u�q�_�l�I
	SLONG	RemoteLineStartPointY;	//�ت��a�u�q�_�l�I
	SLONG	RemoteLineEndPointX;	//�ت��a�u�q���I
	SLONG	RemoteLineEndPointY;	//�ت��a�u�q���I
}TPOS_MAPLINK_POINT;
//-----------------------------------------------------------------------------------
// �C�ӫ����s���I����ư}�C
//-----------------------------------------------------------------------------------
typedef struct
{
    DWORD              ZoneIndex;      // �����s��
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