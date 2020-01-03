//-------------------------------------------------------------------------------
// DoorServer VC Ver 
// By Haweke Hsieh
// 2002-10-20
//-------------------------------------------------------------------------------
#include "DoorServer_Def.h"
#include "DoorServer_Var.h"

//-------------------------------------------------------------------------------
BOOL      Main_Init(HINSTANCE hInstance, int nCmdShow);
LRESULT   CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

//-------------------------------------------------------------------------------
int _stdcall WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{ 
	MSG                     msg; 
	INITCOMMONCONTROLSEX    InitControls;  

	//初始化遊戲數據臨界區
	InitCriticalSectionGlobals();

	InitControls.dwSize = sizeof(INITCOMMONCONTROLSEX);
	InitControls.dwICC = ICC_BAR_CLASSES|ICC_INTERNET_CLASSES;
	InitCommonControlsEx( &InitControls );
 
	MainInst=hInstance;    
	if(!Main_Init(MainInst, nCmdShow)) return FALSE; 
 
    while (GetMessage(&msg, NULL, 0, 0) )
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    //釋放遊戲數據臨界區
    FreeCriticalSectionGlobals();

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
	wc.lpszClassName	= szClassName;//"WorldServer VC Ver";
	wc.hIconSm		    = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));

    int s=RegisterClassEx(&wc);   

    sprintf((char *)title, "DoorServer(VC) V%d.%d", CURRENT_VERSION / 1000, CURRENT_VERSION / 10);
    MainhWnd = CreateWindow(
		       szClassName, //"DoorServer VC Ver",
		       title,       //"DoorServer VC Ver",
		       WS_OVERLAPPEDWINDOW,
		       CW_USEDEFAULT,
		       0,
		       CW_USEDEFAULT,
		       0,
		       NULL,
		       NULL,
		       MainInst,
		       NULL);	

    if (!MainhWnd)
	{
      return FALSE;
	}	

    ShowWindow(MainhWnd, nCmdShow);

	//InitCommonControls();
	hStatusBarWnd = CreateStatusBar(hInstance, MainhWnd);
	hListViewWnd = CreateListView(hInstance, MainhWnd);	
    UpdateWindow(MainhWnd);	

	return TRUE;
}
//-------------------------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent,iRet;
	RECT		r;
	DWORD		x, y, cx, cy;
	switch (message) 
	{  
	case WM_CREATE:
		CreateInit();
		//SaveMsgToLog("SYSTEM","INIT FORM SUCCESS");	   
		return 0;
		
	case WM_COMMAND:
		wmId    = LOWORD(wParam); 
		wmEvent = HIWORD(wParam); 
		switch (wmId) 
		{       
        case ID_MENUITEM40001:					 			 
			iRet=Active();			
			iRet=SetConnectInfo();
			if(iRet==DLL_OK)
			{
				bDoorServerStart=TRUE;			 		 					
			}				
			if(bDoorServerStart==TRUE)
			{
				iRet=StartDoorServer(); 
			}			              
			return 0;
			
        case ID_MENUITEM40002:             
			iRet=ShutDownServer();			
			return 0;			 
			
		case ID_MENUITEM40003:			
			PostQuitMessage(0);
			return 0;						
        
		case ID_MENUITEM40004:
			ChangeWorldStateToEnable();
			return 0;

		case ID_MENUITEM40005:
			ChangeWorldStateToDisable();
			return 0;
		
		case ID_MENUITEM40007:
			
			return 0;

		default:
			break;	
		}
		break;
	case WM_CONTEXTMENU:
		DoContextMenu(hWnd, MainInst, wParam, lParam);
		break;
	case WM_SIZE:
		// fix ListView window
		if(hListViewWnd == NULL) break;
		GetClientRect(hWnd, &r);
		SetWindowPos(hListViewWnd, NULL, r.left, r.top, r.right, r.bottom-20, SWP_SHOWWINDOW);
		// fix StatusBar window
		InitStatusBar(hWnd, hStatusBarWnd);
		GetWindowRect(hStatusBarWnd, &r);
		cy = r.bottom - r.top;
		x = 0;
		y = HIWORD(lParam) - cy;
		cx = LOWORD(lParam);
		MoveWindow(hStatusBarWnd, x, y, cx, cy, TRUE);
		break;
			
	case WM_PAINT:			 
		break;
		
	case WM_DESTROY:       
		//PostQuitMessage(0);
		break;        	
		
	default:
		break;	  
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}
//-------------------------------------------------------------------------------