/*
**  UIAccMan.h
**  ui account manager functions header.
**
**  Jack, 2002.5.28.
*/
#ifndef _UIACCMAN_H_
#define _UIACCMAN_H_
#include "ImageRim.h"
#include "SwapScr.h"
#include "ErrorMsg.h"
#include "UIComboBox.h"


// DEFINES ///////////////////////////////////////////////////////////////////////////////////////
typedef enum    ACCMANAGER_ENUMS
{   ACCMANAGER_FRAME_BKGND          =   0,
ACCMANAGER_FRAME_CHECK_POINTS       =   1,
ACCMANAGER_FRAME_MODIFY_RECORD      =   4,
ACCMANAGER_FRAME_SUPPLY_POINTS      =   7,
ACCMANAGER_FRAME_CHANGE_PASSWORD    =   10,
ACCMANAGER_FRAME_BACK               =   13,
//
ACCMANAGER_EVENT                =   1007,
ACCMANAGER_ID_BKGND             =   0,
ACCMANAGER_ID_CHECK_POINTS      =   10,
ACCMANAGER_ID_MODIFY_RECORD     =   20,
ACCMANAGER_ID_SUPPLY_POINTS     =   30,
ACCMANAGER_ID_CHANGE_PASSWORD   =   40,
ACCMANAGER_ID_BACK              =   50,
//
} ACCMANAGER_ENUMS;


typedef enum    CHECKPOINTS_ENUMS
{   CHECKPOINTS_FRAME_BKGND     =   0,
CHECKPOINTS_FRAME_QUERY         =   1,
CHECKPOINTS_FRAME_BACK          =   4,
//
CHECKPOINTS_EVENT           =   1008,
CHECKPOINTS_ID_BKGND        =   0,
CHECKPOINTS_ID_QUERY        =   10,
CHECKPOINTS_ID_BACK         =   20,
CHECKPOINTS_ID_ACCOUNT      =   30,
CHECKPOINTS_ID_PASSWORD     =   40,
//
CHECKPOINTS_ACCOUNT_BAR_SX      =   189,
CHECKPOINTS_ACCOUNT_BAR_SY      =   256,
CHECKPOINTS_ACCOUNT_BAR_XL      =   465 - 189,
CHECKPOINTS_ACCOUNT_BAR_YL      =   290 - 256,
CHECKPOINTS_ACCOUNT_INPUT_SX    =   209,
CHECKPOINTS_ACCOUNT_INPUT_SY    =   260,
CHECKPOINTS_ACCOUNT_INPUT_XL    =   465 - 209,
CHECKPOINTS_ACCOUNT_INPUT_YL    =   290 - 260,
CHECKPOINTS_PASSWORD_BAR_SX     =   189,
CHECKPOINTS_PASSWORD_BAR_SY     =   322,
CHECKPOINTS_PASSWORD_BAR_XL     =   465 - 189,
CHECKPOINTS_PASSWORD_BAR_YL     =   356 - 322,
CHECKPOINTS_PASSWORD_INPUT_SX   =   209,
CHECKPOINTS_PASSWORD_INPUT_SY   =   326,
CHECKPOINTS_PASSWORD_INPUT_XL   =   465 - 209,
CHECKPOINTS_PASSWORD_INPUT_YL   =   356 - 326,
CHECKPOINTS_POINTS_BAR_SX       =   223,
CHECKPOINTS_POINTS_BAR_SY       =   390,
CHECKPOINTS_POINTS_BAR_XL       =   417 - 223,
CHECKPOINTS_POINTS_BAR_YL       =   427 - 390,
} CHECKPOINTS_ENUMS;

