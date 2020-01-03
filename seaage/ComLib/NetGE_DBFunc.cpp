/*
**	NetGE_DBFunc.cpp 
**	database functions.
**
**	Jack, 2003.1.8
*/
#include "NetGE_MainFunc.h"

//
// DEFINES //////////////////////////////////////////////////////////////////////////////////////////////////
//
#define	STATEMENT_STR_LEN		102400
#define	STATEMENT_TEMP_LEN		1024
//

//
// GLOBALS //////////////////////////////////////////////////////////////////////////////////////////////////
//
static	char	statement_str[STATEMENT_STR_LEN];
static	char	statement_temp[STATEMENT_TEMP_LEN];


// Reserved functions:
SLONG	DeleteAccountDBTable(void);
SLONG	CreateAccountDBTable(void);
SLONG	DeleteCharacterDBTable(void);
SLONG	CreateCharacterDBTable(void);
SLONG	DeleteItemDBTable(void);
SLONG	CreateItemDBTable(void);
SLONG	DeleteQQDBTable(void);
SLONG	CreateQQDBTable(void);
SLONG	DeleteQQMsgDBTable(void);
SLONG	CreateQQMsgDBTable(void);
SLONG	DeleteBankDBTable(void);
SLONG	CreateBankDBTable(void);
SLONG	DeleteHouseDBTable(void);
SLONG	CreateHouseDBTable(void);
SLONG	DeleteQuestDBTable(void);
SLONG	CreateQuestDBTable(void);


static	VOID	InitStatementStr(VOID);

/************************************************************************************************************/
/* MISC STATIC FUNCTIONS                                                                                    */
/************************************************************************************************************/
static	VOID	InitStatementStr(VOID)
{
	memset(statement_str, 0, STATEMENT_STR_LEN);
}

/************************************************************************************************************/
/* ACCOUNT DB FUNCTIONS                                                                                     */
/************************************************************************************************************/
SLONG	DeleteAccountDBTable(void)
{
	HSTMT	hstmt;
	SQLRETURN	rc;

	InitStatementStr();
	sprintf((char *)statement_str,
		"DROP TABLE IF EXISTS `pos_account`"
		);
	hstmt = GetODBCStatementHandle();
	rc = SQLExecDirect(hstmt, (unsigned char*)statement_str, SQL_NTS);
	if(rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) 
	{
		return	-1;
	}
	return	0;
}


SLONG	CreateAccountDBTable(void)
{
	HSTMT	hstmt;
	SQLRETURN	rc;

	InitStatementStr();
	sprintf((char *)statement_str, 
		"CREATE TABLE `pos_account` ("
		"`Account` char(32) NOT NULL default '',"
		"`Password` char(32) NOT NULL default '',"
		"`Name` char(32) NOT NULL default '',"
		"`Sex` tinyint(1) unsigned default '',"
		"`Birthday` char(12) default '',"
		"`Country` char(16) default '',"
		"`City` char(16) default '',"
		"`Address` char(52) default '',"
		"`Phone` char(16) default '',"
		"`Job` int(4) default '',"
		"`NetStyle` int(4) default '',"
		"`Email` char(40) NOT NULL default '',"
		"`PayType` int(4) default '',"
		"`Status` tinyint(1) unsigned default '0',"
		// Jack, Added [5/15/2003]
		"`RestPoints` int(4) unsigned default '0',"
		"`LimitDate` int(4) unsigned default '0',"
		"`RestMinutes` int(4) unsigned default '0',"
		"PRIMARY KEY (`Account`)"
		") TYPE = MyISAM"
		);
	hstmt = GetODBCStatementHandle();
	rc = SQLExecDirect(hstmt, (unsigned char*)statement_str, SQL_NTS);
	if(rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) 
	{
		return	-1;
	}
	return	0;
}


SLONG	AppendRecordToAccountDB(TPOS_DB_ACCOUNT *lpAccount)
{
	HSTMT	hstmt;
	SQLRETURN	rc;

	InitStatementStr();
	sprintf((char *)statement_str, "INSERT INTO pos_account (");

	//== Colume names
	sprintf((char *)statement_temp, 
		"Account,Password,Name,Sex,Birthday,"
		"Country,City,Address,Phone,Job,"
		"NetStyle,Email,PayType,Status,"
		"RestPoints,LimitDate,RestMinutes"
		);
	strcat((char *)statement_str, (const char *)statement_temp);

	//== Values
	strcat((char *)statement_str, ") VALUES (");

	// Colume values
	sprintf((char *)statement_temp, 
		"'%s','%s','%s',%d,'%s','%s','%s','%s','%s',%d,%d,'%s',%d,%d,%u,%u,%u",
		lpAccount->cId,
		lpAccount->cPw,
		lpAccount->cName,
		lpAccount->Sex,
		lpAccount->cBirthday,
		lpAccount->cCountry,
		lpAccount->cCity,
		lpAccount->cAddress,
		lpAccount->cPhone,
		lpAccount->dwJob,
		lpAccount->dwNetStyle,
		lpAccount->cEmail,
		lpAccount->dwPayType,
		lpAccount->cStatus,
		// Jack, Added [5/15/2003]
		lpAccount->RestPoints,
		lpAccount->LimitDate,
		lpAccount->RestMinutes
		);
	strcat((char *)statement_str, (const char *)statement_temp);

	//Statement string end.
	strcat((char *)statement_str, ")");

	hstmt = GetODBCStatementHandle();
	rc = SQLExecDirect(hstmt, (unsigned char*)statement_str, SQL_NTS);
	if(rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) 
	{
		return	FALSE;
	}
	else
	{
		return	TRUE;
	}
}

SLONG	DeleteRecordFromAccountDB(CHAR *szAccount, CHAR *szPassword)
{
	HSTMT	hstmt;
	SQLRETURN	rc;

	InitStatementStr();
	sprintf((char *)statement_str, 
		"DELETE FROM pos_account WHERE Account='%s' AND Password='%s'",
		szAccount, szPassword);
	hstmt = GetODBCStatementHandle();
	rc = SQLExecDirect(hstmt, (unsigned char*)statement_str, SQL_NTS);
	if(rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) 
	{
		return	FALSE;
	}
	else
	{
		return	TRUE;
	}
}


SLONG	UpdateRecordOfAccountDB(TPOS_DB_ACCOUNT *lpAccount)
{
	HSTMT	hstmt;
	SQLRETURN	rc;

	//
	// Update record to account database by Account.
	//
	InitStatementStr();
	sprintf((char *)statement_str, "UPDATE pos_account SET ");
	//"[Field1 = Value1,...N]"

	sprintf((char *)statement_temp, 
		"Password='%s',Name='%s',Sex=%d,Birthday='%s',"
		"Country='%s',City='%s',Address='%s',Phone='%s',Job=%d,"
		"NetStyle=%d,Email='%s',PayType=%d,Status=%d,RestPoints=%u,LimitDate=%u,RestMinutes=%u",
		lpAccount->cPw,
		lpAccount->cName,
		lpAccount->Sex,
		lpAccount->cBirthday,
		lpAccount->cCountry,
		lpAccount->cCity,
		lpAccount->cAddress,
		lpAccount->cPhone,
		lpAccount->dwJob,
		lpAccount->dwNetStyle,
		lpAccount->cEmail,
		lpAccount->dwPayType,
		lpAccount->cStatus,
		// Jack, Added. [5/15/2003]
		lpAccount->RestPoints,
		lpAccount->LimitDate,
		lpAccount->RestMinutes
		);
	strcat((char*)statement_str, (const char *)statement_temp);

	//Statement string end.
	sprintf((char *)statement_temp, " WHERE Account='%s'",
		lpAccount->cId);
	strcat((char*)statement_str, (const char *)statement_temp);

	hstmt = GetODBCStatementHandle();
	rc = SQLExecDirect(hstmt, (unsigned char*)statement_str, SQL_NTS);
	if(rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) 
	{
		return	FALSE;
	}
	else
	{
		return	TRUE;
	}
}

SLONG	GetRecordFromAccountDB(TPOS_DB_ACCOUNT *lpAccount, CHAR *szAccount)
{
	HSTMT		hstmt;
	SQLRETURN	rc;
	
	InitStatementStr();
	sprintf((char *)statement_str, 
		"SELECT * from pos_account WHERE Account='%s'",
		szAccount );
	hstmt = GetODBCStatementHandle();
	rc = SQLExecDirect( hstmt, (unsigned char *)statement_str, SQL_NTS);
	if(rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) 
	{
		goto _error;
	}

	BindAccountDBColumn(hstmt, lpAccount);
	rc = SQLFetch(hstmt);
	if(rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) 
	{
		goto _error;
	}
	SQLCloseCursor(hstmt);
	return	TRUE;

_error:
	return	FALSE;
}

SLONG	ChangePasswordOfAccountDB(CHAR *szAccount, CHAR *szPassword)
{
	HSTMT	hstmt;
	SQLRETURN	rc;

	InitStatementStr();
	sprintf((char *)statement_str, 
		"UPDATE pos_account SET Password='%s' WHERE Account='%s'",
		szPassword, szAccount);
	hstmt = GetODBCStatementHandle();
	rc = SQLExecDirect(hstmt, (unsigned char*)statement_str, SQL_NTS);
	if(rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) 
	{
		return	FALSE;
	}
	else
	{
		return	TRUE;
	}
}


SLONG	CheckPasswordOfAccountDB(CHAR *szAccount, CHAR *szPassword)
{
	HSTMT		hstmt;
	SQLRETURN	rc;
	SDWORD		cb;
	char		password[32];
	SLONG		result;
	
	result = NETGE_DB_SUCCESS;
	InitStatementStr();
	sprintf((char *)statement_str, 
		"SELECT * from pos_account WHERE Account='%s'",
		szAccount);
	hstmt = GetODBCStatementHandle();
	rc = SQLExecDirect( hstmt, (unsigned char *)statement_str, SQL_NTS);
	if(rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) 
	{
		result = NETGE_DB_ERROR_ODBC;
		goto _error;
	}

	SQLBindCol(hstmt, 2, SQL_CHAR, password, sizeof(password), &cb);
	rc = SQLFetch(hstmt);	
	SQLCloseCursor(hstmt);
	if(rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) 
	{
		result = NETGE_DB_ERROR_ACCOUNT;
		goto _error;
	}

	if(0 != strcmp((const char *)password, (const char *)szPassword))
	{
		result = NETGE_DB_ERROR_PASSWORD;
		goto _error;
	}
	result = NETGE_DB_SUCCESS;

	return	result;

_error:
	return	result;
}


SLONG	CheckAccountOfAccountDB(CHAR *szAccount)
{
	HSTMT		hstmt;
	SQLRETURN	rc;
	SDWORD		cb;
	char		account[32];
	SLONG		result;

	InitStatementStr();
	sprintf((char *)statement_str, 
		"SELECT * from pos_account WHERE Account='%s'",
		szAccount);
	hstmt = GetODBCStatementHandle();
	rc = SQLExecDirect( hstmt, (unsigned char *)statement_str, SQL_NTS);
	if(rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) 
	{
		result = NETGE_DB_ERROR_ODBC;
		goto _error;
	}

	SQLBindCol(hstmt, 1, SQL_CHAR, account, sizeof(account), &cb);
	rc = SQLFetch(hstmt);	
	SQLCloseCursor(hstmt);
	if(rc == SQL_SUCCESS || rc == SQL_SUCCESS_WITH_INFO) 
	{
		result = NETGE_DB_ACCOUNT_EXIST;
		goto _error;
	}
	result = NETGE_DB_ACCOUNT_AVAILABLE;

	return	result;

_error:
	return	result;
}


VOID	BindAccountDBColumn(HSTMT hStmt, TPOS_DB_ACCOUNT *lpAccount)
{
	SDWORD	cb;

	SQLBindCol(hStmt, 1,	SQL_CHAR,		lpAccount->cId,			sizeof(lpAccount->cId),			&cb);
	SQLBindCol(hStmt, 2,	SQL_CHAR,		lpAccount->cPw,			sizeof(lpAccount->cPw),			&cb);
	SQLBindCol(hStmt, 3,	SQL_CHAR,		lpAccount->cName,		sizeof(lpAccount->cName),		&cb);
	SQLBindCol(hStmt, 4,	SQL_TINYINT,	&lpAccount->Sex,		sizeof(lpAccount->Sex),			&cb);
	SQLBindCol(hStmt, 5,	SQL_CHAR,		lpAccount->cBirthday,	sizeof(lpAccount->cBirthday),	&cb);
	SQLBindCol(hStmt, 6,	SQL_CHAR,		lpAccount->cCountry,	sizeof(lpAccount->cCountry),	&cb);
	SQLBindCol(hStmt, 7,	SQL_CHAR,		lpAccount->cCity,		sizeof(lpAccount->cCity),		&cb);
	SQLBindCol(hStmt, 8,	SQL_CHAR,		lpAccount->cAddress,	sizeof(lpAccount->cAddress),	&cb);
	SQLBindCol(hStmt, 9,	SQL_CHAR,		lpAccount->cPhone,		sizeof(lpAccount->cPhone),		&cb);
	SQLBindCol(hStmt, 10,	SQL_INTEGER,	&lpAccount->dwJob,		sizeof(lpAccount->dwJob),		&cb);
	SQLBindCol(hStmt, 11,	SQL_INTEGER,	&lpAccount->dwNetStyle, sizeof(lpAccount->dwNetStyle),	&cb);
	SQLBindCol(hStmt, 12,	SQL_CHAR,		lpAccount->cEmail,		sizeof(lpAccount->cEmail),		&cb);
	SQLBindCol(hStmt, 13,	SQL_INTEGER,	&lpAccount->dwPayType,	sizeof(lpAccount->dwPayType),	&cb);
	SQLBindCol(hStmt, 14,	SQL_TINYINT,	&lpAccount->cStatus,	sizeof(lpAccount->cStatus),		&cb);
	// Jack, Added. [5/15/2003]
	SQLBindCol(hStmt, 15,	SQL_INTEGER,	&lpAccount->RestPoints,	sizeof(lpAccount->RestPoints),	&cb);
	SQLBindCol(hStmt, 16,	SQL_INTEGER,	&lpAccount->LimitDate,	sizeof(lpAccount->LimitDate),	&cb);
	SQLBindCol(hStmt, 17,	SQL_INTEGER,	&lpAccount->RestMinutes,sizeof(lpAccount->RestMinutes), &cb);
}

/************************************************************************************************************/
/* CHARACTER DB FUNCTIONS                                                                                   */
/************************************************************************************************************/
SLONG	DeleteCharacterDBTable(void)
{
	HSTMT	hstmt;
	SQLRETURN	rc;

	InitStatementStr();
	sprintf((char *)statement_str,
		"DROP TABLE IF EXISTS `pos_character`"
		);
	hstmt = GetODBCStatementHandle();
	rc = SQLExecDirect(hstmt, (unsigned char*)statement_str, SQL_NTS);
	if(rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) 
	{
		return	-1;
	}
	return	0;
}

