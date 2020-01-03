# Microsoft Developer Studio Project File - Name="SeaAge" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=SeaAge - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "SeaAge.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "SeaAge.mak" CFG="SeaAge - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SeaAge - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "SeaAge - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "SeaAge - Win32 Release"

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

!ELSEIF  "$(CFG)" == "SeaAge - Win32 Debug"

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
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_WIN32" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "SeaAge - Win32 Release"
# Name "SeaAge - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AccountDetails.cpp
# End Source File
# Begin Source File

SOURCE=.\CChat.cpp
# End Source File
# Begin Source File

SOURCE=.\CHear.cpp
# End Source File
# Begin Source File

SOURCE=.\Client_Item.cpp
# End Source File
# Begin Source File

SOURCE=.\Client_RecvMsg.cpp
# End Source File
# Begin Source File

SOURCE=.\Client_SendMsg.cpp
# End Source File
# Begin Source File

SOURCE=.\Client_Thread.cpp
# End Source File
# Begin Source File

SOURCE=.\ClientMain.cpp
# End Source File
# Begin Source File

SOURCE=.\CmdEvent.cpp
# End Source File
# Begin Source File

SOURCE=.\Config.cpp
# End Source File
# Begin Source File

SOURCE=.\CRange.cpp
# End Source File
# Begin Source File

SOURCE=.\DoingClient.cpp
# End Source File
# Begin Source File

SOURCE=.\DoingSeaClient.cpp
# End Source File
# Begin Source File

SOURCE=.\Dummy.cpp
# End Source File
# Begin Source File

SOURCE=.\ErrorMsg.cpp
# End Source File
# Begin Source File

SOURCE=.\Fight.cpp
# End Source File
# Begin Source File

SOURCE=.\FightClient.cpp
# End Source File
# Begin Source File

SOURCE=.\FreeProcess.cpp
# End Source File
# Begin Source File

SOURCE=.\GM_Main.cpp
# End Source File
# Begin Source File

SOURCE=.\House.cpp
# End Source File
# Begin Source File

SOURCE=.\HouseSet.cpp
# End Source File
# Begin Source File

SOURCE=.\HrtBeat.cpp
# End Source File
# Begin Source File

SOURCE=.\ImageRim.cpp
# End Source File
# Begin Source File

SOURCE=.\LineDlink.cpp
# End Source File
# Begin Source File

SOURCE=.\Magic.cpp
# End Source File
# Begin Source File

SOURCE=.\MagicClient.cpp
# End Source File
# Begin Source File

SOURCE=.\MagicHit.cpp
# End Source File
# Begin Source File

SOURCE=.\MainGame.cpp
# End Source File
# Begin Source File

SOURCE=.\Map.cpp
# End Source File
# Begin Source File

SOURCE=.\MapBlock.cpp
# End Source File
# Begin Source File

SOURCE=.\MapHouse.cpp
# End Source File
# Begin Source File

SOURCE=.\MapLight.cpp
# End Source File
# Begin Source File

SOURCE=.\MapObject.cpp
# End Source File
# Begin Source File

SOURCE=.\MapTile.cpp
# End Source File
# Begin Source File

SOURCE=.\MapTrack.cpp
# End Source File
# Begin Source File

SOURCE=.\MapUpper.cpp
# End Source File
# Begin Source File

SOURCE=.\MapUtility.cpp
# End Source File
# Begin Source File

SOURCE=.\Media.cpp
# End Source File
# Begin Source File

SOURCE=.\MouseHand.cpp
# End Source File
# Begin Source File

SOURCE=.\Npc.cpp
# End Source File
# Begin Source File

SOURCE=.\npc_state.cpp
# End Source File
# Begin Source File

SOURCE=.\Parse.cpp
# End Source File
# Begin Source File

SOURCE=.\Player.cpp
# End Source File
# Begin Source File

SOURCE=.\PosData.cpp
# End Source File
# Begin Source File

SOURCE=.\qq.cpp
# End Source File
# Begin Source File

SOURCE=.\qqchat.cpp
# End Source File
# Begin Source File

SOURCE=.\qqclient.cpp
# End Source File
# Begin Source File

SOURCE=.\qqedit.cpp
# End Source File
# Begin Source File

SOURCE=.\qqfriend.cpp
# End Source File
# Begin Source File

SOURCE=.\qqhis.cpp
# End Source File
# Begin Source File

SOURCE=.\qqlocal.cpp
# End Source File
# Begin Source File

SOURCE=.\qqlog.cpp
# End Source File
# Begin Source File

SOURCE=.\qqmsgbox.cpp
# End Source File
# Begin Source File

SOURCE=.\qqsearch.cpp
# End Source File
# Begin Source File

SOURCE=.\SeaAge.rc
# End Source File
# Begin Source File

SOURCE=.\SeaNpc.cpp
# End Source File
# Begin Source File

SOURCE=.\SecretSkill.cpp
# End Source File
# Begin Source File

SOURCE=.\SGE.cpp
# End Source File
# Begin Source File

SOURCE=.\SingleGame.cpp
# End Source File
# Begin Source File

