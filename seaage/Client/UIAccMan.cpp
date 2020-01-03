/*
**  UIAccMan.cpp
**  ui account manager functions.
**
**  Jack, 2002.5.28.
*/
#include "MainFun.h"
#include "NetGE_MainFunc.h"
#include "ClientMain.h"
#include "CRange.h"
#include "ErrorMsg.h"
#include "UIPosIME.h"
#include "UI.h"
#include "AccountDetails.h"
#include "Client_RecvMsg.h"
#include "Client_SendMsg.h"


ACCOUNT_INFO        account_info;       //information of user account
ACCMANAGER_DATA     accmanager_data;    //account manager
CHECKPOINTS_DATA    checkpoints_data;   //check points
CHANGEPASSWORD_DATA changepassword_data;//change password
CREATEACCOUNT_DATA  createaccount_data; //create account(step1):account & password
SETUPRECORD_DATA    setuprecord_data;   //create account(step2):setup user information
SELECTPAYMENT_DATA  selectpayment_data; //create account(step3):select payment type

//local functions:
SLONG   on_change_password(void);
SLONG   on_create_account_next_step(void);
SLONG   on_create_account_final_step(void);
SLONG   check_setup_record_combobox(void);
SLONG   check_select_payment_combobox(void);


//////////////////////////////////////////////////////////////////////////////////////////////
// ACCOUNT MANAGER(帳號管理)                                                                //
//////////////////////////////////////////////////////////////////////////////////////////////
void    init_account_info(void)
{
    ACCOUNT_INFO    *data = &account_info;

    memset(data->account, 0x00, 32);
    memset(data->password, 0x00, 32);
    memset(data->verify_password, 0x00, 32);
    //
    memset(data->name, 0x00, 32);
    data->sex = SEX_MALE;
    data->year = 1970;
    data->month = 1;
    data->day = 1;
    memset(data->locate, 0x00, 16);
    memset(data->occupation, 0x00, 16);
    memset(data->city, 0x00, 16);
    memset(data->address, 0x00, 64);
    memset(data->telephone, 0x00, 32);
    memset(data->email, 0x00, 64);
}


int     init_account_manager(void)
{
    USTR    filename[_MAX_FNAME];
    SLONG   result, i, frames;
    CAKE_FRAME_ANI  *cfa;
    ACCMANAGER_DATA *data = &accmanager_data;

    data->cfa = NULL;
    for(i=0; i<32; i++)
    {
        data->cf[i] = NULL;
    }

    set_data_file(packed_menu_file);
    strcpy((char *)filename, "menu\\accman.cak");
    result = load_cake_frame_ani_from_file((USTR*)filename, &data->cfa);
    if(TTN_OK != result)
        return  -1;
    frames = count_cake_frames(data->cfa);
    for(i=0; i<frames; i++)
    {
        cfa = get_specify_cake_frame_ani(data->cfa, i);
        data->cf[i] = cfa->cake_frame;
    }

    data->hilight_id = 0;
    data->active_id = 0;
    //
    return  0;
}


void    active_account_manager(int active)
{
}


void    free_account_manager(void)
{
    ACCMANAGER_DATA *data = &accmanager_data;    
    SLONG   i;

    if(data->cfa)
    {
        destroy_cake_frame_ani(&data->cfa);
        for(i=0; i<32; i++)
        {
            data->cf[i] = NULL;
        }
    }
    return;
}


void    refresh_account_manager(void)
{
}


void    redraw_account_manager(SLONG sx, SLONG sy, void *vbitmap)
{
    ACCMANAGER_DATA *data = &accmanager_data;    
    BMP *bitmap = (BMP*)vbitmap;
    CAKE_FRAME  *cf;
    SLONG   frame, x, y, id, event;

    event = ACCMANAGER_EVENT;
    game_range.clear();

    //(1) background -------------------------------------------
    frame = ACCMANAGER_FRAME_BKGND;
    id = ACCMANAGER_ID_BKGND;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

    //(3) back button ------------------------------------------
    frame = ACCMANAGER_FRAME_BACK;
    id = ACCMANAGER_ID_BACK;
    if(data->active_id == id)
        frame += 2;
    else if(data->hilight_id == id)
        frame += 1;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

    //(4) check points button ---------------------------------
    frame = ACCMANAGER_FRAME_CHECK_POINTS;
    id = ACCMANAGER_ID_CHECK_POINTS;
    if(data->active_id == id)
        frame += 2;
    else if(data->hilight_id == id)
        frame += 1;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

    //(4) modify record button ---------------------------------
    frame = ACCMANAGER_FRAME_MODIFY_RECORD;
    id = ACCMANAGER_ID_MODIFY_RECORD;
    if(data->active_id == id)
        frame += 2;
    else if(data->hilight_id == id)
        frame += 1;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

    //(5) modify record button ---------------------------------
    frame = ACCMANAGER_FRAME_CHANGE_PASSWORD;
    id = ACCMANAGER_ID_CHANGE_PASSWORD;
    if(data->active_id == id)
        frame += 2;
    else if(data->hilight_id == id)
        frame += 1;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

    //(4) supply points button -----------------------------------
    frame = ACCMANAGER_FRAME_SUPPLY_POINTS;
    id = ACCMANAGER_ID_SUPPLY_POINTS;
    if(data->active_id == id)
        frame += 2;
    else if(data->hilight_id == id)
        frame += 1;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);
}


SLONG   handle_account_manager(UINT message, WPARAM wParam, LPARAM lParam)
{
    ACCMANAGER_DATA *data = &accmanager_data;
    static  SLONG   mouse_x, mouse_y;
    SLONG   event_type, event_id;
    int iRet;

    switch(message)
    {
    case WM_MOUSEMOVE:
        mouse_x = GET_X_LPARAM(lParam);
        mouse_y = GET_Y_LPARAM(lParam);
        event_type = event_id = 0;
        game_range.mapping(mouse_x, mouse_y, &event_type, &event_id);
        data->hilight_id = event_id;
        break;
    case WM_LBUTTONDOWN:
        {
            mouse_x = GET_X_LPARAM(lParam);
            mouse_y = GET_Y_LPARAM(lParam);
            event_type = event_id = 0;
            game_range.mapping(mouse_x, mouse_y, &event_type, &event_id);
            switch(event_id)
            {
            case ACCMANAGER_ID_BACK:
                data->active_id = event_id;
                iRet = ClientLogoutDoor();
                set_next_app_state(APPSTATE_INIT_LOGIN);
                change_app_state();
                break;
            case ACCMANAGER_ID_CHECK_POINTS:
                data->active_id = event_id;
                //TODO:
                break;
            case ACCMANAGER_ID_MODIFY_RECORD:
                data->active_id = event_id;
                set_next_app_state(APPSTATE_INIT_MODIFY_RECORD);
                change_app_state();
                break;
            case ACCMANAGER_ID_CHANGE_PASSWORD:
                data->active_id = event_id;
                set_next_app_state(APPSTATE_INIT_CHANGE_PASSWORD);
                change_app_state();
                break;
            case ACCMANAGER_ID_SUPPLY_POINTS:
                data->active_id = event_id;
                set_next_app_state(APPSTATE_INIT_SUPPLY_POINTS);
                change_app_state();
                break;
            }
        }
        break;
    case WM_LBUTTONUP:
        data->active_id = 0;
        break;
    }
    return  0;
}

