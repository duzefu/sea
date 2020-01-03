/*
**	MapUtility.h 
**	map utility functions.
**
**	Jack, 2003.1.23.
*/
#pragma once


//
// DEFINES //////////////////////////////////////////////////////////////////////////////////////////////////
//
#define	MAX_MAP_OBJECT_TYPES			64	//地圖上最多物件種類數目


#define	register_map_object(type_data, type_name)	register_map_object_type_utility(type_data, \
	add_##type_name,\
	del_##type_name,\
	draw_##type_name,\
	refresh_##type_name,\
	change_##type_name##_id,\
	get_##type_name##_information)

//
// STRUCTURES ///////////////////////////////////////////////////////////////////////////////////////////////
//
typedef	SLONG	(*FNADDOBJ)		(SLONG id, SLONG px, SLONG py, SLONG pz, SLONG effect, SLONG ext_data);
typedef	SLONG	(*FNDELOBJ)		(SLONG object_index);
typedef	void	(*FNDRAWOBJ)	(SLONG object_index, SLONG flags, BMP *bitmap);
typedef	void	(*FNREFRESHOBJ)	(SLONG object_index);
typedef	SLONG	(*FNCHGOBJID)	(SLONG object_index, SLONG id);
typedef	SLONG	(*FNGETOBJINFO)	(SLONG object_index, SLONG *object_flag, SLONG *sx, SLONG *sy, 
								 SLONG *ex, SLONG *ey, POLY **poly);

//
//
// GLOBALS //////////////////////////////////////////////////////////////////////////////////////////////////
//

//
// FUNCTIONS ////////////////////////////////////////////////////////////////////////////////////////////////
//
void	init_map_object_type_utility(void);
SLONG	register_map_object_type_utility(SLONG object_type, FNADDOBJ fn_add, FNDELOBJ fn_del, FNDRAWOBJ fn_draw, 
										 FNREFRESHOBJ fn_refresh, FNCHGOBJID fn_change_id,
										 FNGETOBJINFO fn_get_info);
SLONG	add_map_object(SLONG type_flags, SLONG id, SLONG px, SLONG py, SLONG pz, SLONG effect, SLONG ext_data);
SLONG	del_map_object(SLONG object_index);
void	draw_map_object(SLONG object_index, SLONG flags, BMP *bitmap);
void	refresh_map_object(SLONG object_index);
SLONG	change_map_object_id(SLONG object_index, SLONG new_id);
SLONG	get_map_object_information(SLONG object_index, SLONG *object_flag, SLONG *sx, SLONG *sy, 
								   SLONG *ex, SLONG *ey, POLY **poly);

