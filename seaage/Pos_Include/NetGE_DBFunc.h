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
#define	NETGE_DB_SUCCESS				0		//�ˬd�b���M�K�X���\
#define	NETGE_DB_ERROR_ACCOUNT			-1		//�b�����~
#define	NETGE_DB_ERROR_PASSWORD			-2		//�K�X���~
#define	NETGE_DB_ERROR_ODBC				-99		//ODBC�ާ@����
//
#define	NETGE_DB_ACCOUNT_AVAILABLE		0		//�b���i�H�ϥ�
#define	NETGE_DB_ACCOUNT_EXIST			1		//�b���w�g�s�b
//
#define	NETGE_DB_MAINNAME_AVAILABLE		0		//�W�٥i�H�ϥ�
#define	NETGE_DB_MAINNAME_EXIST			1		//�W�٤w�g�s�b
//
#define	NETGE_DB_ITEM_AVAILABLE			0		//���~�bDB�����s�b
#define	NETGE_DB_ITEM_EXIST				1		//���~�bDB���w�g�s�b
//
#define	NETGE_DB_QQ_AVAILABLE			0		//QQ�bDB�����s�b
#define	NETGE_DB_QQ_EXIST				1		//QQ�bDB���w�g�s�b


// STRUCTURES ///////////////////////////////////////////////////////////////////////////////////////////////
//
typedef	struct POS_DB_ACCOUNT
{
	char	cId[32];            // �b��
	char	cPw[32];            // �K�X
	char	cName[32];			// �u��m�W
	char	Sex;				// �ʧO
	char	cBirthday[12];		// �ͤ�
	char	cCountry[16];		// ��a
	char	cCity[16];          // ����
	char	cAddress[52];		// ��}
	char	cPhone[16];		    // �դѹq�� 
	DWORD	dwJob;				// ¾�~
	DWORD	dwNetStyle;			// �W���覡
	char	cEmail[40];			// �q�l�l�� 
	DWORD	dwPayType;          // �I�ڤ覡
	char	cStatus;			// �b�����A(0-�L��, 1-�I�ƭp�O, 2-�]��p�O, 3-�ɶ��p�O)

	// Jack, Added. [5/15/2003]
	ULONG	RestPoints;			// �Ѿl�I��
	ULONG	LimitDate;			// ���Ĥ��(�Q�i��YYYYMMDD)
	ULONG	RestMinutes;		// �Ѿl�ɶ�(����)
} TPOS_DB_ACCOUNT;


