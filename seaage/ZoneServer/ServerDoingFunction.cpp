/*
**	ServerDoingFunction.cpp
**	server doing functions.
**
**	Jack, 2002/10/30.
*/
#include "ZoneServer_Def.h"
#include "ServerWeather.h"
 
/******************************************************************************************************************/
/* NO HIT DOING FUNCTIONS                                                                                         */
/******************************************************************************************************************/
SLONG   server_do_npc_dummy( SLONG npc_no )
{
    //do nothing.
    return ACTION_RETURN_PROC;    
}


SLONG   server_do_npc_pause( SLONG npc_no )
{
    //do nothing.
    return ACTION_RETURN_PROC;    
}


//NPC��a����(idle)
SLONG   server_do_npc_idle( SLONG npc_no )
{
    
    //�Ӱʧ@�A�Ⱦ��u�ݭn�������ݾ��ʧ@
    SLONG   new_action;
    SLONG   is_fight;
    //
    LOCK_CHARACTER(npc_no);
    is_fight = IsCharacterOnFightState(npc_no);
    UNLOCK_CHARACTER(npc_no);    
    //
    //new_action = GetIdleAction(is_fight);
    new_action = AC_WAIT_0;
    MinKind_NpcActionLoop(npc_no, new_action);//�`������ݾ��ʵe
    //
    return ACTION_RETURN_PROC;    
    //
    //mark by lijun 2003-04-16
    /*    
    enum
    {   
        DOING_STEP_IDLE_START   =   0,      //�ݾ��ʧ@�}�l
        DOING_STEP_IDLE_RUNNING     =   1,      //���b�i��ݾ��ʧ@
    };
    SLONG   doing_step, file_index;
    SLONG   new_action, new_id;
    SLONG   is_fight;

    LOCK_CHARACTER(npc_no);
    doing_step = GetCharacterDoingStep(npc_no);
    switch(doing_step)
    {
    case DOING_STEP_IDLE_START:
        is_fight = IsCharacterOnFightState(npc_no);
        new_action = GetIdleAction(is_fight);
        file_index = GetCharacterFileIndex(npc_no);
        new_id = GetCharacterFileActionImageID(file_index, new_action);
        SetCharacterImageID(npc_no, new_id);
        DirHeadCharacterFrame(npc_no);
        SetCharacterDoingStep(npc_no, DOING_STEP_IDLE_RUNNING);
        break;
    case DOING_STEP_IDLE_RUNNING:
        break;
    }
    UNLOCK_CHARACTER(npc_no);
    */    
}
//----
//  ���a���b��a .������..�ਭ
//----
SLONG	server_do_npc_stand(SLONG npc_no)
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
    // mark by lijun 2003-04-18
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



//NPC�߷Q(muse)
SLONG   server_do_npc_muse(SLONG npc_no)
{
    enum    
    { 
        MUSE_APPLY_TICKS        =   20 
    };
    SLONG   muse_ticks;
    SLONG   apply_effect = false;
    //����ʵe
    //�@�q�ɶ��i��߷Q�p��
    if (NPC_ID_CHANGE_YES == MinKind_NpcActionLoop(npc_no, AC_SPOWER))
    {
        //��}�l���ɭԻݭn�]�w�߷Q���ɶ�
        LOCK_CHARACTER(npc_no);    
        SetCharacterMuseTicks(npc_no, MUSE_APPLY_TICKS);
        UNLOCK_CHARACTER(npc_no);  
    }
    else
    {
        LOCK_CHARACTER(npc_no);    
        muse_ticks = GetCharacterMuseTicks(npc_no);
        if(--muse_ticks == 0)
        {
            //���0��ݭn�q�s�]�w
            muse_ticks = MUSE_APPLY_TICKS;
            apply_effect = true;
        }
        SetCharacterMuseTicks(npc_no, muse_ticks);        
        UNLOCK_CHARACTER(npc_no);        
    }
    if(apply_effect)
    {
        server_process_npc_muse_effect(npc_no);//�߷Q���ƭȹB��
    }    
    //
    return ACTION_RETURN_PROC;
    // mark by lijun 2003-04-10
    /*    
    enum    
    {   
        DOING_STEP_MUSE_START   =   0,  //�߷Q�ʧ@�}�l
        DOING_STEP_MUSE_RUNNING     =   1,  //���b�i��߷Q
        //
        MUSE_APPLY_TICKS            =   20  //�C�j�h���ɶ��i��@������
    };
    SLONG   doing_step, file_index;
    SLONG   new_action, new_id, muse_ticks;
    SLONG   apply_effect;

    apply_effect = false;

    LOCK_CHARACTER(npc_no);
    doing_step = GetCharacterDoingStep(npc_no);
    switch(doing_step)
    {
    case DOING_STEP_MUSE_START:
        file_index = GetCharacterFileIndex(npc_no);
        new_action = AC_SPOWER;
        new_id = GetCharacterFileActionImageID(file_index, new_action);
        SetCharacterImageID(npc_no, new_id);
        SetCharacterMuseTicks(npc_no, MUSE_APPLY_TICKS);
        DirHeadCharacterFrame(npc_no);
        break;
    case DOING_STEP_MUSE_RUNNING:
        DirFastLoopCharacterFrame(npc_no);
        muse_ticks = GetCharacterMuseTicks(npc_no);
        if(--muse_ticks == 0)
        {
            muse_ticks = MUSE_APPLY_TICKS;
            apply_effect = true;
        }
        SetCharacterMuseTicks(npc_no, muse_ticks);
        break;
    }
    UNLOCK_CHARACTER(npc_no);

    if(apply_effect)
    {
        server_process_npc_muse_effect(npc_no);//�߷Q���ƭȹB��
    }
    */    
}


//�W�O
SLONG   server_do_npc_spower(SLONG npc_no)
{

    //�A�Ⱦ��b�Ӫ��A...��ꨭ�򳣤��ݭn�@(���D����ʵe�N�i�H�F)
    MinKind_NpcActionLoop(npc_no, AC_SPOWER);
    return ACTION_RETURN_PROC;    
    // mark by lijun 2003-04-165
    /*
    enum
    {   
        DOING_STEP_START_SPOWER     =   0,  //�}�l�W�O
        DOING_STEP_SPOWER_RUNNING       =   1,  //�W�O��
    };
    SLONG   doing_step, file_index;
    SLONG   new_action, new_id;

    LOCK_CHARACTER(npc_no);
    doing_step = GetCharacterDoingStep(npc_no);
    switch(doing_step)
    {
    case DOING_STEP_START_SPOWER:
        new_action = AC_SPOWER;
        file_index = GetCharacterFileIndex(npc_no);
        new_id = GetCharacterFileActionImageID(file_index, new_action);
        SetCharacterImageID(npc_no, new_id);
        DirHeadCharacterFrame(npc_no);
        SetCharacterDoingStep(npc_no, DOING_STEP_SPOWER_RUNNING);
        break;
    case DOING_STEP_SPOWER_RUNNING:
        break;
    }
    UNLOCK_CHARACTER(npc_no);
    */    
}


//�����a��
SLONG   server_do_npc_change_map(SLONG npc_no)
{
    SLONG   is_on_sea;
    //
    LOCK_CHARACTER(npc_no);
	is_on_sea = IsCharacterOnTheSea(npc_no);
    UNLOCK_CHARACTER(npc_no);
    //
	if(is_on_sea)
	{
        server_do_sea_npc_idle(npc_no);
	}
	else
	{
        server_do_npc_idle(npc_no);
	}
    return ACTION_RETURN_PROC;	
    //mark by lijun 2003-04-16
    /*
    enum
    {   
        DOING_STEP_START_CHANGE_MAP =   0,  //�}�l�����a��
        DOING_STEP_CHANGEING_MAP        =   1,  //�����a�Ϥ�
    };
    SLONG   doing_step, file_index;
    SLONG   new_action, new_id;
    SLONG   is_fight;

    LOCK_CHARACTER(npc_no);
    doing_step = GetCharacterDoingStep(npc_no);
    switch(doing_step)
    {
    case DOING_STEP_START_CHANGE_MAP:
        is_fight = IsCharacterOnFightState(npc_no);
        new_action = GetIdleAction(is_fight);
        file_index = GetCharacterFileIndex(npc_no);
        new_id = GetCharacterFileActionImageID(file_index, new_action);
        SetCharacterImageID(npc_no, new_id);
        DirHeadCharacterFrame(npc_no);
        SetCharacterDoingStep(npc_no, DOING_STEP_CHANGEING_MAP);
        break;
    case DOING_STEP_CHANGEING_MAP:
        break;
    }
    UNLOCK_CHARACTER(npc_no);
    */    
}

