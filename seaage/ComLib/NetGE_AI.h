/*
 *	NetGE_AI.cpp
 *      關於遊戲中AI控制的一些函數
 */
 
//----
//  
//---- 
#define    MAX_AI_TYPE         100
#define    MAX_AI_BLOCK_TYPE   256
//----
//  ai類型的定義 
//----
#define         MAIN_AI_CONTROL     0   //玩家控制..AI_BLOCK由玩家給
#define         MAIN_AI_IDLE        1   //IDLE
#define         MAIN_AI_FIGHT_GAD   2   //遊蕩..在地圖上隨機亂走
//----
//  AI_BLOCK類型的定義
//----
#define         MAIN_AI_BLOCK_DUMP          0   //空甚麼都不作
#define         MAIN_AI_BLOCK_IDLE          1   //在原地待機
#define         MAIN_AI_BLOCK_USE_SKILL     2   //在原地使用莫個技能    
#define         MAIN_AI_BLOCK_TALK          3   //在原第和人對話
#define         MAIN_AI_BLOCK_SPOWER        4   //蓄力的AI斷
#define         MAIN_AI_BLOCK_MOVE_TO       5   //移動到莫個目標點..如果有目標npc..就是跟隨目標npc
#define         MAIN_AI_BLOCK_MOVE_SKILL    6   //移動到目標點使用技能..如果有目標npc..就是攻擊某個目標npc
#define         MAIN_AI_BLOCK_MOVE_TALK     7   //移動到目標點和莫個某個npc對話
//關於AI塊的一些返回值
#define         ACTION_RETURN_PROC          0   //執行過程中
#define         ACTION_RETURN_OK            1   //執行成功
#define         ACTION_RETURN_FAIL         -1   //執行失敗
//-------------------------------------------------------------------------
typedef	void    (*FNCHANGEAIBLOCK)(SLONG lIndex,SLONG lAIBlock, SLONG d1, SLONG d2, SLONG d3, SLONG d4, SLONG d5);
//-------------------------------------------------------------------------
void    InitAiData(void);
//  NPC的AI處理函數
void    NpcMainAIproc(SLONG lNpcIndex);
//
void    AIBlockChange(SLONG lIndex, SLONG ai_block);
//--
void    SetChangeCharacterAIBlockFun(SLONG lIndex, FNCHANGEAIBLOCK pFunc);
void    ExecChangeCharacterAIBlockFun(SLONG lIndex,SLONG lAIBlock, SLONG d1, SLONG d2, SLONG d3, SLONG d4, SLONG d5);

//-------------------------------------------------------------------------
//  End.
//-------------------------------------------------------------------------

