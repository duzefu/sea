/*
**      NPC.CPP
**      npc functions.
**
**      ZJian,2000.11.22.
**
*/
#include "MainFun.h"
#include "NetGE_MainFunc.h"
#include "Map.h"
#include "Npc.h"
#include "MapObject.h"
#include "CRange.h"
#include "MainGame.h"
#include "Fight.h"
#include "MouseHand.h"
#include "SGE.h"
#include "ImageRim.h"
#include "ClientMain.h"
#include "PosData.h"
#include "SeaNpc.h"
#include "DoingClient.h"
#include "DoingSeaClient.h"
#include "Media.h"




// DEFINES & STRUCTS //////////////////////////////////////////////////////////////////////////////////////////////////
//
// Define this for use MDA file as npc's object image file.
// Otherwise, we will use the default cak file as npc's object image file.
//
#define	USE_MDA_NPC_OBJECT		1


#ifdef	USE_MDA_NPC_OBJECT
#define	dec_reference_for_npc(id)	dec_reference_for_map_media_object_image(id)
#define	add_reference_for_npc(id)	add_reference_for_map_media_object_image(id)

#else//!USE_MDA_NPC_OBJECT
#define	dec_reference_for_npc(id)	dec_reference_for_map_object_image(id)
#define	add_reference_for_npc(id)	add_reference_for_map_object_image(id)

#endif//USE_MDA_NPC_OBJECT


//
// Talk list of map's npc.
//
typedef struct tagNPC_TALK_LIST 
{
    SLONG   max_talk_npcs;
    SLONG   npc_no[MAX_CHARACTER_PER_ZONE];
} NPC_TALK_LIST, *LPNPC_TALK_LIST;




// G L O B A L S //////////////////////////////////////////////////////////////////////////////////////////////////////
GAME_NPC    game_npc[MAX_CHARACTER_PER_ZONE];
SLONG       game_npc_max = 0;
//
NPC_SHOW        npc_show[MAX_CHARACTER_PER_ZONE];
NPC_TALK_LIST   npc_talk_list;


extern  LONG    g_lPlayerIndex;

// F U N C T I O N S //////////////////////////////////////////////////////////////////////////////////////////////////
int     init_npc(void)
{
    SLONG   result;

    //-------------------------------------------------------
    init_all_game_npc();

    //-------------------------------------------------------
	set_data_file(packed_data_file);
    InitCharacterFileInfo();
    result = LoadCharacterFileInfo("data\\npcfile.ini");
    if(TTN_OK != result)
    {
        log_error(1, "load npc file info failed");
        return  -1;
    }
    //DebugLogCharacterFileInfo();

    //-------------------------------------------------------
	set_data_file(packed_data_file);
    InitSeaCharacterFileInfo();
    result = LoadSeaCharacterFileInfo("data\\seanpcfile.ini");
    if(TTN_OK != result)
    {
        log_error(1, "load sea npc file info failed");
        return  -1;
    }
    //DebugLogCharacterFileInfo();

    //-------------------------------------------------------
	set_data_file(packed_data_file);
    init_sea_npc_track_file_info();
    result = load_sea_npc_track_file_info();
    if(TTN_OK != result)
    {
        log_error(1, "load sea npc track file info failed");
        return  -1;
    }
    debug_log_sea_npc_track_file_info();

    //-------------------------------------------------------
	IniMiscMath();
	//DebugLogShipMath();

    //-------------------------------------------------------
	set_data_file(packed_data_file);
	InitCharacterDoingPriority();
    if(TTN_OK != LoadCharacterDoingPriority("data\\doingpri.ini"))
    {
        log_error(1, "load npc doing priority failed");
        return  -2;
    }
    //DebugLogCharacterDoingPriority();

    //-------------------------------------------------------
    init_npc_talk_list();

    //-------------------------------------------------------

    return  0;
}


void    active_npc(int active)
{
}


void    free_npc(void)
{
	FreeCharacterFileInfo();
    FreeCharacterDoingPriority();
}


void    init_all_game_npc(void)
{
    SLONG i;

    for(i=0; i<MAX_CHARACTER_PER_ZONE; i++)
    {
        init_one_game_npc(i);
    }
    game_npc_max = 0;
}


void    init_one_game_npc(SLONG npc_no)
{
	SetCharacterImageID(npc_no, INVALID_OBJECT_ID);
	SetCharacterHp(npc_no, 1);
	SetCharacterDoingKindStep(npc_no, DOING_KIND_IDLE, 0);
	SetCharacterFrame(npc_no, 0);

	set_npc_flag(npc_no, 0);
	set_npc_object_index(npc_no, -1);
    set_npc_ext_id(npc_no, INVALID_OBJECT_ID);
    set_npc_ext_frame(npc_no, 0);
}


void    clear_one_game_npc(SLONG npc_no)
{
    SetCharacterImageID(npc_no, INVALID_OBJECT_ID);
	SetCharacterDoingKindStep(npc_no, DOING_KIND_IDLE, 0);
    SetCharacterFrame(npc_no, 0);

    memset(&game_npc[npc_no], 0x00, sizeof(GAME_NPC));
	set_npc_flag(npc_no, 0);
	set_npc_object_index(npc_no, -1);
    set_npc_ext_id(npc_no, INVALID_OBJECT_ID);
    set_npc_ext_frame(npc_no, 0);
    set_npc_effect(npc_no, OBJECT_NORMAL_IMAGE);
}


void    clear_npc_ext_effect(SLONG npc_no)
{
    game_npc[npc_no].ext_id = INVALID_OBJECT_ID;
    game_npc[npc_no].ext_frame = 0;
    //
    game_npc[npc_no].foot_id = INVALID_OBJECT_ID;
    game_npc[npc_no].foot_frame = 0;
    //--------------------------------------------------------------------
    game_npc[npc_no].head_id = INVALID_OBJECT_ID;
    game_npc[npc_no].head_frame = 0;
    //--------------------------------------------------------------------
    game_npc[npc_no].body_front_id = INVALID_OBJECT_ID;
    game_npc[npc_no].body_back_id = INVALID_OBJECT_ID;
    game_npc[npc_no].body_frame = 0;
}


void    refresh_map_npc(void)
{
    SLONG   npc_no, flag;

    for(npc_no = 0; npc_no < game_npc_max; npc_no ++)
    {
        LOCK_CHARACTER(npc_no);
        flag = get_npc_flag(npc_no);
        UNLOCK_CHARACTER(npc_no);

        if(flag & NPC_USED)
        {
            refresh_one_npc(npc_no);
        }
    }
}


void    refresh_one_npc(SLONG npc_no)
{
    SLONG   doing_kind, on_pause;

	LOCK_CHARACTER(npc_no);
	doing_kind = GetCharacterDoingKind(npc_no);
	on_pause = IsCharacterOnPauseState(npc_no);
	UNLOCK_CHARACTER(npc_no);

    refresh_npc_state_lapse(npc_no);

	LOCK_CHARACTER(npc_no);
    RefreshCharacterRightHandMagicState(npc_no);
	UNLOCK_CHARACTER(npc_no);

	if(on_pause)
	{
		ExecCharacterPause(npc_no);
	}
	else
	{
	    // mark by lijun 2003-05-19
		//ExecCharacterDoingSomething(npc_no, doing_kind);
		//把npc的行為處理轉為AI控制
        NpcMainAIproc(npc_no);
	}
	return;
}


void    refresh_npc_state_lapse(SLONG npc_no)
{
    refresh_npc_foot_speed_state(npc_no);
    // Jack, todo: [16:54,9/24/2002]
}


void    debug_show_map_npc_data(SLONG npc_no, BMP *bitmap)
{
    static USTR dir_str[8][8] = { "UP","DN","LT","RT","RU","LD","LU","RD" };
    SLONG	sx, sy;
	SLONG	x, y, z, dir;

	GetCharacterPosition(npc_no, &x, &y, &z);
	dir = GetCharacterDir(npc_no);

    sx = 4;
    sy = 4;
    sprintf((char *)print_rec,"~C0~O3FPS = %d~C0~O0", get_fps());
    print16(sx,sy,(USTR*)print_rec,PEST_PUT,bitmap);
    sy += 20;

    sprintf((char *)print_rec,"~C0~O3POS = (%d, %d, %d)~C0~O0", x, y, z);
    print16(sx,sy,(USTR*)print_rec,PEST_PUT,bitmap);
    sy += 20;

    sprintf((char *)print_rec,"~C0~O3DIR = %s~C0~O0", dir_str[dir]);
    print16(sx,sy,(USTR*)print_rec,PEST_PUT,bitmap);
    sy += 20;
}


