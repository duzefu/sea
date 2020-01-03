/*
**  NetGE_MapMask.cpp
**  map mask functions.
**
**  Jack, 2002.12.11.
*/
#include "NetGE_Mainfunc.h"


/************************************************************************************************************/
/* DEFINES & STRUCTS                                                                                        */
/************************************************************************************************************/
#define LAST_MAP_MASK_FILE_VERSION  0x00020000


typedef enum    MASK_DIR_ENUM
{   MASK_DIR_CENTER     =   0,
MASK_DIR_UP             =   1,
MASK_DIR_DOWN           =   2,
MASK_DIR_LEFT           =   3,
MASK_DIR_RIGHT          =   4,
MASK_DIR_LEFT_UP        =   5,
MASK_DIR_LEFT_DOWN      =   6,
MASK_DIR_RIGHT_UP       =   7,
MASK_DIR_RIGHT_DOWN     =   8,
} MASK_DIR_ENUM;


typedef struct tagMASK_NPC 
{
	SLONG		npc_mask_x[MAX_CHARACTER_PER_ZONE];	//NPC 的阻擋座標 X
	SLONG		npc_mask_y[MAX_CHARACTER_PER_ZONE];	//NPC 的阻擋座標 Y
	SLONG		mask_npcs;					//總共有多少有阻擋的NPC 
} MASK_NPC, *LPMASK_NPC;


MASK_NPC	l_MaskNpc;
MAP_MASK	*l_MapMask = NULL;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MAP MASK FUNCTIONS
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
MAP_MASK *  create_map_mask(SLONG w, SLONG h, SLONG sw, SLONG sh)
{
    MAP_MASK    *tmp = NULL;
    SLONG   size;

    size = sizeof(MAP_MASK)  + (w * h - 4) * sizeof(UCHR);
    if(NULL == (tmp = (MAP_MASK*)malloc(size)) )
        return NULL;
    tmp->w = w;
    tmp->h = h;
    tmp->sw = sw;
    tmp->sh = sh;
    memset(tmp->data, 0, w * h);
    return tmp;
}


void    destroy_map_mask(MAP_MASK **mm)
{
    if(*mm)
    {
        free(*mm);
        *mm = NULL;
    }
}


MAP_MASK *  load_map_mask(USTR *filename)
{
    PACK_FILE    *fp = NULL;
    MAP_MASK    *tmp = NULL;
    MAP_MASK_HEAD   mmh;

    if(NULL == (fp = pack_fopen((const char *)filename, "rb")) )
    {
        log_error(1, "file %s open error", filename);
        goto error;
    }
    pack_fread(&mmh, 1, sizeof(mmh), fp);
    if(mmh.version != LAST_MAP_MASK_FILE_VERSION)
    {
        log_error(1, "map mask file %s version error");
        goto error;
    }
    if(NULL == (tmp = create_map_mask(mmh.w, mmh.h, mmh.sw, mmh.sh )) )
    {
        log_error(1, "memory alloc error");
        goto error;
    }
    pack_fread(tmp->data, 1, mmh.w * mmh.h * sizeof(UCHR), fp);
    if(fp) pack_fclose(fp);

    return tmp;
error:
    if(fp) pack_fclose(fp);
    if(tmp) free(tmp);
    return NULL;

}


UCHR    get_map_mask(MAP_MASK *mm, SLONG x, SLONG y)
{
    return mm->data[y * mm->w + x];
}


void    set_map_mask(MAP_MASK *mm, SLONG x, SLONG y, UCHR mask)
{
    mm->data[y * mm->w + x] = mask;
}


void	or_map_mask(MAP_MASK *mm, SLONG x, SLONG y, UCHR mask)
{
	mm->data[y * mm->w + x] |= mask;
}


void	remove_map_mask(MAP_MASK *mm, SLONG x, SLONG y, UCHR mask)
{
	mm->data[y * mm->w + x] &= ~mask;
}


void    convert_position_map2mask(MAP_MASK *mm, SLONG map_x, SLONG map_y, SLONG *mask_x, SLONG *mask_y)
{
    *mask_x = map_x / mm->sw;
    *mask_y = map_y / mm->sh;
}


SLONG   approach_mask_dir(SLONG mask_dx, SLONG mask_dy)
{
    static  SLONG   dir[3][3] = 
    {               /*dx<0*/        /*dx=0*/            /*dx>0*/
        /*dy>0*/{MASK_DIR_LEFT_UP   ,MASK_DIR_UP        ,MASK_DIR_RIGHT_UP  },
        /*dy=0*/{MASK_DIR_LEFT      ,MASK_DIR_CENTER    ,MASK_DIR_RIGHT     },
        /*dy<0*/{MASK_DIR_LEFT_DOWN ,MASK_DIR_DOWN      ,MASK_DIR_RIGHT_DOWN}
    };
    SLONG   x_index, y_index;

    if(mask_dx < 0) 
        x_index = 0;
    else if(mask_dx == 0)
        x_index = 1;
    else
        x_index = 2;

    if(mask_dy > 0)
        y_index = 0;
    else if(mask_dy == 0)
        y_index = 1;
    else
        y_index = 2;

    return dir[y_index][x_index];
}


SLONG   is_pixel_mask_stop(SLONG pixel_x, SLONG pixel_y, MAP_MASK *mm)
{
    SLONG   mask_x, mask_y;
    UCHR    mask;

    mask_x = pixel_x / mm->sw;
    mask_y = pixel_y / mm->sh;

    //if it out of range, we set to stop.
    if(mask_x < 0 || mask_x >= mm->w || mask_y < 0 || mask_y >= mm->h)
        return  TRUE;
    mask = get_map_mask(mm, mask_x, mask_y);
    if( mask & MASK_STOP)
        return  TRUE;
    return  FALSE;
}


SLONG   is_pixel_mask_match(SLONG pixel_x, SLONG pixel_y, SLONG check_mask, MAP_MASK *mm)
{
    SLONG   mask_x, mask_y;
    UCHR    mask;

    mask_x = pixel_x / mm->sw;
    mask_y = pixel_y / mm->sh;

    //if it out of range, we set to stop.
    if(mask_x < 0 || mask_x >= mm->w || mask_y < 0 || mask_y >= mm->h)
        return  TRUE;
    mask = get_map_mask(mm, mask_x, mask_y);
    if( mask & check_mask)
        return  TRUE;
    return  FALSE;
}


