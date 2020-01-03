/*
 * qqlocal.h
 * functions for save and load qq information
 *        qq information include chat log
 * Zhang Zhaohui
 * 2002.10.11
 */

#pragma once

#include "mainfun.h"
#include "qqfriend.h"

enum QQLOCAL
{
    QL_NAME_TEXT_SIZE    = 20,
    QL_MAX_TEXT_SIZE     = 200,
    QL_FILE_SIGN_SIZE    = 8,
    QL_MAX_BLOCK_SIZE    = 1048,
    QL_RESERVED_SIZE     = 64,        // reserver size in save file
};



/***************************************
 *
 *
 *  System Message Save Structure
 *
 *
 **************************************/

typedef struct tagUI_QQMSG_SAVE_HEADER
{
    char        sign[QL_FILE_SIGN_SIZE];
    DWORD       version;
    DWORD       total_msg;
    DWORD       first_offset;   // offset of last block
    WORD        key1;           // 31 ~ 24 15 ~ 8 of key ( DWORD )
    WORD        key2;           // 23 ~ 16  7 ~ 0 of key ( DWORD )
    char        reserved[QL_RESERVED_SIZE];

} QLM_HEADER, *LP_QLM_HEADER;

/***************************************
 *
 *
 *  Chat Save Structure
 *
 *
 **************************************/

typedef struct tagUI_QQCHAT_SAVE_HEADER
{
    char        sign[QL_FILE_SIGN_SIZE];
    LONG        version;
    WORD        key1;           // 31 ~ 24 15 ~ 8 of key ( DWORD )
    WORD        key2;           // 23 ~ 16  7 ~ 0 of key ( DWORD )
    char        reserved[QL_RESERVED_SIZE];

} QLC_HEADER, *LP_QLC_HEADER;


typedef struct tagUI_QQCHAT_INDEX_HEADER
{
    char        sign[QL_FILE_SIGN_SIZE];
    DWORD       version;
    DWORD       count;
    char        reserved[QL_RESERVED_SIZE];

} QLCI_HEADER, *LP_QLCI_HEADER;


typedef struct tagUI_QQCHAT_INDEX_BLOCK
{
    DWORD       sid;                // server ID
    DWORD       offset;            // offset in chat file

} QLCI_BLOCK, *LP_QLCI_BLOCK;

/***************************************
 *
 *
 *  Save File Block ( both chat save and message save )
 *
 *
 **************************************/

typedef struct tagUI_QQ_SAVE_BLOCK
{
    DWORD       check_code;
    DWORD       next_offset;
    time_t      time;
    CHAR        name[QL_NAME_TEXT_SIZE];        // 說話人的名字
    CHAR        text_buf[QL_MAX_TEXT_SIZE];

} QL_BLOCK, *LP_QL_BLOCK;


/***************************************
 *
 *
 *  Functions
 *
 *
 **************************************/

LONG ql_init( VOID );
VOID ql_free( VOID );


LONG ql_on_login( VOID );
LONG ql_on_logout( VOID );


// system message --------------------------------------------------------
BOOL ql_get_first_msg( time_t* ltime, CHAR * message );
BOOL ql_get_next_msg( time_t* ltime, CHAR* message );
VOID ql_get_msg_end( VOID );

BOOL  ql_add_msg( char *message );
DWORD ql_get_msg_count( VOID );

// chat ------------------------------------------------------------------
BOOL ql_get_first_chat( DWORD sid, CHAR *name, time_t* ltime, CHAR *text );
BOOL ql_get_next_chat( CHAR *name, time_t* ltime, CHAR* text );
VOID  ql_get_chat_end( VOID );

BOOL ql_add_chat( DWORD sid, CHAR *name, CHAR* text );
VOID ql_del_chat( DWORD sid );

