/*
**      OBJECT.H
**      map object functions header.
**      ZJian,2000/10/09.
*/
#ifndef OBJECT_H_INCLUDE
#define OBJECT_H_INCLUDE        1
#include "NetGE_MainFunc.h"
//#include "xgrafx.h"
//#include "xcak.h"
//
// defines -----------------------------------------------------------------------------------------------------
// 
#define OBJECT_DIRECTORY            "object"
#define OBJECT_INI_FILENAME         "objinfo.ini"
#define OBJECT_NUMBER_FILENAME      "objnumbr.dat"
#define OBJECT_FRAMES_FILENAME      "objframe.dat"

//moved to comlib.
/*
#define MAKE_OBJECT_ID(type,index)      ( (((type) & 0xff)<<24) | ((index) & 0x00ffffff) )
#define MAKE_OBJECT_TYPE(id)            ( ((id) >> 24) & 0xff )
#define MAKE_OBJECT_INDEX(id)           ( (id) & 0x00ffffff )



// enums --------------------------------------------------------------------------------------------------------
//
//object types
typedef enum OBJECT_TYPE_VALUE_ENUMS
{   MAX_OBJECT_TYPES    =   33,

//normal object types for out map(unfixed) objects  
NORMAL_OBJECT_TYPES     =   32, 

// this object is used only in the memory for fixed map object in psd-map file.
OBJECT_TYPE_FIXED       =   (NORMAL_OBJECT_TYPES-1)+1,

//normal object types list
OBJECT_TYPE_ADDNEW      =   0,  //addnew,新增
OBJECT_TYPE_NPC         =   1,  //npc,人物
OBJECT_TYPE_ITEM        =   2,  //item,道具
OBJECT_TYPE_MAGIC       =   3,  //magic,法術
OBJECT_TYPE_SEANPC      =   17, //seanpc, 船隻等
//
START_INDEX_OF_USER_OBJECT_TYPE =   4,
//
INVALID_OBJECT_ID               =   0xffffffff,
MAX_OBJECT_IMAGES               =   4096
} OBJECT_TYPE_VALUE;



typedef enum    REDRAW_MAP_OBJECT_EFFECT_FLAG_ENUMS
{   OBJECT_IMAGE_MASK           =   0x000000ff,
//
OBJECT_NONE_IMAGE               =   0,
OBJECT_NORMAL_IMAGE             =   1,
OBJECT_MASK_IMAGE               =   3,
OBJECT_MASK_EDGE_IMAGE          =   4,
OBJECT_GRAY_IMAGE               =   5,
OBJECT_GRAY_EDGE_IMAGE          =   6,
OBJECT_ALFA_IMAGE               =   7,
OBJECT_ALFA_EDGE_IMAGE          =   8,
OBJECT_ADDITIVE_IMAGE           =   9,
OBJECT_ADDITIVE_EDGE_IMAGE      =   10,
OBJECT_SUBTRACTIVE_IMAGE        =   11,
OBJECT_SUBTRACTIVE_EDGE_IMAGE   =   12,
OBJECT_MINIMUM_IMAGE            =   13,
OBJECT_MINIMUM_EDGE_IMAGE       =   14,
OBJECT_MAXIMUM_IMAGE            =   15,
OBJECT_MAXIMUM_EDGE_IMAGE       =   16,
OBJECT_HALF_IMAGE               =   17,
OBJECT_HALF_EDGE_IMAGE          =   18,
OBJECT_MESH_IMAGE               =   19,
OBJECT_SCALE_IMAGE              =   20,
OBJECT_LIGHT_IMAGE              =   21,
OBJECT_RED_IMAGE                =   22,
OBJECT_GREEN_IMAGE              =   23,
OBJECT_BLUE_IMAGE               =   24,
OBJECT_YELLOW_IMAGE             =   25,
OBJECT_MERGE_IMAGE              =   26,
//
OBJECT_ALPHA_MASK               =   0x0000ff00,
OBJECT_POLY                     =   0x80000000,
OBJECT_SHADOW                   =   0x40000000,
OBJECT_BOX                      =   0x20000000,
} REDRAW_MAP_OBJECT_EFFECT_FLAG;
*/


typedef enum    OBJECT_GROUP_DATA_VALUES_ENUMS
{   MAX_GROUP_OBJECTS           =   8,
} OBJECT_GROUP_DATA_VALUES;




// struct typedefs -----------------------------------------------------------------------------------------------------
//
typedef struct  tagOBJECT_TYPE
{
    SLONG   flag;
    USTR    filename[32];
    USTR    infoname[32];
} OBJECT_TYPE,*LPOBJECT_TYPE;



typedef struct  tagOBJECT_NUMBER
{
    SLONG   objects[NORMAL_OBJECT_TYPES];
    SLONG   groups[NORMAL_OBJECT_TYPES];
} OBJECT_NUMBER,*LPOBJECT_NUMBER;



typedef struct  tagOBJECT_IMAGE
{
    SLONG           ref;
    CAKE_FRAME_ANI *cfa;	// use for cak object.
	SLONG			handle;	// use for media object.
} OBJECT_IMAGE,*LPOBJECT_IMAGE;



// global variables --------------------------------------------------------------------------------------------------
//
extern  OBJECT_TYPE     map_object_type[MAX_OBJECT_TYPES];
extern  OBJECT_NUMBER   map_object_number;
extern  OBJECT_IMAGE    map_object_image[MAX_OBJECT_TYPES][MAX_OBJECT_IMAGES];


// global functions ----------------------------------------------------------------------------------------------------
//
extern  SLONG   init_map_object_type(void);
extern  void    debug_list_map_object_type(void);
extern  void    set_map_object_type(SLONG index,SLONG flag,USTR *filename,USTR *infoname);
extern  USTR *  get_map_object_type_infoname(SLONG object_type);
extern  void    free_map_object_type(void);

extern  SLONG   init_map_object_system(void);
extern  void    free_map_object_system(void);

extern  SLONG   init_map_object_number(void);
extern  SLONG   pick_map_object_number(SLONG type);
extern  SLONG   load_map_object_number(void);
extern  void    free_map_object_number(void);

extern  SLONG   load_map_object_image(SLONG object_type,SLONG object_index,CAKE_FRAME_ANI **cfa);
extern  SLONG   register_map_object_image(SLONG object_type,SLONG object_index,CAKE_FRAME_ANI *cfa);

extern  SLONG   init_map_object_image(void);
extern  void    free_map_object_image(void);
extern  SLONG   load_specify_map_object_image(SLONG object_type,SLONG object_index);
extern  void    free_specify_map_object_image(SLONG object_type,SLONG object_index);
extern  SLONG   add_reference_for_map_object_image(SLONG id);
extern  SLONG   dec_reference_for_map_object_image(SLONG id);
extern  CAKE_FRAME_ANI *    get_map_object_image(SLONG id,SLONG frame);
extern  CAKE_FRAME_ANI *    get_map_object_image_head_ptr(SLONG id);
extern  POLY *  get_map_object_image_poly(SLONG id,SLONG frame);
//
// Jack, Add for media file support. [1/24/2003]
extern	SLONG	get_map_object_image_handle(SLONG id);
extern	void	set_map_object_image_handle(SLONG id, SLONG handle);
extern  SLONG   add_reference_for_map_media_object_image(SLONG id);
extern  SLONG   dec_reference_for_map_media_object_image(SLONG id);


//extern  SLONG   load_map_object_image_frames(void);
//extern  SLONG   get_map_object_image_total_frames(SLONG id);



#endif//OBJECT_H_INCLUDE

