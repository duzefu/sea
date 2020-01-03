//-------------------------------------------------------------------------------
// Psalm of Sea WorldServer ShutDown
// By Hawke Hsieh
// 2002-10-20
//-------------------------------------------------------------------------------
#include "WorldServer_Def.h"

//-------------------------------------------------------------------------------
// WorldServer ShutDown
//-------------------------------------------------------------------------------
int ShutDownServer()
{
	int        iRet;
	HMENU      TmpMnu; 

//Temp remarked, 2002.12.10.	
	//stop_qqqueryheartbeat();
	//free_qqqueryheartbeat();
	
	iRet=CloseDoorServer();
	if(iRet==DLL_OK)
	{
		SaveMsgToLog("SYSTEM","LOGOUT_DOORSERVER_OK");
	}else
	{
		SaveMsgToLog("SYSTEM","LOGOUT_DOORSERVER_FAIL");
	}
	
	iRet=ODBCDisConnect();
	
	iRet=CloseWorldServer();
	if(iRet==DLL_OK)
	{
		SaveMsgToLog("SYSTEM","CLOSE_WORLDSERVER_OK");
	}else
	{
		SaveMsgToLog("SYSTEM","WORLD_CLOSESERVER_FAIL");
	}             
	
	FreeVarMemory();
	TmpMnu=GetMenu(MainhWnd);
	EnableMenuItem(TmpMnu,ID_MENUITEM40001,MF_ENABLED);
	EnableMenuItem(TmpMnu,ID_MENUITEM40002,MF_GRAYED);
	EnableMenuItem(TmpMnu,ID_MENUITEM40003,MF_ENABLED);
	bWorldServerStart=FALSE;
	
	return DLL_OK;
}
//-------------------------------------------------------------------------------
// ODBC Disconnect
//-------------------------------------------------------------------------------
int ODBCDisConnect()
{
	DisconnectODBC();
	return DLL_OK; 
}
//-------------------------------------------------------------------------------
// ZoneServer Free Memory
//-------------------------------------------------------------------------------
void FreeVarMemory()
{
  WSACleanup();
  free(compressbuf);
  free(Macro);
  free(ZoneMacro);
 // FreeQQData();	    
  SaveMsgToLog("SYSTEM","FREEVARMEMORY_OK");
}
//-------------------------------------------------------------------------------

       
