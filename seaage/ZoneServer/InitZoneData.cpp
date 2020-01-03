
#include "ZoneServer_Def.h"
/******************************************************************************************************************/
/* INIT ZONE SERVER DATA
/******************************************************************************************************************/
int     InitZoneServerData(void)
{
    SLONG   result;
	int		i;

    //呼叫RAYSSDK初始化系統.
    result = init_system();
    if(0 != result)
        return  -999;
	
	//初始化Character資料
	InitAllZoneCharacters();

	SyncMove = (TPOS_SYNCMOVE *)malloc(sizeof(TPOS_SYNCMOVE) * MAX_CHARACTER_PER_ZONE);
    memset(SyncMove, 0x00, sizeof(TPOS_SYNCMOVE) * MAX_CHARACTER_PER_ZONE);
	SyncSeaMove = (TPOS_SYNCSEAMOVE *)malloc(sizeof(TPOS_SYNCSEAMOVE) * MAX_CHARACTER_PER_ZONE);
    memset(SyncSeaMove, 0x00, sizeof(TPOS_SYNCSEAMOVE) * MAX_CHARACTER_PER_ZONE);
    Macro = (TPOS_MACRO_WORLD *)malloc(sizeof(TPOS_MACRO_WORLD));
    memset(Macro, 0x00, sizeof(TPOS_MACRO_WORLD));
	ZoneMacro = (TPOS_MACRO_ZONE *)malloc(sizeof(TPOS_MACRO_ZONE));
	memset(ZoneMacro, 0x00, sizeof(TPOS_MACRO_ZONE));
    GetWorldInfoFromDoor = (TPOS_WORLDINFO *)malloc(sizeof(TPOS_WORLDINFO) * MAX_WORLD_PER_DOOR);
    memset(GetWorldInfoFromDoor,0x0,sizeof(TPOS_WORLDINFO) * MAX_WORLD_PER_DOOR);
	SyncCompressBuf=(char *)malloc(SYNC_COMPRESS_BUF_SIZE);
    memset(SyncCompressBuf, 0x00, SYNC_COMPRESS_BUF_SIZE);
    compressbuf=(char *)malloc(COMPRESS_BUF_SIZE);
    memset(compressbuf, 0x00, COMPRESS_BUF_SIZE);

	NPCType = (TPOS_NPC *)malloc(sizeof(TPOS_NPC) * MAX_NPC_TYPE);
    memset(NPCType, 0x00, sizeof(TPOS_NPC) * MAX_NPC_TYPE);

	GetZoneInfoFromMarco=(TPOS_ZONEINFO *)malloc(sizeof(TPOS_ZONEINFO)*100);
    memset(GetZoneInfoFromMarco,0x0,sizeof(TPOS_ZONEINFO)*100);
	
	//初始化天氣資料
    ZoneWeather=(TPOS_ZONEWEATHER*)malloc(sizeof(TPOS_ZONEWEATHER));
    memset(ZoneWeather,0x0,sizeof(TPOS_ZONEWEATHER));    

	//初始壞連接的資料
	for(i = 0;i < MAX_PLAYER_PER_ZONE;i++)
	{
		BadConnect[i] = FALSE;
	}

	// Load Macro
	if(0 != server_load_door_addr_port())
        return  -1;
    if(0 != server_load_macro("sea"))
        return  -1;
    if(0 != server_load_npc_type((USTR*)"Macro\\npc.bse"))
        return  -1;
	
	// 初始化腳本
	init_script();	
	set_script_decode_func(pos_decode_script);

    //初始化法術數值----------------------------------------------	
    result = InitSkillSystem();
    if(TTN_OK != result)
    {
        log_error(1, "load magic data error");
        return  -1;
    }

    //初始化物件影像資訊-------------------------------------------
	InitObjectImageInfo();
    result = LoadObjectImageInfo("data\\objframe.dat");
    if(TTN_OK != result)
    {
        log_error(1, "load object image info error");
        return  -2;
    }

    //初始化陸地NPC文件資訊----------------------------------------
    InitCharacterFileInfo();
    result = LoadCharacterFileInfo("data\\npcfile.ini");
    if(TTN_OK != result)
    {
        log_error(1, "load npc file info error");
        return  -3;
    }

    //初始化海洋NPC文件資訊----------------------------------------
	InitSeaCharacterFileInfo();
	result = LoadSeaCharacterFileInfo("data\\seanpcfile.ini");
	if(TTN_OK != result)
	{
		log_error(1, "load sea npc file info error");
		return	-31;
	}

	//初始化船隻航行運算 ------------------------------------------
	IniMiscMath();
	//DebugLogShipMath();

    //初始化NPC動作事務優先級--------------------------------------
    InitCharacterDoingPriority();
    result = LoadCharacterDoingPriority("data\\doingpri.ini");
    if(TTN_OK != result)
    {
        log_error(1, "load npc doing priority error");
        return  -4;
    }
	DebugLogCharacterDoingPriority();

    //初始化角色升級數據-------------------------------------------
	InitCareerUpgrade();
	result = LoadCareerUpgrade();
    if(TTN_OK != result)
    {
        log_error(1, "load char upgrade data error");
        return  -5;
    }
	InitCareerBaseAffectInfo();
	result = LoadCareerBaseAffectInfo();
    if(TTN_OK != result)
    {
        log_error(1, "load career base affect info error");
        return  -6;
    }    
    //初始化NPC動作事務體------------------------------------------
    server_set_npc_doing_functions();
    //初始AI處理---------------------------------------------------
    server_set_npc_AI_functions();
    //初始化技能處理-----------------------------------------------
    server_init_magic_hit();
	
	//初始化物品系統
	InitItemSystem();

	//初始化商店資料
	InitStoreSystem();

	// 讀取地圖預設值的資料
    InitZoneMapDefault();        

	//初始化寶藏
	InitTreasury();

    return  0;
}
//-------------------------------------------------------------------------------

