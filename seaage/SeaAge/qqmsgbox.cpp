/*
 * qqmsgbox.cpp
 * functions for qq friend list
 * Zhang Zhaohui
 * 2002.10.9
 */

#include "qqmsgbox.h"
#include "qqedit.h"
#include "ImageRim.h"
#include "CRange.h"
#include "ErrorMsg.h"

// DEFINE //////////////////////////////////////
#define MB_NORMAL_COLOR                SYSTEM_BLACK
#define MB_WARNING_COLOR            SYSTEM_RED
#define MB_QUESTION_COLOR            SYSTEM_BLUE
#define MB_INFORMATION_COLOR        SYSTEM_YELLOW

#define MB_MAX_COUNT                32
#define MB_MAX_COL                    50
#define MB_MAX_LINE                    25

#define MB_MAX_BUTTON_FRAME            20

#define MB_TEXT_MAX_LINE            40
#define MB_TEXT_DEFAULT_FONT        TE_FONT_SIZE_12

#define MB_DEFAULT_W                300

#define MB_BUTTON_SPACE                20    // 两个按钮之间的间隔


// GLOBAL //////////////////////////////////////

BOOL                mb_inited = FALSE;
BOOL                mb_active;
UIMB_LIST_HEADER    mb_header;
UI_TEXT                *mb_ptext;
UIMB_DATA            mb_data;

CAKE_FRAME_ANI        *btn_cfa = NULL;    // button cake cfa
CAKE_FRAME            *btn_cf[MB_MAX_BUTTON_FRAME];
SLONG                btn_w;                // button width
SLONG                btn_h;                // button height

/***************************************
 *
 *
 *  static fucntions declare
 *
 *
 **************************************/

LPUIMB_LIST new_msgbox_list(void);
void        del_msgbox_list(LPUIMB_LIST p);
void        next_msgbox(void);
void        add_msgbox_to_list(LPUIMB_LIST p);
void        refresh_text(LPUIMB_LIST p);

void draw_msgbox_button(SLONG x, 
                        SLONG y, 
                        SLONG id,
                        BMP *bitmap);

/***************************************
 *
 *
 *  Global function
 *
 *
 **************************************/


int init_ui_msgbox(void)
{
    SLONG tw, th;
    USTR btn_filename[] = "menu\\msgboxbn.cak";
    SLONG count, valid_count, i;
    CAKE_FRAME_ANI  *cfa;

    mb_active = TRUE;
    mb_header.p_data = NULL;
    mb_header.count = 0;

    tw = MB_DEFAULT_W;
    th = MB_TEXT_MAX_LINE * MB_TEXT_DEFAULT_FONT;

    mb_ptext = te_create( 0, 0, tw, th, MB_MAX_CHAR );

    te_set_active( mb_ptext, TRUE );
    te_set_read_only( mb_ptext, TRUE );

    if (TTN_OK != load_cake_frame_ani_from_file( btn_filename, &btn_cfa ) )
    {
        log_error( 1, "ERROR: Open file failed. ( %s )", btn_filename );
        return TTN_NOT_OK;
    }
    count = count_cake_frames( btn_cfa );
    valid_count = min( count, MB_MAX_BUTTON_FRAME );

    for ( i = 0; i <    valid_count; i++ )
    {
        cfa = get_specify_cake_frame_ani( btn_cfa, i );
        btn_cf[i] = cfa->cake_frame;
    }

    btn_w = btn_cf[0]->rle->w;
    btn_h = btn_cf[0]->rle->h;

    mb_data.active_id    = 0;
    mb_data.active_id    = 0;

    mb_inited = TRUE;

    return 0;
}

void active_ui_msgbox(int active)
{
    mb_active = active;
}

void free_ui_msgbox(void)
{
    DWORD i;
    UIMB_LIST *p, *pl;

    pl = mb_header.p_data;

    te_destroy( mb_ptext );

    for (i = 0; i < mb_header.count; i++)
    {
        if (pl)
        {
            p = pl->p_next;
            del_msgbox_list(pl);
            pl = p;
        }
    }

    if ( btn_cfa )
    {
        destroy_cake_frame_ani( &btn_cfa );
        btn_cfa = NULL;
    }
}

