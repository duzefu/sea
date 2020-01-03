/*
 * qqchat.cpp
 *
 * functions for qq chat
 *
 * Created by Zhang Zhaohui, 2002.12.6
 *
 */

#include "qqchat.h"
#include "qqfriend.h"

QQ_CHAT         qq_chat;
char            qq_chat_buf[200];
QQ_CHAT_LIST    *qq_list_p = NULL;
QQ_CHAT_MSG     *qq_chat_mem_buf = NULL;
QQ_CHAT_LIST    *qq_chat_list_mem_buf = NULL;

static void         qq_chat_list_free(QQ_CHAT_MSG *p);
static QQ_CHAT_MSG  **qq_chat_get_list(SLONG group);
static SLONG        qq_chat_list_add(QQ_CHAT_MSG *pmsg);
static void         qq_chat_del_first(void);
static void         qq_chat_del_specify( QQ_CHAT_MSG *pmsg);
static QQ_CHAT_MSG  *qq_chat_mem_alloc(void);
static void         qq_chat_mem_free(QQ_CHAT_MSG *p);
static QQ_CHAT_LIST *qq_chat_list_mem_alloc(void);
static void         qq_chat_list_mem_free(QQ_CHAT_LIST *p);

/************************************************************************/
/* Functions                                                            */
/************************************************************************/

/* qq chat init */
SLONG init_qq_chat(void)
{
    qq_chat_mem_buf = (QQ_CHAT_MSG*)GlobalAlloc( GPTR, sizeof(QQ_CHAT_MSG) * QQ_CHAT_MAX_LIST );
    if (!qq_chat_mem_buf)
    {
        log_error(1, "Error: alloc memory failed (chat)");
        return TTN_NOT_OK;
    }

    qq_chat_list_mem_buf = (QQ_CHAT_LIST*)GlobalAlloc( GPTR, sizeof(QQ_CHAT_LIST) * QQ_CHAT_MAX_LIST );

    if (!qq_chat_list_mem_buf)
    {
        log_error(1, "Error: alloc memory failed(chat2)");
        return TTN_NOT_OK;
    }
    ZeroMemory(&qq_chat, sizeof(QQ_CHAT));
    qq_list_p = NULL;

    return TTN_OK;
}

/* clear all message */
void  free_qq_chat(void)
{
//  qq_chat_clear();
    ZeroMemory(&qq_chat, sizeof(QQ_CHAT));
    qq_list_p = NULL;

    GlobalFree( qq_chat_mem_buf );
    qq_chat_mem_buf = NULL;

    GlobalFree( qq_chat_list_mem_buf );
    qq_chat_list_mem_buf = NULL;
    
}

/* check if specify friend has message */
BOOL  qq_chat_specify_check(SLONG index, SLONG group)
{
    QQ_CHAT_MSG **p;
    BOOL    result = FALSE;
    p = qq_chat_get_list(group);
    if (p)
    {
        result = (NULL != p[index]);
    }
    return result;
}

/* check if specify friend has message by friend server index */
BOOL qq_chat_specify_check_by_sindex(SLONG sid, SLONG group)
{
    QQ_CHAT_MSG **p;
    SLONG count, i;
    BOOL    result = FALSE;

    p = qq_chat_get_list(group);
    if (p)
    {
        count = qfl_max_count(group);

        for( i = 0; i < count; i++)
        {
            if (p[i])
            {
                if ( p[i]->sid == sid)
                {
                    result = TRUE;
                    break;
                }
            }
        }
    }
    return result;
}

/* check if has message */
BOOL  qq_chat_check(void)
{
    return (NULL != qq_list_p);
}

/* check if has message in specify group */
BOOL qq_chat_check_group(SLONG group)
{
    if (group >= QQ_MY_FRIENDS && group <= QQ_STRANGERS)
        return (qq_chat.group_count[group-QQ_MY_FRIENDS]);
    else
        return FALSE;
}


/* get first chat message */
char  *qq_chat_get_chat(SLONG index, SLONG group, DWORD *sid)
{
    QQ_CHAT_MSG **pp;
    char *result;
    pp = qq_chat_get_list(group);
    if (pp && pp[index])
    {
        result = pp[index]->msg;
        *sid = pp[index]->sid;
    }
    return result;
}

/* get first chat message */
char  *qq_chat_get_chat_by_sindex(SLONG sid, SLONG group)
{
    QQ_CHAT_MSG **p;
    SLONG count, i;
    char    *result = NULL;
    
    p = qq_chat_get_list(group);
    if (p)
    {
        count = qfl_max_count(group);
        
        for( i = 0; i < count; i++)
        {
            if (p[i])
            {
                if ( p[i]->sid == sid)
                {
                    result = p[i]->msg;
                    break;
                }
            }
        }
    }
    return result;
}

