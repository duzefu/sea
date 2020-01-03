/*
**	ServerQuest.cpp 
**	server quest functions.
**
**	Hawke, 2003.05.13
*/
#include "ZoneServer_Def.h"

TPOS_NPC_QUEST_LIST		NpcQuestList;
TPOS_NORMAL_NPC_LIST	NormalNpcList;
CRITICAL_SECTION		g_csQuestList;			//任務列表數據臨界區
CRITICAL_SECTION		g_csNormalNpcList;		//閒人 NPC 列表數據臨界區

// -----------------------------------------------------------------------------
void	InitQuestCriticalSection(void)
{
	InitializeCriticalSection(&g_csQuestList);
	InitializeCriticalSection(&g_csNormalNpcList);
}
// -----------------------------------------------------------------------------
void    FreeQuestCriticalSection(void)
{
	DeleteCriticalSection(&g_csQuestList);
	DeleteCriticalSection(&g_csNormalNpcList);
}
// -----------------------------------------------------------------------------
// 找出所有 NPC 類型為閒人的 NPC 並紀錄下來
// -----------------------------------------------------------------------------
void	ServerDoSearchNomalNpc()
{
	int	i, j;

	LOCK_NORMALNPCLIST(0);
	NormalNpcList.Count = 0;	
	for(i = 0;i < MAX_NPC_PER_ZONE; i++)
	{		
		NormalNpcList.NpcNo[i] = -1;			
	}
	
	j = 0;
	for(i = 0;i < MAX_NPC_PER_ZONE; i++)
	{
		LOCK_ZONEMACRO(0);
		if(ZoneMacro[0].NPC[i].dNPCType == NPC_KIND_NPC)
		{
			NormalNpcList.NpcNo[j] = MAX_NPC_PER_ZONE + i;
			j++;
		}
		UNLOCK_ZONEMACRO(0);
	}	
	NormalNpcList.Count = j;
	UNLOCK_NORMALNPCLIST(0);
}
// -----------------------------------------------------------------------------
void	InitNPCQuestList()
{
	LOCK_QUESTLIST(0);
	memset(&NpcQuestList, 0x0, sizeof(TPOS_NPC_QUEST_LIST));	
	UNLOCK_QUESTLIST(0);
}
// -----------------------------------------------------------------------------
void	ServerDoClearNPCQuestList()
{
	int i;

	LOCK_QUESTLIST(0);
	for(i = 0; i < MAX_CITY_TRANSFER_QUEST; i++)
	{
		memset(&NpcQuestList.Quest[i] , 0x0, sizeof(TPOS_NPC_QUEST));
	}	
	UNLOCK_QUESTLIST(0);
}
// -----------------------------------------------------------------------------
void	ServerDoMakeNPCQuestList()
{
	int		i, c;
	time_t	t;
	char	temp_mainname[32];
	SLONG	temp_npc_no, quest_npc_no;	

	ServerDoClearNPCQuestList();
	time(&t);			
	LOCK_QUESTLIST(0);
	quest_npc_no = NpcQuestList.NpcNo;
	UNLOCK_QUESTLIST(0);
	if(quest_npc_no == 0)return;
	for(i = 0; i < MAX_CITY_TRANSFER_QUEST; i++)
	{		
		LOCK_QUESTLIST(0);		
		NpcQuestList.Quest[i].IsAccepted = QUEST_FREE;
		strcpy(NpcQuestList.Quest[i].TargetZone, ZoneName);
		UNLOCK_QUESTLIST(0);
		LOCK_NORMALNPCLIST(0);
		if(NormalNpcList.Count > 1)
		{
G1:			c = system_rand() % NormalNpcList.Count;		
			if(NormalNpcList.NpcNo[c] == quest_npc_no)
			{
				goto G1;
			}
			temp_npc_no = NormalNpcList.NpcNo[c];
		}
		UNLOCK_NORMALNPCLIST(0);		
		LOCK_CHARACTER(0);
		strcpy(temp_mainname, GetCharacterMainName(temp_npc_no));
		UNLOCK_CHARACTER(0);
		LOCK_QUESTLIST(0);
		strcpy(NpcQuestList.Quest[i].TargetNpc, temp_mainname);		
		//NpcQuestList.
		NpcQuestList.Quest[i].Deadline = t + (system_rand() % 10800) + 1200;
		NpcQuestList.Quest[i].PayType = QUEST_PAY_MONEY;
		NpcQuestList.Quest[i].PayData = system_rand() % 100 + 100;
		NpcQuestList.Quest[i].PunishType = QUEST_PAY_PRESTIGE;
		NpcQuestList.Quest[i].PunishData = system_rand() % 100 + 10;		
		c = system_rand() % 7;
		switch(c)
		{
		case 0:
			NpcQuestList.Quest[i].RequestCareer = 'A';
			break;
		case 1:
			NpcQuestList.Quest[i].RequestCareer = 'B';
			break;
		case 2:
			NpcQuestList.Quest[i].RequestCareer = 'C';
			break;
		case 3:
			NpcQuestList.Quest[i].RequestCareer = 'D';
			break;
		case 4:
			NpcQuestList.Quest[i].RequestCareer = 'E';
			break;
		case 5:
			NpcQuestList.Quest[i].RequestCareer = 'F';
			break;
		case 6:
			NpcQuestList.Quest[i].RequestCareer = 'G';
			break;		
		}
		NpcQuestList.Quest[i].RequestCareerLevel = 0;	// 大於等於 0
		NpcQuestList.Quest[i].RequestLevel = 0;			// 大於等於 0
		NpcQuestList.Quest[i].RequestPrestige = 0;		// 大於等於 0	
		UNLOCK_QUESTLIST(0);
	}	
}
// -----------------------------------------------------------------------------
SLONG	ServerDoCheckIsAcceptAbleQuest(int	quest_index, CHAR career, CHAR career_level, UHINT level, SLONG prestige)
{
	SLONG	ret_value;

	ret_value = TRUE;
	LOCK_QUESTLIST(0);
	if(NpcQuestList.Quest[quest_index].RequestCareer != career)
	{
		ret_value = FALSE;
	}
	if(NpcQuestList.Quest[quest_index].RequestCareerLevel < career_level)
	{
		ret_value = FALSE;
	}
	if(NpcQuestList.Quest[quest_index].RequestLevel < level)
	{
		ret_value = FALSE;
	}
	if(NpcQuestList.Quest[quest_index].RequestPrestige < prestige)
	{
		ret_value = FALSE;
	}
	UNLOCK_QUESTLIST(0);
	
	return ret_value;
}
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------