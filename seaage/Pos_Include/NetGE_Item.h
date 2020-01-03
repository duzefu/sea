/*
**	NetGE_Item.h
**	Item functions header.
**
**	Jack, 2002.11.30
**
**	Modify by Hawke 2003.04.01
**
**	Jack, 2003.5.8.
**		-- Modified struct define TPOS_ITEM for add item-quest related data.
**		-- Added two functions for access item-quest:
**			(1) void	SetItemQuestIndex(TPOS_ITEM *IT, SLONG lIndex);
**			(2) SLONG	GetItemQuestIndex(TPOS_ITEM *IT);
**
**	Hawke, 2003.5.21.
**		-- Added functions:
**			(1)	void	SetTreasureMapItemIndex(TPOS_ITEM *IT, UCHAR uIndex);
**			(2)	UCHAR	GetTreasureMapItemIndex(TPOS_ITEM *IT);
**		-- Added drug item functions.	
*/
#pragma once


// DEFINES ///////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//-----------------------------------------------
//
#define	MAX_GAME_ITEM_BASES					4096	//�C�����򥻪��~�ؼ�
#define	HEAD_GAME_ITEMS						1		//�Χ@�Y�`�I���D�㶵, ���p��C���a�ϼƥ�
#define	MAX_GAME_ITEMS						10240	//�C�����Ҧ��a�ϤW�P�ɦs�b���̦h���~�ƥ�
#define	MAX_ZONE_GS_ITEMS					(MAX_GAME_ITEMS - HEAD_GAME_ITEMS)	//��Ӱϰ쪺�a�W�̤j���~�ƥ�
#define	ZONE_ITEM_LIFE_TICKS				(15 * 20 * 60)	//�a�W���~�����ͩR��(15����)
#define	ZONE_ITEM_OWNER_TICKS				(5 * 20 * 60)	//�a�W���~�u��Q�S�w�H�B�����ɶ�(5����)

#define	MAX_PROPERTY_PER_ITEM				4		//���~�̤j�H���ݩʼƥ�
#define	MAX_PROPERTY_PER_TYPE				64		//�C�دS���ݩʸs���ݩʼƥ�

#define	ITEM_STAY_WIDTH						64	//���~�b�a�ϤW���ڰϰ쪺�e��
#define	ITEM_STAY_HEIGHT					40	//���~�b�a�ϤW���ڰϰ쪺����

//
//�D�������]�w(@ POS_ITEM_BS)
//
#define	ITEM_TYPE_GENERAL					0	//�`�W���~(�O�d)
#define	ITEM_TYPE_LAND_NORMAL				1	//���a���~
#define	ITEM_TYPE_SEA_NORMAL				2	//���v���~
#define	ITEM_TYPE_TREASURE_MAP				3	//���_��
#define	ITEM_TYPE_SEA_EXPENDABLE			4	//���v���ӫ~
#define	ITEM_TYPE_SEA_SAILOR				5	//���v����
#define	ITEM_TYPE_MONEY						6	//������T
#define	ITEM_TYPE_MONSTER					7	//�_�c��
#define	ITEM_TYPE_DRUG						8	//�ī~

//
//�D���ID�]�w
//
#define	ITEM_BASE_ID_NONE					0		//��ܬƻ򪫫~���S��
#define	ITEM_BASE_ID_GOLD					200		//����
#define	ITEM_BASE_ID_MONSTER				201		//�_�c��
#define	ITEM_BASE_ID_NORMAL_START			300		//�`�W���~ID���_�l��


//
//�D��A�γ���w�q
//
#define	ITEM_PART_HUMAN_HEAD				0x00000001	//�H���Y�W�˳�
#define	ITEM_PART_HUMAN_NECK				0x00000002	//�H���V���˳�
#define	ITEM_PART_HUMAN_BODY				0x00000004	//�H������˳�
#define	ITEM_PART_HUMAN_WAIST				0x00000008	//�H���y���˳�
#define	ITEM_PART_HUMAN_WRIST				0x00000010	//�H�������˳�
#define	ITEM_PART_HUMAN_WEAPON				0x00000020	//�H���Z���˳�
#define	ITEM_PART_HUMAN_FEET				0x00000040	//�H�������˳�
#define	ITEM_PART_HUMAN_DECK				0x00000080	//�H���˹���˳�
#define	ITEM_PART_HUMAN_SASH				0x00000100	//�H���y�]�˳�(�ֱ���)
#define	ITEM_PART_HUMAN_GLOVE				0x00000200	//�H����M�˳�


