/*
**  Player.cpp
**  player functions.
**
**  Jack, 2002.5.20.
*/
#include "MainFun.h"
#include "NetGE_MainFunc.h"
#include "MapObject.h"
#include "UIManface.h"
#include "PosData.h"



//////////////////////////////////////////////////////////////////////////////////////////////
//GLOBALS                                                                                   //
//////////////////////////////////////////////////////////////////////////////////////////////
GAME_PLAYER     game_player[MAX_CHARACTER_PER_ZONE];


//////////////////////////////////////////////////////////////////////////////////////////////
//FUNCTIONS                                                                                 //
//////////////////////////////////////////////////////////////////////////////////////////////
/*
void    clear_player_list(void)
{
    SLONG   i;

    for(i = 0; i<MAX_CHARACTER_PER_ZONE; i++)
    {
        game_player[i].flag = 0;
        clear_player_item(i);
        clear_player_magic(i);
    }
}
*/

/*
void    get_player_manface(SLONG player_index, MANFACE_DATA *face)
{
    SLONG   career, sex, manchar_index;
    SLONG   eye_index, mouth_index;

    career = GetCharacterCareer(player_index);
    sex = GetCharacterSex(player_index);
    manchar_index = get_character_main_face(career, sex);
    eye_index = GetCharacterEyes(player_index);
    mouth_index = GetCharacterMouth(player_index);
    set_manface(face, manchar_index, eye_index, mouth_index);
}
*/

/******************************************************************************************************************/
/* 玩家法術(技能)相關函數                                                                                         */
/******************************************************************************************************************/
/*
void    init_player_magic(SLONG player_index)
{
    clear_player_magic(player_index);
}
*/

/*
void    clear_player_magic(SLONG player_index)
{
    GAME_PLAYER *p = &game_player[player_index];
    SLONG   i;

    for(i=0; i<MAX_PLAYER_MAGICS; i++)
    {
        p->magic[i].base = -1;
    }
}
*/


/*
SLONG   find_player_magic_room(SLONG player_index)
{
    GAME_PLAYER *p = &game_player[player_index];
    SLONG   room_index;
    //SLONG   i;

    room_index = -1;
    for(i=0; i<MAX_PLAYER_MAGICS; i++)
    {
        if(p->magic[i].base < 0)
        {
            room_index = i;
            break;
        }
    }
    return  room_index;
}
*/


	/*
SLONG   find_player_magic_index(SLONG player_index, SLONG magic_no)
{
    GAME_PLAYER *p = &game_player[player_index];
    SLONG   index;
    //SLONG   i;

    index = -1;
    for(i=0; i<MAX_PLAYER_MAGICS; i++)
    {
        if(p->magic[i].base == magic_no)
        {
            index = i;
            break;
        }
    }
    return  index;
}
	*/