SLONG   is_mask_line_through(SLONG x1, SLONG y1, SLONG x2, SLONG y2, SLONG stop_mask, MAP_MASK *mm)
{
    SLONG   dx,dy,dm,dn,m,n,k,u,v,l,sum;
    UCHR    stop, mask;

    //  if(x1 < 0 || x1 >= mm->w || y1 < 0 || y1 >= mm->h)
    //      return FALSE;
    //  if(x2 < 0 || x2 >= mm->w || y2 < 0 || y2 >= mm->h)
    //      return FALSE;
    stop = (UCHR)stop_mask;
    dx = x2 - x1, dy = y2 - y1;
    if(dx == 0)
    {
        u = y1, v = y2;
        if(dy < 0) u = y2, v = y1;
        for (l = u; l <= v; l ++)
        {
            mask = get_map_mask(mm, x2, l);
            if(mask & stop)
                return FALSE;
        }
        return TRUE;
    }
    if(dy==0)
    {
        u = x1, v = x2;
        if(dx < 0) u = x2,v = x1;
        for(l = u; l <= v; l ++)
        {
            mask = get_map_mask(mm, l, y2);
            if(mask & stop)
                return FALSE;
        }
        return TRUE;
    }
    
    dm = dn = 1;
    if(dx < 0) dx = -dx, dm = -1;
    if(dy < 0) dy = -dy, dn = -1;
    m = dx, n = dy, k = 1, u = x1, v = y1;
    if(dx<dy) m = dy, n = dx, k = dm, dm = dn, dn = k, k = 0, u = y1, v = x1;
    l = 0;
    sum = m;

    mask = get_map_mask(mm, x1, y1);
    if(mask & stop)
        return FALSE;
    while (sum != 0)
    {
        sum--;
        l += n;
        u += dm;
        if(l >= m)
        {
            v += dn;
            l -= m;
        }
        if(k == 1)
        {
            mask = get_map_mask(mm, u, v);
            if(mask & stop)
                return FALSE;
        }
        else
        {
            mask = get_map_mask(mm, v, u);
            if(mask & stop)
                return FALSE;
        }
    }
    return TRUE;
}


SLONG   is_pixel_line_through(SLONG x1, SLONG y1, SLONG x2, SLONG y2, SLONG stop_mask, MAP_MASK *mm)
{
    SLONG   dx,dy,dm,dn,m,n,k,u,v,l,sum;
    UCHR    stop, mask;

    stop = (UCHR)stop_mask;
    dx = x2 - x1, dy = y2 - y1;
    if(dx == 0)
    {
        u = y1, v = y2;
        if(dy < 0) u = y2, v = y1;
        for (l = u; l <= v; l ++)
        {
            mask = get_map_mask(mm, x2 / mm->sw, l / mm->sh);
            if(mask & stop)
                return FALSE;
        }
        return TRUE;
    }
    if(dy==0)
    {
        u = x1, v = x2;
        if(dx < 0) u = x2,v = x1;
        for(l = u; l <= v; l ++)
        {
            mask = get_map_mask(mm, l / mm->sw, y2 / mm->sh);
            if(mask & stop)
                return FALSE;
        }
        return TRUE;
    }
    
    dm = dn = 1;
    if(dx < 0) dx = -dx, dm = -1;
    if(dy < 0) dy = -dy, dn = -1;
    m = dx, n = dy, k = 1, u = x1, v = y1;
    if(dx<dy) m = dy, n = dx, k = dm, dm = dn, dn = k, k = 0, u = y1, v = x1;
    l = 0;
    sum = m;

    mask = get_map_mask(mm, x1 / mm->sw, y1 / mm->sh);
    if(mask & stop)
        return FALSE;
    while (sum != 0)
    {
        sum--;
        l += n;
        u += dm;
        if(l >= m)
        {
            v += dn;
            l -= m;
        }
        if(k == 1)
        {
            mask = get_map_mask(mm, u / mm->sw, v / mm->sh);
            if(mask & stop)
                return FALSE;
        }
        else
        {
            mask = get_map_mask(mm, v / mm->sw, u / mm->sh);
            if(mask & stop)
                return FALSE;
        }
    }
    return TRUE;
}


SLONG   find_mask_near_open_pixel(SLONG *pixel_x, SLONG *pixel_y, SLONG stop_mask, MAP_MASK *mm)
{
    UCHR    stop, mask;
    SLONG   mask_cx, mask_cy;
    SLONG   mask_x, mask_y;
    SLONG   n, x, y;

    stop = (UCHR)stop_mask;

    mask_cx = *pixel_x / mm->sw;
    mask_cy = *pixel_y / mm->sh;

    if(mask_cx < 0) mask_cx = 0;
    if(mask_cx >= mm->w) mask_cx = mm->w-1;
    if(mask_cy < 0) mask_cy = 0;
    if(mask_cy >= mm->h) mask_cy = mm->h -1;

    // . . . . . . . . . . . . . . . . . . . . .
    // . . . . . . . . . . . . . . . . . . . . .
    // . . . . . . . . . . . . . . . . . . . . .
    // . . . . . . . . n n n n n n n n n . . . .
    // . . . . . . . . n . . . . . . . n . . . .
    // . . . . . . . . n . 2 2 2 2 2 . n . . . .
    // . . . . . . . . n . 2 1 1 1 2 . n . . . .
    // . . . . . . . . n . 2 1 x 1 2 . n ------X
    // . . . . . . . . n . 2 1 1 1 2 . n . . . .
    // . . . . . . . . n . 2 2 2 2 2 . n . . . .
    // . . . . . . . . n . . . . . . . n . . . .
    // . . . . . . . . n n n n n n n n n . . . .
    // . . . . . . . . . . . . | . . . . . . . .
    // . . . . . . . . . . . . | . . . . . . . .
    // . . . . . . . . . . . . y . . . . . . . .

    for(n = 1; n < 5; n ++ )
    {
        //bottom line -------------------------------------
        y = n;
        mask_y = mask_cy + y;
        for(x = n; x <= -n; x --)
        {
            mask_x = mask_cx + x;
            mask = get_map_mask(mm, mask_x, mask_y);
            if(! (mask & stop) )
            {
                *pixel_x = mask_x * mm->sw;
                *pixel_y = mask_y * mm->sh;
                return TTN_OK;
            }
        }

        //left line ----------------------------------------
        x = -n;
        mask_x = mask_cx + x;
        for(y = n-1; y <= -n+1; y --)
        {
            mask_y = mask_cy + y;
            mask = get_map_mask(mm, mask_x, mask_y);
            if(! (mask & stop) )
            {
                *pixel_x = mask_x * mm->sw;
                *pixel_y = mask_y * mm->sh;
                return TTN_OK;
            }
        }

        //top line -----------------------------------------
        y = -n;
        mask_y = mask_cy + y;
        for(x = n; x <= -n; x --)
        {
            mask_x = mask_cx + x;
            mask = get_map_mask(mm, mask_x, mask_y);
            if(! (mask & stop) )
            {
                *pixel_x = mask_x * mm->sw;
                *pixel_y = mask_y * mm->sh;
                return TTN_OK;
            }
        }

        //right line ---------------------------------------
        x = n;
        mask_x = mask_cx + x;
        for(y = n-1; y <= -n+1; y --)
        {
            mask_y = mask_cy + y;
            mask = get_map_mask(mm, mask_x, mask_y);
            if(! (mask & stop) )
            {
                *pixel_x = mask_x * mm->sw;
                *pixel_y = mask_y * mm->sh;
                return TTN_OK;
            }
        }
    }
    return  TTN_NOT_OK;
}


