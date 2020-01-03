///////////////////////////////////////////////////////////////////
//
//	UIShowMap.cpp
//
//	Zhang Zhaohui	2003/5/16
//
//	對世界地圖和藏寶圖的顯示和操作.
//
//	Copyright (c) Rays Multimedia. All rights reserved.
//
//////////////////////////////////////////////////////////////////

#include "UIShowMap.h"
#include "packfile.h"
#include "clientmain.h"
#include "CRange.h"
#include "NetGE_Item.h"
#include "Client_SendMsg.h"

//////////////////////////////////////////////////////////////////////////
// 類型定義
//////////////////////////////////////////////////////////////////////////

typedef VOID (*REDRAW_FUNC)( BMP * bitmap );

//////////////////////////////////////////////////////////////////////////
// 常量
//////////////////////////////////////////////////////////////////////////

enum SM_UI
{
    SM_EVENT        = 30010,

    SM_FRAME_BKGND      = 0,            // 在 CAKE 文件中的位置
    SM_FRAME_RIM        = 1,
    SM_FRAME_TM_BTN     = 2,
    SM_FRAME_WM_BTN     = 5,
    SM_FRAME_ZOOM_IN    = 8,
    SM_FRAME_ZOOM_OUT   = 11,
    SM_FRAME_SEPARATE   = 14,
    SM_FRAME_CLOSE      = 17,

    SM_FRAME_BIG_RED        = 0,
    SM_FRAME_BIG_GREEN      = 1,
    SM_FRAME_SMALL_RED      = 2,
    SM_FRAME_SMALL_GREEN    = 3,
    SM_FRAME_TM_POSITION    = 4,
    SM_FRAME_WM_POSITION    = 5,

    SM_ID_BKGND         = 0,            // game_range 中的標示符
    SM_ID_RIM           = 1,
    SM_ID_TM            = 2,
    SM_ID_WM            = 3,
    SM_ID_ZOOM_IN       = 4,
    SM_ID_ZOOM_OUT      = 5,
    SM_ID_CLOSE         = 6,
    SM_ID_TM_BTN        = 7,
    SM_ID_WM_BTN        = 8,
    SM_ID_SEPARATE_BTN  = 9,

    SM_ID_BIG_GREEN     = 10,
    SM_ID_BIG_RED       = 11,
    SM_ID_SMALL_GREEN   = 12,
    SM_ID_SMALL_RED     = 13,
    SM_ID_WM_POSITION   = 14,
    SM_ID_TM_POSITION   = 15,

    SM_TM_WIDTH         = 272,          // 藏寶圖寬
    SM_TM_HEIGHT        = 346,          // 藏寶圖高

    SM_TM_START_X       = 59,           // 藏寶圖座標
    SM_TM_START_Y       = 101,          // 藏寶圖座標
};


CONST CHAR SM_FILE_WORLDMAP[]   = "menu\\worldmap.cak";
CONST CHAR SM_FILE_MINWDMAP[]   = "menu\\minwdmap.cak";
CONST CHAR SM_FILE_WDMAPUI[]    = "menu\\wdmapui.cak";
CONST CHAR SM_FILE_MISC[]       = "menu\\smmisc.cak";

CONST CHAR SM_MASK_FILENAME_3[] = "menu\\tmmask3_1.cak";
CONST CHAR SM_MASK_FILENAME_5[] = "menu\\tmmask5_1.cak";
CONST CHAR SM_MASK_FILENAME_7[] = "menu\\tmmask7_1.cak";


//////////////////////////////////////////////////////////////////////////
// 變量
//////////////////////////////////////////////////////////////////////////


DWORD   sm_type = 0;        // 保存當前顯示的界面
TM      sm_tm;              // 保存藏寶圖的信息
WM      sm_wm;              // 保存世界地圖的信息

SM_UI_DATA   sm_data;       // 保存界面狀態


