/*
**	ServerCharacterDoing.cpp
**	server character doing functions.
**
**	Jack, 2002/10/30.
*/
#include "ZoneServer_Def.h"

void    server_set_npc_AI_functions(void)
{
    SLONG   i;
    //初始化npc的AI數據
    InitAiData();
    //
    for (i=0; i<MAX_AI_BLOCK_TYPE; i++)
    {
        SetChangeCharacterAIBlockFun(i, ServerChangeCharacterAiBlock);
    }
    //
	for(i=0; i<MAX_CHARACTER_DOING_KINDS; i++)
	{
        SetChangeCharacterDoingSomethingFun(i,ServerChangeCharacterDoing);
	}
    
}

void    server_set_npc_doing_functions(void)
{
	InitCharacterDoingSomethingFunction();
 
	//陸地NPC的事務類型 --------------------------------------------------------------------
	SetCharacterDoingSomethingFunction(DOING_KIND_IDLE, server_do_npc_idle);
	SetCharacterDoingSomethingFunction(DOING_KIND_STAND, server_do_npc_stand);
	SetCharacterDoingSomethingFunction(DOING_KIND_MUSE, server_do_npc_muse);
	SetCharacterDoingSomethingFunction(DOING_KIND_SPOWER, server_do_npc_spower);
	SetCharacterDoingSomethingFunction(DOING_KIND_CHANGEMAP, server_do_npc_change_map);
	//SetCharacterDoingSomethingFunction(DOING_KIND_FIGHT_IDLE, server_do_npc_fight_idle);
    //
	SetCharacterDoingSomethingFunction(DOING_KIND_MOVE_TO, server_do_npc_move_to);
	//SetCharacterDoingSomethingFunction(DOING_KIND_MAGIC_POSITION, server_do_npc_magic_position);
	SetCharacterDoingSomethingFunction(DOING_KIND_CLASH, server_do_npc_clash);
	//SetCharacterDoingSomethingFunction(DOING_KIND_FIGHT_GAD, server_do_npc_fight_gad);
	//SetCharacterDoingSomethingFunction(DOING_KIND_FIGHT_PATROL, server_do_npc_fight_patrol);
	SetCharacterDoingSomethingFunction(DOING_KIND_SKILL_ACTION, server_do_npc_fight_action);	
    //
	SetCharacterDoingSomethingFunction(DOING_KIND_PICK_ITEM, server_do_npc_pick_item);
    //
	SetCharacterDoingSomethingFunction(DOING_KIND_TALK_WITH_NPC, server_do_npc_talk_with_npc);
	//SetCharacterDoingSomethingFunction(DOING_KIND_ATTACK_NPC, server_do_npc_attack_npc);
	//SetCharacterDoingSomethingFunction(DOING_KIND_MAGIC_NPC, server_do_npc_magic_npc);
	SetCharacterDoingSomethingFunction(DOING_KIND_SEQUENTIAL_ATTACK_NPC, server_do_npc_sequential_attack_npc);
    //
	SetCharacterDoingSomethingFunction(DOING_KIND_BEATED, server_do_npc_beated);
	SetCharacterDoingSomethingFunction(DOING_KIND_DEAD, server_do_npc_dead);
	SetCharacterDoingSomethingFunction(DOING_KIND_DOWN_AND_OUT, server_do_npc_down_and_out);
	SetCharacterDoingSomethingFunction(DOING_KIND_DEFENCE, server_do_npc_defence);
	SetCharacterDoingSomethingFunction(DOING_KIND_DEFENCED, server_do_npc_defenced);
    //
	//SetCharacterDoingSomethingFunction(DOING_KIND_CHEER, server_do_npc_cheer);
	SetCharacterDoingSomethingFunction(DOING_KIND_ANGRY, server_do_npc_angry);
	SetCharacterDoingSomethingFunction(DOING_KIND_BECKON, server_do_npc_beckon);
	//SetCharacterDoingSomethingFunction(DOING_KIND_COURT, server_do_npc_court);
	SetCharacterDoingSomethingFunction(DOING_KIND_FAINT, server_do_npc_faint);
	SetCharacterDoingSomethingFunction(DOING_KIND_SAY_NO, server_do_npc_say_no);
	SetCharacterDoingSomethingFunction(DOING_KIND_BOW, server_do_npc_bow);
	SetCharacterDoingSomethingFunction(DOING_KIND_WIN, server_do_npc_win); 
	SetCharacterDoingSomethingFunction(DOING_KIND_SWASH, server_do_npc_swash);
	SetCharacterDoingSomethingFunction(DOING_KIND_XXPOWER, server_do_npc_xxpower);
	SetCharacterDoingSomethingFunction(DOING_KIND_XXBEATED, server_do_npc_xxbeated);
	//
	//SetCharacterDoingSomethingFunction(DOING_KIND_GAD, server_do_npc_gad);
	//海洋NPC的事務類型 --------------------------------------------------------------------
	SetCharacterDoingSomethingFunction(DOING_KIND_SEA_IDLE, server_do_sea_npc_idle);
	SetCharacterDoingSomethingFunction(DOING_KIND_SEA_SAIL_TO, server_do_sea_npc_sail_to);
	SetCharacterDoingSomethingFunction(DOING_KIND_SEA_WALK_TO, server_do_sea_npc_walk_to);
}


