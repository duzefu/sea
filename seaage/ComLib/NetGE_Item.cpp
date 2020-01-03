/*
**	NetGE_Item.cpp
**	Item functions.
**
**	Jack, 2002.12.3
**  
**  Modify by Hawke 2003.04.02
**
**	Jack, 2003.5.8.
**		-- Add item-quest associated functions.
**		-- Modified item check functions which effected by item-quest.
**
**	Hawke, 2003.5.21.
**		-- Add drug item functions.
**		-- Add tressuremap item functions.
*/
#include "NetGE_Mainfunc.h"


/************************************************************************************************************/
/* 全局變量                                                                                                 */
/************************************************************************************************************/
TPOS_ITEM_BS		GameItemBase[MAX_GAME_ITEM_BASES];	//遊戲物品基本資料列表
TPOS_ITEM_RANDOM_BS	GameItemRandomBase;				    //遊戲物品隨機附加屬性基本資料列表
TPOS_ITEM_GS		ZoneItemGS[MAX_GAME_ITEMS];			//遊戲中最多物品數目


/************************************************************************************************************/
/* 物品基本數值函數                                                                                         */
/************************************************************************************************************/
SLONG	InitItemSystem(void)
{
	SLONG	result;

	//
	//初始化遊戲物品基本表
	//
	InitGameItemBase();
	result = LoadGameItemBase("data\\itembase.ini");
	if(0 != result)
		return	-1;
	//DebugLogGameItemBase();

	//
	//初始化遊戲物品隨機附加屬性基本表
	//
	InitGameItemRandomBase();
	result = LoadGameItemRandomBase("data\\item_random.ini");
	if(0 != result)
		return	-1;
	//
	//初始化遊戲區域地圖上的物品
	//
	InitZoneItem();

	return	0;
}


void	FreeItemSystem(void)
{
}


//
//功能: 初始化遊戲物品基本數值資料
void	InitGameItemBase(void)
{
	memset(&GameItemBase[0], 0, sizeof(GameItemBase));
}


//
//功能: 從文件中載入遊戲物品基本數值資料
SLONG	LoadGameItemBase(char *FileName)
{
    enum {LINE_BUFFER_SIZE = 1024};
    USTR    *file_buf;
    SLONG   file_size, pass, result, buffer_index;
    USTR    line[LINE_BUFFER_SIZE];
    SLONG   index, data_index, len;
	TPOS_ITEM_BS	*data = NULL;

    file_size = load_file_to_buffer((USTR*)FileName, &file_buf);
    if(file_size < 0)
        goto error;

	//total_item_bases = 0;
    pass = 0;
    buffer_index = 0;
    result = get_buffer_line((char*)file_buf, &buffer_index, file_size, (char*)line, LINE_BUFFER_SIZE);
    while((result == TTN_OK) && (pass == 0))
    {
        len = ( SLONG )strlen( ( const char* )line );
        if( ( line[0] != 0x00 ) && ( line[0] != ';' ) )
        {
            index = 0;

			data_index = get_buffer_number(line, &index);
			if(data_index >= 0 && data_index < MAX_GAME_ITEM_BASES)
			{
				data = &GameItemBase[data_index];

				//編號: 第一欄為 BaseID, 同時作為列表的索引.
				data->BaseID = (UHINT)data_index;

				//載入公用定義部分的數據
				//圖標編號
				data->IconIndex = (SLONG)get_buffer_number(line, &index);
				//名稱
				strcpy((char *)data->Name, (const char*)get_buffer_string(line, &index));
				//物品類型
				data->Type = (SLONG)get_buffer_number(line, &index);
				//TC等級
				data->TcLevel = get_buffer_number(line, &index);
				//善惡需求
				data->NeedGoodEvil = get_buffer_number(line, &index);
				//使用人
				data->User = (ULONG)get_buffer_number(line, &index);
				//適用部位
				data->Part = (ULONG)get_buffer_number(line, &index);
				//特殊屬性
				data->Special = (ULONG)get_buffer_number(line, &index);
				//TODO:
				//對應紫晶裝備BaseID
				//data->CrystalID = (UHINT)get_buffer_number(line, &index);
				//對應神器裝備BaseID
				//data->ArtifactsID = (UHINT)get_buffer_number(line, &index);
				//附加隨機屬性(適用於紫晶裝備,神器裝備)
				//data->AddedAttrib = (UHINT)get_buffer_number(line, &index);

				switch(data->Type)
				{
				case ITEM_TYPE_GENERAL:
					break;

				case ITEM_TYPE_LAND_NORMAL:	//陸地物品
					//力量需求
					data->Land.MinNeedStr = (SLONG)get_buffer_number(line, &index);
					//直覺需求
					data->Land.MinNeedIns = (SLONG)get_buffer_number(line, &index);
					//智力需求
					data->Land.MinNeedWit = (SLONG)get_buffer_number(line, &index);
					//運氣需求
					data->Land.MinNeedLuck = (SLONG)get_buffer_number(line, &index);
					//命中率
					data->Land.HitChance = (SLONG)get_buffer_number(line, &index);
					//膛爆率
					data->Land.ExplodeRate = (SLONG)get_buffer_number(line, &index);
					//基本傷害
					data->Land.BaseAtt = (SLONG)get_buffer_number(line, &index);
					//基本防御力
					data->Land.BaseDef = (SLONG)get_buffer_number(line, &index);
					//恢复HP%
					data->Land.ResHpRate = (SLONG)get_buffer_number(line, &index);
					//恢复MP%
					data->Land.ResMpRate = (SLONG)get_buffer_number(line, &index);
					break;

				case ITEM_TYPE_SEA_NORMAL:	//海洋物品
					//船隻等級需求(小, 中, 大, 巨)
					data->Sea.NeedShipSize = (SLONG)get_buffer_number(line, &index);
					//炮擊力(0~255)
					data->Sea.CannonAttack = (SLONG)get_buffer_number(line, &index);
					//撞角傷害力(0~255)
					data->Sea.EmbolonAttack = (SLONG)get_buffer_number(line, &index);
					//裝甲值(0~255)
					data->Sea.Armor = (SLONG)get_buffer_number(line, &index);
					//命中率(0~255)
					data->Sea.HitChance = (SLONG)get_buffer_number(line, &index);
					//移動速度(慢, 中, 快)
					data->Sea.MoveSpeed = (SLONG)get_buffer_number(line, &index);
					//轉向力(慢, 中, 快)
					data->Sea.TurnSpeed = (SLONG)get_buffer_number(line, &index);
					//耗彈量
					data->Sea.FireCost = (SLONG)get_buffer_number(line, &index);
					break;

				case ITEM_TYPE_TREASURE_MAP:	//藏寶圖					
					break;

				case ITEM_TYPE_SEA_EXPENDABLE:	//海洋消耗品
					break;

				case ITEM_TYPE_SEA_SAILOR:	//海洋水手
					break;

				case ITEM_TYPE_MONEY:	//金錢
					break;

				case ITEM_TYPE_MONSTER:	//寶箱怪
					break;

				case ITEM_TYPE_DRUG:	//藥品
					//增加力量(+/-)
					data->Drug.AddStr = (SLONG)get_buffer_number(line, &index);
					//增加直覺(+/-)
					data->Drug.AddIns = (SLONG)get_buffer_number(line, &index);
					//增加智慧(+/-)
					data->Drug.AddWit = (SLONG)get_buffer_number(line, &index);
					//增加運氣(+/-)
					data->Drug.AddLuck = (SLONG)get_buffer_number(line, &index);
					//HP回復率
					data->Drug.ResHpRate = (SLONG)get_buffer_number(line, &index);
					//MP回復率
					data->Drug.ResMpRate = (SLONG)get_buffer_number(line, &index);
					break;
				}
			}
        }
        result = get_buffer_line((char*)file_buf, &buffer_index, file_size, (char*)line, LINE_BUFFER_SIZE);
    }
    
    if(file_buf) free(file_buf);
    return 0;

error:
    return -1;
}


