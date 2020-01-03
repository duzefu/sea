/*
**  NetGE_Global.cpp
**
**  
*/
#include "NetGE_MainFunc.h"


//GLOBALS /////////////////////////////////////////////////////////////////////////////////
CRITICAL_SECTION    g_csCharacter;		//角色數據臨界區
CRITICAL_SECTION    g_csWeather;        //天氣數據臨界區
CRITICAL_SECTION    g_csConnection;     //玩家連接數據臨界區
CRITICAL_SECTION    g_csMapMask;        //地圖mask數據臨界區
CRITICAL_SECTION    g_csSyncConnection; //玩家同步數據臨界區
CRITICAL_SECTION    g_csZoneInfo;		//區域伺服器同步數據臨界區
CRITICAL_SECTION    g_csNPCType;		//NPC類型結構數據臨界區
CRITICAL_SECTION    g_csMacro;			//MACRO數據臨界區
CRITICAL_SECTION    g_csZoneMacro;		//ZONEMACRO數據臨界區
CRITICAL_SECTION	g_csMagic;			//MAGIC數據臨界區
CRITICAL_SECTION	g_csItem;			//ITEM數據臨界區
CRITICAL_SECTION	g_csQQOnlinePlayerList;	//QQ在線玩家列表
CRITICAL_SECTION	g_csWorldInfo;		//World資訊數據臨界區
CRITICAL_SECTION	g_csGlobals;		//全局變數
CRITICAL_SECTION	g_csScript;			//腳本數據臨界區
CRITICAL_SECTION	g_csShip;			//船隻數據臨界區
CRITICAL_SECTION	g_csTreasury;		//寶藏數據臨界區


//FUNCTIONS ///////////////////////////////////////////////////////////////////////////////
//功能: 初始化臨界區數據
int     InitCriticalSectionGlobals(void)
{
    InitializeCriticalSection(&g_csCharacter);
    InitializeCriticalSection(&g_csWeather);
    InitializeCriticalSection(&g_csConnection);
    InitializeCriticalSection(&g_csMapMask);
    InitializeCriticalSection(&g_csSyncConnection);
	InitializeCriticalSection(&g_csZoneInfo);
	InitializeCriticalSection(&g_csNPCType);
	InitializeCriticalSection(&g_csMacro);
	InitializeCriticalSection(&g_csZoneMacro);
	InitializeCriticalSection(&g_csMagic);
	InitializeCriticalSection(&g_csItem);
	InitializeCriticalSection(&g_csQQOnlinePlayerList);
	InitializeCriticalSection(&g_csWorldInfo);
	InitializeCriticalSection(&g_csGlobals);
	InitializeCriticalSection(&g_csScript);
	InitializeCriticalSection(&g_csShip);
	InitializeCriticalSection(&g_csTreasury);

    return  0;
}



//功能: 釋放臨界區數據
void    FreeCriticalSectionGlobals(void)
{
	DeleteCriticalSection(&g_csShip);
	DeleteCriticalSection(&g_csScript);
	DeleteCriticalSection(&g_csGlobals);
	DeleteCriticalSection(&g_csWorldInfo);
	DeleteCriticalSection(&g_csQQOnlinePlayerList);
	DeleteCriticalSection(&g_csItem);
	DeleteCriticalSection(&g_csMagic);
	DeleteCriticalSection(&g_csMacro);
	DeleteCriticalSection(&g_csZoneMacro);
	DeleteCriticalSection(&g_csNPCType);
	DeleteCriticalSection(&g_csZoneInfo);
    DeleteCriticalSection(&g_csSyncConnection);
    DeleteCriticalSection(&g_csMapMask);
    DeleteCriticalSection(&g_csConnection);
    DeleteCriticalSection(&g_csWeather);
    DeleteCriticalSection(&g_csCharacter);
	DeleteCriticalSection(&g_csTreasury);
}

