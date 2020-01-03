/*
**  HrtBeat.cpp
**  game heart-beat functions.
**
**  geaan, 2001.8.1.
*/
#include "mainfun.h"
#include "hrtbeat.h"


// D E F I N E S ///////////////////////////////////////////////////////////////////////////////////////////////////
#define USE_C_RUNTIME_LIBRARY       1
//
#define HEARTBEAT_INITIALIZED       0x00000001  //心跳模組已經初始化
#define HEARTBEAT_CS_INITIALIZED    0x00000002  //心跳的臨界區已經初始化
//
#define HBF_INIT_HEARTBEAT          0x01
//
#define LOCK_HEARTBEAT()            EnterCriticalSection(&csHeartBeat)
#define UNLOCK_HEARTBEAT()          LeaveCriticalSection(&csHeartBeat)
//
// S T R U C T U R E S /////////////////////////////////////////////////////////////////////////////////////////////
typedef struct tagHEARTBEAT_DATA
{
    SLONG   flags;          //標誌

    DWORD   dwLastTimes;    //上次接收到同步的時候, 本機自己心跳的次數.
    DWORD   dwBeatTimes;    //本機當前的心跳次數
    DWORD   dwMsPerBeat;    //每次心跳的間隔時間(毫秒)
    //
    DWORD   dwSyncTimes;    //上次接收到的同步心跳次數
    //
    DWORD   dwRefreshTimes; //到這次需要刷新的次數
    //
} HEARTBEAT_DATA, *LPHEARTBEAT_DATA;


// GLOBALS /////////////////////////////////////////////////////////////////////////////////////////////////////////
HEARTBEAT_DATA  heartbeat_data;
//
// STATICS /////////////////////////////////////////////////////////////////////////////////////////////////////////
static  DWORD   dwHeartBeatFlags = 0;
static  HANDLE  hHeartBeatThread = NULL;
static  HANDLE  hHeartBeatExitEvent = NULL;
static  HANDLE  hHeartBeatEvent = NULL;
static  CRITICAL_SECTION    csHeartBeat;
//
static  SLONG   InitializeHeartBeat( void );
static  void    DestroyHeartBeat( void );
static  void    ExecHeartBeat(void);
//
/******************************************************************************************************************/
/* HEARTBEAT FUNCTIONS                                                                                            */
/******************************************************************************************************************/
int     init_heartbeat(void)
{
    SLONG   ret;

    dwHeartBeatFlags = 0;

    //初始化臨界區
    InitializeCriticalSection(&csHeartBeat);
    dwHeartBeatFlags |= HEARTBEAT_CS_INITIALIZED;

    //初始化心跳數據
    init_heartbeat_data();

    ret = InitializeHeartBeat();
    if(ret != TTN_OK)
        return -1;

    dwHeartBeatFlags |= HEARTBEAT_INITIALIZED;

    return  0;
}


void    active_heartbeat(int active)
{
    //if(dwHeartBeatFlags & HEARTBEAT_INITIALIZED);
}



void    free_heartbeat(void)
{
    DestroyHeartBeat();
    DeleteCriticalSection(&csHeartBeat);
    dwHeartBeatFlags = 0;
}


void    start_heartbeat(void)
{
    if(! (dwHeartBeatFlags & HEARTBEAT_INITIALIZED) )
        return;

    if( hHeartBeatThread )
    {
        ResumeThread( hHeartBeatThread );
    }
}


void    stop_heartbeat(void)
{
    if(! (dwHeartBeatFlags & HEARTBEAT_INITIALIZED) )
        return;

    if( hHeartBeatThread )
    {
        SuspendThread( hHeartBeatThread );
    }
}


void    set_heartbeat_timeout_milliseconds(DWORD ms)
{
    if(! (dwHeartBeatFlags & HEARTBEAT_INITIALIZED) )
        return;

    LOCK_HEARTBEAT();
    heartbeat_data.dwMsPerBeat = ms;
    UNLOCK_HEARTBEAT();
}


