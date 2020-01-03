//-------------------------------------------------------------------------------
// Psalm of Sea DoorServer Create
// By Hawke Hsieh
// 2002-10-7
//-------------------------------------------------------------------------------
#include "DoorServer_Def.h"

//-------------------------------------------------------------------------------
// DoorServer Create Init
//-------------------------------------------------------------------------------
void CreateInit()
{
 char	    	str[25];
 FILE          *f;
 
 memset(str, 0x0, 25);
 f = fopen("door_ip.txt","rb");
 fgets(str, 25, f);
 fclose(f);
 sprintf(DoorServerAddr,"%s",str); 

}
//-------------------------------------------------------------------------------
// Active Dialog Server
//-------------------------------------------------------------------------------
int Active()
{ 
 return DLL_OK;
}
//-------------------------------------------------------------------------------
// Set Connect Door Server Info 
//-------------------------------------------------------------------------------
int SetConnectInfo()
{
	return DLL_OK;
}
//-------------------------------------------------------------------------------
// Active Door Server
//-------------------------------------------------------------------------------
int StartDoorServer()
{
	int        iRet;  
	HMENU      TmpMnu;
	char       str[256];	
	
	// 所有相關人數統計設定
	dwConnectedCounter = 0;	       //已連線總人數
	dwOnlineCounter = 0;
	dwOnlinePlayer = 0;
	iWorldCount = 0;

	LoadConnectedCounter();	

	sprintf(str,"Now Player : %d", dwOnlinePlayer);
    MsgOut(hStatusBarWnd,0,str);	
	sprintf(str,"Now World : %d",iWorldCount);
	MsgOut(hStatusBarWnd,1,str);
	sprintf(str,"Connected : %d",dwConnectedCounter);
	MsgOut(hStatusBarWnd,2,str);


	// 連接資料庫
	InitODBC();
	ConnectODBC("POS","posadmin","hawkesch");
	
	// 啟動 World Server
	iRet=DoorWinSockInit(MainhWnd,DoorServerPort);
	if(iRet!=DLL_OK)
	{
		switch(iRet)
		{
		case WINSOCK_VER_ERROR:
			if(MessageBox(MainhWnd,"WINSOCK_VER_ERROR","Error",MB_OK|MB_ICONERROR)==IDOK)        
				break;
		case INIT_SOCKET_ERROR:
			if(MessageBox(MainhWnd,"INIT_SOCKET_ERROR","Error",MB_OK|MB_ICONERROR)==IDOK)                
				break;
		case CANT_CONNECTED:        
			if(MessageBox(MainhWnd,"CANT_CONNECTED","Error",MB_OK|MB_ICONERROR)==IDOK)        
				break; 
		case CANT_ASYNC:        
			if(MessageBox(MainhWnd,"CANT_ASYNC","Error",MB_OK|MB_ICONERROR)==IDOK)        
				break;
		} 
		
		return FALSE;
	} 
	SaveMsgToLog("SYSTEM","INIT_DOORSERVER_OK");

	TmpMnu=GetMenu(MainhWnd);
	EnableMenuItem(TmpMnu,ID_MENUITEM40001,MF_GRAYED);
	EnableMenuItem(TmpMnu,ID_MENUITEM40002,MF_ENABLED);
	EnableMenuItem(TmpMnu,ID_MENUITEM40003,MF_GRAYED);	
	return DLL_OK;
}

//-------------------------------------------------------------------------------