/*
**      MapUpper.CPP
**      map upper functions. 
**
**      ZJian, 2000.10.6.
*/
#include "mainfun.h"
#include "map.h"
#include "mapupper.h"



MAP_UPPER   map_upper[MAX_MAP_UPPER];
SLONG       map_upper_max;



SLONG   init_map_upper_system(void)
{
    SLONG i;
    for(i=0;i<MAX_MAP_UPPER;i++)
    {
        map_upper[i].flag=0;
        map_upper[i].x=0;
        map_upper[i].y=0;
        map_upper[i].bitmap=NULL;
    }
    map_upper_max=0;
    return TTN_OK;
}


void    free_map_upper_system(void)
{
    clear_all_map_uppers();
}


SLONG   get_map_upper_count(void)
{
    return map_upper_max;
}


void    clear_all_map_uppers(void)
{
    SLONG i;
    for(i=0;i<MAX_MAP_UPPER;i++)
    {
        if(map_upper[i].bitmap)
            destroy_bitmap(&map_upper[i].bitmap);
        map_upper[i].flag=0;
        map_upper[i].x=0;
        map_upper[i].y=0;
    }
    map_upper_max=0;
}


SLONG   naked_read_map_upper(PACK_FILE *fp)
{
    SLONG i,y,w,h;

    clear_all_map_uppers();
    pack_fread(&map_upper_max,1,sizeof(map_upper_max),fp);
    for(i=0;i<map_upper_max;i++)
    {
        pack_fread(&map_upper[i].flag,1,sizeof(SLONG),fp);
        pack_fread(&map_upper[i].x,1,sizeof(SLONG),fp);
        pack_fread(&map_upper[i].y,1,sizeof(SLONG),fp);
        pack_fread(&w,1,sizeof(SLONG),fp);
        pack_fread(&h,1,sizeof(SLONG),fp);
        map_upper[i].bitmap = create_bitmap(w,h);
        for(y=0;y<map_upper[i].bitmap->h;++y)
            pack_fread(map_upper[i].bitmap->line[y],1,map_upper[i].bitmap->pitch,fp);
        convert_bitmap_fff2hi(map_upper[i].bitmap);
    }
    return TTN_OK;
}


void    redraw_map_upper_layer(SLONG sx,SLONG sy,BMP *bmp)
{
    SLONG i;
    for(i=0;i<map_upper_max;i++)
    {
        if(map_upper[i].flag)
        {
            put_bitmap(map_upper[i].x-sx,map_upper[i].y-sy,map_upper[i].bitmap,bmp);
        }
    }
}

