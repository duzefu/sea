/*
**	posdata.h
**	psalm of sea data.
**
**	Jack, 2002/07/15.
*/
#ifndef _POSDATA_H_
#define _POSDATA_H_


// D E F I N E S ///////////////////////////////////////////////////////////////////////////////////////////////////
//-------------
//�Ѯ𪬺A
//-------------
#define WEATHER_TYPE_WIND           0   //��
#define WEATHER_TYPE_FINE           1   //��
#define WEATHER_TYPE_RAIN           2   //�B
#define WEATHER_TYPE_THUNDER        3   //�p
#define WEATHER_TYPE_FOG            4   //��


#define MAX_GAME_MONSTER_GROUPS     256     //�C�����Ǫ��ոs���O�ƶq
#define NORMAL_MONSTERS_PER_GROUP   10      //�Ǫ��ոs�����q�Ǫ��ƶq
//
#define MAX_GAME_MAP_INFOS          512     //�C�����a�ϸ�T�ƶq
#define MAP_MONSTER_GROUP_TYPES     5       //�a�ϤW�Ǫ��ոs���O�ƶq
#define MAX_MAP_MONSTER_SETS        128     //�C�i�a�ϤW�Ǫ�(�ոs)�ƶq
//
#define MAX_GAME_NPC_BASES          256     //�C����NPC�򥻼ƭȪ��ƶq


#define MAX_GAME_MANCHAR            14      //�C��������ƥ�

//----------------------------
//�a�Ϫ����O
//----------------------------
#define MAP_TYPE_NEWER_CITY         0   //�s�⫰��(����԰��A�i�J�ɦ۰ʤ������M���Ҧ��A����ޢ�)
#define MAP_TYPE_THIEF_CITY         1   //���s����(�i�H�԰��A�i�J�ɤ������A���M�O�d����Ӫ��Ҧ��A�i�H�ޢ�)
#define MAP_TYPE_PLAYER_CITY        2   //���a����(�i�H�԰��A�i�J�ɮھڰ}������A�i�H�ޢ�)
#define MAP_TYPE_NORMAL_CITY        3   //���q����(�i�H�԰��A�i�J�ɦ۰ʤ������M���Ҧ��A�i�H�ޢ�)
#define MAP_TYPE_NEWER_FIELD        4   //�s�⳥�~(�i�H�԰��A�i�J�ɦ۰ʤ������԰��Ҧ��A����ޢ�)
#define MAP_TYPE_NORMAL_FIELD       5   //���q���~(�Ǫ��i���͡A�b�X�{�I�H���X�{�@��)
#define MAP_TYPE_EXPLORE_FIELD      6   //���I���~(�Ǫ����i���͡A�b�X�{�I�X�{���w��)
#define MAP_TYPE_SEA_FIELD          7   //���v���~(��{���)


//-----------------------------
//�����}��
//-----------------------------
#define CITY_STAND_ORDERED          0   //����
#define CITY_STAND_NEUTRAL          1   //����
#define CITY_STAND_CHAOS            2   //�V��



// S T R U C T U R E S /////////////////////////////////////////////////////////////////////////////////////////////
typedef struct tagMONSTER_GROUP 
{
    SLONG   header_monster;     //�Y�ة�
    SLONG   normal_monster[NORMAL_MONSTERS_PER_GROUP];  //���q�Ǫ�
} MONSTER_GROUP, *LPMONSTER_GROUP;


typedef struct  tagMAP_INFO
{
    USTR    map_cname[24];      //�a�ϦW��
    SLONG   map_type;           //�a�����O(MAP_TYPE_$$$)
    SLONG   city_stand;         //�����}��(CITY_STAND_$$$)
    SLONG   start_longitude;    //�g��
    SLONG   start_latitude;     //�n��
    SLONG   total_monsters;     //�Ǫ��ƶq
    SLONG   total_groups;       //�Ǫ������ƶq
    SLONG   group[MAP_MONSTER_GROUP_TYPES];  //�Ǫ���
    //
} MAP_INFO, *LPMAP_INFO;


