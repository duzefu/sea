/*
**	UIMapState.h
**	UI of map state.
**
**	Jack, 2002/07/03.
*/
#ifndef _UIMAPSTATE_H_
#define _UIMAPSTATE_H_



// DEFINES /////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef enum    UI_MAPSTATE_ENUMS
{   UIMAPSTATE_FRAME_BKGND          =   0,
UIMAPSTATE_FRAME_LOGBOOK            =   1,
UIMAPSTATE_FRAME_TITLE              =   2,
UIMAPSTATE_FRAME_PREV_PAGE          =   3,
UIMAPSTATE_FRAME_NEXT_PAGE          =   4,
UIMAPSTATE_FRAME_CLOSE              =   5,
//
UIMAPSTATE_EVENT                    =   3002,
UIMAPSTATE_ID_BKGND                 =   0,
UIMAPSTATE_ID_PREV_PAGE             =   10,
UIMAPSTATE_ID_NEXT_PAGE             =   20,
UIMAPSTATE_ID_CLOSE                 =   30,
//
UIMAPSTATE_PHOTO_SX                 =   54,
UIMAPSTATE_PHOTO_SY                 =   165,
UIMAPSTATE_PHOTO_XL                 =   104 - 54,
UIMAPSTATE_PHOTO_YL                 =   231 - 165,

UIMAPSTATE_MAINNAME_SX              =   192,
UIMAPSTATE_MAINNAME_SY              =   157,
UIMAPSTATE_MAINNAME_XL              =   116,
UIMAPSTATE_MAINNAME_YL              =   14,

UIMAPSTATE_NICKNAME_SX              =   192,
UIMAPSTATE_NICKNAME_SY              =   179,
UIMAPSTATE_NICKNAME_XL              =   116,
UIMAPSTATE_NICKNAME_YL              =   14,

UIMAPSTATE_CAREER_SX                =   192,
UIMAPSTATE_CAREER_SY                =   201,
UIMAPSTATE_CAREER_XL                =   116,
UIMAPSTATE_CAREER_YL                =   14,

UIMAPSTATE_SPOUSE_SX                =   192,
UIMAPSTATE_SPOUSE_SY                =   219,
UIMAPSTATE_SPOUSE_XL                =   116,
UIMAPSTATE_SPOUSE_YL                =   14,

UIMAPSTATE_EXP_SX                   =   192,
UIMAPSTATE_EXP_SY                   =   240,
UIMAPSTATE_EXP_XL                   =   116,
UIMAPSTATE_EXP_YL                   =   14,

UIMAPSTATE_LEFT_TEXT_SX             =   60,
UIMAPSTATE_LEFT_TEXT_SY             =   280,
UIMAPSTATE_LEFT_TEXT_XL             =   100,
UIMAPSTATE_LEFT_TEXT_YL             =   180,
UIMAPSTATE_RIGHT_TEXT_SX            =   196,
UIMAPSTATE_RIGHT_TEXT_SY            =   280,
UIMAPSTATE_RIGHT_TEXT_XL            =   100,
UIMAPSTATE_RIGHT_TEXT_YL            =   180,

UIMAPSTATE_COUNTRY_SX               =   244,
UIMAPSTATE_COUNTRY_SY               =   287,
UIMAPSTATE_COUNTRY_XL               =   60,
UIMAPSTATE_COUNTRY_YL               =   14,

UIMAPSTATE_NOBILITY_SX              =   244,
UIMAPSTATE_NOBILITY_SY              =   309,
UIMAPSTATE_NOBILITY_XL              =   60,
UIMAPSTATE_NOBILITY_YL              =   14,

UIMAPSTATE_GUILD_SX                 =   244,
UIMAPSTATE_GUILD_SY                 =   331,
UIMAPSTATE_GUILD_XL                 =   60,
UIMAPSTATE_GUILD_YL                 =   14,

UIMAPSTATE_PRESTIGE_SX              =   196,
UIMAPSTATE_PRESTIGE_SY              =   371,
UIMAPSTATE_PRESTIGE_XL              =   100,
UIMAPSTATE_PRESTIGE_YL              =   14,

UIMAPSTATE_PKVALUE_SX               =   196,
UIMAPSTATE_PKVALUE_SY               =   408,
UIMAPSTATE_PKVALUE_XL               =   100,
UIMAPSTATE_PKVALUE_YL               =   14,

UIMAPSTATE_DEPOSIT_SX               =   196,
UIMAPSTATE_DEPOSIT_SY               =   448,
UIMAPSTATE_DEPOSIT_XL               =   100,
UIMAPSTATE_DEPOSIT_YL               =   14,
//
UIMAPSTATE_MENU_SHOW_PAGE           =   0,
UIMAPSTATE_MENU_TURN_TO_NEXT_PAGE   =   1,
UIMAPSTATE_MENU_TURN_TO_PREV_PAGE   =   2,
} UI_MAPSTATE_ENUMS;




// STRUCTURES //////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct tagUI_MAPSTATE_DATA 
{
    CAKE_FRAME_ANI  *cfa;       //frame ani pointer
    CAKE_FRAME      *cf[32];    //image pointer of each frame.
    //
    SLONG   hilight_id;         //hilight id
    SLONG   active_id;          //active id
    //
    CAKE_FRAME_ANI  *book_cfa;      //book frame ani pointer
    CAKE_FRAME      *book_cf[16];   //book image pointer of each frame
    SLONG   book_frame;             //current book frame
    SLONG   book_frames;            //total book frames
    //
    SLONG   book_page;              //current book page.
    SLONG   total_pages;            //total book pages.
    //
    SLONG   menu_state;             //menu state.
    DWORD   menu_time;              //menu time.
    //
    SLONG   is_opened;  //狀態介面是否打開

} UI_MAPSTATE_DATA, *LPUI_MAPSTATE_DATA;


// GLOBALS /////////////////////////////////////////////////////////////////////////////////////////////////////////
extern  UI_MAPSTATE_DATA ui_mapstate_data;



// FUNCTIONS ///////////////////////////////////////////////////////////////////////////////////////////////////////
int     init_ui_mapstate(void);
void    active_ui_mapstate(int active);
void    free_ui_mapstate(void);
void    redraw_ui_mapstate(SLONG sx, SLONG sy, void *vbitmap);
void    refresh_ui_mapstate(void);
SLONG   handle_ui_mapstate(UINT message, WPARAM wParam, LPARAM lParam);
void    redraw_uimapstate_mouse_point_info(SLONG id, BMP *bitmap);
//
SLONG   is_mapstate_menu_opened(void);
void    open_mapstate_menu(SLONG flag);


#endif//_UIMAPSTATE_H_
