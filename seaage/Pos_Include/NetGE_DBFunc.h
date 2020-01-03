/*
**	NetGE_DBFunc.h 
**	database functions header.
**
**	Jack, 2003.1.8
**
**	Jack, 2003.5.9.
**		-- Add POS_DB_CHARACTER::LeaderName.
**	Jack, 2003.5.14.
**		-- Add POS_DB_CHARACTER::CareerLevel.
**	Jack, 2003.5.15.
**		-- Add POS_DB_ACCOUNT::RestPoints/LimitDate/RestMinutes.
*/
#pragma once
#include <windows.h>
#include <windowsx.h>
#include <sql.h>
#include <sqlext.h>
#include "NetGE_Character.h"


//
// STRUCTURES ///////////////////////////////////////////////////////////////////////////////////////////////
//
#define	NETGE_DB_SUCCESS				0		//檢查帳號和密碼成功
#define	NETGE_DB_ERROR_ACCOUNT			-1		//帳號錯誤
#define	NETGE_DB_ERROR_PASSWORD			-2		//密碼錯誤
#define	NETGE_DB_ERROR_ODBC				-99		//ODBC操作失敗
//
#define	NETGE_DB_ACCOUNT_AVAILABLE		0		//帳號可以使用
#define	NETGE_DB_ACCOUNT_EXIST			1		//帳號已經存在
//
#define	NETGE_DB_MAINNAME_AVAILABLE		0		//名稱可以使用
#define	NETGE_DB_MAINNAME_EXIST			1		//名稱已經存在
//
#define	NETGE_DB_ITEM_AVAILABLE			0		//物品在DB中不存在
#define	NETGE_DB_ITEM_EXIST				1		//物品在DB中已經存在
//
#define	NETGE_DB_QQ_AVAILABLE			0		//QQ在DB中不存在
#define	NETGE_DB_QQ_EXIST				1		//QQ在DB中已經存在


// STRUCTURES ///////////////////////////////////////////////////////////////////////////////////////////////
//
typedef	struct POS_DB_ACCOUNT
{
	char	cId[32];            // 帳號
	char	cPw[32];            // 密碼
	char	cName[32];			// 真實姓名
	char	Sex;				// 性別
	char	cBirthday[12];		// 生日
	char	cCountry[16];		// 國家
	char	cCity[16];          // 城市
	char	cAddress[52];		// 住址
	char	cPhone[16];		    // 白天電話 
	DWORD	dwJob;				// 職業
	DWORD	dwNetStyle;			// 上網方式
	char	cEmail[40];			// 電子郵件 
	DWORD	dwPayType;          // 付款方式
	char	cStatus;			// 帳號狀態(0-無效, 1-點數計費, 2-包月計費, 3-時間計費)

	// Jack, Added. [5/15/2003]
	ULONG	RestPoints;			// 剩餘點數
	ULONG	LimitDate;			// 有效日期(十進制YYYYMMDD)
	ULONG	RestMinutes;		// 剩餘時間(分鐘)
} TPOS_DB_ACCOUNT;


