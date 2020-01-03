/*
 * qqfriend.cpp
 * functions for qq friend list
 *
 * Created by Zhang Zhaohui, 2002.10.31
 *
 */
#include "NetGE_MainFunc.h"
#include "PosData.h"
#include "qqmain.h"


#define QF_MAX_ERROR_CODE        4

/* error code, get it by qf_get_error() */
enum QF_ERROR_CODE{
    QF_SUCCESS,
    QF_ALREADY_ADDED,
    QF_MAX_COUNT,
    QF_NO_ENOUGH_MEM,
};

/* error string */
char *qf_error_str[QF_MAX_ERROR_CODE] =
{
    QQERR_SUCCESS,
    QQERR_QF_ALREADY_ADDED,
    QQERR_QF_MAX_COUNT,
    QQERR_NO_ENOUGH_MEM,
};

/* Stores player information */
UI_QQFRIEND     g_qf_self;

/* Friends infomation buffer, include Header and all kinds of friend list */
char            *gp_qf_buf = NULL;

/* Friend list header, it's a first part in gp_qf_buf. */
UI_QF_MAIN        *gp_qf_main = NULL;

/* Friend information start postion in gp_qf_buf */
UI_QF_LIST        *gp_qf_start = NULL;

/* Friend function error code */
DWORD            qf_error_code = 0;

char error_str[] = "";

/*
 * Alloc memory for friend buffer and Initialize global pointer.
 */
SLONG init_qf(void)
{
    DWORD size, total_item;

    /* calculate buffer size */
    total_item = QF_MY_FRIEND_SIZE + QF_TEAM_SIZE + QF_GUILD_SIZE + 
                    QF_STRANGER_SIZE;
    size = sizeof(UI_QF_LIST)*total_item + sizeof(UI_QF_MAIN);

    /* alloc memory */
    gp_qf_buf = (char*)GlobalAlloc(GPTR, size);
    if (!gp_qf_buf)
    {
        log_error(1, "Error: Can not alloc memory for qq friend!");
        return TTN_NOT_OK;
    }

    /* Initialize global pointer */
    gp_qf_main = (LPUI_QF_MAIN)gp_qf_buf;
    gp_qf_start = (LPUI_QF_LIST)(gp_qf_buf + sizeof(UI_QF_MAIN));


    // ZZH, Get player info from server [2002.12.17 16:16]
    /* Get player information */
    //qfm_get_info();

    return TTN_OK;
}


/*
 *  Free friend buffer, and set global variable to zero
 */
void free_qf(void)
{
    if (gp_qf_buf)
    {
        GlobalFree(gp_qf_buf);
        gp_qf_buf = NULL;
    }

    gp_qf_main = NULL;
    gp_qf_start = NULL;
}



/*
 * Create a friend structure
 */
UI_QQFRIEND *qf_new(void)
{
    LPUI_QQFRIEND p_qf = NULL;

    p_qf = (LPUI_QQFRIEND)GlobalAlloc(LPTR, sizeof(UI_QQFRIEND));
    if (!p_qf)
    {
        log_error(1, "ERROR: Can not alloc memory for qq_friend.");
        return NULL;
    }

    return p_qf;
}


/*
 * Free a friend structure
 */
void qf_free(LPUI_QQFRIEND p_qf)
{
    if (p_qf)
    {
        GlobalFree(p_qf);
    }
}


/*
 * Add a friend (p_qf) to specify friend group (qfg)
 *
 *      TODO: ...
 */
