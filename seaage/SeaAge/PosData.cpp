/*
**	posdata.cpp
**	psalm of sea data.
**
**	Jack, 2002/07/15.
*/
#include "mainfun.h"
#include "NetGE_MainFunc.h"
#include "posdata.h"
#include "ClientMain.h"
#include "ErrorMsg.h"
#include "MainGame.h"
#include "Media.h"


/******************************************************************************************************************/
/* GLOBALS                                                                                                        */
/******************************************************************************************************************/
MONSTER_GROUP       game_monster_group[MAX_GAME_MONSTER_GROUPS];
MAP_INFO            game_map_info[MAX_GAME_MAP_INFOS];
NPC_BASE            game_npc_base[MAX_GAME_NPC_BASES];
MAP_MONSTER_SET     map_monster_set[MAX_MAP_MONSTER_SETS];
MANCHAR_SET         manchar_set[MAX_GAME_MANCHAR];
NEW_CHARACTER_CONFIG    new_character_config;   //新創建人物設定
CHANGE_MAP_DATA     change_map_data;    //切換地圖設定
CHAR_COLOR_SET		char_color_set[MAX_GAME_MANCHAR];


/******************************************************************************************************************/
/* GAME DATA MAIN FUNCTIONS                                                                                       */
/******************************************************************************************************************/
int     init_game_data(void)
{
    if(TTN_OK != load_game_monster_group())
        return  -2;

    if(TTN_OK != load_game_map_info())
        return  -3;

    if(TTN_OK != load_game_npc_base())
        return  -4;

    init_manchar_set();
    if(TTN_OK != load_manchar_set())
        return  -5;

	init_char_color_set();
	if(TTN_OK != load_char_color_set())
		return	-6;
	debug_log_char_color_set();

    clear_map_monster_set();

    init_change_map_data();
    init_game_config();

    return  0;
}


void    active_game_data(int active)
{
    active_game_config(active);
}


void    free_game_data(void)
{
    free_game_config();
}




/******************************************************************************************************************/
/* GAME INFORMATION FUNCTIONS                                                                                     */
/******************************************************************************************************************/
char*   get_country_name(SLONG country)
{
    switch(country)
    {
    case COUNTRY_CHINA: return (char *)TEXTMSG_COUNTRY_NAME_CHINA;
    case COUNTRY_ENGLAND: return (char *)TEXTMSG_COUNTRY_NAME_ENGLAND;
    case COUNTRY_SWEDEN: return (char *)TEXTMSG_COUNTRY_NAME_SWEDEN;
    case COUNTRY_FRANCE: return (char *)TEXTMSG_COUNTRY_NAME_FRANCE;
    case COUNTRY_GERMANY: return (char *)TEXTMSG_COUNTRY_NAME_GERMANY;
    case COUNTRY_SPAIN: return (char *)TEXTMSG_COUNTRY_NAME_SPAIN;
    case COUNTRY_PORTUGAL: return (char *)TEXTMSG_COUNTRY_NAME_PORTUGAL;
    case COUNTRY_ITALY:	return (char *)TEXTMSG_COUNTRY_NAME_ITALY;
    case COUNTRY_DENMRKE: return (char *)TEXTMSG_COUNTRY_NAME_DENMRKE;
    case COUNTRY_FINLAND: return (char *)TEXTMSG_COUNTRY_NAME_FINLAND;
    case COUNTRY_GREECE: return (char *)TEXTMSG_COUNTRY_NAME_GREECE;
    case COUNTRY_NORWAY: return (char *)TEXTMSG_COUNTRY_NAME_NORWAY;
    case COUNTRY_IRELAND: return (char *)TEXTMSG_COUNTRY_NAME_IRELAND;
    case COUNTRY_TUNIS: return (char *)TEXTMSG_COUNTRY_NAME_TUNIS;
    case COUNTRY_ARAB: return (char *)TEXTMSG_COUNTRY_NAME_ARAB;
    case COUNTRY_TURKEY: return (char *)TEXTMSG_COUNTRY_NAME_TURKEY;
    case COUNTRY_AFRICA: return (char *)TEXTMSG_COUNTRY_NAME_AFRICA;
    case COUNTRY_KOREA: return (char *)TEXTMSG_COUNTRY_NAME_KOREA;
    case COUNTRY_JAPAN: return (char *)TEXTMSG_COUNTRY_NAME_JAPAN;
    case COUNTRY_INDIA: return (char *)TEXTMSG_COUNTRY_NAME_INDIA;
    default: return (char *)TEXTMSG_COUNTRY_NAME_DUMMY;
    }
}