typedef struct POS_DB_CHARACTER
{
	//Name
	char	ID[32];				//玩家帳號
	char	MainName[32];		//人物名稱
	char	NickName[32];		//人物暱稱
	ULONG	QQID;				//人物的QQ
	SHINT	Index;				//本人物屬於該帳號的第幾個角色, 0~3.
	//Style	
	char	Color;				//人物顏色
	char	Eyes;				//人物眼睛索引
	char	Mouth;				//人物嘴巴索引
	char	MainNameColor;		//人物名稱顏色
	char	NickNameColor;		//人物暱稱顏色
	char	MessageColor;		//消息顏色
	char	TalkBackColor;		//對話背景顏色
	ULONG	Logo;				//人物LOGO
	SLONG	LandFileIndex;		//人物影響文件索引
	//Position
	char	ZoneName[32];		//人物所在區域名稱
	SLONG	X;					//人物座標 X
	SLONG	Y;					//人物座標 Y
	SLONG	Z;					//人物座標 Z
	char	Dir;				//人物方向
	SLONG	StopRadius;			//阻擋區域半徑
	//Speed
	SLONG	Mspeed;
	SLONG	FSpeedX;			//船X軸速度
	SLONG	FSpeedY;			//船Y軸速度
	UHINT	SailSize;			//船帆吃風的面積
	UHINT	Turn;				//船轉向力
	UHINT	Weight;				//船重量
	SLONG	DegreeDir;			//船的方向
	//State
	ULONG	BitState;
	// 裝備影響的讀入之後再做運算  Hawke 1/8/2003
	//Str
	UHINT	InitStr;			//初始化時設定的力量值
	UHINT	LevUpStr;			//升級時分配的力量值	
	//Ins
	UHINT	InitIns;			//初始化時設定的直覺值
	UHINT	LevUpIns;			//升級時分配的直覺值	
	//Wit
	UHINT	InitWit;			//初始化時設定的智慧值
	UHINT	LevUpWit;			//升級時分配的智慧值	
	//Lucky
	UHINT	InitLucky;			//初始化時設定的幸運值
	UHINT	LevUpLucky;			//升級時分配的幸運值	
	//Attack
	UHINT	SightRange;			//視野範圍
	UHINT 	FinalExplodeRate;	//膛爆率
	//Defence
	UHINT	DodgeRate;			//躲避率
	UHINT	ParryRate;			//格擋率
	//Property
	UHINT	PropertyPoint;		//屬性增加剩餘點數
	//Exp Lev
	ULONG	Exp;				//經驗值	
	UHINT	Level;				//等級
	//Hp Mp
	UHINT	Hp;					//當前生命力
	UHINT	MaxHp;				//生命力上限
	UHINT	HpRes;				//生命回復力
	UHINT	Mp;					//當前內力
	UHINT	MaxMp;				//內力上限
	UHINT	MpRes;				//內力回復力
	//Skill
	SHINT	SkillNo[36];		//技能編號
	UHINT	SkillLevel[36];		//技能等級
	//Equip
	DWORD	EquHead;			//頭部
	DWORD	EquNeck;			//頸部
	DWORD	EquBody;			//身體
	DWORD	EquWaist;			//腰部
	DWORD	EquGlove;			//手套
	DWORD	EquWeapon;			//武器
	DWORD	EquWrist;			//手環
	DWORD	EquFeet;			//腳部
	DWORD	EquOtherA;			//其他A
	DWORD	EquOtherB;			//其他B
	DWORD	EquOtherC;			//其他C
	//Body Item
	DWORD	BagItem[MAX_CHARACTER_BAG_ITEMS];		//背包內物品
	DWORD	SashItem[MAX_CHARACTER_SASH_ITEMS];		//腰包內物品
	DWORD	TransItem[MAX_CHARACTER_TRANS_ITEMS];	//QQ傳送欄物品
	DWORD	OnMouseItem;		//在滑鼠上的物品
	DWORD	TreasureItem;		//藏寶圖物品
	ULONG	Money;				//身上的金錢
	//Society
	CHAR	Sex;				//性別
	CHAR	Country;			//國家
	CHAR	Guild[32];			//工會
	CHAR	Spouse[32];			//配偶
	CHAR	Career;				//職業
	ULONG	Office;				//工會的職位
	CHAR	Nobility[16];		//爵位
	SLONG	GoodEvil;			//善惡值
	SLONG	Prestige;			//聲望
	ULONG	PkCount;			//PK死別人的多少人
	ULONG	PkedCount;			//被人PK死的次數	
	//Mouse skill and Hot Key
	SHINT	LandLeftSkill;		//陸地滑鼠左鍵技能
	SHINT	LandRightSkill;		//陸地滑鼠右鍵技能
	SHINT	LandFnSkillNo[MAX_CHARACTER_FN_SKILLS];		//陸地按鍵F1~F8對應技能編號
	CHAR	LandFnSkillHand[MAX_CHARACTER_FN_SKILLS];	//陸地按鍵F1~F8對應技能設置在哪只手
	//
	SHINT	SeaLeftSkill;		//海洋滑鼠左鍵技能
	SHINT	SeaRightSkill;		//海洋滑鼠右鍵技能
	SHINT	SeaFnSkillNo[MAX_CHARACTER_FN_SKILLS];		//海洋按鍵F1~F8對應技能編號
	CHAR	SeaFnSkillHand[MAX_CHARACTER_FN_SKILLS];	//海洋按鍵F1~F8對應技能設置在哪只手
	//Datas
	UHINT	FinalAttack;		//最終攻擊力
	UHINT	FinalDefence;		//最終防禦力
	SLONG	SeaFileIndex;		//船隻影像文件索引
	ULONG	PartRGB[MAX_CHARACTER_PARTS];	//人物組件顏色組
	ULONG	NameColorTicks;		//名稱顏色時間
	ULONG	TotalOnlineTicks;	//總在線時間
	// Jack, added [5/9/2003]
	CHAR	LeaderName[32];		//隊伍Leader的名字
	// Jack, added [5/14/2003]
	UCHR	CareerLevel;

	//Doing
	SLONG	DoingKind;			//事務類型
} TPOS_DB_CHARACTER;


typedef struct POS_DB_BANK
{	
	char	MainName[32];
	ULONG	Money;								//銀行的存款
	DWORD	Item[MAX_CHARACTER_BANK_ITEMS];		//銀行的物品
} TPOS_DB_BANK;


