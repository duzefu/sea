/*
**    qq.cpp
**    QQ functions.
**
**    Jack, 2002/07/19.
**
**  Modified by ZZH, 2002.7.25
**    
**    add start and end function on each window, ZZH, 2002.10.9
*/

#include "mainfun.h"
#include "clientmain.h"
#include "ui.h"
#include "posdata.h"
#include "Map.h"
#include "qqmain.h"
#include "client_item.h"
#include "NetGE_Character.h"
#include "NetGE_event_def.h"


/******************************************************************************************************************/
/* DEFINE                                                                                                         */
/******************************************************************************************************************/

#define QQ_FONT_HEIGHT            12
#define QQ_FONT_WIDTH_HALF        6
#define QQ_FONT_HEIGHT_16         16
#define QQ_FONT_WIDTH_HALF_16     8
#define QQ_MAIN_LIST_COLOR        SYSTEM_BLUE
#define QQ_FIND_LIST_COLOR        SYSTEM_BLACK
#define QQ_CHAT_NAME_COLOR        SYSTEM_BLACK
#define QQ_CHAT_TEXT_LEN          200
#define QQ_VERIFY_INFO_COLOR      SYSTEM_BLACK

#define QQ_NAME_SIZE              16
#define QQ_GUILD_NAME_SIZE        16
#define QQ_COUNTRY_SIZE           16
#define QQ_LEVEL_SIZE             3

#define QQ_FACE_FLASH_SPEED       0x8
/******************************************************************************************************************/
/* GLOBALS                                                                                                        */
/******************************************************************************************************************/
UI_QQ           ui_qq;
UI_QQFACE       ui_qqface;
UI_QQMAIN       ui_qqmain;
UI_QQPOPUP      ui_qqpopup;
UI_QQCALLGM     ui_qqcallgm;
UI_QQCHAT       ui_qqchat;
UI_QQDETAIL     ui_qqdetail;
UI_QQFIND1      ui_qqfind1;
UI_QQFIND2      ui_qqfind2;
UI_QQFIND3      ui_qqfind3;
UI_QQITEM       ui_qqitem;
UI_QQLOG        ui_qqlog;
UI_QQSET        ui_qqset;
UI_QQVERIFY     ui_qqverify;
UI_QQLIST       ui_qqlist;
UI_QQHIS        ui_qqhis;


/************************************************************************/
/*  FUNCTION PROTOTYPE                                                    */
/************************************************************************/
SLONG   init_qq_face_image(void);
void    free_qq_face_image(void);
void    redraw_qq_face(SLONG sx, SLONG sy, SLONG face_index, SLONG effect, BMP *bitmap);

SLONG   init_qq_main_image(void);
void    free_qq_main_image(void);
void    redraw_qq_main(SLONG sx, SLONG sy, BMP *bitmap);

SLONG    qq_get_current_group(void);

SLONG   init_qq_popup_image(void);
void    free_qq_popup_image(void);
void    redraw_qq_popup(SLONG sx, SLONG sy, BMP *bitmap);

SLONG   init_qq_callgm_image(void);
void    free_qq_callgm_image(void);
void    redraw_qq_callgm(SLONG sx, SLONG sy, BMP *bitmap);
SLONG   qq_callgm_send_message(void);

SLONG   init_qq_chat_image(void);
void    free_qq_chat_image(void);
void    redraw_qq_chat(SLONG sx, SLONG sy, BMP *bitmap);
SLONG    send_chat_content(USTR* pid, USTR* pchat);

SLONG   init_qq_detail_image(void);
void    free_qq_detail_image(void);
void    redraw_qq_detail(SLONG sx, SLONG sy, BMP *bitmap);

SLONG   init_qq_find1_image(void);
void    free_qq_find1_image(void);
void    redraw_qq_find1(SLONG sx, SLONG sy, BMP *bitmap);

SLONG   init_qq_find2_image(void);
void    free_qq_find2_image(void);
void    redraw_qq_find2(SLONG sx, SLONG sy, BMP *bitmap);

SLONG   init_qq_find3_image(void);
void    free_qq_find3_image(void);
void    redraw_qq_find3(SLONG sx, SLONG sy, BMP *bitmap);

SLONG   init_qq_item_image(void);
void    free_qq_item_image(void);
void    redraw_qq_item(SLONG sx, SLONG sy, BMP *bitmap);

SLONG   init_qq_log_image(void);
void    free_qq_log_image(void);
void    redraw_qq_log(SLONG sx, SLONG sy, BMP *bitmap);

SLONG   init_qq_set_image(void);
void    free_qq_set_image(void);
void    redraw_qq_set(SLONG sx, SLONG sy, BMP *bitmap);

SLONG   init_qq_verify_image(void);
void    free_qq_verify_image(void);
void    redraw_qq_verify(SLONG sx, SLONG sy, BMP *bitmap);

SLONG   init_qq_list_image(void);
void    free_qq_list_image(void);
void    redraw_qq_list(SLONG sx, SLONG sy, BMP *bitmap);

SLONG   init_qq_his_image(void);
void    free_qq_his_image(void);
void    redraw_qq_his(SLONG sx, SLONG sy, BMP *bitmap);


void    qq_draw_text(SLONG sx, SLONG sy, SLONG xl, char* pstr, DWORD txt_color, BMP *bitmap);
void    qq_draw_hi_text(SLONG sx, SLONG sy, SLONG sl, char* pstr, DWORD txt_color, BMP *bitmap);
void    qq_draw_sel_text(SLONG sx, SLONG sy, SLONG sl, char* pstr, DWORD txt_color, BMP *bitmap);
void    qq_draw_text_16(SLONG sx, SLONG sy, SLONG sl, char* pstr, DWORD txt_color, BMP *bitmap);
VOID    qq_get_log_text( DWORD sid, DWORD index );

/************************************************************************/
/* MESSAGE FUNCATIONS                                                   */
/* mm ----- mouse move                                                  */
/* mu ----- mouse up                                                    */
/* md ----- mouse down                                                  */
/* mw ----- mouse wheel                                                 */
/* ch ----- char                                                        */
/************************************************************************/
void    redraw_qq_min(BMP *bitmap);
void    redraw_qq_list_item(SLONG sx, SLONG sy, SLONG icon_index, USTR *name, SLONG id, SLONG effect, BMP *bitmap);

SLONG   qq_main_on_mm(SLONG sx, SLONG sy, SLONG id);
SLONG   qq_main_on_md(SLONG sx, SLONG sy, SLONG button, SLONG id);
SLONG   qq_main_on_mu(SLONG sx, SLONG sy, SLONG button, SLONG id);

SLONG    qq_set_on_mm(SLONG sx, SLONG sy, SLONG id);
SLONG    qq_set_on_md(SLONG sx, SLONG sy, SLONG button, SLONG id);
SLONG    qq_set_on_mu(SLONG sx, SLONG sy, SLONG button, SLONG id);

SLONG    qq_detail_on_mm(SLONG sx, SLONG sy, SLONG id);
SLONG    qq_detail_on_md(SLONG sx, SLONG sy, SLONG button, SLONG id);
SLONG    qq_detail_on_mu(SLONG sx, SLONG sy, SLONG button, SLONG id);


SLONG   qq_chat_on_mm(SLONG sx, SLONG sy, SLONG id);
SLONG   qq_chat_on_md(SLONG sx, SLONG sy, SLONG button, SLONG id);
SLONG   qq_chat_on_mu(SLONG sx, SLONG sy, SLONG button, SLONG id);
void    qq_chat_start(void);
void    qq_chat_end(void);


SLONG   qq_callgm_on_mm(SLONG sx, SLONG sy, SLONG id);
SLONG   qq_callgm_on_md(SLONG sx, SLONG sy, SLONG button, SLONG id);
SLONG   qq_callgm_on_mu(SLONG sx, SLONG sy, SLONG button, SLONG id);
void    qq_callgm_start(void);
void    qq_callgm_end(void);

SLONG   qq_find1_on_mm(SLONG sx, SLONG sy, SLONG id);
SLONG   qq_find1_on_md(SLONG sx, SLONG sy, SLONG button, SLONG id);
SLONG   qq_find1_on_mu(SLONG sx, SLONG sy, SLONG button, SLONG id);
void    qq_find1_start(void);
void    qq_find1_end(void);

SLONG   qq_find2_on_mm(SLONG sx, SLONG sy, SLONG id);
SLONG   qq_find2_on_md(SLONG sx, SLONG sy, SLONG button, SLONG id);
SLONG   qq_find2_on_mu(SLONG sx, SLONG sy, SLONG button, SLONG id);
SLONG   qq_find2_search(void);
void    qq_find2_start(void);
void    qq_find2_end(void);


SLONG   qq_find3_on_mm(SLONG sx, SLONG sy, SLONG id);
SLONG   qq_find3_on_md(SLONG sx, SLONG sy, SLONG button, SLONG id);
SLONG   qq_find3_on_mu(SLONG sx, SLONG sy, SLONG button, SLONG id);
void    qq_find3_show_list(SLONG y, LPUI_QQFRIEND p, BMP *bitmap, SLONG flag);
void    qq_find3_start(void);
void    qq_find3_end(void);
void    qq_find3_add_friend(void);

SLONG   qq_log_on_mm(SLONG sx, SLONG sy, SLONG id);
SLONG   qq_log_on_md(SLONG sx, SLONG sy, SLONG button, SLONG id);
SLONG   qq_log_on_mu(SLONG sx, SLONG sy, SLONG button, SLONG id);


SLONG   qq_list_on_mm(SLONG sx, SLONG sy, SLONG id);
SLONG   qq_list_on_md(SLONG sx, SLONG sy, SLONG button, SLONG id);
SLONG   qq_list_on_mu(SLONG sx, SLONG sy, SLONG button, SLONG id);


SLONG   qq_popup_on_mm(SLONG sx, SLONG sy, SLONG id);
SLONG   qq_popup_on_md(SLONG sx, SLONG sy, SLONG button, SLONG id);
SLONG   qq_popup_on_mu(SLONG sx, SLONG sy, SLONG button, SLONG id);


SLONG   qq_item_on_mm(SLONG sx, SLONG sy, SLONG id);
SLONG   qq_item_on_md(SLONG sx, SLONG sy, SLONG button, SLONG id);
SLONG   qq_item_on_mu(SLONG sx, SLONG sy, SLONG button, SLONG id);
void    qq_item_start( void );
void    qq_item_end( void );

SLONG   qq_verify_on_mm(SLONG sx, SLONG sy, SLONG id);
SLONG   qq_verify_on_md(SLONG sx, SLONG sy, SLONG button, SLONG id);
SLONG   qq_verify_on_mu(SLONG sx, SLONG sy, SLONG button, SLONG id);
void    qq_verify_start(void);
void    qq_verify_end(void);

SLONG   qq_face_on_mm(SLONG sx, SLONG sy, SLONG id);
SLONG   qq_face_on_md(SLONG sx, SLONG sy, SLONG button, SLONG id);
SLONG   qq_face_on_mu(SLONG sx, SLONG sy, SLONG button, SLONG id);

SLONG   qq_his_on_mm(SLONG sx, SLONG sy, SLONG id);
SLONG   qq_his_on_md(SLONG sx, SLONG sy, SLONG button, SLONG id);
SLONG   qq_his_on_mu(SLONG sx, SLONG sy, SLONG button, SLONG id);
void    qq_his_start(void);
void    qq_his_end(void);

// qq MessageBox
void    qq_msgbox(DWORD event, char *title, char *text, DWORD type, DWORD time);

// MessageBox call this function for result
void    qq_msgbox_callback( DWORD param, SLONG result );

// Delete friend callback function
void qq_del_friend_callback( DWORD param, SLONG result );

/******************************************************************************************************************/
/* UI QQ FUNCTIONS                                                                                                */
/******************************************************************************************************************/
int     init_ui_qq(void)
{
    te_list_clear();        // 清空編輯區鏈表

    if(TTN_OK != init_qq_face_image())
        return  -1;
    if(TTN_OK != init_qq_main_image())
        return  -2;
    if(TTN_OK != init_qq_popup_image())
        return  -3;
    if(TTN_OK != init_qq_callgm_image())
        return  -4;
    if(TTN_OK != init_qq_chat_image())
        return  -5;
    if( TTN_OK != init_qq_detail_image())
        return -6;
    if( TTN_OK != init_qq_find1_image())
        return -7;
    if( TTN_OK != init_qq_find2_image())
        return -8;
    if( TTN_OK != init_qq_find3_image())
        return -9;
    if( TTN_OK != init_qq_item_image())
        return -10;
    if( TTN_OK != init_qq_log_image())
        return -11;
    if( TTN_OK != init_qq_set_image())
        return -12;
    if( TTN_OK != init_qq_verify_image())
        return -13;
    if( TTN_OK != init_qq_list_image())
        return -14;
    if (TTN_OK != init_qq_his_image())
        return -15;
    if( TTN_OK != init_qf())
        return -16;
    if (TTN_OK != init_qq_search())
        return -17;
    if (TTN_OK != init_qh())
        return -18;
    if (TTN_OK != init_qq_chat())
        return -19;
    if ( TTN_OK != ql_init( ) )
    {
        log_error( 1, "Chat save module init failed.!" );
        return -20;
    }

    ui_qq.curr_state_id = QQ_MAXIMIZE;
//    ui_qq.input_focus    = 0;
    ui_qq.end_func        = NULL;
    ui_qq.total_players = 0;

    return  0;
}


void    active_ui_qq(int active)
{
}


void    free_ui_qq(void)
{
    ql_free( );
    free_qq_chat();
    free_qq_his_image();
    free_qq_list_image();
    free_qq_verify_image();
    free_qq_set_image();
    free_qq_log_image();    
    free_qq_item_image();
    free_qq_find3_image();
    free_qq_find2_image();
    free_qq_find1_image();
    free_qq_detail_image();
    free_qq_chat_image();
    free_qq_callgm_image();
    free_qq_popup_image();
    free_qq_main_image();
    free_qq_face_image();
    free_qf();
    free_qq_search();
    free_qh();
}


void    refresh_ui_qq(void)
{
    // TODO: [7/22/2002]
}


/*
 *    Free friend's information, and player's settings
 */
void    qq_clear(void)
{
    /* TODO:    Free friend's information, reset player settings 
     *            clear qq_search
     *            logout qq_local */
    qfl_clear_all();
    qq_search_clear();
    ql_on_logout();
    qfm_clear();
    qq_chat_clear();
    qq_chat_end();    
    qq_callgm_end();
    qq_find1_end();
    qq_find2_end();
    qq_find3_end();
    qq_item_end();
    clean_msg_box();

}

void redraw_ui_qq(BMP *bitmap)
{
    SLONG   main_sx, main_sy;
    
    // TODO: [7/22/2002]
    main_sx = main_sy = 0;
    if( ui_qq.curr_state_id == QQ_MINIMIZE)
        redraw_qq_min(bitmap);
    else
        redraw_qq_main(main_sx, main_sy, bitmap);
    ui_qq.face_flash++;
}


//畫最小化QQ
void    redraw_qq_min( BMP *bitmap)
{
    UI_QQMAIN *data = &ui_qqmain;
    CAKE_FRAME  *cf;
    SLONG   event, id, frame, x, y;
    
    if(!data)
        return;
    event = QQMAIN_EVENT;
    
    id = QQMAIN_ID_MAXIMIZE;
    frame = QQMAIN_FRAME_MAXIMIZE;
    cf = data->cf[frame];
    if(uimap_data.minimap_alpha == 0)
    {
        x = SCREEN_WIDTH - cf->rle->w;
        y = cf->rle->h;
    }
    else
    {
        x = QQMAIN_MAX_SX;
        y = QQMAIN_MAX_SY;
    }
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);
    
}


