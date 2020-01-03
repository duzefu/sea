/*
**	ServerMagicHit.cpp
**	server magic hit functions.
**
**	Jack, 2002/11/05.
*/
#include "ZoneServer_Def.h"

typedef struct tagMAGIC_HIT
{
    SLONG   (*hit_map_func)(SLONG player_index, SLONG magic_no, SLONG x, SLONG y);
    SLONG   (*hit_npc_func)(SLONG player_index, SLONG magic_no, SLONG npc_no);
    SLONG   (*hit_map_item_func)(SLONG player_index, SLONG magic_no, SLONG x, SLONG y);
    SLONG   (*end_hit_map_func)(SLONG player_index, SLONG magic_no, SLONG x, SLONG y);
} MAGIC_HIT, *LPMAGIC_HIT;


static  MAGIC_HIT   server_magic_hits[MAX_GAME_SKILL_BASES];
//
static  SLONG   dummy_hit_map_func(SLONG player_index, SLONG magic_no, SLONG x, SLONG y);
static  SLONG   dummy_hit_npc_func(SLONG player_index, SLONG magic_no, SLONG npc_no);
static  SLONG   dummy_hit_map_item_func(SLONG player_index, SLONG magic_no, SLONG x, SLONG y);
static  SLONG   dummy_end_hit_map_func(SLONG player_index, SLONG magic_no, SLONG x, SLONG y);
//
static  SLONG   server_skill_common_hit_map_func(SLONG player_index, SLONG magic_no, SLONG x, SLONG y);
static  SLONG   server_skill_common_hit_npc_func(SLONG player_index, SLONG magic_no, SLONG npc_no);
static  SLONG   server_skill_common_hit_map_item_func(SLONG player_index, SLONG magic_no, SLONG x, SLONG y);
static  SLONG   server_skill_common_end_hit_map_func(SLONG player_index, SLONG magic_no, SLONG x, SLONG y);
static  SLONG   server_hit_npc_for_sequential_attack(SLONG player_index, SLONG magic_no, SLONG npc_no);
//
//static  SLONG   server_hit_map_for_walk(SLONG player_index, SLONG magic_no, SLONG x, SLONG y);
//static  SLONG   server_hit_map_for_walk_or_spower(SLONG player_index, SLONG magic_no, SLONG x, SLONG y);
//static	SLONG	server_hit_map_for_walk_or_magic_position(SLONG player_index, SLONG magic_no, SLONG x, SLONG y);
//
//static  SLONG   server_end_hit_map_for_clash(SLONG player_index, SLONG magic_no, SLONG x, SLONG y);
//
//static  SLONG   server_hit_npc_for_talk(SLONG player_index, SLONG magic_no, SLONG npc_no);
//static  SLONG   server_hit_npc_for_talk_or_attack(SLONG player_index, SLONG magic_no, SLONG npc_no);
//static  SLONG   server_hit_npc_for_talk_or_sequential_attack(SLONG player_index, SLONG magic_no, SLONG npc_no);
//static	SLONG	server_hit_npc_for_talk_or_magic_position(SLONG player_index, SLONG magic_no, SLONG npc_no);
//static	SLONG	server_hit_map_for_magic_position(SLONG player_index, SLONG magic_no, SLONG x, SLONG y);
//
static	SLONG	server_hit_map_for_seawalk(SLONG player_index, SLONG magic_no, SLONG x, SLONG y);

