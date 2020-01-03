/*
**  TileImage.h
**  Tile image functions header.
**
**  Jack, 2002.3.6.
*/
#ifndef _TILEIMAGE_H_
#define _TILEIMAGE_H_
#include "xgrafx.h"

// DEFINES ////////////////////////////////////////////////////////////////////////
#define TILE_IMAGE_FILE_VERSION     0x00010000
#define TILE_DIRECTORY              "tile"
#define TILE_IMAGE_FILENAME         "tileimg.dat"


//tile size defines.
#define TILE_WIDTH                  128     //64
#define TILE_HEIGHT                 80      //40
#define TILE_SIZE                   (TILE_WIDTH*TILE_HEIGHT)
#define TILE_DATA_SIZE              (TILE_WIDTH*TILE_HEIGHT/2)
#define TILE_HALF_WIDTH             (TILE_WIDTH/2)
#define TILE_HALF_HEIGHT            (TILE_HEIGHT/2)

//tile image limited.
#define MAX_TILE_IMAGES             10240   //max tile images

//tile shape defines.
#define TILE_POLY_RECTANGLE         0
#define TILE_POLY_DIAMOND           1


// STURCTURES /////////////////////////////////////////////////////////////////////
typedef struct  tagTILE_VPUT
{
    int offset; //offset from the line start point
    int width;  //continuous pixel
    int index;  //image pixel index
} TILE_VPUT, *LPTILE_VPUT;


typedef struct  tagTILE_RPUT
{
    int rx;     //offset x
    int ry;     //offset y
} TILE_RPUT, *LPTILE_RPUT;


typedef struct  tagTILE_IMAGE_HEAD
{
    ULONG   copyright;      //tile image file copyright, 'RAYS'.
    ULONG   id;             //tile image file id, 'TILE'.
    ULONG   version;        //tile image file version, TILE_IMAGE_FILE_VERSION.
    ULONG   head_size;      //size of this head.
    //
    SLONG   tile_width;     //tile image pixel width.
    SLONG   tile_height;    //tile image pixel height.
    SLONG   tile_poly;      //tile image poly.
    SLONG   total_tiles;    //total tiles in this file.
    SLONG   reserved[8];    //reserved area.
} TILE_IMAGE_HEAD, *LPTILE_IMAGE_HEAD;


typedef struct  tagTILE_IMAGE_DATA
{
    SLONG   flag;
    PIXEL*  buffer;
} TILE_IMAGE_DATA, *LPTILE_IMAGE_DATA;


// GLOBALS ////////////////////////////////////////////////////////////////////////
static  USTR        tile_vmask[TILE_HEIGHT][TILE_WIDTH];
static  TILE_VPUT   tile_vput[TILE_HEIGHT];
static  TILE_RPUT   tile_rput[TILE_DATA_SIZE];
//
extern  TILE_IMAGE_DATA     tile_image_data[MAX_TILE_IMAGES];
extern  SLONG   total_tile_image_datas;
//

// FUNCTIONS //////////////////////////////////////////////////////////////////////
extern	void    generate_tile_vmask(void);
extern	void    output_tile_vmask(void);
extern	void    generate_tile_vput(void);
extern	void    output_tile_vput(void);
extern	void    generate_tile_rput(void);
extern	void    output_tile_rput(void);
//
extern	void    init_tile_image_module(void);
extern	void    free_tile_image_module(void);
extern	void    put_tile_image(SLONG sx,SLONG sy,PIXEL *tile_buffer,BMP *bitmap);
extern	void    range_put_tile_image(SLONG sx,SLONG sy,PIXEL *tile_buffer,BMP *bitmap);
//
extern	void    init_tile_image_data(void);
extern	void    free_tile_image_data(void);
extern	PIXEL*  create_tile_image_buffer(void);
extern	void    destroy_tile_image_buffer(PIXEL **buffer);
//
extern	SLONG   load_tile_image_data_from_file(USTR *filename);
extern	SLONG   naked_read_tile_image(PACK_FILE *fp, PIXEL **image_buffer);



#endif//_TILEIMAGE_
