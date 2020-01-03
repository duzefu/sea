/*
**	UIGameChoice.cpp 
**	user interface of game choice.
**
**	Jack, 2003.1.20
*/
#include "MainFun.h"
#include "CRange.h"
#include "MouseHand.h"
#include "CmdEvent.h"
#include "UIGameChoice.h"


/************************************************************************************************************/
/* DEFINES & STRUCTURES                                                                                     */
/************************************************************************************************************/
typedef	enum    CHOICE_LOCAL_ENUMS
{   MIN_OPTIONS =   1,  //5,
REMAIN_HEIGHT   =   20,
OPTION_HEIGHT   =   20,
TITLE_HEIGHT    =   24,
WIN_Y_GAP       =   16,
EDGE_SIZE       =   8,
OPTION_X_GAP    =   2,
OPTION_Y_GAP    =   2,
//
WIN_XL          =   452,
WIN_YL          =   OPTION_HEIGHT * MIN_OPTIONS + WIN_Y_GAP + REMAIN_HEIGHT,
WIN_SX          =   126,
WIN_SY          =   424 - WIN_YL,   //308,
//
TITLE_XL        =   WIN_XL,
TITLE_YL        =   TITLE_HEIGHT,
TITLE_SX        =   WIN_SX,
TITLE_SY        =   WIN_SY - EDGE_SIZE * 2 - TITLE_HEIGHT,
OPTION_SX       =   WIN_SX,
OPTION_SY       =   WIN_SY + WIN_Y_GAP / 2,
OPTION_XL       =   WIN_XL,
OPTION_YL       =   OPTION_HEIGHT,
} CHOICE_LOCAL_ENUMS;


/************************************************************************************************************/
/* GLOBALS                                                                                                  */
/************************************************************************************************************/
GAME_CHOICE game_choice;


/************************************************************************************************************/
/* GAME CHOICE FUNCTIONS                                                                                    */
/************************************************************************************************************/
int     init_game_choice(void)
{
	clear_game_choice();
	return	0;
}

void    active_game_choice(int active)
{
	// Do nothing here.
}

void    free_game_choice(void)
{
    game_choice.offer_npc = -1;
    game_choice.max_option = 0;
	game_choice.active_option = 0;
}

void    clear_game_choice(void)
{
    SLONG   i;

    game_choice.flag = FALSE;
    game_choice.offer_npc = -1;
    game_choice.offer_map = -1;

    game_choice.max_option = 0;
    memset(game_choice.title, 0, CHOICE_TITLE_LEN);
    for(i=0; i<CHOICE_OPTION_NUM; i++)
    {
        memset(game_choice.option[i], 0, CHOICE_OPTION_LEN);
    }
    game_choice.win_sx = WIN_SX;
    game_choice.win_sy = WIN_SY;
    game_choice.win_xl = WIN_XL;
    game_choice.win_yl = WIN_YL;
    game_choice.title_sx = TITLE_SX;
    game_choice.title_sy = TITLE_SY;
    game_choice.title_xl = TITLE_XL;
    game_choice.title_yl = TITLE_YL;
    game_choice.option_sx = OPTION_SX;
    game_choice.option_sy = OPTION_SY;
    game_choice.option_xl = OPTION_XL;
    game_choice.option_yl = OPTION_YL;

	game_choice.active_option = 0;
}


void    set_game_choice_title(char *title)
{
    SLONG   i=0;

    memset(game_choice.title, 0, CHOICE_TITLE_LEN);
    do {
        game_choice.title[i] = title[i];
    } while(i++ < CHOICE_TITLE_LEN);
}

