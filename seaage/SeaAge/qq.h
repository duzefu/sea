/*
**    qq.h
**    QQ functions.
**
**    Jack, 2002/07/19.
**
**  Modified by ZZH, 2002.7.25
*/
#ifndef _UIQQ_H_
#define _UIQQ_H_
#include "mainfun.h"
#include "clientmain.h"
#include "qqfriend.h"
#include "NetGe_Character.h"
// DEFINES /////////////////////////////////////////////////////////////////////////

#define MAX_TEXT_LEN                210

#define QQ_KEY_ONCHAR                0
#define QQ_KEY_ONKEYDOWN            1

// STRUCTURES ////////////////////////////////////////////////////////////

//

int     init_ui_qq(void);
void    active_ui_qq(int active);
void    free_ui_qq(void);
void    refresh_ui_qq(void);
void    redraw_ui_qq(BMP *bitmap);
SLONG    handle_ui_qq(UINT message, WPARAM wParam, LPARAM lParam);

void    qq_clear(void);

BOOL    ui_qq_is_max(void);
void    ui_qq_set_min(void);
void    ui_qq_set_max(void);

void    redraw_uiqq_mouse_point_info(SLONG event, SLONG id, BMP *bitmap);

void    ui_qq_show_msg(void);
void    ui_qq_set_online_count(DWORD count);

void    ui_qq_find3_search_end( void );

void    ui_qq_set_detail( LPUI_QQFRIEND p );

void    ui_qq_get_item( DWORD ID );
void    ui_qq_send_item_failed( DWORD ID );
void    ui_qq_send_item_ok( DWORD ID );
#endif//_UIQQ_H_