SLONG   find_mask_near_through_pixel(SLONG pixel_sx, SLONG pixel_sy, SLONG *pixel_ex, SLONG *pixel_ey, SLONG stop_mask, MAP_MASK *mm)
{
    SLONG   dx,dy,dm,dn,m,n,k,u,v,l,sum;
    UCHR    stop, mask;
    SLONG   x1, y1, x2, y2;
    SLONG   last_x, last_y;

    x1 = pixel_sx;
    y1 = pixel_sy;
    x2 = *pixel_ex;
    y2 = *pixel_ey;
    stop = (UCHR)stop_mask;

    dx = x2 - x1, dy = y2 - y1;
    if(dx == 0)
    {
        if(dy > 0)
        {
            for(l = y1; l <= y2; l ++)
            {
                mask = get_map_mask(mm, x2 / mm->sw, l / mm->sh);
                if(mask & stop)
                {
                    //get last point
                    *pixel_ex = x2;
                    *pixel_ey = l - 1;
                    return  TTN_NOT_OK;
                }
            }
            return  TTN_OK;
        }
        else
        {
            for(l = y1; l >= y2; l --)
            {
                mask = get_map_mask(mm, x2 / mm->sw, l / mm->sh);
                if(mask & stop)
                {
                    //get last point
                    *pixel_ex = x2;
                    *pixel_ey = l + 1;
                    return  TTN_NOT_OK;
                }
            }
            return  TTN_OK;
        }
    }
    if(dy == 0)
    {
        if( dx > 0)
        {
            for(l = x1; l <= x2; l ++)
            {
                mask = get_map_mask(mm, l / mm->sw, y2 / mm->sh);
                if(mask & stop)
                {
                    *pixel_ex = l - 1;
                    *pixel_ey = y2;
                    return TTN_NOT_OK;
                }
            }
            return  TTN_OK;
        }
        else
        {
            for(l = x1; l >= x2; l --)
            {
                mask = get_map_mask(mm, l / mm->sw, y2 / mm->sh);
                if(mask & stop)
                {
                    *pixel_ex = l + 1;
                    *pixel_ey = y2;
                    return TTN_NOT_OK;
                }
            }
            return  TTN_OK;
        }
    }
    
    dm = dn = 1;
    if(dx < 0) dx = -dx, dm = -1;
    if(dy < 0) dy = -dy, dn = -1;
    m = dx, n = dy, k = 1, u = x1, v = y1;
    if(dx < dy) m = dy, n = dx, k = dm, dm = dn, dn = k, k = 0, u = y1, v = x1;
    l = 0;
    sum = m;

    mask = get_map_mask(mm, x1 / mm->sw, y1 / mm->sh);
    if(mask & stop)
    {
        *pixel_ex = x1;
        *pixel_ey = y1;
        return  TTN_NOT_OK;
    }

    last_x = x1;
    last_y = y1;
    while (sum != 0)
    {
        sum --;
        l += n;
        u += dm;
        if(l >= m)
        {
            v += dn;
            l -= m;
        }
        if(k == 1)
        {
            mask = get_map_mask(mm, u / mm->sw, v / mm->sh);
            if(mask & stop)
            {
                *pixel_ex = last_x;
                *pixel_ey = last_y;
                return TTN_NOT_OK;
            }
            last_x = u;
            last_y = v;
        }
        else
        {
            mask = get_map_mask(mm, v / mm->sw, u / mm->sh);
            if(mask & stop)
            {
                *pixel_ex = last_x;
                *pixel_ey = last_y;
                return TTN_NOT_OK;
            }
            last_x = v;
            last_y = u;
        }
    }

    return TTN_OK;
}


void    intercept_geometry_line(SLONG sx, SLONG sy, SLONG *ex, SLONG *ey, SLONG len)
{
    SLONG   dx, dy;
    double  dr, k;

    dx = *ex - sx;
    dy = *ey - sy;
    dr = sqrt( dx * dx + dy * dy );
    if(len < dr)
    {
        k = len / dr;
        *ex = (SLONG)( sx + dx * k );
        *ey = (SLONG)( sy + dy * k );
    }
}