SLONG qf_add(LPUI_QQFRIEND p_qf, SLONG qfg)
{
    LPUI_QF_LIST    p;
    LPUI_QF_LIST    new_plist;
    SLONG           count;
    SLONG            *pcount;
//    SLONG            tmp_group;

    if (!gp_qf_main)
    {
        log_error(1, "Error: add_qq_friend() function needs be init.");
        return TTN_NOT_OK;
    }

    if (!p_qf)
        return TTN_NOT_OK;

    /* check if max friends in friend group */
    pcount = qfl_pcount(qfg);
    count = qfl_count(qfg);
    if (count >= qfl_max_count(qfg))
    {
        qf_set_error(QF_MAX_COUNT);
        log_error(1, "Error: max friends list!");
        return TTN_NOT_OK;
    }

    /* check if friend already added */

/* Do not need check if friend already here
    tmp_group = qf_get_group_by_name((char*)p_qf->name);
    if (tmp_group == QQ_STRANGERS)
    {
        qf_delete(qf_get_index_by_name((char*)p_qf->name, tmp_group), tmp_group);
    }
    else if(tmp_group != -1)
    {
        qf_set_error(QF_ALREADY_ADDED);
        log_error(1, "Error: friend already in friend list.");
        return TTN_NOT_OK;
    }
*/

    /* find empty block in friend buffer */
    new_plist = NULL;
    new_plist = qfl_get_empty();
    if (!new_plist)
    {
        log_error(1, "Error: No enough space for new friend.");
        qf_set_error(QF_NO_ENOUGH_MEM);
        return TTN_NOT_OK;
    }
    
    /* Insert the new friend in the first of group list */
    switch  (qfg)
    {
        case QQ_MY_FRIENDS:
            p = gp_qf_main->pmy_friends;
            gp_qf_main->pmy_friends = new_plist;
            break;
        case QQ_TEAM_PLAYERS:
            p = gp_qf_main->pteam_players;
            gp_qf_main->pteam_players = new_plist;
            break;
        case QQ_GUILD_PLAYERS:
            p = gp_qf_main->pguild_players;
            gp_qf_main->pguild_players = new_plist;
            break;
        case QQ_STRANGERS:
            p = gp_qf_main->pstrangers;
            gp_qf_main->pstrangers = new_plist;
            break;
        case QQ_UNDESIREDERS:
            p = gp_qf_main->pundesireders;
            gp_qf_main->pundesireders = new_plist;
            break;
        default:
            log_error(1,"Error:Unknow group ID.\n");
            return TTN_NOT_OK;
    }
    new_plist->next = p;
    memcpy(&new_plist->friend_info, p_qf, sizeof(UI_QQFRIEND));
    (*pcount)++;
    qfl_sort( qfg );
    return TTN_OK;
}


/*
 *  Delete a friend by friend index in specify friend group (qfg)
 */
SLONG qf_delete(SLONG index, SLONG qfg)
{
    LPUI_QF_LIST   *op;
    LPUI_QF_LIST   p;
    LPUI_QQFRIEND  pqf;
    SLONG        *pcount;
    void         **last_p;

    op = qfl_get_header_pointer(qfg);
    if (op == NULL)
        return TTN_NOT_OK;

    pcount = qfl_pcount(qfg);
    if (*pcount <= 0)
        return TTN_NOT_OK;


    pqf = qf_get(index, qfg);
    if (!pqf)
        return TTN_NOT_OK;
    

    /* last_p stores a pointer pointed to next pointer of friend list,
     * If found specify friend list, last_p stroes the address of next 
     * pointer in last friend list, change its content to next pointer
     * of current friend list, so we can remove the specify friend from 
     * friend list chain.*/
    p = *op;
    last_p = (void**)op;
    
    while (&p->friend_info != pqf)
    {
        last_p = (void**)&p->next;
        p = p->next;
        if(!p)
            return TTN_NOT_OK;
    }
    *last_p = p->next;

    /* Clear memory of specify friend by zero */
    ZeroMemory(p, sizeof(UI_QF_LIST));
    (*pcount)--;
    return TTN_OK;
}


/*
 *  Get specify friend (p_qf) index in friend group (qfg)
 */
SLONG qf_get_index(LPUI_QQFRIEND p_qf, SLONG qfg)
{
    LPUI_QF_LIST p;
    SLONG result;

    if (!p_qf)
        return -1;

    p = qfl_get(0, qfg);

    /* Index start from 0 */
    result = 0;
    while (&p->friend_info != p_qf)
    {
        p = p->next;
        if (!p)
            return -1;
        result++;
    }
    
    return result;
}


/*
 *    Return friend group by friend main name
 */
// TODO: 函數效率太低，需後期優化
SLONG    qf_get_group_by_name(char *name)
{
    SLONG result = -1;
    
    if (qf_get_index_by_name(name, QQ_MY_FRIENDS) >= 0)
        result = QQ_MY_FRIENDS;
    else if (qf_get_index_by_name(name, QQ_TEAM_PLAYERS) >= 0)
        result = QQ_TEAM_PLAYERS;
    else if (qf_get_index_by_name(name, QQ_GUILD_PLAYERS) >= 0)
        result = QQ_GUILD_PLAYERS;
    else if (qf_get_index_by_name(name, QQ_STRANGERS) >= 0)
        result = QQ_STRANGERS;
    else if (qf_get_index_by_name(name, QQ_UNDESIREDERS) >= 0)
        result = QQ_UNDESIREDERS;
    
    return result;
}


