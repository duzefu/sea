//-------------------------------------------------------------------------------
// Psalm of Sea ZoneServer Create
// By Hawke Hsieh
// 2002-10-7
//-------------------------------------------------------------------------------
#include "ZoneServer_Def.h"

#define SYNC_COMPRESS_BUF_SIZE      16384
#define COMPRESS_BUF_SIZE           16777216
#define MAX_CHARACTER               1000
#define MAX_WORLD_INFO              500
#define MAX_NPC_TYPE                500

SLONG   server_load_macro(char *filename);
SLONG   server_load_npc_type(USTR *filename);
SLONG   server_load_door_addr_port(void);

//-------------------------------------------------------------------------------
// ZoneServer Create Init
//-------------------------------------------------------------------------------
int CreateInit()
{
    WORD	wVersionRequested;
    WSADATA wd;
    int     iRet;
        
	InitZoneServerData();
	// 2002-12-04 Add for QQ by Hawke
	//InitQQData();
    //MagicType=(TPOS_MAGIC *)malloc(sizeof(TPOS_MAGIC)*200);
    //memset(MagicType,0x0,sizeof(TPOS_MAGIC)*200);
    
    //ItemType=(TPOS_ITEM *)malloc(sizeof(TPOS_ITEM)*500);
    //memset(ItemType,0x0,sizeof(TPOS_ITEM)*500);    

    // 起始 Winsock
    // The high order byte specifies the minor version (revision) number;
    // The low-order byte specifies the major version number.
    wVersionRequested = MAKEWORD(1, 2);  // Winsock 2.1
    iRet = WSAStartup(wVersionRequested, &wd);
    if(iRet != 0)
    {
        WSACleanup();
        return  -1;
    }   		
    return  0;
}

