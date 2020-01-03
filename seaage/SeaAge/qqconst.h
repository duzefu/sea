/*
**    qqconst.h
**
**    Const variable declaration for UIQQ
**
**    Zhang Zhaohui, 2002/11/07.
*/

#pragma once

#include "mainfun.h"

typedef enum QQ_ENUMS
{
    QQ_EVENT                        = 29999,
    QQ_MOUSE_DOWN                   = 1,
    QQ_MOUSE_UP                     = 2,
    QQ_MAX_FRIEND_LIST              = 9,
    QQ_MINIMIZE                     = 10,
    QQ_MAXIMIZE                     = 11,
    QQ_CHATITEMLOGLIST_FIX_DY       = -20,
}QQ_ENUMS;


typedef enum    QQMAIN_ENUMS
{   QQMAIN_FRAME_BKGND              =   0,
QQMAIN_FRAME_MINIMIZE               =   1,
QQMAIN_FRAME_MAXIMIZE               =   37,
QQMAIN_FRAME_HIDE_STATE_LOGIN       =   3,
QQMAIN_FRAME_SHOW_STATE_LOGIN       =   5,
QQMAIN_FRAME_CALLGM                 =   7,
QQMAIN_FRAME_LIST_PAGEUP            =   9,
QQMAIN_FRAME_LIST_PAGEDOWN          =   12,
QQMAIN_FRAME_KIND_MY_FRIENDS        =   13,         //我的好友
QQMAIN_FRAME_KIND_TEAM_PLAYERS      =   16,         //隊伍成員
QQMAIN_FRAME_KIND_GUILD_PLAYERS     =   19,         //工會成員
QQMAIN_FRAME_KIND_STRANGERS         =   22,         //陌生人
QQMAIN_FRAME_KIND_UNDESIREDERS      =   25,         //黑名單
QQMAIN_FRAME_SYSSET                 =   28,
QQMAIN_FRAME_MESSAGE                =   31,
QQMAIN_FRAME_SEARCH                 =   34,
//
QQMAIN_EVENT                        =   20000,
QQMAIN_ID_BKGND                     =   5,
QQMAIN_ID_MINIMIZE                  =   10,
QQMAIN_ID_MAXIMIZE                  =    15,
QQMAIN_ID_SWITCH_LOGIN_STATE        =   20,
QQMAIN_ID_CALLGM                    =   30,
QQMAIN_ID_SYSSET                    =   40,
QQMAIN_ID_MESSAGE                   =   50,
QQMAIN_ID_SEARCH                    =   60,
QQMAIN_ID_POPUP                     =    70,
QQMAIN_ID_CHAT                      =    80,
QQMAIN_ID_KIND_MY_FRIENDS           =   100,
QQMAIN_ID_KIND_TEAM_PLAYERS         =   101,
QQMAIN_ID_KIND_GUILD_PLAYERS        =   102,
QQMAIN_ID_KIND_STRANGERS            =   103,
QQMAIN_ID_KIND_UNDESIREDERS         =   104,
QQMAIN_ID_LIST_0                    =   200,
QQMAIN_ID_LIST_PAGEUP               =   300,
QQMAIN_ID_LIST_PAGEDOWN             =   310,
QQMAIN_ID_FACE                      =    320,
//
QQMAIN_LIST_SX                      =   723,        //好友名單等外框
QQMAIN_LIST_SY                      =   196,
QQMAIN_LIST_XL                      =   796 - 724,
QQMAIN_LIST_YL                      =   504 - 196,
QQMAIN_KIND_XL                      =   72,         //我的好友等按鈕尺寸
QQMAIN_KIND_YL                      =   17,
QQMAIN_LIST_KINDS                   =   5,
QQMAIN_MAX_SX                       =    766,
QQMAIN_MAX_SY                       =    58,
QQMAIN_LIST_ITEM_SX                 =    725,
QQMAIN_LIST_ITEM_MAX                =   9,
QQMAIN_LIST_AERA_YL                 =   224,
QQMAIN_KIND_MOVE_SPEED              =   40,
} QQMAIN_ENUMS;


