/*
**	MapUtility.cpp 
**	map utility functions.
**
**	Jack, 2003.1.23.
*/
#include "MainFun.h"
#include "Map.h"
#include "MapUtility.h"




/************************************************************************************************************/
/* DEFINES & STRUCTURES                                                                                     */
/************************************************************************************************************/
#define	MAX_MAP_OBJECT_TYPES			64	// Counts of defferent map object types.


typedef	struct tagOBJECT_TYPE_UTILITY
{
	//
	FNADDOBJ		add_object_func;		// Processing function of add map object.
	FNDELOBJ		del_object_func;		// Processing function of del map object.
	FNDRAWOBJ		draw_object_func;		// Processing function of draw map object.
	FNREFRESHOBJ	refresh_object_func;	// Refreshing the object function.
	FNCHGOBJID		change_object_id_func;	// Changing object image id.
	FNGETOBJINFO	get_object_info_func;	// Function for get map object information.
	//
} OBJECT_TYPE_UTILITY, *LPOBJECT_TYPE_UTILITY;

/************************************************************************************************************/
/* GLOBALS                                                                                                  */
/************************************************************************************************************/
OBJECT_TYPE_UTILITY	l_object_type_utility[MAX_MAP_OBJECT_TYPES];


static	SLONG	dummy_add_object_func(SLONG id, SLONG px, SLONG py, SLONG pz, SLONG effect, SLONG ext_data);
static	SLONG	dummy_del_object_func(SLONG object_index);
static	void	dummy_draw_object_func(SLONG object_index, SLONG flags, BMP *bitmap);
static	void	dummy_refresh_object_func(SLONG object_index);
static	SLONG	dummy_change_object_id_func(SLONG object_index, SLONG new_id);
static	SLONG	dummy_get_object_information_func(SLONG object_index, SLONG *object_flag, SLONG *sx, SLONG *sy, 
												  SLONG *ex, SLONG *ey, POLY **poly);

/************************************************************************************************************/
/* STATIC FUNCTIONS                                                                                         */
/************************************************************************************************************/
static	SLONG	dummy_add_object_func(SLONG id, SLONG px, SLONG py, SLONG pz, SLONG effect, SLONG ext_data)
{
	return	-1;
}

static	SLONG	dummy_del_object_func(SLONG object_index)
{
	return	TTN_OK;
}

static	void	dummy_draw_object_func(SLONG object_index, SLONG flags, BMP *bitmap)
{
	return;
}

static	void	dummy_refresh_object_func(SLONG object_index)
{
	return;
}

static	SLONG	dummy_change_object_id_func(SLONG object_index, SLONG new_id)
{
	return	TTN_NOT_OK;
}

static	SLONG	dummy_get_object_information_func(SLONG object_index, SLONG *object_flag, SLONG *sx, SLONG *sy, 
												  SLONG *ex, SLONG *ey, POLY **poly)
{
	return	TTN_NOT_OK;
}
/************************************************************************************************************/
/* OBJECT UTILITY FUNCTIONS                                                                                 */
/************************************************************************************************************/
void	init_map_object_type_utility(void)
{
	SLONG	i;

	for(i=0; i<MAX_MAP_OBJECT_TYPES; i++)
	{
		l_object_type_utility[i].add_object_func = dummy_add_object_func;
		l_object_type_utility[i].del_object_func = dummy_del_object_func;
		l_object_type_utility[i].draw_object_func = dummy_draw_object_func;
		l_object_type_utility[i].refresh_object_func = dummy_refresh_object_func;
		l_object_type_utility[i].change_object_id_func = dummy_change_object_id_func;
		l_object_type_utility[i].get_object_info_func = dummy_get_object_information_func;
	}
}


