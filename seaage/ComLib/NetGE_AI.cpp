/*
 *	NetGE_AI.cpp
 *      關於遊戲中AI控制的一些函數
 */

#include "NetGE_MainFunc.h"

//-------------------------------------------------------------------------
void    NpcMainAIDump(SLONG lIndex);
void    NpcMainAIControl(SLONG lNpcIndex);
void    NpcMainAIIdle(SLONG lIndex);
void    NpcMainAIGad(SLONG lIndex);
//-------------------------------------------------------------------------
SLONG   NpcMainAIBlcokDump(SLONG lIndex);
SLONG   NpcMainAIBlcokIdle(SLONG lIndex);
SLONG   NpcMainAIBlcokMoveTo(SLONG lIndex);
SLONG   NpcMainAIBlcokUseSkill(SLONG lIndex);
SLONG   NpcMainAIBlcokTalk(SLONG lIndex);
SLONG   NpcMainAIBlockSpower(SLONG lIndex);
SLONG   NpcMainAIBlcokMoveAttack(SLONG lIndex);
SLONG   NpcMainAIBlcokMoveTalk(SLONG lIndex);
//------------------------------------------------------------------------
SLONG   NpcAIBlock_MonsterLockAttackNpc(SLONG lIndex);
//-------------------------------------------------------------------------
static  void    DummyChangeCharacterAIBlock(SLONG lIndex,SLONG lAIBlock, SLONG d1, SLONG d2, SLONG d3, SLONG d4,SLONG d5);
//-------------------------------------------------------------------------
void    (*l_AIFun[MAX_AI_TYPE])(SLONG lIndex);
SLONG   (*l_AiBlockFun[MAX_AI_BLOCK_TYPE])(SLONG lIndex);
static	void    (*l_ChangeCharacterAIBlock[MAX_AI_BLOCK_TYPE]) (SLONG lIndex,SLONG lAIBlock, SLONG d1, SLONG d2, SLONG d3, SLONG d4, SLONG d5);
//-------------------------------------------------------------------------
//  使用該ai 過程需要注意到的東西
//      1.在 npc所有的DoingKind都需要返回到IDLE狀態
//      2.
//-------------------------------------------------------------------------
void    InitAiData(void)
{
    SLONG   i;
    SLONG   block;
    //
    for (i=0; i<MAX_AI_TYPE; i++)
        l_AIFun[i] = NpcMainAIDump;
    //        
    l_AIFun[MAIN_AI_CONTROL] = NpcMainAIControl;//玩家控制..AI_BLOCK由玩家給
    l_AIFun[MAIN_AI_IDLE] = NpcMainAIIdle;
    l_AIFun[MAIN_AI_FIGHT_GAD] = NpcMainAIGad;
    //
    for (i=0; i<MAX_AI_BLOCK_TYPE; i++)
    {
        //l_AiBlockFun[i] = NpcMainAIBlcokDump;
        l_AiBlockFun[i] = NpcMainAIBlcokIdle;
        l_ChangeCharacterAIBlock[i] = DummyChangeCharacterAIBlock;
    }
    //
    block = MAIN_AI_BLOCK_IDLE;//在原地待機
    l_AiBlockFun[block] = NpcMainAIBlcokIdle;
    //
    block = MAIN_AI_BLOCK_USE_SKILL;//在原地使用莫個技能    
    l_AiBlockFun[block] = NpcMainAIBlcokUseSkill;
    //
    
    block = MAIN_AI_BLOCK_TALK;//在原第和人對話
    l_AiBlockFun[block] = NpcMainAIBlcokTalk;
    //
    block = MAIN_AI_BLOCK_SPOWER;//蓄力的AI斷
    l_AiBlockFun[block] = NpcMainAIBlockSpower;
    //
    block = MAIN_AI_BLOCK_MOVE_TO;//移動到莫個目標點..如果有目標npc..就是跟隨目標npc
    l_AiBlockFun[block] = NpcMainAIBlcokMoveTo;
    //
    
    block = MAIN_AI_BLOCK_MOVE_SKILL;//移動到目標點使用技能..如果有目標npc..就是攻擊某個目標npc
    l_AiBlockFun[block] = NpcMainAIBlcokMoveAttack;
    //
    
    block = MAIN_AI_BLOCK_MOVE_TALK;//移動到目標點和莫個某個npc對話    
    l_AiBlockFun[block] = NpcMainAIBlcokMoveTalk;
    //
    
}
//----
//  NPC的AI處理函數
//----
void    NpcMainAIproc(SLONG lIndex)
{
    SLONG   AI;
    //
    LOCK_CHARACTER(lIndex);
    AI = GetCharacterAI(lIndex);
    UNLOCK_CHARACTER(lIndex);
    //
    if (AI>=0 && AI<MAX_AI_TYPE )
    {
        l_AIFun[AI](lIndex);
    }
    //
    return;
}
//---
//
//---
void    NpcMainAIDump(SLONG lIndex)
{
    return ;
}
//---
//  玩家控制的AI
//---
void    NpcMainAIControl(SLONG lIndex)
{
    SLONG   AI_block;
    //
    LOCK_CHARACTER(lIndex);
    AI_block = GetCharacterAIBlock(lIndex);
    UNLOCK_CHARACTER(lIndex);
    //玩家控制...直接執行需要的ai_block
    if (AI_block>=0 && AI_block<MAX_AI_BLOCK_TYPE)    
    {    
        switch (l_AiBlockFun[AI_block](lIndex))
        {
        case ACTION_RETURN_PROC:
            break;
        case ACTION_RETURN_OK:
        case ACTION_RETURN_FAIL:
            if (AI_block != MAIN_AI_BLOCK_IDLE)
            {
                LOCK_CHARACTER(lIndex);
                AIBlockChange(lIndex, MAIN_AI_BLOCK_IDLE);
                UNLOCK_CHARACTER(lIndex);
            }                
            break;
        }
    }        
}
//----
//
//----
void    NpcMainAIIdle(SLONG lIndex)
{
    SLONG   AI_block;
    SLONG   d1, d2, d3, d4, d5;
    //
    LOCK_CHARACTER(lIndex);
    AI_block = GetCharacterAIBlock(lIndex);
    UNLOCK_CHARACTER(lIndex);
    //    
    switch (AI_block)
    {
    case MAIN_AI_BLOCK_IDLE:        //在原地待機
        break;
    default:
        //.....客戶端甚麼都不作
        //.....服務器端需要改變AI_BLOCK...給一個隨機會時間在原地IDLE
        d1 = d2 = d3 = d4 = d5 = 0;
        //
        ExecChangeCharacterAIBlockFun(lIndex, MAIN_AI_BLOCK_IDLE, d1, d2, d3, d4, d5);
        break;
    }
}        
//---
//  隨機亂走的AI
//---
void    NpcMainAIGad(SLONG lIndex)
{
    enum
    {
		GAD_RAND_X		    =   300,    //隨機移動的範圍
		GAD_RAND_Y			=   250,
		GAD_RAND_TICKS		=   400,        
    };
    SLONG   total_ticks, ticks;
    SLONG   AI_block;
    SLONG   x, y, z;
    SLONG   temp_x, temp_y;
    SLONG   d1,d2,d3,d4,d5;
    SLONG   ai_block_ret;
    //
    LOCK_CHARACTER(lIndex);
    AI_block = GetCharacterAIBlock(lIndex);
    ticks = GetCharacterGadTicks(lIndex);
    total_ticks = GetCharacterGadTotalTicks(lIndex);
    GetCharacterPosition(lIndex, &x, &y, &z);    
    UNLOCK_CHARACTER(lIndex);
    
    //玩家控制...直接執行需要的ai_block
    if (AI_block>=0 && AI_block<MAX_AI_BLOCK_TYPE)    
    {    
        ai_block_ret = l_AiBlockFun[AI_block](lIndex);
        switch (AI_block)
        {
        case MAIN_AI_BLOCK_IDLE:        //在原地待機
            //
            if (FALSE == NpcAIBlock_MonsterLockAttackNpc(lIndex))
            {
                //
                ticks ++;
                LOCK_CHARACTER(lIndex);
                SetCharacterGadTicks(lIndex, ticks);
                UNLOCK_CHARACTER(lIndex);                                    
                //
                if (ticks >= total_ticks)
                {
                    //IDLE 的時間結束了
                    //.....客戶端甚麼都不作
                    //.....服務器端需要改變AI_BLOCK...移動到一個隨機的位置
                    //過一段時間需要到處動一下下..
                    temp_x = x + ( system_rand() % GAD_RAND_X ) * ( 1 - (system_rand() % 2) * 2 );
                    temp_y = y + ( system_rand() % GAD_RAND_Y ) * ( 1 - (system_rand() % 2) * 2 );
                    //
                    //
                    d1 = -1;
                    d2 = temp_x;
                    d3 = temp_y;
                    d4 = 0;
                    d5 = 0;
                    //
                    ExecChangeCharacterAIBlockFun(lIndex, MAIN_AI_BLOCK_MOVE_TO, d1, d2, d3, d4, d5);
                }
                else
                {
                    //繼續IDLE..甚麼都不作
                }
            }
            break;
        case MAIN_AI_BLOCK_MOVE_TO:     //移動到莫個目標點..如果有目標npc..就是跟隨目標npc
            if (FALSE == NpcAIBlock_MonsterLockAttackNpc(lIndex))
            {
                switch (ai_block_ret)
                {
                case ACTION_RETURN_PROC:
                    //繼續IDLE..甚麼都不作
                    break;
                case ACTION_RETURN_OK:
                case ACTION_RETURN_FAIL:                
                    //.....客戶端甚麼都不作
                    //.....服務器端需要改變AI_BLOCK...給一個隨機會時間在原地IDLE
                    total_ticks = GAD_RAND_TICKS + system_rand() % GAD_RAND_TICKS; 
                    //
                    LOCK_CHARACTER(lIndex);
                    SetCharacterGadTicks(lIndex, 0);
                    SetCharacterGadTotalTicks(lIndex, total_ticks);
                    UNLOCK_CHARACTER(lIndex);                    
                    //
                    d1 = -1;
                    d2 = d3 = d4 = d5 = 0;
                    //
                    ExecChangeCharacterAIBlockFun(lIndex, MAIN_AI_BLOCK_IDLE, d1, d2, d3, d4, d5);                                    
                    break;
                }                    
            }
            break;
        case MAIN_AI_BLOCK_MOVE_SKILL://移動到目標點使用技能..如果有目標npc..就是攻擊某個目標npc        
            switch (ai_block_ret)
            {
            case ACTION_RETURN_PROC:
                //繼續IDLE..甚麼都不作
                break;
            case ACTION_RETURN_FAIL://攻擊失敗
            case ACTION_RETURN_OK:            
                //.....客戶端甚麼都不作
                //.....服務器端需要改變AI_BLOCK...給一個隨機會時間在原地IDLE            
                total_ticks = GAD_RAND_TICKS + system_rand() % GAD_RAND_TICKS; 
                //
                LOCK_CHARACTER(lIndex);
                SetCharacterGadTicks(lIndex, 0);
                SetCharacterGadTotalTicks(lIndex, total_ticks);
                //失敗清空目標NPC
                SetCharacterDestID(lIndex, -1);
                UNLOCK_CHARACTER(lIndex);                    
                //                
                d1 = -1;
                d2 = d3 = d4 = d5 = 0;
                //
                ExecChangeCharacterAIBlockFun(lIndex, MAIN_AI_BLOCK_IDLE, d1, d2, d3, d4, d5);            
                break;
            }                            
            break;
        default:    
            //.....客戶端甚麼都不作
            //.....服務器端需要改變AI_BLOCK...給一個隨機會時間在原地IDLE
            total_ticks = system_rand() % GAD_RAND_TICKS;
            //
            LOCK_CHARACTER(lIndex);
            SetCharacterGadTicks(lIndex, 0);
            SetCharacterGadTotalTicks(lIndex, total_ticks);
            UNLOCK_CHARACTER(lIndex); 
            //
            d1 = -1;
            d2 = d3 = d4 = d5 = 0;
            //
            ExecChangeCharacterAIBlockFun(lIndex, MAIN_AI_BLOCK_IDLE, d1, d2, d3, d4, d5);
            break;        
        }        
    }      
    //
    return;
}
//-------------------------------------------------------------------------
//  NPC的AI_BLOCK處理函數
//-------------------------------------------------------------------------
SLONG   NpcMainAIBlcokDump(SLONG lIndex)
{
    //甚麼都不作..
    return ACTION_RETURN_PROC;
}
//----
//
//----
SLONG   NpcMainAIBlcokIdle(SLONG lIndex)
{   
    SLONG   doing_kind, new_doing_kind;
    SLONG   selfbreak_flag;
    //判斷npc當前的doingkind是否是idle
    LOCK_CHARACTER(lNpcIndex);
    doing_kind = GetCharacterDoingKind(lIndex);    
    selfbreak_flag = IsCharacterSelfDoingKindBreak(lIndex);
    UNLOCK_CHARACTER(lNpcIndex);
    //
    new_doing_kind = DOING_KIND_IDLE;
    //判斷該npc動作能否被中斷...
    if ( new_doing_kind != doing_kind)
    {
        //改變到待機狀態
        if (selfbreak_flag)
        {
            doing_kind = new_doing_kind;
            //
            LOCK_CHARACTER(lIndex);
            //改變狀態到待機狀態
            ExecChangeCharacterDoingSomethingFun(lIndex, doing_kind, 0, 0,0,0,0,0);
            UNLOCK_CHARACTER(lNpcIndex);
        }
    }
    //調用對應的doingkind處理函數
    ExecCharacterDoingSomething(lIndex, doing_kind);
    //待機只有一種返回狀態
    return ACTION_RETURN_PROC;
}
//----
//
//----
SLONG   NpcMainAIBlcokMoveTo(SLONG lIndex)
{
    SLONG   doing_kind, new_doing_kind;
    SLONG   selfbreak_flag;    
    SLONG   dx, dy, dz;
    SLONG   des_no;    
    SLONG   magic_no;
    SLONG   d1, d2, d3, d4, d5;
    SLONG   ret = ACTION_RETURN_PROC;
    //
    LOCK_CHARACTER(lNpcIndex);
    doing_kind = GetCharacterDoingKind(lIndex);    
    selfbreak_flag = IsCharacterSelfDoingKindBreak(lIndex);
    GetCharacterDestPosition(lIndex, &dx, &dy, &dz);
    des_no = GetCharacterDestID(lIndex);
    magic_no = GetCharacterDoingMagic(lIndex);
    UNLOCK_CHARACTER(lNpcIndex);
    //
    if (des_no >= 0)
    {
        LOCK_CHARACTER(des_no);
        GetCharacterPosition(des_no, &dx, &dy, &dz);
        UNLOCK_CHARACTER(des_no);
    }    
    //
    new_doing_kind = DOING_KIND_MOVE_TO;
    //判斷是否處於移動的狀態
    if (new_doing_kind != doing_kind)
    {
        //改變到移動狀態
        if (selfbreak_flag)
        {
            d1 = dx;
            d2 = dy;
            d3 = d4 = 0;        
            d5 = magic_no;
            //改變到移動狀態
            doing_kind = new_doing_kind;
            LOCK_CHARACTER(lIndex);
            ExecChangeCharacterDoingSomethingFun(lIndex, doing_kind, 0, d1, d2, d3, d4, d5);
            UNLOCK_CHARACTER(lNpcIndex);
        }
    }
    //調用對應的doingkind處理函數
    ret = ExecCharacterDoingSomething(lIndex, doing_kind);
    //更具doingkind的返回值..確定..需要的返回值
    return ret;
}
//----
//  使用技能的..過程需要...(攻擊..喘息)
//----
SLONG   NpcMainAIBlcokUseSkill(SLONG lIndex)
{
    enum
    {
        MOVE_SPEED_TIMES            =   5,  //移動速度是正常移動速度的倍數
    };
    //
    SLONG   doing_kind, new_doing_kind, sill_can_use_flag;
    SLONG   selfbreak_flag;
    SLONG   move_speed;
    SLONG   magic_no, magic_level;
    SLONG   dx, dy, dz;
    SLONG   des_no; 
    SLONG   clash_dist;
    SLONG   d1, d2, d3, d4, d5;
    SLONG   ret = ACTION_RETURN_PROC;
    //判斷npc當前的doingkind是否是idle
    LOCK_CHARACTER(lNpcIndex);
    move_speed = GetCharacterMoveSpeed(lIndex);
    doing_kind = GetCharacterDoingKind(lIndex);    
    selfbreak_flag = IsCharacterSelfDoingKindBreak(lIndex);
    GetCharacterDestPosition(lIndex, &dx, &dy, &dz);
    magic_no = GetCharacterDoingMagic(lIndex);
    magic_level = GetCharacterSpecialSkillLevel(lIndex, magic_no);
    des_no = GetCharacterDestID(lIndex);    
    UNLOCK_CHARACTER(lNpcIndex);
    //
    clash_dist = GetSkillMagicFlyDistance(magic_no, magic_level);
    //
    if (des_no>=0)
    {
        LOCK_CHARACTER(des_no);
        GetCharacterPosition(des_no, &dx, &dy, &dz);
        UNLOCK_CHARACTER(des_no);
    }
    //使用技能前..需要判定..該技能能否使用
    sill_can_use_flag = IsSkillMouseDownCanUse(lIndex, magic_no, magic_level, des_no);
    //
    if (sill_can_use_flag)
        new_doing_kind = GetSkillNeedDoingKind(magic_no);    
    else
        new_doing_kind = DOING_KIND_IDLE;
    //判斷該npc動作能否被中斷...
    //改變到待機狀態
    if (doing_kind != new_doing_kind) 
    {
        if (selfbreak_flag)
        {
            switch(new_doing_kind)
            {
            case DOING_KIND_CLASH:
                // d1   移動到的目標座標  x
                // d2   移動到的目標座標  y
                // d3   移動到的目標座標  z
                // d4   經過的步數
                // d5   但前使用的技能
                d1 = dx;
                d2 = dy;
                d3 = 0;
                //衝撞的時候..速度是正常時候的5倍
                if (move_speed<=0)
                    move_speed = 0;
                d4 = (SLONG)(1.0 * clash_dist /(move_speed * MOVE_SPEED_TIMES) +0.5);
                d5 = magic_no;
                break;
            case DOING_KIND_SEQUENTIAL_ATTACK_NPC:
                // d1   目標npc
                // d2   無特別意義
                // d3   無特別意義
                // d4   無特別意義
                // d5   但前使用的技能
                d1 = des_no;
                d2 = dx;
                d3 = dy;
                d4 = dz;
                d5 = magic_no;
                break;
            default:
                d1 = des_no;
                d2 = dx;
                d3 = dy;
                d4 = dz;
                d5 = magic_no;
                break;
            }
            //
            //
            doing_kind = new_doing_kind;            
            //改變到對應的釋放法術的doingkind
            LOCK_CHARACTER(lIndex);
            ExecChangeCharacterDoingSomethingFun(lIndex, doing_kind, 0, d1, d2, d3, d4, d5);
            UNLOCK_CHARACTER(lNpcIndex);
            //
        }
    }    
    //調用對應的doingkind處理函數
    ret = ExecCharacterDoingSomething(lIndex, doing_kind);
    if (!sill_can_use_flag)//如果技能不能使用返回失敗
        ret = ACTION_RETURN_FAIL;
    //
    return ret;    
}
//----
//  處在蓄力的階段
//----
SLONG   NpcMainAIBlockSpower(SLONG lIndex)
{
    SLONG   doing_kind, new_doing_kind;
    SLONG   selfbreak_flag;
    SLONG   magic_no, magic_level;
    //判斷npc當前的doingkind是否是idle
    LOCK_CHARACTER(lNpcIndex);
    doing_kind = GetCharacterDoingKind(lIndex);    
    selfbreak_flag = IsCharacterSelfDoingKindBreak(lIndex);
    magic_no = GetCharacterDoingMagic(lIndex);
    magic_level = GetCharacterSpecialSkillLevel(lIndex, magic_no);
    UNLOCK_CHARACTER(lNpcIndex);
    //
    new_doing_kind = DOING_KIND_SPOWER;
    //判斷該npc動作能否被中斷...
    if ( new_doing_kind != doing_kind)
    {
        //改變到待機狀態
        if (selfbreak_flag)
        {
            doing_kind = new_doing_kind;
            LOCK_CHARACTER(lIndex);
            //改變狀態到待機狀態
            ExecChangeCharacterDoingSomethingFun(lIndex, doing_kind, 0, 0,0,0,0,0);
            //蓄力數據初始化
            FightPrepareSpower(lIndex, magic_no, magic_level);
            UNLOCK_CHARACTER(lNpcIndex);
        }
    }
    //調用對應的doingkind處理函數
    ExecCharacterDoingSomething(lIndex, doing_kind);
    //待機只有一種返回狀態
    return ACTION_RETURN_PROC;
}
//----
//  和人對話的doingkind
//----
SLONG   NpcMainAIBlcokTalk(SLONG lIndex)
{
    SLONG   doing_kind, new_doing_kind;
    SLONG   selfbreak_flag;
    SLONG   d1, d2, d3, d4, d5;
    SLONG   des_no;
    SLONG   ret = ACTION_RETURN_PROC;
    //判斷npc當前的doingkind是否是idle
    LOCK_CHARACTER(lNpcIndex);
    doing_kind = GetCharacterDoingKind(lIndex);    
    selfbreak_flag = IsCharacterSelfDoingKindBreak(lIndex);
    des_no = GetCharacterDestID(lIndex);        
    UNLOCK_CHARACTER(lNpcIndex);
    //
    new_doing_kind = DOING_KIND_TALK_WITH_NPC;
    //判斷該npc動作能否被中斷...
    //改變到待機狀態
    if (doing_kind != new_doing_kind)
    {
        if (selfbreak_flag)
        {
            d1 = des_no;
            d2 = 0;
            d3 = 0;
            d4 = 0;
            d5 = 0;
            //改變到對應的釋放法術的doingkind
            doing_kind = new_doing_kind;
            LOCK_CHARACTER(lIndex);            
            ExecChangeCharacterDoingSomethingFun(lIndex, doing_kind, 0, d1, d2, d3, d4, d5);
            UNLOCK_CHARACTER(lNpcIndex);
            //
        }
    }    
    //調用對應的doingkind處理函數
    ret = ExecCharacterDoingSomething(lIndex, doing_kind);
    //
    return ret ;

}
//----
//  追擊
//----
SLONG   NpcMainAIBlcokMoveAttack(SLONG lIndex)
{
    SLONG   doingkind;
    SLONG   selfbreak_flag;    
    SLONG   magic_no, magic_level;
    SLONG   magic_dis;
    SLONG   x, y, z;
    SLONG   dx, dy, dz;
    SLONG   des_no;
    SLONG   dest;
    SLONG   sight;
    SLONG   ret = ACTION_RETURN_PROC;    
    //
    LOCK_CHARACTER(lIndex);
    doingkind = GetCharacterDoingKind(lIndex);    
    selfbreak_flag = IsCharacterSelfDoingKindBreak(lIndex);
    magic_no = GetCharacterDoingMagic(lIndex);
    magic_level = GetCharacterSpecialSkillLevel(lIndex, magic_no);
    GetCharacterPosition(lIndex, &x, &y, &z);
    GetCharacterDestPosition(lIndex, &dx, &dy, &dz);
    des_no = GetCharacterDestID(lIndex);
    sight = GetCharacterSightRange(lIndex);
    UNLOCK_CHARACTER(lIndex);
    //
    if (des_no>=0)
    {
        LOCK_CHARACTER(des_no);
        GetCharacterPosition(des_no, &dx, &dy, &dz);
        UNLOCK_CHARACTER(des_no);
    }
    //
    dest = (SLONG)sqrt((x-dx)*(x-dx) + (y-dy)*(y-dy));
    //
    magic_dis = GetSkillMagicDisChargeDistance(magic_no, magic_level);
    //
    if (dest <= sight ) 
    {
        // 在自己的視線內
        if (dest <= magic_dis)
        {
            //在施法的距離內
            //          調用使用技能的AI_BLOCK
            ret = NpcMainAIBlcokUseSkill(lIndex);
        }
        else
        {
            //在施法的距離外
            //      調用..移動的AI_BLOCK
            ret = NpcMainAIBlcokMoveTo(lIndex);
        }
    }
    else
    {
        // 在自己的視線外
        //調用IDLE_BLOCK
        NpcMainAIBlcokIdle(lIndex);
        //
        ret = ACTION_RETURN_FAIL;
    }
    //
    return ret;
}
SLONG   NpcMainAIBlcokMoveTalk(SLONG lIndex)
{
    enum
    {   
        NEAR_DISTANCE               =   80,
    };
    SLONG   doingkind;
    SLONG   selfbreak_flag;    
    SLONG   x, y, z;
    SLONG   dx, dy, dz;
    SLONG   des_no;
    SLONG   dest;
    SLONG   ret = ACTION_RETURN_PROC;
    //
    LOCK_CHARACTER(lIndex);
    doingkind = GetCharacterDoingKind(lIndex);    
    selfbreak_flag = IsCharacterSelfDoingKindBreak(lIndex);
    GetCharacterDestPosition(lIndex, &dx, &dy, &dz);
    GetCharacterPosition(lIndex, &x, &y, &z);
    des_no = GetCharacterDestID(lIndex);
    UNLOCK_CHARACTER(lIndex);
    //
    if (des_no>=0)
    {
        LOCK_CHARACTER(des_no);
        GetCharacterPosition(des_no, &dx, &dy, &dz);
        UNLOCK_CHARACTER(des_no);
    }
    //
    dest = (SLONG)sqrt((x-dx)*(x-dx) + (y-dy)*(y-dy));
    // 在自己的視線內
    if (dest <= NEAR_DISTANCE)
    {
        ret = NpcMainAIBlcokTalk(lIndex);
    }
    else
    {
        //在施法的距離外
        //      調用..移動的AI_BLOCK
        ret = NpcMainAIBlcokMoveTo(lIndex);
    }
    //
    return ret;
}
//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------
SLONG   NpcAIBlock_MonsterLockAttackNpc(SLONG lIndex)
{
    SLONG   ret = FALSE;
    SLONG   dest_can_attack_flag;
    SLONG   dest_npc;
    SLONG   d1, d2, d3, d4, d5;
    SLONG   use_magic_no;
    //
    LOCK_CHARACTER(lIndex);
    dest_npc = GetCharacterDestID(lIndex);
    use_magic_no = get_can_use_skill_to_attack(lIndex, dest_npc);
    UNLOCK_CHARACTER(lIndex);    
    //
    if (dest_npc>=0) 
    {
        LOCK_CHARACTER(dest_npc);
        dest_can_attack_flag = IsCharacterCanAttackMonsterCheck(dest_npc);
        UNLOCK_CHARACTER(dest_npc);            
        //
        if (!dest_can_attack_flag)
            dest_npc = -1;
    }
    //
    if (dest_npc<0) 
    {
        dest_npc = search_near_target_npc(lIndex);
    }
    if(dest_npc >= 0) //判斷視線內有敵人
    {
        //.....客戶端甚麼都不作
        //.....服務器端需要改變AI_BLOCK...攻擊敵人...結束...為npc選擇一個使用的技能
        d1 = dest_npc;
        d2 = d3 = d4 = 0;
        d5 = use_magic_no;
        //
        ExecChangeCharacterAIBlockFun(lIndex, MAIN_AI_BLOCK_MOVE_SKILL, d1, d2, d3, d4, d5);
        //
        ret = TRUE;
    }    
    //
    LOCK_CHARACTER(lIndex);
    SetCharacterDestID(lIndex, dest_npc);
    UNLOCK_CHARACTER(lIndex);    
    //
    return ret;
}
//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------
static  void    AIBlockAbort(SLONG lIndex)
{
    SLONG   AIBlock;
    SLONG   Skill, SkillLevel;
    //
    AIBlock = GetCharacterAIBlock(lIndex);
    Skill   = GetCharacterLandRightSkill(lIndex);
    SkillLevel = GetCharacterSpecialSkillLevel(lIndex, Skill);
    //
    switch (AIBlock)
    {
    case MAIN_AI_BLOCK_DUMP:        //空甚麼都不作
        break;
    case MAIN_AI_BLOCK_IDLE:        //在原地待機
        break;    
    case MAIN_AI_BLOCK_USE_SKILL:   //在原地使用莫個技能    
        break;    
    case MAIN_AI_BLOCK_TALK:        //在原第和人對話
        break;    
    case MAIN_AI_BLOCK_SPOWER:      //蓄力的AI斷
        FightAbortSpower(lIndex, Skill, SkillLevel);
        break;    
    case MAIN_AI_BLOCK_MOVE_TO:     //移動到莫個目標點..如果有目標npc..就是跟隨目標npc
        break;    
    case MAIN_AI_BLOCK_MOVE_SKILL:  //移動到目標點使用技能..如果有目標npc..就是攻擊某個目標npc
        break;    
    case MAIN_AI_BLOCK_MOVE_TALK:   //移動到目標點和莫個某個npc對話    
        break;    
    }
}
//---
//  使用在 Character 需要在改變他的AI_BLOCK的時候調用...在AI  處理中..需要改變 AI_BLOCK不要調用這個!!!
//---
void    AIBlockChange(SLONG lIndex, SLONG ai_block)
{
    AIBlockAbort(lIndex);
    SetCharacterAIBlock(lIndex, ai_block);
}
//----
//
//----
void    AIBlockPrepareChangeAIBlockParament(SLONG doing_kind, SLONG des_npc, SLONG dx, SLONG dy, 
                                              SLONG *d1, SLONG *d2, SLONG *d3, SLONG *d4, SLONG *d5)
{
    
}
//----
//
//----
static  void    DummyChangeCharacterAIBlock(SLONG lIndex,SLONG lAIBlock, SLONG d1, SLONG d2, SLONG d3, SLONG d4,SLONG d5)
{
}
//----
//
//----
void    SetChangeCharacterAIBlockFun(SLONG lIndex, FNCHANGEAIBLOCK pFunc)
{
    if (lIndex>=0 && lIndex<=MAX_AI_BLOCK_TYPE)
        l_ChangeCharacterAIBlock[lIndex] = pFunc;
}
//----
//  該函數是用在 AI 處理的時候..在..多個AI_BLOCK跳轉的時候使用..
//----
void    ExecChangeCharacterAIBlockFun(SLONG lIndex,SLONG lAIBlock, SLONG d1, SLONG d2, SLONG d3, SLONG d4, SLONG d5)
{
    if (lAIBlock>=0 && lAIBlock<=MAX_AI_BLOCK_TYPE)
    {
        l_ChangeCharacterAIBlock[lAIBlock](lIndex, lAIBlock, d1, d2, d3, d4, d5);
    }
}
//----
//
//----
//-------------------------------------------------------------------------
//  End.
//-------------------------------------------------------------------------

