/*
**  MapTile.cpp
**
**  map tile system functions.
**
**  Jack,2002.3.6.
*/
#include "mainfun.h"
#include "MapTile.h"


//#include "ClientMain.h"
extern	DATA_FILE	*packed_tile_file;



//FUNCTIONS --------------------------------------------------------------------------------------
SLONG   init_map_tile_system(void)
{
    SLONG   result;
    USTR    filename[_MAX_FNAME];

    init_tile_image_module();
    //
	// Jack, skip load terra's ini files for game.[1/13/2003]
	/*
    if(0 != init_terra_base())
        return  TTN_ERROR;
    if(0 != init_terra_shape())
        return  TTN_ERROR;
    if(0 != init_terra_set())
        return  TTN_ERROR;
	*/
    //
    set_data_file(packed_tile_file);
    sprintf((char *)filename, "%s\\%s", TILE_DIRECTORY, TILE_IMAGE_FILENAME);
    result = load_tile_image_data_from_file((USTR*)filename);
    if(TTN_OK != result)
        return  TTN_ERROR;
    //
    set_data_file(packed_tile_file);
    sprintf((char *)filename, "%s\\%s", TILE_DIRECTORY, TERRA_SHAPE_FILENAME);
    result = load_terra_shape_data_from_file((USTR *)filename);
    if(TTN_OK != result)
        return  TTN_ERROR;
    
    //
    result = init_map_tile_plat();
    if(TTN_OK != result)
        return  TTN_ERROR;

    
    return  TTN_OK;
}


void    active_map_tile_system(int active)
{
}


void    free_map_tile_system(void)
{
    free_map_tile_plat();
    free_tile_image_data();
    free_tile_image_module();
    destroy_tile_field(&map_tile_field);
}


