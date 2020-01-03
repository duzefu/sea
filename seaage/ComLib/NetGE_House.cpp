/*
**	NetGE_House.cpp 
**	House functions.
**
**	Jack, 2002.12.9
*/
#include "NetGE_Mainfunc.h"


/************************************************************************************************************/
/* GLOBALS                                                                                                  */
/************************************************************************************************************/
TPOS_HOUSE	ZoneHouse[MAX_ZONE_HOUSES];



/************************************************************************************************************/
/* FUNCTIONS                                                                                                */
/************************************************************************************************************/

/************************************************************************/
/* Set/Get House Name                                                   */
/************************************************************************/

void	SetHouseID(SLONG lIndex, ULONG uID)
{
	ZoneHouse[lIndex].ID = uID;
}

ULONG	GetHouseID(SLONG lIndex)
{
	return ZoneHouse[lIndex].ID;
}

void	SetHouseName(SLONG lIndex, CHAR *szName)
{
	strcpy( ZoneHouse[lIndex].Name, szName );
}

CHAR*	GetHouseName(SLONG lIndex)
{
	return ZoneHouse[lIndex].Name;
}

void	SetHouseOwnerName(SLONG lIndex, CHAR *szOwnerName)
{
	strcpy( ZoneHouse[lIndex].OwnerName, szOwnerName );
}

CHAR*	GetHouseOwnerName(SLONG lIndex)
{
	return ZoneHouse[lIndex].OwnerName;
}

void	SetHouseGuildName(SLONG lIndex, CHAR *szGuildName)
{
	strcpy( ZoneHouse[lIndex].GuildName, szGuildName );
}

CHAR*	GetHouseGuildName(SLONG lIndex)
{
	return ZoneHouse[lIndex].GuildName;
}

/************************************************************************/
/* Set/Get House Money and Item                                         */
/************************************************************************/

void	SetHouseBoxMoney(SLONG lHouseIndex, SLONG lBoxIndex, ULONG uMoney)
{
	ZoneHouse[lHouseIndex].Box[lBoxIndex].Money = uMoney;
}

ULONG	GetHouseBoxMoney(SLONG lHouseIndex, SLONG lBoxIndex)
{
	return ZoneHouse[lHouseIndex].Box[lBoxIndex].Money;
}

void	SetHouseBoxItem(SLONG lHouseIndex, SLONG lBoxIndex, SLONG lItemIndex, TPOS_ITEM *lpItem)
{
	ZoneHouse[lHouseIndex].Box[lBoxIndex].Item[lItemIndex] = *lpItem;
}

void	GetHouseBoxItem(SLONG lHouseIndex, SLONG lBoxIndex, SLONG lItemIndex, TPOS_ITEM *lpItem)
{
	*lpItem = ZoneHouse[lHouseIndex].Box[lBoxIndex].Item[lItemIndex];
}

/************************************************************************
/* Set/Get House States                                                 */
/************************************************************************/

void	SetHouseSize(SLONG lIndex, UHINT uSize)
{
	ZoneHouse[lIndex].State.Size = uSize;
}

UHINT	GetHouseSize(SLONG lIndex)
{
	return ZoneHouse[lIndex].State.Size;
}

void	SetHouseCityName(SLONG lIndex, CHAR *szCityName)
{
	strcpy( ZoneHouse[lIndex].State.CityName, szCityName );
}

CHAR*	GetHouseCityName(SLONG lIndex)
{
	return ZoneHouse[lIndex].State.CityName;
}

void	SetHouseGuildPrice(SLONG lIndex, ULONG uPrice)
{
	ZoneHouse[lIndex].State.GuildPrice = uPrice;
}

ULONG	GetHouseGuildPrice(SLONG lIndex)
{
	return ZoneHouse[lIndex].State.GuildPrice;
}

void	SetHousePersonalPrice(SLONG lIndex, ULONG uPrice)
{
	ZoneHouse[lIndex].State.PersonalPrice = uPrice;;
}

ULONG	GetHousePersonalPrice(SLONG lIndex)
{
	return ZoneHouse[lIndex].State.PersonalPrice;
}

void	SetHouseBoxSize(SLONG lIndex, UHINT uBoxSize)
{
	ZoneHouse[lIndex].State.BoxSize = uBoxSize;
}

UHINT	GetHouseBoxSize(SLONG lIndex)
{
	return ZoneHouse[lIndex].State.BoxSize;
}

