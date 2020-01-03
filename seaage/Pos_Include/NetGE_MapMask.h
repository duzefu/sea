/*
**  NetGE_MapMask.h
**  map mask functions header.
**
**  Jack, 2001.12.110.
*/
#pragma once


//
// DEFINES //////////////////////////////////////////////////////////////////////////////////////////////////
//
#define MIN_MASK_WIDTH          16      //地圖MASK的最小寬度
#define MIN_MASK_HEIGHT         8       //地圖MASK的最小高度
//
#define MASK_LO_MAGIC           0x01    //地上法術阻擋
#define MASK_MID_MAGIC          0x02    //半空中法術阻擋
#define MASK_HI_MAGIC           0x04    //高空法術阻擋
#define	MASK_DYNAMIC_NPC	    0x20	//動態NPC阻擋
#define MASK_FINDPATH           0x40    //用於尋徑的保留位
#define MASK_STOP               0x80    //人物行走阻擋
//
#define MASK_SHOW_LO_MAGIC      0x00000001
#define MASK_SHOW_MID_MAGIC     0x00000002
#define MASK_SHOW_HI_MAGIC      0x00000004
#define MASK_SHOW_STOP          0x00000008
#define MASK_SHOW_GRID          0x00000010
#define MASK_SHOW_FINDPATH      0x00000020
#define MASK_SHOW_ALL           0xffffffff
//
#define MASK_FILE_EXT           "MSK"
//
#define LO_MAGIC_HEIGHT         0
#define MID_MAGIC_HEIGHT        40
#define HI_MAGIC_HEIGHT         100
//
//----------------------------------------------------------------------------------------------
#define PATH_STEPS_NUM          200
//
#define STEP_ARRIVE             0   //到達
#define STEP_ON_THE_WAY         1   //在途中
#define STEP_OBSTRUCT           2   //被阻隔
#define STEP_OUTSTRETCH         3   //超出範圍
//
#define PATH_ARRIVE             0   //已經達到
#define PATH_FOUND              1   //找到可以到達的路徑
#define PATH_NEAR               2   //靠近目標
#define PATH_FAIL               3   //尋徑失敗
#define PATH_ERROR              -1  //錯誤


//
// STRUCTURES ///////////////////////////////////////////////////////////////////////////////////////////////
//
typedef struct  tagMAP_MASK
{
    SLONG   w;          //width masks
    SLONG   h;          //height masks
    SLONG   sw;         //single mask pixel width
    SLONG   sh;         //single mask pixel height
    UCHR    data[4];    //mask datas
} MAP_MASK, *LPMAP_MASK;


typedef struct  tagMAP_MASK_HEAD
{
    ULONG   copyright;  //copyright
    ULONG   id;         //file id
    ULONG   version;    //file version
    ULONG   head_size;  //this head size
    SLONG   w;          //width masks
    SLONG   h;          //height masks
    SLONG   sw;         //single mask width
    SLONG   sh;         //single mask height
} MAP_MASK_HEAD, *LPMAP_MASK_HEAD;


typedef struct  tagMASK_PATH
{
    POINT   pos[PATH_STEPS_NUM];
    SLONG   steps;
} MASK_PATH, *LPMASK_PATH;


