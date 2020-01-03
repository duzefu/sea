/*
**  parse.cpp
**  cmd string parse functions.
**
**  geaan, 2001.7.16.
*/
#include "MainFun.h"
#include "NetGE_MainFunc.h"
#include "ClientMain.h"
#include "Parse.h"
#include "Weather.h"
#include "Npc.h"
#include "MainGame.h"
#include "SecretSkill.h"
#include "ErrorMsg.h"
#include "UIShop.h"
#include "UIStore.h"
#include "Client_SendMsg.h"
#include "MagicClient.h"
//


//
// DEFINES ///////////////////////////////////////////////////////////////////////////////////////////////
//
#define PARSE_SEGMENT_COMPARTMENT_STR   " ,"    //分隔符列表
#define PARSE_SEGMENT_COMPARTMENT_NUM   2       //分隔符數目

typedef enum    PARSE_ENUMS
{   PARSE_LINE_LEN  =   1024,
PARSE_TEMP_LEN      =   1024,
PARSE_LEAD_STR_LEN  =   80,
} PARSE_ENUMS ;



typedef void    (*PFNPARSE) (void);

typedef struct  tagPARSE_SET
{
    SLONG       flag;
    USTR        lead_str[PARSE_LEAD_STR_LEN];
    PFNPARSE    exe_func;
} PARSE_SET, *LPPARSE_SET;



typedef	struct tagBREAK_MAGIC_NAME_FUNC 
{
	CHAR	name[64];
	SLONG	(*func)(SLONG magic_no, SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG dest_no);
} BREAK_MAGIC_NAME_FUNC, *LPBREAK_MAGIC_NAME_FUNC;


//
// FUNCTIONS PROTOTYPES //////////////////////////////////////////////////////////////////////////////////////
//
//static functions --------------------------------------------------
static  void    reset_parse_data(USTR *input);
static  void    get_parse_segment(void);
static  SLONG   get_parse_number(SLONG *number);
static  SLONG   get_parse_string(USTR *string);
static  SLONG   is_parse_command(USTR *cmd_string);
//
//
//static  void    chat_command_npc_cheer(void);
static  void    chat_command_npc_angry(void);
static  void    chat_command_npc_beckon(void);
//static  void    chat_command_npc_court(void);
static  void    chat_command_npc_faint(void);
static  void    chat_command_npc_say_no(void);
static  void    chat_command_npc_bow(void);
static  void    chat_command_npc_win(void);
static  void    chat_command_npc_swash(void);
static  void    chat_command_npc_xxpower(void);
static  void    chat_command_npc_spower(void);
static  void    chat_command_npc_xxbeated(void);
static  void    chat_command_get_upgrade_points(void);
static  void    chat_command_debug_show_map_mask(void);
static  void    chat_command_debug_show_map_proc(void);
static  void    chat_command_debug_show_game_info(void);
static  void    chat_command_foot_state(void);
static  void    chat_command_zero_mp(void);
static  void    chat_command_player_file(void);
static  void	chat_weather_rain_on(void);
static  void	chat_weather_rain_off(void);
static  void	chat_weather_snow_on(void);
static  void	chat_weather_snow_off(void);
static  void	chat_weather_thunder_on(void);
static  void	chat_weather_thunder_off(void);
static  void	chat_weather_cloud_on(void);
static  void	chat_weather_cloud_off(void);
static  void	chat_weather_earthquake_on(void);
static  void	chat_weather_earthquake_off(void);
static  void    chat_weather_set_wind(void);
static  void    chat_command_enable_secret_skill(void);
static  void    chat_command_disable_secret_skill(void);
static  void    chat_command_enable_rand_move(void);
static  void    chat_command_disable_rand_move(void);
static  void    chat_command_enable_rand_weather(void);
static  void    chat_command_disable_rand_weather(void);
static  void    chat_command_enable_follow_npc(void);
static  void    chat_command_disable_follow_npc(void);
static  void    chat_command_keep_map_range(void);
static  void    chat_command_enable_create_account(void);
static	void	chat_command_show_debug_minimap(void);
static	void	chat_command_show_object_poly(void);
static	void	chat_command_show_trade_shop(void);
static	void	chat_command_show_store_shop(void);
static	void	chat_command_full_hp_mp(void);
static	void	chat_command_get_property_point(void);
static	void	chat_command_jump_to(void);
static	void	chat_command_request_item(void);
static	void	chat_command_request_money(void);
static	void	chat_command_request_exp(void);
static	void	chat_command_request_move_fast(void);
static	void	chat_command_request_change_zone(void);
static	void	chat_command_request_dead(void);
static	void	chat_command_break_magic(void);
static	void	chat_command_show_game_range(void);
//
static  void    chat_command_reload_magic_ini(void);
//

