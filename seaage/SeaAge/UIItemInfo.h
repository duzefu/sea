/*----------------------------------------------------------------*\
|
|	UIItemInfo.h	
|
|	Zhang Zhaohui	2003/4/3
|
|	定義物品屬性的顯示順序
|
|	Copyright (c) Rays Multimedia. All rights reserved.
\*----------------------------------------------------------------*/

#pragma once

// 文字的描述請參見 itemhint.ini

#define ITEM_INFO_INDESTRUCTIBLE				0	//
#define ITEM_INFO_DURABILITY					1	//
#define ITEM_INFO_REQUIRED_GOODBAD				2	//

#define ITEM_INFO_REQUIRED_BAD					3	// 保留

// --------陸地裝備------------

#define ITEM_INFO_REQUIRED_STR					4
#define ITEM_INFO_REQUIRED_INS					5
#define ITEM_INFO_REQUIRED_WIT					6
#define ITEM_INFO_REQUIRED_LUCKY				7
#define ITEM_INFO_HITCHANCE						8
#define ITEM_INFO_EXPLODERATE					9
#define ITEM_INFO_BASEATT						10
#define ITEM_INFO_BASEDEF						11
#define ITEM_INFO_RESHPRATE						12
#define ITEM_INFO_RESMPRATE						13

// ----------藥品--------------

#define ITEM_INFO_ADD_STR						14
#define ITEM_INFO_ADD_INS						15
#define ITEM_INFO_ADD_WIT						16
#define ITEM_INFO_ADD_LUCKY						17
#define ITEM_INFO_ADD_HP						18
#define ITEM_INFO_ADD_MP						19

// --------海洋裝備------------

// --------特殊屬性------------

#define ITEM_INFO_ACC_MUSE						20
#define ITEM_INFO_ANTI_BAD						21
#define ITEM_INFO_LEVEL_ADD_ATT					22
#define ITEM_INFO_LEVEL_ADD_DEF					23
#define ITEM_INFO_LEVEL_ADD_MAX_HP				24
#define ITEM_INFO_LEVEL_ADD_MAX_MP				25
#define ITEM_INFO_LOWER_DAMAGE					26

#define ITEM_INFO_LOWER_REQUIRED				27
#define ITEM_INFO_BE_TORTOISE					28
#define ITEM_INFO_BE_PIG						29
#define ITEM_INFO_SLEEP							30
#define ITEM_INFO_ADD_SKILL_LEVEL				31
#define ITEM_INFO_ADD_GENERAL_SKILL_LEVEL		32
#define ITEM_INFO_ADD_SWORDER_SKILL_LEVEL		33
#define ITEM_INFO_ADD_EXPLORER_SKILL_LEVEL		34
#define ITEM_INFO_ADD_THIEF_SKILL_LEVEL			35
#define ITEM_INFO_ADD_TRADER_SKILL_LEVEL		36
#define ITEM_INFO_ADD_CLERIC_SKILL_LEVEL		37
#define ITEM_INFO_ADD_HOROSCOPER_SKILL_LEVEL	38
#define ITEM_INFO_ADD_ATTACK_RATIO				39

#define ITEM_INFO_ADD_MAX_HP					40	// 增加生命上限
#define ITEM_INFO_ADD_MAX_MP					41	// 增加魔法上限
#define ITEM_INFO_ADD_DEF						42	// 增加防禦力
#define ITEM_INFO_ADD_ENHANCE_DEF				43	// 加強防禦
#define ITEM_INFO_ADD_RESIST					44	// 增加抵抗

#define ITEM_INFO_ADD_ATT						45	// 增加攻擊力
#define ITEM_INFO_ENHANCE_ATT					46	// 加強攻擊
#define ITEM_INFO_ADD_MAGIC_HURT				47	// 增加魔法傷害
#define ITEM_INFO_ADD_SPECIAL_HURT				48	// 增加特殊傷害

#define ITEM_INFO_MAN_ONLY						49	// 男
#define ITEM_INFO_WOMAN_ONLY					50	// 女

#define ITEM_INFO_GENERAL_ONLY					51	// 提督
#define ITEM_INFO_SWORDER_ONLY					52	// 劍客
#define ITEM_INFO_EXPLORER_ONLY					53	// 探險家
#define ITEM_INFO_THIEF_ONLY					54	// 小偷
#define ITEM_INFO_TRADER_ONLY					55	// 商人
#define ITEM_INFO_CLERIC_ONLY					56	// 牧師
#define ITEM_INFO_HOROSCOPER_ONLY				57	// 占星術士

#define ITEM_INFO_USER							58	// %s專用


CONST DOUBLE	LOWER_REQUIRED = 0.2;		// 最小需求減少

CONST DOUBLE	LEVEL_ADD_ATT = 0.5;		// 基於等級增加傷害(暫)
CONST DOUBLE	LEVEL_ADD_DEF = 0.5;		// 基於等級增加防禦_(暫)
CONST DOUBLE	LEVEL_ADD_MAX_HP = 0.5;		// 基於等級增加生命上限(暫)
CONST DOUBLE	LEVEL_ADD_MAX_MP = 0.5;		// 基於等級增加魔力上限(暫)
CONST DWORD		LOW_DAMAGE = 10;			// 減少物理傷害

CONST DWORD		SMALL_ATTATCK_RATE = 5;		// 攻擊力增加的值(小)
CONST DWORD		MIDDLE_ATTACK_RATE = 10;	// 攻擊力增加的值(中)
CONST DWORD		LARGE_ATTACK_RATE  = 15;	// 攻擊力增加的值(大)

