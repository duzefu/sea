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
/* �����ܶq                                                                                                 */
/************************************************************************************************************/
TPOS_ITEM_BS		GameItemBase[MAX_GAME_ITEM_BASES];	//�C�����~�򥻸�ƦC��
TPOS_ITEM_RANDOM_BS	GameItemRandomBase;				    //�C�����~�H�����[�ݩʰ򥻸�ƦC��
TPOS_ITEM_GS		ZoneItemGS[MAX_GAME_ITEMS];			//�C�����̦h���~�ƥ�


/************************************************************************************************************/
/* ���~�򥻼ƭȨ��                                                                                         */
/************************************************************************************************************/
SLONG	InitItemSystem(void)
{
	SLONG	result;

	//
	//��l�ƹC�����~�򥻪�
	//
	InitGameItemBase();
	result = LoadGameItemBase("data\\itembase.ini");
	if(0 != result)
		return	-1;
	//DebugLogGameItemBase();

	//
	//��l�ƹC�����~�H�����[�ݩʰ򥻪�
	//
	InitGameItemRandomBase();
	result = LoadGameItemRandomBase("data\\item_random.ini");
	if(0 != result)
		return	-1;
	//
	//��l�ƹC���ϰ�a�ϤW�����~
	//
	InitZoneItem();

	return	0;
}


void	FreeItemSystem(void)
{
}


//
//�\��: ��l�ƹC�����~�򥻼ƭȸ��
void	InitGameItemBase(void)
{
	memset(&GameItemBase[0], 0, sizeof(GameItemBase));
}