//
SLONG handle_ui_qq(UINT message, WPARAM wParam, LPARAM lParam)
{
    SLONG sx, sy, event, id, result;
    
    result = 1;

    handle_combobox( message, wParam, lParam );    
    
    switch( message)
    {
    case WM_MOUSEMOVE:

        if ( ((wParam&MK_LBUTTON) || (wParam&MK_RBUTTON))
             && !ui_qq.button_down )
             break;

        sx = GET_X_LPARAM(lParam);
        sy = GET_Y_LPARAM(lParam);
        event = id = 0;
        game_range.mapping(sx, sy, &event, &id);

        switch( event)
        {
        case QQMAIN_EVENT:
            result = qq_main_on_mm(sx, sy, id);
            break;
        case QQCALLGM_EVENT:
            result = qq_callgm_on_mm(sx, sy, id);
            break;
        case QQSET_EVENT:
            result = qq_set_on_mm(sx, sy, id);
            break;
        case QQFIND1_EVENT:
            result = qq_find1_on_mm(sx, sy, id);
            break;
        case QQDETAIL_EVENT:
            result = qq_detail_on_mm(sx, sy, id);
            break;
        case QQCHAT_EVENT:
            result = qq_chat_on_mm(sx, sy, id);
            break;
        case QQLIST_EVENT:
            result = qq_list_on_mm(sx, sy, id);
            break;
        case QQLOG_EVENT:
            result = qq_log_on_mm(sx, sy, id);
            break;
        case QQITEM_EVENT:
            result = qq_item_on_mm(sx, sy, id);
            break;
        case QQPOPUP_EVENT:
            result = qq_popup_on_mm(sx, sy, id);
            break;
        case QQFIND2_EVENT:
            result = qq_find2_on_mm(sx, sy, id);
            break;
        case QQFIND3_EVENT:
            result = qq_find3_on_mm(sx, sy, id);
            break;
        case QQFACE_EVENT:
            result= qq_face_on_mm(sx, sy, id);
            break;
        case QQVERIFY_EVENT:
            result = qq_verify_on_mm(sx, sy, id);
            break;
        case QQHIS_EVENT:
            result = qq_his_on_mm(sx, sy, id);
            break;
        default:
            ui_qqmain.hilight_id     = 0;
            ui_qqpopup.hilight_id    = 0;
            ui_qqcallgm.hilight_id   = 0;
            ui_qqchat.hilight_id     = 0;
            ui_qqdetail.hilight_id   = 0;
            ui_qqfind1.hilight_id    = 0;
            ui_qqfind2.hilight_id    = 0;
            ui_qqfind3.hilight_id    = 0;
            ui_qqitem.hilight_id     = 0;
            ui_qqlog.hilight_id      = 0;
            ui_qqset.hilight_id      = 0;
            ui_qqverify.hilight_id   = 0;
            ui_qqlist.hilight_id     = 0;
            break;
        }
        break;
    case WM_LBUTTONDOWN:
        sx = GET_X_LPARAM(lParam);
        sy = GET_Y_LPARAM(lParam);
        event = id = 0;
        game_range.mapping(sx, sy, &event, &id);
        switch( event)
        {
        case QQMAIN_EVENT:
            result = qq_main_on_md( sx, sy, MK_LBUTTON, id);
            break;
        case QQCALLGM_EVENT:
            result = qq_callgm_on_md( sx, sy, MK_LBUTTON, id);
            break;
        case QQSET_EVENT:
            result = qq_set_on_md(sx, sy, MK_LBUTTON, id);
            break;
        case QQFIND1_EVENT:
            result = qq_find1_on_md(sx, sy, MK_LBUTTON, id);
            break;
        case QQDETAIL_EVENT:
            result = qq_detail_on_md(sx, sy, MK_LBUTTON, id);
            break;
        case QQCHAT_EVENT:
            result = qq_chat_on_md(sx, sy, MK_LBUTTON, id);
            break;
        case QQLIST_EVENT:
            result = qq_list_on_md(sx, sy, MK_LBUTTON, id);
            break;
        case QQLOG_EVENT:
            result = qq_log_on_md(sx, sy, MK_LBUTTON, id);
            break;
        case QQITEM_EVENT:
            result = qq_item_on_md(sx, sy, MK_LBUTTON, id);
            break;
        case QQPOPUP_EVENT:
            result = qq_popup_on_md(sx, sy, MK_LBUTTON, id);
            break;
        case QQFIND2_EVENT:
            result = qq_find2_on_md(sx, sy, MK_LBUTTON, id);
            break;
        case QQFIND3_EVENT:
            result = qq_find3_on_md(sx, sy, MK_LBUTTON, id);
            break;
        case QQFACE_EVENT:
            result= qq_face_on_md(sx, sy, MK_LBUTTON, id);
            break;
        case QQVERIFY_EVENT:
            result = qq_verify_on_md(sx, sy, MK_LBUTTON, id);
            break;
        case QQHIS_EVENT:
            result = qq_his_on_md(sx, sy, MK_LBUTTON, id);
            break;
        default:
//            ui_qq.input_focus = 0;
            break;
        }
        if ( 0 == result )
            ui_qq.button_down = TRUE;
        break;
    case WM_RBUTTONDOWN:
        sx = GET_X_LPARAM(lParam);
        sy = GET_Y_LPARAM(lParam);
        event = id = 0;
        game_range.mapping(sx, sy, &event, &id);
        switch( event)
        {
        case QQMAIN_EVENT:
            result = qq_main_on_md( sx, sy, MK_RBUTTON, id);
            break;
        case QQCALLGM_EVENT:
            result = qq_callgm_on_md( sx, sy, MK_RBUTTON, id);
            break;
        case QQSET_EVENT:
            result = qq_set_on_md(sx, sy, MK_RBUTTON, id);
            break;
        case QQFIND1_EVENT:
            result = qq_find1_on_md(sx, sy, MK_RBUTTON, id);
            break;
        case QQDETAIL_EVENT:
            result = qq_detail_on_md(sx, sy, MK_RBUTTON, id);
            break;
        case QQCHAT_EVENT:
            result = qq_chat_on_md(sx, sy, MK_RBUTTON, id);
            break;
        case QQLIST_EVENT:
            result = qq_list_on_md(sx, sy, MK_RBUTTON, id);
            break;
        case QQLOG_EVENT:
            result = qq_log_on_md(sx, sy, MK_RBUTTON, id);
            break;
        case QQITEM_EVENT:
            result = qq_item_on_md(sx, sy, MK_RBUTTON, id);
            break;
        case QQPOPUP_EVENT:
            result = qq_popup_on_md(sx, sy, MK_RBUTTON, id);
            break;
        case QQFIND2_EVENT:
            result = qq_find2_on_md(sx, sy, MK_RBUTTON, id);
            break;
        case QQFIND3_EVENT:
            result = qq_find3_on_md(sx, sy, MK_RBUTTON, id);
            break;
        case QQFACE_EVENT:
            result= qq_face_on_md(sx, sy, MK_RBUTTON, id);
            break;
        case QQVERIFY_EVENT:
            result = qq_verify_on_md(sx, sy, MK_RBUTTON, id);
            break;
        case QQHIS_EVENT:
            result = qq_his_on_md(sx, sy, MK_RBUTTON, id);
            break;
        default:
//            ui_qq.input_focus = 0;
            break;
        }
        if ( 0 == result )
            ui_qq.button_down = TRUE;        
        break;
    case WM_LBUTTONUP:
        sx = GET_X_LPARAM(lParam);
        sy = GET_Y_LPARAM(lParam);
        event = id = 0;
        game_range.mapping(sx, sy, &event, &id);
        
        switch( event)
        {
        case QQMAIN_EVENT:
            result = qq_main_on_mu( sx, sy, MK_LBUTTON, id);
            break;
        case QQCALLGM_EVENT:
            result = qq_callgm_on_mu( sx, sy, MK_LBUTTON, id);
            break;
        case QQSET_EVENT:
            result = qq_set_on_mu(sx, sy, MK_LBUTTON, id);
            break;
        case QQFIND1_EVENT:
            result = qq_find1_on_mu(sx, sy, MK_LBUTTON, id);
            break;
        case QQDETAIL_EVENT:
            result = qq_detail_on_mu(sx, sy, MK_LBUTTON, id);
            break;
        case QQCHAT_EVENT:
            result = qq_chat_on_mu(sx, sy, MK_LBUTTON, id);
            break;
        case QQLIST_EVENT:
            result = qq_list_on_mu(sx, sy, MK_LBUTTON, id);
            break;
        case QQLOG_EVENT:
            result = qq_log_on_mu(sx, sy, MK_LBUTTON, id);
            break;
        case QQITEM_EVENT:
            result = qq_item_on_mu(sx, sy, MK_LBUTTON, id);
            break;
        case QQPOPUP_EVENT:
            result = qq_popup_on_mu(sx, sy, MK_LBUTTON, id);
            break;
        case QQFIND2_EVENT:
            result = qq_find2_on_mu(sx, sy, MK_LBUTTON, id);
            break;
        case QQFIND3_EVENT:
            result = qq_find3_on_mu(sx, sy, MK_LBUTTON, id);
            break;
        case QQFACE_EVENT:
            result = qq_face_on_mu(sx, sy, MK_LBUTTON, id);
            break;
        case QQVERIFY_EVENT:
            result = qq_verify_on_mu(sx, sy, MK_LBUTTON, id);
            break;
        case QQHIS_EVENT:
            result = qq_his_on_mu(sx, sy, MK_LBUTTON, id);
            break;
        default:
//            ui_qq.input_focus = 0;
            break;
        }
        if ( ui_qq.button_down )
        {
            ui_qqmain.active_id     = 0;
            ui_qqpopup.active_id    = 0;
            ui_qqcallgm.active_id   = 0;
            ui_qqchat.active_id     = 0;
            ui_qqdetail.active_id   = 0;
            ui_qqfind1.active_id    = 0;
            ui_qqfind2.active_id    = 0;
            ui_qqfind3.active_id    = 0;
            ui_qqitem.active_id     = 0;
            ui_qqlog.active_id      = 0;
            ui_qqset.active_id      = 0;
            ui_qqverify.active_id   = 0;
            ui_qqlist.active_id     = 0;
            ui_qq.button_down = FALSE;
        }
        break;
    case WM_RBUTTONUP:
        sx = GET_X_LPARAM(lParam);
        sy = GET_Y_LPARAM(lParam);
        event = id = 0;
        game_range.mapping(sx, sy, &event, &id);
        switch( event)
        {
        case QQMAIN_EVENT:
            result = qq_main_on_mu( sx, sy, MK_RBUTTON, id);
            break;
        case QQCALLGM_EVENT:
            result = qq_callgm_on_mu( sx, sy, MK_RBUTTON, id);
            break;
        case QQSET_EVENT:
            result = qq_set_on_mu(sx, sy, MK_RBUTTON, id);
            break;
        case QQFIND1_EVENT:
            result = qq_find1_on_mu(sx, sy, MK_RBUTTON, id);
            break;
        case QQDETAIL_EVENT:
            result = qq_detail_on_mu(sx, sy, MK_RBUTTON, id);
            break;
        case QQCHAT_EVENT:
            result = qq_chat_on_mu(sx, sy, MK_RBUTTON, id);
            break;
        case QQLIST_EVENT:
            result = qq_list_on_mu(sx, sy, MK_RBUTTON, id);
            break;
        case QQLOG_EVENT:
            result = qq_log_on_mu(sx, sy, MK_RBUTTON, id);
            break;
        case QQITEM_EVENT:
            result = qq_item_on_mu(sx, sy, MK_RBUTTON, id);
            break;
        case QQPOPUP_EVENT:
            result = qq_popup_on_mu(sx, sy, MK_RBUTTON, id);
            break;
        case QQFIND2_EVENT:
            result = qq_find2_on_mu(sx, sy, MK_RBUTTON, id);
            break;
        case QQFIND3_EVENT:
            result = qq_find3_on_mu(sx, sy, MK_RBUTTON, id);
            break;
        case QQFACE_EVENT:
            result= qq_face_on_mu(sx, sy, MK_RBUTTON, id);
            break;
        case QQVERIFY_EVENT:
            result = qq_verify_on_mu(sx, sy, MK_RBUTTON, id);
            break;
        case QQHIS_EVENT:
            result = qq_his_on_mu(sx, sy, MK_RBUTTON, id);
            break;
        default:
//            ui_qq.input_focus = 0;
            break;
        }
        if ( ui_qq.button_down )
        {
            ui_qqmain.active_id     = 0;
            ui_qqpopup.active_id    = 0;
            ui_qqcallgm.active_id   = 0;
            ui_qqchat.active_id     = 0;
            ui_qqdetail.active_id   = 0;
            ui_qqfind1.active_id    = 0;
            ui_qqfind2.active_id    = 0;
            ui_qqfind3.active_id    = 0;
            ui_qqitem.active_id     = 0;
            ui_qqlog.active_id      = 0;
            ui_qqset.active_id      = 0;
            ui_qqverify.active_id   = 0;
            ui_qqlist.active_id     = 0;
            ui_qq.button_down = FALSE;
        }
        break;
//    case WM_MOUSEWHEEL:
//        ch = read_mouse_key();
//        reset_mouse_key();
//        qq_main_on_mw(ch);    // other _on_mw function is loaded by 
//                            // qq_main_on_mw.
//        break;
    default:
        break;
    }
    
    return result;
}

BOOL ui_qq_is_max(void)
{
    return (ui_qq.curr_state_id == QQ_MAXIMIZE);
}

void    ui_qq_set_min(void)
{
    ui_qq.curr_state_id = QQ_MINIMIZE;
}

void    ui_qq_set_max(void)
{
    ui_qq.curr_state_id = QQ_MAXIMIZE;
}

/******************************************************************************************************************/
/* UI QQ FACE                                                                                                     */
/******************************************************************************************************************/
SLONG   init_qq_face_image(void)
{
    USTR    filename[_MAX_FNAME];
    SLONG   result, i, frames, valid_frames;
    CAKE_FRAME_ANI  *cfa;
    UI_QQFACE   *data = &ui_qqface;
    
    data->cfa = NULL;

    for(i=0; i<MAX_CAK_FRAME; i++)
    {
        data->cf[i] = NULL;
    }
    
    set_data_file(packed_menu_file);
    strcpy((char *)filename, "menu\\QQFace.cak");
    result = load_cake_frame_ani_from_file((USTR*)filename, &data->cfa);
    if(TTN_OK != result)
        return  -1;
    frames = count_cake_frames(data->cfa);
    valid_frames = min(frames, MAX_CAK_FRAME);
    for(i=0; i<valid_frames; i++)
    {
        cfa = get_specify_cake_frame_ani(data->cfa, i);
        data->cf[i] = cfa->cake_frame;
    }
    
    return  TTN_OK;
}


void    free_qq_face_image(void)
{
    UI_QQFACE   *data = &ui_qqface;
    SLONG   i;
    
    if(data->cfa)
    {
        destroy_cake_frame_ani(&data->cfa);
        for(i=0; i<MAX_CAK_FRAME; i++)
        {
            data->cf[i] = NULL;
        }
    }
    return;
}


void    redraw_qq_face(SLONG sx, SLONG sy, SLONG face_index, SLONG effect, BMP *bitmap)
{
    UI_QQFACE   *data = &ui_qqface;
    CAKE_FRAME  *cf;
    SLONG x1, x2, y1, y2;
    

    /* maybe has problem here, face_index need be check */
    cf = data->cf[face_index];
    if(! cf)
        return;
    switch(effect&0xffff)
    {
    case QQFACE_EFFECT_UP:
        x1 = sx;
        x2 = sx+cf->rle->w;
        y1 = sy;
        y2 = sy+cf->rle->h;
        put_line(x1, y1, x2, y1, SYSTEM_WHITE, bitmap);
        put_line(x1, y1, x1, y2, SYSTEM_WHITE, bitmap);
        
        put_line(x1, y2, x2, y2, SYSTEM_BLACK, bitmap);
        put_line(x2, y1, x2, y2, SYSTEM_BLACK, bitmap);
        break;
    case QQFACE_EFFECT_DOWN:
        x1 = sx;
        x2 = sx+cf->rle->w;
        y1 = sy;
        y2 = sy+cf->rle->h;
        put_line(x1, y1, x2, y1, SYSTEM_BLACK, bitmap);
        put_line(x1, y1, x1, y2, SYSTEM_BLACK, bitmap);
        
        put_line(x1, y2, x2, y2, SYSTEM_WHITE, bitmap);
        put_line(x2, y1, x2, y2, SYSTEM_WHITE, bitmap);
        break;
    default:
        break;
    }
    
    if ( (ui_qq.face_flash&QQ_FACE_FLASH_SPEED)
         && ((effect>>16)&QQFACE_EFFECT_TITTUP))
        return;

    if ((effect>>16) & QQFACE_EFFECT_NORMAL)
    {
        put_rle(sx, sy, cf->rle, bitmap);
    }
    if ((effect>>16) & QQFACE_EFFECT_GRAY)
    {
        gray_put_rle(sx, sy, cf->rle, bitmap);
    }
}

SLONG    qq_face_on_mm(SLONG sx, SLONG sy, SLONG id)
{
    return 0;
}
SLONG    qq_face_on_md(SLONG sx, SLONG sy, SLONG button, SLONG id)
{
    return 0;
}

SLONG    qq_face_on_mu(SLONG sx, SLONG sy, SLONG button, SLONG id)
{
    return 0;
}

SLONG    qq_face_on_mw(UCHR ch, SLONG id)
{
    return 0;
}

/******************************************************************************************************************/
/* UI QQ MAIN                                                                                                     */
/******************************************************************************************************************/
SLONG   init_qq_main_image(void)
{
    USTR    filename[_MAX_FNAME];
    SLONG   result, i, frames, valid_frames;
    CAKE_FRAME_ANI  *cfa;
    UI_QQMAIN *data = &ui_qqmain;
    
    data->cfa = NULL;
    for(i=0; i<32; i++)
    {
        data->cf[i] = NULL;
    }
    
    set_data_file(packed_menu_file);
    strcpy((char *)filename, "menu\\QQMain.cak");
    result = load_cake_frame_ani_from_file((USTR*)filename, &data->cfa);
    if(TTN_OK != result)
        return  -1;
    frames = count_cake_frames(data->cfa);
    valid_frames = min(frames, MAX_CAK_FRAME);
    for(i=0; i<valid_frames; i++)
    {
        cfa = get_specify_cake_frame_ani(data->cfa, i);
        data->cf[i] = cfa->cake_frame;
    }
    
    data->hilight_id = 0;
    data->active_id = 0;
    data->function_id = 0;
    //
    data->hide_state_login = 1;
    //
    data->first_list_index = 0;
    data->list_group = -1;
    data->list_item_count = 0;
    data->curr_list_kind = 0;
    data->curr_move_kind = -1;
    data->next_list_kind = 0;
    
    return  TTN_OK;
}


void    free_qq_main_image(void)
{
    UI_QQMAIN   *data = &ui_qqmain;
    SLONG   i;
    
    if(data->cfa)
    {
        destroy_cake_frame_ani(&data->cfa);
        for(i=0; i<MAX_CAK_FRAME; i++)
        {
            data->cf[i] = NULL;
        }
    }
    return;
}


void    redraw_qq_main(SLONG sx, SLONG sy, BMP *bitmap)
{
    CAKE_FRAME    *cf;
    UI_QQMAIN    *data = &ui_qqmain;
    LPUI_QQFRIEND pfriend;
    SLONG        group1, group2;
    SLONG        list_y1, list_y2, list_count1, list_count2;
    SLONG        frame, x, y, id, event, popup_y, updown_dy;
    SLONG   i, j, k;
    SLONG    icon;
    USTR    *name;
    BOOL    flag;
    
    event = QQMAIN_EVENT;
    
    //(1) background -------------------------------------------
    id = QQMAIN_ID_BKGND;
    frame = QQMAIN_FRAME_BKGND;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);
    
    //(2) minimize button --------------------------------------
    id = QQMAIN_ID_MINIMIZE;
    frame = QQMAIN_FRAME_MINIMIZE;
    if(data->active_id == id)
        frame += 1;
    else if(data->hilight_id == id)
        frame += 1;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);
    
    //(3) switch login state button ----------------------------
    id = QQMAIN_ID_SWITCH_LOGIN_STATE;
    if (qfms_get_state() == QF_ONLINE)
        frame = QQMAIN_FRAME_SHOW_STATE_LOGIN;
    else
        frame = QQMAIN_FRAME_HIDE_STATE_LOGIN;

    if(data->active_id == id)
        frame += 1;
    else if(data->hilight_id == id)
        frame += 1;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);
    
    //(4) callgm ----------------------------------------------
    id = QQMAIN_ID_CALLGM;
    frame = QQMAIN_FRAME_CALLGM;
    if(data->active_id == id)
        frame += 1;
    else if(data->hilight_id == id)
        frame += 1;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);
    
    //(5) system settings button -------------------------------
    id = QQMAIN_ID_SYSSET;
    frame = QQMAIN_FRAME_SYSSET;
    if(data->active_id == id)
        frame += 2;
    else if(data->hilight_id == id)
        frame += 1;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

    //(6) message button ---------------------------------------
    id = QQMAIN_ID_MESSAGE;
    frame = QQMAIN_FRAME_MESSAGE;
    if(data->active_id == id)
        frame += 2;
    else if(data->hilight_id == id)
        frame += 1;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);
    
    //(7) search button ----------------------------------------
    id = QQMAIN_ID_SEARCH;
    frame = QQMAIN_FRAME_SEARCH;
    if(data->active_id == id)
        frame += 2;
    else if(data->hilight_id == id)
        frame += 1;
    
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);
    
    //(8) kind buttons -----------------------------------------
    x = sx + QQMAIN_LIST_SX;
    y = sy + QQMAIN_LIST_SY;
    flag = false;
    
    
    
    if( data->next_list_kind != data->curr_list_kind)
    {
        data->curr_move_ay += QQMAIN_KIND_MOVE_SPEED;
        if(data->curr_move_ay >= QQMAIN_LIST_AERA_YL)
        {
            data->curr_move_ay = QQMAIN_LIST_AERA_YL;
            data->curr_list_kind = data->next_list_kind;
            data->first_list_index = 0;
        }
    }
    
    //
    for( i = 0; i < QQMAIN_LIST_KINDS; i++)
    {
        
        if( data->next_list_kind != data->curr_list_kind)
        {
            if( data->curr_move_kind>data->curr_list_kind)
            {
                y = sy + QQMAIN_LIST_SY + i*QQMAIN_KIND_YL;
                if(i<= data->curr_list_kind)
                {
                    
                }
                else if(i > data->curr_list_kind && i <= data->curr_move_kind)
                {
                    y +=  QQMAIN_LIST_AERA_YL - data->curr_move_ay;
                }
                else
                {
                    y += QQMAIN_LIST_AERA_YL;
                }
            }
            else
            {
                y = sy + QQMAIN_LIST_SY + i*QQMAIN_KIND_YL;
                if(i < data->curr_move_kind)
                {
                }
                else if( i >= data->curr_move_kind && i <= data->curr_list_kind)
                {
                    y += data->curr_move_ay;
                }
                else
                {
                    y += QQMAIN_LIST_AERA_YL;
                }
            }
        }
        else
        {
            if( i <= data->curr_list_kind)
                y = sy + QQMAIN_LIST_SY + i*QQMAIN_KIND_YL;
            else
                y = sy + QQMAIN_LIST_SY + i*QQMAIN_KIND_YL + QQMAIN_LIST_AERA_YL;
        }
        
        frame = QQMAIN_FRAME_KIND_MY_FRIENDS + i*3;
        id      = QQMAIN_ID_KIND_MY_FRIENDS + i;
        if (qq_chat_check_group(id) && i != data->curr_list_kind)
        {
            if ((ui_qq.face_flash&QQ_FACE_FLASH_SPEED))
                frame += 1;
        }
        else
        {
            if( data->active_id == id)    
                frame += 2;
            else if( data->hilight_id == id)
                frame += 1;
        }
        cf = data->cf[frame];
        put_rle(x, y, cf->rle, bitmap);
        game_range.add(x, y, QQMAIN_KIND_XL, QQMAIN_KIND_YL, event, id);
        
        
        if(i == data->curr_list_kind)
        {
            data->list_group = id;
            
            if (qfms_check(SHOW_ONLINE_ONLY))
                data->list_item_count = qfl_online_count(id);
            else
                data->list_item_count = *qfl_pcount(id);

            group1 = data->list_group;

            list_y1 = y + QQMAIN_KIND_YL + 1;
            if( i == QQMAIN_LIST_KINDS - 1)
            {
                list_count1 = ((sy + QQMAIN_LIST_SY + QQMAIN_LIST_YL) - list_y1)/24;
            }
            updown_dy = i * cf->rle->h;
        }
        else if( i == data->next_list_kind)
        {
            group2 = id;

            if (qfms_check(SHOW_ONLINE_ONLY))
                data->next_list_count = qfl_online_count(id);
            else
                data->next_list_count = *qfl_pcount(id);
            list_y2 = y + QQMAIN_KIND_YL + 1;
            if( i == QQMAIN_LIST_KINDS-1)
            {
                list_count2 = ((sy + QQMAIN_LIST_SY + QQMAIN_LIST_YL) - list_y2)/24;
            }
        }
        if( i == data->curr_list_kind+1)
        {
            list_count1 = (y - list_y1)/24;
        }
        else if( i == data->next_list_kind+1)
        {
            list_count2 = (y - list_y2)/24;
        }
    }
    
    //(9) friends list -----------------------------------------
    id = QQMAIN_ID_LIST_0;
    y  = list_y1;
    x  = QQMAIN_LIST_ITEM_SX;
    k = data->first_list_index;
    
    for(i = 0; i < QQMAIN_LIST_ITEM_MAX;i++)
    {
        //        k = i + data->first_list_index;
        
        if( i >= list_count1 || k >= data->list_item_count)
            break;
        
        pfriend = qf_get(k,data->list_group);
        
        icon = pfriend->icon_index;
        name = (USTR*)pfriend->name;
        
        if(qf_get_state(pfriend) != QF_ONLINE)
        {
            if( qfms_check(SHOW_ONLINE_ONLY))
            {
                // don't show offline friend
                k++;
                i--;
                continue;
            }
            else
                j = QQFACE_EFFECT_GRAY<<16;
        }
        else
            j = QQFACE_EFFECT_NORMAL<<16;

        if (qq_chat_specify_check_by_sindex(pfriend->sid, data->list_group))
            j = j | (QQFACE_EFFECT_TITTUP<<16);
        
        if((data->active_id>>16) == QQMAIN_ID_LIST_0 && i == (data->active_id & 0xffff))
            j = j|QQFACE_EFFECT_DOWN;
        else if((data->hilight_id>>16) == QQMAIN_ID_LIST_0 && i == (data->hilight_id & 0xffff))
            j = j|QQFACE_EFFECT_UP;

        
        popup_y = y+i*25;
        if((data->item_id&0xffff) == i)
            data->popup_y = popup_y;
        
        redraw_qq_list_item( x, popup_y, icon, name, (id<<16)|i, j, bitmap);
        
        k++;
    }
    if(data->curr_list_kind != data->next_list_kind)
    {
        y  = list_y2;
        for(i = 0; i < QQMAIN_LIST_ITEM_MAX;i++)
        {
            if( i >= list_count2 || i >= data->next_list_count)
                break;
            
            icon = qf_get(i, group2)->icon_index;
            name = (USTR*)qf_get(i, group2)->nickname;
            redraw_qq_list_item( x, y + i*25, icon, name, 0, QQFACE_EFFECT_GRAY<<16, bitmap);
        }
    }
    
    if(data->curr_list_kind == data->next_list_kind)
    {
        
        //(10) list pageup button ----------------------------------
        if(data->first_list_index > 0)
        {
            id = QQMAIN_ID_LIST_PAGEUP;
            frame = QQMAIN_FRAME_LIST_PAGEUP;
            
            if(data->hilight_id == id)
                frame++;
            if(data->active_id == id)
                data->first_list_index--;
            
            cf = data->cf[frame];
            x = sx + cf->frame_rx;
            y = sx + cf->frame_ry + updown_dy;
            put_rle(x, y, cf->rle, bitmap);
            game_range.add(x,y,cf->rle->w, cf->rle->h, event, id);
        }
        
        //(11) list pagedown button --------------------------------
        if(data->list_item_count > QQMAIN_LIST_ITEM_MAX 
            && data->first_list_index <data->list_item_count - QQMAIN_LIST_ITEM_MAX)
        {
            id = QQMAIN_ID_LIST_PAGEDOWN;
            frame = QQMAIN_FRAME_LIST_PAGEDOWN;
            
            if(data->hilight_id == id)
                frame--;
            if(data->active_id == id)
                data->first_list_index++;
            
            cf = data->cf[frame];
            x = sx + cf->frame_rx;
            y = sx + cf->frame_ry + updown_dy;
            put_rle(x, y, cf->rle, bitmap);
            game_range.add(x,y,cf->rle->w, cf->rle->h, event, id);
        }
    }
    //sub 
    switch( data->function_id)
    {
    case QQMAIN_ID_CALLGM:
        redraw_qq_callgm( sx, sy, bitmap);
        break;
    case QQMAIN_ID_SYSSET:
        redraw_qq_set( sx + QQSET_FIX_DX, sy, bitmap);
        break;
    case QQMAIN_ID_MESSAGE:
        redraw_qq_his(sx, sy, bitmap);
        break;
    case QQMAIN_ID_SEARCH:
        redraw_qq_find1( sx, sy, bitmap);
        break;
    case QQMAIN_ID_POPUP:
        redraw_qq_popup(sx, sy+data->popup_y, bitmap);
        break;
    case QQMAIN_ID_CHAT:
        redraw_qq_chat(sx, sy, bitmap);
        break;
    default:
        break;
    }
}