CAKE_FRAME_ANI  *sm_ui_cfa      = NULL;       // 界面
CAKE_FRAME      *sm_ui_cf[24];                // 界面動畫禎
CAKE_FRAME_ANI  *sm_wdmap_cfa   = NULL;       // 世界地圖
CAKE_FRAME_ANI  *sm_minwd_cfa   = NULL;       // 縮小的世界地圖
CAKE_FRAME_ANI  *sm_mask_cfa    = NULL;       // 藏寶圖的碎片
BMP             *sm_tm_bmp      = NULL;       // 藏寶圖圖像數據
BMP             *sm_wm_bmp      = NULL;       // 世界圖圖像數據
CAKE_FRAME_ANI  *sm_misc_cfa    = NULL;       // 各種標記 (城市, 位置 )
CAKE_FRAME      *sm_misc_cf[8];               // 標記動畫禎


REDRAW_FUNC sm_redraw = NULL;               // 藏寶圖上圖
REDRAW_FUNC sm_draw_btn = NULL;             // 界面按鈕


//////////////////////////////////////////////////////////////////////////
// 本地函數聲明
//////////////////////////////////////////////////////////////////////////

static VOID sm_on_show_tm( VOID );          // 初始化藏寶圖顯示數據
static VOID sm_on_show_wm( VOID );          // 初始化世界地圖顯示數據
static VOID sm_on_close( VOID );            // 釋放顯示數據佔用的內存
static VOID sm_redraw_tm( BMP *bitmap );    // 畫藏寶圖
static VOID sm_redraw_wm( BMP *bitmap );    // 畫世界地圖
static VOID sm_draw_btn_tm( BMP *bitmap );  // 畫藏寶圖按鈕
static VOID sm_draw_btn_wm( BMP *bitmap );  // 畫世界地圖按鈕

static LONG sm_load_mask( VOID );           // 載入藏寶圖碎片
static LONG sm_load_tm_bmp( VOID );         // 載入藏寶圖
static LONG sm_load_min_wdmap( VOID );      // 載入小世界地圖
static LONG sm_load_wdmap( VOID );          // 載入世界地圖

static VOID sm_free_mask( VOID );           // 釋放藏寶圖碎片數據
static VOID sm_free_tm_bmp( VOID );         // 釋放藏寶圖數據
static VOID sm_free_min_wdmap( VOID );      // 釋放小地圖數據
static VOID sm_free_wdmap( VOID );          // 釋放世界地圖數據

static VOID sm_clear_struct( VOID );        // 藏寶圖數據結構清零

static CHAR *sm_get_mask_filename( LONG );  // 獲得藏寶圖文件名

static VOID sm_draw_tm_point( BMP *bitmap );    // 畫寶藏位置
static VOID sm_draw_wm_point( BMP *bitmap );    // 在航海圖上畫當前位置
static VOID sm_draw_wm_citys( BMP *bitmap );    // 在航海圖上畫城市

//////////////////////////////////////////////////////////////////////////
// 全局函數
//////////////////////////////////////////////////////////////////////////

LONG  init_sm( VOID )
{
    LONG result, count, i;
    CAKE_FRAME_ANI *cfa;
    
    if ( sm_ui_cfa )
        return TTN_NOT_OK;

    // 結構變量清零
    sm_clear_struct( );

    // 載入界面數據
    set_data_file( packed_menu_file );
    result = load_cake_frame_ani_from_file( (USTR*)SM_FILE_WDMAPUI, &sm_ui_cfa );
    if ( result != TTN_OK )
        return TTN_NOT_OK;

    count = count_cake_frames( sm_ui_cfa );

    for ( i = 0; i < count; i ++ )
    {
        cfa = get_specify_cake_frame_ani( sm_ui_cfa, i );
        sm_ui_cf[i] = cfa->cake_frame;
    }

    // 載入標記數據 ( 城市, 位置 )
    result = load_cake_frame_ani_from_file( (USTR*)SM_FILE_MISC, &sm_misc_cfa );
    if ( result != TTN_OK )
        return TTN_NOT_OK;
    
    count = count_cake_frames( sm_misc_cfa );
    for ( i = 0; i < count; i ++  )
    {
        cfa = get_specify_cake_frame_ani( sm_misc_cfa, i );
        sm_misc_cf[i] = cfa->cake_frame;
    }

    return TTN_OK;
}


