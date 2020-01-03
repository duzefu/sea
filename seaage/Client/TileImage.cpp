/*
**  TileImage.CPP
**  Tile image functions.
**
**  Jack, 2002.3.6.
*/
#include "mainfun.h"
#include "TileImage.h"


//////////////////////////////////////////////////////////////////////////////////////////
// GLOBALS                                                                              //
//////////////////////////////////////////////////////////////////////////////////////////
TILE_IMAGE_DATA  tile_image_data[MAX_TILE_IMAGES];
SLONG   total_tile_image_datas;
//
BMP*    module_tile_bitmap = NULL;

//////////////////////////////////////////////////////////////////////////////////////////
// S T A T I C   F U N C T I O N S                                                      //
//////////////////////////////////////////////////////////////////////////////////////////
void    generate_tile_vmask(void)
{
    SLONG   x, y;

    // Generate left-up corner rectangle area.
    for(y=0; y<TILE_HEIGHT/2; y++)
    {
        for(x=0; x<TILE_WIDTH/2; x++)
        {
            //We suppose the key line: y = K * x + C.
            //And the line will cross (0, TILE_HEIGHT/2) and (TILE_WIDTH/2,0).
            //So we can get the declair of the line is:
            // (TILE_HEIGHT/2) * x + (TILE_WIDTH/2) * y = (TILE_WIDTH/2)*(TILE_HEIGHT/2).
            if( x * TILE_HEIGHT/2 + y * TILE_WIDTH/2 >= TILE_HEIGHT/2 * TILE_WIDTH/2)
            {
                tile_vmask[y][x] = 1;
            }
            else
            {
                tile_vmask[y][x] = 0;
            }
        }
    }
    // Mirror left-down corner.
    for(y=TILE_HEIGHT/2; y<TILE_HEIGHT; y++)
    {
        for(x=0; x<TILE_WIDTH/2; x++)
        {
            tile_vmask[y][x] = tile_vmask[TILE_HEIGHT- 1 - y][x];
        }
    }
    // Match right-down corner with left-up corner.
    for(y=TILE_HEIGHT/2; y<TILE_HEIGHT; y++)
    {
        for(x=TILE_WIDTH/2; x<TILE_WIDTH; x++)
        {
            tile_vmask[y][x] = 1 - tile_vmask[y-TILE_HEIGHT/2][x-TILE_WIDTH/2];
        }
    }
    //Match left-up corner with left-down corner.
    for(y=0; y<TILE_HEIGHT/2; y++)
    {
        for(x=TILE_WIDTH/2; x<TILE_WIDTH; x++)
        {
            tile_vmask[y][x] = 1 - tile_vmask[y+TILE_HEIGHT/2][x-TILE_WIDTH/2];
        }
    }
}


void    output_tile_vmask(void)
{
    for(SLONG y=0;y<TILE_HEIGHT;y++)
    {
        strcpy((char *)print_rec,"   {");
        for(SLONG x=0;x<TILE_WIDTH;x++)
        {
            if(x==TILE_WIDTH-1)
            {
                if(tile_vmask[y][x])
                    strcat((char *)print_rec,(const char *)"1},");
                else
                    strcat((char *)print_rec,(const char *)"0},");
            }
            else
            {
                if(tile_vmask[y][x])
                    strcat((char *)print_rec,(const char *)"1,");
                else
                    strcat((char *)print_rec,(const char *)"0,");
            }
        }
        log_error(1,print_rec);
    }
}


