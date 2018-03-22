@echo off
copy "%~dp0..\src\buildversion.h" "%~dp0..\src\version.h" 
"../../../../../Tools/Fart/fart.exe" "%~dp0..\src\version.h" ##BUILD_VERSION## 4.1.0
copy MTunerPreVersion.swx MTuner.swx 
"../../../../../Tools/Fart/fart.exe" MTuner.swx ##BUILD_VERSION## 4.1.0
"../../../../../Tools/Fart/fart.exe" MTuner.swx 1.0.0 1.0.0