typedef enum    CHANGEPASSWORD_ENUMS
{   CHANGEPASSWORD_FRAME_BKGND      =   0,
CHANGEPASSWORD_FRAME_OK             =   1,
CHANGEPASSWORD_FRAME_BACK           =   4,
//
CHANGEPASSWORD_EVENT                =   1009,
CHANGEPASSWORD_ID_BKGND             =   0,
CHANGEPASSWORD_ID_NEW_PASSWORD      =   30,
CHANGEPASSWORD_ID_VERIFY_PASSWORD   =   40,
CHANGEPASSWORD_ID_OK                =   60,
CHANGEPASSWORD_ID_BACK              =   70,
//
CHANGEPASSWORD_NEW_PASSWORD_BAR_SX      =   481,
CHANGEPASSWORD_NEW_PASSWORD_BAR_SY      =   204,
CHANGEPASSWORD_NEW_PASSWORD_BAR_XL      =   745 - 481,
CHANGEPASSWORD_NEW_PASSWORD_BAR_YL      =   238 - 204,
CHANGEPASSWORD_VERIFY_PASSWORD_BAR_SX   =   481,
CHANGEPASSWORD_VERIFY_PASSWORD_BAR_SY   =   282,
CHANGEPASSWORD_VERIFY_PASSWORD_BAR_XL   =   745 - 481,
CHANGEPASSWORD_VERIFY_PASSWORD_BAR_YL   =   316 - 282,
//
} CHANGEPASSWORD_ENUMS;


typedef enum    MODIFYRECORD_ENUMS
{   MODIFYRECORD_FRAME_BKGND            =   0,
MODIFYRECORD_FRAME_MALE                 =   1,
MODIFYRECORD_FRAME_FEMAIL               =   3,
MODIFYRECORD_FRAME_YEAR_LIST            =   5,
MODIFYRECORD_FRAME_MONTH_LIST           =   6,
MODIFYRECORD_FRAME_DAY_LIST             =   7,
MODIFYRECORD_FRAME_LOCATE_LIST          =   8,
MODIFYRECORD_FRAME_OCCUPATION_LIST      =   9,
MODIFYRECORD_FRAME_CITY_LIST            =   10,
MODIFYRECORD_FRAME_LIST_SCROLL_DOWN     =   11,
MODIFYRECORD_FRAME_LIST_SCROLL_UP       =   13,
MODIFYRECORD_FRAME_LIST_SCROLL_BAR      =   15,
MODIFYRECORD_FRAME_OK                   =   16,
MODIFYRECORD_FRAME_BACK                 =   19,
MODIFYRECORD_FRAME_BKGND_TITLE          =   20,
//
MODIFYRECORD_EVENT                      =   1010,
MODIFYRECORD_ID_BKGND                   =   0,
MODIFYRECORD_ID_NAME_INPUT              =   10,
MODIFYRECORD_ID_MALE                    =   20,
MODIFYRECORD_ID_FEMALE                  =   30,

MODIFYRECORD_ID_YEAR_INPUT              =   40,
MODIFYRECORD_ID_YEAR_EXPAND             =   50,
MODIFYRECORD_ID_YEAR_LIST_BKGND         =   60,
MODIFYRECORD_ID_YEAR_LIST_SCROLL_BKGND  =   70,
MODIFYRECORD_ID_YEAR_LIST_SCROLL_UP     =   80,
MODIFYRECORD_ID_YEAR_LIST_SCROLL_DOWN   =   90,
MODIFYRECORD_ID_YEAR_LIST_SCROLL_BAR    =   100,
} MODIFYRECORD_ENUMS;