/*
 *    Return friend index by friend main name
 */
SLONG qf_get_index_by_name(char *name, SLONG qfg)
{
    UI_QF_LIST *p;
    SLONG result = -1;

    for(p = qfl_get_header(qfg); p != NULL; p = p->next)
    {
        result ++;
        if (CSTR_EQUAL == CompareString(LOCALE_SYSTEM_DEFAULT, 0,
                                        (LPCSTR)name, -1,
                                        (LPCSTR)p->friend_info.name, -1))
            break;
    }
    if (!p)
        result = -1;
    return result;
}


/*
 *  Get a friend by friend index in friend group (qfg)
 */
UI_QQFRIEND *qf_get(SLONG index, SLONG qfg)
{
    LPUI_QF_LIST p;

    if( index >= *qfl_pcount(qfg) || index < 0)
        return NULL;

    /* Get friend list by index*/
    p = qfl_get(index, qfg);

    if(p)
        return &p->friend_info;
    else
        return NULL;
}


/*
 *    Return friend group by friend server ID
 */
// TODO: 函數效率太低，需後期優化
SLONG qf_get_group_by_sid(SLONG sid)
{
    SLONG result = -1;

    if (qf_get_by_sid(sid, QQ_MY_FRIENDS))
        result = QQ_MY_FRIENDS;
    else if (qf_get_by_sid(sid, QQ_TEAM_PLAYERS))
        result = QQ_TEAM_PLAYERS;
    else if (qf_get_by_sid(sid, QQ_GUILD_PLAYERS))
        result = QQ_GUILD_PLAYERS;
    else if (qf_get_by_sid(sid, QQ_STRANGERS))
        result = QQ_STRANGERS;
    else if (qf_get_by_sid(sid, QQ_UNDESIREDERS))
        result = QQ_UNDESIREDERS;
    
    return result;
}

/*
 *    Return friend pointer by friend server ID
 */
UI_QQFRIEND *qf_get_by_sid(DWORD sid, SLONG qfg)
{
    UI_QF_LIST *p;

    for(p = qfl_get_header(qfg); p != NULL; p = p->next)
    {
        if (p->friend_info.sid == sid)
            break;
    }
    if (p)
        return &p->friend_info;
    else
        return NULL;
}

/*
 *    Return friend index by friend server ID
 */
SLONG qf_get_index_by_sid(DWORD sid, SLONG qfg)
{
    UI_QF_LIST *p;
    SLONG result = -1;
    
    for(p = qfl_get_header(qfg); p != NULL; p = p->next)
    {
        result ++;
        if (p->friend_info.sid == sid)
            break;
    }

    if (!p)
        result = -1;

    return result;
}



/*
 *  Set specify settings by TRUE
 */
void qfs_enable(LPUI_QQFRIEND p_qf, DWORD settings)
{
    if (!p_qf)
        return;
    p_qf->settings = p_qf->settings|settings;

}


/*
 *  Set specify settings by FALSE
 */
void qfs_disable(LPUI_QQFRIEND p_qf, DWORD settings)
{
    if (!p_qf)
        return;
    p_qf->settings = p_qf->settings&(~settings);
}


/*
 *  Check specify setting is TRUE or FALSE
 */
BOOL qfs_check(LPUI_QQFRIEND p_qf, DWORD setting)
{
    if (!p_qf)
        return FALSE;
    return (p_qf->settings&setting);
}


/*
 *  Clear all content in friend buffer
 */
void qfl_clear_all(void)
{
    DWORD total_item, size;
    LPUI_QQFRIEND p = NULL;
    DWORD i = 0;

    // 刪除陌生人的消息
    p = qf_get( i, QQ_UNDESIREDERS );
    while ( p )
    {
        ql_del_chat( p->sid );
        p = qf_get( i, QQ_UNDESIREDERS );
    }


    /* calculate buffer size */    
    total_item = QF_MY_FRIEND_SIZE + QF_TEAM_SIZE + QF_GUILD_SIZE + 
                    QF_STRANGER_SIZE;
    size = sizeof(UI_QF_LIST)*total_item + sizeof(UI_QF_MAIN);

    /* Clear memory */
    ZeroMemory(gp_qf_buf, size);
    ZeroMemory(&g_qf_self, sizeof(g_qf_self));
}


