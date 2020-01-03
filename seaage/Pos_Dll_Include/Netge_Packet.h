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
//#define		MSG_STR_LEN		        		450   // 字串長度
#define		MAX_PACKET_SIZE	        	   20480   // 最大封包大小
#define		MAX_COMPACKET_SIZE	       	   4096   // 最大壓縮後的封包大小
//#define     BUFSIZE                        1024   // 緩衝區大小

// STRUCTURES ////////////////////////////////////////////////////////////////////////////////////////////////////////
//
#pragma pack(push)
#pragma	pack(1)

//封包標頭結構
typedef	struct POS_PACKETHEADER
{
	DWORD	dwType;			//	Event Type
	DWORD	dwSize;			//	Packet Size
	DWORD	dwVersion;		//	Packet Version
}TPOS_PACKETHEADER;
//封包資料結構
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