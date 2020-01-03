/*
**	NetGE_Account.h 
**	account functions header.
**
**	Jack, 2002.12.9
*/
#pragma once


// DEFINES ///////////////////////////////////////////////////////////////////////////////////////////////////////////
//

// STRUCTURES ////////////////////////////////////////////////////////////////////////////////////////////////////////
//
#pragma pack(push)
#pragma	pack(1)

//
//人物帳號資料結構
typedef	struct POS_ACCOUNT 
{
	CHAR	ID[20];				//帳號名稱
	CHAR	Password[20];		//帳號密碼
	CHAR	VerifyPassword[20];	//確認帳號密碼
	CHAR	Name[32];			//真實名稱
	CHAR	Sex;				//性別
	CHAR	Birthday[9];		//生日, YYYY-MM-DD
	CHAR	Phone[16];			//電話
	CHAR	Email[40];			//EMAIL
	CHAR	Country[16];		//所在國家
	CHAR	City[16];			//所在城市
	CHAR	Address[64];		//通訊地址
	UHINT	PayType;			//付費方式
	UHINT	NetType;			//網路連線方式
	UHINT	Career;				//職業
	//
	UHINT	BirthdayYear;		//出生年份
	UHINT	BirthdayMonth;		//出生月份
	UHINT	BirthdayDay;		//出生日期
} TPOS_ACCOUNT, *LPTPOS_ACCOUNT;


#pragma pack(pop)

// GLOBALS ///////////////////////////////////////////////////////////////////////////////////////////////////////////
//

// FUNCTIONS /////////////////////////////////////////////////////////////////////////////////////////////////////////
//



