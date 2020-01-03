# Microsoft Developer Studio Project File - Name="ZoneServer" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=ZoneServer - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ZoneServer.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ZoneServer.mak" CFG="ZoneServer - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ZoneServer - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "ZoneServer - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ZoneServer - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "ZoneServer - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 Ws2_32.lib User32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"LIBCD.lib" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "ZoneServer - Win32 Release"
# Name "ZoneServer - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\CloseSocket.cpp
# End Source File
# Begin Source File

SOURCE=.\HeartBeat.cpp
# End Source File
# Begin Source File

SOURCE=.\InitSocket.cpp
# End Source File
# Begin Source File

SOURCE=.\InitZoneData.cpp
# End Source File
# Begin Source File

SOURCE=.\Log.cpp
# End Source File
# Begin Source File

SOURCE=.\Main.cpp
# End Source File
# Begin Source File

SOURCE=.\ProcessSocket.cpp
# End Source File
# Begin Source File

SOURCE=.\Resource.rc
# End Source File
# Begin Source File

SOURCE=.\SaveDataHeartBeat.cpp
# End Source File
# Begin Source File

SOURCE=.\ServerCharacterDoing.cpp
# End Source File
# Begin Source File

SOURCE=.\ServerDecodeMacro.cpp
# End Source File
# Begin Source File

SOURCE=.\ServerDoingFunction.cpp
# End Source File
# Begin Source File

SOURCE=.\ServerEnemy.cpp
# End Source File
# Begin Source File

SOURCE=.\ServerFight.cpp
# End Source File
# Begin Source File

SOURCE=.\ServerFindGold.cpp
# End Source File
# Begin Source File

SOURCE=.\ServerItem.cpp
# End Source File
# Begin Source File

SOURCE=.\ServerMagic.cpp
# End Source File
# Begin Source File

SOURCE=.\ServerMagicHit.cpp
# End Source File
# Begin Source File

SOURCE=.\ServerQuest.cpp
# End Source File
# Begin Source File

SOURCE=.\ServerRefreshGame.cpp
# End Source File
# Begin Source File

SOURCE=.\ServerTeam.cpp
# End Source File
# Begin Source File

SOURCE=.\ServerWeather.cpp
# End Source File
# Begin Source File

SOURCE=.\SyncHeartBeat.cpp
# End Source File
# Begin Source File

SOURCE=.\SyncPositionHeartBeat.cpp
# End Source File
# Begin Source File

SOURCE=.\SyncSeaPositionHeartBeat.cpp
# End Source File
# Begin Source File

SOURCE=.\ZoneServer_Create.cpp
# End Source File
# Begin Source File

SOURCE=.\ZoneServerMisc.cpp
# End Source File
# Begin Source File

SOURCE=.\ZoneServerShutDown.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\CloseSocket.h
# End Source File
# Begin Source File

SOURCE=.\HeartBeat.h
# End Source File
# Begin Source File

SOURCE=.\InitSocket.h
# End Source File
# Begin Source File

SOURCE=.\InitZoneData.h
# End Source File
# Begin Source File

SOURCE=.\Log.h
# End Source File
# Begin Source File

SOURCE=.\mcdef.h
# End Source File
# Begin Source File

SOURCE=.\Netge_Weather_Def.h
# End Source File
# Begin Source File

SOURCE=.\ProcessSocket.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\SaveDataHeartBeat.h
# End Source File
# Begin Source File

SOURCE=.\ServerCharacterDoing.h
# End Source File
# Begin Source File

SOURCE=.\ServerDecodeMacro.h
# End Source File
# Begin Source File

SOURCE=.\ServerDoingFunction.h
# End Source File
# Begin Source File

SOURCE=.\ServerEnemy.h
# End Source File
# Begin Source File

SOURCE=.\ServerFight.h
# End Source File
# Begin Source File

SOURCE=.\ServerFindGold.h
# End Source File
# Begin Source File

SOURCE=.\ServerItem.h
# End Source File
# Begin Source File

SOURCE=.\ServerMagic.h
# End Source File
# Begin Source File

SOURCE=.\ServerMagicHit.h
# End Source File
# Begin Source File

SOURCE=.\ServerQuest.h
# End Source File
# Begin Source File

SOURCE=.\ServerRefreshGame.h
# End Source File
# Begin Source File

SOURCE=.\ServerTeam.h
# End Source File
# Begin Source File

SOURCE=.\ServerWeather.h
# End Source File
# Begin Source File

SOURCE=.\SyncHeartBeat.h
# End Source File
# Begin Source File

SOURCE=.\SyncPositionHeartbeat.h
# End Source File
# Begin Source File

SOURCE=.\SyncSeaPositionHeartBeat.h
# End Source File
# Begin Source File

SOURCE=.\ZoneServer_Create.h
# End Source File
# Begin Source File

SOURCE=.\ZoneServer_Def.h
# End Source File
# Begin Source File

SOURCE=.\ZoneServer_Ext_Var.h
# End Source File
# Begin Source File

SOURCE=.\ZoneServer_Var.h
# End Source File
# Begin Source File

SOURCE=.\ZoneServerMisc.h
# End Source File
# Begin Source File

SOURCE=.\ZoneServerShutDown.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Group "ComLib"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\ComLib\Dummy.cpp
# End Source File
# Begin Source File

SOURCE=..\ComLib\NetGE.h
# End Source File
# Begin Source File

SOURCE=..\ComLib\NetGE_Account.cpp
# End Source File
# Begin Source File

SOURCE=..\ComLib\NetGE_Account.h
# End Source File
# Begin Source File

SOURCE=..\ComLib\NetGE_AI.cpp
# End Source File
# Begin Source File

SOURCE=..\ComLib\NetGE_AI.h
# End Source File
# Begin Source File

