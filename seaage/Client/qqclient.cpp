/*
* qqclient.cpp
* functions for communication between qq server and qq client
* Zhang Zhaohui
* 2002.10.11
*/
#include "NetGE_MainFunc.h"
#include "NetGE_Event_Struct_Def.h"
#include "qqmain.h"
#include "Client_SendMsg.h"
#include "Client_RecvMsg.h"
#include "qqlog.h"

#define MAX_ADD_LIST 100

/************************************************************************/
/* Send message to server                                               */
/************************************************************************/
/* send get player self information message */
SLONG qq_client_request_mydata(void)
{
    if (SEND_MSG_OK != ClientRequestQQMyData())
    {
        log_error(1, "Error: Send request player self information message failed.");
        return TTN_NOT_OK;
    }
    return TTN_OK;
}

/* send get player friends message */
SLONG qq_client_request_friend_list(void)
{
    if (SEND_MSG_OK != ClientRequestQQFriendList(BEGIN))
    {
        log_error(1, "Error: Send get friends message failed.");
        return TTN_NOT_OK;
    }
    return TTN_OK;
}

/* send get player guild friends message */
SLONG qq_client_request_guild_friend_list(void)
{
    if (SEND_MSG_OK != ClientRequestQQGuildFriendList(BEGIN))
    {
        log_error(1, "Error: Send get guild friends message failed.");
        return TTN_NOT_OK;
    }
    return TTN_OK;
}

/* send get team friends message */
SLONG qq_client_request_team_list(void)
{
    if (SEND_MSG_OK != ClientRequestQQTeamFriendList(BEGIN))
    {
        log_error(1, "Error: Send request team friends message failed.");
        return TTN_NOT_OK;
    }
    return TTN_OK;
}

/* update  player online/offline status */
SLONG qq_client_set_mystate(char State)
{
    if (SEND_MSG_OK != ClientRequestQQSetMyState(State))
    {
        log_error(1, "Error: Send set my state failed.");
        return TTN_NOT_OK;
    }
    return TTN_OK;
}

/* update player self settings */
SLONG qq_client_set_myconfig(DWORD Settings)
{
    if (SEND_MSG_OK != ClientRequestQQSetMyConfig(Settings))
    {
        log_error(1, "Error: Send get player self settings message failed.");
        return TTN_NOT_OK;
    }
    return TTN_OK;
}

/* send get specify friend information */
SLONG qq_client_request_query_someone(DWORD ID)
{
    if (SEND_MSG_OK != ClientRequestQQQuerySomeone(ID))
    {
        log_error(1, "Error: Send search message failed.");
        return TTN_NOT_OK;
    }
    return TTN_OK;
}

/* send search message */
SLONG qq_client_request_query_add_list(UI_QQSEARCH_FILTER *p_filter)
{
    // Jack, TODO [1/3/2003]
    /*
    TPOS_QQ_QD    QueryAddCondition;

    if (!p_filter)
        return TTN_NOT_OK;

    ZeroMemory( &QueryAddCondition, sizeof(TPOS_QQ_QD));

    lstrcpyn(QueryAddCondition.MainName, (LPCTSTR)p_filter->name, 32);
    lstrcpyn(QueryAddCondition.NickName, (LPCTSTR)p_filter->nickname, 32);
    lstrcpyn(QueryAddCondition.Guild,    (LPCTSTR)p_filter->guild_name, 32);
    QueryAddCondition.Country = p_filter->country;
    QueryAddCondition.Level = p_filter->level;
    
    QueryAddCondition.Index = qq_search_get_index();
    
    if (SEND_MSG_OK != PosQQRequestQueryAddList(&QueryAddCondition))
    {
        log_error(1, "Error: Send request add query list message failed.");
        return TTN_NOT_OK;
    }
    */
    return TTN_OK;
}

