/*
**	UIGameTalk.cpp 
**	user interface of game talk.
**
**	Jack, 2003.1.20
*/
#include "MainFun.h"
#include "CRange.h"
#include "MouseHand.h"
#include "CmdEvent.h"
#include "UIGameTalk.h"


/************************************************************************************************************/
/* DEFINES & STRUCTURES                                                                                     */
/************************************************************************************************************/
typedef	enum GAME_TALK_ENUMS
{   MIN_LINES           =   1,  //5,
REMAIN_HEIGHT           =   20,
LINE_HEIGHT             =   20,
WIN_Y_GAP               =   16,
//
PHOTO_XL                =   126,
PHOTO_YL                =   LINE_HEIGHT * MIN_LINES + 14 + 24,
PHOTO_SX                =   0,
PHOTO_SY                =   308 - 24,
WIN_XL                  =   452,
WIN_YL                  =   LINE_HEIGHT * MIN_LINES + WIN_Y_GAP + REMAIN_HEIGHT,
WIN_SX                  =   126,
WIN_SY                  =   424 - WIN_YL,   //308,
//
TALK_FRAME_RIM_LU       =   0,
TALK_FRAME_RIM_UP       =   1,
TALK_FRAME_RIM_RU       =   2,
TALK_FRAME_RIM_LT       =   3,
TALK_FRAME_RIM_RT       =   4,
TALK_FRAME_RIM_LD       =   5,
TALK_FRAME_RIM_DN       =   6,
TALK_FRAME_RIM_RD       =   7,
//
RIM_INDEX_LU            =   0,
RIM_INDEX_UP            =   1,
RIM_INDEX_RU            =   2,
RIM_INDEX_LT            =   3,
RIM_INDEX_RT            =   4,
RIM_INDEX_LD            =   5,
RIM_INDEX_DN            =   6,
RIM_INDEX_RD            =   7,
} GAME_TALK_ENUMS;


/************************************************************************************************************/
/* GLOBALS                                                                                                  */
/************************************************************************************************************/
GAME_TALK   game_talk;



/************************************************************************************************************/
/* GAME TALK FUNCTIONS                                                                                      */
/************************************************************************************************************/
int     init_game_talk(void)
{
    game_talk.max_text = 0;
    game_talk.flag = FALSE;
    game_talk.offer_npc = -1;
    game_talk.opp_proc = -1;
    game_talk.photo_id = -1;

    game_talk.photo_sx  = PHOTO_SX;
    game_talk.photo_sy  = PHOTO_SY;
    game_talk.photo_xl  = PHOTO_XL;
    game_talk.photo_yl  = PHOTO_YL;

    game_talk.win_sx    = WIN_SX;
    game_talk.win_sy    = WIN_SY;
    game_talk.win_xl    = WIN_XL;
    game_talk.win_yl    = WIN_YL;

    return  0;
}

void    free_game_talk(void)
{
    game_talk.max_text = 0;
    game_talk.flag = FALSE;
    game_talk.offer_npc = -1;
    game_talk.opp_proc = -1;
    game_talk.photo_id = -1;
}


void    active_game_talk(int active)
{
	// Do nothing here.
}

void    clear_game_talk(void)
{
    SLONG   i;

    for(i=0; i<TALK_TEXT_NUM; i++)
    {
        memset(game_talk.text[i], 0, TALK_TEXT_LEN);
        game_talk.len[i][0] = 0;
        game_talk.len[i][1] = 0;
    }
    game_talk.max_text = 0;
    game_talk.photo_id = -1;
    game_talk.flag = FALSE;

    game_talk.photo_sx  = PHOTO_SX;
    game_talk.photo_sy  = PHOTO_SY;
    game_talk.photo_xl  = PHOTO_XL;
    game_talk.photo_yl  = PHOTO_YL;

    game_talk.win_sx    = WIN_SX;
    game_talk.win_sy    = WIN_SY;
    game_talk.win_xl    = WIN_XL;
    game_talk.win_yl    = WIN_YL;
}


SLONG   add_game_talk_text(char *text)
{
    SLONG   index = -1;
    SLONG   i = 0;
    SLONG   add_lines;

    if(game_talk.max_text < TALK_TEXT_NUM)
    {
        index = game_talk.max_text;
        game_talk.max_text ++;
        memset(game_talk.text[index], 0, TALK_TEXT_LEN);
        do {
            game_talk.text[index][i] = text[i];
        }while(i++ < TALK_TEXT_LEN);
        game_talk.len[index][0] = strlen((const char *)game_talk.text[index]);
        game_talk.len[index][1] = 0;

        if(game_talk.max_text > MIN_LINES)
        {
            add_lines = game_talk.max_text - MIN_LINES;

            game_talk.photo_sy  = PHOTO_SY - LINE_HEIGHT * add_lines;
            game_talk.win_sy    = WIN_SY - LINE_HEIGHT * add_lines;
            game_talk.win_yl    = WIN_YL + LINE_HEIGHT * add_lines;
        }
    }
    return index;
}


void    set_game_talk_image(SLONG image_id)
{
    game_talk.photo_id = image_id;
}

SLONG	get_game_talk_image(void)
{
	return	game_talk.photo_id;
}

void	set_game_talk_offer_npc(SLONG npc_no)
{
	game_talk.offer_npc = npc_no;
}

SLONG	get_game_talk_offer_npc(void)
{
	return	game_talk.offer_npc;
}

void	set_game_talk_next_proc(SLONG proc_no)
{
	game_talk.opp_proc = proc_no;
}

SLONG	get_game_talk_next_proc(void)
{
	return	game_talk.opp_proc;
}

