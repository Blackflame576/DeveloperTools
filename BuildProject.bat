@echo off
echo -- Running "cmake ."
cmake .
echo ==================================
echo -- Running "cmake --build ."
cmake --build .
echo ==================================
echo -- Running "DeepForgeToolset.exe"
cd build
cd Windows
.\DeepForgeToolset.exe