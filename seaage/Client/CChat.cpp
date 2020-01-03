/*
**  CChat.cpp
**  class chat functions.
**
**  ZJian,2001.4.21.
*/
#include "mainfun.h"
#include "CChat.h"



//#define DEBUG_CHAT        1   //將 CHAT 內容同時寫入磁碟機


CChat   game_chat;

/******************************************************************************************************************/
/* CCHAT MAIN FUNCTIONS                                                                                           */
/******************************************************************************************************************/
CChat::CChat()
{
    this->clear();
    this->clear_input();
}


CChat::~CChat()
{
}


void    CChat::clear(void)
{
    SLONG i;

    this->next = 0;
    for(i=0;i<CHAT_NUM;i++)
    {
        this->flag[i] = 0;
        this->tick[i] = 0;
        this->effect[i] = 0;
        memset((void*)this->str[i], '\0', CHAT_LEN);
    }
}


void    CChat::add(SLONG effect, USTR *string)
{
    SLONG next;

    // add this string 
    next = this->next;
    strcpy((char *)this->str[next],(const char *)string);
    this->flag[next] = 1;
    this->tick[next] = CHAT_STAY;
    this->effect[next] = effect;
    this->next = (next+1) % CHAT_NUM;

    // clear forehead
    next = (this->next + CHAT_SHOWS) % CHAT_NUM;
    this->flag[next] = 0;
    this->tick[next] = 0;
    this->effect[next] = 0;
    memset((void*)this->str[next],'\0',CHAT_LEN);

#ifdef  DEBUG_CHAT
    log_error(1,string);
#endif//DEBUG_CHAT
}


void    CChat::refresh(void)
{
    SLONG i;

    for(i=0; i<CHAT_NUM; i++)
    {
        if(this->flag[i])
        {
            this->tick[i]--;
            if(this->tick[i]<0)
                this->tick[i]=0;
        }
    }
}


void	CChat::hide_all(void)
{
	SLONG	i;

	for(i=0; i<CHAT_NUM; i++)
	{
		this->tick[i] = 0;
	}
}


void    CChat::refresh2(void)
{
    static SLONG count = 0;
    SLONG next;

    count++;
    if(count > CHAT_STAY)
    {
        // scroll chats
        next = this->next;
        this->next = (next + 1) % CHAT_NUM;

        // clear forehead
        next = (this->next + CHAT_SHOWS) % CHAT_NUM;
        this->flag[next] = 0;
        memset((void*)this->str[next],'\0',CHAT_LEN);

        count = 0;
    }
}

void    CChat::redraw(void *vbitmap)
{
    SLONG i, index;
    SLONG sx,sy, bar_sx, bar_sy, bar_xl, bar_yl;
    BMP *bitmap = (BMP*)vbitmap;
    USTR disp_rec[512];

    // Jack, for SEA. [15:32,9/13/2002]
    //this->refresh();

    //redraw background --------------------------------------------------------------------
    bar_sy = CHAT_SY + abs(CHAT_DY) + CHAT_SHOWS * CHAT_DY - 4;
    bar_sx = CHAT_SX - 4;
    bar_xl = 80 * 6 + 4 * 2;    //40個漢字的寬度 + 4 PIXELS 的邊空 * 2.
    bar_yl = CHAT_SHOWS * abs(CHAT_DY) + 8;
    alpha_put_form(bar_sx, bar_sy, bar_xl, bar_yl, SYSTEM_BLUE, bitmap, 80);
    //alpha_put_bar(bar_sx, bar_sy, bar_xl, bar_yl, SYSTEM_BLUE, bitmap, 80);

    //redraw chat text ---------------------------------------------------------------------
    sy = CHAT_SY;
    sx = CHAT_SX;
    for(i=0; i<CHAT_SHOWS; i++)
    {
        // draw chat str from the lasted one to before...
        index = (this->next -1 -i + CHAT_NUM) % CHAT_NUM;
        if( this->flag[index] && (this->tick[index] > 0) )
        {
            switch(this->effect[index])
            {
            case CHATEFF_WHITE:
                sprintf((char *)disp_rec,"~C0~O0%s~C0~O0",this->str[index]);
                print12(sx,sy,(USTR*)disp_rec,PEST_PUT,(BMP*)bitmap);
                break;
            case CHATEFF_RED:
                sprintf((char *)disp_rec,"~C1~O0%s~C0~O0",this->str[index]);
                print12(sx,sy,(USTR*)disp_rec,PEST_PUT,(BMP*)bitmap);
                break;
            case CHATEFF_GREEN:
                sprintf((char *)disp_rec,"~C2~O0%s~C0~O0",this->str[index]);
                print12(sx,sy,(USTR*)disp_rec,PEST_PUT,(BMP*)bitmap);
                break;
            case CHATEFF_BLUE:
                sprintf((char *)disp_rec,"~C3~O0%s~C0~O0",this->str[index]);
                print12(sx,sy,(USTR*)disp_rec,PEST_PUT,(BMP*)bitmap);
                break;
            case CHATEFF_YELLOW:
                sprintf((char *)disp_rec,"~C4~O0%s~C0~O0",this->str[index]);
                print12(sx,sy,(USTR*)disp_rec,PEST_PUT,(BMP*)bitmap);
                break;
            case CHATEFF_CYAN:
                sprintf((char *)disp_rec,"~C5~O0%s~C0~O0",this->str[index]);
                print12(sx,sy,(USTR*)disp_rec,PEST_PUT,(BMP*)bitmap);
                break;
            case CHATEFF_PINK:
                sprintf((char *)disp_rec,"~C6~O0%s~C0~O0",this->str[index]);
                print12(sx,sy,(USTR*)disp_rec,PEST_PUT,(BMP*)bitmap);
                break;
            default:
                sprintf((char *)disp_rec,"%s",this->str[index]);
                print12(sx,sy,(USTR*)disp_rec,PEST_PUT,(BMP*)bitmap);
                break;
            }
        }
        sy += CHAT_DY;
    }
}