// Zhang Zhaohui 2003.5.17
static  VOID    chat_command_request_get_treasure_map( void );
//
//
// GLOBALS ////////////////////////////////////////////////////////////////////////////////////////////////////
//
USTR    parse_line[PARSE_LINE_LEN];
USTR    parse_temp[PARSE_TEMP_LEN];
SLONG   parse_index;
SLONG	god_mode_enable = 0;
PARSE_RESULT    parse_result;
//
PARSE_SET   chat_parse_set[] = 
{

    { 1,    "angry"                                 ,chat_command_npc_angry                 },
    { 1,    "qifen"                                 ,chat_command_npc_angry                 },

    { 1,    "beckon"                                ,chat_command_npc_beckon                },
    { 1,    "hello"                                 ,chat_command_npc_beckon                },
    { 1,    "zhaoshou"                              ,chat_command_npc_beckon                },
    { 1,    "hi"                                    ,chat_command_npc_beckon                },
    { 1,    "goodbye"                               ,chat_command_npc_beckon                },
    { 1,    "bye"                                   ,chat_command_npc_beckon                },
    { 1,    "886"                                   ,chat_command_npc_beckon                },
    { 1,    "88"                                    ,chat_command_npc_beckon                },
    { 1,    "zaijian"                               ,chat_command_npc_beckon                },
    { 1,    "seeyou"                                ,chat_command_npc_beckon                },
    { 1,    "cya"                                   ,chat_command_npc_beckon                },
    { 1,    "cu"                                    ,chat_command_npc_beckon                },

           
    { 1,    "faint"                                 ,chat_command_npc_faint                 },
    { 1,    "yundao"                                ,chat_command_npc_faint                 },
    { 1,    "dao"                                   ,chat_command_npc_faint                 },
           
    { 1,    "no"                                    ,chat_command_npc_say_no                },
    { 1,    "bu"                                    ,chat_command_npc_say_no                },

    { 1,    "bow"                                   ,chat_command_npc_bow                   },
    { 1,    "jugong"                                ,chat_command_npc_bow                   },
    { 1,    "thanks"                                ,chat_command_npc_bow                   },
    { 1,    "thanx"                                 ,chat_command_npc_bow                   },
    { 1,    "thankyou"                              ,chat_command_npc_bow                   },
    { 1,    "3q"                                    ,chat_command_npc_bow                   },

    { 1,    "win"                                   ,chat_command_npc_win                   },
    { 1,    "victory"                               ,chat_command_npc_win                   },
    { 1,    "shengli"                               ,chat_command_npc_win                   },

#ifdef  BIG5_VERSION
    { 1,    "氣憤"                                  ,chat_command_npc_angry                 },
    { 1,    "你好"                                  ,chat_command_npc_beckon                },
    { 1,    "招手"                                  ,chat_command_npc_beckon                },
    { 1,    "再見"                                  ,chat_command_npc_beckon                },
    { 1,    "暈倒"                                  ,chat_command_npc_faint                 },
    { 1,    "不"                                    ,chat_command_npc_say_no                },
    { 1,    "鞠躬"                                  ,chat_command_npc_bow                   },
    { 1,    "勝利"                                  ,chat_command_npc_win                   },
    { 1,    "嚇唬"                                  ,chat_command_npc_swash                 },
    { 1,    "蓄力"                                  ,chat_command_npc_xxpower               },
    { 1,    "受傷"                                  ,chat_command_npc_xxbeated              },
#endif//BIG5_VERSION

#ifdef  GB_VERSION
    { 1,    "ァ猷"                                  ,chat_command_npc_angry                 },
    { 1,    "斕疑"                                  ,chat_command_npc_beckon                },
    { 1,    "桸忒"                                  ,chat_command_npc_beckon                },
    { 1,    "婬獗"                                  ,chat_command_npc_beckon                },
    { 1,    "婠給"                                  ,chat_command_npc_faint                 },
    { 1,    "祥"                                    ,chat_command_npc_say_no                },
    { 1,    "懍鼓"                                  ,chat_command_npc_bow                   },
    { 1,    "吨瞳"                                  ,chat_command_npc_win                   },
    { 1,    "狣誨"                                  ,chat_command_npc_swash                 },
    { 1,    "匎薯"                                  ,chat_command_npc_xxpower               },
    { 1,    "忳夼"                                  ,chat_command_npc_xxbeated              },
#endif//GB_VERSION

    { 1,    "swash"                                 ,chat_command_npc_swash                 },
    { 1,    "xiahu"                                 ,chat_command_npc_swash                 },
    { 1,    "gongji"                                ,chat_command_npc_swash                 },
    { 1,    "attack"                                ,chat_command_npc_swash                 },

    { 1,    "xxpower"                               ,chat_command_npc_xxpower               },
    { 1,    "xuli"                                  ,chat_command_npc_xxpower               },

    { 1,    "xxbeated"                              ,chat_command_npc_xxbeated              },
    { 1,    "hurt"                                  ,chat_command_npc_xxbeated              },
    { 1,    "shoushang"                             ,chat_command_npc_xxbeated              },

    { 1,    "spower"                                ,chat_command_npc_spower                },

    { 1,    "getupgradepoints"                      ,chat_command_get_upgrade_points        },
    { 1,    "##mapmask##"                           ,chat_command_debug_show_map_mask       },
    { 1,    "##mapproc##"                           ,chat_command_debug_show_map_proc       },
    { 1,    "##gameinfo##"                          ,chat_command_debug_show_game_info      },

    { 1,    "##footstate##"                         ,chat_command_foot_state                },
    { 1,    "##zeromp##"                            ,chat_command_zero_mp                   },
    { 1,    "##playerfile##"                        ,chat_command_player_file               },

    { 1,    "##rain_on##"                           ,chat_weather_rain_on                   },
    { 1,    "##rain_off##"                          ,chat_weather_rain_off                  },
    { 1,    "##snow_on##"                           ,chat_weather_snow_on                   },
    { 1,    "##snow_off##"                          ,chat_weather_snow_off                  },
    { 1,    "##thunder_on##"                        ,chat_weather_thunder_on                },
    { 1,    "##thunder_off##"                       ,chat_weather_thunder_off               },
    { 1,    "##cloud_on##"                          ,chat_weather_cloud_on                  },
    { 1,    "##cloud_off##"                         ,chat_weather_cloud_off                 },
    { 1,    "##earthquake_on##"                     ,chat_weather_earthquake_on             },
    { 1,    "##earthquake_off##"                    ,chat_weather_earthquake_off            },
    { 1,    "##wind_size_dir##"                     ,chat_weather_set_wind                  },

    { 1,    "##god_bless_pos##"                     ,chat_command_enable_secret_skill       },
    { 1,    "##god_love_pos##"                      ,chat_command_disable_secret_skill      },
    { 1,    "##enable_rand_move##"                  ,chat_command_enable_rand_move          },
    { 1,    "##disable_rand_move##"                 ,chat_command_disable_rand_move         },
    { 1,    "##enable_rand_weather##"               ,chat_command_enable_rand_weather       },
    { 1,    "##disable_rand_weather##"              ,chat_command_disable_rand_weather      },
    { 1,    "##enable_follow_npc##"                 ,chat_command_enable_follow_npc         },
    { 1,    "##disable_follow_npc##"                ,chat_command_disable_follow_npc        },
    { 1,    "##keep_map_range##"                    ,chat_command_keep_map_range            },
    { 1,    "##goodgoodstudydaydayup##"             ,chat_command_enable_create_account     },
    { 1,    "##jackjackshowmethedebugminimap##"     ,chat_command_show_debug_minimap        },
    { 1,    "##poly##"								,chat_command_show_object_poly			},
    { 1,    "##tradeshop##"							,chat_command_show_trade_shop			},
    { 1,    "##storeshop##"							,chat_command_show_store_shop			},
    { 1,    "##breakmagic##"						,chat_command_break_magic				},
    { 1,    "/d/gamerange"							,chat_command_show_game_range			},
	//
    { 1,    "/c/hawkepleasegivemefullhpmp"			,chat_command_full_hp_mp				},
    { 1,    "/c/hawkepleasegivemepropertypoint"		,chat_command_get_property_point		},
    { 1,    "/c/iwanttojumpto"						,chat_command_jump_to					},
    { 1,    "/c/showmetheitem"						,chat_command_request_item				},
    { 1,    "/c/hawkepleaseshowmethemoney"			,chat_command_request_money				},
    { 1,    "/c/wouldyoumindgivemesomeexp"			,chat_command_request_exp				},
    { 1,    "/c/jackjackflyfly"						,chat_command_request_move_fast			},
    { 1,    "/c/hahaicanchangezonenow"				,chat_command_request_change_zone		},
    { 1,    "/c/gotohell"							,chat_command_request_dead				},

    { 1,    "##reloadmagic##"                       ,chat_command_reload_magic_ini          },
    { 1,    "/c/mapmapcomehere"                     ,chat_command_request_get_treasure_map   },

    //end parse set, DON'T DELETE !!!
    {-1,    ""                          ,NULL                                   },
};


