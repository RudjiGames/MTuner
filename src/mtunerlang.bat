%QTDIR_VS2017_x64%\bin\lupdate.exe -verbose -no-obsolete mtunerlang.pro
%QTDIR_VS2017_x64%\bin\linguist.exe mtuner_en.ts mtuner_rs.ts mtuner_it.ts mtuner_de.ts
%QTDIR_VS2017_x64%\bin\lrelease mtunerlang.pro
