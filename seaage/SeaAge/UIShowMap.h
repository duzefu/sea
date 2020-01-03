///////////////////////////////////////////////////////////////////
//
//	UIShowMap.h
//
//	Zhang Zhaohui	2003/5/16
//
//	對世界地圖和藏寶圖的顯示和操作
//
//	Copyright (c) Rays Multimedia. All rights reserved.
//
//////////////////////////////////////////////////////////////////


#pragma once

#include "mainfun.h"


//////////////////////////////////////////////////////////////////////////
// 常量定義
//////////////////////////////////////////////////////////////////////////

#define TM_MASK_STYLE_3     3       // 藏寶圖碎片數
#define TM_MASK_STYLE_5     5
#define TM_MASK_STYLE_7     7

#define TM_MAX_MASK_COUNT   16      // 最多的碎片數

enum SHOW_MAP
{
    TYPE_TM         = 1,                // 藏寶圖類型號
    TYPE_WM         = 2,                // 放大後的世界地圖類型號
    TYPE_CLOSE      = 0,
};

CONST DWORD TM_MASK[TM_MAX_MASK_COUNT] = 
{
    0x00000001,
    0x00000002,
    0x00000004,
    0x00000008,
    0x00000010,
    0x00000020,
    0x00000040,
    0x00000080,
    0x00000100,
    0x00000200,
    0x00000400,
    0x00000800,
    0x00001000,
    0x00002000,
    0x00004000,
    0x00008000
};

CONST DWORD TM_MASK_FULL[TM_MAX_MASK_COUNT] = 
{
    0, 
    0,
    0,
    0x00000007,
    0,
    0x00000015,
    0,
    0x0000007f,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
};

//////////////////////////////////////////////////////////////////////////
// 藏寶圖 和 世界地圖 結構
//////////////////////////////////////////////////////////////////////////

typedef struct tagTREASURE_MAP
{

    LONG    top, left;  // 藏寶圖在大地圖中的位置
    LONG    x, y;       // 寶藏位置(相對座標)
    CHAR    name[32];   // 藏寶圖的名字
    CHAR    info[256];  // 藏寶圖的說明
    DWORD   style;      // 藏寶圖分為幾片
    DWORD   kind;       // 藏寶圖碎塊的種類
    DWORD   mask;       // 當前擁有的碎片( 按位二進制與 )
    DWORD   index;      // 藏寶圖對應的裝備格

} TM;

typedef struct tagWORLD_MAP
{

    LONG    x, y;       // 玩家在世界地圖中的位置
    LONG    left, top;  // 放大後地圖的左上角走標
    LONG    mouse_bx;   // 開始移動地圖時鼠標的座標
    LONG    mouse_by;   
    LONG    bleft;      // 開始移動地圖時鼠標的座標
    LONG    btop;

} WM;

typedef struct tagSM_UI_DATA
{
    LONG    hilight_id;
    LONG    active_id;
    LONG    function_id;

    BOOL    zoom_in;    // 顯示世界地圖用來存儲放大縮小的狀態
} SM_UI_DATA;

//////////////////////////////////////////////////////////////////////////
// 函數聲明
//////////////////////////////////////////////////////////////////////////

LONG  init_sm( VOID );
VOID  free_sm( VOID );

VOID  redraw_sm( BMP *bitmap );
LONG  handle_sm( UINT msg, WPARAM wparam, LPARAM lparam );


VOID  sm_set( SHOW_MAP show_type );        // 設定要顯示的界面, 0 為關閉

VOID  sm_set_tm_info( TM *info );
VOID  sm_set_wm_info( WM *info );
TM    *sm_get_tm_info( VOID );
WM    *sm_get_wm_info( VOID );


