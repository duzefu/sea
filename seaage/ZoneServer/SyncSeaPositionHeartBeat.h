#ifndef _SYNCSEAPOSITIONHEARTBEAT_H_
#define _SYNCSEAPOSITIONHEARTBEAT_H_

#define HBF_INIT_SYNCSEAPOSITIONHEARTBEAT          0x01

typedef struct tagSYNCSEAPOSITIONHEARTBEAT_DATA
{
    SLONG   flags;          //標誌 
    DWORD   dwBeatTimes;    //本機當前的心跳次數
    DWORD   dwMsPerBeat;    //每次心跳的間隔時間(毫秒)
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