//Draw list item
//
void redraw_qq_list_item(SLONG sx, SLONG sy, SLONG icon_index, USTR *name, SLONG id, SLONG effect, BMP *bitmap)
{
    redraw_qq_face( sx, sy, icon_index, effect, bitmap);
    set_word_color(0, QQ_MAIN_LIST_COLOR);
    strcpy((char*)print_rec, (const char*)name);
    if( strlen((const char*)print_rec) > 8)
    {
        print_rec[6] = '.';
        print_rec[7] = '.';
        print_rec[8] = '\0';
    }
    print12( sx+21, sy+8, (USTR*)print_rec, PEST_PUT, bitmap);
    game_range.add( sx, sy, 60, 22, QQMAIN_EVENT, id);
    set_word_color( 0, SYSTEM_WHITE);
}


SLONG    qq_main_on_mm(SLONG sx, SLONG sy, SLONG id)
{
    SLONG map_x, map_y;
    SLONG event = QQMAIN_EVENT;

    map_x = map_data.map_sx + sx;
    map_y = map_data.map_sy + sy;
    set_mouse_hand_position(sx, sy);
    set_mouse_hand_point_position(map_x, map_y);
    set_mouse_hand_point_kind_no(event, id);

    ui_qqmain.hilight_id = id;
    return 0;
}

SLONG    qq_main_on_md(SLONG sx, SLONG sy, SLONG button, SLONG id)
{
    
    switch(id)
    {
    case QQMAIN_ID_MINIMIZE:
        ui_qq.curr_state_id = QQ_MINIMIZE;
        break;
    case QQMAIN_ID_MAXIMIZE:
        ui_qq.curr_state_id = QQ_MAXIMIZE;
        break;
    case QQMAIN_ID_MESSAGE:
    case QQMAIN_ID_SEARCH:
    case QQMAIN_ID_SYSSET:
    case QQMAIN_ID_CALLGM:
        if(ui_qqmain.active_id == id)
            ui_qqmain.active_id = 0;
        else
            ui_qqmain.active_id = id;
        break;
    case QQMAIN_ID_KIND_MY_FRIENDS:
    case QQMAIN_ID_KIND_TEAM_PLAYERS:
    case QQMAIN_ID_KIND_GUILD_PLAYERS:
    case QQMAIN_ID_KIND_STRANGERS:
    case QQMAIN_ID_KIND_UNDESIREDERS:
        ui_qqmain.active_id = id;
        break;
    case QQMAIN_ID_SWITCH_LOGIN_STATE:
        if (qfms_get_state() == QF_ONLINE)
            qq_client_set_mystate(QF_HIDE);
        else
            qq_client_set_mystate(QF_ONLINE);
        ui_qqmain.active_id = 0;
        break;
    case QQMAIN_ID_LIST_PAGEUP:
    case QQMAIN_ID_LIST_PAGEDOWN:
        ui_qqmain.active_id = id;
        break;
    default:
        ui_qqmain.active_id = id;
        break;
    }
    return 0;
    
}


SLONG    qq_main_on_mu(SLONG sx, SLONG sy, SLONG button, SLONG id)
{
    SLONG kind, result = 1;
    UI_QQFRIEND *pf;
    SLONG index, group;
    char *p_t;
    TPOS_ITEM item;
    SLONG i;
    
    switch( id)
    {
    case QQMAIN_ID_MINIMIZE:
        break;
    case QQMAIN_ID_KIND_MY_FRIENDS:
    case QQMAIN_ID_KIND_TEAM_PLAYERS:
    case QQMAIN_ID_KIND_GUILD_PLAYERS:
    case QQMAIN_ID_KIND_STRANGERS:
    case QQMAIN_ID_KIND_UNDESIREDERS:
        if( ui_qqmain.active_id == id)
        {
            kind = id - QQMAIN_ID_KIND_MY_FRIENDS;
            
            if( kind > ui_qqmain.curr_list_kind)
            {
                ui_qqmain.curr_move_kind = kind;
            }
            else if(kind < ui_qqmain.curr_list_kind)
            {
                ui_qqmain.curr_move_kind = kind + 1;
            }
            ui_qqmain.curr_move_ay = 0;
            ui_qqmain.next_list_kind = kind;
            if( ui_qqmain.function_id == QQMAIN_ID_POPUP)
                ui_qqmain.function_id = 0;
            result = 0;
        }
        break;
    case QQMAIN_ID_CALLGM:
        if( ui_qqmain.active_id == id)
        {
            if( ui_qqmain.function_id == id)
                ui_qqmain.function_id = 0;
            else
            {
                if (ui_qq.end_func)
                    ui_qq.end_func();
                ui_qqmain.function_id = id;
                qq_callgm_start();
            }
            ui_qqmain.hilight_id = id;    
            result = 1;
        }
        break;
    case QQMAIN_ID_SYSSET:
        if( ui_qqmain.active_id == id)
        {
            if( ui_qqmain.function_id == id)
                ui_qqmain.function_id = 0;
            else
            {
                if (ui_qq.end_func)
                    ui_qq.end_func();
                ui_qqmain.function_id = id;
            }
            ui_qqmain.hilight_id = id;    
            result = 1;
        }
        break;
    case QQMAIN_ID_SEARCH:
        if( ui_qqmain.active_id == id)
        {
            if( ui_qqmain.function_id == id)
                ui_qqmain.function_id = 0;
            else
            {
                if (ui_qq.end_func)
                    ui_qq.end_func();
                ui_qqmain.function_id = id;
                qq_find1_start();
                qq_client_request_player_count();
            }
            ui_qqmain.hilight_id = id;    
            result = 1;
        }
        break;
    case QQMAIN_ID_MESSAGE:
        if( ui_qqmain.active_id == id)
        {
            if( ui_qqmain.function_id == id)
                ui_qqmain.function_id = 0;
            else
            {
                if (ui_qq.end_func)
                    ui_qq.end_func();
                ui_qqmain.function_id = id;
                //TODO: ADD SYSTEM HISTORY INIT CODE
            }
            ui_qqmain.hilight_id = id;    
            result = 1;
        }
        break;
    case QQMAIN_ID_LIST_PAGEUP:
    case QQMAIN_ID_LIST_PAGEDOWN:
        ui_qqmain.hilight_id = id;
        result = 1;
        break;
    default:
        if( ui_qqmain.active_id == id)
        {
            if( (id>>16) == QQMAIN_ID_LIST_0)
            {
                
                switch(button)
                {
                case MK_LBUTTON:
                    if(ui_qqmain.item_id == id && ui_qqmain.function_id == QQMAIN_ID_CHAT)
                    {
                        qq_chat_end();
                        ui_qqmain.function_id = 0;
                        ui_qqmain.item_id = 0;
                    }
                    else
                    {
                        ui_qqmain.function_id = QQMAIN_ID_CHAT;
                        ui_qqmain.item_id = id;
                        index = (id&0xffff)+ui_qqmain.first_list_index;
                        group = ui_qqmain.list_group;
                        pf = qf_get(index, group);
                        ui_qqchat.icon_index = pf->icon_index;
                        lstrcpyn(ui_qqchat.name, pf->name, 32);
                        ui_qqchat.sid = pf->sid;
                        te_set_text( ui_qqchat.ptext, NULL );

                        if (qq_chat_specify_check_by_sindex(pf->sid, group))
                        {
                            p_t = qq_chat_get_chat_by_sindex(pf->sid, group);
                            if (p_t)
                            {
                                te_set_text( ui_qqchat.ptext, p_t);
//                                ui_qqchat.read_only = TRUE;
                                te_set_read_only( ui_qqchat.ptext, TRUE );
                                ui_qqchat.sid = pf->sid;
                                ui_qqchat.function_id = 0;

                                for ( i = 0; i < 3; i++ )
                                {
                                    GetCharacterTransItem( g_lPlayerIndex, i, &item );
                                    if ( !IsItemNone( &item ) )
                                    {
                                        ui_qqchat.function_id = QQCHAT_ID_SEND_ITEM;
                                        break;
                                    }
                                }
                            }
                            else
                            {
                                te_set_read_only( ui_qqchat.ptext, FALSE );
                                ui_qqchat.function_id = 0;
                                
                            }
                            qq_chat_del_chat(index, group);
                        }
                        else
                        {
                            te_set_read_only( ui_qqchat.ptext, FALSE );
                            ui_qqchat.function_id = 0;
                        }
                    }
                    break;
                case MK_RBUTTON:
                    if(ui_qqmain.item_id == id && ui_qqmain.function_id == QQMAIN_ID_POPUP)
                    {
                        ui_qqmain.function_id = 0;
                        // item_id maybe not use
                        ui_qqmain.item_id = 0;
                    }
                    else
                    {
                        ui_qqmain.function_id = QQMAIN_ID_POPUP;
                        ui_qqmain.item_id = id;
                        ui_qqpopup.pfriend = 
                            qf_get((id&0xffff)+ui_qqmain.first_list_index, ui_qqmain.list_group);
                        ui_qqpopup.current_goup = qq_get_current_group();
                        ui_qqpopup.function_id = 0;
                    }
                    break;
                default:
                    break;
                }
                ui_qqmain.hilight_id = id;    
                result = 1;
            }
        }
        break;
    }
    //    ui_qqmain.hilight_id = ui_qqmain.active_id;
    ui_qqmain.active_id = 0;
    return result;
}

SLONG qq_get_current_group()
{
    return ui_qqmain.curr_list_kind+QQMAIN_ID_KIND_MY_FRIENDS;
}
/******************************************************************************************************************/
/* UI QQ POPUP                                                                                                    */
/******************************************************************************************************************/
SLONG   init_qq_popup_image(void)
{
    USTR    filename[_MAX_FNAME];
    SLONG   result, i, frames, valid_frames;
    CAKE_FRAME_ANI  *cfa;
    UI_QQPOPUP *data = &ui_qqpopup;
    
    data->cfa = NULL;
    for(i=0; i<32; i++)
    {
        data->cf[i] = NULL;
    }
    
    set_data_file(packed_menu_file);
    strcpy((char *)filename, "menu\\QQPopup.cak");
    result = load_cake_frame_ani_from_file((USTR*)filename, &data->cfa);
    if(TTN_OK != result)
        return  -1;
    frames = count_cake_frames(data->cfa);
    valid_frames = min(frames, MAX_CAK_FRAME);
    for(i=0; i<valid_frames; i++)
    {
        cfa = get_specify_cake_frame_ani(data->cfa, i);
        data->cf[i] = cfa->cake_frame;
    }
    
    data->hilight_id = 0;
    data->active_id = 0;
    data->function_id = 0;
    //
    return  TTN_OK;
}


void    free_qq_popup_image(void)
{
    UI_QQPOPUP   *data = &ui_qqpopup;
    SLONG   i;
    
    if(data->cfa)
    {
        destroy_cake_frame_ani(&data->cfa);
        for(i=0; i<MAX_CAK_FRAME; i++)
        {
            data->cf[i] = NULL;
        }
    }
    return;
}


void    redraw_qq_popup(SLONG sx, SLONG sy, BMP *bitmap)
{
    CAKE_FRAME    *cf;
    UI_QQPOPUP    *data = &ui_qqpopup;
    SLONG event, id, frame, x, y;
    
    if(data->function_id == QQPOPUP_ID_CHECK)
    {
        redraw_qq_detail(0, 0, bitmap);
        return;
    }
    event = QQPOPUP_EVENT;
    //backgrond ------------------------
    id = QQPOPUP_ID_BKGND;
    frame = QQPOPUP_FRAME_BKGND;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->w, event, id);
    
    //check button ---------------------
    id = QQPOPUP_ID_CHECK;
    frame = QQPOPUP_FRAME_CHECK;
    
    if ( data->active_id == id )
        frame += 2;
    else if ( data->hilight_id == id )
        frame++;
    
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + QQPOPUP_ID_DY1;

    put_rle( x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);
    
    //delete button ----------------------
    id = QQPOPUP_ID_DELETE;
    frame = QQPOPUP_FRAME_DELETE;
    
    if ( data->active_id == id )
        frame += 2;
    else if ( data->hilight_id == id )
        frame++;
        
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy    + QQPOPUP_ID_DY2;
    if (QQ_TEAM_PLAYERS == data->current_goup)
    {
        gray_put_rle( x, y, cf->rle, bitmap);
    }
    else 
    {
        if( data->active_id == id || data->hilight_id == id)
            put_rle( x, y, cf->rle, bitmap);
        game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);
    }    

    
}


SLONG    qq_popup_on_mm(SLONG sx, SLONG sy, SLONG id)
{
    ui_qqpopup.hilight_id = id;
    return 0;
}

SLONG    qq_popup_on_md(SLONG sx, SLONG sy, SLONG button, SLONG id)
{
    switch(id)
    {
    case QQPOPUP_ID_CHECK:
    case QQPOPUP_ID_DELETE:
        ui_qqpopup.active_id = id;
        break;
    }
    return 0;
}

SLONG    qq_popup_on_mu(SLONG sx, SLONG sy, SLONG button, SLONG id)
{
    SLONG result = 1;
    UI_QQPOPUP *data = &ui_qqpopup;
    UIMSGBOX mb;

    switch(id)
    {
    case QQPOPUP_ID_CHECK:
        if(ui_qqpopup.active_id == id)
        {
            if (ui_qqpopup.pfriend)
            {
                ui_qqpopup.function_id = id;
                ui_qqdetail.pfriend = ui_qqpopup.pfriend;
                qq_client_request_query_someone(ui_qqdetail.pfriend->sid);
                ui_qqdetail.parent_id = QQPOPUP_EVENT;
                result = 0;
            }
        }
        break;
    case QQPOPUP_ID_DELETE:
        if(ui_qqpopup.active_id == id)
        {
            mb.pfunc = qq_del_friend_callback;
            mb.disp_time = 0;
            mb.font_size = TE_FONT_SIZE_12;
            mb.msgbox_type = UIMB_YESNO | UIMB_OWN_MOUSE;
            mb.param.event_id = QQPOPUP_EVENT;
            mb.param.param1 = id;

            ui_qqmain.function_id = 0;
            result = 0;
        }
        break;
        
    }
    ui_qqpopup.active_id = 0;
    return result;
}

/******************************************************************************************************************/
/* UI QQ CALLGM                                                                                                   */
/******************************************************************************************************************/
SLONG   init_qq_callgm_image(void)
{
    USTR    filename[_MAX_FNAME];
    SLONG   result, i, frames, valid_frames;
    CAKE_FRAME_ANI  *cfa;
    UI_QQCALLGM *data = &ui_qqcallgm;
    
    data->cfa = NULL;
    for(i=0; i<32; i++)
    {
        data->cf[i] = NULL;
    }
    
    set_data_file(packed_menu_file);
    strcpy((char *)filename, "menu\\QQCallGM.cak");
    result = load_cake_frame_ani_from_file((USTR*)filename, &data->cfa);
    if(TTN_OK != result)
        return  -1;
    frames = count_cake_frames(data->cfa);
    valid_frames = min(frames, MAX_CAK_FRAME);
    for(i=0; i<valid_frames; i++)
    {
        cfa = get_specify_cake_frame_ani(data->cfa, i);
        data->cf[i] = cfa->cake_frame;
    }
    
    data->hilight_id = 0;
    data->active_id = 0;
    data->function_id = 0;
    //

    
    // te_init(&data->text, QQ_CHAT_TEXT_LEN, QQCALLGM_INPUT_MEMO_XL, QQCALLGM_INPUT_MEMO_YL, FALSE);
    data->ptext = te_create( QQCALLGM_INPUT_MEMO_SX, QQCALLGM_INPUT_MEMO_SY,
                             QQCALLGM_INPUT_MEMO_XL, QQCALLGM_INPUT_MEMO_YL, 
                             QQ_CHAT_TEXT_LEN );

    te_set_active( data->ptext, TRUE );

    return  TTN_OK;
}


