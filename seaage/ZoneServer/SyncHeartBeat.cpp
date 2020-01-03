//-------------------------------------------------------------------------------
// Psalm of Sea Sync Heart Beat
// By Hawke Hsieh
// 2002-10-10
//-------------------------------------------------------------------------------
#include "ZoneServer_Def.h"
//-------------------------------------------------------------------------------
// GLOBALS 
//-------------------------------------------------------------------------------
SYNCHEARTBEAT_DATA  syncheartbeat_data;
//
extern  void    ExecHeartBeat( void );
//-------------------------------------------------------------------------------
// STATICS 
//-------------------------------------------------------------------------------
static  DWORD   dwCurrentSyncHeartBeatTimes = 0;
MMRESULT        idSyncHeartBeat;
//
static  SLONG   InitializeSyncHeartBeat( void );
static  void    DestroySyncHeartBeat( void );
//-------------------------------------------------------------------------------
// Sync Heart Beat Thread Proc
//-------------------------------------------------------------------------------
void CALLBACK SyncHeartBeatProc(UINT uID,UINT uMsg,DWORD dwUser,DWORD dw1,DWORD dw2 )
{
 ExecSyncHeartBeat();   
}
//-------------------------------------------------------------------------------
// Init Sync Heart Beat Thread
//-------------------------------------------------------------------------------
static  SLONG   InitializeSyncHeartBeat( void )
{
 idSyncHeartBeat = timeSetEvent(syncheartbeat_data.dwMsPerBeat,
	                            NULL,
								SyncHeartBeatProc,
								NULL,
								TIME_PERIODIC);
 return TTN_OK;
}
//-------------------------------------------------------------------------------
// Destroy Sync Heart Beat Thread
//-------------------------------------------------------------------------------
static  void    DestroySyncHeartBeat( void )
{
    timeKillEvent(idSyncHeartBeat);
	SaveMsgToLog("SYSTEM","DESTROY_SYNCHEARTBEAT_OK");
}

int     init_syncheartbeat(void)
{
    SLONG   ret;

    init_syncheartbeat_data();

    ret = InitializeSyncHeartBeat();
    if(ret != TTN_OK)
        return -1;
    return  0;
}

void    free_syncheartbeat(void)
{
    DestroySyncHeartBeat();
}

void    start_syncheartbeat(void)
{

}

void    stop_syncheartbeat(void)
{
 
 SaveMsgToLog("SYSTEM","SYNVHEARTBEAT_STOP"); 
}

void    init_syncheartbeat_data(void)
{
    syncheartbeat_data.flags = 0;
    syncheartbeat_data.dwMsPerBeat = 1000;
    syncheartbeat_data.dwBeatTimes = 0;
}

DWORD   get_syncheartbeat_times(void)
{
    return  syncheartbeat_data.dwBeatTimes;
}

void    ExecSyncHeartBeat(void)
{
 DWORD s;
 char  TmpBuf[20];
 s=get_heartbeat_times(); 
 SendRefreshToAll(s); 
 sprintf(TmpBuf,"%d",s);
 SaveMsgToLog("SYSTEM","SYNCHEARTBEAT_BEAT"); 
 SaveMsgToLog("SYSTEM",TmpBuf);
}