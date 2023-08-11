#!/bin/bash
echo "==> Building"
unameOut=$(uname -a)
case "${unameOut}" in
	Darwin*) 	os="macOS";;
	Linux*)		os="Linux";;
esac
# Building
mkdir build
cd build
mkdir $os
cd ..
g++ -o ./build/$os/DeepForgeToolset ./src/DeepForgeToolset.cpp -DCURL_STATICLIB -I ../../include -I ./src/include -L ../../lib/  -lcurl -Wreturn-type -ljsoncpp -lsqlite3 -std=c++2a
echo "==> Copying folder of DB to build/$os ..."
cp -R ./src/DB ./build/$os/DB
echo "==> Copying folder of DB to build/$os was successfully."
echo "==> Copying folder of include to build/$os"
cp -R ./src/include ./build/$os/include
echo "==> Copying folder of include to build/$os was successfully."
echo "==> Copying folder of Scripts to build/$os"
cp -R ./src/Scripts ./build/$os/Scripts
echo "==> Copying folder of Scripts to build/$os was successfully."
echo "==> Copying folder of utils to build/$os"
cp -R ./src/utils ./build/$os/utils
echo "==> Copying folder of utils to build/$os was successfully."
echo "==> Copying folder of locale to build/$os"
cp -R ./src/locale ./build/$os/locale
echo "==> Copying folder of locale to build/$os was successfully."
echo "==> Copying folder of Logo to build/$os"
cp -R ./src/Logo ./build/$os/Icon
echo "==> Copying folder of Logo to build/$os was successfully."
#echo "=================================="