BREAK_MAGIC_NAME_FUNC	l_break_magic_name_func[100];
/*
BREAK_MAGIC_NAME_FUNC	l_break_magic_name_func[] = 
{

	{"FireBall",		BreakMagic_FireBall				},
	{"FireDragon",		BreakMagic_FireDragon			},
	{"FireWall",		BreakMagic_FireWall				},
	{"FireArmor",		BreakMagic_FireArmor			},
	{"FireBroken",		BreakMagic_FireBroken			},
	{"FireAerolite",	BreakMagic_FireAerolite			},
	{"FireWard",		BreakMagic_FireWard				},
	
	{"IceBall",			BreakMagic_IceBall				},
	{"IceBow",			BreakMagic_IceBow				},
	{"IceMirror",		BreakMagic_IceMirror			},
	{"IceCoagulate",	BreakMagic_IceCoagulate			},
	{"IceCircle",		BreakMagic_IceCircle			},
	{"IceFall",			BreakMagic_IceFall				},
	{"IceBlade",		BreakMagic_IceBlade				},
	
	{"LightStrike",		BreakMagic_LightStrike			},
	{"LightBless",		BreakMagic_LightBless			},
	{"LightBlade",		BreakMagic_LightBlade			},
	{"LightBall",		BreakMagic_LightBall			},
	{"LightBaptism",	BreakMagic_LightBaptism			},
	{"LightThundering",	BreakMagic_LightThundering		},
	
	{"DustUnderStick",	BreakMagic_DustUnderStick		},
	{"DustArrayStones",	BreakMagic_DustArrayStones		},
	{"DustDiffuseWave",	BreakMagic_DustDiffuseWave		},
	{"DustXirang",		BreakMagic_DustXirang			},
	{"DustRollStone",	BreakMagic_DustRollStone		},
	{"DustVirusGas",	BreakMagic_DustVirusGas			},
	{"ArcChop",			BreakMagic_ArcChop				},
	{"SeriesChop",		BreakMagic_SeriesChop			},
	{"SteelSever",		BreakMagic_SteelSever			},
	{"BallyragCircle",	BreakMagic_BallyragCircle		},
	
	{"WindfallChop",	BreakMagic_WindfallChop			},
	{"ThrowDragon",		BreakMagic_ThrowDragon			},
	{"EvilBomb",		BreakMagic_EvilBomb				},
	{"CleanseLight",	BreakMagic_CleanseLight			},
	{"BlestBarrier",	BreakMagic_BlestBarrier			},
	{"Blessing",		BreakMagic_Blessing				},
	{"Prayer",			BreakMagic_Prayer				},
	{"FastWind",		BreakMagic_FastWind				},
	{"HolyPhotosphere",	BreakMagic_HolyPhotosphere		},
	{"VitalWind",		BreakMagic_VitalWind			},
	{"RevengeAngel",	BreakMagic_RevengeAngel			},
	{"JusticeAngel",	BreakMagic_JusticeAngel			},
	
	{"AresDance",		BreakMagic_AresDance			},
	{"BrokenBoxing",	BreakMagic_BrokenBoxing			},
	{"DemonHowl",		BreakMagic_DemonHowl			},
	{"WindBoxing",		BreakMagic_WindBoxing			},
	{"BrokenArmor",		BreakMagic_BrokenArmor			},
	{"ArhatBoxing",		BreakMagic_ArhatBoxing			},
	{"GasBarrier",		BreakMagic_GasBarrier			},
	{"BloodEddies",		BreakMagic_BloodEddies			},

	{"ShipCannon",		BreakMagic_ShipCannon			},

};
*/	
/******************************************************************************************************************/
/* PARSE MAIN FUNCTIONS                                                                                           */
/******************************************************************************************************************/
void    clear_parse_result(void)
{
    memset(&parse_result, 0, sizeof(parse_result));
}