DWORD   get_heartbeat_timeout_milliseconds(void)
{
    DWORD   dwValue;

    if(! (dwHeartBeatFlags & HEARTBEAT_INITIALIZED) )
        return  1000;

    LOCK_HEARTBEAT();
    dwValue = heartbeat_data.dwMsPerBeat;
    UNLOCK_HEARTBEAT();

    return dwValue;
}


void    init_heartbeat_data(void)
{
    if(! (dwHeartBeatFlags & HEARTBEAT_CS_INITIALIZED) )
        return;

    LOCK_HEARTBEAT();
    heartbeat_data.flags = 0;
    heartbeat_data.dwMsPerBeat = 50;
    heartbeat_data.dwBeatTimes = 0;
    UNLOCK_HEARTBEAT();
}


void    sync_heartbeat_data(DWORD dwTimes)
{
    DWORD   dwNextSyncTimes;
    DWORD   dwBeats, dwPeriod, dwMsPerBeat;

    if(! (dwHeartBeatFlags & HEARTBEAT_INITIALIZED) )
        return;

    LOCK_HEARTBEAT();
    if(heartbeat_data.flags & HBF_INIT_HEARTBEAT)
    {
        //預計 SERVER 的下次心跳
        dwNextSyncTimes = (dwTimes - heartbeat_data.dwSyncTimes) + dwTimes;

        //
        if(dwNextSyncTimes > heartbeat_data.dwBeatTimes)
        {
            //到下一次同步, 自己需要心跳的次數.
            dwBeats = dwNextSyncTimes - heartbeat_data.dwBeatTimes;
            
            //時間間隔
            dwPeriod = heartbeat_data.dwMsPerBeat * (heartbeat_data.dwBeatTimes - heartbeat_data.dwLastTimes);
            
            if(dwBeats > 0 && dwPeriod > 0)
            {
                dwMsPerBeat = dwPeriod / dwBeats;
                if(dwMsPerBeat < 25)
                    dwMsPerBeat = 25;   //最快不超過每秒40次.
            }
            else
            {
                dwMsPerBeat = 50;
            }
            
            heartbeat_data.dwLastTimes = heartbeat_data.dwBeatTimes;
            heartbeat_data.dwSyncTimes = dwTimes;
            heartbeat_data.dwMsPerBeat = dwMsPerBeat;
        }
        //自己的心跳太快, 以致到下次同步時自己都不需要, 所以, 需要慢下來.
        else if(dwNextSyncTimes < heartbeat_data.dwBeatTimes)
        {
            heartbeat_data.dwLastTimes = heartbeat_data.dwBeatTimes;
            heartbeat_data.dwSyncTimes = dwTimes;
            heartbeat_data.dwMsPerBeat = 100;   //固定慢為每秒10次.
        }
    }
    else
    {
        heartbeat_data.dwLastTimes = dwTimes;
        heartbeat_data.dwBeatTimes = dwTimes;
        heartbeat_data.dwSyncTimes = dwTimes;
        heartbeat_data.dwMsPerBeat = 50;
        heartbeat_data.flags |= HBF_INIT_HEARTBEAT;
    }
    UNLOCK_HEARTBEAT();
}


DWORD   get_heartbeat_times(void)
{
    DWORD   dwData;

    LOCK_HEARTBEAT();
    dwData = heartbeat_data.dwBeatTimes;
    UNLOCK_HEARTBEAT();

    return  dwData;
}


DWORD   get_heartbeat_refresh_times(void)
{
    DWORD   dwData;

    LOCK_HEARTBEAT();
    dwData = heartbeat_data.dwRefreshTimes;
    heartbeat_data.dwRefreshTimes = 0;
    UNLOCK_HEARTBEAT();

    return  dwData;
}


