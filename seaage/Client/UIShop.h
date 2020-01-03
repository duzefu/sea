/*
**  UIShop.h
**  Class UIShop functions.
**
**  WR, 2002.11.22.
*/
#ifndef _UISHOP_H_
#define _UISHOP_H_

#include "mainfun.h"

// DEFINES /////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef enum    UI_SHOP_ENUMS
{  
	UISHOP_FRAME_BKGND				 =  0,
	UISHOP_FRAME_PRODUCT_LEFT		 =	1,
	UISHOP_FRAME_PRODUCT_RIGHT		 =	4,	
	UISHOP_FRAME_SELL_LEFT			 =	7,
	UISHOP_FRAME_SELL_RIGHT			 =	10,
	UISHOP_FRAME_SELL_ALL			 =  13,
	UISHOP_FRAME_OK					 =	16,
	UISHOP_FRAME_CANCEL				 =	19,
	//

	//
	UISHOP_EVENT                     =  3009,
	UISHOP_ID_BKGND                  =  0,
	UISHOP_ID_PRODUCT_LEFT			 =  1,
	UISHOP_ID_PRODUCT_RIGHT			 =  2,
	UISHOP_ID_SELL_LEFT				 =	3,
	UISHOP_ID_SELL_RIGHT			 =	4,
	UISHOP_ID_SELL_ALL				 =  5,	
	UISHOP_ID_OK					 =  6,
	UISHOP_ID_CANCEL                 =  7,

	UISHOP_ID_PRODUCT_BAR_0_GOODS	 =  50,
	UISHOP_ID_SELL_BAR_0_GOODS		 =  60,
	UISHOP_ID_CABIN_0_GOODS			 =  70,			
	
	UISHOP_PRODUCT_BAR_SX			=	45,
	UISHOP_PRODUCT_BAR_SY			=	133,
	UISHOP_SELL_BAR_SX				=	45,
	UISHOP_SELL_BAR_SY				=	221,
	UISHOP_BAR_DX					=	31,
	UISHOP_BAR_DY					=	31,	
	UISHOP_SHIP_SX					=	47,
	UISHOP_SHIP_SY					=	299,

} UI_SHOP_ENUMS;


// STRUCTURES //////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct tagUI_SHOP_GOODS
{
	SLONG id;
	SLONG flag;					
	SLONG price;
	SLONG orig_price;
}UI_SHOP_GOODS,*LPUI_SHOP_GOODS;

typedef struct tagUI_SHOP_DATA 
{
    CAKE_FRAME_ANI  *cfa;			//frame ani pointer
    CAKE_FRAME      *cf[32];		//image pointer of each frame.
    //
    CAKE_FRAME_ANI  *ship_cfa;      //ship frame ani pointre
    CAKE_FRAME      *ship_cf[32];   //image pointer of each ship
    //
	CAKE_FRAME_ANI  *cabin_cfa;      
    CAKE_FRAME      *cabin_cf[32];   
    //
    SLONG   hilight_id;				//hilight id
    SLONG   active_id;				//active id
    
	SLONG   ship_index;				//船隻索引, 對應船隻介面的底圖
    SLONG   is_opened;				//介面是否打開

	/* goods info
	//
	SLONG		product_bar_start;					//港口特產品框起始編號
    SLONG		product_type;						//特產品種類數目
	UI_SHOP_GOODS product[MAX_PRODUCT_TYPE];
    
    SLONG       sell_bar_start;						//玩家賣出框起始
    SLONG       sell_goods_num[MAX_CABIN];			//同種賣出品個數
    UI_SHOP_GOODS sell_goods[MAX_CABIN];

	UI_SHOP_GOODS cabin_goods[MAX_CABIN];
    
    LONG        expense;							//支出    
    LONG        income;								//收入
    LONG        totalIncome;						//總計
    */
} UI_SHOP_DATA, *LPUI_SHOP_DATA;


// GLOBALS /////////////////////////////////////////////////////////////////////////////////////////////////////////
extern  UI_SHOP_DATA ui_shop_data;


// FUNCTIONS ///////////////////////////////////////////////////////////////////////////////////////////////////////
int		init_ui_shop(void);
void	free_ui_shop(void);
SLONG	handle_ui_shop(UINT message, WPARAM wParam, LPARAM lParam);
void	redraw_ui_shop(SLONG sx, SLONG sy, void *vbitmap);
void	open_ui_shop(SLONG flag);
SLONG	is_ui_shop_open(void);




#endif//_UISHOP_H_