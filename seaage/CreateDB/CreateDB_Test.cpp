/*
**	CreateDB_Test.cpp 
**	create database test functions.
**
**	Jack, 2003.1.10
**
**	Jack, 2003.5.9.
**		-- Added ask yes/no when start each test function.
**
**	Jack, 2003.5.12.
**		-- Added quest-db functions.
**
*/
#include "CreateDB_Main.h"



int		wait_key_yn(void);
//
void	test_init_db_account(TPOS_DB_ACCOUNT *lpAccount);
void	test_account_table_functions(void);
//
void	test_init_db_character(TPOS_DB_CHARACTER *lpChar);
void	test_character_table_functions(void);
//
void	test_init_db_qq(TPOS_DB_QQ *lpQQ);
void	test_qq_table_functions(void);
//
void	test_init_qq_message_table(TPOS_DB_QQMSG *lpMsg);
void	test_qq_message_table_functions(void);
//
void	test_init_db_bank(TPOS_DB_BANK *lpBank);
void	test_bank_table_functions(void);
//
void	test_init_db_item(TPOS_DB_ITEM *lpItem);
void	test_item_table_functions(void);
//
void	test_init_db_house(TPOS_DB_HOUSE *lpHouse);
void	test_house_table_functions(void);
//
void	test_init_db_quest(TPOS_DB_QUEST *lpQuest);
void	test_quest_table_functions(void);
/************************************************************************************************************/
/* TEST MISC FUNCTIONS                                                                                      */
/************************************************************************************************************/
int		wait_key_yn(void)
{
	int	pass, key;

	pass = 0;
	while(0 == pass)
	{
		key = getch();
		switch(key)
		{
		case 'y':case 'Y':
			pass = 1;
			key = 'y';
			break;
		case 'n':case 'N':
			pass = 1;
			key = 'n';
			break;
		}
	}
	return	key;
}

void	test_account_table_functions(void)
{
	static	TPOS_DB_ACCOUNT		db_account;
	SLONG	result;

	cprintf("do you want to test account table functions ?(Y/N)");
	if('n' == wait_key_yn())
		return;
	
	printf("-------------------------------------------------------\n");
	printf("TEST ACCOUNT PROCESS :\n");

	printf("press any to append account ...\n");
	getch();
	memset(&db_account, 0, sizeof(db_account));
	test_init_db_account(&db_account);
	result = AppendRecordToAccountDB(&db_account);
	printf("append account %s.\n", result == TRUE ? "ok" : "failed");

	printf("press any to get account by account ...\n");
	getch();
	memset(&db_account, 0, sizeof(db_account));
	result = GetRecordFromAccountDB(&db_account, "TestAccount");
	printf("get account by account %s.\n", result == TRUE ? "ok" : "failed");

	printf("press any to change password of account...\n");
	getch();
	result = ChangePasswordOfAccountDB("TestAccount", "NewPassword");
	printf("change password of account %s.\n", result == TRUE ? "ok" : "failed");

	printf("press any to check password of account...\n");
	getch();
	result = CheckPasswordOfAccountDB("TestAccount", "NewPassword");
	printf("check password of account %s.\n", result == TRUE ? "match" : "not match");

	printf("press any to update account ...\n");
	getch();
	memset(&db_account, 0, sizeof(db_account));
	strcpy((char *)db_account.cId, "TestAccount");
	strcpy((char *)db_account.cPw, "NewPassword");
	result = UpdateRecordOfAccountDB(&db_account);
	printf("update account %s.\n", result == TRUE ? "ok" : "failed");


	printf("press any to delete account ...\n");
	getch();
	result = DeleteRecordFromAccountDB("TestAccount", "NewPassword");
	printf("delete account %s.\n", result == TRUE ? "ok" : "failed");
}

