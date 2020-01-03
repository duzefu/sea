/*
**	NetGE_Character.h 
**	character functions header.
**
**	Jack, 2002.12.9
**
**	Jack, 2003.5.14.
**		-- Added CareerLevel to character structure.
**
*/
#pragma once
#include "NetGE_Item.h"

//
// DEFINES //////////////////////////////////////////////////////////////////////////////////////////////////
//
#define	MAX_CHARACTER_PER_ZONE			1000		//每個ZONE中能夠容納的人數(NPC, PLAYER, ...)
//
#define	MAX_CHARACTER_BAG_ITEMS			27			//人物背包物品數量
#define	MAX_CHARACTER_SASH_ITEMS		4			//人物腰包物品數量
#define	MAX_CHARACTER_TRANS_ITEMS		3			//人物傳送物品數量
#define	MAX_CHARACTER_BANK_ITEMS		36			//人物銀行物品數量
#define	MAX_CHARACTER_SKILLS			36			//人物技能數量
#define	MAX_CHARACTER_FN_SKILLS			8			//人物快捷鍵技能
#define	MAX_CHARACTER_DEFAULT_SKILLS	12			//人物默認技能
#define	MAX_CHARACTER_DEFAULT_ITEMS		1			//人物默認物品
#define	MAX_CHARACTER_TEAM_MEMBERS		8			//人物同隊人員, 隊長為0. 
#define	MAX_CHARACTER_ENEMY_MEMBERS		8		 	//人物的敵人列表
#define	MAX_CHARACTER_PARTS				7			//人物組件數目
#define	MAX_CHARACTER_QUESTS			16			//人物能夠接受的最多任務數目


//(角色的1/0狀態) POS_CHARACTER_STATE::BitState
#define	CHARACTER_BAG_OPENED			0x00000001	//人物背包在打開狀態
#define	CHARACTER_ON_FIGHT				0x00000002	//人物目前在戰鬥狀態
#define	CHARACTER_IS_DEAD				0x00000004	//人物已經死亡
#define	CHARACTER_ON_SEA				0x00000008	//人物目前在海上
//和陸戰有關的狀態
#define	CHARACTER_ON_DEFENCE			0x00000010	//人物在防禦狀態
#define	CHARACTER_DODGE       			0x00000020	//人物躲避中...移動帶殘影
#define CHARACTER_ON_BLOCK              0X00000040  //格檔(提高npc的格檔機率)
#define CHARACTER_MAGIC_REBOUND         0X00000080  //魔法反彈(有一定類型的法術)
#define CHARACTER_SHOW_SUBTIL           0X00000100  //隱形(自己人可見,敵人不可見)
#define CHARACTER_SPEED_DELAY1          0X00000200  //遲緩1(只有在移動的時候..速度變慢,動畫播放速度變慢)
#define CHARACTER_SPEED_DELAY2          0X00000400  //遲緩2遲緩2(動畫速度播放加快,移動速度變慢)
#define CHARACTER_WITHOUT_EQUAL         0X00000800  //無敵(人物上圖需要閃爍)
#define CHARACTER_BLACK_NPC             0X00001000  //黑人狀態
#define CHARACTER_NPC_FAINT             0X00002000  //NPC摔倒狀態
#define CHARACTER_NPC_STAND_UP          0X00004000  //NPC爬起來

#define CHARACTER_HEAD_SLEEP            0X00008000  //頭昏
#define CHARACTER_ON_SLEEP              0X00010000  //睡眠
#define CHARACTER_ON_SWIVET             0X00020000  //狂亂
#define CHARACTER_ON_BLIND              0X00040000  //失明
#define CHARACTER_UP_DEFENCE            0X00080000  //增加防禦
//和海戰有關係的狀態
#define CHARACTER_BOAT_ROTATE           0X00100000  //旋轉(被動)船隻
#define CHARACTER_BOAT_FIRE             0X00200000  //著火(被動)船隻
#define CHARACTER_BOAT_EXPLODE          0X00400000  //爆炸(被動)船隻
#define CHARACTER_BOAT_SAILHURT         0X00800000  //帆損害 (被動)	船隻
#define CHARACTER_BOAT_RUDDERHURT       0X01000000  //舵損害 (被動)	船隻
#define CHARACTER_BOAT_PRETEND          0X02000000  //偽裝 (主動)	船隻
#define CHARACTER_BOAT_HALFDOWN         0X04000000  //半沉	船隻
#define CHARACTER_BOAT_OCTOPUS          0X08000000  //章魚 (被動)	船隻
//
#define	CHARACTER_IS_PAUSE				0x40000000	//人物正在暫停原來動作中
#define	CHARACTER_SPECIAL_ITEM			0x80000000	//攜帶特定物品(用於怪物,死亡掉出)
//------------------------------------------------------------
//NPC類別(NPC KIND)
//-------------------------
#define NPC_KIND_EMPLACEMENT			0   //砲台
#define NPC_KIND_GUIDEPOST				1   //路牌
#define NPC_KIND_NORMAL_MONSTER			2   //普通怪物
#define NPC_KIND_HEADER_MONSTER			3   //頭目怪物
#define NPC_KIND_BOSS_MONSTER			4   //BOSS怪物
#define NPC_KIND_THIEF_MONSTER			5   //小偷怪
#define NPC_KIND_TREASURE_MONSTER		6   //寶物怪
#define NPC_KIND_GUARD					7   //警衛
#define NPC_KIND_NPC					8   //閒人(村人)
#define NPC_KIND_PLAYER					9   //玩家
#define NPC_KIND_TREASURE				10  //寶藏(小島)
#define NPC_KIND_MERMAID				11  //美人魚(會改變背景音樂)
#define NPC_KIND_TRAP					12  //陷阱
#define NPC_KIND_SUBMERGED_ROCK			13  //暗礁
#define NPC_KIND_BURBLE					14  //漩渦
#define NPC_KIND_STATUARY				15  //雕像
#define	NPC_KIND_CORPSE					16	//屍體
#define MAX_NPC_KINDS				    17  //總的類別數目

//--------------------------------------------------------------
//TEAM MEMBER FLAGS
//------------------------------
#define	TEAM_MEMBER_IN_SAME_ZONE		0x00000001	//在同一個ZONE中
//
//
//---------------------------------------------------------------
//QUEST PAYTYPE DEFINES (TPOS_QUEST_INFO::PayType)
//---------------------------------------------------------------
#define	QUEST_PAY_NONE					0	//無報酬
#define	QUEST_PAY_PRESTIGE				1	//聲望報酬
#define	QUEST_PAY_MONEY					2	//金錢報酬
#define	QUEST_PAY_ITEM					3	//物品報酬
#define	QUEST_PAY_STR					4	//力量
#define	QUEST_PAY_INT					5	//智慧
#define	QUEST_PAY_WIT					6	//體質
#define	QUEST_PAY_LUCKY					7	//運氣
#define	QUEST_PAY_KEEPITEM				8	//信物
//
//---------------------------------------------------------------
//QUEST TYPE DEFINES (TPOS_QUEST_INFO::QuestType)
//---------------------------------------------------------------
#define	QUEST_TYPE_NONE					0	//無任務
#define	QUEST_TYPE_DELIVER				1	//送貨任務 (deliver goods)
#define	QUEST_TYPE_SCRIPT				2	//劇本任務 (be written in script file)


// STRUCTURES ///////////////////////////////////////////////////////////////////////////////////////////////
//
#pragma pack(push)
#pragma pack(1)


//
//Level 0 Structures ----------------------
//

//
//角色註冊資料結構
typedef	struct POS_CHARACTER_REG
{
	CHAR	ID[32];			//帳號名稱
	CHAR	MainName[32];	//角色名稱
	CHAR	NickName[32];	//角色暱稱
	CHAR	Country;		//所屬國家
	CHAR	Eyes;			//眼睛
	CHAR	Mouth;			//嘴
	CHAR	Color;			//顏色
	DWORD	Index;			//索引
	DWORD	DefaultIndex;	//默認索引
} TPOS_CHARACTER_REG, *LPTPOS_CHARACTER_REG;


//
//角色默認資料結構
typedef	struct POS_CHARACTER_DEFAULT 
{
	UHINT	Index;			//角色索引
	SLONG	FileIndex;		//角色影像文件索引
	CHAR	Sex;			//性別
	CHAR	Career;			//職業
	CHAR	Color;			//顏色
	CHAR	Eyes;			//眼睛
	CHAR	Mouth;			//嘴
	CHAR	Country;		//所屬國家
	UHINT	Str;			//力量
	UHINT	Ins;			//直覺
	UHINT	Wis;			//智力
	UHINT	Lucky;			//運氣
	UHINT	Hp;				//生命力
	UHINT	Mp;				//法力
	UHINT	Mspeed;			//移動速度
	UHINT	Attack;			//攻擊力
	UHINT	Defence;		//防禦力
	SLONG	Sight;			//視野
	SHINT		Skill[MAX_CHARACTER_DEFAULT_SKILLS];	//技能
	POS_ITEM	Item[MAX_CHARACTER_DEFAULT_ITEMS];		//物品
} TPOS_CHARACTER_DEFAULT, *LPTPOS_CHARACTER_DEFAULT;


//角色資料標頭
typedef	struct POS_CHARACTER_HEADER 
{
	UHINT	Type;			//類型
	UHINT	Index;			//索引
} TPOS_CHARACTER_HEADER, *LPTPOS_CHARACTER_HEADER;


//角色姓名
typedef	struct POS_CHARACTER_NAME 
{
	CHAR	ID[32];			//帳號
	CHAR	MainName[32];	//角色名字
	CHAR	NickName[32];	//暱稱
	ULONG	QQID;			//QQ唯一ID
	SLONG	Index;			//本帳號的第幾個角色, 0~3
} TPOS_CHARACTER_NAME, *LPTPOS_CHARACTER_NAME;


//角色外觀
typedef	struct POS_CHARACTER_STYLE 
{
	CHAR	Picture;		//外觀
	CHAR	Color;			//顏色
	CHAR	Eyes;			//眼睛
	CHAR	Mouth;			//嘴巴
	CHAR	MainNameColor;	//名字顏色
	CHAR	NickNameColor;	//暱稱顏色
	CHAR	MessageColor;	//訊息顏色
	CHAR	TalkBackColor;	//聊天訊息背景顏色
	ULONG	Logo;			//工會標誌
	SLONG	FileIndex;		//當前圖像索引
	SLONG	LandFileIndex;	//陸地圖像索引
	SLONG	SeaFileIndex;	//海洋圖像索引
	ULONG	PartRGB[MAX_CHARACTER_PARTS];	//組裝部件顏色, ARGB.
	ULONG	NameColorTicks;	//紀錄人物
} TPOS_CHARACTER_STYLE, *LPTPOS_CHARACTER_STYLE;


