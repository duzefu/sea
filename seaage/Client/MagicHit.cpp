/*
**	MagicHit.cpp
**	magic hit processing.
**
**	Jack, 2002/09/16.
*/ 
#include "MainFun.h"
#include "NetGE_MainFunc.h"
#include "ClientMain.h"
#include "Map.h"
#include "CRange.h"
#include "MouseHand.h"
#include "MainGame.h"
#include "CmdEvent.h"
#include "UIMagicArea.h"
//
/******************************************************************************************************************/
/* STRUCTURES                                                                                                     */
/******************************************************************************************************************/
typedef struct tagMAGIC_HITS
{
    SLONG   (*buttondown_func)(SLONG player_index, SLONG magic_no, WPARAM wParam, LPARAM lParam);
    SLONG   (*buttonup_func)(SLONG player_index, SLONG magic_no, WPARAM wParam, LPARAM lParam);
    SLONG   (*mousemove_func)(SLONG player_index, SLONG magic_no, WPARAM wParam, LPARAM lParam);
    //
} MAGIC_HITS, *LPMAGIC_HITS;

/******************************************************************************************************************/
/* GLOBALS                                                                                                        */
/******************************************************************************************************************/
MAGIC_HITS  magic_hits[MAX_GAME_SKILL_BASES];
//
static  SLONG   dummy_buttondown_func(SLONG player_index, SLONG magic_no, WPARAM wParam, LPARAM lParam);
static  SLONG   dummy_buttonup_func(SLONG player_index, SLONG magic_no, WPARAM wParam, LPARAM lParam);
static  SLONG   dummy_mousemove_func(SLONG player_index, SLONG magic_no, WPARAM wParam, LPARAM lParam);
//
static  SLONG   buttondown_do_normal(SLONG player_index, SLONG magic_no, WPARAM wParam, LPARAM lParam);
static  SLONG   buttonup_do_normal(SLONG player_index, SLONG magic_no, WPARAM wParam, LPARAM lParam);
//static  SLONG   buttondown_do_spower(SLONG player_index, SLONG magic_no, WPARAM wParam, LPARAM lParam);
//static  SLONG   buttonup_do_clash(SLONG player_index, SLONG magic_no, WPARAM wParam, LPARAM lParam);
/******************************************************************************************************************/
/* MAGIC HIT MAIN FUNCTIONS                                                                                       */
/******************************************************************************************************************/
void    init_magic_hits(void)
{
    SLONG   index;

    //clear magic hits data. ----------------------------------------------
    for(index=0; index<MAX_GAME_SKILL_BASES; index++)
    {
        // mark by lijun 2003-05-06
        /*
        magic_hits[index].buttondown_func = dummy_buttondown_func;
        magic_hits[index].buttonup_func = dummy_buttonup_func;
        magic_hits[index].mousemove_func = dummy_mousemove_func;
        */        
        magic_hits[index].buttondown_func = buttondown_do_normal;
        magic_hits[index].buttonup_func = buttonup_do_normal;
        magic_hits[index].mousemove_func = dummy_mousemove_func;        
    }
    //set magic hits one by one. ------------------------------------------
    index = MAGIC_NO_JOIN_TEAM; //�ն�
    index = MAGIC_NO_LEAVE_TEAM;//����
    index = MAGIC_NO_TRADE;     //���
    index = MAGIC_NO_FOLLOW;    //���H
    index = MAGIC_NO_IDENTIFY;  //ų�w
    //
    index = MAGIC_NO_WALK;      //�樫
    //magic_hits[index].buttondown_func = buttondown_do_normal;

    index = MAGIC_NO_MUSE;      //�߷Q

    index = MAGIC_NO_ESCRIME;   //�C�N
    //magic_hits[index].buttondown_func = buttondown_do_normal;

    index = MAGIC_NO_SEQUENTIAL_ESCRIME;    //�s��
    //magic_hits[index].buttondown_func = buttondown_do_normal;

    index = MAGIC_NO_STRONG;    //�j��

    index = MAGIC_NO_DEFENCE;   //���

    index = MAGIC_NO_CLASH; //�ļ�
    //magic_hits[index].buttondown_func = buttondown_do_spower;
    //magic_hits[index].buttonup_func   = buttonup_do_clash;

    index = MAGIC_NO_PENETRABLE_ESCRIME;    //�C��
    index = MAGIC_NO_KNOCK_TO_DIZZY;    //�V�w
    index = MAGIC_NO_FATAL_ESCRIME; //�����C
    //
    index = MAGIC_NO_SHOOT; //�g��
    //magic_hits[index].buttondown_func = buttondown_do_normal;

    index = MAGIC_NO_SEQUENTIAL_SHOOT;  //�s�g
    //magic_hits[index].buttondown_func = buttondown_do_normal;

    index = MAGIC_NO_EYES_SHOOT;    //������
    index = MAGIC_NO_DODGE; //���{
    index = MAGIC_NO_PENETRABLE_SHOOT;  //��z�u
    index = MAGIC_NO_DOUBLE_SHOOT;  //�����u��
    index = MAGIC_NO_FEET_SHOOT;    //���}

    index = MAGIC_NO_DIFFUSE_SHOOT; //���g
    //magic_hits[index].buttondown_func = buttondown_do_normal;
    //
    index = MAGIC_NO_BOOK_READ; //Ū��
    index = MAGIC_NO_CURE;  //�v��
    index = MAGIC_NO_DEFEND_MIRROR; //���m��
    index = MAGIC_NO_RELIVE;//�_��
    index = MAGIC_NO_BAPTISM;//�~§
    index = MAGIC_NO_MAGIC_MIRROR;//�]�k��
    index = MAGIC_NO_ENRICH_BLOOD;//�j�ɦ�
    index = MAGIC_NO_INFINITE_KINDNESS;//�����E��

    index = MAGIC_NO_DARK_STAR;//�t�P
    //magic_hits[index].buttondown_func = buttondown_do_normal;

    index = MAGIC_NO_SLEEP;//�ίv��
    index = MAGIC_NO_TORTOISE;//�Q�t��
    index = MAGIC_NO_RESIST;//���

    index = MAGIC_NO_DARK_BALL;//�t�y
    //magic_hits[index].buttondown_func = buttondown_do_normal;

    index = MAGIC_NO_BEELINE_MAGIC;//���u�]�k
    //magic_hits[index].buttondown_func = buttondown_do_normal;

    index = MAGIC_NO_AZRAEL;//����
    index = MAGIC_NO_DEVIL;//�c�]
    //
    index = MAGIC_NO_THONG;//���@
    index = MAGIC_NO_CIRRUS_TRAP;//�ý�����
    index = MAGIC_NO_BEAST_TRAP;//���~��
    index = MAGIC_NO_ERUPTIVE_THONG;//���@�W�O
    index = MAGIC_NO_RAVEL_TRAP;//�Ѱ�����
    index = MAGIC_NO_PREDICT;//�w�P
    index = MAGIC_NO_STONE_TRAP;//���۳���
    index = MAGIC_NO_PRETEND;//����
    index = MAGIC_NO_LANDMINE;//�a�p
    //
    index = MAGIC_NO_DAGGER;//�P��
    index = MAGIC_NO_BEHIND_DAGGER;//�I��
    index = MAGIC_NO_STEAL;//����
    index = MAGIC_NO_UNLOCK;//�}��
    index = MAGIC_NO_HIDE;//����
    index = MAGIC_NO_POISON;//�U�r
    index = MAGIC_NO_GOLD;//����
    index = MAGIC_NO_NEGOTIATE;//�ͧP
    index = MAGIC_NO_ATTRACT_MONSTER;//�l�ީǪ�
    index = MAGIC_NO_BOX_TRAP;//�_�c����
    index = MAGIC_NO_CONTROL_MONSTER;//�Ǫ�����
    //
    index = MAGIC_NO_CHOP;//���
    index = MAGIC_NO_TOXOPHILY;//�g�b
    index = MAGIC_NO_RELIVE_2;//�_���G
    index = MAGIC_NO_SUCK_BLOOD;//�l��
    index = MAGIC_NO_SUCK_MAGIC;//�l�]
    index = MAGIC_NO_DESTROY_ARMOR;//����}�a
    index = MAGIC_NO_RELIVE_3;//�_���T
    index = MAGIC_NO_HIDE_2;//�����G
    index = MAGIC_NO_FIRE_BALL;//���y
    index = MAGIC_NO_EXPLODE;//���z�@
    index = MAGIC_NO_EXPLODE_2;//���z�G
    index = MAGIC_NO_BREAK_EQUIP;//���˳�
    index = MAGIC_NO_RECALL;//�l��
    index = MAGIC_NO_CHANGE_FORM;//�ܨ�
    index = MAGIC_NO_INSURANCE;//�O�I
    index = MAGIC_NO_INSURANCE_2;//�O�I�G
    index = MAGIC_NO_INSURANCE_3;//�O�I�T
    index = MAGIC_NO_INSURANCE_4;//�O�I�|
    index = MAGIC_NO_INSURANCE_5;//�O�I��

	//sea skill functions ----------------------------------------------------
    //���W�ޯ઺�B�z
    index = MAGIC_NO_SEAWALK;      //�樫
    //magic_hits[index].buttondown_func = buttondown_do_normal;
    //
    index = MAGIC_NO_PRETEND;//����
    index = MAGIC_NO_ARMOUR_PIERCING_BALL;//��Ҽu

    index = MAGIC_NO_LINK_BALL;//��u
	//magic_hits[index].buttondown_func = buttondown_do_normal;

    index = MAGIC_NO_BURNT_BALL;//�U�N�u
    index = MAGIC_NO_EMANATORY_BALL;//���u
    index = MAGIC_NO_REPAIR_BOAT;//�ײz
}

