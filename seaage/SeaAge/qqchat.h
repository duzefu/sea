/*
 * qqchat.h
 *
 * functions and structures for qq chat
 *
 * Created by Zhang Zhaohui, 2002.12.6
 *
 */

#ifndef        QQCHAT_H_
#define        QQCHAT_H_

#include "mainfun.h"
#include "qqfriend.h"

enum QQ_CHAT_CONST{ QQ_CHAT_MAX_LIST = 1024};

/*
 *    chat message structrue
 */
typedef struct tagQQ_CHAT_MSG QQ_CHAT_MSG, *LPQQ_CHAT_MSG;
struct tagQQ_CHAT_MSG
{
    SLONG            index;
    SLONG            group;
    SLONG            sid;
    char            msg[200];
    QQ_CHAT_MSG        *next;
};


/*
 *    chat message header
 */
typedef struct tagQQ_CHAT
{
    DWORD            group_count[4];
    QQ_CHAT_MSG        *p_myfriend_msg[QF_MY_FRIEND_SIZE];
    QQ_CHAT_MSG        *p_team_friend_msg[QF_TEAM_SIZE];
    QQ_CHAT_MSG        *p_guild_friend_msg[QF_GUILD_SIZE];
    QQ_CHAT_MSG        *p_stranger_msg[QF_STRANGER_SIZE];
}QQ_CHAT, *LPQQ_CHAT;



/*
 *    chat message list by server ID
 */
typedef struct tagQQ_CHAT_LIST QQ_CHAT_LIST, *LPQQ_CHAT_LIST;
struct tagQQ_CHAT_LIST
{
    QQ_CHAT_MSG     *pmsg;
    QQ_CHAT_LIST *next;
};



/* qq chat init */
SLONG init_qq_chat(void);

/* clear all message */
void  free_qq_chat(void);

/* check if specify friend has message */
//BOOL qq_chat_specify_check(SLONG index, SLONG group);

/* check if specify friend has message by friend server index */
BOOL qq_chat_specify_check_by_sindex(SLONG sid, SLONG group);

/* check if has message */
BOOL  qq_chat_check(void);

/* check if has message in specify group */
BOOL qq_chat_check_group(SLONG group);

/* get first chat message */
//char  *qq_chat_get_chat(SLONG index, SLONG group, DWORD *sid);

/* get first chat message by friend server index */
char  *qq_chat_get_chat_by_sindex(SLONG sid, SLONG group);

/* add message to end of specify friend message list */
SLONG qq_chat_add_chat(SLONG index, SLONG group, SLONG sid,char *message);

/* delete first chat message */
void qq_chat_del_chat(SLONG index, SLONG group);

/* delete specify friend message */
void qq_chat_del_specify_one(SLONG index, SLONG group);

/* clear all message */
void  qq_chat_clear(void);

/* get first chat message */
char *qq_chat_get_first(SLONG *i, SLONG *group, DWORD *sid);

/* move chat message */
SLONG qq_chat_move(SLONG s_index, SLONG s_group, SLONG d_index, SLONG d_group);

#endif        /* QQCHAT_H_ */