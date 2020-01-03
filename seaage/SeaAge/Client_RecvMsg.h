/*
**  Client_RecvMsg.h
**  Client receive message functions header.
**
**  Jack, 2002.5.13.
**
**  Version update:
**      0.14版 -- 2002.11.1 update.
**      0.15版 -- 2002.11.09 update.
**		0.16版 -- 2002.11.18 update.
**		0.17版 -- 2002.12.05 update.
**		0.18版 -- 2002.12.13 update.
**		0.19版 -- 2002.12.20 update.
**		0.20版 -- 2002.12.24 update.
**		0.21版 -- 2002.12.27 update.
**		0.30版 -- 2003.1.11 update. 
**		0.40版 -- 2003.1.29 update. 
**		0.41版 -- 2003.2.18 update.
**		0.42版 -- 2003.2.21 update.
**		0.43版 -- 2003.2.28 update.
*/
#pragma	once
#include "NetGE_Event_Def.h"
//
// DEFINES ////////////////////////////////////////////////////////////////////////////////////////////////
//
#define MAX_WORLD_INFO						256
#define MAX_ZONE_INFO						256
#define MAX_CHARACTER_INFO					4
//
#define POS_CLIENT_VERSION					500 //0.50版


//STRUCTURES /////////////////////////////////////////////////////////////////////////////////////////////
typedef struct  tagWORLD_INFO
{
    char    name[64];       //WORLD名稱
    char    addr[64];       //IP地址
    DWORD   port;           //端口
    DWORD   active;         //當前狀態
    SLONG   player_count;   //目前玩家數量
} WORLD_INFO, *LPWORLD_INFO;


typedef struct  tagCHARACTER_INFO
{
    SLONG   flag;           //使用標記
    USTR    mainname[32];   //名稱
    USTR    nickname[32];   //暱稱
    USTR    zone[32];       //ZONE NAME
    SLONG   career;         //職業
    SLONG   sex;            //性別
    SLONG   level;          //等級
    SLONG   country;        //國家
    USTR    nobility[16];   //爵位
	ULONG	qqid;			//QQID
} CHARACTER_INFO, *LPCHARACTER_INFO;



//GLOBALS ///////////////////////////////////////////////////////////////////////////////////////////////
extern  HWND            g_hWndGameEvent;
extern  WORLD_INFO      world_info[MAX_WORLD_INFO];
extern  SLONG           max_world_info;
extern  CHARACTER_INFO  character_info[MAX_CHARACTER_INFO];


//FUNCTIONS /////////////////////////////////////////////////////////////////////////////////////////////
int     init_client(void);
void    active_client(int active);
void    free_client(void);
//
void    clear_world_info(void);
void    clear_zone_info(void);
void    clear_character_info(void);
void    debug_init_character_info(void);
//
HRESULT HandlePosGameEvent(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
//
void    client_add_npc_talk_msg(SLONG npc_no, USTR *msg);