VOID  free_sm( VOID )
{
    if ( sm_misc_cfa )
        destroy_cake_frame_ani( &sm_misc_cfa );

    if ( sm_ui_cfa )
        destroy_cake_frame_ani( &sm_ui_cfa );

    sm_on_close( );

    sm_clear_struct( );
}


VOID  redraw_sm( BMP *bitmap )
{
    CAKE_FRAME *cf;
    LONG event, x, y;

    if ( !sm_redraw || !sm_draw_btn )
        return;

    event = SM_EVENT;

    // 背景 -------------------------------------------------

    cf = sm_ui_cf[SM_FRAME_BKGND];
    x = cf->frame_rx;
    y = cf->frame_ry;
    put_rle( x, y, cf->rle, bitmap );
    game_range.add( x, y, cf->rle->w, cf->rle->h, event, SM_ID_BKGND );

    // 藏寶圖 -----------------------------------------------
    sm_redraw( bitmap );


    // 邊框 -------------------------------------------------

    cf = sm_ui_cf[SM_FRAME_RIM];
    x = cf->frame_rx;
    y = cf->frame_ry;
    put_rle( x, y, cf->rle, bitmap );

    // 按鈕 -------------------------------------------------
    sm_draw_btn( bitmap );

    // "關閉" -----------------------------------------------
    if ( sm_data.hilight_id == SM_ID_SEPARATE_BTN )
        cf = sm_ui_cf[SM_FRAME_SEPARATE+1];
    else
        cf = sm_ui_cf[SM_FRAME_SEPARATE];
    x = cf->frame_rx;
    y = cf->frame_ry;
    put_rle( x, y, cf->rle, bitmap );
    game_range.add( x, y, cf->rle->w, cf->rle->h, event, SM_ID_CLOSE );

}


LONG  handle_sm( UINT msg, WPARAM wparam, LPARAM lparam )
{
    LONG result = 1;
    LONG event, id;
    LONG dx, dy;
    CAKE_FRAME_ANI *cfa;
    LONG max_w, max_h;

    if ( !sm_redraw )
        return result;

    switch ( msg )
    {
    case WM_MOUSEMOVE:
        game_range.mapping( GET_X_LPARAM( lparam ), GET_Y_LPARAM( lparam ),
                                &event, &id );
        if ( event == SM_EVENT )
        {

            if ( sm_data.active_id == SM_ID_WM && sm_data.zoom_in ) // 移動地圖
            {
                dx = GET_X_LPARAM( lparam ) - sm_wm.mouse_bx;
                dy = GET_Y_LPARAM( lparam ) - sm_wm.mouse_by;

                cfa = get_specify_cake_frame_ani( sm_wdmap_cfa, 0 );
                max_w = cfa->cake_frame->rle->w - SM_TM_WIDTH;
                max_h = cfa->cake_frame->rle->h - SM_TM_HEIGHT;
                
                sm_wm.left = sm_wm.bleft + dx;
                sm_wm.top  = sm_wm.btop + dy;

                // 限定左上角的座標範圍
                sm_wm.left = MAX( 0, sm_wm.left );
                sm_wm.left = MIN( sm_wm.left, max_w );
                sm_wm.top  = MAX( 0, sm_wm.top );
                sm_wm.top  = MIN( sm_wm.top, max_h );
            }
            sm_data.hilight_id = id;
        }
        else
            sm_data.hilight_id = 0;
        break;
    case WM_LBUTTONDOWN:
        game_range.mapping( GET_X_LPARAM( lparam ), GET_Y_LPARAM( lparam ), 
                                &event, &id );
        if ( event == SM_EVENT )
        {
            if ( id == SM_ID_WM && sm_data.zoom_in )        // 開始移動地圖
            {
                sm_wm.mouse_bx = GET_X_LPARAM( lparam );
                sm_wm.mouse_by = GET_Y_LPARAM( lparam );
                sm_wm.bleft = sm_wm.left;
                sm_wm.btop  = sm_wm.top;
            }
            sm_data.active_id = id;
            result = 0;
        }
        break;
    case WM_LBUTTONUP:
        game_range.mapping( GET_X_LPARAM( lparam ), GET_Y_LPARAM( lparam ),
                                &event, &id );
        if ( event == SM_EVENT && id == sm_data.active_id )
        {
            switch ( id )
            {
            case SM_ID_ZOOM_IN:
                sm_data.zoom_in = TRUE;
                break;
            case SM_ID_ZOOM_OUT:
                sm_data.zoom_in = FALSE;
                break;
            case SM_ID_TM_BTN:
                // TODO 設置藏寶圖資料結構
                sm_on_show_tm( );
                break;
            case SM_ID_WM_BTN:
                sm_on_show_wm( );
                break;
            case SM_ID_CLOSE:
                sm_set( TYPE_CLOSE );
                break;
            case SM_ID_SEPARATE_BTN:
                ClientRequestSeparateMap( sm_tm.index );
                break;
            default:
                break;
            }
            result = 0;
        }
        sm_data.active_id = 0;
        break;

    }
    return result;
}