//----
//  ��������U�ɭԵo�X������
//----
SLONG   exec_magic_buttondown(SLONG player_index, SLONG magic_no, WPARAM wParam, LPARAM lParam)
{
    return  magic_hits[magic_no].buttondown_func(player_index, magic_no, wParam, lParam);
}
//----
//  �������P�}�ɭԵo�X������
//----
SLONG   exec_magic_buttonup(SLONG player_index, SLONG magic_no, WPARAM wParam, LPARAM lParam)
{
    return  magic_hits[magic_no].buttonup_func(player_index, magic_no, wParam, lParam);
}

//----
//  �����䲾�ʮɭԵo�X������
//----
SLONG   exec_magic_mousemove(SLONG player_index, SLONG magic_no, WPARAM wParam, LPARAM lParam)
{
    return  magic_hits[magic_no].mousemove_func(player_index, magic_no, wParam, lParam);
}
/******************************************************************************************************************/
/* MAGIC HIT STATIC FUNCTIONS                                                                                     */
/******************************************************************************************************************/
//buttondown functions //////////////////////////////////////////////////////////
static  SLONG   dummy_buttondown_func(SLONG player_index, SLONG magic_no, WPARAM wParam, LPARAM lParam)
{
    return  0;
}

static  SLONG   buttondown_do_normal(SLONG player_index, SLONG magic_no, WPARAM wParam, LPARAM lParam)
{

    switch (mouse_hand.point_doing)
    {
    case HAND_DOING_LEFT_ITEM:
    case HAND_DOING_LEFT_MAGIC:
        if (mouse_hand.point_no >= 0)
            client_cmd_left_hit_npc(mouse_hand.point_no);
        else    
            client_cmd_left_hit_map(mouse_hand.point_x, mouse_hand.point_y);
        break;
    case HAND_DOING_RIGHT_ITEM:
    case HAND_DOING_RIGHT_MAGIC:
        if (mouse_hand.point_no >= 0)
            client_cmd_right_hit_npc(mouse_hand.point_no);
        else    
            client_cmd_right_hit_map(mouse_hand.point_x, mouse_hand.point_y);    
        break;
    }
    return  0;

/*
    SLONG   mouse_x, mouse_y, map_x, map_y;
    SLONG   event_type, event_id;
    SLONG   dx, dy, npc_x, npc_y, npc_z;

    mouse_x = GET_X_LPARAM(lParam);
    mouse_y = GET_Y_LPARAM(lParam);
    map_x = map_data.map_sx + mouse_x;
    map_y = map_data.map_sy + mouse_y;
    event_type = event_id = 0;
    game_range.mapping(mouse_x, mouse_y, &event_type, &event_id);
    set_mouse_hand_position(mouse_x, mouse_y);
    set_mouse_hand_point_info(event_type, event_id, map_x, map_y);
    switch(event_type)
    {
    case RT_MAP:
        LOCK_CHARACTER(g_lPlayerIndex);
		GetCharacterPosition(g_lPlayerIndex, &npc_x, &npc_y, &npc_z);
        UNLOCK_CHARACTER(g_lPlayerIndex);

        dx = abs(mouse_hand.point_x - npc_x);
        dy = abs(mouse_hand.point_y - npc_y);
        if(dx >= INVALID_MOUSE_RANGE_HALF_WIDTH || dy >= INVALID_MOUSE_RANGE_HALF_HEIGHT)
        {
            client_cmd_right_hit_map(mouse_hand.point_x, mouse_hand.point_y);
            
            mouse_hand.right_down.type = mouse_hand.point_kind;
            mouse_hand.right_down.doing = HAND_DOING_CTRL_MAP;
            mouse_hand.right_down.time = timeGetTime();
            mouse_hand.right_down.x = mouse_hand.x;
            mouse_hand.right_down.y = mouse_hand.y;
        }
        break;

    case RT_NPC:
        client_cmd_right_hit_npc(mouse_hand.point_no);
        break;

    case RT_MAP_ITEM:
		// Jack, TODO [1/2/2003]
		// Left or Right ?
        client_cmd_left_hit_map_item(mouse_hand.point_x, mouse_hand.point_y);
        //client_cmd_right_hit_map_item(mouse_hand.point_x, mouse_hand.point_y);
        break;
    }
    return  0;
*/    
}

