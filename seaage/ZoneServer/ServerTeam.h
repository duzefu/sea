/*
**	ServerTeam.h 
**	server team functions header.
**
**	Hawke, 2003.05.06
*/
#ifndef	_SERVERTEAM_H_
#define	_SERVERTEAM_H_

SLONG	ServerCheckTeamIsFull(SLONG leader_npc_no);
SLONG	ServerCheckIsInTeam(SLONG npc_no);
SLONG	FindUseableTeamInfo(SLONG npc_no);
SLONG	FindSomeoneInTeam(SLONG leader_npc_no, char *member_mainname);
SLONG	ServerCheckTeamMemberNumber(SLONG leader_npc_no);
SLONG	ServerCheckSomeoneIsInTeam(SLONG leader_npc_no, char *member_mainname);
void	ServerDoAddTeamMember(SLONG npc_no, SLONG target_npc_no, SLONG index);
void	ServerDoDeleteTeamMember(SLONG npc_no, SLONG index);
void	ServerDoClearTeamInfo(SLONG npc_no);

void	ServerDoSendTeamFull(TPOS_CN *cn, SLONG leader_npc_no);
void	ServerDoSendSomeoneWantJoinTeam(char *leader_mainname, char *member_mainname, char *member_zonename);
void	ServerDoSendMakeTeam(SLONG leader_npc_no, SLONG member_npc_no);
void	ServerDoSendSomeoneJoinTeam(SLONG leader_npc_no, SLONG member_npc_no);
void	ServerDoSendSomeoneExitTeam(SLONG leader_npc_no, char *leader_mainname, char *member_mainname);
void	ServerDoSendKillTeam(SLONG leader_npc_no);
void	ServerDoSendChangeLeader(SLONG old_leader_npc_no);

#endif//_SERVERTEAM_H_