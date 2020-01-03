/*
**      MAP.CPP
**      map functions.
**
**      ZJian, 2000.8.16.
**          Created.
**      ZJian, 2001.6.27.
**          Classify the map object to under_object & normal_object for ARPG use.
**
*/
#include "MainFun.h"
#include "NetGE_MainFunc.h"
//
#include "CRange.h"
#include "Map.h"
#include "Npc.h"
#include "MapTile.h"
#include "MapHouse.h"
#include "MapBlock.h"
#include "MapUpper.h"
#include "MapLight.h"
#include "MapTrack.h"
#include "MapUtility.h"
//
#include "Client_Item.h"
#include "Magic.h"
#include "SGE.h"
#include "UIMagicArea.h"


#define map_object_timer_tick       timer_tick09
#define MAP_OBJECT_REFRESH_SPEED    3   // ticks

//
MAP_HEAD        map_head;
MAP_DATA        map_data;
MAP_OBJECT      map_object[MAX_MAP_OBJECT];
MAP_OBJECT_EX   map_object_ex[MAX_MAP_OBJECT];
SLONG           map_object_max;
MAP_MOVE        map_move;

//
//Jack, 2001.6.26. 將地圖上地毯類物件和一般物件分開處理.
static  SLONG   map_under_obj_queue[MAX_MAP_OBJECT];    //地毯類物件列表
static  SLONG   map_under_obj_max = 0;
static  SLONG   map_normal_obj_queue[MAX_MAP_OBJECT];   //需要重繪的普通物件列表
static  SLONG   map_normal_obj_max = 0;
static  int     map_normal_obj_turn[MAX_MAP_OBJECT];    //需要重繪的普通物件順序

//---------------------------------------------------------------------------------
static  void    reinit_map_contain(void);
static  void    classify_map_object(BMP *bitmap);
static  void    redraw_map_under_object_layer(SLONG map_sx,SLONG map_sy,BMP *bitmap);
static  void    redraw_map_normal_object_layer(SLONG map_sx,SLONG map_sy,BMP *bitmap);
static	void    clear_all_map_objects(void);
static	void    refresh_all_map_objects(void);


//
// Simple map object functions
//
SLONG	add_map_simple_object(SLONG id, SLONG px, SLONG py, SLONG pz, SLONG effect, SLONG change_tick);
SLONG	del_map_simple_object(SLONG object_index);
void	draw_map_simple_object(SLONG object_index, SLONG flags, BMP *bitmap);
void	refresh_map_simple_object(SLONG object_index);
SLONG	change_map_simple_object_id(SLONG object_index, SLONG new_id);
SLONG	get_map_simple_object_information(SLONG object_index, SLONG *object_flag, SLONG *sx, SLONG *sy, 
										  SLONG *ex, SLONG *ey, POLY **poly);
//
// Dynamic map object functions
//
SLONG   add_map_dynamic_object(SLONG id, SLONG px, SLONG py, SLONG pz, SLONG effect, SLONG change_tick);
SLONG	del_map_dynamic_object(SLONG object_index);
void	draw_map_dynamic_object(SLONG object_index, SLONG flags, BMP *bitmap);
void	refresh_map_dynamic_object(SLONG object_index);
SLONG	change_map_dynamic_object_id(SLONG object_index, SLONG new_id);
SLONG	get_map_dynamic_object_information(SLONG object_index, SLONG *object_flag, SLONG *sx, SLONG *sy, 
										   SLONG *ex, SLONG *ey, POLY **poly);
//
// Fixed map object functions
//
SLONG   add_map_fixed_object(SLONG id, SLONG px, SLONG py, SLONG pz, SLONG effect, SLONG change_tick);
SLONG	del_map_fixed_object(SLONG object_index);
void	draw_map_fixed_object(SLONG object_index, SLONG flags, BMP *bitmap);
void	refresh_map_fixed_object(SLONG object_index);
SLONG	change_map_fixed_object_id(SLONG object_index, SLONG new_id);
SLONG	get_map_fixed_object_information(SLONG object_index, SLONG *object_flag, SLONG *sx, SLONG *sy, 
										 SLONG *ex, SLONG *ey, POLY **poly);

//
// House object functions
//
SLONG   add_map_house_object(SLONG id, SLONG px, SLONG py, SLONG pz, SLONG effect, SLONG reserved);
SLONG	del_map_house_object(SLONG object_index);
void	draw_map_house_object(SLONG object_index, SLONG flags, BMP *bitmap);
void	refresh_map_house_object(SLONG object_index);
SLONG	change_map_house_object_id(SLONG object_index, SLONG new_id);
SLONG	get_map_house_object_information(SLONG object_index, SLONG *object_flag, SLONG *sx, SLONG *sy, 
										 SLONG *ex, SLONG *ey, POLY **poly);

//
// House roof functions
//
SLONG   add_map_house_roof(SLONG id, SLONG px, SLONG py, SLONG pz, SLONG effect, SLONG reserved);
SLONG	del_map_house_roof(SLONG object_index);
void	draw_map_house_roof(SLONG object_index, SLONG flags, BMP *bitmap);
void	refresh_map_house_roof(SLONG object_index);
SLONG	change_map_house_roof_id(SLONG object_index, SLONG new_id);
SLONG	get_map_house_roof_information(SLONG object_index, SLONG *object_flag, SLONG *sx, SLONG *sy, 
									   SLONG *ex, SLONG *ey, POLY **poly);

//
// Npc object functions
//
// In Npc.cpp
//

//
// Magic object functions
//
// In Magic.cpp.
//


/************************************************************************************************************/
/* MAP MAIN FUNCTIONS                                                                                       */
/************************************************************************************************************/
EXPORT  int     FNBACK  init_map(void)
{
    if(TTN_OK != init_map_tile_system())
        return -1;
    if(TTN_OK != init_map_object_system())
        return -1;
    if(TTN_OK != init_map_upper_system())
        return -1;
    if(TTN_OK != init_map_track_system())
        return -1;
	if(TTN_OK != init_map_light_system())
		return	-1;
    if(TTN_OK != init_map_house_system())
        return  -1;

    init_map_data(&map_data);
    reinit_map_contain();

    init_magic_area();

	init_map_object_type_utility();
	register_map_object(GET_MAP_OBJECT_TYPE(MOBJ_SIMPLE),		map_simple_object		);
	register_map_object(GET_MAP_OBJECT_TYPE(MOBJ_DYNAMIC),		map_dynamic_object		);
	register_map_object(GET_MAP_OBJECT_TYPE(MOBJ_FIXED),		map_fixed_object		);
	register_map_object(GET_MAP_OBJECT_TYPE(MOBJ_HOUSE_OBJECT),	map_house_object		);
	register_map_object(GET_MAP_OBJECT_TYPE(MOBJ_HOUSE_ROOF),	map_house_roof			);
	register_map_object(GET_MAP_OBJECT_TYPE(MOBJ_NPC),			map_npc_object			);
	register_map_object(GET_MAP_OBJECT_TYPE(MOBJ_MAGIC),		map_magic_object		);
	//register_map_object(GET_MAP_OBJECT_TYPE(MOBJ_DOOR),		map_door_object			);

    return 0;
}

