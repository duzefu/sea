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
	UHINT	QuestID;			//���Ȫ� ID
	UHINT	IsAccepted;			//�ӥ��ȬO�_�Q���F
	CHAR	TargetZone[32];		//�ؼЦa�I(�ϰ�)
	CHAR	TargetNpc[32];		//�ؼФH
	ULONG	Deadline;			//���ȧ������̲״���
	ULONG	TransferItemBaseID;	//�ǰe���~�� BaseID
	UCHR	PayType;			//�������Ȫ����S���O (QUEST_PAY_$$)
	ULONG	PayData;			//�������Ȫ����S�ƭ� (�i�H�O�n��Prestidge, ����Money �Ϊ̪��~ItemBaseID )
	UCHR	PunishType;			//���������Ȫ��g�@���O
	ULONG	PunishData;			//���������Ȫ��g�@�ƭ�
	CHAR	Memo[64];			//���Ȼ���
	UHINT	RequestLevel;		//�n�D����
	CHAR	RequestCareer;		//�n�D¾�~
	CHAR	RequestCareerLevel;	//�n�D¾��
	SLONG	RequestPrestige;	//�n�D�n��
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
extern	CRITICAL_SECTION		g_csQuestList;			//���ȦC��ƾ��{�ɰ�
extern	CRITICAL_SECTION		g_csNormalNpcList;		//���H NPC �C��ƾ��{�ɰ�

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