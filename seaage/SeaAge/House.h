/*
**  house.h
**  house functions header.
**
**  Jack, 2002.3.25.
*/
#ifndef _HOUSE_H_
#define _HOUSE_H_


// DEFINES ////////////////////////////////////////////////////////////////////////////////
//version of house files.
#define HOUSE_FILE_VERSION              0x00010000

//ximg(mixed image) image types
#define IMAGE_TYPE_NULL                 0           //this ximg has no image data.
#define IMAGE_TYPE_PIXEL                1           //image data is pixel array.
#define IMAGE_TYPE_RLE                  2           //image data is rle.

//ximg(mixed image) image attrib mask
#define IMAGE_MASK_INNER                0x00000001  //when someone stay at this image, house roof will be hide.

//house object flags
#define HOUSE_OBJECT_ACTIVE             0x00000001  //this house object is active(in used).
#define HOUSE_OBJECT_MARKED             0x00000002  //this house object is marked.
#define HOUSE_OBJECT_INCOVER            0x00000004  //this house object is whole under the cover.

//house floor flags
#define HOUSE_FLOOR_ACTIVE              0x00000001  //under is active(in used).

//house roof flags
#define HOUSE_ROOF_ACTIVE               0x00000001  //cover is active(in used).

//house data_flags of house file.
#define HOUSE_FILE_DATA_UNDER           0x00000001  //there is a house floor in the house file
#define HOUSE_FILE_DATA_OBJECT          0x00000002  //there are some objects in the house file
#define HOUSE_FILE_DATA_ROOF            0x00000004  //there is a cover in the house file


// STRUCTURES /////////////////////////////////////////////////////////////////////////////
typedef struct  tagXIMG
{
    SLONG   type;           //image type
    SLONG   mask;           //image attrib mask
    union
    {
        PIXEL*  buffer;     //pixels buffer image
        RLE*    rle;        //rle image
    };
} XIMG, *LPXIMG;


typedef struct  tagHOUSE_FLOOR
{
    SLONG   flag;       //flag
    //------------------
    SLONG   px;         //ximg[0]'s x position, related with house's barycenter.
    SLONG   py;         //ximg[0]'s y position, related with house's barycenter.
    SLONG   pz;         //always = 0.
    //------------------
    SLONG   cw;         //count of row ximg(es).
    SLONG   ch;         //count of column ximg(es).
    XIMG**  ximg;       //ximg(es) of the house floor.

} HOUSE_FLOOR, *LPHOUSE_FLOOR;


typedef struct  tagHOUSE_ROOF
{
    SLONG   flag;       //flag
    //------------------
    SLONG   px;         //poly's barycenter x position, related with house's barycenter.
    SLONG   py;         //poly's barycenter y position, related with house's barycenter.
    SLONG   pz;         //poly's barycenter z position, related with house's barycenter.
    //------------------
    SLONG   fx;         //rla image's start x position, related with poly's barycenter position.
    SLONG   fy;         //rla image's start y position, related with poly's barycenter position.
    POLY*   poly;       //poly data of the cover.
    RLA*    rla;        //rla image data of the cover.
} HOUSE_ROOF, *LPHOUSE_ROOF;


typedef struct  tagHOUSE_OBJECT
{
    SLONG   flag;       //flag
    //------------------
    SLONG   px;         //poly's barycenter x position, related with house's barycenter.
    SLONG   py;         //poly's barycenter y position, related with house's barycenter.
    SLONG   pz;         //poly's barycenter z position, related with house's barycenter.
    //------------------
    SLONG   fx;         //rle image's start position, related with poly's barycenter position.
    SLONG   fy;         //
    POLY*   poly;       //poly data of the object.
    RLE*    rle;        //rle image data of the image.
} HOUSE_OBJECT, *LPHOUSE_OBJECT;


typedef struct  tagHOUSE_DATA
{
    SLONG           total_objects;
    HOUSE_FLOOR*    floor;
    HOUSE_ROOF*     roof;
    HOUSE_OBJECT**  object;
} HOUSE_DATA, *LPHOUSE_DATA;


// GLOBALS ////////////////////////////////////////////////////////////////////////////////
//

// FUNCTION PROTOTYPES ////////////////////////////////////////////////////////////////////
//
extern	SLONG   load_house_from_file(USTR *filename, HOUSE_DATA **house_data);
extern	void    destroy_house(HOUSE_DATA **house_data);

extern	void    put_ximg(SLONG sx, SLONG sy, XIMG *ximg, BMP *bitmap);
extern	void    range_put_ximg(SLONG sx, SLONG sy, XIMG *ximg, BMP *bitmap);

extern	SLONG   naked_read_bitmap(PACK_FILE *fp, BMP **bitmap);


#endif//_HOUSE_H_