//
//�D��S���ݩʩw�q
//
#define ITEM_SPECIAL_DISCARDABLE			0x00000001  //�O�_����
#define ITEM_SPECIAL_SELLABLE				0x00000002  //�O�_��c��
#define ITEM_SPECIAL_TRANSFERABLE			0x00000004  //�O�_���ICQ�ǿ�
#define ITEM_SPECIAL_SWAPABLE				0x00000008  //�O�_��洫
#define ITEM_SPECIAL_KEEPSAKE				0x00000010  //�O�_���H��
#define ITEM_SPECIAL_DEADDROP				0x00000020  //�O�_�঺�ᱼ��
#define ITEM_SPECIAL_NEWBIE					0x00000040  //�O�_�O�s�⪫�~
#define ITEM_SPECIAL_USABLE					0x00000080  //�O�_��ϥ�
#define ITEM_SPECIAL_FIXABLE				0x00000100  //�O�_��˳�
#define	ITEM_SPECIAL_CRYSTAL				0x40000000	//�O�_�������˳�
#define	ITEM_SPECIAL_ARTIFACTS				0x80000000	//�O�_������

//
//---------------------------------------------------------------------------
//���a���~�H���ݩʩw�q IR
//---------------------------------------------------------------------------
//
//���a���~�S���ݩʩw�q(SPECIAL 1)
//
#define	LAND_ITEM_SPECIAL1_NONE							0	//�L�����ݩ�
#define	LAND_ITEM_SPECIAL1_ACC_MUSE						1	//�[�t�߷Q
#define	LAND_ITEM_SPECIAL1_ANTI_BAD						2	//�t�����A�K��
#define	LAND_ITEM_SPECIAL1_LEVEL_ADD_ATT				3	//��󵥯żW�[�ˮ`
#define	LAND_ITEM_SPECIAL1_LEVEL_ADD_DEF				4	//��󵥯żW�[���m
#define	LAND_ITEM_SPECIAL1_LEVEL_ADD_MAX_HP				5	//��󵥯żW�[�ͩR�W��
#define	LAND_ITEM_SPECIAL1_LEVEL_ADD_MAX_MP				6	//��󵥯żW�[�]�O�W��
#define	LAND_ITEM_SPECIAL1_NEVER_SHATTER				7	//�ä��i�l
#define	LAND_ITEM_SPECIAL1_LOWER_DAMAGE					8	//��֪��z�ˮ`10%
//
//���a���~�S���ݩʩw�q(SPECIAL 2)
//
#define	LAND_ITEM_SPECIAL2_NONE							0	//�L�����ݩ�
#define	LAND_ITEM_SPECIAL2_LOWER_REQUEST				1	//���C�ݨD20%
#define	LAND_ITEM_SPECIAL2_BE_TORTOISE					2	//��2%�ܯQ�t�ݩ�
#define	LAND_ITEM_SPECIAL2_BE_PIG						3	//��2%�ܽ��ݩ�
#define LAND_ITEM_SPECIAL2_SLEEP						4   //��2%�����ݩ�
#define	LAND_ITEM_SPECIAL2_ADD_SKILL_LEVEL				5	//���a�ޯ൥�� + 1
#define	LAND_ITEM_SPECIAL2_ADD_GENERAL_SKILL_LEVEL		6	//�����ޯ൥�� + 1
#define	LAND_ITEM_SPECIAL2_ADD_SWORDER_SKILL_LEVEL		7	//�C�ȧޯ൥�� + 1
#define	LAND_ITEM_SPECIAL2_ADD_EXPLORER_SKILL_LEVEL		8	//���I�a�ޯ൥�� + 1
#define	LAND_ITEM_SPECIAL2_ADD_THIEF_SKILL_LEVEL		9	//�p���ޯ൥�� + 1
#define	LAND_ITEM_SPECIAL2_ADD_TRADER_SKILL_LEVEL		10	//�ӤH�ޯ൥�� + 1
#define	LAND_ITEM_SPECIAL2_ADD_CLERIC_SKILL_LEVEL		11	//���v�ޯ൥�� + 1
#define	LAND_ITEM_SPECIAL2_ADD_HOROSCOPER_SKILL_LEVEL	12	//�e�P�N�h�ޯ൥�� + 1
#define	LAND_ITEM_SPECIAL2_ADD_SMALL_ATTACK_RATIO		13	//�R���v +5
#define	LAND_ITEM_SPECIAL2_ADD_MIDDLE_ATTACK_RATIO		14	//�R���v +10
#define	LAND_ITEM_SPECIAL2_ADD_LARGE_ATTACK_RATIO		15	//�R���v +15
//
//���a���~�ƭ������w�q(TYPE 1)
//
#define	LAND_ITEM_DATATYPE1_NONE						0	//�L
#define	LAND_ITEM_DATATYPE1_ADD_MAX_HP					1	//�W�[�ͩR�W��
#define	LAND_ITEM_DATATYPE1_ADD_MAX_MP					2	//�W�[�]�k�W��
#define	LAND_ITEM_DATATYPE1_ADD_DEF						3	//�W�[���m�O
#define	LAND_ITEM_DATATYPE1_ENHANCE_DEF					4	//�[�j���m
#define	LAND_ITEM_DATATYPE1_ADD_RESIST					5	//�W�[���
//
//���a���~�ƭ������w�q(TYPE 2)
//
#define	LAND_ITEM_DATATYPE2_NONE						0	//�L
#define	LAND_ITEM_DATATYPE2_ADD_ATT						1	//�W�[�����O
#define	LAND_ITEM_DATATYPE2_ENHANCE_ATT					2	//�[�j����
#define	LAND_ITEM_DATATYPE2_ADD_MAGIC_HURT				3	//�W�[�]�k�ˮ`
#define	LAND_ITEM_DATATYPE2_ADD_SPECIAL_HURT			4	//�W�[�S��ˮ`
#define	LAND_ITEM_DATATYPE2_CRITICAL_STRIKE				5	//�|�ߤ@��	
//
//---------------------------------------------------------------------------
//���v���~�H���ݩʩw�q
//---------------------------------------------------------------------------
//
//���v���~�S���ݩʩw�q
//
#define	SEA_ITEM_SPECIAL1_NONE							0	//�L�����ݩ�
#define	SEA_ITEM_SPECIAL1_NEVER_SHATTER					1	//�ä��i�l
#define	SEA_ITEM_SPECIAL1_ADD_SMALL_SPEED				2	//��t + 5
#define	SEA_ITEM_SPECIAL1_ADD_MIDDLE_SPEED				3	//��t + 10
#define	SEA_ITEM_SPECIAL1_ADD_LARGE_SPEED				4	//��t + 15
#define	SEA_ITEM_SPECIAL1_ADD_SMALL_TURN				5	//��t + 5
#define	SEA_ITEM_SPECIAL1_ADD_MIDDLE_TURN				6	//��t + 10
#define	SEA_ITEM_SPECIAL1_ADD_LARGE_TURN				7	//��t + 15
#define	SEA_ITEM_SPECIAL1_REDUCE_SMALL_FOOD				8	//�������� -10%
#define	SEA_ITEM_SPECIAL1_REDUCE_MIDDLE_FOOD			9	//�������� -15%
#define	SEA_ITEM_SPECIAL1_REDUCE_LARGE_FOOD				10	//�������� -20%
#define	SEA_ITEM_SPECIAL1_REDUCE_SMALL_POWDER			11	//���Į��� -1
#define	SEA_ITEM_SPECIAL1_REDUCE_MIDDLE_POWDER			12	//���Į��� -2
#define	SEA_ITEM_SPECIAL1_REDUCE_LARGE_POWDER			13	//���Į��� -3
//
//���v���~�ƭ������w�q(TYPE 1)
//
#define	SEA_ITEM_DATATYPE1_NONE							0	//�L
#define	SEA_ITEM_DATATYPE1_ADD_ATTACK_RATIO				1	//�W�[�R���v
#define	SEA_ITEM_DATATYPE1_ADD_DAMAGE					2	//�W�[�ˮ`�O
#define	SEA_ITEM_DATATYPE1_ENHANCE_DAMAGE				3	//�[�j�ˮ`�O
#define	SEA_ITEM_DATATYPE1_ADD_EMBOLON_DAMAGE			4	//�W�[�����ˮ`�O
#define	SEA_ITEM_DATATYPE1_ADD_SAILOR_DAMAGE			5	//�W�[����ˮ`�O
//
//���v���~�ƭ������w�q(TYPE 2)
//
#define	SEA_ITEM_DATATYPE2_NONE							0	//�L
#define	SEA_ITEM_DATATYPE2_ADD_ARMOR					1	//�W�[�˥ҭ�
#define	SEA_ITEM_DATATYPE2_ENHANCE_ARMOR				2	//�[�j�˥ҭ�
#define	SEA_ITEM_DATATYPE2_REDUCE_DAMAGE				3	//���C�ˮ`