/* add message to end of specify friend message list */
SLONG qq_chat_add_chat(SLONG index, SLONG group, SLONG sid,char *message)
{
    QQ_CHAT_MSG *p;
    QQ_CHAT_MSG *tp1, *tp2;
    QQ_CHAT_MSG **pp;
    UI_QQFRIEND *pf;
    
    pp = qq_chat_get_list(group);

    if (pp)
    {
        p = qq_chat_mem_alloc();
        if (NULL == p)
            return TTN_NOT_OK;

        if (pp[index])
        {
            for( tp1 = pp[index]; tp1 != NULL; tp1 = tp1->next)
                tp2 = tp1;
            tp2->next = p;
        }
        else
        {
            pp[index] = p;
        }

        pf = qf_get(index, group);
        if (pf)
        {
            p->sid = pf->sid;
        }

        lstrcpyn((LPSTR)p->msg, (LPCSTR)message, 200);
        p->index = index;
        p->group = group;
        p->next  = NULL;

        qq_chat_list_add(p);

        qq_chat.group_count[group-QQ_MY_FRIENDS]++;

        return TTN_OK;
    }

    return TTN_NOT_OK;
}

/* delete first chat message in specify friend */
void qq_chat_del_chat(SLONG index, SLONG group)
{
    QQ_CHAT_MSG **pp;
    QQ_CHAT_MSG *p;
    pp = qq_chat_get_list(group);

    if (pp)
    {
        if (pp[index])
        {
            p = pp[index];
            pp[index] = pp[index]->next;
            qq_chat_del_specify(p);
            qq_chat_mem_free(p);

            qq_chat.group_count[group - QQ_MY_FRIENDS]--;
            
        }
    }
}

/* clear all message */
void  qq_chat_clear(void)
{
    SLONG i;
    QQ_CHAT_MSG **p;
    SLONG n;

    p = qq_chat.p_myfriend_msg;
    n = qfl_count(QQ_MY_FRIENDS);
    for ( i = 0; i < n; i++)
    {
        if (p[i])
            qq_chat_list_free(p[i]);
        p[i] = NULL;
    }
        
    p = qq_chat.p_team_friend_msg;
    n = qfl_count(QQ_TEAM_PLAYERS);
    for ( i = 0; i < n; i++)
    {
        if (p[i])
            qq_chat_list_free(p[i]);
        p[i] = NULL;
    }

    p = qq_chat.p_guild_friend_msg;
    n = qfl_count(QQ_GUILD_PLAYERS);
    for ( i = 0; i < n; i++)
    {
        if (p[i])
            qq_chat_list_free(p[i]);
        p[i] = NULL;
    }

    p = qq_chat.p_stranger_msg;
    n = qfl_count(QQ_STRANGERS);
    for ( i = 0; i < n; i++)
    {
        if (p[i])
            qq_chat_list_free(p[i]);
        p[i] = NULL;
    }
}


/* get first chat message */
char *qq_chat_get_first(SLONG *index, SLONG *group, DWORD *sid)
{
    char *result = NULL;

    if (qq_list_p)
    {
        *index = qq_list_p->pmsg->index;
        *group = qq_list_p->pmsg->group;
        *sid = qq_list_p->pmsg->sid;
        result = qq_list_p->pmsg->msg;

        lstrcpyn((LPSTR)qq_chat_buf, (LPCSTR)result, 200);
        qq_chat_del_chat(*index, *group);
        qq_chat_del_first();

        result = qq_chat_buf;
    }

    return result;
}

SLONG qq_chat_move(SLONG s_index, SLONG s_group, SLONG d_index, SLONG d_group)
{
    QQ_CHAT_MSG **pp, *p;

    pp = qq_chat_get_list(s_group);
    
    if (!pp)
        return TTN_NOT_OK;
    
    p = pp[s_index];

    while (p)
    {
        p->group = d_group;
        p->index = d_index;
        qq_chat_add_chat(d_index, d_group, p->sid, p->msg);
        qq_chat_del_chat(s_index, s_group);
        p = pp[s_index];
    }
    return TTN_OK;
}

void qq_chat_del_specify_one(SLONG index, SLONG group)
{
    QQ_CHAT_MSG **pp, *p;
    
    pp = qq_chat_get_list(group);
    
    if (!pp)
        return;
    
    p = pp[index];
    
    while (p)
    {
        qq_chat_del_chat(index, group);
        p = pp[index];
    }
}
/************************************************************************/
/* static function                                                      */
/************************************************************************/
void qq_chat_list_free(QQ_CHAT_MSG *p)
{
    QQ_CHAT_MSG *tmp_p;

    while (p)
    {
        tmp_p = p;
        p = tmp_p->next;
        qq_chat_mem_free(tmp_p);

    }
}