void    generate_tile_vput(void)
{
    int x,y,flag,index;
    
    index=0;
    for(y=0;y<TILE_HEIGHT;y++)
    {
        flag=0;
        for(x=0;x<TILE_WIDTH;x++)
        {
            if(flag==0)
            {
                if(tile_vmask[y][x] == 1 )
                {
                    tile_vput[y].index = index;
                    tile_vput[y].offset = x;
                    flag=1;
                }
            }
            else if(flag==1)
            {
                if(tile_vmask[y][x]==0)
                {
                    tile_vput[y].width = x-tile_vput[y].offset;
                    index+=tile_vput[y].width;
                    flag=2;
                }
                else if(x == TILE_WIDTH-1)
                {
                    tile_vput[y].width = x - tile_vput[y].offset + 1; //add 1 for edge
                    index += tile_vput[y].width;
                    flag=2;
                }
            }
        }
    }
    for(y=0;y<TILE_HEIGHT;y++)
    {
        tile_vput[y].width *= SIZEOFPIXEL;
    }
}


void    output_tile_vput(void)
{
    int y;
    for(y=0;y<TILE_HEIGHT;y++)
    {
        sprintf((char *)print_rec,"memcpy(&bitmap->line[sy+%d][sx+%d],&tile_buffer[%d],%d);",
            y,tile_vput[y].offset,tile_vput[y].index,tile_vput[y].width);
        log_error(1,print_rec);
    }
}


void    generate_tile_rput(void)
{
    int index=0;
    for(int y=0;y<TILE_HEIGHT;y++)
    {
        for(int x=0;x<TILE_WIDTH;x++)
        {
            if(tile_vmask[y][x]==1)
            {
                tile_rput[index].rx=x;
                tile_rput[index].ry=y;
                index++;
            }
        }
    }
}


void    output_tile_rput(void)
{
    sprintf((char *)print_rec,"%s","tile_rput ============");
    log_error(1,print_rec);
    for(int i=0;i<TILE_DATA_SIZE;i++)
    {
        sprintf((char *)print_rec,"%d,%d",tile_rput[i].rx,tile_rput[i].ry);
        log_error(1,print_rec);
    }
}


//////////////////////////////////////////////////////////////////////////////////////////////
// TILE IMAGE GRAPHICS FUNCTIONS                                                            //
//////////////////////////////////////////////////////////////////////////////////////////////
void    init_tile_image_module(void)
{
    generate_tile_vmask();
    generate_tile_vput();
    generate_tile_rput();
    //output_tile_vmask();
    //output_tile_vput();
    //output_tile_rput();
    //
    module_tile_bitmap = create_bitmap(TILE_WIDTH, TILE_HEIGHT);
    clear_bitmap(module_tile_bitmap);
    //
    init_tile_image_data();
    return;
}


void    free_tile_image_module(void)
{
    destroy_bitmap(&module_tile_bitmap);
}


void    put_tile_image(SLONG sx,SLONG sy,PIXEL *tile_buffer,BMP *bitmap)
{
    SLONG   y;

    if(!tile_buffer)
        return;

    for(y=TILE_HEIGHT-1;y>=0;y--)
    {
        memcpy(&bitmap->line[sy+y][sx+tile_vput[y].offset],&tile_buffer[tile_vput[y].index],tile_vput[y].width);
    }
    return;
}


void    range_put_tile_image(SLONG sx,SLONG sy,PIXEL *tile_buffer,BMP *bitmap)
{
    SLONG x, y, i;

    if(!tile_buffer)
        return;

    for(i=TILE_DATA_SIZE-1;i>=0;i--)
    {
        x=sx+tile_rput[i].rx;
        if(x<0 || x>=bitmap->w)
            continue;
        y=sy+tile_rput[i].ry;
        if(y<0 || y>=bitmap->h)
            continue;
        bitmap->line[y][x]=tile_buffer[i];
    }
    return;
}


//////////////////////////////////////////////////////////////////////////////////////////
// TILE IMAGE FILE FUNCTIONS                                                            //
//////////////////////////////////////////////////////////////////////////////////////////
void    init_tile_image_data(void)
{
    SLONG   i;

    for(i=0; i<MAX_TILE_IMAGES; i++)
    {
        tile_image_data[i].flag = 0;
        tile_image_data[i].buffer = NULL;
    }
    total_tile_image_datas = 0;
}


