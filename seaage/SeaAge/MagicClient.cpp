/*
**	MagicClient.cpp
**	client magic functions
**
**	Jack, 2002/06/24.
*/
#include "MainFun.h"
#include "NetGE_MainFunc.h"
#include "Map.h"
#include "Npc.h"
#include "Magic.h"
#include "MagicClient.h"

//
void	do_magic_part_sleep(SLONG p);
void	do_magic_part_explode(SLONG p);
//
void	do_magic_part_line(SLONG p);
void	do_magic_part_stay(SLONG p);
void	do_magic_part_link(SLONG p);
void	do_magic_part_fall(SLONG p);
void	do_magic_part_move(SLONG p);
void	do_magic_part_trace(SLONG p);
void	do_magic_part_stay_once(SLONG p);
void	do_magic_part_roll(SLONG p);
void	do_magic_part_shake(SLONG p);
void	do_magic_part_diffuse(SLONG p);
void	do_magic_part_screw(SLONG p);
void	do_magic_part_eddy(SLONG p);
void	do_magic_part_parabola(SLONG p);


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void	client_break_magic(SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG magic_no, SLONG dest_no, SLONG type)
{
	ExecBreakMagic(magic_no, npc_no, type, dest_x, dest_y, dest_no);
	AppendBreakMagicParts();
}

//---
//  客戶端物件刷新函數
//---
void    client_refresh_magic(void)
{
    SLONG   p, next, map_no = 0;
    SLONG   flag, state;
    //
    LOCK_MAGIC(map_no);
    //
    p = GetZoneMagicPartNext(map_no);
    while(p != map_no)
    {
        next = GetZoneMagicPartNext(p);
        flag = GetZoneMagicPartFlag(p);
        state = GetZoneMagicPartState(p);
        //
        switch (state)
        {
        case MAGIC_STATE_SLEEP:
            do_magic_part_state_sleep(p);
            break;
        case MAGIC_STATE_SHIFT:
            //SURVIAL 控制
            do_magic_part_survial(p);
            //
            do_magic_part_state_shift(p);
            break;        
        case MAGIC_STATE_EXPLODE:
            //
            do_magic_part_state_explode(p);
            break;
        default:            
            do_magic_part_state_dump(p);
            break;
        }
        //動畫播放...控制
        do_magic_part_frame(p);
        //
        p = next;        
    }
    //刪去系統中一些已經死亡的魔法物件
    ReduceVoidZoneMagicPart();
    //
    UNLOCK_MAGIC(map_no);
    // mark by lijun 2003-05-06
    /*
    SLONG   p, next, map_no = 0;
    SLONG   magic_path;
    SLONG   flag, state;

    LOCK_MAGIC(map_no);

    p = GetZoneMagicPartNext(map_no);
    while(p != map_no)
    {
        next = GetZoneMagicPartNext(p);
        flag = GetZoneMagicPartFlag(p);
        state = GetZoneMagicPartState(p);
        magic_path = GetZoneMagicPartPath(p);
        if(flag)
        {
            switch(state)
            {
            case MAGIC_STATE_SLEEP:
				do_magic_part_sleep(p);
				break;

            case MAGIC_STATE_SHIFT:
                {
                    switch(magic_path)
                    {
                    case MAGIC_PATH_LINE:
						do_magic_part_line(p);
						break;

                    case MAGIC_PATH_CURVE:
                    case MAGIC_PATH_MISSILE:
                        break;

                    case MAGIC_PATH_STAY:
						do_magic_part_stay(p);
						break;

                    case MAGIC_PATH_LINK:
						do_magic_part_link(p);
						break;

                    case MAGIC_PATH_FALL:
						do_magic_part_fall(p);
						break;

                    case MAGIC_PATH_MOVE:
						do_magic_part_move(p);
						break;

                    case MAGIC_PATH_TRACE:
						do_magic_part_trace(p);
						break;

                    case MAGIC_PATH_STAY_ONCE:
						do_magic_part_stay_once(p);
						break;

                    case MAGIC_PATH_ROLL:
						do_magic_part_roll(p);
						break;

                    case MAGIC_PATH_SHAKE:
						do_magic_part_shake(p);
						break;

                    case MAGIC_PATH_DIFFUSE:
						do_magic_part_diffuse(p);
						break;

                    case MAGIC_PATH_SCREW:
						do_magic_part_screw(p);
						break;

                    case MAGIC_PATH_EDDY:
						do_magic_part_eddy(p);
						break;

					case MAGIC_PATH_PARABOLA:
						do_magic_part_parabola(p);
						break;

                    default: //default magic path
                        break;
                    }
                    break;
                }
            case MAGIC_STATE_EXPLODE:
				do_magic_part_explode(p);
				break;
            }
        }

		//
        // Ready for the next magic_part.
		//
        p = next;
    }

	//
    // Cleanup the void magic parts (someone's flag is 0).
	//
    ReduceVoidZoneMagicPart();

    UNLOCK_MAGIC(map_no);
    */    
}



