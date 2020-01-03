#ifndef _SYNCSEAPOSITIONHEARTBEAT_H_
#define _SYNCSEAPOSITIONHEARTBEAT_H_

#define HBF_INIT_SYNCSEAPOSITIONHEARTBEAT          0x01

typedef struct tagSYNCSEAPOSITIONHEARTBEAT_DATA
{
    SLONG   flags;          //�лx 
    DWORD   dwBeatTimes;    //������e���߸�����
    DWORD   dwMsPerBeat;    //�C���߸������j�ɶ�(�@��)
} SYNCSEAPOSITIONHEARTBEAT_DATA, *LPSYNCSEAPOSITIONHEARTBEAT_DATA;

extern  SYNCSEAPOSITIONHEARTBEAT_DATA  syncseapositionheartbeat_data;

static  SLONG   InitializeSyncSeaPositionHeartBeat( void );
static  void    DestroySyncSeaPositionHeartBeat( void );
extern  int     init_syncseapositionheartbeat(void);
extern  void    free_syncseapositionheartbeat(void);
extern  void    start_syncseapositionheartbeat(void);
extern  void    stop_syncseapositionheartbeat(void);
//
extern  void    init_syncseapositionheartbeat_data(void);
extern  DWORD   get_syncseapositionheartbeat_times(void);
extern  void    ExecSyncSeaPositionHeartBeat( void );

#endif//_SYNCSEAPOSITIONHRTBEAT_H_