SLONG	CreateCharacterDBTable(void)
{
	HSTMT	hstmt;
	SQLRETURN	rc;
	SLONG	i;

	InitStatementStr();
	sprintf((char *)statement_str, "CREATE TABLE `pos_character` (");

	//Name
	strcat((char *)statement_str, "`Account` char(32) NOT NULL default '',");
	strcat((char *)statement_str, "`MainName` char(32) NOT NULL default '',");
	strcat((char *)statement_str, "`NickName` char(32) default '',");
	strcat((char *)statement_str, "`QQID` int(4) unsigned NOT NULL default '0',");
	strcat((char *)statement_str, "`CharacterIndex` smallint(2) unsigned default '',");

	//Style	
	strcat((char *)statement_str, "`Color` tinyint(1) unsigned default '',");
	strcat((char *)statement_str, "`Eyes` tinyint(1) unsigned default '',");
	strcat((char *)statement_str, "`Mouth` tinyint(1) unsigned default '',");
	strcat((char *)statement_str, "`MainNameColor` tinyint(1) unsigned default '',");
	strcat((char *)statement_str, "`NickNameColor` tinyint(1) unsigned default '',");
	strcat((char *)statement_str, "`MessageColor` tinyint(1) unsigned default '',");
	strcat((char *)statement_str, "`TalkBackColor` tinyint(1) unsigned default '',");
	strcat((char *)statement_str, "`Logo` int(4) unsigned default '0',");
	strcat((char *)statement_str, "`LandFileIndex` int(4) default '',");
	
	//Position
	strcat((char *)statement_str, "`ZoneName` char(32) default '',");
	strcat((char *)statement_str, "`X` int(4) default '0',");
	strcat((char *)statement_str, "`Y` int(4) default '0',");
	strcat((char *)statement_str, "`Z` int(4) default '0',");
	strcat((char *)statement_str, "`Dir` tinyint(1) unsigned default '0',");
	strcat((char *)statement_str, "`StopRadius` int(4) default '10',");
	
	//Speed
	strcat((char *)statement_str, "`MoveSpeed` int(4) default '10',");
	strcat((char *)statement_str, "`ShipSpeedX` int(4) default '0',");
	strcat((char *)statement_str, "`ShipSpeedY` int(4) default '0',");
	strcat((char *)statement_str, "`ShipSailSize` smallint(2) default '0',");
	strcat((char *)statement_str, "`ShipTurn` smallint(2) default '0',");
	strcat((char *)statement_str, "`ShipWeight` smallint(2) unsigned default '0',");
	strcat((char *)statement_str, "`ShipDegreeDir` int(4) default '0',");
	
	//State
	strcat((char *)statement_str, "`BitState` int(4) unsigned default '0',");
	
	//Str
	strcat((char *)statement_str, "`InitStr` smallint(2) unsigned default '0',");
	strcat((char *)statement_str, "`LevelUpStr` smallint(2) unsigned default '0',");
	
	//Ins
	strcat((char *)statement_str, "`InitIns` smallint(2) unsigned default '0',");
	strcat((char *)statement_str, "`LevelUpIns` smallint(2) unsigned default '0',");
	
	//Wit
	strcat((char *)statement_str, "`InitWit` smallint(2) unsigned default '0',");
	strcat((char *)statement_str, "`LevelUpWit` smallint(2) unsigned default '0',");
	
	//Lucky
	strcat((char *)statement_str, "`InitLucky` smallint(2) unsigned default '0',");
	strcat((char *)statement_str, "`LevelUpLucky` smallint(2) unsigned default '0',");
	
	//Attack
	strcat((char *)statement_str, "`SightRange` smallint(2) unsigned default '0',");
	strcat((char *)statement_str, "`FinalExplodeRate` smallint(2) unsigned default '0',");

	//Defence
	strcat((char *)statement_str, "`DodgeRate` smallint(2) unsigned default '0',");
	strcat((char *)statement_str, "`ParryRate` smallint(2) unsigned default '0',");
	
	//PropertyPoint
	strcat((char *)statement_str, "`PropertyPoint` smallint(2) unsigned default '0',");

	//Exp Lev
	strcat((char *)statement_str, "`Exp` int(4) unsigned default '0',");
	strcat((char *)statement_str, "`Level` smallint(2) unsigned default '0',");
	
	//Hp Mp
	strcat((char *)statement_str, "`Hp` smallint(2) unsigned default '1',");
	strcat((char *)statement_str, "`MaxHp` smallint(2) unsigned default '1',");
	strcat((char *)statement_str, "`HpRestore` smallint(2) unsigned default '0',");
	strcat((char *)statement_str, "`Mp` smallint(2) unsigned default '1',");
	strcat((char *)statement_str, "`MaxMp` smallint(2) unsigned default '1',");
	strcat((char *)statement_str, "`MpRestore` smallint(2) unsigned default '0',");
	
	//SHINT	SkillNo[36];			//技能編號
	//UHINT	SkillLevel[36];			//技能等級
	for(i=0; i<36; i++)
	{
		sprintf((char *)statement_temp, 
			"`SkillNo%02d` smallint(2) default '-1',"
			"`SkillLevel%02d` smallint(2) default '0',",
			i+1, i+1);
		strcat((char *)statement_str, (const char *)statement_temp);
	}
	
	//Equip
	strcat((char *)statement_str, "`EquHead` int(4) unsigned default '0',");
	strcat((char *)statement_str, "`EquNeck` int(4) unsigned default '0',");
	strcat((char *)statement_str, "`EquBody` int(4) unsigned default '0',");
	strcat((char *)statement_str, "`EquWaist` int(4) unsigned default '0',");
	strcat((char *)statement_str, "`EquGlove` int(4) unsigned default '0',");
	strcat((char *)statement_str, "`EquWeapon` int(4) unsigned default '0',");
	strcat((char *)statement_str, "`EquWrist` int(4) unsigned default '0',");
	strcat((char *)statement_str, "`EquFeet` int(4) unsigned default '0',");
	strcat((char *)statement_str, "`EquOtherA` int(4) unsigned default '0',");
	strcat((char *)statement_str, "`EquOtherB` int(4) unsigned default '0',");
	strcat((char *)statement_str, "`EquOtherC` int(4) unsigned default '0',");

	//Body Item
	//DWORD	BagItem[MAX_CHARACTER_BAG_ITEMS];		//背包內物品
	for(i=0; i<MAX_CHARACTER_BAG_ITEMS; i++)
	{
		sprintf((char *)statement_temp, 
			"`BagItem%02d` int(4) unsigned default '0',"
			,i+1);
		strcat((char *)statement_str, (const char *)statement_temp);
	}

	//DWORD	SashItem[MAX_CHARACTER_SASH_ITEMS];		//腰包內物品
	for(i=0; i<MAX_CHARACTER_SASH_ITEMS; i++)
	{
		sprintf((char *)statement_temp, 
			"`SashItem%02d` int(4) unsigned default '0',"
			,i+1);
		strcat((char *)statement_str, (const char *)statement_temp);
	}

	//DWORD	TransItem[MAX_CHARACTER_TRANS_ITEMS];	//QQ傳送欄物品
	for(i=0; i<MAX_CHARACTER_TRANS_ITEMS; i++)
	{
		sprintf((char *)statement_temp, 
			"`TransItem%02d` int(4) unsigned default '0',"
			,i+1);
		strcat((char *)statement_str, (const char *)statement_temp);
	}

	strcat((char *)statement_str, "`OnMouseItem` int(4) unsigned default '0',");
	strcat((char *)statement_str, "`TreasureItem` int(4) unsigned default '0',");
	strcat((char *)statement_str, "`Money` int(4) unsigned default '0',");

	//Society
	strcat((char *)statement_str, "`Sex` tinyint(1) unsigned default '',");
	strcat((char *)statement_str, "`Country` tinyint(1) unsigned default '',");
	strcat((char *)statement_str, "`GuildName` char(32) default '',");
	strcat((char *)statement_str, "`SpouseName` char(32) default '',");
	strcat((char *)statement_str, "`Career` tinyint(1) unsigned default '',");
	strcat((char *)statement_str, "`Office` int(4) unsigned default '',");
	strcat((char *)statement_str, "`Nobility` char(16) default '',");
	strcat((char *)statement_str, "`GoodEvil` int(4) default '',");
	strcat((char *)statement_str, "`Prestige` int(4) default '',");
	strcat((char *)statement_str, "`PkCount` int(4) unsigned default '',");
	strcat((char *)statement_str, "`PkedCount` int(4) unsigned default '',");

	//Mouse skill and Hot Key
	strcat((char *)statement_str, "`LandLeftSkill` smallint(2) default '-1',");
	strcat((char *)statement_str, "`LandRightSkill` smallint(2) default '-1',");
	for(i=0; i<MAX_CHARACTER_FN_SKILLS; i++)
	{
		sprintf((char *)statement_temp, 
			"`LandFnSkillNo%02d` smallint(2) default '-1',"
			"`LandFnSkillHand%02d` tinyint(1) unsigned default '',"
			,i+1, i+1);
		strcat((char *)statement_str, (const char *)statement_temp);
	}
	strcat((char *)statement_str, "`SeaLeftSkill` smallint(2) default '-1',");
	strcat((char *)statement_str, "`SeaRightSkill` smallint(2) default '-1',");
	for(i=0; i<MAX_CHARACTER_FN_SKILLS; i++)
	{
		sprintf((char *)statement_temp, 
			"`SeaFnSkillNo%02d` smallint(2) default '-1',"
			"`SeaFnSkillHand%02d` tinyint(1) unsigned default '',"
			,i+1, i+1);
		strcat((char *)statement_str, (const char *)statement_temp);
	}

	//Datas
	strcat((char *)statement_str, "`FinalAttack` smallint(2) unsigned default '',");
	strcat((char *)statement_str, "`FinalDefence` smallint(2) unsigned default '',");
	strcat((char *)statement_str, "`SeaFileIndex` int(4) unsigned default '',");
	for(i=0; i<MAX_CHARACTER_PARTS; i++)
	{
		sprintf((char *)statement_temp,
			"`PartRGB%02d` int(4) unsigned default '0',",
			i+1);
		strcat((char *)statement_str, (const char *)statement_temp);
	}
	// Jack, Added. [2/19/2003]
	strcat((char *)statement_str, "`NameColorTicks` int(4) unsigned default '0',");
	strcat((char *)statement_str, "`TotalOnlineTicks` int(4) unsigned default '0',");
	// Jack, Added. [5/9/2003]
	strcat((char *)statement_str, "`LeaderName` char(32) default '',");
	// Jack, Added. [5/14/2003]
	strcat((char *)statement_str, "`CareerLevel` tinyint(1) unsigned default '0',");

	//Doing
	strcat((char *)statement_str, "`DoingKind` int(4) default '',");

	strcat((char *)statement_str, "PRIMARY KEY (`Account`,`MainName`,`QQID`)");

	strcat((char *)statement_str, ") TYPE = MyISAM");

	hstmt = GetODBCStatementHandle();
	rc = SQLExecDirect(hstmt, (unsigned char*)statement_str, SQL_NTS);
	if(rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) 
	{
		return	-1;
	}

	return	0;
}


