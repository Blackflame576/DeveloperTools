FROM gcc:latest as build
COPY . ./app
WORKDIR ./app

RUN apt update -y && apt install \
    curl \ 
    g++ \ 
    gcc \ 
    build-essential \ 
    cmake \
    make \ 
    libcurl4-openssl-dev \ 
    libjsoncpp-dev \ 
    libfmt-dev \ 
    libsqlite3-dev \ 
    libgtest-dev \ 
    googletest \ 
    google-mock \ 
    libgmock-dev \ 
    libtbb-dev \
    libzip-dev -y
RUN mkdir build && cd build && mkdir Linux && cd ..
RUN g++ -o ./build/Linux/DeepForgeToolset ./src/DeepForgeToolset.cpp -DCURL_STATICLIB -I ../../include -I ./src/include -L ../../lib/  -lcurl -Wreturn-type -ljsoncpp -lsqlite3 -std=c++2a