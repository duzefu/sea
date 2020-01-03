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
//�H���b����Ƶ��c
typedef	struct POS_ACCOUNT 
{
	CHAR	ID[20];				//�b���W��
	CHAR	Password[20];		//�b���K�X
	CHAR	VerifyPassword[20];	//�T�{�b���K�X
	CHAR	Name[32];			//�u��W��
	CHAR	Sex;				//�ʧO
	CHAR	Birthday[9];		//�ͤ�, YYYY-MM-DD
	CHAR	Phone[16];			//�q��
	CHAR	Email[40];			//EMAIL
	CHAR	Country[16];		//�Ҧb��a
	CHAR	City[16];			//�Ҧb����
	CHAR	Address[64];		//�q�T�a�}
	UHINT	PayType;			//�I�O�覡
	UHINT	NetType;			//�����s�u�覡
	UHINT	Career;				//¾�~
	//
	UHINT	BirthdayYear;		//�X�ͦ~��
	UHINT	BirthdayMonth;		//�X�ͤ��
	UHINT	BirthdayDay;		//�X�ͤ��
} TPOS_ACCOUNT, *LPTPOS_ACCOUNT;


#pragma pack(pop)

// GLOBALS ///////////////////////////////////////////////////////////////////////////////////////////////////////////
//

// FUNCTIONS /////////////////////////////////////////////////////////////////////////////////////////////////////////
//



