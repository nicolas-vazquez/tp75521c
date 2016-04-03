#!/bin/bash

# Remove old libraries, ensure use right versions
echo "Search and remove old libs"
find / -type f -name "librocksdb.a" -exec rm {} \;
find / -type f -name "libjsoncpp.a" -exec rm {} \;
echo "Search end"

# Instalación de dependencias y herramientas
echo "Installing tools and dependencies"
apt-get install -y --force-yes\
libsnappy-dev \
zlib1g-dev \
libbz2-dev \
libgflags-dev

# Instala las librerías
echo "Installing libraries"
apt-get install -y wget
mkdir -p temp_install && \
cd temp_install && \
wget https://github.com/facebook/rocksdb/archive/v3.13.1.zip && \
unzip v3.13.1.zip && \
cd rocksdb-3.13.1 && \
make static_lib && \
sudo cp librocksdb.a /usr/lib && \
cd .. && \
wget https://github.com/open-source-parsers/jsoncpp/archive/0.y.z.zip && \
unzip 0.y.z.zip && \
cd jsoncpp-1.6.5 && \
python amalgamate.py && \
cd dist && \
gcc -c jsoncpp.cpp && \
ar rvs libjsoncpp.a jsoncpp.o && \
sudo cp libjsoncpp.a /usr/lib && \
cd ../.. && \
wget https://github.com/Gregwar/mongoose-cpp/archive/master.zip && \
unzip master.zip && \
cd mongoose-cpp-master && \
cmake . && \
make install \
cd ../.. && \
rm -rf temp_install


echo "Make and install"

mkdir -p build && cd build \
cmake . && make
