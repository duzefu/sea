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
#define SYS_MACRO_PROC          0   //�t�μ@���ƥ�
#define MAP_MACRO_PROC          1   //�a�ϼ@���ƥ�
#define NPC_MACRO_PROC          2   //NPC �@���ƥ�


// STRUCTURES ///////////////////////////////////////////////////////////////////////////////////////////////
//
typedef struct  tagMAC_PIPE
{
    SLONG   proc_type;		//�@���ƥ�����
    SLONG   active_npc;		//�E�o�@���ƥ�NPC���s��
	SLONG	active_map;		//�E�o�@���ƥ󪺦a�Ͻs��
	SLONG	script_npc;		//�a���@����NPC���s��
    USTR    debug_rec[1024];//DEBUG��ܥ�
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