SOURCE=.\SwapScr.cpp
# End Source File
# Begin Source File

SOURCE=.\Team.cpp
# End Source File
# Begin Source File

SOURCE=.\TileField.cpp
# End Source File
# Begin Source File

SOURCE=.\TileImage.cpp
# End Source File
# Begin Source File

SOURCE=.\TileSet.cpp
# End Source File
# Begin Source File

SOURCE=.\UI.cpp
# End Source File
# Begin Source File

SOURCE=.\UIAccMan.cpp
# End Source File
# Begin Source File

SOURCE=.\UIComboBox.cpp
# End Source File
# Begin Source File

SOURCE=.\UIGameChoice.cpp
# End Source File
# Begin Source File

SOURCE=.\UIGameMessage.cpp
# End Source File
# Begin Source File

SOURCE=.\UIGameTalk.cpp
# End Source File
# Begin Source File

SOURCE=.\UIIconMessage.cpp
# End Source File
# Begin Source File

SOURCE=.\UIInfobar.cpp
# End Source File
# Begin Source File

SOURCE=.\UIInput.cpp
# End Source File
# Begin Source File

SOURCE=.\UILoading.cpp
# End Source File
# Begin Source File

SOURCE=.\UIMagicArea.cpp
# End Source File
# Begin Source File

SOURCE=.\UIMagicIcon.cpp
# End Source File
# Begin Source File

SOURCE=.\UIManager.cpp
# End Source File
# Begin Source File

SOURCE=.\UIManface.cpp
# End Source File
# Begin Source File

SOURCE=.\UIMap.cpp
# End Source File
# Begin Source File

SOURCE=.\UIMapChat.cpp
# End Source File
# Begin Source File

SOURCE=.\UIMapItem.cpp
# End Source File
# Begin Source File

SOURCE=.\UIMapQuickMagic.cpp
# End Source File
# Begin Source File

SOURCE=.\UIMapShip.cpp
# End Source File
# Begin Source File

SOURCE=.\UIMapSkill.cpp
# End Source File
# Begin Source File

SOURCE=.\UIMapState.cpp
# End Source File
# Begin Source File

SOURCE=.\UIMapTask.cpp
# End Source File
# Begin Source File

SOURCE=.\UIPosIME.cpp
# End Source File
# Begin Source File

SOURCE=.\UIQuitGame.cpp
# End Source File
# Begin Source File

SOURCE=.\UIRebuildCabin.cpp
# End Source File
# Begin Source File

SOURCE=.\UIShop.cpp
# End Source File
# Begin Source File

SOURCE=.\UIShowMap.cpp
# End Source File
# Begin Source File

SOURCE=.\UIStore.cpp
# End Source File
# Begin Source File

SOURCE=.\UISystemMessage.cpp
# End Source File
# Begin Source File

SOURCE=.\Weather.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AccountDetails.h
# End Source File
# Begin Source File

SOURCE=.\CChat.h
# End Source File
# Begin Source File

SOURCE=.\CHear.h
# End Source File
# Begin Source File

SOURCE=.\Client_Event.h
# End Source File
# Begin Source File

SOURCE=.\Client_Item.h
# End Source File
# Begin Source File

SOURCE=.\Client_RecvMsg.h
# End Source File
# Begin Source File

SOURCE=.\Client_SendMsg.h
# End Source File
# Begin Source File

SOURCE=.\Client_Thread.h
# End Source File
# Begin Source File

SOURCE=.\ClientMain.h
# End Source File
# Begin Source File

SOURCE=.\CmdEvent.h
# End Source File
# Begin Source File

SOURCE=.\Config.h
# End Source File
# Begin Source File

SOURCE=.\CRange.h
# End Source File
# Begin Source File

SOURCE=.\DoingClient.h
# End Source File
# Begin Source File

SOURCE=.\DoingSeaClient.h
# End Source File
# Begin Source File

SOURCE=.\ErrorMsg.h
# End Source File
# Begin Source File

SOURCE=.\Fight.h
# End Source File
# Begin Source File

SOURCE=.\FightClient.h
# End Source File
# Begin Source File

SOURCE=.\FreeProcess.h
# End Source File
# Begin Source File

SOURCE=.\GM_Main.h
# End Source File
# Begin Source File

SOURCE=.\House.h
# End Source File
# Begin Source File

SOURCE=.\HouseSet.h
# End Source File
# Begin Source File

SOURCE=.\HrtBeat.h
# End Source File
# Begin Source File

SOURCE=.\ImageRim.h
# End Source File
# Begin Source File

SOURCE=.\LineDlink.h
# End Source File
# Begin Source File

SOURCE=.\Magic.h
# End Source File
# Begin Source File

SOURCE=.\MagicClient.h
# End Source File
# Begin Source File

SOURCE=.\MagicHit.h
# End Source File
# Begin Source File

SOURCE=.\mainfun.h
# End Source File
# Begin Source File

SOURCE=.\MainGame.h
# End Source File
# Begin Source File

SOURCE=.\Map.h
# End Source File
# Begin Source File

SOURCE=.\MapBlock.h
# End Source File
# Begin Source File