SLONG qq_client_request_query_online_addlist( void )
{
    
    DWORD Index = qq_search_get_index();

    if ( SEND_MSG_OK != ClientRequestQQQueryOnlineAddList( Index ) )
    {
        log_error(1, "Error: Send request query add online list message failed.");
        return TTN_NOT_OK;
    }

    return TTN_OK;
}

/* send add friend message*/
SLONG qq_client_request_add_someone(DWORD ID, UCHAR relation )
{
    if (SEND_MSG_OK != ClientRequestQQAddSomeone(ID, relation ))
    {
        log_error(1, "Error: Send add friend request failed.");
        return TTN_NOT_OK;
    }
    return TTN_OK;
}

/* send delete friend request */
SLONG qq_client_request_del_friend(DWORD ID)
{
    if (SEND_MSG_OK != ClientRequestQQDeleteFriend(ID))
    {
        log_error(1, "Error: Send delete friend request failed.");
        return TTN_NOT_OK;
    }
    return TTN_OK;
}

/* send delete guild friend request */
SLONG qq_client_request_del_guild_friend(DWORD ID)
{
    if (SEND_MSG_OK != ClientRequestQQDeleteGuildFriend(ID) )
    {
        log_error(1, "Error: Send delete guild friend request failed.");
        return TTN_NOT_OK;
    }

    return TTN_OK;
}

/* send get total players number message */
SLONG qq_client_request_player_count(void)
{
    if (SEND_MSG_OK != ClientRequestQQPlayerCount())
    {
        log_error(1, "Error: Send get total player number message failed.");
        return TTN_NOT_OK;
    }
    return TTN_OK;
}

/* send chat text to one player */
SLONG qq_client_qq_send_2one_msg(DWORD ID, char *p_text)
{
    if (SEND_MSG_OK != ClientRequestQQSendMessageToSomeone(ID, p_text))
    {
        log_error(1, "Error: Send chat message failed.");
        return TTN_NOT_OK;
    }
    return TTN_OK;
}

/* send chat text to multiplayer */
SLONG qq_client_qq_send_2some_msg(DWORD size, DWORD *p_ID, char *p_text)
{
    // Jack, TODO [1/3/2003]
    /*
    TPOS_QQ_SEND_2SOME_MSG SendMse2Some;
    DWORD i;

    size = min(size, 50);

    for (i = 0; i < size; i++)
        SendMse2Some.RecvID[i] = p_ID[i];

    if (p_text)
        lstrcpyn(SendMse2Some.Msg, p_text, 200);
    else
        return TTN_NOT_OK;

    if (SEND_MSG_OK != PosQQSendMsg2Some(&SendMse2Some))
    {
        log_error(1, "Error: Send chat message to multiplayer failed.");
        return TTN_NOT_OK;
    }
    */

    return TTN_OK;
}

SLONG qq_client_request_hit_trans_item( char r_l, UCHAR index )
{
    if ( SEND_MSG_OK != ClientRequestQQHitTransItem( r_l, index ) )
    {
        log_error( 1, "Error: Request hit transfer item failed." );
        return TTN_NOT_OK;
    }
    return TTN_OK;
}

SLONG qq_client_request_transfer_item( DWORD ID )
{
    if ( SEND_MSG_OK != ClientRequestQQTransferItem( ID ) )
    {
        log_error( 1, "Error: Request transfer item failed.");
        return TTN_NOT_OK;
    }
    return TTN_OK;
}

/************************************************************************/
/* receive message from server                                          */
/************************************************************************/

SLONG    client_handle_qq_player_login(DWORD wParam)
{
#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    QQ_PLAYER_LOGIN");
#endif//DEBUG_MSG
    return    0;
}

SLONG    client_handle_qq_login_ok(DWORD wParam)
{
#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    QQ_PLAYER_LOGIN_OK");
#endif//DEBUG_MSG
    qq_client_request_mydata();
    return    0;
}


SLONG    client_handle_qq_player_logout(DWORD wParam)
{
    qq_clear();
    return    0;
}


