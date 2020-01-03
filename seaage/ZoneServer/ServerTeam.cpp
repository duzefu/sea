/*
**	ServerTeam.cpp 
**	server team functions.
**
**	Hawke, 2003.05.06
*/
#include "ZoneServer_Def.h"
// -----------------------------------------------------------------------------
SLONG	ServerCheckTeamIsFull(SLONG	leader_npc_no)
{
	SLONG	ret_value;
	int		i;

	ret_value = TRUE;

	LOCK_CHARACTER(0);
	for(i = 1; i < MAX_CHARACTER_TEAM_MEMBERS; i++)
	{
		if(strcmp(GetCharacterTeamMemberMainName(leader_npc_no, i), "") == 0)
		{
			ret_value = FALSE;
			break;
		}
	}		
	UNLOCK_CHARACTER(0);

	return	ret_value;
}
// -----------------------------------------------------------------------------
SLONG	ServerCheckIsInTeam(SLONG npc_no)
{
	SLONG	ret_value;	

	ret_value = FALSE;

	LOCK_CHARACTER(0);
	if(strcmp(GetCharacterTeamMemberMainName(npc_no, 0), "") != 0)ret_value = TRUE;
	UNLOCK_CHARACTER(0);

	return ret_value;
}
// -----------------------------------------------------------------------------
SLONG	FindUseableTeamInfo(SLONG npc_no)
{
	SLONG	ret_value;
	int		i;
	char	temp_mainname[32];

	ret_value = -1;	
	for(i = 0; i < MAX_CHARACTER_TEAM_MEMBERS; i++)
	{
		LOCK_CHARACTER(0);
		strcpy(temp_mainname, GetCharacterTeamMemberMainName(npc_no, i));
		UNLOCK_CHARACTER(0);
		if(strcmp(temp_mainname, "") == 0)
		{
			return i;
		}
	}	

	return ret_value;
}
// -----------------------------------------------------------------------------
SLONG	ServerCheckTeamMemberNumber(SLONG leader_npc_no)
{
	SLONG	ret_value = 0;
	int		i;

	LOCK_CHARACTER(0);
	for(i = 0; i< MAX_CHARACTER_TEAM_MEMBERS; i++)
	{
		if(strcmp(GetCharacterTeamMemberMainName(leader_npc_no, i), "") != 0)
		{
			ret_value++;
		}
	}
	UNLOCK_CHARACTER(0);

	return ret_value;
}
// -----------------------------------------------------------------------------
SLONG	ServerCheckSomeoneIsInTeam(SLONG leader_npc_no, char *member_mainname)
{
	SLONG	ret_value;
	int		i;

	ret_value = FALSE;

	LOCK_CHARACTER(0);
	for(i = 1; i< MAX_CHARACTER_TEAM_MEMBERS; i++)
	{
		if(strcmp(GetCharacterTeamMemberMainName(leader_npc_no, i), member_mainname) == 0)
		{
			ret_value = TRUE;
			break;
		}
	}
	UNLOCK_CHARACTER(0);

	return ret_value;
}
// -----------------------------------------------------------------------------
SLONG	FindSomeoneInTeam(SLONG leader_npc_no, char *member_mainname)
{
	SLONG	ret_value = -1;
	int		i;	
	char	temp_mainname[32];

	for(i = 0;i < MAX_CHARACTER_TEAM_MEMBERS; i++)
	{		
		LOCK_CHARACTER(0);
		strcpy(temp_mainname, GetCharacterTeamMemberMainName(leader_npc_no, i));
		UNLOCK_CHARACTER(0);
		if(strcmp(member_mainname, temp_mainname) == 0)
		{			
			return i;
		}
	}

	return ret_value;
}
// -----------------------------------------------------------------------------
void	ServerDoAddTeamMember(SLONG npc_no, SLONG target_npc_no, SLONG index)
{
	LOCK_CHARACTER(0);				
	SetCharacterTeamMemberMainName(npc_no, index, GetCharacterMainName(target_npc_no));
	SetCharacterTeamMemberHp(npc_no, index, (UHINT)GetCharacterHp(target_npc_no));
	SetCharacterTeamMemberMaxHp(npc_no, index, (UHINT)GetCharacterMaxHp(target_npc_no));
	SetCharacterTeamMemberEyes(npc_no, index, GetCharacterEyes(target_npc_no));
	SetCharacterTeamMemberMouth(npc_no, index, GetCharacterMouth(target_npc_no));			
	SetCharacterTeamMemberLevel(npc_no, index, (UHINT)GetCharacterLevel(target_npc_no));
	SetCharacterTeamMemberCareer(npc_no, index, GetCharacterCareer(target_npc_no));
	SetCharacterTeamMemberSex(npc_no, index, GetCharacterSex(target_npc_no));			
	SetCharacterTeamMemberZoneName(npc_no, index, GetCharacterZoneName(target_npc_no));
	UNLOCK_CHARACTER(0);			
}
// -----------------------------------------------------------------------------
void	ServerDoDeleteTeamMember(SLONG npc_no, SLONG index)
{
	LOCK_CHARACTER(0);				
	SetCharacterTeamMemberMainName(npc_no, index, "");
	SetCharacterTeamMemberHp(npc_no, index, 0);
	SetCharacterTeamMemberMaxHp(npc_no, index, 0);
	SetCharacterTeamMemberEyes(npc_no, index, 0);
	SetCharacterTeamMemberMouth(npc_no, index, 0);			
	SetCharacterTeamMemberLevel(npc_no, index, 0);
	SetCharacterTeamMemberCareer(npc_no, index, 0);
	SetCharacterTeamMemberSex(npc_no, index, 0);			
	SetCharacterTeamMemberZoneName(npc_no, index, "");
	UNLOCK_CHARACTER(0);
}
// -----------------------------------------------------------------------------
void	ServerDoClearTeamInfo(SLONG npc_no)
{
	int	i;

	LOCK_CHARACTER(0);
	for(i = 0; i < MAX_CHARACTER_TEAM_MEMBERS; i++)
	{
		SetCharacterTeamMemberMainName(npc_no, i, "");
		SetCharacterTeamMemberHp(npc_no, i, 0);
		SetCharacterTeamMemberMaxHp(npc_no, i, 0);
		SetCharacterTeamMemberEyes(npc_no, i, 0);
		SetCharacterTeamMemberMouth(npc_no, i, 0);			
		SetCharacterTeamMemberLevel(npc_no, i, 0);
		SetCharacterTeamMemberCareer(npc_no, i, 0);
		SetCharacterTeamMemberSex(npc_no, i, 0);			
		SetCharacterTeamMemberZoneName(npc_no, i, "");
	}
	UNLOCK_CHARACTER(0);
}
// -----------------------------------------------------------------------------
void	ServerDoCopyTeamInfo(SLONG src_npc_no, SLONG tag_npc_no)
{
	int	i;

	LOCK_CHARACTER(0);
	for(i = 0; i < MAX_CHARACTER_TEAM_MEMBERS; i++)
	{
		SetCharacterTeamMemberMainName(tag_npc_no, i, GetCharacterTeamMemberMainName(src_npc_no, i));
		SetCharacterTeamMemberHp(tag_npc_no, i, GetCharacterTeamMemberHp(src_npc_no, i));
		SetCharacterTeamMemberMaxHp(tag_npc_no, i, GetCharacterTeamMemberMaxHp(src_npc_no, i));
		SetCharacterTeamMemberEyes(tag_npc_no, i, GetCharacterTeamMemberEyes(src_npc_no, i));
		SetCharacterTeamMemberMouth(tag_npc_no, i, GetCharacterTeamMemberMouth(src_npc_no, i));
		SetCharacterTeamMemberLevel(tag_npc_no, i, GetCharacterTeamMemberLevel(src_npc_no, i));
		SetCharacterTeamMemberCareer(tag_npc_no, i, GetCharacterTeamMemberCareer(src_npc_no, i));
		SetCharacterTeamMemberSex(tag_npc_no, i, GetCharacterTeamMemberSex(src_npc_no, i));
		SetCharacterTeamMemberZoneName(tag_npc_no, i, GetCharacterTeamMemberZoneName(src_npc_no, i));
	}	
	UNLOCK_CHARACTER(0);
}
// -----------------------------------------------------------------------------
void	ServerDoSendTeamFull(TPOS_CN *cn, SLONG leader_npc_no)
{
	TPOS_EVENT_NOTIFYJOINTEAMFULL	EventNotifyJoinTeamFull;
	TPOS_PACKET						send_packet;

	send_packet.Header.dwType = NOTIFY_JOIN_TEAM_FULL;
	send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYJOINTEAMFULL);
	LOCK_CHARACTER(0);
	strcpy(EventNotifyJoinTeamFull.LeaderMainName, GetCharacterMainName(leader_npc_no));
	UNLOCK_CHARACTER(0);
	memcpy(send_packet.data.cBuf, &EventNotifyJoinTeamFull, sizeof(TPOS_EVENT_NOTIFYJOINTEAMFULL));
	server_send_packet_to_one(cn, &send_packet);
}
// -----------------------------------------------------------------------------
void	ServerDoSendSomeoneWantJoinTeam(char *leader_mainname, char *member_mainname, char *member_zonename)
{
	TPOS_EVENT_NOTIFYSOMEONEWANTJOINTEAM	EventNotifySomeoneWantJoinTeam;
	TPOS_PACKET		send_packet;
	int				cn_index;

	strcpy(EventNotifySomeoneWantJoinTeam.MemberMainName, member_mainname);
	strcpy(EventNotifySomeoneWantJoinTeam.MemberZoneName, member_zonename);
	send_packet.Header.dwType = NOTIFY_SOMEONE_WANT_JOIN_TEAM;
	send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYSOMEONEWANTJOINTEAM);
	memcpy(send_packet.data.cBuf, &EventNotifySomeoneWantJoinTeam, sizeof(TPOS_EVENT_NOTIFYSOMEONEWANTJOINTEAM));
	LOCK_CONNECTION(0);
	cn_index = FindConnectionByName(leader_mainname);
	UNLOCK_CONNECTION(0);
	if(cn_index >= 0)
	{
		server_send_packet_to_one(&Pos_Cn[cn_index], &send_packet);
	}	
}
// -----------------------------------------------------------------------------
void	ServerDoSendMakeTeam(SLONG leader_npc_no, SLONG member_npc_no)
{
	TPOS_EVENT_NOTIFYMAKETEAM	EventNotifyMakeTeam;
	TPOS_PACKET					send_packet;
	int		i;
	SLONG	cn_index;
	char	leader_mainname[32];
	char	member_mainname[32];
	
	memset(&EventNotifyMakeTeam, 0x0, sizeof(TPOS_EVENT_NOTIFYMAKETEAM));
	
	// 存隊長自己的資訊		
	ServerDoAddTeamMember(leader_npc_no, leader_npc_no, 0);	
	ServerDoAddTeamMember(leader_npc_no, member_npc_no, 1);	
	ServerDoAddTeamMember(member_npc_no, leader_npc_no, 0);	
	ServerDoAddTeamMember(member_npc_no, member_npc_no, 1);	
	
	LOCK_CHARACTER(0);
	strcpy(leader_mainname, GetCharacterMainName(leader_npc_no));
	strcpy(member_mainname, GetCharacterMainName(member_npc_no));
	for(i = 0; i < MAX_CHARACTER_TEAM_MEMBERS; i++)
	{		
		strcpy(EventNotifyMakeTeam.TeamMemberInfo[i].MainName, GetCharacterTeamMemberMainName(leader_npc_no, i));
		EventNotifyMakeTeam.TeamMemberInfo[i].Hp = (UHINT)GetCharacterTeamMemberHp(leader_npc_no, i);
		EventNotifyMakeTeam.TeamMemberInfo[i].MaxHp = (UHINT)GetCharacterTeamMemberMaxHp(leader_npc_no, i);
		EventNotifyMakeTeam.TeamMemberInfo[i].Eyes = (CHAR)GetCharacterTeamMemberEyes(leader_npc_no, i);
		EventNotifyMakeTeam.TeamMemberInfo[i].Level = (UHINT)GetCharacterTeamMemberLevel(leader_npc_no, i);
		EventNotifyMakeTeam.TeamMemberInfo[i].Career = (CHAR)GetCharacterTeamMemberCareer(leader_npc_no, i);
		EventNotifyMakeTeam.TeamMemberInfo[i].Mouth = (CHAR)GetCharacterTeamMemberMouth(leader_npc_no, i);
		EventNotifyMakeTeam.TeamMemberInfo[i].Sex = (CHAR)GetCharacterTeamMemberSex(leader_npc_no, i);
		strcpy(EventNotifyMakeTeam.TeamMemberInfo[i].ZoneName, GetCharacterTeamMemberZoneName(leader_npc_no, i));	
	}
	UNLOCK_CHARACTER(0);
	
	send_packet.Header.dwType = NOTIFY_MAKE_TEAM;
	send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYMAKETEAM);
	
	memcpy(send_packet.data.cBuf, &EventNotifyMakeTeam, sizeof(TPOS_EVENT_NOTIFYMAKETEAM));
	
	// 給隊長
	LOCK_CONNECTION(0);	
	cn_index = FindConnectionByName(leader_mainname);
	UNLOCK_CONNECTION(0);			
	if(cn_index >= 0 && cn_index < 500)
	{
		server_send_packet_to_one(&Pos_Cn[cn_index], &send_packet);
	}
	// 給隊員	
	LOCK_CONNECTION(0);	
	cn_index = FindConnectionByName(member_mainname);
	UNLOCK_CONNECTION(0);			
	if(cn_index >= 0 && cn_index < 500)
	{
		server_send_packet_to_one(&Pos_Cn[cn_index], &send_packet);
	}
}
// -----------------------------------------------------------------------------
void	ServerDoSendSomeoneJoinTeam(SLONG leader_npc_no, SLONG member_npc_no)
{
	TPOS_EVENT_NOTIFYSOMEONEJOINTEAM	EventNotifySomeoneJoinTeam;
	TPOS_EVENT_NOTIFYTEAMMEMBERINFO		EventNotifyTeamMemberInfo;	
	TPOS_PACKET		send_packet;
	SLONG			cn_index;
	char			temp_mainname[32];
	char			leader_mainname[32];
	char			member_mainname[32];
	int				i;
	SLONG			index;
	SLONG			temp_npc_no;
	
	LOCK_CHARACTER(0);
	strcpy(leader_mainname, GetCharacterMainName(leader_npc_no));
	strcpy(member_mainname, GetCharacterMainName(member_npc_no));
	UNLOCK_CHARACTER(0);

	index = FindUseableTeamInfo(leader_npc_no);
	if(index != -1)
	{		
		ServerDoAddTeamMember(leader_npc_no, member_npc_no, index);
	}
	
	for(i = 1; i < MAX_CHARACTER_TEAM_MEMBERS; i++)
	{
		LOCK_CHARACTER(0);
		strcpy(temp_mainname, GetCharacterTeamMemberMainName(leader_npc_no, i));
		UNLOCK_CHARACTER(0);
		if(strcmp(temp_mainname, "") != 0)
		{
			LOCK_CHARACTER(0);
			temp_npc_no = FindCharacterByMainName(GetCharacterTeamMemberMainName(leader_npc_no, i));
			UNLOCK_CHARACTER(0);
			ServerDoCopyTeamInfo(leader_npc_no, temp_npc_no);
		}		
	}		

	send_packet.Header.dwType = NOTIFY_SOMEONE_JOIN_TEAM;
	send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYSOMEONEJOINTEAM);
	LOCK_CHARACTER(0);
	strcpy(EventNotifySomeoneJoinTeam.MainName, GetCharacterMainName(member_npc_no));
	EventNotifySomeoneJoinTeam.Career = (CHAR)GetCharacterCareer(member_npc_no);
	EventNotifySomeoneJoinTeam.Eyes = (CHAR)GetCharacterEyes(member_npc_no);
	EventNotifySomeoneJoinTeam.Mouth = (CHAR)GetCharacterMouth(member_npc_no);
	EventNotifySomeoneJoinTeam.Hp = (UHINT)GetCharacterHp(member_npc_no);
	EventNotifySomeoneJoinTeam.Level = (UHINT)GetCharacterLevel(member_npc_no);
	EventNotifySomeoneJoinTeam.MaxHp = (UHINT)GetCharacterMaxHp(member_npc_no);		
	EventNotifySomeoneJoinTeam.Sex = (CHAR)GetCharacterSex(member_npc_no);		
	strcpy(EventNotifySomeoneJoinTeam.ZoneName, GetCharacterZoneName(member_npc_no));
	UNLOCK_CHARACTER(0);

	memcpy(send_packet.data.cBuf, &EventNotifySomeoneJoinTeam, sizeof(TPOS_EVENT_NOTIFYSOMEONEJOINTEAM));

	// 給隊長
	LOCK_CONNECTION(0);	
	cn_index = FindConnectionByName(leader_mainname);
	UNLOCK_CONNECTION(0);			
	if(cn_index >= 0 && cn_index < 500)
	{
		server_send_packet_to_one(&Pos_Cn[cn_index], &send_packet);
	}	
	// 給隊友
	for(i = 1; i < MAX_CHARACTER_TEAM_MEMBERS; i++)
	{	
		LOCK_CHARACTER(0);
		strcpy(temp_mainname, GetCharacterTeamMemberMainName(leader_npc_no, i));
		UNLOCK_CHARACTER(0);
		if(strcmp(temp_mainname, member_mainname) != 0 && strcmp(temp_mainname, "") != 0)
		{			
			LOCK_CONNECTION(0);
			cn_index = FindConnectionByName(temp_mainname);
			UNLOCK_CONNECTION(0);			
			if(cn_index >= 0 && cn_index < 500)
			{
				server_send_packet_to_one(&Pos_Cn[cn_index], &send_packet);
			}
		}			
	}
	// 發所有隊友資訊給新加入隊員
	memset(&EventNotifyTeamMemberInfo, 0x0, sizeof(TPOS_EVENT_NOTIFYTEAMMEMBERINFO));
		
	LOCK_CHARACTER(0);		
	for(i = 0; i < MAX_CHARACTER_TEAM_MEMBERS; i++)
	{							
		strcpy(EventNotifyTeamMemberInfo.TeamMemberInfo[i].MainName, GetCharacterTeamMemberMainName(leader_npc_no, i));			
		EventNotifyTeamMemberInfo.TeamMemberInfo[i].Career = (CHAR)GetCharacterTeamMemberCareer(leader_npc_no, i);
		EventNotifyTeamMemberInfo.TeamMemberInfo[i].Sex = (CHAR)GetCharacterTeamMemberSex(leader_npc_no, i);
		EventNotifyTeamMemberInfo.TeamMemberInfo[i].Eyes = (CHAR)GetCharacterTeamMemberEyes(leader_npc_no, i);
		EventNotifyTeamMemberInfo.TeamMemberInfo[i].Mouth = (CHAR)GetCharacterTeamMemberMouth(leader_npc_no, i);
		EventNotifyTeamMemberInfo.TeamMemberInfo[i].Hp = (UHINT)GetCharacterTeamMemberHp(leader_npc_no, i);
		EventNotifyTeamMemberInfo.TeamMemberInfo[i].MaxHp = (UHINT)GetCharacterTeamMemberMaxHp(leader_npc_no, i);	
		EventNotifyTeamMemberInfo.TeamMemberInfo[i].Level = (UHINT)GetCharacterTeamMemberLevel(leader_npc_no, i);
		strcpy(EventNotifyTeamMemberInfo.TeamMemberInfo[i].ZoneName, GetCharacterTeamMemberZoneName(leader_npc_no, i));
	}
	UNLOCK_CHARACTER(0);
	send_packet.Header.dwType = NOTIFY_TEAM_MEMBER_INFO;
	send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYTEAMMEMBERINFO);
	memcpy(send_packet.data.cBuf, &EventNotifyTeamMemberInfo, sizeof(TPOS_EVENT_NOTIFYTEAMMEMBERINFO));

	LOCK_CONNECTION(0);
	cn_index = FindConnectionByName(member_mainname);
	UNLOCK_CONNECTION(0);
	if(cn_index >= 0)
	{
		server_send_packet_to_one(&Pos_Cn[cn_index], &send_packet);
	}	
}
// -----------------------------------------------------------------------------
void	ServerDoSendSomeoneExitTeam(SLONG leader_npc_no, char *leader_mainname, char *member_mainname)
{
	TPOS_EVENT_NOTIFYSOMEONEEXITTEAM	EventNotifySomeoneExitTeam;
	TPOS_PACKET		send_packet;
	SLONG			cn_index;
	SLONG			member_npc_no;
	SLONG			temp_npc_no;
	char			temp_mainname[32];
	int				i;
	SLONG			index;
	
	send_packet.Header.dwType = NOTIFY_SOMEONE_EXIT_TEAM;
	send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYSOMEONEEXITTEAM);
	strcpy(EventNotifySomeoneExitTeam.MemberMainName, member_mainname);
	memcpy(send_packet.data.cBuf, &EventNotifySomeoneExitTeam, sizeof(TPOS_EVENT_NOTIFYSOMEONEEXITTEAM));
	// 給隊長
	LOCK_CONNECTION(0);
	cn_index = FindConnectionByName(leader_mainname);
	UNLOCK_CONNECTION(0);			
	if(cn_index >= 0 && cn_index < 500)
	{
		server_send_packet_to_one(&Pos_Cn[cn_index], &send_packet);
	}
	// 給隊友
	for(i = 1; i < MAX_CHARACTER_TEAM_MEMBERS; i++)
	{
		LOCK_CHARACTER(0);
		strcpy(temp_mainname, GetCharacterTeamMemberMainName(leader_npc_no, i));
		UNLOCK_CHARACTER(0);
		if(strcmp(temp_mainname, "") != 0)
		{			
			LOCK_CONNECTION(0);
			cn_index = FindConnectionByName(temp_mainname);
			UNLOCK_CONNECTION(0);			
			if(cn_index >= 0 && cn_index < 500)
			{
				server_send_packet_to_one(&Pos_Cn[cn_index], &send_packet);
			}
		}			
	}		
	// 隊友的隊伍資料清除離開隊員
	for(i = 1; i < MAX_CHARACTER_TEAM_MEMBERS; i++)
	{
		LOCK_CHARACTER(0);
		strcpy(temp_mainname, GetCharacterTeamMemberMainName(leader_npc_no, i));
		UNLOCK_CHARACTER(0);
		if(strcmp(temp_mainname, "") != 0)
		{
			LOCK_CHARACTER(0);
			temp_npc_no = FindCharacterByMainName(temp_mainname);
			UNLOCK_CHARACTER(0);
			index = FindSomeoneInTeam(temp_npc_no, member_mainname);
			ServerDoDeleteTeamMember(temp_npc_no, index);
		}
	}
	// 清除離開隊員的隊伍資料
	LOCK_CHARACTER(0);
	member_npc_no = FindCharacterByMainName(member_mainname);
	UNLOCK_CHARACTER(0);
	ServerDoClearTeamInfo(member_npc_no);
	// 隊長的隊伍資料清除離開隊員
	index = FindSomeoneInTeam(leader_npc_no, member_mainname);
	ServerDoDeleteTeamMember(leader_npc_no, index);
}
// -----------------------------------------------------------------------------
void	ServerDoSendKillTeam(SLONG leader_npc_no)
{
	TPOS_PACKET	send_packet;
	int			i;
	char		temp_mainname[32];
	SLONG		cn_index;
	SLONG		temp_npc_no;

	send_packet.Header.dwType = NOTIFY_KILL_TEAM;
	send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER);

	for(i = 1; i < MAX_CHARACTER_TEAM_MEMBERS; i++)
	{
		LOCK_CHARACTER(0);
		strcpy(temp_mainname, GetCharacterTeamMemberMainName(leader_npc_no, i));
		UNLOCK_CHARACTER(0);
		if(strcmp(temp_mainname, "") != 0)
		{
			LOCK_CHARACTER(0);
			temp_npc_no = FindCharacterByMainName(temp_mainname);
			UNLOCK_CHARACTER(0);
			ServerDoClearTeamInfo(temp_npc_no);
			LOCK_CONNECTION(0);
			cn_index = FindConnectionByName(temp_mainname);
			UNLOCK_CONNECTION(0);			
			if(cn_index >= 0 && cn_index < 500)
			{
				server_send_packet_to_one(&Pos_Cn[cn_index], &send_packet);
			}
		}
	}	
	// 處理隊長部分
	ServerDoClearTeamInfo(leader_npc_no);
	LOCK_CHARACTER(0);
	strcpy(temp_mainname, GetCharacterMainName(leader_npc_no));
	UNLOCK_CHARACTER(0);
	LOCK_CONNECTION(0);
	cn_index = FindConnectionByName(temp_mainname);
	UNLOCK_CONNECTION(0);			
	if(cn_index >= 0 && cn_index < 500)
	{
		server_send_packet_to_one(&Pos_Cn[cn_index], &send_packet);
	}
}
// -----------------------------------------------------------------------------
void	ServerDoSendChangeLeader(SLONG old_leader_npc_no)
{	
	TPOS_EVENT_NOTIFYCHANGELEADER	EventNotifyChangeLeader;
	TPOS_PACKET		send_packet;
	int				i, j;
	SLONG			cn_index;
	char			temp_mainname[32];
	SLONG			temp_npc_no;
	
	j = 0;
	ServerDoDeleteTeamMember(old_leader_npc_no, 0);

	for(i = 0; i < MAX_CHARACTER_TEAM_MEMBERS; i++)
	{
		LOCK_CHARACTER(0);
		strcpy(temp_mainname, GetCharacterTeamMemberMainName(old_leader_npc_no, i));		
		if(strcmp(temp_mainname, "") != 0)
		{
			SetCharacterTeamMemberMainName(old_leader_npc_no, j, temp_mainname);
			SetCharacterTeamMemberHp(old_leader_npc_no, j, (UHINT)GetCharacterTeamMemberHp(old_leader_npc_no, i));
			SetCharacterTeamMemberMaxHp(old_leader_npc_no, j, (UHINT)GetCharacterTeamMemberMaxHp(old_leader_npc_no, i));
			SetCharacterTeamMemberCareer(old_leader_npc_no, j, (CHAR)GetCharacterTeamMemberCareer(old_leader_npc_no, i));
			SetCharacterTeamMemberLevel(old_leader_npc_no, j, (UHINT)GetCharacterTeamMemberLevel(old_leader_npc_no, i));
			SetCharacterTeamMemberEyes(old_leader_npc_no, j, (CHAR)GetCharacterTeamMemberEyes(old_leader_npc_no, i));
			SetCharacterTeamMemberMouth(old_leader_npc_no, j, (CHAR)GetCharacterTeamMemberMouth(old_leader_npc_no, i));
			SetCharacterTeamMemberSex(old_leader_npc_no, j, (CHAR)GetCharacterTeamMemberSex(old_leader_npc_no, i));
			SetCharacterTeamMemberZoneName(old_leader_npc_no, j, GetCharacterTeamMemberZoneName(old_leader_npc_no, i));			
			j++;
		}
		UNLOCK_CHARACTER(0);
	}

	// 將其他的空位清空
	for(i = j; i < MAX_CHARACTER_TEAM_MEMBERS; i++)
	{
		ServerDoDeleteTeamMember(old_leader_npc_no, i);
	}

	LOCK_CHARACTER(0);
	for(i = 0; i < MAX_CHARACTER_TEAM_MEMBERS; i++)
	{
		strcpy(EventNotifyChangeLeader.TeamMemberInfo[i].MainName, 
			   GetCharacterTeamMemberMainName(old_leader_npc_no, i));  
		EventNotifyChangeLeader.TeamMemberInfo[i].Hp = GetCharacterTeamMemberHp(old_leader_npc_no, i);
		EventNotifyChangeLeader.TeamMemberInfo[i].MaxHp = GetCharacterTeamMemberMaxHp(old_leader_npc_no, i);
		EventNotifyChangeLeader.TeamMemberInfo[i].Level = GetCharacterTeamMemberLevel(old_leader_npc_no, i);
		EventNotifyChangeLeader.TeamMemberInfo[i].Eyes = (CHAR)GetCharacterTeamMemberEyes(old_leader_npc_no, i);
		EventNotifyChangeLeader.TeamMemberInfo[i].Mouth = (CHAR)GetCharacterTeamMemberMouth(old_leader_npc_no, i);
		EventNotifyChangeLeader.TeamMemberInfo[i].Career = (CHAR)GetCharacterTeamMemberCareer(old_leader_npc_no, i);
		EventNotifyChangeLeader.TeamMemberInfo[i].Sex = (CHAR)GetCharacterTeamMemberSex(old_leader_npc_no, i);
		strcpy(EventNotifyChangeLeader.TeamMemberInfo[i].ZoneName, 
			   GetCharacterTeamMemberZoneName(old_leader_npc_no, i));
	}	
	UNLOCK_CHARACTER(0);

	send_packet.Header.dwType = NOTIFY_CHANGE_LEADER;
	send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER) + sizeof(TPOS_EVENT_NOTIFYCHANGELEADER);
	memcpy(send_packet.data.cBuf, &EventNotifyChangeLeader, sizeof(TPOS_EVENT_NOTIFYCHANGELEADER));

	for(i = 0; i < MAX_CHARACTER_TEAM_MEMBERS; i++)
	{
		LOCK_CHARACTER(0);
		strcpy(temp_mainname, GetCharacterTeamMemberMainName(old_leader_npc_no, i));		
		UNLOCK_CHARACTER(0);
		if(strcmp(temp_mainname, "") != 0)
		{
			LOCK_CHARACTER(0);
			temp_npc_no = FindCharacterByMainName(temp_mainname);
			UNLOCK_CHARACTER(0);
			ServerDoCopyTeamInfo(old_leader_npc_no, temp_npc_no);
			LOCK_CONNECTION(0);
			cn_index = FindConnectionByName(temp_mainname);
			UNLOCK_CONNECTION(0);
			if(cn_index >= 0)
			{
				server_send_packet_to_one(&Pos_Cn[cn_index], &send_packet);
			}			
		}		
	}
	// 清除原來隊長的資料
	ServerDoClearTeamInfo(old_leader_npc_no);

	send_packet.Header.dwType = NOTIFY_KILL_TEAM;
	send_packet.Header.dwSize = sizeof(TPOS_PACKETHEADER);
	LOCK_CHARACTER(0);
	strcpy(temp_mainname, GetCharacterMainName(old_leader_npc_no));
	UNLOCK_CHARACTER(0);
	LOCK_CONNECTION(0);
	cn_index = FindConnectionByName(temp_mainname);
	UNLOCK_CONNECTION(0);
	if(cn_index >= 0)
	{
		server_send_packet_to_one(&Pos_Cn[cn_index], &send_packet);
	}				
}
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

