/*
**  SWAPSCR.CPP
**  Swap screen functions.
**
**  Jack, 2002.5.10.
*/
#include "mainfun.h"
#include "SwapScr.h"
#include "ClientMain.h"

#define SWAPSCR_VOICE_CHANNEL       0
#define VOICE_SWAPSCR_LINE_SKIP     "sound\\lineskip.wav"
#define VOICE_SWAPSCR_LINE_RAND     "sound\\linerand.wav"
#define VOICE_SWAPSCR_BLOCK_RAND    "sound\\blockrnd.wav"
#define VOICE_SWAPSCR_SCALE_A       "sound\\scalea.wav"
#define VOICE_SWAPSCR_SCALE_B       "sound\\scaleb.wav"
#define VOICE_SWAPSCR_HELIX_A       "sound\\helixa.wav"
#define VOICE_SWAPSCR_HELIX_B       "sound\\helixa.wav"
//
#define IDLE_LOOP() 

//GLOBALS /////////////////////////////////////////////////////////////////////////////
SWAPSCR_DATA	swapscr_data;


///////////////////////////////////////////////////////////////////////////////////////
// SWAP SCREEN(«Ì¹õ¤Á´«®ÄªG)                                                         //
///////////////////////////////////////////////////////////////////////////////////////
//¹j¦æ¥­²¾¤Á´«
SLONG	redraw_swap_screen_with_line_skip(SLONG curr_step, BMP *dest_bitmap, BMP *src_bitmap, BMP *bitmap)
{
    enum	{ XX_WIDTH = 100 };
    SLONG   skip, y;
	SLONG	total_steps;

	if(curr_step == 0 && swapscr_data.play_sound)
	{
		stop_voice(SWAPSCR_VOICE_CHANNEL);
		set_data_file(packed_sound_file);
		play_voice(SWAPSCR_VOICE_CHANNEL, 0, (USTR*)VOICE_SWAPSCR_LINE_SKIP);
		swapscr_data.play_sound = false;
	}

	total_steps = SCREEN_WIDTH / XX_WIDTH;
	curr_step = CLAMP(curr_step, 0, total_steps-1);

	skip = XX_WIDTH * curr_step;
	for(y = 0; y < SCREEN_HEIGHT; y += 2)
	{
		memcpy(&bitmap->line[y][0], &src_bitmap->line[y][skip], (SCREEN_WIDTH-skip) * SIZEOFPIXEL);
		memcpy(&bitmap->line[y][SCREEN_WIDTH-skip], &dest_bitmap->line[y][0], skip * SIZEOFPIXEL);
		
		memcpy(&bitmap->line[y+1][0], &dest_bitmap->line[y+1][SCREEN_WIDTH-skip], skip * SIZEOFPIXEL);
		memcpy(&bitmap->line[y+1][skip], &src_bitmap->line[y+1][0], (SCREEN_WIDTH-skip) * SIZEOFPIXEL);
	}

	return	total_steps;
}


// ³v¦æÀHÉó¶¡¹j¤Á´«
SLONG	redraw_swap_screen_with_line_rand(SLONG curr_step, BMP *dest_bitmap, BMP *src_bitmap, BMP *bitmap)
{
    const   SLONG   XX_WIDTH = 40;
    SLONG   copy_len, y;
	SLONG	total_steps;

	if(curr_step == 0 && swapscr_data.play_sound)
	{
		stop_voice(SWAPSCR_VOICE_CHANNEL);
		set_data_file(packed_sound_file);
		play_voice(SWAPSCR_VOICE_CHANNEL, 0, (USTR*)VOICE_SWAPSCR_LINE_RAND);
		swapscr_data.play_sound = false;
	}

	total_steps = SCREEN_WIDTH/XX_WIDTH;
	curr_step = CLAMP(curr_step, 0, total_steps-1);
    
	for(y=0; y<SCREEN_HEIGHT; y++)
	{
		copy_len = swapscr_data.copy_base + rand()%XX_WIDTH;
		memcpy(&bitmap->line[y][0], &dest_bitmap->line[y][0], copy_len * SIZEOFPIXEL);
	}
	swapscr_data.copy_base += XX_WIDTH;

	return	total_steps;
}


SLONG	redraw_swap_screen_with_move_down(SLONG curr_step, BMP *dest_bitmap, BMP *src_bitmap, BMP *bitmap)
{
    enum {  STEPS = 16 };
    SLONG   sx, sy;
	SLONG	total_steps;

	total_steps = STEPS;
	curr_step = CLAMP(curr_step, 0, total_steps-1);
    sx = 0;
    sy = -bitmap->h + bitmap->h / STEPS * curr_step;

	put_bitmap(0, 0, src_bitmap, bitmap);
	if(swapscr_data.redraw_dest_func)
		swapscr_data.redraw_dest_func(sx, sy, bitmap);
	else
		put_bitmap(sx, sy, dest_bitmap, bitmap);

	return	total_steps;
}


