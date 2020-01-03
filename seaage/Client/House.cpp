/*
**  house.cpp
**  house functions.
**
**  Jack, 2002.3.25.
*/
#include "mainfun.h"
#include "tileimage.h"
#include "house.h"


/************************************************************************************************************/
/* STRUCTS                                                                                                  */
/************************************************************************************************************/
typedef struct  tagHOUSE_HEAD
{
    ULONG   copyright;      //house file copyright, 'RAYS'.
    ULONG   id;             //house file id, 'HOUS'.
    ULONG   version;        //house file version, HOUSE_FILE_VERSION.
    ULONG   head_size;      //size of this head.
    //
    ULONG   data_flags;     //house data flags
    SLONG   floor_offset;   //house floor file offset(from file start)
    SLONG   object_offset;  //house object file offset(from file start)
    SLONG   roof_offset;    //house roof file offset(from file start)
    SLONG   total_objects;  //total house objects.
    //
    SLONG   reserved[3];    //reserved data.
} HOUSE_HEAD, *LPHOUSE_HEAD;


typedef struct  tagHOUSE_OBJECTS_INFO
{
    SLONG   total_objects;
    SLONG   offset[1];
} HOUSE_OBJECTS_INFO, *LPHOUSE_OBJECTS_INFO;



/************************************************************************************************************/
/* FUNCTIONS PROTOTYPES                                                                                     */
/************************************************************************************************************/
static	HOUSE_FLOOR*    create_house_floor(SLONG cw, SLONG ch);
static	HOUSE_OBJECT*   create_house_object(void);
static	HOUSE_DATA*     create_house(SLONG total_objects);
static	void    destroy_house_roof(HOUSE_ROOF *house_roof);
static	HOUSE_OBJECTS_INFO* create_house_objects_info(SLONG total_objects);
static	void    destroy_house_objects_info(HOUSE_OBJECTS_INFO **info);
static	SLONG   get_house_objects_info_size(HOUSE_OBJECTS_INFO *info);
static	XIMG*   create_ximg(void);
static	void    destroy_ximg(XIMG **ximg);
static	SLONG   naked_read_ximg(PACK_FILE *fp, XIMG **ximg);
static	SLONG   naked_read_house_floor(PACK_FILE *fp, HOUSE_FLOOR **house_floor);
static	SLONG   naked_read_house_object(PACK_FILE *fp, HOUSE_OBJECT **house_object);
static	SLONG   naked_read_house_roof(PACK_FILE *fp, HOUSE_ROOF **house_roof);
//


/************************************************************************************************************/
/* MAIN HOUSE FUNCTIONS                                                                                     */
/************************************************************************************************************/
SLONG   load_house_from_file(USTR *filename, HOUSE_DATA **house_data)
{
    PACK_FILE    *fp = NULL;
    HOUSE_HEAD  house_head;
    HOUSE_DATA *tmp = NULL;
    HOUSE_FLOOR *house_floor = NULL;
    HOUSE_OBJECT **house_object = NULL;
    HOUSE_ROOF *house_roof = NULL;
    HOUSE_OBJECTS_INFO *info = NULL;
    SLONG   i, total_objects, info_size;

    if(NULL == (fp = pack_fopen((const char *)filename, "rb")))
    {
        log_error(1, "file %s open error", filename);
        goto some_error;
    }
    pack_fread(&house_head, 1, sizeof(HOUSE_HEAD), fp);
    total_objects = house_head.total_objects;

    if(house_head.data_flags & HOUSE_FILE_DATA_UNDER)
    {
        pack_fseek(fp, house_head.floor_offset, SEEK_SET);

        if(TTN_OK != naked_read_house_floor(fp, &house_floor))
        {
            log_error(1, "read house floor error");
            goto some_error;
        }
    }
    if(house_head.data_flags & HOUSE_FILE_DATA_OBJECT)
    {
        pack_fseek(fp, house_head.object_offset, SEEK_SET);

        if(NULL == (info = create_house_objects_info(total_objects)))
        {
            log_error(1, "create house objects info error when load house");
            goto some_error;
        }
        info_size = get_house_objects_info_size(info);
        pack_fread(info, 1, info_size, fp);

        if(NULL == (house_object = (HOUSE_OBJECT**)malloc(sizeof(HOUSE_OBJECT*)*total_objects)))
        {
            log_error(1, "memory alloc error when load house");
            goto some_error;
        }
        for(i=0; i<total_objects; i++)
        {
            pack_fseek(fp, info->offset[i], SEEK_SET);

            if(TTN_OK != naked_read_house_object(fp, &house_object[i]))
            {
                log_error(1, "read house object %d error", i);
                goto some_error;
            }
        }

        destroy_house_objects_info(&info);
    }

    if(house_head.data_flags & HOUSE_FILE_DATA_ROOF)
    {
        pack_fseek(fp, house_head.roof_offset, SEEK_SET);

        if(TTN_OK != naked_read_house_roof(fp, &house_roof))
        {
            log_error(1, "read house roof error");
            goto some_error;
        }
    }
    if(fp) { pack_fclose(fp); fp = NULL; }

    if(NULL == (tmp = create_house(total_objects)))
    {
        log_error(1, "memory alloc error");
        goto some_error;
    }
    tmp->floor = house_floor;
    tmp->roof = house_roof;
    for(i=0; i<total_objects; i++)
    {
        tmp->object[i] = house_object[i];
    }
    if(house_object) { free(house_object); house_object = NULL; }
    *house_data = tmp;

    return  TTN_OK;

some_error:
    if(fp) { pack_fclose(fp); fp = NULL; }
    if(house_object) { free(house_object); house_object = NULL; }
    if(tmp) { free(tmp); tmp = NULL; }
    destroy_house_objects_info(&info);

    return  TTN_ERROR;
}


