/*
**  DoingClient.cpp
**  npc doing functions for online game client.
**
**  Jack, 2002.5.15.
*/
#include "MainFun.h"
#include "Map.h"
#include "Npc.h"
#include "Magic.h"
#include "Fight.h"
#include "doingseaclient.h"
#include "magicClient.h" 
/**************************************************************************/
/* NO HIT DOING FUNCTIONS                                                 */
/**************************************************************************/
SLONG   client_do_npc_dummy( SLONG npc_no )
{
    //
    return ACTION_RETURN_PROC;
}

//----
//  暫停...npc停下來他原來做得事情...在原地待機
//  過程的實現
//  
//      1.本doingkind 只要播放動畫.身麼都不用作
//----
SLONG   client_do_npc_pause( SLONG npc_no )
{
    LOCK_CHARACTER(npc_no);
    DirLoopCharacterFrame(npc_no);
    UNLOCK_CHARACTER(npc_no);
    //
    return ACTION_RETURN_PROC;
}

//----
//  待機...
//  過程的實現
//      1.本doingkind 只用在兩個待機動畫中切換
//----
SLONG   client_do_npc_idle(SLONG npc_no)
{
    enum
    {   
        DOING_STEP_IDLE_NORMAL  =   0,      //一般待機動作
        DOING_STEP_IDLE_SPECIAL     =   1,      //特殊待機動作
    };
    SLONG   new_action;
    SLONG   is_fight, idle_ticks;
    SLONG	doing_step;
    //
    LOCK_CHARACTER(npc_no);
    is_fight = IsCharacterOnFightState(npc_no);
    doing_step = GetCharacterDoingStep(npc_no);
    UNLOCK_CHARACTER(npc_no);
    //
    switch(doing_step)
    {
    case DOING_STEP_IDLE_NORMAL:    
        //new_action = GetIdleAction(is_fight);
        new_action = AC_WAIT_0;
        if (NPC_ID_CHANGE_YES == MinKind_NpcActionLoop(npc_no, new_action) )
        {
            SetCharacterIdleTicks(npc_no, 150 + system_rand()%100);
        }
        else
        {
            idle_ticks = GetCharacterIdleTicks(npc_no);
            if(--idle_ticks <= 0)
            {
                SetCharacterDoingStep(npc_no, DOING_STEP_IDLE_SPECIAL);
            }
            else
            {
                SetCharacterIdleTicks(npc_no, idle_ticks);
            }        
        }
        break;
    case DOING_STEP_IDLE_SPECIAL:
        //new_action = GetSpecialIdleAction(is_fight);
        new_action = AC_WAIT_1;
        if (NPC_KEY_FRAME_TAIL == MinKind_NpcActionOneTime(npc_no, new_action))
        {
            LOCK_CHARACTER(npc_no);
            SetCharacterDoingKindStep(npc_no, DOING_KIND_IDLE, DOING_STEP_IDLE_NORMAL);
            UNLOCK_CHARACTER(npc_no);
        }
        break;
    }
    return ACTION_RETURN_PROC;
    // mark by lijun 2003-04-10
    /*
    enum
    {   
        DOING_STEP_IDLE_NORMAL  =   0,      //一般待機動作
        DOING_STEP_IDLE_SPECIAL     =   1,      //特殊待機動作
    };
    SLONG   new_action, new_id;
    SLONG   is_fight, idle_ticks;
    SLONG	doing_step, file_index, id;

    LOCK_CHARACTER(npc_no);
    is_fight = IsCharacterOnFightState(npc_no);
	doing_step = GetCharacterDoingStep(npc_no);
    switch(doing_step)
    {
    case DOING_STEP_IDLE_NORMAL:
        new_action = GetIdleAction(is_fight);
		file_index = GetCharacterFileIndex(npc_no);
        new_id = GetCharacterFileActionImageID(file_index, new_action);
		id = GetCharacterImageID(npc_no);
        if(id != new_id)
        {
			SetCharacterIdleTicks(npc_no, 150 + system_rand()%100);
			SetCharacterImageID(npc_no, new_id);
            DirHeadCharacterFrame(npc_no);
        }
        else 
        {
			idle_ticks = GetCharacterIdleTicks(npc_no);
			if(--idle_ticks <= 0)
			{
				DirFastLoopCharacterFrame(npc_no);
				SetCharacterDoingStep(npc_no, DOING_STEP_IDLE_SPECIAL);
			}
			else
			{
				DirFastLoopCharacterFrame(npc_no);
				SetCharacterIdleTicks(npc_no, idle_ticks);
			}
        }
        break;
    case DOING_STEP_IDLE_SPECIAL:
        new_action = GetSpecialIdleAction(is_fight);
		file_index = GetCharacterFileIndex(npc_no);
        new_id = GetCharacterFileActionImageID(file_index, new_action);
		id = GetCharacterImageID(npc_no);
        if(id != new_id)
        {
			SetCharacterImageID(npc_no, new_id);
            DirHeadCharacterFrame(npc_no);
        }
        else  if(NPC_KEY_FRAME_HEAD == DirFastKeyLoopCharacterFrame(npc_no))
        {
			SetCharacterDoingStep(npc_no, DOING_STEP_IDLE_NORMAL);
        }
        break;
    }
    UNLOCK_CHARACTER(npc_no);
    */    
}
//-----
//  玩家站在原地 .不移動..轉身
//  過程的實現
//      1.只要在原待播放動畫就可以了.
//-----
SLONG   client_do_npc_stand(SLONG npc_no)
{
    SLONG   new_action;
    SLONG   is_fight;
    SLONG	doing_step;
    //
    LOCK_CHARACTER(npc_no);
    is_fight = IsCharacterOnFightState(npc_no);
	doing_step = GetCharacterDoingStep(npc_no);
	//new_action = GetIdleAction(is_fight);
	new_action = AC_WAIT_0;
    UNLOCK_CHARACTER(npc_no);
    //
    MinKind_NpcActionLoop(npc_no, new_action);
    //
    return ACTION_RETURN_PROC;
    // mark by lijun 2003-04-10
    /*
    SLONG   new_action, new_id;
    SLONG   is_fight;
	SLONG	doing_step, file_index, id;
	
    LOCK_CHARACTER(npc_no);
    is_fight = IsCharacterOnFightState(npc_no);
	doing_step = GetCharacterDoingStep(npc_no);
	new_action = GetIdleAction(is_fight);
	file_index = GetCharacterFileIndex(npc_no);
	new_id = GetCharacterFileActionImageID(file_index, new_action);
	id = GetCharacterImageID(npc_no);
	if(id != new_id)
	{
		SetCharacterImageID(npc_no, new_id);
		DirHeadCharacterFrame(npc_no);
	}
	else 
	{
		DirFastLoopCharacterFrame(npc_no);
	}
    UNLOCK_CHARACTER(npc_no);
    */    
}
//-----
//  冥想
//  過程的實現
//      1.播放動畫
//-----
SLONG   client_do_npc_muse(SLONG npc_no)
{
    
    MinKind_NpcActionLoop(npc_no, AC_SPOWER);
    //
    return ACTION_RETURN_PROC;
    //mark by lijun 2003-04-10
    /*
    enum    
    { 
        MUSE_APPLY_TICKS        =   20 
    };
    SLONG   new_action, new_id;
    SLONG   need_voice, apply_effect;
    SLONG   file_index, id, x, y, z;
	SLONG	muse_ticks;

    need_voice = false;

    LOCK_CHARACTER(npc_no);
    file_index = GetCharacterFileIndex(npc_no);
    id = GetCharacterImageID(npc_no);
    UNLOCK_CHARACTER(npc_no);

    new_action = AC_SPOWER;
    new_id = GetCharacterFileActionImageID(file_index, new_action);
    if(id != new_id)
    {
        LOCK_CHARACTER(npc_no);
		SetCharacterImageID(npc_no, new_id);
		SetCharacterMuseTicks(npc_no, MUSE_APPLY_TICKS);
        DirHeadCharacterFrame(npc_no);
		GetCharacterPosition(npc_no, &x, &y, &z);
        need_voice = true;
        UNLOCK_CHARACTER(npc_no);
    }
    else
    {
        apply_effect = false;

        LOCK_CHARACTER(npc_no);
        DirFastLoopCharacterFrame(npc_no);
		muse_ticks = GetCharacterMuseTicks(npc_no);
        if(--muse_ticks == 0)
        {
			SetCharacterMuseTicks(npc_no, MUSE_APPLY_TICKS);
            apply_effect = true;
        }
		else
		{
			SetCharacterMuseTicks(npc_no, muse_ticks);
		}
        UNLOCK_CHARACTER(npc_no);

        if(apply_effect)
        {
            //compute_npc_muse_effect(npc_no);
        }
    }

    if(need_voice)
    {
        play_fight_voice(0, npc_no, file_index, DOING_KIND_MUSE, 0, x, y);
    }
    */    
}
//----
//  蓄力
//  過程的實現
//      1.播放動畫()
//      2.增加身上的效果
//      3.播放需要的聲音
//----
SLONG   client_do_npc_spower(SLONG npc_no)
{
    SLONG   file_index,x,y,z;
    //
    LOCK_CHARACTER(npc_no);
	file_index = GetCharacterFileIndex(npc_no);    
    GetCharacterPosition(npc_no, &x, &y, &z);	
    UNLOCK_CHARACTER(npc_no);	
    //
    if (NPC_ID_CHANGE_YES == MinKind_NpcActionLoop(npc_no, AC_SPOWER)) //第一次切換到這個狀態的時候需要作一些特別的事情
    {
        //增加身上的物件效果
        LOCK_CHARACTER(npc_no);
		set_npc_ext_id(npc_no, MAKE_OBJECT_ID(OBJECT_TYPE_MAGIC, 23)); //增加一個
		set_npc_ext_frame(npc_no, 0);
        UNLOCK_CHARACTER(npc_no);
        //播放音效果
        play_fight_voice(0, npc_no, file_index, DOING_KIND_SPOWER, 0, x, y);
    }
    else
    {
        LOCK_CHARACTER(npc_no);    
        //播放蓄力的動畫
        loop_npc_ext_frame(npc_no);
        UNLOCK_CHARACTER(npc_no);        
    }
    //
    return ACTION_RETURN_PROC;
    //mark by lijun 2003-04-10
    /*
    SLONG   new_action, new_id;
    SLONG   need_voice;
    SLONG   file_index, x, y, z;
	SLONG	id;

    need_voice = false;

    LOCK_CHARACTER(npc_no);
	file_index = GetCharacterFileIndex(npc_no);
	id = GetCharacterImageID(npc_no);
    new_action = AC_SPOWER;
    new_id = GetCharacterFileActionImageID(file_index, new_action);
    if(id != new_id)
    {
		SetCharacterImageID(npc_no, new_id);
        DirHeadCharacterFrame(npc_no);
		GetCharacterPosition(npc_no, &x, &y, &z);
        //
		set_npc_ext_id(npc_no, MAKE_OBJECT_ID(OBJECT_TYPE_MAGIC, 401));	// Jack, for use Petra magic images. [1/27/2003]
		//set_npc_ext_id(npc_no, MAKE_OBJECT_ID(OBJECT_TYPE_MAGIC, 0));
		set_npc_ext_frame(npc_no, 0);
        //
        need_voice = true;
    }
    else
    {
        DirFastLoopCharacterFrame(npc_no);
        loop_npc_ext_frame(npc_no);
    }
    UNLOCK_CHARACTER(npc_no);

    if(need_voice)
    {
        play_fight_voice(0, npc_no, file_index, DOING_KIND_SPOWER, 0, x, y);
    }
    */
}
//----
//  npc在切換地圖的時候..因為地圖資源還沒有讀取完畢..的狀態
//  過程表現
//      在地圖上播放待機動畫
//----
SLONG   client_do_npc_change_map(SLONG npc_no)
{
    SLONG   is_on_sea;
    //
    LOCK_CHARACTER(npc_no);
	is_on_sea = IsCharacterOnTheSea(npc_no);
    UNLOCK_CHARACTER(npc_no);
    //
	if(is_on_sea)
	{
        client_do_sea_npc_idle(npc_no);	
	}
	else
	{
        client_do_npc_idle(npc_no);
	}
    return ACTION_RETURN_PROC;
    // mark by lijun 2003-04-10
    /*
    SLONG   doing_step;
    SLONG   file_index, id;
    SLONG   new_action, new_id;
    SLONG   is_fight, is_on_sea;

    LOCK_CHARACTER(npc_no);
    doing_step = GetCharacterDoingStep(npc_no);
    file_index = GetCharacterFileIndex(npc_no);
    id = GetCharacterImageID(npc_no);
    is_fight = IsCharacterOnFightState(npc_no);
	is_on_sea = IsCharacterOnTheSea(npc_no);
    UNLOCK_CHARACTER(npc_no);

	if(is_on_sea)
	{
		new_action = GetOnSeaIdleAction(is_fight);
		new_id = GetSeaCharacterFileActionImageID(file_index, new_action);
		if(id != new_id)
		{
			LOCK_CHARACTER(npc_no);
			SetCharacterImageID(npc_no, new_id);
			DirHeadSeaCharacterFrame(npc_no, -1);
			LOCK_CHARACTER(npc_no);
		}
		else
		{
			LOCK_CHARACTER(npc_no);
			DirFastLoopSeaCharacterFrame(npc_no);
			UNLOCK_CHARACTER(npc_no);
		}
	}
	else
	{
		new_action = GetIdleAction(is_fight);
		new_id = GetCharacterFileActionImageID(file_index, new_action);
		if(new_id != id)
		{
			LOCK_CHARACTER(npc_no);
			SetCharacterImageID(npc_no, new_id);
			DirHeadCharacterFrame(npc_no);
			UNLOCK_CHARACTER(npc_no);
		}
		else
		{
			LOCK_CHARACTER(npc_no);
			DirLoopCharacterFrame(npc_no);
			UNLOCK_CHARACTER(npc_no);
		}
	}
    */	
}

