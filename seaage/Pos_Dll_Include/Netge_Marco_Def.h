//===============================================================================
// Netge_Macro_Def.h
// Macro Struct Define Header File
// By Hawke Hsieh
// 2002-08-12
//===============================================================================
#ifndef HMACRO_DEF_H
#define HMACRO_DEF_H

#define	MAX_ZONE_PER_MACRO		1024
#define	MAX_MAPLINK_PER_ZONE	48
#define	MAX_QUEST_PER_NPC		10
#define	MACRO_VERSION			500
//#define	MAX_TALK_PER_NPC		50
//-----------------------------------------------------------------------------------
// ��@�s���I�����
//-----------------------------------------------------------------------------------
typedef struct
{ 
 DWORD				dDestZoneIndex;			// �s�����ϰ�s��
 long				lDestZoneX;				// �ؼЫ����y��
 long				lDestZoneY;                  
 long				lDestZoneZ;
 char				cDir[1];				//��e��V
 UHINT				LocalProcessID;			//���a���ƥ�� ID
 UHINT				RemoteProcessID;		//�ت��a�ƥ�� ID
 SLONG				RemoteLineStartPointX;	//�ت��a�u�q�_�l�I
 SLONG				RemoteLineStartPointY;	//�ت��a�u�q�_�l�I
 SLONG				RemoteLineEndPointX;	//�ت��a�u�q���I
 SLONG				RemoteLineEndPointY;	//�ت��a�u�q���I
}TPOS_MACRO_MAPLINK_POINT;
//---------------------------------------------------------------------------
// �@���򥻵��c
//---------------------------------------------------------------------------
typedef struct POS_MACRO_BASIC
{
 DWORD				dIndex;				//�ϰ����
 char				cName[32];			//�ϰ�W��
 char				cMapName[32];		//�ϰ�a�ϦW�� 
 TPOS_MACRO_MAPLINK_POINT MapLinkPoint[MAX_MAPLINK_PER_ZONE];//�a�ϳs���I�����
}TPOS_MACRO_BASIC;
//---------------------------------------------------------------------------
// ��ܪ����c
//---------------------------------------------------------------------------
/*
typedef struct POS_MARCO_TALK
{
 DWORD             dIndex;				//��ܽs��
 DWORD             dCommand;			//�R�O
 char              cMessage[100];		//���e
 DWORD             dNextIndex;			//�U�@�ӱ����s��
 DWORD             dNextCommand;		//�U�@�ӱ����R�O
}TPOS_MARCO_TALK;
*/
//---------------------------------------------------------------------------
// NPC �����c
//---------------------------------------------------------------------------
typedef struct POS_MACRO_NPC
{
 DWORD				dIndex;			//NPC���s��
 char				cName[32];		//NPC�W��
 DWORD				dNPCType;		//NPC���O
 UHINT				uiKind;			//NPC������
 UHINT				uiGroup;		//�էO�s�� 
 DWORD				dX;				//�y��
 DWORD				dY;
 DWORD				dZ;
 DWORD				dQuest[MAX_QUEST_PER_NPC];	//���W�������Ƚs��
 //DWORD             dTalk[MAX_TALK_PER_NPC];	//���W��ܪ��s��
}TPOS_MACRO_NPC;
//---------------------------------------------------------------------------
// �ϰ쪺���c
//---------------------------------------------------------------------------
typedef struct POS_MACRO_ZONE
{
 TPOS_MACRO_BASIC	Basic;					//�ϰ�򥻸��
 TPOS_MACRO_NPC		NPC[MAX_NPC_PER_ZONE];	//NPC�����
 UHINT				uiNormalProbability;
 UHINT				uiDrugProbability;
 UHINT				uiMoneyProbability;
 UHINT				uiTreasureMapProbability;
}TPOS_MACRO_ZONE;
//---------------------------------------------------------------------------
typedef struct POS_MACRO_ZONE_INDEX
{
 DWORD				dIndex;				//�ϰ����
 char				cName[32];			//�ϰ�W��  
 char				cMapName[32];		//�a�ϦW��
 char				cCountry;           //���ݰ�a
 long				lBirthPointX;		//�X���I
 long				lBirthPointY;				
 long				lBirthPointZ; 
 //SDOUBLE			LULongitude;		//���W�g��
 //SDOUBLE			LULatitude;			//���W�n��
 //SDOUBLE			RDLongitude;		//�k�U�g��
 //SDOUBLE			RDLatitude;			//�k�U�n��
 DWORD				dType;				//�ϰ�����
}TPOS_MACRO_ZONE_INDEX;
//---------------------------------------------------------------------------
typedef struct POS_MACRO_WORLD
{ 
 char				cName[32];							//�M�צW��
 DWORD				dVersion;							//�������X
 DWORD				dOtherZoneItemMFProbability;		//��L�ϰ쪺MF���v
 DWORD				dFindGoldZoneItemMFProbability;		//�M�_�a�I��MF���v
 UHINT				uiNPCTypeDropItemProbability[17];	//�Ǫ������������~�����v
 TPOS_MACRO_ZONE_INDEX	Zone[MAX_ZONE_PER_MACRO];
}TPOS_MACRO_WORLD;
//---------------------------------------------------------------------------
#endif

