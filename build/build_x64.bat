@echo off



set SDK_INC_DIR=C:\Users\carlo\source\Repos\Pitxino\ets-ats\scs_sdk_1_13\include
set INSTALL_DIR=D:\games\Steam\steamapps\common\Euro Truck Simulator 2\bin\win_x64\plugins
set INSTALL_DIR2=D:\games\Steam\steamapps\common\American Truck Simulator\bin\win_x64\plugins
set SRC_DIR=C:\Users\carlo\source\Repos\Pitxino\ets-ats\ets2_plugin

set SRC_FILES=%SRC_DIR%\plugin.def %SRC_DIR%\plugin.cpp %SRC_DIR%\serial.cpp %SRC_DIR%\options.cpp

set OPTIONS=/nologo /W4 /LD /MD /EHsc /O2

@echo on


"C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.31.31103\bin\Hostx64\x64\"cl %OPTIONS% /I%SDK_INC_DIR% %SRC_FILES% /link /OUT:dash_plugin.dll

xcopy dash_plugin.dll "%INSTALL_DIR%" /D /Y
xcopy dash_plugin.txt "%INSTALL_DIR%" /D /Y


@echo off



set SDK_INC_DIR=C:\Users\carlo\source\Repos\Pitxino\ets-ats\scs_sdk_1_13\include
set INSTALL_DIR=D:\games\Steam\steamapps\common\Euro Truck Simulator 2\bin\win_x64\plugins
set INSTALL_DIR2=D:\games\Steam\steamapps\common\American Truck Simulator\bin\win_x64\plugins
set SRC_DIR=C:\Users\carlo\source\Repos\Pitxino\ets-ats\ets2_plugin

set SRC_FILES=%SRC_DIR%\plugin.def %SRC_DIR%\pluginats.cpp %SRC_DIR%\serial.cpp %SRC_DIR%\options.cpp

set OPTIONS=/nologo /W4 /LD /MD /EHsc /O2

@echo on


"C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.31.31103\bin\Hostx64\x64\"cl %OPTIONS% /I%SDK_INC_DIR% %SRC_FILES% /link /OUT:dash_plugin.dll

xcopy dash_plugin.dll "%INSTALL_DIR%" /D /Y
xcopy dash_plugin.txt "%INSTALL_DIR%" /D /Y