SLONG   client_process_magic_roll(SLONG magic_index, SLONG src_npc, SLONG map_no, SLONG magic_x, SLONG magic_y,
                                  SLONG magic_orig_x, SLONG magic_orig_y, SLONG magic_dest_x, SLONG magic_dest_y )
{
    SLONG   attack_radius, magic_relation;
    SLONG   found_dest_npc;
    SLONG   dest_npc, npc_flag;
    SLONG   dest_npc_x, dest_npc_y, dest_npc_z;
    SLONG   dest_npc_hp;
    SLONG   relation;
    SLONG   distance;
    SLONG   dx, dy;
    double  dr, kx, ky;
    double  upright_kx, upright_ky;
    
    //mark by lijun 2003-04-23
    //attack_radius = GetSkillExplodeRange(magic_index);
    //magic_relation = GetSkillRelation(magic_index);    
    attack_radius = GetSkillMagicHitDistance(magic_index, 0);
    magic_relation = GetSkillUseTag(magic_index, 0);

    dx = magic_dest_x - magic_orig_x;
    dy = magic_dest_y - magic_orig_y;
    dr = sqrt( dx * dx + dy * dy );
    if(dr == 0)
        return  0;

    kx = dx / dr;
    ky = dy / dr;
    upright_kx = ky;
    upright_ky = -kx;
    
    
    found_dest_npc = FALSE;
    for(dest_npc = 0; dest_npc < game_npc_max; dest_npc ++)
    {
        if(dest_npc != src_npc)
        {
            LOCK_CHARACTER(dest_npc);
            npc_flag = get_npc_flag(dest_npc);
			GetCharacterPosition(dest_npc, &dest_npc_x, &dest_npc_y, &dest_npc_z);
            dest_npc_hp = GetCharacterHp(dest_npc);
            UNLOCK_CHARACTER(dest_npc);
            
            if(npc_flag && dest_npc_hp > 0)
            {
                distance = (SLONG) sqrt( (dest_npc_x - magic_x) * (dest_npc_x - magic_x ) +
                    (dest_npc_y - magic_y) * (dest_npc_y - magic_y) );
                if(distance < attack_radius)
                {
                    //Shake out if it's in the attack radius -----------------------------------------------
                    {
                        SLONG   droop_x, droop_y, droop_z;
                        SLONG   shake_distance;
                        SLONG   shake_x, shake_y;
                        SLONG   result, is_shaked;
                        SLONG   droop_distance;
                        double  s;
                        
                        //TODO:
                        //Shake out other npc here.
                        //We must write a function for compute the shake point position later.
                        //
                        
                        //(1) Find the droop point of dest_npc to the part path line.
                        D3_droop_point_line(dest_npc_x, dest_npc_y, 0, magic_orig_x, magic_orig_y, 0,
                            magic_dest_x, magic_dest_y, 0, &droop_x, &droop_y, &droop_z);
                        
                        droop_distance = D2_distance_point_line( dest_npc_x, dest_npc_y,
                            magic_orig_x, magic_orig_y, magic_dest_x, magic_dest_y);
                        if(droop_distance <= 0)
                            droop_distance = 1;
                        shake_distance = attack_radius * 5 / 2 - droop_distance;
                        
                        s = - shake_distance / droop_distance;
                        shake_x = (SLONG)( dest_npc_x + (droop_x - dest_npc_x) * s );
                        shake_y = (SLONG)( dest_npc_y + (droop_y - dest_npc_y) * s );

                        is_shaked = FALSE;

                        LOCK_MAPMASK(map_no);
                        result = FindMaskNearThroughPixel(dest_npc_x, dest_npc_y, &shake_x, &shake_y, MASK_STOP);
                        is_shaked = TRUE;
                        UNLOCK_MAPMASK(map_no);

                        if( TRUE == is_shaked )
                        {
                            //If the npc is shaked, set it's new position.
                            LOCK_CHARACTER(dest_npc);
							SetCharacterPosition(dest_npc, shake_x, shake_y, 0);
                            UNLOCK_CHARACTER(dest_npc);
                        }
                    }

                    //Check the relation between src_npc and dest_npc --------------------------------
                    relation = get_npc_magic_standpoint_relation(src_npc, dest_npc);

                    //process magics hurts if matched dest flag ----------------------
                    if(relation & magic_relation)
                    {
                        found_dest_npc = TRUE;

                        //Skip magic func process.
                    }
                }
            }
        }
    }
    return  found_dest_npc;
}