void refresh_ui_msgbox(void)
{
    LPUIMB_LIST p;
    DWORD now_time;

    // check current message box if time out
    if (mb_header.p_data)
    {
        p = mb_header.p_data;
        if ( ( p->list.msgbox_type == UIMB_MESSAGE ) && p->list.disp_time)
        {
            now_time = timeGetTime();
            if (now_time - p->list_ex.start_time >= p->list.disp_time)
                next_msgbox();
        }
    }
}

/*
 * redraw_ui_msgbox
 *        draw message box
 *
 */
void redraw_ui_msgbox(BMP *bitmap)
{
    LPUIMB_LIST p = mb_header.p_data;
    LPUIMB_DATA pd = &mb_data;
    SLONG x, y, xl, yl;
    SLONG event, id;
    SLONG rim_index;
    IMAGE_RIM_INFO rim_info = { 0, 0, 0, 0};

    if (!p)
        return;
    
    x = p->list_ex.x;
    y = p->list_ex.y;
    xl = p->list_ex.xl;
    yl = p->list_ex.yl;
    event = MSG_BOX_EVENT;

    // disable game_range
    if ( p->list.msgbox_type & UIMB_OWN_MOUSE )
        game_range.clear( );

    // background ------------------------------
    x = p->list_ex.x;
    y = p->list_ex.y;
    xl = p->list_ex.xl;
    yl = p->list_ex.yl;
    id = MSG_BOX_ID_BKGND;

    rim_index = set_rim_image( 1 );
    get_image_rim_info( 1, &rim_info );

    put_image_rim(x, y, xl, yl, bitmap);
    game_range.add( x - rim_info.left_gap, 
                    y - rim_info.top_gap, 
                    xl + rim_info.right_gap + rim_info.left_gap, 
                    yl + rim_info.bottom_gap + rim_info.top_gap, 
                    event, id);
    
    set_rim_image( rim_index );

    // text ------------------------------------
    redraw_te( mb_ptext, bitmap );


    // button ----------------------------------
    //y = p->list_ex.text_x + p->list_ex.text_h + p->list.font_size;
    y = p->list_ex.y + p->list_ex.yl;
    xl = btn_w;
    yl = btn_h;

    switch ( GET_MSGBOX_TYPE ( p->list.msgbox_type ) )
    {
    case UIMB_OK:
        x = p->list_ex.x + ((MB_DEFAULT_W - btn_w)>>1);
        id = MSG_BOX_ID_OK;
        draw_msgbox_button(x, y, id, bitmap);
        game_range.add(x, y, xl, yl, event, id);
        break;
    case UIMB_OKCANCEL:
        x = p->list_ex.x + ((MB_DEFAULT_W - 
                btn_w*2 - MB_BUTTON_SPACE)>>1);
        id = MSG_BOX_ID_OK;
        draw_msgbox_button(x, y, id, bitmap);
        game_range.add(x, y, xl, yl, event, id);

        x += btn_w + MB_BUTTON_SPACE;
        id = MSG_BOX_ID_CANCEL;
        draw_msgbox_button(x, y, id, bitmap);
        game_range.add(x, y, xl, yl, event, id);
        break;
    case UIMB_MESSAGE:
        break;
    case UIMB_YESNOCANCEL:
        x = p->list_ex.x + ((MB_DEFAULT_W - 
                btn_w*3 - MB_BUTTON_SPACE*2)>>1);
        id = MSG_BOX_ID_YES;
        draw_msgbox_button(x, y, id, bitmap);
        game_range.add(x, y, xl, yl, event, id);

        x += btn_w + MB_BUTTON_SPACE;
        id = MSG_BOX_ID_NO;
        draw_msgbox_button(x, y, id, bitmap);
        game_range.add(x, y, xl, yl, event, id);

        x += btn_w + MB_BUTTON_SPACE;
        id = MSG_BOX_ID_CANCEL;
        draw_msgbox_button(x, y, id, bitmap);
        game_range.add(x, y, xl, yl, event, id);
        break;
    case UIMB_YESNO:
        x = p->list_ex.x + ((MB_DEFAULT_W - 
                btn_w*2 - MB_BUTTON_SPACE)>>1);
        id = MSG_BOX_ID_YES;
        draw_msgbox_button(x, y, id, bitmap);
        game_range.add(x, y, xl, yl, event, id);

        x += btn_w + MB_BUTTON_SPACE;
        id = MSG_BOX_ID_NO;
        draw_msgbox_button(x, y, id, bitmap);
        game_range.add(x, y, xl, yl, event, id);
        break;
    case UIMB_RETRYCANCEL:
        x = p->list_ex.x + ((MB_DEFAULT_W - 
                btn_w*2 - MB_BUTTON_SPACE)>>1);
        id = MSG_BOX_ID_RETRY;
        draw_msgbox_button(x, y, id, bitmap);
        game_range.add(x, y, xl, yl, event, id);

        x += btn_w + MB_BUTTON_SPACE;
        id = MSG_BOX_ID_CANCEL;
        draw_msgbox_button(x, y, id, bitmap);
        game_range.add(x, y, xl, yl, event, id);
        break;
    default:
        break;
    }
    
}



