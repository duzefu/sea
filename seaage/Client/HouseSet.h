/*
**  houseset.h
**  house set functions.
**
**  Jack, 2002.4.9.
*/
#ifndef _HOUSESET_H_
#define _HOUSESET_H_

extern	void    init_house_set(void);
extern	void    free_house_set(void);
extern	SLONG   load_house_set(USTR *filename);

extern	SLONG   add_reference_for_house(SLONG house_index);
extern	SLONG   dec_reference_for_house(SLONG house_index);
extern	XIMG*   get_house_floor_ximg(SLONG house_index, SLONG image_no);
extern	HOUSE_OBJECT*   get_house_object(SLONG house_index, SLONG object_index);
extern	HOUSE_ROOF*     get_house_roof(SLONG house_index);


#endif//_HOUSESET_H_