typedef struct tagNPC_BASE
{
    USTR    cname[24];          //�H���W��
    SLONG   kind;               //�H�����O
    SLONG   state;              //�H���ݩ�
    SLONG   ai;                 //�H�� AI
    SLONG   move_speed;         //���ʳt��
    SLONG   magic_no[3];        //�ޯ�s��
    SLONG   magic_level[3];     //�ޯ൥��
    SLONG   level;              //����
    SLONG   hp;                 //�ͩR�O
    SLONG   att;                //�����O
    SLONG   exp;                //�g���
} NPC_BASE, *LPNPC_BASE;


typedef struct tagMAP_MONSTER_SET
{
    SLONG   flag;               //�ϥμлx
    SLONG   type;               //�Ǫ��X�{����
    SLONG   center_x;           //�����I x �y��
    SLONG   center_y;           //�����I y �y��
    SLONG   radius;             //�X�{�d��b�|
    SLONG   level;              //�Ǫ�����
    union
    {
        SLONG   monster_no;     //�Ǫ��s��
        SLONG   group_no;       //�s�սs��
    };
} MAP_MONSTER_SET, *LPMAP_MONSTER_SET;


//�Ыب���ɹ���14�ӤH��(7��¾�~*2�ةʧO)���q�{�ƭ�
typedef struct  tagMANCHAR_SET
{
    SLONG   flag;           //�ϥμлx
    SLONG   file_index[3];  //NPC���лx
    SLONG   move_speed;     //���ʳt��
    SLONG   career;         //¾�~, 'A'...
    SLONG   sex;            //�ʧO, 'A'...
    SLONG   eyes_index;     //��
    SLONG   mouth_index;    //�f
    SLONG   strength;       //�O�q
    SLONG   instinct;       //��ı
    SLONG   wit;            //���O
    SLONG   luck;           //�B��
    SLONG   hp;             //�ͩR�O
    SLONG   mp;             //�k�O
    SLONG   born_country;   //�X�ͦa
} MANCHAR_SET, *LPMANCHAR_SET;
//

//
typedef struct  tagNEW_CHARACTER_CONFIG  // ���U������
{
    USTR    account[20];    //�b��
    SLONG   character_index;//���b�����ĴX�Ө���(0~3)
    //
    SLONG   body_index;     //����κA(0~13)
    //
    SLONG   career;         //¾�~, 'A'...
    SLONG   sex;            //�ʧO, 'A'...
    SLONG   color;          //�C��
    //
    USTR    mainname[20];   //�W��
    USTR    nickname[20];   //�ʺ�
    SLONG   eyes_index;     //��
    SLONG   mouth_index;    //�f
    //
    SLONG   country;        //��a
    //
    SLONG   strength;       //�O�q
    SLONG   instinct;       //��ı
    SLONG   wit;            //���O
    SLONG   luck;           //�B��
    SLONG   hp;             //�ͩR�O
    SLONG   mp;             //�k�O
	//
	ULONG	part_color[7];	//�C��
} NEW_CHARACTER_CONFIG, *LPNEW_CHARACTER_CONFIG;


typedef struct tagCHANGE_MAP_DATA 
{
    SLONG   flag;           //�s��лx
    USTR    zone_name[64];  //ZONE �W��
    USTR    map_name[64];   //�a�ϦW��
    USTR    addr[32];       //IP �a�}
    SLONG   port;           //�ݤf��
    SLONG   x;              //�i�J�I�y�� X
    SLONG   y;              //�i�J�I�y�� Y
    SLONG   z;              //�i�J�I�y�� Z
    SLONG   dir;            //�i�J�ɤH����V
} CHANGE_MAP_DATA, *LPCHANGE_MAP_DATA;


typedef	struct tagCHAR_COLOR_SET 
{
	SLONG	part_flag[7];		//part valid flag, 1 for valid.
	UCHR	suit_rgb[3][7][4];	//3 suits, 7 parts, 3 rgb colors + 1 a.
	UCHR	init_rgb[7][3];		//initilized rgb color, 7 parts, 3 rgb clors.
	UCHR	and_rgb[3][7][3];	//and rgb color, 3 and types, 7 parts, 3 rgb colors
} CHAR_COLOR_SET, *LPCHAR_COLOR_SET;


