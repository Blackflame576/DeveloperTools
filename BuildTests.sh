echo "==> Building tests"
g++ ./src/tests/MainTest.cpp -o ./tests/MainTest -static-libgcc -static-libstdc++ -lsqlite3 -ljsoncpp -lcurl -lgtest -lgmock -pthread -std=c++2a
echo "==> Build of tests finished"
echo "==> Running tests"
sudo ./tests/MainTest