/******************************************************************************************************************/
/* HIT MAP DOING FUNCTIONS                                                                                        */
/******************************************************************************************************************/
//----
//移動到目標點
//  過程表現.
//      1.路徑搜尋.移動到目標點
//----
SLONG   client_do_npc_move_to( SLONG npc_no )
{
    SLONG   dest_npc;
    SLONG   dest_x, dest_y, dest_z;
    SLONG   ret = ACTION_RETURN_PROC;
    //該DoingKin 只有一個過程 移動到目標點
    LOCK_CHARACTER(npc_no);
    dest_npc = GetCharacterDestID(npc_no);
    GetCharacterDestPosition(npc_no, &dest_x, &dest_y, &dest_z);
    UNLOCK_CHARACTER(npc_no);    
    //
    if (dest_npc >= 0)
    {
        LOCK_CHARACTER(dest_npc);
        GetCharacterPosition(dest_npc, &dest_x, &dest_y, &dest_z);
        UNLOCK_CHARACTER(dest_npc);
    }
    
    //    
    switch (MinKind_NpcMoveFindPath(npc_no,dest_x, dest_y))
    {
    case NPC_MOVE_MOVEING:      //npc移動在移動過程中
        ret = ACTION_RETURN_PROC;
        break;    
    case NPC_MOVE_ARRIVE:       //npc移動到達了目標
        LOCK_CHARACTER(npc_no);
        SetCharacterDoingKindStep(npc_no, DOING_KIND_IDLE, 0);
        UNLOCK_CHARACTER(npc_no);
        //
        ret = ACTION_RETURN_OK;
        break;    
    case NPC_MOVE_CANT_ARRIVE:  //npc移動不能到達
        LOCK_CHARACTER(npc_no);
        SetCharacterDoingKindStep(npc_no, DOING_KIND_IDLE, 0);
        UNLOCK_CHARACTER(npc_no);    
        //
        ret = ACTION_RETURN_FAIL;
        break;
    }
    return ret;
    //mark by lijun 2003-04-09    
    /*
    enum 
    {   DOING_STEP_MOVE_TO  =   0,  //移動到目標點
    };
    SLONG   doing_step, file_index;
    SLONG   new_id, id, new_action, dir;
    SLONG   x, y, z, dest_x, dest_y, dest_z;
    SLONG   move_speed;
    SLONG   ret;
    SLONG   is_fight, foot_state, is_defence;

    LOCK_CHARACTER(npc_no);
    doing_step = GetCharacterDoingStep(npc_no);
    GetCharacterPosition(npc_no, &x, &y, &z);
    GetCharacterDestPosition(npc_no, &dest_x, &dest_y, &dest_z);
    dir = GetCharacterDir(npc_no);
    move_speed = GetCharacterMoveSpeed(npc_no);
    file_index = GetCharacterFileIndex(npc_no);
    id = GetCharacterImageID(npc_no);
    is_fight = IsCharacterOnFightState(npc_no);
    is_defence = IsCharacterOnDefenceState(npc_no);
    foot_state = GetCharacterFootSpeedState(npc_no);
    UNLOCK_CHARACTER(npc_no);

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
    switch(doing_step)
    {
    case DOING_STEP_MOVE_TO:
        {
			LOCK_MAPMASK(0);
            ret = FindCharacterStep(x, y, &dest_x, &dest_y, move_speed);
			UNLOCK_MAPMASK(0);
            switch(ret)
            {
            case STEP_ON_THE_WAY:
                {
                    if(dest_x - x != 0 || dest_y - y != 0)
                        dir = ApproachCharacterDir(dest_x - x, dest_y - y);
                    new_action = GetRunAction(is_fight);
                    new_id = GetCharacterFileActionImageID(file_index, new_action);
                    if(id != new_id)
                    {
                        LOCK_CHARACTER(npc_no);
                        SetCharacterPosition(npc_no, dest_x, dest_y, 0);
                        SetCharacterDir(npc_no, dir);
                        SetCharacterImageID(npc_no, new_id);
                        DirFastLoopCharacterFrame(npc_no);
                        UNLOCK_CHARACTER(npc_no);
                    }
                    else
                    {
                        LOCK_CHARACTER(npc_no);
                        SetCharacterPosition(npc_no, dest_x, dest_y, 0);
                        SetCharacterDir(npc_no, dir);
                        DirFastLoopCharacterFrame(npc_no);
                        UNLOCK_CHARACTER(npc_no);
                    }
                    break;
                }
            case STEP_ARRIVE:
                {
                    LOCK_CHARACTER(npc_no);
                    SetCharacterPosition(npc_no, dest_x, dest_y, 0);
                    DirFastLoopCharacterFrame(npc_no);
                    SetCharacterDoingKindStep(npc_no, DOING_KIND_IDLE, 0);
                    UNLOCK_CHARACTER(npc_no);
                    break;
                }
            case STEP_OBSTRUCT:
            case STEP_OUTSTRETCH:
            default:
                {
                    LOCK_CHARACTER(npc_no);
                    SetCharacterDestPosition(npc_no, x, y, 0);
                    DirFastLoopCharacterFrame(npc_no);
                    SetCharacterDoingKindStep(npc_no, DOING_KIND_IDLE, 0);
                    UNLOCK_CHARACTER(npc_no);
                    break;
                }
            }
            break;
        }
    }
    */    
}
/*
//----
//  對目標釋放法術
//      1.移動接近目標
//      2.釋放法術(過程)
//----
SLONG   client_do_npc_magic_position(SLONG npc_no)
{

    enum
    {   
        DOING_STEP_NEAR_TO          =   0,		//靠近目標
        DOING_STEP_MAGIC_POSITION   =   1,		//對目標施法
        DOING_STEP_PANT				=	2,		//喘息(for server only)
        DOING_STEP_RESPONSE			=	3,		//反應
        //
        NPC_MAGIC_IMAGE_REPEAT      =   1,
    };
    SLONG   doing_step;
    SLONG   magic_index, magic_times;
    SLONG   dest_x, dest_y, dest_z;
    SLONG   x, y, z, dir;
    SLONG   file_index;
    SLONG   new_action;
    SLONG   distance, magic_distance;
    SLONG   is_fight;
	SLONG	fight_ticks;
	SLONG   ret = ACTION_RETURN_PROC;

    LOCK_CHARACTER(npc_no);
    is_fight = IsCharacterOnFightState(npc_no);    
    doing_step = GetCharacterDoingStep(npc_no);
	GetCharacterDestPosition(npc_no, &dest_x, &dest_y, &dest_z);
	GetCharacterPosition(npc_no, &x, &y, &z);
    magic_index = GetCharacterDoingMagic(npc_no);
    magic_times = GetCharacterMagicTimes(npc_no);
    dir = GetCharacterDir(npc_no);
    file_index = GetCharacterFileIndex(npc_no);
	fight_ticks = GetCharacterFightTicks(npc_no);
    UNLOCK_CHARACTER(npc_no);


    magic_distance = GetSkillMagicDisChargeDistance(magic_index, 0);

    switch(doing_step)
    {
    case DOING_STEP_NEAR_TO:
        distance = (SLONG) sqrt( (dest_x - x) * (dest_x - x) + (dest_y - y) * (dest_y - y) );
        if(distance > magic_distance)
        {
            //距離太遠移動過去
            switch (MinKind_NpcMoveFindPath(npc_no,dest_x, dest_y))
            {
            case NPC_MOVE_MOVEING:      //npc移動在移動過程中
                break;    
            case NPC_MOVE_ARRIVE:       //npc移動到達了目標
                LOCK_CHARACTER(npc_no);
                SetCharacterDoingKindStep(npc_no, DOING_KIND_MAGIC_POSITION, DOING_STEP_MAGIC_POSITION);
                UNLOCK_CHARACTER(npc_no);
                break;    
            case NPC_MOVE_CANT_ARRIVE:  //npc移動不能到達
                LOCK_CHARACTER(npc_no);
                SetCharacterDoingKindStep(npc_no, DOING_KIND_IDLE, 0);
                UNLOCK_CHARACTER(npc_no);    
                //
                ret = ACTION_RETURN_FAIL;
                break;
            }                                            
        }
        else
        {
            //面向施法的目標...轉換到施法過程
            if(dest_x - x != 0 || dest_y - y != 0)
                dir = ApproachCharacterDir(dest_x - x, dest_y - y);
            LOCK_CHARACTER(npc_no);
            SetCharacterDir(npc_no, dir);
            DirHeadCharacterFrame(npc_no);
            SetCharacterDoingStep(npc_no, DOING_STEP_MAGIC_POSITION);
            UNLOCK_CHARACTER(npc_no);
        }
        break;
    case DOING_STEP_MAGIC_POSITION:
        //1.播放法術釋放動畫
        //2.在中間幀 .. 播放聲音
        //3.在最後一幀.改變狀態到待機狀態(服務器段需要到下個狀態)
        switch (MinKind_NpcMagicDischarge(npc_no))
        {
        case NPC_MAGIC_DOING://在施法過程中
            break;        
        case NPC_MAGIC_START://開始施法
            break;        
        case NPC_MAGIC_FIRE://到了攻擊幀
            //客戶端身麼都不要作..
            //  服務器端需要產生魔法組件
            break;        
        case NPC_MAGIC_OVER://施法動作結束
            //設置喘息時間..改變到下個狀態
            LOCK_CHARACTER(npc_no);
            fight_ticks = GetSkillPantTick(magic_index, 0);
            SetCharacterFightTicks(npc_no, (SHINT)fight_ticks);
            SetCharacterDoingStep(npc_no, DOING_STEP_PANT);
            UNLOCK_CHARACTER(npc_no);                
            break;
        }
        break;
    // 一下兩個階段只有服務器在使用
    case DOING_STEP_PANT:
	    //戰鬥喘息( 因為 doingstep 的改變..服務器不會發消息通知..所以需要..客戶段自己計算)
	    //1.在一段時間內播放待機動畫
	    //2.在喘息結束後.到下個狀態
        fight_ticks --;
        if(fight_ticks <= 0)
        {
            LOCK_CHARACTER(npc_no);
            SetCharacterFightTicks(npc_no, 0);
            SetCharacterDoingStep(npc_no, DOING_STEP_RESPONSE);
            UNLOCK_CHARACTER(npc_no);
        }
        else
        {
            //待機
            LOCK_CHARACTER(npc_no);
            new_action = GetIdleAction(is_fight);
            UNLOCK_CHARACTER(npc_no);
            //
            MinKind_NpcActionLoop(npc_no, new_action);
            //
            LOCK_CHARACTER(npc_no);
            SetCharacterFightTicks(npc_no, (SHINT)fight_ticks);
            UNLOCK_CHARACTER(npc_no);
        }	    
		break;
	case DOING_STEP_RESPONSE:
        LOCK_CHARACTER(npc_no);
        SetCharacterDoingKindStep(npc_no, DOING_KIND_IDLE, 0);
        UNLOCK_CHARACTER(npc_no);	
        //
        ret = ACTION_RETURN_OK;
		break;

    }
    //
    return ret;
    // mark by lijun 2003-04-10
    /--------------------------------------------------------------------
    enum
    {   
        DOING_STEP_NEAR_TO      =   0,		//靠近目標
        DOING_STEP_MAGIC_POSITION   =   1,		//對目標施法
        DOING_STEP_PANT				=	2,		//喘息(for server only)
        DOING_STEP_RESPONSE			=	3,		//反應
        //
        NPC_MAGIC_IMAGE_REPEAT      =   1,
    };
    SLONG   doing_step;
    SLONG   magic_index, magic_npc_id, magic_times;
    SLONG   dest_x, dest_y, dest_z;
    SLONG   x, y, z, dir;
    SLONG   file_index, id;
    SLONG   new_action, new_id;
    SLONG   move_speed, frame_flag;
    SLONG   distance, magic_distance;
	SLONG	is_fight;
    SLONG   ret;
	SLONG	fight_ticks;

    LOCK_CHARACTER(npc_no);
    doing_step = GetCharacterDoingStep(npc_no);
	GetCharacterDestPosition(npc_no, &dest_x, &dest_y, &dest_z);
	GetCharacterPosition(npc_no, &x, &y, &z);
    magic_index = GetCharacterDoingMagic(npc_no);
    magic_times = GetCharacterMagicTimes(npc_no);
     dir = GetCharacterDir(npc_no);
    move_speed = GetCharacterMoveSpeed(npc_no);
    file_index = GetCharacterFileIndex(npc_no);
    id = GetCharacterImageID(npc_no);
    is_fight = IsCharacterOnFightState(npc_no);
	fight_ticks = GetCharacterFightTicks(npc_no);
    UNLOCK_CHARACTER(npc_no);

    magic_distance = GetSkillTargetDistance(magic_index);
    magic_npc_id = GetSkillSpecialID(magic_index);

    switch(doing_step)
    {
    case DOING_STEP_NEAR_TO:
        {
            distance = (SLONG) sqrt( (dest_x - x) * (dest_x - x) + (dest_y - y) * (dest_y - y) );
            if(distance > magic_distance)
            {
				GatherMapCharacterMaskPosition();
				LOCK_MAPMASK(0);
				UpdateMapCharacterMask();
				ClearMapDynamicCharacterMask(x, y);
				ret = TrendFindCharacterStep(x, y, &dest_x, &dest_y, move_speed, MASK_STOP | MASK_DYNAMIC_NPC);
				RemoveMapCharacterMask();
				UNLOCK_MAPMASK(0);

                switch(ret)
                {
                case STEP_ON_THE_WAY:
                    {
						if(dest_x - x != 0 || dest_y - y != 0)
							dir = ApproachCharacterDir(dest_x - x, dest_y - y);
						new_action = GetRunAction(is_fight);
						new_id = GetCharacterFileActionImageID(file_index, new_action);
                        if(id != new_id)
                        {
                            LOCK_CHARACTER(npc_no);
							SetCharacterPosition(npc_no, dest_x, dest_y, dest_z);
							SetCharacterDir(npc_no, dir);
							SetCharacterImageID(npc_no, new_id);
							DirFastLoopCharacterFrame(npc_no);
                            UNLOCK_CHARACTER(npc_no);
                        }
                        else
                        {
                            LOCK_CHARACTER(npc_no);
							SetCharacterPosition(npc_no, dest_x, dest_y, dest_z);
							SetCharacterDir(npc_no, dir);
							DirFastLoopCharacterFrame(npc_no);
                            UNLOCK_CHARACTER(npc_no);
                        }
                        break;
                    }
                case STEP_ARRIVE:
                    {
                        LOCK_CHARACTER(npc_no);
						SetCharacterPosition(npc_no, dest_x, dest_y, dest_z);
						DirFastLoopCharacterFrame(npc_no);
						SetCharacterDoingStep(npc_no, DOING_STEP_MAGIC_POSITION);
                        UNLOCK_CHARACTER(npc_no);
                        break;
                    }
                case STEP_OBSTRUCT:
                case STEP_OUTSTRETCH:
                default:
                    {
                        LOCK_CHARACTER(npc_no);
						SetCharacterDestPosition(npc_no, x, y, z);
						DirFastLoopCharacterFrame(npc_no);
						SetCharacterDoingKindStep(npc_no, DOING_KIND_IDLE, 0);
                        UNLOCK_CHARACTER(npc_no);
                        break;
                    }
                }
            }
            else
            {
				if(dest_x - x != 0 || dest_y - y != 0)
					dir = ApproachCharacterDir(dest_x - x, dest_y - y);
                LOCK_CHARACTER(npc_no);
				SetCharacterDir(npc_no, dir);
                DirHeadCharacterFrame(npc_no);
				SetCharacterDoingStep(npc_no, DOING_STEP_MAGIC_POSITION);
                UNLOCK_CHARACTER(npc_no);
            }
        }
        break;

    case DOING_STEP_MAGIC_POSITION:
        {
			if(magic_npc_id != INVALID_OBJECT_ID)
				new_id = magic_npc_id;
			else
			{
				new_action = GetMagicAction();
				new_id = GetCharacterFileActionImageID(file_index, new_action);
			}

            if(id != new_id)
            {
                LOCK_CHARACTER(npc_no);
				SetCharacterImageID(npc_no, new_id);
                DirHeadCharacterFrame(npc_no);
                UNLOCK_CHARACTER(npc_no);
            }
            else
            {
                LOCK_CHARACTER(npc_no);
                frame_flag = DirFastHalfCharacterFrame(npc_no);
                UNLOCK_CHARACTER(npc_no);

                if(NPC_KEY_FRAME_HALF == frame_flag)
                {
                    // For Server, need to do:
					// 
                    // (1) Break magic parts & append broken parts to zone magic parts list.
					// (2) Notify clients for break magic.
					// (3) Compute user's mp result.
					//

					//
					// For Client, just play voice:
					//
					play_fight_voice(0, npc_no, magic_index, DOING_KIND_MAGIC_NPC, 0, dest_x, dest_y);
                }
                else if(NPC_KEY_FRAME_TAIL == frame_flag)
                {
                    magic_times -- ;
                    if(magic_times <= 0)
                    {
                        LOCK_CHARACTER(npc_no);
						//
						//For Server:
						//
						//fight_ticks = GetSkillPantTicks(magic_index);
						//SetCharacterFightTicks(npc_no, fight_ticks);
						//SetCharacterDoingStep(npc_no, DOING_STEP_PANT);

						//
						//For Client:
						//
						SetCharacterDoingKindStep(npc_no, DOING_KIND_IDLE, 0);
                        UNLOCK_CHARACTER(npc_no);
                    }
                    else
                    {
                        LOCK_CHARACTER(npc_no);
						DirHeadCharacterFrame(npc_no);
                        SetCharacterMagicTimes(npc_no, (SHINT)magic_times);
                        UNLOCK_CHARACTER(npc_no);
                    }
                }
            }
        }
        break;

		//
		// The following 2 steps are for server use :
		//
	case DOING_STEP_PANT:
		fight_ticks --;
		if(fight_ticks <= 0)
		{
			LOCK_CHARACTER(npc_no);
			SetCharacterFightTicks(npc_no, 0);
			SetCharacterDoingStep(npc_no, DOING_STEP_RESPONSE);
			UNLOCK_CHARACTER(npc_no);
		}
		else
		{
			new_action = GetIdleAction(is_fight);
			new_id = GetCharacterFileActionImageID(file_index, new_action);
			if(id != new_id)
			{
				LOCK_CHARACTER(npc_no);
				SetCharacterImageID(npc_no, id);
				DirHeadCharacterFrame(npc_no);
				SetCharacterFightTicks(npc_no, (SHINT)fight_ticks);
				UNLOCK_CHARACTER(npc_no);
			}
			else
			{
				LOCK_CHARACTER(npc_no);
				DirFastLoopCharacterFrame(npc_no);
				SetCharacterFightTicks(npc_no, (SHINT)fight_ticks);
				UNLOCK_CHARACTER(npc_no);
			}
		}
		break;

	case DOING_STEP_RESPONSE:
		//
		// Server execute character's ai for after magic ...
		//
        // server_execute_npc_ai_after_magic(npc_no);
		break;

    }
    /--------------------------------------------------------------------
}
*/

