#ifndef _SYNCPOSITIONHEARTBEAT_H_
#define _SYNCPOSITIONHEARTBEAT_H_

#define HBF_INIT_SYNCPOSITIONHEARTBEAT          0x01

typedef struct tagSYNCPOSITIONHEARTBEAT_DATA
{
    SLONG   flags;          //標誌 
    DWORD   dwBeatTimes;    //本機當前的心跳次數
    DWORD   dwMsPerBeat;    //每次心跳的間隔時間(毫秒)
} SYNCPOSITIONHEARTBEAT_DATA, *LPSYNCPOSITIONHEARTBEAT_DATA;

extern  SYNCPOSITIONHEARTBEAT_DATA  syncpositionheartbeat_data;

static  SLONG   InitializeSyncPositionHeartBeat( void );
static  void    DestroySyncPositionHeartBeat( void );
extern  int     init_syncpositionheartbeat(void);
extern  void    free_syncpositionheartbeat(void);
extern  void    start_syncpositionheartbeat(void);
extern  void    stop_syncpositionheartbeat(void);
//
extern  void    init_syncpositionheartbeat_data(void);
extern  DWORD   get_syncpositionheartbeat_times(void);
extern  void    ExecSyncPositionHeartBeat( void );

#endif//_SYNCPOSITIONHRTBEAT_H_