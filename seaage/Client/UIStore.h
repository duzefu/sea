/*
**  UISTORE.h
**  Store process functions header.
**
**  Stephen, 2003/3/12
**	Jack, 2003.2.25.
*/
#pragma once


//
// DEFINES //////////////////////////////////////////////////////////////////////////////////////////////////
//
#define UISTORE_DISABLE				0
#define UISTORE_ENABLE				1


typedef	enum	STORE_TYPE
{
	ITEM_STORE			=	0,	// 商店
	BANK_STORE			=	1,	// 銀行
	SAVEBOX_STORE		=   2,	// 儲物箱
	STRONGBOX_STORE     =   3,	// 保險箱
} STORE_TYPE;


typedef	enum	UISTORE_ENUMS
{	UISTORE_FRAME_BKGND				= 0,				// 介面底圖
UISTORE_FRAME_STORE_MARK			= 1,				// 商店文字
UISTORE_FRAME_BANK_MARK				= 2,				// 銀行文字
UISTORE_FRAME_STOREBOX_MARK			= 3,				// 儲物箱文字
UISTORE_FRAME_STRONGBOX_MARK		= 4,				// 保險箱文字
UISTORE_FRAME_GOLD_BKGND			= 5,				// 金錢底圖
UISTORE_FRAME_PAGEUP				= 6,				// 上一頁
UISTORE_FRAME_PAGEDOWN				= 9,				// 下一頁
UISTORE_FRAME_CLOSE                 = 12,				// 關閉按鈕
UISTORE_FRAME_SAVE					= 14,
UISTORE_FRAME_LOAD					= 15,
//
UISTORE_SHOP_0_SX					= 32,				// 
UISTORE_SHOP_0_SY					= 162,
UISTORE_BAG_0_SX					= 32,				// 
UISTORE_BAG_0_SY					= 358,
UISTORE_ITEM_DX						= 34,
UISTORE_ITEM_DY						= 34,
//
// item store ---------------------------------------
ITEMSTORE_EVENT						= 9900,
ITEMSTORE_ID_BKGND					= 0,
ITEMSTORE_ID_CLOSE					= 1,
ITEMSTORE_ID_SHOP_SHELF				= 2,

ITEMSTORE_ID_BAG_0_ITEM				= 100,
ITEMSTORE_ID_SHOP_0_ITEM			= 200,
//
// bank store ---------------------------------------
BANKSTORE_EVENT						= 9901,

BANKSTORE_ID_SHELF				= 10,
BANKSTORE_ID_LOAD				= 11,
BANKSTORE_ID_SAVE				= 12,
BANKSTORE_ID_MONEY				= 13,

BANKSTORE_LOAD_SX				= 100,
BANKSTORE_LOAD_SY				= 468,
BANKSTORE_SAVE_SX				= 234,
BANKSTORE_SAVE_SY				= 468,
BANKSTORE_MONEY_SX				= 152,
BANKSTORE_MONEY_SY				= 315,

BANKSTORE_LOAD_MONEY			= 1000,
BANKSTORE_SAVE_MONEY			= 1001,

BANKSTORE_INPUT_BOX_X			= 40,
BANKSTORE_INPUT_BOX_Y			= 220,

//
SAVEBOXSTORE_EVENT					= 9902,
//
STRONGBOXSTORE_EVENT				= 9903,
//
} UISTORE_ENUMS;


//
// STUCTURES ////////////////////////////////////////////////////////////////////////////////////////////////
//
typedef struct tagUISTORE_DATA
{
	CAKE_FRAME_ANI*	cfa;		// shopitem.cak 主體
	CAKE_FRAME *	cf[30];		// 買賣介面所有圖形
	SLONG	store_type;			// 商店種類
	SLONG	is_opened;			// 是否打開
	SLONG	active_id;
	SLONG	hilight_id;

	//
	//SLONG uistore_enabled;		// 商店是否啟動
	//SLONG uistore_type;			// 商店種類
	//SLONG mouse_x;				// 滑鼠目前座標
	//SLONG mouse_y;				//
	//SLONG task_id;				// 滑鼠目前所在位置的id
	//SLONG active_task_id;		// 滑鼠按下後所在位置的id
	//SLONG active_page;			// 目前商店道具顯示頁
} UISTORE_DATA, *LPUISTORE_DATA;


