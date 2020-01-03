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
//天氣狀態
//-------------
#define WEATHER_TYPE_WIND           0   //風
#define WEATHER_TYPE_FINE           1   //晴
#define WEATHER_TYPE_RAIN           2   //雨
#define WEATHER_TYPE_THUNDER        3   //雷
#define WEATHER_TYPE_FOG            4   //霧


#define MAX_GAME_MONSTER_GROUPS     256     //遊戲中怪物組群類別數量
#define NORMAL_MONSTERS_PER_GROUP   10      //怪物組群中普通怪物數量
//
#define MAX_GAME_MAP_INFOS          512     //遊戲的地圖資訊數量
#define MAP_MONSTER_GROUP_TYPES     5       //地圖上怪物組群類別數量
#define MAX_MAP_MONSTER_SETS        128     //每張地圖上怪物(組群)數量
//
#define MAX_GAME_NPC_BASES          256     //遊戲中NPC基本數值的數量


#define MAX_GAME_MANCHAR            14      //遊戲中角色數目

//----------------------------
//地圖的類別
//----------------------------
#define MAP_TYPE_NEWER_CITY         0   //新手城市(不能戰鬥，進入時自動切換為和平模式，不能ＰＫ)
#define MAP_TYPE_THIEF_CITY         1   //海盜城市(可以戰鬥，進入時不切換，仍然保留為原來的模式，可以ＰＫ)
#define MAP_TYPE_PLAYER_CITY        2   //玩家城市(可以戰鬥，進入時根據陣營切換，可以ＰＫ)
#define MAP_TYPE_NORMAL_CITY        3   //普通城市(可以戰鬥，進入時自動切換為和平模式，可以ＰＫ)
#define MAP_TYPE_NEWER_FIELD        4   //新手野外(可以戰鬥，進入時自動切換為戰鬥模式，不能ＰＫ)
#define MAP_TYPE_NORMAL_FIELD       5   //普通野外(怪物可重生，在出現點隨機出現一組)
#define MAP_TYPE_EXPLORE_FIELD      6   //探險野外(怪物不可重生，在出現點出現指定組)
#define MAP_TYPE_SEA_FIELD          7   //海洋野外(表現為船隻)


//-----------------------------
//城市陣營
//-----------------------------
#define CITY_STAND_ORDERED          0   //秩序
#define CITY_STAND_NEUTRAL          1   //中立
#define CITY_STAND_CHAOS            2   //混亂



// S T R U C T U R E S /////////////////////////////////////////////////////////////////////////////////////////////
typedef struct tagMONSTER_GROUP 
{
    SLONG   header_monster;     //頭目怪
    SLONG   normal_monster[NORMAL_MONSTERS_PER_GROUP];  //普通怪物
} MONSTER_GROUP, *LPMONSTER_GROUP;


typedef struct  tagMAP_INFO
{
    USTR    map_cname[24];      //地圖名稱
    SLONG   map_type;           //地圖類別(MAP_TYPE_$$$)
    SLONG   city_stand;         //城市陣營(CITY_STAND_$$$)
    SLONG   start_longitude;    //經度
    SLONG   start_latitude;     //緯度
    SLONG   total_monsters;     //怪物數量
    SLONG   total_groups;       //怪物組類數量
    SLONG   group[MAP_MONSTER_GROUP_TYPES];  //怪物組
    //
} MAP_INFO, *LPMAP_INFO;


typedef struct tagNPC_BASE
{
    USTR    cname[24];          //人物名稱
    SLONG   kind;               //人物類別
    SLONG   state;              //人物屬性
    SLONG   ai;                 //人物 AI
    SLONG   move_speed;         //移動速度
    SLONG   magic_no[3];        //技能編號
    SLONG   magic_level[3];     //技能等級
    SLONG   level;              //等級
    SLONG   hp;                 //生命力
    SLONG   att;                //攻擊力
    SLONG   exp;                //經驗值
} NPC_BASE, *LPNPC_BASE;


typedef struct tagMAP_MONSTER_SET
{
    SLONG   flag;               //使用標誌
    SLONG   type;               //怪物出現類型
    SLONG   center_x;           //中心點 x 座標
    SLONG   center_y;           //中心點 y 座標
    SLONG   radius;             //出現範圍半徑
    SLONG   level;              //怪物等級
    union
    {
        SLONG   monster_no;     //怪物編號
        SLONG   group_no;       //群組編號
    };
} MAP_MONSTER_SET, *LPMAP_MONSTER_SET;


//創建角色時對應14個人物(7種職業*2種性別)的默認數值
typedef struct  tagMANCHAR_SET
{
    SLONG   flag;           //使用標誌
    SLONG   file_index[3];  //NPC文件標誌
    SLONG   move_speed;     //移動速度
    SLONG   career;         //職業, 'A'...
    SLONG   sex;            //性別, 'A'...
    SLONG   eyes_index;     //眼
    SLONG   mouth_index;    //口
    SLONG   strength;       //力量
    SLONG   instinct;       //直覺
    SLONG   wit;            //智力
    SLONG   luck;           //運氣
    SLONG   hp;             //生命力
    SLONG   mp;             //法力
    SLONG   born_country;   //出生地
} MANCHAR_SET, *LPMANCHAR_SET;
//

//
typedef struct  tagNEW_CHARACTER_CONFIG  // 註冊角色資料
{
    USTR    account[20];    //帳號
    SLONG   character_index;//本帳號的第幾個角色(0~3)
    //
    SLONG   body_index;     //身體形態(0~13)
    //
    SLONG   career;         //職業, 'A'...
    SLONG   sex;            //性別, 'A'...
    SLONG   color;          //顏色
    //
    USTR    mainname[20];   //名稱
    USTR    nickname[20];   //暱稱
    SLONG   eyes_index;     //眼
    SLONG   mouth_index;    //口
    //
    SLONG   country;        //國家
    //
    SLONG   strength;       //力量
    SLONG   instinct;       //直覺
    SLONG   wit;            //智力
    SLONG   luck;           //運氣
    SLONG   hp;             //生命力
    SLONG   mp;             //法力
	//
	ULONG	part_color[7];	//顏色
} NEW_CHARACTER_CONFIG, *LPNEW_CHARACTER_CONFIG;


typedef struct tagCHANGE_MAP_DATA 
{
    SLONG   flag;           //存放標誌
    USTR    zone_name[64];  //ZONE 名稱
    USTR    map_name[64];   //地圖名稱
    USTR    addr[32];       //IP 地址
    SLONG   port;           //端口號
    SLONG   x;              //進入點座標 X
    SLONG   y;              //進入點座標 Y
    SLONG   z;              //進入點座標 Z
    SLONG   dir;            //進入時人物方向
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