SLONG	AppendRecordToCharacterDB(TPOS_DB_CHARACTER *lpChar)
{
	HSTMT	hstmt;
	SQLRETURN	rc;
	SLONG	i;

	//
	// Append record to character database.
	//
	InitStatementStr();
	sprintf((char *)statement_str, "INSERT INTO pos_character (");

	//== Colume names
	//Name
	sprintf((char *)statement_temp, "Account,MainName,NickName,QQID,CharacterIndex,");
	strcat((char *)statement_str, (const char *)statement_temp);

	//Style
	sprintf((char *)statement_temp, "Color,Eyes,Mouth,MainNameColor,NickNameColor,MessageColor,TalkBackColor,Logo,LandFileIndex,");
	strcat((char *)statement_str, (const char *)statement_temp);

	//Position
	sprintf((char *)statement_temp, "ZoneName,X,Y,Z,Dir,StopRadius,");
	strcat((char *)statement_str, (const char *)statement_temp);
	
	//Speed
	sprintf((char *)statement_temp, "MoveSpeed,ShipSpeedX,ShipSpeedY,ShipSailSize,ShipTurn,ShipWeight,ShipDegreeDir,");
	strcat((char *)statement_str, (const char *)statement_temp);
	
	//State
	sprintf((char *)statement_temp, "BitState,");
	strcat((char *)statement_str, (const char *)statement_temp);
	
	//Str
	sprintf((char *)statement_temp, "InitStr,LevelUpStr,");
	strcat((char *)statement_str, (const char *)statement_temp);

	//Ins
	sprintf((char *)statement_temp, "InitIns,LevelUpIns,");
	strcat((char *)statement_str, (const char *)statement_temp);
	
	//Wit
	sprintf((char *)statement_temp, "InitWit,LevelUpWit,");
	strcat((char *)statement_str, (const char *)statement_temp);
	
	//Lucky
	sprintf((char *)statement_temp, "InitLucky,LevelUpLucky,");
	strcat((char *)statement_str, (const char *)statement_temp);
	
	//Attack
	sprintf((char *)statement_temp, "SightRange,FinalExplodeRate,");
	strcat((char *)statement_str, (const char *)statement_temp);

	//Defence
	sprintf((char *)statement_temp, "DodgeRate,ParryRate,");
	strcat((char *)statement_str, (const char *)statement_temp);
	
	//PropertyPoint
	sprintf((char *)statement_temp, "PropertyPoint,");
	strcat((char *)statement_str, (const char *)statement_temp);

	//Exp Lev
	sprintf((char *)statement_temp, "Exp, Level,");
	strcat((char *)statement_str, (const char *)statement_temp);
	
	//Hp Mp
	sprintf((char *)statement_temp, "Hp,MaxHp,HpRestore,Mp,MaxMp,MpRestore,");
	strcat((char *)statement_str, (const char *)statement_temp);

	//Skill
	//SHINT	SkillNo[36];			//技能編號
	//UHINT	SkillLevel[36];			//技能等級
	for(i=0; i<36; i++)
	{
		sprintf((char *)statement_temp, "SkillNo%02d,SkillLevel%02d,", i+1, i+1);
		strcat((char *)statement_str, (const char *)statement_temp);
	}
	
	//Equip
	sprintf((char *)statement_temp, 
		"EquHead,EquNeck,EquBody,EquWaist,EquGlove,EquWeapon,EquWrist,EquFeet,EquOtherA,EquOtherB,EquOtherC,"
		);
	strcat((char *)statement_str, (const char *)statement_temp);

	//Body Item
	//DWORD	BagItem[MAX_CHARACTER_BAG_ITEMS];		//背包內物品
	for(i=0; i<MAX_CHARACTER_BAG_ITEMS; i++)
	{
		sprintf((char *)statement_temp, "BagItem%02d,", i+1);
		strcat((char *)statement_str, (const char *)statement_temp);
	}

	//DWORD	SashItem[MAX_CHARACTER_SASH_ITEMS];		//腰包內物品
	for(i=0; i<MAX_CHARACTER_SASH_ITEMS; i++)
	{
		sprintf((char *)statement_temp, "SashItem%02d,", i+1);
		strcat((char *)statement_str, (const char *)statement_temp);
	}

	//DWORD	TransItem[MAX_CHARACTER_TRANS_ITEMS];	//QQ傳送欄物品
	for(i=0; i<MAX_CHARACTER_TRANS_ITEMS; i++)
	{
		sprintf((char *)statement_temp, "TransItem%02d,", i+1);
		strcat((char *)statement_str, (const char *)statement_temp);
	}

	sprintf((char *)statement_temp, "OnMouseItem,TreasureItem,Money,");
	strcat((char *)statement_str, (const char *)statement_temp);

	//Society
	sprintf((char *)statement_temp, 
		"Sex,Country,GuildName,SpouseName,Career,Office,Nobility,GoodEvil,Prestige,PkCount,PkedCount,"
		);
	strcat((char *)statement_str, (const char *)statement_temp);


	//Mouse skill and Hot Key
	sprintf((char *)statement_temp, "LandLeftSkill,LandRightSkill,");
	strcat((char *)statement_str, (const char *)statement_temp);
	for(i=0; i<MAX_CHARACTER_FN_SKILLS; i++)
	{
		sprintf((char *)statement_temp, "LandFnSkillNo%02d,LandFnSkillHand%02d,", i+1, i+1);
		strcat((char *)statement_str, (const char *)statement_temp);
	}

	sprintf((char *)statement_temp, "SeaLeftSkill,SeaRightSkill,");
	strcat((char *)statement_str, (const char *)statement_temp);
	for(i=0; i<MAX_CHARACTER_FN_SKILLS; i++)
	{
		sprintf((char *)statement_temp, "SeaFnSkillNo%02d,SeaFnSkillHand%02d,", i+1, i+1);
		strcat((char *)statement_str, (const char *)statement_temp);
	}

	//Datas
	sprintf((char *)statement_temp, "FinalAttack,FinalDefence,SeaFileIndex,");
	strcat((char *)statement_str, (const char *)statement_temp);
	for(i=0; i<MAX_CHARACTER_PARTS; i++)
	{
		sprintf((char *)statement_temp, "PartRGB%02d,", i+1);
		strcat((char *)statement_str, (const char *)statement_temp);
	}
	// Jack, Added. [2/19/2003]
	sprintf((char *)statement_temp, "NameColorTicks,TotalOnlineTicks,");
	strcat((char *)statement_str, (const char *)statement_temp);
	// Jack, Added. [5/9/2003]
	sprintf((char *)statement_temp, "LeaderName,");
	strcat((char *)statement_str, (const char *)statement_temp);
	// Jack, Added. [5/14/2003]
	sprintf((char *)statement_temp, "CareerLevel,");
	strcat((char *)statement_str, (const char *)statement_temp);

	//Doing
	sprintf((char *)statement_temp, "DoingKind");
	strcat((char *)statement_str, (const char *)statement_temp);
	

	//== Values
	strcat((char *)statement_str, ") VALUES (");

	// Colume values
	//Name
	sprintf((char *)statement_temp, "'%s','%s','%s',%d,%d,",
		lpChar->ID,
		lpChar->MainName,	
		lpChar->NickName,	
		lpChar->QQID,
		lpChar->Index
		);
	strcat((char *)statement_str, (const char *)statement_temp);

	//Style	
	sprintf((char *)statement_temp, "%d,%d,%d,%d,%d,%d,%d,%d,%d,",
		lpChar->Color,
		lpChar->Eyes,
		lpChar->Mouth,
		lpChar->MainNameColor,
		lpChar->NickNameColor,
		lpChar->MessageColor,
		lpChar->TalkBackColor,
		lpChar->Logo,
		lpChar->LandFileIndex);
	strcat((char *)statement_str, (const char *)statement_temp);

	//Position
	sprintf((char *)statement_temp, "'%s',%d,%d,%d,%d,%d,",
		lpChar->ZoneName,
		lpChar->X,
		lpChar->Y,
		lpChar->Z,
		lpChar->Dir,
		lpChar->StopRadius);
	strcat((char *)statement_str, (const char *)statement_temp);

	//Speed
	sprintf((char *)statement_temp, "%d,%d,%d,%d,%d,%d,%d,",
		lpChar->Mspeed,
		lpChar->FSpeedX,
		lpChar->FSpeedY,
		lpChar->SailSize,
		lpChar->Turn,
		lpChar->Weight,
		lpChar->DegreeDir);
	strcat((char *)statement_str, (const char *)statement_temp);

	//State
	sprintf((char *)statement_temp, "%d,",
		lpChar->BitState);
	strcat((char *)statement_str, (const char *)statement_temp);

	//Str
	sprintf((char *)statement_temp, "%d,%d,",
		lpChar->InitStr,
		lpChar->LevUpStr);
	strcat((char *)statement_str, (const char *)statement_temp);

	//Ins
	sprintf((char *)statement_temp, "%d,%d,",
		lpChar->InitIns,
		lpChar->LevUpIns);
	strcat((char *)statement_str, (const char *)statement_temp);

	//Wit
	sprintf((char *)statement_temp, "%d,%d,",
		lpChar->InitWit,
		lpChar->LevUpWit);
	strcat((char *)statement_str, (const char *)statement_temp);

	//Lucky
	sprintf((char *)statement_temp, "%d,%d,",
		lpChar->InitLucky,
		lpChar->LevUpLucky);
	strcat((char *)statement_str, (const char *)statement_temp);

	//Attack
	sprintf((char *)statement_temp, "%d,%d,",
		lpChar->SightRange,
		lpChar->FinalExplodeRate);
	strcat((char *)statement_str, (const char *)statement_temp);

	//Defence
	sprintf((char *)statement_temp, "%d,%d,",
		lpChar->DodgeRate,
		lpChar->ParryRate);
	strcat((char *)statement_str, (const char *)statement_temp);

	//PropertyPoint
	sprintf((char *)statement_temp, "%d,",
		lpChar->PropertyPoint);
	strcat((char *)statement_str, (const char *)statement_temp);

	//Exp Lev
	sprintf((char *)statement_temp, "%d,%d,",
		lpChar->Exp,
		lpChar->Level);
	strcat((char *)statement_str, (const char *)statement_temp);

	//Hp Mp
	sprintf((char *)statement_temp, "%d,%d,%d,%d,%d,%d,",
		lpChar->Hp,
		lpChar->MaxHp,
		lpChar->HpRes,
		lpChar->Mp,
		lpChar->MaxMp,
		lpChar->MpRes);
	strcat((char *)statement_str, (const char *)statement_temp);

	//SHINT	SkillNo[36];			//技能編號
	//UHINT	SkillLevel[36];			//技能等級
	for(i=0; i<36; i++)
	{
		sprintf((char *)statement_temp, "%d,%d,",
			lpChar->SkillNo[i],
			lpChar->SkillLevel[i]);
		strcat((char *)statement_str, (const char *)statement_temp);
	}
	
	//Equip
	sprintf((char *)statement_temp, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,",
		lpChar->EquHead,
		lpChar->EquNeck,
		lpChar->EquBody,
		lpChar->EquWaist,
		lpChar->EquGlove,
		lpChar->EquWeapon,
		lpChar->EquWrist,
		lpChar->EquFeet,
		lpChar->EquOtherA,
		lpChar->EquOtherB,
		lpChar->EquOtherC);
	strcat((char *)statement_str, (const char *)statement_temp);

	//Body Item
	//DWORD	BagItem[MAX_CHARACTER_BAG_ITEMS];		//背包內物品
	for(i=0; i<MAX_CHARACTER_BAG_ITEMS; i++)
	{
		sprintf((char *)statement_temp, "%d,",
			lpChar->BagItem[i]);
		strcat((char *)statement_str, (const char *)statement_temp);
	}

	//DWORD	SashItem[MAX_CHARACTER_SASH_ITEMS];		//腰包內物品
	for(i=0; i<MAX_CHARACTER_SASH_ITEMS; i++)
	{
		sprintf((char *)statement_temp, "%d,",
			lpChar->SashItem[i]);
		strcat((char *)statement_str, (const char *)statement_temp);
	}

	//DWORD	TransItem[MAX_CHARACTER_TRANS_ITEMS];	//QQ傳送欄物品
	for(i=0; i<MAX_CHARACTER_TRANS_ITEMS; i++)
	{
		sprintf((char *)statement_temp, "%d,",
			lpChar->TransItem[i]);
		strcat((char *)statement_str, (const char *)statement_temp);
	}

	sprintf((char *)statement_temp, "%d,%d,%d,",
		lpChar->OnMouseItem,
		lpChar->TreasureItem,
		lpChar->Money);
	strcat((char *)statement_str, (const char *)statement_temp);

	//Society
	sprintf((char *)statement_temp, "%d,%d,'%s','%s',%d,%d,'%s',%d,%d,%d,%d,",
		lpChar->Sex,
		lpChar->Country,
		lpChar->Guild,
		lpChar->Spouse,
		lpChar->Career,
		lpChar->Office,
		lpChar->Nobility,
		lpChar->GoodEvil,
		lpChar->Prestige,
		lpChar->PkCount,
		lpChar->PkedCount);
	strcat((char *)statement_str, (const char *)statement_temp);

	//Mouse skill and Hot Key(of Land)
	sprintf((char *)statement_temp, "%d,%d,",
		lpChar->LandLeftSkill,
		lpChar->LandRightSkill);
	strcat((char *)statement_str, (const char *)statement_temp);

	for(i=0; i<MAX_CHARACTER_FN_SKILLS; i++)
	{
		sprintf((char *)statement_temp, "%d,%d,",
			lpChar->LandFnSkillNo[i],
			lpChar->LandFnSkillHand[i]);
		strcat((char *)statement_str, (const char *)statement_temp);
	}

	//Mouse skill and Hot Key(of Sea)
	sprintf((char *)statement_temp, "%d,%d,",
		lpChar->SeaLeftSkill,
		lpChar->SeaRightSkill);
	strcat((char *)statement_str, (const char *)statement_temp);

	for(i=0; i<MAX_CHARACTER_FN_SKILLS; i++)
	{
		sprintf((char *)statement_temp, "%d,%d,",
			lpChar->SeaFnSkillNo[i],
			lpChar->SeaFnSkillHand[i]);
		strcat((char *)statement_str, (const char *)statement_temp);
	}

	//Datas
	sprintf((char *)statement_temp,"%d,%d,%d,",
		lpChar->FinalAttack,
		lpChar->FinalDefence,
		lpChar->SeaFileIndex
		);
	strcat((char *)statement_str, (const char *)statement_temp);
	for(i=0; i<MAX_CHARACTER_PARTS; i++)
	{
		sprintf((char *)statement_temp, "%u,",
			lpChar->PartRGB[i]);
		strcat((char *)statement_str, (const char *)statement_temp);
	}
	// Jack, Added. [2/19/2003]
	sprintf((char *)statement_temp,"%u,%u,",
		lpChar->NameColorTicks,
		lpChar->TotalOnlineTicks
		);
	strcat((char *)statement_str, (const char *)statement_temp);
	// Jack, Added. [5/9/2003]
	sprintf((char *)statement_temp,"'%s',", lpChar->LeaderName);
	strcat((char *)statement_str, (const char *)statement_temp);
	// Jack, Added. [5/14/2003]
	sprintf((char *)statement_temp,"%u,", lpChar->CareerLevel);
	strcat((char *)statement_str, (const char *)statement_temp);

	//Doing
	sprintf((char *)statement_temp, "%d",
		lpChar->DoingKind);
	strcat((char *)statement_str, (const char *)statement_temp);

	//Statement string end.
	strcat((char *)statement_str, ")");

	hstmt = GetODBCStatementHandle();
	rc = SQLExecDirect(hstmt, (unsigned char*)statement_str, SQL_NTS);
	if(rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) 
	{
		return	FALSE;
	}
	else
	{
		return	TRUE;
	}
}



SLONG	DeleteRecordFromCharacterDB(CHAR *szAccount, CHAR *szMainName)
{
	HSTMT	hstmt;
	SQLRETURN	rc;

	InitStatementStr();
	sprintf((char *)statement_str, 
		"DELETE FROM pos_character WHERE Account='%s' AND MainName='%s'",
		szAccount, szMainName);
	hstmt = GetODBCStatementHandle();
	rc = SQLExecDirect(hstmt, (unsigned char*)statement_str, SQL_NTS);
	if(rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) 
	{
		return	FALSE;
	}
	else
	{
		return	TRUE;
	}
}


SLONG	UpdateRecordOfCharacterDB(TPOS_DB_CHARACTER *lpChar)
{
	HSTMT	hstmt;
	SQLRETURN	rc;
	SLONG	i;


	//
	// Update record to character database by MainName.
	//
	InitStatementStr();
	sprintf((char *)statement_str, "UPDATE pos_character SET ");
	//"[Field1 = Value1,...N]"

	//== Colume names
	//Name
	sprintf((char *)statement_temp, 
		"NickName='%s',QQID=%d,CharacterIndex=%d,",
		lpChar->NickName,	
		lpChar->QQID,
		lpChar->Index);
	strcat((char *)statement_str, (const char *)statement_temp);

	//Style
	sprintf((char *)statement_temp, 
		"Color=%d,Eyes=%d,Mouth=%d,MainNameColor=%d,NickNameColor=%d,"
		"MessageColor=%d,TalkBackColor=%d,Logo=%d,LandFileIndex=%d,",
		lpChar->Color,
		lpChar->Eyes,
		lpChar->Mouth,
		lpChar->MainNameColor,
		lpChar->NickNameColor,
		lpChar->MessageColor,
		lpChar->TalkBackColor,
		lpChar->Logo,
		lpChar->LandFileIndex);
	strcat((char *)statement_str, (const char *)statement_temp);

	//Position
	sprintf((char *)statement_temp, 
		"ZoneName='%s',X=%d,Y=%d,Z=%d,Dir=%d,StopRadius=%d,",
		lpChar->ZoneName,
		lpChar->X,
		lpChar->Y,
		lpChar->Z,
		lpChar->Dir,
		lpChar->StopRadius);
	strcat((char *)statement_str, (const char *)statement_temp);
	
	//Speed
	sprintf((char *)statement_temp, 
		"MoveSpeed=%d,ShipSpeedX=%d,ShipSpeedY=%d,ShipSailSize=%d,"
		"ShipTurn=%d,ShipWeight=%d,ShipDegreeDir=%d,",
		lpChar->Mspeed,
		lpChar->FSpeedX,
		lpChar->FSpeedY,
		lpChar->SailSize,
		lpChar->Turn,
		lpChar->Weight,
		lpChar->DegreeDir);
	strcat((char *)statement_str, (const char *)statement_temp);
	
	//State
	sprintf((char *)statement_temp, "BitState=%d,",
		lpChar->BitState);
	strcat((char *)statement_str, (const char *)statement_temp);
	
	//Str
	sprintf((char *)statement_temp, "InitStr=%d,LevelUpStr=%d,",
		lpChar->InitStr,
		lpChar->LevUpStr);
	strcat((char *)statement_str, (const char *)statement_temp);

	//Ins
	sprintf((char *)statement_temp, "InitIns=%d,LevelUpIns=%d,",
		lpChar->InitIns,
		lpChar->LevUpIns);
	strcat((char *)statement_str, (const char *)statement_temp);
	
	//Wit
	sprintf((char *)statement_temp, "InitWit=%d,LevelUpWit=%d,",
		lpChar->InitWit,
		lpChar->LevUpWit);
	strcat((char *)statement_str, (const char *)statement_temp);
	
	//Lucky
	sprintf((char *)statement_temp, "InitLucky=%d,LevelUpLucky=%d,",
		lpChar->InitLucky,
		lpChar->LevUpLucky);
	strcat((char *)statement_str, (const char *)statement_temp);
	
	//Attack
	sprintf((char *)statement_temp, "SightRange=%d,FinalExplodeRate=%d,",
		lpChar->SightRange,
		lpChar->FinalExplodeRate);
	strcat((char *)statement_str, (const char *)statement_temp);

	//Defence
	sprintf((char *)statement_temp, "DodgeRate=%d,ParryRate=%d,",
		lpChar->DodgeRate,
		lpChar->ParryRate);
	strcat((char *)statement_str, (const char *)statement_temp);
	
	//PropertyPoint
	sprintf((char *)statement_temp, "PropertyPoint=%d,",
		lpChar->PropertyPoint);
	strcat((char *)statement_str, (const char *)statement_temp);

	//Exp Lev
	sprintf((char *)statement_temp, "Exp=%d, Level=%d,",
		lpChar->Exp,
		lpChar->Level);
	strcat((char *)statement_str, (const char *)statement_temp);
	
	//Hp Mp
	sprintf((char *)statement_temp, "Hp=%d,MaxHp=%d,HpRestore=%d,Mp=%d,MaxMp=%d,MpRestore=%d,",
		lpChar->Hp,
		lpChar->MaxHp,
		lpChar->HpRes,
		lpChar->Mp,
		lpChar->MaxMp,
		lpChar->MpRes);
	strcat((char *)statement_str, (const char *)statement_temp);

	//Skill
	//SHINT	SkillNo[36];			//技能編號
	//UHINT	SkillLevel[36];			//技能等級
	for(i=0; i<36; i++)
	{
		sprintf((char *)statement_temp, "SkillNo%02d=%d,SkillLevel%02d=%d,",
			i+1, lpChar->SkillNo[i],
			i+1, lpChar->SkillLevel[i]);
		strcat((char *)statement_str, (const char *)statement_temp);
	}
	
	//Equip
	sprintf((char *)statement_temp, 
		"EquHead=%d,EquNeck=%d,EquBody=%d,EquWaist=%d,EquGlove=%d,EquWeapon=%d,"
		"EquWrist=%d,EquFeet=%d,EquOtherA=%d,EquOtherB=%d,EquOtherC=%d,",
		lpChar->EquHead,
		lpChar->EquNeck,
		lpChar->EquBody,
		lpChar->EquWaist,
		lpChar->EquGlove,
		lpChar->EquWeapon,
		lpChar->EquWrist,
		lpChar->EquFeet,
		lpChar->EquOtherA,
		lpChar->EquOtherB,
		lpChar->EquOtherC);
	strcat((char *)statement_str, (const char *)statement_temp);

	//Body Item
	//DWORD	BagItem[MAX_CHARACTER_BAG_ITEMS];		//背包內物品
	for(i=0; i<MAX_CHARACTER_BAG_ITEMS; i++)
	{
		sprintf((char *)statement_temp, "BagItem%02d=%d,",
			i+1, lpChar->BagItem[i]);
		strcat((char *)statement_str, (const char *)statement_temp);
	}

	//DWORD	SashItem[MAX_CHARACTER_SASH_ITEMS];		//腰包內物品
	for(i=0; i<MAX_CHARACTER_SASH_ITEMS; i++)
	{
		sprintf((char *)statement_temp, "SashItem%02d=%d,",
			i+1, lpChar->SashItem[i]);
		strcat((char *)statement_str, (const char *)statement_temp);
	}

	//DWORD	TransItem[MAX_CHARACTER_TRANS_ITEMS];	//QQ傳送欄物品
	for(i=0; i<MAX_CHARACTER_TRANS_ITEMS; i++)
	{
		sprintf((char *)statement_temp, "TransItem%02d=%d,",
			i+1, lpChar->TransItem[i]);
		strcat((char *)statement_str, (const char *)statement_temp);
	}

	sprintf((char *)statement_temp, 
		"OnMouseItem=%d,TreasureItem=%d,Money=%d,",
		lpChar->OnMouseItem,
		lpChar->TransItem,
		lpChar->Money);
	strcat((char *)statement_str, (const char *)statement_temp);

	//Society
	sprintf((char *)statement_temp, 
		"Sex=%d,Country=%d,GuildName='%s',SpouseName='%s',"
		"Career=%d,Office=%d,Nobility='%s',GoodEvil=%d,"
		"Prestige=%d,PkCount=%d,PkedCount=%d,",
		lpChar->Sex,
		lpChar->Country,
		lpChar->Guild,
		lpChar->Spouse,
		lpChar->Career,
		lpChar->Office,
		lpChar->Nobility,
		lpChar->GoodEvil,
		lpChar->Prestige,
		lpChar->PkCount,
		lpChar->PkedCount);
	strcat((char *)statement_str, (const char *)statement_temp);


	//Mouse skill and Hot Key
	sprintf((char *)statement_temp, "LandLeftSkill=%d,LandRightSkill=%d,",
		lpChar->LandLeftSkill,
		lpChar->LandRightSkill);
	strcat((char *)statement_str, (const char *)statement_temp);
	for(i=0; i<MAX_CHARACTER_FN_SKILLS; i++)
	{
		sprintf((char *)statement_temp, 
			"LandFnSkillNo%02d=%d,LandFnSkillHand%02d=%d,",
			i+1, lpChar->LandFnSkillNo[i],
			i+1, lpChar->LandFnSkillHand[i]);
		strcat((char *)statement_str, (const char *)statement_temp);
	}

	sprintf((char *)statement_temp, 
		"SeaLeftSkill=%d,SeaRightSkill=%d,",
		lpChar->SeaLeftSkill,
		lpChar->SeaRightSkill);
	strcat((char *)statement_str, (const char *)statement_temp);
	for(i=0; i<MAX_CHARACTER_FN_SKILLS; i++)
	{
		sprintf((char *)statement_temp, 
			"SeaFnSkillNo%02d=%d,SeaFnSkillHand%02d=%d,",
			i+1, lpChar->SeaFnSkillNo[i],
			i+1, lpChar->SeaFnSkillHand[i]);
		strcat((char *)statement_str, (const char *)statement_temp);
	}

	//Datas
	sprintf((char *)statement_temp, 
		"FinalAttack=%d,FinalDefence=%d,SeaFileIndex=%d,",
		lpChar->FinalAttack,
		lpChar->FinalDefence,
		lpChar->SeaFileIndex
		);
	strcat((char *)statement_str, (const char *)statement_temp);
	for(i=0; i<MAX_CHARACTER_PARTS; i++)
	{
		sprintf((char *)statement_temp,
			"PartRGB%02d=%u,",
			i+1, lpChar->PartRGB[i]);
		strcat((char *)statement_str, (const char *)statement_temp);
	}
	// Jack, Added. [2/19/2003]
	sprintf((char *)statement_temp, 
		"NameColorTicks=%u,TotalOnlineTicks=%u,",
		lpChar->NameColorTicks,
		lpChar->TotalOnlineTicks
		);
	strcat((char *)statement_str, (const char *)statement_temp);
	// Jack, Added. [5/9/2003]
	sprintf((char *)statement_temp, "LeaderName='%s',", lpChar->LeaderName );
	strcat((char *)statement_str, (const char *)statement_temp);
	// Jack, Added. [5/14/2003]
	sprintf((char *)statement_temp, "CareerLevel=%u,", lpChar->CareerLevel);
	strcat((char *)statement_str, (const char *)statement_temp);

	//Doing
	sprintf((char *)statement_temp, "DoingKind=%d",
		lpChar->DoingKind);
	strcat((char *)statement_str, (const char *)statement_temp);
	
	//Statement string end.
	sprintf((char *)statement_temp, " WHERE MainName='%s'",
		lpChar->MainName);
	strcat((char *)statement_str, (const char *)statement_temp);

	hstmt = GetODBCStatementHandle();
	rc = SQLExecDirect(hstmt, (unsigned char*)statement_str, SQL_NTS);
	if(rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) 
	{
		return	FALSE;
	}
	else
	{
		return	TRUE;
	}
}