//角色位置
typedef	struct POS_CHARACTER_POSITION 
{
	CHAR	ZoneName[32];	//所在區域
	SLONG	X;				//當前座標
	SLONG	Y;				//當前座標
	SLONG	Z;				//當前座標
	UCHAR	Dir;			//人物方向
	SLONG	DirFrame;		//某個方向幀
	SLONG	Frame;			//整個動畫圖像幀
	SLONG	StopRadius;		//阻擋半徑
	union
	{
		SLONG	DestX;				//移動: 目標座標 X
		SLONG	SequentialStep;		//連擊: 是否進行下一個連續的動作
		SLONG	BeatedBy;			//被擊: 誰攻擊我 ?
	};
	union
	{
		SLONG	DestY;				//移動: 目標座標 Y
		SLONG	IdleTicks;			//待機: 待機的時間
		SLONG	MuseTicks;			//冥想: 每隔多長時間進行一次數值計算
		SLONG	BeatedWith;			//被擊: 被甚麼技能攻擊 ?
	};
	union
	{
		SLONG	DestZ;				//移動: 目標座標 Z
		SLONG	PantTicks;			//被擊倒: 擊倒在地上與爬起來之間的喘息時間
		SLONG	DeadTicks;			//死亡: 死亡了多長時間
		SLONG	DeadAlpha;			//死亡: 死亡後屍體消失的ALPHA值
	};
	union
	{
		SLONG	DestID;				//目標ID
		SLONG	ClashSteps;			//衝撞: 衝撞的步數
		SLONG	PatrolTicks;		//巡邏: 巡邏IDLE的當前時間
	};
	union
	{
		SLONG	OrigX;				//起始座標
		SLONG	GadTotalTicks;		//隨機移動: IDLE的總時間
		SLONG	BeatedX;			//被擊,死亡,被擊倒: 攻擊源 x座標
	};
	union
	{
		SLONG	OrigY;				//起始座標
		SLONG	GadTicks;			//隨機移動: IDLE的當前時間
		SLONG	BeatedY;			//被擊,死亡,被擊倒: 攻擊源 y座標
	};
	union
	{
		SLONG	OrigZ;					//起始座標
		SLONG	AttackPantTicks;		//攻擊: 攻擊後喘息時間
	};
	union
	{
		ULONG	OrigID;					//起始ID
		SLONG	PatrolTotalTicks;		//巡邏: 巡邏IDLE的總時間
		SLONG	AttackPantTotalTicks;	//攻擊: 攻擊後喘息總時間
	};
	union
	{
		SLONG	DialogWithCount;		//對話: 被動NPC同時與幾個玩家在交談
		SLONG	DialogDestIndex;		//對話: 玩家與哪個NPC在對話
	};
} TPOS_CHARACTER_POSITION, *LPTPOS_CHARACTER_POSITION;


//角色速度
typedef	struct POS_CHARACTER_SPEED 
{
	SLONG	Mspeed;			//人物移動速度
	SLONG	FSpeedX;		//船X軸速度
	SLONG	FSpeedY;		//船Y軸速度
	UHINT	SailSize;		//船帆吃風的面積
	UHINT	Turn;			//船轉向力
	UHINT	Weight;			//船重量
	SLONG	DegreeDir;		//船的方向
	SLONG	OldDegreeDir;	//船的原來方向
} TPOS_CHARACTER_SPEED, *LPTPOS_CHARACTER_SPEED;


//角色狀態
typedef	struct POS_CHARACTER_STATE 
{
	ULONG	BitState;				//1/0狀態(是否在戰鬥狀態, 包包是否打開, 在海上或陸地, 是否死亡...)

	SHINT	ReliveTicks;			//再生的時間
	SHINT	DeadState;				//死亡的狀態

	SHINT	RMagicState;			//右鍵技能狀態
	SHINT	RMagicTotalTicks;		//右鍵技能總時間
	SHINT	RMagicCurrentTicks;		//右鍵技能當前時間

	SHINT	HeadSleepState;			//頭暈, 睡眠(被動)
	SHINT	HeadSleepTicks;			//頭暈, 睡眠 時間
	SHINT	HeadSleepLevel;			//頭暈, 睡眠 等級

	SHINT	HeadDefenceState;		//防禦加強(被動或主動)
	SHINT	HeadDefenceTicks;		//防禦加強 時間
	SHINT	HeadDefenceLevel;		//防禦加強 等級

	SHINT	HeadMagicState;			//魔法反彈
	SHINT	HeadMagicTimes;			//魔法反彈次數	
	SHINT	HeadMagicLevel;			//魔法反彈等級

	SHINT	HeadBlindState;			//失明(被動)	
	SHINT	HeadBlindTicks;			//失明 時間	
	SHINT	HeadBlindLevel;			//失明 等級	

	SHINT	BodyDodgeState;			//躲閃(主動光環技)

	SHINT	BodyVirusState;			//中毒(被動)	
	SHINT	BodyVirusTicks;			//中毒 時間	
	SHINT	BodyVirusLevel;			//中毒 等級	

	SHINT	BodyHideState;			//被吸血(被動), 隱形1, 隱形2(主動)	
	SHINT	BodyHideTicks;			//被吸血(被動), 隱形1, 隱形2 時間	
	SHINT	BodyHideLevel;			//被吸血(被動), 隱形1, 隱形2 等級

	SHINT	FootSpeedState;			//遲緩1, 遲緩2(被動或者在範圍內)	
	SHINT	FootSpeedTicks;			//遲緩1, 遲緩2 時間	
	SHINT	FootSpeedLevel;			//遲緩1, 遲緩2 等級	

	SHINT	RotateState;			//旋轉(被動)船隻
	SHINT	RotateTicks;			//旋轉 時間	船隻
	SHINT	RotateLevel;			//旋轉 等級	船隻

	SHINT	FireState;				//著火(被動)船隻
	SHINT	FireTicks;				//著火 時間	船隻
	SHINT	FireLevel;				//著火 等級	船隻

	SHINT	ExplodeState;			//爆炸(被動)船隻
	SHINT	ExplodeTicks;			//爆炸 時間	船隻
	SHINT	ExplodeLevel;			//爆炸 等級	船隻

	SHINT	SailHurtState;			//帆損害 (被動)	船隻
	SHINT	RudderHurtState;		//舵損害 (被動)	船隻

	SHINT	PretendState;			//偽裝 (主動)	船隻
	SHINT	PretendOldFileIndex;	//偽裝前的圖像	船隻
	SHINT	PretendToFileIndex;		//偽裝後的圖像	船隻

	SHINT	HalfDownState;			//半沉	船隻

	SHINT	OctopusState;			//章魚 (被動)	船隻
	SHINT	OctopusTicks;			//章魚 時間	船隻
	SHINT	OctopusLevel;			//章魚 等級	船隻

	ULONG	TotalOnlineTicks;		//總在線時間

    // mark by lijun 2003-06-19
	//ULONG	AI;						//人物戰鬥AI
} TPOS_CHARACTER_STATE, *LPTPOS_CHARACTER_STATE;
//角色的AI數據項
typedef	struct POS_CHARACTER_AI
{
    ULONG   AI;                 //人物的行為AI..在腳本中設定
    ULONG   AIBlock;            //人物所處在的AI塊
}TPOS_CHARACTER_AI, *LPTPOS_CHARACTER_AI;


//人物力量
typedef	struct POS_CHARACTER_PROPERTY_STR
{
	UHINT	FinalStr;			//最後力量
	UHINT	InitStr;			//初始化時設定的力量值
	UHINT	LevUpStr;			//累計升級時分配的力量值
	UHINT	PointStr;			//當前自己調配增加的力量
} TPOS_CHARACTER_PROPERTY_STR, *LPTPOS_CHARACTER_PROPERTY_STR;



//人物直覺
typedef	struct POS_CHARACTER_PROPERTY_INS 
{
	UHINT	FinalIns;			//最後直覺
	UHINT	InitIns;			//初始化時設定的直覺值
	UHINT	LevUpIns;			//累計升級時分配的直覺值
	UHINT	PointIns;			//當前自己調配增加的直覺
} TPOS_CHARACTER_PROPERTY_INS, *LPTPOS_CHARACTER_PROPERTY_INS;


//人物智慧
typedef	struct POS_CHARACTER_PROPERTY_WIT
{
	UHINT	FinalWit;			//最後智慧
	UHINT	InitWit;			//初始化時設定的智慧值
	UHINT	LevUpWit;			//累計升級時分配的智慧值
	UHINT	PointWit;			//當前自己調配增加的智慧
} TPOS_CHARACTER_PROPERTY_WIT, *LPTPOS_CHARACTER_PROPERTY_WIT;


//人物運氣
typedef	struct POS_CHARACTER_PROPERTY_LUCKY
{
	UHINT	FinalLucky;			//最後幸運
	UHINT	InitLucky;			//初始化時設定的幸運值
	UHINT	LevUpLucky;			//累計升級時分配的幸運值
	UHINT	PointLucky;			//當前自己調配增加的幸運
} TPOS_CHARACTER_PROPERTY_LUCKY, *LPTPOS_CHARACTER_PROPERTY_LUCKY;


//人物攻擊力
typedef	struct POS_CHARACTER_PROPERTY_ATTACK
{
	UHINT	FinalPhysicAtt;		//人物最終物理攻擊力(與技能運算後)
	UHINT	FinalMagicAtt;		//人物最終法術攻擊力(與技能運算後)
	UHINT	FinalSpecAtt;		//人物最終特殊攻擊力(與技能運算後)
	//
	UHINT	FinalAtt;				//人物最終基本攻擊力 = EquipBaseAtt * AttribAttRatio %
	UHINT	AttribAttRatio;			//基本屬性影響攻擊力的百分比
	//
	UHINT	EquipBaseAtt;			//裝備攻擊力值
	UHINT	EquipAddedMagicAtt;		//裝備附加的法術攻擊力
	UHINT	EquipAddedSpecAtt;		//裝備附加的特殊攻擊力
	//
	UHINT	SkillAttackRatio;		//所有技能附加的對攻擊力的影響百分比總和
	//
	UHINT	AttackRange;		//攻擊範圍
	UHINT	AttackRate;			//命中率
	UHINT	SightRange;			//視野範圍
	//
	UHINT 	FinalExplodeRate;	//膛爆率
	UHINT	EquipExplodeRate;	//裝備的膛爆率
	UHINT	SkillExplodeRate;	//執行技能之附加膛爆率
} TPOS_CHARACTER_PROPERTY_ATTACK, *LPTPOS_CHARACTER_PROPERTY_ATTACK;