//////////////////////////////////////////////////////////////////////////////////////////////
// CREATE ACCOUNT(創建帳號)                                                                 //
//////////////////////////////////////////////////////////////////////////////////////////////
int     init_create_account(void)
{
    USTR    filename[_MAX_FNAME];
    SLONG   result, i, frames;
    CAKE_FRAME_ANI  *cfa;
    CREATEACCOUNT_DATA *data = &createaccount_data;

    data->cfa = NULL;
    for(i=0; i<32; i++)
    {
        data->cf[i] = NULL;
    }

    set_data_file(packed_menu_file);
    strcpy((char *)filename, "menu\\newacc1.cak");
    result = load_cake_frame_ani_from_file((USTR*)filename, &data->cfa);
    if(TTN_OK != result)
        return  -1;
    frames = count_cake_frames(data->cfa);
    for(i=0; i<frames; i++)
    {
        cfa = get_specify_cake_frame_ani(data->cfa, i);
        data->cf[i] = cfa->cake_frame;
    }

    data->hilight_id = 0;
    data->active_id = 0;
    data->function_id = 0;
    //
    return  0;
}


void    active_create_account(int active)
{
}


void    free_create_account(void)
{
    CREATEACCOUNT_DATA *data = &createaccount_data;
    SLONG   i;

    if(data->cfa)
    {
        destroy_cake_frame_ani(&data->cfa);
        for(i=0; i<32; i++)
        {
            data->cf[i] = NULL;
        }
    }
    return;
}


void    refresh_create_account(void)
{
}


void    redraw_create_account(SLONG sx, SLONG sy, void *vbitmap)
{
    BMP *bitmap = (BMP*)vbitmap;
    CAKE_FRAME  *cf;
    SLONG   frame, x, y, xl, yl, id, event, len;
    CREATEACCOUNT_DATA *data = &createaccount_data;
    ACCOUNT_INFO    *accinfo = &account_info;
    USTR    info[64], mask[64];

    event = CREATEACCOUNT_EVENT;
    game_range.clear();

    //(0) background upper --------------------------------------
    frame = CREATEACCOUNT_FRAME_BKGND;
    id = CREATEACCOUNT_ID_BKGND;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

    //(1) account ------------------------------------------------
    id = CREATEACCOUNT_ID_ACCOUNT;
    x = sx + CREATEACCOUNT_ACCOUNT_BAR_SX;
    y = sy + CREATEACCOUNT_ACCOUNT_BAR_SY;
    xl = CREATEACCOUNT_ACCOUNT_BAR_XL;
    yl = CREATEACCOUNT_ACCOUNT_BAR_YL;
    game_range.add(x, y, xl, yl, event, id);
    len = strlen((const char *)accinfo->account);
    if(data->function_id == id)
        sprintf((char *)info, "~C3%s_~C0", accinfo->account);
    else
        sprintf((char *)info, "~C3%s~C0", accinfo->account);
    set_word_color(3, rgb2hi(237, 98, 55));
    print24(x + 16, y + 4, (USTR*)info, PEST_PUT, bitmap);
    set_word_color(3, rgb2hi(0, 0, 255));

    //(2) password ----------------------------------------------
    id = CREATEACCOUNT_ID_PASSWORD;
    x = sx + CREATEACCOUNT_PASSWORD_BAR_SX;
    y = sy + CREATEACCOUNT_PASSWORD_BAR_SY;
    xl = CREATEACCOUNT_PASSWORD_BAR_XL;
    yl = CREATEACCOUNT_PASSWORD_BAR_YL;
    game_range.add(x, y, xl, yl, event, id);
    len = strlen((const char *)accinfo->password);
    memset(mask, '\0', 64);
    memset(mask, '*', len);
    if(data->function_id == id)
        sprintf((char *)info, "~C3%s_~C0", mask);
    else
        sprintf((char *)info, "~C3%s~C0", mask);
    set_word_color(3, rgb2hi(237, 98, 55));
    print24(x + 16, y + 4, (USTR*)info, PEST_PUT, bitmap);
    set_word_color(3, rgb2hi(0, 0, 255));

    //(3) verify new password -----------------------------------
    id = CREATEACCOUNT_ID_VERIFY_PASSWORD;
    x = sx + CREATEACCOUNT_VERIFY_PASSWORD_BAR_SX;
    y = sy + CREATEACCOUNT_VERIFY_PASSWORD_BAR_SY;
    xl = CREATEACCOUNT_VERIFY_PASSWORD_BAR_XL;
    yl = CREATEACCOUNT_VERIFY_PASSWORD_BAR_YL;
    game_range.add(x, y, xl, yl, event, id);
    len = strlen((const char *)accinfo->verify_password);
    memset(mask, '\0', 64);
    memset(mask, '*', len);
    if(data->function_id == id)
        sprintf((char *)info, "~C3%s_~C0", mask);
    else
        sprintf((char *)info, "~C3%s~C0", mask);
    set_word_color(3, rgb2hi(237, 98, 55));
    print24(x + 16, y + 4, (USTR*)info, PEST_PUT, bitmap);
    set_word_color(3, rgb2hi(0, 0, 255));

    //(4) next button ---------------------------------------------
    frame = CREATEACCOUNT_FRAME_NEXT_STEP;
    id = CREATEACCOUNT_ID_NEXT_STEP;
    if(data->active_id == id)
        frame += 2;
    else if(data->hilight_id == id)
        frame += 1;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

    //(5) back button -------------------------------------------
    frame = CREATEACCOUNT_FRAME_LAST_STEP;
    id = CREATEACCOUNT_ID_LAST_STEP;
    if(data->active_id == id)
        frame += 2;
    else if(data->hilight_id == id)
        frame += 1;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);
}


SLONG   on_create_account_next_step(void)
{
    ACCOUNT_INFO *data = &account_info;
    //TPOS_REGISTERINFO   RegisterInfo;
    int iRet;

    if(0 == strcmpi((const char *)data->account, ""))
    {
        display_error_message((USTR*)ERRMSG_MUST_INPUT_ACCOUNT, DISPLAY_MESSAGE_TO_SCREEN, screen_buffer);
        wait_key_time(' ', 80);
        return  -1;
    }
    if(0 == strcmpi((const char *)data->password, ""))
    {
        display_error_message((USTR*)ERRMSG_MUST_INPUT_PASSWORD, DISPLAY_MESSAGE_TO_SCREEN, screen_buffer);
        wait_key_time(' ', 80);
        return  -2;
    }
    if(0 == strcmpi((const char *)data->verify_password, ""))
    {
        display_error_message((USTR*)ERRMSG_MUST_INPUT_VERIFY_PASSWORD, DISPLAY_MESSAGE_TO_SCREEN, screen_buffer);
        wait_key_time(' ', 80);
        return  -3;
    }
    if(0 != strcmpi((const char *)data->password, (const char *)data->verify_password))
    {
        display_error_message((USTR*)ERRMSG_MUST_CONFIRM_PASSWORD, DISPLAY_MESSAGE_TO_SCREEN, screen_buffer);
        wait_key_time(' ', 80);
        return  -4;
    }


    //strcpy((char *)RegisterInfo.cId, (const char *)data->account);
    //strcpy((char *)RegisterInfo.cPw, (const char *)data->password);
    //iRet = PosRegisterAccountCheck(RegisterInfo);
    iRet = ClientRequestRegisterAccountChecking((char *)data->account, (char *)data->password);
    set_next_app_state(APPSTATE_INIT_SETUP_RECORD);

    return  0;
}


