/*
**  maptrack.cpp
**  map track functions.
**
**  zjian,2001.5.24.
*/
#include "mainfun.h"
#include "maptrack.h"



MAP_TRACK   map_track[MAX_MAP_TRACK];
TRACK_CON   track_con[MAX_TRACK_CON];




//----------------------------------------------------------------------------------------------------------------
// map track system functions
//----------------------------------------------------------------------------------------------------------------
SLONG   init_map_track_system(void)
{
    init_all_map_tracks();
    init_all_track_cons();
    return TTN_OK;
}


void    free_map_track_system(void)
{
    free_all_track_cons();
    free_all_map_tracks();
}


//----------------------------------------------------------------------------------------------------------------
// map track functions
//----------------------------------------------------------------------------------------------------------------
void    init_all_map_tracks(void)
{
    SLONG   i;
    for(i=0; i<MAX_MAP_TRACK; i++)
    {
        map_track[i].flag = 0;
        map_track[i].type = 0;
        map_track[i].con = -1;
        map_track[i].x = 0;
        map_track[i].y = 0;
        map_track[i].z = 0;
        map_track[i].frame = 0;
        map_track[i].tick = 0;
        map_track[i].ltick = 9999;
    }
}


void    free_all_map_tracks(void)
{
}


SLONG   add_map_track(SLONG type, SLONG x, SLONG y, SLONG z, SLONG limited_tick, USTR *filename)
{
    SLONG   track_index;
    SLONG   i;

    track_index = -1;
    for(i=0; i<MAX_MAP_TRACK; i++)
    {
        if(map_track[i].flag == 0)
        {
            track_index = i;
            break;
        }
    }
    if(track_index >= 0)
    {
        map_track[track_index].type = type;
        map_track[track_index].x = x;
        map_track[track_index].y = y;
        map_track[track_index].z = z;
        map_track[track_index].ltick = limited_tick;

        if(NULL == filename)
        {
            map_track[track_index].con = -1;
        }
        else
        {
            map_track[track_index].con = reference_track_con((USTR *)filename);
        }

        //set internal default data
        map_track[track_index].tick = 0;
        map_track[track_index].frame = 0;
        map_track[track_index].flag = 1;
    }
    return track_index;
}


SLONG   del_map_track(SLONG track_index)
{
    map_track[track_index].flag = 0;
    if(map_track[track_index].con >= 0)
    {
        release_track_con(map_track[track_index].con);
        map_track[track_index].con = -1;
    }
    return TTN_OK;
}


void    refresh_map_track(void)
{
    SLONG   i;
    SLONG   con_index, frames;

    if(map_track_timer_tick>MAP_TRACK_REFRESH_SPEED)
    {
        for(i=0; i<MAX_MAP_TRACK; i++)
        {
            if(map_track[i].flag)
            {
                map_track[i].tick ++;
                if(map_track[i].tick > map_track[i].ltick)
                {
                    con_index = map_track[i].con;
                    if(con_index >= 0)
                        frames = get_track_con_total_frames(con_index);
                    else
                        frames = 8; // give it a sample frames for sample-show

                    switch(map_track[i].type)
                    {
                    case MTT_ONCE:
                        {
                            map_track[i].frame++;
                            if(map_track[i].frame >= frames)
                            {
                                del_map_track(i);
                            }
                            break;
                        }
                    case MTT_KEEP:
                        {
                            map_track[i].frame++;
                            if(map_track[i].frame >= frames)
                                map_track[i].frame = frames-1;
                            break;
                        }
                    case MTT_LOOP:
                        {
                            map_track[i].frame++;
                            if(map_track[i].frame >= frames)
                                map_track[i].frame = 0;
                            break;
                        }
                    default:
                        break;
                    }

                    map_track[i].tick = 0;
                }
            }
        }
        //
        map_track_timer_tick = 0;
    }

}


void    redraw_map_track_layer(SLONG view_sx, SLONG view_sy, BMP *bitmap)
{
    SLONG   i;
    SLONG   sx,sy;
	//SLONG	ex,ey;
    SLONG   x,y;
    SLONG   rx0,ry0;
    CAKE_FRAME  *cf = NULL;
    RLE *rle = NULL;
    //SLONG   combine_sx, combine_sy, combine_xl, combine_yl;
    SLONG   frame,con_index;

    for(i=0; i<MAX_MAP_TRACK; i++)
    {
        if(map_track[i].flag)
        {
            sx = map_track[i].x - view_sx;
            sy = map_track[i].y - view_sy;
            con_index = map_track[i].con;
            frame = map_track[i].frame;

            if(con_index >= 0)
            {
                cf = get_track_con_frame(con_index, frame, &rx0, &ry0); 
                if(cf)
                {
                    rle = cf->rle;
                    if(rle)
                    {
                        x = sx-cf->poly_rx;
                        y = sy-cf->poly_ry;
                        //
                        //get_track_con_combine(map_track[i].con, &combine_sx, &combine_sy, &combine_xl, &combine_yl);
                        //sx += (cf->frame_rx - rx0 );
                        //sy += (cf->frame_ry - ry0);
                        //sx -= combine_xl/2; //center adjust
                        //sy -= combine_yl/2;
                        //ex = sx + rle->w;
                        //ey = sy + rle->h;
                        //if( sx < SCREEN_WIDTH && sy < SCREEN_HEIGHT && ex >= 0 && ey >= 0 )
                        {
                            additive_put_rle(x, y, rle, bitmap);
                        }
                    }
                }
            }
            else
            {
                put_ellipse(sx-1, sy, (2 + frame) * 2,  (2 + frame), SYSTEM_BLACK, bitmap);
                put_ellipse(sx, sy-1, (2 + frame) * 2,  (2 + frame), SYSTEM_BLACK, bitmap);
                put_ellipse(sx+1, sy, (2 + frame) * 2,  (2 + frame), SYSTEM_BLACK, bitmap);
                put_ellipse(sx, sy+1, (2 + frame) * 2,  (2 + frame), SYSTEM_BLACK, bitmap);
                put_ellipse(sx, sy, (2 + frame) * 2,  (2 + frame), SYSTEM_WHITE, bitmap);
            }
        }
    }
}




