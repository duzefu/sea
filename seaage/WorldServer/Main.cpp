//-------------------------------------------------------------------------------
// WorldServer VC Ver 
// By Haweke Hsieh
// 2002-10-05
//-------------------------------------------------------------------------------
#include "WorldServer_Def.h"
#include "WorldServer_Var.h"

void	gameExit(void){}
int		gameMain(void){return 0;}
int		gameInit(void){return 0;}
int		gameSet(void) {return 0;}

//-------------------------------------------------------------------------------
BOOL      Main_Init(HINSTANCE hInstance, int nCmdShow);
LRESULT   CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR	  CALLBACK ZoneDialogProc(HWND hwndDlg,  // handle to dialog box
                                  UINT uMsg,     // message
                                  WPARAM wParam, // first message parameter
                                  LPARAM lParam  // second message parameter
								 );
LRESULT CALLBACK DlgSetupProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK DlgSystemMessageProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
//-------------------------------------------------------------------------------
int _stdcall WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{ 
	MSG                     msg; 
	INITCOMMONCONTROLSEX    InitControls;  

	init_system();
	//初始化遊戲數據臨界區
	InitCriticalSectionGlobals();


	InitControls.dwSize = sizeof(INITCOMMONCONTROLSEX);
	InitControls.dwICC = ICC_BAR_CLASSES|ICC_INTERNET_CLASSES;
	InitCommonControlsEx( &InitControls );
 
	HaveManagerFile = CheckHaveManagerFile();

	MainInst=hInstance;    
	if(!Main_Init(MainInst, nCmdShow)) return FALSE; 
 
    while (GetMessage(&msg, NULL, 0, 0) )
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    //釋放遊戲數據臨界區
    FreeCriticalSectionGlobals();
	free_system();

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

    sprintf((char *)title, "WorldServer(VC) V%d.%d", CURRENT_VERSION / 1000, CURRENT_VERSION / 10);
    MainhWnd = CreateWindow(
		       szClassName, //"ZoneServer VC Ver",
		       title,       //"WorldServer VC Ver",
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
	static  unsigned char *IPArray;    
	DWORD		IpCount;

	switch (message) 
	{  
	case WM_CREATE:
		CreateInit();		
		if(HaveManagerFile == TRUE)
		{
			bWorldServerStart = TRUE;
			GetHostIp(WorldServerAddr, 16, (char **)&IPArray , &IpCount);		
			iRet=StartWorldServer(); 			
		}
		//SaveMsgToLog("SYSTEM","INIT FORM SUCCESS");	   
		return 0;
		
	case WM_COMMAND:
		wmId    = LOWORD(wParam); 
		wmEvent = HIWORD(wParam); 
		switch (wmId) 
		{       
        case ID_MENUITEM40001:			 			 			 
			DialogBox(MainInst, (LPCTSTR)IDD_DIALOG1, MainhWnd, (DLGPROC)DlgSetupProc);			 			 
			if(bWorldServerStart==TRUE)
			{
				iRet=StartWorldServer(); 
			}			              
			return 0;
			
        case ID_MENUITEM40002:             
			iRet=ShutDownServer();			
			return 0;			 
			
		case ID_MENUITEM40003:			
			PostQuitMessage(0);
			return 0;			
			
        case ID_MENUITEM40005:
			DialogBox(MainInst, (LPCTSTR)IDD_DIALOG2, MainhWnd, (DLGPROC)DlgSystemMessageProc);	
			return 0;
		default:
			break;	
		}
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
LRESULT CALLBACK DlgSetupProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent,iRet;	 
	HMENU      TmpMnu;

	SetuphWnd = hDlg;
	wmId    = LOWORD(wParam);
	wmEvent = HIWORD(wParam);   
	
	switch (message)
	{   
	case WM_INITDIALOG:   
		if(HaveManagerFile == FALSE)
		{			
			iRet=Active();			
			if(iRet==FALSE)EndDialog(hDlg, wmId);	   
		}else
		{
			TmpMnu=GetMenu(MainhWnd);
			EnableMenuItem(TmpMnu,ID_MENUITEM40001,MF_GRAYED);
			EnableMenuItem(TmpMnu,ID_MENUITEM40002,MF_ENABLED);
			EnableMenuItem(TmpMnu,ID_MENUITEM40003,MF_GRAYED);
			EnableMenuItem(TmpMnu,ID_MENUITEM40005,MF_ENABLED);	
			EndDialog(hDlg, wmId);
		}
		return TRUE;
		
	case WM_COMMAND:       	   
		switch(wmId)
		{		
		case IDC_COMBO1:
			switch(wmEvent)
			{			  
			case CBN_DROPDOWN: 				   
				break;
			case CBN_CLOSEUP:
				break; 
			}
			return TRUE; 		
			
			case IDACTIVE:						
				iRet=SetConnectInfo();
				if(iRet==DLL_OK)
				{
					bWorldServerStart=TRUE;			 		 
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
LRESULT CALLBACK DlgSystemMessageProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;	 	
	
	wmId    = LOWORD(wParam);
	wmEvent = HIWORD(wParam);   
	char Msg[256];
	
	switch (message)
	{   
	case WM_INITDIALOG:       	  
		return TRUE;
		
	case WM_COMMAND:       	   
		switch(wmId)
		{		
		case IDC_COMBO1:
			switch(wmEvent)
			{			  
			case CBN_DROPDOWN: 				   
				break;
			case CBN_CLOSEUP:
				break; 
			}
			return TRUE; 		
			
			case IDOK:			
				GetDlgItemText(hDlg,IDC_EDIT1,Msg,256);
				SendSystemMessageToAll(Msg);
				EndDialog(hDlg, wmId);
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