void	test_character_table_functions(void)
{
	static	TPOS_DB_CHARACTER	db_char;
	SLONG	result;

	cprintf("do you want to test character table functions ?(Y/N)");
	if('n' == wait_key_yn())
		return;
	
	printf("-------------------------------------------------------\n");
	printf("TEST CHARACTER PROCESS :\n");

	printf("press any to append character ...\n");
	getch();
	memset(&db_char, 0, sizeof(db_char));
	test_init_db_character(&db_char);
	result = AppendRecordToCharacterDB(&db_char);
	printf("append character %s.\n", result == TRUE ? "ok" : "failed");


	printf("press any to get character by mainname...\n");
	getch();
	memset(&db_char, 0, sizeof(db_char));
	result = GetRecordFromCharacterDBByMainName(&db_char, "TestMainName");
	printf("get character by mainname %s.\n", result == TRUE ? "ok" : "failed");

	printf("press any to get character by account & index ...\n");
	getch();
	memset(&db_char, 0, sizeof(db_char));
	result = GetRecordFromCharacterDBByAccountAndIndex(&db_char, "TestAccount", 1);
	printf("get character by account & index %s.\n", result == TRUE ? "ok" : "failed");

	printf("press any to check mainname of character...\n");
	getch();
	result = CheckMainNameOfCharacterDB("TestMainName");
	printf("check character of mainname %s.\n", result == TRUE ? "exist" : "not exist");

	printf("press any to update character ...\n");
	getch();
	memset(&db_char, 0, sizeof(db_char));
	strcpy((char *)db_char.MainName, "TestMainName");
	result = UpdateRecordOfCharacterDB(&db_char);
	printf("update character %s.\n", result == TRUE ? "ok" : "failed");

	printf("press any to delete character ...\n");
	getch();
	result = DeleteRecordFromCharacterDB("TestAccount", "TestMainName");
	printf("delete character %s.\n", result == TRUE ? "ok" : "failed");

	printf("press any to check mainname of character...\n");
	getch();
	result = CheckMainNameOfCharacterDB("TestMainName");
	printf("check character of mainname %s.\n", result == TRUE ? "exist" : "not exist");
}


void	test_qq_table_functions(void)
{
	static	TPOS_DB_QQ	db_qq;
	static	TPOS_DB_QQ	db_qq_get;
	SLONG	result;

	cprintf("do you want to test qq table functions ?(Y/N)");
	if('n' == wait_key_yn())
		return;
	
	printf("-------------------------------------------------------\n");
	printf("TEST QQ PROCESS :\n");

	printf("press any to append qq ...\n");
	getch();
	memset(&db_qq, 0, sizeof(db_qq));
	test_init_db_qq(&db_qq);
	result = AppendRecordToQQDB(&db_qq);
	printf("append qq %s.\n", result == TRUE ? "ok" : "failed");


	SLONG	i, same_flag;
	for(i=0; i<500; i++)
	{
		printf("press any to get qq by id[times:%d]...\n", i);
		getch();
		memset(&db_qq_get, 0, sizeof(db_qq_get));
		result = GetRecordFromQQDBByID(&db_qq_get, 1001);
		same_flag = memcmp(&db_qq, &db_qq_get, sizeof(db_qq));
		printf("get qq by id %s[times:%d][same:%d].\n", result == TRUE ? "ok" : "failed", i,
			same_flag);
	}

	printf("press any to update qq ...\n");
	getch();
	memset(&db_qq, 0, sizeof(db_qq));
	db_qq.ID = 1001;
	result = UpdateRecordOfQQDB(&db_qq);
	printf("update qq %s.\n", result == TRUE ? "ok" : "failed");

	printf("press any to delete qq ...\n");
	getch();
	result = DeleteRecordFromQQDBByID(1001);
	printf("delete qq %s.\n", result == TRUE ? "ok" : "failed");
}



