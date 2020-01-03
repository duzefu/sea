/*
**	ServerQuest.h 
**	server quest functions header.
**
**	Hawke, 2003.05.13
*/
#ifndef	_SERVERQUEST_H_
#define	_SERVERQUEST_H_

#define		MAX_CITY_TRANSFER_QUEST		20
// ---------------------------------------------------------------------------------
// Struct Define
// ---------------------------------------------------------------------------------

typedef	struct POS_NPC_QUEST
{	
	UHINT	QuestID;			//任務的 ID
	UHINT	IsAccepted;			//該任務是否被接了
	CHAR	TargetZone[32];		//目標地點(區域)
	CHAR	TargetNpc[32];		//目標人
	ULONG	Deadline;			//任務完成的最終期限
	ULONG	TransferItemBaseID;	//傳送物品的 BaseID
	UCHR	PayType;			//完成任務的報酬類別 (QUEST_PAY_$$)
	ULONG	PayData;			//完成任務的報酬數值 (可以是聲望Prestidge, 金錢Money 或者物品ItemBaseID )
	UCHR	PunishType;			//未完成任務的懲罰類別
	ULONG	PunishData;			//未完成任務的懲罰數值
	CHAR	Memo[64];			//任務說明
	UHINT	RequestLevel;		//要求等級
	CHAR	RequestCareer;		//要求職業
	CHAR	RequestCareerLevel;	//要求職稱
	SLONG	RequestPrestige;	//要求聲望
}TPOS_NPC_QUEST;

typedef	struct POS_NPC_QUEST_LIST
{
	SLONG				NpcNo;
	TPOS_NPC_QUEST	    Quest[MAX_CITY_TRANSFER_QUEST];
}TPOS_NPC_QUEST_LIST;

typedef	struct POS_NORMAL_NPC_LIST
{
	ULONG	Count;
	SLONG	NpcNo[MAX_NPC_PER_ZONE];
}TPOS_NORMAL_NPC_LIST;
// ---------------------------------------------------------------------------------
extern	TPOS_NPC_QUEST_LIST		NpcQuestList;
extern	TPOS_NORMAL_NPC_LIST	NormalNpcList;
extern	CRITICAL_SECTION		g_csQuestList;			//任務列表數據臨界區
extern	CRITICAL_SECTION		g_csNormalNpcList;		//閒人 NPC 列表數據臨界區

#define LOCK_QUESTLIST(a)			EnterCriticalSection(&g_csQuestList)
#define UNLOCK_QUESTLIST(a)			LeaveCriticalSection(&g_csQuestList)
#define LOCK_NORMALNPCLIST(a)		EnterCriticalSection(&g_csNormalNpcList)
#define UNLOCK_NORMALNPCLIST(a)		LeaveCriticalSection(&g_csNormalNpcList)
#define	QUEST_ACCEPTED				1
#define	QUEST_FREE					2
// ---------------------------------------------------------------------------------

void	InitQuestCriticalSection(void);
void    FreeQuestCriticalSection(void);
void	InitNPCQuestList();
void	ServerDoSearchNomalNpc();
void	ServerDoClearNPCQuestList();
void	ServerDoMakeNPCQuestList();
SLONG	ServerDoCheckIsAcceptAbleQuest(int quest_index, CHAR career, CHAR career_level, UHINT level, SLONG prestige);
// ---------------------------------------------------------------------------------

#endif