/******************************************************************************************************************/
/* STATIC HEARTBEAT FUNCTIONS                                                                                     */
/******************************************************************************************************************/
#ifdef  USE_C_RUNTIME_LIBRARY
unsigned __stdcall HeartBeatThread(void* lpParameter)
#else//!USE_C_RUNTIME_LIBRARY
static  DWORD   WINAPI  HeartBeatThread ( LPVOID lpParameter )
#endif//USE_C_RUNTIME_LIBRARY
{
    HANDLE  hEvents[2] = { hHeartBeatEvent, hHeartBeatExitEvent };
    DWORD   dwObject, dwMsPerBeat;
    BOOL    bLoop;
    DWORD   dwError;
    
    log_error(1, "HeartBeat starting .......................");
    bLoop = TRUE;
    while( TRUE == bLoop)
    {
        LOCK_HEARTBEAT();
        dwMsPerBeat = heartbeat_data.dwMsPerBeat;
        UNLOCK_HEARTBEAT();

        dwObject = WaitForMultipleObjects( 2, hEvents, FALSE, dwMsPerBeat );
        switch(dwObject)
        {
        case WAIT_OBJECT_0: // hHeartBeatEvent
            ExecHeartBeat();
            break;
        case WAIT_OBJECT_0 + 1: // hHeartBeatExitEvent
            bLoop = FALSE;
            break;
        case WAIT_TIMEOUT:  // Our specify timeout
            ExecHeartBeat();
            break;
        case WAIT_FAILED:
            dwError = GetLastError();
            log_error(1, "WIN32 Error Code(%d) at HeartBeatThread()", dwError);
            break;
        default:
            break;
        }
    }
    log_error(1, "HeartBeat ended.");

#ifdef  USE_C_RUNTIME_LIBRARY
    _endthreadex(0);
#else//!USE_C_RUNTIME_LIBRARY
    //ExitThread(0);
#endif//USE_C_RUNTIME_LIBRARY

    return 0;
}




static  SLONG   InitializeHeartBeat( void )
{
    DWORD   dwThreadID;

    hHeartBeatEvent = CreateEvent( NULL, FALSE, FALSE, NULL );
    hHeartBeatExitEvent = CreateEvent( NULL, FALSE, FALSE, NULL );
    if( hHeartBeatEvent && hHeartBeatExitEvent )
    {
#ifdef  USE_C_RUNTIME_LIBRARY
        hHeartBeatThread = (HANDLE*)_beginthreadex( NULL, 0, HeartBeatThread, NULL, CREATE_SUSPENDED, (unsigned int*)&dwThreadID );
#else//!USE_C_RUNTIME_LIBRARY
        hHeartBeatThread = CreateThread ( NULL, 0, HeartBeatThread, NULL, CREATE_SUSPENDED, &dwThreadID );
#endif//USE_C_RUNTIME_LIBRARY

        Sleep(200);
        return  TTN_OK;
    }
    return TTN_NOT_OK;
}


static  void    DestroyHeartBeat( void )
{
    if( hHeartBeatThread )
    {
        SetEvent( hHeartBeatExitEvent );
        Sleep( 200 );
        hHeartBeatThread = NULL;
    }
    CloseHandle( hHeartBeatEvent );
    hHeartBeatEvent = NULL;
    CloseHandle( hHeartBeatExitEvent );
    hHeartBeatExitEvent = NULL;
}


//功能 : 執行心跳處理.
//說明 : 使用方式
//       方式1: 我們可以將遊戲的刷新等函數放在本函數中執行, 不過, 需要注意避免主線程和本線程
//              之間的數據衝突.
//       方式2: 紀錄累加的刷新次數, 主線程中獲得這個次數值後, 就將其RESET, 並根據該次數來執行
//              遊戲的刷新函數.
static  void    ExecHeartBeat(void)
{
    LOCK_HEARTBEAT();
    heartbeat_data.dwRefreshTimes++;
    heartbeat_data.dwBeatTimes ++;
    UNLOCK_HEARTBEAT();
}