//人物防禦力
typedef	struct  POS_CHARACTER_PROPERTY_DEFENCE
{
	UHINT	FinalDefence;		//最終防禦力
	UHINT	BaseDefence;		//基本屬性運算得來的防禦力值
	UHINT	EquipDefence;		//裝備防禦力值
	UHINT	SkillDefence;		//技能防禦力值
	UHINT	SkillDefenceTicks;	//技能防禦力有效時間
	//
	union
	{
		UHINT	EquipResistRatio;	//裝備抵抗百分比
		UHINT	FinalResist;		//最終抵抗力
	};
	//
	UHINT	DodgeRate;			//躲避率
	UHINT	ParryRate;			//格擋率
} TPOS_CHARACTER_PROPERTY_DEFENCE, *LPTPOS_CHARACTER_PROPERTY_DEFENCE;


//角色屬性
typedef	struct POS_CHARACTER_PROPERTY 
{
	UHINT	PropertyPoint;							//屬性增加剩餘點數
	TPOS_CHARACTER_PROPERTY_STR			Str;		//力量
	TPOS_CHARACTER_PROPERTY_INS			Ins;		//直覺
	TPOS_CHARACTER_PROPERTY_WIT			Wit;		//智慧
	TPOS_CHARACTER_PROPERTY_LUCKY		Lucky;		//運氣
	TPOS_CHARACTER_PROPERTY_ATTACK		Attack;		//攻擊
	TPOS_CHARACTER_PROPERTY_DEFENCE		Defence;	//防禦力
} TPOS_CHARACTER_PROPERTY, *LPTPOS_CHARACTER_PROPERTY;


//角色等級經驗
typedef	struct POS_CHARACTER_EXPLEV 
{
	ULONG	Exp;			//經驗值
	ULONG	NextExp;		//下一級經驗值
	UHINT	Level;			//等級
} TPOS_CHARACTER_EXPLEV, *LPTPOS_CHARACTER_EXPLEV;


//角色生命魔法
typedef	struct POS_CHARACTER_HPMP 
{
	UHINT	Hp;				//當前生命力
	UHINT	MaxHp;			//生命力上限
	UHINT	AttribHp;		//基本屬性運算得來的生命力上限
	UHINT	LevelUpHp;		//升級獲得的生命力上限值
	UHINT	EquipHp;		//裝備附加的生命力上限值
	UHINT	SkillHp;		//技能影響的生命力上限值
	UHINT	HpRes;			//生命回復力
	UHINT	Mp;				//當前內力
	UHINT	MaxMp;			//內力上限
	UHINT	AttribMp;		//基本屬性運算得來的內力上限
	UHINT	LevelUpMp;		//升級獲得的內力上限值
	UHINT	EquipMp;		//裝備附加的內力上限值
	UHINT	SkillMp;		//技能影響的內力上限值
	UHINT	MpRes;			//內力回復力
} TPOS_CHARACTER_HPMP, *LPTPOS_CHARACTER_HPMP;


//角色技能
typedef	struct POS_CHARACTER_SKILLEXP
{
	SHINT	Skill[MAX_CHARACTER_SKILLS];	//技能編號
	UHINT	Level[MAX_CHARACTER_SKILLS];	//技能等級
} TPOS_CHARACTER_SKILLEXP, *LPTPOS_CHARACTER_SKILLEXP;


//角色裝備
typedef	struct POS_CHARACTER_EQUIPMENT 
{
	TPOS_ITEM	EquHead;		//頭部
	TPOS_ITEM	EquNeck;		//頸部
	TPOS_ITEM	EquBody;		//身體
	TPOS_ITEM	EquWaist;		//腰部
	TPOS_ITEM	EquGlove;		//手套
	TPOS_ITEM	EquWeapon;		//武器
	TPOS_ITEM	EquWrist;		//手環
	TPOS_ITEM	EquFeet;		//腳部
	TPOS_ITEM	EquOtherA;		//其他A
	TPOS_ITEM	EquOtherB;		//其他B
	TPOS_ITEM	EquOtherC;		//其他C
} TPOS_CHARACTER_EQUIPMENT, *LPCHARACTER_EQUIPMENT;


//角色身上物品金錢
typedef	struct POS_CHARACTER_BODY_IM 
{
	TPOS_ITEM	BagItem[MAX_CHARACTER_BAG_ITEMS];		//背包內物品
	TPOS_ITEM	SashItem[MAX_CHARACTER_SASH_ITEMS];		//腰包內物品
	TPOS_ITEM	TransItem[MAX_CHARACTER_TRANS_ITEMS];	//QQ傳送欄物品
	TPOS_ITEM	OnMouseItem;	//在滑鼠上的物品
	TPOS_ITEM	TreasureItem;	//藏寶圖物品
	ULONG		Money;			//身上的金錢
} TPOS_CHARACTER_BODY_IM, *LPTPOS_CHARACTER_BODY_IM;


//角色銀行物品金錢
typedef	struct POS_CHARACTER_BANK_IM 
{
	TPOS_ITEM	Item[MAX_CHARACTER_BANK_ITEMS];		//銀行的物品
	ULONG		Money;			//銀行的存款
} TPOS_CHARACTER_BANK_IM, *LPTPOS_CHARACTER_BANK_IM;

//角色隊伍成員
typedef	struct POS_CHARACTER_TEAM_MEMBER
{
	ULONG	Flags;			//標記
	CHAR	MainName[32];	//名稱
	UHINT	Hp;				//當前HP
	UHINT	MaxHp;			//當前HP上限
	UHINT	Level;			//當前等級
	CHAR	Eyes;			//眼睛圖像索引
	CHAR	Mouth;			//口圖像索引
	CHAR	Career;			//人物職業
	CHAR	Sex;			//人物性別
	CHAR	ZoneName[32];	//所在區域
} TPOS_CHARACTER_TEAM_MEMBER, *LPTPOS_CHARACTER_TEAM_MEMBER;

//角色組隊
typedef	struct POS_CHARACTER_TEAM 
{
	SLONG	MaxMembers;		//當前隊伍中人員數目
	TPOS_CHARACTER_TEAM_MEMBER	Member[MAX_CHARACTER_TEAM_MEMBERS];		//隊伍成員資料
} TPOS_CHARACTER_TEAM, *LPTPOS_CHARACTER_TEAM;


//角色敵人成員
typedef	struct POS_CHARACTER_ENEMY_MEMBER 
{
	UHINT	HitHp;			//打了多少HP
	ULONG	Flag;			//敵人的標誌, 0 = 單一玩家, 1 = 隊伍
	CHAR	MainName[32];	//敵人的名稱
} TPOS_CHARACTER_ENEMY_MEMBER, *LPTPOS_CHARACTER_ENEMY_MEMBER;

//角色敵人
typedef	struct POS_CHARACTER_ENEMY 
{
	SLONG	MaxMembers;
	TPOS_CHARACTER_ENEMY_MEMBER	Member[MAX_CHARACTER_ENEMY_MEMBERS];
} TPOS_CHARACTER_ENEMY, *LPTPOS_CHARACTER_ENEMY;


//角色社會關係
typedef	struct POS_CHARACTER_SOCIETY 
{
	CHAR	Sex;				//性別
	CHAR	Country;			//國家
	CHAR	Guild[32];			//工會
	CHAR	Spouse[32];			//配偶
	CHAR	Career;				//職業類型
	UCHR	CareerLevel;		//職業等級
	ULONG	Office;				//工會的職位
	CHAR	Nobility[16];		//爵位
	SLONG	GoodEvil;			//善惡值
	SLONG	Prestige;			//聲望
	ULONG	PkCount;			//PK死別人的多少人
	ULONG	PkedCount;			//被人PK死的次數
	UHINT	Kind;				//種類	
} TPOS_CHARACTER_SOCIETY, *LPTPOS_CHARACTER_SOCIETY;


//角色快捷按鍵
typedef	struct POS_CHARACTER_QUICKBUTTON 
{
	SHINT	LandLeftSkill;		//陸地滑鼠左鍵技能
	SHINT	LandRightSkill;		//陸地滑鼠右鍵技能
	SHINT	LandFnSkillNo[MAX_CHARACTER_FN_SKILLS];		//陸地按鍵F1~F8對應技能編號
	CHAR	LandFnSkillHand[MAX_CHARACTER_FN_SKILLS];	//陸地按鍵F1~F8對應技能設置在哪只手
	//
	SHINT	SeaLeftSkill;		//海洋滑鼠左鍵技能
	SHINT	SeaRightSkill;		//海洋滑鼠右鍵技能
	SHINT	SeaFnSkillNo[MAX_CHARACTER_FN_SKILLS];		//海洋按鍵F1~F8對應技能編號
	CHAR	SeaFnSkillHand[MAX_CHARACTER_FN_SKILLS];	//海洋按鍵F1~F8對應技能設置在哪只手
} TPOS_CHARACTER_QUICKBUTTON, *LPTPOS_CHARACTER_QUICKBUTTON;



//角色動作相關
typedef	struct POS_CHARACTER_ACTION 
{
	SLONG	DoingKind;			//事務類型
	SLONG	DoingStep;			//事務進行程度
	//
	SHINT	DoingMagic;			//當前使用的法術技能編號
	SHINT	MagicTimes;			//當前使用的法術技能重複次數
	SHINT	FightTicks;			//戰鬥使用的計時
	UCHAR	ImageAction;		//圖檔動作索引
	ULONG	ImageID;			//圖檔文件標示
} TPOS_CHARACTER_ACTION, *LPTPOS_CHARACTER_ACTION;


// Jack, quest related data [5/8/2003]
typedef	struct POS_QUEST_INFO 
{
	UCHR	QuestType;			//任務類別 (QUEST_TYPE_$$)
	CHAR	PublishZone[32];	//發起地點(區域)
	CHAR	PublishNpc[32];		//發起人
	CHAR	TargetZone[32];		//目標地點(區域)
	CHAR	TargetNpc[32];		//目標人
	ULONG	AcceptTime;			//玩家接受任務的時間
	ULONG	Deadline;			//任務完成的最終期限
	UCHR	PayType;			//完成任務的報酬類別 (QUEST_PAY_$$)
	ULONG	PayData;			//完成任務的報酬數值 (可以是聲望Prestidge, 金錢Money 或者物品ItemBaseID )
	UCHR	PunishType;			//未完成任務的懲罰類別
	ULONG	PunishData;			//未完成任務的懲罰數值
	CHAR	Memo[64];			//任務說明
} TPOS_QUEST_INFO, *LPTPOS_QUEST_INFO;