void    free_qq_callgm_image(void)
{
    UI_QQCALLGM   *data = &ui_qqcallgm;
    SLONG   i;

    if ( data->ptext )
    {
        te_destroy( data->ptext );
        data->ptext = NULL;
    }

    if(data->cfa)
    {
        destroy_cake_frame_ani(&data->cfa);
        for(i=0; i<MAX_CAK_FRAME; i++)
        {
            data->cf[i] = NULL;
        }
    }
    return;
}


void    redraw_qq_callgm(SLONG sx, SLONG sy, BMP *bitmap)
{
    UI_QQCALLGM *data = &ui_qqcallgm;
    CAKE_FRAME  *cf;
    SLONG   frame, x, y, id, event;
    
    event = QQCALLGM_EVENT;
    
    //background------------------
    id = QQCALLGM_ID_BKGND;
    frame = QQCALLGM_FRAME_BKGND;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);
    
    //button----------------------
    id = QQCALLGM_ID_SEND;
    frame = QQCALLGM_FRAME_SEND;
    if( data->active_id == id)
        frame += 2;
    else if( data->hilight_id == id)
        frame++;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);
    
    id = QQCALLGM_ID_CANCEL;
    frame = QQCALLGM_FRAME_CANCEL;
    if( data->active_id == id)
        frame += 2;
    else if( data->hilight_id == id)
        frame++;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);
    
    //text------------------------
    redraw_te( data->ptext, bitmap );

/*
    id = QQCALLGM_ID_TEXT;
    x = QQCALLGM_INPUT_MEMO_SX;
    y = QQCALLGM_INPUT_MEMO_SY;

    if ( ui_qq.input_focus == QQCALLGM_EVENT )
        te_set_active( &data->text, TRUE );
    else
        te_set_active( &data->text, FALSE );
    
      te_draw(x, y, data->ptext, bitmap);
    
    game_range.add(x, y, data->text.w, data->text.h, event, id);
*/

}


SLONG    qq_callgm_on_mm(SLONG sx, SLONG sy, SLONG id)
{
    ui_qqcallgm.hilight_id = id;
    return 0;
}

SLONG    qq_callgm_on_md(SLONG sx, SLONG sy, SLONG button, SLONG id)
{
    SLONG result = 1;
    UI_QQCALLGM *data = &ui_qqcallgm;
    switch(id)
    {
    case QQCALLGM_ID_SEND:
    case QQCALLGM_ID_CANCEL:
    case QQCALLGM_ID_BKGND:
        ui_qqcallgm.active_id = id;
        break;
    case QQCALLGM_ID_TEXT:
        ui_qqcallgm.active_id = id;
//        te_on_md(&data->text, sx, sy);
        result = 0;
        break;
    }
    return result;
}

SLONG    qq_callgm_on_mu(SLONG sx, SLONG sy, SLONG button, SLONG id)
{
    SLONG result = 1;
    UI_QQCALLGM *data = &ui_qqcallgm;
    switch(id)
    {
    case QQCALLGM_ID_SEND:
        if (data->active_id == id)
        {
            if(TTN_OK == qq_callgm_send_message())
            {
                qq_callgm_end();
                result = 0;
            }
//            ui_qq.input_focus = 0;
        }
        break;
    case QQCALLGM_ID_CANCEL:
        if (data->active_id == id)
        {
            qq_callgm_end();
            result = 0;
        }
        break;
    case QQCALLGM_ID_TEXT:
        if (data->active_id == id)
        {
            data->function_id = id;
        }
        break;
    default:
        break;

    }
    data->active_id = 0;
    return result;
}

void qq_callgm_start(void)
{
    // todo
    UI_QQCALLGM *data = &ui_qqcallgm;
    te_set_active( data->ptext, TRUE );
    ui_qq.end_func = qq_callgm_end;
}

void    qq_callgm_end(void)
{
    UI_QQCALLGM *data = &ui_qqcallgm;
    ui_qqmain.function_id = 0;
    ui_qq.end_func = NULL;
    te_set_text( data->ptext, NULL );
    ui_qq.end_func = NULL;
}

SLONG    qq_callgm_send_message(void)
{
    UI_QQCALLGM *data = &ui_qqcallgm;
    if (te_get_size( data->ptext ) == 0)
    {
        qq_msgbox(QQ_MB_INPUT_EMPTY, QQMB_TITLE_ERROR, 
                    QQMB_TEXT_INPUT_EMPTY, UIMB_OK, 0);
        return TTN_NOT_OK;
    }
    /* Send message to gm */

    return TTN_OK;
}
/******************************************************************************************************************/
/* UI QQ CHAT                                                                                                     */
/******************************************************************************************************************/
SLONG   init_qq_chat_image(void)
{
    USTR    filename[_MAX_FNAME];
    SLONG   result, i, frames, valid_frames;
    CAKE_FRAME_ANI  *cfa;
    UI_QQCHAT *data = &ui_qqchat;
    
    data->cfa = NULL;
    for(i=0; i<32; i++)
    {
        data->cf[i] = NULL;
    }
    
    set_data_file(packed_menu_file);
    strcpy((char *)filename, "menu\\QQChat.cak");
    result = load_cake_frame_ani_from_file((USTR*)filename, &data->cfa);
    if(TTN_OK != result)
        return  -1;
    frames = count_cake_frames(data->cfa);
    valid_frames = min(frames, MAX_CAK_FRAME);
    for(i=0; i<valid_frames; i++)
    {
        cfa = get_specify_cake_frame_ani(data->cfa, i);
        data->cf[i] = cfa->cake_frame;
    }
    
    data->hilight_id = 0;
    data->active_id = 0;
    data->function_id = 0;

    data->ptext = te_create( QQCHAT_INPUT_MEMO_SX, QQCHAT_INPUT_MEMO_SY + QQ_CHATITEMLOGLIST_FIX_DY,
                             QQCHAT_INPUT_MEMO_XL, QQCHAT_INPUT_MEMO_YL,
                             QQ_CHAT_TEXT_LEN );
    te_set_active( data->ptext, TRUE );
    
    return  TTN_OK;
}


void    free_qq_chat_image(void)
{
    UI_QQCHAT   *data = &ui_qqchat;
    SLONG   i;
    
    te_destroy( data->ptext );
    data->ptext = NULL;

    if(data->cfa)
    {
        destroy_cake_frame_ani(&data->cfa);
        for(i=0; i<MAX_CAK_FRAME; i++)
        {
            data->cf[i] = NULL;
        }
    }
    return;
}


void    redraw_qq_chat(SLONG sx, SLONG sy, BMP *bitmap)
{
    CAKE_FRAME    *cf;
    UI_QQCHAT    *data = &ui_qqchat;
    SLONG event, id, frame, x, y, icon_index;
    SLONG xl, yl;

    
    event = QQCHAT_EVENT;
    
    sy += QQ_CHATITEMLOGLIST_FIX_DY;
    
    //backgrond-------------------
    id = QQCHAT_ID_BKGND;
    frame = QQCHAT_FRAME_BKGND;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle( x, y, cf->rle, bitmap);
    game_range.add( x, y, cf->rle->w, cf->rle->h, event,id);

    if ( data->ptext->read_only )
    {
        //replay ----------------------
        id = QQCHAT_ID_REPLAY;
        frame = QQCHAT_FRAME_REPLAY;
        if (data->active_id == id)
            frame += 2;
        else if (data->hilight_id == id)
            frame ++;
        cf = data->cf[frame];
        x = sx + cf->frame_rx;
        y = sy + cf->frame_ry;

        put_rle(x, y, cf->rle, bitmap);
        game_range.add( x, y, cf->rle->w, cf->rle->h, event, id);

        //close -------------------------
        id = QQCHAT_ID_CLOSE;
        frame = QQCHAT_FRAME_CLOSE;

        if (data->active_id == id)
            frame += 2;
        else if (data->hilight_id == id)
            frame ++;
        cf = data->cf[frame];
        x = sx + cf->frame_rx;
        y = sy + cf->frame_ry;

        put_rle(x, y, cf->rle, bitmap);
        game_range.add( x, y, cf->rle->w, cf->rle->h, event, id);

        // next ---------------------------
        id = QQCHAT_ID_NEXT;
        frame = QQCHAT_FRAME_NEXT;

        if (data->active_id == id)
            frame += 2;
        else if (data->hilight_id == id)
            frame ++;
        cf = data->cf[frame];
        x = sx + cf->frame_rx;
        y = sy + cf->frame_ry;
        
        put_rle(x, y, cf->rle, bitmap);
        game_range.add( x, y, cf->rle->w, cf->rle->h, event, id);

    }
    else
    {
        //send to multi ----------------
//  目前版本不打算支持將消息發給多人

//        id = QQCHAT_ID_SEND_TO_MULTI;
//        frame = QQCHAT_FRAME_SEND_TO_MULTI;
//        if(data->active_id == id)
//            frame += 2;
//        else if( data->hilight_id == id)
//            frame++;
//        cf = data->cf[frame];
//        x = sx + cf->frame_rx;
//        y = sy + cf->frame_ry;

        /* TODO: send chat to multiplayer
        put_rle(x, y, cf->rle, bitmap);
        game_range.add( x, y, cf->rle->w, cf->rle->h, event, id);
        */
//        gray_put_rle(x, y, cf->rle, bitmap);
        
        //send item --------------------
        id = QQCHAT_ID_SEND_ITEM;
        frame = QQCHAT_FRAME_SEND_ITEM;
        if(data->active_id == id)
            frame += 2;
        else if( data->hilight_id == id)
            frame++;
        cf = data->cf[frame];
        x = sx + cf->frame_rx;
        y = sy + cf->frame_ry;

        if ( !ui_qqitem.wait_send )
        {
            put_rle(x, y, cf->rle, bitmap);
            game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);
        }
        else
        {
            gray_put_rle( x, y, cf->rle, bitmap );
        }
    
        //cancel ------------------------
        id = QQCHAT_ID_CANCEL;
        frame = QQCHAT_FRAME_CANCEL;
        if(data->active_id == id)
            frame += 2;
        else if( data->hilight_id == id)
            frame++;
        cf = data->cf[frame];
        x = sx + cf->frame_rx;
        y = sy + cf->frame_ry;
        put_rle(x, y, cf->rle, bitmap);
        game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);
        
        //send ---------------------------
        id = QQCHAT_ID_SEND;
        frame = QQCHAT_FRAME_SEND;
        if(data->active_id == id)
            frame+=2;
        else if(data->hilight_id==id)
            frame++;
        cf = data->cf[frame];
        x = sx + cf->frame_rx;
        y = sy + cf->frame_ry;
        put_rle(x, y, cf->rle, bitmap);
        game_range.add( x, y, cf->rle->w, cf->rle->h, event, id);
    }

    //chat log ---------------------
    id = QQCHAT_ID_CHAT_LOG;
    frame = QQCHAT_FRAME_CHAT_LOG;
    if(data->active_id == id)
        frame += 2;
    else if( data->hilight_id == id)
        frame++;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add( x, y, cf->rle->w, cf->rle->h, event, id);

    // face ----------------------------
    icon_index = data->icon_index;
    x = sx + QQCHAT_TARGET_FACE_SX;
    y = sy + QQCHAT_TARGET_FACE_SY;
    redraw_qq_face(x, y, icon_index, QQFACE_EFFECT_NORMAL<<16, bitmap);

    // name ---------------------------
    x = sx + QQCHAT_TARGET_NAME_SX;
    y = sy + QQCHAT_TARGET_NAME_SY;
    xl = QQCHAT_TARGET_NAME_XL;
    yl = QQCHAT_TARGET_NAME_YL;
    qq_draw_text(x, y, xl, data->name, QQ_CHAT_NAME_COLOR, bitmap);

    //text ----------------------------

    redraw_te( data->ptext, bitmap );

    switch(data->function_id)
    {
    case QQCHAT_ID_SEND_TO_MULTI:
        redraw_qq_list(sx, sy, bitmap);
        break;
    case QQCHAT_ID_SEND_ITEM:
        redraw_qq_item(sx, sy, bitmap);
        break;
    case QQCHAT_ID_CHAT_LOG:
        redraw_qq_log(sx, sy, bitmap);
        break;
    default:
        break;
    }
    
}


SLONG    qq_chat_on_mm(SLONG sx, SLONG sy, SLONG id)
{
    ui_qqchat.hilight_id = id;
    return 0;
}


SLONG    qq_chat_on_md(SLONG sx, SLONG sy, SLONG button, SLONG id)
{
    switch(id)
    {
    case QQCHAT_ID_SEND_TO_MULTI:
    case QQCHAT_ID_SEND_ITEM:
    case QQCHAT_ID_CANCEL:
    case QQCHAT_ID_SEND:
    case QQCHAT_ID_CHAT_LOG:
    case QQCHAT_ID_BKGND:
    case QQCHAT_ID_REPLAY:
    case QQCHAT_ID_CLOSE:
    case QQCHAT_ID_NEXT:
    case QQCHAT_ID_INPUT_MEMO:
        ui_qqchat.active_id = id;
        break;
    default:
        break;
    }
    return 0;
}

SLONG    qq_chat_on_mu(SLONG sx, SLONG sy, SLONG button, SLONG id)
{
    SLONG result = 1;
    UI_QQCHAT    *data = &ui_qqchat;
    char         *p_text;
    SLONG        index, group;
    TPOS_ITEM    item;
    BOOL         trans_item = FALSE;
    SLONG        i;

    switch(id)
    {
    case QQCHAT_ID_CHAT_LOG:
        if ( data->active_id == id )
        {
            if ( data->function_id == id )
            {
                data->function_id = 0;
            }
            else
            {
                qq_log_init( );
                data->function_id = id;
            }
            result = 0;
        }
        break;
    case QQCHAT_ID_SEND_TO_MULTI:
    case QQCHAT_ID_SEND_ITEM:
        if(data->active_id == id)
        {
            if(data->function_id == id)
                data->function_id = 0;
            else
                data->function_id = id;
            result = 0;
//            ui_qq.input_focus = 0;
        }
        break;
    case QQCHAT_ID_SEND:
        if(data->active_id == id)
        {
            for( i = 0; i < 3; i++ )
            {
                GetCharacterTransItem( g_lPlayerIndex, 0, &item );
                if ( !IsItemNone( &item ) )
                {
                    trans_item = TRUE;
                    break;
                }
            }
            
            //send chat contain to server
            if ( te_get_size( data->ptext ) == 0 && !trans_item )
            {

                qq_msgbox(QQ_MB_INPUT_EMPTY, QQMB_TITLE_ERROR,
                            QQMB_TEXT_INPUT_EMPTY, UIMB_OK, 0);

            }
            else
            {
                // send chat to server
                if ( te_get_size( data->ptext ) != 0 )
                {
                    qq_client_qq_send_2one_msg( data->sid, data->ptext->ptext_buf );
                    qq_log_add( data->sid, data->name, data->ptext->ptext_buf );
                }

                if ( trans_item )
                {
                    if ( TTN_OK == qq_client_request_transfer_item( data->sid ) )
                        ui_qqitem.wait_send = TRUE;
                }
                     
                qq_chat_end();
                result =0;
            }
        }
        break;
    case QQCHAT_ID_CANCEL:
    case QQCHAT_ID_CLOSE:
        if(data->active_id == id)
        {
            qq_chat_end();
            result = 0;
        }
        break;
    case QQCHAT_ID_REPLAY:
        if (data->active_id == id )
        {
            te_set_text( data->ptext, NULL );
            te_set_read_only( data->ptext, FALSE );
        }
        break;
    case QQCHAT_ID_NEXT:
        if (data->active_id == id)
        {
            group = qf_get_group_by_sid(data->sid);
            index = qf_get_index_by_sid(data->sid, group);
            p_text = qq_chat_get_chat_by_sindex(data->sid, group);
            te_set_text( data->ptext, p_text);
            qq_chat_del_chat(index, group);
        }
        break;
    default:
        break;
    }

    data->active_id = 0;
    return result;
}


void qq_chat_start(void)
{
    if (ui_qq.end_func)
        ui_qq.end_func();
    ui_qq.end_func = qq_chat_end;
}

void qq_chat_end(void)
{
    ui_qqmain.function_id = 0;
    ui_qq.end_func = NULL;
    te_set_text( ui_qqchat.ptext, NULL );
    ui_qq.end_func = NULL;
}

/******************************************************************************************************************/
/* UI QQ DETAIL                                                                                                   */
/******************************************************************************************************************/
SLONG    init_qq_detail_image(void)
{
    USTR    filename[_MAX_FNAME];
    SLONG   result, i, frames, valid_frames;
    CAKE_FRAME_ANI  *cfa;
    UI_QQDETAIL *data = &ui_qqdetail;
    
    data->cfa = NULL;
    for(i=0; i<32; i++)
    {
        data->cf[i] = NULL;
    }
    
    set_data_file(packed_menu_file);
    strcpy((char *)filename, "menu\\qqDetail.cak");
    result = load_cake_frame_ani_from_file((USTR*)filename, &data->cfa);
    if(TTN_OK != result)
        return  -1;
    frames = count_cake_frames(data->cfa);
    valid_frames = min(frames, MAX_CAK_FRAME);
    for(i=0; i<valid_frames; i++)
    {
        cfa = get_specify_cake_frame_ani(data->cfa, i);
        data->cf[i] = cfa->cake_frame;
    }
    
    data->hilight_id = 0;
    data->active_id = 0;
    data->function_id = 0;
    data->parent_id = 0;
    data->pfriend = NULL;

    memset( &data->friend_info, 0, sizeof( data->friend_info ) );
    //
    //
    return  TTN_OK;
}

void    free_qq_detail_image(void)
{
    UI_QQDETAIL   *data = &ui_qqdetail;
    SLONG   i;
    
    if(data->cfa)
    {
        destroy_cake_frame_ani(&data->cfa);
        for(i=0; i<MAX_CAK_FRAME; i++)
        {
            data->cf[i] = NULL;
        }
    }
}

void    redraw_qq_detail(SLONG sx, SLONG sy, BMP *bitmap)
{
    UI_QQDETAIL   *data = &ui_qqdetail;
    CAKE_FRAME  *cf;
    SLONG   frame, x, y, id, event, xl;
    char    *pstr;
    char    buf[24];
    
    
    event = QQDETAIL_EVENT;
    
    //background------------------
    id = QQDETAIL_ID_BKGND;
    frame = QQDETAIL_FRAME_BKGND;
    cf = data->cf[frame];    
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);
    
    //button----------------------
    id = QQDETAIL_ID_OK;
    frame = QQDETAIL_FRAME_OK;
    if( data->active_id == id)
        frame += 2;
    else if( data->hilight_id == id)
        frame++;
    cf = data->cf[frame];        
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);
    
    //info-------------------------
    if ( data->pfriend )
    {
        if(data->pfriend->name[0] != '\0')
        {
            x = sx + QQDETAIL_NAME_SX;
            y = sy + QQDETAIL_NAME_SY;
            xl = QQDETAIL_NNGP_XL;
            pstr = data->pfriend->name;
            qq_draw_text(x, y, xl, pstr, 0xff, bitmap);
        }
        if(data->pfriend->nickname[0] != '\0')
        {
            x = sx + QQDETAIL_NICKNAME_SX;
            y = sy + QQDETAIL_NICKNAME_SY;
            xl = QQDETAIL_NNGP_XL;
            pstr = data->pfriend->nickname;
            qq_draw_text(x, y, xl, pstr, 0xff, bitmap);
        }
        if(data->pfriend->guild_name[0] != '\0')
        {
            x = sx + QQDETAIL_GUILD_SX;
            y = sy + QQDETAIL_GUILD_SY;
            xl = QQDETAIL_NNGP_XL;
            pstr = data->pfriend->guild_name;
            qq_draw_text(x, y, xl, pstr, 0xff, bitmap);
        }
        if(data->pfriend->partner_name[0] != '\0')
        {
            x = sx + QQDETAIL_PARTNER_SX;
            y = sy + QQDETAIL_PARTNER_SY;
            xl = QQDETAIL_NNGP_XL;
            pstr = data->pfriend->partner_name;
            qq_draw_text(x, y, xl, pstr, 0xff, bitmap);
        }
        if(data->pfriend->country != '\0')
        {
            x = sx + QQDETAIL_COUNTRY_SX;
            y = sy + QQDETAIL_COUNTRY_SY;
            xl = QQDETAIL_COUNTRY_XL;
            pstr = get_country_name(data->pfriend->country);
            qq_draw_text(x, y, xl, pstr, 0xff, bitmap);
        }
        
        x = sx + QQDETAIL_LEVEL_SX;
        y = sy + QQDETAIL_LEVEL_SY;
        xl = QQDETAIL_LEVEL_XL;
        sprintf((char*)buf, "%d", data->pfriend->level);
        qq_draw_text(x, y, xl, buf, 0xff, bitmap);
        
        x = sx + QQDETAIL_PK_SX;
        y = sy + QQDETAIL_PK_SY;
        xl = QQDETAIL_PMP_XL;
        sprintf((char*)buf, "%d", data->pfriend->pk);
        qq_draw_text(x, y, xl, buf, 0xff, bitmap);
        
        x = sx + QQDETAIL_MONEY_SX;
        y = sy + QQDETAIL_MONEY_SY;
        xl = QQDETAIL_PMP_XL;
        sprintf((char*)buf, "%d", data->pfriend->money);
        qq_draw_text(x, y, xl, buf, 0xff, bitmap);
        
        x = sx + QQDETAIL_PRESTIGE_SX;
        y = sy + QQDETAIL_PRESTIGE_SY;
        xl = QQDETAIL_PMP_XL;
        sprintf((char*)buf, "%d", data->pfriend->prestige);
        qq_draw_text(x, y, xl, buf, 0xff, bitmap);

        // character ICON ------------------------------------------------

        x = sx + QQDETAIL_ICON_SX;
        y = sy + QQDETAIL_ICON_SY;

        redraw_scale_manface( x, y, QQDETAIL_ICON_XL, QQDETAIL_ICON_YL, 
                                    &data->pfriend->manface, bitmap );
        
    }
}

