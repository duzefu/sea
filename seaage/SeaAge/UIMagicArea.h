/*
**	UIMagicArea.h
**	magic area functions.
**
**	Jack, 2002/09/26.
*/
#ifndef _UIMAGICAREA_H_
#define _UIMAGICAREA_H_
 

// D E F I N E S //////////////////////////////////////////////////////////////////////////////////////////////////
/*
//------------
//目標範圍類型
//--------------------------------------
#define MAGIC_AREA_TYPE_CIRCLE              1   //圓形範圍
#define MAGIC_AREA_TYPE_RECTANGLE           2   //方形範圍
#define MAGIC_AREA_TYPE_LINE                3   //線性範圍
//
//---------------
//目標範圍標誌
//--------------------------------------
#define MAGIC_AREA_FLAG_VISIBLE         0x00000001  //範圍可見


// S T R U C T U R E S ////////////////////////////////////////////////////////////////////////////////////////////
typedef struct  tagMAGIC_AREA
{
    SLONG   flag;           //標誌
    SLONG   type;           //目標範圍類型
    SLONG   orig_x;         //目標範圍基準起始點座標 X
    SLONG   orig_y;         //目標範圍基準起始點座標 Y
    SLONG   dest_x;         //目標範圍基準目標點座標 X
    SLONG   dest_y;         //目標範圍基準目標座標 Y
    SLONG   range;          //目標範圍的大小
    //
    SLONG   magic_no;       //正在施法的法術編號
    //
    CAKE_FRAME_ANI  *line_cfa;      //線性區域圖檔
    CAKE_FRAME_ANI  *circle_cfa;    //圓形區域圖檔
    CAKE_FRAME_ANI  *rectangle_cfa; //矩形區域圖檔
} MAGIC_AREA, *LPMAGIC_AREA;
*/
//目標標誌
//--------------------------------------
#define     MAX_MAGIC_AREA      MAX_CHARACTER_TEAM_MEMBERS
//
#define MAGIC_AREA_FLAG_VISIBLE         0x00000001  //範圍可見

// S T R U C T U R E S ////////////////////////////////////////////////////////////////////////////////////////////
typedef struct  tagMAGIC_AREA
{
    SLONG   flag;           //標誌
    SLONG   x;              //目標範圍基準起始點座標 X
    SLONG   y;              //目標範圍基準起始點座標 Y
    //
    SLONG   magic_no;       //正在施法的法術編號
    SLONG   npc_no;         //該魔法陣的.使用者
    //
    SLONG   new_imd_id;
    SLONG   new_frame;
    //
    SLONG   draw_img_id;     //對應在物件庫內的圖檔的ID
    SLONG   draw_frame;
} MAGIC_AREA, *LPMAGIC_AREA;

// G L O B A L S //////////////////////////////////////////////////////////////////////////////////////////////////
//extern  MAGIC_AREA  magic_area;
extern  MAGIC_AREA  g_magic_area[MAX_CHARACTER_TEAM_MEMBERS];

// F U N C T I O N S //////////////////////////////////////////////////////////////////////////////////////////////
SLONG   init_magic_area(void);
void    free_magic_area(void);
//
void	clear_magic_area(void);
/*
void    set_magic_area_visible(SLONG is_visible);
SLONG   is_magic_area_visible(void);
void    set_magic_area_orig_position(SLONG orig_x, SLONG orig_y);
void    set_magic_area_dest_position(SLONG dest_x, SLONG dest_y);
void    set_magic_area_range(SLONG range);
void    set_magic_area_type(SLONG type);
*/
void    set_magic_area_visible(SLONG index, SLONG is_visible);
SLONG   is_magic_area_visible(SLONG index);
void    set_magic_area_position(SLONG index, SLONG x, SLONG y);
void    set_magic_magic_no(SLONG index, SLONG magic_no);
void    set_magic_npc_no(SLONG index, SLONG npc_no);

void    redraw_magic_area(BMP *bitmap);

void    add_magic_area(SLONG x, SLONG y, SLONG dir, SLONG npc_no, SLONG magic_no, SLONG level);
void    delete_magic_area(SLONG npc_no,SLONG magic_no);

#endif//_UIMAGICAREA_H_
