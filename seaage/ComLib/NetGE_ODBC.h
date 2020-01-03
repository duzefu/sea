/*
**	NetGE_ODBC.h
**	ODBC functions header.
**
**	Jack, 2002.11.30
*/
#pragma once
#include <windows.h>
#include <windowsx.h>
#include <sql.h>
#include <sqlext.h>


extern	SLONG		InitODBC(void);
extern	void		FreeODBC(void);
extern	SLONG		ConnectODBC(char *db, char *account, char *password);
extern	void		DisconnectODBC(void);
extern	SQLHSTMT	GetODBCStatementHandle(void);
extern	int			MakeMySQLEscapeString(char *strbuf, const char *data, int data_size);