SLONG   client_process_magic_shake(SLONG magic_index, SLONG src_npc, SLONG map_no, SLONG magic_orig_x, SLONG magic_orig_y)
{
    SLONG   attack_radius, magic_relation;
    SLONG   found_dest_npc;
    SLONG   dest_npc, npc_flag;
    SLONG   dest_npc_x, dest_npc_y, dest_npc_z;
    SLONG   dest_npc_hp;
    SLONG   relation;
    SLONG   distance;

    //mark by lijun 2003-04-23
    //attack_radius = GetSkillExplodeRange(magic_index);
    //magic_relation = GetSkillRelation(magic_index);    
    attack_radius = GetSkillMagicHitDistance(magic_index, 0);
    magic_relation = GetSkillUseTag(magic_index, 0);

    found_dest_npc = FALSE;
    for(dest_npc=0; dest_npc<game_npc_max; dest_npc++)
    {
        if(dest_npc != src_npc)
        {
            LOCK_CHARACTER(dest_npc);
            npc_flag = get_npc_flag(dest_npc);
			GetCharacterPosition(dest_npc, &dest_npc_x, &dest_npc_y, &dest_npc_z);
            dest_npc_hp = GetCharacterHp(dest_npc);
            UNLOCK_CHARACTER(dest_npc);
            
            if(npc_flag && dest_npc_hp > 0)
            {
                //Check distance first for attack line len.
                distance = (SLONG) sqrt( (dest_npc_x - magic_orig_x) * (dest_npc_x - magic_orig_x ) +
                    (dest_npc_y - magic_orig_y) * (dest_npc_y - magic_orig_y) );
                if( distance < attack_radius)
                {
                    //Check the relation between src_npc and dest_npc --------------------------------
                    relation = get_npc_magic_standpoint_relation(src_npc, dest_npc);

                    //process magics hurts if matched dest flag ----------------------
                    if(relation & magic_relation)
                    {
                        SLONG   through_result;
                        SLONG   shake_distance;
                        SLONG   is_shaked, result;
                        SLONG   shake_x, shake_y;
                        double  s;

                        LOCK_MAPMASK(map_no);
                        through_result = IsPixelLineThrough(magic_orig_x, magic_orig_y, 
                            dest_npc_x, dest_npc_y, MASK_STOP );
                        UNLOCK_MAPMASK(map_no);

                        if( TRUE == through_result)
                        {
                            shake_distance = attack_radius * 5 / 2 - distance;
                            if(shake_distance > attack_radius * 2)
                                shake_distance = attack_radius * 2;
                            
                            if(distance == 0)
                            {
                                shake_x = (SLONG) (dest_npc_x + shake_distance);
                                shake_y = (SLONG) (dest_npc_y);
                            }
                            else
                            {
                                s = - shake_distance / distance;
                                shake_x = (SLONG)( dest_npc_x + (magic_orig_x - dest_npc_x) * s );
                                shake_y = (SLONG)( dest_npc_y + (magic_orig_y - dest_npc_y) * s );
                            }
                            
                            is_shaked = FALSE;

                            LOCK_MAPMASK(map_no);
                            result = FindMaskNearThroughPixel(dest_npc_x, dest_npc_y, &shake_x, &shake_y, MASK_STOP);
                            is_shaked = TRUE;
                            UNLOCK_MAPMASK(map_no);
                            
                            if( TRUE == is_shaked )
                            {
                                //If the npc is shaked, set it's new position.
                                LOCK_CHARACTER(dest_npc);
								SetCharacterPosition(dest_npc, shake_x, shake_y, 0);
                                UNLOCK_CHARACTER(dest_npc);
                            }

                            //Take magic hurt effect 30 percent.
                            //if( system_rand() % 100 < 30 )
                            if( system_rand() % 100 < 100 )
                            {
                                found_dest_npc = TRUE;

                                //Skip the process magic hurt functions for client.
                                //...
                            }
                        }
                    }
                }
            }
        }
    }
    return  found_dest_npc;
}



SLONG   client_check_is_magic_broken( SLONG magic_index, SLONG src_npc, SLONG map_no, SLONG magic_x, SLONG magic_y )
{
    SLONG   magic_relation;
    SLONG   magic_adjacent, broken_flag;
    SLONG   dest_npc, npc_flag;
    SLONG   dest_npc_x, dest_npc_y, dest_npc_z;
    SLONG   dest_npc_hp;
    SLONG   relation;
    SLONG   distance;
    
    //mark by lijun 2003-04-23
    //magic_relation = GetSkillRelation(magic_index);    
    magic_adjacent = GetSkillMagicBrokenDistance(magic_index, 0);
    magic_relation = GetSkillUseTag(magic_index, 0);

    //(1) Check if need to broken depend on the magic adjacent.
    broken_flag = FALSE;
    for(dest_npc = 0; dest_npc < game_npc_max; dest_npc ++)
    {
        if(src_npc == dest_npc)
            continue;

        LOCK_CHARACTER(dest_npc);
        npc_flag = get_npc_flag(dest_npc);
		GetCharacterPosition(dest_npc, &dest_npc_x, &dest_npc_y, &dest_npc_z);
        dest_npc_hp = GetCharacterHp(dest_npc);
        UNLOCK_CHARACTER(dest_npc);
        
        if(npc_flag && dest_npc_hp > 0)
        {
            //check attack radius ---------------------------------------------
            distance = (SLONG) sqrt( (dest_npc_x - magic_x) * (dest_npc_x - magic_x ) +
                (dest_npc_y - magic_y) * (dest_npc_y - magic_y) );
            if(distance < magic_adjacent)
            {
                //check the relation between src_npc and dest_npc -------------
                relation = get_npc_magic_standpoint_relation(src_npc, dest_npc);
                
                //process magics if matched dest flag ----------------------
                if(relation & magic_relation)
                {
                    broken_flag = TRUE;
                    dest_npc  = game_npc_max + 100;  //break the for loop.
                }
            }
        }
    }

    return  broken_flag;
}



void	client_play_magic_voice(SLONG map_no, SLONG magic_index, SLONG kind, SLONG map_x, SLONG map_y)
{
    //TODO:
}



/************************************************************************************************************/
/*                                                                                                          */
/************************************************************************************************************/
void	do_magic_part_sleep(SLONG p)
{
	SLONG	sleep_tick, magic_stop;
	SLONG	next_x, next_y, next_z;
	SLONG	result;

	sleep_tick = GetZoneMagicPartSleepTick(p);

	--sleep_tick;
	if(sleep_tick <= 0)
	{
		GetZoneMagicPartCurrPosition(p, &next_x, &next_y, &next_z);
		magic_stop = GetZoneMagicPartStop(p);
		
		LOCK_MAPMASK(0);
		result = IsPixelMaskMatch(next_x, next_y, magic_stop);
		UNLOCK_MAPMASK(0);
		
		if(TRUE == result)
		{
			//
			// Dead for stop
			//
			SetZoneMagicPartFlag(p, 0);
		}
		else
		{
			PrepareZoneMagicPartForShift(p);
		}
	}
	else
	{
		SetZoneMagicPartSleepTick(p, sleep_tick);
	}
}


