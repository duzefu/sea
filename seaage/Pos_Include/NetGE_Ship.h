/*
**	NetGE_Ship.h 
**	ship functions header.
**
**	Jack, 2002.12.9
*/
#pragma once
#include "NetGE_Item.h"


// DEFINES ///////////////////////////////////////////////////////////////////////////////////////////////////////////
//
#define	MAX_SHIPS_PER_ZONE			1000	//�C�Ӧa�ϰϰ줤����ƥ�
//
#define	MAX_SHIP_CANNONS			6		//�C�F��̤j���x�ƥ�
#define	MAX_SHIP_CABINS				32		//�C�F��̤j��ƥ�


// STRUCTURES ////////////////////////////////////////////////////////////////////////////////////////////////////////
//
#pragma pack(push)
#pragma	pack(1)
//
//��򥻸�Ƶ��c
typedef	struct POS_SHIP_BS 
{
	UHINT	Type;				//����
	CHAR	Name[32];			//�W��
	ULONG	Price;				//����
	UHINT	SailSize;			//�|�Y�����n
	UHINT	Turn;				//��V�O
	UHINT	Weight;				//���q
	UHINT	BasicSpeed;			//�򥻳t��
	UHINT	BasicArmor;			//�򥻸˥�
	UHINT	BasicArmorRepair;	//�򥻸˥ҭ״_��
	UHINT	BasicSailorRepair;	//�򥻤����_��
	UHINT	SailorAttackPlus;	//��������[��
	UHINT	MinNeedSailor;		//�ֻ̤ݨD�����
	UHINT	MaxCabin;			//�̤j�
	UHINT	MaxSailorCabin;		//�̤j�����
	UHINT	MaxGunCabin;		//�̤j����
	UHINT	MaxArmorCabin;		//�̤j�˥ҿ�
	UHINT	MaxGoodsCabin;		//�̤j�f��
	UHINT	MaxSail;			//�̤j�|��
} TPOS_SHIP_BS, *LPTPOS_SHIP_BS;

//
//��������Ƶ��c
typedef	struct POS_SHIP_EMBOLON 
{
	TPOS_ITEM	Item;			//�ҩ񪫫~
} TPOS_SHIP_EMBOLON, *LPTPOS_SHIP_EMBOLON;

//				
//�������Ƶ��c
typedef	struct POS_SHIP_STATUE 
{
	TPOS_ITEM	Item;			//�ҩ񪫫~
} TPOS_SHIP_STATUE, *LPTPOS_SHIP_STATUE;
				
//
//����x��Ƶ��c
typedef	struct POS_SHIP_CANNON 
{
	UHINT	Attack;				//�������`�����O
	UHINT	FireCost;			//�������`�u�Į���
	UCHAR	AttackRatio;		//�����������R���v
} TPOS_SHIP_CANNON, *LPTPOS_SHIP_CANNON;


//
//��𨾸�Ƶ��c				
typedef	struct POS_SHIP_ATTDEF 
{
	UHINT	SailorAttack;		//��������O
	UHINT	EmbolonAttack;		//���������O
	UHINT	SailorCount;		//�`����ƶq
	UHINT	HealthSailorCount;	//���d������
	UHINT	CurrArmor;			//��e�˥�
} TPOS_SHIP_ATTDEF, *LPTPOS_SHIP_ATTDEF;
				

//
//����A��Ƶ��c
typedef	struct POS_SHIP_STYLE 
{
	SLONG	FileIndex;			//��
	SLONG	TrackIndex;			//�y��
} TPOS_SHIP_STYLE, *LPTPOS_SHIP_STYLE;
				

//
//����Ƶ��c
typedef	struct POS_SHIP_CABIN 
{
	UHINT		CurrType;		//��e����
	SHINT		SpecialIndex;	//�S����ޭ�
	TPOS_ITEM	Item;			//���~
} TPOS_SHIP_CABIN, *LPTPOS_SHIP_CABIN;


