/*
**	NetGE_Port.cpp 
**	Port functions.
**
**	Jack, 2002.12.9
**
**  Modified by Zhang Zhaohui
*/
#include "NetGE_Mainfunc.h"


// GLOBALS //////////////////////////////////////////////////////////////////////////////////////////////////
TPOS_PORT	ZonePort[MAX_PORTS_PER_ZONE];


// FUNCTIONS ////////////////////////////////////////////////////////////////////////////////////////////////
/************************************************************************/
/* Set/Get Port Base Properties (ID, Name, ZoneName etc.)               */
/************************************************************************/

void	SetPortID(SLONG lIndex, ULONG uID)
{
	ZonePort[lIndex].ID = uID;
}

ULONG	GetPortID(SLONG lIndex)
{
	return ZonePort[lIndex].ID;
}

void	SetPortName(SLONG lIndex, CHAR *szName)
{
	strcpy( ZonePort[lIndex].Name, szName );
}

CHAR*	GetPortName(SLONG lIndex)
{
	return ZonePort[lIndex].Name;
}

void	SetPortZoneName(SLONG lIndex, CHAR *szZoneName)
{
	strcpy( ZonePort[lIndex].ZoneName, szZoneName );
}

CHAR*	GetPortZoneName(SLONG lIndex)
{
	return ZonePort[lIndex].ZoneName;
}

void	SetPortCountryName(SLONG lIndex, CHAR *szName)
{
	strcpy( ZonePort[lIndex].CountryName, szName );
}

CHAR*	GetPortCountryName(SLONG lIndex)
{
	return ZonePort[lIndex].CountryName;
}

void	SetPortGuildName(SLONG lIndex, CHAR *szName)
{
	strcpy( ZonePort[lIndex].GuildName, szName );
}

CHAR*	GetPortGuildName(SLONG lIndex)
{
	return ZonePort[lIndex].GuildName;
}

void	SetPortLongitude(SLONG lIndex, SLONG lLong)
{
	ZonePort[lIndex].Longitude = lLong;
}

SLONG	GetPortLongitude(SLONG lIndex)
{
	return ZonePort[lIndex].Longitude;
}

void	SetPortLatitude(SLONG lIndex, SLONG lLat)
{
	ZonePort[lIndex].Latitude = lLat;
}

SLONG	GetPortLatitude(SLONG lIndex)
{
	return ZonePort[lIndex].Latitude;
}

void	SetPortCenterPosition(SLONG lIndex, SLONG lX, SLONG lY)
{
	ZonePort[lIndex].X = lX;
	ZonePort[lIndex].Y = lY;
}

void	GetPortCenterPosition(SLONG lIndex, SLONG *lX, SLONG *lY)
{
	*lX = ZonePort[lIndex].X;
	*lY = ZonePort[lIndex].Y;
}

void	SetPortInvestMoney(SLONG lIndex, ULONG uMoney)
{
	ZonePort[lIndex].InvestMoney = uMoney;
}

ULONG	GetPortInvestMoney(SLONG lIndex)
{
	return ZonePort[lIndex].InvestMoney;
}

void	SetPortSaveMoney(SLONG lIndex, ULONG uMoney)
{
	ZonePort[lIndex].SaveMoney = uMoney;
}

ULONG	GetPortSaveMoney(SLONG lIndex)
{
	return ZonePort[lIndex].SaveMoney;
}

/************************************************************************/
/* Set/Get Port Base Properties2 (Level, Armor, Guns etc.)              */
/************************************************************************/

void	SetPortLevel(SLONG lIndex, UHINT uLevel)
{
	ZonePort[lIndex].Basic.Level =uLevel;
}

UHINT	GetPortLevel(SLONG lIndex)
{
	return ZonePort[lIndex].Basic.Level;
}

void	SetPortCurrentArmor(SLONG lIndex, UHINT uArmor)
{
	ZonePort[lIndex].Basic.CurrArmor = uArmor;
}