void    intercept_raster_line(SLONG sx, SLONG sy, SLONG *ex, SLONG *ey, SLONG len)
{
    SLONG   x1, y1, x2, y2;
    SLONG   dx,dy,dm,dn,m,n,k,u,v,l,sum;
    SLONG   dist, samp_dist;
    SLONG   last_x, last_y;

    x1 = sx, y1 = sy;
    x2 = *ex, y2 = *ey;
    dx = x2 - x1, dy = y2 - y1;

    last_x = sx;
    last_y = sy;
    samp_dist = len * len;
    dist = dx * dx + dy * dy;
    if(dist <= samp_dist)
    {
        return;
    }

    if(dx == 0)
    {
        if(dy < 0)
        {
            last_x = x1;
            last_y = y1 - len;
        }
        else
        {
            last_x = x1;
            last_y = y1 + len;
        }
        *ex = last_x;
        *ey = last_y;
        return;
    }

    if(dy == 0)
    {
        if(dx < 0)
        {
            last_x = x1 - len;
            last_y = y1;
        }
        else
        {
            last_x = x1 + len;
            last_y = y1;
        }
        *ex = last_x;
        *ey = last_y;
        return;
    }
    
    dm = dn = 1;
    if(dx < 0) dx = -dx, dm = -1;
    if(dy < 0) dy = -dy, dn = -1;
    m = dx, n = dy, k = 1, u = x1, v = y1;
    if(dx < dy) m = dy, n = dx, k = dm, dm = dn, dn = k, k = 0, u = y1, v = x1;
    l = 0;
    sum = m;
    //pixel (x1,y1)
    //omit here...
    while (sum != 0)
    {
        sum--;
        l += n;
        u += dm;
        if(l >= m)
        {
            v += dn;
            l -= m;
        }
        if(k == 1)
        {
            //pixel (u, v)
            dist = (u - x1) * (u - x1) + (v - y1) * (v - y1);
            if(dist <= samp_dist)
            {
                last_x = u;
                last_y = v;
            }
            else
            {
                break;
            }
        }
        else
        {
            //pixel (v, u)
            dist = (v - x1) * (v - x1) + (u - y1) * (u - y1);
            if(dist <= samp_dist)
            {
                last_x = v;
                last_y = u;
            }
            else
            {
                break;
            }
        }
    }
    *ex = last_x;
    *ey = last_y;
    return;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MASK PATH FUNCTIONS
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void    clear_mask_path(MASK_PATH *mp)
{
    mp->steps = 0;
}


SLONG   add_mask_path_step(MASK_PATH *mp, SLONG x, SLONG y)
{
    if(mp->steps < PATH_STEPS_NUM)
    {
        mp->pos[mp->steps].x = x;
        mp->pos[mp->steps].y = y;
        mp->steps ++;
        return TTN_OK;
    }
    return TTN_NOT_OK;
}


SLONG   beeline_find_step(SLONG sx, SLONG sy, SLONG *ex, SLONG *ey, SLONG speed, SLONG stop_mask, MAP_MASK *mm)
{
    SLONG   dx, dy; // difference x/y
    double  dr;     // difference distance
    double  k;      // distance ratio
    SLONG   tx, ty; // step target x/y
    SLONG   mask_sx, mask_sy, mask_tx, mask_ty; // mask position

    dx = *ex - sx;
    dy = *ey - sy;
    dr = sqrt(dx * dx + dy * dy);
    if(dr < speed)
        k = 1.0;
    else    
        k = speed / dr;
    tx = (SLONG)( sx + dx * k + 0.5 );  //intercept position
    ty = (SLONG)( sy + dy * k + 0.5 );  //
    mask_sx = sx / mm->sw;
    mask_sy = sy / mm->sh;
    mask_tx = tx / mm->sw;
    mask_ty = ty / mm->sh;
    if( mask_sx < 0 || mask_sx >= mm->w || mask_sy < 0 || mask_sy >= mm->h )
        return STEP_OUTSTRETCH;
    if( mask_tx < 0 || mask_tx >= mm->w || mask_ty < 0 || mask_ty >= mm->h )
        return STEP_OUTSTRETCH;
    // Jack,  [10:04,9/27/2002]
    /*
    if(TRUE == is_mask_line_through(mask_sx, mask_sy, mask_tx, mask_ty, stop_mask, mm) )
    {
        *ex = tx;
        *ey = ty;
        if(k == 1.0)
            return STEP_ARRIVE;
        else
            return STEP_ON_THE_WAY;
    }
    else
    {
        return STEP_OBSTRUCT;
    }
    */
    if(TTN_OK == find_mask_near_through_pixel(sx, sy, &tx, &ty, stop_mask, mm))
    {
        *ex = tx;
        *ey = ty;
        if(k == 1.0)
            return  STEP_ARRIVE;
        else
            return  STEP_ON_THE_WAY;
    }
    else
    {
        *ex = tx;
        *ey = ty;
        return  STEP_OBSTRUCT;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PATH FIND FUNCTIONS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
enum    WAY_ENUMS
{
//
VIA_STEPS           =   ( (SCREEN_WIDTH / MIN_MASK_WIDTH) * (SCREEN_HEIGHT / MIN_MASK_HEIGHT) ),
} WAY_ENUMS;

typedef struct  tagVIA_PATH
{
    SLONG   path_si;    //找到的路徑的開始地址(在path中的偏移位置)
    SLONG   path_ei;    //找到的路徑的結束地址(在path中的偏移位置)
    SLONG   start_si;   //起始點的開始地址(在path中的偏移位置)
    SLONG   start_ei;   //起始點的結束地址(在path中的偏移位置)
    SLONG   end_si;     //終點的開始地址(在path中的偏移位置)
    SLONG   end_ei;     //終點的結束地址(在path中的偏移位置)

    SLONG   start_x;    //start pixel position x
    SLONG   start_y;    //start pixel position y
    SLONG   target_x;   //target pixel position x
    SLONG   target_y;   //target pixel position y

    SLONG   mask_width;     //single mask pixel width
    SLONG   mask_height;    //single mask pixel height

    struct
    {
        SLONG x;        //stop mask x
        SLONG y;        //stop mask y
        SLONG dir;      //dir
        SLONG father;   //father node
    } step[VIA_STEPS];

} VIA_PATH, *LPVIA_PATH;



MASK_PATH   mask_path;
VIA_PATH    via_path;


SLONG   trend_find_via_path(SLONG sx, SLONG sy, SLONG ex, SLONG ey, SLONG stop_mask, MAP_MASK *mm)
{
    enum    {TEST_X = 0x01, TEST_Y = 0x02};
    SLONG   table_width, table_height, inner_width, inner_height;
    SLONG   ret;
    SLONG   mask_sx, mask_sy, mask_ex, mask_ey;
    SLONG   test_x, test_y;
    UCHR    stop, mask;
    SLONG   test_flag, need_test, last_test;
    SLONG   dx, dy;
    SLONG   trend_steps;

    table_width = mm->w;
    table_height = mm->h;
    inner_width = table_width - 1;
    inner_height = table_height - 1;

    mask_sx = sx / mm->sw;
    mask_sy = sy / mm->sh;
    mask_ex = ex / mm->sw;
    mask_ey = ey / mm->sh;

    if( mask_sx <= 0 || mask_sx >= inner_width || mask_sy <= 0 || mask_sy >= inner_height)
        return  PATH_ERROR;
    if( mask_ex <= 0 || mask_ex >= inner_width || mask_ey <= 0 || mask_ey >= inner_height)
        return  PATH_ERROR;

    stop = (UCHR)stop_mask;
    mask = get_map_mask(mm, mask_sx, mask_sy);
    if(mask & stop)
        return  PATH_ERROR;

    if(mask_sx == mask_ex && mask_sy == mask_ey) 
        return  PATH_ARRIVE;

    via_path.start_x = sx;
    via_path.start_y = sy;
    via_path.target_x = ex;
    via_path.target_y = ey;
    via_path.mask_width = mm->sw;
    via_path.mask_height = mm->sh;

    via_path.path_si = 0;
    via_path.step[0].x = mask_sx;
    via_path.step[0].y = mask_sy;
    via_path.path_ei = 1;

    test_x = mask_sx;
    test_y = mask_sy;

    test_flag = 0;
    if(test_x != mask_ex) 
        test_flag = TEST_X;
    else if(test_y != mask_ey) 
        test_flag = TEST_Y;

    trend_steps = 0;
    ret = PATH_NEAR;
    while(  test_x > 0 && test_x < inner_width &&   test_y > 0 && test_y < inner_height &&
            via_path.path_ei < VIA_STEPS)
    {
        last_test = 0;

        //every loop we will check x first, and then y.
        if( test_flag == TEST_X)
        {
            if(test_x > mask_ex)
            {
                mask = get_map_mask(mm, test_x-1, test_y);
                if( mask & stop )
                {
                    test_flag = TEST_Y;
                }
                else
                {
                    test_x --;
                    last_test = TEST_X;
                }
            }
            else if(test_x < mask_ex)
            {
                mask = get_map_mask(mm, test_x+1, test_y);
                if( mask & stop )
                {
                    test_flag = TEST_Y;
                }
                else
                {
                    test_x ++;
                    last_test = TEST_X;
                }
            }
            else
            {
                test_flag = TEST_Y;
            }
        }
        if(test_flag == TEST_Y)
        {
            if(test_y > mask_ey)
            {
                mask = get_map_mask(mm, test_x, test_y-1);
                if(! ( mask & stop ) )
                {
                    test_y --;
                    last_test = TEST_Y;
                }
            }
            else if(test_y < mask_ey)
            {
                mask = get_map_mask(mm, test_x, test_y+1);
                if(! ( mask & stop ) )
                {
                    test_y ++;
                    last_test = TEST_Y;
                }
            }
        }

        if( 0 == last_test )
        {
            if( test_x == mask_ex && test_y == mask_ey) 
                ret = PATH_FOUND;
            else if( trend_steps > 0)
                ret = PATH_NEAR;
            else
                ret = PATH_FAIL;
            break;
        }
        else
        {
            //append our path
            via_path.step[via_path.path_ei].x = test_x;
            via_path.step[via_path.path_ei].y = test_y;
            via_path.path_ei ++;

            //count our trend steps
            trend_steps ++;

            //ready for next loop, we test tilted first.
            dx = mask_ex - test_x;
            dy = mask_ey - test_y;
            need_test = 0;
            if( dx ) need_test |= TEST_X;
            if( dy ) need_test |= TEST_Y;
            if( last_test == TEST_X )
            {
                if (need_test & TEST_Y)
                    test_flag = TEST_Y;
            }
            if( last_test == TEST_Y )
            {
                if( need_test & TEST_X )
                    test_flag = TEST_X;
            }
        }
        //if we want to show the process, unmarked the following part.
        /* 
        via_path.path_si = 0;
        via_path.path_ei--;
        redraw_via_path();
        via_path.path_ei++;
        update_screen( screen_buffer );
        */
    }
    return  ret;
}


void    via_path_to_mask_path ( SLONG stop_mask, MAP_MASK *mm )
{
    SLONG   i, next;
    SLONG   result;

    next = 1;
    for(i = next+1 ; i < via_path.path_ei; i++ )
    {
        result = is_mask_line_through( via_path.step[next-1].x, via_path.step[next-1].y,
            via_path.step[i].x, via_path.step[i].y, 
            stop_mask, mm);
        if(TRUE != result)
            next++;
        via_path.step[next].x = via_path.step[i].x;
        via_path.step[next].y = via_path.step[i].y;
    }
    via_path.path_ei = next;

    //mask_path.pos[0].x = via_path.start_x;
    //mask_path.pos[0].y = via_path.start_y;
    mask_path.pos[0].x = via_path.step[0].x * mm->sw + mm->sw / 2;
    mask_path.pos[0].y = via_path.step[0].y * mm->sh + mm->sh / 2;

    next = 1;
    for( i=1; i <= via_path.path_ei; i++ )
    {
        mask_path.pos[next].x = via_path.step[i].x * mm->sw + mm->sw / 2;
        mask_path.pos[next].y = via_path.step[i].y * mm->sh + mm->sh / 2;
        next ++;
    }
    mask_path.steps = next;
}


void    via_path_find_first_point(SLONG *point_x, SLONG *point_y, SLONG stop_mask, MAP_MASK *mm)
{
    SLONG   test_x, test_y;
    SLONG   i, through;
    SLONG   result;
    SLONG   mask_width, mask_height;

    mask_width = via_path.mask_width;
    mask_height = via_path.mask_height;
    through = 0;
    for( i = 1; i < via_path.path_ei; i++ )
    {
        result = is_pixel_line_through( via_path.start_x, via_path.start_y,
            via_path.step[i].x * mask_width + mask_width/2, via_path.step[i].y * mask_height + mask_height / 2, 
            stop_mask, mm);
        if(TRUE == result)
        {
            through = i;
        }
    }
    test_x = via_path.step[through].x;
    test_y = via_path.step[through].y;
    *point_x = test_x * mask_width + mask_width/2;
    *point_y = test_y * mask_height + mask_height/2;

    mask_path.pos[0].x = via_path.start_x;
    mask_path.pos[0].y = via_path.start_y;
    mask_path.pos[1].x = test_x * mask_width + mask_width/2;
    mask_path.pos[1].y = test_y * mask_height + mask_height/2;
    mask_path.steps = 2;
}


SLONG   trend_find_step(SLONG sx, SLONG sy, SLONG *ex, SLONG *ey, SLONG speed, SLONG stop_mask, MAP_MASK *mm)
{
    SLONG   result;
    SLONG   first_x, first_y;
    SLONG   ret;

    //TODO: can be optimized for we have trend_find_via_path twice.
    result = trend_find_via_path(sx, sy, *ex, *ey, stop_mask, mm);
    if(result != PATH_ARRIVE && result != PATH_FOUND)
    {
        result = diffuse_find_via_path(sx, sy, *ex, *ey, stop_mask, mm);
    }
    if(result != PATH_ARRIVE && result != PATH_FOUND)
    {
        result = trend_find_via_path(sx, sy, *ex, *ey, stop_mask, mm);
    }

    switch(result)
    {
    case PATH_ARRIVE:
        ret = STEP_ARRIVE;
        break;
    case PATH_FOUND:
    case PATH_NEAR:
        {
            via_path_find_first_point(&first_x, &first_y, stop_mask, mm);
            intercept_raster_line(sx, sy, &first_x, &first_y, speed);
            *ex = first_x;
            *ey = first_y;
            ret = STEP_ON_THE_WAY;
            break;
        }
    case PATH_FAIL:
        {
            ret = STEP_OBSTRUCT;
            break;
        }
    case PATH_ERROR:
        {
            ret = STEP_OUTSTRETCH;
            break;
        }
    }
    return  ret;
}



//A*算法搜索
SLONG   astar_find_via_path(SLONG sx, SLONG sy, SLONG ex, SLONG ey, SLONG stop_mask, MAP_MASK *mm)
{
    return  TTN_NOT_OK;
}


//深度優先搜索
SLONG   dfs_find_via_path(SLONG sx, SLONG sy, SLONG ex, SLONG ey, SLONG stop_mask, MAP_MASK *mm)
{
    return  TTN_NOT_OK;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 兩點擴散搜索
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define DIRHV4

#define XPATH_MASK_SOURCE           0x01000000      // is source pos
#define XPATH_MASK_TARGET           0x02000000      // is target pos
#define XPATH_MASK_FROM_SOURCE      0x04000000      // is diffuse from source pos
#define XPATH_MASK_FROM_TARGET      0x08000000      // is diffuse from target pos
#define XPATH_MASK_FROM_WHO         0x0C000000      // is from who ?
#define XPATH_MASK_STOP             0x10000000      // is stop pos
#define XPATH_MASK_PATH             0x20000000      // is the find path
#define XPATH_MASK_OFFSET           0x00ffffff      // offset

#define XPATH_TABLE_WIDTH           (SCREEN_WIDTH / MIN_MASK_WIDTH)
#define XPATH_TABLE_HEIGHT          (SCREEN_HEIGHT / MIN_MASK_HEIGHT)
#define XPATH_TABLE_SIZE            (XPATH_TABLE_WIDTH * XPATH_TABLE_HEIGHT)

#define XPATH_MAKE_OFFSET(x,y)      ((y) * XPATH_TABLE_WIDTH + (x))
#define XPATH_GET_X(offset)         ((offset) % XPATH_TABLE_WIDTH )
#define XPATH_GET_Y(offset)         ((offset) / XPATH_TABLE_WIDTH )
#define XPATH_FATHER_OFFSET(offset) (xpath_mask[XPATH_GET_Y((offset) & XPATH_MASK_OFFSET)][XPATH_GET_X( (offset) & XPATH_MASK_OFFSET)] & XPATH_MASK_OFFSET)

ULONG   xpath_mask [XPATH_TABLE_HEIGHT][XPATH_TABLE_WIDTH];
ULONG   xpath_stack[XPATH_TABLE_SIZE];


#define XPATHPROCESS(x,y)                                                               \
{                                                                                       \
    pmask = &xpath_mask[(y)][(x)];                                                      \
    if(!(*pmask & XPATH_MASK_STOP )) /* not stop */                                     \
    {                                                                                   \
        if(!(*pmask & from_who))  /* not from the current  */                           \
        {                                                                               \
            if(*pmask & from_other)  /* have been from the other, found meet pos */     \
            {                                                                           \
                offset2 = *pmask;       /* backup the meet mask */                      \
                *pmask &= ~XPATH_MASK_OFFSET;                                           \
                *pmask |= from_who | offset;                                            \
                xpath_stack[xpath_to ++] = XPATH_MAKE_OFFSET((x),(y));                  \
                find = TRUE;                                                            \
            }                                                                           \
            else    /* is a fresh pos */                                                \
            {                                                                           \
                *pmask |= from_who | offset;                                            \
                xpath_stack[xpath_to ++] = XPATH_MAKE_OFFSET((x),(y));                  \
            }                                                                           \
        }                                                                               \
    }                                                                                   \
}



SLONG   diffuse_find_via_path(SLONG sx, SLONG sy, SLONG ex, SLONG ey, SLONG stop_mask, MAP_MASK *mm)
{
    SLONG   main_pass;
    SLONG   xpath_to, xpath_from;
    ULONG   offset, offset2, temp_offset;
    ULONG   source_offset, target_offset;
    SLONG   x, y;
    ULONG   mask, *pmask, from_who, from_other;
    SLONG   find;
    SLONG   mask_sx, mask_sy, mask_ex, mask_ey;
    SLONG   consult_x, consult_y, mask_rx, mask_ry;
    SLONG   relate_sx, relate_sy, relate_ex, relate_ey;
    UCHR    temp_map_mask;

    mask_sx = sx / mm->sw;
    mask_sy = sy / mm->sh;
    mask_ex = ex / mm->sw;
    mask_ey = ey / mm->sh;

    //except the status of out-of-range.
    if( mask_sx < 0 || mask_sx >= mm->w || mask_sy < 0 || mask_sy >= mm->h)
        return  PATH_ERROR;
    if( mask_ex < 0 || mask_ex >= mm->w || mask_ey < 0 || mask_ey >= mm->h)
        return  PATH_ERROR;

    if(mask_sx == mask_ex && mask_sy == mask_ey) 
        return  PATH_ARRIVE;

    //except the status by our diffuse method.
    temp_map_mask = get_map_mask(mm, mask_sx, mask_sy);
    if( temp_map_mask & stop_mask )
        return  PATH_FAIL;

    temp_map_mask = get_map_mask(mm, mask_ex, mask_ey);
    if( temp_map_mask & stop_mask )
        return  PATH_FAIL;

    consult_x = (mask_sx + mask_ex) / 2 - XPATH_TABLE_WIDTH / 2;
    if(consult_x > mm->w - XPATH_TABLE_WIDTH)
        consult_x = mm->w - XPATH_TABLE_WIDTH;
    if(consult_x < 0)
        consult_x = 0;
    consult_y = (mask_sy + mask_ey) / 2 - XPATH_TABLE_HEIGHT / 2;
    if(consult_y > mm->h - XPATH_TABLE_HEIGHT)
        consult_y = mm->h - XPATH_TABLE_HEIGHT;
    if(consult_y < 0)
        consult_y = 0;

    relate_sx = mask_sx - consult_x;
    relate_sy = mask_sy - consult_y;
    relate_ex = mask_ex - consult_x;
    relate_ey = mask_ey - consult_y;
    if(relate_sx < 0 || relate_sx >= XPATH_TABLE_WIDTH || relate_sy < 0 || relate_sy >= XPATH_TABLE_HEIGHT)
        return PATH_ERROR;
    if(relate_ex < 0 || relate_ex >= XPATH_TABLE_WIDTH || relate_ey < 0 || relate_ey >= XPATH_TABLE_HEIGHT)
        return PATH_ERROR;

    memset( xpath_mask, 0, XPATH_TABLE_HEIGHT * XPATH_TABLE_WIDTH * sizeof(ULONG) );
    for(y=0; y<XPATH_TABLE_HEIGHT; y++)
    {
        mask_ry = consult_y + y;
        if(mask_ry >= mm->h)
            break;
        for(x=0; x<XPATH_TABLE_WIDTH; x++)
        {
            mask_rx = consult_x + x;
            if(mask_rx >= mm->w)
                break;

            temp_map_mask = get_map_mask(mm, mask_rx, mask_ry);
            if(temp_map_mask & stop_mask)
                xpath_mask[y][x] = XPATH_MASK_STOP;
        }
    }

    source_offset = XPATH_MAKE_OFFSET(relate_sx, relate_sy);
    target_offset = XPATH_MAKE_OFFSET(relate_ex, relate_ey);
    xpath_mask[relate_sy][relate_sx] |= XPATH_MASK_SOURCE | XPATH_MASK_FROM_SOURCE | source_offset;
    xpath_mask[relate_ey][relate_ex] |= XPATH_MASK_TARGET | XPATH_MASK_FROM_TARGET | target_offset;
    xpath_to = xpath_from = 0;
    xpath_stack[xpath_to++] = source_offset;
    xpath_stack[xpath_to++] = target_offset;
    find = FALSE;
    main_pass = 0;
    while( 0 == main_pass)
    {
        offset = xpath_stack[xpath_from ++] & XPATH_MASK_OFFSET;
        x = XPATH_GET_X(offset);
        y = XPATH_GET_Y(offset);
        mask = xpath_mask[y][x];
        from_who = mask & XPATH_MASK_FROM_WHO;
        from_other = ~from_who & XPATH_MASK_FROM_WHO;

        // have found the meeting position
        if(from_who == XPATH_MASK_FROM_WHO)
        { 
            find = TRUE;
            break; 
        }
        if(x > 0 && FALSE == find)
            XPATHPROCESS(x-1, y);
        if(y > 0 && FALSE == find)
            XPATHPROCESS(x, y-1);
        if(x < XPATH_TABLE_WIDTH-1 && FALSE == find) 
            XPATHPROCESS(x+1, y);
        if(y < XPATH_TABLE_HEIGHT-1 && FALSE == find)
            XPATHPROCESS(x, y+1);

        // overflow, find failed.
        if(xpath_from >= xpath_to) 
            break;
    }
    
    // retrospect the found path by xpath mask table
    if(TRUE == find)
    {
        //make offset for source retrospect & offset2 for target retrospect.
        if(offset2 & XPATH_MASK_FROM_SOURCE)
        {
            temp_offset = offset2;
            offset2 = offset;
            offset = temp_offset;
        }
        offset &= XPATH_MASK_OFFSET;
        offset2 &= XPATH_MASK_OFFSET;

        //cut xpath_stack to 2 half, decrease for xpath_from & increase for xpath_to.
        xpath_from = XPATH_TABLE_SIZE / 2;
        while(offset != source_offset)
        {
            xpath_stack[xpath_from --] = offset;
            offset = XPATH_FATHER_OFFSET(offset);
        }
        xpath_stack[xpath_from] = source_offset;

        xpath_to = XPATH_TABLE_SIZE / 2 + 1;
        while(offset2 != target_offset)
        {
            xpath_stack[xpath_to++] = offset2;
            offset2 = XPATH_FATHER_OFFSET(offset2);
        }
        xpath_stack[xpath_to++] = target_offset;

        //if we want mark our found path, just use the following code.
        /*
        for(x = path_from; x < xpath_to; x++)
        {
            offset = xpath_stack[x];
            xpath_mask[XPATH_GET_Y(offset)][XPATH_GET_X(offset)] |= XPATH_MASK_PATH;
        }
        */

        //update found path to via_path
        via_path.start_x = sx;
        via_path.start_y = sy;
        via_path.target_x = ex;
        via_path.target_y = ey;

        via_path.path_si = 0;
        via_path.path_ei = xpath_to - xpath_from;
        for(x = xpath_from; x < xpath_to; x++)
        {
            offset = xpath_stack[x];
            via_path.step[x - xpath_from].x = XPATH_GET_X(offset) + consult_x;
            via_path.step[x - xpath_from].y = XPATH_GET_Y(offset) + consult_y;
        }
        return PATH_FOUND;
    }
    return PATH_FAIL;
}


/************************************************************************************************************/
/* MASK NPC FUNCTIONS                                                                                       */
/************************************************************************************************************/
void	GatherMapCharacterMaskPosition(void)
{
	SLONG	npc_no, npc_hp, npc_x, npc_y, npc_z;
	SLONG	mask_x, mask_y, mask_index;
    SLONG   is_available;

	mask_index = 0;
	for(npc_no=0; npc_no < MAX_CHARACTER_PER_ZONE; npc_no ++)
	{
        LOCK_CHARACTER(npc_no);
        is_available = IsCharacterAvailable(npc_no);
        GetCharacterPosition(npc_no, &npc_x, &npc_y, &npc_z);
        npc_hp = GetCharacterHp(npc_no);
        UNLOCK_CHARACTER(npc_no);
        
        if(is_available && npc_hp > 0)
        {
            mask_x = npc_x / l_MapMask->sw;
            mask_y = npc_y / l_MapMask->sh;
            
            l_MaskNpc.npc_mask_x[mask_index] = mask_x;
            l_MaskNpc.npc_mask_y[mask_index] = mask_y;
            mask_index ++;
        }
	}
	l_MaskNpc.mask_npcs = mask_index;

	return;
}

void	UpdateMapCharacterMask(void)
{
	SLONG	i, j, mask_x, mask_y, mask_cx, mask_cy;
	SLONG	off_x[9] = {-1, 0, 1,-1, 0, 1,-1, 0, 1};
	SLONG	off_y[9] = {-1,-1,-1, 0, 0, 0, 1, 1, 1};

	for(i = 0; i < l_MaskNpc.mask_npcs; i ++)
	{
		mask_cx = l_MaskNpc.npc_mask_x[i];
		mask_cy = l_MaskNpc.npc_mask_y[i];
		//for(j = 0; j < 9; j++)
		j = 4;
		{
			mask_x = mask_cx + off_x[j];
			mask_y = mask_cy + off_y[j];
			if(mask_x >= 0 && mask_x < l_MapMask->w && mask_y >= 0 && mask_y < l_MapMask->h )
			{
				or_map_mask(l_MapMask, mask_x, mask_y, MASK_DYNAMIC_NPC);
			}
		}
	}
	return;
}

void	RemoveMapCharacterMask(void)
{
	SLONG	i, j, mask_cx, mask_cy, mask_x, mask_y;
	SLONG	off_x[9] = {-1, 0, 1,-1, 0, 1,-1, 0, 1};
	SLONG	off_y[9] = {-1,-1,-1, 0, 0, 0, 1, 1, 1};

	for(i = 0; i<l_MaskNpc.mask_npcs; i ++)
	{
		mask_cx = l_MaskNpc.npc_mask_x[i];
		mask_cy = l_MaskNpc.npc_mask_y[i];
		//for(j = 0; j < 9; j++)
		j = 4;
		{
			mask_x = mask_cx + off_x[j];
			mask_y = mask_cy + off_y[j];
			if(mask_x >= 0 && mask_x < l_MapMask->w && mask_y >= 0 && mask_y < l_MapMask->h )
			{
				remove_map_mask(l_MapMask, mask_x, mask_y, MASK_DYNAMIC_NPC);
			}
		}
	}
	return;
}

void	ClearMapDynamicCharacterMask(SLONG pix_x, SLONG pix_y)
{
	SLONG	j, mask_cx, mask_cy, mask_x, mask_y;
	SLONG	off_x[9] = {-1, 0, 1,-1, 0, 1,-1, 0, 1};
	SLONG	off_y[9] = {-1,-1,-1, 0, 0, 0, 1, 1, 1};

	mask_cx = pix_x / l_MapMask->sw;
	mask_cy = pix_y / l_MapMask->sh;

	//for(j = 0; j < 9; j++)
	j = 4;
	{
		mask_x = mask_cx + off_x[j];
		mask_y = mask_cy + off_y[j];
		if(mask_x >= 0 && mask_x < l_MapMask->w && mask_y >= 0 && mask_y < l_MapMask->h )
		{
			remove_map_mask(l_MapMask, mask_x, mask_y, MASK_DYNAMIC_NPC);
		}
	}

	return;
}

SLONG	FindBestAttackPosition(SLONG x, SLONG y, SLONG dest_x, SLONG dest_y, SLONG attack_distance, SLONG *attack_x, SLONG *attack_y)
{
	SLONG	mask_cx, mask_cy;
	SLONG	mask_x, mask_y;
	SLONG	find_x, find_y;
	SLONG	mask_px, mask_py;
	SLONG	near_distance, min_near_distance;
	SLONG	walk_distance2, min_walk_distance2;
	SLONG	best_x, best_y, find_best;
	SLONG	i;
	UCHR	mask;

	mask_cx = dest_x / l_MapMask->sw;
	mask_cy = dest_y / l_MapMask->sh;

	min_walk_distance2 = 999999;
	min_near_distance = 999999;

	best_x = x;
	best_y = y;
	find_best = TTN_NOT_OK;
	for(i = 4; i < 64; i ++)	//4 ~ 64 for 3 circles(4~15, 16~35, 36~63).
	{
		WindingAttackAxisPosition(i, &find_x, &find_y);
		mask_x = mask_cx + find_x;
		mask_y = mask_cy + find_y;
		if( mask_x >= 0 && mask_x < l_MapMask->w && 
			mask_y >= 0 && mask_y < l_MapMask->h )
		{
			mask = get_map_mask(l_MapMask, mask_x, mask_y);
			if(mask & MASK_DYNAMIC_NPC)
				continue;

			mask_px = mask_x * l_MapMask->sw + l_MapMask->sw / 2;
			mask_py = mask_y * l_MapMask->sh + l_MapMask->sh / 2;

			near_distance = MAX( abs(mask_x - mask_cx), abs(mask_y - mask_cy) );	// circle radius for distance.
			if(near_distance > min_near_distance)
				continue;
			else if(near_distance < min_near_distance)
			{
				min_near_distance = near_distance;
				best_x = mask_px;
				best_y = mask_py;
				find_best = TTN_OK;
			}
			else //near_distance == min_near_distance
			{
				walk_distance2 = (mask_px - x) * (mask_px - x) + (mask_py - y) * (mask_py - y);
				if(walk_distance2 < min_walk_distance2)
				{
					min_walk_distance2 = walk_distance2;
					best_x = mask_px;
					best_y = mask_py;
					find_best = TTN_OK;
				}
			}
		}
	}

	*attack_x = best_x;
	*attack_y = best_y;

	return	find_best;
}


SLONG   FindCharacterStep(SLONG x, SLONG y, SLONG *dest_x, SLONG *dest_y, SLONG move_speed)
{
    SLONG   ret;

    //gather_map_npc_mask_position(map_no);
    //update_map_npc_mask(map_no);
    //clear_map_dynamic_npc_mask( map_no, x, y );
    //ret = trend_find_step( x, y, dest_x, dest_y, move_speed, MASK_STOP | MASK_DYNAMIC_NPC, map_base[map_no].mask);
    //remove_map_npc_mask(map_no);

    ret = trend_find_step( x, y, dest_x, dest_y, move_speed, MASK_STOP, l_MapMask);

    return  ret;
}


SLONG   FindCharacterMaskStep(SLONG x, SLONG y, SLONG *dest_x, SLONG *dest_y, SLONG move_speed, SLONG stop)
{
	SLONG	ret;
    ret = trend_find_step( x, y, dest_x, dest_y, move_speed, stop, l_MapMask);
	return	ret;
}


SLONG   FindCharacterBeelineStep(SLONG x, SLONG y, SLONG *dest_x, SLONG *dest_y, SLONG move_speed)
{
	SLONG	ret;
    ret = beeline_find_step( x, y, dest_x, dest_y, move_speed, MASK_STOP, l_MapMask);
	return	ret;
}

SLONG	TrendFindCharacterStep(SLONG sx, SLONG sy, SLONG *ex, SLONG *ey, SLONG speed, SLONG stop_mask)
{
	SLONG	ret;
	ret = trend_find_step(sx, sy, ex, ey, speed, stop_mask, l_MapMask);
	return	ret;
}


SLONG   IsPixelMaskMatch(SLONG pixel_x, SLONG pixel_y, SLONG check_mask)
{
	return	is_pixel_mask_match(pixel_x, pixel_y, check_mask, l_MapMask);
}

SLONG   FindMaskNearThroughPixel(SLONG pixel_sx, SLONG pixel_sy, SLONG *pixel_ex, SLONG *pixel_ey, SLONG stop_mask)
{
	return	find_mask_near_through_pixel(pixel_sx, pixel_sy, pixel_ex, pixel_ey, stop_mask, l_MapMask);
}

SLONG   IsPixelLineThrough(SLONG x1, SLONG y1, SLONG x2, SLONG y2, SLONG stop_mask)
{
	return	is_pixel_line_through(x1, y1, x2, y2, stop_mask, l_MapMask);
}

SLONG	IsPixelMaskStop(SLONG x, SLONG y)
{
	return	is_pixel_mask_stop(x, y, l_MapMask);
}

/************************************************************************************************************/
/* MAP MASK LOAD & FREE FUNCTIONS                                                                           */
/************************************************************************************************************/
SLONG	LoadZoneMapMask(CHAR *szFileName)
{
	SLONG	ret;

	ret = TTN_OK;
    l_MapMask = load_map_mask((USTR *)szFileName);
    if(NULL == l_MapMask)
    {
		log_error(1, "load map mask %s error", szFileName);
		ret = TTN_NOT_OK;
    }
	return	ret;
}


void	FreeZoneMapMask(void)
{
	if(l_MapMask)
	{
		destroy_map_mask(&l_MapMask);
	}
}


MAP_MASK *	GetZoneMapMask(void)
{
	return	l_MapMask;
}
