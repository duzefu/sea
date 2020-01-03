/*
 *	ljun 2003-04-14
 *  �����̭��w�q���O�@��NPC�̤p�欰�����
 */
#include "NetGE_Mainfunc.h"
#include "NetGE_MainFunc.h"
#include "NetGE_NPC_mindoingkind.h" 

/*
    NPC���欰��.
        1.����
        2.�ϥξ���
             ����1
             ����2             
             .....

 */

//-------------------------------------------------------------------------
//  ����ʵe������
//      !!!�`�N�H�U����Ƹ̭����঳doingstep
//      !!�O��b�i�J�o�Ǩ�Ƥ��e..�n����lock ..
//-------------------------------------------------------------------------
//-----
//  ����ʵe�`��
//-----
SLONG   MinKind_NpcActionLoop(SLONG npc_no, SLONG action)
{
    //
    SLONG   new_id, old_id;
    SLONG	file_index, action_block;
    SLONG   is_fight, is_block;
    SLONG   ret = NPC_ID_CHANGE_NONE;
    //
    LOCK_CHARACTER(npc_no);
    //
    is_fight = IsCharacterOnFightState(npc_no);
    is_block = IsCharacterOnBlockState(npc_no);
    file_index = GetCharacterFileIndex(npc_no);
    action_block = StatuseToActionBlocks(is_fight, is_block);
    new_id = GetCharacterFileActionImageID(file_index, action_block, action);
    old_id = GetCharacterImageID(npc_no);
    if(old_id != new_id)
    {
        SetCharacterIdleTicks(npc_no, 150 + system_rand()%100);
        SetCharacterImageID(npc_no, new_id);
        DirHeadCharacterFrame(npc_no);
        //
        ret = NPC_ID_CHANGE_YES;
    }
    else 
    {
        DirFastLoopCharacterFrame(npc_no);
    }
    //
    UNLOCK_CHARACTER(npc_no);  
    //
    return ret;                              
}
SLONG   MinKind_NpcImgIdLoop(SLONG npc_no, SLONG id)
{
    //
    SLONG   new_id, old_id;
    SLONG   ret = NPC_ID_CHANGE_NONE;
    //
    LOCK_CHARACTER(npc_no);
    //
    new_id = id;
    old_id = GetCharacterImageID(npc_no);
    if(old_id != new_id)
    {
        SetCharacterIdleTicks(npc_no, 150 + system_rand()%100);
        SetCharacterImageID(npc_no, new_id);
        DirHeadCharacterFrame(npc_no);
        //
        ret = NPC_ID_CHANGE_YES;
    }
    else 
    {
        DirFastLoopCharacterFrame(npc_no);
    }
    //
    UNLOCK_CHARACTER(npc_no);  
    //
    return ret;                              
}
//-----
//  ����ʵe�@��
//      ��^�ʵe����e�V
//-----
SLONG   MinKind_NpcActionOneTime(SLONG npc_no, SLONG action, SLONG no_play_frame)
{
    enum
    {   
        DOING_STEP_START        =   0,  //�ʵe����}�l
        DOING_STEP_RUNNING      =   1,  //�ʵe����
    };
    SLONG	file_index, action_block;
    SLONG   new_id, old_id;
    SLONG   is_fight, is_block;    
    SLONG   ret = NPC_KEY_FRAME_NONE;

    LOCK_CHARACTER(npc_no);
    //
    is_fight = IsCharacterOnFightState(npc_no);
    is_block = IsCharacterOnBlockState(npc_no);    
    action_block = StatuseToActionBlocks(is_fight, is_block);    
    file_index = GetCharacterFileIndex(npc_no);
    new_id = GetCharacterFileActionImageID(file_index, action_block, action);    
    //
    old_id = GetCharacterImageID(npc_no);
    if (old_id != new_id)
    {
        SetCharacterImageID(npc_no, new_id);
        DirHeadCharacterFrame(npc_no);
        ret = NPC_KEY_FRAME_HEAD;    
    }
    else
    {
        ret = DirCharacterFrame(npc_no, no_play_frame);
    }
    //
    UNLOCK_CHARACTER(npc_no);
    //
    return ret;
}
SLONG   MinKind_NpcImgIdOneTime(SLONG npc_no, SLONG id, SLONG no_play_frame)
{
    enum
    {   
        DOING_STEP_START        =   0,  //�ʵe����}�l
        DOING_STEP_RUNNING      =   1,  //�ʵe����
    };
    SLONG   new_id, old_id;
    SLONG   ret = NPC_KEY_FRAME_NONE;

    LOCK_CHARACTER(npc_no);
    //
    new_id = id;
    //
    old_id = GetCharacterImageID(npc_no);
    if (old_id != new_id)
    {
        SetCharacterImageID(npc_no, new_id);
        DirHeadCharacterFrame(npc_no);
        ret = NPC_KEY_FRAME_HEAD;    
    }
    else
    {
        ret = DirCharacterFrame(npc_no, no_play_frame);
    }
    //
    UNLOCK_CHARACTER(npc_no);
    //
    return ret;
}