SLONG	redraw_swap_screen_with_drag_up(SLONG curr_step, BMP *dest_bitmap, BMP *src_bitmap, BMP *bitmap)
{
    enum {  STEPS = 16 };
    SLONG   sx, sy;
	SLONG	total_steps;

	total_steps = STEPS;
	curr_step = CLAMP(curr_step, 0, total_steps-1);
    sx = 0;
    sy = 0 - bitmap->h / STEPS * curr_step;

	put_bitmap(0, 0, src_bitmap, bitmap);
	if(swapscr_data.redraw_dest_func)
		swapscr_data.redraw_dest_func(sx, sy, bitmap);
	else
		put_bitmap(sx, sy, dest_bitmap, bitmap);

	return	total_steps;
}


SLONG	redraw_swap_screen_with_move_up(SLONG curr_step, BMP *dest_bitmap, BMP *src_bitmap, BMP *bitmap)
{
    enum {  STEPS = 16 };
    SLONG   sx, sy;
	SLONG	total_steps;

	total_steps = STEPS;
	curr_step = CLAMP(curr_step, 0, total_steps-1);
    sx = 0;
    sy = bitmap->h - bitmap->h / STEPS * curr_step;

	put_bitmap(0, 0, src_bitmap, bitmap);
	if(swapscr_data.redraw_dest_func)
		swapscr_data.redraw_dest_func(sx, sy, bitmap);
	else
		put_bitmap(sx, sy, dest_bitmap, bitmap);

	return	total_steps;
}


SLONG	redraw_swap_screen_with_drag_down(SLONG curr_step, BMP *dest_bitmap, BMP *src_bitmap, BMP *bitmap)
{
    enum {  STEPS = 16 };
    SLONG   sx, sy;
	SLONG	total_steps;

	total_steps = STEPS;
	curr_step = CLAMP(curr_step, 0, total_steps-1);
    sx = 0;
    sy = 0 + bitmap->h / STEPS * curr_step;

	put_bitmap(0, 0, src_bitmap, bitmap);
	if(swapscr_data.redraw_dest_func)
		swapscr_data.redraw_dest_func(sx, sy, bitmap);
	else
		put_bitmap(sx, sy, dest_bitmap, bitmap);

	return	total_steps;
}


SLONG	redraw_swap_screen_with_move_right(SLONG curr_step, BMP *dest_bitmap, BMP *src_bitmap, BMP *bitmap)
{
    enum {  STEPS = 16 };
    SLONG   sx, sy;
	SLONG	total_steps;

	total_steps = STEPS;
	curr_step = CLAMP(curr_step, 0, total_steps-1);
    sx = -bitmap->w + bitmap->w / STEPS;
    sy = 0;

	put_bitmap(0, 0, src_bitmap, bitmap);
	if(swapscr_data.redraw_dest_func)
		swapscr_data.redraw_dest_func(sx, sy, bitmap);
	else
		put_bitmap(sx, sy, dest_bitmap, bitmap);

	return	total_steps;
}


SLONG	redraw_swap_screen_with_drag_left(SLONG curr_step, BMP *dest_bitmap, BMP *src_bitmap, BMP *bitmap)
{
    enum {  STEPS = 16 };
    SLONG   sx, sy;
	SLONG	total_steps;

	total_steps = STEPS;
	curr_step = CLAMP(curr_step, 0, total_steps-1);

    sx = 0 - bitmap->w / STEPS * curr_step;
    sy = 0;

	put_bitmap(0, 0, src_bitmap, bitmap);
	if(swapscr_data.redraw_dest_func)
		swapscr_data.redraw_dest_func(sx, sy, bitmap);
	else
		put_bitmap(sx, sy, dest_bitmap, bitmap);
	
	return	total_steps;
}


SLONG	redraw_swap_screen_with_move_left(SLONG curr_step, BMP *dest_bitmap, BMP *src_bitmap, BMP *bitmap)
{
    enum {  STEPS = 16 };
    SLONG   sx, sy;
	SLONG	total_steps;

	total_steps = STEPS;
	curr_step = CLAMP(curr_step, 0, total_steps-1);

    sx = bitmap->w - bitmap->w / STEPS * curr_step ;
    sy = 0;

	put_bitmap(0, 0, src_bitmap, bitmap);
	if(swapscr_data.redraw_dest_func)
		swapscr_data.redraw_dest_func(sx, sy, bitmap);
	else
		put_bitmap(sx, sy, dest_bitmap, bitmap);
	
	return	total_steps;
}


SLONG	redraw_swap_screen_with_drag_right(SLONG curr_step, BMP *dest_bitmap, BMP *src_bitmap, BMP *bitmap)
{
    enum {  STEPS = 16 };
    SLONG   sx, sy;
	SLONG	total_steps;

	total_steps = STEPS;
	curr_step = CLAMP(curr_step, 0, total_steps-1);
    sx = 0 + bitmap->w / STEPS * curr_step;
    sy = 0;

	put_bitmap(0, 0, src_bitmap, bitmap);
	if(swapscr_data.redraw_dest_func)
		swapscr_data.redraw_dest_func(sx, sy, bitmap);
	else
		put_bitmap(sx, sy, dest_bitmap, bitmap);
	
	return	total_steps;
}