static  SLONG   buttonup_do_normal(SLONG player_index, SLONG magic_no, WPARAM wParam, LPARAM lParam)
{
    switch (mouse_hand.point_doing)
    {
    case HAND_DOING_LEFT_ITEM:
    case HAND_DOING_LEFT_MAGIC:
        client_cmd_left_end_hit_map(mouse_hand.point_x, mouse_hand.point_y);    
        break;
    case HAND_DOING_RIGHT_ITEM:
    case HAND_DOING_RIGHT_MAGIC:
        client_cmd_right_end_hit_map(mouse_hand.point_x, mouse_hand.point_y);
        break;
    }
    return  0;
    // mark by lijun 2003-05-21
/*
    switch (mouse_hand.point_doing)
    {
    case HAND_DOING_LEFT_ITEM:
    case HAND_DOING_LEFT_MAGIC:
        client_cmd_left_end_hit_map(mouse_hand.point_x, mouse_hand.point_y);    
        set_magic_area_visible(false);        
        break;
    case HAND_DOING_RIGHT_ITEM:
    case HAND_DOING_RIGHT_MAGIC:
        client_cmd_right_end_hit_map(mouse_hand.point_x, mouse_hand.point_y);
        set_magic_area_visible(false);
        break;
    }
    mouse_hand.point_doing = HAND_DOING_NOTHING;    
    return  0;
*/    
}

