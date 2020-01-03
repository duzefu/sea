#ifndef INITWORLDDATA_H
#define INITWORLDDATA_H

// ---------------------------------------------------------------------------
// ZoneServer Information Struct Define
// 區域伺服器資訊 
// ---------------------------------------------------------------------------
typedef struct POS_ZONEINFO
{
	DWORD			dwSocket;
	DWORD			dwIndex;
	DWORD		   	dwPort;
	char           	cAddr[16];
	DWORD	        dwPlayerCount;
	char	        cName[32];
	char            cMapName[32]; 
	DWORD			dwType;		// 0 - 陸地 , 1 -海上 
	TPOS_QQ_ONLINE_PLAYER_LIST QQOnlinePlayerList[MAX_PLAYER_PER_ZONE];

}TPOS_ZONEINFO;
// ---------------------------------------------------------------------------
// New Character Information Struct Define
// 存入玩家建立新的角色
// ---------------------------------------------------------------------------
typedef struct POS_NEWCHARACTERINFO
{
	DWORD	dwIndex;		//此帳號的第幾個角色
	SLONG	slFileIndex;	//角色影像文件索引
	char	cId[32];		//Account ID
	ULONG	ulQQId;			//QQ ID
	char	cMainName[32];	//名稱
	char	cNickName[32];	//暱稱
	CHAR	cSex;			//性別
	CHAR	cCareer;		//職業
	CHAR	cColor;			//顏色
	CHAR	cEyes;			//眼睛
	CHAR	cMouth;			//嘴
	CHAR	cCountry;		//所屬國家
	UHINT	uhiStr;			//力量
	UHINT	uhiIns;			//直覺
	UHINT	uhiWis;			//智力
	UHINT	uhiLucky;		//運氣
	UHINT	uhiHp;			//生命力
	UHINT	uhiMp;			//法力
	UHINT	uhiMspeed;		//移動速度
	SLONG	slX;			//座標
	SLONG	slY;
	SLONG	slZ;
	char	cZone[32];		//區域名稱
	UHINT	uhiDemage;		//攻擊
	UHINT	uhiDefence;		//防禦
	SLONG	slSight;		//視野
	UHINT	uhiExp;			//經驗值
	UHINT	uhiLevel;		//等級	
	SHINT	shiQuickSkillLeft;						//左手技能
	SHINT	shiQuickSkillRight;						//右手技能
	SHINT	shiSkill[MAX_CHARACTER_DEFAULT_SKILLS];	//技能
	POS_ITEM Item[MAX_CHARACTER_DEFAULT_ITEMS];		//物品
}TPOS_NEWCHARACTERINFO;
//----------------------------------------------------------------------------------
// 玩家選擇國家出生城市,座標預設值
//----------------------------------------------------------------------------------
typedef struct
{
 char    cCountry;
 char    cCityName[32];
 char    cCityMap[32];
 SLONG   lDefaultX;
 SLONG   lDefaultY;
 SLONG   lDefaultZ;
}TPOS_COUNTRYCITY;

void InitCharacterDefault();
void InitCountryDefaultCity();
int	ReturnZoneType(DWORD zonetype);
SLONG LoadZoneMacroFile(char *Name);

#endif