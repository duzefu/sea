/*
**	NetGE_ODBC.cpp
**	ODBC functions.
**
**	Jack, 2002.11.30
*/
#include "NetGE_Mainfunc.h"


//DEFINES ///////////////////////////////////////////////////////////////////////////////////////////////////
#define	RS_ODBC_INITIALIZED			0x00000001		// ODBC have been initialized
#define	RS_ODBC_CONNECTED			0x00000002		// ODBC have been connected 


//VARIABLES /////////////////////////////////////////////////////////////////////////////////////////////////
static	SQLHENV     rs_odbc_henv;					// Environment handle
static	SQLHDBC     rs_odbc_hdbc;					// Connection handle
static	SQLHSTMT    rs_odbc_hstmt;					// Statement handle
static	DWORD		rs_odbc_flags = 0;				// ODBC model flags

/************************************************************************************************************/
/* ODBC MAIN FUNCTIONS                                                                                      */
/************************************************************************************************************/
SLONG	InitODBC(void)
{
	SQLRETURN   retcode;

	// Have been initialized.
	if(rs_odbc_flags & RS_ODBC_INITIALIZED)
		return	0;

	// Allocate environment handle
	retcode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &rs_odbc_henv);
	if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO)
		return	-1;
	
	// Set the ODBC version environment attribute
	retcode = SQLSetEnvAttr(rs_odbc_henv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);
	if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO) 
		return	-2;

	// Allocate connection handle
	retcode = SQLAllocHandle(SQL_HANDLE_DBC, rs_odbc_henv, &rs_odbc_hdbc); 
	if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO)
		return	-3;

	// Update odbc flags for initialized.
	rs_odbc_flags |= RS_ODBC_INITIALIZED;
	
	return	0;
}



void	FreeODBC(void)
{
	if(! (rs_odbc_flags & RS_ODBC_INITIALIZED))
		return;

	SQLFreeHandle(SQL_HANDLE_DBC, rs_odbc_hdbc);
	SQLFreeHandle(SQL_HANDLE_ENV, rs_odbc_henv);
}



SLONG	ConnectODBC(char *db, char *account, char *password)
{
	SQLRETURN   retcode;

	// Not initialized, error.
	if(!(rs_odbc_flags & RS_ODBC_INITIALIZED))
		return	-1;

	// Have connected, you should disconnect first.
	if(rs_odbc_flags & RS_ODBC_CONNECTED)
		return	0;

	// Set login timeout to 5 seconds.
	SQLSetConnectAttr(rs_odbc_hdbc, SQL_LOGIN_TIMEOUT, (void*)5, 0);
				
	// Connect to data source
	retcode = SQLConnect(rs_odbc_hdbc, (SQLCHAR*)db, SQL_NTS, (SQLCHAR*)account, SQL_NTS, (SQLCHAR*)password, SQL_NTS);
	if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO)
		return	-1;

	// Allocate statement handle
	retcode = SQLAllocHandle(SQL_HANDLE_STMT, rs_odbc_hdbc, &rs_odbc_hstmt); 
	if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO) 
		return	-2;

	// Update odbc flags for connected.
	rs_odbc_flags |= RS_ODBC_CONNECTED;

	return	0;
		
}


void	DisconnectODBC(void)
{
	// Not connected yet.
	if(! (rs_odbc_flags & RS_ODBC_CONNECTED))
		return;

	SQLFreeHandle(SQL_HANDLE_STMT, rs_odbc_hstmt);
	SQLDisconnect(rs_odbc_hdbc);
}



SQLHSTMT	GetODBCStatementHandle(void)
{
	return	rs_odbc_hstmt;
}


int		MakeMySQLEscapeString(char *strbuf, const char *data, int data_size)
{
	char	*end;
	int		i;

	end = strbuf;
	for(i=0; i<data_size; i++)
	{
		switch(data[i])
		{
		case 0x00:	// An ASCII 0(NUL) character (\0)
			*end++ = 0x5C; 
			*end++ = 0x30; 
			break;
		case 0x0A:	// A newline character (\n)
			*end++ = 0x5C; 
			*end++ = 0x6E; 
			break;
		case 0x0D:	// A carriage return character (\r) 
			*end++ = 0x5C; 
			*end++ = 0x72; 
			break;
		case 0x1A:	// ASCII(26)(Control-Z) (\Z)
			*end++ = 0x5C; 
			*end++ = 0x5A; 
			break;
		case 0x22:	// A double quote character (\") 
			*end++ = 0x5C; 
			*end++ = 0x22; 
			break;
		case 0x27:	// A single quote character (\')
			*end++ = 0x5C; 
			*end++ = 0x27; 
			break;
		case 0x5C:	// A backslash character (\\) 
			*end++ = 0x5C;
			*end++ = 0x5C; 
			break;
		default: 
			*end++ = data[i]; 
			break;
		}
	}
	return	end - strbuf;
}
