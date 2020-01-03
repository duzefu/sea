/*
**	UIMapChat.h
**	UI of map chat.
**
**	Jack, 2002/10/28.
*/
#ifndef _UIMAPCHAT_H_
#define _UIMAPCHAT_H_


SLONG   filter_map_chat_input(UINT message, WPARAM wParam, LPARAM lParam);
SLONG   is_map_chat_input_active(void);
void    activate_map_chat_input(SLONG active);
void    clear_map_chat_input(void);
void    set_maingame_chat_ime_name(char *name);
USTR*   get_maingame_chat_ime_name(void);


#endif//_UIMAPCHAT_H_
