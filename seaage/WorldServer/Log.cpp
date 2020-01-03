//-------------------------------------------------------------------------------
// Psalm of Sea WorldServer Log
// By Hawke Hsieh
// 2002-10-7
//-------------------------------------------------------------------------------

#include "WorldServer_Def.h"

//-------------------------------------------------------------------------------
// Save Message To Log File
//-------------------------------------------------------------------------------
void SaveMsgToLog(char *from, char *msg)
{
 FILE	*f;  
 char   str[256];
 char   *timeline;
 char   filename[100];
 
 memset(filename, 0x0, 100);
 memset(str, 0x0, 256); 

 _ftime( &timebuffer );
 timeline = ctime( & ( timebuffer.time ) );
 timeline[24]=0x00;  //&timeline[20] = "2002\0x0d\0x00"; 
 
 sprintf(filename,"world_state.txt");
 f = fopen(filename, "a+"); 
 fprintf(f,"[%.19s.%03hu %s] %s : %s\n",
	       timeline,
		   timebuffer.millitm,
		   &timeline[20],
		   from,msg);
 fclose(f);
 
}
//-------------------------------------------------------------------------------
// Save Work To Log File
//-------------------------------------------------------------------------------
void SaveWorkToLog(char *who,char *ip,char *work)
{
 char   str[256]; 
 memset(str, 0x0, 256); 

 sprintf(str,"[ %s ][ %s ][ %s ]",work,who,ip);
 SaveMsgToLog("USER  ",str);
}
//-------------------------------------------------------------------------------
// Save QQ ID Counter
//-------------------------------------------------------------------------------
void SaveQQIDCounter(DWORD index)
{
	FILE		*f;
	char		str[256];
	char       filename[100];
	
	memset(str, 0x0, 20);
	memset(filename, 0x0, 100);
	sprintf(filename,"qqid_counter.txt");
	wsprintf(str, "%d", dwQQIDCounter); 
	f = fopen(filename, "wb");
	fputs(str, f);
	fclose(f);
}
//-------------------------------------------------------------------------------
// Load QQID Counter
//-------------------------------------------------------------------------------
void LoadQQIDCounter(void)
{
	FILE		*f;
	char		str[256];
	char       filename[100];
	
	memset(filename, 0x0, 100);
	sprintf(filename,"qqid_counter.txt");
	if(NULL != (f = fopen(filename, "rb")))
	{
		memset(str, 0x0, 20);
		fgets(str, 20, f);
		fclose(f);
		dwQQIDCounter = atoi(str); 
	}
	else
	{
		dwQQIDCounter = 0;
	}
}
//-------------------------------------------------------------------------------
// Save Connected Counter
//-------------------------------------------------------------------------------
void SaveConnectedCounter(DWORD index)
{
	FILE		*f;
	char		str[256];
	char       filename[100];
	
	memset(str, 0x0, 20);
	memset(filename, 0x0, 100);
	sprintf(filename,"login_counter.txt");
	wsprintf(str, "%d", dwConnectedCounter); 
	if(NULL != (f = fopen(filename, "wb")))
	{
		fputs(str, f);
		fclose(f);
	}
}
//-------------------------------------------------------------------------------
// Load Connected Counter
//-------------------------------------------------------------------------------
void LoadConnectedCounter(void)
{
	FILE		*f;
	char		str[256];
	char       filename[100];
	
	memset(filename, 0x0, 100);
	sprintf(filename,"login_counter.txt");
	if(NULL != (f = fopen(filename, "rb")))
	{
		memset(str, 0x0, 20);
		fgets(str, 20, f);
		fclose(f);
		dwConnectedCounter = atoi(str);
	}
	else
	{
		SaveConnectedCounter(0);
	} 
}
//-------------------------------------------------------------------------------
// Save I/O to Log
//-------------------------------------------------------------------------------
void SaveIOToLog(char *ip,char *io)
{
	char   str[256]; 
	
	memset(str, 0x0, 256); 
	sprintf(str,"%s -> %s",ip,io);
	SaveMsgToLog("I/O   ",str);
}
//
void LoadMaxLoginer(void)
{
	FILE		*f;
	char		str[256];
	
	if(NULL != (f = fopen("login_maxloginer.txt", "rb")))
	{
		memset(str, 0x0, 20);
		fgets(str, 20, f);
		fclose(f);
		dwOnlineMaxLoginer = atoi(str); 
	}
	else
	{
		dwOnlineMaxLoginer = 0;
	}
}
//-------------------------------------------------------------------------------
void LoadMaxPlayer(void)
{
	FILE		*f;
	char		str[256];
	
	if(NULL != (f = fopen("login_maxplayer.txt", "rb")))
	{
		memset(str, 0x0, 20);
		fgets(str, 20, f);
		fclose(f);
		dwOnlineAllWorldMaxPlayer = atoi(str); 
	}
	else
	{
		dwOnlineAllWorldMaxPlayer = 0; 
	}
}
//-------------------------------------------------------------------------------
// Save All World Max Player
//---------------------------------------------------------------------------
void SaveMaxPlayer(void)
{
	FILE		*f;
	char		str[256];
	
	if(NULL != (f = fopen("login_maxplayer.txt", "wb")))
	{
		memset(str, 0x0, 20);
		wsprintf(str, "%d", dwOnlineAllWorldMaxPlayer);
		fputs(str, f);
		fclose(f);
	}
}
//---------------------------------------------------------------------------
// Save Max Loginer
//---------------------------------------------------------------------------
void SaveMaxLoginer(void)
{
	FILE		*f;
	char		str[256];
	
	if(NULL != (f = fopen("login_maxloginer.txt", "wb")))
	{
		memset(str, 0x0, 20);
		wsprintf(str, "%d", dwOnlineMaxLoginer); 
		fputs(str, f);
		fclose(f);
	}
}
//---------------------------------------------------------------------------