void    free_tile_image_data(void)
{
    SLONG   i;

    for(i=0; i<MAX_TILE_IMAGES; i++)
    {
        if(tile_image_data[i].buffer)
        {
            free(tile_image_data[i].buffer);
            tile_image_data[i].buffer = NULL;
        }
        tile_image_data[i].flag = 0;
    }
    total_tile_image_datas = 0;
}


PIXEL*  create_tile_image_buffer(void)
{
    return  (PIXEL*)malloc(sizeof(PIXEL) * TILE_DATA_SIZE);
}


void    destroy_tile_image_buffer(PIXEL **buffer)
{
    if(*buffer)
    {
        free(*buffer);
        *buffer = NULL;
    }
}


SLONG   load_tile_image_data_from_file(USTR *filename)
{
    TILE_IMAGE_HEAD head;
    PACK_FILE*   fp = NULL;
    SLONG   read_size, i;
    PIXEL   buffer[TILE_DATA_SIZE];

    if(NULL == (fp = pack_fopen((const char *)filename, "rb")))
    {
        log_error(1, "file %s open error", filename);
        goto some_error;
    }
    read_size = pack_fread(&head, 1, sizeof(TILE_IMAGE_HEAD), fp);
    if(sizeof(TILE_IMAGE_HEAD) != read_size)
    {
        log_error(1, "read tile image head error");
        goto some_error;
    }

    if(MAKEFOURCC('R','A','Y','S') != head.copyright)
    {
        log_error(1, "tile image file copyright error");
        goto some_error;
    }
    if(MAKEFOURCC('T','I','L','E') != head.id)
    {
        log_error(1, "tile image file format error");
        goto some_error;
    }
    if(TILE_IMAGE_FILE_VERSION != head.version)
    {
        log_error(1, "tile image file version invalid");
        goto some_error;
    }
    if( (TILE_WIDTH != head.tile_width)||(TILE_HEIGHT != head.tile_height) )
    {
        log_error(1, "tile image size mismatched");
        goto some_error;
    }

    free_tile_image_data();

    total_tile_image_datas = 0;
    for(i=0; i<head.total_tiles; i++)
    {
        read_size = pack_fread(buffer, 1, SIZEOFPIXEL * TILE_DATA_SIZE, fp);
        if(SIZEOFPIXEL * TILE_DATA_SIZE == read_size) //read_size is the blocks(here is sizeof(PIXEL), 2 bytes)
        {
            tile_image_data[total_tile_image_datas].buffer = create_tile_image_buffer();
            if(tile_image_data[total_tile_image_datas].buffer)
            {
                convert_buffer_fff2hi(buffer, TILE_DATA_SIZE);
                memcpy(tile_image_data[total_tile_image_datas].buffer, buffer, TILE_DATA_SIZE * sizeof(PIXEL));
                tile_image_data[total_tile_image_datas].flag = 1;

                total_tile_image_datas ++;
            }
            else
            {
                log_error(1, "memory alloc error while read tile image");
                goto some_error;
            }
        }
    }

    if(fp) pack_fclose(fp);

    log_error(1, "Load tile image data (%d tile images) ok.", total_tile_image_datas);

    return  TTN_OK;

some_error:
    if(fp) pack_fclose(fp);
    return  TTN_NOT_OK;
}


SLONG   naked_read_tile_image(PACK_FILE *fp, PIXEL **image_buffer)
{
    PIXEL   *tmp = NULL;

    if(NULL == (tmp = create_tile_image_buffer()))
    {
        log_error(1, "memory alloc error when read tile image");
        return  TTN_ERROR;
    }
    pack_fread(tmp, sizeof(PIXEL), TILE_DATA_SIZE, fp);
    convert_buffer_fff2hi(tmp, TILE_DATA_SIZE);
    *image_buffer = tmp;
    return  TTN_OK;
}


