///////////////////////////////////////////////////////////////////
//
//	UIShowMap.h
//
//	Zhang Zhaohui	2003/5/16
//
//	��@�ɦa�ϩM���_�Ϫ���ܩM�ާ@
//
//	Copyright (c) Rays Multimedia. All rights reserved.
//
//////////////////////////////////////////////////////////////////


#pragma once

#include "mainfun.h"


//////////////////////////////////////////////////////////////////////////
// �`�q�w�q
//////////////////////////////////////////////////////////////////////////

#define TM_MASK_STYLE_3     3       // ���_�ϸH����
#define TM_MASK_STYLE_5     5
#define TM_MASK_STYLE_7     7

#define TM_MAX_MASK_COUNT   16      // �̦h���H����

enum SHOW_MAP
{
    TYPE_TM         = 1,                // ���_��������
    TYPE_WM         = 2,                // ��j�᪺�@�ɦa��������
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
// ���_�� �M �@�ɦa�� ���c
//////////////////////////////////////////////////////////////////////////

typedef struct tagTREASURE_MAP
{

    LONG    top, left;  // ���_�Ϧb�j�a�Ϥ�����m
    LONG    x, y;       // �_�æ�m(�۹�y��)
    CHAR    name[32];   // ���_�Ϫ��W�r
    CHAR    info[256];  // ���_�Ϫ�����
    DWORD   style;      // ���_�Ϥ����X��
    DWORD   kind;       // ���_�ϸH��������
    DWORD   mask;       // ��e�֦����H��( ����G�i��P )
    DWORD   index;      // ���_�Ϲ������˳Ʈ�

} TM;

typedef struct tagWORLD_MAP
{

    LONG    x, y;       // ���a�b�@�ɦa�Ϥ�����m
    LONG    left, top;  // ��j��a�Ϫ����W������
    LONG    mouse_bx;   // �}�l���ʦa�Ϯɹ��Ъ��y��
    LONG    mouse_by;   
    LONG    bleft;      // �}�l���ʦa�Ϯɹ��Ъ��y��
    LONG    btop;

} WM;

typedef struct tagSM_UI_DATA
{
    LONG    hilight_id;
    LONG    active_id;
    LONG    function_id;

    BOOL    zoom_in;    // ��ܥ@�ɦa�ϥΨӦs�x��j�Y�p�����A
} SM_UI_DATA;

//////////////////////////////////////////////////////////////////////////
// ����n��
//////////////////////////////////////////////////////////////////////////

LONG  init_sm( VOID );
VOID  free_sm( VOID );

VOID  redraw_sm( BMP *bitmap );
LONG  handle_sm( UINT msg, WPARAM wparam, LPARAM lparam );


VOID  sm_set( SHOW_MAP show_type );        // �]�w�n��ܪ��ɭ�, 0 ������

VOID  sm_set_tm_info( TM *info );
VOID  sm_set_wm_info( WM *info );
TM    *sm_get_tm_info( VOID );
WM    *sm_get_wm_info( VOID );


