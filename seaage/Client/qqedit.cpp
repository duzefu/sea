/*
 * qqedit.h
 * functions for edit text
 * Zhang Zhaohui
 * 2002.9.17
 */

#include "qqedit.h"
#include "cRange.h"
#include "ErrorMsg.h"

#define TE_CARET_TIMER              0x8
#define TE_DEFAULT_COLOR            SYSTEM_BLACK
#define TE_CARET_COLOR              SYSTEM_RED
#define TE_SELECTED_BK_COLOR        SYSTEM_DARK5

TE_LIST     te_list;
LOGFONT     te_old_ime_font;
LOGFONT     te_ime_font;
HKL         hKL = NULL;
/************************************************************************/
/* Local functions                                                      */
/************************************************************************/

static BOOL     te_available(LPUI_TEXT ptext);

static SLONG    te_on_char(LPUI_TEXT ptext, WPARAM wparam, LPARAM lparam );
static SLONG    te_on_keydown(LPUI_TEXT ptext, WPARAM wparam, LPARAM lparam );
static SLONG    te_on_ime_string(LPUI_TEXT ptext, WPARAM wparam, LPARAM lparam );
static SLONG    te_on_ime_char( LPUI_TEXT ptext, WPARAM wparam, LPARAM lparam );
static SLONG    te_on_lmd( WPARAM wparam, LPARAM lparam );
static SLONG    te_on_lmu( WPARAM wparam, LPARAM lparam );
static SLONG    te_on_mv( WPARAM wparam, LPARAM lparam );
static SLONG    te_on_button(LPUI_TEXT ptext, SLONG x, SLONG y);

static char     *te_next_char(const char *p);
static char     *te_prev_char(const char *pstart, const char *p);

static BOOL     te_is_display_char(TCHAR ch);
static BOOL     te_is_number_char(TCHAR ch);

static void     te_copy(LPUI_TEXT ptext);
static void     te_cut(LPUI_TEXT ptext);
static void     te_paste(LPUI_TEXT ptext);
static void     te_delete(LPUI_TEXT ptext);

static void     te_insert_ch(LPUI_TEXT ptext, int ch_code);
static void     te_insert_str(LPUI_TEXT ptext, char* pstr);
static void     te_del_ch(LPUI_TEXT ptext);

static SLONG    te_str_sub_len(char* pstr, SLONG max_len);
static SLONG    te_get_line_len(LPUI_TEXT ptext, SLONG line);
static SLONG    te_get_show_line(LPUI_TEXT ptext);
static char*    te_get_line_start(LPUI_TEXT ptext, SLONG line);

static void     te_draw_line( LPUI_TEXT ptext, SLONG line, BMP *bitmap);
static void     te_draw_sel_bar( LPUI_TEXT ptext, SLONG line, SLONG n,BMP *bitmap );

static void     te_update_pos_by_caret(LPUI_TEXT ptext);
static void     te_update_caret_by_pos(LPUI_TEXT ptext);
static void     te_update_topline(LPUI_TEXT ptext);
static void     te_update_left_col( LPUI_TEXT ptext );

static SLONG    te_get_top_line(LPUI_TEXT ptext);
static void     te_set_top_line(LPUI_TEXT ptext, SLONG top_line);

static void     te_set_caret(LPUI_TEXT ptext, SLONG lnum, SLONG col);

static void     te_draw( LPUI_TEXT ptext, BOOL show_caret, BMP *bitmap);

static void     te_update_select( LPUI_TEXT ptext );
static void     te_ime_update_pos( LPUI_TEXT ptext );
static void     te_ime_set_font( void );
static SLONG    te_ime_is_open( void );
static void     te_ime_update_hkl( void );
static void     te_ime_set_open( BOOL open );

// 輸入區鏈表控制函數
static SLONG    te_list_add( UI_TEXT *ptext );
static SLONG    te_list_index( UI_TEXT *ptext );
static SLONG    te_list_del( SLONG index );
static UI_TEXT  *te_list_get( SLONG index );
static VOID     te_list_set_focus( UI_TEXT *ptext );
static VOID     te_list_set_focus( SLONG index );


/************************************************************************/
/* UI QQ TEXT EDIT                                                      */
/************************************************************************/

// 獲得消息
SLONG    handle_te( UINT msg, WPARAM wparam, LPARAM lparam )
{
    SLONG result = 1;
    
    switch ( msg )
    {
    case WM_CHAR:
        if ( te_list.focus )
            result = te_on_char( te_list.focus, wparam, lparam );
        break;
    case WM_IME_CHAR:
        if ( te_list.focus )
            result =  te_on_ime_char( te_list.focus, wparam, lparam );
        break;
    case WM_KEYDOWN:
        if ( te_list.focus )
            result = te_on_keydown( te_list.focus, wparam, lparam );
        break;
    case WM_KEYUP:
        if ( te_list.focus && wparam >= ' ' && wparam <= '~' )
            result = 0;
        break;
    case WM_LBUTTONDOWN:
        result = te_on_lmd( wparam, lparam );
        break;
    case WM_LBUTTONUP:
        result = te_on_lmu( wparam, lparam );
        break;
    case WM_MOUSEMOVE:
        result = te_on_mv( wparam, lparam );
        break;
    case WM_INPUTLANGCHANGE:                // 在改變輸入法時設置選字框的
        te_ime_update_hkl();
        if ( te_list.focus && ImmIsIME( hKL ) )
            te_ime_set_font( );
        break;
    case WM_INPUTLANGCHANGEREQUEST:
        if ( !te_list.focus )            // 在編輯區失去焦點時寬不響應輸入法事件
            result = 0;
        else
        {
            if ( te_list.focus->number_only )
                result = 0;
        }
        break;
    }

    return result;
}

