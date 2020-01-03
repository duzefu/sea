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
#define HEARTBEAT_INITIALIZED       0x00000001  //�߸��Ҳդw�g��l��
#define HEARTBEAT_CS_INITIALIZED    0x00000002  //�߸����{�ɰϤw�g��l��
//
#define HBF_INIT_HEARTBEAT          0x01
//
#define LOCK_HEARTBEAT()            EnterCriticalSection(&csHeartBeat)
#define UNLOCK_HEARTBEAT()          LeaveCriticalSection(&csHeartBeat)
//
// S T R U C T U R E S /////////////////////////////////////////////////////////////////////////////////////////////
typedef struct tagHEARTBEAT_DATA
{
    SLONG   flags;          //�лx

    DWORD   dwLastTimes;    //�W��������P�B���ɭ�, �����ۤv�߸�������.
    DWORD   dwBeatTimes;    //������e���߸�����
    DWORD   dwMsPerBeat;    //�C���߸������j�ɶ�(�@��)
    //
    DWORD   dwSyncTimes;    //�W�������쪺�P�B�߸�����
    //
    DWORD   dwRefreshTimes; //��o���ݭn��s������
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

    //��l���{�ɰ�
    InitializeCriticalSection(&csHeartBeat);
    dwHeartBeatFlags |= HEARTBEAT_CS_INITIALIZED;

    //��l�Ƥ߸��ƾ�
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
        //�w�p SERVER ���U���߸�
        dwNextSyncTimes = (dwTimes - heartbeat_data.dwSyncTimes) + dwTimes;

        //
        if(dwNextSyncTimes > heartbeat_data.dwBeatTimes)
        {
            //��U�@���P�B, �ۤv�ݭn�߸�������.
            dwBeats = dwNextSyncTimes - heartbeat_data.dwBeatTimes;
            
            //�ɶ����j
            dwPeriod = heartbeat_data.dwMsPerBeat * (heartbeat_data.dwBeatTimes - heartbeat_data.dwLastTimes);
            
            if(dwBeats > 0 && dwPeriod > 0)
            {
                dwMsPerBeat = dwPeriod / dwBeats;
                if(dwMsPerBeat < 25)
                    dwMsPerBeat = 25;   //�̧֤��W�L�C��40��.
            }
            else
            {
                dwMsPerBeat = 50;
            }
            
            heartbeat_data.dwLastTimes = heartbeat_data.dwBeatTimes;
            heartbeat_data.dwSyncTimes = dwTimes;
            heartbeat_data.dwMsPerBeat = dwMsPerBeat;
        }
        //�ۤv���߸��ӧ�, �H�P��U���P�B�ɦۤv�����ݭn, �ҥH, �ݭn�C�U��.
        else if(dwNextSyncTimes < heartbeat_data.dwBeatTimes)
        {
            heartbeat_data.dwLastTimes = heartbeat_data.dwBeatTimes;
            heartbeat_data.dwSyncTimes = dwTimes;
            heartbeat_data.dwMsPerBeat = 100;   //�T�w�C���C��10��.
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


//�\�� : ����߸��B�z.
//���� : �ϥΤ覡
//       �覡1: �ڭ̥i�H�N�C������s����Ʃ�b����Ƥ�����, ���L, �ݭn�`�N�קK�D�u�{�M���u�{
//              �������ƾڽĬ�.
//       �覡2: �����֥[����s����, �D�u�{����o�o�Ӧ��ƭȫ�, �N�N��RESET, �îھڸӦ��ƨӰ���
//              �C������s���.
static  void    ExecHeartBeat(void)
{
    LOCK_HEARTBEAT();
    heartbeat_data.dwRefreshTimes++;
    heartbeat_data.dwBeatTimes ++;
    UNLOCK_HEARTBEAT();
}



