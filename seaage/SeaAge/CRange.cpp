/*
**  CRange.cpp
**  Class range functions.
**
**  ZJian, 2001.4.17.
*/
#include "mainfun.h"
#include "CRange.h"




CRange  game_range;




CRange::CRange()
{
    this->max_range = 0;
}

CRange::~CRange()
{
    this->max_range = 0;
}

SLONG   CRange::add(SLONG sx, SLONG sy, SLONG xl, SLONG yl, SLONG type, SLONG id)
{
    SLONG   index=-1;
    if(this->max_range < RANGE_NUM)
    {
        index = this->max_range;
        this->max_range ++;
        this->sx[index] = sx;
        this->sy[index] = sy;
        this->xl[index] = xl;
        this->yl[index] = yl;
        this->type[index] = type;
        this->id[index] = id;
    }
    return index;
}

void    CRange::clear(void)
{
    this->max_range = 0;
}


SLONG   CRange::mapping(SLONG x, SLONG y, SLONG *type, SLONG *id)
{
    SLONG   i;
    SLONG   index = -1;

    for(i=this->max_range-1; i>=0; i--)
    {
        if( x >= this->sx[i] && x < this->sx[i]+this->xl[i]
            && y >= this->sy[i] && y < this->sy[i]+this->yl[i] )
        {
            *type = this->type[i];
            *id = this->id[i];
            index = i;
            break;
        }
    }
    return index;
}


void    CRange::redraw(SLONG view_sx, SLONG view_sy, void *vbitmap)
{
//#ifdef  DEBUG
    BMP *bitmap = (BMP*)vbitmap;
    SLONG   i;
    SLONG   sx, sy, xl, yl, ex, ey;

    for(i=0; i<this->max_range; i++)
    {
        sx = this->sx[i] - view_sx;
        sy = this->sy[i] - view_sy;
        xl = this->xl[i];
        yl = this->yl[i];
        ex = sx + xl - 1;
        ey = sy + yl - 1;
        if( sx >= 0 && ex <= bitmap->w && sy >= 0 && ey <= bitmap->h)
        {
            if(xl > 3 && yl > 3)
            {
                put_box(sx, sy, xl, yl, SYSTEM_BLACK, bitmap);
                put_box(sx + 1, sy + 1, xl - 2, yl - 2, SYSTEM_WHITE, bitmap);
                put_box(sx + 2, sy + 2, xl - 4, yl - 4, SYSTEM_BLACK, bitmap);
            }
        }
    }
//#endif//DEBUG
}


SLONG	CRange::get_top_type(void)
{
	SLONG	i, type;

	type = -1;
    for(i = this->max_range-1; i >= 0; i--)
    {
		if(this->id[i] == -1)
		{
			type = this->type[i];
			break;
		}
    }
	return	type;
}


SLONG   CRange::get_range(SLONG type, SLONG id, SLONG *sx, SLONG *sy, SLONG *xl, SLONG *yl)
{
    SLONG   i;
    SLONG   index = -1;

    for(i=this->max_range-1; i>=0; i--)
    {
        if(this->type[i] == type && this->id[i] == id)
        {
            *sx = this->sx[i];
            *sy = this->sy[i];
            *xl = this->xl[i];
            *yl = this->yl[i];
            index = i;
            break;
        }
    }
    return index;
}