/*
 *  Return the pointer of count in specify friend group (qfg)
 */
SLONG *qfl_pcount(SLONG qfg)
{
    SLONG *pcount = NULL;

    switch (qfg)
    {
    case QQ_MY_FRIENDS:
        pcount = &gp_qf_main->nmf_count;
        break;
    case QQ_TEAM_PLAYERS:
        pcount = &gp_qf_main->ntp_count;
        break;
    case QQ_GUILD_PLAYERS:
        pcount = &gp_qf_main->ngp_count;
        break;
    case QQ_STRANGERS:
        pcount = &gp_qf_main->ns_count;
        break;
    case QQ_UNDESIREDERS:
        pcount = &gp_qf_main->nu_count;
        break;
    default:
        log_error(1, "Error: Unknow friend group.\n");
    }
    
    return pcount;
}

/*
 *  Return the pointer of count in specify friend group (qfg)
 */
SLONG    qfl_count(SLONG qfg)
{
    SLONG count = NULL;

    switch (qfg)
    {
    case QQ_UNDESIREDERS:    /* max 256, both MY_FRIENDS and UNDESIREDERS */
    case QQ_MY_FRIENDS:
        count = gp_qf_main->nmf_count + gp_qf_main->nu_count;
        break;
    case QQ_TEAM_PLAYERS:
        count = gp_qf_main->ntp_count;
        break;
    case QQ_GUILD_PLAYERS:
        count = gp_qf_main->ngp_count;
        break;
    case QQ_STRANGERS:
        count = gp_qf_main->ns_count;
        break;
    default:
        log_error(1, "Error: Unknow friend group.\n");
    }
    
    return count;
}
/*
 *    Return online friend count in specify group
 */
SLONG qfl_online_count(SLONG qfg)
{
    SLONG count = 0;
    UI_QF_LIST *p;

    for( p  = qfl_get_header(qfg); p != NULL; p = p->next)
    {
        if ( p->friend_info.state == QF_ONLINE )
            count++;
    }

    return count;
}


/*
 * Return max count in specify friend group (qfg)
 */
SLONG qfl_max_count(SLONG qfg)
{
    SLONG max_count;
    
    switch (qfg)
    {
    case QQ_MY_FRIENDS:
        max_count = QF_MY_FRIEND_SIZE;
        break;
    case QQ_TEAM_PLAYERS:
        max_count = QF_TEAM_SIZE;
        break;
    case QQ_GUILD_PLAYERS:
        max_count = QF_GUILD_SIZE;
        break;
    case QQ_STRANGERS:
        max_count = QF_STRANGER_SIZE;
        break;
    case QQ_UNDESIREDERS:
        max_count = QF_UNDESIREDER_SIZE;
        break;
    default:
        log_error(1, "Error: Unknow friend group.\n");
        max_count = 0;
    }
    return max_count;
}


/*
 *  Get friend list by index in specify firend group (qfg)
 */
UI_QF_LIST *qfl_get(SLONG index, SLONG qfg)
{
    LPUI_QF_LIST p;
    SLONG i;

    p = *qfl_get_header_pointer(qfg);
    
    if (!p)
        return NULL;

    for( i = 0; i < index; i++)
    {
        p = p->next;
        if(!p)
            return NULL;
    }

    return p;
}


/*
 *  Find a empty block in friend list
 */
UI_QF_LIST *qfl_get_empty(void)
{
    SLONG i;
    SLONG total_item;
    LPUI_QF_LIST p;
    
    
    if(gp_qf_start)
    {
        total_item = QF_MY_FRIEND_SIZE + QF_TEAM_SIZE + QF_GUILD_SIZE + 
                       QF_STRANGER_SIZE + QF_UNDESIREDER_SIZE;
        for(i = 0; i < total_item; i++)
        {
            p = &gp_qf_start[i];
            if(p->friend_info.name[0] == '\0')
                return p;
        }
    }
    
    return NULL;
}


/*
 *  Return pointer address of specify friend list header
 */