//----
//衝撞
//  過程
//      1.衝過去
//
//----
SLONG   client_do_npc_clash(SLONG npc_no)
{
    enum
    {   DOING_STEP_READY_CLASH  =   0,  //準備衝撞
    DOING_STEP_CLASH_TO         =   1,  //正在衝撞的進行中
    //
    MOVE_SPEED_TIMES            =   5,  //移動速度是正常移動速度的倍數
    };
    SLONG   doing_step, dir;
    SLONG   file_index, new_action, new_id, action_block;
    SLONG   is_fight, is_block;
    SLONG   x, y, z, dest_x, dest_y, dest_z, step_x, step_y;
    SLONG   move_speed, magic_index, clash_steps;
    SLONG   ret;
    SLONG   fun_ret = ACTION_RETURN_PROC;

    LOCK_CHARACTER(npc_no);
    doing_step = GetCharacterDoingStep(npc_no);
    is_fight = IsCharacterOnFightState(npc_no);
    is_block = IsCharacterOnBlockState(npc_no);
    action_block = StatuseToActionBlocks(is_fight, is_block);        
    file_index = GetCharacterFileIndex(npc_no);
    GetCharacterPosition(npc_no, &x, &y, &z);
    GetCharacterDestPosition(npc_no, &dest_x, &dest_y, &dest_z);
    move_speed = GetCharacterMoveSpeed(npc_no);
    clash_steps = GetCharacterClashSteps(npc_no);
    magic_index = GetCharacterDoingMagic(npc_no);
    UNLOCK_CHARACTER(npc_no);

    move_speed = move_speed * MOVE_SPEED_TIMES;

    switch(doing_step)
    {
    case DOING_STEP_READY_CLASH:
        {
            double  r;
    
            LOCK_CHARACTER(npc_no);
            new_action = AC_SPECIAL_3;
            new_id = GetCharacterFileActionImageID(file_index, action_block, new_action);
            if(dest_x - x != 0 || dest_y - y != 0)
                dir = ApproachCharacterDir(dest_x - x, dest_y - y);
            SetCharacterDir(npc_no, dir);
            SetCharacterImageID(npc_no, new_id);
            DirHeadCharacterFrame(npc_no);
            r = sqrt( (dest_x - x)*(dest_x - x) + (dest_y - y)*(dest_y - y) + 1);
            step_x = (SLONG)( x + (dest_x - x) * move_speed * clash_steps / r );
            step_y = (SLONG)( y + (dest_y - y) * move_speed * clash_steps / r );
            SetCharacterDestPosition(npc_no, step_x, step_y, 0);
            SetCharacterDoingStep(npc_no, DOING_STEP_CLASH_TO);
            UNLOCK_CHARACTER(npc_no);

            play_fight_voice(0, npc_no, file_index, DOING_KIND_CLASH, 0, dest_x, dest_y);
        }
        break;

    case DOING_STEP_CLASH_TO:
        {
			LOCK_MAPMASK(0);
            ret = FindCharacterBeelineStep(x, y, &dest_x, &dest_y, move_speed);
			UNLOCK_MAPMASK(0);
            switch(ret)
            {
            case STEP_ON_THE_WAY:
                LOCK_CHARACTER(npc_no);
                SetCharacterDodge(npc_no, true);
                SetCharacterPosition(npc_no, dest_x, dest_y, 0);
                if(dest_x - x != 0 || dest_y - y != 0)
                    dir = ApproachCharacterDir(dest_x - x, dest_y - y);
                SetCharacterDir(npc_no, dir);
                DirFastTailCharacterFrame(npc_no);
                UNLOCK_CHARACTER(npc_no);
                break;

            case STEP_ARRIVE:
            case STEP_OUTSTRETCH:
                LOCK_CHARACTER(npc_no);
                SetCharacterDodge(npc_no, false);
                SetCharacterDoingKindStep(npc_no, DOING_KIND_IDLE, 0);
                UNLOCK_CHARACTER(npc_no);
                //
                fun_ret = ACTION_RETURN_OK;
                break;

            default:
                LOCK_CHARACTER(npc_no);
                SetCharacterDodge(npc_no, false);
                SetCharacterDoingKindStep(npc_no, DOING_KIND_IDLE, 0);
                UNLOCK_CHARACTER(npc_no);
                //
                fun_ret = ACTION_RETURN_OK;                
                break;
            }
        }
        break;
    }
    return fun_ret;
}
/*
//----
//  閒蕩
//      1.npc的一個行為..在地圖上到處亂走
//----
SLONG   client_do_npc_gad(SLONG npc_no)
{
    enum    
    {   
        DOING_STEP_IDLE   =   0,
        DOING_STEP_MOVE_TO    =   1,
    };
    SLONG   doing_step;
    SLONG   dest_x, dest_y, dest_z;
    SLONG   is_fight,new_action;
    SLONG   ret = ACTION_RETURN_PROC;
    //
    LOCK_CHARACTER(npc_no);
    doing_step = GetCharacterDoingStep(npc_no);
    GetCharacterDestPosition(npc_no, &dest_x, &dest_y, &dest_z);    
    is_fight = IsCharacterOnFightState(npc_no);    
    UNLOCK_CHARACTER(npc_no);

    switch(doing_step)
    {
    case DOING_STEP_IDLE:
        //狀態1 .待機
        //播放待機動畫
        new_action = GetIdleAction(is_fight);
        MinKind_NpcActionLoop(npc_no, new_action);
        break;
    case DOING_STEP_MOVE_TO:
        //狀態2..移動到目標點    
        switch (MinKind_NpcMoveFindPath(npc_no,dest_x, dest_y))
        {
        case NPC_MOVE_MOVEING:      //npc移動在移動過程中
            break;    
        case NPC_MOVE_ARRIVE:       //npc移動到達了目標
            LOCK_CHARACTER(npc_no);
            SetCharacterDoingKindStep(npc_no, DOING_KIND_GAD, DOING_STEP_IDLE);
            UNLOCK_CHARACTER(npc_no);
            break;    
        case NPC_MOVE_CANT_ARRIVE:  //npc移動不能到達
            LOCK_CHARACTER(npc_no);
            SetCharacterDoingKindStep(npc_no, DOING_KIND_GAD, DOING_STEP_IDLE);
            UNLOCK_CHARACTER(npc_no);    
            break;
        }                                                                                 
        break;
    default:
        break;
    }
    //
    return ret;
    //mark by lijun 2003-04-09
    /---------------------------------------------------------------------
    enum    
    {   
    DOING_STEP_IDLE   =   0,
    DOING_STEP_MOVE_TO    =   1,
    };
    SLONG   doing_step;
    SLONG   x, y, z;
    SLONG   dest_x, dest_y, dest_z;
    SLONG   move_speed;
    SLONG   file_index, id;
    SLONG   new_action, new_id;
    SLONG   dir, is_fight;
    SLONG   ret;

    LOCK_CHARACTER(npc_no);
    doing_step = GetCharacterDoingStep(npc_no);
	GetCharacterPosition(npc_no, &x, &y, &z);
	GetCharacterDestPosition(npc_no, &dest_x, &dest_y, &dest_z);
    move_speed = GetCharacterMoveSpeed(npc_no);
    file_index = GetCharacterFileIndex(npc_no);
    id = GetCharacterImageID(npc_no);
    dir = GetCharacterDir(npc_no);
    is_fight = IsCharacterOnFightState(npc_no);
    UNLOCK_CHARACTER(npc_no);

    switch(doing_step)
    {
    case DOING_STEP_IDLE:
        {
			new_action = GetIdleAction(is_fight);
			new_id = GetCharacterFileActionImageID(file_index, new_action);
			if(new_id != id)
			{
				LOCK_CHARACTER(npc_no);
				SetCharacterImageID(npc_no, new_id);
				DirHeadCharacterFrame(npc_no);
				UNLOCK_CHARACTER(npc_no);
			}
			else
			{
				LOCK_CHARACTER(npc_no);
				DirFastLoopCharacterFrame(npc_no);
				UNLOCK_CHARACTER(npc_no);
			}
        }
        break;
    case DOING_STEP_MOVE_TO:
        {
			LOCK_MAPMASK(0);
            ret = FindCharacterStep(x, y, &dest_x, &dest_y, move_speed);
			UNLOCK_MAPMASK(0);
            switch(ret)
            {
            case STEP_ON_THE_WAY:
				if(dest_x - x != 0 || dest_y - y != 0)
					dir = ApproachCharacterDir(dest_x - x, dest_y - y);
				new_action = GetRunAction(is_fight);
				new_id = GetCharacterFileActionImageID(file_index, new_action);
				if(id != new_id)
				{
					LOCK_CHARACTER(npc_no);
					SetCharacterPosition(npc_no, dest_x, dest_y, dest_z);
					SetCharacterDir(npc_no, dir);
					SetCharacterImageID(npc_no, new_id);
					DirHeadCharacterFrame(npc_no);
					UNLOCK_CHARACTER(npc_no);
				}
				else
				{
					LOCK_CHARACTER(npc_no);
					SetCharacterPosition(npc_no, dest_x, dest_y, dest_z);
					SetCharacterDir(npc_no, dir);
					DirFastLoopCharacterFrame(npc_no);
					UNLOCK_CHARACTER(npc_no);
				}
				break;
            case STEP_ARRIVE:
            case STEP_OBSTRUCT:
            case STEP_OUTSTRETCH:
            default:
				LOCK_CHARACTER(npc_no);
				SetCharacterDoingStep(npc_no, DOING_STEP_IDLE);
				UNLOCK_CHARACTER(npc_no);
				break;
            }
        }
        break;
    default:
        break;
    }
    /---------------------------------------------------------------------
}
*/
/*
//----
//  NPC巡邏
//      一般是在幾個固定點.走動
//----
SLONG   client_do_npc_patrol(SLONG npc_no)
{
    enum
    {   
        DOING_STEP_MOVE_TO          =   0,
        DOING_STEP_IDLE_WHEN_TO     =   1,
        DOING_STEP_MOVE_BACK        =   2,
        DOING_STEP_IDLE_WHEN_BACK   =   3,
    };
    SLONG   doing_step;
    SLONG   dest_x, dest_y, dest_z;
    SLONG   orig_x, orig_y, orig_z;
    SLONG   is_fight;
    SLONG   new_action;
    SLONG   ret = ACTION_RETURN_PROC;
    //
    LOCK_CHARACTER(npc_no);
    doing_step = GetCharacterDoingStep(npc_no);
    GetCharacterDestPosition(npc_no, &dest_x, &dest_y, &dest_z);
    GetCharacterOrigPosition(npc_no, &orig_x, &orig_y, &orig_z);    
    is_fight = IsCharacterOnFightState(npc_no);        
    UNLOCK_CHARACTER(npc_no);
    //
    switch(doing_step)
    {
    case DOING_STEP_MOVE_TO:
        //該DoingKin 只有一個過程 移動到目標點(!!需要保留原來的doingking)
        switch (MinKind_NpcMoveFindPath(npc_no,dest_x, dest_y))
        {
        case NPC_MOVE_MOVEING:      //npc移動在移動過程中
            break;    
        case NPC_MOVE_ARRIVE:       //npc移動到達了目標
            LOCK_CHARACTER(npc_no);
            SetCharacterDoingKindStep(npc_no, DOING_KIND_FIGHT_PATROL,DOING_STEP_IDLE_WHEN_TO);
            UNLOCK_CHARACTER(npc_no);
            break;    
        case NPC_MOVE_CANT_ARRIVE:  //npc移動不能到達
            LOCK_CHARACTER(npc_no);
            SetCharacterDoingKindStep(npc_no, DOING_KIND_FIGHT_PATROL, DOING_STEP_IDLE_WHEN_TO);
            UNLOCK_CHARACTER(npc_no);    
            break;
        }                                                                                                                     
        break;
    case DOING_STEP_IDLE_WHEN_TO:
        //播放待機動畫
        new_action = GetIdleAction(is_fight);
        MinKind_NpcActionLoop(npc_no, new_action);
		break;
    case DOING_STEP_MOVE_BACK:
        //該DoingKin 只有一個過程 移動到目標點(!!需要保留原來的doingking)
        switch (MinKind_NpcMoveFindPath(npc_no,orig_x, orig_y))
        {
        case NPC_MOVE_MOVEING:      //npc移動在移動過程中
            break;    
        case NPC_MOVE_ARRIVE:       //npc移動到達了目標
            LOCK_CHARACTER(npc_no);
            SetCharacterDoingKindStep(npc_no, DOING_KIND_FIGHT_PATROL,DOING_STEP_IDLE_WHEN_BACK);
            UNLOCK_CHARACTER(npc_no);
            break;    
        case NPC_MOVE_CANT_ARRIVE:  //npc移動不能到達
            LOCK_CHARACTER(npc_no);
            SetCharacterDoingKindStep(npc_no, DOING_KIND_FIGHT_PATROL, DOING_STEP_IDLE_WHEN_BACK);
            UNLOCK_CHARACTER(npc_no);    
            break;
        }
		break;
    case DOING_STEP_IDLE_WHEN_BACK:
        //播放待機動畫
        new_action = GetIdleAction(is_fight);
        MinKind_NpcActionLoop(npc_no, new_action);
		break;
    }
    return ret;
    // mark by lijun 2003-04-09
    /----------------------------------------------------------------------
    enum
    {   DOING_STEP_MOVE_TO      =   0,
    DOING_STEP_IDLE_WHEN_TO     =   1,
    DOING_STEP_MOVE_BACK        =   2,
    DOING_STEP_IDLE_WHEN_BACK   =   3,
    };
    SLONG   doing_step;
    SLONG   file_index;
    SLONG   new_id, new_action, id;
    SLONG   dir;
    SLONG   x, y, z, dest_x, dest_y, dest_z;
    SLONG   orig_x, orig_y, orig_z;
    SLONG   move_speed;
    SLONG   is_fight;
    SLONG   ret;

    LOCK_CHARACTER(npc_no);
    doing_step = GetCharacterDoingStep(npc_no);
	GetCharacterPosition(npc_no, &x, &y, &z);
	GetCharacterDestPosition(npc_no, &dest_x, &dest_y, &dest_z);
	GetCharacterOrigPosition(npc_no, &orig_x, &orig_y, &orig_z);
    dir = GetCharacterDir(npc_no);
    move_speed = GetCharacterMoveSpeed(npc_no);
    file_index = GetCharacterFileIndex(npc_no);
    id = GetCharacterImageID(npc_no);
    is_fight = IsCharacterOnFightState(npc_no);
    UNLOCK_CHARACTER(npc_no);

    switch(doing_step)
    {
    case DOING_STEP_MOVE_TO:
        {
			LOCK_MAPMASK(0);
            ret = FindCharacterStep(x, y, &dest_x, &dest_y, move_speed);
			UNLOCK_MAPMASK(0);
            switch(ret)
            {
            case STEP_ON_THE_WAY:
				if(dest_x - x != 0 || dest_y - y != 0)
					dir = ApproachCharacterDir(dest_x - x, dest_y - y);
				new_action = GetRunAction(is_fight);
				new_id = GetCharacterFileActionImageID(file_index, new_action);
				if(id != new_id)
				{
					LOCK_CHARACTER(npc_no);
					SetCharacterDestPosition(npc_no, dest_x, dest_y, dest_z);
					SetCharacterDir(npc_no, dir);
					SetCharacterImageID(npc_no, new_id);
					DirHeadCharacterFrame(npc_no);
					UNLOCK_CHARACTER(npc_no);
				}
				else
				{
					LOCK_CHARACTER(npc_no);
					SetCharacterDestPosition(npc_no, dest_x, dest_y, dest_z);
					SetCharacterDir(npc_no, dir);
					DirFastLoopCharacterFrame(npc_no);
					UNLOCK_CHARACTER(npc_no);
				}
				break;

            case STEP_ARRIVE:
				LOCK_CHARACTER(npc_no);
				SetCharacterPosition(npc_no, dest_x, dest_y, dest_z);
				DirFastLoopCharacterFrame(npc_no);
				SetCharacterDoingStep(npc_no, DOING_STEP_IDLE_WHEN_TO);
				UNLOCK_CHARACTER(npc_no);
				break;

            case STEP_OBSTRUCT:
            case STEP_OUTSTRETCH:
            default:
				LOCK_CHARACTER(npc_no);
				DirFastLoopCharacterFrame(npc_no);
				SetCharacterDoingStep(npc_no, DOING_STEP_IDLE_WHEN_TO);
				UNLOCK_CHARACTER(npc_no);
				break;
            }
            break;
        }
    case DOING_STEP_IDLE_WHEN_TO:
		new_action = GetIdleAction(is_fight);
		new_id = GetCharacterFileActionImageID(file_index, new_action);
		if(id != new_id)
		{
			LOCK_CHARACTER(npc_no);
			SetCharacterImageID(npc_no, new_id);
			DirHeadCharacterFrame(npc_no);
			UNLOCK_CHARACTER(npc_no);
		}
		else
		{
			LOCK_CHARACTER(npc_no);
			DirFastLoopCharacterFrame(npc_no);
			UNLOCK_CHARACTER(npc_no);
		}
		break;

    case DOING_STEP_MOVE_BACK:
        {
			LOCK_MAPMASK(0);
            ret = FindCharacterStep(x, y, &orig_x, &orig_y, move_speed);
			UNLOCK_MAPMASK(0);
            switch(ret)
            {
            case STEP_ON_THE_WAY:
				if(orig_x - x != 0 || orig_y - y != 0)
					dir = ApproachCharacterDir(orig_x - x, orig_y - y);
				new_action = GetRunAction(is_fight);
				new_id = GetCharacterFileActionImageID(file_index, new_action);
				if(id != new_id)
				{
					LOCK_CHARACTER(npc_no);
					SetCharacterPosition(npc_no, orig_x, orig_y, orig_z);
					SetCharacterDir(npc_no, dir);
					SetCharacterImageID(npc_no, new_id);
					DirHeadCharacterFrame(npc_no);
					UNLOCK_CHARACTER(npc_no);
				}
				else
				{
					LOCK_CHARACTER(npc_no);
					SetCharacterPosition(npc_no, orig_x, orig_y, orig_z);
					SetCharacterDir(npc_no, dir);
					DirFastLoopCharacterFrame(npc_no);
					UNLOCK_CHARACTER(npc_no);
				}
				break;

            case STEP_ARRIVE:
				LOCK_CHARACTER(npc_no);
				SetCharacterPosition(npc_no, orig_x, orig_y, orig_z);
				DirFastLoopCharacterFrame(npc_no);
				SetCharacterDoingStep(npc_no, DOING_STEP_IDLE_WHEN_BACK);
				UNLOCK_CHARACTER(npc_no);
				break;

            case STEP_OBSTRUCT:
            case STEP_OUTSTRETCH:
            default:
				LOCK_CHARACTER(npc_no);
				DirFastLoopCharacterFrame(npc_no);
				SetCharacterDoingStep(npc_no, DOING_STEP_IDLE_WHEN_BACK);
				UNLOCK_CHARACTER(npc_no);
				break;
            }
        }
		break;

    case DOING_STEP_IDLE_WHEN_BACK:
		new_action = GetIdleAction(is_fight);
		new_id = GetCharacterFileActionImageID(file_index, new_action);
		if(id != new_id)
		{
			LOCK_CHARACTER(npc_no);
			SetCharacterImageID(npc_no, new_id);
			DirHeadCharacterFrame(npc_no);
			UNLOCK_CHARACTER(npc_no);
		}
		else
		{
			LOCK_CHARACTER(npc_no);
			DirFastLoopCharacterFrame(npc_no);
			UNLOCK_CHARACTER(npc_no);
		}
		break;
    }
    /----------------------------------------------------------------------
}
*/

/******************************************************************************************************************/
/* HIT NPC DOING FUNCTIONS                                                                                        */
/******************************************************************************************************************/
//----
//  npc走過去和莫人對話
//----
SLONG   client_do_npc_talk_with_npc(SLONG npc_no)
{
    enum
    {   
        DOING_STEP_NEAR_TO      =   0,
        DOING_STEP_EXEC_PROC        =   1,
        DOING_STEP_IDLE             =   2,
        //
        NEAR_DISTANCE               =   80,
    };
    SLONG   dest_npc;
    SLONG   doing_step;
    SLONG   x, y, z;
    SLONG   dest_x, dest_y, dest_z;
    SLONG   distance;
    SLONG   dir, dest_npc_dir;
    SLONG   ret = ACTION_RETURN_PROC;
    //
    LOCK_CHARACTER(npc_no);
    doing_step = GetCharacterDoingStep(npc_no);
    dest_npc = GetCharacterDestID(npc_no);
    GetCharacterPosition(npc_no, &x, &y, &z);
    UNLOCK_CHARACTER(npc_no);
    //
    LOCK_CHARACTER(dest_npc);
	GetCharacterPosition(dest_npc, &dest_x, &dest_y, &dest_z);
    dest_npc_dir = GetCharacterDir(dest_npc);
    UNLOCK_CHARACTER(dest_npc);

    switch(doing_step)
    {
    case DOING_STEP_NEAR_TO:
        distance = (SLONG)sqrt( (dest_x - x) * (dest_x - x) + (dest_y - y) * (dest_y - y) );
        if(distance > NEAR_DISTANCE)
        {
            
            switch (MinKind_NpcMoveFindPath(npc_no,dest_x, dest_y))
            {
            case NPC_MOVE_MOVEING:      //npc移動在移動過程中
                break;    
            case NPC_MOVE_ARRIVE:       //npc移動到達了目標
                LOCK_CHARACTER(npc_no);
                SetCharacterDoingKindStep(npc_no, DOING_KIND_TALK_WITH_NPC, DOING_STEP_EXEC_PROC);
                UNLOCK_CHARACTER(npc_no);
                break;    
            case NPC_MOVE_CANT_ARRIVE:  //npc移動不能到達
                LOCK_CHARACTER(npc_no);
                SetCharacterDoingKindStep(npc_no, DOING_KIND_IDLE, 0);
                UNLOCK_CHARACTER(npc_no);    
                //
                ret = ACTION_RETURN_FAIL;
                break;
            }                                         
        }
        else
        {
            if(dest_x - x != 0 || dest_y - y != 0)
                dir = ApproachCharacterDir(dest_x - x, dest_y - y);
            //                
            LOCK_CHARACTER(npc_no);
            SetCharacterDir(npc_no, dir);
            DirHeadCharacterFrame(npc_no);
            SetCharacterDoingStep(npc_no, DOING_STEP_EXEC_PROC);
            UNLOCK_CHARACTER(npc_no);        
        }
		break;

    case DOING_STEP_EXEC_PROC:
	case DOING_STEP_IDLE:
	default:
		LOCK_CHARACTER(npc_no);
		SetCharacterDoingKindStep(npc_no, DOING_KIND_IDLE, 0);
		UNLOCK_CHARACTER(npc_no);
		//讓目標npc轉過來
		dir = ApproachCharacterDir(x - dest_x, y - dest_y);
		LOCK_CHARACTER(dest_npc);
		SetCharacterDir(dest_npc, dir);
		UNLOCK_CHARACTER(dest_npc);
		//
		ret = ACTION_RETURN_OK;
		break;
    }
    return ret;
    //mark by lijun 2003-04-10
/*
    enum
    {   DOING_STEP_NEAR_TO      =   0,
    DOING_STEP_EXEC_PROC        =   1,
    DOING_STEP_IDLE             =   2,
    //
    NEAR_DISTANCE               =   80,
    };
    SLONG   dest_npc;
    SLONG   doing_step;
    SLONG   x, y, z;
    SLONG   dest_x, dest_y, dest_z;
    SLONG   distance;
    SLONG   move_speed;
    SLONG   file_index, id;
    SLONG   new_action, new_id, dir, dest_npc_dir;
    SLONG   ret;
    SLONG   is_fight;

    LOCK_CHARACTER(npc_no);
    doing_step = GetCharacterDoingStep(npc_no);
    dest_npc = GetCharacterDestID(npc_no);
    GetCharacterPosition(npc_no, &x, &y, &z);
    move_speed = GetCharacterMoveSpeed(npc_no);
    file_index = GetCharacterFileIndex(npc_no);
    id = GetCharacterImageID(npc_no);
    dir = GetCharacterDir(npc_no);
    is_fight = IsCharacterOnFightState(npc_no);
    UNLOCK_CHARACTER(npc_no);

    LOCK_CHARACTER(dest_npc);
	GetCharacterPosition(dest_npc, &dest_x, &dest_y, &dest_z);
    dest_npc_dir = GetCharacterDir(dest_npc);
    UNLOCK_CHARACTER(dest_npc);

    switch(doing_step)
    {
    case DOING_STEP_NEAR_TO:
        {
            distance = (SLONG)sqrt( (dest_x - x) * (dest_x - x) + (dest_y - y) * (dest_y - y) );
            if(distance > NEAR_DISTANCE)
            {
				LOCK_MAPMASK(0);
                ret = FindCharacterStep(x, y, &dest_x, &dest_y, move_speed);
				UNLOCK_MAPMASK(0);
                switch(ret)
                {
                case STEP_ON_THE_WAY:
                    {
                        if(dest_x - x != 0 || dest_y - y != 0)
                            dir = ApproachCharacterDir(dest_x - x, dest_y - y);
                        new_action = GetRunAction(is_fight);
						new_id = GetCharacterFileActionImageID(file_index, new_action);
                        if(id != new_id)
                        {
                            LOCK_CHARACTER(npc_no);
							SetCharacterPosition(npc_no, dest_x, dest_y, 0);
							SetCharacterDir(npc_no, dir);
							SetCharacterImageID(npc_no, new_id);
                            DirFastLoopCharacterFrame(npc_no);
                            UNLOCK_CHARACTER(npc_no);
                        }
                        else
                        {
                            LOCK_CHARACTER(npc_no);
							SetCharacterPosition(npc_no, dest_x, dest_y, 0);
                            SetCharacterDir(npc_no, dir);
                            DirFastLoopCharacterFrame(npc_no);
                            UNLOCK_CHARACTER(npc_no);
                        }
                        break;
                    }
                case STEP_ARRIVE:
                    {
                        LOCK_CHARACTER(npc_no);
						SetCharacterPosition(npc_no, dest_x, dest_y, 0);
                        DirFastLoopCharacterFrame(npc_no);
						SetCharacterDoingStep(npc_no, DOING_STEP_EXEC_PROC);
                        UNLOCK_CHARACTER(npc_no);
                        break;
                    }
                case STEP_OBSTRUCT:
                case STEP_OUTSTRETCH:
                default:
                    {
                        LOCK_CHARACTER(npc_no);
						SetCharacterDestPosition(npc_no, x, y, 0);
                        DirFastLoopCharacterFrame(npc_no);
						SetCharacterDoingKindStep(npc_no, DOING_KIND_IDLE, 0);
                        UNLOCK_CHARACTER(npc_no);
                        break;
                    }
                }
            }
            else
            {
                if(dest_x - x != 0 || dest_y - y != 0)
                    dir = ApproachCharacterDir(dest_x - x, dest_y - y);
                LOCK_CHARACTER(npc_no);
				SetCharacterDir(npc_no, dir);
                DirHeadCharacterFrame(npc_no);
				SetCharacterDoingStep(npc_no, DOING_STEP_EXEC_PROC);
                UNLOCK_CHARACTER(npc_no);
            }
        }
		break;

    case DOING_STEP_EXEC_PROC:
	case DOING_STEP_IDLE:
	default:
		LOCK_CHARACTER(npc_no);
		SetCharacterDoingKindStep(npc_no, DOING_KIND_IDLE, 0);
		UNLOCK_CHARACTER(npc_no);
		break;
    }
*/
}
    