SLONG   handle_create_account(UINT message, WPARAM wParam, LPARAM lParam)
{
    CREATEACCOUNT_DATA *data = &createaccount_data;
    ACCOUNT_INFO    *accinfo = &account_info;
    static  SLONG   mouse_x, mouse_y;
    SLONG   event_type, event_id, len;
    BYTE    kb;
    int     iRet;

    switch(message)
    {
    case WM_MOUSEMOVE:
        mouse_x = GET_X_LPARAM(lParam);
        mouse_y = GET_Y_LPARAM(lParam);
        event_type = event_id = 0;
        game_range.mapping(mouse_x, mouse_y, &event_type, &event_id);
        data->hilight_id = event_id;
        break;
    case WM_LBUTTONDOWN:
        {
            mouse_x = GET_X_LPARAM(lParam);
            mouse_y = GET_Y_LPARAM(lParam);
            event_type = event_id = 0;
            game_range.mapping(mouse_x, mouse_y, &event_type, &event_id);
            switch(event_id)
            {
            case CREATEACCOUNT_ID_ACCOUNT:
                data->active_id = event_id;
                data->function_id = event_id;
                break;
            case CREATEACCOUNT_ID_PASSWORD:
                data->active_id = event_id;
                data->function_id = event_id;
                break;
            case CREATEACCOUNT_ID_VERIFY_PASSWORD:
                data->active_id = event_id;
                data->function_id = event_id;
                break;
            case CREATEACCOUNT_ID_NEXT_STEP:
                data->active_id = event_id;
                data->function_id = event_id;
                on_create_account_next_step();
                break;
            case CREATEACCOUNT_ID_LAST_STEP:
                data->active_id = event_id;
                data->function_id = event_id;
                iRet = ClientLogoutDoor();
                set_next_app_state(APPSTATE_INIT_LOGIN);
                change_app_state();
                break;
            }
        }
        break;
    case WM_LBUTTONUP:
        data->active_id = 0;
        break;
    case WM_CHAR:
        {
            switch(data->function_id)
            {
            case CREATEACCOUNT_ID_ACCOUNT:
                switch(wParam)
                {
                case VK_BACK:
                    len = strlen((const char *)accinfo->account);
                    if(len > 0) len--;
                    accinfo->account[len] = '\0';
                    break;
                default:
                    kb = 0;
                    if(wParam >= '0' && wParam <= '9')
                        kb = wParam;
                    else if(wParam >= 'A' && wParam <= 'Z')
                        kb = wParam - 'A' + 'a';
                    else if(wParam >= 'a' && wParam <= 'z')
                        kb = wParam;
                    if(kb)
                    {
                        len = strlen((const char *)accinfo->account);
                        if(len < 16)
                            accinfo->account[len++] = kb;
                        accinfo->account[len] = '\0';
                    }
                    break;
                }
                break;
            case CREATEACCOUNT_ID_PASSWORD:
                switch(wParam)
                {
                case VK_BACK:
                    len = strlen((const char *)accinfo->password);
                    if(len > 0) len--;
                    accinfo->password[len] = '\0';
                    break;
                default:
                    kb = 0;
                    if(wParam >= '0' && wParam <= '9')
                        kb = wParam;
                    else if(wParam >= 'A' && wParam <= 'Z')
                        kb = wParam - 'A' + 'a';
                    else if(wParam >= 'a' && wParam <= 'z')
                        kb = wParam;
                    if(kb)
                    {
                        len = strlen((const char *)accinfo->password);
                        if(len < 16)
                            accinfo->password[len++] = kb;
                        accinfo->password[len] = '\0';
                    }
                    break;
                }
                break;
            case CREATEACCOUNT_ID_VERIFY_PASSWORD:
                switch(wParam)
                {
                case VK_BACK:
                    len = strlen((const char *)accinfo->verify_password);
                    if(len > 0) len--;
                    accinfo->verify_password[len] = '\0';
                    break;
                default:
                    kb = 0;
                    if(wParam >= '0' && wParam <= '9')
                        kb = wParam;
                    else if(wParam >= 'A' && wParam <= 'Z')
                        kb = wParam - 'A' + 'a';
                    else if(wParam >= 'a' && wParam <= 'z')
                        kb = wParam;
                    if(kb)
                    {
                        len = strlen((const char *)accinfo->verify_password);
                        if(len < 16)
                            accinfo->verify_password[len++] = kb;
                        accinfo->verify_password[len] = '\0';
                    }
                    break;
                }
                break;
            }
        }
        break;
    case WM_KEYDOWN:
        {
            switch( wParam )
            {
            case VK_TAB:
                if(data->function_id == CREATEACCOUNT_ID_ACCOUNT)
                {
                    data->function_id = CREATEACCOUNT_ID_PASSWORD;
                }
                else if(data->function_id == CREATEACCOUNT_ID_PASSWORD)
                {
                    data->function_id = data->active_id = CREATEACCOUNT_ID_VERIFY_PASSWORD;
                }
                else if(data->function_id == CREATEACCOUNT_ID_VERIFY_PASSWORD)
                {
                    data->function_id = data->active_id = CREATEACCOUNT_ID_ACCOUNT;
                }
                break;
            }
        }
        break;
    default:
        break;
    }
    return  0;
}


