/*
**  TileField.cpp
**
**  Map tile field functions.
**
**  Jack, 2002.3.6.
*/
#include "mainfun.h"
#include "TileSet.h"
#include "TileImage.h"
#include "TileField.h"
#include "MapHouse.h"


//DEFINES ---------------------------------------------------------------------------------------
#define TILE_REFRESH_TICKS      30


//GLOBALS ---------------------------------------------------------------------------------------
TILE_FIELD* map_tile_field  =   NULL;
TILE_PLAT   map_tile_plat;


//FUNCTIONS -------------------------------------------------------------------------------------
TILE_FIELD* create_tile_field(SLONG width, SLONG height, SLONG base_no, SLONG terra_no)
{
    TILE_FIELD *tmp = NULL;
    SLONG   size;
	//SLONG	solid_index, shape_index, tile_id, index;

    size = sizeof(TILE_FIELD) + (width * height - 1) * sizeof(TILE_INST);
    if(NULL == (tmp = (TILE_FIELD*)malloc(size)))
    {
        log_error(1, "memory alloc error(create_tile_field)");
        return  NULL;
    }
    tmp->width = width;
    tmp->height = height;
    tmp->base_no = base_no;
    tmp->terra_no = terra_no;
	/*
    solid_index = terra_set[base_no].solid_terra[terra_no];
    shape_index = get_solid_terra_shape_index(solid_index);

    tile_id = shape_index_to_normal_tile_id(shape_index);
    for(index = 0; index < width * height; index++)
    {
        tmp->tile_inst[index].tile_id = tile_id;
        tmp->tile_inst[index].cover_id = 0;
        tmp->tile_inst[index].flag = 0;
    }
	*/

    return  (TILE_FIELD*)tmp;
}


void        destroy_tile_field(TILE_FIELD **field)
{
    if(*field)
    {
        free(*field);
        *field = NULL;
    }
    return;
}


SLONG   pixel_position_to_tile_x(TILE_FIELD *field, SLONG x, SLONG y)
{
    return ( TILE_HEIGHT * x + TILE_WIDTH * y - field->width * TILE_WIDTH * TILE_HEIGHT / 2 ) / (TILE_WIDTH * TILE_HEIGHT );
}


SLONG   pixel_position_to_tile_y(TILE_FIELD *field, SLONG x, SLONG y)
{
    return  (-TILE_HEIGHT * x + TILE_WIDTH * y + field->width * TILE_WIDTH * TILE_HEIGHT / 2 ) / (TILE_WIDTH * TILE_HEIGHT );
}


void    pixel_position_to_tile_position(TILE_FIELD *field, SLONG x, SLONG y, SLONG *tile_x, SLONG *tile_y)
{
    *tile_x = ( TILE_HEIGHT * x + TILE_WIDTH * y - field->width * TILE_WIDTH * TILE_HEIGHT / 2 ) / (TILE_WIDTH * TILE_HEIGHT );
    *tile_y = (-TILE_HEIGHT * x + TILE_WIDTH * y + field->width * TILE_WIDTH * TILE_HEIGHT / 2 ) / (TILE_WIDTH * TILE_HEIGHT );
}