/*
//----
//  走過去攻擊莫人
//      1.接近目標npc
//      2.開始攻擊目標npc
//----
SLONG   client_do_npc_attack_npc(SLONG npc_no)
{
    enum
    {   
        DOING_STEP_NEAR_TO              =   0,
        DOING_STEP_ATTACK_NPC           =   2,
	    DOING_STEP_ATTACK_PANT			=	3,
        DOING_STEP_RESPONSE             =   4,
        //
        SPECIFIC_ATTACK_DISTANCE        =   64,
        NPC_ATTACK_IMAGE_REPEAT         =   1,
	    PANT_TOTAL_TICKS				=	20, //Need to add to monster's data.
    };
    SLONG   doing_step;
    SLONG   dest_npc;
    SLONG   dest_x, dest_y, dest_z;
    SLONG   x, y,z;
    SLONG   dir;
    SLONG   file_index;
    SLONG   distance, magic_distance, sight;
    SLONG   magic_index;
    SLONG   ret = ACTION_RETURN_PROC;
    //
    LOCK_CHARACTER(0);
    doing_step = GetCharacterDoingStep(npc_no);
    dest_npc = GetCharacterDestID(npc_no);
	GetCharacterPosition(npc_no, &x, &y, &z);
    file_index = GetCharacterFileIndex(npc_no);	
    magic_index = GetCharacterDoingMagic(npc_no);    
    sight = GetCharacterSightRange(npc_no);
    //
	GetCharacterPosition(dest_npc, &dest_x, &dest_y, &dest_z);
    UNLOCK_CHARACTER(0);
    //
    magic_distance = GetSkillMagicDisChargeDistance(magic_index, 0);    

    switch(doing_step)
    {
    case DOING_STEP_NEAR_TO:
        distance = (SLONG) sqrt( (dest_x - x) * (dest_x - x) + (dest_y - y) * (dest_y - y) );
        if(distance > sight)
        {
            //在視野之外..不需要攻擊..改變狀態到待機
            LOCK_CHARACTER(npc_no);
            SetCharacterDoingKindStep(npc_no, DOING_KIND_IDLE, 0);
            UNLOCK_CHARACTER(npc_no);
        }
        else if (distance > magic_distance)
        {
            //在視野之內...移動過去攻擊
                //1.移動過去
                //2.到不了..變狀態為待機
                switch (MinKind_NpcMoveFindPath(npc_no,dest_x, dest_y))
                {
                case NPC_MOVE_MOVEING:      //npc移動在移動過程中
                    break;    
                case NPC_MOVE_ARRIVE:       //npc移動到達了目標
                    LOCK_CHARACTER(npc_no);
                    SetCharacterDoingKindStep(npc_no, DOING_KIND_ATTACK_NPC, DOING_STEP_ATTACK_NPC);
                    UNLOCK_CHARACTER(npc_no);
                    break;    
                case NPC_MOVE_CANT_ARRIVE:  //npc移動不能到達
                    LOCK_CHARACTER(npc_no);
                    SetCharacterDoingKindStep(npc_no, DOING_KIND_IDLE, 0);
                    UNLOCK_CHARACTER(npc_no);    
                    //
                    ret = ACTION_RETURN_FAIL;
                    break;
                }                    
        }
        else
        {
            //進入攻擊範圍..改變狀態為攻擊
            LOCK_CHARACTER(npc_no);
            SetCharacterDoingKindStep(npc_no, DOING_KIND_ATTACK_NPC, DOING_STEP_ATTACK_NPC);
            UNLOCK_CHARACTER(npc_no);
        }
        break;
    case DOING_STEP_ATTACK_NPC:
        //確保npc朝向攻擊的目標
        dir = ApproachCharacterDir(dest_x - x, dest_y - y);        
        LOCK_CHARACTER(npc_no);
        SetCharacterDir(npc_no, dir);
        UNLOCK_CHARACTER(npc_no);        
        // 播放該動畫一次
        switch (MinKind_NpcActionOneTime(npc_no, AC_ATTACK_0))
        {
        case NPC_KEY_FRAME_NONE://非關鍵幀
            break;
        case NPC_KEY_FRAME_HEAD://關鍵幀(第一幀)
            break;
        case NPC_KEY_FRAME_HALF://中間幀
            play_fight_voice(0, npc_no, file_index, DOING_KIND_ATTACK_NPC, 0, x, y);
            break;        
        case NPC_KEY_FRAME_TAIL://最後幀
            LOCK_CHARACTER(npc_no);
            SetCharacterDoingKindStep(npc_no, DOING_KIND_IDLE, 0);
            UNLOCK_CHARACTER(npc_no);        
            //
            ret = ACTION_RETURN_OK;
            break;
        }            
        break;
    }
    return ret;
    //mark by lijun 2003-04-10
    /----------------------------------------------------------------------
    enum
    {   
        DOING_STEP_NEAR_TO      =   0,
        DOING_STEP_ATTACK_NPC       =   1,
        DOING_STEP_RESPONSE         =   3,
        //
        SPECIFIC_ATTACK_DISTANCE    =   64,
        NPC_ATTACK_IMAGE_REPEAT     =   1
    };
    SLONG   doing_step;
    SLONG   dest_npc;
    SLONG   dest_x, dest_y, dest_z;
    SLONG   x, y, z, dir, new_dir;
    SLONG   file_index, id;
    SLONG   new_action, new_id;
    SLONG   move_speed, frame_flag;
    SLONG   distance, attack_distance, sight;
    SLONG   ret;
	SLONG	find_pos, attack_x, attack_y;
    SLONG   is_fight, magic_no;
    //
    LOCK_CHARACTER(0);
    doing_step = GetCharacterDoingStep(npc_no);
    dest_npc = GetCharacterDestID(npc_no);
	GetCharacterPosition(npc_no, &x, &y, &z);
    dir = GetCharacterDir(npc_no);
    move_speed = GetCharacterMoveSpeed(npc_no);
    file_index = GetCharacterFileIndex(npc_no);
    id = GetCharacterImageID(npc_no);
    is_fight = IsCharacterOnFightState(npc_no);
    //attack_distance = game_npc[npc_no].attack_distance;
    sight = GetCharacterSightRange(npc_no);
    //
	GetCharacterPosition(dest_npc, &dest_x, &dest_y, &dest_z);
    UNLOCK_CHARACTER(0);

    // Jack, for test. [7/30/2002]
    attack_distance = 32;

    switch(doing_step)
    {
    case DOING_STEP_NEAR_TO:
        {
            distance = (SLONG) sqrt( (dest_x - x) * (dest_x - x) + (dest_y - y) * (dest_y - y) );
            if(distance > sight)
            {
                LOCK_CHARACTER(npc_no);
				SetCharacterDoingKindStep(npc_no, DOING_KIND_IDLE, 0);
                UNLOCK_CHARACTER(npc_no);
            }
			else
			{
				GatherMapCharacterMaskPosition();
				LOCK_MAPMASK(0);
				UpdateMapCharacterMask();
				ClearMapDynamicCharacterMask(x, y);
				find_pos = FindBestAttackPosition(x, y, dest_x, dest_y, attack_distance, &attack_x, &attack_y);
				UNLOCK_MAPMASK(0);

				if(find_pos == TTN_OK)
				{
					dest_x = attack_x;
					dest_y = attack_y;

					LOCK_MAPMASK(0);
					ClearMapDynamicCharacterMask(x, y);
					ret = TrendFindCharacterStep(x, y, &dest_x, &dest_y, move_speed, MASK_STOP | MASK_DYNAMIC_NPC);
					RemoveMapCharacterMask();
					UNLOCK_MAPMASK(0);

					switch(ret)
					{
					case STEP_ON_THE_WAY:
						{
							if(dest_x - x != 0 || dest_y - y != 0)
								dir = ApproachCharacterDir(dest_x - x, dest_y - y);
                            new_action = GetRunAction(is_fight);
                            new_id = GetCharacterFileActionImageID(file_index, new_action);
							if(id != new_id)
							{
								LOCK_CHARACTER(npc_no);
								SetCharacterPosition(npc_no, dest_x, dest_y, dest_z);
								SetCharacterDir(npc_no, dir);
								SetCharacterImageID(npc_no, new_id);
								DirFastLoopCharacterFrame(npc_no);
								UNLOCK_CHARACTER(npc_no);
							}
							else
							{
								LOCK_CHARACTER(npc_no);
								SetCharacterPosition(npc_no, dest_x, dest_y, dest_z);
								SetCharacterDir(npc_no, dir);
								DirFastLoopCharacterFrame(npc_no);
								UNLOCK_CHARACTER(npc_no);
							}
							break;
						}
					case STEP_ARRIVE:
						{
							LOCK_CHARACTER(npc_no);
							SetCharacterPosition(npc_no, dest_x, dest_y, dest_z);
							DirFastLoopCharacterFrame(npc_no);
							SetCharacterDoingStep(npc_no, DOING_STEP_ATTACK_NPC);
							UNLOCK_CHARACTER(npc_no);
							break;
						}
					case STEP_OBSTRUCT:
					case STEP_OUTSTRETCH:
					default:
						{
							LOCK_CHARACTER(npc_no);
							SetCharacterDestPosition(npc_no, x, y, z);
							DirFastLoopCharacterFrame(npc_no);
							SetCharacterDoingKindStep(npc_no, DOING_KIND_IDLE, 0);
							UNLOCK_CHARACTER(npc_no);
							break;
						}
					}
				}
				else
				{
					LOCK_CHARACTER(npc_no);
					SetCharacterDestPosition(npc_no, x, y, z);
					DirFastLoopCharacterFrame(npc_no);
					SetCharacterDoingKindStep(npc_no, DOING_KIND_IDLE, 0);
					UNLOCK_CHARACTER(npc_no);
				}
			}
            break;
        }
    case DOING_STEP_ATTACK_NPC:
        {
            if(dest_x - x != 0 || dest_y - y != 0)
                new_dir = ApproachCharacterDir(dest_x - x, dest_y - y);
            new_action = AC_ATTACK_0;
            new_id = GetCharacterFileActionImageID(file_index, new_action);
            if((id != new_id) || dir != new_dir)
            {
                LOCK_CHARACTER(npc_no);
				SetCharacterImageID(npc_no, new_id);
				SetCharacterDir(npc_no, new_dir);
                DirHeadCharacterFrame(npc_no);
                UNLOCK_CHARACTER(npc_no);

            }
            else
            {
                LOCK_CHARACTER(npc_no);
                magic_no = GetCharacterDoingMagic(npc_no);
                frame_flag = DirFastHalfCharacterFrame(npc_no);
                UNLOCK_CHARACTER(npc_no);

                if(NPC_KEY_FRAME_HALF == frame_flag)
                {
                    //compute_npc_attack_npc_effect(npc_no, dest_npc, magic_no);
					play_fight_voice(0, npc_no, file_index, DOING_KIND_ATTACK_NPC, 0, x, y);
                }
                else if(NPC_KEY_FRAME_TAIL == frame_flag)
                {
                    LOCK_CHARACTER(npc_no);
					SetCharacterDoingKindStep(npc_no, DOING_KIND_IDLE, 0);
                    UNLOCK_CHARACTER(npc_no);
                }
            }
            break;
        }
    }
    /----------------------------------------------------------------------
}
*/
//----
//連擊
//      連續播放攻擊動作.
//
//----
SLONG   client_do_npc_sequential_attack_npc(SLONG npc_no)
{
    enum
    {   
        DOING_STEP_ATTACK_NPC_1_START       =   0,  //開始第1擊(對應第n擊為 2*n)
        DOING_STEP_ATTACK_NPC_1_RUNNING     =   1,  //正在進行第1擊(對應第n擊為 2*n+1)
        //
        SPECIFIC_ATTACK_DISTANCE            =   64,
        NPC_ATTACK_IMAGE_REPEAT             =   1,
        //
        NPC_SEQUENTIAL_FINISH_FRAME         =   4   //收招動作的幀數 
    };
    SLONG   max_step;//目前只到第3擊
    SLONG   doing_step;
    SLONG   dest_npc;
    SLONG   x, y, z;
    SLONG   dir;
    SLONG   magic_no, magic_level;
    SLONG   file_index, id;
    SLONG   new_action, new_id;
    SLONG   sight;
    SLONG   is_fight, is_block;
    SLONG   action_block;
    SLONG   attack_step;        //第幾擊, 從1開始.
    SLONG   sequential_step;
    SLONG   dx, dy, dz;
    SLONG   ret = ACTION_RETURN_PROC;
    //
    LOCK_CHARACTER(npc_no);
    doing_step = GetCharacterDoingStep(npc_no);
    dest_npc = GetCharacterDestID(npc_no);
    GetCharacterPosition(npc_no, &x, &y, &z);
    file_index = GetCharacterFileIndex(npc_no);
    id = GetCharacterImageID(npc_no);
    is_fight = IsCharacterOnFightState(npc_no);
    is_block = IsCharacterOnBlockState(npc_no);
    action_block = StatuseToActionBlocks(is_fight, is_block);    
    sight = GetCharacterSightRange(npc_no);
    magic_no = GetCharacterDoingMagic(npc_no);    
    magic_level = GetCharacterSpecialSkillLevel(npc_no, magic_no);
    GetCharacterDestPosition(npc_no, &dx, &dy, &dz);    
    UNLOCK_CHARACTER(npc_no);
    //
    if (dest_npc>=0)
    {
        LOCK_CHARACTER(npc_no);
        GetCharacterPosition(dest_npc, &dx, &dy, &dz);
        UNLOCK_CHARACTER(npc_no);
    }
    //
    dir = ApproachCharacterDir(dx - x, dy - y);
    LOCK_CHARACTER(npc_no);
    SetCharacterDir(npc_no, dir);
    UNLOCK_CHARACTER(npc_no);
    //
    max_step = GetSkillActionCount(magic_no, magic_level);
    //
    attack_step = doing_step;
    //
    new_action = GetSequentialAttackAction(attack_step);
    new_id = GetCharacterFileActionImageID(file_index, action_block, new_action);
    //
    switch (MinKind_NpcImgIdOneTime(npc_no, new_id, NPC_SEQUENTIAL_FINISH_FRAME))
    {
    case NPC_KEY_FRAME_HEAD:
        //剛開始的時候..需要..清空..連擊的步數
        LOCK_CHARACTER(npc_no);
        SetCharacterSequentialStep(npc_no, attack_step);
        UNLOCK_CHARACTER(npc_no);
        break;
    case NPC_KEY_FRAME_BACK:
        //需要到下個動作
        LOCK_CHARACTER(npc_no);
        sequential_step = GetCharacterSequentialStep(npc_no);
        if ((sequential_step>attack_step) && (attack_step < max_step-1))
        {
            SetCharacterDoingStep(npc_no, doing_step + 1);  //下1擊
        }
        UNLOCK_CHARACTER(npc_no);
        break;
    case NPC_KEY_FRAME_HALF:
        //到了攻擊幀
        play_fight_voice(0, npc_no, file_index, DOING_KIND_SEQUENTIAL_ATTACK_NPC, attack_step, x, y);
        break;
    case NPC_KEY_FRAME_TAIL:
        //播放完整個動畫
        LOCK_CHARACTER(npc_no);
        SetCharacterDoingKindStep(npc_no, DOING_KIND_IDLE, 0);
        UNLOCK_CHARACTER(npc_no);
        ret = ACTION_RETURN_OK;
        break;
    }
    return ret;
    // mark by lijun 2004-04-10
    /*
    enum
    {   
        DOING_STEP_NEAR_TO              =   0,  //接近目標
        DOING_STEP_ATTACK_NPC_1_START       =   2,  //開始第1擊(對應第n擊為 2*n)
        DOING_STEP_ATTACK_NPC_1_RUNNING     =   3,  //正在進行第1擊(對應第n擊為 2*n+1)
        //
        SPECIFIC_ATTACK_DISTANCE            =   64,
        NPC_ATTACK_IMAGE_REPEAT             =   1
    };
    SLONG   doing_step;
    SLONG   dest_npc;
    SLONG   dest_x, dest_y, dest_z, x, y, z;
    SLONG   file_index, id, dir;
    SLONG   new_action, new_id;
    SLONG   move_speed, frame_flag;
    SLONG   distance, attack_distance, sight;
    SLONG   ret;
	SLONG	find_pos, attack_x, attack_y;
    SLONG   is_fight, magic_no;
    SLONG   attack_step;        //第幾擊, 從1開始.
    SLONG   sequential_step;
    SLONG   need_voice;

    need_voice = false;
    LOCK_CHARACTER(npc_no);
    doing_step = GetCharacterDoingStep(npc_no);
    dest_npc = GetCharacterDestID(npc_no);
    GetCharacterPosition(npc_no, &x, &y, &z);
    move_speed = GetCharacterMoveSpeed(npc_no);
    file_index = GetCharacterFileIndex(npc_no);
    id = GetCharacterImageID(npc_no);
    is_fight = IsCharacterOnFightState(npc_no);
    magic_no = GetCharacterDoingMagic(npc_no);
    //attack_distance = game_npc[npc_no].attack_distance;
    sight = GetCharacterSightRange(npc_no);
    //
    UNLOCK_CHARACTER(npc_no);

    // Jack, for test. [7/30/2002]
    attack_distance = 32;

    LOCK_CHARACTER(dest_npc);
    GetCharacterPosition(dest_npc, &dest_x, &dest_y, &dest_z);
    UNLOCK_CHARACTER(dest_npc);

    switch(doing_step)
    {
    case DOING_STEP_NEAR_TO:
        {
            distance = (SLONG) sqrt( (dest_x - x) * (dest_x - x) + (dest_y - y) * (dest_y - y) );
            if(distance > sight)
            {
                LOCK_CHARACTER(npc_no);
                SetCharacterDoingKindStep(npc_no, DOING_KIND_IDLE, 0);
                UNLOCK_CHARACTER(npc_no);
            }
			else
			{
				GatherMapCharacterMaskPosition();
				LOCK_MAPMASK(0);
				UpdateMapCharacterMask();
				ClearMapDynamicCharacterMask(x, y);
				find_pos = FindBestAttackPosition(x, y, dest_x, dest_y, attack_distance, &attack_x, &attack_y);
				UNLOCK_MAPMASK(0);

				if(find_pos == TTN_OK)
				{
					dest_x = attack_x;
					dest_y = attack_y;

					LOCK_MAPMASK(0);
					ClearMapDynamicCharacterMask( x, y );
					ret = FindCharacterMaskStep( x, y, &dest_x, &dest_y, move_speed, MASK_STOP | MASK_DYNAMIC_NPC);
					RemoveMapCharacterMask();
					UNLOCK_MAPMASK(0);

					switch(ret)
					{
					case STEP_ON_THE_WAY:
						{
							if(dest_x - x != 0 || dest_y - y != 0)
								dir = ApproachCharacterDir(dest_x - x, dest_y - y);
                            new_action = GetRunAction(is_fight);
                            new_id = GetCharacterFileActionImageID(file_index, new_action);

                            LOCK_CHARACTER(npc_no);
                            id = GetCharacterImageID(npc_no);
                            if(id != new_id)
                            {
                                SetCharacterDir(npc_no, dir);
                                SetCharacterImageID(npc_no, new_id);
                                DirHeadCharacterFrame(npc_no);
                                SetCharacterPosition(npc_no, dest_x, dest_y, dest_z);
                            }
                            else
                            {
                                SetCharacterDir(npc_no, dir);
                                DirFastLoopCharacterFrame(npc_no);
                                SetCharacterPosition(npc_no, dest_x, dest_y, dest_z);
                            }
                            UNLOCK_CHARACTER(npc_no);
							break;
						}
					case STEP_ARRIVE:
						{
							LOCK_CHARACTER(npc_no);
                            SetCharacterPosition(npc_no, dest_x, dest_y, dest_z);
							DirFastLoopCharacterFrame(npc_no);
                            SetCharacterSequentialStep(npc_no, false);
                            SetCharacterDoingStep(npc_no, DOING_STEP_ATTACK_NPC_1_START);
							UNLOCK_CHARACTER(npc_no);
							break;
						}
					case STEP_OBSTRUCT:
					case STEP_OUTSTRETCH:
					default:
						{
							LOCK_CHARACTER(npc_no);
                            SetCharacterPosition(npc_no, dest_x, dest_y, dest_z);
							DirFastLoopCharacterFrame(npc_no);
                            SetCharacterDoingKindStep(npc_no, DOING_KIND_IDLE, 0);
							UNLOCK_CHARACTER(npc_no);
							break;
						}
					}
				}
				else
				{
					LOCK_CHARACTER(npc_no);
                    SetCharacterDestPosition(npc_no, x, y, z);
					DirFastLoopCharacterFrame(npc_no);
                    SetCharacterDoingKindStep(npc_no, DOING_KIND_IDLE, 0);
					UNLOCK_CHARACTER(npc_no);
				}
			}
        }
        break;

    default: //ATTACK_NPC_START, ATTACK_NPC_RUNNING
        attack_step = doing_step / 2;
        if(attack_step >= 1 && attack_step <= 3)    //目前只到第3擊
        {
            if(doing_step % 2 == 0) //開始攻擊
            {
                new_action = GetSequentialAttackAction(attack_step);
                new_id = GetCharacterFileActionImageID(file_index, new_action);
                if(dest_x - x != 0 || dest_y - y != 0)
                    dir = ApproachCharacterDir(dest_x - x, dest_y - y);
                LOCK_CHARACTER(npc_no);
                SetCharacterDir(npc_no, dir);
                SetCharacterImageID(npc_no, new_id);
                DirHeadCharacterFrame(npc_no);
                SetCharacterDoingStep(npc_no, doing_step + 1); //進行攻擊
                UNLOCK_CHARACTER(npc_no);
            }
            else    //ATTACK_NPC_RUNNING
            {
                LOCK_CHARACTER(npc_no);
                frame_flag = DirSequentialCharacterFrame(npc_no);
                UNLOCK_CHARACTER(npc_no);
                
                switch(frame_flag)
                {
                case NPC_KEY_FRAME_HALF:
					play_fight_voice(0, npc_no, file_index, DOING_KIND_SEQUENTIAL_ATTACK_NPC, attack_step, x, y);
                    break;
                    
                case NPC_KEY_FRAME_BACK:
                    LOCK_CHARACTER(npc_no);
                    sequential_step = GetCharacterSequentialStep(npc_no);
                    if(sequential_step && attack_step < 3)  //目前強制為3擊.
                    {
                        SetCharacterSequentialStep(npc_no, false);
                        SetCharacterDoingStep(npc_no, doing_step + 1);  //下1擊
                    }
                    UNLOCK_CHARACTER(npc_no);
                    break;
                    
                case NPC_KEY_FRAME_TAIL:
                    LOCK_CHARACTER(npc_no);
                    SetCharacterDoingKindStep(npc_no, DOING_KIND_IDLE, 0);
                    UNLOCK_CHARACTER(npc_no);
                    break;
                }
            }
        }
        else
        {
            LOCK_CHARACTER(npc_no);
            SetCharacterDoingKindStep(npc_no, DOING_KIND_IDLE, 0);
            UNLOCK_CHARACTER(npc_no);
        }
        break;
    }
    */    
}


