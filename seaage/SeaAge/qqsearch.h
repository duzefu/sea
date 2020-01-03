/*
 * qqsearch.h
 * functions for qq friend search
 * Zhang Zhaohui
 * 2002.10.14
 */

#ifndef QQSEARCH_H_
#define QQSEARCH_H_
#include "mainfun.h"
#include "clientmain.h"
#include "qqfriend.h"


//#define LOCAL_RUN

#ifdef LOCAL_RUN
#define MAX_SEARCH_DATA_LIST        30
#endif

#define MAX_SEARCH_LIST        1000
/*
 * Structure use for stores search infomation.
 */
typedef struct tagUI_QQSEARCH_FILTER
{
    USTR    name[32];
    USTR    nickname[32];
    USTR    guild_name[32];
    USTR    country;
    DWORD    level;
}UI_QQSEARCH_FILTER, *LPUI_QQSEARCH_FILTER;


typedef struct tagUI_QQ_SEARCH_ITEM
{
    DWORD    index;
    char    name[32];
    char    guild_name[32];
    char    level;
}UI_QQ_SEARCH_ITEM, *LPUI_QQ_SEARCH_ITEM;

/*
 * Structure for stores search infomation
 *
 */
typedef struct tagUI_QQSEARCH_SEARCH
{
    SLONG totol_list;

    LPUI_QQFRIEND p;

}UI_QQSEARCH_SEARCH, *LPUI_QQSEARCH_SEARCH;

/////////////// FUNCTIONS  ////////////////////////////////


SLONG init_qq_search(void);
void  free_qq_search(void);
SLONG qq_search(LPUI_QQSEARCH_FILTER filter);
SLONG qq_search_again(LPUI_QQSEARCH_FILTER filter);
SLONG qq_search_online(void);
SLONG qq_search_online_again(void);
SLONG qq_search_count(void);
void  qq_search_clear(void);
LPUI_QQFRIEND qq_search_get(SLONG index);
SLONG qq_search_add(LPUI_QQFRIEND p);
void  qq_search_set_index(DWORD index);
DWORD qq_search_get_index(void); 

#endif    /* QQSEARCH_H_ */
