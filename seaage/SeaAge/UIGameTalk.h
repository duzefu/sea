/*
**	UIGameTalk.h 
**	user interface of game talk.
**
**	Jack, 2003.1.20
*/
#pragma once



//
//DEFINES ////////////////////////////////////////////////////////////////////////////////////////////
//
#define TALK_TEXT_NUM           8		// Counts of talk text lines.
#define TALK_TEXT_LEN           64		// Length of each talk line.
#define MAX_TALK_PHOTO          100		// Counts of Npc's photo image.
//
#define	IDTALK_CLOSE			1000	// Event ID of close game talk.


//
//STRUCTS ///////////////////////////////////////////////////////////////////////////////////////////
//
typedef struct  tagGAME_TALK
{
    SLONG   flag;                       //active flag
    SLONG   offer_npc;                  //npc no who offer this talk
    SLONG   opp_proc;                   //opposite proc
    SLONG   photo_id;                   //photo id
    SLONG   proc_type;                  //proc type of this talk
    SLONG   offer_map;                  //map no who offer this talk
    //------------------------------------------------------------
    SLONG   max_text;                   //max talk text
    char	text[TALK_TEXT_NUM][TALK_TEXT_LEN];   //talk text string
    SLONG   len[TALK_TEXT_NUM][2];           //talk text len
    SLONG   photo_sx, photo_sy;         //talk photo start position
    SLONG   photo_xl, photo_yl;         //talk photo size
    SLONG   win_sx, win_sy;             //talk window start position
    SLONG   win_xl, win_yl;             //talk window size
    //------------------------------------------------------------
} GAME_TALK, *LPGAME_TALK;


//
//GLOBALS ///////////////////////////////////////////////////////////////////////////////////////////
//
extern  GAME_TALK   game_talk;

//
//FUNCTIONS //////////////////////////////////////////////////////////////////////////////////////////
//
extern	int     init_game_talk(void);
extern	void    free_game_talk(void);
extern	void    active_game_talk(int active);
//
extern	void    clear_game_talk(void);
extern	SLONG   add_game_talk_text(char *text);
extern	void    set_game_talk_image(SLONG image_id);
extern	SLONG	get_game_talk_image(void);
extern	void	set_game_talk_offer_npc(SLONG npc_no);
extern	SLONG	get_game_talk_offer_npc(void);
extern	void	set_game_talk_next_proc(SLONG proc_no);
extern	SLONG	get_game_talk_next_proc(void);
extern	void    open_game_talk(SLONG flag);
extern	SLONG	is_game_talk_opened(void);
//
extern	void    redraw_game_talk(void *vbitmap);
extern	SLONG	handle_game_talk(UINT message, WPARAM wParam, LPARAM lParam);