SLONG    qq_detail_on_mm(SLONG sx, SLONG sy, SLONG id)
{
    ui_qqdetail.hilight_id = id;
    return 0;
}

SLONG    qq_detail_on_md(SLONG sx, SLONG sy, SLONG button, SLONG id)
{
    switch( id)
    {
    case QQDETAIL_ID_OK:
        ui_qqdetail.active_id = id;
        break;
    default:
        break;
    }
    return 0;
}

SLONG    qq_detail_on_mu(SLONG sx, SLONG sy, SLONG button, SLONG id)
{
    SLONG result = 1;
    switch( id)
    {
    case QQDETAIL_ID_OK:
        if( ui_qqdetail.active_id == id)
        {
            if( ui_qqdetail.parent_id == QQMAIN_EVENT)
                ui_qqmain.function_id = 0;
            else if(ui_qqdetail.parent_id == QQFIND3_EVENT)
                ui_qqfind3.function_id = 0;
            else if(ui_qqdetail.parent_id == QQPOPUP_EVENT)
            {
                ui_qqpopup.function_id = 0;
                ui_qqmain.function_id = 0;
            }
            result = 0;
        }
    }
    ui_qqdetail.active_id = 0;
    return result;
}

/******************************************************************************************************************/
/* UI QQ FIND1                                                                                                    */
/******************************************************************************************************************/
SLONG    init_qq_find1_image(void)
{
    USTR    filename[_MAX_FNAME];
    SLONG   result, i, frames, valid_frames;
    CAKE_FRAME_ANI  *cfa;
    UI_QQFIND1 *data = &ui_qqfind1;
    
    data->cfa = NULL;
    for(i=0; i<32; i++)
    {
        data->cf[i] = NULL;
    }
    
    set_data_file(packed_menu_file);
    strcpy((char *)filename, "menu\\qqfind1.cak");
    result = load_cake_frame_ani_from_file((USTR*)filename, &data->cfa);
    if(TTN_OK != result)
        return  -1;
    frames = count_cake_frames(data->cfa);
    valid_frames = min(frames, MAX_CAK_FRAME);
    for(i=0; i<valid_frames; i++)
    {
        cfa = get_specify_cake_frame_ani(data->cfa, i);
        data->cf[i] = cfa->cake_frame;
    }
    
    data->hilight_id = 0;
    data->active_id = 0;
    data->function_id = 0;
    data->selected_id = QQFIND1_ID_ITEM1;
    //
    //
    return  TTN_OK;
    
}

void    free_qq_find1_image(void)
{
    UI_QQFIND1   *data = &ui_qqfind1;
    SLONG   i;
    
    if(data->cfa)
    {
        destroy_cake_frame_ani(&data->cfa);
        for(i=0; i<MAX_CAK_FRAME; i++)
        {
            data->cf[i] = NULL;
        }
    }
}

void    redraw_qq_find1(SLONG sx, SLONG sy, BMP *bitmap)
{
    UI_QQFIND1   *data = &ui_qqfind1;
    CAKE_FRAME  *cf;
    SLONG   frame, x, y, id, event;
    static buf[20];
    
    if( data->function_id == QQFIND1_ID_NEXT)
    {
        if( data->selected_id == QQFIND1_ID_ITEM1)
        {
            redraw_qq_find3(sx, sy, bitmap);
            return;
        }
        else if( data->selected_id == QQFIND1_ID_ITEM2)
        {
            redraw_qq_find2(sx, sy, bitmap);
            return;
        }
        else if ( data->selected_id == QQFIND1_ID_ITEM3 )
        {
            redraw_qq_find2( sx, sy, bitmap );
            return;
        }
    }
    event = QQFIND1_EVENT;
    
    //background------------------
    id = QQFIND1_ID_BKGND;
    frame = QQFIND1_FRAME_BKGND;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);
    
    //button----------------------
    id = QQFIND1_ID_NEXT;
    frame = QQFIND1_FRAME_NEXT;
    if( data->active_id == id)
        frame += 2;
    else if( data->hilight_id == id)
        frame++;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);
    
    id = QQFIND1_ID_CANCEL;
    frame = QQFIND1_FRAME_CANCEL;
    if( data->active_id == id)
        frame += 2;
    else if( data->hilight_id == id)
        frame++;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

    //online player ----------------
    sprintf((char*)buf, "%d", ui_qq.total_players);
    qq_draw_text_16(QQFIND1_COUNT_SX, QQFIND1_COUNT_SY, 10*TE_FONT_SIZE_16, 
                        (char*)buf, 0xff, bitmap);
    
    //selected----------------------
    id = QQFIND1_ID_ITEM1;
    game_range.add( QQFIND1_ITEM1_SX, QQFIND1_ITEM1_SY,
        QQFIND1_ITEM_XL, QQFIND1_ITEM_YL,
        event,id);
    
    id = QQFIND1_ID_ITEM2;
    game_range.add(QQFIND1_ITEM2_SX, QQFIND1_ITEM2_SY,
        QQFIND1_ITEM_XL, QQFIND1_ITEM_YL,
        event,id);

//    id = QQFIND1_ID_ITEM3;
//    game_range.add( QQFIND1_ITEM3_SX, QQFIND1_ITEM3_SY,
//        QQFIND1_ITEM_XL, QQFIND1_ITEM_YL,
//        event, id );

    if( data->selected_id == QQFIND1_ID_ITEM1)
    {
        ui_qqfind3.add_group = QQ_MY_FRIENDS;    // add a friend ( or a guild member )
        id = QQFIND1_ID_SELECT1;
        x  = QQFIND1_SELECT1_SX;
        y  = QQFIND1_SELECT1_SY;
    }
    else if(data->selected_id == QQFIND1_ID_ITEM2)
    {
        ui_qqfind3.add_group = QQ_MY_FRIENDS;    // add a friend ( or a guild member )
        id = QQFIND1_ID_SELECT2;
        x  = QQFIND1_SELECT2_SX;
        y  = QQFIND1_SELECT2_SY;
    }
    else if ( data->selected_id == QQFIND1_ID_ITEM3 )
    {
        ui_qqfind3.add_group = QQ_UNDESIREDERS;    // add a black list member
        id = QQFIND1_ID_SELECT3;
        x  = QQFIND1_SELECT3_SX;
        y  = QQFIND1_SELECT3_SY;
    }
    
    put_circle(x, y, 1, true2hi(U4_SYSTEM_RED), bitmap);
    put_circle(x, y, 2, true2hi(U4_SYSTEM_RED), bitmap);
    
}

SLONG    qq_find1_on_mm(SLONG sx, SLONG sy, SLONG id)
{
    ui_qqfind1.hilight_id = id;
    return 0;
}

SLONG    qq_find1_on_md(SLONG sx, SLONG sy, SLONG button, SLONG id)
{
    switch(id)
    {
    case QQFIND1_ID_NEXT:
    case QQFIND1_ID_CANCEL:
        ui_qqfind1.active_id = id;
        break;
    case QQFIND1_ID_ITEM1:
        ui_qqfind1.selected_id = id;
        break;
    case QQFIND1_ID_ITEM2:
        ui_qqfind1.selected_id = id;
        break;
    default:
        break;
    }
    return 0;
}

SLONG    qq_find1_on_mu(SLONG sx, SLONG sy, SLONG button, SLONG id)
{
    SLONG result = 1;
    UI_QQFIND1   *data = &ui_qqfind1;

    switch(id)
    {
    case QQFIND1_ID_NEXT:
        if( data->active_id == id)
        {
            if( data->selected_id == QQFIND1_ID_ITEM1)
            {
                qq_search_online();
                qq_find3_start();
                ui_qqfind3.parent_id = QQFIND1_EVENT;
                data->function_id = QQFIND1_ID_NEXT;
                result = 0;
            }
            else if( data->selected_id == QQFIND1_ID_ITEM2)
            {
                ui_qqfind2.function_id = 0;
                data->function_id = QQFIND1_ID_NEXT;

                //get online players count
                qq_client_request_player_count();
                result = 0;
            }
        }
        break;
    case QQFIND1_ID_CANCEL:
        if( data->active_id == id)
        {
            ui_qqmain.function_id = 0;
            qq_find1_end();
            result = 0;
        }
        break;
    default:
        break;
    }
    data->active_id = 0;    
    return result;
}


void    qq_find1_start(void)
{
    ui_qq.end_func = qq_find1_end;
}


void    qq_find1_end(void)
{
    UI_QQFIND1 *data = &ui_qqfind1;
    data->function_id = 0;
    data->selected_id = QQFIND1_ID_ITEM1;
    ui_qq.end_func = NULL;
}

/******************************************************************************************************************/
/* UI QQ FIND2                                                                                                    */
/******************************************************************************************************************/
SLONG    init_qq_find2_image(void)
{
    USTR    filename[_MAX_FNAME];
    SLONG   result, i, frames, valid_frames;
    CAKE_FRAME_ANI  *cfa;
    UI_QQFIND2 *data = &ui_qqfind2;
    
    data->cfa = NULL;
    for(i=0; i<32; i++)
    {
        data->cf[i] = NULL;
    }
    
    set_data_file(packed_menu_file);
    strcpy((char *)filename, "menu\\qqfind2.cak");
    result = load_cake_frame_ani_from_file((USTR*)filename, &data->cfa);
    if(TTN_OK != result)
        return  -1;
    frames = count_cake_frames(data->cfa);
    valid_frames = min(frames, MAX_CAK_FRAME);
    for(i=0; i<valid_frames; i++)
    {
        cfa = get_specify_cake_frame_ani(data->cfa, i);
        data->cf[i] = cfa->cake_frame;
    }
    
    data->hilight_id = 0;
    data->active_id = 0;
    data->function_id = 0;
    //
    //

    data->pname = te_create( QQFIND2_NAME_SX, QQFIND2_NAME_SY, 
                             QQFIND2_INPUT_XL, QQFIND2_INPUT_YL, 
                             QQ_NAME_SIZE+1 );

    data->pnickname = te_create( QQFIND2_NICKNAME_SX, QQFIND2_NICKNAME_SY, 
                                 QQFIND2_INPUT_XL, QQFIND2_INPUT_YL, 
                                 QQ_NAME_SIZE+1 );

    data->pguild = te_create( QQFIND2_GUILD_SX, QQFIND2_GUILD_SY,
                              QQFIND2_INPUT_XL, QQFIND2_INPUT_YL,
                              QQ_GUILD_NAME_SIZE + 1 );


    data->plevel = te_create( QQFIND2_LEVEL_SX, QQFIND2_LEVEL_SY,
                              QQFIND2_INPUT_XL, QQFIND2_INPUT_YL,
                              QQ_LEVEL_SIZE + 1 );

    te_set_active( data->pname, TRUE );
    te_set_active( data->pnickname, TRUE );
    te_set_active( data->pguild, TRUE );
    te_set_active( data->plevel, TRUE );

    te_set_single_line( data->pname, TRUE );
    te_set_single_line( data->pnickname, TRUE );
    te_set_single_line( data->pguild, TRUE );
    te_set_single_line( data->plevel, TRUE );

    te_set_number_only(data->plevel, TRUE);

    // 國家的下拉框
    data->pcountry = create_combobox( );
    for ( i = COUNTRY_CHINA; i <= COUNTRY_INDIA; i ++ )
        add_combobox_item( data->pcountry, (USTR*)get_country_name( i ), i );

    set_combobox_pos( data->pcountry, QQFIND2_COUNTRY_SX, QQFIND2_COUNTRY_SY );
    set_combobox_edit_wh( data->pcountry, QQFIND2_INPUT_XL, QQFIND2_INPUT_YL );
    set_combobox_lines( data->pcountry, 5 );
    set_combobox_default( data->pcountry, 0 );

    add_combobox_to_list( data->pcountry );
    set_combobox_enable( data->pcountry, COMBOBOX_ENABLE );
    set_combobox_font_size( data->pcountry, COMBOBOX_FONT_12 );

    return  TTN_OK;
}

void    free_qq_find2_image(void)
{
    UI_QQFIND2   *data = &ui_qqfind2;
    SLONG   i;
    
    te_destroy( data->pname );
    data->pname = NULL;
    
    te_destroy( data->pnickname );
    data->pnickname = NULL;

    te_destroy( data->pguild );
    data->pguild = NULL;

    te_destroy( data->plevel );
    data->plevel = NULL;

    destroy_combobox( data->pcountry );
    data->pcountry = NULL;

    if(data->cfa)
    {
        destroy_cake_frame_ani(&data->cfa);
        for(i=0; i<MAX_CAK_FRAME; i++)
        {
            data->cf[i] = NULL;
        }
    }
}


void    redraw_qq_find2(SLONG sx, SLONG sy, BMP *bitmap)
{
    UI_QQFIND2   *data = &ui_qqfind2;
    CAKE_FRAME  *cf;
    SLONG   frame, x, y, id, event;
    static char    buf[20];
    
    if (data->function_id == QQFIND2_ID_NEXT)
    {
        redraw_qq_find3(sx, sy, bitmap);
        return;
    }

    
    event = QQFIND2_EVENT;
    
    //background------------------
    id = QQFIND2_ID_BKGND;
    frame = QQFIND2_FRAME_BKGND;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);
    
    //button----------------------
    id = QQFIND2_ID_LAST;
    frame = QQFIND2_FRAME_LAST;
    if( data->active_id == id)
        frame += 2;
    else if( data->hilight_id == id)
        frame++;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);
    
    id = QQFIND2_ID_NEXT;
    frame = QQFIND2_FRAME_NEXT;
    if( data->active_id == id)
        frame += 2;
    else if( data->hilight_id == id)
        frame++;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);
    
    id = QQFIND2_ID_CANCEL;
    frame = QQFIND2_FRAME_CANCEL;
    if( data->active_id == id)
        frame += 2;
    else if( data->hilight_id == id)
        frame++;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

    //online player ----------------
    sprintf((char*)buf, "%d", ui_qq.total_players);
    qq_draw_text_16(QQFIND2_COUNT_SX, QQFIND2_COUNT_SY, 10*TE_FONT_SIZE_16, 
        (char*)buf, 0xff, bitmap);
    
    redraw_te( data->pname, bitmap );
    redraw_te( data->pnickname, bitmap );
    redraw_te( data->pguild, bitmap );
    redraw_te( data->plevel, bitmap );

//    redraw_combobox( bitmap );
}

SLONG    qq_find2_on_mm(SLONG sx, SLONG sy, SLONG id)
{
    ui_qqfind2.hilight_id = id;
    return 0;
}

SLONG    qq_find2_on_md(SLONG sx, SLONG sy, SLONG button, SLONG id)
{
    LPUI_QQFIND2 data = &ui_qqfind2;

    switch( id)
    {
    case QQFIND2_ID_BKGND:
    case QQFIND2_ID_LAST:
    case QQFIND2_ID_NEXT:
    case QQFIND2_ID_CANCEL:
        data->active_id = id;
        break;
        
    default:
        data->active_id = 0;
        break;
    }
    return 0;
}

SLONG    qq_find2_on_mu(SLONG sx, SLONG sy, SLONG button, SLONG id)
{
    SLONG result = 1;
    LPUI_QQFIND2 data = &ui_qqfind2;

    switch (id)
    {
    case QQFIND2_ID_BKGND:
        break;
    case QQFIND2_ID_NEXT:
        if (data->active_id == id)
        {
            if ( TTN_OK == qq_find2_search())
            {
                qq_find3_start();
                ui_qqfind3.parent_id = QQFIND2_EVENT;
                data->function_id = id;
            }
            result = 0;
        }
        break;
    case QQFIND2_ID_NAME:
    case QQFIND2_ID_NICKNAME:
    case QQFIND2_ID_GUILD:
//    case QQFIND2_ID_COUNTRY:
    case QQFIND2_ID_LEVEL:
        break;
    case QQFIND2_ID_CANCEL:
        if (data->active_id == id)
        {
            ui_qqmain.function_id = 0;
            qq_find2_end();
            result = 0;
        }
        break;
    case QQFIND2_ID_LAST:
        if (data->active_id == id)
        {
            ui_qqfind1.function_id = 0;
            qq_client_request_player_count();
            qq_find1_start();
            result = 0;
        }
        break;
    default:
        break;
    }
    data->active_id = 0;
    return result;
}


SLONG qq_find2_search(void)
{
    UI_QQSEARCH_FILTER pf;
    LPUI_QQFIND2 data = &ui_qqfind2;
    char *temp;
    SLONG n = 0;
    SLONG result;

    ZeroMemory(&pf, sizeof(UI_QQSEARCH_FILTER));

    if (te_get_size( data->pname) > 0)
        strcpy((char*)&pf.name, data->pname->ptext_buf);
    else
        ++n;

    if (te_get_size( data->pnickname) > 0)
        strcpy((char*)&pf.nickname, data->pnickname->ptext_buf);
    else
        ++n;
    
    if (te_get_size( data->pguild ) > 0)
        strcpy((char*)&pf.guild_name, data->pguild->ptext_buf);
    else
        ++n;
    
//    if (te_get_size(&data->country) > 0)
//        strcpy((char*)&pf.country, data->country.ptext_buf);
//    else
//        ++n;

    if (te_get_size( data->plevel) > 0)
        pf.level = strtoul( data->plevel->ptext_buf, &temp, 10);
    else
        ++n;

    /*
     *    MESSAGE: must input one or more seach filter
     */
    if ( n == 4)
    {
        qq_msgbox( QQ_MB_FIND2_1, QQMB_TITLE_WARNING, 
                    QQMB_TEXT_SEARCH2, UIMB_OK, 0);
        result = TTN_NOT_OK;
    }
    else
    {
        if (!ui_qqfind3.filter)
            ui_qqfind3.filter = (UI_QQSEARCH_FILTER*)GlobalAlloc(GPTR, sizeof( UI_QQSEARCH_FILTER ) );
        CopyMemory( ui_qqfind3.filter, &pf, sizeof( UI_QQSEARCH_FILTER ) );
        result = qq_search(&pf);
    }

    return result;
}

void qq_find2_start()
{
    UI_QQFIND2 *data = &ui_qqfind2;
    if (ui_qq.end_func)
        ui_qq.end_func();
    ui_qq.end_func = qq_find2_end;
}

void qq_find2_end()
{
    UI_QQFIND2 *data = &ui_qqfind2;
    data->function_id = 0;
    data->hilight_id  = 0;
    ui_qq.end_func = NULL;
//    ui_qq.input_focus = 0;
    qq_find1_end();
    te_set_text( data->pname, NULL );
    te_set_text( data->pnickname, NULL );
    te_set_text( data->pguild, NULL );
    te_set_text( data->plevel, NULL );
}
/******************************************************************************************************************/
/* UI QQ FIND3                                                                                                    */
/******************************************************************************************************************/
SLONG    init_qq_find3_image(void)
{
    USTR    filename[_MAX_FNAME];
    SLONG   result, i, frames, valid_frames;
    CAKE_FRAME_ANI  *cfa;
    UI_QQFIND3 *data = &ui_qqfind3;
    
    data->cfa = NULL;
    for(i=0; i<32; i++)
    {
        data->cf[i] = NULL;
    }
    
    set_data_file(packed_menu_file);
    strcpy((char *)filename, "menu\\qqfind3.cak");
    result = load_cake_frame_ani_from_file((USTR*)filename, &data->cfa);
    if(TTN_OK != result)
        return  -1;
    frames = count_cake_frames(data->cfa);
    valid_frames = min(frames, MAX_CAK_FRAME);
    for(i=0; i<valid_frames; i++)
    {
        cfa = get_specify_cake_frame_ani(data->cfa, i);
        data->cf[i] = cfa->cake_frame;
    }
    
    data->hilight_id = 0;
    data->active_id = 0;
    data->function_id = 0;
    data->parent_id = 0;
    data->search_index = 0;
    data->selected_id = -1;
    data->filter = NULL;
    return  TTN_OK;
}


