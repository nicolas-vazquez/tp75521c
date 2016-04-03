#!/bin/bash

# Remove old libraries, ensure use right versions
echo "Search and remove old libs"
find / -type f -name "librocksdb.a" -exec rm {} \;
find / -type f -name "libjsoncpp.a" -exec rm {} \;
echo "Search end"

# Instalación de dependencias y herramientas
echo "Installing tools and dependencies"
apt-get install -y --assume-yes --force-yes\
libsnappy-dev \
zlib1g-dev \
libbz2-dev \
libgflags-dev

# Instala las librerías
echo "Installing libraries"
apt-get install -y wget
mkdir -p temp_install && \
cd temp_install && \

echo "Installing rocksDB"
wget https://github.com/facebook/rocksdb/archive/master.zip && \
unzip master.zip && \
cd rocksdb-master && \
make shared_lib && \
sudo install -d /usr/include && \
sudo cp -r include/rocksdb /usr/include && \
sudo install -m755 -D librocksdb.so /usr/lib/librocksdb.so && \
sudo install -D -m644 LICENSE "/usr/share/licenses/$pkgname/LICENSE" && \
cd .. && \

echo "Installing jsoncpp"
wget https://github.com/open-source-parsers/jsoncpp/archive/0.y.z.zip && \
unzip 0.y.z.zip && \
cd jsoncpp-0.y.z && \
python amalgamate.py && \
cd dist && \
gcc -c jsoncpp.cpp && \
ar rvs libjsoncpp.a jsoncpp.o && \
sudo cp libjsoncpp.a /usr/lib && \
cd ../.. && \

echo "Installing mongose-cpp"
wget https://github.com/Gregwar/mongoose-cpp/archive/master.zip && \
unzip master.zip && \
cd mongoose-cpp-master && \
cmake . && \
make install && \
cd ../.. && \
rm -rf temp_install


echo "Make and install"

mkdir -p build && cd build \
cmake .. && make