//-----------------------------------------------------------------------------------------------------------------
// track container(track_con) functions
//-----------------------------------------------------------------------------------------------------------------
void    init_all_track_cons(void)
{
    SLONG   i;
    for(i=0; i<MAX_TRACK_CON; i++)
    {
        track_con[i].cfa = NULL;
        track_con[i].ref = 0;
        strcpy((char *)track_con[i].filename,"none.cak");
        track_con[i].frames = 0;
        track_con[i].sx = 0;
        track_con[i].sy = 0;
        track_con[i].xl = 0;
        track_con[i].yl = 0;
    }
}


void    free_all_track_cons(void)
{
    SLONG   i;
    for(i=0; i<MAX_TRACK_CON; i++)
    {
        if(track_con[i].cfa)
        {
            destroy_cake_frame_ani( &track_con[i].cfa );
        }
    }
}


SLONG   reference_track_con(USTR *in_filename)
{
    static  USTR filename[MAX_PATH];
    SLONG   empty_index;
    SLONG   exist_index;
    SLONG   i;
    //
    strcpy( (char *)filename,(char *)in_filename);
    strupr((char *)filename);
    //
    empty_index = -1;
    exist_index = -1;
    for(i=0; i<MAX_TRACK_CON; i++)
    {
        if( track_con[i].cfa )
        {
            if(0 == strcmpi( (const char*)filename, 
                (const char *)track_con[i].filename ) )
            {
                exist_index = i;
                break;
            }
        }
        else
        {
            if(empty_index < 0)
                empty_index = i;
        }
    }
    if(exist_index >= 0)    //has been loaded by others
    {
        track_con[exist_index].ref ++;
        return exist_index;
    }
    if(empty_index >= 0)    //need our's loading
    {
        if(TTN_OK == load_cake_frame_ani_from_file((USTR*)filename, &track_con[empty_index].cfa) )
        {
            CAKE_FRAME_ANI *p=NULL;
            CAKE_FRAME *cf=NULL;
            RLE *rle=NULL;
            SLONG sx,sy,ex,ey;

            track_con[empty_index].frames = count_cake_frames(track_con[empty_index].cfa);
            strcpy((char *)track_con[empty_index].filename, (const char *)filename);
            track_con[empty_index].ref = 1;

            sx = sy = 99999;
            ex = ey = 0;
            p = track_con[empty_index].cfa->next;
            while(p)
            {
                cf = p->cake_frame;
                if(cf)
                {
                    rle = cf->rle;
                    if(rle)
                    {
                        if(sx > cf->frame_rx) sx = cf->frame_rx;
                        if(sy > cf->frame_ry) sy = cf->frame_ry;
                        if(ex < cf->frame_rx + rle->w) ex = cf->frame_rx + rle->w;
                        if(ey < cf->frame_ry + rle->h) ey = cf->frame_ry + rle->h;
                    }
                }
                p = p->next;
            }
            if( (sx >= ex) || (sy >= ey) ) sx = ex = sy = ey = 0;

            track_con[empty_index].sx = sx;
            track_con[empty_index].sy = sy;
            track_con[empty_index].xl = ex - sx;
            track_con[empty_index].yl = ey - sy;

            return empty_index;
        }
    }
    return -1;
}


void    release_track_con(SLONG con_index)
{
    if(track_con[con_index].ref > 0)
    {
        track_con[con_index].ref-- ;
        if(track_con[con_index].ref == 0)
        {
            destroy_cake_frame_ani( &track_con[con_index].cfa );
            track_con[con_index].cfa = NULL;
            strcpy((char *)track_con[con_index].filename,"none.cak");
            track_con[con_index].frames = 0;
            track_con[con_index].sx = 0;
            track_con[con_index].sy = 0;
            track_con[con_index].xl = 0;
            track_con[con_index].yl = 0;
        }
    }
}


CAKE_FRAME *    get_track_con_frame(SLONG con_index, SLONG frame, SLONG *rx0, SLONG *ry0)
{
    CAKE_FRAME *cf = NULL;
    CAKE_FRAME_ANI *p=NULL;

    if(! track_con[con_index].cfa)
        return NULL;
    p = track_con[con_index].cfa->next;
    if(p->cake_frame)
    {
        *rx0 = p->cake_frame->frame_rx;
        *ry0 = p->cake_frame->frame_ry;
    }
    p = get_specify_cake_frame_ani(track_con[con_index].cfa, frame);
    if(p) cf = p->cake_frame;
    return cf;
}


void    get_track_con_combine(SLONG con_index, SLONG *sx, SLONG *sy, SLONG *xl, SLONG *yl)
{
    *sx = track_con[con_index].sx;
    *sy = track_con[con_index].sy;
    *xl = track_con[con_index].xl;
    *yl = track_con[con_index].yl;
}


SLONG   get_track_con_total_frames(SLONG con_index)
{
    return track_con[con_index].frames;
}