//
//功能: (測試)LOG基本物品列表
void	DebugLogGameItemBase(void)
{
#ifdef	_DEBUG
	TPOS_ITEM_BS	*data = NULL;
	char	info[1024];
	SLONG	i;

	log_error(1, ";Debug log game item base");
	for(i=0; i<MAX_GAME_ITEM_BASES; i++)
	{
		data = &GameItemBase[i];
		if(data->BaseID)
		{
			sprintf((char *)info, "%-8d%-8d%-24s%-8d%-8d"\
				"0x%08x      0x%08x    "\
				"%-8d%-8d%-8d%-8d"\
				"%-8d%-8d%-8d%-8d",
				data->BaseID, 
				data->IconIndex, 
				data->Name, 
				data->TcLevel, 
				data->NeedGoodEvil,
				data->User, 
				data->Special,
				//
				data->Land.MinNeedStr,
				data->Land.MinNeedIns, 
				data->Land.MinNeedWit, 
				data->Land.MinNeedLuck,
				data->Land.HitChance, 
				data->Land.ExplodeRate, 
				data->Land.BaseAtt, 
				data->Land.BaseDef,
				data->Land.ResHpRate,
				data->Land.ResMpRate
				);
			log_error(1, info);
		}
	}
#endif//_DEBUG
}


//
//功能: 釋放遊戲物品基本數值資料
void	FreeGameItemBase(void)
{
	//Do nothing here.
}

//
//功能: 初始化遊戲物品隨機附加屬性數值資料
void	InitGameItemRandomBase(void)
{
	memset(&GameItemRandomBase, 0x0, sizeof(TPOS_ITEM_RANDOM_BS));
}

//
//功能: 從文件中載入遊戲物品隨機附加屬性基本數值資料
SLONG	LoadGameItemRandomBase(char *FileName)
{
    enum {LINE_BUFFER_SIZE = 1024};
    USTR    *file_buf;
    SLONG   file_size, pass, result, buffer_index;
    USTR    line[LINE_BUFFER_SIZE];
    SLONG   index, len;
	UHINT	zone_type, property_type, property_index; 
	TPOS_ITEM_RANDOM_BS	*data = NULL;

    file_size = load_file_to_buffer((USTR*)FileName, &file_buf);
    if(file_size < 0)
        goto error;

	//total_item_bases = 0;
    pass = 0;
    buffer_index = 0;
	data = &GameItemRandomBase;
    result = get_buffer_line((char*)file_buf, &buffer_index, file_size, (char*)line, LINE_BUFFER_SIZE);
    while((result == TTN_OK) && (pass == 0))
    {
        len = ( SLONG )strlen( ( const char* )line );
        if( ( line[0] != 0x00 ) && ( line[0] != ';' ) )
        {
            index = 0;

			zone_type = (UHINT)get_buffer_number(line, &index);
			if(zone_type == 0 || zone_type == 1)
			{				
				property_type = ((UHINT)get_buffer_number(line, &index) - 1);
				//載入公用定義部分的數據								
				//屬性序號
				property_index = (UHINT)get_buffer_number(line, &index);
				//名稱索引
				data->ZoneItemRandom[zone_type].PropertyType[property_type].Property[property_index].PropertyNameIndex
					= (UHINT)get_buffer_number(line, &index);
				//有無數值
				data->ZoneItemRandom[zone_type].PropertyType[property_type].Property[property_index].IsHaveValue
					= (UHINT)get_buffer_number(line, &index);
				//適用部位
				data->ZoneItemRandom[zone_type].PropertyType[property_type].Property[property_index].UseablePart
					= (ULONG)get_buffer_number(line, &index);
				//TC等級
				data->ZoneItemRandom[zone_type].PropertyType[property_type].Property[property_index].TCLevel
					= (UHINT)get_buffer_number(line, &index);
				//最小數值
				data->ZoneItemRandom[zone_type].PropertyType[property_type].Property[property_index].MinValue
					= (UHINT)get_buffer_number(line, &index);
				//最大數值
				data->ZoneItemRandom[zone_type].PropertyType[property_type].Property[property_index].MaxValue
					= (UHINT)get_buffer_number(line, &index);
			}
        }
        result = get_buffer_line((char*)file_buf, &buffer_index, file_size, (char*)line, LINE_BUFFER_SIZE);
    }
    
    if(file_buf) free(file_buf);
    return 0;

error:
    return -1;
}

//
//功能: 釋放遊戲物品隨機附加屬性基本數值資料
void	FreeGameItemRandomBase(void)
{
	//Do nothing here.
}
/************************************************************************************************************/
/* 物品操作函數                                                                                             */
/************************************************************************************************************/
void	SetItemBaseID(TPOS_ITEM *IT, UHINT uBaseID)
{
	IT->BaseID = uBaseID;
}

UHINT	GetItemBaseID(TPOS_ITEM *IT)
{
	return	IT->BaseID;
}

void	SetItemHp(TPOS_ITEM *IT, SLONG lHp)
{
	IT->Hp = (UCHAR)lHp;
}

SLONG	GetItemHp(TPOS_ITEM *IT)
{
	return	(SLONG)IT->Hp;
}


void	SetItemID(TPOS_ITEM *IT, ULONG ID)
{
	IT->ID = ID;
}

ULONG	GetItemID(TPOS_ITEM *IT)
{
	return	IT->ID;
}


//獲得物品的名稱
CHAR*	GetItemName(TPOS_ITEM *IT)
{
	return	(CHAR *)GameItemBase[IT->BaseID].Name;
}


//獲得物品的圖表編號
SLONG	GetItemIconIndex(TPOS_ITEM *IT)
{
	return	(SLONG)GameItemBase[IT->BaseID].IconIndex;
}


//獲得物品的類型
SLONG	GetItemType(TPOS_ITEM *IT)
{
	return	(SLONG)GameItemBase[IT->BaseID].Type;
}


//獲得物品的使用人範圍定義
ULONG	GetItemUser(TPOS_ITEM *IT)
{
	return	(ULONG)GameItemBase[IT->BaseID].User;
}


//獲得物品的適用部位定義
ULONG	GetItemPart(TPOS_ITEM *IT)
{
	return	(ULONG)GameItemBase[IT->BaseID].Part;
}