// 重繪編輯區
VOID    redraw_te( UI_TEXT *ptext, BMP* bitmap )
{
    SLONG id;
    static SLONG event = TE_EVENT;
    
    id = te_list_index( ptext );
    if ( id < 0 )
        return;

    if ( !ptext->active )
        return;

    if ( ptext == te_list.focus )
        te_draw( ptext, TRUE, bitmap );
    else
        te_draw( ptext, FALSE, bitmap );

    game_range.add( ptext->x, ptext->y, ptext->w, ptext->h, event, id );
}


// 建立一個文字編輯框
UI_TEXT *te_create( SLONG x, SLONG y, SLONG w, SLONG h, SLONG buf_size )
{
    UI_TEXT *ptext = NULL;
    CHAR *pbuf = NULL;
    
    if ( NULL == ( ptext = ( UI_TEXT* )GlobalAlloc( GPTR, sizeof( UI_TEXT ) ) ) )
        return NULL;

    ptext->buf_size = buf_size;

    buf_size = ( buf_size + 3 ) & 0xfffffffc;
    if ( NULL == ( pbuf = ( CHAR* )GlobalAlloc( GPTR, buf_size ) ) )
    {
        GlobalFree( ptext );
        return NULL;
    }

    ptext->ptext_buf        = pbuf;
    ptext->ptext_next       = ptext->ptext_buf;
    ptext->x                = x;
    ptext->y                = y;
    ptext->w                = w;
    ptext->h                = h;
    ptext->active           = FALSE;
    ptext->single_line      = FALSE;
    ptext->h_scroll         = FALSE;
    ptext->read_only        = FALSE;
    ptext->text_color       = TE_DEFAULT_COLOR;
    ptext->number_only      = FALSE;
    ptext->caret_timer      = 0;
    ptext->font_size        = TE_FONT_SIZE_12;
    ptext->font_h           = ptext->font_size;
    ptext->font_w_half      = ptext->font_size/2;

    if ( te_list_add( ptext ) == -1 )
    {
        log_error( 1, "Error: Can not create new edit box." );
        GlobalFree( pbuf );
        GlobalFree( ptext );
        return NULL;
    }
    
    return ptext;
}

// 刪除一個文字編輯框
BOOL    te_destroy( UI_TEXT *ptext )
{
    if ( !ptext )
        return FALSE;

    te_list_del( te_list_index( ptext ) );
    
    if ( ptext->ptext_buf )
        GlobalFree( ptext->ptext_buf );
    
    GlobalFree( ptext );

    return FALSE;
}


SLONG te_on_char(LPUI_TEXT ptext, WPARAM wparam, LPARAM lparam )
{
    SLONG result = 1;
    TCHAR ch_code;

    if ( !ptext )
        return result;

    ch_code = (TCHAR)wparam;

    if (te_is_display_char(ch_code))
    {
        if (ptext->number_only && !te_is_number_char(ch_code))
            return result;

        te_insert_ch(ptext, ch_code);

        te_update_caret_by_pos( ptext );
        te_update_topline( ptext );
//        te_update_left_col( ptext );

        ptext->sel_start = ptext->caret_pos;
        ptext->sel_end = ptext->caret_pos;
        result = 0;
    }
    return result;
}

SLONG    te_on_keydown(LPUI_TEXT ptext, WPARAM wparam, LPARAM lparam )
{
    UI_TEXT_CARET *c;
    TCHAR ch_code;
    char *p, *ps;
    SLONG n, m, w;
    SLONG result = 1; 
    SHORT state;

    if ( !ptext )
        return 1;

    ch_code = (TCHAR)wparam;
    c = &ptext->caret_pos;
    p = ptext->ptext_next;
    w = ptext->w/ptext->font_w_half;
    ps = ptext->ptext_buf;

    switch(ch_code)
    {
    case VK_BACK:
        if (c->col != 0 || c->lnum != 0)
        {
            p = te_prev_char(ptext->ptext_buf, p);
            n = ptext->ptext_next - p;

            ptext->ptext_next = p;
            ptext->focus_pos -= n;
            te_del_ch(ptext);

            te_update_caret_by_pos(ptext);
            result = 0;
        }
        break;
    case VK_HOME:
        c->col = 0;
        if ( ptext->h_scroll )
            ptext->left_col = 0;
        te_update_pos_by_caret(ptext);
        ptext->ptext_next = ptext->ptext_buf + ptext->focus_pos;
        result = 0;
        break;
    case VK_END:
        if ( ptext->h_scroll )
        {
            n = strlen( ptext->ptext_buf );
            m = ptext->w/ptext->font_w_half;
            if ( n > 0  )
            {
                if ( n > m )
                {
                    ptext->left_col = n - ptext->w/ptext->font_w_half;
                    c->col = n;
                }
                else
                {
                    n = te_get_line_len(ptext, c->lnum);
                    ptext->left_col = 0;
                    c->col = n;
                }
            }
        }
        else
        {
            n = te_get_line_len(ptext, c->lnum);
            c->col = n;
        }
        te_update_pos_by_caret(ptext);
        ptext->ptext_next = ptext->ptext_buf + ptext->focus_pos;
        result = 0;
        break;
    case VK_DOWN:
        if (c->lnum < te_get_max_line(ptext)-1)
        {
            c->lnum++;
            n = te_get_line_len(ptext, c->lnum);
            if (c->col > n)
                c->col = n;
            else
            {
                p = te_get_line_start(ptext, c->lnum);
                c->col = te_str_sub_len(p, c->col);
            }

            te_update_pos_by_caret(ptext);
            ptext->ptext_next = ptext->ptext_buf + ptext->focus_pos;
            result = 0;
        }
        break;
    case VK_UP:
        if (c->lnum > 0)
        {
            c->lnum--;
            n = te_get_line_len(ptext, c->lnum);
            if (c->col > n)
                c->col = n;
            else
            {
                p = te_get_line_start(ptext, c->lnum);
                c->col = te_str_sub_len(p, c->col);
            }
            te_update_pos_by_caret(ptext);
            ptext->ptext_next = ptext->ptext_buf + ptext->focus_pos;
            result = 0;
        }

        break;
    case VK_LEFT:
        p = te_prev_char(ptext->ptext_buf, p);
        n = ptext->ptext_next - p;
        c->col -= n;
        if ( c->col < 0 )
        {
            if ( c->lnum > 0)
            {
                c->lnum--;
                m = te_get_line_len(ptext, c->lnum);
                c->col = m;
            }
            else
            {
                c->col = 0;
            }
        }
        te_update_pos_by_caret(ptext);
        ptext->ptext_next = ptext->ptext_buf + ptext->focus_pos;
        result = 0;
        break;
    case VK_RIGHT:
        p = te_next_char(p);
        n = p - ptext->ptext_next;
        c->col += n;

        if ( ptext->h_scroll )
        {
//            n = strlen( ptext->ptext_buf );
//            if ( c->col > n )
//                c->col = n;
            m = ptext->w/ptext->font_w_half;
            if ( c->col > m + ptext->left_col )
                ptext->left_col += n;
        }
        else
        {
            n = te_get_line_len(ptext, c->lnum);

            if (c->col > n)
            {
                if (c->lnum < te_get_max_line(ptext)-1)
                {
                    c->col = 0;
                    c->lnum++;
                }
                else
                    c->col = n;
            }
        }
        te_update_pos_by_caret(ptext);
        ptext->ptext_next = ptext->ptext_buf + ptext->focus_pos;
        result = 0;
        break;
    case VK_DELETE:
        te_del_ch(ptext);
        result = 0;
        break;
    case 'C':        // 複製
        state = GetKeyState( VK_CONTROL );
        if ( state & 0x8000 )
        {
            te_copy( ptext );
        }
        result = 0;
        break;
    case 'X':
        state = GetKeyState( VK_CONTROL );
        if ( state & 0x8000 )
        {
            te_cut( ptext );
        }
        result = 0;
        break;
    case 'V':        // 粘貼
        state = GetKeyState( VK_CONTROL );
        if ( state & 0x8000 )
        {
            te_paste( ptext );
        }
        result = 0;
        break;
    default:
        ch_code &= 0xff;
        if ( (UCHAR)ch_code >= ' ' && (UCHAR)ch_code <= '~' ||  
             (UCHAR)ch_code == VK_OEM_COMMA || (UCHAR)ch_code == VK_OEM_PERIOD )
            result = 0;
        break;
    }
    
    te_update_select( ptext );
//    te_update_left_col( ptext );
    te_update_topline(ptext);
    
    return result;
}

