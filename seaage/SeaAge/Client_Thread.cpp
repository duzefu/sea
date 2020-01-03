/*
**	Client_Thread.cpp 
**	client thread functions.
**
**	Jack, 2003.1.14
*/
#include "MainFun.h"
#include "NetGE_MainFunc.h"
#include "ClientMain.h"
//#include "NetGE.h"
//#include "NetGE_Event_Struct_Def.h"
#include "NetGE_Event_Def.h"
#include "Client_Thread.h"
#include "Client_RecvMsg.h"


/************************************************************************************************************/
/* DEFINES                                                                                                  */
/************************************************************************************************************/
#define CLIENT_SEND_PER_MILLISECONDS        350
#define CLIENTSENDMSGLIST_SIZE              2048
#define CLIENTRECVMSGLIST_SIZE              2048


/************************************************************************************************************/
/* GLOBALS                                                                                                  */
/************************************************************************************************************/
HWND    g_hWndGameEvent;
static	CHAR	GameEventClassName[] = "PosGameEvent";

// client send & recv message buffers
static  APPMSG  ClientSendMsgList[CLIENTSENDMSGLIST_SIZE];
static  LONG    ClientSendMsgPutIndex;
static  APPMSG  ClientRecvMsgList[CLIENTRECVMSGLIST_SIZE];
static  LONG    ClientRecvMsgPutIndex;

// client critical section
static  CRITICAL_SECTION    g_csClientSendMsgList;
static  CRITICAL_SECTION    g_csClientRecvMsgList;

// about client send message 
static  HANDLE  hClientSendMsgThread = NULL;                
static  HANDLE  hClientSendMsgEvent = NULL;
static  HANDLE  hClientSendMsgExitEvent = NULL;

// about client process message
static  HANDLE  hClientProcessMsgThread = NULL;
static  HANDLE  hClientProcessMsgEvent = NULL;
static  HANDLE  hClientProcessMsgExitEvent = NULL;




static	LONG	InitGameEventWindow(VOID);
static	VOID	FreeGameEventWindow(VOID);
static	LRESULT CALLBACK GameEventWndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

static  void    InitializeClientSendMsgList( void );
static  void    DestroyClientSendMsgList( void );

static  void    InitializeClientRecvMsgList( void );
static  void    DestroyClientRecvMsgList( void );

static  void    ClientSendMsg( void );
static  DWORD   WINAPI  ClientSendMsgThread ( LPVOID lpParameter );
static  SLONG   InitializeClientSendMsg( void );
static  void    DestroyClientSendMsg( void );

extern  void    ClientProcessMsg( void );
static  DWORD   WINAPI  ClientProcessMsgThread ( LPVOID lpParameter );
static  SLONG   InitializeClientProcessMsg( void );
static  void    DestroyClientProcessMsg( void );

/************************************************************************************************************/
/* CLIENT THREAD MAIN FUNCTIONS                                                                             */
/************************************************************************************************************/
int     init_client(void)
{
    InitializeClientSendMsgList();
    InitializeClientRecvMsgList();

	/*
    if(TTN_OK != InitializeClientProcessMsg() )
    {
        log_error(1, "        InitializeClientProcessMsg failed.");
        return	-1;
    }
	*/

    // Jack, remark [1/14/2003]
    /*
    if(TTN_OK != InitializeClientSendMsg() )
    {
        log_error(1, "        InitializeClientSendMsg failed.");
        goto error;
    }
	*/

	if(0 != InitGameEventWindow())
	{
		log_error(1, "init game event window failed");
		return	-2;
	}

	return	0;
}


void    active_client(int active)
{
}


void    free_client(void)
{
	FreeGameEventWindow();

    //DestroyClientSendMsg() ;
    //DestroyClientProcessMsg() ;

    DestroyClientRecvMsgList();
    DestroyClientSendMsgList();
}