UI_QF_LIST **qfl_get_header_pointer(SLONG qfg)
{
    LPUI_QF_LIST *pp = NULL;

    switch (qfg)
    {
    case QQ_MY_FRIENDS:
        pp = &gp_qf_main->pmy_friends;
        break;
    case QQ_TEAM_PLAYERS:
        pp = &gp_qf_main->pteam_players;
        break;
    case QQ_GUILD_PLAYERS:
        pp = &gp_qf_main->pguild_players;
        break;
    case QQ_STRANGERS:
        pp = &gp_qf_main->pstrangers;
        break;
    case QQ_UNDESIREDERS:
        pp = &gp_qf_main->pundesireders;
        break;
    default:
        log_error(1, "Error: Unknow friend group.\n");
        break;
    }

    return pp;    
}


/*
 * Return pointer of specify friend list header
 */
UI_QF_LIST *qfl_get_header(SLONG qfg)
{
    UI_QF_LIST **p;

    p = qfl_get_header_pointer(qfg);

    if (p)
        return (*p);
    else
        return NULL;
}


/*
 *  Sort friends by friend name in specify friend group (qfg)
 */
void qfl_sort(SLONG qfg)
{
    SLONG count;
    SLONG l, r;

    count = *qfl_pcount(qfg);

    if (count <= 0)
        return;

    l = 0;
    r = count - 1;
    qfl_qsort(qfg, l, r);
}


/*
 *  Quick sort friend from index l to index r in specify
 *          friend group
 */
void qfl_qsort(SLONG qfg, SLONG l, SLONG r)
{
    LPUI_QQFRIEND p;
    SLONG i, j;

    do
    {
        i = l;
        j = r;
        p = qf_get((l+r)>>1, qfg);

        do
        {
            while(qfl_compare(qf_get(i, qfg), p) < 0)
                i++;
            while(qfl_compare(qf_get(j, qfg), p) > 0)
                j--;
            if(i <= j)
            {
                qfl_swap(i, j, qfg);
                    i++;
                    j--;
            }
        }while(i <= j);
        
        if(l < j)
            qfl_qsort(qfg, l, j);
        
        l = i;
        
    }while(i < r);
}


/*
 *  Compare two friends by friend name
 */
SLONG qfl_compare(LPUI_QQFRIEND p_qfa, LPUI_QQFRIEND p_qfb)
{
    SLONG result, tmp_result;
    BOOL ba, bb;

    ba = ( qf_get_state( p_qfa ) == QF_ONLINE );
    bb = ( qf_get_state( p_qfb ) == QF_ONLINE );

    if(ba && !bb)
        result = -1;
    else if(!ba && bb)
        result = 1;
    else
    {
        /* compare two friends by name */
        tmp_result = CompareString( LOCALE_SYSTEM_DEFAULT, 0,
                                    (LPCSTR)p_qfa->name, -1,
                                    (LPCSTR)p_qfb->name, -1);

        switch (tmp_result)
        {
            case CSTR_LESS_THAN:
                result = -1;
                break;
            case CSTR_GREATER_THAN:
                result = 1;
                break;
            case CSTR_EQUAL:
                result = 0;
                break;
            default:
                result = 0;
                break;
        }
    }

    return result;
}


/*
 *  Swap to friends in specify friend group
 */
SLONG qfl_swap(SLONG i, SLONG j, SLONG qfg)
{
    LPUI_QF_LIST* pi;
    LPUI_QF_LIST* pj;
    LPUI_QF_LIST c;

    
    if(i==0)
        pi = qfl_get_header_pointer(qfg);
    else
        pi = &qfl_get(i-1, qfg)->next;

    if(j==0)
        pj = qfl_get_header_pointer(qfg);
    else
        pj = &qfl_get(j-1, qfg)->next;

    if (!(pi && pj))
        return TTN_NOT_OK;

    /* swap content between pi and pj, also swap the next pointer
     * of content in two pointer. */
    c = *pi;
    *pi = *pj;
    *pj = c;
    c = (*pi)->next;
    (*pi)->next = (*pj)->next;
    (*pj)->next = c;

    return TTN_OK;
}


/*
 *  Save all friends information in local
 */
void qf_save(void)
{
}


/*
 *  Load all friends information from local, 
 *          if not found, load them from server
 */
void qf_load(void)
{
}

/*
 *  Refresh all friends from server
 */
void qf_refresh(void)
{
}