VOID  sm_set( SHOW_MAP show_type )
{
    switch ( show_type )
    {
    case TYPE_TM:
        sm_on_show_tm( );
        break;
    case TYPE_WM:
        sm_on_show_wm( );
        break;
    default:
        sm_on_close( );
    }
}


//////////////////////////////////////////////////////////////////////////
// 設置 藏寶圖、航海圖 控制數據
//////////////////////////////////////////////////////////////////////////


VOID  sm_set_tm_info( TM *info )
{
    if ( info )
        sm_tm = *info;
}


VOID  sm_set_wm_info( WM *info )
{
    if ( info )
        sm_wm = *info;
}

TM    *sm_get_tm_info( VOID )
{
    return &sm_tm;
}

WM    *sm_get_wm_info( VOID )
{
    return &sm_wm;
}




//////////////////////////////////////////////////////////////////////////
// 動態圖像數據控制
//////////////////////////////////////////////////////////////////////////


VOID sm_on_show_tm( VOID )
{
    if ( sm_tm.style == 0 )
        return;

    if ( TTN_OK != sm_load_tm_bmp( ) )
        return;

    if ( TTN_OK != sm_load_mask( ) )
        return;

    sm_redraw = sm_redraw_tm;
    sm_draw_btn = sm_draw_btn_tm;

}

VOID sm_on_show_wm( VOID )
{
    if ( TTN_OK != sm_load_min_wdmap( ) )
        return;

    if ( TTN_OK != sm_load_wdmap( ) )
        return;

    sm_redraw = sm_redraw_wm;
    sm_draw_btn = sm_draw_btn_wm;
}

VOID sm_on_close( VOID )
{
    sm_redraw = NULL;
    sm_draw_btn = NULL;

    memset( &sm_tm, 0, sizeof( sm_tm ) );
    memset( &sm_wm, 0, sizeof( sm_wm ) );

    sm_free_wdmap( );
    sm_free_min_wdmap( );
    sm_free_mask( );
    sm_free_tm_bmp( );

}



//////////////////////////////////////////////////////////////////////////
// 顯示 (藏寶地圖 探險地圖 界面按鈕 )
//////////////////////////////////////////////////////////////////////////


VOID sm_redraw_tm( BMP *bitmap )
{
    LONG x, y;

    x = SM_TM_START_X;
    y = SM_TM_START_Y;

    put_bitmap( x, y, sm_tm_bmp, bitmap );
    game_range.add( x, y, sm_tm_bmp->w, sm_tm_bmp->h, SM_EVENT, SM_ID_TM );

    sm_draw_tm_point( bitmap );
}