typedef enum    QQCHAT_ENUMS
{   
QQCHAT_FRAME_BKGND                  = 0,          //輸入文字之背景
QQCHAT_FRAME_SEND_TO_MULTI          = 1,
QQCHAT_FRAME_CHAT_LOG               = 4,
QQCHAT_FRAME_SEND_ITEM              = 7,
QQCHAT_FRAME_CANCEL                 = 10,
QQCHAT_FRAME_SEND                   = 13,
QQCHAT_FRAME_REPLAY                 = 16,
QQCHAT_FRAME_CLOSE                  = 19,
QQCHAT_FRAME_NEXT                   = 22,


QQCHAT_EVENT                        = 20001,
QQCHAT_ID_BKGND                     = 100,
QQCHAT_ID_INPUT_MEMO                = 110,
QQCHAT_ID_SEND_TO_MULTI             = 120,
QQCHAT_ID_CHAT_LOG                  = 130,
QQCHAT_ID_SEND_ITEM                 = 140,
QQCHAT_ID_CANCEL                    = 150,
QQCHAT_ID_SEND                      = 160,
QQCHAT_ID_REPLAY                    = 170,
QQCHAT_ID_CLOSE                     = 180,
QQCHAT_ID_NEXT                      = 190,

QQCHAT_TARGET_FACE_SX               = 480,
QQCHAT_TARGET_FACE_SY               = 275,
QQCHAT_TARGET_FACE_XL               = 502 - 478,
QQCHAT_TARGET_FACE_YL               = 296 - 274,
QQCHAT_TARGET_NAME_SX               = 512,
QQCHAT_TARGET_NAME_SY               = 280,
QQCHAT_TARGET_NAME_XL               = 578 - 512,
QQCHAT_TARGET_NAME_YL               = 294 - 280,
QQCHAT_INPUT_MEMO_SX                = 484,
QQCHAT_INPUT_MEMO_SY                = 308,
QQCHAT_INPUT_MEMO_XL                = 226,
QQCHAT_INPUT_MEMO_YL                = 92,
} QQCHAT_ENUMS;


typedef enum    QQCALLGM_ENUMS
{   
QQCALLGM_FRAME_BKGND                = 0,
QQCALLGM_FRAME_SEND                 = 1,
QQCALLGM_FRAME_CANCEL               = 4,

QQCALLGM_EVENT                      = 20002,

QQCALLGM_ID_BKGND                   = 5,
QQCALLGM_ID_SEND                    = 10,
QQCALLGM_ID_CANCEL                  = 20,
QQCALLGM_ID_TEXT                    = 40,
//
QQCALLGM_INPUT_MEMO_SX              = 440,
QQCALLGM_INPUT_MEMO_SY              = 256,
QQCALLGM_INPUT_MEMO_XL              = 228,
QQCALLGM_INPUT_MEMO_YL              = 98,

} QQCALLGM_ENUMS;

typedef enum QQPOPUP_ENUMS
{
    QQPOPUP_FRAME_BKGND             = 0,
    QQPOPUP_FRAME_CHECK             = 1,
    QQPOPUP_FRAME_DELETE            = 4,

    QQPOPUP_EVENT                   = 20003,
    QQPOPUP_ID_BKGND                = 100,
    QQPOPUP_ID_CHECK                = 110,
    QQPOPUP_ID_DELETE               = 120,

    QQPOPUP_ID_DY1                  = 3,
    QQPOPUP_ID_DY2                  = 20,


}QQPOPUP_ENUMS;

