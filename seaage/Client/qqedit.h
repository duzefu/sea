/*
 * qqedit.h
 * functions for edit text
 * Zhang Zhaohui
 * 2002.9.17
 */
#pragma once

#include <rays.h>
#include "mainfun.h"


enum UI_EDIT_FONT
{
    TE_FONT_SIZE_ERR        = 0,
    TE_FONT_SIZE_12         = 12,
    TE_FONT_SIZE_16         = 16,
    TE_FONT_SIZE_20         = 20,
    TE_FONT_SIZE_24         = 24,
    TE_FONT_SIZE_28         = 28,
    TE_FONT_SIZE_32         = 32,
};

enum UI_EDIT
{
    TE_MAX_LIST             = 64,
    TE_EVENT                = 26000,
};


// 光標位置的結構
typedef struct tagUI_TEXT_CARET
{
    SLONG lnum;         // line number
    SLONG col;          // column number
}UI_TEXT_CARET, *LPUI_TEXT_CARET;


// 文字輸入區的結構
typedef struct tagUI_TEXT
{
    char*           ptext_buf;
    char*           ptext_next;

    SLONG           buf_size;                // 文字緩衝區的大小
    SLONG           top_line;                // 縱向滾動時顯示第一行的位置
    SLONG           left_col;                // 橫向滾動時第一個字符的位置
    SLONG           x, y;
    SLONG           w, h;
    RECT            rc;
    BOOL            active;
    BOOL            single_line;
    BOOL            number_only;
    BOOL            h_scroll;
    BOOL            read_only;
    PIXEL           text_color;
    
    SLONG           focus_pos;
    UI_TEXT_CARET   sel_start;
    UI_TEXT_CARET   sel_end;
    UI_TEXT_CARET   caret_pos;

    DWORD           caret_timer;

    UI_EDIT_FONT    font_size;
    SLONG           font_h;
    SLONG           font_w_half;
} UI_TEXT, *LPUI_TEXT;


// 輸入區列表
typedef struct tagUI_EDIT_LIST
{
    UI_TEXT *focus;
    DWORD    count;
    UI_TEXT  *list[TE_MAX_LIST];
} TE_LIST;



// void    te_init(LPUI_TEXT ptext, SLONG buf_size, SLONG w, SLONG h, SLONG single_line);
// void    te_free(LPUI_TEXT ptext);

SLONG   handle_te( UINT msg, WPARAM wparam, LPARAM lparam );
VOID    redraw_te( UI_TEXT *ptext, BMP* bitmap );

UI_TEXT *te_create( SLONG x, SLONG y, SLONG w, SLONG h, SLONG buf_size );
BOOL    te_destroy( UI_TEXT *ptext);

void    te_set_color(LPUI_TEXT ptext, PIXEL color);

void    te_set_active(LPUI_TEXT ptext, BOOL b_active );
void    te_set_single_line( LPUI_TEXT ptext, BOOL b_single );
void    te_set_number_only(LPUI_TEXT ptext, BOOL number_only);
void    te_set_read_only( LPUI_TEXT ptext, BOOL read_only );

void    te_set_xy( LPUI_TEXT ptext, SLONG x, SLONG y );
void    te_set_wh(LPUI_TEXT ptext, SLONG w, SLONG h);
SLONG   te_get_size(LPUI_TEXT ptext);
void    te_set_text(LPUI_TEXT ptext, char *p_buf);
void    te_enable_v_scroll(LPUI_TEXT ptext, BOOL enable);

void    te_set_font_size(LPUI_TEXT ptext,UI_EDIT_FONT fsize);
SLONG   te_get_font_size(LPUI_TEXT ptext);
SLONG   te_get_max_line(LPUI_TEXT ptext);
SLONG   te_get_number( LPUI_TEXT ptext );

VOID    te_set_focus( LPUI_TEXT ptext );
VOID    te_force_set_focus( LPUI_TEXT ptext );
UI_TEXT *te_get_focus( VOID );

VOID    te_list_clear( VOID );