char*   get_career_name(SLONG career)
{
    switch(career)
    {
    case CAREER_GENERAL: return (char *)TEXTMSG_CAREER_NAME_GENERAL;
    case CAREER_SWORDER: return (char *)TEXTMSG_CAREER_NAME_SWORDER;
    case CAREER_THIEF: return (char *)TEXTMSG_CAREER_NAME_THIEF;
    case CAREER_TRADER: return (char *)TEXTMSG_CAREER_NAME_TRADER;
    case CAREER_EXPLORER: return (char *)TEXTMSG_CAREER_NAME_EXPLORER;
    case CAREER_CLERIC: return (char *)TEXTMSG_CAREER_NAME_CLERIC;
    case CAREER_HOROSCOPER: return (char *)TEXTMSG_CAREER_NAME_HOROSCOPER;
    default: return (char *)TEXTMSG_CAREER_NAME_DUMMY;
    }
}


char*   get_sex_name(SLONG sex)
{
    switch(sex)
    {
    case SEX_MALE: return (char *)TEXTMSG_SEX_NAME_MALE;
    case SEX_FEMALE: return (char *)TEXTMSG_SEX_NAME_FEMALE;
    default: return (char *)TEXTMSG_SEX_NAME_DUMMY;
    }
}


char*   get_weather_description(SLONG weather_type)
{
    switch(weather_type)
    {
    case WEATHER_TYPE_WIND: return  (char*)TEXTMSG_WEATHER_TYPE_NAME_WIND;
    case WEATHER_TYPE_FINE: return  (char*)TEXTMSG_WEATHER_TYPE_NAME_FINE;
    case WEATHER_TYPE_RAIN: return  (char*)TEXTMSG_WEATHER_TYPE_NAME_RAIN;
    case WEATHER_TYPE_THUNDER:  return  (char*)TEXTMSG_WEATHER_TYPE_NAME_THUNDER;
    case WEATHER_TYPE_FOG:  return  (char*)TEXTMSG_WEATHER_TYPE_NAME_FOG;
    default:    return  (char*)TEXTMSG_WEATHER_TYPE_DUMMY;
    }
}



SLONG   get_character_main_face(SLONG career, SLONG sex)
{
    SLONG   career_added, sex_added, face;

    switch(sex)
    {
    case SEX_MALE: sex_added = 0; break;
    case SEX_FEMALE: sex_added = 1; break;
    default: sex_added = 0; break;
    }
    switch(career)
    {
    case CAREER_GENERAL: career_added = 0; break;
    case CAREER_SWORDER: career_added = 1; break;
    case CAREER_THIEF: career_added = 2; break;
    case CAREER_TRADER: career_added = 3; break;
    case CAREER_EXPLORER: career_added = 4; break;
    case CAREER_CLERIC: career_added = 5; break;
    case CAREER_HOROSCOPER: career_added = 6; break;
    default: career_added = 0; break;
    }

    face = career_added * 2 + sex_added;
    return  face;
}


SLONG   get_career_default_lhand_map_magic_no(SLONG career)
{
    return  MAGIC_NO_WALK;
}


