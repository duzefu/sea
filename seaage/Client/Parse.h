/*
**  parse.h
**  cmd string parse functions header.
**
**  geaan, 2001.7.16.
*/
#ifndef _PARSE_H_
#define _PARSE_H_


// D E F I N E S ///////////////////////////////////////////////////////////////////////////////////////////////////
//訊息分析結果類型
#define PARSE_TYPE_NONE         0   //無意義
#define PARSE_TYPE_TALK         1   //聊天訊息
#define PARSE_TYPE_WEATHER      2   //改變天氣


// S T R U C T U R E S /////////////////////////////////////////////////////////////////////////////////////////////
//訊息分析結果
typedef struct tagPARSE_RESULT 
{
    SLONG   type;       //訊息分析結果類型
    struct              //聊天訊息
    {
        SLONG   doing_kind;
        SLONG   reserved[4];
    } talk;
    
    struct              //改變天氣資料 
    {
        SLONG   type;       //指定要下哪種天氣的種類 
        SLONG   active;     //開始,清除,結束
        SLONG   size;       //大小 
        SLONG   wind_size;  //風向大小 
        SLONG   wind_dir;   //風向方向
    } weather;
} PARSE_RESULT, *LPPARSE_RESULT;


// G L O B A L S ///////////////////////////////////////////////////////////////////////////////////////////////////
extern  SLONG	        god_mode_enable;
extern  PARSE_RESULT    parse_result;


// F U N C T I O N S ///////////////////////////////////////////////////////////////////////////////////////////////
extern  void    clear_parse_result(void);
extern  SLONG   parse_chat_input(USTR *input_string);


#endif//_PARSE_H_

