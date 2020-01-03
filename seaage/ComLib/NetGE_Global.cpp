/*
**  NetGE_Global.cpp
**
**  
*/
#include "NetGE_MainFunc.h"


//GLOBALS /////////////////////////////////////////////////////////////////////////////////
CRITICAL_SECTION    g_csCharacter;		//����ƾ��{�ɰ�
CRITICAL_SECTION    g_csWeather;        //�Ѯ�ƾ��{�ɰ�
CRITICAL_SECTION    g_csConnection;     //���a�s���ƾ��{�ɰ�
CRITICAL_SECTION    g_csMapMask;        //�a��mask�ƾ��{�ɰ�
CRITICAL_SECTION    g_csSyncConnection; //���a�P�B�ƾ��{�ɰ�
CRITICAL_SECTION    g_csZoneInfo;		//�ϰ���A���P�B�ƾ��{�ɰ�
CRITICAL_SECTION    g_csNPCType;		//NPC�������c�ƾ��{�ɰ�
CRITICAL_SECTION    g_csMacro;			//MACRO�ƾ��{�ɰ�
CRITICAL_SECTION    g_csZoneMacro;		//ZONEMACRO�ƾ��{�ɰ�
CRITICAL_SECTION	g_csMagic;			//MAGIC�ƾ��{�ɰ�
CRITICAL_SECTION	g_csItem;			//ITEM�ƾ��{�ɰ�
CRITICAL_SECTION	g_csQQOnlinePlayerList;	//QQ�b�u���a�C��
CRITICAL_SECTION	g_csWorldInfo;		//World��T�ƾ��{�ɰ�
CRITICAL_SECTION	g_csGlobals;		//�����ܼ�
CRITICAL_SECTION	g_csScript;			//�}���ƾ��{�ɰ�
CRITICAL_SECTION	g_csShip;			//��ƾ��{�ɰ�
CRITICAL_SECTION	g_csTreasury;		//�_�üƾ��{�ɰ�


//FUNCTIONS ///////////////////////////////////////////////////////////////////////////////
//�\��: ��l���{�ɰϼƾ�
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



//�\��: �����{�ɰϼƾ�
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

