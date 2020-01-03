/*
**  Client_RecvMsg.h
**  Client receive message functions header.
**
**  Jack, 2002.5.13.
**
**  Version update:
**      0.14�� -- 2002.11.1 update.
**      0.15�� -- 2002.11.09 update.
**		0.16�� -- 2002.11.18 update.
**		0.17�� -- 2002.12.05 update.
**		0.18�� -- 2002.12.13 update.
**		0.19�� -- 2002.12.20 update.
**		0.20�� -- 2002.12.24 update.
**		0.21�� -- 2002.12.27 update.
**		0.30�� -- 2003.1.11 update. 
**		0.40�� -- 2003.1.29 update. 
**		0.41�� -- 2003.2.18 update.
**		0.42�� -- 2003.2.21 update.
**		0.43�� -- 2003.2.28 update.
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
#define POS_CLIENT_VERSION					500 //0.50��


//STRUCTURES /////////////////////////////////////////////////////////////////////////////////////////////
typedef struct  tagWORLD_INFO
{
    char    name[64];       //WORLD�W��
    char    addr[64];       //IP�a�}
    DWORD   port;           //�ݤf
    DWORD   active;         //��e���A
    SLONG   player_count;   //�ثe���a�ƶq
} WORLD_INFO, *LPWORLD_INFO;


typedef struct  tagCHARACTER_INFO
{
    SLONG   flag;           //�ϥμаO
    USTR    mainname[32];   //�W��
    USTR    nickname[32];   //�ʺ�
    USTR    zone[32];       //ZONE NAME
    SLONG   career;         //¾�~
    SLONG   sex;            //�ʧO
    SLONG   level;          //����
    SLONG   country;        //��a
    USTR    nobility[16];   //���
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


