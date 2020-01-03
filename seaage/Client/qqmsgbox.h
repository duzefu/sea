/*
 * qqmsgobx.h
 * functions for qq friend list
 * Zhang Zhaohui
 * 2002.10.9
 */

#ifndef UIMSGBOX_H_
#define UIMSGBOX_H_
#include "mainfun.h"
#include "ClientMain.h"


///////////////    DEFINE ////////////////////////////////
#define UIMB_TYPE_MASK          0x000000ffL
#define UIMB_OWN_MOUSE          0x00000100L
#define UIMB_OWN_KEY            0x00000200L

#define UIMB_OK                 0x00000000L
#define UIMB_OKCANCEL           0x00000001L
#define UIMB_MESSAGE            0x00000002L
#define UIMB_YESNOCANCEL        0x00000003L
#define UIMB_YESNO              0x00000004L
#define UIMB_RETRYCANCEL        0x00000005L

#define UIMB_ICONWARNING        0x00000030L
#define UIMB_ICONERROR          0x00000010L
#define UIMB_ICONQUESTION       0x00000020L
#define UIMB_ICONINFORMATION    0x00000040L

#define    GET_MSGBOX_TYPE(flag)    ((flag) & UIMB_TYPE_MASK)


#define MB_MAX_CHAR             1048
#define MB_MAX_TITLE            64

#define MB_MAX_PARAM_TEXT       32

#define MB_CENTER_X             (-1)
#define MB_CENTER_Y             (-1)

///////////////  ENUM  ////////////////////////////////
typedef enum tagMSG_BOX
{
    MSG_BOX_EVENT               = 30000,

    MSG_BOX_ID_BKGND            = 100,
    MSG_BOX_ID_OK               = 1,
    MSG_BOX_ID_CANCEL           = 2,
    MSG_BOX_ID_RETRY            = 4,
    MSG_BOX_ID_YES              = 6,
    MSG_BOX_ID_NO               = 7,
    MSG_BOX_ID_TEXT             = 8,

    MSG_BOX_FRAME_OK            = 0,
    MSG_BOX_FRAME_CANCEL        = 3,
    MSG_BOX_FRAME_RETRY         = 6,
    MSG_BOX_FRAME_YES           = 9,
    MSG_BOX_FRAME_NO            = 12
}MSG_BOX;

///////////////    STRUCT ////////////////////////////////
/*
 * Type for message box callback process
 *
 */
typedef void (*FNMBCB)( DWORD param, SLONG result );

/*
 *    Structure for stores parameters
 */
typedef struct tagUIMB_PARAM
{
    SLONG        event_id;
    DWORD        param1;
    DWORD        param2;
    DWORD        param3;
    DWORD        param4;
    char        str[MB_MAX_PARAM_TEXT];
} UIMB_PARAM, *LPUIMB_PARAM;
/*
 * Structure for stores message box infomation
 *
 */
typedef struct tagUIMSGBOX
{
    char            title_info[MB_MAX_TITLE];
    char            text_info[MB_MAX_CHAR];
    FNMBCB            pfunc;
    DWORD            msgbox_type;
    DWORD            disp_time;
    DWORD            font_size;            //default is TE_FONT_SIZE_12
    UIMB_PARAM        param;
}UIMSGBOX, *PUIMSGBOX, *LPUIMSGBOX;


/*
 *    Structure for stores message box position and start time
 *
 */
typedef struct tagUIMSGBOX_EX
{
    DWORD            start_time;    
    DWORD            x;
    DWORD            y;
    DWORD            xl;
    DWORD            yl;
    DWORD            text_x;
    DWORD            text_y;
    DWORD            text_h;
    DWORD            text_w;
}UIMSGBOX_EX, *PUIMSGBOX_EX, *LPUIMSGBOX_EX;


/*
 * Structure for stores message box list
 *
 */
typedef struct tagUIMB_LIST UIMB_LIST, *PUIMB_LIST, *LPUIMB_LIST;
struct tagUIMB_LIST
{
    UIMSGBOX        list;
    UIMSGBOX_EX        list_ex;
    LPUIMB_LIST        p_next;
};

/*
 * Structure for stores message box list header
 *
 */
typedef struct tagUIMB_LIST_HEADER
{
    LPUIMB_LIST    p_data;
    DWORD        count;
}UIMB_LIST_HEADER, *PUIMB_LIST_HEADER, *LPUIMB_LIST_HEADER;

/*
 *    Structure for stores handle message
 *
 */
typedef struct tagUIMB_DATA
{
    SLONG        hilight_id;
    SLONG        active_id;
}UIMB_DATA, *PUIMB_DATA, *LPUIMB_DATA;

///////////////    FUNCTION /////////////////////////////////

int        init_ui_msgbox(void);
void    active_ui_msgbox(int active);
void    free_ui_msgbox(void);

void    refresh_ui_msgbox(void);
void    redraw_ui_msgbox(BMP *bitmap);
SLONG    handle_ui_msgbox(UINT message, WPARAM wParam, LPARAM lParam);

/*
 *    add a messsage box to the box list, sx and sy is start position of 
 *        the box left-top. if sx or/and sy be set to less zero, the box
 *        will be put in the center of x or/and the center of y of screen.
 *        use MB_CENTER_X or MB_CENTER_Y
 */
SLONG    msg_box(SLONG sx, SLONG sy, LPUIMSGBOX pmsgbox);

/*
 *    clean all message box from box list    
 */
void    clean_msg_box( void );

LPUIMSGBOX    new_msgbox(void);
void        del_msgbox(LPUIMSGBOX p);
#endif /* UIMSGBOX_H_ */