/************************************************************************************************************/
/* GAME EVENT WINDOW FUNCTIONS                                                                              */
/************************************************************************************************************/
LRESULT CALLBACK GameEventWndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
    switch (iMsg)
    {
    case WM_POSGAMEEVENT:
		{
			DWORD	dwType, dwSize;
			
			dwType = (lParam & 0xffff0000) >> 16;
			dwSize = lParam & 0xffff;
			// Jack, process message directly. [1/16/2003]
			//AddClientRecvMsg((LPVOID)wParam, dwType, dwSize, 0, 0);
			HandlePosGameEvent(hWnd, 0, wParam, dwType);
		}
        return  0;
        
    case WM_DESTROY:
        return 0;
    }
    return DefWindowProc(hWnd, iMsg, wParam, lParam);
}


LONG	InitGameEventWindow(VOID)
{
    WNDCLASS	wc;
	HWND	hWnd;
    
    wc.style			= 0;
    wc.lpfnWndProc		= (WNDPROC)GameEventWndProc;
    wc.cbClsExtra		= 0;
    wc.cbWndExtra		= 0;
    wc.hInstance		= g_hInstance;
    wc.hIcon			= NULL; 
    wc.hCursor			= NULL; 
    wc.hbrBackground	= NULL;
    wc.lpszMenuName     = NULL;
    wc.lpszClassName	= GameEventClassName;
    
    if(!RegisterClass(&wc))
    {
        return -1;
    }
    
    hWnd = CreateWindow(GameEventClassName, "", 0L, 0, 0, 0, 0, NULL, NULL, g_hInstance, NULL);
    
    if(hWnd == NULL)
    {
        UnregisterClass(GameEventClassName, g_hInstance);
        return -1;
    }
    
    ShowWindow(hWnd, SW_HIDE);
    UpdateWindow(hWnd);

	g_hWndGameEvent = hWnd;
	//g_hWndGameEvent = g_hDDWnd;
    
    return  0;
}


VOID	FreeGameEventWindow(VOID)
{
    DestroyWindow(g_hWndGameEvent);
    UnregisterClass(GameEventClassName, g_hInstance);
}


/************************************************************************************************************/
/* ClientSendMsgList Functions                                                                              */
/************************************************************************************************************/
static  void    InitializeClientSendMsgList( void )
{
    LONG    i;
    
    InitializeCriticalSection( &g_csClientSendMsgList );
    EnterCriticalSection( &g_csClientSendMsgList );
    for(i=0; i<CLIENTSENDMSGLIST_SIZE; i++)
    {
        ClientSendMsgList[i].dwSize = 0;
        ClientSendMsgList[i].idFrom = 0;
        ClientSendMsgList[i].idTo = 0;
        ClientSendMsgList[i].lpBuffer = NULL;
    }
    ClientSendMsgPutIndex = 0;
    LeaveCriticalSection( &g_csClientSendMsgList );
}



static  void    DestroyClientSendMsgList( void )
{
    LONG    i;
    
    EnterCriticalSection( &g_csClientSendMsgList );
    for(i=0; i<CLIENTSENDMSGLIST_SIZE; i++)
    {
        ClientSendMsgList[i].dwSize = 0;
        ClientSendMsgList[i].idFrom = 0;
        ClientSendMsgList[i].idTo = 0;
        if( ClientSendMsgList[i].lpBuffer)
        {
            GlobalFree( ClientSendMsgList[i].lpBuffer );
            ClientSendMsgList[i].lpBuffer = NULL;
        }
    }
    ClientSendMsgPutIndex = 0;
    LeaveCriticalSection( &g_csClientSendMsgList );

    DeleteCriticalSection( &g_csClientSendMsgList );
}