void    CChat::clear_input(void)
{
    SLONG i;

    this->input_next = 0;
    for(i=0;i<CHAT_INPUT_NUM;i++)
    {
        this->input_effect[i] = 0;
        memset((void*)this->input_str[i], '\0', CHAT_LEN);
    }
    this->input_next = 0;
    this->input_get = 0;
}


void    CChat::add_input(SLONG effect, USTR *string)
{
    SLONG i;

    if(this->input_next > 0)
    {
        if(0 == strcmpi((const char *)this->input_str[this->input_next-1], (const char *)string))
        {
            this->input_get = this->input_next-1;
            return;
        }
    }

    if(this->input_next == CHAT_INPUT_NUM)
    {
        for(i=0; i<CHAT_INPUT_NUM-1; i++)
        {
            memcpy(this->input_str[i], this->input_str[i+1], CHAT_LEN);
            this->input_effect[i] = this->input_effect[i+1];
        }
        strcpy((char *)this->input_str[CHAT_INPUT_NUM-1],(const char *)string);
        this->input_effect[CHAT_INPUT_NUM-1] = effect;
    }
    else
    {
        strcpy((char *)this->input_str[this->input_next],(const char *)string);
        this->input_effect[this->input_next] = effect;
        this->input_next++;
    }
    this->input_get = this->input_next-1;

#ifdef  DEBUG_CHAT
    log_error(1,string);
#endif//DEBUG_CHAT
}


SLONG   CChat::get_prev_input(SLONG *effect, USTR *string, SLONG enable_loop)
{
    if(this->input_next <= 0)
        return  TTN_NOT_OK;

    strcpy((char *)string, (const char *)this->input_str[this->input_get]);
    if(effect) *effect = this->input_effect[this->input_get];
    this->input_get --;
    if(this->input_get < 0)
    {
        this->input_get = enable_loop ? this->input_next-1 : 0;
    }
    return  TTN_OK;
}


SLONG   CChat::get_next_input(SLONG *effect, USTR *string, SLONG enable_loop)
{
    if(this->input_next <= 0)
        return  TTN_NOT_OK;

    strcpy((char *)string, (const char *)this->input_str[this->input_get]);
    if(effect) *effect = this->input_effect[this->input_get];
    this->input_get ++;
    if(this->input_get > this->input_next-1)
    {
        this->input_get = enable_loop ? 0 : this->input_next-1;
    }
    return  TTN_OK;
}


EXPORT  void    FNBACK  alpha_put_form(SLONG sx, SLONG sy, SLONG xl, SLONG yl, PIXEL color, BMP *bitmap, SLONG alpha)
{
    enum {ALPHA_STEP = 16};
    SLONG   i, out_lines, step_alpha;

    alpha_put_bar(sx, sy, xl, yl, color, bitmap, alpha);
    out_lines = (alpha - 0) / ALPHA_STEP;
    step_alpha = alpha - ALPHA_STEP;
    for(i=1; i<=out_lines; i++)
    {
        alpha_put_bar(sx - i, sy - i, xl + 2*i, 1, color, bitmap, step_alpha);
        alpha_put_bar(sx - i, sy + yl -1 + i, xl + 2*i, 1, color, bitmap, step_alpha);
        alpha_put_bar(sx - i, sy - i + 1, 1, yl + (i-1)*2, color, bitmap, step_alpha);
        alpha_put_bar(sx + xl - 1 + i, sy - i + 1, 1, yl + (i-1)*2, color, bitmap, step_alpha);
        step_alpha -= ALPHA_STEP;
    }
}


