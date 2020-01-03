/*
 *	ljun 2003-04-14
 *  本文件裡面定義的是一些NPC最小行為的函數
 */
#include "NetGE_Mainfunc.h"
#include "NetGE_MainFunc.h"
#include "NetGE_NPC_mindoingkind.h" 

/*
    NPC的行為有.
        1.移動
        2.使用機能
             機能1
             機能2             
             .....

 */

//-------------------------------------------------------------------------
//  關於動畫播放函數
//      !!!注意以下的函數裡面不能有doingstep
//      !!記住在進入這些函數之前..要先解lock ..
//-------------------------------------------------------------------------
//-----
//  播放動畫循環
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
//  播放動畫一次
//      返回動畫的當前幀
//-----
SLONG   MinKind_NpcActionOneTime(SLONG npc_no, SLONG action, SLONG no_play_frame)
{
    enum
    {   
        DOING_STEP_START        =   0,  //動畫播放開始
        DOING_STEP_RUNNING      =   1,  //動畫播放中
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
        DOING_STEP_START        =   0,  //動畫播放開始
        DOING_STEP_RUNNING      =   1,  //動畫播放中
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
//  一些最小行為塊
//-------------------------------------------------------------------------
//-----
//  陸地npc移動過程的控制函數...會自動路徑搜索的.
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
    //移動相關的數據
    GetCharacterPosition(npc_no, &x, &y, &z);
    move_speed = GetCharacterMoveSpeed(npc_no);
    //狀態相關的數據
    is_fight = IsCharacterOnFightState(npc_no);
    is_block = IsCharacterOnBlockState(npc_no);        
    action_block = StatuseToActionBlocks(is_fight, is_block);        
    is_defence = IsCharacterOnDefenceState(npc_no);
    foot_state = GetCharacterFootSpeedState(npc_no);    
    //客戶端特殊的...上圖必要
    dir = GetCharacterDir(npc_no);
    file_index = GetCharacterFileIndex(npc_no);
    old_id = GetCharacterImageID(npc_no);
    //
    UNLOCK_CHARACTER(npc_no);
    //---------------------------------------------------------------------
    //需要作的事情
    //1.改變需要的速度..
    //2.設置需要的動畫播放速度
    //3.和一定速度有關係的只有npc的..遲緩1,遲緩2 著兩個狀態
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
    ret = FindCharacterStep(x, y, &dest_x, &dest_y, move_speed);    //取得移動的下一步的位置..有路徑搜尋
    UNLOCK_MAPMASK(0);
    //
    switch(ret)
    {
    case STEP_ON_THE_WAY://步驟移動到目標點..的路程中
        {
            if(dest_x - x != 0 || dest_y - y != 0)
                dir = ApproachCharacterDir(dest_x - x, dest_y - y); //轉向判定
            //new_action = GetRunAction(is_fight);                    // 取得當前狀態的 動作 id 
            new_action = AC_RUN;
            new_id = GetCharacterFileActionImageID(file_index, action_block, new_action); //取得新動作的圖
            //
            LOCK_CHARACTER(npc_no);
            SetCharacterPosition(npc_no, dest_x, dest_y, 0);    //設置NPC到新的位置
            SetCharacterDir(npc_no, dir);                       //設置NPC上圖需要的方向                    
            if(old_id != new_id)
                SetCharacterImageID(npc_no, new_id);            //設置npc使用的圖檔..(更新到本狀態)
            DirFastLoopCharacterFrame(npc_no);                  //播放npc動畫(客戶端特殊需要改變動畫幀)
            UNLOCK_CHARACTER(npc_no);
            //
            ret = NPC_MOVE_MOVEING;
            break;
        }
    case STEP_ARRIVE://2.到達目標點
        {
            LOCK_CHARACTER(npc_no);
            SetCharacterPosition(npc_no, dest_x, dest_y, 0);        //到達了目的地 ..設置座標為目標點
            //SetCharacterDoingKindStep(npc_no, arrive_doingkind, arrive_doingstep);  //更該狀態到待機            
            DirFastLoopCharacterFrame(npc_no);                      //播放動畫(客戶端特殊)
            UNLOCK_CHARACTER(npc_no);
            ret = NPC_MOVE_ARRIVE;
            break;
        }
    case STEP_OBSTRUCT:  //3.被阻隔
    case STEP_OUTSTRETCH://4.超出範圍
    default:
        {
            LOCK_CHARACTER(npc_no);
            SetCharacterDestPosition(npc_no, x, y, 0);              //目標點到不了..停留在原地
            //SetCharacterDoingKindStep(npc_no, disarrive_doingkind, disarrive_doingstep);  //改變狀態到待機
            DirFastLoopCharacterFrame(npc_no);                      //播放動畫(客戶端特殊)            
            UNLOCK_CHARACTER(npc_no);
            ret = NPC_MOVE_CANT_ARRIVE;
            break;
        }
    }
    //
    return ret;    
}
//----- 
//  魔法的施放過程
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
    case NPC_KEY_FRAME_NONE://非關鍵幀
        break;
    case NPC_KEY_FRAME_HEAD://關鍵幀(第一幀)
        ret = NPC_MAGIC_START;
        break;
    case NPC_KEY_FRAME_HALF://中間幀
        ret = NPC_MAGIC_FIRE;
        //
        break;        
    case NPC_KEY_FRAME_TAIL://最後幀
        //需要根據該機能的播放次數....判斷是否需要在到第一幀
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
 
 