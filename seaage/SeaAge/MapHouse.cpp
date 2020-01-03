/*
**  MapHouse.cpp
**  map house system functions.
**  
**  Jack, 2002.4.9.
*/
#include "mainfun.h"
#include "House.h"
#include "HouseSet.h"
#include "MapHouse.h"


//#include "ClientMain.h"
extern	DATA_FILE	*packed_house_file;

//GLOBALS ////////////////////////////////////////////////////////////////////////////////////////
MAP_HOUSE   map_house[MAX_MAP_HOUSE];
SLONG       map_house_max;


//FUNCTIONS //////////////////////////////////////////////////////////////////////////////////////
int     init_map_house_system(void)
{
    SLONG   result;
    USTR    filename[_MAX_FNAME];

    init_house_set();

    set_data_file(packed_house_file);
    sprintf((char *)filename, "house\\houseset.dat");
    result = load_house_set((USTR*)filename);
    if(TTN_OK != result)
        return  TTN_ERROR;

    init_all_map_houses();

    return  TTN_OK;
}



void    free_map_house_system(void)
{
    free_house_set();
}


void    init_all_map_houses(void)
{
    SLONG   i;

    for(i=0; i<MAX_MAP_HOUSE; i++)
    {
        map_house[i].flag = 0;
    }
    map_house_max = 0;
}



void    clear_all_map_houses(void)
{
    SLONG   i, flag, house_no;

    for(i=0; i<map_house_max; i++)
    {
        flag = map_house[i].flag;
        house_no = map_house[i].no;
        if(flag)
        {
            dec_reference_for_house(house_no);
        }
        map_house[i].flag = 0;
        map_house[i].no = -1;
    }
    map_house_max = 0;
}


SLONG   get_map_house_no(SLONG house_index)
{
    if(house_index < 0 || house_index >= map_house_max)
        return  -1;
    return  map_house[house_index].no;
}


void    set_map_house_count(SLONG count)
{
    map_house_max = count;
}


void    naked_read_map_house(PACK_FILE *fp, SLONG total_houses)
{
    if(total_houses < MAX_MAP_HOUSE && fp)
    {
        pack_fread(&map_house[0], 1, sizeof(MAP_HOUSE) * total_houses, fp);
    }
}

