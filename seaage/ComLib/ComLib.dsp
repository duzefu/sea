# Microsoft Developer Studio Project File - Name="ComLib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=ComLib - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ComLib.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ComLib.mak" CFG="ComLib - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ComLib - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "ComLib - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ComLib - Win32 Release"

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
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "ComLib - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ  /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ  /c
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "ComLib - Win32 Release"
# Name "ComLib - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Dummy.cpp
# End Source File
# Begin Source File

SOURCE=.\NetGE_Account.cpp
# End Source File
# Begin Source File

SOURCE=.\NetGE_AI.cpp
# End Source File
# Begin Source File

SOURCE=.\NetGE_Bank.cpp
# End Source File
# Begin Source File

SOURCE=.\NetGE_Character.cpp
# End Source File
# Begin Source File

SOURCE=.\NetGE_Common.cpp
# End Source File
# Begin Source File

SOURCE=.\NetGE_DBFunc.cpp
# End Source File
# Begin Source File

SOURCE=.\NetGE_Doing.cpp
# End Source File
# Begin Source File

SOURCE=.\NetGE_Fight.cpp
# End Source File
# Begin Source File

SOURCE=.\NetGE_Global.cpp
# End Source File
# Begin Source File

SOURCE=.\NetGE_House.cpp
# End Source File
# Begin Source File

SOURCE=.\NetGE_Item.cpp
# End Source File
# Begin Source File

SOURCE=.\NetGE_Magic.cpp
# End Source File
# Begin Source File

SOURCE=.\NetGE_MAGIC_mindoingKind.cpp
# End Source File
# Begin Source File

SOURCE=.\NetGE_MagicBreak.cpp
# End Source File
# Begin Source File

SOURCE=.\NetGE_MapMask.cpp
# End Source File
# Begin Source File

SOURCE=.\NetGE_MapProc.cpp
# End Source File
# Begin Source File

SOURCE=.\NetGE_Message.cpp
# End Source File
# Begin Source File

SOURCE=.\NetGE_MFSystem.cpp
# End Source File
# Begin Source File

SOURCE=.\NetGE_Misc.cpp
# End Source File
# Begin Source File

SOURCE=.\NetGE_NPC_mindoingKind.cpp
# End Source File
# Begin Source File

SOURCE=.\NetGE_ODBC.cpp
# End Source File
# Begin Source File

SOURCE=.\NetGE_Port.cpp
# End Source File
# Begin Source File

SOURCE=.\NetGE_QQ.cpp
# End Source File
# Begin Source File

SOURCE=.\NetGE_Script.cpp
# End Source File
# Begin Source File

SOURCE=.\NetGE_Ship.cpp
# End Source File
# Begin Source File

SOURCE=.\NetGE_Skill.cpp
# End Source File
# Begin Source File

SOURCE=.\NetGE_SkillProc.cpp
# End Source File
# Begin Source File

SOURCE=.\NetGE_Store.cpp
# End Source File
# Begin Source File

SOURCE=.\NetGE_Treasury.cpp
# End Source File
# Begin Source File

SOURCE=.\NetGE_Utility.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\NetGE.h
# End Source File
# Begin Source File

SOURCE=.\NetGE_Account.h
# End Source File
# Begin Source File

SOURCE=.\NetGE_AI.h
# End Source File
# Begin Source File

SOURCE=.\NetGE_Bank.h
# End Source File
# Begin Source File

SOURCE=.\NetGE_Character.h
# End Source File
# Begin Source File

SOURCE=.\NetGE_Common.h
# End Source File
# Begin Source File

SOURCE=.\NetGE_DBFunc.h
# End Source File
# Begin Source File

SOURCE=.\NetGE_Doing.h
# End Source File
# Begin Source File

SOURCE=.\NetGE_Fight.h
# End Source File
# Begin Source File

SOURCE=.\NetGE_Global.h
# End Source File
# Begin Source File

SOURCE=.\NetGE_House.h
# End Source File
# Begin Source File

SOURCE=.\NetGE_Image.h
# End Source File
# Begin Source File

SOURCE=.\NetGE_Item.h
# End Source File
# Begin Source File

SOURCE=.\NetGE_Magic.h
# End Source File
# Begin Source File

SOURCE=.\NetGE_MAGIC_mindoingKind.h
# End Source File
# Begin Source File

SOURCE=.\NetGE_MagicBreak.h
# End Source File
# Begin Source File

SOURCE=.\NetGE_Mainfunc.h
# End Source File
# Begin Source File

SOURCE=.\NetGE_MapMask.h
# End Source File
# Begin Source File

SOURCE=.\NetGE_MapProc.h
# End Source File
# Begin Source File

SOURCE=.\NetGE_Message.h
# End Source File
# Begin Source File

SOURCE=.\NetGE_MFSystem.h
# End Source File
# Begin Source File

SOURCE=.\NetGE_Misc.h
# End Source File
# Begin Source File

SOURCE=.\NetGE_NPC_mindoingKind.h
# End Source File
# Begin Source File

SOURCE=.\NetGE_ODBC.h
# End Source File
# Begin Source File

SOURCE=.\NetGE_Port.h
# End Source File
# Begin Source File

SOURCE=.\NetGE_QQ.h
# End Source File
# Begin Source File

SOURCE=.\NetGE_Script.h
# End Source File
# Begin Source File

SOURCE=.\NetGE_Ship.h
# End Source File
# Begin Source File

SOURCE=.\NetGE_Skill.h
# End Source File
# Begin Source File

SOURCE=.\NetGE_SkillProc.h
# End Source File
# Begin Source File

SOURCE=.\NetGE_Store.h
# End Source File
# Begin Source File

SOURCE=.\NetGE_Treasury.h
# End Source File
# Begin Source File

SOURCE=.\NetGE_Utility.h
# End Source File
# End Group
# End Target
# End Project
