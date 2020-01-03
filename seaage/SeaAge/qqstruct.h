/*
**	qqstruct.h
**
**	Structrue declaration for UIQQ
**
**	Zhang Zhaohui, 2002/11/07.
*/


#ifndef QQSTRUCT_H_
#define QQSTRUCT_H_
#include "mainfun.h"
#include "qqedit.h"
#include "qqfriend.h"
#include "qqsearch.h"
#include "NetGE_Item.h"
#include "uicombobox.h"

#define MAX_CAK_FRAME	48

/*
 * store same var for uiqq
 */
typedef struct tagUI_QQ
{
//	SLONG	input_focus;
	BOOL	is_online;			/* is player online? */
	BOOL	button_down;
	SLONG	curr_state_id;		/* max ? min		 */
	void	(*end_func)(void);	/* end function for each window*/
	DWORD	total_players;
	DWORD   face_flash;
} UI_QQ, *LPUI_QQ;

//1
typedef struct tagUI_QQFACE 
{
    CAKE_FRAME_ANI  *cfa;               //all faces ani image.
    CAKE_FRAME      *cf[MAX_CAK_FRAME];  //each face image.
} UI_QQFACE, *LPUI_QQFACE;

//2
typedef struct tagUI_QQMAIN 
{
    CAKE_FRAME_ANI  *cfa;       //menu frames image.
    CAKE_FRAME      *cf[MAX_CAK_FRAME];    //each menu frame image.
    //
    SLONG   hilight_id;         //hilight id
    SLONG   active_id;          //active id
    SLONG   function_id;        //function id
    //
    SLONG   hide_state_login;   //if is hide state login?
    SLONG   curr_list_kind;     //current list friends kind
	SLONG	next_list_kind;
	//
	SLONG	curr_move_kind;		//current move friends kind
	SLONG	curr_move_ay;		//current move item y
	//
	SLONG	list_group;
	SLONG	list_item_count;
	SLONG	next_list_count;
	SLONG	list_item_sy;
	SLONG	first_list_index;

	SLONG			popup_y;
	SLONG			item_id;
	LPUI_QQFRIEND	chat_id;



} UI_QQMAIN, *LPUI_QQMAIN;

//3
typedef struct tagUI_QQPOPUP
{
    CAKE_FRAME_ANI  *cfa;       //menu frames image.
    CAKE_FRAME      *cf[MAX_CAK_FRAME];    //each menu frame image.
    //
    SLONG   hilight_id;         //hilight id
    SLONG   active_id;          //active id
    SLONG   function_id;        //function id

	LPUI_QQFRIEND pfriend;
	SLONG	current_goup;
	
} UI_QQPOPUP, *LPUI_QQPOPUP;

//4
typedef struct tagUI_QQCALLGM
{
    CAKE_FRAME_ANI  *cfa;       //menu frames image.
    CAKE_FRAME      *cf[MAX_CAK_FRAME];    //each menu frame image.
    //
    SLONG   hilight_id;         //hilight id
    SLONG   active_id;          //active id
    SLONG   function_id;        //function id

	UI_TEXT *ptext;				//�O�s��r

} UI_QQCALLGM, *LPUI_QQCALLGM;


//5
typedef struct tagUI_QQCHAT
{
    CAKE_FRAME_ANI  *cfa;
    CAKE_FRAME      *cf[MAX_CAK_FRAME];

    SLONG   hilight_id;
    SLONG   active_id;
    SLONG   function_id;

	char	name[32];			// ��Ѧn�ͪ��W�r
	SLONG	icon_index;         // ��Ѧn�ͪ��Y������
	DWORD	sid;                // ��Ѧn�ͪ����ޭ�

	UI_TEXT *ptext;				// �s���

} UI_QQCHAT, *LPUI_QQCHAT;


//6
typedef struct tagUI_QQDETAIL
{
    CAKE_FRAME_ANI  *cfa;
    CAKE_FRAME      *cf[MAX_CAK_FRAME];

    SLONG   hilight_id;
    SLONG   active_id;
    SLONG   function_id;

	SLONG	parent_id;			// �W�@�Ӭɭ�������
	UI_QQFRIEND	  friend_info;
	LPUI_QQFRIEND pfriend;

} UI_QQDETAIL, *LPUI_QQDETAIL;


//7
typedef struct tagUI_QQFIND1
{
    CAKE_FRAME_ANI  *cfa;
    CAKE_FRAME      *cf[MAX_CAK_FRAME];
    //
    SLONG   hilight_id;
    SLONG   active_id;
    SLONG   function_id;

	SLONG	selected_id;    // 

} UI_QQFIND1, *LPUI_QQFIND1;