/******************************************************************************************************************/
/* HIT MAP FUNCTIONS                                                                                              */
/******************************************************************************************************************/
//�H�����ʨ�ؼ��I
SLONG   server_do_npc_move_to( SLONG npc_no )
{
    SLONG   dest_npc;    
    SLONG   dest_x, dest_y, dest_z;
    SLONG   ret = ACTION_RETURN_PROC;
    //��DoingKin �u���@�ӹL�{ ���ʨ�ؼ��I
    LOCK_CHARACTER(npc_no);
    GetCharacterDestPosition(npc_no, &dest_x, &dest_y, &dest_z);
    dest_npc = GetCharacterDestID(npc_no);
    UNLOCK_CHARACTER(npc_no);
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
    // mark by lijun 2003-04-09
    /*
    SLONG   file_index;
    SLONG   new_id, new_action;
    SLONG   x, y, z, dest_x, dest_y, dest_z, move_speed;
    SLONG   ret;
    SLONG   is_fight, foot_state, is_defence;

    LOCK_CHARACTER(npc_no);
    GetCharacterPosition(npc_no, &x, &y, &z);
    GetCharacterDestPosition(npc_no, &dest_x, &dest_y, &dest_z);
    move_speed = GetCharacterMoveSpeed(npc_no);
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

	LOCK_MAPMASK(0);
    ret = FindCharacterStep(x, y, &dest_x, &dest_y, move_speed);
	UNLOCK_MAPMASK(0);

    switch(ret)
    {
    case STEP_ON_THE_WAY:
        LOCK_CHARACTER(npc_no);
        file_index = GetCharacterFileIndex(npc_no);
        new_action = GetRunAction(is_fight);
        new_id = GetCharacterFileActionImageID(file_index, new_action);
        SetCharacterImageID(npc_no, new_id);
        SetCharacterPosition(npc_no, dest_x, dest_y, 0);
        UNLOCK_CHARACTER(npc_no);
        break;
        
    case STEP_ARRIVE:
        LOCK_CHARACTER(npc_no);
        SetCharacterPosition(npc_no, dest_x, dest_y, 0);
        SetCharacterDoingKindStep(npc_no, DOING_KIND_IDLE, 0);
        UNLOCK_CHARACTER(npc_no);
        break;
        
    case STEP_OBSTRUCT:
    case STEP_OUTSTRETCH:
    default:
        LOCK_CHARACTER(npc_no);
        SetCharacterDestPosition(npc_no, x, y, 0);
        SetCharacterDoingKindStep(npc_no, DOING_KIND_IDLE, 0);
        UNLOCK_CHARACTER(npc_no);
        break;
    }
    */    
}
/*
//----
//  ��ؼ�����k�N
//      1.���ʱ���ؼ�
//      2.����k�N(�L�{)
//----
SLONG   server_do_npc_magic_position(SLONG npc_no)
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
    SLONG   magic_index, magic_npc_id, magic_times;
    SLONG   dest_x, dest_y, dest_z;
    SLONG   x, y, z, dir;
    SLONG   file_index;
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
    magic_npc_id = GetSkillActionId(magic_index, 0);

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
            // (1) Break magic parts & append broken parts to zone magic parts list.
            // (2) Notify clients for break magic.
            // (3) Compute user's mp result.
            //
            server_break_magic(0, npc_no, dest_x, dest_y, magic_index);
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
	    //�԰��ݮ�
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
            //LOCK_CHARACTER(npc_no);
            //new_action = GetIdleAction(is_fight);
            //UNLOCK_CHARACTER(npc_no);
            //
            //if (NPC_ID_CHANGE_YES == MinKind_NpcActionLoop(npc_no, new_action))
            LOCK_CHARACTER(npc_no);
            SetCharacterFightTicks(npc_no, (SHINT)fight_ticks);
            UNLOCK_CHARACTER(npc_no);
        }	    
		break;
	case DOING_STEP_RESPONSE:
	    //�o�q�N�X�O�Ω�ai����...�i�D..npc���U�����ӧ@���Ʊ�.
	    server_execute_npc_ai_after_magic(npc_no);
	    //
	    ret = ACTION_RETURN_OK;
		break;

    }
    return ret;
    //mark by lijun 2003-04-16
    /----------------------------------------------------------------------
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
					server_break_magic(0, npc_no, dest_x, dest_y, magic_index);

					//
					// For Client, just play voice:
					//
					//play_fight_voice(0, npc_no, magic_index, DOING_KIND_MAGIC_NPC, 0, dest_x, dest_y);
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
						fight_ticks = GetSkillPantTicks(magic_index);
						SetCharacterFightTicks(npc_no, (SHINT)fight_ticks);
						SetCharacterDoingStep(npc_no, DOING_STEP_PANT);

						//
						//For Client:
						//
						//SetCharacterDoingKindStep(npc_no, DOING_KIND_IDLE, 0);
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
        server_execute_npc_ai_after_magic(npc_no);
		break;

    }
    /----------------------------------------------------------------------
}
*/
//----
//�ļ�
//----
SLONG   server_do_npc_clash(SLONG npc_no)
{
    enum
    {   DOING_STEP_READY_CLASH  =   0,  //�ǳƽļ�
    DOING_STEP_CLASH_TO         =   1,  //���b�ļ����i�椤
    //
    MOVE_SPEED_TIMES            =   5,  //���ʳt�׬O���`���ʳt�ת�����
    };
    SLONG   doing_step;
    SLONG   is_fight, is_block;;
    SLONG   file_index, new_action, new_id, action_block;
    SLONG   x, y, z, dest_x, dest_y, dest_z, step_x, step_y;
    SLONG   move_speed, magic_index, clash_steps;
    SLONG   ret;
    SLONG   fun_ret = ACTION_RETURN_PROC;



    LOCK_CHARACTER(npc_no);
    is_fight = IsCharacterOnFightState(npc_no);
    is_block = IsCharacterOnBlockState(npc_no);
    action_block = StatuseToActionBlocks(is_fight, is_block);    
    doing_step = GetCharacterDoingStep(npc_no);
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
            new_action = AC_SPECIAL_5;
            new_id = GetCharacterFileActionImageID(file_index, action_block, new_action);
            SetCharacterImageID(npc_no, new_id);
            DirHeadCharacterFrame(npc_no);
            r = sqrt( (dest_x - x)*(dest_x - x) + (dest_y - y)*(dest_y - y) + 1);
            step_x = (SLONG)( x + (dest_x - x) * move_speed * clash_steps / r );
            step_y = (SLONG)( y + (dest_y - y) * move_speed * clash_steps / r );
            SetCharacterDestPosition(npc_no, step_x, step_y, 0);
            SetCharacterOrigPosition(npc_no, x, y, z);  //�O�s��Ӧ�m�w�ƫ��򪺹B��
            SetCharacterDoingStep(npc_no, DOING_STEP_CLASH_TO);
            UNLOCK_CHARACTER(npc_no);
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
                SetCharacterPosition(npc_no, dest_x, dest_y, 0);
                DirFastTailCharacterFrame(npc_no);
                UNLOCK_CHARACTER(npc_no);
                break;

            case STEP_ARRIVE:
            case STEP_OUTSTRETCH:
                LOCK_CHARACTER(npc_no);
                SetCharacterDoingKindStep(npc_no, DOING_KIND_IDLE, 0);
                UNLOCK_CHARACTER(npc_no);

                //�i��ĪG�B��
                server_process_npc_clash_effect(npc_no);
                //
                fun_ret = ACTION_RETURN_OK;
                break;

            default:
                LOCK_CHARACTER(npc_no);
                SetCharacterDoingKindStep(npc_no, DOING_KIND_IDLE, 0);
                UNLOCK_CHARACTER(npc_no);

                //�i��ĪG�B��
                server_process_npc_clash_effect(npc_no);
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
//  ����(NPC���@��AI)
//      1.npc���@�Ӧ欰..�b�a�ϤW��B�è�
//      
//----
SLONG   server_do_npc_gad(SLONG npc_no)
{
    enum    
    {   
        DOING_STEP_IDLE   =   0,
        DOING_STEP_MOVE_TO    =   1,
        //
        GAD_RAND_X      =   200,
        GAD_RAND_Y      =   200,
        GAD_RAND_TICKS  =   400,
    };
    SLONG   doing_step;
    SLONG   dest_x, dest_y, dest_z;
    SLONG   is_fight,new_action;
    SLONG   total_ticks,ticks;
    SLONG   x,y,z;
    SLONG   temp_x,temp_y;
    SLONG   ret = ACTION_RETURN_PROC;
    //
    LOCK_CHARACTER(npc_no);
    doing_step = GetCharacterDoingStep(npc_no);
    GetCharacterPosition(npc_no, &x, &y, &z);
    GetCharacterDestPosition(npc_no, &dest_x, &dest_y, &dest_z);    
    is_fight = IsCharacterOnFightState(npc_no);    
    total_ticks = GetCharacterGadTotalTicks(npc_no);
    ticks = GetCharacterGadTicks(npc_no);    
    UNLOCK_CHARACTER(npc_no);

    switch(doing_step)
    {
    case DOING_STEP_IDLE:
        //���A1 .�ݾ�
        //����ݾ��ʵe
        // �b�@�w���ɶ�..�ݭn���ܪ��A�� ����
        new_action = GetIdleAction(is_fight);
        MinKind_NpcActionLoop(npc_no, new_action);
        //        
        ticks ++;
        if (ticks < total_ticks)
        {            
                LOCK_CHARACTER(npc_no);
                SetCharacterGadTicks(npc_no, ticks);
                UNLOCK_CHARACTER(npc_no);
        }
        else
        {
            temp_x = x + ( system_rand() % GAD_RAND_X ) * ( 1 - (system_rand() % 2) * 2 );
            temp_y = y + ( system_rand() % GAD_RAND_Y ) * ( 1 - (system_rand() % 2) * 2 );

            {
                LOCK_CHARACTER(npc_no);
                ServerChangeCharacterDoing(npc_no, DOING_KIND_GAD, DOING_STEP_MOVE_TO, temp_x, temp_y, total_ticks, ticks, 0);
                UNLOCK_CHARACTER(npc_no);
            }
            //�ݭn�q���ݭn���Ȥ��
            //ServerSendChangeNpcDoing(npc_no, DOING_KIND_GAD, DOING_STEP_MOVE_TO,
            //    temp_x, temp_y, total_ticks, ticks, 0);
        }
        break;
    case DOING_STEP_MOVE_TO:
        //���A2..���ʨ�ؼ��I    
        switch (MinKind_NpcMoveFindPath(npc_no,dest_x, dest_y))
        {
        case NPC_MOVE_MOVEING:      //npc���ʦb���ʹL�{��
            break;    
        case NPC_MOVE_ARRIVE:       //npc���ʨ�F�F�ؼ�
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
    return ret;
    // mark by lijun 2003-04-16
    /----------------------------------------------------------------------
    enum    
    {   
        DOING_STEP_IDLE   =   0,
        DOING_STEP_MOVE_TO    =   1,
        //
        GAD_RAND_X      =   200,
        GAD_RAND_Y      =   200,
        GAD_RAND_TICKS  =   400,
    };
    SLONG   doing_step;
    SLONG   total_ticks, ticks;
    SLONG   x, y, z;
    SLONG   dest_x, dest_y, dest_z;
    SLONG   temp_x, temp_y;
	//SLONG	temp_z;
    SLONG   move_speed;
    SLONG   file_index, id;
    SLONG   new_action, new_id;
    SLONG   dir, is_fight;
    SLONG   ret;
    //
    LOCK_CHARACTER(npc_no);
	doing_step = GetCharacterDoingStep(npc_no);    
    total_ticks = GetCharacterGadTotalTicks(npc_no);
    ticks = GetCharacterGadTicks(npc_no);
    GetCharacterPosition(npc_no,&x,&y,&z);    
    GetCharacterDestPosition(npc_no,&dest_x,&dest_y,&dest_z);        
    move_speed = GetCharacterMoveSpeed(npc_no);
    file_index = GetCharacterFileIndex(npc_no);
    id = GetCharacterImageID(npc_no);
    dir = GetCharacterDir(npc_no);
    is_fight = IsCharacterOnFightState(npc_no);
    UNLOCK_CHARACTER(npc_no);
    //
    switch(doing_step)
    {
    case DOING_STEP_IDLE:
        {
            ticks ++;
            if(ticks < total_ticks)
            {            
				new_action = GetIdleAction(is_fight);
                new_id = GetCharacterFileActionImageID(file_index, new_action);
                if(new_id != id)
                {
                    LOCK_CHARACTER(npc_no);
                    SetCharacterImageID(npc_no, new_id);
                    DirHeadCharacterFrame(npc_no);
					SetCharacterGadTicks(npc_no,ticks);
                    UNLOCK_CHARACTER(npc_no);
                }
                else
                {
                    LOCK_CHARACTER(npc_no);
                    DirFastLoopCharacterFrame(npc_no);
					SetCharacterGadTicks(npc_no, ticks);
                    UNLOCK_CHARACTER(npc_no);
                }
            }
            else
            {
                temp_x = x + ( system_rand() % GAD_RAND_X ) * ( 1 - (system_rand() % 2) * 2 );
                temp_y = y + ( system_rand() % GAD_RAND_Y ) * ( 1 - (system_rand() % 2) * 2 );
                
                {
                    LOCK_CHARACTER(npc_no);
					ServerChangeCharacterDoing(npc_no, DOING_KIND_GAD, DOING_STEP_MOVE_TO, temp_x, temp_y, total_ticks, ticks, 0);
                    UNLOCK_CHARACTER(npc_no);
                }
				ServerSendChangeNpcDoing(npc_no, DOING_KIND_GAD, DOING_STEP_MOVE_TO,
										 temp_x, temp_y, total_ticks, ticks, 0);                
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
                {
                    new_action = GetRunAction(is_fight);
                    new_id = GetCharacterFileActionImageID(file_index, new_action);
                    if(id != new_id)
                    {
                        LOCK_CHARACTER(npc_no);
						SetCharacterPosition(npc_no, dest_x, dest_y, 0);                        
						SetCharacterDir(npc_no, dir);
						SetCharacterImageID(npc_no, new_id);
                        DirHeadCharacterFrame(npc_no);
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
            case STEP_OBSTRUCT:
            case STEP_OUTSTRETCH:
            default:
                {
                    total_ticks = GAD_RAND_TICKS + system_rand() % GAD_RAND_TICKS; 
                    ticks = 0;
                    {
                        LOCK_CHARACTER(npc_no);
						ServerChangeCharacterDoing(npc_no, DOING_KIND_GAD, DOING_STEP_IDLE, x, y, total_ticks, ticks, 0);
                        UNLOCK_CHARACTER(npc_no);
                    }					                 
                    break;
                }
            }
        }
        break;
    default:
        break;
    }    
    /----------------------------------------------------------------------
}
*/

SLONG   server_do_npc_patrol(SLONG npc_no)
{
    return ACTION_RETURN_PROC;
    /*
    enum
    {   
        DOING_STEP_MOVE_TO          =   0,
        DOING_STEP_IDLE_WHEN_TO     =   1,
        DOING_STEP_MOVE_BACK        =   2,
        DOING_STEP_IDLE_WHEN_BACK   =   3,
        //
        PATROL_RAND_TICKS           =   150,
    };
    SLONG   doing_step;
    SLONG   dest_x, dest_y, dest_z;
    SLONG   orig_x, orig_y, orig_z;
    SLONG   is_fight;
    SLONG   new_action;
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
        case NPC_MOVE_CANT_ARRIVE:  //npc���ʤ����F        
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
    */
    // mark by lijun 2003-04-17
    /*
    enum
    {   
        DOING_STEP_MOVE_TO      =   0,
        DOING_STEP_IDLE_WHEN_TO     =   1,
        DOING_STEP_MOVE_BACK        =   2,
        DOING_STEP_IDLE_WHEN_BACK   =   3,
        //
        PATROL_RAND_TICKS   =   150,
    };
    SLONG   map_no, doing_step;
    SLONG   file_index;
    SLONG   new_id, new_action, id;
    SLONG   dir;
    SLONG   x, y, dest_x, dest_y;
    SLONG   orig_x, orig_y;
    SLONG   move_speed;
    SLONG   ticks, total_ticks, is_fight;
    SLONG   ret;

    LOCK_CHARACTER(npc_no);
    doing_step = game_npc[npc_no].doing_step;
    map_no = game_npc[npc_no].map;
    x = game_npc[npc_no].x;
    y = game_npc[npc_no].y;
    dest_x = game_npc[npc_no].dest_x;
    dest_y = game_npc[npc_no].dest_y;
    orig_x = game_npc[npc_no].orig_x;
    orig_y = game_npc[npc_no].orig_y;
    dir = game_npc[npc_no].dir;
    move_speed = game_npc[npc_no].mspeed;
    file_index = game_npc[npc_no].file_index;
    id = game_npc[npc_no].id;
    ticks = game_npc[npc_no].patrol_ticks;
    total_ticks = game_npc[npc_no].patrol_total_ticks;
    is_fight = IsCharacterOnFightState(npc_no);
    UNLOCK_CHARACTER(npc_no);

    switch(doing_step)
    {
    case DOING_STEP_MOVE_TO:
        {
            ret = FindCharacterStep(map_no, x, y, &dest_x, &dest_y, move_speed);
            switch(ret)
            {
            case STEP_ON_THE_WAY:
                {
                    if(dest_x - x != 0 || dest_y - y != 0)
                        dir = approach_npc_dir(dest_x - x, dest_y - y);
                    
                    new_action = get_run_action(is_fight);
                    new_id = get_npc_file_id(file_index, new_action);
                    if(id != new_id)
                    {
                        
                        LOCK_CHARACTER(npc_no);
                        game_npc[npc_no].x = dest_x;
                        game_npc[npc_no].y = dest_y;
                        game_npc[npc_no].dir = (UCHR) dir;
                        game_npc[npc_no].id = new_id;
                        dir_head_npc_frame(npc_no);
                        UNLOCK_CHARACTER(npc_no);
                    }
                    else
                    {
                        LOCK_CHARACTER(npc_no);
                        game_npc[npc_no].x = dest_x;
                        game_npc[npc_no].y = dest_y;
                        game_npc[npc_no].dir = (UCHR) dir;
                        dir_fast_loop_npc_frame(npc_no);
                        UNLOCK_CHARACTER(npc_no);
                    }
                    break;
                }
            case STEP_ARRIVE:
                {
                    LOCK_CHARACTER(npc_no);
                    game_npc[npc_no].x = dest_x;
                    game_npc[npc_no].y = dest_y;
                    dir_fast_loop_npc_frame(npc_no);

                    game_npc[npc_no].doing_step = DOING_STEP_IDLE_WHEN_TO;
                    game_npc[npc_no].patrol_total_ticks = PATROL_RAND_TICKS + system_rand() % PATROL_RAND_TICKS;
                    game_npc[npc_no].patrol_ticks = 0;
                    UNLOCK_CHARACTER(npc_no);

                    break;
                }
            case STEP_OBSTRUCT:
            case STEP_OUTSTRETCH:
            default:
                {
                    LOCK_CHARACTER(npc_no);
                    dir_fast_loop_npc_frame(npc_no);

                    game_npc[npc_no].doing_step = DOING_STEP_IDLE_WHEN_TO;
                    game_npc[npc_no].patrol_total_ticks = PATROL_RAND_TICKS + system_rand() % PATROL_RAND_TICKS;
                    game_npc[npc_no].patrol_ticks = 0;
                    UNLOCK_CHARACTER(npc_no);
                    break;
                }
            }
            break;
        }
    case DOING_STEP_IDLE_WHEN_TO:
        {
            ticks ++;
            if(ticks < total_ticks)
            {
                new_action = get_idle_action(is_fight);
                new_id = get_npc_file_id(file_index, new_action);
                if(id != new_id)
                {
                    LOCK_CHARACTER(npc_no);
                    game_npc[npc_no].id = new_id;
                    dir_head_npc_frame(npc_no);
                    game_npc[npc_no].patrol_ticks = ticks;
                    UNLOCK_CHARACTER(npc_no);
                }
                else
                {
                    LOCK_CHARACTER(npc_no);
                    dir_fast_loop_npc_frame(npc_no);
                    game_npc[npc_no].patrol_ticks = ticks;
                    UNLOCK_CHARACTER(npc_no);
                }
            }
            else
            {
                LOCK_CHARACTER(npc_no);
                game_npc[npc_no].doing_step = DOING_STEP_MOVE_BACK;
                UNLOCK_CHARACTER(npc_no);

//                {
//                    MSG_UPDATE_NPC_DOING_PATROL msg;
//                    msg.dwType = UMT_UPDATE_NPC_DOING_PATROL;
//                    msg.npc_no = npc_no;
//                    msg.doing_kind = DOING_KIND_PATROL;
//                    msg.doing_step = DOING_STEP_MOVE_BACK;
//                    AddServerSendMsg( &msg, sizeof(msg), g_dpidLocal, ALLPLAYER);
//                }
            }
            break;
        }
    case DOING_STEP_MOVE_BACK:
        {
            ret = FindCharacterStep(map_no, x, y, &orig_x, &orig_y, move_speed);
            switch(ret)
            {
            case STEP_ON_THE_WAY:
                {
                    if(orig_x - x != 0 || orig_y - y != 0)
                        dir = approach_npc_dir(orig_x - x, orig_y - y);
                    
                    new_action = get_run_action(is_fight);
                    new_id = get_npc_file_id(file_index, new_action);
                    if(id != new_id)
                    {
                        LOCK_CHARACTER(npc_no);
                        game_npc[npc_no].x = orig_x;
                        game_npc[npc_no].y = orig_y;
                        game_npc[npc_no].dir = (UCHR) dir;
                        game_npc[npc_no].id = new_id;
                        dir_head_npc_frame(npc_no);
                        UNLOCK_CHARACTER(npc_no);
                    }
                    else
                    {
                        LOCK_CHARACTER(npc_no);
                        game_npc[npc_no].x = orig_x;
                        game_npc[npc_no].y = orig_y;
                        game_npc[npc_no].dir = (UCHR) dir;
                        dir_fast_loop_npc_frame(npc_no);
                        UNLOCK_CHARACTER(npc_no);
                    }
                    break;
                }
            case STEP_ARRIVE:
                {
                    LOCK_CHARACTER(npc_no);
                    game_npc[npc_no].x = orig_x;
                    game_npc[npc_no].y = orig_y;
                    dir_fast_loop_npc_frame(npc_no);

                    game_npc[npc_no].doing_step = DOING_STEP_IDLE_WHEN_BACK;
                    game_npc[npc_no].patrol_total_ticks = PATROL_RAND_TICKS + system_rand() % PATROL_RAND_TICKS;
                    game_npc[npc_no].patrol_ticks = 0;
                    UNLOCK_CHARACTER(npc_no);
                    break;
                }
            case STEP_OBSTRUCT:
            case STEP_OUTSTRETCH:
            default:
                {
                    LOCK_CHARACTER(npc_no);
                    dir_fast_loop_npc_frame(npc_no);
                    game_npc[npc_no].doing_step = DOING_STEP_IDLE_WHEN_BACK;
                    game_npc[npc_no].patrol_total_ticks = PATROL_RAND_TICKS + system_rand() % PATROL_RAND_TICKS;
                    game_npc[npc_no].patrol_ticks = 0;
                    UNLOCK_CHARACTER(npc_no);
                    break;
                }
            }
            break;
        }
    case DOING_STEP_IDLE_WHEN_BACK:
        {
            ticks ++;
            if(ticks < total_ticks)
            {
                new_action = get_idle_action(is_fight);
                new_id = get_npc_file_id(file_index, new_action);
                if(id != new_id)
                {
                    LOCK_CHARACTER(npc_no);
                    game_npc[npc_no].id = new_id;
                    dir_head_npc_frame(npc_no);
                    game_npc[npc_no].patrol_ticks = ticks;
                    UNLOCK_CHARACTER(npc_no);
                }
                else
                {
                    LOCK_CHARACTER(npc_no);
                    dir_fast_loop_npc_frame(npc_no);
                    game_npc[npc_no].patrol_ticks = ticks;
                    UNLOCK_CHARACTER(npc_no);
                }
            }
            else
            {
                LOCK_CHARACTER(npc_no);
                game_npc[npc_no].doing_step = DOING_STEP_MOVE_TO;
                UNLOCK_CHARACTER(npc_no);

//                {
//                    MSG_UPDATE_NPC_DOING_PATROL msg;
//                    msg.dwType = UMT_UPDATE_NPC_DOING_PATROL;
//                    msg.npc_no = npc_no;
//                    msg.doing_kind = DOING_KIND_PATROL;
//                    msg.doing_step = DOING_STEP_MOVE_TO;
//                    AddServerSendMsg( &msg, sizeof(msg), g_dpidLocal, ALLPLAYER);
//                }
            }
            break;
        }
    }
    */
}


/******************************************************************************************************************/
/* HIT MAP NPC FUNCTIONS                                                                                          */
/******************************************************************************************************************/
SLONG   server_do_npc_talk_with_npc(SLONG npc_no)
{
    enum
    {   
        DOING_STEP_NEAR_TO          =   0,
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
    SLONG   dialog_with_count;
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
		//�N�@�� NPC �]�w���Ȱ�
		//......�b�o�̭n
		if(dest_npc >= 500)
		{		
			LOCK_CHARACTER(npc_no);
			dialog_with_count = GetCharacterDialogWithCount(dest_npc);
			dialog_with_count++;
			SetCharacterDialogWithCount(dest_npc, dialog_with_count);
			SetCharacterDialogDestIndex(npc_no, dest_npc);
			SetCharacterDoingStep(npc_no, DOING_STEP_IDLE);
			
			SetCharacterOnPauseState(dest_npc, TRUE);
			UNLOCK_CHARACTER(npc_no);
			if(dialog_with_count == 1)
			{				
			    //�p�G�O�Ĥ@�өM�L��ܪ�npc ..�ݭn�o�������Ҧ����H..�]������ܪ��A
				ServerDoSendNotifyNpcOnPauseToAll(dest_npc);			
			}
			
			// ����@��
			LOCK_SCRIPT(0);		
			mac_pipe.active_npc = npc_no;
			mac_pipe.script_npc = dest_npc;
			process_script((dest_npc - 499) * 100);
			UNLOCK_SCRIPT(0);		
		}    
        break;
	case DOING_STEP_IDLE:
	default:
		LOCK_CHARACTER(npc_no);
		SetCharacterDoingKindStep(npc_no, DOING_KIND_IDLE, 0);
		UNLOCK_CHARACTER(npc_no);
		//
		ret = ACTION_RETURN_OK;
		break;
    }
    return ret;
    /*
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
    SLONG   move_speed;
    SLONG   file_index, id;
    SLONG   new_action, new_id, dir, dest_npc_dir;
    SLONG   ret;
    SLONG   is_fight;
	SLONG	dialog_with_count;

    LOCK_CHARACTER(npc_no);
    doing_step = GetCharacterDoingStep(npc_no);
    dest_npc = GetCharacterDestID(npc_no);
    //proc_no = game_npc[npc_no].orig_y;  //orig_y as proc_no
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
    //
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
		//�N�@�� NPC �]�w���Ȱ�
		if(dest_npc >= 500)
		{		
			LOCK_CHARACTER(npc_no);
			dialog_with_count = GetCharacterDialogWithCount(dest_npc);
			dialog_with_count++;
			SetCharacterDialogWithCount(dest_npc, dialog_with_count);
			SetCharacterDialogDestIndex(npc_no, dest_npc);
			SetCharacterDoingStep(npc_no, DOING_STEP_IDLE);
			
			SetCharacterOnPauseState(dest_npc, TRUE);
			UNLOCK_CHARACTER(npc_no);
			if(dialog_with_count == 1)
			{				
				ServerDoSendNotifyNpcOnPauseToAll(dest_npc);			
			}
			
			// ����@��
			LOCK_SCRIPT(0);		
			mac_pipe.active_npc = npc_no;
			mac_pipe.script_npc = dest_npc;
			process_script((dest_npc - 499) * 100);
			UNLOCK_SCRIPT(0);		
		}
		break;

	case DOING_STEP_IDLE:
		LOCK_CHARACTER(npc_no);
		DirFastLoopCharacterFrame(npc_no);
		UNLOCK_CHARACTER(npc_no);
		break;
    }
    */    
}
/*
//----
//����NPC
//----
SLONG   server_do_npc_attack_npc(SLONG npc_no)
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
	SLONG	pant_ticks, pant_total_ticks;    
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
    //magic_distance = GetSkillTargetDistance(magic_index);
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
                    SetCharacterDoingStep(npc_no, DOING_STEP_ATTACK_NPC);
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
        // ����Ӱʵe�@��
        //�T�Onpc�¦V�������ؼ�
        dir = ApproachCharacterDir(dest_x - x, dest_y - y);        
        LOCK_CHARACTER(npc_no);
        SetCharacterDir(npc_no, dir);
        UNLOCK_CHARACTER(npc_no);        
        switch (MinKind_NpcActionOneTime(npc_no, AC_ATTACK_0))
        {
        case NPC_KEY_FRAME_NONE://�D����V
            break;
        case NPC_KEY_FRAME_HEAD://����V(�Ĥ@�V)
            break;
        case NPC_KEY_FRAME_HALF://�����V
            //�A�Ⱦ��p������ƭ�
            server_process_npc_attack_npc_effect(npc_no, dest_npc, magic_index);
            break;        
        case NPC_KEY_FRAME_TAIL://�̫�V
            LOCK_CHARACTER(npc_no);
            SetCharacterAttackPantTicks(npc_no, 0);
            SetCharacterAttackPantTotalTicks(npc_no, PANT_TOTAL_TICKS);
            SetCharacterDoingStep(npc_no, DOING_STEP_ATTACK_PANT);
            UNLOCK_CHARACTER(npc_no);
            //�A�Ⱦ����ӧi�D�Ȥ��.�L�b�ݮ��F.
            break;
        }
        break;
    case DOING_STEP_ATTACK_PANT://�ݮ��ɶ�
		LOCK_CHARACTER(npc_no);
		pant_ticks = GetCharacterAttackPantTicks(npc_no);
		pant_total_ticks = GetCharacterAttackPantTotalTicks(npc_no);
		++ pant_ticks;
		if(pant_ticks >= pant_total_ticks)
		{
			SetCharacterDoingStep(npc_no, DOING_STEP_RESPONSE);
		}
		else
		{
			SetCharacterAttackPantTicks(npc_no, pant_ticks);
		}
		UNLOCK_CHARACTER(npc_no);    
        break;
    case DOING_STEP_RESPONSE://�ϬM�ɶ�..�o�Ӷ��q���@�άOnpc  ai ������
        server_execute_npc_ai_after_attack(npc_no);
        //
        ret = ACTION_RETURN_OK;
        break;
    }
    //
    return ret;
    // mark by lijun 2003-04-16
    /----------------------------------------------------------------------
    enum
    {   
        DOING_STEP_NEAR_TO              =   0,
        DOING_STEP_ATTACK_NPC_START     =   1,
        DOING_STEP_ATTACKING_NPC        =   2,
	    DOING_STEP_ATTACK_PANT					=	3,
        DOING_STEP_RESPONSE             =   4,
        //
        SPECIFIC_ATTACK_DISTANCE        =   64,
        NPC_ATTACK_IMAGE_REPEAT         =   1,
	    PANT_TOTAL_TICKS				=	20, //Need to add to monster's data.
    };
    SLONG   doing_step, dest_npc;
    SLONG   x, y, z, dest_x, dest_y, dest_z;
    SLONG   file_index;
    SLONG   new_action, new_id;
    SLONG   move_speed, frame_flag;
    SLONG   distance, attack_distance, view;
    SLONG   ret;
	SLONG	find_pos, attack_x, attack_y;
    SLONG   is_fight, magic_no;
	SLONG	pant_ticks, pant_total_ticks;

    LOCK_CHARACTER(0);
    doing_step = GetCharacterDoingStep(npc_no);
    dest_npc = GetCharacterDestID(npc_no);
    GetCharacterPosition(npc_no, &x, &y, &z);
    //
    move_speed = GetCharacterMoveSpeed(npc_no);
    file_index = GetCharacterFileIndex(npc_no);
    is_fight = IsCharacterOnFightState(npc_no);
	view = GetCharacterSightRange(npc_no);

    // Jack, for test. [7/30/2002]
    //attack_distance = GetCharacterAttackDistance(npc_no);
    //view = GetCharacterSightRange_range(npc_no);
    attack_distance = 32;
    //view = 250; // 400^2 + 300^2 = 500^2

    GetCharacterPosition(dest_npc, &dest_x, &dest_y, &dest_z);
    UNLOCK_CHARACTER(0);

    switch(doing_step)
    {
    case DOING_STEP_NEAR_TO:
        {
            distance = (SLONG) sqrt( (dest_x - x) * (dest_x - x) + (dest_y - y) * (dest_y - y) );
            if(distance > view) //�W�L����, �۰�change to npc's move AI.
            {                
				server_choose_npc_move_type(npc_no);                
            }
			else
			{
				GatherMapCharacterMaskPosition();
				LOCK_MAPMASK(0);
				UpdateMapCharacterMask();
				ClearMapDynamicCharacterMask(x, y );
				find_pos = FindBestAttackPosition(x, y, dest_x, dest_y, attack_distance, &attack_x, &attack_y);
				UNLOCK_MAPMASK(0);
				if(find_pos == TTN_OK)
				{
					dest_x = attack_x;
					dest_y = attack_y;

					LOCK_MAPMASK(0);
					ClearMapDynamicCharacterMask( x, y );
					ret = TrendFindCharacterStep( x, y, &dest_x, &dest_y, move_speed, MASK_STOP | MASK_DYNAMIC_NPC);
					RemoveMapCharacterMask();
					UNLOCK_MAPMASK(0);

					switch(ret)
					{
					case STEP_ON_THE_WAY:
                        LOCK_CHARACTER(npc_no);
                        file_index = GetCharacterFileIndex(npc_no);
                        new_action = GetRunAction(is_fight);
                        new_id = GetCharacterFileActionImageID(file_index, new_action);
                        SetCharacterImageID(npc_no, new_id);
                        SetCharacterPosition(npc_no, dest_x, dest_y, 0);
                        UNLOCK_CHARACTER(npc_no);
                        break;

					case STEP_ARRIVE:
                        LOCK_CHARACTER(npc_no);
                        SetCharacterPosition(npc_no, dest_x, dest_y, 0);
                        SetCharacterDoingStep(npc_no, DOING_STEP_ATTACK_NPC_START);
                        UNLOCK_CHARACTER(npc_no);
                        break;

					case STEP_OBSTRUCT:
					case STEP_OUTSTRETCH:
					default:
						LOCK_CHARACTER(npc_no);
						SetCharacterDestPosition(npc_no, x, y, 0);
						if(npc_no < 500)
							SetCharacterDoingKindStep(npc_no, DOING_KIND_IDLE, 0);
						UNLOCK_CHARACTER(npc_no);
						if(npc_no >= 500)
						{
							server_choose_npc_move_type(npc_no);
						}
                        break;
					}
				}
				else
                {
                    LOCK_CHARACTER(npc_no);
                    SetCharacterDestPosition(npc_no, x, y, 0);
					if(npc_no < 500)
					{
						SetCharacterDoingKindStep(npc_no, DOING_KIND_IDLE, 0);
					}
                    UNLOCK_CHARACTER(npc_no);
					if(npc_no >= 500)
					{
						server_choose_npc_move_type(npc_no);
					}
				}
			}
        }
        break;

    case DOING_STEP_ATTACK_NPC_START:
        LOCK_CHARACTER(npc_no);
        new_action = AC_ATTACK_0;
        new_id = GetCharacterFileActionImageID(file_index, new_action);
        SetCharacterImageID(npc_no, new_id);
        DirHeadCharacterFrame(npc_no);
        SetCharacterDoingStep(npc_no, DOING_STEP_ATTACKING_NPC);
        UNLOCK_CHARACTER(npc_no);
        break;

    case DOING_STEP_ATTACKING_NPC:
        LOCK_CHARACTER(npc_no);
        magic_no = GetCharacterDoingMagic(npc_no);
        frame_flag = DirFastHalfCharacterFrame(npc_no);
        UNLOCK_CHARACTER(npc_no);
        if(NPC_KEY_FRAME_HALF == frame_flag)
        {
            server_process_npc_attack_npc_effect(npc_no, dest_npc, magic_no);
        }
        else if(NPC_KEY_FRAME_TAIL == frame_flag)
        {
			if(npc_no < 500)
			{
				LOCK_CHARACTER(npc_no);
				SetCharacterDoingKindStep(npc_no, DOING_KIND_IDLE, 0);
				UNLOCK_CHARACTER(npc_no);
			}
			else
			{
				LOCK_CHARACTER(npc_no);
				SetCharacterAttackPantTicks(npc_no, 0);
				SetCharacterAttackPantTotalTicks(npc_no, PANT_TOTAL_TICKS);
				SetCharacterDoingStep(npc_no, DOING_STEP_ATTACK_PANT);
				UNLOCK_CHARACTER(npc_no);
			}
        }
        break;
	case DOING_STEP_ATTACK_PANT:
		LOCK_CHARACTER(npc_no);
		pant_ticks = GetCharacterAttackPantTicks(npc_no);
		pant_total_ticks = GetCharacterAttackPantTotalTicks(npc_no);
		++ pant_ticks;
		if(pant_ticks >= pant_total_ticks)
		{
			SetCharacterDoingStep(npc_no, DOING_STEP_RESPONSE);
		}
		else
		{
			SetCharacterAttackPantTicks(npc_no, pant_ticks);
		}
		UNLOCK_CHARACTER(npc_no);
		break;

	case DOING_STEP_RESPONSE:
		server_execute_npc_ai_after_attack(npc_no);
		break;
    }
    /----------------------------------------------------------------------
}
*/
// �s��
SLONG   server_do_npc_sequential_attack_npc(SLONG npc_no)
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
    SLONG   magic_no, magic_level;
    SLONG   file_index, id;
    SLONG   new_action, new_id;
    SLONG   sight;
    SLONG   is_fight, is_block;
    SLONG   action_block;
    SLONG   attack_step;        //�ĴX��, �q1�}�l.
    SLONG   sequential_step;
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
        if(attack_step == 3)    //�̫�@��, �ثe�j��b��3��
            server_process_npc_final_attack_npc_effect(npc_no, dest_npc, magic_no);
        else
            server_process_npc_attack_npc_effect(npc_no, dest_npc, magic_no);
        break;
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
    // mark by lijun 2003-04-18
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
    SLONG   file_index, id;
    SLONG   new_action, new_id;
    SLONG   move_speed, frame_flag;
    SLONG   distance, attack_distance, view;
    SLONG   ret;
	SLONG	find_pos, attack_x, attack_y;
    SLONG   is_fight, magic_no;
    SLONG   attack_step;        //�ĴX��, �q1�}�l.
    SLONG   sequential_step;

    LOCK_CHARACTER(npc_no);
    doing_step = GetCharacterDoingStep(npc_no);
    dest_npc = GetCharacterDestID(npc_no);
    GetCharacterPosition(npc_no, &x, &y, &z);
    move_speed = GetCharacterMoveSpeed(npc_no);
    file_index = GetCharacterFileIndex(npc_no);
    id = GetCharacterImageID(npc_no);
    is_fight = IsCharacterOnFightState(npc_no);
    magic_no = GetCharacterDoingMagic(npc_no);
	view = GetCharacterSightRange(npc_no);
    //attack_distance = game_npc[npc_no].attack_distance;
    //view = game_npc[npc_no].view;
    //
    UNLOCK_CHARACTER(npc_no);

    // Jack, for test. [7/30/2002]
    attack_distance = 32;
    //view = 250; // 400^2 + 300^2 = 500^2


    LOCK_CHARACTER(dest_npc);
    GetCharacterPosition(dest_npc, &dest_x, &dest_y, &dest_z);
    UNLOCK_CHARACTER(dest_npc);

    switch(doing_step)
    {
    case DOING_STEP_NEAR_TO:
        {
            distance = (SLONG) sqrt( (dest_x - x) * (dest_x - x) + (dest_y - y) * (dest_y - y) );
            if(distance > view)
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
				ClearMapDynamicCharacterMask( x, y );
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
                            new_action = GetRunAction(is_fight);
                            new_id = GetCharacterFileActionImageID(file_index, new_action);
                            LOCK_CHARACTER(npc_no);
                            SetCharacterImageID(npc_no, new_id);
                            SetCharacterPosition(npc_no, dest_x, dest_y, dest_z);
                            UNLOCK_CHARACTER(npc_no);
							break;
						}
					case STEP_ARRIVE:
						{
							LOCK_CHARACTER(npc_no);
                            SetCharacterPosition(npc_no, dest_x, dest_y, dest_z);
                            SetCharacterSequentialStep(npc_no, false);
							DirFastLoopCharacterFrame(npc_no);
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
                
                LOCK_CHARACTER(npc_no);
                SetCharacterImageID(npc_no, new_id);
                DirHeadCharacterFrame(npc_no);
                SetCharacterDoingStep(npc_no, doing_step + 1);  //�i�����
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
                    if(attack_step == 3)    //�̫�@��, �ثe�j��b��3��
                        server_process_npc_final_attack_npc_effect(npc_no, dest_npc, magic_no);
                    else
                        server_process_npc_attack_npc_effect(npc_no, dest_npc, magic_no);
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


SLONG   server_do_npc_magic_npc(SLONG npc_no)
{
    return ACTION_RETURN_PROC;
    // Jack, todo [02:38,10/31/2002]
    /*
    enum
    {   DOING_STEP_NEAR_TO      =   0,
    DOING_STEP_MAGIC_NPC        =   1,
    DOING_STEP_PUNT             =   2,
    DOING_STEP_RESPONSE         =   3,
    DOING_STEP_IDLE             =   4,
    //
    NPC_MAGIC_IMAGE_REPEAT      =   1
    };
    SLONG   doing_step, dest_npc;
    SLONG   magic_index, magic_npc_id, magic_times;
    SLONG   dest_x, dest_y;
    SLONG   map_no;
    SLONG   x, y, dir;
    SLONG   file_index, id;
    SLONG   new_action, new_id;
    SLONG   move_speed, frame_flag;
    SLONG   distance, magic_distance;
//    SLONG   view;
    SLONG   ret;
    SLONG   fight_ticks;
    SLONG   is_fight;

    LOCK_CHARACTER(npc_no);
    doing_step = game_npc[npc_no].doing_step;
    dest_npc = game_npc[npc_no].dest_no;    //dest_no as dest_npc
    magic_index = game_npc[npc_no].magic_index;
    magic_times = game_npc[npc_no].magic_times;
    //
    map_no = game_npc[npc_no].map;
    x = game_npc[npc_no].x;
    y = game_npc[npc_no].y;
    dir = game_npc[npc_no].dir;
    move_speed = game_npc[npc_no].mspeed;
    file_index = game_npc[npc_no].file_index;
    id = game_npc[npc_no].id;
//    view = game_npc[npc_no].view;
    fight_ticks = game_npc[npc_no].fight_ticks;
    is_fight = IsCharacterOnFightState(npc_no);
    UNLOCK_CHARACTER(npc_no);


    LOCK_CHARACTER(dest_npc);
    dest_x = game_npc[dest_npc].x;
    dest_y = game_npc[dest_npc].y;
    UNLOCK_CHARACTER(dest_npc);

    // Jack. [18:01,9/18/2002]
    //magic_distance = magic_data[magic_index].distance;
    //magic_npc_id = magic_data[magic_index].npc_id;
    magic_distance = 300;   //pixels
    magic_npc_id = INVALID_OBJECT_ID;

    switch(doing_step)
    {
    case DOING_STEP_NEAR_TO:
        {
            distance = (SLONG) sqrt( (dest_x - x) * (dest_x - x) + (dest_y - y) * (dest_y - y) );
            // Jack. [18:02,9/18/2002]
            if(distance > view)
            {
                server_choose_npc_move_type( npc_no );
            }
            else
            {
                if(distance > magic_distance)
                {
                    ret = FindCharacterStep(map_no, x, y, &dest_x, &dest_y, move_speed);
                    switch(ret)
                    {
                    case STEP_ON_THE_WAY:
                        {
                            if(dest_x - x != 0 || dest_y - y != 0)
                                dir = approach_npc_dir(dest_x - x, dest_y - y);
                            
                            new_action = get_run_action(is_fight);
							new_id = get_npc_file_id(file_index, new_action);
                            if(id != new_id)
                            {
                                LOCK_CHARACTER(npc_no);
                                game_npc[npc_no].x = dest_x;
                                game_npc[npc_no].y = dest_y;
                                game_npc[npc_no].dir = (UCHR) dir;
                                game_npc[npc_no].id = new_id;
                                dir_fast_loop_npc_frame(npc_no);
                                UNLOCK_CHARACTER(npc_no);
                            }
                            else
                            {
                                LOCK_CHARACTER(npc_no);
                                game_npc[npc_no].x = dest_x;
                                game_npc[npc_no].y = dest_y;
                                game_npc[npc_no].dir = (UCHR) dir;
                                dir_fast_loop_npc_frame(npc_no);
                                UNLOCK_CHARACTER(npc_no);
                            }
                            break;
                        }
                    case STEP_ARRIVE:
                        {
                            LOCK_CHARACTER(npc_no);
                            game_npc[npc_no].x = dest_x;
                            game_npc[npc_no].y = dest_y;
                            dir_fast_loop_npc_frame(npc_no);
                            game_npc[npc_no].doing_step = DOING_STEP_MAGIC_NPC;
                            UNLOCK_CHARACTER(npc_no);
                            break;
                        }
                    case STEP_OBSTRUCT:
                    case STEP_OUTSTRETCH:
                    default:
                        {
                            //server_choose_npc_move_type( npc_no );
                            LOCK_CHARACTER(npc_no);
                            game_npc[npc_no].dest_x = x;
                            game_npc[npc_no].dest_y = y;
                            dir_fast_loop_npc_frame(npc_no);
                            game_npc[npc_no].doing_step = DOING_STEP_IDLE;
                            UNLOCK_CHARACTER(npc_no);
                            break;
                        }
                    }
                }
                else
                {
                    if(dest_x - x != 0 || dest_y - y != 0)
                        dir = approach_npc_dir(dest_x - x, dest_y - y);
                    
                    LOCK_CHARACTER(npc_no);
                    game_npc[npc_no].dir = (UCHR)dir;
                    dir_head_npc_frame(npc_no);
                    game_npc[npc_no].doing_step = DOING_STEP_MAGIC_NPC;
                    UNLOCK_CHARACTER(npc_no);
                }
            }
        }
        break;
    case DOING_STEP_MAGIC_NPC:
        {
            new_action = AC_MAGIC;
			if( magic_npc_id != INVALID_OBJECT_ID)
			new_id = magic_npc_id;
			else
			new_id = get_npc_file_id(file_index, new_action);

            if(id != new_id)
            {

                LOCK_CHARACTER(npc_no);
                game_npc[npc_no].id = new_id;
                dir_head_npc_frame(npc_no);
                UNLOCK_CHARACTER(npc_no);
            }
            else
            {
                LOCK_CHARACTER(npc_no);
                frame_flag = dir_fast_half_npc_frame(npc_no);
                UNLOCK_CHARACTER(npc_no);

                if(NPC_KEY_FRAME_HALF == frame_flag)
                {
                    // Jack. [18:05,9/18/2002]
					//play_fight_voice(map_no, npc_no, magic_index, DOING_KIND_MAGIC_NPC, dest_x, dest_y);
                    break_magic(map_no, npc_no, dest_x, dest_y, magic_index);
                }
                else if(NPC_KEY_FRAME_TAIL == frame_flag)
                {
                    magic_times -- ;
                    if(magic_times <= 0)
                    {
                        LOCK_CHARACTER(npc_no);
                        dir_head_npc_frame(npc_no);
                        game_npc[npc_no].doing_step = DOING_STEP_PUNT;
                        game_npc[npc_no].fight_ticks = (UCHR) magic_data[magic_index].punt_time;
                        UNLOCK_CHARACTER(npc_no);
                    }
                    else
                    {
                        LOCK_CHARACTER(npc_no);
                        dir_head_npc_frame(npc_no);
                        game_npc[npc_no].magic_times = magic_times;
                        UNLOCK_CHARACTER(npc_no);
                    }
                }
            }
        }
        break;
    case DOING_STEP_PUNT:
        {
            fight_ticks --;
            if(fight_ticks <= 0)
            {
                LOCK_CHARACTER(npc_no);
                game_npc[npc_no].fight_ticks = 0;
                game_npc[npc_no].doing_step = DOING_STEP_RESPONSE;
                UNLOCK_CHARACTER(npc_no);
            }
            else
            {
                new_action = get_idle_action(is_fight);
				new_id = get_npc_file_id(file_index, new_action);
                if(id != new_id)
                {
                    LOCK_CHARACTER(npc_no);
                    game_npc[npc_no].id = new_id;
                    DirLoopCharacterFrame(npc_no);
                    game_npc[npc_no].fight_ticks = (UCHR)fight_ticks;
                    UNLOCK_CHARACTER(npc_no);
                }
                else
                {
                    LOCK_CHARACTER(npc_no);
                    DirLoopCharacterFrame(npc_no);
                    game_npc[npc_no].fight_ticks = (UCHR)fight_ticks;
                    UNLOCK_CHARACTER(npc_no);
                }
            }
        }
        break;
    case DOING_STEP_RESPONSE:
        // Jack [18:06,9/18/2002]
        //server_execute_npc_ai_after_magic( npc_no );
        LOCK_CHARACTER(npc_no);
        dir_fast_loop_npc_frame(npc_no);
        game_npc[npc_no].doing_step = DOING_STEP_IDLE;
        UNLOCK_CHARACTER(npc_no);
        break;
    case DOING_STEP_IDLE:
        new_action = get_idle_action(is_fight);
		new_id = get_npc_file_id(file_index, new_action);
        if(id != new_id)
        {
            LOCK_CHARACTER(npc_no);
            game_npc[npc_no].id = new_id;
            dir_head_npc_frame(npc_no);
            UNLOCK_CHARACTER(npc_no);
        }
        else
        {
            LOCK_CHARACTER(npc_no);
            dir_fast_loop_npc_frame(npc_no);
            UNLOCK_CHARACTER(npc_no);
        }
        break;
    default:
        break;
    }
    */
}

/******************************************************************************************************************/
/* HIT MAP ITEM FUNCTIONS                                                                                         */
/******************************************************************************************************************/
SLONG   server_do_npc_pick_item(SLONG npc_no)
{
    return ACTION_RETURN_PROC;
    // Jack, todo [02:37,10/31/2002]
    /*
    enum
    {   DOING_STEP_NEAR_TO  =   0,
    DOING_STEP_PICK_ITEM    =   1,
    //
    PICKABLE_DISTANCE       =   40 * 40,
    };
    SLONG   item_map_no, item_x, item_y;
    SLONG   hand_it;
    SLONG   map_no;
    SLONG   doing_step;
    SLONG   file_index, new_action;
    SLONG   new_id, id, dir;
    SLONG   x, y, dest_x, dest_y;
    SLONG   distance;
    SLONG   move_speed;
    SLONG   ret;
    SLONG   player_index;
    SLONG   is_fight;

    LOCK_CHARACTER(npc_no);
    item_map_no = game_npc[npc_no].dest_no; //dest_no as item_map_no
    item_x = game_npc[npc_no].dest_x;   //dest_x as item_x
    item_y = game_npc[npc_no].dest_y;   //dest_y as item_y
    doing_step = game_npc[npc_no].doing_step;
    map_no = game_npc[npc_no].map;
    file_index = game_npc[npc_no].file_index;
    id = game_npc[npc_no].id;
    x = game_npc[npc_no].x;
    y = game_npc[npc_no].y;
    move_speed = game_npc[npc_no].mspeed;
    dir = game_npc[npc_no].dir;
    is_fight = IsCharacterOnFightState(npc_no);
    UNLOCK_CHARACTER(npc_no);

    hand_it = FALSE;
    if(npc_no < MAX_GAME_PLAYER)
    {
        player_index = npc_no;
        LOCK_PLAYER(player_index);
        hand_it = is_player_bag_open(player_index);
        UNLOCK_PLAYER(player_index);
    }

    switch(doing_step)
    {
    case DOING_STEP_NEAR_TO:
        {
            dest_x = item_x;
            dest_y = item_y;
            distance = (dest_x - x) * (dest_x - x) + (dest_y - y) * (dest_y - y);
            if(distance > PICKABLE_DISTANCE)
            {
                ret = FindCharacterStep(map_no, x, y, &dest_x, &dest_y, move_speed);
                switch(ret)
                {
                case STEP_ON_THE_WAY:
                    {
                        if(dest_x - x != 0 || dest_y - y != 0)
                            dir = approach_npc_dir(dest_x - x, dest_y - y);
                        
                        new_action = get_run_action(is_fight);
                        new_id = get_npc_file_id(file_index, new_action);
                        if(id != new_id)
                        {
                            LOCK_CHARACTER(npc_no);
                            game_npc[npc_no].x = dest_x;
                            game_npc[npc_no].y = dest_y;
                            game_npc[npc_no].dir = (UCHR) dir;
                            game_npc[npc_no].id = new_id;
                            dir_fast_loop_npc_frame(npc_no);
                            UNLOCK_CHARACTER(npc_no);
                        }
                        else
                        {
                            LOCK_CHARACTER(npc_no);
                            game_npc[npc_no].x = dest_x;
                            game_npc[npc_no].y = dest_y;
                            game_npc[npc_no].dir = (UCHR)dir;
                            dir_fast_loop_npc_frame(npc_no);
                            UNLOCK_CHARACTER(npc_no);
                        }
                        break;
                    }
                case STEP_ARRIVE:
                    {
                        LOCK_CHARACTER(npc_no);
                        game_npc[npc_no].x = dest_x;
                        game_npc[npc_no].y = dest_y;
                        dir_fast_loop_npc_frame(npc_no);
                        game_npc[npc_no].doing_step = DOING_STEP_PICK_ITEM;
                        UNLOCK_CHARACTER(npc_no);
                        break;
                    }
                case STEP_OBSTRUCT:
                case STEP_OUTSTRETCH:
                default:
                    {
                        LOCK_CHARACTER(npc_no);
                        game_npc[npc_no].dest_x = x;
                        game_npc[npc_no].dest_y = y;
                        dir_fast_loop_npc_frame(npc_no);
                        game_npc[npc_no].doing_kind = DOING_KIND_IDLE;
                        game_npc[npc_no].doing_step = 0;
                        UNLOCK_CHARACTER(npc_no);
                        break;
                    }
                }
            }
            else
            {
                LOCK_CHARACTER(npc_no);
                game_npc[npc_no].doing_step = DOING_STEP_PICK_ITEM;
                UNLOCK_CHARACTER(npc_no);
            }
            break;
        }
    case DOING_STEP_PICK_ITEM:
        {
            ITEM_ESSE   contain_ie;
            SLONG   pickup_success, game_item_index;

            
            LOCK_ITEM(0);
            contain_ie = catch_game_item_index(item_map_no, item_x, item_y, &game_item_index);
            UNLOCK_ITEM(0);
            
            if(is_valid_item(contain_ie.base))
            {
                if(hand_it == TRUE)
                {
                    LOCK_ITEM(0);
                    // Jack. [12:18,9/20/2002]
                    //del_game_item(item_map_no, item_x, item_y);
                    open_and_disappear_game_item(game_item_index, npc_no);
                    UNLOCK_ITEM(0);

                    LOCK_PLAYER(player_index);
                    set_player_mouse_item(player_index, contain_ie);
                    UNLOCK_PLAYER(player_index);

                    //for UI.
                    set_mouse_hand_item(&contain_ie);
                }
                else
                {
                    SLONG   room_index;

                    pickup_success = TRUE;
                    
                    LOCK_PLAYER(player_index);
                    room_index = find_player_bag_room(player_index);
                    UNLOCK_PLAYER(player_index);
                    
                    if(room_index >= 0)
                    {
                        LOCK_PLAYER(player_index);
                        set_player_bag_item(player_index, room_index, contain_ie);
                        UNLOCK_PLAYER(player_index);
                    }
                    else
                    {
                        game_chat.add(CHATEFF_RED, (USTR*)TEXTMSG_NOT_ENOUGH_BAG_SPACE);
                        pickup_success = FALSE;
                    }

                    if(pickup_success)
                    {
                        LOCK_ITEM(0);
                        // Jack. [12:19,9/20/2002]
                        //del_game_item(item_map_no, item_x, item_y);
                        open_and_disappear_game_item(game_item_index, npc_no);
                        UNLOCK_ITEM(0);
                    }
                }
            }

            LOCK_CHARACTER(npc_no);
            game_npc[npc_no].doing_kind = DOING_KIND_IDLE;
            game_npc[npc_no].doing_step = 0;
            UNLOCK_CHARACTER(npc_no);
        }
        break;
    }
    */
}


/******************************************************************************************************************/
/* PASSIVE DOING FUNCTIONS                                                                                        */
/******************************************************************************************************************/
//�Q��
SLONG   server_do_npc_beated(SLONG npc_no)
{
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
            break;        
        case NPC_KEY_FRAME_TAIL://�̫�V
            //�A�Ⱦ�����ai 
            //if(npc_no < 500)
            //    server_execute_npc_ai_after_beated(npc_no);
            //
            ret = ACTION_RETURN_OK;
            break;            
        case NPC_KEY_FRAME_NONE://�D����V
        case NPC_KEY_FRAME_HEAD://����V(�Ĥ@�V)
        case NPC_KEY_FRAME_BACK://���۴V
        default:
            break;    
    }
    return ret;

    // mark by lijun 2003-04-18
    /*
    enum
    {   
        DOING_STEP_BEATED_START     =   0,
        DOING_STEP_BEATED_RUNNING       =   1,
    };
    SLONG   doing_step, file_index;
    SLONG   new_action, new_id;
	SLONG	key_frame_type;

    LOCK_CHARACTER(npc_no);
    doing_step = GetCharacterDoingStep(npc_no);
    UNLOCK_CHARACTER(npc_no);
    switch(doing_step)
    {
    case DOING_STEP_BEATED_START:
        new_action = AC_BEATED;
		LOCK_CHARACTER(npc_no);
        file_index = GetCharacterFileIndex(npc_no);
        new_id = GetCharacterFileActionImageID(file_index, new_action);
        SetCharacterImageID(npc_no, new_id);
        DirHeadCharacterFrame(npc_no);
        SetCharacterDoingStep(npc_no, DOING_STEP_BEATED_RUNNING);
		UNLOCK_CHARACTER(npc_no);
        break;

    case DOING_STEP_BEATED_RUNNING:
		LOCK_CHARACTER(npc_no);
		key_frame_type = DirFastTailCharacterFrame(npc_no);
		UNLOCK_CHARACTER(npc_no);
		if(NPC_KEY_FRAME_TAIL == key_frame_type)
		{
			if(npc_no < 500)
			{			
				LOCK_CHARACTER(npc_no);
				SetCharacterDoingKindStep(npc_no, DOING_KIND_IDLE, 0);
				UNLOCK_CHARACTER(npc_no);
			}else
			{
				server_execute_npc_ai_after_beated(npc_no);
			}
		}
        break;
    }
    */    
}


//���`
SLONG   server_do_npc_dead(SLONG npc_no)
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
    SLONG   doing_step;
    SLONG   file_index, x, y, z;
    SLONG   beated_x, beated_y, dir;
    SLONG   dead_time;
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
                break;
            case NPC_KEY_FRAME_HALF://�����V
                break;
            case NPC_KEY_FRAME_TAIL://�̫�V
                LOCK_CHARACTER(npc_no);
                SetCharacterDoingStep(npc_no, DOING_STEP_DEAD_WAITING);
                server_process_npc_dead_operation(npc_no);
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
		dead_time = GetCharacterDeadTicks(npc_no);
		dead_time--;  // ���`�ɶ����p��
		if(dead_time <= 0)
		{
			if(npc_no >= 500)
			{
				SetCharacterDeadState(npc_no,NPC_DISAPPEAR);
				SetCharacterDeadTicks(npc_no,1200);
				SetCharacterDoingStep(npc_no, DOING_STEP_DEAD_DISAPPEAR);
			}
			else
			{
				SetCharacterDeadState(npc_no, NPC_LIVE);
				SetCharacterDeadTicks(npc_no, 0);
				SetCharacterDoingStep(npc_no, DOING_STEP_DEAD_PROCESS);
			}
		}	
		else
		{
			SetCharacterDeadTicks(npc_no, (SHINT)dead_time);
		}
        UNLOCK_CHARACTER(npc_no);
        break;
    case DOING_STEP_DEAD_DISAPPEAR://�������
        LOCK_CHARACTER(npc_no);
		dead_time = GetCharacterDeadTicks(npc_no);
		dead_time--;  // ���`�ɶ����p��
		if(dead_time <= 0)
		{
			SetCharacterDeadState(npc_no, NPC_LIVE);
			SetCharacterDoingStep(npc_no, DOING_STEP_DEAD_PROCESS);
		}		
		else
		{
			SetCharacterDeadTicks(npc_no, (SHINT)dead_time);
		}
        UNLOCK_CHARACTER(npc_no);
        break;

    case DOING_STEP_DEAD_PROCESS:
        //�o�q�u���A�Ⱦ��ݭn�B�z
		LOCK_CHARACTER(0);
		SetCharacterDoingStep(npc_no, DOING_STEP_DEAD_END);
		UNLOCK_CHARACTER(0);
        server_process_npc_dead_relive(npc_no);        
        break;
    case DOING_STEP_DEAD_END:
        // server do nothing ..
        ret = ACTION_RETURN_OK;
        break;
    }
    return ret;
    // mark by lijun 2003-04-17
    /*
    enum
    {   
        DOING_STEP_DEAD_START       =   0,  //���`�}�l
        DOING_STEP_DEAD_RUNNING         =   1,  //���`��
	    DOING_STEP_DEAD_WAITING			=	2,	//���ݫ������
	    DOING_STEP_DEAD_DISAPPEAR		=	4,	//�������
        DOING_STEP_DEAD_PROCESS         =   5,  //���`���B�z
        DOING_STEP_DEAD_END				=   6,  //���`END
    };
    SLONG   doing_step, file_index, new_action, new_id;
	SLONG	dead_time;

    LOCK_CHARACTER(npc_no);
    doing_step = GetCharacterDoingStep(npc_no);
    UNLOCK_CHARACTER(npc_no);

    switch(doing_step)
    {
    case DOING_STEP_DEAD_START:
        LOCK_CHARACTER(npc_no);
        file_index = GetCharacterFileIndex(npc_no);
        new_action = AC_FAINT;
        new_id = GetCharacterFileActionImageID(file_index, new_action);
        SetCharacterImageID(npc_no, new_id);
        DirHeadCharacterFrame(npc_no);
        SetCharacterDoingStep(npc_no, DOING_STEP_DEAD_RUNNING);
        UNLOCK_CHARACTER(npc_no);
        break;

    case DOING_STEP_DEAD_RUNNING:
        LOCK_CHARACTER(npc_no);
        if(NPC_KEY_FRAME_TAIL == DirFastTailCharacterFrame(npc_no))
        {
            SetCharacterDoingStep(npc_no, DOING_STEP_DEAD_WAITING);
            server_process_npc_dead_operation(npc_no);
        }
        UNLOCK_CHARACTER(npc_no);
        break;

	case DOING_STEP_DEAD_WAITING:
        LOCK_CHARACTER(npc_no);
		dead_time = GetCharacterDeadTicks(npc_no);
		dead_time--;  // ���`�ɶ����p��
		if(dead_time <= 0)
		{
			if(npc_no >= 500)
			{
				SetCharacterDeadState(npc_no,NPC_DISAPPEAR);
				SetCharacterDeadTicks(npc_no,1200);
				SetCharacterDoingStep(npc_no, DOING_STEP_DEAD_DISAPPEAR);
			}
			else
			{
				SetCharacterDeadState(npc_no, NPC_LIVE);
				SetCharacterDeadTicks(npc_no, 0);
				SetCharacterDoingStep(npc_no, DOING_STEP_DEAD_PROCESS);
			}
		}	
		else
		{
			SetCharacterDeadTicks(npc_no, (SHINT)dead_time);
		}
        UNLOCK_CHARACTER(npc_no);
		break;

	case DOING_STEP_DEAD_DISAPPEAR:
        LOCK_CHARACTER(npc_no);
		dead_time = GetCharacterDeadTicks(npc_no);
		dead_time--;  // ���`�ɶ����p��
		if(dead_time <= 0)
		{
			SetCharacterDeadState(npc_no, NPC_LIVE);
			SetCharacterDoingStep(npc_no, DOING_STEP_DEAD_PROCESS);
		}		
		else
		{
			SetCharacterDeadTicks(npc_no, (SHINT)dead_time);
		}
        UNLOCK_CHARACTER(npc_no);
		break;

    case DOING_STEP_DEAD_PROCESS:
		LOCK_CHARACTER(0);
		SetCharacterDoingStep(npc_no, DOING_STEP_DEAD_END);
		UNLOCK_CHARACTER(0);
        server_process_npc_dead_relive(npc_no);
        break;
		
	case DOING_STEP_DEAD_END:
		//do nothing.
		break;
    }
    */    
}
//----
//�Q����
//----
SLONG   server_do_npc_down_and_out(SLONG npc_no)
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
        UNLOCK_CHARACTER(npc_no);
        switch (MinKind_NpcActionOneTime(npc_no, AC_FAINT))
        {
        case NPC_KEY_FRAME_NONE://�D����V
            break;
        case NPC_KEY_FRAME_HEAD://����V(�Ĥ@�V)
            break;
        case NPC_KEY_FRAME_HALF://�����V
            break;        
        case NPC_KEY_FRAME_TAIL://�̫�V
            LOCK_CHARACTER(npc_no);
            SetCharacterDoingStep(npc_no, DOING_STEP_PANT);
            SetCharacterPantTicks(npc_no, 5);  //0.25��ݮ�
            UNLOCK_CHARACTER(npc_no);
            break;
        }
        //
        break;
    case DOING_STEP_PANT://�Q���˰��b�a�O�W�@�q�ɶ�
        pant_ticks = GetCharacterPantTicks(npc_no);
        if(--pant_ticks <= 0)
		{
			//server_execute_npc_ai_after_beated(npc_no);
			//
			ret = ACTION_RETURN_OK;
		}
        else
		{
            SetCharacterPantTicks(npc_no, pant_ticks);
		}
        break;
    }
    return ret;
    // mark by lijun 2003-04-18
    /*
    enum
    {   
        DOING_STEP_DOWN_AND_OUT_START   =   0,  //�}�l�Q����
        DOING_STEP_DOWN_AND_OUT_RUNNING     =   1,  //�Q���ˤ�
        DOING_STEP_PANT                     =   2,  //�ݮ��@�q�ɶ�
    };
    SLONG   doing_step, file_index, new_action, new_id;
    SLONG   pant_ticks, need_ai;

	need_ai = 0;
    LOCK_CHARACTER(npc_no);
    doing_step = GetCharacterDoingStep(npc_no);
    switch(doing_step)
    {
    case DOING_STEP_DOWN_AND_OUT_START:
        new_action = AC_FAINT;
        file_index = GetCharacterFileIndex(npc_no);
        new_id = GetCharacterFileActionImageID(file_index, new_action);
        SetCharacterImageID(npc_no, new_id);
        DirHeadCharacterFrame(npc_no);
        SetCharacterDoingStep(npc_no, DOING_STEP_DOWN_AND_OUT_RUNNING);
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
		{
			need_ai = 1;
		}
        else
		{
            SetCharacterPantTicks(npc_no, pant_ticks);
		}
        break;
    }
    UNLOCK_CHARACTER(npc_no);

	if(need_ai)
	{
		server_execute_npc_ai_after_beated(npc_no);
	}
    */	
}

//----
//����
//----
SLONG   server_do_npc_defence(SLONG npc_no)
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
    // mark by lijun 2003-04-18
    /*
    enum
    {   
        DOING_STEP_START_DEFENCE        =   0,
        DOING_STEP_DEFENCE_RUNNING      =   1,
    };
    SLONG   doing_step, file_index;
    SLONG   new_action, new_id;

    LOCK_CHARACTER(npc_no);
    doing_step = GetCharacterDoingStep(npc_no);
    switch(doing_step)
    {
    case DOING_STEP_START_DEFENCE:
        new_action = AC_WARD;
        file_index = GetCharacterFileIndex(npc_no);
        new_id = GetCharacterFileActionImageID(file_index, new_action);
        SetCharacterImageID(npc_no, new_id);
        DirHeadCharacterFrame(npc_no);
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


//�Q����
SLONG   server_do_npc_defenced(SLONG npc_no)
{
    SLONG ret = ACTION_RETURN_PROC;
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
    // mark by lijun 2003-04-18
    /*
    enum
    {   
        DOING_STEP_START_DEFENCED       =   0,
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
/* PLAYER EMOTION FUNCTIONS                                                                                       */
/******************************************************************************************************************/
/*
//���ʧ@: �w�I
SLONG   server_do_npc_cheer(SLONG npc_no)
{
    SLONG   ret = ACTION_RETURN_PROC;
    if (NPC_KEY_FRAME_TAIL == MinKind_NpcActionOneTime(npc_no, AC_CHEER))
    {
        LOCK_CHARACTER(npc_no);
        SetCharacterDoingKindStep(npc_no, DOING_KIND_IDLE, 0);
        UNLOCK_CHARACTER(npc_no);
        //
        ret = ACTION_RETURN_OK;
    }
    return ret;
    // mark by lijun 2003-04-18
    /----------------------------------------------------------------------
    enum
    {   
        DOING_STEP_START_CHEER      =   0,
        DOING_STEP_CHEER_RUNNING        =   1,
    };
    SLONG   doing_step, file_index;
    SLONG   new_action, new_id;

    LOCK_CHARACTER(npc_no);
    doing_step = GetCharacterDoingStep(npc_no);
    switch(doing_step)
    {
    case DOING_STEP_START_CHEER:
        new_action = AC_CHEER;
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

//���ʧ@: �ͮ�
SLONG   server_do_npc_angry(SLONG npc_no)
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
    // mark by lijun 2003-04-18
    /*
    enum
    {   
        DOING_STEP_START_ANGRY      =   0,
        DOING_STEP_ANGRY_RUNNING        =   1,
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


//���ʧ@: ����
SLONG   server_do_npc_beckon(SLONG npc_no)
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
    // mark by lijun 2003-04-18
    /*
    enum
    {   
        DOING_STEP_START_BECKON     =   0,
        DOING_STEP_BECKON_RUNNING       =   1,
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
//���ʧ@: �D�R
SLONG   server_do_npc_court(SLONG npc_no)
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
    // mark by lijun 2003-04-18
    /----------------------------------------------------------------------
    enum
    {   
        DOING_STEP_START_COURT      =   0,
        DOING_STEP_COURT_RUNNING        =   1,
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

//���ʧ@: �w��
SLONG   server_do_npc_faint(SLONG npc_no)
{
    SLONG   ret = ACTION_RETURN_PROC;
    if (NPC_KEY_FRAME_TAIL == MinKind_NpcActionOneTime(npc_no, AC_FAINT))
    {
        LOCK_CHARACTER(npc_no);
        SetCharacterDoingKindStep(npc_no, DOING_KIND_IDLE, 0);
        UNLOCK_CHARACTER(npc_no);
        //
        ret = ACTION_RETURN_OK;
    }
    return ret;
    // mark by lijun 2003-04-18
    /*
    enum
    {   
        DOING_STEP_START_FAINT      =   0,
        DOING_STEP_FAINT_RUNNING        =   1,
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


//���ʧ@: ����
SLONG   server_do_npc_say_no(SLONG npc_no)
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
    // mark by lijun 2003-04-18
    /*
    enum
    {   DOING_STEP_START_SAY_NO     =   0,
    DOING_STEP_SAYING_NO            =   1,
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



//���ʧ@: ���`
SLONG   server_do_npc_bow(SLONG npc_no)
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
    {   
        DOING_STEP_START_BOW        =   0,
        DOING_STEP_BOW_RUNNING          =   1,
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


//���ʧ@: �ӧQ
SLONG   server_do_npc_win(SLONG npc_no)
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
    // mark by lijun 2003-04-18
    /*
    enum
    {   
        DOING_STEP_START_WIN        =   0,
        DOING_STEP_WIN_RUNNING          =   1,
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


//���ʧ@: ����
SLONG   server_do_npc_swash(SLONG npc_no)
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
    // mark by lijun 2003-04-18
    /*
    enum
    {  
        DOING_STEP_START_SWASH      =   0,
        DOING_STEP_SWASH_RUNNING        =   1,
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


//���ʧ@: �W�O
SLONG   server_do_npc_xxpower(SLONG npc_no)
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
    // mark by lijun 2003-04-18              
    /*
    enum
    {  
        DOING_STEP_START_XXPOWER    =   0,
        DOING_STEP_XXPOWER_RUNNING      =   1,
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


//���ʧ@: �Q��
SLONG   server_do_npc_xxbeated(SLONG npc_no)
{
    SLONG   ret = ACTION_RETURN_PROC;
    if (NPC_KEY_FRAME_TAIL == MinKind_NpcActionOneTime(npc_no, AC_BEATED))
    {
        LOCK_CHARACTER(npc_no);
        SetCharacterDoingKindStep(npc_no, DOING_KIND_IDLE, 0);
        UNLOCK_CHARACTER(npc_no);
        //
        ret = ACTION_RETURN_OK;
    }                          
    return ret;                  
    // mark by lijun 2003-04-18
    /*
    enum
    {   DOING_STEP_START_XXBEATED   =   0,
    DOING_STEP_XXBEATED_RUNNING     =   1,
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
/*
SLONG	server_do_npc_fight_idle(SLONG npc_no)
{    
    server_do_npc_idle( npc_no);
    if (npc_no >= 500)
    {
        server_execute_npc_ai_when_move(npc_no);
    }    
    return ACTION_RETURN_PROC;
    // mark by lijun 2003-04-18
    /------------------------------------------------------------------------
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
		if((npc_no >= 500) && (NPC_KEY_FRAME_HEAD == key_frame_type))
		{
			server_execute_npc_ai_when_move(npc_no);
		}
    }
    /------------------------------------------------------------------------
}
*/
/*
// �԰�
SLONG	server_do_npc_fight_gad(SLONG npc_no)
{    
    enum
    {
        DOING_STEP_IDLE     =   0,
        DOING_STEP_MOVE_TO  =   1,
		//
		GAD_RAND_X		    =   300,    //�H�����ʪ��d��
		GAD_RAND_Y			=   250,
		GAD_RAND_TICKS		=   400,        
    };
    SLONG   doing_step;
    SLONG   dest_x, dest_y, dest_z;
    SLONG   is_fight;
    SLONG   x,y,z;
    SLONG   new_action;
    SLONG   total_ticks,ticks;
    SLONG   temp_x,temp_y;
    //
    LOCK_CHARACTER(npc_no);
    doing_step = GetCharacterDoingStep(npc_no);
    GetCharacterPosition(npc_no,&x,&y,&z);
	GetCharacterDestPosition(npc_no, &dest_x, &dest_y, &dest_z);
    total_ticks = GetCharacterGadTotalTicks(npc_no);
    ticks = GetCharacterGadTicks(npc_no);	
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
        ticks ++;
        //
        LOCK_CHARACTER(npc_no);
        SetCharacterGadTicks(npc_no, ticks);
        UNLOCK_CHARACTER(npc_no);
        //
        if(ticks < total_ticks)
        {
            if(npc_no >= 500)
            {
                server_execute_npc_ai_when_move(npc_no);
            }
        }
        else
        {
            //�L�@�q�ɶ��ݭn��B�ʤ@�U�U..
            temp_x = x + ( system_rand() % GAD_RAND_X ) * ( 1 - (system_rand() % 2) * 2 );
            temp_y = y + ( system_rand() % GAD_RAND_Y ) * ( 1 - (system_rand() % 2) * 2 );

            {
                LOCK_CHARACTER(npc_no);
                ServerChangeCharacterDoing(npc_no, DOING_KIND_FIGHT_GAD, DOING_STEP_MOVE_TO, temp_x, temp_y, total_ticks, ticks, 0);
                UNLOCK_CHARACTER(npc_no);
            }				
            //ServerSendChangeNpcDoing(npc_no, DOING_KIND_FIGHT_GAD, DOING_STEP_MOVE_TO,
            //    temp_x, temp_y, total_ticks, ticks, 0);					
        }
        //
        break;
    case DOING_STEP_MOVE_TO:
        switch (MinKind_NpcMoveFindPath(npc_no,dest_x, dest_y))
        {
        case NPC_MOVE_MOVEING:      //npc���ʦb���ʹL�{��
            server_execute_npc_ai_when_move(npc_no);
            break;    
        case NPC_MOVE_ARRIVE:       //npc���ʨ�F�F�ؼ�
        case NPC_MOVE_CANT_ARRIVE:  //npc���ʤ����F
            total_ticks = GAD_RAND_TICKS + system_rand() % GAD_RAND_TICKS; 
            ticks = 0;
            {
                temp_x = x;
                temp_y = y;
                LOCK_CHARACTER(npc_no);
                ServerChangeCharacterDoing(npc_no, DOING_KIND_FIGHT_GAD, DOING_STEP_IDLE, temp_x, temp_y, total_ticks, ticks, 0);
                UNLOCK_CHARACTER(npc_no);
            }
            //ServerSendChangeNpcDoing(npc_no, DOING_KIND_FIGHT_GAD, DOING_STEP_IDLE,
            //						 temp_x, temp_y, total_ticks, ticks, 0);                    
            break;
        }
        break;
    default:
        break;
    }
    return ACTION_RETURN_PROC;
    //mark by lijun 2003-04-18
    /----------------------------------------------------------------------
    enum    
    {   
		DOING_STEP_IDLE		=   0,
		DOING_STEP_MOVE_TO  =   1,
		//
		GAD_RAND_X		    =   300,
		GAD_RAND_Y			=   250,
		GAD_RAND_TICKS		=   400,
    };
    SLONG   doing_step;
    SLONG   total_ticks, ticks;
    SLONG   x, y, z;
    SLONG   dest_x, dest_y, dest_z;
    SLONG   temp_x, temp_y;
    SLONG   move_speed;
    SLONG   file_index, id;
    SLONG   new_action, new_id;
    SLONG   dir, is_fight;
    SLONG   ret, key_frame_type;


    LOCK_CHARACTER(npc_no);
	doing_step = GetCharacterDoingStep(npc_no);    
    total_ticks = GetCharacterGadTotalTicks(npc_no);
    ticks = GetCharacterGadTicks(npc_no);
    GetCharacterPosition(npc_no,&x,&y,&z);    
    GetCharacterDestPosition(npc_no,&dest_x,&dest_y,&dest_z);        
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
            ticks ++;
            if(ticks < total_ticks)
            {
				new_action = GetIdleAction(is_fight);
                new_id = GetCharacterFileActionImageID(file_index, new_action);
                if(new_id != id)
                {
                    LOCK_CHARACTER(npc_no);
                    SetCharacterImageID(npc_no, new_id);
                    DirHeadCharacterFrame(npc_no);					
					SetCharacterGadTicks(npc_no,ticks);                    
                    UNLOCK_CHARACTER(npc_no);
                }
                else
                {
                    LOCK_CHARACTER(npc_no);
					SetCharacterGadTicks(npc_no, ticks);                    
					key_frame_type = DirFastKeyLoopCharacterFrame(npc_no);
                    UNLOCK_CHARACTER(npc_no);
                    if((npc_no >= 500)&&(NPC_KEY_FRAME_HEAD == key_frame_type))
					{
						server_execute_npc_ai_when_move(npc_no);
					}
                }
            }
            else
            {
                temp_x = x + ( system_rand() % GAD_RAND_X ) * ( 1 - (system_rand() % 2) * 2 );
                temp_y = y + ( system_rand() % GAD_RAND_Y ) * ( 1 - (system_rand() % 2) * 2 );
                
                {
                    LOCK_CHARACTER(npc_no);
					ServerChangeCharacterDoing(npc_no, DOING_KIND_FIGHT_GAD, DOING_STEP_MOVE_TO, temp_x, temp_y, total_ticks, ticks, 0);
                    UNLOCK_CHARACTER(npc_no);
                }				
				ServerSendChangeNpcDoing(npc_no, DOING_KIND_FIGHT_GAD, DOING_STEP_MOVE_TO,
										 temp_x, temp_y, total_ticks, ticks, 0);					
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
                {
                    new_action = GetRunAction(is_fight);
                    new_id = GetCharacterFileActionImageID(file_index, new_action);
                    if(id != new_id)
                    {
                        LOCK_CHARACTER(npc_no);
						SetCharacterPosition(npc_no, dest_x, dest_y, 0);                        
						SetCharacterDir(npc_no, (UCHR) dir);
						SetCharacterImageID(npc_no, new_id);
                        DirHeadCharacterFrame(npc_no);
                        UNLOCK_CHARACTER(npc_no);
                    }
                    else
                    {
                        LOCK_CHARACTER(npc_no);
                        SetCharacterPosition(npc_no, dest_x, dest_y, 0);                        
						SetCharacterDir(npc_no, (UCHR) dir);
                        key_frame_type = DirFastKeyLoopCharacterFrame(npc_no);
                        UNLOCK_CHARACTER(npc_no);
						if((npc_no >= 500) && (NPC_KEY_FRAME_HEAD == key_frame_type))
						{
							server_execute_npc_ai_when_move(npc_no);
						}
                    }

                    break;
                }
            case STEP_ARRIVE:
            case STEP_OBSTRUCT:
            case STEP_OUTSTRETCH:
            default:
                {
                    total_ticks = GAD_RAND_TICKS + system_rand() % GAD_RAND_TICKS; 
                    ticks = 0;
                    {
						temp_x = x;
						temp_y = y;
                        LOCK_CHARACTER(npc_no);
						ServerChangeCharacterDoing(npc_no, DOING_KIND_FIGHT_GAD, DOING_STEP_IDLE, temp_x, temp_y, total_ticks, ticks, 0);
                        UNLOCK_CHARACTER(npc_no);
                    }
					//ServerSendChangeNpcDoing(npc_no, DOING_KIND_FIGHT_GAD, DOING_STEP_IDLE,
					//						 temp_x, temp_y, total_ticks, ticks, 0);                    
                    break;
                }
            }
        }
        break;
    default:
        break;
    } 
    /----------------------------------------------------------------------
}
*/
//----
//  ����
//----
SLONG	server_do_npc_fight_patrol(SLONG npc_no)
{
    return ACTION_RETURN_PROC;
    // mark by lijun 2003-04-18
    /*
    enum
    {   
        DOING_STEP_MOVE_TO          =   0,
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
				//if(dest_x - x != 0 || dest_y - y != 0)
				//	dir = approach_npc_dir(dest_x - x, dest_y - y);
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
				//if(orig_x - x != 0 || orig_y - y != 0)
				//	dir = approach_npc_dir(orig_x - x, orig_y - y);
				
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
    */    
}


/************************************************************************************************************/
/* ���vNPC���ư�����                                                                                        */
/************************************************************************************************************/
//���WNPC�b��a���ݾ�
SLONG	server_do_sea_npc_idle(SLONG npc_no)
{
    SLONG       new_action, new_id;
    SLONG       is_fight, file_index;

    LOCK_CHARACTER(npc_no);
    is_fight = IsCharacterOnFightState(npc_no);
	file_index = GetCharacterFileIndex(npc_no);
    new_action = GetOnSeaIdleAction(is_fight);
    new_id = GetSeaCharacterFileActionImageID(file_index, new_action);
	SetCharacterImageID(npc_no, new_id);
    UNLOCK_CHARACTER(npc_no);
    //
    return ACTION_RETURN_PROC;
}


//���WNPC����ت��a�I(�������v�T)
SLONG	server_do_sea_npc_sail_to(SLONG npc_no)
{
    enum 
    {   DOING_STEP_MOVE_TO  =   0,
       DOING_STEP_ARRIVE   =   1,
       DOING_STEP_STOP     =   2,
    };
    SLONG   doing_step;
    SLONG   file_index;
    SLONG   new_id, new_action;
    SLONG   dir, id,new_dir;
    SLONG   x, y, z, dest_x, dest_y, dest_z;
    SLONG   move_speed;
    SLONG   is_fight, foot_state, is_defence;
    //�M����������ƾ�
    FLOAT   Ax;				    //�x�b�W���[�t��
    FLOAT   Ay;				    //�y�b�W���[�t��
    FLOAT   Speedx;			    //��bx�b�W���t��(�N�O��bx�b�W,���ɶ����첾)
    FLOAT   Speedy;			    //��by�b�W���t��(�N�O��bx�b�W,���ɶ����첾)
    FLOAT   BoatWinUseRate;		//��ﭷ���ϥβv(�M��t�צ����Y) (�`��)
    FLOAT   BoatWeight;			//����q(�M����O�����Y)
    SLONG	Rotate;				//����ਤ��(��ਤ)
    FLOAT   BoatBaseSpeed;		//��򥻳t��
    FLOAT   SpeedAddLeftx;	    //�ξl�O�s�t�׭p��᪺�l�� x
    FLOAT   SpeedAddLefty;	    //�ξl�O�s�t�׭p��᪺�l�� y
    FLOAT   BoatDir[3];		    //���V
    FLOAT   BoatForce[3];       //����쪺���O
    FLOAT   resist[3];          //����쪺���O
    SLONG   lspeedx,lspeedy;
    SLONG   lWindDir;
    SLONG   lWindForce;
    SLONG   degree_dir;
    float   base_speed_x,base_speed_y;
    float   t_speed_x,t_speed_y;
    float   cosq;
    float   tag[3];
    float   temp[3];
    FLOAT   speed_ver[3];
    FLOAT   mod;
    SLONG   result;
	//

    //�����onpc���ƾ�
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
    //
    new_action = GetOnSeaMoveAction(is_fight);
    new_id = GetSeaCharacterFileActionImageID(file_index, new_action);
    //
    //����npc�����ɮ�
    if(id != new_id)
    {
		SetCharacterImageID(npc_no, new_id);
        DirHeadSeaCharacterFrame(npc_no, dir);
    }
	Speedx = (FLOAT)(GetCharacterShipSpeedX(npc_no) * 1.0 / BOAT_SPEED_ACCURACY);
	Speedy = (FLOAT)(GetCharacterShipSpeedY(npc_no) * 1.0 / BOAT_SPEED_ACCURACY);
	BoatWinUseRate  =   (FLOAT)GetCharacterShipSailSize(npc_no);	//��ﭷ���ϥβv(�M��t�צ����Y) (�`��)
    BoatWeight      =   (FLOAT)GetCharacterShipWeight(npc_no);			//����q(�M����O�����Y)
    Rotate          =   GetCharacterShipTurn(npc_no);				//����ਤ��(��ਤ)
    BoatBaseSpeed   =   (FLOAT)move_speed;		//��򥻳t��
	degree_dir = GetCharacterShipDegreeDir(npc_no);
	ShipDegreeDirToVector(degree_dir, BoatDir);    //���V
    UNLOCK_CHARACTER(npc_no);


	//���o������V�M�j�p
    server_get_zone_weather_wind_for_boat(&lWindDir,&lWindForce);

    switch(doing_step)
    {
    case DOING_STEP_MOVE_TO://���ʨ�ؼЦa�I���L�{
		{
			//�[�t�L�{
			//���`�ھڭ��O����p
			//--AI�B�z,,�B�z���V..�O�_PARK���лx
			tag[0] = (FLOAT)( dest_x - x );
			tag[1] = (FLOAT)( dest_y - y );
			tag[2] = 0.0f;
			VectorNormal( tag );
			//
			ShipDegreeDirToVector(degree_dir, BoatDir);
			//
			cosq = VectorDotProduct( tag,BoatDir );
			if( cosq < cos(Rotate * PI * 2 / MAX_BOAT_DIR) )
			{
				VectorCrossProduct(tag, BoatDir, temp);
				if( temp[2] < 0 )
					degree_dir += Rotate;
				else
					degree_dir -= Rotate;
				if( degree_dir >= MAX_BOAT_DIR )
				{
					degree_dir = degree_dir % MAX_BOAT_DIR;
				}
				if( degree_dir < 0 )
				{
					degree_dir = (degree_dir + MAX_BOAT_DIR * 100) % MAX_BOAT_DIR;
				}
				ShipDegreeDirToVector(degree_dir, BoatDir);
			}
			else
			{
				BoatDir[0] = tag[0];
				BoatDir[1] = tag[1];
				BoatDir[2] = tag[2];
				/* ??? ask dixon ???
				tag[0] = BoatDir[0];
				tag[1] = BoatDir[1];
				tag[2] = BoatDir[2];
				*/
			}

			//�p�G�t�ת���V�M���V���I��
			speed_ver[0] = Speedx;
			speed_ver[1] = Speedy;
			speed_ver[2] = 0.0f;
			if( VectorDotProduct( speed_ver,BoatDir ) > 0 )
			{
				mod =(FLOAT)(  sqrt(Speedx*Speedx+Speedy*Speedy) );
				Speedx = BoatDir[0] * mod;
				Speedy = BoatDir[1] * mod;
			}

			//
			//..����`���ʹL�{
			// 1 �ھڭ��O�p���[�t��
			ShipWindDirToForceVector(degree_dir, lWindDir, BoatForce);
			BoatForce[0] = BoatForce[0] * BoatWinUseRate * lWindForce / 100;
			BoatForce[1] = BoatForce[1] * BoatWinUseRate * lWindForce/ 100;			

			// 2 �ھڳt��,���q�p�����O
			ComputeSeaCharacterSailResistance(BoatWeight,Speedx,Speedy,BoatDir,resist);

			// 3 ���o��{�b�u�����[�t��
			Ax = BoatForce[0]+resist[0];
			Ay = BoatForce[1]+resist[1];

			// 4 �ھڭ�Ӫ��t��,�[�t��,�򥻳t�׭p���u���t��,�W�����ʳѤU���B�I�t��
			Speedx += Ax;
			Speedy += Ay;
			Speedx = float_to_precision_10_float(Speedx);
			Speedy = float_to_precision_10_float(Speedy);

			// �p���򥻳t��
			base_speed_x = (BoatDir[0] * BoatBaseSpeed);
			base_speed_y = (BoatDir[1] * BoatBaseSpeed);
			t_speed_x = (Speedx+base_speed_x);
			t_speed_y = (Speedy+base_speed_y);
			//
			lspeedx = (SLONG)(t_speed_x);
			lspeedy = (SLONG)(t_speed_y);
			// 5 ���ʲ��s����m
			x += lspeedx;
			y += lspeedy;
			// 6 �O�d�ѤU���B�I�l��
			SpeedAddLeftx = t_speed_x-lspeedx;
			SpeedAddLefty = t_speed_y-lspeedy;
			Speedx += SpeedAddLeftx;
			Speedy += SpeedAddLefty;
			//��t����L�{
			//
			new_dir = ApproachSeaCharacterDir( BoatDir );

			//�N�ݭn�O�d���s�t�ګO�d�_��
			LOCK_CHARACTER(npc_no);
			if( dir != new_dir)	//����npc����V
			{
				SetCharacterDir(npc_no, new_dir);
				DirHeadSeaCharacterFrame(npc_no, new_dir);
			}
			UNLOCK_CHARACTER(npc_no);

			//�P�_��ؼ��I�O�_����
			LOCK_MAPMASK(0);
			result = IsPixelMaskStop(x, y);
			UNLOCK_MAPMASK(0);
			if( TRUE == result )
			{
				//�I�˪��ɳt���ܬ�0
				Speedx = (-1* Speedx);
				Speedy = (-1* Speedy);
				//
				SpeedAddLeftx = 0.0f;
				SpeedAddLefty = 0.0f;
				//
				//�I�쪺�O����
				LOCK_CHARACTER(npc_no);
				SetCharacterShipSpeedX(npc_no, (SLONG)(Speedx*BOAT_SPEED_ACCURACY));
				SetCharacterShipSpeedY(npc_no, (SLONG)(Speedy*BOAT_SPEED_ACCURACY));
				SetCharacterShipDegreeDir(npc_no, degree_dir);

				//�P�_�ت��a�O�_��F
				//�p�G���V�O���V�ؼЪ�...���N��ܨ�F�F.!!!
				if( ( tag[0] == BoatDir[0] ) &&
					( tag[1] == BoatDir[1] )   )
				{
					SetCharacterDoingStep(npc_no, DOING_STEP_STOP);
				}
				UNLOCK_CHARACTER(npc_no);
			}
			else
			{
				// 1. �O�d��e���y��
				//
				LOCK_CHARACTER(npc_no);
				SetCharacterPosition(npc_no, x, y, z);
				SetCharacterShipSpeedX(npc_no, (SLONG)(Speedx*BOAT_SPEED_ACCURACY));
				SetCharacterShipSpeedY(npc_no, (SLONG)(Speedy*BOAT_SPEED_ACCURACY));
				SetCharacterShipDegreeDir(npc_no, degree_dir);

				//�P�_�O�_��F�ؼЦa�I
				//�p�G���V�O���V�ؼЪ�...���N��ܨ�F�F.!!!
				if( ( tag[0] == BoatDir[0] ) &&
					( tag[1] == BoatDir[1] )   )
				{
					if(( abs( x - dest_x) <= abs(lspeedx)+1 ) && ( abs( y - dest_y) <= abs(lspeedy)+1 ) )
					{
						SetCharacterDoingStep(npc_no, DOING_STEP_ARRIVE);
					}
				}
				UNLOCK_CHARACTER(npc_no);
			}
		}		
		/*
		if(npc_no==0)
		{			
static	unsigned	long	step_count;
		log_error(1, "[%d] x:%d, y:%d, degree_dir:%d, speedx:%d, speedy:%d", 
			step_count++,
			CharacterInfo[npc_no].Position.lX , 
			CharacterInfo[npc_no].Position.lY ,
			CharacterInfo[npc_no].Position.BoatDir,
			CharacterInfo[npc_no].Position.fSpeedX,
			CharacterInfo[npc_no].Position.fSpeedY
			);
		}
		*/
        break;

    case DOING_STEP_ARRIVE:
        LOCK_CHARACTER(npc_no);
		SetCharacterPosition(npc_no, x, y, z);
        DirFastLoopSeaCharacterFrame(npc_no);
		SetCharacterDoingKindStep(npc_no, DOING_KIND_SEA_IDLE, 0);
        UNLOCK_CHARACTER(npc_no);
        break;


    case DOING_STEP_STOP:
        LOCK_CHARACTER(npc_no);
        DirFastLoopSeaCharacterFrame(npc_no);
		SetCharacterDoingKindStep(npc_no, DOING_KIND_SEA_IDLE, 0);
        UNLOCK_CHARACTER(npc_no);
        break;
    }
    return ACTION_RETURN_PROC;    
}


//���WNPC�樫��ت��a�I(���������v�T)
SLONG	server_do_sea_npc_walk_to(SLONG npc_no)
{
    static  FLOAT   s_rotate=(FLOAT)(PI/16);
    enum 
    {   DOING_STEP_MOVE_TO  =   0,
    };
    //
    SLONG   doing_step;
    SLONG   file_index;
    SLONG   new_id, new_action;
    SLONG   dir, id, new_dir, degree_dir;
    SLONG   x, y, z, dest_x, dest_y, dest_z;
    SLONG   move_speed;
    SLONG   ret;
    SLONG   is_fight, foot_state, is_defence;
    //
    FLOAT   BoatDir[3];
    FLOAT   tag[3],temp[3];
    SLONG	Rotate;
    FLOAT   cosq;

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
	//
    Rotate = GetCharacterShipTurn(npc_no);		//����ਤ��(��ਤ) 
	degree_dir = GetCharacterShipDegreeDir(npc_no);
	ShipDegreeDirToVector(degree_dir, BoatDir);    //���V
    UNLOCK_CHARACTER(npc_no);
    //

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
                    //NPC���ਭ���L�{ ------------------------------------------
                    tag[0] = (FLOAT)( dest_x - x );
                    tag[1] = (FLOAT)( dest_y - y );
                    tag[2] = 0.0f;
                    VectorNormal( tag );
                    cosq = VectorDotProduct( tag, BoatDir );
                    if( cosq < cos(s_rotate) )
                    {
                        VectorCrossProduct( tag, BoatDir, temp );
                        if( temp[2] < 0 )
						{
							degree_dir += Rotate;
							if(degree_dir >= MAX_BOAT_DIR)
							{
								degree_dir -= MAX_BOAT_DIR;
							}
						}
                        else
						{
							degree_dir -= Rotate;
							if(degree_dir < 0)
							{
								degree_dir += MAX_BOAT_DIR;
							}
						}

						//���s��o���V
						ShipDegreeDirToVector(degree_dir, BoatDir);
                    }
                    else
                    {
                        tag[0] = BoatDir[0];
                        tag[1] = BoatDir[1];
                        tag[2] = BoatDir[2];
                    }

                    //
                    new_dir = ApproachSeaCharacterDir(BoatDir);
                    new_action = GetOnSeaMoveAction(is_fight);
                    new_id = GetSeaCharacterFileActionImageID(file_index, new_action);
                    //
                    LOCK_CHARACTER(npc_no);
					SetCharacterDir(npc_no, new_dir);
					SetCharacterImageID(npc_no, new_id);
                    if( new_dir != dir )
					{
                        DirHeadSeaCharacterFrame(npc_no,new_dir);
					}
                    if( ( BoatDir[0] == tag[0] ) && 
                        ( BoatDir[1] == tag[1] )   )
                    {
						SetCharacterPosition(npc_no, dest_x, dest_y, dest_z);
                        DirFastLoopSeaCharacterFrame(npc_no);
                    }
					SetCharacterShipDegreeDir(npc_no, degree_dir);
                    UNLOCK_CHARACTER(npc_no);
                }
				break;

            case STEP_ARRIVE:
                LOCK_CHARACTER(npc_no);
				SetCharacterPosition(npc_no, dest_x, dest_y, dest_z);
                DirFastLoopCharacterFrame(npc_no);
				SetCharacterDoingKindStep(npc_no, DOING_KIND_SEA_IDLE, 0);
                UNLOCK_CHARACTER(npc_no);
                break;

            case STEP_OBSTRUCT:
            case STEP_OUTSTRETCH:
            default:
                LOCK_CHARACTER(npc_no);
				SetCharacterPosition(npc_no, x, y, z);
                DirFastLoopCharacterFrame(npc_no);
				SetCharacterDoingKindStep(npc_no, DOING_KIND_SEA_IDLE, 0);
                UNLOCK_CHARACTER(npc_no);
                break;
            }
        }
		break;

	default:
		break;
    }
    return ACTION_RETURN_PROC;    
}