//
// STRUCTURES ////////////////////////////////////////////////////////////////////////////////////////////////////////
//
#pragma	pack(push)
#pragma	pack(1)
//
//�D��򥻼ƭȩw�q(BS = Base)
//
typedef	struct POS_ITEM_BS 
{
	UHINT	BaseID;			//�򥻪�ID
	SLONG	IconIndex;		//�ϼнs��
	CHAR	Name[32];		//�W��
	SLONG	Type;			//�D�����O
	SLONG	TcLevel;		//TC����
	SLONG	NeedGoodEvil;	//���c�ݨD
	ULONG	User;			//�ϥΤH
	ULONG	Part;			//�A�γ���
	ULONG	Special;		//�S���ݩ�
	UHINT	CrystalID;		//���������˳�BaseID
	UHINT	ArtifactsID;	//���������˳�BaseID
	ULONG	AddedAttrib;	//���[�H���ݩ�(�A�Ω󵵴��˳�,�����˳�)
	//
	union
	{
		struct  //���a�˳ƾA��
		{
			SLONG	MinNeedStr;		//�O�q�ֻ̤ݨD
			SLONG	MinNeedIns;		//��ı�ֻ̤ݨD
			SLONG	MinNeedWit;		//���z�ֻ̤ݨD
			SLONG	MinNeedLuck;	//�B��ֻ̤ݨD
			SLONG	HitChance;		//�R���v
			SLONG	ExplodeRate;	//���z�v
			SLONG	BaseAtt;		//�򥻧����O
			SLONG	BaseDef;		//�򥻨��m�O
			SLONG	ResHpRate;		//HP��_�v
			SLONG	ResMpRate;		//MP��_�v
		} Land;

		struct  //���v�˳ƾA��
		{
			SLONG	NeedShipSize;	//����ŻݨD(�p, ��, �j, ��)
			SLONG	CannonAttack;	//�����O(0~255)
			SLONG	EmbolonAttack;	//�����ˮ`�O(0~255)
			SLONG	Armor;			//�˥ҭ�(0~255)
			SLONG	HitChance;		//�R���v(0~255)
			SLONG	MoveSpeed;		//���ʳt��(�C, ��, ��)
			SLONG	TurnSpeed;		//��V�O(�C, ��, ��)
			SLONG	FireCost;		//�Ӽu�q
			SLONG	Reserved[2];	//�O�d
		} Sea;

		struct  //�ī~�A��
		{
			SLONG	AddStr;			//�W�[�O�q(+/-)
			SLONG	AddIns;			//�W�[��ı(+/-)
			SLONG	AddWit;			//�W�[���z(+/-)
			SLONG	AddLuck;		//�W�[�B��(+/-)
			SLONG	ResHpRate;		//HP�^�_�v
			SLONG	ResMpRate;		//MP�^�_�v
			SLONG	Reserved[4];	//�O�d
		} Drug;
	};
} TPOS_ITEM_BS, *LPTPOS_ITEM_BS;