SLONG    client_handle_qq_get_mydata(DWORD wParam)
{

    TPOS_EVENT_QQGETMYDATA *QQMydata;

    QQMydata = (TPOS_EVENT_QQGETMYDATA*)wParam;

    qq_clear();

    qfm_set_sid( QQMydata->ID );
    qfm_set_name( QQMydata->CharacterName );
    qfm_set_guild_name( QQMydata->GuildName );
    qfms_enable( QQMydata->Config );
    qfms_disable( ~QQMydata->Config );
    qfms_set_state( QQMydata->State );

#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    QQ_GET_MYDATA(ID %d, MainName: %s)",
                    QQMydata->ID, QQMydata->CharacterName);
#endif//DEBUG_MSG

    return    0;
}


/* get player self settings*/
SLONG    client_handle_qq_get_myconfig(DWORD wParam)
{
    // Jack, TODO [1/3/2003]
    /*
    DWORD settings;
    
    if (SEND_MSG_OK != PosQQGetMyConfig(settings))
    {
        log_error(1, "Error: get player self settings failed.");
        return    -1;
    }

    qfms_enable(settings);
    qfms_disable(~settings);

    if (qfms_check(HIDE_LOGIN))
        qq_client_set_mystate(QF_HIDE);
    else
        qq_client_set_mystate(QF_ONLINE);
    
#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    QQ_GET_MYCONFIG: %x", settings);
#endif//DEBUG_MSG
    */

    qq_client_request_friend_list();

    return    0;
}


/* handle player login failed message */
SLONG    client_handle_qq_login_fail(DWORD wParam)
{
    //TODO: ADD PLAYER LOGIN FAILED CODE
    return    0;
}


/* get player friend list */
SLONG    client_handle_qq_get_friend_list(DWORD wParam)
{
    SLONG result = TTN_OK;
    TPOS_EVENT_QQGETFRIENDLIST *QQFriendList;
    UI_QQFRIEND        f;
    SLONG i, max_i;
    

    QQFriendList = (TPOS_EVENT_QQGETFRIENDLIST *)wParam;

    ZeroMemory(&f, sizeof(UI_QQFRIEND));

    if ( QQFriendList->BookMark == 1 )
    {
        i = 0;
        max_i = 128;
    }
    else if ( QQFriendList->BookMark == 2 )
    {
        i = 128;
        max_i = 256;
    }
    else
    {
        log_error(1, "Error: Bad BookMark on receive player friend list.");
        return TTN_NOT_OK;
    }
    
    for ( ; i < max_i; i++ )
    {
        if ( !QQFriendList->FriendList[i].ID )
            continue;

        f.sid  = QQFriendList->FriendList[i].ID;
        f.icon_index = QQFriendList->FriendList[i].Career - 1;
        f.state         = QQFriendList->FriendList[i].State;
        lstrcpyn( f.name, QQFriendList->FriendList[i].MainName, 32 );

#ifdef  DEBUG_MSG
        log_encrypt_message(1, "    QQ_GET_FRIEND_LIST( Friend ID: %d, Friend Name: %s)", 
            f.sid, f.name);
#endif//DEBUG_MSG        
        
        switch ( QQFriendList->FriendList[i].Relation )
        {
        case 0:
            qf_add(&f, QQ_MY_FRIENDS);
            break;
        case 1:
            qf_add(&f, QQ_UNDESIREDERS);
            break;
        default:
            log_error(1, "Error: Bad friend group on receive player friend list.");
            break;
        }
    }


    return    result;
}


