@echo off
copy MTuner.swx MTuner64.swx
copy dia.wxs dia32.wxs
copy dia.wxs dia64.wxs
Uuidgen -c -opid_guid

set /p PID=<pid_guid

"../../../../../Tools/Fart/fart.exe" MTuner64.swx ##PLATFORM## x64
"../../../../../Tools/Fart/fart.exe" dia64.wxs ##PLATFORM## x64
"../../../../../Tools/Fart/fart.exe" MTuner64.swx ##GUID1## %PID%
"../../../../../Tools/Fart/fart.exe" MTuner64.swx ##GUID2## 09A1B85A-2575-41E1-87C6-673B3F85D484
"../../../../../Tools/Fart/fart.exe" MTuner64.swx ##GUID3## 3B804530-58E3-4AA1-856F-3C5A88D91052
"../../../../../Tools/Fart/fart.exe" MTuner64.swx ##GUID4## BC4392D0-85BE-4BD5-86A9-71B7E16315C1
"../../../../../Tools/Fart/fart.exe" MTuner64.swx ##GUID5## 4C6273BB-1156-4483-B2F3-7B03ACA008F7
"../../../../../Tools/Fart/fart.exe" MTuner64.swx ##GUID6## 71B03195-2591-4147-BAE5-75869304C0B3
"../../../../../Tools/Fart/fart.exe" MTuner64.swx ##GUID7## DE3F85B1-2610-45AF-BD17-8947B802D092
"../../../../../Tools/Fart/fart.exe" MTuner64.swx ##GUID8## 88D52309-2EEA-417D-A4CE-A78C0203B509
"../../../../../Tools/Fart/fart.exe" MTuner64.swx ##GUID9## 980A4F9B-4B70-46E8-8B6F-D6E0DE711803
"../../../../../Tools/Fart/fart.exe" MTuner64.swx ##GUID10## 89D17F78-BE1F-4E06-A351-C8686DDF4E04
"../../../../../Tools/Fart/fart.exe" MTuner64.swx ##GUID11## F54A578D-E2A8-447C-82E1-F2977F69603C
"../../../../../Tools/Fart/fart.exe" MTuner64.swx ##GUID12## CBD5B17D-566C-41F3-886C-A13B693AF743
"../../../../../Tools/Fart/fart.exe" MTuner64.swx ##GUID13## 995B8664-C9D2-42B6-AA0F-E500EC27C85A
"../../../../../Tools/Fart/fart.exe" MTuner64.swx ##GUID14## 6C192682-76D7-4FB6-9445-C652B30C5989
"../../../../../Tools/Fart/fart.exe" MTuner64.swx ##GUID15## F552D103-DDDC-452A-AAA6-CAE5556AFAE3
"../../../../../Tools/Fart/fart.exe" MTuner64.swx ##GUID16## 63735900-0640-48CA-AF4A-33B04EDC2098
"../../../../../Tools/Fart/fart.exe" MTuner64.swx ##GUID17## 3C9CF2F2-0F63-4BAD-A34B-AAA6DB2D0CAC
"../../../../../Tools/Fart/fart.exe" MTuner64.swx ##GUID18## F125E34C-32C3-40D7-8C07-E0362BF55D18
"../../../../../Tools/Fart/fart.exe" MTuner64.swx ##GUID19## E203AAF4-9B3F-4D68-BDBD-5A23D3CB8180
"../../../../../Tools/Fart/fart.exe" MTuner64.swx ##GUID20## 5662B75F-FD51-484C-B136-47F25B433D80
"../../../../../Tools/Fart/fart.exe" MTuner64.swx ##GUID21## B6ACE91E-7735-4D67-A613-E506A103556B
"../../../../../Tools/Fart/fart.exe" MTuner64.swx ##GUID22## A6E7E4AF-B0A1-43EF-989F-11C4637E458D
"../../../../../Tools/Fart/fart.exe" MTuner64.swx ##GUID23## 8A579042-CF01-45C8-9C6F-250E0B017232
"../../../../../Tools/Fart/fart.exe" MTuner64.swx ##GUID24## C0F30A68-A8B9-4B32-A3F5-976181FDE170

"../../../../../Tools/WiX/candle.exe" MTuner64.swx MTunerInstallDirDlg.wxs MTunerWixUI_InstallDir.wxs MTunerExitDialog.wxs MTunerCustomizeDlg.wxs  -arch x64
"../../../../../Tools/WiX/light.exe" -ext ../../../../Tools/WiX/WiX/WixUIExtension.dll -ext ../../../../Tools/WiX/WiX/WixUtilExtension -out mtuner64.msi MTuner64.wixobj MTunerInstallDirDlg.wixobj MTunerWixUI_InstallDir.wixobj MTunerExitDialog.wixobj MTunerCustomizeDlg.wixobj

del pid_guid