SLONG   add_game_choice_option(SLONG opp_proc, char *option)
{
    SLONG   index = -1;
    SLONG   i=0;
    SLONG   add_options;

    if(game_choice.max_option < CHOICE_OPTION_NUM)
    {
        index = game_choice.max_option;
        game_choice.opp_proc[index] = opp_proc;

        memset(game_choice.option[index], 0, CHOICE_OPTION_LEN);
        do {
            game_choice.option[index][i] = option[i];
        } while(i++ < CHOICE_OPTION_LEN);

        game_choice.max_option++;

        if(game_choice.max_option > MIN_OPTIONS)
        {
            add_options = game_choice.max_option - MIN_OPTIONS;

            game_choice.win_sy = WIN_SY - add_options * OPTION_HEIGHT;
            game_choice.win_yl = WIN_YL + add_options * OPTION_HEIGHT;
            game_choice.title_sy = game_choice.win_sy - EDGE_SIZE * 2 - TITLE_HEIGHT;
            game_choice.option_sy = game_choice.win_sy + WIN_Y_GAP / 2;
        }
    }
    return index;
}

void    open_game_choice(SLONG flag)
{
    game_choice.flag = flag ? TRUE : FALSE;
}

SLONG	is_game_choice_opened(void)
{
	return	game_choice.flag == TRUE ? TRUE : FALSE;
}

void	set_game_choice_offer_npc(SLONG npc_no)
{
	game_choice.offer_npc = npc_no;
}

SLONG	get_game_choice_offer_npc(void)
{
	return	game_choice.offer_npc;
}

SLONG	get_game_choice_next_proc(SLONG option_index)
{
	return	game_choice.opp_proc[option_index];
}