/*
void    set_player_magic(SLONG player_index, SLONG room_index, MAGIC_ESSE me)
{
    game_player[player_index].magic[room_index] = me;
}


MAGIC_ESSE  get_player_magic(SLONG player_index, SLONG index)
{
    return  game_player[player_index].magic[index];
}


void    set_player_land_lhand_magic(SLONG player_index, SLONG magic_no)
{
    game_player[player_index].land_lhand_magic = magic_no;
}


SLONG   get_player_land_lhand_magic(SLONG player_index)
{
    return  game_player[player_index].land_lhand_magic;
}


void    set_player_land_rhand_magic(SLONG player_index, SLONG magic_no)
{
    game_player[player_index].land_rhand_magic = magic_no;
}


SLONG   get_player_land_rhand_magic(SLONG player_index)
{
    return  game_player[player_index].land_rhand_magic;
}


void    set_player_land_quick_magic(SLONG player_index, SLONG quick_index, QUICK_MAGIC qm)
{
    game_player[player_index].land_quick_magic[quick_index] = qm;
}


QUICK_MAGIC get_player_land_quick_magic(SLONG player_index, SLONG quick_index)
{
    return  game_player[player_index].land_quick_magic[quick_index];
}


SLONG   find_player_land_quick_magic_index(SLONG player_index, SLONG magic_no, SLONG hand)
{
    SLONG   i;
    QUICK_MAGIC qm;

    for(i=0; i<MAX_QUICK_MAGICS; i++)
    {
        qm = get_player_land_quick_magic(player_index, i);
        if(qm.base == magic_no && qm.hand == hand)
            return  i;
    }
    return  -1;
}


void    check_clear_player_land_quick_magic(SLONG player_index, SLONG magic_no)
{
    SLONG   i;
    QUICK_MAGIC qm, null_qm;

    null_qm.base = -1;
    for(i=0; i<MAX_QUICK_MAGICS; i++)
    {
        qm = get_player_land_quick_magic(player_index, i);
        if(qm.base == magic_no)
        {
            set_player_land_quick_magic(player_index, i, null_qm);
        }
    }
}


//
void    set_player_sea_lhand_magic(SLONG player_index, SLONG magic_no)
{
    game_player[player_index].sea_lhand_magic = magic_no;
}


SLONG   get_player_sea_lhand_magic(SLONG player_index)
{
    return  game_player[player_index].sea_lhand_magic;
}


void    set_player_sea_rhand_magic(SLONG player_index, SLONG magic_no)
{
    game_player[player_index].sea_rhand_magic = magic_no;
}


SLONG   get_player_sea_rhand_magic(SLONG player_index)
{
    return  game_player[player_index].sea_rhand_magic;
}


void    set_player_sea_quick_magic(SLONG player_index, SLONG quick_index, QUICK_MAGIC qm)
{
    game_player[player_index].sea_quick_magic[quick_index] = qm;
}


QUICK_MAGIC get_player_sea_quick_magic(SLONG player_index, SLONG quick_index)
{
    return  game_player[player_index].sea_quick_magic[quick_index];
}


SLONG   find_player_sea_quick_magic_index(SLONG player_index, SLONG magic_no, SLONG hand)
{
    SLONG   i;
    QUICK_MAGIC qm;

    for(i = 0; i < MAX_QUICK_MAGICS; i++)
    {
        qm = get_player_sea_quick_magic(player_index, i);
        if(qm.base == magic_no && qm.hand == hand)
            return  i;
    }
    return  -1;
}


void    check_clear_player_sea_quick_magic(SLONG player_index, SLONG magic_no)
{
    SLONG   i;
    QUICK_MAGIC qm, null_qm;

    null_qm.base = -1;
    for(i=0; i<MAX_QUICK_MAGICS; i++)
    {
        qm = get_player_sea_quick_magic(player_index, i);
        if(qm.base == magic_no)
        {
            set_player_sea_quick_magic(player_index, i, null_qm);
        }
    }
}
*/
/******************************************************************************************************************/
/* 玩家道具(物品)函數                                                                                             */
/******************************************************************************************************************/
/*
void    init_player_item(SLONG player_index)
{
    clear_player_item(player_index);
}


void    clear_player_item(SLONG player_index)
{
    SLONG   i;

    set_player_head_item(player_index, null_item);
    set_player_neck_item(player_index, null_item);
    set_player_body_item(player_index, null_item);
    set_player_hands_item(player_index, null_item);
    set_player_waist_item(player_index, null_item);
    set_player_lwrist_item(player_index, null_item);
    set_player_rwrist_item(player_index, null_item);
    set_player_feet_item(player_index, null_item);
    for(i=0; i<PLAYER_DECK_ITEMS; i++)
        set_player_deck_item(player_index, i, null_item);
    for(i=0; i<PLAYER_SASH_ITEMS; i++)
        set_player_sash_item(player_index, i, null_item);
    for(i=0; i<PLAYER_BAG_ITEMS; i++)
        set_player_bag_item(player_index, i, null_item);
    set_player_mouse_item(player_index, null_item);
}
*/


