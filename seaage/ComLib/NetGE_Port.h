/*
**	NetGE_Port.h 
**	Port functions header.
**
**	Jack, 2002.12.9
*/
#pragma once


// DEFINES ///////////////////////////////////////////////////////////////////////////////////////////////////////////
//
#define	MAX_PORT_SUPPLY_ITEMS		8	//每個港口特產數目
#define	MAX_PORT_NEED_ITEMS			8	//每個港口流行品數目
#define	MAX_PORT_SHIPS				16	//每個港口護衛艦數目
#define	MAX_PORT_CANNONS			16	//每個港口砲台數目
//
#define	MAX_PORTS_PER_ZONE			16	//每個區域中最多的港口數目
//
// STRUCTURES ////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma pack(push)
#pragma	pack(1)

//
//港口物品資料
typedef	struct  POS_PORT_ITEM
{
	UHINT	ItemBaseID;		//物品基本表的ID
	ULONG	SellPrice;		//物品賣出價格
	ULONG	BuyPrice;		//物品買入價格
	SLONG	Stocks;			//庫存量
	UHINT	Wastage;		//消耗量(每20分鐘)
	UHINT	Output;			//出產量(每20分鐘)
} TPOS_PORT_ITEM, *LPTPOS_PORT_ITEM;

//
//港口船隻資料
typedef	struct	POS_PORT_SHIP
{
	ULONG	ID;				//船隻的唯一ID
	ULONG	Flag;			//船隻的標誌
} TPOS_PORT_SHIP, *LPTPOS_PORT_SHIP;


//
//港口砲台資料
typedef	struct POS_PORT_CANNON 
{
	UHINT	Type;			//類型
	SLONG	StandX;			//區域中心點座標
	SLONG	StandY;			//區域中心點座標
	UHINT	AttackDistance;	//攻擊距離
	UHINT	AttackRange;	//攻擊範圍
	UHINT	Damage;			//攻擊力
	UHINT	CurrHp;			//生命力
	UHINT	MaxHp;			//最大生命力
	ULONG	AI;				//AI
	ULONG	State;			//狀態
	UHINT	Level;			//等級
} TPOS_PORT_CANNON, *LPTPOS_PORT_CANNON;


//
//港口基本資料
typedef	struct POS_PORT_BASIC 
{
	UHINT	Level;			//港口等級
	UHINT	CurrArmor;		//港口裝甲
	UHINT	MaxArmor;		//最大裝甲
	UHINT	GunCount;		//炮的數量
	UHINT	ShipCount;		//船的數量
} TPOS_PORT_BASIC, *LPTPOS_PORT_BASIC;

//
//港口資料
typedef	struct POS_PORT 
{
	ULONG	ID;					//唯一ID
	CHAR	Name[32];			//港口名稱
	CHAR	ZoneName[32];		//區域名稱
	CHAR	CountryName[32];	//所屬國家
	CHAR	GuildName[32];		//所屬工會
	SLONG	Longitude;			//經度
	SLONG	Latitude;			//緯度
	SLONG	X;					//中心點區域座標
	SLONG	Y;					//中心點區域座標
	ULONG	InvestMoney;		//投資金額
	ULONG	SaveMoney;			//存放金額
	TPOS_PORT_BASIC		Basic;	//基本值
	TPOS_PORT_ITEM		SupplyItem[MAX_PORT_SUPPLY_ITEMS];	//特產
	TPOS_PORT_ITEM		NeedItem[MAX_PORT_NEED_ITEMS];		//流行品
	TPOS_PORT_SHIP		Ship[MAX_PORT_SHIPS];				//船
	TPOS_PORT_CANNON	Cannon[MAX_PORT_CANNONS];			//炮
} TPOS_PORT, *LPTPOS_PORT;

#pragma	pack(pop)

// GLOBALS ///////////////////////////////////////////////////////////////////////////////////////////////////////////
//
extern	TPOS_PORT	ZonePort[MAX_PORTS_PER_ZONE];