void    free_qq_find3_image(void)
{
    UI_QQFIND3   *data = &ui_qqfind3;
    SLONG   i;
    
    if(data->cfa)
    {
        destroy_cake_frame_ani(&data->cfa);
        for(i=0; i<MAX_CAK_FRAME; i++)
        {
            data->cf[i] = NULL;
        }
    }
    if (data->filter)
    {
        GlobalFree(data->filter);
        data->filter = NULL;
    }
}

void redraw_qq_find3(SLONG sx, SLONG sy, BMP *bitmap)
{
    UI_QQFIND3   *data = &ui_qqfind3;
    CAKE_FRAME  *cf;
    SLONG   frame, x, y, id, event;
    
    
    event = QQFIND3_EVENT;

    if (data->function_id == QQFIND3_ID_NEXT)
    {
        redraw_qq_verify(sx, sy, bitmap);
        return;
    }

    
    //background------------------
    id = QQFIND3_ID_BKGND;
    frame = QQFIND3_FRAME_BKGND;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);
    
    //button----------------------
    id = QQFIND3_ID_DETAIL;
    frame = QQFIND3_FRAME_DETAIL;
    if( data->active_id == id)
        frame += 2;
    else if( data->hilight_id == id)
        frame++;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);
    
    id = QQFIND3_ID_LAST;
    frame = QQFIND3_FRAME_LAST;
    if (data->active_id == id)
        frame += 2;
    else if (data->hilight_id == id)
        frame++;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    if (data->in_search)
        gray_put_rle(x, y, cf->rle, bitmap);
    else
    {
        put_rle(x, y, cf->rle, bitmap);
        game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);
    }
    
    id = QQFIND3_ID_NEXT;
    frame = QQFIND3_FRAME_NEXT;
    if (data->active_id == id)
        frame += 2;
    else if (data->hilight_id == id)
        frame++;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    if (data->in_search)
        gray_put_rle(x, y, cf->rle, bitmap);
    else
    {
        put_rle(x, y, cf->rle, bitmap);
        game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);
    }
    
    id = QQFIND3_ID_CANCEL;
    frame = QQFIND3_FRAME_CANCEL;
    if( data->active_id == id)
        frame += 2;
    else if( data->hilight_id == id)
        frame++;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);
    
    //up down button--------------------------
    id = QQFIND3_ID_UP;
    frame = QQFIND3_FRAME_UP;
    if( data->hilight_id == id)
        frame++;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    if (data->in_search)
        gray_put_rle(x, y, cf->rle, bitmap);
    else
    {
        put_rle(x, y, cf->rle, bitmap);
        game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);
    }
    
    id = QQFIND3_ID_DOWN;
    frame = QQFIND3_FRAME_DOWN;
    if( data->hilight_id == id)
        frame++;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    if (data->in_search)
        gray_put_rle(x, y, cf->rle, bitmap);
    else
    {
        put_rle(x, y, cf->rle, bitmap);
        game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);
    }
    
    //show players detail------------------------
    SLONG n, i, max, index, hilight_id = -1;
    LPUI_QQFRIEND p;

//    data->selected_id = -1;
    id = QQFIND3_ID_LIST;
    y = QQFIND3_LIST_SY;
    n = QQFIND3_LIST_YL/QQ_FONT_HEIGHT;
    if (data->hilight_id>>16 == id)
        hilight_id = data->hilight_id&0x0000ffff;
    if (data->function_id>>16 == id)
        data->selected_id = data->function_id&0x0000ffff;
//    else
//        data->selected_id = -1;

    max = qq_search_count();

    for (i = 0; i < n; i++)
    {
        index = i + data->search_index;
        if (index >= max)
            break;
        p = qq_search_get(data->search_index + i);

        if (hilight_id >= 0 && i == hilight_id)
            qq_find3_show_list(y, p, bitmap, QQFIND3_LIST_HILIGHT);
        else if (data->selected_id >= 0 && i == data->selected_id - data->search_index)
            qq_find3_show_list(y, p, bitmap, QQFIND3_LIST_SELECTED);
        else
            qq_find3_show_list(y, p, bitmap, QQFIND3_LIST_NORMAL);

        game_range.add(QQFIND3_LIST_NAME_SX, y, 
                        QQFIND3_LIST_XL, QQ_FONT_HEIGHT, event, (id<<16)|i);

        y += QQ_FONT_HEIGHT;
    }

    // draw detail ---------------------------------------
    if (data->function_id == QQFIND3_ID_DETAIL)
            redraw_qq_detail(sx, sy, bitmap);

}


SLONG qq_find3_on_mm(SLONG sx, SLONG sy, SLONG id)
{
    ui_qqfind3.hilight_id = id;
    return 0;
}


SLONG qq_find3_on_md(SLONG sx, SLONG sy, SLONG button, SLONG id)
{
    LPUI_QQFIND3 data = &ui_qqfind3;
    SLONG result = 1;

    if (data->function_id == QQFIND3_ID_DETAIL)
        return result;
    switch(id)
    {
    case QQFIND3_ID_DETAIL:
    case QQFIND3_ID_LAST:
    case QQFIND3_ID_NEXT:
    case QQFIND3_ID_CANCEL:
        data->active_id = id;
        break;
    case QQFIND3_ID_UP:
        if (data->search_index > 0)
            data->search_index -= (QQFIND3_LIST_YL/QQ_FONT_HEIGHT-1);
        if (data->search_index < 0)
            data->search_index = 0;
        data->active_id = id;
        break;
    case QQFIND3_ID_DOWN:
        if (data->parent_id == QQFIND1_EVENT)
            qq_search_online_again();
        else
            qq_search_again(data->filter);
        if (data->search_index < qq_search_count() - QQFIND3_LIST_YL/QQ_FONT_HEIGHT)
            data->search_index += (QQFIND3_LIST_YL/QQ_FONT_HEIGHT-1);
        data->active_id = id;

        /* todo: search again */

        break;
    default:
        if (id>>16 == QQFIND3_ID_LIST)
            data->active_id = id + data->search_index;
        break;
    }
    return 0;
}


SLONG    qq_find3_on_mu(SLONG sx, SLONG sy, SLONG button, SLONG id)
{
    LPUI_QQFIND3 data = &ui_qqfind3;
    SLONG result = 1;
    switch (id)
    {
    case QQFIND3_ID_DETAIL:
        if (data->active_id == id)
        {
            if (data->search_index >= 0)
            {
                data->function_id = id;
                ui_qqdetail.parent_id = QQFIND3_EVENT;
                /* TODO: get friend information from server */
                ui_qqdetail.pfriend = qq_search_get(data->selected_id);
                qq_client_request_query_someone( ui_qqdetail.pfriend->sid );
                memcpy( &ui_qqdetail.friend_info, ui_qqdetail.pfriend, sizeof(UI_QQFRIEND) );
                ui_qqdetail.pfriend = &ui_qqdetail.friend_info;
                result = 0;
            }
        }
        break;
    case QQFIND3_ID_NEXT:
        if (data->active_id == id)
        {
            data->function_id = id;
            
            qq_find3_add_friend();
            result = 0;
        }
        break;
    case QQFIND3_ID_UP:
    case QQFIND3_ID_DOWN:
        break;
    case QQFIND3_ID_CANCEL:
        if (data->active_id == id)
        {
            qq_find3_end();
            result = 0;
        }
        break;
    case QQFIND3_ID_LAST:
        if(data->active_id == id)
        {
            switch (data->parent_id)
            {
                case QQFIND1_EVENT:
                    ui_qqfind1.function_id = 0;
                    break;
                case QQFIND2_EVENT:
                    ui_qqfind2.function_id = 0;
                    break;
                default:
                    break;
            }
            result = 0;
        }
        break;
    default:
        if (data->active_id == id + data->search_index 
            && data->active_id>>16 == QQFIND3_ID_LIST)
        {
            data->function_id = id + data->search_index;
            result = 0;
        }
        break;
    }
    data->active_id = 0;
    return result;
}


void qq_find3_show_list(SLONG y, LPUI_QQFRIEND p, BMP *bitmap, SLONG flag)
{
    char level_buf[20];

    _itoa(p->level, level_buf, 10);
    switch (flag)
    {
        case QQFIND3_LIST_NORMAL:
            qq_draw_text(QQFIND3_LIST_NAME_SX,  y, QQFIND3_LIST_NAME_XL,  p->name,            QQ_FIND_LIST_COLOR, bitmap);
            qq_draw_text(QQFIND3_LIST_LEVEL_SX, y, QQFIND3_LIST_LEVEL_XL, level_buf, QQ_FIND_LIST_COLOR, bitmap);
            qq_draw_text(QQFIND3_LIST_GUILD_SX, y, QQFIND3_LIST_GUILD_XL, p->guild_name,    QQ_FIND_LIST_COLOR, bitmap);
            break;
        case QQFIND3_LIST_HILIGHT:
            qq_draw_hi_text(QQFIND3_LIST_NAME_SX,  y, QQFIND3_LIST_NAME_XL,  p->name,           QQ_FIND_LIST_COLOR, bitmap);
            qq_draw_hi_text(QQFIND3_LIST_LEVEL_SX, y, QQFIND3_LIST_LEVEL_XL, level_buf, QQ_FIND_LIST_COLOR, bitmap);
            qq_draw_hi_text(QQFIND3_LIST_GUILD_SX, y, QQFIND3_LIST_GUILD_XL, p->guild_name,    QQ_FIND_LIST_COLOR, bitmap);
            break;
        case QQFIND3_LIST_SELECTED:
            qq_draw_sel_text(QQFIND3_LIST_NAME_SX,  y, QQFIND3_LIST_NAME_XL,  p->name,            QQ_FIND_LIST_COLOR, bitmap);
            qq_draw_sel_text(QQFIND3_LIST_LEVEL_SX, y, QQFIND3_LIST_LEVEL_XL, level_buf, QQ_FIND_LIST_COLOR, bitmap);
            qq_draw_sel_text(QQFIND3_LIST_GUILD_SX, y, QQFIND3_LIST_GUILD_XL, p->guild_name,    QQ_FIND_LIST_COLOR, bitmap);
        default:
            break;
    }
}

void qq_find3_add_friend(void)
{
    LPUI_QQFRIEND p;
    LPUI_QQFIND3 data = &ui_qqfind3;

    if (data->selected_id >= 0)
    {
/*
        p = qq_search_get(data->selected_id);
        if (p)
        {
            if (qfs_check(p, NEED_VERIFY))
            {
                ui_qqverify.pfriend = p;
                qq_verify_start();
                return;
            }
            qf_add(p, qq_get_current_group());
            qfl_sort(qq_get_current_group());
        }
*/
        p = qq_search_get(data->selected_id);
        if (p)
        {
            if (p->sid == qfm_get_sid())
            {
                qq_msgbox( QQ_MB_FIND3_1, QQMB_TITLE_ERROR,
                                QQMB_TEXT_CANOT_ADD_SELF, UIMB_OK, 0);
                data->function_id = 0;
                data->selected_id = -1;
            }
            else if ( qf_get_by_sid( p->sid, QQ_MY_FRIENDS    ) ||
                      qf_get_by_sid( p->sid, QQ_GUILD_PLAYERS ) ||
                      qf_get_by_sid( p->sid, QQ_UNDESIREDERS  ) )
            {
                qq_msgbox( QQ_MB_FIND3_2, QQMB_TITLE_ERROR,
                                QQMB_TEXT_ALREADY_ADDED, UIMB_OK, 0);
                data->function_id = 0;
                data->selected_id = -1;
            }
            else
            {
                if ( data->add_group == QQ_UNDESIREDERS)
                {
                    qq_client_request_add_someone( p->sid, 1 );
                }
                else
                    qq_client_request_add_someone(p->sid, 0);
                qq_find3_end();
            }
        }
    }
    else
    {
        /* Message: Please selected one player */
        qq_msgbox(QQ_MB_SEARCH1, QQMB_TITLE_WARNING, 
                        QQMB_TEXT_SEARCH1, UIMB_OK, 0);
        data->function_id = 0;
    }
}

void qq_find3_start(void)
{
    ui_qq.end_func = qq_find3_end;
    ui_qqfind3.in_search = TRUE;
    ui_qqfind3.filter = NULL;
}

void qq_find3_end(void)
{
    UI_QQFIND3 *data = &ui_qqfind3;

    /*
     *    TODO: has bug here
     */
    switch (data->parent_id)
    {
    case QQFIND1_EVENT:
        ui_qqmain.function_id = 0;
        ui_qqfind1.function_id = 0;
        qq_find1_end();
        break;
    case QQFIND2_EVENT:
        ui_qqmain.function_id = 0;
        ui_qqfind2.function_id = 0;
        qq_find2_end();
        break;
    default:
        break;
    }
    data->function_id = 0;
    data->selected_id = -1;
    data->search_index = 0;
    /////////////////   TODO   ////////////////////////
//    ui_qq.input_focus = 0;
    ui_qq.end_func = NULL;
}
/******************************************************************************************************************/
/* UI QQ ITEM                                                                                                     */
/******************************************************************************************************************/
SLONG    init_qq_item_image(void)
{
    USTR    filename[_MAX_FNAME];
    SLONG   result, i, frames, valid_frames;
    CAKE_FRAME_ANI  *cfa;
    UI_QQITEM *data = &ui_qqitem;
    
    data->cfa = NULL;
    for(i=0; i<32; i++)
    {
        data->cf[i] = NULL;
    }
    
    set_data_file(packed_menu_file);
    strcpy((char *)filename, "menu\\qqitem.cak");
    result = load_cake_frame_ani_from_file((USTR*)filename, &data->cfa);
    if(TTN_OK != result)
        return  -1;
    frames = count_cake_frames(data->cfa);
    valid_frames = min(frames, MAX_CAK_FRAME);
    for(i=0; i<valid_frames; i++)
    {
        cfa = get_specify_cake_frame_ani(data->cfa, i);
        data->cf[i] = cfa->cake_frame;
    }
    
    data->hilight_id = 0;
    data->active_id = 0;
    data->function_id = 0;
    data->selected_index = 0;
    data->wait_send = FALSE;

    TPOS_ITEM item;
    SetItemNone( &item );

    for( i = 0; i < 3; i ++ )
        SetCharacterTransItem( g_lPlayerIndex, i, &item );
    //
    //
    return  TTN_OK;
}
void    free_qq_item_image(void)
{
    UI_QQITEM   *data = &ui_qqitem;
    SLONG   i;
    
    if(data->cfa)
    {
        destroy_cake_frame_ani(&data->cfa);
        for(i=0; i<MAX_CAK_FRAME; i++)
        {
            data->cf[i] = NULL;
        }
    }
}
void    redraw_qq_item(SLONG sx, SLONG sy, BMP *bitmap)
{
    CAKE_FRAME *cf;
    SLONG x, y, frame, id, event;
    UI_QQITEM *data = &ui_qqitem;
    
    event = QQITEM_EVENT;
    
    //    sy += QQ_CHATITEMLOGLIST_FIX_DY;
    
    //backbround ---------------------------
    id = QQITEM_ID_BKGND;
    frame = QQITEM_FRAME_BKGND;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);
    

    //item range --------------------------
    SLONG icon;
    TPOS_ITEM item;

    id = QQITEM_ID_ITEM1;
    x = sx + QQITEM_ITEM_SX;
    y = sy + QQITEM_ITEM_SY;
    game_range.add(x, y, QQITEM_ITEM_XL, QQITEM_ITEM_YL, event, id);

    GetCharacterTransItem( g_lPlayerIndex, 0, &item );
    if ( !IsItemNone( &item ) )
    {
        icon = GetItemIconIndex( &item );
        redraw_item_icon_image( x + ITEM_ICON_WIDTH/2, y + ITEM_ICON_HEIGHT/2, icon, bitmap );
    }
    
    id = QQITEM_ID_ITEM2;
    x = x + QQITEM_ITEM_STEP_X;
    game_range.add(x, y, QQITEM_ITEM_XL, QQITEM_ITEM_YL, event, id);

    GetCharacterTransItem( g_lPlayerIndex, 1, &item );
    if ( !IsItemNone( &item ) )
    {
        icon = GetItemIconIndex( &item );
        redraw_item_icon_image( x + ITEM_ICON_WIDTH/2, y + ITEM_ICON_HEIGHT/2, icon, bitmap );
    }
    
    
    id = QQITEM_ID_ITEM3;
    x = x + QQITEM_ITEM_STEP_X;
    game_range.add(x, y, QQITEM_ITEM_XL, QQITEM_ITEM_YL, event, id);

    GetCharacterTransItem( g_lPlayerIndex, 2, &item );
    if ( !IsItemNone( &item ) )
    {
        icon = GetItemIconIndex( &item );
        redraw_item_icon_image( x + ITEM_ICON_WIDTH/2, y + ITEM_ICON_HEIGHT/2, icon, bitmap );
    }
    
    id = QQITEM_ID_INPUT;
    x = QQITEM_INPUT_SX;
    game_range.add(x, y, QQITEM_INPUT_XL, QQITEM_INPUT_YL, event, id);

    //select range ------------------------
    if ( data->selected_index >= 0 )
    {
        id = QQITEM_ID_RANGE;
        frame = QQITEM_FRAME_RANGE;

        cf = data->cf[frame];
        x = sx + cf->frame_rx - QQITEM_ITEM_STEP_X * ( 2 - data->selected_index );
        y = sy + cf->frame_ry;
        put_rle(x, y, cf->rle, bitmap);
    }
}

SLONG    qq_item_on_mm(SLONG sx, SLONG sy, SLONG id)
{
    UI_QQITEM *data = &ui_qqitem;
    data->active_id = id;
    return 0;
}

SLONG    qq_item_on_md(SLONG sx, SLONG sy, SLONG button, SLONG id)
{
    SLONG result = 1;
    SLONG item_id = -1;
    UI_QQITEM *data = &ui_qqitem;

    if ( button !=     MK_LBUTTON )
        return result;

    data->active_id = id;

    switch ( id )
    {
    case QQITEM_ID_ITEM1:
        result = 0;
        item_id = 0;
        break;
    case QQITEM_ID_ITEM2:
        item_id = 1;
        result = 0;
        break;
    case QQITEM_ID_ITEM3:
        item_id = 2;
        result = 0;
        break;
    case QQITEM_ID_INPUT:
        break;
    default:
        data->active_id = 0;
        data->selected_index = 0;
        return result;
    }

    data->selected_index = item_id;

    qq_client_request_hit_trans_item( LEFT, (UCHAR)item_id );

    return result;
}

SLONG    qq_item_on_mu(SLONG sx, SLONG sy, SLONG button, SLONG id)
{
    SLONG result = 1;
    return result;
}


void    qq_item_start( void )
{
    UI_QQITEM *data = &ui_qqitem;

    data->selected_index = -1;
    data->send_money = 0;

}

void    qq_item_end( void )
{
    UI_QQITEM *data = &ui_qqitem;

    data->selected_index = 0;
    data->send_money = 0;
    data->active_id = 0;
    data->function_id = 0;
    data->hilight_id = 0;
    
}

/******************************************************************************************************************/
/* UI QQ LOG                                                                                                      */
/******************************************************************************************************************/
SLONG    init_qq_log_image(void)
{    
    USTR    filename[_MAX_FNAME];
    SLONG   result, i, frames, valid_frames;
    CAKE_FRAME_ANI  *cfa;
    UI_QQLOG *data = &ui_qqlog;
    
    data->cfa = NULL;
    for(i=0; i<32; i++)
    {
        data->cf[i] = NULL;
    }
    
    set_data_file(packed_menu_file);
    strcpy((char *)filename, "menu\\qqLog.cak");
    result = load_cake_frame_ani_from_file((USTR*)filename, &data->cfa);
    if(TTN_OK != result)
        return  -1;
    frames = count_cake_frames(data->cfa);
    valid_frames = min(frames, MAX_CAK_FRAME);
    for(i=0; i<valid_frames; i++)
    {
        cfa = get_specify_cake_frame_ani(data->cfa, i);
        data->cf[i] = cfa->cake_frame;
    }
    
    data->hilight_id = 0;
    data->active_id = 0;
    data->function_id = 0;

    data->ptext = te_create( QQLOG_LOG_SX, QQLOG_LOG_SY + QQ_CHATITEMLOGLIST_FIX_DY, 
                             QQLOG_LOG_XL, QQLOG_LOG_YL, QQLOG_BUF_SIZE );

    te_set_active( data->ptext, TRUE );
//    te_set_read_only( data->ptext, TRUE );

    //
    //
    return  TTN_OK;
}