EXPORT  void    FNBACK  free_map(void)
{
    free_map_object_system();
    free_map_tile_system();
    free_map_upper_system();
    free_map_track_system();
	free_map_light_system();
    free_map_house_system();

    reinit_map_contain();
    free_magic_area();
}


EXPORT  void    FNBACK  active_map(int active)
{
    if(active)
    {
    }
}


EXPORT  void    FNBACK  clear_map(void)
{
    if(map_head.layer & MAP_LAYER_TILE)
    {
        destroy_tile_field(&map_tile_field);
        map_head.layer &= ~MAP_LAYER_TILE;
    }

    if(map_head.layer & MAP_LAYER_UPPER)
    {
        clear_all_map_uppers();
        map_head.layer &= ~MAP_LAYER_UPPER;
    }

    if(map_head.layer & MAP_LAYER_OBJECT)
    {
        clear_all_map_objects();
        map_head.layer &= ~MAP_LAYER_OBJECT;
    }

    if(map_head.layer & MAP_LAYER_HOUSE)
    {
        clear_all_map_houses();
        map_head.layer &= ~MAP_LAYER_HOUSE;
    }
}



EXPORT  SLONG   FNBACK  load_map(USTR *filename)
{
    PACK_FILE    *fp=NULL;
    USTR    map_filename[_MAX_FNAME];
    SLONG   obj_index;
    SLONG i;

    strcpy((char *)map_filename, (const char *)filename);

    clear_map();
    
    if(NULL==(fp=pack_fopen((const char *)map_filename,"rb")))
    {
        sprintf((char *)print_rec,"file %s open error",map_filename);
        log_error(1,print_rec);
        return(TTN_ERROR);
    }
    // (1) map header ---------------------------------------------------- 
    pack_fread(&map_head,1,sizeof(MAP_HEAD),fp);
    map_object_max = map_head.total_objects;

    set_map_block_count( map_head.total_blocks );
    set_map_proc_count( map_head.total_procs );
    set_map_house_count( map_head.total_houses );

    // (2) map cell layer ------------------------------------------------
    if(map_head.layer & MAP_LAYER_TILE)
    {
        destroy_tile_field(&map_tile_field);
        naked_read_tile_field(fp, &map_tile_field);
    }
    // (3) map upper layer -------------------------------------------------
    if(map_head.layer & MAP_LAYER_UPPER)
    {
        naked_read_map_upper(fp);
        map_head.total_uppers  = get_map_upper_count();
    }
    // (4) map house layer -------------------------------------------------
    if(map_head.layer & MAP_LAYER_HOUSE)
    {
        SLONG   house_no, house_flag;

        naked_read_map_house(fp, map_head.total_houses);
        for(i=0; i<map_head.total_houses; i++)
        {
            house_flag = map_house[i].flag;
            house_no = map_house[i].no;
            if(house_flag && house_no >= 0)
            {
                add_reference_for_house(house_no);
            }
        }
    }

    // (5) map object layer ------------------------------------------------
    if(map_head.layer & MAP_LAYER_OBJECT)
    {
        CAKE_FRAME_ANI *cfa=NULL;
        SLONG id_type,id_index,object_type;

        // we read map object data first
        pack_fread((USTR *)&map_object[0],1,sizeof(MAP_OBJECT)*map_head.total_objects,fp);

        // start add all map object
        for(i=0;i<map_head.total_objects;i++)
        {
            obj_index = i;
            object_type = map_object[obj_index].flag & MOBJ_TYPES;
            if( object_type == MOBJ_FIXED )
            {
                naked_read_cake_frame_ani(fp, &cfa);

                id_type = MAKE_OBJECT_TYPE(map_object[obj_index].id);
                id_index = MAKE_OBJECT_INDEX(map_object[obj_index].id);
                register_map_object_image(id_type,id_index,cfa);
            }
            else
            {
                add_reference_for_map_object_image(map_object[obj_index].id);
            }
        }
    }
    // (6) map block info ---------------------------------------------------
    naked_read_map_block( fp, map_head.total_blocks);

    // (7) map proc info ----------------------------------------------------
    naked_read_map_proc( fp, map_head.total_procs);

    if(fp) pack_fclose(fp);

    //(X) some append process ----------------------------------------------
    strcpy((char *)map_data.filename,(const char *)get_nopath_filename((USTR *)map_filename));

    reset_map_start_position();

    return(TTN_OK);
}


void    redraw_map(BMP *bitmap)
{
    SLONG   map_no = 0;

	//
	//(1) clear something.
	//
    //clear_screen_light();
    clear_npc_talk_list();

	//
    //(2) refresh map normal & dynamic objects.
	//
    refresh_all_map_objects();
    refresh_map_track();
    update_map_npc_object();
    update_map_magic_object();

    classify_map_object(bitmap);

    clear_bitmap(bitmap);
    if(map_head.layer & MAP_LAYER_TILE)
    {
        redraw_tile_field(map_tile_field, map_data.map_sx, map_data.map_sy, bitmap);
        //plat_redraw_tile_field(map_tile_field, map_data.map_sx, map_data.map_sy, bitmap);
    }
    if(map_head.layer & MAP_LAYER_UPPER)
    {
        redraw_map_upper_layer(map_data.map_sx, map_data.map_sy, bitmap);
    }
    if(map_head.layer & MAP_LAYER_OBJECT)
    {
        redraw_map_under_object_layer(map_data.map_sx, map_data.map_sy, bitmap);
    }
    redraw_magic_area(bitmap);
    redraw_map_item( map_no, map_data.map_sx, map_data.map_sy, bitmap);
    redraw_map_track_layer(map_data.map_sx, map_data.map_sy, bitmap);
    if(map_head.layer & MAP_LAYER_OBJECT)
    {
        redraw_map_normal_object_layer(map_data.map_sx, map_data.map_sy, bitmap);
    }

    redraw_map_npc_talk( map_no, map_data.map_sx, map_data.map_sy, bitmap);

    //effects ------------------------
    //redraw_screen_light(bitmap);
}


static  void    reinit_map_contain(void)
{
    int i;
    for(i=0;i<MAX_MAP_OBJECT;i++)
    {
        map_object[i].flag=0;
        map_object[i].id=INVALID_OBJECT_ID;
        map_object[i].frame=0;
    }
    map_object_max = 0;

    reset_map_block_count();
    reset_map_proc_count();
}


SLONG   get_usable_map_object(void)
{
    SLONG   find_usable;
    SLONG   i;

    find_usable = -1;
    for(i=0; i<MAX_MAP_OBJECT; i++)
    {
        if(! (map_object[i].flag & MOBJ_ACTIVE) )
        {
            find_usable=i;
            break;
        }
    }
    return  find_usable;
}


static	void    clear_all_map_objects(void)
{
    SLONG i;
    for(i = 0; i < MAX_MAP_OBJECT; i ++)
    {
        del_map_object(i);
    }
    map_object_max = 0;
}