void    AddClientSendMsg( LPVOID lpBuffer, DWORD dwSize, DWORD idFrom, DWORD idTo )
{
    EnterCriticalSection( &g_csClientSendMsgList );
    if( ClientSendMsgPutIndex < CLIENTSENDMSGLIST_SIZE )
    {
        if( ClientSendMsgList[ClientSendMsgPutIndex].lpBuffer )
        {
            GlobalFree( ClientSendMsgList[ClientSendMsgPutIndex].lpBuffer );
            ClientSendMsgList[ClientSendMsgPutIndex].lpBuffer = NULL;
        }
        
        if(NULL != (ClientSendMsgList[ClientSendMsgPutIndex].lpBuffer = GlobalAlloc(GPTR, dwSize)))
        {
            ClientSendMsgList[ClientSendMsgPutIndex].dwSize = dwSize ;
            ClientSendMsgList[ClientSendMsgPutIndex].idFrom = idFrom ;
            ClientSendMsgList[ClientSendMsgPutIndex].idTo = idTo ;
			
            CopyMemory( ClientSendMsgList[ClientSendMsgPutIndex].lpBuffer, lpBuffer, dwSize);
            
            ClientSendMsgPutIndex ++ ;
        }
    }
	else
	{
		log_error(1, "ERROR: ClientSendMsgPutIndex out range");
	}
    LeaveCriticalSection( &g_csClientSendMsgList );
}


/************************************************************************************************************/
/* ClientRecvMsgList Functions                                                                              */
/************************************************************************************************************/
static  void    InitializeClientRecvMsgList( void )
{
    LONG    i;
    
    InitializeCriticalSection( &g_csClientRecvMsgList );
    EnterCriticalSection( &g_csClientRecvMsgList );
    for(i=0; i<CLIENTRECVMSGLIST_SIZE; i++)
    {
        ClientRecvMsgList[i].dwSize = 0;
        ClientRecvMsgList[i].idFrom = 0;
        ClientRecvMsgList[i].idTo = 0;
        ClientRecvMsgList[i].lpBuffer = NULL;
    }
    ClientRecvMsgPutIndex = 0;
    LeaveCriticalSection( &g_csClientRecvMsgList );
}




static  void    DestroyClientRecvMsgList( void )
{
    LONG    i;
    
    EnterCriticalSection( &g_csClientRecvMsgList );
    for(i=0; i<CLIENTRECVMSGLIST_SIZE; i++)
    {
        ClientRecvMsgList[i].dwSize = 0;
        ClientRecvMsgList[i].idFrom = 0;
        ClientRecvMsgList[i].idTo = 0;
        if( ClientRecvMsgList[i].lpBuffer)
        {
            GlobalFree( ClientRecvMsgList[i].lpBuffer );
            ClientRecvMsgList[i].lpBuffer = NULL;
        }
    }
    ClientRecvMsgPutIndex = 0;
    LeaveCriticalSection( &g_csClientRecvMsgList );
    DeleteCriticalSection( &g_csClientRecvMsgList );
}




void    AddClientRecvMsg( LPVOID lpBuffer, DWORD dwType, DWORD dwSize, DWORD idFrom, DWORD idTo )
{
    EnterCriticalSection( &g_csClientRecvMsgList );
    if( ClientRecvMsgPutIndex < CLIENTRECVMSGLIST_SIZE )
    {
        if( ClientRecvMsgList[ClientRecvMsgPutIndex].lpBuffer )
        {
            GlobalFree( ClientRecvMsgList[ClientRecvMsgPutIndex].lpBuffer );
            ClientRecvMsgList[ClientRecvMsgPutIndex].lpBuffer = NULL;
        }
		if(lpBuffer && dwSize)
		{
			if(NULL != (ClientRecvMsgList[ClientRecvMsgPutIndex].lpBuffer = GlobalAlloc(GPTR, dwSize) ) )
			{
				ClientRecvMsgList[ClientRecvMsgPutIndex].dwType = dwType ;
				ClientRecvMsgList[ClientRecvMsgPutIndex].dwSize = dwSize ;
				ClientRecvMsgList[ClientRecvMsgPutIndex].idFrom = idFrom ;
				ClientRecvMsgList[ClientRecvMsgPutIndex].idTo = idTo ;
				
				CopyMemory( ClientRecvMsgList[ClientRecvMsgPutIndex].lpBuffer, lpBuffer, dwSize);
				
				ClientRecvMsgPutIndex ++ ;
				
				//PS: If we want to process client message now, just use the following line.
				//    But for this "Petra" case, we will process it in main-thread, so remark it.
				//SetEvent( hClientProcessMsgEvent );
			}
			else
			{
			}
		}
        
    }
	else
	{
		//ZJian, 2002.2.1. how to handle this error ?
		log_error(1,"ERROR: ClientRecvMsgPutIndex out range");
	}
    LeaveCriticalSection( &g_csClientRecvMsgList );
}

