#ifndef _SYNCHEARTBEAT_H_
#define _SYNCHEARTBEAT_H_

#define HBF_INIT_SYNCHEARTBEAT          0x01

typedef struct tagSYNCHEARTBEAT_DATA
{
    SLONG   flags;          //�лx 
    DWORD   dwBeatTimes;    //������e���߸�����
    DWORD   dwMsPerBeat;    //�C���߸������j�ɶ�(�@��)
} SYNCHEARTBEAT_DATA, *LPSYNCHEARTBEAT_DATA;

extern  SYNCHEARTBEAT_DATA  syncheartbeat_data;

static  SLONG   InitializeSyncHeartBeat( void );
static  void    DestroySyncHeartBeat( void );
extern  int     init_syncheartbeat(void);
extern  void    free_syncheartbeat(void);
extern  void    start_syncheartbeat(void);
extern  void    stop_syncheartbeat(void);
//
extern  void    init_syncheartbeat_data(void);
extern  DWORD   get_syncheartbeat_times(void);
extern  void    ExecSyncHeartBeat( void );

#endif//_SYNCHRTBEAT_H_