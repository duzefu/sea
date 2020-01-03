/*
**      MAP.H
**      map function header.
**      Jian,2000/8/16.
*/
#ifndef MAP_H_INCLUDE
#define MAP_H_INCLUDE   1
#include "xgrafx.h"
#include "xpoly.h"
#include "MapObject.h"
#include "NetGE_MapMask.h"
#include "NetGE_MapProc.h"


// D E F I N E S ////////////////////////////////////////////////////////////////////////////////////////////////
#define MAP_DIRECTORY           "map"
#define MAP_VERSION             0x00010001
//
#define MAP_LAYER_NONE          0x00000000
#define MAP_LAYER_TILE          0x00000001
#define MAP_LAYER_UPPER         0x00000002
#define MAP_LAYER_OBJECT        0x00000004
#define MAP_LAYER_HOUSE         0x00000008
//
#define MAX_MAP_OBJECT          4096
//
#define ALL_MAP_OBJECTS         -1
//
//map object flags.
#define MOBJ_ACTIVE             0x00000001  //����ثe�Q��
#define MOBJ_MARKED             0x00000002  //����Q�襤
#define MOBJ_UNDER              0x00000004  //����N�|�Q�k�������h����
//
//object types
#define MOBJ_TYPES              0xff000000  //�a�Ϫ�����������X
#define MOBJ_SIMPLE             0x01000000  //²�檺��V�a�Ϫ���A�����a�Ϫ���w
#define MOBJ_DYNAMIC            0x02000000  //�h�V�ʵe�a�Ϫ���A�����a�Ϫ���w
#define MOBJ_FIXED              0x03000000  //PSD�a�Ϥ����T�w����
#define MOBJ_HOUSE_OBJECT       0x04000000  //�ЫΪ���������
#define MOBJ_HOUSE_ROOF         0x05000000  //�ЫΪ��γ�
#define MOBJ_NPC                0x06000000  //�H��������
#define MOBJ_MAGIC              0x07000000  //�k�N������
#define MOBJ_DOOR               0x08000000  //��������A�i�H�}���A�a����
//
//object update flags
#define MOBJ_UPDATES            0x00ff0000  //�a�Ϫ����s���X
#define MOBJ_UPDATE_MAGIC       0x00010000  //�k�N������g�L��s
#define MOBJ_UPDATE_NPC         0x00020000  //�H��������g�L��s
//


//map types.
#define MAP_TYPE_EDIT				1
#define MAP_TYPE_RENDER				2

//redraw edit map flags.
#define REDRAW_MAP_TILE_IMAGE       0x00000001  //�ϯ�
#define REDRAW_MAP_TILE_GRID        0x00000002  //
#define REDRAW_MAP_UPPER_IMAGE      0x00000004  //�a��
#define REDRAW_MAP_UNDER_OBJECT     0x00000008  //����
#define REDRAW_MAP_NORMAL_OBJECT    0x00000010  //
#define REDRAW_MAP_TRACK_IMAGE      0x00000020  //�}�L
#define REDRAW_MAP_BLOCK_INFO       0x00000040  //�a��
#define REDRAW_MAP_PROC_INFO        0x00000080  //�ƥ�
#define REDRAW_MAP_RECT_RANGE       0x00000100  //�x�����
#define REDRAW_MAP_DIAMOND_RANGE    0x00000200  //�٧����
#define REDRAW_MAP_REFRESH_OBJECT   0x00000400  //�۰ʨ�s����Ϲ�
#define REDRAW_MAP_REFRESH_NPC      0x00000800  //�۰ʨ�s�ܢޢѹϹ�
#define REDRAW_MAP_CURRENT_PATH     0x00001000  //��e�a�ϸ��|
#define REDRAW_MAP_ADJUST_START     0x00002000  //�۰ʮե��a�Ϧ�m
#define REDRAW_MAP_CLEAR_BITMAP     0x00004000  //���M������
#define REDRAW_MAP_HOUSE_ROOF       0x00008000  //�ЫΫγ�
#define	REDRAW_MAP_OBJECT_POLY		0x00010000	//��ܪ������
//
#define	OBJECT_POLY_FLAGS			(PDP_VALID | PDP_BASE | PDP_HEIGHT | PDP_ARRIS | PDP_TOP | PDP_CROSS | PDP_PROJECTION | PDP_ZHEIGHT)
												//��ܪ���������лx

