/*
**	UIMapSkill.h
**	UI of map skill.
**
**	Jack, 2002/07/03.
*/
#ifndef _UIMAPSKILL_H_
#define _UIMAPSKILL_H_


// DEFINES /////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef enum    UI_MAPSKILL_ENUMS
{   UIMAPSKILL_FRAME_BKGND              =   0,
UIMAPSKILL_FRAME_STAR                   =   1,
UIMAPSKILL_FRAME_CLOSE                  =   2,
//
UIMAPSKILL_EVENT                        =   3004,
UIMAPSKILL_ID_BKGND                     =   0,
UIMAPSKILL_ID_LIST_0                    =   100,
UIMAPSKILL_ID_CLOSE                     =   1000,
//
UIMAPSKILL_LIST_0_SX                    =   38,         //list 0 start position x
UIMAPSKILL_LIST_0_SY                    =   146,        //list 0 start position y
UIMAPSKILL_LIST_XL                      =   318 - 38,   //
UIMAPSKILL_LIST_YL                      =   180 - 38,   //
UIMAPSKILL_LIST_DX                      =   0,          //list n distance
UIMAPSKILL_LIST_DY                      =   37,         //
//
UIMAPSKILL_ICON_SX                      =   3,          //icon offset position
UIMAPSKILL_ICON_SY                      =   2,          //
UIMAPSKILL_NAME_SX                      =   116 - 38,   //name offset position
UIMAPSKILL_NAME_SY                      =   153 - 146,  //
UIMAPSKILL_LEVEL_SX                     =   260 - 38,   //level offset position
UIMAPSKILL_LEVEL_SY                     =   160 - 146,  //
UIMAPSKILL_STAR_SX                      =   116 - 38,   //first star offset position
UIMAPSKILL_STAR_SY                      =   166 - 146,  //
UIMAPSKILL_STAR_DX                      =   12,         //distance of star
UIMAPSKILL_STAR_DY                      =   0,          //
//
} UI_MAPSKILL_ENUMS;


// STRUCTURES //////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct tagUI_MAPSKILL_DATA 
{
    CAKE_FRAME_ANI  *cfa;       //frame ani pointer
    CAKE_FRAME      *cf[32];    //image pointer of each frame.
    //
    SLONG   hilight_id;         //hilight id
    SLONG   active_id;          //active id
    //
    SLONG   is_opened;  //技能介面是否打開
} UI_MAPSKILL_DATA, *LPUI_MAPSKILL_DATA;


// GLOBALS /////////////////////////////////////////////////////////////////////////////////////////////////////////
extern  UI_MAPSKILL_DATA    ui_mapskill_data;



// FUNCTIONS ///////////////////////////////////////////////////////////////////////////////////////////////////////
int     init_ui_mapskill(void);
void    active_ui_mapskill(int active);
void    free_ui_mapskill(void);
void    redraw_ui_mapskill(SLONG sx, SLONG sy, void *vbitmap);
void    refresh_ui_mapskill(void);
SLONG   handle_ui_mapskill(UINT message, WPARAM wParam, LPARAM lParam);
void    redraw_uimapskill_mouse_point_info(SLONG id, BMP *bitmap);
//
SLONG   is_mapskill_menu_opened(void);
void    open_mapskill_menu(SLONG flag);


#endif//_UIMAPSKILL_H_
