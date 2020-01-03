/*
**	NetGE_Utility.cpp 
**	utility functions.
**
**	Jack, 2003.1.17
*/
#include "NetGE_MainFunc.h"


void	DBItem2Item(TPOS_DB_ITEM *lpDBItem, TPOS_ITEM *lpItem)
{
	lpItem->ID = lpDBItem->ID;
	lpItem->BaseID = lpDBItem->BaseID;
	lpItem->Hp = lpDBItem->Hp;
	lpItem->IR.General.Attr[0] = lpDBItem->Attrib[0];
	lpItem->IR.General.Attr[1] = lpDBItem->Attrib[1];
	lpItem->IR.General.Attr[2] = lpDBItem->Attrib[2];
	lpItem->IR.General.Attr[3] = lpDBItem->Attrib[3];
	lpItem->IR.General.Attr[4] = lpDBItem->Attrib[4];
}

void	Item2DBItem(TPOS_ITEM *lpItem, CHAR *szMainName, SLONG lIndex, TPOS_DB_ITEM *lpDBItem)
{
	lpDBItem->ID = lpItem->ID;
	lpDBItem->BaseID = lpItem->BaseID;
	lpDBItem->Hp = lpItem->Hp;
	lpDBItem->Attrib[0] = lpItem->IR.General.Attr[0];
	lpDBItem->Attrib[1] = lpItem->IR.General.Attr[1];
	lpDBItem->Attrib[2] = lpItem->IR.General.Attr[2];
	lpDBItem->Attrib[3] = lpItem->IR.General.Attr[3];
	lpDBItem->Attrib[4] = lpItem->IR.General.Attr[4];
	//lpDBItem->Status = 0;
	strcpy((char *)lpDBItem->MainName, (const char *)szMainName);
	lpDBItem->Index = (UHINT)lIndex;
}


