@echo off
echo -- Building
if exist .\build\Windows (
    g++ -o .\build\Windows\DeepForgeToolset.exe .\src\DeepForgeToolset.cpp -DCURL_STATICLIB -I ..\..\include -I .\src\include -L ..\..\lib\  -lcurl -Wreturn-type -ljsoncpp -lsqlite3 -std=c++20
) else (
    mkdir build
    cd build
    mkdir Windows
    cd ..
    g++ -o .\build\Windows\DeepForgeToolset.exe .\src\DeepForgeToolset.cpp -DCURL_STATICLIB -I ..\..\include -I .\src\include -L ..\..\lib\  -lcurl -Wreturn-type -ljsoncpp -lsqlite3 -std=c++20
)
echo ==================================
if not exist .\build\Windows\include (
    echo -- Copying folder of include to build/Windows
    Xcopy .\src\include .\build\Windows\include /E /H /C /I
    echo -- Copying folder of include to build/Windows was successfully.
)
if not exist .\build\Windows\DB (
    echo -- Copying folder of DB to build/Windows
    Xcopy .\src\DB .\build\Windows\DB /E /H /C /I
    echo -- Copying folder of DB to build/Windows was successfully.
)
if not exist .\build\Windows\utils (
    echo -- Copying folder of utils to build/Windows
    Xcopy .\src\utils .\build\Windows\utils /E /H /C /I
    echo -- Copying folder of utils to build/Windows was successfully.
)
if not exist .\build\Windows\locale (
    echo -- Copying folder of locale to build/Windows
    Xcopy .\src\locale .\build\Windows\locale /E /H /C /I
    echo -- Copying folder of locale to build/Windows was successfully.
)
if not exist .\build\Windows\Scripts (
    echo -- Copying folder of Scripts to build/Windows
    Xcopy .\src\Scripts .\build\Windows\Scripts /E /H /C /I
    echo -- Copying folder of Scripts to build/Windows was successfully.
)
if not exist .\build\Windows\Icon (
    echo -- Copying folder of Icon to build/Windows
    Xcopy .\src\Icon  .\build\Windows\Icon /E /H /C /I
    echo -- Copying folder of Icon to build/Windows was successfully.
)
echo ==================================
if "%1"=="-autostart" or "%1"=="-AutoStart" or "%1"=="-Autostart" (
    echo -- Running ".\build\Windows\DeeepForgeToolset.exe"
    cd build
    cd Windows
    .\DeepForgeToolset.exe
)