SLONG   get_career_default_lhand_fight_magic_no(SLONG career)
{
    SLONG   magic_no;

    // Jack, todo [12:12,9/28/2002]
    magic_no = MAGIC_NO_WALK;
    switch(career)
    {
    case CAREER_SWORDER:   //劍士
        magic_no = MAGIC_NO_ESCRIME;
        break;
    case CAREER_GENERAL:   //提督
        magic_no = MAGIC_NO_SHOOT;
        break;
    case CAREER_THIEF:     //小偷
        magic_no = MAGIC_NO_DAGGER;
        break;
    case CAREER_TRADER:    //商人
        magic_no = MAGIC_NO_BOOK_READ;
        break;
    case CAREER_EXPLORER:  //探險家
        magic_no = MAGIC_NO_THONG;
        break;
    case CAREER_CLERIC:    //牧師
        magic_no = MAGIC_NO_DARK_STAR;
        break;
    case CAREER_HOROSCOPER://占星術士
        magic_no = MAGIC_NO_DARK_STAR;
        break;
    }
    return  magic_no;
}


//載入遊戲怪物群組設定
SLONG   load_game_monster_group(void)
{
    enum {LINE_BUFFER_SIZE = 1024};
    USTR    *file_buf;
    SLONG   file_size, pass, result, buffer_index;
    USTR    line[LINE_BUFFER_SIZE];
    SLONG   index;
    SLONG   len;
    SLONG   data_index, i;
    MONSTER_GROUP   *data = NULL;

    set_data_file(packed_data_file);
    file_size = load_file_to_buffer((USTR*)"data\\mongroup.ini", &file_buf);
    if(file_size < 0)
        goto error;

    pass = 0;
    buffer_index = 0;
    result = get_buffer_line((char*)file_buf, &buffer_index, file_size, (char*)line, LINE_BUFFER_SIZE);
    while((result == TTN_OK) && (pass == 0))
    {
        len = ( SLONG )strlen( ( const char* )line );
        if( ( line[0] != 0x00 ) && ( line[0] != ';' ) )
        {
            index = 0;
            data_index = get_buffer_number(line, &index);
            if(data_index >= 0 && data_index < MAX_GAME_MONSTER_GROUPS)
            {
                data = &game_monster_group[data_index];
                data->header_monster = get_buffer_number(line, &index);
                for(i=0; i<NORMAL_MONSTERS_PER_GROUP; i++)
                {
                    data->normal_monster[i] = get_buffer_number(line, &index);
                }
            }
        }
        result = get_buffer_line((char*)file_buf, &buffer_index, file_size, (char*)line, LINE_BUFFER_SIZE);
    }
    
    if(file_buf) free(file_buf);
    return TTN_OK;

error:
    return TTN_ERROR;
}


//載入遊戲地圖設定
SLONG   load_game_map_info(void)
{
    enum {LINE_BUFFER_SIZE = 1024};
    USTR    *file_buf;
    SLONG   file_size, pass, result, buffer_index;
    USTR    line[LINE_BUFFER_SIZE];
    SLONG   index;
    SLONG   len;
    SLONG   data_index, i;
    MAP_INFO   *data = NULL;

    set_data_file(packed_data_file);
    file_size = load_file_to_buffer((USTR*)"data\\mapinfo.ini", &file_buf);
    if(file_size < 0)
        goto error;

    pass = 0;
    buffer_index = 0;
    result = get_buffer_line((char*)file_buf, &buffer_index, file_size, (char*)line, LINE_BUFFER_SIZE);
    while((result == TTN_OK) && (pass == 0))
    {
        len = ( SLONG )strlen( ( const char* )line );
        if( ( line[0] != 0x00 ) && ( line[0] != ';' ) )
        {
            index = 0;
            data_index = get_buffer_number(line, &index);
            if(data_index >= 0 && data_index < MAX_GAME_MAP_INFOS)
            {
                data = &game_map_info[data_index];
                strcpy((char *)data->map_cname, (const char *)get_buffer_string(line, &index));
                data->map_type = get_buffer_number(line, &index);
                data->city_stand = get_buffer_number(line, &index);
                data->start_longitude = get_buffer_number(line, &index);
                data->start_latitude = get_buffer_number(line, &index);
                data->total_monsters = get_buffer_number(line, &index);
                data->total_groups = get_buffer_number(line, &index);
                for(i=0; i<MAP_MONSTER_GROUP_TYPES; i++)
                {
                    data->group[i] = get_buffer_number(line, &index);
                }
            }
        }
        result = get_buffer_line((char*)file_buf, &buffer_index, file_size, (char*)line, LINE_BUFFER_SIZE);
    }
    
    if(file_buf) free(file_buf);
    return TTN_OK;

error:
    return TTN_ERROR;
}