SLONG	GetRecordFromCharacterDBByMainName(TPOS_DB_CHARACTER *lpChar, CHAR *szMainName)
{
	HSTMT		hstmt;
	SQLRETURN	rc;
	
	InitStatementStr();
	sprintf((char *)statement_str, "SELECT * from pos_character WHERE MainName='%s'", szMainName );
	hstmt = GetODBCStatementHandle();
	rc = SQLExecDirect( hstmt, (unsigned char *)statement_str, SQL_NTS);
	if(rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) 
	{
		goto _error;
	}

	BindCharacterDBColumn(hstmt, lpChar);
	rc = SQLFetch(hstmt);
	if(rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) 
	{
		goto _error;
	}
	SQLCloseCursor(hstmt);
	return	TRUE;

_error:
	return	FALSE;
}


SLONG	GetRecordFromCharacterDBByAccountAndIndex(TPOS_DB_CHARACTER *lpChar, CHAR *szAccount, SLONG lIndex)
{
	HSTMT		hstmt;
	SQLRETURN	rc;
	
	InitStatementStr();
	sprintf((char *)statement_str, 
		"SELECT * from pos_character WHERE Account='%s' AND CharacterIndex=%d",
		szAccount, lIndex);
	hstmt = GetODBCStatementHandle();
	rc = SQLExecDirect( hstmt, (unsigned char *)statement_str, SQL_NTS);
	if(rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) 
	{
		goto _error;
	}

	BindCharacterDBColumn(hstmt, lpChar);
	rc = SQLFetch(hstmt);
	if(rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) 
	{
		goto _error;
	}
	SQLCloseCursor(hstmt);
	return	TRUE;

_error:
	return	FALSE;
}


SLONG	GetRecordFromCharacterDBByQQID(TPOS_DB_CHARACTER *lpChar, ULONG QQID)
{
	HSTMT		hstmt;
	SQLRETURN	rc;
	
	InitStatementStr();
	sprintf((char *)statement_str, 
		"SELECT * from pos_character WHERE QQID=%d",
		QQID);
	hstmt = GetODBCStatementHandle();
	rc = SQLExecDirect( hstmt, (unsigned char *)statement_str, SQL_NTS);
	if(rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) 
	{
		goto _error;
	}

	BindCharacterDBColumn(hstmt, lpChar);
	rc = SQLFetch(hstmt);
	if(rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) 
	{
		goto _error;
	}
	SQLCloseCursor(hstmt);
	return	TRUE;

_error:
	return	FALSE;
}


SLONG	CheckMainNameOfCharacterDB(CHAR *szMainName)
{
	HSTMT		hstmt;
	SQLRETURN	rc;
	SDWORD		cb;
	char		name[80];
	SLONG		result;

	InitStatementStr();
	sprintf((char *)statement_str, 
		"SELECT * from pos_character WHERE MainName='%s'",
		szMainName);
	hstmt = GetODBCStatementHandle();
	rc = SQLExecDirect( hstmt, (unsigned char *)statement_str, SQL_NTS);
	if(rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) 
	{
		result = NETGE_DB_ERROR_ODBC;
		goto _error;
	}

	SQLBindCol(hstmt, 2, SQL_CHAR, name, 32, &cb);
	rc = SQLFetch(hstmt);	
	SQLCloseCursor(hstmt);
	if(rc == SQL_SUCCESS || rc == SQL_SUCCESS_WITH_INFO) 
	{
		result = NETGE_DB_MAINNAME_EXIST;
		goto _error;
	}
	result = NETGE_DB_MAINNAME_AVAILABLE;
	return	result;

_error:
	return	result;
}


VOID	BindCharacterDBColumn(HSTMT hStmt, TPOS_DB_CHARACTER *lpChar)
{
	SDWORD	cb;
	SHINT	i;

	//Name
	SQLBindCol(hStmt, 1,	SQL_CHAR,		lpChar->ID,				sizeof(lpChar->ID),				&cb);
	SQLBindCol(hStmt, 2,	SQL_CHAR,		lpChar->MainName,		sizeof(lpChar->MainName),		&cb);
	SQLBindCol(hStmt, 3,	SQL_CHAR,		lpChar->NickName,		sizeof(lpChar->NickName),		&cb);
	SQLBindCol(hStmt, 4,	SQL_INTEGER,	&lpChar->QQID,			sizeof(lpChar->QQID),			&cb);
	SQLBindCol(hStmt, 5,	SQL_INTEGER,	&lpChar->Index,			sizeof(lpChar->Index),			&cb);

	//Style	
	SQLBindCol(hStmt, 6,	SQL_TINYINT,	&lpChar->Color,			sizeof(lpChar->Color),			&cb);
	SQLBindCol(hStmt, 7,	SQL_TINYINT,	&lpChar->Eyes,			sizeof(lpChar->Eyes),			&cb);
	SQLBindCol(hStmt, 8,	SQL_TINYINT,	&lpChar->Mouth,			sizeof(lpChar->Mouth),			&cb);
	SQLBindCol(hStmt, 9,	SQL_TINYINT,	&lpChar->MainNameColor, sizeof(lpChar->MainNameColor),	&cb);
	SQLBindCol(hStmt, 10,	SQL_TINYINT,	&lpChar->NickNameColor, sizeof(lpChar->NickNameColor),	&cb);
	SQLBindCol(hStmt, 11,	SQL_TINYINT,	&lpChar->MessageColor,	sizeof(lpChar->MessageColor),	&cb);
	SQLBindCol(hStmt, 12,	SQL_TINYINT,	&lpChar->TalkBackColor, sizeof(lpChar->TalkBackColor),	&cb);
	SQLBindCol(hStmt, 13,	SQL_INTEGER,	&lpChar->Logo,			sizeof(lpChar->Logo),			&cb);
	SQLBindCol(hStmt, 14,	SQL_INTEGER,	&lpChar->LandFileIndex,	sizeof(lpChar->LandFileIndex),	&cb);

	//Position
	SQLBindCol(hStmt, 15,	SQL_CHAR,		&lpChar->ZoneName,		sizeof(lpChar->ZoneName),		&cb);
	SQLBindCol(hStmt, 16,	SQL_INTEGER,	&lpChar->X,				sizeof(lpChar->X),				&cb);
	SQLBindCol(hStmt, 17,	SQL_INTEGER,	&lpChar->Y,				sizeof(lpChar->Y),				&cb);
	SQLBindCol(hStmt, 18,	SQL_INTEGER,	&lpChar->Z,				sizeof(lpChar->Z),				&cb);
	SQLBindCol(hStmt, 19,	SQL_TINYINT,	&lpChar->Dir,			sizeof(lpChar->Dir),			&cb);
	SQLBindCol(hStmt, 20,	SQL_INTEGER,	&lpChar->StopRadius,	sizeof(lpChar->StopRadius),		&cb);
	
	//Speed
	SQLBindCol(hStmt, 21,	SQL_INTEGER,	&lpChar->Mspeed,		sizeof(lpChar->Mspeed),			&cb);
	SQLBindCol(hStmt, 22,	SQL_INTEGER,	&lpChar->FSpeedX,		sizeof(lpChar->FSpeedX),		&cb);
	SQLBindCol(hStmt, 23,	SQL_INTEGER,	&lpChar->FSpeedY,		sizeof(lpChar->FSpeedY),		&cb);
	SQLBindCol(hStmt, 24,	SQL_SMALLINT,	&lpChar->SailSize,		sizeof(lpChar->SailSize),		&cb);
	SQLBindCol(hStmt, 25,	SQL_SMALLINT,	&lpChar->Turn,			sizeof(lpChar->Turn),			&cb);
	SQLBindCol(hStmt, 26,	SQL_SMALLINT,	&lpChar->Weight,		sizeof(lpChar->Weight),			&cb);
	SQLBindCol(hStmt, 27,	SQL_INTEGER,	&lpChar->DegreeDir,		sizeof(lpChar->DegreeDir),		&cb);

	//State
	SQLBindCol(hStmt, 28,	SQL_INTEGER,	&lpChar->BitState,		sizeof(lpChar->BitState),		&cb);
	
	//Str
	SQLBindCol(hStmt, 29,	SQL_SMALLINT,	&lpChar->InitStr,		sizeof(lpChar->InitStr),		&cb);
	SQLBindCol(hStmt, 30,	SQL_SMALLINT,	&lpChar->LevUpStr,		sizeof(lpChar->LevUpStr),		&cb);
	
	//Ins
	SQLBindCol(hStmt, 31,	SQL_SMALLINT,	&lpChar->InitIns,		sizeof(lpChar->InitIns),		&cb);
	SQLBindCol(hStmt, 32,	SQL_SMALLINT,	&lpChar->LevUpIns,		sizeof(lpChar->LevUpIns),		&cb);
	
	//Wit
	SQLBindCol(hStmt, 33,	SQL_SMALLINT,	&lpChar->InitWit,		sizeof(lpChar->InitWit),		&cb);
	SQLBindCol(hStmt, 34,	SQL_SMALLINT,	&lpChar->LevUpWit,		sizeof(lpChar->LevUpWit),		&cb);
	
	//Lucky
	SQLBindCol(hStmt, 35,	SQL_SMALLINT,	&lpChar->InitLucky,		sizeof(lpChar->InitLucky),		&cb);
	SQLBindCol(hStmt, 36,	SQL_SMALLINT,	&lpChar->LevUpLucky,	sizeof(lpChar->LevUpLucky),		&cb);
	
	//Attack
	SQLBindCol(hStmt, 37,	SQL_SMALLINT,	&lpChar->SightRange,		sizeof(lpChar->SightRange),			&cb);
	SQLBindCol(hStmt, 38,	SQL_SMALLINT,	&lpChar->FinalExplodeRate,	sizeof(lpChar->FinalExplodeRate),	&cb);

	//Defence
	SQLBindCol(hStmt, 39,	SQL_SMALLINT,	&lpChar->DodgeRate,		sizeof(lpChar->DodgeRate),		&cb);
	SQLBindCol(hStmt, 40,	SQL_SMALLINT,	&lpChar->ParryRate,		sizeof(lpChar->ParryRate),		&cb);
	
	//PropertyPoint
	SQLBindCol(hStmt, 41,	SQL_SMALLINT,	&lpChar->PropertyPoint, sizeof(lpChar->PropertyPoint),	&cb);

	//Exp Lev
	SQLBindCol(hStmt, 42,	SQL_INTEGER,	&lpChar->Exp,			sizeof(lpChar->Exp),		&cb);
	SQLBindCol(hStmt, 43,	SQL_SMALLINT,	&lpChar->Level,			sizeof(lpChar->Level),		&cb);
	
	//Hp Mp
	SQLBindCol(hStmt, 44,	SQL_SMALLINT,	&lpChar->Hp,			sizeof(lpChar->Hp),			&cb);
	SQLBindCol(hStmt, 45,	SQL_SMALLINT,	&lpChar->MaxHp,			sizeof(lpChar->MaxHp),		&cb);
	SQLBindCol(hStmt, 46,	SQL_SMALLINT,	&lpChar->HpRes,			sizeof(lpChar->HpRes),		&cb);
	SQLBindCol(hStmt, 47,	SQL_SMALLINT,	&lpChar->Mp,			sizeof(lpChar->Mp),			&cb);
	SQLBindCol(hStmt, 48,	SQL_SMALLINT,	&lpChar->MaxMp,			sizeof(lpChar->MaxMp),		&cb);
	SQLBindCol(hStmt, 49,	SQL_SMALLINT,	&lpChar->MpRes,			sizeof(lpChar->MpRes),		&cb);

	//SHINT	SkillNo[36];			//技能編號
	//UHINT	SkillLevel[36];			//技能等級
	for(i=0; i<36; i++)
	{
		SQLBindCol(hStmt, 50+i*2,	SQL_SMALLINT, &lpChar->SkillNo[i],		sizeof(lpChar->SkillNo[i]),		&cb);
		SQLBindCol(hStmt, 50+i*2+1,	SQL_SMALLINT, &lpChar->SkillLevel[i],	sizeof(lpChar->SkillLevel[i]),	&cb);
	}
	
	//Equip
	//50 + 36 * 2 = 122
	SQLBindCol(hStmt, 122,	SQL_INTEGER,	&lpChar->EquHead,		sizeof(lpChar->EquHead),	&cb);
	SQLBindCol(hStmt, 123,	SQL_INTEGER,	&lpChar->EquNeck,		sizeof(lpChar->EquNeck),	&cb);
	SQLBindCol(hStmt, 124,	SQL_INTEGER,	&lpChar->EquBody,		sizeof(lpChar->EquBody),	&cb);
	SQLBindCol(hStmt, 125,	SQL_INTEGER,	&lpChar->EquWaist,		sizeof(lpChar->EquWaist),	&cb);
	SQLBindCol(hStmt, 126,	SQL_INTEGER,	&lpChar->EquGlove,		sizeof(lpChar->EquGlove),	&cb);
	SQLBindCol(hStmt, 127,	SQL_INTEGER,	&lpChar->EquWeapon,		sizeof(lpChar->EquWeapon),	&cb);
	SQLBindCol(hStmt, 128,	SQL_INTEGER,	&lpChar->EquWrist,		sizeof(lpChar->EquWrist),	&cb);
	SQLBindCol(hStmt, 129,	SQL_INTEGER,	&lpChar->EquFeet,		sizeof(lpChar->EquFeet),	&cb);
	SQLBindCol(hStmt, 130,	SQL_INTEGER,	&lpChar->EquOtherA,		sizeof(lpChar->EquOtherA),	&cb);
	SQLBindCol(hStmt, 131,	SQL_INTEGER,	&lpChar->EquOtherB,		sizeof(lpChar->EquOtherB),	&cb);
	SQLBindCol(hStmt, 132,	SQL_INTEGER,	&lpChar->EquOtherC,		sizeof(lpChar->EquOtherC),	&cb);

	//Body Item
	//DWORD	BagItem[MAX_CHARACTER_BAG_ITEMS];	MAX_CHARACTER_BAG_ITEMS = 27
	for(i=0; i<27; i++)
	{
		SQLBindCol(hStmt, 133 + i, SQL_INTEGER, &lpChar->BagItem[i], sizeof(lpChar->BagItem[i]), &cb);
	}

	//DWORD	SashItem[MAX_CHARACTER_SASH_ITEMS];	MAX_CHARACTER_SASH_ITEMS = 4
	//133 + 27 = 160
	for(i=0; i<4; i++)
	{
		SQLBindCol(hStmt, 160 + i, SQL_INTEGER, &lpChar->SashItem[i], sizeof(lpChar->SashItem[i]), &cb);
	}

	//DWORD	TransItem[MAX_CHARACTER_TRANS_ITEMS]; MAX_CHARACTER_TRANS_ITEMS = 3
	//160 + 4 = 164
	for(i=0; i<3; i++)
	{
		SQLBindCol(hStmt, 164 + i, SQL_INTEGER, &lpChar->TransItem[i], sizeof(lpChar->TransItem[i]), &cb);
	}

	//164 + 3 = 167
	SQLBindCol(hStmt, 167,	SQL_INTEGER,	&lpChar->OnMouseItem,	sizeof(lpChar->OnMouseItem),	&cb);
	SQLBindCol(hStmt, 168,	SQL_INTEGER,	&lpChar->TreasureItem,	sizeof(lpChar->TreasureItem),	&cb);
	SQLBindCol(hStmt, 169,	SQL_INTEGER,	&lpChar->Money,			sizeof(lpChar->Money),			&cb);

	//Society
	SQLBindCol(hStmt, 170,	SQL_TINYINT,	&lpChar->Sex,			sizeof(lpChar->Sex),		&cb);
	SQLBindCol(hStmt, 171,	SQL_TINYINT,	&lpChar->Country,		sizeof(lpChar->Country),	&cb);
	SQLBindCol(hStmt, 172,	SQL_CHAR,		lpChar->Guild,			sizeof(lpChar->Guild),		&cb);
	SQLBindCol(hStmt, 173,	SQL_CHAR,		lpChar->Spouse,			sizeof(lpChar->Spouse),		&cb);
	SQLBindCol(hStmt, 174,	SQL_TINYINT,	&lpChar->Career,		sizeof(lpChar->Career),		&cb);
	SQLBindCol(hStmt, 175,	SQL_INTEGER,	&lpChar->Office,		sizeof(lpChar->Office),		&cb);
	SQLBindCol(hStmt, 176,	SQL_CHAR,		lpChar->Nobility,		sizeof(lpChar->Nobility),	&cb);

	SQLBindCol(hStmt, 177,	SQL_INTEGER,	&lpChar->GoodEvil,		sizeof(lpChar->GoodEvil),	&cb);
	SQLBindCol(hStmt, 178,	SQL_INTEGER,	&lpChar->Prestige,		sizeof(lpChar->Prestige),	&cb);
	SQLBindCol(hStmt, 179,	SQL_INTEGER,	&lpChar->PkCount,		sizeof(lpChar->PkCount),	&cb);
	SQLBindCol(hStmt, 180,	SQL_INTEGER,	&lpChar->PkedCount,		sizeof(lpChar->PkedCount),	&cb);

	//Mouse skill and Hot Key
	SQLBindCol(hStmt, 181,	SQL_SMALLINT,	&lpChar->LandLeftSkill,		sizeof(lpChar->LandLeftSkill),	&cb);
	SQLBindCol(hStmt, 182,	SQL_SMALLINT,	&lpChar->LandRightSkill,	sizeof(lpChar->LandRightSkill), &cb);

	//MAX_CHARACTER_FN_SKILLS = 8
	for(i=0; i<8; i++)
	{
		SQLBindCol(hStmt, 183+i*2,	 SQL_SMALLINT,	&lpChar->LandFnSkillNo[i],	 sizeof(lpChar->LandFnSkillNo[i]),   &cb);
		SQLBindCol(hStmt, 183+i*2+1, SQL_TINYINT,	&lpChar->LandFnSkillHand[i], sizeof(lpChar->LandFnSkillHand[i]), &cb);
	}

	//183 + 2 * 8 = 183 + 16 = 199
	SQLBindCol(hStmt, 199,	SQL_SMALLINT,	&lpChar->SeaLeftSkill,		sizeof(lpChar->SeaLeftSkill),	&cb);
	SQLBindCol(hStmt, 200,	SQL_SMALLINT,	&lpChar->SeaRightSkill,		sizeof(lpChar->SeaRightSkill),	&cb);

	//MAX_CHARACTER_FN_SKILLS = 8
	for(i=0; i<MAX_CHARACTER_FN_SKILLS; i++)
	{
		SQLBindCol(hStmt, 201+i*2,   SQL_SMALLINT, &lpChar->SeaFnSkillNo[i],   sizeof(lpChar->SeaFnSkillNo[i]),   &cb);
		SQLBindCol(hStmt, 201+i*2+1, SQL_TINYINT,  &lpChar->SeaFnSkillHand[i], sizeof(lpChar->SeaFnSkillHand[i]), &cb);
	}

	//201 + 2 * 8 = 201 + 16 = 217
	//Datas
	SQLBindCol(hStmt, 217,	SQL_SMALLINT,	&lpChar->FinalAttack,	sizeof(lpChar->FinalAttack),	&cb);
	SQLBindCol(hStmt, 218,	SQL_SMALLINT,	&lpChar->FinalDefence,	sizeof(lpChar->FinalDefence),	&cb);
	SQLBindCol(hStmt, 219,	SQL_INTEGER,	&lpChar->SeaFileIndex,	sizeof(lpChar->SeaFileIndex),	&cb);

	//MAX_CHARACTER_PARTS = 7
	for(i=0; i<7; i++)
	{
		SQLBindCol(hStmt, 220+i,	SQL_INTEGER,  &lpChar->PartRGB[i], sizeof(lpChar->PartRGB[i]), &cb);
	}

	//220 + 7 = 227
	// Jack, Added. [2/19/2003]
	SQLBindCol(hStmt, 227,	SQL_INTEGER,	&lpChar->NameColorTicks,   sizeof(lpChar->NameColorTicks),		&cb);
	SQLBindCol(hStmt, 228,	SQL_INTEGER,	&lpChar->TotalOnlineTicks, sizeof(lpChar->TotalOnlineTicks),	&cb);

	// Jack, Added. [5/9/2003]
	SQLBindCol(hStmt, 229,	SQL_CHAR,		lpChar->LeaderName,		sizeof(lpChar->LeaderName),		&cb);

	// Jack, Added. [5/14/2003]
	SQLBindCol(hStmt, 230,	SQL_TINYINT,	&lpChar->CareerLevel,	sizeof(lpChar->CareerLevel),	&cb);

	//Doing
	SQLBindCol(hStmt, 231,	SQL_INTEGER,	&lpChar->DoingKind,		sizeof(lpChar->DoingKind),		&cb);
}