SLONG   client_do_npc_magic_npc(SLONG npc_no)
{
    // Jack, todo [14:22,11/6/2002]
    return ACTION_RETURN_PROC;
}

/******************************************************************************************************************/
/* HIT MAP ITEM DOING FUNCTIONS                                                                                   */
/******************************************************************************************************************/
//----
//  npc走過去檢道具
//      過程狀態
//          1.移動過去
//          2.
//----
SLONG   client_do_npc_pick_item(SLONG npc_no)
{
    enum
    {   DOING_STEP_NEAR_TO  =   0,
    DOING_STEP_PICK_ITEM    =   1,
    DOING_STEP_IDLE         =   2,
    //
    PICKABLE_DISTANCE       =   40 * 40,
    };
    SLONG   item_x, item_y, item_z;
    SLONG   hand_it;
    SLONG   doing_step;
    SLONG   x, y, z, dest_x, dest_y;
    SLONG   distance;
    SLONG   is_fight;
    SLONG   new_action;
    SLONG   ret = ACTION_RETURN_PROC;
    //
    LOCK_CHARACTER(npc_no);
	GetCharacterDestPosition(npc_no, &item_x, &item_y, &item_z);	//dest for item
    doing_step = GetCharacterDoingStep(npc_no);
	GetCharacterPosition(npc_no, &x, &y, &z);
    is_fight = IsCharacterOnFightState(npc_no);	
    UNLOCK_CHARACTER(npc_no);

    hand_it = FALSE;


    switch(doing_step)
    {
    case DOING_STEP_NEAR_TO:
        {
            dest_x = item_x;
            dest_y = item_y;
            distance = (dest_x - x) * (dest_x - x) + (dest_y - y) * (dest_y - y);
            if(distance > PICKABLE_DISTANCE)
            {
                switch (MinKind_NpcMoveFindPath(npc_no,dest_x, dest_y))
                {
                case NPC_MOVE_MOVEING:      //npc移動在移動過程中
                    break;    
                case NPC_MOVE_ARRIVE:       //npc移動到達了目標
                    LOCK_CHARACTER(npc_no);
                    SetCharacterDoingKindStep(npc_no, DOING_KIND_PICK_ITEM, DOING_STEP_PICK_ITEM);
                    UNLOCK_CHARACTER(npc_no);
                    break;    
                case NPC_MOVE_CANT_ARRIVE:  //npc移動不能到達
                    LOCK_CHARACTER(npc_no);
                    SetCharacterDoingKindStep(npc_no, DOING_STEP_IDLE, 0);
                    UNLOCK_CHARACTER(npc_no);
                    //
                    ret = ACTION_RETURN_FAIL;
                    break;
                }
            }
            else
            {
                LOCK_CHARACTER(npc_no);
				SetCharacterDoingStep(npc_no, DOING_STEP_PICK_ITEM);
                UNLOCK_CHARACTER(npc_no);
            }
            break;
        }
    case DOING_STEP_PICK_ITEM:
        {
            LOCK_CHARACTER(npc_no);
			SetCharacterDoingStep(npc_no, DOING_STEP_IDLE);
            UNLOCK_CHARACTER(npc_no);
        }
        break;
    case DOING_STEP_IDLE:
        //播放待機動畫
        //new_action = GetIdleAction(is_fight);
        new_action = AC_WAIT_0;
        MinKind_NpcActionLoop(npc_no, new_action);
        //
        ret = ACTION_RETURN_OK;
        break;
    }
    return ret;
    // mark by lijun 2003-04-10
    /* 
    enum
    {   DOING_STEP_NEAR_TO  =   0,
    DOING_STEP_PICK_ITEM    =   1,
    DOING_STEP_IDLE         =   2,
    //
    PICKABLE_DISTANCE       =   40 * 40,
    };
    SLONG   item_x, item_y, item_z;
    SLONG   hand_it;
    SLONG   doing_step;
    SLONG   file_index, new_action;
    SLONG   new_id, id, dir;
    SLONG   x, y, z, dest_x, dest_y;
    SLONG   distance;
    SLONG   move_speed;
    SLONG   ret;
    SLONG   is_fight;

    LOCK_CHARACTER(npc_no);
	GetCharacterDestPosition(npc_no, &item_x, &item_y, &item_z);	//dest for item
    doing_step = GetCharacterDoingStep(npc_no);
    file_index = GetCharacterFileIndex(npc_no);
	GetCharacterPosition(npc_no, &x, &y, &z);
    move_speed = GetCharacterMoveSpeed(npc_no);
    dir = GetCharacterDir(npc_no);
	id = GetCharacterImageID(npc_no);
    is_fight = IsCharacterOnFightState(npc_no);
    UNLOCK_CHARACTER(npc_no);

    hand_it = FALSE;


    switch(doing_step)
    {
    case DOING_STEP_NEAR_TO:
        {
            dest_x = item_x;
            dest_y = item_y;
            distance = (dest_x - x) * (dest_x - x) + (dest_y - y) * (dest_y - y);
            if(distance > PICKABLE_DISTANCE)
            {
				LOCK_MAPMASK(0);
                ret = FindCharacterStep(x, y, &dest_x, &dest_y, move_speed);
				UNLOCK_MAPMASK(0);
                switch(ret)
                {
                case STEP_ON_THE_WAY:
                    {
                        if(dest_x - x != 0 || dest_y - y != 0)
                            dir = ApproachCharacterDir(dest_x - x, dest_y - y);
                        new_action = GetRunAction(is_fight);
						new_id = GetCharacterFileActionImageID(file_index, new_action);
                        if(id != new_id)
                        {
                            LOCK_CHARACTER(npc_no);
							SetCharacterPosition(npc_no, dest_x, dest_y, 0);
							SetCharacterDir(npc_no, dir);
							SetCharacterImageID(npc_no, new_id);
                            DirLoopCharacterFrame(npc_no);
                            UNLOCK_CHARACTER(npc_no);
                        }
                        else
                        {
                            LOCK_CHARACTER(npc_no);
							SetCharacterPosition(npc_no, dest_x, dest_y, 0);
							SetCharacterDir(npc_no, dir);
                            DirLoopCharacterFrame(npc_no);
                            UNLOCK_CHARACTER(npc_no);
                        }
                        break;
                    }
                case STEP_ARRIVE:
                    {
                        LOCK_CHARACTER(npc_no);
						SetCharacterPosition(npc_no, dest_x, dest_y, 0);
                        DirLoopCharacterFrame(npc_no);
						SetCharacterDoingStep(npc_no, DOING_STEP_PICK_ITEM);
                        UNLOCK_CHARACTER(npc_no);
                        break;
                    }
                case STEP_OBSTRUCT:
                case STEP_OUTSTRETCH:
                default:
                    {
                        LOCK_CHARACTER(npc_no);
						SetCharacterDestPosition(npc_no, x, y, 0);
                        DirLoopCharacterFrame(npc_no);
						SetCharacterDoingStep(npc_no, DOING_STEP_IDLE);
                        UNLOCK_CHARACTER(npc_no);
                        break;
                    }
                }
            }
            else
            {
                LOCK_CHARACTER(npc_no);
				SetCharacterDoingStep(npc_no, DOING_STEP_PICK_ITEM);
                UNLOCK_CHARACTER(npc_no);
            }
            break;
        }
    case DOING_STEP_PICK_ITEM:
        {
            LOCK_CHARACTER(npc_no);
			SetCharacterDoingStep(npc_no, DOING_STEP_IDLE);
            UNLOCK_CHARACTER(npc_no);
        }
        break;
    case DOING_STEP_IDLE:
        {
            new_action = AC_WAIT_0;
			new_id = GetCharacterFileActionImageID(file_index, new_action);
            if(id != new_action)
            {
                LOCK_CHARACTER(npc_no);
				SetCharacterImageID(npc_no, new_id);
                DirLoopCharacterFrame(npc_no);
                UNLOCK_CHARACTER(npc_no);
            }
            else
            {
                LOCK_CHARACTER(npc_no);
                DirLoopCharacterFrame(npc_no);
                UNLOCK_CHARACTER(npc_no);
            }
        }
        break;
    }
    */    
}


/******************************************************************************************************************/
/* PASSIVE DOING FUNCTIONS                                                                                        */
/******************************************************************************************************************/
//----
//被擊
//----
SLONG   client_do_npc_beated(SLONG npc_no)
{
    SLONG   file_index;
    SLONG   x,y,z;
    SLONG   beated_x,beated_y;
    SLONG   dir;
    SLONG   ret = ACTION_RETURN_PROC;
    //
    LOCK_CHARACTER(npc_no);    
    GetCharacterPosition(npc_no, &x, &y, &z);
    GetCharacterBeatedXY(npc_no, &beated_x, &beated_y);
    dir = ApproachCharacterDir(beated_x - x, beated_y - y);
    SetCharacterDir(npc_no, dir);
    UNLOCK_CHARACTER(npc_no);    
    //
    switch (MinKind_NpcActionOneTime(npc_no, AC_BEATED))
    {
        case NPC_KEY_FRAME_HALF://中間幀
            file_index = GetCharacterFileIndex(npc_no);
            play_fight_voice(0, npc_no, file_index, DOING_KIND_BEATED, 0, x, y);
            //增加命中效果
            LOCK_CHARACTER(npc_no);    
            set_npc_ext_id(npc_no, MAKE_OBJECT_ID(OBJECT_TYPE_MAGIC, 403));	
            set_npc_ext_frame(npc_no, 0);
            UNLOCK_CHARACTER(npc_no);                
            break;        
        case NPC_KEY_FRAME_TAIL://最後幀
            LOCK_CHARACTER(npc_no);
            SetCharacterDoingKindStep(npc_no, DOING_KIND_IDLE, 0);
            UNLOCK_CHARACTER(npc_no);
            //
            ret = ACTION_RETURN_OK;        
            break;            
        case NPC_KEY_FRAME_NONE://非關鍵幀
        case NPC_KEY_FRAME_HEAD://關鍵幀(第一幀)
        case NPC_KEY_FRAME_BACK://收招幀
        default:
            loop_npc_ext_frame(npc_no);
            break;    
    }
    //
    return ret;
    //
    // mark by lijun 2003-04-14
    /*
    enum
    {   
        DOING_STEP_BEATED_START     =   0,      //開始被擊
        DOING_STEP_BEATED_RUNNING       =   1,      //被擊中
    };
    SLONG   doing_step, file_index;
    SLONG   new_action, new_id;
    SLONG   beated_x, beated_y;
    SLONG   x, y, z, dir;
    SLONG   need_voice;
    //
    need_voice = false;
    //
    LOCK_CHARACTER(npc_no);
    doing_step = GetCharacterDoingStep(npc_no);
    switch(doing_step)
    {
    case DOING_STEP_BEATED_START:
        file_index = GetCharacterFileIndex(npc_no);
        new_action = AC_BEATED;
        new_id = GetCharacterFileActionImageID(file_index, new_action);
        //
        GetCharacterPosition(npc_no, &x, &y, &z);
        GetCharacterBeatedXY(npc_no, &beated_x, &beated_y);
        dir = ApproachCharacterDir(beated_x - x, beated_y - y);
        SetCharacterImageID(npc_no, new_id);
        SetCharacterDir(npc_no, dir);
        DirHeadCharacterFrame(npc_no);
        set_npc_ext_id(npc_no, MAKE_OBJECT_ID(OBJECT_TYPE_MAGIC, 403));	// Jack, for use Petra Magic images. [1/27/2003]
        //set_npc_ext_id(npc_no, MAKE_OBJECT_ID(OBJECT_TYPE_MAGIC, 2));
        set_npc_ext_frame(npc_no, 0);
        //
        SetCharacterDoingStep(npc_no, DOING_STEP_BEATED_RUNNING);
        //
        need_voice = true;
        break;

    case DOING_STEP_BEATED_RUNNING:
        if(NPC_KEY_FRAME_TAIL == DirFastTailCharacterFrame(npc_no))
        {
            SetCharacterDoingKindStep(npc_no, DOING_KIND_IDLE, 0);
            clear_npc_ext_effect(npc_no);
        }
        else
        {
            loop_npc_ext_frame(npc_no);
        }
        break;
    }
    UNLOCK_CHARACTER(npc_no);

    if(need_voice)
    {
        play_fight_voice(0, npc_no, file_index, DOING_KIND_BEATED, 0, x, y);
    }
    */    
}