/* get guild friend list */
SLONG    client_handle_qq_get_guild_friend_list(DWORD wParam)
{
    SLONG result = TTN_OK;
    TPOS_EVENT_QQGETGUILDFRIENDLIST *QQGuildFriendList;
    UI_QQFRIEND        f;
    SLONG i;


    QQGuildFriendList = (TPOS_EVENT_QQGETGUILDFRIENDLIST*)wParam;

    for ( i = 0; i < QF_GUILD_SIZE; i++ )
    {
        if ( !QQGuildFriendList->GuildFriendList[i].ID )
            continue;

        ZeroMemory(&f, sizeof(UI_QQFRIEND));
        
        f.sid  = QQGuildFriendList->GuildFriendList[i].ID;
        f.icon_index = QQGuildFriendList->GuildFriendList[i].Career - 1;
        f.state         = QQGuildFriendList->GuildFriendList[i].State;

        lstrcpyn(f.name, QQGuildFriendList->GuildFriendList[i].MainName, 32);

#ifdef  DEBUG_MSG
        log_encrypt_message(1, "    QQ_GET_GUILD_FRIEND_LIST( Friend ID: %d, Friend Name: %s)", 
                    QQGuildFriendList->GuildFriendList[i].ID, QQGuildFriendList->GuildFriendList[i].MainName );
#endif//DEBUG_MSG
        
        qf_add(&f, QQ_GUILD_PLAYERS);
        
    }
    
    
    result = ClientRequestLoginZone(g_szPlayerZone);
    ql_on_login();

    return    result;
}


/* get current team friends information */
SLONG    client_handle_qq_get_team_list(DWORD wParam)
{
    // Jack, TODO [1/3/2003]
    /*
    TPOS_QQ_FRIEND    Team;
    UI_QQFRIEND        f;
    int    v;

    //0 for End Team List.
    v = PosQQGetTeamList(&Team);
    if (END == v)
    {
    }
    else if ( v == SEND_MSG_OK )
    {
        ZeroMemory(&f, sizeof(UI_QQFRIEND));

        f.sid  = Team.ID;
        f.icon_index = Team.Career - 1;
        f.state         = Team.State;

        lstrcpyn(f.name, Team.MainName, 32);

        qf_add(&f, QQ_TEAM_PLAYERS);
    }

#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    QQ_GET_TEAM_LIST( Friend ID: %d, Friend Name: %s)", 
            f.sid, f.name);

#endif//DEBUG_MSG
    */

    return    0;
}


/* get myself online/offline status */
SLONG    client_handle_qq_get_mystate(DWORD wParam)
{
    // Jack, TODO [1/3/2003]
    /*
    char state;
    
    if (SEND_MSG_OK != PosQQGetMyState(&state))
    {
        log_error(1, "Error: Receive player state failed.");
        return -1;
    }
    
    qfms_set_state(state);

#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    QQ_GET_MYSTATE: %x", state);
#endif//DEBUG_MSG
    */

    return    0;
}


/* get other friend online/offline status */
SLONG    client_handle_qq_get_otherstate(DWORD wParam)
{
    SLONG result = TTN_OK;
    POS_EVENT_QQREQUESTSETMYSTATE *QQState;
    SLONG group;
    UI_QQFRIEND *p;

    QQState = (POS_EVENT_QQREQUESTSETMYSTATE *)wParam;

    group = qf_get_group_by_sid( QQState->ID );
    if (NULL != ( p = qf_get_by_sid( QQState->ID, group ) ) )
    {
        qf_set_state( p, QQState->State );
        qfl_sort( group );
    }
    else
        result = TTN_NOT_OK;
    
#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    QQ_GET_OTHERSTATE(ID %d)", QQState->ID );
#endif//DEBUG_MSG
    
    return    result;
}


