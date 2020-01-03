/*---------------------------------------------------------------------
|         qqlog.cpp      Zhang Zhaohui, 2003/3/6.
|         Get/Add chat log
\---------------------------------------------------------------------*/


#include "qqlog.h"
#include "qqlocal.h"
#include "qqmsg.h"

#define QQ_LOG_MAX                  0x800  // 

//////////////////////////////////////////////////////////////////////////

QQ_LOG  *g_log_buf  = NULL;
DWORD   g_log_count = 0;
DWORD   g_log_max_count = QQ_LOG_MAX;

DWORD   g_log_buf_block = 1;

//////////////////////////////////////////////////////////////////////////

static VOID     qq_log_get_time_str( time_t ltime, CHAR *time_buf );
static SLONG    qq_log_list_init( VOID );
static VOID     qq_log_list_free( VOID );
static SLONG    qq_log_list_add( QQ_LOG *log_info );
static QQ_LOG   *qq_log_list_get( DWORD index );
static SLONG    qq_log_list_grow( VOID );

//////////////////////////////////////////////////////////////////////////
// 函數實現
//////////////////////////////////////////////////////////////////////////
SLONG   qq_log_init( VOID )
{
    return qq_log_list_init( );
}

VOID   qq_log_free( VOID )
{
    qq_log_list_free( );
}

SLONG qq_log_get( DWORD sid, DWORD index, QQ_LOG *log_info )
{
    static DWORD g_sid = 0;
    CHAR    name_buf[32];
    CHAR    time_buf[32];
    CHAR    chat_buf[200];
    QQ_LOG  *p_log = NULL;
    time_t  ltime;
    

    if ( sid != g_sid )
    {
        if ( g_sid != 0 )
        {
            ql_get_chat_end();
        }
        g_sid = sid;
        if ( !ql_get_first_chat( g_sid, name_buf, &ltime, chat_buf ) )
            return TTN_NOT_OK;
    }
    else
    {
        if ( index > g_log_count )
        {
            if ( !ql_get_next_chat( name_buf, &ltime, chat_buf ) )
                return TTN_NOT_OK;
        }
        else
        {
            p_log = qq_log_list_get( index );

            if ( p_log == NULL )
                return TTN_NOT_OK;

            *log_info = *p_log;

            return TTN_NOT_OK;
        }
    }

    qq_log_get_time_str( ltime, time_buf );
        
    strcpy( log_info->name, name_buf );
    strcpy( log_info->time, time_buf );
    strcpy( log_info->chat, chat_buf );
    
    qq_log_list_add( log_info );

    return TTN_OK;
}

SLONG qq_log_add( DWORD sid, CHAR *name, CHAR *chat )
{
    return ql_add_chat( sid, name, chat );
}

VOID qq_log_delete( DWORD sid )
{
    ql_del_chat( sid );
}

//////////////////////////////////////////////////////////////////////////
// 將時間轉換為字符串
//////////////////////////////////////////////////////////////////////////

VOID qq_log_get_time_str( time_t ltime, CHAR *time_buf )
{
    tm    *tm_time;
    tm_time = localtime( &ltime );
    sprintf( time_buf, QQTXT_TIME_STR, tm_time->tm_year + 1900,
                                       tm_time->tm_mon + 1,
                                       tm_time->tm_mday,
                                       tm_time->tm_mday,
                                       tm_time->tm_hour,
                                       tm_time->tm_min );
}

//////////////////////////////////////////////////////////////////////////
// 儲存從文件讀入的聊天記錄
//////////////////////////////////////////////////////////////////////////

SLONG   qq_log_list_init( VOID )
{
    if ( g_log_buf )
        qq_log_list_free( );
    
    g_log_buf = (QQ_LOG*)GlobalAlloc( GPTR, QQ_LOG_MAX * sizeof(QQ_LOG) );

    if ( g_log_buf == NULL )
        return TTN_NOT_OK;

    g_log_count = 0;
    
    return TTN_OK;
}

VOID    qq_log_list_free( VOID )
{
    if ( g_log_buf )
    {
        GlobalFree( g_log_buf );
        g_log_buf = NULL;
    }
    g_log_count = 0;
    g_log_buf_block = 1;
}


SLONG   qq_log_list_add( QQ_LOG *log_info )
{
    if ( !g_log_buf )
        return TTN_NOT_OK;

    if ( g_log_count >= g_log_max_count )
    {
        if ( qq_log_list_grow( ) != TTN_OK )
            return TTN_NOT_OK;
    }

    g_log_buf[g_log_count] = *log_info;
    g_log_count++;

    return TTN_OK;
}


QQ_LOG  *qq_log_list_get( DWORD index )
{
    if ( !g_log_buf )
        return NULL;

    if ( index < g_log_count )
        return &g_log_buf[index];

    return NULL;
}


SLONG    qq_log_list_grow( VOID )
{
    QQ_LOG *p_log = NULL;

    g_log_buf_block++;

    p_log = (QQ_LOG*)GlobalReAlloc( g_log_buf, 
                QQ_LOG_MAX * sizeof(QQ_LOG) * g_log_buf_block, 0 );
    if ( p_log == NULL )
        return TTN_NOT_OK;

    g_log_buf = p_log;

    return TTN_OK;
}