//
//��t�׸�Ƶ��c
typedef	struct POS_SHIP_SPEED 
{
	SLONG	AccSpeedX;		//X�b�[�t��
	SLONG	AccSpeedY;		//Y�b�[�t��
	SLONG	SpeedX;			//X�b�t��
	SLONG	SpeedY;			//Y�b�t��
	SLONG	SpeedLeftX;		//�B�I�B�⪺�Ѿl��
	SLONG	SpeedLeftY;		//�B�I�B�⪺�Ѿl��
} TPOS_SHIP_SPEED, *LPTPOS_SHIP_SPEED;


//
//���m��Ƶ��c
typedef	struct POS_SHIP_POSITION 
{
	SLONG	X;				//�y�� X
	SLONG	Y;				//�y�� Y
	SLONG	Z;				//�y�� Z
	SLONG	DestX;			//�ؼЮy�� X
	SLONG	DestY;			//�ؼЮy�� Y
	SLONG	DestZ;			//�ؼЮy�� Z
	SLONG	ShipDir;		//���V
	SLONG	SailDir;		//�|����V
} TPOS_SHIP_POSITION, *LPTPOS_SHIP_POSITION;


//
//���Ƶ��c
typedef	struct POS_SHIP 
{
	ULONG	ID;			//��ߤ@ID
	UHINT	BaseID;		//���ID
	CHAR	Name[32];	//��W��
	CHAR	Port[32];	//�����f
	TPOS_SHIP_SPEED		Speed;		//�t��
	TPOS_SHIP_POSITION	Position;	//��m
	TPOS_SHIP_STYLE		Style;		//�~�[
	TPOS_SHIP_ATTDEF	AttDef;		//��
	TPOS_SHIP_EMBOLON	Embolon;	//����
	TPOS_SHIP_STATUE	Statue;		//���
	TPOS_SHIP_CANNON	Cannon[MAX_SHIP_CANNONS];	//��
	TPOS_SHIP_CABIN		Cabin[MAX_SHIP_CABINS];		//�
} TPOS_SHIP, *LPTPOS_SHIP;
				

//TPOS_SHIP_DB	Ship	TPOS_SHIP

#pragma	pack(pop)

// GLOBALS ///////////////////////////////////////////////////////////////////////////////////////////////////////////
//
extern	TPOS_SHIP	ZoneShip[MAX_SHIPS_PER_ZONE];