SLONG   parse_chat_input(USTR *input_string)
{
    SLONG   i, ret;

    ret = TTN_NOT_OK;

    reset_parse_data((USTR*)input_string);

    //the first segment for a command lead string.
    get_parse_segment();

    for(i=0; chat_parse_set[i].flag >= 0; i++)
    {
        if(chat_parse_set[i].flag)
        {
            if( is_parse_command( (USTR*)chat_parse_set[i].lead_str ) )
            {
                if(chat_parse_set[i].exe_func)
                {
                    chat_parse_set[i].exe_func();
                }
                ret = TTN_OK;
                break;
            }
        }
    }
    return  ret;
}


/******************************************************************************************************************/
/* PARSE STATIC FUNCTIONS                                                                                         */
/******************************************************************************************************************/
static  void    reset_parse_data(USTR *input)
{
    memset(parse_line, '\0', PARSE_LINE_LEN);
    strcpy((char *)parse_line, (const char *)input);
    parse_index = 0;
}


static  void    get_parse_segment(void)
{
    skip_compartment((USTR*)parse_line, &parse_index, 
        (USTR*)PARSE_SEGMENT_COMPARTMENT_STR, PARSE_SEGMENT_COMPARTMENT_NUM);
    get_string(parse_temp, PARSE_TEMP_LEN, parse_line, &parse_index,
        (USTR*)PARSE_SEGMENT_COMPARTMENT_STR, PARSE_SEGMENT_COMPARTMENT_NUM);
    CharLower((LPSTR)parse_temp);
}


