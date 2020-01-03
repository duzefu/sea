/*
**  UIMapChat.cpp
**  ui of map chat.
**
**  Jack, 2002.10.28.
**  Modified by Zhang Zhaohui, 2003.5.15
**      �ϥ� UI_TEXT �ӹ�{�D�ɭ���Ѯ�������J
**
*/
#include "MainFun.h"
#include "NetGE_MainFunc.h"
#include "ClientMain.h"
#include "UIMap.h"
#include "CChat.h"
#include "CmdEvent.h"
#include "UIMapChat.h"

#include "qqedit.h"

SLONG   is_map_chat_input_active(void)
{
    return ( te_get_focus( ) ==  uimap_data.pchat);
}

void    activate_map_chat_input(SLONG active)
{
    //    te_set_read_only( uimap_data.pchat, (BOOL)!active );
    
    if ( active )
        te_set_focus( uimap_data.pchat );
    else
    {
        if ( is_map_chat_input_active( ) )
            te_force_set_focus( NULL );
    }
}

void    clear_map_chat_input(void)
{
    te_set_text( uimap_data.pchat, NULL );
}

SLONG   filter_map_chat_input(UINT message, WPARAM wParam, LPARAM lParam)
{
    USTR    buffer[256];
    
    switch ( message )
    {
    case WM_KEYDOWN:
        switch ( wParam )
        {
        case VK_RETURN:
            if ( is_map_chat_input_active( ) )
            {
                if ( te_get_size( uimap_data.pchat ) )
                {
                    client_cmd_public_talk( (char *)GetCharacterMainName(g_lPlayerIndex), uimap_data.pchat->ptext_buf );
                    game_chat.add_input( CHATEFF_WHITE, (USTR*)uimap_data.pchat->ptext_buf );
                    clear_map_chat_input( );
                    activate_map_chat_input( false );
                }
                else
                {
                    activate_map_chat_input( false );
                }
                return TRUE;
            }
            else
            {
                // �E����J��
                activate_map_chat_input( true );
                if ( is_map_chat_input_active( ) )
                    return TRUE;
            }
            break;
        case VK_UP:
            if ( is_map_chat_input_active() &&
                TTN_OK == game_chat.get_prev_input( NULL, buffer, false ) )
                
            {
                te_set_text( uimap_data.pchat, (CHAR*)buffer );
                return TRUE;
            }
            break;
        case VK_DOWN:
            if ( is_map_chat_input_active() &&
                TTN_OK == game_chat.get_next_input( NULL, buffer, false ) )
            {
                te_set_text( uimap_data.pchat, (CHAR*)buffer );
                return TRUE;
            }
            break;
        }
        break;
    }
    
    
    return FALSE;
}