typedef enum QQDETAIL_ENUMS
{
    QQDETAIL_FRAME_BKGND            = 0,
    QQDETAIL_FRAME_OK               = 1,

    QQDETAIL_EVENT                  = 20004,

    QQDETAIL_ID_BKGND               = 10,
    QQDETAIL_ID_OK                  = 20,

    QQDETAIL_NAME_SX                = 547,
    QQDETAIL_NAME_SY                = 205,
    QQDETAIL_NICKNAME_SX            = 547,
    QQDETAIL_NICKNAME_SY            = 224,
    QQDETAIL_GUILD_SX               = 547,
    QQDETAIL_GUILD_SY               = 241,
    QQDETAIL_PARTNER_SX             = 547,
    QQDETAIL_PARTNER_SY             = 260,
    QQDETAIL_NNGP_XL                = 661-547,
    QQDETAIL_NNGP_YL                = 16,

    QQDETAIL_COUNTRY_SX             = 493,
    QQDETAIL_COUNTRY_SY             = 280,
    QQDETAIL_COUNTRY_XL             = 575-493,
    QQDETAIL_COUNTRY_YL             = 16,
    
    QQDETAIL_LEVEL_SX               = 626,
    QQDETAIL_LEVEL_SY               = 281,
    QQDETAIL_LEVEL_XL               = 666-626,
    QQDETAIL_LEVEL_YL               = 16,

    QQDETAIL_PK_SX                  = 493,
    QQDETAIL_PK_SY                  = 300,
    QQDETAIL_MONEY_SX               = 493,
    QQDETAIL_MONEY_SY               = 322,
    QQDETAIL_PRESTIGE_SX            = 493,
    QQDETAIL_PRESTIGE_SY            = 343,
    QQDETAIL_PMP_XL                 = 562-493,
    QQDETAIL_PMP_YL                 = 16,

    QQDETAIL_ICON_SX                = 442,
    QQDETAIL_ICON_SY                = 208,
    QQDETAIL_ICON_XL                = 50,
    QQDETAIL_ICON_YL                = 60,


}QQDETAIL_ENUMS;


typedef enum QQFIND1_ENUMS
{
    QQFIND1_FRAME_BKGND             =   0,
    QQFIND1_FRAME_NEXT              =   4,
    QQFIND1_FRAME_CANCEL            =   7,
    //
    QQFIND1_EVENT                   = 20005,

    QQFIND1_ID_BKGND                = 5,
    QQFIND1_ID_NEXT                 = 10,
    QQFIND1_ID_CANCEL               = 20,

    QQFIND1_ID_ITEM1                = 50,
    QQFIND1_ID_ITEM2                = 60,
    QQFIND1_ID_ITEM3                = 65,
    QQFIND1_ID_SELECT1              = 70,
    QQFIND1_ID_SELECT2              = 80,
    QQFIND1_ID_SELECT3              = 90,

    QQFIND1_ITEM1_SX                = 486,
    QQFIND1_ITEM1_SY                = 214,

    QQFIND1_ITEM2_SX                = 486,
    QQFIND1_ITEM2_SY                = 246,

    QQFIND1_ITEM3_SX                = 486,
    QQFIND1_ITEM3_SY                = 284,

    QQFIND1_ITEM_XL                 = 124,
    QQFIND1_ITEM_YL                 = 30,


    QQFIND1_SELECT1_SX              = 496,
    QQFIND1_SELECT1_SY              = 227,
    QQFIND1_SELECT2_SX              = 496,
    QQFIND1_SELECT2_SY              = 263,    
    QQFIND1_SELECT3_SX              = 496,
    QQFIND1_SELECT3_SY              = 296,
    QQFIND1_COUNT_SX                = 566,
    QQFIND1_COUNT_SY                = 346,
    
}QQFIND1_ENUMS;


typedef enum QQFIND2_ENUMS
{
    QQFIND2_FRAME_BKGND             = 0,
    QQFIND2_FRAME_LAST              = 1,
    QQFIND2_FRAME_NEXT              = 4,
    QQFIND2_FRAME_CANCEL            = 7,
    
    QQFIND2_EVENT                   = 20006,

    QQFIND2_ID_BKGND                = 100,
    QQFIND2_ID_LAST                 = 110,
    QQFIND2_ID_NEXT                 = 120,
    QQFIND2_ID_CANCEL               = 130,

    QQFIND2_ID_NAME                 = 200,
    QQFIND2_ID_NICKNAME             = 210,
    QQFIND2_ID_GUILD                = 220,
    QQFIND2_ID_LEVEL                = 230,
    QQFIND2_ID_COUNTRY              = 240,

    QQFIND2_NAME_SX                 = 496,
    QQFIND2_NAME_SY                 = 208,
    QQFIND2_NICKNAME_SX             = 496,
    QQFIND2_NICKNAME_SY             = 234,
    QQFIND2_GUILD_SX                = 496,
    QQFIND2_GUILD_SY                = 256,
    QQFIND2_COUNTRY_SX              = 496,
    QQFIND2_COUNTRY_SY              = 282,
    QQFIND2_LEVEL_SX                = 496,
    QQFIND2_LEVEL_SY                = 308,
    QQFIND2_INPUT_XL                = 164,
    QQFIND2_INPUT_YL                = 16,
    QQFIND2_COUNT_SX                = 565,
    QQFIND2_COUNT_SY                = 346,

}QQFIND2_ENUMS;