typedef struct POS_DB_CHARACTER
{
	//Name
	char	ID[32];				//���a�b��
	char	MainName[32];		//�H���W��
	char	NickName[32];		//�H���ʺ�
	ULONG	QQID;				//�H����QQ
	SHINT	Index;				//���H���ݩ�ӱb�����ĴX�Ө���, 0~3.
	//Style	
	char	Color;				//�H���C��
	char	Eyes;				//�H����������
	char	Mouth;				//�H���L�گ���
	char	MainNameColor;		//�H���W���C��
	char	NickNameColor;		//�H���ʺ��C��
	char	MessageColor;		//�����C��
	char	TalkBackColor;		//��ܭI���C��
	ULONG	Logo;				//�H��LOGO
	SLONG	LandFileIndex;		//�H���v�T������
	//Position
	char	ZoneName[32];		//�H���Ҧb�ϰ�W��
	SLONG	X;					//�H���y�� X
	SLONG	Y;					//�H���y�� Y
	SLONG	Z;					//�H���y�� Z
	char	Dir;				//�H����V
	SLONG	StopRadius;			//���װϰ�b�|
	//Speed
	SLONG	Mspeed;
	SLONG	FSpeedX;			//��X�b�t��
	SLONG	FSpeedY;			//��Y�b�t��
	UHINT	SailSize;			//��|�Y�������n
	UHINT	Turn;				//����V�O
	UHINT	Weight;				//��q
	SLONG	DegreeDir;			//���V
	//State
	ULONG	BitState;
	// �˳Ƽv�T��Ū�J����A���B��  Hawke 1/8/2003
	//Str
	UHINT	InitStr;			//��l�Ʈɳ]�w���O�q��
	UHINT	LevUpStr;			//�ɯŮɤ��t���O�q��	
	//Ins
	UHINT	InitIns;			//��l�Ʈɳ]�w����ı��
	UHINT	LevUpIns;			//�ɯŮɤ��t����ı��	
	//Wit
	UHINT	InitWit;			//��l�Ʈɳ]�w�����z��
	UHINT	LevUpWit;			//�ɯŮɤ��t�����z��	
	//Lucky
	UHINT	InitLucky;			//��l�Ʈɳ]�w�����B��
	UHINT	LevUpLucky;			//�ɯŮɤ��t�����B��	
	//Attack
	UHINT	SightRange;			//�����d��
	UHINT 	FinalExplodeRate;	//���z�v
	//Defence
	UHINT	DodgeRate;			//���ײv
	UHINT	ParryRate;			//��ײv
	//Property
	UHINT	PropertyPoint;		//�ݩʼW�[�Ѿl�I��
	//Exp Lev
	ULONG	Exp;				//�g���	
	UHINT	Level;				//����
	//Hp Mp
	UHINT	Hp;					//��e�ͩR�O
	UHINT	MaxHp;				//�ͩR�O�W��
	UHINT	HpRes;				//�ͩR�^�_�O
	UHINT	Mp;					//��e���O
	UHINT	MaxMp;				//���O�W��
	UHINT	MpRes;				//���O�^�_�O
	//Skill
	SHINT	SkillNo[36];		//�ޯ�s��
	UHINT	SkillLevel[36];		//�ޯ൥��
	//Equip
	DWORD	EquHead;			//�Y��
	DWORD	EquNeck;			//�V��
	DWORD	EquBody;			//����
	DWORD	EquWaist;			//�y��
	DWORD	EquGlove;			//��M
	DWORD	EquWeapon;			//�Z��
	DWORD	EquWrist;			//����
	DWORD	EquFeet;			//�}��
	DWORD	EquOtherA;			//��LA
	DWORD	EquOtherB;			//��LB
	DWORD	EquOtherC;			//��LC
	//Body Item
	DWORD	BagItem[MAX_CHARACTER_BAG_ITEMS];		//�I�]�����~
	DWORD	SashItem[MAX_CHARACTER_SASH_ITEMS];		//�y�]�����~
	DWORD	TransItem[MAX_CHARACTER_TRANS_ITEMS];	//QQ�ǰe�檫�~
	DWORD	OnMouseItem;		//�b�ƹ��W�����~
	DWORD	TreasureItem;		//���_�Ϫ��~
	ULONG	Money;				//���W������
	//Society
	CHAR	Sex;				//�ʧO
	CHAR	Country;			//��a
	CHAR	Guild[32];			//�u�|
	CHAR	Spouse[32];			//�t��
	CHAR	Career;				//¾�~
	ULONG	Office;				//�u�|��¾��
	CHAR	Nobility[16];		//���
	SLONG	GoodEvil;			//���c��
	SLONG	Prestige;			//�n��
	ULONG	PkCount;			//PK���O�H���h�֤H
	ULONG	PkedCount;			//�Q�HPK��������	
	//Mouse skill and Hot Key
	SHINT	LandLeftSkill;		//���a�ƹ�����ޯ�
	SHINT	LandRightSkill;		//���a�ƹ��k��ޯ�
	SHINT	LandFnSkillNo[MAX_CHARACTER_FN_SKILLS];		//���a����F1~F8�����ޯ�s��
	CHAR	LandFnSkillHand[MAX_CHARACTER_FN_SKILLS];	//���a����F1~F8�����ޯ�]�m�b���u��
	//
	SHINT	SeaLeftSkill;		//���v�ƹ�����ޯ�
	SHINT	SeaRightSkill;		//���v�ƹ��k��ޯ�
	SHINT	SeaFnSkillNo[MAX_CHARACTER_FN_SKILLS];		//���v����F1~F8�����ޯ�s��
	CHAR	SeaFnSkillHand[MAX_CHARACTER_FN_SKILLS];	//���v����F1~F8�����ޯ�]�m�b���u��
	//Datas
	UHINT	FinalAttack;		//�̲ק����O
	UHINT	FinalDefence;		//�̲ר��m�O
	SLONG	SeaFileIndex;		//��v��������
	ULONG	PartRGB[MAX_CHARACTER_PARTS];	//�H���ե��C���
	ULONG	NameColorTicks;		//�W���C��ɶ�
	ULONG	TotalOnlineTicks;	//�`�b�u�ɶ�
	// Jack, added [5/9/2003]
	CHAR	LeaderName[32];		//����Leader���W�r
	// Jack, added [5/14/2003]
	UCHR	CareerLevel;

	//Doing
	SLONG	DoingKind;			//�ư�����
} TPOS_DB_CHARACTER;