VOID sm_redraw_wm( BMP *bitmap )
{
    CAKE_FRAME *cf;
    LONG event, x, y;

    event = SM_EVENT;

    if ( sm_data.zoom_in )
    {
        x = -sm_wm.left;
        y = -sm_wm.top;
        cf = get_specify_cake_frame_ani( sm_wdmap_cfa, 0 )->cake_frame;
        put_rle( x, y, cf->rle, sm_wm_bmp );
        
        x = SM_TM_START_X;
        y = SM_TM_START_Y;
        put_bitmap( SM_TM_START_X, SM_TM_START_Y, sm_wm_bmp, bitmap );
        game_range.add( x, y, sm_wm_bmp->w, sm_wm_bmp->h, event, SM_ID_WM );

    }
    else
    {
        cf = get_specify_cake_frame_ani( sm_minwd_cfa, 0 )->cake_frame;
        x = SM_TM_START_X;
        y = SM_TM_START_Y;
        put_rle( x, y, cf->rle, bitmap );
        game_range.add( x, y, cf->rle->w, cf->rle->h, event, SM_ID_WM );
    }

}

VOID sm_draw_btn_tm( BMP *bitmap )
{
    CAKE_FRAME *cf;
    LONG frame, x, y;
    

    // "航海圖" ---------------------------------------------
    frame = SM_FRAME_WM_BTN;
    if ( sm_data.active_id == SM_ID_WM_BTN )
        frame += 2;
    else if ( sm_data.hilight_id == SM_ID_WM_BTN )
        frame ++;
    cf = sm_ui_cf[frame];
    x = cf->frame_rx;
    y = cf->frame_ry;
    put_rle( x, y, cf->rle, bitmap );
    game_range.add( x, y, cf->rle->w, cf->rle->h, SM_EVENT, SM_ID_WM_BTN );

    // "拆開"   ---------------------------------------------
    frame = SM_FRAME_SEPARATE;
    if ( sm_data.active_id == SM_ID_SEPARATE_BTN )
        frame += 2;
    else if ( sm_data.hilight_id == SM_ID_SEPARATE_BTN )
        frame ++;
    cf = sm_ui_cf[frame];
    x = cf->frame_rx;
    y = cf->frame_ry;
    put_rle( x, y, cf->rle, bitmap );
    game_range.add( x, y, cf->rle->w, cf->rle->h, SM_EVENT, SM_ID_SEPARATE_BTN );

}


VOID sm_draw_btn_wm( BMP *bitmap )
{
    CAKE_FRAME *cf;
    LONG event, id, frame, x, y;

    event = SM_EVENT;

    
    // "藏寶圖" ---------------------------------------------
    if ( sm_tm.style == 0 )
    {
        cf = sm_ui_cf[SM_FRAME_TM_BTN];
        gray_put_rle(  cf->frame_rx, cf->frame_ry, cf->rle, bitmap );
    }
    else
    {
        frame = SM_FRAME_TM_BTN;
        if ( sm_data.active_id == SM_ID_TM_BTN )
            frame += 2;
        else if ( sm_data.hilight_id == SM_ID_TM_BTN )
            frame++;
        cf = sm_ui_cf[frame];
        x = cf->frame_rx;
        y = cf->frame_ry;
        put_rle( x, y, cf->rle, bitmap );
        game_range.add( x, y, cf->rle->w, cf->rle->h, SM_EVENT, SM_ID_TM_BTN );
    }


    // "放大"   ---------------------------------------------
    if ( sm_data.zoom_in )
    {
        cf = sm_ui_cf[SM_FRAME_ZOOM_IN];
        gray_put_rle( cf->frame_rx, cf->frame_ry, cf->rle, bitmap );
    }
    else
    {
        id = SM_ID_ZOOM_IN;
        frame = SM_FRAME_ZOOM_IN;
        if ( sm_data.active_id == id )
            frame += 2;
        else
            frame++;
        cf = sm_ui_cf[frame];
        x = cf->frame_rx;
        y = cf->frame_ry;
        put_rle( x, y, cf->rle, bitmap );
        game_range.add( x, y, cf->rle->w, cf->rle->h, SM_EVENT, id );
    }
    
    // "縮小"   ---------------------------------------------
    if ( sm_data.zoom_in )
    {
        id = SM_ID_ZOOM_OUT;
        frame = SM_FRAME_ZOOM_OUT;
        if ( sm_data.active_id == id )
            frame += 2;
        else
            frame++;
        cf = sm_ui_cf[frame];
        x = cf->frame_rx;
        y = cf->frame_ry;
        put_rle( x, y, cf->rle, bitmap );
        game_range.add( x, y, cf->rle->w, cf->rle->h, SM_EVENT, id );
    }
    else
    {
        cf = sm_ui_cf[SM_FRAME_ZOOM_OUT];
        gray_put_rle( cf->frame_rx, cf->frame_ry, cf->rle, bitmap );
    }
}