typedef	struct POS_CHARACTER_QUEST 
{
	TPOS_QUEST_INFO		QuestInfo[MAX_CHARACTER_QUESTS];
} TPOS_CHARACTER_QUEST, *LPTPOS_CHARACTER_QUEST;

//角色資料結構
typedef	struct POS_CHARACTER 
{
	TPOS_CHARACTER_HEADER		Header;			//標頭
	TPOS_CHARACTER_NAME			Name;			//姓名
	TPOS_CHARACTER_STYLE		Style;			//外觀
	TPOS_CHARACTER_POSITION		Position;		//位置
	TPOS_CHARACTER_SPEED		Speed;			//速度
	TPOS_CHARACTER_STATE		State;			//狀態
    TPOS_CHARACTER_AI	        AI;             //AI
	TPOS_CHARACTER_PROPERTY		Property;		//屬性
	TPOS_CHARACTER_EXPLEV		ExpLev;			//等級經驗
	TPOS_CHARACTER_HPMP			HpMp;			//生命魔法
	TPOS_CHARACTER_SKILLEXP		SkillExp;		//技能
	TPOS_CHARACTER_EQUIPMENT	Equipment;		//裝備
	TPOS_CHARACTER_BODY_IM		BodyItemMoney;	//身上物品金錢
	TPOS_CHARACTER_BANK_IM		BankItemMoney;	//銀行物品金錢
	TPOS_CHARACTER_TEAM			Team;			//組隊
	TPOS_CHARACTER_ENEMY		Enemy;			//敵人
	TPOS_CHARACTER_SOCIETY		Society;		//社會關係
	TPOS_CHARACTER_QUICKBUTTON	QuickButton;	//快捷按鍵
	TPOS_CHARACTER_ACTION		Action;			//動作相關
	TPOS_CHARACTER_QUEST		Quest;			//任務相關(Jack, [5/8/2003]) 
} TPOS_CHARACTER, *LPTPOS_CHARACTER;


//
//Level 1 Structures ----------------------
//

#pragma pack(pop)

//
// GLOBALS //////////////////////////////////////////////////////////////////////////////////////////////////
//
extern	TPOS_CHARACTER	ZoneCharacter[MAX_CHARACTER_PER_ZONE];

//
// FUNCTIONS ////////////////////////////////////////////////////////////////////////////////////////////////
//
extern	void	InitAllZoneCharacters(void);
extern	void	ClearOneCharacter(SLONG lIndex);
extern	void	ClearCharacterSkills(SLONG lIndex);
extern	SLONG	IsCharacterAvailable(SLONG lIndex);
//
// Level 0 functions ------------------------------------------------
extern	void	SetCharacterType(SLONG lIndex, UHINT uType);
extern	UHINT	GetCharacterType(SLONG lIndex);
extern	void	SetCharacterAccount(SLONG lIndex, CHAR *szAccout);
extern	CHAR*	GetCharacterAccount(SLONG lIndex);
extern	void	SetCharacterMainName(SLONG lIndex, CHAR *szMainName);
extern	CHAR*	GetCharacterMainName(SLONG lIndex);
extern	void	SetCharacterNickName(SLONG lIndex, CHAR *szNickName);
extern	CHAR*	GetCharacterNickName(SLONG lIndex);
extern	void	SetCharacterQQID(SLONG lIndex, ULONG uID);
extern	ULONG	GetCharacterQQID(SLONG lIndex);
extern	void	SetCharacterIndex(SLONG lCharIndex, SLONG lIndex);
extern	SLONG	GetCharacterIndex(SLONG lCharIndex);
//
extern	void	SetCharacterPicture(SLONG lIndex, SLONG lPicture);
extern	SLONG	GetCharacterPicture(SLONG lIndex);
extern	void	SetCharacterColor(SLONG lIndex, SLONG lColor);
extern	SLONG	GetCharacterColor(SLONG lIndex);
extern	void	SetCharacterEyes(SLONG lIndex, SLONG lEyes);
extern	SLONG	GetCharacterEyes(SLONG lIndex);
extern	void	SetCharacterMouth(SLONG lIndex, SLONG lMouth);
extern	SLONG	GetCharacterMouth(SLONG lIndex);
extern	void	SetCharacterMainNameColor(SLONG lIndex, SLONG lColor);
extern	SLONG	GetCharacterMainNameColor(SLONG lIndex);
extern	void	SetCharacterNickNameColor(SLONG lIndex, SLONG lColor);
extern	SLONG	GetCharacterNickNameColor(SLONG lIndex);
extern	void	SetCharacterMessageColor(SLONG lIndex, SLONG lColor);
extern	SLONG	GetCharacterMessageColor(SLONG lIndex);
extern	void	SetCharacterTalkBackColor(SLONG lIndex, SLONG lColor);
extern	SLONG	GetCharacterTalkBackColor(SLONG lIndex);
extern	void	SetCharacterLogo(SLONG lIndex, ULONG lLogo);
extern	ULONG	GetCharacterLogo(SLONG lIndex);
extern	void	SetCharacterFileIndex(SLONG lIndex, SLONG lFileIndex);
extern	SLONG	GetCharacterFileIndex(SLONG lIndex);
extern	void	SetCharacterLandFileIndex(SLONG lIndex, SLONG lFileIndex);
extern	SLONG	GetCharacterLandFileIndex(SLONG lIndex);
extern	void	SetCharacterSeaFileIndex(SLONG lIndex, SLONG lFileIndex);
extern	SLONG	GetCharacterSeaFileIndex(SLONG lIndex);
extern	void	SetCharacterPartRGB(SLONG lIndex, SLONG lPart, ULONG uRGB);
extern	ULONG	GetCharacterPartRGB(SLONG lIndex, SLONG lPart);
extern	void	SetCharacterNameColorTicks(SLONG lIndex, ULONG uTicks);
extern	ULONG	GetCharacterNameColorTicks(SLONG lIndex);

//
extern	void	SetCharacterZoneName(SLONG lIndex, CHAR *szName);
extern	CHAR *	GetCharacterZoneName(SLONG lIndex);
extern	void	SetCharacterPosition(SLONG lIndex, SLONG lX, SLONG lY, SLONG lZ);
extern	void	GetCharacterPosition(SLONG lIndex, SLONG *lX, SLONG *lY, SLONG *lZ);
extern	void	SetCharacterDir(SLONG lIndex, SLONG lDir);
extern	SLONG	GetCharacterDir(SLONG lIndex);
extern	void	SetCharacterDirFrame(SLONG lIndex, SLONG lFrame);
extern	SLONG	GetCharacterDirFrame(SLONG lIndex);
extern	void	SetCharacterFrame(SLONG lIndex, SLONG lFrame);
extern	SLONG	GetCharacterFrame(SLONG lIndex);
extern	void	SetCharacterDestPosition(SLONG lIndex, SLONG lX, SLONG lY, SLONG lZ);
extern	void	GetCharacterDestPosition(SLONG lIndex, SLONG *lX, SLONG *lY, SLONG *lZ);
extern	void	SetCharacterDestID(SLONG lIndex, SLONG uID);
extern	SLONG	GetCharacterDestID(SLONG lIndex);
extern	void	SetCharacterOrigPosition(SLONG lIndex, SLONG lX, SLONG lY, SLONG lZ);
extern	void	GetCharacterOrigPosition(SLONG lIndex, SLONG *lX, SLONG *lY, SLONG *lZ);
extern	void	SetCharacterOrigID(SLONG lIndex, ULONG uID);
extern	ULONG	GetCharacterOrigID(SLONG lIndex);
extern	void	SetCharacterStopRadius(SLONG lIndex, SLONG lRadius);
extern	SLONG	GetCharacterStopRadius(SLONG lIndex);
extern	void	SetCharacterDialogWithCount(SLONG lIndex, SLONG lCount);
extern	SLONG	GetCharacterDialogWithCount(SLONG lIndex);
extern	void	SetCharacterDialogDestIndex(SLONG lIndex, SLONG lDestIndex);
extern	SLONG	GetCharacterDialogDestIndex(SLONG lIndex);