//////////////////////////////////////////////////////////////////////////////////////////////
// SETUP RECORD(創建用戶資料)                                                               //
//////////////////////////////////////////////////////////////////////////////////////////////
int     init_setup_record(void)
{
    USTR    filename[_MAX_FNAME];
    SLONG   result, i, frames;
    CAKE_FRAME_ANI  *cfa;
    SETUPRECORD_DATA *data = &setuprecord_data;
    ACCOUNT_INFO *accinfo = &account_info;

    data->cfa = NULL;
    for(i=0; i<32; i++)
    {
        data->cf[i] = NULL;
    }

    set_data_file(packed_menu_file);
    strcpy((char *)filename, "menu\\newacc2.cak");
    result = load_cake_frame_ani_from_file((USTR*)filename, &data->cfa);
    if(TTN_OK != result)
        return  -1;
    frames = count_cake_frames(data->cfa);
    for(i=0; i<frames; i++)
    {
        cfa = get_specify_cake_frame_ani(data->cfa, i);
        data->cf[i] = cfa->cake_frame;
    }

    data->hilight_id = 0;
    data->active_id = 0;
    data->function_id = 0;
    data->locate_item_index = 0;
    data->city_item_index = 0;
    //
    result = init_account_details();
    if(0 != result)
        return  -2;

    //set year, month, day, locate, occupation, city combo boxes.
    LPCOMBOBOX  lpcbb;

    clear_combobox_list();

    lpcbb = data->year_cbb = get_year_cbb();
    set_combobox_pos(lpcbb, SETUPRECORD_YEAR_CBB_SX, SETUPRECORD_YEAR_CBB_SY);
    set_combobox_edit_wh(lpcbb, SETUPRECORD_YEAR_CBB_XL, SETUPRECORD_YEAR_CBB_YL);
    set_combobox_style(lpcbb, COMBOBOX_STYLE_DOWN);
    set_combobox_lines(lpcbb, 6);
    set_combobox_enable(lpcbb, COMBOBOX_ENABLE);
    set_combobox_default(lpcbb, 0);
    add_combobox_to_list(lpcbb);
    accinfo->year = get_combobox_data(lpcbb);

    lpcbb = data->month_cbb = get_month_cbb();
    set_combobox_pos(lpcbb, SETUPRECORD_MONTH_CBB_SX, SETUPRECORD_MONTH_CBB_SY);
    set_combobox_edit_wh(lpcbb, SETUPRECORD_MONTH_CBB_XL, SETUPRECORD_MONTH_CBB_YL);
    set_combobox_style(lpcbb, COMBOBOX_STYLE_DOWN);
    set_combobox_lines(lpcbb, 6);
    set_combobox_enable(lpcbb, COMBOBOX_ENABLE);
    set_combobox_default(lpcbb, 0);
    add_combobox_to_list(lpcbb);
    accinfo->month = get_combobox_data(lpcbb);

    lpcbb = data->day_cbb = get_day_cbb();
    set_combobox_pos(lpcbb, SETUPRECORD_DAY_CBB_SX, SETUPRECORD_DAY_CBB_SY);
    set_combobox_edit_wh(lpcbb, SETUPRECORD_DAY_CBB_XL, SETUPRECORD_DAY_CBB_YL);
    set_combobox_style(lpcbb, COMBOBOX_STYLE_DOWN);
    set_combobox_lines(lpcbb, 6);
    set_combobox_enable(lpcbb, COMBOBOX_ENABLE);
    set_combobox_default(lpcbb, 0);
    add_combobox_to_list(lpcbb);
    accinfo->day = get_combobox_data(lpcbb);

    lpcbb = data->occupation_cbb = get_occupation_cbb();
    set_combobox_pos(lpcbb, SETUPRECORD_OCCUPATION_CBB_SX, SETUPRECORD_OCCUPATION_CBB_SY);
    set_combobox_edit_wh(lpcbb, SETUPRECORD_OCCUPATION_CBB_XL, SETUPRECORD_OCCUPATION_CBB_YL);
    set_combobox_style(lpcbb, COMBOBOX_STYLE_DOWN);
    set_combobox_lines(lpcbb, 6);
    set_combobox_enable(lpcbb, COMBOBOX_ENABLE);
    set_combobox_default(lpcbb, 0);
    add_combobox_to_list(lpcbb);
    strcpy((char *)accinfo->occupation, (const char *)get_combobox_str(lpcbb));

    lpcbb = data->locate_cbb = get_locate_cbb();
    set_combobox_pos(lpcbb, SETUPRECORD_LOCATE_CBB_SX, SETUPRECORD_LOCATE_CBB_SY);
    set_combobox_edit_wh(lpcbb, SETUPRECORD_LOCATE_CBB_XL, SETUPRECORD_LOCATE_CBB_YL);
    set_combobox_style(lpcbb, COMBOBOX_STYLE_DOWN);
    set_combobox_lines(lpcbb, 6);
    set_combobox_enable(lpcbb, COMBOBOX_ENABLE);
    set_combobox_default(lpcbb, 0);
    add_combobox_to_list(lpcbb);
    strcpy((char *)accinfo->locate, (const char *)get_combobox_str(lpcbb));

    lpcbb = data->city_cbb = get_city_cbb(data->locate_item_index);
    set_combobox_pos(lpcbb, SETUPRECORD_CITY_CBB_SX, SETUPRECORD_CITY_CBB_SY);
    set_combobox_edit_wh(lpcbb, SETUPRECORD_CITY_CBB_XL, SETUPRECORD_CITY_CBB_YL);
    set_combobox_style(lpcbb, COMBOBOX_STYLE_DOWN);
    set_combobox_lines(lpcbb, 6);
    set_combobox_enable(lpcbb, COMBOBOX_ENABLE);
    set_combobox_default(lpcbb, 0);
    add_combobox_to_list(lpcbb);
    strcpy((char *)accinfo->city, (const char *)get_combobox_str(lpcbb));

    //
//    enable_ime();
    //
    return  0;
}


void    active_setup_record(int active)
{
}


void    free_setup_record(void)
{
    SETUPRECORD_DATA *data = &setuprecord_data;
    SLONG   i;

    if(data->cfa)
    {
        destroy_cake_frame_ani(&data->cfa);
        for(i=0; i<32; i++)
        {
            data->cf[i] = NULL;
        }
    }

//    disable_ime();
    clear_combobox_list();
    free_account_details();

    return;
}


void    refresh_setup_record(void)
{
}


void    redraw_setup_record(SLONG sx, SLONG sy, void *vbitmap)
{
    SETUPRECORD_DATA    *data = &setuprecord_data;
    ACCOUNT_INFO    *accinfo = &account_info;
    BMP *bitmap = (BMP*)vbitmap;
    CAKE_FRAME  *cf;
    SLONG   frame, x, y, xl, yl, id, event;
    SLONG   len;
    USTR    info[128];
    

    event = SETUPRECORD_EVENT;
    game_range.clear();

    //(1) background -------------------------------------------
    frame = SETUPRECORD_FRAME_BKGND;
    id = SETUPRECORD_ID_BKGND;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

    //(2) male button ------------------------------------------
    frame = SETUPRECORD_FRAME_MALE;
    id = SETUPRECORD_ID_MALE;
    if(accinfo->sex == MALE)
    {
        cf = data->cf[frame];
        x = sx + cf->frame_rx;
        y = sy + cf->frame_ry;
        put_rle(x, y, cf->rle, bitmap);
    }
    if(data->hilight_id == id)
    {
        frame += 1;
        cf = data->cf[frame];
        x = sx + cf->frame_rx;
        y = sy + cf->frame_ry;
        put_rle(x, y, cf->rle, bitmap);
    }
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

    //(2) female button ----------------------------------------
    frame = SETUPRECORD_FRAME_FEMALE;
    id = SETUPRECORD_ID_FEMALE;
    if(accinfo->sex == FEMALE)
    {
        cf = data->cf[frame];
        x = sx + cf->frame_rx;
        y = sy + cf->frame_ry;
        put_rle(x, y, cf->rle, bitmap);
    }
    if(data->hilight_id == id)
    {
        frame += 1;
        cf = data->cf[frame];
        x = sx + cf->frame_rx;
        y = sy + cf->frame_ry;
        put_rle(x, y, cf->rle, bitmap);
    }
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

    //(3) last step button -------------------------------------
    frame = SETUPRECORD_FRAME_LAST_STEP;
    id = SETUPRECORD_ID_LAST_STEP;
    if(data->active_id == id)
        frame += 2;
    else if(data->hilight_id == id)
        frame += 1;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

    //(4) next step button -------------------------------------
    frame = SETUPRECORD_FRAME_NEXT_STEP;
    id = SETUPRECORD_ID_NEXT_STEP;
    if(data->active_id == id)
        frame += 2;
    else if(data->hilight_id == id)
        frame += 1;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

    //(5) name input -------------------------------------------
    id = SETUPRECORD_ID_NAME_INPUT;
    x = sx + SETUPRECORD_NAME_BAR_SX;
    y = sy + SETUPRECORD_NAME_BAR_SY;
    xl = SETUPRECORD_NAME_BAR_XL;
    yl = SETUPRECORD_NAME_BAR_YL;
    game_range.add(x, y, xl, yl, event, id);

    len = strlen((const char *)accinfo->name);
    if(data->function_id == id)
        sprintf((char *)info, "~C3%s_~C0", accinfo->name);
    else
        sprintf((char *)info, "~C3%s~C0", accinfo->name);
    set_word_color(3, rgb2hi(20, 20, 255));
    print16(x + 8, y + 8, (USTR*)info, PEST_PUT, bitmap);
    set_word_color(3, rgb2hi(0, 0, 255));

    //(5) address input -------------------------------------------
    id = SETUPRECORD_ID_ADDRESS_INPUT;
    x = sx + SETUPRECORD_ADDRESS_BAR_SX;
    y = sy + SETUPRECORD_ADDRESS_BAR_SY;
    xl = SETUPRECORD_ADDRESS_BAR_XL;
    yl = SETUPRECORD_ADDRESS_BAR_YL;
    game_range.add(x, y, xl, yl, event, id);

    len = strlen((const char *)accinfo->address);
    if(data->function_id == id)
        sprintf((char *)info, "~C3%s_~C0", accinfo->address);
    else
        sprintf((char *)info, "~C3%s~C0", accinfo->address);
    set_word_color(3, rgb2hi(20, 20, 255));
    print16(x + 8, y + 4, (USTR*)info, PEST_PUT, bitmap);
    set_word_color(3, rgb2hi(0, 0, 255));

    //(5) telephone input -------------------------------------------
    id = SETUPRECORD_ID_TELEPHONE_INPUT;
    x = sx + SETUPRECORD_TELEPHONE_BAR_SX;
    y = sy + SETUPRECORD_TELEPHONE_BAR_SY;
    xl = SETUPRECORD_TELEPHONE_BAR_XL;
    yl = SETUPRECORD_TELEPHONE_BAR_YL;
    game_range.add(x, y, xl, yl, event, id);

    len = strlen((const char *)accinfo->telephone);
    if(data->function_id == id)
        sprintf((char *)info, "~C3%s_~C0", accinfo->telephone);
    else
        sprintf((char *)info, "~C3%s~C0", accinfo->telephone);
    set_word_color(3, rgb2hi(20, 20, 255));
    print16(x + 8, y + 4, (USTR*)info, PEST_PUT, bitmap);
    set_word_color(3, rgb2hi(0, 0, 255));

    //(5) email input -------------------------------------------
    id = SETUPRECORD_ID_EMAIL_INPUT;
    x = sx + SETUPRECORD_EMAIL_BAR_SX;
    y = sy + SETUPRECORD_EMAIL_BAR_SY;
    xl = SETUPRECORD_EMAIL_BAR_XL;
    yl = SETUPRECORD_EMAIL_BAR_YL;
    game_range.add(x, y, xl, yl, event, id);

    len = strlen((const char *)accinfo->email);
    if(data->function_id == id)
        sprintf((char *)info, "~C3%s_~C0", accinfo->email);
    else
        sprintf((char *)info, "~C3%s~C0", accinfo->email);
    set_word_color(3, rgb2hi(20, 20, 255));
    print16(x + 8, y + 4, (USTR*)info, PEST_PUT, bitmap);
    set_word_color(3, rgb2hi(0, 0, 255));

    //year, month, day, locate, occupation, city combo boxes.
    redraw_combobox(bitmap);

    //ime input --------------------------------------------
//    pos_redraw_ime(bitmap);
}



