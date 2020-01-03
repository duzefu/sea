/*
**	NetGE_Packet.h 
**	Hawke Hsieh, 2002.12.31
*/
#ifndef	_NETGE_PACKET_H_
#define	_NETGE_PACKET_H_

// DEFINES ///////////////////////////////////////////////////////////////////////////////////////////////////////////
// ---------------------------------------------------------------------------
// Buffer Langeth Set
// ---------------------------------------------------------------------------
//#define		MSG_STR_LEN		        		450   // �r�����
#define		MAX_PACKET_SIZE	        	   20480   // �̤j�ʥ]�j�p
#define		MAX_COMPACKET_SIZE	       	   4096   // �̤j���Y�᪺�ʥ]�j�p
//#define     BUFSIZE                        1024   // �w�İϤj�p

// STRUCTURES ////////////////////////////////////////////////////////////////////////////////////////////////////////
//
#pragma pack(push)
#pragma	pack(1)

//�ʥ]���Y���c
typedef	struct POS_PACKETHEADER
{
	DWORD	dwType;			//	Event Type
	DWORD	dwSize;			//	Packet Size
	DWORD	dwVersion;		//	Packet Version
}TPOS_PACKETHEADER;
//�ʥ]��Ƶ��c
typedef	struct POS_PACKET
{	
	TPOS_PACKETHEADER	Header;
	union
	{
		char	cBuf[MAX_PACKET_SIZE - sizeof(TPOS_PACKETHEADER) - sizeof(DWORD)];	
	}data;
}TPOS_PACKET;

typedef	struct POS_COMPACKETHEADER
{
	DWORD		dwSize;
}TPOS_COMPACKETHEADER;

typedef	struct POS_COMPACKET
{	
	TPOS_COMPACKETHEADER	Header;	
	char					cBuf[MAX_COMPACKET_SIZE - sizeof(DWORD)];
}TPOS_COMPACKET;

#pragma pack(pop)
#endif