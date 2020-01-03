/*
**	UIMapQuickMagic.h
**	UI of map quick magics functions header.
**
**	Jack, 2002/09/13.
*/
#ifndef _UIMAPQUICKMAGIC_H_
#define _UIMAPQUICKMAGIC_H_



// D E F I N E S ///////////////////////////////////////////////////////////////////////////////////////////////////
//show quick magics flags
#define SHOW_NONE_QUICK_MAGICS          0   //不顯示快捷技能設置
#define SHOW_LEFT_QUICK_MAGICS          1   //顯示左側快捷技能設置
#define SHOW_RIGHT_QUICK_MAGICS         2   //顯示右側快捷技能設置


//quick magics-----
typedef enum    UIMAPQUICKMAGIC_ENUMS
{   UIMAP_ID_QUICK_MAGIC_0   =   1000,  //1000~1999(see also "uimap.h" for different id range)
//UIMAP_EVENT                =   3000,  //defined in "uimap.h".
//
//left quick magics position
UIMAP_LEFT_QUICK_MAGICS_SX   =   230,
UIMAP_LEFT_QUICK_MAGICS_SY   =   500,
UIMAP_LEFT_QUICK_MAGICS_DX   =   32,
UIMAP_LEFT_QUICK_MAGICS_DY   =   -32,
//right quick magics position
UIMAP_RIGHT_QUICK_MAGICS_SX  =   581,
UIMAP_RIGHT_QUICK_MAGICS_SY  =   500,
UIMAP_RIGHT_QUICK_MAGICS_DX  =   -32,
UIMAP_RIGHT_QUICK_MAGICS_DY  =   -32,
//
} UIMAPQUICKMAGIC_ENUMS;



// F U N C T I O N S ///////////////////////////////////////////////////////////////////////////////////////////////
//
void    redraw_map_ui_left_quick_magics(BMP *bitmap);
void    redraw_map_ui_right_quick_magics(BMP *bitmap);
void    redraw_map_ui_quick_magic_mouse_point_info(SLONG id, BMP *bitmap);
void    redraw_map_ui_magic_quick_info(SLONG sx, SLONG sy, SLONG quick_index, BMP *bitmap);
//
SLONG   filter_map_quick_magics(UINT message, WPARAM wParam, LPARAM lParam);
//
SLONG   is_left_quick_magics_ui_visible(void);
SLONG   is_right_quick_magics_ui_visible(void);
void    show_left_quick_magics_ui(void);
void    hide_left_quick_magics_ui(void);
void    show_right_quick_magics_ui(void);
void    hide_right_quick_magics_ui(void);




#endif//_UIMAPQUICKMAGIC_H_
