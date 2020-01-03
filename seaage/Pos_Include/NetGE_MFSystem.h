/*
**	NetGE_MFSystem.h 
**	MF system functions header.
**
**	Hawke,	2003.03.24.
*/
#pragma once

#define	ITEM_MF_LEVEL_NONE		0	// 普通物品不帶屬性
#define	ITEM_MF_LEVEL_ONE		1	// 一種附加屬性
#define	ITEM_MF_LEVEL_TWO		2	// 二種附加屬性
#define	ITEM_MF_LEVEL_THREE		3	// 三種附加屬性
#define	ITEM_MF_LEVEL_FOUR		4	// 四種附加屬性
#define	ITEM_MF_LEVEL_CRYSTAL	5	// 紫晶物品
#define	ITEM_MF_LEVEL_GOD		6	// 神器
// ---------------------------------------------------------------------------
// Zone Map Type
// ---------------------------------------------------------------------------
#define		CITY_NORMAL						10
#define		CITY_NEWBIE						11
#define		CITY_PK							12
#define		CITY_FINDGOLD					13
#define		CITY_BIRTH						14
#define		FIELD_NORMAL					20
#define		FIELD_NEWBIE					21
#define		FIELD_PK						22
#define		FIELD_FINDGOLD					23
#define		FIELD_BIRTH						24
#define		SAIL_NORMAL						30
#define		SAIL_NEWBIE						31
#define		SAIL_PK							32
#define		SAIL_FINDGOLD					33
#define		SAIL_BIRTH						34
// ---------------------------------------------------------------------------
typedef	struct POS_ITEM_MF
{	
	SLONG PlayerIndex;
	SLONG DestNpc;
	DWORD CurrentZoneType;
	DWORD MonsterType;
	UHINT MonsterLevel;
	UHINT NormalProbability;
	UHINT DrugProbability;
	UHINT MoneyProbability;
	UHINT TreasureMapProbability;
	DWORD OtherZoneItemMFProbability;
	DWORD FindGoldZoneItemMFProbability;
	UHINT NPCTypeDropItemProbability[17];
}TPOS_ITEM_MF;

// ---------------------------------------------------------------------------
extern	SLONG MakeItem(TPOS_ITEM *Item, TPOS_ITEM_MF ItemMf);

