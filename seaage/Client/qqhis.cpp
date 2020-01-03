/*
 *  qqhis.cpp
 *  functions for store system message
 *  Zhang Zhaohui 2002.11.12
 */

#include "qqhis.h"
#include "qqlocal.h"


/* Stores system messages */
QQHIS   *qh = NULL;

/* Store message count */
DWORD   qh_count = 0;



/* Save and load message */
static SLONG qh_save(char *msg);
static SLONG qh_load(SLONG index, QQHIS_MSG *qh_msg);

/* Frist index add 1 */
static void qh_index_inc(void);

/* Frist index subtract 1 */
static void qh_index_dec(void);




/*
 * Alloc memory for history and Initialize global pointer.
 */
SLONG init_qh(void)
{
    SLONG i;
    
    if (qh)
        return TTN_NOT_OK;

    qh = (QQHIS*)GlobalAlloc(GPTR, sizeof(QQHIS));
    if (!qh)
    {
        log_error(1, "Error: Can not alloc memory for message cache.");
        return TTN_NOT_OK;
    }
    
    for (i = 0; i < MAX_MSG; i++)
        qh_load(i, &qh->msg[i]);
    
    qh->first = 0;
    qh_count = qh_get_count();

    return TTN_OK;
}


/*
 *  Free friend buffer, and set global variable to zero
 */
void free_qh(void)
{
    if (qh)
    {
        GlobalFree(qh);
        qh = NULL;
    }
    qh_count = 0;
}


/*
 * Add a message to message list
 */
SLONG qh_add(char *message)
{
    SLONG i;
    
    if (!qh)
    {
        log_error(1, "Error: system message need been Initialized!");
        return TTN_NOT_OK;
    }

    qh_save(message);
    
    for (i = 0; i < MAX_MSG; i++)
    {
        if (qh->msg[i].index >= 0)
            ++(qh->msg[i].index);
    }
    return TTN_OK;
}

/*
 * Get a message
 */
char *qh_get(SLONG index)
{
    SLONG i;
    char *ch;

    for (i = 0; i < MAX_MSG; i++)
        if (qh->msg[i].index == index)
            return (char*)qh->msg[i].message;

    /* read from file */
    qh_load(index, &qh->msg[qh->first]);

    if (qh->msg[qh->first].index == index)
    {
        ch = qh->msg[qh->first].message;
        qh_index_inc();
        return ch;
    }

    return NULL;
}


/*
 * Get time string
 */
char *qh_get_time(SLONG index)
{
    SLONG i;
    char *ch;

    for (i = 0; i < MAX_MSG; i++)
        if (qh->msg[i].index == index)
            return (char*)qh->msg[i].time_str;

    /* read from file */
    qh_load(index, &qh->msg[qh->first]);

    if (qh->msg[qh->first].index == index)
    {
        ch = qh->msg[qh->first].time_str;
        qh_index_inc();
        return ch;
    }

    return NULL;
}


/*
 *  Get total message number
 */
SLONG qh_get_count(void)
{
//    return ql_get_system_msg_count();
    return 0;
}


/*
 *  Save system message
 */
SLONG qh_save(char *qh_msg)
{

    time_t ltime;
    
    time(&ltime);

//    return ql_save_system_msg(qh_msg, ltime);
    return NULL;
}


/*
 *  load system message
 */
SLONG qh_load(SLONG index, QQHIS_MSG *qh_msg)
{
    static char msg_buf[MAX_MSG_STR];
    DWORD ltime;
    tm    *tm_time;

//    if ( TTN_OK != ql_load_system_msg(index, msg_buf, &ltime))
//        return TTN_NOT_OK;
    return TTN_NOT_OK;

    if (qh_msg)
    {
        lstrcpyn(qh_msg->message, msg_buf, MAX_MSG_STR);
        tm_time = localtime((const time_t*)&ltime);
        wsprintf(msg_buf, QQTXT_TIME_STR, tm_time->tm_year,
                                          tm_time->tm_mon,
                                          tm_time->tm_mday,
                                          tm_time->tm_hour,
                                          tm_time->tm_min);
        
        lstrcpyn(qh_msg->time_str, msg_buf, MAX_TIME_STR);
            return TTN_OK;
    }
    else
        return TTN_NOT_OK;
}


/* 
 *  Frist index add 1
 */
static void qh_index_inc(void)
{
    if (qh)
    {
        ++(qh->first);
        if (qh->first >= MAX_MSG)
            qh->first = 0;
    }
}


/* 
 * Frist index subtract 1
 */
static void qh_index_dec(void)
{
    if (qh)
    {
        --(qh->first);
        if (qh->first < 0)
            qh->first = MAX_MSG - 1;
    }
}
