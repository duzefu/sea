@echo on
@echo --------------------Jack Added: Copy exe files -------------------
@echo Copying exe files to seaage bin directory...
@echo off
@if exist Release\CreateDB.exe copy Release\CreateDB.exe   ..\Bin\Tools > nul
@if exist Debug\CreateDBdbg.exe copy Debug\CreateDBdbg.exe  ..\Bin\Tools > nul
@echo on