static	void    refresh_all_map_objects(void)
{
    SLONG i;

    if(map_object_timer_tick>MAP_OBJECT_REFRESH_SPEED)
    {
        for(i=0; i<map_object_max; i++)
        {
			refresh_map_object(i);
        }
        map_object_timer_tick=0;
    }
}

static  void    redraw_map_under_object_layer(SLONG map_sx,SLONG map_sy,BMP *bitmap)
{
    SLONG   i, object_index;

    for(i=0; i<map_under_obj_max; i++)
    {
        object_index = map_under_obj_queue[i];
		draw_map_object(object_index, 1, bitmap);
    }
}

static  void    redraw_map_normal_object_layer(SLONG map_sx,SLONG map_sy,BMP *bitmap)
{
    SLONG   i, turn_value;
    SLONG   object_index;

    for(i=0; i<map_normal_obj_max; i++)
    {
        turn_value = map_normal_obj_turn[i];    //>0 for sort ok, <0 for can't sort.
        object_index = map_normal_obj_queue[abs(turn_value)-1];
		draw_map_object(object_index, turn_value, bitmap);
    }
}


static  void    classify_map_object(BMP *bitmap)
{
    SLONG   i, j, flag, sx, sy, ex, ey, obj_no1, obj_no2;
    SLONG   val, check_flag;
    POLY    *pl = NULL, *pl1 = NULL, *pl2 = NULL;
    
    //(1) classify screen map object to normal_object & under_object 
    //---------------------------------------------------------------------------------------------
    map_normal_obj_max = 0;
    map_under_obj_max = 0;
    for(i=0; i<map_object_max; i++)
    {
        if(TTN_OK == get_map_object_information(i, &flag, &sx, &sy, &ex, &ey, &pl))
        {
            if(sx>=bitmap->w || sy>=bitmap->h || ex<0 || ey<0)
                continue;

            //房屋屋頂被掀開時，不用重畫。
            if( ( (flag & MOBJ_TYPES) == MOBJ_HOUSE_ROOF )
                && (map_object[i].alpha == 0) )
                continue;

            if( (pl->bz == 0) || (flag & MOBJ_UNDER) )
            {
                map_under_obj_queue[map_under_obj_max] = i;
                map_under_obj_max ++;
            }
            else
            {
                map_object_ex[map_normal_obj_max].image_sx = sx;
                map_object_ex[map_normal_obj_max].image_sy = sy;
                map_object_ex[map_normal_obj_max].image_ex = ex;
                map_object_ex[map_normal_obj_max].image_ey = ey;
                map_object_ex[map_normal_obj_max].poly = pl;
                
                map_normal_obj_queue[map_normal_obj_max] = i;
                map_normal_obj_max ++;
            }
        }
    }

    //(2) topo sort the normal object 
    //---------------------------------------------------------------------------------------------
    if(map_normal_obj_max <= 1) // for 0 or 1, the sort is needless, but we must specify the turn
    {
        map_normal_obj_turn[0] = 1;
    }
    else if(map_normal_obj_max > 1)
    {
        int *dynamic_topo_relation = NULL;
        int dynamic_total_topo_relation = 0;

        dynamic_topo_relation = (int *)GlobalAlloc(GPTR, map_normal_obj_max * (map_normal_obj_max-1) * sizeof(int) );
        if(! dynamic_topo_relation)
        {
            log_error(1,"memory alloc error for classify_map_object()");
            return;
        }
        
        dynamic_total_topo_relation = 0 ;
        for(i=0; i<map_normal_obj_max; i++)
        {
            for(j=i+1; j<map_normal_obj_max; j++)
            {
                obj_no1 = map_normal_obj_queue[i];
                obj_no2 = map_normal_obj_queue[j];
                pl1 = map_object_ex[i].poly;
                pl2 = map_object_ex[j].poly;
                if(pl1 && pl2)
                {
                    check_flag=1;
                    if( (map_object_ex[i].image_sx >= map_object_ex[j].image_ex)
                        || (map_object_ex[i].image_sy >= map_object_ex[j].image_ey)
                        || (map_object_ex[i].image_ex <= map_object_ex[j].image_sx)
                        || (map_object_ex[i].image_ey <= map_object_ex[j].image_sy) )
                        check_flag=0;
                    
                    if(check_flag)
                    {
                        val = D3_check_deeply_poly_poly(
                            pl1, map_object[obj_no1].px, map_object[obj_no1].py, map_object[obj_no1].pz,
                            pl2, map_object[obj_no2].px, map_object[obj_no2].py, map_object[obj_no2].pz);
                        switch(val)
                        {
                        case DEEPLY_FIRST:     // 1 is deeper
                            dynamic_topo_relation[dynamic_total_topo_relation * 2]   = i+1;
                            dynamic_topo_relation[dynamic_total_topo_relation * 2 + 1] = j+1;
                            dynamic_total_topo_relation++;
                            break;
                        case DEEPLY_SECOND:     // 2 is deeper
                            dynamic_topo_relation[dynamic_total_topo_relation * 2]   = j+1;
                            dynamic_topo_relation[dynamic_total_topo_relation * 2 + 1] = i+1;
                            dynamic_total_topo_relation++;
                            break;
                        case DEEPLY_UNKNOWN:     // unknown
                            break;
                        }
                    }
                }
            }
        }
        
        topo_sort(map_normal_obj_max, dynamic_topo_relation, dynamic_total_topo_relation, map_normal_obj_turn );
        
        if(dynamic_topo_relation) 
        {
            GlobalFree(dynamic_topo_relation);
            dynamic_topo_relation = NULL;
        }
    }

    //(3) sort the under object
    //---------------------------------------------------------------------------------------------
    if(map_under_obj_max > 1)
    {
        for(i=0; i<map_under_obj_max; i++)
        {
            for(j=i+1; j<map_under_obj_max; j++)
            {
                obj_no1 = map_under_obj_queue[i];
                obj_no2 = map_under_obj_queue[j];
                if(map_object[obj_no1].pz > map_object[obj_no2].pz)
                {
                    map_under_obj_queue[i] = obj_no2;
                    map_under_obj_queue[j] = obj_no1;
                }
                else if(map_object[obj_no1].pz == map_object[obj_no2].pz)
                {
                    if(map_object[obj_no1].py > map_object[obj_no2].py)
                    {
                        map_under_obj_queue[i] = obj_no2;
                        map_under_obj_queue[j] = obj_no1;
                    }
                    else if(map_object[obj_no1].py == map_object[obj_no2].py)
                    {
                        if(map_object[obj_no1].px > map_object[obj_no2].px)
                        {
                            map_under_obj_queue[i] = obj_no2;
                            map_under_obj_queue[j] = obj_no1;
                        }
                    }
                }
            }
        }
    }
}


