/*
**  MapHouse.h
**  map house system functions.
**  
**  Jack, 2002.4.9.
*/
#ifndef _HOUSESYSTEM_H_
#define _HOUSESYSTEM_H_
#include "House.h"
#include "HouseSet.h"


//DEFINES ///////////////////////////////////////////////////////////////////////////////////////
//
#define MAX_MAP_HOUSE           64  //一張地圖上最多可以有多少房屋


//STRUCTURES ////////////////////////////////////////////////////////////////////////////////////
//
typedef struct  tagMAP_HOUSE
{
    SLONG   flag;       //flag
    SLONG   no;         //house image no(in house_set).
    SLONG   px;         //house position x (map axis)
    SLONG   py;         //house position y (map axis)
    SLONG   tile_sx;    //house floor ximgs start x (tile position)
    SLONG   tile_sy;    //house floor ximgs start y (tile position)
    SLONG   tile_xl;    //house floor ximgs xl (tile position)
    SLONG   tile_yl;    //house floor ximgs yl (tile position)
    //
    SLONG   roof_index; //house roof object index in map_object[]
} MAP_HOUSE, *LPMAP_HOUSE;


//GLOBALS ///////////////////////////////////////////////////////////////////////////////////////
//
extern  MAP_HOUSE   map_house[MAX_MAP_HOUSE];
extern  SLONG       map_house_max;



//FUNCTIONS /////////////////////////////////////////////////////////////////////////////////////
//
extern	int     init_map_house_system(void);
extern	void    free_map_house_system(void);
//
extern	void    init_all_map_houses(void);
extern	void    clear_all_map_houses(void);
extern	SLONG   get_map_house_no(SLONG house_index);
extern	void    set_map_house_count(SLONG count);
//
extern	void    naked_read_map_house(PACK_FILE *fp, SLONG total_houses);
//


#endif//_HOUSESYSTEM_H_


