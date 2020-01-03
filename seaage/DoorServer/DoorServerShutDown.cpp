//-------------------------------------------------------------------------------
// Psalm of Sea DoorServer ShutDown
// By Hawke Hsieh
// 2002-10-20
//-------------------------------------------------------------------------------
#include "DoorServer_Def.h"

//-------------------------------------------------------------------------------
// DoorServer ShutDown
//-------------------------------------------------------------------------------
int ShutDownServer()
{
 int        iRet;
 HMENU      TmpMnu; 
 
 iRet=ODBCDisConnect();

 iRet=CloseDoorServer();
 if(iRet==DLL_OK)
 {
  SaveMsgToLog("SYSTEM","LOGOUT_DOORSERVER_OK");
 }else
 {
  SaveMsgToLog("SYSTEM","LOGOUT_DOORSERVER_FAIL");
 }

 FreeVarMemory();
 TmpMnu=GetMenu(MainhWnd);
 EnableMenuItem(TmpMnu,ID_MENUITEM40001,MF_ENABLED);
 EnableMenuItem(TmpMnu,ID_MENUITEM40002,MF_GRAYED);
 EnableMenuItem(TmpMnu,ID_MENUITEM40003,MF_ENABLED);
 bDoorServerStart=FALSE;

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
// DoorServer Free Memory
//-------------------------------------------------------------------------------
void FreeVarMemory()
{
	int i;
	
	for(i = 0;i < MAX_WORLD_PER_DOOR;i++)
	{
		memset(&WorldInfo[i], 0x0, sizeof(TPOS_WORLDINFO));
	}
	free(Pos_Cn);	
	SaveMsgToLog("SYSTEM","FREEVARMEMORY_OK");
}
//-------------------------------------------------------------------------------