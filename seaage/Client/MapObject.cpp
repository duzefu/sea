/*
**      OBJECT.CPP
**      map object functions.
**
**      ZJian,2000.10.09.
*/
#include "MainFun.h"
#include "NetGE_MainFunc.h"
#include "MapObject.h"
#include "Media.h"


//#include "ClientMain.h"
extern	DATA_FILE	*packed_object_file;
extern	DATA_FILE	*packed_npc_file;
extern	DATA_FILE	*packed_seanpc_file;


OBJECT_TYPE     map_object_type[MAX_OBJECT_TYPES];
OBJECT_NUMBER   map_object_number;
OBJECT_IMAGE    map_object_image[MAX_OBJECT_TYPES][MAX_OBJECT_IMAGES];


SLONG   init_map_object_system(void)
{
    init_map_object_type();

#ifdef  DEBUG
    debug_list_map_object_type();
#endif//DEBUG

    init_map_object_number();
    load_map_object_number();
    
    init_map_object_image();

    //PS: here is for game main..., we need to know the frames of each id
    //load_map_object_image_frames();
    set_data_file(packed_object_file);
	LoadObjectImageInfo("object\\objframe.dat");

    return TTN_OK;
}


void    free_map_object_system(void)
{
    free_map_object_image();
    free_map_object_number();
    free_map_object_type();
}


SLONG   init_map_object_type(void)
{
    SLONG i,index;
    USTR    key[128];
    USTR    value[512];
    USTR    filename[64];
    USTR    infoname[64];
    SLONG   out_max;
    USTR    full_filename[_MAX_FNAME];
    
    // system default map object types
    set_map_object_type( OBJECT_TYPE_ADDNEW ,1  ,(USTR *)"addnew"   ,(USTR *)"新增");
    set_map_object_type( OBJECT_TYPE_NPC    ,1  ,(USTR *)"npc"      ,(USTR *)"人物");
    set_map_object_type( OBJECT_TYPE_ITEM   ,1  ,(USTR *)"item"     ,(USTR *)"道具");
    set_map_object_type( OBJECT_TYPE_MAGIC  ,1  ,(USTR *)"magic"    ,(USTR *)"法術");

    set_data_file(packed_object_file);
    sprintf((char *)full_filename,"%s\\%s",OBJECT_DIRECTORY,OBJECT_INI_FILENAME);
    load_ini_information((USTR *)full_filename);
    //list_ini_information();
    for(i=START_INDEX_OF_USER_OBJECT_TYPE;i<NORMAL_OBJECT_TYPES;++i)
    {
        map_object_type[i].flag = 0;
        sprintf((char *)key,"OBJLIB%02d",i+1);
        get_ini_information((USTR *)"OBJLIBS",(USTR *)key,(USTR *)&value);
        if('\0' != value[0])
        {
            map_object_type[i].flag = 1;
            
            index=0;
            out_max=31;
            skip_compartment(value,&index,(USTR *)" =",1);
            get_string((USTR *)filename,out_max,value,&index,(USTR *)",\x00",2);
            
            skip_compartment(value,&index,(USTR *)", \x09",3);
            get_string((USTR *)infoname,out_max,value,&index,(USTR *)",\x00",2);
            
            if(filename[0] && infoname[0])
            {
                set_map_object_type(i,1,(USTR *)filename,(USTR *)infoname);
            }
        }
    }
    free_ini_information();
    return TTN_OK;
}

void    debug_list_map_object_type(void)
{
    SLONG i;
    for(i=0;i<MAX_OBJECT_TYPES;++i)
    {
        sprintf((char *)print_rec,"[%d] [%d] [%s] [%s]",i,map_object_type[i].flag,
            map_object_type[i].filename,map_object_type[i].infoname);
        log_error(1,print_rec);
        log_error(1,(USTR *)"---------------------------------------------------");
    }
}

void    set_map_object_type(SLONG index,SLONG flag,USTR *filename,USTR *infoname)
{
    if(index>=0 && index<NORMAL_OBJECT_TYPES)
    {
        map_object_type[index].flag=flag;
        strcpy((char *)map_object_type[index].filename,(const char *)filename);
        strcpy((char *)map_object_type[index].infoname,(const char *)infoname);
    }
}



USTR *  get_map_object_type_infoname(SLONG object_type)
{
    if(object_type >=0 && object_type < NORMAL_OBJECT_TYPES)
        return (USTR *)map_object_type[object_type].infoname;
    else
        return NULL;
}

void    free_map_object_type(void)
{
}

