/*
**	LineDlink.h
**	text line dlink.
**
**	Jack, 2002/06/19.
*/
#ifndef _LINEDLINK_H_
#define _LINEDLINK_H_




// STRUCTURES //////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct  tagTEXT_LINE_NODE   TEXT_LINE_NODE,*LPTEXT_LINE_NODE;
typedef struct  tagTEXT_LINE_DLINK  TEXT_LINE_DLINK, *LPTEXT_LINE_DLINK;

struct  tagTEXT_LINE_NODE
{
    USTR    text[256];
    SLONG   len;
};

struct  tagTEXT_LINE_DLINK
{
    TEXT_LINE_NODE  *node;
    TEXT_LINE_DLINK *prev, *next;
};


// FUNCTIONS ///////////////////////////////////////////////////////////////////////////////////////////////////////
TEXT_LINE_DLINK *create_text_line_dlink(void);
void    free_text_line_dlink(TEXT_LINE_DLINK *head);
SLONG   append_text_line_node(TEXT_LINE_DLINK *head, TEXT_LINE_NODE *node);
SLONG   count_text_line_nodes(TEXT_LINE_DLINK *head);
TEXT_LINE_NODE  *get_text_line_node(TEXT_LINE_DLINK *head, SLONG node_index);
TEXT_LINE_DLINK *load_text_file(USTR *filename);
//
char**  divide_chine_string(char *src_string, SLONG seg_len, SLONG *segments);




#endif//_LINEDLINK_H_
