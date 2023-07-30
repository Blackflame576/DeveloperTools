echo "==> Running 'cmake .'"
cmake .
echo "=================================="
echo "==> Running 'cmake --build .'"
cmake --build .
echo "=================================="
unameOut=$(uname -a)
case "${unameOut}" in
	Darwin*) 	os="macOS";;
	Linux*)		os="Linux";;
esac
if [ $os == "Linux" ]
then
	cd build
	cd Linux
	./DeepForgeToolset
elif [ $os == "macOS" ]
then
	cd build 
	cd MacOS
	./DeepForgeToolset
fi