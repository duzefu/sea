/*
**  NetGE_Script.H
**  script system functions header.
**
**  Jack,2001.2.15.
**      Created.
**
**  Jack,2001.5.17.
**      Added MAC_PIPE for global data exchange.
**
**	Jack, 2003.1.19.
**		Added to SeaAge common library.
**
*/
#pragma once


#define MAX_VAR             2048		// count of macro system variables
#define SCRIPT_PATH         "script"	// directory of script files

//
// system script command ================================
//
#define CMD_PROC            0x00
#define CMD_ENDPROC         0x01
#define CMD_IF              0x02
#define CMD_ELSE            0x03
#define CMD_ELSEIF          0x04
#define CMD_ENDIF           0x05
#define CMD_WHILE           0x06
#define CMD_BREAK           0x07
#define CMD_ENDWHILE        0x08
#define CMD_SWITCH          0x09
#define CMD_CASE            0x0a
#define CMD_ENDCASE         0x0b
#define CMD_ENDSWITCH       0x0c
#define CMD_GOTO            0x0d
#define CMD_CALL            0x0e
#define CMD_RETURN          0x0f
#define CMD_EXEC            0x10
#define CMD_VAR             0x11
#define CMD_ADD             0x12
#define CMD_SUB             0x13
#define CMD_MUL             0x14
#define CMD_DEV             0x15
#define CMD_RAND            0x16
#define CMD_EXIT            0x17


typedef struct  tagMAC_INFO
{
    USTR    filename[80];       // mac filename
    ULONG   code_size;          // mac code size
    ULONG   code_index;         // mac code index
    ULONG   max_var;            // max mac variables(=MAX_VAR)
    SLONG   variable[1];        // mac variable list
} MAC_INFO, *LPMAC_INFO;


typedef struct  tagMAC_HEAD
{
    ULONG   copyright;          // '3SS'+0x1a
    ULONG   id;                 // "MAC "
    ULONG   version;            // 0x00050000
    ULONG   head_size;          // file head size
    
    ULONG   data_size;          // total data size
    ULONG   key_check;          // check key
    ULONG   max_proc;           // max proc
    SLONG   proc_address[1];    // proc address list
} MAC_HEAD, *LPMAC_HEAD;


typedef SLONG   (* SCRIPT_DECODE_FUNC)(UCHR code);
typedef void    (* SCRIPT_DEBUG_FUNC)(USTR *info);
typedef void    (* SCRIPT_INSET_FUNC)(void);


extern  int     init_script(void);
extern  void    free_script(void);
extern  void    active_script(int active);
extern  void    reset_script(void);

extern  SLONG   load_script(USTR *filename);
extern  SLONG   reload_script(void);
extern  SLONG   process_script(SLONG proc_no);

extern  void    set_script_decode_func( SCRIPT_DECODE_FUNC func);
extern  void    set_script_debug_func( SCRIPT_DEBUG_FUNC func);
extern  void    set_script_inset_func( SCRIPT_INSET_FUNC func);

extern  SLONG   get_script_info_size(void);
extern  SLONG   get_script_head_size(void);
extern  USTR *  export_script_filename(USTR *buffer);
extern  SLONG   export_script_info(MAC_INFO *mi);
extern  SLONG   inport_script_info(MAC_INFO *mi);

extern  SLONG   get_script_number(void);
extern  USTR *  get_script_string(void);
extern  UCHR    get_script_char(void);
extern  SLONG   get_script_variable(SLONG index);
extern  void    set_script_variable(SLONG index,SLONG value);

