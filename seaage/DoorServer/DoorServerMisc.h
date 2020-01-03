#ifndef DOORSERVERMISC_H
#define DOORSERVERMISC_H

int     FindUsableWorldInfo(void);
int     FindWorldInfoByName(char *name);
void	ChangeWorldStateToDisable();
void	ChangeWorldStateToEnable();
void	ServerDoPlayerLogin(TPOS_CN	*cn, TPOS_PACKET *packet);
void	ServerDoRegisterAccountCheck(TPOS_CN *cn, TPOS_PACKET *packet);
void	ServerDoRegisterAccountFinal(TPOS_CN *cn, TPOS_PACKET *packet);
void	ServerDoChangeProfile(TPOS_CN *cn, TPOS_PACKET *packet);
void	ServerDoChangePassword(TPOS_CN *cn, TPOS_PACKET *packet);
void	ServerDoWorldServerLogin(TPOS_CN *cn, TPOS_PACKET *packet);
void	ServerDoZoneServerLogin(TPOS_CN *cn, TPOS_PACKET *packet);
void	ServerDoRecvWorldServerInfo(TPOS_CN *cn, TPOS_PACKET *packet);
void	ServerDoRequestWorldServerInfo(TPOS_CN *cn, TPOS_PACKET *packet);
void	ServerDoRefreshWorldServerInfo(TPOS_CN *cn, TPOS_PACKET *packet);
void	ConvertEventRegisterAccountToDbAccout(TPOS_EVENT_REGISTERACCOUNT *erc, TPOS_DB_ACCOUNT *da);
void	ConvertEventChangeProfileToDbAccout(TPOS_EVENT_CHANGEPROFILE *ecp, TPOS_DB_ACCOUNT *da);



#endif