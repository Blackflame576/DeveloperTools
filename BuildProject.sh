#!/bin/bash
echo "==> Building"
unameOut=$(uname -a)
case "${unameOut}" in
	Darwin*) 	os="macOS";;
	Linux*)		os="Linux";;
esac
if [ $os == "Linux" ]
then
  # Building
	mkdir build
  cd build
  mkdir Linux
  cd ..
  g++ -o ./build/Linux/DeepForgeToolset ./src/DeepForgeToolset.cpp -DCURL_STATICLIB -I ../../include -I ./src/include -L ../../lib/  -lcurl -Wreturn-type -ljsoncpp -lsqlite3 -std=c++20
	echo "==> Copying folder of DB to build/Linux ..."
  cp --recursive ./src/DB ./build/Linux/DB
  echo "==> Copying folder of DB to build/Windows was successfully."
  echo "==> Copying folder of include to build/Linux"
  cp --recursive ./src/include ./build/Linux/include
  echo "==> Copying folder of include to build/Linux was successfully."
  echo "==> Copying folder of Scripts to build/Linux"
  cp --recursive ./src/Scripts ./build/Linux/Scripts
  echo "==> Copying folder of Scripts to build/Linux was successfully."
  echo "==> Copying folder of utils to build/Linux"
  cp --recursive ./src/utils ./build/Linux/utils
  echo "==> Copying folder of utils to build/Linux was successfully."
  echo "==> Copying folder of locale to build/Linux"
  cp --recursive ./src/locale ./build/Linux/locale
  echo "==> Copying folder of locale to build/Linux was successfully."
  echo "==> Copying folder of Logo to build/Linux"
  cp --recursive ./src/Logo ./build/Linux/Icon
  echo "==> Copying folder of Logo to build/Linux was successfully."
elif [ $os == "macOS" ]
then
	cd build
	cd MacOS
	./DeepForgeToolset
fi
#echo "=================================="

echo "=================================="