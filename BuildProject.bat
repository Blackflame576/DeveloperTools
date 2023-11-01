@echo off
set arg_1 = %1
echo -- Building library Zipper
git clone --recursive https://github.com/sebastiandev/zipper.git
cd src
mkdir lib
cd ..
cd zipper
mkdir build
cmake  .
cmake --build .
rename "libstaticZipper.a" "libZipper.a"
Xcopy *.a  ..\src\lib\  /Y
cd ..
@REM rmdir .\zipper /s /q
echo -- Zipper successfully builded
echo ==================================
echo -- Building library Google Test and Google Mock
git clone --recursive git@github.com:google/googletest.git
cd src
mkdir lib
cd ..
cd googletest
cmake  .
cmake --build .
cd lib
Xcopy *.a  ..\..\src\lib\  /Y
cd .. && cd ..
@REM rmdir .\googletest /s /q
echo -- Google Test and Google Mock successfully builded
echo ==================================
echo -- Building project
if exist .\build\Windows (
    if ERRORLEVEL 0 (
        g++ -o .\build\Windows\DeepForgeToolset.exe .\src\resource.res .\src\DeepForgeToolset.cpp -DCURL_STATICLIB -I ..\..\include -I .\src\include -L ..\..\lib\ -L .\src\lib\ -static-libgcc -static-libstdc++ -lws2_32 -lurlmon  -lcurl -w -ljsoncpp -lZipper -lz -lsqlite3 -std=c++20
    ) else (
        echo -- Error in project build.
    )
) else (
    mkdir build
    cd build
    mkdir Windows
    cd ..
    if ERRORLEVEL 0 (
        g++ -o .\build\Windows\DeepForgeToolset.exe .\src\resource.res .\src\DeepForgeToolset.cpp -DCURL_STATICLIB -I ..\..\include -I .\src\include -L ..\..\lib\ -L .\src\lib\ -static-libgcc -static-libstdc++ -lws2_32 -lurlmon -lcurl -w -ljsoncpp -lZipper -lz -lsqlite3 -std=c++20
    ) else (
        echo -- Error in project build.
    )
)
mkdir tests
echo -- Building tests
if ERRORLEVEL 0 (
    g++ .\src\tests\MainTest.cpp -o .\tests\MainTest -I ..\..\include -I .\src\include -L ..\..\lib\ -L .\src\lib\ -static-libgcc -static-libstdc++  -lsqlite3 -ljsoncpp -lcurl -lgtest -lgmock -pthread -std=c++20 -w
   echo -- Build of tests was successfully.
   echo -- Running ".\tests\MainTest.exe"
   cd tests
   .\MainTest.exe
   cd ..
) else (
    echo -- Error in tests build.
)

echo ==================================
@REM echo -- Copying folder of include to build/Windows
@REM Xcopy .\src\include .\build\Windows\include /E /H /C /I /Y
@REM echo -- Copying folder of include to build/Windows was successfully.
echo -- Copying folder of DB to build/Windows
Xcopy .\src\DB .\build\Windows\DB /E /H /C /I /Y
echo -- Copying folder of DB to build/Windows was successfully.

@REM echo -- Copying folder of utils to build/Windows
@REM Xcopy .\src\utils .\build\Windows\utils /E /H /C /I /Y
@REM echo -- Copying folder of utils to build/Windows was successfully.
echo -- Copying folder of locale to build/Windows
Xcopy .\src\locale .\build\Windows\locale /E /H /C /I /Y
echo -- Copying folder of locale to build/Windows was successfully.

echo -- Copying folder of Scripts to build/Windows
Xcopy .\src\Scripts .\build\Windows\Scripts /E /H /C /I /Y
echo -- Copying folder of Scripts to build/Windows was successfully.
@REM echo -- Copying folder of Logo to build/Windows
@REM Xcopy .\src\Logo  .\build\Windows\Logo /E /H /C /I /Y
@REM echo -- Copying folder of Logo to build/Windows was successfully.
@REM echo -- Copying folder of DLL to build/Windows
@REM Xcopy .\DLL  .\build\Windows /E /H /C /I /Y
@REM echo -- Copying folder of DLL to build/Windows was successfully.
echo ==================================

if arg_1=="-autostart" or arg_1=="-AutoStart" or arg_1=="-Autostart" (
   echo -- Running ".\build\Windows\DeeepForgeToolset.exe"
   cd build
   cd Windows
   .\DeepForgeToolset.exe
)