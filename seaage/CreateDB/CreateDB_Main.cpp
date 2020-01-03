/*
**	CreateDB_Main.cpp 
**	create database functions.
**
**	Jack, 2003.1.8
**		--- Created for POS, Version1.00.
**
**	Jack, 2003.1.11.
**		--- Modified for insert 2 columns (`FinalAttack`, `FinalDefence`) to character table
**			before column `DoingKind`.	
**		--- Update Version to 1.01.
**
**	Jack, 2003.1.15.
**		--- Added create item table functions.
**		--- Update Version to 1.1.
**
**	Jack, 2003.1.16.
**		--- Added tablesname parameters control.
**      --- Update Version to 1.2.
**
**	Jack, 2003.1.24.
**		--- After ComLib changing, rebuild.
**		--- Added test controls.
**		--- Update Version to 1.3.
**
**	Jack, 2003.2.19.
**		--- After ComLib changing, rebuild.
**		--- Update Version to 1.4.
**
**	Jack, 2003.3.14.
**		--- Added bank db functions.
**		--- Added house db functions.
**		--- Update Version to 1.41.
**		
**	Jack, 2003.4.8.
**		--- Added MainName, Index to ItemDB, rebuild.
**		--- Update Version to 1.42.
**
**	Jack, 2003.4.8.
**		--- Added test item table functions.
**		--- Update Version to 1.43.
**
**	Jack, 2003.5.9.
**		--- Recompile after added POS_DB_CHARACTER::LeaderName.
**		--- Update Version to 1.44.
**
**	Jack, 2003.5.12.
**		--- Added character quest db related support, rebuild.
**		--- Update Version to 1.5.
**
**	Jack, 2003.5.14.
**		--- Rebuild after add POS_DB_CHARACTER::CareerLevel.
**		--- Update Version to 1.51.
**
**	Jack, 2003.5.15.
**		--- Rebuild after add POS_DB_ACCOUNT::RestPoints/LimitDate/RestMinutes.
**		--- Update Version to 1.52.
**
*/
#include "CreateDB_Main.h"


#define	VERSION_INFO	"V1.52."
#define	MAX_DB_TABLES	32

extern	SLONG	DeleteAccountDBTable(void);
extern	SLONG	CreateAccountDBTable(void);
extern	SLONG	DeleteCharacterDBTable(void);
extern	SLONG	CreateCharacterDBTable(void);
extern	SLONG	DeleteItemDBTable(void);
extern	SLONG	CreateItemDBTable(void);
extern	SLONG	DeleteQQDBTable(void);
extern	SLONG	CreateQQDBTable(void);
extern	SLONG	DeleteQQMsgDBTable(void);
extern	SLONG	CreateQQMsgDBTable(void);
extern	SLONG	DeleteBankDBTable(void);
extern	SLONG	CreateBankDBTable(void);
extern	SLONG	DeleteHouseDBTable(void);
extern	SLONG	CreateHouseDBTable(void);
extern	SLONG	DeleteQuestDBTable(void);
extern	SLONG	CreateQuestDBTable(void);



struct  command_parameters_struct
{
	SLONG	create_account;
	SLONG	create_character;
	SLONG	create_bank;
	SLONG	create_house;
	SLONG	create_qq;
	SLONG	create_qq_message;
	SLONG	create_item;
	SLONG	create_quest;
	//
	SLONG	test_flag;
} command_parameters;



// These functions for use RaysSDK.
int gameMain(void) {return 0;}
int gameInit(void){return 0;}
int gameSet(void){return 0;}
void gameExit(void){return;}

//
// Usage:
//
//	CREATEDB DataSource UserName Password TableName
//  
//
char	data_source[80];
char	username[80];
char	password[80];

SLONG	create_table_counts;
SLONG	delete_table_counts;

void	init_command_parameters(void);
void	show_createdb_usage(void);
void	init_create_db_count(void);
void	show_create_db_count(void);
SLONG	connect_pos_datasource(void);
void	disconnect_pos_datasource(void);
SLONG	create_pos_account_table(void);
SLONG	create_pos_character_table(void);
SLONG	create_pos_item_table(void);
SLONG	create_pos_house_table(void);
SLONG	create_pos_qq_table(void);
SLONG	create_pos_qq_message_table(void);
SLONG	create_pos_bank_table(void);
SLONG	create_pos_quest_table(void);
//