/************************************************************************************************************/
/* MAP DATA FUNCTIONS                                                                                       */
/************************************************************************************************************/
EXPORT  void    FNBACK  init_map_data(MAP_DATA *map_data)
{
    strcpy((char *)map_data->filename,"NONAME.MAP");
    strcpy((char *)map_data->mapname,"未知世界");
    map_data->redraw_flags = 0;
    map_data->map_sx = 0;
    map_data->map_sy = 0;
    map_data->map_tx = 0;
    map_data->map_ty = 0;
    map_data->map_mx = 4;
    map_data->map_my = 4;
    map_data->view_sx = 0;
    map_data->view_sy = 0;
    map_data->view_xl = SCREEN_WIDTH;
    map_data->view_yl = SCREEN_HEIGHT;
    //
    SLONG   tiles;
    double  zoom;

    tiles = (SCREEN_WIDTH / 4 + TILE_WIDTH - 1)/TILE_WIDTH;
    map_data->zoom_win_def_xl = tiles * TILE_WIDTH;
    map_data->zoom_win_def_yl = tiles * TILE_HEIGHT;

    map_data->zoom_win_xl = map_data->zoom_win_def_xl;
    map_data->zoom_win_yl = map_data->zoom_win_def_yl;
    map_data->zoom_win_sx = SCREEN_WIDTH - map_data->zoom_win_xl - 4;
    map_data->zoom_win_sy = SCREEN_HEIGHT - map_data->zoom_win_yl - 32;

    map_data->zoom_control = 0.1;
    zoom = 1 / map_data->zoom_control;
    map_data->zoom_map_xl = (SLONG)(map_data->zoom_win_xl * zoom);
    map_data->zoom_map_yl = (SLONG)(map_data->zoom_win_yl * zoom);
    map_data->zoom_map_sx = (map_data->map_sx + SCREEN_WIDTH/2) - (SLONG)(map_data->zoom_win_xl * zoom / 2);
    map_data->zoom_map_sy = (map_data->map_sy + SCREEN_HEIGHT/2) - (SLONG)(map_data->zoom_win_yl * zoom / 2);

    return;
}

void    set_map_redraw_flags(SLONG flags)
{
    map_data.redraw_flags = flags;
}

void    reset_map_start_position(void)
{
    map_data.map_sx=map_head.map_xl/2-SCREEN_WIDTH/2;
    map_data.map_sy=map_head.map_yl/2-SCREEN_HEIGHT/2;
    map_data.map_tx=map_data.map_sx;
    map_data.map_ty=map_data.map_sy;
}

void    init_map_move(void)
{
    map_move.type = MAP_MOVE_STAY_CURRENT;
    map_move.move_speed = 1;
    map_move.dest_npc = 0;
}

void    set_map_move_to_position(SLONG dest_x, SLONG dest_y, SLONG move_speed)
{
    map_move.type = MAP_MOVE_TO_POSITION;
    map_move.dest_x = dest_x;
    map_move.dest_y = dest_y;
    map_move.move_speed = max(move_speed, 1);
}


void    set_map_move_follow_npc(SLONG npc_no)
{
    map_move.type = MAP_MOVE_FOLLOW_NPC;
    if(npc_no >= 0 && npc_no < MAX_CHARACTER_PER_ZONE)
    {
        map_move.dest_npc = npc_no;
    }
}


void    set_map_move_auto(void)
{
    map_move.type = MAP_MOVE_AUTO;
}


void    set_map_move_keep_range(SLONG flag)
{
    map_move.keep_range = flag;
}


void    adjust_map_move(void)
{
    SLONG   dx, dy;
    SLONG   tx, ty;
	SLONG	npc_x, npc_y, npc_z;

    switch(map_move.type)
    {
    case MAP_MOVE_STAY_CURRENT:
        break;
    case MAP_MOVE_TO_POSITION:
        dx = map_move.dest_x - map_data.map_sx;
        dy = map_move.dest_y - map_data.map_sy;
        map_data.map_sx += ZSGN(dx) * min(map_move.move_speed, abs(dx) % map_move.move_speed);
        map_data.map_sy += ZSGN(dy) * min(map_move.move_speed, abs(dy) % map_move.move_speed);
        break;
    case MAP_MOVE_FOLLOW_NPC:
        LOCK_CHARACTER(map_move.dest_npc);
		GetCharacterPosition(map_move.dest_npc, &npc_x, &npc_y, &npc_z);
        tx = npc_x - map_data.view_xl/2 - map_data.view_sx;
        ty = npc_y - npc_z - map_data.view_yl/2 - map_data.view_sy;
        UNLOCK_CHARACTER(map_move.dest_npc);
        map_data.map_sx = tx;
        map_data.map_sy = ty;
        /*
        if(map_data.map_sx < tx) map_data.map_sx ++;
        if(map_data.map_sx > tx) map_data.map_sx --;
        if(map_data.map_sy < ty) map_data.map_sy ++;
        if(map_data.map_sy > ty) map_data.map_sy --;
        */
        break;
    case MAP_MOVE_AUTO:
        map_data.map_sx += map_data.map_mx;
        map_data.map_sy += map_data.map_my;
        break;
    }

    if(map_move.keep_range)
    {
        if(map_data.map_sx < -map_data.view_sx)
            map_data.map_sx = -map_data.view_sx;
        if(map_data.map_sx > map_head.map_xl - map_data.view_xl - map_data.view_sx)
            map_data.map_sx = map_head.map_xl - map_data.view_xl - map_data.view_sx;
        if(map_data.map_sy < -map_data.view_sy)
            map_data.map_sy = -map_data.view_sy;
        if(map_data.map_sy > map_head.map_yl - map_data.view_yl - map_data.view_sy)
            map_data.map_sy = map_head.map_yl - map_data.view_yl - map_data.view_sy;
        /*
        if(map_data.map_sx < 0)
            map_data.map_sx = 0;
        if(map_data.map_sx > map_head.map_xl-SCREEN_WIDTH)
            map_data.map_sx = map_head.map_xl-SCREEN_WIDTH;
        if(map_data.map_sy < 0)
            map_data.map_sy = 0;
        if(map_data.map_sy > map_head.map_yl-SCREEN_HEIGHT)
            map_data.map_sy = map_head.map_yl-SCREEN_HEIGHT;
        */
    }
}


void    set_map_view_range(SLONG sx, SLONG sy, SLONG xl, SLONG yl)
{
    map_data.view_sx = sx;
    map_data.view_sy = sy;
    map_data.view_xl = xl;
    map_data.view_yl = yl;
}