//----
//死亡
//----
SLONG   client_do_npc_dead(SLONG npc_no)
{
    enum
    {   
        DOING_STEP_DEAD_START           =   0,  //死亡開始
        DOING_STEP_DEAD_RUNNING         =   1,  //正在死亡中
        DOING_STEP_DEAD_WAITING         =   2,  //等待屍體消失
	    DOING_STEP_DEAD_DISAPPEAR		=	4,	//屍體消失
        DOING_STEP_DEAD_PROCESS         =   5,  //死亡的處理
        DOING_STEP_DEAD_END				=   6,  //死亡END
    };
    SLONG   doing_step, dead_ticks, dead_alpha;
    SLONG   file_index, x, y, z;
    SLONG   beated_x, beated_y, dir;
    SLONG   effect, flag;
    SLONG   ret = ACTION_RETURN_PROC;
    //
    LOCK_CHARACTER(npc_no);
    doing_step = GetCharacterDoingStep(npc_no);
    UNLOCK_CHARACTER(npc_no);    
    //
    switch(doing_step)
    {
    case DOING_STEP_DEAD_START:
    case DOING_STEP_DEAD_RUNNING:
        //播放死亡動畫
        LOCK_CHARACTER(npc_no);
        GetCharacterPosition(npc_no, &x, &y, &z);
        GetCharacterBeatedXY(npc_no, &beated_x, &beated_y);
        dir = ApproachCharacterDir(beated_x - x, beated_y - y);
        SetCharacterDir(npc_no, dir);
        file_index = GetCharacterFileIndex(npc_no);
        UNLOCK_CHARACTER(npc_no);
        //
        switch (MinKind_NpcActionOneTime(npc_no, AC_FAINT))
        {
            case NPC_KEY_FRAME_HEAD://關鍵幀(第一幀)
                play_fight_voice(0, npc_no, file_index, DOING_KIND_DEAD, 0, x, y);
                break;
            case NPC_KEY_FRAME_HALF://中間幀
                break;
            case NPC_KEY_FRAME_TAIL://最後幀
                LOCK_CHARACTER(npc_no);
                flag = get_npc_flag(npc_no);
                flag |= NPC_DIED;
                set_npc_flag(npc_no, flag);
                SetCharacterDoingKindStep(npc_no, DOING_KIND_DEAD,DOING_STEP_DEAD_WAITING);
                UNLOCK_CHARACTER(npc_no);
                break;
            case NPC_KEY_FRAME_NONE://非關鍵幀
            case NPC_KEY_FRAME_BACK://收招幀
            default:
                break;
        }
        break;
    case DOING_STEP_DEAD_WAITING://死亡需要頓一段的時間
        LOCK_CHARACTER(npc_no);
		dead_ticks = GetCharacterDeadTicks(npc_no);//該數值的初始值是服務器給的
		dead_ticks--;
		if(dead_ticks <= 0)
		{
			SetCharacterDoingStep(npc_no, DOING_STEP_DEAD_DISAPPEAR);
            SetCharacterDeadAlpha(npc_no, 255);
		}
        else
        {
            SetCharacterDeadTicks(npc_no, (SHINT)dead_ticks);
        }
        UNLOCK_CHARACTER(npc_no);
        break;

    case DOING_STEP_DEAD_DISAPPEAR://屍體消失
        LOCK_CHARACTER(npc_no);
        dead_alpha = GetCharacterDeadAlpha(npc_no);
        dead_alpha -= 4;
        if(dead_alpha <= 0)
        {
            SetCharacterDoingStep(npc_no, DOING_STEP_DEAD_END);
        }
        else
        {
            effect = OBJECT_ALFA_IMAGE | ((dead_alpha << 8) & OBJECT_ALPHA_MASK);
            set_npc_effect(npc_no, effect);
            SetCharacterDeadAlpha(npc_no, dead_alpha);
        }
        UNLOCK_CHARACTER(npc_no);        
        break;

    case DOING_STEP_DEAD_PROCESS:
        //這段只有服務器需要處理
        break;
    case DOING_STEP_DEAD_END:
        LOCK_CHARACTER(npc_no);
        set_npc_effect(npc_no, OBJECT_NORMAL_IMAGE);
        set_npc_flag(npc_no, 0);
        UNLOCK_CHARACTER(npc_no);
        //
        ret = ACTION_RETURN_OK;
        break;
    }
    //
    return ret;
    // mark by lijun 2003-04-14
    /*
    enum
    {   
        DOING_STEP_DEAD_START       =   0,  //死亡開始
        DOING_STEP_DEAD_RUNNING         =   1,  //正在死亡中
        DOING_STEP_DEAD_WAITING         =   2,  //等待屍體消失
	    DOING_STEP_DEAD_DISAPPEAR		=	4,	//屍體消失
        DOING_STEP_DEAD_PROCESS         =   5,  //死亡的處理
        DOING_STEP_DEAD_END				=   6,  //死亡END
    };
    SLONG   doing_step, dead_ticks, dead_alpha;
    SLONG   new_action, new_id;
    SLONG   file_index, need_voice, x, y, z;
    SLONG   beated_x, beated_y, dir;
    SLONG   effect, flag;

    need_voice = false;

    LOCK_CHARACTER(npc_no);
    doing_step = GetCharacterDoingStep(npc_no);
    switch(doing_step)
    {
    case DOING_STEP_DEAD_START:
        new_action = AC_FAINT;
        file_index = GetCharacterFileIndex(npc_no);
        new_id = GetCharacterFileActionImageID(file_index, new_action);
        SetCharacterImageID(npc_no, new_id);

        GetCharacterPosition(npc_no, &x, &y, &z);
        GetCharacterBeatedXY(npc_no, &beated_x, &beated_y);
        dir = ApproachCharacterDir(beated_x - x, beated_y - y);
        SetCharacterDir(npc_no, dir);
        DirHeadCharacterFrame(npc_no);

        SetCharacterDoingStep(npc_no, DOING_STEP_DEAD_RUNNING);
        need_voice = true;
        break;

    case DOING_STEP_DEAD_RUNNING:
        if(NPC_KEY_FRAME_TAIL == DirFastTailCharacterFrame(npc_no))
        {
            SetCharacterDoingStep(npc_no, DOING_STEP_DEAD_WAITING);
            flag = get_npc_flag(npc_no);
            flag |= NPC_DIED;
            set_npc_flag(npc_no, flag);
        }
        break;

    case DOING_STEP_DEAD_WAITING:
		dead_ticks = GetCharacterDeadTicks(npc_no);
		dead_ticks--;
		if(dead_ticks <= 0)
		{
			SetCharacterDoingStep(npc_no, DOING_STEP_DEAD_DISAPPEAR);
            SetCharacterDeadAlpha(npc_no, 255);
		}
        else
        {
            SetCharacterDeadTicks(npc_no, (SHINT)dead_ticks);
        }
        break;

    case DOING_STEP_DEAD_DISAPPEAR:
        dead_alpha = GetCharacterDeadAlpha(npc_no);
        dead_alpha -= 4;
        if(dead_alpha <= 0)
        {
            SetCharacterDoingStep(npc_no, DOING_STEP_DEAD_END);
        }
        else
        {
            effect = OBJECT_ALFA_IMAGE | ((dead_alpha << 8) & OBJECT_ALPHA_MASK);
            set_npc_effect(npc_no, effect);
            SetCharacterDeadAlpha(npc_no, dead_alpha);
        }
        break;

    case DOING_STEP_DEAD_PROCESS:
        //skip this process for client.
        break;

    case DOING_STEP_DEAD_END:
        set_npc_effect(npc_no, OBJECT_NORMAL_IMAGE);
        set_npc_flag(npc_no, 0);
        break;
    }
    UNLOCK_CHARACTER(npc_no);

    if(need_voice)
    {
        play_fight_voice(0, npc_no, file_index, DOING_KIND_DEAD, 0, x, y);
    }
    */    
}

//----
//被擊倒
//----
SLONG   client_do_npc_down_and_out(SLONG npc_no)
{
    enum
    {   
        DOING_STEP_DOWN_AND_OUT_START       =   0,  //開始被擊倒
        DOING_STEP_PANT                     =   1,  //喘息一段時間
    };
    SLONG   doing_step;
    SLONG   pant_ticks, x, y, z;
    SLONG   beated_x, beated_y;
    SLONG   dir;
    SLONG   file_index;
    SLONG   ret = ACTION_RETURN_PROC;
    //
    LOCK_CHARACTER(npc_no);
    doing_step = GetCharacterDoingStep(npc_no);
    UNLOCK_CHARACTER(npc_no);    
    switch(doing_step)
    {
    case DOING_STEP_DOWN_AND_OUT_START://播放被擊倒的動畫
        //根據攻擊者npc倒向需要的方向
        LOCK_CHARACTER(npc_no);
        GetCharacterPosition(npc_no, &x, &y, &z);
        GetCharacterBeatedXY(npc_no, &beated_x, &beated_y);
        dir = ApproachCharacterDir(beated_x - x, beated_y - y);
        SetCharacterDir(npc_no, dir);
        LOCK_CHARACTER(npc_no);
        switch (MinKind_NpcActionOneTime(npc_no, AC_FAINT))
        {
        case NPC_KEY_FRAME_NONE://非關鍵幀
            break;
        case NPC_KEY_FRAME_HEAD://關鍵幀(第一幀)
            LOCK_CHARACTER(npc_no);
            file_index = GetCharacterFileIndex(npc_no);
            GetCharacterPosition(npc_no, &x, &y, &z);
            play_fight_voice(0, npc_no, file_index, DOING_KIND_BEATED, 0, x, y);
            LOCK_CHARACTER(npc_no);            
            break;
        case NPC_KEY_FRAME_HALF://中間幀
            break;        
        case NPC_KEY_FRAME_TAIL://最後幀
            LOCK_CHARACTER(npc_no);
            SetCharacterDoingKindStep(npc_no, DOING_KIND_DOWN_AND_OUT, DOING_STEP_PANT);
            SetCharacterPantTicks(npc_no, 5);  //0.25秒喘息  如果需要增加到npc的數據結構中..該數值需要服務器給
            LOCK_CHARACTER(npc_no);
            //
            break;
        }
        //
        break;
    case DOING_STEP_PANT://被打倒停在地板上一段時間
        LOCK_CHARACTER(npc_no);
        pant_ticks = GetCharacterPantTicks(npc_no);
        if(--pant_ticks <= 0)
            SetCharacterDoingKindStep(npc_no, DOING_KIND_IDLE, 0);
        else
            SetCharacterPantTicks(npc_no, pant_ticks);
        LOCK_CHARACTER(npc_no);
        //
        ret = ACTION_RETURN_OK ;
        break;
    }
    //
    return ret;
/*
    enum
    {   
        DOING_STEP_DOWN_AND_OUT_START   =   0,  //開始被擊倒
        DOING_STEP_DOWN_AND_OUT_RUNNING     =   1,  //被擊倒中
        DOING_STEP_PANT                     =   2,  //喘息一段時間
    };
    SLONG   file_index, doing_step, new_action, new_id;
    SLONG   pant_ticks, x, y, z;
    SLONG   beated_x, beated_y;
    SLONG   need_voice, dir;


    need_voice = false;

    LOCK_CHARACTER(npc_no);
    doing_step = GetCharacterDoingStep(npc_no);
    switch(doing_step)
    {
    case DOING_STEP_DOWN_AND_OUT_START:
        new_action = AC_FAINT;
        file_index = GetCharacterFileIndex(npc_no);
        new_id = GetCharacterFileActionImageID(file_index, new_action);
        //
        GetCharacterPosition(npc_no, &x, &y, &z);
        GetCharacterBeatedXY(npc_no, &beated_x, &beated_y);
        dir = ApproachCharacterDir(beated_x - x, beated_y - y);
        //
        SetCharacterImageID(npc_no,new_id);
        SetCharacterDir(npc_no, dir);
        DirHeadCharacterFrame(npc_no);
        //
        SetCharacterDoingStep(npc_no, DOING_STEP_DOWN_AND_OUT_RUNNING);
        //
        need_voice = true;
        break;

    case DOING_STEP_DOWN_AND_OUT_RUNNING:
        if(NPC_KEY_FRAME_TAIL == DirFastTailCharacterFrame(npc_no))
        {
            SetCharacterDoingStep(npc_no, DOING_STEP_PANT);
            SetCharacterPantTicks(npc_no, 5);  //0.25秒喘息
        }
        break;

    case DOING_STEP_PANT:
        pant_ticks = GetCharacterPantTicks(npc_no);
        if(--pant_ticks <= 0)
            SetCharacterDoingKindStep(npc_no, DOING_KIND_IDLE, 0);
        else
            SetCharacterPantTicks(npc_no, pant_ticks);
        break;
    }
    UNLOCK_CHARACTER(npc_no);

    if(need_voice)
    {
        play_fight_voice(0, npc_no, file_index, DOING_KIND_BEATED, 0, x, y);
    }
    */    
}

//----
//格檔
//----
SLONG   client_do_npc_defence(SLONG npc_no)
{
    SLONG   beated_by, dest_x, dest_y, dest_z;
    SLONG   x, y, z, dir;
    SLONG   ret = ACTION_RETURN_PROC;
    //播放一格檔動畫
    LOCK_CHARACTER(npc_no);
    GetCharacterPosition(npc_no, &x, &y, &z);
    beated_by = GetCharacterBeatedBy(npc_no);
    GetCharacterPosition(beated_by, &dest_x, &dest_y, &dest_z);
    dir = ApproachCharacterDir(dest_x - x, dest_y - y);    
    SetCharacterDir(npc_no, dir);
    UNLOCK_CHARACTER(npc_no);    
    if (NPC_KEY_FRAME_TAIL == MinKind_NpcActionOneTime(npc_no, AC_WARD))
    {
        LOCK_CHARACTER(npc_no);
        SetCharacterDoingKindStep(npc_no, DOING_KIND_IDLE, 0);
        UNLOCK_CHARACTER(npc_no);
        //
        ret = ACTION_RETURN_OK;
    }    
    return ret;
    //
    // mark by lijun 2003-04-15
    /*
    enum
    {   
        DOING_STEP_START_DEFENCE        =   0,      //開始格檔
        DOING_STEP_DEFENCE_RUNNING      =   1,      //格檔中
    };
    SLONG   doing_step, file_index;
    SLONG   new_action, new_id, beated_by, dest_x, dest_y, dest_z;
    SLONG   x, y, z, dir;
    //
    LOCK_CHARACTER(npc_no);
    doing_step = GetCharacterDoingStep(npc_no);
    switch(doing_step)
    {
    case DOING_STEP_START_DEFENCE:
        new_action = AC_WARD;
        file_index = GetCharacterFileIndex(npc_no);
        new_id = GetCharacterFileActionImageID(file_index, new_action);
        //
        GetCharacterPosition(npc_no, &x, &y, &z);
        beated_by = GetCharacterBeatedBy(npc_no);
        GetCharacterPosition(beated_by, &dest_x, &dest_y, &dest_z);
        dir = ApproachCharacterDir(dest_x - x, dest_y - y);
        //
        SetCharacterImageID(npc_no, new_id);
        SetCharacterDir(npc_no, dir);
        DirHeadCharacterFrame(npc_no);
        //
        SetCharacterDoingStep(npc_no, DOING_STEP_DEFENCE_RUNNING);
        break;

    case DOING_STEP_DEFENCE_RUNNING:
        if(NPC_KEY_FRAME_TAIL == DirFastTailCharacterFrame(npc_no))
        {
            SetCharacterDoingKindStep(npc_no, DOING_KIND_IDLE, 0);
        }
        break;
    }
    UNLOCK_CHARACTER(npc_no);
    */    
}

//----
//被格檔

SLONG   client_do_npc_defenced(SLONG npc_no)
{
    SLONG   ret = ACTION_RETURN_PROC;
    // 播放被格檔動畫
    if (NPC_KEY_FRAME_TAIL == MinKind_NpcActionOneTime(npc_no, AC_BEATED))
    {
        LOCK_CHARACTER(npc_no);
        SetCharacterDoingKindStep(npc_no, DOING_KIND_IDLE, 0);
        UNLOCK_CHARACTER(npc_no);
        //
        ret = ACTION_RETURN_OK;
    }        
    return ret;
    /*
    enum
    {   
        DOING_STEP_START_DEFENCED   =   0,
        DOING_STEP_DEFENCED_RUNNING     =   1,
    };
    SLONG   doing_step, file_index;
    SLONG   new_action, new_id;

    LOCK_CHARACTER(npc_no);
    doing_step = GetCharacterDoingStep(npc_no);
    switch(doing_step)
    {
    case DOING_STEP_START_DEFENCED:
        new_action = AC_BEATED;
        file_index = GetCharacterFileIndex(npc_no);
        new_id = GetCharacterFileActionImageID(file_index, new_action);
        SetCharacterImageID(npc_no, new_id);
        DirHeadCharacterFrame(npc_no);
        SetCharacterDoingStep(npc_no, DOING_STEP_DEFENCED_RUNNING);
        break;

    case DOING_STEP_DEFENCED_RUNNING:
        if(NPC_KEY_FRAME_TAIL == DirFastTailCharacterFrame(npc_no))
        {
            SetCharacterDoingKindStep(npc_no, DOING_KIND_IDLE, 0);
        }
        break;
    }
    UNLOCK_CHARACTER(npc_no);
    */    
}

