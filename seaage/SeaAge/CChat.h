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
{   CHAT_NUM        =   32,     //��Ѫ�����`��, �]�t�ۤv��J���M�����쪺.
CHAT_LEN            =   256,    //��ܪ���
CHAT_STAY           =   300,    //��ܫO�d�ɶ�
CHAT_SHOWS          =   16,     //��ܪ�����`��
CHAT_SX             =   228,    //��ܰ_�l x �y��
//CHAT_DY           =   (-20),  //�C���ܶ��j�Z��
//CHAT_SY           =   (SCREEN_HEIGHT-160) //��ܰ_�l y �y��
CHAT_DY             =   -14,    //�C���ܶ��j�Z��
CHAT_SY             =   520,    //��ܰ_�l y �y��
//
CHAT_INPUT_NUM      =   64,     //�ۤv��J������`��
} CHAT_ENUMS;


class   CChat
{
private:
    //-----------------------------------------------------------------
    USTR    str[CHAT_NUM][CHAT_LEN];    //��ܼƾ�
    SLONG   flag[CHAT_NUM];             //��ܼлx
    SLONG   tick[CHAT_NUM];             //�O�d�ɶ�
    SLONG   effect[CHAT_NUM];           //��ܮĪG
    SLONG   next;                       //�[�J��ܯ���
    //-----------------------------------------------------------------
    SLONG   sx,sy,xl,yl;    // position and range of redraw chat
    //-----------------------------------------------------------------
    USTR    input_str[CHAT_INPUT_NUM][CHAT_LEN];    //�ۤv��J����ܤ��e
    SLONG   input_effect[CHAT_INPUT_NUM];           //�ۤv��J�������ܮĪG
    SLONG   input_next;                             //�ۤv��J����ܪ��[�J����
    SLONG   input_get;                              //�ۤv��J����ܪ��������

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