typedef enum    CREATEACCOUNT_ENUMS
{   CREATEACCOUNT_FRAME_BKGND           =   0,
CREATEACCOUNT_FRAME_LAST_STEP           =   1,
CREATEACCOUNT_FRAME_NEXT_STEP           =   4,
//
CREATEACCOUNT_EVENT                     =   1011,
CREATEACCOUNT_ID_BKGND                  =   0,
CREATEACCOUNT_ID_ACCOUNT                =   10,
CREATEACCOUNT_ID_PASSWORD               =   20,
CREATEACCOUNT_ID_VERIFY_PASSWORD        =   30,
CREATEACCOUNT_ID_LAST_STEP              =   40,
CREATEACCOUNT_ID_NEXT_STEP              =   50,
//
CREATEACCOUNT_ACCOUNT_BAR_SX            =   468,
CREATEACCOUNT_ACCOUNT_BAR_SY            =   202,
CREATEACCOUNT_ACCOUNT_BAR_XL            =   734 - 468,
CREATEACCOUNT_ACCOUNT_BAR_YL            =   236 - 202,
CREATEACCOUNT_PASSWORD_BAR_SX           =   468,
CREATEACCOUNT_PASSWORD_BAR_SY           =   262,
CREATEACCOUNT_PASSWORD_BAR_XL           =   734 - 468,
CREATEACCOUNT_PASSWORD_BAR_YL           =   294 - 262,
CREATEACCOUNT_VERIFY_PASSWORD_BAR_SX    =   468,
CREATEACCOUNT_VERIFY_PASSWORD_BAR_SY    =   322,
CREATEACCOUNT_VERIFY_PASSWORD_BAR_XL    =   734 - 468,
CREATEACCOUNT_VERIFY_PASSWORD_BAR_YL    =   356 - 322,
} CREATEACCOUNT_ENUMS;


typedef enum    SETUPRECORD_ENUMS
{   SETUPRECORD_FRAME_BKGND             =   0,
SETUPRECORD_FRAME_MALE                  =   1,
SETUPRECORD_FRAME_FEMALE                =   3,
SETUPRECORD_FRAME_LAST_STEP             =   16,
SETUPRECORD_FRAME_NEXT_STEP             =   19,
//
SETUPRECORD_EVENT                       =   1012,
SETUPRECORD_ID_BKGND                    =   0,
SETUPRECORD_ID_MALE                     =   10,
SETUPRECORD_ID_FEMALE                   =   20,
SETUPRECORD_ID_LAST_STEP                =   30,
SETUPRECORD_ID_NEXT_STEP                =   40,
SETUPRECORD_ID_NAME_INPUT               =   50,
SETUPRECORD_ID_ADDRESS_INPUT            =   60,
SETUPRECORD_ID_TELEPHONE_INPUT          =   70,
SETUPRECORD_ID_EMAIL_INPUT              =   80,
//
SETUPRECORD_NAME_BAR_SX                 =   140,
SETUPRECORD_NAME_BAR_SY                 =   223,
SETUPRECORD_NAME_BAR_XL                 =   372 - 140,
SETUPRECORD_NAME_BAR_YL                 =   255 - 223,
SETUPRECORD_ADDRESS_BAR_SX              =   202,
SETUPRECORD_ADDRESS_BAR_SY              =   475,
SETUPRECORD_ADDRESS_BAR_XL              =   518 - 202,
SETUPRECORD_ADDRESS_BAR_YL              =   501 - 475,
SETUPRECORD_TELEPHONE_BAR_SX            =   202,
SETUPRECORD_TELEPHONE_BAR_SY            =   513,
SETUPRECORD_TELEPHONE_BAR_XL            =   518 - 202,
SETUPRECORD_TELEPHONE_BAR_YL            =   538 - 513,
SETUPRECORD_EMAIL_BAR_SX                =   202,
SETUPRECORD_EMAIL_BAR_SY                =   549,
SETUPRECORD_EMAIL_BAR_XL                =   518 - 202,
SETUPRECORD_EMAIL_BAR_YL                =   575 - 549,
SETUPRECORD_YEAR_CBB_SX                 =   131,        //combo box
SETUPRECORD_YEAR_CBB_SY                 =   327,
SETUPRECORD_YEAR_CBB_XL                 =   230 - 131,
SETUPRECORD_YEAR_CBB_YL                 =   351 - 327,
SETUPRECORD_MONTH_CBB_SX                =   269,
SETUPRECORD_MONTH_CBB_SY                =   327,
SETUPRECORD_MONTH_CBB_XL                =   321 - 269,
SETUPRECORD_MONTH_CBB_YL                =   351 - 327,
SETUPRECORD_DAY_CBB_SX                  =   368,
SETUPRECORD_DAY_CBB_SY                  =   327,
SETUPRECORD_DAY_CBB_XL                  =   420 - 368,
SETUPRECORD_DAY_CBB_YL                  =   351 - 327,
SETUPRECORD_LOCATE_CBB_SX               =   133,
SETUPRECORD_LOCATE_CBB_SY               =   391,
SETUPRECORD_LOCATE_CBB_XL               =   298 - 133,
SETUPRECORD_LOCATE_CBB_YL               =   415 - 391,
SETUPRECORD_OCCUPATION_CBB_SX           =   391,
SETUPRECORD_OCCUPATION_CBB_SY           =   391,
SETUPRECORD_OCCUPATION_CBB_XL           =   507 - 391,
SETUPRECORD_OCCUPATION_CBB_YL           =   415 - 391,
SETUPRECORD_CITY_CBB_SX                 =   133,
SETUPRECORD_CITY_CBB_SY                 =   436,
SETUPRECORD_CITY_CBB_XL                 =   298 - 133,
SETUPRECORD_CITY_CBB_YL                 =   460 - 436,
} SETUPRECORD_ENUMS;