void	do_magic_part_line(SLONG p)
{
	double  dx,dy,dz,dr;
	SLONG   step, magic_stop;
	double  speed;
	SLONG	dest_x, dest_y, dest_z;
	SLONG	orig_x, orig_y, orig_z;
	SLONG	next_x, next_y, next_z;
	SLONG	broken_flag;
	SLONG	magic_index;
	SLONG	src_npc, map_no = 0;
	SLONG	life_tick;
	SLONG	result;
	
	step = GetZoneMagicPartStep(p);
	speed = GetZoneMagicPartSpeed(p);
	GetZoneMagicPartDestPosition(p, &dest_x, &dest_y, &dest_z);
	GetZoneMagicPartOrigPosition(p, &orig_x, &orig_y, &orig_z);
	dx = dest_x - orig_x;
	dy = dest_y - orig_y;
	dz = dest_z - orig_z;
	dr = sqrt( dx * dx + dy * dy + dz * dz);
	next_x = orig_x + (SLONG) ( step * speed * dx / dr );
	next_y = orig_y + (SLONG) ( step * speed * dy / dr );
	next_z = orig_z + (SLONG) ( step * speed * dz / dr );
	
	magic_stop = GetZoneMagicPartStop(p);
	LOCK_MAPMASK(map_no);
	result = IsPixelMaskMatch(next_x, next_y, magic_stop);
	UNLOCK_MAPMASK(map_no);
	
	if(TRUE == result)
	{
		PrepareZoneMagicPartForExplode(p);
	}
	else
	{
        magic_index = GetZoneMagicPartSkillIndex(p);
        src_npc = GetZoneMagicPartSourceNo(p);

		broken_flag = client_check_is_magic_broken( magic_index, src_npc, map_no, next_x, next_y);
		
		if(broken_flag)
		{
			client_play_magic_voice(map_no, magic_index, MAGIC_VOICE_BROKEN, next_x, next_y);

			PrepareZoneMagicPartForExplode(p);
		}
		else
		{
			SetZoneMagicPartCurrPosition(p, next_x, next_y, next_z);
			SetZoneMagicPartStep(p, step+1);
			life_tick = GetZoneMagicPartLifeTick(p);
			life_tick --;
			if(life_tick <= 0)	
			{
				//
				// It's naturally dead.
				//
				SetZoneMagicPartFlag(p, 0);
			}
			else
			{
				SetZoneMagicPartLifeTick(p, life_tick);
				LoopZoneMagicPartFrame(p);
			}
		}
	}
}



void	do_magic_part_stay(SLONG p)
{
	SLONG	next_x, next_y, next_z;
	SLONG	magic_stop;
	SLONG	result;
	SLONG	life_tick;

	GetZoneMagicPartCurrPosition(p, &next_x, &next_y, &next_z);
	magic_stop = GetZoneMagicPartStop(p);
	
	LOCK_MAPMASK(map_no);
	result = IsPixelMaskMatch(next_x, next_y, magic_stop);
	UNLOCK_MAPMASK(map_no);
	
	if( TRUE == result )
	{
		//
		// Dead for stop(can't stay).
		//
		SetZoneMagicPartFlag(p, 0);
	}
	else
	{
		life_tick = GetZoneMagicPartLifeTick(p);
		life_tick --;
		if(life_tick <= 0)
		{
			SetZoneMagicPartFlag(p, 0);
		}
		else
		{
			SetZoneMagicPartLifeTick(p, life_tick);
			LoopZoneMagicPartFrame(p);
		}
	}
}



void	do_magic_part_link(SLONG p)
{
	SLONG	src_npc;
	SLONG	next_x, next_y, next_z;
	SLONG	life_tick;
	SLONG	over_flag;

	src_npc = GetZoneMagicPartSourceNo(p);

	LOCK_CHARACTER(src_npc);
	GetCharacterPosition(src_npc, &next_x, &next_y, &next_z);
	UNLOCK_CHARACTER(src_npc);

	life_tick = GetZoneMagicPartLifeTick(p);
	life_tick --;
	if(life_tick <= 0)
	{
		SetZoneMagicPartFlag(p, 0);
	}
	else
	{
		over_flag = OverZoneMagicPartFrame(p);
		if(over_flag)
		{
			SetZoneMagicPartFlag(p, 0);
		}
	}
}


