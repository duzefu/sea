@echo on
@echo --------------------Jack Added: Make Library and Include-------------------
@echo Copying library files to seaage library directory...
@echo off
@if exist Release\ComLib.lib copy Release\ComLib.lib   ..\POS_LIB > nul
@if exist Debug\ComLibDbg.lib copy Debug\ComLibDbg.lib  ..\POS_LIB > nul
@echo Copying header files to seaage include directory...
@echo off
@copy NetGE_*.h     ..\POS_INCLUDE > nul
@echo on
