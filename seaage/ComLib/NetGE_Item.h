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
#define	MAX_GAME_ITEM_BASES					4096	//遊戲的基本物品種數
#define	HEAD_GAME_ITEMS						1		//用作頭節點的道具項, 不小於遊戲地圖數目
#define	MAX_GAME_ITEMS						10240	//遊戲中所有地圖上同時存在的最多物品數目
#define	MAX_ZONE_GS_ITEMS					(MAX_GAME_ITEMS - HEAD_GAME_ITEMS)	//單個區域的地上最大物品數目
#define	ZONE_ITEM_LIFE_TICKS				(15 * 20 * 60)	//地上物品有的生命期(15分鐘)
#define	ZONE_ITEM_OWNER_TICKS				(5 * 20 * 60)	//地上物品只能被特定人拾取的時間(5分鐘)

#define	MAX_PROPERTY_PER_ITEM				4		//物品最大隨機屬性數目
#define	MAX_PROPERTY_PER_TYPE				64		//每種特殊屬性群的屬性數目

#define	ITEM_STAY_WIDTH						64	//物品在地圖上佔據區域的寬度
#define	ITEM_STAY_HEIGHT					40	//物品在地圖上佔據區域的高度

//
//道具類型設定(@ POS_ITEM_BS)
//
#define	ITEM_TYPE_GENERAL					0	//常規物品(保留)
#define	ITEM_TYPE_LAND_NORMAL				1	//陸地物品
#define	ITEM_TYPE_SEA_NORMAL				2	//海洋物品
#define	ITEM_TYPE_TREASURE_MAP				3	//藏寶圖
#define	ITEM_TYPE_SEA_EXPENDABLE			4	//海洋消耗品
#define	ITEM_TYPE_SEA_SAILOR				5	//海洋水手
#define	ITEM_TYPE_MONEY						6	//金錢資訊
#define	ITEM_TYPE_MONSTER					7	//寶箱怪
#define	ITEM_TYPE_DRUG						8	//藥品

//
//道具基本ID設定
//
#define	ITEM_BASE_ID_NONE					0		//表示甚麼物品都沒有
#define	ITEM_BASE_ID_GOLD					200		//金錢
#define	ITEM_BASE_ID_MONSTER				201		//寶箱怪
#define	ITEM_BASE_ID_NORMAL_START			300		//常規物品ID的起始值


//
//道具適用部位定義
//
#define	ITEM_PART_HUMAN_HEAD				0x00000001	//人物頭上裝備
#define	ITEM_PART_HUMAN_NECK				0x00000002	//人物頸部裝備
#define	ITEM_PART_HUMAN_BODY				0x00000004	//人物身體裝備
#define	ITEM_PART_HUMAN_WAIST				0x00000008	//人物腰部裝備
#define	ITEM_PART_HUMAN_WRIST				0x00000010	//人物手環裝備
#define	ITEM_PART_HUMAN_WEAPON				0x00000020	//人物武器裝備
#define	ITEM_PART_HUMAN_FEET				0x00000040	//人物足部裝備
#define	ITEM_PART_HUMAN_DECK				0x00000080	//人物裝飾位裝備
#define	ITEM_PART_HUMAN_SASH				0x00000100	//人物腰包裝備(快捷欄)
#define	ITEM_PART_HUMAN_GLOVE				0x00000200	//人物手套裝備


//
//道具特殊屬性定義
//
#define ITEM_SPECIAL_DISCARDABLE			0x00000001  //是否能丟棄
#define ITEM_SPECIAL_SELLABLE				0x00000002  //是否能販賣
#define ITEM_SPECIAL_TRANSFERABLE			0x00000004  //是否能夠ICQ傳輸
#define ITEM_SPECIAL_SWAPABLE				0x00000008  //是否能交換
#define ITEM_SPECIAL_KEEPSAKE				0x00000010  //是否為信物
#define ITEM_SPECIAL_DEADDROP				0x00000020  //是否能死後掉落
#define ITEM_SPECIAL_NEWBIE					0x00000040  //是否是新手物品
#define ITEM_SPECIAL_USABLE					0x00000080  //是否能使用
#define ITEM_SPECIAL_FIXABLE				0x00000100  //是否能裝備
#define	ITEM_SPECIAL_CRYSTAL				0x40000000	//是否為紫晶裝備
#define	ITEM_SPECIAL_ARTIFACTS				0x80000000	//是否為神器