void	redraw_tile_field(TILE_FIELD *field, SLONG sx, SLONG sy, BMP *bitmap)
{
    SLONG   tile_sx, tile_sy, tile_ex, tile_ey, field_xl;
    SLONG   tile_x, tile_y, tile_offset, tile_id, cover_id, image_no, flag;
    SLONG   house_index, house_no;
    SLONG   disp_x, disp_y;
    static  SLONG   frame = 0;
    XIMG *  ximg = NULL;

    if(timer_tick04 > TILE_REFRESH_TICKS)
    {
        frame ++;
        if(frame >= TILE_IMAGES)
            frame = 0;
        timer_tick04 = 0;
    }

    field_xl = field->width * TILE_WIDTH;
    tile_sx = pixel_position_to_tile_x(field, sx, sy);
    tile_sy = pixel_position_to_tile_y(field, sx + bitmap->w, sy);
    tile_ex = pixel_position_to_tile_x(field, sx + bitmap->w, sy + bitmap->h);
    tile_ey = pixel_position_to_tile_y(field, sx, sy + bitmap->h);

    for(tile_y = tile_sy; tile_y <= tile_ey; tile_y++)
    {
        if(tile_y < 0 || tile_y >= field->height)
            continue;
        for(tile_x = tile_sx; tile_x <= tile_ex; tile_x++)
        {
            if(tile_x < 0 || tile_x >= field->width)
                continue;

            disp_x = field_xl/2 + TILE_WIDTH/2 * (tile_x - tile_y) - TILE_WIDTH/2 - sx;
            disp_y = TILE_HEIGHT/2 * (tile_x + tile_y) - sy;
            if(disp_x + TILE_WIDTH < 0 || disp_x >= bitmap->w)
                continue;
            if(disp_y + TILE_HEIGHT < 0 || disp_y >= bitmap->h)
                continue;

            tile_offset = tile_y * field->width + tile_x;
            flag = field->tile_inst[tile_offset].flag;
            tile_id = field->tile_inst[tile_offset].tile_id;
            cover_id = field->tile_inst[tile_offset].cover_id;

            switch(flag & COVER_TILE_TYPE_MASK)
            {
            case COVER_TILE_IS_HOUSE:
                {/* cover tile is house floor ximgs */
                    switch(flag & COVER_TILE_AREA_MASK)
                    {
                    case COVER_TILE_WHOLE_COVER:
                        {
                            house_index = (cover_id & 0xffff0000) >> 16;
                            house_no = get_map_house_no(house_index);
                            if(house_no >= 0)
                            {
                                image_no = cover_id & 0x0000ffff;
                                ximg = get_house_floor_ximg(house_no, image_no);
                                if(disp_x>=0 && disp_y >=0 && disp_x<bitmap->w-TILE_WIDTH && disp_y<bitmap->h-TILE_HEIGHT)
                                    put_ximg(disp_x, disp_y, ximg, bitmap);
                                else
                                    range_put_ximg(disp_x, disp_y, ximg, bitmap);
                            }
                        }
                        break;
                    case COVER_TILE_PART_COVER:
                        {
                            //under tile.
                            image_no = get_tile_terra_image_no(tile_id, frame);
                            if(image_no >= 0)
                            {
                                if(disp_x>=0 && disp_y >=0 && disp_x<bitmap->w-TILE_WIDTH && disp_y<bitmap->h-TILE_HEIGHT)
                                    put_tile_image(disp_x, disp_y, tile_image_data[image_no].buffer, bitmap);
                                else
                                    range_put_tile_image(disp_x, disp_y, tile_image_data[image_no].buffer, bitmap);
                            }
                            
                            //cover tile.
                            house_index = (cover_id & 0xffff0000) >> 16;
                            house_no = get_map_house_no(house_index);
                            if(house_no >= 0)
                            {
                                image_no = cover_id & 0x0000ffff;
                                ximg = get_house_floor_ximg(house_no, image_no);
                                if(disp_x>=0 && disp_y >=0 && disp_x<bitmap->w-TILE_WIDTH && disp_y<bitmap->h-TILE_HEIGHT)
                                    put_ximg(disp_x, disp_y, ximg, bitmap);
                                else
                                    range_put_ximg(disp_x, disp_y, ximg, bitmap);
                            }
                        }
                        break;
                    default:
                        {
                            image_no = get_tile_terra_image_no(tile_id, frame);
                            if(image_no >= 0)
                            {
                                if(disp_x>=0 && disp_y >=0 && disp_x<bitmap->w-TILE_WIDTH && disp_y<bitmap->h-TILE_HEIGHT)
                                    put_tile_image(disp_x, disp_y, tile_image_data[image_no].buffer, bitmap);
                                else
                                    range_put_tile_image(disp_x, disp_y, tile_image_data[image_no].buffer, bitmap);
                            }
                        }
                        break;
                    }
                }
                break;
            case COVER_TILE_IS_OBJECT:
                break;
            default:    //no cover tile, only redraw under tile.
                {
                    image_no = get_tile_terra_image_no(tile_id, frame);
                    if(image_no >= 0)
                    {
                        if(disp_x>=0 && disp_y >=0 && disp_x<bitmap->w-TILE_WIDTH && disp_y<bitmap->h-TILE_HEIGHT)
                            put_tile_image(disp_x, disp_y, tile_image_data[image_no].buffer, bitmap);
                        else
                            range_put_tile_image(disp_x, disp_y, tile_image_data[image_no].buffer, bitmap);
                    }
                }
                break;
            }
        }
    }
    return;
}


SLONG   naked_read_tile_field(PACK_FILE *fp, TILE_FIELD **field)
{
    TILE_FIELD  tf;
    SLONG   head_size, data_size, read_size;

    head_size = sizeof(TILE_FIELD) - 1 * sizeof(TILE_INST);
    read_size = pack_fread(&tf, 1, head_size, fp);
    if(read_size != head_size)
    {
        log_error(1, "read tile field head error");
        return  TTN_ERROR;
    }
    if(NULL == ((*field) = create_tile_field(tf.width, tf.height, tf.base_no, tf.terra_no)))
    {
        log_error(1, "memory alloc error when read tile field");
        return  TTN_ERROR;
    }
    (*field)->width = tf.width;
    (*field)->height = tf.height;
    (*field)->base_no = tf.base_no;
    (*field)->terra_no = tf.terra_no;

    data_size = (*field)->width * (*field)->height * sizeof(TILE_INST);
    read_size = pack_fread( &(*field)->tile_inst[0], 1, data_size, fp);
    if(read_size != data_size)
    {
        log_error(1, "read tile field data error");
        return  TTN_ERROR;
    }

    return  TTN_OK;
}


