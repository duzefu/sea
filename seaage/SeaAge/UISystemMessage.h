/*
**	UISystemMessage.h
**	UI of system message.
**
**	Jack, 2002/10/21.
*/
#ifndef _UISYSTEMMESSAGE_H_
#define _UISYSTEMMESSAGE_H_


// F U N C T I O N S ///////////////////////////////////////////////////////////////////////////////////////////////
int     init_system_message(void);
void    free_system_message(void);

void    refresh_system_message(void);
SLONG   add_system_message(USTR *world, USTR *msg);
void    redraw_system_message(BMP *bitmap);
void    clear_system_message(void);




#endif//_UISYSTEMMESSAGE_H_