SLONG	LoadCharacterItemDataByItemID(SLONG lIndex)
{
	TPOS_ITEM	head_item, neck_item, body_item, waist_item, glove_item;
	TPOS_ITEM	weapon_item, wrist_item, feet_item;
	TPOS_ITEM	othera_item, otherb_item, otherc_item;
	TPOS_ITEM	bag_item[MAX_CHARACTER_BAG_ITEMS];
	TPOS_ITEM	sash_item[MAX_CHARACTER_SASH_ITEMS];
	TPOS_ITEM	trans_item[MAX_CHARACTER_TRANS_ITEMS];
	TPOS_ITEM	onmouse_item;
	TPOS_ITEM	treasure_item;
	TPOS_DB_ITEM	db_item;
	ULONG		item_id;
	SLONG		i;

	if(lIndex < 0 || lIndex >= MAX_CHARACTER_PER_ZONE)
		return	FALSE;

	//
	// Get character's item data.
	//
	LOCK_CHARACTER(lIndex);
	GetCharacterEquipHead(lIndex, &head_item);
	GetCharacterEquipNeck(lIndex, &neck_item);
	GetCharacterEquipBody(lIndex, &body_item);
	GetCharacterEquipWaist(lIndex, &waist_item);
	GetCharacterEquipGlove(lIndex, &glove_item);
	GetCharacterEquipWeapon(lIndex, &weapon_item);
	GetCharacterEquipWrist(lIndex, &wrist_item);
	GetCharacterEquipFeet(lIndex, &feet_item);
	GetCharacterEquipOtherA(lIndex, &othera_item);
	GetCharacterEquipOtherB(lIndex, &otherb_item);
	GetCharacterEquipOtherC(lIndex, &otherc_item);
	for(i=0; i<MAX_CHARACTER_BAG_ITEMS; i++)
	{
		GetCharacterBagItem(lIndex, i, &bag_item[i]);
	}
	for(i=0; i<MAX_CHARACTER_SASH_ITEMS; i++)
	{
		GetCharacterSashItem(lIndex, i, &sash_item[i]);
	}
	for(i=0; i<MAX_CHARACTER_TRANS_ITEMS; i++)
	{
		GetCharacterTransItem(lIndex, i, &trans_item[i]);
	}
	GetCharacterOnMouseItem(lIndex, &onmouse_item);
	GetCharacterTreasureItem(lIndex, &treasure_item);
	UNLOCK_CHARACTER(lIndex);


	//
	// Get item whole data from database by item's unique id.
	//
	item_id = GetItemID(&head_item);
	if(item_id > 0)
	{
		if(TRUE == GetRecordFromItemDBByUniqueID(&db_item, item_id))
		{
			DBItem2Item(&db_item, &head_item);
		}
	}

	item_id = GetItemID(&neck_item);
	if(item_id > 0)
	{
		if(TRUE == GetRecordFromItemDBByUniqueID(&db_item, item_id))
		{
			DBItem2Item(&db_item, &neck_item);
		}
	}

	item_id = GetItemID(&body_item);
	if(item_id > 0)
	{
		if(TRUE == GetRecordFromItemDBByUniqueID(&db_item, item_id))
		{
			DBItem2Item(&db_item, &body_item);
		}
	}

	item_id = GetItemID(&waist_item);
	if(item_id > 0)
	{
		if(TRUE == GetRecordFromItemDBByUniqueID(&db_item, item_id))
		{
			DBItem2Item(&db_item, &waist_item); 
		}
	}

	item_id = GetItemID(&glove_item);
	if(item_id > 0)
	{
		if(TRUE == GetRecordFromItemDBByUniqueID(&db_item, item_id))
		{
			DBItem2Item(&db_item, &glove_item);
		}
	}

	item_id = GetItemID(&weapon_item);
	if(item_id > 0)
	{
		if(TRUE == GetRecordFromItemDBByUniqueID(&db_item, item_id))
		{
			DBItem2Item(&db_item, &weapon_item);
		}
	}

	item_id = GetItemID(&wrist_item);
	if(item_id > 0)
	{
		if(TRUE == GetRecordFromItemDBByUniqueID(&db_item, item_id))
		{
			DBItem2Item(&db_item, &wrist_item);
		}
	}

	item_id = GetItemID(&feet_item);
	if(item_id > 0)
	{
		if(TRUE == GetRecordFromItemDBByUniqueID(&db_item, item_id))
		{
			DBItem2Item(&db_item, &feet_item);
		}
	}

	item_id = GetItemID(&othera_item);
	if(item_id > 0)
	{
		if(TRUE == GetRecordFromItemDBByUniqueID(&db_item, item_id))
		{
			DBItem2Item(&db_item, &othera_item);
		}
	}

	item_id = GetItemID(&otherb_item);
	if(item_id > 0)
	{
		if(TRUE == GetRecordFromItemDBByUniqueID(&db_item, item_id))
		{
			DBItem2Item(&db_item, &otherb_item);
		}
	}

	item_id = GetItemID(&otherc_item);
	if(item_id > 0)
	{
		if(TRUE == GetRecordFromItemDBByUniqueID(&db_item, item_id))
		{
			DBItem2Item(&db_item, &otherc_item);
		}
	}


	for(i=0; i<MAX_CHARACTER_BAG_ITEMS; i++)
	{
		item_id = GetItemID(&bag_item[i]);
		if(item_id > 0)
		{
			if(TRUE == GetRecordFromItemDBByUniqueID(&db_item, item_id))
			{
				DBItem2Item(&db_item, &bag_item[i]);
			}
		}
	}

	for(i=0; i<MAX_CHARACTER_SASH_ITEMS; i++)
	{
		item_id = GetItemID(&sash_item[i]);
		if(item_id > 0)
		{
			if(TRUE == GetRecordFromItemDBByUniqueID(&db_item, item_id))
			{
				DBItem2Item(&db_item, &sash_item[i]);
			}
		}
	}

	for(i=0; i<MAX_CHARACTER_TRANS_ITEMS; i++)
	{
		item_id = GetItemID(&trans_item[i]);
		if(item_id > 0)
		{
			if(TRUE == GetRecordFromItemDBByUniqueID(&db_item, item_id))
			{
				DBItem2Item(&db_item, &trans_item[i]);
			}
		}
	}

	item_id = GetItemID(&onmouse_item);
	if(item_id > 0)
	{
		if(TRUE == GetRecordFromItemDBByUniqueID(&db_item, item_id))
		{
			DBItem2Item(&db_item, &onmouse_item);
		}
	}

	item_id = GetItemID(&treasure_item);
	if(item_id > 0)
	{
		if(TRUE == GetRecordFromItemDBByUniqueID(&db_item, item_id))
		{
			DBItem2Item(&db_item, &treasure_item);
		}
	}

	//
	// Set back character's item data.
	//
	LOCK_CHARACTER(lIndex);
	SetCharacterEquipHead(lIndex, &head_item);
	SetCharacterEquipNeck(lIndex, &neck_item);
	SetCharacterEquipBody(lIndex, &body_item);
	SetCharacterEquipWaist(lIndex, &waist_item);
	SetCharacterEquipGlove(lIndex, &glove_item);
	SetCharacterEquipWeapon(lIndex, &weapon_item);
	SetCharacterEquipWrist(lIndex, &wrist_item);
	SetCharacterEquipFeet(lIndex, &feet_item);
	SetCharacterEquipOtherA(lIndex, &othera_item);
	SetCharacterEquipOtherB(lIndex, &otherb_item);
	SetCharacterEquipOtherC(lIndex, &otherc_item);
	for(i=0; i<MAX_CHARACTER_BAG_ITEMS; i++)
	{
		SetCharacterBagItem(lIndex, i, &bag_item[i]);
	}
	for(i=0; i<MAX_CHARACTER_SASH_ITEMS; i++)
	{
		SetCharacterSashItem(lIndex, i, &sash_item[i]);
	}
	for(i=0; i<MAX_CHARACTER_TRANS_ITEMS; i++)
	{
		SetCharacterTransItem(lIndex, i, &trans_item[i]);
	}
	SetCharacterOnMouseItem(lIndex, &onmouse_item);
	SetCharacterTreasureItem(lIndex, &treasure_item);
	UNLOCK_CHARACTER(lIndex);

	return	TRUE;
}


