//===============================================================================
// Netge_Macro_Def.h
// Macro Struct Define Header File
// By Hawke Hsieh
// 2002-08-12
//===============================================================================
#ifndef HMACRO_DEF_H
#define HMACRO_DEF_H

#define	MAX_ZONE_PER_MACRO		1024
#define	MAX_MAPLINK_PER_ZONE	48
#define	MAX_QUEST_PER_NPC		10
#define	MACRO_VERSION			500
//#define	MAX_TALK_PER_NPC		50
//-----------------------------------------------------------------------------------
// 單一連接點的資料
//-----------------------------------------------------------------------------------
typedef struct
{ 
 DWORD				dDestZoneIndex;			// 連接的區域編號
 long				lDestZoneX;				// 目標城市座標
 long				lDestZoneY;                  
 long				lDestZoneZ;
 char				cDir[1];				//當前方向
 UHINT				LocalProcessID;			//本地的事件區 ID
 UHINT				RemoteProcessID;		//目的地事件區 ID
 SLONG				RemoteLineStartPointX;	//目的地線段起始點
 SLONG				RemoteLineStartPointY;	//目的地線段起始點
 SLONG				RemoteLineEndPointX;	//目的地線段終點
 SLONG				RemoteLineEndPointY;	//目的地線段終點
}TPOS_MACRO_MAPLINK_POINT;
//---------------------------------------------------------------------------
// 劇本基本結構
//---------------------------------------------------------------------------
typedef struct POS_MACRO_BASIC
{
 DWORD				dIndex;				//區域索引
 char				cName[32];			//區域名稱
 char				cMapName[32];		//區域地圖名稱 
 TPOS_MACRO_MAPLINK_POINT MapLinkPoint[MAX_MAPLINK_PER_ZONE];//地圖連接點的資料
}TPOS_MACRO_BASIC;
//---------------------------------------------------------------------------
// 對話的結構
//---------------------------------------------------------------------------
/*
typedef struct POS_MARCO_TALK
{
 DWORD             dIndex;				//對話編號
 DWORD             dCommand;			//命令
 char              cMessage[100];		//內容
 DWORD             dNextIndex;			//下一個接的編號
 DWORD             dNextCommand;		//下一個接的命令
}TPOS_MARCO_TALK;
*/
//---------------------------------------------------------------------------
// NPC 的結構
//---------------------------------------------------------------------------
typedef struct POS_MACRO_NPC
{
 DWORD				dIndex;			//NPC的編號
 char				cName[32];		//NPC名稱
 DWORD				dNPCType;		//NPC類別
 UHINT				uiKind;			//NPC的種類
 UHINT				uiGroup;		//組別編號 
 DWORD				dX;				//座標
 DWORD				dY;
 DWORD				dZ;
 DWORD				dQuest[MAX_QUEST_PER_NPC];	//身上接的任務編號
 //DWORD             dTalk[MAX_TALK_PER_NPC];	//身上對話的編號
}TPOS_MACRO_NPC;
//---------------------------------------------------------------------------
// 區域的結構
//---------------------------------------------------------------------------
typedef struct POS_MACRO_ZONE
{
 TPOS_MACRO_BASIC	Basic;					//區域基本資料
 TPOS_MACRO_NPC		NPC[MAX_NPC_PER_ZONE];	//NPC的資料
 UHINT				uiNormalProbability;
 UHINT				uiDrugProbability;
 UHINT				uiMoneyProbability;
 UHINT				uiTreasureMapProbability;
}TPOS_MACRO_ZONE;
//---------------------------------------------------------------------------
typedef struct POS_MACRO_ZONE_INDEX
{
 DWORD				dIndex;				//區域索引
 char				cName[32];			//區域名稱  
 char				cMapName[32];		//地圖名稱
 char				cCountry;           //所屬國家
 long				lBirthPointX;		//出生點
 long				lBirthPointY;				
 long				lBirthPointZ; 
 //SDOUBLE			LULongitude;		//左上經度
 //SDOUBLE			LULatitude;			//左上緯度
 //SDOUBLE			RDLongitude;		//右下經度
 //SDOUBLE			RDLatitude;			//右下緯度
 DWORD				dType;				//區域類型
}TPOS_MACRO_ZONE_INDEX;
//---------------------------------------------------------------------------
typedef struct POS_MACRO_WORLD
{ 
 char				cName[32];							//專案名稱
 DWORD				dVersion;							//版本號碼
 DWORD				dOtherZoneItemMFProbability;		//其他區域的MF機率
 DWORD				dFindGoldZoneItemMFProbability;		//尋寶地點的MF機率
 UHINT				uiNPCTypeDropItemProbability[17];	//怪物類型掉落物品的機率
 TPOS_MACRO_ZONE_INDEX	Zone[MAX_ZONE_PER_MACRO];
}TPOS_MACRO_WORLD;
//---------------------------------------------------------------------------
#endif

