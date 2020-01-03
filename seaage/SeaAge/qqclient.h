/*
 * qqclient.h
 * functions for communication between qq server and qq client
 * Zhang Zhaohui
 * 2002.10.11
 * 
 * All index in qqclient is the index of player in server
 *
 */

#ifndef QQCLIENT_H_
#define QQCLIENT_H_
#include "mainfun.h"
#include "qqfriend.h"
#include "qqsearch.h"
#include "netge_item.h"
enum QQ_CLIENT{ QQ_CLIENT_EVENT = 50000};

/* receive message for server */
extern    SLONG qq_client_get_server_msg(DWORD msg);

/* send message to server */
extern    SLONG qq_client_request_mydata(void);
extern    SLONG qq_client_request_friend_list(void);
extern    SLONG qq_client_request_guild_friend_list(void);
extern    SLONG qq_client_set_mystate(char State);
extern    SLONG qq_client_set_myconfig(DWORD Settings);
extern    SLONG qq_client_request_query_someone(DWORD ID);
extern    SLONG qq_client_request_query_add_list(UI_QQSEARCH_FILTER *p_filter);
extern    SLONG qq_client_request_query_online_addlist( void );
extern    SLONG qq_client_request_add_someone(DWORD ID, UCHAR relation );
extern    SLONG qq_client_request_team_list(void);
extern    SLONG qq_client_request_del_friend(DWORD ID);
extern    SLONG qq_client_request_del_guild_friend(DWORD ID);
extern    SLONG qq_client_request_player_count(void);
extern    SLONG qq_client_qq_send_2one_msg(DWORD ID, char *p_text);
extern    SLONG qq_client_qq_send_2some_msg(DWORD size, DWORD *p_ID, char *p_text);
extern    SLONG qq_client_request_hit_trans_item( char r_l, UCHAR index );
extern    SLONG qq_client_request_transfer_item( DWORD ID );

//
//QQ message handle functions:
extern    SLONG    client_handle_qq_login_errpw(DWORD wParam);
extern    SLONG    client_handle_qq_login_errid(DWORD wParam);
extern    SLONG    client_handle_qq_login_denied(DWORD wParam);
extern    SLONG    client_handle_qq_login_repeat(DWORD wParam);
extern    SLONG    client_handle_qq_player_login(DWORD wParam);
extern    SLONG    client_handle_qq_login_ok(DWORD wParam);
extern    SLONG    client_handle_qq_player_logout(DWORD wParam);
extern    SLONG    client_handle_qq_get_mydata(DWORD wParam);
extern    SLONG    client_handle_qq_get_myconfig(DWORD wParam);
extern    SLONG    client_handle_qq_login_fail(DWORD wParam);
extern    SLONG    client_handle_qq_get_friend_list(DWORD wParam);
extern    SLONG    client_handle_qq_get_guild_friend_list(DWORD wParam);
extern    SLONG    client_handle_qq_get_team_list(DWORD wParam);
extern    SLONG    client_handle_qq_get_mystate(DWORD wParam);
extern    SLONG    client_handle_qq_get_otherstate(DWORD wParam);
extern    SLONG    client_handle_qq_get_query_someone(DWORD wParam);
extern    SLONG    client_handle_qq_get_query_add_list(DWORD wParam);
extern  SLONG    client_handle_qq_get_query_add_list_end(DWORD wParam);
extern    SLONG    client_handle_qq_get_add_someone(DWORD wParam);
extern    SLONG    client_handle_qq_get_add_guild_friend(DWORD wParam);
extern    SLONG    client_handle_qq_friend_login(DWORD wParam);
extern    SLONG    client_handle_qq_friend_logout(DWORD wParam);
extern    SLONG    client_handle_qq_team_join(DWORD wParam);
extern    SLONG    client_handle_qq_team_exit(DWORD wParam);
extern    SLONG    client_handle_qq_get_del_friend(DWORD wParam);
extern    SLONG    client_handle_qq_get_msg(DWORD wParam);
extern    SLONG    client_handle_qq_get_player_count(DWORD wParam);
extern    SLONG    client_handle_qq_get_del_guild_friend(DWORD wParam);
extern    SLONG    client_handle_qq_get_item( DWORD wParam );
extern    SLONG    client_handle_qq_get_item_fail( DWORD wParam );
extern    SLONG    client_handle_qq_get_item_ok( DWORD wParam );


#endif    /* QQCLIENT_H_ */