//8
typedef struct tagUI_QQFIND2
{
    CAKE_FRAME_ANI  *cfa;
    CAKE_FRAME      *cf[MAX_CAK_FRAME];
    //
    SLONG   hilight_id;
    SLONG   active_id;
    SLONG   function_id;

    // �j������
	UI_TEXT *pname;         // �W�r
	UI_TEXT *pnickname;     // �ʺ�
	UI_TEXT *pguild;        // ���|
	UI_TEXT *plevel;        // ����
	COMBOBOX *pcountry;     // ��a

} UI_QQFIND2, *LPUI_QQFIND2;

//9
typedef struct tagUI_QQFIND3
{
    CAKE_FRAME_ANI  *cfa;
    CAKE_FRAME      *cf[MAX_CAK_FRAME];
    //
    SLONG   hilight_id;
    SLONG   active_id;
    SLONG   function_id;

	SLONG	parent_id;          // �W�@�Ӭɭ������ޭ�
	SLONG	add_group;			// �K�[�� �ڪ��n�� �� �¦W��
    SLONG	search_index;       // �j���ɪ����ޭ�
	SLONG	selected_id;        // ��ܬO�����ޭ�
	LPUI_QQSEARCH_FILTER filter;    // �j���L�o
	BOOL	in_search;          // �O�_���b�j��

} UI_QQFIND3, *LPUI_QQFIND3;

//10
typedef struct tagUI_QQITEM
{
    CAKE_FRAME_ANI  *cfa;
    CAKE_FRAME      *cf[MAX_CAK_FRAME];
    //
    SLONG   hilight_id;
    SLONG   active_id;
    SLONG   function_id;

	SLONG	selected_index;		// �O���襤�����~����
	SLONG	send_money;			// �ǰe���~�һݿ���
	BOOL	wait_send;			// ���ݶǰe�����лx

} UI_QQITEM, *LPUI_QQITEM;

//11
typedef struct tagUI_QQLOG
{
    CAKE_FRAME_ANI  *cfa;
    CAKE_FRAME      *cf[MAX_CAK_FRAME];
    //
    SLONG   hilight_id;
    SLONG   active_id;
    SLONG   function_id;
    
    UI_TEXT *ptext;             // ��ܤ�r
    DWORD   index;              // ��e��ܪ���������
    DWORD   count;              // ��e��ܪ�������

} UI_QQLOG, *LPUI_QQLOG;

//12
typedef struct tagUI_QQSET
{
    CAKE_FRAME_ANI  *cfa;
    CAKE_FRAME      *cf[MAX_CAK_FRAME];
    //
    SLONG   hilight_id;
    SLONG   active_id;
    SLONG   function_id;
	
	DWORD	draw_settings;      // �]�w��

} UI_QQSET, *LPUI_QQSET;


//13
typedef struct tagUI_QQVERIFY
{
    CAKE_FRAME_ANI  *cfa;
    CAKE_FRAME      *cf[MAX_CAK_FRAME];
    //
    SLONG   hilight_id;
    SLONG   active_id;
    SLONG   function_id;

	UI_TEXT *ptext;             // ���Ҧr�ſ�J
	LPUI_QQFRIEND pfriend;      // �\���Ҫ����a
	SLONG	send_ok;            // �o�e���\

} UI_QQVERIFY, *LPUI_QQVERIFY;

//14
typedef struct tagUI_QQLIST
{
    CAKE_FRAME_ANI  *cfa;
    CAKE_FRAME      *cf[MAX_CAK_FRAME];
    //
    SLONG   hilight_id;
    SLONG   active_id;
    SLONG   function_id;

	SLONG	index_start;        // �Ĥ@�Ӧn�ͪ�����
	SLONG	group;              // ���Ӳժ��n��
	
} UI_QQLIST, *LPUI_QQLIST;


typedef struct tagUI_QQHIS
{
	CAKE_FRAME_ANI	*cfa;
	CAKE_FRAME		*cf[MAX_CAK_FRAME];

	SLONG			hilight_id;
	SLONG			active_id;
	SLONG			function_id;

	SLONG			index;
} UI_QQHIS, *LPUI_QQHIS;

// GLOBALS /////////////////////////////////////////////////////////////////////////////////////////////////////////
extern  UI_QQFACE       ui_qqface;
extern  UI_QQMAIN       ui_qqmain;
extern  UI_QQPOPUP      ui_qqpopup;
extern  UI_QQCALLGM     ui_qqcallgm;
extern  UI_QQCHAT       ui_qqchat;
extern	UI_QQDETAIL		ui_qqdetail;
extern	UI_QQFIND1		ui_qqfind1;
extern	UI_QQFIND2		ui_qqfind2;
extern	UI_QQFIND3		ui_qqfind3;
extern	UI_QQITEM		ui_qqitem;
extern	UI_QQLOG		ui_qqlog;
extern	UI_QQSET		ui_qqset;
extern	UI_QQVERIFY		ui_qqverify;
extern	UI_QQLIST		ui_qqlist;
extern	UI_QQHIS		ui_qqhis;

// FUNCTIONS ///////////////////////////////////////////////////////////////////////////////////////////////////////


#endif /* QQSTRUCT_H_ */