// FUNCTIONS /////////////////////////////////////////////////////////////////////////////////////////////////////////
//
extern	void	SetShipID(SLONG lIndex, ULONG uID);
extern	ULONG	GetShipID(SLONG lIndex);
extern	void	SetShipBaseID(SLONG lIndex, UHINT uBaseID);
extern	UHINT	GetShipBaseID(SLONG lIndex);
extern	void	SetShipName(SLONG lIndex, CHAR *szName);
extern	CHAR*	GetShipName(SLONG lIndex);
extern	void	SetShipPortName(SLONG lIndex, CHAR *szName);
extern	CHAR*	GetShipPortName(SLONG lIndex);
//
extern	void	SetShipAccSpeedX(SLONG lIndex, SLONG lAccX);
extern	SLONG	GetShipAccSpeedX(SLONG lIndex);
extern	void	SetShipAccSpeedY(SLONG lIndex, SLONG lAccY);
extern	SLONG	GetShipAccSpeedY(SLONG lIndex);
extern	void	SetShipSpeedX(SLONG lIndex, SLONG lSpeedX);
extern	SLONG	GetShipSpeedX(SLONG lIndex);
extern	void	SetShipSpeedY(SLONG lIndex, SLONG lSpeedY);
extern	SLONG	GetShipSpeedY(SLONG lIndex);
extern	void	SetShipSpeedLeftX(SLONG lIndex, SLONG lLeftX);
extern	SLONG	GetShipSpeedLeftX(SLONG lIndex);
extern	void	SetShipSpeedLeftY(SLONG lIndex, SLONG lLeftY);
extern	SLONG	GetShipSpeedLeftY(SLONG lIndex);
//
extern	void	SetShipPosition(SLONG lIndex, SLONG lX, SLONG lY, SLONG lZ);
extern	void	GetShipPosition(SLONG lIndex, SLONG *lX, SLONG *lY, SLONG *lZ);
extern	void	SetShipDestPosition(SLONG lIndex, SLONG lX, SLONG lY, SLONG lZ);
extern	void	GetShipDestPosition(SLONG lIndex, SLONG *lX, SLONG *lY, SLONG *lZ);
extern	void	SetShipBodyDir(SLONG lIndex, SLONG lDir);
extern	SLONG	GetShipBodyDir(SLONG lIndex);
extern	void	SetShipSailDir(SLONG lIndex, SLONG lDir);
extern	SLONG	GetShipSailDir(SLONG lIndex);
//
extern	void	SetShipFileImageIndex(SLONG lIndex, SLONG lFileIndex);
extern	SLONG	GetShipFileImageIndex(SLONG lIndex);
extern	void	SetShipTrackImageIndex(SLONG lIndex, SLONG lTrackIndex);
extern	SLONG	GetShipTrackImageIndex(SLONG lIndex);
//
extern	void	SetShipSailorAttack(SLONG lIndex, UHINT uAttack);
extern	UHINT	GetShipSailorAttack(SLONG lIndex);
extern	void	SetShipEmbolonAttack(SLONG lIndex, UHINT uAttack);
extern	UHINT	GetShipEmbolonAttack(SLONG lIndex);
extern	void	SetShipSailorCount(SLONG lIndex, UHINT uCount);
extern	UHINT	GetShipSailorCount(SLONG lIndex);
extern	void	SetShipHealthSailorCount(SLONG lIndex, UHINT uCount);
extern	UHINT	GetShipHealthSailorCount(SLONG lIndex);
extern	void	SetShipCurrentArmor(SLONG lIndex, UHINT uArmor);
extern	UHINT	GetShipCurrentArmor(SLONG lIndex);
//
extern	void	SetShipEmbolonItem(SLONG lIndex, TPOS_ITEM *lpItem);
extern	void	GetShipEmbolonItem(SLONG lIndex, TPOS_ITEM *lpItem);
extern	void	SetShipStatueItem(SLONG lIndex, TPOS_ITEM *lpItem);
extern	void	GetShipStatueItem(SLONG lIndex, TPOS_ITEM *lpItem);
//
extern	void	SetShipCannonAttack(SLONG lShipIndex, SLONG lCannonIndex, UHINT uAttack);
extern	UHINT	GetShipCannonAttack(SLONG lShipIndex, SLONG lCannonIndex);
extern	void	SetShipCannonFireCost(SLONG lShipIndex, SLONG lCannonIndex, UHINT uCost);
extern	UHINT	GetShipCannonFireCost(SLONG lShipIndex, SLONG lCannonIndex);
extern	void	SetShipCannonAttackRatio(SLONG lShipIndex, SLONG lCannonIndex, UCHAR uRatio);
extern	UCHAR	GetShipCannonAttackRatio(SLONG lShipIndex, SLONG lCannonIndex);
//
extern	void	SetShipCabinType(SLONG lShipIndex, SLONG lCabinIndex, UHINT uType);
extern	UHINT	GetShipCabinType(SLONG lShipIndex, SLONG lCabinIndex);
extern	void	SetShipCabinSpecialIndex(SLONG lShipIndex, SLONG lCabinIndex, SHINT lSpecialIndex);
extern	SHINT	GetShipCabinSpecialIndex(SLONG lShipIndex, SLONG lCabinIndex);
extern	void	SetShipCabinItem(SLONG lShipIndex, SLONG lCabinIndex, TPOS_ITEM *lpItem);
extern	void	GetShipCabinItem(SLONG lShipIndex, SLONG lCabinIndex, TPOS_ITEM *lpItem);