//
//---------------------------------------------------------------------------
//陸地物品隨機屬性定義 IR
//---------------------------------------------------------------------------
//
//陸地物品特殊屬性定義(SPECIAL 1)
//
#define	LAND_ITEM_SPECIAL1_NONE							0	//無任何屬性
#define	LAND_ITEM_SPECIAL1_ACC_MUSE						1	//加速冥想
#define	LAND_ITEM_SPECIAL1_ANTI_BAD						2	//負面狀態免疫
#define	LAND_ITEM_SPECIAL1_LEVEL_ADD_ATT				3	//基於等級增加傷害
#define	LAND_ITEM_SPECIAL1_LEVEL_ADD_DEF				4	//基於等級增加防禦
#define	LAND_ITEM_SPECIAL1_LEVEL_ADD_MAX_HP				5	//基於等級增加生命上限
#define	LAND_ITEM_SPECIAL1_LEVEL_ADD_MAX_MP				6	//基於等級增加魔力上限
#define	LAND_ITEM_SPECIAL1_NEVER_SHATTER				7	//永不磨損
#define	LAND_ITEM_SPECIAL1_LOWER_DAMAGE					8	//減少物理傷害10%
//
//陸地物品特殊屬性定義(SPECIAL 2)
//
#define	LAND_ITEM_SPECIAL2_NONE							0	//無任何屬性
#define	LAND_ITEM_SPECIAL2_LOWER_REQUEST				1	//降低需求20%
#define	LAND_ITEM_SPECIAL2_BE_TORTOISE					2	//有2%變烏龜屬性
#define	LAND_ITEM_SPECIAL2_BE_PIG						3	//有2%變豬屬性
#define LAND_ITEM_SPECIAL2_SLEEP						4   //有2%昏睡屬性
#define	LAND_ITEM_SPECIAL2_ADD_SKILL_LEVEL				5	//玩家技能等級 + 1
#define	LAND_ITEM_SPECIAL2_ADD_GENERAL_SKILL_LEVEL		6	//提督技能等級 + 1
#define	LAND_ITEM_SPECIAL2_ADD_SWORDER_SKILL_LEVEL		7	//劍客技能等級 + 1
#define	LAND_ITEM_SPECIAL2_ADD_EXPLORER_SKILL_LEVEL		8	//探險家技能等級 + 1
#define	LAND_ITEM_SPECIAL2_ADD_THIEF_SKILL_LEVEL		9	//小偷技能等級 + 1
#define	LAND_ITEM_SPECIAL2_ADD_TRADER_SKILL_LEVEL		10	//商人技能等級 + 1
#define	LAND_ITEM_SPECIAL2_ADD_CLERIC_SKILL_LEVEL		11	//牧師技能等級 + 1
#define	LAND_ITEM_SPECIAL2_ADD_HOROSCOPER_SKILL_LEVEL	12	//占星術士技能等級 + 1
#define	LAND_ITEM_SPECIAL2_ADD_SMALL_ATTACK_RATIO		13	//命中率 +5
#define	LAND_ITEM_SPECIAL2_ADD_MIDDLE_ATTACK_RATIO		14	//命中率 +10
#define	LAND_ITEM_SPECIAL2_ADD_LARGE_ATTACK_RATIO		15	//命中率 +15
//
//陸地物品數值類型定義(TYPE 1)
//
#define	LAND_ITEM_DATATYPE1_NONE						0	//無
#define	LAND_ITEM_DATATYPE1_ADD_MAX_HP					1	//增加生命上限
#define	LAND_ITEM_DATATYPE1_ADD_MAX_MP					2	//增加魔法上限
#define	LAND_ITEM_DATATYPE1_ADD_DEF						3	//增加防禦力
#define	LAND_ITEM_DATATYPE1_ENHANCE_DEF					4	//加強防禦
#define	LAND_ITEM_DATATYPE1_ADD_RESIST					5	//增加抵抗
//
//陸地物品數值類型定義(TYPE 2)
//
#define	LAND_ITEM_DATATYPE2_NONE						0	//無
#define	LAND_ITEM_DATATYPE2_ADD_ATT						1	//增加攻擊力
#define	LAND_ITEM_DATATYPE2_ENHANCE_ATT					2	//加強攻擊
#define	LAND_ITEM_DATATYPE2_ADD_MAGIC_HURT				3	//增加魔法傷害
#define	LAND_ITEM_DATATYPE2_ADD_SPECIAL_HURT			4	//增加特殊傷害
#define	LAND_ITEM_DATATYPE2_CRITICAL_STRIKE				5	//會心一擊	
//
//---------------------------------------------------------------------------
//海洋物品隨機屬性定義
//---------------------------------------------------------------------------
//
//海洋物品特殊屬性定義
//
#define	SEA_ITEM_SPECIAL1_NONE							0	//無任何屬性
#define	SEA_ITEM_SPECIAL1_NEVER_SHATTER					1	//永不磨損
#define	SEA_ITEM_SPECIAL1_ADD_SMALL_SPEED				2	//船速 + 5
#define	SEA_ITEM_SPECIAL1_ADD_MIDDLE_SPEED				3	//船速 + 10
#define	SEA_ITEM_SPECIAL1_ADD_LARGE_SPEED				4	//船速 + 15
#define	SEA_ITEM_SPECIAL1_ADD_SMALL_TURN				5	//轉速 + 5
#define	SEA_ITEM_SPECIAL1_ADD_MIDDLE_TURN				6	//轉速 + 10
#define	SEA_ITEM_SPECIAL1_ADD_LARGE_TURN				7	//轉速 + 15
#define	SEA_ITEM_SPECIAL1_REDUCE_SMALL_FOOD				8	//食物消耗 -10%
#define	SEA_ITEM_SPECIAL1_REDUCE_MIDDLE_FOOD			9	//食物消耗 -15%
#define	SEA_ITEM_SPECIAL1_REDUCE_LARGE_FOOD				10	//食物消耗 -20%
#define	SEA_ITEM_SPECIAL1_REDUCE_SMALL_POWDER			11	//火藥消耗 -1
#define	SEA_ITEM_SPECIAL1_REDUCE_MIDDLE_POWDER			12	//火藥消耗 -2
#define	SEA_ITEM_SPECIAL1_REDUCE_LARGE_POWDER			13	//火藥消耗 -3
//
//海洋物品數值類型定義(TYPE 1)
//
#define	SEA_ITEM_DATATYPE1_NONE							0	//無
#define	SEA_ITEM_DATATYPE1_ADD_ATTACK_RATIO				1	//增加命中率
#define	SEA_ITEM_DATATYPE1_ADD_DAMAGE					2	//增加傷害力
#define	SEA_ITEM_DATATYPE1_ENHANCE_DAMAGE				3	//加強傷害力
#define	SEA_ITEM_DATATYPE1_ADD_EMBOLON_DAMAGE			4	//增加撞角傷害力
#define	SEA_ITEM_DATATYPE1_ADD_SAILOR_DAMAGE			5	//增加水手傷害力
//
//海洋物品數值類型定義(TYPE 2)
//
#define	SEA_ITEM_DATATYPE2_NONE							0	//無
#define	SEA_ITEM_DATATYPE2_ADD_ARMOR					1	//增加裝甲值
#define	SEA_ITEM_DATATYPE2_ENHANCE_ARMOR				2	//加強裝甲值
#define	SEA_ITEM_DATATYPE2_REDUCE_DAMAGE				3	//降低傷害

