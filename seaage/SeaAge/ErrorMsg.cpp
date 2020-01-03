/*
**  ErrorMsg.cpp
**  error message functions.
**
**  Jack, 2002.5.9.
*/
#include <sys/types.h> 
#include <sys/timeb.h>
#include "mainfun.h"
#include "ImageRim.h"
#include "ErrorMsg.h"
#include "QQMsgBox.h"



void    errormsg_file_open(char *filename)
{
    log_error(1, "file %s open error", filename);
}


void    errormsg_memory(void)
{
    log_error(1, "memory alloc error");
}


void    display_error_message(USTR *message, SLONG flag, void *vbitmap)
{
    enum {FONT_WIDTH = 24};
    BMP *bitmap = (BMP*)vbitmap;
    USTR    info[256];
    SLONG   ll;
    SLONG   x,y;
    SLONG   xl,yl;
    
    ll = strlen((const char *)message);
    y = bitmap->h/2-FONT_WIDTH/2;
    x = bitmap->w/2-((ll+1)/2*FONT_WIDTH/2);
    yl = FONT_WIDTH + FONT_WIDTH;
    xl = (ll+1)/2*FONT_WIDTH + FONT_WIDTH;
    sprintf((char *)info, "~C1%s~C0",(const char *)message);
    put_image_rim(x, y, xl, yl, bitmap);
    print24(x+FONT_WIDTH/2,y+FONT_WIDTH/2,message,PEST_PUT,bitmap);
    switch(flag)
    {
    case DISPLAY_MESSAGE_TO_SCREEN:
        update_screen(bitmap);
        break;
    case DISPLAY_MESSAGE_TO_BUFFER:
        break;
    default:
        break;
    }
}


void    log_encrypt_message(int p, char *strMsg, ...)
{
    static  int     init_flag = 0;
    static  char    strBuffer[2048], strLog[2048];
    char    filename[_MAX_PATH+_MAX_FNAME];
    FILE    *logfile=NULL;
    va_list args;

    if (!p) return;

    va_start(args, strMsg);
    _vsnprintf( strBuffer, 2048, strMsg, args );
    va_end(args);

    sprintf((char*)filename,"%s", "msg.txt");
    if(is_file_exist((USTR*)filename) && init_flag == 0)
    {
        remove((const char *)filename);
        init_flag = 1;
    }
    if( NULL == (logfile = fopen((const char *)filename,"a+")) )
    {
        sprintf(filename,"c:\\%s", "msg.txt");
        if(is_file_exist((USTR*)filename) && init_flag == 0)
        {
            remove((const char *)filename);
            init_flag = 1;
        }
        if(NULL == (logfile = fopen((const char *)filename,"a+")))
            goto _error;
    }

    /*
    struct _timeb timebuffer;
    char *timeline;
    _ftime( &timebuffer );
    timeline = ctime( & ( timebuffer.time ) );
    timeline[24]=0x00;  //&timeline[20] = "2002\0x0d\0x00";
    sprintf((char *)strLog, "%.19s.%03hu %s %s", timeline, timebuffer.millitm, &timeline[20] ,strBuffer);
    */
    struct _timeb timebuffer;
    struct tm *newtime;

    _ftime( &timebuffer );
    newtime = localtime(&timebuffer.time);
    sprintf((char *)strLog, "%04d%02d%02d %02d:%02d:%02d.%03hu  %s", 
        newtime->tm_year+1900, newtime->tm_mon+1, newtime->tm_mday, 
        newtime->tm_hour, newtime->tm_min, newtime->tm_sec, 
        timebuffer.millitm, strBuffer);

    fputs((const char *)strLog, logfile);
    fputs("\n",logfile);
    if(logfile) fclose(logfile);

_error:

#ifdef  DEBUG
    OutputDebugString((LPCTSTR)strBuffer);
    OutputDebugString((LPCTSTR)"\n");
#endif//DEBUG

    return;
}




void display_message(char *title, char *text, DWORD type, DWORD time, DWORD font_size)
{
	UIMSGBOX	mb;
	SLONG		len, copy_len;

	memset(&mb, 0, sizeof(mb));

	len = strlen((const char *)title);
	copy_len = min(len, MB_MAX_TITLE-1);
	memcpy(mb.title_info, title, copy_len);

	len = strlen((const char *)text);
	copy_len = min(len, MB_MAX_CHAR);
	memcpy(mb.text_info, text, copy_len);

	mb.pfunc = NULL;
	mb.msgbox_type = type;
	mb.disp_time = time;
	mb.font_size = font_size;

	msg_box(-1, -1, &mb);
}