SLONG   init_map_object_number(void)
{
    SLONG i;
    for(i=0;i<NORMAL_OBJECT_TYPES;++i)
    {
        map_object_number.objects[i]=0;
        map_object_number.groups[i]=0;
    }
    return TTN_OK;
}


SLONG   pick_map_object_number(SLONG type)
{
    if(type>=0 && type<NORMAL_OBJECT_TYPES)
        return map_object_number.objects[type];
    else
        return 0;
}


SLONG   load_map_object_number(void)
{
    PACK_FILE *  fp=NULL;
    USTR    full_filename[_MAX_FNAME];

    set_data_file(packed_object_file);
    sprintf((char *)full_filename,"%s\\%s",OBJECT_DIRECTORY,OBJECT_NUMBER_FILENAME);
    if(NULL==(fp=pack_fopen((const char *)full_filename,"rb")))
    {
        sprintf((char *)print_rec,"open file %s for read error",full_filename);
        log_error(1,print_rec);
        return TTN_ERROR;
    }
    pack_fread(&map_object_number,1,sizeof(OBJECT_NUMBER),fp);
    if(fp) pack_fclose(fp);
    return TTN_OK;
}

void    free_map_object_number(void)
{
}

SLONG   load_map_object_image(SLONG object_type,SLONG object_index,CAKE_FRAME_ANI **cfa)
{
    USTR    filename[_MAX_FNAME];

    if(object_type>=0 && object_type<NORMAL_OBJECT_TYPES)
    {
        set_data_file(packed_object_file);
        sprintf((char *)filename,"%s\\%s\\%02dt%05d.cak",OBJECT_DIRECTORY,
            map_object_type[object_type].filename,object_type,object_index);
        load_cake_frame_ani_from_file((USTR *)filename, cfa);
        return TTN_OK;
    }
    return TTN_NOT_OK;
}


SLONG   register_map_object_image(SLONG object_type,SLONG object_index,CAKE_FRAME_ANI *cfa)
{
    SLONG   id = INVALID_OBJECT_ID;
	SLONG	frames;

    if(object_type >=0 && object_type<MAX_OBJECT_TYPES)
    {
        id = MAKE_OBJECT_ID(object_type,object_index);
        map_object_image[object_type][object_index].cfa = cfa;
		frames = count_cake_frames(cfa);

		// Jack, Modify for SeaAge's ComLIB reference. [1/8/2003]
        //map_object_image[object_type][object_index].frames = frames;
		SetObjectImageTotalFrames(id, frames);
        map_object_image[object_type][object_index].ref ++;
    }
    return id;
}


SLONG   init_map_object_image(void)
{
    SLONG i,j;
    for(j=0;j<MAX_OBJECT_TYPES;++j)
    {
        for(i=0;i<MAX_OBJECT_IMAGES;++i)
        {
            map_object_image[j][i].ref = 0;
            map_object_image[j][i].cfa = NULL;
			map_object_image[j][i].handle = -1;
        }
    }
    return TTN_OK;
}

void    free_map_object_image(void)
{
    SLONG i,j;
    for(j=0;j<MAX_OBJECT_TYPES;++j)
    {
        for(i=0;i<MAX_OBJECT_IMAGES;++i)
        {
            destroy_cake_frame_ani(&map_object_image[j][i].cfa);
            map_object_image[j][i].cfa = NULL;
            map_object_image[j][i].ref = 0;
			map_object_image[j][i].handle = -1;
        }
    }
}


SLONG   load_specify_map_object_image(SLONG type,SLONG index)
{
    return load_map_object_image(type,index,&map_object_image[type][index].cfa);
}

void    free_specify_map_object_image(SLONG type,SLONG index)
{
    destroy_cake_frame_ani(&map_object_image[type][index].cfa);
}


SLONG   add_reference_for_map_object_image(SLONG id)
{
    SLONG type,index,total;
    
    type = MAKE_OBJECT_TYPE(id);
    index = MAKE_OBJECT_INDEX(id);
    total = pick_map_object_number(type);
    if(index>=0 && index<total)
    {
        if(map_object_image[type][index].ref == 0)
        {
            load_specify_map_object_image(type, index);
        }
        map_object_image[type][index].ref++;
    }
    return TTN_OK;
}

SLONG   dec_reference_for_map_object_image(SLONG id)
{
    SLONG type,index;
    
    type = MAKE_OBJECT_TYPE(id);
    index = MAKE_OBJECT_INDEX(id);
	if(map_object_image[type][index].ref > 0)
		map_object_image[type][index].ref--;
	if(map_object_image[type][index].ref == 0)
	{
		free_specify_map_object_image(type, index);
		//geaan, 2001.8.10.
		// map_object_image[type][index].frames = 1; // why not 0?
	}
    return TTN_OK;
}


