/*
**  TileSet.cpp
**  Tile set functions.
**
**  Jack, 2002.3.6.
*/
#include "mainfun.h"
#include "TileSet.h"

//#include "ClientMain.h"
extern	DATA_FILE	*packed_tile_file;


typedef struct  tagTERRA_SHAPE_HEAD
{
    ULONG   copyright;      //copyright 'RAYS'
    ULONG   id;             //file id 'TRSP'
    ULONG   version;        //TERRA_SHAPE_FILE_VERSION
    ULONG   head_size;      //size of the file head
    //
    SLONG   total_shapes;   //total shapes
    SLONG   reserved[7];    //reserved datas
} TERRA_SHAPE_HEAD, *LPTERRA_SHAPE_HEAD;



// GLOBALS ////////////////////////////////////////////////////////////////////////
//TERRA_BASE  terra_base[MAX_TERRA_SOLIDS];
//
TERRA_SHAPE terra_shape[MAX_TERRA_SHAPES];
//
//TERRA_SET   terra_set[MAX_TERRA_SETS];
//TERRA_MIXED terra_mixed[MAX_TERRA_MIXEDS];
//TERRA_SOLID terra_solid[MAX_TERRA_SOLIDS];
//


/******************************************************************************************************************/
/* FUNCTIONS                                                                                                      */
/******************************************************************************************************************/
/*
int init_terra_base(void)
{
    enum {LINE_BUFFER_SIZE = 1024};
    USTR    *file_buf;
    SLONG   file_size, pass, result, buffer_index;
    USTR    line[LINE_BUFFER_SIZE];
    SLONG   index;
    SLONG   len;
    SLONG   base_index;
    SLONG   i;
    TERRA_BASE  *data;

    //(1) clear all terra bases.----------------------
    for(i=0; i<MAX_TERRA_SOLIDS; i++)
    {
        terra_base[i].flag = 0;
        terra_base[i].mask = 0x00000000;
        sprintf((char *)terra_base[i].name, "BASE%02d", i);
        //
        terra_solid[i].flag = 0;
    }

    //(2) load terra base.----------------------------
    set_data_file(packed_tile_file);
    file_size = load_file_to_buffer((USTR*)"tile\\tilebase.ini", &file_buf);
    if(file_size < 0)
        goto _error;

    pass = 0;
    buffer_index = 0;
    result = get_buffer_line((char*)file_buf, &buffer_index, file_size, (char*)line, LINE_BUFFER_SIZE);
    while((result == TTN_OK) && (pass == 0))
    {
        len = ( SLONG )strlen( ( const char* )line );
        if( ( line[0] != 0x00 ) && ( line[0] != ';' ) )
        {
            index = 0;
            base_index = get_buffer_number(line, &index);
            if(base_index >= 0 && base_index < MAX_TERRA_SOLIDS)
            {
                data = &terra_base[base_index];
                data->flag = 1;
                strcpy((char *)data->name, (const char *)get_buffer_string(line, &index));
                //
                terra_solid[base_index].flag = 1;
                terra_solid[base_index].type = base_index;
            }
        }
        result = get_buffer_line((char*)file_buf, &buffer_index, file_size, (char*)line, LINE_BUFFER_SIZE);
    }
    if(file_buf) free(file_buf);
    return  0;

_error:
    if(file_buf) free(file_buf);
    return  -1;
}


int init_terra_shape(void)
{
    enum {LINE_BUFFER_SIZE = 1024};
    USTR    *file_buf;
    SLONG   file_size, pass, result, buffer_index;
    USTR    line[LINE_BUFFER_SIZE];
    SLONG   index;
    SLONG   len;
    SLONG   i, start, mixed, shape_index;
    SLONG   under_type, cover_type;

    //solid terra type : 0 ~ MAX_TERRA_SOLIDS-1. -----------------------------------
    for(i=0; i<MAX_TERRA_SOLIDS; i++)
    {
        terra_shape[i].under_type = i;
        terra_shape[i].cover_type = i;
        terra_shape[i].shape_code = 0xff;
        terra_shape[i].max_tiles = 0;
        terra_shape[i].max_specials = 0;
    }

    //init terra_mixed -------------------------------------------------------------
    for(i=0; i<MAX_TERRA_MIXEDS; i++)
    {
        terra_mixed[i].flag = 0;
        terra_mixed[i].under_type = -1;
        terra_mixed[i].cover_type = -1;
    }

    //mixed terra type : MAX_TERRA_SOLIDS ~ ... ------------------------------------
    start = MAX_TERRA_SOLIDS;

    set_data_file(packed_tile_file);
    file_size = load_file_to_buffer((USTR*)"tile\\tilelink.ini", &file_buf);
    if(file_size < 0)
        goto _error;

    pass = 0;
    buffer_index = 0;
    result = get_buffer_line((char*)file_buf, &buffer_index, file_size, (char*)line, LINE_BUFFER_SIZE);
    while((result == TTN_OK) && (pass == 0))
    {
        len = ( SLONG )strlen( ( const char* )line );
        if( ( line[0] != 0x00 ) && ( line[0] != ';' ) )
        {
            index = 0;
            mixed = get_buffer_number(line, &index);
            if(mixed >= 0 && mixed < MAX_TERRA_MIXEDS)
            {
                under_type = get_buffer_number(line, &index);
                cover_type = get_buffer_number(line, &index);
                for(i=0; i<TILE_SHAPES; i++)
                {
                    shape_index = start + i;
                    terra_shape[shape_index].under_type = under_type;
                    terra_shape[shape_index].cover_type = cover_type;
                    terra_shape[shape_index].shape_code = i;
                    terra_shape[shape_index].max_tiles = 0;
                    terra_shape[shape_index].max_specials = 0;
                }
                start += TILE_SHAPES;

                //
                terra_mixed[mixed].flag = 1;
                terra_mixed[mixed].under_type = under_type;
                terra_mixed[mixed].cover_type = cover_type;
            }
        }
        result = get_buffer_line((char*)file_buf, &buffer_index, file_size, (char*)line, LINE_BUFFER_SIZE);
    }
    if(file_buf) free(file_buf);

    //reserved terra types : ...
    for(i = start; i<MAX_TERRA_SHAPES; i++)
    {
        terra_shape[i].under_type = -1;
        terra_shape[i].cover_type = -1;
        terra_shape[i].shape_code = 0xff;
        terra_shape[i].max_tiles = 0;
        terra_shape[i].max_specials = 0;
    }

    return  0;

_error:
    if(file_buf) free(file_buf);
    return  -1;
}


int init_terra_set(void)
{
    enum {LINE_BUFFER_SIZE = 1024};
    USTR    *file_buf;
    SLONG   file_size, pass, result, buffer_index;
    USTR    line[LINE_BUFFER_SIZE];
    SLONG   index;
    SLONG   len;
    SLONG   i, j, k, mixed, find, under_type, cover_type;
    SLONG   max_mixed, max_solid;
    SLONG   solid[64] = {-1};
    SLONG   link_index[12];
    SLONG   set_index;

    //clear terra sets. ----------------------------------------------------------
    for(i=0; i<MAX_TERRA_SETS; i++)
    {
        terra_set[i].flag = 0;
        terra_set[i].max_mixeds = 0;
        terra_set[i].max_solids = 0;
        sprintf((char *)terra_set[i].name, "SET%02d", i);
    }

    //load terra sets. -----------------------------------------------------------
    set_data_file(packed_tile_file);
    file_size = load_file_to_buffer((USTR*)"tile\\tileset.ini", &file_buf);
    if(file_size < 0)
        goto _error;

    pass = 0;
    buffer_index = 0;
    result = get_buffer_line((char*)file_buf, &buffer_index, file_size, (char*)line, LINE_BUFFER_SIZE);
    while((result == TTN_OK) && (pass == 0))
    {
        len = ( SLONG )strlen( ( const char* )line );
        if( ( line[0] != 0x00 ) && ( line[0] != ';' ) )
        {
            index = 0;
            set_index = get_buffer_number(line, &index);
            if(set_index >= 0 && set_index < MAX_TERRA_SETS)
            {
                terra_set[set_index].flag = 1;
                terra_set[set_index].max_mixeds = 0;
                terra_set[set_index].max_solids = 0;
                strcpy((char *)terra_set[set_index].name, (const char *)get_buffer_string(line, &index) );
                for(i=0; i<12; i++)
                {
                    link_index[i] = get_buffer_number(line, &index);
                }
                
                max_mixed = 0;
                max_solid = 0;
                for(j=0; link_index[j] >= 0; j++)
                {
                    mixed = link_index[j];
                    under_type = terra_mixed[mixed].under_type;
                    cover_type = terra_mixed[mixed].cover_type;
                    terra_set[set_index].mixed_terra[j] = mixed;
                    max_mixed ++;
                    
                    find = -1;
                    for(k=0; k<max_solid; k++)
                    {
                        if(solid[k] == under_type)
                        {
                            find = k;
                            k = max_solid + 100;
                        }
                    }
                    if(find < 0)
                    {
                        solid[max_solid] = under_type;
                        max_solid ++;
                    }
                    
                    find = -1;
                    for(k=0; k<max_solid; k++)
                    {
                        if(solid[k] == cover_type)
                        {
                            find = k;
                            k = max_solid + 100;
                        }
                    }
                    if(find < 0)
                    {
                        solid[max_solid] = cover_type;
                        max_solid ++;
                    }
                }
                for(k=0; k<max_solid; k++)
                {
                    terra_set[set_index].solid_terra[k] = solid[k];
                }
                terra_set[set_index].max_mixeds = max_mixed;
                terra_set[set_index].max_solids = max_solid;
            }
        }
        result = get_buffer_line((char*)file_buf, &buffer_index, file_size, (char*)line, LINE_BUFFER_SIZE);
    }
    if(file_buf) free(file_buf);

    return  0;
_error:
    if(file_buf) free(file_buf);
    return  -1;
}

SLONG   find_terra_shape_index(SLONG under_type, SLONG cover_type, SLONG shape_code)
{
    SLONG   i, find;

    find = -1;
    for(i=0; i<MAX_TERRA_SHAPES; i++)
    {
        if( (terra_shape[i].under_type == under_type) && (terra_shape[i].cover_type == cover_type) 
            && (terra_shape[i].shape_code == shape_code) )
        {
            find = i;
            break;
        }
    }
    return  find;
}
*/