/************************************************************************************************************/
/* SWAP SCREEN FUNCTIONS                                                                                    */
/************************************************************************************************************/
void    swap_screen(SLONG type, BMP *dest_bitmap, BMP *src_bitmap)
{
	swapscr_data.swap_type = type;
	swapscr_data.dest_bitmap = dest_bitmap;
	swapscr_data.src_bitmap = src_bitmap;
	swapscr_data.curr_step = 0;
	swapscr_data.total_steps = 999;
	swapscr_data.play_sound = true;
	switch(type)
	{
    case SWAP_SCREEN_LINE_SKIP:
        break;
    case SWAP_SCREEN_LINE_RAND:
		swapscr_data.copy_base = 0;
        break;
    case SWAP_SCREEN_MOVE_DOWN:
        break;
    case SWAP_SCREEN_DRAG_UP:
        break;
    case SWAP_SCREEN_MOVE_UP:
        break;
    case SWAP_SCREEN_DRAG_DOWN:
        break;
    case SWAP_SCREEN_MOVE_RIGHT:
        break;
    case SWAP_SCREEN_DRAG_LEFT:
        break;
    case SWAP_SCREEN_MOVE_LEFT:
        break;
    case SWAP_SCREEN_DRAG_RIGHT:
        break;
	}
	//
	swapscr_data.dwPrevAppState = g_dwAppState;
	g_dwAppState = APPSTATE_SHOW_SWAP_SCREEN;
}


int		init_swap_screen(void)
{
	memset(&swapscr_data, 0, sizeof(swapscr_data));
	swapscr_data.total_steps = 9999;
	return	0;
}

void	free_swap_screen(void)
{
}

void	refresh_swap_screen(void)
{
	swapscr_data.curr_step ++;
	if(swapscr_data.curr_step > swapscr_data.total_steps-1)
	{
		swapscr_data.curr_step = swapscr_data.total_steps-1;

		change_app_state();
	}
}

void	redraw_swap_screen(SLONG sx, SLONG sy, void *vbitmap)
{
	BMP	*bitmap = (BMP*)vbitmap;
	BMP *src_bitmap, *dest_bitmap;
	SLONG	curr_step, total_steps, swap_type;

	curr_step = swapscr_data.curr_step;
	src_bitmap = swapscr_data.src_bitmap;
	dest_bitmap = swapscr_data.dest_bitmap;
	swap_type = swapscr_data.swap_type;
	switch(swap_type)
	{
    case SWAP_SCREEN_LINE_SKIP:
		total_steps = redraw_swap_screen_with_line_skip(curr_step, dest_bitmap, src_bitmap, bitmap);
        break;
    case SWAP_SCREEN_LINE_RAND:
        total_steps = redraw_swap_screen_with_line_rand(curr_step, dest_bitmap, src_bitmap, bitmap);
        break;
    case SWAP_SCREEN_MOVE_DOWN:
        total_steps = redraw_swap_screen_with_move_down(curr_step, dest_bitmap, src_bitmap, bitmap);
        break;
    case SWAP_SCREEN_DRAG_UP:
        total_steps = redraw_swap_screen_with_drag_up(curr_step, dest_bitmap, src_bitmap, bitmap);
        break;
    case SWAP_SCREEN_MOVE_UP:
        total_steps = redraw_swap_screen_with_move_up(curr_step, dest_bitmap, src_bitmap, bitmap);
        break;
    case SWAP_SCREEN_DRAG_DOWN:
        total_steps = redraw_swap_screen_with_drag_down(curr_step, dest_bitmap, src_bitmap, bitmap);
        break;
    case SWAP_SCREEN_MOVE_RIGHT:
        total_steps = redraw_swap_screen_with_move_right(curr_step, dest_bitmap, src_bitmap, bitmap);
        break;
    case SWAP_SCREEN_DRAG_LEFT:
        total_steps = redraw_swap_screen_with_drag_left(curr_step, dest_bitmap, src_bitmap, bitmap);
        break;
    case SWAP_SCREEN_MOVE_LEFT:
        total_steps = redraw_swap_screen_with_move_left(curr_step, dest_bitmap, src_bitmap, bitmap);
        break;
    case SWAP_SCREEN_DRAG_RIGHT:
        total_steps = redraw_swap_screen_with_drag_right(curr_step, dest_bitmap, src_bitmap, bitmap);
        break;
	}

	swapscr_data.total_steps = total_steps;
}


SLONG	handle_swap_screen(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
	case WM_KEYDOWN:
		{
			switch(wParam)
			{
				// Skip swap screen effect and change current application state instantly.
			case VK_SPACE:
				change_app_state();
				break;
			}
		}
		break;
	}
	return	0;
}


SLONG   rand_swap_screen_type(void)
{
    //return  rand() % MAX_SWAP_SCREEN_TYPES;

    //return something between 0 ~ SWAP_SCREEN_MOVE_DOWN-1.
    return  rand() %  SWAP_SCREEN_MOVE_DOWN;
}


void    set_swap_screen_redraw_dest_function(FNREDRAWBITMAP func)
{
	swapscr_data.redraw_dest_func = func;
}

DWORD	get_swap_screen_prev_app_state(void)
{
	return	swapscr_data.dwPrevAppState;
}


