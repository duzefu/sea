/*
**  Magic.cpp
**  magic functions.
**
**  Jack, 2002.4.17.
*/
#include "MainFun.h"
#include "NetGE_MainFunc.h"
#include "ClientMain.h"
#include "Map.h"
#include "MapObject.h"
#include "Magic.h"
#include "MagicClient.h"
#include "UIMagicIcon.h"
#include "MagicHit.h"

 
/************************************************************************************************************/
/* MAGIC MAIN FUNCTIONS                                                                                     */
/************************************************************************************************************/
int     init_magic(void)
{
    init_magic_hits();
    InitZoneMagicPart();

    SLONG   result;
    result = init_magic_icon_image();
    if(TTN_OK != result)
    {
        log_error(1, "load magic icon image fail");
        return  -2;
    }
    return 0;
}


void    active_magic(int active)
{
}


void    free_magic(void)
{
    free_magic_icon_image();
}

/******************************************************************************************************************/
/* MAGIC REDRAW FUNCTIONS                                                                                         */
/******************************************************************************************************************/
void    refresh_map_magic(void)
{
    client_refresh_magic();
}


void    update_map_magic_object(void)
{
	SLONG	map_no = 0;
    SLONG   p, next, flag;
    SLONG   image_id, object_index, frame, effect,obj_eff;
    SLONG   img_dir, img_max_dir;
    SLONG   x, y, z;
    SLONG   map_object_id;

    LOCK_MAGIC(0);
    p = GetZoneMagicPartNext(map_no);
    UNLOCK_MAGIC(0);

    while( map_no != p)
    {
        LOCK_MAGIC(0);
        flag = GetZoneMagicPartFlag(p);
        next = GetZoneMagicPartNext(p);
        UNLOCK_MAGIC(0);
        //
        if( flag )
        {
            LOCK_MAGIC(0);
            //
            object_index = GetZoneMagicPartObjectIndex(p);
            image_id = GetZoneMagicPartImageID(p);
            if (image_id != INVALID_OBJECT_ID)            
            {
                img_dir = GetZoneMagicPartImgDir(p);
                img_max_dir = GetZoneMagicPartDirNum(p);
                //
                image_id += MagicDirToImgDir(img_dir, img_max_dir);
            }
            //因為物件有多個方向...需要增加物件的方向編號
            //
			GetZoneMagicPartCurrPosition(p, &x, &y, &z);
            frame = GetZoneMagicPartImageFrame(p);
            //
            obj_eff = GetZoneMagicPartDrawEff(p);
            effect = OBJECT_NORMAL_IMAGE;
            if (obj_eff & MAGIC_EFF_BLEND)
            {
                //上圖需要加亮的色融合效果
                effect = OBJECT_ADDITIVE_IMAGE;
            }
            //
            UNLOCK_MAGIC(0);

			if(object_index < 0)
			{
				object_index = add_map_magic_object(image_id, x, y, z, effect, p);
				if(object_index >= 0)
				{
					LOCK_MAGIC(0);
					SetZoneMagicPartObjectIndex(p, object_index);
					UNLOCK_MAGIC(0);
					
					map_object[object_index].flag |= MOBJ_UPDATE_MAGIC;
				}
			}
			else
			{
				map_object_id = map_object[object_index].id;
				if(map_object_id != image_id)
				{
					change_map_magic_object_id(object_index, image_id);
				}
				map_object[object_index].px = x;
				map_object[object_index].py = y;
				map_object[object_index].pz = z;
				map_object[object_index].frame = frame;
				map_object[object_index].effect = effect;
				
				map_object[object_index].flag |= MOBJ_UPDATE_MAGIC;
			}
        }

        //get the next one for the loop.
        p = next;
    }

    //cleanup void magic object
    for( p = 0; p < map_object_max; p ++)
    {
        flag = map_object[p].flag;
        if( (flag & MOBJ_ACTIVE) && ((flag & MOBJ_TYPES) == MOBJ_MAGIC) )
        {
            if(flag & MOBJ_UPDATE_MAGIC)
                map_object[p].flag &= ~MOBJ_UPDATE_MAGIC;
            else
                del_map_magic_object(p);
        }
    }
}

/************************************************************************************************************/
/* MAP MAGIC OBJECT FUNCTIONS                                                                               */
/************************************************************************************************************/
SLONG   add_map_magic_object(SLONG id, SLONG px, SLONG py, SLONG pz, SLONG effect, SLONG magic_part_no)
{
    SLONG   object_index;

    object_index = get_usable_map_object();
    if(object_index >= 0)
    {
        map_object[object_index].flag = MOBJ_ACTIVE | MOBJ_MAGIC;
        map_object[object_index].id = id;
        map_object[object_index].px = px;
        map_object[object_index].py = py;
        map_object[object_index].pz = pz;
        map_object[object_index].magic_part_no = magic_part_no;

        map_object[object_index].effect = effect;
        map_object[object_index].frame = 0;
        
		if(INVALID_OBJECT_ID != id)
		{
			add_reference_for_map_object_image(id);
		}

        if(object_index >= map_object_max)
            map_object_max = object_index + 1;
    }
    return object_index;
}

