/*
 *	NetGE_AI.cpp
 *      ����C����AI����@�Ǩ��
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
//  �ϥθ�ai �L�{�ݭn�`�N�쪺�F��
//      1.�b npc�Ҧ���DoingKind���ݭn��^��IDLE���A
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
    l_AIFun[MAIN_AI_CONTROL] = NpcMainAIControl;//���a����..AI_BLOCK�Ѫ��a��
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
    block = MAIN_AI_BLOCK_IDLE;//�b��a�ݾ�
    l_AiBlockFun[block] = NpcMainAIBlcokIdle;
    //
    block = MAIN_AI_BLOCK_USE_SKILL;//�b��a�ϥβ��ӧޯ�    
    l_AiBlockFun[block] = NpcMainAIBlcokUseSkill;
    //
    
    block = MAIN_AI_BLOCK_TALK;//�b��ĩM�H���
    l_AiBlockFun[block] = NpcMainAIBlcokTalk;
    //
    block = MAIN_AI_BLOCK_SPOWER;//�W�O��AI�_
    l_AiBlockFun[block] = NpcMainAIBlockSpower;
    //
    block = MAIN_AI_BLOCK_MOVE_TO;//���ʨ���ӥؼ��I..�p�G���ؼ�npc..�N�O���H�ؼ�npc
    l_AiBlockFun[block] = NpcMainAIBlcokMoveTo;
    //
    
    block = MAIN_AI_BLOCK_MOVE_SKILL;//���ʨ�ؼ��I�ϥΧޯ�..�p�G���ؼ�npc..�N�O�����Y�ӥؼ�npc
    l_AiBlockFun[block] = NpcMainAIBlcokMoveAttack;
    //
    
    block = MAIN_AI_BLOCK_MOVE_TALK;//���ʨ�ؼ��I�M���ӬY��npc���    
    l_AiBlockFun[block] = NpcMainAIBlcokMoveTalk;
    //
    
}
//----
//  NPC��AI�B�z���
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
//  ���a���AI
//---
void    NpcMainAIControl(SLONG lIndex)
{
    SLONG   AI_block;
    //
    LOCK_CHARACTER(lIndex);
    AI_block = GetCharacterAIBlock(lIndex);
    UNLOCK_CHARACTER(lIndex);
    //���a����...��������ݭn��ai_block
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
    case MAIN_AI_BLOCK_IDLE:        //�b��a�ݾ�
        break;
    default:
        //.....�Ȥ�ݬƻ򳣤��@
        //.....�A�Ⱦ��ݻݭn����AI_BLOCK...���@���H���|�ɶ��b��aIDLE
        d1 = d2 = d3 = d4 = d5 = 0;
        //
        ExecChangeCharacterAIBlockFun(lIndex, MAIN_AI_BLOCK_IDLE, d1, d2, d3, d4, d5);
        break;
    }
}        
//---
//  �H���è���AI
//---
void    NpcMainAIGad(SLONG lIndex)
{
    enum
    {
		GAD_RAND_X		    =   300,    //�H�����ʪ��d��
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
    
    //���a����...��������ݭn��ai_block
    if (AI_block>=0 && AI_block<MAX_AI_BLOCK_TYPE)    
    {    
        ai_block_ret = l_AiBlockFun[AI_block](lIndex);
        switch (AI_block)
        {
        case MAIN_AI_BLOCK_IDLE:        //�b��a�ݾ�
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
                    //IDLE ���ɶ������F
                    //.....�Ȥ�ݬƻ򳣤��@
                    //.....�A�Ⱦ��ݻݭn����AI_BLOCK...���ʨ�@���H������m
                    //�L�@�q�ɶ��ݭn��B�ʤ@�U�U..
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
                    //�~��IDLE..�ƻ򳣤��@
                }
            }
            break;
        case MAIN_AI_BLOCK_MOVE_TO:     //���ʨ���ӥؼ��I..�p�G���ؼ�npc..�N�O���H�ؼ�npc
            if (FALSE == NpcAIBlock_MonsterLockAttackNpc(lIndex))
            {
                switch (ai_block_ret)
                {
                case ACTION_RETURN_PROC:
                    //�~��IDLE..�ƻ򳣤��@
                    break;
                case ACTION_RETURN_OK:
                case ACTION_RETURN_FAIL:                
                    //.....�Ȥ�ݬƻ򳣤��@
                    //.....�A�Ⱦ��ݻݭn����AI_BLOCK...���@���H���|�ɶ��b��aIDLE
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
        case MAIN_AI_BLOCK_MOVE_SKILL://���ʨ�ؼ��I�ϥΧޯ�..�p�G���ؼ�npc..�N�O�����Y�ӥؼ�npc        
            switch (ai_block_ret)
            {
            case ACTION_RETURN_PROC:
                //�~��IDLE..�ƻ򳣤��@
                break;
            case ACTION_RETURN_FAIL://��������
            case ACTION_RETURN_OK:            
                //.....�Ȥ�ݬƻ򳣤��@
                //.....�A�Ⱦ��ݻݭn����AI_BLOCK...���@���H���|�ɶ��b��aIDLE            
                total_ticks = GAD_RAND_TICKS + system_rand() % GAD_RAND_TICKS; 
                //
                LOCK_CHARACTER(lIndex);
                SetCharacterGadTicks(lIndex, 0);
                SetCharacterGadTotalTicks(lIndex, total_ticks);
                //���ѲM�ťؼ�NPC
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
            //.....�Ȥ�ݬƻ򳣤��@
            //.....�A�Ⱦ��ݻݭn����AI_BLOCK...���@���H���|�ɶ��b��aIDLE
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
//  NPC��AI_BLOCK�B�z���
//-------------------------------------------------------------------------
SLONG   NpcMainAIBlcokDump(SLONG lIndex)
{
    //�ƻ򳣤��@..
    return ACTION_RETURN_PROC;
}
//----
//
//----
SLONG   NpcMainAIBlcokIdle(SLONG lIndex)
{   
    SLONG   doing_kind, new_doing_kind;
    SLONG   selfbreak_flag;
    //�P�_npc��e��doingkind�O�_�Oidle
    LOCK_CHARACTER(lNpcIndex);
    doing_kind = GetCharacterDoingKind(lIndex);    
    selfbreak_flag = IsCharacterSelfDoingKindBreak(lIndex);
    UNLOCK_CHARACTER(lNpcIndex);
    //
    new_doing_kind = DOING_KIND_IDLE;
    //�P�_��npc�ʧ@��_�Q���_...
    if ( new_doing_kind != doing_kind)
    {
        //���ܨ�ݾ����A
        if (selfbreak_flag)
        {
            doing_kind = new_doing_kind;
            //
            LOCK_CHARACTER(lIndex);
            //���ܪ��A��ݾ����A
            ExecChangeCharacterDoingSomethingFun(lIndex, doing_kind, 0, 0,0,0,0,0);
            UNLOCK_CHARACTER(lNpcIndex);
        }
    }
    //�եι�����doingkind�B�z���
    ExecCharacterDoingSomething(lIndex, doing_kind);
    //�ݾ��u���@�ت�^���A
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
    //�P�_�O�_�B�󲾰ʪ����A
    if (new_doing_kind != doing_kind)
    {
        //���ܨ첾�ʪ��A
        if (selfbreak_flag)
        {
            d1 = dx;
            d2 = dy;
            d3 = d4 = 0;        
            d5 = magic_no;
            //���ܨ첾�ʪ��A
            doing_kind = new_doing_kind;
            LOCK_CHARACTER(lIndex);
            ExecChangeCharacterDoingSomethingFun(lIndex, doing_kind, 0, d1, d2, d3, d4, d5);
            UNLOCK_CHARACTER(lNpcIndex);
        }
    }
    //�եι�����doingkind�B�z���
    ret = ExecCharacterDoingSomething(lIndex, doing_kind);
    //���doingkind����^��..�T�w..�ݭn����^��
    return ret;
}
//----
//  �ϥΧޯ઺..�L�{�ݭn...(����..�ݮ�)
//----
SLONG   NpcMainAIBlcokUseSkill(SLONG lIndex)
{
    enum
    {
        MOVE_SPEED_TIMES            =   5,  //���ʳt�׬O���`���ʳt�ת�����
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
    //�P�_npc��e��doingkind�O�_�Oidle
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
    //�ϥΧޯ�e..�ݭn�P�w..�ӧޯ��_�ϥ�
    sill_can_use_flag = IsSkillMouseDownCanUse(lIndex, magic_no, magic_level, des_no);
    //
    if (sill_can_use_flag)
        new_doing_kind = GetSkillNeedDoingKind(magic_no);    
    else
        new_doing_kind = DOING_KIND_IDLE;
    //�P�_��npc�ʧ@��_�Q���_...
    //���ܨ�ݾ����A
    if (doing_kind != new_doing_kind) 
    {
        if (selfbreak_flag)
        {
            switch(new_doing_kind)
            {
            case DOING_KIND_CLASH:
                // d1   ���ʨ쪺�ؼЮy��  x
                // d2   ���ʨ쪺�ؼЮy��  y
                // d3   ���ʨ쪺�ؼЮy��  z
                // d4   �g�L���B��
                // d5   ���e�ϥΪ��ޯ�
                d1 = dx;
                d2 = dy;
                d3 = 0;
                //�ļ����ɭ�..�t�׬O���`�ɭԪ�5��
                if (move_speed<=0)
                    move_speed = 0;
                d4 = (SLONG)(1.0 * clash_dist /(move_speed * MOVE_SPEED_TIMES) +0.5);
                d5 = magic_no;
                break;
            case DOING_KIND_SEQUENTIAL_ATTACK_NPC:
                // d1   �ؼ�npc
                // d2   �L�S�O�N�q
                // d3   �L�S�O�N�q
                // d4   �L�S�O�N�q
                // d5   ���e�ϥΪ��ޯ�
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
            //���ܨ����������k�N��doingkind
            LOCK_CHARACTER(lIndex);
            ExecChangeCharacterDoingSomethingFun(lIndex, doing_kind, 0, d1, d2, d3, d4, d5);
            UNLOCK_CHARACTER(lNpcIndex);
            //
        }
    }    
    //�եι�����doingkind�B�z���
    ret = ExecCharacterDoingSomething(lIndex, doing_kind);
    if (!sill_can_use_flag)//�p�G�ޯण��ϥΪ�^����
        ret = ACTION_RETURN_FAIL;
    //
    return ret;    
}
//----
//  �B�b�W�O�����q
//----
SLONG   NpcMainAIBlockSpower(SLONG lIndex)
{
    SLONG   doing_kind, new_doing_kind;
    SLONG   selfbreak_flag;
    SLONG   magic_no, magic_level;
    //�P�_npc��e��doingkind�O�_�Oidle
    LOCK_CHARACTER(lNpcIndex);
    doing_kind = GetCharacterDoingKind(lIndex);    
    selfbreak_flag = IsCharacterSelfDoingKindBreak(lIndex);
    magic_no = GetCharacterDoingMagic(lIndex);
    magic_level = GetCharacterSpecialSkillLevel(lIndex, magic_no);
    UNLOCK_CHARACTER(lNpcIndex);
    //
    new_doing_kind = DOING_KIND_SPOWER;
    //�P�_��npc�ʧ@��_�Q���_...
    if ( new_doing_kind != doing_kind)
    {
        //���ܨ�ݾ����A
        if (selfbreak_flag)
        {
            doing_kind = new_doing_kind;
            LOCK_CHARACTER(lIndex);
            //���ܪ��A��ݾ����A
            ExecChangeCharacterDoingSomethingFun(lIndex, doing_kind, 0, 0,0,0,0,0);
            //�W�O�ƾڪ�l��
            FightPrepareSpower(lIndex, magic_no, magic_level);
            UNLOCK_CHARACTER(lNpcIndex);
        }
    }
    //�եι�����doingkind�B�z���
    ExecCharacterDoingSomething(lIndex, doing_kind);
    //�ݾ��u���@�ت�^���A
    return ACTION_RETURN_PROC;
}
//----
//  �M�H��ܪ�doingkind
//----
SLONG   NpcMainAIBlcokTalk(SLONG lIndex)
{
    SLONG   doing_kind, new_doing_kind;
    SLONG   selfbreak_flag;
    SLONG   d1, d2, d3, d4, d5;
    SLONG   des_no;
    SLONG   ret = ACTION_RETURN_PROC;
    //�P�_npc��e��doingkind�O�_�Oidle
    LOCK_CHARACTER(lNpcIndex);
    doing_kind = GetCharacterDoingKind(lIndex);    
    selfbreak_flag = IsCharacterSelfDoingKindBreak(lIndex);
    des_no = GetCharacterDestID(lIndex);        
    UNLOCK_CHARACTER(lNpcIndex);
    //
    new_doing_kind = DOING_KIND_TALK_WITH_NPC;
    //�P�_��npc�ʧ@��_�Q���_...
    //���ܨ�ݾ����A
    if (doing_kind != new_doing_kind)
    {
        if (selfbreak_flag)
        {
            d1 = des_no;
            d2 = 0;
            d3 = 0;
            d4 = 0;
            d5 = 0;
            //���ܨ����������k�N��doingkind
            doing_kind = new_doing_kind;
            LOCK_CHARACTER(lIndex);            
            ExecChangeCharacterDoingSomethingFun(lIndex, doing_kind, 0, d1, d2, d3, d4, d5);
            UNLOCK_CHARACTER(lNpcIndex);
            //
        }
    }    
    //�եι�����doingkind�B�z���
    ret = ExecCharacterDoingSomething(lIndex, doing_kind);
    //
    return ret ;

}
//----
//  �l��
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
        // �b�ۤv�����u��
        if (dest <= magic_dis)
        {
            //�b�I�k���Z����
            //          �եΨϥΧޯ઺AI_BLOCK
            ret = NpcMainAIBlcokUseSkill(lIndex);
        }
        else
        {
            //�b�I�k���Z���~
            //      �ե�..���ʪ�AI_BLOCK
            ret = NpcMainAIBlcokMoveTo(lIndex);
        }
    }
    else
    {
        // �b�ۤv�����u�~
        //�ե�IDLE_BLOCK
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
    // �b�ۤv�����u��
    if (dest <= NEAR_DISTANCE)
    {
        ret = NpcMainAIBlcokTalk(lIndex);
    }
    else
    {
        //�b�I�k���Z���~
        //      �ե�..���ʪ�AI_BLOCK
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
    if(dest_npc >= 0) //�P�_���u�����ĤH
    {
        //.....�Ȥ�ݬƻ򳣤��@
        //.....�A�Ⱦ��ݻݭn����AI_BLOCK...�����ĤH...����...��npc��ܤ@�ӨϥΪ��ޯ�
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
    case MAIN_AI_BLOCK_DUMP:        //�Ŭƻ򳣤��@
        break;
    case MAIN_AI_BLOCK_IDLE:        //�b��a�ݾ�
        break;    
    case MAIN_AI_BLOCK_USE_SKILL:   //�b��a�ϥβ��ӧޯ�    
        break;    
    case MAIN_AI_BLOCK_TALK:        //�b��ĩM�H���
        break;    
    case MAIN_AI_BLOCK_SPOWER:      //�W�O��AI�_
        FightAbortSpower(lIndex, Skill, SkillLevel);
        break;    
    case MAIN_AI_BLOCK_MOVE_TO:     //���ʨ���ӥؼ��I..�p�G���ؼ�npc..�N�O���H�ؼ�npc
        break;    
    case MAIN_AI_BLOCK_MOVE_SKILL:  //���ʨ�ؼ��I�ϥΧޯ�..�p�G���ؼ�npc..�N�O�����Y�ӥؼ�npc
        break;    
    case MAIN_AI_BLOCK_MOVE_TALK:   //���ʨ�ؼ��I�M���ӬY��npc���    
        break;    
    }
}
//---
//  �ϥΦb Character �ݭn�b���ܥL��AI_BLOCK���ɭԽե�...�bAI  �B�z��..�ݭn���� AI_BLOCK���n�եγo��!!!
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
//  �Ө�ƬO�Φb AI �B�z���ɭ�..�b..�h��AI_BLOCK���઺�ɭԨϥ�..
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

