/*
**	NetGE_Image.h 
**	image functions header.
**
**	Jack, 2003.1.26.
*/
#pragma once



//
// DEFINES ////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
#define MAKE_OBJECT_ID(type,index)      ( (((type) & 0xff)<<24) | ((index) & 0x00ffffff) )
#define MAKE_OBJECT_TYPE(id)            ( ((id) >> 24) & 0xff )
#define MAKE_OBJECT_INDEX(id)           ( (id) & 0x00ffffff )


typedef enum OBJECT_TYPE_VALUE_ENUMS
{   MAX_OBJECT_TYPES    =   33,		//total object types
NORMAL_OBJECT_TYPES     =   32,		//normal object types for out map(unfixed) objects  
MAX_OBJECT_IMAGES       =   4096,	//total object images of each type
//
OBJECT_TYPE_FIXED       =   32,		// this object is used only in the memory for fixed map object in psd-map file.
//
//normal object types list
OBJECT_TYPE_ADDNEW      =   0,		// addnew,新增
OBJECT_TYPE_NPC         =   1,		// npc,人物
OBJECT_TYPE_ITEM        =   2,		// item,道具
OBJECT_TYPE_MAGIC       =   3,		// magic,法術
OBJECT_TYPE_SEANPC      =   17,		// seanpc, 船隻等
//
START_INDEX_OF_USER_OBJECT_TYPE =   4,
//
INVALID_OBJECT_ID       =   0xffffffff,
} OBJECT_TYPE_VALUE_ENUMS;



typedef enum    REDRAW_MAP_OBJECT_EFFECT_FLAG_ENUMS
{   OBJECT_IMAGE_MASK           =   0x000000ff,
OBJECT_ALPHA_MASK               =   0x0000ff00,
OBJECT_POLY                     =   0x80000000,
OBJECT_SHADOW                   =   0x40000000,
OBJECT_BOX                      =   0x20000000,
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
OBJECT_MERGE_IMAGE              =   26
//
} REDRAW_MAP_OBJECT_EFFECT_FLAG_ENUMS;



