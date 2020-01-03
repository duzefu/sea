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
#define MAX_GAME_CAREERS							7           //遊戲職業數目
#define MAX_CAREER_LEVELS							120         //每種職業的等級數

#define MAX_CAREER_EXP								999999999   //角色最大的經驗值
#define MAX_CAREER_HP								9999        //角色最大的生命力
#define MAX_CAREER_MP								9999        //角色最大的內力
//
#define	MAX_CAREER_STR								999			//角色最大力量
#define	MAX_CAREER_INS								999			//角色最大直覺
#define	MAX_CAREER_WIT								999			//角色最大智力
#define	MAX_CAREER_LUCKY							999			//角色最大運氣
#define	MAX_CAREER_BASE_ATTACK_RATIO				999			//角色基本值影響攻擊的最大百分比
#define	MAX_CAREER_ATTACK							999			//角色最大攻擊力
#define	MAX_CAREER_DEFENCE							999			//角色最大防禦力
#define	MAX_CAREER_DEFENCE_RATIO					999			//角色最大防禦百分比
#define	MAX_CAREER_ENHANCE_ATTACK_RATIO				999			//角色最大攻擊加強傷害百分比
#define	MAX_CAREER_RESIST							999			//角色最大抵抗力(百分比)
#define	MAX_CAREER_EXPLODE_RATE						999			//角色最大膛爆率
#define	MAX_CAREER_PROPERTY_POINT					999			//角色最大屬性點數


//
// STRUCT ///////////////////////////////////////////////////////////////////////////////////////////////////
//
//人物升N級後結算數據
//
typedef struct tagCHARACTER_UPGRADE_RESULT
{
    UHINT	level;              //最終升到的等級
    ULONG	next_exp;           //最終升到的等級的下一級經驗值
    UHINT	max_hp;				//最終HP上限
    UHINT	max_mp;				//最終MP上限
    UHINT	property_point;		//最終屬性點
} CHARACTER_UPGRADE_RESULT, *LPCHARACTER_UPGRADE_RESULT;


//
//人物屬性點與力量互換後的運算結果
//
typedef	struct tagPOINTSTR_UPDATE_RESULT 
{
	UHINT	property_point;		//屬性點
	UHINT	str;				//力量
	UHINT	att;				//攻擊力
	UHINT	defence;			//防禦力
	UHINT	max_hp;				//生命力上限
	UHINT	hp;					//當前生命力
	UHINT	max_mp;				//內力上限
	UHINT	mp;					//當前內力
} POINTSTR_UPDATE_RESULT, *LPPOINTSTR_UPDATE_RESULT;

//
//人物屬性點與直覺互換後的運算結果
//
typedef	struct tagPOINTINS_UPDATE_RESULT 
{
	UHINT	property_point;		//屬性點
	UHINT	ins;				//直覺
	UHINT	att;				//攻擊力
	UHINT	defence;			//防禦力
	UHINT	max_hp;				//生命力上限
	UHINT	hp;					//當前生命力
	UHINT	max_mp;				//內力上限
	UHINT	mp;					//當前內力
} POINTINS_UPDATE_RESULT, *LPPOINTINS_UPDATE_RESULT;

//
//人物屬性點與智力互換後的運算結果
//
typedef	struct tagPOINTWIT_UPDATE_RESULT 
{
	UHINT	property_point;		//屬性點
	UHINT	wit;				//智力
	UHINT	att;				//攻擊力
	UHINT	defence;			//防禦力
	UHINT	max_hp;				//生命力上限
	UHINT	hp;					//當前生命力
	UHINT	max_mp;				//內力上限
	UHINT	mp;					//當前內力
} POINTWIT_UPDATE_RESULT, *LPPOINTWIT_UPDATE_RESULT;

//
//人物屬性點與運氣互換後的運算結果
//
typedef	struct tagPOINTLUCKY_UPDATE_RESULT 
{
	UHINT	property_point;		//屬性點
	UHINT	lucky;				//運氣
	UHINT	att;				//攻擊力
	UHINT	defence;			//防禦力
	UHINT	max_hp;				//生命力上限
	UHINT	hp;					//當前生命力
	UHINT	max_mp;				//內力上限
	UHINT	mp;					//當前內力
} POINTLUCKY_UPDATE_RESULT, *LPPOINTLUCKY_UPDATE_RESULT;


//
//人物武器裝備改變後的運算結果
//
typedef	struct tagEQUIP_UPDATE_RESULT
{
	UHINT	att;				//攻擊力
	UHINT	defence;			//防禦力
	UHINT	resist;				//抵抗力
	UHINT	max_hp;				//生命力上限
	UHINT	hp;					//當前生命力
	UHINT	max_mp;				//內力上限
	UHINT	mp;					//當前內力
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
//  一些使用戰鬥技能的準備函數
extern  void    FightPrepareSpower(SLONG lIndex, SLONG Skill, SLONG lLevel);
extern  void    FightAbortSpower(SLONG lIndex,SLONG Skill,SLONG lLevel);
//
extern  SLONG   search_near_target_npc(SLONG npc_no);
extern  SLONG   find_near_target_npc(SLONG src_npc, SLONG center_x, SLONG center_y, SLONG radius, SLONG find_flags);
extern  SLONG   get_can_use_skill_to_attack(SLONG npc_no, SLONG dest_no);
