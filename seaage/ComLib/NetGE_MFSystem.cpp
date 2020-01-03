/*
**	NetGE_MFSystem.cpp 
**	MF system functions.
**
**	Hawke,	2003.03.21.	
*/
//********************
//**	MF �t��		**
//********************
#include "NetGE_MainFunc.h"

// --------------------------------------------------------------------------------------
SLONG CheckIsDropQuestItem(ULONG PlayerNo, ULONG NpcNo);
SLONG IsMonsterDropItem(TPOS_ITEM_MF ItemMf);
int	MakeDropItemType(TPOS_ITEM_MF ItemMf);
int	MakeDropItemTCClass(UHINT MonsterLevel);
SLONG FindThisTCClassItemFromItemBase(UHINT	tc_class, int item_type, TPOS_ITEM *IT, UHINT MonsterLevel);
int MakeItemMFLevel(TPOS_ITEM *IT, TPOS_ITEM_MF ItemMf);
void MakeItemProperty(TPOS_ITEM	*IT, TPOS_ITEM_MF ItemMf, int Mf,UHINT	tc_class);
SLONG CheckIsDropQuestItem(ULONG PlayerNo, ULONG NpcNo);
int	FindMonsterDropItemProbability(TPOS_ITEM_MF ItemMf);
int	ReturnPropertyCountInType(int ZoneType, int PropertyType);
void RandomPropertyFromType(TPOS_ITEM *IT, int type_index, int zone, UHINT tc_class);
void AddPropertyToItem(TPOS_ITEM *IT, int zone, int type_index, int property_index);
int	TransferTypeIndex(char type);

