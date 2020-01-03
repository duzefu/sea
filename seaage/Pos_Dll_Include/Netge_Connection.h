//===============================================================================
// Netge_Connection_Def.h
//===============================================================================
#ifndef NETGE_CONNECTION_DEF_H
#define NETGE_CONNECTION_DEF_H

//===============================================================================
#pragma pack(push)
#pragma pack(1)
// ---------------------------------------------------------------------------
// Buffer Struct Define
// �w�İ�
// ---------------------------------------------------------------------------
typedef struct POS_BUFFER        
{
    DWORD				dwSize;
    DWORD				dwLocation;
    struct POS_BUFFER  *next;
    char				cBuf[MAX_COMPACKET_SIZE];
}TPOS_BUFFER;
// ---------------------------------------------------------------------------
// Login Use User Information Struct Define
// �n�J�j�U�M�@�ɦ��A���ϥ�
// ---------------------------------------------------------------------------
typedef struct POS_USERINFO      
{
    char  cId[32];
    char  cPw[32];
    DWORD dVersion;
}TPOS_USERINFO;
// ---------------------------------------------------------------------------
// Connections Information Struct Define
// �s����T
// ---------------------------------------------------------------------------
typedef struct POS_CN            
{
    DWORD				dwSocket;
    struct sockaddr_in	Addr;
    TPOS_USERINFO	   	User;
    TPOS_BUFFER		   *InBuf;
    TPOS_BUFFER		   *OutBuf;
}TPOS_CN;

#pragma pack(pop)

#endif