//////////////////////////////////////////////////////////////////////////
// 動態載入圖像數據
//////////////////////////////////////////////////////////////////////////

LONG sm_load_mask( VOID )
{
    CAKE_FRAME_ANI *cfa, *cfa0;
    CHAR *filename;
    LONG result;
    LONG count, i, j;
    LONG bx, by, x, y;

    if ( !sm_tm_bmp )
        return TTN_NOT_OK;
    
    // 獲得碎片圖像文件名
    filename = sm_get_mask_filename( sm_tm.style );
    if ( !filename )
        return TTN_NOT_OK;

    result = load_cake_frame_ani_from_file( (USTR*)filename, &sm_mask_cfa );
    
    if ( result != TTN_OK )
        return TTN_NOT_OK;

    count = count_cake_frames( sm_mask_cfa );
    j = 0;

    cfa0 = get_specify_cake_frame_ani( sm_mask_cfa, 0 );
    bx = cfa0->cake_frame->frame_rx;
    by = cfa0->cake_frame->frame_ry;

    // 畫碎片
    for ( i = 1; i < count; i ++ )
    {
        if ( !( sm_tm.mask & TM_MASK[i-1 ] ))
        {
            cfa = get_specify_cake_frame_ani( sm_mask_cfa, i );
            x = cfa->cake_frame->frame_rx - bx;
            y = cfa->cake_frame->frame_ry - by;
            put_rle( x, y, cfa->cake_frame->rle, sm_tm_bmp );
            j ++;
        }
    }

    // 畫碎片拼合線
    cfa = get_specify_cake_frame_ani( sm_mask_cfa, 0 );
//    put_rle( 0, 0, cfa->rle, sm_tm_bmp );

    destroy_cake_frame_ani( &sm_mask_cfa );

    return TTN_OK;
}


LONG sm_load_tm_bmp( VOID )
{
    LONG x, y;
    CAKE_FRAME *cf;

    if ( sm_tm_bmp )
        return TTN_OK;

    sm_tm_bmp = create_bitmap( SM_TM_WIDTH, SM_TM_HEIGHT );
    if ( !sm_tm_bmp )
        return TTN_NOT_OK;

    // 獲得大地圖的數據
    if ( !sm_wdmap_cfa )
    {
        if ( TTN_OK != sm_load_wdmap( ) )
        {
            sm_free_tm_bmp( );
            return TTN_NOT_OK;
        }
    }
    x = -sm_tm.top;
    y = -sm_tm.left;

    cf = get_specify_cake_frame_ani( sm_wdmap_cfa, 0 )->cake_frame;
    put_rle( x, y, cf->rle, sm_tm_bmp );

    return TTN_OK;
}


LONG sm_load_min_wdmap( VOID )
{
    LONG result;

    if ( sm_minwd_cfa )
        return TTN_OK;

    result = load_cake_frame_ani_from_file( (USTR*)SM_FILE_MINWDMAP, &sm_minwd_cfa );
    if ( result != TTN_OK )
        return TTN_NOT_OK;
    
    return TTN_OK;
}