//
//�D�㪺�H���ݩ�
//
typedef	union	POS_ITEM_RANDOM
{
	struct	//�@���(�ī~, �ӫ~)
	{
		UCHAR	Attr[5];			//5���ݩ�
	} General;

	struct  //���a���~
	{
		union
		{
			struct  
			{
				UHINT	Special1 : 4;	//�S���ݩ�1
				UHINT	Special2 : 4;	//�S���ݩ�2
				UHINT	Reserved : 8;	//�O�d����
			};
			UHINT	Specials;			//�S���ݩ�
		};
		union
		{
			struct  
			{
				UCHAR	Type1 : 4;		//�ƭ�����1
				UCHAR	Type2 : 4;		//�ƭ�����2
			};
			UCHAR	Types;
		};
		UCHAR	Data1;				//�ƭ�1(0~255)
		UCHAR	Data2;				//�ƭ�2(0~255)
	} Land;

	struct  //���v���~
	{
		union
		{
			struct  
			{
				UHINT	Special1 : 4;	//�S���ݩ�1
				UHINT	Reserved : 12;	//�O�d����
			};
			UHINT	Specials;
		};
		union
		{
			struct  
			{
				UCHAR	Type1 : 4;		//�ƭ�����1
				UCHAR	Type2 : 4;		//�ƭ�����2
			};
			UCHAR	Types;
		};
		UCHAR	Data1;				//�ƭ�1(0~255)
		UCHAR	Data2;				//�ƭ�2(0~255)
	} Sea;

	struct  //���_�ϸ�T
	{
		UHINT	WholePieces;		//�`���Ƽлx
		UHINT	CurrentPieces;		//��e���Ƽлx(�C��BIT��ܤ@���H��, �̦h16��)
		UCHAR	Index;				//�۹����_�èƥ󪺽s��

	} TreasureMap;

	struct	//���v���ӫ~
	{
		UHINT	Count;				//�ƶq(1~1000)
		UCHAR	Reserved[3];		//�O�d
	} SeaExpendable;

	struct	//���v����
	{
		UCHAR	TotalCount;			//�����`�q
		UCHAR	HealthCount;		//���d����q
		UCHAR	Reserved[3];		//�O�d
	} Sailor;

	struct	//������T
	{
		ULONG	Amount;				//�����ƶq
		UCHAR	Reserved[1];		//�O�d
	} Money;

	struct	//�_�c��
	{
		UCHAR	Level;				//�X�{�Ǫ�������(1~100)
		UCHAR	Style;				//�X�{�Ǫ������A
		UCHAR	Reserved[3];		//�O�d
	} Monster;
	
} TPOS_ITEM_RANDOM, *LPTPOS_ITEM_RANDOM;

