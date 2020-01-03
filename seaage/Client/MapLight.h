/*
**	maplight.h
**	map light functions header.
**
**	Jack, 2001.12.25.
*/
#ifndef	_MAPLIGHT_H_
#define	_MAPLIGHT_H_
#include "mainfun.h"


//DEFINES ---------------------------------------------------------------------------------------------
//
#define	LIGHT_TILE_WIDTH				8
#define	LIGHT_TILE_HEIGHT				4
#define	SCREEN_WIDTH_LIGHT_TILES		(SCREEN_WIDTH / LIGHT_TILE_WIDTH)
#define	SCREEN_HEIGHT_LIGHT_TILES		(SCREEN_HEIGHT / LIGHT_TILE_HEIGHT)


typedef	union	tagLIGHT_VALUE
{
	struct
	{
		UCHR	l;		//亮度(lum)
		UCHR	r;		//紅色分量
		UCHR	g;		//綠色分量
		UCHR	b;		//藍色分量
	};
	ULONG		u;		//總量
} LIGHT_VALUE, *LPLIGHT_VALUE;

typedef	struct	tagTILE_LIGHT
{
	SLONG	w;			//光影寬度(格)
	SLONG	h;			//光影高度(格)
	LIGHT_VALUE	*v[1];	//光影值
} TILE_LIGHT, *LPTILE_LIGHT;


//GLOBALS ---------------------------------------------------------------------------------------------
//
extern	TILE_LIGHT	*screen_light;


//FUNCTIONS -------------------------------------------------------------------------------------------
//
int		init_map_light_system(void);
void	free_map_light_system(void);
//
TILE_LIGHT *	create_tile_light( SLONG pixel_w, SLONG pixel_h );
TILE_LIGHT *	make_ellipse_tile_light( SLONG pixel_ra, SLONG pixel_rb, LIGHT_VALUE center_lv, LIGHT_VALUE side_lv );
void	destroy_tile_light( TILE_LIGHT **tl );
void	clear_tile_light( TILE_LIGHT *tl );
void	fill_tile_light( TILE_LIGHT *tl, LIGHT_VALUE lv );
void	fill_tile_light_lum( TILE_LIGHT *tl, UCHR lum );
void	shine_light( TILE_LIGHT *tl, SLONG sx, SLONG sy, SLONG xl, SLONG yl, LIGHT_VALUE v);
void	ellipse_tile_light( TILE_LIGHT *tl, LIGHT_VALUE center_lv, LIGHT_VALUE side_lv );
void	put_tile_light(SLONG pixel_cx, SLONG pixel_cy, TILE_LIGHT *src, TILE_LIGHT *dest);
void	blur_tile_light( TILE_LIGHT *tl );
SLONG	load_tile_light( USTR* filename, TILE_LIGHT **tl );
void	put_light_tile(LIGHT_VALUE *v, SLONG sx, SLONG sy, BMP *bitmap);
void	redraw_tile_light( TILE_LIGHT *tl, BMP *vbitmap );
//
void	merge_light_value( LIGHT_VALUE *src_lv, LIGHT_VALUE *dest_lv );


#endif//_MAPLIGHT_H_
