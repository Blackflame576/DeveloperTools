sudo zypper update
sudo zypper install rpmdevtools make gcc-c++ gcc automake autoconf libtool
wget https://www.openssl.org/source/openssl-1.1.1m.tar.gz
tar zxvf openssl-1.1.1m.tar.gz
cd openssl-1.1.1m
./config --prefix=/usr/local/openssl --openssldir=/usr/local/openssl no-ssl2
sudo make
sudo make test
sudo make install