void    open_game_talk(SLONG flag)
{
    game_talk.flag = flag ? TRUE : FALSE;
}

SLONG	is_game_talk_opened(void)
{
	return	game_talk.flag == TRUE ? TRUE : FALSE;
}

void    redraw_game_talk(void *vbitmap)
{
    enum { EDGE_SIZE = 8 };
    BMP *bitmap = (BMP*)vbitmap;
    SLONG   i;
    struct
    {
        SLONG   sx, sy, xl, yl;
    } inner_pos = {126, 308, 452, 114};
    PIXEL   inner_pixel = SYSTEM_BLUE;
    PIXEL   outer_pixel = SYSTEM_BLUE;
    SLONG   inner_alpha = 50;
    SLONG   outer_alpha = 128;
    //PIXEL   inner_pixel = rgb2hi( 235, 201, 181 );
    //PIXEL   outer_pixel = rgb2hi( 240, 222, 212 );
    //SLONG   inner_alpha = 149;
    //SLONG   outer_alpha = 76;

    if( !game_talk.flag )
        return;


    //photo
    if(game_talk.photo_id >= 0)
    {
        put_box(game_talk.photo_sx,game_talk.photo_sy, game_talk.photo_xl, game_talk.photo_yl, 
            SYSTEM_YELLOW, bitmap);
        alpha_put_bar(game_talk.photo_sx,game_talk.photo_sy, game_talk.photo_xl, game_talk.photo_yl, 
            SYSTEM_BLUE, bitmap, 20);
        
        put_box(game_talk.photo_sx,game_talk.photo_sy,
            game_talk.photo_xl,game_talk.photo_yl,
            SYSTEM_GREEN,bitmap);
    }

    //text background
    {
        //program functions achieve method.
        alpha_put_bar(game_talk.win_sx, game_talk.win_sy, game_talk.win_xl, game_talk.win_yl, inner_pixel,
            bitmap, inner_alpha);
        alpha_put_bar(game_talk.win_sx-EDGE_SIZE, game_talk.win_sy-EDGE_SIZE, game_talk.win_xl+EDGE_SIZE*2, 
            EDGE_SIZE, outer_pixel, bitmap, outer_alpha);
        alpha_put_bar(game_talk.win_sx-EDGE_SIZE, game_talk.win_sy+game_talk.win_yl, game_talk.win_xl+EDGE_SIZE*2, 
            EDGE_SIZE, outer_pixel, bitmap, outer_alpha);
        alpha_put_bar(game_talk.win_sx-EDGE_SIZE, game_talk.win_sy, EDGE_SIZE, game_talk.win_yl,
            outer_pixel, bitmap, outer_alpha);
        alpha_put_bar(game_talk.win_sx+game_talk.win_xl, game_talk.win_sy, EDGE_SIZE, game_talk.win_yl,
            outer_pixel, bitmap, outer_alpha);
    }
	/*
    {
        alpha_put_bar(game_talk.win_sx, game_talk.win_sy, game_talk.win_xl, game_talk.win_yl, inner_pixel,
            bitmap, inner_alpha);
        redraw_game_talk_rim(game_talk.win_sx, game_talk.win_sy, game_talk.win_xl, game_talk.win_yl, bitmap);
    }
	*/

    // Jack, add ~F2 effect. [16:34,10/9/2002]
	set_word_color(0, SYSTEM_YELLOW);
	set_back_color(0, SYSTEM_BLACK);
    print16(0,0,(USTR*)"~C0~F2",PEST_PUT, bitmap); //yellow
    for(i=0; i<game_talk.max_text; i++)
    {
        print16(game_talk.win_sx + WIN_Y_GAP / 2, game_talk.win_sy + WIN_Y_GAP / 2 + LINE_HEIGHT * i, 
            (USTR*)game_talk.text[i], PEST_PUT, bitmap);
    }
    print16(0,0,(USTR*)"~C0~F0",PEST_PUT, bitmap);
	set_word_color(0, SYSTEM_WHITE);

    game_range.add(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, RT_TALK, IDTALK_CLOSE);
}


SLONG	handle_game_talk(UINT message, WPARAM wParam, LPARAM lParam)
{
    SLONG   mouse_x, mouse_y;
    SLONG   event_type, event_id;
	SLONG	npc_no, proc_no;

    switch(message)
    {
    case WM_LBUTTONDOWN:
		mouse_x = GET_X_LPARAM(lParam);
		mouse_y = GET_Y_LPARAM(lParam);
		event_type = event_id = 0;
		game_range.mapping(mouse_x, mouse_y, &event_type, &event_id);
		//mouse_hand.left_down.type = event_type;
		//mouse_hand.left_down.id = event_id;
		mouse_hand.point_kind = event_type;
		mouse_hand.point_no = event_id;		
		break;

    case WM_LBUTTONUP:
		mouse_x = GET_X_LPARAM(lParam);
		mouse_y = GET_Y_LPARAM(lParam);
		event_type = event_id = 0;
		game_range.mapping(mouse_x, mouse_y, &event_type, &event_id);
		//if(mouse_hand.left_down.type == event_type && mouse_hand.left_down.id == event_id)
		if(mouse_hand.point_kind == event_type && mouse_hand.point_no == event_id)		
		{
			switch(event_id)
			{
			case IDTALK_CLOSE:
				npc_no = get_game_talk_offer_npc();
				proc_no = get_game_talk_next_proc();
				client_cmd_request_npc_proc(npc_no, proc_no);
				break;
			}
			//mouse_hand.left_down.type = 0;
			//mouse_hand.left_down.id = 0;
		    mouse_hand.point_kind = 0;
		    mouse_hand.point_no = 0;
		}
        break;

    }
    return  0;
}
