/*
**  CChat.h
**  class chat functions header.
**
**  ZJian,2001.4.21.
*/
#ifndef _CCHAT_H_INCLUDE_
#define _CCHAT_H_INCLUDE_

//chat text effect
#define CHATEFF_WHITE       0
#define CHATEFF_RED         1
#define CHATEFF_GREEN       2
#define CHATEFF_BLUE        3
#define CHATEFF_YELLOW      4
#define CHATEFF_CYAN        5
#define CHATEFF_PINK        6


typedef enum    CHAT_ENUMS
{   CHAT_NUM        =   32,     //聊天的對話總數, 包含自己輸入的和接收到的.
CHAT_LEN            =   256,    //對話長度
CHAT_STAY           =   300,    //對話保留時間
CHAT_SHOWS          =   16,     //顯示的對話總數
CHAT_SX             =   228,    //對話起始 x 座標
//CHAT_DY           =   (-20),  //每行對話間隔距離
//CHAT_SY           =   (SCREEN_HEIGHT-160) //對話起始 y 座標
CHAT_DY             =   -14,    //每行對話間隔距離
CHAT_SY             =   520,    //對話起始 y 座標
//
CHAT_INPUT_NUM      =   64,     //自己輸入的對話總數
} CHAT_ENUMS;


class   CChat
{
private:
    //-----------------------------------------------------------------
    USTR    str[CHAT_NUM][CHAT_LEN];    //對話數據
    SLONG   flag[CHAT_NUM];             //對話標誌
    SLONG   tick[CHAT_NUM];             //保留時間
    SLONG   effect[CHAT_NUM];           //顯示效果
    SLONG   next;                       //加入對話索引
    //-----------------------------------------------------------------
    SLONG   sx,sy,xl,yl;    // position and range of redraw chat
    //-----------------------------------------------------------------
    USTR    input_str[CHAT_INPUT_NUM][CHAT_LEN];    //自己輸入的對話內容
    SLONG   input_effect[CHAT_INPUT_NUM];           //自己輸入的對話顯示效果
    SLONG   input_next;                             //自己輸入的對話的加入索引
    SLONG   input_get;                              //自己輸入的對話的抓取索引

public:
    CChat();
    ~CChat();

    void    add(SLONG effect, USTR *string);
    void    refresh(void);
    void    refresh2(void);
    void    redraw(void *vbitmap);
    void    clear(void);
	void	hide_all(void);
    //
    void    clear_input(void);
    void    add_input(SLONG effect, USTR *string);
    SLONG   get_prev_input(SLONG *effect, USTR *string, SLONG enable_loop);
    SLONG   get_next_input(SLONG *effect, USTR *string, SLONG enable_loop);
};



extern  CChat   game_chat;

EXPORT  void    FNBACK  alpha_put_form(SLONG sx, SLONG sy, SLONG xl, SLONG yl, PIXEL color, BMP *bitmap, SLONG alpha);

#endif//_CCHAT_H_INCLUDE_