/************************************************************************************************************/
/* ClientProcessMsg functions                                                                               */
/************************************************************************************************************/
static  DWORD   WINAPI  ClientProcessMsgThread ( LPVOID lpParameter )
{
    HANDLE  hEvents[2] = { hClientProcessMsgEvent,  hClientProcessMsgExitEvent };
    DWORD   dwObject;
    BOOL    bLoop;
    DWORD   dwError;
    
	/*
    log_error(1, "");
    log_error(1, "THREAD ClientProcessMsgThread() starting .......................");
    log_error(1, "");
	*/

    bLoop = TRUE;
    while( TRUE == bLoop)
    {
        dwObject = WaitForMultipleObjects( 2, hEvents, FALSE, INFINITE ) ;
        switch(dwObject)
        {
        case WAIT_OBJECT_0 + 1: // hClientProcessMsgExitEvent
            bLoop = FALSE;
            break;
        case WAIT_OBJECT_0:     // hClientProcessMsgEvent
            ClientProcessMsg();
            break;
        case WAIT_FAILED:
            dwError = GetLastError();
            log_error(1, "WIN32 Error Code(%d) at ClientProcessMsgThread()", dwError);
            break;
        default:
            break;
        }
    }

	/*
    log_error(1, "");
    log_error(1, "THREAD ClientProcessMsgThread() ending .......................");
    log_error(1, "");
	*/

    return 0;
}



static  SLONG   InitializeClientProcessMsg( void )
{
    DWORD dwThreadID;

    hClientProcessMsgEvent = CreateEvent( NULL, FALSE, FALSE, NULL );
    hClientProcessMsgExitEvent = CreateEvent( NULL, FALSE, FALSE, NULL );
    if( hClientProcessMsgEvent && hClientProcessMsgExitEvent)
    {
        hClientProcessMsgThread = CreateThread ( NULL, 0, ClientProcessMsgThread, NULL, 0, &dwThreadID );
        if( hClientProcessMsgThread )
        {
            Sleep(200);
            return TTN_OK;
        }
    }
    return TTN_ERROR;
}


static  void    DestroyClientProcessMsg( void )
{
    if( hClientProcessMsgThread )
    {
        SetEvent( hClientProcessMsgExitEvent );
        Sleep( 200 );
        hClientProcessMsgThread = NULL;
    }
    CloseHandle( hClientProcessMsgEvent );
    hClientProcessMsgEvent = NULL;

    CloseHandle( hClientProcessMsgExitEvent );
    hClientProcessMsgExitEvent = NULL;
}




void    ClientProcessMsg( void )
{
    EnterCriticalSection( &g_csClientRecvMsgList );

    for(LONG i = 0; i<ClientRecvMsgPutIndex; i++ )
    {
		HandlePosGameEvent(NULL, 0, (WPARAM)ClientRecvMsgList[i].lpBuffer, ClientRecvMsgList[i].dwType);
    }
    ClientRecvMsgPutIndex = 0 ;

    LeaveCriticalSection( &g_csClientRecvMsgList );
}



