/*
**	AccountDetails.h
**	account details.
**
**	Jack, 2002/07/23.
*/
#ifndef _ACCOUNTDETAILS_H_
#define _ACCOUNTDETAILS_H_


// DEFINES /////////////////////////////////////////////////////////////////////////////////////////////////////////
#define NOT_SPECIFIED_YEAR              -1      //未指定年
#define NOT_SPECIFIED_MONTH             -1      //未指定月
#define NOT_SPECIFIED_DAY               -1      //未指定日
#define NOT_SPECIFIED_OCCUPATION        -1      //未指定職業
#define NOT_SPECIFIED_LOCATE            -1      //未指定地區
#define NOT_SPECIFIED_CITY              -1      //未指定城市


// GLOBALS /////////////////////////////////////////////////////////////////////////////////////////////////////////


// FUNCTIONS ///////////////////////////////////////////////////////////////////////////////////////////////////////
int     init_account_details(void);
void    free_account_details(void);
//
COMBOBOX*   get_year_cbb(void);
COMBOBOX*   get_month_cbb(void);
COMBOBOX*   get_day_cbb(void);
COMBOBOX*   get_occupation_cbb(void);
COMBOBOX*   get_locate_cbb(void);
COMBOBOX*   get_city_cbb(SLONG locate_index);
SLONG       get_total_city_cbbs(void);
//
SLONG       is_yun_year(SLONG year);
SLONG       get_month_days(SLONG year, SLONG month);
COMBOBOX*   create_year_cbb(SLONG start_year, SLONG end_year);
COMBOBOX*   create_month_cbb(SLONG start_month, SLONG end_month);
COMBOBOX*   create_day_cbb(SLONG start_day, SLONG end_day);
COMBOBOX*   create_occupation_cbb(void);
COMBOBOX*   create_locate_cbb(SLONG *locates, COMBOBOX ***city_cbb);
//


#endif//_ACCOUNTDETAILS_H_
