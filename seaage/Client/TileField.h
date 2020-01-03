/*
**  TileField.h
**  
**  Map tile field functions header.
**
**  Jack, 2002.3.6.
*/
#ifndef _TILEFIELD_H_
#define _TILEFIELD_H_


//DEFINES ////////////////////////////////////////////////////////////////////////////////////////
//tile flags.
#define COVER_TILE_AREA_MASK        0x0000000f  //上層圖素的面積屬性
#define COVER_TILE_WHOLE_COVER      0x00000001  //底層圖素被上層圖素完全覆蓋
#define COVER_TILE_PART_COVER       0x00000002  //底層圖素被上層圖素部分覆蓋
//
#define COVER_TILE_TYPE_MASK        0x000000f0  //上層圖素屬於哪種類型
#define COVER_TILE_IS_HOUSE         0x00000010  //上層圖素為房屋的地表
#define COVER_TILE_IS_OBJECT        0x00000020  //上層圖素為某些地表類型的物件
//
#define FIELD_TILE_IN_HOUSE         0x00000100  //本圖素對應某房屋的屋內(掀屋頂)
//
//tile plat defines
#define	TILE_PLAT_WIDTH_SCREENS		3
#define	TILE_PLAT_HEIGHT_SCREENS	3
#define	TILE_PLAT_WIDTH				(SCREEN_WIDTH * TILE_PLAT_WIDTH_SCREENS)
#define	TILE_PLAT_HEIGHT			(SCREEN_HEIGHT * TILE_PLAT_HEIGHT_SCREENS)



//STRUCTURES /////////////////////////////////////////////////////////////////////////////////////
//tile instance structure.
typedef struct  tagTILE_INST
{
    SLONG   flag;               //tile flags
    SLONG   tile_id;            //earth tile image id(used for under layer tiles)
    SLONG   cover_id;           //earth cover image id(used for covers, buildings, etc.)
} TILE_INST, *LPTILE_INST;


//tile field structure.
typedef struct  tagTILE_FIELD
{
    SLONG       width;          //field width(of tiles)
    SLONG       height;         //field height(of tiles)
    SLONG       base_no;        //field base no
    SLONG       terra_no;       //original terra no
    TILE_INST   tile_inst[1];   //field tiles instance
} TILE_FIELD, *LPTILE_FIELD;


//tile platform cache.
typedef struct  tagTILE_PLAT
{
	SLONG	sx;		//plat map sx
	SLONG	sy;		//plat map sy
	SLONG	ex;		//plat map ex
	SLONG	ey;		//plat map ey
	BMP*	bitmap;	//full bitmap
	BMP*	sub_bitmap[TILE_PLAT_HEIGHT_SCREENS][TILE_PLAT_WIDTH_SCREENS];	//like TV wall
} TILE_PLAT, *LPTILE_PLAT;


//GLOBALS ////////////////////////////////////////////////////////////////////////////////////////
extern  TILE_FIELD* map_tile_field;
extern  TILE_PLAT   map_tile_plat;


//FUNCTIONS //////////////////////////////////////////////////////////////////////////////////////
extern	TILE_FIELD* create_tile_field(SLONG width, SLONG height, SLONG base_no, SLONG terra_no);
extern	void	destroy_tile_field(TILE_FIELD **field);
extern	void	redraw_tile_field(TILE_FIELD *field, SLONG sx, SLONG sy, BMP *bitmap);
extern	SLONG   naked_read_tile_field(PACK_FILE *fp, TILE_FIELD **field);
//
extern	SLONG   pixel_position_to_tile_x(TILE_FIELD *field, SLONG x, SLONG y);
extern	SLONG   pixel_position_to_tile_y(TILE_FIELD *field, SLONG x, SLONG y);
extern	void    pixel_position_to_tile_position(TILE_FIELD *field, SLONG x, SLONG y, SLONG *tile_x, SLONG *tile_y);
extern	SLONG   get_in_house_index_by_pixel_position(TILE_FIELD *field, SLONG pixel_x, SLONG pixel_y);
//
extern	SLONG   init_map_tile_plat(void);
extern	void	free_map_tile_plat(void);
extern	void	reset_map_tile_plat(void);
extern	void    plat_redraw_tile_field(TILE_FIELD *field, SLONG sx, SLONG sy, BMP *bitmap);



#endif//_TILEFIELD_H_