/******************************************************************************************************************/
/* SERVER MAGIC HIT MAIN FUNCTIONS                                                                                */
/******************************************************************************************************************/
int     server_init_magic_hit(void)
{
    SLONG   i, index;

    //先初始化所有的函數.---------------------------------------------------------
    for(i = 0; i < MAX_GAME_SKILL_BASES; i++)
    {
        server_magic_hits[i].hit_map_func = dummy_hit_map_func;
        server_magic_hits[i].hit_npc_func = dummy_hit_npc_func;
        server_magic_hits[i].hit_map_item_func = dummy_hit_map_item_func;
        server_magic_hits[i].end_hit_map_func = dummy_end_hit_map_func;
        //add by lijun 2003-05-06    
        server_magic_hits[i].hit_map_func = server_skill_common_hit_map_func;
        server_magic_hits[i].hit_npc_func = server_skill_common_hit_npc_func;
        server_magic_hits[i].hit_map_item_func = server_skill_common_hit_map_item_func;
        server_magic_hits[i].end_hit_map_func = server_skill_common_end_hit_map_func;
    }

    //依據不同的技能, 分別設定.---------------------------------------------------
    index = MAGIC_NO_JOIN_TEAM; //組隊
    index = MAGIC_NO_LEAVE_TEAM;//離隊
    index = MAGIC_NO_TRADE;     //交易
    index = MAGIC_NO_FOLLOW;    //跟隨
    index = MAGIC_NO_IDENTIFY;  //鑒定
    //
    index = MAGIC_NO_WALK;      //行走
    //server_magic_hits[index].hit_map_func = server_hit_map_for_walk;
	//server_magic_hits[index].hit_npc_func = server_hit_npc_for_talk;
    //
    index = MAGIC_NO_MUSE;      //冥想
    //
    index = MAGIC_NO_ESCRIME;   //劍術
    //server_magic_hits[index].hit_map_func = server_hit_map_for_walk;
    //server_magic_hits[index].hit_npc_func = server_hit_npc_for_talk_or_attack;
    //
    index = MAGIC_NO_SEQUENTIAL_ESCRIME;    //連擊
    //server_magic_hits[index].hit_map_func = server_hit_map_for_walk;
    server_magic_hits[index].hit_npc_func = server_hit_npc_for_sequential_attack;
    //
    index = MAGIC_NO_STRONG;    //強壯
    index = MAGIC_NO_DEFENCE;   //格擋
    //
    index = MAGIC_NO_CLASH; //衝撞
    //server_magic_hits[index].hit_map_func = server_hit_map_for_walk_or_spower;
    //server_magic_hits[index].end_hit_map_func = server_end_hit_map_for_clash;
    //
    index = MAGIC_NO_PENETRABLE_ESCRIME;    //劍氣
    index = MAGIC_NO_KNOCK_TO_DIZZY;    //敲暈
    index = MAGIC_NO_FATAL_ESCRIME; //必殺劍
    //
    index = MAGIC_NO_SHOOT; //射擊
	//server_magic_hits[index].hit_map_func = server_hit_map_for_walk_or_magic_position;
	//server_magic_hits[index].hit_npc_func = server_hit_npc_for_talk_or_magic_position;

    index = MAGIC_NO_SEQUENTIAL_SHOOT;  //連射
	//server_magic_hits[index].hit_map_func = server_hit_map_for_walk_or_magic_position;
	//server_magic_hits[index].hit_npc_func = server_hit_npc_for_talk_or_magic_position;

    index = MAGIC_NO_EYES_SHOOT;    //打眼睛
    index = MAGIC_NO_DODGE; //躲閃
    index = MAGIC_NO_PENETRABLE_SHOOT;  //穿透彈
    index = MAGIC_NO_DOUBLE_SHOOT;  //雙倍彈藥

    index = MAGIC_NO_FEET_SHOOT;    //打腳

    index = MAGIC_NO_DIFFUSE_SHOOT; //掃射
	//server_magic_hits[index].hit_map_func = server_hit_map_for_walk_or_magic_position;
	//server_magic_hits[index].hit_npc_func = server_hit_npc_for_talk_or_magic_position;
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
	//server_magic_hits[index].hit_map_func = server_hit_map_for_walk_or_magic_position;
	//server_magic_hits[index].hit_npc_func = server_hit_npc_for_talk_or_magic_position;
    index = MAGIC_NO_SLEEP;//睡眠技
    index = MAGIC_NO_TORTOISE;//烏龜技
    index = MAGIC_NO_RESIST;//抵抗

    index = MAGIC_NO_DARK_BALL;//暗球
	//server_magic_hits[index].hit_map_func = server_hit_map_for_walk_or_magic_position;
	//server_magic_hits[index].hit_npc_func = server_hit_npc_for_talk_or_magic_position;
    index = MAGIC_NO_BEELINE_MAGIC;//直線魔法
	//server_magic_hits[index].hit_map_func = server_hit_map_for_walk_or_magic_position;
	//server_magic_hits[index].hit_npc_func = server_hit_npc_for_talk_or_magic_position;
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
	//
	index = MAGIC_NO_SEAWALK;
    server_magic_hits[index].hit_map_func = server_hit_map_for_seawalk;

	//index = MAGIC_NO_PRETEND;
	index = MAGIC_NO_ARMOUR_PIERCING_BALL;

	index = MAGIC_NO_LINK_BALL;
	index = MAGIC_NO_BURNT_BALL;
	index = MAGIC_NO_EMANATORY_BALL;
	index = MAGIC_NO_REPAIR_BOAT;

    return  0;
}


void    server_free_magic_hit(void)
{
}