//獲得物品的特殊屬性定義
ULONG	GetItemSpecial(TPOS_ITEM *IT)
{
	return	(ULONG)GameItemBase[IT->BaseID].Special;
}

//將物品設置為空的物品
void	SetItemNone(TPOS_ITEM *IT)
{
	if(IT) memset(IT, 0, sizeof(*IT));
}


//判斷物品是否為空的物品
SLONG	IsItemNone(TPOS_ITEM *IT)
{
	SLONG	BaseID;

	BaseID = GetItemBaseID(IT);
	if(BaseID == ITEM_BASE_ID_NONE)
		return	TRUE;
	return	FALSE;
}


//判斷物品是否是金錢
SLONG	IsItemGold(TPOS_ITEM *IT)
{
	SLONG	BaseID;

	BaseID = GetItemBaseID(IT);
	if(BaseID == ITEM_BASE_ID_GOLD)
		return	TRUE;
	return	FALSE;
}


//判斷物品是否是怪物(寶箱怪)
SLONG	IsItemMonster(TPOS_ITEM *IT)
{
	SLONG	BaseID;

	BaseID = GetItemBaseID(IT);
	if(BaseID == ITEM_BASE_ID_MONSTER)
		return	TRUE;
	return	FALSE;
}


//判斷物品是否是指定職業指定性別的人物可使用的
SLONG	IsItemForMe(TPOS_ITEM *IT, SLONG Career, SLONG Sex)
{
	ULONG	ItemUser, CheckUser;

	//檢查物品是否是自己可以使用的
	ItemUser = GetItemUser(IT);
	CheckUser = MakeUserDescriptionByCareerSex(Career, Sex);
	if( (CheckUser & ItemUser) != CheckUser)
		return	FALSE;
	return	TRUE;
}


//判斷物品是否是指定職業指定性別的人物的頭部裝備
SLONG	IsItemForMyHead(TPOS_ITEM *IT, SLONG Career, SLONG Sex)
{
	ULONG	CheckUser, ItemUser, ItemPart;

	//檢查物品是不是適用於頭上
	ItemPart = GetItemPart(IT);
	if(! (ItemPart & ITEM_PART_HUMAN_HEAD))
		return	FALSE;

	//檢查物品是否是自己可以使用的
	ItemUser = GetItemUser(IT);
	CheckUser = MakeUserDescriptionByCareerSex(Career, Sex);
	if( (CheckUser & ItemUser) != CheckUser)
		return	FALSE;

	return	TRUE;
}


//判斷物品是否是指定職業指定性別的人物的頸部裝備
SLONG	IsItemForMyNeck(TPOS_ITEM *IT, SLONG Career, SLONG Sex)
{
	ULONG	CheckUser, ItemUser, ItemPart;

	//檢查物品是不是適用於頸部
	ItemPart = GetItemPart(IT);
	if(! (ItemPart & ITEM_PART_HUMAN_NECK))
		return	FALSE;

	//檢查物品是否是自己可以使用的
	ItemUser = GetItemUser(IT);
	CheckUser = MakeUserDescriptionByCareerSex(Career, Sex);
	if( (CheckUser & ItemUser) != CheckUser)
		return	FALSE;

	return	TRUE;
}



//判斷物品是否是指定職業指定性別的人物的身體裝備
SLONG	IsItemForMyBody(TPOS_ITEM *IT, SLONG Career, SLONG Sex)
{
	ULONG	CheckUser, ItemUser, ItemPart;

	//檢查物品是不是適用於身體
	ItemPart = GetItemPart(IT);
	if(! (ItemPart & ITEM_PART_HUMAN_BODY))
		return	FALSE;

	//檢查物品是否是自己可以使用的
	ItemUser = GetItemUser(IT);
	CheckUser = MakeUserDescriptionByCareerSex(Career, Sex);
	if( (CheckUser & ItemUser) != CheckUser)
		return	FALSE;

	return	TRUE;
}


//判斷物品是否是指定職業指定性別的人物的腰部裝備
SLONG	IsItemForMyWaist(TPOS_ITEM *IT, SLONG Career, SLONG Sex)
{
	ULONG	CheckUser, ItemUser, ItemPart;

	//檢查物品是不是適用於腰部
	ItemPart = GetItemPart(IT);
	if(! (ItemPart & ITEM_PART_HUMAN_WAIST))
		return	FALSE;

	//檢查物品是否是自己可以使用的
	ItemUser = GetItemUser(IT);
	CheckUser = MakeUserDescriptionByCareerSex(Career, Sex);
	if( (CheckUser & ItemUser) != CheckUser)
		return	FALSE;

	return	TRUE;
}


//判斷物品是否是指定職業指定性別的人物的手腕裝備
SLONG	IsItemForMyWrist(TPOS_ITEM *IT, SLONG Career, SLONG Sex)
{
	ULONG	CheckUser, ItemUser, ItemPart;

	//檢查物品是不是適用於手腕
	ItemPart = GetItemPart(IT);
	if(! (ItemPart & ITEM_PART_HUMAN_WRIST))
		return	FALSE;

	//檢查物品是否是自己可以使用的
	ItemUser = GetItemUser(IT);
	CheckUser = MakeUserDescriptionByCareerSex(Career, Sex);
	if( (CheckUser & ItemUser) != CheckUser)
		return	FALSE;

	return	TRUE;
}


//判斷物品是否是指定職業指定性別的人物的武器裝備
SLONG	IsItemForMyWeapon(TPOS_ITEM *IT, SLONG Career, SLONG Sex)
{
	ULONG	CheckUser, ItemUser, ItemPart;

	//檢查物品是不是適用於武器部位
	ItemPart = GetItemPart(IT);
	if(! (ItemPart & ITEM_PART_HUMAN_WEAPON))
		return	FALSE;

	//檢查物品是否是自己可以使用的
	ItemUser = GetItemUser(IT);
	CheckUser = MakeUserDescriptionByCareerSex(Career, Sex);
	if( (CheckUser & ItemUser) != CheckUser)
		return	FALSE;

	return	TRUE;
}


//判斷物品是否是指定職業指定性別的人物的足部裝備
SLONG	IsItemForMyFeet(TPOS_ITEM *IT, SLONG Career, SLONG Sex)
{
	ULONG	CheckUser, ItemUser, ItemPart;

	//檢查物品是不是適用於足部
	ItemPart = GetItemPart(IT);
	if(! (ItemPart & ITEM_PART_HUMAN_FEET))
		return	FALSE;

	//檢查物品是否是自己可以使用的
	ItemUser = GetItemUser(IT);
	CheckUser = MakeUserDescriptionByCareerSex(Career, Sex);
	if( (CheckUser & ItemUser) != CheckUser)
		return	FALSE;

	return	TRUE;
}


