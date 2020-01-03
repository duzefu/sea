//---------------------------------------------------------------------------
// Psalm of Sea ZoneServer Close Socket
// By Hawke Hsieh 
// 2002-10-07
//---------------------------------------------------------------------------

#include "ZoneServer_Def.h"

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
// Close Zone Server
//---------------------------------------------------------------------------
int CloseZoneServer(void)
{
 int	 i; 

 LOCK_CONNECTION(0);
 for(i=0; i<MAX_PLAYER_PER_ZONE; i++)
    {
     if(!Pos_Cn[i].dwSocket) continue;
     CloseOneConnection(&Pos_Cn[i]);
    }
 if(Pos_Cn) {free(Pos_Cn); Pos_Cn = NULL;}
 UNLOCK_CONNECTION(0);

 LOCK_SYNCCONNECTION(0);
 for(i=0; i<MAX_PLAYER_PER_ZONE; i++)
    {
     if(!Pos_Cn_Sync[i].dwSocket) continue;
     CloseOneConnection(&Pos_Cn_Sync[i]);
    }
 if(Pos_Cn_Sync) {free(Pos_Cn_Sync); Pos_Cn_Sync = NULL;}
 UNLOCK_SYNCCONNECTION(0);

 CloseOneConnection(Zone);
 if(Zone) {free(Zone); Zone = NULL;}

 CloseOneConnection(ZoneSync);
 if(ZoneSync) {free(ZoneSync); ZoneSync = NULL;} 

 return DLL_OK;
}
//---------------------------------------------------------------------------
// Close Zone SYNC Server
//---------------------------------------------------------------------------
int CloseZoneSyncServer(void)
{
 int	 i; 
 CloseOneConnection(ZoneSync); 
 free(ZoneSync);
 for(i=0; i<MAX_PLAYER_PER_ZONE; i++)
    {
     if(!Pos_Cn_Sync[i].dwSocket) continue;     
     CloseOneConnection(&Pos_Cn_Sync[i]);
    } 
 free(Pos_Cn_Sync); 

 return DLL_OK;
}
//---------------------------------------------------------------------------
// Close World Server
//---------------------------------------------------------------------------
int CloseWorldServer(void)
{ 
	shutdown(World->dwSocket,SD_BOTH);
	CloseOneConnection(World);
	free(World);	
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
	return DLL_OK;
}
//---------------------------------------------------------------------------
