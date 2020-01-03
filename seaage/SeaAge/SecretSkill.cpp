/*
**	SecretSkill.cpp
**	secret skill functions.
**
**	Jack, 2002/10/18.
*/
#include "MainFun.h"
#include "NetGE_MainFunc.h"
#include "ClientMain.h"
#include "Npc.h"
#include "SecretSkill.h"
#include "CmdEvent.h"



/************************************************************************************************************/
/* STRUCTURES & DATAS                                                                                       */
/************************************************************************************************************/
typedef struct tagSECRET_SKILL_CONFIG 
{
    SLONG   flag;                           //�K�޼Ҧ��O�_���}
    //
    SLONG   enable_create_account;          //�O�_�i�H�إ߷s�b��
    //
    SLONG   enable_rand_move;               //�H������
    SLONG   last_rand_move_time;            //�W���H�����ʪ��ɶ�
    SLONG   rand_move_duration;             //�C���T�w�s���ؼ��I���ɶ����j
    //
    SLONG   enable_rand_weather;            //�H���Ѯ�
    SLONG   last_rand_weather_time;         //�W���H���H���Ѯ𪺮ɶ�
    SLONG   rand_weather_duration;          //�C���s���Ѯ𪺮ɶ����j
    //
    SLONG   enable_follow_npc;              //�۰ʸ��H
    SLONG   last_follow_npc_time;           //�W���T�w���HNPC���ؼ��I���ɶ�
    SLONG   follow_npc_duration;            //�C���s��oNPC���y�Ъ��ɶ����j
    CHAR	follow_npc_mainname[64];        //�۰ʸ��H��NPC�W��
    //
} SECRET_SKILL_CONFIG, *LPSECRET_SKILL_CONFIG;


SECRET_SKILL_CONFIG     secret_skill_config;    //���D�t�m�ƾ�


/******************************************************************************************************************/
/* SECRET SKILL FUNCTIONS                                                                                       */
/******************************************************************************************************************/
void    init_secret_skill(void)
{
    SECRET_SKILL_CONFIG *data = &secret_skill_config;

    memset(data, 0x00, sizeof(SECRET_SKILL_CONFIG));

    // ZZH 2003.5.15 ���}�n�������W�� �Ыرb�� �M �b���޲z ���s
    secret_skill_config.enable_create_account = 1;
    
    data->follow_npc_duration = 500;
    data->rand_move_duration = 500;
    data->rand_weather_duration = 20000;
}


void    enable_secret_skill(void)
{
    secret_skill_config.flag = true;
}


void    disable_secret_skill(void)
{
    secret_skill_config.flag = false;
}


void    set_secret_skill_rand_move(SLONG flag)
{
    secret_skill_config.enable_rand_move = flag;
}


void    set_secret_skill_rand_weather(SLONG flag)
{
    secret_skill_config.enable_rand_weather = flag;
}


void    set_secret_skill_follow_npc(SLONG flag, USTR *mainname)
{
    secret_skill_config.enable_follow_npc = flag;
    if(flag && mainname) 
    {
        strcpy((char *)secret_skill_config.follow_npc_mainname, (const char *)mainname);
    }
}


void    set_secret_skill_create_account(SLONG flag)
{
    secret_skill_config.enable_create_account = flag;
}


SLONG   is_enable_create_account(void)
{
    return  secret_skill_config.enable_create_account;
}


void    refresh_secret_skill(void)
{
    SECRET_SKILL_CONFIG *data = &secret_skill_config;

    if(!data->flag)
        return;

    if(data->enable_rand_move)
        process_secret_skill_rand_move();
    if(data->enable_rand_weather)
        process_secret_skill_rand_weather();
    if(data->enable_follow_npc)
        process_secret_skill_follow_npc();
}


void    process_secret_skill_rand_move(void)
{
    SECRET_SKILL_CONFIG *data = &secret_skill_config;
    SLONG   x, y, z, dest_x, dest_y;
    DWORD   curr_time;

    if(g_lPlayerIndex < 0)
        return;

    curr_time = timeGetTime();
    if( curr_time - data->last_rand_move_time < (DWORD)data->rand_move_duration)
        return;

    LOCK_CHARACTER(g_lPlayerIndex);
	GetCharacterPosition(g_lPlayerIndex, &x, &y, &z);
    UNLOCK_CHARACTER(g_lPlayerIndex);

    dest_x = x + (200 + system_rand() % 50) * (1-(system_rand()%2)*2);
    dest_y = y + (200 + system_rand() % 50) * (1-(system_rand()%2)*2);
    client_cmd_left_hit_map(dest_x, dest_y);

    data->last_rand_weather_time = curr_time;
}


void    process_secret_skill_rand_weather(void)
{
    SECRET_SKILL_CONFIG *data = &secret_skill_config;
    DWORD   curr_time;

    if(g_lPlayerIndex < 0)
        return;

    curr_time = timeGetTime();
    if(curr_time - data->last_rand_weather_time < (DWORD)data->rand_weather_duration)
        return;

    // Jack, todo [10:48,10/18/2002]
    //control rand weather here.

    data->last_rand_weather_time = curr_time;
}


void    process_secret_skill_follow_npc(void)
{
    SECRET_SKILL_CONFIG *data = &secret_skill_config;
    DWORD   curr_time;
    SLONG   dest_x, dest_y, dest_z, dest_npc;
    SLONG   my_x, my_y, my_z, dx, dy, dr;
    SLONG   new_x, new_y;

    if(g_lPlayerIndex < 0)
        return;

    curr_time = timeGetTime();
    if(curr_time - data->last_follow_npc_time < (DWORD)data->follow_npc_duration)
        return;

    LOCK_CHARACTER(0);
    dest_npc = FindCharacterByMainName(data->follow_npc_mainname);
    UNLOCK_CHARACTER(0);
    if(dest_npc < 0)
        goto _cant_find_this_time;

    LOCK_CHARACTER(0);
	GetCharacterPosition(dest_npc, &dest_x, &dest_y, &dest_z);
	GetCharacterPosition(g_lPlayerIndex, &my_x, &my_y, &my_z);
    UNLOCK_CHARACTER(0);

    dx = abs(dest_x - my_x);
    dy = abs(dest_y - my_y);
    dr = (SLONG) sqrt(dx * dx + dy * dy);
    if(dr > 160 && dr < 400)
    {
        new_x = dest_x + (50 + system_rand() % 20) * (1- system_rand()%2*2);
        new_y = dest_y + (50 + system_rand() % 20) * (1- system_rand()%2*2);
        client_cmd_left_hit_map(new_x, new_y);
    }


_cant_find_this_time:
    data->last_rand_weather_time = curr_time;
    return;
}