typedef enum QQFIND3_ENUMS
{
    QQFIND3_FRAME_BKGND             = 0,
    QQFIND3_FRAME_DETAIL            = 1,
    QQFIND3_FRAME_LAST              = 4,
    QQFIND3_FRAME_NEXT              = 7,
    QQFIND3_FRAME_CANCEL            = 10,
    QQFIND3_FRAME_UP                = 13,
    QQFIND3_FRAME_DOWN              = 15,

    QQFIND3_EVENT                   = 20007,

    QQFIND3_ID_BKGND                = 100,
    QQFIND3_ID_DETAIL               = 110,
    QQFIND3_ID_LAST                 = 120,
    QQFIND3_ID_NEXT                 = 130,
    QQFIND3_ID_CANCEL               = 140,
    QQFIND3_ID_UP                   = 150,
    QQFIND3_ID_DOWN                 = 160,
    QQFIND3_ID_LIST                 = 170,

    QQFIND3_LIST_SY                 = 224,
    QQFIND3_LIST_YL                 = 132,
    QQFIND3_LIST_NAME_SX            = 438,
    QQFIND3_LIST_NAME_XL            = 72,
    QQFIND3_LIST_LEVEL_SX           = 520,
    QQFIND3_LIST_LEVEL_XL           = 30,
    QQFIND3_LIST_GUILD_SX           = 560,
    QQFIND3_LIST_GUILD_XL           = 108,
    QQFIND3_LIST_XL                 = 230,

    QQFIND3_LIST_NORMAL             = 20,
    QQFIND3_LIST_HILIGHT            = 30,
    QQFIND3_LIST_SELECTED           = 40,

}QQFIND3_ENUMS;


typedef enum QQITEM_ENUMS
{
    QQITEM_FRAME_BKGND              = 0,
    QQITEM_FRAME_RANGE              = 1,
    QQITEM_EVENT                    = 20008,
    QQITEM_ID_BKGND                 = 100,
    QQITEM_ID_ITEM1                 = 110,
    QQITEM_ID_ITEM2                 = 120,
    QQITEM_ID_ITEM3                 = 130,
    QQITEM_ID_INPUT                 = 140,
    QQITEM_ID_RANGE                 = 150,

    //TO DO
    QQITEM_ITEM_SX                  = 483,
    QQITEM_ITEM_SY                  = 440,
    QQITEM_ITEM_XL                  = 30,
    QQITEM_ITEM_YL                  = 30,
    QQITEM_ITEM_STEP_X              = 33,
    
    QQITEM_INPUT_SX                 = 618,
    QQITEM_INPUT_SY                 = 446,
    QQITEM_INPUT_XL                 = 710-618,
    QQITEM_INPUT_YL                 = 464-446,
    
}QQITEM_ENUMS;


typedef enum QQLOG_ENUMS
{
    QQLOG_FRAME_BKGND               = 0,
    QQLOG_FRAME_UP                  = 1,
    QQLOG_FRAME_DOWN                = 3,

    QQLOG_EVENT                     = 20009,

    QQLOG_ID_BKGND                  = 100,
    QQLOG_ID_UP                     = 110,
    QQLOG_ID_DOWN                   = 120,

    QQLOG_LOG_SX                    = 483,
    QQLOG_LOG_SY                    = 440,
    QQLOG_LOG_XL                    = 217,
    QQLOG_LOG_YL                    = 110,

    QQLOG_BUF_SIZE                  = 200,

}QQLOG_ENUMS;

