//---------------------------------------------------------------------------
// Psalm of Sea WorldServer Doing Close Connect
// By Hawke Hsieh 
// 2002-10-07
//---------------------------------------------------------------------------

#include "WorldServer_Def.h"

//---------------------------------------------------------------------------
// Close One Socket
//---------------------------------------------------------------------------
int CloseOneSocket(SOCKET tmp_socket)
{
 LINGER	linger;

 linger.l_onoff = true;
 linger.l_linger = 0;
 setsockopt(tmp_socket,  SOL_SOCKET, SO_LINGER, (LPSTR)&linger, sizeof(linger));
 closesocket(tmp_socket);
 return 1;
}
//---------------------------------------------------------------------------
// Close One Connection
//---------------------------------------------------------------------------
int CloseOneConnection(TPOS_CN *cn)
{
 TPOS_BUFFER 	*tmpbuf;
 CloseOneSocket(cn->dwSocket);
 while(cn->InBuf)
      {
       tmpbuf = cn->InBuf->next;
       free(cn->InBuf);
       cn->InBuf = tmpbuf;
      }
 while(cn->OutBuf)
      {
       tmpbuf = cn->OutBuf->next;
       free(cn->OutBuf);
       cn->OutBuf = tmpbuf;
      }
 // clear the memory block
 memset(cn, 0x0, sizeof(TPOS_CN));
 return 1;
}
//---------------------------------------------------------------------------
// Close World Server
//---------------------------------------------------------------------------
int CloseWorldServer(void)
{ 
	int	 i; 
	
	LOCK_CONNECTION(0);
	for(i=0; i<MAX_PLAYER_PER_WORLD; i++)
    {
		if(!Pos_Cn[i].dwSocket) continue;
		CloseOneConnection(&Pos_Cn[i]);
    }
	if(Pos_Cn) {free(Pos_Cn); Pos_Cn = NULL;}
	UNLOCK_CONNECTION(0);	
	
	CloseOneConnection(World);
	if(World) {free(World); World = NULL;}		
	
	DestroyWindow(WorldSockethWnd);
	UnregisterClass(WorldClassName, wInstance); 
	
	return DLL_OK;
}
//---------------------------------------------------------------------------
// Close Door Server
//---------------------------------------------------------------------------
int CloseDoorServer(void)
{ 
	shutdown(Door->dwSocket,SD_BOTH);
	CloseOneConnection(Door);
	free(Door);	
	DestroyWindow(DoorSockethWnd);
	UnregisterClass(DoorClassName, dInstance); 
	return DLL_OK;
}
//---------------------------------------------------------------------------