/* get specify friend information */
SLONG    client_handle_qq_get_query_someone(DWORD wParam)
{
    TPOS_EVENT_QQGETQUERYSOMEONE *QQueryData;
    SLONG group;
    UI_QQFRIEND *p = NULL;

    QQueryData = (TPOS_EVENT_QQGETQUERYSOMEONE *)wParam;
    
    if ( -1 != ( group = qf_get_group_by_sid(QQueryData->ID) ) )
    {
        if ( NULL == ( p = qf_get_by_sid(QQueryData->ID, group) ) )
        {
#ifdef  DEBUG_MSG
            log_encrypt_message(1, "    Error: Can not Find QQ_GET_QUERY_SOMEONE( ID: %d  Name %s)", p->sid, p->name);
#endif//DEBUG_MSG
            return TTN_NOT_OK;
        }

        lstrcpyn(p->name,        QQueryData->MainName, 32);
        lstrcpyn(p->nickname,    QQueryData->NickName, 32);

        p->country = QQueryData->Country;

        lstrcpyn(p->guild_name,  QQueryData->GuildName,    32);

        p->money = QQueryData->Money;
        p->level = QQueryData->Level + 1;
        p->pk    = QQueryData->PK;

        lstrcpyn(p->partner_name, QQueryData->Spouse,   32);
        
        p->prestige   = QQueryData->Prestige;
        p->icon_index = QQueryData->Career - 1;


    }
    else
    {
        UI_QQFRIEND f;
        p = &f;

        lstrcpyn(p->name,        QQueryData->MainName, 32);
        lstrcpyn(p->nickname,    QQueryData->NickName, 32);
        
        p->country = QQueryData->Country;
        
        lstrcpyn(p->guild_name,  QQueryData->GuildName,    32);
        
        p->money = QQueryData->Money;
        p->level = QQueryData->Level + 1;
        p->pk    = QQueryData->PK;
        
        lstrcpyn(p->partner_name, QQueryData->Spouse,   32);
        
        p->prestige   = QQueryData->Prestige;
        p->icon_index = QQueryData->Career - 1;

        ui_qq_set_detail( p );
    }

#ifdef  DEBUG_MSG
        log_encrypt_message(1, "    QQ_GET_QUERY_SOMEONE( ID: %d  Name %s)", p->sid, p->name);
#endif//DEBUG_MSG
    return    0;
}


/* receive search result */
SLONG    client_handle_qq_get_query_add_list(DWORD wParam)
{
    TPOS_EVENT_QQGETQUERYONLINELIST *AddListReturn;
    UI_QQFRIEND f;
    SLONG i;
    SLONG result = TTN_OK;

    AddListReturn = (TPOS_EVENT_QQGETQUERYONLINELIST *)wParam;

    qq_search_set_index( AddListReturn->BookMark );

    for ( i = 0; i < MAX_ADD_LIST; i++)
    {
        ZeroMemory(&f, sizeof(UI_QQFRIEND));
        f.sid  = AddListReturn->QQAddList[i].ID;
        f.level      = AddListReturn->QQAddList[i].Level + 1;
    
        lstrcpyn( f.name,       AddListReturn->QQAddList[i].MainName, 32);
        lstrcpyn( f.guild_name, AddListReturn->QQAddList[i].GuildName, 32);
        qq_search_add(&f);

#ifdef  DEBUG_MSG
        log_encrypt_message(1, "    QQ_GET_QUERY_ADD_LIST(ID: %d, Name: %s)",
                                f.sid, f.name);
#endif//DEBUG_MSG
    }

    return result;
}

/* receive search end */
SLONG    client_handle_qq_get_query_add_list_end(DWORD wParam)
{
    TPOS_EVENT_QQGETQUERYONLINELIST *AddListReturn;
    UI_QQFRIEND f;
    SLONG i;
    SLONG result = TTN_OK;
    
    AddListReturn = (TPOS_EVENT_QQGETQUERYONLINELIST *)wParam;
    
    qq_search_set_index( AddListReturn->BookMark );
    
    for ( i = 0; i < MAX_ADD_LIST; i++)
    {
        if ( !AddListReturn->QQAddList[i].ID )
            break;

        ZeroMemory(&f, sizeof(UI_QQFRIEND));
        f.sid  = AddListReturn->QQAddList[i].ID;
        f.level      = AddListReturn->QQAddList[i].Level + 1;
        
        lstrcpyn( f.name,       AddListReturn->QQAddList[i].MainName, 32);
        lstrcpyn( f.guild_name, AddListReturn->QQAddList[i].GuildName, 32);
        qq_search_add(&f);
        
#ifdef  DEBUG_MSG
        log_encrypt_message(1, "    QQ_GET_QUERY_ADD_LIST(ID: %d, Name: %s)",
            f.sid, f.name);
#endif//DEBUG_MSG
    }
#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    QQ_GET_QUERY_ADD_LIST_END" );
#endif//DEBUG_MSG

    ui_qq_find3_search_end();

    return result;
}