int	main(int argc, char *argv[])
{
	int	i, with_test;

	if(argc <= 4)
	{
		show_createdb_usage();
		return	0;
	}
	init_create_db_count();
	strcpy((char *)data_source, (const char *)argv[1]);
	strcpy((char *)username, (const char *)argv[2]);
	strcpy((char *)password, (const char *)argv[3]);

	init_command_parameters();
	for(i=4; i<argc; i++)
	{
		if(0 == strcmpi((const char *)argv[i], "all"))
		{
			command_parameters.create_account = 1;
			command_parameters.create_character = 1;
			command_parameters.create_bank = 1;
			command_parameters.create_house = 1;
			command_parameters.create_qq = 1;
			command_parameters.create_qq_message = 1;
			command_parameters.create_item = 1;
			command_parameters.create_quest = 1;
		}
		else if(0 == strcmpi((const char *)argv[i], "account"))
		{
			command_parameters.create_account = 1;
		}
		else if(0 == strcmpi((const char *)argv[i], "character"))
		{
			command_parameters.create_character = 1;
		}
		else if(0 == strcmpi((const char *)argv[i], "bank"))
		{
			command_parameters.create_bank = 1;
		}
		else if(0 == strcmpi((const char *)argv[i], "house"))
		{
			command_parameters.create_house = 1;
		}
		else if(0 == strcmpi((const char *)argv[i], "qq"))
		{
			command_parameters.create_qq = 1;
		}
		else if(0 == strcmpi((const char *)argv[i], "qqmessage"))
		{
			command_parameters.create_qq_message = 1;
		}
		else if(0 == strcmpi((const char *)argv[i], "item"))
		{
			command_parameters.create_item = 1;
		}
		else if(0 == strcmpi((const char *)argv[i], "quest"))
		{
			command_parameters.create_quest = 1;
		}
		else if(0 == strcmpi((const char*)argv[i], "[test]"))
		{
			command_parameters.test_flag = 1;
		}
	}

	if( 0 != connect_pos_datasource())
	{
		printf("connect datasource error !\n");
		return	-1;
	}
	printf("\n");

	with_test = command_parameters.test_flag;
	printf("%s\n", with_test ? "with test.": "no test.");

	if(command_parameters.create_account)
	{
		create_pos_account_table();
		if(with_test)
		{
			test_account_table_functions();
		}
	}
	if(command_parameters.create_character)
	{
		create_pos_character_table();
		if(with_test)
		{
			test_character_table_functions();
		}
	}
	if(command_parameters.create_bank)
	{
		create_pos_bank_table();
		if(with_test)
		{
			test_bank_table_functions();
		}
	}
	if(command_parameters.create_house)
	{
		create_pos_house_table();
		if(with_test)
		{
			test_house_table_functions();
		}
	}
	if(command_parameters.create_item)
	{
		create_pos_item_table();
		if(with_test)
		{
			test_item_table_functions();
		}
	}
	if(command_parameters.create_qq)
	{
		create_pos_qq_table();
		if(with_test)
		{
			test_qq_table_functions();
		}
	}
	if(command_parameters.create_qq_message)
	{
		create_pos_qq_message_table();
		if(with_test)
		{
			test_qq_message_table_functions();
		}
	}
	if(command_parameters.create_quest)
	{
		create_pos_quest_table();
		if(with_test)
		{
			test_quest_table_functions();
		}
	}


	show_create_db_count();

	disconnect_pos_datasource();


	return	0;
}

void	init_command_parameters(void)
{
	memset(&command_parameters, 0, sizeof(command_parameters));
}

void	show_createdb_usage(void)
{
	char * usage = 
	{
		"\n"
		"Create POS Database Tool, "  VERSION_INFO	"\n"
		"Copyright(C) 2003, Rays Multimedia Co. Ltd.\n"
		"Created by Jack, Build ( " __DATE__ "," __TIME__ " )\n"
		"All rights reserved.\n"
		"\n"
		"Usage:\n"
		"    CREATEDB DataSource UserName Password TablesName...\n"
		"\n"
		"    DataSource         Your data source name.\n"
		"    UserName           The username of access data source.\n"
		"    Password           Password associated with the username.\n"
		"    TablesName         The table name which you want to create:\n"
		"        account            Account table\n"
		"        character          Character table\n"
		"        item               Item table\n"
        "        bank               Bank table\n"
        "        house              House table\n"
        "        qq                 QQ table\n"
        "        qqmessage          QQ message table\n"
        "        quest              Quest table\n"
		"        all                All tables\n"
		"        [test]             After create table(s), execute test functions\n"
        "\n"
        "\n"
	};
	printf(usage);
}


SLONG	connect_pos_datasource(void)
{
	SLONG	result;

	result = InitODBC();
	if(0 != result)
	{
		printf("init odbc failed.\n");
		return	-1;
	}

	result = ConnectODBC(data_source, username, password);
	if(0 != result)
	{
		printf("connect odbc error\n");
		return	-2;
	}

	return	0;
}


void	disconnect_pos_datasource(void)
{
	DisconnectODBC();
	FreeODBC();
}

