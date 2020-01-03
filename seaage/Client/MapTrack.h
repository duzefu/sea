/*
**  maptrack.h
**  map track functions header.
**
**  zjian,2001.5.24.
*/
#ifndef _MAPTRACK_H_INCLUDE_
#define _MAPTRACK_H_INCLUDE_
#include "xcak.h"

#define map_track_timer_tick       timer_tick08
#define MAP_TRACK_REFRESH_SPEED    4   // ticks

//0x2072667
#define MAX_MAP_TRACK       1024
#define MAX_TRACK_CON       1024


//map track types
#define MTT_ONCE    1   //play track once, then delete itself.
#define MTT_KEEP    2   //play track and keep the last frame.
#define MTT_LOOP    3   //play track loop.


//map track struct
typedef struct  tagMAP_TRACK
{
    SLONG   flag;       //on,off flag
    SLONG   type;       //map track types, MTT_*
    SLONG   con;        //track con index
    SLONG   x;          //position x
    SLONG   y;          //position y
    SLONG   z;          //position z
    SLONG   frame;      //current image frame
    SLONG   tick;       //refresh tick counter
    SLONG   ltick;      //limited ticks
} MAP_TRACK, *LPMAP_TRACK;


//track container struct
typedef struct  tagTRACK_CON
{
    USTR    filename[80];   //track image ani filename
    SLONG   ref;            //reference times
    CAKE_FRAME_ANI  *cfa;   //image cak
    SLONG   frames;         //image cak frames
    SLONG   sx;             //image cak first frame rx
    SLONG   sy;             //image cak first frame ry
    SLONG   xl;             //image cak combine xl
    SLONG   yl;             //image cak combine yl
} TRACK_CON, *LPTRACK_CON;


extern  SLONG   init_map_track_system(void);
extern  void    free_map_track_system(void);

extern  void    init_all_map_tracks(void);
extern  void    free_all_map_tracks(void);
extern  SLONG   add_map_track(SLONG type, SLONG x, SLONG y, SLONG z, SLONG limited_tick, USTR *filename);
extern  SLONG   del_map_track(SLONG track_index);
extern  void    refresh_map_track(void);
extern  void    redraw_map_track_layer(SLONG view_sx, SLONG view_sy, BMP *bitmap);

extern  void    init_all_track_cons(void);
extern  void    free_all_track_cons(void);
extern  SLONG   reference_track_con(USTR *filename);
extern  void    release_track_con(SLONG con_index);
extern  CAKE_FRAME *    get_track_con_frame(SLONG con_index, SLONG frame, SLONG *rx0, SLONG *ry0);
extern  void    get_track_con_combine(SLONG con_index, SLONG *sx, SLONG *sy, SLONG *xl, SLONG *yl);
extern  SLONG   get_track_con_total_frames(SLONG con_index);


#endif//_MAPTRACK_H_INCLUDE_