static  SLONG   get_parse_number(SLONG *number)
{
    SLONG   ret;

    ret = TTN_NOT_OK;
    get_parse_segment();
    if(parse_temp[0])
    {
        *number = string_2_number((char *)parse_temp);
        ret = TTN_OK;
    }
    return ret;
}


static  SLONG   get_parse_string(USTR *string)
{
    SLONG   ret;

    ret = TTN_NOT_OK;
    get_parse_segment();
    if(parse_temp[0])
    {
        strcpy((char *)string, (const char *)parse_temp);
        ret = TTN_OK;
    }
    return ret;
}


static  SLONG   is_parse_command(USTR *cmd_string)
{
    if( 0 == strcmpi((const char *)parse_temp, (const char *)cmd_string) )
        return TRUE;
    else
        return FALSE;
}

/******************************************************************************************************************/
/* CHAT COMMAND FUNCTIONS                                                                                         */
/******************************************************************************************************************/
/*
static  void    chat_command_npc_cheer(void)
{
    parse_result.type = PARSE_TYPE_TALK;
    parse_result.talk.doing_kind = DOING_KIND_CHEER;
}
*/
static  void    chat_command_npc_angry(void)
{
    parse_result.type = PARSE_TYPE_TALK;
    parse_result.talk.doing_kind = DOING_KIND_ANGRY;
}

static  void    chat_command_npc_beckon(void)
{
    parse_result.type = PARSE_TYPE_TALK;
    parse_result.talk.doing_kind = DOING_KIND_BECKON;
}
/*
static  void    chat_command_npc_court(void)
{
    parse_result.type = PARSE_TYPE_TALK;
    parse_result.talk.doing_kind = DOING_KIND_COURT;
}
*/
static  void    chat_command_npc_faint(void)
{
    parse_result.type = PARSE_TYPE_TALK;
    parse_result.talk.doing_kind = DOING_KIND_FAINT;
}

static  void    chat_command_npc_say_no(void)
{
    parse_result.type = PARSE_TYPE_TALK;
    parse_result.talk.doing_kind = DOING_KIND_SAY_NO;
}

static  void    chat_command_npc_bow(void)
{
    parse_result.type = PARSE_TYPE_TALK;
    parse_result.talk.doing_kind = DOING_KIND_BOW;
}

static  void    chat_command_npc_win(void)
{
    parse_result.type = PARSE_TYPE_TALK;
    parse_result.talk.doing_kind = DOING_KIND_WIN;
}


static  void    chat_command_npc_swash(void)
{
    parse_result.type = PARSE_TYPE_TALK;
    parse_result.talk.doing_kind = DOING_KIND_SWASH;
}


static  void    chat_command_npc_xxpower(void)
{
    parse_result.type = PARSE_TYPE_TALK;
    parse_result.talk.doing_kind = DOING_KIND_XXPOWER;
}


static  void    chat_command_npc_xxbeated(void)
{
    parse_result.type = PARSE_TYPE_TALK;
    parse_result.talk.doing_kind = DOING_KIND_XXBEATED;
}


static  void    chat_command_npc_spower(void)
{
    parse_result.type = PARSE_TYPE_TALK;
    parse_result.talk.doing_kind = DOING_KIND_SPOWER;
}


static  void    chat_command_get_upgrade_points(void)
{
    parse_result.type = PARSE_TYPE_NONE;
}


static  void    chat_command_debug_show_map_mask(void)
{
    SLONG   flag;

    parse_result.type = PARSE_TYPE_NONE;
    flag = get_game_config_show_map_mask();
    flag = 1-flag;
    set_game_config_show_map_mask(flag);
}


static  void    chat_command_debug_show_map_proc(void)
{
    SLONG   flag;

    parse_result.type = PARSE_TYPE_NONE;
    flag = get_game_config_show_map_proc();
    flag = 1 - flag;
    set_game_config_show_map_proc(flag);
}


static  void    chat_command_debug_show_game_info(void)
{
    SLONG   flag;

    parse_result.type = PARSE_TYPE_NONE;
    flag = get_game_config_show_game_info();
    flag = 1 - flag;
    set_game_config_show_game_info(flag);
}