void	do_magic_part_fall(SLONG p)
{
	SLONG	dest_x, dest_y, dest_z;
	SLONG	orig_x, orig_y, orig_z;
	SLONG	next_x, next_y, next_z;
	double  dx,dy,dz,dr;
	SLONG   step;
	double  speed;
	SLONG	life_tick;
	SLONG	magic_index;

	step = GetZoneMagicPartStep(p);
	speed = GetZoneMagicPartSpeed(p);
	magic_index = GetZoneMagicPartSkillIndex(p);
	GetZoneMagicPartDestPosition(p, &dest_x, &dest_y, &dest_z);
	GetZoneMagicPartOrigPosition(p, &orig_x, &orig_y, &orig_z);

	dx = dest_x - orig_x;
	dy = dest_y - orig_y;
	dz = dest_z - orig_z;
	dr = sqrt( dx * dx + dy * dy + dz * dz);
	next_x = orig_x + (SLONG) ( step * speed * dx / dr );
	next_y = orig_y + (SLONG) ( step * speed * dy / dr / 2 );
	next_z = orig_z + (SLONG) ( step * speed * dz / dr );
	if(next_z <= 0)
	{
		client_play_magic_voice(0, magic_index, MAGIC_VOICE_BROKEN, next_x, next_y);
		
		//
		// Ready for explode
		//
		next_z = 0;
		SetZoneMagicPartCurrPosition(p, next_x, next_y, next_z);
		PrepareZoneMagicPartForExplode(p);
	}
	else
	{
		SetZoneMagicPartCurrPosition(p, next_x, next_y, next_z);
		SetZoneMagicPartStep(p, step+1);
		life_tick = GetZoneMagicPartLifeTick(p);
		life_tick --;
		if(life_tick <= 0)
		{
			SetZoneMagicPartFlag(p, 0);
		}
		else
		{
			SetZoneMagicPartLifeTick(p, life_tick);
			LoopZoneMagicPartFrame(p);
		}
	}
}


void	do_magic_part_move(SLONG p)
{
	SLONG	map_no = 0;
	SLONG	dest_x, dest_y, dest_z;
	SLONG	orig_x, orig_y, orig_z;
	SLONG	next_x, next_y, next_z;
	double  dx,dy,dz,dr;
	SLONG   step;
	double  speed;
	SLONG	result;
	SLONG	magic_stop;
	SLONG	broken_flag;
	SLONG	life_tick;
	SLONG	magic_index;
	SLONG	src_npc;
	
	step = GetZoneMagicPartStep(p);
	speed = GetZoneMagicPartSpeed(p);
	GetZoneMagicPartDestPosition(p, &dest_x, &dest_y, &dest_z);
	GetZoneMagicPartOrigPosition(p, &orig_x, &orig_y, &orig_z);
	dx = dest_x - orig_x;
	dy = dest_y - orig_y;
	dz = dest_z - orig_z;
	dr = sqrt( dx * dx + dy * dy + dz * dz);
	next_x = orig_x + (SLONG) ( step * speed * dx / dr );
	next_y = orig_y + (SLONG) ( step * speed * dy / dr );
	next_z = orig_z + (SLONG) ( step * speed * dz / dr );
	
	magic_stop = GetZoneMagicPartStop(p);
	LOCK_MAPMASK(map_no);
	result = IsPixelMaskMatch(next_x, next_y, magic_stop);
	UNLOCK_MAPMASK(map_no);
	
	if(TRUE == result)
	{
		// dead now!
		SetZoneMagicPartFlag(p, 0);
	}
	else
	{
		magic_index = GetZoneMagicPartSkillIndex(p);
		src_npc = GetZoneMagicPartSourceNo(p);
		broken_flag = client_check_is_magic_broken( magic_index, src_npc, map_no, next_x, next_y);
		
		if(broken_flag)
		{
			client_play_magic_voice(map_no, magic_index, MAGIC_VOICE_BROKEN, next_x, next_y);
			
			// dead now!
			SetZoneMagicPartFlag(p, 0);
		}
		else
		{
			SetZoneMagicPartCurrPosition(p, next_x, next_y, next_z);
			SetZoneMagicPartStep(p, step+1);

			life_tick = GetZoneMagicPartLifeTick(p);
			life_tick --;
			if(life_tick <= 0)
			{
				//it's naturally dead
				SetZoneMagicPartFlag(p, 0);
			}
			else
			{
				SetZoneMagicPartLifeTick(p, life_tick);
				LoopZoneMagicPartFrame(p);
			}
		}
	}
}


void	do_magic_part_trace(SLONG p)
{
	SLONG   dest_npc;
	SLONG   dest_x, dest_y, dest_z;
	SLONG   cur_x, cur_y, cur_z;
	SLONG   result;
	double  speed;
	SLONG	magic_stop;
	SLONG	step;
	SLONG	life_tick;
	
	dest_npc = GetZoneMagicPartTargetNo(p);
	if(dest_npc >= 0)
	{
		LOCK_CHARACTER(dest_npc);
		GetCharacterPosition(dest_npc, &dest_x, &dest_y, &dest_z);
        UNLOCK_CHARACTER(dest_npc);
	}
	else
	{
		GetZoneMagicPartDestPosition(p, &dest_x, &dest_y, &dest_z);
	}
	
	speed = GetZoneMagicPartSpeed(p);
	GetZoneMagicPartCurrPosition(p, &cur_x, &cur_y, &cur_z);
	
	magic_stop = GetZoneMagicPartStop(p);
	LOCK_MAPMASK(map_no);
	result = TrendFindCharacterStep(cur_x, cur_y, &dest_x, &dest_y, (SLONG)speed, magic_stop);
	UNLOCK_MAPMASK(map_no);
	
	switch(result)
	{
	case STEP_ON_THE_WAY:
		{
			SetZoneMagicPartCurrPosition(p, dest_x, dest_y, dest_z);
			step = GetZoneMagicPartStep(p);
			SetZoneMagicPartStep(p, step+1);
			life_tick = GetZoneMagicPartLifeTick(p);
			life_tick --;
			if(life_tick <= 0)
			{
				SetZoneMagicPartFlag(p, 0);
			}
			else
			{
				SetZoneMagicPartLifeTick(p, life_tick);
				LoopZoneMagicPartFrame(p);
			}
		}
		break;
		
	case STEP_ARRIVE:
		//We need not check broken here.
		//broken_flag = client_check_is_magic_broken(magic_index, src_npc, map_no, dest_x, dest_y);
		SetZoneMagicPartCurrPosition(p, dest_x, dest_y, dest_z);
		PrepareZoneMagicPartForExplode(p);
		break;
		
	case STEP_OBSTRUCT:
	case STEP_OUTSTRETCH:
		SetZoneMagicPartCurrPosition(p, dest_x, dest_y, dest_z);
		PrepareZoneMagicPartForExplode(p);
		break;
	}
}


