#ifndef _SAVEDATAHEARTBEAT_H_
#define _SAVEDATAHEARTBEAT_H_

#define HBF_INIT_SAVEDATAHEARTBEAT          0x01

typedef struct tagSAVEDATAHEARTBEAT_DATA
{
    SLONG   flags;          //�лx 
    DWORD   dwBeatTimes;    //������e���߸�����
    DWORD   dwMsPerBeat;    //�C���߸������j�ɶ�(�@��)
} SAVEDATAHEARTBEAT_DATA, *LPSAVEDATAHEARTBEAT_DATA;

extern  SAVEDATAHEARTBEAT_DATA  savedataheartbeat_data;

void CALLBACK   SaveDataHeartBeatProc(UINT uID,UINT uMsg,DWORD dwUser,DWORD dw1,DWORD dw2 );
static  SLONG   InitializeSaveDataHeartBeat( void );
static  void    DestroySaveDataHeartBeat( void );
extern  int     init_savedataheartbeat(void);
extern  void    free_savedataheartbeat(void);
extern  void    start_savedataheartbeat(void);
extern  void    stop_savedataheartbeat(void);
extern  void    init_savedataheartbeat_data(void);
extern  DWORD   get_savedataheartbeat_times(void);
extern  void    ExecSaveDataHeartBeat( void );


#endif//_SAVEDATAHEARTBEAT_H_