static  void    chat_command_foot_state(void)
{
    parse_result.type = PARSE_TYPE_NONE;

    SLONG   state, npc_index, result;

    npc_index = g_lPlayerIndex;
    result = get_parse_number(&state);
    if(TTN_OK != result)
        return;

    switch(state)
    {
    case 0: //NPC_FOOT_SPEED_STATE_NORMAL
        SetCharacterFootSpeedState(npc_index, NPC_FOOT_SPEED_STATE_NORMAL);
        SetCharacterFootSpeedTicks(npc_index, 0);
        break;
    case 1: //NPC_FOOT_SPEED_STATE_TARDY
        SetCharacterFootSpeedState(npc_index, NPC_FOOT_SPEED_STATE_TARDY);
        SetCharacterFootSpeedTicks(npc_index, 300);
        break;
    case 2: //NPC_FOOT_SPEED_STATE_TIRED
        SetCharacterFootSpeedState(npc_index, NPC_FOOT_SPEED_STATE_TIRED);
        SetCharacterFootSpeedTicks(npc_index, 300);
        break;
    }
}



void    chat_command_zero_mp(void)
{
    parse_result.type = PARSE_TYPE_NONE;

    LOCK_CHARACTER(g_lPlayerIndex);
    SetCharacterMp(g_lPlayerIndex, 0);
    UNLOCK_CHARACTER(g_lPlayerIndex);
}


void    chat_command_player_file(void)
{
    SLONG   result, file_index;

    parse_result.type = PARSE_TYPE_NONE;

    result = get_parse_number(&file_index);
    if(TTN_OK != result)
        return;

    if(g_lPlayerIndex >= 0)
    {
        LOCK_CHARACTER(g_lPlayerIndex);
		SetCharacterFileIndex(g_lPlayerIndex, file_index);
        UNLOCK_CHARACTER(g_lPlayerIndex);
    }
}


void    chat_weather_rain_on(void)
{
    parse_result.type = PARSE_TYPE_WEATHER;
    parse_result.weather.type = WEATHER_RAIN;
    parse_result.weather.active = WEATHER_STARTUP;
    parse_result.weather.size = WEATHER_LARGE;
    parse_result.weather.wind_size = WIND_DUMMY;
    parse_result.weather.wind_dir = WIND_RIGHT;
}


void    chat_weather_rain_off(void)
{
    parse_result.type = PARSE_TYPE_WEATHER;
    parse_result.weather.type = WEATHER_RAIN;
    parse_result.weather.active = WEATHER_STOP;
    parse_result.weather.size = WEATHER_LARGE;
    parse_result.weather.wind_size = WIND_DUMMY;
    parse_result.weather.wind_dir = WIND_RIGHT;
}


void    chat_weather_snow_on(void)
{
    parse_result.type = PARSE_TYPE_WEATHER;
    parse_result.weather.type = WEATHER_SNOW;
    parse_result.weather.active = WEATHER_STARTUP;
    parse_result.weather.size = WEATHER_LARGE;
    parse_result.weather.wind_size = WIND_DUMMY;
    parse_result.weather.wind_dir = WIND_RIGHT;
}


void    chat_weather_snow_off(void)
{
    parse_result.type = PARSE_TYPE_WEATHER;
    parse_result.weather.type = WEATHER_SNOW;
    parse_result.weather.active = WEATHER_STOP;
    parse_result.weather.size = WEATHER_LARGE;
    parse_result.weather.wind_size = WIND_DUMMY;
    parse_result.weather.wind_dir = WIND_RIGHT;
}


void    chat_weather_thunder_on(void)
{
    parse_result.type = PARSE_TYPE_WEATHER;
    parse_result.weather.type = WEATHER_THUNDER;
    parse_result.weather.active = WEATHER_STARTUP;
    parse_result.weather.size = WEATHER_LARGE;
    parse_result.weather.wind_size = WIND_DUMMY;
    parse_result.weather.wind_dir = WIND_RIGHT;
}


void    chat_weather_thunder_off(void)
{
    parse_result.type = PARSE_TYPE_WEATHER;
    parse_result.weather.type = WEATHER_THUNDER;
    parse_result.weather.active = WEATHER_STOP;
    parse_result.weather.size = WEATHER_LARGE;
    parse_result.weather.wind_size = WIND_DUMMY;
    parse_result.weather.wind_dir = WIND_RIGHT;
}


void    chat_weather_cloud_on(void)
{
    parse_result.type = PARSE_TYPE_WEATHER;
    parse_result.weather.type = WEATHER_CLOUD;
    parse_result.weather.active = WEATHER_STARTUP;
    parse_result.weather.size = WEATHER_LARGE;
    parse_result.weather.wind_size = WIND_DUMMY;
    parse_result.weather.wind_dir = WIND_RIGHT;
}