//載入遊戲NPC設定
SLONG   load_game_npc_base(void)
{
    enum {LINE_BUFFER_SIZE = 1024};
    USTR    *file_buf;
    SLONG   file_size, pass, result, buffer_index;
    USTR    line[LINE_BUFFER_SIZE];
    SLONG   index;
    SLONG   len;
    SLONG   data_index;
    NPC_BASE    *data = NULL;

    set_data_file(packed_data_file);
    file_size = load_file_to_buffer((USTR*)"data\\npcinfo.ini", &file_buf);
    if(file_size < 0)
        goto error;

    pass = 0;
    buffer_index = 0;
    result = get_buffer_line((char*)file_buf, &buffer_index, file_size, (char*)line, LINE_BUFFER_SIZE);
    while((result == TTN_OK) && (pass == 0))
    {
        len = ( SLONG )strlen( ( const char* )line );
        if( ( line[0] != 0x00 ) && ( line[0] != ';' ) )
        {
            index = 0;
            data_index = get_buffer_number(line, &index);
            if(data_index >= 0 && data_index < MAX_GAME_NPC_BASES)
            {
                data = &game_npc_base[data_index];
                strcpy((char *)data->cname, (const char *)get_buffer_string(line, &index));
                data->kind = get_buffer_number(line, &index);
                data->state = get_buffer_number(line, &index);
                data->ai = get_buffer_number(line, &index);
                data->move_speed = get_buffer_number(line, &index);
                data->magic_no[0] = get_buffer_number(line, &index);
                data->magic_level[0] = get_buffer_number(line, &index);
                data->magic_no[1] = get_buffer_number(line, &index);
                data->magic_level[1] = get_buffer_number(line, &index);
                data->magic_no[2] = get_buffer_number(line, &index);
                data->magic_level[2] = get_buffer_number(line, &index);
                data->level = get_buffer_number(line, &index);
                data->hp = get_buffer_number(line, &index);
                data->att = get_buffer_number(line, &index);
                data->exp = get_buffer_number(line, &index);
            }
        }
        result = get_buffer_line((char*)file_buf, &buffer_index, file_size, (char*)line, LINE_BUFFER_SIZE);
    }
    
    if(file_buf) free(file_buf);
    return TTN_OK;

error:
    return TTN_ERROR;
}



void    clear_map_monster_set(void)
{
    SLONG   i;

    for(i=0; i<MAX_MAP_MONSTER_SETS; i++)
    {
        map_monster_set[i].flag = 0;
    }
}


//載入指定地圖的怪物設定
SLONG   load_map_monster_set(SLONG map_no)
{
    enum {LINE_BUFFER_SIZE = 1024};
    USTR    filename[MAX_PATH];
    USTR    *file_buf;
    SLONG   file_size, pass, result, buffer_index;
    USTR    line[LINE_BUFFER_SIZE];
    SLONG   index;
    SLONG   len;
    SLONG   data_index;
    MAP_MONSTER_SET *data = NULL;

    set_data_file(packed_data_file);
    sprintf((char *)filename, "data\\pos%04d.ini", map_no);
    file_size = load_file_to_buffer((USTR*)filename, &file_buf);
    if(file_size < 0)
        goto error;

    pass = 0;
    buffer_index = 0;
    result = get_buffer_line((char*)file_buf, &buffer_index, file_size, (char*)line, LINE_BUFFER_SIZE);
    while((result == TTN_OK) && (pass == 0))
    {
        len = ( SLONG )strlen( ( const char* )line );
        if( ( line[0] != 0x00 ) && ( line[0] != ';' ) )
        {
            index = 0;
            data_index = get_buffer_number(line, &index);
            if(data_index >= 0 && data_index < MAX_GAME_NPC_BASES)
            {
                data = &map_monster_set[data_index];
                data->flag = 1;
                data->type = get_buffer_number(line, &index);
                data->center_x = get_buffer_number(line, &index);
                data->center_y = get_buffer_number(line, &index);
                data->radius = get_buffer_number(line, &index);
                data->level = get_buffer_number(line, &index);
                data->group_no = get_buffer_number(line, &index);
            }
        }
        result = get_buffer_line((char*)file_buf, &buffer_index, file_size, (char*)line, LINE_BUFFER_SIZE);
    }
    
    if(file_buf) free(file_buf);
    return TTN_OK;

error:
    return TTN_ERROR;
}