SLONG   check_setup_record_combobox(void)
{
    SETUPRECORD_DATA    *data = &setuprecord_data;
    ACCOUNT_INFO *accinfo = &account_info;
    SLONG   locate_index, cbb_index;
    COMBOBOX*   lpcbb;

    //check locate and set city cbb. ---------------------------------
    locate_index = get_combobox_default(data->locate_cbb);
    if(locate_index != data->locate_item_index)
    {
        strcpy((char *)accinfo->locate, (const char *)get_combobox_str(data->locate_cbb));
        data->locate_item_index = locate_index;

        //
        cbb_index = find_combobox_index(data->city_cbb);
        del_combobox_from_list(cbb_index);

        //
        data->city_item_index = 0;
        lpcbb = data->city_cbb = get_city_cbb(data->locate_item_index);
        set_combobox_pos(lpcbb, SETUPRECORD_CITY_CBB_SX, SETUPRECORD_CITY_CBB_SY);
        set_combobox_edit_wh(lpcbb, SETUPRECORD_CITY_CBB_XL, SETUPRECORD_CITY_CBB_YL);
        set_combobox_style(lpcbb, COMBOBOX_STYLE_DOWN);
        set_combobox_lines(lpcbb, 6);
        set_combobox_enable(lpcbb, COMBOBOX_ENABLE);
        set_combobox_default(lpcbb, data->city_item_index);
        add_combobox_to_list(lpcbb);
        strcpy((char *)accinfo->city, (const char *)get_combobox_str(lpcbb));
    }


    return  0;
}


SLONG   handle_setup_record(UINT message, WPARAM wParam, LPARAM lParam)
{
    ACCOUNT_INFO    *accinfo = &account_info;
    SETUPRECORD_DATA *data = &setuprecord_data;
    static  SLONG   mouse_x, mouse_y;
    SLONG   event_type, event_id;
    BYTE    kb;
    SLONG   len;

    switch(message)
    {
    case WM_MOUSEMOVE:
        mouse_x = GET_X_LPARAM(lParam);
        mouse_y = GET_Y_LPARAM(lParam);
        event_type = event_id = 0;
        game_range.mapping(mouse_x, mouse_y, &event_type, &event_id);
        data->hilight_id = event_id;
        break;
    case WM_LBUTTONDOWN:
        {
            mouse_x = GET_X_LPARAM(lParam);
            mouse_y = GET_Y_LPARAM(lParam);
            event_type = event_id = 0;
            game_range.mapping(mouse_x, mouse_y, &event_type, &event_id);
            switch(event_id)
            {
            case SETUPRECORD_ID_LAST_STEP:
                data->active_id = event_id;
                data->function_id = event_id;
                set_next_app_state(APPSTATE_INIT_CREATE_ACCOUNT);
                change_app_state();
                break;
            case SETUPRECORD_ID_NEXT_STEP:
                data->active_id = event_id;
                data->function_id = event_id;
                set_next_app_state(APPSTATE_INIT_SELECT_PAYMENT);
                change_app_state();
                break;
            case SETUPRECORD_ID_MALE:
                data->function_id = event_id;
                data->active_id = event_id;
                accinfo->sex = MALE;
                break;
            case SETUPRECORD_ID_FEMALE:
                data->function_id = event_id;
                data->active_id = event_id;
                accinfo->sex = FEMALE;
                break;
            case SETUPRECORD_ID_NAME_INPUT:
                data->function_id = event_id;
                data->active_id = event_id;
                break;
            case SETUPRECORD_ID_ADDRESS_INPUT:
                data->function_id = event_id;
                data->active_id = event_id;
                break;
            case SETUPRECORD_ID_TELEPHONE_INPUT:
                data->function_id = event_id;
                data->active_id = event_id;
                break;
            case SETUPRECORD_ID_EMAIL_INPUT:
                data->function_id = event_id;
                data->active_id = event_id;
                break;
            default:
                break;
            }
        }
        break;
    case WM_LBUTTONUP:
        data->active_id = 0;
        check_setup_record_combobox();
        break;
    case WM_IME_STRING:
        {
            switch(data->function_id)
            {
            case SETUPRECORD_ID_NAME_INPUT:
                strcat((char *)accinfo->name, (const char *)wParam);
                break;
            case SETUPRECORD_ID_ADDRESS_INPUT:
                strcat((char *)accinfo->address, (const char *)wParam);
                break;
            case SETUPRECORD_ID_TELEPHONE_INPUT:
                strcat((char *)accinfo->telephone, (const char *)wParam);
                break;
            case SETUPRECORD_ID_EMAIL_INPUT:
                strcat((char *)accinfo->email, (const char *)wParam);
                break;
            }
        }
        break;
    case WM_CHAR:
        {
            switch(data->function_id)
            {
            case SETUPRECORD_ID_NAME_INPUT:
                switch(wParam)
                {
                case VK_BACK:
                    delete_last_word((char *)accinfo->name);
                    break;
                default:
                    kb = wParam;
                    if(isprint(kb))
                    {
                        len = strlen((const char *)accinfo->name);
                        if(len < 16)
                            accinfo->name[len++] = kb;
                        accinfo->name[len] = '\0';
                    }
                    break;
                }
                break;
            case SETUPRECORD_ID_ADDRESS_INPUT:
                switch(wParam)
                {
                case VK_BACK:
                    delete_last_word((char *)accinfo->address);
                    break;
                default:
                    kb = wParam;
                    if(isprint(kb))
                    {
                        len = strlen((const char *)accinfo->address);
                        if(len < 60)
                            accinfo->address[len++] = kb;
                        accinfo->address[len] = '\0';
                    }
                    break;
                }
                break;
            case SETUPRECORD_ID_TELEPHONE_INPUT:
                switch(wParam)
                {
                case VK_BACK:
                    delete_last_word((char *)accinfo->telephone);
                    break;
                default:
                    kb = wParam;
                    if(isprint(kb))
                    {
                        len = strlen((const char *)accinfo->telephone);
                        if(len < 60)
                            accinfo->telephone[len++] = kb;
                        accinfo->telephone[len] = '\0';
                    }
                    break;
                }
                break;
            case SETUPRECORD_ID_EMAIL_INPUT:
                switch(wParam)
                {
                case VK_BACK:
                    delete_last_word((char *)accinfo->email);
                    break;
                default:
                    kb = wParam;
                    if(isprint(kb))
                    {
                        len = strlen((const char *)accinfo->email);
                        if(len < 60)
                            accinfo->email[len++] = kb;
                        accinfo->email[len] = '\0';
                    }
                    break;
                }
                break;
            }
        }
        break;
    }
    return  0;
}