void    server_refresh_one_character(SLONG npc_no)
{
    SLONG   doing_kind;
    SLONG   is_available;
	SLONG	on_pause;
	SLONG	prestige;
	DWORD	heart_beat;

    LOCK_CHARACTER(npc_no);	
    is_available = IsCharacterAvailable(npc_no);
	on_pause = IsCharacterOnPauseState(npc_no);
    doing_kind = GetCharacterDoingKind(npc_no);
	prestige = GetCharacterPrestige(npc_no);
    UNLOCK_CHARACTER(npc_no);	

    if(is_available)
    {
		// 處理玩家聲望,如果小於零,每分鐘 +1 到零為止
		heart_beat = get_heartbeat_times();
		if(heart_beat % 1200 == 0)
		{
			if(prestige < 0)
			{
				prestige++;
				LOCK_CHARACTER(0);
				SetCharacterPrestige(npc_no, prestige);
				UNLOCK_CHARACTER(0);
			}
		}

		// 檢查名字該不該換色
		if(npc_no < 500)
		{			
			CheckNameColorTicks(npc_no);
		}		

        LOCK_CHARACTER(npc_no);
        RefreshCharacterRightHandMagicState(npc_no);
        UNLOCK_CHARACTER(npc_no);

		if(on_pause)
		{
			ExecCharacterPause(npc_no);
		}
		else
		{
		    // mark by lijun 2004-05-19
			//ExecCharacterDoingSomething(npc_no, doing_kind);
			NpcMainAIproc(npc_no);
		}		
    }
}


void    server_refresh_character(void)
{
    SLONG   i;

    for(i = 0; i < 1000; i ++)
    {	
        server_refresh_one_character(i);
    }
}

void	server_save_character_data()
{
	TPOS_DB_CHARACTER			DbCharacter;
	SLONG						is_available;	    	

	LOCK_CHARACTER(0);	
	is_available = IsCharacterAvailable(savecount);
	UNLOCK_CHARACTER(0);	
	if(is_available)
	{
		LOCK_CHARACTER(0);
		ConvertZoneCharacterDataToDBCharacter(savecount, &DbCharacter);		
		UNLOCK_CHARACTER(0);
		// 存物品
		SaveCharacterItemDataByMainNameAndIndex(savecount);
		SaveCharacterBankData(savecount);

		strcpy(DbCharacter.ZoneName, ZoneName);
		UpdateRecordOfCharacterDB(&DbCharacter);		
	}
	savecount++;
	if(savecount == 500)savecount = 0;	
}

void    AbortCharacterDoing(SLONG npc_no)
{
}


