//-------------------------------------------------------------------------------
// Psalm of Sea WorldServer Create
// By Hawke Hsieh
// 2002-10-7
//-------------------------------------------------------------------------------
#include "WorldServer_Def.h"

//-------------------------------------------------------------------------------
// WorldServer Create Init
//-------------------------------------------------------------------------------
void CreateInit()
{
	char	    str[256];
	FILE        *f;
	WORD	    wVersionRequested;
	WSADATA     wd;
	int         iRet;
	
	compressbuf=(char *)malloc(COMPRESS_BUF_SIZE);
    memset(compressbuf, 0x00, COMPRESS_BUF_SIZE);
	Macro = (TPOS_MACRO_WORLD *)malloc(sizeof(TPOS_MACRO_WORLD));
	memset(Macro, 0x0, sizeof(TPOS_MACRO_WORLD));

	ZoneMacro = (TPOS_MACRO_ZONE *)malloc(sizeof(TPOS_MACRO_ZONE));
	memset(ZoneMacro, 0x0, sizeof(TPOS_MACRO_ZONE));

	memset(ZoneInfo, 0x0, sizeof(TPOS_ZONEINFO)*MAX_ZONE_PER_WORLD);

	memset(str, 0x0, 25);
	f = fopen("door_ip.txt","rb");
	if(f == NULL)
	{
		//TODO: error handle ...
		return;
	}

	fgets(str, 25, f);
	fclose(f);
	sprintf(DoorServerAddr,"%s",str);
	
	f = fopen("door_port.txt","rb");
	if(f == NULL)
	{
		//TODO: error handle ...
		return;
	}
	fgets(str, 25, f);
	fclose(f);
	DoorServerPort=atoi(str); 
	
	// 起始 Winsock
	// The high order byte specifies the minor version (revision) number;
	// The low-order byte specifies the major version number.
	wVersionRequested = MAKEWORD(1, 2);  // Winsock 2
	iRet = WSAStartup(wVersionRequested, &wd);
	if(iRet != 0)
	{
		WSACleanup();		
	}
	// 為了以後 QQ Server 獨立使用
	//GetQQServerInfoFromDoor = (TPOS_QQ_SERVER_INFO *)malloc(sizeof(TPOS_QQ_SERVER_INFO) * 100);
    //memset(GetQQServerInfoFromDoor,0x0,sizeof(TPOS_QQ_SERVER_INFO) * 100);

	//InitQQDiskIO();
	/*
	InitQQData();	
	*/
		
}
//-------------------------------------------------------------------------------
// Active Dialog Server
//-------------------------------------------------------------------------------
int Active()
{
	int TempCount; 
	char TempBuf[5];
	DWORD	TmpAddr;     
	static  unsigned char *IPArray;
    char	MyIp[16];
	DWORD	IpCount;
	
	for(TempCount=8799;TempCount<8809;TempCount++)
	{
		itoa(TempCount,TempBuf,10);
		SendDlgItemMessage(SetuphWnd,
			IDC_COMBO1,
			CB_ADDSTRING,
			0,
			(LPARAM)TempBuf
			);
	}
	GetHostIp(MyIp, 16, (char **)&IPArray , &IpCount);
	TmpAddr = (IPArray[0] << 24) | (IPArray[1] << 16) | (IPArray[2] << 8) | IPArray[3];
    SendDlgItemMessage(SetuphWnd,IDC_IPADDRESS1,IPM_SETADDRESS,0,(LONG)TmpAddr);

	SendDlgItemMessage(SetuphWnd,IDC_COMBO1,CB_SETCURSEL,0,0);	
	return DLL_OK;
}
//-------------------------------------------------------------------------------
// Set Connect World Server Info 
//-------------------------------------------------------------------------------
int SetConnectInfo()
{
	int    iRet;
	char   TmpBuffer[100];
	DWORD  TmpAddr;
	
	memset(TmpBuffer,0,100);
	// 檢查是否設定 WorldServer Name
	GetDlgItemText(SetuphWnd,IDC_EDIT1,TmpBuffer,256);
	if(strcmp(TmpBuffer,"")==0)
	{
		 if(MessageBox(SetuphWnd,
			"WorldServer Name Is Empty!!",
			"Error",
			MB_OK|MB_ICONSTOP
			)==IDOK)return DLL_ERROR;  
	}			
	strcpy(WorldServerName,TmpBuffer);

	// 檢查是否設定 WorldServer IP
	iRet=SendDlgItemMessage(SetuphWnd,IDC_IPADDRESS1,IPM_ISBLANK,0,0);
	if(iRet!=0)
	{
		if(MessageBox(SetuphWnd,
			"WorldServer IP Is Empty!!",
			"Error",
			MB_OK|MB_ICONSTOP
			)==IDOK)return DLL_ERROR;  }
	// 取得 WorldServer 設定的 IP
	SendDlgItemMessage(SetuphWnd,IDC_IPADDRESS1,IPM_GETADDRESS,0,(LONG)&TmpAddr);
	sprintf(WorldServerAddr,"%d.%d.%d.%d",
		(TmpAddr & 0xff000000) >> 24,
		(TmpAddr & 0x00ff0000) >> 16,
		(TmpAddr & 0x0000ff00) >> 8,
		(TmpAddr & 0x000000ff)
		); 


	// 檢查是否設定 WorldServer Port
	iRet=SendDlgItemMessage(SetuphWnd,IDC_COMBO1,CB_GETCURSEL,0,0);
	if(iRet==CB_ERR)
	{
		if(MessageBox(SetuphWnd,
			"WorldServer Port Is Empty!!",
			"Error",
			MB_OK|MB_ICONSTOP
			)==IDOK)return DLL_ERROR;  
	}	
	// 取得 WorldServer 設定的 Port
	SendDlgItemMessage(SetuphWnd,IDC_COMBO1,CB_GETLBTEXT,iRet,(LONG)TmpBuffer);
	WorldServerPort=atoi(TmpBuffer);
	return DLL_OK;
}
//-------------------------------------------------------------------------------
// Active Login Door Server and Start World Server
//-------------------------------------------------------------------------------
int StartWorldServer()
{
	int        iRet;  
	HMENU      TmpMnu;
	char       str[256];	
	
	// 所有相關人數統計設定
	dwConnectedCounter = 0;	       //已連線總人數
	dwOnlineCounter = 0;
	dwOnlineLoginer = 0;
	dwOnlineMaxLoginer = 0;
	dwOnlineAllWorldPlayer = 0;
	dwOnlineAllWorldMaxPlayer = 0;
	dwQQIDCounter = 0;
	iZoneCount = 0;

	LoadConnectedCounter();	
	LoadMaxPlayer();
	LoadMaxLoginer();
	LoadQQIDCounter();
	sprintf(str,"Now Login : %d", dwOnlineLoginer);
    MsgOut(hStatusBarWnd,0,str);
	sprintf(str,"Now Players All World : %d", dwOnlineAllWorldPlayer);
    MsgOut(hStatusBarWnd,1,str);
	sprintf(str,"Max Login : %d", dwOnlineMaxLoginer);
    MsgOut(hStatusBarWnd,2,str);
	sprintf(str,"Max Playera All World : %d", dwOnlineAllWorldMaxPlayer);
    MsgOut(hStatusBarWnd,3,str);
	sprintf(str,"Now Zone : %d",iZoneCount);
	MsgOut(hStatusBarWnd,4,str);
	sprintf(str,"Connected : %d",dwConnectedCounter);
	MsgOut(hStatusBarWnd,5,str);


	// 連接資料庫
	InitODBC();
	iRet = ConnectODBC("POS","posadmin","hawkesch");	
	
	server_load_macro((USTR*)"sea.smf");
	
	InitCharacterDefault();
	InitCountryDefaultCity();
	// 啟動 World Server
	iRet=WorldWinSockInit(MainhWnd,WorldServerPort,WorldServerAddr);
	if(iRet!=DLL_OK)
	{
		switch(iRet)
		{
		case WINSOCK_VER_ERROR:
			if(MessageBox(MainhWnd,"WINSOCK_VER_ERROR","Error",MB_OK|MB_ICONERROR)==IDOK)        
				break;
		case INIT_SOCKET_ERROR:
			if(MessageBox(MainhWnd,"INIT_SOCKET_ERROR","Error",MB_OK|MB_ICONERROR)==IDOK)                
				break;
		case CANT_CONNECTED:        
			if(MessageBox(MainhWnd,"CANT_CONNECTED","Error",MB_OK|MB_ICONERROR)==IDOK)        
				break; 
		case CANT_ASYNC:        
			if(MessageBox(MainhWnd,"CANT_ASYNC","Error",MB_OK|MB_ICONERROR)==IDOK)        
				break;
		} 
		
		return FALSE;
	} 
	SaveMsgToLog("SYSTEM","INIT_WORLDSERVER_OK");

//Temp remarked..., 2002.12.10.
	//init_qqqueryheartbeat();
	//start_qqqueryheartbeat();
	
	// 連接 Door Server
	iRet=DoorWinSockInit(MainhWnd);
	if(iRet!=DLL_OK)
	{
		switch(iRet)
		{
		case WINSOCK_VER_ERROR:
			if(MessageBox(MainhWnd,"WINSOCK_VER_ERROR","Error",MB_OK|MB_ICONERROR)==IDOK)        
				break;
		case INIT_SOCKET_ERROR:
			if(MessageBox(MainhWnd,"INIT_SOCKET_ERROR","Error",MB_OK|MB_ICONERROR)==IDOK)                
				break;
		case CANT_CONNECTED:        
			if(MessageBox(MainhWnd,"CANT_CONNECTED","Error",MB_OK|MB_ICONERROR)==IDOK)        
				break; 
		case CANT_ASYNC:        
			if(MessageBox(MainhWnd,"CANT_ASYNC","Error",MB_OK|MB_ICONERROR)==IDOK)        
				break;
		} 
		
		return FALSE;
	} 
	SaveMsgToLog("SYSTEM","INIT_DOORSERVER_OK");
	
/*  // 為了以後 QQ Server 獨立使用
	// 連接 QQ Server
	iRet=QQWinSockInit(MainhWnd);
	if(iRet!=DLL_OK)
	{
		switch(iRet)
		{
		case WINSOCK_VER_ERROR:
			if(MessageBox(MainhWnd,"QQ_WINSOCK_VER_ERROR","Error",MB_OK|MB_ICONERROR)==IDOK)        
				break;
		case INIT_SOCKET_ERROR:
			if(MessageBox(MainhWnd,"QQ_INIT_SOCKET_ERROR","Error",MB_OK|MB_ICONERROR)==IDOK)                
				break;
		case CANT_CONNECTED:        
			if(MessageBox(MainhWnd,"QQ_CANT_CONNECTED","Error",MB_OK|MB_ICONERROR)==IDOK)        
				break; 
		case CANT_ASYNC:        
			if(MessageBox(MainhWnd,"QQ_CANT_ASYNC","Error",MB_OK|MB_ICONERROR)==IDOK)        
				break;
		} 
		
		return FALSE;
	} 
	SaveMsgToLog("SYSTEM","INIT_QQSERVER_OK");
	*/

	TmpMnu=GetMenu(MainhWnd);
	EnableMenuItem(TmpMnu,ID_MENUITEM40001,MF_GRAYED);
	EnableMenuItem(TmpMnu,ID_MENUITEM40002,MF_ENABLED);
	EnableMenuItem(TmpMnu,ID_MENUITEM40003,MF_GRAYED);
	EnableMenuItem(TmpMnu,ID_MENUITEM40005,MF_ENABLED);
	return DLL_OK;
}