/*
SLONG te_on_ime_string(LPUI_TEXT ptext, char* pstr)
{

    if (!te_available(ptext) || NULL == pstr)
        return 0;
    te_insert_str(ptext, pstr);
    te_update_caret_by_pos(ptext);
    te_update_topline(ptext);
    return 1;
}
*/

SLONG te_on_ime_char( LPUI_TEXT ptext, WPARAM wparam, LPARAM lparam )
{
    SLONG result = 1;
    CHAR buf[8];
    if ( !ptext )
        return result;
    
    if ( !HIBYTE( LOWORD( wparam ) ) )
            return result;
    
    buf[0] = HIBYTE( LOWORD(wparam) );
    buf[1] = LOBYTE( LOWORD(wparam) );
    buf[2] = '\0';

    te_insert_str( ptext, buf );

    te_update_caret_by_pos( ptext );
    te_update_topline( ptext );
//    te_update_left_col( ptext );

    ptext->sel_end = ptext->caret_pos;
    ptext->sel_start = ptext->caret_pos;
    result = 0;
    return result;
}

// WM_LBUTTONDOWN
SLONG te_on_lmd( WPARAM wparam, LPARAM lparam )
{
    SLONG event, id;
    SLONG x, y;
    UI_TEXT *ptext = NULL;

    x = LOWORD( lparam );
    y = HIWORD( lparam );

    game_range.mapping( x, y, &event, &id );

    if ( event != TE_EVENT )
    {
        te_list_set_focus( -1 );
        return 1;
    }

    ptext = te_list_get( id );

    if ( !ptext )
        return 1;

    if ( ptext->read_only )
    {
        te_list_set_focus( -1 );
        return 0;
    }

    if ( ptext != te_list.focus )
    {
        te_list_set_focus( te_list_index( ptext ) );
    }

    te_on_button( ptext, x, y );

    ptext->sel_start = ptext->caret_pos;
    ptext->sel_end = ptext->caret_pos;

    return 0;
}

// WM_LBUTTONUP
SLONG te_on_lmu( WPARAM wparam, LPARAM lparam )
{
    SLONG x, y;
    SLONG event, id;
    UI_TEXT *ptext = NULL;

    x = LOWORD( lparam );
    y = HIWORD( lparam );

    game_range.mapping( x, y, &event, &id );

    if ( event != TE_EVENT )
        return 1;

    ptext = te_list_get( id );

    if ( !ptext || ptext != te_list.focus )
        return 1;

    te_on_button( ptext, x, y );

    ptext->sel_end = ptext->caret_pos;
    
    return 0;
}

// 響應鼠標移動
SLONG te_on_mv( WPARAM wparam, LPARAM lparam )
{
    SLONG x, y;
    SLONG event, id;
    UI_TEXT *ptext = NULL;

    // 鼠標左鍵是否按下
    if ( !(wparam & MK_LBUTTON) )
        return 1;

    x = LOWORD( lparam );
    y = HIWORD( lparam );

    game_range.mapping( x, y, &event, &id );

    if ( event != TE_EVENT )
        return 1;

    ptext = te_list_get( id );

    if ( !ptext )
        return 1;

    te_on_button( ptext, x, y );

    ptext->sel_end = ptext->caret_pos;

    return 0;
}