/************************************************************************************************************/
/* OTHER MAP FUNCTIONS                                                                                      */
/************************************************************************************************************/
void    redraw_map_mask(SLONG map_sx, SLONG map_sy, MAP_MASK *mm, SLONG flags, void *vbitmap)
{
    BMP *bitmap = (BMP *)vbitmap;
    SLONG   mask_sx, mask_sy;
    SLONG   x, y, w;
    SLONG   disp_x, disp_y;
    UCHR    mask;
    SLONG   offset;
    SLONG   back_disp_x;

    mask_sx = (map_sx >= 0) ? map_sx / mm->sw : map_sx / mm->sw - 1;
    mask_sy = (map_sy >= 0) ? map_sy / mm->sh : map_sy / mm->sh - 1;

    disp_x = (mask_sx > 0) ? mask_sx * mm->sw - map_sx : - map_sx;
    disp_y = (mask_sy > 0) ? mask_sy * mm->sh - map_sy : - map_sy;
    back_disp_x = disp_x;

    offset = mask_sy * mm->w;
    if(offset < 0)
        offset = 0;
    for(y = (mask_sy > 0) ? mask_sy : 0; y < mm->h  && y < mask_sy + bitmap->h / mm->sh + 1; y++ )
    {
        w = (mask_sx > 0) ? mask_sx : 0;
        disp_x = back_disp_x;

        for(x = (mask_sx > 0) ? mask_sx : 0; x < mm->w && x < mask_sx + bitmap->w / mm->sw + 1; x++ )
        {
            mask = mm->data[offset+w];

            if(flags & MASK_SHOW_GRID)
            {
                put_box(disp_x, disp_y, mm->sw, mm->sh, SYSTEM_DARK1, bitmap);
            }
            if(flags & MASK_SHOW_STOP)
            {
                if(mask & MASK_STOP)
                {
                    put_box(disp_x, disp_y, mm->sw, mm->sh, SYSTEM_RED, bitmap);
                }
            }
            if(flags & MASK_SHOW_LO_MAGIC)
            {
                if(mask & MASK_LO_MAGIC)
                {
                    put_box(disp_x+2, disp_y+2, mm->sw-4, mm->sh-4, SYSTEM_BLUE, bitmap);
                }
            }
            if(flags & MASK_SHOW_MID_MAGIC)
            {
                if(mask & MASK_MID_MAGIC)
                {
                    put_box(disp_x+2, disp_y+2, mm->sw-4, mm->sh-4, SYSTEM_PINK, bitmap);
                }
            }
            if(flags & MASK_SHOW_HI_MAGIC)
            {
                if(mask & MASK_HI_MAGIC)
                {
                    put_box(disp_x+2, disp_y+2, mm->sw-4, mm->sh-4, SYSTEM_YELLOW, bitmap);
                }
            }
            disp_x += mm->sw;
            w ++;
        }
        disp_y += mm->sh;
        offset  += mm->w;
    }
}


void    redraw_map_proc_layer(SLONG map_sx,SLONG map_sy,SLONG flag,BMP *bmp)
{
    SLONG i;
    const SLONG draw_poly_flags = PDP_VALID | PDP_BASE | PDP_HEIGHT | PDP_ARRIS 
        | PDP_TOP | PDP_CROSS | PDP_PROJECTION;//| PDP_ZHEIGHT;

    if(!flag) return;
    for(i=0;i<map_proc_max;i++)
    {
        if(map_proc[i].id > 0)
        {
            D3_draw_poly(-map_sx, -map_sy, 0, draw_poly_flags, &map_proc[i].poly, bmp);
            //D2_fill_poly(map_sx, map_sy, &map_proc[i].poly,SYSTEM_BLUE,screen_buffer);

            sprintf((char *)print_rec,"~C0~O3%d~C0~O0~C4(%d)~C0",map_proc[i].id,map_proc[i].type);
            print16(map_proc[i].poly.bx-map_data.map_sx, map_proc[i].poly.by-map_data.map_sy,
                (USTR *)print_rec,PEST_PUT,bmp);
        }
    }
}

/************************************************************************************************************/
/* MAP SIMPLE OBJECT FUNCTIONS                                                                              */
/************************************************************************************************************/
//
// Simple map object is a standard library object, which managered by editor environment.
// Gernerally its image format is .cak, and it has only one frame.
// 
//
SLONG	add_map_simple_object(SLONG id, SLONG px, SLONG py, SLONG pz, SLONG effect, SLONG change_tick)
{
    SLONG index;

    index = get_usable_map_object();
    if(index >= 0)
    {
        map_object[index].flag = MOBJ_ACTIVE | MOBJ_SIMPLE;
        map_object[index].id = id;
        map_object[index].px = px;
        map_object[index].py = py;
        map_object[index].pz = pz;
        map_object[index].change_tick = change_tick;
        map_object[index].now_tick = 0;
        map_object[index].effect = effect;
		map_object[index].frame = 0;
        
        add_reference_for_map_object_image(id);

        if(index >= map_object_max)
            map_object_max = index + 1;
    }
    return index;
}


SLONG	del_map_simple_object(SLONG object_index)
{
	SLONG	id;

    if( object_index >= 0 && object_index < map_object_max )
    {
		id = map_object[object_index].id;
		if( id != INVALID_OBJECT_ID)
		{
			dec_reference_for_map_object_image(id);
		}
		map_object[object_index].flag = 0;
		map_object[object_index].id = INVALID_OBJECT_ID;
    }
    return TTN_OK;
}


void	draw_map_simple_object(SLONG object_index, SLONG flags, BMP *bitmap)
{
    SLONG   sx, sy;
    CAKE_FRAME_ANI *cfa = NULL;
    CAKE_FRAME *cf = NULL;

    if(! (map_object[object_index].flag & MOBJ_ACTIVE) )
		return;

    cfa = get_map_object_image(map_object[object_index].id, map_object[object_index].frame);
    if(cfa) cf=cfa->cake_frame;
    if(cf) 
	{ 
		RLE	*rle;
		rle = cf->rle; 
		if(rle)
		{
			// we suppose all frame's polys have the same barycenter position,
			// so the offset x/y is just the following values...
			sx = -cf->poly_rx + map_object[object_index].px - map_data.map_sx;
			sy = -cf->poly_ry + map_object[object_index].py - map_object[object_index].pz - map_data.map_sy;
			put_rle(sx,sy,rle,bitmap);
		}

		if(is_redraw_map_object_poly())
		{
			POLY *pl;
			pl = cf->poly;
			if(pl)
			{
				D3_draw_poly(map_object[object_index].px - map_data.map_sx,
					map_object[object_index].py - map_data.map_sy,
					map_object[object_index].pz, OBJECT_POLY_FLAGS, pl, bitmap);
			}
		}
	}
}


void	refresh_map_simple_object(SLONG object_index)
{
	//
	// Simple map object has only one frame. 
	// Now we just want to control frame refreshing, so do nothing here.
	//
}


SLONG	change_map_simple_object_id(SLONG object_index, SLONG new_id)
{
    if(map_object[object_index].id != new_id)
    {
        if(map_object[object_index].id != INVALID_OBJECT_ID)
            dec_reference_for_map_object_image(map_object[object_index].id);
        add_reference_for_map_object_image(new_id);

        map_object[object_index].id = new_id;
        map_object[object_index].frame = 0;
        map_object[object_index].now_tick = 0;

        return  TTN_OK;
    }
    return  TTN_NOT_OK;
}