// --------------------------------------------------------------------------------------
SLONG MakeItem(TPOS_ITEM *Item, TPOS_ITEM_MF ItemMf)
{
	SLONG		quest = FALSE;
	SLONG		drop = FALSE;
	SLONG		find_item = -1;
	int			item_type;
	int			tc_class;	
	int			mf; 
	TPOS_ITEM	item;

	quest = CheckIsDropQuestItem(ItemMf.PlayerIndex, ItemMf.DestNpc);
	if(quest == FALSE)
	{
		// �D�������Ȫ��~
		drop = IsMonsterDropItem(ItemMf);
		if(drop == TRUE)
		{
			item_type = MakeDropItemType(ItemMf);
			tc_class = MakeDropItemTCClass(ItemMf.MonsterLevel);
			find_item = FindThisTCClassItemFromItemBase(tc_class, item_type, &item, ItemMf.MonsterLevel);
			if(find_item == TRUE)
			{
				mf = MakeItemMFLevel(&item, ItemMf);
				if(mf > 0)
				{
					MakeItemProperty(&item, ItemMf, mf, tc_class);
				}
				memcpy(Item, &item, sizeof(TPOS_ITEM));
				return drop;
			}
			drop = FALSE;
			return drop;
		}
	}else
	{
		// �������Ȫ��~
	}
	return drop;
}
// --------------------------------------------------------------------------------------
// (1)�T�w�O�_���X���~
// --------------------------------------------------------------------------------------
SLONG IsMonsterDropItem(TPOS_ITEM_MF ItemMf)
{
	int		randno;
	int		probability;
	SLONG	drop;
	
	drop = FALSE;
	randno = system_rand() % 100;

	probability = FindMonsterDropItemProbability(ItemMf);
	if(randno <= probability)drop = TRUE;	

	return drop;
}
// --------------------------------------------------------------------------------------
// (2)�̩w���~����
// --------------------------------------------------------------------------------------		
int	MakeDropItemType(TPOS_ITEM_MF ItemMf)
{	
	int		randno;	
	int		item_type;
	UHINT	land_normal, drug, money, treasure_map;

	land_normal = ItemMf.NormalProbability;
	drug = ItemMf.DrugProbability;
	money = ItemMf.MoneyProbability;
	treasure_map = ItemMf.TreasureMapProbability;
	randno = system_rand() % 100;
	switch(ItemMf.CurrentZoneType)
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
		//[0,land_normal,drug,money,treasure_map]
		if(randno < land_normal)
			item_type = ITEM_TYPE_LAND_NORMAL;
		else if(randno < land_normal + drug)
			item_type = ITEM_TYPE_DRUG;
		else if(randno < land_normal + drug + money)
			item_type = ITEM_TYPE_MONEY;
		else
			item_type = ITEM_TYPE_TREASURE_MAP;
		break;
	case SAIL_NORMAL:
	case SAIL_NEWBIE:
	case SAIL_PK:
	case SAIL_FINDGOLD:
	case SAIL_BIRTH:		
		item_type = ITEM_TYPE_SEA_NORMAL;
		break;
	}	
	return	item_type;
}
// --------------------------------------------------------------------------------------
// (3)�ھکǪ��� TC(Treature Class)����, ���Ӥ@�w�W�h�M�w�Ӫ��~��TC�ŧO
// --------------------------------------------------------------------------------------
int	MakeDropItemTCClass(UHINT MonsterLevel)
{
	UHINT	monster_tc_class;
	monster_tc_class = (MonsterLevel / 3) * 3;
	
	return monster_tc_class;
}
// --------------------------------------------------------------------------------------
// (4)�ھڽT�w��TC�ŧO, �j�����~�򥻪�, �H�����@�زŦX�H�W���󪺪��~.
// --------------------------------------------------------------------------------------
SLONG FindThisTCClassItemFromItemBase(UHINT	tc_class, int item_type, TPOS_ITEM *IT, UHINT MonsterLevel)
{
	SLONG	return_value;
	int	i, j, randno;
	TPOS_ITEM_BS	temp_item[MAX_GAME_ITEM_BASES];
	TPOS_ITEM		return_item;

	j = 0;
	return_value = FALSE;
	memset(&return_item, 0x0, sizeof(TPOS_ITEM));
	memset(temp_item, 0x0, sizeof(TPOS_ITEM_BS)*MAX_GAME_ITEM_BASES);
	switch(item_type)
	{
	case ITEM_TYPE_LAND_NORMAL:
		for(i = 0;i < MAX_GAME_ITEM_BASES;i++)
		{
			if(GameItemBase[i].BaseID == 0)
				continue;
			
			if(GameItemBase[i].Type == (SLONG)item_type)
			{
				if(GameItemBase[i].TcLevel <= (SLONG)tc_class && GameItemBase[i].TcLevel >= (SLONG)tc_class - (tc_class/3))
				{
					temp_item[j] = GameItemBase[i];
					j++;
				}
			}
		}
		break;
	case ITEM_TYPE_DRUG:
		for(i = 0;i < MAX_GAME_ITEM_BASES;i++)
		{
			if(GameItemBase[i].BaseID == 0)
				continue;
			
			if(GameItemBase[i].Type == (SLONG)ITEM_TYPE_DRUG)
			{
				temp_item[j] = GameItemBase[i];
				j++;				
			}
		}
		break;
	case ITEM_TYPE_MONEY:
		temp_item[0].BaseID = 200;		
		j++;
		break;
	case ITEM_TYPE_TREASURE_MAP:
		int		temp_treasury[MAX_TREASURY_PER_WORLD];		
		// ����X�i�H�Ϊ��_�ø��
		for(i = 0; i < MAX_TREASURY_PER_WORLD; i++)
		{
			LOCK_TREASURY(0);
			if(GetTreasuryMapPartNo(i) != 0)
			{
				temp_treasury[j] = i;
				j++;		
			}
			UNLOCK_TREASURY(0);
		}
		return_item.BaseID = 300;				
		break;
	}	
	if(j == 0)return return_value;
	if(item_type == ITEM_TYPE_MONEY || item_type == ITEM_TYPE_TREASURE_MAP)
	{
		if(item_type == ITEM_TYPE_MONEY)
		{
			return_item.BaseID = temp_item[0].BaseID;
			return_item.IR.Money.Amount = MonsterLevel * 2;		
		}
		if(item_type == ITEM_TYPE_TREASURE_MAP)
		{			
			int		t_index, temp_piece;
			
			t_index = system_rand() % j;			
			LOCK_TREASURY(0);
			return_item.IR.TreasureMap.WholePieces = GetTreasuryMapPartNo(t_index);
			temp_piece = system_rand() % GetTreasuryMapPartNo(t_index);
			UNLOCK_TREASURY(0);
			return_item.IR.TreasureMap.CurrentPieces = 2 ^ temp_piece;
			return_item.IR.TreasureMap.Index = t_index;
		}		
	}else	
	{
		randno = system_rand() % j;
		return_item.BaseID = temp_item[randno].BaseID;	
		return_item.Hp = 100;
	}
	
	memcpy(IT, &return_item, sizeof(TPOS_ITEM));

	return_value = TRUE;
	return return_value;
}
// --------------------------------------------------------------------------------------
//(5)�M�w�˳ƪ��]�k�ŧO(MF)
// --------------------------------------------------------------------------------------
int MakeItemMFLevel(TPOS_ITEM *IT, TPOS_ITEM_MF ItemMf)
{
	int rp;	
	int mf;	
	int item_mf;

	//	A)�ھڰϰ�O�_�O���_�ϰ�, �H������ rp ��:
	//	���_�ϰ�:	rp = random(0~1)
	//	�D���_�ϰ�: rp = random(0.01~1)	
	switch(ItemMf.CurrentZoneType)
	{
	case CITY_NORMAL:
	case CITY_NEWBIE:
	case CITY_PK:	
	case CITY_BIRTH:
	case FIELD_NORMAL:
	case FIELD_NEWBIE:
	case FIELD_PK:	
	case FIELD_BIRTH:		
	case SAIL_NORMAL:
	case SAIL_NEWBIE:
	case SAIL_PK:
	case SAIL_BIRTH:
		rp = (system_rand() % ItemMf.OtherZoneItemMFProbability) + 1;	
		break;		
	case CITY_FINDGOLD:
	case FIELD_FINDGOLD:
	case SAIL_FINDGOLD:
		rp = (system_rand() % ItemMf.FindGoldZoneItemMFProbability) + 1;	
		break;
	}	
	
	//	B)�̾کǪ�����(���a���P���M�_��), �o�� mf�� :	
	switch(ItemMf.MonsterType)
	{	
	case NPC_KIND_NORMAL_MONSTER: 	
		mf = rp / 1;
		break;
	case NPC_KIND_HEADER_MONSTER:		
		mf = rp / 4;
		break;
	case NPC_KIND_BOSS_MONSTER:		
		mf = rp / 10;
		break;
	}

	//	C)�̾� mf �ȽT�w�]�k�ݩʪ��ƶq:
	if(mf >= 10001 && mf <= 100000)	item_mf = ITEM_MF_LEVEL_NONE;
	if(mf >= 5001  && mf <= 100000)	item_mf = ITEM_MF_LEVEL_ONE;
	if(mf >= 1001  && mf <= 5000)	item_mf = ITEM_MF_LEVEL_TWO;
	if(mf >= 101   && mf <= 1000)	item_mf = ITEM_MF_LEVEL_THREE;
	if(mf >= 11    && mf <= 100)	item_mf = ITEM_MF_LEVEL_FOUR;
	if(mf >= 2     && mf <= 10)		item_mf = ITEM_MF_LEVEL_CRYSTAL;
	if(mf == 1)						item_mf = ITEM_MF_LEVEL_GOD;
/*
		100000[0.1, 1]		->	�L������[�ݩ�(���q���~)
		10000[0.01, 0.1)	->	1�ت��[�ݩ�
		5000[0.005, 0.01)	->	2�ت��[�ݩ�
		1000[0.001, 0.005)	->  3�ت��[�ݩ�
		100[0.0001, 0.001)	->  4�ت��[�ݩ�
		10[0.00001, 0.0001)	->	�����˳�
		1[0, 0.00001)		->  ����		
*/
	return item_mf;
}
// --------------------------------------------------------------------------------------
// (6)��󵵴��˳ƩM����, �����q���~�򥻪��d�����[�]�k�ݩ�.
//    ����L���[�ݩʪ����~, �ݭn�q �m���~���[�ݩʪ�n���d��.
// --------------------------------------------------------------------------------------
void MakeItemProperty(TPOS_ITEM	*IT, TPOS_ITEM_MF ItemMf, int Mf, UHINT	tc_class)
{		
	char	land_type1_list[4][2] = {"0","1","2","3"};
	char	land_type2_list[6][3] = {"01","02","03","12","13","23"};
	char	land_type3_list[4][4] = {"012","013","023","123"};
	char	land_type4_list[1][5] = {"0123"};
	char	land_type_str[5];
	char	sea_type1_list[3][2] = {"0","1","2"};
	char	sea_type2_list[3][3] = {"01","02","12"};
	char	sea_type3_list[1][4] = {"012"};
	char	sea_type_str[4];
	int		i;	
	int		zone;	
	int		type_index;
	TPOS_ITEM	item;
	
	memset(land_type_str, 0x0, 5);
	memset(sea_type_str, 0x0, 4);
	memset(&item, 0x0, sizeof(TPOS_ITEM));
	memcpy(&item, IT, sizeof(TPOS_ITEM));
	// ���ھڮ��v�γ��a��X�i�H���ͪ��ݩʸs�ƶq
	switch(ItemMf.CurrentZoneType)
	{
	case CITY_NORMAL:
	case CITY_NEWBIE:
	case CITY_PK:	
	case CITY_BIRTH:
	case CITY_FINDGOLD:
	case FIELD_NORMAL:
	case FIELD_NEWBIE:
	case FIELD_PK:	
	case FIELD_BIRTH:			
	case FIELD_FINDGOLD:		
		zone = 0;
		break;			
	case SAIL_NORMAL:
	case SAIL_NEWBIE:
	case SAIL_PK:
	case SAIL_BIRTH:
	case SAIL_FINDGOLD:		
		zone = 1;
		break;
	}
	// �ھڥi�H���[���ݩʼƶq�}�l�H������
	switch(Mf)
	{
	case ITEM_MF_LEVEL_NONE:
		break;
	case ITEM_MF_LEVEL_ONE:
		if(zone == 0)
		{
			strcpy(land_type_str, land_type1_list[system_rand() % 4]);
			for(i = 0;i < Mf;i++)
			{
				type_index = TransferTypeIndex(land_type_str[i]);				
				RandomPropertyFromType(&item, type_index, zone, tc_class);
			}			
		}		
		if(zone == 1)
		{
			strcpy(sea_type_str, sea_type1_list[system_rand() % 3]);		
			for(i = 0;i < Mf;i++)
			{
				type_index = TransferTypeIndex(sea_type_str[i]);
				RandomPropertyFromType(&item, type_index, zone, tc_class);
			}			
		}		
		break;
	case ITEM_MF_LEVEL_TWO:
		if(zone == 0)
		{
			strcpy(land_type_str, land_type2_list[system_rand() % 6]);
			for(i = 0;i < Mf;i++)
			{			
				type_index = TransferTypeIndex(land_type_str[i]);
				RandomPropertyFromType(&item, type_index, zone, tc_class);
			}	
		}		
		if(zone == 1)
		{
			strcpy(sea_type_str, sea_type2_list[system_rand() % 3]);		
			for(i = 0;i < Mf;i++)
			{			
				type_index = TransferTypeIndex(sea_type_str[i]);
				RandomPropertyFromType(&item, type_index, zone, tc_class);
			}
		}
		break;
	case ITEM_MF_LEVEL_THREE:
		if(zone == 0)
		{
			strcpy(land_type_str, land_type3_list[system_rand() % 4]);
			for(i = 0;i < Mf;i++)
			{			
				type_index = TransferTypeIndex(land_type_str[i]);
				RandomPropertyFromType(&item, type_index, zone, tc_class);
			}
		}
		if(zone == 1)
		{
			strcpy(sea_type_str, sea_type3_list[0]);		
			for(i = 0;i < Mf;i++)
			{			
				type_index = TransferTypeIndex(sea_type_str[i]);
				RandomPropertyFromType(&item, type_index, zone, tc_class);
			}
		}
		break;
	case ITEM_MF_LEVEL_FOUR:
		if(zone == 0)
		{
			strcpy(land_type_str, land_type4_list[0]);
			for(i = 0;i < Mf;i++)
			{			
				type_index = TransferTypeIndex(land_type_str[i]);
				RandomPropertyFromType(&item, type_index, zone, tc_class);
			}
		}
		break;
	}
	memcpy(IT, &item, sizeof(TPOS_ITEM));
}
// --------------------------------------------------------------------------------------
// (8)�S�w�Ǫ��b���}�}����|�B�~���X�S�w�����Ȫ��~�C
//    �}����GM�x���C�b�}�s���a�ϫ�A�|�X�{���������_�ϡC
// --------------------------------------------------------------------------------------
SLONG CheckIsDropQuestItem(ULONG PlayerNo, ULONG NpcNo)  
{
	return FALSE;
}
// --------------------------------------------------------------------------------------
// ��X�Ǫ���F�誺���v
// --------------------------------------------------------------------------------------
int	FindMonsterDropItemProbability(TPOS_ITEM_MF ItemMf)
{
	int	probability = 0;
	
	switch(ItemMf.MonsterType)
	{	
	case NPC_KIND_NORMAL_MONSTER: 	
		probability = ItemMf.NPCTypeDropItemProbability[NPC_KIND_NORMAL_MONSTER];		
		break;
	case NPC_KIND_HEADER_MONSTER:		
		probability = ItemMf.NPCTypeDropItemProbability[NPC_KIND_HEADER_MONSTER];		
		break;
	case NPC_KIND_BOSS_MONSTER:		
		probability = ItemMf.NPCTypeDropItemProbability[NPC_KIND_BOSS_MONSTER];		
		break;
	}	
	return probability;
}
// --------------------------------------------------------------------------------------
// ��X���ݩʸs���X���ݩ�
// --------------------------------------------------------------------------------------
int	ReturnPropertyCountInType(int ZoneType, int PropertyType)
{
	int	return_value, i;

	return_value = -1;
	for(i = 0;i < MAX_PROPERTY_PER_TYPE;i++)
	{
		if(GameItemRandomBase.ZoneItemRandom[ZoneType].PropertyType[PropertyType].Property[i].IsHaveValue == 2)
		{
			return_value = i;	
			break;
		}				
	}								
	return return_value;
}
// --------------------------------------------------------------------------------------
// ��X�ݩ�
// --------------------------------------------------------------------------------------
void	RandomPropertyFromType(TPOS_ITEM *IT, int type_index, int zone, UHINT tc_class)
{
	int							RandomPropertyIndex[MAX_PROPERTY_PER_TYPE];
	int							j, property_count_in_type;		
	int							find_usable_property_count;
	int							random_property_index;	
	TPOS_ITEM					item;	
	
	find_usable_property_count = 0;
	random_property_index = 0;		
	memset(&item, 0x0, sizeof(TPOS_ITEM));
	memcpy(&item, IT, sizeof(TPOS_ITEM));
	// ��X���ݩʸs���X���ݩ�
	property_count_in_type = ReturnPropertyCountInType(zone, type_index);			
	if(property_count_in_type > 0)
	{
		for(j = 0;j < property_count_in_type;j ++)
		{	
			// �ˬd�ϥγ���O�_OK
			if(GameItemRandomBase.ZoneItemRandom[zone].PropertyType[type_index].Property[j].UseablePart & GameItemBase[IT->BaseID].Part)
			{
				// �ˬd�O�_�ŦXTC�ŧO
				if(tc_class >= GameItemRandomBase.ZoneItemRandom[zone].PropertyType[type_index].Property[j].TCLevel)
				{				
					RandomPropertyIndex[find_usable_property_count] = j;
					find_usable_property_count++;
				}								
			}				
		}
		if(find_usable_property_count > 0)
		{	
			random_property_index = system_rand() % find_usable_property_count;
			// (7)�̾ڪ��[�ݩ�, ���ͥX�Ӫ��~.	
			AddPropertyToItem(&item, zone, type_index, RandomPropertyIndex[random_property_index]);			
		}
	}	
	memcpy(IT, &item, sizeof(TPOS_ITEM));
}
// --------------------------------------------------------------------------------------
// �����~�[�W�ݩ�
// --------------------------------------------------------------------------------------
void	AddPropertyToItem(TPOS_ITEM *IT, int zone, int type_index, int property_index)
{
	UHINT	min_value, max_value, final_value;
	TPOS_ITEM	item;
	
	memcpy(&item, IT, sizeof(TPOS_ITEM));
	switch(zone)
	{
	case 0:
		switch(type_index)
		{
		case 0:
			item.IR.Land.Special1 = GameItemRandomBase.ZoneItemRandom[0].PropertyType[type_index].Property[property_index].PropertyNameIndex;			
			break;
		case 1:
			item.IR.Land.Special2 = GameItemRandomBase.ZoneItemRandom[0].PropertyType[type_index].Property[property_index].PropertyNameIndex;
			break;
		case 2:
			item.IR.Land.Type1 = GameItemRandomBase.ZoneItemRandom[0].PropertyType[type_index].Property[property_index].PropertyNameIndex;
			min_value = GameItemRandomBase.ZoneItemRandom[0].PropertyType[type_index].Property[property_index].MinValue;
			max_value = GameItemRandomBase.ZoneItemRandom[0].PropertyType[type_index].Property[property_index].MaxValue;
			final_value = min_value + (system_rand() % (max_value - min_value));
			item.IR.Land.Data1 = (char)final_value;
			break;
		case 3:
			item.IR.Land.Type2 = GameItemRandomBase.ZoneItemRandom[0].PropertyType[type_index].Property[property_index].PropertyNameIndex;
			min_value = GameItemRandomBase.ZoneItemRandom[0].PropertyType[type_index].Property[property_index].MinValue;
			max_value = GameItemRandomBase.ZoneItemRandom[0].PropertyType[type_index].Property[property_index].MaxValue;
			final_value = min_value + (system_rand() % (max_value - min_value));
			item.IR.Land.Data2 = (char)final_value;			
			break;
		}
		break;
	case 1:
		switch(type_index)
		{
		case 0:
			item.IR.Sea.Special1 = GameItemRandomBase.ZoneItemRandom[1].PropertyType[type_index].Property[property_index].PropertyNameIndex;
			break;
		case 1:
			item.IR.Sea.Type1 = GameItemRandomBase.ZoneItemRandom[1].PropertyType[type_index].Property[property_index].PropertyNameIndex;
			min_value = GameItemRandomBase.ZoneItemRandom[1].PropertyType[type_index].Property[property_index].MinValue;
			max_value = GameItemRandomBase.ZoneItemRandom[1].PropertyType[type_index].Property[property_index].MaxValue;
			final_value = min_value + (system_rand() % (max_value - min_value));
			item.IR.Sea.Data1 = (char)final_value;
			break;
		case 2:
			item.IR.Sea.Type2 = GameItemRandomBase.ZoneItemRandom[1].PropertyType[type_index].Property[property_index].PropertyNameIndex;
			min_value = GameItemRandomBase.ZoneItemRandom[1].PropertyType[type_index].Property[property_index].MinValue;
			max_value = GameItemRandomBase.ZoneItemRandom[1].PropertyType[type_index].Property[property_index].MaxValue;
			final_value = min_value + (system_rand() % (max_value - min_value));
			item.IR.Sea.Data2 = (char)final_value;
			break;		
		}
		break;
	}
	memcpy(IT, &item, sizeof(TPOS_ITEM));
}
// --------------------------------------------------------------------------------------
int	TransferTypeIndex(char type)
{
	int	return_value;

	return_value = 0;
	switch(type)
	{
	case '1':
		return_value = 1;
		break;
	case '2':
		return_value = 2;
		break;
	case '3':
		return_value = 3;
		break;
	case '4':
		return_value = 4;
		break;
	}
	return return_value;
}
// --------------------------------------------------------------------------------------