//-------------------------------------------------------------------------------
SLONG   server_load_macro(USTR *filename)
{
    FILE    *fp = NULL;
    SLONG   file_size;
    USTR*   file_buf = NULL;

    //載入macro文件到file_buf中 ---------------------
    if(NULL == (fp = fopen((const char *)filename, "rb")))
    {
        //log_error(1, "file %s open error", filename);
        goto _error;
    }
    fseek(fp, 0L, SEEK_END);
    file_size = ftell(fp);
    if(NULL == (file_buf = (USTR*)malloc(file_size)))
    {
        //log_error(1, "memory alloc error");
        goto _error;
    }
    fseek(fp, 0L, SEEK_SET);
    fread(file_buf, 1, file_size, fp);
    fclose(fp);

    //解壓讀取的數據到compressbuf中
    compresssize = file_size;
    uncompresssize = lzo_decompress(file_buf, compresssize, compressbuf);
    free(file_buf); file_buf = NULL;

    //將解壓後的數據複製到Macro中
    if(uncompresssize != sizeof(TPOS_MACRO_WORLD))
    {
        //log_error(1, "uncompressed file size error");
        goto _error;
    }
    LOCK_MACRO(0);
    memcpy(&Macro[0], compressbuf, sizeof(TPOS_MACRO_WORLD));
    UNLOCK_MACRO(0);

    return  0;

_error:
    if(fp) { fclose(fp); fp = NULL; }
    if(file_buf) { free(file_buf); file_buf = NULL; }
    return  -1;
}
//-------------------------------------------------------------------------------
BOOL	CheckHaveManagerFile()
{
	FILE    *f = NULL;    
	char	filename[256];
	char	str[256];

	sprintf(filename,"startworldname.txt");
    if(NULL == (f = fopen((const char *)filename, "rb")))
    {        
        goto _error;
    }
	fgets(WorldServerName, 256, f);
	fclose(f);
	remove(filename);

	sprintf(filename,"startworldport.txt");
    if(NULL == (f = fopen((const char *)filename, "rb")))
    {        
        goto _error;
    }
	fgets(str, 256, f);
	fclose(f);
	remove(filename);
	WorldServerPort = atoi(str);
	
	return TRUE;

_error:
	return FALSE;
}
//-------------------------------------------------------------------------------