//
// STRUCTURES ////////////////////////////////////////////////////////////////////////////////////////////////////////
//
#pragma	pack(push)
#pragma	pack(1)
//
//道具基本數值定義(BS = Base)
//
typedef	struct POS_ITEM_BS 
{
	UHINT	BaseID;			//基本表ID
	SLONG	IconIndex;		//圖標編號
	CHAR	Name[32];		//名稱
	SLONG	Type;			//道具類別
	SLONG	TcLevel;		//TC等級
	SLONG	NeedGoodEvil;	//善惡需求
	ULONG	User;			//使用人
	ULONG	Part;			//適用部位
	ULONG	Special;		//特殊屬性
	UHINT	CrystalID;		//對應紫晶裝備BaseID
	UHINT	ArtifactsID;	//對應神器裝備BaseID
	ULONG	AddedAttrib;	//附加隨機屬性(適用於紫晶裝備,神器裝備)
	//
	union
	{
		struct  //陸地裝備適用
		{
			SLONG	MinNeedStr;		//力量最少需求
			SLONG	MinNeedIns;		//直覺最少需求
			SLONG	MinNeedWit;		//智慧最少需求
			SLONG	MinNeedLuck;	//運氣最少需求
			SLONG	HitChance;		//命中率
			SLONG	ExplodeRate;	//膛爆率
			SLONG	BaseAtt;		//基本攻擊力
			SLONG	BaseDef;		//基本防禦力
			SLONG	ResHpRate;		//HP恢復率
			SLONG	ResMpRate;		//MP恢復率
		} Land;

		struct  //海洋裝備適用
		{
			SLONG	NeedShipSize;	//船隻等級需求(小, 中, 大, 巨)
			SLONG	CannonAttack;	//炮擊力(0~255)
			SLONG	EmbolonAttack;	//撞角傷害力(0~255)
			SLONG	Armor;			//裝甲值(0~255)
			SLONG	HitChance;		//命中率(0~255)
			SLONG	MoveSpeed;		//移動速度(慢, 中, 快)
			SLONG	TurnSpeed;		//轉向力(慢, 中, 快)
			SLONG	FireCost;		//耗彈量
			SLONG	Reserved[2];	//保留
		} Sea;

		struct  //藥品適用
		{
			SLONG	AddStr;			//增加力量(+/-)
			SLONG	AddIns;			//增加直覺(+/-)
			SLONG	AddWit;			//增加智慧(+/-)
			SLONG	AddLuck;		//增加運氣(+/-)
			SLONG	ResHpRate;		//HP回復率
			SLONG	ResMpRate;		//MP回復率
			SLONG	Reserved[4];	//保留
		} Drug;
	};
} TPOS_ITEM_BS, *LPTPOS_ITEM_BS;


