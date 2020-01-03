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
extern DWORD              dwConnectedCounter;		//�w�s�u�`�H��
extern DWORD              dwOnlineCounter;			//�ثe�s�u�`��
extern DWORD              dwOnlinePlayer;			//�ثe�u�W�H��
extern int                iWorldCount;				//�@�ɦ��A�����s�u�ƥ�

extern BOOL               bDoorServerStart;			//Server�O�_�Ұ�

extern BOOL               bDSReadingNow;			//�O�_Ū�����

//-------------------------------------------------------------------------------
#endif //DOORSERVER_EXTVAR_H

