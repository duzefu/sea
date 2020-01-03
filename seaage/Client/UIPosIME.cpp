/*
**	UIPosIME.cpp
**	UI of pos ime functions.
**
**	Jack, 2002/10/18.
*/
#include "mainfun.h"
#include "ClientMain.h"
#include "ErrorMsg.h"


/*
void    pos_redraw_ime(void *vbitmap)
{
    enum    {   IME_FONT_SIZE       =   24   };
    BMP     *bitmap = (BMP*)vbitmap;
    CANDIDATELIST *pCandList = NULL;
    char    *szCompStr = NULL, *szCompReadStr = NULL, *szCandList = NULL;
    SLONG   bar_sx, bar_sy, bar_xl, bar_yl;
    SLONG   disp_x, disp_y, disp_xl, disp_yl;
    char    info[256], tmp[80];
    SLONG   i, len, index;

    if( get_ime_name() )
    {
        get_ime_input( &szCompStr, &szCompReadStr, NULL, &szCandList );

        //(1) background ----------------------------------------------------
        bar_sx = 0;
        bar_sy = bitmap->h - IME_FONT_SIZE - 16;
        bar_xl = bitmap->w;
        bar_yl = IME_FONT_SIZE + 16;
        alpha_put_bar(bar_sx, bar_sy, bar_xl, bar_yl, SYSTEM_BLUE, bitmap, 128);

        //set font color
        print16(0, 0, "~C0", PEST_PUT, bitmap);

        //(2) ime name ------------------------------------------------------
        sprintf((char *)info, "%s/%s", get_ime_name(), is_ime_sharp() ? TEXTMSG_IME_QUANJIAO : TEXTMSG_IME_BANJIAO);
        len = strlen((const char *)info);
        disp_x = bar_sx + bar_xl - len * IME_FONT_SIZE / 2 - 8;
        disp_y = bar_sy + bar_yl / 2 - IME_FONT_SIZE / 2;
        print24( disp_x, disp_y,  (USTR*)info, PEST_PUT, bitmap);
        //sprintf((char *)info, "%s", is_ime_symbol() ? TEXTMSG_IME_CHINESE_PUNCTUATION : TEXTMSG_IME_ENGLISH_PUNCTUATION);
        //print16( IME_SYMBOL_SX, IME_SYMBOL_SY, (USTR*)info, PEST_PUT, bitmap);

        //(3) cand list -----------------------------------------------------

//        if(szCandList)
//        {
//            disp_x = bar_sx + 8;
//            disp_y = bar_sy + bar_yl / 2 - IME_FONT_SIZE / 2;
//            print24( disp_x, disp_y, (USTR*)szCandList, PEST_PUT, bitmap);
//        }

        disp_x = bar_sx + 8;
        disp_y = bar_sy + bar_yl / 2 - IME_FONT_SIZE / 2;
        pCandList = app_ime->g_lpCandList;
        if(pCandList)
        {
            for(i = 0; i < min((SLONG)pCandList->dwCount - (SLONG)pCandList->dwPageStart, (SLONG)pCandList->dwPageSize); i++)
            {
                index = pCandList->dwPageStart+i;
                sprintf((char *)info, "%d.%s", 1 + i, (char*)pCandList + pCandList->dwOffset[index]);
                len = strlen((const char *)info);
                
                if(index == (SLONG)pCandList->dwSelection)
                    sprintf((char *)tmp, "~C4~O3%s~C0~O0", info);
                else
                    sprintf((char *)tmp, "%s", info);
                print24(disp_x, disp_y, (USTR*)tmp, PEST_PUT, bitmap);
                disp_x += 8 + len * IME_FONT_SIZE / 2;
            }
        }


        //(4) comp str ------------------------------------------------------
        if(szCompStr)
        {
            len = strlen((const char *)szCompStr);
            disp_x = bar_sx + 8;
            disp_y = bar_sy - IME_FONT_SIZE - 8;
            disp_xl = len * IME_FONT_SIZE / 2;
            disp_yl = IME_FONT_SIZE;
            alpha_put_bar(disp_x - 8, disp_y - 8, disp_xl + 16, disp_yl + 16, SYSTEM_BLUE, bitmap, 128);
            print24( disp_x, disp_y, (USTR*)szCompStr, PEST_PUT, bitmap);
        }

        //(4) comp read str -------------------------------------------------
        //print16( IME_INPUT_COMP_READ_SX, IME_INPUT_COMP_READ_SY, (USTR*)szCompReadStr, PEST_PUT, bitmap);

        //restore font color.
        print16(0, 0, "~C0", PEST_PUT, bitmap);
    }
}


void    pos_main_game_redraw_ime(void *vbitmap)
{
    enum    {   IME_FONT_SIZE       =   12   };
    BMP     *bitmap = (BMP*)vbitmap;
    CANDIDATELIST *pCandList = NULL;
    char    *szCompStr = NULL, *szCompReadStr = NULL, *szCandList = NULL;
    SLONG   bar_sx, bar_sy, bar_xl, bar_yl;
    SLONG   disp_x, disp_y, disp_xl, disp_yl;
    char    info[256], tmp[80];
    SLONG   i, len, index;
    int     cursor_index;

    if( get_ime_name() )
    {
        get_ime_input( &szCompStr, &szCompReadStr, &cursor_index, &szCandList );

        //(1) background ----------------------------------------------------
        bar_sx = 232;
        bar_sy = bitmap->h - IME_FONT_SIZE - 8;
        bar_xl = bitmap->w - bar_sx;
        bar_yl = bitmap->h - bar_sy; 
        alpha_put_bar(bar_sx, bar_sy, bar_xl, bar_yl, SYSTEM_BLUE, bitmap, 128);

        //set font color
        print12(0, 0, "~C0", PEST_PUT, bitmap);

        //(2) ime name ------------------------------------------------------
        sprintf((char *)info, "%s/%s", get_ime_name(), is_ime_sharp() ? TEXTMSG_IME_QUANJIAO : TEXTMSG_IME_QUANJIAO);
        len = strlen((const char *)info);
        disp_x = bar_sx + bar_xl - len * IME_FONT_SIZE / 2 - 4;
        disp_y = bar_sy + bar_yl / 2 - IME_FONT_SIZE / 2;
        print12( disp_x, disp_y,  (USTR*)info, PEST_PUT, bitmap);
        //sprintf((char *)info, "%s", is_ime_symbol() ? TEXTMSG_IME_CHINESE_PUNCTUATION : TEXTMSG_IME_ENGLISH_PUNCTUATION);
        //print16( IME_SYMBOL_SX, IME_SYMBOL_SY, (USTR*)info, PEST_PUT, bitmap);

        //(3) cand list -----------------------------------------------------
        disp_x = bar_sx + 8;
        disp_y = bar_sy + bar_yl / 2 - IME_FONT_SIZE / 2;
        pCandList = app_ime->g_lpCandList;
        if(pCandList)
        {
            for(i = 0; i < min((SLONG)pCandList->dwCount - (SLONG)pCandList->dwPageStart, (SLONG)pCandList->dwPageSize); i++)
            {
                index = pCandList->dwPageStart+i;
                sprintf((char *)info, "%d%s", 1 + i, (char*)pCandList + pCandList->dwOffset[index]);
                len = strlen((const char *)info);
                
                if(index == (SLONG)pCandList->dwSelection)
                {
                    alpha_put_bar(disp_x-2, disp_y-2, len * IME_FONT_SIZE/2 + 4, 
                        IME_FONT_SIZE + 4, SYSTEM_WHITE, bitmap, 128);
                    sprintf((char *)tmp, "~C4~O8%s~C0~O0", info);
                    print12(disp_x, disp_y, (USTR*)tmp, PEST_PUT, bitmap);
                }
                else
                {
                    sprintf((char *)tmp, "%s", info);
                    print12(disp_x, disp_y, (USTR*)tmp, PEST_PUT, bitmap);
                }
                disp_x += 4 + len * IME_FONT_SIZE / 2;
            }
        }


        //(4) comp str ------------------------------------------------------
        if(szCompStr)
        {
            strcpy((char *)info, (const char *)szCompStr);
            len = strlen((const char *)szCompStr);
            disp_x = bar_sx + 8;
            disp_y = bar_sy - IME_FONT_SIZE - 8;
            disp_xl = len * IME_FONT_SIZE / 2;
            disp_yl = IME_FONT_SIZE;
            alpha_put_bar(disp_x - 8, disp_y - 8, disp_xl + 16, disp_yl + 16, SYSTEM_BLUE, bitmap, 128);
            bar_sx = disp_x + 6 * cursor_index;
            bar_sy = disp_y - 2;
            bar_xl = (len - cursor_index) * 6;
            bar_yl = 12 + 4;
            if(bar_xl > 0)
            {
                alpha_put_bar(bar_sx, bar_sy, bar_xl, bar_yl, SYSTEM_WHITE, bitmap, 128);
                tmp[0] = info[cursor_index];
                info[cursor_index] = 0x00;
                print12( disp_x, disp_y, (USTR*)info, PEST_PUT, bitmap);

                disp_x += cursor_index * 6;
                info[cursor_index] = tmp[0];
                print12(0, 0, (USTR*)"~C4~O8", PEST_PUT, bitmap);
                print12(disp_x, disp_y, (USTR*)&info[cursor_index], PEST_PUT, bitmap);
                print12(0, 0, (USTR*)"~C0~O0", PEST_PUT, bitmap);
            }
            else
            {
                print12( disp_x, disp_y, (USTR*)szCompStr, PEST_PUT, bitmap);
            }
        }

        //(4) comp read str -------------------------------------------------
        //print16( IME_INPUT_COMP_READ_SX, IME_INPUT_COMP_READ_SY, (USTR*)szCompReadStr, PEST_PUT, bitmap);

        //restore font color.
        print12(0, 0, "~C0", PEST_PUT, bitmap);
    }

}
*/
