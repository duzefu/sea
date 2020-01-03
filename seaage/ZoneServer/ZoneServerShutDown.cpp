//-------------------------------------------------------------------------------
// Psalm of Sea ZoneServer ShutDown
// By Hawke Hsieh
// 2002-10-11
//-------------------------------------------------------------------------------
#include "ZoneServer_Def.h"

//-------------------------------------------------------------------------------
// ZoneServer ShutDown
//-------------------------------------------------------------------------------
int ShutDownServer()
{
    int        iRet;
    HMENU      TmpMnu;

	switch(ZoneType)
	{
	case CITY_NORMAL:
	case CITY_NEWBIE:
	case CITY_PK:
	case CITY_FINDGOLD:
	case CITY_BIRTH:
	case FIELD_NORMAL:
	case FIELD_NEWBIE:
	case FIELD_PK:
	case FIELD_FINDGOLD:
	case FIELD_BIRTH:
		stop_syncpositionheartbeat();
		free_syncpositionheartbeat();  		
		break;
	case SAIL_NORMAL:
	case SAIL_NEWBIE:
	case SAIL_PK:
	case SAIL_FINDGOLD:
	case SAIL_BIRTH:
		stop_syncseapositionheartbeat();
		free_syncseapositionheartbeat();
		break;
	}    	
	stop_savedataheartbeat();
log_error(1, "ShutDownServer stop savedataheartbeat ok...");

	free_savedataheartbeat();
log_error(1, "ShutDownServer free savedataheartbeat ok...");

    stop_syncheartbeat();
log_error(1, "ShutDownServer stop syncheartbeat ok...");

	free_syncheartbeat();
log_error(1, "ShutDownServer free syncheartbeat ok...");

    stop_heartbeat();	
log_error(1, "ShutDownServer stop heartbeat ok...");

    free_heartbeat();
log_error(1, "ShutDownServer free heartbeat ok...");
  
    iRet = CloseWorldServer();
log_error(1, "ShutDownServer close world server ret : %d", iRet);

    if(iRet == DLL_OK)
    {
        SaveMsgToLog("SYSTEM","LOGOUT_WORLDSERVER_OK");
    }else
    {
        SaveMsgToLog("SYSTEM","LOGOUT_WORLDSERVER_FAIL");
    }
       
    
    iRet = CloseZoneServer();
log_error(1, "ShutDownServer close zone server ret : %d", iRet);

    if(iRet==DLL_OK)
    {
        SaveMsgToLog("SYSTEM","CLOSE_ZONESERVER_OK");
    }
    else
    {
        SaveMsgToLog("SYSTEM","ZONE_CLOSESERVER_FAIL");
    }             
    
    FreeVarMemory();
log_error(1, "ShutDownServer FreeVarMemory ok");

    TmpMnu = GetMenu(MainhWnd);
log_error(1, "ShutDownServer GetMenu ok");

    EnableMenuItem(TmpMnu, IDM_SYSTEM_ACTIVE, MF_ENABLED);
    EnableMenuItem(TmpMnu, IDM_SYSTEM_SHUTDOWN, MF_GRAYED);
    EnableMenuItem(TmpMnu, IDM_SYSTEM_EXIT, MF_ENABLED);
    EnableMenuItem(TmpMnu, IDM_SYSTEM_RELOGIN_WORLDSERVER,MF_GRAYED);

log_error(1, "ShutDownServer end");
    
    return DLL_OK;
}

//-------------------------------------------------------------------------------
// ZoneServer Free Memory
//-------------------------------------------------------------------------------
void FreeVarMemory()
{
    FreeZoneServerData();

    WSACleanup();
    
    SaveMsgToLog("SYSTEM","FREEVARMEMORY_OK");  
}
//-------------------------------------------------------------------------------