//-------------------------------------------------------------------------------
// Active Login Door Server
//-------------------------------------------------------------------------------
int Active()
{
    int     iRet,TempCount;
    char    TempBuf[5];
	DWORD	TmpAddr;     
	static  unsigned char *IPArray;    
	DWORD	IpCount;

	GetHostIp(ZoneServerIP, 16, (char **)&IPArray , &IpCount);
	
    iRet = DoorWinSockInit(MainhWnd);
    if(iRet != DLL_OK)
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
    
    for(TempCount=0;TempCount<MAX_ZONE_PER_MACRO;TempCount++)
    {
        if(strcmp(ZoneMapDefault[TempCount].cZoneName,"")!=0)
        {       				
            SendDlgItemMessage(SetuphWnd,
                IDC_COMBO2,
                CB_ADDSTRING,
                0,
                (LPARAM)ZoneMapDefault[TempCount].cZoneName
                );         	   
        }
    }
    
    for(TempCount=9110; TempCount<9210; TempCount++)
    {
        itoa(TempCount, TempBuf, 10);
        SendDlgItemMessage(SetuphWnd,
            IDC_COMBO3,
            CB_ADDSTRING,
            0,
            (LPARAM)TempBuf
            );
    }
	
	TmpAddr = (IPArray[0] << 24) | (IPArray[1] << 16) | (IPArray[2] << 8) | IPArray[3];
    SendDlgItemMessage(SetuphWnd,IDC_IPADDRESS3,IPM_SETADDRESS,0,(LONG)TmpAddr);	
	
	SendDlgItemMessage(SetuphWnd,IDC_COMBO2,CB_SETCURSEL,0,0);
	SendDlgItemMessage(SetuphWnd,IDC_COMBO3,CB_SETCURSEL,0,0);
    return DLL_OK;
}
//-------------------------------------------------------------------------------
// Set Connect World Server Info and Set Zone Server Info
//-------------------------------------------------------------------------------
int SetConnectInfo()
{
    int    iRet,x;
    char   TmpBuffer[100];
    DWORD  TmpAddr;       
	
    // 檢查是否選取 WorldServer
    iRet=SendDlgItemMessage(SetuphWnd,IDC_COMBO1,CB_GETCURSEL,0,0);
    if(iRet==CB_ERR)
    {
        if(MessageBox(SetuphWnd,
            "WorldServer Name Is Empty!!",
            "Error",
            MB_OK|MB_ICONSTOP
            )==IDOK)return DLL_ERROR;
    }
    // 取得所設定的 WorldServer Name , Addr , Port 
    SendDlgItemMessage(SetuphWnd,IDC_COMBO1,CB_GETLBTEXT,iRet,(LONG)TmpBuffer);
    for(x=0;x<500;x++)
    {
        if(strcmp(TmpBuffer,GetWorldInfoFromDoor[x].cName)==0)
        {
            strcpy(WorldServerAddr,GetWorldInfoFromDoor[x].cAddr);
            WorldServerPort = GetWorldInfoFromDoor[x].dwPort;
            
            break;
        }	  
    }
    // 檢查是否設定 ZoneServer Name (選取地圖)
    iRet=SendDlgItemMessage(SetuphWnd,IDC_COMBO2,CB_GETCURSEL,0,0);
    if(iRet==CB_ERR)
    {
        if(MessageBox(SetuphWnd,
            "ZoneServer Name Is Empty!!",
            "Error",
            MB_OK|MB_ICONSTOP
            )==IDOK)return DLL_ERROR; 
    }    
    
    // 取得 ZoneServer 設定的 Name
    SendDlgItemMessage(SetuphWnd,IDC_COMBO2,CB_GETLBTEXT,iRet,(LONG)TmpBuffer);
	strcpy(ZoneName, TmpBuffer);       
    
    // 檢查是否設定 ZoneServer IP
    iRet=SendDlgItemMessage(SetuphWnd,IDC_IPADDRESS3,IPM_ISBLANK,0,0);
    if(iRet!=0)
    {
        if(MessageBox(SetuphWnd,
            "ZoneServer IP Is Empty!!",
            "Error",
            MB_OK|MB_ICONSTOP
            )==IDOK)return DLL_ERROR;  }
    // 取得 ZoneServer 設定的 IP
    SendDlgItemMessage(SetuphWnd,IDC_IPADDRESS3,IPM_GETADDRESS,0,(LONG)&TmpAddr);
    sprintf(ZoneServerIP,"%d.%d.%d.%d",	
			(TmpAddr & 0xff000000) >> 24,
			(TmpAddr & 0x00ff0000) >> 16, 
			(TmpAddr & 0x0000ff00) >> 8,
			(TmpAddr & 0x000000ff)); 
    
    // 檢查是否設定 ZoneServer Port
    iRet = SendDlgItemMessage(SetuphWnd,IDC_COMBO3,CB_GETCURSEL,0,0);
    if(iRet == CB_ERR)
    {
        if(MessageBox(SetuphWnd, "ZoneServer Port Is Empty!!", "Error",MB_OK | MB_ICONSTOP ) == IDOK)
            return DLL_ERROR;  
    }

    // 取得 ZoneServer 設定的 Port
    SendDlgItemMessage(SetuphWnd,IDC_COMBO3,CB_GETLBTEXT,iRet,(LONG)TmpBuffer);
    ZoneServerPort = atoi(TmpBuffer);
    return DLL_OK;
}
//-------------------------------------------------------------------------------
// Active Login World Server and Start Zone Server
//-------------------------------------------------------------------------------
int StartZoneServer()
{
    int     iRet;  
    HMENU   TmpMnu;
    char    str[256];    
	SLONG	result;
	int		x;
    
	if(HaveManagerFile == FALSE)
	{
		iRet = CloseDoorServer();
	}    
    SaveMsgToLog("SYSTEM", "LOGOUT_DOOR_OK"); 

	// 設置 Windows Caption
	sprintf(WindowCaption, "ZoneServer(VC) V%d.%d - [ %s ] ",
			CURRENT_VERSION / 1000, CURRENT_VERSION / 10,
			ZoneName);
	SetWindowText(MainhWnd, WindowCaption); 			
    
	// 找出區域使用的地圖名稱
	for(x = 0;x < MAX_ZONE_PER_MACRO;x++)
	{
		if(strcmp(ZoneMapDefault[x].cZoneName, ZoneName)==0)   
		{
			sprintf(mapname,"%s",ZoneMapDefault[x].cMapName);   			
			break;
		}
	}
    // 讀取地圖阻擋	
    sea_data_file=NULL;
    sea_data_file =  open_data_file((char *)"sea.pak"); 
    sprintf(str,"map\\%s.msk",mapname);
	result = LoadZoneMapMask((char *)str);
    if(TTN_OK != result)
    {
        if(MessageBox(MainhWnd,"Can't Read Map Mask File!!","Error",MB_OK)==IDOK)
        {
            SaveMsgToLog("SYSTEM","LOAD_MAP_MASK_FAIL"); 
        }
    }
    else
    { 
        SaveMsgToLog("SYSTEM","LOAD_MAP_MASK_OK"); 
    }
    
    // 讀取事件區資料
    clear_all_map_procs();
    sprintf(str,"map\\%s.prc",mapname);
    load_map_proc((USTR *)str);
    SaveMsgToLog("SYSTEM","LOAD_MAP_PROC_OK");        
    
	ZoneActive = MapLink[0].ZoneIndex;

	// 讀取該地圖的類型
	LOCK_MACRO(0);
	ZoneType = ReturnZoneType(Macro[0].Zone[ZoneActive].dType);
	UNLOCK_MACRO(0);

	// 讀取 Macro
	LoadZoneMacroFile(ZoneName);
	
    // 讀取該區域的 NPC 資料	
    LOCK_CHARACTER(0);    
    LoadNPCDataFormMacro();
    UNLOCK_CHARACTER(0);
    
    SaveMsgToLog("SYSTEM","LOAD_ZONE_NPC_OK"); 
        
	// 讀取腳本資料
	// Hawke TODO [1/19/2003]
	sprintf(str, "%s.mac", ZoneName);
	result = load_script((unsigned char *)str);
	if(result == 0)
	{
		SaveMsgToLog("SYSTEM","LOAD_ZONE_SCRIPT_OK"); 
	}

	// 清除任務列表
	InitNPCQuestList();
	// 找出所有是閒人的 NPC
	ServerDoSearchNomalNpc();

	// 讀取寶藏資料
	LoadTreasuryFile();
	
    // 預設區域天氣狀態
    LOCK_WEATHER(0);
	LoadZoneWeather();    
    UNLOCK_WEATHER(0);

	// 讀取地圖連接資料    
    InitMapLinkData(); 
    
    SaveMsgToLog("SYSTEM","SET_ZONE_WEATHER_DEFAULT_OK"); 
    
    // 取得已連接人數
    LoadConnectedCounter();

	// 連接 ODBC
	InitODBC();
    ConnectODBC("POS", "posadmin", "hawkesch");

    // Init ZoneServer And Login WorldServer
    SaveMsgToLog("SYSTEM","INIT_ZONESERVER");
    iRet=ZoneWinSockInit(MainhWnd,ZoneServerPort);
    if(iRet==DLL_ERROR)
    {
        switch(iRet)
        {
        case WINSOCK_VER_ERROR:
            SaveMsgToLog("SYSTEM","ZONE_WINSOCK_VER_ERROR");
            break;
        case INIT_SOCKET_ERROR:
            SaveMsgToLog("SYSTEM","ZONE_INIT_SOCKET_ERROR");
            break;
        case CANT_CONNECTED:
            SaveMsgToLog("SYSTEM","ZONE_CANT_CONNECTED");
            break; 
        case CANT_ASYNC:
            SaveMsgToLog("SYSTEM","ZONE_CANT_ASYNC");
            break;
        }  
        if(MessageBox(SetuphWnd,"WinSocket Problem","Error",MB_OK|MB_ICONERROR)==IDOK)
            return DLL_ERROR;
    }
    SaveMsgToLog("SYSTEM","INIT_ZONESERVER_OK");  

	// init store item 初始商店
	process_script(10);	
    
    // 起始心跳 , 同步座標時鐘 , 同步心跳時鐘
    init_heartbeat();
    init_syncheartbeat();    
	init_savedataheartbeat();
    start_heartbeat();
    start_syncheartbeat();	
	start_savedataheartbeat();
	switch(ZoneType)
	{
	case CITY_NORMAL:
	case CITY_NEWBIE:
	case CITY_PK:
	case CITY_FINDGOLD:
	case CITY_BIRTH:
		// init quest npc
		//process_script(11);
		init_syncpositionheartbeat();
		start_syncpositionheartbeat();
		break;
	case FIELD_NORMAL:
	case FIELD_NEWBIE:
	case FIELD_PK:
	case FIELD_FINDGOLD:
	case FIELD_BIRTH:
		init_syncpositionheartbeat();
		start_syncpositionheartbeat();
		break;
	case SAIL_NORMAL:
	case SAIL_NEWBIE:
	case SAIL_PK:
	case SAIL_FINDGOLD:
	case SAIL_BIRTH:
		init_syncseapositionheartbeat();
		start_syncseapositionheartbeat();
		break;
	}    
    SaveMsgToLog("SYSTEM","INIT_WORLDSERVER"); 
    iRet=WorldWinSockInit(MainhWnd,WorldServerPort,WorldServerAddr);
    if(iRet==DLL_ERROR)
    {
        switch(iRet)
        {
        case WINSOCK_VER_ERROR:
            SaveMsgToLog("SYSTEM","WORLD_WINSOCK_VER_ERROR");
            break;
        case INIT_SOCKET_ERROR:
            SaveMsgToLog("SYSTEM","WORLD_INIT_SOCKET_ERROR");
            break;
        case CANT_CONNECTED:
            SaveMsgToLog("SYSTEM","WORLD_CANT_CONNECTED");
            break; 
        case CANT_ASYNC:
            SaveMsgToLog("SYSTEM","WORLD_CANT_ASYNC");
            break;
        }  
        if(MessageBox(SetuphWnd,"WinSocket Problem","Error",MB_OK|MB_ICONERROR)==IDOK)
            return DLL_ERROR;
    }
    if(iRet==DLL_OK)SaveMsgToLog("SYSTEM","INIT_WORLDSERVER_OK");  
    
    // 改變 MENU 狀態
    TmpMnu = GetMenu(MainhWnd);
    EnableMenuItem(TmpMnu, IDM_SYSTEM_ACTIVE, MF_GRAYED);
    EnableMenuItem(TmpMnu, IDM_SYSTEM_SHUTDOWN, MF_ENABLED);
    EnableMenuItem(TmpMnu, IDM_SYSTEM_EXIT, MF_GRAYED);
    EnableMenuItem(TmpMnu, IDM_SYSTEM_RELOGIN_WORLDSERVER, MF_ENABLED);

    return DLL_OK;
}
//-------------------------------------------------------------------------------
int ReLoginDoorAndWorld()
{
    HMENU      TmpMnu;
    int    iRet,x;
    char   TmpBuffer[100];
    
    iRet=CloseWorldServer();
    if(iRet==DLL_OK)
    {
        SaveMsgToLog("SYSTEM","LOGOUT_WORLDSERVER_OK");
    }else
    {
        SaveMsgToLog("SYSTEM","LOGOUT_WORLDSERVER_FAIL");
    }	
    
    DialogBox(MainhInst, (LPCTSTR)IDD_DIALOG2, MainhWnd, (DLGPROC)DlgReloginProc);
    
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
    iRet=CloseDoorServer();
    SaveMsgToLog("SYSTEM", "LOGOUT_DOOR_OK"); 
    
    // 檢查是否選取 WorldServer
    iRet=SendDlgItemMessage(ReloginhWnd,IDC_COMBO1,CB_GETCURSEL,0,0);
    if(iRet==CB_ERR)
    {
        if(MessageBox(ReloginhWnd,
            "WorldServer Name Is Empty!!",
            "Error",
            MB_OK|MB_ICONSTOP
            )==IDOK)return DLL_ERROR;
    }
    // 取得所設定的 WorldServer Name , Addr , Port 
    SendDlgItemMessage(ReloginhWnd,IDC_COMBO1,CB_GETLBTEXT,iRet,(LONG)TmpBuffer);
    for(x=0;x<500;x++)
    {
        if(strcmp(TmpBuffer,GetWorldInfoFromDoor[x].cName)==0)
        {
            strcpy(WorldServerAddr,GetWorldInfoFromDoor[x].cAddr);
            WorldServerPort=GetWorldInfoFromDoor[x].dwPort;			
            break;
        }	  
    }
    LOCK_ZONEINFO(0);
    for(x=0;x<MAX_ZONE_PER_WORLD;x++)
    {
        memset(&ZoneInfo[x],0x0,sizeof(TPOS_ZONEINFO));
    }
    UNLOCK_ZONEINFO(0);
    
    iRet=WorldWinSockInit(MainhWnd,WorldServerPort,WorldServerAddr);
    if(iRet==DLL_ERROR)
    {
        switch(iRet)
        {
        case WINSOCK_VER_ERROR:
            SaveMsgToLog("SYSTEM","WORLD_WINSOCK_VER_ERROR");
            break;
        case INIT_SOCKET_ERROR:
            SaveMsgToLog("SYSTEM","WORLD_INIT_SOCKET_ERROR");
            break;
        case CANT_CONNECTED:
            SaveMsgToLog("SYSTEM","WORLD_CANT_CONNECTED");
            break; 
        case CANT_ASYNC:
            SaveMsgToLog("SYSTEM","WORLD_CANT_ASYNC");
            break;
        }  
        if(MessageBox(SetuphWnd,"WinSocket Problem","Error",MB_OK|MB_ICONERROR)==IDOK)
            return DLL_ERROR;
    }
    if(iRet==DLL_OK)SaveMsgToLog("SYSTEM","INIT_WORLDSERVER_OK");  	
    
    TmpMnu = GetMenu(MainhWnd);
    EnableMenuItem(TmpMnu, IDM_SYSTEM_ACTIVE, MF_GRAYED);
    EnableMenuItem(TmpMnu, IDM_SYSTEM_SHUTDOWN, MF_ENABLED);
    EnableMenuItem(TmpMnu, IDM_SYSTEM_EXIT, MF_GRAYED);
    EnableMenuItem(TmpMnu, IDM_SYSTEM_RELOGIN_WORLDSERVER, MF_ENABLED);

    return DLL_OK;
}

