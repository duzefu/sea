//===============================================================================
// Netge_Event_Struct_Def.h
//===============================================================================
#ifndef NETGE_EVENT_STRUCT_DEF_H
#define NETGE_EVENT_STRUCT_DEF_H

//-------------------------------------------------------------------------------
// Login Door and World
//-------------------------------------------------------------------------------
typedef	struct POS_EVENT_LOGIN
{
	char	cId[32];
	char	cPw[32];
	DWORD	dwVersion;
}TPOS_EVENT_LOGIN;
//-------------------------------------------------------------------------------
// Register Account Struct
//-------------------------------------------------------------------------------
typedef	struct POS_EVENT_REGISTERACCOUNT
{
	char		cId[32];                // �b��
	char		cPw[32];                // �K�X
	char		cName[32];				// �u��m�W
	DWORD		dwSex;					// �ʧO
	char		cBirthday[8];			// �ͤ�
	char		cCountry[16];			// ��a
	char		cCity[16];              // ����
	char		cAddress[52];			// ��}
	char		cPhone[16];		    	// �դѹq�� 
	DWORD		dwJob;				    // ¾�~
	DWORD		dwNetStyle;				// �W���覡
	char		cEmail[40];				// �q�l�l�� 
	DWORD		dwPayType;              // �I�ڤ覡
}TPOS_EVENT_REGISTERACCOUNT;
//-------------------------------------------------------------------------------
// Change Account Profile Struct
//-------------------------------------------------------------------------------
typedef	struct POS_EVENT_CHANGEPROFILE
{		
	char		cName[32];				// �u��m�W
	DWORD		dwSex;					// �ʧO
	char		cBirthday[8];			// �ͤ�
	char		cCountry[16];			// ��a
	char		cCity[16];              // ����
	char		cAddress[52];			// ��}
	char		cPhone[16];		    	// �դѹq�� 
	DWORD		dwJob;				    // ¾�~
	DWORD		dwNetStyle;				// �W���覡
	char		cEmail[40];				// �q�l�l�� 
	DWORD		dwPayType;              // �I�ڤ覡
}TPOS_EVENT_CHANGEPROFILE;
//-------------------------------------------------------------------------------
// Register Account Check ID Struct
//-------------------------------------------------------------------------------
typedef	struct POS_EVENT_REGISTERACCOUNTCHECK
{
	char		cId[32];                // �b��	
	char		cPw[32];                // �K�X
}TPOS_EVENT_REGISTERACCOUNTCHECK;
//-------------------------------------------------------------------------------
// Change Account Password Struct
//-------------------------------------------------------------------------------
typedef	struct POS_EVENT_CHANGEPASSWORD
{	
	char		cPw[32];                // �K�X
}TPOS_EVENT_CHANGEPASSWORD;
//-------------------------------------------------------------------------------
// New World Server Active
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_NEWWORLDINFO
{
	char	        cName[32]; 
	DWORD	        dwPlayerCount;
	DWORD		   	dwPort;
	char        	cAddr[16];	
	DWORD			dwActive; 	
}TPOS_EVENT_NEWWORLDINFO;
//-------------------------------------------------------------------------------
// Request World Server Info
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_REQUESTWORLDINFO
{
	DWORD			dwIndex;		
}TPOS_EVENT_REQUESTWORLDINFO;
//-------------------------------------------------------------------------------
// Get World Server Info
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_GETWORLDINFO
{
	DWORD			dwIndex;
	char	        cName[32]; 
	DWORD	        dwPlayerCount;
	DWORD		   	dwPort;
	char        	cAddr[16];	
	DWORD			dwActive; 	
}TPOS_EVENT_GETWORLDINFO;
//-------------------------------------------------------------------------------
// One World Server Close
//-------------------------------------------------------------------------------
typedef	struct POS_EVENT_CLOSEWORLDINFO
{
	char			cName[32];
}TPOS_EVENT_CLOSEWORLDINFO;
//-------------------------------------------------------------------------------
// Refresh World Server Info
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_REFRESHWORLDINFO
{
	char	        cName[32]; 
	DWORD	        dwPlayerCount;	
	DWORD			dwActive; 
}TPOS_EVENT_REFRESHWORLDINFO;
//-------------------------------------------------------------------------------
// Request Zone Server Info
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_REQUESTZONEINFO
{
	DWORD			dwIndex;		
}TPOS_EVENT_REQUESTZONEINFO;
//-------------------------------------------------------------------------------
// Close Zone Server Info
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_CLOSEZONEINFO
{
	char	        cName[32]; 	
}TPOS_EVENT_CLOSEZONEINFO;
//-------------------------------------------------------------------------------
// Refresh Zone Server Info
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_REFRESHZONEINFO
{
	char	        cName[32];
	DWORD	        dwPlayerCount;	
}TPOS_EVENT_REFRESHZONEINFO;
//-------------------------------------------------------------------------------
// New Zone Server Info
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_NEWZONEINFO
{
	char	        cName[32];
	char			cMapName[32];
	char			cAddr[16];
	DWORD			dwPort;
	DWORD	        dwPlayerCount;
	DWORD			dwType;	
}TPOS_EVENT_NEWZONEINFO;
//-------------------------------------------------------------------------------
// System Message Info
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_SYSTEMMESSAGE
{
	char			WorldName[32];
	char	        cMsg[256]; 	
}TPOS_EVENT_SYSTEMMESSAGE;
//-------------------------------------------------------------------------------
// Request Character Default Info
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_REQUESTCHARACTERDEFAULT
{
	int				iIndex;
}TPOS_EVENT_REQUESTCHARACTERDEFAULT;
//-------------------------------------------------------------------------------
// Get Character Default Info
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_GETCHARACTERDEFAULT
{
	SLONG			slFileIndex;	//����v��������
	CHAR			cSex;			//�ʧO
	CHAR			cCareer;		//¾�~
	CHAR			cColor;			//�C��
	CHAR			cEyes;			//����
	CHAR			cMouth;			//�L
	CHAR			cCountry;		//���ݰ�a
	UINT			iStr;			//�O�q
	UINT			iIns;			//��ı
	UINT			iWis;			//���O
	UINT			iLucky;			//�B��
	UINT			iHp;			//�ͩR�O
	UINT			iMp;			//�k�O
	UINT			iMspeed;		//���ʳt��
}TPOS_EVENT_GETCHARACTERDEFAULT;
//-------------------------------------------------------------------------------
// Request Character Info
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_REQUESTCHARACTERINFO
{
	int				iIndex;
}TPOS_EVENT_REQUESTCHARACTERINFO;
//-------------------------------------------------------------------------------
// Get Character Info
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_GETCHARACTERINFO
{	
	char	cMainName[32];				//�W��
	char	cNickName[32];				//�ʺ�
	char	cCareer;					//¾�~
	char	cCountry;					//��a
	char	cSex;						//�ʧO
	UHINT	uhiLevel;					//����
	CHAR	cNobility[16];				//���
	CHAR	cZone[32];					//�ϰ�
	ULONG	QQID;						// QQ ID
}TPOS_EVENT_GETCHARACTERINFO;
//-------------------------------------------------------------------------------
// Create Character Check Info
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_CREATECHARACTERCHECK
{
	char			cMainName[32];
}TPOS_EVENT_CREATECHARACTERCHECK;
//-------------------------------------------------------------------------------
// Delete Character Info
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_DELETECHARACTER
{
	char			cMainName[32];
}TPOS_EVENT_DELETECHARACTER;
//-------------------------------------------------------------------------------
// Create Character Final Info
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_CREATECHARACTERFINAL
{
	DWORD	dwCharacterDefaultIndex;	//�ҿ諸¾�~����
	DWORD	dwIndex;					//���b�����ĴX�Ө���	
	char	cMainName[32];				//�W��
	char	cNickName[32];				//�ʺ�
	CHAR	Color;						//�C��
	CHAR	Eyes;						//����
	CHAR	Mouth;						//�L
	CHAR	Country;					//���ݰ�a
	ULONG	PartRGB[7];					//�U�����C��
}TPOS_EVENT_CREATECHARACTERFINAL;
//-------------------------------------------------------------------------------
// Player Request Login Zone Server
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_REQUESTLOGINZONE
{
	char	cZone[32];
}TPOS_EVENT_REQUESTLOGINZONE;
//-------------------------------------------------------------------------------
// Player Get Zone Server Info
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_GETZONEINFO
{
	DWORD	dwIndex;			//����
	char	cZone[32];			//�ϰ�W��
	char	cMapName[32];		//�a�ϦW��
	char	cAddr[16];			//IP�a�}
	DWORD	dwPort;				//Port
	DWORD	dwType;				//�ϰ�����
	DWORD	dwPlayerCount;		//�H��
}TPOS_EVENT_GETZONEINFO;
//-------------------------------------------------------------------------------
// Zone Server Login
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_ZONELOGIN
{
	char	cZone[32];			//�ϰ�W��	
}TPOS_EVENT_ZONELOGIN;
//-------------------------------------------------------------------------------
// Player Join
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_PLAYERJOIN
{
	int		iIndex;
	char	cMainName[32];
	char	MainNameColor;
	SLONG	slFileIndex;	//����v��������
	UINT	iHp;			//�ͩR�O
	UINT	iMaxHp;
	UINT	iMp;			//�k�O
	UINT	iMaxMp;
	UINT	iLevel;			
	UINT	iMspeed;		//���ʳt��
	CHAR	cColor;			//�C��	
	LONG	lX;
	LONG	lY;
	LONG	lZ;
	CHAR	cDir;
	UHINT	iSightRange;
	SLONG	slSailSize;
	SLONG	slWeight;
	SLONG	slTurn;
	SLONG	slDoingKind;	//��eDoingKind
	ULONG	ulBitState;
	ULONG	PartRGB[7];
}TPOS_EVENT_PLAYERJOIN;