extern	void	SetCharacterMoveSpeed(SLONG lIndex, SLONG lSpeed);
extern	SLONG	GetCharacterMoveSpeed(SLONG lIndex);
extern	void	SetCharacterShipSpeedX(SLONG lIndex, SLONG lSpeedX);
extern	SLONG	GetCharacterShipSpeedX(SLONG lIndex);
extern	void	SetCharacterShipSpeedY(SLONG lIndex, SLONG lSpeedY);
extern	SLONG	GetCharacterShipSpeedY(SLONG lIndex);
extern	void	SetCharacterShipSailSize(SLONG lIndex, SLONG lSize);
extern	SLONG	GetCharacterShipSailSize(SLONG lIndex);
extern	void	SetCharacterShipTurn(SLONG lIndex, SLONG lTurn);
extern	SLONG	GetCharacterShipTurn(SLONG lIndex);
extern	void	SetCharacterShipWeight(SLONG lIndex, SLONG lWeight);
extern	SLONG	GetCharacterShipWeight(SLONG lIndex);
extern	void	SetCharacterShipDegreeDir(SLONG lIndex, SLONG lDegreeDir);
extern	SLONG	GetCharacterShipDegreeDir(SLONG lIndex);
extern	void	SetCharacterShipOldDegreeDir(SLONG lIndex, SLONG lDegreeDir);
extern	SLONG	GetCharacterShipOldDegreeDir(SLONG lIndex);
//
extern	SLONG	IsCharacterOnFightState(SLONG lIndex);
extern	void	SetCharacterOnFightState(SLONG lIndex, SLONG lFlag);
extern  SLONG	IsCharacterOnBlockState(SLONG lIndex);
extern  void	SetCharacterOnBlockState(SLONG lIndex, SLONG lFlag);
extern	SLONG	IsCharacterBagOpened(SLONG lIndex);
extern	void	SetCharacterBagOpened(SLONG lIndex, SLONG lFlag);
extern	SLONG	IsCharacterOnTheSea(SLONG lIndex);
extern	void	SetCharacterOnTheSea(SLONG lIndex, SLONG lFlag);
extern	SLONG	IsCharacterOnDeadState(SLONG lIndex);
extern	void	SetCharacterOnDeadState(SLONG lIndex, SLONG lFlag);
extern	SLONG	IsCharacterOnDefenceState(SLONG lIndex);
extern	void	SetCharacterOnDefenceState(SLONG lIndex, SLONG lFlag);
extern	SLONG	IsCharacterDodge(SLONG lIndex);
extern	void	SetCharacterDodge(SLONG lIndex, SLONG lFlag);
extern	SLONG   IsCharacterOnBlock(SLONG lIndex);
extern	void    SetCharacterOnBlock(SLONG lIndex,SLONG lFlag);
extern	SLONG   IsCharacterMagicRebound(SLONG lIndex);
extern	void    SetCharacterMagicRebound(SLONG lIndex,SLONG lFlag);
extern	SLONG   IsCharacterShowSubtil(SLONG lIndex);
extern	void    SetCharacterShowSubtil(SLONG lIndex,SLONG lFlag);
extern	SLONG   IsCharacterSpeedDelay1(SLONG lIndex);
extern	void    SetCharacterSpeedDelay1(SLONG lIndex,SLONG lFlag);
extern	SLONG   IsCharacterSpeedDelay2(SLONG lIndex);
extern	void    SetCharacterSpeedDelay2(SLONG lIndex,SLONG lFlag);
extern	SLONG   IsCharacterWithoutEqual(SLONG lIndex);
extern	void    SetCharacterWithoutEqual(SLONG lIndex,SLONG lFlag);
extern	SLONG   IsCharacterBlackNpc(SLONG lIndex);
extern	void    SetCharacterBlackNpc(SLONG lIndex,SLONG lFlag);
extern	SLONG   IsCharacterNpcFaint(SLONG lIndex);
extern	void    SetCharacterNpcFaint(SLONG lIndex,SLONG lFlag);
extern	SLONG   IsCharacterNpcStandUp(SLONG lIndex);
extern	void    SetCharacterNpcStandUp(SLONG lIndex,SLONG lFlag);
extern	SLONG   IsCharacterHeadSleep(SLONG lIndex);
extern	void    SetCharacterHeadSleep(SLONG lIndex,SLONG lFlag);
extern	SLONG   IsCharacterOnSleep(SLONG lIndex);
extern	void    SetCharacterOnSleep(SLONG lIndex,SLONG lFlag);
extern	SLONG	IsCharacterOnPauseState(SLONG lIndex);
extern	void	SetCharacterOnPauseState(SLONG lIndex, SLONG lFlag);
extern	SLONG	IsCharacterOnSpecialItem(SLONG lIndex);
extern	void	SetCharacterOnSpecialItem(SLONG lIndex, SLONG lFlag);
//
extern	void	SetCharacterBitState(SLONG lIndex, ULONG uState);
extern	ULONG	GetCharacterBitState(SLONG lIndex);
extern	void	SetCharacterReliveTicks(SLONG lIndex, SHINT lTicks);
extern	SHINT	GetCharacterReliveTicks(SLONG lIndex);
extern	void	SetCharacterDeadState(SLONG lIndex, SHINT lState);
extern	SHINT	GetCharacterDeadState(SLONG lIndex);
extern	void	SetCharacterRightHandMagicState(SLONG lIndex, SHINT lState);
extern	SHINT	GetCharacterRightHandMagicState(SLONG lIndex);
extern	void	SetCharacterRightHandMagicTotalTicks(SLONG lIndex, SHINT lTicks);
extern	SHINT	GetCharacterRightHandMagicTotalTicks(SLONG lIndex);
extern	void	SetCharacterRightHandMagicCurrentTicks(SLONG lIndex, SHINT lTicks);
extern	SHINT	GetCharacterRightHandMagicCurrentTicks(SLONG lIndex);
extern	void	SetCharacterHeadSleepState(SLONG lIndex, SHINT lState);
extern	SHINT	GetCharacterHeadSleepState(SLONG lIndex);
extern	void	SetCharacterHeadSleepTicks(SLONG lIndex, SHINT lTicks);
extern	SHINT	GetCharacterHeadSleepTicks(SLONG lIndex);
extern	void	SetCharacterHeadSleepLevel(SLONG lIndex, SHINT lLevel);
extern	SHINT	GetCharacterHeadSleepLevel(SLONG lIndex);
extern	void	SetCharacterHeadPredictState(SLONG lIndex, SHINT lState);
extern	SHINT	GetCharacterHeadPredictState(SLONG lIndex);
extern	void	SetCharacterHeadPredictLevel(SLONG lIndex, SHINT lLevel);
extern	SHINT	GetCharacterHeadPredictLevel(SLONG lIndex);
extern	void	SetCharacterHeadDefenceState(SLONG lIndex, SHINT lState);
extern	SHINT	GetCharacterHeadDefenceState(SLONG lIndex);
extern	void	SetCharacterHeadDefenceTicks(SLONG lIndex, SHINT lTicks);
extern	SHINT	GetCharacterHeadDefenceTicks(SLONG lIndex);
extern	void	SetCharacterHeadDefenceLevel(SLONG lIndex, SHINT lLevel);
extern	SHINT	GetCharacterHeadDefenceLevel(SLONG lIndex);
extern	void	SetCharacterHeadMagicState(SLONG lIndex, SHINT lState);
extern	SHINT	GetCharacterHeadMagicState(SLONG lIndex);
extern	void	SetCharacterHeadMagicTimes(SLONG lIndex, SHINT lTimes);
extern	SHINT	GetCharacterHeadMagicTimes(SLONG lIndex);
extern	void	SetCharacterHeadMagicLevel(SLONG lIndex, SHINT lLevel);
extern	SHINT	GetCharacterHeadMagicLevel(SLONG lIndex);
extern	void	SetCharacterHeadBlindState(SLONG lIndex, SHINT lState);
extern	SHINT	GetCharacterHeadBlindState(SLONG lIndex);
extern	void	SetCharacterHeadBlindTicks(SLONG lIndex, SHINT lTicks);
extern	SHINT	GetCharacterHeadBlindTicks(SLONG lIndex);
extern	void	SetCharacterHeadBlindLevel(SLONG lIndex, SHINT lLevel);
extern	SHINT	GetCharacterHeadBlindLevel(SLONG lIndex);
extern	void	SetCharacterBodyDodgeState(SLONG lIndex, SHINT lState);
extern	SHINT	GetCharacterBodyDodgeState(SLONG lIndex);
extern	void	SetCharacterBodyVirusState(SLONG lIndex, SHINT lState);
extern	SHINT	GetCharacterBodyVirusState(SLONG lIndex);
extern	void	SetCharacterBodyVirusTicks(SLONG lIndex, SHINT lTicks);
extern	SHINT	GetCharacterBodyVirusTicks(SLONG lIndex);
extern	void	SetCharacterBodyVirusLevel(SLONG lIndex, SHINT lLevel);
extern	SHINT	GetCharacterBodyVirusLevel(SLONG lIndex);
extern	void	SetCharacterBodyHideState(SLONG lIndex, SHINT lState);
extern	SHINT	GetCharacterBodyHideState(SLONG lIndex);
extern	void	SetCharacterBodyHideTicks(SLONG lIndex, SHINT lTicks);
extern	SHINT	GetCharacterBodyHideTicks(SLONG lIndex);
extern	void	SetCharacterBodyHideLevel(SLONG lIndex, SHINT lLevel);
extern	SHINT	GetCharacterBodyHideLevel(SLONG lIndex);
extern	void	SetCharacterFootSpeedState(SLONG lIndex, SHINT lState);
extern	SHINT	GetCharacterFootSpeedState(SLONG lIndex);
extern	void	SetCharacterFootSpeedTicks(SLONG lIndex, SHINT lTicks);
extern	SHINT	GetCharacterFootSpeedTicks(SLONG lIndex);
extern	void	SetCharacterFootSpeedLevel(SLONG lIndex, SHINT lLevel);
extern	SHINT	GetCharacterFootSpeedLevel(SLONG lIndex);
//
extern	void	SetCharacterShipRotateState(SLONG lIndex, SHINT lState);
extern	SHINT	GetCharacterShipRotateState(SLONG lIndex);
extern	void	SetCharacterShipRotateTicks(SLONG lIndex, SHINT lTicks);
extern	SHINT	GetCharacterShipRotateTicks(SLONG lIndex);
extern	void	SetCharacterShipRotateLevel(SLONG lIndex, SHINT lLevel);
extern	SHINT	GetCharacterShipRotateLevel(SLONG lIndex);
extern	void	SetCharacterShipFireState(SLONG lIndex, SHINT lState);
extern	SHINT	GetCharacterShipFireState(SLONG lIndex);
extern	void	SetCharacterShipFireTicks(SLONG lIndex, SHINT lTicks);
extern	SHINT	GetCharacterShipFireTicks(SLONG lIndex);
extern	void	SetCharacterShipFireLevel(SLONG lIndex, SHINT lLevel);
extern	SHINT	GetCharacterShipFireLevel(SLONG lIndex);
extern	void	SetCharacterShipExplodeState(SLONG lIndex, SHINT lState);
extern	SHINT	GetCharacterShipExplodeState(SLONG lIndex);
extern	void	SetCharacterShipExplodeTicks(SLONG lIndex, SHINT lTicks);
extern	SHINT	GetCharacterShipExplodeTicks(SLONG lIndex);
extern	void	SetCharacterShipExplodeLevel(SLONG lIndex, SHINT lLevel);
extern	SHINT	GetCharacterShipExplodeLevel(SLONG lIndex);
extern	void	SetCharacterShipSailHurtState(SLONG lIndex, SHINT lState);
extern	SHINT	GetCharacterShipSailHurtState(SLONG lIndex);
extern	void	SetCharacterShipRudderHurtState(SLONG lIndex, SHINT lState);
extern	SHINT	GetCharacterShipRudderHurtState(SLONG lIndex);
// 
extern	void	SetCharacterShipPretendState(SLONG lIndex, SHINT lState);
extern	SHINT	GetCharacterShipPretendState(SLONG lIndex);
extern	void	SetCharacterShipPretendOldFileIndex(SLONG lIndex, SHINT lFileIndex);
extern	SHINT	GetCharacterShipPretendOldFileIndex(SLONG lIndex);
extern	void	SetCharacterShipPretendToFileIndex(SLONG lIndex, SHINT lFileIndex);
extern	SHINT	GetCharacterShipPretendToFileIndex(SLONG lIndex);
extern	void	SetCharacterShipHalfDownState(SLONG lIndex, SHINT lState);
extern	SHINT	GetCharacterShipHalfDownState(SLONG lIndex);
extern	void	SetCharacterShipOctopusState(SLONG lIndex, SHINT lState);
extern	SHINT	GetCharacterShipOctopusState(SLONG lIndex);
extern	void	SetCharacterShipOctopusTicks(SLONG lIndex, SHINT lTicks);
extern	SHINT	GetCharacterShipOctopusTicks(SLONG lIndex);
extern	void	SetCharacterShipOctopusLevel(SLONG lIndex, SHINT lLevel);
extern	SHINT	GetCharacterShipOctopusLevel(SLONG lIndex);
extern	void	SetCharacterAI(SLONG lIndex, ULONG uAI);
extern	ULONG	GetCharacterAI(SLONG lIndex);
extern  void	SetCharacterAIBlock(SLONG lIndex, ULONG uAIBlock);
extern  ULONG	GetCharacterAIBlock(SLONG lIndex);
extern	void	SetCharacterTotalOnlineTicks(SLONG lIndex, ULONG uTicks);
extern	ULONG	GetCharacterTotalOnlineTicks(SLONG lIndex);
//
extern	void	SetCharacterFinalStr(SLONG lIndex, UHINT uStr);
extern	UHINT	GetCharacterFinalStr(SLONG lIndex);
extern	void	SetCharacterInitStr(SLONG lIndex, UHINT uStr);
extern	UHINT	GetCharacterInitStr(SLONG lIndex);
extern	void	SetCharacterLevelUpStr(SLONG lIndex, UHINT uStr);
extern	UHINT	GetCharacterLevelUpStr(SLONG lIndex);
extern	void	SetCharacterPointStr(SLONG lIndex, UHINT uStr);
extern	UHINT	GetCharacterPointStr(SLONG lIndex);
//
extern	void	SetCharacterFinalIns(SLONG lIndex, UHINT uIns);
extern	UHINT	GetCharacterFinalIns(SLONG lIndex);
extern	void	SetCharacterInitIns(SLONG lIndex, UHINT uIns);
extern	UHINT	GetCharacterInitIns(SLONG lIndex);
extern	void	SetCharacterLevelUpIns(SLONG lIndex, UHINT uIns);
extern	UHINT	GetCharacterLevelUpIns(SLONG lIndex);
extern	void	SetCharacterPointIns(SLONG lIndex, UHINT uIns);
extern	UHINT	GetCharacterPointIns(SLONG lIndex);
//
extern	void	SetCharacterFinalWit(SLONG lIndex, UHINT uWit);
extern	UHINT	GetCharacterFinalWit(SLONG lIndex);
extern	void	SetCharacterInitWit(SLONG lIndex, UHINT uWit);
extern	UHINT	GetCharacterInitWit(SLONG lIndex);
extern	void	SetCharacterLevelUpWit(SLONG lIndex, UHINT uWit);
extern	UHINT	GetCharacterLevelUpWit(SLONG lIndex);
extern	void	SetCharacterPointWit(SLONG lIndex, UHINT uWit);
extern	UHINT	GetCharacterPointWit(SLONG lIndex);
//
extern	void	SetCharacterFinalLucky(SLONG lIndex, UHINT uLucky);
extern	UHINT	GetCharacterFinalLucky(SLONG lIndex);
extern	void	SetCharacterInitLucky(SLONG lIndex, UHINT uLucky);
extern	UHINT	GetCharacterInitLucky(SLONG lIndex);
extern	void	SetCharacterLevelUpLucky(SLONG lIndex, UHINT uLucky);
extern	UHINT	GetCharacterLevelUpLucky(SLONG lIndex);
extern	void	SetCharacterPointLucky(SLONG lIndex, UHINT uLucky);
extern	UHINT	GetCharacterPointLucky(SLONG lIndex);
//
extern	void	SetCharacterFinalAtt(SLONG lIndex, UHINT uAtt);
extern	UHINT	GetCharacterFinalAtt(SLONG lIndex);
extern	void	SetCharacterFinalPhysicAtt(SLONG lIndex, UHINT uAtt);
extern	UHINT	GetCharacterFinalPhysicAtt(SLONG lIndex);
extern	void	SetCharacterFinalMagicAtt(SLONG lIndex, UHINT uAtt);
extern	UHINT	GetCharacterFinalMagicAtt(SLONG lIndex);
extern	void	SetCharacterFinalSpecAtt(SLONG lIndex, UHINT uAtt);
extern	UHINT	GetCharacterFinalSpecAtt(SLONG lIndex);
extern	void	SetCharacterEquipBaseAtt(SLONG lIndex, UHINT uAtt);
extern	UHINT	GetCharacterEquipBaseAtt(SLONG lIndex);
extern	void	SetCharacterEquipAddedMagicAtt(SLONG lIndex, UHINT uAtt);
extern	UHINT	GetCharacterEquipAddedMagicAtt(SLONG lIndex);
extern	void	SetCharacterEquipAddedSpecAtt(SLONG lIndex, UHINT uAtt);
extern	SLONG	GetCharacterEquipAddedSpecAtt(SLONG lIndex);
extern	void	SetCharacterAttribAttRatio(SLONG lIndex, UHINT uRatio);
extern	UHINT	GetCharacterAttribAttRatio(SLONG lIndex);
extern	void	SetCharacterSkillAttackRatio(SLONG lIndex, UHINT uRatio);
extern	UHINT	GetCharacterSkillAttackRatio(SLONG lIndex);
extern	void	SetCharacterAttackRange(SLONG lIndex, UHINT uRange);
extern	UHINT	GetCharacterAttackRange(SLONG lIndex);
extern	void	SetCharacterAttackRate(SLONG lIndex, UHINT uRate);
extern	UHINT	GetCharacterAttackRate(SLONG lIndex);
extern	void	SetCharacterSightRange(SLONG lIndex, UHINT uRange);
extern	UHINT	GetCharacterSightRange(SLONG lIndex);
extern	void	SetCharacterFinalExplodeRate(SLONG lIndex, UHINT uRate);
extern	UHINT	GetCharacterFinalExplodeRate(SLONG lIndex);
extern	void	SetCharacterEquipExplodeRate(SLONG lIndex, UHINT uRate);
extern	UHINT	GetCharacterEquipExplodeRate(SLONG lIndex);
extern	void	SetCharacterSkillExplodeRate(SLONG lIndex, UHINT uRate);
extern	UHINT	GetCharacterSkillExplodeRate(SLONG lIndex);
//
extern	void	SetCharacterFinalDefence(SLONG lIndex, UHINT uDefence);
extern	UHINT	GetCharacterFinalDefence(SLONG lIndex);
extern	void	SetCharacterBaseDefence(SLONG lIndex, UHINT uDefence);
extern	UHINT	GetCharacterBaseDefence(SLONG lIndex);
extern	void	SetCharacterEquipDefence(SLONG lIndex, UHINT uDefence);
extern	UHINT	GetCharacterEquipDefence(SLONG lIndex);
extern	void	SetCharacterSkillDefence(SLONG lIndex, UHINT uDefence);
extern	UHINT	GetCharacterSkillDefence(SLONG lIndex);
extern	void	SetCharacterSkillDefenceTicks(SLONG lIndex, UHINT uTicks);
extern	UHINT	GetCharacterSkillDefenceTicks(SLONG lIndex);
extern	void	SetCharacterEquipResistRatio(SLONG lIndex, UHINT uRatio);
extern	UHINT	GetCharacterEquipResistRatio(SLONG lIndex);
extern	void	SetCharacterFinalResist(SLONG lIndex, UHINT uResist);
extern	UHINT	GetCharacterFinalResist(SLONG lIndex);
extern	void	SetCharacterDodgeRate(SLONG lIndex, UHINT uRate);
extern	UHINT	GetCharacterDodgeRate(SLONG lIndex);
extern	void	SetCharacterParryRate(SLONG lIndex, UHINT uRate);
extern	UHINT	GetCharacterParryRate(SLONG lIndex);
//
extern	void	SetCharacterPropertyPoint(SLONG lIndex, UHINT uPoint);
extern	UHINT	GetCharacterPropertyPoint(SLONG lIndex);
extern	void	AffectCharacterPropertyPoint(SLONG lIndex);
//
extern	void	SetCharacterExp(SLONG lIndex, ULONG uExp);
extern	ULONG	GetCharacterExp(SLONG lIndex);
extern	void	SetCharacterNextExp(SLONG lIndex, ULONG uExp);
extern	ULONG	GetCharacterNextExp(SLONG lIndex);
extern	void	SetCharacterLevel(SLONG lIndex, UHINT uLevel);
extern	UHINT	GetCharacterLevel(SLONG lIndex);
//
extern	void	SetCharacterHp(SLONG lIndex, UHINT uHp);
extern	UHINT	GetCharacterHp(SLONG lIndex);
extern	void	SetCharacterMaxHp(SLONG lIndex, UHINT uMaxHp);
extern	UHINT	GetCharacterMaxHp(SLONG lIndex);
extern	void	SetCharacterAttribHp(SLONG lIndex, UHINT uHp);
extern	UHINT	GetCharacterAttribHp(SLONG lIndex);
extern	void	SetCharacterLevelUpHp(SLONG lIndex, UHINT uHp);
extern	UHINT	GetCharacterLevelUpHp(SLONG lIndex);
extern	void	SetCharacterEquipHp(SLONG lIndex, UHINT uHp);
extern	UHINT	GetCharacterEquipHp(SLONG lIndex);
extern	void	SetCharacterSkillHp(SLONG lIndex, UHINT uHp);
extern	UHINT	GetCharacterSkillHp(SLONG lIndex);
extern	void	SetCharacterHpRes(SLONG lIndex, UHINT uRes);
extern	UHINT	GetCharacterHpRes(SLONG lIndex);
extern	void	SetCharacterMp(SLONG lIndex, UHINT uMp);
extern	UHINT	GetCharacterMp(SLONG lIndex);
extern	void	SetCharacterMaxMp(SLONG lIndex, UHINT uMaxMp);
extern	UHINT	GetCharacterMaxMp(SLONG lIndex);
extern	void	SetCharacterAttribMp(SLONG lIndex, UHINT uMp);
extern	UHINT	GetCharacterAttribMp(SLONG lIndex);
extern	void	SetCharacterLevelUpMp(SLONG lIndex, UHINT uMp);
extern	UHINT	GetCharacterLevelUpMp(SLONG lIndex);
extern	void	SetCharacterEquipMp(SLONG lIndex, UHINT uMp);
extern	UHINT	GetCharacterEquipMp(SLONG lIndex);
extern	void	SetCharacterSkillMp(SLONG lIndex, UHINT uMp);
extern	UHINT	GetCharacterSkillMp(SLONG lIndex);
extern	void	SetCharacterMpRes(SLONG lIndex, UHINT uRes);
extern	UHINT	GetCharacterMpRes(SLONG lIndex);
//
extern	void	SetCharacterSkillNo(SLONG lCharIndex, SLONG lSkillIndex, SLONG lSkillNo);
extern	SLONG	GetCharacterSkillNo(SLONG lCharIndex, SLONG lSkillIndex);
extern	void	SetCharacterSkillLevel(SLONG lCharIndex, SLONG lSkillIndex, UHINT uLevel);
extern	UHINT	GetCharacterSkillLevel(SLONG lCharIndex, SLONG lSkillIndex);
//  npc 根據skill_no 和 npc_no  取得對應的skill 的等級..如果..不會..返回 0等級
extern  SLONG   GetCharacterSpecialSkillLevel(SLONG lCharIndex, SLONG lSkillNo);
//
extern	void	SetCharacterEquipHead(SLONG lIndex, TPOS_ITEM *lpItem);
extern	void	GetCharacterEquipHead(SLONG lIndex, TPOS_ITEM *lpItem);
extern	void	SetCharacterEquipNeck(SLONG lIndex, TPOS_ITEM *lpItem);
extern	void	GetCharacterEquipNeck(SLONG lIndex, TPOS_ITEM *lpItem);
extern	void	SetCharacterEquipBody(SLONG lIndex, TPOS_ITEM *lpItem);
extern	void	GetCharacterEquipBody(SLONG lIndex, TPOS_ITEM *lpItem);
extern	void	SetCharacterEquipWaist(SLONG lIndex, TPOS_ITEM *lpItem);
extern	void	GetCharacterEquipWaist(SLONG lIndex, TPOS_ITEM *lpItem);
extern	void	SetCharacterEquipGlove(SLONG lIndex, TPOS_ITEM *lpItem);
extern	void	GetCharacterEquipGlove(SLONG lIndex, TPOS_ITEM *lpItem);
extern	void	SetCharacterEquipWeapon(SLONG lIndex, TPOS_ITEM *lpItem);
extern	void	GetCharacterEquipWeapon(SLONG lIndex, TPOS_ITEM *lpItem);
extern	void	SetCharacterEquipWrist(SLONG lIndex, TPOS_ITEM *lpItem);
extern	void	GetCharacterEquipWrist(SLONG lIndex, TPOS_ITEM *lpItem);
extern	void	SetCharacterEquipFeet(SLONG lIndex, TPOS_ITEM *lpItem);
extern	void	GetCharacterEquipFeet(SLONG lIndex, TPOS_ITEM *lpItem);
extern	void	SetCharacterEquipOtherA(SLONG lIndex, TPOS_ITEM *lpItem);
extern	void	GetCharacterEquipOtherA(SLONG lIndex, TPOS_ITEM *lpItem);
extern	void	SetCharacterEquipOtherB(SLONG lIndex, TPOS_ITEM *lpItem);
extern	void	GetCharacterEquipOtherB(SLONG lIndex, TPOS_ITEM *lpItem);
extern	void	SetCharacterEquipOtherC(SLONG lIndex, TPOS_ITEM *lpItem);
extern	void	GetCharacterEquipOtherC(SLONG lIndex, TPOS_ITEM *lpItem);
//
extern	void	SetCharacterBagItem(SLONG lCharIndex, SLONG lBagIndex, TPOS_ITEM *lpItem);
extern	void	GetCharacterBagItem(SLONG lCharIndex, SLONG lBagIndex, TPOS_ITEM *lpItem);
extern	void	SetCharacterSashItem(SLONG lCharIndex, SLONG lSashIndex, TPOS_ITEM *lpItem);
extern	void	GetCharacterSashItem(SLONG lCharIndex, SLONG lSashIndex, TPOS_ITEM *lpItem);
extern	void	SetCharacterTransItem(SLONG lCharIndex, SLONG lTransIndex, TPOS_ITEM *lpItem);
extern	void	GetCharacterTransItem(SLONG lCharIndex, SLONG lTransIndex, TPOS_ITEM *lpItem);
extern	void	SetCharacterOnMouseItem(SLONG lCharIndex, TPOS_ITEM *lpItem);
extern	void	GetCharacterOnMouseItem(SLONG lCharIndex, TPOS_ITEM *lpItem);
extern	void	SetCharacterTreasureItem(SLONG lCharIndex, TPOS_ITEM *lpItem);
extern	void	GetCharacterTreasureItem(SLONG lCharIndex, TPOS_ITEM *lpItem);
extern	void	SetCharacterBodyMoney(SLONG lIndex, ULONG uMoney);
extern	ULONG	GetCharacterBodyMoney(SLONG lIndex);
//
extern	void	SetCharacterBankItem(SLONG lCharIndex, SLONG lItemIndex, TPOS_ITEM *lpItem);
extern	void	GetCharacterBankItem(SLONG lCharIndex, SLONG lItemIndex, TPOS_ITEM *lpItem);
extern	void	SetCharacterBankMoney(SLONG lIndex, ULONG uMoney);
extern	ULONG	GetCharacterBankMoney(SLONG lIndex);
//
extern	void	SetCharacterTeamMaxMembers(SLONG lCharIndex, SLONG lMaxMembers);
extern	SLONG	GetCharacterTeamMaxMembers(SLONG lCharIndex);
extern	void	SetCharacterTeamMemberFlag(SLONG lCharIndex, SLONG lMemberIndex, ULONG uFlag);
extern	ULONG	GetCharacterTeamMemberFlag(SLONG lCharIndex, SLONG lMemberIndex);
extern	void	SetCharacterTeamMemberMainName(SLONG lCharIndex, SLONG lMemberIndex, CHAR *szMainName);
extern	CHAR*	GetCharacterTeamMemberMainName(SLONG lCharIndex, SLONG lMemberIndex);
extern	void	SetCharacterTeamMemberHp(SLONG lCharIndex, SLONG lMemberIndex, UHINT uHp);
extern	UHINT	GetCharacterTeamMemberHp(SLONG lCharIndex, SLONG lMemberIndex);
extern	void	SetCharacterTeamMemberMaxHp(SLONG lCharIndex, SLONG lMemberIndex, UHINT uMaxHp);
extern	UHINT	GetCharacterTeamMemberMaxHp(SLONG lCharIndex, SLONG lMemberIndex);
extern	void	SetCharacterTeamMemberLevel(SLONG lCharIndex, SLONG lMemberIndex, UHINT uLevel);
extern	UHINT	GetCharacterTeamMemberLevel(SLONG lCharIndex, SLONG lMemberIndex);
extern	void	SetCharacterTeamMemberEyes(SLONG lCharIndex, SLONG lMemberIndex, SLONG lEyes);
extern	SLONG	GetCharacterTeamMemberEyes(SLONG lCharIndex, SLONG lMemberIndex);
extern	void	SetCharacterTeamMemberMouth(SLONG lCharIndex, SLONG lMemberIndex, SLONG lMouth);
extern	SLONG	GetCharacterTeamMemberMouth(SLONG lCharIndex, SLONG lMemberIndex);
extern	void	SetCharacterTeamMemberCareer(SLONG lCharIndex, SLONG lMemberIndex, SLONG lCareer);
extern	SLONG	GetCharacterTeamMemberCareer(SLONG lCharIndex, SLONG lMemberIndex);
extern	void	SetCharacterTeamMemberSex(SLONG lCharIndex, SLONG lMemberIndex, SLONG lSex);
extern	SLONG	GetCharacterTeamMemberSex(SLONG lCharIndex, SLONG lMemberIndex);
extern	void	SetCharacterTeamMemberZoneName(SLONG lCharIndex, SLONG lMemberIndex, CHAR *szZoneName);
extern	CHAR*	GetCharacterTeamMemberZoneName(SLONG lCharIndex, SLONG lMemberIndex);
//
extern	void	SetCharacterEnemyMaxMembers(SLONG lCharIndex, SLONG lMaxMembers);
extern	SLONG	GetCharacterEnemyMaxMembers(SLONG lCharIndex);
extern	void	SetCharacterEnemyMemberHitHp(SLONG lCharIndex, SLONG lMemberIndex, UHINT lHp);
extern	UHINT	GetCharacterEnemyMemberHitHp(SLONG lCharIndex, SLONG lMemberIndex);
extern	void	SetCharacterEnemyMemberMainName(SLONG lCharIndex, SLONG lMemberIndex, CHAR *szMainName);
extern	CHAR*	GetCharacterEnemyMemberMainName(SLONG lCharIndex, SLONG lMemberIndex);
//
extern	void	SetCharacterSex(SLONG lIndex, SLONG lSex);
extern	SLONG	GetCharacterSex(SLONG lIndex);
extern	void	SetCharacterCountry(SLONG lIndex, SLONG lCountry);
extern	SLONG	GetCharacterCountry(SLONG lIndex);
extern	void	SetCharacterGuildName(SLONG lIndex, CHAR *szName);
extern	CHAR*	GetCharacterGuildName(SLONG lIndex);
extern	void	SetCharacterSpouseName(SLONG lIndex, CHAR *szName);
extern	CHAR*	GetCharacterSpouseName(SLONG lIndex);
extern	void	SetCharacterCareer(SLONG lIndex, SLONG lCareer);
extern	SLONG	GetCharacterCareer(SLONG lIndex);
extern	void	SetCharacterCareerLevel(SLONG lIndex, SLONG lLevel);
extern	SLONG	GetCharacterCareerLevel(SLONG lIndex);
extern	void	SetCharacterOffice(SLONG lIndex, ULONG uOffice);
extern	ULONG	GetCharacterOffice(SLONG lIndex);
extern	void	SetCharacterNobilityName(SLONG lIndex, CHAR *szName);
extern	CHAR*	GetCharacterNobilityName(SLONG lIndex);
extern	void	SetCharacterGoodEvil(SLONG lIndex, SLONG lData);
extern	SLONG	GetCharacterGoodEvil(SLONG lIndex);
extern	void	SetCharacterPrestige(SLONG lIndex, SLONG lPres);
extern	SLONG	GetCharacterPrestige(SLONG lIndex);
extern	void	SetCharacterPkCount(SLONG lIndex, ULONG uCount);
extern	ULONG	GetCharacterPkCount(SLONG lIndex);
extern	void	SetCharacterPkedCount(SLONG lIndex, ULONG uCount);
extern	ULONG	GetCharacterPkedCount(SLONG lIndex);
extern	void	SetCharacterKind(SLONG lIndex, SLONG lKind);
extern	SLONG	GetCharacterKind(SLONG lIndex);
//
extern	void	SetCharacterLandLeftSkill(SLONG lIndex, SHINT lSkill);
extern	SHINT	GetCharacterLandLeftSkill(SLONG lIndex);
extern	void	SetCharacterLandRightSkill(SLONG lIndex, SHINT lSkill);
extern	SHINT	GetCharacterLandRightSkill(SLONG lIndex);
extern	void	SetCharacterLandFnSkillNo(SLONG lIndex, SLONG lFnIndex, SHINT lSkill);
extern	SHINT	GetCharacterLandFnSkillNo(SLONG lIndex, SLONG lFnIndex);
extern	void	SetCharacterLandFnSkillHand(SLONG lIndex, SLONG lFnIndex, SLONG lHand);
extern	SLONG	GetCharacterLandFnSkillHand(SLONG lIndex, SLONG lFnIndex);
//
extern	void	SetCharacterSeaLeftSkill(SLONG lIndex, SHINT lSkill);
extern	SHINT	GetCharacterSeaLeftSkill(SLONG lIndex);
extern	void	SetCharacterSeaRightSkill(SLONG lIndex, SHINT lSkill);
extern	SHINT	GetCharacterSeaRightSkill(SLONG lIndex);
extern	void	SetCharacterSeaFnSkillNo(SLONG lIndex, SLONG lFnIndex, SHINT lSkill);
extern	SHINT	GetCharacterSeaFnSkillNo(SLONG lIndex, SLONG lFnIndex);
extern	void	SetCharacterSeaFnSkillHand(SLONG lIndex, SLONG lFnIndex, SLONG lHand);
extern	SLONG	GetCharacterSeaFnSkillHand(SLONG lIndex, SLONG lFnIndex);
//
extern	void	SetCharacterDoingKind(SLONG lIndex, SLONG lKind);
extern	SLONG	GetCharacterDoingKind(SLONG lIndex);
extern	void	SetCharacterDoingStep(SLONG lIndex, SLONG lStep);
extern	SLONG	GetCharacterDoingStep(SLONG lIndex);
extern	void	SetCharacterDoingKindStep(SLONG lIndex, SLONG lDoingKind, SLONG lDoingStep);
extern	void	SetCharacterDoingMagic(SLONG lIndex, SHINT lMagic);
extern	SHINT	GetCharacterDoingMagic(SLONG lIndex);
extern	void	SetCharacterMagicTimes(SLONG lIndex, SHINT lTimes);
extern	SHINT	GetCharacterMagicTimes(SLONG lIndex);
extern	void	SetCharacterFightTicks(SLONG lIndex, SHINT lTicks);
extern	SHINT	GetCharacterFightTicks(SLONG lIndex);
extern	void	SetCharacterImageAction(SLONG lIndex, SLONG lAction);
extern	SLONG	GetCharacterImageAction(SLONG lIndex);
extern	void	SetCharacterImageID(SLONG lIndex, ULONG uID);
extern	ULONG	GetCharacterImageID(SLONG lIndex);
extern	void	SetCharacterIdleTicks(SLONG lIndex, SLONG lTicks);
extern	SLONG	GetCharacterIdleTicks(SLONG lIndex);
extern	void	SetCharacterSequentialStep(SLONG lIndex, SLONG lStep);
extern	SLONG	GetCharacterSequentialStep(SLONG lIndex);
extern	void	SetCharacterBeatedBy(SLONG lIndex, SLONG lBy);
extern	SLONG	GetCharacterBeatedBy(SLONG lIndex);
extern	void	SetCharacterBeatedWith(SLONG lIndex, SLONG lWith);
extern	SLONG	GetCharacterBeatedWith(SLONG lIndex);
extern	void	SetCharacterPantTicks(SLONG lIndex, SLONG lTicks);
extern	SLONG	GetCharacterPantTicks(SLONG lIndex);
extern	void	SetCharacterBeatedX(SLONG lIndex, SLONG lX);
extern	SLONG	GetCharacterBeatedX(SLONG lIndex);
extern	void	SetCharacterBeatedY(SLONG lIndex, SLONG lY);
extern	SLONG	GetCharacterBeatedY(SLONG lIndex);
extern	void	SetCharacterBeatedXY(SLONG lIndex, SLONG lX, SLONG lY);
extern	void	GetCharacterBeatedXY(SLONG lIndex, SLONG *lX, SLONG *lY);
extern	void	SetCharacterMuseTicks(SLONG lIndex, SLONG lTicks);
extern	SLONG	GetCharacterMuseTicks(SLONG lIndex);
extern	void	SetCharacterClashSteps(SLONG lIndex, SLONG lSteps);
extern	SLONG	GetCharacterClashSteps(SLONG lIndex);
extern	void	SetCharacterPatrolTicks(SLONG lIndex, SLONG lTicks);
extern	SLONG	GetCharacterPatrolTicks(SLONG lIndex);
extern	void	SetCharacterPatrolTotalTicks(SLONG lIndex, SLONG lTicks);
extern	SLONG	GetCharacterPatrolTotalTicks(SLONG lIndex);
extern	void	SetCharacterGadTicks(SLONG lIndex, SLONG lTicks);
extern	SLONG	GetCharacterGadTicks(SLONG lIndex);
extern	void	SetCharacterGadTotalTicks(SLONG lIndex, SLONG lTicks);
extern	SLONG	GetCharacterGadTotalTicks(SLONG lIndex);
extern	void	SetCharacterDeadTicks(SLONG lIndex, SLONG lTicks);
extern	SLONG	GetCharacterDeadTicks(SLONG lIndex);
extern	void	SetCharacterDeadAlpha(SLONG lIndex, SLONG lTicks);
extern	SLONG	GetCharacterDeadAlpha(SLONG lIndex);
extern	void	SetCharacterAttackPantTicks(SLONG lIndex, SLONG lTicks);
extern	SLONG	GetCharacterAttackPantTicks(SLONG lIndex);
extern	void	SetCharacterAttackPantTotalTicks(SLONG lIndex, SLONG lTicks);
extern	SLONG	GetCharacterAttackPantTotalTicks(SLONG lIndex);

