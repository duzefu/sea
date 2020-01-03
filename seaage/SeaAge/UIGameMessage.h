/*
**	UIGameMessage.h
**	UI of game message.
**
**	Jack, 2002/10/22.
*/
#ifndef _UIGAMEMESSAGE_H_
#define _UIGAMEMESSAGE_H_


#define GAMEMSG_TYPE_SYSTEM             0   //系統發起的訊息
#define GAMEMSG_TYPE_MYSELF             1   //玩家自己的操作引起的訊息



// F U N C T I O N S ///////////////////////////////////////////////////////////////////////////////////////////////
int     init_game_message(void);
void    free_game_message(void);

void    refresh_game_message(void);
SLONG   add_game_message(SLONG type, USTR *msg);
void    redraw_game_message(BMP *bitmap);
void    clear_game_message(void);




#endif//_UIGAMEMESSAGE_H_