typedef enum    SELECTPAYMENT_ENUMS
{   SELECTPAYMENT_FRAME_BKGND           =   0,
SELECTPAYMENT_FRAME_CREDIT_CARD         =   1,      //name, card id.
SELECTPAYMENT_FRAME_POINTS_CARD         =   2,      //card id, pswd.
SELECTPAYMENT_FRAME_OK                  =   3,
SELECTPAYMENT_FRAME_CANCEL              =   6,
//
SELECTPAYMENT_EVENT                     =   1013,
SELECTPAYMENT_ID_BKGND                  =   0,
SELECTPAYMENT_ID_OK                     =   10,
SELECTPAYMENT_ID_CANCEL                 =   20,
SELECTPAYMENT_ID_CREDIT_CARD_NAME       =   30,
SELECTPAYMENT_ID_CREDIT_CARD_ID_0       =   40,
SELECTPAYMENT_ID_CREDIT_CARD_ID_1       =   41,
SELECTPAYMENT_ID_CREDIT_CARD_ID_2       =   42,
SELECTPAYMENT_ID_CREDIT_CARD_ID_3       =   43,
SELECTPAYMENT_ID_POINTS_CARD_ID_0       =   50,
SELECTPAYMENT_ID_POINTS_CARD_ID_1       =   50,
SELECTPAYMENT_ID_POINTS_CARD_ID_2       =   50,
SELECTPAYMENT_ID_POINTS_CARD_ID_3       =   50,
SELECTPAYMENT_ID_POINTS_CARD_PASSWORD   =   60,
//
SELECTPAYMENT_TYPE_CBB_SX               =   493,
SELECTPAYMENT_TYPE_CBB_SY               =   195,
SELECTPAYMENT_TYPE_CBB_XL               =   658 - 493,
SELECTPAYMENT_TYPE_CBB_YL               =   220 - 195,
SELECTPAYMENT_REST_POINTS_SX            =   613,
SELECTPAYMENT_REST_POINTS_SY            =   140,
SELECTPAYMENT_REST_POINTS_XL            =   730 - 613,
SELECTPAYMENT_REST_POINTS_YL            =   173 - 140,
SELECTPAYMENT_ADD_POINTS_SX             =   546,
SELECTPAYMENT_ADD_POINTS_SY             =   485,
SELECTPAYMENT_ADD_POINTS_XL             =   703 - 546,
SELECTPAYMENT_ADD_POINTS_YL             =   518 - 485,
//
SELECTPAYMENT_CCARD_NAME_INPUT_SX       =   451,            //CCARD = Credit Card.
SELECTPAYMENT_CCARD_NAME_INPUT_SY       =   291,
SELECTPAYMENT_CCARD_NAME_INPUT_XL       =   687 - 454,
SELECTPAYMENT_CCARD_NAME_INPUT_YL       =   325 - 291,
SELECTPAYMENT_CCARD_ID_0_INPUT_SX       =   374,
SELECTPAYMENT_CCARD_ID_0_INPUT_SY       =   385,
SELECTPAYMENT_CCARD_ID_0_INPUT_XL       =   456 - 374,
SELECTPAYMENT_CCARD_ID_0_INPUT_YL       =   420 - 385,
SELECTPAYMENT_CCARD_ID_1_INPUT_SX       =   476,
SELECTPAYMENT_CCARD_ID_1_INPUT_SY       =   385,
SELECTPAYMENT_CCARD_ID_1_INPUT_XL       =   557 - 476,
SELECTPAYMENT_CCARD_ID_1_INPUT_YL       =   420 - 385,
SELECTPAYMENT_CCARD_ID_2_INPUT_SX       =   579,
SELECTPAYMENT_CCARD_ID_2_INPUT_SY       =   385,
SELECTPAYMENT_CCARD_ID_2_INPUT_XL       =   662 - 579,
SELECTPAYMENT_CCARD_ID_2_INPUT_YL       =   420 - 385,
SELECTPAYMENT_CCARD_ID_3_INPUT_SX       =   682,
SELECTPAYMENT_CCARD_ID_3_INPUT_SY       =   385,
SELECTPAYMENT_CCARD_ID_3_INPUT_XL       =   764 - 682,
SELECTPAYMENT_CCARD_ID_3_INPUT_YL       =   420 - 385,
SELECTPAYMENT_CCARD_YEAR_CBB_SX         =   512,
SELECTPAYMENT_CCARD_YEAR_CBB_SY         =   448,
SELECTPAYMENT_CCARD_YEAR_CBB_XL         =   611 - 512,
SELECTPAYMENT_CCARD_YEAR_CBB_YL         =   473 - 448,
SELECTPAYMENT_CCARD_MONTH_CBB_SX        =   649,
SELECTPAYMENT_CCARD_MONTH_CBB_SY        =   448,
SELECTPAYMENT_CCARD_MONTH_CBB_XL        =   701 - 649,
SELECTPAYMENT_CCARD_MONTH_CBB_YL        =   473 - 448,
//
SELECTPAYMENT_PCARD_ID_0_INPUT_SX       =   374,
SELECTPAYMENT_PCARD_ID_0_INPUT_SY       =   318,
SELECTPAYMENT_PCARD_ID_0_INPUT_XL       =   456 - 374,
SELECTPAYMENT_PCARD_ID_0_INPUT_YL       =   352 - 318,
SELECTPAYMENT_PCARD_ID_1_INPUT_SX       =   476,
SELECTPAYMENT_PCARD_ID_1_INPUT_SY       =   318,
SELECTPAYMENT_PCARD_ID_1_INPUT_XL       =   557 - 476,
SELECTPAYMENT_PCARD_ID_1_INPUT_YL       =   352 - 318,
SELECTPAYMENT_PCARD_ID_2_INPUT_SX       =   579,
SELECTPAYMENT_PCARD_ID_2_INPUT_SY       =   318,
SELECTPAYMENT_PCARD_ID_2_INPUT_XL       =   661 - 579,
SELECTPAYMENT_PCARD_ID_2_INPUT_YL       =   352 - 318,
SELECTPAYMENT_PCARD_ID_3_INPUT_SX       =   682,
SELECTPAYMENT_PCARD_ID_3_INPUT_SY       =   318,
SELECTPAYMENT_PCARD_ID_3_INPUT_XL       =   764 - 682,
SELECTPAYMENT_PCARD_ID_3_INPUT_YL       =   352 - 318,
SELECTPAYMENT_PCARD_PSWD_INPUT_SX       =   454,
SELECTPAYMENT_PCARD_PSWD_INPUT_SY       =   431,
SELECTPAYMENT_PCARD_PSWD_INPUT_XL       =   687 - 454,
SELECTPAYMENT_PCARD_PSWD_INPUT_YL       =   465 - 431,
//
PAYMENT_TYPE_CREDIT_CARD                =   0,
PAYMENT_TYPE_POINTS_CARD                =   1,
} SELECTPAYMENT_ENUMS;