typedef	struct  POS_ITEM_RANDOM_PROPERTY
{
	UHINT	PropertyNameIndex;		//�ݩʦW�ٯ���
	UHINT	IsHaveValue;			//���L�ƭ�  0 - �L , 1 -��
	ULONG	UseablePart;			//�A�γ���
	UHINT	TCLevel;				//TC �ŧO
	UHINT	MinValue;				//�̤p��
	UHINT	MaxValue;				//�̤j��
}TPOS_ITEM_RANDOM_PROPERTY;

typedef struct  POS_ITEM_RANDOM_PROPERTY_TYPE
{		
	TPOS_ITEM_RANDOM_PROPERTY	Property[MAX_PROPERTY_PER_TYPE];
}TPOS_ITEM_RANDOM_PROPERTY_TYPE;

typedef struct  POS_ITEM_RANDOM_BS_ZONE
{
	TPOS_ITEM_RANDOM_PROPERTY_TYPE PropertyType[MAX_PROPERTY_PER_ITEM];
}TPOS_ITEM_RANDOM_BS_ZONE;

typedef struct	POS_ITEM_RANDOM_BS
{
	TPOS_ITEM_RANDOM_BS_ZONE	ZoneItemRandom[2];	// �ϰ�  0 - ���a , 1 - ���v
}TPOS_ITEM_RANDOM_BS;

//
//�D����骺�w�q
//
typedef	struct  POS_ITEM
{
	UHINT	BaseID;		//���~�򥻽s��
	UCHAR	Hp;			//���~���@�[��
	union
	{
		ULONG	ID;		//���~���ߤ@ID(�ثe����)
		struct  
		{
			UCHR	QuestIndex;		//�������Ƚs��(0���D���Ȫ��~, ��L��ܹ������Ȫ����~)
			CHAR	Reserved[3];	//�O�d
		};
	};
	
	TPOS_ITEM_RANDOM	IR;			//���~���H���ݩ�
} TPOS_ITEM, *LPTPOS_ITEM;


