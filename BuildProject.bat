@echo off
set arg_1 = %1
echo -- Building project
if exist .\build\Windows (
    if ERRORLEVEL 0 (
        g++ -o .\build\Windows\DeepForgeToolset.exe .\src\resource.res .\src\DeepForgeToolset.cpp -DCURL_STATICLIB -I ..\..\include -I .\src\include -L ..\..\lib\ -static-libgcc -static-libstdc++   -lcurl -w -ljsoncpp -lsqlite3 -std=c++20
    ) else (
        echo -- Error in project build.
    )
) else (
    mkdir build
    cd build
    mkdir Windows
    cd ..
    if ERRORLEVEL 0 (
        g++ -o .\build\Windows\DeepForgeToolset.exe .\src\resource.res .\src\DeepForgeToolset.cpp -DCURL_STATICLIB -I ..\..\include -I .\src\include -L ..\..\lib\ -static-libgcc -static-libstdc++  -lcurl -w -ljsoncpp -lsqlite3 -std=c++20
    ) else (
        echo -- Error in project build.
    )
)
mkdir tests
echo -- Building tests
if ERRORLEVEL 0 (
    g++ .\src\tests\MainTest.cpp -o .\tests\MainTest -static-libgcc -static-libstdc++  -lsqlite3 -ljsoncpp -lcurl -lgtest -lgmock -pthread -std=c++20 -w
   echo -- Build of tests was successfully.
   echo -- Running ".\tests\MainTest.exe"
   cd tests
   .\MainTest.exe
   cd ..
) else (
    echo -- Error in tests build.
)

echo ==================================
echo -- Copying folder of include to build/Windows
Xcopy .\src\include .\build\Windows\include /E /H /C /I /Y
echo -- Copying folder of include to build/Windows was successfully.
echo -- Copying folder of DB to build/Windows
Xcopy .\src\DB .\build\Windows\DB /E /H /C /I /Y
echo -- Copying folder of DB to build/Windows was successfully.

echo -- Copying folder of utils to build/Windows
Xcopy .\src\utils .\build\Windows\utils /E /H /C /I /Y
echo -- Copying folder of utils to build/Windows was successfully.
echo -- Copying folder of locale to build/Windows
Xcopy .\src\locale .\build\Windows\locale /E /H /C /I /Y
echo -- Copying folder of locale to build/Windows was successfully.

echo -- Copying folder of Scripts to build/Windows
Xcopy .\src\Scripts .\build\Windows\Scripts /E /H /C /I /Y
echo -- Copying folder of Scripts to build/Windows was successfully.
echo -- Copying folder of Logo to build/Windows
Xcopy .\src\Logo  .\build\Windows\Logo /E /H /C /I /Y
echo -- Copying folder of Logo to build/Windows was successfully.
echo -- Copying folder of DLL to build/Windows
Xcopy .\DLL  .\build\Windows /E /H /C /I /Y
echo -- Copying folder of DLL to build/Windows was successfully.
echo ==================================

cd
if arg_1=="-autostart" or arg_1=="-AutoStart" or arg_1=="-Autostart" (
   echo -- Running ".\build\Windows\DeeepForgeToolset.exe"
   cd build
   cd Windows
   .\DeepForgeToolset.exe
)