/*
**	LineDlink.cpp
**	text line dlink.
**
**	Jack, 2002/06/19.
*/
#include "mainfun.h"
#include "LineDlink.h"
#include "ErrorMsg.h"

/******************************************************************************************************************/
/* TEXT LINE DLINK FUNCTIONS                                                                                      */
/******************************************************************************************************************/
TEXT_LINE_DLINK *create_text_line_dlink(void)
{
    TEXT_LINE_DLINK *tmp = NULL;

    if(NULL == (tmp = (TEXT_LINE_DLINK *)malloc(sizeof(TEXT_LINE_DLINK))))
        return  NULL;
    tmp->node = NULL;
    tmp->prev = NULL;
    tmp->next = NULL;
    return  (TEXT_LINE_DLINK*)tmp;
}


void    free_text_line_dlink(TEXT_LINE_DLINK *head)
{
    TEXT_LINE_DLINK *p, *s;

    p = head;
    while(p)
    {
        s = p;
        p = p->next;

        if(s->node) free(s->node);
        free(s);
    }
}


SLONG   append_text_line_node(TEXT_LINE_DLINK *head, TEXT_LINE_NODE *node)
{
    TEXT_LINE_DLINK *p = NULL, *s = NULL;
    TEXT_LINE_NODE  *n = NULL;

    p = head;
    while(p->next) p = p->next;

    if(NULL == (s = (TEXT_LINE_DLINK*)malloc(sizeof(TEXT_LINE_DLINK))))
        goto _error;
    if(NULL == (n = (TEXT_LINE_NODE*)malloc(sizeof(TEXT_LINE_NODE))))
        goto _error;
    *n = *node;
    s->node = n;
    s->prev = p;
    s->next = NULL;
    p->next = s;
    return  TTN_OK;

_error:
    if(s) free(s);
    if(n) free(n);
    return  TTN_NOT_OK;
}


SLONG   count_text_line_nodes(TEXT_LINE_DLINK *head)
{
    TEXT_LINE_DLINK *p;
    SLONG   nodes;

    p = head;
    nodes = 0;
    while(p->next)
    {
        nodes++;
        p = p->next;
    }
    return  nodes;
}


TEXT_LINE_NODE  *get_text_line_node(TEXT_LINE_DLINK *head, SLONG node_index)
{
    TEXT_LINE_DLINK *p;

    p = head;
    node_index;
    while(p->next && node_index >= 0)
    {
        p = p->next;
        node_index--;
    }
    if(node_index == -1)
        return  p->node;
    else
        return  NULL;
}


TEXT_LINE_DLINK *load_text_file(USTR *filename)
{
    enum {LINE_BUFFER_SIZE = 256};
    PACK_FILE    *fp=NULL;
    USTR    *file_buf = NULL;
    SLONG   file_size;
    USTR    line[LINE_BUFFER_SIZE];
    SLONG   result, buffer_index, len, copy_len, pass;
    TEXT_LINE_NODE  node;
    TEXT_LINE_DLINK *dlink = NULL;

    if(NULL == (fp = pack_fopen((const char *)filename, "rb")))
    {
        errormsg_file_open((char *)filename);
        goto error;
    }
    file_size = pack_fsize(fp);
    if(NULL == (file_buf = (USTR*)malloc(file_size)))
    {
        errormsg_memory();
        goto error;
    }
    pack_fread(file_buf, 1, file_size, fp);
    pack_fclose(fp);

    dlink = create_text_line_dlink();
    if(NULL == dlink)
        goto error;

    buffer_index = 0;
    pass = 0;
    result = get_buffer_line((char*)file_buf, &buffer_index, file_size, (char*)line, LINE_BUFFER_SIZE);
    while((result == TTN_OK) && (pass == 0))
    {
        len = (SLONG)strlen((const char *)line);
        if( (line[0] != 0x00) && (line[0] != ';') )
        {
            copy_len = min(255, len);
            memcpy(node.text, line, copy_len);
            node.text[copy_len] = 0x00;
            node.len = copy_len;
            append_text_line_node(dlink, &node);
        }
        result = get_buffer_line((char*)file_buf, &buffer_index, file_size, (char*)line, LINE_BUFFER_SIZE);
    }

    if(file_buf) free(file_buf);
    
    return dlink;
error:
    if(file_buf) free(file_buf);
    if(dlink) free_text_line_dlink(dlink);
    return NULL;
}


/******************************************************************************************************************/
/* MISC FUNCTIONS                                                                                                 */
/******************************************************************************************************************/
//〈TODO: 把σ CharUpper, CharLower, CharNext, CharPrev 单ㄧ计.
//        硂ㄇㄧ计矪瞶いゅ㎝璣ゅ睼逼﹃.
//
//BIG5->GB:
//沮ㄢㄧ计秈︽BIG5->GB ㎝ GB->BIG5 锣传.
// MultiByteToWideChar(950, 0, (LPCSTR)src_str, -1, (LPWSTR)wide_dest, len / sizeof(WCHAR));
// WideCharToMultiByte(936, 0, (LPWSTR)wide_dest, -1, (LPCSTR)src_str, len / sizeof(CHAR), NULL, NULL);

char**  divide_chine_string(char *str, SLONG seg_len, SLONG *segments)
{
    static  char *  seg_str[32];        //max divide segments is 32.
    static  char    whole_str[1024];    //total length of the string.
    SLONG   clip, start, index, divide_total;

    index = start = 0;
    divide_total = 0;
    clip = find_word_clip_position((char *)str, start, seg_len);
    while(clip >= 0)
    {
        memcpy((char *)&whole_str[index], (const char *)&str[start], clip-start);
        whole_str[index + clip - start] = 0x00;
        seg_str[divide_total] = (char *)&whole_str[index];
        index += clip-start+1;
        divide_total ++;
        if(divide_total == 32)
            break;

        start = clip;
        clip = find_word_clip_position((char *)str, start, seg_len);
    }
    *segments = divide_total;
    return  (char **)seg_str;
}