void	do_magic_part_stay_once(SLONG p)
{
	SLONG	next_x, next_y, next_z;
	SLONG	magic_stop;
	SLONG	result;
	SLONG	life_tick;
	SLONG	over_flag;

	GetZoneMagicPartCurrPosition(p, &next_x, &next_y, &next_z);
	magic_stop = GetZoneMagicPartStop(p);
	
	LOCK_MAPMASK(map_no);
	result = IsPixelMaskMatch(next_x, next_y, magic_stop);
	UNLOCK_MAPMASK(map_no);
	
	if( TRUE == result )
	{
		SetZoneMagicPartFlag(p, 0);
	}
	else
	{
		life_tick = GetZoneMagicPartLifeTick(p);
		life_tick--;
		if(life_tick <= 0)
		{
			SetZoneMagicPartFlag(p, 0);
		}
		else
		{
			SetZoneMagicPartLifeTick(p, life_tick);
			over_flag = OverZoneMagicPartFrame(p);
			if(over_flag)
			{
				SetZoneMagicPartFlag(p, 0);
			}
		}
	}
}


void	do_magic_part_roll(SLONG p)
{
	SLONG	map_no = 0;
	double  dx, dy, dz, dr;
	double  speed;
	SLONG   step;
	SLONG   orig_x, orig_y, orig_z;
	SLONG   dest_x, dest_y, dest_z;
	SLONG	next_x, next_y, next_z;
	SLONG	magic_stop;
	SLONG	result;
	SLONG	magic_index;
	SLONG	life_tick;
	SLONG	broken_flag;
	SLONG	src_npc;
	
	step = GetZoneMagicPartStep(p);
	speed = GetZoneMagicPartSpeed(p);
	GetZoneMagicPartOrigPosition(p, &orig_x, &orig_y, &orig_z);
	GetZoneMagicPartDestPosition(p, &dest_x, &dest_y, &dest_z);
	dx = dest_x - orig_x;
	dy = dest_y - orig_y;
	dz = dest_z - orig_z;
	dr = sqrt( dx * dx + dy * dy + dz * dz);
	next_x = orig_x + (SLONG) ( step * speed * dx / dr );
	next_y = orig_y + (SLONG) ( step * speed * dy / dr );
	next_z = orig_z + (SLONG) ( step * speed * dz / dr );
	
	magic_stop = GetZoneMagicPartStop(p);
	LOCK_MAPMASK(map_no);
	result = IsPixelMaskMatch(next_x, next_y, magic_stop);
	UNLOCK_MAPMASK(map_no);
	
	if(TRUE == result)
	{
		PrepareZoneMagicPartForExplode(p);
	}
	else
	{
		magic_index = GetZoneMagicPartSkillIndex(p);
		src_npc = GetZoneMagicPartSourceNo(p);

		//? We may skip client process magic roll here ?
		broken_flag = client_process_magic_roll(magic_index, src_npc, map_no, next_x, next_y, orig_x, orig_y,
			dest_x, dest_y);
		
		{
			SetZoneMagicPartCurrPosition(p, next_x, next_y, next_z);
			SetZoneMagicPartStep(p, step+1);
			life_tick = GetZoneMagicPartLifeTick(p);
			life_tick --;
			if(life_tick <= 0)
			{
				//it's naturally dead
				client_play_magic_voice(map_no, magic_index, MAGIC_VOICE_BROKEN, next_x, next_y);
				
				PrepareZoneMagicPartForExplode(p);
			}
			else
			{
				SetZoneMagicPartLifeTick(p, life_tick);
				LoopZoneMagicPartFrame(p);
			}
		}
	}
}


void	do_magic_part_shake(SLONG p)
{
	SLONG	map_no = 0;
	SLONG	src_npc;
	SLONG	next_x, next_y, next_z;
	SLONG	delay_tick;
	SLONG	life_tick;
	SLONG	over_flag;
	SLONG	magic_index;

	src_npc = GetZoneMagicPartSourceNo(p);
	LOCK_CHARACTER(src_npc);
	GetCharacterPosition(src_npc, &next_x, &next_y, &next_z);
	UNLOCK_CHARACTER(src_npc);
	
	delay_tick = GetZoneMagicPartDelayTick(p);
	if(delay_tick > 0)
	{
		delay_tick --;
		SetZoneMagicPartDelayTick(p, delay_tick);
	}
	if(delay_tick <= 0)
	{
		
		SetZoneMagicPartDelayTick(p, MAX_MAGIC_DELAY_TICK);
		
		//for client, we will process magic hurt image effect.
		src_npc = GetZoneMagicPartSourceNo(p);
		magic_index = GetZoneMagicPartSkillIndex(p);
		client_process_magic_shake( magic_index, src_npc, map_no, next_x, next_y);
	}
	
	life_tick = GetZoneMagicPartLifeTick(p);
	life_tick --;
	if(life_tick <= 0)
	{
		SetZoneMagicPartFlag(p, 0);
	}
	else
	{
		SetZoneMagicPartLifeTick(p, life_tick);
		SetZoneMagicPartCurrPosition(p, next_x, next_y, next_z);
		over_flag = OverZoneMagicPartFrame(p);
		if(over_flag)
		{
			SetZoneMagicPartFlag(p, 0);
		}
	}
}


