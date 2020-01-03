/*
**	NetGE_MapProc.h
**	map proc functions header.
**
**	Jack, 2002/08/02.
*/
#pragma once


// DEFINES /////////////////////////////////////////////////////////////////////////////////////////////////////////
//
#define MAX_MAP_PROC            1024        //最大地圖事件數
#define MAP_PROC_FILE_VERSION   0x00010000  //地圖事件文件版本
#define MAP_PROC_FILE_EXT       "PRC"       //地圖事件文件擴展名


//MAP PROC TYPES------------------------------
#define DUMMY_PROC              0   //啞事件
#define AUTO_PROC               1   //自動事件
#define ITEM_PROC               2   //道具事件
#define KEY_PROC                3   //鍵盤事件




// STRUCTURES //////////////////////////////////////////////////////////////////////////////////////////////////////
//
//地圖事件數據結構
typedef struct tagMAP_PROC
{
    SLONG   id;         // proc id
    SLONG   type;       // proc type
    POLY    poly;       // proc poly
} MAP_PROC,*LPMAP_PROC;


//
//地圖事件文件數據結構
typedef struct tagMAP_PROC_HEAD 
{
    ULONG   copyright;      //copyright 'RAYS'
    ULONG   id;             //file id 'PROC'
    ULONG   version;        //MAP_PROC_FILE_VERSION
    ULONG   head_size;      //size of the file head
    //
    SLONG   map_xl;         //map pixel width
    SLONG   map_yl;         //map pixel height
    SLONG   total_procs;    //total map procs
} MAP_PROC_HEAD, *LPMAP_PROC_HEAD;



//GLOBALS /////////////////////////////////////////////////////////////////////////////////////////
//
extern  MAP_PROC        map_proc[MAX_MAP_PROC];
extern  SLONG           map_proc_max;
extern  MAP_PROC_HEAD   map_proc_head;



//FUNCTION PROTOTYPES ////////////////////////////////////////////////////////////////////////////
//
extern	void    reset_map_proc_count(void);
extern	void    set_map_proc_count(SLONG count);
extern  void    clear_all_map_procs(void);
extern	void    naked_read_map_proc(PACK_FILE *fp, SLONG read_procs);
extern  SLONG   load_map_proc(USTR *filename);
extern  BOOL    match_map_proc(SLONG x, SLONG y, SLONG *proc_id, SLONG *proc_type);


