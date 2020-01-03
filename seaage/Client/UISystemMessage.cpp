/*
**	UISystemMessage.cpp
**	UI of system message.
**
**	Jack, 2002/10/21.
*/
#include "MainFun.h"
#include "UISystemMessage.h"


// D E F I N E S ///////////////////////////////////////////////////////////////////////////////////////////////////
#define MAX_SYSMSG_DATA         1   //�����쪺�̦h�t�ΰT���ƥ�
#define SYSMSG_FONT_SIZE        20  //�t�ΰT���r��j�p



// S T R U C T U R E S /////////////////////////////////////////////////////////////////////////////////////////////
typedef struct tagSYSMSG_DATA
{
    SLONG   flag;           //�лx
    ULONG   recv_time;      //�����ɪ��ɶ�
    USTR    world[64];      //WORLD���A���W��
    USTR    message[256];   //�t�ή������e
    //
    SLONG   show_sx;        //��ܰ_�l��m X
    SLONG   show_sy;        //��ܰ_�l��m Y
    SLONG   show_bytes;     //��ܦr�`����
} SYSMSG_DATA, *LPSYSMSG_DATA;


typedef struct tagSYSTEM_MESSAGE 
{
    SLONG       recv_index;                 //�����t�ΰT������
    SLONG       show_inex;                  //��ܨt�ΰT������
    SYSMSG_DATA msg_data[MAX_SYSMSG_DATA];  //�����쪺�t�ΰT��
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