void    chat_weather_cloud_off(void)
{
    parse_result.type = PARSE_TYPE_WEATHER;
    parse_result.weather.type = WEATHER_CLOUD;
    parse_result.weather.active = WEATHER_STOP;
    parse_result.weather.size = WEATHER_LARGE;
    parse_result.weather.wind_size = WIND_DUMMY;
    parse_result.weather.wind_dir = WIND_RIGHT;
}


void    chat_weather_earthquake_on(void)
{
    parse_result.type = PARSE_TYPE_WEATHER;
    parse_result.weather.type = WEATHER_EARTHQUAKE;
    parse_result.weather.active = WEATHER_STARTUP;
    parse_result.weather.size = WEATHER_LARGE;
    parse_result.weather.wind_size = WIND_DUMMY;
    parse_result.weather.wind_dir = WIND_RIGHT;
}


void    chat_weather_earthquake_off(void)
{
    parse_result.type = PARSE_TYPE_WEATHER;
    parse_result.weather.type = WEATHER_EARTHQUAKE;
    parse_result.weather.active = WEATHER_STOP;
    parse_result.weather.size = WEATHER_LARGE;
    parse_result.weather.wind_size = WIND_DUMMY;
    parse_result.weather.wind_dir = WIND_RIGHT;
}


void    chat_weather_set_wind(void)
{
    SLONG   result, wind_size, wind_dir;

    parse_result.type = PARSE_TYPE_NONE;

    result = get_parse_number(&wind_size);
    if(TTN_OK != result)
        return;
    result = get_parse_number(&wind_dir);
    if(TTN_OK != result)
        return;

    parse_result.type = PARSE_TYPE_WEATHER;
    parse_result.weather.type = WEATHER_DUMMY;
    parse_result.weather.active = 0;
    parse_result.weather.size = 0;
    parse_result.weather.wind_size = wind_size;
    parse_result.weather.wind_dir = wind_dir;
}



//----------------------------------------------------------------------------------------------
static  void    chat_command_enable_secret_skill(void)
{
    parse_result.type = PARSE_TYPE_NONE;
    enable_secret_skill();
}


static  void    chat_command_disable_secret_skill(void)
{
    parse_result.type = PARSE_TYPE_NONE;
    disable_secret_skill();
}


static  void    chat_command_enable_rand_move(void)
{
    parse_result.type = PARSE_TYPE_NONE;
    set_secret_skill_rand_move(true);
}

static  void    chat_command_disable_rand_move(void)
{
    parse_result.type = PARSE_TYPE_NONE;
    set_secret_skill_rand_move(false);
}

static  void    chat_command_enable_rand_weather(void)
{
    parse_result.type = PARSE_TYPE_NONE;
    set_secret_skill_rand_weather(true);
}


static  void    chat_command_disable_rand_weather(void)
{
    parse_result.type = PARSE_TYPE_NONE;
    set_secret_skill_rand_weather(false);
}


static  void    chat_command_enable_follow_npc(void)
{
    USTR    mainname[128];
    SLONG   result;

    parse_result.type = PARSE_TYPE_NONE;
    result = get_parse_string(mainname);
    if(TTN_OK != result)
        return;

    set_secret_skill_follow_npc(true, (USTR *)mainname);
}


static  void    chat_command_disable_follow_npc(void)
{
    set_secret_skill_follow_npc(false, NULL);
}


static  void    chat_command_keep_map_range(void)
{
    SLONG   result, flag;

    parse_result.type = PARSE_TYPE_NONE;

    result = get_parse_number(&flag);
    if(TTN_OK != result)
        return;

    set_map_move_keep_range(flag);
}

static  void    chat_command_enable_create_account(void)
{
    set_secret_skill_create_account(true);
}


static	void	chat_command_show_debug_minimap(void)
{
    SLONG   flag;

    parse_result.type = PARSE_TYPE_NONE;
    flag = get_game_config_show_debug_minimap();
    flag = 1 - flag;
    set_game_config_show_debug_minimap(flag);
}


static	void	chat_command_show_object_poly(void)
{
	SLONG	is_show;

    parse_result.type = PARSE_TYPE_NONE;
	is_show = is_redraw_map_object_poly();
	set_redraw_map_object_poly(1 - is_show);
}


static	void	chat_command_show_trade_shop(void)
{
	SLONG	is_show;

    parse_result.type = PARSE_TYPE_NONE;
	is_show = is_ui_shop_open();
	open_ui_shop(1 - is_show);
}


static	void	chat_command_show_store_shop(void)
{
	SLONG	is_show;

    parse_result.type = PARSE_TYPE_NONE;
	is_show = is_ui_store_opened();
	open_ui_store(1 - is_show);
}



static	void	chat_command_full_hp_mp(void)
{
    parse_result.type = PARSE_TYPE_NONE;
	ClientGodRequestFullHpMp();
}

