/*
**	AccountDetails.cpp
**	account details.
**
**	Jack, 2002/07/23.
*/
#include "mainfun.h"
#include "UIComboBox.h"
#include "AccountDetails.h"
#include "ClientMain.h"


/******************************************************************************************************************/
/* GLOBALS                                                                                                        */
/******************************************************************************************************************/
COMBOBOX    *acc_year_cbb;              //年份
COMBOBOX    *acc_month_cbb;             //月份(12個月)
COMBOBOX    *acc_day_cbb;               //日期
//
COMBOBOX    *acc_occupation_cbb;        //職業
COMBOBOX    *acc_locate_cbb;            //地區
COMBOBOX    **acc_city_cbb;             //城市
SLONG       total_city_cbbs;            //城市CBB的數目(=地區CBB的項目數)


/******************************************************************************************************************/
/* ACCOUNT DETAILS FUNCTIONS                                                                                      */
/******************************************************************************************************************/
int     init_account_details(void)
{
    acc_year_cbb = NULL;
    acc_month_cbb = NULL;
    acc_day_cbb = NULL;
    acc_occupation_cbb = NULL;
    acc_locate_cbb = NULL;
    acc_city_cbb = NULL;
    total_city_cbbs = 0;
    //
    acc_year_cbb = create_year_cbb(1900, 2050);
    if(NULL == acc_year_cbb)
        return  -1;
    acc_month_cbb = create_month_cbb(1, 12);
    if(NULL == acc_month_cbb)
        return  -2;
    acc_day_cbb = create_day_cbb(1, 31);
    if(NULL == acc_day_cbb)
        return  -3;
    acc_occupation_cbb = create_occupation_cbb();
    if(NULL == acc_occupation_cbb)
        return  -4;
    acc_locate_cbb = create_locate_cbb(&total_city_cbbs, &acc_city_cbb);
    if(NULL == acc_locate_cbb)
        return  -5;

    return  0;
}


void    free_account_details(void)
{
    SLONG   i;

    if(acc_year_cbb)
    {
        destroy_combobox(acc_year_cbb);
        acc_year_cbb = NULL;
    }
    if(acc_month_cbb)
    {
        destroy_combobox(acc_month_cbb);
        acc_month_cbb = NULL;
    }
    if(acc_day_cbb)
    {
        destroy_combobox(acc_day_cbb);
        acc_day_cbb = NULL;
    }
    if(acc_city_cbb)
    {
        for(i=0; i<total_city_cbbs; i++)
        {
            if(acc_city_cbb[i])
            {
                destroy_combobox(acc_city_cbb[i]);
                acc_city_cbb[i] = NULL;
            }
        }
        free(acc_city_cbb);
        acc_city_cbb = NULL;
        total_city_cbbs = 0;
    }
    if(acc_locate_cbb)
    {
        destroy_combobox(acc_locate_cbb);
        acc_locate_cbb = NULL;
    }
}


COMBOBOX*   get_year_cbb(void)
{
    return  acc_year_cbb;
}


COMBOBOX*   get_month_cbb(void)
{
    return  acc_month_cbb;
}


COMBOBOX*   get_day_cbb(void)
{
    return  acc_day_cbb;
}

COMBOBOX*   get_occupation_cbb(void)
{
    return  acc_occupation_cbb;
}


COMBOBOX*   get_locate_cbb(void)
{
    return  acc_locate_cbb;
}


COMBOBOX*   get_city_cbb(SLONG locate_index)
{
    return  acc_city_cbb[locate_index];
}


SLONG       get_total_city_cbbs(void)
{
    return  total_city_cbbs;
}

/******************************************************************************************************************/
/* MISC FUNCTIONS                                                                                                 */
/******************************************************************************************************************/
SLONG   is_yun_year(SLONG year)
{
    if(year % 4)
        return  FALSE;
    if(year % 100)
        return  TRUE;
    return  FALSE;
}


