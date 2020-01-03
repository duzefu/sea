/*----------------------------------------------------------------*\
|
|	UIItemInfo.h	
|
|	Zhang Zhaohui	2003/4/3
|
|	�w�q���~�ݩʪ���ܶ���
|
|	Copyright (c) Rays Multimedia. All rights reserved.
\*----------------------------------------------------------------*/

#pragma once

// ��r���y�z�аѨ� itemhint.ini

#define ITEM_INFO_INDESTRUCTIBLE				0	//
#define ITEM_INFO_DURABILITY					1	//
#define ITEM_INFO_REQUIRED_GOODBAD				2	//

#define ITEM_INFO_REQUIRED_BAD					3	// �O�d

// --------���a�˳�------------

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

// ----------�ī~--------------

#define ITEM_INFO_ADD_STR						14
#define ITEM_INFO_ADD_INS						15
#define ITEM_INFO_ADD_WIT						16
#define ITEM_INFO_ADD_LUCKY						17
#define ITEM_INFO_ADD_HP						18
#define ITEM_INFO_ADD_MP						19

// --------���v�˳�------------

// --------�S���ݩ�------------

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

#define ITEM_INFO_ADD_MAX_HP					40	// �W�[�ͩR�W��
#define ITEM_INFO_ADD_MAX_MP					41	// �W�[�]�k�W��
#define ITEM_INFO_ADD_DEF						42	// �W�[���m�O
#define ITEM_INFO_ADD_ENHANCE_DEF				43	// �[�j���m
#define ITEM_INFO_ADD_RESIST					44	// �W�[���

#define ITEM_INFO_ADD_ATT						45	// �W�[�����O
#define ITEM_INFO_ENHANCE_ATT					46	// �[�j����
#define ITEM_INFO_ADD_MAGIC_HURT				47	// �W�[�]�k�ˮ`
#define ITEM_INFO_ADD_SPECIAL_HURT				48	// �W�[�S��ˮ`

#define ITEM_INFO_MAN_ONLY						49	// �k
#define ITEM_INFO_WOMAN_ONLY					50	// �k

#define ITEM_INFO_GENERAL_ONLY					51	// ����
#define ITEM_INFO_SWORDER_ONLY					52	// �C��
#define ITEM_INFO_EXPLORER_ONLY					53	// ���I�a
#define ITEM_INFO_THIEF_ONLY					54	// �p��
#define ITEM_INFO_TRADER_ONLY					55	// �ӤH
#define ITEM_INFO_CLERIC_ONLY					56	// ���v
#define ITEM_INFO_HOROSCOPER_ONLY				57	// �e�P�N�h

#define ITEM_INFO_USER							58	// %s�M��


CONST DOUBLE	LOWER_REQUIRED = 0.2;		// �̤p�ݨD���

CONST DOUBLE	LEVEL_ADD_ATT = 0.5;		// ��󵥯żW�[�ˮ`(��)
CONST DOUBLE	LEVEL_ADD_DEF = 0.5;		// ��󵥯żW�[���m_(��)
CONST DOUBLE	LEVEL_ADD_MAX_HP = 0.5;		// ��󵥯żW�[�ͩR�W��(��)
CONST DOUBLE	LEVEL_ADD_MAX_MP = 0.5;		// ��󵥯żW�[�]�O�W��(��)
CONST DWORD		LOW_DAMAGE = 10;			// ��֪��z�ˮ`

CONST DWORD		SMALL_ATTATCK_RATE = 5;		// �����O�W�[����(�p)
CONST DWORD		MIDDLE_ATTACK_RATE = 10;	// �����O�W�[����(��)
CONST DWORD		LARGE_ATTACK_RATE  = 15;	// �����O�W�[����(�j)

