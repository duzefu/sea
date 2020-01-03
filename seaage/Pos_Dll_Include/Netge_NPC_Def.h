//===============================================================================
// Netge_NPC_Def.h
// NPC Struct Define Header File
// By Hawke Hsieh
// 2002-08-12
//===============================================================================
#ifndef NETGE_NPC_DEF_H
#define NETGE_NPC_DEF_H

#define	MAX_NPC_TYPE	500
// ---------------------------------------------------------------------------
// 名稱
// ---------------------------------------------------------------------------
typedef struct POS_NPC_NAME
{
 DWORD      dIndex;                 // 編號
 char		cNPCName[32];          // 名稱
 UHINT      uiKind;					// 類型
}TPOS_NPC_NAME;
// ---------------------------------------------------------------------------
// 某些狀態 
// =======類型=========
//       0   //砲台
//       1   //路牌
//       2   //普通怪物
//       3   //頭目怪物
//       4   //BOSS怪物
//       5   //小偷怪
//       6   //寶物怪
//       7   //警衛
//       8   //閒人(村人)
//       9   //玩家
//       10  //寶藏(小島)
//       11  //美人魚(會改變背景音樂)
//       12  //陷阱
//       13  //暗礁
//       14  //漩渦
//       15  //雕像
//       16  //屍體
// =======類型=========
// ---------------------------------------------------------------------------
typedef struct POS_NPC_BASIC
{ 
 DWORD      dLevel;                 // 等級
 DWORD		dHP;                    // HP
 DWORD		dHPLimit;               // HP Limit
 DWORD		dMP;                    // MANA
 DWORD		dMPLimit;				// MANA Limit
 DWORD		dDemage;                // 攻擊力
 DWORD		dHT;                    // 命中力
 DWORD		dMagicDemage;           // 魔法攻擊力
 DWORD		dDefence;               // 防禦力
 DWORD		dResist;                // 抵抗力
 DWORD		dMSpeed;                // 速度
 DWORD		dSight;                 // 視野
 int        iFileIndex;             // 外觀 (File_Index)
 DWORD      dSpec;                  // 特性
 DWORD      dAI;                    // AI
}TPOS_NPC_BASIC;
// ---------------------------------------------------------------------------
// 技能
// ---------------------------------------------------------------------------
typedef struct POS_NPC_SKILL
{
 DWORD      dSkill[10];
}TPOS_NPC_SKILL;
// ---------------------------------------------------------------------------
// 身上物品
// ---------------------------------------------------------------------------
typedef struct POS_NPC_ITEM
{
 DWORD      dItem[10];
 //DWORD      dAccount[10];
}TPOS_NPC_ITEM;
// ---------------------------------------------------------------------------
// NPC種類基本結構
// ---------------------------------------------------------------------------
typedef struct POS_NPC
{
 TPOS_NPC_NAME     Name;
 TPOS_NPC_BASIC    Basic;
 TPOS_NPC_SKILL    Skill;
 TPOS_NPC_ITEM     Item;
}TPOS_NPC;
// ---------------------------------------------------------------------------
#endif