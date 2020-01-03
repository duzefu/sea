/*
**	UIInfobar.cpp
**	ui information bar.
**
**	Jack, 2002/06/18.
*/
#include "MainFun.h"
#include "UIInfoBar.h"



/******************************************************************************************************************/
/* INFOBAR FUNCTIONS                                                                                              */
/******************************************************************************************************************/
void	clear_info_bar( INFO_BAR *p )
{
	SLONG	i;

	p->flag = 0;
	p->range_sx = 0;
	p->range_sy = 0;
	p->range_xl = 0;
	p->range_yl = 0;
	p->bound_sx = 0;
	p->bound_sy = 0;
	p->bound_xl = SCREEN_WIDTH;
	p->bound_yl = SCREEN_HEIGHT;
	p->gap_xl = INFO_BAR_GAP_XL;
	p->gap_yl = INFO_BAR_GAP_YL;
	p->font_xl = INFO_BAR_FONT_WIDTH;
	p->font_yl = INFO_BAR_FONT_HEIGHT;
	p->lines = 0;
	p->max_pure_len = 0;

	for(i=0; i<INFO_BAR_LINES; i++)
	{
		memset(p->pure_str, '\0', INFO_BAR_LINE_LEN);
		memset(p->full_str, '\0', INFO_BAR_LINE_LEN);
		p->pure_len[i] = 0;
	}
}


SLONG	add_info_bar_string( INFO_BAR *p, USTR *pure_str, USTR *full_str )
{
	SLONG	index;

	index = p->lines;
	if(index < INFO_BAR_LINES)
	{
		strcpy((char *)p->pure_str[index], (const char *)pure_str);
		strcpy((char *)p->full_str[index], (const char *)full_str);
		p->pure_len[index] = (SLONG)strlen((const char *)pure_str);
		if(p->pure_len[index] > p->max_pure_len)
		{
			p->max_pure_len = p->pure_len[index];
		}

		p->lines ++;
	}
	return	index;
}

void	set_info_bar_range( INFO_BAR *p, SLONG range_sx, SLONG range_sy, SLONG range_xl, SLONG range_yl )
{
	p->range_sx = range_sx;
	p->range_sy = range_sy;
	p->range_xl = range_xl;
	p->range_yl = range_yl;
}


void	set_info_bar_bound( INFO_BAR *p, SLONG bound_sx, SLONG bound_sy, SLONG bound_xl, SLONG bound_yl )
{
	p->bound_sx = bound_sx;
	p->bound_sy = bound_sy;
	p->bound_xl = bound_xl;
	p->bound_yl = bound_yl;
}


void	set_info_bar_gap( INFO_BAR *p, SLONG gap_xl, SLONG gap_yl)
{
	p->gap_xl = gap_xl;
	p->gap_yl = gap_yl;
}


void	redraw_info_bar( INFO_BAR *p, void *vbitmap )
{
	BMP *	bitmap = (BMP*)vbitmap;
	SLONG	win_sx, win_sy, win_xl, win_yl;
	SLONG	win_cx, disp_x, disp_y;
	SLONG	i;

    win_xl = (p->max_pure_len + 1) / 2 * p->font_xl + p->gap_xl ;
    win_yl = p->lines * p->font_yl + p->gap_yl;
    find_appropriate_window_position(p->range_sx, p->range_sy, p->range_xl, p->range_yl, 
		bitmap->w, bitmap->h, win_xl, win_yl,
        &win_sx, &win_sy);
    win_cx = win_sx + win_xl / 2;
    dark_put_bar(win_sx, win_sy, win_xl, win_yl, bitmap, 10);
    disp_x = win_sx + p->gap_xl / 2;
    disp_y = win_sy + p->gap_yl / 2;
    for(i=0; i<p->lines; i++)
    {
        disp_x = win_cx - (p->pure_len[i] + 1) / 2 * p->font_xl / 2;
#if (INFO_BAR_FONT_SIZE == 16)
        print16(disp_x, disp_y, (USTR*)p->full_str[i], PEST_PUT, bitmap);
#endif
#if (INFO_BAR_FONT_SIZE == 12)
        print12(disp_x, disp_y, (USTR*)p->full_str[i], PEST_PUT, bitmap);
#endif
        disp_y += p->font_yl;
    }
	return;
}



void    find_appropriate_window_position(SLONG stand_win_sx, SLONG stand_win_sy, SLONG stand_win_xl, SLONG stand_win_yl,
                                         SLONG range_win_xl, SLONG range_win_yl, SLONG find_win_xl, SLONG find_win_yl,
                                         SLONG *find_win_sx, SLONG *find_win_sy)
{
    SLONG   stand_win_ex, stand_win_ey;
    SLONG   find_sx, find_sy;

    stand_win_ex = stand_win_sx + stand_win_xl;
    stand_win_ey = stand_win_sy + stand_win_yl;

    //find window start y position ----------------------------------
    if(stand_win_sy > range_win_yl - stand_win_ey)
    {
        if(stand_win_sy >= find_win_yl)
        {
            find_sy = stand_win_sy - find_win_yl;
        }
        else if(range_win_yl - stand_win_ey >= find_win_yl)
        {
            find_sy = stand_win_ey;
        }
        else
        {
            find_sy = stand_win_sy;
        }
    }
    else
    {
        if(stand_win_sy >= find_win_yl)
        {
            find_sy = stand_win_sy - find_win_yl;
        }
        else if(range_win_yl - stand_win_ey >= find_win_yl)
        {
            find_sy = stand_win_ey;
        }
        else
        {
            find_sy = stand_win_sy;
        }
    }

    if(find_sy + find_win_yl > range_win_yl)
    {
        find_sy = range_win_yl - find_win_yl;
    }
    if(find_sy < 0)
    {
        find_sy = 0;
    }

    //find window start x position ----------------------------------
    find_sx = stand_win_sx + stand_win_xl / 2 - find_win_xl / 2;
    if(find_sx + find_win_xl > range_win_xl)
    {
        find_sx = range_win_xl - find_win_xl;
    }
    if(find_sx < 0)
    {
        find_sx = 0;
    }

    *find_win_sx = find_sx;
    *find_win_sy = find_sy;
}