//判斷物品是否是指定職業指定性別的人物的手套裝備
SLONG	IsItemForMyGlove(TPOS_ITEM *IT, SLONG Career, SLONG Sex)
{
	ULONG	CheckUser, ItemUser, ItemPart;

	//檢查物品是不是適用於手套
	ItemPart = GetItemPart(IT);
	if(! (ItemPart & ITEM_PART_HUMAN_GLOVE))
		return	FALSE;

	//檢查物品是否是自己可以使用的
	ItemUser = GetItemUser(IT);
	CheckUser = MakeUserDescriptionByCareerSex(Career, Sex);
	if( (CheckUser & ItemUser) != CheckUser)
		return	FALSE;

	return	TRUE;
}


//判斷物品是否是指定職業指定性別的人物的裝飾物
SLONG	IsItemForMyDeck(TPOS_ITEM *IT, SLONG Career, SLONG Sex)
{
	ULONG	CheckUser, ItemUser, ItemPart;

	//檢查物品是不是適用於裝飾部位
	ItemPart = GetItemPart(IT);
	if(! (ItemPart & ITEM_PART_HUMAN_DECK))
		return	FALSE;

	//檢查物品是否是自己可以使用的
	ItemUser = GetItemUser(IT);
	CheckUser = MakeUserDescriptionByCareerSex(Career, Sex);
	if( (CheckUser & ItemUser) != CheckUser)
		return	FALSE;

	return	TRUE;
}


//判斷物品是否是指定職業指定性別的人物的腰包裝備(快捷欄)
SLONG	IsItemForMySash(TPOS_ITEM *IT, SLONG Career, SLONG Sex)
{
	ULONG	CheckUser, ItemUser, ItemPart;

	//檢查物品是不是適用於腰包
	ItemPart = GetItemPart(IT);
	if(! (ItemPart & ITEM_PART_HUMAN_SASH))
		return	FALSE;

	//檢查物品是否是自己可以使用的
	ItemUser = GetItemUser(IT);
	CheckUser = MakeUserDescriptionByCareerSex(Career, Sex);
	if( (CheckUser & ItemUser) != CheckUser)
		return	FALSE;

	return	TRUE;
}


//判斷物品能否能丟棄
SLONG	IsItemDiscardable(TPOS_ITEM *IT)
{
	ULONG	special;
	SLONG	quest_index;

	quest_index = GetItemQuestIndex(IT);
	if(quest_index > 0)
		return	FALSE;

	special = GetItemSpecial(IT);
	if(special & ITEM_SPECIAL_DISCARDABLE)
		return	TRUE;

	return	FALSE;
}


//判斷物品能否能販賣
SLONG	IsItemSellable(TPOS_ITEM *IT)
{
	ULONG	Special;
	SLONG	quest_index;

	quest_index = GetItemQuestIndex(IT);
	if(quest_index > 0)
		return	FALSE;

	Special = GetItemSpecial(IT);
	if(Special & ITEM_SPECIAL_SELLABLE)
		return	TRUE;
	return	FALSE;
}


//判斷物品能否能夠ICQ傳輸
SLONG	IsItemTransferable(TPOS_ITEM *IT)
{
	ULONG	Special;
	SLONG	quest_index;

	quest_index = GetItemQuestIndex(IT);
	if(quest_index > 0)
		return	FALSE;

	Special = GetItemSpecial(IT);
	if(Special & ITEM_SPECIAL_TRANSFERABLE)
		return	TRUE;
	return	FALSE;
}


//判斷物品能否能交換
SLONG	IsItemSwapable(TPOS_ITEM *IT)
{
	ULONG	Special;
	SLONG	quest_index;

	quest_index = GetItemQuestIndex(IT);
	if(quest_index > 0)
		return	FALSE;

	Special = GetItemSpecial(IT);
	if(Special & ITEM_SPECIAL_SWAPABLE)
		return	TRUE;
	return	FALSE;
}

//判斷物品是否為信物
SLONG	IsItemKeepsake(TPOS_ITEM *IT)
{
	ULONG	Special;
	SLONG	quest_index;

	quest_index = GetItemQuestIndex(IT);
	if(quest_index > 0)
		return	TRUE;

	Special = GetItemSpecial(IT);
	if(Special & ITEM_SPECIAL_KEEPSAKE)
		return	TRUE;
	return	FALSE;
}


//判斷物品能否死後掉落
SLONG	IsItemDeadDrop(TPOS_ITEM *IT)
{
	ULONG	Special;
	//SLONG	quest_index;

	//quest_index = GetItemQuestIndex(IT);
	//if(quest_index > 0)
		//return	FALSE;

	Special = GetItemSpecial(IT);
	if(Special & ITEM_SPECIAL_DEADDROP)
		return	TRUE;
	return	FALSE;
}


//判斷物品能否新手物品
SLONG	IsItemNewbie(TPOS_ITEM *IT)
{
	ULONG	Special;

	Special = GetItemSpecial(IT);
	if(Special & ITEM_SPECIAL_NEWBIE)
		return	TRUE;
	return	FALSE;
}


//判斷物品能否使用
SLONG	IsItemUsable(TPOS_ITEM *IT)
{
	ULONG	Special;
	SLONG	quest_index;

	quest_index = GetItemQuestIndex(IT);
	if(quest_index > 0)
		return	FALSE;

	Special = GetItemSpecial(IT);
	if(Special & ITEM_SPECIAL_USABLE)
		return	TRUE;
	return	FALSE;
}


//判斷物品能否裝備
SLONG	IsItemFixable(TPOS_ITEM *IT)
{
	ULONG	Special;
	SLONG	quest_index;

	quest_index = GetItemQuestIndex(IT);
	if(quest_index > 0)
		return	FALSE;

	Special = GetItemSpecial(IT);
	if(Special & ITEM_SPECIAL_FIXABLE)
		return	TRUE;
	return	FALSE;
}


/************************************************************************************************************/
/* 遊戲區域中地上物品相關函數                                                                               */
/************************************************************************************************************/
void	SetZoneItemPosition(SLONG lIndex, SLONG lX, SLONG lY)
{
	ZoneItemGS[lIndex].X = lX;
	ZoneItemGS[lIndex].Y = lY;
}

void	GetZoneItemPosition(SLONG lIndex, SLONG *lX, SLONG *lY)
{
	if(lX) *lX = ZoneItemGS[lIndex].X;
	if(lY) *lY = ZoneItemGS[lIndex].Y;
}

void	SetZoneItemLife(SLONG lIndex, SLONG lLife)
{
	ZoneItemGS[lIndex].Life = lLife;
}

SLONG	GetZoneItemLife(SLONG lIndex)
{
	return	ZoneItemGS[lIndex].Life;
}

void	SetZoneItem(SLONG lIndex, TPOS_ITEM *IT)
{
	if(IT) ZoneItemGS[lIndex].Item = *IT;
}

void	GetZoneItem(SLONG lIndex, TPOS_ITEM *IT)
{
	if(IT) *IT = ZoneItemGS[lIndex].Item;
}

void	SetZoneItemOwner(SLONG lIndex, CHAR *szOwner)
{
	if(szOwner)
	{
		strcpy((char *)ZoneItemGS[lIndex].Owner, (const char *)szOwner);
	}
}

