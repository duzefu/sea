/*
**  MapTile.h
**
**  map tile system functions header.
**
**  Jack, 2002.3.6.
*/
#ifndef _MAPTILE_H_
#define _MAPTILE_H_

#include "TileImage.h"
#include "TileSet.h"
#include "TileField.h"



extern	SLONG   init_map_tile_system(void);
extern	void    active_map_tile_system(int active);
extern	void    free_map_tile_system(void);
//



#endif//_MAPTILE_H_