SLONG   get_in_house_index_by_pixel_position(TILE_FIELD *field, SLONG pixel_x, SLONG pixel_y)
{
    TILE_INST   *ti;
    SLONG   tile_x, tile_y, cover_id, house_index;

    pixel_position_to_tile_position(field, pixel_x, pixel_y, &tile_x, &tile_y);
    if(tile_x < 0 || tile_x >= field->width || tile_y < 0 || tile_y >= field->height )
        return  -1;
    ti = &field->tile_inst[tile_y * field->width + tile_x];
    if(ti->flag & FIELD_TILE_IN_HOUSE)
    {
        cover_id = ti->cover_id;
        house_index = (cover_id & 0xffff0000) >> 16;
        return  house_index;
    }
    return  -1;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TILE PLAT FUNCTIONS                                                                                      //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
SLONG   init_map_tile_plat(void)
{
	SLONG	w, h;

	map_tile_plat.sx = 0;
	map_tile_plat.sy = 0;
	map_tile_plat.ex = 0;
	map_tile_plat.ey = 0;
	map_tile_plat.bitmap = create_bitmap(TILE_PLAT_WIDTH, TILE_PLAT_HEIGHT);
	if(map_tile_plat.bitmap == NULL)
		return	TTN_ERROR;
	clear_bitmap(map_tile_plat.bitmap);

	for(h=0; h<TILE_PLAT_HEIGHT_SCREENS; h++)
	{
		for(w=0; w<TILE_PLAT_WIDTH_SCREENS; w++)
		{
			map_tile_plat.sub_bitmap[h][w] = create_sub_bitmap(map_tile_plat.bitmap, 
				w * SCREEN_WIDTH, h * SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT);
			if(map_tile_plat.sub_bitmap[h][w] == NULL)
			{
				return TTN_ERROR;
			}
		}
	}

	return	TTN_OK;
}


void	free_map_tile_plat(void)
{
	SLONG	w, h;

	for(h = 0; h<TILE_PLAT_HEIGHT_SCREENS; h++)
	{
		for(w = 0; w<TILE_PLAT_WIDTH_SCREENS; w++)
		{
			destroy_bitmap(&map_tile_plat.sub_bitmap[h][w]);
		}
	}
	destroy_bitmap(&map_tile_plat.bitmap);
	return;
}


void	reset_map_tile_plat(void)
{
	map_tile_plat.sx = 0;
	map_tile_plat.sy = 0;
	map_tile_plat.ex = 0;
	map_tile_plat.ey = 0;
	clear_bitmap(map_tile_plat.bitmap);
}


void    plat_redraw_tile_field(TILE_FIELD *field, SLONG sx, SLONG sy, BMP *bitmap)
{
	SLONG	ex, ey;
	SLONG	w, h;
	SLONG	plat_sx, plat_sy;
	SLONG	plat_x, plat_y;
	SLONG	in_range;

    //Jack, 2002.4.18.
    //TODO:
    //目前還不能支持多層動態圖素.

	ex = sx + bitmap->w;
	ey = sy + bitmap->h;

	in_range = 0;
	if( D2_INCLUDE(sx, sy, map_tile_plat.sx, map_tile_plat.sy, map_tile_plat.ex, map_tile_plat.ey)
		&& D2_INCLUDE(ex, ey, map_tile_plat.sx, map_tile_plat.sy, map_tile_plat.ex, map_tile_plat.ey) )
	{
		in_range = 1;
	}

	if(! in_range)
	{
		plat_sx = map_tile_plat.sx = sx - TILE_PLAT_WIDTH / 2;
		plat_sy = map_tile_plat.sy = sy - TILE_PLAT_HEIGHT / 2;
		map_tile_plat.ex = map_tile_plat.sx + TILE_PLAT_WIDTH;
		map_tile_plat.ey = map_tile_plat.sy + TILE_PLAT_HEIGHT;

		plat_y = plat_sy;
		for(h=0; h<TILE_PLAT_HEIGHT_SCREENS; h++)
		{
			plat_x = plat_sx;
			for(w=0; w<TILE_PLAT_WIDTH_SCREENS; w++)
			{
				redraw_tile_field(field, plat_x, plat_y, map_tile_plat.sub_bitmap[h][w]);
				plat_x += SCREEN_WIDTH;
			}
			plat_y += SCREEN_HEIGHT;
		}
	}

	bound_put_bitmap(0, 0, sx - map_tile_plat.sx, sy - map_tile_plat.sy, 
		bitmap->w, bitmap->h, map_tile_plat.bitmap, bitmap);

	return;
}


