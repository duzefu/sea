/*
**	NetGE_Port.h 
**	Port functions header.
**
**	Jack, 2002.12.9
*/
#pragma once


// DEFINES ///////////////////////////////////////////////////////////////////////////////////////////////////////////
//
#define	MAX_PORT_SUPPLY_ITEMS		8	//�C�Ӵ�f�S���ƥ�
#define	MAX_PORT_NEED_ITEMS			8	//�C�Ӵ�f�y��~�ƥ�
#define	MAX_PORT_SHIPS				16	//�C�Ӵ�f�@��ĥ�ƥ�
#define	MAX_PORT_CANNONS			16	//�C�Ӵ�f���x�ƥ�
//
#define	MAX_PORTS_PER_ZONE			16	//�C�Ӱϰ줤�̦h����f�ƥ�
//
// STRUCTURES ////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma pack(push)
#pragma	pack(1)

//
//��f���~���
typedef	struct  POS_PORT_ITEM
{
	UHINT	ItemBaseID;		//���~�򥻪�ID
	ULONG	SellPrice;		//���~��X����
	ULONG	BuyPrice;		//���~�R�J����
	SLONG	Stocks;			//�w�s�q
	UHINT	Wastage;		//���Ӷq(�C20����)
	UHINT	Output;			//�X���q(�C20����)
} TPOS_PORT_ITEM, *LPTPOS_PORT_ITEM;

//
//��f����
typedef	struct	POS_PORT_SHIP
{
	ULONG	ID;				//����ߤ@ID
	ULONG	Flag;			//����лx
} TPOS_PORT_SHIP, *LPTPOS_PORT_SHIP;


//
//��f���x���
typedef	struct POS_PORT_CANNON 
{
	UHINT	Type;			//����
	SLONG	StandX;			//�ϰ줤���I�y��
	SLONG	StandY;			//�ϰ줤���I�y��
	UHINT	AttackDistance;	//�����Z��
	UHINT	AttackRange;	//�����d��
	UHINT	Damage;			//�����O
	UHINT	CurrHp;			//�ͩR�O
	UHINT	MaxHp;			//�̤j�ͩR�O
	ULONG	AI;				//AI
	ULONG	State;			//���A
	UHINT	Level;			//����
} TPOS_PORT_CANNON, *LPTPOS_PORT_CANNON;


//
//��f�򥻸��
typedef	struct POS_PORT_BASIC 
{
	UHINT	Level;			//��f����
	UHINT	CurrArmor;		//��f�˥�
	UHINT	MaxArmor;		//�̤j�˥�
	UHINT	GunCount;		//�����ƶq
	UHINT	ShipCount;		//��ƶq
} TPOS_PORT_BASIC, *LPTPOS_PORT_BASIC;

//
//��f���
typedef	struct POS_PORT 
{
	ULONG	ID;					//�ߤ@ID
	CHAR	Name[32];			//��f�W��
	CHAR	ZoneName[32];		//�ϰ�W��
	CHAR	CountryName[32];	//���ݰ�a
	CHAR	GuildName[32];		//���ݤu�|
	SLONG	Longitude;			//�g��
	SLONG	Latitude;			//�n��
	SLONG	X;					//�����I�ϰ�y��
	SLONG	Y;					//�����I�ϰ�y��
	ULONG	InvestMoney;		//�����B
	ULONG	SaveMoney;			//�s����B
	TPOS_PORT_BASIC		Basic;	//�򥻭�
	TPOS_PORT_ITEM		SupplyItem[MAX_PORT_SUPPLY_ITEMS];	//�S��
	TPOS_PORT_ITEM		NeedItem[MAX_PORT_NEED_ITEMS];		//�y��~
	TPOS_PORT_SHIP		Ship[MAX_PORT_SHIPS];				//��
	TPOS_PORT_CANNON	Cannon[MAX_PORT_CANNONS];			//��
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
