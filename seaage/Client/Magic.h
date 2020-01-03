/*
**  Magic.h
**  magic functions.
**
**  Jack, 2002.4.
*/
#ifndef _MAGIC_H_
#define _MAGIC_H_


//
// FUNCTIONS ///////////////////////////////////////////////////////////////////////////////////////////////////////
//
int     init_magic(void);
void    active_magic(int active);
void    free_magic(void);
//
void    refresh_map_magic(void);
void    update_map_magic_object(void);
//

//
// Map magic object functions:
//
SLONG   add_map_magic_object(SLONG id, SLONG px, SLONG py, SLONG pz, SLONG effect, SLONG magic_part_no);
SLONG	del_map_magic_object(SLONG object_index);
void	draw_map_magic_object(SLONG object_index, SLONG flags, BMP *bitmap);
void	refresh_map_magic_object(SLONG object_index);
SLONG	change_map_magic_object_id(SLONG object_index, SLONG new_id);
SLONG	get_map_magic_object_information(SLONG object_index, SLONG *object_flag, SLONG *sx, SLONG *sy, 
										 SLONG *ex, SLONG *ey, POLY **poly);


#endif//_MAGIC_H_