QQ_CHAT_MSG **qq_chat_get_list(SLONG group)
{
    QQ_CHAT_MSG **result;
    switch (group)
    {
    case QQ_MY_FRIENDS:
        result = qq_chat.p_myfriend_msg;
        break;
    case QQ_TEAM_PLAYERS:
        result = qq_chat.p_team_friend_msg;
        break;
    case QQ_GUILD_PLAYERS:
        result = qq_chat.p_guild_friend_msg;
        break;
    case QQ_STRANGERS:
        result = qq_chat.p_stranger_msg;
        break;
    default:
        result = NULL;
        break;
    }
    return result;
}

SLONG qq_chat_list_add(QQ_CHAT_MSG *pmsg)
{
    QQ_CHAT_LIST *tp1;
    QQ_CHAT_LIST *p_new;

    p_new = qq_chat_list_mem_alloc();
    if (!p_new)
        return TTN_NOT_OK;

    if (!qq_list_p)
    {
        qq_list_p = p_new;
        qq_list_p->next = NULL;
        p_new->pmsg = pmsg;
    }
    else
    {
        for (tp1 = qq_list_p; tp1->next != NULL; tp1 = tp1->next)
            ;
        tp1->next = p_new;
        p_new->next = NULL;
        p_new->pmsg = pmsg;
    }
    return TTN_OK;
}

void qq_chat_del_first(void)
{
    QQ_CHAT_LIST *p_first;
    p_first = qq_list_p;

    if (qq_list_p)
    {
        qq_list_p = qq_list_p->next;
        qq_chat_list_mem_free(p_first);
    }
}

void qq_chat_del_specify( QQ_CHAT_MSG *pmsg)
{
    QQ_CHAT_LIST *p, *op;

    if ( pmsg == qq_list_p->pmsg )
    {
        p = qq_list_p;
        qq_list_p = qq_list_p->next;
        qq_chat_list_mem_free(p);
    }
    else
    {
        p = qq_list_p;
        
        while (p)
        {
            if (p->pmsg == pmsg)
                break;

            op = p;
            p = p->next;
        }


        if (!p)         // Not found
            return;

        op->next = p->next;
        qq_chat_list_mem_free(p);
    }
}

QQ_CHAT_MSG  *qq_chat_mem_alloc(void)
{
    SLONG i;
    QQ_CHAT_MSG *result;

    if (!qq_chat_mem_buf)
        result = NULL;
    else
    {
        for (i = 0; i < QQ_CHAT_MAX_LIST; i++)
        {
            if (qq_chat_mem_buf[i].sid == 0)
            {
                result = &qq_chat_mem_buf[i];
                break;
            }
        }
    }
    
    return result;
}


void qq_chat_mem_free(QQ_CHAT_MSG *p)
{
    if (qq_chat_mem_buf)
    {
        if ( p >= qq_chat_mem_buf && 
            p <= qq_chat_mem_buf + sizeof(QQ_CHAT_MSG)*( QQ_CHAT_MAX_LIST - 1) )
        {
            qq_chat_mem_buf[(p - qq_chat_mem_buf)/sizeof(QQ_CHAT_MSG)].sid = 0;
            qq_chat_mem_buf[(p - qq_chat_mem_buf)/sizeof(QQ_CHAT_MSG)].next = NULL;
        }
    }
}

QQ_CHAT_LIST *qq_chat_list_mem_alloc(void)
{
    SLONG i;
    QQ_CHAT_LIST *result;
    
    if (!qq_chat_list_mem_buf)
        result = NULL;
    else
    {
        for (i = 0; i < QQ_CHAT_MAX_LIST; i++)
        {
            if (qq_chat_list_mem_buf[i].pmsg == NULL)
            {
                result = &qq_chat_list_mem_buf[i];
                break;
            }
        }
    }
    
    return result;
}

void qq_chat_list_mem_free(QQ_CHAT_LIST *p)
{
    if (qq_chat_list_mem_buf)
    {
        if ( p >= qq_chat_list_mem_buf && 
            p <= qq_chat_list_mem_buf + sizeof(QQ_CHAT_LIST)*( QQ_CHAT_MAX_LIST - 1) )
        {
            qq_chat_list_mem_buf[(p - qq_chat_list_mem_buf)/sizeof(QQ_CHAT_LIST)].pmsg = NULL;
            qq_chat_list_mem_buf[(p - qq_chat_list_mem_buf)/sizeof(QQ_CHAT_LIST)].next = NULL;
        }
    }
}
