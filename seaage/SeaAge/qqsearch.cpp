/*
 * qqfriend.cpp
 * functions for qq friend search
 * Zhang Zhaohui
 * 2002.10.14
 */

#include "qqsearch.h"
#include "qqclient.h"


UI_QQSEARCH_SEARCH        g_search_friend;
LPUI_QF_LIST            g_friend_search = NULL;
LPUI_QQSEARCH_FILTER    g_friend_search_filter = NULL;
DWORD                    g_index;
/*
 * init_qq_search:
 *        initialize search
 */
SLONG init_qq_search(void)
{
    g_search_friend.p = (LPUI_QQFRIEND)LocalAlloc(LPTR, MAX_SEARCH_LIST*sizeof(UI_QQFRIEND));
    if (!g_search_friend.p)
        return TTN_NOT_OK;

    qq_search_clear();
    qq_search_set_index(0);
    return TTN_OK;
}

/*
 * free_qq_search:
 *        free search
 */
void free_qq_search(void)
{
    if (g_search_friend.p)
    {
        LocalFree(g_search_friend.p);
        g_search_friend.p = NULL;
    }
}


/*
 * qq_search_count:
 *        return how many friend info has been searched
 */
SLONG qq_search_count(void)
{
    return g_search_friend.totol_list;
}


/*
 * qq_search_clear:
 *        clear search result
 */
void  qq_search_clear(void)
{
    ZeroMemory(g_search_friend.p, MAX_SEARCH_LIST*sizeof(UI_QQFRIEND));
    g_search_friend.totol_list = 0;
}


/*
 * qq_search:
 *        search friends from server
 */
SLONG qq_search(LPUI_QQSEARCH_FILTER filter)
{
    if (qq_search_count() > 0)
        qq_search_clear();

    qq_search_set_index(0);
#ifdef LOCAL_RUN
    char filename[MAX_PATH];
    char line[260];
    USTR *file_buf;
    LPUI_QQFRIEND p = NULL;
    SLONG file_size, i, result, buffer_index;
    SLONG index;

    set_data_file(packed_data_file);
    sprintf(filename, "data\\friends.txt");
    file_size = load_file_to_buffer((USTR*)filename, &file_buf);
    if (file_size < 0)
        return TTN_NOT_OK;

    if ((p = qf_new()) == NULL)
    {
        free(file_buf);
        return TTN_NOT_OK;
    }

    buffer_index = 0;
    
    for (i = 0; i < MAX_SEARCH_DATA_LIST; i++)
    {
        result = get_buffer_line((char*)file_buf, &buffer_index, file_size, line, 260);
        if (result != TTN_OK)
            break;
        index = 0;
        get_buffer_string((USTR*)line, &index);
        strcpy((char*)p->name,            (const char*)get_buffer_string((USTR*)line, &index));
        strcpy((char*)p->nickname,        (const char*)get_buffer_string((USTR*)line, &index));
        strcpy((char*)p->guild_name,    (const char*)get_buffer_string((USTR*)line, &index));
        strcpy((char*)p->partner_name,    (const char*)get_buffer_string((USTR*)line, &index));

        get_buffer_string((USTR*)line, &index);
//        strcpy((char*)p->country,        (const char*)get_buffer_string((USTR*)line, &index));


        p->pk            = get_buffer_number((USTR*)line, &index);
        p->money        = get_buffer_number((USTR*)line, &index);
        p->prestige        = get_buffer_number((USTR*)line, &index);
        p->level        = get_buffer_number((USTR*)line, &index);
        p->icon_index    = get_buffer_number((USTR*)line, &index);
        p->settings        = 0;//get_buffer_number((USTR*)line, &index);

        if (filter)
        {
            if (filter->name[0] != '\0')
                if (CompareString(LOCALE_SYSTEM_DEFAULT,
                                0, (LPCSTR)filter->name,
                                -1, (LPCSTR)p->name, -1) != CSTR_EQUAL)
                    continue;
            if (filter->nickname[0] != '\0')
                if (CompareString(LOCALE_SYSTEM_DEFAULT,
                                0, (LPCSTR)filter->nickname,
                                -1, (LPCSTR)p->nickname, -1) != CSTR_EQUAL)
                    continue;
            if (filter->guild_name[0] != '\0')
                if (CompareString(LOCALE_SYSTEM_DEFAULT,
                                0, (LPCSTR)filter->guild_name,
                                -1, (LPCSTR)p->guild_name, -1) != CSTR_EQUAL)
                    continue;
/*            if (filter->country[0] != '\0')
                if (CompareString(LOCALE_SYSTEM_DEFAULT,
                                0, (LPCSTR)filter->country,
                                -1, (LPCSTR)p->country, -1) != CSTR_EQUAL)
                    continue;
*/

            if (filter->level)
                if (filter->level != p->level)
                    continue;
        }
        qq_search_add(p);
    }

    free(file_buf);
    qf_free(p);
    return TTN_OK;
#else    /* LOCAL_RUN */

    // TODO: ADD SEARCH INDEX
    return qq_client_request_query_add_list(filter);

#endif  /* LOCAL_RUN */

}


/*
 * qq_search_again:
 *        search again
 */
SLONG qq_search_again(LPUI_QQSEARCH_FILTER filter)
{
    // TODO: ADD SEARCH INDEX
    return qq_client_request_query_add_list(filter);
}

SLONG qq_search_online(void)
{
    qq_search_clear();
    qq_search_set_index(0);
    return qq_client_request_query_online_addlist();
}

SLONG qq_search_online_again(void)
{
    return qq_client_request_query_online_addlist();
}

/*
 * qq_search_get
 *        return specify friend search info
 */
LPUI_QQFRIEND qq_search_get(SLONG index)
{
    if (index < g_search_friend.totol_list)
    {
        return &g_search_friend.p[index];
    }

    return NULL;
}


/*
 * qq_search_add:
 *        add a search result to search list
 */
SLONG qq_search_add(LPUI_QQFRIEND p)
{
    if( g_search_friend.totol_list < MAX_SEARCH_LIST)
    {
        memcpy(&g_search_friend.p[g_search_friend.totol_list], p, sizeof(UI_QQFRIEND));
        g_search_friend.totol_list++;
        return TTN_OK;
    }

    return TTN_NOT_OK;
}

void  qq_search_set_index(DWORD index)
{
    g_index = index;
}


DWORD qq_search_get_index(void)
{
    return g_index;
}