/************************************************************************************************************/
/* ITEM DB FUNCTIONS                                                                                        */
/************************************************************************************************************/
SLONG	DeleteItemDBTable(void)
{
	HSTMT	hstmt;
	SQLRETURN	rc;

	InitStatementStr();
	sprintf((char *)statement_str,
		"DROP TABLE IF EXISTS `pos_item`"
		);
	hstmt = GetODBCStatementHandle();
	rc = SQLExecDirect(hstmt, (unsigned char*)statement_str, SQL_NTS);
	if(rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) 
	{
		return	-1;
	}
	return	0;
}

SLONG	CreateItemDBTable(void)
{
	HSTMT	hstmt;
	SQLRETURN	rc;
	
	InitStatementStr();
	sprintf((char *)statement_str, 
		"CREATE TABLE `pos_item` ("
		"`UniqueID` int(4) unsigned default '',"
		"`BaseID` smallint(2) unsigned default '',"
		"`Hp` tinyint(1) unsigned default '',"
		"`Attrib1` tinyint(1) unsigned default '',"
		"`Attrib2` tinyint(1) unsigned default '',"
		"`Attrib3` tinyint(1) unsigned default '',"
		"`Attrib4` tinyint(1) unsigned default '',"
		"`Attrib5` tinyint(1) unsigned default '',"
		"`ItemStatus` tinyint(1) unsigned default '',"
		"`MainName` char(32) default '',"
		"`ItemIndex` smallint(2) unsigned default ''"
		")TYPE = MyISAM"
		);
	hstmt = GetODBCStatementHandle();
	rc = SQLExecDirect(hstmt, (unsigned char*)statement_str, SQL_NTS);
	if(rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) 
	{
		return	-1;
	}
	return	0;
}

SLONG	AppendRecordToItemDB(TPOS_DB_ITEM *lpItem)
{
	HSTMT	hstmt;
	SQLRETURN	rc;

	InitStatementStr();
	sprintf((char *)statement_str, "INSERT INTO pos_item (");

	//== Colume names
	sprintf((char *)statement_temp, 
		"UniqueID,BaseID,Hp,"
		"Attrib1,Attrib2,Attrib3,Attrib4,Attrib5,"
		"ItemStatus,MainName,ItemIndex"
		);
	strcat((char *)statement_str, (const char *)statement_temp);

	//== Values
	strcat((char *)statement_str, ") VALUES (");

	// Colume values
	sprintf((char *)statement_temp, 
		"%d,%d,%d,%d,%d,%d,%d,%d,%d,'%s',%d",
		lpItem->ID,
		lpItem->BaseID,
		lpItem->Hp,
		lpItem->Attrib[0],
		lpItem->Attrib[1],
		lpItem->Attrib[2],
		lpItem->Attrib[3],
		lpItem->Attrib[4],
		lpItem->Status,
		lpItem->MainName,
		lpItem->Index
		);
	strcat((char *)statement_str, (const char *)statement_temp);

	//Statement string end.
	strcat((char *)statement_str, ")");

	hstmt = GetODBCStatementHandle();
	rc = SQLExecDirect(hstmt, (unsigned char*)statement_str, SQL_NTS);
	if(rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) 
	{
		return	FALSE;
	}
	else
	{
		return	TRUE;
	}
}

SLONG	DeleteRecordFromItemDB(ULONG UniqueID)
{
	HSTMT	hstmt;
	SQLRETURN	rc;

	InitStatementStr();
	sprintf((char *)statement_str, 
		"DELETE FROM pos_item WHERE UniqueID=%d",
		UniqueID);
	hstmt = GetODBCStatementHandle();
	rc = SQLExecDirect(hstmt, (unsigned char*)statement_str, SQL_NTS);
	if(rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) 
	{
		return	FALSE;
	}
	else
	{
		return	TRUE;
	}
}

SLONG	DeleteRecordFromItemDBByMainName(CHAR *szMainName)
{
	HSTMT	hstmt;
	SQLRETURN	rc;

	InitStatementStr();
	sprintf((char *)statement_str, 
		"DELETE FROM pos_item WHERE MainName='%s'",
		szMainName);
	hstmt = GetODBCStatementHandle();
	rc = SQLExecDirect(hstmt, (unsigned char*)statement_str, SQL_NTS);
	if(rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) 
	{
		return	FALSE;
	}
	else
	{
		return	TRUE;
	}
}

SLONG	UpdateRecordOfItemDBByUniqueID(TPOS_DB_ITEM *lpItem)
{
	HSTMT	hstmt;
	SQLRETURN	rc;

	InitStatementStr();
	sprintf((char *)statement_str, "UPDATE pos_item SET ");
	//"[Field1 = Value1,...N]"

	sprintf((char *)statement_temp, 
		"UniqueID=%d,BaseID=%d,Hp=%d,"
		"Attrib1=%d,Attrib2=%d,Attrib3=%d,Attrib4=%d,Attrib5=%d,"
		"ItemStatus=%d,MainName='%s',ItemIndex=%d",
		lpItem->ID,
		lpItem->BaseID,
		lpItem->Hp,
		lpItem->Attrib[0],
		lpItem->Attrib[1],
		lpItem->Attrib[2],
		lpItem->Attrib[3],
		lpItem->Attrib[4],
		lpItem->Status,
		lpItem->MainName,
		lpItem->Index
		);
	strcat((char*)statement_str, (const char *)statement_temp);

	//Statement string end.
	sprintf((char *)statement_temp, " WHERE UniqueID=%d",
		lpItem->ID);
	strcat((char*)statement_str, (const char *)statement_temp);

	hstmt = GetODBCStatementHandle();
	rc = SQLExecDirect(hstmt, (unsigned char*)statement_str, SQL_NTS);
	if(rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) 
	{
		return	FALSE;
	}
	else
	{
		return	TRUE;
	}
}

SLONG	UpdateRecordOfItemDBByMainNameAndIndex(TPOS_DB_ITEM *lpItem)
{
	HSTMT	hstmt;
	SQLRETURN	rc;

	InitStatementStr();
	sprintf((char *)statement_str, "UPDATE pos_item SET ");
	//"[Field1 = Value1,...N]"

	sprintf((char *)statement_temp, 
		"UniqueID=%d,BaseID=%d,Hp=%d,"
		"Attrib1=%d,Attrib2=%d,Attrib3=%d,Attrib4=%d,Attrib5=%d,"
		"ItemStatus=%d",
		lpItem->ID,
		lpItem->BaseID,
		lpItem->Hp,
		lpItem->Attrib[0],
		lpItem->Attrib[1],
		lpItem->Attrib[2],
		lpItem->Attrib[3],
		lpItem->Attrib[4],
		lpItem->Status
		);
	strcat((char*)statement_str, (const char *)statement_temp);

	//Statement string end.
	sprintf((char *)statement_temp, " WHERE MainName='%s' AND ItemIndex=%d",
		lpItem->MainName, lpItem->Index);
	strcat((char*)statement_str, (const char *)statement_temp);

	hstmt = GetODBCStatementHandle();
	rc = SQLExecDirect(hstmt, (unsigned char*)statement_str, SQL_NTS);
	if(rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) 
	{
		return	FALSE;
	}
	else
	{
		return	TRUE;
	}
}

SLONG	GetRecordFromItemDBByUniqueID(TPOS_DB_ITEM *lpItem, ULONG UniqueID)
{
	HSTMT		hstmt;
	SQLRETURN	rc;
	
	InitStatementStr();
	sprintf((char *)statement_str, 
		"SELECT * from pos_item WHERE UniqueID=%d",
		UniqueID );
	hstmt = GetODBCStatementHandle();
	rc = SQLExecDirect( hstmt, (unsigned char *)statement_str, SQL_NTS);
	if(rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) 
	{
		goto _error;
	}

	BindItemDBColumn(hstmt, lpItem);
	rc = SQLFetch(hstmt);
	if(rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) 
	{
		goto _error;
	}
	SQLCloseCursor(hstmt);
	return	TRUE;

_error:
	return	FALSE;
}


SLONG	GetRecordFromItemDBByMainNameAndIndex(TPOS_DB_ITEM *lpItem, CHAR *szMainName, SLONG lIndex)
{
	HSTMT		hstmt;
	SQLRETURN	rc;
	
	InitStatementStr();
	sprintf((char *)statement_str, 
		"SELECT * from pos_item WHERE MainName='%s' AND ItemIndex=%d",
		szMainName, lIndex );
	hstmt = GetODBCStatementHandle();
	rc = SQLExecDirect( hstmt, (unsigned char *)statement_str, SQL_NTS);
	if(rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) 
	{
		goto _error;
	}

	BindItemDBColumn(hstmt, lpItem);
	rc = SQLFetch(hstmt);
	if(rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) 
	{
		goto _error;
	}
	SQLCloseCursor(hstmt);
	return	TRUE;

_error:
	return	FALSE;
}