//----
//  當mouse的鍵按下的時候需要處理的事情..在地圖上
//----
SLONG   server_exec_magic_hit_map_func(SLONG player_index, SLONG magic_no, SLONG x, SLONG y)
{
    //先判定該技能是否可以使用
    if (!IsSkillMouseDownCanUse(player_index, magic_no, 0, -1))
    {
        //服務器需要發送消息告訴..玩家..該技能不能使用
        return 0;
    }        
    return  server_magic_hits[magic_no].hit_map_func(player_index, magic_no, x, y);
}
//----
//  當mouse的鍵按下的時候需要處理的事情...在特別的npc身上
//----
SLONG   server_exec_magic_hit_npc_func(SLONG player_index, SLONG magic_no, SLONG npc_no)
{
    //先判定該技能是否可以使用
    if (!IsSkillMouseDownCanUse(player_index, magic_no, 0, npc_no))
    {
        //服務器需要發送消息告訴..玩家..該技能不能使用
        return 0;
    }        
    return  server_magic_hits[magic_no].hit_npc_func(player_index, magic_no, npc_no);
}

//----
//  當mouse的鍵按下的時候需要處理的事情...在特別的道具物品上
//----
SLONG   server_exec_magic_hit_map_item_func(SLONG player_index, SLONG magic_no, SLONG x, SLONG y)
{
    return  server_magic_hits[magic_no].hit_map_item_func(player_index, magic_no, x, y);
}
//----
//  當mouse的鍵鬆開的時候需要處理的事情...在特別的道具物品上
//----
SLONG   server_exec_magic_end_hit_map_func(SLONG player_index, SLONG magic_no, SLONG x, SLONG y)
{
    return  server_magic_hits[magic_no].end_hit_map_func(player_index, magic_no, x, y);
}

/******************************************************************************************************************/
/* STATIC DUMMY FUNCTIONS                                                                                         */
/******************************************************************************************************************/
static  SLONG   dummy_hit_map_func(SLONG player_index, SLONG magic_no, SLONG x, SLONG y)
{
    return  0;
}

static  SLONG   dummy_hit_npc_func(SLONG player_index, SLONG magic_no, SLONG npc_no)
{
    return  0;
}


static  SLONG   dummy_hit_map_item_func(SLONG player_index, SLONG magic_no, SLONG x, SLONG y)
{
    return  0;
}