void    SetCharacterDoing(SLONG npc_no, SLONG doing_kind, SLONG doing_step, SLONG d1, SLONG d2, SLONG d3, SLONG d4, SLONG d5)
{
    switch(doing_kind)
    {
        //with nothing ------------------------------------
    case DOING_KIND_IDLE:
        SetCharacterDoingKindStep(npc_no, doing_kind, doing_step);
        SetCharacterIdleTicks(npc_no, 0);
        break;

	case DOING_KIND_STAND:
        SetCharacterDoingKindStep(npc_no, doing_kind, doing_step);        
		SetCharacterDir(npc_no, d1);
        break;

    case DOING_KIND_MUSE:
    case DOING_KIND_SPOWER:
        SetCharacterDoingKindStep(npc_no, doing_kind, doing_step);
		SetCharacterDoingMagic(npc_no, (SHINT)d5);
        break;
    /*
    case DOING_KIND_GAD:
        SetCharacterDoingKindStep(npc_no, doing_kind, doing_step);
		SetCharacterDestPosition(npc_no, d1, d2, 0);
        SetCharacterGadTotalTicks(npc_no, d3);
        SetCharacterGadTicks(npc_no, d4);
        break;
    */
    /*
    case DOING_KIND_PATROL:
        SetCharacterDoingKindStep(npc_no, doing_kind, doing_step);
        SetCharacterOrigPosition(npc_no, d1, d2, 0);
        SetCharacterDestPosition(npc_no, d3, d4, 0);
        break;
    */        
    case DOING_KIND_CHANGEMAP:
        SetCharacterDoingKindStep(npc_no, doing_kind, doing_step);
        break;

        //with map position -------------------------------
    case DOING_KIND_MOVE_TO:
    //case DOING_KIND_MAGIC_POSITION:
        SetCharacterDoingKindStep(npc_no, doing_kind, doing_step);
        SetCharacterDestPosition(npc_no, d1, d2, d3);
        SetCharacterDoingMagic(npc_no, (SHINT)d5);
        break;

    case DOING_KIND_CLASH:
        SetCharacterDoingKindStep(npc_no, doing_kind, doing_step);
        SetCharacterDestPosition(npc_no, d1, d2, d3);
        SetCharacterClashSteps(npc_no, d4);
        SetCharacterDoingMagic(npc_no, (SHINT)d5);
        break;

        //with npc -----------------------------------------
    case DOING_KIND_TALK_WITH_NPC:
    //case DOING_KIND_ATTACK_NPC:
    //case DOING_KIND_MAGIC_NPC:
    case DOING_KIND_SEQUENTIAL_ATTACK_NPC:
        SetCharacterDoingKindStep(npc_no, doing_kind, doing_step);
        SetCharacterDestID(npc_no, d1);
        SetCharacterDoingMagic(npc_no, (SHINT)d5);
        break;

        //with map item ---------------------------------
    case DOING_KIND_PICK_ITEM:
        SetCharacterDoingKindStep(npc_no, doing_kind, doing_step);
        SetCharacterDestID(npc_no, d1); //as map_no for client, here is dummy.
        SetCharacterDestPosition(npc_no, d2, d3, 0);    //d2, d3 as item_x, item_y
        SetCharacterDoingMagic(npc_no, (SHINT)d5);
        break;

        //passive ---------------------------------------
    case DOING_KIND_BEATED:         //被擊
    case DOING_KIND_DEAD:           //死亡
    case DOING_KIND_DOWN_AND_OUT:   //被擊倒
    case DOING_KIND_DEFENCE:        //格擋
    case DOING_KIND_DEFENCED:       //被格擋
        SetCharacterDoingKindStep(npc_no, doing_kind, doing_step);
        SetCharacterBeatedBy(npc_no, d1);
        SetCharacterBeatedWith(npc_no, d5);
		SetCharacterBeatedX(npc_no, d3);
		SetCharacterBeatedY(npc_no, d4);
        break;

        //with player's emotions ------------------------
    //case DOING_KIND_CHEER:
    case DOING_KIND_ANGRY:
    case DOING_KIND_BECKON:
    //case DOING_KIND_COURT:
    case DOING_KIND_FAINT:
    case DOING_KIND_SAY_NO:
    case DOING_KIND_BOW:
    case DOING_KIND_WIN:
    case DOING_KIND_SWASH:
    case DOING_KIND_XXPOWER:
    case DOING_KIND_XXBEATED:
        SetCharacterDoingKindStep(npc_no, doing_kind, doing_step);
        break;

		//sea player's doings ---------------------------
    case DOING_KIND_SEA_IDLE:
        SetCharacterDoingKindStep(npc_no, doing_kind, doing_step);
        break;

    case DOING_KIND_SEA_SAIL_TO:
    case DOING_KIND_SEA_WALK_TO:
        SetCharacterDoingKindStep(npc_no, doing_kind, doing_step);
        SetCharacterDestPosition(npc_no, d1, d2, d3);
        break;
    /*
		//npc fight doings --------------------------------
	case DOING_KIND_FIGHT_IDLE:
        SetCharacterDoingKindStep(npc_no, doing_kind, doing_step);
        SetCharacterIdleTicks(npc_no, 0);
		break;
    */		
    /*		
	case DOING_KIND_FIGHT_GAD:
        SetCharacterDoingKindStep(npc_no, doing_kind, doing_step);
		SetCharacterDestPosition(npc_no, d1, d2, 0);
        SetCharacterGadTotalTicks(npc_no, d3);
        SetCharacterGadTicks(npc_no, d4);
		break;
    */		
    /*
	case DOING_KIND_FIGHT_PATROL:
        SetCharacterDoingKindStep(npc_no, doing_kind, doing_step);
        SetCharacterOrigPosition(npc_no, d1, d2, 0);
        SetCharacterDestPosition(npc_no, d3, d4, 0);
		break;
    */		
    case DOING_KIND_SKILL_ACTION:
        // d1   目標npc
        // d2   目標座標x
        // d3   目標座標y
        // d4   目標座標z
        // d5   使用的技能編號 
        SetCharacterDoingKindStep(npc_no, doing_kind, doing_step);
        SetCharacterDestID(npc_no, d1);
        SetCharacterDestPosition(npc_no, d2, d3, d4);
        SetCharacterDoingMagic(npc_no, (SHINT)d5);
        break;		
    default:
        // d1   無特別意義
        // d2   無特別意義
        // d3   無特別意義
        // d4   無特別意義
        // d5   無特別意義        
        SetCharacterDoingKindStep(npc_no, doing_kind, doing_step);
        break;		

    }
}
void    ServerSetCharacterAiBlock(SLONG npc_no, SLONG ai_block, SLONG d1, SLONG d2, SLONG d3, SLONG d4, SLONG d5)
{
    //
    AIBlockChange(npc_no,ai_block);
    SetCharacterDestID(npc_no,d1);
    SetCharacterDestPosition(npc_no, d2, d3, d4);
    SetCharacterDoingMagic(npc_no, (UHINT)d5);
}