// 根據鼠標點擊的位置來確定光標的位置
SLONG te_on_button(LPUI_TEXT ptext, SLONG x, SLONG y)
{
    SLONG h, w, line, max_line;
    char *pstr;

    if ( !ptext )
        return TTN_NOT_OK;

    h = y - ptext->y;
    w = x - ptext->x;

    if (h <= 0)
        ptext->caret_pos.lnum = 0;
    else
    {
        line = h/ptext->font_size + ptext->top_line;
        max_line = te_get_max_line(ptext);
        if ( max_line == 0 )
            ptext->caret_pos.lnum = 0;
        else
        {
            if (line < max_line)
                ptext->caret_pos.lnum = line;
            else
                ptext->caret_pos.lnum = max_line - 1;
        }
    }

    if (w <= 0)
        ptext->caret_pos.col = 0;
    else
    {
        pstr = te_get_line_start(ptext, ptext->caret_pos.lnum);
        ptext->caret_pos.col = te_str_sub_len(pstr, w/ptext->font_w_half);
    }

    if ( ptext->h_scroll )
    {
        ptext->caret_pos.col += ptext->left_col;
    }

    te_update_pos_by_caret( ptext );
    ptext->ptext_next = ptext->ptext_buf + ptext->focus_pos;
    te_ime_update_pos( ptext );
    return TTN_OK;
}


BOOL te_available(LPUI_TEXT ptext)
{
    if (NULL != ptext && NULL != ptext->ptext_buf && ptext->buf_size >= 0)
    {
        te_ime_update_pos( ptext );
        return true;
    }
    else
        return false;
}

// 判斷是否為可顯示字符
BOOL te_is_display_char(TCHAR ch)
{
//    CHAR c;
//    c = ch&0xff;

    if ( ch >= ' ' && ch <= '~' || ch == 0xd)
        return TRUE;
    else
        return FALSE;
}


// 判斷是否為數字字符
BOOL te_is_number_char(TCHAR ch)
{
    CHAR c;
    c = ch&0xff;

    if (c >= '0' && c <= '9')
        return TRUE;
    else
        return FALSE;
}

// 插入一個字符
void te_insert_ch(LPUI_TEXT ptext, int ch_code)
{
    SLONG oldlen, sublen;
    char *p_sub, *p_start;
//    DWORD number;

    if ( ptext->buf_size < 0 || 
        ptext->focus_pos > ptext->buf_size)
        return;

    if (ch_code == VK_RETURN)
    {
        if (ptext->single_line)
            return;
        ch_code = '\n';
    }

    // 檢查數字是否出界
/*
    if ( ptext->number_only )
    {
        number = te_get_number( ptext );
        // ULONG_MAX        
    }
*/

    p_start = ptext->ptext_buf;
    
    oldlen = strlen(p_start);
    if (oldlen >= ptext->buf_size-1)
        return;


    sublen = strlen((const char*)ptext->ptext_next);
    if (sublen == 0)
    {
        ptext->ptext_buf[oldlen] = (char)ch_code;
        ptext->focus_pos++;
        ptext->ptext_next++;
        ptext->ptext_next[0] = '\0';
    }
    else
    {
        p_sub = (char*)LocalAlloc(LPTR, sublen);
        if (!p_sub)
            return;
        memcpy((void*)p_sub, (const void*)ptext->ptext_next, sublen);
        ptext->ptext_next[0] = ch_code;
        memcpy((void*)(ptext->ptext_next+1), (const void*)p_sub, sublen);
        LocalFree(p_sub);
        ptext->focus_pos++;
        ptext->ptext_next++;
        (ptext->ptext_next + sublen)[0] = '\0';
    }
}

// 插入一個字符串
void te_insert_str(LPUI_TEXT ptext, char* pstr)
{
    SLONG oldlen, sublen, iptlen;
    char *p_start, *buf;

    if ( ptext->buf_size < 0 || 
        ptext->focus_pos > ptext->buf_size)
        return;


    oldlen = strlen(ptext->ptext_buf);
    if (oldlen >= ptext->buf_size)
        return;

    //check last char
    p_start = te_next_char(pstr);
    if ( p_start - pstr >= 2 && (ptext->buf_size - oldlen <= 2) )
        return;
    
    p_start = ptext->ptext_buf;
    


    // get insert string size
    iptlen = strlen((const char*)pstr);
    if (iptlen + oldlen > ptext->buf_size)
    {
        iptlen = te_str_sub_len(pstr, ptext->buf_size-oldlen-1);
    }

    // insert pos.
    sublen = strlen((const char*)ptext->ptext_next);

    if (sublen == 0)
    {
        memcpy(ptext->ptext_next, pstr, iptlen);
        ptext->focus_pos += iptlen;
        ptext->ptext_next += iptlen;
        ptext->ptext_next[0] = '\0';
    }
    else
    {
        buf = (char*)LocalAlloc(LPTR, sublen);

        memcpy(buf, ptext->ptext_next, sublen);
        memcpy(ptext->ptext_next, pstr, iptlen);
        memcpy(ptext->ptext_next+iptlen, buf, sublen);

        LocalFree(buf);
        ptext->focus_pos += iptlen;
        ptext->ptext_next += iptlen;
        (ptext->ptext_next+sublen)[0] = '\0';
    }
}

// 橫向滾動設置
void te_enable_v_scroll(LPUI_TEXT ptext, BOOL enable)
{
    if ( ptext )    
        ptext->h_scroll = enable;
}


SLONG te_str_sub_len(char* pstr, SLONG max_len)
{
    int result, d;
    char *p;
    char *p_old;

    if (pstr == NULL)
        return NULL;

    p_old = p = pstr;
    result = d = 0;

    while (p[0] != '\0' && p[0] != '\n')
    {
        p = te_next_char(p);
        d = (DWORD)p - (DWORD)p_old;
        p_old = p;
        if ((result + d) > max_len)
            break;
        result += d;
    }
    return result;
}