typedef struct POS_DB_HOUSE
{
	ULONG	ID;									//唯一ID
	CHAR	Name[32];							//房屋名稱
	CHAR	OwnerName[32];						//擁有者名稱(個人)
	CHAR	GuildName[32];						//工會名稱
	CHAR	CityName[32];						//所在城市
	UHINT	Size;								//房屋大小
	ULONG	GuildPrice;							//工會價
	ULONG	PersonalPrice;						//個人價
	UHINT	BoxSize;							//保險箱格數
	UHINT	BoxCount;							//保險箱數量
	DWORD	ItemA[MAX_HOUSE_BOX_ITEMS];			//房子的物品
	ULONG	MoneyA;								//房子的存款
	DWORD	ItemB[MAX_HOUSE_BOX_ITEMS];			//房子的物品
	ULONG	MoneyB;								//房子的存款
} TPOS_DB_HOUSE;


typedef	struct POS_DB_ITEM 
{
	ULONG	ID;				//物品唯一ID
	UHINT	BaseID;			//物品基本ID
	UCHAR	Hp;				//物品耐久度
	UCHAR	Attrib[5];		//物品屬性
	UCHAR	Status;			//物品的狀態

	// Jack, added for store item without item's unique id. [3/14/2003]
	CHAR	MainName[32];	//人物名稱(透過人物名稱 + 物品索引 來獲得人物的物品)
	UHINT	Index;			//物品索引

} TPOS_DB_ITEM;


/*
typedef struct POS_QQ_FRIEND_DB
{
	ULONG			ID;						// 唯一的ID	
	UCHAR			Relation;				// 好壞 0-好, 1-壞 	
}TPOS_QQ_FRIEND_DB;	

typedef struct POS_QQ
{
	ULONG			ID;						// QQ 唯一	ID 號
	ULONG			Config;					// 相關設定
	CHAR			WorldServerName[32];	// 世界伺服器名稱	
	CHAR			AccountName[32];		// 帳號名稱	
	CHAR			CharacterName[32];		// 角色名稱	
	CHAR			GuildName[32];			// 工會名稱
	CHAR			LeaderName[32];			// 隊長角色名稱
	CHAR			NickName[32];			// 暱稱
	CHAR			Country;				// 國家 
	CHAR			State;					// 狀態
	CHAR			Career;					// 職業
	DWORD			Level;					// 等級
	TPOS_QQ_FRIEND_DB	Friend[256];		// 好友名單 
	TPOS_QQ_FRIEND_DB	GuildFriend[128];	// 工會好友名單
}TPOS_QQ;
*/
typedef	struct  POS_QQ	TPOS_DB_QQ;


typedef	struct POS_DB_QQMSG
{
	ULONG	SendID;
	ULONG	RecvID;
	ULONG	MsgTime;
	CHAR	MsgStr[220];
} TPOS_DB_QQMSG;


typedef	struct POS_DB_QUEST
{
	CHAR	MainName[32];	//角色名字
	UHINT	Index;			//任務索引值
	TPOS_QUEST_INFO	Info;	//任務資訊
} TPOS_DB_QUEST;
//
// FUNCTIONS ////////////////////////////////////////////////////////////////////////////////////////////////
//
extern	SLONG	AppendRecordToAccountDB(TPOS_DB_ACCOUNT *lpAccount);
extern	SLONG	DeleteRecordFromAccountDB(CHAR *szAccount, CHAR *szPassword);
extern	SLONG	UpdateRecordOfAccountDB(TPOS_DB_ACCOUNT *lpAccount);
extern	SLONG	GetRecordFromAccountDB(TPOS_DB_ACCOUNT *lpAccount, CHAR *szAccount);
extern	SLONG	CheckPasswordOfAccountDB(CHAR *szAccount, CHAR *szPassword);
extern	SLONG	CheckAccountOfAccountDB(CHAR *szAccount);
extern	SLONG	ChangePasswordOfAccountDB(CHAR *szAccount, CHAR *szPassword);
extern	VOID	BindAccountDBColumn(HSTMT hStmt, TPOS_DB_ACCOUNT *lpAccount);

extern	SLONG	AppendRecordToCharacterDB(TPOS_DB_CHARACTER *lpChar);
extern	SLONG	DeleteRecordFromCharacterDB(CHAR *szAccount, CHAR *szMainName);
extern	SLONG	UpdateRecordOfCharacterDB(TPOS_DB_CHARACTER *lpChar);
extern	SLONG	GetRecordFromCharacterDBByMainName(TPOS_DB_CHARACTER *lpChar, CHAR *szMainName);
extern	SLONG	GetRecordFromCharacterDBByAccountAndIndex(TPOS_DB_CHARACTER *lpChar, CHAR *szAccount, SLONG lIndex);
extern	SLONG	GetRecordFromCharacterDBByQQID(TPOS_DB_CHARACTER *lpChar, ULONG QQID);
extern	SLONG	CheckMainNameOfCharacterDB(CHAR *szMainName);
extern	VOID	BindCharacterDBColumn(HSTMT hStmt, TPOS_DB_CHARACTER *lpChar);

