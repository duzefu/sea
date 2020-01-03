/*
**  TileSet.h
**
**  Tile set functions header.
**
**  Jack, 2002.3.6.
*/
#ifndef _TILESET_H_
#define _TILESET_H_


// DEFINES ////////////////////////////////////////////////////////////////////////
#define TERRA_SHAPE_FILE_VERSION        0x00010001
#define TERRA_SHAPE_FILENAME            "terrashp.dat"


//encode cell shape by upper layer terra type.
#define TILE_SHAPE_UPPER_LEFT           0x01    //upper-left corner is upper layer terra
#define TILE_SHAPE_UPPER_RIGHT          0x02    //upper-right corner is upper layer terra
#define TILE_SHAPE_LOWER_LEFT           0x04    //lower-left corner is upper layer terra
#define TILE_SHAPE_LOWER_RIGHT          0x08    //lower-right corner is upper layer terra
//
#define TILE_IMAGES                     4       //image frames of a tile
#define TILE_SHAPES                     16      //shapes of a mixed-terra tile
#define SET_SOLIDS                      16      //solid terra shapes of one terra set
#define SET_MIXEDS                      16      //mixed terra shapes of one terra set
//
#define MAX_TERRA_SOLIDS                32  //solid terras
#define MAX_TERRA_MIXEDS                32  //mixed terras
#define MAX_TERRA_SETS                  16  //max terra sets
#define MAX_SHAPE_TILES                 64  //max shape tiles
#define MAX_TERRA_SHAPES                (TILE_SHAPES * MAX_TERRA_MIXEDS + MAX_TERRA_SOLIDS) //max terra shapes
#define MAX_TILE_BASES                  10240   //max tile bases

//
#define TILE_MASK_TILE_INDEX            0x000000ff  //index of terra_shape's tile_no
#define TILE_MASK_SOLID_TERRA           0x0000ff00  //this tile is a solid-terra tile
#define TILE_MASK_TILE_SHAPE            0x000f0000  //shape code of the tile
#define TILE_MASK_MIXED_TERRA           0x0ff00000  //this tile is a mixed-terra tile
//


// STURCTURES /////////////////////////////////////////////////////////////////////
///*
//terra base structure.
typedef struct  tagTERRA_BASE
{
    SLONG   flag;       //terra flag
    ULONG   mask;       //mask of whose solid shape
    SLONG   layer;      //terra layer
    UCHR    name[32];   //terra name
} TERRA_BASE, *LPTERRA_BASE;
///*/

//terra shape structure.
typedef struct  tagTERRA_SHAPE
{
    SLONG   under_type;     //under terra type
    SLONG   cover_type;     //cover terra type
    SLONG   shape_code;     //terra shape code
    SLONG   max_tiles;      //max terra tiles(= normals + specials)
    SLONG   max_specials;   //special terra tiles
    SLONG   image_no[MAX_SHAPE_TILES][TILE_IMAGES]; //terra tile images
} TERRA_SHAPE, *LPTERRA_SHAPE;


////*
//terra mixed structure.
typedef struct  tagTERRA_MIXED
{
    SLONG   flag;
    SLONG   under_type;
    SLONG   cover_type;
} TERRA_MIXED, *LPTERRA_MIXED;


//terra solid structure.
typedef struct  tagTERRA_SOLID
{
    SLONG   flag;
    SLONG   type;
} TERRA_SOLID, *LPTERRA_SOLID;


//terra set structure.
typedef struct  tagTERRA_SET
{
    SLONG   flag;
    USTR    name[32];
    SLONG   solid_terra[SET_SOLIDS];
    SLONG   max_solids;
    SLONG   mixed_terra[SET_MIXEDS];
    SLONG   max_mixeds;
} TERRA_SET, *LPTERRA_SET;
///*/

//terra shape file head structure.
// GLOBALS ////////////////////////////////////////////////////////////////////////
//extern  TERRA_BASE  terra_base[MAX_TERRA_SOLIDS];
//
extern  TERRA_SHAPE terra_shape[MAX_TERRA_SHAPES];
//
extern  TERRA_SET   terra_set[MAX_TERRA_SETS];
extern  TERRA_MIXED terra_mixed[MAX_TERRA_MIXEDS];
extern  TERRA_SOLID terra_solid[MAX_TERRA_SOLIDS];

// FUNCTIONS //////////////////////////////////////////////////////////////////////
extern	int     init_terra_base(void);
extern	int     init_terra_shape(void);
extern	int     init_terra_set(void);
//
extern	SLONG   get_tile_terra_image_no(SLONG tile_id, SLONG frame);
extern	SLONG   get_solid_terra_shape_index(SLONG solid_index);
extern	SLONG   tile_id_to_shape_index(SLONG tile_id);
extern	SLONG   shape_index_to_normal_tile_id(SLONG shape_index);
//
extern	SLONG   load_terra_shape_data_from_file(USTR *filename);
//


#endif//_TILESET_H_