SOURCE=.\MapHouse.h
# End Source File
# Begin Source File

SOURCE=.\MapLight.h
# End Source File
# Begin Source File

SOURCE=.\MapObject.h
# End Source File
# Begin Source File

SOURCE=.\MapTile.h
# End Source File
# Begin Source File

SOURCE=.\MapTrack.h
# End Source File
# Begin Source File

SOURCE=.\MapUpper.h
# End Source File
# Begin Source File

SOURCE=.\MapUtility.h
# End Source File
# Begin Source File

SOURCE=.\Media.h
# End Source File
# Begin Source File

SOURCE=.\MouseHand.h
# End Source File
# Begin Source File

SOURCE=.\Npc.h
# End Source File
# Begin Source File

SOURCE=.\npc_state.h
# End Source File
# Begin Source File

SOURCE=.\Parse.h
# End Source File
# Begin Source File

SOURCE=.\PosData.h
# End Source File
# Begin Source File

SOURCE=.\qq.h
# End Source File
# Begin Source File

SOURCE=.\qqchat.h
# End Source File
# Begin Source File

SOURCE=.\qqclient.h
# End Source File
# Begin Source File

SOURCE=.\qqconst.h
# End Source File
# Begin Source File

SOURCE=.\qqedit.h
# End Source File
# Begin Source File

SOURCE=.\qqfriend.h
# End Source File
# Begin Source File

SOURCE=.\qqhis.h
# End Source File
# Begin Source File

SOURCE=.\qqlocal.h
# End Source File
# Begin Source File

SOURCE=.\qqlog.h
# End Source File
# Begin Source File

SOURCE=.\qqmain.h
# End Source File
# Begin Source File

SOURCE=.\qqmsg.h
# End Source File
# Begin Source File

SOURCE=.\qqmsgbox.h
# End Source File
# Begin Source File

SOURCE=.\qqsearch.h
# End Source File
# Begin Source File

SOURCE=.\qqstruct.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\SeaNpc.h
# End Source File
# Begin Source File

SOURCE=.\SecretSkill.h
# End Source File
# Begin Source File

SOURCE=.\SGE.h
# End Source File
# Begin Source File

SOURCE=.\SingleGame.h
# End Source File
# Begin Source File

SOURCE=.\SwapScr.h
# End Source File
# Begin Source File

SOURCE=.\Team.h
# End Source File
# Begin Source File

SOURCE=.\TileField.h
# End Source File
# Begin Source File

SOURCE=.\TileImage.h
# End Source File
# Begin Source File

SOURCE=.\TileSet.h
# End Source File
# Begin Source File

SOURCE=.\UI.h
# End Source File
# Begin Source File

SOURCE=.\UIAccMan.h
# End Source File
# Begin Source File

SOURCE=.\UIComboBox.h
# End Source File
# Begin Source File

SOURCE=.\UIGameChoice.h
# End Source File
# Begin Source File

SOURCE=.\UIGameMessage.h
# End Source File
# Begin Source File

SOURCE=.\UIGameTalk.h
# End Source File
# Begin Source File

SOURCE=.\UIIconMessage.h
# End Source File
# Begin Source File

SOURCE=.\UIInfobar.h
# End Source File
# Begin Source File

SOURCE=.\UIInput.h
# End Source File
# Begin Source File

SOURCE=.\UIItemInfo.h
# End Source File
# Begin Source File

SOURCE=.\UILoading.h
# End Source File
# Begin Source File

SOURCE=.\UIMagicArea.h
# End Source File
# Begin Source File

SOURCE=.\UIMagicIcon.h
# End Source File
# Begin Source File

SOURCE=.\UIManager.h
# End Source File
# Begin Source File

SOURCE=.\UIManface.h
# End Source File
# Begin Source File

SOURCE=.\UIMap.h
# End Source File
# Begin Source File

SOURCE=.\UIMapChat.h
# End Source File
# Begin Source File

SOURCE=.\UIMapItem.h
# End Source File
# Begin Source File

SOURCE=.\UIMapQuickMagic.h
# End Source File
# Begin Source File

SOURCE=.\UIMapShip.h
# End Source File
# Begin Source File

SOURCE=.\UIMapSkill.h
# End Source File
# Begin Source File

SOURCE=.\UIMapState.h
# End Source File
# Begin Source File

SOURCE=.\UIMapTask.h
# End Source File
# Begin Source File

SOURCE=.\UIPosIME.h
# End Source File
# Begin Source File

SOURCE=.\UIQuitGame.h
# End Source File
# Begin Source File

SOURCE=.\UIRebuildCabin.h
# End Source File
# Begin Source File

SOURCE=.\UIShop.h
# End Source File
# Begin Source File

SOURCE=.\UIShowMap.h
# End Source File
# Begin Source File

SOURCE=.\UIStore.h
# End Source File
# Begin Source File

SOURCE=.\UISystemMessage.h
# End Source File
# Begin Source File

SOURCE=.\Weather.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\SeaAge.ico
# End Source File
# End Group
# Begin Group "ComLib"

# PROP Default_Filter ""
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
