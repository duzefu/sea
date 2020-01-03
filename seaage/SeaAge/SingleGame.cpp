/*
**	SingleGame.cpp 
**	single game functions.
**
**	Jack, 2003.2.19.
*/
#include "MainFun.h"
#include "NetGE_MainFunc.h"
#include "NetGE.h"
#include "NetGE_Event_Def.h"
#include "NetGE_Event_Struct_Def.h"
#include "ClientMain.h"
#include "ErrorMsg.h"
#include "Weather.h"
#include "Npc.h"
#include "SingleGame.h"

/************************************************************************************************************/
/* GLOBALS                                                                                                  */
/************************************************************************************************************/
STARTING_SINGLE_GAME_DATA	*l_staring_single_game_data = NULL;


static	int		init_single_game_for_land(void);

/************************************************************************************************************/
/* FUNCTIONS                                                                                                */
/************************************************************************************************************/
int     init_starting_single_game(void)
{
	l_staring_single_game_data = (STARTING_SINGLE_GAME_DATA *)malloc(sizeof(STARTING_SINGLE_GAME_DATA));
	if(NULL == l_staring_single_game_data)
		return	-1;
	l_staring_single_game_data->wait_counts = 20;

	get_bitmap(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, screen_channel2, screen_buffer);
	init_single_game_for_land();
	g_lIsSingleGame = 1;

	return	0;
}


void    active_starting_single_game(int active)
{
	// do nothing here.
}


void    free_starting_single_game(void)
{
	if(l_staring_single_game_data)
	{
		free(l_staring_single_game_data);
		l_staring_single_game_data = NULL;
	}
}


void    refresh_starting_single_game(void)
{
	if(timer_tick02 > 20)
	{
		l_staring_single_game_data->wait_counts--;
		if(l_staring_single_game_data->wait_counts <= 0)
		{
			set_next_app_state(APPSTATE_INIT_MAIN_GAME);
			change_app_state();
		}
		timer_tick02 = 0;
	}
}


void    redraw_starting_single_game(SLONG sx, SLONG sy, void *vbitmap)
{
	char	info[80];

	put_bitmap(0, 0, screen_channel2, (BMP*)vbitmap);
	sprintf((char *)info, "Loading single game, please wait...%d", l_staring_single_game_data->wait_counts);
    display_error_message((USTR*)info, DISPLAY_MESSAGE_TO_BUFFER, vbitmap);
}


SLONG   handle_starting_single_game(UINT message, WPARAM wParam, LPARAM lParam)
{
    switch(message)
    {
    case WM_KEYDOWN:
		{
			switch( wParam )
			{
			case VK_ESCAPE:
				set_next_app_state(APPSTATE_INIT_LOGIN);
				change_app_state();
				break;
			}
		}
        break;
    }
    return  0;
}


