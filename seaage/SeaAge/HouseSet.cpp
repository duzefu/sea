/*
**  houseset.cpp
**  house set functions.
**
**  Jack, 2002.4.9.
*/
#include "mainfun.h"
#include "house.h"
#include "houseset.h"
#include "clientmain.h"


// DEFINES ////////////////////////////////////////////////////////////////////////////////
//#define HOUSE_SET_FILENAME          "houseset.dat"
//#define HOUSE_SET_FILE_VERSION      0x00010000
//
#define MAX_SET_HOUSES              256


// STRUCTURES /////////////////////////////////////////////////////////////////////////////
typedef struct  tagHOUSE_SET_HEAD
{
    ULONG   copyright;      //house set file copyright, 'RAYS'.
    ULONG   id;             //house number file id, 'HOSS'.
    ULONG   version;        //house file version, HOUSE_SET_FILE_VERSION.
    ULONG   head_size;      //size of this head.
    SLONG   total_houses;   //total set houses.
    SLONG   reserved[3];    //reserved.
} HOUSE_SET_HEAD, *LPHOUSE_SET_HEAD;

typedef struct  tagHOUSE_SET
{
    SLONG   total_houses;               //total houses
    SLONG   reference[MAX_SET_HOUSES];  //house data referance
    //
    HOUSE_DATA  *house_data[MAX_SET_HOUSES];//house datas
} HOUSE_SET, LPHOUSE_SET;


// GLOBALS ////////////////////////////////////////////////////////////////////////////////
HOUSE_SET   house_set;


// FUNCTION ///////////////////////////////////////////////////////////////////////////////
void    init_house_set(void)
{
    SLONG   i;

    house_set.total_houses = 0;
    for(i=0; i<MAX_SET_HOUSES; i++)
    {
        house_set.reference[i] = 0;
        house_set.house_data[i] = NULL;
    }
}


void    free_house_set(void)
{
    SLONG   i;

    for(i=0; i< house_set.total_houses; i++)
    {
        if(house_set.house_data[i])
        {
            destroy_house(&house_set.house_data[i]);
        }
        house_set.reference[i] = 0;
    }
}


SLONG   load_house_set(USTR *filename)
{
    HOUSE_SET_HEAD  head;
    PACK_FILE*   fp = NULL;

    if(NULL == (fp = pack_fopen((const char *)filename, "rb")))
    {
        log_error(1, "open file %s error", filename);
        goto _error;
    }
    pack_fread(&head, 1, sizeof(HOUSE_SET_HEAD), fp);
    house_set.total_houses = head.total_houses;
    if(fp) pack_fclose(fp);
    return  TTN_OK;

_error:
    if(fp) pack_fclose(fp);
    return  TTN_ERROR;
}


//////////////////////////////////////////////////////////////////////////////////////////
// HOUSE PREVIEW FUNCTIONS                                                              //
//////////////////////////////////////////////////////////////////////////////////////////
SLONG   add_reference_for_house(SLONG house_index)
{
    USTR    filename[_MAX_FNAME];

    if(house_index >= 0 && house_index < house_set.total_houses)
    {
        if(house_set.reference[house_index] == 0)
        {
            set_data_file(packed_house_file);
            sprintf((char *)filename, "house\\house%03d.hos", house_index);
            load_house_from_file((USTR*)filename, &house_set.house_data[house_index]);
        }
        house_set.reference[house_index] ++;
    }
    return  TTN_OK;
}


SLONG   dec_reference_for_house(SLONG house_index)
{
    if(house_index >= 0 && house_index < house_set.total_houses)
    {
        if(house_set.reference[house_index] > 0)
        {
            house_set.reference[house_index]--;
            if(house_set.reference[house_index] == 0)
            {
                destroy_house(&house_set.house_data[house_index]);
            }
        }
    }
    return  TTN_OK;
}


XIMG*   get_house_floor_ximg(SLONG house_index, SLONG image_no)
{
    return (XIMG*) house_set.house_data[house_index]->floor->ximg[image_no];
}


HOUSE_OBJECT*   get_house_object(SLONG house_index, SLONG object_index)
{
    return  (HOUSE_OBJECT*)house_set.house_data[house_index]->object[object_index];
}


HOUSE_ROOF*    get_house_roof(SLONG house_index)
{
    return  (HOUSE_ROOF*)house_set.house_data[house_index]->roof;
}

