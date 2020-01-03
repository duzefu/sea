#ifndef WORLDSERVERMISC_H
#define WORLDSERVERMISC_H

int     FindUsableZoneQQOnlinePlayerList(int zoneindex);
int     FindUsableZoneInfo(void);
int     FindZoneInfoByName(char *name);
int     FindZoneInfoByMapName(char *mapname);
int     FindZoneInfoByConnection(TPOS_CN *cn);
int		GetQQOnlinePlayerListByQQID(ULONG QQID, ULONG zoneindex);
int		FindQQOnliePlayerByQQID(int	zoneindex, ULONG QQID);
int		FindQQOnliePlayerZoneIndexByQQID(ULONG	QQID);

void	ServerDoDoorLoginOK(TPOS_CN	*cn, TPOS_PACKET *packet);
void	ServerDoPlayerLogin(TPOS_CN *cn, TPOS_PACKET *packet);
void	ServerDoRequestCharacterDefault(TPOS_CN *cn, TPOS_PACKET *packet);
void	ServerDoCreateCharacterCheck(TPOS_CN *cn, TPOS_PACKET *packet);
void	ServerDoCreateCharacterFinal(TPOS_CN *cn, TPOS_PACKET *packet);
void	ServerDoDeleteCharacter(TPOS_CN *cn, TPOS_PACKET *packet);
void	ServerDoRequestCharacterInfo(TPOS_CN *cn, TPOS_PACKET *packet);
void	ServerDoCharacterSelected(TPOS_CN *cn, TPOS_PACKET *packet);
void	ServerDoQQPlayerLogin(TPOS_CN *cn, TPOS_PACKET *packet);
void	ServerDoQQPlayerLogout(TPOS_CN *cn, TPOS_PACKET *packet);
void	ServerDoQQRequestFriendList(TPOS_CN *cn, TPOS_PACKET *packet);
void	ServerDoQQRequestGuildFriendList(TPOS_CN *cn, TPOS_PACKET *packet);
void	ServerDoQQSetMyState(TPOS_CN *cn, TPOS_PACKET *packet);
void	ServerDoQQRequestQueryAddList(TPOS_CN *cn, TPOS_PACKET *packet);
void	ServerDoQQRequestQueryOnlineAddList(TPOS_CN *cn, TPOS_PACKET *packet);
void	ServerDoQQRequestQuerySomeone(TPOS_CN *cn, TPOS_PACKET *packet);
void	ServerDoQQRequestAddSomeone(TPOS_CN *cn, TPOS_PACKET *packet);
void	ServerDoQQsend2OneMsg(TPOS_CN *cn, TPOS_PACKET *packet);
void	ServerDoQQRequestPlayerCount(TPOS_CN *cn, TPOS_PACKET *packet);
void	ServerDoQQRequestDeleteFriend(TPOS_CN *cn, TPOS_PACKET *packet);
void	ServerDoQQRequestDeleteGuildFriend(TPOS_CN *cn, TPOS_PACKET *packet);
void	ServerDoQQRequestTransferItem(TPOS_CN *cn, TPOS_PACKET *packet);
void	ServerDoQQTransferItemOK(TPOS_CN *cn, TPOS_PACKET *packet);
void	ServerDoQQTransferItemFail(TPOS_CN *cn, TPOS_PACKET *packet);
void	ServerDoPlayerRequestLoginZone(TPOS_CN *cn, TPOS_PACKET *packet);
void	ServerDoZoneLogin(TPOS_CN *cn, TPOS_PACKET *packet);
void	ServerDoNewZoneInfo(TPOS_CN *cn, TPOS_PACKET *packet);
void	ServerDoRequestZoneInfo(TPOS_CN *cn, TPOS_PACKET *packet);
void	ServerDoRefreshZoneInfo(TPOS_CN *cn, TPOS_PACKET *packet);
void	ServerDoSendWorldTalk(TPOS_CN *cn, TPOS_PACKET *packet);
void	ServerDoZoneRequestJoinTeam(TPOS_CN *cn, TPOS_PACKET *packet);
void	ServerDoZoneRequestAgreeJoinTeam(TPOS_CN *cn, TPOS_PACKET *packet);
void	ServerDoZoneRequestExitTeam(TPOS_CN *cn, TPOS_PACKET *packet);
void	ServerDoZoneRequestKickTeamMember(TPOS_CN *cn, TPOS_PACKET *packet);
void	ServerDoZoneNotifySomeoneWantJoinTeam(TPOS_CN *cn, TPOS_PACKET *packet);
void	ServerDoZoneNotifyJoinTeamFull(TPOS_CN *cn, TPOS_PACKET *packet);
void	ServerDoZoneNotifySomeoneJoinTeam(TPOS_CN *cn, TPOS_PACKET *packet);
void	ServerDoZoneNotifySomeoneExitTeam(TPOS_CN *cn, TPOS_PACKET *packet);
void	ServerDoZoneNotifyKickFromTeam(TPOS_CN *cn, TPOS_PACKET *packet);
void	ServerDoZoneNotifyTeamMemberInfo(TPOS_CN *cn, TPOS_PACKET *packet);
void	ServerDoZoneNotifyTeamMemberChangeZone(TPOS_CN *cn, TPOS_PACKET *packet);
void	ConvertEventCharacterFinalToDbCharacter(TPOS_EVENT_CREATECHARACTERFINAL *eccf, TPOS_DB_CHARACTER *dc);
void	ConvertDbCharacterToEventGetCharacterInfo(TPOS_DB_CHARACTER *dc, TPOS_EVENT_GETCHARACTERINFO *egc);

#endif
