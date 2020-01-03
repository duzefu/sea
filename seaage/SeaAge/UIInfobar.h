/*
**	UIInfobar.h
**	ui information bar.
**
**	Jack, 2002/06/18.
*/
#ifndef _UIINFOBAR_H_
#define _UIINFOBAR_H_


// DEFINES /////////////////////////////////////////////////////////////////////////////////////////////////////////
#define INFO_BAR_FONT_SIZE                      12

#if (INFO_BAR_FONT_SIZE == 16)
#define	INFO_BAR_GAP_XL							16
#define	INFO_BAR_GAP_YL							16
#define	INFO_BAR_LINES							32
#define	INFO_BAR_LINE_LEN						80
#define	INFO_BAR_FONT_WIDTH						16
#define	INFO_BAR_FONT_HEIGHT					20
#endif

#if (INFO_BAR_FONT_SIZE == 12)
#define	INFO_BAR_GAP_XL							12
#define	INFO_BAR_GAP_YL							12
#define	INFO_BAR_LINES							32
#define	INFO_BAR_LINE_LEN						80
#define	INFO_BAR_FONT_WIDTH						12
#define	INFO_BAR_FONT_HEIGHT					16
#endif

// STRUCTURES //////////////////////////////////////////////////////////////////////////////////////////////////////
typedef	struct	tagINFO_BAR
{
	SLONG	flag;
	SLONG	range_sx, range_sy;
	SLONG	range_xl, range_yl;
	SLONG	bound_sx, bound_sy;
	SLONG	bound_xl, bound_yl;
	SLONG	gap_xl, gap_yl;
	SLONG	font_xl, font_yl;
	SLONG	lines;
	SLONG	max_pure_len;
	//
	USTR	pure_str[INFO_BAR_LINES][INFO_BAR_LINE_LEN];
	USTR	full_str[INFO_BAR_LINES][INFO_BAR_LINE_LEN];
	SLONG	pure_len[INFO_BAR_LINES];
} INFO_BAR, *LPINFO_BAR;


// FUNCTIONS ///////////////////////////////////////////////////////////////////////////////////////////////////////
void	clear_info_bar( INFO_BAR *p );
SLONG	add_info_bar_string( INFO_BAR *p, USTR *pure_str, USTR *full_str );
void	set_info_bar_range( INFO_BAR *p, SLONG range_sx, SLONG range_sy, SLONG range_xl, SLONG range_yl );
void	set_info_bar_bound( INFO_BAR *p, SLONG bound_sx, SLONG bound_sy, SLONG bound_xl, SLONG bound_yl );
void	set_info_bar_gap( INFO_BAR *p, SLONG gap_xl, SLONG gap_yl);
void	set_info_bar_font( INFO_BAR *p, SLONG font_xl, SLONG font_yl);
void	redraw_info_bar( INFO_BAR *p, void *vbitmap );
//
void    find_appropriate_window_position(SLONG stand_win_sx, SLONG stand_win_sy, SLONG stand_win_xl, SLONG stand_win_yl,
                                         SLONG range_win_xl, SLONG range_win_yl, SLONG find_win_xl, SLONG find_win_yl,
                                         SLONG *find_win_sx, SLONG *find_win_sy);



#endif//_UIINFOBAR_H_