/******************************************************************************************************************/
/* MANCHAR SET FUNCTIONS                                                                                          */
/******************************************************************************************************************/
void    init_manchar_set(void)
{
    SLONG   i;

    for(i=0; i<MAX_GAME_MANCHAR; i++)
    {
        manchar_set[i].flag = 0;
    }
}


SLONG   load_manchar_set(void)
{
    enum {LINE_BUFFER_SIZE = 1024};
    USTR    filename[MAX_PATH];
    USTR    *file_buf;
    SLONG   file_size, pass, result, buffer_index;
    USTR    line[LINE_BUFFER_SIZE];
    SLONG   index;
    SLONG   len;
    SLONG   data_index;
    MANCHAR_SET *data = NULL;

    set_data_file(packed_data_file);
    sprintf((char *)filename, "data\\manchar.ini");
    file_size = load_file_to_buffer((USTR*)filename, &file_buf);
    if(file_size < 0)
        goto error;

    pass = 0;
    buffer_index = 0;
    result = get_buffer_line((char*)file_buf, &buffer_index, file_size, (char*)line, LINE_BUFFER_SIZE);
    while((result == TTN_OK) && (pass == 0))
    {
        len = ( SLONG )strlen( ( const char* )line );
        if( ( line[0] != 0x00 ) && ( line[0] != ';' ) )
        {
            index = 0;
            data_index = get_buffer_number(line, &index);
            if(data_index >= 0 && data_index < MAX_GAME_NPC_BASES)
            {
                data = &manchar_set[data_index];
                data->flag = 1;

                data->file_index[0] = get_buffer_number(line, &index);     //NPC文件標誌
                data->file_index[1] = get_buffer_number(line, &index);     //NPC文件標誌
                data->file_index[2] = get_buffer_number(line, &index);     //NPC文件標誌
                data->move_speed = get_buffer_number(line, &index);     //移動速度
                data->career = CAREER_GENERAL + get_buffer_number(line, &index);         //職業
                data->sex = SEX_MALE + get_buffer_number(line, &index);            //性別
                data->eyes_index = get_buffer_number(line, &index);     //眼
                data->mouth_index = get_buffer_number(line, &index);    //口
                data->strength = get_buffer_number(line, &index);       //力量
                data->instinct = get_buffer_number(line, &index);       //直覺
                data->wit = get_buffer_number(line, &index);            //智力
                data->luck = get_buffer_number(line, &index);           //運氣
                data->hp = get_buffer_number(line, &index);             //生命力
                data->mp = get_buffer_number(line, &index);             //法力
                data->born_country = 'A' + get_buffer_number(line, &index);   //出生地
            }
        }
        result = get_buffer_line((char*)file_buf, &buffer_index, file_size, (char*)line, LINE_BUFFER_SIZE);
    }
    
    if(file_buf) free(file_buf);
    return TTN_OK;

error:
    return TTN_ERROR;
}


/******************************************************************************************************************/
/* NEW CHARACTER CONFIG FUNCTIONS                                                                                 */
/******************************************************************************************************************/
void    init_new_character_config(void)
{
    memset(&new_character_config, 0, sizeof(new_character_config));
}

void    set_new_character_account(USTR *account)
{
    strcpy((char *)new_character_config.account, (const char *)account);
}

