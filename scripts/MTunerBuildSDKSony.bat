@echo off

set PLATFORM=orbis
IF "%1"=="orbis"      set PLATFORM=orbis
IF "%1"=="prospero"   set PLATFORM=prospero
IF "%1"=="ps4"        set PLATFORM=orbis
IF "%1"=="ps5"        set PLATFORM=prospero

set PLATFORM_SHORT=ps4
IF "%1"=="orbis"      set PLATFORM_SHORT=ps4
IF "%1"=="prospero"   set PLATFORM_SHORT=ps5
IF "%1"=="ps4"        set PLATFORM_SHORT=ps4
IF "%1"=="ps5"        set PLATFORM_SHORT=ps5

echo Generating makefiles for %PLATFORM_SHORT%
..\build\tools\bin\windows\genie.exe --file=..\src\libs\rmem\genie\genie.lua --gcc=%PLATFORM% gmake
cd ..\.build\%PLATFORM%\%PLATFORM%-clang\rmem\projects\
make -R config=debug64 rmem
make -R config=release64 rmem
cd ..\..\..\..\..\scripts
mkdir SDK\inc
mkdir SDK\lib\%PLATFORM_SHORT%
copy ..\src\libs\rmem\inc\*.* SDK\inc
copy ..\.build\%PLATFORM%\%PLATFORM%-clang\rmem\x64\debug\lib\librmem_debug.a SDK\lib\%PLATFORM_SHORT%\librmem_debug.a
copy ..\.build\%PLATFORM%\%PLATFORM%-clang\rmem\x64\release\lib\librmem_release.a SDK\lib\%PLATFORM_SHORT%\librmem_release.a