//
//�\��: �q��󤤸��J�C�����~�򥻼ƭȸ��
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

				//�s��: �Ĥ@�欰 BaseID, �P�ɧ@���C������.
				data->BaseID = (UHINT)data_index;

				//���J���Ωw�q�������ƾ�
				//�ϼнs��
				data->IconIndex = (SLONG)get_buffer_number(line, &index);
				//�W��
				strcpy((char *)data->Name, (const char*)get_buffer_string(line, &index));
				//���~����
				data->Type = (SLONG)get_buffer_number(line, &index);
				//TC����
				data->TcLevel = get_buffer_number(line, &index);
				//���c�ݨD
				data->NeedGoodEvil = get_buffer_number(line, &index);
				//�ϥΤH
				data->User = (ULONG)get_buffer_number(line, &index);
				//�A�γ���
				data->Part = (ULONG)get_buffer_number(line, &index);
				//�S���ݩ�
				data->Special = (ULONG)get_buffer_number(line, &index);
				//TODO:
				//���������˳�BaseID
				//data->CrystalID = (UHINT)get_buffer_number(line, &index);
				//���������˳�BaseID
				//data->ArtifactsID = (UHINT)get_buffer_number(line, &index);
				//���[�H���ݩ�(�A�Ω󵵴��˳�,�����˳�)
				//data->AddedAttrib = (UHINT)get_buffer_number(line, &index);

				switch(data->Type)
				{
				case ITEM_TYPE_GENERAL:
					break;

				case ITEM_TYPE_LAND_NORMAL:	//���a���~
					//�O�q�ݨD
					data->Land.MinNeedStr = (SLONG)get_buffer_number(line, &index);
					//��ı�ݨD
					data->Land.MinNeedIns = (SLONG)get_buffer_number(line, &index);
					//���O�ݨD
					data->Land.MinNeedWit = (SLONG)get_buffer_number(line, &index);
					//�B��ݨD
					data->Land.MinNeedLuck = (SLONG)get_buffer_number(line, &index);
					//�R���v
					data->Land.HitChance = (SLONG)get_buffer_number(line, &index);
					//���z�v
					data->Land.ExplodeRate = (SLONG)get_buffer_number(line, &index);
					//�򥻶ˮ`
					data->Land.BaseAtt = (SLONG)get_buffer_number(line, &index);
					//�򥻨��s�O
					data->Land.BaseDef = (SLONG)get_buffer_number(line, &index);
					//���`HP%
					data->Land.ResHpRate = (SLONG)get_buffer_number(line, &index);
					//���`MP%
					data->Land.ResMpRate = (SLONG)get_buffer_number(line, &index);
					break;

				case ITEM_TYPE_SEA_NORMAL:	//���v���~
					//����ŻݨD(�p, ��, �j, ��)
					data->Sea.NeedShipSize = (SLONG)get_buffer_number(line, &index);
					//�����O(0~255)
					data->Sea.CannonAttack = (SLONG)get_buffer_number(line, &index);
					//�����ˮ`�O(0~255)
					data->Sea.EmbolonAttack = (SLONG)get_buffer_number(line, &index);
					//�˥ҭ�(0~255)
					data->Sea.Armor = (SLONG)get_buffer_number(line, &index);
					//�R���v(0~255)
					data->Sea.HitChance = (SLONG)get_buffer_number(line, &index);
					//���ʳt��(�C, ��, ��)
					data->Sea.MoveSpeed = (SLONG)get_buffer_number(line, &index);
					//��V�O(�C, ��, ��)
					data->Sea.TurnSpeed = (SLONG)get_buffer_number(line, &index);
					//�Ӽu�q
					data->Sea.FireCost = (SLONG)get_buffer_number(line, &index);
					break;

				case ITEM_TYPE_TREASURE_MAP:	//���_��					
					break;

				case ITEM_TYPE_SEA_EXPENDABLE:	//���v���ӫ~
					break;

				case ITEM_TYPE_SEA_SAILOR:	//���v����
					break;

				case ITEM_TYPE_MONEY:	//����
					break;

				case ITEM_TYPE_MONSTER:	//�_�c��
					break;

				case ITEM_TYPE_DRUG:	//�ī~
					//�W�[�O�q(+/-)
					data->Drug.AddStr = (SLONG)get_buffer_number(line, &index);
					//�W�[��ı(+/-)
					data->Drug.AddIns = (SLONG)get_buffer_number(line, &index);
					//�W�[���z(+/-)
					data->Drug.AddWit = (SLONG)get_buffer_number(line, &index);
					//�W�[�B��(+/-)
					data->Drug.AddLuck = (SLONG)get_buffer_number(line, &index);
					//HP�^�_�v
					data->Drug.ResHpRate = (SLONG)get_buffer_number(line, &index);
					//MP�^�_�v
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
//�\��: (����)LOG�򥻪��~�C��
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
//�\��: ����C�����~�򥻼ƭȸ��
void	FreeGameItemBase(void)
{
	//Do nothing here.
}

//
//�\��: ��l�ƹC�����~�H�����[�ݩʼƭȸ��
void	InitGameItemRandomBase(void)
{
	memset(&GameItemRandomBase, 0x0, sizeof(TPOS_ITEM_RANDOM_BS));
}

//
//�\��: �q��󤤸��J�C�����~�H�����[�ݩʰ򥻼ƭȸ��
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
				//���J���Ωw�q�������ƾ�								
				//�ݩʧǸ�
				property_index = (UHINT)get_buffer_number(line, &index);
				//�W�ٯ���
				data->ZoneItemRandom[zone_type].PropertyType[property_type].Property[property_index].PropertyNameIndex
					= (UHINT)get_buffer_number(line, &index);
				//���L�ƭ�
				data->ZoneItemRandom[zone_type].PropertyType[property_type].Property[property_index].IsHaveValue
					= (UHINT)get_buffer_number(line, &index);
				//�A�γ���
				data->ZoneItemRandom[zone_type].PropertyType[property_type].Property[property_index].UseablePart
					= (ULONG)get_buffer_number(line, &index);
				//TC����
				data->ZoneItemRandom[zone_type].PropertyType[property_type].Property[property_index].TCLevel
					= (UHINT)get_buffer_number(line, &index);
				//�̤p�ƭ�
				data->ZoneItemRandom[zone_type].PropertyType[property_type].Property[property_index].MinValue
					= (UHINT)get_buffer_number(line, &index);
				//�̤j�ƭ�
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
//�\��: ����C�����~�H�����[�ݩʰ򥻼ƭȸ��
void	FreeGameItemRandomBase(void)
{
	//Do nothing here.
}
/************************************************************************************************************/
/* ���~�ާ@���                                                                                             */
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


//��o���~���W��
CHAR*	GetItemName(TPOS_ITEM *IT)
{
	return	(CHAR *)GameItemBase[IT->BaseID].Name;
}


//��o���~���Ϫ�s��
SLONG	GetItemIconIndex(TPOS_ITEM *IT)
{
	return	(SLONG)GameItemBase[IT->BaseID].IconIndex;
}


//��o���~������
SLONG	GetItemType(TPOS_ITEM *IT)
{
	return	(SLONG)GameItemBase[IT->BaseID].Type;
}


//��o���~���ϥΤH�d��w�q
ULONG	GetItemUser(TPOS_ITEM *IT)
{
	return	(ULONG)GameItemBase[IT->BaseID].User;
}


//��o���~���A�γ���w�q
ULONG	GetItemPart(TPOS_ITEM *IT)
{
	return	(ULONG)GameItemBase[IT->BaseID].Part;
}


//��o���~���S���ݩʩw�q
ULONG	GetItemSpecial(TPOS_ITEM *IT)
{
	return	(ULONG)GameItemBase[IT->BaseID].Special;
}

//�N���~�]�m���Ū����~
void	SetItemNone(TPOS_ITEM *IT)
{
	if(IT) memset(IT, 0, sizeof(*IT));
}


//�P�_���~�O�_���Ū����~
SLONG	IsItemNone(TPOS_ITEM *IT)
{
	SLONG	BaseID;

	BaseID = GetItemBaseID(IT);
	if(BaseID == ITEM_BASE_ID_NONE)
		return	TRUE;
	return	FALSE;
}


//�P�_���~�O�_�O����
SLONG	IsItemGold(TPOS_ITEM *IT)
{
	SLONG	BaseID;

	BaseID = GetItemBaseID(IT);
	if(BaseID == ITEM_BASE_ID_GOLD)
		return	TRUE;
	return	FALSE;
}


//�P�_���~�O�_�O�Ǫ�(�_�c��)
SLONG	IsItemMonster(TPOS_ITEM *IT)
{
	SLONG	BaseID;

	BaseID = GetItemBaseID(IT);
	if(BaseID == ITEM_BASE_ID_MONSTER)
		return	TRUE;
	return	FALSE;
}


//�P�_���~�O�_�O���w¾�~���w�ʧO���H���i�ϥΪ�
SLONG	IsItemForMe(TPOS_ITEM *IT, SLONG Career, SLONG Sex)
{
	ULONG	ItemUser, CheckUser;

	//�ˬd���~�O�_�O�ۤv�i�H�ϥΪ�
	ItemUser = GetItemUser(IT);
	CheckUser = MakeUserDescriptionByCareerSex(Career, Sex);
	if( (CheckUser & ItemUser) != CheckUser)
		return	FALSE;
	return	TRUE;
}


//�P�_���~�O�_�O���w¾�~���w�ʧO���H�����Y���˳�
SLONG	IsItemForMyHead(TPOS_ITEM *IT, SLONG Career, SLONG Sex)
{
	ULONG	CheckUser, ItemUser, ItemPart;

	//�ˬd���~�O���O�A�Ω��Y�W
	ItemPart = GetItemPart(IT);
	if(! (ItemPart & ITEM_PART_HUMAN_HEAD))
		return	FALSE;

	//�ˬd���~�O�_�O�ۤv�i�H�ϥΪ�
	ItemUser = GetItemUser(IT);
	CheckUser = MakeUserDescriptionByCareerSex(Career, Sex);
	if( (CheckUser & ItemUser) != CheckUser)
		return	FALSE;

	return	TRUE;
}


//�P�_���~�O�_�O���w¾�~���w�ʧO���H�����V���˳�
SLONG	IsItemForMyNeck(TPOS_ITEM *IT, SLONG Career, SLONG Sex)
{
	ULONG	CheckUser, ItemUser, ItemPart;

	//�ˬd���~�O���O�A�Ω��V��
	ItemPart = GetItemPart(IT);
	if(! (ItemPart & ITEM_PART_HUMAN_NECK))
		return	FALSE;

	//�ˬd���~�O�_�O�ۤv�i�H�ϥΪ�
	ItemUser = GetItemUser(IT);
	CheckUser = MakeUserDescriptionByCareerSex(Career, Sex);
	if( (CheckUser & ItemUser) != CheckUser)
		return	FALSE;

	return	TRUE;
}



//�P�_���~�O�_�O���w¾�~���w�ʧO���H��������˳�
SLONG	IsItemForMyBody(TPOS_ITEM *IT, SLONG Career, SLONG Sex)
{
	ULONG	CheckUser, ItemUser, ItemPart;

	//�ˬd���~�O���O�A�Ω���
	ItemPart = GetItemPart(IT);
	if(! (ItemPart & ITEM_PART_HUMAN_BODY))
		return	FALSE;

	//�ˬd���~�O�_�O�ۤv�i�H�ϥΪ�
	ItemUser = GetItemUser(IT);
	CheckUser = MakeUserDescriptionByCareerSex(Career, Sex);
	if( (CheckUser & ItemUser) != CheckUser)
		return	FALSE;

	return	TRUE;
}


//�P�_���~�O�_�O���w¾�~���w�ʧO���H�����y���˳�
SLONG	IsItemForMyWaist(TPOS_ITEM *IT, SLONG Career, SLONG Sex)
{
	ULONG	CheckUser, ItemUser, ItemPart;

	//�ˬd���~�O���O�A�Ω�y��
	ItemPart = GetItemPart(IT);
	if(! (ItemPart & ITEM_PART_HUMAN_WAIST))
		return	FALSE;

	//�ˬd���~�O�_�O�ۤv�i�H�ϥΪ�
	ItemUser = GetItemUser(IT);
	CheckUser = MakeUserDescriptionByCareerSex(Career, Sex);
	if( (CheckUser & ItemUser) != CheckUser)
		return	FALSE;

	return	TRUE;
}


//�P�_���~�O�_�O���w¾�~���w�ʧO���H������ø˳�
SLONG	IsItemForMyWrist(TPOS_ITEM *IT, SLONG Career, SLONG Sex)
{
	ULONG	CheckUser, ItemUser, ItemPart;

	//�ˬd���~�O���O�A�Ω���
	ItemPart = GetItemPart(IT);
	if(! (ItemPart & ITEM_PART_HUMAN_WRIST))
		return	FALSE;

	//�ˬd���~�O�_�O�ۤv�i�H�ϥΪ�
	ItemUser = GetItemUser(IT);
	CheckUser = MakeUserDescriptionByCareerSex(Career, Sex);
	if( (CheckUser & ItemUser) != CheckUser)
		return	FALSE;

	return	TRUE;
}


//�P�_���~�O�_�O���w¾�~���w�ʧO���H�����Z���˳�
SLONG	IsItemForMyWeapon(TPOS_ITEM *IT, SLONG Career, SLONG Sex)
{
	ULONG	CheckUser, ItemUser, ItemPart;

	//�ˬd���~�O���O�A�Ω�Z������
	ItemPart = GetItemPart(IT);
	if(! (ItemPart & ITEM_PART_HUMAN_WEAPON))
		return	FALSE;

	//�ˬd���~�O�_�O�ۤv�i�H�ϥΪ�
	ItemUser = GetItemUser(IT);
	CheckUser = MakeUserDescriptionByCareerSex(Career, Sex);
	if( (CheckUser & ItemUser) != CheckUser)
		return	FALSE;

	return	TRUE;
}


//�P�_���~�O�_�O���w¾�~���w�ʧO���H���������˳�
SLONG	IsItemForMyFeet(TPOS_ITEM *IT, SLONG Career, SLONG Sex)
{
	ULONG	CheckUser, ItemUser, ItemPart;

	//�ˬd���~�O���O�A�Ω󨬳�
	ItemPart = GetItemPart(IT);
	if(! (ItemPart & ITEM_PART_HUMAN_FEET))
		return	FALSE;

	//�ˬd���~�O�_�O�ۤv�i�H�ϥΪ�
	ItemUser = GetItemUser(IT);
	CheckUser = MakeUserDescriptionByCareerSex(Career, Sex);
	if( (CheckUser & ItemUser) != CheckUser)
		return	FALSE;

	return	TRUE;
}


//�P�_���~�O�_�O���w¾�~���w�ʧO���H������M�˳�
SLONG	IsItemForMyGlove(TPOS_ITEM *IT, SLONG Career, SLONG Sex)
{
	ULONG	CheckUser, ItemUser, ItemPart;

	//�ˬd���~�O���O�A�Ω��M
	ItemPart = GetItemPart(IT);
	if(! (ItemPart & ITEM_PART_HUMAN_GLOVE))
		return	FALSE;

	//�ˬd���~�O�_�O�ۤv�i�H�ϥΪ�
	ItemUser = GetItemUser(IT);
	CheckUser = MakeUserDescriptionByCareerSex(Career, Sex);
	if( (CheckUser & ItemUser) != CheckUser)
		return	FALSE;

	return	TRUE;
}


//�P�_���~�O�_�O���w¾�~���w�ʧO���H�����˹���
SLONG	IsItemForMyDeck(TPOS_ITEM *IT, SLONG Career, SLONG Sex)
{
	ULONG	CheckUser, ItemUser, ItemPart;

	//�ˬd���~�O���O�A�Ω�˹�����
	ItemPart = GetItemPart(IT);
	if(! (ItemPart & ITEM_PART_HUMAN_DECK))
		return	FALSE;

	//�ˬd���~�O�_�O�ۤv�i�H�ϥΪ�
	ItemUser = GetItemUser(IT);
	CheckUser = MakeUserDescriptionByCareerSex(Career, Sex);
	if( (CheckUser & ItemUser) != CheckUser)
		return	FALSE;

	return	TRUE;
}


//�P�_���~�O�_�O���w¾�~���w�ʧO���H�����y�]�˳�(�ֱ���)
SLONG	IsItemForMySash(TPOS_ITEM *IT, SLONG Career, SLONG Sex)
{
	ULONG	CheckUser, ItemUser, ItemPart;

	//�ˬd���~�O���O�A�Ω�y�]
	ItemPart = GetItemPart(IT);
	if(! (ItemPart & ITEM_PART_HUMAN_SASH))
		return	FALSE;

	//�ˬd���~�O�_�O�ۤv�i�H�ϥΪ�
	ItemUser = GetItemUser(IT);
	CheckUser = MakeUserDescriptionByCareerSex(Career, Sex);
	if( (CheckUser & ItemUser) != CheckUser)
		return	FALSE;

	return	TRUE;
}


//�P�_���~��_����
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


//�P�_���~��_��c��
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


//�P�_���~��_���ICQ�ǿ�
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


//�P�_���~��_��洫
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

//�P�_���~�O�_���H��
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


//�P�_���~��_���ᱼ��
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


//�P�_���~��_�s�⪫�~
SLONG	IsItemNewbie(TPOS_ITEM *IT)
{
	ULONG	Special;

	Special = GetItemSpecial(IT);
	if(Special & ITEM_SPECIAL_NEWBIE)
		return	TRUE;
	return	FALSE;
}


//�P�_���~��_�ϥ�
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


//�P�_���~��_�˳�
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
/* �C���ϰ줤�a�W���~�������                                                                               */
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
//��l�ưϰ줤�a�Ϫ��~���
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


//���m�ϰ줤�a�ϩҦ����~���
void	ResetZoneItem(void)
{
	InitZoneItem();
}


//�M���ϰ�a�ϤW�@�Ӫ��~���
void	ClearOneZoneItem(SLONG index)
{
	ZoneItemGS[index].Flag = 0;
	SetItemNone(&ZoneItemGS[index].Item);
	ZoneItemGS[index].X = 0;
	ZoneItemGS[index].Y = 0;
	ZoneItemGS[index].Next = -1;
}


//�P�_�ϰ줤�a�Ϫ��~���O�_���Q�ϥ�
SLONG	IsZoneItemUnused(SLONG index)
{
	if(ZoneItemGS[index].Flag == 0)
		return	TRUE;
	return	FALSE;
}




//�M��i�H�ϥΪ��ϰ�a�Ϫ��~���
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


//�b�ϰ�a�ϤW�K�[�@�Ӫ��~
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


//�q�ϰ�a�ϤW�R���@�Ӫ��~
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


//����a�Ϫ��~�y��
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
//�\��: ��o�a�ϤW��e��m�ҩ�m�����~, 
//��^: �p�G�S���o�{���~, ��^-1, �_�h, �N���~�ƭȦs��bIT��, 
//	    �åB��^�Ӫ��~�b�a�Ϫ��~�C�����ޭ�.
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
//�\��: �p�⳰�a�˳ƪ��~�����m�O
//      ���m�O = ���~��¦���m�O * ( 1 + �[�j���m %) + �W�[���m�O
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
//�\��: ��o���~����ܦʤ���
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

