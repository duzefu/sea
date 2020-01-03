//-------------------------------------------------------------------------------
// Psalm of Sea Heart Beat
// By Hawke Hsieh
// 2002-10-10
//-------------------------------------------------------------------------------
#include "ZoneServer_Def.h"

//-------------------------------------------------------------------------------
// GLOBALS 
//-------------------------------------------------------------------------------
HEARTBEAT_DATA  heartbeat_data;
//-------------------------------------------------------------------------------
// STATICS 
//-------------------------------------------------------------------------------
static  DWORD   dwCurrentHeartBeatTimes = 0;
MMRESULT        idHeartBeat;
//-------------------------------------------------------------------------------
// Heart Beat Thread Proc
//-------------------------------------------------------------------------------
void CALLBACK HeartBeatProc(UINT uID,UINT uMsg,DWORD dwUser,DWORD dw1,DWORD dw2 )
{ 
    ExecHeartBeat();
}
//-------------------------------------------------------------------------------
// Init Heart Beat Thread
//-------------------------------------------------------------------------------
static SLONG InitializeHeartBeat( void )
{
    
    idHeartBeat = timeSetEvent(heartbeat_data.dwMsPerBeat,NULL,HeartBeatProc,NULL,TIME_PERIODIC);
    return TTN_OK;
}
//-------------------------------------------------------------------------------
// Destroy Heart Beat Thread
//-------------------------------------------------------------------------------
static  void    DestroyHeartBeat( void )
{
    timeKillEvent(idHeartBeat);		
    SaveMsgToLog("SYSTEM","DESTROY_HEARTBEAT_OK");
}

int     init_heartbeat(void)
{
    SLONG   ret;
    
    init_heartbeat_data();
    
    ret = InitializeHeartBeat();
    if(ret != TTN_OK)
        return -1;
    return  0;
}

void    free_heartbeat(void)
{
    DestroyHeartBeat();
}

void    start_heartbeat(void)
{
    
}

void    stop_heartbeat(void)
{    
    SaveMsgToLog("SYSTEM","HEARTBEAT_STOP");
}

void    init_heartbeat_data(void)
{
    heartbeat_data.flags = 0;
    heartbeat_data.dwMsPerBeat = 50;
    heartbeat_data.dwBeatTimes = 0;
}

DWORD   get_heartbeat_times(void)
{
    return  heartbeat_data.dwBeatTimes;
}

void    ExecHeartBeat(void)
{
	static	char	title[256];	

    heartbeat_data.dwBeatTimes++;
    //SaveMsgToLog("SYSTEM","TIME_BEAT");
    RefreshMainGame();	
	/* Remake For Do Not Display HeartBeat Count */
	/* By Hawke 2003-04-25 */
	//sprintf(title, "%s -- (%d)", WindowCaption, heartbeat_data.dwBeatTimes);
	//SetWindowText(MainhWnd,title);	
	SetWindowText(MainhWnd,WindowCaption);	
}