extern	SLONG	AppendRecordToItemDB(TPOS_DB_ITEM *lpItem);
extern	SLONG	DeleteRecordFromItemDB(ULONG UniqueID);
extern	SLONG	DeleteRecordFromItemDBByMainName(CHAR *szMainName);
extern	SLONG	UpdateRecordOfItemDBByUniqueID(TPOS_DB_ITEM *lpItem);
extern	SLONG	UpdateRecordOfItemDBByMainNameAndIndex(TPOS_DB_ITEM *lpItem);
extern	SLONG	GetRecordFromItemDBByUniqueID(TPOS_DB_ITEM *lpItem, ULONG UniqueID);
extern	SLONG	GetRecordFromItemDBByMainNameAndIndex(TPOS_DB_ITEM *lpItem, CHAR *szMainName, SLONG lIndex);
extern	SLONG	CheckUniqueIDOfItemDB(ULONG UniqueID);
extern	VOID	BindItemDBColumn(HSTMT hStmt, TPOS_DB_ITEM *lpItem);

extern	SLONG	AppendRecordToQQDB(TPOS_DB_QQ *lpQQ);
extern	SLONG	DeleteRecordFromQQDBByID(ULONG ID);
extern	SLONG	UpdateRecordOfQQDB(TPOS_DB_QQ *lpQQ);
extern	SLONG	GetRecordFromQQDBByID(TPOS_DB_QQ *lpQQ, ULONG ID);
extern	SLONG	CheckIDOfQQDB(ULONG ID);
extern	VOID	BindQQDBColumn(HSTMT hStmt, TPOS_DB_QQ *lpQQ);

extern	SLONG	AppendRecordToQQMsgDB(TPOS_DB_QQMSG *lpMsg);
extern	SLONG	DeleteReocrdFromQQMsgDBByRecvID(ULONG ID);
extern	SLONG	DeleteRecordFromQQMsgDBBySendID(ULONG ID);
extern	SLONG	DeleteRecordFromQQMsgDBByMsgTime(ULONG MsgTime);
extern	SLONG	GetRecordFromQQMsgDBByRecvID(TPOS_DB_QQMSG *lpMsg, ULONG ID);
extern	SLONG	GetRecordFromQQMsgDBBySendID(TPOS_DB_QQMSG *lpMsg, ULONG ID);
extern	VOID	BindQQMsgDBColumn(HSTMT hStmt, TPOS_DB_QQMSG *lpMsg);

extern	SLONG	AppendRecordToBankDB(TPOS_DB_BANK *lpBank);
extern	SLONG	DeleteRecordFromBankDB(CHAR *szMainName);
extern	SLONG	UpdateRecordOfBankDB(TPOS_DB_BANK *lpBank);
extern	SLONG	GetRecordFromBankDB(TPOS_DB_BANK *lpBank, CHAR *szMainName);
extern	VOID	BindBankDBColumn(HSTMT hStmt, TPOS_DB_BANK *lpBank);

extern	SLONG	AppendRecordToHouseDB(TPOS_DB_HOUSE *lpHouse);
extern	SLONG	DeleteRecordFromHouseDBByHouseID(ULONG uID);
extern	SLONG	DeleteRecordFromHouseDBByOwnerName(CHAR *szOwnerName);
extern	SLONG	DeleteRecordFromHouseDBByGuildName(CHAR *szGuildName);
extern	SLONG	DeleteRecordFromHouseDBByCityName(CHAR *szCityName);
extern	SLONG	UpdateRecordOfHouseDBByHouseID(TPOS_DB_HOUSE *lpHouse, ULONG uID);
extern	SLONG	GetRecordFromHouseDBByHouseID(TPOS_DB_HOUSE *lpHouse, ULONG uID);
extern	VOID	BindHouseDBColumn(HSTMT hStmt, TPOS_DB_HOUSE *lpHouse);

extern	SLONG	AppendRecordToQuestDB(TPOS_DB_QUEST *lpQuest);
extern	SLONG	DeleteRecordFromQuestDBByMainName(CHAR *szMainName);
extern	SLONG	UpdateRecordOfQuestDBByMainNameAndIndex(TPOS_DB_QUEST *lpQuest);
extern	SLONG	GetRecordFromQuestDBByMainNameAndIndex(TPOS_DB_QUEST *lpQuest, CHAR *szMainName, SLONG lIndex);
extern	VOID	BindQuestDBColumn(HSTMT hStmt, TPOS_DB_QUEST *lpQuest);