void    FreeZoneServerData(void)
{
	DisconnectODBC();
	FreeODBC();
    server_free_magic_hit();
    FreeCharacterDoingPriority();
    FreeCharacterFileInfo();
	FreeObjectImageInfo();
    FreeCareerUpgrade();
	FreeCareerBaseAffectInfo();
	free_script();
    FreeGameSkillBase();
	FreeZoneMapMask();	
    close_data_file(sea_data_file);
    clear_all_map_procs();    
    free(SyncMove);
	free(SyncSeaMove);
    free(SyncCompressBuf);
    free(Macro);
	free(ZoneMacro);
    free(NPCType);	
	// 2002-12-04 Add for QQ by Hawke
	//FreeQQData();        
    free(ZoneWeather);    
    //free(MagicType);
	FreeTreasury();
    FreeMapLinkData();
    FreeZoneMapDefault();  	
	FreeStoreSystem();
	FreeItemSystem();
    free_system();
}

//-------------------------------------------------------------------------------
// 預設名稱
//-------------------------------------------------------------------------------
void InitZoneMapDefault()
{
    int TempCount;

    memset(ZoneMapDefault,0x0,sizeof(TPOS_ZONEMAPDEFAULT));
    
	LOCK_MACRO(0);
    for(TempCount=0;TempCount<MAX_ZONE_PER_MACRO;TempCount++)
    {
        if(strcmp(Macro[0].Zone[TempCount].cName,"")!=0)
        {        
            strcpy(ZoneMapDefault[TempCount].cZoneName,
                Macro[0].Zone[TempCount].cName);				
            strcpy(ZoneMapDefault[TempCount].cMapName,
                Macro[0].Zone[TempCount].cMapName);
			ZoneMapDefault[TempCount].dType = 
				Macro[0].Zone[TempCount].dType;
        }
    }
	UNLOCK_MACRO(0);
    
    /*
    // 野外
    strcpy(ZoneMapDefault[0].ZoneName,"Field");
    strcpy(ZoneMapDefault[0].MapName,"map0000");
    // 海盜城市
    strcpy(ZoneMapDefault[1].ZoneName,"Pirate");
    strcpy(ZoneMapDefault[1].MapName,"map0001");
    // 威尼斯
    strcpy(ZoneMapDefault[2].ZoneName,"Vience");
    strcpy(ZoneMapDefault[2].MapName,"map0002");
    // 伊斯坦堡
    strcpy(ZoneMapDefault[3].ZoneName,"Istanbul");
    strcpy(ZoneMapDefault[3].MapName,"map0003");
    */
}
//-------------------------------------------------------------------------------
// 釋放預設名稱
//-------------------------------------------------------------------------------
void FreeZoneMapDefault()
{
    memset(ZoneMapDefault,0x0,sizeof(TPOS_ZONEMAPDEFAULT)*100); 
}
//---------------------------------------------------------------------------
// Init MapLink Data
//---------------------------------------------------------------------------
void InitMapLinkData()
{
    memset(MapLink,0x0,sizeof(TPOS_MAPLINK));
    int j;
    
	LOCK_ZONEMACRO(0);
    for(j=0;j<MAX_MAPLINK_PER_ZONE;j++)
	{
		MapLink[0].ZoneIndex=ZoneMacro[0].Basic.dIndex;
		MapLink[0].Point[j].ZoneData=ZoneMacro[0].Basic.MapLinkPoint[j].dDestZoneIndex;
		MapLink[0].Point[j].lDestX=ZoneMacro[0].Basic.MapLinkPoint[j].lDestZoneX;
		MapLink[0].Point[j].lDestY=ZoneMacro[0].Basic.MapLinkPoint[j].lDestZoneY;
		MapLink[0].Point[j].lDestZ=ZoneMacro[0].Basic.MapLinkPoint[j].lDestZoneZ;
		MapLink[0].Point[j].cDir[0]=ZoneMacro[0].Basic.MapLinkPoint[j].cDir[0] - '0';
		MapLink[0].Point[j].LocalProcessID = ZoneMacro[0].Basic.MapLinkPoint[j].LocalProcessID;
		MapLink[0].Point[j].RemoteProcessID = ZoneMacro[0].Basic.MapLinkPoint[j].RemoteProcessID;
		MapLink[0].Point[j].RemoteLineEndPointX = ZoneMacro[0].Basic.MapLinkPoint[j].RemoteLineEndPointX;
		MapLink[0].Point[j].RemoteLineEndPointY = ZoneMacro[0].Basic.MapLinkPoint[j].RemoteLineEndPointY;
		MapLink[0].Point[j].RemoteLineStartPointX = ZoneMacro[0].Basic.MapLinkPoint[j].RemoteLineStartPointX;
		MapLink[0].Point[j].RemoteLineStartPointY = ZoneMacro[0].Basic.MapLinkPoint[j].RemoteLineStartPointY;
	}    
	UNLOCK_ZONEMACRO(0);
}
//---------------------------------------------------------------------------
// Free Init MapLink Data
//---------------------------------------------------------------------------
void FreeMapLinkData()
{
    memset(MapLink,0x0,sizeof(TPOS_MAPLINK));
}
//---------------------------------------------------------------------------
void LoadNPCDataFormMacro()
{
	int	x;
	int        npc_type;

	LOCK_ZONEMACRO(0);
	for(x = 500; x < 1000; x++)
    {	 
        // NPC型態類型索引
        npc_type = ZoneMacro[0].NPC[x-500].dNPCType;
        // NPC類型名稱
		SetCharacterAccount(x, NPCType[npc_type].Name.cNPCName);        
        // NPC名字
		SetCharacterMainName(x, ZoneMacro[0].NPC[x-500].cName);        
        // 速度
		SetCharacterMoveSpeed(x, NPCType[npc_type].Basic.dMSpeed);        
        // 外觀
		SetCharacterFileIndex(x, NPCType[npc_type].Basic.iFileIndex);        
        // 座標
		SetCharacterPosition(x, ZoneMacro[0].NPC[x-500].dX,
								ZoneMacro[0].NPC[x-500].dY,
								ZoneMacro[0].NPC[x-500].dZ);        
		// 類型
		SetCharacterKind(x, npc_type);
        // 動作
		switch(ZoneType)
		{
		case CITY_NORMAL:
		case CITY_NEWBIE:
		case CITY_PK:
		case CITY_FINDGOLD:
		case CITY_BIRTH:
		case FIELD_NORMAL:
		case FIELD_NEWBIE:
		case FIELD_PK:
		case FIELD_FINDGOLD:
		case FIELD_BIRTH:
			if(NPCType[npc_type].Name.uiKind == 8)
			{
				//mary by lijun 2003-05-22
				//SetCharacterDoingKind(x, DOING_KIND_IDLE);
				//假的!!!!!需要工具裡面取增加....
				SetCharacterAI(x, MAIN_AI_IDLE);
				SetCharacterOnFightState(x, FALSE);
			}else
			{
				//mary by lijun 2003-05-22			
				//SetCharacterAI(x, MAIN_AI_FIGHT_GAD);
				//假的!!!!!需要工具裡面取增加....
				SetCharacterAI(x, MAIN_AI_FIGHT_GAD);
				SetCharacterOnFightState(x, TRUE);
			}
			break;
		case SAIL_NORMAL:
		case SAIL_NEWBIE:
		case SAIL_PK:
		case SAIL_FINDGOLD:
		case SAIL_BIRTH:
			SetCharacterDoingKind(x, DOING_KIND_SEA_IDLE);									
			SetCharacterAI(x, MAIN_AI_IDLE);
			break;
		}     
		//// AI		 假的!!!!!需要工具裡面取增加....
		//SetCharacterAI(x, NPCType[npc_type].Basic.dAI);
        // 生命
		SetCharacterHp(x, (UHINT)NPCType[npc_type].Basic.dHP);
		SetCharacterMaxHp(x, (UHINT)NPCType[npc_type].Basic.dHPLimit);
        SetCharacterMp(x, (UHINT)NPCType[npc_type].Basic.dMP);
		SetCharacterMaxMp(x, (UHINT)NPCType[npc_type].Basic.dMPLimit);        
        //等級
		SetCharacterLevel(x, (UHINT)NPCType[npc_type].Basic.dLevel);        
        // 相關屬性
		//SetCharacterEquipBaseAtt(x, (UHINT)NPCType[npc_type].Basic.dDemage);
        //SetCharacterBaseDefence(x, (UHINT)NPCType[npc_type].Basic.dDefence);        
		SetCharacterFinalAtt(x, (UHINT)NPCType[npc_type].Basic.dDemage);
        SetCharacterFinalDefence(x, (UHINT)NPCType[npc_type].Basic.dDefence); 		
		SetCharacterSightRange(x, (UHINT)NPCType[npc_type].Basic.dSight);		
        // 技能....假的!!!!!需要工具裡面取增加....
        SetCharacterSkillNo(x, 0, MAGIC_NO_ESCRIME);
        SetCharacterSkillLevel(x, 0, 0);
        // ....未完
    }	
	UNLOCK_ZONEMACRO(0);
}
//---------------------------------------------------------------------------
void	LoadZoneWeather()
{
	ZoneWeather->dWeatherType=WEATHER_NORMAL;
    ZoneWeather->dRainActive=WEATHER_STOP;
    ZoneWeather->dRainSize=WEATHER_SMALL;
    ZoneWeather->dSnowActive=WEATHER_STOP;
    ZoneWeather->dSnowSize=WEATHER_SMALL;
    ZoneWeather->dCloudActive=WEATHER_STOP;
    ZoneWeather->dCloudSize=WEATHER_SMALL;
    ZoneWeather->dThunderActive=WEATHER_STOP;
    ZoneWeather->dThunderSize=WEATHER_SMALL;
    ZoneWeather->dEarthQuakeActive=WEATHER_STOP;
    ZoneWeather->dEarthQuakeSize=WEATHER_SMALL;
    ZoneWeather->dWindSize=WIND_SMALL;
    ZoneWeather->dWindDir=WIND_RIGHT;	
}
//---------------------------------------------------------------------------