void    ServerChangeCharacterDoing(SLONG npc_no, SLONG doing_kind, SLONG doing_step, SLONG d1, SLONG d2, SLONG d3, SLONG d4, SLONG d5)
{
    AbortCharacterDoing(npc_no);
    SetCharacterDoing(npc_no, doing_kind, doing_step, d1, d2, d3, d4, d5);
    //add by lijun 2004-05-19
    //ServerSendChangeNpcDoing(npc_no, doing_kind, doing_step, d1, d2, d3, d4, d5);
}
//
void    ServerChangeCharacterAiBlock(SLONG npc_no, SLONG ai_block, SLONG d1, SLONG d2, SLONG d3, SLONG d4, SLONG d5)
{
    LOCK_CHARACTER(npc_no);
    ServerSetCharacterAiBlock(npc_no, ai_block, d1, d2, d3, d4, d5);
    UNLOCK_CHARACTER(npc_no);    
    //
    ServerSendNpcAIBlock(npc_no, (UHINT)ai_block, d1, d2, d3, d4, (UHINT)d5);
}
//
void    ServerCreateMagicArea(SLONG type, SLONG npc_no, SLONG mx, SLONG my, SLONG magic_no, SLONG magic_level)
{
    SLONG   x, y, z;
    SLONG   dir;
    SLONG   in_of_pos[3];
    //
    if (type)
    {    
        if (IsSkillNeedSelfMagicArea(magic_no, magic_level))
        {
            LOCK_CHARACTER(npc_no);
            GetCharacterPosition(npc_no, &x, &y, &z);
            UNLOCK_CHARACTER(npc_no);
            //
            in_of_pos[0] = mx - x;
            in_of_pos[1] = my - y;
            in_of_pos[2] = 0;
            dir = Vertex2Dir16(in_of_pos);
        }
        else
        {
            x = mx;
            y = my;
            dir = 0;
        }
    }        
    else
    {
        dir = 0;
        x = 0;
        y = 0;
    }
    //
    ServerSendMagicArea(type, dir, x, y, npc_no, magic_no);    
}
//-------------------------------------------------------------------------
//  End.
//-------------------------------------------------------------------------

