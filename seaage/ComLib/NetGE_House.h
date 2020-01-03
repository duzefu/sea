/*
**	NetGE_House.h 
**	House functions header.
**
**	Jack, 2002.12.9
*/
#pragma once


// DEFINES ///////////////////////////////////////////////////////////////////////////////////////////////////////////
//
#define	MAX_ZONE_HOUSES				32		//�C�Ӧa�ϤW���̦h�Фl�ƥ�
#define	MAX_HOUSE_BOX_ITEMS			144		//�ЫΪ��C���_�c�����̤j���~�ƥ�


// STRUCTURES ////////////////////////////////////////////////////////////////////////////////////////////////////////
//
#pragma pack(push)
#pragma	pack(1)
//
//�ЫΫO�I�c��Ƶ��c
typedef	struct	POS_HOUSE_BOX
{
	ULONG		Money;						//�s�����
	TPOS_ITEM	Item[MAX_HOUSE_BOX_ITEMS];	//�s�񪫫~
} TPOS_HOUSE_BOX, *LPTPOS_HOUSE_BOX;

//
//�ЫΪ��A��Ƶ��c
typedef	struct	POS_HOUSE_STATE
{
	UHINT	Size;				//�ЫΤj�p
	CHAR	CityName[32];		//�Ҧb����
	ULONG	GuildPrice;			//�u�|��
	ULONG	PersonalPrice;		//�ӤH��
	UHINT	BoxSize;			//�O�I�c���
} TPOS_HOUSE_STATE, *LPTPOS_HOUSE_STATE;

//
//�Ыθ�Ƶ��c
typedef	struct POS_HOUSE 
{
	ULONG	ID;					//�ߤ@ID
	CHAR	Name[32];			//�ЫΦW��
	CHAR	OwnerName[32];		//�֦��̦W��(�ӤH)
	CHAR	GuildName[32];		//�u�|�W��
	TPOS_HOUSE_BOX		Box[2];	//�O�I�cA,B
	TPOS_HOUSE_STATE	State;	//�Ыά����ݩ�
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