/*
 *  Refresh a specify friend from server
 */
void qf_refresh_specify(LPUI_QQFRIEND p_qf)
{
}


/*
 *  Get player self information
 */
UI_QQFRIEND *qfm_get_info(void)
{
    CHAR *str;
    SLONG career, sex;
    
//    str = GetCharacterAccount(g_lPlayerIndex);
//    strcpy((char*)gp_qf_self.c_Id, (const char*)str);

//    str = (USTR*)get_country_name(GetCharacterCountry(g_lPlayerIndex));
//    strcpy((char*)g_qf_self.country, (const char*)str);
    g_qf_self.country = '\0';

    str = GetCharacterGuildName(g_lPlayerIndex);
    strcpy((char*)g_qf_self.guild_name, (const char*)str);

    str = GetCharacterMainName(g_lPlayerIndex);
    strcpy((char*)g_qf_self.name, (const char*)str);

    str = GetCharacterNickName(g_lPlayerIndex);
    strcpy((char*)g_qf_self.nickname, (const char*)str);

    str = GetCharacterSpouseName(g_lPlayerIndex);
    strcpy((char*)g_qf_self.partner_name, (const char*)str);
    
    g_qf_self.level = GetCharacterLevel(g_lPlayerIndex);

    career = GetCharacterCareer(g_lPlayerIndex);
    sex = GetCharacterLevel(g_lPlayerIndex);
    
    g_qf_self.icon_index = get_character_main_face(career, sex);

    g_qf_self.money = GetCharacterBodyMoney(g_lPlayerIndex);

    g_qf_self.pk = GetCharacterGoodEvil(g_lPlayerIndex);

    /* TODO: get player setting from server*/
    return &g_qf_self;
}

/*
 *    clear player self info
 */
void qfm_clear(void)
{
    ZeroMemory(&g_qf_self, sizeof(UI_QQFRIEND));
    g_qf_self.state = QF_OFFLINE;
}


/*
 *    Set player server index
 */
void qfm_set_sid(DWORD id)
{
    g_qf_self.sid = id;
}

/*
 *    Get player server index
 */
DWORD    qfm_get_sid(void)
{
    return g_qf_self.sid;
}
/*
 *    Set player main name
 */
void qfm_set_name(char *new_name)
{
    if (new_name)
        lstrcpyn(g_qf_self.name, new_name, 32);
}

/*
 *    Get player main name
 */
char *qfm_get_name(void)
{
    return (char*)g_qf_self.name;
}

/*
 *    Set player guild name
 */
void qfm_set_guild_name(char *new_guild_name)
{
    if (new_guild_name)
        lstrcpyn(g_qf_self.name, new_guild_name, 32);
}

/*
 *    Get player guild name
 */
char *qfm_get_guild_name(void)
{
    return (char*)g_qf_self.guild_name;
}


/*
 *  Change player specify settings to TRUE
 */
void qfms_enable(DWORD settings)
{
    g_qf_self.settings = g_qf_self.settings|settings;
}


/*
 *  Change player specify settings to FALSE
 */
void qfms_disable(DWORD settings)
{
    g_qf_self.settings = g_qf_self.settings&(~settings);
}


/*
 * Return player specify setting
 */
BOOL qfms_check(DWORD setting)
{
    return (g_qf_self.settings&setting);
}

/*
 *    Set player self status
 */
void qfms_set_state(char state)
{
    g_qf_self.state = state;
}

/*
 *    Return player self status
 */
SLONG qfms_get_state( void )
{
    return (g_qf_self.state);
}

/*
 *    Return player online status
 */
char qf_get_state(LPUI_QQFRIEND p)
{
    if (p)
        return p->state;
    else
        return QF_OFFLINE;
}

/*
 *    Set player online status
 */
void qf_set_state(LPUI_QQFRIEND p, char state)
{
    if (p)
    {
        p->state = state;
    }
}


/*
 *    set error code
 */
void qf_set_error(DWORD error_code)
{
    qf_error_code = error_code;
}

/*
 *    get error code
 */
DWORD    qf_get_error(void)
{
    return qf_error_code;
}

/*
 *    get error setring by error code
 */
char    *qf_get_error_str(DWORD error_code)
{
    if ( error_code >= 0 && error_code < QF_MAX_ERROR_CODE)
        return qf_error_str[error_code];
    return error_str;    
}