SLONG	CheckUniqueIDOfItemDB(ULONG UniqueID)
{
	HSTMT		hstmt;
	SQLRETURN	rc;
	SDWORD		cb;
	SLONG		result;
	ULONG		id;
	
	result = NETGE_DB_SUCCESS;
	InitStatementStr();
	sprintf((char *)statement_str, 
		"SELECT * from pos_item WHERE UniqueID=%d",
		UniqueID);
	hstmt = GetODBCStatementHandle();
	rc = SQLExecDirect( hstmt, (unsigned char *)statement_str, SQL_NTS);
	if(rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) 
	{
		result = NETGE_DB_ERROR_ODBC;
		goto _error;
	}

	SQLBindCol(hstmt, 1, SQL_INTEGER, &id, sizeof(id), &cb);
	rc = SQLFetch(hstmt);	
	SQLCloseCursor(hstmt);
	if(rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) 
	{
		result = NETGE_DB_ITEM_EXIST;
		goto _error;
	}

	result = NETGE_DB_ITEM_AVAILABLE;

	return	result;

_error:
	return	result;
}


VOID	BindItemDBColumn(HSTMT hStmt, TPOS_DB_ITEM *lpItem)
{
	SDWORD	cb;

	SQLBindCol(hStmt, 1,	SQL_INTEGER,	&lpItem->ID,			sizeof(lpItem->ID),				&cb);
	SQLBindCol(hStmt, 2,	SQL_SMALLINT,	&lpItem->BaseID,		sizeof(lpItem->BaseID),			&cb);
	SQLBindCol(hStmt, 3,	SQL_TINYINT,	&lpItem->Hp,			sizeof(lpItem->Hp),				&cb);
	SQLBindCol(hStmt, 4,	SQL_TINYINT,	&lpItem->Attrib[0],		sizeof(lpItem->Attrib[0]),		&cb);
	SQLBindCol(hStmt, 5,	SQL_TINYINT,	&lpItem->Attrib[1],		sizeof(lpItem->Attrib[1]),		&cb);
	SQLBindCol(hStmt, 6,	SQL_TINYINT,	&lpItem->Attrib[2],		sizeof(lpItem->Attrib[2]),		&cb);
	SQLBindCol(hStmt, 7,	SQL_TINYINT,	&lpItem->Attrib[3],		sizeof(lpItem->Attrib[3]),		&cb);
	SQLBindCol(hStmt, 8,	SQL_TINYINT,	&lpItem->Attrib[4],		sizeof(lpItem->Attrib[4]),		&cb);
	SQLBindCol(hStmt, 9,	SQL_TINYINT,	&lpItem->Status,		sizeof(lpItem->Status),			&cb);
	SQLBindCol(hStmt, 10,	SQL_CHAR,		lpItem->MainName,		sizeof(lpItem->MainName),		&cb);
	SQLBindCol(hStmt, 11,	SQL_SMALLINT,	&lpItem->Index,			sizeof(lpItem->Index),			&cb);
}


/************************************************************************************************************/
/* QQ DB FUNCTIONS                                                                                          */
/************************************************************************************************************/
SLONG	DeleteQQDBTable(void)
{
	HSTMT	hstmt;
	SQLRETURN	rc;

	InitStatementStr();
	sprintf((char *)statement_str,
		"DROP TABLE IF EXISTS `pos_qq`"
		);
	hstmt = GetODBCStatementHandle();
	rc = SQLExecDirect(hstmt, (unsigned char*)statement_str, SQL_NTS);
	if(rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) 
	{
		return	-1;
	}
	return	0;
}


SLONG	CreateQQDBTable(void)
{
	HSTMT	hstmt;
	SQLRETURN	rc;
	
	InitStatementStr();
	sprintf((char *)statement_str, 
		"CREATE TABLE `pos_qq` ("
		"`ID` int(4) unsigned NOT NULL default '0',"
		"`Config` int(4) unsigned default '0',"
		"`WorldServerName` char(32) NOT NULL default '',"
		"`AccountName` char(32) NOT NULL default '',"
		"`CharacterName` char(32) NOT NULL default '',"
		"`GuildName` char(32) default '',"
		"`LeaderName` char(32) default '',"
		"`NickName` char(32) default '',"
		"`Country` tinyint(1) unsigned default '',"
		"`State` tinyint(1) unsigned NOT NULL default '',"
		"`Career` tinyint(1) unsigned default '',"
		"`Level` int(4) unsigned default '0',"
		"`Friend` blob,"
		"`GuildFriend` blob,"
		"PRIMARY KEY (`ID`)"
		") TYPE = MyISAM"
		);
	hstmt = GetODBCStatementHandle();
	rc = SQLExecDirect(hstmt, (unsigned char*)statement_str, SQL_NTS);
	if(rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) 
	{
		return	-1;
	}
	return	0;
}

SLONG	AppendRecordToQQDB(TPOS_DB_QQ *lpQQ)
{
	HSTMT	hstmt;
	SQLRETURN	rc;
	char	*end;

	InitStatementStr();
	sprintf((char *)statement_str, "INSERT INTO pos_qq (");

	//== Colume names
	sprintf((char *)statement_temp, 
		"ID,Config,WorldServerName,AccountName,CharacterName,"
		"GuildName,LeaderName,NickName,Country,State,"
		"Career,Level,Friend,GuildFriend"
		);
	strcat((char *)statement_str, (const char *)statement_temp);

	//== Values
	strcat((char *)statement_str, ") VALUES (");

	// Colume values
	sprintf((char *)statement_temp, 
		"%d,%d,'%s','%s','%s','%s','%s','%s',%d,%d,%d,%d,",
		lpQQ->ID,
		lpQQ->Config,
		lpQQ->WorldServerName,
		lpQQ->AccountName,
		lpQQ->CharacterName,
		lpQQ->GuildName,
		lpQQ->LeaderName,
		lpQQ->NickName,
		lpQQ->Country,
		lpQQ->State,
		lpQQ->Career,
		lpQQ->Level
		);
	strcat((char *)statement_str, (const char *)statement_temp);

	end = statement_str + strlen(statement_str);
	*end++ = '\'';
	end += MakeMySQLEscapeString(end, (const char *)lpQQ->Friend, sizeof(lpQQ->Friend));
	*end++ = '\'';
	*end++ = ',';

	*end++ = '\'';
	end += MakeMySQLEscapeString(end, (const char *)lpQQ->GuildFriend, sizeof(lpQQ->GuildFriend));
	*end++ = '\'';

	//Statement string end.
	*end++ = ')';

	hstmt = GetODBCStatementHandle();
	rc = SQLExecDirect(hstmt, (unsigned char*)statement_str, SQL_NTS);
	if(rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) 
	{
		return	FALSE;
	}
	else
	{
		return	TRUE;
	}
	return	FALSE;
}

SLONG	DeleteRecordFromQQDBByID(ULONG ID)
{
	HSTMT	hstmt;
	SQLRETURN	rc;

	InitStatementStr();
	sprintf((char *)statement_str, "DELETE FROM pos_qq WHERE ID=%d", ID);
	hstmt = GetODBCStatementHandle();
	rc = SQLExecDirect(hstmt, (unsigned char*)statement_str, SQL_NTS);
	if(rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) 
	{
		return	FALSE;
	}
	else
	{
		return	TRUE;
	}
}


SLONG	UpdateRecordOfQQDB(TPOS_DB_QQ *lpQQ)
{
	HSTMT	hstmt;
	SQLRETURN	rc;
	char	*end;

	//
	// Update record to account database by Account.
	//
	InitStatementStr();
	sprintf((char *)statement_str, "UPDATE pos_qq SET ");
	//"[Field1 = Value1,...N]"

	sprintf((char *)statement_temp, 
		"Config=%d,"
		"WorldServerName='%s',AccountName='%s',"
		"CharacterName='%s',GuildName='%s',LeaderName='%s',NickName='%s',"
		"Country=%d,State=%d,Career=%d,Level=%d,Friend=",
		lpQQ->Config,
		lpQQ->WorldServerName,
		lpQQ->AccountName,
		lpQQ->CharacterName,
		lpQQ->GuildName,
		lpQQ->LeaderName,
		lpQQ->NickName,
		lpQQ->Country,
		lpQQ->State,
		lpQQ->Career,
		lpQQ->Level
		);
	strcat((char*)statement_str, (const char *)statement_temp);

	end = statement_str + strlen((const char *)statement_str);
	*end++ = '\'';
	end += MakeMySQLEscapeString(end, (const char *)lpQQ->Friend, sizeof(lpQQ->Friend));
	*end++ = '\'';
	*end++ = ',';

	sprintf((char *)statement_temp, "GuildFriend=");
	strcat(statement_str, (const char *)statement_temp);
	end += strlen((const char *)statement_temp);
	*end++ = '\'';
	end += MakeMySQLEscapeString(end, (const char *)lpQQ->GuildFriend, sizeof(lpQQ->GuildFriend));
	*end++ = '\'';

	//Statement string end.
	sprintf((char *)statement_temp, " WHERE ID=%d", lpQQ->ID);
	strcat((char*)statement_str, (const char *)statement_temp);

	hstmt = GetODBCStatementHandle();
	rc = SQLExecDirect(hstmt, (unsigned char*)statement_str, SQL_NTS);
	if(rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) 
	{
		return	FALSE;
	}
	else
	{
		return	TRUE;
	}
}

SLONG	GetRecordFromQQDBByID(TPOS_DB_QQ *lpQQ, ULONG ID)
{
	HSTMT		hstmt;
	SQLRETURN	rc;
	int		len;
	
	InitStatementStr();
	sprintf((char *)statement_str, "SELECT * from pos_qq WHERE ID=%d", ID );
	hstmt = GetODBCStatementHandle();
	rc = SQLExecDirect( hstmt, (unsigned char *)statement_str, SQL_NTS);
	if(rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) 
	{
		goto _error;
	}

	BindQQDBColumn(hstmt, lpQQ);
	rc = SQLFetch(hstmt);
	if(rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) 
	{
		goto _error;
	}

	//column 13: "`Friend` blob,"
	//column 14: "`GuildFriend` blob"
// 	SQLGetData(hstmt, 13, SQL_BINARY, lpQQ->Friend, sizeof(lpQQ->Friend), &len);
// 	SQLGetData(hstmt, 14, SQL_BINARY, lpQQ->GuildFriend, sizeof(lpQQ->GuildFriend), &len);

	SQLCloseCursor(hstmt);
	return	TRUE;

_error:
	return	FALSE;
}


SLONG	CheckIDOfQQDB(ULONG ID)
{
	HSTMT		hstmt;
	SQLRETURN	rc;
	SDWORD		cb;
	ULONG		id;
	SLONG		result;

	InitStatementStr();
	sprintf((char *)statement_str, "SELECT * from pos_qq WHERE ID=%d", ID);
	hstmt = GetODBCStatementHandle();
	rc = SQLExecDirect( hstmt, (unsigned char *)statement_str, SQL_NTS);
	if(rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) 
	{
		result = NETGE_DB_ERROR_ODBC;
		goto _error;
	}

	SQLBindCol(hstmt, 1, SQL_INTEGER, &id, sizeof(id), &cb);
	rc = SQLFetch(hstmt);
	SQLCloseCursor(hstmt);
	if(rc == SQL_SUCCESS || rc == SQL_SUCCESS_WITH_INFO) 
	{
		result = NETGE_DB_QQ_EXIST;
		goto _error;
	}
	result = NETGE_DB_QQ_AVAILABLE;

	return	result;

_error:
	return	result;
}

VOID	BindQQDBColumn(HSTMT hStmt, TPOS_DB_QQ *lpQQ)
{
	SDWORD	cb;

	SQLBindCol(hStmt, 1,	SQL_INTEGER,	&lpQQ->ID,				sizeof(lpQQ->ID),				&cb);
	SQLBindCol(hStmt, 2,	SQL_INTEGER,	&lpQQ->Config,			sizeof(lpQQ->Config),			&cb);
	SQLBindCol(hStmt, 3,	SQL_CHAR,		lpQQ->WorldServerName,	sizeof(lpQQ->WorldServerName),	&cb);
	SQLBindCol(hStmt, 4,	SQL_CHAR,		lpQQ->AccountName,		sizeof(lpQQ->AccountName),		&cb);
	SQLBindCol(hStmt, 5,	SQL_CHAR,		lpQQ->CharacterName,	sizeof(lpQQ->CharacterName),	&cb);
	SQLBindCol(hStmt, 6,	SQL_CHAR,		lpQQ->GuildName,		sizeof(lpQQ->GuildName),		&cb);
	SQLBindCol(hStmt, 7,	SQL_CHAR,		lpQQ->LeaderName,		sizeof(lpQQ->LeaderName),		&cb);
	SQLBindCol(hStmt, 8,	SQL_CHAR,		lpQQ->NickName,			sizeof(lpQQ->NickName),			&cb);
	SQLBindCol(hStmt, 9,	SQL_TINYINT,	&lpQQ->Country,			sizeof(lpQQ->Country),			&cb);
	SQLBindCol(hStmt, 10,	SQL_TINYINT,	&lpQQ->State,			sizeof(lpQQ->State),			&cb);
	SQLBindCol(hStmt, 11,	SQL_TINYINT,	&lpQQ->Career,			sizeof(lpQQ->Career),			&cb);
	SQLBindCol(hStmt, 12,	SQL_INTEGER,	&lpQQ->Level,			sizeof(lpQQ->Level),			&cb);
	//column 13: "`Friend` blob,"
	//column 14: "`GuildFriend` blob"
}
/************************************************************************************************************/
/* QQMSG DB FUNCTIONS                                                                                       */
/************************************************************************************************************/
SLONG	DeleteQQMsgDBTable(void)
{
	HSTMT	hstmt;
	SQLRETURN	rc;

	InitStatementStr();
	sprintf((char *)statement_str,
		"DROP TABLE IF EXISTS `pos_qq_msg`"
		);
	hstmt = GetODBCStatementHandle();
	rc = SQLExecDirect(hstmt, (unsigned char*)statement_str, SQL_NTS);
	if(rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) 
	{
		return	-1;
	}
	return	0;
}


SLONG	CreateQQMsgDBTable(void)
{
	HSTMT	hstmt;
	SQLRETURN	rc;
	
	InitStatementStr();
	sprintf((char *)statement_str, 
		"CREATE TABLE `pos_qq_msg` ("
		"`SendID` int(4) unsigned NOT NULL default '0',"
		"`RecvID` int(4) unsigned NOT NULL default '0',"
		"`MsgTime` int(4) unsigned NOT NULL default '0',"
		"`MsgStr` blob,"
		"PRIMARY KEY (`SendID`,`RecvID`,`MsgTime`)"
		") TYPE = MyISAM"
		);
	hstmt = GetODBCStatementHandle();
	rc = SQLExecDirect(hstmt, (unsigned char*)statement_str, SQL_NTS);
	if(rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) 
	{
		return	-1;
	}
	return	0;
}

SLONG	AppendRecordToQQMsgDB(TPOS_DB_QQMSG *lpMsg)
{
	HSTMT	hstmt;
	SQLRETURN	rc;
	char	*end;

	InitStatementStr();
	sprintf((char *)statement_str, "INSERT INTO pos_qq_msg (");

	//== Colume names
	sprintf((char *)statement_temp, 
		"SendID, RecvID, MsgTime, MsgStr"
		);
	strcat((char *)statement_str, (const char *)statement_temp);

	//== Values
	strcat((char *)statement_str, ") VALUES (");

	// Colume values
	sprintf((char *)statement_temp, 
		"%d,%d,%d,",
		lpMsg->SendID,
		lpMsg->RecvID,
		lpMsg->MsgTime
		);
	strcat((char *)statement_str, (const char *)statement_temp);

	end = statement_str + strlen((const char *)statement_str);
	*end++ = '\'';
	end += MakeMySQLEscapeString(end, (const char *)lpMsg->MsgStr, sizeof(lpMsg->MsgStr));
	*end++ = '\'';

	//Statement string end.
	strcat((char *)statement_str, ")");

	hstmt = GetODBCStatementHandle();
	rc = SQLExecDirect(hstmt, (unsigned char*)statement_str, SQL_NTS);
	if(rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) 
	{
		return	FALSE;
	}
	else
	{
		return	TRUE;
	}
}

SLONG	DeleteReocrdFromQQMsgDBByRecvID(ULONG ID)
{
	HSTMT	hstmt;
	SQLRETURN	rc;

	InitStatementStr();
	sprintf((char *)statement_str, "DELETE FROM pos_qq_msg WHERE RecvID=%d", ID);
	hstmt = GetODBCStatementHandle();
	rc = SQLExecDirect(hstmt, (unsigned char*)statement_str, SQL_NTS);
	if(rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) 
	{
		return	FALSE;
	}
	else
	{
		return	TRUE;
	}
}