void    update_map_npc_object(void)
{
    SLONG   i, npc_no;
    SLONG   object_index, object_id;
    SLONG   flag, id, frame;
    SLONG   x, y, z, effect, hp, max_hp;
    SLONG   with_shadow;
    //
    SLONG   ext_id, ext_frame;
    //
    SLONG   foot_id,foot_frame;
    SLONG   head_id,head_frame;
    SLONG   body_front_id,body_frame;
    SLONG   body_back_id;

    //update & refresh map npc objects.
    for(i=0; i<game_npc_max; i++)
    {
        npc_no = i;

        LOCK_CHARACTER(npc_no);
        flag = get_npc_flag(npc_no);
        object_index = get_npc_object_index(npc_no);
        effect = get_npc_effect(npc_no);        
        //
        ext_id      = get_npc_ext_id(npc_no);
        ext_frame   = get_npc_ext_frame(npc_no);
        foot_id     = get_npc_foot_id(npc_no);
        foot_frame  = get_npc_foot_frame(npc_no);
        head_id     = get_npc_head_id(npc_no);
        head_frame  = get_npc_head_frame(npc_no);
        body_front_id=get_npc_body_front_id(npc_no);
        body_back_id= get_npc_body_back_id(npc_no);
        body_frame  = get_npc_body_frame(npc_no);
        //
        //
        id = GetCharacterImageID(npc_no);
        frame = GetCharacterFrame(npc_no);
		GetCharacterPosition(npc_no, &x, &y, &z);
		hp = GetCharacterHp(npc_no);
		max_hp = GetCharacterMaxHp(npc_no);
        with_shadow = IsCharacterDodge(npc_no);
        UNLOCK_CHARACTER(npc_no);

		npc_show[npc_no].flag = 0;
        if(flag & NPC_USED)
        {
			update_npc_show_shadow_move(npc_no, x, y, z, with_shadow);
			npc_show[npc_no].flag |= NPC_SHOW_ENABLE_VIEW;
			if( (npc_no != g_lPlayerIndex) && (hp > 0) )
			{
				npc_show[npc_no].flag |= NPC_SHOW_ENABLE_RANGE;
			}

            //update npc's id --------------------------------
			if(object_index < 0)
			{
				object_index = add_map_npc_object(id, x, y, z, OBJECT_NORMAL_IMAGE, npc_no);
				if(object_index >= 0)
				{
					LOCK_CHARACTER(npc_no);
					game_npc[npc_no].object_index = object_index;
					UNLOCK_CHARACTER(npc_no);
					
					map_object[object_index].effect = effect;
					map_object[object_index].frame = frame;
					map_object[object_index].flag |= MOBJ_UPDATE_NPC;
					if(flag & NPC_DIED)
					{
						map_object[object_index].flag |= MOBJ_UNDER;
					}
				}
			}
			else
			{
				object_id = map_object[object_index].id;
				if(object_id != id)
				{
					change_map_npc_object_id(object_index, id);
				}
				
				map_object[object_index].px = x;
				map_object[object_index].py = y;
				map_object[object_index].pz = z;
				map_object[object_index].effect = effect; 
				
				map_object[object_index].frame = frame;
				map_object[object_index].flag |= MOBJ_UPDATE_NPC;
				if(flag & NPC_DIED)
				{
					map_object[object_index].flag |= MOBJ_UNDER;
				}
			}

            //update npc's ext_id
            //npc特殊效果圖檔的管理
            npc_effect_id_manage(&(game_npc[npc_no].ext_id),
                                 &(npc_show[npc_no].ext_id),
                                 &(game_npc[npc_no].ext_frame),
                                 &(npc_show[npc_no].ext_frame));
            // mark by lijun 2003-04-08
            /*
            if(ext_id != INVALID_OBJECT_ID)
            {
                show_ext_id = get_npc_show_ext_id(npc_no);
                if(show_ext_id == INVALID_OBJECT_ID)
                {
                    add_reference_for_map_object_image(ext_id);
                    set_npc_show_ext_id(npc_no, ext_id);
                    set_npc_show_ext_frame(npc_no, ext_frame);
                }
                else if(show_ext_id != ext_id)
                {
                    dec_reference_for_map_object_image(show_ext_id);
                    add_reference_for_map_object_image(ext_id);
                    set_npc_show_ext_id(npc_no, ext_id);
                    set_npc_show_ext_frame(npc_no, ext_frame);
                }
                else
                {
                    set_npc_show_ext_frame(npc_no, ext_frame);
                }
            }
            else //從內存中釋放特殊效果圖檔
            {
                show_ext_id = get_npc_show_ext_id(npc_no);
                if(show_ext_id != INVALID_OBJECT_ID)
                {
                    dec_reference_for_map_object_image(show_ext_id);
                    set_npc_show_ext_id(npc_no, INVALID_OBJECT_ID);
                    set_npc_show_ext_frame(npc_no, 0);
                }
            }
            */
            //頭上圖檔效果的管理
            npc_effect_id_manage(&(game_npc[npc_no].head_id),
                                 &(npc_show[npc_no].head_id),
                                 &(game_npc[npc_no].head_frame),
                                 &(npc_show[npc_no].head_frame));

            //腳下圖檔效果的管理
            npc_effect_id_manage(&(game_npc[npc_no].foot_id),
                                 &(npc_show[npc_no].foot_id),
                                 &(game_npc[npc_no].foot_frame),
                                 &(npc_show[npc_no].foot_frame));
            
            //身上圖檔效果的管理
            npc_effect_id_manage(&(game_npc[npc_no].body_front_id),
                                 &(npc_show[npc_no].body_front_id),
                                 &(game_npc[npc_no].body_frame),
                                 &(npc_show[npc_no].body_frame));
            npc_effect_id_manage(&(game_npc[npc_no].body_back_id),
                                 &(npc_show[npc_no].body_back_id),
                                 &(game_npc[npc_no].body_frame),
                                 &(npc_show[npc_no].body_frame));
        }
    }

    //cleanup dead map npc objects.
    for(i = 0; i < map_object_max; i++)
    {
        flag = map_object[i].flag;
        if( (flag & MOBJ_ACTIVE) && ((flag & MOBJ_TYPES) == MOBJ_NPC) )
        {
            if(flag & MOBJ_UPDATE_NPC)
            {
                map_object[i].flag &= ~MOBJ_UPDATE_NPC;
            }
            else
            {
                //刪除npc的圖檔
                del_map_npc_object(i);

                //刪除npc的附加效果圖檔
                npc_no = map_object[i].npc_no;

                LOCK_CHARACTER(npc_no);
                game_npc[npc_no].ext_id = INVALID_OBJECT_ID;
                game_npc[npc_no].ext_frame = 0;
                //
                game_npc[npc_no].foot_id = INVALID_OBJECT_ID;
                game_npc[npc_no].foot_frame = 0;
                game_npc[npc_no].head_id = INVALID_OBJECT_ID;
                game_npc[npc_no].head_frame = 0;
                game_npc[npc_no].body_front_id = INVALID_OBJECT_ID;
                game_npc[npc_no].body_back_id = INVALID_OBJECT_ID;
                game_npc[npc_no].body_frame = 0;
                //
                UNLOCK_CHARACTER(npc_no);
                //身上的附加效果
                ext_id = get_npc_show_ext_id(npc_no);
                if(ext_id != INVALID_OBJECT_ID)
                {
                    dec_reference_for_map_object_image(ext_id);
                    set_npc_show_ext_id(npc_no, INVALID_OBJECT_ID);
                    set_npc_show_ext_frame(npc_no, 0);
                }
                //頭上的效果
                head_id = get_npc_show_head_id(npc_no);
                if(head_id != INVALID_OBJECT_ID)
                {
                    dec_reference_for_map_object_image(head_id);
                    set_npc_show_head_id(npc_no, INVALID_OBJECT_ID);
                    set_npc_show_head_frame(npc_no, 0);
                }
                //腳上的效果
                foot_id = get_npc_show_foot_id(npc_no);
                if(foot_id != INVALID_OBJECT_ID)
                {
                    dec_reference_for_map_object_image(foot_id);
                    set_npc_show_foot_id(npc_no, INVALID_OBJECT_ID);
                    set_npc_show_foot_frame(npc_no, 0);
                }
                //身體的效果
                body_front_id = get_npc_show_body_front_id(npc_no);
                if(body_front_id != INVALID_OBJECT_ID)
                {
                    dec_reference_for_map_object_image(body_front_id);
                    set_npc_show_body_front_id(npc_no, INVALID_OBJECT_ID);
                    set_npc_show_body_frame(npc_no, 0);
                }
                //
                body_back_id = get_npc_show_body_back_id(npc_no);
                if(body_back_id != INVALID_OBJECT_ID)
                {
                    dec_reference_for_map_object_image(body_back_id);
                    set_npc_show_body_back_id(npc_no, INVALID_OBJECT_ID);
                    set_npc_show_body_frame(npc_no, 0);
                }
                
            }
        }
    }
}


/////////////////////////////////////////////////////////////////////////////////////////////////////
void    active_map_npc(SLONG npc_no)
{
    if(npc_no >= 0)
    {
        game_npc[npc_no].flag = NPC_USED;
        if(game_npc_max <= npc_no)
        {
            game_npc_max = npc_no + 1;
        }
    }
}


void    del_map_npc(SLONG npc_no)
{
    if(npc_no >= 0 && npc_no < MAX_CHARACTER_PER_ZONE)
    {
        game_npc[npc_no].flag = 0;
        game_npc[npc_no].object_index = -1;
    }
}


void    clear_all_map_npc(void)
{
    SLONG   npc_no;

    for(npc_no = 0; npc_no < MAX_CHARACTER_PER_ZONE; npc_no ++)
    {
		clear_one_game_npc(npc_no);
    }
    game_npc_max = 0;
}


