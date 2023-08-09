echo "==> Building"
unameOut=$(uname -a)
case "${unameOut}" in
	Darwin*) 	os="macOS";;
	Linux*)		os="Linux";;
esac
if [ $os == "Linux" ]
then
  # Building
	if [-d "./build/Linux"]
	then
	  g++ -o .\build\Linux\DeepForgeToolset.exe .\src\DeepForgeToolset.cpp -DCURL_STATICLIB -I ..\..\include -I .\src\include -L ..\..\lib\  -lcurl -Wreturn-type -ljsoncpp -lsqlite3 -std=c++20
	else
	  mkdir build
    cd build
    mkdir Linux
    cd ..
    g++ -o .\build\Linux\DeepForgeToolset.exe .\src\DeepForgeToolset.cpp -DCURL_STATICLIB -I ..\..\include -I .\src\include -L ..\..\lib\  -lcurl -Wreturn-type -ljsoncpp -lsqlite3 -std=c++20
	fi
	# Exists folder
	if [! -d "./build/Linux/DB"]
	then
	  echo "==> Copying folder of DB to build/Linux ..."
	  cp ./src/DB ./build/Linux/DB
	  echo "==> Copying folder of DB to build/Windows was successfully."

	if [! -d "./build/Linux/include"]
	then
	  echo "==> Copying folder of include to build/Linux"
	  cp ./src/include ./build/Linux/include
	  echo "==> Copying folder of include to build/Linux was successfully."

	if [! -d "./build/Linux/Scripts"]
	then
	  echo "==> Copying folder of Scripts to build/Linux"
	  cp ./src/Scripts ./build/Linux/Scripts
	  echo "==> Copying folder of Scripts to build/Linux was successfully."

	if [! -d "./build/Linux/utils"]
	then
	  echo "==> Copying folder of utils to build/Linux"
	  cp ./src/utils ./build/Linux/utils
	  echo "==> Copying folder of utils to build/Linux was successfully."

	if [! -d "./build/Linux/locale"]
	then
	  echo "==> Copying folder of locale to build/Linux"
	  cp ./src/locale ./build/Linux/locale
	  echo "==> Copying folder of locale to build/Linux was successfully."

	if [! -d "./build/Linux/Icon"]
	then
	  echo "==> Copying folder of Icon to build/Linux"
	  cp ./src/Icon ./build/Linux/Icon
	  echo "==> Copying folder of Icon to build/Linux was successfully."

elif [ $os == "macOS" ]
then
	cd build
	cd MacOS
	./DeepForgeToolset
fi
#echo "=================================="

echo "=================================="