typedef enum QQSET_ENUMS
{
    QQSET_FRAME_BKGND               = 0,
    QQSET_FRAME_DEFAULT             = 1,
    QQSET_FRAME_OK                  = 4,
    QQSET_FRAME_CANCEL              = 7,

    QQSET_EVENT                     = 20010,

    QQSET_ID_BKGND                  = 50,
    QQSET_ID_DEFAULT                = 100,
    QQSET_ID_OK                     = 110,
    QQSET_ID_CANCEL                 = 120,
    QQSET_ID_SET1                   = 1,
    QQSET_ID_SET2                   = 2,
    QQSET_ID_SET3                   = 4,
    QQSET_ID_SET4                   = 8,
    QQSET_ID_SET5                   = 16,
    QQSET_ID_SET6                   = 32,
    QQSET_ID_SET7                   = 64,
    QQSET_ID_SET8                   = 128,

    QQSET_SET1_SX                   = 384,
    QQSET_SET1_SY                   = 350,
    QQSET_SET1_XL                   = 100,
    QQSET_SET1_YL                   = 20,

    QQSET_SET2_SX                   = 492,
    QQSET_SET2_SY                   = 350,
    QQSET_SET2_XL                   = 104,
    QQSET_SET2_YL                   = 20,

    QQSET_SET3_SX                   = 384,
    QQSET_SET3_SY                   = 372,
    QQSET_SET3_XL                   = 140,
    QQSET_SET3_YL                   = 20,
    
    QQSET_SET4_SX                   = 384,
    QQSET_SET4_SY                   = 394,
    QQSET_SET4_XL                   = 163,
    QQSET_SET4_YL                   = 20,

    QQSET_SET5_SX                   = 384,
    QQSET_SET5_SY                   = 416,
    QQSET_SET5_XL                   = 140,
    QQSET_SET5_YL                   = 20,

    QQSET_SET6_SX                   = 384,
    QQSET_SET6_SY                   = 437,
    QQSET_SET6_XL                   = 118,
    QQSET_SET6_YL                   = 20,

    QQSET_SET7_SX                   = 384,
    QQSET_SET7_SY                   = 457,
    QQSET_SET7_XL                   = 161,
    QQSET_SET7_YL                   = 20,

    QQSET_SELECT1_SX                = 391,
    QQSET_SELECT1_SY                = 360,
    QQSET_SELECT2_SX                = 502,
    QQSET_SELECT2_SY                = 360,
    QQSET_SELECT3_SX                = 391,
    QQSET_SELECT3_SY                = 382,
    QQSET_SELECT4_SX                = 391,
    QQSET_SELECT4_SY                = 403,
    QQSET_SELECT5_SX                = 391,
    QQSET_SELECT5_SY                = 426,
    QQSET_SELECT6_SX                = 391,
    QQSET_SELECT6_SY                = 446,
    QQSET_SELECT7_SX                = 391,
    QQSET_SELECT7_SY                = 467,

    QQSET_FIX_DX                    = 56,
    
}QQSET_ENUMS;


typedef enum QQVERIFY_ENUMS
{
    QQVERIFY_FRAME_BKGND            = 0,
    QQVERIFY_FRAME_SEND             = 1,
    QQVERIFY_FRAME_LAST             = 4,
    QQVERIFY_FRAME_OK               = 7,
    QQVERIFY_FRAME_CANCEL           = 10,


    QQVERIFY_EVENT                  = 20011,

    QQVERIFY_ID_BKGND               = 110,
    QQVERIFY_ID_SEND                = 120,
    QQVERIFY_ID_LAST                = 130,
    QQVERIFY_ID_OK                  = 140,
    QQVERIFY_ID_CANCEL              = 150,
    QQVERIFY_ID_NAME                = 160,
    QQVERIFY_ID_LEVEL               = 170,
    QQVERIFY_ID_GUILD               = 180,
    QQVERIFY_ID_INPUT_MESSAGE       = 190,

    QQVERIFY_NAME_SX                = 438,
    QQVERIFY_NAME_XL                = 74,

    QQVERIFY_LEVEL_SX               = 516,
    QQVERIFY_LEVEL_XL               = 38,

    QQVERIFY_GUILD_SX               = 560,
    QQVERIFY_GUILD_XL               = 108,

    QQVERIFY_INFO_SY                = 226,
    QQVERIFY_INFO_YL                = 24,
    
    QQVERIFY_MSG_SX                 = 450,
    QQVERIFY_MSG_SY                 = 280,
    QQVERIFY_MSG_XL                 = 154,
    QQVERIFY_MSG_YL                 = 60,

}QQVERIFY_ENUMS;