void    te_del_ch(LPUI_TEXT ptext)
{
    SLONG sublen;
    char *p;
    char *pnew;

    if (!te_available(ptext) || '\0' == ptext->ptext_next[0])
        return;

    p = ptext->ptext_next;
    pnew = te_next_char(p);

    sublen = strlen(pnew);
    memmove(p, pnew, sublen+1);
}

// 根據光標的位置確定插入點
void te_update_pos_by_caret(LPUI_TEXT ptext)
{
    UI_TEXT_CARET *c;
    SLONG j, ln, slen, result, n;
    SLONG *f;
    SLONG col;
    char *pc;

    c = &ptext->caret_pos;
    f = &ptext->focus_pos;

    if ( ptext->h_scroll )
    {
        *f = c->col;
    }
    else
    {
        
        n = result = j = 0;
        pc = ptext->ptext_buf;
        ln = ptext->w/ptext->font_w_half;
        slen = strlen(ptext->ptext_buf);
        col = c->col;

        while(1)
        {
            if (j == c->lnum)
            {
                ln = col<=ln?col:ln;
                result += te_str_sub_len(pc, ln);
                break;
            }
            
            n = te_str_sub_len(pc, ln);
            result += n;
            pc += n;
            if (pc[0] == '\n')
            {
                pc++;
                result++;
            }
            if (result >= slen)
            {
                result = slen;
                break;
            }
            j++;
        }
        *f = result;
    }
    te_update_left_col( ptext );
    te_ime_update_pos( ptext );
}

/*
// 根據插入點的位置確定光標的位置
void te_update_caret_by_pos(LPUI_TEXT ptext)
{
    UI_TEXT_CARET *c;
    SLONG j, ln, slen, n, s;
    SLONG *f;
    char *p;

    c = &ptext->caret_pos;
    f = &ptext->focus_pos;

    ln = n = j = 0;
    slen = strlen(ptext->ptext_buf);
    s = te_get_max_line(ptext);
    p = ptext->ptext_buf;

    for (j = 0; j < s; j++)
    {
        n = te_get_line_len(ptext, j);

        if ( ptext->focus_pos - ln <= n)
        {
            break;
        }
        ln += n;
        if (p[ln] == '\n')
            ln ++;
    }
    c->lnum = j;
    c->col = ptext->focus_pos - ln;

    te_ime_update_pos( ptext );
}
*/
// 根據插入點的位置確定光標的位置
void te_update_caret_by_pos(LPUI_TEXT ptext)
{
    UI_TEXT_CARET *c;
    SLONG j, ln, slen, n, s;
    SLONG *f;
    char *p;

    c = &ptext->caret_pos;
    f = &ptext->focus_pos;

    ln = n = j = 0;
    slen = strlen(ptext->ptext_buf);
    s = te_get_max_line(ptext);
    p = ptext->ptext_buf;

    if ( !ptext->h_scroll )
    {
        for (j = 0; j < s; j++)
        {
            n = te_get_line_len(ptext, j);
            
            if ( ptext->focus_pos - ln <= n)
            {
                break;
            }
            ln += n;
            if (p[ln] == '\n')
                ln ++;
        }
        c->lnum = j;
        c->col = ptext->focus_pos - ln;
    }
    else
    {
        c->lnum = 0;
        c->col = ptext->focus_pos;
    }

    te_update_left_col( ptext );
    te_ime_update_pos( ptext );
}


// 更新顯示區的第一行
void te_update_topline(LPUI_TEXT ptext)
{
    SLONG n;
    UI_TEXT_CARET *c;
    SLONG *tl;

    if ( !ptext )
        return;
    
    c  = &ptext->caret_pos;
    tl = &ptext->top_line;
    n  = ptext->h/ptext->font_h - 1;

    if (c->lnum < *tl)
        *tl = c->lnum;
    else if (c->lnum  - n > *tl)
        *tl = c->lnum - n;

    ptext->caret_timer    = 0;
}

// 更新顯示區的第一列
void te_update_left_col( LPUI_TEXT ptext )
{
    UI_TEXT_CARET *c;
    SLONG *lc;
    SLONG n;
    CHAR *pstr;

    if ( !ptext->h_scroll )
        return;

    c = &ptext->caret_pos;
    lc = &ptext->left_col;
    n = ptext->w/ptext->font_w_half;

    if ( c->col < *lc )
        *lc = c->col;
    else if ( c->col - n > *lc )
        *lc = c->col - n;

    n = 0;
    pstr = ptext->ptext_buf;

    while ( n < *lc )
    {
        pstr = te_next_char( pstr );
        n = pstr - ptext->ptext_buf;
    }

    *lc = n;
}

// 獲得指定行的長度
SLONG    te_get_line_len(LPUI_TEXT ptext, SLONG line)
{
    SLONG i, n, w, s, slen;
    char *p;

    p = ptext->ptext_buf;
    w = ptext->w/ptext->font_w_half;
    slen = strlen(p);
    s = 0;
    i = 0;

    while (i <= line)
    {
        if (s >= slen)
        {
            n = 0;
            break;
        }
        n = te_str_sub_len(p+s, w);
        s += n;
        if (p[s] == '\n')
            s++;
        i++;
    }
    return n;
}


// 獲得最寬行的長度
SLONG   te_get_max_line(LPUI_TEXT ptext)
{
    SLONG i, n, w, s, slen;
    char *p;

    p = ptext->ptext_buf;
    w = ptext->w/ptext->font_w_half;
    slen = strlen(p);
    s = 0;
    i = 0;

    while (s < slen)
    {
        n = te_str_sub_len(p+s, w);
        s += n;
        if (p[s] == '\n')
            s ++;
        i++;
    }

    return i;
}

