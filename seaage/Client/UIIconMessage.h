/*
**	UIIconMessage.h 
**	icon control message functions header.
**
**	Jack, 2003.3.18.
**
**  ZhangZhaohui, 2003.3.26
**  ------遊戲中彈出的消息文字, 有用戶的交互動作
** 
*/
#pragma once

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//readme:
//說明:
// 遊戲中, 當收到某些網路消息時, 會彈出一個前面帶有ICON的文字消息行,
// 該消息行顯示對應的遊戲消息; 某些情況下, 可以通過滑鼠點擊該ICON來
// 作對該消息的回饋控制, 比如同意或者不同意等.
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

//
// DEFINES //////////////////////////////////////////////////////////////////////////////////////////////////
//

// 
// CONST ///////////////////////////////////////////////////////////////////////////////////////////////////
//
enum ICONMSG_BASE
{
	IM_HINT		= 0,
	IM_YESNO	= 1,
	IM_MAX		= 8,
	IM_MSGLEN	= 80,
	IM_FRAMES	= 4,
	IM_EVENT	= 25000,
	IM_IMG_YES	= 0,			// "是"按鈕在圖檔中的位置
	IM_IMG_NO	= 1,			// "否"按鈕在圖檔中的位置
	IM_IMG_INFO = 2,			// "信息"按鈕在圖檔中的位置
	IM_MAX_PARA = 4,			// 最多四個參數
};

enum ICONMSG_ACTION
{
	IMA_YES		= 1,
	IMA_NO		= 2,
};

enum ICONMSG_STATE
{
	IMS_FLASH		= 0,
	IMS_NORMAL		= 1,
	IMS_DISAPPEAR	= 2,
};

enum ICONMSG_LEFT
{
	IMT_FLASH		= 1500,		// 1.5 秒
	IMT_NORMAL		= 10000,	// 10 秒
};
//
// STRUCTS //////////////////////////////////////////////////////////////////////////////////////////////////
//
/*
//消息的ICON圖標影像資料
typedef	struct tagICONMSG_IMAGE
{
	CAKE_FRAME_ANI	*cfa;	// images
} ICONMSG_IMAGE, *LPICONMSG_IMAGE;
*/

//
//消息參數
typedef	struct tagICONMSG_PARA 
{
	ULONG	flags;				// 消息標誌
//	ULONG	life;				// 消息生存時間
	SLONG	num[IM_MAX_PARA];				// 消息整數參數 1 ~ 3
	CHAR	str[IM_MAX_PARA][IM_MSGLEN];	// 消息字串參數 1 ~ 3
} ICONMSG_PARA;
//
// 消息內容
typedef struct tagICONMSG
{
	union
	{
		SLONG		alpha;				// 透明度
		DWORD		flash;				// 控制閃爍
	};
	DWORD		state;				// 消息的當前狀態
	DWORD		start_time;			// 當前狀態的開始時間
	CHAR		msg[IM_MSGLEN];		// 消息文字
} ICONMSG;
//
//消息鏈表
typedef	struct tagICONMSG_NODE	ICONMSG_NODE; 
struct tagICONMSG_NODE
{
	INT				index;			// 消息的索引
	DWORD			event;			// 用戶設定的事件
	DWORD			type;			// 消息的標誌
	ICONMSG			content;		// 消息的內容
	ICONMSG_PARA	para;			// 消息的參數
};

//
//消息定義文字
typedef	struct  tagMSG_DEFINE
{
	DWORD   para_type;			// 0-無參數,0X1-字符串,0X2-整型
	CHAR	text[IM_MSGLEN];
} MSG_DEFINE;


//
// GLOBALS //////////////////////////////////////////////////////////////////////////////////////////////////
//

//
// FUNCTIONS ////////////////////////////////////////////////////////////////////////////////////////////////
//

INT		init_iconmsg( VOID );
VOID	active_iconmsg( INT active );
VOID	free_iconmsg( VOID );

INT		add_iconmsg( DWORD id, DWORD type, ICONMSG_PARA* para, DWORD event );

VOID	refresh_iconmsg( VOID );
LONG	handle_iconmsg( UINT msg, WPARAM wparam, LPARAM lparam );
VOID	redraw_iconmsg( BMP *bitmap );