//
//從數據庫中載入玩家的物品資料
//
SLONG	LoadCharacterItemDataByMainNameAndIndex(SLONG lIndex)
{
	TPOS_ITEM	head_item, neck_item, body_item, waist_item, glove_item;
	TPOS_ITEM	weapon_item, wrist_item, feet_item;
	TPOS_ITEM	othera_item, otherb_item, otherc_item;
	TPOS_ITEM	bag_item[MAX_CHARACTER_BAG_ITEMS];
	TPOS_ITEM	sash_item[MAX_CHARACTER_SASH_ITEMS];
	TPOS_ITEM	trans_item[MAX_CHARACTER_TRANS_ITEMS];
	TPOS_ITEM	onmouse_item;
	TPOS_ITEM	treasure_item;
	TPOS_DB_ITEM	db_item;
	SLONG		i;
	char	mainname[32];


	if(lIndex < 0 || lIndex >= MAX_CHARACTER_PER_ZONE)
		return	FALSE;

	//
	// Get character's item data.
	//
	LOCK_CHARACTER(lIndex);
	strcpy((char *)mainname, (const char *)GetCharacterMainName(lIndex));
	UNLOCK_CHARACTER(lIndex);


	//
	// Get item whole data from database
	//
	SetItemNone(&head_item);
	if(TRUE == GetRecordFromItemDBByMainNameAndIndex(&db_item, (char *)mainname, CII_EQUIP_HEAD))
	{
		DBItem2Item(&db_item, &head_item);
	}

	SetItemNone(&neck_item);
	if(TRUE == GetRecordFromItemDBByMainNameAndIndex(&db_item, (char *)mainname, CII_EQUIP_NECK))
	{
		DBItem2Item(&db_item, &neck_item);
	}

	SetItemNone(&body_item);
	if(TRUE == GetRecordFromItemDBByMainNameAndIndex(&db_item, (char *)mainname, CII_EQUIP_BODY))
	{
		DBItem2Item(&db_item, &body_item);
	}

	SetItemNone(&waist_item);
	if(TRUE == GetRecordFromItemDBByMainNameAndIndex(&db_item, (char *)mainname, CII_EQUIP_WAIST))
	{
		DBItem2Item(&db_item, &waist_item); 
	}
	
	SetItemNone(&glove_item);
	if(TRUE == GetRecordFromItemDBByMainNameAndIndex(&db_item, (char *)mainname, CII_EQUIP_GLOVE))
	{
		DBItem2Item(&db_item, &glove_item);
	}

	SetItemNone(&weapon_item);
	if(TRUE == GetRecordFromItemDBByMainNameAndIndex(&db_item, (char *)mainname, CII_EQUIP_WEAPON))
	{
		DBItem2Item(&db_item, &weapon_item);
	}

	SetItemNone(&wrist_item);
	if(TRUE == GetRecordFromItemDBByMainNameAndIndex(&db_item, (char *)mainname, CII_EQUIP_WRIST))
	{
		DBItem2Item(&db_item, &wrist_item);
	}

	SetItemNone(&feet_item);
	if(TRUE == GetRecordFromItemDBByMainNameAndIndex(&db_item, (char *)mainname, CII_EQUIP_FEET))
	{
		DBItem2Item(&db_item, &feet_item);
	}

	SetItemNone(&othera_item);
	if(TRUE == GetRecordFromItemDBByMainNameAndIndex(&db_item, (char *)mainname, CII_EQUIP_OTHERA))
	{
		DBItem2Item(&db_item, &othera_item);
	}

	SetItemNone(&otherb_item);
	if(TRUE == GetRecordFromItemDBByMainNameAndIndex(&db_item, (char *)mainname, CII_EQUIP_OTHERB))
	{
		DBItem2Item(&db_item, &otherb_item);
	}

	SetItemNone(&otherc_item);
	if(TRUE == GetRecordFromItemDBByMainNameAndIndex(&db_item, (char *)mainname, CII_EQUIP_OTHERC))
	{
		DBItem2Item(&db_item, &otherc_item);
	}

	for(i=0; i<MAX_CHARACTER_BAG_ITEMS; i++)
	{
		SetItemNone(&bag_item[i]);
		if(TRUE == GetRecordFromItemDBByMainNameAndIndex(&db_item, (char *)mainname, CII_BAG_ITEM_00 + i))
		{
			DBItem2Item(&db_item, &bag_item[i]);
		}
	}

	for(i=0; i<MAX_CHARACTER_SASH_ITEMS; i++)
	{
		SetItemNone(&sash_item[i]);
		if(TRUE == GetRecordFromItemDBByMainNameAndIndex(&db_item, (char *)mainname, CII_SASH_ITEM_00 + i))
		{
			DBItem2Item(&db_item, &sash_item[i]);
		}
	}

	for(i=0; i<MAX_CHARACTER_TRANS_ITEMS; i++)
	{
		SetItemNone(&trans_item[i]);
		if(TRUE == GetRecordFromItemDBByMainNameAndIndex(&db_item, (char *)mainname, CII_TRANS_ITEM_00 + i))
		{
			DBItem2Item(&db_item, &trans_item[i]);
		}
	}

	SetItemNone(&onmouse_item);
	if(TRUE == GetRecordFromItemDBByMainNameAndIndex(&db_item, (char *)mainname, CII_ONMOUSE_ITEM))
	{
		DBItem2Item(&db_item, &onmouse_item);
	}

	SetItemNone(&treasure_item);
	if(TRUE == GetRecordFromItemDBByMainNameAndIndex(&db_item, (char *)mainname, CII_TREASURE_ITEM))
	{
		DBItem2Item(&db_item, &treasure_item);
	}

	//
	// Set back character's item data.
	//
	LOCK_CHARACTER(lIndex);
	SetCharacterEquipHead(lIndex, &head_item);
	SetCharacterEquipNeck(lIndex, &neck_item);
	SetCharacterEquipBody(lIndex, &body_item);
	SetCharacterEquipWaist(lIndex, &waist_item);
	SetCharacterEquipGlove(lIndex, &glove_item);
	SetCharacterEquipWeapon(lIndex, &weapon_item);
	SetCharacterEquipWrist(lIndex, &wrist_item);
	SetCharacterEquipFeet(lIndex, &feet_item);
	SetCharacterEquipOtherA(lIndex, &othera_item);
	SetCharacterEquipOtherB(lIndex, &otherb_item);
	SetCharacterEquipOtherC(lIndex, &otherc_item);
	for(i=0; i<MAX_CHARACTER_BAG_ITEMS; i++)
	{
		SetCharacterBagItem(lIndex, i, &bag_item[i]);
	}
	for(i=0; i<MAX_CHARACTER_SASH_ITEMS; i++)
	{
		SetCharacterSashItem(lIndex, i, &sash_item[i]);
	}
	for(i=0; i<MAX_CHARACTER_TRANS_ITEMS; i++)
	{
		SetCharacterTransItem(lIndex, i, &trans_item[i]);
	}
	SetCharacterOnMouseItem(lIndex, &onmouse_item);
	SetCharacterTreasureItem(lIndex, &treasure_item);
	UNLOCK_CHARACTER(lIndex);

	return	TRUE;
}