void	do_magic_part_diffuse(SLONG p)
{
	SLONG	src_npc;
	SLONG	next_x, next_y, next_z;
	SLONG	life_tick;
	SLONG	frame_type;

	src_npc = GetZoneMagicPartSourceNo(p);
	LOCK_CHARACTER(src_npc);
	GetCharacterPosition(src_npc, &next_x, &next_y, &next_z);
	UNLOCK_CHARACTER(src_npc);
	
	// We process magic hurt in the last frame.
	// So we skip delay_tick checking here.

	life_tick = GetZoneMagicPartLifeTick(p);
	life_tick --;
	if(life_tick <= 0)
	{
		SetZoneMagicPartFlag(p, 0);
	}
	else
	{
		SetZoneMagicPartCurrPosition(p, next_x, next_y, next_z);
		frame_type = KeyPlayZoneMagicPartFrame(p);
		if(MAGIC_KEY_FRAME_TAIL == frame_type)
		{
			// We process magic hurt at the last frame.
			// But skip magic data process at client.
		}
		else if(MAGIC_KEY_FRAME_OVER == frame_type)
		{
			SetZoneMagicPartFlag(p, 0);
		}
	}
}


void	do_magic_part_screw(SLONG p)
{
	SLONG	map_no = 0;
	SLONG	orig_x, orig_y, orig_z;
	SLONG	dest_x, dest_y, dest_z;
	SLONG	next_x, next_y, next_z;
	double  dx, dy, dz;
	SLONG   step;
	double  speed;
	double  a, sita, sin_sita, cos_sita, omiga;
	double  fx, fy, fz;
	double  fx2, fy2, fz2;
	SLONG	magic_stop;
	SLONG	result;
	SLONG	broken_flag;
	SLONG	src_npc;
	SLONG	life_tick;
	SLONG	magic_index;
	
	step = GetZoneMagicPartStep(p);
	speed = GetZoneMagicPartSpeed(p);
	GetZoneMagicPartDestPosition(p, &dest_x, &dest_y, &dest_z);
	GetZoneMagicPartOrigPosition(p, &orig_x, &orig_y, &orig_z);
	dx = dest_x - orig_x;
	dy = dest_y - orig_y;
	dz = dest_z - orig_z;
	
	sita = atan2(dy, dx);
	if(sita < 0)
		sita += 2 * PI;
	sin_sita = sin(sita);
	cos_sita = cos(sita);
	
	//(1) Make stand screw
	//------------------------------------------
	//fx = a * cos( omiga * t );
	//fy = a * sin( omiga * t );
	//fz = v * t;
	omiga = (2 * PI / 12);
	a = MID_MAGIC_HEIGHT / 3;
	fx = a * cos( omiga * step );
	fy = a * sin( omiga * step );
	fz = speed * step;
	
	//(2) Convert to our axis system -----------
	fx2 = fx * cos_sita - fy * sin_sita + fz * cos_sita;
	fy2 = fx * sin_sita + fy * cos_sita + fz * sin_sita;
	fz2 = -fx;
	
	next_x = orig_x + (SLONG) ( fx2 );
	next_y = orig_y + (SLONG) ( fy2 );
	next_z = orig_z + (SLONG) ( fz2 );
	
	magic_stop = GetZoneMagicPartStop(p);
	LOCK_MAPMASK(map_no);
	result = IsPixelMaskMatch(next_x, next_y, magic_stop);
	UNLOCK_MAPMASK(map_no);
	
	if(TRUE == result)
	{
		SetZoneMagicPartFlag(p, 0);
	}
	else
	{
		src_npc = GetZoneMagicPartSourceNo(p);
		magic_index = GetZoneMagicPartSkillIndex(p);
		broken_flag = client_check_is_magic_broken( magic_index, src_npc, map_no, next_x, next_y);
		
		if(TRUE == broken_flag)
		{
			// Skip hurt process for client here.
			// ...
			SetZoneMagicPartFlag(p, 0);
		}
		else
		{
			SetZoneMagicPartCurrPosition(p, next_x, next_y, next_z);
			SetZoneMagicPartStep(p, step+1);
			life_tick = GetZoneMagicPartLifeTick(p);
			life_tick --;
			if(life_tick <= 0)
			{
				SetZoneMagicPartFlag(p, 0);
			}
			else
			{
				LoopZoneMagicPartFrame(p);
			}
		}
	}
}


