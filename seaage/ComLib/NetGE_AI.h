/*
 *	NetGE_AI.cpp
 *      ����C����AI����@�Ǩ��
 */
 
//----
//  
//---- 
#define    MAX_AI_TYPE         100
#define    MAX_AI_BLOCK_TYPE   256
//----
//  ai�������w�q 
//----
#define         MAIN_AI_CONTROL     0   //���a����..AI_BLOCK�Ѫ��a��
#define         MAIN_AI_IDLE        1   //IDLE
#define         MAIN_AI_FIGHT_GAD   2   //�C��..�b�a�ϤW�H���è�
//----
//  AI_BLOCK�������w�q
//----
#define         MAIN_AI_BLOCK_DUMP          0   //�Ŭƻ򳣤��@
#define         MAIN_AI_BLOCK_IDLE          1   //�b��a�ݾ�
#define         MAIN_AI_BLOCK_USE_SKILL     2   //�b��a�ϥβ��ӧޯ�    
#define         MAIN_AI_BLOCK_TALK          3   //�b��ĩM�H���
#define         MAIN_AI_BLOCK_SPOWER        4   //�W�O��AI�_
#define         MAIN_AI_BLOCK_MOVE_TO       5   //���ʨ���ӥؼ��I..�p�G���ؼ�npc..�N�O���H�ؼ�npc
#define         MAIN_AI_BLOCK_MOVE_SKILL    6   //���ʨ�ؼ��I�ϥΧޯ�..�p�G���ؼ�npc..�N�O�����Y�ӥؼ�npc
#define         MAIN_AI_BLOCK_MOVE_TALK     7   //���ʨ�ؼ��I�M���ӬY��npc���
//����AI�����@�Ǫ�^��
#define         ACTION_RETURN_PROC          0   //����L�{��
#define         ACTION_RETURN_OK            1   //���榨�\
#define         ACTION_RETURN_FAIL         -1   //���楢��
//-------------------------------------------------------------------------
typedef	void    (*FNCHANGEAIBLOCK)(SLONG lIndex,SLONG lAIBlock, SLONG d1, SLONG d2, SLONG d3, SLONG d4, SLONG d5);
//-------------------------------------------------------------------------
void    InitAiData(void);
//  NPC��AI�B�z���
void    NpcMainAIproc(SLONG lNpcIndex);
//
void    AIBlockChange(SLONG lIndex, SLONG ai_block);
//--
void    SetChangeCharacterAIBlockFun(SLONG lIndex, FNCHANGEAIBLOCK pFunc);
void    ExecChangeCharacterAIBlockFun(SLONG lIndex,SLONG lAIBlock, SLONG d1, SLONG d2, SLONG d3, SLONG d4, SLONG d5);

//-------------------------------------------------------------------------
//  End.
//-------------------------------------------------------------------------