typedef enum QQFACE_ENUMS
{
    QQFACE_FRAME_START              = 0,
    QQFACE_EVENT                    = 20012,
    QQFACE_ID_START                 = 0,
    QQFACE_SY                       = 3,
    QQFACE_STEP_Y                   = 2,
    QQFACE_SX                       = 0,

    QQFACE_EFFECT_NORMAL            = 1,
    QQFACE_EFFECT_GRAY              = 2,
    QQFACE_EFFECT_UP                = 4,
    QQFACE_EFFECT_DOWN              = 8,
    QQFACE_EFFECT_TITTUP            = 16,

}QQFACE_ENUMS;

typedef enum QQLIST_ENUMS
{
QQLIST_FRAME_BKGND                  = 0,
QQLIST_FRAME_MYFRIENDS              = 1,
QQLIST_FRAME_TEAMPLAYERS            = 4,
QQLIST_FRAME_GUILDPLAYERS           = 7,
QQLIST_FRAME_STRANGERS              = 10,
QQLIST_FRAME_UNDESIREDERS           = 13,
QQLIST_FRAME_SEND_TO_MUTIL          = 16,
QQLIST_FRAME_UP                     = 19,
QQLIST_FRAME_DOWN                   = 21,

QQLIST_EVENT                        = 20013,
QQLIST_ID_BKGND                     = 100,
QQLIST_ID_MYFRIENDS                 = 110,
QQLIST_ID_TEAMPLAYERS               = 120,
QQLIST_ID_GUILDPLAYERS              = 130,
QQLIST_ID_STRANGERS                 = 140,
QQLIST_ID_UNDESIREDERS              = 150,
QQLIST_ID_SEND_TO_MUTIL             = 160,
QQLIST_ID_UP                        = 170,
QQLIST_ID_DOWN                      = 180,
QQLIST_ID_LIST                      = 190,

QQLIST_MAX_LIST                     = 10,
QQLIST_LIST_SX                      = 496,    
QQLIST_LIST_SY                      = 431,
QQLIST_LIST_DX                      = 54,
QQLIST_LIST_DY                      = 12,
QQLIST_LIST_ITEM_DX                 = 80,
QQLIST_LIST_ITEM_DY                 = 22,
QQLIST_CHECK_SX                     = 486,
QQLIST_CHECK_SY                     = 438,
QQLIST_CHECK_DX                     = 80,
QQLIST_CHECK_DY                     = 24,
}QQLIST_ENUMS;

typedef enum QQHIS_ENUMS
{
    QQHIS_EVENT                    = 20014,
    
    QQHIS_FRAME_BKGND               = 0,
    QQHIS_FRAME_OK                  = 1,
    QQHIS_FRAME_CANCEL              = 4,
    QQHIS_FRAME_UP                  = 7,
    QQHIS_FRAME_DOWN                = 9,
    
    
    QQHIS_ID_BKGND                  = 100,
    QQHIS_ID_OK                     = 110,
    QQHIS_ID_CANCEL                 = 120,
    QQHIS_ID_UP                     = 130,
    QQHIS_ID_DOWN                   = 140,

    QQHIS_OUTPUT_SX                 = 444,
    QQHIS_OUTPUT_SY                 = 230,
    QQHIS_OUTPUT_XL                 = 221,
    QQHIS_OUTPUT_YL                 = 120,
}QQHIS_ENUMS;


typedef enum QQ_MSGBOX_ID
{
    QQ_MB_SEARCH1,
    QQ_MB_FIND2_1,
    QQ_MB_INPUT_EMPTY,
    QQ_MB_CHAT_1,
    QQ_MB_FIND3_1,
    QQ_MB_FIND3_2,
    QQ_MB_POPUP_1,
}QQ_MSGBOX_ID;