/* Zhang Zhaohui 2003.5.13
SLONG   is_map_chat_input_active(void)
{
    return (uimap_data.function_id == UIMAP_ID_CHAT_INPUT) ? true : false;
}


void    activate_map_chat_input(SLONG active)
{
    char    *curr_name = NULL, *stored_name = NULL;
    SLONG   try_counts = 20;
    
    uimap_data.function_id = active ? UIMAP_ID_CHAT_INPUT : 0;
    
    if(active) //�}�l��J, �p�G�W�����ϥ�IME, �h���ɦ۰ʥ��}
    {
        enable_ime();
        if(is_maingame_enable_chat_ime())
        {
            stored_name = (char *)get_maingame_chat_ime_name();
            while(try_counts-- >= 0)
            {
                curr_name = get_ime_name();
                if(curr_name)
                {
                    if(0 == strcmpi((const char *)curr_name, (const char *)stored_name))
                        break;
                }
                next_ime();
            }
        }
    }
    else //������J, �P�ɫO�s�����O�_���}IME.
    {
        curr_name = get_ime_name();
        if(curr_name)
        {
            set_maingame_enable_chat_ime(true);
            set_maingame_chat_ime_name((char *)curr_name);
        }
        else
        {
            set_maingame_enable_chat_ime(false);
        }
        disable_ime();
    }
}


void    clear_map_chat_input(void)
{
    UIMAP_DATA  *data = &uimap_data;
    memset(data->chat_input, 0, CHAT_INPUT_LEN);
    data->chat_input_index = 0;
    data->chat_input_max = 0;
    data->chat_show_index = 0;
    data->chat_show_len = 0;
}


SLONG   filter_map_chat_input(UINT message, WPARAM wParam, LPARAM lParam)
{
    enum { MAX_SHOW_BYTES = 38, AUTO_ADJUST_BYTES = 8};
    USTR    buffer[256], clip_buffer[80];
    SLONG   len, exist_len, append_len, copy_len, insert_len;
    SLONG   delete_len;
    BYTE    kb;
    UIMAP_DATA  *data = &uimap_data;
    
    if(!is_map_chat_input_active())
        return  false;
    
    switch(message)
    {
    case WM_IME_STRING:
        exist_len = strlen((const char *)data->chat_input);
        len = strlen((const char *)wParam);
        if(exist_len + len < CHAT_INPUT_LEN)
        {
            insert_len = insert_string_at_cursor((char *)data->chat_input, (char*)wParam, 
                data->chat_input_index);
            data->chat_input_max += insert_len;
            data->chat_input_index += insert_len;
            //
            if(data->chat_input_index - data->chat_show_index >= MAX_SHOW_BYTES)
            {
                data->chat_show_index = find_after_cursor_position((char *)data->chat_input, 
                    data->chat_show_index, AUTO_ADJUST_BYTES);
            }
            data->chat_show_len = find_after_cursor_position((char *)data->chat_input,
                data->chat_show_index, MAX_SHOW_BYTES) - data->chat_show_index;
        }
        return  true;
        
    case WM_KEYDOWN:
        {
            switch(wParam)
            {
            case VK_BACK:   //�R�����Ыe���@�Ӧr���Ϊ̺~�r
                if(data->chat_input_index > 0)
                {
                    delete_len = delete_before_cursor_word((char *)data->chat_input, data->chat_input_index);
                    data->chat_input_index -= delete_len;
                    data->chat_input_max = strlen((const char *)data->chat_input);
                    
                    if(data->chat_input_index <= data->chat_show_index)
                    {
                        data->chat_show_index = find_before_cursor_position((char *)data->chat_input, 
                            data->chat_show_index, AUTO_ADJUST_BYTES);
                    }
                    data->chat_show_len = find_after_cursor_position((char *)data->chat_input,
                        data->chat_show_index, MAX_SHOW_BYTES) - data->chat_show_index;
                }
                return  true;
                
            case VK_DELETE: //�R�����Ы᪺�@�Ӧr���Ϊ̺~�r
                if(data->chat_input_index < data->chat_input_max)
                {
                    delete_len = delete_after_cursor_word((char *)data->chat_input, data->chat_input_index);
                    data->chat_input_max = strlen((const char *)data->chat_input);
                    
                    data->chat_show_len = find_after_cursor_position((char *)data->chat_input,
                        data->chat_show_index, MAX_SHOW_BYTES) - data->chat_show_index;
                }
                return  true;
                
            case VK_HOME:   //�^���J���歺
                data->chat_input_index = 0;
                data->chat_show_index = 0;
                data->chat_show_index = 0;
                data->chat_show_len = find_after_cursor_position((char *)data->chat_input,
                    data->chat_show_index, MAX_SHOW_BYTES) - data->chat_show_index;
                return  true;
                
            case VK_END:    //�^���J�����
                data->chat_input_index = data->chat_input_max;
                //
                data->chat_show_index = find_before_cursor_position((char *)data->chat_input, 
                    data->chat_input_index, MAX_SHOW_BYTES);
                data->chat_show_len = find_after_cursor_position((char *)data->chat_input,
                    data->chat_show_index, MAX_SHOW_BYTES) - data->chat_show_index;
                return  true;
                
            case VK_UP:     //��o��e�����W�@������Ѭ���
                if(TTN_OK == game_chat.get_prev_input(NULL, buffer, false))
                {
                    strcpy((char *)data->chat_input, (const char *)buffer);
                    data->chat_input_max = strlen((const char *)data->chat_input);
                    data->chat_input_index = data->chat_input_max;
                    
                    data->chat_show_index = find_before_cursor_position((char *)data->chat_input, 
                        data->chat_input_index, MAX_SHOW_BYTES);
                    data->chat_show_len = find_after_cursor_position((char *)data->chat_input,
                        data->chat_show_index, MAX_SHOW_BYTES) - data->chat_show_index;
                }
                return  true;
                
            case VK_DOWN:   //��o��e�����U�@������Ѭ���
                if(TTN_OK == game_chat.get_next_input(NULL, buffer, false))
                {
                    strcpy((char *)data->chat_input, (const char *)buffer);
                    data->chat_input_max = strlen((const char *)data->chat_input);
                    data->chat_input_index = data->chat_input_max;
                    
                    data->chat_show_index = find_before_cursor_position((char *)data->chat_input, 
                        data->chat_input_index, MAX_SHOW_BYTES);
                    data->chat_show_len = find_after_cursor_position((char *)data->chat_input,
                        data->chat_show_index, MAX_SHOW_BYTES) - data->chat_show_index;
                }
                return  true;
                
            case VK_LEFT:   //���в���e�@�Ӻ~�r
                if(data->chat_input_index > 0)
                {
                    data->chat_input_index = find_prev_word_position(
                        (char *)data->chat_input, data->chat_input_index);
                    if(data->chat_input_index <= data->chat_show_index)
                    {
                        data->chat_show_index = find_before_cursor_position((char *)data->chat_input, 
                            data->chat_show_index, AUTO_ADJUST_BYTES);
                        data->chat_show_len = find_after_cursor_position((char *)data->chat_input,
                            data->chat_show_index, MAX_SHOW_BYTES) - data->chat_show_index;
                    }
                }
                return  true;
                
            case VK_RIGHT:  //���в����@�Ӻ~�r
                if(data->chat_input_index < data->chat_input_max)
                {
                    data->chat_input_index = find_next_word_position(
                        (char *)data->chat_input, data->chat_input_index);
                    if(data->chat_input_index - data->chat_show_index >= MAX_SHOW_BYTES)
                    {
                        data->chat_show_index = find_after_cursor_position((char *)data->chat_input, 
                            data->chat_show_index, AUTO_ADJUST_BYTES);
                        data->chat_show_len = find_after_cursor_position((char *)data->chat_input,
                            data->chat_show_index, MAX_SHOW_BYTES) - data->chat_show_index;
                    }
                }
                return  true;
                
            case VK_ESCAPE: //������J
                clear_map_chat_input();
                activate_map_chat_input(false);
                return  true;
                
            case VK_INSERT: //�H�KWINDOWS�ŶK�O�������e���J��
                exist_len = strlen((const char *)data->chat_input);
                append_len = CHAT_INPUT_LEN - exist_len;
                if(append_len > 0)
                {
                    copy_len = copy_text_from_clipboard(g_hDDWnd, (USTR*)clip_buffer, append_len);
                    if(copy_len > 0)
                    {
                        insert_len = insert_string_at_cursor((char *)data->chat_input, (char*)clip_buffer, 
                            data->chat_input_index);
                        data->chat_input_max += insert_len;
                        data->chat_input_index += insert_len;
                        
                        if(data->chat_input_index - data->chat_show_index >= MAX_SHOW_BYTES)
                        {
                            data->chat_show_index = find_after_cursor_position((char *)data->chat_input, 
                                data->chat_show_index, AUTO_ADJUST_BYTES);
                        }
                        data->chat_show_len = find_after_cursor_position((char *)data->chat_input,
                            data->chat_show_index, MAX_SHOW_BYTES) - data->chat_show_index;
                    }
                }
                return  true;
                
            case VK_OEM_COMMA:  //','
                return  true;
                
            case VK_OEM_PERIOD: //'.'
                return  true;
                
            default:
                kb = (BYTE)wParam;
                if(isprint(kb))
                    return  true;
                return  false;
            }
        }
        
    case WM_KEYUP:
        return  true;
        
    case WM_CHAR:
        switch(wParam)
        {
        case VK_RETURN: //�^���o�e����, ������ѿ�J, �åB������J�k.
            if(0 < strlen((const char *)data->chat_input))
            {
                client_cmd_public_talk((char *)GetCharacterMainName(g_lPlayerIndex), (char *)data->chat_input);
                game_chat.add_input(CHATEFF_WHITE, (USTR*)data->chat_input);
                clear_map_chat_input();
                activate_map_chat_input(false);
            }
            else
            {
                activate_map_chat_input(false);
            }
            return  true;
        default:
            kb = (BYTE)wParam;
            if(isprint(kb)) //�O�^��r��, �N�Ӧr�����J����Ц�m
            {
                exist_len = strlen((const char *)data->chat_input);
                if(exist_len + 1 < CHAT_INPUT_LEN)
                {
                    clip_buffer[0] = kb;
                    clip_buffer[1] = '\0';
                    insert_len = insert_string_at_cursor((char *)data->chat_input, (char*)clip_buffer, 
                        data->chat_input_index);
                    data->chat_input_max += insert_len;
                    data->chat_input_index += insert_len;
                    //
                    if(data->chat_input_index - data->chat_show_index >= MAX_SHOW_BYTES)
                    {
                        data->chat_show_index = find_after_cursor_position((char *)data->chat_input, 
                            data->chat_show_index, AUTO_ADJUST_BYTES);
                    }
                    data->chat_show_len = find_after_cursor_position((char *)data->chat_input,
                        data->chat_show_index, MAX_SHOW_BYTES) - data->chat_show_index;
                }
            }
            return  true;
        }
    }
    return  false;
}
                                                            
*/