/******************************************************************************************************************/
/* EMOTION DOING FUNCTIONS                                                                                        */
/******************************************************************************************************************/
/*
//----
//表情動作: 歡呼
//----
SLONG   client_do_npc_cheer(SLONG npc_no)
{
    SLONG ret = ACTION_RETURN_PROC;
    if (NPC_KEY_FRAME_TAIL == MinKind_NpcActionOneTime(npc_no, AC_CHEER))
    {
        LOCK_CHARACTER(npc_no);
        SetCharacterDoingKindStep(npc_no, DOING_KIND_IDLE, 0);
        UNLOCK_CHARACTER(npc_no);
        //
        ret = ACTION_RETURN_OK;
    }            
    return ret;
    // mark by lijun 2003-04-10
    /----------------------------------------------------------------------
    enum
    {   DOING_STEP_START_CHEER      =   0,  //歡呼開始
    DOING_STEP_CHEER_RUNNING        =   1,  //歡呼中
    };
    SLONG   doing_step, file_index;
    SLONG   new_action, new_id;

    LOCK_CHARACTER(npc_no);
    doing_step = GetCharacterDoingStep(npc_no);
    switch(doing_step)
    {
    case DOING_STEP_START_CHEER:
        new_action = ;
        file_index = GetCharacterFileIndex(npc_no);
        new_id = GetCharacterFileActionImageID(file_index, new_action);
        SetCharacterImageID(npc_no, new_id);
        DirHeadCharacterFrame(npc_no);
        SetCharacterDoingStep(npc_no, DOING_STEP_CHEER_RUNNING);
        break;

    case DOING_STEP_CHEER_RUNNING:
        if( NPC_KEY_FRAME_TAIL == DirTailCharacterFrame(npc_no))
        {
            SetCharacterDoingKindStep(npc_no, DOING_KIND_IDLE, 0);
        }
        break;
    }
    UNLOCK_CHARACTER(npc_no);
    /----------------------------------------------------------------------
}
*/
//----
//表情動作: 生氣
//----
SLONG   client_do_npc_angry(SLONG npc_no)
{
    SLONG   ret = ACTION_RETURN_PROC;
    if (NPC_KEY_FRAME_TAIL == MinKind_NpcActionOneTime(npc_no, AC_ANGRY))
    {
        LOCK_CHARACTER(npc_no);
        SetCharacterDoingKindStep(npc_no, DOING_KIND_IDLE, 0);
        UNLOCK_CHARACTER(npc_no);
        //
        ret = ACTION_RETURN_OK;
    }                
    return ret;
    // mark by lijun 2003-04-10
    /*
    enum
    {   DOING_STEP_START_ANGRY      =   0,  //生氣開始
    DOING_STEP_ANGRY_RUNNING        =   1,  //生氣中
    };
    SLONG   doing_step, file_index;
    SLONG   new_action, new_id;

    LOCK_CHARACTER(npc_no);
    doing_step = GetCharacterDoingStep(npc_no);
    switch(doing_step)
    {
    case DOING_STEP_START_ANGRY:
        new_action = AC_ANGRY;
        file_index = GetCharacterFileIndex(npc_no);
        new_id = GetCharacterFileActionImageID(file_index, new_action);
        SetCharacterImageID(npc_no, new_id);
        DirHeadCharacterFrame(npc_no);
        SetCharacterDoingStep(npc_no, DOING_STEP_ANGRY_RUNNING);
        break;

    case DOING_STEP_ANGRY_RUNNING:
        if( NPC_KEY_FRAME_TAIL == DirTailCharacterFrame(npc_no))
        {
            SetCharacterDoingKindStep(npc_no, DOING_KIND_IDLE, 0);
        }
        break;
    }
    UNLOCK_CHARACTER(npc_no);
    */    
}


//表情動作: 招手
SLONG   client_do_npc_beckon(SLONG npc_no)
{
    SLONG   ret = ACTION_RETURN_PROC;
    if (NPC_KEY_FRAME_TAIL == MinKind_NpcActionOneTime(npc_no, AC_BECKON))
    {
        LOCK_CHARACTER(npc_no);
        SetCharacterDoingKindStep(npc_no, DOING_KIND_IDLE, 0);
        UNLOCK_CHARACTER(npc_no);
        //
        ret = ACTION_RETURN_OK;
    }                
    return ret;
    // mark by lijun 2003-04-10
    /*
    enum
    {   DOING_STEP_START_BECKON     =   0,  //招手開始
    DOING_STEP_BECKON_RUNNING       =   1,  //招手中
    };
    SLONG   doing_step, file_index;
    SLONG   new_action, new_id;

    LOCK_CHARACTER(npc_no);
    doing_step = GetCharacterDoingStep(npc_no);
    switch(doing_step)
    {
    case DOING_STEP_START_BECKON:
        new_action = AC_BECKON;
        file_index = GetCharacterFileIndex(npc_no);
        new_id = GetCharacterFileActionImageID(file_index, new_action);
        SetCharacterImageID(npc_no, new_id);
        DirHeadCharacterFrame(npc_no);
        SetCharacterDoingStep(npc_no, DOING_STEP_BECKON_RUNNING);
        break;

    case DOING_STEP_BECKON_RUNNING:
        if( NPC_KEY_FRAME_TAIL == DirTailCharacterFrame(npc_no))
        {
            SetCharacterDoingKindStep(npc_no, DOING_KIND_IDLE, 0);
        }
        break;
    }
    UNLOCK_CHARACTER(npc_no);
    */
}
/*
//----
//表情動作: 求愛
//----
SLONG   client_do_npc_court(SLONG npc_no)
{
    SLONG   ret = ACTION_RETURN_PROC;
    if (NPC_KEY_FRAME_TAIL == MinKind_NpcActionOneTime(npc_no, AC_COURT))
    {
        LOCK_CHARACTER(npc_no);
        SetCharacterDoingKindStep(npc_no, DOING_KIND_IDLE, 0);
        UNLOCK_CHARACTER(npc_no);
        //
        ret = ACTION_RETURN_PROC;
    }                
    return ret;
    // mark by lijun 2003-04-10
    /----------------------------------------------------------------------
    enum
    {   DOING_STEP_START_COURT      =   0,  //求愛開始
    DOING_STEP_COURT_RUNNING        =   1,  //求愛中
    };
    SLONG   doing_step, file_index;
    SLONG   new_action, new_id;

    LOCK_CHARACTER(npc_no);
    doing_step = GetCharacterDoingStep(npc_no);
    switch(doing_step)
    {
    case DOING_STEP_START_COURT:
        new_action = AC_COURT;
        file_index = GetCharacterFileIndex(npc_no);
        new_id = GetCharacterFileActionImageID(file_index, new_action);
        SetCharacterImageID(npc_no, new_id);
        DirHeadCharacterFrame(npc_no);
        SetCharacterDoingStep(npc_no, DOING_STEP_COURT_RUNNING);
        break;

    case DOING_STEP_COURT_RUNNING:
        if( NPC_KEY_FRAME_TAIL == DirTailCharacterFrame(npc_no))
        {
            SetCharacterDoingKindStep(npc_no, DOING_KIND_IDLE, 0);
        }
        break;
    }
    UNLOCK_CHARACTER(npc_no);
    /----------------------------------------------------------------------
}
*/
//----
//表情動作: 暈倒
//----
SLONG   client_do_npc_faint(SLONG npc_no)
{
    SLONG ret = ACTION_RETURN_PROC;
    if (NPC_KEY_FRAME_TAIL == MinKind_NpcActionOneTime(npc_no, AC_FAINT))
    {
        LOCK_CHARACTER(npc_no);
        SetCharacterDoingKindStep(npc_no, DOING_KIND_IDLE, 0);
        UNLOCK_CHARACTER(npc_no);
        //
        ret = ACTION_RETURN_OK;
    }
    return ret;
    /*
    enum
    {   DOING_STEP_START_FAINT      =   0,  //暈倒開始
    DOING_STEP_FAINT_RUNNING        =   1,  //暈倒中
    };
    SLONG   doing_step, file_index;
    SLONG   new_action, new_id;

    LOCK_CHARACTER(npc_no);
    doing_step = GetCharacterDoingStep(npc_no);
    switch(doing_step)
    {
    case DOING_STEP_START_FAINT:
        new_action = AC_FAINT;
        file_index = GetCharacterFileIndex(npc_no);
        new_id = GetCharacterFileActionImageID(file_index, new_action);
        SetCharacterImageID(npc_no, new_id);
        DirHeadCharacterFrame(npc_no);
        SetCharacterDoingStep(npc_no, DOING_STEP_FAINT_RUNNING);
        break;

    case DOING_STEP_FAINT_RUNNING:
        if( NPC_KEY_FRAME_TAIL == DirTailCharacterFrame(npc_no))
        {
            SetCharacterDoingKindStep(npc_no, DOING_KIND_IDLE, 0);
        }
        break;
    }
    UNLOCK_CHARACTER(npc_no);
    */
}

//----
//表情動作: 說不
//----
SLONG   client_do_npc_say_no(SLONG npc_no)
{
    SLONG   ret = ACTION_RETURN_PROC;  
    if (NPC_KEY_FRAME_TAIL == MinKind_NpcActionOneTime(npc_no, AC_SAY_NO))
    {
        LOCK_CHARACTER(npc_no);
        SetCharacterDoingKindStep(npc_no, DOING_KIND_IDLE, 0);
        UNLOCK_CHARACTER(npc_no);
        //
        ret = ACTION_RETURN_OK;
    }                        
    return ret;
    // mark by lijun 2003-04-10
    /*
    enum
    {   DOING_STEP_START_SAY_NO     =   0,  //說不開始
    DOING_STEP_SAYING_NO            =   1,  //說不中
    };
    SLONG   doing_step, file_index;
    SLONG   new_action, new_id;

    LOCK_CHARACTER(npc_no);
    doing_step = GetCharacterDoingStep(npc_no);
    switch(doing_step)
    {
    case DOING_STEP_START_SAY_NO:
        new_action = AC_SAY_NO;
        file_index = GetCharacterFileIndex(npc_no);
        new_id = GetCharacterFileActionImageID(file_index, new_action);
        SetCharacterImageID(npc_no, new_id);
        DirHeadCharacterFrame(npc_no);
        SetCharacterDoingStep(npc_no, DOING_STEP_SAYING_NO);
        break;

    case DOING_STEP_SAYING_NO:
        if( NPC_KEY_FRAME_TAIL == DirTailCharacterFrame(npc_no))
        {
            SetCharacterDoingKindStep(npc_no, DOING_KIND_IDLE, 0);
        }
        break;
    }
    UNLOCK_CHARACTER(npc_no);
    */
}

//----
//表情動作: 鞠躬
//----
SLONG   client_do_npc_bow(SLONG npc_no)
{
    SLONG   ret = ACTION_RETURN_PROC;
    if (NPC_KEY_FRAME_TAIL == MinKind_NpcActionOneTime(npc_no, AC_BOW))
    {
        LOCK_CHARACTER(npc_no);
        SetCharacterDoingKindStep(npc_no, DOING_KIND_IDLE, 0);
        UNLOCK_CHARACTER(npc_no);
        //
        ret = ACTION_RETURN_OK;
    }                          
    return ret;  
    // mark by lijun 2003-04-10
    /*    
    enum
    {   DOING_STEP_START_BOW        =   0,  //鞠躬開始
    DOING_STEP_BOW_RUNNING          =   1,  //鞠躬中
    };
    SLONG   doing_step, file_index;
    SLONG   new_action, new_id;

    LOCK_CHARACTER(npc_no);
    doing_step = GetCharacterDoingStep(npc_no);
    switch(doing_step)
    {
    case DOING_STEP_START_BOW:
        new_action = AC_BOW;
        file_index = GetCharacterFileIndex(npc_no);
        new_id = GetCharacterFileActionImageID(file_index, new_action);
        SetCharacterImageID(npc_no, new_id);
        DirHeadCharacterFrame(npc_no);
        SetCharacterDoingStep(npc_no, DOING_STEP_BOW_RUNNING);
        break;

    case DOING_STEP_BOW_RUNNING:
        if( NPC_KEY_FRAME_TAIL == DirTailCharacterFrame(npc_no))
        {
            SetCharacterDoingKindStep(npc_no, DOING_KIND_IDLE, 0);
        }
        break;
    }
    UNLOCK_CHARACTER(npc_no);
    */
}

//----
//表情動作: 勝利
//----
SLONG   client_do_npc_win(SLONG npc_no)
{
    SLONG   ret = ACTION_RETURN_PROC;
    if (NPC_KEY_FRAME_TAIL == MinKind_NpcActionOneTime(npc_no, AC_WIN))
    {
        LOCK_CHARACTER(npc_no);
        SetCharacterDoingKindStep(npc_no, DOING_KIND_IDLE, 0);
        UNLOCK_CHARACTER(npc_no);
        //
        ret = ACTION_RETURN_OK;
    }                          
    return ret;      
    // mark by lijun 2003-04-10
    /*
    enum
    {   DOING_STEP_START_WIN        =   0,  //勝利開始
    DOING_STEP_WIN_RUNNING          =   1,  //勝利中
    };
    SLONG   doing_step, file_index;
    SLONG   new_action, new_id;

    LOCK_CHARACTER(npc_no);
    doing_step = GetCharacterDoingStep(npc_no);
    switch(doing_step)
    {
    case DOING_STEP_START_WIN:
        new_action = AC_WIN;
        file_index = GetCharacterFileIndex(npc_no);
        new_id = GetCharacterFileActionImageID(file_index, new_action);
        SetCharacterImageID(npc_no, new_id);
        DirHeadCharacterFrame(npc_no);
        SetCharacterDoingStep(npc_no, DOING_STEP_WIN_RUNNING);
        break;

    case DOING_STEP_WIN_RUNNING:
        if( NPC_KEY_FRAME_TAIL == DirTailCharacterFrame(npc_no))
        {
            SetCharacterDoingKindStep(npc_no, DOING_KIND_IDLE, 0);
        }
        break;
    }
    UNLOCK_CHARACTER(npc_no);
    */
}

//----
//表情動作: 攻擊
//----
SLONG   client_do_npc_swash(SLONG npc_no)
{
    SLONG   ret = ACTION_RETURN_PROC;
    if (NPC_KEY_FRAME_TAIL == MinKind_NpcActionOneTime(npc_no, AC_ATTACK_0))
    {
        LOCK_CHARACTER(npc_no);
        SetCharacterDoingKindStep(npc_no, DOING_KIND_IDLE, 0);
        UNLOCK_CHARACTER(npc_no);
        //
        ret = ACTION_RETURN_OK;
    }                          
    return ret;          
    // mark by lijun 2003-04-10
    /*
    enum
    {   DOING_STEP_START_SWASH      =   0,  //攻擊開始
    DOING_STEP_SWASH_RUNNING        =   1,  //攻擊中
    };
    SLONG   doing_step, file_index;
    SLONG   new_action, new_id;

    LOCK_CHARACTER(npc_no);
    doing_step = GetCharacterDoingStep(npc_no);
    switch(doing_step)
    {
    case DOING_STEP_START_SWASH:
        new_action = AC_ATTACK_0;
        file_index = GetCharacterFileIndex(npc_no);
        new_id = GetCharacterFileActionImageID(file_index, new_action);
        SetCharacterImageID(npc_no, new_id);
        DirHeadCharacterFrame(npc_no);
        SetCharacterDoingStep(npc_no, DOING_STEP_SWASH_RUNNING);
        break;

    case DOING_STEP_SWASH_RUNNING:
        if( NPC_KEY_FRAME_TAIL == DirTailCharacterFrame(npc_no))
        {
            SetCharacterDoingKindStep(npc_no, DOING_KIND_IDLE, 0);
        }
        break;
    }
    UNLOCK_CHARACTER(npc_no);
    */
}

//----
//表情動作: 蓄力
//----
SLONG   client_do_npc_xxpower(SLONG npc_no)
{
    SLONG   ret = ACTION_RETURN_PROC;
    if (NPC_KEY_FRAME_TAIL == MinKind_NpcActionOneTime(npc_no, AC_SPOWER))
    {
        LOCK_CHARACTER(npc_no);
        SetCharacterDoingKindStep(npc_no, DOING_KIND_IDLE, 0);
        UNLOCK_CHARACTER(npc_no);
        //
        ret = ACTION_RETURN_OK;
    }                          
    return ret;              
    // mark by lijun 2003-04-10
    /*
    enum
    {   DOING_STEP_START_XXPOWER    =   0,  //蓄力開始
    DOING_STEP_XXPOWER_RUNNING      =   1,  //蓄力中
    };
    SLONG   doing_step, file_index;
    SLONG   new_action, new_id;

    LOCK_CHARACTER(npc_no);
    doing_step = GetCharacterDoingStep(npc_no);
    switch(doing_step)
    {
    case DOING_STEP_START_XXPOWER:
        new_action = AC_SPOWER;
        file_index = GetCharacterFileIndex(npc_no);
        new_id = GetCharacterFileActionImageID(file_index, new_action);
        SetCharacterImageID(npc_no, new_id);
        DirHeadCharacterFrame(npc_no);
        SetCharacterDoingStep(npc_no, DOING_STEP_XXPOWER_RUNNING);
        break;

    case DOING_STEP_XXPOWER_RUNNING:
        if( NPC_KEY_FRAME_TAIL == DirTailCharacterFrame(npc_no))
        {
            SetCharacterDoingKindStep(npc_no, DOING_KIND_IDLE, 0);
        }
        break;
    }
    UNLOCK_CHARACTER(npc_no);
    */
}


//----
//表情動作: 被擊
//----
SLONG   client_do_npc_xxbeated(SLONG npc_no)
{
    SLONG   ret = ACTION_RETURN_PROC;
    //
    if (NPC_KEY_FRAME_TAIL == MinKind_NpcActionOneTime(npc_no, AC_BEATED))
    {
        LOCK_CHARACTER(npc_no);
        SetCharacterDoingKindStep(npc_no, DOING_KIND_IDLE, 0);
        UNLOCK_CHARACTER(npc_no);
        //
        ret = ACTION_RETURN_OK;
    }                         
    return ret;                   
    //mark by lijun 2003-04-10
    /*
    enum
    {   DOING_STEP_START_XXBEATED   =   0,  //被擊開始
    DOING_STEP_XXBEATED_RUNNING     =   1,  //被擊中
    };
    SLONG   doing_step, file_index;
    SLONG   new_action, new_id;

    LOCK_CHARACTER(npc_no);
    doing_step = GetCharacterDoingStep(npc_no);
    switch(doing_step)
    {
    case DOING_STEP_START_XXBEATED:
        new_action = AC_BEATED;
        file_index = GetCharacterFileIndex(npc_no);
        new_id = GetCharacterFileActionImageID(file_index, new_action);
        SetCharacterImageID(npc_no, new_id);
        DirHeadCharacterFrame(npc_no);
        SetCharacterDoingStep(npc_no, DOING_STEP_XXBEATED_RUNNING);
        break;

    case DOING_STEP_XXBEATED_RUNNING:
        if( NPC_KEY_FRAME_TAIL == DirTailCharacterFrame(npc_no))
        {
            SetCharacterDoingKindStep(npc_no, DOING_KIND_IDLE, 0);
        }
        break;
    }
    UNLOCK_CHARACTER(npc_no);
    */
}


/************************************************************************************************************/
/* SEA NPC FUNCTIONS                                                                                        */
/************************************************************************************************************/
SLONG   client_do_sea_npc_acc_move_to(SLONG npc_no)
{
	// TODO [12/17/2002]
	return ACTION_RETURN_PROC;
}


