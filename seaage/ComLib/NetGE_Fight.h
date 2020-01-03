/*
**	NetGE_Fight.h 
**	fight functions header.
**
**	Jack, 2003.1.10
*/
#pragma once


//
// DEFINES //////////////////////////////////////////////////////////////////////////////////////////////////
//
#define MAX_GAME_CAREERS							7           //�C��¾�~�ƥ�
#define MAX_CAREER_LEVELS							120         //�C��¾�~�����ż�

#define MAX_CAREER_EXP								999999999   //����̤j���g���
#define MAX_CAREER_HP								9999        //����̤j���ͩR�O
#define MAX_CAREER_MP								9999        //����̤j�����O
//
#define	MAX_CAREER_STR								999			//����̤j�O�q
#define	MAX_CAREER_INS								999			//����̤j��ı
#define	MAX_CAREER_WIT								999			//����̤j���O
#define	MAX_CAREER_LUCKY							999			//����̤j�B��
#define	MAX_CAREER_BASE_ATTACK_RATIO				999			//����򥻭ȼv�T�������̤j�ʤ���
#define	MAX_CAREER_ATTACK							999			//����̤j�����O
#define	MAX_CAREER_DEFENCE							999			//����̤j���m�O
#define	MAX_CAREER_DEFENCE_RATIO					999			//����̤j���m�ʤ���
#define	MAX_CAREER_ENHANCE_ATTACK_RATIO				999			//����̤j�����[�j�ˮ`�ʤ���
#define	MAX_CAREER_RESIST							999			//����̤j��ܤO(�ʤ���)
#define	MAX_CAREER_EXPLODE_RATE						999			//����̤j���z�v
#define	MAX_CAREER_PROPERTY_POINT					999			//����̤j�ݩ��I��


//
// STRUCT ///////////////////////////////////////////////////////////////////////////////////////////////////
//
//�H����N�ūᵲ��ƾ�
//
typedef struct tagCHARACTER_UPGRADE_RESULT
{
    UHINT	level;              //�̲פɨ쪺����
    ULONG	next_exp;           //�̲פɨ쪺���Ū��U�@�Ÿg���
    UHINT	max_hp;				//�̲�HP�W��
    UHINT	max_mp;				//�̲�MP�W��
    UHINT	property_point;		//�̲��ݩ��I
} CHARACTER_UPGRADE_RESULT, *LPCHARACTER_UPGRADE_RESULT;


//
//�H���ݩ��I�P�O�q�����᪺�B�⵲�G
//
typedef	struct tagPOINTSTR_UPDATE_RESULT 
{
	UHINT	property_point;		//�ݩ��I
	UHINT	str;				//�O�q
	UHINT	att;				//�����O
	UHINT	defence;			//���m�O
	UHINT	max_hp;				//�ͩR�O�W��
	UHINT	hp;					//��e�ͩR�O
	UHINT	max_mp;				//���O�W��
	UHINT	mp;					//��e���O
} POINTSTR_UPDATE_RESULT, *LPPOINTSTR_UPDATE_RESULT;

//
//�H���ݩ��I�P��ı�����᪺�B�⵲�G
//
typedef	struct tagPOINTINS_UPDATE_RESULT 
{
	UHINT	property_point;		//�ݩ��I
	UHINT	ins;				//��ı
	UHINT	att;				//�����O
	UHINT	defence;			//���m�O
	UHINT	max_hp;				//�ͩR�O�W��
	UHINT	hp;					//��e�ͩR�O
	UHINT	max_mp;				//���O�W��
	UHINT	mp;					//��e���O
} POINTINS_UPDATE_RESULT, *LPPOINTINS_UPDATE_RESULT;

//
//�H���ݩ��I�P���O�����᪺�B�⵲�G
//
typedef	struct tagPOINTWIT_UPDATE_RESULT 
{
	UHINT	property_point;		//�ݩ��I
	UHINT	wit;				//���O
	UHINT	att;				//�����O
	UHINT	defence;			//���m�O
	UHINT	max_hp;				//�ͩR�O�W��
	UHINT	hp;					//��e�ͩR�O
	UHINT	max_mp;				//���O�W��
	UHINT	mp;					//��e���O
} POINTWIT_UPDATE_RESULT, *LPPOINTWIT_UPDATE_RESULT;

//
//�H���ݩ��I�P�B�𤬴��᪺�B�⵲�G
//
typedef	struct tagPOINTLUCKY_UPDATE_RESULT 
{
	UHINT	property_point;		//�ݩ��I
	UHINT	lucky;				//�B��
	UHINT	att;				//�����O
	UHINT	defence;			//���m�O
	UHINT	max_hp;				//�ͩR�O�W��
	UHINT	hp;					//��e�ͩR�O
	UHINT	max_mp;				//���O�W��
	UHINT	mp;					//��e���O
} POINTLUCKY_UPDATE_RESULT, *LPPOINTLUCKY_UPDATE_RESULT;