// FUNCTIONS /////////////////////////////////////////////////////////////////////////////////////////////////////////
//
extern	void	SetPortID(SLONG lIndex, ULONG uID);
extern	ULONG	GetPortID(SLONG lIndex);
extern	void	SetPortName(SLONG lIndex, CHAR *szName);
extern	CHAR*	GetPortName(SLONG lIndex);
extern	void	SetPortZoneName(SLONG lIndex, CHAR *szZoneName);
extern	CHAR*	GetPortZoneName(SLONG lIndex);
extern	void	SetPortCountryName(SLONG lIndex, CHAR *szName);
extern	CHAR*	GetPortCountryName(SLONG lIndex);
extern	void	SetPortGuildName(SLONG lIndex, CHAR *szName);
extern	CHAR*	GetPortGuildName(SLONG lIndex);
extern	void	SetPortLongitude(SLONG lIndex, SLONG lLong);
extern	SLONG	GetPortLongitude(SLONG lIndex);
extern	void	SetPortLatitude(SLONG lIndex, SLONG lLat);
extern	SLONG	GetPortLatitude(SLONG lIndex);
extern	void	SetPortCenterPosition(SLONG lIndex, SLONG lX, SLONG lY);
extern	void	GetPortCenterPosition(SLONG lIndex, SLONG *lX, SLONG *lY);
extern	void	SetPortInvestMoney(SLONG lIndex, ULONG uMoney);
extern	ULONG	GetPortInvestMoney(SLONG lIndex);
extern	void	SetPortSaveMoney(SLONG lIndex, ULONG uMoney);
extern	ULONG	GetPortSaveMoney(SLONG lIndex);
//
extern	void	SetPortLevel(SLONG lIndex, UHINT uLevel);
extern	UHINT	GetPortLevel(SLONG lIndex);
extern	void	SetPortCurrentArmor(SLONG lIndex, UHINT uArmor);
extern	UHINT	GetPortCurrentArmor(SLONG lIndex);
extern	void	SetPortMaxArmor(SLONG lIndex, UHINT uArmor);
extern	UHINT	GetPortMaxArmor(SLONG lIndex);
extern	void	SetPortGunCount(SLONG lIndex, UHINT uCount);
extern	UHINT	GetPortGunCount(SLONG lIndex);
extern	void	SetPortShipCount(SLONG lIndex, UHINT uCount);
extern	UHINT	GetPortShipCount(SLONG lIndex);
//
extern	void	SetPortSupplyItemBaseID(SLONG lPortIndex, SLONG lItemIndex, UHINT uID);
extern	UHINT	GetPortSupplyItemBaseID(SLONG lPortIndex, SLONG lItemIndex);
extern	void	SetPortSupplyItemSellPrice(SLONG lPortIndex, SLONG lItemIndex, ULONG uPrice);
extern	ULONG	GetPortSupplyItemSellPrice(SLONG lPortIndex, SLONG lItemIndex);
extern	void	SetPortSupplyItemBuyPrice(SLONG lPortIndex, SLONG lItemIndex, ULONG uPrice);
extern	ULONG	GetPortSupplyItemBuyPrice(SLONG lPortIndex, SLONG lItemIndex);
extern	void	SetPortSupplyItemStocks(SLONG lPortIndex, SLONG lItemIndex, SLONG lStocks);
extern	SLONG	GetPortSupplyItemStocks(SLONG lPortIndex, SLONG lItemIndex);
extern	void	SetPortSupplyItemWastage(SLONG lPortIndex, SLONG lItemIndex, UHINT uWastage);
extern	UHINT	GetPortSupplyItemWastage(SLONG lPortIndex, SLONG lItemIndex);
extern	void	SetPortSupplyItemOutput(SLONG lPortIndex, SLONG lItemIndex, UHINT uOutput);
extern	UHINT	GetPortSupplyItemOutput(SLONG lPortIndex, SLONG lItemIndex);
//
extern	void	SetPortNeedItemBaseID(SLONG lPortIndex, SLONG lItemIndex, UHINT uID);
extern	UHINT	GetPortNeedItemBaseID(SLONG lPortIndex, SLONG lItemIndex);
extern	void	SetPortNeedItemSellPrice(SLONG lPortIndex, SLONG lItemIndex, ULONG uPrice);
extern	ULONG	GetPortNeedItemSellPrice(SLONG lPortIndex, SLONG lItemIndex);
extern	void	SetPortNeedItemBuyPrice(SLONG lPortIndex, SLONG lItemIndex, ULONG uPrice);
extern	ULONG	GetPortNeedItemBuyPrice(SLONG lPortIndex, SLONG lItemIndex);
extern	void	SetPortNeedItemStocks(SLONG lPortIndex, SLONG lItemIndex, SLONG lStocks);
extern	SLONG	GetPortNeedItemStocks(SLONG lPortIndex, SLONG lItemIndex);
extern	void	SetPortNeedItemWastage(SLONG lPortIndex, SLONG lItemIndex, UHINT uWastage);
extern	UHINT	GetPortNeedItemWastage(SLONG lPortIndex, SLONG lItemIndex);
extern	void	SetPortNeedItemOutput(SLONG lPortIndex, SLONG lItemIndex, UHINT uOutput);
extern	UHINT	GetPortNeedItemOutput(SLONG lPortIndex, SLONG lItemIndex);
//
extern	void	SetPortShipID(SLONG lPortIndex, SLONG lShipIndex, ULONG uID);
extern	ULONG	GetPortShipID(SLONG lPortIndex, SLONG lShipIndex);
extern	void	SetPortShipFlag(SLONG lPortIndex, SLONG lShipIndex, ULONG uFlag);
extern	ULONG	GetPortShipFlag(SLONG lPortIndex, SLONG lShipIndex);
//
extern	void	SetPortCannonType(SLONG lPortIndex, SLONG lCannonIndex, UHINT uType);
extern	UHINT	GetPortCannonType(SLONG lPortIndex, SLONG lCannonIndex);
extern	void	SetPortCannonStandPosition(SLONG lPortIndex, SLONG lCannonIndex, SLONG lX, SLONG lY);
extern	void	GetPortCannonStandPosition(SLONG lPortIndex, SLONG lCannonIndex, SLONG *lX, SLONG *lY);
extern	void	SetPortCannonAttackDistance(SLONG lPortIndex, SLONG lCannonIndex, UHINT uDist);
extern	UHINT	GetPortCannonAttackDistance(SLONG lPortIndex, SLONG lCannonIndex);
extern	void	SetPortCannonAttackRange(SLONG lPortIndex, SLONG lCannonIndex, UHINT lRange);
extern	UHINT	GetPortCannonAttackRange(SLONG lPortIndex, SLONG lCannonIndex);
extern	void	SetPortCannonDamage(SLONG lPortIndex, SLONG lCannonIndex, UHINT uDamage);
extern	UHINT	GetPortCannonDamage(SLONG lPortIndex, SLONG lCannonIndex);
extern	void	SetPortCannonCurrentHp(SLONG lPortIndex, SLONG lCannonIndex, UHINT uHp);
extern	UHINT	GetPortCannonCurrentHp(SLONG lPortIndex, SLONG lCannonIndex);
extern	void	SetPortCannonMaxHp(SLONG lPortIndex, SLONG lCannonIndex, UHINT uHp);
extern	UHINT	GetPortCannonMaxHp(SLONG lPortIndex, SLONG lCannonIndex);
extern	void	SetPortCannonAI(SLONG lPortIndex, SLONG lCannonIndex, ULONG uAI);
extern	ULONG	GetPortCannonAI(SLONG lPortIndex, SLONG lCannonIndex);
extern	void	SetPortCannonState(SLONG lPortIndex, SLONG lCannonIndex, ULONG uState);
extern	ULONG	GetPortCannonState(SLONG lPortIndex, SLONG lCannonIndex);
extern	void	SetPortCannonLevel(SLONG lPortIndex, SLONG lCannonIndex, UHINT uLevel);
extern	UHINT	GetPortCannonLevel(SLONG lPortIndex, SLONG lCannonIndex);
//