/************************************************************************************************************/
/* TEST INIT FUNCTIONS                                                                                      */
/************************************************************************************************************/
void	test_init_db_character(TPOS_DB_CHARACTER *lpChar)
{
	SLONG	i;

	memset(lpChar, 0, sizeof(*lpChar));
	strcpy((char *)lpChar->ID, "TestAccount");
	strcpy((char *)lpChar->MainName, "TestMainName");
	strcpy((char *)lpChar->NickName, "TestNickName");
	lpChar->QQID = 1234;
	lpChar->Index = 1;		//該帳號的第幾個角色, 0~3.
	//Style	
	lpChar->Color = 'C';
	lpChar->Eyes = 'E';
	lpChar->Mouth = 'M';
	lpChar->MainNameColor = 1;
	lpChar->NickNameColor = 2;
	lpChar->MessageColor = 3;
	lpChar->TalkBackColor = 4;
	lpChar->Logo = 5000;
	lpChar->LandFileIndex = 15;
	//Position
	strcpy((char *)lpChar->	ZoneName, "ZoneName");
	lpChar->X = 300;
	lpChar->Y = 400;
	lpChar->Z = 0;
	lpChar->Dir = 1;
	lpChar->StopRadius = 20;
	//Speed
	lpChar->Mspeed = 10;
	lpChar->FSpeedX = 1;
	lpChar->FSpeedY = 1;
	lpChar->SailSize = 60;
	lpChar->Turn = 20;
	lpChar->Weight = 100;
	lpChar->DegreeDir = 200;
	//State
	lpChar->BitState = 0x12345678;

	//Str
	lpChar->InitStr = 10;
	lpChar->LevUpStr = 10;
	//Ins
	lpChar->InitIns = 20;
	lpChar->LevUpIns = 20;
	//Wit
	lpChar->InitWit = 30;
	lpChar->LevUpWit = 30;
	//Lucky
	lpChar->InitLucky = 40;
	lpChar->LevUpLucky = 40;
	//Attack
	lpChar->SightRange = 400;
	lpChar->FinalExplodeRate = 50;
	//Defence
	lpChar->DodgeRate = 40;
	lpChar->ParryRate = 60;
	//屬性點數
	lpChar->PropertyPoint = 4;
	//Exp Lev
	lpChar->Exp = 50000;
	lpChar->Level = 60;
	//Hp Mp
	lpChar->Hp = 900;
	lpChar->MaxHp = 999;
	lpChar->HpRes = 1;
	lpChar->Mp = 800;
	lpChar->MaxMp = 888;
	lpChar->MpRes = 2;
	//Skill
	for(i=0; i<36; i++)
	{
		lpChar->SkillNo[i] = (SHINT)i;
		lpChar->SkillLevel[i] = i+1;
	}
	//Equip
	lpChar->EquHead = 1001;
	lpChar->EquNeck = 1002;
	lpChar->EquBody = 1003;
	lpChar->EquWaist = 1004;
	lpChar->EquGlove = 1005;
	lpChar->EquWeapon = 1006;
	lpChar->EquWrist = 1007;
	lpChar->EquFeet = 1008;
	lpChar->EquOtherA = 1009;
	lpChar->EquOtherB = 1010;
	lpChar->EquOtherC = 1011;
	//Body Item
	for(i=0; i<MAX_CHARACTER_BAG_ITEMS; i++)
	{
		lpChar->BagItem[i] = 2000 + i;
	}
	for(i=0; i<MAX_CHARACTER_SASH_ITEMS; i++)
	{
		lpChar->SashItem[i] = 3000 + i;
	}
	for(i=0; i<MAX_CHARACTER_TRANS_ITEMS; i++)
	{
		lpChar->TransItem[i] = 4000 + i;
	}
	lpChar->OnMouseItem = 5001;
	lpChar->TreasureItem = 5002;
	lpChar->Money = 99999999;
	//Society
	lpChar->Sex = 'A';
	lpChar->Country = 'C';
	strcpy((char *)lpChar->Guild, "GuildName");
	strcpy((char *)lpChar->Spouse, "SpouseName");
	lpChar->Career = 'I';
	lpChar->Office = 200;
	strcpy((char *)lpChar->Nobility, "Nobility");
	lpChar->GoodEvil = 911;
	lpChar->Prestige = 100;
	lpChar->PkCount = 99;
	lpChar->PkedCount = 90;
	//Mouse skill and Hot Key
	lpChar->LandLeftSkill = 5;
	lpChar->LandRightSkill = 6;
	for(i=0; i<MAX_CHARACTER_FN_SKILLS; i++)
	{
		lpChar->LandFnSkillNo[i] = (SHINT)(2 + i);
	}
	for(i=0; i<MAX_CHARACTER_FN_SKILLS; i++)
	{
		lpChar->LandFnSkillHand[i] = i%2;
	}
	//
	lpChar->SeaLeftSkill = 7;
	lpChar->SeaRightSkill = 8;
	for(i=0; i<MAX_CHARACTER_FN_SKILLS; i++)
	{
		lpChar->SeaFnSkillNo[i] = (SHINT)(2 + i);
	}
	for(i=0; i<MAX_CHARACTER_FN_SKILLS; i++)
	{
		lpChar->SeaFnSkillHand[i] = i%2;
	}
	strcpy((char *)lpChar->LeaderName, "LeaderName");
	//Doing
	lpChar->DoingKind = 10;

	return;
}