CHAR*	GetZoneItemOwner(SLONG lIndex)
{
	return	ZoneItemGS[lIndex].Owner;
}

void	SetZoneItemFrame(SLONG lIndex, SLONG lFrame)
{
	ZoneItemGS[lIndex].Frame = lFrame;
}

SLONG	GetZoneItemFrame(SLONG lIndex)
{
	return	ZoneItemGS[lIndex].Frame;
}

void	SetZoneItemState(SLONG lIndex, SLONG lState)
{
	ZoneItemGS[lIndex].State = lState;
}

SLONG	GetZoneItemState(SLONG lIndex)
{
	return	ZoneItemGS[lIndex].State;
}

SLONG	GetZoneItemTotal(SLONG lIndex)
{
	return	ZoneItemGS[lIndex].Total;
}

void	SetZoneItemNext(SLONG lIndex, SLONG lNext)
{
	ZoneItemGS[lIndex].Next = lNext;
}

SLONG	GetZoneItemNext(SLONG lIndex)
{
	return	ZoneItemGS[lIndex].Next;
}

void	SetZoneItemFlag(SLONG lIndex, SLONG lFlag)
{
	ZoneItemGS[lIndex].Flag = lFlag;
}

SLONG	GetZoneItemFlag(SLONG lIndex)
{
	return	ZoneItemGS[lIndex].Flag;
}

//
//初始化區域中地圖物品資料
void	InitZoneItem(void)
{
    SLONG   i;

    for(i=0; i<HEAD_GAME_ITEMS; i++)
    {
		ZoneItemGS[i].Next = i;
		ZoneItemGS[i].Tail = i;
		ZoneItemGS[i].Total = 0;
    }
    for(i=HEAD_GAME_ITEMS; i<MAX_GAME_ITEMS; i++)
    {
		ClearOneZoneItem(i);
    }
}


//重置區域中地圖所有物品資料
void	ResetZoneItem(void)
{
	InitZoneItem();
}


//清除區域地圖上一個物品資料
void	ClearOneZoneItem(SLONG index)
{
	ZoneItemGS[index].Flag = 0;
	SetItemNone(&ZoneItemGS[index].Item);
	ZoneItemGS[index].X = 0;
	ZoneItemGS[index].Y = 0;
	ZoneItemGS[index].Next = -1;
}


//判斷區域中地圖物品欄位是否未被使用
SLONG	IsZoneItemUnused(SLONG index)
{
	if(ZoneItemGS[index].Flag == 0)
		return	TRUE;
	return	FALSE;
}




//尋找可以使用的區域地圖物品欄位
SLONG	FindUnusedZoneItem(void)
{
	SLONG	find_idx, i;

	find_idx = -1;
	for(i=HEAD_GAME_ITEMS; i<MAX_GAME_ITEMS; i++)
	{
		if( IsZoneItemUnused(i) )
		{
			find_idx = i;
			break;
		}
	}
	return	find_idx;
}


//在區域地圖上添加一個物品
SLONG	AddZoneItem(SLONG X, SLONG Y, CHAR *Owner, TPOS_ITEM *IT)
{
	SLONG	index, tail;
	SLONG	map_no = 0;

	index = FindUnusedZoneItem();
	if(index >= 0)
	{
		ClearOneZoneItem(index);
		SetZoneItemPosition(index, X, Y);
		SetZoneItemOwner(index, Owner);
		SetZoneItem(index, IT);
		SetZoneItemLife(index, ZONE_ITEM_LIFE_TICKS);
		SetZoneItemState(index, 0);
		SetZoneItemFrame(index, 0);
		ZoneItemGS[index].Flag = 1;
		//
		ZoneItemGS[index].Next = map_no;
        tail = ZoneItemGS[map_no].Tail;
        ZoneItemGS[tail].Next = index;
        ZoneItemGS[map_no].Tail = index;
        ZoneItemGS[map_no].Total ++;
	}
	return	index;
}


//從區域地圖上刪除一個物品
SLONG	DeleteZoneItem(SLONG X, SLONG Y)
{
    SLONG   p, s, del_count;
	SLONG	map_no = 0;

    del_count = 0;
    s = map_no;
    p = ZoneItemGS[s].Next;
    while(p != map_no)
    {
        if(ZoneItemGS[p].X == X && ZoneItemGS[p].Y == Y)
        {
            ZoneItemGS[s].Next = ZoneItemGS[p].Next;
            if(ZoneItemGS[s].Next == map_no)
                ZoneItemGS[map_no].Tail = s;
            ZoneItemGS[map_no].Total --;

            ZoneItemGS[p].Flag = 0;
			ClearOneZoneItem(p);

			del_count++;
        }

		//
        s = p;
        p = ZoneItemGS[s].Next;
    }
    return  del_count;
}


//對齊地圖物品座標
void    TrimZoneItemPosition(SLONG *X, SLONG *Y)
{
    SLONG   trim_x, trim_y;
    SLONG   grid_x, grid_y;

    trim_x = *X;
    trim_y = *Y;
    D2_adjust_diamond_position(&trim_x, &trim_y, &grid_x, &grid_y, ITEM_STAY_WIDTH, ITEM_STAY_HEIGHT);
    trim_x = grid_x * ITEM_STAY_WIDTH + (grid_y & 1) * ITEM_STAY_WIDTH / 2;
    trim_y = grid_y * ITEM_STAY_HEIGHT / 2;
    *X = trim_x;
    *Y = trim_y;
}


//
//功能: 獲得地圖上當前位置所放置的物品, 
//返回: 如果沒有發現物品, 返回-1, 否則, 將物品數值存放在IT中, 
//	    並且返回該物品在地圖物品列表的索引值.
SLONG	CatchZoneItem(SLONG X, SLONG Y, TPOS_ITEM *IT)
{
    SLONG   p, index;
	SLONG	map_no = 0;

	index = -1;
    p = ZoneItemGS[map_no].Next;
    while(p != map_no)
    {
        if(ZoneItemGS[p].X == X && ZoneItemGS[p].Y == Y)
        {
			if(IT) *IT = ZoneItemGS[p].Item;
			index = p;
            break;
        }
        else
        {
            p = ZoneItemGS[p].Next;
        }
    }
    return index;
}


/************************************************************************************************************/
/* Data functions of Land Normal Item(s)                                                                    */
/************************************************************************************************************/
void	SetLandItemSpecial1(TPOS_ITEM *IT, UHINT uSpecial)
{
	IT->IR.Land.Special1 = uSpecial;
}

UHINT	GetLandItemSpecial1(TPOS_ITEM *IT)
{
	return	IT->IR.Land.Special1;
}

void	SetLandItemSpecial2(TPOS_ITEM *IT, UHINT uSpecial)
{
	IT->IR.Land.Special2 = uSpecial;
}

UHINT	GetLandItemSpecial2(TPOS_ITEM *IT)
{
	return	IT->IR.Land.Special2;
}

void	SetLandItemDataType1(TPOS_ITEM *IT, UCHAR uType)
{
	IT->IR.Land.Type1 = uType;
}

UCHAR	GetLandItemDataType1(TPOS_ITEM *IT)
{
	return	IT->IR.Land.Type1;
}

