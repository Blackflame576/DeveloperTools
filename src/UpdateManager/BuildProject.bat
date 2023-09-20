@echo off
echo -- Building UpdateManager
g++ -o UpdateManager.exe UpdateManager.cpp -I ..\..\include -I .\include -L ..\..\lib\  -L .\lib\Windows -static -static-libgcc -static-libstdc++ -lurlmon -lcurl -lsqlite3 -lws2_32 -lwinmm -ljsoncpp -lZipper -lz -std=c++20 -w
echo -- Build of UpdateManager finished