LONG sm_load_wdmap( VOID )
{
    LONG result;

    if ( sm_wdmap_cfa && sm_wm_bmp )
        return TTN_OK;

    sm_wm_bmp = create_bitmap( SM_TM_WIDTH, SM_TM_HEIGHT );
    if ( !sm_wm_bmp )
        return TTN_NOT_OK;

    if ( !sm_wdmap_cfa )
    {
        result = load_cake_frame_ani_from_file( (USTR*)SM_FILE_WORLDMAP, &sm_wdmap_cfa );
        if (result != TTN_OK )
        {
            destroy_bitmap( &sm_wm_bmp );
            return TTN_NOT_OK;
        }
    }

    return TTN_OK;
}


//////////////////////////////////////////////////////////////////////////
// 釋放圖像數據佔用的內存
//////////////////////////////////////////////////////////////////////////


VOID sm_free_mask( VOID )
{
}


VOID sm_free_tm_bmp( VOID )
{
    if ( sm_tm_bmp )
        destroy_bitmap( &sm_tm_bmp );
}


VOID sm_free_min_wdmap( VOID )
{
    if ( sm_minwd_cfa )
        destroy_cake_frame_ani( &sm_minwd_cfa );
}


VOID sm_free_wdmap( VOID )
{
    if ( sm_wdmap_cfa )
        destroy_cake_frame_ani( &sm_wdmap_cfa );

    if ( sm_wm_bmp )
        destroy_bitmap( &sm_wm_bmp );
}


//////////////////////////////////////////////////////////////////////////
// 藏寶圖數據結構清零
//////////////////////////////////////////////////////////////////////////

VOID sm_clear_struct( VOID )
{
    memset( &sm_ui_cf,   0, sizeof( sm_ui_cf   ) );
    memset( &sm_tm,      0, sizeof( sm_tm      ) );
    memset( &sm_wm,      0, sizeof( sm_wm      ) );
    memset( &sm_data,    0, sizeof( sm_data    ) );
    memset( &sm_misc_cf, 0, sizeof( sm_misc_cf ) );

    sm_redraw = NULL;
    sm_draw_btn = NULL;
}

//////////////////////////////////////////////////////////////////////////
// 獲得藏寶圖碎片文件的文件名
//////////////////////////////////////////////////////////////////////////

CHAR *sm_get_mask_filename( LONG style)
{
    CHAR *result = NULL;

    switch ( style )
    {
    case TM_MASK_STYLE_3:
        result = (CHAR*)SM_MASK_FILENAME_3;
        break;
    case TM_MASK_STYLE_5:
        result = (CHAR*)SM_MASK_FILENAME_5;
        break;
    case TM_MASK_STYLE_7:
        result = (CHAR*)SM_MASK_FILENAME_7;
        break;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////
// 畫寶藏位置
//////////////////////////////////////////////////////////////////////////

VOID sm_draw_tm_point( BMP *bitmap )
{
    SLONG frame, x, y;
    CAKE_FRAME *cf;

    if ( sm_tm.mask != TM_MASK_FULL[sm_tm.style] )
        return;

    frame = SM_FRAME_TM_POSITION;
    cf = sm_misc_cf[frame];
    x = SM_TM_START_X + sm_tm.x - sm_tm.left - cf->rle->w/2;
    y = SM_TM_START_Y + sm_tm.y - sm_tm.top - cf->rle->h/2;

    put_rle( x, y, cf->rle, bitmap );


}


//////////////////////////////////////////////////////////////////////////
// 玩家位置
//////////////////////////////////////////////////////////////////////////

VOID sm_draw_wm_point( BMP *bitmap )
{
    /*
     *	TODO 畫玩家位置
     */
}

//////////////////////////////////////////////////////////////////////////
// 城市
//////////////////////////////////////////////////////////////////////////

VOID sm_draw_wm_citys( BMP *bitmap )
{
    /*
     *	TODO 畫城市
     */
}