void    set_npc_doing(SLONG npc_no, SLONG doing_kind, SLONG doing_step, SLONG d1, SLONG d2, SLONG d3, SLONG d4, SLONG d5)
{
    switch(doing_kind)
    {
        //with nothing ------------------------------------
    case DOING_KIND_IDLE:
        // d1   無特別意義
        // d2   無特別意義
        // d3   無特別意義
        // d4   無特別意義
        // d5   無特別意義
        SetCharacterDoingKindStep(npc_no, doing_kind, doing_step);
		SetCharacterIdleTicks(npc_no, 0);
        break;
	case DOING_KIND_STAND:
        // d1   無特別意義
        // d2   無特別意義
        // d3   無特別意義
        // d4   無特別意義
        // d5   無特別意義	
		SetCharacterDoingKindStep(npc_no, doing_kind, doing_step);
		SetCharacterDir(npc_no, d1);
		break;
    case DOING_KIND_MUSE:
    case DOING_KIND_SPOWER:
        // d1   無特別意義
        // d2   無特別意義
        // d3   無特別意義
        // d4   無特別意義
        // d5   無特別意義    
        SetCharacterDoingKindStep(npc_no, doing_kind, doing_step);
        SetCharacterDoingMagic(npc_no, (SHINT)d5);
        break;
    /*
    case DOING_KIND_GAD:
        // d1   移動目標座標 x
        // d2   移動目標座標 y
        // d3   閒蕩的間隔時間
        // d4   閒蕩但前的時間計數
        // d5   無特別意義    
        SetCharacterDoingKindStep(npc_no, doing_kind, doing_step);
		SetCharacterDestPosition(npc_no, d1, d2, 0);
        SetCharacterGadTotalTicks(npc_no, d3);
        SetCharacterGadTicks(npc_no, d4);
        break;
    */        
    /*
    case DOING_KIND_PATROL:
        // d1   巡邏的源座標 x
        // d2   巡邏的源座標 y
        // d3   巡邏的目標座標  x
        // d4   巡邏的目標座標  y
        // d5   無特別意義    
        SetCharacterDoingKindStep(npc_no, doing_kind, doing_step);
        SetCharacterOrigPosition(npc_no, d1, d2, 0);
        SetCharacterDestPosition(npc_no, d3, d4, 0);
        break;
    */        
    case DOING_KIND_CHANGEMAP:
        // d1   無特別意義
        // d2   無特別意義
        // d3   無特別意義
        // d4   無特別意義
        // d5   無特別意義
        SetCharacterDoingKindStep(npc_no, doing_kind, doing_step);
        break;

        //with map position -------------------------------
    case DOING_KIND_MOVE_TO:
    //case DOING_KIND_MAGIC_POSITION:
        // d1   移動到的目標座標  x
        // d2   移動到的目標座標  y
        // d3   移動到的目標座標  z
        // d4   無特別意義
        // d5   但前使用的技能
        SetCharacterDoingKindStep(npc_no, doing_kind, doing_step);
        SetCharacterDestPosition(npc_no, d1, d2, d3);
        SetCharacterDoingMagic(npc_no, (SHINT)d5);
        break;
    case DOING_KIND_CLASH:
        // d1   移動到的目標座標  x
        // d2   移動到的目標座標  y
        // d3   移動到的目標座標  z
        // d4   經過的步數
        // d5   但前使用的技能
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
        // d1   目標npc
        // d2   無特別意義
        // d3   無特別意義
        // d4   無特別意義
        // d5   但前使用的技能
        SetCharacterDoingKindStep(npc_no, doing_kind, doing_step);
        SetCharacterDestID(npc_no, d1);    //as dest_npc
        SetCharacterDoingMagic(npc_no, (SHINT)d5);
        break;

        //with map item ---------------------------------
    case DOING_KIND_PICK_ITEM:
        // d1   目標npc
        // d2   目標座標x
        // d3   目標座標y
        // d4   目標座標z
        // d5   但前使用的技能
        SetCharacterDoingKindStep(npc_no, doing_kind, doing_step);
        SetCharacterDestID(npc_no, d1);    //as map_no
        SetCharacterDestPosition(npc_no, d2, d3, 0);   //d2,d3 as item_x, item_y
        SetCharacterDoingMagic(npc_no, (SHINT)d5);
        break;

        //passive ---------------------------------------
    case DOING_KIND_BEATED:         //被擊
    case DOING_KIND_DEAD:           //死亡
    case DOING_KIND_DOWN_AND_OUT:   //被擊倒
    case DOING_KIND_DEFENCE:        //格擋
    case DOING_KIND_DEFENCED:       //被格擋
        // d1   攻擊的源npc
        // d2   被攻擊所使用的技能
        // d3   攻擊者的座標x
        // d4   攻擊者的座標y
        // d5   無特別意義    
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
        // d1   無特別意義
        // d2   無特別意義
        // d3   無特別意義
        // d4   無特別意義
        // d5   無特別意義    
        SetCharacterDoingKindStep(npc_no, doing_kind, doing_step);
        break;

		//sea doing functions -------------------------------------
	case DOING_KIND_SEA_ACC_MOVE_TO:
        // d1   目標座標x
        // d2   目標座標y
        // d3   目標座標z
        // d4   無特別意義
        // d5   無特別意義	
        SetCharacterDoingKindStep(npc_no, doing_kind, doing_step);
        SetCharacterDestPosition(npc_no, d1, d2, d3);
		break;
    case DOING_KIND_SEA_IDLE:
        // d1   無特別意義
        // d2   無特別意義
        // d3   無特別意義
        // d4   無特別意義
        // d5   無特別意義        
        SetCharacterDoingKindStep(npc_no, doing_kind, doing_step);
        break;
    case DOING_KIND_SEA_SAIL_TO:
    case DOING_KIND_SEA_WALK_TO:
        // d1   目標座標x
        // d2   目標座標y
        // d3   目標座標z
        // d4   無特別意義
        // d5   無特別意義        
        SetCharacterDoingKindStep(npc_no, doing_kind, doing_step);
        SetCharacterDestPosition(npc_no, d1, d2, d3);
        break;
    /*
		//fight functions -----------------------------------------
	case DOING_KIND_FIGHT_IDLE:
        // d1   無特別意義
        // d2   無特別意義
        // d3   無特別意義
        // d4   無特別意義
        // d5   無特別意義        	
        SetCharacterDoingKindStep(npc_no, doing_kind, doing_step);
        SetCharacterIdleTicks(npc_no, 0);
		break;
    */		
    /*		
	case DOING_KIND_FIGHT_GAD:
        // d1   目標座標x
        // d2   目標座標y
        // d3   時間間隔
        // d4   時間計數
        // d5   無特別意義        	
        SetCharacterDoingKindStep(npc_no, doing_kind, doing_step);
		SetCharacterDestPosition(npc_no, d1, d2, 0);
        SetCharacterGadTotalTicks(npc_no, d3);
        SetCharacterGadTicks(npc_no, d4);
		break;
    */		
    /*    
	case DOING_KIND_FIGHT_PATROL:
        // d1   源座標x
        // d2   源座標y
        // d3   目標座標x
        // d4   目標座標y
        // d5   無特別意義        		
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


void    abort_npc_doing(SLONG npc_no)
{
    SLONG   doing_kind;

    doing_kind = GetCharacterDoingKind(npc_no);
    switch(doing_kind)
    {
    case DOING_KIND_CLASH:  //衝撞的時候有陰影效果, 所以, 終止時需要去掉.
        SetCharacterDodge(npc_no, false);
        break;
    case DOING_KIND_BEATED: //去掉被擊時的附加效果
        game_npc[npc_no].ext_id = INVALID_OBJECT_ID;
        game_npc[npc_no].ext_frame = 0;
        break;
    case DOING_KIND_SPOWER: //去掉蓄力時的附加效果
        game_npc[npc_no].ext_id = INVALID_OBJECT_ID;
        game_npc[npc_no].ext_frame = 0;
        break;
    default:
        break;
    }
}


void    change_npc_doing(SLONG npc_no, SLONG doing_kind, SLONG doing_step, SLONG d1, SLONG d2, SLONG d3, SLONG d4, SLONG d5)
{
    abort_npc_doing(npc_no);
    set_npc_doing(npc_no, doing_kind, doing_step, d1, d2, d3, d4, d5);
}


SLONG   get_npc_magic_standpoint_relation( SLONG src_npc, SLONG dest_npc)
{
    SLONG   relation;

    //check src_npc and dest_npc's relation by their kind.
    //TODO:
    relation = RELATION_NEUTRAL;
    return  relation;
}

/******************************************************************************************************************/
/* NPC SHOW FUNCTIONS                                                                                             */
/******************************************************************************************************************/
void    init_npc_show(void)
{
    SLONG   i;

    for(i=0; i<MAX_CHARACTER_PER_ZONE; i++)
    {
        npc_show[i].flag = 0;
        npc_show[i].ext_id = INVALID_OBJECT_ID;
        npc_show[i].ext_frame = 0;
        //
        npc_show[i].foot_id = INVALID_OBJECT_ID;
        npc_show[i].foot_frame = 0;
        //
        npc_show[i].head_id = INVALID_OBJECT_ID;
        npc_show[i].head_frame = 0;
        //
        npc_show[i].body_front_id = INVALID_OBJECT_ID;
        npc_show[i].body_back_id = INVALID_OBJECT_ID;
        npc_show[i].body_frame = 0;
    }
}


void    update_npc_show_shadow_move(SLONG index, SLONG x, SLONG y, SLONG z, SLONG with_shadow)
{
    SLONG   i;

	//保存NPC當前座標, 已備後續使用和上圖
	npc_show[index].last_x = x;
	npc_show[index].last_y = y;
	npc_show[index].last_z = z;

	//開始進行SHADOW運算
    if(npc_show[index].with_shadow)
    {
        if(with_shadow)
        {/* 如果已經在殘影狀態, 而且繼續殘影, 則依次更新殘影座標 */
            for(i=MAX_SHOW_SHADOWS - 1; i>0; i--)
            {
                npc_show[index].shadow_x[i] = npc_show[index].shadow_x[i-1];
                npc_show[index].shadow_y[i] = npc_show[index].shadow_y[i-1];
                npc_show[index].shadow_z[i] = npc_show[index].shadow_z[i-1];
            }
            npc_show[index].shadow_x[0] = npc_show[index].last_x;
            npc_show[index].shadow_y[0] = npc_show[index].last_y;
            npc_show[index].shadow_z[0] = npc_show[index].last_z;
            
        }
        else
        {/* 如果已經在殘影狀態, 但是需要取消殘影, 則待所有座標都到達後停止殘影 */
            if(npc_show[index].shadow_x[MAX_SHOW_SHADOWS-1] == npc_show[index].last_x &&
                npc_show[index].shadow_y[MAX_SHOW_SHADOWS-1] == npc_show[index].last_y &&
                npc_show[index].shadow_z[MAX_SHOW_SHADOWS-1] == npc_show[index].last_z)
            {
                npc_show[index].with_shadow = false;
            }
            else
            {
                for(i=MAX_SHOW_SHADOWS-1; i>0; i--)
                {
                    npc_show[index].shadow_x[i] = npc_show[index].shadow_x[i-1];
                    npc_show[index].shadow_y[i] = npc_show[index].shadow_y[i-1];
                    npc_show[index].shadow_z[i] = npc_show[index].shadow_z[i-1];
                }
                npc_show[index].shadow_x[0] = npc_show[index].last_x;
                npc_show[index].shadow_y[0] = npc_show[index].last_y;
                npc_show[index].shadow_z[0] = npc_show[index].last_z;
            }
        }
    }
    else
    {
        if(with_shadow)
        {/* 如果以前不是殘影狀態, 而現在需要加上殘影, 則初始化座標 */
            for(i=0; i<MAX_SHOW_SHADOWS; i++)
            {
                npc_show[index].shadow_x[i] = npc_show[index].last_x;
                npc_show[index].shadow_y[i] = npc_show[index].last_y;
                npc_show[index].shadow_z[i] = npc_show[index].last_z;
            }
            npc_show[index].with_shadow = true;
        }
    }
}


/******************************************************************************************************************/
/* NPC TALK FUNCTIONS                                                                                             */
/******************************************************************************************************************/
void    clear_npc_talk(SLONG npc_no)
{
    GAME_NPC *npc = &game_npc[npc_no];
    SLONG  i;

    npc->talk_flags = 0;
    npc->talk_time = 0;
    npc->talk_lines = 0;
    for(i=0; i<NPC_TALK_NUM; i++)
    {
        memset(&npc->talk_text[i][0], 0, NPC_TALK_LEN+4);
    }
}


SLONG   add_npc_talk(SLONG npc_no, DWORD talk_time, USTR* text)
{
    GAME_NPC *npc = &game_npc[npc_no];
    SLONG   i;

    npc->talk_flags = NPC_TALK_IS_DIALOG;
    npc->talk_time = talk_time;
    if(npc->talk_lines == NPC_TALK_NUM)
    {
        for(i=0; i<NPC_TALK_NUM-1; i++)
        {
            memcpy(npc->talk_text[i], npc->talk_text[i+1], NPC_TALK_LEN+4);
        }
        memset(npc->talk_text[NPC_TALK_NUM-1], 0, NPC_TALK_LEN+4);
        npc->talk_lines--;
    }
    strcpy((char *)npc->talk_text[npc->talk_lines], (const char *)text);
    npc->talk_lines++;
    return  TTN_OK;
}


void    redraw_npc_talk(SLONG top_cx, SLONG top_cy, SLONG npc_no, BMP *bitmap)
{
    enum 
    {   TALK_FONT_WIDTH     =   12,
    TALK_FONT_HEIGHT        =   12,
    TALK_FONT_LINE_HEIGHT   =   TALK_FONT_HEIGHT + 3,
    };
    GAME_NPC *npc = &game_npc[npc_no];
    SLONG   sx, sy, xl, yl;
    SLONG   i;
    USTR    info[64];
    SLONG   exist_icon;
    USTR    npc_name[32];
    USTR    talk_text[NPC_TALK_NUM][NPC_TALK_LEN+4];
    SLONG   talk_max;

    if(npc->talk_flags == 0)
        return;
    if(npc->talk_lines <= 0)
        return;

    sx = top_cx - NPC_TALK_LEN * (TALK_FONT_WIDTH / 2) / 2;
    sy = top_cy - (NPC_TALK_NUM + 1)* TALK_FONT_LINE_HEIGHT;    //+1 for line of npc's name.
    xl = (NPC_TALK_LEN) * (TALK_FONT_WIDTH/2);
    yl = (npc->talk_lines + 1)* TALK_FONT_LINE_HEIGHT; //+1 is for the line of npc's name
    put_talk_rim(sx + TALK_FONT_WIDTH/2, sy + TALK_FONT_WIDTH/2, xl - TALK_FONT_WIDTH, 
        yl - TALK_FONT_LINE_HEIGHT, bitmap);

    LOCK_CHARACTER(npc_no);
    strcpy((char *)npc_name, (const char *)GetCharacterMainName(npc_no));
    talk_max = get_npc_talk_lines(npc_no);
    for(i=0; i<talk_max; i++)
    {
        strcpy((char *)&talk_text[i][0], (const char *)get_npc_talk_text(npc_no, i));
    }
    UNLOCK_CHARACTER(npc_no);

    // Jack, todo: need to check is exist icon later. [22:31,10/28/2002]
    exist_icon = false;
    if(exist_icon)
    {
        //icon ------------------------
        put_box(sx+2, sy - 8, 20, 20, SYSTEM_WHITE, bitmap);
        
        //name ------------------------
        sprintf((char *)info, "~C3~O7%s:~C0~O0", npc_name);
        print12(sx + 24, sy, (USTR*)info, PEST_PUT, bitmap);
    }
    else
    {
        //name ------------------------
        sprintf((char *)info, "~C3~O7%s:~C0~O0", npc_name);
        print12(sx, sy, (USTR*)info, PEST_PUT, bitmap);
    }
    sy += TALK_FONT_LINE_HEIGHT;

    for(i=0; i<talk_max; i++)
    {
        sprintf((char *)info, (const char *)talk_text[i]);
        print12(sx, sy + TALK_FONT_LINE_HEIGHT * i, (USTR*)info, PEST_PUT, bitmap);
    }
}



void    redraw_npc_name(SLONG top_cx, SLONG top_cy, SLONG npc_no, BMP *bitmap)
{
    SLONG   sx, sy;
    SLONG   len, color_index;
	ULONG	u4_color;
    PIXEL   color;
    USTR    name[32];
    
    LOCK_CHARACTER(npc_no);
    strcpy((char *)name, (const char *)GetCharacterMainName(npc_no));
	color_index = GetCharacterMainNameColor(npc_no);
    UNLOCK_CHARACTER(npc_no);
    
    len = strlen((const char *)name);
    sx = top_cx - len * 4;
    sy = top_cy;

    u4_color = GameIndexColorToTrueColor(color_index);
    color = true2hi(u4_color);
    
    set_word_color(0, color);
    print16(sx, sy, (USTR*)"~C0~O0", PEST_PUT, bitmap);
    print16(sx, sy, (USTR*)name, PEST_PUT, bitmap);
    print16(sx, sy, (USTR*)"~C0~O0", PEST_PUT, bitmap);
    set_word_color(0, SYSTEM_WHITE);
}



void    local_refresh_npc_talk(void)
{
    DWORD   curr_time, talk_time;
    SLONG   npc_no, npc_flag, talk_flag;

    curr_time = timeGetTime();
    for(npc_no = 0; npc_no < game_npc_max; npc_no ++)
    {
        LOCK_CHARACTER(npc_no);
        npc_flag = get_npc_flag(npc_no);
        talk_flag = get_npc_talk_flag(npc_no);
        talk_time = get_npc_talk_time(npc_no);
        if(npc_flag && talk_flag)
        {
            if(curr_time - talk_time > 8000)
            {
                clear_npc_talk(npc_no);
            }
        }
        UNLOCK_CHARACTER(npc_no);
    }
}


/******************************************************************************************************************/
/* NPC TALK LIST FUNCTIONS                                                                                        */
/******************************************************************************************************************/
void    init_npc_talk_list(void)
{
    memset(&npc_talk_list, 0, sizeof(npc_talk_list));
}


void    clear_npc_talk_list(void)
{
    npc_talk_list.max_talk_npcs = 0;
}


void    add_npc_to_npc_talk_list(SLONG npc_no)
{
    npc_talk_list.npc_no[npc_talk_list.max_talk_npcs++] = npc_no;
}


void    sort_npc_talk_list(void)
{
    SLONG   i, j, npc_no1, npc_no2;
    DWORD   talk_time1, talk_time2;

    for(i=0; i<npc_talk_list.max_talk_npcs; i++)
    {
        for(j=i; j<npc_talk_list.max_talk_npcs; j++)
        {
            npc_no1 = npc_talk_list.npc_no[i];
            npc_no2 = npc_talk_list.npc_no[j];
            talk_time1 = get_npc_talk_time(npc_no1);
            talk_time2 = get_npc_talk_time(npc_no2);
            if(talk_time2 < talk_time1)
            {
                npc_talk_list.npc_no[i] = npc_no2;
                npc_talk_list.npc_no[j] = npc_no1;
            }
        }
    }
}


void    redraw_map_npc_talk(SLONG map_no, SLONG map_sx, SLONG map_sy, BMP *bitmap)
{
    SLONG   i, npc_no, talk_sx, talk_sy, talk_flag;
    SLONG   show_npc_name_flag;

    sort_npc_talk_list();
    show_npc_name_flag = get_game_config_show_npc_name();

    if(show_npc_name_flag)
    {
        for(i=0; i<npc_talk_list.max_talk_npcs; i++)
        {
            npc_no = npc_talk_list.npc_no[i];
			get_npc_talk_position(npc_no, &talk_sx, &talk_sy);
            talk_flag = get_npc_talk_flag(npc_no);
            switch(talk_flag)
            {
            case NPC_TALK_IS_DIALOG:
                redraw_npc_talk(talk_sx, talk_sy, npc_no, bitmap);
                break;
            case NPC_TALK_IS_NAME:
                redraw_npc_name(talk_sx, talk_sy, npc_no, bitmap);
                break;
            }
        }
    }
    else
    {
        for(i=0; i<npc_talk_list.max_talk_npcs; i++)
        {
            npc_no = npc_talk_list.npc_no[i];
			get_npc_talk_position(npc_no, &talk_sx, &talk_sy);
            talk_flag = get_npc_talk_flag(npc_no);
            switch(talk_flag)
            {
            case NPC_TALK_IS_DIALOG:
                redraw_npc_talk(talk_sx, talk_sy, npc_no, bitmap);
                break;
            case NPC_TALK_IS_NAME:
                break;
            }
        }
    }
}


/******************************************************************************************************************/
/* UI NPC FUNCTIONS                                                                                               */
/******************************************************************************************************************/
void    refresh_ui_npc(void)
{
    SLONG   npc_no, flag, doing_kind;

    for(npc_no = 0; npc_no < game_npc_max; npc_no ++)
    {
        flag = game_npc[npc_no].flag;
        if(flag)
        {
            doing_kind = GetCharacterDoingKind(npc_no);
			ExecCharacterDoingSomething(npc_no, doing_kind);
        }
    }
}


void    ui_redraw_one_npc_object(SLONG npc_no, BMP *bitmap)
{
    SLONG   flag, id, px, py, pz, frame;
    CAKE_FRAME_ANI *cfa=NULL;
    CAKE_FRAME *cf=NULL;
    RLE *rle=NULL;

    flag = get_npc_flag(npc_no);
    if(!flag) return;

	LOCK_CHARACTER(npc_no);
    id = GetCharacterImageID(npc_no);
	GetCharacterPosition(npc_no, &px, &py, &pz);
    frame = GetCharacterFrame(npc_no);
	UNLOCK_CHARACTER(npc_no);

    //redraw body image
    //-------------------------------------------------------------------------------------------------
    {
#ifdef	USE_MDA_NPC_OBJECT
		SLONG	handle;
		SLONG	mda_index;

		handle = get_map_object_image_handle(id);
		if(handle >= 0)
		{

			LOCK_CHARACTER(npc_no);
			mda_index = get_mda_index(handle);
			memcpy(mda_group[mda_index].sea_rgb_data, get_npc_rgb_scroll(npc_no), 35);
			UNLOCK_CHARACTER(npc_no);

			mda_group_exec_with_position(handle, NULL, px, py, bitmap, 0x00000000, 0, 0, frame);

			LOCK_CHARACTER(npc_no);
			set_npc_rgb_scroll(npc_no, (USTR*)mda_group[mda_index].sea_rgb_data);
			UNLOCK_CHARACTER(npc_no);
		}
#else//!USE_MDA_NPC_OBJECT
		SLONG   sx,sy,ox,oy,xl,yl;

        cfa = get_map_object_image(id, frame);
        rle = NULL;
        if( cfa ) cf = cfa->cake_frame;
        if( cf )  { rle = cf->rle;}
        if( rle )
        {
            // we suppose all frame's polys have the same barycenter position,
            // so the offset x/y is just the following values...
            ox = -cf->poly_rx;
            oy = -cf->poly_ry;
            xl = rle->w;
            yl = rle->h;
            sx = ox + px;
            sy = oy + py - pz;

            put_rle(sx,sy,rle,bitmap);
        }
#endif//USE_MDA_NPC_OBJECT
    }
}


void    update_ui_npc_object(void)
{
    SLONG   i, npc_no;
    SLONG   flag, id, ext_id;

    for(i=0; i<game_npc_max; i++)
    {
        npc_no = i;
        flag = get_npc_flag(npc_no);
        id = GetCharacterImageID(npc_no);
        ext_id = get_npc_ext_id(npc_no);
        if(flag)
        {
            if(ext_id != id)
            {
                //釋放舊的影像資料
                if(ext_id != INVALID_OBJECT_ID)
				{
                    dec_reference_for_npc(ext_id);
				}

                //載入新的影像資料
                ext_id = id;
                if(ext_id != INVALID_OBJECT_ID)
				{
                    add_reference_for_npc(ext_id);
				}
            }
        }
    }
}



void    free_ui_npc_object(void)
{
    SLONG   i, npc_no;
    SLONG   flag, ext_id,foot_id,head_id,body_front_id,body_back_id;

    for(i=0; i<game_npc_max; i++)
    {
        npc_no = i;
        flag = game_npc[npc_no].flag;
        ext_id = game_npc[npc_no].ext_id;
        foot_id = game_npc[npc_no].ext_id;
        head_id = game_npc[npc_no].ext_id;        
        body_front_id = game_npc[npc_no].ext_id;
        body_back_id = game_npc[npc_no].ext_id;        
        if(flag)
        {
            //釋放影像資料
            if(ext_id != INVALID_OBJECT_ID)
            {
                dec_reference_for_npc(ext_id);
                game_npc[npc_no].ext_id = INVALID_OBJECT_ID;
                game_npc[npc_no].ext_frame = 0;
            }
            if(foot_id != INVALID_OBJECT_ID)
            {
                dec_reference_for_npc(foot_id);
                game_npc[npc_no].foot_id = INVALID_OBJECT_ID;
                game_npc[npc_no].foot_frame = 0;
            }
            if(head_id != INVALID_OBJECT_ID)
            {
                dec_reference_for_npc(head_id);
                game_npc[npc_no].head_id = INVALID_OBJECT_ID;
                game_npc[npc_no].head_frame = 0;
            }
            if(body_front_id != INVALID_OBJECT_ID)
            {
                dec_reference_for_npc(body_front_id);
                game_npc[npc_no].body_front_id = INVALID_OBJECT_ID;
                game_npc[npc_no].body_frame = 0;
            }
            if(body_back_id != INVALID_OBJECT_ID)
            {
                dec_reference_for_npc(body_back_id);
                game_npc[npc_no].body_back_id = INVALID_OBJECT_ID;
                game_npc[npc_no].body_frame = 0;
            }
            
        }
        
    }
}

/******************************************************************************************************************/
/* NPC SHOW FUNCTIONS                                                                                             */
/******************************************************************************************************************/
__inline    void    set_npc_show_ext_id(SLONG index, SLONG id)
{
    npc_show[index].ext_id = id;
}


__inline    SLONG   get_npc_show_ext_id(SLONG index)
{
    return  npc_show[index].ext_id;
}


__inline    SLONG   get_npc_show_ext_frame(SLONG index)
{
    return  npc_show[index].ext_frame;
}


__inline    void    set_npc_show_ext_frame(SLONG index, SLONG frame)
{
    npc_show[index].ext_frame = frame;
}

__inline    void    set_npc_show_head_id(SLONG index, SLONG id)
{
    npc_show[index].head_id = id;
}
__inline    SLONG   get_npc_show_head_id(SLONG index)
{
    return npc_show[index].head_id;
}
__inline    void    set_npc_show_head_frame(SLONG index, SLONG frame)
{
    npc_show[index].head_frame = frame;
}
__inline    SLONG   get_npc_show_head_frame(SLONG index)
{
    return npc_show[index].head_frame;
}

__inline    void    set_npc_show_foot_id(SLONG index, SLONG id)
{
    npc_show[index].foot_id = id;
}
__inline    SLONG   get_npc_show_foot_id(SLONG index)
{
    return npc_show[index].foot_id;
}
__inline    void    set_npc_show_foot_frame(SLONG index, SLONG frame)
{
    npc_show[index].foot_frame = frame;
}
__inline    SLONG   get_npc_show_foot_frame(SLONG index)
{
    return npc_show[index].foot_frame;
}

__inline    void    set_npc_show_body_front_id(SLONG index, SLONG id)
{
    npc_show[index].body_front_id = id;
}
__inline    SLONG   get_npc_show_body_front_id(SLONG index)
{
    return npc_show[index].body_front_id;
}
__inline    void    set_npc_show_body_back_id(SLONG index, SLONG id)
{
    npc_show[index].body_back_id = id;
}
__inline    SLONG   get_npc_show_body_back_id(SLONG index)
{
    return npc_show[index].body_back_id;
}
__inline    void    set_npc_show_body_frame(SLONG index, SLONG frame)
{
    npc_show[index].body_frame = frame;
}
__inline    SLONG   get_npc_show_body_frame(SLONG index)
{
    return npc_show[index].body_frame;
}


SLONG	get_npc_talk_lines(SLONG npc_no)
{
	return	game_npc[npc_no].talk_lines;
}

CHAR*	get_npc_talk_text(SLONG npc_no, SLONG line_index)
{
	return	(CHAR*)game_npc[npc_no].talk_text[line_index];
}

void	set_npc_talk_time(SLONG npc_no, ULONG talk_time)
{
	game_npc[npc_no].talk_time = talk_time;
}

ULONG	get_npc_talk_time(SLONG npc_no)
{
	return	game_npc[npc_no].talk_time;
}

SLONG   get_npc_talk_flag(SLONG npc_no)
{
    return  game_npc[npc_no].talk_flags;
}


void    set_npc_talk_flag(SLONG npc_no, SLONG flag)
{
    game_npc[npc_no].talk_flags = flag;
}


void	set_npc_talk_position(SLONG npc_no, SLONG sx, SLONG sy)
{
	game_npc[npc_no].talk_sx = sx;
	game_npc[npc_no].talk_sy = sy;
}


void	get_npc_talk_position(SLONG npc_no, SLONG *sx, SLONG *sy)
{
	if(sx) *sx = game_npc[npc_no].talk_sx;
	if(sy) *sy = game_npc[npc_no].talk_sy;
}


void	set_npc_effect(SLONG npc_no, SLONG effect)
{
	game_npc[npc_no].effect = effect;
}

SLONG	get_npc_effect(SLONG npc_no)
{
	return	game_npc[npc_no].effect;
}

void	set_npc_flag(SLONG npc_no, SLONG flag)
{
	game_npc[npc_no].flag = flag;
}

SLONG	get_npc_flag(SLONG npc_no)
{
	return	game_npc[npc_no].flag;
}

void	set_npc_object_index(SLONG npc_no, SLONG index)
{
	game_npc[npc_no].object_index = index;
}

SLONG	get_npc_object_index(SLONG npc_no)
{
	return	game_npc[npc_no].object_index;
}
//
void	set_npc_ext_id(SLONG npc_no, SLONG ext_id)
{
	game_npc[npc_no].ext_id = ext_id;
}

SLONG	get_npc_ext_id(SLONG npc_no)
{
	return	game_npc[npc_no].ext_id;
}

void	set_npc_ext_frame(SLONG npc_no, SLONG ext_frame)
{
	game_npc[npc_no].ext_frame = ext_frame;
}

SLONG	get_npc_ext_frame(SLONG npc_no)
{
	return	game_npc[npc_no].ext_frame;
}

void    set_npc_foot_id(SLONG npc_no,SLONG foot_id)
{
    game_npc[npc_no].foot_id = foot_id;
}
SLONG   get_npc_foot_id(SLONG npc_no)
{
    return game_npc[npc_no].foot_id;
}

void    set_npc_foot_frame(SLONG npc_no,SLONG foot_frame)
{
    game_npc[npc_no].foot_frame = foot_frame;
}
SLONG   get_npc_foot_frame(SLONG npc_no)
{
    return game_npc[npc_no].foot_frame;
}

void    set_npc_head_id(SLONG npc_no,SLONG head_id)
{
    game_npc[npc_no].head_id = head_id;
}
SLONG   get_npc_head_id(SLONG npc_no)
{
    return game_npc[npc_no].head_id;
}

void    set_npc_head_frame(SLONG npc_no,SLONG head_frame)
{
    game_npc[npc_no].head_frame = head_frame;
}
SLONG   get_npc_head_frame(SLONG npc_no)
{
    return game_npc[npc_no].head_frame;
}

void    set_npc_body_front_id(SLONG npc_no,SLONG body_id)
{
    game_npc[npc_no].body_front_id = body_id;
}
SLONG   get_npc_body_front_id(SLONG npc_no)
{
    return game_npc[npc_no].body_front_id;
}

void    set_npc_body_back_id(SLONG npc_no,SLONG body_id)
{
    game_npc[npc_no].body_back_id = body_id;
}
SLONG   get_npc_body_back_id(SLONG npc_no)
{
    return game_npc[npc_no].body_back_id;
}
void    set_npc_body_frame(SLONG npc_no,SLONG body_frame)
{
    game_npc[npc_no].body_frame = body_frame;
}
SLONG   get_npc_body_frame(SLONG npc_no)
{
    return game_npc[npc_no].body_frame;
}
//
void	set_npc_rgb_scroll(SLONG npc_no, UCHR *buffer)
{
	if(buffer)
	{
		memcpy(game_npc[npc_no].rgb_scroll, buffer, 35);
	}
}

UCHR*	get_npc_rgb_scroll(SLONG npc_no)
{
	return	(UCHR*)game_npc[npc_no].rgb_scroll;
}

void    loop_npc_ext_frame(SLONG npc_no)
{
    SLONG   id, frames, frame;

    id = get_npc_ext_id(npc_no);
    if(id == INVALID_OBJECT_ID)
        return;

    frames = GetObjectImageTotalFrames(id);
	frame = get_npc_ext_frame(npc_no);

	frame++;
    if(frame >= frames)
		frame = 0;

	set_npc_ext_frame(npc_no, frame);
}
//--------------------------------------------------------------------------
//
//--------------------------------------------------------------------------
void    ClientChangeCharacterDoing(SLONG npc_no, SLONG doing_kind, SLONG doing_step, SLONG d1, SLONG d2, SLONG d3, SLONG d4, SLONG d5)
{
    //SetCharacterDoingKindStep(npc_no, doing_kind, doing_step);
    change_npc_doing(npc_no, doing_kind, doing_step, d1, d2, d3, d4, d5);
}
void    set_npc_ai_function(void)
{
    SLONG   i;
    //初始化npc的AI數據
    InitAiData();
    //
	for(i=0; i<MAX_CHARACTER_DOING_KINDS; i++)
	{
        SetChangeCharacterDoingSomethingFun(i,ClientChangeCharacterDoing);
	}
}

void    set_npc_doing_functions(void)
{
	InitCharacterDoingSomethingFunction();

	SetCharacterDoingSomethingFunction(DOING_KIND_IDLE, client_do_npc_idle);
	SetCharacterDoingSomethingFunction(DOING_KIND_MUSE, client_do_npc_muse);
	SetCharacterDoingSomethingFunction(DOING_KIND_SPOWER, client_do_npc_spower);
	SetCharacterDoingSomethingFunction(DOING_KIND_CHANGEMAP, client_do_npc_change_map);
//	SetCharacterDoingSomethingFunction(DOING_KIND_FIGHT_IDLE, client_do_npc_fight_idle);
	SetCharacterDoingSomethingFunction(DOING_KIND_STAND, client_do_npc_stand);
	//
	SetCharacterDoingSomethingFunction(DOING_KIND_MOVE_TO, client_do_npc_move_to);
//	SetCharacterDoingSomethingFunction(DOING_KIND_MAGIC_POSITION, client_do_npc_magic_position);
	SetCharacterDoingSomethingFunction(DOING_KIND_CLASH, client_do_npc_clash);
//	SetCharacterDoingSomethingFunction(DOING_KIND_GAD, client_do_npc_gad);
//	SetCharacterDoingSomethingFunction(DOING_KIND_PATROL, client_do_npc_patrol);
//	SetCharacterDoingSomethingFunction(DOING_KIND_FIGHT_GAD, client_do_npc_fight_gad);
//	SetCharacterDoingSomethingFunction(DOING_KIND_FIGHT_PATROL, client_do_npc_fight_patrol);
	SetCharacterDoingSomethingFunction(DOING_KIND_SKILL_ACTION, client_do_npc_fight_action);	
	//
	SetCharacterDoingSomethingFunction(DOING_KIND_TALK_WITH_NPC, client_do_npc_talk_with_npc);
//	SetCharacterDoingSomethingFunction(DOING_KIND_ATTACK_NPC, client_do_npc_attack_npc);
//	SetCharacterDoingSomethingFunction(DOING_KIND_MAGIC_NPC, client_do_npc_magic_npc);
	SetCharacterDoingSomethingFunction(DOING_KIND_SEQUENTIAL_ATTACK_NPC, client_do_npc_sequential_attack_npc);
	//
	SetCharacterDoingSomethingFunction(DOING_KIND_PICK_ITEM, client_do_npc_pick_item);
	//
	SetCharacterDoingSomethingFunction(DOING_KIND_BEATED, client_do_npc_beated);
	SetCharacterDoingSomethingFunction(DOING_KIND_DEAD, client_do_npc_dead);
	SetCharacterDoingSomethingFunction(DOING_KIND_DOWN_AND_OUT, client_do_npc_down_and_out);
	SetCharacterDoingSomethingFunction(DOING_KIND_DEFENCE, client_do_npc_defence);
	SetCharacterDoingSomethingFunction(DOING_KIND_DEFENCED, client_do_npc_defenced);
	//
	//SetCharacterDoingSomethingFunction(DOING_KIND_CHEER, client_do_npc_cheer);
	SetCharacterDoingSomethingFunction(DOING_KIND_ANGRY, client_do_npc_angry);
	SetCharacterDoingSomethingFunction(DOING_KIND_BECKON, client_do_npc_beckon);
	//SetCharacterDoingSomethingFunction(DOING_KIND_COURT, client_do_npc_court);
	SetCharacterDoingSomethingFunction(DOING_KIND_FAINT, client_do_npc_faint);
	SetCharacterDoingSomethingFunction(DOING_KIND_SAY_NO, client_do_npc_say_no);
	SetCharacterDoingSomethingFunction(DOING_KIND_BOW, client_do_npc_bow);
	SetCharacterDoingSomethingFunction(DOING_KIND_WIN, client_do_npc_win);
	SetCharacterDoingSomethingFunction(DOING_KIND_SWASH, client_do_npc_swash);
	SetCharacterDoingSomethingFunction(DOING_KIND_XXPOWER, client_do_npc_xxpower);
	SetCharacterDoingSomethingFunction(DOING_KIND_XXBEATED, client_do_npc_xxbeated);
	
	//sea functions -------------------------------------------------
	SetCharacterDoingSomethingFunction(DOING_KIND_SEA_ACC_MOVE_TO, client_do_sea_npc_acc_move_to);
	SetCharacterDoingSomethingFunction(DOING_KIND_SEA_IDLE, client_do_sea_npc_idle);
	SetCharacterDoingSomethingFunction(DOING_KIND_SEA_SAIL_TO, client_do_sea_npc_sail_to);
	SetCharacterDoingSomethingFunction(DOING_KIND_SEA_WALK_TO, client_do_sea_npc_walk_to);
}



/************************************************************************************************************/
/* MAP NPC OBJECT FUNCTIONS                                                                                 */
/************************************************************************************************************/
SLONG	add_map_npc_object(SLONG id, SLONG px, SLONG py, SLONG pz, SLONG effect, SLONG npc_no)
{
    SLONG   object_index;

    object_index = get_usable_map_object();
    if(object_index >= 0)
    {
        map_object[object_index].flag = MOBJ_ACTIVE | MOBJ_NPC;
        map_object[object_index].id = id;
        map_object[object_index].px = px;
        map_object[object_index].py = py;
        map_object[object_index].pz = pz;
        map_object[object_index].npc_no = npc_no;

        map_object[object_index].effect = effect;
        map_object[object_index].frame = 0;

		if(id != INVALID_OBJECT_ID)
		{
			add_reference_for_npc(id);
		}

        if(object_index >= map_object_max)
            map_object_max = object_index + 1;
    }
    return object_index;
}

SLONG	del_map_npc_object(SLONG object_index)
{
	SLONG	id;

    if( object_index >= 0 && object_index < map_object_max )
	{
		id = map_object[object_index].id;

		if( id != INVALID_OBJECT_ID)
		{
			dec_reference_for_npc(id);
		}

		map_object[object_index].flag = 0;
		map_object[object_index].id = INVALID_OBJECT_ID;
	}
	return	TTN_OK;
}

void	draw_map_npc_object(SLONG object_index, SLONG flags, BMP *bitmap)
{
    SLONG   npc_no, flag, id, px, py, pz, effect, frame, alpha;
    SLONG   sx,sy,ox,oy,xl,yl;
    CAKE_FRAME_ANI *cfa=NULL;
    CAKE_FRAME *cf=NULL;
    RLE *rle=NULL;
    POLY *pl=NULL;
    SLONG   foot_state, i;
    SLONG   ext_id, ext_frame;
    CAKE_FRAME_ANI  *ext_cfa = NULL;
    CAKE_FRAME  *ext_cf = NULL;
    RLE *ext_rle = NULL;
    POLY *ext_pl = NULL;
    SLONG   talk_flag;
	SLONG	mda_index;

    npc_no = map_object[object_index].npc_no;
    flag = map_object[object_index].flag;
    id = map_object[object_index].id;
    px = map_object[object_index].px;
    py = map_object[object_index].py;
    pz = map_object[object_index].pz;
    effect = map_object[object_index].effect;
    frame = map_object[object_index].frame;

    if(! (flag & MOBJ_ACTIVE) )return;

    // Jack added. [7/30/2002]
    //add_npc_light(px, py, pz);

    LOCK_CHARACTER(npc_no);
    foot_state = GetCharacterFootSpeedState(npc_no);
    talk_flag = get_npc_talk_flag(npc_no);
    UNLOCK_CHARACTER(npc_no);
    ext_id = get_npc_show_ext_id(npc_no);
    ext_frame = get_npc_show_ext_frame(npc_no);

    //(1) redraw foot abnormity effect
    //-------------------------------------------------------------------------------------------------
    switch(foot_state)
    {
    case NPC_FOOT_SPEED_STATE_TARDY:
        put_ellipse(px-map_data.map_sx, py-pz-map_data.map_sy,
            NPC_MASK_WIDTH / 2 + 4, NPC_MASK_WIDTH / 4 + 2, rgb2hi(200, 0, 0),bitmap);
        put_ellipse(px-map_data.map_sx, py-pz-map_data.map_sy,
            NPC_MASK_WIDTH / 2 + 5, NPC_MASK_WIDTH / 4 + 3, rgb2hi(255, 0, 0),bitmap);
        put_ellipse(px-map_data.map_sx, py-pz-map_data.map_sy,
            NPC_MASK_WIDTH / 2 + 6, NPC_MASK_WIDTH / 4 + 4 ,rgb2hi(200, 0, 0),bitmap);
        break;
    case NPC_FOOT_SPEED_STATE_TIRED:
        put_ellipse(px-map_data.map_sx, py-pz-map_data.map_sy,
            NPC_MASK_WIDTH / 2 + 4, NPC_MASK_WIDTH / 4 + 2, rgb2hi(0, 0, 200),bitmap);
        put_ellipse(px-map_data.map_sx, py-pz-map_data.map_sy,
            NPC_MASK_WIDTH / 2 + 5, NPC_MASK_WIDTH / 4 + 3, rgb2hi(0, 0, 255),bitmap);
        put_ellipse(px-map_data.map_sx, py-pz-map_data.map_sy,
            NPC_MASK_WIDTH / 2 + 6, NPC_MASK_WIDTH / 4 + 4 ,rgb2hi(0, 0, 200),bitmap);
        break;
    }

    //(2) redraw foot magic effect
    //-------------------------------------------------------------------------------------------------

    //(3) redraw body image
    //-------------------------------------------------------------------------------------------------
#ifdef	USE_MDA_NPC_OBJECT
	SLONG	handle, result, object_flag;
	SLONG	cx, cy;

	handle = get_map_object_image_handle(id);
	if(handle >= 0)
	{
		result = get_map_npc_object_information(object_index, &object_flag, &sx, &sy, &xl, &yl, &pl);
		if(TTN_OK == result)
		{
			cx = px - map_data.map_sx;
			cy = py - pz - map_data.map_sy;
            if(npc_show[npc_no].flag & NPC_SHOW_ENABLE_RANGE)
            {
				if(mouse_hand.point_kind == RT_NPC && mouse_hand.point_no == npc_no)
				{
                    put_ellipse(px-map_data.map_sx + 1, py-pz-map_data.map_sy + 1,
                        NPC_MASK_WIDTH / 3 + 2, NPC_MASK_WIDTH / 6 + 1 ,SYSTEM_DARK1,bitmap);
                    put_ellipse(px-map_data.map_sx, py-pz-map_data.map_sy,
                        NPC_MASK_WIDTH / 3 + 2, NPC_MASK_WIDTH / 6 + 1 ,SYSTEM_RED,bitmap);
				}
            }

			put_npc_shadow_image(cx, cy, 0, 0, bitmap);

			if(npc_show[npc_no].with_shadow)
			{
				for(i=MAX_SHOW_SHADOWS-1; i>=0; i--)
				{
					// Jack, TODO: [1/24/2003]
					//blue_alpha_put_rle(sx + npc_show[npc_no].shadow_x[i] - px,
					//	sy + npc_show[npc_no].shadow_y[i] - py, rle, bitmap, 192 - 24 * i);
				}

				LOCK_CHARACTER(npc_no);
				mda_index = get_mda_index(handle);
				memcpy(mda_group[mda_index].sea_rgb_data, get_npc_rgb_scroll(npc_no), 35);
				UNLOCK_CHARACTER(npc_no);

				mda_group_exec_with_position(handle, NULL, cx, cy, bitmap, 0x00000000, 0, 0, frame);

				LOCK_CHARACTER(npc_no);
				set_npc_rgb_scroll(npc_no, (USTR*)mda_group[mda_index].sea_rgb_data);
				UNLOCK_CHARACTER(npc_no);

			}
			else
			{
				LOCK_CHARACTER(npc_no);
				mda_index = get_mda_index(handle);
				memcpy(mda_group[mda_index].sea_rgb_data, get_npc_rgb_scroll(npc_no), 35);
				UNLOCK_CHARACTER(npc_no);

				switch(effect & OBJECT_IMAGE_MASK)
				{
				case OBJECT_NORMAL_IMAGE:
					mda_group_exec_with_position(handle, NULL, cx, cy, bitmap, 0x00000000, 0, 0, frame);
					break;
				case OBJECT_ALFA_IMAGE:
					alpha = (effect & OBJECT_ALPHA_MASK) >> 8;
					mda_group_exec_with_position(handle, NULL, cx, cy, bitmap, MDA_COMMAND_ALPHA, 0, alpha, frame);
					break;
				}

				LOCK_CHARACTER(npc_no);
				set_npc_rgb_scroll(npc_no, (USTR*)mda_group[mda_index].sea_rgb_data);
				UNLOCK_CHARACTER(npc_no);
			}
			
            //update game_range
            if(npc_show[npc_no].flag & NPC_SHOW_ENABLE_RANGE)
            {
                game_range.add( cx - NPC_MASK_WIDTH/2, cy - NPC_MASK_HEIGHT,
                    NPC_MASK_WIDTH, NPC_MASK_HEIGHT, RT_NPC, npc_no );
            }
			
			if(is_redraw_map_object_poly())
            {
                D3_draw_poly(px-map_data.map_sx, py-map_data.map_sy, pz, OBJECT_POLY_FLAGS, pl, bitmap);
            }
		}
	}

#else//!USE_MDA_NPC_OBJECT
    {
        cfa = get_map_object_image(id, frame);
        rle = NULL;
        if( cfa ) cf = cfa->cake_frame;
        if( cf )  { rle = cf->rle; pl = cf->poly; }
        if( rle )
        {
            // we suppose all frame's polys have the same barycenter position,
            // so the offset x/y is just the following values...
            ox = -cf->poly_rx;
            oy = -cf->poly_ry;
            xl = rle->w;
            yl = rle->h;
            sx = ox + px - map_data.map_sx;
            sy = oy + py - pz - map_data.map_sy;

            //show body image
            // Jack,  [16:14,9/27/2002]
            /*
            if( flags < 0 )
            {
#ifdef  DEBUG
                sprintf((char *)print_rec,"~O3~C0#%d(H%d)~C0~O0",abs(flags),pz);
                print16(px-map_data.map_sx,py-map_data.map_sy-pz,(USTR *)print_rec,PEST_PUT,bitmap);
#endif//DEBUG
                mesh_put_rle(sx,sy,rle,bitmap);
            }
            else
            */
            {
                if(npc_show[npc_no].with_shadow)
                {
                    for(i=MAX_SHOW_SHADOWS-1; i>=0; i--)
                    {
                        blue_alpha_put_rle(sx + npc_show[npc_no].shadow_x[i] - px,
                            sy + npc_show[npc_no].shadow_y[i] - py, rle, bitmap, 192 - 24 * i);
                    }
                    put_rle(sx,sy,rle,bitmap);
                }
                else
                {
                    switch(effect & OBJECT_IMAGE_MASK)
                    {
                    case OBJECT_NORMAL_IMAGE:
                        put_rle(sx,sy,rle,bitmap);
                        break;
                    case OBJECT_ALFA_IMAGE:
                        alpha = (effect & OBJECT_ALPHA_MASK) >> 8;
                        alpha_put_rle(sx, sy, rle, bitmap, alpha);
                        break;
                    }
                }
            }

            if(npc_show[npc_no].flag & NPC_SHOW_ENABLE_RANGE)
            {
				if(mouse_hand.point_kind == RT_NPC && mouse_hand.point_no == npc_no)
				{
					mask_put_rle_edge(sx, sy, SYSTEM_YELLOW, rle, bitmap);
				}
            }

            //update game_range
            if(npc_show[npc_no].flag & NPC_SHOW_ENABLE_RANGE)
            {
                game_range.add( px - map_data.map_sx - NPC_MASK_WIDTH/2, py - pz - map_data.map_sy - NPC_MASK_HEIGHT,
                    NPC_MASK_WIDTH, NPC_MASK_HEIGHT, RT_NPC, npc_no );
            }

#ifdef  DEBUG
			if(is_redraw_map_object_poly())
            {
                D3_draw_poly(px-map_data.map_sx,py-map_data.map_sy,pz, OBJECT_POLY_FLAGS, pl, bitmap);
            }
#endif//DEBUG
        }
    }
#endif//USE_MDA_NPC_OBJECT

    //(3) redraw body ext image
    //-------------------------------------------------------------------------------------------------
    {
        if(ext_id != INVALID_OBJECT_ID)
        {
            ext_cfa = get_map_object_image(ext_id, ext_frame);
            ext_rle = NULL;
            if( ext_cfa ) ext_cf = ext_cfa->cake_frame;
            if( ext_cf )  { ext_rle = ext_cf->rle; ext_pl = ext_cf->poly; }
            if( ext_rle )
            {
                // we suppose all frame's polys have the same barycenter position,
                // so the offset x/y is just the following values...
                ox = -ext_cf->poly_rx;
                oy = -ext_cf->poly_ry;
                sx = px - map_data.map_sx + ox;
                sy = py - pz - map_data.map_sy - NPC_MASK_HEIGHT * 2 / 4 + oy;
                //put_rle(sx, sy, ext_rle, bitmap);
                additive_put_rle(sx, sy, ext_rle, bitmap);
                //alpha_put_rle(sx, sy, ext_rle, bitmap, 128);
            }
        }
    }

    /*
    // Jack, todo [17:10,10/14/2002]
    //(4) redraw npc's head magic images --------------------------------------------------------------
    if( npc_show[npc_index].head_flag )
    {
        cfa = get_map_object_image( npc_show[npc_index].head_id, npc_show[npc_index].head_frame );
        if( cfa ) cf = cfa->cake_frame;
        if( cf )
        {
            rle = cf->rle;
            if(rle)
            {
                put_rle( -cf->poly_rx + npc_show[npc_index].head_x - map_data.map_sx,
                    -cf->poly_ry + npc_show[npc_index].head_y - npc_show[npc_index].head_z - map_data.map_sy,
                    rle, bitmap);
            }
        }
    }
    */

    //(5) redraw npc's talk or npc's name.
    //-------------------------------------------------------------------------------------------------
    switch(talk_flag)
    {
    case NPC_TALK_IS_DIALOG:
        sx = px - map_data.map_sx;
        sy = py - pz - map_data.map_sy - NPC_MASK_HEIGHT - 20;
        LOCK_CHARACTER(npc_no);
        set_npc_talk_position(npc_no, sx, sy);
        add_npc_to_npc_talk_list(npc_no);
        UNLOCK_CHARACTER(npc_no);
        break;
    default:
        sx = px - map_data.map_sx;
        sy = py - pz - map_data.map_sy - NPC_MASK_HEIGHT - 20;
        LOCK_CHARACTER(npc_no);
        set_npc_talk_flag(npc_no, NPC_TALK_IS_NAME);
        set_npc_talk_position(npc_no, sx, sy);
        add_npc_to_npc_talk_list(npc_no);
        UNLOCK_CHARACTER(npc_no);
        break;
    }
}

void	refresh_map_npc_object(SLONG object_index)
{
	// Do nothing here.
	// We will refresh map npc object after we refreshed npc(character) data.
}

SLONG	change_map_npc_object_id(SLONG object_index, SLONG new_id)
{
	SLONG	old_id;

	old_id = map_object[object_index].id;
	if(new_id != INVALID_OBJECT_ID)
	{
		add_reference_for_npc(new_id);
	}
	if(old_id != INVALID_OBJECT_ID)
	{
		dec_reference_for_npc(old_id);
	}
	map_object[object_index].id = new_id;

    return  TTN_OK;
}


SLONG	get_map_npc_object_information(SLONG object_index, SLONG *object_flag, SLONG *sx, SLONG *sy, 
									   SLONG *ex, SLONG *ey, POLY **poly)
{
#ifdef	USE_MDA_NPC_OBJECT
	enum
	{ 
		NPC_OBJECT_IMAGE_WIDTH		= NPC_MASK_WIDTH,
		NPC_OBJECT_IMAGE_HEIGHT		= NPC_MASK_HEIGHT,
		NPC_OBJECT_POLY_XHALF		= 8,
		NPC_OBJECT_POLY_YHALF		= 4,
		NPC_OBJECT_POLY_Z0			= 0,
		NPC_OBJECT_POLY_Z1			= 60
	};
	static	POLY 	npc_poly;
	static	SLONG	not_init = 1;
    SLONG   flag, id, px, py, pz;
	

	if(not_init)
	{
        D3_clear_poly(&npc_poly);
        D3_make_diamond_poly(&npc_poly, 0, 0, NPC_OBJECT_POLY_XHALF, NPC_OBJECT_POLY_YHALF);
        D3_set_poly_height(&npc_poly, NPC_OBJECT_POLY_Z0, NPC_OBJECT_POLY_Z1);
        D3_set_poly_type(&npc_poly,POLY_TYPE_MAST);
		not_init = 0;
	}

    flag = map_object[object_index].flag;
    id = map_object[object_index].id;
    px = map_object[object_index].px;
    py = map_object[object_index].py;
    pz = map_object[object_index].pz;

	if( id != INVALID_OBJECT_ID && flag )
	{
		//
		// We suppose that each npc has the same image size and the same poly data.
		//
		*object_flag = flag;
		*sx = - map_data.map_sx + px - NPC_OBJECT_IMAGE_WIDTH/2;
		*sy = - map_data.map_sy + (py - pz) - NPC_OBJECT_IMAGE_HEIGHT;
		*ex = *sx + NPC_OBJECT_IMAGE_WIDTH;
		*ey = *sy + NPC_OBJECT_IMAGE_HEIGHT;
		*poly = &npc_poly;
		
		return  TTN_OK;
	}

#else//!USE_MDA_NPC_OBJECT

    SLONG   flag, id, px, py, pz;
    SLONG   object_type;
	CAKE_FRAME_ANI *cfa = NULL;
	CAKE_FRAME  * cf = NULL;
	RLE*    rle = NULL;
	POLY*   pl = NULL;
	SLONG   ox, oy;

    flag = map_object[object_index].flag;
    id = map_object[object_index].id;
    px = map_object[object_index].px;
    py = map_object[object_index].py;
    pz = map_object[object_index].pz;
    object_type = flag & MOBJ_TYPES;

	if( id != INVALID_OBJECT_ID && flag )
	{
		cfa = get_map_object_image(id, map_object[object_index].frame);
		if(cfa) cf = cfa->cake_frame;
		if(cf) 
		{   
			rle = cf->rle;
			pl = cf->poly;
		}
		if(rle && pl)
		{
			// we suppose all frame's polys have the same barycenter position,
			// so the offset x/y is just the following values...
			ox = -cf->poly_rx;
			oy = -cf->poly_ry;
			
			*object_flag = flag;
			*sx = - map_data.map_sx + ox + px;
			*sy = - map_data.map_sy + oy + (py - pz);
			*ex = *sx + rle->w;
			*ey = *sy + rle->h;
			*poly = pl;
			
			return  TTN_OK;
		}
	}
#endif//USE_MDA_NPC_OBJECT

	return  TTN_NOT_OK;
}

//----
//  讀取需要的  npc的圖檔管理機制
//----
void    npc_effect_id_manage(SLONG *npc_id,SLONG *npc_show_id,SLONG *npc_frame,SLONG *npc_show_frame)
{
    if ((*npc_id) != INVALID_OBJECT_ID)
    {
        if ((*npc_show_id) == INVALID_OBJECT_ID)
        {
            add_reference_for_map_object_image(*npc_id);
            //
            *npc_show_id = *npc_id;
            *npc_show_frame = *npc_frame;
        }
        else if ((*npc_show_id) != (*npc_id))
        {
            dec_reference_for_map_object_image(*npc_show_id);
            add_reference_for_map_object_image(*npc_id);
            //
            *npc_show_id = *npc_id;
            *npc_show_frame = *npc_frame;
        }
        else
        {
            *npc_show_frame = *npc_frame;            
        }
    }
    else //從內存中釋放特殊效果圖檔
    {
        if ((*npc_show_id) != INVALID_OBJECT_ID)
        {
            dec_reference_for_map_object_image(*npc_show_id);
            //
            *npc_show_id = INVALID_OBJECT_ID;
            *npc_show_frame = 0;
        }
    }
}


