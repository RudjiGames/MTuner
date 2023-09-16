@echo off
echo Packing MTuner

mkdir MTuner
cd    MTuner
mkdir platforms
mkdir translation
mkdir SDK

copy ..\..\.build\windows\vs2022\MTuner\x64\retail\bin\MTuner_retail.exe        MTuner.exe

copy ..\..\.build\windows\vs2022\MTuner\x64\retail\bin\Qt6Core.dll              Qt6Core.dll
copy ..\..\.build\windows\vs2022\MTuner\x64\retail\bin\Qt6Gui.dll               Qt6Gui.dll
copy ..\..\.build\windows\vs2022\MTuner\x64\retail\bin\Qt6Widgets.dll           Qt6Widgets.dll
copy ..\..\.build\windows\vs2022\MTuner\x64\retail\bin\MTunerCmd_retail.exe     MTuner.com

copy ..\..\3rd\DIA\bin\x64\dbghelp.dll                                          dbghelp.dll
copy ..\..\3rd\DIA\bin\x64\SymbolCheck.dll                                      SymbolCheck.dll
copy ..\..\3rd\DIA\bin\x64\symchk.exe                                           symchk.exe
copy ..\..\3rd\DIA\bin\x64\symsrv.dll                                           symsrv.dll
copy ..\..\3rd\DIA\bin\x64\msdia140.dll                                         msdia140.dll

copy ..\..\.build\windows\vs2022\MTuner\x32\retail\bin\MTunerInject_retail.exe  MTunerInject32.exe
copy ..\..\.build\windows\vs2022\MTuner\x64\retail\bin\MTunerInject_retail.exe  MTunerInject64.exe

copy ..\..\.build\windows\vs2022\MTuner\x32\retail\bin\MTunerDLL_retail.dll     MTunerDLL32.dll
copy ..\..\.build\windows\vs2022\MTuner\x64\retail\bin\MTunerDLL_retail.dll     MTunerDLL64.dll

copy ..\..\.build\windows\vs2022\MTuner\x64\retail\bin\platforms\qwindows.dll   platforms\qwindows.dll
copy ..\..\.build\windows\vs2022\MTuner\x64\retail\bin\platforms\qminimal.dll   platforms\qminimal.dll

copy ..\..\src\MTuner\src\mtuner_en.qm translation\MTuner_en.qm
copy ..\..\src\MTuner\src\mtuner_rs.qm translation\MTuner_rs.qm					
copy ..\..\src\MTuner\src\mtuner_de.qm translation\MTuner_de.qm
copy ..\..\src\MTuner\src\mtuner_it.qm translation\MTuner_it.qm

cd SDK
mkdir inc
mkdir src
mkdir genie
mkdir samples
mkdir 3rd
cd ..

copy ..\..\src\libs\rmem\inc\rmem.h						SDK\inc\rmem.h
copy ..\..\src\libs\rmem\inc\rmem_entry.h				SDK\inc\rmem_entry.h

copy ..\..\src\libs\rmem\inc\rmem.h						SDK\inc\rmem.h
copy ..\..\src\libs\rmem\inc\rmem_entry.h				SDK\inc\rmem_entry.h

copy ..\..\src\libs\rmem\src\rmem_config.h				SDK\src\rmem_config.h
copy ..\..\src\libs\rmem\src\rmem_enums.h				SDK\src\rmem_enums.h 
copy ..\..\src\libs\rmem\src\rmem_get_module_info.cpp	SDK\src\rmem_get_module_info.cpp
copy ..\..\src\libs\rmem\src\rmem_hook.cpp				SDK\src\rmem_hook.cpp
copy ..\..\src\libs\rmem\src\rmem_hook.h				SDK\src\rmem_hook.h
copy ..\..\src\libs\rmem\src\rmem_lib.cpp				SDK\src\rmem_lib.cpp
copy ..\..\src\libs\rmem\src\rmem_mutex.h				SDK\src\rmem_mutex.h
copy ..\..\src\libs\rmem\src\rmem_platform.h			SDK\src\rmem_platform.h
copy ..\..\src\libs\rmem\src\rmem_utils.h				SDK\src\rmem_utils.h
copy ..\..\src\libs\rmem\src\rmem_wrap_win.cpp			SDK\src\rmem_wrap_win.cpp
copy ..\..\src\libs\rmem\src\rmem_wrap_win.h			SDK\src\rmem_wrap_win.h

