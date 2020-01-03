//-------------------------------------------------------------------------------
// ZoneServer VC Ver 
// By Haweke Hsieh
// 2002-10-05
//-------------------------------------------------------------------------------
#include "ZoneServer_Def.h"
#include "ZoneServer_Var.h"
//#include "ServerAuxiMain.h"


//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
int _stdcall WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{ 
    MSG     msg; 
	HACCEL  hAccelTable;
    INITCOMMONCONTROLSEX    InitControls;  
    
    //初始化遊戲數據
    //if(0 != init_server_auxi_main())
    //    return FALSE;
    
	InitCriticalSectionGlobals();
	InitQuestCriticalSection();	
    InitControls.dwSize = sizeof(INITCOMMONCONTROLSEX);
    InitControls.dwICC = ICC_BAR_CLASSES|ICC_INTERNET_CLASSES;
    InitCommonControlsEx( &InitControls );
    
	HaveManagerFile = CheckHaveManagerFile();
	
    MainhInst=hInstance;    
    if(!Main_Init(MainhInst, nCmdShow)) 
        return FALSE; 
    
	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDR_ZONESERVER);
    while (GetMessage(&msg, NULL, 0, 0) )
    {
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
	FreeQuestCriticalSection();	
	FreeCriticalSectionGlobals();	
    //釋放遊戲數據
    //free_server_auxi_main();
    
    return	msg.wParam;
    
}
//-------------------------------------------------------------------------------
BOOL Main_Init(HINSTANCE hInstance, int nCmdShow)
{
    WNDCLASSEX wc;	
    char    title[128];
    
    wc.cbSize           = sizeof(wc);
    wc.style			= CS_HREDRAW | CS_VREDRAW | CS_NOCLOSE;	
    wc.lpfnWndProc	    = WndProc;
    wc.cbClsExtra		= 0;
    wc.cbWndExtra		= 0;
    wc.hInstance		= hInstance;
    wc.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
    wc.hCursor		    = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);	
    wc.lpszMenuName     = (LPCSTR)IDR_MENU1;
    wc.lpszClassName	= szClassName;//"ZoneServer VC Ver";
    wc.hIconSm		    = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
    
    int s=RegisterClassEx(&wc);   
    
    sprintf((char *)title, "ZoneServer(VC) V%d.%d", CURRENT_VERSION / 1000, CURRENT_VERSION / 10);
    MainhWnd = CreateWindow(
        szClassName,//"ZoneServer VC Ver",
        title,      //"ZoneServer VC Ver",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        0,
        CW_USEDEFAULT,
        0,
        NULL,
        NULL,
        MainhInst,
        NULL);	
    
    if (!MainhWnd)
    {
        return FALSE;
    }
    
    ShowWindow(MainhWnd, nCmdShow);
    
    //InitCommonControls();

    //hStatusBarWnd = CreateStatusBar(hInst, hWnd);
    //hListViewWnd = CreateListView(hInst, hWnd);
    UpdateWindow(MainhWnd);
    
    return TRUE;
}
//-------------------------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    int iRet;	
	static  unsigned char *IPArray;    
	DWORD	IpCount;	

    switch (message) 
    {  
    case WM_CREATE:
        if(0 != CreateInit())PostQuitMessage(0);
		if(HaveManagerFile == TRUE)
		{			
			ServerStart = TRUE;
			GetHostIp(ZoneServerIP, 16, (char **)&IPArray , &IpCount);
	
			iRet = StartZoneServer();
			if(iRet == FALSE)PostQuitMessage(0);			
		}        
        return 0;
        
    case WM_COMMAND:
        {
            switch(wParam)
            {       
            case IDM_SYSTEM_ACTIVE:
                DialogBox(MainhInst, (LPCTSTR)IDD_DIALOG1, hWnd, (DLGPROC)DlgSetupProc);
                if(ServerStart == TRUE)
                {
                    iRet = StartZoneServer(); 
                }
                return 0;
                
            case IDM_SYSTEM_SHUTDOWN:
                iRet = ShutDownServer();
                ServerStart = FALSE;
                return 0;
                
            case IDM_SYSTEM_EXIT:
                PostQuitMessage(0);
                return 0;
                
            case IDM_SYSTEM_RELOGIN_WORLDSERVER:
                ReLoginDoorAndWorld();
                return 0;
                
            default:
                break;	
            }
        }
        break;
        
    case WM_PAINT:			 
        break;
        
    case WM_DESTROY:
        break;        

        /*
    case WM_POSGAMEEVENT:
        switch(lParam)
        {
        case DOOR_SERVER_CLOSED:
            MessageBox(MainhWnd,
                "DoorServer Close!!",
                "Error",
                MB_OK|MB_ICONERROR);
            break;
        case WORLD_SERVER_CLOSED:
            MessageBox(MainhWnd,
                "WorldServer Close!!",
                "Error",
                MB_OK|MB_ICONERROR);
            ReLoginDoorAndWorld();
            
            break; 			
        }
        break;
        */

    default:
        break;	  
    }

    return DefWindowProc(hWnd, message, wParam, lParam);
}

//-------------------------------------------------------------------------------
LRESULT CALLBACK DlgSetupProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    int wmId, wmEvent,iRet;	 

    SetuphWnd = hDlg;
    wmId    = LOWORD(wParam);
    wmEvent = HIWORD(wParam);

    switch (message)
    {   
    case WM_INITDIALOG:       	  
        iRet = Active();
        if(iRet == FALSE)
            EndDialog(hDlg, wmId);
        return TRUE;
        
    case WM_COMMAND:
        {
            switch(wmId)
            {
            case IDC_COMBO1:
                {
                    switch(wmEvent)
                    {			  
                    case CBN_DROPDOWN: 				   
                        break;
                    case CBN_CLOSEUP:
                        break; 
                    }
                }
                return TRUE; 
                
            case IDACTIVE:	
                iRet = SetConnectInfo();
                if(iRet == DLL_OK)
                {
                    ServerStart = TRUE;
                    EndDialog(hDlg, wmId);
                }			 
                return TRUE;
                    
            case IDCANCEL:
                EndDialog(hDlg, wmId);
                return TRUE;			 
            } 
        }
        break;
    }
    return FALSE;
}

//-------------------------------------------------------------------------------
LRESULT CALLBACK DlgReloginProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    int wmId, wmEvent,iRet;	 

    SetuphWnd = hDlg;
    switch (message)
    {   
    case WM_INITDIALOG:       	         
        return TRUE;
        
    case WM_COMMAND:       	   
        wmId    = LOWORD(wParam);
        wmEvent = HIWORD(wParam);
        switch(wmId)
        {
        case IDC_COMBO1:
            {
                switch(wmEvent)
                {			  
                case CBN_DROPDOWN: 				   
                    break;
                case CBN_CLOSEUP:
                    break; 
                }
            }
            return TRUE; 
            
        case IDACTIVE:	
            iRet = SetConnectInfo();
            if(iRet == DLL_OK)
            {
                ServerStart = TRUE;			 		 
                EndDialog(hDlg, wmId);
            }			 
            return TRUE;
            
        case IDCANCEL:
            EndDialog(hDlg, wmId);
            return TRUE;			 
        } 
        break;
    }
    return FALSE;
}
//-------------------------------------------------------------------------------
void    gameExit(void){}
int     gameMain(void){return 0;}
int     gameInit(void){return 0;}
int     gameSet(void){return 0;}
//-------------------------------------------------------------------------------

