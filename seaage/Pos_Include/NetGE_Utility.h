/*
**	NetGE_Utility.h 
**	utility functions header.
**
**	Jack, 2003.1.17
*/
#pragma once
#include "NetGE_Item.h"
#include "NetGE_DBFunc.h"


typedef	enum	CHAR_ITEM_INDEX
{	CII_EQUIP_HEAD		=	1,
CII_EQUIP_NECK			=	2,
CII_EQUIP_BODY			=	3,
CII_EQUIP_WAIST			=	4,
CII_EQUIP_GLOVE			=	5,
CII_EQUIP_WEAPON		=	6,
CII_EQUIP_WRIST			=	7,
CII_EQUIP_FEET			=	8,
CII_EQUIP_OTHERA		=	9,
CII_EQUIP_OTHERB		=	10,
CII_EQUIP_OTHERC		=	11,
//
CII_BAG_ITEM_00			=	12,
CII_BAG_ITEM_01			=	13,
CII_BAG_ITEM_02			=	14,
CII_BAG_ITEM_03			=	15,
CII_BAG_ITEM_04			=	16,
CII_BAG_ITEM_05			=	17,
CII_BAG_ITEM_06			=	18,
CII_BAG_ITEM_07			=	19,
CII_BAG_ITEM_08			=	20,
CII_BAG_ITEM_09			=	21,
CII_BAG_ITEM_10			=	22,
CII_BAG_ITEM_11			=	23,
CII_BAG_ITEM_12			=	24,
CII_BAG_ITEM_13			=	25,
CII_BAG_ITEM_14			=	26,
CII_BAG_ITEM_15			=	27,
CII_BAG_ITEM_16			=	28,
CII_BAG_ITEM_17			=	29,
CII_BAG_ITEM_18			=	30,
CII_BAG_ITEM_19			=	31,
CII_BAG_ITEM_20			=	32,
CII_BAG_ITEM_21			=	33,
CII_BAG_ITEM_22			=	34,
CII_BAG_ITEM_23			=	35,
CII_BAG_ITEM_24			=	36,
CII_BAG_ITEM_25			=	37,
CII_BAG_ITEM_26			=	38,
//
CII_SASH_ITEM_00		=	39,
CII_SASH_ITEM_01		=	40,
CII_SASH_ITEM_02		=	41,
CII_SASH_ITEM_03		=	42,
//
CII_TRANS_ITEM_00		=	43,
CII_TRANS_ITEM_01		=	44,
CII_TRANS_ITEM_02		=	45,
//
CII_ONMOUSE_ITEM		=	46,
CII_TREASURE_ITEM		=	47,
//
CII_BANK_ITEM_00		=	48,
CII_BANK_ITEM_01		=	49,
CII_BANK_ITEM_02		=	50,
CII_BANK_ITEM_03		=	51,
CII_BANK_ITEM_04		=	52,
CII_BANK_ITEM_05		=	53,
CII_BANK_ITEM_06		=	54,
CII_BANK_ITEM_07		=	55,
CII_BANK_ITEM_08		=	56,
CII_BANK_ITEM_09		=	57,
CII_BANK_ITEM_10		=	58,
CII_BANK_ITEM_11		=	59,
CII_BANK_ITEM_12		=	60,
CII_BANK_ITEM_13		=	61,
CII_BANK_ITEM_14		=	62,
CII_BANK_ITEM_15		=	63,
CII_BANK_ITEM_16		=	64,
CII_BANK_ITEM_17		=	65,
CII_BANK_ITEM_18		=	66,
CII_BANK_ITEM_19		=	67,
CII_BANK_ITEM_20		=	68,
CII_BANK_ITEM_21		=	69,
CII_BANK_ITEM_22		=	70,
CII_BANK_ITEM_23		=	71,
CII_BANK_ITEM_24		=	72,
CII_BANK_ITEM_25		=	73,
CII_BANK_ITEM_26		=	74,
CII_BANK_ITEM_27		=	75,
CII_BANK_ITEM_28		=	76,
CII_BANK_ITEM_29		=	77,
CII_BANK_ITEM_30		=	78,
CII_BANK_ITEM_31		=	79,
CII_BANK_ITEM_32		=	80,
CII_BANK_ITEM_33		=	81,
CII_BANK_ITEM_34		=	82,
CII_BANK_ITEM_35		=	83,
//
CII_START				=	1,
CII_END					=	83,
} CHAR_ITEM_INDEX;


extern	void	DBItem2Item(TPOS_DB_ITEM *lpDBItem, TPOS_ITEM *lpItem);
extern	void	Item2DBItem(TPOS_ITEM *lpItem, CHAR *szMainName, SLONG lIndex, TPOS_DB_ITEM *lpDBItem);
extern	SLONG	LoadCharacterItemDataByItemID(SLONG lIndex);
extern	SLONG	LoadCharacterItemDataByMainNameAndIndex(SLONG lIndex);
extern	SLONG	SaveCharacterItemDataByMainNameAndIndex(SLONG lIndex);
extern	SLONG	InitItemDBWhenCreateCharacter(CHAR *szMainName);
extern	SLONG	FindContainItemPosition(SLONG *map_x, SLONG *map_y);
extern	void	ExecCharacterPause(SLONG lIndex);
//
extern	SLONG	LoadCharacterBankData(SLONG lIndex);
extern	SLONG	SaveCharacterBankData(SLONG lIndex);
//
extern	SLONG	InitQuestDBWhenCreateCharacter(CHAR *szMainName);
extern	SLONG	LoadCharacterQuestData(SLONG lIndex);
extern	SLONG	SaveCharacterQuestData(SLONG lIndex);

