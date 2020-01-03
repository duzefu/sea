/*
**  sge.cpp
**  specially good effect functions.
**
**  zjian,2001.5.28.
*/
#include "MainFun.h"
#include "NetGE_MainFunc.h"
#include "npc.h"
#include "magic.h"
#include "sge.h"
#include "maplight.h"


#define SGE_INIT            0x01

#define SGE_TIME_PERIOD     300


//globals ------------------------------------------------------------------------------------------------------
TILE_LIGHT*	screen_light = NULL;
TILE_LIGHT*	npc_light = NULL;
TILE_LIGHT*	magic_light = NULL;
SGE         game_sge;

//locals -------------------------------------------------------------------------------------------------------
static  DWORD   dwSGE = 0;
//
static  UCHR    oneday_light[24 * 8]=
{   0,  0,  0,  0,  0,  0,  0,  0,  // night
    0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,
        
    0,  1,  2,  3,  4,  5,  6,  7,  // night -> day  
    8,  9,  10, 11, 12, 13, 14, 15, //
    16, 17, 18, 19, 20, 21, 22, 23, //
    24, 25, 26, 27, 28, 29, 30, 31, //
        
    31, 31, 31, 31, 31, 31, 31, 31, // day
    31, 31, 31, 31, 31, 31, 31, 31,
    31, 31, 31, 31, 31, 31, 31, 31,
    31, 31, 31, 31, 31, 31, 31, 31,
    31, 31, 31, 31, 31, 31, 31, 31,
    31, 31, 31, 31, 31, 31, 31, 31,
    31, 31, 31, 31, 31, 31, 31, 31,
    31, 31, 31, 31, 31, 31, 31, 31,
        
    31, 30, 29, 28, 27, 26, 25, 24, // day - > night
    23, 22, 21, 20, 19, 18, 17, 16, //
    15, 14, 13, 12, 11, 10, 9,  8,  //
    7,  6,  5,  4,  3,  2,  1,  0   //
};


//functions ----------------------------------------------------------------------------------------------------
int     init_sge(void)
{
	LIGHT_VALUE	center_lv, side_lv;

	if(NULL == (screen_light = create_tile_light( SCREEN_WIDTH, SCREEN_HEIGHT ) ) )
		return	-1;
	clear_tile_light(screen_light);

	center_lv.r = 0;
	center_lv.g = 0;
	center_lv.b = 0;
	center_lv.l = 255;
	side_lv.r = 0;
	side_lv.g = 0;
	side_lv.b = 0;
	side_lv.l = 0;
	if(NULL == (npc_light = make_ellipse_tile_light( SCREEN_WIDTH / 3, SCREEN_HEIGHT / 3, 
		center_lv, side_lv ) ) )
		return	-2;
	if(NULL == (magic_light = make_ellipse_tile_light( SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4,
		center_lv, side_lv ) ) )
		return	-3;

    game_sge.day = 0;
    game_sge.time = 0;	//24 * 8 / 2;
    timer_tick07 = 0;

    dwSGE |= SGE_INIT;

    return  0;
}



void    active_sge(int active)
{
    if(! (dwSGE & SGE_INIT) )
        return;
	//
	return;
}


void    free_sge(void)
{
    if(! (dwSGE & SGE_INIT) )
        return;

    //(1) destroy light --------------------
	destroy_tile_light( &screen_light );
    destroy_tile_light( &npc_light );
    destroy_tile_light( &magic_light );

    dwSGE = 0;

	return;
}


void    refresh_sge(void)
{
    if(! (dwSGE & SGE_INIT) )
        return;

	blur_tile_light(screen_light);

    if(timer_tick07 > SGE_TIME_PERIOD)
    {
        game_sge.time ++;
        if(game_sge.time > 24 * 8 - 1)
        {
            game_sge.day ++;
            game_sge.time = 0;
        }
        timer_tick07 = 0;
    }
}


void    sge_show_light(SLONG mx, SLONG my, void *vbitmap)
{
	SLONG	map_no = 0;
    BMP     *bitmap = (BMP*)vbitmap;
    SLONG   npc_no, npc_x, npc_y, npc_z;
    SLONG   p, x, y, z;
	LIGHT_VALUE	npc_lv, magic_lv;
    SLONG   flag, sleep_tick;

    if(! (dwSGE & SGE_INIT) )
        return;

	npc_lv.r = 255;
	npc_lv.g = 0;
	npc_lv.b = 0;
	npc_lv.l = 0;
	magic_lv.r = 255;
	magic_lv.g = 200;
	magic_lv.b = 0;
	magic_lv.l = 0;

	fill_tile_light_lum( screen_light, oneday_light[game_sge.time] * 8 );

    for(npc_no = 0; npc_no < game_npc_max; npc_no ++)
    {
        LOCK_CHARACTER(npc_no);
        flag  = get_npc_flag(npc_no);
        UNLOCK_CHARACTER(npc_no);

        if(flag & NPC_USED)
        {
            LOCK_CHARACTER(npc_no);
			GetCharacterPosition(npc_no, &npc_x, &npc_y, &npc_z);
            UNLOCK_CHARACTER(npc_no);

            //range_put_light( npc_x - map_data.map_sx, npc_y - npc_z - map_data.map_sy, full_light, npc_light);
			//shine_light( screen_light, npc_x - map_data.map_sx - 120, npc_y - npc_z - map_data.map_sy - 60,
			//	240, 120, npc_lv);
			put_tile_light( npc_x - map_data.map_sx, npc_y - npc_z - map_data.map_sy, npc_light, screen_light);
        }
    }

    LOCK_MAGIC(map_no);
    p = GetZoneMagicPartNext(map_no);
    while(p != map_no)
    {
		flag = GetZoneMagicPartFlag(p);
        if(flag)
        {
			sleep_tick = GetZoneMagicPartSleepTick(p);
            if(sleep_tick <= 0)
            {
				GetZoneMagicPartCurrPosition(p, &x, &y, &z);

                //range_put_light(x - map_data.map_sx, y - z - map_data.map_sy, full_light, mouse_light);
				//shine_light(screen_light, x - map_data.map_sx - 80, y - z - map_data.map_sy - 40, 160, 80, magic_lv);
				put_tile_light(x - map_data.map_sx, y - z - map_data.map_sy, magic_light, screen_light);
            }
        }

        // ready for the next.
        p = GetZoneMagicPartNext(p);
    }
    UNLOCK_MAGIC(map_no);

	redraw_tile_light(screen_light, bitmap);

	return;
}


void    clear_screen_light(void)
{
	fill_tile_light_lum( screen_light, oneday_light[game_sge.time] * 8 );
}


void    add_npc_light(SLONG npc_x, SLONG npc_y, SLONG npc_z)
{
    put_tile_light( npc_x - map_data.map_sx, npc_y - npc_z - map_data.map_sy, npc_light, screen_light);
}


void    add_magic_light(SLONG magic_x, SLONG magic_y, SLONG magic_z)
{
    put_tile_light(magic_x - map_data.map_sx, magic_y - magic_z - map_data.map_sy, magic_light, screen_light);
}


void    redraw_screen_light(void *vbitmap)
{
    BMP *bitmap = (BMP*)vbitmap;

	redraw_tile_light(screen_light, bitmap);
}