SLONG	DeleteRecordFromQQMsgDBBySendID(ULONG ID)
{
	HSTMT	hstmt;
	SQLRETURN	rc;

	InitStatementStr();
	sprintf((char *)statement_str, "DELETE FROM pos_qq_msg WHERE SendID=%d", ID);
	hstmt = GetODBCStatementHandle();
	rc = SQLExecDirect(hstmt, (unsigned char*)statement_str, SQL_NTS);
	if(rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) 
	{
		return	FALSE;
	}
	else
	{
		return	TRUE;
	}
}

SLONG	DeleteRecordFromQQMsgDBByMsgTime(ULONG MsgTime)
{
	HSTMT	hstmt;
	SQLRETURN	rc;

	InitStatementStr();
	sprintf((char *)statement_str, "DELETE FROM pos_qq_msg WHERE MsgTime=%d", MsgTime);
	hstmt = GetODBCStatementHandle();
	rc = SQLExecDirect(hstmt, (unsigned char*)statement_str, SQL_NTS);
	if(rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) 
	{
		return	FALSE;
	}
	else
	{
		return	TRUE;
	}
}

SLONG	GetRecordFromQQMsgDBByRecvID(TPOS_DB_QQMSG *lpMsg, ULONG ID)
{
	HSTMT		hstmt;
	SQLRETURN	rc;
	int		len;
	
	InitStatementStr();
	sprintf((char *)statement_str, "SELECT * from pos_qq_msg WHERE RecvID=%d", ID);
	hstmt = GetODBCStatementHandle();
	rc = SQLExecDirect( hstmt, (unsigned char *)statement_str, SQL_NTS);
	if(rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) 
	{
		goto _error;
	}

	BindQQMsgDBColumn(hstmt, lpMsg);
	rc = SQLFetch(hstmt);
	if(rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) 
	{
		goto _error;
	}
	//column 4: "`MsgStr` blob"
//	SQLGetData(hstmt, 4, SQL_BINARY, lpMsg->MsgStr, sizeof(lpMsg->MsgStr), &len);
	SQLCloseCursor(hstmt);
	return	TRUE;

_error:
	return	FALSE;
}

SLONG	GetRecordFromQQMsgDBBySendID(TPOS_DB_QQMSG *lpMsg, ULONG ID)
{
	HSTMT		hstmt;
	SQLRETURN	rc;
	int		len;
	
	InitStatementStr();
	sprintf((char *)statement_str, "SELECT * from pos_qq_msg WHERE SendID=%d", ID);
	hstmt = GetODBCStatementHandle();
	rc = SQLExecDirect( hstmt, (unsigned char *)statement_str, SQL_NTS);
	if(rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) 
	{
		goto _error;
	}

	BindQQMsgDBColumn(hstmt, lpMsg);
	rc = SQLFetch(hstmt);
	if(rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) 
	{
		goto _error;
	}
	//column 4: "`MsgStr` blob"
//	SQLGetData(hstmt, 4, SQL_BINARY, lpMsg->MsgStr, sizeof(lpMsg->MsgStr), &len);
	SQLCloseCursor(hstmt);
	return	TRUE;

_error:
	return	FALSE;
}

VOID	BindQQMsgDBColumn(HSTMT hStmt, TPOS_DB_QQMSG *lpMsg)
{
	SDWORD	cb;

	SQLBindCol(hStmt, 1,	SQL_INTEGER,	&lpMsg->SendID,			sizeof(lpMsg->SendID),			&cb);
	SQLBindCol(hStmt, 2,	SQL_INTEGER,	&lpMsg->RecvID,			sizeof(lpMsg->RecvID),			&cb);
	SQLBindCol(hStmt, 3,	SQL_INTEGER,	&lpMsg->MsgTime,		sizeof(lpMsg->MsgTime),			&cb);
	//column 4: "`MsgStr` blob"
}

/************************************************************************************************************/
/* BANK DB FUNCTIONS                                                                                        */
/************************************************************************************************************/
SLONG	DeleteBankDBTable(void)
{
	HSTMT	hstmt;
	SQLRETURN	rc;

	InitStatementStr();
	sprintf((char *)statement_str,
		"DROP TABLE IF EXISTS `pos_bank`"
		);
	hstmt = GetODBCStatementHandle();
	rc = SQLExecDirect(hstmt, (unsigned char*)statement_str, SQL_NTS);
	if(rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) 
	{
		return	-1;
	}
	return	0;
}

SLONG	CreateBankDBTable(void)
{
	HSTMT	hstmt;
	SQLRETURN	rc;
	SLONG	i;

	InitStatementStr();
	sprintf((char *)statement_str, 
		"CREATE TABLE `pos_bank` (");

	//char	MainName[32];
	strcpy((char *)statement_temp, 
		"`MainName` char(32) NOT NULL default '',"
		);
	strcat((char *)statement_str, (const char *)statement_temp);

	//ULONG	Money;								//銀行的存款
	sprintf((char *)statement_temp, 
		"`Money` int(4) unsigned NOT NULL default '0',"
		);
	strcat((char *)statement_str, (const char *)statement_temp);

	//DWORD	Item[MAX_CHARACTER_BANK_ITEMS];		//銀行的物品
	for(i=0; i<MAX_CHARACTER_BANK_ITEMS; i++)
	{
		sprintf((char *)statement_temp, 
			"`Item%02d` int(4) unsigned default '0',"
			,i+1);
		strcat((char *)statement_str, (const char *)statement_temp);
	}

	sprintf((char *)statement_temp, 
		"PRIMARY KEY (`MainName`)"
		") TYPE = MyISAM"
		);
	strcat((char *)statement_str, (const char *)statement_temp);

	hstmt = GetODBCStatementHandle();
	rc = SQLExecDirect(hstmt, (unsigned char*)statement_str, SQL_NTS);
	if(rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) 
	{
		return	-1;
	}
	return	0;
}


SLONG	AppendRecordToBankDB(TPOS_DB_BANK *lpBank)
{
	HSTMT	hstmt;
	SQLRETURN	rc;
	SLONG	i;

	InitStatementStr();
	sprintf((char *)statement_str, "INSERT INTO pos_bank (");

	//== Colume names
	sprintf((char *)statement_temp, 
		"MainName,Money"
		);
	strcat((char *)statement_str, (const char *)statement_temp);
	for(i=0; i<MAX_CHARACTER_BANK_ITEMS; i++)
	{
		sprintf((char *)statement_temp, ",Item%02d", i + 1);
		strcat((char *)statement_str, (const char *)statement_temp);
	}

	//== Values
	strcat((char *)statement_str, ") VALUES (");

	// Colume values
	sprintf((char *)statement_temp, 
		"'%s',%u",
		lpBank->MainName,
		lpBank->Money
		);
	strcat((char *)statement_str, (const char *)statement_temp);
	for(i=0; i<MAX_CHARACTER_BANK_ITEMS; i++)
	{
		sprintf((char *)statement_temp, ",%u", lpBank->Item[i]);
		strcat((char *)statement_str, (const char *)statement_temp);
	}

	//Statement string end.
	strcat((char *)statement_str, ")");

	hstmt = GetODBCStatementHandle();
	rc = SQLExecDirect(hstmt, (unsigned char*)statement_str, SQL_NTS);
	if(rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) 
	{
		return	FALSE;
	}
	else
	{
		return	TRUE;
	}
}

SLONG	DeleteRecordFromBankDB(CHAR *szMainName)
{
	HSTMT	hstmt;
	SQLRETURN	rc;

	InitStatementStr();
	sprintf((char *)statement_str, 
		"DELETE FROM pos_bank WHERE MainName='%s'",
		szMainName);
	hstmt = GetODBCStatementHandle();
	rc = SQLExecDirect(hstmt, (unsigned char*)statement_str, SQL_NTS);
	if(rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) 
	{
		return	FALSE;
	}
	else
	{
		return	TRUE;
	}
}

SLONG	UpdateRecordOfBankDB(TPOS_DB_BANK *lpBank)
{
	HSTMT	hstmt;
	SQLRETURN	rc;
	SLONG	i;

	InitStatementStr();
	sprintf((char *)statement_str, "UPDATE pos_bank SET ");

	//"[Field1 = Value1,...N]"
	sprintf((char *)statement_temp, "Money=%u", lpBank->Money);
	strcat((char*)statement_str, (const char *)statement_temp);
	for(i=0; i<MAX_CHARACTER_BANK_ITEMS; i++)
	{
		sprintf((char *)statement_temp, ",Item%02d=%u", i+1, lpBank->Item[i]);
		strcat((char*)statement_str, (const char *)statement_temp);
	}

	//Statement string end.
	sprintf((char *)statement_temp, " WHERE MainName='%s'",
		lpBank->MainName);
	strcat((char*)statement_str, (const char *)statement_temp);

	hstmt = GetODBCStatementHandle();
	rc = SQLExecDirect(hstmt, (unsigned char*)statement_str, SQL_NTS);
	if(rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) 
	{
		return	FALSE;
	}
	else
	{
		return	TRUE;
	}
}

SLONG	GetRecordFromBankDB(TPOS_DB_BANK *lpBank, CHAR *szMainName)
{
	HSTMT		hstmt;
	SQLRETURN	rc;
	
	InitStatementStr();
	sprintf((char *)statement_str, 
		"SELECT * from pos_bank WHERE MainName='%s'",
		szMainName );
	hstmt = GetODBCStatementHandle();
	rc = SQLExecDirect( hstmt, (unsigned char *)statement_str, SQL_NTS);
	if(rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) 
	{
		goto _error;
	}

	BindBankDBColumn(hstmt, lpBank);
	rc = SQLFetch(hstmt);
	if(rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) 
	{
		goto _error;
	}
	SQLCloseCursor(hstmt);
	return	TRUE;

_error:
	return	FALSE;
}

VOID	BindBankDBColumn(HSTMT hStmt, TPOS_DB_BANK *lpBank)
{
	SDWORD	cb;
	UHINT	i;

	//C1: MainName
	SQLBindCol(hStmt, 1,	SQL_CHAR,		lpBank->MainName,	sizeof(lpBank->MainName),	&cb);

	//C2: Money
	SQLBindCol(hStmt, 2,	SQL_INTEGER,	&lpBank->Money,		sizeof(lpBank->Money),		&cb);

	//C3~38: MAX_CHARACTER_BANK_ITEMS = 36
	for(i=0; i<MAX_CHARACTER_BANK_ITEMS; i++)
	{
		SQLBindCol(hStmt,	3+i,	SQL_INTEGER,	&lpBank->Item[i],	sizeof(lpBank->Item[i]), &cb);
	}
	//C39: 
}

/************************************************************************************************************/
/* HOUSE DB FUNCTIONS                                                                                       */
/************************************************************************************************************/
SLONG	DeleteHouseDBTable(void)
{
	HSTMT	hstmt;
	SQLRETURN	rc;

	InitStatementStr();
	sprintf((char *)statement_str,
		"DROP TABLE IF EXISTS `pos_house`"
		);
	hstmt = GetODBCStatementHandle();
	rc = SQLExecDirect(hstmt, (unsigned char*)statement_str, SQL_NTS);
	if(rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) 
	{
		return	-1;
	}
	return	0;
}


SLONG	CreateHouseDBTable(void)
{
	HSTMT	hstmt;
	SQLRETURN	rc;
	SLONG	i;

	InitStatementStr();
	sprintf((char *)statement_str, 
		"CREATE TABLE `pos_house` ("
		"`ID` int(4) unsigned NOT NULL default '',"
		"`Name` char(32) default '',"
		"`OwnerName` char(32) default '',"
		"`GuildName` char(32) default '',"
		"`CityName` char(32) default '',"
		"`Size` smallint(2) unsigned default '',"
		"`GuildPrice` int(4) unsigned default '',"
		"`PersonalPrice` int(4) unsigned default '',"
		"`BoxSize` smallint(2) unsigned default '',"
		"`BoxCount` smallint(2) unsigned default '',"
		);
	for(i=0; i<MAX_HOUSE_BOX_ITEMS; i++)
	{
		sprintf((char *)statement_temp, "`ItemA%03d` int(4) unsigned default '',", i+1);
		strcat((char *)statement_str, (const char *)statement_temp);
	}
	sprintf((char *)statement_temp, "`MoneyA` int(4) unsigned default '',");
	strcat((char *)statement_str, (const char *)statement_temp);
	for(i=0; i<MAX_HOUSE_BOX_ITEMS; i++)
	{
		sprintf((char *)statement_temp, "`ItemB%03d` int(4) unsigned default '',", i+1);
		strcat((char *)statement_str, (const char *)statement_temp);
	}
	sprintf((char *)statement_temp, "`MoneyB` int(4) unsigned default '',");
	strcat((char *)statement_str, (const char *)statement_temp);

	sprintf((char *)statement_temp, "PRIMARY KEY (`ID`)"
		") TYPE = MyISAM" 
		);
	strcat((char *)statement_str, (const char *)statement_temp);

	hstmt = GetODBCStatementHandle();
	rc = SQLExecDirect(hstmt, (unsigned char*)statement_str, SQL_NTS);
	if(rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) 
	{
		return	-1;
	}
	return	0;
}

SLONG	AppendRecordToHouseDB(TPOS_DB_HOUSE *lpHouse)
{
	HSTMT	hstmt;
	SQLRETURN	rc;
	SLONG	i;

	InitStatementStr();
	sprintf((char *)statement_str, "INSERT INTO pos_house (");

	//== Colume names
	sprintf((char *)statement_temp, 
		"ID,Name,OwnerName,GuildName,CityName,"
		"Size,GuildPrice,PersonalPrice,BoxSize,BoxCount,"
		);
	strcat((char *)statement_str, (const char *)statement_temp);

	for(i=0; i<MAX_HOUSE_BOX_ITEMS; i++)
	{
		sprintf((char *)statement_temp, "ItemA%03d,", i+1);
		strcat((char *)statement_str, (const char *)statement_temp);
	}
	sprintf((char *)statement_temp, "MoneyA,");
	strcat((char *)statement_str, (const char *)statement_temp);

	for(i=0; i<MAX_HOUSE_BOX_ITEMS; i++)
	{
		sprintf((char *)statement_temp, "ItemB%03d,", i+1);
		strcat((char *)statement_str, (const char *)statement_temp);
	}
	sprintf((char *)statement_temp, "`MoneyB` int(4) unsigned default '',");
	strcat((char *)statement_str, (const char *)statement_temp);

	//== Values
	strcat((char *)statement_str, ") VALUES (");

	// Colume values
	sprintf((char *)statement_temp, 
		"%u,'%s','%s','%s','%s',"
		"%d,%u,%u,%d,%d,",
		lpHouse->ID,
		lpHouse->Name,
		lpHouse->OwnerName,
		lpHouse->GuildName,
		lpHouse->CityName,

		lpHouse->Size,
		lpHouse->GuildPrice,
		lpHouse->PersonalPrice,
		lpHouse->BoxSize,
		lpHouse->BoxCount
		);
	strcat((char *)statement_str, (const char *)statement_temp);

	for(i=0; i<MAX_HOUSE_BOX_ITEMS; i++)
	{
		sprintf((char *)statement_temp, "%u,", lpHouse->ItemA[i]);
		strcat((char *)statement_str, (const char *)statement_temp);
	}
	sprintf((char *)statement_temp, "%u,", lpHouse->MoneyA);
	strcat((char *)statement_str, (const char *)statement_temp);

	for(i=0; i<MAX_HOUSE_BOX_ITEMS; i++)
	{
		sprintf((char *)statement_temp, "%u,", lpHouse->ItemB[i]);
		strcat((char *)statement_str, (const char *)statement_temp);
	}
	sprintf((char *)statement_temp, "%u", lpHouse->MoneyB);
	strcat((char *)statement_str, (const char *)statement_temp);


	//Statement string end.
	strcat((char *)statement_str, ")");

	hstmt = GetODBCStatementHandle();
	rc = SQLExecDirect(hstmt, (unsigned char*)statement_str, SQL_NTS);
	if(rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) 
	{
		return	FALSE;
	}
	else
	{
		return	TRUE;
	}
}


SLONG	DeleteRecordFromHouseDBByHouseID(ULONG uID)
{
	HSTMT	hstmt;
	SQLRETURN	rc;

	InitStatementStr();
	sprintf((char *)statement_str, 
		"DELETE FROM pos_house WHERE ID=%u",
		uID);
	hstmt = GetODBCStatementHandle();
	rc = SQLExecDirect(hstmt, (unsigned char*)statement_str, SQL_NTS);
	if(rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) 
	{
		return	FALSE;
	}
	else
	{
		return	TRUE;
	}
}


