/*
**  FreeProcess.h
**  free process functions.
**
**  Jack, 2002.5.15.
*/
#ifndef _FREEPROCESS_H_
#define _FREEPROCESS_H_

//DEFINES /////////////////////////////////////////////////////////////////////////////////////////
#define MAX_FREE_PROCESS        32


//STRUCTURES //////////////////////////////////////////////////////////////////////////////////////
typedef struct  tagFREE_PROCESS_STACK
{
    void    (*func[MAX_FREE_PROCESS])(void);
    SLONG   top;
} FREE_PROCESS_STACK, *LPFREE_PROCESS_STACK;


//GLOBALS /////////////////////////////////////////////////////////////////////////////////////////
extern  FREE_PROCESS_STACK  free_process_stack;

//FUNCTIONS ///////////////////////////////////////////////////////////////////////////////////////
void    init_free_process(void);
void    push_free_process(void (*func)(void));
void    exec_free_process(void);
//



#endif//_FREEPROCESS_H_