UHINT	GetPortCurrentArmor(SLONG lIndex)
{
	return ZonePort[lIndex].Basic.CurrArmor;
}

void	SetPortMaxArmor(SLONG lIndex, UHINT uArmor)
{
	ZonePort[lIndex].Basic.MaxArmor = uArmor;
}

UHINT	GetPortMaxArmor(SLONG lIndex)
{
	return	ZonePort[lIndex].Basic.MaxArmor;
}

void	SetPortGunCount(SLONG lIndex, UHINT uCount)
{
	ZonePort[lIndex].Basic.GunCount = uCount;
}

UHINT	GetPortGunCount(SLONG lIndex)
{
	return ZonePort[lIndex].Basic.GunCount;
}

void	SetPortShipCount(SLONG lIndex, UHINT uCount)
{
	ZonePort[lIndex].Basic.ShipCount = uCount;
}

UHINT	GetPortShipCount(SLONG lIndex)
{
	return ZonePort[lIndex].Basic.ShipCount;
}

/************************************************************************
/* Set/Get Port Supply Item                                             */
/************************************************************************/

void	SetPortSupplyItemBaseID(SLONG lPortIndex, SLONG lItemIndex, UHINT uID)
{
	ZonePort[lPortIndex].SupplyItem[lItemIndex].ItemBaseID = uID;
}

UHINT	GetPortSupplyItemBaseID(SLONG lPortIndex, SLONG lItemIndex)
{
	return ZonePort[lPortIndex].SupplyItem[lItemIndex].ItemBaseID;
}

void	SetPortSupplyItemSellPrice(SLONG lPortIndex, SLONG lItemIndex, ULONG uPrice)
{
	ZonePort[lPortIndex].SupplyItem[lItemIndex].SellPrice = uPrice;
}

ULONG	GetPortSupplyItemSellPrice(SLONG lPortIndex, SLONG lItemIndex)
{
	return ZonePort[lPortIndex].SupplyItem[lItemIndex].SellPrice;
}

void	SetPortSupplyItemBuyPrice(SLONG lPortIndex, SLONG lItemIndex, ULONG uPrice)
{
	ZonePort[lPortIndex].SupplyItem[lItemIndex].BuyPrice = uPrice;
}

ULONG	GetPortSupplyItemBuyPrice(SLONG lPortIndex, SLONG lItemIndex)
{
	return ZonePort[lPortIndex].SupplyItem[lItemIndex].BuyPrice;
}

void	SetPortSupplyItemStocks(SLONG lPortIndex, SLONG lItemIndex, SLONG lStocks)
{
	ZonePort[lPortIndex].SupplyItem[lItemIndex].Stocks = lStocks;
}

SLONG	GetPortSupplyItemStocks(SLONG lPortIndex, SLONG lItemIndex)
{
	return ZonePort[lPortIndex].SupplyItem[lItemIndex].Stocks;
}

void	SetPortSupplyItemWastage(SLONG lPortIndex, SLONG lItemIndex, UHINT uWastage)
{
	ZonePort[lPortIndex].SupplyItem[lItemIndex].Wastage = uWastage;
}

UHINT	GetPortSupplyItemWastage(SLONG lPortIndex, SLONG lItemIndex)
{
	return ZonePort[lPortIndex].SupplyItem[lItemIndex].Wastage;
}

void	SetPortSupplyItemOutput(SLONG lPortIndex, SLONG lItemIndex, UHINT uOutput)
{
	ZonePort[lPortIndex].SupplyItem[lItemIndex].Output = uOutput;
}

UHINT	GetPortSupplyItemOutput(SLONG lPortIndex, SLONG lItemIndex)
{
	return ZonePort[lPortIndex].SupplyItem[lItemIndex].Output;
}

/************************************************************************/
/*  Set/Get Port Need Item Properties                                   */
/************************************************************************/

