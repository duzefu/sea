/*
**	NetGE_MapProc.h
**	map proc functions header.
**
**	Jack, 2002/08/02.
*/
#pragma once


// DEFINES /////////////////////////////////////////////////////////////////////////////////////////////////////////
//
#define MAX_MAP_PROC            1024        //�̤j�a�Ϩƥ��
#define MAP_PROC_FILE_VERSION   0x00010000  //�a�Ϩƥ��󪩥�
#define MAP_PROC_FILE_EXT       "PRC"       //�a�Ϩƥ����X�i�W


//MAP PROC TYPES------------------------------
#define DUMMY_PROC              0   //�רƥ�
#define AUTO_PROC               1   //�۰ʨƥ�
#define ITEM_PROC               2   //�D��ƥ�
#define KEY_PROC                3   //��L�ƥ�




// STRUCTURES //////////////////////////////////////////////////////////////////////////////////////////////////////
//
//�a�Ϩƥ�ƾڵ��c
typedef struct tagMAP_PROC
{
    SLONG   id;         // proc id
    SLONG   type;       // proc type
    POLY    poly;       // proc poly
} MAP_PROC,*LPMAP_PROC;


//
//�a�Ϩƥ���ƾڵ��c
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