//------------------------------------------------
//map move types.
#define MAP_MOVE_STAY_CURRENT       0
#define MAP_MOVE_TO_POSITION        1
#define MAP_MOVE_FOLLOW_NPC         2
#define MAP_MOVE_AUTO               3
//map move datas.
#define MAP_MOVE_FREE               0
#define MAP_MOVE_KEEP               1
#define MAP_MOVE_ACCELATE_MAX       16
#define MAP_MOVE_ACCELATE_MIN       -16
#define MAP_MOVE_SPEED_MAX          16
#define MAP_MOVE_SPEED_MIN          -16



#define	GET_MAP_OBJECT_TYPE(flag)		(((flag) & MOBJ_TYPES) >> 24)
#define	GET_HOUSE_INDEX(id)				(((id) & 0xffff0000) >> 16)
#define	GET_HOUSE_OBJECT_INDEX(id)		(((id) & 0xffff) - 1)


// S T R U C T U R E S //////////////////////////////////////////////////////////////////////////////////////////
typedef struct  tagMAP_DATA
{
    USTR    filename[80];   // now map filename
    USTR    mapname[80];    // now map text name
    SLONG   redraw_flags;   // map redraw flags
    SLONG   map_sx;         // now map left-up x position
    SLONG   map_sy;         // now map left-up y position
    SLONG   map_tx;         // map target left-up x position
    SLONG   map_ty;         // map target left-up y position
    SLONG   map_mx;         // map move speed x pixels
    SLONG   map_my;         // map move speed y pixels
    SLONG   map_ax;         // map x acceleration
    SLONG   map_ay;         // map y acceleration
    SLONG   view_sx;        // view left-up x position
    SLONG   view_sy;        // view left-up y position
    SLONG   view_xl;        // view range width
    SLONG   view_yl;        // view range height
    //
    SLONG   zoom_win_def_xl;// default zoom window width
    SLONG   zoom_win_def_yl;// default zoom window height
    SLONG   zoom_win_sx;    // screen zoom window left-up x position
    SLONG   zoom_win_sy;    // screen zoom window left-up y position
    SLONG   zoom_win_xl;    // screen zoom window width
    SLONG   zoom_win_yl;    // screen zoom window height
    SLONG   zoom_map_sx;    // map zoom range start x position
    SLONG   zoom_map_sy;    // map zoom range start y position
    SLONG   zoom_map_xl;    // map zoom range width
    SLONG   zoom_map_yl;    // map zoom range height
    double  zoom_control;   // map zoom control
    //
} MAP_DATA,*LPMAP_DATA;



typedef struct  tagMAP_HEAD
{
    USTR    copyright[4];   //"RAYS"
    USTR    id[4];          //"MAP "
    SLONG   version;        // MAP_VERSION
    SLONG   head_size;      // map head size
    SLONG   type;           // map type
    SLONG   layer;          // map layer information
    SLONG   map_xl;         // map pixel width
    SLONG   map_yl;         // map pixel height
    SLONG   cell_xl;        // map cell width
    SLONG   cell_yl;        // map cell height
    SLONG   map_cxl;        // map cell table width
    SLONG   map_cyl;        // map cell table height
    SLONG   total_uppers;   // count of map upper
    SLONG   total_objects;  // count of map object
    SLONG   total_houses;   // count of map houses
    SLONG   total_blocks;   // count of map blocks
    SLONG   total_procs;    // count of map proc
} MAP_HEAD,*LPMAP_HEAD;