USTR*   get_new_character_account(void)
{
    return  (USTR*)new_character_config.account;
}

//設置新建人物在帳號中的索引值(該帳號的第幾個角色)
void    set_new_character_index(SLONG index)
{
    new_character_config.character_index = index;
}

SLONG   get_new_character_index(void)
{
    return  new_character_config.character_index;
}

void    set_new_character_body_index(SLONG index)
{
    new_character_config.body_index = index;
}

SLONG   get_new_character_body_index(void)
{
    return  new_character_config.body_index;
}

void    set_new_character_career(SLONG career)
{
    new_character_config.career = career;
}


SLONG   get_new_character_career(void)
{
    return  new_character_config.career;
}

void    set_new_character_sex(SLONG sex)
{
    new_character_config.sex = sex;
}

SLONG   get_new_character_sex(void)
{
    return  new_character_config.sex;
}

void    set_new_character_color(SLONG color)
{
    new_character_config.color = color;
}

SLONG   get_new_character_color(void)
{
    return  new_character_config.color;
}

void    set_new_character_mainname(USTR *mainname)
{
    strcpy((char *)new_character_config.mainname, (const char *)mainname);
}

USTR*   get_new_character_mainname(void)
{
    return  (USTR*)new_character_config.mainname;
}

void    set_new_character_nickname(USTR *nickname)
{
    strcpy((char *)new_character_config.nickname, (const char *)nickname);
}

USTR*   get_new_character_nickname(void)
{
    return  (USTR*)new_character_config.nickname;
}

void    set_new_character_eyes_index(SLONG index)
{
    new_character_config.eyes_index = index;
}

SLONG   get_new_character_eyes_index(void)
{
    return  new_character_config.eyes_index;
}

void    set_new_character_mouth_index(SLONG index)
{
    new_character_config.mouth_index = index;
}

SLONG   get_new_character_mouth_index(void)
{
    return  new_character_config.mouth_index;
}

void    set_new_character_country(SLONG country)
{
    new_character_config.country = country;
}

SLONG   get_new_character_country(void)
{
    return  new_character_config.country;
}

void    set_new_character_strength(SLONG strength)
{
    new_character_config.strength = strength;
}

SLONG   get_new_character_strength(void)
{
    return  new_character_config.strength;
}

void    set_new_character_instinct(SLONG instinct)
{
    new_character_config.instinct = instinct;
}

SLONG   get_new_character_instinct(void)
{
    return  new_character_config.instinct;
}

void    set_new_character_wit(SLONG wit)
{
    new_character_config.wit = wit;
}

SLONG   get_new_character_wit(void)
{
    return  new_character_config.wit;
}

void    set_new_character_luck(SLONG luck)
{
    new_character_config.luck = luck;
}

SLONG   get_new_character_luck(void)
{
    return  new_character_config.luck;
}

void    set_new_character_hp(SLONG hp)
{
    new_character_config.hp = hp;
}

SLONG   get_new_character_hp(void)
{
    return  new_character_config.hp;
}

void    set_new_character_mp(SLONG mp)
{
    new_character_config.mp = mp;
}

SLONG   get_new_character_mp(void)
{
    return  new_character_config.mp;
}

ULONG	get_new_character_part_color(SLONG part)
{
	return	new_character_config.part_color[part];
}

void	set_new_character_part_color(SLONG part, ULONG argb)
{
	new_character_config.part_color[part] = argb;
}


/******************************************************************************************************************/
/* CHANGE MAP DATA FUNCTIONS                                                                                      */
/******************************************************************************************************************/
void    init_change_map_data(void)
{
    change_map_data.flag = 0;
}


void    store_change_map_data(USTR *zonename, USTR *mapname, USTR *addr, SLONG port, SLONG x, SLONG y, SLONG z, SLONG dir)
{
    CHANGE_MAP_DATA *data = &change_map_data;

    strcpy((char *)data->zone_name, (const char *)zonename);
    strcpy((char *)data->map_name, (const char *)mapname);
    strcpy((char *)data->addr, (const char *)addr);
    data->port = port;
    data->x = x;
    data->y = y;
    data->z = z;
    data->dir = dir;
    data->flag = 1;
}


