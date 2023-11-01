@echo off
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