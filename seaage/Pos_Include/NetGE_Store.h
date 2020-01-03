/*
**	NetGE_Store.h 
**	store functions.
**
**	Jack, 2003.2.18.
*/
#pragma once


//
// DEFINES //////////////////////////////////////////////////////////////////////////////////////////////////
//
#define	MAX_GAME_STORE_BASES			256		//遊戲中所有基本商店資料的數目
#define	MAX_ZONE_STORES					32		//每個區域中商店的數目
#define	MAX_STORE_ITEMS					36		//每個商店中出售物品的最大數目
#define	MAX_STORE_CUSTOMERS				10		//商店中同時買賣的顧客最大數目
#define	STORE_ITEM_PRODUCE_BASE			100		//商店物品生產率基數
#define	STORE_ITEM_PRICE_QUOTIETY_BASE	100		//商店物品價格係數基數


// Store item flags
#define	STORE_ITEM_TYPE_MASK		0x0000000f	//物品類型掩碼
#define	STORE_ITEM_TYPE_PRODUCT		0x00000001	//商店自產物品
#define	STORE_ITEM_TYPE_PLAYER		0x00000002	//商店買進的玩家的物品(商店無產出物品)

//
// STRUCTS //////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//遊戲中的商店基本資料的結構
//
typedef	struct POS_STORE_BASE
{
	UHINT	ItemBaseID[MAX_STORE_ITEMS];	//物品的基本ID
	UHINT	InitCount[MAX_STORE_ITEMS];		//初始化的數量
	SLONG	InitProduce[MAX_STORE_ITEMS];	//初始化的生產率
	SLONG	PriceQuotiety[MAX_STORE_ITEMS];	//價格係數
} TPOS_STORE_BASE, *LPTPOS_STORE_BASE;


//
//區域中商店物品資料結構
//
typedef	struct POS_STORE_ITEM
{
	ULONG		Flags;			//該物品的標示
	UHINT		Count;			//商店擁有該物品的數量
	ULONG		Price;			//售出價格
	union
	{
		UHINT	Produce;		//商店自己產出的物品: 生產量
		UHINT	Consume;		//玩家賣給商店的物品: 消耗量
	};
	union
	{
		UHINT	AddUpProduce;	//商店自己產出的物品: 累計生產量
		UHINT	AddUpConsume;	//玩家賣給商店的物品: 累計消耗量
	};
	TPOS_ITEM	Item;			//出售的物品

} TPOS_STORE_ITEM, *LPPOS_STORE_ITEM;

//
//區域中商店資料結構
//
typedef	struct POS_ZONE_STORE 
{
	SLONG			Flag;					//商店標誌
	CHAR			StoreName[32];			//商店名稱
	SLONG			StorePriceQuotiety;		//價格係數
	TPOS_STORE_ITEM	StoreItem[MAX_STORE_ITEMS];				//出售物品列表
	CHAR			CustomerName[MAX_STORE_CUSTOMERS][32];	//顧客名稱
} TPOS_ZONE_STORE, *LPTPOS_ZONE_STORE;

//
// GLOBALS //////////////////////////////////////////////////////////////////////////////////////////////////
//
extern	TPOS_STORE_BASE		GameStoreBase[MAX_GAME_STORE_BASES];
extern	TPOS_ZONE_STORE		ZoneStore[MAX_ZONE_STORES];

//
// FUNCTIONS ////////////////////////////////////////////////////////////////////////////////////////////////
//
extern	SLONG	InitStoreSystem(void);
extern	void	FreeStoreSystem(void);
//
extern	void	InitGameStoreBase(void);
extern	SLONG	LoadGameStoreBase(void);
extern	void	DebugLogGameStoreBase(void);
extern	void	FreeGameStoreBase(void);
extern	SLONG	LoadOneGameStoreBase(SLONG lStoreIndex);
extern	void	DebugLogOneGameStoreBase(SLONG lStoreIndex);
//
extern	void	InitZoneStore(void);
extern	void	RefreshZoneStore(void);
extern	void	RefreshOneZoneStore(SLONG lIndex);
extern	void	SetupZoneStore(SLONG lIndex, SLONG lBaseIndex);
//
extern	void	SetZoneStoreFlag(SLONG lIndex, SLONG lFlag);
extern	SLONG	GetZoneStoreFlag(SLONG lIndex);
extern	void	SetZoneStoreName(SLONG lIndex, char *szStoreName);
extern	char*	GetZoneStoreName(SLONG lIndex);
extern	void	SetZoneStorePriceQuotiety(SLONG lIndex, SLONG lQuotiety);
extern	SLONG	GetZoneStorePriceQuotiety(SLONG lIndex);
extern	SLONG	SetZoneStoreItem(SLONG lIndex, SLONG lItemIndex, TPOS_STORE_ITEM *lpStoreItem);
extern	SLONG	GetZoneStoreItem(SLONG lIndex, SLONG lItemIndex, TPOS_STORE_ITEM *lpStoreItem);
extern	SLONG	FindZoneStoreCustomerIndex(SLONG lIndex, char *szMainName);
extern	void	SetZoneStoreCustomerName(SLONG lIndex, SLONG lCustomerIndex, char *szMainName);
extern	char*	GetZoneStoreCustomername(SLONG lIndex, SLONG lCustomerIndex);