typedef struct POS_DB_BANK
{	
	char	MainName[32];
	ULONG	Money;								//�Ȧ檺�s��
	DWORD	Item[MAX_CHARACTER_BANK_ITEMS];		//�Ȧ檺���~
} TPOS_DB_BANK;


typedef struct POS_DB_HOUSE
{
	ULONG	ID;									//�ߤ@ID
	CHAR	Name[32];							//�ЫΦW��
	CHAR	OwnerName[32];						//�֦��̦W��(�ӤH)
	CHAR	GuildName[32];						//�u�|�W��
	CHAR	CityName[32];						//�Ҧb����
	UHINT	Size;								//�ЫΤj�p
	ULONG	GuildPrice;							//�u�|��
	ULONG	PersonalPrice;						//�ӤH��
	UHINT	BoxSize;							//�O�I�c���
	UHINT	BoxCount;							//�O�I�c�ƶq
	DWORD	ItemA[MAX_HOUSE_BOX_ITEMS];			//�Фl�����~
	ULONG	MoneyA;								//�Фl���s��
	DWORD	ItemB[MAX_HOUSE_BOX_ITEMS];			//�Фl�����~
	ULONG	MoneyB;								//�Фl���s��
} TPOS_DB_HOUSE;


typedef	struct POS_DB_ITEM 
{
	ULONG	ID;				//���~�ߤ@ID
	UHINT	BaseID;			//���~��ID
	UCHAR	Hp;				//���~�@�[��
	UCHAR	Attrib[5];		//���~�ݩ�
	UCHAR	Status;			//���~�����A

	// Jack, added for store item without item's unique id. [3/14/2003]
	CHAR	MainName[32];	//�H���W��(�z�L�H���W�� + ���~���� ����o�H�������~)
	UHINT	Index;			//���~����

} TPOS_DB_ITEM;


/*
typedef struct POS_QQ_FRIEND_DB
{
	ULONG			ID;						// �ߤ@��ID	
	UCHAR			Relation;				// �n�a 0-�n, 1-�a 	
}TPOS_QQ_FRIEND_DB;	

typedef struct POS_QQ
{
	ULONG			ID;						// QQ �ߤ@	ID ��
	ULONG			Config;					// �����]�w
	CHAR			WorldServerName[32];	// �@�ɦ��A���W��	
	CHAR			AccountName[32];		// �b���W��	
	CHAR			CharacterName[32];		// ����W��	
	CHAR			GuildName[32];			// �u�|�W��
	CHAR			LeaderName[32];			// ��������W��
	CHAR			NickName[32];			// �ʺ�
	CHAR			Country;				// ��a 
	CHAR			State;					// ���A
	CHAR			Career;					// ¾�~
	DWORD			Level;					// ����
	TPOS_QQ_FRIEND_DB	Friend[256];		// �n�ͦW�� 
	TPOS_QQ_FRIEND_DB	GuildFriend[128];	// �u�|�n�ͦW��
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
	CHAR	MainName[32];	//����W�r
	UHINT	Index;			//���ȯ��ޭ�
	TPOS_QUEST_INFO	Info;	//���ȸ�T
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
