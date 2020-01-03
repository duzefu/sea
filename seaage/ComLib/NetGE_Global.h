/*
**    GLOBAL.H
**    global variables.
*/
#pragma once


//DEFINES ////////////////////////////////////////////////////////////////////////////////////

//#define LOCK_CHARACTER(a)			EnterCriticalSection(&g_csCharacter)
//                                    log_error(1, __FILE__);\
//                                    log_error(1, __LINE__);
#define LOCK_CHARACTER(a)			EnterCriticalSection(&g_csCharacter)
#define UNLOCK_CHARACTER(a)			LeaveCriticalSection(&g_csCharacter)

#define LOCK_WEATHER(a)             EnterCriticalSection(&g_csWeather)
#define UNLOCK_WEATHER(a)           LeaveCriticalSection(&g_csWeather)

#define LOCK_CONNECTION(a)          EnterCriticalSection(&g_csConnection)
#define UNLOCK_CONNECTION(a)        LeaveCriticalSection(&g_csConnection)

#define LOCK_MAPMASK(a)             EnterCriticalSection(&g_csMapMask)
#define UNLOCK_MAPMASK(a)           LeaveCriticalSection(&g_csMapMask)

#define LOCK_SYNCCONNECTION(a)      EnterCriticalSection(&g_csSyncConnection)
#define UNLOCK_SYNCCONNECTION(a)    LeaveCriticalSection(&g_csSyncConnection)

#define LOCK_ZONEINFO(a)			EnterCriticalSection(&g_csZoneInfo)
#define UNLOCK_ZONEINFO(a)			LeaveCriticalSection(&g_csZoneInfo)

#define LOCK_MACRO(a)				EnterCriticalSection(&g_csMacro)
#define UNLOCK_MACRO(a)				LeaveCriticalSection(&g_csMacro)

#define LOCK_ZONEMACRO(a)			EnterCriticalSection(&g_csZoneMacro)
#define UNLOCK_ZONEMACRO(a)			LeaveCriticalSection(&g_csZoneMacro)

#define LOCK_NPCTYPE(a)				EnterCriticalSection(&g_csNPCType)
#define UNLOCK_NPCTYPE(a)			LeaveCriticalSection(&g_csNPCType)

#define	LOCK_MAGIC(a)				EnterCriticalSection(&g_csMagic)
#define	UNLOCK_MAGIC(a)				LeaveCriticalSection(&g_csMagic)

#define	LOCK_ITEM(a)				EnterCriticalSection(&g_csItem)
#define	UNLOCK_ITEM(a)				LeaveCriticalSection(&g_csItem)

#define LOCK_QQONLINEPLAYERLIST(a)     EnterCriticalSection(&g_csQQOnlinePlayerList)
#define UNLOCK_QQONLINEPLAYERLIST(a)   LeaveCriticalSection(&g_csQQOnlinePlayerList)

#define LOCK_WORLDINFO(a)           EnterCriticalSection(&g_csWorldInfo)
#define UNLOCK_WORLDINFO(a)         LeaveCriticalSection(&g_csWorldInfo)

#define	LOCK_GLOBALS(a)				EnterCriticalSection(&g_csGlobals)
#define	UNLOCK_GLOBALS(a)			LeaveCriticalSection(&g_csGlobals)

#define	LOCK_SCRIPT(a)				EnterCriticalSection(&g_csScript)
#define	UNLOCK_SCRIPT(a)			LeaveCriticalSection(&g_csScript)

#define	LOCK_SHIP(a)				EnterCriticalSection(&g_csShip)
#define	UNLOCK_SHIP(a)				LeaveCriticalSection(&g_csShip)

#define	LOCK_TREASURY(a)			EnterCriticalSection(&g_csTreasury)
#define	UNLOCK_TREASURY(a)			LeaveCriticalSection(&g_csTreasury)

//GLOBALS ////////////////////////////////////////////////////////////////////////////////////
extern  CRITICAL_SECTION    g_csCharacter;		//����ƾ��{�ɰ�
extern  CRITICAL_SECTION    g_csWeather;        //�Ѯ�ƾ��{�ɰ�
extern  CRITICAL_SECTION    g_csConnection;     //���a�s���ƾ��{�ɰ�
extern  CRITICAL_SECTION    g_csMapMask;        //�a��mask�ƾ��{�ɰ�
extern  CRITICAL_SECTION    g_csSyncConnection; //���a�P�B�ƾ��{�ɰ�
extern  CRITICAL_SECTION    g_csZoneInfo;		//�ϰ���A���P�B�ƾ��{�ɰ�
extern  CRITICAL_SECTION    g_csNPCType;		//NPC�������c�P�B�ƾ��{�ɰ�
extern  CRITICAL_SECTION    g_csMacro;			//MACRO�P�B�ƾ��{�ɰ�
extern  CRITICAL_SECTION    g_csZoneMacro;		//ZONEMACRO�P�B�ƾ��{�ɰ�
extern  CRITICAL_SECTION    g_csMagic;			//MAGIC�P�B�ƾ��{�ɰ�
extern  CRITICAL_SECTION    g_csItem;			//ITEM�P�B�ƾ��{�ɰ�
extern	CRITICAL_SECTION	g_csQQOnlinePlayerList;	//QQ�b�u���a�C��
extern	CRITICAL_SECTION	g_csWorldInfo;		//World��T�ƾ��{�ɰ�
extern	CRITICAL_SECTION	g_csGlobals;		//�����ܼ�
extern	CRITICAL_SECTION	g_csScript;			//�}���ƾ��{�ɰ�
extern	CRITICAL_SECTION	g_csShip;			//��ƾ��{�ɰ�
extern	CRITICAL_SECTION	g_csTreasury;		//�_�üƾ��{�ɰ�

//FUNCTIONS //////////////////////////////////////////////////////////////////////////////////
int     InitCriticalSectionGlobals(void);
void    FreeCriticalSectionGlobals(void);