void    destroy_house(HOUSE_DATA **house_data)
{
    HOUSE_DATA  *p = NULL;
    SLONG   i;

    if(!(*house_data))
        return;

    p = (*house_data);
    if(p->floor)
    {
        if(p->floor->flag & HOUSE_FLOOR_ACTIVE)
        {
            for(i=0; i<p->floor->cw * p->floor->ch; i++)
            {
                destroy_ximg(&p->floor->ximg[i]);
            }
        }
        free(p->floor->ximg);
        p->floor->ximg = NULL;
        free(p->floor);
        p->floor = NULL;
    }
    if(p->roof)
    {
        if(p->roof->flag & HOUSE_ROOF_ACTIVE)
        {
            if(p->roof->poly) 
            {
                D3_destroy_poly(p->roof->poly);
                p->roof->poly = NULL;
            }
            destroy_rla(&p->roof->rla);
        }
        free(p->roof);
        p->roof = NULL;
    }
    if(p->total_objects > 0)
    {
        if(p->object)
        {
            for(i=0; i<p->total_objects; i++)
            {
                if(p->object[i]->poly)
                {
                    D3_destroy_poly(p->object[i]->poly);
                    p->object[i]->poly = NULL;
                }
                if(p->object[i]->rle)
                {
                    destroy_rle(&p->object[i]->rle);
                }
                free(p->object[i]);
                p->object[i] = NULL;
            }
        }
        free(p->object);
        p->object = NULL;
    }
    free(*house_data);
    *house_data = NULL;
    return;
}


void    put_ximg(SLONG sx, SLONG sy, XIMG *ximg, BMP *bitmap)
{
    switch(ximg->type)
    {
    case IMAGE_TYPE_NULL:
        break;
    case IMAGE_TYPE_PIXEL:
        put_tile_image(sx, sy, ximg->buffer, bitmap);
        break;
    case IMAGE_TYPE_RLE:
        put_rle(sx, sy, ximg->rle, bitmap);
        break;
    }
}



void    range_put_ximg(SLONG sx, SLONG sy, XIMG *ximg, BMP *bitmap)
{
    switch(ximg->type)
    {
    case IMAGE_TYPE_NULL:
        break;
    case IMAGE_TYPE_PIXEL:
        range_put_tile_image(sx, sy, ximg->buffer, bitmap);
        break;
    case IMAGE_TYPE_RLE:
        put_rle(sx, sy, ximg->rle, bitmap);
        break;
    }
}


SLONG   naked_read_bitmap(PACK_FILE *fp, BMP **bitmap)
{
    BMP *bc = NULL,tbc;
    SLONG y;
    
    pack_fread(&tbc,1,sizeof(BMP)-sizeof(PIXEL *),fp);
    if(NULL==(bc=(BMP *)create_bitmap(tbc.w, tbc.h) ) )
    {
        sprintf((char *)print_rec,"memory alloc error(naked read bitmap)");
        log_error(1,print_rec);
        goto _some_error;
    }
    for(y=0;y<bc->h;++y)
    {
        pack_fread(bc->line[y],1,bc->pitch,fp);
    }
    convert_bitmap_fff2hi(bc);
    *bitmap = bc;
    return  TTN_OK;

_some_error:
    if(bc) destroy_bitmap(&bc);
    return  TTN_ERROR;
}