/* add specify player */
SLONG    client_handle_qq_get_add_someone(DWORD wParam)
{
    TPOS_EVENT_QQGETADDSOMEONE *AddOne;
    UI_QQFRIEND f;
    UI_QQFRIEND *p = NULL;
    SLONG index, group;


    AddOne = (TPOS_EVENT_QQGETADDSOMEONE*)wParam;

    ZeroMemory(&f, sizeof(UI_QQFRIEND));

    f.icon_index = AddOne->Career - 1;
    f.state         = AddOne->State;
    f.sid  = AddOne->TargetID;
    lstrcpyn(f.name, AddOne->MainName,  32);

    if ( AddOne->Relation == 0 )        // Add to friend list
    {
        group = QQ_MY_FRIENDS;

        p = qf_get_by_sid( AddOne->TargetID, QQ_STRANGERS );
        if ( p )
        {
            index = qf_get_index( p, QQ_STRANGERS );
            if ( index != -1 )
            {
                qf_delete( index, QQ_STRANGERS );
            }
        }
    }
    else if ( AddOne->Relation == 1 )    // Add to black list
    {
        group = QQ_UNDESIREDERS;

        p = qf_get_by_sid( AddOne->TargetID, QQ_UNDESIREDERS );
        if ( p )
        {
            index = qf_get_index( p, QQ_UNDESIREDERS );
            if ( index != -1 )
            {
                qf_delete( index, QQ_UNDESIREDERS );
            }
        }
    }
    else
    {
        log_error(1, "Error: Bad friend group in get add friend.");
        return    -1;
    }

    qf_add( &f,  group );

    if ( group == QQ_MY_FRIENDS && p && ( index != -1 ) )
    {
        qq_chat_move(index, QQ_STRANGERS, 
                        qf_get_index_by_sid(f.sid, group), group);
    }

#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    QQ_GET_ADD_SOMEONE(ID: %d, Name: %s)", 
                                f.sid, f.name);
#endif//DEBUG_MSG


    return    0;
}


SLONG    client_handle_qq_get_add_guild_friend(DWORD wParam)
{
    // Jack, TODO [1/3/2003]
    /*
    TPOS_QQ_FRIEND AddOne;
    UI_QQFRIEND f;
    
    if (SEND_MSG_OK != PosQQGetAddSomeone(&AddOne))
    {
        log_error(1, "Error: get add guild friend failed");
        return -1;
    }
    
    ZeroMemory(&f, sizeof(UI_QQFRIEND));
    
    f.icon_index = AddOne.Career - 1;
    f.state         = AddOne.State;
    f.sid  = AddOne.ID;
    lstrcpyn(f.name,       AddOne.MainName,  32);
    
    qf_add(&f, QQ_GUILD_PLAYERS);

#ifdef  DEBUG_MSG
  log_encrypt_message(1, "    QQ_ADD_GUILD_FRIEND(ID: %d, Name: %s)", f.sid, f.name);
#endif//DEBUG_MSG
    */

    return    0;
}


/* get friend login message */
SLONG    client_handle_qq_friend_login(DWORD wParam)
{

    DWORD *ID;
    UI_QQFRIEND *p;
    SLONG group;

    ID = (DWORD*)wParam;

    //TODO: Show friend online self-motion

    group = qf_get_group_by_sid(*ID);
    if (NULL != (p = qf_get_by_sid(*ID, group)))
    {
        qf_set_state(p, QF_ONLINE);
        qfl_sort( group );
    }

#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    QQ_FRIEND_LOGIN(ID: %d )", *ID);
#endif//DEBUG_MSG

    return    0;
}