//----
//  �q��!!!! ��npc�԰��ʵe������
//          1.�ھ�skill���Ѽ�,,�M�w�ʵe�����񦸼�
//          2.�b�C�����ʵe���񪺤����V����k�N�ե�...�p�G������
//----
SLONG   server_do_npc_fight_action(SLONG npc_no)
{
    SLONG   fight_ticks;
    SLONG   magic_index;
    SLONG   x, y, z;
    SLONG   dest_x,dest_y,dest_z;
    SLONG   dest_no;
    SLONG   dir;
    SLONG   ret = ACTION_RETURN_PROC;
    //
    LOCK_CHARACTER(npc_no);
    magic_index = GetCharacterDoingMagic(npc_no);
    dest_no = GetCharacterDestID(npc_no);    
    GetCharacterPosition(npc_no, &x, &y, &z);    
    GetCharacterDestPosition(npc_no, &dest_x, &dest_y, &dest_z);
    UNLOCK_CHARACTER(npc_no);
    //
    if (dest_no >=0 )
    {
        LOCK_CHARACTER(dest_no);
        GetCharacterPosition(dest_no, &dest_x, &dest_y, &dest_z);
        UNLOCK_CHARACTER(dest_no);
    }
    //1.����k�N����ʵe
    //2.�b�����V .. �����n��
    //3.�b�̫�@�V.���ܪ��A��ݾ����A(�A�Ⱦ��q�ݭn��U�Ӫ��A)
    dir = ApproachCharacterDir(dest_x - x, dest_y - y);
    LOCK_CHARACTER(npc_no);
    SetCharacterDir(npc_no, dir);
    UNLOCK_CHARACTER(npc_no);
    //    
    switch (MinKind_NpcMagicDischarge(npc_no))
    {
    case NPC_MAGIC_DOING://�b�I�k�L�{��
        break;        
    case NPC_MAGIC_START://�}�l�I�k
        break;        
    case NPC_MAGIC_FIRE://��F�����V
        //  �A�Ⱦ��ݻݭn�����]�k�ե�
        server_break_magic(0, npc_no, dest_x, dest_y, magic_index);
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



