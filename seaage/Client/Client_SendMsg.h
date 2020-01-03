/*
**	Client_SendMsg.h 
**	Client send message functions header.
**
**	Jack, 2003.1.2
**
**  modified by Zhang Zhaohui 2003.5.31
*/
#pragma	once
#include "NetGE_MainFunc.h"
#include "NetGE.h"
#include "NetGE_Event_Def.h"
#include "NetGE_Event_Struct_Def.h"

// DEFINES //////////////////////////////////////////////////////////////////////////////////////////////////
//
#define		SEND_MSG_OK						1				//發送消息成功
//
#define     CONNECTED_SERVER_NONE           0x00000000      // 未連接任何伺服器
#define     CONNECTED_SERVER_DOOR           0x00000001      // 連接Door伺服器
#define     CONNECTED_SERVER_WORLD          0x00000002      // 連接World伺服器
#define     CONNECTED_SERVER_ZONE           0x00000004      // 連接Zone伺服器

// FUNCTIONS ////////////////////////////////////////////////////////////////////////////////////////////////
extern	int		ClientConnectionsInit(void);
extern	int		ClientConnectionsFree(void);
extern	int		ClientGetCurrentConnectedType(void);
//
extern	int		ClientLoginDoor(HWND hWnd, char* szServerName, SLONG lPort, CHAR* szID, CHAR* szPassword, DWORD dwVersion);
extern	int		ClientLogoutDoor(void);
extern	int		ClientRequestForWorldInfo(SLONG lIndex);
extern	int		ClientRequestRegisterAccountChecking(CHAR *szAccount, CHAR *szPassword);
extern	int		ClientRequestChangeAccountPassword(CHAR *szAccount, CHAR *szPassword);
extern	int		ClientRequestRegisterAccountFinal(TPOS_EVENT_REGISTERACCOUNT *lpRA);
//
extern	int		ClientLoginWorld(HWND hWnd, char* szServerName, SLONG port, CHAR *szID, CHAR* szPassword, DWORD dwVersion);
extern	int		ClientLogoutWorld(void);
extern	int		ClientRequestForCharacterInfo(CHAR *szAccount, SLONG lIndex);
extern	int		ClientRequestChooseCharacter(ULONG uQQID);
extern	int		ClientRequestLoginZone(CHAR *szZoneName);
extern	int		ClientRequestDeleteCharacter(CHAR *szMainName);
extern	int		ClientRequestForDefaultCharacterInfo(SLONG lIndex);
extern	int		ClientRequestCreateCharacterChecking(CHAR *szMainName);
extern	int		ClientRequestCreateCharacterFinal(TPOS_EVENT_CREATECHARACTERFINAL *lpCCF);
//
extern	int		ClientLoginZone(HWND hWnd, char *szServerName, int lPort, char *szMainName, DWORD dwVersion);
extern	int		ClientLogoutZone(void);
extern	int		ClientRequestForPlayerList(SLONG lIndex);
extern	int		ClientRequestGameStart(void);
extern	int		ClientRequestLeftHitMap(SLONG lX, SLONG lY);
extern	int		ClientRequestRightHitMap(SLONG lX, SLONG lY);
extern	int		ClientRequestLeftHitNpc(SLONG lDestIndex);
extern	int		ClientRequestRightHitNpc(SLONG lDestIndex);
extern	int		ClientRequestOpenBag(void);
extern	int		ClientRequestCloseBag(void);
extern	int		ClientRequestSwitchAttackState(void);
extern	int		ClientRequestAddBaseStrength(SLONG lData);
extern	int		ClientRequestAddBaseInstinct(SLONG lData);
extern	int		ClientRequestAddBaseWit(SLONG lData);
extern	int		ClientRequestAddBaseLucky(SLONG lData);
extern	int		ClientRequestSubBaseStrength(SLONG lData);
extern	int		ClientRequestSubBaseInstinct(SLONG lData);
extern	int		ClientRequestSubBaseWit(SLONG lData);
extern	int		ClientRequestSubBaseLucky(SLONG lData);
extern	int		ClientRequestLeftHitEquipHead(void);
extern	int		ClientRequestRightHitEquipHead(void);
extern	int		ClientRequestLeftHitEquipNeck(void);
extern	int		ClientRequestRightHitEquipNeck(void);
extern	int		ClientRequestLeftHitEquipBody(void);
extern	int		ClientRequestRightHitEquipBody(void);
extern	int		ClientRequestLeftHitEquipWeapon(void);
extern	int		ClientRequestRightHitEquipWeapon(void);
extern	int		ClientRequestLeftHitEquipWaist(void);
extern	int		ClientRequestRightHitEquipWaist(void);
extern	int		ClientRequestLeftHitEquipWrist(void);
extern	int		ClientRequestRightHitEquipWrist(void);
extern	int		ClientRequestLeftHitEquipGlove(void);
extern	int		ClientRequestRightHitEquipGlove(void);
extern	int		ClientRequestLeftHitEquipFeet(void);
extern	int		ClientRequestRightHitEquipFeet(void);
extern	int		ClientRequestLeftHitEquipOtherA(void);
extern	int		ClientRequestRightHitEquipOtherA(void);
extern	int		ClientRequestLeftHitEquipOtherB(void);
extern	int		ClientRequestRightHitEquipOtherB(void);
extern	int		ClientRequestLeftHitEquipOtherC(void);
extern	int		ClientRequestRightHitEquipOtherC(void);
extern  int     ClientRequestLeftHitTreasureItem( VOID );
extern  int     ClientRequestRightHitTreasureItem( VOID );
extern	int		ClientRequestLeftHitBagItem(SLONG lBagIndex);
extern	int		ClientRequestRightHitBagItem(SLONG lBagIndex);
extern	int		ClientRequestLeftHitSashItem(SLONG lSashIndex);
extern	int		ClientRequestRightHitSashItem(SLONG lSashIndex);
extern	int		ClientRequestDropItem(SLONG map_x, SLONG map_y);
extern	int		ClientRequestLeftHitMapItem(SLONG item_x, SLONG item_y);
extern	int		ClientRequestRightHitMapItem(SLONG item_x, SLONG item_y);
extern	int		ClientRequestChangeLeftHandMagic(SLONG lMagicNo);
extern	int		ClientRequestChangeRightHandMagic(SLONG lMagicNo);
extern	int		ClientRequestLeftEndHitMap(SLONG lX, SLONG lY);
extern	int		ClientRequestRightEndHitMap(SLONG lX, SLONG lY);
extern	int		ClientRequestExitGame(void);
extern	int		ClientRequestSendPublicTalk(SLONG lDoingKind, SLONG lPlayerIndex, char *szMsg);
extern	int		ClientRequestChangeWeather(SLONG lType, SLONG lActive, SLONG lSize, SLONG lWindSize, SLONG lWindDir);
extern	int		ClientRequestSetLeftHandQuickSkill(SLONG quick_index, SLONG magic_no);
extern	int		ClientRequestSetRightHandQuickSkill(SLONG quick_index, SLONG magic_no);
extern	int		ClientRequestQuickSetHandSkill(SLONG quick_index);
//
extern	int		ClientRequestQQMyData(void);
extern	int		ClientRequestQQFriendList(SLONG lIndex);
extern	int		ClientRequestQQGuildFriendList(SLONG lIndex);
extern	int		ClientRequestQQTeamFriendList(SLONG lIndex);
extern	int		ClientRequestQQSetMyState(CHAR cState);
extern	int		ClientRequestQQSetMyConfig(ULONG uSettings);
extern	int		ClientRequestQQQuerySomeone(ULONG uID);
extern	int		ClientRequestQQAddSomeone(ULONG uID, UCHAR cRelation );
extern	int		ClientRequestQQDeleteFriend(ULONG uID);
extern	int		ClientRequestQQDeleteGuildFriend(ULONG uID);
extern	int		ClientRequestQQPlayerCount(void);
extern	int		ClientRequestQQSendMessageToSomeone(ULONG uToID, CHAR* szText);
extern	int		ClientRequestQQQueryOnlineAddList( ULONG uIndex );
extern	int		ClientRequestQQHitTransItem(char r_l, UCHAR index);
extern	int		ClientRequestQQTransferItem(DWORD ID);
//
extern	int		ClientRequestNpcProc(SLONG lNpcNo, SLONG lProcNo);
extern	int		ClientRequestChangeDir(SLONG lDir);
extern	int		ClientRequestBuyItem(SLONG lStoreIndex, SLONG lIndex);
extern	int		ClientRequestSellItem(SLONG lStoreIndex);
//
//銀行相關
extern	int		ClientRequestSaveMoney( SLONG lMoney );
extern	int		ClientRequestLoadMoney( SLONG lMoney );
extern	int		ClientRequestHitBankItem( UHINT lBankIndex );
//
extern	int		ClientGodRequestFullHpMp(void);
extern	int		ClientGodRequestPropertyPoint(SLONG points);
extern	int		ClientGodRequestJumpTo(SLONG lX, SLONG lY, SLONG lZ);
extern	int		ClientGodRequestItem(UHINT uBaseID);
extern	int		ClientGodRequestMoney(ULONG uMoney);
extern	int		ClientGodRequestExp(ULONG uExp);
extern	int		ClientGodRequestMoveFast(ULONG uSpeed);
extern	int		ClientGodRequestChangeZone(CHAR *szZoneName, SLONG lX, SLONG lY, SLONG lZ);
extern	int		ClientGodRequestDead(void);
extern  int     ClientGodRequestTreasureMap( SLONG Index, SLONG PieceIndex );
//
extern	int		ClientRequestJoinTeam(CHAR *szMainName, CHAR *szZoneName );
extern	int		ClientRequestAgreeJoinTeam(CHAR *szMainName, CHAR *szZoneName );
extern	int		ClientRequestExitTeam(CHAR *szMainName );
extern	int		ClientRequestKickTeamMember(CHAR *szMainName, CHAR *szZoneName );

// 請求拆開藏寶圖
extern  int     ClientRequestSeparateMap( DWORD dwBagIndex );