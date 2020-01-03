//-------------------------------------------------------------------------------
// Psalm of Sea Sync Position Heart Beat
// By Hawke Hsieh
// 2002-10-10
//-------------------------------------------------------------------------------
#include "ZoneServer_Def.h"
//-------------------------------------------------------------------------------
// GLOBALS 
//-------------------------------------------------------------------------------
SYNCPOSITIONHEARTBEAT_DATA  syncpositionheartbeat_data;
//
extern  void    ExecSyncPositionHeartBeat( void );
//-------------------------------------------------------------------------------
// STATICS 
//-------------------------------------------------------------------------------
static  DWORD   dwCurrentSyncPositionHeartBeatTimes = 0;
MMRESULT        idSyncPositionHeartBeat;
//
static  SLONG   InitializeSyncPositionHeartBeat( void );
static  void    DestroySyncPositionHeartBeat( void );
//-------------------------------------------------------------------------------
// Sync Position Heart Beat Thread Proc
//-------------------------------------------------------------------------------
void CALLBACK SyncPositionHeartBeatProc(UINT uID,UINT uMsg,DWORD dwUser,DWORD dw1,DWORD dw2 )
{
 ExecSyncPositionHeartBeat();   
}
//-------------------------------------------------------------------------------
// Init Sync Position Heart Beat Thread
//-------------------------------------------------------------------------------
static  SLONG   InitializeSyncPositionHeartBeat( void )
{
 idSyncPositionHeartBeat = timeSetEvent(syncpositionheartbeat_data.dwMsPerBeat,
	                            NULL,
								SyncPositionHeartBeatProc,
								NULL,
								TIME_PERIODIC);
 return TTN_OK;
}
//-------------------------------------------------------------------------------
// Destroy Sync Position Heart Beat Thread
//-------------------------------------------------------------------------------
static  void    DestroySyncPositionHeartBeat( void )
{
    timeKillEvent(idSyncPositionHeartBeat);
	SaveMsgToLog("SYSTEM","DESTROY_SYNCPOSITIONHEARTBEAT_OK");
}

int     init_syncpositionheartbeat(void)
{
    SLONG   ret;

    init_syncpositionheartbeat_data();

    ret = InitializeSyncPositionHeartBeat();
    if(ret != TTN_OK)
        return -1;
    return  0;
}

void    free_syncpositionheartbeat(void)
{
    DestroySyncPositionHeartBeat();
}

void    start_syncpositionheartbeat(void)
{

}

void    stop_syncpositionheartbeat(void)
{
 SaveMsgToLog("SYSTEM","SYNCPOSITIONHEARTBEAT_STOP"); 
}

void    init_syncpositionheartbeat_data(void)
{
    syncpositionheartbeat_data.flags = 0;
    syncpositionheartbeat_data.dwMsPerBeat = 4000;
    syncpositionheartbeat_data.dwBeatTimes = 0;
}

DWORD   get_syncpositionheartbeat_times(void)
{
    return  syncpositionheartbeat_data.dwBeatTimes;
}

void    ExecSyncPositionHeartBeat(void)
{ 
 SaveMsgToLog("SYSTEM","SYNCPOSITIONHEARTBEAT_BEAT");  
 SendPositionToAll();
 DoCloseBadConnectCount++;
 if(DoCloseBadConnectCount == 3)
 {
	 ServerDoClearBadConnect();
	 DoCloseBadConnectCount = 0;
 }
}