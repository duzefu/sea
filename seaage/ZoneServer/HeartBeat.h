#ifndef _HEARTBEAT_H_
#define _HEARTBEAT_H_

#define HBF_INIT_HEARTBEAT          0x01

typedef struct tagHEARTBEAT_DATA
{
    SLONG   flags;          //�лx 
    DWORD   dwBeatTimes;    //������e���߸�����
    DWORD   dwMsPerBeat;    //�C���߸������j�ɶ�(�@��)
} HEARTBEAT_DATA, *LPHEARTBEAT_DATA;

extern  HEARTBEAT_DATA  heartbeat_data;

void CALLBACK   HeartBeatProc(UINT uID,UINT uMsg,DWORD dwUser,DWORD dw1,DWORD dw2 );
static  SLONG   InitializeHeartBeat( void );
static  void    DestroyHeartBeat( void );
extern  int     init_heartbeat(void);
extern  void    free_heartbeat(void);
extern  void    start_heartbeat(void);
extern  void    stop_heartbeat(void);
extern  void    init_heartbeat_data(void);
extern  DWORD   get_heartbeat_times(void);
extern  void    ExecHeartBeat( void );


#endif//_HRTBEAT_H_
