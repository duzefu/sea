/*
**	NetGE_Treasury.cpp 
**	treasury functions.
**
**	Hawke,	2003.05.26.	
*/
#include "NetGE_Mainfunc.h"

TPOS_TREASURY	Treasury[MAX_TREASURY_PER_WORLD];

// --------------------------------------------------------------------------------------
void	ChangeSailMapPositionToLongitudeAndLatitude(SLONG X, SLONG Y, SDOUBLE &Longitude, SDOUBLE &Latitude)
{
	// West
	if(X < 450)
    {
        Longitude = (SDOUBLE)((X - 450) / 10);         
    }
	// East
    if(X > 450)
    {
        Longitude = (SDOUBLE)((X - 450) / 10);
    }
	// North
    if(Y < 750)
    {
        Latitude = (SDOUBLE)((750 - Y) / 10);        
    }
	// South
    if(Y > 750)
    {
        Latitude = (SDOUBLE)((750 - Y) / 10);        
    }
}
// --------------------------------------------------------------------------------------
void	ChangeZonePositionToLongitudeAndLatitude(DWORD ZoneType, SLONG X, SLONG Y, SDOUBLE &Longitude, SDOUBLE &Latitude)
{
	switch(ZoneType)
	{
	case CITY_BIRTH:
	case CITY_NEWBIE:
	case CITY_NORMAL:
	case CITY_FINDGOLD:
	case CITY_PK:
	case FIELD_BIRTH:
	case FIELD_NEWBIE:
	case FIELD_NORMAL:
	case FIELD_FINDGOLD:
	case FIELD_PK:		
		break;
	case SAIL_BIRTH:
	case SAIL_NEWBIE:
	case SAIL_NORMAL:
	case SAIL_FINDGOLD:
	case SAIL_PK:		
		break;
	}
}
// --------------------------------------------------------------------------------------
void	InitTreasury()
{
	LOCK_TREASURY(0);
	memset(Treasury, 0x0, sizeof(TPOS_TREASURY) * MAX_TREASURY_PER_WORLD);	
	UNLOCK_TREASURY(0);
}
// --------------------------------------------------------------------------------------
void	FreeTreasury()
{
}
// --------------------------------------------------------------------------------------
void	SetTreasuryMapPartNo(ULONG Index, UHINT PartNo)
{
	Treasury[Index].MapPartNo = PartNo;
}
// --------------------------------------------------------------------------------------
UHINT	GetTreasuryMapPartNo(ULONG Index)
{
	return	Treasury[Index].MapPartNo;
}
// --------------------------------------------------------------------------------------
void	SetTreasuryMapRedPoint(ULONG Index, SLONG X, SLONG Y)
{
	Treasury[Index].MapRedPointX = X;
	Treasury[Index].MapRedPointY = Y;
}
// --------------------------------------------------------------------------------------
void	GetTreasuryMapRedPoint(ULONG Index, SLONG &X, SLONG &Y)
{
	X = Treasury[Index].MapRedPointX;	
	Y = Treasury[Index].MapRedPointY;	
}
// --------------------------------------------------------------------------------------
void	SetTreasuryRequestLevel(ULONG Index, UHINT Level)
{
	Treasury[Index].RequestLevel = Level;
}
// --------------------------------------------------------------------------------------
UHINT	GetTreasuryRequestLevel(ULONG Index)
{
	return	Treasury[Index].RequestLevel;
}
// --------------------------------------------------------------------------------------
void	SetTreasuryTimeLimit(ULONG Index, ULONG Time)
{
	Treasury[Index].TimeLimit = Time;
}
// --------------------------------------------------------------------------------------
ULONG	GetTreasuryTimeLimit(ULONG Index)
{
	return	Treasury[Index].TimeLimit;
}
// --------------------------------------------------------------------------------------
void	SetTreasuryFindOutZoneName(ULONG Index, char *ZoneName)
{
	strcpy(Treasury[Index].FindOutZoneName, ZoneName);
}
// --------------------------------------------------------------------------------------
char*	GetTreasuryFindOutZoneName(ULONG Index)
{
	return	Treasury[Index].FindOutZoneName;
}
// --------------------------------------------------------------------------------------
void	SetTreasuryFindOutActiveNpcNo(ULONG Index, ULONG NpcNo)
{
	Treasury[Index].FindOutActiveNpcNo = NpcNo;
}
// --------------------------------------------------------------------------------------
ULONG	GetTreasuryFindOutActiveNpcNo(ULONG Index)
{
	return	Treasury[Index].FindOutActiveNpcNo;
}
// --------------------------------------------------------------------------------------
void	SetTreasuryActiveZoneName(ULONG Index, char *ZoneName)
{
	strcpy(Treasury[Index].ActiveZoneName, ZoneName);
}
// --------------------------------------------------------------------------------------
char*	GetTreasuryActiveZoneName(ULONG Index)
{
	return	Treasury[Index].ActiveZoneName;
}
// --------------------------------------------------------------------------------------
void	SetTreasuryActiveZoneAppearPoint(ULONG Index, SLONG X, SLONG Y)
{
	Treasury[Index].AppearPointX = X;
	Treasury[Index].AppearPointY = Y;
}
// --------------------------------------------------------------------------------------
void	GetTreasuryActiveZoneAppearPoint(ULONG Index, SLONG &X, SLONG &Y)
{
	X = Treasury[Index].AppearPointX;
	Y = Treasury[Index].AppearPointY;
}
// --------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------