SLONG	DeleteRecordFromHouseDBByOwnerName(CHAR *szOwnerName)
{
	HSTMT	hstmt;
	SQLRETURN	rc;

	InitStatementStr();
	sprintf((char *)statement_str, 
		"DELETE FROM pos_house WHERE OwnerName=%s",
		szOwnerName);
	hstmt = GetODBCStatementHandle();
	rc = SQLExecDirect(hstmt, (unsigned char*)statement_str, SQL_NTS);
	if(rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) 
	{
		return	FALSE;
	}
	else
	{
		return	TRUE;
	}
}


SLONG	DeleteRecordFromHouseDBByGuildName(CHAR *szGuildName)
{
	HSTMT	hstmt;
	SQLRETURN	rc;

	InitStatementStr();
	sprintf((char *)statement_str, 
		"DELETE FROM pos_house WHERE GuildName=%s",
		szGuildName);
	hstmt = GetODBCStatementHandle();
	rc = SQLExecDirect(hstmt, (unsigned char*)statement_str, SQL_NTS);
	if(rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) 
	{
		return	FALSE;
	}
	else
	{
		return	TRUE;
	}
}

SLONG	DeleteRecordFromHouseDBByCityName(CHAR *szCityName)
{
	HSTMT	hstmt;
	SQLRETURN	rc;

	InitStatementStr();
	sprintf((char *)statement_str, 
		"DELETE FROM pos_house WHERE CityName=%s",
		szCityName);
	hstmt = GetODBCStatementHandle();
	rc = SQLExecDirect(hstmt, (unsigned char*)statement_str, SQL_NTS);
	if(rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) 
	{
		return	FALSE;
	}
	else
	{
		return	TRUE;
	}
}

SLONG	UpdateRecordOfHouseDBByHouseID(TPOS_DB_HOUSE *lpHouse, ULONG uID)
{
	HSTMT	hstmt;
	SQLRETURN	rc;
	SLONG	i;

	InitStatementStr();
	sprintf((char *)statement_str, "UPDATE pos_house SET ");

	//"[Field1 = Value1,...N]"
	sprintf((char *)statement_temp, 
		"Name='%s',OwnerName='%s',GuildName='%s',CityName='%s',"
		"Size=%d,GuildPrice=%u,PersonalPrice=%u,BoxSize=%d,BoxCount=%d,",
		lpHouse->Name, lpHouse->OwnerName, lpHouse->GuildName, lpHouse->CityName,
		lpHouse->Size, lpHouse->GuildPrice, lpHouse->PersonalPrice, lpHouse->BoxSize, lpHouse->BoxCount
		);
	strcat((char *)statement_str, (const char *)statement_temp);

	for(i=0; i<MAX_HOUSE_BOX_ITEMS; i++)
	{
		sprintf((char *)statement_temp, "ItemA%03d=%u,", i+1, lpHouse->ItemA[i]);
		strcat((char *)statement_str, (const char *)statement_temp);
	}
	sprintf((char *)statement_temp, "MoneyA=%u,", lpHouse->MoneyA);
	strcat((char *)statement_str, (const char *)statement_temp);

	for(i=0; i<MAX_HOUSE_BOX_ITEMS; i++)
	{
		sprintf((char *)statement_temp, "ItemB%03d=%u,", i+1, lpHouse->ItemB[i]);
		strcat((char *)statement_str, (const char *)statement_temp);
	}
	sprintf((char *)statement_temp, "MoneyB=%u", lpHouse->MoneyB);
	strcat((char *)statement_str, (const char *)statement_temp);

	//Statement string end.
	sprintf((char *)statement_temp, " WHERE ID=%u", uID);
	strcat((char*)statement_str, (const char *)statement_temp);

	hstmt = GetODBCStatementHandle();
	rc = SQLExecDirect(hstmt, (unsigned char*)statement_str, SQL_NTS);
	if(rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) 
	{
		return	FALSE;
	}
	else
	{
		return	TRUE;
	}
}

SLONG	GetRecordFromHouseDBByHouseID(TPOS_DB_HOUSE *lpHouse, ULONG uID)
{
	HSTMT		hstmt;
	SQLRETURN	rc;
	
	InitStatementStr();
	sprintf((char *)statement_str, "SELECT * from pos_house WHERE ID=%u", uID);
	hstmt = GetODBCStatementHandle();
	rc = SQLExecDirect( hstmt, (unsigned char *)statement_str, SQL_NTS);
	if(rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) 
	{
		goto _error;
	}

	BindHouseDBColumn(hstmt, lpHouse);
	rc = SQLFetch(hstmt);
	if(rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) 
	{
		goto _error;
	}
	SQLCloseCursor(hstmt);
	return	TRUE;

_error:
	return	FALSE;
}

VOID	BindHouseDBColumn(HSTMT hStmt, TPOS_DB_HOUSE *lpHouse)
{
	SDWORD	cb;
	UHINT	i;

	//C1~C10:
	SQLBindCol(hStmt, 1,	SQL_INTEGER,	&lpHouse->ID,				sizeof(lpHouse->ID),				&cb);
	SQLBindCol(hStmt, 2,	SQL_CHAR,		lpHouse->Name,				sizeof(lpHouse->Name),				&cb);
	SQLBindCol(hStmt, 3,	SQL_CHAR,		lpHouse->OwnerName,			sizeof(lpHouse->OwnerName),			&cb);
	SQLBindCol(hStmt, 4,	SQL_CHAR,		lpHouse->GuildName,			sizeof(lpHouse->GuildName),			&cb);
	SQLBindCol(hStmt, 5,	SQL_CHAR,		lpHouse->CityName,			sizeof(lpHouse->CityName),			&cb);
	SQLBindCol(hStmt, 6,	SQL_SMALLINT,	&lpHouse->Size,				sizeof(lpHouse->Size),				&cb);
	SQLBindCol(hStmt, 7,	SQL_INTEGER,	&lpHouse->GuildPrice,		sizeof(lpHouse->GuildPrice),		&cb);
	SQLBindCol(hStmt, 8,	SQL_INTEGER,	&lpHouse->PersonalPrice,	sizeof(lpHouse->PersonalPrice),		&cb);
	SQLBindCol(hStmt, 9,	SQL_SMALLINT,	&lpHouse->BoxSize,			sizeof(lpHouse->BoxSize),			&cb);
	SQLBindCol(hStmt, 10,	SQL_SMALLINT,	&lpHouse->BoxCount,			sizeof(lpHouse->BoxCount),			&cb);

	//C11~154: ItemA[144] (MAX_HOUSE_BOX_ITEMS = 144)
	for(i=0; i<MAX_HOUSE_BOX_ITEMS; i++)
	{
		SQLBindCol(hStmt, 11+i,	SQL_INTEGER,	&lpHouse->ItemA[i],	sizeof(lpHouse->ItemA[i]),	&cb);
	}

	//C155: MoneyA
	SQLBindCol(hStmt, 155,	SQL_INTEGER,	&lpHouse->MoneyA,	sizeof(lpHouse->MoneyA),	&cb);

	//C156~299: ItemB[144] (MAX_HOUSE_BOX_ITEMS = 144)
	for(i=0; i<MAX_HOUSE_BOX_ITEMS; i++)
	{
		SQLBindCol(hStmt, 156+i,	SQL_INTEGER,	&lpHouse->ItemB[i],	sizeof(lpHouse->ItemB[i]),	&cb);
	}

	//C300: MoneyB
	SQLBindCol(hStmt, 300,	SQL_INTEGER,	&lpHouse->MoneyB,	sizeof(lpHouse->MoneyB),	&cb);

	//C301:
}

/************************************************************************************************************/
/* QUEST DB FUNCTIONS                                                                                       */
/************************************************************************************************************/
SLONG	DeleteQuestDBTable(void)
{
	HSTMT	hstmt;
	SQLRETURN	rc;

	InitStatementStr();
	sprintf((char *)statement_str,
		"DROP TABLE IF EXISTS `pos_quest`"
		);
	hstmt = GetODBCStatementHandle();
	rc = SQLExecDirect(hstmt, (unsigned char*)statement_str, SQL_NTS);
	if(rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) 
	{
		return	-1;
	}
	return	0;
}

SLONG	CreateQuestDBTable(void)
{
	HSTMT	hstmt;
	SQLRETURN	rc;

	InitStatementStr();
	sprintf((char *)statement_str, 
		"CREATE TABLE `pos_quest` ("
		"`MainName` char(32) NOT NULL default '',"
		"`QuestIndex` smallint(2) unsigned default '0',"
		"`QuestType` tinyint(1) unsigned default '',"
		"`PublishZone` char(32) default '',"
		"`PublishNpc` char(32) default '',"
		"`TargetZone` char(32) default '',"
		"`TargetNpc` char(32) default '',"
		"`AcceptTime` int(4) unsigned default '',"
		"`Deadline` int(4) unsigned default '',"
		"`PayType` tinyint(1) unsigned default '',"
		"`PayData` int(4) unsigned default '',"
		"`PunishType` tinyint(1) unsigned default '',"
		"`PunishData` int(4) unsigned default '',"
		"`Memo` char(64) default '',"
		"PRIMARY KEY (`MainName`)"
		") TYPE = MyISAM"
		);
	hstmt = GetODBCStatementHandle();
	rc = SQLExecDirect(hstmt, (unsigned char*)statement_str, SQL_NTS);
	if(rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) 
	{
		return	-1;
	}
	return	0;
}

SLONG	AppendRecordToQuestDB(TPOS_DB_QUEST *lpQuest)
{
	HSTMT	hstmt;
	SQLRETURN	rc;

	InitStatementStr();
	sprintf((char *)statement_str, "INSERT INTO pos_quest (");

	//== Colume names
	sprintf((char *)statement_temp, 
		"MainName,QuestIndex,QuestType,PublishZone,PublishNpc,"
		"TargetZone,TargetNpc,AcceptTime,Deadline,PayType,"
		"PayData,PunishType,PunishData,Memo"
		);
	strcat((char *)statement_str, (const char *)statement_temp);

	//== Values
	strcat((char *)statement_str, ") VALUES (");

	// Colume values
	sprintf((char *)statement_temp, 
		"'%s',%u,%u,'%s','%s','%s','%s',%u,%u,%u,%u,%u,%u,'%s'",
		lpQuest->MainName,
		lpQuest->Index,
		lpQuest->Info.QuestType,
		lpQuest->Info.PublishZone,
		lpQuest->Info.PublishNpc,
		lpQuest->Info.TargetZone,
		lpQuest->Info.TargetNpc,
		lpQuest->Info.AcceptTime,
		lpQuest->Info.Deadline,
		lpQuest->Info.PayType,
		lpQuest->Info.PayData,
		lpQuest->Info.PunishType,
		lpQuest->Info.PunishData,
		lpQuest->Info.Memo
		);
	strcat((char *)statement_str, (const char *)statement_temp);

	//Statement string end.
	strcat((char *)statement_str, ")");

	hstmt = GetODBCStatementHandle();
	rc = SQLExecDirect(hstmt, (unsigned char*)statement_str, SQL_NTS);
	if(rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) 
	{
		return	FALSE;
	}
	else
	{
		return	TRUE;
	}
}

SLONG	DeleteRecordFromQuestDBByMainName(CHAR *szMainName)
{
	HSTMT	hstmt;
	SQLRETURN	rc;

	InitStatementStr();
	sprintf((char *)statement_str, 
		"DELETE FROM pos_quest WHERE MainName='%s'",
		szMainName);
	hstmt = GetODBCStatementHandle();
	rc = SQLExecDirect(hstmt, (unsigned char*)statement_str, SQL_NTS);
	if(rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) 
	{
		return	FALSE;
	}
	else
	{
		return	TRUE;
	}
}

SLONG	UpdateRecordOfQuestDBByMainNameAndIndex(TPOS_DB_QUEST *lpQuest)
{
	HSTMT	hstmt;
	SQLRETURN	rc;

	InitStatementStr();
	sprintf((char *)statement_str, "UPDATE pos_quest SET ");
	//"[Field1 = Value1,...N]"

	sprintf((char *)statement_temp, 
		"QuestType=%u,PublishZone='%s',PublishNpc='%s',"
		"TargetZone='%s',TargetNpc='%s',AcceptTime=%u,Deadline=%u,PayType=%u,"
		"PayData=%u,PunishType=%u,PunishData=%u,Memo='%s'",
		lpQuest->Info.QuestType,
		lpQuest->Info.PublishZone,
		lpQuest->Info.PublishNpc,
		lpQuest->Info.TargetZone,
		lpQuest->Info.TargetNpc,
		lpQuest->Info.AcceptTime,
		lpQuest->Info.Deadline,
		lpQuest->Info.PayType,
		lpQuest->Info.PayData,
		lpQuest->Info.PunishType,
		lpQuest->Info.PunishData,
		lpQuest->Info.Memo
		);
	strcat((char*)statement_str, (const char *)statement_temp);

	//Statement string end.
	sprintf((char *)statement_temp, " WHERE MainName='%s' AND QuestIndex=%u",
		lpQuest->MainName, lpQuest->Index);
	strcat((char*)statement_str, (const char *)statement_temp);

	hstmt = GetODBCStatementHandle();
	rc = SQLExecDirect(hstmt, (unsigned char*)statement_str, SQL_NTS);
	if(rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) 
	{
		return	FALSE;
	}
	else
	{
		return	TRUE;
	}
}

SLONG	GetRecordFromQuestDBByMainNameAndIndex(TPOS_DB_QUEST *lpQuest, CHAR *szMainName, SLONG lIndex)
{
	HSTMT		hstmt;
	SQLRETURN	rc;
	
	InitStatementStr();
	sprintf((char *)statement_str, 
		"SELECT * from pos_quest WHERE MainName='%s' AND QuestIndex=%u",
		szMainName, lIndex);
	hstmt = GetODBCStatementHandle();
	rc = SQLExecDirect( hstmt, (unsigned char *)statement_str, SQL_NTS);
	if(rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) 
	{
		goto _error;
	}

	BindQuestDBColumn(hstmt, lpQuest);
	rc = SQLFetch(hstmt);
	if(rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) 
	{
		goto _error;
	}
	SQLCloseCursor(hstmt);
	return	TRUE;

_error:
	return	FALSE;
}

VOID	BindQuestDBColumn(HSTMT hStmt, TPOS_DB_QUEST *lpQuest)
{
	SDWORD	cb;

	SQLBindCol(hStmt, 1,	SQL_CHAR,		lpQuest->MainName,			sizeof(lpQuest->MainName),			&cb);
	SQLBindCol(hStmt, 2,	SQL_SMALLINT,	&lpQuest->Index,			sizeof(lpQuest->Index),				&cb);
	SQLBindCol(hStmt, 3,	SQL_TINYINT,	&lpQuest->Info.QuestType,	sizeof(lpQuest->Info.QuestType),	&cb);
	SQLBindCol(hStmt, 4,	SQL_CHAR,		lpQuest->Info.PublishZone,	sizeof(lpQuest->Info.PublishZone),	&cb);
	SQLBindCol(hStmt, 5,	SQL_CHAR,		lpQuest->Info.PublishNpc,	sizeof(lpQuest->Info.PublishNpc),	&cb);
	SQLBindCol(hStmt, 6,	SQL_CHAR,		lpQuest->Info.TargetZone,	sizeof(lpQuest->Info.TargetZone),	&cb);
	SQLBindCol(hStmt, 7,	SQL_CHAR,		lpQuest->Info.TargetNpc,	sizeof(lpQuest->Info.TargetNpc),	&cb);
	SQLBindCol(hStmt, 8,	SQL_INTEGER,	&lpQuest->Info.AcceptTime,	sizeof(lpQuest->Info.AcceptTime),	&cb);
	SQLBindCol(hStmt, 9,	SQL_INTEGER,	&lpQuest->Info.Deadline,	sizeof(lpQuest->Info.Deadline),		&cb);
	SQLBindCol(hStmt, 10,	SQL_TINYINT,	&lpQuest->Info.PayType,		sizeof(lpQuest->Info.PayType),		&cb);
	SQLBindCol(hStmt, 11,	SQL_INTEGER,	&lpQuest->Info.PayData,		sizeof(lpQuest->Info.PayData),		&cb);
	SQLBindCol(hStmt, 12,	SQL_TINYINT,	&lpQuest->Info.PunishType,	sizeof(lpQuest->Info.PunishType),	&cb);
	SQLBindCol(hStmt, 13,	SQL_INTEGER,	&lpQuest->Info.PunishData,	sizeof(lpQuest->Info.PunishData),	&cb);
	SQLBindCol(hStmt, 14,	SQL_CHAR,		lpQuest->Info.Memo,			sizeof(lpQuest->Info.Memo),			&cb);
}