//////////////////////////////////////////////////////////////////////////////////////////////
// SELECT PAYMENT(選擇付款方式)                                                             //
//////////////////////////////////////////////////////////////////////////////////////////////
int     init_select_payment(void)
{
    USTR    filename[_MAX_FNAME];
    SLONG   result, i, frames;
    CAKE_FRAME_ANI  *cfa;
    SELECTPAYMENT_DATA *data = &selectpayment_data;

    data->cfa = NULL;
    for(i=0; i<32; i++)
    {
        data->cf[i] = NULL;
    }

    set_data_file(packed_menu_file);
    strcpy((char *)filename, "menu\\payment.cak");
    result = load_cake_frame_ani_from_file((USTR*)filename, &data->cfa);
    if(TTN_OK != result)
        return  -1;
    frames = count_cake_frames(data->cfa);
    for(i=0; i<frames; i++)
    {
        cfa = get_specify_cake_frame_ani(data->cfa, i);
        data->cf[i] = cfa->cake_frame;
    }

    data->hilight_id = 0;
    data->active_id = 0;
    data->function_id = 0;
    //

    //init some datas ----------------------------------
    COMBOBOX    *lpcbb;

    data->payment_type = PAYMENT_TYPE_CREDIT_CARD;

    lpcbb = data->card_cbb = create_combobox();
    add_combobox_item(lpcbb, (USTR*)TEXTMSG_CREDIT_CARD, 0);
    add_combobox_item(lpcbb, (USTR*)TEXTMSG_POINTS_CARD, 1);
    set_combobox_pos(lpcbb, SELECTPAYMENT_TYPE_CBB_SX, SELECTPAYMENT_TYPE_CBB_SY);
    set_combobox_edit_wh(lpcbb, SELECTPAYMENT_TYPE_CBB_XL, SELECTPAYMENT_TYPE_CBB_YL);
    set_combobox_style(lpcbb, COMBOBOX_STYLE_DOWN);
    set_combobox_lines(lpcbb, 3);
    set_combobox_enable(lpcbb, COMBOBOX_ENABLE);
    set_combobox_default(lpcbb, data->payment_type);

    lpcbb = data->year_cbb = create_year_cbb(2002, 2050);
    set_combobox_pos(lpcbb, SELECTPAYMENT_CCARD_YEAR_CBB_SX, SELECTPAYMENT_CCARD_YEAR_CBB_SY);
    set_combobox_edit_wh(lpcbb, SELECTPAYMENT_CCARD_YEAR_CBB_XL, SELECTPAYMENT_CCARD_YEAR_CBB_YL);
    set_combobox_style(lpcbb, COMBOBOX_STYLE_DOWN);
    set_combobox_lines(lpcbb, 6);
    set_combobox_enable(lpcbb, COMBOBOX_ENABLE);
    set_combobox_default(lpcbb, 0);

    lpcbb = data->month_cbb = create_month_cbb(1, 12);
    set_combobox_pos(lpcbb, SELECTPAYMENT_CCARD_MONTH_CBB_SX, SELECTPAYMENT_CCARD_MONTH_CBB_SY);
    set_combobox_edit_wh(lpcbb, SELECTPAYMENT_CCARD_MONTH_CBB_XL, SELECTPAYMENT_CCARD_MONTH_CBB_YL);
    set_combobox_style(lpcbb, COMBOBOX_STYLE_DOWN);
    set_combobox_lines(lpcbb, 6);
    set_combobox_enable(lpcbb, COMBOBOX_ENABLE);
    set_combobox_default(lpcbb, 0);

    clear_combobox_list();
    add_combobox_to_list(data->card_cbb);
    switch(data->payment_type)
    {
    case PAYMENT_TYPE_CREDIT_CARD:
        add_combobox_to_list(data->year_cbb);
        add_combobox_to_list(data->month_cbb);
        break;
    case PAYMENT_TYPE_POINTS_CARD:
        break;
    }

    return  0;
}


void    active_select_payment(int active)
{
}


void    free_select_payment(void)
{
    SELECTPAYMENT_DATA *data = &selectpayment_data;
    SLONG   i;

    if(data->cfa)
    {
        destroy_cake_frame_ani(&data->cfa);
        for(i=0; i<32; i++)
        {
            data->cf[i] = NULL;
        }
    }

    clear_combobox_list();
    if(data->card_cbb)
    {
        destroy_combobox(data->card_cbb);
        data->card_cbb = NULL;
    }
    if(data->year_cbb)
    {
        destroy_combobox(data->year_cbb);
        data->year_cbb = NULL;
    }
    if(data->month_cbb)
    {
        destroy_combobox(data->month_cbb);
        data->month_cbb = NULL;
    }

    return;
}


void    refresh_select_payment(void)
{
}


void    redraw_select_payment(SLONG sx, SLONG sy, void *vbitmap)
{
    SELECTPAYMENT_DATA    *data = &selectpayment_data;
    ACCOUNT_INFO    *accinfo = &account_info;
    BMP *bitmap = (BMP*)vbitmap;
    CAKE_FRAME  *cf;
    SLONG   frame, x, y, id, event;

    event = SELECTPAYMENT_EVENT;
    game_range.clear();

    //(1) background -------------------------------------------
    frame = SELECTPAYMENT_FRAME_BKGND;
    id = SELECTPAYMENT_ID_BKGND;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);


    //(2) ok button --------------------------------------------
    frame = SELECTPAYMENT_FRAME_OK;
    id = SELECTPAYMENT_ID_OK;
    if(data->active_id == id)
        frame += 2;
    else if(data->hilight_id == id)
        frame += 1;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

    //(3) cancel button ----------------------------------------
    frame = SELECTPAYMENT_FRAME_CANCEL;
    id = SELECTPAYMENT_ID_CANCEL;
    if(data->active_id == id)
        frame += 2;
    else if(data->hilight_id == id)
        frame += 1;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

    //(4) rest points -------------------------------------------
    // TODO: [7/26/2002]

    //(5) add points --------------------------------------------
    // TODO: [7/26/2002]

    //(6) card info ---------------------------------------------
    switch(data->payment_type)
    {
    case PAYMENT_TYPE_CREDIT_CARD:
        {
            //card bkgnd.----------
            frame = SELECTPAYMENT_FRAME_CREDIT_CARD;
            cf = data->cf[frame];
            x = sx + cf->frame_rx;
            y = sy + cf->frame_ry;
            put_rle(x, y, cf->rle, bitmap);

            // TODO: [7/26/2002]
        }
        break;
    case PAYMENT_TYPE_POINTS_CARD:
        {
            //card bkgnd.----------
            frame = SELECTPAYMENT_FRAME_POINTS_CARD;
            cf = data->cf[frame];
            x = sx + cf->frame_rx;
            y = sy + cf->frame_ry;
            put_rle(x, y, cf->rle, bitmap);

            //TODO:
        }
        break;
    }

    //(7) combobox -----------------------------------------------
    redraw_combobox(bitmap);
}