void	test_init_db_account(TPOS_DB_ACCOUNT *lpAccount)
{
	strcpy((char *)lpAccount->cId, "TestAccount");
	strcpy((char *)lpAccount->cPw, "TestPassword");
	strcpy((char *)lpAccount->cName, "TestName");
	lpAccount->Sex = 0;
	strcpy((char *)lpAccount->cBirthday, "19700910");
	strcpy((char *)lpAccount->cCountry, "TestCountry");
	strcpy((char *)lpAccount->cCity, "TestCity");
	strcpy((char *)lpAccount->cAddress, "TestAddress");
	strcpy((char *)lpAccount->cPhone, "TestPhone");
	lpAccount->dwJob = 1;
	lpAccount->dwNetStyle = 2;
	strcpy((char *)lpAccount->cEmail, "TestEmail");
	lpAccount->dwPayType = 3;
	lpAccount->cStatus = 1;
}


void	test_init_db_qq(TPOS_DB_QQ *lpQQ)
{
	SLONG	i;

	lpQQ->ID = 1001;
	lpQQ->Config = 0x1234;
	strcpy((char *)lpQQ->WorldServerName, "WorldServerName");
	strcpy((char *)lpQQ->AccountName, "AccountName");
	strcpy((char *)lpQQ->CharacterName, "CharacterName");
	strcpy((char *)lpQQ->GuildName, "GuildName");
	strcpy((char *)lpQQ->LeaderName, "LeaderName");
	strcpy((char *)lpQQ->NickName, "NickName");
	lpQQ->Country = 'A';
	lpQQ->State = 1;
	lpQQ->Career = 'A';
	lpQQ->Level = 10;
	for(i=0; i<256; i++)
	{
		lpQQ->Friend[i].ID = 2000 + i;
		lpQQ->Friend[i].Relation = 0x12;
	}
	for(i=0; i<128; i++)
	{
		lpQQ->GuildFriend[i].ID = 3000 + i;
		lpQQ->GuildFriend[i].Relation = 0x34;
	}
}


/************************************************************************************************************/
/* test qq message table functions                                                                          */
/************************************************************************************************************/
void	test_init_qq_message_table(TPOS_DB_QQMSG *lpMsg)
{
	// Jack, TODO [5/9/2003]
}

void	test_qq_message_table_functions(void)
{
	// Jack, TODO [5/9/2003]
}
/************************************************************************************************************/
/* test bank functions                                                                                      */
/************************************************************************************************************/
void	test_init_db_bank(TPOS_DB_BANK *lpBank)
{
	// Jack, TODO [5/9/2003]
}

void	test_bank_table_functions(void)
{
	// Jack, TODO [5/9/2003]
}

/************************************************************************************************************/
/* test item functions                                                                                      */
/************************************************************************************************************/
void	test_init_db_item(TPOS_DB_ITEM *lpItem)
{
	lpItem->BaseID = 1500;
	lpItem->Attrib[0] = 11;
	lpItem->Attrib[1] = 22;
	lpItem->Attrib[2] = 33;
	lpItem->Attrib[3] = 44;
	lpItem->Attrib[4] = 55;
	lpItem->Hp = 255;
	lpItem->Status = 0;
}

