/*
**  parse.h
**  cmd string parse functions header.
**
**  geaan, 2001.7.16.
*/
#ifndef _PARSE_H_
#define _PARSE_H_


// D E F I N E S ///////////////////////////////////////////////////////////////////////////////////////////////////
//�T�����R���G����
#define PARSE_TYPE_NONE         0   //�L�N�q
#define PARSE_TYPE_TALK         1   //��ѰT��
#define PARSE_TYPE_WEATHER      2   //���ܤѮ�


// S T R U C T U R E S /////////////////////////////////////////////////////////////////////////////////////////////
//�T�����R���G
typedef struct tagPARSE_RESULT 
{
    SLONG   type;       //�T�����R���G����
    struct              //��ѰT��
    {
        SLONG   doing_kind;
        SLONG   reserved[4];
    } talk;
    
    struct              //���ܤѮ��� 
    {
        SLONG   type;       //���w�n�U���ؤѮ𪺺��� 
        SLONG   active;     //�}�l,�M��,����
        SLONG   size;       //�j�p 
        SLONG   wind_size;  //���V�j�p 
        SLONG   wind_dir;   //���V��V
    } weather;
} PARSE_RESULT, *LPPARSE_RESULT;


// G L O B A L S ///////////////////////////////////////////////////////////////////////////////////////////////////
extern  SLONG	        god_mode_enable;
extern  PARSE_RESULT    parse_result;


// F U N C T I O N S ///////////////////////////////////////////////////////////////////////////////////////////////
extern  void    clear_parse_result(void);
extern  SLONG   parse_chat_input(USTR *input_string);


#endif//_PARSE_H_