//
// FUNCTIONS ////////////////////////////////////////////////////////////////////////////////////////////////
//
MAP_MASK *  create_map_mask(SLONG w, SLONG h, SLONG sw, SLONG sh);
void        destroy_map_mask(MAP_MASK **mm);
MAP_MASK *  load_map_mask(USTR *filename);
UCHR    get_map_mask(MAP_MASK *mm, SLONG x, SLONG y);
void    set_map_mask(MAP_MASK *mm, SLONG x, SLONG y, UCHR mask);
void	or_map_mask(MAP_MASK *mm, SLONG x, SLONG y, UCHR mask);
void	remove_map_mask(MAP_MASK *mm, SLONG x, SLONG y, UCHR mask);
void    convert_position_map2mask(MAP_MASK *mm, SLONG map_x, SLONG map_y, SLONG *mask_x, SLONG *mask_y);
SLONG   approach_mask_dir(SLONG mask_dx, SLONG mask_dy);
//
SLONG   is_pixel_mask_stop(SLONG pixel_x, SLONG pixel_y, MAP_MASK *mm);
SLONG   is_pixel_mask_match(SLONG pixel_x, SLONG pixel_y, SLONG check_mask, MAP_MASK *mm);
SLONG   is_mask_line_through(SLONG x1, SLONG y1, SLONG x2, SLONG y2, SLONG stop_mask, MAP_MASK *mm);
SLONG   is_pixel_line_through(SLONG x1, SLONG y1, SLONG x2, SLONG y2, SLONG stop_mask, MAP_MASK *mm);
SLONG   find_mask_near_open_pixel(SLONG *pixel_x, SLONG *pixel_y, SLONG stop_mask, MAP_MASK *mm);
SLONG   find_mask_near_through_pixel(SLONG pixel_sx, SLONG pixel_sy, SLONG *pixel_ex, SLONG *pixel_ey, SLONG stop_mask, MAP_MASK *mm);
void    intercept_geometry_line(SLONG sx, SLONG sy, SLONG *ex, SLONG *ey, SLONG len);
void    intercept_raster_line(SLONG sx, SLONG sy, SLONG *ex, SLONG *ey, SLONG len);
void    via_path_to_mask_path ( SLONG stop_mask, MAP_MASK *mm );
void    via_path_find_first_point(SLONG *point_x, SLONG *point_y, SLONG stop_mask, MAP_MASK *mm);
//
SLONG   trend_find_via_path(SLONG sx, SLONG sy, SLONG ex, SLONG ey, SLONG stop_mask, MAP_MASK *mm);
SLONG   astar_find_via_path(SLONG sx, SLONG sy, SLONG ex, SLONG ey, SLONG stop_mask, MAP_MASK *mm);
SLONG   dfs_find_via_path(SLONG sx, SLONG sy, SLONG ex, SLONG ey, SLONG stop_mask, MAP_MASK *mm);
SLONG   diffuse_find_via_path(SLONG sx, SLONG sy, SLONG ex, SLONG ey, SLONG stop_mask, MAP_MASK *mm);
//
SLONG   beeline_find_step(SLONG sx, SLONG sy, SLONG *ex, SLONG *ey, SLONG speed, SLONG stop_mask, MAP_MASK *mm);
SLONG   trend_find_step(SLONG sx, SLONG sy, SLONG *ex, SLONG *ey, SLONG speed, SLONG stop_mask, MAP_MASK *mm);
SLONG   astar_find_step(SLONG sx, SLONG sy, SLONG *ex, SLONG *ey, SLONG speed, SLONG stop_mask, MAP_MASK *mm);
SLONG   dfs_find_step(SLONG sx, SLONG sy, SLONG *ex, SLONG *ey, SLONG speed, SLONG stop_mask, MAP_MASK *mm);
SLONG   diffuse_find_step(SLONG sx, SLONG sy, SLONG *ex, SLONG *ey, SLONG speed, SLONG stop_mask, MAP_MASK *mm);

//
// Common functions:
//
extern  SLONG	LoadZoneMapMask(CHAR *szFileName);
extern  void	FreeZoneMapMask(void);
extern	MAP_MASK *	GetZoneMapMask(void);
//
extern  void	GatherMapCharacterMaskPosition(void);
extern  void	UpdateMapCharacterMask(void);
extern  void	RemoveMapCharacterMask(void);
extern  void	ClearMapDynamicCharacterMask(SLONG pix_x, SLONG pix_y);
extern  SLONG	FindBestAttackPosition(SLONG x, SLONG y, SLONG dest_x, SLONG dest_y, SLONG attack_distance, SLONG *attack_x, SLONG *attack_y);
extern  SLONG   FindCharacterStep(SLONG x, SLONG y, SLONG *dest_x, SLONG *dest_y, SLONG move_speed);
extern  SLONG   FindCharacterMaskStep(SLONG x, SLONG y, SLONG *dest_x, SLONG *dest_y, SLONG move_speed, SLONG stop);
extern  SLONG   FindCharacterBeelineStep(SLONG x, SLONG y, SLONG *dest_x, SLONG *dest_y, SLONG move_speed);
extern	SLONG	TrendFindCharacterStep(SLONG sx, SLONG sy, SLONG *ex, SLONG *ey, SLONG speed, SLONG stop_mask);
extern	SLONG   IsPixelMaskMatch(SLONG pixel_x, SLONG pixel_y, SLONG check_mask);
extern	SLONG   FindMaskNearThroughPixel(SLONG pixel_sx, SLONG pixel_sy, SLONG *pixel_ex, SLONG *pixel_ey, SLONG stop_mask);
extern	SLONG   IsPixelLineThrough(SLONG x1, SLONG y1, SLONG x2, SLONG y2, SLONG stop_mask);
extern	SLONG	IsPixelMaskStop(SLONG x, SLONG y);