//
//
// Level 1 functions ------------------------------------------------
extern	void	SetCharacterLeftSkill(SLONG lIndex, SHINT lSkill);
extern	SHINT	GetCharacterLeftSkill(SLONG lIndex);
extern	void	SetCharacterRightSkill(SLONG lIndex, SHINT lSkill);
extern	SHINT	GetCharacterRightSkill(SLONG lIndex);
extern	void	SetCharacterFnSkill(SLONG lIndex, SLONG lFnIndex, SLONG lSkill, SLONG lHand);
extern	void	GetCharacterFnSkill(SLONG lIndex, SLONG lFnIndex, SLONG *lSkill, SLONG *lHand);
extern	SLONG	FindCharacterBagItemRoom(SLONG lIndex);
extern	SLONG	FindCharacterSashItemRoom(SLONG lIndex);
extern	SLONG	FindCharacterTransItemRoom(SLONG lIndex);
extern	SLONG	FindCharacterByMainName(CHAR *szMainName);
extern	SLONG   FindCharacterLandFnSkillIndex(SLONG lIndex, SLONG lSkillNo, SLONG lHand);
extern	SLONG   FindCharacterSeaFnSkillIndex(SLONG lIndex, SLONG lSkillNo, SLONG lHand);
extern	SLONG	FindCharacterFnSkillIndex(SLONG lIndex, SLONG lSkillNo, SLONG lHand);
extern	SLONG	FindCharacterSkillIndex(SLONG lIndex, SLONG lSkillNo);
extern	SLONG	SetupCharacterHandQuickSkill(SLONG lIndex, SLONG lQuickIndex, SLONG lHand, SLONG lSkillNo);
//
extern	void    InitCharacterRightSkillState(SLONG lIndex);
extern	void    RefreshCharacterRightHandMagicState(SLONG lIndex);
extern	void    SetCharacterRightHandMagicStartSpower(SLONG lIndex);
extern	SLONG   IsCharacterRightHandMagicCanBreak(SLONG lIndex);