SLONG   get_change_map_addr_port(USTR *addr, SLONG *port)
{
    CHANGE_MAP_DATA *data = &change_map_data;

    if(!data->flag)
        return  TTN_ERROR;

    if(addr)    strcpy((char *)addr, (const char *)data->addr);
    if(port)    *port = data->port;
    return  TTN_OK;
}


/************************************************************************************************************/
/* CHAR COLOR SET                                                                                           */
/************************************************************************************************************/
void	init_char_color_set(void)
{
	memset(char_color_set, 0, sizeof(char_color_set));
}


SLONG	load_char_color_set(void)
{
	SLONG	i, result;

	result = TTN_OK;
	for(i=0; i<MAX_GAME_MANCHAR; i++)
	{
		if(TTN_OK != load_one_char_color_set(i))
		{
			result = TTN_ERROR;
			break;
		}
	}
	return	result;
}


SLONG	load_one_char_color_set(SLONG char_index)
{
    enum {LINE_BUFFER_SIZE = 1024};
    USTR    *file_buf;
    SLONG   file_size, pass, result, buffer_index;
    USTR    line[LINE_BUFFER_SIZE];
    SLONG   index;
    SLONG   len;
    SLONG   data_index;
	USTR	filename[_MAX_FNAME];
	CHAR_COLOR_SET	*data;
	SLONG	number;

    set_data_file(packed_data_file);
	sprintf((char *)filename, "data\\chancl%02d.ini", char_index);
    file_size = load_file_to_buffer((USTR*)filename, &file_buf);
    if(file_size < 0)
        goto error;

	data = &char_color_set[char_index];

    pass = 0;
    buffer_index = 0;
	data_index = 0;
    result = get_buffer_line((char*)file_buf, &buffer_index, file_size, (char*)line, LINE_BUFFER_SIZE);
    while((result == TTN_OK) && (pass == 0))
    {
        len = ( SLONG )strlen( ( const char* )line );
        if( ( line[0] != 0x00 ) && ( line[0] != ';' ) )
        {
            index = 0;

			//skip name string
			get_buffer_string(line, &index);
			//
            //data_index = get_buffer_number(line, &index);
            //if(data_index >= 0 && data_index < 6)	//total 6 parts
            {
				number = get_buffer_number(line, &index);
				if(number >= 0)
				{
					// the first data >= 0 means that this part is valid.
					data->part_flag[data_index] = 1;
					//
					// the 2nd suit.
					data->suit_rgb[1][data_index][0] = (UCHR)number;
					data->suit_rgb[1][data_index][1] = (UCHR)get_buffer_number(line, &index);
					data->suit_rgb[1][data_index][2] = (UCHR)get_buffer_number(line, &index);
					data->suit_rgb[1][data_index][3] = (UCHR)RGB_EFFECT_AND;

					// the 3rd suit.
					data->suit_rgb[2][data_index][0] = (UCHR)get_buffer_number(line, &index);
					data->suit_rgb[2][data_index][1] = (UCHR)get_buffer_number(line, &index);
					data->suit_rgb[2][data_index][2] = (UCHR)get_buffer_number(line, &index);
					data->suit_rgb[2][data_index][3] = (UCHR)RGB_EFFECT_AND;

					// init rgb colors.
					data->init_rgb[data_index][0] = (UCHR)get_buffer_number(line, &index);
					data->init_rgb[data_index][1] = (UCHR)get_buffer_number(line, &index);
					data->init_rgb[data_index][2] = (UCHR)get_buffer_number(line, &index);

					// and rgb colors.
					// the 2nd rgb colors.
					data->and_rgb[1][data_index][0] = (UCHR)get_buffer_number(line, &index);
					data->and_rgb[1][data_index][1] = (UCHR)get_buffer_number(line, &index);
					data->and_rgb[1][data_index][2] = (UCHR)get_buffer_number(line, &index);

					// the 3rd rgb colors.
					data->and_rgb[2][data_index][0] = (UCHR)get_buffer_number(line, &index);
					data->and_rgb[2][data_index][1] = (UCHR)get_buffer_number(line, &index);
					data->and_rgb[2][data_index][2] = (UCHR)get_buffer_number(line, &index);

					// the 1st suit is default all rgb for init.
					data->suit_rgb[0][data_index][0] = data->init_rgb[data_index][0];
					data->suit_rgb[0][data_index][1] = data->init_rgb[data_index][1];
					data->suit_rgb[0][data_index][2] = data->init_rgb[data_index][2];
					data->suit_rgb[0][data_index][3] = (UCHR)RGB_EFFECT_NONE;

					// the 1st and rgb colors is default to init.
					data->and_rgb[0][data_index][0] = data->init_rgb[data_index][0];
					data->and_rgb[0][data_index][1] = data->init_rgb[data_index][1];
					data->and_rgb[0][data_index][2] = data->init_rgb[data_index][2];
				}
				else	//the first data < 0 means that this part is invalid.
				{
					data->part_flag[data_index] = 0;
				}
            }

			data_index ++;
        }
        result = get_buffer_line((char*)file_buf, &buffer_index, file_size, (char*)line, LINE_BUFFER_SIZE);
    }
    
    if(file_buf) free(file_buf);
    return TTN_OK;

error:
    return TTN_ERROR;
}