//-------------------------------------------------------------------------
//  �@�ǳ̤p�欰��
//-------------------------------------------------------------------------
//-----
//  ���anpc���ʹL�{��������...�|�۰ʸ��|�j����.
//-----
SLONG   MinKind_NpcMoveFindPath(SLONG npc_no,SLONG dest_x,SLONG dest_y)
{
    //
    SLONG   file_index, action_block;
    SLONG   new_id, old_id, new_action, dir;
    SLONG   x, y, z ;
    SLONG   move_speed;
    SLONG   is_fight, foot_state, is_defence, is_block;
    SLONG   ret = NPC_MOVE_MOVEING;
    //
    LOCK_CHARACTER(npc_no);
    //���ʬ������ƾ�
    GetCharacterPosition(npc_no, &x, &y, &z);
    move_speed = GetCharacterMoveSpeed(npc_no);
    //���A�������ƾ�
    is_fight = IsCharacterOnFightState(npc_no);
    is_block = IsCharacterOnBlockState(npc_no);        
    action_block = StatuseToActionBlocks(is_fight, is_block);        
    is_defence = IsCharacterOnDefenceState(npc_no);
    foot_state = GetCharacterFootSpeedState(npc_no);    
    //�Ȥ�ݯS��...�W�ϥ��n
    dir = GetCharacterDir(npc_no);
    file_index = GetCharacterFileIndex(npc_no);
    old_id = GetCharacterImageID(npc_no);
    //
    UNLOCK_CHARACTER(npc_no);
    //---------------------------------------------------------------------
    //�ݭn�@���Ʊ�
    //1.���ܻݭn���t��..
    //2.�]�m�ݭn���ʵe����t��
    //3.�M�@�w�t�צ����Y���u��npc��..��w1,��w2 �ۨ�Ӫ��A
    //
    // mark by lijun  2003-04-09
    /*    
    switch(foot_state)
    {
    case NPC_FOOT_SPEED_STATE_NORMAL:
    break;
    case NPC_FOOT_SPEED_STATE_TARDY:
    case NPC_FOOT_SPEED_STATE_TIRED:
        move_speed /= 2;
        if(move_speed < 2)
        move_speed = 2;
    break;
    }
    if(is_defence)
    {
        move_speed /= 2;
        if(move_speed < 1)
        move_speed = 1;
    }
    */
    //        
    LOCK_MAPMASK(0);
    ret = FindCharacterStep(x, y, &dest_x, &dest_y, move_speed);    //���o���ʪ��U�@�B����m..�����|�j�M
    UNLOCK_MAPMASK(0);
    //
    switch(ret)
    {
    case STEP_ON_THE_WAY://�B�J���ʨ�ؼ��I..�����{��
        {
            if(dest_x - x != 0 || dest_y - y != 0)
                dir = ApproachCharacterDir(dest_x - x, dest_y - y); //��V�P�w
            //new_action = GetRunAction(is_fight);                    // ���o��e���A�� �ʧ@ id 
            new_action = AC_RUN;
            new_id = GetCharacterFileActionImageID(file_index, action_block, new_action); //���o�s�ʧ@����
            //
            LOCK_CHARACTER(npc_no);
            SetCharacterPosition(npc_no, dest_x, dest_y, 0);    //�]�mNPC��s����m
            SetCharacterDir(npc_no, dir);                       //�]�mNPC�W�ϻݭn����V                    
            if(old_id != new_id)
                SetCharacterImageID(npc_no, new_id);            //�]�mnpc�ϥΪ�����..(��s�쥻���A)
            DirFastLoopCharacterFrame(npc_no);                  //����npc�ʵe(�Ȥ�ݯS��ݭn���ܰʵe�V)
            UNLOCK_CHARACTER(npc_no);
            //
            ret = NPC_MOVE_MOVEING;
            break;
        }
    case STEP_ARRIVE://2.��F�ؼ��I
        {
            LOCK_CHARACTER(npc_no);
            SetCharacterPosition(npc_no, dest_x, dest_y, 0);        //��F�F�ت��a ..�]�m�y�Ь��ؼ��I
            //SetCharacterDoingKindStep(npc_no, arrive_doingkind, arrive_doingstep);  //��Ӫ��A��ݾ�            
            DirFastLoopCharacterFrame(npc_no);                      //����ʵe(�Ȥ�ݯS��)
            UNLOCK_CHARACTER(npc_no);
            ret = NPC_MOVE_ARRIVE;
            break;
        }
    case STEP_OBSTRUCT:  //3.�Q���j
    case STEP_OUTSTRETCH://4.�W�X�d��
    default:
        {
            LOCK_CHARACTER(npc_no);
            SetCharacterDestPosition(npc_no, x, y, 0);              //�ؼ��I�줣�F..���d�b��a
            //SetCharacterDoingKindStep(npc_no, disarrive_doingkind, disarrive_doingstep);  //���ܪ��A��ݾ�
            DirFastLoopCharacterFrame(npc_no);                      //����ʵe(�Ȥ�ݯS��)            
            UNLOCK_CHARACTER(npc_no);
            ret = NPC_MOVE_CANT_ARRIVE;
            break;
        }
    }
    //
    return ret;    
}
//----- 
//  �]�k���I��L�{
//-----
SLONG   MinKind_NpcMagicDischarge(SLONG npc_no)
{
    SLONG   magic_npc_id, new_id;
    SLONG   new_action;
    SLONG   file_index, action_block;
    SLONG   is_fight, is_block;
    SLONG   magic_index,magic_times;
    SLONG   ret = NPC_MAGIC_DOING;
    //
    LOCK_CHARACTER(npc_no);
    is_fight = IsCharacterOnFightState(npc_no);
    is_block = IsCharacterOnBlockState(npc_no);    
    action_block = StatuseToActionBlocks(is_fight, is_block);    
    file_index = GetCharacterFileIndex(npc_no);    
    magic_index = GetCharacterDoingMagic(npc_no);
    magic_times = GetCharacterMagicTimes(npc_no);
    UNLOCK_CHARACTER(npc_no);
    //
    //magic_npc_id = GetSkillSpecialID(magic_index);
    magic_npc_id = GetSkillActionId(magic_index, 0);
    file_index = GetCharacterFileIndex(npc_no);
    if(magic_npc_id != INVALID_OBJECT_ID)
    {
        new_action = magic_npc_id;
    }        
    else
    {
        //new_action = GetMagicAction();
        //new_action = AC_MAGIC;
        new_action = AC_ATTACK_0;
    }
    new_id = GetCharacterFileActionImageID(file_index, action_block, new_action);    
    //
    switch (MinKind_NpcImgIdOneTime(npc_no, new_id))
    {
    case NPC_KEY_FRAME_NONE://�D����V
        break;
    case NPC_KEY_FRAME_HEAD://����V(�Ĥ@�V)
        ret = NPC_MAGIC_START;
        break;
    case NPC_KEY_FRAME_HALF://�����V
        ret = NPC_MAGIC_FIRE;
        //
        break;        
    case NPC_KEY_FRAME_TAIL://�̫�V
        //�ݭn�ھڸӾ��઺���񦸼�....�P�_�O�_�ݭn�b��Ĥ@�V
        magic_times -- ;
        if(magic_times <= 0)
        {
            ret = NPC_MAGIC_OVER;
        }
        else
        {
            LOCK_CHARACTER(npc_no);
            DirHeadCharacterFrame(npc_no);
            SetCharacterMagicTimes(npc_no, (SHINT)magic_times);
            UNLOCK_CHARACTER(npc_no);
        }
    }
    //
    return ret;
}
//-------------------------------------------------------------------------
// End.
//-------------------------------------------------------------------------
 
 