SLONG   on_create_account_final_step(void)
{
	TPOS_EVENT_REGISTERACCOUNT	request;
    ACCOUNT_INFO    *data = &account_info;
    char    temp[256];
    int     iRet;

    strcpy((char *)request.cId, (const char *)data->account);	//32-1 bytes
    strcpy((char *)request.cPw, (const char *)data->password);	//32-1 bytes
    strcpy((char *)request.cName, (const char *)data->name);	//32-1 bytes
    request.dwSex = data->sex;
    sprintf((char *)temp, "%04d%02d%02d", data->year, data->month, data->day);
    memcpy(&request.cBirthday, temp, 8);	//8 bytes
    strcpy((char *)request.cCountry, (const char *)data->locate);	//16-1 bytes
    strcpy((char *)request.cCity, (const char *)data->city);		//16-1 bytes
    strcpy((char *)request.cAddress, (const char *)data->address);	//52-1 bytes
    strcpy((char *)request.cPhone, (const char *)data->telephone);	//16-1 bytes
    request.dwJob = data->occupation_no;
    request.dwNetStyle = 0;
    strcpy((char *)request.cEmail, (const char *)data->email);	//40-1 bytes
    request.dwPayType = data->payment;

    iRet = ClientRequestRegisterAccountFinal(&request);
    set_next_app_state(APPSTATE_INIT_LOGIN);

    return  0;
}


SLONG   check_select_payment_combobox(void)
{
    SELECTPAYMENT_DATA    *data = &selectpayment_data;
    SLONG   payment_type;

    payment_type = get_combobox_default(data->card_cbb);
    if(payment_type != data->payment_type)
    {
        data->payment_type = payment_type;
        clear_combobox_list();
        add_combobox_to_list(data->card_cbb);
        switch(data->payment_type)
        {
        case PAYMENT_TYPE_CREDIT_CARD:
            add_combobox_to_list(data->year_cbb);
            add_combobox_to_list(data->month_cbb);
            break;
        case PAYMENT_TYPE_POINTS_CARD:
            break;
        }
    }

    return  0;
}


SLONG   handle_select_payment(UINT message, WPARAM wParam, LPARAM lParam)
{
    ACCOUNT_INFO    *accinfo = &account_info;
    SELECTPAYMENT_DATA *data = &selectpayment_data;
    static  SLONG   mouse_x, mouse_y;
    SLONG   event_type, event_id;

    switch(message)
    {
    case WM_MOUSEMOVE:
        mouse_x = GET_X_LPARAM(lParam);
        mouse_y = GET_Y_LPARAM(lParam);
        event_type = event_id = 0;
        game_range.mapping(mouse_x, mouse_y, &event_type, &event_id);
        data->hilight_id = event_id;
        break;
    case WM_LBUTTONDOWN:
        {
            mouse_x = GET_X_LPARAM(lParam);
            mouse_y = GET_Y_LPARAM(lParam);
            event_type = event_id = 0;
            game_range.mapping(mouse_x, mouse_y, &event_type, &event_id);
            switch(event_id)
            {
            case SELECTPAYMENT_ID_OK:
                data->active_id = event_id;
                data->function_id = event_id;
                on_create_account_final_step();
                break;
            case SELECTPAYMENT_ID_CANCEL:
                data->active_id = event_id;
                data->function_id = event_id;
                set_next_app_state(APPSTATE_INIT_SETUP_RECORD);
                change_app_state();
                break;
            }
        }
        break;
    case WM_LBUTTONUP:
        data->active_id = 0;
        check_select_payment_combobox();
        break;
    }
    return  0;
}


//////////////////////////////////////////////////////////////////////////////////////////////
// MODIFY RECORD(修改資料)                                                                  //
//////////////////////////////////////////////////////////////////////////////////////////////
int     init_modify_record(void)
{
    return  0;
}


void    active_modify_record(int active)
{
}


void    free_modify_record(void)
{
}


void    refresh_modify_record(void)
{
}


void    redraw_modify_record(SLONG sx, SLONG sy, void *vbitmap)
{
}


SLONG   handle_modify_record(UINT message, WPARAM wParam, LPARAM lParam)
{
    return  0;
}


//////////////////////////////////////////////////////////////////////////////////////////////
// CHANGE PASSWORD(修改密碼)                                                                //
//////////////////////////////////////////////////////////////////////////////////////////////
int     init_change_password(void)
{
    USTR    filename[_MAX_FNAME];
    SLONG   result, i, frames;
    CAKE_FRAME_ANI  *cfa;
    CHANGEPASSWORD_DATA *data = &changepassword_data;;

    data->cfa = NULL;
    for(i=0; i<32; i++)
    {
        data->cf[i] = NULL;
    }

    set_data_file(packed_menu_file);
    strcpy((char *)filename, "menu\\chgpswd.cak");
    result = load_cake_frame_ani_from_file((USTR*)filename, &data->cfa);
    if(TTN_OK != result)
        return  -1;

    frames = count_cake_frames(data->cfa);
    for(i=0; i<frames; i++)
    {
        cfa = get_specify_cake_frame_ani(data->cfa, i);
        data->cf[i] = cfa->cake_frame;
    }

    data->hilight_id = 0;
    data->active_id = 0;
    memset(data->new_password, '\0', 32);
    memset(data->verify_password, '\0', 32);
    //
    return  0;
}


void    active_change_password(int active)
{
}


void    free_change_password(void)
{
    CHANGEPASSWORD_DATA *data = &changepassword_data;
    SLONG   i;

    if(data->cfa)
    {
        destroy_cake_frame_ani(&data->cfa);
        for(i=0; i<32; i++)
        {
            data->cf[i] = NULL;
        }
    }
}


void    refresh_change_password(void)
{
}


