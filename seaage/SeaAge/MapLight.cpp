/*
**	maplight.cpp
**	map light functions.
**
**	Jack, 2001.12.25.
*/
#include "mainfun.h"
#include "maplight.h"


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FUNCTIONS
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
int		init_map_light_system(void)
{
	return	0;
}


void	free_map_light_system(void)
{
	return;
}


TILE_LIGHT *	create_tile_light( SLONG pixel_w, SLONG pixel_h )
{
	TILE_LIGHT *tmp = NULL;
	LIGHT_VALUE *p = NULL;
	SLONG	w, h;
	SLONG	size, y;

	w = pixel_w / LIGHT_TILE_WIDTH;
	h = pixel_h / LIGHT_TILE_HEIGHT;
	size = sizeof(TILE_LIGHT) + (h-1) * sizeof(LIGHT_VALUE *) + w * h * sizeof(LIGHT_VALUE);
	if(NULL == (tmp = (TILE_LIGHT *)GlobalAlloc( GPTR, size ) ) )
		return	NULL;
	tmp->w = w;
	tmp->h = h;
    p = tmp->v[0] = (LIGHT_VALUE *)((char *)tmp + sizeof(TILE_LIGHT) + (h-1)*sizeof(LIGHT_VALUE *) );
	for(y = 1; y < h; y ++)
	{
		tmp->v[y] = (p += w);
	}

	return	tmp;
}


TILE_LIGHT *	make_ellipse_tile_light( SLONG pixel_ra, SLONG pixel_rb, LIGHT_VALUE center_lv, LIGHT_VALUE side_lv )
{
	TILE_LIGHT	*tl = NULL;

	if(NULL == (tl = create_tile_light( pixel_ra * 2, pixel_rb * 2 ) ) )
		return	NULL;
	fill_tile_light( tl, side_lv );
	ellipse_tile_light( tl, center_lv, side_lv );

	return	tl;
}


void	fill_tile_light( TILE_LIGHT *tl, LIGHT_VALUE lv )
{
	SLONG	x, y;

	for(y = 0; y < tl->h; y ++)
	{
		for(x = 0; x < tl->w; x ++)
		{
			tl->v[y][x].u = lv.u;
		}
	}
	return;
}


void	ellipse_tile_light( TILE_LIGHT *tl, LIGHT_VALUE center_lv, LIGHT_VALUE side_lv )
{
	SLONG	x, y;
	SLONG	rx, ry, ra, rb;
	double	ra2, rb2;
	double	k;

	ra = tl->w / 2;
	rb = tl->h / 2;
	ra2 = ra * ra;
	rb2 = rb * rb;
	for(y = 0; y < tl->h; y ++)
	{
		ry = y - rb;
		for(x = 0; x < tl->w; x ++)
		{
			rx = x - ra;
			k = sqrt( rx * rx / ra2 + ry * ry / rb2 );
			if(k > 1.0)
			{
				tl->v[y][x].u = side_lv.u;
			}
			else
			{
				tl->v[y][x].r = (UCHR)( center_lv.r + side_lv.r * k - center_lv.r * k );
				tl->v[y][x].g = (UCHR)( center_lv.g + side_lv.g * k - center_lv.g * k );
				tl->v[y][x].b = (UCHR)( center_lv.b + side_lv.b * k - center_lv.b * k );
				tl->v[y][x].l = (UCHR)( center_lv.l + side_lv.l * k - center_lv.l * k );
			}
		}
	}

	return;
}


void	merge_light_value( LIGHT_VALUE *sv, LIGHT_VALUE *dv )
{
	SLONG	r, g, b, l;

	r = sv->r + dv->r - (sv->r * dv->r) / 255;
	if(r > 255) r = 255;
	g = sv->g + dv->g - (sv->g * dv->g) / 255;
	if(g > 255) g = 255;
	b = sv->b + dv->b - (sv->b * dv->b) / 255;
	if(b > 255) b = 255;
	l = sv->l + dv->l - (sv->l * dv->l) / 255;
	if(l > 255) l = 255;

	dv->r = (UCHR)r;
	dv->g = (UCHR)g;
	dv->b = (UCHR)b;
	dv->l = (UCHR)l;
}



void	put_tile_light(SLONG pixel_cx, SLONG pixel_cy, TILE_LIGHT *src, TILE_LIGHT *dest)
{
	SLONG	cx, cy;
	SLONG	sx, sy;
    SLONG	over_xl,over_yl;
    SLONG	des_sx,des_sy;
    SLONG	src_sx,src_sy;
    SLONG	x, y;

	cx = pixel_cx / LIGHT_TILE_WIDTH;
	cy = pixel_cy / LIGHT_TILE_HEIGHT;
	sx = cx - src->w / 2;
	sy = cy - src->h / 2;
    des_sx = MAX(sx,0);
    des_sy = MAX(sy,0);
    over_xl = MIN(sx + src->w, dest->w) - des_sx;
    over_yl = MIN(sy + src->h, dest->h) - des_sy;
    if(over_yl<=0 || over_xl<=0)
        return;
    src_sx = MAX(-sx, 0);
    src_sy = MAX(-sy, 0);
    for(y=0;y<over_yl;y++)
    {
        for(x=0;x<over_xl;x++)
        {
			merge_light_value( &src->v[src_sy + y][src_sx + x], &dest->v[des_sy + y][des_sx + x] );
        }
    }
	return;
}


void	destroy_tile_light( TILE_LIGHT **tl )
{
	if(*tl)
	{
		GlobalFree(*tl);
		*tl = NULL;
	}
	return;
}


void	clear_tile_light( TILE_LIGHT *tl )
{
	SLONG	w, h;

	for(h = 0; h < tl->h; h ++)
	{
		for(w = 0; w < tl->w; w ++)
		{
			tl->v[h][w].u = 0;
		}
	}
	//memset( tl->v[0], 0, sizeof(LIGHT_VALUE) * tl->w * tl->h );
	return;
}