void	test_item_table_functions(void)
{
	static	TPOS_DB_ITEM	db_item;
	SLONG	result;

	printf("-------------------------------------------------------\n");
	printf("TEST ITEM PROCESS :\n");

	printf("press any to append item ...\n");
	getch();
	memset(&db_item, 0, sizeof(db_item));
	test_init_db_item(&db_item);
	strcpy((char *)db_item.MainName, "TestMainName");
	db_item.Index = 1;
	result = AppendRecordToItemDB(&db_item);
	printf("append item %s.\n", result == TRUE ? "ok" : "failed");

	printf("press any to get item by mainname and index...\n");
	getch();
	memset(&db_item, 0, sizeof(db_item));
	result = GetRecordFromItemDBByMainNameAndIndex(&db_item, "TestMainName", 1);
	printf("get item by mainname and index %s.\n", result == TRUE ? "ok" : "failed");

	printf("press any to update item ...\n");
	getch();
	memset(&db_item, 0, sizeof(db_item));
	strcpy((char *)db_item.MainName, "TestMainName");
	db_item.Index = 1;
	result = UpdateRecordOfItemDBByMainNameAndIndex(&db_item);
	printf("update item %s.\n", result == TRUE ? "ok" : "failed");

	printf("press any to delete item by mainname ...\n");
	getch();
	result = DeleteRecordFromItemDBByMainName("TestMainName");
	printf("delete item %s.\n", result == TRUE ? "ok" : "failed");
}


/************************************************************************************************************/
/* test house functions                                                                                     */
/************************************************************************************************************/
void	test_init_db_house(TPOS_DB_HOUSE *lpHouse)
{
	// Jack, TODO [5/9/2003]
}

void	test_house_table_functions(void)
{
	// Jack, TODO [5/9/2003]
}

/************************************************************************************************************/
/* test quest functions                                                                                     */
/************************************************************************************************************/
void	test_init_db_quest(TPOS_DB_QUEST *lpQuest)
{
	strcpy((char *)lpQuest->MainName, "MainName");
	lpQuest->Index = 1;
	lpQuest->Info.QuestType = 2;
	strcpy((char *)lpQuest->Info.PublishZone, "publish-zone");
	strcpy((char *)lpQuest->Info.PublishNpc, "publish-npc");
	strcpy((char *)lpQuest->Info.TargetZone, "target-zone");
	strcpy((char *)lpQuest->Info.TargetNpc, "target-npc");
	lpQuest->Info.AcceptTime = time(NULL);
	lpQuest->Info.Deadline = lpQuest->Info.AcceptTime + 20000;
	lpQuest->Info.PayType = 3;
	lpQuest->Info.PayData = 3033;
	lpQuest->Info.PunishType = 4;
	lpQuest->Info.PunishData = 4044;
	strcpy((char *)lpQuest->Info.Memo, "memo");
}

void	test_quest_table_functions(void)
{
	static	TPOS_DB_QUEST	db_quest;
	SLONG	result;

	printf("-------------------------------------------------------\n");
	printf("TEST QUEST PROCESS :\n");

	printf("press any to append quest ...\n");
	getch();
	memset(&db_quest, 0, sizeof(db_quest));
	test_init_db_quest(&db_quest);
	strcpy((char *)db_quest.MainName, "TestMainName");
	db_quest.Index = 1;
	result = AppendRecordToQuestDB(&db_quest);
	printf("append quest %s.\n", result == TRUE ? "ok" : "failed");

	printf("press any to get quest by mainname and index...\n");
	getch();
	memset(&db_quest, 0, sizeof(db_quest));
	result = GetRecordFromQuestDBByMainNameAndIndex(&db_quest, "TestMainName", 1);
	printf("get quest by mainname and index %s.\n", result == TRUE ? "ok" : "failed");

	printf("press any to update quest ...\n");
	getch();
	memset(&db_quest, 0, sizeof(db_quest));
	strcpy((char *)db_quest.MainName, "TestMainName");
	db_quest.Index = 1;
	result = UpdateRecordOfQuestDBByMainNameAndIndex(&db_quest);
	printf("update quest %s.\n", result == TRUE ? "ok" : "failed");

	printf("press any to delete quest by mainname ...\n");
	getch();
	result = DeleteRecordFromQuestDBByMainName("TestMainName");
	printf("delete quest %s.\n", result == TRUE ? "ok" : "failed");
}