// STRUCTURES ////////////////////////////////////////////////////////////////////////////////////
//
// informations of user's account
typedef struct  tagACCOUNT_INFO
{
    USTR    account[32];        //account name
    USTR    password[32];       //password string
    USTR    verify_password[32];//verify password string
    //
    USTR    name[32];           //name
    SLONG   sex;                //sex
    SLONG   year;               //birthday year
    SLONG   month;              //birthday month
    SLONG   day;                //birthday day
    USTR    locate[64];         //user locate name
    USTR    occupation[64];     //user occupation
    SLONG   occupation_no;      //user occupation number
    USTR    city[64];           //user city name
    USTR    address[64];        //user address
    USTR    telephone[32];      //user telephone
    USTR    email[64];          //user email address
    //
    SLONG   payment;            //user payment
    //
} ACCOUNT_INFO, *LPACCOUNT_INFO;


typedef struct  tagACCMANAGER_DATA
{
    CAKE_FRAME_ANI  *cfa;
    CAKE_FRAME      *cf[32];
    //
    SLONG   hilight_id;         //hilight id
    SLONG   active_id;          //active id
} ACCMANAGER_DATA, *LPACCMANAGER_DATA;


typedef struct  tagCHECKPOINTS_DATA
{
    CAKE_FRAME_ANI  *cfa;
    CAKE_FRAME      *cf[32];
    //
    SLONG   hilight_id;         //hilight id
    SLONG   active_id;          //active id
    SLONG   function_id;        //function id
    USTR    account[32];        //account string
    USTR    password[32];       //password string
} CHECKPOINTS_DATA, *LPCHECKPOINTS_DATA;


