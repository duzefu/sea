/*
**	UIGameMessage.cpp
**	UI of game message.
**
**	Jack, 2002/10/22.
*/
#include "MainFun.h"
#include "UIGameMessage.h"


// D E F I N E S ///////////////////////////////////////////////////////////////////////////////////////////////////
#define MAX_GAMEMSG_DATA            48      //接收到的最多遊戲訊息數目
#define MAX_GAMEMSG_SHOW            24      //同時顯示的最多遊戲訊息
#define GAMEMSG_FONT_SIZE           12      //遊戲訊息字體大小
#define GAMEMSG_KEEP_TIME           30000   //30秒鍾
//
#define GAMEMSG_SHOW_SX             4
#define GAMEMSG_SHOW_SY             (SCREEN_HEIGHT-160)
#define GAMEMSG_SHOW_DY             (- GAMEMSG_FONT_SIZE - 3)


// S T R U C T U R E S /////////////////////////////////////////////////////////////////////////////////////////////
typedef struct tagGAMEMSG_DATA
{
    SLONG   flag;           //標誌
    ULONG   recv_time;      //接收時的時間
    SLONG   type;           //訊息類型
    USTR    message[256];   //消息內容
    SLONG   show_bytes;     //顯示字節長度
} GAMEMSG_DATA, *LPGAMEMSG_DATA;


typedef struct tagGAME_MESSAGE 
{
    SLONG           show_sx;                    //顯示起始位置 X
    SLONG           show_sy;                    //顯示起始位置 Y
    SLONG           recv_index;                 //接受系統訊息索引
    SLONG           show_inex;                  //顯示系統訊息索引
    GAMEMSG_DATA    msg_data[MAX_GAMEMSG_DATA]; //接收到的遊戲訊息
} GAME_MESSAGE, *LPGAME_MESSAGE;


// G L O B A L S ///////////////////////////////////////////////////////////////////////////////////////////////////
GAME_MESSAGE    game_message;

/******************************************************************************************************************/
/* SYSTEM MESSAGE MAIN FUNCTIONS                                                                                  */
/******************************************************************************************************************/
int     init_game_message(void)
{
    clear_game_message();
    return  0;
}

void    free_game_message(void)
{
}


SLONG   add_game_message(SLONG type, USTR *msg)
{
    GAMEMSG_DATA *data;
    SLONG   index;

    index = game_message.recv_index;
    data = &game_message.msg_data[index];
    data->type = type;
    strcpy((char *)data->message, (const char *)msg);
    data->recv_time = timeGetTime();
    data->show_bytes = strlen((const char *)msg);
    data->flag = 1;
    game_message.recv_index = (index + 1) % MAX_GAMEMSG_DATA;

    return  index;
}


void    refresh_game_message(void)
{
    GAMEMSG_DATA *data;
    ULONG   curr_time;
    SLONG   i;

    curr_time = timeGetTime();
    for(i=0; i<MAX_GAMEMSG_DATA; i++)
    {
        data = &game_message.msg_data[i];
        if(data->flag)
        {
            if(curr_time - data->recv_time > GAMEMSG_KEEP_TIME)
            {
                data->flag = 0;
            }
        }
    }
}


void    redraw_game_message(BMP *bitmap)
{
    SLONG   i, index, disp_x, disp_y;
    USTR    info[512];

    disp_x = GAMEMSG_SHOW_SX;
    disp_y = GAMEMSG_SHOW_SY;
    print12(0, 0, (USTR*)"~C3~O0", PEST_PUT, bitmap);
    for(i=0; i<MAX_GAMEMSG_SHOW; i++)
    {
        index = ((game_message.recv_index - i) + MAX_GAMEMSG_DATA) % MAX_GAMEMSG_DATA;
        if(game_message.msg_data[index].flag)
        {
            sprintf((char *)info, "%s", game_message.msg_data[index].message);
            print12(disp_x, disp_y, (USTR*)info, PEST_PUT, bitmap);
            disp_y += GAMEMSG_SHOW_DY;
        }
    }
    print12(0, 0, (USTR*)"~C0~O0", PEST_PUT, bitmap);
}


void    clear_game_message(void)
{
    memset(&game_message, 0x00, sizeof(game_message));
}