SLONG	del_map_magic_object(SLONG object_index)
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

void	draw_map_magic_object(SLONG object_index, SLONG flags, BMP *bitmap)
{
    SLONG   id;
    SLONG   px,py,pz;
    SLONG   effect;
    SLONG   frame;
    SLONG   sx, sy, ox, oy, xl, yl;
	SLONG	shadow_x, shadow_y;
    SLONG   flag;
    CAKE_FRAME_ANI *cfa=NULL;
    CAKE_FRAME *cf=NULL;
    RLE *   rle=NULL;
    RLE *   headrle=NULL;
    SLONG   part_index;
	//
    POLY *  pl=NULL;
    SLONG   show_image_type;
    const SLONG draw_poly_flags = PDP_VALID | PDP_BASE | PDP_HEIGHT | PDP_ARRIS 
        | PDP_TOP | PDP_CROSS | PDP_PROJECTION | PDP_ZHEIGHT ;

    flag = map_object[object_index].flag;
    if(! (flag & MOBJ_ACTIVE) )return;

    id = map_object[object_index].id;
    px = map_object[object_index].px;
    py = map_object[object_index].py;
    pz = map_object[object_index].pz;
    effect = map_object[object_index].effect;
    frame = map_object[object_index].frame;
    part_index = map_object[object_index].magic_part_no;

    cfa=get_map_object_image(id,0);
    if(cfa) cf=cfa->cake_frame;
    if(cf) headrle=cf->rle;
    
    cfa = get_map_object_image(id,frame);
    
    rle=NULL;

    if(cfa) cf=cfa->cake_frame;
    if(cf) { rle=cf->rle; pl=cf->poly; }
    if(rle)
    {
        // we suppose all frame's polys have the same barycenter position,
        // so the offset x/y is just the following values...
        ox=-cf->poly_rx;
        oy=-cf->poly_ry;
        
        xl=rle->w;
        yl=rle->h;
        
        sx=ox+px-map_data.map_sx;
        sy=oy+py-pz-map_data.map_sy;

        // flags effect ---------------------------------------------------
        if( (flag & MOBJ_MARKED) && (headrle) )
        {
            put_ellipse(px-map_data.map_sx,py-pz-map_data.map_sy,headrle->w/2+2,headrle->w/4+1,SYSTEM_GREEN,bitmap);
        }

        // show auto shadow -----------------------------------------------
        if(effect & OBJECT_SHADOW)
        {
        }

		// show image shadow -----------------------------------------
		shadow_x = sx;
		shadow_y = sy + pz;
		alpha_put_rle(shadow_x, shadow_y, rle, bitmap, 64);

        // show image ------------------------------------------------
        show_image_type = effect & OBJECT_IMAGE_MASK;

        // Jack,  [16:14,9/27/2002]
        /*
        if(ext_flag<0)
        {
            mesh_put_rle(sx,sy,rle,bitmap);
        }
        else
        */
        {
            switch(show_image_type)
            {
            case OBJECT_NORMAL_IMAGE:
                // Jack. [14:44,9/19/2002]
                //merge_put_rle(sx, sy, rle, bitmap);
                put_rle(sx,sy,rle,bitmap);
                //filter_put_rle(sx,sy,rle,bitmap,128);
                //additive_put_rle(sx,sy,rle,bitmap);
                break;
            case OBJECT_MASK_IMAGE:
                mesh_put_rle(sx,sy,rle,bitmap);
                break;
            case OBJECT_MASK_EDGE_IMAGE:
                // we set default mask_color
                mask_edge_put_rle(sx,sy,SYSTEM_YELLOW,rle,bitmap);
                break;
            case OBJECT_GRAY_IMAGE:
                gray_put_rle(sx,sy,rle,bitmap);
                break;
            case OBJECT_GRAY_EDGE_IMAGE:
                gray_edge_put_rle(sx,sy,rle,bitmap);
                break;
            case OBJECT_ALFA_IMAGE:
                // we set alpha=30
                alpha_put_rle(sx,sy,rle,bitmap,30);
                break;
            case OBJECT_ALFA_EDGE_IMAGE:
                // we set alpha=30
                alpha_edge_put_rle(sx,sy,rle,bitmap,30);
                break;
            case OBJECT_ADDITIVE_IMAGE:
                additive_put_rle(sx,sy,rle,bitmap);
                break;
            case OBJECT_ADDITIVE_EDGE_IMAGE:
                additive_edge_put_rle(sx,sy,rle,bitmap);
                break;
            case OBJECT_SUBTRACTIVE_IMAGE:
                subtractive_put_rle(sx,sy,rle,bitmap);
                break;
            case OBJECT_SUBTRACTIVE_EDGE_IMAGE:
                subtractive_edge_put_rle(sx,sy,rle,bitmap);
                break;
            case OBJECT_MINIMUM_IMAGE:
                minimum_put_rle(sx,sy,rle,bitmap);
                break;
            case OBJECT_MINIMUM_EDGE_IMAGE:
                minimum_edge_put_rle(sx,sy,rle,bitmap);
                break;
            case OBJECT_MAXIMUM_IMAGE:
                maximum_put_rle(sx,sy,rle,bitmap);
                break;
            case OBJECT_MAXIMUM_EDGE_IMAGE:
                maximum_edge_put_rle(sx,sy,rle,bitmap);
                break;
            case OBJECT_HALF_IMAGE:
                half_put_rle(sx,sy,rle,bitmap);
                break;
            case OBJECT_HALF_EDGE_IMAGE:
                half_edge_put_rle(sx,sy,rle,bitmap);
                break;
            case OBJECT_MESH_IMAGE:
                mesh_put_rle(sx,sy,rle,bitmap);
                break;
            case OBJECT_SCALE_IMAGE:
                // for speed,we dont support this...
                //scale_put_rle(SLONG sx,SLONG sy,SLONG scalex,SLONG scaley,RLE *src_rle,BMP *dest_bmp);
                break;
            case OBJECT_LIGHT_IMAGE:
                //light_put_rle(sx,sy,rle,bitmap);
                break;
            case OBJECT_RED_IMAGE:
                red_put_rle(sx, sy, rle, bitmap);
                break;
            case OBJECT_GREEN_IMAGE:
                green_put_rle(sx, sy, rle, bitmap);
                break;
            case OBJECT_BLUE_IMAGE:
                blue_put_rle(sx, sy, rle, bitmap);
                break;
            case OBJECT_YELLOW_IMAGE:
                yellow_put_rle(sx, sy, rle, bitmap);
                break;
            case OBJECT_MERGE_IMAGE:
                merge_put_rle(sx, sy, rle, bitmap);
                break;
            default:
                break;
            }
        }
        // show poly -------------------------------------------------------
#ifdef  DEBUG
        if(effect & OBJECT_POLY)
        {
            D3_draw_poly(px-map_data.map_sx,py-map_data.map_sy,pz,draw_poly_flags,pl,bitmap);
        }
#endif//DEBUG
        // show box --------------------------------------------------------
        if(effect & OBJECT_BOX)
        {
        }
        //------------------------------------------------------------------

        //------------------------------------------------------------------

#ifdef  DEBUG
        if(flags<0)
        {
            sprintf((char *)print_rec,"~O3~C0#%d(H%d)~C0~O0",abs(flags),pz);
            print16(px-map_data.map_sx,py-map_data.map_sy-pz,(USTR *)print_rec,PEST_PUT,bitmap);
        }
#endif//DEBUG

    }

#ifdef  DEBUG
    /*{
        SLONG   part_dest_x, part_dest_y, part_dest_z;
        SLONG   part_orig_x, part_orig_y, part_orig_z;

        LOCK_MAGIC(0);
        part_orig_x = magic_part[part_index].orig_x;
        part_orig_y = magic_part[part_index].orig_y;
        part_orig_z = magic_part[part_index].orig_z;
        part_dest_x = magic_part[part_index].dest_x;
        part_dest_y = magic_part[part_index].dest_y;
        part_dest_z = magic_part[part_index].dest_z;
        UNLOCK_MAGIC(0);

        put_line( part_orig_x - map_data.map_sx, part_orig_y - map_data.map_sy,
            part_dest_x - map_data.map_sx, part_dest_y - map_data.map_sy,
            SYSTEM_PINK, bitmap);
    }*/
#endif//DEBUG

}

void	refresh_map_magic_object(SLONG object_index)
{
	// Do nothing here.
	// We will refresh map magic object after we refreshed magic part.
}

SLONG	change_map_magic_object_id(SLONG object_index, SLONG new_id)
{
	SLONG	old_id;

	old_id = map_object[object_index].id;
	if(new_id != INVALID_OBJECT_ID)
	{
		add_reference_for_map_object_image(new_id);
	}
	if(old_id != INVALID_OBJECT_ID)
	{
		dec_reference_for_map_object_image(old_id);
	}
	map_object[object_index].id = new_id;

    return  TTN_OK;
}

SLONG	get_map_magic_object_information(SLONG object_index, SLONG *object_flag, SLONG *sx, SLONG *sy, 
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