void	SetLandItemDataValue1(TPOS_ITEM *IT, UCHAR uValue)
{
	IT->IR.Land.Data1 = uValue;
}

UCHAR	GetLandItemDataValue1(TPOS_ITEM *IT)
{
	return	IT->IR.Land.Data1;
}

void	SetLandItemDataType2(TPOS_ITEM *IT, UCHAR uType)
{
	IT->IR.Land.Type2 = uType;
}

UCHAR	GetLandItemDataType2(TPOS_ITEM *IT)
{
	return	IT->IR.Land.Type2;
}

void	SetLandItemDataValue2(TPOS_ITEM *IT, UCHAR uValue)
{
	IT->IR.Land.Data2 = uValue;
}

UCHAR	GetLandItemDataValue2(TPOS_ITEM *IT)
{
	return	IT->IR.Land.Data2;
}


SLONG	GetItemAttackData(TPOS_ITEM *IT)
{
	SLONG	base_attack;
	SLONG	attack_data;
	SLONG	added_attack;
	SLONG	enhance_ratio;
	SLONG	type, hp, base, data_type, data_value;

	//
	// Only land equipment item has this property.
	//
	type = GetItemType(IT);
	if(type != ITEM_TYPE_LAND_NORMAL)
		return	0;

	//
	// Only the item with greater than zero hp has data properties.
	//
	hp = GetItemHp(IT);
	if(hp == 0)
		return	0;

	
	base_attack = 0;
	base = GetItemBaseID(IT);
	if(base >= 0 && base < MAX_GAME_ITEM_BASES)
	{
		base_attack = GameItemBase[base].Land.BaseAtt;
	}

	//
	// Magic attack are associated with type1-data1 and type2-data2.
	//
	added_attack = 0;
	enhance_ratio = 0;
	/*
	data_type = GetLandItemDataType1(IT);
	data_value = GetLandItemDataValue1(IT);
	switch(data_type)
	{
	case LAND_ITEM_DATATYPE2_ADD_ATT_1:
	case LAND_ITEM_DATATYPE2_ADD_ATT_2:
	case LAND_ITEM_DATATYPE2_ADD_ATT_3:
		added_attack += data_value;
		break;
	case LAND_ITEM_DATATYPE2_ENHANCE_ATT_1:
	case LAND_ITEM_DATATYPE2_ENHANCE_ATT_2:
	case LAND_ITEM_DATATYPE2_ENHANCE_ATT_3:
		enhance_ratio += data_value;
		break;
	}
	*/

	data_type = GetLandItemDataType2(IT);
	data_value = GetLandItemDataValue2(IT);
	switch(data_type)
	{
	case LAND_ITEM_DATATYPE2_ADD_ATT:	
		added_attack += data_value;
		break;
	case LAND_ITEM_DATATYPE2_ENHANCE_ATT:	
		enhance_ratio += data_value;
		break;
	}

	attack_data = base_attack * (100 + enhance_ratio) / 100 + added_attack;

	return	attack_data;
}


SLONG	GetItemAddedAttack(TPOS_ITEM *IT)
{
	SLONG	added_attack;
	SLONG	type;
	SLONG	hp;
	SLONG	data_type, data_value;

	//
	// Only land equipment item has this property.
	//
	type = GetItemType(IT);
	if(type != ITEM_TYPE_LAND_NORMAL)
		return	0;

	//
	// Only the item with greater than zero hp has data properties.
	//
	hp = GetItemHp(IT);
	if(hp == 0)
		return	0;

	//
	// Magic attack are associated with type1-data1 and type2-data2.
	//
	added_attack = 0;
	/*
	data_type = GetLandItemDataType1(IT);
	switch(data_type)
	{
	case LAND_ITEM_DATATYPE2_ADD_ATT_1:
	case LAND_ITEM_DATATYPE2_ADD_ATT_2:
	case LAND_ITEM_DATATYPE2_ADD_ATT_3:	
		data_value = GetLandItemDataValue1(IT);
		added_attack += data_value;
		break;
	}
	*/	
	data_type = GetLandItemDataType2(IT);
	switch(data_type)
	{
	case LAND_ITEM_DATATYPE2_ADD_ATT:		
		data_value = GetLandItemDataValue2(IT);
		added_attack += data_value;
		break;
	}

	return	added_attack;
}


SLONG	GetItemEnhanceAttackRatio(TPOS_ITEM *IT)
{
	SLONG	enhance_ratio;
	SLONG	type;
	SLONG	hp;
	SLONG	data_type, data_value;

	//
	// Only land equipment item has this property.
	//
	type = GetItemType(IT);
	if(type != ITEM_TYPE_LAND_NORMAL)
		return	0;

	//
	// Only the item with greater than zero hp has data properties.
	//
	hp = GetItemHp(IT);
	if(hp == 0)
		return	0;

	//
	// Magic attack are associated with type1-data1 and type2-data2.
	//
	enhance_ratio = 0;
	/*
	data_type = GetLandItemDataType1(IT);
	if(data_type == LAND_ITEM_DATATYPE_ENHANCE_ATT)
	{
		data_value = GetLandItemDataValue1(IT);
		enhance_ratio += data_value;
	}
	*/
	
	data_type = GetLandItemDataType2(IT);
	switch(data_type)
	{
	case LAND_ITEM_DATATYPE2_ENHANCE_ATT:		
		data_value = GetLandItemDataValue2(IT);
		enhance_ratio += data_value;
		break;
	}

	return	enhance_ratio;
}


SLONG	GetItemAddedMagicAttack(TPOS_ITEM *IT)
{
	SLONG	added_magic_attack;
	SLONG	type;
	SLONG	hp;
	SLONG	data_type, data_value;

	//
	// Only land equipment item has this property.
	//
	type = GetItemType(IT);
	if(type != ITEM_TYPE_LAND_NORMAL)
		return	0;

	//
	// Only the item with greater than zero hp has data properties.
	//
	hp = GetItemHp(IT);
	if(hp == 0)
		return	0;

	//
	// Magic attack are associated with type1-data1 and type2-data2.
	//
	added_magic_attack = 0;
	/*
	data_type = GetLandItemDataType1(IT);
	if(data_type == LAND_ITEM_DATATYPE_ADD_MAGIC_HURT)
	{
		data_value = GetLandItemDataValue1(IT);
		added_magic_attack += data_value;
	}
	*/
	
	data_type = GetLandItemDataType2(IT);
	switch(data_type)		
	{
	case LAND_ITEM_DATATYPE2_ADD_MAGIC_HURT:	
		data_value = GetLandItemDataValue2(IT);
		added_magic_attack += data_value;
		break;
	}

	return	added_magic_attack;
}