SLONG	get_map_simple_object_information(SLONG object_index, SLONG *object_flag, SLONG *sx, SLONG *sy, 
										  SLONG *ex, SLONG *ey, POLY **poly)
{
    SLONG   flag, id, px, py, pz;
    SLONG   object_type;
	CAKE_FRAME_ANI *cfa = NULL;
	CAKE_FRAME  * cf = NULL;
	RLE*    rle = NULL;
	POLY*   pl = NULL;
	SLONG   ox, oy;

    flag = map_object[object_index].flag;
    id = map_object[object_index].id;
    px = map_object[object_index].px;
    py = map_object[object_index].py;
    pz = map_object[object_index].pz;
    object_type = flag & MOBJ_TYPES;

	if( id != INVALID_OBJECT_ID && flag )
	{
		cfa = get_map_object_image(id, map_object[object_index].frame);
		if(cfa) cf = cfa->cake_frame;
		if(cf) 
		{   
			rle = cf->rle;
			pl = cf->poly;
		}
		if(rle && pl)
		{
			// we suppose all frame's polys have the same barycenter position,
			// so the offset x/y is just the following values...
			ox = -cf->poly_rx;
			oy = -cf->poly_ry;
			
			*object_flag = flag;
			*sx = - map_data.map_sx + ox + px;
			*sy = - map_data.map_sy + oy + (py - pz);
			*ex = *sx + rle->w;
			*ey = *sy + rle->h;
			*poly = pl;
			
			return  TTN_OK;
		}
	}
	return  TTN_NOT_OK;
}


/************************************************************************************************************/
/* MAP DYNAMIC OBJECT FUNCTIONS                                                                             */
/************************************************************************************************************/
//
// Dynamic map object is standard library object. But it's not same as simple map object,
// It has more frames.
//
SLONG   add_map_dynamic_object(SLONG id, SLONG px, SLONG py, SLONG pz, SLONG effect, SLONG change_tick)
{
    SLONG index;

    index = get_usable_map_object();
    if(index >= 0)
    {
        map_object[index].flag = MOBJ_ACTIVE | MOBJ_DYNAMIC;
        map_object[index].id = id;
        map_object[index].px = px;
        map_object[index].py = py;
        map_object[index].pz = pz;
        map_object[index].change_tick = change_tick;
        map_object[index].now_tick = 0;
        map_object[index].effect = effect;
        map_object[index].frame = 0;
        
        add_reference_for_map_object_image(id);

        if(index >= map_object_max)
            map_object_max = index + 1;
    }
    return index;
}


SLONG	del_map_dynamic_object(SLONG object_index)
{
	SLONG	id;

    if( object_index >= 0 && object_index < map_object_max )
    {
		id = map_object[object_index].id;
		if( id != INVALID_OBJECT_ID)
		{
			dec_reference_for_map_object_image(id);
		}
		map_object[object_index].flag = 0;
		map_object[object_index].id = INVALID_OBJECT_ID;
    }
    return TTN_OK;
}


void	draw_map_dynamic_object(SLONG object_index, SLONG flags, BMP *bitmap)
{
    SLONG   sx, sy;
    CAKE_FRAME_ANI *cfa = NULL;
    CAKE_FRAME *cf = NULL;

    if(! (map_object[object_index].flag & MOBJ_ACTIVE) )
		return;

    cfa = get_map_object_image(map_object[object_index].id, map_object[object_index].frame);
    if(cfa) cf=cfa->cake_frame;
    if(cf) 
	{ 
		RLE *rle;
		rle = cf->rle;
		if(rle)
		{
			// we suppose all frame's polys have the same barycenter position,
			// so the offset x/y is just the following values...
			sx = -cf->poly_rx + map_object[object_index].px - map_data.map_sx;
			sy = -cf->poly_ry + map_object[object_index].py - map_object[object_index].pz - map_data.map_sy;
			put_rle(sx,sy,rle,bitmap);
		}

		if(is_redraw_map_object_poly())
		{
			POLY *pl;
			pl = cf->poly;
			if(pl)
			{
				D3_draw_poly(map_object[object_index].px - map_data.map_sx,
					map_object[object_index].py - map_data.map_sy,
					map_object[object_index].pz, OBJECT_POLY_FLAGS, pl, bitmap);
			}
		}
	}
}


void	refresh_map_dynamic_object(SLONG object_index)
{
	SLONG	flag;

	flag = map_object[object_index].flag;
	if(! (flag & MOBJ_ACTIVE))
		return;

	//
	// Dynamic map object has multi-frames, the processing here is refreshing frame.
	//
	map_object[object_index].now_tick++;
	if(map_object[object_index].now_tick > map_object[object_index].change_tick)
	{
		map_object[object_index].frame++;
		if(map_object[object_index].frame >= GetObjectImageTotalFrames(map_object[object_index].id))
			map_object[object_index].frame=0;
		map_object[object_index].now_tick=0;
	}
}


SLONG	change_map_dynamic_object_id(SLONG object_index, SLONG new_id)
{
    if(map_object[object_index].id != new_id)
    {
        if(map_object[object_index].id != INVALID_OBJECT_ID)
            dec_reference_for_map_object_image(map_object[object_index].id);
        add_reference_for_map_object_image(new_id);

        map_object[object_index].id = new_id;
        map_object[object_index].frame = 0;
        map_object[object_index].now_tick = 0;

        return  TTN_OK;
    }
    return  TTN_NOT_OK;
}


SLONG	get_map_dynamic_object_information(SLONG object_index, SLONG *object_flag, SLONG *sx, SLONG *sy, 
										   SLONG *ex, SLONG *ey, POLY **poly)
{
    SLONG   flag, id, px, py, pz;
    SLONG   object_type;
	CAKE_FRAME_ANI *cfa = NULL;
	CAKE_FRAME  * cf = NULL;
	RLE*    rle = NULL;
	POLY*   pl = NULL;
	SLONG   ox, oy;

    flag = map_object[object_index].flag;
    id = map_object[object_index].id;
    px = map_object[object_index].px;
    py = map_object[object_index].py;
    pz = map_object[object_index].pz;
    object_type = flag & MOBJ_TYPES;

	if( id != INVALID_OBJECT_ID && flag )
	{
		cfa = get_map_object_image(id, map_object[object_index].frame);
		if(cfa) cf = cfa->cake_frame;
		if(cf) 
		{   
			rle = cf->rle;
			pl = cf->poly;
		}
		if(rle && pl)
		{
			// we suppose all frame's polys have the same barycenter position,
			// so the offset x/y is just the following values...
			ox = -cf->poly_rx;
			oy = -cf->poly_ry;
			
			*object_flag = flag;
			*sx = - map_data.map_sx + ox + px;
			*sy = - map_data.map_sy + oy + (py - pz);
			*ex = *sx + rle->w;
			*ey = *sy + rle->h;
			*poly = pl;
			
			return  TTN_OK;
		}
	}
	return  TTN_NOT_OK;
}


/************************************************************************************************************/
/* MAP FIXED OBJECT FUNCTIONS                                                                               */
/************************************************************************************************************/
//
// Fixed map object is the object which saved in the map file.
// In the engine, there is one kind of map whose source image file format is PSD(photoshop file).
//
// Relations between source image file PSD and destination file MAP are list as following:
// 
//		Photoshop PSD file	|	Game MAP file
//      --------------------+----------------------------------------------------
//		Layer 0				|	Map upper layer(as scene background)
//      --------------------+----------------------------------------------------
//		Layer 1...Layer n	|	Map fixed object
//      --------------------------------------------------------------------------
//
// The fixed map object images are saved in the game map file.
// When we load game map file, we will load the fixed map object images to memory too.
// For manager these kind of images by id, we call a function to register the image to our 
// standard object library manager.
//
//
SLONG   add_map_fixed_object(SLONG id,SLONG px,SLONG py,SLONG pz,SLONG effect,SLONG change_tick)
{
    SLONG index;

    index = get_usable_map_object();
    if(index >= 0)
    {
        map_object[index].flag = MOBJ_ACTIVE | MOBJ_FIXED ;
        map_object[index].id = id;
        map_object[index].px = px;
        map_object[index].py = py;
        map_object[index].pz = pz;
        map_object[index].change_tick = change_tick;
        map_object[index].now_tick = 0;
        map_object[index].effect = effect;
        map_object[index].frame = 0;
        //
        if(index >= map_object_max)
            map_object_max = index+1;
    }
    return index;
}


