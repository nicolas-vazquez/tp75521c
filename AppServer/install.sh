#!/bin/bash

root_dir=`pwd`
install_dir="$root_dir/temp_install"

# Remove old libraries, ensure use right versions
echo "Search and remove old libs"
    find / -type f -name "librocksdb.a" -exec rm {} \;
    find / -type f -name "libjsoncpp.a" -exec rm {} \;
    find / -type f -name "libgtest.a" -exec rm --force {} \;
    find / -type f -name "libgtest_main.a" -exec rm --force {} \;
    find / -type f -name "libgtest.so" -exec rm --force {} \;
    find / -type f -name "libgtest_main.so" -exec rm --force {} \;
echo "Search end"

# Instalación de dependencias y herramientas
echo "Installing tools and dependencies"
apt-get update
apt-get install -y --assume-yes --force-yes libsnappy-dev zlib1g-dev libbz2-dev libgflags-dev cmake libcppunit-doc libcppunit-dev lcov libboost-all-dev libssl-dev git

## Instala las librerías
echo "Installing libraries"
apt-get install -y wget
mkdir -p temp_install && \
cd temp_install && \

echo "Installing rocksDB"
wget https://github.com/facebook/rocksdb/archive/v4.4.1.zip && \
unzip v4.4.1.zip && \
cd rocksdb-4.4.1 && \
make shared_lib && \
sudo install -d /usr/include && \
sudo cp -r include/rocksdb /usr/include && \
sudo install -m755 -D librocksdb.so.4.4.1 /usr/lib/librocksdb.so.4.4 && \
sudo install -m755 -D librocksdb.so.4.4.1 /usr/lib/librocksdb.so && \
sudo install -D -m644 LICENSE "/usr/share/licenses/$pkgname/LICENSE" && \

cd $install_dir
echo "Installing jsoncpp"
wget https://github.com/open-source-parsers/jsoncpp/archive/0.y.z.zip && \
unzip 0.y.z.zip && \
cd jsoncpp-0.y.z && \
python amalgamate.py && \
cd dist && \
gcc -c jsoncpp.cpp && \
ar rvs libjsoncpp.a jsoncpp.o && \
sudo cp libjsoncpp.a /usr/lib && \


cd $install_dir
# Last release does not have cmake enabled, so we install it from master.
echo "Installing mongose-cpp"
wget https://github.com/Gregwar/mongoose-cpp/archive/master.zip && \
unzip master.zip && \
rm master.zip && \
cd mongoose-cpp-master && \
cmake . && \
make install && \



echo "Installing Casablanca"
git clone https://github.com/Microsoft/cpprestsdk.git casablanca && \
cd casablanca/Release && \
mkdir build.debug && \
cd build.debug && \
    cmake .. -DCMAKE_BUILD_TYPE=Debug && \
make install
ldconfig -v

cd $root_dir
rm -rf temp_install

echo "Make and install"
mkdir -p build && cd build && \
cmake .. && make
