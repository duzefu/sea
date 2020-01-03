/*
**  mapblock.h
**  map block functions.
**  
**  geaan, 2001.6.22.
*/
#ifndef _MAPBLOCK_H_INCLUDE_
#define _MAPBLOCK_H_INCLUDE_
#include "xpoly.h"


//MISC ----------------------------------------------------------------------------------
//
#define MAX_MAP_BLOCK           4096
#define MAX_PATH_LONG           99999999
#define MIN_PATH_WIDTH          32



//MAP BLOCK TYPES(地形類型) -------------------------------------------------------------
//
#define MBT_LAND                0x00000001  //陸地
#define MBT_SNOW                0x00000002  //雪地
#define MBT_WATER               0x00000004  //淺水
#define MBT_BOG                 0x00000008  //沼澤
#define MBT_DEEPWATER           0x00000010  //深水
#define MBT_BUILDING            0x00000020  //建筑


//MAP BLOCK STRUCT(地形數據定義)---------------------------------------------------------
//
typedef struct tagMAP_BLOCK
{
    SLONG   type;               // block type
    POLY    poly;               // block poly
    SLONG   adj[MAX_POLY_NUM];  // adjoint information
    SLONG   other[MAX_POLY_NUM];// adjoint block line index
    SLONG   dist[MAX_POLY_NUM]; // distance of two map blocks
} MAP_BLOCK,*LPMAP_BLOCK;


extern  MAP_BLOCK   map_block[MAX_MAP_BLOCK];
extern  SLONG       map_block_max;



//FUNCTION PROTOTYPES --------------------------------------------------------------------
//
extern  void    reset_map_block_count(void);
extern  SLONG   get_map_block_count(void);
extern  void    set_map_block_count(SLONG count);
extern  void    naked_read_map_block(PACK_FILE *fp, SLONG read_blocks);

extern  void    redraw_map_block_layer(SLONG sx,SLONG sy,SLONG flag,BMP *bmp);
extern  SLONG   find_map_block_whose_cover_include_point(SLONG x,SLONG y);
extern  SLONG   find_point_of_map_block_underside(SLONG *x,SLONG *y,SLONG *no,SLONG *index,SLONG size);
extern  USTR *  get_map_block_type_string(SLONG type);
extern  void    clear_all_map_blocks(void);
extern  void    clear_map_block(SLONG index);
extern  SLONG   add_map_block(SLONG type,POLY poly);
extern  void    del_map_block(SLONG index);
extern  SLONG   update_map_block_data(void);
extern  SLONG   find_map_block_line(SLONG x1,SLONG y1,SLONG z1,SLONG x2,SLONG y2,SLONG z2,SLONG *no1,SLONG *lindex1,SLONG *no2,SLONG *lindex2);
extern  SLONG   operate_map_block_distance(SLONG index1,SLONG index2);
extern  SLONG   find_map_block_over_line(SLONG no1,SLONG no2,SLONG *x1,SLONG *y1,SLONG *z1,SLONG *x2,SLONG *y2,SLONG *z2);
extern  SLONG   find_map_block_cover_point(SLONG x,SLONG y,SLONG *height);
extern  SLONG   redraw_map_block_info(SLONG no,BMP *bit_map);
extern  SLONG   find_map_block_intersect_point(SLONG *xx,SLONG *yy,SLONG *zz,SLONG no,SLONG no1);
extern  SLONG   find_map_specific_block_point(SLONG block_index,SLONG dist,SLONG *x,SLONG *y,SLONG *point_index);
extern  SLONG   find_point_of_map_block_cover(SLONG dist,SLONG *x,SLONG *y,SLONG *block_index,SLONG *point_index);
extern  SLONG   seek_map_point_block_height(SLONG x,SLONG y,SLONG *hh);



#endif//_MAPBLOCK_H_INCLUDE_