void	fill_tile_light_lum( TILE_LIGHT *tl, UCHR lum )
{
	SLONG	w, h;

	for(h = 0; h < tl->h; h ++)
	{
		for(w = 0; w < tl->w; w ++)
		{
			tl->v[h][w].l = lum;
		}
	}
	return;
}



void	shine_light( TILE_LIGHT *tl, SLONG pixel_sx, SLONG pixel_sy, SLONG pixel_xl, SLONG pixel_yl, LIGHT_VALUE v)
{
	SLONG	sx, sy;
	SLONG	ex, ey;
	SLONG	x, y;
	SLONG	r, g, b, l;

	sx = (pixel_sx + LIGHT_TILE_WIDTH / 2) / LIGHT_TILE_WIDTH;
	sy = (pixel_sy + LIGHT_TILE_HEIGHT / 2) / LIGHT_TILE_HEIGHT;
	ex = (pixel_sx + pixel_xl + LIGHT_TILE_WIDTH / 2) / LIGHT_TILE_WIDTH;
	ey = (pixel_sy + pixel_yl + LIGHT_TILE_HEIGHT / 2) / LIGHT_TILE_HEIGHT;
	if(sx < 0) sx = 0;
	if(sy < 0) sy = 0;
	if(ex > tl->w) ex = tl->w;
	if(ey > tl->h) ey = tl->h;
	for( y = sy; y < ey; y ++)
	{
		for(x = sx; x < ex; x ++)
		{
			r = tl->v[y][x].r + v.r;
			if(r > 255) r = 255;
			g = tl->v[y][x].g + v.g;
			if(g > 255) g = 255;
			b = tl->v[y][x].b + v.b;
			if(b > 255) b = 255;
			l = tl->v[y][x].l + v.l;
			if(l > 255) l = 255;
			tl->v[y][x].r = (UCHR)r;
			tl->v[y][x].g = (UCHR)g;
			tl->v[y][x].b = (UCHR)b;
			tl->v[y][x].l = (UCHR)l;
		}
	}
	return;
}



void	blur_tile_light( TILE_LIGHT *tl )
{
    LIGHT_VALUE		*row1, *row2, *row3;
    SLONG	x, y;
	SLONG	r, g, b, l;

    for (y = 1; y < tl->h - 1; y ++)
    {
        // Get values of pixel above and below the particle's row
        row1 = &tl->v[y-1][0];
        row2 = &tl->v[y][0];
        row3 = &tl->v[y+1][0];
        
        // Set value of next row's pixel to 0 to prevent sides of screen
        // from staying ablaze
        (*row1++).u = 0;
        (*row2++).u = 0;
        (*row3++).u = 0;
        
        // Take the average of the 4 pixels on each side of the current pixel
        // and darken it a bit too
        for (x = 1; x < tl->w - 1; x ++)
        {
			l = ( (*row1).l + (*row3).l + (*(row2 - 1)).l + (*(row2+1)).l ) / 4 - 3;
			r = ( (*row1).r + (*row3).r + (*(row2 - 1)).r + (*(row2+1)).r ) / 4 - 3;
			g = ( (*row1).g + (*row3).g + (*(row2 - 1)).g + (*(row2+1)).g ) / 4 - 3;
			b = ( (*row1).b + (*row3).b + (*(row2 - 1)).b + (*(row2+1)).b ) / 4 - 3;
			if(l < 0) l = 0;
			if(r < 0) r = 0;
			if(g < 0) g = 0;
			if(b < 0) b = 0;
            
            // Set current pixel to calculated color
            (*row2).l = (UCHR)l;
            (*row2).r = (UCHR)r;
            (*row2).g = (UCHR)g;
            (*row2).b = (UCHR)b;
            
            row1++;
            row2++;
            row3++;
        }
        
        // Set value of next row's pixel to 0 to prevent sides of screen
        // from staying ablaze
        (*row1++).u = 0;
        (*row2++).u = 0;
        (*row3++).u = 0;
    }
	memset(tl->v[0], 0, sizeof(LIGHT_VALUE) * tl->w );
	memset(tl->v[tl->h-1], 0, sizeof(LIGHT_VALUE) * tl->w );

	return;
}


void	redraw_tile_light( TILE_LIGHT *tl, BMP *bitmap )
{
	SLONG	x, y;
	SLONG	disp_x, disp_y;
	LIGHT_VALUE *	v = NULL;

	disp_y = 0;
	for(y = 0; y < tl->h; y ++)
	{
		disp_x = 0;
		v = tl->v[y];
		for(x = 0; x < tl->w; x ++)
		{
			put_light_tile(v, disp_x, disp_y, bitmap);
			v ++;
			disp_x += LIGHT_TILE_WIDTH;
		}
		disp_y += LIGHT_TILE_HEIGHT;
	}

	return;
}


void	put_light_tile(LIGHT_VALUE *v, SLONG sx, SLONG sy, BMP *bitmap)
{
	UCHR	r, g, b, l;
	PIXEL	c;

	r = v->r;
	g = v->g;
	b = v->b;
	l = v->l;

	//Jack, 2001.12.25. temp use.
	c = rgb2hi(r, g, b);
	alpha_put_bar(sx, sy, LIGHT_TILE_WIDTH, LIGHT_TILE_HEIGHT, c, bitmap, 255-l);
	//put_bar(sx, sy, LIGHT_TILE_WIDTH, LIGHT_TILE_HEIGHT, c, bitmap);

	return;
}



SLONG	load_tile_light( USTR* filename, TILE_LIGHT **tl )
{
	return	TTN_NOT_OK;
}