void	SetPortNeedItemBaseID(SLONG lPortIndex, SLONG lItemIndex, UHINT uID)
{
	ZonePort[lPortIndex].NeedItem[lItemIndex].ItemBaseID = uID;
}

UHINT	GetPortNeedItemBaseID(SLONG lPortIndex, SLONG lItemIndex)
{
	return ZonePort[lPortIndex].NeedItem[lItemIndex].ItemBaseID;
}

void	SetPortNeedItemSellPrice(SLONG lPortIndex, SLONG lItemIndex, ULONG uPrice)
{
	ZonePort[lPortIndex].NeedItem[lItemIndex].SellPrice = uPrice;
}

ULONG	GetPortNeedItemSellPrice(SLONG lPortIndex, SLONG lItemIndex)
{
	return ZonePort[lPortIndex].NeedItem[lItemIndex].SellPrice;
}

void	SetPortNeedItemBuyPrice(SLONG lPortIndex, SLONG lItemIndex, ULONG uPrice)
{
	ZonePort[lPortIndex].NeedItem[lItemIndex].BuyPrice = uPrice;
}

ULONG	GetPortNeedItemBuyPrice(SLONG lPortIndex, SLONG lItemIndex)
{
	return ZonePort[lPortIndex].NeedItem[lItemIndex].BuyPrice;
}

void	SetPortNeedItemStocks(SLONG lPortIndex, SLONG lItemIndex, SLONG lStocks)
{
	ZonePort[lPortIndex].NeedItem[lItemIndex].Stocks = lStocks;
}

SLONG	GetPortNeedItemStocks(SLONG lPortIndex, SLONG lItemIndex)
{
	return ZonePort[lPortIndex].NeedItem[lItemIndex].Stocks;
}

void	SetPortNeedItemWastage(SLONG lPortIndex, SLONG lItemIndex, UHINT uWastage)
{
	ZonePort[lPortIndex].NeedItem[lItemIndex].Wastage = uWastage;
}

UHINT	GetPortNeedItemWastage(SLONG lPortIndex, SLONG lItemIndex)
{
	return ZonePort[lPortIndex].NeedItem[lItemIndex].Wastage;
}

void	SetPortNeedItemOutput(SLONG lPortIndex, SLONG lItemIndex, UHINT uOutput)
{
	ZonePort[lPortIndex].NeedItem[lItemIndex].Output = uOutput;
}

UHINT	GetPortNeedItemOutput(SLONG lPortIndex, SLONG lItemIndex)
{
	return ZonePort[lPortIndex].NeedItem[lItemIndex].Output;
}

/************************************************************************/
/* Set/Get Port Ship ID and Flag                                        */
/************************************************************************/

void	SetPortShipID(SLONG lPortIndex, SLONG lShipIndex, ULONG uID)
{
	ZonePort[lPortIndex].Ship[lShipIndex].ID = uID;
}

ULONG	GetPortShipID(SLONG lPortIndex, SLONG lShipIndex)
{
	return ZonePort[lPortIndex].Ship[lShipIndex].ID;
}

void	SetPortShipFlag(SLONG lPortIndex, SLONG lShipIndex, ULONG uFlag)
{
	ZonePort[lPortIndex].Ship[lShipIndex].Flag = uFlag;
}

ULONG	GetPortShipFlag(SLONG lPortIndex, SLONG lShipIndex)
{
	return ZonePort[lPortIndex].Ship[lShipIndex].Flag;
}

/************************************************************************/
/* Set/Get Cannon Properties                                            */
/************************************************************************/

void	SetPortCannonType(SLONG lPortIndex, SLONG lCannonIndex, UHINT uType)
{
	ZonePort[lPortIndex].Cannon[lCannonIndex].Type = uType;
}

UHINT	GetPortCannonType(SLONG lPortIndex, SLONG lCannonIndex)
{
	return ZonePort[lPortIndex].Cannon[lCannonIndex].Type;
}