void    free_qq_log_image(void)
{
    UI_QQLOG   *data = &ui_qqlog;
    SLONG   i;
    
    te_destroy( data->ptext );
    data->ptext = NULL;
    
    if(data->cfa)
    {
        destroy_cake_frame_ani(&data->cfa);
        for(i=0; i<MAX_CAK_FRAME; i++)
        {
            data->cf[i] = NULL;
        }
    }
}

void    redraw_qq_log(SLONG sx, SLONG sy, BMP *bitmap)
{
    CAKE_FRAME    *cf;
    UI_QQLOG    *data = &ui_qqlog;
    SLONG x, y, frame, id, event;
    
    event = QQLOG_EVENT;
    
    //    sy += QQ_CHATITEMLOGLIST_FIX_DY;
    
    //background -------------------------------
    id = QQLOG_ID_BKGND;
    frame = QQLOG_FRAME_BKGND;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);
    
    
    //up button --------------------------------
    id = QQLOG_ID_UP;
    frame = QQLOG_FRAME_UP;
    if(data->hilight_id == id && data->active_id != id)
        frame++;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);
    
    //down button ------------------------------
    id = QQLOG_ID_DOWN;
    frame = QQLOG_FRAME_DOWN;
    if(data->hilight_id == id && data->active_id != id)
        frame++;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

    //log text --------------------------------
    redraw_te( data->ptext, bitmap );
}

SLONG    qq_log_on_mm(SLONG sx, SLONG sy, SLONG id)
{
    ui_qqlog.hilight_id = id;
    return 0;
}

SLONG    qq_log_on_md(SLONG sx, SLONG sy, SLONG button, SLONG id)
{
    LPUI_QQLOG data = &ui_qqlog;
    
    switch ( id )
    {
    case QQLOG_ID_UP:
    case QQLOG_ID_DOWN:
    case QQLOG_ID_BKGND:
        data->active_id = id;
        break;
    }

    return 0;
}

SLONG    qq_log_on_mu(SLONG sx, SLONG sy, SLONG button, SLONG id)
{
    LPUI_QQLOG data = &ui_qqlog;

    switch ( id )
    {
    case QQLOG_ID_UP:
        break;
    case QQLOG_ID_DOWN:
        break;
    }

    return 0;
}

VOID qq_get_log_text( DWORD sid, DWORD index )
{

}

/******************************************************************************************************************/
/* UI QQ SET                                                                                                      */
/******************************************************************************************************************/
SLONG    init_qq_set_image(void)
{
    USTR    filename[_MAX_FNAME];
    SLONG   result, i, frames, valid_frames;
    CAKE_FRAME_ANI  *cfa;
    UI_QQSET *data = &ui_qqset;
    
    data->cfa = NULL;
    for(i=0; i<32; i++)
    {
        data->cf[i] = NULL;
    }
    
    set_data_file(packed_menu_file);
    strcpy((char *)filename, "menu\\qqSet.cak");
    result = load_cake_frame_ani_from_file((USTR*)filename, &data->cfa);
    if(TTN_OK != result)
        return  -1;
    frames = count_cake_frames(data->cfa);
    valid_frames = min(frames, MAX_CAK_FRAME);
    for(i=0; i<valid_frames; i++)
    {
        cfa = get_specify_cake_frame_ani(data->cfa, i);
        data->cf[i] = cfa->cake_frame;
    }
    
    data->hilight_id = 0;
    data->active_id = 0;
    data->function_id = 0;
    //
    //
    return  TTN_OK;
}

void    free_qq_set_image(void)
{
    UI_QQSET   *data = &ui_qqset;
    SLONG   i;
    
    if(data->cfa)
    {
        destroy_cake_frame_ani(&data->cfa);
        for(i=0; i<MAX_CAK_FRAME; i++)
        {
            data->cf[i] = NULL;
        }
    }
    return;
}

void    redraw_qq_set(SLONG sx, SLONG sy, BMP *bitmap)
{
    UI_QQSET   *data = &ui_qqset;
    CAKE_FRAME  *cf;
    SLONG   frame, x, y, id, event;
    
    
    event = QQSET_EVENT;
    
    //background------------------
    id = QQSET_ID_BKGND;
    frame = QQSET_FRAME_BKGND;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);
    
    //button---------------------
    id = QQSET_ID_DEFAULT;
    frame = QQSET_FRAME_DEFAULT;
    if( data->active_id == id)
        frame += 2;
    else if( data->hilight_id == id)
        frame++;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);
    
    id = QQSET_ID_OK;
    frame = QQSET_FRAME_OK;
    if( data->active_id == id)
        frame += 2;
    else if( data->hilight_id == id)
        frame++;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);
    
    id = QQSET_ID_CANCEL;
    frame = QQSET_FRAME_CANCEL;
    if( data->active_id == id)
        frame += 2;
    else if( data->hilight_id == id)
        frame++;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);
    
    //settings--------------------------------------
    id = QQSET_ID_SET1;
    game_range.add(QQSET_SET1_SX + sx, QQSET_SET1_SY,
        QQSET_SET1_XL, QQSET_SET1_YL, event, id);
    
    id = QQSET_ID_SET2;
    game_range.add(QQSET_SET2_SX + sx, QQSET_SET2_SY,
        QQSET_SET2_XL, QQSET_SET2_YL, event, id);
    
    id = QQSET_ID_SET3;
    game_range.add(QQSET_SET3_SX + sx, QQSET_SET3_SY,
        QQSET_SET3_XL, QQSET_SET3_YL, event, id);
    
    id = QQSET_ID_SET4;
    game_range.add(QQSET_SET4_SX + sx, QQSET_SET4_SY,
        QQSET_SET4_XL, QQSET_SET4_YL, event, id);
    
    id = QQSET_ID_SET5;
    game_range.add(QQSET_SET5_SX + sx, QQSET_SET5_SY,
        QQSET_SET5_XL, QQSET_SET5_YL, event, id);
    
    id = QQSET_ID_SET6;
    game_range.add(QQSET_SET6_SX + sx, QQSET_SET6_SY,
        QQSET_SET6_XL, QQSET_SET6_YL, event, id);
    
    id = QQSET_ID_SET7;
    game_range.add(QQSET_SET7_SX + sx, QQSET_SET7_SY,
        QQSET_SET7_XL, QQSET_SET7_YL, event, id);
    
    /*--==[data->options_draw]==--*/
    if (data->draw_settings&HIDE_LOGIN)
    {
        x = QQSET_SELECT1_SX + sx;
        y = QQSET_SELECT1_SY;
        put_circle(x, y, 1, true2hi(U4_SYSTEM_RED), bitmap);
        put_circle(x, y, 2, true2hi(U4_SYSTEM_RED), bitmap);
    }
    
    if (data->draw_settings&PUB_DETAIL)
    {
        x = QQSET_SELECT2_SX + sx;
        y = QQSET_SELECT2_SY;
        put_circle(x, y, 1, true2hi(U4_SYSTEM_RED), bitmap);
        put_circle(x, y, 2, true2hi(U4_SYSTEM_RED), bitmap);
    }

    if (data->draw_settings&AUTO_SHOW)
    {
        x = QQSET_SELECT3_SX + sx;
        y = QQSET_SELECT3_SY;
        put_circle(x, y, 1, true2hi(U4_SYSTEM_RED), bitmap);
        put_circle(x, y, 2, true2hi(U4_SYSTEM_RED), bitmap);
    }

    if (data->draw_settings&SHOW_ONLINE_ONLY)
    {
        x = QQSET_SELECT4_SX + sx;
        y = QQSET_SELECT4_SY;
        put_circle(x, y, 1, true2hi(U4_SYSTEM_RED), bitmap);
        put_circle(x, y, 2, true2hi(U4_SYSTEM_RED), bitmap);
    }

    if (data->draw_settings&FRIEND_ONLINE_BOX)
    {
        x = QQSET_SELECT5_SX + sx;
        y = QQSET_SELECT5_SY;
        put_circle(x, y, 1, true2hi(U4_SYSTEM_RED), bitmap);
        put_circle(x, y, 2, true2hi(U4_SYSTEM_RED), bitmap);
    }

    if (data->draw_settings&NEED_VERIFY)
    {
        x = QQSET_SELECT6_SX + sx;
        y = QQSET_SELECT6_SY;
        put_circle(x, y, 1, true2hi(U4_SYSTEM_RED), bitmap);
        put_circle(x, y, 2, true2hi(U4_SYSTEM_RED), bitmap);
    }

    if (data->draw_settings&KEEP_STRANGER_AWAY)
    {
        x = QQSET_SELECT7_SX + sx;
        y = QQSET_SELECT7_SY;
        put_circle(x, y, 1, true2hi(U4_SYSTEM_RED), bitmap);
        put_circle(x, y, 2, true2hi(U4_SYSTEM_RED), bitmap);
    }
    
}


SLONG    qq_set_on_mm(SLONG sx, SLONG sy, SLONG id)
{
    ui_qqset.hilight_id = id;
    return 0;
}


SLONG    qq_set_on_md(SLONG sx, SLONG sy, SLONG button, SLONG id)
{
    SLONG result = 1;
    UI_QQSET *data = &ui_qqset;

    switch (id)
    {
    case QQSET_ID_DEFAULT:
    case QQSET_ID_OK:
    case QQSET_ID_CANCEL:
        data->active_id = id;
        result = 0;
        break;
    case QQSET_ID_SET1:
    case QQSET_ID_SET2:
    case QQSET_ID_SET3:
    case QQSET_ID_SET4:
    case QQSET_ID_SET5:
    case QQSET_ID_SET6:
    case QQSET_ID_SET7:
    case QQSET_ID_SET8:
        if (data->draw_settings&id)
            data->draw_settings &= ~id;
        else
            data->draw_settings |= id;
        break;
    default:
        break;
    }
    return result;
}


SLONG    qq_set_on_mu(SLONG sx, SLONG sy, SLONG button, SLONG id)
{
    SLONG result = 1;
    UI_QQSET *data = &ui_qqset;

    switch( id)
    {
    case QQSET_ID_DEFAULT:
        if( ui_qqset.active_id == id)
        {
            /* TODO: add default settings */
            result = 0;
        }
        break;
    case QQSET_ID_OK:
        if( ui_qqset.active_id == id)
        {
            //ui_qqset.options_set = ui_qqset.options_draw;
            qfms_enable(data->draw_settings);
            qfms_disable(~(data->draw_settings));
            qfl_sort(ui_qqmain.list_group);

            qq_client_set_myconfig(data->draw_settings);
            
            ui_qqmain.function_id = 0;
            result = 0;
        }
        break;
    case QQSET_ID_CANCEL:
        if( ui_qqset.active_id == id)
        {
            ui_qqmain.function_id = 0;
            result = 0;
        }
        break;
    default:
        break;
    }
    ui_qqset.active_id = 0;
    return result;
}


/******************************************************************************************************************/
/* UI QQ VERIFY                                                                                                   */
/******************************************************************************************************************/
SLONG    init_qq_verify_image(void)
{
    USTR    filename[_MAX_FNAME];
    SLONG   result, i, frames, valid_frames;
    CAKE_FRAME_ANI  *cfa;
    UI_QQVERIFY *data = &ui_qqverify;
    
    data->cfa = NULL;
    for(i=0; i<32; i++)
    {
        data->cf[i] = NULL;
    }
    
    set_data_file(packed_menu_file);
    strcpy((char *)filename, "menu\\qqVerify.cak");
    result = load_cake_frame_ani_from_file((USTR*)filename, &data->cfa);
    if(TTN_OK != result)
        return  -1;
    frames = count_cake_frames(data->cfa);
    valid_frames = min(frames, MAX_CAK_FRAME);
    for(i=0; i<valid_frames; i++)
    {
        cfa = get_specify_cake_frame_ani(data->cfa, i);
        data->cf[i] = cfa->cake_frame;
    }
    
    data->hilight_id = 0;
    data->active_id = 0;
    data->function_id = 0;
    //
    //
    data->ptext = te_create( QQVERIFY_MSG_SX, QQVERIFY_MSG_SY,
                             QQVERIFY_MSG_XL, QQVERIFY_MSG_YL,
                             64 );
    te_set_active( data->ptext, TRUE );

    data->pfriend = NULL;
    return  TTN_OK;
}

void    free_qq_verify_image(void)
{
    UI_QQVERIFY *data = &ui_qqverify;
    SLONG   i;
    
    te_destroy( data->ptext );
    data->ptext = NULL;

    if(data->cfa)
    {
        destroy_cake_frame_ani(&data->cfa);
        for(i=0; i<MAX_CAK_FRAME; i++)
        {
            data->cf[i] = NULL;
        }
    }
}


void    redraw_qq_verify(SLONG sx, SLONG sy, BMP *bitmap)
{
    UI_QQVERIFY   *data = &ui_qqverify;
    CAKE_FRAME  *cf;
    SLONG   frame, x, y, id, event;

    event = QQVERIFY_EVENT;

    // background -----------------------
    id = QQVERIFY_ID_BKGND;
    frame = QQVERIFY_FRAME_BKGND;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);
    
    // send -----------------------------
    id = QQVERIFY_ID_SEND;
    frame = QQVERIFY_FRAME_SEND;
    if (data->active_id == id)
        frame += 2;
    else if (data->hilight_id == id)
        frame++;

    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

    // last -----------------------------
    id = QQVERIFY_ID_LAST;
    frame = QQVERIFY_FRAME_LAST;
    if (data->active_id == id)
        frame += 2;
    else if (data->hilight_id == id)
        frame++;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

    // finish ---------------------------
    id = QQVERIFY_ID_OK;
    frame = QQVERIFY_FRAME_OK;
    
    if (data->send_ok)
    {
        if (data->active_id == id)
            frame += 2;
        else if (data->hilight_id == id)
            frame++;
    }
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;

    if (data->send_ok)
    {
        put_rle(x, y, cf->rle, bitmap);
        game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);
    }
    else
        gray_put_rle(x, y, cf->rle, bitmap);

    // cancel ------------------------------
    id = QQVERIFY_ID_CANCEL;
    frame = QQVERIFY_FRAME_CANCEL;
    if (data->active_id == id)
        frame += 2;
    else if (data->hilight_id == id)
        frame++;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

    char buf[16];
    SLONG xl;
    // name ---------------------------------
    x = QQVERIFY_NAME_SX;
    y = QQVERIFY_INFO_SY;
    xl = QQVERIFY_NAME_XL;
    qq_draw_text_16(x, y, xl, data->pfriend->name, QQ_VERIFY_INFO_COLOR, bitmap);

    // level --------------------------------
    x = QQVERIFY_LEVEL_SX;
    y = QQVERIFY_INFO_SY;
    xl = QQVERIFY_LEVEL_XL;
    sprintf((char*)buf, "%d", data->pfriend->level);
    qq_draw_text_16(x, y, xl, buf, QQ_VERIFY_INFO_COLOR, bitmap);

    // guild --------------------------------
    x = QQVERIFY_GUILD_SX;
    y = QQVERIFY_INFO_SY;
    xl = QQVERIFY_GUILD_XL;
    qq_draw_text_16(x, y, xl, data->pfriend->guild_name, QQ_VERIFY_INFO_COLOR, bitmap);

    redraw_te( data->ptext, bitmap );
}

SLONG    qq_verify_on_mm(SLONG sx, SLONG sy, SLONG id)
{
    LPUI_QQVERIFY data = &ui_qqverify;
    data->hilight_id = id;
    return 0;
}

SLONG    qq_verify_on_md(SLONG sx, SLONG sy, SLONG button, SLONG id)
{
    LPUI_QQVERIFY data = &ui_qqverify;
    SLONG result = 1;
    switch (id)
    {
        case QQVERIFY_ID_BKGND:
        case QQVERIFY_ID_LAST:
        case QQVERIFY_ID_CANCEL:
        case QQVERIFY_ID_SEND:
        case QQVERIFY_ID_OK:
        case QQVERIFY_ID_INPUT_MESSAGE:
            data->active_id = id;
            result = 0;
            break;
    }

    return result;
}

SLONG    qq_verify_on_mu(SLONG sx, SLONG sy, SLONG button, SLONG id)
{
    LPUI_QQVERIFY data = &ui_qqverify;
    SLONG result = 1;

    switch (id)
    {
        case QQVERIFY_ID_SEND:
            /* todo send verify infomation */
            data->function_id = id;
            data->send_ok = true;
            break;
        case QQVERIFY_ID_CANCEL:
        case QQVERIFY_ID_OK:
        case QQVERIFY_ID_LAST:
            if (data->active_id == id)
            {
                data->function_id = id;
                qq_verify_end();
                result = 0;
            }
            break;
        default:
            break;
    }
    return result;
}


void qq_verify_start()
{
    LPUI_QQVERIFY data = &ui_qqverify;
    te_set_text( data->ptext, NULL );
    data->active_id = 0;
    data->function_id = 0;
    data->hilight_id = 0;
    data->send_ok = FALSE;
    if (ui_qq.end_func)
        ui_qq.end_func();
    ui_qq.end_func = qq_verify_end;
}

void qq_verify_end()
{
    LPUI_QQVERIFY data = &ui_qqverify;
    switch (data->function_id)
    {
    case QQVERIFY_ID_OK:
    case QQVERIFY_ID_CANCEL:
        ui_qqmain.function_id = 0;
        break;
    case QQVERIFY_ID_LAST:
        ui_qqfind3.function_id = 0;
        break;
    default:
        break;
    }
    te_set_active( data->ptext, FALSE );
    ui_qq.end_func = NULL;
}

/******************************************************************************************************************/
/* UI QQ VERIFY                                                                                                   */
/******************************************************************************************************************/
SLONG    init_qq_list_image(void)
{
    USTR    filename[_MAX_FNAME];
    SLONG   result, i, frames, valid_frames;
    CAKE_FRAME_ANI  *cfa;
    UI_QQLIST *data = &ui_qqlist;
    
    data->cfa = NULL;
    for(i=0; i<32; i++)
    {
        data->cf[i] = NULL;
    }
    
    set_data_file(packed_menu_file);
    strcpy((char *)filename, "menu\\qqList.cak");
    result = load_cake_frame_ani_from_file((USTR*)filename, &data->cfa);
    if(TTN_OK != result)
        return  -1;
    frames = count_cake_frames(data->cfa);
    valid_frames = min(frames, MAX_CAK_FRAME);
    for(i=0; i<valid_frames; i++)
    {
        cfa = get_specify_cake_frame_ani(data->cfa, i);
        data->cf[i] = cfa->cake_frame;
    }
    
    data->hilight_id = 0;
    data->active_id = 0;
    data->function_id = 0;

    data->index_start = 0;
    data->group = QQ_MY_FRIENDS;
    return  TTN_OK;
}

void    free_qq_list_image(void)
{
    UI_QQLIST   *data = &ui_qqlist;
    SLONG   i;
    
    if(data->cfa)
    {
        destroy_cake_frame_ani(&data->cfa);
        for(i=0; i<MAX_CAK_FRAME; i++)
        {
            data->cf[i] = NULL;
        }
    }
    return;
    
}