// 將字符串轉換為數字(只支持整型)
SLONG te_get_number( LPUI_TEXT ptext )
{
    SLONG result;
    CHAR *temp;
    
    if ( !ptext )
        return 0;

    if ( !ptext->single_line || !ptext->number_only )
        return 0;
    
    result = strtoul( ptext->ptext_buf, &temp, 10 );

    return result;
}

// 如果 te_list.focus 為空則將 ptext 設為焦點
VOID   te_set_focus( LPUI_TEXT ptext )
{
    if ( !te_list.focus )
    {
        te_list_set_focus( ptext );
    }
}

// 將 ptext 強制設為焦點
VOID   te_force_set_focus( LPUI_TEXT ptext )
{
    te_list_set_focus( ptext );
}

// 返回輸入焦點結構指針
UI_TEXT *te_get_focus( VOID )
{
    return te_list.focus;
}


// 獲得顯示區的行數
SLONG te_get_show_line(LPUI_TEXT ptext)
{
    if (!te_available(ptext))
        return -1;
    return (ptext->h/ptext->font_h);
}


// 獲得指定行的起始指針
char* te_get_line_start(LPUI_TEXT ptext, SLONG line)
{
    char *p;
    SLONG ln, ll, i;
    
    ln = te_get_max_line(ptext);
    if (line > ln)
        return NULL;

    p = ptext->ptext_buf;

    for (i = 0; i < line; i++)
    {
        ll = te_get_line_len(ptext, i);
        p += ll;
        if (p[0] == '\n')
            p ++;
    }
    return p;
}


// 畫編輯區
void te_draw( LPUI_TEXT ptext, BOOL show_caret, BMP *bitmap)
{
    SLONG hb, hm, i, x, y;
//    static timer = 0;

    if (!te_available(ptext))
        return;


    hb = te_get_show_line(ptext);


    hm = te_get_max_line(ptext) - ptext->top_line;
    hm = hm < hb?hm:hb;

    for (i = 0; i < hm; i++)
        te_draw_line( ptext, i, bitmap);


    ptext->caret_timer++;

    // 畫光標
    if ( show_caret
        && ptext->caret_pos.lnum >= ptext->top_line 
        && ptext->caret_pos.lnum < hb+ptext->top_line
        && !(ptext->read_only) )
    {
        if (!(ptext->caret_timer&TE_CARET_TIMER))
        {
            x = ptext->x + ( ptext->caret_pos.col - ptext->left_col ) * ptext->font_w_half;
            y = ptext->y + (ptext->caret_pos.lnum-ptext->top_line)*ptext->font_h;
            put_bar(x, y, 2, ptext->font_h, TE_CARET_COLOR, bitmap);
        }
    }
}

// 畫一行
void te_draw_line( LPUI_TEXT ptext, SLONG line, BMP *bitmap )
{
    CHAR *tp;
    SLONG n, y;
    SLONG max_char;
    static CHAR buf[512];

    if ( ptext->single_line )
    {
        if ( ptext->h_scroll )
        {
            tp = ptext->ptext_buf + ptext->left_col;

            n = te_str_sub_len( tp, ptext->w/ptext->font_w_half );
            
            memcpy( buf, tp, n );
            buf[n] = '\0';

            y = ptext->y;
        }
        else
        {

            tp = ptext->ptext_buf;
            n = strlen( tp );
            max_char = ptext->w/ptext->font_w_half;
            n = MIN( n, max_char );
            n = MIN( n, 511 );

            memcpy( buf, tp, n );

            buf[n] = '\0';

            y = ptext->y;
        }
    }
    else
    {
        n = te_get_line_len( ptext, ptext->top_line + line );

        tp = te_get_line_start(ptext, ptext->top_line + line);

        max_char = ptext->w/ptext->font_w_half;

        n = MIN( n, max_char );
        n = MIN( n, 511 );

        memcpy(buf, tp, n);

        buf[n] = '\0';

        y = line * ptext->font_h + ptext->y;

    }

    // 文字選擇
    if ( te_list.focus == ptext )
        te_draw_sel_bar( ptext, line, n, bitmap );

    set_word_color(0, ptext->text_color);

    switch (ptext->font_size)
    {
        case TE_FONT_SIZE_12:
            print12( ptext->x, y, (USTR*)buf, PEST_PUT, bitmap);
            break;
        case TE_FONT_SIZE_16:
            print16( ptext->x, y, (USTR*)buf, PEST_PUT, bitmap);
            break;
        case TE_FONT_SIZE_20:
            print20( ptext->x, y, (USTR*)buf, PEST_PUT, bitmap);
            break;
        case TE_FONT_SIZE_24:
            print24( ptext->x, y, (USTR*)buf, PEST_PUT, bitmap);
            break;
        case TE_FONT_SIZE_28:
            print28( ptext->x, y, (USTR*)buf, PEST_PUT, bitmap);
            break;
        case TE_FONT_SIZE_32:
            print32( ptext->x, y, (USTR*)buf, PEST_PUT, bitmap);
            break;
        default:
            break;
    }

    set_word_color( 0, SYSTEM_WHITE);
}