CAKE_FRAME_ANI *    get_map_object_image(SLONG id,SLONG frame)
{
    SLONG type,index;
    CAKE_FRAME_ANI *p;
    
    type = MAKE_OBJECT_TYPE(id);
    index = MAKE_OBJECT_INDEX(id);
	frame++;
	p = map_object_image[type][index].cfa;
	while(p && frame)
	{
		p=p->next;
		frame--;
	}
	return p;
}


CAKE_FRAME_ANI *    get_map_object_image_head_ptr(SLONG id)
{
    SLONG type,index;
    
    type = MAKE_OBJECT_TYPE(id);
    index = MAKE_OBJECT_INDEX(id);
	return	map_object_image[type][index].cfa;
}


POLY *  get_map_object_image_poly(SLONG id,SLONG frame)
{
    SLONG type,index;
    CAKE_FRAME_ANI *p;
    CAKE_FRAME *cf;
    
    type = MAKE_OBJECT_TYPE(id);
    index = MAKE_OBJECT_INDEX(id);

	frame++;
	p = map_object_image[type][index].cfa;
	while(p && frame)
	{
		p=p->next;
		frame--;
	}
	if(!p) return NULL;
	if(NULL==(cf=p->cake_frame)) return NULL;
	return cf->poly;
}

/*
SLONG   load_map_object_image_frames(void)
{
    USTR    full_filename[_MAX_FNAME];
    PACK_FILE    *fp=NULL;
    SLONG   i,j;
    SLONG   frames;

    set_data_file(packed_object_file);
    sprintf((char *)full_filename,"%s\\%s",OBJECT_DIRECTORY,OBJECT_FRAMES_FILENAME);
    if(NULL == (fp = pack_fopen((const char *)full_filename,"rb")) )
    {
        sprintf((char *)print_rec,"file %s open error", full_filename);
        log_error(1, print_rec);
        return TTN_ERROR;
    }
    for(i=0; i<MAX_OBJECT_TYPES; i++)
    {
        for(j=0; j<MAX_OBJECT_IMAGES; j++)
        {
            pack_fread(&frames, 1, sizeof(SLONG), fp);
            map_object_image[i][j].frames = frames ;
        }
    }
    if(fp) pack_fclose(fp);
    return TTN_OK;
}


SLONG   get_map_object_image_total_frames(SLONG id)
{
    SLONG type,index,total;
    
    type = MAKE_OBJECT_TYPE(id);
    index = MAKE_OBJECT_INDEX(id);
    total = pick_map_object_number(type);
    if(index>=0 && index<total)
        return map_object_image[type][index].frames;
    return 1;
}
*/

/************************************************************************************************************/
/* FUNCTIONS FOR MEDIA OBJECT SUPPORT                                                                       */
/************************************************************************************************************/
SLONG	get_map_object_image_handle(SLONG id)
{
    SLONG type,index;

    type = MAKE_OBJECT_TYPE(id);
    index = MAKE_OBJECT_INDEX(id);

	return	map_object_image[type][index].handle;
}

void	set_map_object_image_handle(SLONG id, SLONG handle)
{
    SLONG type,index;

    type = MAKE_OBJECT_TYPE(id);
    index = MAKE_OBJECT_INDEX(id);
	map_object_image[type][index].handle = handle;
}

SLONG   add_reference_for_map_media_object_image(SLONG id)
{
	USTR	filename[_MAX_FNAME];
	SLONG	type, index;
	SLONG	handle, result;
	
	type = MAKE_OBJECT_TYPE(id);
	index = MAKE_OBJECT_INDEX(id);
	switch(type)
	{
	case OBJECT_TYPE_NPC:
		set_data_file(packed_npc_file);
		sprintf((char *)filename, "npc\\npc\\%04d.mda", index);
		result = mda_group_open_with_position((UCHR*)filename, &handle);
		if(TTN_OK == result)
		{
			set_map_object_image_handle(id, handle);
		}
		break;
	case OBJECT_TYPE_SEANPC:
		set_data_file(packed_seanpc_file);
		sprintf((char *)filename, "npc\\seanpc\\%04d.mda", index);
		result = mda_group_open_with_position((UCHR*)filename, &handle);
		if(TTN_OK == result)
		{
			set_map_object_image_handle(id, handle);
		}
		break;
	}
	return	TTN_OK;
}


SLONG   dec_reference_for_map_media_object_image(SLONG id)
{
	SLONG	handle;
	
	handle = get_map_object_image_handle(id);
	if(handle >= 0)
	{
		mda_group_close(&handle);
		set_map_object_image_handle(id, handle);
	}
	return	TTN_OK;
}