/* get friend logout message */
SLONG    client_handle_qq_friend_logout(DWORD wParam)
{
    DWORD *ID;
    UI_QQFRIEND *p;
    SLONG group;

    ID = (DWORD*)wParam;

    group = qf_get_group_by_sid( *ID );
    if (NULL != (p = qf_get_by_sid( *ID, group)))
    {
        qf_set_state(p, QF_OFFLINE);
        qfl_sort( group );
    }

#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    QQ_FRIEND_LOGOUT(ID: %d )", *ID);
#endif//DEBUG_MSG

    return    0;
}


/* get new one joined current team message */
SLONG    client_handle_qq_team_join(DWORD wParam)
{
    // Jack, TODO [1/3/2003]
    /*
    UI_QQFRIEND f;
    TPOS_QQ_FRIEND Team;
    
    if (SEND_MSG_OK != PosQQTeamJoin(&Team))
    {
        log_error(1, "Error: get joined team player failed");
        return -1;
    }

    ZeroMemory(&f, sizeof(UI_QQFRIEND));

    f.sid  = Team.ID;
    f.icon_index = Team.Career - 1;
    f.state         = Team.State;
    lstrcpyn(f.name, Team.MainName, 32);


    qf_add(&f, QQ_TEAM_PLAYERS);

#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    QQ_TEAM_JOIN(ID: %d, Name: %s)", f.sid, f.name);
#endif//DEBUG_MSG
    */

    return    0;
}


/* get friend exit the current team message */
SLONG    client_handle_qq_team_exit(DWORD wParam)
{
    // Jack, TODO [1/3/2003]
    /*
    DWORD ID;
    UI_QQFRIEND *p;
    SLONG index;

    if (SEND_MSG_OK != PosQQTeamExit(ID))
    {
        log_error(1, "Error: get exit team player failed.");
        return    -1;
    }

    if (NULL != (p = qf_get_by_sid(ID, QQ_TEAM_PLAYERS)))
    {
        index = qf_get_index(p, QQ_TEAM_PLAYERS);
        qf_delete(index, QQ_TEAM_PLAYERS);
    }

#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    QQ_TEAM_EXIT(ID: %d)", ID);
#endif//DEBUG_MSG
    */

    return    0;
}


/* get delete friend result */
SLONG    client_handle_qq_get_del_friend(DWORD wParam)
{
    TPOS_EVENT_QQGETDELFRIEND *DelFriend;
    UI_QQFRIEND *p;
    SLONG index;
    SLONG group;

    DelFriend = (TPOS_EVENT_QQGETDELFRIEND*)wParam;

    group = qf_get_group_by_sid( DelFriend->TargetID );

    if (NULL != (p = qf_get_by_sid( DelFriend->TargetID, group ) ) )
    {
        index = qf_get_index( p, group );
        qf_delete( index, group );
        qq_chat_del_specify_one( index, group );
    }

#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    QQ_GET_DEL_FRIEND(ID: %d)", DelFriend->TargetID);
#endif//DEBUG_MSG


    return    0;
}



SLONG    client_handle_qq_get_del_guild_friend(DWORD wParam)
{
    TPOS_EVENT_QQGETDELGUILDFRIEND *DelFriend;
    UI_QQFRIEND *p;
    SLONG index;

    DelFriend = (TPOS_EVENT_QQGETDELGUILDFRIEND*)wParam;
    
    if ( NULL != ( p = qf_get_by_sid( DelFriend->TargetID, QQ_GUILD_PLAYERS ) ) )
    {
        index = qf_get_index( p, QQ_GUILD_PLAYERS );
        qf_delete( index, QQ_GUILD_PLAYERS );
    }
    
#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    QQ_GET_DEL_GUILD_FRIEND(ID: %d)", DelFriend->TargetID);
#endif//DEBUG_MSG


    return    0;
}