//
//�ϰ�a�ϤW�D��ƭȵ��c(GS = Ground State)
//
typedef	struct POS_ITEM_GS
{
    //-------------------------------
    union 
    {
        SLONG   Flag;			//�ϥμлx
        SLONG   Tail;			//���a�ϹD�����������
    };
    SLONG		Next;			//���~����
    //-------------------------------
	union
	{
		SLONG	X;				//�a�Ϯy�� X
		SLONG	Total;			//���a�Ϫ��D���`�ƥ�
	};
	SLONG		Y;				//�a�Ϯy�� Y
	SLONG		State;			//��e���A
	SLONG		Life;			//�ͩR��
	SLONG		Frame;			//�v���V��
	CHAR		Owner[32];		//�֦��H
	TPOS_ITEM	Item;			//���~
} TPOS_ITEM_GS, *LPTPOS_ITEM_GS;


#pragma	pack(pop)

// GLOBALS ///////////////////////////////////////////////////////////////////////////////////////////////////////////
//
extern	TPOS_ITEM_BS		GameItemBase[MAX_GAME_ITEM_BASES];	//�C�����~�򥻸�ƦC��
extern	TPOS_ITEM_RANDOM_BS	GameItemRandomBase;					//�C�����~�H�����[�ݩʰ򥻸�ƦC��
extern	TPOS_ITEM_GS		ZoneItemGS[MAX_GAME_ITEMS];			//�C�����̦h���~�ƥ�


