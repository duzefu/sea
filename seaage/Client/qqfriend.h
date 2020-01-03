/*
 * qqfriend.h
 * functions and structures for qq friend list
 *
 * Created by Zhang Zhaohui, 2002.10.31
 *
 */

#pragma once

#include "mainfun.h"
#include "clientmain.h"
#include "uimanface.h"


/*
 *  Firends information type
 */
enum QQ_FRIEND
{
    QQ_MY_FRIENDS           = 100,
    QQ_TEAM_PLAYERS         = 101,
    QQ_GUILD_PLAYERS        = 102,
    QQ_STRANGERS            = 103,
    QQ_UNDESIREDERS         = 104,
};


/*
 *  Firends settings, stores in a DWORD variable.  
 */
enum QQ_SETTINGS
{
    HIDE_LOGIN              = 1,
    PUB_DETAIL              = 2,
    AUTO_SHOW               = 4,
    SHOW_ONLINE_ONLY        = 8,
    FRIEND_ONLINE_BOX       = 16,
    NEED_VERIFY             = 32,
    KEEP_STRANGER_AWAY      = 64,
};


/*
 *  How many friends in each kind of friend list.
 */
enum QQ_FRIEND_BUF_SIZE
{
    QF_MY_FRIEND_SIZE       = 256,
    QF_TEAM_SIZE            = 7,
    QF_GUILD_SIZE           = 128,
    QF_STRANGER_SIZE        = 64,
    QF_UNDESIREDER_SIZE     = 256,
};    // total 455, friends and undesireders share memory


/*
 *    Friend status
 */
enum QQ_FRIEND_STATE
{
    QF_OFFLINE        = 0,
    QF_ONLINE        = 1,
    QF_HIDE            = 2,
};


/*
 * Structure use for stores friend information.
 */ 
typedef struct tagUI_QQFRIEND
{
    char            name[32];           // friend main name
    char            nickname[32];       // friend nickname
    char            guild_name[32];
    char            partner_name[32];
    char            country;            // country index
    DWORD            pk;                 // friend pk(player kill) value
    DWORD            money;
    DWORD            prestige;
    DWORD            level;
    DWORD            icon_index;
    DWORD            settings;           // settings, one or more QQ_SETTINGS,
    DWORD            sid;          // server friend index
    MANFACE_DATA    manface;            // friend face
    char            state;                // friend is offline/online/hide
}UI_QQFRIEND, *LPUI_QQFRIEND;    // 170 bytes


/*
 * Structure for stores a node of friend list
 */
typedef struct tagUI_QF_LIST UI_QF_LIST, *LPUI_QF_LIST;
struct tagUI_QF_LIST
{
    LPUI_QF_LIST            next;           /* next UI_QF_LIST */
    UI_QQFRIEND             friend_info;    /* stores friend info */
};


/*
 * Structure for stores header of friend list
 */
typedef struct tagUI_QF_MAIN
{
    LPUI_QF_LIST        pmy_friends;
    LPUI_QF_LIST        pteam_players;
    LPUI_QF_LIST        pguild_players;
    LPUI_QF_LIST        pstrangers;
    LPUI_QF_LIST        pundesireders;
    SLONG               nmf_count;
    SLONG               ntp_count;
    SLONG               ngp_count;
    SLONG               ns_count;
    SLONG               nu_count;
}UI_QF_MAIN, *LPUI_QF_MAIN;


/*
 * Initialize and free friend information buffer functions
 */
SLONG    init_qf(void);
void    free_qf(void);

/*
 * Functions for create and delete single friend
 */
UI_QQFRIEND *qf_new(void);
void        qf_free(LPUI_QQFRIEND p_qf);


/*
 *  Main functions for processes friend infromation
 *      qfg --- friend group number
 */
SLONG   qf_add(LPUI_QQFRIEND p_qf, SLONG qfg);
SLONG   qf_delete(SLONG index, SLONG qfg);
SLONG   qf_get_index(LPUI_QQFRIEND p_qf, SLONG qfg);
SLONG   qf_get_group_by_name(char *name);
SLONG   qf_get_index_by_name(char *name, SLONG qfg);
UI_QQFRIEND *qf_get(SLONG index, SLONG qfg);
UI_QQFRIEND *qf_get_by_sid(DWORD sid, SLONG qfg);
SLONG   qf_get_group_by_sid(SLONG sid);
SLONG   qf_get_index_by_sid(DWORD sid, SLONG qfg);
/*
 * Change and check friend settings
 */
void    qfs_enable(LPUI_QQFRIEND p_qf, DWORD settings);
void    qfs_disable(LPUI_QQFRIEND p_qf, DWORD settings);
BOOL    qfs_check(LPUI_QQFRIEND p_qf, DWORD settings);


/*
 *  Functions for processes friend list
 *      qfg --- friend group number
 */
void    qfl_clear_all(void);
SLONG   *qfl_pcount(SLONG qfg);
SLONG   qfl_count(SLONG qfg);
SLONG   qfl_online_count(SLONG qfg);
SLONG   qfl_max_count(SLONG qfg);
UI_QF_LIST *qfl_get(SLONG index, SLONG qfg);
UI_QF_LIST *qfl_get_empty(void);
UI_QF_LIST **qfl_get_header_pointer(SLONG qfg);
UI_QF_LIST *qfl_get_header(SLONG qfg);


/*
 * Sort friend list by friend's name
 *      qfg --- friend group number
 */
void    qfl_sort(SLONG qfg);
void    qfl_qsort(SLONG qfg, SLONG l, SLONG r);
SLONG   qfl_compare(LPUI_QQFRIEND p_qfa, LPUI_QQFRIEND p_qfb);
SLONG   qfl_swap(SLONG i, SLONG j, SLONG qfg);


/*
 *  Load and save friend information from local or server
 */
void    qf_save(void);
void    qf_load(void);
void    qf_refresh(void);
void    qf_refresh_specify(LPUI_QQFRIEND p_qf);


/*
 * Get player self information
 */
UI_QQFRIEND *qfm_get_info(void);
void    qfm_clear(void);
void    qfm_set_sid(DWORD id);
DWORD   qfm_get_sid(void);
void    qfm_set_name(char *new_name);
char    *qfm_get_name(void);
void    qfm_set_guild_name(char *new_guild_name);
char    *qfm_get_guild_name(void);


/*
 * Change and check player self settings
 */
void    qfms_enable(DWORD settings);
void    qfms_disable(DWORD settings);
BOOL    qfms_check(DWORD setting);
void    qfms_set_state(char state);
SLONG   qfms_get_state( void);


/*
 *    Check specify online state
 */
char    qf_get_state(LPUI_QQFRIEND p);
void    qf_set_state(LPUI_QQFRIEND p, char state);


/*
 *    Error function
 */
void    qf_set_error(DWORD error_code);
DWORD   qf_get_error(void);
char    *qf_get_error_str(DWORD error_code);