//
//存儲人物的物品資訊到數據庫
//
SLONG	SaveCharacterItemDataByMainNameAndIndex(SLONG lIndex)
{
	TPOS_ITEM	head_item, neck_item, body_item, waist_item, glove_item;
	TPOS_ITEM	weapon_item, wrist_item, feet_item;
	TPOS_ITEM	othera_item, otherb_item, otherc_item;
	TPOS_ITEM	bag_item[MAX_CHARACTER_BAG_ITEMS];
	TPOS_ITEM	sash_item[MAX_CHARACTER_SASH_ITEMS];
	TPOS_ITEM	trans_item[MAX_CHARACTER_TRANS_ITEMS];
	TPOS_ITEM	onmouse_item;
	TPOS_ITEM	treasure_item;
	TPOS_DB_ITEM	db_item;
	SLONG		i;
	CHAR		mainname[32];

	if(lIndex < 0 || lIndex >= MAX_CHARACTER_PER_ZONE)
		return	FALSE;

	//
	// Get character's item data.
	//
	LOCK_CHARACTER(lIndex);
	strcpy((char *)mainname, (const char *)GetCharacterMainName(lIndex));
	GetCharacterEquipHead(lIndex, &head_item);
	GetCharacterEquipNeck(lIndex, &neck_item);
	GetCharacterEquipBody(lIndex, &body_item);
	GetCharacterEquipWaist(lIndex, &waist_item);
	GetCharacterEquipGlove(lIndex, &glove_item);
	GetCharacterEquipWeapon(lIndex, &weapon_item);
	GetCharacterEquipWrist(lIndex, &wrist_item);
	GetCharacterEquipFeet(lIndex, &feet_item);
	GetCharacterEquipOtherA(lIndex, &othera_item);
	GetCharacterEquipOtherB(lIndex, &otherb_item);
	GetCharacterEquipOtherC(lIndex, &otherc_item);
	for(i=0; i<MAX_CHARACTER_BAG_ITEMS; i++)
	{
		GetCharacterBagItem(lIndex, i, &bag_item[i]);
	}
	for(i=0; i<MAX_CHARACTER_SASH_ITEMS; i++)
	{
		GetCharacterSashItem(lIndex, i, &sash_item[i]);
	}
	for(i=0; i<MAX_CHARACTER_TRANS_ITEMS; i++)
	{
		GetCharacterTransItem(lIndex, i, &trans_item[i]);
	}
	GetCharacterOnMouseItem(lIndex, &onmouse_item);
	GetCharacterTreasureItem(lIndex, &treasure_item);
	UNLOCK_CHARACTER(lIndex);


	//
	// Get item whole data from database by item's unique id.
	//
	Item2DBItem(&head_item, (char *)mainname, CII_EQUIP_HEAD, &db_item);
	UpdateRecordOfItemDBByMainNameAndIndex(&db_item);

	Item2DBItem(&neck_item, (char *)mainname, CII_EQUIP_NECK, &db_item);
	UpdateRecordOfItemDBByMainNameAndIndex(&db_item);

	Item2DBItem(&body_item, (char *)mainname, CII_EQUIP_BODY, &db_item);
	UpdateRecordOfItemDBByMainNameAndIndex(&db_item);

	Item2DBItem(&waist_item, (char *)mainname, CII_EQUIP_WAIST, &db_item);
	UpdateRecordOfItemDBByMainNameAndIndex(&db_item);

	Item2DBItem(&glove_item, (char *)mainname, CII_EQUIP_GLOVE, &db_item);
	UpdateRecordOfItemDBByMainNameAndIndex(&db_item);

	Item2DBItem(&weapon_item, (char *)mainname, CII_EQUIP_WEAPON, &db_item);
	UpdateRecordOfItemDBByMainNameAndIndex(&db_item);

	Item2DBItem(&wrist_item, (char *)mainname, CII_EQUIP_WRIST, &db_item);
	UpdateRecordOfItemDBByMainNameAndIndex(&db_item);

	Item2DBItem(&feet_item, (char *)mainname, CII_EQUIP_FEET, &db_item);
	UpdateRecordOfItemDBByMainNameAndIndex(&db_item);

	Item2DBItem(&othera_item, (char *)mainname, CII_EQUIP_OTHERA, &db_item);
	UpdateRecordOfItemDBByMainNameAndIndex(&db_item);

	Item2DBItem(&otherb_item, (char *)mainname, CII_EQUIP_OTHERB, &db_item);
	UpdateRecordOfItemDBByMainNameAndIndex(&db_item);

	Item2DBItem(&otherc_item, (char *)mainname, CII_EQUIP_OTHERC, &db_item);
	UpdateRecordOfItemDBByMainNameAndIndex(&db_item);

	for(i=0; i<MAX_CHARACTER_BAG_ITEMS; i++)
	{
		Item2DBItem(&bag_item[i], (char *)mainname, CII_BAG_ITEM_00 + i, &db_item);
		UpdateRecordOfItemDBByMainNameAndIndex(&db_item);
	}

	for(i=0; i<MAX_CHARACTER_SASH_ITEMS; i++)
	{
		Item2DBItem(&sash_item[i], (char *)mainname, CII_SASH_ITEM_00 + i, &db_item);
		UpdateRecordOfItemDBByMainNameAndIndex(&db_item);
	}

	for(i=0; i<MAX_CHARACTER_TRANS_ITEMS; i++)
	{
		Item2DBItem(&trans_item[i], (char *)mainname, CII_TRANS_ITEM_00 + i, &db_item);
		UpdateRecordOfItemDBByMainNameAndIndex(&db_item);
	}

	Item2DBItem(&onmouse_item, (char *)mainname, CII_ONMOUSE_ITEM, &db_item);
	UpdateRecordOfItemDBByMainNameAndIndex(&db_item);

	Item2DBItem(&treasure_item, (char *)mainname, CII_TREASURE_ITEM, &db_item);
	UpdateRecordOfItemDBByMainNameAndIndex(&db_item);

	return	TRUE;
}

