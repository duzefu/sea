/*
**      MAP.H
**      map function header.
**      Jian,2000/8/16.
*/
#ifndef MAP_H_INCLUDE
#define MAP_H_INCLUDE   1
#include "xgrafx.h"
#include "xpoly.h"
#include "MapObject.h"
#include "NetGE_MapMask.h"
#include "NetGE_MapProc.h"


// D E F I N E S ////////////////////////////////////////////////////////////////////////////////////////////////
#define MAP_DIRECTORY           "map"
#define MAP_VERSION             0x00010001
//
#define MAP_LAYER_NONE          0x00000000
#define MAP_LAYER_TILE          0x00000001
#define MAP_LAYER_UPPER         0x00000002
#define MAP_LAYER_OBJECT        0x00000004
#define MAP_LAYER_HOUSE         0x00000008
//
#define MAX_MAP_OBJECT          4096
//
#define ALL_MAP_OBJECTS         -1
//
//map object flags.
#define MOBJ_ACTIVE             0x00000001  //物件目前被用
#define MOBJ_MARKED             0x00000002  //物件被選中
#define MOBJ_UNDER              0x00000004  //物件將會被歸類為底層物件
//
//object types
#define MOBJ_TYPES              0xff000000  //地圖物件種類的掩碼
#define MOBJ_SIMPLE             0x01000000  //簡單的單幀地圖物件，對應地圖物件庫
#define MOBJ_DYNAMIC            0x02000000  //多幀動畫地圖物件，對應地圖物件庫
#define MOBJ_FIXED              0x03000000  //PSD地圖中的固定物件
#define MOBJ_HOUSE_OBJECT       0x04000000  //房屋的中間物件
#define MOBJ_HOUSE_ROOF         0x05000000  //房屋的屋頂
#define MOBJ_NPC                0x06000000  //人物類物件
#define MOBJ_MAGIC              0x07000000  //法術類物件
#define MOBJ_DOOR               0x08000000  //門類物件，可以開關，帶阻擋
//
//object update flags
#define MOBJ_UPDATES            0x00ff0000  //地圖物件更新掩碼
#define MOBJ_UPDATE_MAGIC       0x00010000  //法術類物件經過更新
#define MOBJ_UPDATE_NPC         0x00020000  //人物類物件經過更新
//


//map types.
#define MAP_TYPE_EDIT				1
#define MAP_TYPE_RENDER				2

//redraw edit map flags.
#define REDRAW_MAP_TILE_IMAGE       0x00000001  //圖素
#define REDRAW_MAP_TILE_GRID        0x00000002  //
#define REDRAW_MAP_UPPER_IMAGE      0x00000004  //地表
#define REDRAW_MAP_UNDER_OBJECT     0x00000008  //物件
#define REDRAW_MAP_NORMAL_OBJECT    0x00000010  //
#define REDRAW_MAP_TRACK_IMAGE      0x00000020  //腳印
#define REDRAW_MAP_BLOCK_INFO       0x00000040  //地形
#define REDRAW_MAP_PROC_INFO        0x00000080  //事件
#define REDRAW_MAP_RECT_RANGE       0x00000100  //矩形邊框
#define REDRAW_MAP_DIAMOND_RANGE    0x00000200  //菱形邊框
#define REDRAW_MAP_REFRESH_OBJECT   0x00000400  //自動刷新物件圖像
#define REDRAW_MAP_REFRESH_NPC      0x00000800  //自動刷新ＮＰＣ圖像
#define REDRAW_MAP_CURRENT_PATH     0x00001000  //當前地圖路徑
#define REDRAW_MAP_ADJUST_START     0x00002000  //自動校正地圖位置
#define REDRAW_MAP_CLEAR_BITMAP     0x00004000  //先清除底圖
#define REDRAW_MAP_HOUSE_ROOF       0x00008000  //房屋屋頂
#define	REDRAW_MAP_OBJECT_POLY		0x00010000	//顯示物件輪廓
//
#define	OBJECT_POLY_FLAGS			(PDP_VALID | PDP_BASE | PDP_HEIGHT | PDP_ARRIS | PDP_TOP | PDP_CROSS | PDP_PROJECTION | PDP_ZHEIGHT)
												//顯示物件輪廓的標誌

//------------------------------------------------
//map move types.
#define MAP_MOVE_STAY_CURRENT       0
#define MAP_MOVE_TO_POSITION        1
#define MAP_MOVE_FOLLOW_NPC         2
#define MAP_MOVE_AUTO               3
//map move datas.
#define MAP_MOVE_FREE               0
#define MAP_MOVE_KEEP               1
#define MAP_MOVE_ACCELATE_MAX       16
#define MAP_MOVE_ACCELATE_MIN       -16
#define MAP_MOVE_SPEED_MAX          16
#define MAP_MOVE_SPEED_MIN          -16



#define	GET_MAP_OBJECT_TYPE(flag)		(((flag) & MOBJ_TYPES) >> 24)
#define	GET_HOUSE_INDEX(id)				(((id) & 0xffff0000) >> 16)
#define	GET_HOUSE_OBJECT_INDEX(id)		(((id) & 0xffff) - 1)