//
//�H���Z���˳Ƨ��ܫ᪺�B�⵲�G
//
typedef	struct tagEQUIP_UPDATE_RESULT
{
	UHINT	att;				//�����O
	UHINT	defence;			//���m�O
	UHINT	resist;				//��ܤO
	UHINT	max_hp;				//�ͩR�O�W��
	UHINT	hp;					//��e�ͩR�O
	UHINT	max_mp;				//���O�W��
	UHINT	mp;					//��e���O
} EQUIP_UPDATE_RESULT, *LPEQUIP_UPDATE_RESULT;


//
// FUNCTIONS ////////////////////////////////////////////////////////////////////////////////////////////////
//
extern  void    InitCareerUpgrade(void);
extern  SLONG   LoadCareerUpgrade(void);
extern  void    FreeCareerUpgrade(void);
extern  void    DebugLogCareerUpgrade(void);
extern	SLONG   LoadOneCareerUpgrade(SLONG char_index);
extern	void    DebugLogOneCareerUpgrade(SLONG char_index);
//
extern	void	InitCareerBaseAffectInfo(void);
extern	SLONG	LoadCareerBaseAffectInfo(void);
extern	void	FreeCareerBaseAffectInfo(void);
extern	void	DebugLogCareerBaseAffectInfo(void);
//
extern  SLONG   GetCareerUpgradeExp(SLONG char_index, SLONG level);
extern  SLONG   GetCareerUpgradeAddMaxHp(SLONG char_index, SLONG level);
extern  SLONG   GetCareerUpgradeAddMaxMp(SLONG char_index, SLONG level);
extern  SLONG   GetCareerUpgradeAddAttribPoint(SLONG char_index, SLONG level);
//
extern  SLONG   ComputeCharacterUpgradeResult(SLONG lIndex, SLONG level, SLONG exp, CHARACTER_UPGRADE_RESULT *lpResult);
//
extern	UHINT	ComputeCareerBaseAttackRatio(SLONG char_index, SLONG str, SLONG ins, SLONG wit, SLONG lucky);
extern	UHINT	ComputeCareerBaseDefence(SLONG char_index, SLONG str, SLONG ins, SLONG wit, SLONG lucky);
extern	UHINT	ComputeCareerBaseMaxHp(SLONG char_index, SLONG str, SLONG ins, SLONG wit, SLONG lucky);
extern	UHINT	ComputeCareerBaseMaxMp(SLONG char_index, SLONG str, SLONG ins, SLONG wit, SLONG lucky);
extern	SLONG	CharCareer2IntCareer(SLONG career);
//
extern	UHINT	ComputeCharacterFinalStr(SLONG lIndex);
extern	UHINT	ComputeCharacterFinalIns(SLONG lIndex);
extern	UHINT	ComputeCharacterFinalWit(SLONG lIndex);
extern	UHINT	ComputeCharacterFinalLucky(SLONG lIndex);
//
extern	UHINT	ComputeCharacterSkillAttackRatio(SLONG lIndex);
extern	UHINT	ComputeCharacterAttribAttackRatio(SLONG lIndex);
extern	UHINT	ComputeCharacterEquipBaseAttack(SLONG lIndex);
extern	UHINT	ComputeCharacterFinalAttack(SLONG lIndex);
extern	void	ComputeCharacterFinalAttackWithSkill(SLONG lIndex, SLONG lSkillNo);
//
extern	UHINT	ComputeCharacterEquipExplodeRate(SLONG lIndex);
extern	UHINT	ComputeCharacterSkillExplodeRate(SLONG lIndex);
extern	UHINT	ComputeCharacterFinalExplodeRate(SLONG lIndex);
//
extern	UHINT	ComputeCharacterBaseDefence(SLONG lIndex);
extern	UHINT	ComputeCharacterEquipDefence(SLONG lIndex);
extern	UHINT	ComputeCharacterFinalDefence(SLONG lIndex);
//
extern	UHINT	ComputeCharacterEquipResistRatio(SLONG lIndex);
extern	UHINT	ComputeCharacterFinalResist(SLONG lIndex);
//
extern	UHINT	ComputeCharacterAttribMaxHp(SLONG lIndex);
extern	UHINT	ComputeCharacterEquipMaxHp(SLONG lIndex);
extern	UHINT	ComputeCharacterSkillMaxHp(SLONG lIndex);
extern	UHINT	ComputeCharacterFinalMaxHp(SLONG lIndex);
//
extern	UHINT	ComputeCharacterAttribMaxMp(SLONG lIndex);
extern	UHINT	ComputeCharacterEquipMaxMp(SLONG lIndex);
extern	UHINT	ComputeCharacterSkillMaxMp(SLONG lIndex);
extern	UHINT	ComputeCharacterFinalMaxMp(SLONG lIndex);
//
extern	void	UpdateCharacterDataWithBaseAttrib(SLONG lIndex);
extern	SLONG	ComputeCharacterPropertyPointToPointStr(SLONG lIndex, SLONG lData, POINTSTR_UPDATE_RESULT *lpResult);
extern	SLONG	ComputeCharacterPointStrToPropertyPoint(SLONG lIndex, SLONG lData, POINTSTR_UPDATE_RESULT *lpResult);
extern	SLONG	ComputeCharacterPropertyPointToPointIns(SLONG lIndex, SLONG lData, POINTINS_UPDATE_RESULT *lpResult);
extern	SLONG	ComputeCharacterPointInsToPropertyPoint(SLONG lIndex, SLONG lData, POINTINS_UPDATE_RESULT *lpResult);
extern	SLONG	ComputeCharacterPropertyPointToPointWit(SLONG lIndex, SLONG lData, POINTWIT_UPDATE_RESULT *lpResult);
extern	SLONG	ComputeCharacterPointWitToPropertyPoint(SLONG lIndex, SLONG lData, POINTWIT_UPDATE_RESULT *lpResult);
extern	SLONG	ComputeCharacterPropertyPointToPointLucky(SLONG lIndex, SLONG lData, POINTLUCKY_UPDATE_RESULT *lpResult);
extern	SLONG	ComputeCharacterPointLuckyToPropertyPoint(SLONG lIndex, SLONG lData, POINTLUCKY_UPDATE_RESULT *lpResult);
extern	void	EndAdjustCharacterPropertyPoint(SLONG lIndex);
//
extern	SLONG	UpdateCharacterDataWithChangeEquip(SLONG lIndex, EQUIP_UPDATE_RESULT *lpResult);
extern	SLONG	ComputeCharacterDataAfterChangeEquipHead(SLONG lIndex, EQUIP_UPDATE_RESULT *lpResult);
extern	SLONG	ComputeCharacterDataAfterChangeEquipNeck(SLONG lIndex, EQUIP_UPDATE_RESULT *lpResult);
extern	SLONG	ComputeCharacterDataAfterChangeEquipBody(SLONG lIndex, EQUIP_UPDATE_RESULT *lpResult);
extern	SLONG	ComputeCharacterDataAfterChangeEquipWaist(SLONG lIndex, EQUIP_UPDATE_RESULT *lpResult);
extern	SLONG	ComputeCharacterDataAfterChangeEquipGlove(SLONG lIndex, EQUIP_UPDATE_RESULT *lpResult);
extern	SLONG	ComputeCharacterDataAfterChangeEquipWeapon(SLONG lIndex, EQUIP_UPDATE_RESULT *lpResult);
extern	SLONG	ComputeCharacterDataAfterChangeEquipWrist(SLONG lIndex, EQUIP_UPDATE_RESULT *lpResult);
extern	SLONG	ComputeCharacterDataAfterChangeEquipFeet(SLONG lIndex, EQUIP_UPDATE_RESULT *lpResult);
extern	SLONG	ComputeCharacterDataAfterChangeEquipOtherA(SLONG lIndex, EQUIP_UPDATE_RESULT *lpResult);
extern	SLONG	ComputeCharacterDataAfterChangeEquipOtherB(SLONG lIndex, EQUIP_UPDATE_RESULT *lpResult);
extern	SLONG	ComputeCharacterDataAfterChangeEquipOtherC(SLONG lIndex, EQUIP_UPDATE_RESULT *lpResult);
//
extern	void	ComputeCharacterDataAfterInit(SLONG lIndex);
//
//  �@�Ǩϥξ԰��ޯ઺�ǳƨ��
extern  void    FightPrepareSpower(SLONG lIndex, SLONG Skill, SLONG lLevel);
extern  void    FightAbortSpower(SLONG lIndex,SLONG Skill,SLONG lLevel);
//
extern  SLONG   search_near_target_npc(SLONG npc_no);
extern  SLONG   find_near_target_npc(SLONG src_npc, SLONG center_x, SLONG center_y, SLONG radius, SLONG find_flags);
extern  SLONG   get_can_use_skill_to_attack(SLONG npc_no, SLONG dest_no);