void    redraw_game_choice(void *vbitmap)
{
    BMP *bitmap = (BMP*)vbitmap;
    SLONG   i;
    struct
    {
        SLONG   sx, sy, xl, yl;
    } inner_pos = {126, 308, 452, 114};
    PIXEL   inner_pixel = SYSTEM_BLUE;  //rgb2hi( 235, 201, 181 );
    PIXEL   outer_pixel = SYSTEM_BLUE;  //rgb2hi( 240, 222, 212 );
    SLONG   inner_alpha = 50;   //149;
    SLONG   outer_alpha = 128;  //76
    SLONG   mx, my;


    if(! game_choice.flag) return;

	// Jack, TODO [1/20/2003]
	// Temperary use get_mouse_position() to get mouse position, later we should use other function to 
	// fetch mouse position.
    get_mouse_position( &mx, &my);

    //background --------------------------------------------------
	/*
    {
        SLONG   background_sx, background_sy, background_xl, background_yl;
        SLONG   margin_sx, margin_sy, margin_xl, margin_yl;

        background_sx = game_choice.title_sx;
        background_sy = game_choice.title_sy;
        background_xl = game_choice.win_sx + game_choice.win_xl - game_choice.title_sx;
        background_yl = game_choice.win_sy + game_choice.win_yl - game_choice.title_sy;

        margin_sx = background_sx;
        margin_sy = background_sy + game_choice.title_yl + EDGE_SIZE * 2;
        margin_xl = background_xl;
        margin_yl = 1;

        alpha_put_bar(background_sx, background_sy, background_xl, background_yl, inner_pixel,
            bitmap, inner_alpha);
        redraw_game_talk_rim(background_sx, background_sy, background_xl, background_yl, bitmap);

        redraw_game_talk_up_margin(margin_sx, margin_sy, margin_xl, margin_yl, bitmap);
    }
	*/
    game_range.add(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, RT_CHOICE, IDCHOICE_CLOSE );

    //title ----------------------------------------------------------
    if(game_choice.title[0])
    {
        //title background -----------------
		///*
        {
            alpha_put_bar(game_choice.title_sx, game_choice.title_sy, game_choice.title_xl, game_choice.title_yl, inner_pixel,
                bitmap, inner_alpha);
            alpha_put_bar(game_choice.title_sx-EDGE_SIZE, game_choice.title_sy-EDGE_SIZE, game_choice.title_xl+EDGE_SIZE*2, 
                EDGE_SIZE, outer_pixel, bitmap, outer_alpha);
            alpha_put_bar(game_choice.title_sx-EDGE_SIZE, game_choice.title_sy+game_choice.title_yl, game_choice.title_xl+EDGE_SIZE*2, 
                EDGE_SIZE, outer_pixel, bitmap, outer_alpha);
            alpha_put_bar(game_choice.title_sx-EDGE_SIZE, game_choice.title_sy, EDGE_SIZE, game_choice.title_yl,
                outer_pixel, bitmap, outer_alpha);
            alpha_put_bar(game_choice.title_sx+game_choice.title_xl, game_choice.title_sy, EDGE_SIZE, game_choice.title_yl,
                outer_pixel, bitmap, outer_alpha);
        }
		///*/

        //title text ------------------------
        print16(game_choice.title_sx+4, game_choice.title_sy+4, (USTR*)game_choice.title, PEST_PUT, bitmap);
    }

    //option background
	///*
    {
        alpha_put_bar(game_choice.win_sx, game_choice.win_sy, game_choice.win_xl, game_choice.win_yl, inner_pixel,
            bitmap, inner_alpha);
        alpha_put_bar(game_choice.win_sx-EDGE_SIZE, game_choice.win_sy-EDGE_SIZE, game_choice.win_xl+EDGE_SIZE*2, 
            EDGE_SIZE, outer_pixel, bitmap, outer_alpha);
        alpha_put_bar(game_choice.win_sx-EDGE_SIZE, game_choice.win_sy+game_choice.win_yl, game_choice.win_xl+EDGE_SIZE*2, 
            EDGE_SIZE, outer_pixel, bitmap, outer_alpha);
        alpha_put_bar(game_choice.win_sx-EDGE_SIZE, game_choice.win_sy, EDGE_SIZE, game_choice.win_yl,
            outer_pixel, bitmap, outer_alpha);
        alpha_put_bar(game_choice.win_sx+game_choice.win_xl, game_choice.win_sy, EDGE_SIZE, game_choice.win_yl,
            outer_pixel, bitmap, outer_alpha);
    }
	//*/

    //options -----------------------------------------------------------------------------------
    // Jack, add ~F2 effect. [16:34,10/9/2002]
	set_word_color(0, SYSTEM_YELLOW);
	set_back_color(0, SYSTEM_BLACK);
    print16(0,0,(USTR*)"~C0~F2",PEST_PUT, bitmap); //yellow


    for(i=0; i<game_choice.max_option; i++)
    {
        //check if the option is active
        if( mx > game_choice.option_sx + OPTION_X_GAP 
            && mx < game_choice.option_xl + game_choice.option_sx + OPTION_X_GAP * 2
            && my > game_choice.option_sy + OPTION_Y_GAP + i * OPTION_HEIGHT
            && my < game_choice.option_sy + OPTION_Y_GAP + (i+1) * OPTION_HEIGHT )
		//if(game_choice.active_option == i)
        {
            alpha_put_bar(game_choice.option_sx, game_choice.option_sy+i*20, game_choice.option_xl, game_choice.option_yl, 
                SYSTEM_RED, bitmap, 100);
        }
        print16(game_choice.option_sx+2, game_choice.option_sy+2+i*20, (USTR*)game_choice.option[i], PEST_PUT, bitmap);

        game_range.add( game_choice.option_sx, game_choice.option_sy+i*20, game_choice.option_xl, game_choice.option_yl,
            RT_CHOICE, IDCHOICE_OPTION_0 + i);
    }
    print16(0,0,(USTR*)"~C0~F0",PEST_PUT, bitmap); //restore to white
	set_word_color(0, SYSTEM_WHITE);
}


SLONG	handle_game_choice(UINT message, WPARAM wParam, LPARAM lParam)
{
    SLONG   mouse_x, mouse_y;
    SLONG   event_type, event_id;
	SLONG	npc_no, proc_no;
	SLONG	max_option, choose_option;

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
			case IDCHOICE_CLOSE:
				// Don't response this event.
				break;

			default:
				max_option = game_choice.max_option;
                if(event_id >= IDCHOICE_OPTION_0 && event_id < IDCHOICE_OPTION_0 + max_option)
				{
                    choose_option = event_id - IDCHOICE_OPTION_0;
					npc_no = get_game_choice_offer_npc();
					proc_no = get_game_choice_next_proc(choose_option);
					client_cmd_request_npc_proc(npc_no, proc_no);
				}
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

