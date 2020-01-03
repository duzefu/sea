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
#define	MAX_SHIPS_PER_ZONE			1000	//每個地圖區域中的船隻數目
//
#define	MAX_SHIP_CANNONS			6		//每艏船的最大砲台數目
#define	MAX_SHIP_CABINS				32		//每艏船的最大船艙數目


// STRUCTURES ////////////////////////////////////////////////////////////////////////////////////////////////////////
//
#pragma pack(push)
#pragma	pack(1)
//
//船隻基本資料結構
typedef	struct POS_SHIP_BS 
{
	UHINT	Type;				//類型
	CHAR	Name[32];			//名稱
	ULONG	Price;				//價格
	UHINT	SailSize;			//帆吃風面積
	UHINT	Turn;				//轉向力
	UHINT	Weight;				//重量
	UHINT	BasicSpeed;			//基本速度
	UHINT	BasicArmor;			//基本裝甲
	UHINT	BasicArmorRepair;	//基本裝甲修復值
	UHINT	BasicSailorRepair;	//基本水手恢復值
	UHINT	SailorAttackPlus;	//水手攻擊加成
	UHINT	MinNeedSailor;		//最少需求水手數
	UHINT	MaxCabin;			//最大船艙
	UHINT	MaxSailorCabin;		//最大水手室
	UHINT	MaxGunCabin;		//最大炮艙
	UHINT	MaxArmorCabin;		//最大裝甲艙
	UHINT	MaxGoodsCabin;		//最大貨艙
	UHINT	MaxSail;			//最大帆位
} TPOS_SHIP_BS, *LPTPOS_SHIP_BS;

//
//船隻撞角位資料結構
typedef	struct POS_SHIP_EMBOLON 
{
	TPOS_ITEM	Item;			//所放物品
} TPOS_SHIP_EMBOLON, *LPTPOS_SHIP_EMBOLON;

//				
//船隻船首像位資料結構
typedef	struct POS_SHIP_STATUE 
{
	TPOS_ITEM	Item;			//所放物品
} TPOS_SHIP_STATUE, *LPTPOS_SHIP_STATUE;
				
//
//船隻砲台資料結構
typedef	struct POS_SHIP_CANNON 
{
	UHINT	Attack;				//本砲的總攻擊力
	UHINT	FireCost;			//本砲的總彈藥消耗
	UCHAR	AttackRatio;		//本砲的攻擊命中率
} TPOS_SHIP_CANNON, *LPTPOS_SHIP_CANNON;


//
//船隻攻防資料結構				
typedef	struct POS_SHIP_ATTDEF 
{
	UHINT	SailorAttack;		//水手攻擊力
	UHINT	EmbolonAttack;		//撞角攻擊力
	UHINT	SailorCount;		//總水手數量
	UHINT	HealthSailorCount;	//健康的水手
	UHINT	CurrArmor;			//當前裝甲
} TPOS_SHIP_ATTDEF, *LPTPOS_SHIP_ATTDEF;
				

//
//船隻型態資料結構
typedef	struct POS_SHIP_STYLE 
{
	SLONG	FileIndex;			//圖
	SLONG	TrackIndex;			//軌跡
} TPOS_SHIP_STYLE, *LPTPOS_SHIP_STYLE;
				

//
//船隻船艙資料結構
typedef	struct POS_SHIP_CABIN 
{
	UHINT		CurrType;		//當前類型
	SHINT		SpecialIndex;	//特殊索引值
	TPOS_ITEM	Item;			//物品
} TPOS_SHIP_CABIN, *LPTPOS_SHIP_CABIN;


//
//船隻速度資料結構
typedef	struct POS_SHIP_SPEED 
{
	SLONG	AccSpeedX;		//X軸加速度
	SLONG	AccSpeedY;		//Y軸加速度
	SLONG	SpeedX;			//X軸速度
	SLONG	SpeedY;			//Y軸速度
	SLONG	SpeedLeftX;		//浮點運算的剩餘數
	SLONG	SpeedLeftY;		//浮點運算的剩餘數
} TPOS_SHIP_SPEED, *LPTPOS_SHIP_SPEED;


//
//船隻位置資料結構
typedef	struct POS_SHIP_POSITION 
{
	SLONG	X;				//座標 X
	SLONG	Y;				//座標 Y
	SLONG	Z;				//座標 Z
	SLONG	DestX;			//目標座標 X
	SLONG	DestY;			//目標座標 Y
	SLONG	DestZ;			//目標座標 Z
	SLONG	ShipDir;		//船隻方向
	SLONG	SailDir;		//帆的方向
} TPOS_SHIP_POSITION, *LPTPOS_SHIP_POSITION;


//
//船隻資料結構
typedef	struct POS_SHIP 
{
	ULONG	ID;			//船隻唯一ID
	UHINT	BaseID;		//船隻基本ID
	CHAR	Name[32];	//船隻名稱
	CHAR	Port[32];	//停放港口
	TPOS_SHIP_SPEED		Speed;		//速度
	TPOS_SHIP_POSITION	Position;	//位置
	TPOS_SHIP_STYLE		Style;		//外觀
	TPOS_SHIP_ATTDEF	AttDef;		//攻防
	TPOS_SHIP_EMBOLON	Embolon;	//撞角
	TPOS_SHIP_STATUE	Statue;		//船首像
	TPOS_SHIP_CANNON	Cannon[MAX_SHIP_CANNONS];	//炮
	TPOS_SHIP_CABIN		Cabin[MAX_SHIP_CABINS];		//船艙
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

