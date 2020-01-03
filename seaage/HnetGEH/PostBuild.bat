@echo on
@echo --------------------Jack Added: Make Dll and Include-------------------
@echo Copying dll files to seaage dll directory...
@echo off
@if exist Release\HNetGEH.dll copy Release\HNetGEH.dll   ..\POS_DLL > nul
@if exist Debug\HNetGEHdbg.dll copy Debug\HNetGEHdbg.dll  ..\POS_DLL > nul
@echo Copying lib files to seaage lib directory...
@echo off
@if exist Release\HNetGEH.lib copy Release\HNetGEH.lib   ..\POS_LIB > nul
@if exist Release\HNetGEH.exp copy Release\HNetGEH.exp   ..\POS_LIB > nul
@if exist Debug\HNetGEHdbg.lib copy Debug\HNetGEHdbg.lib   ..\POS_LIB > nul
@if exist Debug\HNetGEHdbg.exp copy Debug\HNetGEHdbg.exp   ..\POS_LIB > nul
@if exist Debug\HNetGEHdbg.ilk copy Debug\HNetGEHdbg.ilk   ..\POS_LIB > nul
@echo on
