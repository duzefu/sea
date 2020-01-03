/*
**	UIGameChoice.h 
**	user interface of game choice.
**
**	Jack, 2003.1.20
*/
#pragma once

//
// DEFINES //////////////////////////////////////////////////////////////////////////////////////////////////////////
//
#define CHOICE_OPTION_NUM		8		// Counts of choice options.
#define CHOICE_OPTION_LEN		64		// Length of each choice option line.
#define CHOICE_TITLE_LEN		64		// Length of choice title.
//
#define	IDCHOICE_OPTION_0       1		// Event ID of choice option
#define	IDCHOICE_CLOSE			1000	// Event ID of close choice interface.


//
// STRUCTS //////////////////////////////////////////////////////////////////////////////////////////////////////////
//
typedef struct  tagGAME_CHOICE
{
    SLONG   flag;       //active flag
    SLONG   proc_type;  //proc type
    SLONG   offer_npc;  //npc no who offer this choice to player
    SLONG   offer_map;  //map no who offer this choice
    //-------------------------------------------------
    SLONG   max_option;                     //max offer option number
    USTR    title[CHOICE_TITLE_LEN];                //choice title
    USTR    option[CHOICE_OPTION_NUM][CHOICE_OPTION_LEN];   //choice options
    SLONG   opp_proc[CHOICE_OPTION_NUM];            //opposite proc
    //-------------------------------------------------
    SLONG   title_sx, title_sy;             //title start position
    SLONG   title_xl, title_yl;             //title range
    SLONG   option_sx, option_sy;           //option start position
    SLONG   option_xl, option_yl;           //option range
    SLONG   win_sx, win_sy;                 //background window position
    SLONG   win_xl, win_yl;                 //background window range
    //-------------------------------------------------
	SLONG	active_option;
    //-------------------------------------------------
} GAME_CHOICE, *LPGAME_CHOICE;


//
// EXTERNS //////////////////////////////////////////////////////////////////////////////////////////////////////////
//
extern  GAME_CHOICE game_choice;


//
// FUNCTIONS ////////////////////////////////////////////////////////////////////////////////////////////////////////
//
extern	int     init_game_choice(void);
extern	void    active_game_choice(int active);
extern	void    free_game_choice(void);
//
extern	void    clear_game_choice(void);
extern	void    set_game_choice_title(char *title);
extern	SLONG   add_game_choice_option(SLONG opp_proc, char *option);
extern	void    open_game_choice(SLONG flag);
extern	SLONG	is_game_choice_opened(void);
extern	void	set_game_choice_offer_npc(SLONG npc_no);
extern	SLONG	get_game_choice_offer_npc(void);
extern	SLONG	get_game_choice_next_proc(SLONG option_index);
//
extern	void    redraw_game_choice(void *vbitmap);
extern	SLONG	handle_game_choice(UINT message, WPARAM wParam, LPARAM lParam);