/* get chat message */
SLONG    client_handle_qq_get_msg(DWORD wParam)
{
    TPOS_EVENT_QQGETMSG *QQMsg;
    UI_QQFRIEND f;
    UI_QQFRIEND *p;
    SLONG index;
    SLONG group;
    char  name[32];

    QQMsg = (TPOS_EVENT_QQGETMSG *)wParam;

    group = qf_get_group_by_sid( QQMsg->SendID );
    if (NULL == ( p = qf_get_by_sid( QQMsg->SendID, group ) ) )
    {
        if (qfms_check(KEEP_STRANGER_AWAY))
            return    TTN_NOT_OK;

        ZeroMemory( &f, sizeof(f) );
        p = &f;

        p->sid = QQMsg->SendID;

        wsprintf(name, "%s%d", QQTXT_STRANGER_NAME, qfl_count(QQ_STRANGERS));
        lstrcpyn(p->name, name, 32);

        qf_add(p, QQ_STRANGERS);
        
        group = QQ_STRANGERS;

        if ( NULL == ( p = qf_get_by_sid( QQMsg->SendID, group) ) )
            return    TTN_NOT_OK;
    }

    index = qf_get_index(p, group);
    if (index == -1)
        return    -5;

    qq_chat_add_chat( index, group, QQMsg->SendID, QQMsg->Msg );

    // 保存聊天記錄
    qq_log_add( p->sid, p->name, QQMsg->Msg );


#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    QQ_GET_MSG(ID: %d)", QQMsg->SendID);
#endif//DEBUG_MSG

    return    TTN_OK;
}


/* get total players number in the current world */
SLONG    client_handle_qq_get_player_count(DWORD wParam)
{
    TPOS_EVENT_QQGETPLAYERCOUNT *Count;


    Count = (TPOS_EVENT_QQGETPLAYERCOUNT *)wParam;

    ui_qq_set_online_count( Count->PlayerCount );

#ifdef  DEBUG_MSG
    log_encrypt_message(1, "    QQ_GET_PLAYER_COUNT(COUNT: %d)", Count->PlayerCount );
#endif//DEBUG_MSG

    return    TTN_OK;
}


SLONG    client_handle_qq_get_item( DWORD wParam )
{
    TPOS_EVENT_QQGETTRANSFERITEM *Item;

    Item = (TPOS_EVENT_QQGETTRANSFERITEM *)wParam;

    ui_qq_get_item( Item->RequestID );

#ifdef DEBUG_MSG
    log_encrypt_message( 1, "    QQ_GET_TRANSFER_ITEM( ID: %d)", Item->RequestID );
#endif

    return TTN_OK;
}

SLONG    client_handle_qq_get_item_fail( DWORD wParam )
{
    TPOS_EVENT_QQTRANSFERITEMFAIL    *Item;

    Item = (TPOS_EVENT_QQTRANSFERITEMFAIL*)wParam;

    ui_qq_send_item_failed( Item->TargetID );

#ifdef DEBUG_MSG
    log_encrypt_message( 1, "    QQ_TRANSFER_ITEM_FAILED( ID: %d)", Item->TargetID );
#endif
    
    return TTN_OK;
}

SLONG    client_handle_qq_get_item_ok( DWORD wParam )
{
    TPOS_EVENT_QQTRANSFERITEMOK    *Item;

    Item = (TPOS_EVENT_QQTRANSFERITEMOK*)wParam;

    ui_qq_send_item_ok( Item->TargetID );

#ifdef DEBUG_MSG
    log_encrypt_message( 1, "    QQ_TRANSFER_ITEM_OK( ID: %d)", Item->TargetID );
#endif

    return TTN_OK;
}

/************************************************************************/
/* reserved                                                             */
/************************************************************************/
/* login failed, error password */
SLONG    client_handle_qq_login_errpw(DWORD wParam)
{
    return    0;
}


/* login failed, error id */
SLONG    client_handle_qq_login_errid(DWORD wParam)
{
    return    0;
}

/* login failed, login refuse */
SLONG    client_handle_qq_login_denied(DWORD wParam)
{
    return    0;
}

/* login failed, login repeat */
SLONG    client_handle_qq_login_repeat(DWORD wParam)
{
    return    0;
}