/*
ITEM_ESSE   get_player_head_item(SLONG player_index)
{
    return  game_player[player_index].head_item;
}


ITEM_ESSE   get_player_body_item(SLONG player_index)
{
    return  game_player[player_index].body_item;
}


ITEM_ESSE   get_player_neck_item(SLONG player_index)
{
    return  game_player[player_index].neck_item;
}


ITEM_ESSE   get_player_hands_item(SLONG player_index)
{
    return  game_player[player_index].hands_item;
}


ITEM_ESSE   get_player_waist_item(SLONG player_index)
{
    return  game_player[player_index].waist_item;
}


ITEM_ESSE   get_player_lwrist_item(SLONG player_index)
{
    return  game_player[player_index].lwrist_item;
}


ITEM_ESSE   get_player_rwrist_item(SLONG player_index)
{
    return  game_player[player_index].rwrist_item;
}


ITEM_ESSE   get_player_feet_item(SLONG player_index)
{
    return  game_player[player_index].feet_item;
}

ITEM_ESSE   get_player_deck_item(SLONG player_index, SLONG deck_index)
{
    return  game_player[player_index].deck_item[deck_index];
}


ITEM_ESSE   get_player_sash_item(SLONG player_index, SLONG sash_index)
{
    return  game_player[player_index].sash_item[sash_index];
}


ITEM_ESSE   get_player_bag_item(SLONG player_index, SLONG bag_index)
{
    return  game_player[player_index].bag_item[bag_index];
}


ITEM_ESSE   get_player_mouse_item(SLONG player_index)
{
    return  game_player[player_index].mouse_item;
}


void    set_player_head_item(SLONG player_index, ITEM_ESSE ie)
{
    game_player[player_index].head_item = ie;
}


void    set_player_body_item(SLONG player_index, ITEM_ESSE ie)
{
    game_player[player_index].body_item = ie;
}


void    set_player_neck_item(SLONG player_index, ITEM_ESSE ie)
{
    game_player[player_index].neck_item = ie;
}

void    set_player_hands_item(SLONG player_index, ITEM_ESSE ie)
{
    game_player[player_index].hands_item = ie;
}

void    set_player_waist_item(SLONG player_index, ITEM_ESSE ie)
{
    game_player[player_index].waist_item = ie;
}

void    set_player_lwrist_item(SLONG player_index, ITEM_ESSE ie)
{
    game_player[player_index].lwrist_item = ie;
}

void    set_player_rwrist_item(SLONG player_index, ITEM_ESSE ie)
{
    game_player[player_index].rwrist_item = ie;
}

void    set_player_feet_item(SLONG player_index, ITEM_ESSE ie)
{
    game_player[player_index].feet_item = ie;
}

void    set_player_deck_item(SLONG player_index, SLONG deck_index, ITEM_ESSE ie)
{
    game_player[player_index].deck_item[deck_index] = ie;
}

void    set_player_sash_item(SLONG player_index, SLONG sash_index, ITEM_ESSE ie)
{
    game_player[player_index].sash_item[sash_index] = ie;
}

void    set_player_bag_item(SLONG player_index, SLONG bag_index, ITEM_ESSE ie)
{
    game_player[player_index].bag_item[bag_index] = ie;
}

void    set_player_mouse_item(SLONG player_index, ITEM_ESSE ie)
{
    game_player[player_index].mouse_item = ie;
}
*/

/******************************************************************************************************************/
/* MISC FUNCTIONS                                                                                                 */
/******************************************************************************************************************/
/*
SLONG   is_player_bag_open(SLONG player_index)
{
    if(game_player[player_index].state & PLAYER_STATE_OPENED_BAG)
        return  TRUE;
    return  FALSE;
}

void    open_player_bag(SLONG player_index)
{
    game_player[player_index].state |= PLAYER_STATE_OPENED_BAG;
}


void    close_player_bag(SLONG player_index)
{
    game_player[player_index].state &= ~PLAYER_STATE_OPENED_BAG;
}
*/