SLONG	del_map_fixed_object(SLONG object_index)
{
	SLONG	id;

    if( object_index >= 0 && object_index < map_object_max )
    {
		id = map_object[object_index].id;
		if( id != INVALID_OBJECT_ID)
		{
			dec_reference_for_map_object_image(id);
		}
		map_object[object_index].flag = 0;
		map_object[object_index].id = INVALID_OBJECT_ID;
    }
    return TTN_OK;
}

void	draw_map_fixed_object(SLONG object_index, SLONG flags, BMP *bitmap)
{
    SLONG   sx, sy;
    CAKE_FRAME_ANI *cfa = NULL;
    CAKE_FRAME *cf = NULL;

    if(! (map_object[object_index].flag & MOBJ_ACTIVE) )
		return;

    cfa = get_map_object_image(map_object[object_index].id, map_object[object_index].frame);
    if(cfa) cf=cfa->cake_frame;
    if(cf) 
	{ 
		RLE *rle;
		rle = cf->rle;
		if(rle)
		{
			// we suppose all frame's polys have the same barycenter position,
			// so the offset x/y is just the following values...
			sx = -cf->poly_rx + map_object[object_index].px - map_data.map_sx;
			sy = -cf->poly_ry + map_object[object_index].py - map_object[object_index].pz - map_data.map_sy;
			put_rle(sx,sy,rle,bitmap);
		}

		if(is_redraw_map_object_poly())
		{
			POLY *pl;
			pl = cf->poly;
			if(pl)
			{
				D3_draw_poly(map_object[object_index].px - map_data.map_sx,
					map_object[object_index].py - map_data.map_sy,
					map_object[object_index].pz, OBJECT_POLY_FLAGS, pl, bitmap);
			}
		}
	}
}

void	refresh_map_fixed_object(SLONG object_index)
{
	//
	// Fixed map object has only one frame. 
	// Now we just want to control frame refreshing, so do nothing here.
	//
}

SLONG	change_map_fixed_object_id(SLONG object_index, SLONG new_id)
{
    if(map_object[object_index].id != new_id)
    {
        if(map_object[object_index].id != INVALID_OBJECT_ID)
            dec_reference_for_map_object_image(map_object[object_index].id);
        add_reference_for_map_object_image(new_id);

        map_object[object_index].id = new_id;
        map_object[object_index].frame = 0;
        map_object[object_index].now_tick = 0;

        return  TTN_OK;
    }
    return  TTN_NOT_OK;
}

SLONG	get_map_fixed_object_information(SLONG object_index, SLONG *object_flag, SLONG *sx, SLONG *sy, 
										 SLONG *ex, SLONG *ey, POLY **poly)
{
    SLONG   flag, id, px, py, pz;
    SLONG   object_type;
	CAKE_FRAME_ANI *cfa = NULL;
	CAKE_FRAME  * cf = NULL;
	RLE*    rle = NULL;
	POLY*   pl = NULL;
	SLONG   ox, oy;

    flag = map_object[object_index].flag;
    id = map_object[object_index].id;
    px = map_object[object_index].px;
    py = map_object[object_index].py;
    pz = map_object[object_index].pz;
    object_type = flag & MOBJ_TYPES;

	if( id != INVALID_OBJECT_ID && flag )
	{
		cfa = get_map_object_image(id, map_object[object_index].frame);
		if(cfa) cf = cfa->cake_frame;
		if(cf) 
		{   
			rle = cf->rle;
			pl = cf->poly;
		}
		if(rle && pl)
		{
			// we suppose all frame's polys have the same barycenter position,
			// so the offset x/y is just the following values...
			ox = -cf->poly_rx;
			oy = -cf->poly_ry;
			
			*object_flag = flag;
			*sx = - map_data.map_sx + ox + px;
			*sy = - map_data.map_sy + oy + (py - pz);
			*ex = *sx + rle->w;
			*ey = *sy + rle->h;
			*poly = pl;
			
			return  TTN_OK;
		}
	}
	return  TTN_NOT_OK;
}


/************************************************************************************************************/
/* MAP HOUSE OBJECT FUNCTIONS                                                                               */
/************************************************************************************************************/
//
// House objects are the with-mask objects which under the house roof and on the house floor, as same as
// tables, desks, walls, etc.
// We use house set to manager house images, so in the map object systems, we just access the datas,
// exclude the images.
// A house object has only one frame, formatted as cak.
//
// In this version of map, we saved not only the map_house data, but also each house object and house roof.
// Later when we develop the newest version, we can save the map_house data only, and when we loading
// game map, we can dynamically add house objects and house roof to map object queue, just as the processing
// in the map editor.
//
SLONG   add_map_house_object(SLONG id, SLONG px, SLONG py, SLONG pz, SLONG effect, SLONG reserved)
{
    SLONG index;

    index = get_usable_map_object();
    if(index >= 0)
    {
        map_object[index].flag = MOBJ_ACTIVE | MOBJ_HOUSE_OBJECT;
        map_object[index].id = id;
        map_object[index].px = px;
        map_object[index].py = py;
        map_object[index].pz = pz;
        map_object[index].effect = effect;
        map_object[index].frame = 0;
        map_object[index].update_alpha = 0;
        map_object[index].alpha = 255;

        if(index >= map_object_max)
            map_object_max = index + 1;
    }
            
    return index;
}


SLONG	del_map_house_object(SLONG object_index)
{
    if( object_index >= 0 && object_index < map_object_max )
    {
		//only clear data, we will free image memory at other place.
		map_object[object_index].flag = 0;
		map_object[object_index].id = INVALID_OBJECT_ID;
	}
	return	TTN_OK;
}

void    draw_map_house_object(SLONG object_index, SLONG flags, BMP *bitmap)
{
    HOUSE_OBJECT * house_object = NULL;
    RLE *   rle = NULL;
    SLONG   id, sx, sy;
    SLONG   house_index, house_no, house_object_index;

    id = map_object[object_index].id;
    house_index = GET_HOUSE_INDEX(id);
    house_object_index = GET_HOUSE_OBJECT_INDEX(id);
    house_no = map_house[house_index].no;
    house_object = get_house_object(house_no, house_object_index);
	if(house_object)
	{
		rle = house_object->rle;
		if(rle)
		{
			sx = map_object[object_index].px - map_data.map_sx + house_object->fx;
			sy = map_object[object_index].py - map_object[object_index].pz - map_data.map_sy + house_object->fy;
			
			put_rle(sx,sy,rle,bitmap);
		}
		
		if(is_redraw_map_object_poly())
		{
			POLY *pl;
			pl = house_object->poly;
			if(pl)
			{
				D3_draw_poly(map_object[object_index].px - map_data.map_sx,
					map_object[object_index].py - map_data.map_sy,
					map_object[object_index].pz, OBJECT_POLY_FLAGS, pl, bitmap);
			}
		}
	}
}

