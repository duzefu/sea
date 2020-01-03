/*
**    qqlog.h
**    qq chat log
**
**    Zhang Zhaohui, 2003/02/17.
**
**    讀取/保存 聊天記錄
**
*/

#pragma once

#include <rays.h>

typedef struct tagQQ_LOG
{
    CHAR    name[32];
    CHAR    time[24];
    CHAR    chat[200];

} QQ_LOG, *LP_QQ_LOG;

SLONG   qq_log_init( VOID );
VOID    qq_log_free( VOID );

SLONG   qq_log_get( DWORD sid, DWORD index, QQ_LOG *log_info );
SLONG   qq_log_add( DWORD sid, CHAR *name, CHAR *chat );
VOID    qq_log_delete( DWORD sid );
