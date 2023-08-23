#!/bin/bash
echo "==> Building"
unameOut=$(uname -a)
case "${unameOut}" in
	Darwin*) 	os="macOS";;
	Linux*)		os="Linux";;
esac
# Installing libraries
if $os=="macOS"
then
elif $os=="Linux"
then

   YUM_PACKAGE_NAME="jsoncpp jsoncpp-devel"
   DEB_PACKAGE_NAME="python2.7 python-dev python-pip libssl-dev"

   if cat /etc/*release | grep ^NAME | grep CentOS; then
      echo "==============================================="
      echo "Installing packages $YUM_PACKAGE_NAME on CentOS"
      echo "==============================================="
      yum install -y $YUM_PACKAGE_NAME
   elif cat /etc/*release | grep ^NAME | grep Red; then
      echo "==============================================="
      echo "Installing packages $YUM_PACKAGE_NAME on RedHat"
      echo "==============================================="
      yum install -y $YUM_PACKAGE_NAME
   elif cat /etc/*release | grep ^NAME | grep Fedora; then
      echo "================================================"
      echo "Installing libraries"
      echo "================================================"
      sudo yum install -y $YUM_PACKAGE_NAME
   elif cat /etc/*release | grep ^NAME | grep Ubuntu; then
      echo "==============================================="
      echo "Installing packages $DEB_PACKAGE_NAME on Ubuntu"
      echo "==============================================="
      apt-get update
      apt-get install -y $DEB_PACKAGE_NAME
   elif cat /etc/*release | grep ^NAME | grep Debian ; then
      echo "==============================================="
      echo "Installing packages $DEB_PACKAGE_NAME on Debian"
      echo "==============================================="
      apt-get update
      apt-get install -y $DEB_PACKAGE_NAME
   elif cat /etc/*release | grep ^NAME | grep Mint ; then
      echo "============================================="
      echo "Installing packages $DEB_PACKAGE_NAME on Mint"
      echo "============================================="
      apt-get update
      apt-get install -y $DEB_PACKAGE_NAME
   elif cat /etc/*release | grep ^NAME | grep Knoppix ; then
      echo "================================================="
      echo "Installing packages $DEB_PACKAGE_NAME on Kanoppix"
      echo "================================================="
      apt-get update
      apt-get install -y $DEB_PACKAGE_NAME
   else
      echo "OS NOT DETECTED, couldn't install package $PACKAGE"
      exit 1;
   fi
fi
# Building
sudo rm -rf ./build/Linux
mkdir build
cd build
mkdir $os
cd ..
echo "==> Building project"
g++ -o ./build/$os/DeepForgeToolset ./src/resource.res ./src/DeepForgeToolset.cpp -DCURL_STATICLIB -I ../../include -I ./src/include -L ../../lib/ -static-libgcc -static-libstdc++  -lcurl -w -ljsoncpp -lsqlite3 -std=c++2a
echo "==> Build of project finished"
mkdir tests
echo "==> Building tests"
g++ ./src/tests/MainTest.cpp -o ./tests/MainTest -static-libgcc -static-libstdc++ -lsqlite3 -ljsoncpp -lcurl -lgtest -lgmock -pthread -std=c++2a -w
echo "==> Build of tests finished"
echo "==> Running tests"
sudo ./tests/MainTest
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
cd build
cd $os
sudo ./DeepForgeToolset
#echo "=================================="
exit 0