static  SLONG   dummy_end_hit_map_func(SLONG player_index, SLONG magic_no, SLONG x, SLONG y)
{
    return  0;
}
/******************************************************************************************************************/
/*通用函數...                                                                                                     */
/* 關於技能..鼠標按鍵消息的控制                                                                                   */
/*  add by lijun 2003-05-06                                                                                       */
/******************************************************************************************************************/
//---
//  在這些函數裡面..表示該..戰鬥skill已經驗證通過...可以開始執行..對應技能的一些步驟
//
//---
static  SLONG   server_skill_common_hit_map_func(SLONG player_index, SLONG magic_no, SLONG x, SLONG y)
{
    SLONG   d1, d2, d3, d4,d5;
    SLONG   skill_level;
    SLONG   ai_block;
    SLONG   break_flag;
    //判斷npc當前所處的狀態可否替換...npc是主動改變自己的狀態
    LOCK_CHARACTER(player_index);    
    break_flag = IsCharacterSelfDoingKindBreak(player_index);
    skill_level = GetCharacterSpecialSkillLevel(player_index, magic_no); 
    UNLOCK_CHARACTER(player_index);
    if (break_flag)
    {
        //改變到npc新的狀態
        d1 = -1;
        d2 = x;
        d3 = y;
        d4 = 0;
        d5 = magic_no;
        //
        if (IsSkillNeedSpower(magic_no, skill_level))//判斷該技能是否需要蓄力
        {
            //改變ai到移動到目標點
            ai_block = MAIN_AI_BLOCK_SPOWER;//移動到目標點使用技能
            //魔法陣
            ServerCreateMagicArea(1, player_index, x, y, magic_no, skill_level);
        }
        else
        {
            //改變ai到移動到目標點
            ai_block = MAIN_AI_BLOCK_MOVE_SKILL;//移動到目標點使用技能
        }
        ServerChangeCharacterAiBlock(player_index, ai_block, d1, d2, d3, d4, d5);        
    }
    //
    return 0;
}
static  SLONG   server_skill_common_hit_npc_func(SLONG player_index, SLONG magic_no, SLONG npc_no)
{
    SLONG   d1, d2, d3, d4,d5;
    SLONG   skill_level;
    SLONG   ai_block;
    SLONG   break_flag;
	SLONG	npc_type;
	SLONG	npc_kind;
	SLONG	talk_with_npc = FALSE;
	
    //判斷npc當前所處的狀態可否替換...npc是主動改變自己的狀態
    LOCK_CHARACTER(player_index);    
    if (player_index >= MAX_PLAYER_PER_ZONE)
    {    
        npc_type = GetCharacterKind(player_index);
        npc_kind = (SLONG)NPCType[npc_type].Name.uiKind;
        switch(npc_kind)
        {
        case NPC_KIND_NPC:	
        case NPC_KIND_GUIDEPOST:
        case NPC_KIND_GUARD	:
        case NPC_KIND_TREASURE:
        case NPC_KIND_MERMAID:
        case NPC_KIND_STATUARY:
            talk_with_npc = TRUE;			
            break;
        }
    }
    break_flag = IsCharacterSelfDoingKindBreak(player_index);
    skill_level = GetCharacterSpecialSkillLevel(player_index, magic_no); 
    UNLOCK_CHARACTER(player_index);
    if (break_flag)
    {
		//改變到npc新的狀態
		d1 = npc_no;
		d2 = 0;
		d3 = 0;
		d4 = 0;
		d5 = magic_no;

		if(talk_with_npc == TRUE)
		{	
			ai_block = MAIN_AI_BLOCK_MOVE_TALK;
			ServerChangeCharacterAiBlock(player_index, ai_block, d1, d2, d3, d4, d5);        
		}
		else
		{					
			if (IsSkillNeedSpower(magic_no, skill_level))//判斷該技能是否需要蓄力
			{
				//改變ai到移動到目標點
				ai_block = MAIN_AI_BLOCK_SPOWER;//移動到目標點使用技能
				//魔法陣
				ServerCreateMagicArea(1, player_index, 0, 0, magic_no, skill_level);            
			}
			else
			{
				//改變ai到移動到目標點
				ai_block = MAIN_AI_BLOCK_MOVE_SKILL;//移動到目標點使用技能
			}
			ServerChangeCharacterAiBlock(player_index, ai_block, d1, d2, d3, d4, d5);        
		}        
    }
    //
    return 0;

}
static  SLONG   server_skill_common_hit_map_item_func(SLONG player_index, SLONG magic_no, SLONG x, SLONG y)
{
    return  0;
}
static  SLONG   server_skill_common_end_hit_map_func(SLONG player_index, SLONG magic_no, SLONG x, SLONG y)
{
    SLONG   skill_level;
    SLONG   ai_block;
    SLONG   d1,d2,d3,d4,d5;
    //
    LOCK_CHARACTER(player_index);    
    skill_level = GetCharacterSpecialSkillLevel(player_index, magic_no); 
    UNLOCK_CHARACTER(player_index);
    //判斷是否是蓄力技能
    if (IsSkillNeedSpower(magic_no, skill_level))
    {
        d1 = -1;
        d2 = x;
        d3 = y;
        d4 = 0;
        d5 = magic_no;
        //判斷蓄力的時間是否主夠
        //      足夠...使用技能的AI_BLOCK
        //      不夠...編為IDLE  的 AI_BLOCK
        if (IsCharacterRightHandMagicCanBreak(player_index))
            ai_block = MAIN_AI_BLOCK_USE_SKILL;        
        else
            ai_block = MAIN_AI_BLOCK_IDLE;
        //
        ServerChangeCharacterAiBlock(player_index, ai_block, d1, d2, d3, d4, d5);        
        //去掉魔法陣
        ServerCreateMagicArea(0, player_index, 0, 0, magic_no, skill_level);
    }
    //
    return  0;
}
//----
//  連續技
//----
static  SLONG   server_hit_npc_for_sequential_attack(SLONG player_index, SLONG magic_no, SLONG npc_no)
{
    SLONG   doing_kind;
    SLONG   curr_step;
    SLONG   sequential_step;
    SLONG   d1, d2, d3, d4;
    //
    LOCK_CHARACTER(player_index);
    doing_kind = GetCharacterDoingKind(player_index);
    curr_step = GetCharacterDoingStep(player_index);
    UNLOCK_CHARACTER(player_index);    
    //判斷當前的doingkind 是否在連擊中
    if (DOING_KIND_SEQUENTIAL_ATTACK_NPC == doing_kind)
    {
        d1 = d2 = d3 = d4 = 0;
        //
        LOCK_CHARACTER(player_index);
        sequential_step = GetCharacterSequentialStep(player_index);
        SetCharacterSequentialStep(player_index, sequential_step+1);
        UNLOCK_CHARACTER(player_index);  
        //該消息通知..npc..連擊成功
        ServerSendUpdateNpcDoing(player_index, DOING_KIND_SEQUENTIAL_ATTACK_NPC, curr_step,
				                 npc_no, d2, d3, d4, magic_no);			        
    }
    else
    {
        //
        server_skill_common_hit_npc_func(player_index, magic_no, npc_no);        
    }
    return 0;

/*
    enum 
    {   HIT_RESULT_NOTHING          =   0,
    HIT_RESULT_CHANGE_NPC_DOING     =   1, 
    HIT_RESULT_SEQUENTIAL_NPC_DOING =   2,
    };
    SLONG   is_fight, curr_doing, will_doing, curr_step;
    SLONG   hit_result;
    SLONG   d1, d2, d3, d4;
	SLONG	dest_doing_kind;

    //改變NPC的目前進行事務 -------------------------------------------------
    hit_result = HIT_RESULT_NOTHING;
    LOCK_CHARACTER(player_index);
    is_fight = IsCharacterOnFightState(player_index);
    curr_doing = GetCharacterDoingKind(player_index);
    curr_step = GetCharacterDoingStep(player_index);
	dest_doing_kind	= GetCharacterDoingKind(npc_no);

    if(dest_doing_kind != DOING_KIND_CHANGEMAP && is_fight)
    {
        will_doing = DOING_KIND_SEQUENTIAL_ATTACK_NPC;
        if(curr_doing == will_doing)
        {
            if(curr_step > 0)   //>0表示已經靠近了人物, 並且開始攻擊了
            {
                SetCharacterSequentialStep(player_index, true);
                hit_result = HIT_RESULT_SEQUENTIAL_NPC_DOING;
            }
        }
        else
        {
            if(IsHighPriorityDoingKind(curr_doing, will_doing))
            {
                d1 = npc_no;
                d2 = d3 = d4 = 0;
                ServerChangeCharacterDoing(player_index, will_doing, 0, d1, d2, d3, d4, magic_no);
                hit_result = HIT_RESULT_CHANGE_NPC_DOING;
            }
        }
    }
    else
    {
    }
    UNLOCK_CHARACTER(player_index);

    
    //將改變後的結果發送給所有人 ---------------------------------------------
    switch(hit_result)
    {
    case HIT_RESULT_NOTHING:
        break;

    case HIT_RESULT_CHANGE_NPC_DOING:
        {
			ServerSendChangeNpcDoing(player_index, will_doing, 0,
				d1, d2, d3, d4, magic_no);
        }
        break;

    case HIT_RESULT_SEQUENTIAL_NPC_DOING:
        {
			ServerSendUpdateNpcDoing(player_index, will_doing, curr_step,
				npc_no, d2, d3, d4, magic_no);			
        }
        break;
    }
    return  0;
*/    
}
/******************************************************************************************************************/
/* STATIC HIT MAP ITEM FUNCTIONS                                                                                  */
/******************************************************************************************************************/