void	refresh_map_house_object(SLONG object_index)
{
	// Need do nothing here.
}

SLONG	change_map_house_object_id(SLONG object_index, SLONG new_id)
{
	map_object[object_index].id = new_id;
    return  TTN_OK;
}


SLONG	get_map_house_object_information(SLONG object_index, SLONG *object_flag, SLONG *sx, SLONG *sy, 
										 SLONG *ex, SLONG *ey, POLY **poly)
{
    SLONG   flag, id, px, py, pz;
	HOUSE_OBJECT *house_object = NULL;
	SLONG   house_index, house_no, house_object_index;

    flag = map_object[object_index].flag;
    id = map_object[object_index].id;
    px = map_object[object_index].px;
    py = map_object[object_index].py;
    pz = map_object[object_index].pz;
            
	house_index = GET_HOUSE_INDEX(id);;
	house_object_index = GET_HOUSE_OBJECT_INDEX(id);
	house_no = map_house[house_index].no;
	house_object = get_house_object(house_no, house_object_index);
	if(house_object)
	{
		*object_flag = flag;
		*sx = -map_data.map_sx + px + house_object->fx;
		*sy = -map_data.map_sy + (py - pz) + house_object->fy;
		*ex = *sx + house_object->rle->w;
		*ey = *sy + house_object->rle->h;
		*poly = house_object->poly;

		return	TTN_OK;
	}

	return	TTN_NOT_OK;
}


/************************************************************************************************************/
/* MAP HOUSE ROOF FUNCTIONS                                                                                 */
/************************************************************************************************************/
//
// House roof is the cover of the house, which has the format of rla(rle array).
// The image of the house roof object is managed by house set manager.
//
SLONG   add_map_house_roof(SLONG id, SLONG px, SLONG py, SLONG pz, SLONG effect, SLONG reserved)
{
    SLONG index;

    index = get_usable_map_object();
    if(index >= 0)
    {
        map_object[index].flag = MOBJ_ACTIVE | MOBJ_HOUSE_ROOF;
        map_object[index].id = id;
        map_object[index].px = px;
        map_object[index].py = py;
        map_object[index].pz = pz;
        map_object[index].effect = effect;
        map_object[index].frame = 0;
        map_object[index].update_alpha = 0;
        map_object[index].alpha = 255;

        if(index >= map_object_max)
            map_object_max = index + 1;
    }
    return index;
}

SLONG	del_map_house_roof(SLONG object_index)
{
    if( object_index >= 0 && object_index < map_object_max )
    {
		//only clear data, we will free image memory at other place.
		map_object[object_index].flag = 0;
		map_object[object_index].id = INVALID_OBJECT_ID;
	}
	return	TTN_OK;
}

void	draw_map_house_roof(SLONG object_index, SLONG flags, BMP *bitmap)
{
    HOUSE_ROOF * house_roof = NULL;
    RLA *   rla = NULL;
    SLONG   id, sx, sy, house_index, house_no, alpha;

    id = map_object[object_index].id;
    house_index = GET_HOUSE_INDEX(id);
    house_no = map_house[house_index].no;
    house_roof = get_house_roof(house_no);
	if(house_roof)
	{
		rla = house_roof->rla;
		if(rla)
		{
			sx = map_object[object_index].px - map_data.map_sx + house_roof->fx;
			sy = map_object[object_index].py - map_object[object_index].pz - map_data.map_sy + house_roof->fy;
			
			alpha = map_object[object_index].alpha;
			switch(alpha)
			{
			case 0x00:
				break;
			case 0xff:
				put_rla(sx, sy, rla, bitmap);
				break;
			default:
				alpha_put_rla(sx, sy, rla, bitmap, alpha);
				break;
			}
		}

		if(is_redraw_map_object_poly())
		{
			POLY *pl;
			pl = house_roof->poly;
			if(pl)
			{
				D3_draw_poly(map_object[object_index].px - map_data.map_sx,
					map_object[object_index].py - map_data.map_sy,
					map_object[object_index].pz, OBJECT_POLY_FLAGS, pl, bitmap);
			}
		}
	}
}

void	refresh_map_house_roof(SLONG object_index)
{
    SLONG update_alpha;

	update_alpha = map_object[object_index].update_alpha;
	if(update_alpha > 0)
	{
		map_object[object_index].alpha += 32;
		if(map_object[object_index].alpha >= 255)
			map_object[object_index].alpha = 255;
	}
	else if(update_alpha < 0)
	{
		map_object[object_index].alpha -= 32;
		if(map_object[object_index].alpha <= 0)
			map_object[object_index].alpha = 0;
	}
}

SLONG	change_map_house_roof_id(SLONG object_index, SLONG new_id)
{
	map_object[object_index].id = new_id;
	map_object[object_index].frame = 0;
	map_object[object_index].update_alpha = 0;
	map_object[object_index].alpha = 255;
    return  TTN_OK;
}


SLONG	get_map_house_roof_information(SLONG object_index, SLONG *object_flag, SLONG *sx, SLONG *sy, 
									   SLONG *ex, SLONG *ey, POLY **poly)
{
    SLONG   flag, id, px, py, pz;
    SLONG   object_type;
	HOUSE_ROOF *house_roof = NULL;
	SLONG   house_index, house_no;

    flag = map_object[object_index].flag;
    id = map_object[object_index].id;
    px = map_object[object_index].px;
    py = map_object[object_index].py;
    pz = map_object[object_index].pz;
    object_type = flag & MOBJ_TYPES;

	house_index = GET_HOUSE_INDEX(id);
	house_no = map_house[house_index].no;
	house_roof = get_house_roof(house_no);
	if(house_roof)
	{
		*object_flag = flag;
		*sx = -map_data.map_sx + px + house_roof->fx;
		*sy = -map_data.map_sy + (py - pz) + house_roof->fy;
		*ex = *sx + house_roof->rla->w;
		*ey = *sy + house_roof->rla->h;
		*poly = house_roof->poly;
		
		return  TTN_OK;
	}

	return	TTN_NOT_OK;
}



/************************************************************************************************************/
/* MAP REDRAW SET FUNCTIONS                                                                                 */
/************************************************************************************************************/
SLONG	is_redraw_map_object_poly(void)
{
	return	map_data.redraw_flags & REDRAW_MAP_OBJECT_POLY ? TRUE : FALSE;
}

void	set_redraw_map_object_poly(SLONG flag)
{
	if(flag)
		map_data.redraw_flags |= REDRAW_MAP_OBJECT_POLY;
	else
		map_data.redraw_flags &= ~REDRAW_MAP_OBJECT_POLY;
}

