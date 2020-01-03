/*
**  hrtbeat.h
**  game heart beat functions header.
**
**  geaan, 2001.8.1.
*/
#ifndef _HRTBEAT_H_
#define _HRTBEAT_H_


int     init_heartbeat(void);
void    active_heartbeat(int active);
void    free_heartbeat(void);
void    start_heartbeat(void);
void    stop_heartbeat(void);
//
void    init_heartbeat_data(void);
void    sync_heartbeat_data(DWORD dwTimes);
DWORD   get_heartbeat_times(void);
DWORD   get_heartbeat_refresh_times(void);
void    set_heartbeat_timeout_milliseconds(DWORD ms);
DWORD   get_heartbeat_timeout_milliseconds(void);



#endif//_HRTBEAT_H_