// FUNCTIONS /////////////////////////////////////////////////////////////////////////////////////////////////////////
//
extern	SLONG	InitItemSystem(void);
extern	void	FreeItemSystem(void);
//
extern	void	InitGameItemBase(void);
extern	SLONG	LoadGameItemBase(char *FileName);
extern	void	DebugLogGameItemBase(void);
extern	void	FreeGameItemBase(void);
//
extern	void	InitGameItemRandomBase(void);
extern	SLONG	LoadGameItemRandomBase(char *FileName);
extern	void	FreeGameItemRandomBase(void);
//
extern	void	SetItemBaseID(TPOS_ITEM *IT, UHINT uBaseID);
extern	UHINT	GetItemBaseID(TPOS_ITEM *IT);
extern	void	SetItemHp(TPOS_ITEM *IT, SLONG lHp);
extern	SLONG	GetItemHp(TPOS_ITEM *IT);
extern	void	SetItemID(TPOS_ITEM *IT, ULONG ID);
extern	ULONG	GetItemID(TPOS_ITEM *IT);
extern	CHAR *	GetItemName(TPOS_ITEM *IT);
extern	SLONG	GetItemIconIndex(TPOS_ITEM *IT);
extern	SLONG	GetItemType(TPOS_ITEM *IT);
extern	ULONG	GetItemUser(TPOS_ITEM *IT);
extern	ULONG	GetItemSpecial(TPOS_ITEM *IT);
extern	ULONG	GetItemPart(TPOS_ITEM *IT);
//
extern	void	SetItemNone(TPOS_ITEM *IT);
extern	SLONG	IsItemNone(TPOS_ITEM *IT);
extern	SLONG	IsItemGold(TPOS_ITEM *IT);
extern	SLONG	IsItemMonster(TPOS_ITEM *IT);
extern	SLONG	IsItemForMe(TPOS_ITEM *IT, SLONG Career, SLONG Sex);
extern	SLONG	IsItemForMyHead(TPOS_ITEM *IT, SLONG Career, SLONG Sex);
extern	SLONG	IsItemForMyNeck(TPOS_ITEM *IT, SLONG Career, SLONG Sex);
extern	SLONG	IsItemForMyBody(TPOS_ITEM *IT, SLONG Career, SLONG Sex);
extern	SLONG	IsItemForMyWaist(TPOS_ITEM *IT, SLONG Career, SLONG Sex);
extern	SLONG	IsItemForMyWrist(TPOS_ITEM *IT, SLONG Career, SLONG Sex);
extern	SLONG	IsItemForMyWeapon(TPOS_ITEM *IT, SLONG Career, SLONG Sex);
extern	SLONG	IsItemForMyFeet(TPOS_ITEM *IT, SLONG Career, SLONG Sex);
extern	SLONG	IsItemForMyGlove(TPOS_ITEM *IT, SLONG Career, SLONG Sex);
extern	SLONG	IsItemForMyDeck(TPOS_ITEM *IT, SLONG Career, SLONG Sex);
extern	SLONG	IsItemForMySash(TPOS_ITEM *IT, SLONG Career, SLONG Sex);
//
extern	SLONG	IsItemDiscardable(TPOS_ITEM *IT);
extern	SLONG	IsItemSellable(TPOS_ITEM *IT);
extern	SLONG	IsItemTransferable(TPOS_ITEM *IT);
extern	SLONG	IsItemSwapable(TPOS_ITEM *IT);
extern	SLONG	IsItemKeepsake(TPOS_ITEM *IT);
extern	SLONG	IsItemDeadDrop(TPOS_ITEM *IT);
extern	SLONG	IsItemNewbie(TPOS_ITEM *IT);
extern	SLONG	IsItemUsable(TPOS_ITEM *IT);
extern	SLONG	IsItemFixable(TPOS_ITEM *IT);
//
//
extern	void	SetZoneItemPosition(SLONG lIndex, SLONG lX, SLONG lY);
extern	void	GetZoneItemPosition(SLONG lIndex, SLONG *lX, SLONG *lY);
extern	void	SetZoneItemLife(SLONG lIndex, SLONG lLife);
extern	SLONG	GetZoneItemLife(SLONG lIndex);
extern	void	SetZoneItem(SLONG lIndex, TPOS_ITEM *IT);
extern	void	GetZoneItem(SLONG lIndex, TPOS_ITEM *IT);
extern	void	SetZoneItemOwner(SLONG lIndex, CHAR *szOwner);
extern	CHAR*	GetZoneItemOwner(SLONG lIndex);
extern	void	SetZoneItemFrame(SLONG lIndex, SLONG lFrame);
extern	SLONG	GetZoneItemFrame(SLONG lIndex);
extern	void	SetZoneItemState(SLONG lIndex, SLONG lState);
extern	SLONG	GetZoneItemState(SLONG lIndex);
extern	SLONG	GetZoneItemTotal(SLONG lIndex);
extern	void	SetZoneItemNext(SLONG lIndex, SLONG lNext);
extern	SLONG	GetZoneItemNext(SLONG lIndex);
extern	void	SetZoneItemFlag(SLONG lIndex, SLONG lFlag);
extern	SLONG	GetZoneItemFlag(SLONG lIndex);
//
extern	void	InitZoneItem(void);
extern	void	ResetZoneItem(void);
extern	void	ClearOneZoneItem(SLONG index);
extern	SLONG	IsZoneItemUnused(SLONG index);
extern	SLONG	FindUnusedZoneItem(void);
extern	SLONG	CatchZoneItem(SLONG X, SLONG Y, TPOS_ITEM *IT);
extern	SLONG	AddZoneItem(SLONG X, SLONG Y, CHAR *Owner, TPOS_ITEM *IT);
extern	SLONG	DeleteZoneItem(SLONG X, SLONG Y);
//
extern	void    TrimZoneItemPosition(SLONG *X, SLONG *Y);
//
// Land normal item(s) functions -------------------------------------------------
extern	void	SetLandItemSpecial1(TPOS_ITEM *IT, UHINT uSpecial);
extern	UHINT	GetLandItemSpecial1(TPOS_ITEM *IT);
extern	void	SetLandItemSpecial2(TPOS_ITEM *IT, UHINT uSpecial);
extern	UHINT	GetLandItemSpecial2(TPOS_ITEM *IT);
extern	void	SetLandItemDataType1(TPOS_ITEM *IT, UCHAR uType);
extern	UCHAR	GetLandItemDataType1(TPOS_ITEM *IT);
extern	void	SetLandItemDataValue1(TPOS_ITEM *IT, UCHAR uValue);
extern	UCHAR	GetLandItemDataValue1(TPOS_ITEM *IT);
extern	void	SetLandItemDataType2(TPOS_ITEM *IT, UCHAR uType);
extern	UCHAR	GetLandItemDataType2(TPOS_ITEM *IT);
extern	void	SetLandItemDataValue2(TPOS_ITEM *IT, UCHAR uValue);
extern	UCHAR	GetLandItemDataValue2(TPOS_ITEM *IT);
//
extern	SLONG	GetItemAttackData(TPOS_ITEM *IT);
extern	SLONG	GetItemAddedMagicAttack(TPOS_ITEM *IT);
extern	SLONG	GetItemAddedSpecialAttack(TPOS_ITEM *IT);
extern	SLONG	GetItemDefenceData(TPOS_ITEM *IT);
extern	SLONG	GetItemResistRatio(TPOS_ITEM *IT);
extern	SLONG	GetItemAddedMaxHp(TPOS_ITEM *IT);
extern	SLONG	GetItemAddedMaxMp(TPOS_ITEM *IT);
extern	UHINT	GetItemExplodeRate(TPOS_ITEM *IT);

