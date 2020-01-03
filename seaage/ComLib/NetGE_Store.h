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
#define	MAX_GAME_STORE_BASES			256		//�C�����Ҧ��򥻰ө���ƪ��ƥ�
#define	MAX_ZONE_STORES					32		//�C�Ӱϰ줤�ө����ƥ�
#define	MAX_STORE_ITEMS					36		//�C�Ӱө����X�⪫�~���̤j�ƥ�
#define	MAX_STORE_CUSTOMERS				10		//�ө����P�ɶR�檺�U�ȳ̤j�ƥ�
#define	STORE_ITEM_PRODUCE_BASE			100		//�ө����~�Ͳ��v���
#define	STORE_ITEM_PRICE_QUOTIETY_BASE	100		//�ө����~����Y�ư��


// Store item flags
#define	STORE_ITEM_TYPE_MASK		0x0000000f	//���~�������X
#define	STORE_ITEM_TYPE_PRODUCT		0x00000001	//�ө��۲����~
#define	STORE_ITEM_TYPE_PLAYER		0x00000002	//�ө��R�i�����a�����~(�ө��L���X���~)

//
// STRUCTS //////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//�C�������ө��򥻸�ƪ����c
//
typedef	struct POS_STORE_BASE
{
	UHINT	ItemBaseID[MAX_STORE_ITEMS];	//���~����ID
	UHINT	InitCount[MAX_STORE_ITEMS];		//��l�ƪ��ƶq
	SLONG	InitProduce[MAX_STORE_ITEMS];	//��l�ƪ��Ͳ��v
	SLONG	PriceQuotiety[MAX_STORE_ITEMS];	//����Y��
} TPOS_STORE_BASE, *LPTPOS_STORE_BASE;


//
//�ϰ줤�ө����~��Ƶ��c
//
typedef	struct POS_STORE_ITEM
{
	ULONG		Flags;			//�Ӫ��~���Х�
	UHINT		Count;			//�ө��֦��Ӫ��~���ƶq
	ULONG		Price;			//��X����
	union
	{
		UHINT	Produce;		//�ө��ۤv���X�����~: �Ͳ��q
		UHINT	Consume;		//���a�浹�ө������~: ���Ӷq
	};
	union
	{
		UHINT	AddUpProduce;	//�ө��ۤv���X�����~: �֭p�Ͳ��q
		UHINT	AddUpConsume;	//���a�浹�ө������~: �֭p���Ӷq
	};
	TPOS_ITEM	Item;			//�X�⪺���~

} TPOS_STORE_ITEM, *LPPOS_STORE_ITEM;

//
//�ϰ줤�ө���Ƶ��c
//
typedef	struct POS_ZONE_STORE 
{
	SLONG			Flag;					//�ө��лx
	CHAR			StoreName[32];			//�ө��W��
	SLONG			StorePriceQuotiety;		//����Y��
	TPOS_STORE_ITEM	StoreItem[MAX_STORE_ITEMS];				//�X�⪫�~�C��
	CHAR			CustomerName[MAX_STORE_CUSTOMERS][32];	//�U�ȦW��
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