//
//道具的隨機屬性
//
typedef	union	POS_ITEM_RANDOM
{
	struct	//一般性(藥品, 商品)
	{
		UCHAR	Attr[5];			//5種屬性
	} General;

	struct  //陸地物品
	{
		union
		{
			struct  
			{
				UHINT	Special1 : 4;	//特殊屬性1
				UHINT	Special2 : 4;	//特殊屬性2
				UHINT	Reserved : 8;	//保留未用
			};
			UHINT	Specials;			//特殊屬性
		};
		union
		{
			struct  
			{
				UCHAR	Type1 : 4;		//數值類型1
				UCHAR	Type2 : 4;		//數值類型2
			};
			UCHAR	Types;
		};
		UCHAR	Data1;				//數值1(0~255)
		UCHAR	Data2;				//數值2(0~255)
	} Land;

	struct  //海洋物品
	{
		union
		{
			struct  
			{
				UHINT	Special1 : 4;	//特殊屬性1
				UHINT	Reserved : 12;	//保留未用
			};
			UHINT	Specials;
		};
		union
		{
			struct  
			{
				UCHAR	Type1 : 4;		//數值類型1
				UCHAR	Type2 : 4;		//數值類型2
			};
			UCHAR	Types;
		};
		UCHAR	Data1;				//數值1(0~255)
		UCHAR	Data2;				//數值2(0~255)
	} Sea;

	struct  //藏寶圖資訊
	{
		UHINT	WholePieces;		//總片數標誌
		UHINT	CurrentPieces;		//當前片數標誌(每個BIT表示一片碎片, 最多16片)
		UCHAR	Index;				//相對應寶藏事件的編號

	} TreasureMap;

	struct	//海洋消耗品
	{
		UHINT	Count;				//數量(1~1000)
		UCHAR	Reserved[3];		//保留
	} SeaExpendable;

	struct	//海洋水手
	{
		UCHAR	TotalCount;			//水手總量
		UCHAR	HealthCount;		//健康水手量
		UCHAR	Reserved[3];		//保留
	} Sailor;

	struct	//金錢資訊
	{
		ULONG	Amount;				//金錢數量
		UCHAR	Reserved[1];		//保留
	} Money;

	struct	//寶箱怪
	{
		UCHAR	Level;				//出現怪物的等級(1~100)
		UCHAR	Style;				//出現怪物的型態
		UCHAR	Reserved[3];		//保留
	} Monster;
	
} TPOS_ITEM_RANDOM, *LPTPOS_ITEM_RANDOM;