void	SetPortCannonStandPosition(SLONG lPortIndex, SLONG lCannonIndex, SLONG lX, SLONG lY)
{
	ZonePort[lPortIndex].Cannon[lCannonIndex].StandX = lX;
	ZonePort[lPortIndex].Cannon[lCannonIndex].StandY = lY;
}

void	GetPortCannonStandPosition(SLONG lPortIndex, SLONG lCannonIndex, SLONG *lX, SLONG *lY)
{
	*lX = ZonePort[lPortIndex].Cannon[lCannonIndex].StandX;
	*lY = ZonePort[lPortIndex].Cannon[lCannonIndex].StandY;
}

void	SetPortCannonAttackDistance(SLONG lPortIndex, SLONG lCannonIndex, UHINT uDist)
{
	ZonePort[lPortIndex].Cannon[lCannonIndex].AttackDistance = uDist;
}

UHINT	GetPortCannonAttackDistance(SLONG lPortIndex, SLONG lCannonIndex)
{
	return ZonePort[lPortIndex].Cannon[lCannonIndex].AttackDistance;
}

void	SetPortCannonAttackRange(SLONG lPortIndex, SLONG lCannonIndex, UHINT lRange)
{
	ZonePort[lPortIndex].Cannon[lCannonIndex].AttackRange = lRange;
}

UHINT	GetPortCannonAttackRange(SLONG lPortIndex, SLONG lCannonIndex)
{
	return ZonePort[lPortIndex].Cannon[lCannonIndex].AttackRange;
}

void	SetPortCannonDamage(SLONG lPortIndex, SLONG lCannonIndex, UHINT uDamage)
{
	ZonePort[lPortIndex].Cannon[lCannonIndex].Damage = uDamage;
}

UHINT	GetPortCannonDamage(SLONG lPortIndex, SLONG lCannonIndex)
{
	return ZonePort[lPortIndex].Cannon[lCannonIndex].Damage;
}

void	SetPortCannonCurrentHp(SLONG lPortIndex, SLONG lCannonIndex, UHINT uHp)
{
	ZonePort[lPortIndex].Cannon[lCannonIndex].CurrHp = uHp;
}

UHINT	GetPortCannonCurrentHp(SLONG lPortIndex, SLONG lCannonIndex)
{
	return ZonePort[lPortIndex].Cannon[lCannonIndex].CurrHp;
}

void	SetPortCannonMaxHp(SLONG lPortIndex, SLONG lCannonIndex, UHINT uHp)
{
	ZonePort[lPortIndex].Cannon[lCannonIndex].MaxHp = uHp;
}

UHINT	GetPortCannonMaxHp(SLONG lPortIndex, SLONG lCannonIndex)
{
	return ZonePort[lPortIndex].Cannon[lCannonIndex].MaxHp;
}

void	SetPortCannonAI(SLONG lPortIndex, SLONG lCannonIndex, ULONG uAI)
{
	ZonePort[lPortIndex].Cannon[lCannonIndex].AI = uAI;
}

ULONG	GetPortCannonAI(SLONG lPortIndex, SLONG lCannonIndex)
{
	return ZonePort[lPortIndex].Cannon[lCannonIndex].AI;
}

void	SetPortCannonState(SLONG lPortIndex, SLONG lCannonIndex, ULONG uState)
{
	ZonePort[lPortIndex].Cannon[lCannonIndex].State = uState;
}

ULONG	GetPortCannonState(SLONG lPortIndex, SLONG lCannonIndex)
{
	return ZonePort[lPortIndex].Cannon[lCannonIndex].State;
}

void	SetPortCannonLevel(SLONG lPortIndex, SLONG lCannonIndex, UHINT uLevel)
{
	ZonePort[lPortIndex].Cannon[lCannonIndex].Level = uLevel;
}

UHINT	GetPortCannonLevel(SLONG lPortIndex, SLONG lCannonIndex)
{
	return ZonePort[lPortIndex].Cannon[lCannonIndex].Level;
}