typedef	struct  tagITEM_STORE_DATA
{
	TPOS_ITEM	Item[MAX_STORE_ITEMS];
	ULONG		Money[MAX_STORE_ITEMS];
	ULONG		Amount[MAX_STORE_ITEMS];
	SLONG		NextProc;
	SLONG		OfferNpc;
	SLONG		StoreIndex;
} ITEM_STORE_DATA, *LPITEM_STORE_DATA;


typedef	struct tagBANK_STORE_DATA
{
	SLONG		NextProc;
	SLONG		OfferNpc;
	SLONG		BankIndex;
	SLONG		ShowInput;		// 是否顯示輸入框
} BANK_STORE_DATA, *LPBANK_STORE_DATA;


typedef	struct tagSAVEBOX_STORE_DATA
{
	TPOS_ITEM	Item[MAX_HOUSE_BOX_ITEMS];
	ULONG		Money;
} SAVEBOX_STORE_DATA, *LPSAVEBOX_STORE_DATA;


typedef	struct tagSTRONGBOX_STORE_DATA
{
	TPOS_ITEM	Item[MAX_HOUSE_BOX_ITEMS];
	ULONG		Money;
} STRONGBOX_STORE_DATA, *LPSTRONGBOX_STORE_DATA;


//
// GLOBALS //////////////////////////////////////////////////////////////////////////////////////////////////
//
extern	UISTORE_DATA			uistore_data;
extern	ITEM_STORE_DATA			item_store_data;
extern	BANK_STORE_DATA			bank_store_data;
extern	SAVEBOX_STORE_DATA		savebox_store_data;
extern	STRONGBOX_STORE_DATA	strongbox_store_data;

//
// FUNCTIONS ////////////////////////////////////////////////////////////////////////////////////////////////
//
//ui store
extern	int		init_ui_store(void);
extern	void    free_ui_store(void);
extern	void    active_ui_store(int active);
//
extern	void	set_ui_store_type(SLONG store_type);
extern	void	open_ui_store(SLONG flag);
extern	SLONG	is_ui_store_opened(void);
extern	void    refresh_ui_store(void);
extern	SLONG   handle_ui_store(UINT message, WPARAM wParam, LPARAM lParam);
extern	void    redraw_ui_store(SLONG sx, SLONG sy, void *vbitmap);
//
//item store
extern	void	clear_item_store_data(void);
extern	void	refresh_item_store(void);
extern	SLONG	handle_item_store(UINT message, WPARAM wParam, LPARAM lParam);
extern	void	redraw_item_store(SLONG sx, SLONG sy, void *vbitmap);
extern	void	redraw_item_store_mouse_point_info(SLONG id, void *vbitmap);
extern	void	open_item_store(SLONG flag);
extern	SLONG	is_item_store_opened(void);
//
//bank store
extern	void	clear_bank_store_data(void);
extern	void	refresh_bank_store(void);
extern	SLONG	handle_bank_store(UINT message, WPARAM wParam, LPARAM lParam);
extern	void	redraw_bank_store(SLONG sx, SLONG sy, void *vbitmap);
extern	void	redraw_bank_store_mouse_point_info(SLONG id, void *vbitmap);
extern	void	open_bank_store(SLONG flag);
extern	SLONG	is_bank_store_opened(void);
extern	VOID	bank_money_not_enough( VOID );
extern	VOID	bank_no_item_room( VOID );
//
//savebox store
extern	void	clear_savebox_store_data(void);
extern	void	refresh_savebox_store(void);
extern	SLONG	handle_savebox_store(UINT message, WPARAM wParam, LPARAM lParam);
extern	void	redraw_savebox_store(SLONG sx, SLONG sy, void *vbitmap);
extern	void	redraw_savebox_store_mouse_point_info(SLONG id, void *vbitmap);
extern	void	open_savebox_store(SLONG flag);
extern	SLONG	is_savebox_store_opened(void);
//
//strongbox store
extern	void	clear_strongbox_store_data(void);
extern	void	refresh_strongbox_store(void);
extern	SLONG	handle_strongbox_store(UINT message, WPARAM wParam, LPARAM lParam);
extern	void	redraw_strongbox_store(SLONG sx, SLONG sy, void *vbitmap);
extern	void	redraw_strongbox_store_mouse_point_info(SLONG id, void *vbitmap);
extern	void	open_strongbox_store(SLONG flag);
extern	SLONG	is_strongbox_store_opened(void);
//
//misc functions
extern	void	redraw_my_bag_items(SLONG sx, SLONG sy, SLONG event, SLONG id, BMP *bitmap);
