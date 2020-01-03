#ifndef _DOINGPROCESS_H_
#define _DOINGPROCESS_H_

int FindConnectionByName(char *mainname);
int FindOldConnectionByName(char *mainname,WPARAM wParam);
int FindCurrentConnection(WPARAM wParam);
SLONG FindCurrentConnectionQQID(TPOS_CN *cn);
int FindCurrentSyncConnection(WPARAM wParam);
int FindCurrentConnectionCharacter(TPOS_CN *cn);

int ReadPacket(TPOS_CN *cn);
int WritePacket(TPOS_CN *cn);
int QueuePacket(TPOS_CN *cn, TPOS_COMPACKET *compacket,DWORD ServerType);
int ProcessPacket(TPOS_CN *cn);
LRESULT CALLBACK DoorSocketWndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WorldSocketWndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK ZoneSocketWndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK ZoneSyncSocketWndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
int RequestForWorldInfo(DWORD index);
int RequestForZoneInfo(DWORD index);
void SendPlayerExitToAll(int index);
void SendPlayerJoinToAll(TPOS_CN *cn, TPOS_EVENT_PLAYERJOIN *EventPlayerJoin);
void SendRefreshZoneInfoToWorld();
void CompressPacket(TPOS_PACKET	*packet, TPOS_COMPACKET *compacket);
int server_send_packet_to_all(void *packet);
int server_send_packet_to_one(void *connect, void *packet);
int server_send_packet_to_player(int player_index, void *packet);
int server_send_packet_to_teammember(int npc_no, void *packet);
void SendRefreshToAll(DWORD s);
void SendPositionToAll(void);
void SendSeaPositionToAll(void);
int SendNPCReliveToAll(TPOS_PACKET *packet);
int SendSystemMessageToAll(TPOS_PACKET *packet);
int SendCharacterQuickSkillItem(DWORD index, DWORD zonetype, TPOS_CN *cn);
int SendCharacterSkill(DWORD index,TPOS_CN *cn);
int SendSystemMessage(TPOS_CN *cn);
void SendCurrentWeatherToNewPlayer(TPOS_CN *cn);
void	ServerSendUpdateNpcDoing(DWORD Index, SLONG doingkind, LONG doingstep,
								 SLONG d1, SLONG d2, SLONG d3, SLONG d4, SLONG d5);
void	ServerSendChangeNpcDoing(DWORD Index, SLONG doingkind, LONG doingstep,
								 SLONG d1, SLONG d2, SLONG d3, SLONG d4, SLONG d5);
void	ServerSendNpcAIBlock(SLONG	index, UHINT ai_block, SLONG dest_npc_no, SLONG x, SLONG y, SLONG z, UHINT skill_no);
void	ServerSendMagicArea(CHAR Type, CHAR	Dir, SLONG X, SLONG Y, SLONG NpcNo, SLONG MagicNo);
void	ServerSendPlayerJoinToOthers(TPOS_CN *cn, TPOS_PACKET *packet);
void	SendRepeatLoginedPlayer(DWORD index, TPOS_PACKET *packet);
void	ServerSendNotifyBreakMagicToAll(SLONG npc_no, SLONG dest_x, SLONG dest_y, SLONG magic_index);
#endif