/************************************************************************************************************/
/* STATIC FUNCTIONS                                                                                         */
/************************************************************************************************************/
static	HOUSE_FLOOR*    create_house_floor(SLONG cw, SLONG ch)
{
    HOUSE_FLOOR *tmp = NULL;
    XIMG    **ppximg = NULL;
    SLONG   i;

    if(NULL == (ppximg = (XIMG **)malloc(sizeof(XIMG*) * (cw * ch))))
    {
        log_error(1, "memory alloc error");
        goto some_error;
    }
    if(NULL == (tmp = (HOUSE_FLOOR *)malloc(sizeof(HOUSE_FLOOR))))
    {
        log_error(1, "memory alloc error");
        goto some_error;
    }
    tmp->flag = 0;
    tmp->cw = cw;
    tmp->ch = ch;
    tmp->px = 0;
    tmp->py = 0;
    tmp->pz = 0;
    tmp->ximg = ppximg;
    for(i=0; i<cw * ch; i++)
    {
        tmp->ximg[i] = NULL;
    }
    return  (HOUSE_FLOOR*)tmp;

some_error:
    if(tmp) {free(tmp); tmp = NULL; }
    if(ppximg) {free(ppximg); ppximg = NULL; }
    return  NULL;
}


static	HOUSE_OBJECT*   create_house_object(void)
{
    HOUSE_OBJECT    *tmp = NULL;

    if(NULL == (tmp = (HOUSE_OBJECT*)malloc(sizeof(HOUSE_OBJECT))))
    {
        log_error(1, "memory alloc error");
        return  NULL;
    }
    tmp->flag = 0;
    tmp->px = 0;
    tmp->py = 0;
    tmp->pz = 0;
    tmp->fx = 0;
    tmp->fy = 0;
    tmp->poly = NULL;
    tmp->rle = NULL;
    return  (HOUSE_OBJECT*)tmp;
}


static	HOUSE_DATA* create_house(SLONG total_objects)
{
    HOUSE_DATA* tmp = NULL;
    HOUSE_OBJECT**  ppobj = NULL;

    if(NULL == (tmp = (HOUSE_DATA*)malloc(sizeof(HOUSE_DATA))))
    {
        log_error(1, "memory alloc error");
        goto some_error;
    }
    if(NULL == (ppobj = (HOUSE_OBJECT**)malloc(sizeof(HOUSE_OBJECT*) * total_objects)))
    {
        log_error(1, "memory alloc error");
        goto some_error;
    }
    tmp->total_objects = total_objects;
    tmp->floor = NULL;
    tmp->roof = NULL;
    tmp->object = ppobj;
    return  (HOUSE_DATA *)tmp;

some_error:
    if(tmp) { free(tmp); tmp = NULL;}
    if(ppobj) { free(ppobj); ppobj = NULL;}
    return  NULL;
}


static	void    destroy_house_roof(HOUSE_ROOF **house_roof)
{
    if(!(*house_roof))
        return;
    if((*house_roof)->poly) 
    {
        D3_destroy_poly((*house_roof)->poly);
        (*house_roof)->poly = NULL;
    }
    destroy_rla(&(*house_roof)->rla);
    free(*house_roof);
    *house_roof = NULL;
}


static	HOUSE_OBJECTS_INFO* create_house_objects_info(SLONG total_objects)
{
    HOUSE_OBJECTS_INFO *tmp = NULL;
    SLONG   i;

    if(NULL == (tmp = (HOUSE_OBJECTS_INFO *)malloc(sizeof(HOUSE_OBJECTS_INFO) + (total_objects-1) * sizeof(SLONG))))
        return  NULL;
    tmp->total_objects = total_objects;
    for(i=0; i<total_objects; i++)
    {
        tmp->offset[i] = 0;
    }
    return  tmp;
}


static	void    destroy_house_objects_info(HOUSE_OBJECTS_INFO **info)
{
    if(*info)
    {
        free(*info);
        *info = NULL;
    }
}


static	SLONG   get_house_objects_info_size(HOUSE_OBJECTS_INFO *info)
{
    SLONG   size;

    if(!info)   return  0;
    size = sizeof(HOUSE_OBJECTS_INFO) + (info->total_objects-1) * sizeof(SLONG);
    return  size;
}


static	XIMG*   create_ximg(void)
{
    return  (XIMG*)malloc(sizeof(XIMG));
}


static	void    destroy_ximg(XIMG **ximg)
{
    if(*ximg)
    {
        switch((*ximg)->type)
        {
        case IMAGE_TYPE_PIXEL:
            destroy_tile_image_buffer(&((*ximg)->buffer));
            break;
        case IMAGE_TYPE_RLE:
            destroy_rle(&((*ximg)->rle));
            break;
        }
        free(*ximg);
        *ximg = NULL;
    }
}