//-------------------------------------------------------------------------------
// Player Exit
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_PLAYEREXIT
{
	int				iIndex;	
}TPOS_EVENT_PLAYEREXIT;
//-------------------------------------------------------------------------------
// Refresh Heart Beat
//-------------------------------------------------------------------------------
typedef	struct POS_EVENT_REFRESHFLAG
{
	DWORD			dwHeartBeat;
}TPOS_EVENT_REFRESHFLAG;
//-------------------------------------------------------------------------------
// Change Zone Server 
//-------------------------------------------------------------------------------
typedef	struct POS_EVENT_CHANGEZONESERVER
{
	char			cZoneName[32];
	char			cMapName[32];
	char			cAddr[16];
	DWORD			dwPort;		
}TPOS_EVENT_CHANGEZONESERVER;
//-------------------------------------------------------------------------------
// Change Zone Server 
//-------------------------------------------------------------------------------
typedef	struct POS_EVENT_GETCHANGEMAP
{
	char			cZoneName[32];
	char			cMapName[32];
	char			cAddr[16];
	DWORD			dwPort;
	DWORD			dwType;
	SLONG			lX;
	SLONG			lY;
	SLONG			lZ;
	char			cDir;
}TPOS_EVENT_GETCHANGEMAP;
//-------------------------------------------------------------------------------
// Get Npc Relive
//-------------------------------------------------------------------------------
typedef	struct POS_EVENT_GETNPCRELIVE 
{
	DWORD			Index;
	UHINT			iHp;
	UHINT			iMp;
	SLONG			lX;
	SLONG			lY;
	SLONG			lZ;
	char			cDir;
	SLONG			slDoingKind;
}TPOS_EVENT_GETNPCRELIVE;
//-------------------------------------------------------------------------------
// Set Npc Hp
//-------------------------------------------------------------------------------
typedef	struct POS_EVENT_SETNPCHP 
{
	SLONG			Index;
	UHINT			iHp;
}TPOS_EVENT_SETNPCHP;
//-------------------------------------------------------------------------------
// Set Npc Mp
//-------------------------------------------------------------------------------
typedef	struct POS_EVENT_SETNPCMP 
{
	SLONG			Index;
	UHINT			iMp;
}TPOS_EVENT_SETNPCMP;
//-------------------------------------------------------------------------------
// My Character 
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_MYCHARACTER
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
	SLONG	FileIndex;			//�H���v�T������	
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
	UHINT	FinalStr;			//��l�Ʈɳ]�w���O�q��	
	//Ins
	UHINT	FinalIns;			//��l�Ʈɳ]�w����ı��	
	//Wit
	UHINT	FinalWit;			//��l�Ʈɳ]�w�����z��	
	//Lucky
	UHINT	FinalLucky;			//��l�Ʈɳ]�w�����B��	
	//Attack
	UHINT	SightRange;			//�����d��	
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
	TPOS_ITEM	EquHead;			//�Y��
	TPOS_ITEM	EquNeck;			//�V��
	TPOS_ITEM	EquBody;			//����
	TPOS_ITEM	EquWaist;			//�y��
	TPOS_ITEM	EquGlove;			//��M
	TPOS_ITEM	EquWeapon;			//�Z��
	TPOS_ITEM	EquWrist;			//����
	TPOS_ITEM	EquFeet;			//�}��
	TPOS_ITEM	EquOtherA;			//��LA
	TPOS_ITEM	EquOtherB;			//��LB
	TPOS_ITEM	EquOtherC;			//��LC
	//Body Item
	TPOS_ITEM	BagItem[MAX_CHARACTER_BAG_ITEMS];		//�I�]�����~
	TPOS_ITEM	SashItem[MAX_CHARACTER_SASH_ITEMS];		//�y�]�����~
	TPOS_ITEM	TransItem[MAX_CHARACTER_TRANS_ITEMS];	//QQ�ǰe�檫�~
	TPOS_ITEM	OnMouseItem;		//�b�ƹ��W�����~
	TPOS_ITEM	TreasureItem;		//���_�Ϫ��~
	ULONG	Money;				//���W������
	//Society
	CHAR	Sex;				//�ʧO
	CHAR	Country;			//��a
	CHAR	Guild[32];			//�u�|
	CHAR	Spouse[32];			//�t��
	CHAR	Career;				//¾�~
	UCHR	CareerLevel;		//¾�~����
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
	ULONG	PartRGB[7];
	ULONG	NameColorTicks;		//�W�r�C�⪺�ɶ�
	ULONG	TotalOnlineTicks;	//�`�b�u�ɶ�	
	//Doing
	SLONG	DoingKind;			//�ư�����
}TPOS_EVENT_MYCHARACTER;
//-------------------------------------------------------------------------------
// My Character Data
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_ZONELOGINOK
{
	DWORD					NpcIndex;
	TPOS_EVENT_MYCHARACTER	data;
}TPOS_EVENT_ZONELOGINOK;
//-------------------------------------------------------------------------------
// Request Player List
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_REQUESTPLAYERLIST
{
	int		iIndex;
}TPOS_EVENT_REQUESTPLAYERLIST;
//-------------------------------------------------------------------------------
// GET Player List
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_GETPLAYERLIST
{
	int		iIndex;
	char	cMainName[32];
	SLONG	slFileIndex;	//����v��������
	UINT	iHp;			//�ͩR�O
	UINT	iMp;			//�k�O
	UINT	iMspeed;		//���ʳt��
	CHAR	cColor;			//�C��
	CHAR	cEyes;			//����
	CHAR	cMouth;			//�L
	LONG	lX;
	LONG	lY;
	LONG	lZ;
	SLONG	slDoingKind;	//��eDoingKind
	LONG	lDoingStep;		
    UHINT	iMaxHp;
	UHINT	iMaxMp;
    char	Picture;
    char	cMainNameColor;
    char	cNickNameColor;
    char	cMessageColor;
    char	cTalkBackColor;
    DWORD	dwLogo;
    UHINT	iLevel;
    UHINT	iSightRange;
	DWORD	BitState;
	UHINT	iDirFrame;
	LONG	lDestNo;
	LONG	lOrigNo;
	LONG	lDestX;
	LONG	lDestY;
	LONG    lDestZ;
	LONG	lOrigX;
	LONG	lOrigY;
	LONG	lOrigZ;	
	char	cDir;
	UHINT	SailSize;
	UHINT	Turn;
	UHINT	Weight;
	SLONG	DegreeDir;	
	ULONG	PartRGB[7];
}TPOS_EVENT_GETPLAYERLIST;
//-------------------------------------------------------------------------------
// GET Player Quick Skill Item
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_GETPLAYERQUICKSKILLITEM
{
	SHINT	LeftSkillNo;
	SHINT	RightSkillNo;
	SHINT	FnSkillNo[MAX_CHARACTER_FN_SKILLS];		//����F1~F8�����ޯ�s��
	CHAR	FnSkillHand[MAX_CHARACTER_FN_SKILLS];	//����F1~F8�����ޯ�]�m�b���u��
	DWORD	SashItem[MAX_CHARACTER_SASH_ITEMS];		//�y�]�����~	
}TPOS_EVENT_GETPLAYERQUICKSKILLITEM;
//-------------------------------------------------------------------------------
// GET Player Skill
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_GETPLAYERSKILL
{
	SHINT	SkillNo[MAX_CHARACTER_SKILLS];			//�ޯ�s��
	UHINT	SkillLevel[MAX_CHARACTER_SKILLS];		//�ޯ൥��	
}TPOS_EVENT_GETPLAYERSKILL;
//-------------------------------------------------------------------------------
// GET Player Skill
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_INITZONEWEATHER
{
	DWORD      dWeatherType;      // �Ѯ𫬺A  
	DWORD      dRainActive;       // �O�_�U�B
	DWORD      dRainSize;         // �B���j�p
	DWORD      dSnowActive;       // �O�_�U��
	DWORD      dSnowSize;         // �����j�p
	DWORD      dCloudActive;      // �O�_����
	DWORD      dCloudSize;        // �����j�p
	DWORD      dThunderActive;    // �O�_���p  
	DWORD      dThunderSize;      // �p���j�p
	DWORD      dEarthQuakeActive; // �O�_�a�_
	DWORD      dEarthQuakeSize;   // �a�_�j�p 
	DWORD      dWindSize;         // �����j�p  
	DWORD      dWindDir;          // ���V��V
}TPOS_EVENT_INITZONEWEATHER;
//-------------------------------------------------------------------------------
// GET Public Talk
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_GETPUBLICTALK
{
	DWORD	    	dwType; 
	DWORD			dwSendIndex;
	DWORD			dwTargetIndex;
	long			lDoing_kind; 
	char			cMsg[256];
}TPOS_EVENT_GETPUBLICTALK;
//-------------------------------------------------------------------------------
// Attack Switch
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_ATTACKSWITCH
{
	DWORD           dwIndex;
	DWORD           dwPk; 
	long	        lDoing_kind;
}TPOS_EVENT_ATTACKSWITCH;
//-------------------------------------------------------------------------------
// Bag Switch
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_BAGSWITCH
{	
	DWORD           dwBag; 
}TPOS_EVENT_BAGSWITCH;
//-------------------------------------------------------------------------------
// Change Mouse Skill
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_CHANGEMOUSESKILL
{	
	DWORD           dwLeftRight;      // ���k
	DWORD           dwSkill;          // �ޯ�  
}TPOS_EVENT_CHANGEMOUSESKILL;
//-------------------------------------------------------------------------------
// Hit Map
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_HITMAP
{	
	DWORD			dwLeftRight;	
	LONG			lX;
	LONG			lY;
	LONG			lZ;
}TPOS_EVENT_HITMAP;
//-------------------------------------------------------------------------------
// Hit NPC
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_HITNPC
{	
	DWORD			dwLeftRight;	
	DWORD			dwDestNPC;
}TPOS_EVENT_HITNPC;
//-------------------------------------------------------------------------------
// Hit ITEM
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_HITITEM
{	
	DWORD			dwLeftRight;	
	LONG			lX;
	LONG			lY;
	LONG			lZ;
}TPOS_EVENT_HITITEM;
//-------------------------------------------------------------------------------
// Update NPC Base Data
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_UPDATENPCBASEDATA
{	
    SLONG   update_type;    //UPDATE�ƾ�����(�O�q, ��ı, ���O, �B��)
    SLONG   update_value;   //UPDATE�ƾ�(>0��ܼW�[, <0��ܴ��)
}TPOS_EVENT_UPDATENPCBASEDATA;
//-------------------------------------------------------------------------------
// Set Upgrade NPC Base Data
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_SETNPCUPGRADEBASEDATA
{	
    SLONG   update_type;    //UPDATE�ƾ�����(�O�q, ��ı, ���O, �B��)
    SLONG   value;          //�����ƾ�
    SLONG   rest_point;     //�ѤU���ݩ��I	
	UHINT	att;			//�����O
	UHINT	defence;		//���m�O
	UHINT	max_hp;			//�ͩR�O�W��
	UHINT	hp;				//��e�ͩR�O
	UHINT	max_mp;			//���O�W��
	UHINT	mp;				//��e���O
}TPOS_EVENT_SETNPCUPGRADEBASEDATA;
//-------------------------------------------------------------------------------
// Request Change Zone Weather
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_REQUESTCHANGEWEATHER
{	
	DWORD      dType;      // ���w�n�U���ؤѮ𪺺��� 
	DWORD      dActive;    // �}�l,�M��,����
	DWORD      dSize;      // �j�p 
	DWORD      dWindSize;  // ���V�j�p 
	DWORD      dWindDir;   // ���V��V	
}TPOS_EVENT_REQUESTCHANGEWEATHER;
//-------------------------------------------------------------------------------
// Get Zone Now Weather
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_GETZONENOWWEATHER
{	
	DWORD      dWeatherType;      // �Ѯ𫬺A  
	DWORD      dRainActive;       // �O�_�U�B
	DWORD      dRainSize;         // �B���j�p
	DWORD      dSnowActive;       // �O�_�U��
	DWORD      dSnowSize;         // �����j�p
	DWORD      dCloudActive;      // �O�_����
	DWORD      dCloudSize;        // �����j�p
	DWORD      dThunderActive;    // �O�_���p  
	DWORD      dThunderSize;      // �p���j�p
	DWORD      dEarthQuakeActive; // �O�_�a�_
	DWORD      dEarthQuakeSize;   // �a�_�j�p 
	DWORD      dWindSize;         // �����j�p  
	DWORD      dWindDir;          // ���V��V	
}TPOS_EVENT_GETZONENOWWEATHER;
// ---------------------------------------------------------------------------
// SYNC Position Struct Define
// �P�B�y�Ю���  
// ---------------------------------------------------------------------------
typedef struct POS_SYNCMOVE
{ 
 long                         lX;
 long                         lY; 
}TPOS_SYNCMOVE;
// ---------------------------------------------------------------------------
// SYNC Sea Position Struct Define
// �P�B���W�y�Ю���  
// ---------------------------------------------------------------------------
typedef struct POS_SYNCSEAMOVE
{ 
 SLONG						  X;
 SLONG						  Y;	
 SLONG						  Z;	 
}TPOS_SYNCSEAMOVE;
// ---------------------------------------------------------------------------
// Get Change Doing
// ���o���ܪ�Doing����
// ---------------------------------------------------------------------------
typedef struct POS_EVENT_GETCHANGENPCDOING
{ 
	DWORD	Index;	
	SLONG	DoingKind;
	LONG	DoingStep;
	DWORD	d1;
	DWORD	d2;
	DWORD	d3;
	DWORD	d4;
	DWORD	d5;	
}TPOS_EVENT_GETCHANGENPCDOING;
// ---------------------------------------------------------------------------
// NPC Up Level
// ---------------------------------------------------------------------------
typedef struct POS_EVENT_NPCLEVELUP
{ 
	DWORD	Index;
    UHINT	Level;
    UHINT	MaxHp;
    UHINT	MaxMp;
    UHINT	AttribPoint;
    ULONG	Exp;
    ULONG	NextExp;
}TPOS_EVENT_NPCLEVELUP;
// ---------------------------------------------------------------------------
// Set NPC exp
// ---------------------------------------------------------------------------
typedef struct POS_EVENT_SETNPCEXP
{ 
	DWORD	Index;
	ULONG	Exp;
}TPOS_EVENT_SETNPCEXP;
//-------------------------------------------------------------------------------
// Request/Notify set hand quick skill
//-------------------------------------------------------------------------------
typedef	struct POS_EVENT_SETHANDQUICKSKILL 
{
	SLONG	Hand;
	SLONG	QuickIndex;
	SLONG	SkillNo;
}TPOS_EVENT_SETHANDQUICKSKILL;
//-------------------------------------------------------------------------------
// Request use hand quick skill
//-------------------------------------------------------------------------------
typedef	struct POS_EVENT_USEHANDQUICKSKILL 
{
	SLONG	QuickIndex;
}TPOS_EVENT_USEHANDQUICKSKILL;
//-------------------------------------------------------------------------------
// ���~������ Event Struct
//-------------------------------------------------------------------------------
typedef	struct POS_EVENT_REQUESTHITBAGITEM
{
	char		LR;
	UCHAR		BagIndex;	
}TPOS_EVENT_REQUESTHITBAGITEM;
//-------------------------------------------------------------------------------
typedef	struct POS_EVENT_REQUESTHITHEADITEM
{
	char		LR;
}TPOS_EVENT_REQUESTHITHEADITEM;
//-------------------------------------------------------------------------------
typedef	struct POS_EVENT_REQUESTHITNECKITEM
{
	char		LR;
}TPOS_EVENT_REQUESTHITNECKITEM;
//-------------------------------------------------------------------------------
typedef	struct POS_EVENT_REQUESTHITBODYITEM
{
	char		LR;
}TPOS_EVENT_REQUESTHITBODYITEM;
//-------------------------------------------------------------------------------
typedef	struct POS_EVENT_REQUESTHITWAISTITEM
{
	char		LR;
}TPOS_EVENT_REQUESTHITWAISTITEM;
//-------------------------------------------------------------------------------
typedef	struct POS_EVENT_REQUESTHITGLOVEITEM
{
	char		LR;
}TPOS_EVENT_REQUESTHITGLOVEITEM;
//-------------------------------------------------------------------------------
typedef	struct POS_EVENT_REQUESTHITWEAPONITEM
{
	char		LR;
}TPOS_EVENT_REQUESTHITWEAPONITEM;
//-------------------------------------------------------------------------------
typedef	struct POS_EVENT_REQUESTHITWRISTITEM
{
	char		LR;
}TPOS_EVENT_REQUESTHITWRISTITEM;
//-------------------------------------------------------------------------------
typedef	struct POS_EVENT_REQUESTHITFEETITEM
{
	char		LR;
}TPOS_EVENT_REQUESTHITFEETITEM;
//-------------------------------------------------------------------------------
typedef	struct POS_EVENT_REQUESTHITOTHERAITEM
{
	char		LR;
}TPOS_EVENT_REQUESTHITOTHERAITEM;
//-------------------------------------------------------------------------------
typedef	struct POS_EVENT_REQUESTHITOTHERBITEM
{
	char		LR;
}TPOS_EVENT_REQUESTHITOTHERBITEM;
//-------------------------------------------------------------------------------
typedef	struct POS_EVENT_REQUESTHITOTHERCITEM
{
	char		LR;
}TPOS_EVENT_REQUESTHITOTHERCITEM;
//-------------------------------------------------------------------------------
typedef	struct POS_EVENT_REQUESTHITSASHITEM
{
	char		LR;
	UCHAR		SashIndex;
}TPOS_EVENT_REQUESTHITSASHITEM;
//-------------------------------------------------------------------------------
typedef	struct POS_EVENT_REQUESTHITTRANSITEM
{
	char		LR;
	UCHAR		TransIndex;
}TPOS_EVENT_REQUESTHITTRANSITEM;
//-------------------------------------------------------------------------------
typedef	struct POS_EVENT_REQUESTHITTREASUREITEM
{
	char		LR;
}TPOS_EVENT_REQUESTHITTREASUREITEM;
//-------------------------------------------------------------------------------
typedef	struct POS_EVENT_REQUESTDROPITEM
{
	SLONG		X;
	SLONG		Y;
}TPOS_EVENT_REQUESTDROPITEM;
//-------------------------------------------------------------------------------
typedef	struct POS_EVENT_REQUESTHITMAPITEM
{
	char		LR;
	SLONG		X;
	SLONG		Y;
}TPOS_EVENT_REQUESTHITMAPITEM;
//-------------------------------------------------------------------------------
typedef	struct POS_EVENT_NOTIFYADDMAPITEM
{
	SLONG		X;
	SLONG		Y;
	TPOS_ITEM	Item;
}TPOS_EVENT_NOTIFYADDMAPITEM;
//-------------------------------------------------------------------------------
typedef	struct POS_EVENT_NOTIFYDELETEMAPITEM
{
	SLONG		X;
	SLONG		Y;
}TPOS_EVENT_NOTIFYDELETEMAPITEM;
//-------------------------------------------------------------------------------
typedef	struct POS_EVENT_NOTIFYSETONMOUSEITEM
{
	TPOS_ITEM	Item;
}TPOS_EVENT_NOTIFYSETONMOUSEITEM;
//-------------------------------------------------------------------------------
typedef	struct POS_EVENT_NOTIFYSETBAGITEM
{
	UCHAR		BagIndex;
	TPOS_ITEM	Item;
}TPOS_EVENT_NOTIFYSETBAGITEM;
//-------------------------------------------------------------------------------
typedef	struct POS_EVENT_NOTIFYSETHEADITEM
{
	TPOS_ITEM	Item;
}TPOS_EVENT_NOTIFYSETHEADITEM;
//-------------------------------------------------------------------------------
typedef	struct POS_EVENT_NOTIFYSETNECKITEM
{
	TPOS_ITEM	Item;
}TPOS_EVENT_NOTIFYSETNECKITEM;
//-------------------------------------------------------------------------------
typedef	struct POS_EVENT_NOTIFYSETBODYITEM
{
	TPOS_ITEM	Item;
}TPOS_EVENT_NOTIFYSETBODYITEM;
//-------------------------------------------------------------------------------
typedef	struct POS_EVENT_NOTIFYSETWAISTITEM
{
	TPOS_ITEM	Item;
}TPOS_EVENT_NOTIFYSETWAISTITEM;
//-------------------------------------------------------------------------------
typedef	struct POS_EVENT_NOTIFYSETGLOVEITEM
{
	TPOS_ITEM	Item;
}TPOS_EVENT_NOTIFYSETGLOVEITEM;
//-------------------------------------------------------------------------------
typedef	struct POS_EVENT_NOTIFYSETWEAPONITEM
{
	TPOS_ITEM	Item;
}TPOS_EVENT_NOTIFYSETWEAPONITEM;
//-------------------------------------------------------------------------------
typedef	struct POS_EVENT_NOTIFYSETWRISTITEM
{
	TPOS_ITEM	Item;
}TPOS_EVENT_NOTIFYSETWRISTITEM;
//-------------------------------------------------------------------------------
typedef	struct POS_EVENT_NOTIFYSETFEETITEM
{
	TPOS_ITEM	Item;
}TPOS_EVENT_NOTIFYSETFEETITEM;
//-------------------------------------------------------------------------------
typedef	struct POS_EVENT_NOTIFYSETOTHERAITEM
{
	TPOS_ITEM	Item;
}TPOS_EVENT_NOTIFYSETOTHERAITEM;
//-------------------------------------------------------------------------------
typedef	struct POS_EVENT_NOTIFYSETOTHERBITEM
{
	TPOS_ITEM	Item;
}TPOS_EVENT_NOTIFYSETOTHERBITEM;
//-------------------------------------------------------------------------------
typedef	struct POS_EVENT_NOTIFYSETOTHERCITEM
{
	TPOS_ITEM	Item;
}TPOS_EVENT_NOTIFYSETOTHERCITEM;
//-------------------------------------------------------------------------------
typedef	struct POS_EVENT_NOTIFYSETSASHITEM
{
	UCHAR		SashIndex;
	TPOS_ITEM	Item;
}TPOS_EVENT_NOTIFYSETSASHITEM;
//-------------------------------------------------------------------------------
typedef	struct POS_EVENT_NOTIFYSETTRANSITEM
{
	UCHAR		TransIndex;
	TPOS_ITEM	Item;
}TPOS_EVENT_NOTIFYSETTRANSITEM;
//-------------------------------------------------------------------------------
typedef	struct POS_EVENT_NOTIFYSETTREASUREITEM
{
	TPOS_ITEM	Item;
}TPOS_EVENT_NOTIFYSETTREASUREITEM;
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_NOTIFYNPCTALK
{
	SLONG	TargetNPCIndex;
	char	Msg[5][48];
	SLONG	NextProc;
}TPOS_EVENT_NOTIFYNPCTALK;
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_NOTIFYNPCCHOICE
{
	SLONG	TargetNPCIndex;
	SLONG	NextProc[5];
	char	Option[5][48];
	char	Title[48];
}TPOS_EVENT_NOTIFYNPCCHOICE;
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_NOTIFYENDDIALOG
{
	SLONG	TargetNPCIndex;	
}TPOS_EVENT_NOTIFYENDDIALOG;
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_REQUESTNPCPROC
{
	SLONG	TargetNPCIndex;	
	SLONG	NextProc;
}TPOS_EVENT_REQUESTNPCPROC;
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_NOTIFYNPCONPAUSE
{
	SLONG	OnPauseNpcIndex;
}TPOS_EVENT_NOTIFYNPCONPAUSE;
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_NOTIFYNPCNOPAUSE
{
	SLONG	NoPauseNpcIndex;
}TPOS_EVENT_NOTIFYNPCNOPAUSE;
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_REQUESTCHANGEDIR
{
	char	Dir;
}TPOS_EVENT_REQUESTCHANGEDIR;
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_CHARACTERSELECTED
{
	ULONG	QQID;	
}TPOS_EVENT_CHARACTERSELECTED;
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_QQPLAYERLOGIN
{
	ULONG	QQID;	
}TPOS_EVENT_QQPLAYERLOGIN;
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_QQPLAYERLOGOUT
{
	ULONG	QQID;	
}TPOS_EVENT_QQPLAYERLOGOUT;
//-------------------------------------------------------------------------------
// QQ Get MyData Struct
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_QQGETMYDATA
{
	ULONG			ID;						// QQ �ߤ@	ID ��
	ULONG			Config;					// �����]�w	
	CHAR			CharacterName[32];		// ����W��
	CHAR			GuildName[32];			// �u�|�W��
	CHAR			State;					// ���A	
}TPOS_EVENT_QQGETMYDATA;
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_QQGETFRIENDLIST
{	
	ULONG			BookMark;
	TPOS_QQ_FRIEND	FriendList[128];	
}TPOS_EVENT_QQGETFRIENDLIST;
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_QQGETGUILDFRIENDLIST
{
	TPOS_QQ_FRIEND	GuildFriendList[128];	
}TPOS_EVENT_QQGETGUILDFRIENDLIST;
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_QQREQUESTSETMYSTATE
{
	ULONG			ID;
	CHAR			State;
}TPOS_EVENT_QQREQUESTSETMYSTATE;
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_QQREQUESTQUERYONLINELIST
{
	DWORD			BookMark;				// Server�ݬd�ߪ�BookMark
	DWORD			ZoneIndex;				// Server�ݬd�ߪ�ZoneIndex
	ULONG			RequestID;				// �n�D��QQID	
}TPOS_EVENT_QQREQUESTQUERYONLINELIST;
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_QQGETQUERYONLINELIST
{
	DWORD			BookMark;				// Server�ݬd�ߪ�BookMark
	DWORD			ZoneIndex;				// Server�ݬd�ߪ�ZoneIndex	
	ULONG			RequestID;				// �n�D��QQID
	TPOS_QQ_ADDLIST QQAddList[100];
}TPOS_EVENT_QQGETQUERYONLINELIST;
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_QQREQUESTQUERYSOMEONE
{
	ULONG			RequestID;
	ULONG			TargetID;	
}TPOS_EVENT_QQREQUESTQUERYSOMEONE;
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_QQGETQUERYSOMEONE
{
	ULONG			RequestID;				// �n�D�d�ߪ����aQQID
	ULONG			ID;						// �ߤ@��ID
	CHAR			MainName[32];			// ����W��
	CHAR			NickName[32];			// ����ʺ�
	CHAR			Country;				// ��a�W��
	CHAR			GuildName[32];			// �u�|�W��
	ULONG			Money;					// ����
	UINT			Level;					// ����
	ULONG			PK;						// PK �ƶq
	CHAR			Spouse[32];				// �t���W��
	LONG			Prestige;				// �n��				
	CHAR			Career;					// ¾�~
}TPOS_EVENT_QQGETQUERYSOMEONE;
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_QQREQUESTADDSOMEONE
{
	ULONG			RequestID;
	ULONG			TargetID;
	UCHAR			Relation;
}TPOS_EVENT_QQREQUESTADDSOMEONE;
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_QQGETADDSOMEONE
{	
	DWORD			Index;					// �ǿ骺����
	ULONG			RequestID;				// �n�D�C�� QQID
	ULONG			TargetID;				// �ߤ@��ID
	CHAR			MainName[32];			// �n�ͦW��
	UCHAR			Relation;				// �n�a 0-�n, 1-�a 
	CHAR			Career;					// ¾�~
	CHAR			State;					// ���A	
}TPOS_EVENT_QQGETADDSOMEONE;
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_QQREQUESTSENDMSGTOONE
{	
	ULONG			SendID;					// �o�e����ID
	ULONG			RecvID;					// ��������ID
	CHAR			Msg[200];	
}TPOS_EVENT_QQREQUESTSENDMSGTOONE;
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_QQREQUESTSENDMSGTOSOME
{	
	ULONG			SendID;					// �o�e����ID
	ULONG			RecvID[50];				// ��������ID
	CHAR			Msg[200];	
}TPOS_EVENT_QQREQUESTSENDMSGTOSOME;
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_QQGETMSG
{	
	ULONG			SendID;					// �o�e����ID
	ULONG			RecvID;					// ��������ID
	CHAR			Msg[200];	
}TPOS_EVENT_QQGETMSG;
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_QQREQUESTPLAYERCOUNT
{
	ULONG			RequestID;
}TPOS_EVENT_QQREQUESTPLAYERCOUNT;
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_QQGETPLAYERCOUNT
{
	ULONG			RequestID;
	ULONG			PlayerCount;	
}TPOS_EVENT_QQGETPLAYERCOUNT;
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_QQGETOTHERSTATE
{
	ULONG			ID;
	char			State;
}TPOS_EVENT_QQGETOTHERSTATE;
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_QQREQUESTDELFRIEND
{
	ULONG			RequestID;
	ULONG			TargetID;	
}TPOS_EVENT_QQREQUESTDELFRIEND;
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_QQGETDELFRIEND
{
	ULONG			RequestID;
	ULONG			TargetID;	
}TPOS_EVENT_QQGETDELFRIEND;
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_QQREQUESTDELGUILDFRIEND
{
	ULONG			RequestID;
	ULONG			TargetID;	
}TPOS_EVENT_QQREQUESTDELGUILDFRIEND;
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_QQGETDELGUILDFRIEND
{	
	ULONG			RequestID;
	ULONG			TargetID;	
}TPOS_EVENT_QQGETDELGUILDFRIEND;
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_QQREQUESTTRANSFERITEM
{
	ULONG			RequestID;
	ULONG			TargetID;	
}TPOS_EVENT_QQREQUESTTRANSFERITEM;
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_QQREQUESTTRANSFERITEMFROMWORLD
{
	ULONG			RequestID;
	ULONG			TargetID;	
	TPOS_ITEM		TransItem[3];
}TPOS_EVENT_QQREQUESTTRANSFERITEMFROMWORLD;
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_QQGETTRANSFERITEM
{
	ULONG			RequestID;
	ULONG			TargetID;	
}TPOS_EVENT_QQGETTRANSFERITEM;
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_QQTRANSFERITEMOKFROMWORLD
{
	ULONG			RequestID;
	ULONG			TargetID;	
}TPOS_EVENT_QQTRANSFERITEMOKFROMWORLD;
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_QQTRANSFERITEMFAILFROMWORLD
{
	ULONG			RequestID;	
	ULONG			TargetID;	
}TPOS_EVENT_QQTRANSFERITEMFAILFROMWORLD;
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_QQTRANSFERITEMOK
{
	ULONG			RequestID;
	ULONG			TargetID;
}TPOS_EVENT_QQTRANSFERITEMOK;
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_QQTRANSFERITEMFAIL
{
	ULONG			RequestID;	
	ULONG			TargetID;	
}TPOS_EVENT_QQTRANSFERITEMFAIL;
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_NOTIFYBREAKMAGIC
{
	SLONG			npc_no;
	SLONG			dest_x;
	SLONG			dest_y;
	SLONG			magic_index;
}TPOS_EVENT_NOTIFYBREAKMAGIC;
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_ZONEREQUESTITEMID
{
	DWORD			EventType;
	ULONG			Npc_No;
	TPOS_ITEM		Item;
}TPOS_EVENT_ZONEREQUESTITEMID;
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_ZONEGETITEMID
{
	DWORD			EventType;
	ULONG			Npc_No;
	TPOS_ITEM		Item;		
}TPOS_EVENT_ZONEGETITEMID;
//-------------------------------------------------------------------------------
typedef	struct POS_EVENT_SETMAINNAMECOLOR
{
	ULONG			Npc_No;
	char			MainNameColor;
}TPOS_EVENT_SETMAINNAMECOLOR;
//-------------------------------------------------------------------------------
typedef	struct POS_EVENT_SETGOODEVIL
{
	SLONG			GoodEvil;
	ULONG			PkCount;	
	ULONG			PkedCount;
}TPOS_EVENT_SETGOODEVIL;
//-------------------------------------------------------------------------------
typedef	struct POS_EVENT_SETNPCMOVESPEED
{
	ULONG			Npc_No;
	ULONG			MoveSpeed;
}TPOS_EVENT_SETNPCMOVESPEED;
//-------------------------------------------------------------------------------
typedef	struct POS_EVENT_SETMONEY
{	
	ULONG			Money;
}TPOS_EVENT_SETMONEY;
//-------------------------------------------------------------------------------
typedef	struct POS_EVENT_NOTIFYAFTERCHANGEEQUIP
{	
	UHINT	att;				//�����O
	UHINT	defence;			//���m�O
	UHINT	resist;				//��ܤO
	UHINT	max_hp;				//�ͩR�O�W��
	UHINT	hp;					//��e�ͩR�O
	UHINT	max_mp;				//���O�W��
	UHINT	mp;					//��e���O
}TPOS_EVENT_NOTIFYAFTERCHANGEEQUIP;
//-------------------------------------------------------------------------------
typedef	struct POS_EVENT_SETNPCPOSITION
{
	SLONG	x;
	SLONG	y;
	SLONG	z;
}TPOS_EVENT_SETNPCPOSITION;
//-------------------------------------------------------------------------------
// TOP SECRET MSG
//-------------------------------------------------------------------------------
typedef	struct POS_GOD_REQUESTJUMPTO
{	
	SLONG	X;
	SLONG	Y;
	SLONG	Z;
}TPOS_GOD_REQUESTJUMPTO;
//-------------------------------------------------------------------------------
typedef	struct POS_GOD_REQUESTITEM
{
	UHINT	BaseID;
}TPOS_GOD_REQUESTITEM;
//-------------------------------------------------------------------------------
typedef	struct POS_GOD_REQUESTMONEY
{
	ULONG	Money;
}TPOS_GOD_REQUESTMONEY;
//-------------------------------------------------------------------------------
typedef	struct POS_GOD_REQUESTEXP
{
	ULONG	Exp;
}TPOS_GOD_REQUESTEXP;
//-------------------------------------------------------------------------------
typedef	struct POS_GOD_REQUESTMOVEFAST
{
	ULONG	MoveSpeed;
}TPOS_GOD_REQUESTMOVEFAST;
//-------------------------------------------------------------------------------
typedef	struct POS_GOD_REQUESTCHANGEZONE
{
	CHAR	ZoneName[32];
	SLONG	X;
	SLONG	Y;
	SLONG	Z;
}TPOS_GOD_REQUESTCHANGEZONE;
//-------------------------------------------------------------------------------
typedef	struct POS_GOD_REQUESTGETMAP
{
	UHINT	Index;
	UHINT	PieceIndex;
}TPOS_GOD_REQUESTGETMAP;
//-------------------------------------------------------------------------------
typedef	struct POS_GOD_REQUESTPROPERTYPOINT
{
	SLONG	Point;
}TPOS_GOD_REQUESTPROPERTYPOINT;
//-------------------------------------------------------------------------------
typedef	struct POS_GOD_NOTIFYPROPERTYPOINT
{
	SLONG	Point;
}TPOS_GOD_NOTIFYPROPERTYPOINT;
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_NOTIFYSTOREDATA
{
	TPOS_ITEM	Item[36];	
	ULONG		Money[36];
	ULONG		Amount[36];
	SLONG		NextProc;
	SLONG		NpcNo;
	SLONG		ZoneStoreIndex;
}TPOS_EVENT_NOTIFYSTOREDATA;
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_REFRESHSTOREDATA
{
	TPOS_ITEM	Item[36];	
	ULONG		Money[36];
	ULONG		Amount[36];		
}TPOS_EVENT_REFRESHSTOREDATA;
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_REQUESTBUYITEM
{
	ULONG		ItemIndex;
	SLONG		ZoneStoreIndex;
}TPOS_EVENT_REQUESTBUYITEM;
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_REQUESTSELLITEM
{	
	SLONG		ZoneStoreIndex;
}TPOS_EVENT_REQUESTSELLITEM;
//-------------------------------------------------------------------------------
typedef	struct POS_EVENT_SETNPCSKILL
{
	ULONG		NpcNo;
	ULONG		SkillIndex;
	SLONG		SkillNo;
}TPOS_EVENT_SETNPCSKILL;
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_REQUESTJOINTEAM
{
	char		LeaderMainName[32];
	char		LeaderZoneName[32];
}TPOS_EVENT_REQUESTJOINTEAM;
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_REQUESTAGREEJOINTEAM
{		
	char		MemberMainName[32];
	char		MemberZoneName[32];
}TPOS_EVENT_REQUESTAGREEJOINTEAM;
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_REQUESTEXITTEAM
{
	char		LeaderMainName[32];
	char		LeaderZoneName[32];
}TPOS_EVENT_REQUESTEXITTEAM;
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_REQUESTKICKMEMBER
{	
	char		MemberMainName[32];
	char		MemberZoneName[32];
}TPOS_EVENT_REQUESTKICKMEMBER;
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_NOTIFYJOINTEAMFULL
{
	char		LeaderMainName[32];	
	char		LeaderZoneName[32];
}TPOS_EVENT_NOTIFYJOINTEAMFULL;
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_NOTIFYSOMEONEWANTJOINTEAM
{
	char		LeaderMainName[32];
	char		LeaderZoneName[32];
	char		MemberMainName[32];
	char		MemberZoneName[32];
}TPOS_EVENT_NOTIFYSOMEONEWANTJOINTEAM;
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_NOTIFYSOMEONEJOINTEAM
{	
	CHAR	MainName[32];	//�W��
	UHINT	Hp;				//��eHP
	UHINT	MaxHp;			//��eHP�W��
	UHINT	Level;			//��e����
	CHAR	Eyes;			//�����Ϲ�����
	CHAR	Mouth;			//�f�Ϲ�����
	CHAR	Career;			//�H��¾�~
	CHAR	Sex;			//�H���ʧO
	CHAR	ZoneName[32];	//�Ҧb�ϰ�
}TPOS_EVENT_NOTIFYSOMEONEJOINTEAM;
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_NOTIFYSOMEONEEXITTEAM
{	
	char		MemberMainName[32];
	char		MemberZoneName[32];
}TPOS_EVENT_NOTIFYSOMEONEEXITTEAM;
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_NOTIFYTEAMMEMBERINFO
{	
	TPOS_EVENT_NOTIFYSOMEONEJOINTEAM	TeamMemberInfo[MAX_CHARACTER_TEAM_MEMBERS];	
}TPOS_EVENT_NOTIFYTEAMMEMBERINFO;
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_NOTIFYMAKETEAM
{
	TPOS_EVENT_NOTIFYSOMEONEJOINTEAM	TeamMemberInfo[MAX_CHARACTER_TEAM_MEMBERS];	
}TPOS_EVENT_NOTIFYMAKETEAM;
//-------------------------------------------------------------------------------
typedef	struct POS_EVENT_NOTIFYCHANGELEADER
{
	TPOS_EVENT_NOTIFYSOMEONEJOINTEAM	TeamMemberInfo[MAX_CHARACTER_TEAM_MEMBERS];	
}TPOS_EVENT_NOTIFYCHANGELEADER;
//-------------------------------------------------------------------------------
typedef	struct POS_EVENT_NOTIFYRELOADTEAMINFO
{
	TPOS_EVENT_NOTIFYSOMEONEJOINTEAM	TeamMemberInfo[MAX_CHARACTER_TEAM_MEMBERS];	
}TPOS_EVENT_NOTIFYRELOADTEAMINFO;
//-------------------------------------------------------------------------------
typedef	struct	POS_EVENT_ZONEREQUESTJOINTEAM
{
	char		LeaderMainName[32];
	char		LeaderZoneName[32];
	char		MemberMainName[32];
	char		MemberZoneName[32];
}TPOS_EVENT_ZONEREQUESTJOINTEAM;
//-------------------------------------------------------------------------------
typedef	struct	POS_EVENT_ZONEREQUESTAGREEJOINTEAM
{
	char		LeaderMainName[32];
	char		LeaderZoneName[32];
	char		MemberMainName[32];
	char		MemberZoneName[32];
}TPOS_EVENT_ZONEREQUESTAGREEJOINTEAM;
//-------------------------------------------------------------------------------
typedef	struct	POS_EVENT_ZONEREQUESTEXITTEAM
{
	char		LeaderMainName[32];
	char		LeaderZoneName[32];
	char		MemberMainName[32];
	char		MemberZoneName[32];
}TPOS_EVENT_ZONEREQUESTEXITTEAM;
//-------------------------------------------------------------------------------
typedef	struct	POS_EVENT_ZONEREQUESTKICKTEAMMEMBER
{
	char		LeaderMainName[32];
	char		LeaderZoneName[32];
	char		MemberMainName[32];
	char		MemberZoneName[32];
}TPOS_EVENT_ZONEREQUESTKICKTEAMMEMBER;
//-------------------------------------------------------------------------------
typedef	struct	POS_EVENT_ZONENOTIFYSOMEONEWANTJOINTEAM
{
	char		MemberMainName[32];
	char		MemberZoneName[32];
}TPOS_EVENT_ZONENOTIFYSOMEONEWANTJOINTEAM;
//-------------------------------------------------------------------------------
typedef	struct	POS_EVENT_ZONENOTIFYJOINTEAMFULL
{	
	char		MemberMainName[32];
	char		MemberZoneName[32];
}TPOS_EVENT_ZONENOTIFYJOINTEAMFULL;
//-------------------------------------------------------------------------------
typedef	struct	POS_EVENT_ZONENOTIFYSOMEONEJOINTEAM
{
	char		MemberMainName[32];		
	char		ZoneName[32];
	CHAR		Eyes;
	CHAR		Mouth;	
	CHAR		Sex;
	CHAR		Career;
	UHINT		Hp;
	UHINT		MaxHp;
	UHINT		Level;
}TPOS_EVENT_ZONENOTIFYSOMEONEJOINTEAM;
//-------------------------------------------------------------------------------
typedef	struct	POS_EVENT_ZONENOTIFYSOMEONEEXITTEAM
{
	char		LeaderMainName[32];
	char		LeaderZoneName[32];
	char		MemberMainName[32];
	char		MemberZoneName[32];
}TPOS_EVENT_ZONENOTIFYSOMEONEEXITTEAM;
//-------------------------------------------------------------------------------
typedef	struct	POS_EVENT_ZONENOTIFYKICKEDFROMTEAM
{
	char		LeaderMainName[32];
	char		LeaderZoneName[32];
	char		MemberMainName[32];
	char		MemberZoneName[32];
}TPOS_EVENT_ZONENOTIFYKICKEDFROMTEAM;
//-------------------------------------------------------------------------------
typedef	struct	POS_EVENT_ZONENOTIFYTEAMMEMBERINFO
{	
	TPOS_EVENT_ZONENOTIFYSOMEONEJOINTEAM	TeamMemberInfo[MAX_CHARACTER_TEAM_MEMBERS];	
}TPOS_EVENT_ZONENOTIFYTEAMMEMBERINFO;
//-------------------------------------------------------------------------------
typedef	struct	POS_EVENT_ZONENOTIFYTEAMMEMBERCHANGEZONE
{
	char		LeaderMainName[32];
	char		LeaderZoneName[32];
	char		MemberMainName[32];
	char		MemberZoneName[32];
}TPOS_EVENT_ZONENOTIFYTEAMMEMBERCHANGEZONE;
//-------------------------------------------------------------------------------
typedef	struct POS_EVENT_NOTIFYBANKMONEYITEM
{
	SLONG		NextProc;
	SLONG		NpcNo;
	ULONG		Money;
	TPOS_ITEM	Item[MAX_CHARACTER_BANK_ITEMS];
}TPOS_EVENT_NOTIFYBANKMONEYITEM;
//-------------------------------------------------------------------------------
typedef	struct POS_EVENT_REQUESTSAVEMONEY
{	
	ULONG		Money;
}TPOS_EVENT_REQUESTSAVEMONEY;
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_REQUESTLOADMONEY
{
	ULONG		Money;	
}TPOS_EVENT_REQUESTLOADMONEY;
//-------------------------------------------------------------------------------
typedef	struct POS_EVENT_REQUESTHITBANKITEM
{
	UHINT		Index;
	TPOS_ITEM	Item;
}TPOS_EVENT_REQUESTHITBANKITEM;
//-------------------------------------------------------------------------------
typedef	struct POS_EVENT_NOTIFYSETBANKITEM
{
	UHINT		Index;
	TPOS_ITEM	Item;
}TPOS_EVENT_NOTIFYSETBANKITEM;
//-------------------------------------------------------------------------------
typedef	struct POS_EVENT_SETBANKMONEY
{	
	ULONG			Money;
}TPOS_EVENT_SETBANKMONEY;
//-------------------------------------------------------------------------------
typedef	struct POS_EVENT_NOTIFYZONEITEMLIST
{
	SLONG		X[500];
	SLONG		Y[500];
	TPOS_ITEM	Item[500];
}TPOS_EVENT_NOTIFYZONEITEMLIST;
//-------------------------------------------------------------------------------
typedef	struct POS_NOTIFYNPCQUESTLIST
{
	UHINT	QuestID;			//���� ID
	CHAR	TargetNpc[32];		//�ؼФH
	ULONG	Deadline;			//���ȧ������̲״���
	UCHR	PayType;			//�������Ȫ����S���O (QUEST_PAY_$$)
	ULONG	PayData;			//�������Ȫ����S�ƭ� (�i�H�O�n��Prestidge, ����Money �Ϊ̪��~ItemBaseID )
	UCHR	PunishType;			//���������Ȫ��g�@���O
	ULONG	PunishData;			//���������Ȫ��g�@�ƭ�
	CHAR	Memo[64];			//���Ȼ���
	UHINT	RequestLevel;		//�n�D����
	CHAR	RequestCareer;		//�n�D¾�~
	CHAR	RequestCareerLevel;	//�n�D¾��
	SLONG	RequestPrestige;	//�n�D�n��
}TPOS_NOTIFYNPCQUESTLIST;
//-------------------------------------------------------------------------------
typedef	struct POS_EVENT_NOTIFYNPCQUESTLIST
{
	TPOS_NOTIFYNPCQUESTLIST		QuestList[20];
}TPOS_EVENT_NOTIFYNPCQUESTLIST;
//-------------------------------------------------------------------------------
typedef	struct POS_NOTIFYPLAYERQUESTLIST
{
	CHAR	TargetNpc[32];		//�ؼФH
	ULONG	Deadline;			//���ȧ������̲״���
	CHAR	Memo[64];			//���Ȼ���
}TPOS_NOTIFYPLAYERQUESTLIST;
//-------------------------------------------------------------------------------
typedef	struct POS_EVENT_NOTIFYPLAYERQUESTLIST
{
	TPOS_NOTIFYPLAYERQUESTLIST	QuestList[10];
}TPOS_EVENT_NOTIFYPLAYERQUESTLIST;
//-------------------------------------------------------------------------------
typedef	struct POS_EVENT_REQUESTDOONEQUEST
{
	UHINT	QuestID;
}TPOS_EVENT_REQUESTDOONEQUEST;
//-------------------------------------------------------------------------------
typedef	struct POS_EVENT_NOTIFYCOMPELETEQUEST
{
	UHINT	MyQuestIndex;
}TPOS_EVENT_NOTIFYCOMPELETEQUEST;
//-------------------------------------------------------------------------------
typedef	struct POS_EVENT_NOTIFYNPCAIBLOCK
{
	SLONG	Index;	
	UHINT	AIBlock;	
	SLONG	DestNpcNo;
	SLONG	X;
	SLONG	Y;
	SLONG	Z;
	UHINT	SkillNo;	
}TPOS_EVENT_NOTIFYNPCAIBLOCK;
//-------------------------------------------------------------------------------
typedef	struct POS_EVENT_NOTIFYCREATEMAGICAREA
{
	CHAR	Type;	
	CHAR	Dir;
	SLONG	X;			//	�y��
	SLONG	Y;
	SLONG	NpcNo;	
	UHINT	MagicNo;	
}TPOS_EVENT_NOTIFYCREATEMAGICAREA;
//-------------------------------------------------------------------------------
typedef	struct POS_EVENT_REQUESTSEPARATEMAP
{
	SLONG	BagIndex;
}TPOS_EVENT_REQUESTSEPARATEMAP;
//-------------------------------------------------------------------------------
typedef	struct POS_EVENT_NOTIFYMAPINFO
{
	UHINT	BagIndex;				// �]�]���Ů� (255 �� TreasureMapItem)
	SLONG	MapLeftUpX;				// �j�a�ϥ��W�����w��y��	
	SLONG	MapLeftUpY;				// �j�a�ϥ��W�����w��y��		
	char	Memo[256];				// ����
	SLONG	RedPointX;				// ���_�ϤW�����I���y��
	SLONG	RedPointY;				// ���_�ϤW�����I���y��		
}TPOS_EVENT_NOTIFYMAPINFO;
//-------------------------------------------------------------------------------
#endif//NETGE_EVENT_STRUCT_DEF_H
