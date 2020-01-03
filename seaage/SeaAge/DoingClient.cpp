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
//  �Ȱ�...npc���U�ӥL��Ӱ��o�Ʊ�...�b��a�ݾ�
//  �L�{����{
//  
//      1.��doingkind �u�n����ʵe.���򳣤��Χ@
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
//  �ݾ�...
//  �L�{����{
//      1.��doingkind �u�Φb��ӫݾ��ʵe������
//----
SLONG   client_do_npc_idle(SLONG npc_no)
{
    enum
    {   
        DOING_STEP_IDLE_NORMAL  =   0,      //�@��ݾ��ʧ@
        DOING_STEP_IDLE_SPECIAL     =   1,      //�S��ݾ��ʧ@
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
        DOING_STEP_IDLE_NORMAL  =   0,      //�@��ݾ��ʧ@
        DOING_STEP_IDLE_SPECIAL     =   1,      //�S��ݾ��ʧ@
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
//  ���a���b��a .������..�ਭ
//  �L�{����{
//      1.�u�n�b��ݼ���ʵe�N�i�H�F.
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
//  �߷Q
//  �L�{����{
//      1.����ʵe
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
//  �W�O
//  �L�{����{
//      1.����ʵe()
//      2.�W�[���W���ĪG
//      3.����ݭn���n��
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
    if (NPC_ID_CHANGE_YES == MinKind_NpcActionLoop(npc_no, AC_SPOWER)) //�Ĥ@��������o�Ӫ��A���ɭԻݭn�@�@�ǯS�O���Ʊ�
    {
        //�W�[���W������ĪG
        LOCK_CHARACTER(npc_no);
		set_npc_ext_id(npc_no, MAKE_OBJECT_ID(OBJECT_TYPE_MAGIC, 23)); //�W�[�@��
		set_npc_ext_frame(npc_no, 0);
        UNLOCK_CHARACTER(npc_no);
        //���񭵮ĪG
        play_fight_voice(0, npc_no, file_index, DOING_KIND_SPOWER, 0, x, y);
    }
    else
    {
        LOCK_CHARACTER(npc_no);    
        //����W�O���ʵe
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
//  npc�b�����a�Ϫ��ɭ�..�]���a�ϸ귽�٨S��Ū������..�����A
//  �L�{��{
//      �b�a�ϤW����ݾ��ʵe
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
//���ʨ�ؼ��I
//  �L�{��{.
//      1.���|�j�M.���ʨ�ؼ��I
//----
SLONG   client_do_npc_move_to( SLONG npc_no )
{
    SLONG   dest_npc;
    SLONG   dest_x, dest_y, dest_z;
    SLONG   ret = ACTION_RETURN_PROC;
    //��DoingKin �u���@�ӹL�{ ���ʨ�ؼ��I
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
    case NPC_MOVE_MOVEING:      //npc���ʦb���ʹL�{��
        ret = ACTION_RETURN_PROC;
        break;    
    case NPC_MOVE_ARRIVE:       //npc���ʨ�F�F�ؼ�
        LOCK_CHARACTER(npc_no);
        SetCharacterDoingKindStep(npc_no, DOING_KIND_IDLE, 0);
        UNLOCK_CHARACTER(npc_no);
        //
        ret = ACTION_RETURN_OK;
        break;    
    case NPC_MOVE_CANT_ARRIVE:  //npc���ʤ����F
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
    {   DOING_STEP_MOVE_TO  =   0,  //���ʨ�ؼ��I
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
//  ��ؼ�����k�N
//      1.���ʱ���ؼ�
//      2.����k�N(�L�{)
//----
SLONG   client_do_npc_magic_position(SLONG npc_no)
{

    enum
    {   
        DOING_STEP_NEAR_TO          =   0,		//�a��ؼ�
        DOING_STEP_MAGIC_POSITION   =   1,		//��ؼЬI�k
        DOING_STEP_PANT				=	2,		//�ݮ�(for server only)
        DOING_STEP_RESPONSE			=	3,		//����
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
            //�Z���ӻ����ʹL�h
            switch (MinKind_NpcMoveFindPath(npc_no,dest_x, dest_y))
            {
            case NPC_MOVE_MOVEING:      //npc���ʦb���ʹL�{��
                break;    
            case NPC_MOVE_ARRIVE:       //npc���ʨ�F�F�ؼ�
                LOCK_CHARACTER(npc_no);
                SetCharacterDoingKindStep(npc_no, DOING_KIND_MAGIC_POSITION, DOING_STEP_MAGIC_POSITION);
                UNLOCK_CHARACTER(npc_no);
                break;    
            case NPC_MOVE_CANT_ARRIVE:  //npc���ʤ����F
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
            //���V�I�k���ؼ�...�ഫ��I�k�L�{
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
        //1.����k�N����ʵe
        //2.�b�����V .. �����n��
        //3.�b�̫�@�V.���ܪ��A��ݾ����A(�A�Ⱦ��q�ݭn��U�Ӫ��A)
        switch (MinKind_NpcMagicDischarge(npc_no))
        {
        case NPC_MAGIC_DOING://�b�I�k�L�{��
            break;        
        case NPC_MAGIC_START://�}�l�I�k
            break;        
        case NPC_MAGIC_FIRE://��F�����V
            //�Ȥ�ݨ��򳣤��n�@..
            //  �A�Ⱦ��ݻݭn�����]�k�ե�
            break;        
        case NPC_MAGIC_OVER://�I�k�ʧ@����
            //�]�m�ݮ��ɶ�..���ܨ�U�Ӫ��A
            LOCK_CHARACTER(npc_no);
            fight_ticks = GetSkillPantTick(magic_index, 0);
            SetCharacterFightTicks(npc_no, (SHINT)fight_ticks);
            SetCharacterDoingStep(npc_no, DOING_STEP_PANT);
            UNLOCK_CHARACTER(npc_no);                
            break;
        }
        break;
    // �@�U��Ӷ��q�u���A�Ⱦ��b�ϥ�
    case DOING_STEP_PANT:
	    //�԰��ݮ�( �]�� doingstep ������..�A�Ⱦ����|�o�����q��..�ҥH�ݭn..�Ȥ�q�ۤv�p��)
	    //1.�b�@�q�ɶ�������ݾ��ʵe
	    //2.�b�ݮ�������.��U�Ӫ��A
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
            //�ݾ�
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
        DOING_STEP_NEAR_TO      =   0,		//�a��ؼ�
        DOING_STEP_MAGIC_POSITION   =   1,		//��ؼЬI�k
        DOING_STEP_PANT				=	2,		//�ݮ�(for server only)
        DOING_STEP_RESPONSE			=	3,		//����
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
//�ļ�
//  �L�{
//      1.�ĹL�h
//
//----
SLONG   client_do_npc_clash(SLONG npc_no)
{
    enum
    {   DOING_STEP_READY_CLASH  =   0,  //�ǳƽļ�
    DOING_STEP_CLASH_TO         =   1,  //���b�ļ����i�椤
    //
    MOVE_SPEED_TIMES            =   5,  //���ʳt�׬O���`���ʳt�ת�����
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
//  ����
//      1.npc���@�Ӧ欰..�b�a�ϤW��B�è�
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
        //���A1 .�ݾ�
        //����ݾ��ʵe
        new_action = GetIdleAction(is_fight);
        MinKind_NpcActionLoop(npc_no, new_action);
        break;
    case DOING_STEP_MOVE_TO:
        //���A2..���ʨ�ؼ��I    
        switch (MinKind_NpcMoveFindPath(npc_no,dest_x, dest_y))
        {
        case NPC_MOVE_MOVEING:      //npc���ʦb���ʹL�{��
            break;    
        case NPC_MOVE_ARRIVE:       //npc���ʨ�F�F�ؼ�
            LOCK_CHARACTER(npc_no);
            SetCharacterDoingKindStep(npc_no, DOING_KIND_GAD, DOING_STEP_IDLE);
            UNLOCK_CHARACTER(npc_no);
            break;    
        case NPC_MOVE_CANT_ARRIVE:  //npc���ʤ����F
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
//  NPC����
//      �@��O�b�X�өT�w�I.����
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
        //��DoingKin �u���@�ӹL�{ ���ʨ�ؼ��I(!!�ݭn�O�d��Ӫ�doingking)
        switch (MinKind_NpcMoveFindPath(npc_no,dest_x, dest_y))
        {
        case NPC_MOVE_MOVEING:      //npc���ʦb���ʹL�{��
            break;    
        case NPC_MOVE_ARRIVE:       //npc���ʨ�F�F�ؼ�
            LOCK_CHARACTER(npc_no);
            SetCharacterDoingKindStep(npc_no, DOING_KIND_FIGHT_PATROL,DOING_STEP_IDLE_WHEN_TO);
            UNLOCK_CHARACTER(npc_no);
            break;    
        case NPC_MOVE_CANT_ARRIVE:  //npc���ʤ����F
            LOCK_CHARACTER(npc_no);
            SetCharacterDoingKindStep(npc_no, DOING_KIND_FIGHT_PATROL, DOING_STEP_IDLE_WHEN_TO);
            UNLOCK_CHARACTER(npc_no);    
            break;
        }                                                                                                                     
        break;
    case DOING_STEP_IDLE_WHEN_TO:
        //����ݾ��ʵe
        new_action = GetIdleAction(is_fight);
        MinKind_NpcActionLoop(npc_no, new_action);
		break;
    case DOING_STEP_MOVE_BACK:
        //��DoingKin �u���@�ӹL�{ ���ʨ�ؼ��I(!!�ݭn�O�d��Ӫ�doingking)
        switch (MinKind_NpcMoveFindPath(npc_no,orig_x, orig_y))
        {
        case NPC_MOVE_MOVEING:      //npc���ʦb���ʹL�{��
            break;    
        case NPC_MOVE_ARRIVE:       //npc���ʨ�F�F�ؼ�
            LOCK_CHARACTER(npc_no);
            SetCharacterDoingKindStep(npc_no, DOING_KIND_FIGHT_PATROL,DOING_STEP_IDLE_WHEN_BACK);
            UNLOCK_CHARACTER(npc_no);
            break;    
        case NPC_MOVE_CANT_ARRIVE:  //npc���ʤ����F
            LOCK_CHARACTER(npc_no);
            SetCharacterDoingKindStep(npc_no, DOING_KIND_FIGHT_PATROL, DOING_STEP_IDLE_WHEN_BACK);
            UNLOCK_CHARACTER(npc_no);    
            break;
        }
		break;
    case DOING_STEP_IDLE_WHEN_BACK:
        //����ݾ��ʵe
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
//  npc���L�h�M���H���
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
            case NPC_MOVE_MOVEING:      //npc���ʦb���ʹL�{��
                break;    
            case NPC_MOVE_ARRIVE:       //npc���ʨ�F�F�ؼ�
                LOCK_CHARACTER(npc_no);
                SetCharacterDoingKindStep(npc_no, DOING_KIND_TALK_WITH_NPC, DOING_STEP_EXEC_PROC);
                UNLOCK_CHARACTER(npc_no);
                break;    
            case NPC_MOVE_CANT_ARRIVE:  //npc���ʤ����F
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
		//���ؼ�npc��L��
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
//  ���L�h�������H
//      1.����ؼ�npc
//      2.�}�l�����ؼ�npc
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
            //�b�������~..���ݭn����..���ܪ��A��ݾ�
            LOCK_CHARACTER(npc_no);
            SetCharacterDoingKindStep(npc_no, DOING_KIND_IDLE, 0);
            UNLOCK_CHARACTER(npc_no);
        }
        else if (distance > magic_distance)
        {
            //�b��������...���ʹL�h����
                //1.���ʹL�h
                //2.�줣�F..�ܪ��A���ݾ�
                switch (MinKind_NpcMoveFindPath(npc_no,dest_x, dest_y))
                {
                case NPC_MOVE_MOVEING:      //npc���ʦb���ʹL�{��
                    break;    
                case NPC_MOVE_ARRIVE:       //npc���ʨ�F�F�ؼ�
                    LOCK_CHARACTER(npc_no);
                    SetCharacterDoingKindStep(npc_no, DOING_KIND_ATTACK_NPC, DOING_STEP_ATTACK_NPC);
                    UNLOCK_CHARACTER(npc_no);
                    break;    
                case NPC_MOVE_CANT_ARRIVE:  //npc���ʤ����F
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
            //�i�J�����d��..���ܪ��A������
            LOCK_CHARACTER(npc_no);
            SetCharacterDoingKindStep(npc_no, DOING_KIND_ATTACK_NPC, DOING_STEP_ATTACK_NPC);
            UNLOCK_CHARACTER(npc_no);
        }
        break;
    case DOING_STEP_ATTACK_NPC:
        //�T�Onpc�¦V�������ؼ�
        dir = ApproachCharacterDir(dest_x - x, dest_y - y);        
        LOCK_CHARACTER(npc_no);
        SetCharacterDir(npc_no, dir);
        UNLOCK_CHARACTER(npc_no);        
        // ����Ӱʵe�@��
        switch (MinKind_NpcActionOneTime(npc_no, AC_ATTACK_0))
        {
        case NPC_KEY_FRAME_NONE://�D����V
            break;
        case NPC_KEY_FRAME_HEAD://����V(�Ĥ@�V)
            break;
        case NPC_KEY_FRAME_HALF://�����V
            play_fight_voice(0, npc_no, file_index, DOING_KIND_ATTACK_NPC, 0, x, y);
            break;        
        case NPC_KEY_FRAME_TAIL://�̫�V
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
//�s��
//      �s�򼽩�����ʧ@.
//
//----
SLONG   client_do_npc_sequential_attack_npc(SLONG npc_no)
{
    enum
    {   
        DOING_STEP_ATTACK_NPC_1_START       =   0,  //�}�l��1��(������n���� 2*n)
        DOING_STEP_ATTACK_NPC_1_RUNNING     =   1,  //���b�i���1��(������n���� 2*n+1)
        //
        SPECIFIC_ATTACK_DISTANCE            =   64,
        NPC_ATTACK_IMAGE_REPEAT             =   1,
        //
        NPC_SEQUENTIAL_FINISH_FRAME         =   4   //���۰ʧ@���V�� 
    };
    SLONG   max_step;//�ثe�u���3��
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
    SLONG   attack_step;        //�ĴX��, �q1�}�l.
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
        //��}�l���ɭ�..�ݭn..�M��..�s�����B��
        LOCK_CHARACTER(npc_no);
        SetCharacterSequentialStep(npc_no, attack_step);
        UNLOCK_CHARACTER(npc_no);
        break;
    case NPC_KEY_FRAME_BACK:
        //�ݭn��U�Ӱʧ@
        LOCK_CHARACTER(npc_no);
        sequential_step = GetCharacterSequentialStep(npc_no);
        if ((sequential_step>attack_step) && (attack_step < max_step-1))
        {
            SetCharacterDoingStep(npc_no, doing_step + 1);  //�U1��
        }
        UNLOCK_CHARACTER(npc_no);
        break;
    case NPC_KEY_FRAME_HALF:
        //��F�����V
        play_fight_voice(0, npc_no, file_index, DOING_KIND_SEQUENTIAL_ATTACK_NPC, attack_step, x, y);
        break;
    case NPC_KEY_FRAME_TAIL:
        //���񧹾�Ӱʵe
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
        DOING_STEP_NEAR_TO              =   0,  //����ؼ�
        DOING_STEP_ATTACK_NPC_1_START       =   2,  //�}�l��1��(������n���� 2*n)
        DOING_STEP_ATTACK_NPC_1_RUNNING     =   3,  //���b�i���1��(������n���� 2*n+1)
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
    SLONG   attack_step;        //�ĴX��, �q1�}�l.
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
        if(attack_step >= 1 && attack_step <= 3)    //�ثe�u���3��
        {
            if(doing_step % 2 == 0) //�}�l����
            {
                new_action = GetSequentialAttackAction(attack_step);
                new_id = GetCharacterFileActionImageID(file_index, new_action);
                if(dest_x - x != 0 || dest_y - y != 0)
                    dir = ApproachCharacterDir(dest_x - x, dest_y - y);
                LOCK_CHARACTER(npc_no);
                SetCharacterDir(npc_no, dir);
                SetCharacterImageID(npc_no, new_id);
                DirHeadCharacterFrame(npc_no);
                SetCharacterDoingStep(npc_no, doing_step + 1); //�i�����
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
                    if(sequential_step && attack_step < 3)  //�ثe�j�3��.
                    {
                        SetCharacterSequentialStep(npc_no, false);
                        SetCharacterDoingStep(npc_no, doing_step + 1);  //�U1��
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
//  npc���L�h�˹D��
//      �L�{���A
//          1.���ʹL�h
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
                case NPC_MOVE_MOVEING:      //npc���ʦb���ʹL�{��
                    break;    
                case NPC_MOVE_ARRIVE:       //npc���ʨ�F�F�ؼ�
                    LOCK_CHARACTER(npc_no);
                    SetCharacterDoingKindStep(npc_no, DOING_KIND_PICK_ITEM, DOING_STEP_PICK_ITEM);
                    UNLOCK_CHARACTER(npc_no);
                    break;    
                case NPC_MOVE_CANT_ARRIVE:  //npc���ʤ����F
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
        //����ݾ��ʵe
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
//�Q��
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
        case NPC_KEY_FRAME_HALF://�����V
            file_index = GetCharacterFileIndex(npc_no);
            play_fight_voice(0, npc_no, file_index, DOING_KIND_BEATED, 0, x, y);
            //�W�[�R���ĪG
            LOCK_CHARACTER(npc_no);    
            set_npc_ext_id(npc_no, MAKE_OBJECT_ID(OBJECT_TYPE_MAGIC, 403));	
            set_npc_ext_frame(npc_no, 0);
            UNLOCK_CHARACTER(npc_no);                
            break;        
        case NPC_KEY_FRAME_TAIL://�̫�V
            LOCK_CHARACTER(npc_no);
            SetCharacterDoingKindStep(npc_no, DOING_KIND_IDLE, 0);
            UNLOCK_CHARACTER(npc_no);
            //
            ret = ACTION_RETURN_OK;        
            break;            
        case NPC_KEY_FRAME_NONE://�D����V
        case NPC_KEY_FRAME_HEAD://����V(�Ĥ@�V)
        case NPC_KEY_FRAME_BACK://���۴V
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
        DOING_STEP_BEATED_START     =   0,      //�}�l�Q��
        DOING_STEP_BEATED_RUNNING       =   1,      //�Q����
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
//���`
//----
SLONG   client_do_npc_dead(SLONG npc_no)
{
    enum
    {   
        DOING_STEP_DEAD_START           =   0,  //���`�}�l
        DOING_STEP_DEAD_RUNNING         =   1,  //���b���`��
        DOING_STEP_DEAD_WAITING         =   2,  //���ݫ������
	    DOING_STEP_DEAD_DISAPPEAR		=	4,	//�������
        DOING_STEP_DEAD_PROCESS         =   5,  //���`���B�z
        DOING_STEP_DEAD_END				=   6,  //���`END
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
        //���񦺤`�ʵe
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
            case NPC_KEY_FRAME_HEAD://����V(�Ĥ@�V)
                play_fight_voice(0, npc_no, file_index, DOING_KIND_DEAD, 0, x, y);
                break;
            case NPC_KEY_FRAME_HALF://�����V
                break;
            case NPC_KEY_FRAME_TAIL://�̫�V
                LOCK_CHARACTER(npc_no);
                flag = get_npc_flag(npc_no);
                flag |= NPC_DIED;
                set_npc_flag(npc_no, flag);
                SetCharacterDoingKindStep(npc_no, DOING_KIND_DEAD,DOING_STEP_DEAD_WAITING);
                UNLOCK_CHARACTER(npc_no);
                break;
            case NPC_KEY_FRAME_NONE://�D����V
            case NPC_KEY_FRAME_BACK://���۴V
            default:
                break;
        }
        break;
    case DOING_STEP_DEAD_WAITING://���`�ݭn�y�@�q���ɶ�
        LOCK_CHARACTER(npc_no);
		dead_ticks = GetCharacterDeadTicks(npc_no);//�ӼƭȪ���l�ȬO�A�Ⱦ�����
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

    case DOING_STEP_DEAD_DISAPPEAR://�������
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
        //�o�q�u���A�Ⱦ��ݭn�B�z
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
        DOING_STEP_DEAD_START       =   0,  //���`�}�l
        DOING_STEP_DEAD_RUNNING         =   1,  //���b���`��
        DOING_STEP_DEAD_WAITING         =   2,  //���ݫ������
	    DOING_STEP_DEAD_DISAPPEAR		=	4,	//�������
        DOING_STEP_DEAD_PROCESS         =   5,  //���`���B�z
        DOING_STEP_DEAD_END				=   6,  //���`END
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
//�Q����
//----
SLONG   client_do_npc_down_and_out(SLONG npc_no)
{
    enum
    {   
        DOING_STEP_DOWN_AND_OUT_START       =   0,  //�}�l�Q����
        DOING_STEP_PANT                     =   1,  //�ݮ��@�q�ɶ�
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
    case DOING_STEP_DOWN_AND_OUT_START://����Q���˪��ʵe
        //�ھڧ�����npc�˦V�ݭn����V
        LOCK_CHARACTER(npc_no);
        GetCharacterPosition(npc_no, &x, &y, &z);
        GetCharacterBeatedXY(npc_no, &beated_x, &beated_y);
        dir = ApproachCharacterDir(beated_x - x, beated_y - y);
        SetCharacterDir(npc_no, dir);
        LOCK_CHARACTER(npc_no);
        switch (MinKind_NpcActionOneTime(npc_no, AC_FAINT))
        {
        case NPC_KEY_FRAME_NONE://�D����V
            break;
        case NPC_KEY_FRAME_HEAD://����V(�Ĥ@�V)
            LOCK_CHARACTER(npc_no);
            file_index = GetCharacterFileIndex(npc_no);
            GetCharacterPosition(npc_no, &x, &y, &z);
            play_fight_voice(0, npc_no, file_index, DOING_KIND_BEATED, 0, x, y);
            LOCK_CHARACTER(npc_no);            
            break;
        case NPC_KEY_FRAME_HALF://�����V
            break;        
        case NPC_KEY_FRAME_TAIL://�̫�V
            LOCK_CHARACTER(npc_no);
            SetCharacterDoingKindStep(npc_no, DOING_KIND_DOWN_AND_OUT, DOING_STEP_PANT);
            SetCharacterPantTicks(npc_no, 5);  //0.25��ݮ�  �p�G�ݭn�W�[��npc���ƾڵ��c��..�ӼƭȻݭn�A�Ⱦ���
            LOCK_CHARACTER(npc_no);
            //
            break;
        }
        //
        break;
    case DOING_STEP_PANT://�Q���˰��b�a�O�W�@�q�ɶ�
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
        DOING_STEP_DOWN_AND_OUT_START   =   0,  //�}�l�Q����
        DOING_STEP_DOWN_AND_OUT_RUNNING     =   1,  //�Q���ˤ�
        DOING_STEP_PANT                     =   2,  //�ݮ��@�q�ɶ�
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
            SetCharacterPantTicks(npc_no, 5);  //0.25��ݮ�
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
//����
//----
SLONG   client_do_npc_defence(SLONG npc_no)
{
    SLONG   beated_by, dest_x, dest_y, dest_z;
    SLONG   x, y, z, dir;
    SLONG   ret = ACTION_RETURN_PROC;
    //����@���ɰʵe
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
        DOING_STEP_START_DEFENCE        =   0,      //�}�l����
        DOING_STEP_DEFENCE_RUNNING      =   1,      //���ɤ�
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
//�Q����

SLONG   client_do_npc_defenced(SLONG npc_no)
{
    SLONG   ret = ACTION_RETURN_PROC;
    // ����Q���ɰʵe
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
//���ʧ@: �w�I
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
    {   DOING_STEP_START_CHEER      =   0,  //�w�I�}�l
    DOING_STEP_CHEER_RUNNING        =   1,  //�w�I��
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
//���ʧ@: �ͮ�
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
    {   DOING_STEP_START_ANGRY      =   0,  //�ͮ�}�l
    DOING_STEP_ANGRY_RUNNING        =   1,  //�ͮ�
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


//���ʧ@: �ۤ�
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
    {   DOING_STEP_START_BECKON     =   0,  //�ۤ�}�l
    DOING_STEP_BECKON_RUNNING       =   1,  //�ۤ⤤
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
//���ʧ@: �D�R
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
    {   DOING_STEP_START_COURT      =   0,  //�D�R�}�l
    DOING_STEP_COURT_RUNNING        =   1,  //�D�R��
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
//���ʧ@: �w��
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
    {   DOING_STEP_START_FAINT      =   0,  //�w�˶}�l
    DOING_STEP_FAINT_RUNNING        =   1,  //�w�ˤ�
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
//���ʧ@: ����
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
    {   DOING_STEP_START_SAY_NO     =   0,  //�����}�l
    DOING_STEP_SAYING_NO            =   1,  //������
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
//���ʧ@: ���`
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
    {   DOING_STEP_START_BOW        =   0,  //���`�}�l
    DOING_STEP_BOW_RUNNING          =   1,  //���`��
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
//���ʧ@: �ӧQ
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
    {   DOING_STEP_START_WIN        =   0,  //�ӧQ�}�l
    DOING_STEP_WIN_RUNNING          =   1,  //�ӧQ��
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
//���ʧ@: ����
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
    {   DOING_STEP_START_SWASH      =   0,  //�����}�l
    DOING_STEP_SWASH_RUNNING        =   1,  //������
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
//���ʧ@: �W�O
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
    {   DOING_STEP_START_XXPOWER    =   0,  //�W�O�}�l
    DOING_STEP_XXPOWER_RUNNING      =   1,  //�W�O��
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
//���ʧ@: �Q��
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
    {   DOING_STEP_START_XXBEATED   =   0,  //�Q���}�l
    DOING_STEP_XXBEATED_RUNNING     =   1,  //�Q����
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
    //����ݾ��ʵe
    //-----�Mnpc��ai�������� �Ǫ���ai --�A�Ⱦ��Anpc  fight_idle ���ɭԷ|�h�@�@�ǨƱ�
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
        //����ݾ��ʵe
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
        case NPC_MOVE_MOVEING:      //npc���ʦb���ʹL�{��
            break;    
        case NPC_MOVE_ARRIVE:       //npc���ʨ�F�F�ؼ�
            LOCK_CHARACTER(npc_no);
            SetCharacterDoingKindStep(npc_no, DOING_KIND_FIGHT_GAD, DOING_STEP_IDLE);
            UNLOCK_CHARACTER(npc_no);
            break;    
        case NPC_MOVE_CANT_ARRIVE:  //npc���ʤ����F
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
//  ����
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
        case NPC_MOVE_MOVEING:      //npc���ʦb���ʹL�{��
            break;    
        case NPC_MOVE_ARRIVE:       //npc���ʨ�F�F�ؼ�
            LOCK_CHARACTER(npc_no);
            SetCharacterDoingKindStep(npc_no, DOING_KIND_FIGHT_PATROL, DOING_STEP_IDLE_WHEN_TO);
            UNLOCK_CHARACTER(npc_no);
            break;    
        case NPC_MOVE_CANT_ARRIVE:  //npc���ʤ����F
            LOCK_CHARACTER(npc_no);
            SetCharacterDoingKindStep(npc_no, DOING_KIND_FIGHT_PATROL, DOING_STEP_IDLE_WHEN_TO);
            UNLOCK_CHARACTER(npc_no);
            break;
        }                                     
        //    
        break;
    case DOING_STEP_IDLE_WHEN_TO:
        //����ݾ��ʵe
        LOCK_CHARACTER(npc_no);
        new_action = GetIdleAction(is_fight);
        MinKind_NpcActionLoop(npc_no, new_action);
        UNLOCK_CHARACTER(npc_no);
        break;

    case DOING_STEP_MOVE_BACK:
        switch (MinKind_NpcMoveFindPath(npc_no,dest_x, dest_y))
        {
        case NPC_MOVE_MOVEING:      //npc���ʦb���ʹL�{��
            break;    
        case NPC_MOVE_ARRIVE:       //npc���ʨ�F�F�ؼ�
            LOCK_CHARACTER(npc_no);
            SetCharacterDoingKindStep(npc_no, DOING_KIND_FIGHT_PATROL, DOING_STEP_IDLE_WHEN_BACK);
            UNLOCK_CHARACTER(npc_no);
            break;    
        case NPC_MOVE_CANT_ARRIVE:  //npc���ʤ����F
            LOCK_CHARACTER(npc_no);
            SetCharacterDoingKindStep(npc_no, DOING_KIND_FIGHT_PATROL, DOING_STEP_IDLE_WHEN_BACK);
            UNLOCK_CHARACTER(npc_no);
            break;
        }                                                                          
        break;

    case DOING_STEP_IDLE_WHEN_BACK:
        //����ݾ��ʵe
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
//  �q��!!!! ��npc�԰��ʵe������
//          1.�ھ�skill���Ѽ�,,�M�w�ʵe�����񦸼�
//          2.�b�C�����ʵe���񪺤����V����k�N�ե�...�p�G������
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

    //1.�ਭ��ؼЦ�m
    //2.����k�N����ʵe
    //3.�b�����V .. �����n��
    //4.�b�̫�@�V.���ܪ��A��ݾ����A(�A�Ⱦ��q�ݭn��U�Ӫ��A)
    dir = ApproachCharacterDir(dx - x, dy - y);
    LOCK_CHARACTER(npc_no);
    SetCharacterDir(npc_no, dir);
    UNLOCK_CHARACTER(npc_no);
    //    
    switch (MinKind_NpcMagicDischarge(npc_no))
    {
    case NPC_MAGIC_DOING://�b�I�k�L�{��
        break;
    case NPC_MAGIC_START://�}�l�I�k
        client_break_magic(npc_no, x, y, magic_index, -1,MAGIC_BREAK_TYPE_SELF);
        break;
    case NPC_MAGIC_FIRE://��F�����V
        //�Ȥ�ݨ��򳣤��n�@..
        //  �A�Ⱦ��ݻݭn�����]�k�ե�
        break;
    case NPC_MAGIC_OVER://�I�k�ʧ@����
        //�]�m�ݮ��ɶ�..���ܨ�U�Ӫ��A
        LOCK_CHARACTER(npc_no);
        fight_ticks = GetSkillPantTick(magic_index, 0);
        SetCharacterFightTicks(npc_no, (SHINT)fight_ticks);
        //���ܪ��A��ݾ�
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


