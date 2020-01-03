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
    index = MAGIC_NO_JOIN_TEAM; //組隊
    index = MAGIC_NO_LEAVE_TEAM;//離隊
    index = MAGIC_NO_TRADE;     //交易
    index = MAGIC_NO_FOLLOW;    //跟隨
    index = MAGIC_NO_IDENTIFY;  //鑒定
    //
    index = MAGIC_NO_WALK;      //行走
    //magic_hits[index].buttondown_func = buttondown_do_normal;

    index = MAGIC_NO_MUSE;      //冥想

    index = MAGIC_NO_ESCRIME;   //劍術
    //magic_hits[index].buttondown_func = buttondown_do_normal;

    index = MAGIC_NO_SEQUENTIAL_ESCRIME;    //連擊
    //magic_hits[index].buttondown_func = buttondown_do_normal;

    index = MAGIC_NO_STRONG;    //強壯

    index = MAGIC_NO_DEFENCE;   //格擋

    index = MAGIC_NO_CLASH; //衝撞
    //magic_hits[index].buttondown_func = buttondown_do_spower;
    //magic_hits[index].buttonup_func   = buttonup_do_clash;

    index = MAGIC_NO_PENETRABLE_ESCRIME;    //劍氣
    index = MAGIC_NO_KNOCK_TO_DIZZY;    //敲暈
    index = MAGIC_NO_FATAL_ESCRIME; //必殺劍
    //
    index = MAGIC_NO_SHOOT; //射擊
    //magic_hits[index].buttondown_func = buttondown_do_normal;

    index = MAGIC_NO_SEQUENTIAL_SHOOT;  //連射
    //magic_hits[index].buttondown_func = buttondown_do_normal;

    index = MAGIC_NO_EYES_SHOOT;    //打眼睛
    index = MAGIC_NO_DODGE; //躲閃
    index = MAGIC_NO_PENETRABLE_SHOOT;  //穿透彈
    index = MAGIC_NO_DOUBLE_SHOOT;  //雙倍彈藥
    index = MAGIC_NO_FEET_SHOOT;    //打腳

    index = MAGIC_NO_DIFFUSE_SHOOT; //掃射
    //magic_hits[index].buttondown_func = buttondown_do_normal;
    //
    index = MAGIC_NO_BOOK_READ; //讀書
    index = MAGIC_NO_CURE;  //治療
    index = MAGIC_NO_DEFEND_MIRROR; //防禦鏡
    index = MAGIC_NO_RELIVE;//復活
    index = MAGIC_NO_BAPTISM;//洗禮
    index = MAGIC_NO_MAGIC_MIRROR;//魔法鏡
    index = MAGIC_NO_ENRICH_BLOOD;//大補血
    index = MAGIC_NO_INFINITE_KINDNESS;//神恩浩蕩

    index = MAGIC_NO_DARK_STAR;//暗星
    //magic_hits[index].buttondown_func = buttondown_do_normal;

    index = MAGIC_NO_SLEEP;//睡眠技
    index = MAGIC_NO_TORTOISE;//烏龜技
    index = MAGIC_NO_RESIST;//抵抗

    index = MAGIC_NO_DARK_BALL;//暗球
    //magic_hits[index].buttondown_func = buttondown_do_normal;

    index = MAGIC_NO_BEELINE_MAGIC;//直線魔法
    //magic_hits[index].buttondown_func = buttondown_do_normal;

    index = MAGIC_NO_AZRAEL;//死神
    index = MAGIC_NO_DEVIL;//惡魔
    //
    index = MAGIC_NO_THONG;//皮鞭
    index = MAGIC_NO_CIRRUS_TRAP;//藤蔓陷阱
    index = MAGIC_NO_BEAST_TRAP;//捕獸夾
    index = MAGIC_NO_ERUPTIVE_THONG;//皮鞭蓄力
    index = MAGIC_NO_RAVEL_TRAP;//解除陷阱
    index = MAGIC_NO_PREDICT;//預感
    index = MAGIC_NO_STONE_TRAP;//巨石陷阱
    index = MAGIC_NO_PRETEND;//偽裝
    index = MAGIC_NO_LANDMINE;//地雷
    //
    index = MAGIC_NO_DAGGER;//匕首
    index = MAGIC_NO_BEHIND_DAGGER;//背刺
    index = MAGIC_NO_STEAL;//偷竊
    index = MAGIC_NO_UNLOCK;//開鎖
    index = MAGIC_NO_HIDE;//隱形
    index = MAGIC_NO_POISON;//下毒
    index = MAGIC_NO_GOLD;//金幣
    index = MAGIC_NO_NEGOTIATE;//談判
    index = MAGIC_NO_ATTRACT_MONSTER;//吸引怪物
    index = MAGIC_NO_BOX_TRAP;//寶箱陷阱
    index = MAGIC_NO_CONTROL_MONSTER;//怪物控制
    //
    index = MAGIC_NO_CHOP;//砍殺
    index = MAGIC_NO_TOXOPHILY;//射箭
    index = MAGIC_NO_RELIVE_2;//復活二
    index = MAGIC_NO_SUCK_BLOOD;//吸血
    index = MAGIC_NO_SUCK_MAGIC;//吸魔
    index = MAGIC_NO_DESTROY_ARMOR;//防具破壞
    index = MAGIC_NO_RELIVE_3;//復活三
    index = MAGIC_NO_HIDE_2;//隱身二
    index = MAGIC_NO_FIRE_BALL;//火球
    index = MAGIC_NO_EXPLODE;//自爆一
    index = MAGIC_NO_EXPLODE_2;//自爆二
    index = MAGIC_NO_BREAK_EQUIP;//打裝備
    index = MAGIC_NO_RECALL;//召喚
    index = MAGIC_NO_CHANGE_FORM;//變身
    index = MAGIC_NO_INSURANCE;//保險
    index = MAGIC_NO_INSURANCE_2;//保險二
    index = MAGIC_NO_INSURANCE_3;//保險三
    index = MAGIC_NO_INSURANCE_4;//保險四
    index = MAGIC_NO_INSURANCE_5;//保險五

	//sea skill functions ----------------------------------------------------
    //海上技能的處理
    index = MAGIC_NO_SEAWALK;      //行走
    //magic_hits[index].buttondown_func = buttondown_do_normal;
    //
    index = MAGIC_NO_PRETEND;//偽裝
    index = MAGIC_NO_ARMOUR_PIERCING_BALL;//穿甲彈

    index = MAGIC_NO_LINK_BALL;//鏈彈
	//magic_hits[index].buttondown_func = buttondown_do_normal;

    index = MAGIC_NO_BURNT_BALL;//燃燒彈
    index = MAGIC_NO_EMANATORY_BALL;//散彈
    index = MAGIC_NO_REPAIR_BOAT;//修理
}

//----
//  當鼠標鍵按下時候發出的消息
//----
SLONG   exec_magic_buttondown(SLONG player_index, SLONG magic_no, WPARAM wParam, LPARAM lParam)
{
    return  magic_hits[magic_no].buttondown_func(player_index, magic_no, wParam, lParam);
}
//----
//  當鼠標鍵鬆開時候發出的消息
//----
SLONG   exec_magic_buttonup(SLONG player_index, SLONG magic_no, WPARAM wParam, LPARAM lParam)
{
    return  magic_hits[magic_no].buttonup_func(player_index, magic_no, wParam, lParam);
}

//----
//  當鼠標鍵移動時候發出的消息
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
//衝撞
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