/******************************************************************************************************************/
/* PLAYER DATA ASSOCIATED FUNCTIONS                                                                               */
/******************************************************************************************************************/
/*
USTR*   get_player_id(SLONG player_index)
{
    return  (USTR*)game_player[player_index].id;
}


void    set_player_mainname(SLONG player_index, USTR *mainname)
{
    strcpy((char *)game_player[player_index].mainname, (const char *)mainname);
}


USTR*   get_player_mainname(SLONG player_index)
{
    return  (USTR*)game_player[player_index].mainname;
}


void    set_player_nickname(SLONG player_index, USTR *nickname)
{
    strcpy((char *)game_player[player_index].nickname, (const char *)nickname);
}


USTR*   get_player_nickname(SLONG player_index)
{
    return  (USTR*)game_player[player_index].nickname;
}


void    set_player_color(SLONG player_index, SLONG color)
{
    game_player[player_index].color = color;
}


SLONG   get_player_color(SLONG player_index)
{
    return  game_player[player_index].color;
}


void    set_player_eyes(SLONG player_index, SLONG eyes)
{
    game_player[player_index].eyes = eyes;
}


SLONG   get_player_eyes(SLONG player_index)
{
    return  game_player[player_index].eyes;
}


void    set_player_mouth(SLONG player_index, SLONG mouth)
{
    game_player[player_index].mouth = mouth;
}


SLONG   get_player_mouth(SLONG player_index)
{
    return  game_player[player_index].mouth;
}


void    set_player_logo(SLONG player_index, SLONG logo)
{
    game_player[player_index].logo = logo;
}


SLONG   get_player_logo(SLONG player_index)
{
    return  game_player[player_index].logo;
}


void    set_player_picture(SLONG player_index, SLONG picture)
{
    game_player[player_index].picture = picture;
}


SLONG   get_player_picture(SLONG player_index)
{
    return  game_player[player_index].picture;
}


void    set_player_mainname_color(SLONG player_index, SLONG color)
{
    game_player[player_index].mainname_color = color;
}


SLONG   get_player_mainname_color(SLONG player_index)
{
    return  game_player[player_index].mainname_color;
}


void    set_player_nickname_color(SLONG player_index, SLONG color)
{
    game_player[player_index].nickname_color = color;
}


SLONG   get_player_nickname_color(SLONG player_index)
{
    return  game_player[player_index].nickname_color;
}


void    set_player_message_color(SLONG player_index, SLONG color)
{
    game_player[player_index].message_color = color;
}


SLONG   get_player_message_color(SLONG player_index)
{
    return  game_player[player_index].message_color;
}


void    set_player_talk_back_color(SLONG player_index, SLONG color)
{
    game_player[player_index].talk_back_color = color;
}


SLONG   get_player_talk_back_color(SLONG player_index)
{
    return  game_player[player_index].talk_back_color;
}


void    set_player_zone(SLONG player_index, USTR *zone)
{
    strcpy((char *)game_player[player_index].zone, (const char *)zone);
}


USTR*   get_player_zone(SLONG player_index)
{
    return  (USTR*)game_player[player_index].zone;
}


void    set_player_career(SLONG player_index, SLONG career)
{
    game_player[player_index].career = career;
}


SLONG   get_player_career(SLONG player_index)
{
    return  game_player[player_index].career;
}


void    set_player_guild(SLONG player_index, USTR *guild)
{
    strcpy((char *)game_player[player_index].guild, (const char *)guild);
}


USTR*   get_player_guild(SLONG player_index)
{
    return  (USTR*)game_player[player_index].guild;
}


void    set_player_country(SLONG player_index, SLONG country)
{
    game_player[player_index].country = country;
}


SLONG   get_player_country(SLONG player_index)
{
    return  game_player[player_index].country;
}


void    set_player_goodevil(SLONG player_index, SLONG goodevil)
{
    game_player[player_index].goodevil = goodevil;
}


SLONG   get_player_goodevil(SLONG player_index)
{
    return  game_player[player_index].goodevil;
}

void    set_player_nobility(SLONG player_index, USTR *nobility)
{
    strcpy((char *)game_player[player_index].nobility, (const char *)nobility);
}


USTR*   get_player_nobility(SLONG player_index)
{
    return  (USTR*)game_player[player_index].nobility;
}

void    set_player_sex(SLONG player_index, SLONG sex)
{
    game_player[player_index].sex = sex;
}


SLONG   get_player_sex(SLONG player_index)
{
    return  game_player[player_index].sex;
}


void    set_player_office(SLONG player_index, SLONG office)
{
    game_player[player_index].office = office;
}


SLONG   get_player_office(SLONG player_index)
{
    return  game_player[player_index].office;
}


void    set_player_prestige(SLONG player_index, SLONG prestige)
{
    game_player[player_index].prestige = prestige;
}


SLONG   get_player_prestige(SLONG player_index)
{
    return  game_player[player_index].prestige;
}


void    set_player_spouse_id(SLONG player_index, USTR *id)
{
    strcpy((char *)game_player[player_index].spouse_id, (const char *)id);
}


USTR*   get_player_spouse_id(SLONG player_index)
{
    return  (USTR*)game_player[player_index].spouse_id;
}


void    set_player_spouse_mainname(SLONG player_index, USTR *mainname)
{
    strcpy((char *)game_player[player_index].spouse_mainname, (const char *)mainname);
}


USTR*   get_player_spouse_mainname(SLONG player_index)
{
    return  (USTR*)game_player[player_index].spouse_mainname;
}


void    set_player_spouse_nickname(SLONG player_index, USTR *nickname)
{
    strcpy((char *)game_player[player_index].spouse_nickname, (const char *)nickname);
}


USTR*   get_player_spouse_nickname(SLONG player_index)
{
    return  (USTR*)game_player[player_index].spouse_nickname;
}


void    set_player_deposit(SLONG player_index, SLONG deposit)
{
    game_player[player_index].deposit = deposit;
}


SLONG   get_player_deposit(SLONG player_index)
{
    return  game_player[player_index].deposit;
}


void    set_player_level(SLONG player_index, SLONG level)
{
    game_player[player_index].level = level;
}


SLONG   get_player_level(SLONG player_index)
{
    return  (SLONG)game_player[player_index].level;
}


void    set_player_hp(SLONG player_index, SLONG hp)
{
    game_player[player_index].hp = hp;
}


SLONG   get_player_hp(SLONG player_index)
{
    return  (SLONG)game_player[player_index].hp;
}


void    set_player_max_hp(SLONG player_index, SLONG max_hp)
{
    game_player[player_index].max_hp = max_hp;
}


SLONG   get_player_max_hp(SLONG player_index)
{
    return  (SLONG)game_player[player_index].max_hp;
}


void    set_player_mp(SLONG player_index, SLONG mp)
{
    game_player[player_index].mp = mp;
}


SLONG   get_player_mp(SLONG player_index)
{
    return  (SLONG)game_player[player_index].mp;
}


void    set_player_max_mp(SLONG player_index, SLONG max_mp)
{
    game_player[player_index].mp2 = max_mp;
}


SLONG   get_player_max_mp(SLONG player_index)
{
    return  (SLONG)game_player[player_index].mp2;
}


void    set_player_strength(SLONG player_index, SLONG strength)
{
    game_player[player_index].strength = strength;
}


SLONG   get_player_strength(SLONG player_index)
{
    return  (SLONG)game_player[player_index].strength;
}


void    set_player_instinct(SLONG player_index, SLONG instinct)
{
    game_player[player_index].instinct = instinct;
}


SLONG   get_player_instinct(SLONG player_index)
{
    return  (SLONG)game_player[player_index].instinct;
}


void    set_player_wit(SLONG player_index, SLONG wit)
{
    game_player[player_index].wit = wit;
}


SLONG   get_player_wit(SLONG player_index)
{
    return  (SLONG)game_player[player_index].wit;
}


void    set_player_luck(SLONG player_index, SLONG luck)
{
    game_player[player_index].luck = luck;
}


SLONG   get_player_luck(SLONG player_index)
{
    return  (SLONG)game_player[player_index].luck;
}


void    set_player_ahurt(SLONG player_index, SLONG ahurt)
{
    game_player[player_index].ahurt = ahurt;
}


SLONG   get_player_ahurt(SLONG player_index)
{
    return  (SLONG)game_player[player_index].ahurt;
}


void    set_player_dp(SLONG player_index, SLONG dp)
{
    game_player[player_index].dp = dp;
}


SLONG   get_player_dp(SLONG player_index)
{
    return  (SLONG)game_player[player_index].dp;
}


void    set_player_aresist(SLONG player_index, SLONG aresist)
{
    game_player[player_index].aresist = aresist;
}


SLONG   get_player_aresist(SLONG player_index)
{
    return  (SLONG)game_player[player_index].aresist;
}


void    set_player_mresist(SLONG player_index, SLONG mresist)
{
    game_player[player_index].mresist = mresist;
}


SLONG   get_player_mresist(SLONG player_index)
{
    return  (SLONG)game_player[player_index].mresist;
}


void    set_player_exp(SLONG player_index, SLONG exp)
{
    game_player[player_index].exp = exp;
}


SLONG   get_player_exp(SLONG player_index)
{
    return  (SLONG)game_player[player_index].exp;
}


void    set_player_next_exp(SLONG player_index, SLONG next_exp)
{
    game_player[player_index].next_exp = next_exp;
}


SLONG   get_player_next_exp(SLONG player_index)
{
    return  (SLONG)game_player[player_index].next_exp;
}


void    set_player_upgrade_point(SLONG player_index, SLONG points)
{
    game_player[player_index].upgrade_point = points;
}


SLONG   get_player_upgrade_point(SLONG player_index)
{
    return  (SLONG)game_player[player_index].upgrade_point;
}
*/