//
//當創建人物資料時，同時在物品資料庫中建立該人物的物品資訊
//
SLONG	InitItemDBWhenCreateCharacter(CHAR *szMainName)
{
	TPOS_DB_ITEM	db_item;
	SLONG	i, result;

	result = TRUE;
	memset(&db_item, 0, sizeof(db_item));
	strcpy((char *)db_item.MainName, szMainName);
	for(i = CII_START; i <= CII_END; i++)
	{
		db_item.Index = (UHINT)i;
		if(TRUE != AppendRecordToItemDB(&db_item))
		{
			result = FALSE;
			break;
		}
	}
	return	result;
}


//
//尋找可以放置物品的地圖座標
//
SLONG	FindContainItemPosition(SLONG *map_x, SLONG *map_y)
{
	enum	{ DROP_POINTS = 999 };
    SLONG   item_cx, item_cy, nx, ny, ix, iy;
    SLONG   item_x, item_y;
    SLONG   found, i, result;
	SLONG	catch_index;
	TPOS_ITEM	catch_item;

    item_cx = *map_x;
    item_cy = *map_y;
    TrimZoneItemPosition( &item_cx, &item_cy);

    found = FALSE;
	for(i=0; i < DROP_POINTS; i++)
	{
		WindingItemAxisPosition(i, &nx, &ny);
		ix = nx - ny;
		iy = nx + ny;
		item_x = item_cx + ITEM_STAY_WIDTH / 2 * ix;
		item_y = item_cy + ITEM_STAY_HEIGHT / 2 * iy;

		LOCK_ITEM(0);
		catch_index = CatchZoneItem(item_x, item_y, &catch_item);
		UNLOCK_ITEM(0);
		if(catch_index < 0)	//如果原來沒有物品
        {
			//檢查是否有阻擋, 只有在沒有阻擋的地方才可以放置物品
			LOCK_MAPMASK(0);
			result = IsPixelMaskStop(item_x, item_y);
			UNLOCK_MAPMASK(0);
            if(TRUE != result )
            {
                found = TRUE;
                break;
            }
        }
	}
	if(TRUE == found)
	{
        *map_x = item_x;
        *map_y = item_y;
        return TTN_OK;
	}
	else
	{
		return	TTN_NOT_OK;
	}
}