// 畫選中標記
void te_draw_sel_bar( LPUI_TEXT ptext, SLONG line, SLONG n, BMP *bitmap )
{
    SLONG bx, bw;
    UI_TEXT_CARET start;
    UI_TEXT_CARET end;

    
    if ( ptext->sel_start.lnum != ptext->sel_end.lnum 
         || ptext->sel_start.col != ptext->sel_end.col ) 
    {
        if ( ptext->sel_start.lnum < ptext->sel_end.lnum 
            || ( ptext->sel_start.lnum == ptext->sel_end.lnum 
                 && ptext->sel_start.col <= ptext->sel_end.col ) )
        {
            // 從前向後選擇
            start = ptext->sel_start;
            end = ptext->sel_end;
            if ( ptext->h_scroll )
            {
                start.col -= ptext->left_col;
                end.col -= ptext->left_col;
                if ( start.col < 0 )
                    start.col = 0;
            }
        }
        else
        {
            // 從後向前選擇
            start = ptext->sel_end;
            end = ptext->sel_start;
            if ( ptext->h_scroll )
            {
                end.col -= ptext->left_col;
                start.col -= ptext->left_col;
                if ( end.col > ptext->w/ptext->font_w_half )
                    end.col = ptext->w/ptext->font_w_half;
            }
        }
        
        if ( line < start.lnum || line > end.lnum )
            return;

        if ( line == start.lnum && line == end.lnum )
        {
            bx = ptext->x + start.col * ptext->font_w_half;
            bw = ( end.col - start.col ) * ptext->font_w_half;
        }
        else if ( line == start.lnum )
        {
            bx = ptext->x + start.col * ptext->font_w_half;
            bw = ( n - start.col ) * ptext->font_w_half;
        }
        else if ( line == end.lnum )
        {
            bx = ptext->x;
            bw = end.col * ptext->font_w_half;
        }
        else
        {
            bx = ptext->x;
            bw = n * ptext->font_w_half;
        }

        put_bar( bx, ptext->y+ line*ptext->font_h, bw, ptext->font_h, TE_SELECTED_BK_COLOR, bitmap );
    }
}

// 設置文字顏色
void    te_set_color(LPUI_TEXT ptext, PIXEL color)
{
    if ( ptext )
        ptext->text_color = color;
}


// 設置編輯區是否可見
void te_set_active( LPUI_TEXT ptext, BOOL b_active )
{
    if ( ptext )
    {
        ptext->active = b_active;
        ptext->caret_timer = 0;
    }

}

// 設置編輯區是否為單行
void te_set_single_line( LPUI_TEXT ptext, BOOL b_active )
{
    if ( ptext )
        ptext->single_line = b_active;
}


// 設置光標的位置
void    te_set_caret(LPUI_TEXT ptext, SLONG lnum, SLONG col)
{
    if ( ptext )
    {
        ptext->caret_pos.col = col;
        ptext->caret_pos.lnum = lnum;
    }
}


// 設置是否只接受數字輸入
void te_set_number_only(LPUI_TEXT ptext, BOOL number_only)
{
    if ( ptext )
        ptext->number_only = number_only;
}


// 設置是否只讀
void te_set_read_only( LPUI_TEXT ptext, BOOL read_only )
{
    if ( ptext )
        ptext->read_only = read_only;
}

// 設置編輯區左上角的位置
void    te_set_xy( LPUI_TEXT ptext, SLONG x, SLONG y )
{
    if ( ptext )
    {
        ptext->x = x;
        ptext->y = y;
    }
}

// 設置編輯區的寬和高
void    te_set_wh(LPUI_TEXT ptext, SLONG w, SLONG h)
{
    if ( ptext )
    {
        ptext->w = w;
        ptext->h = h;
    }
}

// 獲得文字串的大小
SLONG te_get_size(LPUI_TEXT ptext)
{
    if ( ptext )
        return strlen(ptext->ptext_buf);
    else
        return -1;
}


// 獲得當前顯區的第一行行號
SLONG te_get_top_line(LPUI_TEXT ptext)
{
    if ( ptext )
        return ptext->top_line;
    else
        return -1;
}

// 設置當前顯區的第一行行號
void te_set_top_line(LPUI_TEXT ptext, SLONG top_line)
{
    if ( ptext && top_line >= 0 && top_line < te_get_max_line( ptext ) )
        ptext->top_line = top_line;
}


// 設置編輯區的文字
void te_set_text(LPUI_TEXT ptext, char *p_buf)
{
    if ( ptext )
    {
        if ( p_buf )
            lstrcpyn( ptext->ptext_buf, p_buf, ptext->buf_size );
        else
        {
            ptext->ptext_buf[0]        = '\0';
            ptext->ptext_next        = ptext->ptext_buf;
            ptext->caret_pos.col    = 0;
            ptext->caret_pos.lnum    = 0;
            ptext->focus_pos        = 0;
        }
    }
}


// 文字的複製操作
void te_copy(LPUI_TEXT ptext)
{
}

// 文字的剪切操作
void    te_cut(LPUI_TEXT ptext)
{
}

// 文字的粘貼操作
void    te_paste(LPUI_TEXT ptext)
{
}


// 選中文字的刪除操作
void    te_delete(LPUI_TEXT ptext)
{
    SLONG a;
    UI_TEXT_CARET *s, *e;

    s = &ptext->sel_start;
    e = &ptext->sel_end;

    if (s->col == e->col && s->lnum == e->lnum)
        return;

    if (s->lnum > e->lnum)
    {
        a = s->lnum;
        s->lnum = e->lnum;
        e->lnum = a;
    }
    /* 鳳腕弇离 */

}


// 設置編輯區文字的大小
void te_set_font_size(LPUI_TEXT ptext, UI_EDIT_FONT fsize)
{
    if ( ptext )
    {
        ptext->font_size    = fsize;
        ptext->font_h        = fsize;
        ptext->font_w_half    = fsize/2;
    }
}


// 獲得編輯區文字的大小
SLONG te_get_font_size(LPUI_TEXT ptext)
{
    if ( ptext )
        return ptext->font_size;
    else
        return 0;
}


// 獲得字符串中下一個字符的位置
char *te_next_char(const char *p)
{
    char *result  = NULL;
    if (p)
    {
        result = CharNext(p);
    }
    return result;
}

// 獲得字符串中上一個字符的位置
char *te_prev_char(const char *pstart, const char *p)
{
    char *result = NULL;
    if (p && pstart)
    {
        result = CharPrev(pstart, p);
    }
    return result;
}