void	do_magic_part_eddy(SLONG p)
{
	SLONG	map_no = 0;
	SLONG	orig_x, orig_y, orig_z;
	SLONG	dest_x, dest_y, dest_z;
	SLONG	next_x, next_y, next_z;
	double  dx, dy, dz;
	SLONG   step;
	double  speed;
	double  r, a, sita, sin_sita, cos_sita;
	double  fx, fy, fz;
	SLONG	magic_stop;
	SLONG	src_npc;
	SLONG	result;
	SLONG	broken_flag;
	SLONG	life_tick;
	SLONG	magic_index;
	
	step = GetZoneMagicPartStep(p);
	speed = GetZoneMagicPartSpeed(p);
	GetZoneMagicPartDestPosition(p, &dest_x, &dest_y, &dest_z);
	GetZoneMagicPartOrigPosition(p, &orig_x, &orig_y, &orig_z);
	dx = dest_x - orig_x;
	dy = dest_y - orig_y;
	dz = dest_z - orig_z;
	
	//Use NPC_MASK_HEIGHT for the general sample for a.
	a = NPC_MASK_HEIGHT / 8;
	sita = atan2(dy, dx);
	if(sita < 0)
		sita += 2 * PI;
	sita = sita + step * speed;
	
	sin_sita = sin(sita);
	cos_sita = cos(sita);
	
	//阿基米德螺線
	//------------------------
	//r = a * sita;
	//
	r = a * sita;
	fx = r * cos(sita);
	fy = r * sin(sita);
	fz = 0;
	
	next_x = orig_x + (SLONG) ( fx );
	next_y = orig_y + (SLONG) ( fy );
	next_z = orig_z + (SLONG) ( fz );
	
	magic_stop = GetZoneMagicPartStop(p);
	LOCK_MAPMASK(map_no);
	result = IsPixelMaskMatch(next_x, next_y, magic_stop);
	UNLOCK_MAPMASK(map_no);
	
	if(TRUE == result)
	{
		SetZoneMagicPartFlag(p, 0);
	}
	else
	{
		src_npc = GetZoneMagicPartSourceNo(p);
		magic_index = GetZoneMagicPartSkillIndex(p);
		broken_flag = client_check_is_magic_broken( magic_index, src_npc, map_no, next_x, next_y);
		
		if(TRUE == broken_flag)
		{
			// Skip hurt process for client.
			// ...
			SetZoneMagicPartFlag(p, 0);
		}
		else
		{
			SetZoneMagicPartCurrPosition(p, next_x, next_y, next_z);
			SetZoneMagicPartStep(p, step+1);
			life_tick = GetZoneMagicPartLifeTick(p);
			life_tick --;
			if(life_tick <= 0)
			{
				SetZoneMagicPartFlag(p, 0);
			}
			else
			{
				LoopZoneMagicPartFrame(p);
			}
		}
	}
}


void	do_magic_part_explode(SLONG p)
{
	SLONG	map_no = 0;
	SLONG	frame_type;
	SLONG	magic_index;
	SLONG	x, y, z;

	frame_type = KeyPlayZoneMagicPartFrame(p);
	if(MAGIC_KEY_FRAME_HEAD == frame_type)
	{
		magic_index = GetZoneMagicPartSkillIndex(p);
		GetZoneMagicPartCurrPosition(p, &x, &y, &z);
		client_play_magic_voice(map_no, magic_index, MAGIC_VOICE_BROKEN, x, y);
	}
	else if(MAGIC_KEY_FRAME_OVER == frame_type)
	{
		SetZoneMagicPartFlag(p, 0);
	}
}




void	do_magic_part_parabola(SLONG p)
{
	double  dx,dy,dz,dr;
	SLONG   step;
	double  speed, zspeed;
	SLONG	dest_x, dest_y, dest_z;
	SLONG	orig_x, orig_y, orig_z;
	SLONG	next_x, next_y, next_z;
	SLONG	magic_index;
	SLONG	src_npc, map_no = 0;
	SLONG	life_tick;

	// Jack, TODO: [2/19/2003]
	step = GetZoneMagicPartStep(p);
	speed = GetZoneMagicPartSpeed(p);
	zspeed = GetZoneMagicPartVertSpeed(p);
	GetZoneMagicPartDestPosition(p, &dest_x, &dest_y, &dest_z);
	GetZoneMagicPartOrigPosition(p, &orig_x, &orig_y, &orig_z);
	dx = dest_x - orig_x;
	dy = dest_y - orig_y;
	//dz = dest_z - orig_z;
	dz = 0;
	dr = sqrt( dx * dx + dy * dy + dz * dz);
	next_x = orig_x + (SLONG) ( step * speed * dx / dr );
	next_y = orig_y + (SLONG) ( step * speed * dy / dr );
	next_z = orig_z + (SLONG) ( zspeed * step + GRAVITY_ACCELERATION  * step * step / 2.0);

	magic_index = GetZoneMagicPartSkillIndex(p);
	src_npc = GetZoneMagicPartSourceNo(p);
	
	if(next_z <= 0)
	{
		client_play_magic_voice(map_no, magic_index, MAGIC_VOICE_BROKEN, next_x, next_y);
		
		SetZoneMagicPartCurrPosition(p, next_x, next_y, 0);
		PrepareZoneMagicPartForExplode(p);
	}
	else
	{
		SetZoneMagicPartCurrPosition(p, next_x, next_y, next_z);
		SetZoneMagicPartStep(p, step+1);
		life_tick = GetZoneMagicPartLifeTick(p);
		life_tick --;
		if(life_tick <= 0)	
		{
			//
			// It's naturally dead.
			//
			SetZoneMagicPartFlag(p, 0);
		}
		else
		{
			SetZoneMagicPartLifeTick(p, life_tick);
			LoopZoneMagicPartFrame(p);
		}
	}
}



/************************************************************************************************************/
/* BREAK MAGIC FUNCTIONS                                                                                    */
/************************************************************************************************************/

