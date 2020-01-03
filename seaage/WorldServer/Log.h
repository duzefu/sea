#ifndef	_LOG_H_
#define	_LOG_H_

void SaveMsgToLog(char *from, char *msg);
void SaveWorkToLog(char *who,char *ip,char *work);
void SaveConnectedCounter(DWORD index);
void LoadConnectedCounter(void);
void SaveIOToLog(char *ip,char *io);
void LoadMaxLoginer(void);
void LoadMaxPlayer(void);
void SaveMaxPlayer(void);
void SaveMaxLoginer(void);
void SaveQQIDCounter(DWORD index);
void LoadQQIDCounter(void);

#endif	//_LOG_H_