SLONG	GetItemAddedSpecialAttack(TPOS_ITEM *IT)
{
	SLONG	added_special_attack;
	SLONG	type;
	SLONG	hp;
	SLONG	data_type, data_value;

	//
	// Only land equipment item has this property.
	//
	type = GetItemType(IT);
	if(type != ITEM_TYPE_LAND_NORMAL)
		return	0;

	//
	// Only the item with greater than zero hp has data properties.
	//
	hp = GetItemHp(IT);
	if(hp == 0)
		return	0;

	//
	// Magic attack are associated with type1-data1 and type2-data2.
	//
	added_special_attack = 0;
	/*
	data_type = GetLandItemDataType1(IT);
	if(data_type == LAND_ITEM_DATATYPE2_ADD_SPECIAL_HURT_1)
	{
		data_value = GetLandItemDataValue1(IT);
		added_special_attack += data_value;
	}
	*/
	data_type = GetLandItemDataType2(IT);
	switch(data_type)
	{
	case LAND_ITEM_DATATYPE2_ADD_SPECIAL_HURT:	
		data_value = GetLandItemDataValue2(IT);
		added_special_attack += data_value;
		break;
	}

	return	added_special_attack;
}


//
//功能: 計算陸地裝備物品的防禦力
//      防禦力 = 物品基礎防禦力 * ( 1 + 加強防禦 %) + 增加防禦力
//
SLONG	GetItemDefenceData(TPOS_ITEM *IT)
{
	SLONG	type, hp, base;
	SLONG	data_type, data_value;
	SLONG	defence_data, defence_added;
	SLONG	enhance_ratio, base_defence;

	//
	// Only land equipment item has this property.
	//
	type = GetItemType(IT);
	if(type != ITEM_TYPE_LAND_NORMAL)
		return	0;

	//
	// Only the item with greater than zero hp has data properties.
	//
	hp = GetItemHp(IT);
	if(hp == 0)
		return	0;

	//
	// Defence ratio are associated with type1-data1 and type2-data2.
	//
	base_defence = 0;
	base = GetItemBaseID(IT);
	if(base >= 0 && base < MAX_GAME_ITEM_BASES)
	{
		base_defence += GameItemBase[base].Land.BaseDef;
	}

	defence_added = 0;
	enhance_ratio = 0;
	data_type = GetLandItemDataType1(IT);
	data_value = GetLandItemDataValue1(IT);
	switch(data_type)
	{
	case LAND_ITEM_DATATYPE1_ADD_DEF:	
		defence_added += data_value;
		break;
	case LAND_ITEM_DATATYPE1_ENHANCE_DEF:	
		enhance_ratio += data_value;
		break;
	}
	/*
	data_type = GetLandItemDataType2(IT);
	data_value = GetLandItemDataValue2(IT);
	switch(data_type)
	{
	case LAND_ITEM_DATATYPE_ADD_DEF:
		defence_added += data_value;
		break;
	case LAND_ITEM_DATATYPE_ENHANCE_DEF:
		enhance_ratio += data_value;
		break;
	}
	*/
	defence_data = base_defence * (100 + enhance_ratio) / 100 + defence_added;

	return	defence_data;
}


//
//功能: 獲得物品的抵抗百分比
//
SLONG	GetItemResistRatio(TPOS_ITEM *IT)
{
	SLONG	type, hp;
	SLONG	data_type, data_value;
	SLONG	resist_ratio;

	//
	// Only land equipment item has this property.
	//
	type = GetItemType(IT);
	if(type != ITEM_TYPE_LAND_NORMAL)
		return	0;

	//
	// Only the item with greater than zero hp has data properties.
	//
	hp = GetItemHp(IT);
	if(hp == 0)
		return	0;

	//
	// Resist ratio are associated with type1-data1 and type2-data2.
	//
	resist_ratio = 0;
	data_type = GetLandItemDataType1(IT);
	switch(data_type)		
	{
	case LAND_ITEM_DATATYPE1_ADD_RESIST:	
		data_value = GetLandItemDataValue1(IT);
		resist_ratio += data_value;
		break;
	}
	/*
	data_type = GetLandItemDataType2(IT);
	if(data_type == LAND_ITEM_DATATYPE_ADD_RESIST)
	{
		data_value = GetLandItemDataValue2(IT);
		resist_ratio += data_value;
	}
	*/
	return	resist_ratio;
}


SLONG	GetItemAddedMaxHp(TPOS_ITEM *IT)
{
	SLONG	type, hp;
	SLONG	data_type, data_value;
	SLONG	max_hp;

	//
	// Only land equipment item has this property.
	//
	type = GetItemType(IT);
	if(type != ITEM_TYPE_LAND_NORMAL)
		return	0;

	//
	// Only the item with greater than zero hp has data properties.
	//
	hp = GetItemHp(IT);
	if(hp == 0)
		return	0;

	//
	// Resist ratio are associated with type1-data1 and type2-data2.
	//
	max_hp = 0;
	data_type = GetLandItemDataType1(IT);
	switch(data_type)
	{
	case LAND_ITEM_DATATYPE1_ADD_MAX_HP:		
		data_value = GetLandItemDataValue1(IT);
		max_hp += data_value;
		break;
	}
	/*
	data_type = GetLandItemDataType2(IT);
	if(data_type == LAND_ITEM_DATATYPE_ADD_MAX_HP)
	{
		data_value = GetLandItemDataValue2(IT);
		max_hp += data_value;
	}
	*/

	return	max_hp;
}

SLONG	GetItemAddedMaxMp(TPOS_ITEM *IT)
{
	SLONG	type, hp;
	SLONG	data_type, data_value;
	SLONG	max_mp;

	//
	// Only land equipment item has this property.
	//
	type = GetItemType(IT);
	if(type != ITEM_TYPE_LAND_NORMAL)
		return	0;

	//
	// Only the item with greater than zero hp has data properties.
	//
	hp = GetItemHp(IT);
	if(hp == 0)
		return	0;

	//
	// Resist ratio are associated with type1-data1 and type2-data2.
	//
	max_mp = 0;
	data_type = GetLandItemDataType1(IT);
	switch(data_type)
	{
	case LAND_ITEM_DATATYPE1_ADD_MAX_MP:		
		data_value = GetLandItemDataValue1(IT);
		max_mp += data_value;
		break;
	}
	/*
	data_type = GetLandItemDataType2(IT);
	if(data_type == LAND_ITEM_DATATYPE_ADD_MAX_MP)
	{
		data_value = GetLandItemDataValue2(IT);
		max_mp += data_value;
	}
	*/

	return	max_mp;
}


UHINT	GetItemExplodeRate(TPOS_ITEM *IT)
{
	SLONG	type, hp;
	UHINT	explode_rate;

	//
	// Only land equipment item has this property.
	//
	type = GetItemType(IT);
	if(type != ITEM_TYPE_LAND_NORMAL)
		return	0;

	//
	// Only the item with greater than zero hp has data properties.
	//
	hp = GetItemHp(IT);
	if(hp == 0)
		return	0;

	explode_rate = (UHINT)GameItemBase[IT->BaseID].Land.ExplodeRate;

	return	explode_rate;
}

/************************************************************************************************************/
/* Sea normal item functions                                                                                */
/************************************************************************************************************/
void	SetSeaItemSpecial1(TPOS_ITEM *IT, UHINT uSpecial)
{
	IT->IR.Sea.Special1 = uSpecial;
}