SLONG   get_solid_terra_shape_index(SLONG solid_index)
{
    return  solid_index;
}


SLONG   tile_id_to_shape_index(SLONG tile_id)
{
    SLONG   shape_index;
    SLONG   mixed_index, shape_code;

    if(tile_id & TILE_MASK_MIXED_TERRA)
    {/* mixed-terra tile    */
        mixed_index = ((tile_id & TILE_MASK_MIXED_TERRA) >> 20) - 1;
        shape_code = (tile_id & TILE_MASK_TILE_SHAPE) >> 16;
        shape_index = MAX_TERRA_SOLIDS + mixed_index * TILE_SHAPES + shape_code;
    }
    else
    {/* solid-terra tile    */
        shape_index = (tile_id & TILE_MASK_SOLID_TERRA) >> 8;
    }
    return  shape_index;
}


SLONG   shape_index_to_normal_tile_id(SLONG shape_index)
{
    SLONG   max_tiles, tile_index, tile_id;
    SLONG   mixed_index, shape_code;
    SLONG   max_specials, max_normals;

    max_tiles = terra_shape[shape_index].max_tiles;
    max_specials = terra_shape[shape_index].max_specials;
    max_normals = max_tiles - max_specials;
    if(max_normals < 1)
        tile_index = 0;
    else
        tile_index = rand() % max_normals;
    if(shape_index < MAX_TERRA_SOLIDS)
    {/* solid terra shapes */
        tile_id = ((shape_index << 8) & TILE_MASK_SOLID_TERRA) | 
            (tile_index & TILE_MASK_TILE_INDEX);
    }
    else
    {/* mixed terra shapes */
        mixed_index = (shape_index - MAX_TERRA_SOLIDS) / TILE_SHAPES;
        shape_code = (shape_index - MAX_TERRA_SOLIDS) % TILE_SHAPES;
        tile_id = (((mixed_index+1) << 20) & TILE_MASK_MIXED_TERRA) |
            ((shape_code << 16) & TILE_MASK_TILE_SHAPE) |
            (tile_index & TILE_MASK_TILE_INDEX);
    }
    return  tile_id;
}


