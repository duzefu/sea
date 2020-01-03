/*
**	UIQuitGame.h 
**	ui of quit game.
**
**	Jack, 2003.2.20.
*/
#pragma once

//
// DEFINES //////////////////////////////////////////////////////////////////////////////////////////////////
//
typedef	enum	UI_QUITGAME_ENUMS
{	UIQUITGAME_FRAME_BKGND			=	0,
UIQUITGAME_FRAME_RETURN_GAME		=	1,
UIQUITGAME_FRAME_VIDEO_OPTIONS		=	4,
UIQUITGAME_FRAME_AUDIO_OPTIONS		=	7,
UIQUITGAME_FRAME_MYSELF_SETTINGS	=	10,
UIQUITGAME_FRAME_QUIT_GAME			=	13,
//
UIQUITGAME_EVENT					=	4000,
UIQUITGAME_ID_BKGND					=	0,
UIQUITGAME_ID_RETURN_GAME			=	1,
UIQUITGAME_ID_VIDEO_OPTIONS			=	2,
UIQUITGAME_ID_AUDIO_OPTIONS			=	3,
UIQUITGAME_ID_MYSELF_SETTINGS		=	4,
UIQUITGAME_ID_QUIT_GAME				=	5,
//	
} UI_QUITGAME_ENUMS;


//
// STRUCTURES ///////////////////////////////////////////////////////////////////////////////////////////////
//
typedef	struct tagQUITGAME_DATA 
{
    CAKE_FRAME_ANI  *cfa;		//frame ani pointer.
    CAKE_FRAME      *cf[32];	//image pointer of each frame.

	SLONG	hilight_id;			//
	SLONG	active_id;			//

	SLONG	is_opened;			//

} QUITGAME_DATA, *LPQUITGAME_DATA;

//
// GLOBALS //////////////////////////////////////////////////////////////////////////////////////////////////
//
extern	QUITGAME_DATA	quitgame_data;

//
// FUNCTIONS ////////////////////////////////////////////////////////////////////////////////////////////////
//
int		init_ui_quitgame(void);
void	active_ui_quitgame(int active);
void	free_ui_quitgame(void);
//
void	refresh_ui_quitgame(void);
void	redraw_ui_quitgame(SLONG sx, SLONG sy, void *vbitmap);
SLONG	handle_ui_quitgame(UINT message, WPARAM wParam, LPARAM lParam);
//
void	open_ui_quitgame(SLONG flag);
SLONG	is_ui_quitgame_opened(void);

// Zhang Zhaohui 2003.5.29
VOID    ui_quitgame_clear( VOID );