copy ..\..\src\libs\rmem\genie\genie.lua				SDK\genie\genie.lua
copy ..\..\src\libs\rmem\genie\rmem.lua					SDK\genie\rmem.lua

cd SDK
cd samples
mkdir linker
mkdir manual
cd ..
cd ..

copy ..\..\src\libs\rmem\samples\linker\rmem_linker_sample.cpp SDK\samples\linker\MTunerLinkerExample.cpp
copy ..\..\src\libs\rmem\samples\manual\rmem_manual_sample.cpp SDK\samples\manual\MTunerManualExample.cpp

cd SDK
cd 3rd
mkdir minhook
cd minhook
mkdir src
mkdir include
cd src
mkdir hde
cd ..
cd ..
mkdir msvc
mkdir lz4-r191
cd ..
cd ..

copy ..\..\src\libs\rmem\3rd\minhook\AUTHORS.txt             SDK\3rd\minhook\AUTHORS.txt
copy ..\..\src\libs\rmem\3rd\minhook\LICENSE.txt             SDK\3rd\minhook\LICENSE.txt
copy ..\..\src\libs\rmem\3rd\minhook\src\buffer.c            SDK\3rd\minhook\src\buffer.c
copy ..\..\src\libs\rmem\3rd\minhook\src\buffer.h            SDK\3rd\minhook\src\buffer.h
copy ..\..\src\libs\rmem\3rd\minhook\src\hook.c              SDK\3rd\minhook\src\hook.c
copy ..\..\src\libs\rmem\3rd\minhook\src\trampoline.c        SDK\3rd\minhook\src\trampoline.c
copy ..\..\src\libs\rmem\3rd\minhook\src\trampoline.h        SDK\3rd\minhook\src\trampoline.h
copy ..\..\src\libs\rmem\3rd\minhook\src\hde\hde32.c         SDK\3rd\minhook\src\hde\hde32.c                    
copy ..\..\src\libs\rmem\3rd\minhook\src\hde\hde32.h         SDK\3rd\minhook\src\hde\hde32.h
copy ..\..\src\libs\rmem\3rd\minhook\src\hde\hde64.c         SDK\3rd\minhook\src\hde\hde64.c
copy ..\..\src\libs\rmem\3rd\minhook\src\hde\hde64.h         SDK\3rd\minhook\src\hde\hde64.h
copy ..\..\src\libs\rmem\3rd\minhook\src\hde\pstdint.h       SDK\3rd\minhook\src\hde\pstdint.h
copy ..\..\src\libs\rmem\3rd\minhook\src\hde\table32.h       SDK\3rd\minhook\src\hde\table32.h
copy ..\..\src\libs\rmem\3rd\minhook\src\hde\table64.h       SDK\3rd\minhook\src\hde\table64.h
copy ..\..\src\libs\rmem\3rd\minhook\include\MinHook.h       SDK\3rd\minhook\include\MinHook.h

copy ..\..\src\libs\rmem\3rd\lz4-r191\lz4.h                  SDK\3rd\lz4-r191\lz4.h
copy ..\..\src\libs\rmem\3rd\lz4-r191\lz4.c                  SDK\3rd\lz4-r191\lz4.c
   
copy ..\..\src\libs\rmem\3rd\msvc\inttypes.h                 SDK\3rd\msvc\inttypes.h
copy ..\..\src\libs\rmem\3rd\msvc\stdint.h                   SDK\3rd\msvc\stdint.h

cd ..
