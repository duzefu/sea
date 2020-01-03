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
DWORD				dwConnectedCounter=0;	            //�w�s�u�`�H��
DWORD				dwOnlineCounter=0;					//�ثe�s�u�`��
DWORD				dwOnlinePlayer=0;					//�ثe�u�W�H��
int					iWorldCount=0;						//�@�ɦ��A�����s�u�ƥ�

BOOL				bDoorServerStart=false;				//Server�O�_�Ұ�

BOOL				bDSReadingNow = false;				//�O�_Ū�����
//-------------------------------------------------------------------------------
#endif //DOORSERVER_VAR_H