typedef struct  tagCHANGEPASSWORD_DATA
{
    CAKE_FRAME_ANI  *cfa;
    CAKE_FRAME      *cf[32];
    //
    SLONG   hilight_id;         //hilight id
    SLONG   active_id;          //active id
    SLONG   function_id;        //function id
    USTR    new_password[32];   //new password string
    USTR    verify_password[32];//verify new password string
} CHANGEPASSWORD_DATA, *LPCHANGEPASSWORD_DATA;


typedef struct  tagMODIFYRECORD_DATA
{
    CAKE_FRAME_ANI  *cfa;
    CAKE_FRAME      *cf[32];
    //
    SLONG   hilight_id;         //hilight id
    SLONG   active_id;          //active id
    SLONG   function_id;        //function id
    //
    ACCOUNT_INFO    modify;     //modify account info
} MODIFYRECORD_DATA, *LPMODIFYRECORD_DATA;


typedef struct tagCREATEACCOUNT_DATA
{
    CAKE_FRAME_ANI  *cfa;
    CAKE_FRAME      *cf[32];
    //
    SLONG   hilight_id;         //hilight id
    SLONG   active_id;          //active id
    SLONG   function_id;        //function id
    //
} CREATEACCOUNT_DATA, *LPCREATEACCOUNT_DATA;


