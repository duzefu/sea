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

    //����l�ƩҦ������.---------------------------------------------------------
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

    //�̾ڤ��P���ޯ�, ���O�]�w.---------------------------------------------------
    index = MAGIC_NO_JOIN_TEAM; //�ն�
    index = MAGIC_NO_LEAVE_TEAM;//����
    index = MAGIC_NO_TRADE;     //���
    index = MAGIC_NO_FOLLOW;    //���H
    index = MAGIC_NO_IDENTIFY;  //ų�w
    //
    index = MAGIC_NO_WALK;      //�樫
    //server_magic_hits[index].hit_map_func = server_hit_map_for_walk;
	//server_magic_hits[index].hit_npc_func = server_hit_npc_for_talk;
    //
    index = MAGIC_NO_MUSE;      //�߷Q
    //
    index = MAGIC_NO_ESCRIME;   //�C�N
    //server_magic_hits[index].hit_map_func = server_hit_map_for_walk;
    //server_magic_hits[index].hit_npc_func = server_hit_npc_for_talk_or_attack;
    //
    index = MAGIC_NO_SEQUENTIAL_ESCRIME;    //�s��
    //server_magic_hits[index].hit_map_func = server_hit_map_for_walk;
    server_magic_hits[index].hit_npc_func = server_hit_npc_for_sequential_attack;
    //
    index = MAGIC_NO_STRONG;    //�j��
    index = MAGIC_NO_DEFENCE;   //���
    //
    index = MAGIC_NO_CLASH; //�ļ�
    //server_magic_hits[index].hit_map_func = server_hit_map_for_walk_or_spower;
    //server_magic_hits[index].end_hit_map_func = server_end_hit_map_for_clash;
    //
    index = MAGIC_NO_PENETRABLE_ESCRIME;    //�C��
    index = MAGIC_NO_KNOCK_TO_DIZZY;    //�V�w
    index = MAGIC_NO_FATAL_ESCRIME; //�����C
    //
    index = MAGIC_NO_SHOOT; //�g��
	//server_magic_hits[index].hit_map_func = server_hit_map_for_walk_or_magic_position;
	//server_magic_hits[index].hit_npc_func = server_hit_npc_for_talk_or_magic_position;

    index = MAGIC_NO_SEQUENTIAL_SHOOT;  //�s�g
	//server_magic_hits[index].hit_map_func = server_hit_map_for_walk_or_magic_position;
	//server_magic_hits[index].hit_npc_func = server_hit_npc_for_talk_or_magic_position;

    index = MAGIC_NO_EYES_SHOOT;    //������
    index = MAGIC_NO_DODGE; //���{
    index = MAGIC_NO_PENETRABLE_SHOOT;  //��z�u
    index = MAGIC_NO_DOUBLE_SHOOT;  //�����u��

    index = MAGIC_NO_FEET_SHOOT;    //���}

    index = MAGIC_NO_DIFFUSE_SHOOT; //���g
	//server_magic_hits[index].hit_map_func = server_hit_map_for_walk_or_magic_position;
	//server_magic_hits[index].hit_npc_func = server_hit_npc_for_talk_or_magic_position;
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
	//server_magic_hits[index].hit_map_func = server_hit_map_for_walk_or_magic_position;
	//server_magic_hits[index].hit_npc_func = server_hit_npc_for_talk_or_magic_position;
    index = MAGIC_NO_SLEEP;//�ίv��
    index = MAGIC_NO_TORTOISE;//�Q�t��
    index = MAGIC_NO_RESIST;//���

    index = MAGIC_NO_DARK_BALL;//�t�y
	//server_magic_hits[index].hit_map_func = server_hit_map_for_walk_or_magic_position;
	//server_magic_hits[index].hit_npc_func = server_hit_npc_for_talk_or_magic_position;
    index = MAGIC_NO_BEELINE_MAGIC;//���u�]�k
	//server_magic_hits[index].hit_map_func = server_hit_map_for_walk_or_magic_position;
	//server_magic_hits[index].hit_npc_func = server_hit_npc_for_talk_or_magic_position;
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
//  ��mouse������U���ɭԻݭn�B�z���Ʊ�..�b�a�ϤW
//----
SLONG   server_exec_magic_hit_map_func(SLONG player_index, SLONG magic_no, SLONG x, SLONG y)
{
    //���P�w�ӧޯ�O�_�i�H�ϥ�
    if (!IsSkillMouseDownCanUse(player_index, magic_no, 0, -1))
    {
        //�A�Ⱦ��ݭn�o�e�����i�D..���a..�ӧޯण��ϥ�
        return 0;
    }        
    return  server_magic_hits[magic_no].hit_map_func(player_index, magic_no, x, y);
}
//----
//  ��mouse������U���ɭԻݭn�B�z���Ʊ�...�b�S�O��npc���W
//----
SLONG   server_exec_magic_hit_npc_func(SLONG player_index, SLONG magic_no, SLONG npc_no)
{
    //���P�w�ӧޯ�O�_�i�H�ϥ�
    if (!IsSkillMouseDownCanUse(player_index, magic_no, 0, npc_no))
    {
        //�A�Ⱦ��ݭn�o�e�����i�D..���a..�ӧޯण��ϥ�
        return 0;
    }        
    return  server_magic_hits[magic_no].hit_npc_func(player_index, magic_no, npc_no);
}