static	void	chat_command_get_property_point(void)
{
    SLONG   result, number;

    parse_result.type = PARSE_TYPE_NONE;

    result = get_parse_number(&number);
    if(TTN_OK != result)
        return;

    if(g_lPlayerIndex >= 0 && number > 0)
    {
		ClientGodRequestPropertyPoint(number);
    }
}



static	void	chat_command_jump_to(void)
{
    SLONG   result, x, y, z;

    parse_result.type = PARSE_TYPE_NONE;

    result = get_parse_number(&x);
    if(TTN_OK != result)
        return;
    result = get_parse_number(&y);
    if(TTN_OK != result)
        return;
    result = get_parse_number(&z);
    if(TTN_OK != result)
        return;

    if(g_lPlayerIndex >= 0)
    {
		ClientGodRequestJumpTo(x, y, z);
    }
}

static	void	chat_command_request_item(void)
{
    SLONG   result, base_id;

    parse_result.type = PARSE_TYPE_NONE;

    result = get_parse_number(&base_id);
    if(TTN_OK != result)
        return;
    if(g_lPlayerIndex >= 0)
    {
		ClientGodRequestItem((UHINT)base_id);
    }
}

static	void	chat_command_request_money(void)
{
    SLONG   result;
	SLONG	money;

    parse_result.type = PARSE_TYPE_NONE;

    result = get_parse_number(&money);
    if(TTN_OK != result)
        return;

    if(g_lPlayerIndex >= 0)
    {
		ClientGodRequestMoney((ULONG)money);
    }
}

static	void	chat_command_request_exp(void)
{
    SLONG   result;
	SLONG	exp;

    parse_result.type = PARSE_TYPE_NONE;

    result = get_parse_number(&exp);
    if(TTN_OK != result)
        return;

    if(g_lPlayerIndex >= 0)
    {
		ClientGodRequestExp((ULONG)exp);
    }
}

static	void	chat_command_request_move_fast(void)
{
    SLONG   result;
	SLONG	speed;

    parse_result.type = PARSE_TYPE_NONE;

    result = get_parse_number(&speed);
    if(TTN_OK != result)
        return;

    if(g_lPlayerIndex >= 0)
    {
		ClientGodRequestMoveFast((ULONG)speed);
    }
}

static	void	chat_command_request_change_zone(void)
{
    SLONG   result;
	SLONG	x, y, z;
	USTR	zone_name[64];

    parse_result.type = PARSE_TYPE_NONE;

    result = get_parse_string(zone_name);
    if(TTN_OK != result)
        return;
    result = get_parse_number(&x);
    if(TTN_OK != result)
        return;
    result = get_parse_number(&y);
    if(TTN_OK != result)
        return;
    result = get_parse_number(&z);
    if(TTN_OK != result)
        return;

    if(g_lPlayerIndex >= 0)
    {
		ClientGodRequestChangeZone((CHAR*)zone_name, x, y, z);
    }
}

static	void	chat_command_request_dead(void)
{
	ClientGodRequestDead();
}


static	void	chat_command_break_magic(void)
{
    SLONG   result;
	SLONG	npc_no, dest_x, dest_y, magic_no, dest_no;
	SLONG	mx, my;
	USTR	break_name[128];
	SLONG	i;

    parse_result.type = PARSE_TYPE_NONE;

	get_mouse_position(&mx, &my);
	dest_x = mx + map_data.map_sx;
	dest_y = my + map_data.map_sy;

    result = get_parse_string((USTR*)break_name);
    if(TTN_OK != result)
		return;
	dest_no = -1;
	magic_no = 0;
	npc_no = g_lPlayerIndex;
	for(i=0; i<sizeof(l_break_magic_name_func)/sizeof(l_break_magic_name_func[0]); i++)
	{
		if(0 == strcmpi((const char *)break_name, (const char *)l_break_magic_name_func[i].name))
		{
			l_break_magic_name_func[i].func(magic_no, npc_no, dest_x, dest_y, dest_no);
		}
	}
	AppendBreakMagicParts();
}


static	void	chat_command_show_game_range(void)
{
	set_game_config_show_game_range(1 - get_game_config_show_game_range());
}

//----
//  ini 文件從新讀取函數
//----
static  void    chat_command_reload_magic_ini(void)
{
    //
    InitSkillSystem();
}


// 獲得藏寶圖中的寶藏位置 zzh 2003.5.17
VOID    chat_command_request_get_treasure_map( void )
{
    LONG para1, para2;

    if ( TTN_OK != get_parse_number( &para1 ) )
        return;
    if ( TTN_OK != get_parse_number( &para2 ) )
        return;

    ClientGodRequestTreasureMap( para1, para2 );
}