//-------------------------------------------------------------------------------
// Psalm of Sea Save Data Heart Beat
// By Hawke Hsieh
// 2003-02-21
//-------------------------------------------------------------------------------
#include "ZoneServer_Def.h"

//-------------------------------------------------------------------------------
// GLOBALS 
//-------------------------------------------------------------------------------
SAVEDATAHEARTBEAT_DATA  savedataheartbeat_data;
//-------------------------------------------------------------------------------
// STATICS 
//-------------------------------------------------------------------------------
static  DWORD   dwCurrentSaveDataHeartBeatTimes = 0;
MMRESULT        idSaveDataHeartBeat;
//-------------------------------------------------------------------------------
// Save Data Heart Beat Thread Proc
//-------------------------------------------------------------------------------
void CALLBACK SaveDataHeartBeatProc(UINT uID,UINT uMsg,DWORD dwUser,DWORD dw1,DWORD dw2 )
{ 
    ExecSaveDataHeartBeat();
}
//-------------------------------------------------------------------------------
// Init Save Data Heart Beat Thread
//-------------------------------------------------------------------------------
static SLONG InitializeSaveDataHeartBeat( void )
{
    
    idSaveDataHeartBeat = timeSetEvent(savedataheartbeat_data.dwMsPerBeat,NULL,SaveDataHeartBeatProc,NULL,TIME_PERIODIC);
    return TTN_OK;
}
//-------------------------------------------------------------------------------
// Destroy Save Data Heart Beat Thread
//-------------------------------------------------------------------------------
static  void    DestroySaveDataHeartBeat( void )
{
    timeKillEvent(idSaveDataHeartBeat);		
    SaveMsgToLog("SYSTEM","DESTROY_SAVEDATAHEARTBEAT_OK");
}

int     init_savedataheartbeat(void)
{
    SLONG   ret;
    
    init_savedataheartbeat_data();
    
    ret = InitializeSaveDataHeartBeat();
    if(ret != TTN_OK)
        return -1;
    return  0;
}

void    free_savedataheartbeat(void)
{
    DestroySaveDataHeartBeat();
}

void    start_savedataheartbeat(void)
{
    
}

void    stop_savedataheartbeat(void)
{    
    SaveMsgToLog("SYSTEM","SAVEDATAHEARTBEAT_STOP");
}

void    init_savedataheartbeat_data(void)
{
    savedataheartbeat_data.flags = 0;
    savedataheartbeat_data.dwMsPerBeat = 2000;
    savedataheartbeat_data.dwBeatTimes = 0;
}

DWORD   get_savedataheartbeat_times(void)
{
    return  savedataheartbeat_data.dwBeatTimes;
}

void    ExecSaveDataHeartBeat(void)
{
    savedataheartbeat_data.dwBeatTimes++;    
	server_save_character_data();
}