void	init_create_db_count(void)
{
	create_table_counts = 0;
	delete_table_counts = 0;
}


void	show_create_db_count(void)
{
	printf("-------------------------------------------------------\n");
	printf("PROCESS RESULT:\n");
	printf("      deleted tables : %d\n", delete_table_counts);
	printf("      created tables : %d\n", create_table_counts);
	printf("\n\n");
}


SLONG	create_pos_account_table(void)
{
	printf("ACCOUNT TABLE PROCESS:\n");

	if(0 != DeleteAccountDBTable())
	{
		printf("    delete exist account table error.\n");
	}
	else
	{
		printf("    delete exist account table ok.\n");
		delete_table_counts ++;
	}


	if(0 != CreateAccountDBTable())
	{
		printf("    create new account table failed !\n");
	}
	else
	{
		printf("    create new account table ok.\n");
		create_table_counts ++;
	}
	//printf("\n");

	return	0;
}


SLONG	create_pos_character_table(void)
{
	printf("CHARACTER TABLE PROCESS:\n");

	if(0 != DeleteCharacterDBTable())
	{
		printf("    delete exist character table error.\n");
	}
	else
	{
		printf("    delete exist character table ok.\n");
		delete_table_counts ++;
	}


	if(0 != CreateCharacterDBTable())
	{
		printf("    create new character table failed !\n");
	}
	else
	{
		printf("    create new character table ok.\n");
		create_table_counts ++;
	}
	//printf("\n");

	return	0;
}



SLONG	create_pos_house_table(void)
{
	printf("HOUSE TABLE PROCESS:\n");

	if(0 != DeleteHouseDBTable())
	{
		printf("    delete exist house table error.\n");
	}
	else
	{
		printf("    delete exist house table ok.\n");
		delete_table_counts ++;
	}


	if(0 != CreateHouseDBTable())
	{
		printf("    create new house table failed !\n");
	}
	else
	{
		printf("    create new house table ok.\n");
		create_table_counts ++;
	}
	//printf("\n");

	return	0;
}


SLONG	create_pos_qq_table(void)
{
	printf("QQ TABLE PROCESS:\n");

	if(0 != DeleteQQDBTable())
	{
		printf("    delete exist qq table error.\n");
	}
	else
	{
		printf("    delete exist qq table ok.\n");
		delete_table_counts ++;
	}


	if(0 != CreateQQDBTable())
	{
		printf("    create new qq table failed !\n");
	}
	else
	{
		printf("    create new qq table ok.\n");
		create_table_counts ++;
	}
	//printf("\n");

	return	0;
}


SLONG	create_pos_qq_message_table(void)
{
	printf("QQ MSG TABLE PROCESS:\n");

	if(0 != DeleteQQMsgDBTable())
	{
		printf("    delete exist qq msg table error.\n");
	}
	else
	{
		printf("    delete exist qq msg table ok.\n");
		delete_table_counts ++;
	}

	if(0 != CreateQQMsgDBTable())
	{
		printf("    create new qq msg table failed !\n");
	}
	else
	{
		printf("    create new qq msg table ok.\n");
		create_table_counts ++;
	}
	//printf("\n");

	return	0;
}


SLONG	create_pos_item_table(void)
{
	printf("ITEM TABLE PROCESS:\n");

	if(0 != DeleteItemDBTable())
	{
		printf("    delete exist item table error.\n");
	}
	else
	{
		printf("    delete exist item table ok.\n");
		delete_table_counts ++;
	}

	if(0 != CreateItemDBTable())
	{
		printf("    create new item table failed !\n");
	}
	else
	{
		printf("    create new item table ok.\n");
		create_table_counts ++;
	}
	//printf("\n");

	return	0;
}


SLONG	create_pos_bank_table(void)
{
	printf("BANK TABLE PROCESS:\n");

	if(0 != DeleteBankDBTable())
	{
		printf("    delete exist bank table error.\n");
	}
	else
	{
		printf("    delete exist bank table ok.\n");
		delete_table_counts ++;
	}

	if(0 != CreateBankDBTable())
	{
		printf("    create new bank table failed !\n");
	}
	else
	{
		printf("    create new bank table ok.\n");
		create_table_counts ++;
	}
	//printf("\n");

	return	0;
}


SLONG	create_pos_quest_table(void)
{
	printf("QUEST TABLE PROCESS:\n");

	if(0 != DeleteQuestDBTable())
	{
		printf("    delete exist quest table error.\n");
	}
	else
	{
		printf("    delete exist quest table ok.\n");
		delete_table_counts ++;
	}

	if(0 != CreateQuestDBTable())
	{
		printf("    create new quest table failed !\n");
	}
	else
	{
		printf("    create new quest table ok.\n");
		create_table_counts ++;
	}
	//printf("\n");

	return	0;
}

