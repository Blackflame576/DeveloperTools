@echo off
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