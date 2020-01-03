/*
**	NetGE_Ship.cpp 
**	ship functions header.
**
**	Jack, 2002.12.9
*/
#include "NetGE_Mainfunc.h"



/************************************************************************************************************/
/* GLOBALS                                                                                                  */
/************************************************************************************************************/
TPOS_SHIP	ZoneShip[MAX_SHIPS_PER_ZONE];


/************************************************************************************************************/
/* FUNCTIONS                                                                                                */
/************************************************************************************************************/

/************************************************************************/
/* Set/Get Ship ID and Names                                            */
/************************************************************************/

void	SetShipID(SLONG lIndex, ULONG uID)
{
	ZoneShip[lIndex].ID = uID;
}

ULONG	GetShipID(SLONG lIndex)
{
	return ZoneShip[lIndex].ID;
}

void	SetShipBaseID(SLONG lIndex, UHINT uBaseID)
{
	ZoneShip[lIndex].BaseID = uBaseID;
}

UHINT	GetShipBaseID(SLONG lIndex)
{
	return ZoneShip[lIndex].BaseID;
}

void	SetShipName(SLONG lIndex, CHAR *szName)
{
	strcpy( ZoneShip[lIndex].Name, szName );
}

CHAR*	GetShipName(SLONG lIndex)
{
	return ZoneShip[lIndex].Name;
}

void	SetShipPortName(SLONG lIndex, CHAR *szName)
{
	strcpy( ZoneShip[lIndex].Port, szName );
}

CHAR*	GetShipPortName(SLONG lIndex)
{
	return ZoneShip[lIndex].Port;
}

/************************************************************************/
/* Set/Get Ship Speed                                                   */
/************************************************************************/

void	SetShipAccSpeedX(SLONG lIndex, SLONG lAccX)
{
	ZoneShip[lIndex].Speed.AccSpeedX = lAccX;
}

SLONG	GetShipAccSpeedX(SLONG lIndex)
{
	return ZoneShip[lIndex].Speed.AccSpeedX;
}

void	SetShipAccSpeedY(SLONG lIndex, SLONG lAccY)
{
	ZoneShip[lIndex].Speed.AccSpeedY = lAccY;
}

SLONG	GetShipAccSpeedY(SLONG lIndex)
{
	return ZoneShip[lIndex].Speed.AccSpeedY;
}

void	SetShipSpeedX(SLONG lIndex, SLONG lSpeedX)
{
	ZoneShip[lIndex].Speed.SpeedX = lSpeedX;
}

SLONG	GetShipSpeedX(SLONG lIndex)
{
	return ZoneShip[lIndex].Speed.SpeedX;
}

void	SetShipSpeedY(SLONG lIndex, SLONG lSpeedY)
{
	ZoneShip[lIndex].Speed.SpeedY = lSpeedY;
}

SLONG	GetShipSpeedY(SLONG lIndex)
{
	return ZoneShip[lIndex].Speed.SpeedY;
}

void	SetShipSpeedLeftX(SLONG lIndex, SLONG lLeftX)
{
	ZoneShip[lIndex].Speed.SpeedLeftX = lLeftX;
}

SLONG	GetShipSpeedLeftX(SLONG lIndex)
{
	return ZoneShip[lIndex].Speed.SpeedLeftX;
}

void	SetShipSpeedLeftY(SLONG lIndex, SLONG lLeftY)
{
	ZoneShip[lIndex].Speed.SpeedLeftY = lLeftY;
}

SLONG	GetShipSpeedLeftY(SLONG lIndex)
{
	return ZoneShip[lIndex].Speed.SpeedLeftY;
}

/************************************************************************/
/* Set/Get Ship Position and Direction                                  */
/************************************************************************/

void	SetShipPosition(SLONG lIndex, SLONG lX, SLONG lY, SLONG lZ)
{
	ZoneShip[lIndex].Position.X = lX;
	ZoneShip[lIndex].Position.Y = lY;
	ZoneShip[lIndex].Position.Z = lZ;
}

void	GetShipPosition(SLONG lIndex, SLONG *lX, SLONG *lY, SLONG *lZ)
{
	*lX = ZoneShip[lIndex].Position.X;
	*lY = ZoneShip[lIndex].Position.Y;
	*lZ = ZoneShip[lIndex].Position.Z;
}

void	SetShipDestPosition(SLONG lIndex, SLONG lX, SLONG lY, SLONG lZ)
{
	ZoneShip[lIndex].Position.DestX = lX;
	ZoneShip[lIndex].Position.DestY = lY;
	ZoneShip[lIndex].Position.DestZ = lZ;
}

void	GetShipDestPosition(SLONG lIndex, SLONG *lX, SLONG *lY, SLONG *lZ)
{
	*lX = ZoneShip[lIndex].Position.DestX;
	*lY = ZoneShip[lIndex].Position.DestY;
	*lZ = ZoneShip[lIndex].Position.DestZ;
}

void	SetShipBodyDir(SLONG lIndex, SLONG lDir)
{
	ZoneShip[lIndex].Position.ShipDir = lDir;
}

SLONG	GetShipBodyDir(SLONG lIndex)
{
	return ZoneShip[lIndex].Position.ShipDir;
}

void	SetShipSailDir(SLONG lIndex, SLONG lDir)
{
	ZoneShip[lIndex].Position.SailDir = lDir;
}

SLONG	GetShipSailDir(SLONG lIndex)
{
	return ZoneShip[lIndex].Position.SailDir;
}

/************************************************************************/
/* Set/Get Ship Image Index                                             */
/************************************************************************/

void	SetShipFileImageIndex(SLONG lIndex, SLONG lFileIndex)
{
	ZoneShip[lIndex].Style.FileIndex = lFileIndex;
}