UHINT	GetSeaItemSpecial1(TPOS_ITEM *IT)
{
	return	IT->IR.Sea.Special1;
}

void	SetSeaItemDataType1(TPOS_ITEM *IT, UCHAR uType)
{
	IT->IR.Sea.Type1 = uType;
}

UCHAR	GetSeaItemDataType1(TPOS_ITEM *IT)
{
	return	IT->IR.Sea.Type1;
}

void	SetSeaItemDataValue1(TPOS_ITEM *IT, UCHAR uValue)
{
	IT->IR.Sea.Data1 = uValue;
}

UCHAR	GetSeaItemDataValue1(TPOS_ITEM *IT)
{
	return	IT->IR.Sea.Data1;
}

void	SetSeaItemDataType2(TPOS_ITEM *IT, UCHAR uType)
{
	IT->IR.Sea.Type2 = uType;
}

UCHAR	GetSeaItemDataType2(TPOS_ITEM *IT)
{
	return	IT->IR.Sea.Type2;
}

void	SetSeaItemDataValue2(TPOS_ITEM *IT, UCHAR uValue)
{
	IT->IR.Sea.Data2 = uValue;
}

UCHAR	GetSeaItemDataValue2(TPOS_ITEM *IT)
{
	return	IT->IR.Sea.Data2;
}

/************************************************************************************************************/
/* Drug item functions                                                                                */
/************************************************************************************************************/
SLONG	GetDrugItemAddStr(TPOS_ITEM *IT)
{
	UHINT	base;

	base = GetItemBaseID(IT);
	return GameItemBase[base].Drug.AddStr;
}

SLONG	GetDrugItemAddIns(TPOS_ITEM *IT)
{
	UHINT	base;

	base = GetItemBaseID(IT);
	return GameItemBase[base].Drug.AddIns;
}

SLONG	GetDrugItemAddWit(TPOS_ITEM *IT)
{
	UHINT	base;

	base = GetItemBaseID(IT);
	return GameItemBase[base].Drug.AddWit;
}

SLONG	GetDrugItemAddLuck(TPOS_ITEM *IT)
{
	UHINT	base;

	base = GetItemBaseID(IT);
	return GameItemBase[base].Drug.AddLuck;
}

SLONG	GetDrugItemResHpRate(TPOS_ITEM *IT)
{
	UHINT	base;

	base = GetItemBaseID(IT);
	return GameItemBase[base].Drug.ResHpRate;
}

SLONG	GetDrugItemResMpRate(TPOS_ITEM *IT)
{
	UHINT	base;

	base = GetItemBaseID(IT);
	return GameItemBase[base].Drug.ResMpRate;
}

/************************************************************************************************************/
/* Treasure map item functions                                                                              */
/************************************************************************************************************/
void	SetTreasureMapItemWholePieces(TPOS_ITEM *IT, UHINT uPieces)
{
	IT->IR.TreasureMap.WholePieces = uPieces;
}

UHINT	GetTreasureMapItemWholePieces(TPOS_ITEM *IT)
{
	return	IT->IR.TreasureMap.WholePieces;
}

void	SetTreasureMapItemCurrentPieces(TPOS_ITEM *IT, UHINT uPieces)
{
	IT->IR.TreasureMap.CurrentPieces = uPieces;
}

UHINT	GetTreasureMapItemCurrentPieces(TPOS_ITEM *IT)
{
	return	IT->IR.TreasureMap.CurrentPieces;
}

void	SetTreasureMapItemIndex(TPOS_ITEM *IT, UCHAR uIndex)
{
	IT->IR.TreasureMap.Index = uIndex;
}

UCHAR	GetTreasureMapItemIndex(TPOS_ITEM *IT)
{
	return	IT->IR.TreasureMap.Index;
}

/************************************************************************************************************/
/* Sea expendable item functions                                                                            */
/************************************************************************************************************/
void	SetSeaExpendableItemCount(TPOS_ITEM *IT, UHINT uCount)
{
	IT->IR.SeaExpendable.Count = uCount;
}

UHINT	GetSeaExpendableItemCount(TPOS_ITEM *IT)
{
	return	IT->IR.SeaExpendable.Count;
}

/************************************************************************************************************/
/* Sailor item functions                                                                                    */
/************************************************************************************************************/
void	SetSailorItemTotalCount(TPOS_ITEM *IT, UCHAR uCount)
{
	IT->IR.Sailor.TotalCount = uCount;
}

UCHAR	GetSailorItemTotalCount(TPOS_ITEM *IT)
{
	return	IT->IR.Sailor.TotalCount;
}

void	SetSailorItemHealthCount(TPOS_ITEM *IT, UCHAR uCount)
{
	IT->IR.Sailor.HealthCount = uCount;
}

UCHAR	GetSailorItemHealthCount(TPOS_ITEM *IT)
{
	return	IT->IR.Sailor.HealthCount;
}

/************************************************************************************************************/
/* Gold item functions                                                                                      */
/************************************************************************************************************/
void	SetItemGoldCount(TPOS_ITEM *IT, ULONG uGold)
{
	IT->IR.Money.Amount = uGold;
}

ULONG	GetItemGoldCount(TPOS_ITEM *IT)
{
	return	IT->IR.Money.Amount;
}

ULONG	ComputeItemBuyCost(TPOS_ITEM *IT)
{
	enum
	{	ATTACK_PRICE_BASE	=	10,
	DEFENCE_PRICE_BASE		=	10
	};
	UHINT	base_id;
	SLONG	type;
	ULONG	cost;

	base_id = IT->BaseID;
	type = GetItemType(IT);
	switch(type)
	{
	case ITEM_TYPE_LAND_NORMAL:
		cost = GameItemBase[base_id].Land.BaseAtt * ATTACK_PRICE_BASE 
			+ GameItemBase[base_id].Land.BaseDef * DEFENCE_PRICE_BASE;
		break;
	default:
		cost = 200;	// Jack, To be modified here. [2/24/2003]
		break;
	}
	return	cost;
}


ULONG	ComputeItemSellPrice(TPOS_ITEM *IT)
{
	enum
	{	ATTACK_PRICE_BASE	=	5,
	DEFENCE_PRICE_BASE		=	5
	};
	UHINT	base_id;
	SLONG	type;
	ULONG	price;

	base_id = IT->BaseID;
	type = GetItemType(IT);
	switch(type)
	{
	case ITEM_TYPE_LAND_NORMAL:
		price = GameItemBase[base_id].Land.BaseAtt * ATTACK_PRICE_BASE 
			+ GameItemBase[base_id].Land.BaseDef * DEFENCE_PRICE_BASE;
		break;
	default:
		price = 200;	// Jack, To be modified here. [2/24/2003]
		break;
	}
	return	price;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Jack,  [5/8/2003]
// item-quest related functions
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void	SetItemQuestIndex(TPOS_ITEM *IT, SLONG lIndex)
{
	IT->QuestIndex = (UCHR)lIndex;
}

SLONG	GetItemQuestIndex(TPOS_ITEM *IT)
{
	return	(SLONG)IT->QuestIndex;
}