SLONG    handle_ui_msgbox(UINT message, WPARAM wParam, LPARAM lParam)
{
    LPUIMB_DATA p = &mb_data;
    LPUIMB_LIST ph = mb_header.p_data;
    SLONG result = 1;
    SLONG mx, my, event, id;

    if ( mb_header.count == 0 )
        return result;

    if ( ph->list.msgbox_type & UIMB_OWN_KEY )
    {
        switch ( message )
        {
            case WM_KEYDOWN:
            case WM_KEYUP:
            case WM_CHAR:
            case WM_SYSKEYDOWN:
            case WM_SYSKEYUP:
                result = 0;
                break;
        }
    }

    if ( ph->list.msgbox_type & UIMB_OWN_MOUSE )
    {
        switch ( message )
        {
        case WM_MOVE:
        case WM_LBUTTONDOWN:
        case WM_LBUTTONUP:
        case WM_RBUTTONDOWN:
        case WM_RBUTTONUP:
        case WM_MBUTTONDOWN:
        case WM_MBUTTONUP:
            result = 0;
            break;
        }
    }

    get_mouse_position( &mx, &my );
    game_range.mapping(mx, my, &event, &id);
    
    if (MSG_BOX_EVENT != event)
    {
        if ( message == WM_LBUTTONUP )
            p->active_id = 0;
        p->hilight_id = 0;
        return result;
    }

    switch (message)
    {
        case WM_MOUSEMOVE:
            p->hilight_id = id;
            break;
        case WM_LBUTTONDOWN:
            if (id != MSG_BOX_ID_BKGND && id != MSG_BOX_ID_TEXT)
            {
                p->active_id = id;
                result = 0;
            }
            break;
        case WM_LBUTTONUP:
            if (p->active_id == id)
            {
                p->active_id = 0;
                p->hilight_id = 0;
                if ( ph->list.pfunc )
                    ph->list.pfunc( (DWORD)&ph->list.param, id);
                next_msgbox();
                result = 0;
            }
            p->active_id = 0;
            break;
        default:
            break;
    }
    return result;
}

SLONG msg_box(SLONG sx, SLONG sy, LPUIMSGBOX pmsgbox)
{
    LPUIMB_LIST p = NULL;
    UI_TEXT *tmp_ptext = NULL;
    SLONG tw, th;
    
    if (!mb_inited)
    {
        log_error(1, "Error: msgbox need be initialized.");
        return TTN_NOT_OK;
    }
    
    p = new_msgbox_list();
    if (p && pmsgbox)
    {
        CopyMemory(&p->list, pmsgbox, sizeof(UIMSGBOX));
        
        tw = p->list_ex.text_w = MB_DEFAULT_W;
        th = p->list_ex.text_h = MB_TEXT_MAX_LINE*p->list.font_size;
        
        tmp_ptext = te_create( 0, 0, tw, th, MB_MAX_CHAR );
        te_set_active( tmp_ptext, FALSE );
        te_set_text( tmp_ptext, p->list.text_info );
        te_set_font_size( tmp_ptext, (UI_EDIT_FONT)p->list.font_size);
        
        p->list_ex.yl = te_get_max_line( tmp_ptext) * p->list.font_size;
        
        te_destroy( tmp_ptext );
        
        p->list_ex.xl = MB_DEFAULT_W;
        
        if (sx < 0)
            sx = (SCREEN_WIDTH - p->list_ex.xl)>>1;
        if (sy < 0)
            sy = (SCREEN_HEIGHT - p->list_ex.yl)>>1;
        
        p->list_ex.x = sx;
        p->list_ex.y = sy;
        
        p->list_ex.text_x = sx;
        p->list_ex.text_y = sy;
        
        if (p->list.msgbox_type != UIMB_MESSAGE)
        {
            p->list_ex.yl += btn_h + p->list.font_size;
        }            
        
        te_set_xy( mb_ptext, p->list_ex.text_x, p->list_ex.text_y );
        te_set_wh( mb_ptext, p->list_ex.text_w, p->list_ex.text_h );
        add_msgbox_to_list(p);
        if (mb_header.count == 1)
        {
            refresh_text(p);
            p->list_ex.start_time = timeGetTime();
        }
    }
    return 0;
}