// S T R U C T U R E S //////////////////////////////////////////////////////////////////////////////////////////
typedef struct  tagMAP_DATA
{
    USTR    filename[80];   // now map filename
    USTR    mapname[80];    // now map text name
    SLONG   redraw_flags;   // map redraw flags
    SLONG   map_sx;         // now map left-up x position
    SLONG   map_sy;         // now map left-up y position
    SLONG   map_tx;         // map target left-up x position
    SLONG   map_ty;         // map target left-up y position
    SLONG   map_mx;         // map move speed x pixels
    SLONG   map_my;         // map move speed y pixels
    SLONG   map_ax;         // map x acceleration
    SLONG   map_ay;         // map y acceleration
    SLONG   view_sx;        // view left-up x position
    SLONG   view_sy;        // view left-up y position
    SLONG   view_xl;        // view range width
    SLONG   view_yl;        // view range height
    //
    SLONG   zoom_win_def_xl;// default zoom window width
    SLONG   zoom_win_def_yl;// default zoom window height
    SLONG   zoom_win_sx;    // screen zoom window left-up x position
    SLONG   zoom_win_sy;    // screen zoom window left-up y position
    SLONG   zoom_win_xl;    // screen zoom window width
    SLONG   zoom_win_yl;    // screen zoom window height
    SLONG   zoom_map_sx;    // map zoom range start x position
    SLONG   zoom_map_sy;    // map zoom range start y position
    SLONG   zoom_map_xl;    // map zoom range width
    SLONG   zoom_map_yl;    // map zoom range height
    double  zoom_control;   // map zoom control
    //
} MAP_DATA,*LPMAP_DATA;



typedef struct  tagMAP_HEAD
{
    USTR    copyright[4];   //"RAYS"
    USTR    id[4];          //"MAP "
    SLONG   version;        // MAP_VERSION
    SLONG   head_size;      // map head size
    SLONG   type;           // map type
    SLONG   layer;          // map layer information
    SLONG   map_xl;         // map pixel width
    SLONG   map_yl;         // map pixel height
    SLONG   cell_xl;        // map cell width
    SLONG   cell_yl;        // map cell height
    SLONG   map_cxl;        // map cell table width
    SLONG   map_cyl;        // map cell table height
    SLONG   total_uppers;   // count of map upper
    SLONG   total_objects;  // count of map object
    SLONG   total_houses;   // count of map houses
    SLONG   total_blocks;   // count of map blocks
    SLONG   total_procs;    // count of map proc
} MAP_HEAD,*LPMAP_HEAD;


//地圖物件資料結構
typedef struct  tagMAP_OBJECT
{
	SLONG   flag;			// map object flags
	SLONG   id;				// map object file image id
    SLONG   px;             // map object position x
    SLONG   py;             // map object position y
    SLONG   pz;             // map object position z
    SLONG   effect;         // map object show effect
    SLONG   frame;          // map object now frame
    union
    {
        SLONG   now_tick;       //動態物件的目前計時數
        SLONG   alpha;          //房屋屋頂的當前ALPHA值
    };
    union
    {
        SLONG   change_tick;    //動態物件：動態物件的換幀計時數
        SLONG   update_alpha;   //房屋屋頂：房屋屋頂的ALPHA變化標誌
        SLONG   npc_no;         //NPC 物件：NPC 的索引值，指向NPC 數據資料
        SLONG   magic_part_no;  //法術物件：法術組件的索引值，指向法術組件數據資料
    };
} MAP_OBJECT,*LPMAP_OBJECT;


typedef struct  tagMAP_OBJECT_EX
{
    SLONG   image_sx;
    SLONG   image_sy;
    SLONG   image_ex;
    SLONG   image_ey;
    POLY*   poly;
} MAP_OBJECT_EX, *LPMAP_OBJECT_EX;


//地圖移動相關結構
typedef struct  tagMAP_MOVE
{
    SLONG   type;       //地圖的移動方式
    //
    SLONG   dest_x;     //目標點 X 座標
    SLONG   dest_y;     //目標點 Y 座標
    SLONG   move_speed; //地圖的移動速度
    //
    SLONG   dest_npc;   //目標 NPC 編號
    //
    SLONG   keep_range; //是否不超過地圖大小限制
} MAP_MOVE, *LPMAP_MOVE;


// G L O B A L S ////////////////////////////////////////////////////////////////////////////////////////////////
extern  MAP_HEAD        map_head;
extern  MAP_DATA        map_data;
extern  MAP_OBJECT      map_object[MAX_MAP_OBJECT];
extern  MAP_OBJECT_EX   map_object_ex[MAX_MAP_OBJECT];
extern  SLONG           map_object_max;
extern  MAP_MOVE        map_move;


// F U N C T I O N    P R O T O T Y P E ////////////////////////////////////////////////////////////////////////
extern  int     init_map(void);
extern  void    free_map(void);
extern  void    active_map(int active);
extern  void    clear_map(void);
extern  SLONG   load_map(USTR *filename);
extern  void    redraw_map(BMP *bitmap);
extern  void    set_map_redraw_flags(SLONG flags);
extern  SLONG   get_usable_map_object(void);
//
extern  void    init_map_data(MAP_DATA *map_data);
extern  void    reset_map_start_position(void);
extern  void    init_map_move(void);
extern  void    set_map_move_to_position(SLONG dest_x, SLONG dest_y, SLONG move_speed);
extern  void    set_map_move_follow_npc(SLONG npc_no);
extern  void    set_map_move_auto(void);
extern  void    set_map_move_keep_range(SLONG flag);
extern  void    adjust_map_move(void);
extern  void    set_map_view_range(SLONG sx, SLONG sy, SLONG xl, SLONG yl);
//
extern	void    redraw_map_mask(SLONG map_sx, SLONG map_sy, MAP_MASK *mm, SLONG flags, void *vbitmap);
extern	void    redraw_map_proc_layer(SLONG map_sx,SLONG map_sy,SLONG flag,BMP *bmp);
//
extern	SLONG	is_redraw_map_object_poly(void);
extern	void	set_redraw_map_object_poly(SLONG flag);


#endif//MAP_H_INCLUDE
