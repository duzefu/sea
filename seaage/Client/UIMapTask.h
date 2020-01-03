/*
**	UIMapTask.h
**	UI of map task.
**
**	Jack, 2002/07/03.
*/
#ifndef _UIMAPTASK_H_
#define _UIMAPTASK_H_


// DEFINES /////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef enum    UI_MAPTASK_ENUMS
{   UIMAPTASK_FRAME_BKGND           =   0,
UIMAPTASK_FRAME_VSCROLL_BAR         =   1,
UIMAPTASK_FRAME_LIST_0_BKGND        =   3,
UIMAPTASK_FRAME_DETAILS_BKGND       =   8,
UIMAPTASK_FRAME_ABANDON_TASK        =   9,
UIMAPTASK_FRAME_HIDE_DETAILS        =   12,
UIMAPTASK_FRAME_LARGE_FAILURE_MARK  =   15,
UIMAPTASK_FRAME_SMALL_FAILURE_MARK  =   16,
UIMAPTASK_FRAME_LARGE_SUCCESS_MARK  =   17,
UIMAPTASK_FRAME_SMALL_SUCCESS_MARK  =   18,
UIMAPTASK_FRAME_CLOSE               =   19,
//
UIMAPTASK_EVENT                     =   3003,
UIMAPTASK_ID_BKGND                  =   0,
UIMAPTASK_ID_VSCROLL_BKGND          =   20,
UIMAPTASK_ID_VSCROLL_BAR            =   30,
UIMAPTASK_ID_LIST_0                 =   100,
UIMAPTASK_ID_ABANDON_TASK           =   200,
UIMAPTASK_ID_HIDE_DETAILS           =   210,
UIMAPTASK_ID_CLOSE                  =   300,
//
UIMAPTASK_VSCROLL_BKGND_SX          =   299,
UIMAPTASK_VSCROLL_BKGND_SY          =   178,
UIMAPTASK_VSCROLL_BKGND_XL          =   319 - 299,
UIMAPTASK_VSCROLL_BKGND_YL          =   460 - 178,
} UI_MAPTASK_ENUMS;


// STRUCTURES //////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct tagUI_MAPTASK_DATA 
{
    CAKE_FRAME_ANI  *cfa;       //frame ani pointer
    CAKE_FRAME      *cf[32];    //image pointer of each frame.
    //
    SLONG   hilight_id;         //hilight id
    SLONG   active_id;          //active id
    SLONG   start_index;        //start index
    //
    SLONG   scroll_y_pos;       //scroll button y position
    SLONG   min_scroll_y;       //minimize scroll y position
    SLONG   max_scroll_y;       //maximize scroll y position
    SLONG   mouse_event;        //mouse event 
    //
    SLONG   is_opened;  //任務介面是否打開
} UI_MAPTASK_DATA, *LPUI_MAPTASK_DATA;


// GLOBALS /////////////////////////////////////////////////////////////////////////////////////////////////////////
extern  UI_MAPTASK_DATA ui_maptask_data;


// FUNCTIONS ///////////////////////////////////////////////////////////////////////////////////////////////////////
int     init_ui_maptask(void);
void    active_ui_maptask(int active);
void    free_ui_maptask(void);
void    redraw_ui_maptask(SLONG sx, SLONG sy, void *vbitmap);
void    refresh_ui_maptask(void);
SLONG   handle_ui_maptask(UINT message, WPARAM wParam, LPARAM lParam);
void    redraw_uimaptask_mouse_point_info(SLONG id, BMP *bitmap);
//
SLONG   is_maptask_menu_opened(void);
void    open_maptask_menu(SLONG flag);


#endif//_UIMAPTASK_H_
