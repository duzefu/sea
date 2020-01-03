/*
**	UILoading.h
**	User interface of loading.
**
**	Jack, 2002/10/17.
*/
#ifndef _UILOADING_H_
#define _UILOADING_H_



// S T R U C T U R E S /////////////////////////////////////////////////////////////////////////////////////////////
typedef struct tagLOADING_MAINGAME_DATA 
{
    CAKE_FRAME_ANI  *cfa;   //frame ani pointer.
    CAKE_FRAME      *cf[1]; //image pointer of each frame.
    //
    USTR    title[64];      //標題文字
    SLONG   effect;         //效果
    //
} LOADING_MAINGAME_DATA, *LPLOADING_MAINGAME_DATA;


typedef struct tagUI_CHANGEMAP_LOADING
{
    USTR    title[64];      //標題文字
    SLONG   effect;         //效果
} UI_CHANGEMAP_LOADING, *LPUI_CHANGEMAP_LOADING;

// G L O B A L S ///////////////////////////////////////////////////////////////////////////////////////////////////
extern  LOADING_MAINGAME_DATA   loading_maingame_data;
extern  UI_CHANGEMAP_LOADING    ui_changemap_loading;


// F U N C T I O N S ///////////////////////////////////////////////////////////////////////////////////////////////
//ui loading main game --------------------------
int     init_loading_main_game(void);
void    active_loading_main_game(int active);
void    free_loading_main_game(void);
void    refresh_loading_main_game(void);
void    redraw_loading_main_game(SLONG sx, SLONG sy, void *vbitmap);
SLONG   handle_loading_main_game(UINT message, WPARAM wParam, LPARAM lParam);


//ui change map loading -------------------------
int     init_changemap_loading(void);
void    active_changemap_loading(int active);
void    free_changemap_loading(void);
void    refresh_changemap_loading(void);
void    redraw_changemap_loading(SLONG sx, SLONG sy, void *vbitmap);
SLONG   handle_changemap_loading(UINT message, WPARAM wParam, LPARAM lParam);

//transfering waiting ---------------------------
void    redraw_transfer_waiting(void *vbitmap);



#endif//_UILOADING_H_
