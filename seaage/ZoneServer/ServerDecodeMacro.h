/*
**	ServerDecodeMacro.h 
**	decode macro functions.
**
**	Jack, 2002.12.17
*/
#ifndef	_SERVERDECODEMACRO_H_
#define	_SERVERDECODEMACRO_H_


// DEFINES //////////////////////////////////////////////////////////////////////////////////////////////////
//
#define SYS_MACRO_PROC          0   //系統劇本事件
#define MAP_MACRO_PROC          1   //地圖劇本事件
#define NPC_MACRO_PROC          2   //NPC 劇本事件


// STRUCTURES ///////////////////////////////////////////////////////////////////////////////////////////////
//
typedef struct  tagMAC_PIPE
{
    SLONG   proc_type;		//劇本事件類型
    SLONG   active_npc;		//激發劇本事件的NPC的編號
	SLONG	active_map;		//激發劇本事件的地圖編號
	SLONG	script_npc;		//帶有劇本的NPC的編號
    USTR    debug_rec[1024];//DEBUG顯示用
} MAC_PIPE, *LPMAC_PIPE;


// GLOBALS //////////////////////////////////////////////////////////////////////////////////////////////////
//
extern  MAC_PIPE    mac_pipe;

// FUNCTIONS ////////////////////////////////////////////////////////////////////////////////////////////////
//
extern	void    replace_variable_string(USTR *in, USTR *out, SLONG player_index);
extern  void    reset_mac_pipe(void);
extern	void	set_mac_pipe_with_npc_proc(SLONG active_npc, SLONG script_npc);
extern	SLONG   pos_decode_script(UCHR code);


#endif//_SERVERDECODEMACRO_H_
