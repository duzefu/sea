#ifndef INITWORLDDATA_H
#define INITWORLDDATA_H

// ---------------------------------------------------------------------------
// ZoneServer Information Struct Define
// �ϰ���A����T 
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
	DWORD			dwType;		// 0 - ���a , 1 -���W 
	TPOS_QQ_ONLINE_PLAYER_LIST QQOnlinePlayerList[MAX_PLAYER_PER_ZONE];

}TPOS_ZONEINFO;
// ---------------------------------------------------------------------------
// New Character Information Struct Define
// �s�J���a�إ߷s������
// ---------------------------------------------------------------------------
typedef struct POS_NEWCHARACTERINFO
{
	DWORD	dwIndex;		//���b�����ĴX�Ө���
	SLONG	slFileIndex;	//����v��������
	char	cId[32];		//Account ID
	ULONG	ulQQId;			//QQ ID
	char	cMainName[32];	//�W��
	char	cNickName[32];	//�ʺ�
	CHAR	cSex;			//�ʧO
	CHAR	cCareer;		//¾�~
	CHAR	cColor;			//�C��
	CHAR	cEyes;			//����
	CHAR	cMouth;			//�L
	CHAR	cCountry;		//���ݰ�a
	UHINT	uhiStr;			//�O�q
	UHINT	uhiIns;			//��ı
	UHINT	uhiWis;			//���O
	UHINT	uhiLucky;		//�B��
	UHINT	uhiHp;			//�ͩR�O
	UHINT	uhiMp;			//�k�O
	UHINT	uhiMspeed;		//���ʳt��
	SLONG	slX;			//�y��
	SLONG	slY;
	SLONG	slZ;
	char	cZone[32];		//�ϰ�W��
	UHINT	uhiDemage;		//����
	UHINT	uhiDefence;		//���m
	SLONG	slSight;		//����
	UHINT	uhiExp;			//�g���
	UHINT	uhiLevel;		//����	
	SHINT	shiQuickSkillLeft;						//����ޯ�
	SHINT	shiQuickSkillRight;						//�k��ޯ�
	SHINT	shiSkill[MAX_CHARACTER_DEFAULT_SKILLS];	//�ޯ�
	POS_ITEM Item[MAX_CHARACTER_DEFAULT_ITEMS];		//���~
}TPOS_NEWCHARACTERINFO;
//----------------------------------------------------------------------------------
// ���a��ܰ�a�X�ͫ���,�y�йw�]��
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