void	ExecCharacterPause(SLONG lIndex)
{
    SLONG   file_index, action_block;
    SLONG   new_action, new_id, id;
    SLONG   is_fight, is_block;

    LOCK_CHARACTER(lIndex);
	is_fight = IsCharacterOnFightState(lIndex);
	is_block = IsCharacterOnBlockState(lIndex);
	//new_action = GetIdleAction(is_fight);
	new_action = AC_WAIT_0;
	file_index = GetCharacterFileIndex(lIndex);
	id = GetCharacterImageID(lIndex);
	action_block = StatuseToActionBlocks(is_fight, is_block);
	new_id = GetCharacterFileActionImageID(file_index, action_block, new_action);
	if(id != new_id)
	{
		SetCharacterImageID(lIndex, new_id);
		DirHeadCharacterFrame(lIndex);
	}
	else
	{
		DirFastLoopCharacterFrame(lIndex);
	}
    UNLOCK_CHARACTER(lIndex);
}

//
//載入玩家存放在銀行的物品和金錢
//
SLONG	LoadCharacterBankData(SLONG lIndex)
{
	TPOS_ITEM	bank_item[MAX_CHARACTER_BANK_ITEMS];
	TPOS_DB_ITEM	db_item;
	TPOS_DB_BANK	db_bank;
	CHAR	mainname[32];
	SLONG	i, result;


	if(lIndex < 0 || lIndex >= MAX_CHARACTER_PER_ZONE)
		return	FALSE;

	LOCK_CHARACTER(lIndex);
	strcpy((char *)mainname, (const char *)GetCharacterMainName(lIndex));
	UNLOCK_CHARACTER(lIndex);

	//
	// Load character's bank data from bank db.
	//
	memset(&db_bank, 0, sizeof(db_bank));
	result = GetRecordFromBankDB(&db_bank, mainname);
	if(TRUE != result)
		return	FALSE;

	//
	// Get item whole data from item db.
	//
	for(i=0; i<MAX_CHARACTER_BANK_ITEMS; i++)
	{
		SetItemNone(&bank_item[i]);
		if(TRUE == GetRecordFromItemDBByMainNameAndIndex(&db_item, (char *)mainname, CII_BANK_ITEM_00 + i))
		{
			DBItem2Item(&db_item, &bank_item[i]);
		}
	}

	//
	// Set back character's bank item & gold data.
	//
	LOCK_CHARACTER(lIndex);
	for(i=0; i<MAX_CHARACTER_BANK_ITEMS; i++)
	{
		SetCharacterBankItem(lIndex, i, &bank_item[i]);
	}
	SetCharacterBankMoney(lIndex, db_bank.Money);
	UNLOCK_CHARACTER(lIndex);

	return	TRUE;
}


