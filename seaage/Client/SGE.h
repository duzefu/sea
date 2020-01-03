/*
**  sge.h
**  specially good effect header.
**
**  zjian,2001.5.28.
*/
#ifndef _SGE_H_INCLUDE_
#define _SGE_H_INCLUDE_


typedef struct  tagSGE
{
    ULONG   day;
    ULONG   time;
} SGE, *LPSGE;


extern  int     init_sge(void);
extern  void    active_sge(int active);
extern  void    free_sge(void);
extern  void    refresh_sge(void);
//
extern  void    sge_show_light(SLONG mouse_x, SLONG mouse_y, void *vbitmap);
//
extern  void    clear_screen_light(void);
extern  void    add_npc_light(SLONG npc_x, SLONG npc_y, SLONG npc_z);
extern  void    add_magic_light(SLONG magic_x, SLONG magic_y, SLONG magic_z);
extern  void    redraw_screen_light(void *vbitmap);


#endif//_SGE_H_INCLUDE_