void    clean_msg_box( void )
{
    LPUIMB_LIST p;
    
    p = mb_header.p_data;
    
    while(p)
    {
        next_msgbox();
        p = mb_header.p_data;
    }
}


/***************************************
 *
 *
 *  static functions
 *
 *
 **************************************/

void next_msgbox(void)
{
    LPUIMB_LIST p;

    p = mb_header.p_data;
    if (p)
    {
        mb_header.p_data = p->p_next;
        mb_header.count--;
        del_msgbox_list(p);
        
        p = mb_header.p_data;        
        if (p)
        {
            p->list_ex.start_time = timeGetTime();
            refresh_text(p);
        }
    }
}

void add_msgbox_to_list(LPUIMB_LIST p)
{
    LPUIMB_LIST *tmp;

    if (p)
    {
        if (mb_header.count < MB_MAX_COUNT)
        {
            tmp = &mb_header.p_data;

            while (*tmp)
                tmp = &(*tmp)->p_next;

            *tmp = p;
            p->p_next = NULL;
            mb_header.count++;
        }
    }
}

LPUIMB_LIST new_msgbox_list(void)
{
    LPUIMB_LIST p_result;
    p_result = (LPUIMB_LIST)GlobalAlloc(GPTR, sizeof(UIMB_LIST));
    if (p_result)
        p_result->p_next = NULL;
    return p_result;
}

void del_msgbox_list(LPUIMB_LIST p)
{
    if (p)
    {
        GlobalFree(p);
        p = NULL;
    }
}

LPUIMSGBOX new_msgbox(void)
{
    LPUIMSGBOX p_result;

    p_result = (LPUIMSGBOX)GlobalAlloc(GPTR, sizeof(UIMSGBOX));

    if (p_result)
        ZeroMemory(p_result, sizeof(UIMSGBOX));
    p_result->font_size = TE_FONT_SIZE_12;
    return p_result;
}

void del_msgbox(LPUIMSGBOX p)
{
    if (p)
    {
        GlobalFree(p);
        p = NULL;
    }
}

void draw_msgbox_button( SLONG x, SLONG y, SLONG id, BMP *bitmap )
{
    SLONG frame;
    LPUIMB_DATA p = &mb_data;

    switch (id)
    {
    case MSG_BOX_ID_OK:
        frame = MSG_BOX_FRAME_OK;
        break;
    case MSG_BOX_ID_CANCEL:
        frame = MSG_BOX_FRAME_CANCEL;
        break;
    case MSG_BOX_ID_RETRY:
        frame = MSG_BOX_FRAME_RETRY;
        break;
    case MSG_BOX_ID_YES:
        frame = MSG_BOX_FRAME_YES;
        break;
    case MSG_BOX_ID_NO:
        frame = MSG_BOX_FRAME_NO;
        break;
    default:
        return;
    }

    if ( id == p->active_id )
        frame += 2;
    else if ( id == p->hilight_id )
        frame++;

    put_rle( x, y, btn_cf[frame]->rle, bitmap );

}

void refresh_text(LPUIMB_LIST p)
{
    if (p)
    {
        te_set_text( mb_ptext, p->list.text_info);
        te_set_font_size( mb_ptext, (UI_EDIT_FONT)p->list.font_size);
        te_set_wh( mb_ptext, p->list_ex.text_w, p->list_ex.text_h);
    }
}
