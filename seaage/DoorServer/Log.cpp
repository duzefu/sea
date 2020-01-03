//-------------------------------------------------------------------------------
// Psalm of Sea DoorServer Log
// By Hawke Hsieh
// 2002-10-7
//-------------------------------------------------------------------------------

#include "DoorServer_Def.h"

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
 
 sprintf(filename,"door_state.txt");
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
// Save Connected Counter
//-------------------------------------------------------------------------------
void SaveConnectedCounter(DWORD index)
{
 FILE		*f;
 char		str[20];
 char       filename[100];

 memset(str, 0x0, 20);
 memset(filename, 0x0, 100);
 sprintf(filename,"login_counter.txt");
 wsprintf(str, "%d", dwConnectedCounter); 
 f = fopen(filename, "wb");
 fputs(str, f);
 fclose(f);
}
//-------------------------------------------------------------------------------
// Load Connected Counter
//-------------------------------------------------------------------------------
void LoadConnectedCounter(void)
{
 FILE		*f;
 char		str[20];
 char       filename[100];

 memset(str, 0x0, 20);
 memset(filename, 0x0, 100);
 sprintf(filename,"login_counter.txt");
 if(is_file_exist((USTR*)filename))
 {
  f = fopen(filename, "rb");
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
//-------------------------------------------------------------------------------
