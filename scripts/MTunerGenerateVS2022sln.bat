@echo off
echo Generating solution and project files for Visual Studio 2022
..\build\tools\bin\windows\genie.exe --file=..\src\MTuner\genie\genie.lua vs2022