//
//儲存玩家的銀行物品和金錢
//
SLONG	SaveCharacterBankData(SLONG lIndex)
{
	TPOS_ITEM	bank_item[MAX_CHARACTER_BANK_ITEMS];
	TPOS_DB_ITEM	db_item;
	TPOS_DB_BANK	db_bank;
	CHAR	mainname[32];
	SLONG	i, result;


	if(lIndex < 0 || lIndex >= MAX_CHARACTER_PER_ZONE)
		return	FALSE;

	LOCK_CHARACTER(lIndex);
	memset(&db_bank, 0, sizeof(db_bank));
	strcpy(db_bank.MainName, (const char *)GetCharacterMainName(lIndex));
	strcpy(mainname, db_bank.MainName);
	db_bank.Money = GetCharacterBankMoney(lIndex);
	for(i=0; i<MAX_CHARACTER_BANK_ITEMS; i++)
	{
		GetCharacterBankItem(lIndex, i, &bank_item[i]);
	}
	UNLOCK_CHARACTER(lIndex);

	result = UpdateRecordOfBankDB(&db_bank);
	if(TRUE != result)
		return	FALSE;

	for(i=0; i<MAX_CHARACTER_BANK_ITEMS; i++)
	{
		Item2DBItem(&bank_item[i], (char *)mainname, CII_BANK_ITEM_00 + i, &db_item);
		UpdateRecordOfItemDBByMainNameAndIndex(&db_item);
	}

	return	TRUE;
}


