#!/bin/bash
echo "==> Installing libraries"
# Installing libraries
YUM_PACKAGE_NAME="jsoncpp jsoncpp-devel make cmake g++ gcc gtest-devel gtest gmock-devel gmock curl libcurl-devel libcurl sqlite-devel sqlite-tcl libstdc++.x86_64 libstdc++-devel.x86_64 libstdc++-static.x86_64 zlib"
DEB_PACKAGE_NAME="g++ gcc build-essential cmake make curl libcurl4-openssl-dev libjsoncpp-dev libfmt-dev libsqlite3-dev libgtest-dev googletest google-mock libgmock-dev libtbb-dev libzip-dev zlib1g-dev"
PACMAN_PACKAGE_NAME="jsoncpp gcc base-devel cmake  clang gtest lib32-curl libcurl-compat libcurl-gnutls curl fmt lib32-sqlite sqlite sqlite-tcl zlib"
ZYPPER_PACKAGE_NAME="libcurl-devel gcc-c++ cmake gtest gmock zlib-devel fmt-devel sqlite3-devel jsoncpp-devel"
if [[ "$OSTYPE" == "linux-gnu"* ]]; then
   if [ -f /etc/os-release ]; then
      # freedesktop.org and systemd
      . /etc/os-release
      OS=$NAME
   elif type lsb_release >/dev/null 2>&1; then
      # linuxbase.org
      OS=$(lsb_release -si)
   elif [ -f /etc/lsb-release ]; then
      # For some versions of Debian/Ubuntu without lsb_release command
      . /etc/lsb-release
      OS=$DISTRIB_ID
   elif [ -f /etc/debian_version ]; then
      # Older Debian/Ubuntu/etc.
      OS=Debian
   elif [ -f /etc/SuSe-release ]; then
      # Older SuSE/etc.
      ...
   elif [ -f /etc/redhat-release ]; then
      # Older Red Hat, CentOS, etc.
      ...
   else
      # Fall back to uname, e.g. "Linux <version>", also works for BSD, etc.
      OS=$(uname -s)
   fi
   if [[ "$OS" == "CentOS"* ]]; then
      echo "================================================"
      echo "Installing libraries"
      echo "================================================"
      sudo yum update -y
      sudo yum install -y $YUM_PACKAGE_NAME
   elif [[ "$OS" == "Red"* ]]; then
      echo "================================================"
      echo "Installing libraries"
      echo "================================================"
      sudo yum update -y
      sudo yum install -y $YUM_PACKAGE_NAME
   elif [[ "$OS" == "Fedora"* ]]; then
      echo "================================================"
      echo "Installing libraries"
      echo "================================================"
      sudo yum update -y
      sudo yum install -y $YUM_PACKAGE_NAME
   elif [[ "$OS" == "Ubuntu"* ]]; then
      echo "================================================"
      echo "Installing libraries"
      echo "================================================"
      sudo add-apt-repository universe
      sudo apt-get update
      sudo apt-get install -y $DEB_PACKAGE_NAME
   elif [[ "$OS" == "Debian"* ]]; then
      echo "================================================"
      echo "Installing libraries"
      echo "================================================"
      sudo add-apt-repository universe
      sudo apt-get update
      sudo apt-get install -y $DEB_PACKAGE_NAME
   elif [[ "$OS" == "Mint"* ]]; then
      echo "================================================"
      echo "Installing libraries"
      echo "================================================"
      sudo add-apt-repository universe
      sudo apt-get update
      apt-get install -y $DEB_PACKAGE_NAME
   elif [[ "$OS" == "Knoppix"* ]]; then
      echo "================================================"
      echo "Installing libraries"
      echo "================================================"
      sudo add-apt-repository universe
      sudo apt-get update
      sudo apt-get install -y $DEB_PACKAGE_NAME
   elif [[ "$OS" == "Manjaro Linux"* ]]; then
      echo "================================================"
      echo "Installing libraries"
      echo "================================================"
      sudo pacman -Sy jsoncpp
      sudo pacman -Sy gcc
      sudo pacman -Sy base-devel
      sudo pacman -Sy cmake
      sudo pacman -Sy clang
      sudo pacman -Sy gtest
      sudo pacman -Sy lib32-curl
      sudo pacman -Sy libcurl-compat
      sudo pacman -Sy libcurl-gnutls
      sudo pacman -Sy curl
      sudo pacman -Sy fmt
      sudo pacman -Sy lib32-sqlite
      sudo pacman -Sy sqlite
      sudo pacman -Sy sqlite-tcl
      sudo pacman -Sy zlib
   elif [[ "$OS" == "Kali GNU/Linux"* ]]; then
      echo "================================================"
      echo "Installing libraries"
      echo "================================================"
      sudo add-apt-repository universe
      sudo apt-get update
      sudo apt-get install -y $DEB_PACKAGE_NAME
   elif [[ "$OS" == "openSUSE Leap"* ]]; then
      echo "================================================"
      echo "Installing libraries"
      echo "================================================"
      zypper update -y
      zypper install sudo -y
      sudo zypper update -y
      sudo zypper install $ZYPPER_PACKAGE_NAME -y
   else
      echo "Not found package manager"
      exit 1;
   fi
   echo "==> Building library Zipper"
   cd src
   mkdir lib
   cd ..
   git clone --recursive https://github.com/sebastiandev/zipper.git
   cd zipper
   mkdir build
   cmake .
   make
   find . -name "*.a" -exec mv "{}" ../src/lib/ \;
   cd ..
   sudo rm -rf ./zipper
   echo "==> Zipper successfully builded"
