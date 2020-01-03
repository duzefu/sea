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
	char		cId[32];                // 帳號
	char		cPw[32];                // 密碼
	char		cName[32];				// 真實姓名
	DWORD		dwSex;					// 性別
	char		cBirthday[8];			// 生日
	char		cCountry[16];			// 國家
	char		cCity[16];              // 城市
	char		cAddress[52];			// 住址
	char		cPhone[16];		    	// 白天電話 
	DWORD		dwJob;				    // 職業
	DWORD		dwNetStyle;				// 上網方式
	char		cEmail[40];				// 電子郵件 
	DWORD		dwPayType;              // 付款方式
}TPOS_EVENT_REGISTERACCOUNT;
//-------------------------------------------------------------------------------
// Change Account Profile Struct
//-------------------------------------------------------------------------------
typedef	struct POS_EVENT_CHANGEPROFILE
{		
	char		cName[32];				// 真實姓名
	DWORD		dwSex;					// 性別
	char		cBirthday[8];			// 生日
	char		cCountry[16];			// 國家
	char		cCity[16];              // 城市
	char		cAddress[52];			// 住址
	char		cPhone[16];		    	// 白天電話 
	DWORD		dwJob;				    // 職業
	DWORD		dwNetStyle;				// 上網方式
	char		cEmail[40];				// 電子郵件 
	DWORD		dwPayType;              // 付款方式
}TPOS_EVENT_CHANGEPROFILE;
//-------------------------------------------------------------------------------
// Register Account Check ID Struct
//-------------------------------------------------------------------------------
typedef	struct POS_EVENT_REGISTERACCOUNTCHECK
{
	char		cId[32];                // 帳號	
	char		cPw[32];                // 密碼
}TPOS_EVENT_REGISTERACCOUNTCHECK;
//-------------------------------------------------------------------------------
// Change Account Password Struct
//-------------------------------------------------------------------------------
typedef	struct POS_EVENT_CHANGEPASSWORD
{	
	char		cPw[32];                // 密碼
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
	SLONG			slFileIndex;	//角色影像文件索引
	CHAR			cSex;			//性別
	CHAR			cCareer;		//職業
	CHAR			cColor;			//顏色
	CHAR			cEyes;			//眼睛
	CHAR			cMouth;			//嘴
	CHAR			cCountry;		//所屬國家
	UINT			iStr;			//力量
	UINT			iIns;			//直覺
	UINT			iWis;			//智力
	UINT			iLucky;			//運氣
	UINT			iHp;			//生命力
	UINT			iMp;			//法力
	UINT			iMspeed;		//移動速度
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
	char	cMainName[32];				//名稱
	char	cNickName[32];				//暱稱
	char	cCareer;					//職業
	char	cCountry;					//國家
	char	cSex;						//性別
	UHINT	uhiLevel;					//等級
	CHAR	cNobility[16];				//爵位
	CHAR	cZone[32];					//區域
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
	DWORD	dwCharacterDefaultIndex;	//所選的職業角色
	DWORD	dwIndex;					//此帳號的第幾個角色	
	char	cMainName[32];				//名稱
	char	cNickName[32];				//暱稱
	CHAR	Color;						//顏色
	CHAR	Eyes;						//眼睛
	CHAR	Mouth;						//嘴
	CHAR	Country;					//所屬國家
	ULONG	PartRGB[7];					//各部位顏色
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
	DWORD	dwIndex;			//索引
	char	cZone[32];			//區域名稱
	char	cMapName[32];		//地圖名稱
	char	cAddr[16];			//IP地址
	DWORD	dwPort;				//Port
	DWORD	dwType;				//區域類型
	DWORD	dwPlayerCount;		//人數
}TPOS_EVENT_GETZONEINFO;
//-------------------------------------------------------------------------------
// Zone Server Login
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_ZONELOGIN
{
	char	cZone[32];			//區域名稱	
}TPOS_EVENT_ZONELOGIN;
//-------------------------------------------------------------------------------
// Player Join
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_PLAYERJOIN
{
	int		iIndex;
	char	cMainName[32];
	char	MainNameColor;
	SLONG	slFileIndex;	//角色影像文件索引
	UINT	iHp;			//生命力
	UINT	iMaxHp;
	UINT	iMp;			//法力
	UINT	iMaxMp;
	UINT	iLevel;			
	UINT	iMspeed;		//移動速度
	CHAR	cColor;			//顏色	
	LONG	lX;
	LONG	lY;
	LONG	lZ;
	CHAR	cDir;
	UHINT	iSightRange;
	SLONG	slSailSize;
	SLONG	slWeight;
	SLONG	slTurn;
	SLONG	slDoingKind;	//當前DoingKind
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
	SLONG	FileIndex;			//人物影響文件索引	
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
	UHINT	FinalStr;			//初始化時設定的力量值	
	//Ins
	UHINT	FinalIns;			//初始化時設定的直覺值	
	//Wit
	UHINT	FinalWit;			//初始化時設定的智慧值	
	//Lucky
	UHINT	FinalLucky;			//初始化時設定的幸運值	
	//Attack
	UHINT	SightRange;			//視野範圍	
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
	TPOS_ITEM	EquHead;			//頭部
	TPOS_ITEM	EquNeck;			//頸部
	TPOS_ITEM	EquBody;			//身體
	TPOS_ITEM	EquWaist;			//腰部
	TPOS_ITEM	EquGlove;			//手套
	TPOS_ITEM	EquWeapon;			//武器
	TPOS_ITEM	EquWrist;			//手環
	TPOS_ITEM	EquFeet;			//腳部
	TPOS_ITEM	EquOtherA;			//其他A
	TPOS_ITEM	EquOtherB;			//其他B
	TPOS_ITEM	EquOtherC;			//其他C
	//Body Item
	TPOS_ITEM	BagItem[MAX_CHARACTER_BAG_ITEMS];		//背包內物品
	TPOS_ITEM	SashItem[MAX_CHARACTER_SASH_ITEMS];		//腰包內物品
	TPOS_ITEM	TransItem[MAX_CHARACTER_TRANS_ITEMS];	//QQ傳送欄物品
	TPOS_ITEM	OnMouseItem;		//在滑鼠上的物品
	TPOS_ITEM	TreasureItem;		//藏寶圖物品
	ULONG	Money;				//身上的金錢
	//Society
	CHAR	Sex;				//性別
	CHAR	Country;			//國家
	CHAR	Guild[32];			//工會
	CHAR	Spouse[32];			//配偶
	CHAR	Career;				//職業
	UCHR	CareerLevel;		//職業等級
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
	ULONG	PartRGB[7];
	ULONG	NameColorTicks;		//名字顏色的時間
	ULONG	TotalOnlineTicks;	//總在線時間	
	//Doing
	SLONG	DoingKind;			//事務類型
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
	SLONG	slFileIndex;	//角色影像文件索引
	UINT	iHp;			//生命力
	UINT	iMp;			//法力
	UINT	iMspeed;		//移動速度
	CHAR	cColor;			//顏色
	CHAR	cEyes;			//眼睛
	CHAR	cMouth;			//嘴
	LONG	lX;
	LONG	lY;
	LONG	lZ;
	SLONG	slDoingKind;	//當前DoingKind
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
	SHINT	FnSkillNo[MAX_CHARACTER_FN_SKILLS];		//按鍵F1~F8對應技能編號
	CHAR	FnSkillHand[MAX_CHARACTER_FN_SKILLS];	//按鍵F1~F8對應技能設置在哪只手
	DWORD	SashItem[MAX_CHARACTER_SASH_ITEMS];		//腰包內物品	
}TPOS_EVENT_GETPLAYERQUICKSKILLITEM;
//-------------------------------------------------------------------------------
// GET Player Skill
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_GETPLAYERSKILL
{
	SHINT	SkillNo[MAX_CHARACTER_SKILLS];			//技能編號
	UHINT	SkillLevel[MAX_CHARACTER_SKILLS];		//技能等級	
}TPOS_EVENT_GETPLAYERSKILL;
//-------------------------------------------------------------------------------
// GET Player Skill
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_INITZONEWEATHER
{
	DWORD      dWeatherType;      // 天氣型態  
	DWORD      dRainActive;       // 是否下雨
	DWORD      dRainSize;         // 雨的大小
	DWORD      dSnowActive;       // 是否下雪
	DWORD      dSnowSize;         // 雪的大小
	DWORD      dCloudActive;      // 是否有雲
	DWORD      dCloudSize;        // 雲的大小
	DWORD      dThunderActive;    // 是否打雷  
	DWORD      dThunderSize;      // 雷的大小
	DWORD      dEarthQuakeActive; // 是否地震
	DWORD      dEarthQuakeSize;   // 地震大小 
	DWORD      dWindSize;         // 風的大小  
	DWORD      dWindDir;          // 風向方向
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
	DWORD           dwLeftRight;      // 左右
	DWORD           dwSkill;          // 技能  
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
    SLONG   update_type;    //UPDATE數據類型(力量, 直覺, 智力, 運氣)
    SLONG   update_value;   //UPDATE數據(>0表示增加, <0表示減少)
}TPOS_EVENT_UPDATENPCBASEDATA;
//-------------------------------------------------------------------------------
// Set Upgrade NPC Base Data
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_SETNPCUPGRADEBASEDATA
{	
    SLONG   update_type;    //UPDATE數據類型(力量, 直覺, 智力, 運氣)
    SLONG   value;          //對應數據
    SLONG   rest_point;     //剩下的屬性點	
	UHINT	att;			//攻擊力
	UHINT	defence;		//防禦力
	UHINT	max_hp;			//生命力上限
	UHINT	hp;				//當前生命力
	UHINT	max_mp;			//內力上限
	UHINT	mp;				//當前內力
}TPOS_EVENT_SETNPCUPGRADEBASEDATA;
//-------------------------------------------------------------------------------
// Request Change Zone Weather
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_REQUESTCHANGEWEATHER
{	
	DWORD      dType;      // 指定要下哪種天氣的種類 
	DWORD      dActive;    // 開始,清除,結束
	DWORD      dSize;      // 大小 
	DWORD      dWindSize;  // 風向大小 
	DWORD      dWindDir;   // 風向方向	
}TPOS_EVENT_REQUESTCHANGEWEATHER;
//-------------------------------------------------------------------------------
// Get Zone Now Weather
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_GETZONENOWWEATHER
{	
	DWORD      dWeatherType;      // 天氣型態  
	DWORD      dRainActive;       // 是否下雨
	DWORD      dRainSize;         // 雨的大小
	DWORD      dSnowActive;       // 是否下雪
	DWORD      dSnowSize;         // 雪的大小
	DWORD      dCloudActive;      // 是否有雲
	DWORD      dCloudSize;        // 雲的大小
	DWORD      dThunderActive;    // 是否打雷  
	DWORD      dThunderSize;      // 雷的大小
	DWORD      dEarthQuakeActive; // 是否地震
	DWORD      dEarthQuakeSize;   // 地震大小 
	DWORD      dWindSize;         // 風的大小  
	DWORD      dWindDir;          // 風向方向	
}TPOS_EVENT_GETZONENOWWEATHER;
// ---------------------------------------------------------------------------
// SYNC Position Struct Define
// 同步座標消息  
// ---------------------------------------------------------------------------
typedef struct POS_SYNCMOVE
{ 
 long                         lX;
 long                         lY; 
}TPOS_SYNCMOVE;
// ---------------------------------------------------------------------------
// SYNC Sea Position Struct Define
// 同步海上座標消息  
// ---------------------------------------------------------------------------
typedef struct POS_SYNCSEAMOVE
{ 
 SLONG						  X;
 SLONG						  Y;	
 SLONG						  Z;	 
}TPOS_SYNCSEAMOVE;
// ---------------------------------------------------------------------------
// Get Change Doing
// 取得改變的Doing類型
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
// 物品相關的 Event Struct
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
	ULONG			ID;						// QQ 唯一	ID 號
	ULONG			Config;					// 相關設定	
	CHAR			CharacterName[32];		// 角色名稱
	CHAR			GuildName[32];			// 工會名稱
	CHAR			State;					// 狀態	
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
	DWORD			BookMark;				// Server端查詢的BookMark
	DWORD			ZoneIndex;				// Server端查詢的ZoneIndex
	ULONG			RequestID;				// 要求的QQID	
}TPOS_EVENT_QQREQUESTQUERYONLINELIST;
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_QQGETQUERYONLINELIST
{
	DWORD			BookMark;				// Server端查詢的BookMark
	DWORD			ZoneIndex;				// Server端查詢的ZoneIndex	
	ULONG			RequestID;				// 要求的QQID
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
	ULONG			RequestID;				// 要求查詢的玩家QQID
	ULONG			ID;						// 唯一的ID
	CHAR			MainName[32];			// 角色名稱
	CHAR			NickName[32];			// 角色暱稱
	CHAR			Country;				// 國家名稱
	CHAR			GuildName[32];			// 工會名稱
	ULONG			Money;					// 金錢
	UINT			Level;					// 等級
	ULONG			PK;						// PK 數量
	CHAR			Spouse[32];				// 配偶名稱
	LONG			Prestige;				// 聲望				
	CHAR			Career;					// 職業
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
	DWORD			Index;					// 傳輸的索引
	ULONG			RequestID;				// 要求列表的 QQID
	ULONG			TargetID;				// 唯一的ID
	CHAR			MainName[32];			// 好友名稱
	UCHAR			Relation;				// 好壞 0-好, 1-壞 
	CHAR			Career;					// 職業
	CHAR			State;					// 狀態	
}TPOS_EVENT_QQGETADDSOMEONE;
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_QQREQUESTSENDMSGTOONE
{	
	ULONG			SendID;					// 發送角色ID
	ULONG			RecvID;					// 接收角色ID
	CHAR			Msg[200];	
}TPOS_EVENT_QQREQUESTSENDMSGTOONE;
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_QQREQUESTSENDMSGTOSOME
{	
	ULONG			SendID;					// 發送角色ID
	ULONG			RecvID[50];				// 接收角色ID
	CHAR			Msg[200];	
}TPOS_EVENT_QQREQUESTSENDMSGTOSOME;
//-------------------------------------------------------------------------------
typedef struct POS_EVENT_QQGETMSG
{	
	ULONG			SendID;					// 發送角色ID
	ULONG			RecvID;					// 接收角色ID
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
	UHINT	att;				//攻擊力
	UHINT	defence;			//防禦力
	UHINT	resist;				//抵抗力
	UHINT	max_hp;				//生命力上限
	UHINT	hp;					//當前生命力
	UHINT	max_mp;				//內力上限
	UHINT	mp;					//當前內力
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
	CHAR	MainName[32];	//名稱
	UHINT	Hp;				//當前HP
	UHINT	MaxHp;			//當前HP上限
	UHINT	Level;			//當前等級
	CHAR	Eyes;			//眼睛圖像索引
	CHAR	Mouth;			//口圖像索引
	CHAR	Career;			//人物職業
	CHAR	Sex;			//人物性別
	CHAR	ZoneName[32];	//所在區域
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
	UHINT	QuestID;			//任務 ID
	CHAR	TargetNpc[32];		//目標人
	ULONG	Deadline;			//任務完成的最終期限
	UCHR	PayType;			//完成任務的報酬類別 (QUEST_PAY_$$)
	ULONG	PayData;			//完成任務的報酬數值 (可以是聲望Prestidge, 金錢Money 或者物品ItemBaseID )
	UCHR	PunishType;			//未完成任務的懲罰類別
	ULONG	PunishData;			//未完成任務的懲罰數值
	CHAR	Memo[64];			//任務說明
	UHINT	RequestLevel;		//要求等級
	CHAR	RequestCareer;		//要求職業
	CHAR	RequestCareerLevel;	//要求職稱
	SLONG	RequestPrestige;	//要求聲望
}TPOS_NOTIFYNPCQUESTLIST;
//-------------------------------------------------------------------------------
typedef	struct POS_EVENT_NOTIFYNPCQUESTLIST
{
	TPOS_NOTIFYNPCQUESTLIST		QuestList[20];
}TPOS_EVENT_NOTIFYNPCQUESTLIST;
//-------------------------------------------------------------------------------
typedef	struct POS_NOTIFYPLAYERQUESTLIST
{
	CHAR	TargetNpc[32];		//目標人
	ULONG	Deadline;			//任務完成的最終期限
	CHAR	Memo[64];			//任務說明
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
	SLONG	X;			//	座標
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
	UHINT	BagIndex;				// 包包的空格 (255 為 TreasureMapItem)
	SLONG	MapLeftUpX;				// 大地圖左上角的定位座標	
	SLONG	MapLeftUpY;				// 大地圖左上角的定位座標		
	char	Memo[256];				// 說明
	SLONG	RedPointX;				// 藏寶圖上面紅點的座標
	SLONG	RedPointY;				// 藏寶圖上面紅點的座標		
}TPOS_EVENT_NOTIFYMAPINFO;
//-------------------------------------------------------------------------------
#endif//NETGE_EVENT_STRUCT_DEF_H