/************************************************************************************************************/
/* CHARACTER QUEST FUNCTIONS                                                                                */
/************************************************************************************************************/
SLONG	InitQuestDBWhenCreateCharacter(CHAR *szMainName)
{
	TPOS_DB_QUEST	db_quest;
	SLONG	i, result;

	result = TRUE;
	memset(&db_quest, 0, sizeof(db_quest));
	strcpy((char *)db_quest.MainName, szMainName);
	for(i = 0; i < MAX_CHARACTER_QUESTS; i++)
	{
		db_quest.Index = (UHINT)(i+1);	//db start from 1
		if(TRUE != AppendRecordToQuestDB(&db_quest))
		{
			result = FALSE;
			break;
		}
	}
	return	result;
}

SLONG	LoadCharacterQuestData(SLONG lIndex)
{
	TPOS_DB_QUEST	db_quest;
	TPOS_QUEST_INFO	quest_info[MAX_CHARACTER_QUESTS];
	char	mainname[32];
	SLONG	i;


	if(lIndex < 0 || lIndex >= MAX_CHARACTER_PER_ZONE)
		return	FALSE;

	LOCK_CHARACTER(lIndex);
	strcpy((char *)mainname, (const char *)GetCharacterMainName(lIndex));
	UNLOCK_CHARACTER(lIndex);

	memset(quest_info, 0, sizeof(quest_info));
	for(i=0; i<MAX_CHARACTER_QUESTS; i++)
	{
		memset(&db_quest, 0, sizeof(db_quest));

		//db start from 1
		if(TRUE == GetRecordFromQuestDBByMainNameAndIndex(&db_quest, (char *)mainname, i+1))
		{
			quest_info[i] = db_quest.Info;
		}
	}

	LOCK_CHARACTER(lIndex);
	for(i=0; i<MAX_CHARACTER_QUESTS; i++)
	{
		SetCharacterQuestInfo(lIndex, i, &quest_info[i]);
	}
	UNLOCK_CHARACTER(lIndex);

	return	TRUE;
}


SLONG	SaveCharacterQuestData(SLONG lIndex)
{
	TPOS_DB_QUEST	db_quest;
	TPOS_QUEST_INFO	quest_info[MAX_CHARACTER_QUESTS];
	char	mainname[32];
	SLONG	i;


	if(lIndex < 0 || lIndex >= MAX_CHARACTER_PER_ZONE)
		return	FALSE;

	LOCK_CHARACTER(lIndex);
	strcpy((char *)mainname, (const char *)GetCharacterMainName(lIndex));
	for(i=0; i<MAX_CHARACTER_QUESTS; i++)
	{
		GetCharacterQuestInfo(lIndex, i, &quest_info[i]);
	}
	UNLOCK_CHARACTER(lIndex);

	memset(&db_quest, 0, sizeof(db_quest));
	strcpy(db_quest.MainName, (const char *)mainname);
	for(i=0; i<MAX_CHARACTER_QUESTS; i++)
	{
		db_quest.Index = (UHINT)(i+1);	//db start from 1
		UpdateRecordOfQuestDBByMainNameAndIndex(&db_quest);
	}

	return	TRUE;
}
