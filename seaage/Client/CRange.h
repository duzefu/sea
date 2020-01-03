/*
**  CRange.h
**  Class range functions.
**
**  ZJian, 2001.4.17.
*/
#ifndef _CRANGE_H_INCLUDE_
#define _CRANGE_H_INCLUDE_



//range types -----------------------------------------------
#define RT_UNKNOWN      0
#define RT_MAP          10
#define RT_NPC          20
#define RT_CONTAIN      21
#define RT_CHOICE       30
#define RT_TALK         40
#define RT_MENUQUIT     110
#define RT_MAP_ITEM     120
#define RT_HOTEL        130
//
#define RT_UIMAIN       200
#define RT_UISTATE      210
#define RT_UIITEM       220
#define RT_UIMAGIC      230
#define RT_UISYSTEM     240
#define RT_UIMINIMAP    250
#define RT_UITASK       260
#define RT_UISETUP      270
//
#define RT_TRANSFER             400
#define RT_LOADING              410
#define RT_SHOP_SHOWCASE        420
#define RT_SHOP_CUSTOMER        430
#define	RT_DROPCASH				440
//-----------------------------------------------------------


class   CRange
{
private:
    enum { RANGE_NUM = 4096 };
    //-------------------------------------------------------
    SLONG   max_range;
    SLONG   sx[RANGE_NUM];
    SLONG   sy[RANGE_NUM];
    SLONG   xl[RANGE_NUM];
    SLONG   yl[RANGE_NUM];
    SLONG   type[RANGE_NUM];
    SLONG   id[RANGE_NUM];

public:
    CRange();
    ~CRange();
    SLONG   add(SLONG sx, SLONG sy, SLONG xl, SLONG yl, SLONG type, SLONG id);
    void    clear(void);
    SLONG   mapping(SLONG x, SLONG y, SLONG *type, SLONG *id);
    void    redraw(SLONG view_sx, SLONG view_sy, void *vbitmap);
	SLONG	get_top_type(void);
    SLONG   get_range(SLONG type, SLONG id, SLONG *sx, SLONG *sy, SLONG *xl, SLONG *yl);
};


extern  CRange  game_range;


#endif//_CRANGE_H_INCLUDE_