void	debug_log_char_color_set(void)
{
#ifdef	_DEBUG
	SLONG	i;

	for(i=0; i<MAX_GAME_MANCHAR; i++)
	{
		debug_log_one_char_color_set(i);
	}
#endif//_DEBUG
}


void	debug_log_one_char_color_set(SLONG index)
{
#ifdef	_DEBUG
	SLONG	i;

	log_error(1, ";log char color set");
	log_error(1, ";-----------------------------------------------------------------------------------");
	for(i=0; i<7; i++)
	{
		sprintf((char *)print_rec, "PART%02d  "
			"%-8d%-8d%-8d"
			"%-8d%-8d%-8d"
			"%-8d%-8d%-8d"
			"%-8d%-8d%-8d"
			"%-8d%-8d%-8d"
			,
			i, 
			char_color_set[index].part_flag[i] ? char_color_set[index].suit_rgb[1][i][0]: -1,
			char_color_set[index].part_flag[i] ? char_color_set[index].suit_rgb[1][i][1]: -1,
			char_color_set[index].part_flag[i] ? char_color_set[index].suit_rgb[1][i][2]: -1,

			char_color_set[index].part_flag[i] ? char_color_set[index].suit_rgb[2][i][0]: -1,
			char_color_set[index].part_flag[i] ? char_color_set[index].suit_rgb[2][i][1]: -1,
			char_color_set[index].part_flag[i] ? char_color_set[index].suit_rgb[2][i][2]: -1,

			char_color_set[index].part_flag[i] ? char_color_set[index].init_rgb[i][0] : -1,
			char_color_set[index].part_flag[i] ? char_color_set[index].init_rgb[i][1] : -1,
			char_color_set[index].part_flag[i] ? char_color_set[index].init_rgb[i][2] : -1,

			char_color_set[index].part_flag[i] ? char_color_set[index].and_rgb[1][i][0] : -1,
			char_color_set[index].part_flag[i] ? char_color_set[index].and_rgb[1][i][1] : -1,
			char_color_set[index].part_flag[i] ? char_color_set[index].and_rgb[1][i][2] : -1,

			char_color_set[index].part_flag[i] ? char_color_set[index].and_rgb[2][i][0] : -1,
			char_color_set[index].part_flag[i] ? char_color_set[index].and_rgb[2][i][1] : -1,
			char_color_set[index].part_flag[i] ? char_color_set[index].and_rgb[2][i][2] : -1
			);
		log_error(1, print_rec);
	}

#endif//_DEBUG
}

