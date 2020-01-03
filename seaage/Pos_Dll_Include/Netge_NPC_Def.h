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
// �W��
// ---------------------------------------------------------------------------
typedef struct POS_NPC_NAME
{
 DWORD      dIndex;                 // �s��
 char		cNPCName[32];          // �W��
 UHINT      uiKind;					// ����
}TPOS_NPC_NAME;
// ---------------------------------------------------------------------------
// �Y�Ǫ��A 
// =======����=========
//       0   //���x
//       1   //���P
//       2   //���q�Ǫ�
//       3   //�Y�ةǪ�
//       4   //BOSS�Ǫ�
//       5   //�p����
//       6   //�_����
//       7   //ĵ��
//       8   //���H(���H)
//       9   //���a
//       10  //�_��(�p�q)
//       11  //���H��(�|���ܭI������)
//       12  //����
//       13  //�t�G
//       14  //�x��
//       15  //�J��
//       16  //����
// =======����=========
// ---------------------------------------------------------------------------
typedef struct POS_NPC_BASIC
{ 
 DWORD      dLevel;                 // ����
 DWORD		dHP;                    // HP
 DWORD		dHPLimit;               // HP Limit
 DWORD		dMP;                    // MANA
 DWORD		dMPLimit;				// MANA Limit
 DWORD		dDemage;                // �����O
 DWORD		dHT;                    // �R���O
 DWORD		dMagicDemage;           // �]�k�����O
 DWORD		dDefence;               // ���m�O
 DWORD		dResist;                // ��ܤO
 DWORD		dMSpeed;                // �t��
 DWORD		dSight;                 // ����
 int        iFileIndex;             // �~�[ (File_Index)
 DWORD      dSpec;                  // �S��
 DWORD      dAI;                    // AI
}TPOS_NPC_BASIC;
// ---------------------------------------------------------------------------
// �ޯ�
// ---------------------------------------------------------------------------
typedef struct POS_NPC_SKILL
{
 DWORD      dSkill[10];
}TPOS_NPC_SKILL;
// ---------------------------------------------------------------------------
// ���W���~
// ---------------------------------------------------------------------------
typedef struct POS_NPC_ITEM
{
 DWORD      dItem[10];
 //DWORD      dAccount[10];
}TPOS_NPC_ITEM;
// ---------------------------------------------------------------------------
// NPC�����򥻵��c
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