// G L O B A L S ///////////////////////////////////////////////////////////////////////////////////////////////////
extern  MONSTER_GROUP       game_monster_group[MAX_GAME_MONSTER_GROUPS];
extern  MAP_INFO            game_map_info[MAX_GAME_MAP_INFOS];
extern  NPC_BASE            game_npc_base[MAX_GAME_NPC_BASES];
extern  MAP_MONSTER_SET     map_monster_set[MAX_MAP_MONSTER_SETS];
extern  MANCHAR_SET         manchar_set[MAX_GAME_MANCHAR];
extern  NEW_CHARACTER_CONFIG    new_character_config;
extern  CHANGE_MAP_DATA     change_map_data;
extern	CHAR_COLOR_SET		char_color_set[MAX_GAME_MANCHAR];
//


// F U N C T I O N S ///////////////////////////////////////////////////////////////////////////////////////////////
int     init_game_data(void);
void    active_game_data(int active);
void    free_game_data(void);
//
char*   get_career_name(SLONG career);
char*   get_country_name(SLONG country);
char*   get_sex_name(SLONG sex);
char*   get_weather_description(SLONG weather_type);
SLONG   get_character_main_face(SLONG career, SLONG sex);
SLONG   get_career_default_lhand_map_magic_no(SLONG career);
SLONG   get_career_default_lhand_fight_magic_no(SLONG career);
//
SLONG   load_game_monster_group(void);
SLONG   load_game_map_info(void);
SLONG   load_game_npc_base(void);
void    clear_map_monster_set(void);
SLONG   load_map_monster_set(SLONG map_no);
//
void    init_manchar_set(void);
SLONG   load_manchar_set(void);
//
void    init_new_character_config(void);
void    set_new_character_account(USTR *account);
USTR*   get_new_character_account(void);
void    set_new_character_index(SLONG index);
SLONG   get_new_character_index(void);
void    set_new_character_body_index(SLONG index);
SLONG   get_new_character_body_index(void);
void    set_new_character_career(SLONG career);
SLONG   get_new_character_career(void);
void    set_new_character_sex(SLONG sex);
SLONG   get_new_character_sex(void);
void    set_new_character_color(SLONG color);
SLONG   get_new_character_color(void);
void    set_new_character_mainname(USTR *mainname);
USTR*   get_new_character_mainname(void);
void    set_new_character_nickname(USTR *nickname);
USTR*   get_new_character_nickname(void);
void    set_new_character_eyes_index(SLONG index);
SLONG   get_new_character_eyes_index(void);
void    set_new_character_mouth_index(SLONG index);
SLONG   get_new_character_mouth_index(void);
void    set_new_character_country(SLONG country);
SLONG   get_new_character_country(void);
void    set_new_character_strength(SLONG strength);
SLONG   get_new_character_strength(void);
void    set_new_character_instinct(SLONG instinct);
SLONG   get_new_character_instinct(void);
void    set_new_character_wit(SLONG wit);
SLONG   get_new_character_wit(void);
void    set_new_character_luck(SLONG luck);
SLONG   get_new_character_luck(void);
void    set_new_character_hp(SLONG hp);
SLONG   get_new_character_hp(void);
void    set_new_character_mp(SLONG mp);
SLONG   get_new_character_mp(void);
ULONG	get_new_character_part_color(SLONG part);
void	set_new_character_part_color(SLONG part, ULONG argb);
//
//change map data functions -------------------------------------------------------
void    init_change_map_data(void);
void    store_change_map_data(USTR *zone_name, USTR *mapname, USTR *addr, SLONG port, SLONG x, SLONG y, SLONG z, SLONG dir);
SLONG   get_change_map_addr_port(USTR *addr, SLONG *port);
//
//
//char color set functions --------------------------------------------------------
void	init_char_color_set(void);
SLONG	load_char_color_set(void);
SLONG	load_one_char_color_set(SLONG index);
void	debug_log_char_color_set(void);
void	debug_log_one_char_color_set(SLONG index);



#endif//_POSDATA_H_