void redraw_qq_list(SLONG sx, SLONG sy, BMP *bitmap)
{
    SLONG frame, x, y, id, event;
    UI_QQLIST *data = &ui_qqlist;
    CAKE_FRAME *cf;
    UI_QQFRIEND *pf = NULL;
    SLONG        group = 0;
    SLONG        i;
    SLONG        color;
    
    event = QQLIST_EVENT;
    
    //    sy += QQ_CHATITEMLOGLIST_FIX_DY;
    
    //background -------------------------
    id = QQLIST_ID_BKGND;
    frame = QQLIST_FRAME_BKGND;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle( x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);
    
    
    //my friend button -------------------
    id = QQLIST_ID_MYFRIENDS;
    frame = QQLIST_FRAME_MYFRIENDS;
    if(data->active_id == id)
        frame += 2;
    else if(data->hilight_id == id)
        frame ++;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h,event, id);
    
    //team player button ------------------
    id = QQLIST_ID_TEAMPLAYERS;
    frame = QQLIST_FRAME_TEAMPLAYERS;
    if(data->active_id == id)
        frame += 2;
    else if(data->hilight_id == id)
        frame ++;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);
    
    //guild player button -----------------
    id = QQLIST_ID_GUILDPLAYERS;
    frame = QQLIST_FRAME_GUILDPLAYERS;
    if(data->active_id == id)
        frame += 2;
    else if( data->hilight_id == id)
        frame ++;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);
    
    //strangers player button --------------
    id = QQLIST_ID_STRANGERS;
    frame = QQLIST_FRAME_STRANGERS;
    if(data->active_id == id)
        frame+=2;
    else if(data->hilight_id == id)
        frame++;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);
    
    //undesireders player button ------------
    id = QQLIST_ID_UNDESIREDERS;
    frame = QQLIST_FRAME_UNDESIREDERS;
    if(data->active_id == id)
        frame+=2;
    else if(data->hilight_id == id)
        frame++;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);
    
    //send to multi button ------------------
    id = QQLIST_ID_SEND_TO_MUTIL;
    frame = QQLIST_FRAME_SEND_TO_MUTIL;
    if(data->active_id == id)
        frame += 2;
    else if(data->hilight_id == id)
        frame++;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);
    
    //up button -----------------------------
    id = QQLIST_ID_UP;
    frame = QQLIST_FRAME_UP;
    if(data->active_id == id || data->hilight_id == id)
        frame ++;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);
    
    //down buton ----------------------------
    id = QQLIST_ID_DOWN;
    frame = QQLIST_FRAME_DOWN;
    if(data->active_id == id || data->hilight_id == id)
        frame++;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

    //friend name list
    
    i = 0;

    while((pf = qf_get(i+data->index_start, data->group)) != NULL 
            && i < QQLIST_MAX_LIST)
    {
        x = sx + QQLIST_LIST_SX + (i&0x1)*QQLIST_LIST_ITEM_DX;
        y = QQLIST_LIST_SY + (i>>0x1)*QQLIST_LIST_ITEM_DY;
        id = QQLIST_ID_LIST<<16|i;
        color = QQ_FIND_LIST_COLOR;
        if (qf_get_state(pf) == QF_ONLINE)
            color = SYSTEM_DARK0;

        qq_draw_text(x, y, QQLIST_LIST_DX, pf->name, color, bitmap);
        game_range.add(x, y, QQLIST_LIST_DX, QQLIST_LIST_ITEM_DY, event, id);
        i ++;
    }
    
    //selected sign
}


SLONG    qq_list_on_mm(SLONG sx, SLONG sy, SLONG id)
{
    ui_qqlist.hilight_id = id;
    return 0;
}


SLONG    qq_list_on_md(SLONG sx, SLONG sy, SLONG button, SLONG id)
{
    SLONG result = 1;
    UI_QQLIST *data = &ui_qqlist;
    SLONG    max_index;

    switch(id)
    {
    case QQLIST_ID_BKGND:
    case QQLIST_ID_MYFRIENDS:
    case QQLIST_ID_TEAMPLAYERS:
    case QQLIST_ID_GUILDPLAYERS:
    case QQLIST_ID_STRANGERS:
    case QQLIST_ID_UNDESIREDERS:
    case QQLIST_ID_SEND_TO_MUTIL:
        data->active_id = id;
        result = 0;
        break;
    case QQLIST_ID_UP:
        data->active_id = id;
        data->index_start -= QQLIST_MAX_LIST;
        if (data->index_start < 0)
            data->index_start = 0;
        result = 0;
        break;
    case QQLIST_ID_DOWN:
        if (qfms_check(SHOW_ONLINE_ONLY))
            max_index = qfl_online_count(data->group);
        else
            max_index = *qfl_pcount(data->group);
        if ((data->index_start + QQLIST_MAX_LIST) < max_index)
            data->index_start += QQLIST_MAX_LIST;
        
        data->active_id = id;
        result = 0;
        break;
    }
    return result;
}

SLONG    qq_list_on_mu(SLONG sx, SLONG sy, SLONG button, SLONG id)
{
    SLONG result = 1;
    UI_QQLIST *data = &ui_qqlist;

    switch(id)
    {
    case QQLIST_ID_BKGND:
        if (data->active_id == id)
        {
            data->function_id = id;
            data->active_id = 0;
            result = 0;
        }
        break;
    case QQLIST_ID_MYFRIENDS:
        if (data->active_id == id)
        {
            data->group = QQ_MY_FRIENDS;
            data->function_id = id;
            data->active_id = 0;
            result = 0;
        }
        break;
    case QQLIST_ID_TEAMPLAYERS:
        if (data->active_id == id)
        {
            data->group = QQ_TEAM_PLAYERS;
            data->function_id = id;
            data->active_id = 0;
            result = 0;
        }
        break;
    case QQLIST_ID_GUILDPLAYERS:
        if (data->active_id == id)
        {
            data->group = QQ_GUILD_PLAYERS;
            data->function_id = id;
            data->active_id = 0;
            result = 0;
        }
        break;
    case QQLIST_ID_STRANGERS:
        if (data->active_id == id)
        {
            data->group = QQ_STRANGERS;
            data->function_id = id;
            data->active_id = 0;
            result = 0;
        }
        break;
    case QQLIST_ID_UNDESIREDERS:
        if (data->active_id == id)
        {
            data->group = QQ_UNDESIREDERS;
            data->function_id = id;
            data->active_id = 0;
            result = 0;
        }
        break;
    case QQLIST_ID_SEND_TO_MUTIL:
        if (data->active_id == id)
        {
            /* TODO : add send code.*/
            data->function_id = id;
            data->active_id = 0;
            result = 0;
        }
        break;
    case QQLIST_ID_UP:
    case QQLIST_ID_DOWN:
        if (data->active_id == id)
        {
            data->function_id = id;
            data->active_id = 0;
            result = 0;
        }
        break;
    }

    return result;
}

/******************************************************************************************************************/
/* UI QQ HISTORY TEXT                                                                                             */
/******************************************************************************************************************/
SLONG    init_qq_his_image(void)
{
    USTR    filename[_MAX_FNAME];
    SLONG   result, i, frames, valid_frames;
    CAKE_FRAME_ANI  *cfa;
    UI_QQHIS *data = &ui_qqhis;
    
    data->cfa = NULL;
    for(i=0; i<32; i++)
    {
        data->cf[i] = NULL;
    }
    
    set_data_file(packed_menu_file);
    strcpy((char *)filename, "menu\\qqHis.cak");
    result = load_cake_frame_ani_from_file((USTR*)filename, &data->cfa);
    if(TTN_OK != result)
        return  -1;
    frames = count_cake_frames(data->cfa);
    valid_frames = min(frames, MAX_CAK_FRAME);
    for(i=0; i<valid_frames; i++)
    {
        cfa = get_specify_cake_frame_ani(data->cfa, i);
        data->cf[i] = cfa->cake_frame;
    }
    
    data->hilight_id = 0;
    data->active_id = 0;
    data->function_id = 0;

    return  TTN_OK;
}


void    free_qq_his_image(void)
{
    UI_QQHIS   *data = &ui_qqhis;
    SLONG   i;
    
    if(data->cfa)
    {
        destroy_cake_frame_ani(&data->cfa);
        for(i=0; i<MAX_CAK_FRAME; i++)
        {
            data->cf[i] = NULL;
        }
    }
}


void    redraw_qq_his(SLONG sx, SLONG sy, BMP *bitmap)
{
    UI_QQHIS *data = &ui_qqhis;
    SLONG    event, id;
    SLONG    frame, x, y;
    CAKE_FRAME *cf;

    event = QQHIS_EVENT;

    /* draw backgroup */
    id = QQHIS_ID_BKGND;
    frame = QQHIS_FRAME_BKGND;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);
    
    /* draw button */
    id = QQHIS_ID_OK;
    frame = QQHIS_FRAME_OK;
    if (data->hilight_id == id)
        frame++;
    if (data->active_id == id)
        frame++;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

    id = QQHIS_ID_CANCEL;
    frame = QQHIS_FRAME_CANCEL;
    if (data->hilight_id == id)
        frame++;
    if(data->active_id == id)
        frame++;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

    /* up down arrow*/
    id = QQHIS_ID_UP;
    frame = QQHIS_FRAME_UP;
    if (data->active_id == id)
        frame++;
    cf = data->cf[frame];
    x = cf->frame_rx;
    y = cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

    id = QQHIS_ID_DOWN;
    frame = QQHIS_FRAME_DOWN;
    if (data->active_id == id)
        frame++;
    cf = data->cf[frame];
    x = cf->frame_rx;
    y = cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

    /* draw text */
}


SLONG    qq_his_on_mm(SLONG sx, SLONG sy, SLONG id)
{
    SLONG result = 1;
    UI_QQHIS *data = &ui_qqhis;

    data->hilight_id = id;
    return result;
}


SLONG    qq_his_on_md(SLONG sx, SLONG sy, SLONG button, SLONG id)
{
    SLONG result = 1;
    UI_QQHIS *data = &ui_qqhis;

    switch (id)
    {
    case QQHIS_ID_BKGND:
    case QQHIS_ID_OK:
    case QQHIS_ID_CANCEL:
    case QQHIS_ID_UP:
    case QQHIS_ID_DOWN:
        data->active_id = id;
        result = 0;
        break;
    default:
        break;
    }
    return result;
}


SLONG    qq_his_on_mu(SLONG sx, SLONG sy, SLONG button, SLONG id)
{
    SLONG result = 1;
    UI_QQHIS *data = &ui_qqhis;

    switch (id)
    {
    case QQHIS_ID_BKGND:
    case QQHIS_ID_UP:
    case QQHIS_ID_DOWN:
        if (data->active_id == id)
        {
            data->function_id = id;
            data->active_id = 0;
            result = 0;
        }
        break;
    case QQHIS_ID_OK:
    case QQHIS_ID_CANCEL:
        if (data->active_id == id)
        {
            qq_his_end();
            result = 0;
        }
    default:
        break;
    }
    return result;
}


void    qq_his_start(void)
{
}


void    qq_his_end(void)
{
    UI_QQHIS *data    = &ui_qqhis;
    data->active_id   = 0;
    data->function_id = 0;
    data->index       = 0;
    ui_qqmain.function_id = 0;

}
/******************************************************************************************************************/
/* UI QQ DRAW TEXT                                                                                                */
/******************************************************************************************************************/
void qq_draw_text(SLONG sx, SLONG sy, SLONG sl, char *pstr, DWORD txt_color, BMP *bitmap)
{
    SLONG n;
    char *p;
    
    set_word_color(0, (UHINT)txt_color);

    strcpy((char*)print_rec, (const char*)pstr);

    n = sl/QQ_FONT_WIDTH_HALF;

    if( strlen((const char*)print_rec) > (ULONG)n)
    {
        p = (char*)print_rec;
        n -= 3;
        while( p - (char*)print_rec < n)
            p = CharNext(p);

        p[0] = '.';
        p[1] = '.';
        p[2] = '\0';
    }
    
    print12( sx, sy, (USTR*)print_rec, PEST_PUT, bitmap);
    set_word_color( 0, SYSTEM_WHITE);
}


void qq_draw_hi_text(SLONG sx, SLONG sy, SLONG sl, char *pstr, DWORD txt_color, BMP *bitmap)
{
    SLONG n;
    char *p;

    set_word_color(0, (UHINT)txt_color);
    strcpy((char*)print_rec, (const char*)pstr);
    
    n = sl/QQ_FONT_WIDTH_HALF;

    if( strlen((const char*)print_rec) > (ULONG)n)
    {
        p = (char*)print_rec;
        n -= 3;
        while( p - (char*)print_rec < n)
            p = CharNext(p);

        p[0] = '.';
        p[1] = '.';
        p[2] = '\0';
    }

    print12( sx, sy, (USTR*)print_rec, COPY_PUT_COLOR(SYSTEM_DARK5), bitmap);

    set_word_color( 0, SYSTEM_WHITE);
}


void qq_draw_sel_text(SLONG sx, SLONG sy, SLONG sl, char *pstr, DWORD txt_color, BMP *bitmap)
{
    SLONG n;
    char *p;

    set_word_color(0, (UHINT)txt_color);
    strcpy((char*)print_rec, (const char*)pstr);
    
    n = sl/QQ_FONT_WIDTH_HALF;

    if( strlen((const char*)print_rec) > (ULONG)n)
    {
        p = (char*)print_rec;
        n -= 3;
        while( p - (char*)print_rec < n)
            p = CharNext(p);

        p[0] = '.';
        p[1] = '.';
        p[2] = '\0';
    }

    print12( sx, sy, (USTR*)print_rec, COPY_PUT_COLOR(SYSTEM_DARK3), bitmap);

    set_word_color( 0, SYSTEM_WHITE);

}

void qq_draw_text_16(SLONG sx, SLONG sy, SLONG sl, char *pstr, DWORD txt_color, BMP *bitmap)
{
    SLONG n;
    char *p;
    
    set_word_color(0, (UHINT)txt_color);

    strcpy((char*)print_rec, (const char*)pstr);

    n = sl/QQ_FONT_WIDTH_HALF_16;

    if( strlen((const char*)print_rec) > (ULONG)n)
    {
        p = (char*)print_rec;
        n -= 3;
        while( p - (char*)print_rec < n)
            p = CharNext(p);

        p[0] = '.';
        p[1] = '.';
        p[2] = '\0';
    }
    
    print16( sx, sy, (USTR*)print_rec, PEST_PUT, bitmap);
    set_word_color( 0, SYSTEM_WHITE);
}


/*
 *    draw mouse hit
 */
void redraw_uiqq_mouse_point_info(SLONG event, SLONG id, BMP *bitmap)
{
    switch (event)
    {
    case QQMAIN_EVENT:
        switch (id)
        {
        case QQMAIN_ID_MAXIMIZE:
            redraw_event_info_bar(event, id, (USTR*)TEXTMSG_MENU_MAXIMIZE, 
                                    (USTR*)TEXTMSG_MENU_MAXIMIZE_INFO, bitmap);
            break;
        case QQMAIN_ID_MINIMIZE:
            redraw_event_info_bar(event, id, (USTR*)TEXTMSG_MENU_MINIMIZE, 
                                    (USTR*)TEXTMSG_MENU_MINIMIZE_INFO, bitmap);
            break;
        case QQMAIN_ID_CALLGM:
            redraw_event_info_bar(event, id, (USTR*)QQTXT_CALLGM, 
                            (USTR*)QQTXT_CALLGM_INFO, bitmap);
            break;
        case QQMAIN_ID_SEARCH:
            redraw_event_info_bar(event, id, (USTR*)QQTXT_SEARCH,
                            (USTR*)QQTXT_SEARCH_INFO, bitmap);
            break;
        case QQMAIN_ID_SWITCH_LOGIN_STATE:
            if (qfms_get_state() == QF_ONLINE)
                redraw_event_info_bar(event, id, (USTR*)QQTXT_HIDE_LOGIN,
                            (USTR*)QQTXT_HIDE_LOGIN_INFO, bitmap);
            else
                redraw_event_info_bar(event, id, (USTR*)QQTXT_ONLINE_LOGIN,
                            (USTR*)QQTXT_ONLINE_LOGIN_INFO, bitmap);

            break;
        case QQMAIN_ID_SYSSET:
            redraw_event_info_bar(event, id, (USTR*)QQTXT_SYSSET,
                                    (USTR*)QQTXT_SYSSET_INFO, bitmap);
            break;
        case QQMAIN_ID_MESSAGE:
            redraw_event_info_bar(event, id, (USTR*)QQTXT_MESSAGE,
                                    (USTR*)QQTXT_MESSAGE_INFO, bitmap);
            break;
        }
        break;
    }
}

/************************************************************************/
/* QQ MessageBox                                                        */
/************************************************************************/

void qq_msgbox(DWORD event, char *title, char *text, DWORD type, DWORD time)
{
    LPUIMSGBOX p;
    if ( NULL != ( p = new_msgbox() ) )
    {
        p->font_size = TE_FONT_SIZE_12;
        p->disp_time = time;
        p->msgbox_type = type;
        p->pfunc = qq_msgbox_callback;
        p->param.event_id = event;
        lstrcpy(p->title_info, title);
        lstrcpy(p->text_info, text);

        msg_box(-1, -1, p);

        del_msgbox(p);
    }
}

/********************************************************************/
/* MessageBox Callback function                                     */
/********************************************************************/

void    qq_msgbox_callback( DWORD param, SLONG result )
{
}

void qq_del_friend_callback( DWORD param, SLONG result )
{
    SLONG friend_group = 0;
    SLONG index;
    UIMB_PARAM *p;

    if ( result == MSG_BOX_ID_CANCEL )
        return;

    p = ( UIMB_PARAM *)param;

    friend_group = qf_get_group_by_sid( p->event_id );
    
    switch (friend_group)
    {
    case QQ_GUILD_PLAYERS:
        qq_client_request_del_guild_friend( p->event_id );
        break;
    case QQ_MY_FRIENDS:
        qq_client_request_del_friend( p->event_id );
        break;
    case QQ_STRANGERS:
        index = qf_get_index_by_sid( p->event_id, friend_group );
        qf_delete( index, friend_group);
        break;
    //TODO: delete from BLACK LIST
    // case QQ_UNDESIREDERS:
    //        break;
    default:
        break;
    }
    
}
/************************************************************************/
/* Other functions                                                      */
/************************************************************************/

void ui_qq_set_online_count(DWORD count)
{
    ui_qq.total_players = count;
}

void ui_qq_show_msg(void)
{
    char *p_text;
    SLONG index, group;
    DWORD sid;

    if (qq_chat_check())
    {
        p_text = qq_chat_get_first(&index, &group, &sid);
//        ui_qqchat.read_only = TRUE;
        te_set_read_only( ui_qqchat.ptext, TRUE );
        ui_qqchat.sid = sid;
        te_set_text( ui_qqchat.ptext, p_text );
        ui_qqmain.function_id = QQMAIN_ID_CHAT; 
    }
}

void ui_qq_find3_search_end(void)
{
    ui_qqfind3.in_search = FALSE;
}


void ui_qq_set_detail( LPUI_QQFRIEND p )
{
    LPUI_QQDETAIL data = &ui_qqdetail;

    if ( p )
    {
        memcpy( &data->friend_info, p, sizeof(UI_QQFRIEND) );
    }
}


void    ui_qq_get_item( DWORD ID )
{
    SLONG group;
    SLONG index;
    CHAR  name[32];
    UI_QQFRIEND f;
    UI_QQFRIEND *p;

    group = qf_get_group_by_sid( ID );

    if (NULL == ( p = qf_get_by_sid( ID, group ) ) )
    {
        if (qfms_check(KEEP_STRANGER_AWAY))
            return;
        
        ZeroMemory( &f, sizeof(f) );
        p = &f;
        
        p->sid = ID;
        
        wsprintf(name, "%s%d", QQTXT_STRANGER_NAME, qfl_count(QQ_STRANGERS));
        lstrcpyn(p->name, name, 32);
        
        qf_add(p, QQ_STRANGERS);
        
        group = QQ_STRANGERS;
        
        if ( NULL == ( p = qf_get_by_sid( ID, group) ) )
            return;
    }
    
    index = qf_get_index(p, group);
    if (index == -1)
        return;
    
    qq_chat_add_chat( index, group, ID, QQTXT_RECEIVE_ITEM );

}

void    ui_qq_send_item_failed( DWORD ID )
{
    SLONG group;
    SLONG index;
    CHAR  name[32];
    UI_QQFRIEND f;
    UI_QQFRIEND *p;
    
    group = qf_get_group_by_sid( ID );
    
    if (NULL == ( p = qf_get_by_sid( ID, group ) ) )
    {
        if (qfms_check(KEEP_STRANGER_AWAY))
            return;
        
        ZeroMemory( &f, sizeof(f) );
        p = &f;
        
        p->sid = ID;
        
        wsprintf(name, "%s%d", QQTXT_STRANGER_NAME, qfl_count(QQ_STRANGERS));
        lstrcpyn(p->name, name, 32);
        
        qf_add(p, QQ_STRANGERS);
        
        group = QQ_STRANGERS;
        
        if ( NULL == ( p = qf_get_by_sid( ID, group) ) )
            return;
    }
    
    index = qf_get_index(p, group);
    if (index == -1)
        return;
    
    qq_chat_add_chat( index, group, ID, QQERR_SEND_ITEM_FAILED );

    ui_qqitem.wait_send = FALSE;
}


void    ui_qq_send_item_ok( DWORD ID )
{
    ui_qqitem.wait_send = FALSE;
}
