/*
 *  qqhis.h
 *  functions for store system message
 *  Zhang Zhaohui 2002.11.12
 */


#ifndef QQHIS_H_
#define QQHIS_H_
#include "mainfun.h"
#include "qqmsg.h"

enum QQHIS_CONST
{ 
    MAX_TIME_STR = 24, 
    MAX_MSG_STR  = 200, 
    MAX_MSG      = 0x20,
};


/*
 * Structure for stores one message
 */
typedef struct tagQQHIS_MSG 
{ 
    SLONG       index;
    char        message[MAX_MSG_STR]; 
    char        time_str[MAX_TIME_STR];
}QQHIS_MSG, *LPQQHIS_MSG; 


/*
 *  Structure for cache message
 */
typedef struct tagQQHIS
{
    SLONG           first;
    QQHIS_MSG       msg[MAX_MSG];
}QQHIS, *LPQQHIS;



/*
 *  Initialize and free function
 */
SLONG init_qh(void);
void  free_qh(void);


/*
 *  Add message and get message
 *      return index of message
 */
SLONG qh_add(char *message);
char *qh_get(SLONG index);
char *qh_get_time(SLONG index);


/*
 *  Get the number of total messages
 */
SLONG qh_get_count(void);


#endif /* QQHIS_H_ */