SLONG   get_tile_terra_image_no(SLONG tile_id, SLONG frame)
{
    SLONG   tile_index, shape_index;
    SLONG   image_no;

    tile_index = tile_id & TILE_MASK_TILE_INDEX;
    if(tile_id & TILE_MASK_MIXED_TERRA)
    {/* mixed-terra tile    */
        shape_index = tile_id_to_shape_index(tile_id);
    }
    else
    {/* solid-terra tile    */
        shape_index = (tile_id & TILE_MASK_SOLID_TERRA) >> 8;
    }
    image_no = terra_shape[shape_index].image_no[tile_index][frame];

    return  image_no;
}


SLONG   load_terra_shape_data_from_file(USTR *filename)
{
    TERRA_SHAPE_HEAD head;
    PACK_FILE *fp = NULL;
    SLONG read_size;

    if(NULL == (fp = pack_fopen((const char *)filename, "rb")))
    {
        log_error(1, "file %s open error", filename);
        goto some_error;
    }
    read_size = pack_fread(&head, 1, sizeof(TERRA_SHAPE_HEAD), fp);
    if(sizeof(TERRA_SHAPE_HEAD) != read_size )
    {
        log_error(1, "read terra shape file head error");
        goto some_error;
    }
    if(MAKEFOURCC('R','A','Y','S') != head.copyright)
    {
        log_error(1, "terra shape file copyright error");
        goto some_error;
    }
    if(MAKEFOURCC('T','R','S','P') != head.id)
    {
        log_error(1, "terra shape file format error");
        goto some_error;
    }
    if(TERRA_SHAPE_FILE_VERSION != head.version)
    {
        log_error(1, "terra shape file version error");
        goto some_error;
    }
    if(MAX_TERRA_SHAPES != head.total_shapes)
    {
        log_error(1, "terra shapes in file mismatch");
        goto some_error;
    }
    pack_fread(&terra_shape[0], 1, sizeof(TERRA_SHAPE) * MAX_TERRA_SHAPES, fp);
    if(fp) pack_fclose(fp);

    log_error(1, "Load terra shapes( %d shapes ) ok.", MAX_TERRA_SHAPES);

    return  TTN_OK;

some_error:
    if(fp) pack_fclose(fp);
    return  TTN_NOT_OK;
}