typedef struct tagSETUPRECORD_DATA
{
    CAKE_FRAME_ANI  *cfa;
    CAKE_FRAME      *cf[32];
    //
    SLONG   hilight_id;         //hilight id
    SLONG   active_id;          //active id
    SLONG   function_id;        //function id
    //
    COMBOBOX    *year_cbb;
    COMBOBOX    *month_cbb;
    COMBOBOX    *day_cbb;
    COMBOBOX    *occupation_cbb;
    COMBOBOX    *locate_cbb;
    COMBOBOX    *city_cbb;
    SLONG       locate_item_index;
    SLONG       city_item_index;
    //
} SETUPRECORD_DATA, *LPSETUPRECORD_DATA;


typedef struct tagSELECTPAYMENT_DATA
{
    CAKE_FRAME_ANI  *cfa;
    CAKE_FRAME      *cf[32];
    //
    SLONG   hilight_id;         //hilight id
    SLONG   active_id;          //active id
    SLONG   function_id;        //function id
    //
    SLONG       payment_type;   //payment type, 0 ~ max types.
    COMBOBOX    *card_cbb;      //payment card cbb.
    COMBOBOX    *year_cbb;      //validate year cbb
    COMBOBOX    *month_cbb;     //validate month cbb
    //
} SELECTPAYMENT_DATA, *LPSELECTPAYMENT_DATA;



extern  ACCOUNT_INFO        account_info;
extern  ACCMANAGER_DATA     accmanager_data;
extern  CHECKPOINTS_DATA    checkpoints_data;
extern  CHANGEPASSWORD_DATA changepassword_data;
extern  CREATEACCOUNT_DATA  createaccount_data;
extern  SETUPRECORD_DATA    setuprecord_data;
extern  SELECTPAYMENT_DATA  selectpayment_data;


//ui account manager ---------------------------
void    init_account_info(void);
//
int     init_account_manager(void);
void    active_account_manager(int active);
void    free_account_manager(void);
void    refresh_account_manager(void);
void    redraw_account_manager(SLONG sx, SLONG sy, void *vbitmap);
SLONG   handle_account_manager(UINT message, WPARAM wParam, LPARAM lParam);

//ui create account ----------------------------
int     init_create_account(void);
void    active_create_account(int active);
void    free_create_account(void);
void    refresh_create_account(void);
void    redraw_create_account(SLONG sx, SLONG sy, void *vbitmap);
SLONG   handle_create_account(UINT message, WPARAM wParam, LPARAM lParam);

//ui setup record ------------------------------
int     init_setup_record(void);
void    active_setup_record(int active);
void    free_setup_record(void);
void    refresh_setup_record(void);
void    redraw_setup_record(SLONG sx, SLONG sy, void *vbitmap);
SLONG   handle_setup_record(UINT message, WPARAM wParam, LPARAM lParam);

//ui select payment ------------------------------
int     init_select_payment(void);
void    active_select_payment(int active);
void    free_select_payment(void);
void    refresh_select_payment(void);
void    redraw_select_payment(SLONG sx, SLONG sy, void *vbitmap);
SLONG   handle_select_payment(UINT message, WPARAM wParam, LPARAM lParam);

//ui check points -------------------------------
int     init_check_points(void);
void    active_check_points(int active);
void    free_check_points(void);
void    refresh_check_points(void);
void    redraw_check_points(SLONG sx, SLONG sy, void *vbitmap);
SLONG   handle_check_points(UINT message, WPARAM wParam, LPARAM lParam);

//ui modify record -------------------------------
int     init_modify_record(void);
void    active_modify_record(int active);
void    free_modify_record(void);
void    refresh_modify_record(void);
void    redraw_modify_record(SLONG sx, SLONG sy, void *vbitmap);
SLONG   handle_modify_record(UINT message, WPARAM wParam, LPARAM lParam);


//ui change password ------------------------------
int     init_change_password(void);
void    active_change_password(int active);
void    free_change_password(void);
void    refresh_change_password(void);
void    redraw_change_password(SLONG sx, SLONG sy, void *vbitmap);
SLONG   handle_change_password(UINT message, WPARAM wParam, LPARAM lParam);


#endif//_UIACCMAN_H_
