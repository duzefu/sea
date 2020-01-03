/*
**	FightClient.cpp
**	client fight functions.
**
**	Jack, 2002/09/24.
*/
#include "MainFun.h"
#include "NetGE_MainFunc.h"
#include "ClientMain.h"
#include "Npc.h"
#include "CHear.h"


void    client_refresh_npc_foot_speed_state(SLONG npc_no)
{
	SLONG	state, ticks;

    LOCK_CHARACTER(npc_no);
	state = GetCharacterFootSpeedState(npc_no);
    switch(state)
    {
    case NPC_FOOT_SPEED_STATE_NORMAL:
        break;
    case NPC_FOOT_SPEED_STATE_TARDY:
		ticks = GetCharacterFootSpeedTicks(npc_no);
        if(--ticks <= 0)
            SetCharacterFootSpeedState(npc_no, NPC_FOOT_SPEED_STATE_NORMAL);
		else
			SetCharacterFootSpeedTicks(npc_no, (SHINT)ticks);
        break;
    case NPC_FOOT_SPEED_STATE_TIRED:
		ticks = GetCharacterFootSpeedTicks(npc_no);
        if(--ticks <= 0)
            SetCharacterFootSpeedState(npc_no, NPC_FOOT_SPEED_STATE_NORMAL);
		else
			SetCharacterFootSpeedTicks(npc_no, (SHINT)ticks);
        break;
    }
    UNLOCK_CHARACTER(npc_no);
}


void    client_compute_npc_muse_effect(SLONG npc_no)
{
}


void    client_compute_npc_attack_npc_effect(SLONG npc_no, SLONG dest_npc, SLONG magic_no)
{
}


void    client_compute_npc_final_attack_npc_effect(SLONG npc_no, SLONG dest_npc, SLONG magic_no)
{
}


/******************************************************************************************************************/
/* VOICE FUNCTIONS                                                                                                */
/******************************************************************************************************************/
void	client_play_fight_voice(SLONG map_no, SLONG npc_no, SLONG file_index, SLONG doing_kind, 
                                SLONG doing_step, SLONG dest_x, SLONG dest_y)
{
	SLONG	hear_map, hear_x, hear_y, hear_z;
	SLONG	dist_x, dist_y;
	SLONG	npc_x, npc_y, npc_z;

	LOCK_CHARACTER(0);
	hear_map = 0;
	GetCharacterPosition(g_lPlayerIndex, &hear_x, &hear_y, &hear_z);
	GetCharacterPosition(npc_no, &npc_x, &npc_y, &npc_z);
	UNLOCK_CHARACTER(0);

	if(map_no == hear_map)
	{
		switch(doing_kind)
		{
		case DOING_KIND_DEAD:
			dist_x = hear_x - npc_x;
			dist_y = hear_y - npc_y;
			if(abs(dist_x) < HEAR_RANGE_HALF_WIDTH  && abs(dist_y) < HEAR_RANGE_HALF_HEIGHT )
			{
				play_npc_dead_voice(npc_no, file_index);
			}
			break;
		case DOING_KIND_BEATED:
			dist_x = hear_x - npc_x;
			dist_y = hear_y - npc_y;
			if(abs(dist_x) < HEAR_RANGE_HALF_WIDTH  && abs(dist_y) < HEAR_RANGE_HALF_HEIGHT )
			{
				play_npc_beated_voice(npc_no, file_index);
			}
			break;
        case DOING_KIND_SPOWER:
			dist_x = hear_x - npc_x;
			dist_y = hear_y - npc_y;
			if(abs(dist_x) < HEAR_RANGE_HALF_WIDTH  && abs(dist_y) < HEAR_RANGE_HALF_HEIGHT )
			{
				play_npc_spower_voice(npc_no, file_index);
			}
            break;
        case DOING_KIND_MUSE:
			dist_x = hear_x - npc_x;
			dist_y = hear_y - npc_y;
			if(abs(dist_x) < HEAR_RANGE_HALF_WIDTH  && abs(dist_y) < HEAR_RANGE_HALF_HEIGHT )
			{
				play_npc_muse_voice(npc_no, file_index);
			}
            break;
        /*
		case DOING_KIND_ATTACK_NPC:
			dist_x = hear_x - npc_x;
			dist_y = hear_y - npc_y;
			if(abs(dist_x) < HEAR_RANGE_HALF_WIDTH  && abs(dist_y) < HEAR_RANGE_HALF_HEIGHT )
			{
				play_npc_attack_voice(npc_no, file_index);
			}
			break;
        */			
        case DOING_KIND_SEQUENTIAL_ATTACK_NPC:
			dist_x = hear_x - npc_x;
			dist_y = hear_y - npc_y;
			if(abs(dist_x) < HEAR_RANGE_HALF_WIDTH  && abs(dist_y) < HEAR_RANGE_HALF_HEIGHT )
			{
				play_npc_sequential_attack_voice(npc_no, file_index, doing_step);
			}
            break;
        case DOING_KIND_CLASH:
			dist_x = hear_x - npc_x;
			dist_y = hear_y - npc_y;
			if(abs(dist_x) < HEAR_RANGE_HALF_WIDTH  && abs(dist_y) < HEAR_RANGE_HALF_HEIGHT )
			{
				play_npc_clash_voice(npc_no, file_index);
			}
            break;
            /*
		case DOING_KIND_MAGIC_NPC:
		case DOING_KIND_MAGIC_POSITION:
		case DOING_KIND_MAGIC_MOVE_TO:
		case DOING_KIND_MAGIC_MOVE_TO_NPC:
			dist_x = hear_x - npc_x;
			dist_y = hear_y - npc_y;
			if(abs(dist_x) < HEAR_RANGE_HALF_WIDTH  && abs(dist_y) < HEAR_RANGE_HALF_HEIGHT )
			{
				// Here file_index is magic_index
				play_magic_start_voice(file_index);
			}
			break;
		case DOING_KIND_MAGIC_ATTACK_NPC:		//use magic broken voice
		case DOING_KIND_MAGIC_ATTACK_LINE:		//use magic broken voice
		case DOING_KIND_MAGIC_ATTACK_CIRCLE:	//use magic broken voice
			dist_x = hear_x - npc_x;
			dist_y = hear_y - npc_y;
			if(abs(dist_x) < HEAR_RANGE_HALF_WIDTH  && abs(dist_y) < HEAR_RANGE_HALF_HEIGHT )
			{
				// Here file_index is magic_index
				play_magic_broken_voice(file_index);
			}
			break;
            */
		default:
			break;
		}
	}
	return;
}