static	int     init_single_game_for_land(void)
{
	USTR	rgb_data[35];
    SLONG   i, index;
	ULONG	part_rgb;

	part_rgb = 0x10203040;

    //(0) set current zone -------------------------------------------------------
    strcpy((char *)g_szPlayerZone, (const char *)"zone0012");
    strcpy((char *)g_szPlayerMap,  (const char *)"map0012");
	g_dwZoneType = CITY_NORMAL;
	g_lPlayerIndex = 0;
	init_zone_weather();

    //(1) clear player and npc.
    LOCK_CHARACTER(0);
	InitAllZoneCharacters();
    clear_all_map_npc();
    UNLOCK_CHARACTER(0);

	//(2) setup player character.
	index = g_lPlayerIndex;
	ClearOneCharacter(index);
    clear_one_game_npc(index);
	//
	//Name
	SetCharacterAccount(index, "MyAccount");
	SetCharacterMainName(index, "MyMainName");
	SetCharacterNickName(index, "MyNickName");
	SetCharacterQQID(index, 1000);
	SetCharacterIndex(index, 0);
	//Style	
	SetCharacterColor(index, 0);
	SetCharacterEyes(index, 1);
	SetCharacterMouth(index, 2);
	SetCharacterMainNameColor(index, 0);
	SetCharacterNickNameColor(index, 0);
	SetCharacterMessageColor(index, 0);
	SetCharacterTalkBackColor(index, 0);
	SetCharacterLogo(index, 0);
	SetCharacterFileIndex(index, 7);	//7 for male sworder, 10 for female sworder.
	for(i=0; i<7; i++)
	{
		SetCharacterPartRGB(index, i, part_rgb);
	}

	//Position
	SetCharacterZoneName(index, "ZoneName");
	SetCharacterPosition(index, 7445, 4815, 0);
	SetCharacterDir(index, NPC_DOWN);
	SetCharacterStopRadius(index, 200);
	//Speed
	SetCharacterMoveSpeed(index, 12);
	SetCharacterShipSpeedX(index, 0);
	SetCharacterShipSpeedY(index, 0);
	SetCharacterShipSailSize(index, 100);
	SetCharacterShipTurn(index, 10);
	SetCharacterShipWeight(index, 10);
	SetCharacterShipDegreeDir(index, 0);
	//State
	SetCharacterBitState(index, 0);
	//Str
	SetCharacterFinalStr(index, 10);
	//Ins
	SetCharacterFinalIns(index, 10);
	//Wit
	SetCharacterFinalWit(index, 10);
	//Lucky
	SetCharacterFinalLucky(index, 20);
	//Attack
	SetCharacterSightRange(index, 100);
	//Property
	SetCharacterPropertyPoint(index, 0);
	//Exp Lev
	SetCharacterExp(index, 50);
	SetCharacterLevel(index, 1);
	//Hp Mp
	SetCharacterHp(index, 200);
	SetCharacterMaxHp(index, 200);
	SetCharacterHpRes(index, 0);
	SetCharacterMp(index, 100);
	SetCharacterMaxMp(index, 100);
	SetCharacterMpRes(index, 0);
	//Skill
	//組隊, 離隊, 交易, 跟隨.
	for(i=0; i<4; i++)
	{
		SetCharacterSkillNo(index, i, i);
		SetCharacterSkillLevel(index, i, (UHINT)i);
	}
	SetCharacterSkillNo(index, i++, MAGIC_NO_WALK);	//行走
	SetCharacterSkillNo(index, i++, MAGIC_NO_MUSE);	//冥想
	SetCharacterSkillNo(index, i++, MAGIC_NO_ESCRIME);	//劍術
	SetCharacterSkillNo(index, i++, MAGIC_NO_SEQUENTIAL_ESCRIME);	//連擊
	SetCharacterSkillNo(index, i++, MAGIC_NO_STRONG);	//強壯
	SetCharacterSkillNo(index, i++, MAGIC_NO_DEFENCE);	//格擋
	SetCharacterSkillNo(index, i++, MAGIC_NO_CLASH);	//衝撞
	SetCharacterSkillNo(index, i++, MAGIC_NO_CLASH);	//劍氣
	SetCharacterSkillNo(index, i++, MAGIC_NO_KNOCK_TO_DIZZY);	//敲暈
	SetCharacterSkillNo(index, i++, MAGIC_NO_FATAL_ESCRIME);    //必殺劍

	/*
	SetCharacterEquipHead(index, &info.EquHead);
	SetCharacterEquipNeck(index, &info.EquNeck);
	SetCharacterEquipBody(index, &info.EquBody);
	SetCharacterEquipWaist(index, &info.EquWaist);
	SetCharacterEquipGlove(index, &info.EquGlove);
	SetCharacterEquipWeapon(index, &info.EquWeapon);
	SetCharacterEquipWrist(index, &info.EquWrist);
	SetCharacterEquipFeet(index, &info.EquFeet);
	SetCharacterEquipOtherA(index, &info.EquOtherA);
	SetCharacterEquipOtherB(index, &info.EquOtherB);
	SetCharacterEquipOtherC(index, &info.EquOtherC);
	for(i=0; i<MAX_CHARACTER_BAG_ITEMS; i++)
	{
		SetCharacterBagItem(index, i, &info.BagItem[i]);
	}
	for(i=0; i<MAX_CHARACTER_SASH_ITEMS; i++)
	{
		SetCharacterSashItem(index, i, &info.SashItem[i]);
	}
	for(i=0; i<MAX_CHARACTER_TRANS_ITEMS; i++)
	{
		SetCharacterTransItem(index, i, &info.TransItem[i]);
	}

	// Jack, temp use onmouseitem, later will be none for server have been drop it to the ground. [1/17/2003]
	SetCharacterOnMouseItem(index, &info.OnMouseItem);
	SetCharacterTreasureItem(index, &info.TreasureItem);
	SetCharacterBodyMoney(index, info.Money);
	*/
	//Society
	SetCharacterSex(index, SEX_MALE);
	SetCharacterCountry(index, COUNTRY_CHINA);
	SetCharacterGuildName(index, "MyGuildName");
	SetCharacterSpouseName(index, "MySpouseName");
	SetCharacterCareer(index, CAREER_SWORDER);
	SetCharacterOffice(index, 0);
	SetCharacterNobilityName(index, "Nobility");
	SetCharacterGoodEvil(index, 10);
	SetCharacterPrestige(index, 20);
	SetCharacterPkCount(index, 0);
	SetCharacterPkedCount(index, 0);

	//Mouse skill and Hot Key
	/*
	SetCharacterLandLeftSkill(index, info.LandLeftSkill);
	SetCharacterLandRightSkill(index, info.LandRightSkill);
	for(i=0; i<MAX_CHARACTER_FN_SKILLS; i++)
	{
		SetCharacterLandFnSkillNo(index, i, info.LandFnSkillNo[i]);
		SetCharacterLandFnSkillHand(index, i, info.LandFnSkillHand[i]);
	}
	//
	SetCharacterSeaLeftSkill(index, info.SeaLeftSkill);
	SetCharacterSeaRightSkill(index, info.SeaRightSkill);
	for(i=0; i<MAX_CHARACTER_FN_SKILLS; i++)
	{
		SetCharacterSeaFnSkillNo(index, i, info.SeaFnSkillNo[i]);
		SetCharacterSeaFnSkillHand(index, i, info.SeaFnSkillHand[i]);
	}
	*/
	//Datas
	SetCharacterFinalAtt(index, 20);
	SetCharacterFinalDefence(index, 30);
	//Doing
	SetCharacterDoingKindStep(index, DOING_KIND_IDLE, 0);

	switch(g_dwZoneType)
	{
	case SAIL_NORMAL:
	case SAIL_NEWBIE:
	case SAIL_PK:
	case SAIL_FINDGOLD:
	case SAIL_BIRTH:
		SetCharacterOnTheSea(index, true);
		SetCharacterShipSpeedX(index, 0);
		SetCharacterShipSpeedY(index, 0);
		break;
	case CITY_NORMAL:
	case CITY_NEWBIE:
	case CITY_PK:
	case CITY_FINDGOLD:
	case CITY_BIRTH:
	case FIELD_NORMAL:
	case FIELD_NEWBIE:
	case FIELD_PK:
	case FIELD_FINDGOLD:
	case FIELD_BIRTH:
	default:
		SetCharacterOnTheSea(index, false);
		break;
	}

	for(i=0; i<7; i++)
	{
		rgb_data[i*5 + 0] = ((ARGB_DATA*)&part_rgb)->a;
		rgb_data[i*5 + 1] = ((ARGB_DATA*)&part_rgb)->r;
		rgb_data[i*5 + 2] = ((ARGB_DATA*)&part_rgb)->g;
		rgb_data[i*5 + 3] = ((ARGB_DATA*)&part_rgb)->b;
		rgb_data[i*5 + 4] = 0;
	}
	set_npc_rgb_scroll(index, (USTR*)rgb_data);

    active_map_npc(index);
    LOCK_CHARACTER(index);

    return  0;
}