/************************************************************************************************************/
/* ClientSendMsg functions                                                                                  */
/************************************************************************************************************/
static  void    ClientSendMsg( void )
{
    LONG    index;
    BOOL    bIdle = TRUE ;
    //LONG    ret;
    
    EnterCriticalSection( &g_csClientSendMsgList );
    
    index = ClientSendMsgPutIndex-1;
    if(index >= 0)
    {
        if( (ClientSendMsgList[index].dwSize != 0) && (ClientSendMsgList[index].lpBuffer != NULL) )
        {
            bIdle = FALSE;

			// Jack, TODO [1/14/2003]
			// Remark godlast's functions.
			/*
            // Server sim client send msg to itself.
            // if(g_bIsHost)
            if( g_dpidLocal == g_dpidHost )
            {
                AddServerRecvMsg( ClientSendMsgList[index].lpBuffer, ClientSendMsgList[index].dwSize,
                    ClientSendMsgList[index].idFrom, ClientSendMsgList[index].idTo );
            }
            else
            {
                ret = NET_send_data( ClientSendMsgList[index].lpBuffer, ClientSendMsgList[index].dwSize,
                    ClientSendMsgList[index].idFrom, ClientSendMsgList[index].idTo );
                if(ret != 0)
                {
                    //the host lost, or some other error occured
                    sprintf((char *)print_rec,"client send msg error");
                    log_error(1, print_rec);
                }
            }
			*/
        }
    }
    // If we want to send idle_msg to the server...
    if(bIdle)
    {
        //Send idle msg here.
    }
    ClientSendMsgPutIndex = 0;
    
    LeaveCriticalSection( &g_csClientSendMsgList );
}


static  DWORD   WINAPI  ClientSendMsgThread ( LPVOID lpParameter )
{
    HANDLE  hEvents[2] = { hClientSendMsgEvent, hClientSendMsgExitEvent };
    DWORD   dwObject;
    BOOL    bLoop;
    DWORD   dwError;
    
    log_error(1, "");
    log_error(1, "THREAD ClientSendMsgThread() starting .......................");
    log_error(1, "");

    bLoop = TRUE;
    while( TRUE == bLoop)
    {
        dwObject = WaitForMultipleObjects( 2, hEvents, FALSE, CLIENT_SEND_PER_MILLISECONDS ) ;
        switch(dwObject)
        {
        case WAIT_OBJECT_0: // hClientSendMsgEvent
            ClientSendMsg();
            break;
        case WAIT_OBJECT_0 + 1: // hClientSendMsgExitEvent
            bLoop = FALSE;
            break;
        case WAIT_TIMEOUT:  // Our specify timeout
            ClientSendMsg();
            break;
        case WAIT_FAILED:
            dwError = GetLastError();
            log_error(1, "WIN32 Error Code(%d) at ClientSendMsgThread()", dwError);
            break;
        default:
            break;
        }
    }

    log_error(1, "");
    log_error(1, "THREAD ClientSendMsgThread() ending .......................");
    log_error(1, "");
    return 0;
}



static  SLONG   InitializeClientSendMsg( void )
{
    DWORD   dwThreadID;

    hClientSendMsgEvent = CreateEvent( NULL, FALSE, FALSE, NULL );
    hClientSendMsgExitEvent = CreateEvent( NULL, FALSE, FALSE, NULL );
    if( hClientSendMsgEvent && hClientSendMsgExitEvent)
    {
        hClientSendMsgThread = CreateThread ( NULL, 0, ClientSendMsgThread, NULL, 0, &dwThreadID );
        if( hClientSendMsgThread )
        {
            Sleep(200);
            return TTN_OK;
        }
    }
    return TTN_ERROR;
}


static  void    DestroyClientSendMsg( void )
{
    if( hClientSendMsgThread )
    {
        SetEvent( hClientSendMsgExitEvent );
        Sleep( 200 );
        hClientSendMsgThread = NULL;
    }
    CloseHandle( hClientSendMsgEvent );
    hClientSendMsgEvent = NULL;
    CloseHandle( hClientSendMsgExitEvent );
    hClientSendMsgExitEvent = NULL;
}


