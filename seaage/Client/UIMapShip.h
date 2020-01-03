/*
**	UIMapShip.h
**	UI of map ship.
**
**	Jack, 2002/07/03.
*/
#ifndef _UIMAPSHIP_H_
#define _UIMAPSHIP_H_


// DEFINES /////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef enum    UI_MAPSHIP_ENUMS
{   UIMAPSHIP_FRAME_BKGND           =   0,
UIMAPSHIP_FRAME_EQUIP_BKGND         =   1,
UIMAPSHIP_FRAME_EQUIP               =   2,
UIMAPSHIP_FRAME_DOCK                =   5,
UIMAPSHIP_FRAME_INFORMATION         =   8,
UIMAPSHIP_FRAME_CLOSE               =   11,
//
UIMAPSHIP_EVENT                     =   3005,
UIMAPSHIP_ID_BKGND                  =   0,
UIMAPSHIP_ID_EQUIP                  =   10,
UIMAPSHIP_ID_DOCK                   =   20,
UIMAPSHIP_ID_INFORMATION            =   30,
UIMAPSHIP_ID_CLOSE                  =   40,
UIMAPSHIP_ID_BAG_0_ITEM             =   200,
//
UIMAPSHIP_BAG_0_SX                  =   32,
UIMAPSHIP_BAG_0_SY                  =   379,
UIMAPSHIP_BAG_DX                    =   34,
UIMAPSHIP_BAG_DY                    =   34,
UIMAPSHIP_BAG_X_COUNT               =   9,
UIMAPSHIP_BAG_Y_COUNT               =   3,
UIMAPSHIP_BAG_COUNTS                =   27,
} UI_MAPSHIP_ENUMS;

// STRUCTURES //////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct tagUI_MAPSHIP_DATA 
{
    CAKE_FRAME_ANI  *cfa;       //frame ani pointer
    CAKE_FRAME      *cf[32];    //image pointer of each frame.
    //
    CAKE_FRAME_ANI  *ship_cfa;      //ship frame ani pointre
    CAKE_FRAME      *ship_cf[32];   //image pointer of each ship
    //
    SLONG   hilight_id;         //hilight id
    SLONG   active_id;          //active id
    SLONG   function_id;        //目前列表的內容(資料, 裝備)
    SLONG   function_dock;      //船塢選單
    //
    SLONG   ship_index;     //船隻索引, 對應船隻介面的底圖
    //
    SLONG   is_opened;  //船隻介面是否打開
} UI_MAPSHIP_DATA, *LPUI_MAPSHIP_DATA;


// GLOBALS /////////////////////////////////////////////////////////////////////////////////////////////////////////
extern  UI_MAPSHIP_DATA ui_mapship_data;


// FUNCTIONS ///////////////////////////////////////////////////////////////////////////////////////////////////////
int     init_ui_mapship(void);
void    active_ui_mapship(int active);
void    free_ui_mapship(void);
void    redraw_ui_mapship(SLONG sx, SLONG sy, void *vbitmap);
void    refresh_ui_mapship(void);
SLONG   handle_ui_mapship(UINT message, WPARAM wParam, LPARAM lParam);
void    redraw_uimapship_mouse_point_info(SLONG id, BMP *bitmap);
//
SLONG   is_mapship_menu_opened(void);
void    open_mapship_menu(SLONG flag);
//


#endif//_UIMAPSHIP_H_