void    redraw_change_password(SLONG sx, SLONG sy, void *vbitmap)
{
    BMP *bitmap = (BMP*)vbitmap;
    CAKE_FRAME  *cf;
    SLONG   frame, x, y, xl, yl, id, event, len;
    CHANGEPASSWORD_DATA *data = &changepassword_data;
    USTR    info[64], mask[64];

    event = ACCMANAGER_EVENT;
    game_range.clear();

    //(1) background upper --------------------------------------
    frame = CHANGEPASSWORD_FRAME_BKGND;
    id = CHANGEPASSWORD_ID_BKGND;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

    //(2) new password ------------------------------------------
    id = CHANGEPASSWORD_ID_NEW_PASSWORD;
    x = sx + CHANGEPASSWORD_NEW_PASSWORD_BAR_SX;
    y = sy + CHANGEPASSWORD_NEW_PASSWORD_BAR_SY;
    xl = CHANGEPASSWORD_NEW_PASSWORD_BAR_XL;
    yl = CHANGEPASSWORD_NEW_PASSWORD_BAR_YL;
    game_range.add(x, y, xl, yl, event, id);
    len = strlen((const char *)data->new_password);
    memset(mask, '\0', 64);
    memset(mask, '*', len);
    if(data->function_id == id)
        sprintf((char *)info, "~C3%s_~C0", mask);
    else
        sprintf((char *)info, "~C3%s~C0", mask);
    set_word_color(3, rgb2hi(237, 98, 55));
    print24(x + 16, y + 4, (USTR*)info, PEST_PUT, bitmap);
    set_word_color(3, rgb2hi(0, 0, 255));

    //(3) verify new password -----------------------------------
    id = CHANGEPASSWORD_ID_VERIFY_PASSWORD;
    x = sx + CHANGEPASSWORD_VERIFY_PASSWORD_BAR_SX;
    y = sy + CHANGEPASSWORD_VERIFY_PASSWORD_BAR_SY;
    xl = CHANGEPASSWORD_VERIFY_PASSWORD_BAR_XL;
    yl = CHANGEPASSWORD_VERIFY_PASSWORD_BAR_YL;
    game_range.add(x, y, xl, yl, event, id);
    len = strlen((const char *)data->verify_password);
    memset(mask, '\0', 64);
    memset(mask, '*', len);
    if(data->function_id == id)
        sprintf((char *)info, "~C3%s_~C0", mask);
    else
        sprintf((char *)info, "~C3%s~C0", mask);
    set_word_color(3, rgb2hi(237, 98, 55));
    print24(x + 16, y + 4, (USTR*)info, PEST_PUT, bitmap);
    set_word_color(3, rgb2hi(0, 0, 255));

    //(4) ok button ---------------------------------------------
    frame = CHANGEPASSWORD_FRAME_OK;
    id = CHANGEPASSWORD_ID_OK;
    if(data->active_id == id)
        frame += 2;
    else if(data->hilight_id == id)
        frame += 1;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);

    //(5) back button -------------------------------------------
    frame = CHANGEPASSWORD_FRAME_BACK;
    id = CHANGEPASSWORD_ID_BACK;
    if(data->active_id == id)
        frame += 2;
    else if(data->hilight_id == id)
        frame += 1;
    cf = data->cf[frame];
    x = sx + cf->frame_rx;
    y = sy + cf->frame_ry;
    put_rle(x, y, cf->rle, bitmap);
    game_range.add(x, y, cf->rle->w, cf->rle->h, event, id);
}


SLONG   on_change_password(void)
{
    //TPOS_REGISTERINFO   reginfo;
    CHANGEPASSWORD_DATA *data = &changepassword_data;
    int iRet;

    if(0 == strcmpi((const char *)data->new_password, ""))
    {
        display_error_message((USTR*)ERRMSG_MUST_INPUT_NEW_PASSWORD, DISPLAY_MESSAGE_TO_SCREEN, screen_buffer);
        wait_key_time(' ', 80);
        return  -1;
    }
    if(0 == strcmpi((const char *)data->verify_password, ""))
    {
        display_error_message((USTR*)ERRMSG_MUST_INPUT_VERIFY_PASSWORD, DISPLAY_MESSAGE_TO_SCREEN, screen_buffer);
        wait_key_time(' ', 80);
        return  -2;
    }
    if(0 != strcmpi((const char *)data->new_password, (const char *)data->verify_password))
    {
        display_error_message((USTR*)ERRMSG_MUST_CONFIRM_PASSWORD, DISPLAY_MESSAGE_TO_SCREEN, screen_buffer);
        wait_key_time(' ', 80);
        return  -3;
    }

    //strcpy((char *)reginfo.cId, (const char *)uilogin.account);
    //strcpy((char *)reginfo.cPw, (const char *)data->new_password);
    //iRet = PosChangeAccountPassword(reginfo);
	iRet = ClientRequestChangeAccountPassword((char *)uilogin.account, (char *)data->new_password);
    switch(iRet)
    {
    case SEND_MSG_OK:
        display_error_message((USTR*)ERRMSG_CHANGE_PASSWORD_OK, DISPLAY_MESSAGE_TO_SCREEN, screen_buffer);
        wait_key_time(' ', 80);
        return  0;
    }
    return  0;
}


SLONG   handle_change_password(UINT message, WPARAM wParam, LPARAM lParam)
{
    CHANGEPASSWORD_DATA *data = &changepassword_data;
    static  SLONG   mouse_x, mouse_y;
    SLONG   event_type, event_id, len;
    BYTE    kb;

    switch(message)
    {
    case WM_MOUSEMOVE:
        mouse_x = GET_X_LPARAM(lParam);
        mouse_y = GET_Y_LPARAM(lParam);
        event_type = event_id = 0;
        game_range.mapping(mouse_x, mouse_y, &event_type, &event_id);
        data->hilight_id = event_id;
        break;
    case WM_LBUTTONDOWN:
        {
            mouse_x = GET_X_LPARAM(lParam);
            mouse_y = GET_Y_LPARAM(lParam);
            event_type = event_id = 0;
            game_range.mapping(mouse_x, mouse_y, &event_type, &event_id);
            switch(event_id)
            {
            case CHANGEPASSWORD_ID_NEW_PASSWORD:
                data->active_id = event_id;
                data->function_id = event_id;
                break;
            case CHANGEPASSWORD_ID_VERIFY_PASSWORD:
                data->active_id = event_id;
                data->function_id = event_id;
                break;
            case CHANGEPASSWORD_ID_OK:
                data->active_id = event_id;
                data->function_id = event_id;
                if(0 == on_change_password() )
                {
                    set_next_app_state(APPSTATE_INIT_ACCOUNT_MANAGER);
                    change_app_state();
                }
                break;
            case CHANGEPASSWORD_ID_BACK:
                data->active_id = event_id;
                data->function_id = event_id;
                set_next_app_state(APPSTATE_INIT_ACCOUNT_MANAGER);
                change_app_state();
                break;
            }
        }
        break;
    case WM_LBUTTONUP:
        data->active_id = 0;
        break;
    case WM_CHAR:
        {
            switch(data->function_id)
            {
            case CHANGEPASSWORD_ID_NEW_PASSWORD:
                switch(wParam)
                {
                case VK_BACK:
                    len = strlen((const char *)data->new_password);
                    if(len > 0) len--;
                    data->new_password[len] = '\0';
                    break;
                default:
                    kb = 0;
                    if(wParam >= '0' && wParam <= '9')
                        kb = wParam;
                    else if(wParam >= 'A' && wParam <= 'Z')
                        kb = wParam - 'A' + 'a';
                    else if(wParam >= 'a' && wParam <= 'z')
                        kb = wParam;
                    if(kb)
                    {
                        len = strlen((const char *)data->new_password);
                        if(len < 16)
                            data->new_password[len++] = kb;
                        data->new_password[len] = '\0';
                    }
                    break;
                }
                break;
            case CHANGEPASSWORD_ID_VERIFY_PASSWORD:
                switch(wParam)
                {
                case VK_BACK:
                    len = strlen((const char *)data->verify_password);
                    if(len > 0) len--;
                    data->verify_password[len] = '\0';
                    break;
                default:
                    kb = 0;
                    if(wParam >= '0' && wParam <= '9')
                        kb = wParam;
                    else if(wParam >= 'A' && wParam <= 'Z')
                        kb = wParam - 'A' + 'a';
                    else if(wParam >= 'a' && wParam <= 'z')
                        kb = wParam;
                    if(kb)
                    {
                        len = strlen((const char *)data->verify_password);
                        if(len < 16)
                            data->verify_password[len++] = kb;
                        data->verify_password[len] = '\0';
                    }
                    break;
                }
                break;
            }
        }
        break;
    case WM_KEYDOWN:
        {
            switch( wParam )
            {
            case VK_TAB:
                if(data->function_id == CHANGEPASSWORD_ID_NEW_PASSWORD)
                {
                    data->function_id = data->active_id = CHANGEPASSWORD_ID_VERIFY_PASSWORD;
                }
                else
                {
                    data->function_id = data->active_id = CHANGEPASSWORD_ID_NEW_PASSWORD;
                }
                break;
            }
        }
        break;
    default:
        break;
    }
    return  0;
}

//////////////////////////////////////////////////////////////////////////////////////////////
// SUPPLY POINTS(充值點數)                                                                  //
//////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