//�a�Ϫ����Ƶ��c
typedef struct  tagMAP_OBJECT
{
	SLONG   flag;			// map object flags
	SLONG   id;				// map object file image id
    SLONG   px;             // map object position x
    SLONG   py;             // map object position y
    SLONG   pz;             // map object position z
    SLONG   effect;         // map object show effect
    SLONG   frame;          // map object now frame
    union
    {
        SLONG   now_tick;       //�ʺA���󪺥ثe�p�ɼ�
        SLONG   alpha;          //�ЫΫγ�����eALPHA��
    };
    union
    {
        SLONG   change_tick;    //�ʺA����G�ʺA���󪺴��V�p�ɼ�
        SLONG   update_alpha;   //�ЫΫγ��G�ЫΫγ���ALPHA�ܤƼлx
        SLONG   npc_no;         //NPC ����GNPC �����ޭȡA���VNPC �ƾڸ��
        SLONG   magic_part_no;  //�k�N����G�k�N�ե󪺯��ޭȡA���V�k�N�ե�ƾڸ��
    };
} MAP_OBJECT,*LPMAP_OBJECT;


typedef struct  tagMAP_OBJECT_EX
{
    SLONG   image_sx;
    SLONG   image_sy;
    SLONG   image_ex;
    SLONG   image_ey;
    POLY*   poly;
} MAP_OBJECT_EX, *LPMAP_OBJECT_EX;


//�a�ϲ��ʬ������c
typedef struct  tagMAP_MOVE
{
    SLONG   type;       //�a�Ϫ����ʤ覡
    //
    SLONG   dest_x;     //�ؼ��I X �y��
    SLONG   dest_y;     //�ؼ��I Y �y��
    SLONG   move_speed; //�a�Ϫ����ʳt��
    //
    SLONG   dest_npc;   //�ؼ� NPC �s��
    //
    SLONG   keep_range; //�O�_���W�L�a�Ϥj�p����
} MAP_MOVE, *LPMAP_MOVE;


// G L O B A L S ////////////////////////////////////////////////////////////////////////////////////////////////
extern  MAP_HEAD        map_head;
extern  MAP_DATA        map_data;
extern  MAP_OBJECT      map_object[MAX_MAP_OBJECT];
extern  MAP_OBJECT_EX   map_object_ex[MAX_MAP_OBJECT];
extern  SLONG           map_object_max;
extern  MAP_MOVE        map_move;


// F U N C T I O N    P R O T O T Y P E ////////////////////////////////////////////////////////////////////////
extern  int     init_map(void);
extern  void    free_map(void);
extern  void    active_map(int active);
extern  void    clear_map(void);
extern  SLONG   load_map(USTR *filename);
extern  void    redraw_map(BMP *bitmap);
extern  void    set_map_redraw_flags(SLONG flags);
extern  SLONG   get_usable_map_object(void);
//
extern  void    init_map_data(MAP_DATA *map_data);
extern  void    reset_map_start_position(void);
extern  void    init_map_move(void);
extern  void    set_map_move_to_position(SLONG dest_x, SLONG dest_y, SLONG move_speed);
extern  void    set_map_move_follow_npc(SLONG npc_no);
extern  void    set_map_move_auto(void);
extern  void    set_map_move_keep_range(SLONG flag);
extern  void    adjust_map_move(void);
extern  void    set_map_view_range(SLONG sx, SLONG sy, SLONG xl, SLONG yl);
//
extern	void    redraw_map_mask(SLONG map_sx, SLONG map_sy, MAP_MASK *mm, SLONG flags, void *vbitmap);
extern	void    redraw_map_proc_layer(SLONG map_sx,SLONG map_sy,SLONG flag,BMP *bmp);
//
extern	SLONG	is_redraw_map_object_poly(void);
extern	void	set_redraw_map_object_poly(SLONG flag);


#endif//MAP_H_INCLUDE