//buttonup functions ////////////////////////////////////////////////////////////
static  SLONG   dummy_buttonup_func(SLONG player_index, SLONG magic_no, WPARAM wParam, LPARAM lParam)
{
    return  0;
}

//mousemove functions ///////////////////////////////////////////////////////////
static  SLONG   dummy_mousemove_func(SLONG player_index, SLONG magic_no, WPARAM wParam, LPARAM lParam)
{
    return  0;
}
// mark by lijun 2003-05-21
/*
static  SLONG   buttondown_do_spower(SLONG player_index, SLONG magic_no, WPARAM wParam, LPARAM lParam)
{
    SLONG   mouse_x, mouse_y, map_x, map_y;
    SLONG   event_type, event_id;
    SLONG   dx, dy, npc_x, npc_y, npc_z, is_fight;

    mouse_x = GET_X_LPARAM(lParam);
    mouse_y = GET_Y_LPARAM(lParam);
    map_x = map_data.map_sx + mouse_x;
    map_y = map_data.map_sy + mouse_y;
    event_type = event_id = 0;
    game_range.mapping(mouse_x, mouse_y, &event_type, &event_id);
    set_mouse_hand_position(mouse_x, mouse_y);
    set_mouse_hand_point_info(event_type, event_id, map_x, map_y);
    switch(event_type)
    {
    case RT_MAP:
    case RT_NPC:
    case RT_MAP_ITEM:
        LOCK_CHARACTER(g_lPlayerIndex);
        GetCharacterPosition(g_lPlayerIndex, &npc_x, &npc_y, &npc_z);
		is_fight = IsCharacterOnFightState(g_lPlayerIndex);
        UNLOCK_CHARACTER(g_lPlayerIndex);

        dx = abs(mouse_hand.point_x - npc_x);
        dy = abs(mouse_hand.point_y - npc_y);
        if(dx >= INVALID_MOUSE_RANGE_HALF_WIDTH || dy >= INVALID_MOUSE_RANGE_HALF_HEIGHT)
        {
            client_cmd_right_hit_map(mouse_hand.point_x, mouse_hand.point_y);
            
            mouse_hand.right_down.type = mouse_hand.point_kind;
            mouse_hand.right_down.doing = HAND_DOING_CTRL_MAGIC;
            mouse_hand.right_down.time = timeGetTime();
            mouse_hand.right_down.x = mouse_hand.x;
            mouse_hand.right_down.y = mouse_hand.y;
            
            set_magic_area_type(MAGIC_AREA_TYPE_LINE);
            set_magic_area_orig_position(npc_x, npc_y);
            set_magic_area_dest_position(mouse_hand.point_x, mouse_hand.point_y);
            if(is_fight) set_magic_area_visible(true);
        }
        break;
    }
    return  0;
}
//�ļ�
static  SLONG   buttonup_do_clash(SLONG player_index, SLONG magic_no, WPARAM wParam, LPARAM lParam)
{
    SLONG   mouse_x, mouse_y, map_x, map_y;
    SLONG   event_type, event_id;

    mouse_x = GET_X_LPARAM(lParam);
    mouse_y = GET_Y_LPARAM(lParam);
    map_x = map_data.map_sx + mouse_x;
    map_y = map_data.map_sy + mouse_y;
    event_type = event_id = 0;
    game_range.mapping(mouse_x, mouse_y, &event_type, &event_id);
    set_mouse_hand_position(mouse_x, mouse_y);
    set_mouse_hand_point_info(event_type, event_id, map_x, map_y);

    switch(mouse_hand.right_down.doing)
    {
    case HAND_DOING_CTRL_MAGIC:
        client_cmd_right_end_hit_map(mouse_hand.point_x, mouse_hand.point_y);
        set_magic_area_visible(false);
        break;
    default:
        break;
    }
    mouse_hand.right_down.doing = HAND_DOING_NOTHING;
    //
    return  0;
}
*/