/******************************************************************************************************************/
/* PLAYER RHAND MAGIC STATE FUNCTIONS                                                                             */
/******************************************************************************************************************/
/*
void    init_player_rhand_magic_state(SLONG player_index)
{
    GAME_PLAYER *player = &game_player[player_index];
    SLONG   magic_no;

    magic_no = get_player_rhand_magic(player_index);
    if( is_magic_need_prepare(magic_no) )
    {
        player->rhand_magic_state = MAGIC_STATE_PREPARE;
        player->rhand_magic_total = get_magic_prepare_ticks(magic_no);
        player->rhand_magic_ticks = 0;
    }
    else if( is_magic_need_spower(magic_no) )
    {
        player->rhand_magic_state = MAGIC_STATE_WAIT_SPOWER;
        player->rhand_magic_total = get_magic_spower_ticks(magic_no);
        player->rhand_magic_ticks = 0;
    }
    else
    {
        player->rhand_magic_state = MAGIC_STATE_OK;
        player->rhand_magic_total = 0;
        player->rhand_magic_ticks = 0;
    }
}


void    refresh_player_rhand_magic_state(SLONG player_index)
{
    GAME_PLAYER *player = &game_player[player_index];
    SLONG   magic_no;

    switch(player->rhand_magic_state)
    {
    case MAGIC_STATE_OK:
        break;
    case MAGIC_STATE_PREPARE:
        if(++player->rhand_magic_ticks >= player->rhand_magic_total)
        {
            magic_no = get_player_rhand_magic(player_index);
            if( is_magic_need_spower(magic_no) )
            {
                player->rhand_magic_state = MAGIC_STATE_WAIT_SPOWER;
                player->rhand_magic_total = get_magic_spower_ticks(magic_no);
                player->rhand_magic_ticks = 0;
            }
            else
            {
                player->rhand_magic_state = MAGIC_STATE_OK;
                player->rhand_magic_total = 0;
                player->rhand_magic_ticks = 0;
            }
        }
        break;
    case MAGIC_STATE_WAIT_SPOWER:
        break;
    case MAGIC_STATE_SPOWER:
        if(++player->rhand_magic_ticks >= player->rhand_magic_total)
        {
            player->rhand_magic_state = MAGIC_STATE_WAIT_BREAK;
            player->rhand_magic_ticks = 255;    //目前的alpha值
            player->rhand_magic_total = -1;     //當作alpha的增加或者減少標誌
        }
        break;
    case MAGIC_STATE_WAIT_BREAK:
        if(player->rhand_magic_total == 1)
        {
            player->rhand_magic_ticks += 32;
            if(player->rhand_magic_ticks > 255)
            {
                player->rhand_magic_ticks = 255;
                player->rhand_magic_total = -1;
            }
        }
        else
        {
            player->rhand_magic_ticks -= 32;
            if(player->rhand_magic_ticks < 128)
            {
                player->rhand_magic_ticks = 128;
                player->rhand_magic_total = 1;
            }
        }
        break;
    }
}


void    get_player_rhand_magic_state(SLONG player_index, SLONG *state, SLONG *ticks, SLONG *total)
{
    GAME_PLAYER *player = &game_player[player_index];

    if(state) *state = player->rhand_magic_state;
    if(ticks) *ticks = player->rhand_magic_ticks;
    if(total) *total = player->rhand_magic_total;
}


void    set_player_rhand_magic_start_spower(SLONG player_index)
{
    GAME_PLAYER *player = &game_player[player_index];

    if(player->rhand_magic_state == MAGIC_STATE_WAIT_SPOWER)
        player->rhand_magic_state = MAGIC_STATE_SPOWER;
}


SLONG   is_player_rhand_magic_can_break(SLONG player_index)
{
    GAME_PLAYER *player = &game_player[player_index];

    if(player->rhand_magic_state == MAGIC_STATE_WAIT_BREAK ||
        player->rhand_magic_state == MAGIC_STATE_OK)
        return  TRUE;
    return  FALSE;
}

*/
