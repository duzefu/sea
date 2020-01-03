/*
**	UISystemMessage.cpp
**	UI of system message.
**
**	Jack, 2002/10/21.
*/
#include "MainFun.h"
#include "UISystemMessage.h"


// D E F I N E S ///////////////////////////////////////////////////////////////////////////////////////////////////
#define MAX_SYSMSG_DATA         1   //接收到的最多系統訊息數目
#define SYSMSG_FONT_SIZE        20  //系統訊息字體大小



// S T R U C T U R E S /////////////////////////////////////////////////////////////////////////////////////////////
typedef struct tagSYSMSG_DATA
{
    SLONG   flag;           //標誌
    ULONG   recv_time;      //接收時的時間
    USTR    world[64];      //WORLD伺服器名稱
    USTR    message[256];   //系統消息內容
    //
    SLONG   show_sx;        //顯示起始位置 X
    SLONG   show_sy;        //顯示起始位置 Y
    SLONG   show_bytes;     //顯示字節長度
} SYSMSG_DATA, *LPSYSMSG_DATA;


typedef struct tagSYSTEM_MESSAGE 
{
    SLONG       recv_index;                 //接受系統訊息索引
    SLONG       show_inex;                  //顯示系統訊息索引
    SYSMSG_DATA msg_data[MAX_SYSMSG_DATA];  //接收到的系統訊息
} SYSTEM_MESSAGE, *LPSYSTEM_MESSAGE;


// G L O B A L S ///////////////////////////////////////////////////////////////////////////////////////////////////
SYSTEM_MESSAGE  system_message;

/******************************************************************************************************************/
/* SYSTEM MESSAGE MAIN FUNCTIONS                                                                                  */
/******************************************************************************************************************/
int     init_system_message(void)
{
    clear_system_message();
    return  0;
}

void    free_system_message(void)
{
}

SLONG   add_system_message(USTR *world, USTR *msg)
{
    SYSMSG_DATA *data;
    SLONG   index;

    index = system_message.recv_index;
    data = &system_message.msg_data[index];
    strcpy((char *)data->world, (const char *)world);
    strcpy((char *)data->message, (const char *)msg);
    data->recv_time = timeGetTime();
    data->show_sx = SCREEN_WIDTH - SYSMSG_FONT_SIZE;
    data->show_sy = index * (SYSMSG_FONT_SIZE+2);
    //data->show_bytes = strlen((const char *)world) + strlen((const char *)msg) + 4;
    data->show_bytes = strlen((const char *)msg) + 4;
    data->flag = 1;
    system_message.recv_index = (index + 1) % MAX_SYSMSG_DATA;

    return  index;
}


void    refresh_system_message(void)
{
    SYSMSG_DATA *data;
    ULONG   curr_time;
    SLONG   i;

    curr_time = timeGetTime();
    for(i=0; i<MAX_SYSMSG_DATA; i++)
    {
        data = &system_message.msg_data[i];
        if(data->flag)
        {
            if(curr_time - data->recv_time > 180000) //3 minutes
            {
                data->flag = 0;
            }
            else
            {
                data->show_sx -= 4;
                if(data->show_sx < - data->show_bytes * SYSMSG_FONT_SIZE / 2)
                    data->show_sx = SCREEN_WIDTH + 4;
            }
        }
    }
}


void    redraw_system_message(BMP *bitmap)
{
    SYSMSG_DATA *data;
    SLONG   i;
    USTR    info[512];

    print20(0, 0, (USTR*)"~C4~O8", PEST_PUT, bitmap);
    for(i=0; i<MAX_SYSMSG_DATA; i++)
    {
        data = &system_message.msg_data[i];
        if(data->flag)
        {
            //sprintf((char *)info, "%s : %s", data->world, data->message);
            alpha_put_bar(0, data->show_sy - 1, bitmap->w, SYSMSG_FONT_SIZE+2, SYSTEM_BLUE, bitmap, 128);
            sprintf((char *)info, "%s", data->message);
            print20(data->show_sx, data->show_sy, (USTR*)info, PEST_PUT, bitmap);
        }
    }
    print20(0, 0, (USTR*)"~C0~O0", PEST_PUT, bitmap);
}


void    clear_system_message(void)
{
    memset(&system_message, 0x00, sizeof(system_message));
}