static	SLONG   naked_read_ximg(PACK_FILE *fp, XIMG **ximg)
{
    XIMG    head, *tmp = NULL;
    PIXEL   *pixels;
    RLE     *rle;

    pack_fread(&head, 1, sizeof(XIMG) - sizeof(PIXEL *), fp);
    if(NULL == (tmp = create_ximg()))
    {
        log_error(1, "memory alloc ximg error");
        return  TTN_ERROR;
    }
    memcpy(tmp, &head, sizeof(XIMG) - sizeof(PIXEL*));
    tmp->buffer = NULL;
    tmp->rle = NULL;
    switch(tmp->type)
    {
    case IMAGE_TYPE_NULL:
        break;
    case IMAGE_TYPE_PIXEL:
        if(TTN_OK != naked_read_tile_image(fp, &pixels))
        {
            log_error(1, "read ximg pixels error");
            return  TTN_ERROR;
        }
        tmp->buffer = pixels;
        break;
    case IMAGE_TYPE_RLE:
        if(TTN_OK != naked_read_rle(fp, &rle))
        {
            log_error(1, "read ximg rle error");
            return  TTN_ERROR;
        }
        tmp->rle = rle;
        break;
    }
    *ximg = tmp;

    return  TTN_OK;
}


static	SLONG   naked_read_house_floor(PACK_FILE *fp, HOUSE_FLOOR **house_floor)
{
    HOUSE_FLOOR head, *tmp = NULL;
    XIMG    *ximg  = NULL;
    SLONG   i;

    pack_fread(&head, 1, sizeof(HOUSE_FLOOR) - sizeof(XIMG**), fp);
    if(NULL == (tmp = create_house_floor(head.cw, head.ch)))
    {
        log_error(1, "memory alloc house floor error");
        return  TTN_ERROR;
    }
    memcpy(tmp, &head, sizeof(HOUSE_FLOOR) - sizeof(XIMG**));
    for(i=0; i<tmp->cw * tmp->ch; i++)
    {
        if(TTN_OK != naked_read_ximg(fp, &ximg))
        {
            log_error(1, "read house floor ximg error");
            return  TTN_ERROR;
        }
        tmp->ximg[i] = ximg;
    }
    *house_floor = tmp;

    return  TTN_OK;
}



static	SLONG   naked_read_house_object(PACK_FILE *fp, HOUSE_OBJECT **house_object)
{
    HOUSE_OBJECT    head, *tmp = NULL;
    RLE *rle = NULL;

    pack_fread(&head, 1, sizeof(HOUSE_OBJECT) - sizeof(POLY*) - sizeof(RLE *), fp);
    if(NULL == (tmp = (HOUSE_OBJECT *)malloc(sizeof(HOUSE_OBJECT))))
    {
        log_error(1, "memory alloc house object error");
        return  TTN_ERROR;
    }
    memcpy(tmp, &head, sizeof(HOUSE_OBJECT) - sizeof(POLY*) - sizeof(RLE*));
    tmp->poly = D3_create_poly();
    pack_fread(tmp->poly, 1, sizeof(POLY), fp);
    if(TTN_OK != naked_read_rle(fp, &rle))
    {
        log_error(1, "read house object rle error");
        return  TTN_ERROR;
    }
    tmp->rle = rle;
    *house_object = tmp;
    return  TTN_OK;
}


static	SLONG   naked_read_house_roof(PACK_FILE *fp, HOUSE_ROOF **house_roof)
{
    HOUSE_ROOF head, *tmp = NULL;
    RLA *rla = NULL;

    pack_fread(&head, 1, sizeof(HOUSE_ROOF) - sizeof(POLY*) - sizeof(RLA*), fp);
    if(NULL == (tmp = (HOUSE_ROOF *)malloc(sizeof(HOUSE_ROOF))))
    {
        log_error(1, "memory alloc house roof error");
        return  TTN_ERROR;
    }
    memcpy(tmp, &head, sizeof(HOUSE_ROOF) - sizeof(POLY*) - sizeof(RLA*));
    tmp->poly = D3_create_poly();
    pack_fread(tmp->poly, 1, sizeof(POLY), fp);
    if(TTN_OK != naked_read_rla(fp, &rla))
    {
        log_error(1, "read house roof rla error");
        return  TTN_ERROR;
    }
    tmp->rla = rla;
    *house_roof = tmp;
    return  TTN_OK;
}


