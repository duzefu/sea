#ifndef _SERVERREFRESHGAME_H_
#define _SERVERREFRESHGAME_H_

void	RefreshMainGame(void);
void	CheckConnectPoint(void);
void	CheckWheather(void);
int		SaveCharacterInfo(DWORD cnIndex,TPOS_DB_CHARACTER *dbcharacter);
void	CheckNameColorTicks(ULONG npc_no);

#endif