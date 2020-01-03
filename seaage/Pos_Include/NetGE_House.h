/*
**	NetGE_House.h 
**	House functions header.
**
**	Jack, 2002.12.9
*/
#pragma once


// DEFINES ///////////////////////////////////////////////////////////////////////////////////////////////////////////
//
#define	MAX_ZONE_HOUSES				32		//每個地圖上的最多房子數目
#define	MAX_HOUSE_BOX_ITEMS			144		//房屋的每個寶箱中的最大物品數目


// STRUCTURES ////////////////////////////////////////////////////////////////////////////////////////////////////////
//
#pragma pack(push)
#pragma	pack(1)
//
//房屋保險箱資料結構
typedef	struct	POS_HOUSE_BOX
{
	ULONG		Money;						//存放金錢
	TPOS_ITEM	Item[MAX_HOUSE_BOX_ITEMS];	//存放物品
} TPOS_HOUSE_BOX, *LPTPOS_HOUSE_BOX;

//
//房屋狀態資料結構
typedef	struct	POS_HOUSE_STATE
{
	UHINT	Size;				//房屋大小
	CHAR	CityName[32];		//所在城市
	ULONG	GuildPrice;			//工會價
	ULONG	PersonalPrice;		//個人價
	UHINT	BoxSize;			//保險箱格數
} TPOS_HOUSE_STATE, *LPTPOS_HOUSE_STATE;

//
//房屋資料結構
typedef	struct POS_HOUSE 
{
	ULONG	ID;					//唯一ID
	CHAR	Name[32];			//房屋名稱
	CHAR	OwnerName[32];		//擁有者名稱(個人)
	CHAR	GuildName[32];		//工會名稱
	TPOS_HOUSE_BOX		Box[2];	//保險箱A,B
	TPOS_HOUSE_STATE	State;	//房屋相關屬性
} TPOS_HOUSE, *LPTPOS_HOUSE;

#pragma pack(pop)

// GLOBALS ///////////////////////////////////////////////////////////////////////////////////////////////////////////
//
extern	TPOS_HOUSE	ZoneHouse[MAX_ZONE_HOUSES];

// FUNCTIONS /////////////////////////////////////////////////////////////////////////////////////////////////////////
//
extern	void	SetHouseID(SLONG lIndex, ULONG uID);
extern	ULONG	GetHouseID(SLONG lIndex);
extern	void	SetHouseName(SLONG lIndex, CHAR *szName);
extern	CHAR*	GetHouseName(SLONG lIndex);
extern	void	SetHouseOwnerName(SLONG lIndex, CHAR *szOwnerName);
extern	CHAR*	GetHouseOwnerName(SLONG lIndex);
extern	void	SetHouseGuildName(SLONG lIndex, CHAR *szGuildName);
extern	CHAR*	GetHouseGuildName(SLONG lIndex);
//
extern	void	SetHouseBoxMoney(SLONG lHouseIndex, SLONG lBoxIndex, ULONG uMoney);
extern	ULONG	GetHouseBoxMoney(SLONG lHouseIndex, SLONG lBoxIndex);
extern	void	SetHouseBoxItem(SLONG lHouseIndex, SLONG lBoxIndex, SLONG lItemIndex, TPOS_ITEM *lpItem);
extern	void	GetHouseBoxItem(SLONG lHouseIndex, SLONG lBoxIndex, SLONG lItemIndex, TPOS_ITEM *lpItem);
//
extern	void	SetHouseSize(SLONG lIndex, UHINT uSize);
extern	UHINT	GetHouseSize(SLONG lIndex);
extern	void	SetHouseCityName(SLONG lIndex, CHAR *szCityName);
extern	CHAR*	GetHouseCityName(SLONG lIndex);
extern	void	SetHouseGuildPrice(SLONG lIndex, ULONG uPrice);
extern	ULONG	GetHouseGuildPrice(SLONG lIndex);
extern	void	SetHousePersonalPrice(SLONG lIndex, ULONG uPrice);
extern	ULONG	GetHousePersonalPrice(SLONG lIndex);
extern	void	SetHouseBoxSize(SLONG lIndex, UHINT uBoxSize);
extern	UHINT	GetHouseBoxSize(SLONG lIndex);