//----
//  ��mouse������U���ɭԻݭn�B�z���Ʊ�...�b�S�O���D�㪫�~�W
//----
SLONG   server_exec_magic_hit_map_item_func(SLONG player_index, SLONG magic_no, SLONG x, SLONG y)
{
    return  server_magic_hits[magic_no].hit_map_item_func(player_index, magic_no, x, y);
}
//----
//  ��mouse�����P�}���ɭԻݭn�B�z���Ʊ�...�b�S�O���D�㪫�~�W
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
/*�q�Ψ��...                                                                                                     */
/* ����ޯ�..���Ы������������                                                                                   */
/*  add by lijun 2003-05-06                                                                                       */
/******************************************************************************************************************/
//---
//  �b�o�Ǩ�Ƹ̭�..��ܸ�..�԰�skill�w�g���ҳq�L...�i�H�}�l����..�����ޯ઺�@�ǨB�J
//
//---
static  SLONG   server_skill_common_hit_map_func(SLONG player_index, SLONG magic_no, SLONG x, SLONG y)
{
    SLONG   d1, d2, d3, d4,d5;
    SLONG   skill_level;
    SLONG   ai_block;
    SLONG   break_flag;
    //�P�_npc��e�ҳB�����A�i�_����...npc�O�D�ʧ��ܦۤv�����A
    LOCK_CHARACTER(player_index);    
    break_flag = IsCharacterSelfDoingKindBreak(player_index);
    skill_level = GetCharacterSpecialSkillLevel(player_index, magic_no); 
    UNLOCK_CHARACTER(player_index);
    if (break_flag)
    {
        //���ܨ�npc�s�����A
        d1 = -1;
        d2 = x;
        d3 = y;
        d4 = 0;
        d5 = magic_no;
        //
        if (IsSkillNeedSpower(magic_no, skill_level))//�P�_�ӧޯ�O�_�ݭn�W�O
        {
            //����ai�첾�ʨ�ؼ��I
            ai_block = MAIN_AI_BLOCK_SPOWER;//���ʨ�ؼ��I�ϥΧޯ�
            //�]�k�}
            ServerCreateMagicArea(1, player_index, x, y, magic_no, skill_level);
        }
        else
        {
            //����ai�첾�ʨ�ؼ��I
            ai_block = MAIN_AI_BLOCK_MOVE_SKILL;//���ʨ�ؼ��I�ϥΧޯ�
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
	
    //�P�_npc��e�ҳB�����A�i�_����...npc�O�D�ʧ��ܦۤv�����A
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
		//���ܨ�npc�s�����A
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
			if (IsSkillNeedSpower(magic_no, skill_level))//�P�_�ӧޯ�O�_�ݭn�W�O
			{
				//����ai�첾�ʨ�ؼ��I
				ai_block = MAIN_AI_BLOCK_SPOWER;//���ʨ�ؼ��I�ϥΧޯ�
				//�]�k�}
				ServerCreateMagicArea(1, player_index, 0, 0, magic_no, skill_level);            
			}
			else
			{
				//����ai�첾�ʨ�ؼ��I
				ai_block = MAIN_AI_BLOCK_MOVE_SKILL;//���ʨ�ؼ��I�ϥΧޯ�
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
    //�P�_�O�_�O�W�O�ޯ�
    if (IsSkillNeedSpower(magic_no, skill_level))
    {
        d1 = -1;
        d2 = x;
        d3 = y;
        d4 = 0;
        d5 = magic_no;
        //�P�_�W�O���ɶ��O�_�D��
        //      ����...�ϥΧޯ઺AI_BLOCK
        //      ����...�s��IDLE  �� AI_BLOCK
        if (IsCharacterRightHandMagicCanBreak(player_index))
            ai_block = MAIN_AI_BLOCK_USE_SKILL;        
        else
            ai_block = MAIN_AI_BLOCK_IDLE;
        //
        ServerChangeCharacterAiBlock(player_index, ai_block, d1, d2, d3, d4, d5);        
        //�h���]�k�}
        ServerCreateMagicArea(0, player_index, 0, 0, magic_no, skill_level);
    }
    //
    return  0;
}
//----
//  �s���
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
    //�P�_��e��doingkind �O�_�b�s����
    if (DOING_KIND_SEQUENTIAL_ATTACK_NPC == doing_kind)
    {
        d1 = d2 = d3 = d4 = 0;
        //
        LOCK_CHARACTER(player_index);
        sequential_step = GetCharacterSequentialStep(player_index);
        SetCharacterSequentialStep(player_index, sequential_step+1);
        UNLOCK_CHARACTER(player_index);  
        //�Ӯ����q��..npc..�s�����\
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

    //����NPC���ثe�i��ư� -------------------------------------------------
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
            if(curr_step > 0)   //>0��ܤw�g�a��F�H��, �åB�}�l�����F
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

    
    //�N���ܫ᪺���G�o�e���Ҧ��H ---------------------------------------------
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
	//�P�_npc�ҳB�� doingKind �������
    if(curr_doing != DOING_KIND_CHANGEMAP && hp > 0)
    {
        will_doing = DOING_KIND_MOVE_TO;
        //�P�_��e��doing_kind�i�_�Q���_
        if(IsHighPriorityDoingKind(curr_doing, will_doing))
        {
            d1 = x;
            d2 = y;
            d3 = d4 = 0;
            //���ܨ�s��doing_kind
            ServerChangeCharacterDoing(player_index, will_doing, 0, d1, d2, d3, d4, magic_no);
            hit_successful = true;
        }
    }
    UNLOCK_CHARACTER(player_index);
    //
    if(hit_successful)
    {
        //�o�����q���Ҧ������a
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
        //����k�N
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
        //�����k�N�W�O
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

    //����NPC���ثe�i��ư� -------------------------------------------------
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
    
    //�N���ܫ᪺���G�o�e���Ҧ��H ---------------------------------------------
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

    //����NPC���ثe�i��ư� -------------------------------------------------
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
    //�N���ܫ᪺���G�o�e���Ҧ��H ---------------------------------------------
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

    //����NPC���ثe�i��ư� -------------------------------------------------
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
            if(curr_step > 0)   //>0��ܤw�g�a��F�H��, �åB�}�l�����F
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

    
    //�N���ܫ᪺���G�o�e���Ҧ��H ---------------------------------------------
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

    //����NPC���ثe�i��ư� -------------------------------------------------
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
    
    //�N���ܫ᪺���G�o�e���Ҧ��H ---------------------------------------------
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