/******************************************************************************************************************/
/* STATIC END HIT MAP FUNCTIONS                                                                                   */
/******************************************************************************************************************/

static	SLONG	server_hit_map_for_seawalk(SLONG player_index, SLONG magic_no, SLONG x, SLONG y)
{
    SLONG   curr_doing, will_doing, hp;
    SLONG   d1, d2, d3, d4;
    SLONG   hit_successful;

    hit_successful = false;
    LOCK_CHARACTER(player_index);
    curr_doing = GetCharacterDoingKind(player_index);
	hp = GetCharacterHp(player_index);
    if(curr_doing != DOING_KIND_CHANGEMAP && hp > 0)
    {
        will_doing = DOING_KIND_SEA_SAIL_TO;
        if(IsHighPriorityDoingKind(curr_doing, will_doing))
        {
            d1 = x;
            d2 = y;
            d3 = d4 = 0;
            ServerChangeCharacterDoing(player_index, will_doing, 0, d1, d2, d3, d4, magic_no);
            hit_successful = true;
        }
    }
    UNLOCK_CHARACTER(player_index);

    if(hit_successful)
    {
		ServerSendChangeNpcDoing(player_index, will_doing, 0,
			d1, d2, d3, d4, magic_no);
    }
    return  0;
}


/*
static  SLONG   server_hit_map_for_walk(SLONG player_index, SLONG magic_no, SLONG x, SLONG y)
{
    SLONG   curr_doing, will_doing, hp;
    SLONG   d1, d2, d3, d4;
    SLONG   hit_successful;

    hit_successful = false;
    LOCK_CHARACTER(player_index);
    curr_doing = GetCharacterDoingKind(player_index);
	hp = GetCharacterHp(player_index);
	//判斷npc所處的 doingKind 能夠替換
    if(curr_doing != DOING_KIND_CHANGEMAP && hp > 0)
    {
        will_doing = DOING_KIND_MOVE_TO;
        //判斷當前的doing_kind可否被中斷
        if(IsHighPriorityDoingKind(curr_doing, will_doing))
        {
            d1 = x;
            d2 = y;
            d3 = d4 = 0;
            //改變到新的doing_kind
            ServerChangeCharacterDoing(player_index, will_doing, 0, d1, d2, d3, d4, magic_no);
            hit_successful = true;
        }
    }
    UNLOCK_CHARACTER(player_index);
    //
    if(hit_successful)
    {
        //發消息通知所有的玩家
		ServerSendChangeNpcDoing(player_index, will_doing, 0,
								 d1, d2, d3, d4, magic_no);
    }
    return  0;
}


static  SLONG   server_hit_map_for_walk_or_spower(SLONG player_index, SLONG magic_no, SLONG x, SLONG y)
{
    SLONG   curr_doing, will_doing, hp, is_fight;
    SLONG   d1, d2, d3, d4;
    SLONG   hit_successful;

    hit_successful = false;
    LOCK_CHARACTER(player_index);
    curr_doing = GetCharacterDoingKind(player_index);
    is_fight = IsCharacterOnFightState(player_index);
	hp = GetCharacterHp(player_index);
    if(curr_doing != DOING_KIND_CHANGEMAP && hp > 0)
    {
        if(is_fight)
            will_doing = DOING_KIND_SPOWER;
        else
            will_doing = DOING_KIND_MOVE_TO;
        if(IsHighPriorityDoingKind(curr_doing, will_doing))
        {
            d1 = x;
            d2 = y;
            d3 = d4 = 0;
            ServerChangeCharacterDoing(player_index, will_doing, 0, d1, d2, d3, d4, magic_no);
            SetCharacterRightHandMagicStartSpower(player_index);
            hit_successful = true;
        }
    }
    UNLOCK_CHARACTER(player_index);

    if(hit_successful)
    {
		ServerSendChangeNpcDoing(player_index, will_doing, 0,
			d1, d2, d3, d4, magic_no);
    }
    return  0;
}


static	SLONG	server_hit_map_for_walk_or_magic_position(SLONG player_index, SLONG magic_no, SLONG x, SLONG y)
{
    SLONG   curr_doing, will_doing, hp, is_fight;
    SLONG   d1, d2, d3, d4;
    SLONG   hit_successful;

    hit_successful = false;
    LOCK_CHARACTER(player_index);
    curr_doing = GetCharacterDoingKind(player_index);
    is_fight = IsCharacterOnFightState(player_index);
	hp = GetCharacterHp(player_index);
    if(curr_doing != DOING_KIND_CHANGEMAP && hp > 0)
    {
        if(is_fight)
            will_doing = DOING_KIND_MAGIC_POSITION;
        else
            will_doing = DOING_KIND_MOVE_TO;
        if(IsHighPriorityDoingKind(curr_doing, will_doing))
        {
            d1 = x;
            d2 = y;
            d3 = d4 = 0;
            ServerChangeCharacterDoing(player_index, will_doing, 0, d1, d2, d3, d4, magic_no);
            hit_successful = true;
        }
    }
    UNLOCK_CHARACTER(player_index);

    if(hit_successful)
    {
		ServerSendChangeNpcDoing(player_index, will_doing, 0,
			d1, d2, d3, d4, magic_no);
    }
    return  0;
}

static  SLONG   server_end_hit_map_for_clash(SLONG player_index, SLONG magic_no, SLONG x, SLONG y)
{
    SLONG   npc_index, is_fight;
    SLONG   cur_doing, cmd_doing;
    SLONG   z = 0, clash_steps;
    SLONG   can_break, sth_change;

    npc_index = player_index;

    //clash is a right-hand magic.
    LOCK_CHARACTER(player_index);
    can_break = IsCharacterRightHandMagicCanBreak(player_index);
    UNLOCK_CHARACTER(player_index);

    sth_change = false;
    if(can_break)
    {   
        //釋放法術
        LOCK_CHARACTER(npc_index);
        cur_doing = GetCharacterDoingKind(npc_index);
        is_fight = IsCharacterOnFightState(npc_index);
        if(is_fight) 
        {
            cmd_doing = DOING_KIND_CLASH;
            if(IsHighPriorityDoingKind(cur_doing, cmd_doing))
            {
                clash_steps = 10;
                ServerChangeCharacterDoing(npc_index, cmd_doing, 0, x, y, z, clash_steps, magic_no);
                InitCharacterRightSkillState(npc_index);
                sth_change = true;
            }
        }
        UNLOCK_CHARACTER(npc_index);

        if(sth_change)
        {
			ServerSendChangeNpcDoing(npc_index, cmd_doing, 0,
				x, y, z,	clash_steps, magic_no);
        }
    }
    else
    {
        //取消法術蓄力
        cmd_doing = DOING_KIND_IDLE;

        LOCK_CHARACTER(npc_index);
        ServerChangeCharacterDoing(npc_index, DOING_KIND_IDLE, 0, x, y, z, 0, magic_no);
        InitCharacterRightSkillState(player_index);
        UNLOCK_CHARACTER(npc_index);

		ServerSendChangeNpcDoing(npc_index, DOING_KIND_IDLE, 0,
			x, y, z, 1, magic_no);        
    }

    return  0;
}


static  SLONG   server_hit_npc_for_talk(SLONG player_index, SLONG magic_no, SLONG npc_no)
{
    SLONG   is_fight, curr_doing, will_doing;
    SLONG   hit_successful;
    SLONG   d1, d2, d3, d4;
	SLONG	dest_doing_kind;

    //改變NPC的目前進行事務 -------------------------------------------------
    hit_successful = false;

    LOCK_CHARACTER(player_index);
    is_fight = IsCharacterOnFightState(player_index);
    curr_doing = GetCharacterDoingKind(player_index);
	dest_doing_kind = GetCharacterDoingKind(npc_no);	
	UNLOCK_CHARACTER(player_index);

	if(dest_doing_kind != DOING_KIND_CHANGEMAP && is_fight)	    
    {		
        will_doing = DOING_KIND_TALK_WITH_NPC;
        if(IsHighPriorityDoingKind(curr_doing, will_doing))
        {
            d1 = npc_no;
            d2 = d3 = d4 = 0;

			LOCK_CHARACTER(player_index);
            ServerChangeCharacterDoing(player_index, will_doing, 0, d1, d2, d3, d4, magic_no);
			UNLOCK_CHARACTER(player_index);

            hit_successful = true;
        }
    }
    else
    {
        // Jack, to be continue. [20:01,11/5/2002]        
        will_doing = DOING_KIND_TALK_WITH_NPC;
        if(IsHighPriorityDoingKind(curr_doing, will_doing))
        {
            d1 = npc_no;
            d2 = d3 = d4 = 0;
            ServerChangeCharacterDoing(player_index, will_doing, 0, d1, d2, d3, d4, magic_no);
            hit_successful = true;
        }        
    }
    
    //將改變後的結果發送給所有人 ---------------------------------------------
    if(hit_successful)
    {
		ServerSendChangeNpcDoing(player_index, will_doing, 0,
								   d1, d2, d3, d4, magic_no);
    }
    return  0;
}
static  SLONG   server_hit_npc_for_talk_or_attack(SLONG player_index, SLONG magic_no, SLONG npc_no)
{
    SLONG   is_fight, curr_doing, will_doing;
    SLONG   hit_successful;
    SLONG   d1, d2, d3, d4;
	SLONG	dest_doing_kind;

    //改變NPC的目前進行事務 -------------------------------------------------
    hit_successful = false;

    LOCK_CHARACTER(player_index);
    is_fight = IsCharacterOnFightState(player_index);
    curr_doing = GetCharacterDoingKind(player_index);
	dest_doing_kind = GetCharacterDoingKind(npc_no);	
	UNLOCK_CHARACTER(player_index);

	if(dest_doing_kind != DOING_KIND_CHANGEMAP && is_fight)	    
    {
        will_doing = DOING_KIND_ATTACK_NPC;
        if(IsHighPriorityDoingKind(curr_doing, will_doing))
        {
            d1 = npc_no;
            d2 = d3 = d4 = 0;

			LOCK_CHARACTER(player_index);
            ServerChangeCharacterDoing(player_index, will_doing, 0, d1, d2, d3, d4, magic_no);
			UNLOCK_CHARACTER(player_index);

            hit_successful = true;
        }
    }
    else
    {
        // Jack, to be continue. [20:01,11/5/2002]        
		will_doing = DOING_KIND_TALK_WITH_NPC;
		if(IsHighPriorityDoingKind(curr_doing, will_doing))
		{
			d1 = npc_no;
			d2 = d3 = d4 = 0;
			ServerChangeCharacterDoing(player_index, will_doing, 0, d1, d2, d3, d4, magic_no);
			hit_successful = true;
		}
        
    }    
    //將改變後的結果發送給所有人 ---------------------------------------------
    if(hit_successful)
    {
		ServerSendChangeNpcDoing(player_index, will_doing, 0,
								   d1, d2, d3, d4, magic_no);
    }
    return  0;
}


static  SLONG   server_hit_npc_for_talk_or_sequential_attack(SLONG player_index, SLONG magic_no, SLONG npc_no)
{
    enum 
    {   HIT_RESULT_NOTHING          =   0,
    HIT_RESULT_CHANGE_NPC_DOING     =   1, 
    HIT_RESULT_SEQUENTIAL_NPC_DOING =   2,
    };
    SLONG   is_fight, curr_doing, will_doing, curr_step;
    SLONG   hit_result;
    SLONG   d1, d2, d3, d4;
	SLONG	dest_doing_kind;

    //改變NPC的目前進行事務 -------------------------------------------------
    hit_result = HIT_RESULT_NOTHING;
    LOCK_CHARACTER(player_index);
    is_fight = IsCharacterOnFightState(player_index);
    curr_doing = GetCharacterDoingKind(player_index);
    curr_step = GetCharacterDoingStep(player_index);
	dest_doing_kind	= GetCharacterDoingKind(npc_no);

    if(dest_doing_kind != DOING_KIND_CHANGEMAP && is_fight)
    {
        will_doing = DOING_KIND_SEQUENTIAL_ATTACK_NPC;
        if(curr_doing == will_doing)
        {
            if(curr_step > 0)   //>0表示已經靠近了人物, 並且開始攻擊了
            {
                SetCharacterSequentialStep(player_index, true);
                hit_result = HIT_RESULT_SEQUENTIAL_NPC_DOING;
            }
        }
        else
        {
            if(IsHighPriorityDoingKind(curr_doing, will_doing))
            {
                d1 = npc_no;
                d2 = d3 = d4 = 0;
                ServerChangeCharacterDoing(player_index, will_doing, 0, d1, d2, d3, d4, magic_no);
                hit_result = HIT_RESULT_CHANGE_NPC_DOING;
            }
        }
    }
    else
    {
    }
    UNLOCK_CHARACTER(player_index);

    
    //將改變後的結果發送給所有人 ---------------------------------------------
    switch(hit_result)
    {
    case HIT_RESULT_NOTHING:
        break;

    case HIT_RESULT_CHANGE_NPC_DOING:
        {
			ServerSendChangeNpcDoing(player_index, will_doing, 0,
				d1, d2, d3, d4, magic_no);
        }
        break;

    case HIT_RESULT_SEQUENTIAL_NPC_DOING:
        {
			ServerSendUpdateNpcDoing(player_index, will_doing, curr_step,
				npc_no, d2, d3, d4, magic_no);			
        }
        break;
    }
    return  0;
}


static	SLONG	server_hit_npc_for_talk_or_magic_position(SLONG player_index, SLONG magic_no, SLONG npc_no)
{
    SLONG   is_fight, curr_doing, will_doing;
	SLONG	dest_x, dest_y, dest_z;
    SLONG   hit_successful;
    SLONG   d1, d2, d3, d4;
	SLONG	dest_doing_kind;

    //改變NPC的目前進行事務 -------------------------------------------------
    hit_successful = false;

    LOCK_CHARACTER(player_index);
    is_fight = IsCharacterOnFightState(player_index);
    curr_doing = GetCharacterDoingKind(player_index);
	//
	dest_doing_kind = GetCharacterDoingKind(npc_no);
	GetCharacterPosition(npc_no, &dest_x, &dest_y, &dest_z);
	UNLOCK_CHARACTER(player_index);
    
	if(dest_doing_kind != DOING_KIND_CHANGEMAP && is_fight)	    
    {
        will_doing = DOING_KIND_MAGIC_POSITION;
        if(IsHighPriorityDoingKind(curr_doing, will_doing))
        {
            d1 = dest_x;
            d2 = dest_y;
			d3 = d4 = 0;

			LOCK_CHARACTER(player_index);
            ServerChangeCharacterDoing(player_index, will_doing, 0, d1, d2, d3, d4, magic_no);
			UNLOCK_CHARACTER(player_index);

            hit_successful = true;
        }
    }
    else
    {
        will_doing = DOING_KIND_TALK_WITH_NPC;
        if(IsHighPriorityDoingKind(curr_doing, will_doing))
        {
            d1 = npc_no;
            d2 = d3 = d4 = 0;
            ServerChangeCharacterDoing(player_index, will_doing, 0, d1, d2, d3, d4, magic_no);
            hit_successful = true;
        }        
    }
    
    //將改變後的結果發送給所有人 ---------------------------------------------
    if(hit_successful)
    {
		ServerSendChangeNpcDoing(player_index, will_doing, 0,
								   d1, d2, d3, d4, magic_no);
    }
    return  0;
}
static	SLONG	server_hit_map_for_magic_position(SLONG player_index, SLONG magic_no, SLONG x, SLONG y)
{
	server_break_magic(0, player_index, x, y, magic_no);
	return	0;
}
*/
//-------------------------------------------------------------------------
//  End.
//-------------------------------------------------------------------------