elif [[ "$OSTYPE" == "darwin"* ]]; then
   # Mac OSX
   /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
   brew  install jsoncpp sqlite3 sqlite-utils fmt clang-format curl googletest gcc zlib cmake
   echo "==> Building library Zipper"
   git clone --recursive https://github.com/sebastiandev/zipper.git
   cd src
   mkdir lib
   cd ..
   cd zipper
   mkdir build
   cmake .
   make
   find . -name "*.a" -exec cp "{}" ../src/lib/ \;
   cd ..
   sudo rm -rf ./zipper
   echo "==> Build of Zipper finished"
fi
echo "==> Libraries successfully installed"
unameOut=$(uname -a)
case "${unameOut}" in
	Darwin*) 	os="macOS";;
	Linux*)		os="Linux";;
esac
# Building
sudo rm -rf ./build/Linux
mkdir build
cd build
mkdir $os
cd ..
echo "==> Building DeepForgeToolset"
case "${unameOut}" in
	Darwin*) 	sudo clang++ -o ./build/$os/DeepForgeToolset ./src/DeepForgeToolset.cpp -DCURL_STATICLIB -I ../../include -I ./src/include -L ./src/lib   -lcurl -ljsoncpp -lsqlite3 -std=c++2a -Bstatic;;
	Linux*)		sudo g++ -o ./build/$os/DeepForgeToolset ./src/DeepForgeToolset.cpp -DCURL_STATICLIB -I ../../include -I ./src/include -L ../../lib/ -L ./src/lib -lcurl -ljsoncpp -lsqlite3 -std=c++20;;
esac
echo "==> Build of DeepForgeToolset finished"
mkdir tests
echo "==> Building tests"
case "${unameOut}" in
	Darwin*) 	sudo clang++ ./src/tests/MainTest.cpp -o ./tests/MainTest -I ./src/include -L ./src/lib -lsqlite3 -ljsoncpp -lcurl -lgtest -lgmock -lZipper -lz -pthread -std=c++2a -Bstatic;;
	Linux*)		sudo g++ ./src/tests/MainTest.cpp -o ./tests/MainTest -I ./src/include -L ./src/lib -lsqlite3 -ljsoncpp -lcurl -lgtest -lgmock -lZipper -lz -pthread -std=c++20;;
esac

echo "==> Build of tests finished"
echo "==> Running tests"
cd tests
case "${unameOut}" in
	Darwin*) 	./MainTest;;
	Linux*)		sudo ./MainTest;;
esac
cd ..
echo "==> Copying folder of DB to build/$os ..."
sudo cp -R ./src/DB ./build/$os/DB
echo "==> Copying folder of DB to build/$os was successfully."
echo "==> Copying folder of include to build/$os"
sudo cp -R ./src/include ./build/$os/include
echo "==> Copying folder of include to build/$os was successfully."
echo "==> Copying folder of Scripts to build/$os"
sudo cp -R ./src/Scripts ./build/$os/Scripts
echo "==> Copying folder of Scripts to build/$os was successfully."
echo "==> Copying folder of utils to build/$os"
sudo cp -R ./src/utils ./build/$os/utils
echo "==> Copying folder of utils to build/$os was successfully."
echo "==> Copying folder of locale to build/$os"
sudo cp -R ./src/locale ./build/$os/locale
echo "==> Copying folder of locale to build/$os was successfully."
echo "==> Copying folder of Logo to build/$os"
sudo cp -R ./src/Logo ./build/$os/Logo
echo "==> Copying folder of Logo to build/$os was successfully."
echo "==> Copying folder of UpdateManager to build/$os"
cd build
cd $os
case "${unameOut}" in
	Darwin*) 	./DeepForgeToolset;;
	Linux*)		sudo ./DeepForgeToolset;;
esac
echo "=================================="
exit 0