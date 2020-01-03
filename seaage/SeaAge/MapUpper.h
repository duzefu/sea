/*
**      MapUpper.H
**      map upper functions header. 
**      ZJian,2000/10/6.
*/
#ifndef _MAPUPPER_H_INCLUDE_
#define _MAPUPPER_H_INCLUDE_        1
#include "xgrafx.h"


//MISC ---------------------------------------------------------------------------------------------
#define MAX_MAP_UPPER           32

typedef struct  tagMAP_UPPER
{
    SLONG   flag;
    SLONG   x;
    SLONG   y;
    BMP     *bitmap;
} MAP_UPPER,*LPMAP_UPPER;


extern  MAP_UPPER   map_upper[MAX_MAP_UPPER];
extern  SLONG       map_upper_max;

extern  SLONG   init_map_upper_system(void);
extern  void    free_map_upper_system(void);
extern  SLONG   get_map_upper_count(void);
extern  void    clear_all_map_uppers(void);
extern  SLONG   naked_read_map_upper(PACK_FILE *fp);
extern  void    redraw_map_upper_layer(SLONG sx,SLONG sy,BMP *bmp);


#endif//_MAPUPPER_H_INCLUDE_