// 按下 shift 時選擇文字
void te_update_select( LPUI_TEXT ptext )
{
    SHORT state1, state2;
    
    state1 = GetKeyState( VK_LSHIFT );
    state2 = GetKeyState( VK_RSHIFT );

    if ( ( state1 & 0x8000 ) || ( state2 & 0x8000 ) )
    {
        ptext->sel_end = ptext->caret_pos;
    }
    else
    {
        ptext->sel_start = ptext->caret_pos;
        ptext->sel_end = ptext->caret_pos;
    }

}

/************************************************************************/
/* 輸入法函數                                                           */
/************************************************************************/

void te_ime_update_pos( LPUI_TEXT ptext )
{
    HIMC hImc;
    POINT pt;
    COMPOSITIONFORM cf;

    if ( te_list.focus != ptext )
        return;

    hImc = ImmGetContext( g_hDDWnd );
    if ( hImc )
    {
        if ( ptext->h_scroll )
            pt.x = ( ptext->caret_pos.col - ptext->left_col )* ptext->font_w_half + ptext->x;
        else
            pt.x = ptext->caret_pos.col * ptext->font_w_half + ptext->x;

        pt.y = ptext->caret_pos.lnum * ptext->font_h + ptext->y;
        
        cf.dwStyle = CFS_POINT;
        cf.ptCurrentPos = pt;

        ImmSetCompositionWindow( hImc, &cf);
        ImmReleaseContext( g_hDDWnd, hImc );
    }
}

void te_ime_set_font( VOID )
{
    if ( !te_list.focus )
        return;

    HIMC hImc = ImmGetContext( g_hDDWnd );
    if ( hImc )
    {
        LOGFONT lf;

        ImmGetCompositionFont( hImc, &lf );
        lf.lfHeight = -te_list.focus->font_h;
        ImmSetCompositionFont( hImc, &lf );
        ImmReleaseContext( g_hDDWnd, hImc );
    }
}

SLONG    te_ime_is_open( void )
{
    SLONG    result;
    HIMC hImc = ImmGetContext( g_hDDWnd );
    if ( hImc )
    {
        result = ImmGetOpenStatus( hImc );
        ImmReleaseContext( g_hDDWnd, hImc );
    }
    return result;
}

void    te_ime_update_hkl( void )
{
    hKL = GetKeyboardLayout( 0 );
}

void        te_ime_set_open( BOOL open )
{
    HIMC hImc = ImmGetContext( g_hDDWnd );
    if ( hImc )
    {
        ImmSetOpenStatus( hImc, open );
        ImmReleaseContext( g_hDDWnd, hImc );
    }
}

/************************************************************************/
/* 輸入區鏈表控制函數                                                   */
/************************************************************************/

VOID te_list_clear( VOID )
{
    memset( &te_list, 0, sizeof( te_list ) );
}


// 返回編輯區的索引值，失敗返回-1
SLONG te_list_add( UI_TEXT *ptext )
{
    if ( te_list.count >= TE_MAX_LIST && !ptext )
        return -1;

    te_list.list[te_list.count] = ptext;
    te_list.count++;

    return te_list.count - 1;
}

SLONG te_list_index( UI_TEXT *ptext )
{
    DWORD i;
    if ( !ptext )
        return -1;
    
    for( i = 0; i < te_list.count; i ++ )
    {
        if ( te_list.list[i] == ptext )
            return i;
    }

    return -1;
}

// 返回零表示刪除成功
SLONG te_list_del( SLONG index )
{
    if ( index < 0 || index >= TE_MAX_LIST )
        return TTN_NOT_OK;

    if ( te_list.list[index] )
    {
        if ( te_list.focus == te_list.list[index] )
            te_list_set_focus( -1 );
        
        while( te_list.list[index] )
        {
            if ( index == TE_MAX_LIST -1 )
                te_list.list[index] = 0;
            else
                te_list.list[index] = te_list.list[index+1];
            
            index++;
        }
        
        te_list.count--;
        
        return TTN_OK;
    }

    return TTN_NOT_OK;
}

// 獲得 index 所對應的編輯區指針
UI_TEXT *te_list_get( SLONG index )
{
    if ( index < 0 || index >= TE_MAX_LIST )
        return NULL;

    return te_list.list[index];
}

// 將 index 所對應的編輯區設為焦點
VOID te_list_set_focus( SLONG index )
{
    if ( index < 0 || index >= TE_MAX_LIST )
    {
        te_list.focus = NULL;
        te_ime_set_open( FALSE );
        return;
    }

    if ( te_list.list[index] )
    {
        te_list.focus = te_list.list[index];
        hKL = GetKeyboardLayout(0);
        
        if ( te_list.focus->caret_pos.col < te_list.focus->left_col )
            te_list.focus->left_col = te_list.focus->caret_pos.col;

        if ( te_list.focus->number_only || te_list.focus->read_only )
        {
            te_ime_set_open( FALSE );
        }
        else
        {
            if ( ImmIsIME( hKL ) )
            {
                te_ime_set_font( );
                te_ime_set_open( TRUE );
            }
        }
    }
    
}

VOID te_list_set_focus( UI_TEXT *ptext )
{
    if ( !ptext )
    {
        te_list.focus = NULL;
        te_ime_set_open( FALSE );
        return;
    }
    
    te_list.focus = ptext;

    hKL = GetKeyboardLayout( 0 );

    if ( ptext->h_scroll )
    {
        if ( te_get_size( ptext ) == 0 )
        {
            ptext->left_col = 0;
            ptext->caret_pos.col = 0;
        }
    }

    if ( te_list.focus->number_only || te_list.focus->read_only )
    {
        te_ime_set_open( FALSE );
    }
    else
    {
        if ( ImmIsIME( hKL ) )
        {
            te_ime_set_font( );
            te_ime_set_open( TRUE );
        }
    }
}