typedef	struct  POS_ITEM_RANDOM_PROPERTY
{
	UHINT	PropertyNameIndex;		//屬性名稱索引
	UHINT	IsHaveValue;			//有無數值  0 - 無 , 1 -有
	ULONG	UseablePart;			//適用部位
	UHINT	TCLevel;				//TC 級別
	UHINT	MinValue;				//最小值
	UHINT	MaxValue;				//最大值
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
	TPOS_ITEM_RANDOM_BS_ZONE	ZoneItemRandom[2];	// 區域  0 - 陸地 , 1 - 海洋
}TPOS_ITEM_RANDOM_BS;

//
//道具實體的定義
//
typedef	struct  POS_ITEM
{
	UHINT	BaseID;		//物品基本編號
	UCHAR	Hp;			//物品的耐久度
	union
	{
		ULONG	ID;		//物品的唯一ID(目前未用)
		struct  
		{
			UCHR	QuestIndex;		//對應任務編號(0為非任務物品, 其他表示對應任務的物品)
			CHAR	Reserved[3];	//保留
		};
	};
	
	TPOS_ITEM_RANDOM	IR;			//物品的隨機屬性
} TPOS_ITEM, *LPTPOS_ITEM;


//
//區域地圖上道具數值結構(GS = Ground State)
//
typedef	struct POS_ITEM_GS
{
    //-------------------------------
    union 
    {
        SLONG   Flag;			//使用標誌
        SLONG   Tail;			//本地圖道具鏈鏈尾指標
    };
    SLONG		Next;			//後繼指標
    //-------------------------------
	union
	{
		SLONG	X;				//地圖座標 X
		SLONG	Total;			//本地圖的道具總數目
	};
	SLONG		Y;				//地圖座標 Y
	SLONG		State;			//當前狀態
	SLONG		Life;			//生命期
	SLONG		Frame;			//影像幀數
	CHAR		Owner[32];		//擁有人
	TPOS_ITEM	Item;			//物品
} TPOS_ITEM_GS, *LPTPOS_ITEM_GS;


#pragma	pack(pop)

// GLOBALS ///////////////////////////////////////////////////////////////////////////////////////////////////////////
//
extern	TPOS_ITEM_BS		GameItemBase[MAX_GAME_ITEM_BASES];	//遊戲物品基本資料列表
extern	TPOS_ITEM_RANDOM_BS	GameItemRandomBase;					//遊戲物品隨機附加屬性基本資料列表
extern	TPOS_ITEM_GS		ZoneItemGS[MAX_GAME_ITEMS];			//遊戲中最多物品數目


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