//  怪物..用來檢測..莫個npc可否攻擊
extern  SLONG   IsCharacterCanAttackMonsterCheck(SLONG lIndex);
//----
//  一些人物行為的判定函數
//----
//判定人物是否死亡
extern  SLONG   IsCharacterDead(SLONG lIndex);
//判斷莫兩個人之間是否是隊友
extern  SLONG   IsCharacterTeamMember(SLONG lNpcSc, SLONG lNpcTag);
//
//  npc自己..可以自己中斷自己的動作
SLONG   IsCharacterSelfDoingKindBreak(SLONG lIndex);
//  npc可以被..強行中斷的動作
SLONG   IsCharacterOtherDoingBreak(SLONG lIndex);
//-------------------------------------------------------------------------
//  End.
//-------------------------------------------------------------------------

// Jack, quest related functions [5/8/2003]
//-------------------------------------------------------------------------
extern	void	SetQuestType(TPOS_QUEST_INFO *lpQI, SLONG lType);
extern	SLONG	GetQuestType(TPOS_QUEST_INFO *lpQI);
extern	void	SetQuestPublishZone(TPOS_QUEST_INFO *lpQI, CHAR* szZoneName);
extern	CHAR*	GetQuestPublishZone(TPOS_QUEST_INFO *lpQI);
extern	void	SetQuestPublishNpc(TPOS_QUEST_INFO *lpQI, CHAR* szNpcName);
extern	CHAR*	GetQuestPublishNpc(TPOS_QUEST_INFO *lpQI);
extern	void	SetQuestTargetZone(TPOS_QUEST_INFO *lpQI, CHAR *szZoneName);
extern	CHAR*	GetQuestTargetZone(TPOS_QUEST_INFO *lpQI);
extern	void	SetQuestTargetNpc(TPOS_QUEST_INFO *lpQI, CHAR *szNpcName);
extern	CHAR*	GetQuestTargetNpc(TPOS_QUEST_INFO *lpQI);
extern	void	SetQuestAcceptTime(TPOS_QUEST_INFO *lpQI, ULONG uTime);
extern	ULONG	GetQuestAcceptTime(TPOS_QUEST_INFO *lpQI);
extern	void	SetQuestDeadline(TPOS_QUEST_INFO *lpQI, ULONG uDeadline);
extern	ULONG	GetQuestDeadline(TPOS_QUEST_INFO *lpQI);
extern	void	SetQuestPay(TPOS_QUEST_INFO *lpQI, SLONG lPayType, ULONG uPayData);
extern	void	GetQuestPay(TPOS_QUEST_INFO *lpQI, SLONG *lPayType, ULONG *uPayData);
extern	void	SetQuestPunish(TPOS_QUEST_INFO *lpQI, SLONG lPunishType, ULONG uPunishData);
extern	void	GetQuestPunish(TPOS_QUEST_INFO *lpQI, SLONG *lPunishType, ULONG *uPunishData);
extern	void	SetQuestMemo(TPOS_QUEST_INFO *lpQI, CHAR *szMemo);
extern	CHAR*	GetQuestMemo(TPOS_QUEST_INFO *lpQI);
//
extern	void	SetCharacterQuestInfo(SLONG lCharIndex, SLONG lQuestIndex, TPOS_QUEST_INFO *lpInfo);
extern	void	GetCharacterQuestInfo(SLONG lCharIndex, SLONG lQuestIndex, TPOS_QUEST_INFO *lpInfo);
extern	SLONG	FindCharacterEmptyQuestIndex(SLONG lCharIndex);