SOURCE=..\ComLib\NetGE_Bank.cpp
# End Source File
# Begin Source File

SOURCE=..\ComLib\NetGE_Bank.h
# End Source File
# Begin Source File

SOURCE=..\ComLib\NetGE_Character.cpp
# End Source File
# Begin Source File

SOURCE=..\ComLib\NetGE_Character.h
# End Source File
# Begin Source File

SOURCE=..\ComLib\NetGE_Common.cpp
# End Source File
# Begin Source File

SOURCE=..\ComLib\NetGE_Common.h
# End Source File
# Begin Source File

SOURCE=..\ComLib\NetGE_DBFunc.cpp
# End Source File
# Begin Source File

SOURCE=..\ComLib\NetGE_DBFunc.h
# End Source File
# Begin Source File

SOURCE=..\ComLib\NetGE_Doing.cpp
# End Source File
# Begin Source File

SOURCE=..\ComLib\NetGE_Doing.h
# End Source File
# Begin Source File

SOURCE=..\ComLib\NetGE_Fight.cpp
# End Source File
# Begin Source File

SOURCE=..\ComLib\NetGE_Fight.h
# End Source File
# Begin Source File

SOURCE=..\ComLib\NetGE_Global.cpp
# End Source File
# Begin Source File

SOURCE=..\ComLib\NetGE_Global.h
# End Source File
# Begin Source File

SOURCE=..\ComLib\NetGE_House.cpp
# End Source File
# Begin Source File

SOURCE=..\ComLib\NetGE_House.h
# End Source File
# Begin Source File

SOURCE=..\ComLib\NetGE_Image.h
# End Source File
# Begin Source File

SOURCE=..\ComLib\NetGE_Item.cpp
# End Source File
# Begin Source File

SOURCE=..\ComLib\NetGE_Item.h
# End Source File
# Begin Source File

SOURCE=..\ComLib\NetGE_Magic.cpp
# End Source File
# Begin Source File

SOURCE=..\ComLib\NetGE_Magic.h
# End Source File
# Begin Source File

SOURCE=..\ComLib\NetGE_MAGIC_mindoingKind.cpp
# End Source File
# Begin Source File

SOURCE=..\ComLib\NetGE_MAGIC_mindoingKind.h
# End Source File
# Begin Source File

SOURCE=..\ComLib\NetGE_MagicBreak.cpp
# End Source File
# Begin Source File

SOURCE=..\ComLib\NetGE_MagicBreak.h
# End Source File
# Begin Source File

SOURCE=..\ComLib\NetGE_Mainfunc.h
# End Source File
# Begin Source File

SOURCE=..\ComLib\NetGE_MapMask.cpp
# End Source File
# Begin Source File

SOURCE=..\ComLib\NetGE_MapMask.h
# End Source File
# Begin Source File

SOURCE=..\ComLib\NetGE_MapProc.cpp
# End Source File
# Begin Source File

SOURCE=..\ComLib\NetGE_MapProc.h
# End Source File
# Begin Source File

SOURCE=..\ComLib\NetGE_Message.cpp
# End Source File
# Begin Source File

SOURCE=..\ComLib\NetGE_Message.h
# End Source File
# Begin Source File

SOURCE=..\ComLib\NetGE_MFSystem.cpp
# End Source File
# Begin Source File

SOURCE=..\ComLib\NetGE_MFSystem.h
# End Source File
# Begin Source File

SOURCE=..\ComLib\NetGE_Misc.cpp
# End Source File
# Begin Source File

SOURCE=..\ComLib\NetGE_Misc.h
# End Source File
# Begin Source File

SOURCE=..\ComLib\NetGE_NPC_mindoingKind.cpp
# End Source File
# Begin Source File

SOURCE=..\ComLib\NetGE_NPC_mindoingKind.h
# End Source File
# Begin Source File

SOURCE=..\ComLib\NetGE_ODBC.cpp
# End Source File
# Begin Source File

SOURCE=..\ComLib\NetGE_ODBC.h
# End Source File
# Begin Source File

SOURCE=..\ComLib\NetGE_Port.cpp
# End Source File
# Begin Source File

SOURCE=..\ComLib\NetGE_Port.h
# End Source File
# Begin Source File

SOURCE=..\ComLib\NetGE_QQ.cpp
# End Source File
# Begin Source File

SOURCE=..\ComLib\NetGE_QQ.h
# End Source File
# Begin Source File

SOURCE=..\ComLib\NetGE_Script.cpp
# End Source File
# Begin Source File

SOURCE=..\ComLib\NetGE_Script.h
# End Source File
# Begin Source File

SOURCE=..\ComLib\NetGE_Ship.cpp
# End Source File
# Begin Source File

SOURCE=..\ComLib\NetGE_Ship.h
# End Source File
# Begin Source File

SOURCE=..\ComLib\NetGE_Skill.cpp
# End Source File
# Begin Source File

SOURCE=..\ComLib\NetGE_Skill.h
# End Source File
# Begin Source File

SOURCE=..\ComLib\NetGE_SkillProc.cpp
# End Source File
# Begin Source File

SOURCE=..\ComLib\NetGE_SkillProc.h
# End Source File
# Begin Source File

SOURCE=..\ComLib\NetGE_Store.cpp
# End Source File
# Begin Source File

SOURCE=..\ComLib\NetGE_Store.h
# End Source File
# Begin Source File

SOURCE=..\ComLib\NetGE_Treasury.cpp
# End Source File
# Begin Source File

SOURCE=..\ComLib\NetGE_Treasury.h
# End Source File
# Begin Source File

SOURCE=..\ComLib\NetGE_Utility.cpp
# End Source File
# Begin Source File

SOURCE=..\ComLib\NetGE_Utility.h
# End Source File
# End Group
# End Target
# End Project