SLONG	register_map_object_type_utility(SLONG object_type, FNADDOBJ fn_add, FNDELOBJ fn_del, FNDRAWOBJ fn_draw, 
										 FNREFRESHOBJ fn_refresh, FNCHGOBJID fn_change_id, FNGETOBJINFO fn_get_info)
{
	OBJECT_TYPE_UTILITY	*data;
	SLONG	result;

	result = TTN_NOT_OK;
	if(object_type >= 0 && object_type < MAX_MAP_OBJECT_TYPES)
	{
		data = &l_object_type_utility[object_type];

		if(fn_add) data->add_object_func = fn_add;
		if(fn_del) data->del_object_func = fn_del;
		if(fn_draw) data->draw_object_func = fn_draw;
		if(fn_refresh) data->refresh_object_func = fn_refresh;
		if(fn_change_id) data->change_object_id_func = fn_change_id;
		if(fn_get_info) data->get_object_info_func = fn_get_info;

		result = TTN_OK;
	}
	return	result;
}


SLONG	add_map_object(SLONG type_flags, SLONG id, SLONG px, SLONG py, SLONG pz, SLONG effect, SLONG ext_data)
{
	SLONG	object_type;
	SLONG	object_index;

	object_index = -1;
	object_type = GET_MAP_OBJECT_TYPE(type_flags);
	if(object_type >= 0 && object_type < MAX_MAP_OBJECT_TYPES)
	{
		object_index = l_object_type_utility[object_type].add_object_func(id, px, py, pz, effect, ext_data);
	}
	return	object_index;
}


SLONG	del_map_object(SLONG object_index)
{
	SLONG	object_type;

	if(object_index < 0 || object_index >= map_object_max)
		return	TTN_OK;

	object_type = GET_MAP_OBJECT_TYPE(map_object[object_index].flag);
	if(object_type >= 0 && object_type < MAX_MAP_OBJECT_TYPES)
	{
		l_object_type_utility[object_type].del_object_func(object_index);
	}
	return	TTN_OK;
}


void	draw_map_object(SLONG object_index, SLONG flags, BMP *bitmap)
{
	SLONG	object_type;

	if(object_index < 0 || object_index >= map_object_max)
		return;

	object_type = GET_MAP_OBJECT_TYPE(map_object[object_index].flag);
	if(object_type >= 0 && object_type < MAX_MAP_OBJECT_TYPES)
	{
		l_object_type_utility[object_type].draw_object_func(object_index, flags, bitmap);
	}
	return;
}


void	refresh_map_object(SLONG object_index)
{
	SLONG	object_type;

	if(object_index < 0 || object_index >= map_object_max)
		return;

	object_type = GET_MAP_OBJECT_TYPE(map_object[object_index].flag);
	if(object_type >= 0 && object_type < MAX_MAP_OBJECT_TYPES)
	{
		l_object_type_utility[object_type].refresh_object_func(object_index);
	}
	return;
}


SLONG	change_map_object_id(SLONG object_index, SLONG new_id)
{
	SLONG	object_type, result;

	result = TTN_NOT_OK;
	object_type = GET_MAP_OBJECT_TYPE(map_object[object_index].flag);
	if(object_type >= 0 && object_type < MAX_MAP_OBJECT_TYPES)
	{
		result = l_object_type_utility[object_type].change_object_id_func(object_index, new_id);
	}
	return	result;
}


SLONG	get_map_object_information(SLONG object_index, SLONG *object_flag, SLONG *sx, SLONG *sy, 
								   SLONG *ex, SLONG *ey, POLY **poly)
{
	SLONG	result;
	SLONG	object_type;

	if(object_index < 0 || object_index >= map_object_max)
		return TTN_NOT_OK;

	result = TTN_NOT_OK;
	object_type = GET_MAP_OBJECT_TYPE(map_object[object_index].flag);
	if(object_type >= 0 && object_type < MAX_MAP_OBJECT_TYPES)
	{
		result = l_object_type_utility[object_type].get_object_info_func(object_index, object_flag,
			sx, sy, ex, ey, poly);
	}
	return	result;
}

