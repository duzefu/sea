// =============================================================================
// CommonFunc.cpp
// Psalm of Sea DDL Common Function Source By Hawke Hsieh
// Last Modify Date : 2002.04.25
// =============================================================================

#include "HNETGEH.h"
#ifdef __NETGE_NETWORK__

#include "Netge_Extern.h"

// -----------------------------------------------------------------------------
// Init WSAStarup
// -----------------------------------------------------------------------------
#ifdef BCBUSED
int _PosInit()
#else
NETGE_API int NETGE_FNB PosInit()
#endif
{
	int	iRet;

	TotalSendDataSize = 0;
	TotalRecvDataSize = 0;

	// ±Ò©l Winsock
    // The high order byte specifies the minor version (revision) number;
	// The low-order byte specifies the major version number.
	wVersionRequested = MAKEWORD(1, 2);  // Winsock 2
	iRet = WSAStartup(wVersionRequested, &wd);
    if(iRet != 0)
	{
		WSACleanup();
		return 0;
	}
	return 1;
}
// -----------------------------------------------------------------------------
// Return Connected Server Type
// -----------------------------------------------------------------------------
#ifdef BCBUSED
int _PosGetCurrentConnectedType()
#else
NETGE_API int NETGE_FNB PosGetCurrentConnectedType()
#endif
{	  
 return g_dwConnectedServerType;	
}
// -----------------------------------------------------------------------------
// Get Total Recv Data Size
// -----------------------------------------------------------------------------
#ifdef BCBUSED
ULONG _PosGetTotalRecvDataSize()
#else
NETGE_API ULONG NETGE_FNB PosGetTotalRecvDataSize()
#endif
{	  
	return TotalRecvDataSize;	
}
// -----------------------------------------------------------------------------
// Get Total Send Data Size
// -----------------------------------------------------------------------------
#ifdef BCBUSED
ULONG _PosGetTotalSendDataSize()
#else
NETGE_API ULONG NETGE_FNB PosGetTotalSendDataSize()
#endif
{	  
	return TotalSendDataSize;	
}
// -----------------------------------------------------------------------------
// Set Total Recv Data Size
// -----------------------------------------------------------------------------
#ifdef BCBUSED
int _PosSetTotalRecvDataSize(ULONG size)
#else
NETGE_API int NETGE_FNB PosSetTotalRecvDataSize(ULONG size)
#endif
{	  
	TotalRecvDataSize = size;	
	
	return DLL_OK;
}
// -----------------------------------------------------------------------------
// Set Total Send Data Size
// -----------------------------------------------------------------------------
#ifdef BCBUSED
int _PosSetTotalSendDataSize(ULONG size)
#else
NETGE_API int NETGE_FNB PosSetTotalSendDataSize(ULONG size)
#endif
{	  
	TotalSendDataSize = size;	

	return DLL_OK;
}
// -----------------------------------------------------------------------------
// Free Memory
// -----------------------------------------------------------------------------
#ifdef BCBUSED
int _PosFreeMemory()
#else
NETGE_API int NETGE_FNB PosFreeMemory()
#endif
{ 

 WSACleanup();

 TotalSendDataSize = 0;
 TotalRecvDataSize = 0;

 return DLL_OK;
}
// -----------------------------------------------------------------------------
// Sea Sync Position Data Decode
// -----------------------------------------------------------------------------
/*
#ifdef BCBUSED
void	_decode_sea_npc_sync_position(SLONG sync_x, SLONG sync_y, SLONG sync_z, 
									  SLONG &degree_dir, SLONG &x, SLONG &y, 
									  SLONG &speed_x, SLONG &speed_y)
#else
NETGE_API void NETGE_FNB decode_sea_npc_sync_position(SLONG sync_x, SLONG sync_y, SLONG sync_z, 
													  SLONG &degree_dir, SLONG &x, SLONG &y, 
													  SLONG &speed_x, SLONG &speed_y)
#endif
{
	ULONG	ulong_z;
	ULONG	ulong_speed_x, ulong_speed_y, ulong_degree_dir;

	ulong_z = (ULONG)sync_z;
	ulong_speed_y = ulong_z & 0x000003ff;
	ulong_speed_x = (ulong_z & 0x000ffc00) >> 10;
	ulong_degree_dir = (ulong_z & 0x3ff00000) >> 20;
	degree_dir = (SLONG)ulong_degree_dir;
	speed_x = (SLONG)ulong_speed_x - 500;
	speed_y = (SLONG)ulong_speed_y - 500;
	x = sync_x;
	y = sync_y;
}
*/
// -----------------------------------------------------------------------------
#endif
