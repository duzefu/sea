//-------------------------------------------------------------------------------
// Psalm of Sea Sync Sea Position Heart Beat
// By Hawke Hsieh
// 2002-12-17
//-------------------------------------------------------------------------------
#include "ZoneServer_Def.h"
//-------------------------------------------------------------------------------
// GLOBALS 
//-------------------------------------------------------------------------------
SYNCSEAPOSITIONHEARTBEAT_DATA  syncseapositionheartbeat_data;
//
extern  void    ExecSyncSeaPositionHeartBeat( void );
//-------------------------------------------------------------------------------
// STATICS 
//-------------------------------------------------------------------------------
static  DWORD   dwCurrentSyncSeaPositionHeartBeatTimes = 0;
MMRESULT        idSyncSeaPositionHeartBeat;
//
static  SLONG   InitializeSyncSeaPositionHeartBeat( void );
static  void    DestroySyncSeaPositionHeartBeat( void );
//-------------------------------------------------------------------------------
// Sync Sea Position Heart Beat Thread Proc
//-------------------------------------------------------------------------------
void CALLBACK SyncSeaPositionHeartBeatProc(UINT uID,UINT uMsg,DWORD dwUser,DWORD dw1,DWORD dw2 )
{
 ExecSyncSeaPositionHeartBeat();   
}
//-------------------------------------------------------------------------------
// Init Sync Sea Position Heart Beat Thread
//-------------------------------------------------------------------------------
static  SLONG   InitializeSyncSeaPositionHeartBeat( void )
{
 idSyncSeaPositionHeartBeat = timeSetEvent(syncseapositionheartbeat_data.dwMsPerBeat,
	                            NULL,
								SyncSeaPositionHeartBeatProc,
								NULL,
								TIME_PERIODIC);
 return TTN_OK;
}
//-------------------------------------------------------------------------------
// Destroy Sync Sea Position Heart Beat Thread
//-------------------------------------------------------------------------------
static  void    DestroySyncSeaPositionHeartBeat( void )
{
    timeKillEvent(idSyncSeaPositionHeartBeat);
	SaveMsgToLog("SYSTEM","DESTROY_SYNCSEAPOSITIONHEARTBEAT_OK");
}

int     init_syncseapositionheartbeat(void)
{
    SLONG   ret;

    init_syncseapositionheartbeat_data();

    ret = InitializeSyncSeaPositionHeartBeat();
    if(ret != TTN_OK)
        return -1;
    return  0;
}

void    free_syncseapositionheartbeat(void)
{
    DestroySyncSeaPositionHeartBeat();
}

void    start_syncseapositionheartbeat(void)
{

}

void    stop_syncseapositionheartbeat(void)
{
 SaveMsgToLog("SYSTEM","SYNCSEAPOSITIONHEARTBEAT_STOP"); 
}

void    init_syncseapositionheartbeat_data(void)
{
    syncseapositionheartbeat_data.flags = 0;
    syncseapositionheartbeat_data.dwMsPerBeat = 4000;
    syncseapositionheartbeat_data.dwBeatTimes = 0;
}

DWORD   get_syncseapositionheartbeat_times(void)
{
    return  syncseapositionheartbeat_data.dwBeatTimes;
}

void    ExecSyncSeaPositionHeartBeat(void)
{ 
 SaveMsgToLog("SYSTEM","SYNCSEAPOSITIONHEARTBEAT_BEAT");  
 SendSeaPositionToAll();
 DoCloseBadConnectCount++;
 if(DoCloseBadConnectCount == 3)
 {
	 ServerDoClearBadConnect();
	 DoCloseBadConnectCount = 0;
 }
}