SLONG   get_month_days(SLONG year, SLONG month)
{
    static  SLONG   days[2][12] = 
    {
        {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
        {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
    };
    SLONG   yun;

    yun = is_yun_year(year);
    return  days[yun][month-1];
}


COMBOBOX*   create_year_cbb(SLONG start_year, SLONG end_year)
{
    COMBOBOX    *lpcbb = NULL;
    USTR    info[32];
    SLONG   i, year, total_years;

    if(NULL == (lpcbb = create_combobox()))
        return  NULL;

    year = NOT_SPECIFIED_YEAR;
    sprintf((char *)info, "----");
    add_combobox_item(lpcbb, (USTR*)info, year);

    total_years = end_year - start_year + 1;
    for(i=0; i<total_years; i++)
    {
        year = start_year + i;
        sprintf((char *)info, "%04d", year);
        add_combobox_item(lpcbb, (USTR*)info, year);
    }
    return  lpcbb;
}


COMBOBOX*   create_month_cbb(SLONG start_month, SLONG end_month)
{
    COMBOBOX    *lpcbb = NULL;
    USTR    info[32];
    SLONG   month, i, total_months;

    if(NULL == (lpcbb = create_combobox()))
        return  NULL;

    month = NOT_SPECIFIED_MONTH;
    sprintf((char *)info, "--");
    add_combobox_item(lpcbb, (USTR*)info, month);

    total_months = end_month - start_month + 1;
    for(i=0; i<total_months; i++)
    {
        month = start_month + i;
        sprintf((char *)info, "%02d", month);
        add_combobox_item(lpcbb, (USTR*)info, month);
    }
    return  lpcbb;
}



COMBOBOX*   create_day_cbb(SLONG start_day, SLONG end_day)
{
    COMBOBOX    *lpcbb = NULL;
    USTR    info[32];
    SLONG   day, i, total_days;

    if(NULL == (lpcbb = create_combobox()))
        return  NULL;

    day = NOT_SPECIFIED_DAY;
    sprintf((char *)info, "--");
    add_combobox_item(lpcbb, (USTR*)info, day);

    total_days = end_day - start_day + 1;
    for(i=0; i<total_days; i++)
    {
        day = start_day + i;
        sprintf((char *)info, "%02d", day);
        add_combobox_item(lpcbb, (USTR*)info, day);
    }
    return  lpcbb;
}


COMBOBOX*   create_occupation_cbb(void)
{
    enum {LINE_BUFFER_SIZE = 1024};
    COMBOBOX    *lpcbb = NULL;
    USTR    line[LINE_BUFFER_SIZE];
    USTR    *file_buf = NULL, *str = NULL;
    SLONG   file_size, buffer_index, len, index, pass, result;
    SLONG   occupation_index;

    if(NULL == (lpcbb = create_combobox()))
        return  NULL;

    occupation_index = NOT_SPECIFIED_OCCUPATION;
    add_combobox_item(lpcbb, (USTR*)"----", occupation_index);

    set_data_file(packed_data_file);
    file_size = load_file_to_buffer((USTR*)"data\\occupate.ini", &file_buf);
    if(file_size < 0)
        return  lpcbb;

    pass = 0;
    buffer_index = 0;
    result = get_buffer_line((char*)file_buf, &buffer_index, file_size, (char*)line, LINE_BUFFER_SIZE);
    while((result == TTN_OK) && (pass == 0))
    {
        len = (SLONG)strlen((const char*)line);
        if( (line[0] != 0x00) && (line[0] != ';') )
        {
            index = 0;

            occupation_index = get_buffer_number(line, &index);
            str = get_buffer_string(line, &index);
            add_combobox_item(lpcbb, (USTR*)str, occupation_index);
        }
        result = get_buffer_line((char*)file_buf, &buffer_index, file_size, (char*)line, LINE_BUFFER_SIZE);
    }
    
    if(file_buf) free(file_buf);
    
    return  lpcbb;
}


COMBOBOX*   create_locate_cbb(SLONG *locates, COMBOBOX ***city_cbb)
{
    enum {LINE_BUFFER_SIZE = 1024};
    COMBOBOX    *lplocate_cbb = NULL;
    COMBOBOX    **lplpcity_cbb = NULL;
    USTR    line[LINE_BUFFER_SIZE];
    USTR    *file_buf = NULL, *str = NULL;
    SLONG   file_size, buffer_index, len, index, pass, result;
    //
    USTR    info[64];
    SLONG   locate_index, city_index, id, last_id;
    SLONG   total_locates, i;


    total_locates = 0;
    if(NULL == (lplocate_cbb = create_combobox()))
    {
        goto _error;
    }
    total_locates = 0;
    locate_index = NOT_SPECIFIED_LOCATE;
    add_combobox_item(lplocate_cbb, (USTR*)"----", locate_index);
    total_locates ++;

    set_data_file(packed_data_file);
    file_size = load_file_to_buffer((USTR*)"data\\locate.ini", &file_buf);
    if(file_size < 0)
    {
        goto _error;
    }

    // count total locates ------------------------------------------
    pass = 0;
    buffer_index = 0;
    result = get_buffer_line((char*)file_buf, &buffer_index, file_size, (char*)line, LINE_BUFFER_SIZE);
    while((result == TTN_OK) && (pass == 0))
    {
        len = (SLONG)strlen((const char*)line);
        if( (line[0] != 0x00) && (line[0] != ';') )
        {
            index = 0;
            if(1 == get_buffer_number(line, &index))
                total_locates++;
        }
        result = get_buffer_line((char*)file_buf, &buffer_index, file_size, (char*)line, LINE_BUFFER_SIZE);
    }
    if(total_locates == 0)
    {
        goto _error;
    }

    // create city cbbs ---------------------------------------------
    lplpcity_cbb = (COMBOBOX **)malloc(sizeof(COMBOBOX*) * total_locates);
    for(i=0; i<total_locates; i++)
    {
        lplpcity_cbb[i] = NULL;
    }
    for(i=0; i<total_locates; i++)
    {
        if(NULL == (lplpcity_cbb[i] = create_combobox()))
            return  NULL;
        city_index = NOT_SPECIFIED_CITY;
        sprintf((char *)info, "----");
        add_combobox_item(lplpcity_cbb[i], (USTR*)info, city_index);
    }


    // process locates and cities -----------------------------------
    pass = 0;
    buffer_index = 0;
    last_id = 0;
    locate_index = 0 + 1;   //for skip '----' (NOT_SPECIFIED_LOCATE).
    result = get_buffer_line((char*)file_buf, &buffer_index, file_size, (char*)line, LINE_BUFFER_SIZE);
    while((result == TTN_OK) && (pass == 0))
    {
        len = (SLONG)strlen((const char*)line);
        if( (line[0] != 0x00) && (line[0] != ';') )
        {
            index = 0;

            id = get_buffer_number(line, &index);
            str = get_buffer_string(line, &index);
            switch(id)
            {
            case 1: //locate
                add_combobox_item(lplocate_cbb, (USTR*)str, locate_index);
                locate_index ++;
                city_index = 0;
                break;
            case 2: //city
                if(locate_index > 0)
                {
                    add_combobox_item(lplpcity_cbb[locate_index-1], (USTR*)str, city_index);
                    city_index++;
                }
                break;
            }
        }
        result = get_buffer_line((char*)file_buf, &buffer_index, file_size, (char*)line, LINE_BUFFER_SIZE);
    }
    if(file_buf) free(file_buf);

    //ok, process all data successful.
    *city_cbb = lplpcity_cbb;
    *locates = total_locates;
    return  lplocate_cbb;

_error:
    if(file_buf) free(file_buf);
    if(lplpcity_cbb)
    {
        for(i=0; i<total_locates; i++)
        {
            if(lplpcity_cbb[i])
            {
                destroy_combobox(lplpcity_cbb[i]);
            }
        }
        free(lplpcity_cbb);
    }
    if(lplocate_cbb)
    {
        destroy_combobox(lplocate_cbb);
    }
    return  NULL;
}