/******************************************************************************************************************/
/* INIT FUNCTIONS                                                                                                 */
/******************************************************************************************************************/
SLONG   server_load_macro(char *filename)
{
    FILE    *fp = NULL;
    SLONG   file_size;
    USTR*   file_buf = NULL;
	char	tempstr[256];

	sprintf(tempstr,"Macro\\%s.smf",filename);
    //載入macro文件到file_buf中 ---------------------
    if(NULL == (fp = fopen(tempstr, "rb")))
    {
        log_error(1, "file %s open error", filename);
        goto _error;
    }
    fseek(fp, 0L, SEEK_END);
    file_size = ftell(fp);
    if(NULL == (file_buf = (USTR*)malloc(file_size)))
    {
        log_error(1, "memory alloc error");
        goto _error;
    }
    fseek(fp, 0L, SEEK_SET);
    fread(file_buf, 1, file_size, fp);
    fclose(fp);

    //解壓讀取的數據到compressbuf中
    compresssize = file_size;
    uncompresssize = lzo_decompress(file_buf, compresssize, compressbuf);
    free(file_buf); file_buf = NULL;

    //將解壓後的數據複製到Marco中
    if(uncompresssize != sizeof(TPOS_MACRO_WORLD))
    {
        log_error(1, "uncompressed file size error");
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

//---------------------------------------------------------------------------------
SLONG   server_load_npc_type(USTR *filename)
{
    FILE    *fp = NULL;
    SLONG   file_size;
    USTR *  file_buf = NULL;

    //載入文件到file_buf
    if(NULL == (fp = fopen((const char *)filename,"rb")))
    {
        log_error(1, "file %s open error", filename);
        goto _error;
    }
    fseek(fp, 0L, SEEK_END);
    file_size = ftell(fp);
    if(NULL == (file_buf = (USTR*)malloc(file_size)))
    {
        log_error(1, "memory alloc error");
        goto _error;
    }
    fseek(fp, 0L, SEEK_SET);
    fread(file_buf, 1, file_size, fp);
    fclose(fp); fp = NULL;

    //開始解壓
    compresssize = file_size;
    uncompresssize = lzo_decompress(file_buf, compresssize, compressbuf);
    free(file_buf); file_buf = NULL;

    //將解壓後的數據複製到NPCType中
    if(uncompresssize != sizeof(TPOS_NPC) * MAX_NPC_TYPE)
    {
        log_error(1, "uncompressed file size error");
        goto _error;
    }
    LOCK_NPCTYPE(0);
    memcpy(NPCType, compressbuf, sizeof(TPOS_NPC) * MAX_NPC_TYPE);
    UNLOCK_NPCTYPE(0);

    return  0;

_error:
    if(fp) { fclose(fp); fp = NULL; }
    if(file_buf) { free(file_buf); file_buf = NULL; }
    return  -1;
}

//---------------------------------------------------------------------------------
SLONG   server_load_door_addr_port(void)
{
    char    str[32];
    FILE    *fp = NULL;

    memset(str, 0x00, 32);
    if(NULL == (fp = fopen("door_ip.txt", "rb")))
    {
        log_error(1, "open file door_ip.txt error");
        goto _error;
    }
    fgets(str, 25, fp);
    fclose(fp); fp = NULL;
    sprintf(DoorServerAddr, "%s", str);

    memset(str, 0x00, 32);
    if(NULL == (fp = fopen("door_port.txt","rb")))
    {
        log_error(1, "open file door_port.txt error");
        goto _error;
    }
    fgets(str, 32, fp);
    fclose(fp); fp = NULL;
    DoorServerPort = atoi(str); 
    return  0;

_error:
    return  -1;
}
//---------------------------------------------------------------------------------
SLONG	LoadZoneMacroFile(char *Name)
{
	FILE    *fp = NULL;
    SLONG   file_size;
    USTR*   file_buf = NULL;
	char	filename[256];

	sprintf(filename,"Macro\\%s.zmf", Name);
    //載入macro文件到file_buf中 ---------------------
    if(NULL == (fp = fopen((const char *)filename, "rb")))
    {        
        goto _error;
    }
    fseek(fp, 0L, SEEK_END);
    file_size = ftell(fp);
    if(NULL == (file_buf = (USTR*)malloc(file_size)))
    {        
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
    if(uncompresssize != sizeof(TPOS_MACRO_ZONE))
    {
        //log_error(1, "uncompressed file size error");
        goto _error;
    }
    LOCK_ZONEMACRO(0);
    memcpy(&ZoneMacro[0], compressbuf, sizeof(TPOS_MACRO_ZONE));
    UNLOCK_ZONEMACRO(0);

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

	sprintf(filename,"worldname.txt");
    if(NULL == (f = fopen((const char *)filename, "rb")))
    {        
        goto _error;
    }
	//fgets(WorldServerName, 256, f);
	fgets(cWorldServerName, 256, f);	
	fclose(f);
	remove(filename);

	sprintf(filename,"worldip.txt");
    if(NULL == (f = fopen((const char *)filename, "rb")))
    {        
        goto _error;
    }
	fgets(WorldServerAddr, 256, f);
	fclose(f);
	remove(filename);

	sprintf(filename,"worldport.txt");
    if(NULL == (f = fopen((const char *)filename, "rb")))
    {        
        goto _error;
    }
	fgets(str, 256, f);
	fclose(f);
	remove(filename);
	WorldServerPort = atoi(str);

	sprintf(filename,"startzonename.txt");
    if(NULL == (f = fopen((const char *)filename, "rb")))
    {        
        goto _error;
    }
	fgets(ZoneName, 256, f);
	fclose(f);
	remove(filename);

	sprintf(filename,"startzoneport.txt");
    if(NULL == (f = fopen((const char *)filename, "rb")))
    {        
        goto _error;
    }
	fgets(str, 256, f);
	fclose(f);
	remove(filename);
	ZoneServerPort = atoi(str);

	
	return TRUE;

_error:
	return FALSE;
}
//-------------------------------------------------------------------------------
