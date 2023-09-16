@echo off
copy "%~dp0..\src\buildversion.h" "%~dp0..\src\version.h" 
fart.exe" "%~dp0..\src\version.h" ##BUILD_VERSION## 4.6
copy MTunerPreVersion.swx MTuner.swx 
fart.exe" MTuner.swx ##BUILD_VERSION## 4.6
fart.exe" MTuner.swx 1.0.0 1.0.0