// Sea normal item(s) functions ---------------------------------------------------
extern	void	SetSeaItemSpecial1(TPOS_ITEM *IT, UHINT uSpecial);
extern	UHINT	GetSeaItemSpecial1(TPOS_ITEM *IT);
extern	void	SetSeaItemDataType1(TPOS_ITEM *IT, UCHAR uType);
extern	UCHAR	GetSeaItemDataType1(TPOS_ITEM *IT);
extern	void	SetSeaItemDataValue1(TPOS_ITEM *IT, UCHAR uValue);
extern	UCHAR	GetSeaItemDataValue1(TPOS_ITEM *IT);
extern	UCHAR	GetSeaItemDataType2(TPOS_ITEM *IT);
extern	UCHAR	GetSeaItemDataType2(TPOS_ITEM *IT);
extern	void	SetSeaItemDataValue2(TPOS_ITEM *IT, UCHAR uValue);
extern	UCHAR	GetSeaItemDataValue2(TPOS_ITEM *IT);

// Drug item(s) functions ---------------------------------------------------									
extern	SLONG	GetDrugItemAddStr(TPOS_ITEM *IT);
extern	SLONG	GetDrugItemAddIns(TPOS_ITEM *IT);
extern	SLONG	GetDrugItemAddWit(TPOS_ITEM *IT);
extern	SLONG	GetDrugItemAddLuck(TPOS_ITEM *IT);
extern	SLONG	GetDrugItemResHpRate(TPOS_ITEM *IT);
extern	SLONG	GetDrugItemResMpRate(TPOS_ITEM *IT);

// Treasure map item(s) functions -------------------------------------------------
extern	void	SetTreasureMapItemWholePieces(TPOS_ITEM *IT, UHINT uPieces);
extern	UHINT	GetTreasureMapItemWholePieces(TPOS_ITEM *IT);
extern	void	SetTreasureMapItemCurrentPieces(TPOS_ITEM *IT, UHINT uPieces);
extern	UHINT	GetTreasureMapItemCurrentPieces(TPOS_ITEM *IT);
extern	void	SetTreasureMapItemIndex(TPOS_ITEM *IT, UCHAR uIndex);
extern	UCHAR	GetTreasureMapItemIndex(TPOS_ITEM *IT);

// Sea expendable item(s) functions -----------------------------------------------
extern	void	SetSeaExpendableItemCount(TPOS_ITEM *IT, UHINT uCount);
extern	UHINT	GetSeaExpendableItemCount(TPOS_ITEM *IT);

// Sailor item(s) functions -------------------------------------------------------
extern	void	SetSailorItemTotalCount(TPOS_ITEM *IT, UCHAR uCount);
extern	UCHAR	GetSailorItemTotalCount(TPOS_ITEM *IT);
extern	void	SetSailorItemHealthCount(TPOS_ITEM *IT, UCHAR uCount);
extern	UCHAR	GetSailorItemHealthCount(TPOS_ITEM *IT);

// Gold item functions ------------------------------------------------------------
extern	void	SetItemGoldCount(TPOS_ITEM *IT, ULONG uGold);
extern	ULONG	GetItemGoldCount(TPOS_ITEM *IT);
//
extern	ULONG	ComputeItemBuyCost(TPOS_ITEM *IT);
extern	ULONG	ComputeItemSellPrice(TPOS_ITEM *IT);

// Item-quest related functions ---------------------------------------------------
extern	void	SetItemQuestIndex(TPOS_ITEM *IT, SLONG lIndex);
extern	SLONG	GetItemQuestIndex(TPOS_ITEM *IT);