/************************************************************************************************************/
/* NPC FIGHT FUNCTIONS                                                                                      */
/************************************************************************************************************/
/*
SLONG   client_do_npc_fight_idle(SLONG npc_no)
{
    //播放待機動畫
    //-----和npc的ai相關控制 怪物的ai --服務器再npc  fight_idle 的時候會去作一些事情
    client_do_npc_idle(npc_no);
    return ACTION_RETURN_PROC;
    //mark by lijun 2003-04-10
    /---------------------------------------------------------------------------------
    SLONG   file_index, is_fight;
    SLONG   new_action, new_id, id;
    SLONG   key_frame_type;

    LOCK_CHARACTER(npc_no);
    file_index = GetCharacterFileIndex(npc_no);
	id = GetCharacterImageID(npc_no);
	is_fight = IsCharacterOnFightState(npc_no);
    UNLOCK_CHARACTER(npc_no);

	new_action = GetIdleAction(is_fight);
	new_id = GetCharacterFileActionImageID(file_index, new_action);
	if(id != new_id)
    {
        LOCK_CHARACTER(npc_no);
		SetCharacterImageID(npc_no, new_id);
        DirLoopCharacterFrame(npc_no);
        UNLOCK_CHARACTER(npc_no);
    }
    else
    {
        LOCK_CHARACTER(npc_no);
        key_frame_type = DirKeyLoopCharacterFrame(npc_no);
        UNLOCK_CHARACTER(npc_no);
    }
    /---------------------------------------------------------------------------------
}
*/
/*
SLONG   client_do_npc_fight_gad(SLONG npc_no)
{
    enum
    {
        DOING_STEP_IDLE     =   0,
        DOING_STEP_MOVE_TO  =   1,
    };
    SLONG   doing_step;
    SLONG   dest_x, dest_y, dest_z;
    SLONG   is_fight;
    SLONG   new_action;
    SLONG   ret = ACTION_RETURN_PROC;
    //
    LOCK_CHARACTER(npc_no);
    doing_step = GetCharacterDoingStep(npc_no);
	GetCharacterDestPosition(npc_no, &dest_x, &dest_y, &dest_z);
    UNLOCK_CHARACTER(npc_no);
    //
    switch(doing_step)
    {
    case DOING_STEP_IDLE:
        //播放待機動畫
        LOCK_CHARACTER(npc_no);
        is_fight = IsCharacterOnFightState(npc_no);
        new_action = GetIdleAction(is_fight);
        MinKind_NpcActionLoop(npc_no, new_action);
        UNLOCK_CHARACTER(npc_no);
        //
        break;
    case DOING_STEP_MOVE_TO:
        switch (MinKind_NpcMoveFindPath(npc_no,dest_x, dest_y))
        {
        case NPC_MOVE_MOVEING:      //npc移動在移動過程中
            break;    
        case NPC_MOVE_ARRIVE:       //npc移動到達了目標
            LOCK_CHARACTER(npc_no);
            SetCharacterDoingKindStep(npc_no, DOING_KIND_FIGHT_GAD, DOING_STEP_IDLE);
            UNLOCK_CHARACTER(npc_no);
            break;    
        case NPC_MOVE_CANT_ARRIVE:  //npc移動不能到達
            LOCK_CHARACTER(npc_no);
            SetCharacterDoingKindStep(npc_no, DOING_KIND_FIGHT_GAD, DOING_STEP_IDLE);
            UNLOCK_CHARACTER(npc_no);
            break;
        }
        break;
    default:
        break;
    }
    return ret;
    // mark by lijun 2003-04-10
    /---------------------------------------------------------------------
    enum    
    {   DOING_STEP_IDLE   =   0,
    DOING_STEP_MOVE_TO    =   1,
    };
    SLONG   doing_step;
    SLONG   x, y, z;
    SLONG   dest_x, dest_y, dest_z;
    SLONG   move_speed;
    SLONG   file_index, id;
    SLONG   new_action, new_id;
    SLONG   dir, is_fight;
    SLONG   ret;

    LOCK_CHARACTER(npc_no);
    doing_step = GetCharacterDoingStep(npc_no);
	GetCharacterPosition(npc_no, &x, &y, &z);
	GetCharacterDestPosition(npc_no, &dest_x, &dest_y, &dest_z);
    move_speed = GetCharacterMoveSpeed(npc_no);
    file_index = GetCharacterFileIndex(npc_no);
    id = GetCharacterImageID(npc_no);
    dir = GetCharacterDir(npc_no);
    is_fight = IsCharacterOnFightState(npc_no);
    UNLOCK_CHARACTER(npc_no);

    switch(doing_step)
    {
    case DOING_STEP_IDLE:
        {
			new_action = GetIdleAction(is_fight);
			new_id = GetCharacterFileActionImageID(file_index, new_action);
			if(new_id != id)
			{
				LOCK_CHARACTER(npc_no);
				SetCharacterImageID(npc_no, new_id);
				DirHeadCharacterFrame(npc_no);
				UNLOCK_CHARACTER(npc_no);
			}
			else
			{
				LOCK_CHARACTER(npc_no);
				DirFastLoopCharacterFrame(npc_no);
				UNLOCK_CHARACTER(npc_no);
			}
        }
        break;
    case DOING_STEP_MOVE_TO:
        {
			LOCK_MAPMASK(0);
            ret = FindCharacterStep(x, y, &dest_x, &dest_y, move_speed);
			UNLOCK_MAPMASK(0);
            switch(ret)
            {
            case STEP_ON_THE_WAY:
				if(dest_x - x != 0 || dest_y - y != 0)
					dir = ApproachCharacterDir(dest_x - x, dest_y - y);
				new_action = GetRunAction(is_fight);
				new_id = GetCharacterFileActionImageID(file_index, new_action);
				if(id != new_id)
				{
					LOCK_CHARACTER(npc_no);
					SetCharacterPosition(npc_no, dest_x, dest_y, dest_z);
					SetCharacterDir(npc_no, dir);
					SetCharacterImageID(npc_no, new_id);
					DirHeadCharacterFrame(npc_no);
					UNLOCK_CHARACTER(npc_no);
				}
				else
				{
					LOCK_CHARACTER(npc_no);
					SetCharacterPosition(npc_no, dest_x, dest_y, dest_z);
					SetCharacterDir(npc_no, dir);
					DirFastLoopCharacterFrame(npc_no);
					UNLOCK_CHARACTER(npc_no);
				}
				break;
            case STEP_ARRIVE:
            case STEP_OBSTRUCT:
            case STEP_OUTSTRETCH:
            default:
				LOCK_CHARACTER(npc_no);
				SetCharacterDoingStep(npc_no, DOING_STEP_IDLE);
				UNLOCK_CHARACTER(npc_no);
				break;
            }
        }
        break;
    default:
        break;
    }
    /---------------------------------------------------------------------
}
*/
/*
//----
//  巡邏
//----
SLONG   client_do_npc_fight_patrol(SLONG npc_no)
{
    enum
    {   
        DOING_STEP_MOVE_TO          =   0,
        DOING_STEP_IDLE_WHEN_TO     =   1,
        DOING_STEP_MOVE_BACK        =   2,
        DOING_STEP_IDLE_WHEN_BACK   =   3,
    };
    SLONG   doing_step;
    SLONG   x, y, z, dest_x, dest_y, dest_z;
    SLONG   orig_x, orig_y, orig_z;
    SLONG   is_fight;
    SLONG   new_action;
    SLONG   ret = ACTION_RETURN_PROC;

    LOCK_CHARACTER(npc_no);
    doing_step = GetCharacterDoingStep(npc_no);
    GetCharacterPosition(npc_no, &x, &y, &z);
    GetCharacterDestPosition(npc_no, &dest_x, &dest_y, &dest_z);
    GetCharacterOrigPosition(npc_no, &orig_x, &orig_y, &orig_z);
    is_fight = IsCharacterOnFightState(npc_no);
    UNLOCK_CHARACTER(npc_no);

    switch(doing_step)
    {
    case DOING_STEP_MOVE_TO:
        switch (MinKind_NpcMoveFindPath(npc_no,dest_x, dest_y))
        {
        case NPC_MOVE_MOVEING:      //npc移動在移動過程中
            break;    
        case NPC_MOVE_ARRIVE:       //npc移動到達了目標
            LOCK_CHARACTER(npc_no);
            SetCharacterDoingKindStep(npc_no, DOING_KIND_FIGHT_PATROL, DOING_STEP_IDLE_WHEN_TO);
            UNLOCK_CHARACTER(npc_no);
            break;    
        case NPC_MOVE_CANT_ARRIVE:  //npc移動不能到達
            LOCK_CHARACTER(npc_no);
            SetCharacterDoingKindStep(npc_no, DOING_KIND_FIGHT_PATROL, DOING_STEP_IDLE_WHEN_TO);
            UNLOCK_CHARACTER(npc_no);
            break;
        }                                     
        //    
        break;
    case DOING_STEP_IDLE_WHEN_TO:
        //播放待機動畫
        LOCK_CHARACTER(npc_no);
        new_action = GetIdleAction(is_fight);
        MinKind_NpcActionLoop(npc_no, new_action);
        UNLOCK_CHARACTER(npc_no);
        break;

    case DOING_STEP_MOVE_BACK:
        switch (MinKind_NpcMoveFindPath(npc_no,dest_x, dest_y))
        {
        case NPC_MOVE_MOVEING:      //npc移動在移動過程中
            break;    
        case NPC_MOVE_ARRIVE:       //npc移動到達了目標
            LOCK_CHARACTER(npc_no);
            SetCharacterDoingKindStep(npc_no, DOING_KIND_FIGHT_PATROL, DOING_STEP_IDLE_WHEN_BACK);
            UNLOCK_CHARACTER(npc_no);
            break;    
        case NPC_MOVE_CANT_ARRIVE:  //npc移動不能到達
            LOCK_CHARACTER(npc_no);
            SetCharacterDoingKindStep(npc_no, DOING_KIND_FIGHT_PATROL, DOING_STEP_IDLE_WHEN_BACK);
            UNLOCK_CHARACTER(npc_no);
            break;
        }                                                                          
        break;

    case DOING_STEP_IDLE_WHEN_BACK:
        //播放待機動畫
        LOCK_CHARACTER(npc_no);
        new_action = GetIdleAction(is_fight);
        MinKind_NpcActionLoop(npc_no, new_action);
        UNLOCK_CHARACTER(npc_no);
        break;
    }
    return ret;
    //mark by lijun 2003-04-10
/--------------------------------------------------------------------------
    enum
    {   
    DOING_STEP_MOVE_TO      =   0,
    DOING_STEP_IDLE_WHEN_TO     =   1,
    DOING_STEP_MOVE_BACK        =   2,
    DOING_STEP_IDLE_WHEN_BACK   =   3,
    };
    SLONG   doing_step;
    SLONG   file_index;
    SLONG   new_id, new_action, id;
    SLONG   dir;
    SLONG   x, y, z, dest_x, dest_y, dest_z;
    SLONG   orig_x, orig_y, orig_z;
    SLONG   move_speed;
    SLONG   is_fight;
    SLONG   ret;

    LOCK_CHARACTER(npc_no);
    doing_step = GetCharacterDoingStep(npc_no);
	GetCharacterPosition(npc_no, &x, &y, &z);
	GetCharacterDestPosition(npc_no, &dest_x, &dest_y, &dest_z);
	GetCharacterOrigPosition(npc_no, &orig_x, &orig_y, &orig_z);
    dir = GetCharacterDir(npc_no);
    move_speed = GetCharacterMoveSpeed(npc_no);
    file_index = GetCharacterFileIndex(npc_no);
    id = GetCharacterImageID(npc_no);
    is_fight = IsCharacterOnFightState(npc_no);
    UNLOCK_CHARACTER(npc_no);

    switch(doing_step)
    {
    case DOING_STEP_MOVE_TO:
        {
			LOCK_MAPMASK(0);
            ret = FindCharacterStep(x, y, &dest_x, &dest_y, move_speed);
			UNLOCK_MAPMASK(0);
            switch(ret)
            {
            case STEP_ON_THE_WAY:
				if(dest_x - x != 0 || dest_y - y != 0)
					dir = ApproachCharacterDir(dest_x - x, dest_y - y);
				new_action = GetRunAction(is_fight);
				new_id = GetCharacterFileActionImageID(file_index, new_action);
				if(id != new_id)
				{
					LOCK_CHARACTER(npc_no);
					SetCharacterDestPosition(npc_no, dest_x, dest_y, dest_z);
					SetCharacterDir(npc_no, dir);
					SetCharacterImageID(npc_no, new_id);
					DirHeadCharacterFrame(npc_no);
					UNLOCK_CHARACTER(npc_no);
				}
				else
				{
					LOCK_CHARACTER(npc_no);
					SetCharacterDestPosition(npc_no, dest_x, dest_y, dest_z);
					SetCharacterDir(npc_no, dir);
					DirFastLoopCharacterFrame(npc_no);
					UNLOCK_CHARACTER(npc_no);
				}
				break;

            case STEP_ARRIVE:
				LOCK_CHARACTER(npc_no);
				SetCharacterPosition(npc_no, dest_x, dest_y, dest_z);
				DirFastLoopCharacterFrame(npc_no);
				SetCharacterDoingStep(npc_no, DOING_STEP_IDLE_WHEN_TO);
				UNLOCK_CHARACTER(npc_no);
				break;

            case STEP_OBSTRUCT:
            case STEP_OUTSTRETCH:
            default:
				LOCK_CHARACTER(npc_no);
				DirFastLoopCharacterFrame(npc_no);
				SetCharacterDoingStep(npc_no, DOING_STEP_IDLE_WHEN_TO);
				UNLOCK_CHARACTER(npc_no);
				break;
            }
            break;
        }
    case DOING_STEP_IDLE_WHEN_TO:
		new_action = GetIdleAction(is_fight);
		new_id = GetCharacterFileActionImageID(file_index, new_action);
		if(id != new_id)
		{
			LOCK_CHARACTER(npc_no);
			SetCharacterImageID(npc_no, new_id);
			DirHeadCharacterFrame(npc_no);
			UNLOCK_CHARACTER(npc_no);
		}
		else
		{
			LOCK_CHARACTER(npc_no);
			DirFastLoopCharacterFrame(npc_no);
			UNLOCK_CHARACTER(npc_no);
		}
		break;

    case DOING_STEP_MOVE_BACK:
        {
			LOCK_MAPMASK(0);
            ret = FindCharacterStep(x, y, &orig_x, &orig_y, move_speed);
			UNLOCK_MAPMASK(0);
            switch(ret)
            {
            case STEP_ON_THE_WAY:
				if(orig_x - x != 0 || orig_y - y != 0)
					dir = ApproachCharacterDir(orig_x - x, orig_y - y);
				new_action = GetRunAction(is_fight);
				new_id = GetCharacterFileActionImageID(file_index, new_action);
				if(id != new_id)
				{
					LOCK_CHARACTER(npc_no);
					SetCharacterPosition(npc_no, orig_x, orig_y, orig_z);
					SetCharacterDir(npc_no, dir);
					SetCharacterImageID(npc_no, new_id);
					DirHeadCharacterFrame(npc_no);
					UNLOCK_CHARACTER(npc_no);
				}
				else
				{
					LOCK_CHARACTER(npc_no);
					SetCharacterPosition(npc_no, orig_x, orig_y, orig_z);
					SetCharacterDir(npc_no, dir);
					DirFastLoopCharacterFrame(npc_no);
					UNLOCK_CHARACTER(npc_no);
				}
				break;

            case STEP_ARRIVE:
				LOCK_CHARACTER(npc_no);
				SetCharacterPosition(npc_no, orig_x, orig_y, orig_z);
				DirFastLoopCharacterFrame(npc_no);
				SetCharacterDoingStep(npc_no, DOING_STEP_IDLE_WHEN_BACK);
				UNLOCK_CHARACTER(npc_no);
				break;

            case STEP_OBSTRUCT:
            case STEP_OUTSTRETCH:
            default:
				LOCK_CHARACTER(npc_no);
				DirFastLoopCharacterFrame(npc_no);
				SetCharacterDoingStep(npc_no, DOING_STEP_IDLE_WHEN_BACK);
				UNLOCK_CHARACTER(npc_no);
				break;
            }
        }
		break;

    case DOING_STEP_IDLE_WHEN_BACK:
		new_action = GetIdleAction(is_fight);
		new_id = GetCharacterFileActionImageID(file_index, new_action);
		if(id != new_id)
		{
			LOCK_CHARACTER(npc_no);
			SetCharacterImageID(npc_no, new_id);
			DirHeadCharacterFrame(npc_no);
			UNLOCK_CHARACTER(npc_no);
		}
		else
		{
			LOCK_CHARACTER(npc_no);
			DirFastLoopCharacterFrame(npc_no);
			UNLOCK_CHARACTER(npc_no);
		}
		break;
    }
/--------------------------------------------------------------------------
}
*/
//----
//  通用!!!! 的npc戰鬥動畫播放函數
//          1.根據skill的參數,,決定動畫的播放次數
//          2.在每次的動畫播放的中間幀釋放法術組件...如果有的話
//----
SLONG   client_do_npc_fight_action(SLONG npc_no)
{
    SLONG   fight_ticks;
    SLONG   magic_index;
    SLONG   x,y,z;
    SLONG   dest_no;
    SLONG   dx, dy, dz;
    SLONG   dir;
    SLONG   ret = ACTION_RETURN_PROC;
    //
    LOCK_CHARACTER(npc_no);
    magic_index = GetCharacterDoingMagic(npc_no);
    GetCharacterPosition(npc_no, &x, &y, &z);
    dest_no = GetCharacterDestID(npc_no);
    GetCharacterDestPosition(npc_no, &dx, &dy, &dz);
    UNLOCK_CHARACTER(npc_no);
    //

    if (dest_no >=0 )
    {
        LOCK_CHARACTER(dest_no);
        GetCharacterPosition(dest_no, &dx, &dy, &dz);
        UNLOCK_CHARACTER(dest_no);
    }        

    //1.轉身到目標位置
    //2.播放法術釋放動畫
    //3.在中間幀 .. 播放聲音
    //4.在最後一幀.改變狀態到待機狀態(服務器段需要到下個狀態)
    dir = ApproachCharacterDir(dx - x, dy - y);
    LOCK_CHARACTER(npc_no);
    SetCharacterDir(npc_no, dir);
    UNLOCK_CHARACTER(npc_no);
    //    
    switch (MinKind_NpcMagicDischarge(npc_no))
    {
    case NPC_MAGIC_DOING://在施法過程中
        break;
    case NPC_MAGIC_START://開始施法
        client_break_magic(npc_no, x, y, magic_index, -1,MAGIC_BREAK_TYPE_SELF);
        break;
    case NPC_MAGIC_FIRE://到了攻擊幀
        //客戶端身麼都不要作..
        //  服務器端需要產生魔法組件
        break;
    case NPC_MAGIC_OVER://施法動作結束
        //設置喘息時間..改變到下個狀態
        LOCK_CHARACTER(npc_no);
        fight_ticks = GetSkillPantTick(magic_index, 0);
        SetCharacterFightTicks(npc_no, (SHINT)fight_ticks);
        //改變狀態到待機
        SetCharacterDoingKindStep(npc_no, DOING_KIND_IDLE, 0);
        UNLOCK_CHARACTER(npc_no);
        //
        ret = ACTION_RETURN_OK;
        break;
    }
    //
    return ret;    
}
//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------