SLONG	GetShipFileImageIndex(SLONG lIndex)
{
	return ZoneShip[lIndex].Style.FileIndex;
}

void	SetShipTrackImageIndex(SLONG lIndex, SLONG lTrackIndex)
{
	ZoneShip[lIndex].Style.TrackIndex = lTrackIndex;
}

SLONG	GetShipTrackImageIndex(SLONG lIndex)
{
	return ZoneShip[lIndex].Style.TrackIndex;
}

/************************************************************************/
/* Set/Get Ship Attack and Defence                                      */
/************************************************************************/

void	SetShipSailorAttack(SLONG lIndex, UHINT uAttack)
{
	ZoneShip[lIndex].AttDef.SailorAttack = uAttack;
}

UHINT	GetShipSailorAttack(SLONG lIndex)
{
	return ZoneShip[lIndex].AttDef.SailorAttack;
}

void	SetShipEmbolonAttack(SLONG lIndex, UHINT uAttack)
{
	ZoneShip[lIndex].AttDef.EmbolonAttack = uAttack;
}

UHINT	GetShipEmbolonAttack(SLONG lIndex)
{
	return ZoneShip[lIndex].AttDef.EmbolonAttack;
}

void	SetShipSailorCount(SLONG lIndex, UHINT uCount)
{
	ZoneShip[lIndex].AttDef.SailorCount = uCount;
}

UHINT	GetShipSailorCount(SLONG lIndex)
{
	return ZoneShip[lIndex].AttDef.SailorCount;
}

void	SetShipHealthSailorCount(SLONG lIndex, UHINT uCount)
{
	ZoneShip[lIndex].AttDef.HealthSailorCount = uCount;
}

UHINT	GetShipHealthSailorCount(SLONG lIndex)
{
	return ZoneShip[lIndex].AttDef.HealthSailorCount;
}

void	SetShipCurrentArmor(SLONG lIndex, UHINT uArmor)
{
	ZoneShip[lIndex].AttDef.CurrArmor = uArmor;
}

UHINT	GetShipCurrentArmor(SLONG lIndex)
{
	return ZoneShip[lIndex].AttDef.CurrArmor;
}

/************************************************************************/
/* Set/Get Ship Embolon and Figurehead                                  */
/************************************************************************/

void	SetShipEmbolonItem(SLONG lIndex, TPOS_ITEM *lpItem)
{
	ZoneShip[lIndex].Embolon.Item = *lpItem;
}

void	GetShipEmbolonItem(SLONG lIndex, TPOS_ITEM *lpItem)
{
	*lpItem = ZoneShip[lIndex].Embolon.Item;
}

void	SetShipStatueItem(SLONG lIndex, TPOS_ITEM *lpItem)
{
	ZoneShip[lIndex].Statue.Item = *lpItem;
}

void	GetShipStatueItem(SLONG lIndex, TPOS_ITEM *lpItem)
{
	*lpItem = ZoneShip[lIndex].Statue.Item;
}

/************************************************************************/
/* Set/Get Ship Cannon                                                  */
/************************************************************************/

void	SetShipCannonAttack(SLONG lShipIndex, SLONG lCannonIndex, UHINT uAttack)
{
	ZoneShip[lShipIndex].Cannon[lCannonIndex].Attack = uAttack;
}

UHINT	GetShipCannonAttack(SLONG lShipIndex, SLONG lCannonIndex)
{
	return ZoneShip[lShipIndex].Cannon[lCannonIndex].Attack;
}

void	SetShipCannonFireCost(SLONG lShipIndex, SLONG lCannonIndex, UHINT uCost)
{
	ZoneShip[lShipIndex].Cannon[lCannonIndex].FireCost = uCost;
}

UHINT	GetShipCannonFireCost(SLONG lShipIndex, SLONG lCannonIndex)
{
	return ZoneShip[lShipIndex].Cannon[lCannonIndex].FireCost;
}

void	SetShipCannonAttackRatio(SLONG lShipIndex, SLONG lCannonIndex, UCHAR uRatio)
{
	ZoneShip[lShipIndex].Cannon[lCannonIndex].AttackRatio = uRatio;
}

UCHAR	GetShipCannonAttackRatio(SLONG lShipIndex, SLONG lCannonIndex)
{
	return ZoneShip[lShipIndex].Cannon[lCannonIndex].AttackRatio;
}

/************************************************************************/
/* Set/Get Ship Cabin                                                   */
/************************************************************************/

void	SetShipCabinType(SLONG lShipIndex, SLONG lCabinIndex, UHINT uType)
{
	ZoneShip[lShipIndex].Cabin[lCabinIndex].CurrType = uType;
}

UHINT	GetShipCabinType(SLONG lShipIndex, SLONG lCabinIndex)
{
	return ZoneShip[lShipIndex].Cabin[lCabinIndex].CurrType;
}

void	SetShipCabinSpecialIndex(SLONG lShipIndex, SLONG lCabinIndex, SHINT lSpecialIndex)
{
	ZoneShip[lShipIndex].Cabin[lCabinIndex].SpecialIndex = lSpecialIndex;
}

SHINT	GetShipCabinSpecialIndex(SLONG lShipIndex, SLONG lCabinIndex)
{
	return ZoneShip[lShipIndex].Cabin[lCabinIndex].SpecialIndex;
}

void	SetShipCabinItem(SLONG lShipIndex, SLONG lCabinIndex, TPOS_ITEM *lpItem)
{
	ZoneShip[lShipIndex].Cabin[lCabinIndex].Item = *lpItem;
}

void	GetShipCabinItem(SLONG lShipIndex, SLONG lCabinIndex, TPOS_ITEM *lpItem)
{
	*lpItem = ZoneShip[lShipIndex].Cabin[lCabinIndex].Item;
}
